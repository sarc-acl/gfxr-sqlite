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

import os, re, sys, inspect, textwrap
from pickle import NONE
from vulkan_base_generator import VulkanBaseGeneratorOptions, VulkanBaseGenerator, write


class VulkanEnumToSqliteBodyGeneratorOptions(VulkanBaseGeneratorOptions):
    """Options for generating C++ functions for Vulkan FieldToSqlite() functions"""

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


# VulkanEnumToSqliteBodyGenerator - subclass of BaseGenerator.
# Generates C++ functions for stringifying Vulkan API enums.
class VulkanEnumToSqliteBodyGenerator(VulkanBaseGenerator):
    """Generate C++ functions for Vulkan FieldToSqlite() functions"""

    SKIP_ENUM = [
    ]

    SKIP_ENUMERANTS = [
        'VK_SHADER_STAGE_ALL_GRAPHICS',
        'VK_SHADER_STAGE_ALL',
        'VK_STRUCTURE_TYPE_NATIVE_BUFFER_OHOS',
        'VK_STRUCTURE_TYPE_SWAPCHAIN_IMAGE_CREATE_INFO_OHOS',
        'VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PRESENTATION_PROPERTIES_OHOS'
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
        self.recordedEnums = set()
        self.processedEnums = set()
        self.enumType = dict()
        self.flagsType = dict()
        self.flagEnumBitsType = dict()
        self.camelCasePattern = re.compile(r'(?<!^)(?=[A-Z])')

    # Method override
    # yapf: disable
    def beginFile(self, genOpts):
        VulkanBaseGenerator.beginFile(self, genOpts)
        body = inspect.cleandoc('''
            #include "generated_vulkan_enum_to_sqlite.h"
            #include "generated_vulkan_struct_to_sqlite.h"

            #include "sqlite_utils.h"
            GFXRECON_BEGIN_NAMESPACE(gfxrecon)
            GFXRECON_BEGIN_NAMESPACE(decode)

            template<typename TFlags, typename ToStringFunctionType>
            std::string ExpandFlags(TFlags flags, ToStringFunctionType toString)
            {
                if (flags == 0)
                {
                    return to_hex_fixed_width(flags);
                }
                uint32_t bit_number = 0;
                bool first = true;
                std::ostringstream ostr;
                while (flags != 0)
                {
                    if (flags & 1)
                    {
                        if (!first) ostr << "|";
                        ostr << toString((flags & 1) << bit_number);
                        first = false;
                    }
                    bit_number++;
                    flags = flags >> 1;
                }
                return ostr.str();
            }

            ''')
        write(body, file=self.outFile)
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
                self.flagEnumBitsType[name] = bittype

    def gen_enum_alias(self, enum, enumerant):
        under_score_enum = self.camelCasePattern.sub('_', enum.replace('AV1', 'Av1')).upper()
        prefix = os.path.commonprefix([under_score_enum, enumerant]).removesuffix('_F')
        alias = (
            enumerant.removeprefix(prefix)
            .removeprefix('_')
            .removesuffix('_KHR_EXT')
            .removesuffix('_KHR')
            .removesuffix('_EXT_EXT')
            .removesuffix('_EXT')
            .removesuffix('_NV')
            .removesuffix('_AMD')
            .removesuffix('_AMDX')
            .removesuffix('_ANDROID')
            .removesuffix('_ARM')
            .removesuffix('_HUAWEI')
            .removesuffix('_FUCHSIA')
            .removesuffix('_QNX')
            .removesuffix('_NVX')
            .removesuffix('_QCOM')
            .removesuffix('_INTEL')
            .removesuffix('_BIT')
            .removesuffix('_SEC')
            .replace('_', ' ')
        )
        if 'FlagBits2' in enum:
            alias = alias.removeprefix('2 ')
        return alias



    #
    # Performs C++ code generation for the feature.
    # yapf: disable
    def make_decls(self):

        body = 'void CreateEnumTable(sqlite3* db, const char* typeName)\n'
        body +='{{\n'
        body +='    auto sql = std::string("CREATE TABLE ") + typeName +\n'
        body +='               "(value INTEGER UNIQUE NOT NULL PRIMARY KEY,"\n'
        body +='               " valueName TEXT NOT NULL,"\n'
        body +='               " aliasName TEXT NOT NULL) STRICT;";\n'
        body +='    ExecSQL(db, sql.c_str());\n'
        body +='}}\n\n'

        body += 'void RecordEnums(sqlite3* db)\n'
        body += '{{\n'
        body += '    CreateEnumTable(db, "VkBool32");\n'
        body += '    {{\n'
        body += '        sqlite3_stmt* stmt = nullptr;\n'
        body += '        sqlite3_prepare_v3(db, "INSERT INTO VkBool32 VALUES (?, ?, ?);", -1, 0, &stmt, nullptr);\n'
        body += '        sqlite3_reset(stmt); sqlite3_bind_int64(stmt, 1, 0); sqlite3_bind_text(stmt, 2, "VK_FALSE", -1, SQLITE_STATIC); sqlite3_bind_text(stmt, 3, "FALSE", -1, SQLITE_STATIC); sqlite3_step(stmt);\n'
        body += '        sqlite3_reset(stmt); sqlite3_bind_int64(stmt, 1, 1); sqlite3_bind_text(stmt, 2, "VK_TRUE", -1, SQLITE_STATIC); sqlite3_bind_text(stmt, 3, "TRUE", -1, SQLITE_STATIC); sqlite3_step(stmt);\n'
        body += '        sqlite3_finalize(stmt);\n'
        body += '    }}\n\n'
        write(body.format(), file=self.outFile)
        for enum in sorted(self.enum_names):
            if not enum in self.recordedEnums and not enum in self.enumAliases and not enum in self.SKIP_ENUM:
                self.recordedEnums.add(enum)
                if len(self.enumEnumerants[enum]):
                    body = '    CreateEnumTable(db, "{0}");\n'
                    body += '    {{\n'
                    body += '        sqlite3_stmt* stmt = nullptr;\n'
                    body += '        sqlite3_prepare_v3(db, "INSERT INTO {0} VALUES (?, ?, ?);", -1, 0, &stmt, nullptr);\n'
                    write(body.format(enum), file=self.outFile)
                    for enumerant in self.enumEnumerants[enum]:
                        if enumerant in self.SKIP_ENUMERANTS:
                            continue
                        alias = self.gen_enum_alias(enum, enumerant)
                        body = '        sqlite3_reset(stmt); sqlite3_bind_int64(stmt, 1, static_cast<sqlite3_int64>({0})); sqlite3_bind_text(stmt, 2, "{0}", -1, SQLITE_STATIC); sqlite3_bind_text(stmt, 3, "{1}", -1, SQLITE_STATIC); sqlite3_step(stmt);'
                        write(body.format(enumerant, alias), file=self.outFile)
                    body = '        sqlite3_finalize(stmt);\n'
                    body += '    }}\n'
                    write(body.format(enum), file=self.outFile)
        body = '}}\n'
        write(body.format(), file=self.outFile)

        for enum in sorted(self.enum_names):
            if not enum in self.processedEnums and not enum in self.enumAliases and not enum in self.SKIP_ENUM and not enum in self.flagEnumBitsType:
                self.processedEnums.add(enum)
                bitwidth = 'VkFlags'

                if enum in self.enumType and self.enumType[enum] == 'VkFlags64':
                    body = 'void FieldToSqlite(VulkanSqlitePreparedStatements& statements, const FieldInfo &fieldInfo, size_t fieldIndex, std::string_view fieldName, {0}_t, const {0}& value, std::string_view typeName)\n'
                else:
                    body = 'void FieldToSqlite(VulkanSqlitePreparedStatements& statements, const FieldInfo &fieldInfo, size_t fieldIndex, std::string_view fieldName, const {0}& value, std::string_view typeName)\n'
                body += '{{\n'
                if len(self.enumEnumerants[enum]):
                    body += '    switch (value) {{\n'
                    for enumerant in self.enumEnumerants[enum]:
                        body += textwrap.indent(prefix='        ', text=textwrap.dedent('''\
                        case {0}:
                            RecordField<std::string_view>(statements, fieldInfo, fieldIndex, fieldName, "{1}", "{0}");
                            break;
                        '''.format(enumerant, enum)))
                    body += '        default:\n'
                    body += '            RecordFieldAsHexFixedWidth<{0}>(statements, fieldInfo, fieldIndex, fieldName, "{0}", value);\n'
                    body += '            break;\n'
                    body += '    }}\n'
                else:
                    body += '    RecordFieldAsHexFixedWidth<{0}>(statements, fieldInfo, fieldIndex, fieldName, "{0}", value);\n'

                body += '}}\n'
                write(body.format(enum, bitwidth), file=self.outFile)

        for enum in sorted(self.flagsType):
            bittype = None
            if enum in self.flagEnumBitsType:
                bittype = self.flagEnumBitsType[enum]
            body = 'void FieldToSqlite(VulkanSqlitePreparedStatements& statements, const FieldInfo &fieldInfo, size_t fieldIndex, std::string_view fieldName, {0}_t, const {1} flags, std::string_view typeName)\n'
            body += '{{\n'
            if bittype is not None and bittype in self.enum_names and len(self.enumEnumerants[bittype]):
                # TODO possibly support expanded flags, removed due to json options being removed
                body += '    RecordFieldAsHexFixedWidth<{0}>(statements, fieldInfo, fieldIndex, fieldName, typeName, flags);\n'
                # body += '    if (!options.expand_flags)\n'
                # body += '    {{\n'
                # body += '        RecordFieldAsHexFixedWidth<{0}>(statements, fieldInfo, fieldIndex, fieldName, "{0}", flags);\n'
                # body += '        return;\n'
                # body += '    }}\n'
                # body += '    auto expandedFlags = ExpandFlags(flags, []({1} flags)\n'
                # body += '    {{\n'
                # body += '        switch (flags)\n'
                # body += '        {{\n'
                # for enumerant in self.enumEnumerants[bittype]:
                #     body += textwrap.indent(prefix='            ', text=textwrap.dedent('''\
                #     case {0}:
                #         return std::string("{0}");
                #     '''.format(enumerant)))
                # body += '        }}\n'
                # body += '        return to_hex_fixed_width(flags);\n'
                # body += '    }});\n'
                # body += '    RecordFieldAsHexFixedWidth<{0}>(statements, fieldInfo, fieldIndex, fieldName, "{0}", expandedFlags);\n'
            else:
                body += '    RecordFieldAsHexFixedWidth<{0}>(statements, fieldInfo, fieldIndex, fieldName, typeName, flags);\n'

            body += '}}\n'
            write(body.format(enum, self.flags_types[enum]), file=self.outFile)

    # yapf: enable
