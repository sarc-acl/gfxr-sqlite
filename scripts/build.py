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

"""Build gfxr-sqlite end-to-end.

This is the top-level standalone build entry point: it ensures the gfxreconstruct
dependency is built (via build_dependencies.py), then configures and builds the
gfxr-sqlite CMake project, producing the gfxr-sqlite CLI executable, the
gfxr-db-library static library, and the gfxr-db-test test executable.

Typical usage:

    python3 scripts/build.py                # release
    python3 scripts/build.py debug          # debug
    python3 scripts/build.py --clean        # clean rebuild
    python3 scripts/build.py --skip-deps    # skip rebuilding gfxreconstruct
"""

from __future__ import annotations

import argparse
import shutil
import sys
from pathlib import Path

# Allow importing build_dependencies as a module.
sys.path.insert(0, str(Path(__file__).resolve().parent))
import build_dependencies  # noqa: E402

PROJECT_ROOT = build_dependencies.PROJECT_ROOT
BUILD_TYPE_RELEASE = build_dependencies.BUILD_TYPE_RELEASE
BUILD_TYPE_DEBUG = build_dependencies.BUILD_TYPE_DEBUG


def build_gfxr_sqlite(build_type: str, clean: bool) -> Path:
    """Configure and build the gfxr-sqlite CMake project. Returns the build dir."""
    if build_type == BUILD_TYPE_RELEASE:
        cmake_config = 'Release'
        build_subdir = 'build'
    else:
        cmake_config = 'Debug'
        build_subdir = 'dbuild'

    build_dir = PROJECT_ROOT.joinpath('out', build_subdir)
    if clean and build_dir.exists():
        print(f'Cleaning {build_dir}')
        shutil.rmtree(build_dir)
    build_dir.mkdir(parents=True, exist_ok=True)

    build_dependencies.run(
        ['cmake', '-S', str(PROJECT_ROOT), '-B', str(build_dir),
         f'-DCMAKE_BUILD_TYPE={cmake_config}'])
    build_dependencies.run(
        ['cmake', '--build', str(build_dir), '--config', cmake_config, '--parallel'])
    return build_dir


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__,
                                     formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument('build_type', choices=[BUILD_TYPE_RELEASE, BUILD_TYPE_DEBUG],
                        nargs='?', default=BUILD_TYPE_RELEASE,
                        help='Build configuration (default: release)')
    parser.add_argument('--clean', action='store_true',
                        help='Clean before building (both deps and gfxr-sqlite)')
    parser.add_argument('--skip-deps', action='store_true',
                        help='Skip the dependency build (assume gfxreconstruct is already built)')
    args = parser.parse_args()

    if not args.skip_deps:
        build_dependencies.ensure_gfxreconstruct_initialized()
        build_dependencies.build_gfxreconstruct(args.build_type, args.clean)

    build_dir = build_gfxr_sqlite(args.build_type, args.clean)
    print(f'\nBuild complete. Artifacts in {build_dir}')


if __name__ == '__main__':
    main()
