/********************************************************************************
    Copyright 2024-2026 The Sokatoa Project Authors

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        https://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
********************************************************************************/

/*
** This file is generated from the Khronos Vulkan XML API Registry.
**
*/

#ifndef  GFXRECON_GENERATED_VULKAN_ENUM_FROM_STRING_H
#define  GFXRECON_GENERATED_VULKAN_ENUM_FROM_STRING_H

#include "vulkan/vulkan.h"
#include "vk_video/vulkan_video_codec_h264std.h"
#include "vk_video/vulkan_video_codec_h264std_decode.h"
#include "vk_video/vulkan_video_codec_h264std_encode.h"
#include "vk_video/vulkan_video_codec_h265std.h"
#include "vk_video/vulkan_video_codec_h265std_decode.h"
#include "vk_video/vulkan_video_codec_h265std_encode.h"
#include "vk_video/vulkan_video_codecs_common.h"

#include "format/platform_types.h"

#include <string_view>

GFXRECON_BEGIN_NAMESPACE(gfxrecon)
GFXRECON_BEGIN_NAMESPACE(decode)

/** Resolves an enumerant spelling to its value, returning false for an unknown name.
 *
 * Alias spellings are included, so both VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2
 * and its _KHR spelling resolve, whichever one the layer happened to print.
 */

