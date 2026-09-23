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

#include "vulkan/vulkan.h"
#include "vk_video/vulkan_video_codec_h264std.h"
#include "vk_video/vulkan_video_codec_h264std_decode.h"
#include "vk_video/vulkan_video_codec_h264std_encode.h"
#include "vk_video/vulkan_video_codec_h265std.h"
#include "vk_video/vulkan_video_codec_h265std_decode.h"
#include "vk_video/vulkan_video_codec_h265std_encode.h"
#include "vk_video/vulkan_video_codecs_common.h"

#include "apidump_struct_encode.h"

#include "generated_vulkan_enum_from_string.h"
#include "generated_vulkan_struct_from_apidump.h"

#include "util/logging.h"

GFXRECON_BEGIN_NAMESPACE(gfxrecon)
GFXRECON_BEGIN_NAMESPACE(decode)

namespace
{

/** Reads the sType of a chain link, by number when the layer wrote one and by name otherwise. */
bool ResolveStructureType(ApiDumpContext& ctx, std::string_view text, VkStructureType& out)
{
    int64_t numeric = 0;
    if (ParseLeadingSigned(text, numeric))
    {
        out = static_cast<VkStructureType>(numeric);
        return true;
    }

    if (text.empty() || !EnumFromString_VkStructureType(text, out))
    {
        ++ctx.MutableStats().unknown_structure_types;
        return false;
    }

    return true;
}

} // namespace

