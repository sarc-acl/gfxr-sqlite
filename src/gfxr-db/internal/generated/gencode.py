#!/usr/bin/env python
#
# Copyright (c) 2018-2023 Valve Corporation
# Copyright (c) 2018-2023 LunarG, Inc.
# Copyright (c) 2024-2025 The Sokatoa Project Authors
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
#
# The content of this file was derived from the Khronos Registry gencode.py
# and related Python files found in the KhronosGroup/Vulkan-Headers GitHub repository.
#
# Copyright (c) 2013-2016 The Khronos Group Inc.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

import argparse
import os
import pdb
import sys
import time
from registry.reg import Registry, etree
from generator import write

# Consumers
from vulkan_sqlite_consumer_header_generator import VulkanSqliteConsumerHeaderGenerator, VulkanSqliteConsumerHeaderGeneratorOptions
from vulkan_sqlite_consumer_body_generator import VulkanSqliteConsumerBodyGenerator, VulkanSqliteConsumerBodyGeneratorOptions

# Converters
from vulkan_struct_to_sqlite_header_generator import VulkanStructToSqliteHeaderGenerator, VulkanStructToSqliteHeaderGeneratorOptions
from vulkan_struct_to_sqlite_body_generator import VulkanStructToSqliteBodyGenerator, VulkanStructToSqliteBodyGeneratorOptions
from vulkan_enum_to_sqlite_header_generator import VulkanEnumToSqliteHeaderGenerator, VulkanEnumToSqliteHeaderGeneratorOptions
from vulkan_enum_to_sqlite_body_generator import VulkanEnumToSqliteBodyGenerator, VulkanEnumToSqliteBodyGeneratorOptions
from vulkan_process_features_body_generator import VulkanProcessFeaturesBodyGenerator, VulkanProcessFeaturesBodyGeneratorOptions

# Simple timer functions
start_time = None


def start_timer(timeit):
    global start_time
    if timeit:
        start_time = time.process_time()


def end_timer(timeit, msg):
    global start_time
    if timeit:
        end_time = time.process_time()
        write(msg, end_time - start_time, file=sys.stderr) # type: ignore
        start_time = None


# JSON files for customizing code generation
default_blacklists = 'blacklists.json'
default_platform_types = 'platform_types.json'


def _getExtraVulkanHeaders(extraHeadersDir):
    '''
    Recursively get a list of extra Vulkan headers used in the generated code,
    that are included after vulkan/vulkan.h is included
    '''
    extra_headers = []
    for child in os.listdir(extraHeadersDir):
        childPath = os.path.join(extraHeadersDir, child)
        if os.path.isdir(childPath):
            extra_headers.extend(_getExtraVulkanHeaders(childPath))
        else:
            extra_headers.append(childPath)
    return extra_headers


def getExtraVulkanHeaders(extraHeadersDir):
    '''
    Get a list of extra Vulkan headers used in the generated code, that are
    included after vulkan/vulkan.h is included
    '''
    return [
        os.path.relpath(header, extraHeadersDir)
        for header in _getExtraVulkanHeaders(extraHeadersDir)
    ]


def extend_xml(dest_tree, src_xml, debug=False):
    '''Extend the parsed vk.xml registry tree with content from another xml file'''
    def merge(dest, src):
        '''Perform a recursive merge of src into dest'''
        leaf_tags = ('command', 'enums', 'extension', 'feature', 'format',
                     'platform', 'spirvcapability', 'spirvextension', 'tag', 'type')
        for src_child in src:
            dest_child = dest.find(src_child.tag)
            if (src_child.tag in leaf_tags) or (dest_child is not None):
                # stop descent and copy if the heirarchy diverges or we reach a leaf tag
                dest.append(src_child)
            else:
                merge(dest_child, src_child)
    merge(dest_tree.getroot(), etree.parse(src_xml).getroot())
    if debug:
        dest_tree.write(os.path.splitext(src_xml)[0] + '_merged.xml')


