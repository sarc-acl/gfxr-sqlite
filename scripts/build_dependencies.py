#!/usr/bin/env python3
# Copyright 2026 The Sokatoa Project Authors
#
#    Licensed under the Apache License, Version 2.0 (the "License");
#    you may not use this file except in compliance with the License.
#    You may obtain a copy of the License at
#
#        https://www.apache.org/licenses/LICENSE-2.0
#
#    Unless required by applicable law or agreed to in writing, software
#    distributed under the License is distributed on an "AS IS" BASIS,
#    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#    See the License for the specific language governing permissions and
#    limitations under the License.

"""Build the external dependencies of gfxr-sqlite.

The only dependency is gfxreconstruct (nested submodule at external/gfxreconstruct).
This script initializes it if needed and runs its bundled build.py with the same
flags Sokatoa uses, so the gfxr-sqlite project can link against the resulting libs.

The nested gfxreconstruct submodule is marked `update = none` in .gitmodules so
that parent projects consuming gfxr-sqlite via add_subdirectory (e.g. Sokatoa) do
not pull a redundant copy. This script overrides that locally to force the init.
"""

from __future__ import annotations

import argparse
import platform
import subprocess
import sys
from pathlib import Path

PROJECT_ROOT = Path(__file__).resolve().parent.parent
GFXR_PATH = PROJECT_ROOT.joinpath('external', 'gfxreconstruct')

BUILD_TYPE_RELEASE = 'release'
BUILD_TYPE_DEBUG = 'debug'


def run(args: list, *, cwd: Path | None = None) -> None:
    """Run a command, streaming output, raising on non-zero exit."""
    label_cwd = f' (cwd={cwd})' if cwd else ''
    print(f'+ {" ".join(map(str, args))}{label_cwd}', flush=True)
    result = subprocess.run([str(a) for a in args], cwd=str(cwd) if cwd else None)
    if result.returncode != 0:
        raise SystemExit(f'\nCommand failed with exit code {result.returncode}: {" ".join(map(str, args))}\n')


def target_arch() -> str:
    """Architecture component of gfxreconstruct's build output path."""
    arch = platform.uname().machine
    if arch in ('x86_64', 'AMD64'):
        arch = 'x64'
    if platform.system() == 'Darwin':
        arch = 'universal'
    return arch


def platform_dir() -> str:
    """Platform component of gfxreconstruct's build output path (matches CMakeLists.txt)."""
    system = platform.system()
    if system == 'Windows':
        return 'windows'
    if system == 'Darwin':
        return 'darwin'
    return 'linux'


def gfxreconstruct_cmake_output_dir(build_type: str) -> Path:
    """Directory holding gfxreconstruct's build output for the given config.

    Mirrors the paths gfxr-sqlite's CMakeLists.txt includes/links against:
    gfxreconstruct uses 'dbuild' for debug and 'build' for release.
    """
    subdir = 'dbuild' if build_type == BUILD_TYPE_DEBUG else 'build'
    return GFXR_PATH.joinpath(subdir, platform_dir(), target_arch(), 'cmake_output')


def ensure_gfxreconstruct_initialized() -> None:
    """Initialize the nested gfxreconstruct submodule (overrides update=none).

    Idempotent: a no-op if gfxreconstruct's working tree already has its build.py.
    """
    if GFXR_PATH.joinpath('scripts', 'build.py').is_file():
        print(f'gfxreconstruct submodule already initialized at {GFXR_PATH}')
        return

    print('Initializing nested gfxreconstruct submodule')
    # -c override bypasses the `update = none` set in .gitmodules.
    run(['git', '-c', 'submodule.external/gfxreconstruct.update=checkout',
         'submodule', 'update', '--init', '--recursive', 'external/gfxreconstruct'],
        cwd=PROJECT_ROOT)


def build_gfxreconstruct(build_type: str, clean: bool, parallel: int) -> None:
    """Build gfxreconstruct via its bundled scripts/build.py.

    parallel: number of compilation jobs (0 = use all available cores).
    """
    print(f'Building gfxreconstruct ({build_type}, -j={parallel})')

    args = [sys.executable, 'scripts/build.py', '-c', build_type,
            '--skip-check-code-style', '--skip-tests', '--skip-d3d12-support',
            f'-j={parallel}',
            '--cmake-extra=GFXRECON_ENABLE_OPENXR=OFF',
            '--cmake-extra=CMAKE_CXX_VISIBILITY_PRESET=hidden']

    if platform.system() == 'Windows':
        # Required for non-English Windows locales (UTF-8 sources).
        args += ['--cmake-extra=CMAKE_CXX_FLAGS_INIT=/utf-8']

    if platform.system() == 'Darwin':
        args += ['--cmake-extra', 'CMAKE_OSX_DEPLOYMENT_TARGET=13.3']

    if clean:
        run(args + ['--clean'], cwd=GFXR_PATH)
    run(args, cwd=GFXR_PATH)


def add_parallel_arg(parser: argparse.ArgumentParser) -> None:
    """Add the shared --parallel / -j argument (used by both build.py and this script)."""
    parser.add_argument('--parallel', '-j', type=int, default=0,
                        help='Number of compilation jobs to run in parallel '
                             '(0 = use all available cores, default: 0)')


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__,
                                     formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument('build_type', choices=[BUILD_TYPE_RELEASE, BUILD_TYPE_DEBUG],
                        nargs='?', default=BUILD_TYPE_RELEASE,
                        help='Build configuration (default: release)')
    parser.add_argument('--clean', action='store_true',
                        help='Clean before building')
    parser.add_argument('--no-init', action='store_true',
                        help='Skip submodule initialization (assume it is already set up)')
    add_parallel_arg(parser)
    args = parser.parse_args()

    if not args.no_init:
        ensure_gfxreconstruct_initialized()
    build_gfxreconstruct(args.build_type, args.clean, args.parallel)


if __name__ == '__main__':
    main()
