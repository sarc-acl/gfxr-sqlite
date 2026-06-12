#!/usr/bin/python3 -i
#
# Copyright (c) 2022-2023 LunarG, Inc.
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

import os
import re
import sys
import inspect
from vulkan_base_generator import VulkanBaseGeneratorOptions, VulkanBaseGenerator, write


class VulkanEnumToSqliteHeaderGeneratorOptions(VulkanBaseGeneratorOptions):
    """Options for generating C++ functions for Vulkan ToString() functions"""

    def __init__(
        self,
        blacklists=None,  # Path to JSON file listing apicalls and structs to ignore.
        platform_types=None,  # Path to JSON file listing platform (WIN32, X11, etc.) defined types.
        filename=None,
        directory='.',
        prefixText=[],
        protectFile=False,
        protectFeature=True,
        extra_headers=[]
    ):
        VulkanBaseGeneratorOptions.__init__(
            self,
            blacklists,
            platform_types,
            filename,
            directory,
            prefixText,
            protectFile,
            protectFeature,
            extra_headers=extra_headers
        )


# VulkanEnumToSSqliteHeaderGenerator - subclass of BaseGenerator.
# Generates C++ functions for stringifying Vulkan API enums.
class VulkanEnumToSqliteHeaderGenerator(VulkanBaseGenerator):
    """Generate C++ functions to serialize Vulkan enumeration to Sqlite"""

    SKIP_ENUM = [
    ]

    def __init__(
        self, err_file=sys.stderr, warn_file=sys.stderr, diag_file=sys.stdout
    ):
        VulkanBaseGenerator.__init__(
            self,
            err_file=err_file,
            warn_file=warn_file,
            diag_file=diag_file
        )

        # Set of enums that have been processed since we'll encounter enums that are
        #   referenced by extensions multiple times.  This list is prepopulated with
        #   enums that should be skipped.
        self.processedEnums = set()

        self.enumType = dict()
        self.flagsType = dict()
        self.flagBitsType = dict()

    # Method override
    # yapf: disable
    def beginFile(self, genOpts):
        VulkanBaseGenerator.beginFile(self, genOpts)
        includes = inspect.cleandoc(
            '''
            #include "format/platform_types.h"

            #include "decode/field_info.h"
            #include "decode/vulkan_sqlite_prepared_statements.h"

            #include "sqlite3.h"

            #include "sqlite_utils.h"

            #include <string>
            #include <string_view>
            #include <type_traits>

            '''
        )
        write(includes, file=self.outFile)

        namespace = inspect.cleandoc(
            '''
            GFXRECON_BEGIN_NAMESPACE(gfxrecon)
            GFXRECON_BEGIN_NAMESPACE(decode)

            template<typename T>
            void RecordField(VulkanSqlitePreparedStatements &statements, const FieldInfo &fieldInfo, size_t fieldIndex, std::string_view fieldName, std::string_view fieldType, T value)
            {
                statements.RecordField<to_arg_type<T>>(fieldInfo, fieldIndex, fieldName, fieldType, value);
            }

            template<typename T>
            void RecordFieldAsHex(VulkanSqlitePreparedStatements &statements, const FieldInfo &fieldInfo, size_t fieldIndex, std::string_view fieldName, std::string_view fieldType, T value)
            {
                RecordField<std::string_view>(statements, fieldInfo, fieldIndex, fieldName, fieldType, to_hex_variable_width(value));
            }

            template<typename T>
            void RecordFieldAsHexFixedWidth(VulkanSqlitePreparedStatements &statements, const FieldInfo &fieldInfo, size_t fieldIndex, std::string_view fieldName, std::string_view fieldType, T value)
            {
                RecordField<std::string_view>(statements, fieldInfo, fieldIndex, fieldName, fieldType, to_hex_fixed_width(value));
            }

            void RecordEnums(sqlite3* db);

            void CreateEnumTable(sqlite3* db, std::string_view typeName);'''
        )
        write(namespace, file=self.outFile)
    # yapf: enable

    # Method override
    # yapf: disable
    def endFile(self):
        write('\n', file=self.outFile)
        self.make_decls()

        body = inspect.cleandoc('''
            GFXRECON_END_NAMESPACE(decode)
            GFXRECON_END_NAMESPACE(gfxrecon)
            ''')
        write(body, file=self.outFile)

        # Finish processing in superclass
        VulkanBaseGenerator.endFile(self)
    # yapf: enable

    #
    # Indicates that the current feature has C++ code to generate.
    def need_feature_generation(self):
        if self.feature_struct_members:
            return True
        return False

    def genGroup(self, groupinfo, group_name, alias):
        VulkanBaseGenerator.genGroup(self, groupinfo, group_name, alias)
        type_elem = groupinfo.elem
        if type_elem.get('bitwidth') == '64':
            self.enumType[group_name] = 'VkFlags64'
        else:
            self.enumType[group_name] = 'VkFlags'

    def genType(self, typeinfo, name, alias):
        super().genType(typeinfo, name, alias)
        if self.is_flags(name) and alias is None:
            self.flagsType[name] = self.flags_types[name]
            bittype = typeinfo.elem.get('requires')
            if bittype is None:
                bittype = typeinfo.elem.get('bitvalues')
            if bittype is not None:
                self.flagBitsType[bittype] = name

    def make_decls(self):
        for flag in sorted(self.flagsType):
            body = 'struct {0}_t {{ }};'
            write(body.format(flag), file=self.outFile)

        for enum in sorted(self.enum_names):
            if not enum in self.enumAliases:
                if enum in self.enumType and self.enumType[enum] == 'VkFlags64':
                    body = 'struct {0}_t {{ }};'
                    write(body.format(enum), file=self.outFile)

        write('\n', file=self.outFile)
        for enum in sorted(self.enum_names):
            if not enum in self.processedEnums and not enum in self.SKIP_ENUM:
                self.processedEnums.add(enum)
                if not enum in self.enumAliases:
                    if enum in self.enumType and self.enumType[enum] == 'VkFlags64':
                        body = 'void FieldToSqlite(VulkanSqlitePreparedStatements& statements, const FieldInfo& fieldInfo, size_t fieldIndex, std::string_view fieldName, {0}_t, const {0}& value, std::string_view typeName);'
                    else:
                        body = 'void FieldToSqlite(VulkanSqlitePreparedStatements& statements, const FieldInfo& fieldInfo, size_t fieldIndex, std::string_view fieldName, const {0}& value, std::string_view typeName);'
                    write(body.format(enum), file=self.outFile)

        for flag in sorted(self.flagsType):
            body = 'void FieldToSqlite(VulkanSqlitePreparedStatements& statements, const FieldInfo& fieldInfo, size_t fieldIndex, std::string_view fieldName, {0}_t, const {1} flags, std::string_view typeName);'
            write(body.format(flag, self.flagsType[flag]), file=self.outFile)