def make_gen_opts(args):
    """Returns a directory of [ generator function, generator options ] indexed
    by specified short names. The generator options incorporate the following
    parameters:

    args is an parsed argument object; see below for the fields that are used.
    """
    global gen_opts
    gen_opts = {}

    # Output target directory
    directory = args.directory

    # JSON configuration files
    blacklists = os.path.join(args.configs, default_blacklists)
    platform_types = os.path.join(args.configs, default_platform_types)

    # Copyright text prefixing all headers (list of strings).
    prefix_strings = [
        '/********************************************************************************',
        '    Copyright 2024-2026 The Sokatoa Project Authors',
        '',
        '    Licensed under the Apache License, Version 2.0 (the "License");',
        '    you may not use this file except in compliance with the License.',
        '    You may obtain a copy of the License at',
        '',
        '        https://www.apache.org/licenses/LICENSE-2.0',
        '',
        '    Unless required by applicable law or agreed to in writing, software',
        '    distributed under the License is distributed on an "AS IS" BASIS,',
        '    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.',
        '    See the License for the specific language governing permissions and',
        '    limitations under the License.',
        '********************************************************************************/',
        ''
    ]

    # Text specific to Vulkan headers
    vk_prefix_strings = [
        '/*',
        '** This file is generated from the Khronos Vulkan XML API Registry.',
        '**', '*/', ''
    ]

    extra_headers = []
    if args.headers_dir is not None:
        extra_headers = getExtraVulkanHeaders(args.headers_dir)

    gen_opts['generated_vulkan_sqlite_consumer.h'] = [
        VulkanSqliteConsumerHeaderGenerator,
        VulkanSqliteConsumerHeaderGeneratorOptions(
            class_name='VulkanSqliteConsumer',
            base_class_header='vulkan_sqlite_consumer_base.h',
            constructor_args='sqlite3* db',
            is_override=True,
            filename='generated_vulkan_sqlite_consumer.h',
            directory=directory,
            blacklists=blacklists,
            platform_types=platform_types,
            prefix_text=prefix_strings + vk_prefix_strings,
            protect_file=True,
            protect_feature=False,
            extra_headers=extra_headers
        )
    ]

    gen_opts['generated_vulkan_sqlite_consumer.cpp'] = [
        VulkanSqliteConsumerBodyGenerator,
        VulkanSqliteConsumerBodyGeneratorOptions(
            filename='generated_vulkan_sqlite_consumer.cpp',
            directory=directory,
            blacklists=blacklists,
            platform_types=platform_types,
            prefix_text=prefix_strings + vk_prefix_strings,
            protect_file=False,
            protect_feature=False,
            extra_headers=extra_headers
        )
    ]

    gen_opts['generated_vulkan_struct_to_sqlite.h'] = [
        VulkanStructToSqliteHeaderGenerator,
        VulkanStructToSqliteHeaderGeneratorOptions(
            filename='generated_vulkan_struct_to_sqlite.h',
            directory=directory,
            blacklists=blacklists,
            platform_types=platform_types,
            prefix_text=prefix_strings + vk_prefix_strings,
            protect_file=True,
            protect_feature=False,
            extra_headers=extra_headers
        )
    ]

    gen_opts['generated_vulkan_struct_to_sqlite.cpp'] = [
        VulkanStructToSqliteBodyGenerator,
        VulkanStructToSqliteBodyGeneratorOptions(
            filename='generated_vulkan_struct_to_sqlite.cpp',
            directory=directory,
            blacklists=blacklists,
            platform_types=platform_types,
            prefix_text=prefix_strings + vk_prefix_strings,
            protect_file=False,
            protect_feature=False,
            extra_headers=extra_headers
        )
    ]

    gen_opts['generated_vulkan_enum_to_sqlite.h'] = [
        VulkanEnumToSqliteHeaderGenerator,
        VulkanEnumToSqliteHeaderGeneratorOptions(
            filename='generated_vulkan_enum_to_sqlite.h',
            directory=directory,
            blacklists=blacklists,
            platform_types=platform_types,
            prefixText=prefix_strings + vk_prefix_strings,
            protectFile=True,
            protectFeature=False,
            extra_headers=extra_headers
        )
    ]

    gen_opts['generated_vulkan_enum_to_sqlite.cpp'] = [
        VulkanEnumToSqliteBodyGenerator,
        VulkanEnumToSqliteBodyGeneratorOptions(
            filename='generated_vulkan_enum_to_sqlite.cpp',
            directory=directory,
            blacklists=blacklists,
            platform_types=platform_types,
            prefixText=prefix_strings + vk_prefix_strings,
            protectFile=False,
            protectFeature=False,
            extra_headers=extra_headers
        )
    ]

    gen_opts['generated_vulkan_process_features.cpp'] = [
        VulkanProcessFeaturesBodyGenerator,
        VulkanProcessFeaturesBodyGeneratorOptions(
            filename='generated_vulkan_process_features.cpp',
            directory=directory,
            blacklists=blacklists,
            platform_types=platform_types,
            prefix_text=prefix_strings + vk_prefix_strings,
            protect_file=False,
            protect_feature=False,
            extra_headers=extra_headers
        )
    ]

def gen_target(args):
    """Generate a target based on the options in the matching gen_opts{} object.
    This is encapsulated in a function so it can be profiled and/or timed.
    The args parameter is an parsed argument object containing the following
    fields that are used:
      target - target to generate
      directory - directory to generate it in
      protect - True if re-inclusion wrappers should be created
      extensions - list of additional extensions to include in generated
      interfaces
    """
    # Create generator options with specified parameters
    make_gen_opts(args)

    if args.target in gen_opts:
        create_generator = gen_opts[args.target][0]
        options = gen_opts[args.target][1]

        if not args.quiet:
            write('* Building', options.filename, file=sys.stderr)
            write(
                '* options.versions          =',
                options.versions,
                file=sys.stderr
            )
            write(
                '* options.emitversions      =',
                options.emitversions,
                file=sys.stderr
            )
            write(
                '* options.defaultExtensions =',
                options.defaultExtensions,
                file=sys.stderr
            )
            write(
                '* options.addExtensions     =',
                options.addExtensions,
                file=sys.stderr
            )
            write(
                '* options.removeExtensions  =',
                options.removeExtensions,
                file=sys.stderr
            )
            write(
                '* options.emitExtensions    =',
                options.emitExtensions,
                file=sys.stderr
            )

        gen = create_generator(
            err_file=err_warn, warn_file=err_warn, diag_file=diag
        )

        return (gen, options)
    else:
        write(
            'No generator options for unknown target:',
            args.target,
            file=sys.stderr
        )
        return None