bool EnumFromString_StdVideoAV1ChromaSamplePosition(std::string_view name, StdVideoAV1ChromaSamplePosition& out);
bool EnumFromString_StdVideoAV1ColorPrimaries(std::string_view name, StdVideoAV1ColorPrimaries& out);
bool EnumFromString_StdVideoAV1FrameRestorationType(std::string_view name, StdVideoAV1FrameRestorationType& out);
bool EnumFromString_StdVideoAV1FrameType(std::string_view name, StdVideoAV1FrameType& out);
bool EnumFromString_StdVideoAV1InterpolationFilter(std::string_view name, StdVideoAV1InterpolationFilter& out);
bool EnumFromString_StdVideoAV1Level(std::string_view name, StdVideoAV1Level& out);
bool EnumFromString_StdVideoAV1MatrixCoefficients(std::string_view name, StdVideoAV1MatrixCoefficients& out);
bool EnumFromString_StdVideoAV1Profile(std::string_view name, StdVideoAV1Profile& out);
bool EnumFromString_StdVideoAV1ReferenceName(std::string_view name, StdVideoAV1ReferenceName& out);
bool EnumFromString_StdVideoAV1TransferCharacteristics(std::string_view name, StdVideoAV1TransferCharacteristics& out);
bool EnumFromString_StdVideoAV1TxMode(std::string_view name, StdVideoAV1TxMode& out);
bool EnumFromString_StdVideoDecodeH264FieldOrderCount(std::string_view name, StdVideoDecodeH264FieldOrderCount& out);
bool EnumFromString_StdVideoH264AspectRatioIdc(std::string_view name, StdVideoH264AspectRatioIdc& out);
bool EnumFromString_StdVideoH264CabacInitIdc(std::string_view name, StdVideoH264CabacInitIdc& out);
bool EnumFromString_StdVideoH264ChromaFormatIdc(std::string_view name, StdVideoH264ChromaFormatIdc& out);
bool EnumFromString_StdVideoH264DisableDeblockingFilterIdc(std::string_view name, StdVideoH264DisableDeblockingFilterIdc& out);
bool EnumFromString_StdVideoH264LevelIdc(std::string_view name, StdVideoH264LevelIdc& out);
bool EnumFromString_StdVideoH264MemMgmtControlOp(std::string_view name, StdVideoH264MemMgmtControlOp& out);
bool EnumFromString_StdVideoH264ModificationOfPicNumsIdc(std::string_view name, StdVideoH264ModificationOfPicNumsIdc& out);
bool EnumFromString_StdVideoH264NonVclNaluType(std::string_view name, StdVideoH264NonVclNaluType& out);
bool EnumFromString_StdVideoH264PictureType(std::string_view name, StdVideoH264PictureType& out);
bool EnumFromString_StdVideoH264PocType(std::string_view name, StdVideoH264PocType& out);
bool EnumFromString_StdVideoH264ProfileIdc(std::string_view name, StdVideoH264ProfileIdc& out);
bool EnumFromString_StdVideoH264SliceType(std::string_view name, StdVideoH264SliceType& out);
bool EnumFromString_StdVideoH264WeightedBipredIdc(std::string_view name, StdVideoH264WeightedBipredIdc& out);
bool EnumFromString_StdVideoVP9ColorSpace(std::string_view name, StdVideoVP9ColorSpace& out);
bool EnumFromString_StdVideoVP9FrameType(std::string_view name, StdVideoVP9FrameType& out);
bool EnumFromString_StdVideoVP9InterpolationFilter(std::string_view name, StdVideoVP9InterpolationFilter& out);
bool EnumFromString_StdVideoVP9Level(std::string_view name, StdVideoVP9Level& out);
bool EnumFromString_StdVideoVP9Profile(std::string_view name, StdVideoVP9Profile& out);
bool EnumFromString_StdVideoVP9ReferenceName(std::string_view name, StdVideoVP9ReferenceName& out);
bool EnumFromString_VkAccelerationStructureBuildTypeKHR(std::string_view name, VkAccelerationStructureBuildTypeKHR& out);
bool EnumFromString_VkAccelerationStructureCompatibilityKHR(std::string_view name, VkAccelerationStructureCompatibilityKHR& out);
bool EnumFromString_VkAccelerationStructureCreateFlagBitsKHR(std::string_view name, VkAccelerationStructureCreateFlagBitsKHR& out);
bool EnumFromString_VkAccelerationStructureMemoryRequirementsTypeNV(std::string_view name, VkAccelerationStructureMemoryRequirementsTypeNV& out);
bool EnumFromString_VkAccelerationStructureMotionInstanceTypeNV(std::string_view name, VkAccelerationStructureMotionInstanceTypeNV& out);
bool EnumFromString_VkAccelerationStructureSerializedBlockTypeKHR(std::string_view name, VkAccelerationStructureSerializedBlockTypeKHR& out);
bool EnumFromString_VkAccelerationStructureTypeKHR(std::string_view name, VkAccelerationStructureTypeKHR& out);
bool EnumFromString_VkAccessFlagBits(std::string_view name, VkAccessFlagBits& out);
bool EnumFromString_VkAccessFlagBits2(std::string_view name, VkAccessFlagBits2& out);
bool EnumFromString_VkAccessFlagBits3KHR(std::string_view name, VkAccessFlagBits3KHR& out);
bool EnumFromString_VkAcquireProfilingLockFlagBitsKHR(std::string_view name, VkAcquireProfilingLockFlagBitsKHR& out);
bool EnumFromString_VkAddressCommandFlagBitsKHR(std::string_view name, VkAddressCommandFlagBitsKHR& out);
bool EnumFromString_VkAddressCopyFlagBitsKHR(std::string_view name, VkAddressCopyFlagBitsKHR& out);
bool EnumFromString_VkAntiLagModeAMD(std::string_view name, VkAntiLagModeAMD& out);
bool EnumFromString_VkAntiLagStageAMD(std::string_view name, VkAntiLagStageAMD& out);
bool EnumFromString_VkAttachmentDescriptionFlagBits(std::string_view name, VkAttachmentDescriptionFlagBits& out);
bool EnumFromString_VkAttachmentLoadOp(std::string_view name, VkAttachmentLoadOp& out);
bool EnumFromString_VkAttachmentStoreOp(std::string_view name, VkAttachmentStoreOp& out);
bool EnumFromString_VkBlendFactor(std::string_view name, VkBlendFactor& out);
bool EnumFromString_VkBlendOp(std::string_view name, VkBlendOp& out);
bool EnumFromString_VkBlendOverlapEXT(std::string_view name, VkBlendOverlapEXT& out);
bool EnumFromString_VkBlockMatchWindowCompareModeQCOM(std::string_view name, VkBlockMatchWindowCompareModeQCOM& out);
bool EnumFromString_VkBorderColor(std::string_view name, VkBorderColor& out);
bool EnumFromString_VkBufferCreateFlagBits(std::string_view name, VkBufferCreateFlagBits& out);
bool EnumFromString_VkBufferUsageFlagBits(std::string_view name, VkBufferUsageFlagBits& out);
bool EnumFromString_VkBufferUsageFlagBits2(std::string_view name, VkBufferUsageFlagBits2& out);
bool EnumFromString_VkBuildAccelerationStructureFlagBitsKHR(std::string_view name, VkBuildAccelerationStructureFlagBitsKHR& out);
bool EnumFromString_VkBuildAccelerationStructureModeKHR(std::string_view name, VkBuildAccelerationStructureModeKHR& out);
bool EnumFromString_VkBuildMicromapFlagBitsEXT(std::string_view name, VkBuildMicromapFlagBitsEXT& out);
bool EnumFromString_VkBuildMicromapModeEXT(std::string_view name, VkBuildMicromapModeEXT& out);
bool EnumFromString_VkChromaLocation(std::string_view name, VkChromaLocation& out);
bool EnumFromString_VkCoarseSampleOrderTypeNV(std::string_view name, VkCoarseSampleOrderTypeNV& out);
bool EnumFromString_VkColorComponentFlagBits(std::string_view name, VkColorComponentFlagBits& out);
bool EnumFromString_VkColorSpaceKHR(std::string_view name, VkColorSpaceKHR& out);
bool EnumFromString_VkCommandBufferLevel(std::string_view name, VkCommandBufferLevel& out);
bool EnumFromString_VkCommandBufferResetFlagBits(std::string_view name, VkCommandBufferResetFlagBits& out);
bool EnumFromString_VkCommandBufferUsageFlagBits(std::string_view name, VkCommandBufferUsageFlagBits& out);
bool EnumFromString_VkCommandPoolCreateFlagBits(std::string_view name, VkCommandPoolCreateFlagBits& out);
bool EnumFromString_VkCommandPoolResetFlagBits(std::string_view name, VkCommandPoolResetFlagBits& out);
bool EnumFromString_VkCompareOp(std::string_view name, VkCompareOp& out);
bool EnumFromString_VkComponentSwizzle(std::string_view name, VkComponentSwizzle& out);
bool EnumFromString_VkComponentTypeKHR(std::string_view name, VkComponentTypeKHR& out);
bool EnumFromString_VkCompositeAlphaFlagBitsKHR(std::string_view name, VkCompositeAlphaFlagBitsKHR& out);
bool EnumFromString_VkConditionalRenderingFlagBitsEXT(std::string_view name, VkConditionalRenderingFlagBitsEXT& out);
bool EnumFromString_VkConservativeRasterizationModeEXT(std::string_view name, VkConservativeRasterizationModeEXT& out);
bool EnumFromString_VkCooperativeMatrixFlagBitsEXT(std::string_view name, VkCooperativeMatrixFlagBitsEXT& out);
bool EnumFromString_VkCooperativeVectorMatrixLayoutNV(std::string_view name, VkCooperativeVectorMatrixLayoutNV& out);
bool EnumFromString_VkCopyAccelerationStructureModeKHR(std::string_view name, VkCopyAccelerationStructureModeKHR& out);
bool EnumFromString_VkCopyMicromapModeEXT(std::string_view name, VkCopyMicromapModeEXT& out);
bool EnumFromString_VkCoverageModulationModeNV(std::string_view name, VkCoverageModulationModeNV& out);
bool EnumFromString_VkCoverageReductionModeNV(std::string_view name, VkCoverageReductionModeNV& out);
bool EnumFromString_VkCubicFilterWeightsQCOM(std::string_view name, VkCubicFilterWeightsQCOM& out);
bool EnumFromString_VkCullModeFlagBits(std::string_view name, VkCullModeFlagBits& out);
bool EnumFromString_VkDataGraphModelCacheTypeQCOM(std::string_view name, VkDataGraphModelCacheTypeQCOM& out);
bool EnumFromString_VkDataGraphOpticalFlowCreateFlagBitsARM(std::string_view name, VkDataGraphOpticalFlowCreateFlagBitsARM& out);
bool EnumFromString_VkDataGraphOpticalFlowExecuteFlagBitsARM(std::string_view name, VkDataGraphOpticalFlowExecuteFlagBitsARM& out);
bool EnumFromString_VkDataGraphOpticalFlowGridSizeFlagBitsARM(std::string_view name, VkDataGraphOpticalFlowGridSizeFlagBitsARM& out);
bool EnumFromString_VkDataGraphOpticalFlowImageUsageFlagBitsARM(std::string_view name, VkDataGraphOpticalFlowImageUsageFlagBitsARM& out);
bool EnumFromString_VkDataGraphOpticalFlowPerformanceLevelARM(std::string_view name, VkDataGraphOpticalFlowPerformanceLevelARM& out);
bool EnumFromString_VkDataGraphPipelineDispatchFlagBitsARM(std::string_view name, VkDataGraphPipelineDispatchFlagBitsARM& out);
bool EnumFromString_VkDataGraphPipelineNodeConnectionTypeARM(std::string_view name, VkDataGraphPipelineNodeConnectionTypeARM& out);
bool EnumFromString_VkDataGraphPipelineNodeTypeARM(std::string_view name, VkDataGraphPipelineNodeTypeARM& out);
bool EnumFromString_VkDataGraphPipelinePropertyARM(std::string_view name, VkDataGraphPipelinePropertyARM& out);
bool EnumFromString_VkDataGraphPipelineSessionBindPointARM(std::string_view name, VkDataGraphPipelineSessionBindPointARM& out);
bool EnumFromString_VkDataGraphPipelineSessionBindPointTypeARM(std::string_view name, VkDataGraphPipelineSessionBindPointTypeARM& out);
bool EnumFromString_VkDataGraphPipelineSessionCreateFlagBitsARM(std::string_view name, VkDataGraphPipelineSessionCreateFlagBitsARM& out);
bool EnumFromString_VkDebugReportFlagBitsEXT(std::string_view name, VkDebugReportFlagBitsEXT& out);
bool EnumFromString_VkDebugReportObjectTypeEXT(std::string_view name, VkDebugReportObjectTypeEXT& out);
bool EnumFromString_VkDebugUtilsMessageSeverityFlagBitsEXT(std::string_view name, VkDebugUtilsMessageSeverityFlagBitsEXT& out);
bool EnumFromString_VkDebugUtilsMessageTypeFlagBitsEXT(std::string_view name, VkDebugUtilsMessageTypeFlagBitsEXT& out);
bool EnumFromString_VkDefaultVertexAttributeValueKHR(std::string_view name, VkDefaultVertexAttributeValueKHR& out);
bool EnumFromString_VkDependencyFlagBits(std::string_view name, VkDependencyFlagBits& out);
bool EnumFromString_VkDepthBiasRepresentationEXT(std::string_view name, VkDepthBiasRepresentationEXT& out);
bool EnumFromString_VkDepthClampModeEXT(std::string_view name, VkDepthClampModeEXT& out);
bool EnumFromString_VkDescriptorBindingFlagBits(std::string_view name, VkDescriptorBindingFlagBits& out);
bool EnumFromString_VkDescriptorPoolCreateFlagBits(std::string_view name, VkDescriptorPoolCreateFlagBits& out);
bool EnumFromString_VkDescriptorSetLayoutCreateFlagBits(std::string_view name, VkDescriptorSetLayoutCreateFlagBits& out);
bool EnumFromString_VkDescriptorType(std::string_view name, VkDescriptorType& out);
bool EnumFromString_VkDescriptorUpdateTemplateType(std::string_view name, VkDescriptorUpdateTemplateType& out);
bool EnumFromString_VkDeviceAddressBindingFlagBitsEXT(std::string_view name, VkDeviceAddressBindingFlagBitsEXT& out);
bool EnumFromString_VkDeviceAddressBindingTypeEXT(std::string_view name, VkDeviceAddressBindingTypeEXT& out);
bool EnumFromString_VkDeviceDiagnosticsConfigFlagBitsNV(std::string_view name, VkDeviceDiagnosticsConfigFlagBitsNV& out);
bool EnumFromString_VkDeviceEventTypeEXT(std::string_view name, VkDeviceEventTypeEXT& out);
bool EnumFromString_VkDeviceFaultAddressTypeKHR(std::string_view name, VkDeviceFaultAddressTypeKHR& out);
bool EnumFromString_VkDeviceFaultFlagBitsKHR(std::string_view name, VkDeviceFaultFlagBitsKHR& out);
bool EnumFromString_VkDeviceFaultVendorBinaryHeaderVersionKHR(std::string_view name, VkDeviceFaultVendorBinaryHeaderVersionKHR& out);
bool EnumFromString_VkDeviceGroupPresentModeFlagBitsKHR(std::string_view name, VkDeviceGroupPresentModeFlagBitsKHR& out);
bool EnumFromString_VkDeviceMemoryReportEventTypeEXT(std::string_view name, VkDeviceMemoryReportEventTypeEXT& out);
bool EnumFromString_VkDeviceQueueCreateFlagBits(std::string_view name, VkDeviceQueueCreateFlagBits& out);
bool EnumFromString_VkDirectDriverLoadingModeLUNARG(std::string_view name, VkDirectDriverLoadingModeLUNARG& out);
bool EnumFromString_VkDiscardRectangleModeEXT(std::string_view name, VkDiscardRectangleModeEXT& out);
bool EnumFromString_VkDisplacementMicromapFormatNV(std::string_view name, VkDisplacementMicromapFormatNV& out);
bool EnumFromString_VkDisplayEventTypeEXT(std::string_view name, VkDisplayEventTypeEXT& out);
bool EnumFromString_VkDisplayPlaneAlphaFlagBitsKHR(std::string_view name, VkDisplayPlaneAlphaFlagBitsKHR& out);
bool EnumFromString_VkDisplayPowerStateEXT(std::string_view name, VkDisplayPowerStateEXT& out);
bool EnumFromString_VkDisplaySurfaceStereoTypeNV(std::string_view name, VkDisplaySurfaceStereoTypeNV& out);
bool EnumFromString_VkDriverId(std::string_view name, VkDriverId& out);
bool EnumFromString_VkDynamicState(std::string_view name, VkDynamicState& out);
bool EnumFromString_VkEventCreateFlagBits(std::string_view name, VkEventCreateFlagBits& out);
bool EnumFromString_VkExternalFenceFeatureFlagBits(std::string_view name, VkExternalFenceFeatureFlagBits& out);
bool EnumFromString_VkExternalFenceHandleTypeFlagBits(std::string_view name, VkExternalFenceHandleTypeFlagBits& out);
bool EnumFromString_VkExternalMemoryFeatureFlagBits(std::string_view name, VkExternalMemoryFeatureFlagBits& out);
bool EnumFromString_VkExternalMemoryFeatureFlagBitsNV(std::string_view name, VkExternalMemoryFeatureFlagBitsNV& out);
bool EnumFromString_VkExternalMemoryHandleTypeFlagBits(std::string_view name, VkExternalMemoryHandleTypeFlagBits& out);
bool EnumFromString_VkExternalMemoryHandleTypeFlagBitsNV(std::string_view name, VkExternalMemoryHandleTypeFlagBitsNV& out);
bool EnumFromString_VkExternalSemaphoreFeatureFlagBits(std::string_view name, VkExternalSemaphoreFeatureFlagBits& out);
bool EnumFromString_VkExternalSemaphoreHandleTypeFlagBits(std::string_view name, VkExternalSemaphoreHandleTypeFlagBits& out);
bool EnumFromString_VkFenceCreateFlagBits(std::string_view name, VkFenceCreateFlagBits& out);
bool EnumFromString_VkFenceImportFlagBits(std::string_view name, VkFenceImportFlagBits& out);
bool EnumFromString_VkFilter(std::string_view name, VkFilter& out);
bool EnumFromString_VkFormat(std::string_view name, VkFormat& out);
bool EnumFromString_VkFormatFeatureFlagBits(std::string_view name, VkFormatFeatureFlagBits& out);
bool EnumFromString_VkFormatFeatureFlagBits2(std::string_view name, VkFormatFeatureFlagBits2& out);
bool EnumFromString_VkFormatFeatureFlagBits4KHR(std::string_view name, VkFormatFeatureFlagBits4KHR& out);
bool EnumFromString_VkFragmentShadingRateCombinerOpKHR(std::string_view name, VkFragmentShadingRateCombinerOpKHR& out);
bool EnumFromString_VkFragmentShadingRateNV(std::string_view name, VkFragmentShadingRateNV& out);
bool EnumFromString_VkFragmentShadingRateTypeNV(std::string_view name, VkFragmentShadingRateTypeNV& out);
bool EnumFromString_VkFrameBoundaryFlagBitsEXT(std::string_view name, VkFrameBoundaryFlagBitsEXT& out);
bool EnumFromString_VkFramebufferCreateFlagBits(std::string_view name, VkFramebufferCreateFlagBits& out);
bool EnumFromString_VkFrontFace(std::string_view name, VkFrontFace& out);
bool EnumFromString_VkFullScreenExclusiveEXT(std::string_view name, VkFullScreenExclusiveEXT& out);
bool EnumFromString_VkGeometryFlagBitsKHR(std::string_view name, VkGeometryFlagBitsKHR& out);
bool EnumFromString_VkGeometryInstanceFlagBitsKHR(std::string_view name, VkGeometryInstanceFlagBitsKHR& out);
bool EnumFromString_VkGeometryTypeKHR(std::string_view name, VkGeometryTypeKHR& out);
bool EnumFromString_VkGpaDeviceClockModeAMD(std::string_view name, VkGpaDeviceClockModeAMD& out);
bool EnumFromString_VkGpaPerfBlockAMD(std::string_view name, VkGpaPerfBlockAMD& out);
bool EnumFromString_VkGpaSampleTypeAMD(std::string_view name, VkGpaSampleTypeAMD& out);
bool EnumFromString_VkGpaSqShaderStageFlagBitsAMD(std::string_view name, VkGpaSqShaderStageFlagBitsAMD& out);
bool EnumFromString_VkGraphicsPipelineLibraryFlagBitsEXT(std::string_view name, VkGraphicsPipelineLibraryFlagBitsEXT& out);
bool EnumFromString_VkHostImageCopyFlagBits(std::string_view name, VkHostImageCopyFlagBits& out);
bool EnumFromString_VkImageAspectFlagBits(std::string_view name, VkImageAspectFlagBits& out);
bool EnumFromString_VkImageCompressionFixedRateFlagBitsEXT(std::string_view name, VkImageCompressionFixedRateFlagBitsEXT& out);
bool EnumFromString_VkImageCompressionFlagBitsEXT(std::string_view name, VkImageCompressionFlagBitsEXT& out);
bool EnumFromString_VkImageCreateFlagBits(std::string_view name, VkImageCreateFlagBits& out);
bool EnumFromString_VkImageCreateFlagBits2KHR(std::string_view name, VkImageCreateFlagBits2KHR& out);
bool EnumFromString_VkImageLayout(std::string_view name, VkImageLayout& out);
bool EnumFromString_VkImageTiling(std::string_view name, VkImageTiling& out);
bool EnumFromString_VkImageTilingControlEXT(std::string_view name, VkImageTilingControlEXT& out);
bool EnumFromString_VkImageType(std::string_view name, VkImageType& out);
bool EnumFromString_VkImageUsageFlagBits(std::string_view name, VkImageUsageFlagBits& out);
bool EnumFromString_VkImageUsageFlagBits2KHR(std::string_view name, VkImageUsageFlagBits2KHR& out);
bool EnumFromString_VkImageViewCreateFlagBits(std::string_view name, VkImageViewCreateFlagBits& out);
bool EnumFromString_VkImageViewType(std::string_view name, VkImageViewType& out);
bool EnumFromString_VkIndexType(std::string_view name, VkIndexType& out);
bool EnumFromString_VkIndirectCommandsInputModeFlagBitsEXT(std::string_view name, VkIndirectCommandsInputModeFlagBitsEXT& out);
bool EnumFromString_VkIndirectCommandsLayoutUsageFlagBitsEXT(std::string_view name, VkIndirectCommandsLayoutUsageFlagBitsEXT& out);
bool EnumFromString_VkIndirectCommandsLayoutUsageFlagBitsNV(std::string_view name, VkIndirectCommandsLayoutUsageFlagBitsNV& out);
bool EnumFromString_VkIndirectCommandsTokenTypeEXT(std::string_view name, VkIndirectCommandsTokenTypeEXT& out);
bool EnumFromString_VkIndirectCommandsTokenTypeNV(std::string_view name, VkIndirectCommandsTokenTypeNV& out);
bool EnumFromString_VkIndirectExecutionSetInfoTypeEXT(std::string_view name, VkIndirectExecutionSetInfoTypeEXT& out);
bool EnumFromString_VkIndirectStateFlagBitsNV(std::string_view name, VkIndirectStateFlagBitsNV& out);
bool EnumFromString_VkInstanceCreateFlagBits(std::string_view name, VkInstanceCreateFlagBits& out);
bool EnumFromString_VkInternalAllocationType(std::string_view name, VkInternalAllocationType& out);
bool EnumFromString_VkLatencyMarkerNV(std::string_view name, VkLatencyMarkerNV& out);
bool EnumFromString_VkLayerSettingTypeEXT(std::string_view name, VkLayerSettingTypeEXT& out);
bool EnumFromString_VkLayeredDriverUnderlyingApiMSFT(std::string_view name, VkLayeredDriverUnderlyingApiMSFT& out);
bool EnumFromString_VkLineRasterizationMode(std::string_view name, VkLineRasterizationMode& out);
bool EnumFromString_VkLogicOp(std::string_view name, VkLogicOp& out);
bool EnumFromString_VkMemoryAllocateFlagBits(std::string_view name, VkMemoryAllocateFlagBits& out);
bool EnumFromString_VkMemoryDecompressionMethodFlagBitsEXT(std::string_view name, VkMemoryDecompressionMethodFlagBitsEXT& out);
bool EnumFromString_VkMemoryHeapFlagBits(std::string_view name, VkMemoryHeapFlagBits& out);
bool EnumFromString_VkMemoryMapFlagBits(std::string_view name, VkMemoryMapFlagBits& out);
bool EnumFromString_VkMemoryOverallocationBehaviorAMD(std::string_view name, VkMemoryOverallocationBehaviorAMD& out);
bool EnumFromString_VkMemoryPropertyFlagBits(std::string_view name, VkMemoryPropertyFlagBits& out);
bool EnumFromString_VkMemoryUnmapFlagBits(std::string_view name, VkMemoryUnmapFlagBits& out);
bool EnumFromString_VkMicromapCreateFlagBitsEXT(std::string_view name, VkMicromapCreateFlagBitsEXT& out);
bool EnumFromString_VkMicromapTypeEXT(std::string_view name, VkMicromapTypeEXT& out);
bool EnumFromString_VkNeuralAcceleratorStatisticsModeARM(std::string_view name, VkNeuralAcceleratorStatisticsModeARM& out);
bool EnumFromString_VkObjectType(std::string_view name, VkObjectType& out);
bool EnumFromString_VkOpacityMicromapFormatKHR(std::string_view name, VkOpacityMicromapFormatKHR& out);
bool EnumFromString_VkOpacityMicromapSpecialIndexKHR(std::string_view name, VkOpacityMicromapSpecialIndexKHR& out);
bool EnumFromString_VkOpticalFlowExecuteFlagBitsNV(std::string_view name, VkOpticalFlowExecuteFlagBitsNV& out);
bool EnumFromString_VkOpticalFlowGridSizeFlagBitsNV(std::string_view name, VkOpticalFlowGridSizeFlagBitsNV& out);
bool EnumFromString_VkOpticalFlowPerformanceLevelNV(std::string_view name, VkOpticalFlowPerformanceLevelNV& out);
bool EnumFromString_VkOpticalFlowSessionBindingPointNV(std::string_view name, VkOpticalFlowSessionBindingPointNV& out);
bool EnumFromString_VkOpticalFlowSessionCreateFlagBitsNV(std::string_view name, VkOpticalFlowSessionCreateFlagBitsNV& out);
bool EnumFromString_VkOpticalFlowUsageFlagBitsNV(std::string_view name, VkOpticalFlowUsageFlagBitsNV& out);
bool EnumFromString_VkOutOfBandQueueTypeNV(std::string_view name, VkOutOfBandQueueTypeNV& out);
bool EnumFromString_VkPartitionedAccelerationStructureInstanceFlagBitsNV(std::string_view name, VkPartitionedAccelerationStructureInstanceFlagBitsNV& out);
bool EnumFromString_VkPartitionedAccelerationStructureOpTypeNV(std::string_view name, VkPartitionedAccelerationStructureOpTypeNV& out);
bool EnumFromString_VkPastPresentationTimingFlagBitsEXT(std::string_view name, VkPastPresentationTimingFlagBitsEXT& out);
bool EnumFromString_VkPeerMemoryFeatureFlagBits(std::string_view name, VkPeerMemoryFeatureFlagBits& out);
bool EnumFromString_VkPerfHintTypeQCOM(std::string_view name, VkPerfHintTypeQCOM& out);
bool EnumFromString_VkPerformanceConfigurationTypeINTEL(std::string_view name, VkPerformanceConfigurationTypeINTEL& out);
bool EnumFromString_VkPerformanceCounterDescriptionFlagBitsKHR(std::string_view name, VkPerformanceCounterDescriptionFlagBitsKHR& out);
bool EnumFromString_VkPerformanceCounterScopeKHR(std::string_view name, VkPerformanceCounterScopeKHR& out);
bool EnumFromString_VkPerformanceCounterStorageKHR(std::string_view name, VkPerformanceCounterStorageKHR& out);
bool EnumFromString_VkPerformanceCounterUnitKHR(std::string_view name, VkPerformanceCounterUnitKHR& out);
bool EnumFromString_VkPerformanceOverrideTypeINTEL(std::string_view name, VkPerformanceOverrideTypeINTEL& out);
bool EnumFromString_VkPerformanceParameterTypeINTEL(std::string_view name, VkPerformanceParameterTypeINTEL& out);
bool EnumFromString_VkPerformanceValueTypeINTEL(std::string_view name, VkPerformanceValueTypeINTEL& out);
bool EnumFromString_VkPhysicalDeviceDataGraphOperationTypeARM(std::string_view name, VkPhysicalDeviceDataGraphOperationTypeARM& out);
bool EnumFromString_VkPhysicalDeviceDataGraphProcessingEngineTypeARM(std::string_view name, VkPhysicalDeviceDataGraphProcessingEngineTypeARM& out);
bool EnumFromString_VkPhysicalDeviceLayeredApiKHR(std::string_view name, VkPhysicalDeviceLayeredApiKHR& out);
bool EnumFromString_VkPhysicalDeviceSchedulingControlsFlagBitsARM(std::string_view name, VkPhysicalDeviceSchedulingControlsFlagBitsARM& out);
bool EnumFromString_VkPhysicalDeviceType(std::string_view name, VkPhysicalDeviceType& out);
bool EnumFromString_VkPipelineBindPoint(std::string_view name, VkPipelineBindPoint& out);
bool EnumFromString_VkPipelineCacheCreateFlagBits(std::string_view name, VkPipelineCacheCreateFlagBits& out);
bool EnumFromString_VkPipelineCacheHeaderVersion(std::string_view name, VkPipelineCacheHeaderVersion& out);
bool EnumFromString_VkPipelineColorBlendStateCreateFlagBits(std::string_view name, VkPipelineColorBlendStateCreateFlagBits& out);
bool EnumFromString_VkPipelineCompilerControlFlagBitsAMD(std::string_view name, VkPipelineCompilerControlFlagBitsAMD& out);
bool EnumFromString_VkPipelineCreateFlagBits(std::string_view name, VkPipelineCreateFlagBits& out);
bool EnumFromString_VkPipelineCreateFlagBits2(std::string_view name, VkPipelineCreateFlagBits2& out);
bool EnumFromString_VkPipelineCreationFeedbackFlagBits(std::string_view name, VkPipelineCreationFeedbackFlagBits& out);
bool EnumFromString_VkPipelineDepthStencilStateCreateFlagBits(std::string_view name, VkPipelineDepthStencilStateCreateFlagBits& out);
bool EnumFromString_VkPipelineExecutableStatisticFormatKHR(std::string_view name, VkPipelineExecutableStatisticFormatKHR& out);
bool EnumFromString_VkPipelineLayoutCreateFlagBits(std::string_view name, VkPipelineLayoutCreateFlagBits& out);
bool EnumFromString_VkPipelineRobustnessBufferBehavior(std::string_view name, VkPipelineRobustnessBufferBehavior& out);
bool EnumFromString_VkPipelineRobustnessImageBehavior(std::string_view name, VkPipelineRobustnessImageBehavior& out);
bool EnumFromString_VkPipelineShaderStageCreateFlagBits(std::string_view name, VkPipelineShaderStageCreateFlagBits& out);
bool EnumFromString_VkPipelineStageFlagBits(std::string_view name, VkPipelineStageFlagBits& out);
bool EnumFromString_VkPipelineStageFlagBits2(std::string_view name, VkPipelineStageFlagBits2& out);
bool EnumFromString_VkPointClippingBehavior(std::string_view name, VkPointClippingBehavior& out);
bool EnumFromString_VkPolygonMode(std::string_view name, VkPolygonMode& out);
bool EnumFromString_VkPresentGravityFlagBitsKHR(std::string_view name, VkPresentGravityFlagBitsKHR& out);
bool EnumFromString_VkPresentModeKHR(std::string_view name, VkPresentModeKHR& out);
bool EnumFromString_VkPresentScalingFlagBitsKHR(std::string_view name, VkPresentScalingFlagBitsKHR& out);
bool EnumFromString_VkPresentStageFlagBitsEXT(std::string_view name, VkPresentStageFlagBitsEXT& out);
bool EnumFromString_VkPresentTimingInfoFlagBitsEXT(std::string_view name, VkPresentTimingInfoFlagBitsEXT& out);
bool EnumFromString_VkPrimitiveTopology(std::string_view name, VkPrimitiveTopology& out);
bool EnumFromString_VkPrivateDataSlotCreateFlagBits(std::string_view name, VkPrivateDataSlotCreateFlagBits& out);
bool EnumFromString_VkProvokingVertexModeEXT(std::string_view name, VkProvokingVertexModeEXT& out);
bool EnumFromString_VkQueryControlFlagBits(std::string_view name, VkQueryControlFlagBits& out);
bool EnumFromString_VkQueryPipelineStatisticFlagBits(std::string_view name, VkQueryPipelineStatisticFlagBits& out);
bool EnumFromString_VkQueryPoolCreateFlagBits(std::string_view name, VkQueryPoolCreateFlagBits& out);
bool EnumFromString_VkQueryPoolSamplingModeINTEL(std::string_view name, VkQueryPoolSamplingModeINTEL& out);
bool EnumFromString_VkQueryResultFlagBits(std::string_view name, VkQueryResultFlagBits& out);
bool EnumFromString_VkQueryResultStatusKHR(std::string_view name, VkQueryResultStatusKHR& out);
bool EnumFromString_VkQueryType(std::string_view name, VkQueryType& out);
bool EnumFromString_VkQueueFlagBits(std::string_view name, VkQueueFlagBits& out);
bool EnumFromString_VkQueueGlobalPriority(std::string_view name, VkQueueGlobalPriority& out);
bool EnumFromString_VkRasterizationOrderAMD(std::string_view name, VkRasterizationOrderAMD& out);
bool EnumFromString_VkRayTracingInvocationReorderModeEXT(std::string_view name, VkRayTracingInvocationReorderModeEXT& out);
bool EnumFromString_VkRayTracingLssIndexingModeNV(std::string_view name, VkRayTracingLssIndexingModeNV& out);
bool EnumFromString_VkRayTracingLssPrimitiveEndCapsModeNV(std::string_view name, VkRayTracingLssPrimitiveEndCapsModeNV& out);
bool EnumFromString_VkRayTracingShaderGroupTypeKHR(std::string_view name, VkRayTracingShaderGroupTypeKHR& out);
bool EnumFromString_VkRenderPassCreateFlagBits(std::string_view name, VkRenderPassCreateFlagBits& out);
bool EnumFromString_VkRenderingAttachmentFlagBitsKHR(std::string_view name, VkRenderingAttachmentFlagBitsKHR& out);
bool EnumFromString_VkRenderingFlagBits(std::string_view name, VkRenderingFlagBits& out);
bool EnumFromString_VkResolveImageFlagBitsKHR(std::string_view name, VkResolveImageFlagBitsKHR& out);
bool EnumFromString_VkResolveModeFlagBits(std::string_view name, VkResolveModeFlagBits& out);
bool EnumFromString_VkResult(std::string_view name, VkResult& out);
bool EnumFromString_VkSampleCountFlagBits(std::string_view name, VkSampleCountFlagBits& out);
bool EnumFromString_VkSamplerAddressMode(std::string_view name, VkSamplerAddressMode& out);
bool EnumFromString_VkSamplerCreateFlagBits(std::string_view name, VkSamplerCreateFlagBits& out);
bool EnumFromString_VkSamplerMipmapMode(std::string_view name, VkSamplerMipmapMode& out);
bool EnumFromString_VkSamplerReductionMode(std::string_view name, VkSamplerReductionMode& out);
bool EnumFromString_VkSamplerYcbcrModelConversion(std::string_view name, VkSamplerYcbcrModelConversion& out);
bool EnumFromString_VkSamplerYcbcrRange(std::string_view name, VkSamplerYcbcrRange& out);
bool EnumFromString_VkScopeKHR(std::string_view name, VkScopeKHR& out);
bool EnumFromString_VkSemaphoreImportFlagBits(std::string_view name, VkSemaphoreImportFlagBits& out);
bool EnumFromString_VkSemaphoreType(std::string_view name, VkSemaphoreType& out);
bool EnumFromString_VkSemaphoreWaitFlagBits(std::string_view name, VkSemaphoreWaitFlagBits& out);
bool EnumFromString_VkShaderCodeTypeEXT(std::string_view name, VkShaderCodeTypeEXT& out);
bool EnumFromString_VkShaderCorePropertiesFlagBitsAMD(std::string_view name, VkShaderCorePropertiesFlagBitsAMD& out);
bool EnumFromString_VkShaderCreateFlagBitsEXT(std::string_view name, VkShaderCreateFlagBitsEXT& out);
bool EnumFromString_VkShaderFloatControlsIndependence(std::string_view name, VkShaderFloatControlsIndependence& out);
bool EnumFromString_VkShaderGroupShaderKHR(std::string_view name, VkShaderGroupShaderKHR& out);
bool EnumFromString_VkShaderInfoTypeAMD(std::string_view name, VkShaderInfoTypeAMD& out);
bool EnumFromString_VkShaderStageFlagBits(std::string_view name, VkShaderStageFlagBits& out);
bool EnumFromString_VkShadingRatePaletteEntryNV(std::string_view name, VkShadingRatePaletteEntryNV& out);
bool EnumFromString_VkSharingMode(std::string_view name, VkSharingMode& out);
bool EnumFromString_VkSparseImageFormatFlagBits(std::string_view name, VkSparseImageFormatFlagBits& out);
bool EnumFromString_VkSparseMemoryBindFlagBits(std::string_view name, VkSparseMemoryBindFlagBits& out);
bool EnumFromString_VkStencilFaceFlagBits(std::string_view name, VkStencilFaceFlagBits& out);
bool EnumFromString_VkStencilOp(std::string_view name, VkStencilOp& out);
bool EnumFromString_VkStructureType(std::string_view name, VkStructureType& out);
bool EnumFromString_VkSubgroupFeatureFlagBits(std::string_view name, VkSubgroupFeatureFlagBits& out);
bool EnumFromString_VkSubmitFlagBits(std::string_view name, VkSubmitFlagBits& out);
bool EnumFromString_VkSubpassContents(std::string_view name, VkSubpassContents& out);
bool EnumFromString_VkSubpassDescriptionFlagBits(std::string_view name, VkSubpassDescriptionFlagBits& out);
bool EnumFromString_VkSubpassMergeStatusEXT(std::string_view name, VkSubpassMergeStatusEXT& out);
bool EnumFromString_VkSurfaceCounterFlagBitsEXT(std::string_view name, VkSurfaceCounterFlagBitsEXT& out);
bool EnumFromString_VkSurfaceTransformFlagBitsKHR(std::string_view name, VkSurfaceTransformFlagBitsKHR& out);
bool EnumFromString_VkSwapchainCreateFlagBitsKHR(std::string_view name, VkSwapchainCreateFlagBitsKHR& out);
bool EnumFromString_VkSystemAllocationScope(std::string_view name, VkSystemAllocationScope& out);
bool EnumFromString_VkTensorCreateFlagBitsARM(std::string_view name, VkTensorCreateFlagBitsARM& out);
bool EnumFromString_VkTensorTilingARM(std::string_view name, VkTensorTilingARM& out);
bool EnumFromString_VkTensorUsageFlagBitsARM(std::string_view name, VkTensorUsageFlagBitsARM& out);
bool EnumFromString_VkTensorViewCreateFlagBitsARM(std::string_view name, VkTensorViewCreateFlagBitsARM& out);
bool EnumFromString_VkTessellationDomainOrigin(std::string_view name, VkTessellationDomainOrigin& out);
bool EnumFromString_VkThrottleHintTypeSEC(std::string_view name, VkThrottleHintTypeSEC& out);
bool EnumFromString_VkTileShadingRenderPassFlagBitsQCOM(std::string_view name, VkTileShadingRenderPassFlagBitsQCOM& out);
bool EnumFromString_VkTimeDomainKHR(std::string_view name, VkTimeDomainKHR& out);
bool EnumFromString_VkToolPurposeFlagBits(std::string_view name, VkToolPurposeFlagBits& out);
bool EnumFromString_VkValidationCacheHeaderVersionEXT(std::string_view name, VkValidationCacheHeaderVersionEXT& out);
bool EnumFromString_VkValidationCheckEXT(std::string_view name, VkValidationCheckEXT& out);
bool EnumFromString_VkValidationFeatureDisableEXT(std::string_view name, VkValidationFeatureDisableEXT& out);
bool EnumFromString_VkValidationFeatureEnableEXT(std::string_view name, VkValidationFeatureEnableEXT& out);
bool EnumFromString_VkVendorId(std::string_view name, VkVendorId& out);
bool EnumFromString_VkVertexInputRate(std::string_view name, VkVertexInputRate& out);
bool EnumFromString_VkVideoCapabilityFlagBitsKHR(std::string_view name, VkVideoCapabilityFlagBitsKHR& out);
bool EnumFromString_VkVideoChromaSubsamplingFlagBitsKHR(std::string_view name, VkVideoChromaSubsamplingFlagBitsKHR& out);
bool EnumFromString_VkVideoCodecOperationFlagBitsKHR(std::string_view name, VkVideoCodecOperationFlagBitsKHR& out);
bool EnumFromString_VkVideoCodingControlFlagBitsKHR(std::string_view name, VkVideoCodingControlFlagBitsKHR& out);
bool EnumFromString_VkVideoComponentBitDepthFlagBitsKHR(std::string_view name, VkVideoComponentBitDepthFlagBitsKHR& out);
bool EnumFromString_VkVideoDecodeCapabilityFlagBitsKHR(std::string_view name, VkVideoDecodeCapabilityFlagBitsKHR& out);
bool EnumFromString_VkVideoDecodeH264PictureLayoutFlagBitsKHR(std::string_view name, VkVideoDecodeH264PictureLayoutFlagBitsKHR& out);
bool EnumFromString_VkVideoDecodeUsageFlagBitsKHR(std::string_view name, VkVideoDecodeUsageFlagBitsKHR& out);
bool EnumFromString_VkVideoEncodeAV1CapabilityFlagBitsKHR(std::string_view name, VkVideoEncodeAV1CapabilityFlagBitsKHR& out);
bool EnumFromString_VkVideoEncodeAV1PredictionModeKHR(std::string_view name, VkVideoEncodeAV1PredictionModeKHR& out);
bool EnumFromString_VkVideoEncodeAV1RateControlFlagBitsKHR(std::string_view name, VkVideoEncodeAV1RateControlFlagBitsKHR& out);
bool EnumFromString_VkVideoEncodeAV1RateControlGroupKHR(std::string_view name, VkVideoEncodeAV1RateControlGroupKHR& out);
bool EnumFromString_VkVideoEncodeAV1StdFlagBitsKHR(std::string_view name, VkVideoEncodeAV1StdFlagBitsKHR& out);
bool EnumFromString_VkVideoEncodeAV1SuperblockSizeFlagBitsKHR(std::string_view name, VkVideoEncodeAV1SuperblockSizeFlagBitsKHR& out);
bool EnumFromString_VkVideoEncodeCapabilityFlagBitsKHR(std::string_view name, VkVideoEncodeCapabilityFlagBitsKHR& out);
bool EnumFromString_VkVideoEncodeContentFlagBitsKHR(std::string_view name, VkVideoEncodeContentFlagBitsKHR& out);
bool EnumFromString_VkVideoEncodeFeedbackFlagBitsKHR(std::string_view name, VkVideoEncodeFeedbackFlagBitsKHR& out);
bool EnumFromString_VkVideoEncodeFlagBitsKHR(std::string_view name, VkVideoEncodeFlagBitsKHR& out);
bool EnumFromString_VkVideoEncodeH264CapabilityFlagBitsKHR(std::string_view name, VkVideoEncodeH264CapabilityFlagBitsKHR& out);
bool EnumFromString_VkVideoEncodeH264RateControlFlagBitsKHR(std::string_view name, VkVideoEncodeH264RateControlFlagBitsKHR& out);
bool EnumFromString_VkVideoEncodeH264StdFlagBitsKHR(std::string_view name, VkVideoEncodeH264StdFlagBitsKHR& out);
bool EnumFromString_VkVideoEncodeH265CtbSizeFlagBitsKHR(std::string_view name, VkVideoEncodeH265CtbSizeFlagBitsKHR& out);
bool EnumFromString_VkVideoEncodeIntraRefreshModeFlagBitsKHR(std::string_view name, VkVideoEncodeIntraRefreshModeFlagBitsKHR& out);
bool EnumFromString_VkVideoEncodePerPartitionFeedbackFlagBitsKHR(std::string_view name, VkVideoEncodePerPartitionFeedbackFlagBitsKHR& out);
bool EnumFromString_VkVideoEncodeRateControlModeFlagBitsKHR(std::string_view name, VkVideoEncodeRateControlModeFlagBitsKHR& out);
bool EnumFromString_VkVideoEncodeRgbChromaOffsetFlagBitsVALVE(std::string_view name, VkVideoEncodeRgbChromaOffsetFlagBitsVALVE& out);
bool EnumFromString_VkVideoEncodeRgbModelConversionFlagBitsVALVE(std::string_view name, VkVideoEncodeRgbModelConversionFlagBitsVALVE& out);
bool EnumFromString_VkVideoEncodeRgbRangeCompressionFlagBitsVALVE(std::string_view name, VkVideoEncodeRgbRangeCompressionFlagBitsVALVE& out);
bool EnumFromString_VkVideoEncodeTuningModeKHR(std::string_view name, VkVideoEncodeTuningModeKHR& out);
bool EnumFromString_VkVideoEncodeUsageFlagBitsKHR(std::string_view name, VkVideoEncodeUsageFlagBitsKHR& out);
bool EnumFromString_VkVideoSessionCreateFlagBitsKHR(std::string_view name, VkVideoSessionCreateFlagBitsKHR& out);
bool EnumFromString_VkVideoSessionParametersCreateFlagBitsKHR(std::string_view name, VkVideoSessionParametersCreateFlagBitsKHR& out);
bool EnumFromString_VkViewportCoordinateSwizzleNV(std::string_view name, VkViewportCoordinateSwizzleNV& out);

GFXRECON_END_NAMESPACE(decode)
GFXRECON_END_NAMESPACE(gfxrecon)

#endif // GFXRECON_GENERATED_VULKAN_ENUM_FROM_STRING_H
