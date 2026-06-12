#!/usr/bin/env python3
#
# Copyright (c) 2018 Valve Corporation
# Copyright (c) 2018-2023 LunarG, Inc.
# Copyright (c) 2024 The Sokatoa Project Authors
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to
# deal in the Software without restriction, including without limitation the
# rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
# sell copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
# FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
# IN THE SOFTWARE.
'''Generate GFXR Vulkan framework source code
   Modified top level wrapper to generate code for the sokatoa project
'''

import argparse
import os
import sys
import subprocess

LOCAL_SCRIPT_DIR = os.path.abspath(os.path.dirname(__file__))
# Default path to gfxreconstruct: the nested submodule inside the gfxr-sqlite repo.
# When invoked from Sokatoa (where the script lives in external/gfxr-sqlite), this
# default points at external/gfxr-sqlite/external/gfxreconstruct. Override with --gfxr-dir.
DEFAULT_GFXR_DIR = os.path.abspath(os.path.join(LOCAL_SCRIPT_DIR, '..', '..', '..', '..', 'external', 'gfxreconstruct'))

# File names to provide to the Vulkan XML Registry generator script.
generate_targets = [
    'generated_vulkan_sqlite_consumer.h',
    'generated_vulkan_sqlite_consumer.cpp',
    'generated_vulkan_struct_to_sqlite.h',
    'generated_vulkan_struct_to_sqlite.cpp',
    'generated_vulkan_enum_to_sqlite.h',
    'generated_vulkan_enum_to_sqlite.cpp',
    'generated_vulkan_process_features.cpp'
]

if __name__ == '__main__':
    arg_parser = argparse.ArgumentParser(description=__doc__)
    arg_parser.add_argument(
        '--gfxr-dir',
        dest='gfxr_dir',
        default=None,
        help='\n'.join(
            [
                'Path to a gfxreconstruct source tree (its root, containing framework/ and external/).',
                'If omitted, defaults to the nested external/gfxreconstruct submodule inside gfxr-sqlite.'
            ]
        )
    )
    arg_parser.add_argument(
        '--registry-dir',
        dest='registry_dir',
        default=None,
        help='\n'.join(
            [
                'Path to a directory that holds the Vulkan registry file (vk.xml) used to generate Vulkan source.',
                'If this option is not provide the registry from the external Khronos Vulkan headers sub module will be used.'
            ]
        )
    )
    arg_parser.add_argument(
        '--headers-dir',
        dest='headers_dir',
        default=None,
        help='\n'.join(
            [
                'Path to a directory that holds additional Vulkan header files required to build.',
                'These header files are included directly after the Vulkan header in all generated files.',
                'All .h file under the given directory are assumed to be Vulkan headers.'
            ]
        )
    )
    args = arg_parser.parse_args()

    gfxr_dir = os.path.abspath(args.gfxr_dir) if args.gfxr_dir is not None else DEFAULT_GFXR_DIR
    if not os.path.isdir(gfxr_dir):
        raise Exception(f'Error: gfxreconstruct dir {gfxr_dir} does not exist')
    SCRIPT_DIR = os.path.join(gfxr_dir, 'framework', 'generated')
    KHRONOS_REGISTRY_DIR = os.path.join(gfxr_dir, 'external', 'Vulkan-Headers', 'registry')
    KHRONOS_GENERATOR_DIR = os.path.join(SCRIPT_DIR, 'khronos_generators')
    BASE_GENERATOR_DIR = os.path.join(SCRIPT_DIR, 'khronos_generators', 'base_generators')
    GENERATOR_DIR = os.path.join(SCRIPT_DIR, 'khronos_generators', 'vulkan_generators')
    VK_HEADERS_DIR = os.path.join(gfxr_dir, 'external', 'Vulkan-Headers')

    registry_dir = KHRONOS_REGISTRY_DIR
    if args.registry_dir is not None:
        registry_dir = os.path.abspath(args.registry_dir)
    registry_path = os.path.join(registry_dir, 'vk.xml')
    if not os.path.isfile(registry_path):
        raise Exception(f'Error: {registry_path} does not exist')

    video_path = os.path.join(registry_dir, 'video.xml')
    if not os.path.isfile(video_path):
        raise Exception(f'Error: {video_path} does not exist')

    env = os.environ.copy()
    if not 'PYTHONPATH' in env:
        env['PYTHONPATH'] = ''

    # Note: order matters, base_generator.py exists twice.
    env['PYTHONPATH'] = os.pathsep.join(
        [
            KHRONOS_GENERATOR_DIR,
            BASE_GENERATOR_DIR,
            GENERATOR_DIR,
            KHRONOS_REGISTRY_DIR,
            VK_HEADERS_DIR,
        ]
    )

    for target in generate_targets:
        print('Generating', target)
        gencode_args = [
            sys.executable,
            os.path.join(LOCAL_SCRIPT_DIR, 'gencode.py'),
            '-o',
            LOCAL_SCRIPT_DIR,
            '-configs',
            GENERATOR_DIR,
            '-registry',
            registry_path,
            '-video',
            video_path,
        ]
        if args.headers_dir is not None:
            if not os.path.isdir(args.headers_dir):
                raise Exception(
                    'Error: extra headers dir', args.headers_dir,
                    'is not a directory'
                )
            gencode_args.extend(
                ['-headers-dir',
                 os.path.abspath(args.headers_dir)]
            )
        gencode_args.append(target)
        subprocess.check_call(
            gencode_args,
            shell=False,
            env=env,
            cwd=SCRIPT_DIR,
        )