void PNextFromApiDump(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    if (value.IsNullPointer() || !value.HasData())
    {
        ctx.Encoder().EncodeStructPtrPreamble(0, true, false);
        return;
    }

    VkStructureType stype{};
    const std::string_view stype_text = value["sType"].ValueString();

    if (!ResolveStructureType(ctx, stype_text, stype))
    {
        // The chain cannot be walked past a link whose type is unknown, because the
        // members that follow cannot be interpreted. Encode a null so the buffer stays
        // well formed and let the conversion summary report it.
        ctx.Encoder().EncodeStructPtrPreamble(0, true, false);
        return;
    }

    switch (stype)
    {
    case VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_BUILD_GEOMETRY_INFO_KHR:
        StructPtrFromApiDump<VkAccelerationStructureBuildGeometryInfoKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_BUILD_SIZES_INFO_KHR:
        StructPtrFromApiDump<VkAccelerationStructureBuildSizesInfoKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_CAPTURE_DESCRIPTOR_DATA_INFO_EXT:
        StructPtrFromApiDump<VkAccelerationStructureCaptureDescriptorDataInfoEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_CREATE_INFO_2_KHR:
        StructPtrFromApiDump<VkAccelerationStructureCreateInfo2KHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_CREATE_INFO_KHR:
        StructPtrFromApiDump<VkAccelerationStructureCreateInfoKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_CREATE_INFO_NV:
        StructPtrFromApiDump<VkAccelerationStructureCreateInfoNV>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_DEVICE_ADDRESS_INFO_KHR:
        StructPtrFromApiDump<VkAccelerationStructureDeviceAddressInfoKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_AABBS_DATA_KHR:
        StructPtrFromApiDump<VkAccelerationStructureGeometryAabbsDataKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_INSTANCES_DATA_KHR:
        StructPtrFromApiDump<VkAccelerationStructureGeometryInstancesDataKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_LINEAR_SWEPT_SPHERES_DATA_NV:
        StructPtrFromApiDump<VkAccelerationStructureGeometryLinearSweptSpheresDataNV>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_MICROMAP_DATA_KHR:
        StructPtrFromApiDump<VkAccelerationStructureGeometryMicromapDataKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_MOTION_TRIANGLES_DATA_NV:
        StructPtrFromApiDump<VkAccelerationStructureGeometryMotionTrianglesDataNV>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_SPHERES_DATA_NV:
        StructPtrFromApiDump<VkAccelerationStructureGeometrySpheresDataNV>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_TRIANGLES_DATA_KHR:
        StructPtrFromApiDump<VkAccelerationStructureGeometryTrianglesDataKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_INFO_NV:
        StructPtrFromApiDump<VkAccelerationStructureInfoNV>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_MEMORY_REQUIREMENTS_INFO_NV:
        StructPtrFromApiDump<VkAccelerationStructureMemoryRequirementsInfoNV>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_MOTION_INFO_NV:
        StructPtrFromApiDump<VkAccelerationStructureMotionInfoNV>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_TRIANGLES_DISPLACEMENT_MICROMAP_NV:
        StructPtrFromApiDump<VkAccelerationStructureTrianglesDisplacementMicromapNV>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_TRIANGLES_OPACITY_MICROMAP_EXT:
        StructPtrFromApiDump<VkAccelerationStructureTrianglesOpacityMicromapEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_TRIANGLES_OPACITY_MICROMAP_KHR:
        StructPtrFromApiDump<VkAccelerationStructureTrianglesOpacityMicromapKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_VERSION_INFO_KHR:
        StructPtrFromApiDump<VkAccelerationStructureVersionInfoKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_ACQUIRE_NEXT_IMAGE_INFO_KHR:
        StructPtrFromApiDump<VkAcquireNextImageInfoKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_ACQUIRE_PROFILING_LOCK_INFO_KHR:
        StructPtrFromApiDump<VkAcquireProfilingLockInfoKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_AMIGO_PROFILING_SUBMIT_INFO_SEC:
        StructPtrFromApiDump<VkAmigoProfilingSubmitInfoSEC>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_ANDROID_HARDWARE_BUFFER_FORMAT_PROPERTIES_2_ANDROID:
        StructPtrFromApiDump<VkAndroidHardwareBufferFormatProperties2ANDROID>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_ANDROID_HARDWARE_BUFFER_FORMAT_PROPERTIES_ANDROID:
        StructPtrFromApiDump<VkAndroidHardwareBufferFormatPropertiesANDROID>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_ANDROID_HARDWARE_BUFFER_FORMAT_RESOLVE_PROPERTIES_ANDROID:
        StructPtrFromApiDump<VkAndroidHardwareBufferFormatResolvePropertiesANDROID>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_ANDROID_HARDWARE_BUFFER_PROPERTIES_ANDROID:
        StructPtrFromApiDump<VkAndroidHardwareBufferPropertiesANDROID>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_ANDROID_HARDWARE_BUFFER_USAGE_ANDROID:
        StructPtrFromApiDump<VkAndroidHardwareBufferUsageANDROID>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_ANDROID_SURFACE_CREATE_INFO_KHR:
        StructPtrFromApiDump<VkAndroidSurfaceCreateInfoKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_ANTI_LAG_DATA_AMD:
        StructPtrFromApiDump<VkAntiLagDataAMD>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_ANTI_LAG_PRESENTATION_INFO_AMD:
        StructPtrFromApiDump<VkAntiLagPresentationInfoAMD>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_APPLICATION_INFO:
        StructPtrFromApiDump<VkApplicationInfo>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_ATTACHMENT_DESCRIPTION_2:
        StructPtrFromApiDump<VkAttachmentDescription2>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_ATTACHMENT_DESCRIPTION_STENCIL_LAYOUT:
        StructPtrFromApiDump<VkAttachmentDescriptionStencilLayout>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_ATTACHMENT_FEEDBACK_LOOP_INFO_EXT:
        StructPtrFromApiDump<VkAttachmentFeedbackLoopInfoEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_ATTACHMENT_REFERENCE_2:
        StructPtrFromApiDump<VkAttachmentReference2>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_ATTACHMENT_REFERENCE_STENCIL_LAYOUT:
        StructPtrFromApiDump<VkAttachmentReferenceStencilLayout>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_ATTACHMENT_SAMPLE_COUNT_INFO_AMD:
        StructPtrFromApiDump<VkAttachmentSampleCountInfoAMD>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_BEGIN_CUSTOM_RESOLVE_INFO_EXT:
        StructPtrFromApiDump<VkBeginCustomResolveInfoEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_BIND_ACCELERATION_STRUCTURE_MEMORY_INFO_NV:
        StructPtrFromApiDump<VkBindAccelerationStructureMemoryInfoNV>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_DEVICE_GROUP_INFO:
        StructPtrFromApiDump<VkBindBufferMemoryDeviceGroupInfo>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO:
        StructPtrFromApiDump<VkBindBufferMemoryInfo>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_BIND_DATA_GRAPH_PIPELINE_SESSION_MEMORY_INFO_ARM:
        StructPtrFromApiDump<VkBindDataGraphPipelineSessionMemoryInfoARM>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_BIND_DESCRIPTOR_BUFFER_EMBEDDED_SAMPLERS_INFO_EXT:
        StructPtrFromApiDump<VkBindDescriptorBufferEmbeddedSamplersInfoEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_BIND_DESCRIPTOR_SETS_INFO:
        StructPtrFromApiDump<VkBindDescriptorSetsInfo>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_BIND_IMAGE_MEMORY_DEVICE_GROUP_INFO:
        StructPtrFromApiDump<VkBindImageMemoryDeviceGroupInfo>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_BIND_IMAGE_MEMORY_INFO:
        StructPtrFromApiDump<VkBindImageMemoryInfo>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_BIND_IMAGE_MEMORY_SWAPCHAIN_INFO_KHR:
        StructPtrFromApiDump<VkBindImageMemorySwapchainInfoKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_BIND_IMAGE_PLANE_MEMORY_INFO:
        StructPtrFromApiDump<VkBindImagePlaneMemoryInfo>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_BIND_INDEX_BUFFER_3_INFO_KHR:
        StructPtrFromApiDump<VkBindIndexBuffer3InfoKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_BIND_MEMORY_STATUS:
        StructPtrFromApiDump<VkBindMemoryStatus>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_BIND_SPARSE_INFO:
        StructPtrFromApiDump<VkBindSparseInfo>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_BIND_TENSOR_MEMORY_INFO_ARM:
        StructPtrFromApiDump<VkBindTensorMemoryInfoARM>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_BIND_TRANSFORM_FEEDBACK_BUFFER_2_INFO_EXT:
        StructPtrFromApiDump<VkBindTransformFeedbackBuffer2InfoEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_BIND_VERTEX_BUFFER_3_INFO_KHR:
        StructPtrFromApiDump<VkBindVertexBuffer3InfoKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_BIND_VIDEO_SESSION_MEMORY_INFO_KHR:
        StructPtrFromApiDump<VkBindVideoSessionMemoryInfoKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_BLIT_IMAGE_CUBIC_WEIGHTS_INFO_QCOM:
        StructPtrFromApiDump<VkBlitImageCubicWeightsInfoQCOM>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_BLIT_IMAGE_INFO_2:
        StructPtrFromApiDump<VkBlitImageInfo2>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_BUFFER_CAPTURE_DESCRIPTOR_DATA_INFO_EXT:
        StructPtrFromApiDump<VkBufferCaptureDescriptorDataInfoEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_BUFFER_COPY_2:
        StructPtrFromApiDump<VkBufferCopy2>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO:
        StructPtrFromApiDump<VkBufferCreateInfo>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_BUFFER_DEVICE_ADDRESS_CREATE_INFO_EXT:
        StructPtrFromApiDump<VkBufferDeviceAddressCreateInfoEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_BUFFER_DEVICE_ADDRESS_INFO:
        StructPtrFromApiDump<VkBufferDeviceAddressInfo>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_BUFFER_IMAGE_COPY_2:
        StructPtrFromApiDump<VkBufferImageCopy2>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_BUFFER_MEMORY_BARRIER:
        StructPtrFromApiDump<VkBufferMemoryBarrier>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_BUFFER_MEMORY_BARRIER_2:
        StructPtrFromApiDump<VkBufferMemoryBarrier2>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_BUFFER_MEMORY_REQUIREMENTS_INFO_2:
        StructPtrFromApiDump<VkBufferMemoryRequirementsInfo2>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_BUFFER_OPAQUE_CAPTURE_ADDRESS_CREATE_INFO:
        StructPtrFromApiDump<VkBufferOpaqueCaptureAddressCreateInfo>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_BUFFER_USAGE_FLAGS_2_CREATE_INFO:
        StructPtrFromApiDump<VkBufferUsageFlags2CreateInfo>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_BUFFER_VIEW_CREATE_INFO:
        StructPtrFromApiDump<VkBufferViewCreateInfo>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_BUILD_PARTITIONED_ACCELERATION_STRUCTURE_INFO_NV:
        StructPtrFromApiDump<VkBuildPartitionedAccelerationStructureInfoNV>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_CALIBRATED_TIMESTAMP_INFO_KHR:
        StructPtrFromApiDump<VkCalibratedTimestampInfoKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_CHECKPOINT_DATA_2_NV:
        StructPtrFromApiDump<VkCheckpointData2NV>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_CHECKPOINT_DATA_NV:
        StructPtrFromApiDump<VkCheckpointDataNV>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO:
        StructPtrFromApiDump<VkCommandBufferAllocateInfo>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO:
        StructPtrFromApiDump<VkCommandBufferBeginInfo>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_COMMAND_BUFFER_INHERITANCE_CONDITIONAL_RENDERING_INFO_EXT:
        StructPtrFromApiDump<VkCommandBufferInheritanceConditionalRenderingInfoEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_COMMAND_BUFFER_INHERITANCE_INFO:
        StructPtrFromApiDump<VkCommandBufferInheritanceInfo>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_COMMAND_BUFFER_INHERITANCE_RENDER_PASS_TRANSFORM_INFO_QCOM:
        StructPtrFromApiDump<VkCommandBufferInheritanceRenderPassTransformInfoQCOM>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_COMMAND_BUFFER_INHERITANCE_RENDERING_INFO:
        StructPtrFromApiDump<VkCommandBufferInheritanceRenderingInfo>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_COMMAND_BUFFER_INHERITANCE_VIEWPORT_SCISSOR_INFO_NV:
        StructPtrFromApiDump<VkCommandBufferInheritanceViewportScissorInfoNV>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_COMMAND_BUFFER_SUBMIT_INFO:
        StructPtrFromApiDump<VkCommandBufferSubmitInfo>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO:
        StructPtrFromApiDump<VkCommandPoolCreateInfo>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_COMPUTE_OCCUPANCY_PRIORITY_PARAMETERS_NV:
        StructPtrFromApiDump<VkComputeOccupancyPriorityParametersNV>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_COMPUTE_PIPELINE_CREATE_INFO:
        StructPtrFromApiDump<VkComputePipelineCreateInfo>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_COMPUTE_PIPELINE_INDIRECT_BUFFER_INFO_NV:
        StructPtrFromApiDump<VkComputePipelineIndirectBufferInfoNV>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_CONDITIONAL_RENDERING_BEGIN_INFO_2_EXT:
        StructPtrFromApiDump<VkConditionalRenderingBeginInfo2EXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_CONDITIONAL_RENDERING_BEGIN_INFO_EXT:
        StructPtrFromApiDump<VkConditionalRenderingBeginInfoEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_CONVERT_COOPERATIVE_VECTOR_MATRIX_INFO_NV:
        StructPtrFromApiDump<VkConvertCooperativeVectorMatrixInfoNV>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_COOPERATIVE_MATRIX_FLEXIBLE_DIMENSIONS_PROPERTIES_NV:
        StructPtrFromApiDump<VkCooperativeMatrixFlexibleDimensionsPropertiesNV>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_COOPERATIVE_MATRIX_PROPERTIES_2_EXT:
        StructPtrFromApiDump<VkCooperativeMatrixProperties2EXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_COOPERATIVE_MATRIX_PROPERTIES_KHR:
        StructPtrFromApiDump<VkCooperativeMatrixPropertiesKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_COOPERATIVE_MATRIX_PROPERTIES_NV:
        StructPtrFromApiDump<VkCooperativeMatrixPropertiesNV>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_COOPERATIVE_VECTOR_PROPERTIES_NV:
        StructPtrFromApiDump<VkCooperativeVectorPropertiesNV>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_COPY_ACCELERATION_STRUCTURE_INFO_KHR:
        StructPtrFromApiDump<VkCopyAccelerationStructureInfoKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_COPY_ACCELERATION_STRUCTURE_TO_MEMORY_INFO_KHR:
        StructPtrFromApiDump<VkCopyAccelerationStructureToMemoryInfoKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_COPY_BUFFER_INFO_2:
        StructPtrFromApiDump<VkCopyBufferInfo2>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_COPY_BUFFER_TO_IMAGE_INFO_2:
        StructPtrFromApiDump<VkCopyBufferToImageInfo2>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_COPY_COMMAND_TRANSFORM_INFO_QCOM:
        StructPtrFromApiDump<VkCopyCommandTransformInfoQCOM>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_COPY_DESCRIPTOR_SET:
        StructPtrFromApiDump<VkCopyDescriptorSet>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_COPY_DEVICE_MEMORY_IMAGE_INFO_KHR:
        StructPtrFromApiDump<VkCopyDeviceMemoryImageInfoKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_COPY_DEVICE_MEMORY_INFO_KHR:
        StructPtrFromApiDump<VkCopyDeviceMemoryInfoKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_COPY_IMAGE_INFO_2:
        StructPtrFromApiDump<VkCopyImageInfo2>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_COPY_IMAGE_TO_BUFFER_INFO_2:
        StructPtrFromApiDump<VkCopyImageToBufferInfo2>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_COPY_IMAGE_TO_IMAGE_INFO:
        StructPtrFromApiDump<VkCopyImageToImageInfo>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_COPY_MEMORY_INDIRECT_INFO_KHR:
        StructPtrFromApiDump<VkCopyMemoryIndirectInfoKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_COPY_MEMORY_TO_ACCELERATION_STRUCTURE_INFO_KHR:
        StructPtrFromApiDump<VkCopyMemoryToAccelerationStructureInfoKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_COPY_MEMORY_TO_IMAGE_INDIRECT_INFO_KHR:
        StructPtrFromApiDump<VkCopyMemoryToImageIndirectInfoKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_COPY_MEMORY_TO_MICROMAP_INFO_EXT:
        StructPtrFromApiDump<VkCopyMemoryToMicromapInfoEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_COPY_MICROMAP_INFO_EXT:
        StructPtrFromApiDump<VkCopyMicromapInfoEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_COPY_MICROMAP_TO_MEMORY_INFO_EXT:
        StructPtrFromApiDump<VkCopyMicromapToMemoryInfoEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_COPY_TENSOR_INFO_ARM:
        StructPtrFromApiDump<VkCopyTensorInfoARM>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_CUSTOM_RESOLVE_CREATE_INFO_EXT:
        StructPtrFromApiDump<VkCustomResolveCreateInfoEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_D3D12_FENCE_SUBMIT_INFO_KHR:
        StructPtrFromApiDump<VkD3D12FenceSubmitInfoKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_DATA_GRAPH_OPTICAL_FLOW_IMAGE_FORMAT_INFO_ARM:
        StructPtrFromApiDump<VkDataGraphOpticalFlowImageFormatInfoARM>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_DATA_GRAPH_OPTICAL_FLOW_IMAGE_FORMAT_PROPERTIES_ARM:
        StructPtrFromApiDump<VkDataGraphOpticalFlowImageFormatPropertiesARM>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_DATA_GRAPH_PIPELINE_BUILTIN_MODEL_CREATE_INFO_QCOM:
        StructPtrFromApiDump<VkDataGraphPipelineBuiltinModelCreateInfoQCOM>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_DATA_GRAPH_PIPELINE_COMPILER_CONTROL_CREATE_INFO_ARM:
        StructPtrFromApiDump<VkDataGraphPipelineCompilerControlCreateInfoARM>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_DATA_GRAPH_PIPELINE_CONSTANT_TENSOR_SEMI_STRUCTURED_SPARSITY_INFO_ARM:
        StructPtrFromApiDump<VkDataGraphPipelineConstantTensorSemiStructuredSparsityInfoARM>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_DATA_GRAPH_PIPELINE_CREATE_INFO_ARM:
        StructPtrFromApiDump<VkDataGraphPipelineCreateInfoARM>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_DATA_GRAPH_PIPELINE_DISPATCH_INFO_ARM:
        StructPtrFromApiDump<VkDataGraphPipelineDispatchInfoARM>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_DATA_GRAPH_PIPELINE_IDENTIFIER_CREATE_INFO_ARM:
        StructPtrFromApiDump<VkDataGraphPipelineIdentifierCreateInfoARM>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_DATA_GRAPH_PIPELINE_INFO_ARM:
        StructPtrFromApiDump<VkDataGraphPipelineInfoARM>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_DATA_GRAPH_PIPELINE_NEURAL_STATISTICS_CREATE_INFO_ARM:
        StructPtrFromApiDump<VkDataGraphPipelineNeuralStatisticsCreateInfoARM>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_DATA_GRAPH_PIPELINE_OPTICAL_FLOW_CREATE_INFO_ARM:
        StructPtrFromApiDump<VkDataGraphPipelineOpticalFlowCreateInfoARM>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_DATA_GRAPH_PIPELINE_OPTICAL_FLOW_DISPATCH_INFO_ARM:
        StructPtrFromApiDump<VkDataGraphPipelineOpticalFlowDispatchInfoARM>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_DATA_GRAPH_PIPELINE_PROPERTY_QUERY_RESULT_ARM:
        StructPtrFromApiDump<VkDataGraphPipelinePropertyQueryResultARM>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_DATA_GRAPH_PIPELINE_RESOURCE_INFO_ARM:
        StructPtrFromApiDump<VkDataGraphPipelineResourceInfoARM>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_DATA_GRAPH_PIPELINE_RESOURCE_INFO_IMAGE_LAYOUT_ARM:
        StructPtrFromApiDump<VkDataGraphPipelineResourceInfoImageLayoutARM>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_DATA_GRAPH_PIPELINE_SESSION_BIND_POINT_REQUIREMENT_ARM:
        StructPtrFromApiDump<VkDataGraphPipelineSessionBindPointRequirementARM>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_DATA_GRAPH_PIPELINE_SESSION_BIND_POINT_REQUIREMENTS_INFO_ARM:
        StructPtrFromApiDump<VkDataGraphPipelineSessionBindPointRequirementsInfoARM>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_DATA_GRAPH_PIPELINE_SESSION_CREATE_INFO_ARM:
        StructPtrFromApiDump<VkDataGraphPipelineSessionCreateInfoARM>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_DATA_GRAPH_PIPELINE_SESSION_MEMORY_REQUIREMENTS_INFO_ARM:
        StructPtrFromApiDump<VkDataGraphPipelineSessionMemoryRequirementsInfoARM>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_DATA_GRAPH_PIPELINE_SESSION_NEURAL_STATISTICS_CREATE_INFO_ARM:
        StructPtrFromApiDump<VkDataGraphPipelineSessionNeuralStatisticsCreateInfoARM>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_DATA_GRAPH_PIPELINE_SHADER_MODULE_CREATE_INFO_ARM:
        StructPtrFromApiDump<VkDataGraphPipelineShaderModuleCreateInfoARM>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_DATA_GRAPH_PIPELINE_SINGLE_NODE_CONNECTION_ARM:
        StructPtrFromApiDump<VkDataGraphPipelineSingleNodeConnectionARM>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_DATA_GRAPH_PIPELINE_SINGLE_NODE_CREATE_INFO_ARM:
        StructPtrFromApiDump<VkDataGraphPipelineSingleNodeCreateInfoARM>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_DATA_GRAPH_PROCESSING_ENGINE_CREATE_INFO_ARM:
        StructPtrFromApiDump<VkDataGraphProcessingEngineCreateInfoARM>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_DEBUG_MARKER_MARKER_INFO_EXT:
        StructPtrFromApiDump<VkDebugMarkerMarkerInfoEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_DEBUG_MARKER_OBJECT_NAME_INFO_EXT:
        StructPtrFromApiDump<VkDebugMarkerObjectNameInfoEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_DEBUG_MARKER_OBJECT_TAG_INFO_EXT:
        StructPtrFromApiDump<VkDebugMarkerObjectTagInfoEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_DEBUG_REPORT_CALLBACK_CREATE_INFO_EXT:
        StructPtrFromApiDump<VkDebugReportCallbackCreateInfoEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_DEBUG_UTILS_LABEL_EXT:
        StructPtrFromApiDump<VkDebugUtilsLabelEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CALLBACK_DATA_EXT:
        StructPtrFromApiDump<VkDebugUtilsMessengerCallbackDataEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT:
        StructPtrFromApiDump<VkDebugUtilsMessengerCreateInfoEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT:
        StructPtrFromApiDump<VkDebugUtilsObjectNameInfoEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_TAG_INFO_EXT:
        StructPtrFromApiDump<VkDebugUtilsObjectTagInfoEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_DECOMPRESS_MEMORY_INFO_EXT:
        StructPtrFromApiDump<VkDecompressMemoryInfoEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_DEDICATED_ALLOCATION_BUFFER_CREATE_INFO_NV:
        StructPtrFromApiDump<VkDedicatedAllocationBufferCreateInfoNV>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_DEDICATED_ALLOCATION_IMAGE_CREATE_INFO_NV:
        StructPtrFromApiDump<VkDedicatedAllocationImageCreateInfoNV>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_DEDICATED_ALLOCATION_MEMORY_ALLOCATE_INFO_NV:
        StructPtrFromApiDump<VkDedicatedAllocationMemoryAllocateInfoNV>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_DEPENDENCY_INFO:
        StructPtrFromApiDump<VkDependencyInfo>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_DEPTH_BIAS_INFO_EXT:
        StructPtrFromApiDump<VkDepthBiasInfoEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_DEPTH_BIAS_REPRESENTATION_INFO_EXT:
        StructPtrFromApiDump<VkDepthBiasRepresentationInfoEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_DESCRIPTOR_ADDRESS_INFO_EXT:
        StructPtrFromApiDump<VkDescriptorAddressInfoEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_DESCRIPTOR_BUFFER_BINDING_INFO_EXT:
        StructPtrFromApiDump<VkDescriptorBufferBindingInfoEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_DESCRIPTOR_BUFFER_BINDING_PUSH_DESCRIPTOR_BUFFER_HANDLE_EXT:
        StructPtrFromApiDump<VkDescriptorBufferBindingPushDescriptorBufferHandleEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_DESCRIPTOR_GET_TENSOR_INFO_ARM:
        StructPtrFromApiDump<VkDescriptorGetTensorInfoARM>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO:
        StructPtrFromApiDump<VkDescriptorPoolCreateInfo>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_INLINE_UNIFORM_BLOCK_CREATE_INFO:
        StructPtrFromApiDump<VkDescriptorPoolInlineUniformBlockCreateInfo>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO:
        StructPtrFromApiDump<VkDescriptorSetAllocateInfo>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_DESCRIPTOR_SET_BINDING_REFERENCE_VALVE:
        StructPtrFromApiDump<VkDescriptorSetBindingReferenceVALVE>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_BINDING_FLAGS_CREATE_INFO:
        StructPtrFromApiDump<VkDescriptorSetLayoutBindingFlagsCreateInfo>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO:
        StructPtrFromApiDump<VkDescriptorSetLayoutCreateInfo>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_HOST_MAPPING_INFO_VALVE:
        StructPtrFromApiDump<VkDescriptorSetLayoutHostMappingInfoVALVE>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_SUPPORT:
        StructPtrFromApiDump<VkDescriptorSetLayoutSupport>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_DESCRIPTOR_SET_VARIABLE_DESCRIPTOR_COUNT_ALLOCATE_INFO:
        StructPtrFromApiDump<VkDescriptorSetVariableDescriptorCountAllocateInfo>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_DESCRIPTOR_SET_VARIABLE_DESCRIPTOR_COUNT_LAYOUT_SUPPORT:
        StructPtrFromApiDump<VkDescriptorSetVariableDescriptorCountLayoutSupport>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_DESCRIPTOR_UPDATE_TEMPLATE_CREATE_INFO:
        StructPtrFromApiDump<VkDescriptorUpdateTemplateCreateInfo>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_DEVICE_ADDRESS_BINDING_CALLBACK_DATA_EXT:
        StructPtrFromApiDump<VkDeviceAddressBindingCallbackDataEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_DEVICE_BUFFER_MEMORY_REQUIREMENTS:
        StructPtrFromApiDump<VkDeviceBufferMemoryRequirements>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO:
        StructPtrFromApiDump<VkDeviceCreateInfo>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_DEVICE_DEVICE_MEMORY_REPORT_CREATE_INFO_EXT:
        StructPtrFromApiDump<VkDeviceDeviceMemoryReportCreateInfoEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_DEVICE_DIAGNOSTICS_CONFIG_CREATE_INFO_NV:
        StructPtrFromApiDump<VkDeviceDiagnosticsConfigCreateInfoNV>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_DEVICE_EVENT_INFO_EXT:
        StructPtrFromApiDump<VkDeviceEventInfoEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_DEVICE_FAULT_COUNTS_EXT:
        StructPtrFromApiDump<VkDeviceFaultCountsEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_DEVICE_FAULT_DEBUG_INFO_KHR:
        StructPtrFromApiDump<VkDeviceFaultDebugInfoKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_DEVICE_FAULT_INFO_EXT:
        StructPtrFromApiDump<VkDeviceFaultInfoEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_DEVICE_FAULT_INFO_KHR:
        StructPtrFromApiDump<VkDeviceFaultInfoKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_DEVICE_FAULT_SHADER_ABORT_MESSAGE_INFO_KHR:
        StructPtrFromApiDump<VkDeviceFaultShaderAbortMessageInfoKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_DEVICE_GROUP_BIND_SPARSE_INFO:
        StructPtrFromApiDump<VkDeviceGroupBindSparseInfo>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_DEVICE_GROUP_COMMAND_BUFFER_BEGIN_INFO:
        StructPtrFromApiDump<VkDeviceGroupCommandBufferBeginInfo>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_DEVICE_GROUP_DEVICE_CREATE_INFO:
        StructPtrFromApiDump<VkDeviceGroupDeviceCreateInfo>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_DEVICE_GROUP_PRESENT_CAPABILITIES_KHR:
        StructPtrFromApiDump<VkDeviceGroupPresentCapabilitiesKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_DEVICE_GROUP_PRESENT_INFO_KHR:
        StructPtrFromApiDump<VkDeviceGroupPresentInfoKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_DEVICE_GROUP_RENDER_PASS_BEGIN_INFO:
        StructPtrFromApiDump<VkDeviceGroupRenderPassBeginInfo>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_DEVICE_GROUP_SUBMIT_INFO:
        StructPtrFromApiDump<VkDeviceGroupSubmitInfo>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_DEVICE_GROUP_SWAPCHAIN_CREATE_INFO_KHR:
        StructPtrFromApiDump<VkDeviceGroupSwapchainCreateInfoKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_DEVICE_IMAGE_MEMORY_REQUIREMENTS:
        StructPtrFromApiDump<VkDeviceImageMemoryRequirements>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_DEVICE_IMAGE_SUBRESOURCE_INFO:
        StructPtrFromApiDump<VkDeviceImageSubresourceInfo>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_DEVICE_MEMORY_COPY_KHR:
        StructPtrFromApiDump<VkDeviceMemoryCopyKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_DEVICE_MEMORY_IMAGE_COPY_KHR:
        StructPtrFromApiDump<VkDeviceMemoryImageCopyKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_DEVICE_MEMORY_OPAQUE_CAPTURE_ADDRESS_INFO:
        StructPtrFromApiDump<VkDeviceMemoryOpaqueCaptureAddressInfo>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_DEVICE_MEMORY_OVERALLOCATION_CREATE_INFO_AMD:
        StructPtrFromApiDump<VkDeviceMemoryOverallocationCreateInfoAMD>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_DEVICE_MEMORY_REPORT_CALLBACK_DATA_EXT:
        StructPtrFromApiDump<VkDeviceMemoryReportCallbackDataEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_DEVICE_PIPELINE_BINARY_INTERNAL_CACHE_CONTROL_KHR:
        StructPtrFromApiDump<VkDevicePipelineBinaryInternalCacheControlKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_DEVICE_PRIVATE_DATA_CREATE_INFO:
        StructPtrFromApiDump<VkDevicePrivateDataCreateInfo>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO:
        StructPtrFromApiDump<VkDeviceQueueCreateInfo>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_DEVICE_QUEUE_GLOBAL_PRIORITY_CREATE_INFO:
        StructPtrFromApiDump<VkDeviceQueueGlobalPriorityCreateInfo>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_DEVICE_QUEUE_INFO_2:
        StructPtrFromApiDump<VkDeviceQueueInfo2>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_DEVICE_QUEUE_SHADER_CORE_CONTROL_CREATE_INFO_ARM:
        StructPtrFromApiDump<VkDeviceQueueShaderCoreControlCreateInfoARM>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_DEVICE_TENSOR_MEMORY_REQUIREMENTS_ARM:
        StructPtrFromApiDump<VkDeviceTensorMemoryRequirementsARM>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_DIRECT_DRIVER_LOADING_INFO_LUNARG:
        StructPtrFromApiDump<VkDirectDriverLoadingInfoLUNARG>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_DIRECT_DRIVER_LOADING_LIST_LUNARG:
        StructPtrFromApiDump<VkDirectDriverLoadingListLUNARG>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_DIRECTFB_SURFACE_CREATE_INFO_EXT:
        StructPtrFromApiDump<VkDirectFBSurfaceCreateInfoEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_DISPATCH_INDIRECT_2_INFO_KHR:
        StructPtrFromApiDump<VkDispatchIndirect2InfoKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_DISPATCH_PARAMETERS_ARM:
        StructPtrFromApiDump<VkDispatchParametersARM>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_DISPATCH_TILE_INFO_QCOM:
        StructPtrFromApiDump<VkDispatchTileInfoQCOM>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_DISPLAY_EVENT_INFO_EXT:
        StructPtrFromApiDump<VkDisplayEventInfoEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_DISPLAY_MODE_CREATE_INFO_KHR:
        StructPtrFromApiDump<VkDisplayModeCreateInfoKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_DISPLAY_MODE_PROPERTIES_2_KHR:
        StructPtrFromApiDump<VkDisplayModeProperties2KHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_DISPLAY_MODE_STEREO_PROPERTIES_NV:
        StructPtrFromApiDump<VkDisplayModeStereoPropertiesNV>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_DISPLAY_NATIVE_HDR_SURFACE_CAPABILITIES_AMD:
        StructPtrFromApiDump<VkDisplayNativeHdrSurfaceCapabilitiesAMD>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_DISPLAY_PLANE_CAPABILITIES_2_KHR:
        StructPtrFromApiDump<VkDisplayPlaneCapabilities2KHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_DISPLAY_PLANE_INFO_2_KHR:
        StructPtrFromApiDump<VkDisplayPlaneInfo2KHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_DISPLAY_PLANE_PROPERTIES_2_KHR:
        StructPtrFromApiDump<VkDisplayPlaneProperties2KHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_DISPLAY_POWER_INFO_EXT:
        StructPtrFromApiDump<VkDisplayPowerInfoEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_DISPLAY_PRESENT_INFO_KHR:
        StructPtrFromApiDump<VkDisplayPresentInfoKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_DISPLAY_PROPERTIES_2_KHR:
        StructPtrFromApiDump<VkDisplayProperties2KHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_DISPLAY_SURFACE_CREATE_INFO_KHR:
        StructPtrFromApiDump<VkDisplaySurfaceCreateInfoKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_DISPLAY_SURFACE_STEREO_CREATE_INFO_NV:
        StructPtrFromApiDump<VkDisplaySurfaceStereoCreateInfoNV>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_DRAW_INDIRECT_2_INFO_KHR:
        StructPtrFromApiDump<VkDrawIndirect2InfoKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_DRAW_INDIRECT_COUNT_2_INFO_KHR:
        StructPtrFromApiDump<VkDrawIndirectCount2InfoKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_DRM_FORMAT_MODIFIER_PROPERTIES_LIST_2_EXT:
        StructPtrFromApiDump<VkDrmFormatModifierPropertiesList2EXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_DRM_FORMAT_MODIFIER_PROPERTIES_LIST_EXT:
        StructPtrFromApiDump<VkDrmFormatModifierPropertiesListEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_EVENT_CREATE_INFO:
        StructPtrFromApiDump<VkEventCreateInfo>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_EXPORT_FENCE_CREATE_INFO:
        StructPtrFromApiDump<VkExportFenceCreateInfo>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_EXPORT_FENCE_WIN32_HANDLE_INFO_KHR:
        StructPtrFromApiDump<VkExportFenceWin32HandleInfoKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_EXPORT_MEMORY_ALLOCATE_INFO:
        StructPtrFromApiDump<VkExportMemoryAllocateInfo>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_EXPORT_MEMORY_ALLOCATE_INFO_NV:
        StructPtrFromApiDump<VkExportMemoryAllocateInfoNV>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_EXPORT_MEMORY_WIN32_HANDLE_INFO_KHR:
        StructPtrFromApiDump<VkExportMemoryWin32HandleInfoKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_EXPORT_MEMORY_WIN32_HANDLE_INFO_NV:
        StructPtrFromApiDump<VkExportMemoryWin32HandleInfoNV>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_EXPORT_SEMAPHORE_CREATE_INFO:
        StructPtrFromApiDump<VkExportSemaphoreCreateInfo>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_EXPORT_SEMAPHORE_WIN32_HANDLE_INFO_KHR:
        StructPtrFromApiDump<VkExportSemaphoreWin32HandleInfoKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_EXTERNAL_BUFFER_PROPERTIES:
        StructPtrFromApiDump<VkExternalBufferProperties>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_EXTERNAL_FENCE_PROPERTIES:
        StructPtrFromApiDump<VkExternalFenceProperties>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_EXTERNAL_FORMAT_ANDROID:
        StructPtrFromApiDump<VkExternalFormatANDROID>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_EXTERNAL_IMAGE_FORMAT_PROPERTIES:
        StructPtrFromApiDump<VkExternalImageFormatProperties>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_EXTERNAL_MEMORY_ACQUIRE_UNMODIFIED_EXT:
        StructPtrFromApiDump<VkExternalMemoryAcquireUnmodifiedEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_EXTERNAL_MEMORY_BUFFER_CREATE_INFO:
        StructPtrFromApiDump<VkExternalMemoryBufferCreateInfo>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_EXTERNAL_MEMORY_IMAGE_CREATE_INFO:
        StructPtrFromApiDump<VkExternalMemoryImageCreateInfo>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_EXTERNAL_MEMORY_IMAGE_CREATE_INFO_NV:
        StructPtrFromApiDump<VkExternalMemoryImageCreateInfoNV>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_EXTERNAL_MEMORY_TENSOR_CREATE_INFO_ARM:
        StructPtrFromApiDump<VkExternalMemoryTensorCreateInfoARM>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_EXTERNAL_SEMAPHORE_PROPERTIES:
        StructPtrFromApiDump<VkExternalSemaphoreProperties>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_EXTERNAL_TENSOR_PROPERTIES_ARM:
        StructPtrFromApiDump<VkExternalTensorPropertiesARM>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_FENCE_CREATE_INFO:
        StructPtrFromApiDump<VkFenceCreateInfo>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_FENCE_GET_FD_INFO_KHR:
        StructPtrFromApiDump<VkFenceGetFdInfoKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_FENCE_GET_WIN32_HANDLE_INFO_KHR:
        StructPtrFromApiDump<VkFenceGetWin32HandleInfoKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_FILTER_CUBIC_IMAGE_VIEW_IMAGE_FORMAT_PROPERTIES_EXT:
        StructPtrFromApiDump<VkFilterCubicImageViewImageFormatPropertiesEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_FORMAT_PROPERTIES_2:
        StructPtrFromApiDump<VkFormatProperties2>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_FORMAT_PROPERTIES_3:
        StructPtrFromApiDump<VkFormatProperties3>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_FORMAT_PROPERTIES_4_KHR:
        StructPtrFromApiDump<VkFormatProperties4KHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_FRAGMENT_SHADING_RATE_ATTACHMENT_INFO_KHR:
        StructPtrFromApiDump<VkFragmentShadingRateAttachmentInfoKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_FRAME_BOUNDARY_EXT:
        StructPtrFromApiDump<VkFrameBoundaryEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_FRAME_BOUNDARY_TENSORS_ARM:
        StructPtrFromApiDump<VkFrameBoundaryTensorsARM>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_FRAMEBUFFER_ATTACHMENT_IMAGE_INFO:
        StructPtrFromApiDump<VkFramebufferAttachmentImageInfo>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_FRAMEBUFFER_ATTACHMENTS_CREATE_INFO:
        StructPtrFromApiDump<VkFramebufferAttachmentsCreateInfo>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO:
        StructPtrFromApiDump<VkFramebufferCreateInfo>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_FRAMEBUFFER_MIXED_SAMPLES_COMBINATION_NV:
        StructPtrFromApiDump<VkFramebufferMixedSamplesCombinationNV>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_GENERATED_COMMANDS_INFO_EXT:
        StructPtrFromApiDump<VkGeneratedCommandsInfoEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_GENERATED_COMMANDS_INFO_NV:
        StructPtrFromApiDump<VkGeneratedCommandsInfoNV>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_GENERATED_COMMANDS_MEMORY_REQUIREMENTS_INFO_EXT:
        StructPtrFromApiDump<VkGeneratedCommandsMemoryRequirementsInfoEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_GENERATED_COMMANDS_MEMORY_REQUIREMENTS_INFO_NV:
        StructPtrFromApiDump<VkGeneratedCommandsMemoryRequirementsInfoNV>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_GENERATED_COMMANDS_PIPELINE_INFO_EXT:
        StructPtrFromApiDump<VkGeneratedCommandsPipelineInfoEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_GENERATED_COMMANDS_SHADER_INFO_EXT:
        StructPtrFromApiDump<VkGeneratedCommandsShaderInfoEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_GEOMETRY_AABB_NV:
        StructPtrFromApiDump<VkGeometryAABBNV>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_GEOMETRY_NV:
        StructPtrFromApiDump<VkGeometryNV>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_GEOMETRY_TRIANGLES_NV:
        StructPtrFromApiDump<VkGeometryTrianglesNV>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_GET_LATENCY_MARKER_INFO_NV:
        StructPtrFromApiDump<VkGetLatencyMarkerInfoNV>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_GPA_DEVICE_CLOCK_MODE_INFO_AMD:
        StructPtrFromApiDump<VkGpaDeviceClockModeInfoAMD>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_GPA_DEVICE_GET_CLOCK_INFO_AMD:
        StructPtrFromApiDump<VkGpaDeviceGetClockInfoAMD>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_GPA_SAMPLE_BEGIN_INFO_AMD:
        StructPtrFromApiDump<VkGpaSampleBeginInfoAMD>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_GPA_SESSION_CREATE_INFO_AMD:
        StructPtrFromApiDump<VkGpaSessionCreateInfoAMD>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO:
        StructPtrFromApiDump<VkGraphicsPipelineCreateInfo>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_LIBRARY_CREATE_INFO_EXT:
        StructPtrFromApiDump<VkGraphicsPipelineLibraryCreateInfoEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_SHADER_GROUPS_CREATE_INFO_NV:
        StructPtrFromApiDump<VkGraphicsPipelineShaderGroupsCreateInfoNV>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_GRAPHICS_SHADER_GROUP_CREATE_INFO_NV:
        StructPtrFromApiDump<VkGraphicsShaderGroupCreateInfoNV>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_HDR_METADATA_EXT:
        StructPtrFromApiDump<VkHdrMetadataEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_HDR_VIVID_DYNAMIC_METADATA_HUAWEI:
        StructPtrFromApiDump<VkHdrVividDynamicMetadataHUAWEI>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_HEADLESS_SURFACE_CREATE_INFO_EXT:
        StructPtrFromApiDump<VkHeadlessSurfaceCreateInfoEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_HOST_IMAGE_COPY_DEVICE_PERFORMANCE_QUERY:
        StructPtrFromApiDump<VkHostImageCopyDevicePerformanceQuery>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_HOST_IMAGE_LAYOUT_TRANSITION_INFO:
        StructPtrFromApiDump<VkHostImageLayoutTransitionInfo>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_IOS_SURFACE_CREATE_INFO_MVK:
        StructPtrFromApiDump<VkIOSSurfaceCreateInfoMVK>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_IMAGE_ALIGNMENT_CONTROL_CREATE_INFO_MESA:
        StructPtrFromApiDump<VkImageAlignmentControlCreateInfoMESA>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_IMAGE_BLIT_2:
        StructPtrFromApiDump<VkImageBlit2>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_IMAGE_CAPTURE_DESCRIPTOR_DATA_INFO_EXT:
        StructPtrFromApiDump<VkImageCaptureDescriptorDataInfoEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_IMAGE_COMPRESSION_CONTROL_EXT:
        StructPtrFromApiDump<VkImageCompressionControlEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_IMAGE_COMPRESSION_PROPERTIES_EXT:
        StructPtrFromApiDump<VkImageCompressionPropertiesEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_IMAGE_COPY_2:
        StructPtrFromApiDump<VkImageCopy2>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_IMAGE_CREATE_FLAGS_2_CREATE_INFO_KHR:
        StructPtrFromApiDump<VkImageCreateFlags2CreateInfoKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO:
        StructPtrFromApiDump<VkImageCreateInfo>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_IMAGE_DRM_FORMAT_MODIFIER_EXPLICIT_CREATE_INFO_EXT:
        StructPtrFromApiDump<VkImageDrmFormatModifierExplicitCreateInfoEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_IMAGE_DRM_FORMAT_MODIFIER_LIST_CREATE_INFO_EXT:
        StructPtrFromApiDump<VkImageDrmFormatModifierListCreateInfoEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_IMAGE_DRM_FORMAT_MODIFIER_PROPERTIES_EXT:
        StructPtrFromApiDump<VkImageDrmFormatModifierPropertiesEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_IMAGE_FORMAT_LIST_CREATE_INFO:
        StructPtrFromApiDump<VkImageFormatListCreateInfo>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_IMAGE_FORMAT_PROPERTIES_2:
        StructPtrFromApiDump<VkImageFormatProperties2>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER:
        StructPtrFromApiDump<VkImageMemoryBarrier>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER_2:
        StructPtrFromApiDump<VkImageMemoryBarrier2>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_IMAGE_MEMORY_REQUIREMENTS_INFO_2:
        StructPtrFromApiDump<VkImageMemoryRequirementsInfo2>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_IMAGEPIPE_SURFACE_CREATE_INFO_FUCHSIA:
        StructPtrFromApiDump<VkImagePipeSurfaceCreateInfoFUCHSIA>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_IMAGE_PLANE_MEMORY_REQUIREMENTS_INFO:
        StructPtrFromApiDump<VkImagePlaneMemoryRequirementsInfo>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_IMAGE_RESOLVE_2:
        StructPtrFromApiDump<VkImageResolve2>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_IMAGE_SPARSE_MEMORY_REQUIREMENTS_INFO_2:
        StructPtrFromApiDump<VkImageSparseMemoryRequirementsInfo2>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_IMAGE_STENCIL_USAGE_2_CREATE_INFO_KHR:
        StructPtrFromApiDump<VkImageStencilUsage2CreateInfoKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_IMAGE_STENCIL_USAGE_CREATE_INFO:
        StructPtrFromApiDump<VkImageStencilUsageCreateInfo>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_IMAGE_SUBRESOURCE_2:
        StructPtrFromApiDump<VkImageSubresource2>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_IMAGE_SWAPCHAIN_CREATE_INFO_KHR:
        StructPtrFromApiDump<VkImageSwapchainCreateInfoKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_IMAGE_TILING_CONTROL_CREATE_INFO_EXT:
        StructPtrFromApiDump<VkImageTilingControlCreateInfoEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_IMAGE_USAGE_FLAGS_2_CREATE_INFO_KHR:
        StructPtrFromApiDump<VkImageUsageFlags2CreateInfoKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_IMAGE_VIEW_ASTC_DECODE_MODE_EXT:
        StructPtrFromApiDump<VkImageViewASTCDecodeModeEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_IMAGE_VIEW_ADDRESS_PROPERTIES_NVX:
        StructPtrFromApiDump<VkImageViewAddressPropertiesNVX>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_IMAGE_VIEW_CAPTURE_DESCRIPTOR_DATA_INFO_EXT:
        StructPtrFromApiDump<VkImageViewCaptureDescriptorDataInfoEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO:
        StructPtrFromApiDump<VkImageViewCreateInfo>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_IMAGE_VIEW_HANDLE_INFO_NVX:
        StructPtrFromApiDump<VkImageViewHandleInfoNVX>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_IMAGE_VIEW_MIN_LOD_CREATE_INFO_EXT:
        StructPtrFromApiDump<VkImageViewMinLodCreateInfoEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_IMAGE_VIEW_SAMPLE_WEIGHT_CREATE_INFO_QCOM:
        StructPtrFromApiDump<VkImageViewSampleWeightCreateInfoQCOM>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_IMAGE_VIEW_SLICED_CREATE_INFO_EXT:
        StructPtrFromApiDump<VkImageViewSlicedCreateInfoEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_IMAGE_VIEW_USAGE_2_CREATE_INFO_KHR:
        StructPtrFromApiDump<VkImageViewUsage2CreateInfoKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_IMAGE_VIEW_USAGE_CREATE_INFO:
        StructPtrFromApiDump<VkImageViewUsageCreateInfo>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_IMPORT_ANDROID_HARDWARE_BUFFER_INFO_ANDROID:
        StructPtrFromApiDump<VkImportAndroidHardwareBufferInfoANDROID>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_IMPORT_FENCE_FD_INFO_KHR:
        StructPtrFromApiDump<VkImportFenceFdInfoKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_IMPORT_FENCE_WIN32_HANDLE_INFO_KHR:
        StructPtrFromApiDump<VkImportFenceWin32HandleInfoKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_IMPORT_MEMORY_FD_INFO_KHR:
        StructPtrFromApiDump<VkImportMemoryFdInfoKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_IMPORT_MEMORY_HOST_POINTER_INFO_EXT:
        StructPtrFromApiDump<VkImportMemoryHostPointerInfoEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_IMPORT_MEMORY_METAL_HANDLE_INFO_EXT:
        StructPtrFromApiDump<VkImportMemoryMetalHandleInfoEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_IMPORT_MEMORY_WIN32_HANDLE_INFO_KHR:
        StructPtrFromApiDump<VkImportMemoryWin32HandleInfoKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_IMPORT_MEMORY_WIN32_HANDLE_INFO_NV:
        StructPtrFromApiDump<VkImportMemoryWin32HandleInfoNV>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_IMPORT_MEMORY_ZIRCON_HANDLE_INFO_FUCHSIA:
        StructPtrFromApiDump<VkImportMemoryZirconHandleInfoFUCHSIA>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_IMPORT_SEMAPHORE_FD_INFO_KHR:
        StructPtrFromApiDump<VkImportSemaphoreFdInfoKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_IMPORT_SEMAPHORE_WIN32_HANDLE_INFO_KHR:
        StructPtrFromApiDump<VkImportSemaphoreWin32HandleInfoKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_IMPORT_SEMAPHORE_ZIRCON_HANDLE_INFO_FUCHSIA:
        StructPtrFromApiDump<VkImportSemaphoreZirconHandleInfoFUCHSIA>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_INDIRECT_COMMANDS_LAYOUT_CREATE_INFO_EXT:
        StructPtrFromApiDump<VkIndirectCommandsLayoutCreateInfoEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_INDIRECT_COMMANDS_LAYOUT_CREATE_INFO_NV:
        StructPtrFromApiDump<VkIndirectCommandsLayoutCreateInfoNV>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_INDIRECT_COMMANDS_LAYOUT_TOKEN_NV:
        StructPtrFromApiDump<VkIndirectCommandsLayoutTokenNV>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_INDIRECT_EXECUTION_SET_PIPELINE_INFO_EXT:
        StructPtrFromApiDump<VkIndirectExecutionSetPipelineInfoEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_INDIRECT_EXECUTION_SET_SHADER_INFO_EXT:
        StructPtrFromApiDump<VkIndirectExecutionSetShaderInfoEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_INDIRECT_EXECUTION_SET_SHADER_LAYOUT_INFO_EXT:
        StructPtrFromApiDump<VkIndirectExecutionSetShaderLayoutInfoEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_INITIALIZE_PERFORMANCE_API_INFO_INTEL:
        StructPtrFromApiDump<VkInitializePerformanceApiInfoINTEL>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO:
        StructPtrFromApiDump<VkInstanceCreateInfo>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_LATENCY_SLEEP_INFO_NV:
        StructPtrFromApiDump<VkLatencySleepInfoNV>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_LATENCY_SLEEP_MODE_INFO_NV:
        StructPtrFromApiDump<VkLatencySleepModeInfoNV>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_LATENCY_SUBMISSION_PRESENT_ID_NV:
        StructPtrFromApiDump<VkLatencySubmissionPresentIdNV>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_LATENCY_SURFACE_CAPABILITIES_NV:
        StructPtrFromApiDump<VkLatencySurfaceCapabilitiesNV>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_LATENCY_TIMINGS_FRAME_REPORT_NV:
        StructPtrFromApiDump<VkLatencyTimingsFrameReportNV>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_LAYER_SETTINGS_CREATE_INFO_EXT:
        StructPtrFromApiDump<VkLayerSettingsCreateInfoEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_MACOS_SURFACE_CREATE_INFO_MVK:
        StructPtrFromApiDump<VkMacOSSurfaceCreateInfoMVK>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE:
        StructPtrFromApiDump<VkMappedMemoryRange>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO:
        StructPtrFromApiDump<VkMemoryAllocateFlagsInfo>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO:
        StructPtrFromApiDump<VkMemoryAllocateInfo>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_MEMORY_BARRIER:
        StructPtrFromApiDump<VkMemoryBarrier>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_MEMORY_BARRIER_2:
        StructPtrFromApiDump<VkMemoryBarrier2>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_MEMORY_BARRIER_ACCESS_FLAGS_3_KHR:
        StructPtrFromApiDump<VkMemoryBarrierAccessFlags3KHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_MEMORY_DEDICATED_ALLOCATE_INFO:
        StructPtrFromApiDump<VkMemoryDedicatedAllocateInfo>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_MEMORY_DEDICATED_ALLOCATE_INFO_TENSOR_ARM:
        StructPtrFromApiDump<VkMemoryDedicatedAllocateInfoTensorARM>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_MEMORY_DEDICATED_REQUIREMENTS:
        StructPtrFromApiDump<VkMemoryDedicatedRequirements>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_MEMORY_FD_PROPERTIES_KHR:
        StructPtrFromApiDump<VkMemoryFdPropertiesKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_MEMORY_GET_ANDROID_HARDWARE_BUFFER_INFO_ANDROID:
        StructPtrFromApiDump<VkMemoryGetAndroidHardwareBufferInfoANDROID>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_MEMORY_GET_FD_INFO_KHR:
        StructPtrFromApiDump<VkMemoryGetFdInfoKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_MEMORY_GET_METAL_HANDLE_INFO_EXT:
        StructPtrFromApiDump<VkMemoryGetMetalHandleInfoEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_MEMORY_GET_REMOTE_ADDRESS_INFO_NV:
        StructPtrFromApiDump<VkMemoryGetRemoteAddressInfoNV>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_MEMORY_GET_WIN32_HANDLE_INFO_KHR:
        StructPtrFromApiDump<VkMemoryGetWin32HandleInfoKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_MEMORY_GET_ZIRCON_HANDLE_INFO_FUCHSIA:
        StructPtrFromApiDump<VkMemoryGetZirconHandleInfoFUCHSIA>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_MEMORY_HOST_POINTER_PROPERTIES_EXT:
        StructPtrFromApiDump<VkMemoryHostPointerPropertiesEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_MEMORY_MAP_INFO:
        StructPtrFromApiDump<VkMemoryMapInfo>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_MEMORY_MAP_PLACED_INFO_EXT:
        StructPtrFromApiDump<VkMemoryMapPlacedInfoEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_MEMORY_MARKER_INFO_AMD:
        StructPtrFromApiDump<VkMemoryMarkerInfoAMD>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_MEMORY_METAL_HANDLE_PROPERTIES_EXT:
        StructPtrFromApiDump<VkMemoryMetalHandlePropertiesEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_MEMORY_OPAQUE_CAPTURE_ADDRESS_ALLOCATE_INFO:
        StructPtrFromApiDump<VkMemoryOpaqueCaptureAddressAllocateInfo>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_MEMORY_PRIORITY_ALLOCATE_INFO_EXT:
        StructPtrFromApiDump<VkMemoryPriorityAllocateInfoEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_MEMORY_RANGE_BARRIER_KHR:
        StructPtrFromApiDump<VkMemoryRangeBarrierKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_MEMORY_RANGE_BARRIERS_INFO_KHR:
        StructPtrFromApiDump<VkMemoryRangeBarriersInfoKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_MEMORY_REQUIREMENTS_2:
        StructPtrFromApiDump<VkMemoryRequirements2>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_MEMORY_UNMAP_INFO:
        StructPtrFromApiDump<VkMemoryUnmapInfo>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_MEMORY_WIN32_HANDLE_PROPERTIES_KHR:
        StructPtrFromApiDump<VkMemoryWin32HandlePropertiesKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_MEMORY_ZIRCON_HANDLE_PROPERTIES_FUCHSIA:
        StructPtrFromApiDump<VkMemoryZirconHandlePropertiesFUCHSIA>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_METAL_SURFACE_CREATE_INFO_EXT:
        StructPtrFromApiDump<VkMetalSurfaceCreateInfoEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_MICROMAP_BUILD_INFO_EXT:
        StructPtrFromApiDump<VkMicromapBuildInfoEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_MICROMAP_BUILD_SIZES_INFO_EXT:
        StructPtrFromApiDump<VkMicromapBuildSizesInfoEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_MICROMAP_CREATE_INFO_EXT:
        StructPtrFromApiDump<VkMicromapCreateInfoEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_MICROMAP_VERSION_INFO_EXT:
        StructPtrFromApiDump<VkMicromapVersionInfoEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_MULTISAMPLE_PROPERTIES_EXT:
        StructPtrFromApiDump<VkMultisamplePropertiesEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_MULTISAMPLED_RENDER_TO_SINGLE_SAMPLED_INFO_EXT:
        StructPtrFromApiDump<VkMultisampledRenderToSingleSampledInfoEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_MULTIVIEW_PER_VIEW_ATTRIBUTES_INFO_NVX:
        StructPtrFromApiDump<VkMultiviewPerViewAttributesInfoNVX>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_MULTIVIEW_PER_VIEW_RENDER_AREAS_RENDER_PASS_BEGIN_INFO_QCOM:
        StructPtrFromApiDump<VkMultiviewPerViewRenderAreasRenderPassBeginInfoQCOM>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_MUTABLE_DESCRIPTOR_TYPE_CREATE_INFO_EXT:
        StructPtrFromApiDump<VkMutableDescriptorTypeCreateInfoEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_OPAQUE_CAPTURE_DESCRIPTOR_DATA_CREATE_INFO_EXT:
        StructPtrFromApiDump<VkOpaqueCaptureDescriptorDataCreateInfoEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_OPTICAL_FLOW_EXECUTE_INFO_NV:
        StructPtrFromApiDump<VkOpticalFlowExecuteInfoNV>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_OPTICAL_FLOW_IMAGE_FORMAT_INFO_NV:
        StructPtrFromApiDump<VkOpticalFlowImageFormatInfoNV>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_OPTICAL_FLOW_IMAGE_FORMAT_PROPERTIES_NV:
        StructPtrFromApiDump<VkOpticalFlowImageFormatPropertiesNV>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_OPTICAL_FLOW_SESSION_CREATE_INFO_NV:
        StructPtrFromApiDump<VkOpticalFlowSessionCreateInfoNV>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_OPTICAL_FLOW_SESSION_CREATE_PRIVATE_DATA_INFO_NV:
        StructPtrFromApiDump<VkOpticalFlowSessionCreatePrivateDataInfoNV>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_OUT_OF_BAND_QUEUE_TYPE_INFO_NV:
        StructPtrFromApiDump<VkOutOfBandQueueTypeInfoNV>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PARTITIONED_ACCELERATION_STRUCTURE_FLAGS_NV:
        StructPtrFromApiDump<VkPartitionedAccelerationStructureFlagsNV>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PARTITIONED_ACCELERATION_STRUCTURE_INSTANCES_INPUT_NV:
        StructPtrFromApiDump<VkPartitionedAccelerationStructureInstancesInputNV>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PAST_PRESENTATION_TIMING_EXT:
        StructPtrFromApiDump<VkPastPresentationTimingEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PAST_PRESENTATION_TIMING_INFO_EXT:
        StructPtrFromApiDump<VkPastPresentationTimingInfoEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PAST_PRESENTATION_TIMING_PROPERTIES_EXT:
        StructPtrFromApiDump<VkPastPresentationTimingPropertiesEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PER_TILE_BEGIN_INFO_QCOM:
        StructPtrFromApiDump<VkPerTileBeginInfoQCOM>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PER_TILE_END_INFO_QCOM:
        StructPtrFromApiDump<VkPerTileEndInfoQCOM>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PERF_HINT_INFO_QCOM:
        StructPtrFromApiDump<VkPerfHintInfoQCOM>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PERFORMANCE_CONFIGURATION_ACQUIRE_INFO_INTEL:
        StructPtrFromApiDump<VkPerformanceConfigurationAcquireInfoINTEL>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PERFORMANCE_COUNTER_ARM:
        StructPtrFromApiDump<VkPerformanceCounterARM>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PERFORMANCE_COUNTER_DESCRIPTION_ARM:
        StructPtrFromApiDump<VkPerformanceCounterDescriptionARM>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PERFORMANCE_COUNTER_DESCRIPTION_KHR:
        StructPtrFromApiDump<VkPerformanceCounterDescriptionKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PERFORMANCE_COUNTER_KHR:
        StructPtrFromApiDump<VkPerformanceCounterKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PERFORMANCE_MARKER_INFO_INTEL:
        StructPtrFromApiDump<VkPerformanceMarkerInfoINTEL>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PERFORMANCE_OVERRIDE_INFO_INTEL:
        StructPtrFromApiDump<VkPerformanceOverrideInfoINTEL>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PERFORMANCE_QUERY_SUBMIT_INFO_KHR:
        StructPtrFromApiDump<VkPerformanceQuerySubmitInfoKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PERFORMANCE_STREAM_MARKER_INFO_INTEL:
        StructPtrFromApiDump<VkPerformanceStreamMarkerInfoINTEL>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_16BIT_STORAGE_FEATURES:
        StructPtrFromApiDump<VkPhysicalDevice16BitStorageFeatures>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_4444_FORMATS_FEATURES_EXT:
        StructPtrFromApiDump<VkPhysicalDevice4444FormatsFeaturesEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_8BIT_STORAGE_FEATURES:
        StructPtrFromApiDump<VkPhysicalDevice8BitStorageFeatures>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_ASTC_DECODE_FEATURES_EXT:
        StructPtrFromApiDump<VkPhysicalDeviceASTCDecodeFeaturesEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_ACCELERATION_STRUCTURE_FEATURES_KHR:
        StructPtrFromApiDump<VkPhysicalDeviceAccelerationStructureFeaturesKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_ACCELERATION_STRUCTURE_PROPERTIES_KHR:
        StructPtrFromApiDump<VkPhysicalDeviceAccelerationStructurePropertiesKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_ADDRESS_BINDING_REPORT_FEATURES_EXT:
        StructPtrFromApiDump<VkPhysicalDeviceAddressBindingReportFeaturesEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_AMIGO_PROFILING_FEATURES_SEC:
        StructPtrFromApiDump<VkPhysicalDeviceAmigoProfilingFeaturesSEC>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_ANTI_LAG_FEATURES_AMD:
        StructPtrFromApiDump<VkPhysicalDeviceAntiLagFeaturesAMD>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_ATTACHMENT_FEEDBACK_LOOP_DYNAMIC_STATE_FEATURES_EXT:
        StructPtrFromApiDump<VkPhysicalDeviceAttachmentFeedbackLoopDynamicStateFeaturesEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_ATTACHMENT_FEEDBACK_LOOP_LAYOUT_FEATURES_EXT:
        StructPtrFromApiDump<VkPhysicalDeviceAttachmentFeedbackLoopLayoutFeaturesEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_BLEND_OPERATION_ADVANCED_FEATURES_EXT:
        StructPtrFromApiDump<VkPhysicalDeviceBlendOperationAdvancedFeaturesEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_BLEND_OPERATION_ADVANCED_PROPERTIES_EXT:
        StructPtrFromApiDump<VkPhysicalDeviceBlendOperationAdvancedPropertiesEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_BORDER_COLOR_SWIZZLE_FEATURES_EXT:
        StructPtrFromApiDump<VkPhysicalDeviceBorderColorSwizzleFeaturesEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_BUFFER_DEVICE_ADDRESS_FEATURES:
        StructPtrFromApiDump<VkPhysicalDeviceBufferDeviceAddressFeatures>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_BUFFER_DEVICE_ADDRESS_FEATURES_EXT:
        StructPtrFromApiDump<VkPhysicalDeviceBufferDeviceAddressFeaturesEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_CLUSTER_CULLING_SHADER_FEATURES_HUAWEI:
        StructPtrFromApiDump<VkPhysicalDeviceClusterCullingShaderFeaturesHUAWEI>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_CLUSTER_CULLING_SHADER_PROPERTIES_HUAWEI:
        StructPtrFromApiDump<VkPhysicalDeviceClusterCullingShaderPropertiesHUAWEI>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_CLUSTER_CULLING_SHADER_VRS_FEATURES_HUAWEI:
        StructPtrFromApiDump<VkPhysicalDeviceClusterCullingShaderVrsFeaturesHUAWEI>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_COHERENT_MEMORY_FEATURES_AMD:
        StructPtrFromApiDump<VkPhysicalDeviceCoherentMemoryFeaturesAMD>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_COLOR_WRITE_ENABLE_FEATURES_EXT:
        StructPtrFromApiDump<VkPhysicalDeviceColorWriteEnableFeaturesEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_COMMAND_BUFFER_INHERITANCE_FEATURES_NV:
        StructPtrFromApiDump<VkPhysicalDeviceCommandBufferInheritanceFeaturesNV>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_COMPUTE_OCCUPANCY_PRIORITY_FEATURES_NV:
        StructPtrFromApiDump<VkPhysicalDeviceComputeOccupancyPriorityFeaturesNV>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_COMPUTE_SHADER_DERIVATIVES_FEATURES_KHR:
        StructPtrFromApiDump<VkPhysicalDeviceComputeShaderDerivativesFeaturesKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_COMPUTE_SHADER_DERIVATIVES_PROPERTIES_KHR:
        StructPtrFromApiDump<VkPhysicalDeviceComputeShaderDerivativesPropertiesKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_CONDITIONAL_RENDERING_FEATURES_EXT:
        StructPtrFromApiDump<VkPhysicalDeviceConditionalRenderingFeaturesEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_CONSERVATIVE_RASTERIZATION_PROPERTIES_EXT:
        StructPtrFromApiDump<VkPhysicalDeviceConservativeRasterizationPropertiesEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_COOPERATIVE_MATRIX_2_FEATURES_NV:
        StructPtrFromApiDump<VkPhysicalDeviceCooperativeMatrix2FeaturesNV>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_COOPERATIVE_MATRIX_2_PROPERTIES_NV:
        StructPtrFromApiDump<VkPhysicalDeviceCooperativeMatrix2PropertiesNV>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_COOPERATIVE_MATRIX_CONVERSION_FEATURES_QCOM:
        StructPtrFromApiDump<VkPhysicalDeviceCooperativeMatrixConversionFeaturesQCOM>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_COOPERATIVE_MATRIX_DECODE_VECTOR_FEATURES_NV:
        StructPtrFromApiDump<VkPhysicalDeviceCooperativeMatrixDecodeVectorFeaturesNV>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_COOPERATIVE_MATRIX_FEATURES_KHR:
        StructPtrFromApiDump<VkPhysicalDeviceCooperativeMatrixFeaturesKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_COOPERATIVE_MATRIX_FEATURES_NV:
        StructPtrFromApiDump<VkPhysicalDeviceCooperativeMatrixFeaturesNV>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_COOPERATIVE_MATRIX_INFO_2_EXT:
        StructPtrFromApiDump<VkPhysicalDeviceCooperativeMatrixInfo2EXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_COOPERATIVE_MATRIX_MAINTENANCE_1_FEATURES_EXT:
        StructPtrFromApiDump<VkPhysicalDeviceCooperativeMatrixMaintenance1FeaturesEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_COOPERATIVE_MATRIX_PROPERTIES_KHR:
        StructPtrFromApiDump<VkPhysicalDeviceCooperativeMatrixPropertiesKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_COOPERATIVE_MATRIX_PROPERTIES_NV:
        StructPtrFromApiDump<VkPhysicalDeviceCooperativeMatrixPropertiesNV>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_COOPERATIVE_VECTOR_FEATURES_NV:
        StructPtrFromApiDump<VkPhysicalDeviceCooperativeVectorFeaturesNV>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_COOPERATIVE_VECTOR_PROPERTIES_NV:
        StructPtrFromApiDump<VkPhysicalDeviceCooperativeVectorPropertiesNV>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_COPY_MEMORY_INDIRECT_FEATURES_KHR:
        StructPtrFromApiDump<VkPhysicalDeviceCopyMemoryIndirectFeaturesKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_COPY_MEMORY_INDIRECT_PROPERTIES_KHR:
        StructPtrFromApiDump<VkPhysicalDeviceCopyMemoryIndirectPropertiesKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_CORNER_SAMPLED_IMAGE_FEATURES_NV:
        StructPtrFromApiDump<VkPhysicalDeviceCornerSampledImageFeaturesNV>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_COVERAGE_REDUCTION_MODE_FEATURES_NV:
        StructPtrFromApiDump<VkPhysicalDeviceCoverageReductionModeFeaturesNV>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_CUBIC_CLAMP_FEATURES_QCOM:
        StructPtrFromApiDump<VkPhysicalDeviceCubicClampFeaturesQCOM>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_CUBIC_WEIGHTS_FEATURES_QCOM:
        StructPtrFromApiDump<VkPhysicalDeviceCubicWeightsFeaturesQCOM>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_CUSTOM_BORDER_COLOR_FEATURES_EXT:
        StructPtrFromApiDump<VkPhysicalDeviceCustomBorderColorFeaturesEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_CUSTOM_BORDER_COLOR_PROPERTIES_EXT:
        StructPtrFromApiDump<VkPhysicalDeviceCustomBorderColorPropertiesEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_CUSTOM_RESOLVE_FEATURES_EXT:
        StructPtrFromApiDump<VkPhysicalDeviceCustomResolveFeaturesEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DATA_GRAPH_FEATURES_ARM:
        StructPtrFromApiDump<VkPhysicalDeviceDataGraphFeaturesARM>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DATA_GRAPH_MODEL_FEATURES_QCOM:
        StructPtrFromApiDump<VkPhysicalDeviceDataGraphModelFeaturesQCOM>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DATA_GRAPH_NEURAL_ACCELERATOR_STATISTICS_FEATURES_ARM:
        StructPtrFromApiDump<VkPhysicalDeviceDataGraphNeuralAcceleratorStatisticsFeaturesARM>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DATA_GRAPH_OPTICAL_FLOW_FEATURES_ARM:
        StructPtrFromApiDump<VkPhysicalDeviceDataGraphOpticalFlowFeaturesARM>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DEDICATED_ALLOCATION_IMAGE_ALIASING_FEATURES_NV:
        StructPtrFromApiDump<VkPhysicalDeviceDedicatedAllocationImageAliasingFeaturesNV>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DEPTH_BIAS_CONTROL_FEATURES_EXT:
        StructPtrFromApiDump<VkPhysicalDeviceDepthBiasControlFeaturesEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DEPTH_CLAMP_CONTROL_FEATURES_EXT:
        StructPtrFromApiDump<VkPhysicalDeviceDepthClampControlFeaturesEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DEPTH_CLAMP_ZERO_ONE_FEATURES_KHR:
        StructPtrFromApiDump<VkPhysicalDeviceDepthClampZeroOneFeaturesKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DEPTH_CLIP_CONTROL_FEATURES_EXT:
        StructPtrFromApiDump<VkPhysicalDeviceDepthClipControlFeaturesEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DEPTH_CLIP_ENABLE_FEATURES_EXT:
        StructPtrFromApiDump<VkPhysicalDeviceDepthClipEnableFeaturesEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DEPTH_STENCIL_RESOLVE_PROPERTIES:
        StructPtrFromApiDump<VkPhysicalDeviceDepthStencilResolveProperties>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DESCRIPTOR_BUFFER_DENSITY_MAP_PROPERTIES_EXT:
        StructPtrFromApiDump<VkPhysicalDeviceDescriptorBufferDensityMapPropertiesEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DESCRIPTOR_BUFFER_FEATURES_EXT:
        StructPtrFromApiDump<VkPhysicalDeviceDescriptorBufferFeaturesEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DESCRIPTOR_BUFFER_PROPERTIES_EXT:
        StructPtrFromApiDump<VkPhysicalDeviceDescriptorBufferPropertiesEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DESCRIPTOR_BUFFER_TENSOR_FEATURES_ARM:
        StructPtrFromApiDump<VkPhysicalDeviceDescriptorBufferTensorFeaturesARM>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DESCRIPTOR_BUFFER_TENSOR_PROPERTIES_ARM:
        StructPtrFromApiDump<VkPhysicalDeviceDescriptorBufferTensorPropertiesARM>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DESCRIPTOR_INDEXING_FEATURES:
        StructPtrFromApiDump<VkPhysicalDeviceDescriptorIndexingFeatures>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DESCRIPTOR_INDEXING_PROPERTIES:
        StructPtrFromApiDump<VkPhysicalDeviceDescriptorIndexingProperties>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DESCRIPTOR_POOL_OVERALLOCATION_FEATURES_NV:
        StructPtrFromApiDump<VkPhysicalDeviceDescriptorPoolOverallocationFeaturesNV>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DESCRIPTOR_SET_HOST_MAPPING_FEATURES_VALVE:
        StructPtrFromApiDump<VkPhysicalDeviceDescriptorSetHostMappingFeaturesVALVE>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DEVICE_ADDRESS_COMMANDS_FEATURES_KHR:
        StructPtrFromApiDump<VkPhysicalDeviceDeviceAddressCommandsFeaturesKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DEVICE_GENERATED_COMMANDS_COMPUTE_FEATURES_NV:
        StructPtrFromApiDump<VkPhysicalDeviceDeviceGeneratedCommandsComputeFeaturesNV>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DEVICE_GENERATED_COMMANDS_FEATURES_EXT:
        StructPtrFromApiDump<VkPhysicalDeviceDeviceGeneratedCommandsFeaturesEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DEVICE_GENERATED_COMMANDS_FEATURES_NV:
        StructPtrFromApiDump<VkPhysicalDeviceDeviceGeneratedCommandsFeaturesNV>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DEVICE_GENERATED_COMMANDS_PROPERTIES_EXT:
        StructPtrFromApiDump<VkPhysicalDeviceDeviceGeneratedCommandsPropertiesEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DEVICE_GENERATED_COMMANDS_PROPERTIES_NV:
        StructPtrFromApiDump<VkPhysicalDeviceDeviceGeneratedCommandsPropertiesNV>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DEVICE_MEMORY_REPORT_FEATURES_EXT:
        StructPtrFromApiDump<VkPhysicalDeviceDeviceMemoryReportFeaturesEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DIAGNOSTICS_CONFIG_FEATURES_NV:
        StructPtrFromApiDump<VkPhysicalDeviceDiagnosticsConfigFeaturesNV>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DISCARD_RECTANGLE_PROPERTIES_EXT:
        StructPtrFromApiDump<VkPhysicalDeviceDiscardRectanglePropertiesEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DISPLACEMENT_MICROMAP_FEATURES_NV:
        StructPtrFromApiDump<VkPhysicalDeviceDisplacementMicromapFeaturesNV>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DISPLACEMENT_MICROMAP_PROPERTIES_NV:
        StructPtrFromApiDump<VkPhysicalDeviceDisplacementMicromapPropertiesNV>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DRIVER_PROPERTIES:
        StructPtrFromApiDump<VkPhysicalDeviceDriverProperties>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DRM_PROPERTIES_EXT:
        StructPtrFromApiDump<VkPhysicalDeviceDrmPropertiesEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DYNAMIC_RENDERING_FEATURES:
        StructPtrFromApiDump<VkPhysicalDeviceDynamicRenderingFeatures>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DYNAMIC_RENDERING_LOCAL_READ_FEATURES:
        StructPtrFromApiDump<VkPhysicalDeviceDynamicRenderingLocalReadFeatures>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DYNAMIC_RENDERING_UNUSED_ATTACHMENTS_FEATURES_EXT:
        StructPtrFromApiDump<VkPhysicalDeviceDynamicRenderingUnusedAttachmentsFeaturesEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_ELAPSED_TIMER_QUERY_FEATURES_QCOM:
        StructPtrFromApiDump<VkPhysicalDeviceElapsedTimerQueryFeaturesQCOM>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_EXCLUSIVE_SCISSOR_FEATURES_NV:
        StructPtrFromApiDump<VkPhysicalDeviceExclusiveScissorFeaturesNV>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_EXTENDED_DYNAMIC_STATE_2_FEATURES_EXT:
        StructPtrFromApiDump<VkPhysicalDeviceExtendedDynamicState2FeaturesEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_EXTENDED_DYNAMIC_STATE_3_FEATURES_EXT:
        StructPtrFromApiDump<VkPhysicalDeviceExtendedDynamicState3FeaturesEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_EXTENDED_DYNAMIC_STATE_3_PROPERTIES_EXT:
        StructPtrFromApiDump<VkPhysicalDeviceExtendedDynamicState3PropertiesEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_EXTENDED_DYNAMIC_STATE_FEATURES_EXT:
        StructPtrFromApiDump<VkPhysicalDeviceExtendedDynamicStateFeaturesEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_EXTENDED_FLAGS_FEATURES_KHR:
        StructPtrFromApiDump<VkPhysicalDeviceExtendedFlagsFeaturesKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_EXTENDED_SPARSE_ADDRESS_SPACE_FEATURES_NV:
        StructPtrFromApiDump<VkPhysicalDeviceExtendedSparseAddressSpaceFeaturesNV>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_EXTENDED_SPARSE_ADDRESS_SPACE_PROPERTIES_NV:
        StructPtrFromApiDump<VkPhysicalDeviceExtendedSparseAddressSpacePropertiesNV>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_EXTERNAL_BUFFER_INFO:
        StructPtrFromApiDump<VkPhysicalDeviceExternalBufferInfo>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_EXTERNAL_FENCE_INFO:
        StructPtrFromApiDump<VkPhysicalDeviceExternalFenceInfo>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_EXTERNAL_FORMAT_RESOLVE_FEATURES_ANDROID:
        StructPtrFromApiDump<VkPhysicalDeviceExternalFormatResolveFeaturesANDROID>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_EXTERNAL_FORMAT_RESOLVE_PROPERTIES_ANDROID:
        StructPtrFromApiDump<VkPhysicalDeviceExternalFormatResolvePropertiesANDROID>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_EXTERNAL_IMAGE_FORMAT_INFO:
        StructPtrFromApiDump<VkPhysicalDeviceExternalImageFormatInfo>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_EXTERNAL_MEMORY_HOST_PROPERTIES_EXT:
        StructPtrFromApiDump<VkPhysicalDeviceExternalMemoryHostPropertiesEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_EXTERNAL_MEMORY_RDMA_FEATURES_NV:
        StructPtrFromApiDump<VkPhysicalDeviceExternalMemoryRDMAFeaturesNV>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_EXTERNAL_SEMAPHORE_INFO:
        StructPtrFromApiDump<VkPhysicalDeviceExternalSemaphoreInfo>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_EXTERNAL_TENSOR_INFO_ARM:
        StructPtrFromApiDump<VkPhysicalDeviceExternalTensorInfoARM>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FAULT_FEATURES_EXT:
        StructPtrFromApiDump<VkPhysicalDeviceFaultFeaturesEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FAULT_FEATURES_KHR:
        StructPtrFromApiDump<VkPhysicalDeviceFaultFeaturesKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FAULT_PROPERTIES_KHR:
        StructPtrFromApiDump<VkPhysicalDeviceFaultPropertiesKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2:
        StructPtrFromApiDump<VkPhysicalDeviceFeatures2>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FLOAT_CONTROLS_PROPERTIES:
        StructPtrFromApiDump<VkPhysicalDeviceFloatControlsProperties>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FORMAT_PACK_FEATURES_ARM:
        StructPtrFromApiDump<VkPhysicalDeviceFormatPackFeaturesARM>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FRAGMENT_DENSITY_MAP_2_FEATURES_EXT:
        StructPtrFromApiDump<VkPhysicalDeviceFragmentDensityMap2FeaturesEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FRAGMENT_DENSITY_MAP_2_PROPERTIES_EXT:
        StructPtrFromApiDump<VkPhysicalDeviceFragmentDensityMap2PropertiesEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FRAGMENT_DENSITY_MAP_FEATURES_EXT:
        StructPtrFromApiDump<VkPhysicalDeviceFragmentDensityMapFeaturesEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FRAGMENT_DENSITY_MAP_LAYERED_FEATURES_VALVE:
        StructPtrFromApiDump<VkPhysicalDeviceFragmentDensityMapLayeredFeaturesVALVE>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FRAGMENT_DENSITY_MAP_LAYERED_PROPERTIES_VALVE:
        StructPtrFromApiDump<VkPhysicalDeviceFragmentDensityMapLayeredPropertiesVALVE>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FRAGMENT_DENSITY_MAP_OFFSET_FEATURES_EXT:
        StructPtrFromApiDump<VkPhysicalDeviceFragmentDensityMapOffsetFeaturesEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FRAGMENT_DENSITY_MAP_OFFSET_PROPERTIES_EXT:
        StructPtrFromApiDump<VkPhysicalDeviceFragmentDensityMapOffsetPropertiesEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FRAGMENT_DENSITY_MAP_PROPERTIES_EXT:
        StructPtrFromApiDump<VkPhysicalDeviceFragmentDensityMapPropertiesEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FRAGMENT_SHADER_BARYCENTRIC_FEATURES_KHR:
        StructPtrFromApiDump<VkPhysicalDeviceFragmentShaderBarycentricFeaturesKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FRAGMENT_SHADER_BARYCENTRIC_PROPERTIES_KHR:
        StructPtrFromApiDump<VkPhysicalDeviceFragmentShaderBarycentricPropertiesKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FRAGMENT_SHADER_INTERLOCK_FEATURES_EXT:
        StructPtrFromApiDump<VkPhysicalDeviceFragmentShaderInterlockFeaturesEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FRAGMENT_SHADING_RATE_ENUMS_FEATURES_NV:
        StructPtrFromApiDump<VkPhysicalDeviceFragmentShadingRateEnumsFeaturesNV>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FRAGMENT_SHADING_RATE_ENUMS_PROPERTIES_NV:
        StructPtrFromApiDump<VkPhysicalDeviceFragmentShadingRateEnumsPropertiesNV>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FRAGMENT_SHADING_RATE_FEATURES_KHR:
        StructPtrFromApiDump<VkPhysicalDeviceFragmentShadingRateFeaturesKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FRAGMENT_SHADING_RATE_KHR:
        StructPtrFromApiDump<VkPhysicalDeviceFragmentShadingRateKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FRAGMENT_SHADING_RATE_PROPERTIES_KHR:
        StructPtrFromApiDump<VkPhysicalDeviceFragmentShadingRatePropertiesKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FRAME_BOUNDARY_FEATURES_EXT:
        StructPtrFromApiDump<VkPhysicalDeviceFrameBoundaryFeaturesEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_GLOBAL_PRIORITY_QUERY_FEATURES:
        StructPtrFromApiDump<VkPhysicalDeviceGlobalPriorityQueryFeatures>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_GPA_FEATURES_AMD:
        StructPtrFromApiDump<VkPhysicalDeviceGpaFeaturesAMD>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_GPA_PROPERTIES_2_AMD:
        StructPtrFromApiDump<VkPhysicalDeviceGpaProperties2AMD>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_GPA_PROPERTIES_AMD:
        StructPtrFromApiDump<VkPhysicalDeviceGpaPropertiesAMD>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_GRAPHICS_PIPELINE_LIBRARY_FEATURES_EXT:
        StructPtrFromApiDump<VkPhysicalDeviceGraphicsPipelineLibraryFeaturesEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_GRAPHICS_PIPELINE_LIBRARY_PROPERTIES_EXT:
        StructPtrFromApiDump<VkPhysicalDeviceGraphicsPipelineLibraryPropertiesEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_GROUP_PROPERTIES:
        StructPtrFromApiDump<VkPhysicalDeviceGroupProperties>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_HDR_VIVID_FEATURES_HUAWEI:
        StructPtrFromApiDump<VkPhysicalDeviceHdrVividFeaturesHUAWEI>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_HOST_IMAGE_COPY_FEATURES:
        StructPtrFromApiDump<VkPhysicalDeviceHostImageCopyFeatures>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_HOST_IMAGE_COPY_PROPERTIES:
        StructPtrFromApiDump<VkPhysicalDeviceHostImageCopyProperties>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_HOST_QUERY_RESET_FEATURES:
        StructPtrFromApiDump<VkPhysicalDeviceHostQueryResetFeatures>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_ID_PROPERTIES:
        StructPtrFromApiDump<VkPhysicalDeviceIDProperties>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_IMAGE_2D_VIEW_OF_3D_FEATURES_EXT:
        StructPtrFromApiDump<VkPhysicalDeviceImage2DViewOf3DFeaturesEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_IMAGE_ALIGNMENT_CONTROL_FEATURES_MESA:
        StructPtrFromApiDump<VkPhysicalDeviceImageAlignmentControlFeaturesMESA>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_IMAGE_ALIGNMENT_CONTROL_PROPERTIES_MESA:
        StructPtrFromApiDump<VkPhysicalDeviceImageAlignmentControlPropertiesMESA>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_IMAGE_COMPRESSION_CONTROL_FEATURES_EXT:
        StructPtrFromApiDump<VkPhysicalDeviceImageCompressionControlFeaturesEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_IMAGE_COMPRESSION_CONTROL_SWAPCHAIN_FEATURES_EXT:
        StructPtrFromApiDump<VkPhysicalDeviceImageCompressionControlSwapchainFeaturesEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_IMAGE_DRM_FORMAT_MODIFIER_INFO_EXT:
        StructPtrFromApiDump<VkPhysicalDeviceImageDrmFormatModifierInfoEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_IMAGE_FORMAT_INFO_2:
        StructPtrFromApiDump<VkPhysicalDeviceImageFormatInfo2>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_IMAGE_PROCESSING_2_FEATURES_QCOM:
        StructPtrFromApiDump<VkPhysicalDeviceImageProcessing2FeaturesQCOM>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_IMAGE_PROCESSING_2_PROPERTIES_QCOM:
        StructPtrFromApiDump<VkPhysicalDeviceImageProcessing2PropertiesQCOM>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_IMAGE_PROCESSING_3_FEATURES_QCOM:
        StructPtrFromApiDump<VkPhysicalDeviceImageProcessing3FeaturesQCOM>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_IMAGE_PROCESSING_FEATURES_QCOM:
        StructPtrFromApiDump<VkPhysicalDeviceImageProcessingFeaturesQCOM>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_IMAGE_PROCESSING_PROPERTIES_QCOM:
        StructPtrFromApiDump<VkPhysicalDeviceImageProcessingPropertiesQCOM>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_IMAGE_ROBUSTNESS_FEATURES:
        StructPtrFromApiDump<VkPhysicalDeviceImageRobustnessFeatures>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_IMAGE_SLICED_VIEW_OF_3D_FEATURES_EXT:
        StructPtrFromApiDump<VkPhysicalDeviceImageSlicedViewOf3DFeaturesEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_IMAGE_TILING_CONTROL_FEATURES_EXT:
        StructPtrFromApiDump<VkPhysicalDeviceImageTilingControlFeaturesEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_IMAGE_VIEW_IMAGE_FORMAT_INFO_EXT:
        StructPtrFromApiDump<VkPhysicalDeviceImageViewImageFormatInfoEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_IMAGE_VIEW_MIN_LOD_FEATURES_EXT:
        StructPtrFromApiDump<VkPhysicalDeviceImageViewMinLodFeaturesEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_IMAGELESS_FRAMEBUFFER_FEATURES:
        StructPtrFromApiDump<VkPhysicalDeviceImagelessFramebufferFeatures>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_INDEX_TYPE_UINT8_FEATURES:
        StructPtrFromApiDump<VkPhysicalDeviceIndexTypeUint8Features>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_INHERITED_VIEWPORT_SCISSOR_FEATURES_NV:
        StructPtrFromApiDump<VkPhysicalDeviceInheritedViewportScissorFeaturesNV>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_INLINE_UNIFORM_BLOCK_FEATURES:
        StructPtrFromApiDump<VkPhysicalDeviceInlineUniformBlockFeatures>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_INLINE_UNIFORM_BLOCK_PROPERTIES:
        StructPtrFromApiDump<VkPhysicalDeviceInlineUniformBlockProperties>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_INTERNALLY_SYNCHRONIZED_QUEUES_FEATURES_KHR:
        StructPtrFromApiDump<VkPhysicalDeviceInternallySynchronizedQueuesFeaturesKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_INVOCATION_MASK_FEATURES_HUAWEI:
        StructPtrFromApiDump<VkPhysicalDeviceInvocationMaskFeaturesHUAWEI>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_LAYERED_API_PROPERTIES_KHR:
        StructPtrFromApiDump<VkPhysicalDeviceLayeredApiPropertiesKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_LAYERED_API_PROPERTIES_LIST_KHR:
        StructPtrFromApiDump<VkPhysicalDeviceLayeredApiPropertiesListKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_LAYERED_API_VULKAN_PROPERTIES_KHR:
        StructPtrFromApiDump<VkPhysicalDeviceLayeredApiVulkanPropertiesKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_LAYERED_DRIVER_PROPERTIES_MSFT:
        StructPtrFromApiDump<VkPhysicalDeviceLayeredDriverPropertiesMSFT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_LEGACY_DITHERING_FEATURES_EXT:
        StructPtrFromApiDump<VkPhysicalDeviceLegacyDitheringFeaturesEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_LEGACY_VERTEX_ATTRIBUTES_FEATURES_EXT:
        StructPtrFromApiDump<VkPhysicalDeviceLegacyVertexAttributesFeaturesEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_LEGACY_VERTEX_ATTRIBUTES_PROPERTIES_EXT:
        StructPtrFromApiDump<VkPhysicalDeviceLegacyVertexAttributesPropertiesEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_LINE_RASTERIZATION_FEATURES:
        StructPtrFromApiDump<VkPhysicalDeviceLineRasterizationFeatures>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_LINE_RASTERIZATION_PROPERTIES:
        StructPtrFromApiDump<VkPhysicalDeviceLineRasterizationProperties>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_LINEAR_COLOR_ATTACHMENT_FEATURES_NV:
        StructPtrFromApiDump<VkPhysicalDeviceLinearColorAttachmentFeaturesNV>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MAINTENANCE_10_FEATURES_KHR:
        StructPtrFromApiDump<VkPhysicalDeviceMaintenance10FeaturesKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MAINTENANCE_10_PROPERTIES_KHR:
        StructPtrFromApiDump<VkPhysicalDeviceMaintenance10PropertiesKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MAINTENANCE_11_FEATURES_KHR:
        StructPtrFromApiDump<VkPhysicalDeviceMaintenance11FeaturesKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MAINTENANCE_3_PROPERTIES:
        StructPtrFromApiDump<VkPhysicalDeviceMaintenance3Properties>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MAINTENANCE_4_FEATURES:
        StructPtrFromApiDump<VkPhysicalDeviceMaintenance4Features>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MAINTENANCE_4_PROPERTIES:
        StructPtrFromApiDump<VkPhysicalDeviceMaintenance4Properties>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MAINTENANCE_5_FEATURES:
        StructPtrFromApiDump<VkPhysicalDeviceMaintenance5Features>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MAINTENANCE_5_PROPERTIES:
        StructPtrFromApiDump<VkPhysicalDeviceMaintenance5Properties>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MAINTENANCE_6_FEATURES:
        StructPtrFromApiDump<VkPhysicalDeviceMaintenance6Features>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MAINTENANCE_6_PROPERTIES:
        StructPtrFromApiDump<VkPhysicalDeviceMaintenance6Properties>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MAINTENANCE_7_FEATURES_KHR:
        StructPtrFromApiDump<VkPhysicalDeviceMaintenance7FeaturesKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MAINTENANCE_7_PROPERTIES_KHR:
        StructPtrFromApiDump<VkPhysicalDeviceMaintenance7PropertiesKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MAINTENANCE_8_FEATURES_KHR:
        StructPtrFromApiDump<VkPhysicalDeviceMaintenance8FeaturesKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MAINTENANCE_9_FEATURES_KHR:
        StructPtrFromApiDump<VkPhysicalDeviceMaintenance9FeaturesKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MAINTENANCE_9_PROPERTIES_KHR:
        StructPtrFromApiDump<VkPhysicalDeviceMaintenance9PropertiesKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MAP_MEMORY_PLACED_FEATURES_EXT:
        StructPtrFromApiDump<VkPhysicalDeviceMapMemoryPlacedFeaturesEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MAP_MEMORY_PLACED_PROPERTIES_EXT:
        StructPtrFromApiDump<VkPhysicalDeviceMapMemoryPlacedPropertiesEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MEMORY_BUDGET_PROPERTIES_EXT:
        StructPtrFromApiDump<VkPhysicalDeviceMemoryBudgetPropertiesEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MEMORY_DECOMPRESSION_FEATURES_EXT:
        StructPtrFromApiDump<VkPhysicalDeviceMemoryDecompressionFeaturesEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MEMORY_DECOMPRESSION_PROPERTIES_EXT:
        StructPtrFromApiDump<VkPhysicalDeviceMemoryDecompressionPropertiesEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MEMORY_PRIORITY_FEATURES_EXT:
        StructPtrFromApiDump<VkPhysicalDeviceMemoryPriorityFeaturesEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MEMORY_PROPERTIES_2:
        StructPtrFromApiDump<VkPhysicalDeviceMemoryProperties2>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MESH_SHADER_FEATURES_EXT:
        StructPtrFromApiDump<VkPhysicalDeviceMeshShaderFeaturesEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MESH_SHADER_FEATURES_NV:
        StructPtrFromApiDump<VkPhysicalDeviceMeshShaderFeaturesNV>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MESH_SHADER_PROPERTIES_EXT:
        StructPtrFromApiDump<VkPhysicalDeviceMeshShaderPropertiesEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MESH_SHADER_PROPERTIES_NV:
        StructPtrFromApiDump<VkPhysicalDeviceMeshShaderPropertiesNV>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MULTI_DRAW_FEATURES_EXT:
        StructPtrFromApiDump<VkPhysicalDeviceMultiDrawFeaturesEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MULTI_DRAW_PROPERTIES_EXT:
        StructPtrFromApiDump<VkPhysicalDeviceMultiDrawPropertiesEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MULTISAMPLED_RENDER_TO_SINGLE_SAMPLED_FEATURES_EXT:
        StructPtrFromApiDump<VkPhysicalDeviceMultisampledRenderToSingleSampledFeaturesEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MULTISAMPLED_RENDER_TO_SWAPCHAIN_FEATURES_EXT:
        StructPtrFromApiDump<VkPhysicalDeviceMultisampledRenderToSwapchainFeaturesEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MULTIVIEW_FEATURES:
        StructPtrFromApiDump<VkPhysicalDeviceMultiviewFeatures>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MULTIVIEW_PER_VIEW_ATTRIBUTES_PROPERTIES_NVX:
        StructPtrFromApiDump<VkPhysicalDeviceMultiviewPerViewAttributesPropertiesNVX>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MULTIVIEW_PER_VIEW_RENDER_AREAS_FEATURES_QCOM:
        StructPtrFromApiDump<VkPhysicalDeviceMultiviewPerViewRenderAreasFeaturesQCOM>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MULTIVIEW_PER_VIEW_VIEWPORTS_FEATURES_QCOM:
        StructPtrFromApiDump<VkPhysicalDeviceMultiviewPerViewViewportsFeaturesQCOM>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MULTIVIEW_PROPERTIES:
        StructPtrFromApiDump<VkPhysicalDeviceMultiviewProperties>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MUTABLE_DESCRIPTOR_TYPE_FEATURES_EXT:
        StructPtrFromApiDump<VkPhysicalDeviceMutableDescriptorTypeFeaturesEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_NESTED_COMMAND_BUFFER_FEATURES_EXT:
        StructPtrFromApiDump<VkPhysicalDeviceNestedCommandBufferFeaturesEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_NESTED_COMMAND_BUFFER_PROPERTIES_EXT:
        StructPtrFromApiDump<VkPhysicalDeviceNestedCommandBufferPropertiesEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_NON_SEAMLESS_CUBE_MAP_FEATURES_EXT:
        StructPtrFromApiDump<VkPhysicalDeviceNonSeamlessCubeMapFeaturesEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_OPACITY_MICROMAP_FEATURES_EXT:
        StructPtrFromApiDump<VkPhysicalDeviceOpacityMicromapFeaturesEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_OPACITY_MICROMAP_FEATURES_KHR:
        StructPtrFromApiDump<VkPhysicalDeviceOpacityMicromapFeaturesKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_OPACITY_MICROMAP_PROPERTIES_EXT:
        StructPtrFromApiDump<VkPhysicalDeviceOpacityMicromapPropertiesEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_OPACITY_MICROMAP_PROPERTIES_KHR:
        StructPtrFromApiDump<VkPhysicalDeviceOpacityMicromapPropertiesKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_OPTICAL_FLOW_FEATURES_NV:
        StructPtrFromApiDump<VkPhysicalDeviceOpticalFlowFeaturesNV>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_OPTICAL_FLOW_PROPERTIES_NV:
        StructPtrFromApiDump<VkPhysicalDeviceOpticalFlowPropertiesNV>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PCI_BUS_INFO_PROPERTIES_EXT:
        StructPtrFromApiDump<VkPhysicalDevicePCIBusInfoPropertiesEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PAGEABLE_DEVICE_LOCAL_MEMORY_FEATURES_EXT:
        StructPtrFromApiDump<VkPhysicalDevicePageableDeviceLocalMemoryFeaturesEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PARTITIONED_ACCELERATION_STRUCTURE_FEATURES_NV:
        StructPtrFromApiDump<VkPhysicalDevicePartitionedAccelerationStructureFeaturesNV>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PARTITIONED_ACCELERATION_STRUCTURE_PROPERTIES_NV:
        StructPtrFromApiDump<VkPhysicalDevicePartitionedAccelerationStructurePropertiesNV>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PER_STAGE_DESCRIPTOR_SET_FEATURES_NV:
        StructPtrFromApiDump<VkPhysicalDevicePerStageDescriptorSetFeaturesNV>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PERFORMANCE_COUNTERS_BY_REGION_FEATURES_ARM:
        StructPtrFromApiDump<VkPhysicalDevicePerformanceCountersByRegionFeaturesARM>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PERFORMANCE_COUNTERS_BY_REGION_PROPERTIES_ARM:
        StructPtrFromApiDump<VkPhysicalDevicePerformanceCountersByRegionPropertiesARM>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PERFORMANCE_QUERY_FEATURES_KHR:
        StructPtrFromApiDump<VkPhysicalDevicePerformanceQueryFeaturesKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PERFORMANCE_QUERY_PROPERTIES_KHR:
        StructPtrFromApiDump<VkPhysicalDevicePerformanceQueryPropertiesKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PIPELINE_BINARY_FEATURES_KHR:
        StructPtrFromApiDump<VkPhysicalDevicePipelineBinaryFeaturesKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PIPELINE_BINARY_PROPERTIES_KHR:
        StructPtrFromApiDump<VkPhysicalDevicePipelineBinaryPropertiesKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PIPELINE_CACHE_INCREMENTAL_MODE_FEATURES_SEC:
        StructPtrFromApiDump<VkPhysicalDevicePipelineCacheIncrementalModeFeaturesSEC>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PIPELINE_CREATION_CACHE_CONTROL_FEATURES:
        StructPtrFromApiDump<VkPhysicalDevicePipelineCreationCacheControlFeatures>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PIPELINE_EXECUTABLE_PROPERTIES_FEATURES_KHR:
        StructPtrFromApiDump<VkPhysicalDevicePipelineExecutablePropertiesFeaturesKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PIPELINE_LIBRARY_GROUP_HANDLES_FEATURES_EXT:
        StructPtrFromApiDump<VkPhysicalDevicePipelineLibraryGroupHandlesFeaturesEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PIPELINE_OPACITY_MICROMAP_FEATURES_ARM:
        StructPtrFromApiDump<VkPhysicalDevicePipelineOpacityMicromapFeaturesARM>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PIPELINE_PROTECTED_ACCESS_FEATURES:
        StructPtrFromApiDump<VkPhysicalDevicePipelineProtectedAccessFeatures>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PIPELINE_ROBUSTNESS_FEATURES:
        StructPtrFromApiDump<VkPhysicalDevicePipelineRobustnessFeatures>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PIPELINE_ROBUSTNESS_PROPERTIES:
        StructPtrFromApiDump<VkPhysicalDevicePipelineRobustnessProperties>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_POINT_CLIPPING_PROPERTIES:
        StructPtrFromApiDump<VkPhysicalDevicePointClippingProperties>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PORTABILITY_SUBSET_FEATURES_KHR:
        StructPtrFromApiDump<VkPhysicalDevicePortabilitySubsetFeaturesKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PORTABILITY_SUBSET_PROPERTIES_KHR:
        StructPtrFromApiDump<VkPhysicalDevicePortabilitySubsetPropertiesKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PRESENT_BARRIER_FEATURES_NV:
        StructPtrFromApiDump<VkPhysicalDevicePresentBarrierFeaturesNV>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PRESENT_ID_2_FEATURES_KHR:
        StructPtrFromApiDump<VkPhysicalDevicePresentId2FeaturesKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PRESENT_ID_FEATURES_KHR:
        StructPtrFromApiDump<VkPhysicalDevicePresentIdFeaturesKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PRESENT_METERING_FEATURES_NV:
        StructPtrFromApiDump<VkPhysicalDevicePresentMeteringFeaturesNV>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PRESENT_MODE_FIFO_LATEST_READY_FEATURES_KHR:
        StructPtrFromApiDump<VkPhysicalDevicePresentModeFifoLatestReadyFeaturesKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PRESENT_TIMING_FEATURES_EXT:
        StructPtrFromApiDump<VkPhysicalDevicePresentTimingFeaturesEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PRESENT_WAIT_2_FEATURES_KHR:
        StructPtrFromApiDump<VkPhysicalDevicePresentWait2FeaturesKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PRESENT_WAIT_FEATURES_KHR:
        StructPtrFromApiDump<VkPhysicalDevicePresentWaitFeaturesKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PRIMITIVE_RESTART_INDEX_FEATURES_EXT:
        StructPtrFromApiDump<VkPhysicalDevicePrimitiveRestartIndexFeaturesEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PRIMITIVE_TOPOLOGY_LIST_RESTART_FEATURES_EXT:
        StructPtrFromApiDump<VkPhysicalDevicePrimitiveTopologyListRestartFeaturesEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PRIMITIVES_GENERATED_QUERY_FEATURES_EXT:
        StructPtrFromApiDump<VkPhysicalDevicePrimitivesGeneratedQueryFeaturesEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PRIVATE_DATA_BASE_HANDLE_FEATURES_NV:
        StructPtrFromApiDump<VkPhysicalDevicePrivateDataBaseHandleFeaturesNV>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PRIVATE_DATA_FEATURES:
        StructPtrFromApiDump<VkPhysicalDevicePrivateDataFeatures>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PROPERTIES_2:
        StructPtrFromApiDump<VkPhysicalDeviceProperties2>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PROTECTED_MEMORY_FEATURES:
        StructPtrFromApiDump<VkPhysicalDeviceProtectedMemoryFeatures>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PROTECTED_MEMORY_PROPERTIES:
        StructPtrFromApiDump<VkPhysicalDeviceProtectedMemoryProperties>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PROVOKING_VERTEX_FEATURES_EXT:
        StructPtrFromApiDump<VkPhysicalDeviceProvokingVertexFeaturesEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PROVOKING_VERTEX_PROPERTIES_EXT:
        StructPtrFromApiDump<VkPhysicalDeviceProvokingVertexPropertiesEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PUSH_CONSTANT_BANK_FEATURES_NV:
        StructPtrFromApiDump<VkPhysicalDevicePushConstantBankFeaturesNV>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PUSH_CONSTANT_BANK_PROPERTIES_NV:
        StructPtrFromApiDump<VkPhysicalDevicePushConstantBankPropertiesNV>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PUSH_DESCRIPTOR_PROPERTIES:
        StructPtrFromApiDump<VkPhysicalDevicePushDescriptorProperties>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_QUEUE_FAMILY_DATA_GRAPH_PROCESSING_ENGINE_INFO_ARM:
        StructPtrFromApiDump<VkPhysicalDeviceQueueFamilyDataGraphProcessingEngineInfoARM>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_QUEUE_PERF_HINT_FEATURES_QCOM:
        StructPtrFromApiDump<VkPhysicalDeviceQueuePerfHintFeaturesQCOM>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_QUEUE_PERF_HINT_PROPERTIES_QCOM:
        StructPtrFromApiDump<VkPhysicalDeviceQueuePerfHintPropertiesQCOM>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_RGBA10X6_FORMATS_FEATURES_EXT:
        StructPtrFromApiDump<VkPhysicalDeviceRGBA10X6FormatsFeaturesEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_RASTERIZATION_ORDER_ATTACHMENT_ACCESS_FEATURES_EXT:
        StructPtrFromApiDump<VkPhysicalDeviceRasterizationOrderAttachmentAccessFeaturesEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_RAW_ACCESS_CHAINS_FEATURES_NV:
        StructPtrFromApiDump<VkPhysicalDeviceRawAccessChainsFeaturesNV>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_RAY_QUERY_FEATURES_KHR:
        StructPtrFromApiDump<VkPhysicalDeviceRayQueryFeaturesKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_RAY_TRACING_INVOCATION_REORDER_FEATURES_EXT:
        StructPtrFromApiDump<VkPhysicalDeviceRayTracingInvocationReorderFeaturesEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_RAY_TRACING_INVOCATION_REORDER_FEATURES_NV:
        StructPtrFromApiDump<VkPhysicalDeviceRayTracingInvocationReorderFeaturesNV>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_RAY_TRACING_INVOCATION_REORDER_PROPERTIES_EXT:
        StructPtrFromApiDump<VkPhysicalDeviceRayTracingInvocationReorderPropertiesEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_RAY_TRACING_INVOCATION_REORDER_PROPERTIES_NV:
        StructPtrFromApiDump<VkPhysicalDeviceRayTracingInvocationReorderPropertiesNV>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_RAY_TRACING_LINEAR_SWEPT_SPHERES_FEATURES_NV:
        StructPtrFromApiDump<VkPhysicalDeviceRayTracingLinearSweptSpheresFeaturesNV>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_RAY_TRACING_MAINTENANCE_1_FEATURES_KHR:
        StructPtrFromApiDump<VkPhysicalDeviceRayTracingMaintenance1FeaturesKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_RAY_TRACING_MOTION_BLUR_FEATURES_NV:
        StructPtrFromApiDump<VkPhysicalDeviceRayTracingMotionBlurFeaturesNV>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_RAY_TRACING_PIPELINE_FEATURES_KHR:
        StructPtrFromApiDump<VkPhysicalDeviceRayTracingPipelineFeaturesKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_RAY_TRACING_PIPELINE_PROPERTIES_KHR:
        StructPtrFromApiDump<VkPhysicalDeviceRayTracingPipelinePropertiesKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_RAY_TRACING_POSITION_FETCH_FEATURES_KHR:
        StructPtrFromApiDump<VkPhysicalDeviceRayTracingPositionFetchFeaturesKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_RAY_TRACING_PROPERTIES_NV:
        StructPtrFromApiDump<VkPhysicalDeviceRayTracingPropertiesNV>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_RAY_TRACING_VALIDATION_FEATURES_NV:
        StructPtrFromApiDump<VkPhysicalDeviceRayTracingValidationFeaturesNV>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_RELAXED_LINE_RASTERIZATION_FEATURES_IMG:
        StructPtrFromApiDump<VkPhysicalDeviceRelaxedLineRasterizationFeaturesIMG>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_RENDER_PASS_STRIPED_FEATURES_ARM:
        StructPtrFromApiDump<VkPhysicalDeviceRenderPassStripedFeaturesARM>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_RENDER_PASS_STRIPED_PROPERTIES_ARM:
        StructPtrFromApiDump<VkPhysicalDeviceRenderPassStripedPropertiesARM>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_REPRESENTATIVE_FRAGMENT_TEST_FEATURES_NV:
        StructPtrFromApiDump<VkPhysicalDeviceRepresentativeFragmentTestFeaturesNV>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_ROBUSTNESS_2_FEATURES_KHR:
        StructPtrFromApiDump<VkPhysicalDeviceRobustness2FeaturesKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_ROBUSTNESS_2_PROPERTIES_KHR:
        StructPtrFromApiDump<VkPhysicalDeviceRobustness2PropertiesKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SAMPLE_LOCATIONS_PROPERTIES_EXT:
        StructPtrFromApiDump<VkPhysicalDeviceSampleLocationsPropertiesEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SAMPLER_FILTER_MINMAX_PROPERTIES:
        StructPtrFromApiDump<VkPhysicalDeviceSamplerFilterMinmaxProperties>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SAMPLER_YCBCR_CONVERSION_FEATURES:
        StructPtrFromApiDump<VkPhysicalDeviceSamplerYcbcrConversionFeatures>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SCALAR_BLOCK_LAYOUT_FEATURES:
        StructPtrFromApiDump<VkPhysicalDeviceScalarBlockLayoutFeatures>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SCHEDULING_CONTROLS_DISPATCH_PARAMETERS_PROPERTIES_ARM:
        StructPtrFromApiDump<VkPhysicalDeviceSchedulingControlsDispatchParametersPropertiesARM>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SCHEDULING_CONTROLS_FEATURES_ARM:
        StructPtrFromApiDump<VkPhysicalDeviceSchedulingControlsFeaturesARM>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SCHEDULING_CONTROLS_PROPERTIES_ARM:
        StructPtrFromApiDump<VkPhysicalDeviceSchedulingControlsPropertiesARM>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SEPARATE_DEPTH_STENCIL_LAYOUTS_FEATURES:
        StructPtrFromApiDump<VkPhysicalDeviceSeparateDepthStencilLayoutsFeatures>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_64_BIT_INDEXING_FEATURES_EXT:
        StructPtrFromApiDump<VkPhysicalDeviceShader64BitIndexingFeaturesEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_ABORT_FEATURES_KHR:
        StructPtrFromApiDump<VkPhysicalDeviceShaderAbortFeaturesKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_ABORT_PROPERTIES_KHR:
        StructPtrFromApiDump<VkPhysicalDeviceShaderAbortPropertiesKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_ATOMIC_FLOAT16_VECTOR_FEATURES_NV:
        StructPtrFromApiDump<VkPhysicalDeviceShaderAtomicFloat16VectorFeaturesNV>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_ATOMIC_FLOAT_2_FEATURES_EXT:
        StructPtrFromApiDump<VkPhysicalDeviceShaderAtomicFloat2FeaturesEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_ATOMIC_FLOAT_FEATURES_EXT:
        StructPtrFromApiDump<VkPhysicalDeviceShaderAtomicFloatFeaturesEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_ATOMIC_INT64_FEATURES:
        StructPtrFromApiDump<VkPhysicalDeviceShaderAtomicInt64Features>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_BFLOAT16_FEATURES_KHR:
        StructPtrFromApiDump<VkPhysicalDeviceShaderBfloat16FeaturesKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_CLOCK_FEATURES_KHR:
        StructPtrFromApiDump<VkPhysicalDeviceShaderClockFeaturesKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_CONSTANT_DATA_FEATURES_KHR:
        StructPtrFromApiDump<VkPhysicalDeviceShaderConstantDataFeaturesKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_CORE_BUILTINS_FEATURES_ARM:
        StructPtrFromApiDump<VkPhysicalDeviceShaderCoreBuiltinsFeaturesARM>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_CORE_BUILTINS_PROPERTIES_ARM:
        StructPtrFromApiDump<VkPhysicalDeviceShaderCoreBuiltinsPropertiesARM>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_CORE_PROPERTIES_2_AMD:
        StructPtrFromApiDump<VkPhysicalDeviceShaderCoreProperties2AMD>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_CORE_PROPERTIES_AMD:
        StructPtrFromApiDump<VkPhysicalDeviceShaderCorePropertiesAMD>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_CORE_PROPERTIES_ARM:
        StructPtrFromApiDump<VkPhysicalDeviceShaderCorePropertiesARM>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_DEMOTE_TO_HELPER_INVOCATION_FEATURES:
        StructPtrFromApiDump<VkPhysicalDeviceShaderDemoteToHelperInvocationFeatures>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_DRAW_PARAMETERS_FEATURES:
        StructPtrFromApiDump<VkPhysicalDeviceShaderDrawParametersFeatures>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_EARLY_AND_LATE_FRAGMENT_TESTS_FEATURES_AMD:
        StructPtrFromApiDump<VkPhysicalDeviceShaderEarlyAndLateFragmentTestsFeaturesAMD>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_EXPECT_ASSUME_FEATURES:
        StructPtrFromApiDump<VkPhysicalDeviceShaderExpectAssumeFeatures>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_FLOAT16_INT8_FEATURES:
        StructPtrFromApiDump<VkPhysicalDeviceShaderFloat16Int8Features>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_FLOAT8_FEATURES_EXT:
        StructPtrFromApiDump<VkPhysicalDeviceShaderFloat8FeaturesEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_FLOAT_CONTROLS_2_FEATURES:
        StructPtrFromApiDump<VkPhysicalDeviceShaderFloatControls2Features>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_FMA_FEATURES_KHR:
        StructPtrFromApiDump<VkPhysicalDeviceShaderFmaFeaturesKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_IMAGE_ATOMIC_INT64_FEATURES_EXT:
        StructPtrFromApiDump<VkPhysicalDeviceShaderImageAtomicInt64FeaturesEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_IMAGE_FOOTPRINT_FEATURES_NV:
        StructPtrFromApiDump<VkPhysicalDeviceShaderImageFootprintFeaturesNV>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_INTEGER_DOT_PRODUCT_FEATURES:
        StructPtrFromApiDump<VkPhysicalDeviceShaderIntegerDotProductFeatures>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_INTEGER_DOT_PRODUCT_PROPERTIES:
        StructPtrFromApiDump<VkPhysicalDeviceShaderIntegerDotProductProperties>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_INTEGER_FUNCTIONS_2_FEATURES_INTEL:
        StructPtrFromApiDump<VkPhysicalDeviceShaderIntegerFunctions2FeaturesINTEL>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_LONG_VECTOR_FEATURES_EXT:
        StructPtrFromApiDump<VkPhysicalDeviceShaderLongVectorFeaturesEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_LONG_VECTOR_PROPERTIES_EXT:
        StructPtrFromApiDump<VkPhysicalDeviceShaderLongVectorPropertiesEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_MAXIMAL_RECONVERGENCE_FEATURES_KHR:
        StructPtrFromApiDump<VkPhysicalDeviceShaderMaximalReconvergenceFeaturesKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_MIXED_FLOAT_DOT_PRODUCT_FEATURES_VALVE:
        StructPtrFromApiDump<VkPhysicalDeviceShaderMixedFloatDotProductFeaturesVALVE>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_MODULE_IDENTIFIER_FEATURES_EXT:
        StructPtrFromApiDump<VkPhysicalDeviceShaderModuleIdentifierFeaturesEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_MODULE_IDENTIFIER_PROPERTIES_EXT:
        StructPtrFromApiDump<VkPhysicalDeviceShaderModuleIdentifierPropertiesEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_MULTIPLE_WAIT_QUEUES_FEATURES_QCOM:
        StructPtrFromApiDump<VkPhysicalDeviceShaderMultipleWaitQueuesFeaturesQCOM>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_MULTIPLE_WAIT_QUEUES_PROPERTIES_QCOM:
        StructPtrFromApiDump<VkPhysicalDeviceShaderMultipleWaitQueuesPropertiesQCOM>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_OCP_MICROSCALING_TYPES_FEATURES_EXT:
        StructPtrFromApiDump<VkPhysicalDeviceShaderOCPMicroscalingTypesFeaturesEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_OBJECT_FEATURES_EXT:
        StructPtrFromApiDump<VkPhysicalDeviceShaderObjectFeaturesEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_OBJECT_PROPERTIES_EXT:
        StructPtrFromApiDump<VkPhysicalDeviceShaderObjectPropertiesEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_QUAD_CONTROL_FEATURES_KHR:
        StructPtrFromApiDump<VkPhysicalDeviceShaderQuadControlFeaturesKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_RELAXED_EXTENDED_INSTRUCTION_FEATURES_KHR:
        StructPtrFromApiDump<VkPhysicalDeviceShaderRelaxedExtendedInstructionFeaturesKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_REPLICATED_COMPOSITES_FEATURES_EXT:
        StructPtrFromApiDump<VkPhysicalDeviceShaderReplicatedCompositesFeaturesEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_SM_BUILTINS_FEATURES_NV:
        StructPtrFromApiDump<VkPhysicalDeviceShaderSMBuiltinsFeaturesNV>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_SM_BUILTINS_PROPERTIES_NV:
        StructPtrFromApiDump<VkPhysicalDeviceShaderSMBuiltinsPropertiesNV>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_SPLIT_BARRIER_FEATURES_EXT:
        StructPtrFromApiDump<VkPhysicalDeviceShaderSplitBarrierFeaturesEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_SPLIT_BARRIER_PROPERTIES_EXT:
        StructPtrFromApiDump<VkPhysicalDeviceShaderSplitBarrierPropertiesEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_SUBGROUP_EXTENDED_TYPES_FEATURES:
        StructPtrFromApiDump<VkPhysicalDeviceShaderSubgroupExtendedTypesFeatures>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_SUBGROUP_PARTITIONED_FEATURES_EXT:
        StructPtrFromApiDump<VkPhysicalDeviceShaderSubgroupPartitionedFeaturesEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_SUBGROUP_ROTATE_FEATURES:
        StructPtrFromApiDump<VkPhysicalDeviceShaderSubgroupRotateFeatures>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_SUBGROUP_UNIFORM_CONTROL_FLOW_FEATURES_KHR:
        StructPtrFromApiDump<VkPhysicalDeviceShaderSubgroupUniformControlFlowFeaturesKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_TERMINATE_INVOCATION_FEATURES:
        StructPtrFromApiDump<VkPhysicalDeviceShaderTerminateInvocationFeatures>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_TILE_IMAGE_FEATURES_EXT:
        StructPtrFromApiDump<VkPhysicalDeviceShaderTileImageFeaturesEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_TILE_IMAGE_PROPERTIES_EXT:
        StructPtrFromApiDump<VkPhysicalDeviceShaderTileImagePropertiesEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_UNIFORM_BUFFER_UNSIZED_ARRAY_FEATURES_EXT:
        StructPtrFromApiDump<VkPhysicalDeviceShaderUniformBufferUnsizedArrayFeaturesEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_UNTYPED_POINTERS_FEATURES_KHR:
        StructPtrFromApiDump<VkPhysicalDeviceShaderUntypedPointersFeaturesKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADING_RATE_IMAGE_FEATURES_NV:
        StructPtrFromApiDump<VkPhysicalDeviceShadingRateImageFeaturesNV>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADING_RATE_IMAGE_PROPERTIES_NV:
        StructPtrFromApiDump<VkPhysicalDeviceShadingRateImagePropertiesNV>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SPARSE_IMAGE_FORMAT_INFO_2:
        StructPtrFromApiDump<VkPhysicalDeviceSparseImageFormatInfo2>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SUBGROUP_PROPERTIES:
        StructPtrFromApiDump<VkPhysicalDeviceSubgroupProperties>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SUBGROUP_SIZE_CONTROL_FEATURES:
        StructPtrFromApiDump<VkPhysicalDeviceSubgroupSizeControlFeatures>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SUBGROUP_SIZE_CONTROL_PROPERTIES:
        StructPtrFromApiDump<VkPhysicalDeviceSubgroupSizeControlProperties>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SUBPASS_MERGE_FEEDBACK_FEATURES_EXT:
        StructPtrFromApiDump<VkPhysicalDeviceSubpassMergeFeedbackFeaturesEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SURFACE_INFO_2_KHR:
        StructPtrFromApiDump<VkPhysicalDeviceSurfaceInfo2KHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SWAPCHAIN_MAINTENANCE_1_FEATURES_KHR:
        StructPtrFromApiDump<VkPhysicalDeviceSwapchainMaintenance1FeaturesKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SYNCHRONIZATION_2_FEATURES:
        StructPtrFromApiDump<VkPhysicalDeviceSynchronization2Features>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_TENSOR_FEATURES_ARM:
        StructPtrFromApiDump<VkPhysicalDeviceTensorFeaturesARM>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_TENSOR_PROPERTIES_ARM:
        StructPtrFromApiDump<VkPhysicalDeviceTensorPropertiesARM>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_TEXEL_BUFFER_ALIGNMENT_FEATURES_EXT:
        StructPtrFromApiDump<VkPhysicalDeviceTexelBufferAlignmentFeaturesEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_TEXEL_BUFFER_ALIGNMENT_PROPERTIES:
        StructPtrFromApiDump<VkPhysicalDeviceTexelBufferAlignmentProperties>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_TEXTURE_COMPRESSION_ASTC_3D_FEATURES_EXT:
        StructPtrFromApiDump<VkPhysicalDeviceTextureCompressionASTC3DFeaturesEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_TEXTURE_COMPRESSION_ASTC_HDR_FEATURES:
        StructPtrFromApiDump<VkPhysicalDeviceTextureCompressionASTCHDRFeatures>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_THROTTLE_HINT_FEATURES_SEC:
        StructPtrFromApiDump<VkPhysicalDeviceThrottleHintFeaturesSEC>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_TILE_MEMORY_HEAP_FEATURES_QCOM:
        StructPtrFromApiDump<VkPhysicalDeviceTileMemoryHeapFeaturesQCOM>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_TILE_MEMORY_HEAP_PROPERTIES_QCOM:
        StructPtrFromApiDump<VkPhysicalDeviceTileMemoryHeapPropertiesQCOM>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_TILE_PROPERTIES_FEATURES_QCOM:
        StructPtrFromApiDump<VkPhysicalDeviceTilePropertiesFeaturesQCOM>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_TILE_SHADING_FEATURES_QCOM:
        StructPtrFromApiDump<VkPhysicalDeviceTileShadingFeaturesQCOM>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_TILE_SHADING_PROPERTIES_QCOM:
        StructPtrFromApiDump<VkPhysicalDeviceTileShadingPropertiesQCOM>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_TIMELINE_SEMAPHORE_FEATURES:
        StructPtrFromApiDump<VkPhysicalDeviceTimelineSemaphoreFeatures>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_TIMELINE_SEMAPHORE_PROPERTIES:
        StructPtrFromApiDump<VkPhysicalDeviceTimelineSemaphoreProperties>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_TOOL_PROPERTIES:
        StructPtrFromApiDump<VkPhysicalDeviceToolProperties>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_TRANSFORM_FEEDBACK_FEATURES_EXT:
        StructPtrFromApiDump<VkPhysicalDeviceTransformFeedbackFeaturesEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_TRANSFORM_FEEDBACK_PROPERTIES_EXT:
        StructPtrFromApiDump<VkPhysicalDeviceTransformFeedbackPropertiesEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_UNIFIED_IMAGE_LAYOUTS_FEATURES_KHR:
        StructPtrFromApiDump<VkPhysicalDeviceUnifiedImageLayoutsFeaturesKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_UNIFORM_BUFFER_STANDARD_LAYOUT_FEATURES:
        StructPtrFromApiDump<VkPhysicalDeviceUniformBufferStandardLayoutFeatures>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VARIABLE_POINTERS_FEATURES:
        StructPtrFromApiDump<VkPhysicalDeviceVariablePointersFeatures>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VERTEX_ATTRIBUTE_DIVISOR_FEATURES:
        StructPtrFromApiDump<VkPhysicalDeviceVertexAttributeDivisorFeatures>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VERTEX_ATTRIBUTE_DIVISOR_PROPERTIES:
        StructPtrFromApiDump<VkPhysicalDeviceVertexAttributeDivisorProperties>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VERTEX_ATTRIBUTE_DIVISOR_PROPERTIES_EXT:
        StructPtrFromApiDump<VkPhysicalDeviceVertexAttributeDivisorPropertiesEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VERTEX_ATTRIBUTE_ROBUSTNESS_FEATURES_EXT:
        StructPtrFromApiDump<VkPhysicalDeviceVertexAttributeRobustnessFeaturesEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VERTEX_INPUT_DYNAMIC_STATE_FEATURES_EXT:
        StructPtrFromApiDump<VkPhysicalDeviceVertexInputDynamicStateFeaturesEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VIDEO_DECODE_VP9_FEATURES_KHR:
        StructPtrFromApiDump<VkPhysicalDeviceVideoDecodeVP9FeaturesKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VIDEO_ENCODE_AV1_FEATURES_KHR:
        StructPtrFromApiDump<VkPhysicalDeviceVideoEncodeAV1FeaturesKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VIDEO_ENCODE_FEEDBACK_2_FEATURES_KHR:
        StructPtrFromApiDump<VkPhysicalDeviceVideoEncodeFeedback2FeaturesKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VIDEO_ENCODE_INTRA_REFRESH_FEATURES_KHR:
        StructPtrFromApiDump<VkPhysicalDeviceVideoEncodeIntraRefreshFeaturesKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VIDEO_ENCODE_QUALITY_LEVEL_INFO_KHR:
        StructPtrFromApiDump<VkPhysicalDeviceVideoEncodeQualityLevelInfoKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VIDEO_ENCODE_QUANTIZATION_MAP_FEATURES_KHR:
        StructPtrFromApiDump<VkPhysicalDeviceVideoEncodeQuantizationMapFeaturesKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VIDEO_ENCODE_RGB_CONVERSION_FEATURES_VALVE:
        StructPtrFromApiDump<VkPhysicalDeviceVideoEncodeRgbConversionFeaturesVALVE>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VIDEO_FORMAT_INFO_KHR:
        StructPtrFromApiDump<VkPhysicalDeviceVideoFormatInfoKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VIDEO_MAINTENANCE_1_FEATURES_KHR:
        StructPtrFromApiDump<VkPhysicalDeviceVideoMaintenance1FeaturesKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_1_FEATURES:
        StructPtrFromApiDump<VkPhysicalDeviceVulkan11Features>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_1_PROPERTIES:
        StructPtrFromApiDump<VkPhysicalDeviceVulkan11Properties>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_2_FEATURES:
        StructPtrFromApiDump<VkPhysicalDeviceVulkan12Features>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_2_PROPERTIES:
        StructPtrFromApiDump<VkPhysicalDeviceVulkan12Properties>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_3_FEATURES:
        StructPtrFromApiDump<VkPhysicalDeviceVulkan13Features>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_3_PROPERTIES:
        StructPtrFromApiDump<VkPhysicalDeviceVulkan13Properties>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_4_FEATURES:
        StructPtrFromApiDump<VkPhysicalDeviceVulkan14Features>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_4_PROPERTIES:
        StructPtrFromApiDump<VkPhysicalDeviceVulkan14Properties>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_MEMORY_MODEL_FEATURES:
        StructPtrFromApiDump<VkPhysicalDeviceVulkanMemoryModelFeatures>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_WORKGROUP_MEMORY_EXPLICIT_LAYOUT_FEATURES_KHR:
        StructPtrFromApiDump<VkPhysicalDeviceWorkgroupMemoryExplicitLayoutFeaturesKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_YCBCR_2_PLANE_444_FORMATS_FEATURES_EXT:
        StructPtrFromApiDump<VkPhysicalDeviceYcbcr2Plane444FormatsFeaturesEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_YCBCR_DEGAMMA_FEATURES_QCOM:
        StructPtrFromApiDump<VkPhysicalDeviceYcbcrDegammaFeaturesQCOM>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_YCBCR_IMAGE_ARRAYS_FEATURES_EXT:
        StructPtrFromApiDump<VkPhysicalDeviceYcbcrImageArraysFeaturesEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_ZERO_INITIALIZE_DEVICE_MEMORY_FEATURES_EXT:
        StructPtrFromApiDump<VkPhysicalDeviceZeroInitializeDeviceMemoryFeaturesEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_ZERO_INITIALIZE_WORKGROUP_MEMORY_FEATURES:
        StructPtrFromApiDump<VkPhysicalDeviceZeroInitializeWorkgroupMemoryFeatures>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PIPELINE_BINARY_CREATE_INFO_KHR:
        StructPtrFromApiDump<VkPipelineBinaryCreateInfoKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PIPELINE_BINARY_DATA_INFO_KHR:
        StructPtrFromApiDump<VkPipelineBinaryDataInfoKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PIPELINE_BINARY_HANDLES_INFO_KHR:
        StructPtrFromApiDump<VkPipelineBinaryHandlesInfoKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PIPELINE_BINARY_INFO_KHR:
        StructPtrFromApiDump<VkPipelineBinaryInfoKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PIPELINE_BINARY_KEY_KHR:
        StructPtrFromApiDump<VkPipelineBinaryKeyKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PIPELINE_CACHE_CREATE_INFO:
        StructPtrFromApiDump<VkPipelineCacheCreateInfo>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_ADVANCED_STATE_CREATE_INFO_EXT:
        StructPtrFromApiDump<VkPipelineColorBlendAdvancedStateCreateInfoEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO:
        StructPtrFromApiDump<VkPipelineColorBlendStateCreateInfo>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PIPELINE_COLOR_WRITE_CREATE_INFO_EXT:
        StructPtrFromApiDump<VkPipelineColorWriteCreateInfoEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PIPELINE_COMPILER_CONTROL_CREATE_INFO_AMD:
        StructPtrFromApiDump<VkPipelineCompilerControlCreateInfoAMD>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PIPELINE_COVERAGE_MODULATION_STATE_CREATE_INFO_NV:
        StructPtrFromApiDump<VkPipelineCoverageModulationStateCreateInfoNV>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PIPELINE_COVERAGE_REDUCTION_STATE_CREATE_INFO_NV:
        StructPtrFromApiDump<VkPipelineCoverageReductionStateCreateInfoNV>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PIPELINE_COVERAGE_TO_COLOR_STATE_CREATE_INFO_NV:
        StructPtrFromApiDump<VkPipelineCoverageToColorStateCreateInfoNV>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PIPELINE_CREATE_FLAGS_2_CREATE_INFO:
        StructPtrFromApiDump<VkPipelineCreateFlags2CreateInfo>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PIPELINE_CREATE_INFO_KHR:
        StructPtrFromApiDump<VkPipelineCreateInfoKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PIPELINE_CREATION_FEEDBACK_CREATE_INFO:
        StructPtrFromApiDump<VkPipelineCreationFeedbackCreateInfo>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO:
        StructPtrFromApiDump<VkPipelineDepthStencilStateCreateInfo>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PIPELINE_DISCARD_RECTANGLE_STATE_CREATE_INFO_EXT:
        StructPtrFromApiDump<VkPipelineDiscardRectangleStateCreateInfoEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO:
        StructPtrFromApiDump<VkPipelineDynamicStateCreateInfo>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PIPELINE_EXECUTABLE_INFO_KHR:
        StructPtrFromApiDump<VkPipelineExecutableInfoKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PIPELINE_EXECUTABLE_INTERNAL_REPRESENTATION_KHR:
        StructPtrFromApiDump<VkPipelineExecutableInternalRepresentationKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PIPELINE_EXECUTABLE_PROPERTIES_KHR:
        StructPtrFromApiDump<VkPipelineExecutablePropertiesKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PIPELINE_EXECUTABLE_STATISTIC_KHR:
        StructPtrFromApiDump<VkPipelineExecutableStatisticKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PIPELINE_FRAGMENT_DENSITY_MAP_LAYERED_CREATE_INFO_VALVE:
        StructPtrFromApiDump<VkPipelineFragmentDensityMapLayeredCreateInfoVALVE>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PIPELINE_FRAGMENT_SHADING_RATE_ENUM_STATE_CREATE_INFO_NV:
        StructPtrFromApiDump<VkPipelineFragmentShadingRateEnumStateCreateInfoNV>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PIPELINE_FRAGMENT_SHADING_RATE_STATE_CREATE_INFO_KHR:
        StructPtrFromApiDump<VkPipelineFragmentShadingRateStateCreateInfoKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PIPELINE_INDIRECT_DEVICE_ADDRESS_INFO_NV:
        StructPtrFromApiDump<VkPipelineIndirectDeviceAddressInfoNV>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PIPELINE_INFO_KHR:
        StructPtrFromApiDump<VkPipelineInfoKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO:
        StructPtrFromApiDump<VkPipelineInputAssemblyStateCreateInfo>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO:
        StructPtrFromApiDump<VkPipelineLayoutCreateInfo>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PIPELINE_LIBRARY_CREATE_INFO_KHR:
        StructPtrFromApiDump<VkPipelineLibraryCreateInfoKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO:
        StructPtrFromApiDump<VkPipelineMultisampleStateCreateInfo>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_CONSERVATIVE_STATE_CREATE_INFO_EXT:
        StructPtrFromApiDump<VkPipelineRasterizationConservativeStateCreateInfoEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_DEPTH_CLIP_STATE_CREATE_INFO_EXT:
        StructPtrFromApiDump<VkPipelineRasterizationDepthClipStateCreateInfoEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_LINE_STATE_CREATE_INFO:
        StructPtrFromApiDump<VkPipelineRasterizationLineStateCreateInfo>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_PROVOKING_VERTEX_STATE_CREATE_INFO_EXT:
        StructPtrFromApiDump<VkPipelineRasterizationProvokingVertexStateCreateInfoEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO:
        StructPtrFromApiDump<VkPipelineRasterizationStateCreateInfo>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_RASTERIZATION_ORDER_AMD:
        StructPtrFromApiDump<VkPipelineRasterizationStateRasterizationOrderAMD>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_STREAM_CREATE_INFO_EXT:
        StructPtrFromApiDump<VkPipelineRasterizationStateStreamCreateInfoEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PIPELINE_RENDERING_CREATE_INFO:
        StructPtrFromApiDump<VkPipelineRenderingCreateInfo>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PIPELINE_REPRESENTATIVE_FRAGMENT_TEST_STATE_CREATE_INFO_NV:
        StructPtrFromApiDump<VkPipelineRepresentativeFragmentTestStateCreateInfoNV>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PIPELINE_ROBUSTNESS_CREATE_INFO:
        StructPtrFromApiDump<VkPipelineRobustnessCreateInfo>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PIPELINE_SAMPLE_LOCATIONS_STATE_CREATE_INFO_EXT:
        StructPtrFromApiDump<VkPipelineSampleLocationsStateCreateInfoEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO:
        StructPtrFromApiDump<VkPipelineShaderStageCreateInfo>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_MODULE_IDENTIFIER_CREATE_INFO_EXT:
        StructPtrFromApiDump<VkPipelineShaderStageModuleIdentifierCreateInfoEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_REQUIRED_SUBGROUP_SIZE_CREATE_INFO:
        StructPtrFromApiDump<VkPipelineShaderStageRequiredSubgroupSizeCreateInfo>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PIPELINE_TESSELLATION_DOMAIN_ORIGIN_STATE_CREATE_INFO:
        StructPtrFromApiDump<VkPipelineTessellationDomainOriginStateCreateInfo>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PIPELINE_TESSELLATION_STATE_CREATE_INFO:
        StructPtrFromApiDump<VkPipelineTessellationStateCreateInfo>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_DIVISOR_STATE_CREATE_INFO:
        StructPtrFromApiDump<VkPipelineVertexInputDivisorStateCreateInfo>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO:
        StructPtrFromApiDump<VkPipelineVertexInputStateCreateInfo>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_COARSE_SAMPLE_ORDER_STATE_CREATE_INFO_NV:
        StructPtrFromApiDump<VkPipelineViewportCoarseSampleOrderStateCreateInfoNV>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_DEPTH_CLAMP_CONTROL_CREATE_INFO_EXT:
        StructPtrFromApiDump<VkPipelineViewportDepthClampControlCreateInfoEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_DEPTH_CLIP_CONTROL_CREATE_INFO_EXT:
        StructPtrFromApiDump<VkPipelineViewportDepthClipControlCreateInfoEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_EXCLUSIVE_SCISSOR_STATE_CREATE_INFO_NV:
        StructPtrFromApiDump<VkPipelineViewportExclusiveScissorStateCreateInfoNV>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_SHADING_RATE_IMAGE_STATE_CREATE_INFO_NV:
        StructPtrFromApiDump<VkPipelineViewportShadingRateImageStateCreateInfoNV>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO:
        StructPtrFromApiDump<VkPipelineViewportStateCreateInfo>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_SWIZZLE_STATE_CREATE_INFO_NV:
        StructPtrFromApiDump<VkPipelineViewportSwizzleStateCreateInfoNV>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_W_SCALING_STATE_CREATE_INFO_NV:
        StructPtrFromApiDump<VkPipelineViewportWScalingStateCreateInfoNV>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PRESENT_FRAME_TOKEN_GGP:
        StructPtrFromApiDump<VkPresentFrameTokenGGP>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PRESENT_ID_2_KHR:
        StructPtrFromApiDump<VkPresentId2KHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PRESENT_ID_KHR:
        StructPtrFromApiDump<VkPresentIdKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PRESENT_INFO_KHR:
        StructPtrFromApiDump<VkPresentInfoKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PRESENT_REGIONS_KHR:
        StructPtrFromApiDump<VkPresentRegionsKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PRESENT_TIMES_INFO_GOOGLE:
        StructPtrFromApiDump<VkPresentTimesInfoGOOGLE>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PRESENT_TIMING_INFO_EXT:
        StructPtrFromApiDump<VkPresentTimingInfoEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PRESENT_TIMING_SURFACE_CAPABILITIES_EXT:
        StructPtrFromApiDump<VkPresentTimingSurfaceCapabilitiesEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PRESENT_TIMINGS_INFO_EXT:
        StructPtrFromApiDump<VkPresentTimingsInfoEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PRESENT_WAIT_2_INFO_KHR:
        StructPtrFromApiDump<VkPresentWait2InfoKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PRIVATE_DATA_SLOT_CREATE_INFO:
        StructPtrFromApiDump<VkPrivateDataSlotCreateInfo>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PROTECTED_SUBMIT_INFO:
        StructPtrFromApiDump<VkProtectedSubmitInfo>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PUSH_CONSTANT_BANK_INFO_NV:
        StructPtrFromApiDump<VkPushConstantBankInfoNV>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PUSH_CONSTANTS_INFO:
        StructPtrFromApiDump<VkPushConstantsInfo>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_PUSH_DESCRIPTOR_SET_INFO:
        StructPtrFromApiDump<VkPushDescriptorSetInfo>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_QUERY_POOL_CREATE_INFO:
        StructPtrFromApiDump<VkQueryPoolCreateInfo>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_QUERY_POOL_PERFORMANCE_CREATE_INFO_KHR:
        StructPtrFromApiDump<VkQueryPoolPerformanceCreateInfoKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_QUERY_POOL_PERFORMANCE_QUERY_CREATE_INFO_INTEL:
        StructPtrFromApiDump<VkQueryPoolPerformanceQueryCreateInfoINTEL>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_QUERY_POOL_VIDEO_ENCODE_FEEDBACK_CREATE_INFO_KHR:
        StructPtrFromApiDump<VkQueryPoolVideoEncodeFeedbackCreateInfoKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_QUERY_POOL_VIDEO_ENCODE_PER_PARTITION_FEEDBACK_CREATE_INFO_KHR:
        StructPtrFromApiDump<VkQueryPoolVideoEncodePerPartitionFeedbackCreateInfoKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_QUEUE_FAMILY_CHECKPOINT_PROPERTIES_2_NV:
        StructPtrFromApiDump<VkQueueFamilyCheckpointProperties2NV>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_QUEUE_FAMILY_CHECKPOINT_PROPERTIES_NV:
        StructPtrFromApiDump<VkQueueFamilyCheckpointPropertiesNV>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_QUEUE_FAMILY_DATA_GRAPH_OPTICAL_FLOW_PROPERTIES_ARM:
        StructPtrFromApiDump<VkQueueFamilyDataGraphOpticalFlowPropertiesARM>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_QUEUE_FAMILY_DATA_GRAPH_PROCESSING_ENGINE_PROPERTIES_ARM:
        StructPtrFromApiDump<VkQueueFamilyDataGraphProcessingEnginePropertiesARM>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_QUEUE_FAMILY_DATA_GRAPH_PROPERTIES_ARM:
        StructPtrFromApiDump<VkQueueFamilyDataGraphPropertiesARM>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_QUEUE_FAMILY_GLOBAL_PRIORITY_PROPERTIES:
        StructPtrFromApiDump<VkQueueFamilyGlobalPriorityProperties>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_QUEUE_FAMILY_OPTIMAL_IMAGE_TRANSFER_GRANULARITY_PROPERTIES_KHR:
        StructPtrFromApiDump<VkQueueFamilyOptimalImageTransferGranularityPropertiesKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_QUEUE_FAMILY_OWNERSHIP_TRANSFER_PROPERTIES_KHR:
        StructPtrFromApiDump<VkQueueFamilyOwnershipTransferPropertiesKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_QUEUE_FAMILY_PROPERTIES_2:
        StructPtrFromApiDump<VkQueueFamilyProperties2>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_QUEUE_FAMILY_QUERY_RESULT_STATUS_PROPERTIES_KHR:
        StructPtrFromApiDump<VkQueueFamilyQueryResultStatusPropertiesKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_QUEUE_FAMILY_VIDEO_PROPERTIES_KHR:
        StructPtrFromApiDump<VkQueueFamilyVideoPropertiesKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_RAY_TRACING_PIPELINE_CREATE_INFO_KHR:
        StructPtrFromApiDump<VkRayTracingPipelineCreateInfoKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_RAY_TRACING_PIPELINE_CREATE_INFO_NV:
        StructPtrFromApiDump<VkRayTracingPipelineCreateInfoNV>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_RAY_TRACING_PIPELINE_INTERFACE_CREATE_INFO_KHR:
        StructPtrFromApiDump<VkRayTracingPipelineInterfaceCreateInfoKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_RAY_TRACING_SHADER_GROUP_CREATE_INFO_KHR:
        StructPtrFromApiDump<VkRayTracingShaderGroupCreateInfoKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_RAY_TRACING_SHADER_GROUP_CREATE_INFO_NV:
        StructPtrFromApiDump<VkRayTracingShaderGroupCreateInfoNV>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_RELEASE_CAPTURED_PIPELINE_DATA_INFO_KHR:
        StructPtrFromApiDump<VkReleaseCapturedPipelineDataInfoKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_RELEASE_SWAPCHAIN_IMAGES_INFO_KHR:
        StructPtrFromApiDump<VkReleaseSwapchainImagesInfoKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_RENDER_PASS_ATTACHMENT_BEGIN_INFO:
        StructPtrFromApiDump<VkRenderPassAttachmentBeginInfo>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO:
        StructPtrFromApiDump<VkRenderPassBeginInfo>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO:
        StructPtrFromApiDump<VkRenderPassCreateInfo>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO_2:
        StructPtrFromApiDump<VkRenderPassCreateInfo2>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_RENDER_PASS_CREATION_CONTROL_EXT:
        StructPtrFromApiDump<VkRenderPassCreationControlEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_RENDER_PASS_CREATION_FEEDBACK_CREATE_INFO_EXT:
        StructPtrFromApiDump<VkRenderPassCreationFeedbackCreateInfoEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_RENDER_PASS_FRAGMENT_DENSITY_MAP_CREATE_INFO_EXT:
        StructPtrFromApiDump<VkRenderPassFragmentDensityMapCreateInfoEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_RENDER_PASS_FRAGMENT_DENSITY_MAP_OFFSET_END_INFO_EXT:
        StructPtrFromApiDump<VkRenderPassFragmentDensityMapOffsetEndInfoEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_RENDER_PASS_INPUT_ATTACHMENT_ASPECT_CREATE_INFO:
        StructPtrFromApiDump<VkRenderPassInputAttachmentAspectCreateInfo>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_RENDER_PASS_MULTIVIEW_CREATE_INFO:
        StructPtrFromApiDump<VkRenderPassMultiviewCreateInfo>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_RENDER_PASS_PERFORMANCE_COUNTERS_BY_REGION_BEGIN_INFO_ARM:
        StructPtrFromApiDump<VkRenderPassPerformanceCountersByRegionBeginInfoARM>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_RENDER_PASS_SAMPLE_LOCATIONS_BEGIN_INFO_EXT:
        StructPtrFromApiDump<VkRenderPassSampleLocationsBeginInfoEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_RENDER_PASS_STRIPE_BEGIN_INFO_ARM:
        StructPtrFromApiDump<VkRenderPassStripeBeginInfoARM>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_RENDER_PASS_STRIPE_INFO_ARM:
        StructPtrFromApiDump<VkRenderPassStripeInfoARM>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_RENDER_PASS_STRIPE_SUBMIT_INFO_ARM:
        StructPtrFromApiDump<VkRenderPassStripeSubmitInfoARM>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_RENDER_PASS_SUBPASS_FEEDBACK_CREATE_INFO_EXT:
        StructPtrFromApiDump<VkRenderPassSubpassFeedbackCreateInfoEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_RENDER_PASS_TILE_SHADING_CREATE_INFO_QCOM:
        StructPtrFromApiDump<VkRenderPassTileShadingCreateInfoQCOM>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_RENDER_PASS_TRANSFORM_BEGIN_INFO_QCOM:
        StructPtrFromApiDump<VkRenderPassTransformBeginInfoQCOM>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_RENDERING_AREA_INFO:
        StructPtrFromApiDump<VkRenderingAreaInfo>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_RENDERING_ATTACHMENT_FLAGS_INFO_KHR:
        StructPtrFromApiDump<VkRenderingAttachmentFlagsInfoKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_RENDERING_ATTACHMENT_INFO:
        StructPtrFromApiDump<VkRenderingAttachmentInfo>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_RENDERING_ATTACHMENT_LOCATION_INFO:
        StructPtrFromApiDump<VkRenderingAttachmentLocationInfo>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_RENDERING_END_INFO_KHR:
        StructPtrFromApiDump<VkRenderingEndInfoKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_RENDERING_FRAGMENT_DENSITY_MAP_ATTACHMENT_INFO_EXT:
        StructPtrFromApiDump<VkRenderingFragmentDensityMapAttachmentInfoEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_RENDERING_FRAGMENT_SHADING_RATE_ATTACHMENT_INFO_KHR:
        StructPtrFromApiDump<VkRenderingFragmentShadingRateAttachmentInfoKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_RENDERING_INFO:
        StructPtrFromApiDump<VkRenderingInfo>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_RENDERING_INPUT_ATTACHMENT_INDEX_INFO:
        StructPtrFromApiDump<VkRenderingInputAttachmentIndexInfo>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_RESOLVE_IMAGE_INFO_2:
        StructPtrFromApiDump<VkResolveImageInfo2>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_RESOLVE_IMAGE_MODE_INFO_KHR:
        StructPtrFromApiDump<VkResolveImageModeInfoKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_SAMPLE_LOCATIONS_INFO_EXT:
        StructPtrFromApiDump<VkSampleLocationsInfoEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_SAMPLER_BLOCK_MATCH_WINDOW_CREATE_INFO_QCOM:
        StructPtrFromApiDump<VkSamplerBlockMatchWindowCreateInfoQCOM>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_SAMPLER_BORDER_COLOR_COMPONENT_MAPPING_CREATE_INFO_EXT:
        StructPtrFromApiDump<VkSamplerBorderColorComponentMappingCreateInfoEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_SAMPLER_CAPTURE_DESCRIPTOR_DATA_INFO_EXT:
        StructPtrFromApiDump<VkSamplerCaptureDescriptorDataInfoEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO:
        StructPtrFromApiDump<VkSamplerCreateInfo>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_SAMPLER_CUBIC_WEIGHTS_CREATE_INFO_QCOM:
        StructPtrFromApiDump<VkSamplerCubicWeightsCreateInfoQCOM>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_SAMPLER_CUSTOM_BORDER_COLOR_CREATE_INFO_EXT:
        StructPtrFromApiDump<VkSamplerCustomBorderColorCreateInfoEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_SAMPLER_REDUCTION_MODE_CREATE_INFO:
        StructPtrFromApiDump<VkSamplerReductionModeCreateInfo>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_SAMPLER_YCBCR_CONVERSION_CREATE_INFO:
        StructPtrFromApiDump<VkSamplerYcbcrConversionCreateInfo>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_SAMPLER_YCBCR_CONVERSION_IMAGE_FORMAT_PROPERTIES:
        StructPtrFromApiDump<VkSamplerYcbcrConversionImageFormatProperties>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_SAMPLER_YCBCR_CONVERSION_INFO:
        StructPtrFromApiDump<VkSamplerYcbcrConversionInfo>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_SAMPLER_YCBCR_CONVERSION_YCBCR_DEGAMMA_CREATE_INFO_QCOM:
        StructPtrFromApiDump<VkSamplerYcbcrConversionYcbcrDegammaCreateInfoQCOM>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_SCREEN_SURFACE_CREATE_INFO_QNX:
        StructPtrFromApiDump<VkScreenSurfaceCreateInfoQNX>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO:
        StructPtrFromApiDump<VkSemaphoreCreateInfo>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_SEMAPHORE_GET_FD_INFO_KHR:
        StructPtrFromApiDump<VkSemaphoreGetFdInfoKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_SEMAPHORE_GET_WIN32_HANDLE_INFO_KHR:
        StructPtrFromApiDump<VkSemaphoreGetWin32HandleInfoKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_SEMAPHORE_GET_ZIRCON_HANDLE_INFO_FUCHSIA:
        StructPtrFromApiDump<VkSemaphoreGetZirconHandleInfoFUCHSIA>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_SEMAPHORE_SIGNAL_INFO:
        StructPtrFromApiDump<VkSemaphoreSignalInfo>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_SEMAPHORE_SUBMIT_INFO:
        StructPtrFromApiDump<VkSemaphoreSubmitInfo>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_SEMAPHORE_TYPE_CREATE_INFO:
        StructPtrFromApiDump<VkSemaphoreTypeCreateInfo>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_SEMAPHORE_WAIT_INFO:
        StructPtrFromApiDump<VkSemaphoreWaitInfo>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_SET_DESCRIPTOR_BUFFER_OFFSETS_INFO_EXT:
        StructPtrFromApiDump<VkSetDescriptorBufferOffsetsInfoEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_SET_LATENCY_MARKER_INFO_NV:
        StructPtrFromApiDump<VkSetLatencyMarkerInfoNV>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_SET_PRESENT_CONFIG_NV:
        StructPtrFromApiDump<VkSetPresentConfigNV>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_SHADER_CREATE_INFO_EXT:
        StructPtrFromApiDump<VkShaderCreateInfoEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO:
        StructPtrFromApiDump<VkShaderModuleCreateInfo>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_SHADER_MODULE_IDENTIFIER_EXT:
        StructPtrFromApiDump<VkShaderModuleIdentifierEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_SHADER_MODULE_VALIDATION_CACHE_CREATE_INFO_EXT:
        StructPtrFromApiDump<VkShaderModuleValidationCacheCreateInfoEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_SHARED_PRESENT_SURFACE_CAPABILITIES_2_KHR:
        StructPtrFromApiDump<VkSharedPresentSurfaceCapabilities2KHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_SHARED_PRESENT_SURFACE_CAPABILITIES_KHR:
        StructPtrFromApiDump<VkSharedPresentSurfaceCapabilitiesKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_SPARSE_IMAGE_FORMAT_PROPERTIES_2:
        StructPtrFromApiDump<VkSparseImageFormatProperties2>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_SPARSE_IMAGE_MEMORY_REQUIREMENTS_2:
        StructPtrFromApiDump<VkSparseImageMemoryRequirements2>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_STREAM_DESCRIPTOR_SURFACE_CREATE_INFO_GGP:
        StructPtrFromApiDump<VkStreamDescriptorSurfaceCreateInfoGGP>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_SUBMIT_INFO:
        StructPtrFromApiDump<VkSubmitInfo>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_SUBMIT_INFO_2:
        StructPtrFromApiDump<VkSubmitInfo2>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_SUBPASS_BEGIN_INFO:
        StructPtrFromApiDump<VkSubpassBeginInfo>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_SUBPASS_DEPENDENCY_2:
        StructPtrFromApiDump<VkSubpassDependency2>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_SUBPASS_DESCRIPTION_2:
        StructPtrFromApiDump<VkSubpassDescription2>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_SUBPASS_DESCRIPTION_DEPTH_STENCIL_RESOLVE:
        StructPtrFromApiDump<VkSubpassDescriptionDepthStencilResolve>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_SUBPASS_END_INFO:
        StructPtrFromApiDump<VkSubpassEndInfo>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_SUBPASS_RESOLVE_PERFORMANCE_QUERY_EXT:
        StructPtrFromApiDump<VkSubpassResolvePerformanceQueryEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_SUBRESOURCE_HOST_MEMCPY_SIZE:
        StructPtrFromApiDump<VkSubresourceHostMemcpySize>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_SUBRESOURCE_LAYOUT_2:
        StructPtrFromApiDump<VkSubresourceLayout2>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_SURFACE_CAPABILITIES_2_EXT:
        StructPtrFromApiDump<VkSurfaceCapabilities2EXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_SURFACE_CAPABILITIES_2_KHR:
        StructPtrFromApiDump<VkSurfaceCapabilities2KHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_SURFACE_CAPABILITIES_FULL_SCREEN_EXCLUSIVE_EXT:
        StructPtrFromApiDump<VkSurfaceCapabilitiesFullScreenExclusiveEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_SURFACE_CAPABILITIES_PRESENT_BARRIER_NV:
        StructPtrFromApiDump<VkSurfaceCapabilitiesPresentBarrierNV>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_SURFACE_CAPABILITIES_PRESENT_ID_2_KHR:
        StructPtrFromApiDump<VkSurfaceCapabilitiesPresentId2KHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_SURFACE_CAPABILITIES_PRESENT_WAIT_2_KHR:
        StructPtrFromApiDump<VkSurfaceCapabilitiesPresentWait2KHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_SURFACE_FORMAT_2_KHR:
        StructPtrFromApiDump<VkSurfaceFormat2KHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_SURFACE_FULL_SCREEN_EXCLUSIVE_INFO_EXT:
        StructPtrFromApiDump<VkSurfaceFullScreenExclusiveInfoEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_SURFACE_FULL_SCREEN_EXCLUSIVE_WIN32_INFO_EXT:
        StructPtrFromApiDump<VkSurfaceFullScreenExclusiveWin32InfoEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_SURFACE_PRESENT_MODE_COMPATIBILITY_KHR:
        StructPtrFromApiDump<VkSurfacePresentModeCompatibilityKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_SURFACE_PRESENT_MODE_KHR:
        StructPtrFromApiDump<VkSurfacePresentModeKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_SURFACE_PRESENT_SCALING_CAPABILITIES_KHR:
        StructPtrFromApiDump<VkSurfacePresentScalingCapabilitiesKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_SURFACE_PROTECTED_CAPABILITIES_KHR:
        StructPtrFromApiDump<VkSurfaceProtectedCapabilitiesKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_SWAPCHAIN_CALIBRATED_TIMESTAMP_INFO_EXT:
        StructPtrFromApiDump<VkSwapchainCalibratedTimestampInfoEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_SWAPCHAIN_COUNTER_CREATE_INFO_EXT:
        StructPtrFromApiDump<VkSwapchainCounterCreateInfoEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR:
        StructPtrFromApiDump<VkSwapchainCreateInfoKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_SWAPCHAIN_DISPLAY_NATIVE_HDR_CREATE_INFO_AMD:
        StructPtrFromApiDump<VkSwapchainDisplayNativeHdrCreateInfoAMD>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_SWAPCHAIN_FLAGS_SURFACE_CAPABILITIES_EXT:
        StructPtrFromApiDump<VkSwapchainFlagsSurfaceCapabilitiesEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_SWAPCHAIN_LATENCY_CREATE_INFO_NV:
        StructPtrFromApiDump<VkSwapchainLatencyCreateInfoNV>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_SWAPCHAIN_PRESENT_BARRIER_CREATE_INFO_NV:
        StructPtrFromApiDump<VkSwapchainPresentBarrierCreateInfoNV>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_SWAPCHAIN_PRESENT_FENCE_INFO_KHR:
        StructPtrFromApiDump<VkSwapchainPresentFenceInfoKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_SWAPCHAIN_PRESENT_MODE_INFO_KHR:
        StructPtrFromApiDump<VkSwapchainPresentModeInfoKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_SWAPCHAIN_PRESENT_MODES_CREATE_INFO_KHR:
        StructPtrFromApiDump<VkSwapchainPresentModesCreateInfoKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_SWAPCHAIN_PRESENT_SCALING_CREATE_INFO_KHR:
        StructPtrFromApiDump<VkSwapchainPresentScalingCreateInfoKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_SWAPCHAIN_TIME_DOMAIN_PROPERTIES_EXT:
        StructPtrFromApiDump<VkSwapchainTimeDomainPropertiesEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_SWAPCHAIN_TIMING_PROPERTIES_EXT:
        StructPtrFromApiDump<VkSwapchainTimingPropertiesEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_TENSOR_CAPTURE_DESCRIPTOR_DATA_INFO_ARM:
        StructPtrFromApiDump<VkTensorCaptureDescriptorDataInfoARM>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_TENSOR_COPY_ARM:
        StructPtrFromApiDump<VkTensorCopyARM>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_TENSOR_CREATE_INFO_ARM:
        StructPtrFromApiDump<VkTensorCreateInfoARM>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_TENSOR_DEPENDENCY_INFO_ARM:
        StructPtrFromApiDump<VkTensorDependencyInfoARM>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_TENSOR_DESCRIPTION_ARM:
        StructPtrFromApiDump<VkTensorDescriptionARM>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_TENSOR_EXPLICIT_TILING_FORMAT_PROPERTIES_ARM:
        StructPtrFromApiDump<VkTensorExplicitTilingFormatPropertiesARM>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_TENSOR_FORMAT_PROPERTIES_ARM:
        StructPtrFromApiDump<VkTensorFormatPropertiesARM>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_TENSOR_MEMORY_BARRIER_ARM:
        StructPtrFromApiDump<VkTensorMemoryBarrierARM>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_TENSOR_MEMORY_REQUIREMENTS_INFO_ARM:
        StructPtrFromApiDump<VkTensorMemoryRequirementsInfoARM>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_TENSOR_ROLLING_BACKING_CREATE_INFO_ARM:
        StructPtrFromApiDump<VkTensorRollingBackingCreateInfoARM>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_TENSOR_VIEW_CAPTURE_DESCRIPTOR_DATA_INFO_ARM:
        StructPtrFromApiDump<VkTensorViewCaptureDescriptorDataInfoARM>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_TENSOR_VIEW_CREATE_INFO_ARM:
        StructPtrFromApiDump<VkTensorViewCreateInfoARM>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_TEXTURE_LOD_GATHER_FORMAT_PROPERTIES_AMD:
        StructPtrFromApiDump<VkTextureLODGatherFormatPropertiesAMD>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_THROTTLE_HINT_SUBMIT_INFO_SEC:
        StructPtrFromApiDump<VkThrottleHintSubmitInfoSEC>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_TILE_MEMORY_BIND_INFO_QCOM:
        StructPtrFromApiDump<VkTileMemoryBindInfoQCOM>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_TILE_MEMORY_REQUIREMENTS_QCOM:
        StructPtrFromApiDump<VkTileMemoryRequirementsQCOM>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_TILE_MEMORY_SIZE_INFO_QCOM:
        StructPtrFromApiDump<VkTileMemorySizeInfoQCOM>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_TILE_PROPERTIES_QCOM:
        StructPtrFromApiDump<VkTilePropertiesQCOM>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_TIMELINE_SEMAPHORE_SUBMIT_INFO:
        StructPtrFromApiDump<VkTimelineSemaphoreSubmitInfo>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_VALIDATION_CACHE_CREATE_INFO_EXT:
        StructPtrFromApiDump<VkValidationCacheCreateInfoEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_VALIDATION_FEATURES_EXT:
        StructPtrFromApiDump<VkValidationFeaturesEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_VALIDATION_FLAGS_EXT:
        StructPtrFromApiDump<VkValidationFlagsEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_VERTEX_INPUT_ATTRIBUTE_DESCRIPTION_2_EXT:
        StructPtrFromApiDump<VkVertexInputAttributeDescription2EXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_VERTEX_INPUT_BINDING_DESCRIPTION_2_EXT:
        StructPtrFromApiDump<VkVertexInputBindingDescription2EXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_VI_SURFACE_CREATE_INFO_NN:
        StructPtrFromApiDump<VkViSurfaceCreateInfoNN>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_VIDEO_BEGIN_CODING_INFO_KHR:
        StructPtrFromApiDump<VkVideoBeginCodingInfoKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_VIDEO_CAPABILITIES_KHR:
        StructPtrFromApiDump<VkVideoCapabilitiesKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_VIDEO_CODING_CONTROL_INFO_KHR:
        StructPtrFromApiDump<VkVideoCodingControlInfoKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_VIDEO_DECODE_AV1_CAPABILITIES_KHR:
        StructPtrFromApiDump<VkVideoDecodeAV1CapabilitiesKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_VIDEO_DECODE_AV1_DPB_SLOT_INFO_KHR:
        StructPtrFromApiDump<VkVideoDecodeAV1DpbSlotInfoKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_VIDEO_DECODE_AV1_PICTURE_INFO_KHR:
        StructPtrFromApiDump<VkVideoDecodeAV1PictureInfoKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_VIDEO_DECODE_AV1_PROFILE_INFO_KHR:
        StructPtrFromApiDump<VkVideoDecodeAV1ProfileInfoKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_VIDEO_DECODE_AV1_SESSION_PARAMETERS_CREATE_INFO_KHR:
        StructPtrFromApiDump<VkVideoDecodeAV1SessionParametersCreateInfoKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_VIDEO_DECODE_CAPABILITIES_KHR:
        StructPtrFromApiDump<VkVideoDecodeCapabilitiesKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_VIDEO_DECODE_H264_CAPABILITIES_KHR:
        StructPtrFromApiDump<VkVideoDecodeH264CapabilitiesKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_VIDEO_DECODE_H264_DPB_SLOT_INFO_KHR:
        StructPtrFromApiDump<VkVideoDecodeH264DpbSlotInfoKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_VIDEO_DECODE_H264_PICTURE_INFO_KHR:
        StructPtrFromApiDump<VkVideoDecodeH264PictureInfoKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_VIDEO_DECODE_H264_PROFILE_INFO_KHR:
        StructPtrFromApiDump<VkVideoDecodeH264ProfileInfoKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_VIDEO_DECODE_H264_SESSION_PARAMETERS_ADD_INFO_KHR:
        StructPtrFromApiDump<VkVideoDecodeH264SessionParametersAddInfoKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_VIDEO_DECODE_H264_SESSION_PARAMETERS_CREATE_INFO_KHR:
        StructPtrFromApiDump<VkVideoDecodeH264SessionParametersCreateInfoKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_VIDEO_DECODE_INFO_KHR:
        StructPtrFromApiDump<VkVideoDecodeInfoKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_VIDEO_DECODE_USAGE_INFO_KHR:
        StructPtrFromApiDump<VkVideoDecodeUsageInfoKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_VIDEO_DECODE_VP9_CAPABILITIES_KHR:
        StructPtrFromApiDump<VkVideoDecodeVP9CapabilitiesKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_VIDEO_DECODE_VP9_PICTURE_INFO_KHR:
        StructPtrFromApiDump<VkVideoDecodeVP9PictureInfoKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_VIDEO_DECODE_VP9_PROFILE_INFO_KHR:
        StructPtrFromApiDump<VkVideoDecodeVP9ProfileInfoKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_VIDEO_ENCODE_AV1_CAPABILITIES_KHR:
        StructPtrFromApiDump<VkVideoEncodeAV1CapabilitiesKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_VIDEO_ENCODE_AV1_DPB_SLOT_INFO_KHR:
        StructPtrFromApiDump<VkVideoEncodeAV1DpbSlotInfoKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_VIDEO_ENCODE_AV1_GOP_REMAINING_FRAME_INFO_KHR:
        StructPtrFromApiDump<VkVideoEncodeAV1GopRemainingFrameInfoKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_VIDEO_ENCODE_AV1_PICTURE_INFO_KHR:
        StructPtrFromApiDump<VkVideoEncodeAV1PictureInfoKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_VIDEO_ENCODE_AV1_PROFILE_INFO_KHR:
        StructPtrFromApiDump<VkVideoEncodeAV1ProfileInfoKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_VIDEO_ENCODE_AV1_QUALITY_LEVEL_PROPERTIES_KHR:
        StructPtrFromApiDump<VkVideoEncodeAV1QualityLevelPropertiesKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_VIDEO_ENCODE_AV1_QUANTIZATION_MAP_CAPABILITIES_KHR:
        StructPtrFromApiDump<VkVideoEncodeAV1QuantizationMapCapabilitiesKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_VIDEO_ENCODE_AV1_RATE_CONTROL_INFO_KHR:
        StructPtrFromApiDump<VkVideoEncodeAV1RateControlInfoKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_VIDEO_ENCODE_AV1_RATE_CONTROL_LAYER_INFO_KHR:
        StructPtrFromApiDump<VkVideoEncodeAV1RateControlLayerInfoKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_VIDEO_ENCODE_AV1_SESSION_CREATE_INFO_KHR:
        StructPtrFromApiDump<VkVideoEncodeAV1SessionCreateInfoKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_VIDEO_ENCODE_AV1_SESSION_PARAMETERS_CREATE_INFO_KHR:
        StructPtrFromApiDump<VkVideoEncodeAV1SessionParametersCreateInfoKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_VIDEO_ENCODE_CAPABILITIES_KHR:
        StructPtrFromApiDump<VkVideoEncodeCapabilitiesKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_VIDEO_ENCODE_FEEDBACK_2_CAPABILITIES_KHR:
        StructPtrFromApiDump<VkVideoEncodeFeedback2CapabilitiesKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_VIDEO_ENCODE_H264_CAPABILITIES_KHR:
        StructPtrFromApiDump<VkVideoEncodeH264CapabilitiesKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_VIDEO_ENCODE_H264_DPB_SLOT_INFO_KHR:
        StructPtrFromApiDump<VkVideoEncodeH264DpbSlotInfoKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_VIDEO_ENCODE_H264_GOP_REMAINING_FRAME_INFO_KHR:
        StructPtrFromApiDump<VkVideoEncodeH264GopRemainingFrameInfoKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_VIDEO_ENCODE_H264_NALU_SLICE_INFO_KHR:
        StructPtrFromApiDump<VkVideoEncodeH264NaluSliceInfoKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_VIDEO_ENCODE_H264_PICTURE_INFO_KHR:
        StructPtrFromApiDump<VkVideoEncodeH264PictureInfoKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_VIDEO_ENCODE_H264_PROFILE_INFO_KHR:
        StructPtrFromApiDump<VkVideoEncodeH264ProfileInfoKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_VIDEO_ENCODE_H264_QUALITY_LEVEL_PROPERTIES_KHR:
        StructPtrFromApiDump<VkVideoEncodeH264QualityLevelPropertiesKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_VIDEO_ENCODE_H264_QUANTIZATION_MAP_CAPABILITIES_KHR:
        StructPtrFromApiDump<VkVideoEncodeH264QuantizationMapCapabilitiesKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_VIDEO_ENCODE_H264_RATE_CONTROL_INFO_KHR:
        StructPtrFromApiDump<VkVideoEncodeH264RateControlInfoKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_VIDEO_ENCODE_H264_RATE_CONTROL_LAYER_INFO_KHR:
        StructPtrFromApiDump<VkVideoEncodeH264RateControlLayerInfoKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_VIDEO_ENCODE_H264_SESSION_CREATE_INFO_KHR:
        StructPtrFromApiDump<VkVideoEncodeH264SessionCreateInfoKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_VIDEO_ENCODE_H264_SESSION_PARAMETERS_ADD_INFO_KHR:
        StructPtrFromApiDump<VkVideoEncodeH264SessionParametersAddInfoKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_VIDEO_ENCODE_H264_SESSION_PARAMETERS_CREATE_INFO_KHR:
        StructPtrFromApiDump<VkVideoEncodeH264SessionParametersCreateInfoKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_VIDEO_ENCODE_H264_SESSION_PARAMETERS_FEEDBACK_INFO_KHR:
        StructPtrFromApiDump<VkVideoEncodeH264SessionParametersFeedbackInfoKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_VIDEO_ENCODE_H264_SESSION_PARAMETERS_GET_INFO_KHR:
        StructPtrFromApiDump<VkVideoEncodeH264SessionParametersGetInfoKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_VIDEO_ENCODE_H265_QUANTIZATION_MAP_CAPABILITIES_KHR:
        StructPtrFromApiDump<VkVideoEncodeH265QuantizationMapCapabilitiesKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_VIDEO_ENCODE_INFO_KHR:
        StructPtrFromApiDump<VkVideoEncodeInfoKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_VIDEO_ENCODE_INTRA_REFRESH_CAPABILITIES_KHR:
        StructPtrFromApiDump<VkVideoEncodeIntraRefreshCapabilitiesKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_VIDEO_ENCODE_INTRA_REFRESH_INFO_KHR:
        StructPtrFromApiDump<VkVideoEncodeIntraRefreshInfoKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_VIDEO_ENCODE_PROFILE_RGB_CONVERSION_INFO_VALVE:
        StructPtrFromApiDump<VkVideoEncodeProfileRgbConversionInfoVALVE>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_VIDEO_ENCODE_QUALITY_LEVEL_INFO_KHR:
        StructPtrFromApiDump<VkVideoEncodeQualityLevelInfoKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_VIDEO_ENCODE_QUALITY_LEVEL_PROPERTIES_KHR:
        StructPtrFromApiDump<VkVideoEncodeQualityLevelPropertiesKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_VIDEO_ENCODE_QUANTIZATION_MAP_CAPABILITIES_KHR:
        StructPtrFromApiDump<VkVideoEncodeQuantizationMapCapabilitiesKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_VIDEO_ENCODE_QUANTIZATION_MAP_INFO_KHR:
        StructPtrFromApiDump<VkVideoEncodeQuantizationMapInfoKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_VIDEO_ENCODE_QUANTIZATION_MAP_SESSION_PARAMETERS_CREATE_INFO_KHR:
        StructPtrFromApiDump<VkVideoEncodeQuantizationMapSessionParametersCreateInfoKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_VIDEO_ENCODE_RATE_CONTROL_INFO_KHR:
        StructPtrFromApiDump<VkVideoEncodeRateControlInfoKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_VIDEO_ENCODE_RATE_CONTROL_LAYER_INFO_KHR:
        StructPtrFromApiDump<VkVideoEncodeRateControlLayerInfoKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_VIDEO_ENCODE_RGB_CONVERSION_CAPABILITIES_VALVE:
        StructPtrFromApiDump<VkVideoEncodeRgbConversionCapabilitiesVALVE>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_VIDEO_ENCODE_SESSION_INTRA_REFRESH_CREATE_INFO_KHR:
        StructPtrFromApiDump<VkVideoEncodeSessionIntraRefreshCreateInfoKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_VIDEO_ENCODE_SESSION_PARAMETERS_FEEDBACK_INFO_KHR:
        StructPtrFromApiDump<VkVideoEncodeSessionParametersFeedbackInfoKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_VIDEO_ENCODE_SESSION_PARAMETERS_GET_INFO_KHR:
        StructPtrFromApiDump<VkVideoEncodeSessionParametersGetInfoKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_VIDEO_ENCODE_SESSION_RGB_CONVERSION_CREATE_INFO_VALVE:
        StructPtrFromApiDump<VkVideoEncodeSessionRgbConversionCreateInfoVALVE>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_VIDEO_ENCODE_USAGE_INFO_KHR:
        StructPtrFromApiDump<VkVideoEncodeUsageInfoKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_VIDEO_END_CODING_INFO_KHR:
        StructPtrFromApiDump<VkVideoEndCodingInfoKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_VIDEO_FORMAT_AV1_QUANTIZATION_MAP_PROPERTIES_KHR:
        StructPtrFromApiDump<VkVideoFormatAV1QuantizationMapPropertiesKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_VIDEO_FORMAT_H265_QUANTIZATION_MAP_PROPERTIES_KHR:
        StructPtrFromApiDump<VkVideoFormatH265QuantizationMapPropertiesKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_VIDEO_FORMAT_PROPERTIES_KHR:
        StructPtrFromApiDump<VkVideoFormatPropertiesKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_VIDEO_FORMAT_QUANTIZATION_MAP_PROPERTIES_KHR:
        StructPtrFromApiDump<VkVideoFormatQuantizationMapPropertiesKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_VIDEO_INLINE_QUERY_INFO_KHR:
        StructPtrFromApiDump<VkVideoInlineQueryInfoKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_VIDEO_PICTURE_RESOURCE_INFO_KHR:
        StructPtrFromApiDump<VkVideoPictureResourceInfoKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_VIDEO_PROFILE_INFO_KHR:
        StructPtrFromApiDump<VkVideoProfileInfoKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_VIDEO_PROFILE_LIST_INFO_KHR:
        StructPtrFromApiDump<VkVideoProfileListInfoKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_VIDEO_REFERENCE_INTRA_REFRESH_INFO_KHR:
        StructPtrFromApiDump<VkVideoReferenceIntraRefreshInfoKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_VIDEO_REFERENCE_SLOT_INFO_KHR:
        StructPtrFromApiDump<VkVideoReferenceSlotInfoKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_VIDEO_SESSION_CREATE_INFO_KHR:
        StructPtrFromApiDump<VkVideoSessionCreateInfoKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_VIDEO_SESSION_MEMORY_REQUIREMENTS_KHR:
        StructPtrFromApiDump<VkVideoSessionMemoryRequirementsKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_VIDEO_SESSION_PARAMETERS_CREATE_INFO_KHR:
        StructPtrFromApiDump<VkVideoSessionParametersCreateInfoKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_VIDEO_SESSION_PARAMETERS_UPDATE_INFO_KHR:
        StructPtrFromApiDump<VkVideoSessionParametersUpdateInfoKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_WAYLAND_SURFACE_CREATE_INFO_KHR:
        StructPtrFromApiDump<VkWaylandSurfaceCreateInfoKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_WIN32_KEYED_MUTEX_ACQUIRE_RELEASE_INFO_KHR:
        StructPtrFromApiDump<VkWin32KeyedMutexAcquireReleaseInfoKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_WIN32_KEYED_MUTEX_ACQUIRE_RELEASE_INFO_NV:
        StructPtrFromApiDump<VkWin32KeyedMutexAcquireReleaseInfoNV>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR:
        StructPtrFromApiDump<VkWin32SurfaceCreateInfoKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET_ACCELERATION_STRUCTURE_KHR:
        StructPtrFromApiDump<VkWriteDescriptorSetAccelerationStructureKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET_ACCELERATION_STRUCTURE_NV:
        StructPtrFromApiDump<VkWriteDescriptorSetAccelerationStructureNV>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET_INLINE_UNIFORM_BLOCK:
        StructPtrFromApiDump<VkWriteDescriptorSetInlineUniformBlock>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET_PARTITIONED_ACCELERATION_STRUCTURE_NV:
        StructPtrFromApiDump<VkWriteDescriptorSetPartitionedAccelerationStructureNV>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET_TENSOR_ARM:
        StructPtrFromApiDump<VkWriteDescriptorSetTensorARM>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_WRITE_INDIRECT_EXECUTION_SET_PIPELINE_EXT:
        StructPtrFromApiDump<VkWriteIndirectExecutionSetPipelineEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_WRITE_INDIRECT_EXECUTION_SET_SHADER_EXT:
        StructPtrFromApiDump<VkWriteIndirectExecutionSetShaderEXT>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_XCB_SURFACE_CREATE_INFO_KHR:
        StructPtrFromApiDump<VkXcbSurfaceCreateInfoKHR>(ctx, value);
        break;
    case VK_STRUCTURE_TYPE_XLIB_SURFACE_CREATE_INFO_KHR:
        StructPtrFromApiDump<VkXlibSurfaceCreateInfoKHR>(ctx, value);
        break;
    default:
        ++ctx.MutableStats().unknown_structure_types;
        GFXRECON_LOG_WARNING("PNextFromApiDump: unrecognized structure type %d", stype);
        ctx.Encoder().EncodeStructPtrPreamble(0, true, false);
        break;
    }
}

GFXRECON_END_NAMESPACE(decode)
GFXRECON_END_NAMESPACE(gfxrecon)
