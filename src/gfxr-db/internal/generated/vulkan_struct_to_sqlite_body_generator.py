#!/usr/bin/python3 -i
#
# Copyright (c) 2022-2023 LunarG, Inc.
# Copyright (c) 2024 The Sokatoa Authors
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

import os
import re
import sys
import inspect
import textwrap
from vulkan_base_generator import VulkanBaseGeneratorOptions, VulkanBaseGenerator, write


class VulkanStructToSqliteBodyGeneratorOptions(VulkanBaseGeneratorOptions):
    """Options for generating C++ functions for serializing Vulkan structures to Sqlite"""

    def __init__(
        self,
        # Path to JSON file listing apicalls and structs to ignore.
        blacklists=None,
        # Path to JSON file listing platform (WIN32, X11, etc.) defined types.
        platform_types=None,
        filename=None,
        directory='.',
        prefix_text=[],
        protect_file=False,
        protect_feature=True,
        extra_headers=[]
    ):
        VulkanBaseGeneratorOptions.__init__(
            self,
            blacklists,
            platform_types,
            filename,
            directory,
            prefix_text,
            protect_file,
            protect_feature,
            extra_headers=extra_headers
        )


# VulkanStructToSqliteBodyGenerator - subclass of BaseGenerator.
# Generates C++ functions for serializing Vulkan API structures to Sqlite.
class VulkanStructToSqliteBodyGenerator(VulkanBaseGenerator):
    """Generate C++ functions for Vulkan FieldToSqlite(...) functions"""

    def __init__(
        self, err_file=sys.stderr, warn_file=sys.stderr, diag_file=sys.stdout
    ):
        VulkanBaseGenerator.__init__(
            self,
            err_file=err_file,
            warn_file=warn_file,
            diag_file=diag_file
        )

        # The following structures require custom implementations for FieldToSqlite()
        self.customImplementationRequired = {
            'VkPipelineCacheCreateInfo',
            'VkShaderModuleCreateInfo',
            'VkPipelineExecutableStatisticKHR',
        }

        self.formatAsHex = {
            'VkDeviceAddress',
        }

        # Fields using this name should be output as handles even though they are uint64_t
        self.formatAsHandle = {
            'objectHandle',
        }

        # Struct types here do not have decoded fields.
        self.notDecoded = {
            'VkDeviceMemoryReportCallbackDataEXT',
        }

        self.pnext_extension_structs = dict()
        self.flagsType = dict()
        self.flagsTypeAlias = dict()
        self.flagEnumBitsType = dict()

    # Method override
    # yapf: disable
    def beginFile(self, genOpts):
        VulkanBaseGenerator.beginFile(self, genOpts)
        body = inspect.cleandoc('''
            #include "generated_vulkan_struct_to_sqlite.h"
            #include "generated_vulkan_enum_to_sqlite.h"

            #include "sqlite_utils.h"

            GFXRECON_BEGIN_NAMESPACE(gfxrecon)
            GFXRECON_BEGIN_NAMESPACE(decode)
            ''')
        write(body, file=self.outFile)
    # yapf: enable

    # Method override
    # yapf: disable
    def endFile(self):
        body = "\n"
        body += inspect.cleandoc('''
                static constexpr std::string_view pNextName = "pNext";
            ''')
        body += self.make_pnext_funcs()
        body += "\n\n"
        body += inspect.cleandoc('''
                void FieldToSqlite(VulkanSqlitePreparedStatements& statements, const FieldInfo& fieldInfo, size_t fieldIndex, std::string_view fieldName, const PNextNode* data)
                {
                    if (data && data->GetPointer())
                    {
                        const auto s_type = reinterpret_cast<const VkBaseInStructure*>(data->GetPointer())->sType;
                        switch (s_type)
                        {
            ''')
        body += "\n"
        body += self.make_pnext_body()
        body += "\n"
        body += inspect.cleandoc('''
                            default:
                                GFXRECON_SQLITE_LOG_WARNING_AT(fieldInfo.eventId, "Unknown pnext node type: %u.", (unsigned) s_type);
                        }
                    }
                }
            ''')
        body += "\n"
        body += inspect.cleandoc('''
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

    #
    # Performs C++ code generation for the feature.
    # yapf: disable
    def generate_feature(self):
        for struct in self.get_filtered_struct_names():
            if not struct in self.customImplementationRequired:
                body = inspect.cleandoc('''
                    void FieldToSqlite(VulkanSqlitePreparedStatements& statements, const FieldInfo& fieldInfo, size_t fieldIndex, std::string_view fieldName, const Decoded_{0}* data, std::string_view typeName)
                    {{
                        const uint64_t structId = RecordStruct(statements, fieldInfo, fieldIndex, fieldName, typeName);
                        if (data && data->decoded_value)
                        {{
                            [[maybe_unused]] const {0}& decoded_value = *data->decoded_value;
                            [[maybe_unused]] const Decoded_{0}& meta_struct = *data;
                            FieldInfo memberInfo = {{.eventId = fieldInfo.eventId, .structId = structId, .arrayId = 0, .arrayIndex = 0}};
                    '''.format(struct))
                body += '\n'
                body += self.makeStructBody(struct,
                                            self.feature_struct_members[struct])
                body += inspect.cleandoc('''
                        }}
                    }}
                    '''.format(struct))
                body += '\n'
                write(body, file=self.outFile)
    # yapf: enable

    #
    # Command definition
    # yapf: disable
    def makeStructBody(self, name, values):
        body = ''
        has_pnext = False
        fieldIndex = 1
        for value in values:
            type_name = self.make_decoded_param_type(value)
            flagsEnumType = value.base_type

            if value.name == 'pNext':
                # move pnext to be the last member
                has_pnext = True
                continue

            # Default to getting the data from the native Vulkan struct:
            to_sqlite = 'FieldToSqlite(statements, memberInfo, {4}, "{0}", decoded_value.{0}, "{3}")'

            if 'pfn' in value.name or 'pUserData' in value.name:
                to_sqlite = 'RecordFieldAsHex(statements, memberInfo, {4}, "{0}", "{3}", meta_struct.{0})'
            elif value.is_pointer:
                if 'String' in type_name:
                    to_sqlite = 'FieldToSqlite(statements, memberInfo, {4}, "{0}", &meta_struct.{0}, "{3}")'
                elif self.is_handle(value.base_type):
                    to_sqlite = 'HandleToSqlite(statements, memberInfo, {4}, "{0}", &meta_struct.{0}, "{3}")'
                else:
                    to_sqlite = 'FieldToSqlite(statements, memberInfo, {4}, "{0}", meta_struct.{0}, "{3}")'
            else:
                if value.is_array:
                    if 'UUID' in value.array_length or 'LUID' in value.array_length:
                        to_sqlite = 'FieldToSqlite(statements, memberInfo, {4}, "{0}", uuid_to_string(sizeof(decoded_value.{0}), decoded_value.{0}), "{3}")'
                    elif 'String' in type_name:
                        to_sqlite = 'FieldToSqlite(statements, memberInfo, {4}, "{0}", &meta_struct.{0}, "{3}")'
                    elif self.is_handle(value.base_type):
                        to_sqlite = 'HandleToSqlite(statements, memberInfo, {4}, "{0}", &meta_struct.{0}, "{3}")'
                    elif self.is_struct(value.base_type):
                        to_sqlite = 'FieldToSqlite(statements, memberInfo, {4}, "{0}", meta_struct.{0}, "{3}")'
                    elif not value.is_dynamic:
                        to_sqlite = 'FieldToSqlite(statements, memberInfo, {4}, "{0}", &meta_struct.{0}, "{3}")'
                    else:
                        to_sqlite = 'FieldToSqlite(statements, memberInfo, {4}, "{0}", meta_struct.{0}, "{3}")'
                else:
                    if (self.is_handle(value.base_type) or value.name in self.formatAsHandle) and not (name in self.notDecoded):
                        to_sqlite = 'HandleToSqlite(statements, memberInfo, {4}, "{0}", meta_struct.{0}, "{3}")'
                    elif value.base_type in self.formatAsHex:
                        to_sqlite = 'RecordFieldAsHex(statements, memberInfo, {4}, "{0}", "{3}", decoded_value.{0})'
                    elif self.is_struct(value.base_type):
                        to_sqlite = 'FieldToSqlite(statements, memberInfo, {4}, "{0}", meta_struct.{0}, "{3}")'
                    elif self.is_flags(value.base_type):
                        if value.base_type in self.flagsTypeAlias:
                            flagsEnumType = self.flagsTypeAlias[value.base_type]
                        to_sqlite = 'FieldToSqlite(statements, memberInfo, {4}, "{0}", {2}_t(), decoded_value.{0}, "{3}")'
                    elif self.is_enum(value.base_type):
                        to_sqlite = 'FieldToSqlite(statements, memberInfo, {4}, "{0}", decoded_value.{0}, "{3}")'
                    elif 'VkBool32' == value.base_type:
                        to_sqlite = 'FieldToSqlite(statements, memberInfo, {4}, "{0}", static_cast<bool>(decoded_value.{0}), "{3}")'

            full_type_name = value.platform_full_type
            if full_type_name == None:
                full_type_name = value.full_type
            to_sqlite = to_sqlite.format(
                value.name, value.base_type, flagsEnumType, full_type_name, fieldIndex)
            fieldIndex += 1
            body += '        {0};\n'.format(to_sqlite)
        # Save pnext as last member
        if has_pnext:
            body += f'        FieldToSqlite(statements, memberInfo, {fieldIndex}, "pNext", meta_struct.pNext);\n'

        return body
    # yapf: enable

    def genStruct(self, typeinfo, typename, alias):
        super().genStruct(typeinfo, typename, alias)

        if not alias:
            if typeinfo.elem.get('structextends'):
                pnext_extension_struct = self.make_structure_type_enum(
                    typeinfo, typename)
                if pnext_extension_struct:
                    self.pnext_extension_structs[typename] = pnext_extension_struct

    def genType(self, typeinfo, name, alias):
        super().genType(typeinfo, name, alias)
        if self.is_flags(name):
            if alias is None:
                self.flagsType[name] = self.flags_types[name]
                bittype = typeinfo.elem.get('requires')
                if bittype is None:
                    bittype = typeinfo.elem.get('bitvalues')
                if bittype is not None:
                    self.flagEnumBitsType[bittype] = name
            else:
                self.flagsTypeAlias[name] = alias

    def make_pnext_body(self):
        body = ''
        for struct in self.pnext_extension_structs:
            body += '\n'
            body += textwrap.indent(prefix='            ', text=inspect.cleandoc(
                    '''case {1}: {{ InsertPNext_{0}(statements, fieldInfo, fieldIndex, fieldName, data); break; }}'''
                ).format(struct, self.pnext_extension_structs[struct]))
        return body

    def make_pnext_funcs(self):
        body = ''
        for struct in self.pnext_extension_structs:
            body += '\n\n'
            # note that we intentionally use a const std::string_view& argument here to avoid stack allocations in the large switch case statement
            # that these are called from. This is not the typical pattern for string_view usage but nothing in this function modifies the
            # underlying string data so we should be ok.
            body += inspect.cleandoc('''
            void InsertPNext_{0}(VulkanSqlitePreparedStatements& statements, const FieldInfo& fieldInfo, size_t fieldIndex, const std::string_view& fieldName, const PNextNode* data)
            {{
                static constexpr std::string_view name = "{0}";

                // generate the structMembers entries
                const uint64_t structId = RecordStruct(statements, fieldInfo, fieldIndex, fieldName, name);
                const auto* pnext = reinterpret_cast<const Decoded_{0}*>(data->GetMetaStructPointer());
                FieldInfo memberInfo = {{ .eventId = fieldInfo.eventId, .structId = structId, .arrayId = 0, .arrayIndex = 0 }};
                FieldToSqlite(statements, memberInfo, fieldIndex, pNextName, pnext, name);
            }}
            ''').format(struct, self.pnext_extension_structs[struct])
        return body
