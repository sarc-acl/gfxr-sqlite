#!/usr/bin/python3 -i
#
# Copyright (c) 2022-2023 LunarG, Inc.
# Copyright (c) 2025-2026 The Sokatoa Authors
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


class VulkanProcessFeaturesBodyGeneratorOptions(VulkanBaseGeneratorOptions):
    """Options for generating C++ functions for processing feature structs"""

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


# VulkanProcessFeaturesBodyGenerator - subclass of BaseGenerator.
# Generates C++ functions for processing Vulkan API feature structures.
class VulkanProcessFeaturesBodyGenerator(VulkanBaseGenerator):
    """Generate C++ process feature function for Vulkan feature structs"""

    def __init__(
        self, err_file=sys.stderr, warn_file=sys.stderr, diag_file=sys.stdout
    ):
        VulkanBaseGenerator.__init__(
            self,
            err_file=err_file,
            warn_file=warn_file,
            diag_file=diag_file
        )

    # Method override
    # yapf: disable
    def beginFile(self, genOpts):
        VulkanBaseGenerator.beginFile(self, genOpts)
        body = inspect.cleandoc('''
            #include "decode/vulkan_sqlite_consumer_ext.h"

            GFXRECON_BEGIN_NAMESPACE(gfxrecon)
            GFXRECON_BEGIN_NAMESPACE(decode)

            void VulkanSqliteConsumerExt::ProcessVkPhysicalDeviceFeatures(
                VkPhysicalDeviceFeatures* deviceFeatures, std::vector<std::string_view>& enabledFeatureNames
            )
            {
                // clang-format off
                if(deviceFeatures->robustBufferAccess) { enabledFeatureNames.emplace_back("robustBufferAccess"); }
                if(deviceFeatures->fullDrawIndexUint32) { enabledFeatureNames.emplace_back("fullDrawIndexUint32"); }
                if(deviceFeatures->imageCubeArray) { enabledFeatureNames.emplace_back("imageCubeArray"); }
                if(deviceFeatures->independentBlend) { enabledFeatureNames.emplace_back("independentBlend"); }
                if(deviceFeatures->geometryShader) { enabledFeatureNames.emplace_back("geometryShader"); }
                if(deviceFeatures->tessellationShader) { enabledFeatureNames.emplace_back("tessellationShader"); }
                if(deviceFeatures->sampleRateShading) { enabledFeatureNames.emplace_back("sampleRateShading"); }
                if(deviceFeatures->dualSrcBlend) { enabledFeatureNames.emplace_back("dualSrcBlend"); }
                if(deviceFeatures->logicOp) { enabledFeatureNames.emplace_back("logicOp"); }
                if(deviceFeatures->multiDrawIndirect) { enabledFeatureNames.emplace_back("multiDrawIndirect"); }
                if(deviceFeatures->drawIndirectFirstInstance) { enabledFeatureNames.emplace_back("drawIndirectFirstInstance"); }
                if(deviceFeatures->depthClamp) { enabledFeatureNames.emplace_back("depthClamp"); }
                if(deviceFeatures->depthBiasClamp) { enabledFeatureNames.emplace_back("depthBiasClamp"); }
                if(deviceFeatures->fillModeNonSolid) { enabledFeatureNames.emplace_back("fillModeNonSolid"); }
                if(deviceFeatures->depthBounds) { enabledFeatureNames.emplace_back("depthBounds"); }
                if(deviceFeatures->wideLines) { enabledFeatureNames.emplace_back("wideLines"); }
                if(deviceFeatures->largePoints) { enabledFeatureNames.emplace_back("largePoints"); }
                if(deviceFeatures->alphaToOne) { enabledFeatureNames.emplace_back("alphaToOne"); }
                if(deviceFeatures->multiViewport) { enabledFeatureNames.emplace_back("multiViewport"); }
                if(deviceFeatures->samplerAnisotropy) { enabledFeatureNames.emplace_back("samplerAnisotropy"); }
                if(deviceFeatures->textureCompressionETC2) { enabledFeatureNames.emplace_back("textureCompressionETC2"); }
                if(deviceFeatures->textureCompressionASTC_LDR) { enabledFeatureNames.emplace_back("textureCompressionASTC_LDR"); }
                if(deviceFeatures->textureCompressionBC) { enabledFeatureNames.emplace_back("textureCompressionBC"); }
                if(deviceFeatures->occlusionQueryPrecise) { enabledFeatureNames.emplace_back("occlusionQueryPrecise"); }
                if(deviceFeatures->pipelineStatisticsQuery) { enabledFeatureNames.emplace_back("pipelineStatisticsQuery"); }
                if(deviceFeatures->vertexPipelineStoresAndAtomics) { enabledFeatureNames.emplace_back("vertexPipelineStoresAndAtomics"); }
                if(deviceFeatures->fragmentStoresAndAtomics) { enabledFeatureNames.emplace_back("fragmentStoresAndAtomics"); }
                if(deviceFeatures->shaderTessellationAndGeometryPointSize) { enabledFeatureNames.emplace_back("shaderTessellationAndGeometryPointSize"); }
                if(deviceFeatures->shaderImageGatherExtended) { enabledFeatureNames.emplace_back("shaderImageGatherExtended"); }
                if(deviceFeatures->shaderStorageImageExtendedFormats) { enabledFeatureNames.emplace_back("shaderStorageImageExtendedFormats"); }
                if(deviceFeatures->shaderStorageImageMultisample) { enabledFeatureNames.emplace_back("shaderStorageImageMultisample"); }
                if(deviceFeatures->shaderStorageImageReadWithoutFormat) { enabledFeatureNames.emplace_back("shaderStorageImageReadWithoutFormat"); }
                if(deviceFeatures->shaderStorageImageWriteWithoutFormat) { enabledFeatureNames.emplace_back("shaderStorageImageWriteWithoutFormat"); }
                if(deviceFeatures->shaderUniformBufferArrayDynamicIndexing) { enabledFeatureNames.emplace_back("shaderUniformBufferArrayDynamicIndexing"); }
                if(deviceFeatures->shaderSampledImageArrayDynamicIndexing) { enabledFeatureNames.emplace_back("shaderSampledImageArrayDynamicIndexing"); }
                if(deviceFeatures->shaderStorageBufferArrayDynamicIndexing) { enabledFeatureNames.emplace_back("shaderStorageBufferArrayDynamicIndexing"); }
                if(deviceFeatures->shaderStorageImageArrayDynamicIndexing) { enabledFeatureNames.emplace_back("shaderStorageImageArrayDynamicIndexing"); }
                if(deviceFeatures->shaderClipDistance) { enabledFeatureNames.emplace_back("shaderClipDistance"); }
                if(deviceFeatures->shaderCullDistance) { enabledFeatureNames.emplace_back("shaderCullDistance"); }
                if(deviceFeatures->shaderFloat64) { enabledFeatureNames.emplace_back("shaderFloat64"); }
                if(deviceFeatures->shaderInt64) { enabledFeatureNames.emplace_back("shaderInt64"); }
                if(deviceFeatures->shaderInt16) { enabledFeatureNames.emplace_back("shaderInt16"); }
                if(deviceFeatures->shaderResourceResidency) { enabledFeatureNames.emplace_back("shaderResourceResidency"); }
                if(deviceFeatures->shaderResourceMinLod) { enabledFeatureNames.emplace_back("shaderResourceMinLod"); }
                if(deviceFeatures->sparseBinding) { enabledFeatureNames.emplace_back("sparseBinding"); }
                if(deviceFeatures->sparseResidencyBuffer) { enabledFeatureNames.emplace_back("sparseResidencyBuffer"); }
                if(deviceFeatures->sparseResidencyImage2D) { enabledFeatureNames.emplace_back("sparseResidencyImage2D"); }
                if(deviceFeatures->sparseResidencyImage3D) { enabledFeatureNames.emplace_back("sparseResidencyImage3D"); }
                if(deviceFeatures->sparseResidency2Samples) { enabledFeatureNames.emplace_back("sparseResidency2Samples"); }
                if(deviceFeatures->sparseResidency4Samples) { enabledFeatureNames.emplace_back("sparseResidency4Samples"); }
                if(deviceFeatures->sparseResidency8Samples) { enabledFeatureNames.emplace_back("sparseResidency8Samples"); }
                if(deviceFeatures->sparseResidency16Samples) { enabledFeatureNames.emplace_back("sparseResidency16Samples"); }
                if(deviceFeatures->sparseResidencyAliased) { enabledFeatureNames.emplace_back("sparseResidencyAliased"); }
                if(deviceFeatures->variableMultisampleRate) { enabledFeatureNames.emplace_back("variableMultisampleRate"); }
                if(deviceFeatures->inheritedQueries) { enabledFeatureNames.emplace_back("inheritedQueries"); }
                // clang-format on
            }

            void VulkanSqliteConsumerExt::ProcessVkDeviceCreateInfoPNext(
                PNextNode* pNext, std::vector<std::string_view>& enabledFeatureNames
            )
            {
                auto* pnext = pNext;
                while (pnext != nullptr)
                {
                    auto header = reinterpret_cast<const VulkanMetaStructHeader*>(pnext->GetMetaStructPointer());
                    switch(*header->sType)
                    {
                        case gfxrecon::util::GetSType<VkPhysicalDeviceFeatures2>():
                        {
                            const auto* pPhysicalDeviceFeatures2 =
                                reinterpret_cast<const Decoded_VkPhysicalDeviceFeatures2*>(header);
                            ProcessVkPhysicalDeviceFeatures(pPhysicalDeviceFeatures2->features->decoded_value, enabledFeatureNames);
                            pnext = header->pNext;
                            break;
                        }
            ''')
        write(body, file=self.outFile)
    # yapf: enable

    # Method override
    # yapf: disable
    def endFile(self):
        body = inspect.cleandoc('''
                        default:
                        {
                            LogUnsupportedPNext(*header->sType);
                            break;
                        }
                    }
                    pnext = header->pNext;
                }
            }

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
            if 'VkPhysicalDevice' in struct and 'Features' in struct:
                if 'VkPhysicalDeviceFeatures' == struct or 'VkPhysicalDeviceFeatures2' == struct:
                    # special handling of this in beginFile
                    continue

                body = textwrap.indent(prefix='            ', text=inspect.cleandoc('''
                    case gfxrecon::util::GetSType<{0}>():
                    {{
                        // clang-format off
                        const auto* pFeatures = reinterpret_cast<const {0}*>(header);
                    '''.format(struct)))
                body += '\n'
                body += self.makeStructBody(struct,
                                            self.feature_struct_members[struct])
                body += textwrap.indent(prefix='            ', text=inspect.cleandoc('''
                        // clang-format on
                        break;
                    }
                    '''))
                write(body, file=self.outFile)
    # yapf: enable

    #
    # Command definition
    # yapf: disable
    def makeStructBody(self, name, values):
        body = ''
        for value in values:
            if value.name == 'sType':
                # skip sType field
                continue
            if value.name == 'pNext':
                # skip pNext fields
                continue

            body += textwrap.indent(prefix='                ', text=inspect.cleandoc('''
                if(pFeatures->{0}) {{ enabledFeatureNames.emplace_back("{0}"); }}
            '''.format(value.name)))
            body += '\n'
        return body
    # yapf: enable