# -feature name
# -extension name
# For both, "name" may be a single name, or a space-separated list
# of names, or a regular expression.
if __name__ == '__main__':
    parser = argparse.ArgumentParser()

    parser.add_argument('-debug', action='store_true', help='Enable debugging')
    parser.add_argument(
        '-dump', action='store_true', help='Enable dump to stderr'
    )
    parser.add_argument(
        '-diagfile',
        action='store',
        default=None,
        help='Write diagnostics to specified file'
    )
    parser.add_argument(
        '-errfile',
        action='store',
        default=None,
        help='Write errors and warnings to specified file instead of stderr'
    )
    parser.add_argument(
        '-noprotect',
        dest='protect',
        action='store_false',
        help='Disable inclusion protection in output headers'
    )
    parser.add_argument(
        '-profile', action='store_true', help='Enable profiling'
    )
    parser.add_argument(
        '-registry',
        action='store',
        default='vk.xml',
        help='Use specified registry file instead of vk.xml'
    )
    parser.add_argument(
        '-video',
        action='store',
        default='video.xml',
        help='Use specified video file instead of video.xml'
    )
    parser.add_argument(
        '-headers-dir',
        dest='headers_dir',
        action='store',
        default=None,
        help='\n'.join(
            [
                'Path to a directory that holds additional Vulkan header files required to build.',
                'These header files are included directly after the Vulkan header in all generated files.'
            ]
        )
    )
    parser.add_argument('-time', action='store_true', help='Enable timing')
    parser.add_argument(
        '-validate', action='store_true', help='Enable group validation'
    )
    parser.add_argument(
        '-o',
        action='store',
        dest='directory',
        default='.',
        help='Create target and related files in specified directory'
    )
    parser.add_argument(
        'target', metavar='target', nargs='?', help='Specify target'
    )
    parser.add_argument(
        '-quiet',
        action='store_true',
        default=True,
        help='Suppress script output during normal execution.'
    )
    parser.add_argument(
        '-verbose',
        action='store_false',
        dest='quiet',
        default=True,
        help='Enable script output during normal execution.'
    )
    parser.add_argument(
        '-configs',
        action='store',
        dest='configs',
        default='.',
        help=
        'Specify directory containing JSON configuration files for generators'
    )

    args = parser.parse_args()

    # create error/warning & diagnostic files
    if (args.errfile):
        err_warn = open(args.errfile, 'w', encoding='utf-8')
    else:
        err_warn = sys.stderr

    if (args.diagfile):
        diag = open(args.diagfile, 'w', encoding='utf-8')
    else:
        diag = None

    (gen, options) = gen_target(args) # type: ignore

    reg = Registry(gen, options)

    ## @note We parse vk.xml to an in-memory element tree and then extract the info we need
    ## from that into the Registry object once per output file we generate rather than once
    ## per run of the top-level generation script.
    start_timer(args.time)
    tree = etree.parse(args.registry)
    gen.VIDEO_TREE = etree.parse(args.video)
    end_timer(args.time, '* Time to make ElementTree =')

    # Apply any temporary patches to the xml to allow correct code generation
    # from it. These should be reviewed and removed when the xml is fixed upstream.
    start_timer(args.time)
    # There are no current patches needed, but here is an example of how to patch the XML
    # after parsing to add a missing single attribute:
    # Workaround 1.3.264 VkFrameBoundaryEXT.pTag lacking len field:
    # <https://github.com/KhronosGroup/Vulkan-Docs/pull/2240>
    # if ptag_member := tree.find('types/type[@name="VkFrameBoundaryEXT"]/member[name="pTag"]'):
    #    ptag_member.set('len', 'tagSize')
    end_timer(args.time, '* Time to patch ElementTree =')

    # Extend the vk.xml tree with XML files from the config dir
    for filename in os.listdir(args.configs):
        if filename.endswith('.xml'):
            extend_xml(tree, os.path.join(args.configs, filename))

    start_timer(args.time)
    reg.loadElementTree(tree)
    end_timer(args.time, '* Time to parse ElementTree =')
    
    if (args.validate):
        reg.validateGroups()

    if (args.dump):
        write('* Dumping registry to regdump.txt', file=sys.stderr)
        reg.dumpReg(filehandle=open('regdump.txt', 'w', encoding='utf-8'))

    if (args.debug):
        pdb.run('reg.api_gen()')
    else:
        start_timer(args.time)
        reg.apiGen()
        end_timer(args.time, '* Time to generate ' + options.filename + ' =')

    if not args.quiet:
        write('* Generated', options.filename, file=sys.stderr)
