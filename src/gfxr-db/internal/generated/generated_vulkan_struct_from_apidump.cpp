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

#include "generated_vulkan_struct_from_apidump.h"

#include "apidump_struct_encode.h"
#include "generated_vulkan_enum_from_string.h"

GFXRECON_BEGIN_NAMESPACE(gfxrecon)
GFXRECON_BEGIN_NAMESPACE(decode)

template <> void StructFromApiDump<StdVideoH264SpsVuiFlags>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.UInt32Value(value["aspect_ratio_info_present_flag"]);
    ctx.UInt32Value(value["overscan_info_present_flag"]);
    ctx.UInt32Value(value["overscan_appropriate_flag"]);
    ctx.UInt32Value(value["video_signal_type_present_flag"]);
    ctx.UInt32Value(value["video_full_range_flag"]);
    ctx.UInt32Value(value["color_description_present_flag"]);
    ctx.UInt32Value(value["chroma_loc_info_present_flag"]);
    ctx.UInt32Value(value["timing_info_present_flag"]);
    ctx.UInt32Value(value["fixed_frame_rate_flag"]);
    ctx.UInt32Value(value["bitstream_restriction_flag"]);
    ctx.UInt32Value(value["nal_hrd_parameters_present_flag"]);
    ctx.UInt32Value(value["vcl_hrd_parameters_present_flag"]);
}

template <> void StructFromApiDump<StdVideoH264HrdParameters>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.UInt8Value(value["cpb_cnt_minus1"]);
    ctx.UInt8Value(value["bit_rate_scale"]);
    ctx.UInt8Value(value["cpb_size_scale"]);
    ctx.UInt8Value(value["reserved1"]);
    ctx.UInt32Array(value["bit_rate_value_minus1"]);
    ctx.UInt32Array(value["cpb_size_value_minus1"]);
    ctx.UInt8Array(value["cbr_flag"]);
    ctx.UInt32Value(value["initial_cpb_removal_delay_length_minus1"]);
    ctx.UInt32Value(value["cpb_removal_delay_length_minus1"]);
    ctx.UInt32Value(value["dpb_output_delay_length_minus1"]);
    ctx.UInt32Value(value["time_offset_length"]);
}

template <> void StructFromApiDump<StdVideoH264SequenceParameterSetVui>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    StructFromApiDump<StdVideoH264SpsVuiFlags>(ctx, value["flags"]);
    ctx.EnumValue(value["aspect_ratio_idc"], EnumFromString_StdVideoH264AspectRatioIdc);
    ctx.UInt16Value(value["sar_width"]);
    ctx.UInt16Value(value["sar_height"]);
    ctx.UInt8Value(value["video_format"]);
    ctx.UInt8Value(value["colour_primaries"]);
    ctx.UInt8Value(value["transfer_characteristics"]);
    ctx.UInt8Value(value["matrix_coefficients"]);
    ctx.UInt32Value(value["num_units_in_tick"]);
    ctx.UInt32Value(value["time_scale"]);
    ctx.UInt8Value(value["max_num_reorder_frames"]);
    ctx.UInt8Value(value["max_dec_frame_buffering"]);
    ctx.UInt8Value(value["chroma_sample_loc_type_top_field"]);
    ctx.UInt8Value(value["chroma_sample_loc_type_bottom_field"]);
    ctx.UInt32Value(value["reserved1"]);
    StructPtrFromApiDump<StdVideoH264HrdParameters>(ctx, value["pHrdParameters"]);
}

template <> void StructFromApiDump<StdVideoH264SpsFlags>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.UInt32Value(value["constraint_set0_flag"]);
    ctx.UInt32Value(value["constraint_set1_flag"]);
    ctx.UInt32Value(value["constraint_set2_flag"]);
    ctx.UInt32Value(value["constraint_set3_flag"]);
    ctx.UInt32Value(value["constraint_set4_flag"]);
    ctx.UInt32Value(value["constraint_set5_flag"]);
    ctx.UInt32Value(value["direct_8x8_inference_flag"]);
    ctx.UInt32Value(value["mb_adaptive_frame_field_flag"]);
    ctx.UInt32Value(value["frame_mbs_only_flag"]);
    ctx.UInt32Value(value["delta_pic_order_always_zero_flag"]);
    ctx.UInt32Value(value["separate_colour_plane_flag"]);
    ctx.UInt32Value(value["gaps_in_frame_num_value_allowed_flag"]);
    ctx.UInt32Value(value["qpprime_y_zero_transform_bypass_flag"]);
    ctx.UInt32Value(value["frame_cropping_flag"]);
    ctx.UInt32Value(value["seq_scaling_matrix_present_flag"]);
    ctx.UInt32Value(value["vui_parameters_present_flag"]);
}

template <> void StructFromApiDump<StdVideoH264ScalingLists>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.UInt16Value(value["scaling_list_present_mask"]);
    ctx.UInt16Value(value["use_default_scaling_matrix_mask"]);
    ctx.UInt8Array(value["ScalingList4x4"]);
    ctx.UInt8Array(value["ScalingList8x8"]);
}

template <> void StructFromApiDump<StdVideoH264SequenceParameterSet>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    StructFromApiDump<StdVideoH264SpsFlags>(ctx, value["flags"]);
    ctx.EnumValue(value["profile_idc"], EnumFromString_StdVideoH264ProfileIdc);
    ctx.EnumValue(value["level_idc"], EnumFromString_StdVideoH264LevelIdc);
    ctx.EnumValue(value["chroma_format_idc"], EnumFromString_StdVideoH264ChromaFormatIdc);
    ctx.UInt8Value(value["seq_parameter_set_id"]);
    ctx.UInt8Value(value["bit_depth_luma_minus8"]);
    ctx.UInt8Value(value["bit_depth_chroma_minus8"]);
    ctx.UInt8Value(value["log2_max_frame_num_minus4"]);
    ctx.EnumValue(value["pic_order_cnt_type"], EnumFromString_StdVideoH264PocType);
    ctx.Int32Value(value["offset_for_non_ref_pic"]);
    ctx.Int32Value(value["offset_for_top_to_bottom_field"]);
    ctx.UInt8Value(value["log2_max_pic_order_cnt_lsb_minus4"]);
    ctx.UInt8Value(value["num_ref_frames_in_pic_order_cnt_cycle"]);
    ctx.UInt8Value(value["max_num_ref_frames"]);
    ctx.UInt8Value(value["reserved1"]);
    ctx.UInt32Value(value["pic_width_in_mbs_minus1"]);
    ctx.UInt32Value(value["pic_height_in_map_units_minus1"]);
    ctx.UInt32Value(value["frame_crop_left_offset"]);
    ctx.UInt32Value(value["frame_crop_right_offset"]);
    ctx.UInt32Value(value["frame_crop_top_offset"]);
    ctx.UInt32Value(value["frame_crop_bottom_offset"]);
    ctx.UInt32Value(value["reserved2"]);
    ctx.Int32Array(value["pOffsetForRefFrame"], ctx.Length(value["num_ref_frames_in_pic_order_cnt_cycle"]));
    StructPtrFromApiDump<StdVideoH264ScalingLists>(ctx, value["pScalingLists"]);
    StructPtrFromApiDump<StdVideoH264SequenceParameterSetVui>(ctx, value["pSequenceParameterSetVui"]);
}

template <> void StructFromApiDump<StdVideoH264PpsFlags>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.UInt32Value(value["transform_8x8_mode_flag"]);
    ctx.UInt32Value(value["redundant_pic_cnt_present_flag"]);
    ctx.UInt32Value(value["constrained_intra_pred_flag"]);
    ctx.UInt32Value(value["deblocking_filter_control_present_flag"]);
    ctx.UInt32Value(value["weighted_pred_flag"]);
    ctx.UInt32Value(value["bottom_field_pic_order_in_frame_present_flag"]);
    ctx.UInt32Value(value["entropy_coding_mode_flag"]);
    ctx.UInt32Value(value["pic_scaling_matrix_present_flag"]);
}

template <> void StructFromApiDump<StdVideoH264PictureParameterSet>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    StructFromApiDump<StdVideoH264PpsFlags>(ctx, value["flags"]);
    ctx.UInt8Value(value["seq_parameter_set_id"]);
    ctx.UInt8Value(value["pic_parameter_set_id"]);
    ctx.UInt8Value(value["num_ref_idx_l0_default_active_minus1"]);
    ctx.UInt8Value(value["num_ref_idx_l1_default_active_minus1"]);
    ctx.EnumValue(value["weighted_bipred_idc"], EnumFromString_StdVideoH264WeightedBipredIdc);
    ctx.Int8Value(value["pic_init_qp_minus26"]);
    ctx.Int8Value(value["pic_init_qs_minus26"]);
    ctx.Int8Value(value["chroma_qp_index_offset"]);
    ctx.Int8Value(value["second_chroma_qp_index_offset"]);
    StructPtrFromApiDump<StdVideoH264ScalingLists>(ctx, value["pScalingLists"]);
}

template <> void StructFromApiDump<StdVideoDecodeH264PictureInfoFlags>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.UInt32Value(value["field_pic_flag"]);
    ctx.UInt32Value(value["is_intra"]);
    ctx.UInt32Value(value["IdrPicFlag"]);
    ctx.UInt32Value(value["bottom_field_flag"]);
    ctx.UInt32Value(value["is_reference"]);
    ctx.UInt32Value(value["complementary_field_pair"]);
}

template <> void StructFromApiDump<StdVideoDecodeH264PictureInfo>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    StructFromApiDump<StdVideoDecodeH264PictureInfoFlags>(ctx, value["flags"]);
    ctx.UInt8Value(value["seq_parameter_set_id"]);
    ctx.UInt8Value(value["pic_parameter_set_id"]);
    ctx.UInt8Value(value["reserved1"]);
    ctx.UInt8Value(value["reserved2"]);
    ctx.UInt16Value(value["frame_num"]);
    ctx.UInt16Value(value["idr_pic_id"]);
    ctx.Int32Array(value["PicOrderCnt"]);
}

template <> void StructFromApiDump<StdVideoDecodeH264ReferenceInfoFlags>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.UInt32Value(value["top_field_flag"]);
    ctx.UInt32Value(value["bottom_field_flag"]);
    ctx.UInt32Value(value["used_for_long_term_reference"]);
    ctx.UInt32Value(value["is_non_existing"]);
}

template <> void StructFromApiDump<StdVideoDecodeH264ReferenceInfo>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    StructFromApiDump<StdVideoDecodeH264ReferenceInfoFlags>(ctx, value["flags"]);
    ctx.UInt16Value(value["FrameNum"]);
    ctx.UInt16Value(value["reserved"]);
    ctx.Int32Array(value["PicOrderCnt"]);
}

template <> void StructFromApiDump<StdVideoEncodeH264WeightTableFlags>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.UInt32Value(value["luma_weight_l0_flag"]);
    ctx.UInt32Value(value["chroma_weight_l0_flag"]);
    ctx.UInt32Value(value["luma_weight_l1_flag"]);
    ctx.UInt32Value(value["chroma_weight_l1_flag"]);
}

template <> void StructFromApiDump<StdVideoEncodeH264WeightTable>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    StructFromApiDump<StdVideoEncodeH264WeightTableFlags>(ctx, value["flags"]);
    ctx.UInt8Value(value["luma_log2_weight_denom"]);
    ctx.UInt8Value(value["chroma_log2_weight_denom"]);
    ctx.Int8Array(value["luma_weight_l0"]);
    ctx.Int8Array(value["luma_offset_l0"]);
    ctx.Int8Array(value["chroma_weight_l0"]);
    ctx.Int8Array(value["chroma_offset_l0"]);
    ctx.Int8Array(value["luma_weight_l1"]);
    ctx.Int8Array(value["luma_offset_l1"]);
    ctx.Int8Array(value["chroma_weight_l1"]);
    ctx.Int8Array(value["chroma_offset_l1"]);
}

template <> void StructFromApiDump<StdVideoEncodeH264SliceHeaderFlags>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.UInt32Value(value["direct_spatial_mv_pred_flag"]);
    ctx.UInt32Value(value["num_ref_idx_active_override_flag"]);
    ctx.UInt32Value(value["reserved"]);
}

template <> void StructFromApiDump<StdVideoEncodeH264PictureInfoFlags>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.UInt32Value(value["IdrPicFlag"]);
    ctx.UInt32Value(value["is_reference"]);
    ctx.UInt32Value(value["no_output_of_prior_pics_flag"]);
    ctx.UInt32Value(value["long_term_reference_flag"]);
    ctx.UInt32Value(value["adaptive_ref_pic_marking_mode_flag"]);
    ctx.UInt32Value(value["reserved"]);
}

template <> void StructFromApiDump<StdVideoEncodeH264ReferenceInfoFlags>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.UInt32Value(value["used_for_long_term_reference"]);
    ctx.UInt32Value(value["reserved"]);
}

template <> void StructFromApiDump<StdVideoEncodeH264ReferenceListsInfoFlags>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.UInt32Value(value["ref_pic_list_modification_flag_l0"]);
    ctx.UInt32Value(value["ref_pic_list_modification_flag_l1"]);
    ctx.UInt32Value(value["reserved"]);
}

template <> void StructFromApiDump<StdVideoEncodeH264RefListModEntry>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["modification_of_pic_nums_idc"], EnumFromString_StdVideoH264ModificationOfPicNumsIdc);
    ctx.UInt16Value(value["abs_diff_pic_num_minus1"]);
    ctx.UInt16Value(value["long_term_pic_num"]);
}

template <> void StructFromApiDump<StdVideoEncodeH264RefPicMarkingEntry>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["memory_management_control_operation"], EnumFromString_StdVideoH264MemMgmtControlOp);
    ctx.UInt16Value(value["difference_of_pic_nums_minus1"]);
    ctx.UInt16Value(value["long_term_pic_num"]);
    ctx.UInt16Value(value["long_term_frame_idx"]);
    ctx.UInt16Value(value["max_long_term_frame_idx_plus1"]);
}

template <> void StructFromApiDump<StdVideoEncodeH264ReferenceListsInfo>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    StructFromApiDump<StdVideoEncodeH264ReferenceListsInfoFlags>(ctx, value["flags"]);
    ctx.UInt8Value(value["num_ref_idx_l0_active_minus1"]);
    ctx.UInt8Value(value["num_ref_idx_l1_active_minus1"]);
    ctx.UInt8Array(value["RefPicList0"]);
    ctx.UInt8Array(value["RefPicList1"]);
    ctx.UInt8Value(value["refList0ModOpCount"]);
    ctx.UInt8Value(value["refList1ModOpCount"]);
    ctx.UInt8Value(value["refPicMarkingOpCount"]);
    ctx.UInt8Array(value["reserved1"], 7);
    StructArrayFromApiDump<StdVideoEncodeH264RefListModEntry>(ctx, value["pRefList0ModOperations"], ctx.Length(value["refList0ModOpCount"]));
    StructArrayFromApiDump<StdVideoEncodeH264RefListModEntry>(ctx, value["pRefList1ModOperations"], ctx.Length(value["refList1ModOpCount"]));
    StructArrayFromApiDump<StdVideoEncodeH264RefPicMarkingEntry>(ctx, value["pRefPicMarkingOperations"], ctx.Length(value["refPicMarkingOpCount"]));
}

template <> void StructFromApiDump<StdVideoEncodeH264PictureInfo>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    StructFromApiDump<StdVideoEncodeH264PictureInfoFlags>(ctx, value["flags"]);
    ctx.UInt8Value(value["seq_parameter_set_id"]);
    ctx.UInt8Value(value["pic_parameter_set_id"]);
    ctx.UInt16Value(value["idr_pic_id"]);
    ctx.EnumValue(value["primary_pic_type"], EnumFromString_StdVideoH264PictureType);
    ctx.UInt32Value(value["frame_num"]);
    ctx.Int32Value(value["PicOrderCnt"]);
    ctx.UInt8Value(value["temporal_id"]);
    ctx.UInt8Array(value["reserved1"], 3);
    StructPtrFromApiDump<StdVideoEncodeH264ReferenceListsInfo>(ctx, value["pRefLists"]);
}

template <> void StructFromApiDump<StdVideoEncodeH264ReferenceInfo>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    StructFromApiDump<StdVideoEncodeH264ReferenceInfoFlags>(ctx, value["flags"]);
    ctx.EnumValue(value["primary_pic_type"], EnumFromString_StdVideoH264PictureType);
    ctx.UInt32Value(value["FrameNum"]);
    ctx.Int32Value(value["PicOrderCnt"]);
    ctx.UInt16Value(value["long_term_pic_num"]);
    ctx.UInt16Value(value["long_term_frame_idx"]);
    ctx.UInt8Value(value["temporal_id"]);
}

template <> void StructFromApiDump<StdVideoEncodeH264SliceHeader>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    StructFromApiDump<StdVideoEncodeH264SliceHeaderFlags>(ctx, value["flags"]);
    ctx.UInt32Value(value["first_mb_in_slice"]);
    ctx.EnumValue(value["slice_type"], EnumFromString_StdVideoH264SliceType);
    ctx.Int8Value(value["slice_alpha_c0_offset_div2"]);
    ctx.Int8Value(value["slice_beta_offset_div2"]);
    ctx.Int8Value(value["slice_qp_delta"]);
    ctx.UInt8Value(value["reserved1"]);
    ctx.EnumValue(value["cabac_init_idc"], EnumFromString_StdVideoH264CabacInitIdc);
    ctx.EnumValue(value["disable_deblocking_filter_idc"], EnumFromString_StdVideoH264DisableDeblockingFilterIdc);
    StructPtrFromApiDump<StdVideoEncodeH264WeightTable>(ctx, value["pWeightTable"]);
}

template <> void StructFromApiDump<StdVideoVP9ColorConfigFlags>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.UInt32Value(value["color_range"]);
    ctx.UInt32Value(value["reserved"]);
}

template <> void StructFromApiDump<StdVideoVP9ColorConfig>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    StructFromApiDump<StdVideoVP9ColorConfigFlags>(ctx, value["flags"]);
    ctx.UInt8Value(value["BitDepth"]);
    ctx.UInt8Value(value["subsampling_x"]);
    ctx.UInt8Value(value["subsampling_y"]);
    ctx.UInt8Value(value["reserved1"]);
    ctx.EnumValue(value["color_space"], EnumFromString_StdVideoVP9ColorSpace);
}

template <> void StructFromApiDump<StdVideoVP9LoopFilterFlags>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.UInt32Value(value["loop_filter_delta_enabled"]);
    ctx.UInt32Value(value["loop_filter_delta_update"]);
    ctx.UInt32Value(value["reserved"]);
}

template <> void StructFromApiDump<StdVideoVP9LoopFilter>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    StructFromApiDump<StdVideoVP9LoopFilterFlags>(ctx, value["flags"]);
    ctx.UInt8Value(value["loop_filter_level"]);
    ctx.UInt8Value(value["loop_filter_sharpness"]);
    ctx.UInt8Value(value["update_ref_delta"]);
    ctx.Int8Array(value["loop_filter_ref_deltas"]);
    ctx.UInt8Value(value["update_mode_delta"]);
    ctx.Int8Array(value["loop_filter_mode_deltas"]);
}

template <> void StructFromApiDump<StdVideoVP9SegmentationFlags>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.UInt32Value(value["segmentation_update_map"]);
    ctx.UInt32Value(value["segmentation_temporal_update"]);
    ctx.UInt32Value(value["segmentation_update_data"]);
    ctx.UInt32Value(value["segmentation_abs_or_delta_update"]);
    ctx.UInt32Value(value["reserved"]);
}

template <> void StructFromApiDump<StdVideoVP9Segmentation>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    StructFromApiDump<StdVideoVP9SegmentationFlags>(ctx, value["flags"]);
    ctx.UInt8Array(value["segmentation_tree_probs"]);
    ctx.UInt8Array(value["segmentation_pred_prob"]);
    ctx.UInt8Array(value["FeatureEnabled"]);
    ctx.Int16Array(value["FeatureData"]);
}

template <> void StructFromApiDump<StdVideoDecodeVP9PictureInfoFlags>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.UInt32Value(value["error_resilient_mode"]);
    ctx.UInt32Value(value["intra_only"]);
    ctx.UInt32Value(value["allow_high_precision_mv"]);
    ctx.UInt32Value(value["refresh_frame_context"]);
    ctx.UInt32Value(value["frame_parallel_decoding_mode"]);
    ctx.UInt32Value(value["segmentation_enabled"]);
    ctx.UInt32Value(value["show_frame"]);
    ctx.UInt32Value(value["UsePrevFrameMvs"]);
    ctx.UInt32Value(value["reserved"]);
}

template <> void StructFromApiDump<StdVideoDecodeVP9PictureInfo>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    StructFromApiDump<StdVideoDecodeVP9PictureInfoFlags>(ctx, value["flags"]);
    ctx.EnumValue(value["profile"], EnumFromString_StdVideoVP9Profile);
    ctx.EnumValue(value["frame_type"], EnumFromString_StdVideoVP9FrameType);
    ctx.UInt8Value(value["frame_context_idx"]);
    ctx.UInt8Value(value["reset_frame_context"]);
    ctx.UInt8Value(value["refresh_frame_flags"]);
    ctx.UInt8Value(value["ref_frame_sign_bias_mask"]);
    ctx.EnumValue(value["interpolation_filter"], EnumFromString_StdVideoVP9InterpolationFilter);
    ctx.UInt8Value(value["base_q_idx"]);
    ctx.Int8Value(value["delta_q_y_dc"]);
    ctx.Int8Value(value["delta_q_uv_dc"]);
    ctx.Int8Value(value["delta_q_uv_ac"]);
    ctx.UInt8Value(value["tile_cols_log2"]);
    ctx.UInt8Value(value["tile_rows_log2"]);
    ctx.UInt16Array(value["reserved1"], 3);
    StructPtrFromApiDump<StdVideoVP9ColorConfig>(ctx, value["pColorConfig"]);
    StructPtrFromApiDump<StdVideoVP9LoopFilter>(ctx, value["pLoopFilter"]);
    StructPtrFromApiDump<StdVideoVP9Segmentation>(ctx, value["pSegmentation"]);
}

template <> void StructFromApiDump<StdVideoAV1ColorConfigFlags>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.UInt32Value(value["mono_chrome"]);
    ctx.UInt32Value(value["color_range"]);
    ctx.UInt32Value(value["separate_uv_delta_q"]);
    ctx.UInt32Value(value["color_description_present_flag"]);
    ctx.UInt32Value(value["reserved"]);
}

template <> void StructFromApiDump<StdVideoAV1ColorConfig>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    StructFromApiDump<StdVideoAV1ColorConfigFlags>(ctx, value["flags"]);
    ctx.UInt8Value(value["BitDepth"]);
    ctx.UInt8Value(value["subsampling_x"]);
    ctx.UInt8Value(value["subsampling_y"]);
    ctx.UInt8Value(value["reserved1"]);
    ctx.EnumValue(value["color_primaries"], EnumFromString_StdVideoAV1ColorPrimaries);
    ctx.EnumValue(value["transfer_characteristics"], EnumFromString_StdVideoAV1TransferCharacteristics);
    ctx.EnumValue(value["matrix_coefficients"], EnumFromString_StdVideoAV1MatrixCoefficients);
    ctx.EnumValue(value["chroma_sample_position"], EnumFromString_StdVideoAV1ChromaSamplePosition);
}

template <> void StructFromApiDump<StdVideoAV1TimingInfoFlags>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.UInt32Value(value["equal_picture_interval"]);
    ctx.UInt32Value(value["reserved"]);
}

template <> void StructFromApiDump<StdVideoAV1TimingInfo>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    StructFromApiDump<StdVideoAV1TimingInfoFlags>(ctx, value["flags"]);
    ctx.UInt32Value(value["num_units_in_display_tick"]);
    ctx.UInt32Value(value["time_scale"]);
    ctx.UInt32Value(value["num_ticks_per_picture_minus_1"]);
}

template <> void StructFromApiDump<StdVideoAV1SequenceHeaderFlags>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.UInt32Value(value["still_picture"]);
    ctx.UInt32Value(value["reduced_still_picture_header"]);
    ctx.UInt32Value(value["use_128x128_superblock"]);
    ctx.UInt32Value(value["enable_filter_intra"]);
    ctx.UInt32Value(value["enable_intra_edge_filter"]);
    ctx.UInt32Value(value["enable_interintra_compound"]);
    ctx.UInt32Value(value["enable_masked_compound"]);
    ctx.UInt32Value(value["enable_warped_motion"]);
    ctx.UInt32Value(value["enable_dual_filter"]);
    ctx.UInt32Value(value["enable_order_hint"]);
    ctx.UInt32Value(value["enable_jnt_comp"]);
    ctx.UInt32Value(value["enable_ref_frame_mvs"]);
    ctx.UInt32Value(value["frame_id_numbers_present_flag"]);
    ctx.UInt32Value(value["enable_superres"]);
    ctx.UInt32Value(value["enable_cdef"]);
    ctx.UInt32Value(value["enable_restoration"]);
    ctx.UInt32Value(value["film_grain_params_present"]);
    ctx.UInt32Value(value["timing_info_present_flag"]);
    ctx.UInt32Value(value["initial_display_delay_present_flag"]);
    ctx.UInt32Value(value["reserved"]);
}

template <> void StructFromApiDump<StdVideoAV1SequenceHeader>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    StructFromApiDump<StdVideoAV1SequenceHeaderFlags>(ctx, value["flags"]);
    ctx.EnumValue(value["seq_profile"], EnumFromString_StdVideoAV1Profile);
    ctx.UInt8Value(value["frame_width_bits_minus_1"]);
    ctx.UInt8Value(value["frame_height_bits_minus_1"]);
    ctx.UInt16Value(value["max_frame_width_minus_1"]);
    ctx.UInt16Value(value["max_frame_height_minus_1"]);
    ctx.UInt8Value(value["delta_frame_id_length_minus_2"]);
    ctx.UInt8Value(value["additional_frame_id_length_minus_1"]);
    ctx.UInt8Value(value["order_hint_bits_minus_1"]);
    ctx.UInt8Value(value["seq_force_integer_mv"]);
    ctx.UInt8Value(value["seq_force_screen_content_tools"]);
    ctx.UInt8Array(value["reserved1"], 5);
    StructPtrFromApiDump<StdVideoAV1ColorConfig>(ctx, value["pColorConfig"]);
    StructPtrFromApiDump<StdVideoAV1TimingInfo>(ctx, value["pTimingInfo"]);
}

template <> void StructFromApiDump<StdVideoAV1LoopFilterFlags>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.UInt32Value(value["loop_filter_delta_enabled"]);
    ctx.UInt32Value(value["loop_filter_delta_update"]);
    ctx.UInt32Value(value["reserved"]);
}

template <> void StructFromApiDump<StdVideoAV1LoopFilter>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    StructFromApiDump<StdVideoAV1LoopFilterFlags>(ctx, value["flags"]);
    ctx.UInt8Array(value["loop_filter_level"]);
    ctx.UInt8Value(value["loop_filter_sharpness"]);
    ctx.UInt8Value(value["update_ref_delta"]);
    ctx.Int8Array(value["loop_filter_ref_deltas"]);
    ctx.UInt8Value(value["update_mode_delta"]);
    ctx.Int8Array(value["loop_filter_mode_deltas"]);
}

template <> void StructFromApiDump<StdVideoAV1QuantizationFlags>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.UInt32Value(value["using_qmatrix"]);
    ctx.UInt32Value(value["diff_uv_delta"]);
    ctx.UInt32Value(value["reserved"]);
}

template <> void StructFromApiDump<StdVideoAV1Quantization>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    StructFromApiDump<StdVideoAV1QuantizationFlags>(ctx, value["flags"]);
    ctx.UInt8Value(value["base_q_idx"]);
    ctx.Int8Value(value["DeltaQYDc"]);
    ctx.Int8Value(value["DeltaQUDc"]);
    ctx.Int8Value(value["DeltaQUAc"]);
    ctx.Int8Value(value["DeltaQVDc"]);
    ctx.Int8Value(value["DeltaQVAc"]);
    ctx.UInt8Value(value["qm_y"]);
    ctx.UInt8Value(value["qm_u"]);
    ctx.UInt8Value(value["qm_v"]);
}

template <> void StructFromApiDump<StdVideoAV1Segmentation>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.UInt8Array(value["FeatureEnabled"]);
    ctx.Int16Array(value["FeatureData"]);
}

template <> void StructFromApiDump<StdVideoAV1TileInfoFlags>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.UInt32Value(value["uniform_tile_spacing_flag"]);
    ctx.UInt32Value(value["reserved"]);
}

template <> void StructFromApiDump<StdVideoAV1TileInfo>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    StructFromApiDump<StdVideoAV1TileInfoFlags>(ctx, value["flags"]);
    ctx.UInt8Value(value["TileCols"]);
    ctx.UInt8Value(value["TileRows"]);
    ctx.UInt16Value(value["context_update_tile_id"]);
    ctx.UInt8Value(value["tile_size_bytes_minus_1"]);
    ctx.UInt8Array(value["reserved1"], 7);
    ctx.UInt16Array(value["pMiColStarts"], ctx.Length(value["TileCols"]));
    ctx.UInt16Array(value["pMiRowStarts"], ctx.Length(value["TileRows"]));
    ctx.UInt16Array(value["pWidthInSbsMinus1"], ctx.Length(value["TileCols"]));
    ctx.UInt16Array(value["pHeightInSbsMinus1"], ctx.Length(value["TileRows"]));
}

template <> void StructFromApiDump<StdVideoAV1CDEF>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.UInt8Value(value["cdef_damping_minus_3"]);
    ctx.UInt8Value(value["cdef_bits"]);
    ctx.UInt8Array(value["cdef_y_pri_strength"]);
    ctx.UInt8Array(value["cdef_y_sec_strength"]);
    ctx.UInt8Array(value["cdef_uv_pri_strength"]);
    ctx.UInt8Array(value["cdef_uv_sec_strength"]);
}

template <> void StructFromApiDump<StdVideoAV1LoopRestoration>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumArray(value["FrameRestorationType"], EnumFromString_StdVideoAV1FrameRestorationType);
    ctx.UInt16Array(value["LoopRestorationSize"]);
}

template <> void StructFromApiDump<StdVideoAV1GlobalMotion>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.UInt8Array(value["GmType"]);
    ctx.Int32Array(value["gm_params"]);
}

template <> void StructFromApiDump<StdVideoAV1FilmGrainFlags>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.UInt32Value(value["chroma_scaling_from_luma"]);
    ctx.UInt32Value(value["overlap_flag"]);
    ctx.UInt32Value(value["clip_to_restricted_range"]);
    ctx.UInt32Value(value["update_grain"]);
    ctx.UInt32Value(value["reserved"]);
}

template <> void StructFromApiDump<StdVideoAV1FilmGrain>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    StructFromApiDump<StdVideoAV1FilmGrainFlags>(ctx, value["flags"]);
    ctx.UInt8Value(value["grain_scaling_minus_8"]);
    ctx.UInt8Value(value["ar_coeff_lag"]);
    ctx.UInt8Value(value["ar_coeff_shift_minus_6"]);
    ctx.UInt8Value(value["grain_scale_shift"]);
    ctx.UInt16Value(value["grain_seed"]);
    ctx.UInt8Value(value["film_grain_params_ref_idx"]);
    ctx.UInt8Value(value["num_y_points"]);
    ctx.UInt8Array(value["point_y_value"]);
    ctx.UInt8Array(value["point_y_scaling"]);
    ctx.UInt8Value(value["num_cb_points"]);
    ctx.UInt8Array(value["point_cb_value"]);
    ctx.UInt8Array(value["point_cb_scaling"]);
    ctx.UInt8Value(value["num_cr_points"]);
    ctx.UInt8Array(value["point_cr_value"]);
    ctx.UInt8Array(value["point_cr_scaling"]);
    ctx.Int8Array(value["ar_coeffs_y_plus_128"]);
    ctx.Int8Array(value["ar_coeffs_cb_plus_128"]);
    ctx.Int8Array(value["ar_coeffs_cr_plus_128"]);
    ctx.UInt8Value(value["cb_mult"]);
    ctx.UInt8Value(value["cb_luma_mult"]);
    ctx.UInt16Value(value["cb_offset"]);
    ctx.UInt8Value(value["cr_mult"]);
    ctx.UInt8Value(value["cr_luma_mult"]);
    ctx.UInt16Value(value["cr_offset"]);
}

template <> void StructFromApiDump<StdVideoDecodeAV1PictureInfoFlags>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.UInt32Value(value["error_resilient_mode"]);
    ctx.UInt32Value(value["disable_cdf_update"]);
    ctx.UInt32Value(value["use_superres"]);
    ctx.UInt32Value(value["render_and_frame_size_different"]);
    ctx.UInt32Value(value["allow_screen_content_tools"]);
    ctx.UInt32Value(value["is_filter_switchable"]);
    ctx.UInt32Value(value["force_integer_mv"]);
    ctx.UInt32Value(value["frame_size_override_flag"]);
    ctx.UInt32Value(value["buffer_removal_time_present_flag"]);
    ctx.UInt32Value(value["allow_intrabc"]);
    ctx.UInt32Value(value["frame_refs_short_signaling"]);
    ctx.UInt32Value(value["allow_high_precision_mv"]);
    ctx.UInt32Value(value["is_motion_mode_switchable"]);
    ctx.UInt32Value(value["use_ref_frame_mvs"]);
    ctx.UInt32Value(value["disable_frame_end_update_cdf"]);
    ctx.UInt32Value(value["allow_warped_motion"]);
    ctx.UInt32Value(value["reduced_tx_set"]);
    ctx.UInt32Value(value["reference_select"]);
    ctx.UInt32Value(value["skip_mode_present"]);
    ctx.UInt32Value(value["delta_q_present"]);
    ctx.UInt32Value(value["delta_lf_present"]);
    ctx.UInt32Value(value["delta_lf_multi"]);
    ctx.UInt32Value(value["segmentation_enabled"]);
    ctx.UInt32Value(value["segmentation_update_map"]);
    ctx.UInt32Value(value["segmentation_temporal_update"]);
    ctx.UInt32Value(value["segmentation_update_data"]);
    ctx.UInt32Value(value["UsesLr"]);
    ctx.UInt32Value(value["usesChromaLr"]);
    ctx.UInt32Value(value["apply_grain"]);
    ctx.UInt32Value(value["reserved"]);
}

template <> void StructFromApiDump<StdVideoDecodeAV1PictureInfo>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    StructFromApiDump<StdVideoDecodeAV1PictureInfoFlags>(ctx, value["flags"]);
    ctx.EnumValue(value["frame_type"], EnumFromString_StdVideoAV1FrameType);
    ctx.UInt32Value(value["current_frame_id"]);
    ctx.UInt8Value(value["OrderHint"]);
    ctx.UInt8Value(value["primary_ref_frame"]);
    ctx.UInt8Value(value["refresh_frame_flags"]);
    ctx.UInt8Value(value["reserved1"]);
    ctx.EnumValue(value["interpolation_filter"], EnumFromString_StdVideoAV1InterpolationFilter);
    ctx.EnumValue(value["TxMode"], EnumFromString_StdVideoAV1TxMode);
    ctx.UInt8Value(value["delta_q_res"]);
    ctx.UInt8Value(value["delta_lf_res"]);
    ctx.UInt8Array(value["SkipModeFrame"]);
    ctx.UInt8Value(value["coded_denom"]);
    ctx.UInt8Array(value["reserved2"], 3);
    ctx.UInt8Array(value["OrderHints"]);
    ctx.UInt32Array(value["expectedFrameId"]);
    StructPtrFromApiDump<StdVideoAV1TileInfo>(ctx, value["pTileInfo"]);
    StructPtrFromApiDump<StdVideoAV1Quantization>(ctx, value["pQuantization"]);
    StructPtrFromApiDump<StdVideoAV1Segmentation>(ctx, value["pSegmentation"]);
    StructPtrFromApiDump<StdVideoAV1LoopFilter>(ctx, value["pLoopFilter"]);
    StructPtrFromApiDump<StdVideoAV1CDEF>(ctx, value["pCDEF"]);
    StructPtrFromApiDump<StdVideoAV1LoopRestoration>(ctx, value["pLoopRestoration"]);
    StructPtrFromApiDump<StdVideoAV1GlobalMotion>(ctx, value["pGlobalMotion"]);
    StructPtrFromApiDump<StdVideoAV1FilmGrain>(ctx, value["pFilmGrain"]);
}

template <> void StructFromApiDump<StdVideoDecodeAV1ReferenceInfoFlags>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.UInt32Value(value["disable_frame_end_update_cdf"]);
    ctx.UInt32Value(value["segmentation_enabled"]);
    ctx.UInt32Value(value["reserved"]);
}

template <> void StructFromApiDump<StdVideoDecodeAV1ReferenceInfo>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    StructFromApiDump<StdVideoDecodeAV1ReferenceInfoFlags>(ctx, value["flags"]);
    ctx.UInt8Value(value["frame_type"]);
    ctx.UInt8Value(value["RefFrameSignBias"]);
    ctx.UInt8Value(value["OrderHint"]);
    ctx.UInt8Array(value["SavedOrderHints"]);
}

template <> void StructFromApiDump<StdVideoEncodeAV1ExtensionHeader>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.UInt8Value(value["temporal_id"]);
    ctx.UInt8Value(value["spatial_id"]);
}

template <> void StructFromApiDump<StdVideoEncodeAV1DecoderModelInfo>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.UInt8Value(value["buffer_delay_length_minus_1"]);
    ctx.UInt8Value(value["buffer_removal_time_length_minus_1"]);
    ctx.UInt8Value(value["frame_presentation_time_length_minus_1"]);
    ctx.UInt8Value(value["reserved1"]);
    ctx.UInt32Value(value["num_units_in_decoding_tick"]);
}

template <> void StructFromApiDump<StdVideoEncodeAV1OperatingPointInfoFlags>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.UInt32Value(value["decoder_model_present_for_this_op"]);
    ctx.UInt32Value(value["low_delay_mode_flag"]);
    ctx.UInt32Value(value["initial_display_delay_present_for_this_op"]);
    ctx.UInt32Value(value["reserved"]);
}

template <> void StructFromApiDump<StdVideoEncodeAV1OperatingPointInfo>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    StructFromApiDump<StdVideoEncodeAV1OperatingPointInfoFlags>(ctx, value["flags"]);
    ctx.UInt16Value(value["operating_point_idc"]);
    ctx.UInt8Value(value["seq_level_idx"]);
    ctx.UInt8Value(value["seq_tier"]);
    ctx.UInt32Value(value["decoder_buffer_delay"]);
    ctx.UInt32Value(value["encoder_buffer_delay"]);
    ctx.UInt8Value(value["initial_display_delay_minus_1"]);
}

template <> void StructFromApiDump<StdVideoEncodeAV1PictureInfoFlags>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.UInt32Value(value["error_resilient_mode"]);
    ctx.UInt32Value(value["disable_cdf_update"]);
    ctx.UInt32Value(value["use_superres"]);
    ctx.UInt32Value(value["render_and_frame_size_different"]);
    ctx.UInt32Value(value["allow_screen_content_tools"]);
    ctx.UInt32Value(value["is_filter_switchable"]);
    ctx.UInt32Value(value["force_integer_mv"]);
    ctx.UInt32Value(value["frame_size_override_flag"]);
    ctx.UInt32Value(value["buffer_removal_time_present_flag"]);
    ctx.UInt32Value(value["allow_intrabc"]);
    ctx.UInt32Value(value["frame_refs_short_signaling"]);
    ctx.UInt32Value(value["allow_high_precision_mv"]);
    ctx.UInt32Value(value["is_motion_mode_switchable"]);
    ctx.UInt32Value(value["use_ref_frame_mvs"]);
    ctx.UInt32Value(value["disable_frame_end_update_cdf"]);
    ctx.UInt32Value(value["allow_warped_motion"]);
    ctx.UInt32Value(value["reduced_tx_set"]);
    ctx.UInt32Value(value["skip_mode_present"]);
    ctx.UInt32Value(value["delta_q_present"]);
    ctx.UInt32Value(value["delta_lf_present"]);
    ctx.UInt32Value(value["delta_lf_multi"]);
    ctx.UInt32Value(value["segmentation_enabled"]);
    ctx.UInt32Value(value["segmentation_update_map"]);
    ctx.UInt32Value(value["segmentation_temporal_update"]);
    ctx.UInt32Value(value["segmentation_update_data"]);
    ctx.UInt32Value(value["UsesLr"]);
    ctx.UInt32Value(value["usesChromaLr"]);
    ctx.UInt32Value(value["show_frame"]);
    ctx.UInt32Value(value["showable_frame"]);
    ctx.UInt32Value(value["reserved"]);
}

template <> void StructFromApiDump<StdVideoEncodeAV1PictureInfo>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    StructFromApiDump<StdVideoEncodeAV1PictureInfoFlags>(ctx, value["flags"]);
    ctx.EnumValue(value["frame_type"], EnumFromString_StdVideoAV1FrameType);
    ctx.UInt32Value(value["frame_presentation_time"]);
    ctx.UInt32Value(value["current_frame_id"]);
    ctx.UInt8Value(value["order_hint"]);
    ctx.UInt8Value(value["primary_ref_frame"]);
    ctx.UInt8Value(value["refresh_frame_flags"]);
    ctx.UInt8Value(value["coded_denom"]);
    ctx.UInt16Value(value["render_width_minus_1"]);
    ctx.UInt16Value(value["render_height_minus_1"]);
    ctx.EnumValue(value["interpolation_filter"], EnumFromString_StdVideoAV1InterpolationFilter);
    ctx.EnumValue(value["TxMode"], EnumFromString_StdVideoAV1TxMode);
    ctx.UInt8Value(value["delta_q_res"]);
    ctx.UInt8Value(value["delta_lf_res"]);
    ctx.UInt8Array(value["ref_order_hint"]);
    ctx.Int8Array(value["ref_frame_idx"]);
    ctx.UInt8Array(value["reserved1"], 3);
    ctx.UInt32Array(value["delta_frame_id_minus_1"]);
    StructPtrFromApiDump<StdVideoAV1TileInfo>(ctx, value["pTileInfo"]);
    StructPtrFromApiDump<StdVideoAV1Quantization>(ctx, value["pQuantization"]);
    StructPtrFromApiDump<StdVideoAV1Segmentation>(ctx, value["pSegmentation"]);
    StructPtrFromApiDump<StdVideoAV1LoopFilter>(ctx, value["pLoopFilter"]);
    StructPtrFromApiDump<StdVideoAV1CDEF>(ctx, value["pCDEF"]);
    StructPtrFromApiDump<StdVideoAV1LoopRestoration>(ctx, value["pLoopRestoration"]);
    StructPtrFromApiDump<StdVideoAV1GlobalMotion>(ctx, value["pGlobalMotion"]);
    StructPtrFromApiDump<StdVideoEncodeAV1ExtensionHeader>(ctx, value["pExtensionHeader"]);
    ctx.UInt32Ptr(value["pBufferRemovalTimes"]);
}

template <> void StructFromApiDump<StdVideoEncodeAV1ReferenceInfoFlags>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.UInt32Value(value["disable_frame_end_update_cdf"]);
    ctx.UInt32Value(value["segmentation_enabled"]);
    ctx.UInt32Value(value["reserved"]);
}

template <> void StructFromApiDump<StdVideoEncodeAV1ReferenceInfo>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    StructFromApiDump<StdVideoEncodeAV1ReferenceInfoFlags>(ctx, value["flags"]);
    ctx.UInt32Value(value["RefFrameId"]);
    ctx.EnumValue(value["frame_type"], EnumFromString_StdVideoAV1FrameType);
    ctx.UInt8Value(value["OrderHint"]);
    ctx.UInt8Array(value["reserved1"], 3);
    StructPtrFromApiDump<StdVideoEncodeAV1ExtensionHeader>(ctx, value["pExtensionHeader"]);
}

template <> void StructFromApiDump<VkExtent2D>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.UInt32Value(value["width"]);
    ctx.UInt32Value(value["height"]);
}

template <> void StructFromApiDump<VkExtent3D>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.UInt32Value(value["width"]);
    ctx.UInt32Value(value["height"]);
    ctx.UInt32Value(value["depth"]);
}

template <> void StructFromApiDump<VkOffset2D>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.Int32Value(value["x"]);
    ctx.Int32Value(value["y"]);
}

template <> void StructFromApiDump<VkOffset3D>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.Int32Value(value["x"]);
    ctx.Int32Value(value["y"]);
    ctx.Int32Value(value["z"]);
}

template <> void StructFromApiDump<VkRect2D>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    StructFromApiDump<VkOffset2D>(ctx, value["offset"]);
    StructFromApiDump<VkExtent2D>(ctx, value["extent"]);
}

template <> void StructFromApiDump<VkAllocationCallbacks>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.VoidPtrValue(value["pUserData"]);
    ctx.FunctionPtrValue(value["pfnAllocation"]);
    ctx.FunctionPtrValue(value["pfnReallocation"]);
    ctx.FunctionPtrValue(value["pfnFree"]);
    ctx.FunctionPtrValue(value["pfnInternalAllocation"]);
    ctx.FunctionPtrValue(value["pfnInternalFree"]);
}

template <> void StructFromApiDump<VkApplicationInfo>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.StringValue(value["pApplicationName"]);
    ctx.UInt32Value(value["applicationVersion"]);
    ctx.StringValue(value["pEngineName"]);
    ctx.UInt32Value(value["engineVersion"]);
    ctx.UInt32Value(value["apiVersion"]);
}

template <> void StructFromApiDump<VkFormatProperties>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.FlagsValue(value["linearTilingFeatures"], EnumFromString_VkFormatFeatureFlagBits);
    ctx.FlagsValue(value["optimalTilingFeatures"], EnumFromString_VkFormatFeatureFlagBits);
    ctx.FlagsValue(value["bufferFeatures"], EnumFromString_VkFormatFeatureFlagBits);
}

template <> void StructFromApiDump<VkImageFormatProperties>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    StructFromApiDump<VkExtent3D>(ctx, value["maxExtent"]);
    ctx.UInt32Value(value["maxMipLevels"]);
    ctx.UInt32Value(value["maxArrayLayers"]);
    ctx.FlagsValue(value["sampleCounts"], EnumFromString_VkSampleCountFlagBits);
    ctx.UInt64Value(value["maxResourceSize"]);
}

template <> void StructFromApiDump<VkInstanceCreateInfo>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.FlagsValue(value["flags"], EnumFromString_VkInstanceCreateFlagBits);
    StructPtrFromApiDump<VkApplicationInfo>(ctx, value["pApplicationInfo"]);
    ctx.UInt32Value(value["enabledLayerCount"]);
    ctx.StringArray(value["ppEnabledLayerNames"], ctx.Length(value["enabledLayerCount"]));
    ctx.UInt32Value(value["enabledExtensionCount"]);
    ctx.StringArray(value["ppEnabledExtensionNames"], ctx.Length(value["enabledExtensionCount"]));
}

template <> void StructFromApiDump<VkMemoryHeap>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.UInt64Value(value["size"]);
    ctx.FlagsValue(value["flags"], EnumFromString_VkMemoryHeapFlagBits);
}

template <> void StructFromApiDump<VkMemoryType>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.FlagsValue(value["propertyFlags"], EnumFromString_VkMemoryPropertyFlagBits);
    ctx.UInt32Value(value["heapIndex"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceFeatures>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.UInt32Value(value["robustBufferAccess"]);
    ctx.UInt32Value(value["fullDrawIndexUint32"]);
    ctx.UInt32Value(value["imageCubeArray"]);
    ctx.UInt32Value(value["independentBlend"]);
    ctx.UInt32Value(value["geometryShader"]);
    ctx.UInt32Value(value["tessellationShader"]);
    ctx.UInt32Value(value["sampleRateShading"]);
    ctx.UInt32Value(value["dualSrcBlend"]);
    ctx.UInt32Value(value["logicOp"]);
    ctx.UInt32Value(value["multiDrawIndirect"]);
    ctx.UInt32Value(value["drawIndirectFirstInstance"]);
    ctx.UInt32Value(value["depthClamp"]);
    ctx.UInt32Value(value["depthBiasClamp"]);
    ctx.UInt32Value(value["fillModeNonSolid"]);
    ctx.UInt32Value(value["depthBounds"]);
    ctx.UInt32Value(value["wideLines"]);
    ctx.UInt32Value(value["largePoints"]);
    ctx.UInt32Value(value["alphaToOne"]);
    ctx.UInt32Value(value["multiViewport"]);
    ctx.UInt32Value(value["samplerAnisotropy"]);
    ctx.UInt32Value(value["textureCompressionETC2"]);
    ctx.UInt32Value(value["textureCompressionASTC_LDR"]);
    ctx.UInt32Value(value["textureCompressionBC"]);
    ctx.UInt32Value(value["occlusionQueryPrecise"]);
    ctx.UInt32Value(value["pipelineStatisticsQuery"]);
    ctx.UInt32Value(value["vertexPipelineStoresAndAtomics"]);
    ctx.UInt32Value(value["fragmentStoresAndAtomics"]);
    ctx.UInt32Value(value["shaderTessellationAndGeometryPointSize"]);
    ctx.UInt32Value(value["shaderImageGatherExtended"]);
    ctx.UInt32Value(value["shaderStorageImageExtendedFormats"]);
    ctx.UInt32Value(value["shaderStorageImageMultisample"]);
    ctx.UInt32Value(value["shaderStorageImageReadWithoutFormat"]);
    ctx.UInt32Value(value["shaderStorageImageWriteWithoutFormat"]);
    ctx.UInt32Value(value["shaderUniformBufferArrayDynamicIndexing"]);
    ctx.UInt32Value(value["shaderSampledImageArrayDynamicIndexing"]);
    ctx.UInt32Value(value["shaderStorageBufferArrayDynamicIndexing"]);
    ctx.UInt32Value(value["shaderStorageImageArrayDynamicIndexing"]);
    ctx.UInt32Value(value["shaderClipDistance"]);
    ctx.UInt32Value(value["shaderCullDistance"]);
    ctx.UInt32Value(value["shaderFloat64"]);
    ctx.UInt32Value(value["shaderInt64"]);
    ctx.UInt32Value(value["shaderInt16"]);
    ctx.UInt32Value(value["shaderResourceResidency"]);
    ctx.UInt32Value(value["shaderResourceMinLod"]);
    ctx.UInt32Value(value["sparseBinding"]);
    ctx.UInt32Value(value["sparseResidencyBuffer"]);
    ctx.UInt32Value(value["sparseResidencyImage2D"]);
    ctx.UInt32Value(value["sparseResidencyImage3D"]);
    ctx.UInt32Value(value["sparseResidency2Samples"]);
    ctx.UInt32Value(value["sparseResidency4Samples"]);
    ctx.UInt32Value(value["sparseResidency8Samples"]);
    ctx.UInt32Value(value["sparseResidency16Samples"]);
    ctx.UInt32Value(value["sparseResidencyAliased"]);
    ctx.UInt32Value(value["variableMultisampleRate"]);
    ctx.UInt32Value(value["inheritedQueries"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceLimits>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.UInt32Value(value["maxImageDimension1D"]);
    ctx.UInt32Value(value["maxImageDimension2D"]);
    ctx.UInt32Value(value["maxImageDimension3D"]);
    ctx.UInt32Value(value["maxImageDimensionCube"]);
    ctx.UInt32Value(value["maxImageArrayLayers"]);
    ctx.UInt32Value(value["maxTexelBufferElements"]);
    ctx.UInt32Value(value["maxUniformBufferRange"]);
    ctx.UInt32Value(value["maxStorageBufferRange"]);
    ctx.UInt32Value(value["maxPushConstantsSize"]);
    ctx.UInt32Value(value["maxMemoryAllocationCount"]);
    ctx.UInt32Value(value["maxSamplerAllocationCount"]);
    ctx.UInt64Value(value["bufferImageGranularity"]);
    ctx.UInt64Value(value["sparseAddressSpaceSize"]);
    ctx.UInt32Value(value["maxBoundDescriptorSets"]);
    ctx.UInt32Value(value["maxPerStageDescriptorSamplers"]);
    ctx.UInt32Value(value["maxPerStageDescriptorUniformBuffers"]);
    ctx.UInt32Value(value["maxPerStageDescriptorStorageBuffers"]);
    ctx.UInt32Value(value["maxPerStageDescriptorSampledImages"]);
    ctx.UInt32Value(value["maxPerStageDescriptorStorageImages"]);
    ctx.UInt32Value(value["maxPerStageDescriptorInputAttachments"]);
    ctx.UInt32Value(value["maxPerStageResources"]);
    ctx.UInt32Value(value["maxDescriptorSetSamplers"]);
    ctx.UInt32Value(value["maxDescriptorSetUniformBuffers"]);
    ctx.UInt32Value(value["maxDescriptorSetUniformBuffersDynamic"]);
    ctx.UInt32Value(value["maxDescriptorSetStorageBuffers"]);
    ctx.UInt32Value(value["maxDescriptorSetStorageBuffersDynamic"]);
    ctx.UInt32Value(value["maxDescriptorSetSampledImages"]);
    ctx.UInt32Value(value["maxDescriptorSetStorageImages"]);
    ctx.UInt32Value(value["maxDescriptorSetInputAttachments"]);
    ctx.UInt32Value(value["maxVertexInputAttributes"]);
    ctx.UInt32Value(value["maxVertexInputBindings"]);
    ctx.UInt32Value(value["maxVertexInputAttributeOffset"]);
    ctx.UInt32Value(value["maxVertexInputBindingStride"]);
    ctx.UInt32Value(value["maxVertexOutputComponents"]);
    ctx.UInt32Value(value["maxTessellationGenerationLevel"]);
    ctx.UInt32Value(value["maxTessellationPatchSize"]);
    ctx.UInt32Value(value["maxTessellationControlPerVertexInputComponents"]);
    ctx.UInt32Value(value["maxTessellationControlPerVertexOutputComponents"]);
    ctx.UInt32Value(value["maxTessellationControlPerPatchOutputComponents"]);
    ctx.UInt32Value(value["maxTessellationControlTotalOutputComponents"]);
    ctx.UInt32Value(value["maxTessellationEvaluationInputComponents"]);
    ctx.UInt32Value(value["maxTessellationEvaluationOutputComponents"]);
    ctx.UInt32Value(value["maxGeometryShaderInvocations"]);
    ctx.UInt32Value(value["maxGeometryInputComponents"]);
    ctx.UInt32Value(value["maxGeometryOutputComponents"]);
    ctx.UInt32Value(value["maxGeometryOutputVertices"]);
    ctx.UInt32Value(value["maxGeometryTotalOutputComponents"]);
    ctx.UInt32Value(value["maxFragmentInputComponents"]);
    ctx.UInt32Value(value["maxFragmentOutputAttachments"]);
    ctx.UInt32Value(value["maxFragmentDualSrcAttachments"]);
    ctx.UInt32Value(value["maxFragmentCombinedOutputResources"]);
    ctx.UInt32Value(value["maxComputeSharedMemorySize"]);
    ctx.UInt32Array(value["maxComputeWorkGroupCount"], 3);
    ctx.UInt32Value(value["maxComputeWorkGroupInvocations"]);
    ctx.UInt32Array(value["maxComputeWorkGroupSize"], 3);
    ctx.UInt32Value(value["subPixelPrecisionBits"]);
    ctx.UInt32Value(value["subTexelPrecisionBits"]);
    ctx.UInt32Value(value["mipmapPrecisionBits"]);
    ctx.UInt32Value(value["maxDrawIndexedIndexValue"]);
    ctx.UInt32Value(value["maxDrawIndirectCount"]);
    ctx.FloatValue(value["maxSamplerLodBias"]);
    ctx.FloatValue(value["maxSamplerAnisotropy"]);
    ctx.UInt32Value(value["maxViewports"]);
    ctx.UInt32Array(value["maxViewportDimensions"], 2);
    ctx.FloatArray(value["viewportBoundsRange"], 2);
    ctx.UInt32Value(value["viewportSubPixelBits"]);
    ctx.SizeTValue(value["minMemoryMapAlignment"]);
    ctx.UInt64Value(value["minTexelBufferOffsetAlignment"]);
    ctx.UInt64Value(value["minUniformBufferOffsetAlignment"]);
    ctx.UInt64Value(value["minStorageBufferOffsetAlignment"]);
    ctx.Int32Value(value["minTexelOffset"]);
    ctx.UInt32Value(value["maxTexelOffset"]);
    ctx.Int32Value(value["minTexelGatherOffset"]);
    ctx.UInt32Value(value["maxTexelGatherOffset"]);
    ctx.FloatValue(value["minInterpolationOffset"]);
    ctx.FloatValue(value["maxInterpolationOffset"]);
    ctx.UInt32Value(value["subPixelInterpolationOffsetBits"]);
    ctx.UInt32Value(value["maxFramebufferWidth"]);
    ctx.UInt32Value(value["maxFramebufferHeight"]);
    ctx.UInt32Value(value["maxFramebufferLayers"]);
    ctx.FlagsValue(value["framebufferColorSampleCounts"], EnumFromString_VkSampleCountFlagBits);
    ctx.FlagsValue(value["framebufferDepthSampleCounts"], EnumFromString_VkSampleCountFlagBits);
    ctx.FlagsValue(value["framebufferStencilSampleCounts"], EnumFromString_VkSampleCountFlagBits);
    ctx.FlagsValue(value["framebufferNoAttachmentsSampleCounts"], EnumFromString_VkSampleCountFlagBits);
    ctx.UInt32Value(value["maxColorAttachments"]);
    ctx.FlagsValue(value["sampledImageColorSampleCounts"], EnumFromString_VkSampleCountFlagBits);
    ctx.FlagsValue(value["sampledImageIntegerSampleCounts"], EnumFromString_VkSampleCountFlagBits);
    ctx.FlagsValue(value["sampledImageDepthSampleCounts"], EnumFromString_VkSampleCountFlagBits);
    ctx.FlagsValue(value["sampledImageStencilSampleCounts"], EnumFromString_VkSampleCountFlagBits);
    ctx.FlagsValue(value["storageImageSampleCounts"], EnumFromString_VkSampleCountFlagBits);
    ctx.UInt32Value(value["maxSampleMaskWords"]);
    ctx.UInt32Value(value["timestampComputeAndGraphics"]);
    ctx.FloatValue(value["timestampPeriod"]);
    ctx.UInt32Value(value["maxClipDistances"]);
    ctx.UInt32Value(value["maxCullDistances"]);
    ctx.UInt32Value(value["maxCombinedClipAndCullDistances"]);
    ctx.UInt32Value(value["discreteQueuePriorities"]);
    ctx.FloatArray(value["pointSizeRange"], 2);
    ctx.FloatArray(value["lineWidthRange"], 2);
    ctx.FloatValue(value["pointSizeGranularity"]);
    ctx.FloatValue(value["lineWidthGranularity"]);
    ctx.UInt32Value(value["strictLines"]);
    ctx.UInt32Value(value["standardSampleLocations"]);
    ctx.UInt64Value(value["optimalBufferCopyOffsetAlignment"]);
    ctx.UInt64Value(value["optimalBufferCopyRowPitchAlignment"]);
    ctx.UInt64Value(value["nonCoherentAtomSize"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceMemoryProperties>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.UInt32Value(value["memoryTypeCount"]);
    StructArrayFromApiDump<VkMemoryType>(ctx, value["memoryTypes"], ctx.Length(value["memoryTypeCount"]));
    ctx.UInt32Value(value["memoryHeapCount"]);
    StructArrayFromApiDump<VkMemoryHeap>(ctx, value["memoryHeaps"], ctx.Length(value["memoryHeapCount"]));
}

template <> void StructFromApiDump<VkPhysicalDeviceSparseProperties>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.UInt32Value(value["residencyStandard2DBlockShape"]);
    ctx.UInt32Value(value["residencyStandard2DMultisampleBlockShape"]);
    ctx.UInt32Value(value["residencyStandard3DBlockShape"]);
    ctx.UInt32Value(value["residencyAlignedMipSize"]);
    ctx.UInt32Value(value["residencyNonResidentStrict"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceProperties>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.UInt32Value(value["apiVersion"]);
    ctx.UInt32Value(value["driverVersion"]);
    ctx.UInt32Value(value["vendorID"]);
    ctx.UInt32Value(value["deviceID"]);
    ctx.EnumValue(value["deviceType"], EnumFromString_VkPhysicalDeviceType);
    ctx.StringValue(value["deviceName"]);
    ctx.UInt8Array(value["pipelineCacheUUID"]);
    StructFromApiDump<VkPhysicalDeviceLimits>(ctx, value["limits"]);
    StructFromApiDump<VkPhysicalDeviceSparseProperties>(ctx, value["sparseProperties"]);
}

template <> void StructFromApiDump<VkQueueFamilyProperties>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.FlagsValue(value["queueFlags"], EnumFromString_VkQueueFlagBits);
    ctx.UInt32Value(value["queueCount"]);
    ctx.UInt32Value(value["timestampValidBits"]);
    StructFromApiDump<VkExtent3D>(ctx, value["minImageTransferGranularity"]);
}

template <> void StructFromApiDump<VkDeviceQueueCreateInfo>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.FlagsValue(value["flags"], EnumFromString_VkDeviceQueueCreateFlagBits);
    ctx.UInt32Value(value["queueFamilyIndex"]);
    ctx.UInt32Value(value["queueCount"]);
    ctx.FloatArray(value["pQueuePriorities"], ctx.Length(value["queueCount"]));
}

template <> void StructFromApiDump<VkDeviceCreateInfo>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.FlagsValue(value["flags"]);
    ctx.UInt32Value(value["queueCreateInfoCount"]);
    StructArrayFromApiDump<VkDeviceQueueCreateInfo>(ctx, value["pQueueCreateInfos"], ctx.Length(value["queueCreateInfoCount"]));
    ctx.UInt32Value(value["enabledLayerCount"]);
    ctx.StringArray(value["ppEnabledLayerNames"], ctx.Length(value["enabledLayerCount"]));
    ctx.UInt32Value(value["enabledExtensionCount"]);
    ctx.StringArray(value["ppEnabledExtensionNames"], ctx.Length(value["enabledExtensionCount"]));
    StructPtrFromApiDump<VkPhysicalDeviceFeatures>(ctx, value["pEnabledFeatures"]);
}

template <> void StructFromApiDump<VkExtensionProperties>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.StringValue(value["extensionName"]);
    ctx.UInt32Value(value["specVersion"]);
}

template <> void StructFromApiDump<VkLayerProperties>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.StringValue(value["layerName"]);
    ctx.UInt32Value(value["specVersion"]);
    ctx.UInt32Value(value["implementationVersion"]);
    ctx.StringValue(value["description"]);
}

template <> void StructFromApiDump<VkSubmitInfo>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["waitSemaphoreCount"]);
    ctx.VulkanHandleArray(value["pWaitSemaphores"], VK_OBJECT_TYPE_SEMAPHORE, ctx.Length(value["waitSemaphoreCount"]));
    ctx.FlagsArray(value["pWaitDstStageMask"], EnumFromString_VkPipelineStageFlagBits, ctx.Length(value["waitSemaphoreCount"]));
    ctx.UInt32Value(value["commandBufferCount"]);
    ctx.VulkanHandleArray(value["pCommandBuffers"], VK_OBJECT_TYPE_COMMAND_BUFFER, ctx.Length(value["commandBufferCount"]));
    ctx.UInt32Value(value["signalSemaphoreCount"]);
    ctx.VulkanHandleArray(value["pSignalSemaphores"], VK_OBJECT_TYPE_SEMAPHORE, ctx.Length(value["signalSemaphoreCount"]));
}

template <> void StructFromApiDump<VkMappedMemoryRange>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.VulkanHandleValue(value["memory"], VK_OBJECT_TYPE_DEVICE_MEMORY);
    ctx.UInt64Value(value["offset"]);
    ctx.UInt64Value(value["size"]);
}

template <> void StructFromApiDump<VkMemoryAllocateInfo>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt64Value(value["allocationSize"]);
    ctx.UInt32Value(value["memoryTypeIndex"]);
}

template <> void StructFromApiDump<VkMemoryRequirements>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.UInt64Value(value["size"]);
    ctx.UInt64Value(value["alignment"]);
    ctx.UInt32Value(value["memoryTypeBits"]);
}

template <> void StructFromApiDump<VkImageSubresource>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.FlagsValue(value["aspectMask"], EnumFromString_VkImageAspectFlagBits);
    ctx.UInt32Value(value["mipLevel"]);
    ctx.UInt32Value(value["arrayLayer"]);
}

template <> void StructFromApiDump<VkSparseImageFormatProperties>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.FlagsValue(value["aspectMask"], EnumFromString_VkImageAspectFlagBits);
    StructFromApiDump<VkExtent3D>(ctx, value["imageGranularity"]);
    ctx.FlagsValue(value["flags"], EnumFromString_VkSparseImageFormatFlagBits);
}

template <> void StructFromApiDump<VkSparseImageMemoryBind>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    StructFromApiDump<VkImageSubresource>(ctx, value["subresource"]);
    StructFromApiDump<VkOffset3D>(ctx, value["offset"]);
    StructFromApiDump<VkExtent3D>(ctx, value["extent"]);
    ctx.VulkanHandleValue(value["memory"], VK_OBJECT_TYPE_DEVICE_MEMORY);
    ctx.UInt64Value(value["memoryOffset"]);
    ctx.FlagsValue(value["flags"], EnumFromString_VkSparseMemoryBindFlagBits);
}

template <> void StructFromApiDump<VkSparseImageMemoryBindInfo>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.VulkanHandleValue(value["image"], VK_OBJECT_TYPE_IMAGE);
    ctx.UInt32Value(value["bindCount"]);
    StructArrayFromApiDump<VkSparseImageMemoryBind>(ctx, value["pBinds"], ctx.Length(value["bindCount"]));
}

template <> void StructFromApiDump<VkSparseImageMemoryRequirements>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    StructFromApiDump<VkSparseImageFormatProperties>(ctx, value["formatProperties"]);
    ctx.UInt32Value(value["imageMipTailFirstLod"]);
    ctx.UInt64Value(value["imageMipTailSize"]);
    ctx.UInt64Value(value["imageMipTailOffset"]);
    ctx.UInt64Value(value["imageMipTailStride"]);
}

template <> void StructFromApiDump<VkSparseMemoryBind>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.UInt64Value(value["resourceOffset"]);
    ctx.UInt64Value(value["size"]);
    ctx.VulkanHandleValue(value["memory"], VK_OBJECT_TYPE_DEVICE_MEMORY);
    ctx.UInt64Value(value["memoryOffset"]);
    ctx.FlagsValue(value["flags"], EnumFromString_VkSparseMemoryBindFlagBits);
}

template <> void StructFromApiDump<VkSparseBufferMemoryBindInfo>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.VulkanHandleValue(value["buffer"], VK_OBJECT_TYPE_BUFFER);
    ctx.UInt32Value(value["bindCount"]);
    StructArrayFromApiDump<VkSparseMemoryBind>(ctx, value["pBinds"], ctx.Length(value["bindCount"]));
}

template <> void StructFromApiDump<VkSparseImageOpaqueMemoryBindInfo>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.VulkanHandleValue(value["image"], VK_OBJECT_TYPE_IMAGE);
    ctx.UInt32Value(value["bindCount"]);
    StructArrayFromApiDump<VkSparseMemoryBind>(ctx, value["pBinds"], ctx.Length(value["bindCount"]));
}

template <> void StructFromApiDump<VkBindSparseInfo>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["waitSemaphoreCount"]);
    ctx.VulkanHandleArray(value["pWaitSemaphores"], VK_OBJECT_TYPE_SEMAPHORE, ctx.Length(value["waitSemaphoreCount"]));
    ctx.UInt32Value(value["bufferBindCount"]);
    StructArrayFromApiDump<VkSparseBufferMemoryBindInfo>(ctx, value["pBufferBinds"], ctx.Length(value["bufferBindCount"]));
    ctx.UInt32Value(value["imageOpaqueBindCount"]);
    StructArrayFromApiDump<VkSparseImageOpaqueMemoryBindInfo>(ctx, value["pImageOpaqueBinds"], ctx.Length(value["imageOpaqueBindCount"]));
    ctx.UInt32Value(value["imageBindCount"]);
    StructArrayFromApiDump<VkSparseImageMemoryBindInfo>(ctx, value["pImageBinds"], ctx.Length(value["imageBindCount"]));
    ctx.UInt32Value(value["signalSemaphoreCount"]);
    ctx.VulkanHandleArray(value["pSignalSemaphores"], VK_OBJECT_TYPE_SEMAPHORE, ctx.Length(value["signalSemaphoreCount"]));
}

template <> void StructFromApiDump<VkFenceCreateInfo>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.FlagsValue(value["flags"], EnumFromString_VkFenceCreateFlagBits);
}

template <> void StructFromApiDump<VkSemaphoreCreateInfo>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.FlagsValue(value["flags"]);
}

template <> void StructFromApiDump<VkQueryPoolCreateInfo>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.FlagsValue(value["flags"], EnumFromString_VkQueryPoolCreateFlagBits);
    ctx.EnumValue(value["queryType"], EnumFromString_VkQueryType);
    ctx.UInt32Value(value["queryCount"]);
    ctx.FlagsValue(value["pipelineStatistics"], EnumFromString_VkQueryPipelineStatisticFlagBits);
}

template <> void StructFromApiDump<VkBufferCreateInfo>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.FlagsValue(value["flags"], EnumFromString_VkBufferCreateFlagBits);
    ctx.UInt64Value(value["size"]);
    ctx.FlagsValue(value["usage"], EnumFromString_VkBufferUsageFlagBits);
    ctx.EnumValue(value["sharingMode"], EnumFromString_VkSharingMode);
    ctx.UInt32Value(value["queueFamilyIndexCount"]);
    ctx.UInt32Array(value["pQueueFamilyIndices"], ctx.Length(value["queueFamilyIndexCount"]));
}

template <> void StructFromApiDump<VkImageCreateInfo>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.FlagsValue(value["flags"], EnumFromString_VkImageCreateFlagBits);
    ctx.EnumValue(value["imageType"], EnumFromString_VkImageType);
    ctx.EnumValue(value["format"], EnumFromString_VkFormat);
    StructFromApiDump<VkExtent3D>(ctx, value["extent"]);
    ctx.UInt32Value(value["mipLevels"]);
    ctx.UInt32Value(value["arrayLayers"]);
    ctx.EnumValue(value["samples"], EnumFromString_VkSampleCountFlagBits);
    ctx.EnumValue(value["tiling"], EnumFromString_VkImageTiling);
    ctx.FlagsValue(value["usage"], EnumFromString_VkImageUsageFlagBits);
    ctx.EnumValue(value["sharingMode"], EnumFromString_VkSharingMode);
    ctx.UInt32Value(value["queueFamilyIndexCount"]);
    ctx.UInt32Array(value["pQueueFamilyIndices"], ctx.Length(value["queueFamilyIndexCount"]));
    ctx.EnumValue(value["initialLayout"], EnumFromString_VkImageLayout);
}

template <> void StructFromApiDump<VkSubresourceLayout>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.UInt64Value(value["offset"]);
    ctx.UInt64Value(value["size"]);
    ctx.UInt64Value(value["rowPitch"]);
    ctx.UInt64Value(value["arrayPitch"]);
    ctx.UInt64Value(value["depthPitch"]);
}

template <> void StructFromApiDump<VkComponentMapping>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["r"], EnumFromString_VkComponentSwizzle);
    ctx.EnumValue(value["g"], EnumFromString_VkComponentSwizzle);
    ctx.EnumValue(value["b"], EnumFromString_VkComponentSwizzle);
    ctx.EnumValue(value["a"], EnumFromString_VkComponentSwizzle);
}

template <> void StructFromApiDump<VkImageSubresourceRange>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.FlagsValue(value["aspectMask"], EnumFromString_VkImageAspectFlagBits);
    ctx.UInt32Value(value["baseMipLevel"]);
    ctx.UInt32Value(value["levelCount"]);
    ctx.UInt32Value(value["baseArrayLayer"]);
    ctx.UInt32Value(value["layerCount"]);
}

template <> void StructFromApiDump<VkImageViewCreateInfo>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.FlagsValue(value["flags"], EnumFromString_VkImageViewCreateFlagBits);
    ctx.VulkanHandleValue(value["image"], VK_OBJECT_TYPE_IMAGE);
    ctx.EnumValue(value["viewType"], EnumFromString_VkImageViewType);
    ctx.EnumValue(value["format"], EnumFromString_VkFormat);
    StructFromApiDump<VkComponentMapping>(ctx, value["components"]);
    StructFromApiDump<VkImageSubresourceRange>(ctx, value["subresourceRange"]);
}

template <> void StructFromApiDump<VkCommandPoolCreateInfo>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.FlagsValue(value["flags"], EnumFromString_VkCommandPoolCreateFlagBits);
    ctx.UInt32Value(value["queueFamilyIndex"]);
}

template <> void StructFromApiDump<VkCommandBufferAllocateInfo>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.VulkanHandleValue(value["commandPool"], VK_OBJECT_TYPE_COMMAND_POOL);
    ctx.EnumValue(value["level"], EnumFromString_VkCommandBufferLevel);
    ctx.UInt32Value(value["commandBufferCount"]);
}

template <> void StructFromApiDump<VkCommandBufferInheritanceInfo>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.VulkanHandleValue(value["renderPass"], VK_OBJECT_TYPE_RENDER_PASS);
    ctx.UInt32Value(value["subpass"]);
    ctx.VulkanHandleValue(value["framebuffer"], VK_OBJECT_TYPE_FRAMEBUFFER);
    ctx.UInt32Value(value["occlusionQueryEnable"]);
    ctx.FlagsValue(value["queryFlags"], EnumFromString_VkQueryControlFlagBits);
    ctx.FlagsValue(value["pipelineStatistics"], EnumFromString_VkQueryPipelineStatisticFlagBits);
}

template <> void StructFromApiDump<VkCommandBufferBeginInfo>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.FlagsValue(value["flags"], EnumFromString_VkCommandBufferUsageFlagBits);
    StructPtrFromApiDump<VkCommandBufferInheritanceInfo>(ctx, value["pInheritanceInfo"]);
}

template <> void StructFromApiDump<VkBufferCopy>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.UInt64Value(value["srcOffset"]);
    ctx.UInt64Value(value["dstOffset"]);
    ctx.UInt64Value(value["size"]);
}

template <> void StructFromApiDump<VkImageSubresourceLayers>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.FlagsValue(value["aspectMask"], EnumFromString_VkImageAspectFlagBits);
    ctx.UInt32Value(value["mipLevel"]);
    ctx.UInt32Value(value["baseArrayLayer"]);
    ctx.UInt32Value(value["layerCount"]);
}

template <> void StructFromApiDump<VkBufferImageCopy>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.UInt64Value(value["bufferOffset"]);
    ctx.UInt32Value(value["bufferRowLength"]);
    ctx.UInt32Value(value["bufferImageHeight"]);
    StructFromApiDump<VkImageSubresourceLayers>(ctx, value["imageSubresource"]);
    StructFromApiDump<VkOffset3D>(ctx, value["imageOffset"]);
    StructFromApiDump<VkExtent3D>(ctx, value["imageExtent"]);
}

template <> void StructFromApiDump<VkImageCopy>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    StructFromApiDump<VkImageSubresourceLayers>(ctx, value["srcSubresource"]);
    StructFromApiDump<VkOffset3D>(ctx, value["srcOffset"]);
    StructFromApiDump<VkImageSubresourceLayers>(ctx, value["dstSubresource"]);
    StructFromApiDump<VkOffset3D>(ctx, value["dstOffset"]);
    StructFromApiDump<VkExtent3D>(ctx, value["extent"]);
}

template <> void StructFromApiDump<VkBufferMemoryBarrier>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.FlagsValue(value["srcAccessMask"], EnumFromString_VkAccessFlagBits);
    ctx.FlagsValue(value["dstAccessMask"], EnumFromString_VkAccessFlagBits);
    ctx.UInt32Value(value["srcQueueFamilyIndex"]);
    ctx.UInt32Value(value["dstQueueFamilyIndex"]);
    ctx.VulkanHandleValue(value["buffer"], VK_OBJECT_TYPE_BUFFER);
    ctx.UInt64Value(value["offset"]);
    ctx.UInt64Value(value["size"]);
}

template <> void StructFromApiDump<VkImageMemoryBarrier>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.FlagsValue(value["srcAccessMask"], EnumFromString_VkAccessFlagBits);
    ctx.FlagsValue(value["dstAccessMask"], EnumFromString_VkAccessFlagBits);
    ctx.EnumValue(value["oldLayout"], EnumFromString_VkImageLayout);
    ctx.EnumValue(value["newLayout"], EnumFromString_VkImageLayout);
    ctx.UInt32Value(value["srcQueueFamilyIndex"]);
    ctx.UInt32Value(value["dstQueueFamilyIndex"]);
    ctx.VulkanHandleValue(value["image"], VK_OBJECT_TYPE_IMAGE);
    StructFromApiDump<VkImageSubresourceRange>(ctx, value["subresourceRange"]);
}

template <> void StructFromApiDump<VkMemoryBarrier>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.FlagsValue(value["srcAccessMask"], EnumFromString_VkAccessFlagBits);
    ctx.FlagsValue(value["dstAccessMask"], EnumFromString_VkAccessFlagBits);
}

template <> void StructFromApiDump<VkDispatchIndirectCommand>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.UInt32Value(value["x"]);
    ctx.UInt32Value(value["y"]);
    ctx.UInt32Value(value["z"]);
}

template <> void StructFromApiDump<VkPipelineCacheHeaderVersionOne>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.UInt32Value(value["headerSize"]);
    ctx.EnumValue(value["headerVersion"], EnumFromString_VkPipelineCacheHeaderVersion);
    ctx.UInt32Value(value["vendorID"]);
    ctx.UInt32Value(value["deviceID"]);
    ctx.UInt8Array(value["pipelineCacheUUID"]);
}

template <> void StructFromApiDump<VkEventCreateInfo>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.FlagsValue(value["flags"], EnumFromString_VkEventCreateFlagBits);
}

template <> void StructFromApiDump<VkBufferViewCreateInfo>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.FlagsValue(value["flags"]);
    ctx.VulkanHandleValue(value["buffer"], VK_OBJECT_TYPE_BUFFER);
    ctx.EnumValue(value["format"], EnumFromString_VkFormat);
    ctx.UInt64Value(value["offset"]);
    ctx.UInt64Value(value["range"]);
}

template <> void StructFromApiDump<VkShaderModuleCreateInfo>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.FlagsValue(value["flags"]);
    ctx.SizeTValue(value["codeSize"]);
    ctx.UInt32Array(value["pCode"], (ctx.Length(value["codeSize"]) / 4));
}

template <> void StructFromApiDump<VkPipelineCacheCreateInfo>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.FlagsValue(value["flags"], EnumFromString_VkPipelineCacheCreateFlagBits);
    ctx.SizeTValue(value["initialDataSize"]);
    ctx.UInt8Array(value["pInitialData"], ctx.Length(value["initialDataSize"]));
}

template <> void StructFromApiDump<VkSpecializationMapEntry>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.UInt32Value(value["constantID"]);
    ctx.UInt32Value(value["offset"]);
    ctx.SizeTValue(value["size"]);
}

template <> void StructFromApiDump<VkSpecializationInfo>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.UInt32Value(value["mapEntryCount"]);
    StructArrayFromApiDump<VkSpecializationMapEntry>(ctx, value["pMapEntries"], ctx.Length(value["mapEntryCount"]));
    ctx.SizeTValue(value["dataSize"]);
    ctx.UInt8Array(value["pData"], ctx.Length(value["dataSize"]));
}

template <> void StructFromApiDump<VkPipelineShaderStageCreateInfo>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.FlagsValue(value["flags"], EnumFromString_VkPipelineShaderStageCreateFlagBits);
    ctx.EnumValue(value["stage"], EnumFromString_VkShaderStageFlagBits);
    ctx.VulkanHandleValue(value["module"], VK_OBJECT_TYPE_SHADER_MODULE);
    ctx.StringValue(value["pName"]);
    StructPtrFromApiDump<VkSpecializationInfo>(ctx, value["pSpecializationInfo"]);
}

template <> void StructFromApiDump<VkComputePipelineCreateInfo>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.FlagsValue(value["flags"], EnumFromString_VkPipelineCreateFlagBits);
    StructFromApiDump<VkPipelineShaderStageCreateInfo>(ctx, value["stage"]);
    ctx.VulkanHandleValue(value["layout"], VK_OBJECT_TYPE_PIPELINE_LAYOUT);
    ctx.VulkanHandleValue(value["basePipelineHandle"], VK_OBJECT_TYPE_PIPELINE);
    ctx.Int32Value(value["basePipelineIndex"]);
}

template <> void StructFromApiDump<VkPushConstantRange>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.FlagsValue(value["stageFlags"], EnumFromString_VkShaderStageFlagBits);
    ctx.UInt32Value(value["offset"]);
    ctx.UInt32Value(value["size"]);
}

template <> void StructFromApiDump<VkPipelineLayoutCreateInfo>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.FlagsValue(value["flags"], EnumFromString_VkPipelineLayoutCreateFlagBits);
    ctx.UInt32Value(value["setLayoutCount"]);
    ctx.VulkanHandleArray(value["pSetLayouts"], VK_OBJECT_TYPE_DESCRIPTOR_SET_LAYOUT, ctx.Length(value["setLayoutCount"]));
    ctx.UInt32Value(value["pushConstantRangeCount"]);
    StructArrayFromApiDump<VkPushConstantRange>(ctx, value["pPushConstantRanges"], ctx.Length(value["pushConstantRangeCount"]));
}

template <> void StructFromApiDump<VkSamplerCreateInfo>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.FlagsValue(value["flags"], EnumFromString_VkSamplerCreateFlagBits);
    ctx.EnumValue(value["magFilter"], EnumFromString_VkFilter);
    ctx.EnumValue(value["minFilter"], EnumFromString_VkFilter);
    ctx.EnumValue(value["mipmapMode"], EnumFromString_VkSamplerMipmapMode);
    ctx.EnumValue(value["addressModeU"], EnumFromString_VkSamplerAddressMode);
    ctx.EnumValue(value["addressModeV"], EnumFromString_VkSamplerAddressMode);
    ctx.EnumValue(value["addressModeW"], EnumFromString_VkSamplerAddressMode);
    ctx.FloatValue(value["mipLodBias"]);
    ctx.UInt32Value(value["anisotropyEnable"]);
    ctx.FloatValue(value["maxAnisotropy"]);
    ctx.UInt32Value(value["compareEnable"]);
    ctx.EnumValue(value["compareOp"], EnumFromString_VkCompareOp);
    ctx.FloatValue(value["minLod"]);
    ctx.FloatValue(value["maxLod"]);
    ctx.EnumValue(value["borderColor"], EnumFromString_VkBorderColor);
    ctx.UInt32Value(value["unnormalizedCoordinates"]);
}

template <> void StructFromApiDump<VkCopyDescriptorSet>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.VulkanHandleValue(value["srcSet"], VK_OBJECT_TYPE_DESCRIPTOR_SET);
    ctx.UInt32Value(value["srcBinding"]);
    ctx.UInt32Value(value["srcArrayElement"]);
    ctx.VulkanHandleValue(value["dstSet"], VK_OBJECT_TYPE_DESCRIPTOR_SET);
    ctx.UInt32Value(value["dstBinding"]);
    ctx.UInt32Value(value["dstArrayElement"]);
    ctx.UInt32Value(value["descriptorCount"]);
}

template <> void StructFromApiDump<VkDescriptorBufferInfo>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.VulkanHandleValue(value["buffer"], VK_OBJECT_TYPE_BUFFER);
    ctx.UInt64Value(value["offset"]);
    ctx.UInt64Value(value["range"]);
}

template <> void StructFromApiDump<VkDescriptorPoolSize>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["type"], EnumFromString_VkDescriptorType);
    ctx.UInt32Value(value["descriptorCount"]);
}

template <> void StructFromApiDump<VkDescriptorPoolCreateInfo>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.FlagsValue(value["flags"], EnumFromString_VkDescriptorPoolCreateFlagBits);
    ctx.UInt32Value(value["maxSets"]);
    ctx.UInt32Value(value["poolSizeCount"]);
    StructArrayFromApiDump<VkDescriptorPoolSize>(ctx, value["pPoolSizes"], ctx.Length(value["poolSizeCount"]));
}

template <> void StructFromApiDump<VkDescriptorSetAllocateInfo>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.VulkanHandleValue(value["descriptorPool"], VK_OBJECT_TYPE_DESCRIPTOR_POOL);
    ctx.UInt32Value(value["descriptorSetCount"]);
    ctx.VulkanHandleArray(value["pSetLayouts"], VK_OBJECT_TYPE_DESCRIPTOR_SET_LAYOUT, ctx.Length(value["descriptorSetCount"]));
}

template <> void StructFromApiDump<VkDescriptorSetLayoutBinding>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.UInt32Value(value["binding"]);
    ctx.EnumValue(value["descriptorType"], EnumFromString_VkDescriptorType);
    ctx.UInt32Value(value["descriptorCount"]);
    ctx.FlagsValue(value["stageFlags"], EnumFromString_VkShaderStageFlagBits);
    ctx.VulkanHandleArray(value["pImmutableSamplers"], VK_OBJECT_TYPE_SAMPLER, ctx.Length(value["descriptorCount"]));
}

template <> void StructFromApiDump<VkDescriptorSetLayoutCreateInfo>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.FlagsValue(value["flags"], EnumFromString_VkDescriptorSetLayoutCreateFlagBits);
    ctx.UInt32Value(value["bindingCount"]);
    StructArrayFromApiDump<VkDescriptorSetLayoutBinding>(ctx, value["pBindings"], ctx.Length(value["bindingCount"]));
}

template <> void StructFromApiDump<VkDrawIndexedIndirectCommand>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.UInt32Value(value["indexCount"]);
    ctx.UInt32Value(value["instanceCount"]);
    ctx.UInt32Value(value["firstIndex"]);
    ctx.Int32Value(value["vertexOffset"]);
    ctx.UInt32Value(value["firstInstance"]);
}

template <> void StructFromApiDump<VkDrawIndirectCommand>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.UInt32Value(value["vertexCount"]);
    ctx.UInt32Value(value["instanceCount"]);
    ctx.UInt32Value(value["firstVertex"]);
    ctx.UInt32Value(value["firstInstance"]);
}

template <> void StructFromApiDump<VkStencilOpState>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["failOp"], EnumFromString_VkStencilOp);
    ctx.EnumValue(value["passOp"], EnumFromString_VkStencilOp);
    ctx.EnumValue(value["depthFailOp"], EnumFromString_VkStencilOp);
    ctx.EnumValue(value["compareOp"], EnumFromString_VkCompareOp);
    ctx.UInt32Value(value["compareMask"]);
    ctx.UInt32Value(value["writeMask"]);
    ctx.UInt32Value(value["reference"]);
}

template <> void StructFromApiDump<VkVertexInputAttributeDescription>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.UInt32Value(value["location"]);
    ctx.UInt32Value(value["binding"]);
    ctx.EnumValue(value["format"], EnumFromString_VkFormat);
    ctx.UInt32Value(value["offset"]);
}

template <> void StructFromApiDump<VkVertexInputBindingDescription>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.UInt32Value(value["binding"]);
    ctx.UInt32Value(value["stride"]);
    ctx.EnumValue(value["inputRate"], EnumFromString_VkVertexInputRate);
}

template <> void StructFromApiDump<VkViewport>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.FloatValue(value["x"]);
    ctx.FloatValue(value["y"]);
    ctx.FloatValue(value["width"]);
    ctx.FloatValue(value["height"]);
    ctx.FloatValue(value["minDepth"]);
    ctx.FloatValue(value["maxDepth"]);
}

template <> void StructFromApiDump<VkPipelineColorBlendAttachmentState>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.UInt32Value(value["blendEnable"]);
    ctx.EnumValue(value["srcColorBlendFactor"], EnumFromString_VkBlendFactor);
    ctx.EnumValue(value["dstColorBlendFactor"], EnumFromString_VkBlendFactor);
    ctx.EnumValue(value["colorBlendOp"], EnumFromString_VkBlendOp);
    ctx.EnumValue(value["srcAlphaBlendFactor"], EnumFromString_VkBlendFactor);
    ctx.EnumValue(value["dstAlphaBlendFactor"], EnumFromString_VkBlendFactor);
    ctx.EnumValue(value["alphaBlendOp"], EnumFromString_VkBlendOp);
    ctx.FlagsValue(value["colorWriteMask"], EnumFromString_VkColorComponentFlagBits);
}

template <> void StructFromApiDump<VkPipelineColorBlendStateCreateInfo>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.FlagsValue(value["flags"], EnumFromString_VkPipelineColorBlendStateCreateFlagBits);
    ctx.UInt32Value(value["logicOpEnable"]);
    ctx.EnumValue(value["logicOp"], EnumFromString_VkLogicOp);
    ctx.UInt32Value(value["attachmentCount"]);
    StructArrayFromApiDump<VkPipelineColorBlendAttachmentState>(ctx, value["pAttachments"], ctx.Length(value["attachmentCount"]));
    ctx.FloatArray(value["blendConstants"], 4);
}

template <> void StructFromApiDump<VkPipelineDepthStencilStateCreateInfo>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.FlagsValue(value["flags"], EnumFromString_VkPipelineDepthStencilStateCreateFlagBits);
    ctx.UInt32Value(value["depthTestEnable"]);
    ctx.UInt32Value(value["depthWriteEnable"]);
    ctx.EnumValue(value["depthCompareOp"], EnumFromString_VkCompareOp);
    ctx.UInt32Value(value["depthBoundsTestEnable"]);
    ctx.UInt32Value(value["stencilTestEnable"]);
    StructFromApiDump<VkStencilOpState>(ctx, value["front"]);
    StructFromApiDump<VkStencilOpState>(ctx, value["back"]);
    ctx.FloatValue(value["minDepthBounds"]);
    ctx.FloatValue(value["maxDepthBounds"]);
}

template <> void StructFromApiDump<VkPipelineDynamicStateCreateInfo>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.FlagsValue(value["flags"]);
    ctx.UInt32Value(value["dynamicStateCount"]);
    ctx.EnumArray(value["pDynamicStates"], EnumFromString_VkDynamicState, ctx.Length(value["dynamicStateCount"]));
}

template <> void StructFromApiDump<VkPipelineInputAssemblyStateCreateInfo>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.FlagsValue(value["flags"]);
    ctx.EnumValue(value["topology"], EnumFromString_VkPrimitiveTopology);
    ctx.UInt32Value(value["primitiveRestartEnable"]);
}

template <> void StructFromApiDump<VkPipelineMultisampleStateCreateInfo>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.FlagsValue(value["flags"]);
    ctx.EnumValue(value["rasterizationSamples"], EnumFromString_VkSampleCountFlagBits);
    ctx.UInt32Value(value["sampleShadingEnable"]);
    ctx.FloatValue(value["minSampleShading"]);
    ctx.UInt32Array(value["pSampleMask"]);
    ctx.UInt32Value(value["alphaToCoverageEnable"]);
    ctx.UInt32Value(value["alphaToOneEnable"]);
}

template <> void StructFromApiDump<VkPipelineRasterizationStateCreateInfo>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.FlagsValue(value["flags"]);
    ctx.UInt32Value(value["depthClampEnable"]);
    ctx.UInt32Value(value["rasterizerDiscardEnable"]);
    ctx.EnumValue(value["polygonMode"], EnumFromString_VkPolygonMode);
    ctx.FlagsValue(value["cullMode"], EnumFromString_VkCullModeFlagBits);
    ctx.EnumValue(value["frontFace"], EnumFromString_VkFrontFace);
    ctx.UInt32Value(value["depthBiasEnable"]);
    ctx.FloatValue(value["depthBiasConstantFactor"]);
    ctx.FloatValue(value["depthBiasClamp"]);
    ctx.FloatValue(value["depthBiasSlopeFactor"]);
    ctx.FloatValue(value["lineWidth"]);
}

template <> void StructFromApiDump<VkPipelineTessellationStateCreateInfo>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.FlagsValue(value["flags"]);
    ctx.UInt32Value(value["patchControlPoints"]);
}

template <> void StructFromApiDump<VkPipelineVertexInputStateCreateInfo>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.FlagsValue(value["flags"]);
    ctx.UInt32Value(value["vertexBindingDescriptionCount"]);
    StructArrayFromApiDump<VkVertexInputBindingDescription>(ctx, value["pVertexBindingDescriptions"], ctx.Length(value["vertexBindingDescriptionCount"]));
    ctx.UInt32Value(value["vertexAttributeDescriptionCount"]);
    StructArrayFromApiDump<VkVertexInputAttributeDescription>(ctx, value["pVertexAttributeDescriptions"], ctx.Length(value["vertexAttributeDescriptionCount"]));
}

template <> void StructFromApiDump<VkPipelineViewportStateCreateInfo>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.FlagsValue(value["flags"]);
    ctx.UInt32Value(value["viewportCount"]);
    StructArrayFromApiDump<VkViewport>(ctx, value["pViewports"], ctx.Length(value["viewportCount"]));
    ctx.UInt32Value(value["scissorCount"]);
    StructArrayFromApiDump<VkRect2D>(ctx, value["pScissors"], ctx.Length(value["scissorCount"]));
}

template <> void StructFromApiDump<VkGraphicsPipelineCreateInfo>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.FlagsValue(value["flags"], EnumFromString_VkPipelineCreateFlagBits);
    ctx.UInt32Value(value["stageCount"]);
    StructArrayFromApiDump<VkPipelineShaderStageCreateInfo>(ctx, value["pStages"], ctx.Length(value["stageCount"]));
    StructPtrFromApiDump<VkPipelineVertexInputStateCreateInfo>(ctx, value["pVertexInputState"]);
    StructPtrFromApiDump<VkPipelineInputAssemblyStateCreateInfo>(ctx, value["pInputAssemblyState"]);
    StructPtrFromApiDump<VkPipelineTessellationStateCreateInfo>(ctx, value["pTessellationState"]);
    StructPtrFromApiDump<VkPipelineViewportStateCreateInfo>(ctx, value["pViewportState"]);
    StructPtrFromApiDump<VkPipelineRasterizationStateCreateInfo>(ctx, value["pRasterizationState"]);
    StructPtrFromApiDump<VkPipelineMultisampleStateCreateInfo>(ctx, value["pMultisampleState"]);
    StructPtrFromApiDump<VkPipelineDepthStencilStateCreateInfo>(ctx, value["pDepthStencilState"]);
    StructPtrFromApiDump<VkPipelineColorBlendStateCreateInfo>(ctx, value["pColorBlendState"]);
    StructPtrFromApiDump<VkPipelineDynamicStateCreateInfo>(ctx, value["pDynamicState"]);
    ctx.VulkanHandleValue(value["layout"], VK_OBJECT_TYPE_PIPELINE_LAYOUT);
    ctx.VulkanHandleValue(value["renderPass"], VK_OBJECT_TYPE_RENDER_PASS);
    ctx.UInt32Value(value["subpass"]);
    ctx.VulkanHandleValue(value["basePipelineHandle"], VK_OBJECT_TYPE_PIPELINE);
    ctx.Int32Value(value["basePipelineIndex"]);
}

template <> void StructFromApiDump<VkAttachmentDescription>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.FlagsValue(value["flags"], EnumFromString_VkAttachmentDescriptionFlagBits);
    ctx.EnumValue(value["format"], EnumFromString_VkFormat);
    ctx.EnumValue(value["samples"], EnumFromString_VkSampleCountFlagBits);
    ctx.EnumValue(value["loadOp"], EnumFromString_VkAttachmentLoadOp);
    ctx.EnumValue(value["storeOp"], EnumFromString_VkAttachmentStoreOp);
    ctx.EnumValue(value["stencilLoadOp"], EnumFromString_VkAttachmentLoadOp);
    ctx.EnumValue(value["stencilStoreOp"], EnumFromString_VkAttachmentStoreOp);
    ctx.EnumValue(value["initialLayout"], EnumFromString_VkImageLayout);
    ctx.EnumValue(value["finalLayout"], EnumFromString_VkImageLayout);
}

template <> void StructFromApiDump<VkAttachmentReference>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.UInt32Value(value["attachment"]);
    ctx.EnumValue(value["layout"], EnumFromString_VkImageLayout);
}

template <> void StructFromApiDump<VkFramebufferCreateInfo>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.FlagsValue(value["flags"], EnumFromString_VkFramebufferCreateFlagBits);
    ctx.VulkanHandleValue(value["renderPass"], VK_OBJECT_TYPE_RENDER_PASS);
    ctx.UInt32Value(value["attachmentCount"]);
    ctx.VulkanHandleArray(value["pAttachments"], VK_OBJECT_TYPE_IMAGE_VIEW, ctx.Length(value["attachmentCount"]));
    ctx.UInt32Value(value["width"]);
    ctx.UInt32Value(value["height"]);
    ctx.UInt32Value(value["layers"]);
}

template <> void StructFromApiDump<VkSubpassDependency>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.UInt32Value(value["srcSubpass"]);
    ctx.UInt32Value(value["dstSubpass"]);
    ctx.FlagsValue(value["srcStageMask"], EnumFromString_VkPipelineStageFlagBits);
    ctx.FlagsValue(value["dstStageMask"], EnumFromString_VkPipelineStageFlagBits);
    ctx.FlagsValue(value["srcAccessMask"], EnumFromString_VkAccessFlagBits);
    ctx.FlagsValue(value["dstAccessMask"], EnumFromString_VkAccessFlagBits);
    ctx.FlagsValue(value["dependencyFlags"], EnumFromString_VkDependencyFlagBits);
}

template <> void StructFromApiDump<VkSubpassDescription>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.FlagsValue(value["flags"], EnumFromString_VkSubpassDescriptionFlagBits);
    ctx.EnumValue(value["pipelineBindPoint"], EnumFromString_VkPipelineBindPoint);
    ctx.UInt32Value(value["inputAttachmentCount"]);
    StructArrayFromApiDump<VkAttachmentReference>(ctx, value["pInputAttachments"], ctx.Length(value["inputAttachmentCount"]));
    ctx.UInt32Value(value["colorAttachmentCount"]);
    StructArrayFromApiDump<VkAttachmentReference>(ctx, value["pColorAttachments"], ctx.Length(value["colorAttachmentCount"]));
    StructArrayFromApiDump<VkAttachmentReference>(ctx, value["pResolveAttachments"], ctx.Length(value["colorAttachmentCount"]));
    StructPtrFromApiDump<VkAttachmentReference>(ctx, value["pDepthStencilAttachment"]);
    ctx.UInt32Value(value["preserveAttachmentCount"]);
    ctx.UInt32Array(value["pPreserveAttachments"], ctx.Length(value["preserveAttachmentCount"]));
}

template <> void StructFromApiDump<VkRenderPassCreateInfo>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.FlagsValue(value["flags"], EnumFromString_VkRenderPassCreateFlagBits);
    ctx.UInt32Value(value["attachmentCount"]);
    StructArrayFromApiDump<VkAttachmentDescription>(ctx, value["pAttachments"], ctx.Length(value["attachmentCount"]));
    ctx.UInt32Value(value["subpassCount"]);
    StructArrayFromApiDump<VkSubpassDescription>(ctx, value["pSubpasses"], ctx.Length(value["subpassCount"]));
    ctx.UInt32Value(value["dependencyCount"]);
    StructArrayFromApiDump<VkSubpassDependency>(ctx, value["pDependencies"], ctx.Length(value["dependencyCount"]));
}

template <> void StructFromApiDump<VkClearDepthStencilValue>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.FloatValue(value["depth"]);
    ctx.UInt32Value(value["stencil"]);
}

template <> void StructFromApiDump<VkClearRect>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    StructFromApiDump<VkRect2D>(ctx, value["rect"]);
    ctx.UInt32Value(value["baseArrayLayer"]);
    ctx.UInt32Value(value["layerCount"]);
}

template <> void StructFromApiDump<VkClearAttachment>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.FlagsValue(value["aspectMask"], EnumFromString_VkImageAspectFlagBits);
    ctx.UInt32Value(value["colorAttachment"]);
    StructFromApiDump<VkClearValue>(ctx, value["clearValue"]);
}

template <> void StructFromApiDump<VkImageBlit>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    StructFromApiDump<VkImageSubresourceLayers>(ctx, value["srcSubresource"]);
    StructArrayFromApiDump<VkOffset3D>(ctx, value["srcOffsets"], 2);
    StructFromApiDump<VkImageSubresourceLayers>(ctx, value["dstSubresource"]);
    StructArrayFromApiDump<VkOffset3D>(ctx, value["dstOffsets"], 2);
}

template <> void StructFromApiDump<VkImageResolve>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    StructFromApiDump<VkImageSubresourceLayers>(ctx, value["srcSubresource"]);
    StructFromApiDump<VkOffset3D>(ctx, value["srcOffset"]);
    StructFromApiDump<VkImageSubresourceLayers>(ctx, value["dstSubresource"]);
    StructFromApiDump<VkOffset3D>(ctx, value["dstOffset"]);
    StructFromApiDump<VkExtent3D>(ctx, value["extent"]);
}

template <> void StructFromApiDump<VkRenderPassBeginInfo>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.VulkanHandleValue(value["renderPass"], VK_OBJECT_TYPE_RENDER_PASS);
    ctx.VulkanHandleValue(value["framebuffer"], VK_OBJECT_TYPE_FRAMEBUFFER);
    StructFromApiDump<VkRect2D>(ctx, value["renderArea"]);
    ctx.UInt32Value(value["clearValueCount"]);
    StructArrayFromApiDump<VkClearValue>(ctx, value["pClearValues"], ctx.Length(value["clearValueCount"]));
}

template <> void StructFromApiDump<VkBindBufferMemoryInfo>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.VulkanHandleValue(value["buffer"], VK_OBJECT_TYPE_BUFFER);
    ctx.VulkanHandleValue(value["memory"], VK_OBJECT_TYPE_DEVICE_MEMORY);
    ctx.UInt64Value(value["memoryOffset"]);
}

template <> void StructFromApiDump<VkBindImageMemoryInfo>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.VulkanHandleValue(value["image"], VK_OBJECT_TYPE_IMAGE);
    ctx.VulkanHandleValue(value["memory"], VK_OBJECT_TYPE_DEVICE_MEMORY);
    ctx.UInt64Value(value["memoryOffset"]);
}

template <> void StructFromApiDump<VkMemoryDedicatedRequirements>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["prefersDedicatedAllocation"]);
    ctx.UInt32Value(value["requiresDedicatedAllocation"]);
}

template <> void StructFromApiDump<VkMemoryDedicatedAllocateInfo>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.VulkanHandleValue(value["image"], VK_OBJECT_TYPE_IMAGE);
    ctx.VulkanHandleValue(value["buffer"], VK_OBJECT_TYPE_BUFFER);
}

template <> void StructFromApiDump<VkMemoryAllocateFlagsInfo>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.FlagsValue(value["flags"], EnumFromString_VkMemoryAllocateFlagBits);
    ctx.UInt32Value(value["deviceMask"]);
}

template <> void StructFromApiDump<VkDeviceGroupCommandBufferBeginInfo>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["deviceMask"]);
}

template <> void StructFromApiDump<VkDeviceGroupSubmitInfo>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["waitSemaphoreCount"]);
    ctx.UInt32Array(value["pWaitSemaphoreDeviceIndices"], ctx.Length(value["waitSemaphoreCount"]));
    ctx.UInt32Value(value["commandBufferCount"]);
    ctx.UInt32Array(value["pCommandBufferDeviceMasks"], ctx.Length(value["commandBufferCount"]));
    ctx.UInt32Value(value["signalSemaphoreCount"]);
    ctx.UInt32Array(value["pSignalSemaphoreDeviceIndices"], ctx.Length(value["signalSemaphoreCount"]));
}

template <> void StructFromApiDump<VkDeviceGroupBindSparseInfo>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["resourceDeviceIndex"]);
    ctx.UInt32Value(value["memoryDeviceIndex"]);
}

template <> void StructFromApiDump<VkBindBufferMemoryDeviceGroupInfo>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["deviceIndexCount"]);
    ctx.UInt32Array(value["pDeviceIndices"], ctx.Length(value["deviceIndexCount"]));
}

template <> void StructFromApiDump<VkBindImageMemoryDeviceGroupInfo>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["deviceIndexCount"]);
    ctx.UInt32Array(value["pDeviceIndices"], ctx.Length(value["deviceIndexCount"]));
    ctx.UInt32Value(value["splitInstanceBindRegionCount"]);
    StructArrayFromApiDump<VkRect2D>(ctx, value["pSplitInstanceBindRegions"], ctx.Length(value["splitInstanceBindRegionCount"]));
}

template <> void StructFromApiDump<VkPhysicalDeviceGroupProperties>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["physicalDeviceCount"]);
    ctx.VulkanHandleArray(value["physicalDevices"], VK_OBJECT_TYPE_PHYSICAL_DEVICE, ctx.Length(value["physicalDeviceCount"]));
    ctx.UInt32Value(value["subsetAllocation"]);
}

template <> void StructFromApiDump<VkDeviceGroupDeviceCreateInfo>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["physicalDeviceCount"]);
    ctx.VulkanHandleArray(value["pPhysicalDevices"], VK_OBJECT_TYPE_PHYSICAL_DEVICE, ctx.Length(value["physicalDeviceCount"]));
}

template <> void StructFromApiDump<VkBufferMemoryRequirementsInfo2>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.VulkanHandleValue(value["buffer"], VK_OBJECT_TYPE_BUFFER);
}

template <> void StructFromApiDump<VkImageMemoryRequirementsInfo2>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.VulkanHandleValue(value["image"], VK_OBJECT_TYPE_IMAGE);
}

template <> void StructFromApiDump<VkImageSparseMemoryRequirementsInfo2>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.VulkanHandleValue(value["image"], VK_OBJECT_TYPE_IMAGE);
}

template <> void StructFromApiDump<VkMemoryRequirements2>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    StructFromApiDump<VkMemoryRequirements>(ctx, value["memoryRequirements"]);
}

template <> void StructFromApiDump<VkSparseImageMemoryRequirements2>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    StructFromApiDump<VkSparseImageMemoryRequirements>(ctx, value["memoryRequirements"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceFeatures2>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    StructFromApiDump<VkPhysicalDeviceFeatures>(ctx, value["features"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceProperties2>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    StructFromApiDump<VkPhysicalDeviceProperties>(ctx, value["properties"]);
}

template <> void StructFromApiDump<VkFormatProperties2>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    StructFromApiDump<VkFormatProperties>(ctx, value["formatProperties"]);
}

template <> void StructFromApiDump<VkImageFormatProperties2>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    StructFromApiDump<VkImageFormatProperties>(ctx, value["imageFormatProperties"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceImageFormatInfo2>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.EnumValue(value["format"], EnumFromString_VkFormat);
    ctx.EnumValue(value["type"], EnumFromString_VkImageType);
    ctx.EnumValue(value["tiling"], EnumFromString_VkImageTiling);
    ctx.FlagsValue(value["usage"], EnumFromString_VkImageUsageFlagBits);
    ctx.FlagsValue(value["flags"], EnumFromString_VkImageCreateFlagBits);
}

template <> void StructFromApiDump<VkQueueFamilyProperties2>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    StructFromApiDump<VkQueueFamilyProperties>(ctx, value["queueFamilyProperties"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceMemoryProperties2>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    StructFromApiDump<VkPhysicalDeviceMemoryProperties>(ctx, value["memoryProperties"]);
}

template <> void StructFromApiDump<VkSparseImageFormatProperties2>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    StructFromApiDump<VkSparseImageFormatProperties>(ctx, value["properties"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceSparseImageFormatInfo2>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.EnumValue(value["format"], EnumFromString_VkFormat);
    ctx.EnumValue(value["type"], EnumFromString_VkImageType);
    ctx.EnumValue(value["samples"], EnumFromString_VkSampleCountFlagBits);
    ctx.FlagsValue(value["usage"], EnumFromString_VkImageUsageFlagBits);
    ctx.EnumValue(value["tiling"], EnumFromString_VkImageTiling);
}

template <> void StructFromApiDump<VkImageViewUsageCreateInfo>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.FlagsValue(value["usage"], EnumFromString_VkImageUsageFlagBits);
}

template <> void StructFromApiDump<VkPhysicalDeviceProtectedMemoryFeatures>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["protectedMemory"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceProtectedMemoryProperties>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["protectedNoFault"]);
}

template <> void StructFromApiDump<VkDeviceQueueInfo2>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.FlagsValue(value["flags"], EnumFromString_VkDeviceQueueCreateFlagBits);
    ctx.UInt32Value(value["queueFamilyIndex"]);
    ctx.UInt32Value(value["queueIndex"]);
}

template <> void StructFromApiDump<VkProtectedSubmitInfo>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["protectedSubmit"]);
}

template <> void StructFromApiDump<VkBindImagePlaneMemoryInfo>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.EnumValue(value["planeAspect"], EnumFromString_VkImageAspectFlagBits);
}

template <> void StructFromApiDump<VkImagePlaneMemoryRequirementsInfo>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.EnumValue(value["planeAspect"], EnumFromString_VkImageAspectFlagBits);
}

template <> void StructFromApiDump<VkExternalMemoryProperties>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.FlagsValue(value["externalMemoryFeatures"], EnumFromString_VkExternalMemoryFeatureFlagBits);
    ctx.FlagsValue(value["exportFromImportedHandleTypes"], EnumFromString_VkExternalMemoryHandleTypeFlagBits);
    ctx.FlagsValue(value["compatibleHandleTypes"], EnumFromString_VkExternalMemoryHandleTypeFlagBits);
}

template <> void StructFromApiDump<VkPhysicalDeviceExternalImageFormatInfo>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.EnumValue(value["handleType"], EnumFromString_VkExternalMemoryHandleTypeFlagBits);
}

template <> void StructFromApiDump<VkExternalImageFormatProperties>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    StructFromApiDump<VkExternalMemoryProperties>(ctx, value["externalMemoryProperties"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceExternalBufferInfo>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.FlagsValue(value["flags"], EnumFromString_VkBufferCreateFlagBits);
    ctx.FlagsValue(value["usage"], EnumFromString_VkBufferUsageFlagBits);
    ctx.EnumValue(value["handleType"], EnumFromString_VkExternalMemoryHandleTypeFlagBits);
}

template <> void StructFromApiDump<VkExternalBufferProperties>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    StructFromApiDump<VkExternalMemoryProperties>(ctx, value["externalMemoryProperties"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceIDProperties>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt8Array(value["deviceUUID"]);
    ctx.UInt8Array(value["driverUUID"]);
    ctx.UInt8Array(value["deviceLUID"]);
    ctx.UInt32Value(value["deviceNodeMask"]);
    ctx.UInt32Value(value["deviceLUIDValid"]);
}

template <> void StructFromApiDump<VkExternalMemoryImageCreateInfo>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.FlagsValue(value["handleTypes"], EnumFromString_VkExternalMemoryHandleTypeFlagBits);
}

template <> void StructFromApiDump<VkExternalMemoryBufferCreateInfo>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.FlagsValue(value["handleTypes"], EnumFromString_VkExternalMemoryHandleTypeFlagBits);
}

template <> void StructFromApiDump<VkExportMemoryAllocateInfo>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.FlagsValue(value["handleTypes"], EnumFromString_VkExternalMemoryHandleTypeFlagBits);
}

template <> void StructFromApiDump<VkPhysicalDeviceExternalFenceInfo>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.EnumValue(value["handleType"], EnumFromString_VkExternalFenceHandleTypeFlagBits);
}

template <> void StructFromApiDump<VkExternalFenceProperties>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.FlagsValue(value["exportFromImportedHandleTypes"], EnumFromString_VkExternalFenceHandleTypeFlagBits);
    ctx.FlagsValue(value["compatibleHandleTypes"], EnumFromString_VkExternalFenceHandleTypeFlagBits);
    ctx.FlagsValue(value["externalFenceFeatures"], EnumFromString_VkExternalFenceFeatureFlagBits);
}

template <> void StructFromApiDump<VkExportFenceCreateInfo>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.FlagsValue(value["handleTypes"], EnumFromString_VkExternalFenceHandleTypeFlagBits);
}

template <> void StructFromApiDump<VkExportSemaphoreCreateInfo>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.FlagsValue(value["handleTypes"], EnumFromString_VkExternalSemaphoreHandleTypeFlagBits);
}

template <> void StructFromApiDump<VkPhysicalDeviceExternalSemaphoreInfo>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.EnumValue(value["handleType"], EnumFromString_VkExternalSemaphoreHandleTypeFlagBits);
}

template <> void StructFromApiDump<VkExternalSemaphoreProperties>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.FlagsValue(value["exportFromImportedHandleTypes"], EnumFromString_VkExternalSemaphoreHandleTypeFlagBits);
    ctx.FlagsValue(value["compatibleHandleTypes"], EnumFromString_VkExternalSemaphoreHandleTypeFlagBits);
    ctx.FlagsValue(value["externalSemaphoreFeatures"], EnumFromString_VkExternalSemaphoreFeatureFlagBits);
}

template <> void StructFromApiDump<VkPhysicalDeviceSubgroupProperties>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["subgroupSize"]);
    ctx.FlagsValue(value["supportedStages"], EnumFromString_VkShaderStageFlagBits);
    ctx.FlagsValue(value["supportedOperations"], EnumFromString_VkSubgroupFeatureFlagBits);
    ctx.UInt32Value(value["quadOperationsInAllStages"]);
}

template <> void StructFromApiDump<VkPhysicalDevice16BitStorageFeatures>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["storageBuffer16BitAccess"]);
    ctx.UInt32Value(value["uniformAndStorageBuffer16BitAccess"]);
    ctx.UInt32Value(value["storagePushConstant16"]);
    ctx.UInt32Value(value["storageInputOutput16"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceVariablePointersFeatures>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["variablePointersStorageBuffer"]);
    ctx.UInt32Value(value["variablePointers"]);
}

template <> void StructFromApiDump<VkDescriptorUpdateTemplateEntry>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.UInt32Value(value["dstBinding"]);
    ctx.UInt32Value(value["dstArrayElement"]);
    ctx.UInt32Value(value["descriptorCount"]);
    ctx.EnumValue(value["descriptorType"], EnumFromString_VkDescriptorType);
    ctx.SizeTValue(value["offset"]);
    ctx.SizeTValue(value["stride"]);
}

template <> void StructFromApiDump<VkDescriptorUpdateTemplateCreateInfo>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.FlagsValue(value["flags"]);
    ctx.UInt32Value(value["descriptorUpdateEntryCount"]);
    StructArrayFromApiDump<VkDescriptorUpdateTemplateEntry>(ctx, value["pDescriptorUpdateEntries"], ctx.Length(value["descriptorUpdateEntryCount"]));
    ctx.EnumValue(value["templateType"], EnumFromString_VkDescriptorUpdateTemplateType);
    ctx.VulkanHandleValue(value["descriptorSetLayout"], VK_OBJECT_TYPE_DESCRIPTOR_SET_LAYOUT);
    ctx.EnumValue(value["pipelineBindPoint"], EnumFromString_VkPipelineBindPoint);
    ctx.VulkanHandleValue(value["pipelineLayout"], VK_OBJECT_TYPE_PIPELINE_LAYOUT);
    ctx.UInt32Value(value["set"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceMaintenance3Properties>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["maxPerSetDescriptors"]);
    ctx.UInt64Value(value["maxMemoryAllocationSize"]);
}

template <> void StructFromApiDump<VkDescriptorSetLayoutSupport>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["supported"]);
}

template <> void StructFromApiDump<VkSamplerYcbcrConversionCreateInfo>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.EnumValue(value["format"], EnumFromString_VkFormat);
    ctx.EnumValue(value["ycbcrModel"], EnumFromString_VkSamplerYcbcrModelConversion);
    ctx.EnumValue(value["ycbcrRange"], EnumFromString_VkSamplerYcbcrRange);
    StructFromApiDump<VkComponentMapping>(ctx, value["components"]);
    ctx.EnumValue(value["xChromaOffset"], EnumFromString_VkChromaLocation);
    ctx.EnumValue(value["yChromaOffset"], EnumFromString_VkChromaLocation);
    ctx.EnumValue(value["chromaFilter"], EnumFromString_VkFilter);
    ctx.UInt32Value(value["forceExplicitReconstruction"]);
}

template <> void StructFromApiDump<VkSamplerYcbcrConversionInfo>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.VulkanHandleValue(value["conversion"], VK_OBJECT_TYPE_SAMPLER_YCBCR_CONVERSION);
}

template <> void StructFromApiDump<VkPhysicalDeviceSamplerYcbcrConversionFeatures>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["samplerYcbcrConversion"]);
}

template <> void StructFromApiDump<VkSamplerYcbcrConversionImageFormatProperties>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["combinedImageSamplerDescriptorCount"]);
}

template <> void StructFromApiDump<VkDeviceGroupRenderPassBeginInfo>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["deviceMask"]);
    ctx.UInt32Value(value["deviceRenderAreaCount"]);
    StructArrayFromApiDump<VkRect2D>(ctx, value["pDeviceRenderAreas"], ctx.Length(value["deviceRenderAreaCount"]));
}

template <> void StructFromApiDump<VkPhysicalDevicePointClippingProperties>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.EnumValue(value["pointClippingBehavior"], EnumFromString_VkPointClippingBehavior);
}

template <> void StructFromApiDump<VkInputAttachmentAspectReference>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.UInt32Value(value["subpass"]);
    ctx.UInt32Value(value["inputAttachmentIndex"]);
    ctx.FlagsValue(value["aspectMask"], EnumFromString_VkImageAspectFlagBits);
}

template <> void StructFromApiDump<VkRenderPassInputAttachmentAspectCreateInfo>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["aspectReferenceCount"]);
    StructArrayFromApiDump<VkInputAttachmentAspectReference>(ctx, value["pAspectReferences"], ctx.Length(value["aspectReferenceCount"]));
}

template <> void StructFromApiDump<VkPipelineTessellationDomainOriginStateCreateInfo>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.EnumValue(value["domainOrigin"], EnumFromString_VkTessellationDomainOrigin);
}

template <> void StructFromApiDump<VkRenderPassMultiviewCreateInfo>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["subpassCount"]);
    ctx.UInt32Array(value["pViewMasks"], ctx.Length(value["subpassCount"]));
    ctx.UInt32Value(value["dependencyCount"]);
    ctx.Int32Array(value["pViewOffsets"], ctx.Length(value["dependencyCount"]));
    ctx.UInt32Value(value["correlationMaskCount"]);
    ctx.UInt32Array(value["pCorrelationMasks"], ctx.Length(value["correlationMaskCount"]));
}

template <> void StructFromApiDump<VkPhysicalDeviceMultiviewFeatures>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["multiview"]);
    ctx.UInt32Value(value["multiviewGeometryShader"]);
    ctx.UInt32Value(value["multiviewTessellationShader"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceMultiviewProperties>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["maxMultiviewViewCount"]);
    ctx.UInt32Value(value["maxMultiviewInstanceIndex"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceShaderDrawParametersFeatures>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["shaderDrawParameters"]);
}

template <> void StructFromApiDump<VkConformanceVersion>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.UInt8Value(value["major"]);
    ctx.UInt8Value(value["minor"]);
    ctx.UInt8Value(value["subminor"]);
    ctx.UInt8Value(value["patch"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceDriverProperties>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.EnumValue(value["driverID"], EnumFromString_VkDriverId);
    ctx.StringValue(value["driverName"]);
    ctx.StringValue(value["driverInfo"]);
    StructFromApiDump<VkConformanceVersion>(ctx, value["conformanceVersion"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceVulkan11Features>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["storageBuffer16BitAccess"]);
    ctx.UInt32Value(value["uniformAndStorageBuffer16BitAccess"]);
    ctx.UInt32Value(value["storagePushConstant16"]);
    ctx.UInt32Value(value["storageInputOutput16"]);
    ctx.UInt32Value(value["multiview"]);
    ctx.UInt32Value(value["multiviewGeometryShader"]);
    ctx.UInt32Value(value["multiviewTessellationShader"]);
    ctx.UInt32Value(value["variablePointersStorageBuffer"]);
    ctx.UInt32Value(value["variablePointers"]);
    ctx.UInt32Value(value["protectedMemory"]);
    ctx.UInt32Value(value["samplerYcbcrConversion"]);
    ctx.UInt32Value(value["shaderDrawParameters"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceVulkan11Properties>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt8Array(value["deviceUUID"]);
    ctx.UInt8Array(value["driverUUID"]);
    ctx.UInt8Array(value["deviceLUID"]);
    ctx.UInt32Value(value["deviceNodeMask"]);
    ctx.UInt32Value(value["deviceLUIDValid"]);
    ctx.UInt32Value(value["subgroupSize"]);
    ctx.FlagsValue(value["subgroupSupportedStages"], EnumFromString_VkShaderStageFlagBits);
    ctx.FlagsValue(value["subgroupSupportedOperations"], EnumFromString_VkSubgroupFeatureFlagBits);
    ctx.UInt32Value(value["subgroupQuadOperationsInAllStages"]);
    ctx.EnumValue(value["pointClippingBehavior"], EnumFromString_VkPointClippingBehavior);
    ctx.UInt32Value(value["maxMultiviewViewCount"]);
    ctx.UInt32Value(value["maxMultiviewInstanceIndex"]);
    ctx.UInt32Value(value["protectedNoFault"]);
    ctx.UInt32Value(value["maxPerSetDescriptors"]);
    ctx.UInt64Value(value["maxMemoryAllocationSize"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceVulkan12Features>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["samplerMirrorClampToEdge"]);
    ctx.UInt32Value(value["drawIndirectCount"]);
    ctx.UInt32Value(value["storageBuffer8BitAccess"]);
    ctx.UInt32Value(value["uniformAndStorageBuffer8BitAccess"]);
    ctx.UInt32Value(value["storagePushConstant8"]);
    ctx.UInt32Value(value["shaderBufferInt64Atomics"]);
    ctx.UInt32Value(value["shaderSharedInt64Atomics"]);
    ctx.UInt32Value(value["shaderFloat16"]);
    ctx.UInt32Value(value["shaderInt8"]);
    ctx.UInt32Value(value["descriptorIndexing"]);
    ctx.UInt32Value(value["shaderInputAttachmentArrayDynamicIndexing"]);
    ctx.UInt32Value(value["shaderUniformTexelBufferArrayDynamicIndexing"]);
    ctx.UInt32Value(value["shaderStorageTexelBufferArrayDynamicIndexing"]);
    ctx.UInt32Value(value["shaderUniformBufferArrayNonUniformIndexing"]);
    ctx.UInt32Value(value["shaderSampledImageArrayNonUniformIndexing"]);
    ctx.UInt32Value(value["shaderStorageBufferArrayNonUniformIndexing"]);
    ctx.UInt32Value(value["shaderStorageImageArrayNonUniformIndexing"]);
    ctx.UInt32Value(value["shaderInputAttachmentArrayNonUniformIndexing"]);
    ctx.UInt32Value(value["shaderUniformTexelBufferArrayNonUniformIndexing"]);
    ctx.UInt32Value(value["shaderStorageTexelBufferArrayNonUniformIndexing"]);
    ctx.UInt32Value(value["descriptorBindingUniformBufferUpdateAfterBind"]);
    ctx.UInt32Value(value["descriptorBindingSampledImageUpdateAfterBind"]);
    ctx.UInt32Value(value["descriptorBindingStorageImageUpdateAfterBind"]);
    ctx.UInt32Value(value["descriptorBindingStorageBufferUpdateAfterBind"]);
    ctx.UInt32Value(value["descriptorBindingUniformTexelBufferUpdateAfterBind"]);
    ctx.UInt32Value(value["descriptorBindingStorageTexelBufferUpdateAfterBind"]);
    ctx.UInt32Value(value["descriptorBindingUpdateUnusedWhilePending"]);
    ctx.UInt32Value(value["descriptorBindingPartiallyBound"]);
    ctx.UInt32Value(value["descriptorBindingVariableDescriptorCount"]);
    ctx.UInt32Value(value["runtimeDescriptorArray"]);
    ctx.UInt32Value(value["samplerFilterMinmax"]);
    ctx.UInt32Value(value["scalarBlockLayout"]);
    ctx.UInt32Value(value["imagelessFramebuffer"]);
    ctx.UInt32Value(value["uniformBufferStandardLayout"]);
    ctx.UInt32Value(value["shaderSubgroupExtendedTypes"]);
    ctx.UInt32Value(value["separateDepthStencilLayouts"]);
    ctx.UInt32Value(value["hostQueryReset"]);
    ctx.UInt32Value(value["timelineSemaphore"]);
    ctx.UInt32Value(value["bufferDeviceAddress"]);
    ctx.UInt32Value(value["bufferDeviceAddressCaptureReplay"]);
    ctx.UInt32Value(value["bufferDeviceAddressMultiDevice"]);
    ctx.UInt32Value(value["vulkanMemoryModel"]);
    ctx.UInt32Value(value["vulkanMemoryModelDeviceScope"]);
    ctx.UInt32Value(value["vulkanMemoryModelAvailabilityVisibilityChains"]);
    ctx.UInt32Value(value["shaderOutputViewportIndex"]);
    ctx.UInt32Value(value["shaderOutputLayer"]);
    ctx.UInt32Value(value["subgroupBroadcastDynamicId"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceVulkan12Properties>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.EnumValue(value["driverID"], EnumFromString_VkDriverId);
    ctx.StringValue(value["driverName"]);
    ctx.StringValue(value["driverInfo"]);
    StructFromApiDump<VkConformanceVersion>(ctx, value["conformanceVersion"]);
    ctx.EnumValue(value["denormBehaviorIndependence"], EnumFromString_VkShaderFloatControlsIndependence);
    ctx.EnumValue(value["roundingModeIndependence"], EnumFromString_VkShaderFloatControlsIndependence);
    ctx.UInt32Value(value["shaderSignedZeroInfNanPreserveFloat16"]);
    ctx.UInt32Value(value["shaderSignedZeroInfNanPreserveFloat32"]);
    ctx.UInt32Value(value["shaderSignedZeroInfNanPreserveFloat64"]);
    ctx.UInt32Value(value["shaderDenormPreserveFloat16"]);
    ctx.UInt32Value(value["shaderDenormPreserveFloat32"]);
    ctx.UInt32Value(value["shaderDenormPreserveFloat64"]);
    ctx.UInt32Value(value["shaderDenormFlushToZeroFloat16"]);
    ctx.UInt32Value(value["shaderDenormFlushToZeroFloat32"]);
    ctx.UInt32Value(value["shaderDenormFlushToZeroFloat64"]);
    ctx.UInt32Value(value["shaderRoundingModeRTEFloat16"]);
    ctx.UInt32Value(value["shaderRoundingModeRTEFloat32"]);
    ctx.UInt32Value(value["shaderRoundingModeRTEFloat64"]);
    ctx.UInt32Value(value["shaderRoundingModeRTZFloat16"]);
    ctx.UInt32Value(value["shaderRoundingModeRTZFloat32"]);
    ctx.UInt32Value(value["shaderRoundingModeRTZFloat64"]);
    ctx.UInt32Value(value["maxUpdateAfterBindDescriptorsInAllPools"]);
    ctx.UInt32Value(value["shaderUniformBufferArrayNonUniformIndexingNative"]);
    ctx.UInt32Value(value["shaderSampledImageArrayNonUniformIndexingNative"]);
    ctx.UInt32Value(value["shaderStorageBufferArrayNonUniformIndexingNative"]);
    ctx.UInt32Value(value["shaderStorageImageArrayNonUniformIndexingNative"]);
    ctx.UInt32Value(value["shaderInputAttachmentArrayNonUniformIndexingNative"]);
    ctx.UInt32Value(value["robustBufferAccessUpdateAfterBind"]);
    ctx.UInt32Value(value["quadDivergentImplicitLod"]);
    ctx.UInt32Value(value["maxPerStageDescriptorUpdateAfterBindSamplers"]);
    ctx.UInt32Value(value["maxPerStageDescriptorUpdateAfterBindUniformBuffers"]);
    ctx.UInt32Value(value["maxPerStageDescriptorUpdateAfterBindStorageBuffers"]);
    ctx.UInt32Value(value["maxPerStageDescriptorUpdateAfterBindSampledImages"]);
    ctx.UInt32Value(value["maxPerStageDescriptorUpdateAfterBindStorageImages"]);
    ctx.UInt32Value(value["maxPerStageDescriptorUpdateAfterBindInputAttachments"]);
    ctx.UInt32Value(value["maxPerStageUpdateAfterBindResources"]);
    ctx.UInt32Value(value["maxDescriptorSetUpdateAfterBindSamplers"]);
    ctx.UInt32Value(value["maxDescriptorSetUpdateAfterBindUniformBuffers"]);
    ctx.UInt32Value(value["maxDescriptorSetUpdateAfterBindUniformBuffersDynamic"]);
    ctx.UInt32Value(value["maxDescriptorSetUpdateAfterBindStorageBuffers"]);
    ctx.UInt32Value(value["maxDescriptorSetUpdateAfterBindStorageBuffersDynamic"]);
    ctx.UInt32Value(value["maxDescriptorSetUpdateAfterBindSampledImages"]);
    ctx.UInt32Value(value["maxDescriptorSetUpdateAfterBindStorageImages"]);
    ctx.UInt32Value(value["maxDescriptorSetUpdateAfterBindInputAttachments"]);
    ctx.FlagsValue(value["supportedDepthResolveModes"], EnumFromString_VkResolveModeFlagBits);
    ctx.FlagsValue(value["supportedStencilResolveModes"], EnumFromString_VkResolveModeFlagBits);
    ctx.UInt32Value(value["independentResolveNone"]);
    ctx.UInt32Value(value["independentResolve"]);
    ctx.UInt32Value(value["filterMinmaxSingleComponentFormats"]);
    ctx.UInt32Value(value["filterMinmaxImageComponentMapping"]);
    ctx.UInt64Value(value["maxTimelineSemaphoreValueDifference"]);
    ctx.FlagsValue(value["framebufferIntegerColorSampleCounts"], EnumFromString_VkSampleCountFlagBits);
}

template <> void StructFromApiDump<VkImageFormatListCreateInfo>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["viewFormatCount"]);
    ctx.EnumArray(value["pViewFormats"], EnumFromString_VkFormat, ctx.Length(value["viewFormatCount"]));
}

template <> void StructFromApiDump<VkPhysicalDeviceVulkanMemoryModelFeatures>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["vulkanMemoryModel"]);
    ctx.UInt32Value(value["vulkanMemoryModelDeviceScope"]);
    ctx.UInt32Value(value["vulkanMemoryModelAvailabilityVisibilityChains"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceHostQueryResetFeatures>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["hostQueryReset"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceTimelineSemaphoreFeatures>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["timelineSemaphore"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceTimelineSemaphoreProperties>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt64Value(value["maxTimelineSemaphoreValueDifference"]);
}

template <> void StructFromApiDump<VkSemaphoreTypeCreateInfo>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.EnumValue(value["semaphoreType"], EnumFromString_VkSemaphoreType);
    ctx.UInt64Value(value["initialValue"]);
}

template <> void StructFromApiDump<VkTimelineSemaphoreSubmitInfo>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["waitSemaphoreValueCount"]);
    ctx.UInt64Array(value["pWaitSemaphoreValues"], ctx.Length(value["waitSemaphoreValueCount"]));
    ctx.UInt32Value(value["signalSemaphoreValueCount"]);
    ctx.UInt64Array(value["pSignalSemaphoreValues"], ctx.Length(value["signalSemaphoreValueCount"]));
}

template <> void StructFromApiDump<VkSemaphoreWaitInfo>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.FlagsValue(value["flags"], EnumFromString_VkSemaphoreWaitFlagBits);
    ctx.UInt32Value(value["semaphoreCount"]);
    ctx.VulkanHandleArray(value["pSemaphores"], VK_OBJECT_TYPE_SEMAPHORE, ctx.Length(value["semaphoreCount"]));
    ctx.UInt64Array(value["pValues"], ctx.Length(value["semaphoreCount"]));
}

template <> void StructFromApiDump<VkSemaphoreSignalInfo>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.VulkanHandleValue(value["semaphore"], VK_OBJECT_TYPE_SEMAPHORE);
    ctx.UInt64Value(value["value"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceBufferDeviceAddressFeatures>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["bufferDeviceAddress"]);
    ctx.UInt32Value(value["bufferDeviceAddressCaptureReplay"]);
    ctx.UInt32Value(value["bufferDeviceAddressMultiDevice"]);
}

template <> void StructFromApiDump<VkBufferDeviceAddressInfo>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.VulkanHandleValue(value["buffer"], VK_OBJECT_TYPE_BUFFER);
}

template <> void StructFromApiDump<VkBufferOpaqueCaptureAddressCreateInfo>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt64Value(value["opaqueCaptureAddress"]);
}

template <> void StructFromApiDump<VkMemoryOpaqueCaptureAddressAllocateInfo>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt64Value(value["opaqueCaptureAddress"]);
}

template <> void StructFromApiDump<VkDeviceMemoryOpaqueCaptureAddressInfo>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.VulkanHandleValue(value["memory"], VK_OBJECT_TYPE_DEVICE_MEMORY);
}

template <> void StructFromApiDump<VkPhysicalDevice8BitStorageFeatures>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["storageBuffer8BitAccess"]);
    ctx.UInt32Value(value["uniformAndStorageBuffer8BitAccess"]);
    ctx.UInt32Value(value["storagePushConstant8"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceShaderAtomicInt64Features>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["shaderBufferInt64Atomics"]);
    ctx.UInt32Value(value["shaderSharedInt64Atomics"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceShaderFloat16Int8Features>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["shaderFloat16"]);
    ctx.UInt32Value(value["shaderInt8"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceFloatControlsProperties>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.EnumValue(value["denormBehaviorIndependence"], EnumFromString_VkShaderFloatControlsIndependence);
    ctx.EnumValue(value["roundingModeIndependence"], EnumFromString_VkShaderFloatControlsIndependence);
    ctx.UInt32Value(value["shaderSignedZeroInfNanPreserveFloat16"]);
    ctx.UInt32Value(value["shaderSignedZeroInfNanPreserveFloat32"]);
    ctx.UInt32Value(value["shaderSignedZeroInfNanPreserveFloat64"]);
    ctx.UInt32Value(value["shaderDenormPreserveFloat16"]);
    ctx.UInt32Value(value["shaderDenormPreserveFloat32"]);
    ctx.UInt32Value(value["shaderDenormPreserveFloat64"]);
    ctx.UInt32Value(value["shaderDenormFlushToZeroFloat16"]);
    ctx.UInt32Value(value["shaderDenormFlushToZeroFloat32"]);
    ctx.UInt32Value(value["shaderDenormFlushToZeroFloat64"]);
    ctx.UInt32Value(value["shaderRoundingModeRTEFloat16"]);
    ctx.UInt32Value(value["shaderRoundingModeRTEFloat32"]);
    ctx.UInt32Value(value["shaderRoundingModeRTEFloat64"]);
    ctx.UInt32Value(value["shaderRoundingModeRTZFloat16"]);
    ctx.UInt32Value(value["shaderRoundingModeRTZFloat32"]);
    ctx.UInt32Value(value["shaderRoundingModeRTZFloat64"]);
}

template <> void StructFromApiDump<VkDescriptorSetLayoutBindingFlagsCreateInfo>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["bindingCount"]);
    ctx.FlagsArray(value["pBindingFlags"], EnumFromString_VkDescriptorBindingFlagBits, ctx.Length(value["bindingCount"]));
}

template <> void StructFromApiDump<VkPhysicalDeviceDescriptorIndexingFeatures>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["shaderInputAttachmentArrayDynamicIndexing"]);
    ctx.UInt32Value(value["shaderUniformTexelBufferArrayDynamicIndexing"]);
    ctx.UInt32Value(value["shaderStorageTexelBufferArrayDynamicIndexing"]);
    ctx.UInt32Value(value["shaderUniformBufferArrayNonUniformIndexing"]);
    ctx.UInt32Value(value["shaderSampledImageArrayNonUniformIndexing"]);
    ctx.UInt32Value(value["shaderStorageBufferArrayNonUniformIndexing"]);
    ctx.UInt32Value(value["shaderStorageImageArrayNonUniformIndexing"]);
    ctx.UInt32Value(value["shaderInputAttachmentArrayNonUniformIndexing"]);
    ctx.UInt32Value(value["shaderUniformTexelBufferArrayNonUniformIndexing"]);
    ctx.UInt32Value(value["shaderStorageTexelBufferArrayNonUniformIndexing"]);
    ctx.UInt32Value(value["descriptorBindingUniformBufferUpdateAfterBind"]);
    ctx.UInt32Value(value["descriptorBindingSampledImageUpdateAfterBind"]);
    ctx.UInt32Value(value["descriptorBindingStorageImageUpdateAfterBind"]);
    ctx.UInt32Value(value["descriptorBindingStorageBufferUpdateAfterBind"]);
    ctx.UInt32Value(value["descriptorBindingUniformTexelBufferUpdateAfterBind"]);
    ctx.UInt32Value(value["descriptorBindingStorageTexelBufferUpdateAfterBind"]);
    ctx.UInt32Value(value["descriptorBindingUpdateUnusedWhilePending"]);
    ctx.UInt32Value(value["descriptorBindingPartiallyBound"]);
    ctx.UInt32Value(value["descriptorBindingVariableDescriptorCount"]);
    ctx.UInt32Value(value["runtimeDescriptorArray"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceDescriptorIndexingProperties>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["maxUpdateAfterBindDescriptorsInAllPools"]);
    ctx.UInt32Value(value["shaderUniformBufferArrayNonUniformIndexingNative"]);
    ctx.UInt32Value(value["shaderSampledImageArrayNonUniformIndexingNative"]);
    ctx.UInt32Value(value["shaderStorageBufferArrayNonUniformIndexingNative"]);
    ctx.UInt32Value(value["shaderStorageImageArrayNonUniformIndexingNative"]);
    ctx.UInt32Value(value["shaderInputAttachmentArrayNonUniformIndexingNative"]);
    ctx.UInt32Value(value["robustBufferAccessUpdateAfterBind"]);
    ctx.UInt32Value(value["quadDivergentImplicitLod"]);
    ctx.UInt32Value(value["maxPerStageDescriptorUpdateAfterBindSamplers"]);
    ctx.UInt32Value(value["maxPerStageDescriptorUpdateAfterBindUniformBuffers"]);
    ctx.UInt32Value(value["maxPerStageDescriptorUpdateAfterBindStorageBuffers"]);
    ctx.UInt32Value(value["maxPerStageDescriptorUpdateAfterBindSampledImages"]);
    ctx.UInt32Value(value["maxPerStageDescriptorUpdateAfterBindStorageImages"]);
    ctx.UInt32Value(value["maxPerStageDescriptorUpdateAfterBindInputAttachments"]);
    ctx.UInt32Value(value["maxPerStageUpdateAfterBindResources"]);
    ctx.UInt32Value(value["maxDescriptorSetUpdateAfterBindSamplers"]);
    ctx.UInt32Value(value["maxDescriptorSetUpdateAfterBindUniformBuffers"]);
    ctx.UInt32Value(value["maxDescriptorSetUpdateAfterBindUniformBuffersDynamic"]);
    ctx.UInt32Value(value["maxDescriptorSetUpdateAfterBindStorageBuffers"]);
    ctx.UInt32Value(value["maxDescriptorSetUpdateAfterBindStorageBuffersDynamic"]);
    ctx.UInt32Value(value["maxDescriptorSetUpdateAfterBindSampledImages"]);
    ctx.UInt32Value(value["maxDescriptorSetUpdateAfterBindStorageImages"]);
    ctx.UInt32Value(value["maxDescriptorSetUpdateAfterBindInputAttachments"]);
}

template <> void StructFromApiDump<VkDescriptorSetVariableDescriptorCountAllocateInfo>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["descriptorSetCount"]);
    ctx.UInt32Array(value["pDescriptorCounts"], ctx.Length(value["descriptorSetCount"]));
}

template <> void StructFromApiDump<VkDescriptorSetVariableDescriptorCountLayoutSupport>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["maxVariableDescriptorCount"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceScalarBlockLayoutFeatures>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["scalarBlockLayout"]);
}

template <> void StructFromApiDump<VkSamplerReductionModeCreateInfo>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.EnumValue(value["reductionMode"], EnumFromString_VkSamplerReductionMode);
}

template <> void StructFromApiDump<VkPhysicalDeviceSamplerFilterMinmaxProperties>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["filterMinmaxSingleComponentFormats"]);
    ctx.UInt32Value(value["filterMinmaxImageComponentMapping"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceUniformBufferStandardLayoutFeatures>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["uniformBufferStandardLayout"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceShaderSubgroupExtendedTypesFeatures>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["shaderSubgroupExtendedTypes"]);
}

template <> void StructFromApiDump<VkAttachmentDescription2>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.FlagsValue(value["flags"], EnumFromString_VkAttachmentDescriptionFlagBits);
    ctx.EnumValue(value["format"], EnumFromString_VkFormat);
    ctx.EnumValue(value["samples"], EnumFromString_VkSampleCountFlagBits);
    ctx.EnumValue(value["loadOp"], EnumFromString_VkAttachmentLoadOp);
    ctx.EnumValue(value["storeOp"], EnumFromString_VkAttachmentStoreOp);
    ctx.EnumValue(value["stencilLoadOp"], EnumFromString_VkAttachmentLoadOp);
    ctx.EnumValue(value["stencilStoreOp"], EnumFromString_VkAttachmentStoreOp);
    ctx.EnumValue(value["initialLayout"], EnumFromString_VkImageLayout);
    ctx.EnumValue(value["finalLayout"], EnumFromString_VkImageLayout);
}

template <> void StructFromApiDump<VkAttachmentReference2>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["attachment"]);
    ctx.EnumValue(value["layout"], EnumFromString_VkImageLayout);
    ctx.FlagsValue(value["aspectMask"], EnumFromString_VkImageAspectFlagBits);
}

template <> void StructFromApiDump<VkSubpassDescription2>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.FlagsValue(value["flags"], EnumFromString_VkSubpassDescriptionFlagBits);
    ctx.EnumValue(value["pipelineBindPoint"], EnumFromString_VkPipelineBindPoint);
    ctx.UInt32Value(value["viewMask"]);
    ctx.UInt32Value(value["inputAttachmentCount"]);
    StructArrayFromApiDump<VkAttachmentReference2>(ctx, value["pInputAttachments"], ctx.Length(value["inputAttachmentCount"]));
    ctx.UInt32Value(value["colorAttachmentCount"]);
    StructArrayFromApiDump<VkAttachmentReference2>(ctx, value["pColorAttachments"], ctx.Length(value["colorAttachmentCount"]));
    StructArrayFromApiDump<VkAttachmentReference2>(ctx, value["pResolveAttachments"], ctx.Length(value["colorAttachmentCount"]));
    StructPtrFromApiDump<VkAttachmentReference2>(ctx, value["pDepthStencilAttachment"]);
    ctx.UInt32Value(value["preserveAttachmentCount"]);
    ctx.UInt32Array(value["pPreserveAttachments"], ctx.Length(value["preserveAttachmentCount"]));
}

template <> void StructFromApiDump<VkSubpassDependency2>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["srcSubpass"]);
    ctx.UInt32Value(value["dstSubpass"]);
    ctx.FlagsValue(value["srcStageMask"], EnumFromString_VkPipelineStageFlagBits);
    ctx.FlagsValue(value["dstStageMask"], EnumFromString_VkPipelineStageFlagBits);
    ctx.FlagsValue(value["srcAccessMask"], EnumFromString_VkAccessFlagBits);
    ctx.FlagsValue(value["dstAccessMask"], EnumFromString_VkAccessFlagBits);
    ctx.FlagsValue(value["dependencyFlags"], EnumFromString_VkDependencyFlagBits);
    ctx.Int32Value(value["viewOffset"]);
}

template <> void StructFromApiDump<VkSubpassBeginInfo>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.EnumValue(value["contents"], EnumFromString_VkSubpassContents);
}

template <> void StructFromApiDump<VkSubpassEndInfo>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
}

template <> void StructFromApiDump<VkRenderPassCreateInfo2>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.FlagsValue(value["flags"], EnumFromString_VkRenderPassCreateFlagBits);
    ctx.UInt32Value(value["attachmentCount"]);
    StructArrayFromApiDump<VkAttachmentDescription2>(ctx, value["pAttachments"], ctx.Length(value["attachmentCount"]));
    ctx.UInt32Value(value["subpassCount"]);
    StructArrayFromApiDump<VkSubpassDescription2>(ctx, value["pSubpasses"], ctx.Length(value["subpassCount"]));
    ctx.UInt32Value(value["dependencyCount"]);
    StructArrayFromApiDump<VkSubpassDependency2>(ctx, value["pDependencies"], ctx.Length(value["dependencyCount"]));
    ctx.UInt32Value(value["correlatedViewMaskCount"]);
    ctx.UInt32Array(value["pCorrelatedViewMasks"], ctx.Length(value["correlatedViewMaskCount"]));
}

template <> void StructFromApiDump<VkSubpassDescriptionDepthStencilResolve>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.EnumValue(value["depthResolveMode"], EnumFromString_VkResolveModeFlagBits);
    ctx.EnumValue(value["stencilResolveMode"], EnumFromString_VkResolveModeFlagBits);
    StructPtrFromApiDump<VkAttachmentReference2>(ctx, value["pDepthStencilResolveAttachment"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceDepthStencilResolveProperties>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.FlagsValue(value["supportedDepthResolveModes"], EnumFromString_VkResolveModeFlagBits);
    ctx.FlagsValue(value["supportedStencilResolveModes"], EnumFromString_VkResolveModeFlagBits);
    ctx.UInt32Value(value["independentResolveNone"]);
    ctx.UInt32Value(value["independentResolve"]);
}

template <> void StructFromApiDump<VkImageStencilUsageCreateInfo>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.FlagsValue(value["stencilUsage"], EnumFromString_VkImageUsageFlagBits);
}

template <> void StructFromApiDump<VkPhysicalDeviceImagelessFramebufferFeatures>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["imagelessFramebuffer"]);
}

template <> void StructFromApiDump<VkFramebufferAttachmentImageInfo>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.FlagsValue(value["flags"], EnumFromString_VkImageCreateFlagBits);
    ctx.FlagsValue(value["usage"], EnumFromString_VkImageUsageFlagBits);
    ctx.UInt32Value(value["width"]);
    ctx.UInt32Value(value["height"]);
    ctx.UInt32Value(value["layerCount"]);
    ctx.UInt32Value(value["viewFormatCount"]);
    ctx.EnumArray(value["pViewFormats"], EnumFromString_VkFormat, ctx.Length(value["viewFormatCount"]));
}

template <> void StructFromApiDump<VkRenderPassAttachmentBeginInfo>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["attachmentCount"]);
    ctx.VulkanHandleArray(value["pAttachments"], VK_OBJECT_TYPE_IMAGE_VIEW, ctx.Length(value["attachmentCount"]));
}

template <> void StructFromApiDump<VkFramebufferAttachmentsCreateInfo>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["attachmentImageInfoCount"]);
    StructArrayFromApiDump<VkFramebufferAttachmentImageInfo>(ctx, value["pAttachmentImageInfos"], ctx.Length(value["attachmentImageInfoCount"]));
}

template <> void StructFromApiDump<VkPhysicalDeviceSeparateDepthStencilLayoutsFeatures>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["separateDepthStencilLayouts"]);
}

template <> void StructFromApiDump<VkAttachmentReferenceStencilLayout>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.EnumValue(value["stencilLayout"], EnumFromString_VkImageLayout);
}

template <> void StructFromApiDump<VkAttachmentDescriptionStencilLayout>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.EnumValue(value["stencilInitialLayout"], EnumFromString_VkImageLayout);
    ctx.EnumValue(value["stencilFinalLayout"], EnumFromString_VkImageLayout);
}

template <> void StructFromApiDump<VkPhysicalDeviceVulkan13Features>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["robustImageAccess"]);
    ctx.UInt32Value(value["inlineUniformBlock"]);
    ctx.UInt32Value(value["descriptorBindingInlineUniformBlockUpdateAfterBind"]);
    ctx.UInt32Value(value["pipelineCreationCacheControl"]);
    ctx.UInt32Value(value["privateData"]);
    ctx.UInt32Value(value["shaderDemoteToHelperInvocation"]);
    ctx.UInt32Value(value["shaderTerminateInvocation"]);
    ctx.UInt32Value(value["subgroupSizeControl"]);
    ctx.UInt32Value(value["computeFullSubgroups"]);
    ctx.UInt32Value(value["synchronization2"]);
    ctx.UInt32Value(value["textureCompressionASTC_HDR"]);
    ctx.UInt32Value(value["shaderZeroInitializeWorkgroupMemory"]);
    ctx.UInt32Value(value["dynamicRendering"]);
    ctx.UInt32Value(value["shaderIntegerDotProduct"]);
    ctx.UInt32Value(value["maintenance4"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceVulkan13Properties>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["minSubgroupSize"]);
    ctx.UInt32Value(value["maxSubgroupSize"]);
    ctx.UInt32Value(value["maxComputeWorkgroupSubgroups"]);
    ctx.FlagsValue(value["requiredSubgroupSizeStages"], EnumFromString_VkShaderStageFlagBits);
    ctx.UInt32Value(value["maxInlineUniformBlockSize"]);
    ctx.UInt32Value(value["maxPerStageDescriptorInlineUniformBlocks"]);
    ctx.UInt32Value(value["maxPerStageDescriptorUpdateAfterBindInlineUniformBlocks"]);
    ctx.UInt32Value(value["maxDescriptorSetInlineUniformBlocks"]);
    ctx.UInt32Value(value["maxDescriptorSetUpdateAfterBindInlineUniformBlocks"]);
    ctx.UInt32Value(value["maxInlineUniformTotalSize"]);
    ctx.UInt32Value(value["integerDotProduct8BitUnsignedAccelerated"]);
    ctx.UInt32Value(value["integerDotProduct8BitSignedAccelerated"]);
    ctx.UInt32Value(value["integerDotProduct8BitMixedSignednessAccelerated"]);
    ctx.UInt32Value(value["integerDotProduct4x8BitPackedUnsignedAccelerated"]);
    ctx.UInt32Value(value["integerDotProduct4x8BitPackedSignedAccelerated"]);
    ctx.UInt32Value(value["integerDotProduct4x8BitPackedMixedSignednessAccelerated"]);
    ctx.UInt32Value(value["integerDotProduct16BitUnsignedAccelerated"]);
    ctx.UInt32Value(value["integerDotProduct16BitSignedAccelerated"]);
    ctx.UInt32Value(value["integerDotProduct16BitMixedSignednessAccelerated"]);
    ctx.UInt32Value(value["integerDotProduct32BitUnsignedAccelerated"]);
    ctx.UInt32Value(value["integerDotProduct32BitSignedAccelerated"]);
    ctx.UInt32Value(value["integerDotProduct32BitMixedSignednessAccelerated"]);
    ctx.UInt32Value(value["integerDotProduct64BitUnsignedAccelerated"]);
    ctx.UInt32Value(value["integerDotProduct64BitSignedAccelerated"]);
    ctx.UInt32Value(value["integerDotProduct64BitMixedSignednessAccelerated"]);
    ctx.UInt32Value(value["integerDotProductAccumulatingSaturating8BitUnsignedAccelerated"]);
    ctx.UInt32Value(value["integerDotProductAccumulatingSaturating8BitSignedAccelerated"]);
    ctx.UInt32Value(value["integerDotProductAccumulatingSaturating8BitMixedSignednessAccelerated"]);
    ctx.UInt32Value(value["integerDotProductAccumulatingSaturating4x8BitPackedUnsignedAccelerated"]);
    ctx.UInt32Value(value["integerDotProductAccumulatingSaturating4x8BitPackedSignedAccelerated"]);
    ctx.UInt32Value(value["integerDotProductAccumulatingSaturating4x8BitPackedMixedSignednessAccelerated"]);
    ctx.UInt32Value(value["integerDotProductAccumulatingSaturating16BitUnsignedAccelerated"]);
    ctx.UInt32Value(value["integerDotProductAccumulatingSaturating16BitSignedAccelerated"]);
    ctx.UInt32Value(value["integerDotProductAccumulatingSaturating16BitMixedSignednessAccelerated"]);
    ctx.UInt32Value(value["integerDotProductAccumulatingSaturating32BitUnsignedAccelerated"]);
    ctx.UInt32Value(value["integerDotProductAccumulatingSaturating32BitSignedAccelerated"]);
    ctx.UInt32Value(value["integerDotProductAccumulatingSaturating32BitMixedSignednessAccelerated"]);
    ctx.UInt32Value(value["integerDotProductAccumulatingSaturating64BitUnsignedAccelerated"]);
    ctx.UInt32Value(value["integerDotProductAccumulatingSaturating64BitSignedAccelerated"]);
    ctx.UInt32Value(value["integerDotProductAccumulatingSaturating64BitMixedSignednessAccelerated"]);
    ctx.UInt64Value(value["storageTexelBufferOffsetAlignmentBytes"]);
    ctx.UInt32Value(value["storageTexelBufferOffsetSingleTexelAlignment"]);
    ctx.UInt64Value(value["uniformTexelBufferOffsetAlignmentBytes"]);
    ctx.UInt32Value(value["uniformTexelBufferOffsetSingleTexelAlignment"]);
    ctx.UInt64Value(value["maxBufferSize"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceToolProperties>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.StringValue(value["name"]);
    ctx.StringValue(value["version"]);
    ctx.FlagsValue(value["purposes"], EnumFromString_VkToolPurposeFlagBits);
    ctx.StringValue(value["description"]);
    ctx.StringValue(value["layer"]);
}

template <> void StructFromApiDump<VkPhysicalDevicePrivateDataFeatures>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["privateData"]);
}

template <> void StructFromApiDump<VkDevicePrivateDataCreateInfo>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["privateDataSlotRequestCount"]);
}

template <> void StructFromApiDump<VkPrivateDataSlotCreateInfo>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.FlagsValue(value["flags"], EnumFromString_VkPrivateDataSlotCreateFlagBits);
}

template <> void StructFromApiDump<VkMemoryBarrier2>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.Flags64Value(value["srcStageMask"], EnumFromString_VkPipelineStageFlagBits2);
    ctx.Flags64Value(value["srcAccessMask"], EnumFromString_VkAccessFlagBits2);
    ctx.Flags64Value(value["dstStageMask"], EnumFromString_VkPipelineStageFlagBits2);
    ctx.Flags64Value(value["dstAccessMask"], EnumFromString_VkAccessFlagBits2);
}

template <> void StructFromApiDump<VkBufferMemoryBarrier2>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.Flags64Value(value["srcStageMask"], EnumFromString_VkPipelineStageFlagBits2);
    ctx.Flags64Value(value["srcAccessMask"], EnumFromString_VkAccessFlagBits2);
    ctx.Flags64Value(value["dstStageMask"], EnumFromString_VkPipelineStageFlagBits2);
    ctx.Flags64Value(value["dstAccessMask"], EnumFromString_VkAccessFlagBits2);
    ctx.UInt32Value(value["srcQueueFamilyIndex"]);
    ctx.UInt32Value(value["dstQueueFamilyIndex"]);
    ctx.VulkanHandleValue(value["buffer"], VK_OBJECT_TYPE_BUFFER);
    ctx.UInt64Value(value["offset"]);
    ctx.UInt64Value(value["size"]);
}

template <> void StructFromApiDump<VkImageMemoryBarrier2>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.Flags64Value(value["srcStageMask"], EnumFromString_VkPipelineStageFlagBits2);
    ctx.Flags64Value(value["srcAccessMask"], EnumFromString_VkAccessFlagBits2);
    ctx.Flags64Value(value["dstStageMask"], EnumFromString_VkPipelineStageFlagBits2);
    ctx.Flags64Value(value["dstAccessMask"], EnumFromString_VkAccessFlagBits2);
    ctx.EnumValue(value["oldLayout"], EnumFromString_VkImageLayout);
    ctx.EnumValue(value["newLayout"], EnumFromString_VkImageLayout);
    ctx.UInt32Value(value["srcQueueFamilyIndex"]);
    ctx.UInt32Value(value["dstQueueFamilyIndex"]);
    ctx.VulkanHandleValue(value["image"], VK_OBJECT_TYPE_IMAGE);
    StructFromApiDump<VkImageSubresourceRange>(ctx, value["subresourceRange"]);
}

template <> void StructFromApiDump<VkDependencyInfo>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.FlagsValue(value["dependencyFlags"], EnumFromString_VkDependencyFlagBits);
    ctx.UInt32Value(value["memoryBarrierCount"]);
    StructArrayFromApiDump<VkMemoryBarrier2>(ctx, value["pMemoryBarriers"], ctx.Length(value["memoryBarrierCount"]));
    ctx.UInt32Value(value["bufferMemoryBarrierCount"]);
    StructArrayFromApiDump<VkBufferMemoryBarrier2>(ctx, value["pBufferMemoryBarriers"], ctx.Length(value["bufferMemoryBarrierCount"]));
    ctx.UInt32Value(value["imageMemoryBarrierCount"]);
    StructArrayFromApiDump<VkImageMemoryBarrier2>(ctx, value["pImageMemoryBarriers"], ctx.Length(value["imageMemoryBarrierCount"]));
}

template <> void StructFromApiDump<VkSemaphoreSubmitInfo>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.VulkanHandleValue(value["semaphore"], VK_OBJECT_TYPE_SEMAPHORE);
    ctx.UInt64Value(value["value"]);
    ctx.Flags64Value(value["stageMask"], EnumFromString_VkPipelineStageFlagBits2);
    ctx.UInt32Value(value["deviceIndex"]);
}

template <> void StructFromApiDump<VkCommandBufferSubmitInfo>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.VulkanHandleValue(value["commandBuffer"], VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.UInt32Value(value["deviceMask"]);
}

template <> void StructFromApiDump<VkSubmitInfo2>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.FlagsValue(value["flags"], EnumFromString_VkSubmitFlagBits);
    ctx.UInt32Value(value["waitSemaphoreInfoCount"]);
    StructArrayFromApiDump<VkSemaphoreSubmitInfo>(ctx, value["pWaitSemaphoreInfos"], ctx.Length(value["waitSemaphoreInfoCount"]));
    ctx.UInt32Value(value["commandBufferInfoCount"]);
    StructArrayFromApiDump<VkCommandBufferSubmitInfo>(ctx, value["pCommandBufferInfos"], ctx.Length(value["commandBufferInfoCount"]));
    ctx.UInt32Value(value["signalSemaphoreInfoCount"]);
    StructArrayFromApiDump<VkSemaphoreSubmitInfo>(ctx, value["pSignalSemaphoreInfos"], ctx.Length(value["signalSemaphoreInfoCount"]));
}

template <> void StructFromApiDump<VkPhysicalDeviceSynchronization2Features>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["synchronization2"]);
}

template <> void StructFromApiDump<VkBufferCopy2>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt64Value(value["srcOffset"]);
    ctx.UInt64Value(value["dstOffset"]);
    ctx.UInt64Value(value["size"]);
}

template <> void StructFromApiDump<VkCopyBufferInfo2>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.VulkanHandleValue(value["srcBuffer"], VK_OBJECT_TYPE_BUFFER);
    ctx.VulkanHandleValue(value["dstBuffer"], VK_OBJECT_TYPE_BUFFER);
    ctx.UInt32Value(value["regionCount"]);
    StructArrayFromApiDump<VkBufferCopy2>(ctx, value["pRegions"], ctx.Length(value["regionCount"]));
}

template <> void StructFromApiDump<VkImageCopy2>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    StructFromApiDump<VkImageSubresourceLayers>(ctx, value["srcSubresource"]);
    StructFromApiDump<VkOffset3D>(ctx, value["srcOffset"]);
    StructFromApiDump<VkImageSubresourceLayers>(ctx, value["dstSubresource"]);
    StructFromApiDump<VkOffset3D>(ctx, value["dstOffset"]);
    StructFromApiDump<VkExtent3D>(ctx, value["extent"]);
}

template <> void StructFromApiDump<VkCopyImageInfo2>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.VulkanHandleValue(value["srcImage"], VK_OBJECT_TYPE_IMAGE);
    ctx.EnumValue(value["srcImageLayout"], EnumFromString_VkImageLayout);
    ctx.VulkanHandleValue(value["dstImage"], VK_OBJECT_TYPE_IMAGE);
    ctx.EnumValue(value["dstImageLayout"], EnumFromString_VkImageLayout);
    ctx.UInt32Value(value["regionCount"]);
    StructArrayFromApiDump<VkImageCopy2>(ctx, value["pRegions"], ctx.Length(value["regionCount"]));
}

template <> void StructFromApiDump<VkBufferImageCopy2>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt64Value(value["bufferOffset"]);
    ctx.UInt32Value(value["bufferRowLength"]);
    ctx.UInt32Value(value["bufferImageHeight"]);
    StructFromApiDump<VkImageSubresourceLayers>(ctx, value["imageSubresource"]);
    StructFromApiDump<VkOffset3D>(ctx, value["imageOffset"]);
    StructFromApiDump<VkExtent3D>(ctx, value["imageExtent"]);
}

template <> void StructFromApiDump<VkCopyBufferToImageInfo2>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.VulkanHandleValue(value["srcBuffer"], VK_OBJECT_TYPE_BUFFER);
    ctx.VulkanHandleValue(value["dstImage"], VK_OBJECT_TYPE_IMAGE);
    ctx.EnumValue(value["dstImageLayout"], EnumFromString_VkImageLayout);
    ctx.UInt32Value(value["regionCount"]);
    StructArrayFromApiDump<VkBufferImageCopy2>(ctx, value["pRegions"], ctx.Length(value["regionCount"]));
}

template <> void StructFromApiDump<VkCopyImageToBufferInfo2>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.VulkanHandleValue(value["srcImage"], VK_OBJECT_TYPE_IMAGE);
    ctx.EnumValue(value["srcImageLayout"], EnumFromString_VkImageLayout);
    ctx.VulkanHandleValue(value["dstBuffer"], VK_OBJECT_TYPE_BUFFER);
    ctx.UInt32Value(value["regionCount"]);
    StructArrayFromApiDump<VkBufferImageCopy2>(ctx, value["pRegions"], ctx.Length(value["regionCount"]));
}

template <> void StructFromApiDump<VkPhysicalDeviceTextureCompressionASTCHDRFeatures>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["textureCompressionASTC_HDR"]);
}

template <> void StructFromApiDump<VkFormatProperties3>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.Flags64Value(value["linearTilingFeatures"], EnumFromString_VkFormatFeatureFlagBits2);
    ctx.Flags64Value(value["optimalTilingFeatures"], EnumFromString_VkFormatFeatureFlagBits2);
    ctx.Flags64Value(value["bufferFeatures"], EnumFromString_VkFormatFeatureFlagBits2);
}

template <> void StructFromApiDump<VkPhysicalDeviceMaintenance4Features>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["maintenance4"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceMaintenance4Properties>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt64Value(value["maxBufferSize"]);
}

template <> void StructFromApiDump<VkDeviceBufferMemoryRequirements>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    StructPtrFromApiDump<VkBufferCreateInfo>(ctx, value["pCreateInfo"]);
}

template <> void StructFromApiDump<VkDeviceImageMemoryRequirements>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    StructPtrFromApiDump<VkImageCreateInfo>(ctx, value["pCreateInfo"]);
    ctx.EnumValue(value["planeAspect"], EnumFromString_VkImageAspectFlagBits);
}

template <> void StructFromApiDump<VkPipelineCreationFeedback>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.FlagsValue(value["flags"], EnumFromString_VkPipelineCreationFeedbackFlagBits);
    ctx.UInt64Value(value["duration"]);
}

template <> void StructFromApiDump<VkPipelineCreationFeedbackCreateInfo>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    StructPtrFromApiDump<VkPipelineCreationFeedback>(ctx, value["pPipelineCreationFeedback"]);
    ctx.UInt32Value(value["pipelineStageCreationFeedbackCount"]);
    StructArrayFromApiDump<VkPipelineCreationFeedback>(ctx, value["pPipelineStageCreationFeedbacks"], ctx.Length(value["pipelineStageCreationFeedbackCount"]));
}

template <> void StructFromApiDump<VkPhysicalDeviceShaderTerminateInvocationFeatures>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["shaderTerminateInvocation"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceShaderDemoteToHelperInvocationFeatures>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["shaderDemoteToHelperInvocation"]);
}

template <> void StructFromApiDump<VkPhysicalDevicePipelineCreationCacheControlFeatures>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["pipelineCreationCacheControl"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceZeroInitializeWorkgroupMemoryFeatures>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["shaderZeroInitializeWorkgroupMemory"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceImageRobustnessFeatures>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["robustImageAccess"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceSubgroupSizeControlFeatures>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["subgroupSizeControl"]);
    ctx.UInt32Value(value["computeFullSubgroups"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceSubgroupSizeControlProperties>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["minSubgroupSize"]);
    ctx.UInt32Value(value["maxSubgroupSize"]);
    ctx.UInt32Value(value["maxComputeWorkgroupSubgroups"]);
    ctx.FlagsValue(value["requiredSubgroupSizeStages"], EnumFromString_VkShaderStageFlagBits);
}

template <> void StructFromApiDump<VkPipelineShaderStageRequiredSubgroupSizeCreateInfo>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["requiredSubgroupSize"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceInlineUniformBlockFeatures>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["inlineUniformBlock"]);
    ctx.UInt32Value(value["descriptorBindingInlineUniformBlockUpdateAfterBind"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceInlineUniformBlockProperties>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["maxInlineUniformBlockSize"]);
    ctx.UInt32Value(value["maxPerStageDescriptorInlineUniformBlocks"]);
    ctx.UInt32Value(value["maxPerStageDescriptorUpdateAfterBindInlineUniformBlocks"]);
    ctx.UInt32Value(value["maxDescriptorSetInlineUniformBlocks"]);
    ctx.UInt32Value(value["maxDescriptorSetUpdateAfterBindInlineUniformBlocks"]);
}

template <> void StructFromApiDump<VkWriteDescriptorSetInlineUniformBlock>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["dataSize"]);
    ctx.UInt8Array(value["pData"], ctx.Length(value["dataSize"]));
}

template <> void StructFromApiDump<VkDescriptorPoolInlineUniformBlockCreateInfo>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["maxInlineUniformBlockBindings"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceShaderIntegerDotProductFeatures>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["shaderIntegerDotProduct"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceShaderIntegerDotProductProperties>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["integerDotProduct8BitUnsignedAccelerated"]);
    ctx.UInt32Value(value["integerDotProduct8BitSignedAccelerated"]);
    ctx.UInt32Value(value["integerDotProduct8BitMixedSignednessAccelerated"]);
    ctx.UInt32Value(value["integerDotProduct4x8BitPackedUnsignedAccelerated"]);
    ctx.UInt32Value(value["integerDotProduct4x8BitPackedSignedAccelerated"]);
    ctx.UInt32Value(value["integerDotProduct4x8BitPackedMixedSignednessAccelerated"]);
    ctx.UInt32Value(value["integerDotProduct16BitUnsignedAccelerated"]);
    ctx.UInt32Value(value["integerDotProduct16BitSignedAccelerated"]);
    ctx.UInt32Value(value["integerDotProduct16BitMixedSignednessAccelerated"]);
    ctx.UInt32Value(value["integerDotProduct32BitUnsignedAccelerated"]);
    ctx.UInt32Value(value["integerDotProduct32BitSignedAccelerated"]);
    ctx.UInt32Value(value["integerDotProduct32BitMixedSignednessAccelerated"]);
    ctx.UInt32Value(value["integerDotProduct64BitUnsignedAccelerated"]);
    ctx.UInt32Value(value["integerDotProduct64BitSignedAccelerated"]);
    ctx.UInt32Value(value["integerDotProduct64BitMixedSignednessAccelerated"]);
    ctx.UInt32Value(value["integerDotProductAccumulatingSaturating8BitUnsignedAccelerated"]);
    ctx.UInt32Value(value["integerDotProductAccumulatingSaturating8BitSignedAccelerated"]);
    ctx.UInt32Value(value["integerDotProductAccumulatingSaturating8BitMixedSignednessAccelerated"]);
    ctx.UInt32Value(value["integerDotProductAccumulatingSaturating4x8BitPackedUnsignedAccelerated"]);
    ctx.UInt32Value(value["integerDotProductAccumulatingSaturating4x8BitPackedSignedAccelerated"]);
    ctx.UInt32Value(value["integerDotProductAccumulatingSaturating4x8BitPackedMixedSignednessAccelerated"]);
    ctx.UInt32Value(value["integerDotProductAccumulatingSaturating16BitUnsignedAccelerated"]);
    ctx.UInt32Value(value["integerDotProductAccumulatingSaturating16BitSignedAccelerated"]);
    ctx.UInt32Value(value["integerDotProductAccumulatingSaturating16BitMixedSignednessAccelerated"]);
    ctx.UInt32Value(value["integerDotProductAccumulatingSaturating32BitUnsignedAccelerated"]);
    ctx.UInt32Value(value["integerDotProductAccumulatingSaturating32BitSignedAccelerated"]);
    ctx.UInt32Value(value["integerDotProductAccumulatingSaturating32BitMixedSignednessAccelerated"]);
    ctx.UInt32Value(value["integerDotProductAccumulatingSaturating64BitUnsignedAccelerated"]);
    ctx.UInt32Value(value["integerDotProductAccumulatingSaturating64BitSignedAccelerated"]);
    ctx.UInt32Value(value["integerDotProductAccumulatingSaturating64BitMixedSignednessAccelerated"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceTexelBufferAlignmentProperties>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt64Value(value["storageTexelBufferOffsetAlignmentBytes"]);
    ctx.UInt32Value(value["storageTexelBufferOffsetSingleTexelAlignment"]);
    ctx.UInt64Value(value["uniformTexelBufferOffsetAlignmentBytes"]);
    ctx.UInt32Value(value["uniformTexelBufferOffsetSingleTexelAlignment"]);
}

template <> void StructFromApiDump<VkImageBlit2>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    StructFromApiDump<VkImageSubresourceLayers>(ctx, value["srcSubresource"]);
    StructArrayFromApiDump<VkOffset3D>(ctx, value["srcOffsets"], 2);
    StructFromApiDump<VkImageSubresourceLayers>(ctx, value["dstSubresource"]);
    StructArrayFromApiDump<VkOffset3D>(ctx, value["dstOffsets"], 2);
}

template <> void StructFromApiDump<VkBlitImageInfo2>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.VulkanHandleValue(value["srcImage"], VK_OBJECT_TYPE_IMAGE);
    ctx.EnumValue(value["srcImageLayout"], EnumFromString_VkImageLayout);
    ctx.VulkanHandleValue(value["dstImage"], VK_OBJECT_TYPE_IMAGE);
    ctx.EnumValue(value["dstImageLayout"], EnumFromString_VkImageLayout);
    ctx.UInt32Value(value["regionCount"]);
    StructArrayFromApiDump<VkImageBlit2>(ctx, value["pRegions"], ctx.Length(value["regionCount"]));
    ctx.EnumValue(value["filter"], EnumFromString_VkFilter);
}

template <> void StructFromApiDump<VkImageResolve2>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    StructFromApiDump<VkImageSubresourceLayers>(ctx, value["srcSubresource"]);
    StructFromApiDump<VkOffset3D>(ctx, value["srcOffset"]);
    StructFromApiDump<VkImageSubresourceLayers>(ctx, value["dstSubresource"]);
    StructFromApiDump<VkOffset3D>(ctx, value["dstOffset"]);
    StructFromApiDump<VkExtent3D>(ctx, value["extent"]);
}

template <> void StructFromApiDump<VkResolveImageInfo2>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.VulkanHandleValue(value["srcImage"], VK_OBJECT_TYPE_IMAGE);
    ctx.EnumValue(value["srcImageLayout"], EnumFromString_VkImageLayout);
    ctx.VulkanHandleValue(value["dstImage"], VK_OBJECT_TYPE_IMAGE);
    ctx.EnumValue(value["dstImageLayout"], EnumFromString_VkImageLayout);
    ctx.UInt32Value(value["regionCount"]);
    StructArrayFromApiDump<VkImageResolve2>(ctx, value["pRegions"], ctx.Length(value["regionCount"]));
}

template <> void StructFromApiDump<VkRenderingAttachmentInfo>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.VulkanHandleValue(value["imageView"], VK_OBJECT_TYPE_IMAGE_VIEW);
    ctx.EnumValue(value["imageLayout"], EnumFromString_VkImageLayout);
    ctx.EnumValue(value["resolveMode"], EnumFromString_VkResolveModeFlagBits);
    ctx.VulkanHandleValue(value["resolveImageView"], VK_OBJECT_TYPE_IMAGE_VIEW);
    ctx.EnumValue(value["resolveImageLayout"], EnumFromString_VkImageLayout);
    ctx.EnumValue(value["loadOp"], EnumFromString_VkAttachmentLoadOp);
    ctx.EnumValue(value["storeOp"], EnumFromString_VkAttachmentStoreOp);
    StructFromApiDump<VkClearValue>(ctx, value["clearValue"]);
}

template <> void StructFromApiDump<VkRenderingInfo>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.FlagsValue(value["flags"], EnumFromString_VkRenderingFlagBits);
    StructFromApiDump<VkRect2D>(ctx, value["renderArea"]);
    ctx.UInt32Value(value["layerCount"]);
    ctx.UInt32Value(value["viewMask"]);
    ctx.UInt32Value(value["colorAttachmentCount"]);
    StructArrayFromApiDump<VkRenderingAttachmentInfo>(ctx, value["pColorAttachments"], ctx.Length(value["colorAttachmentCount"]));
    StructPtrFromApiDump<VkRenderingAttachmentInfo>(ctx, value["pDepthAttachment"]);
    StructPtrFromApiDump<VkRenderingAttachmentInfo>(ctx, value["pStencilAttachment"]);
}

template <> void StructFromApiDump<VkPipelineRenderingCreateInfo>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["viewMask"]);
    ctx.UInt32Value(value["colorAttachmentCount"]);
    ctx.EnumArray(value["pColorAttachmentFormats"], EnumFromString_VkFormat, ctx.Length(value["colorAttachmentCount"]));
    ctx.EnumValue(value["depthAttachmentFormat"], EnumFromString_VkFormat);
    ctx.EnumValue(value["stencilAttachmentFormat"], EnumFromString_VkFormat);
}

template <> void StructFromApiDump<VkPhysicalDeviceDynamicRenderingFeatures>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["dynamicRendering"]);
}

template <> void StructFromApiDump<VkCommandBufferInheritanceRenderingInfo>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.FlagsValue(value["flags"], EnumFromString_VkRenderingFlagBits);
    ctx.UInt32Value(value["viewMask"]);
    ctx.UInt32Value(value["colorAttachmentCount"]);
    ctx.EnumArray(value["pColorAttachmentFormats"], EnumFromString_VkFormat, ctx.Length(value["colorAttachmentCount"]));
    ctx.EnumValue(value["depthAttachmentFormat"], EnumFromString_VkFormat);
    ctx.EnumValue(value["stencilAttachmentFormat"], EnumFromString_VkFormat);
    ctx.EnumValue(value["rasterizationSamples"], EnumFromString_VkSampleCountFlagBits);
}

template <> void StructFromApiDump<VkPhysicalDeviceVulkan14Features>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["globalPriorityQuery"]);
    ctx.UInt32Value(value["shaderSubgroupRotate"]);
    ctx.UInt32Value(value["shaderSubgroupRotateClustered"]);
    ctx.UInt32Value(value["shaderFloatControls2"]);
    ctx.UInt32Value(value["shaderExpectAssume"]);
    ctx.UInt32Value(value["rectangularLines"]);
    ctx.UInt32Value(value["bresenhamLines"]);
    ctx.UInt32Value(value["smoothLines"]);
    ctx.UInt32Value(value["stippledRectangularLines"]);
    ctx.UInt32Value(value["stippledBresenhamLines"]);
    ctx.UInt32Value(value["stippledSmoothLines"]);
    ctx.UInt32Value(value["vertexAttributeInstanceRateDivisor"]);
    ctx.UInt32Value(value["vertexAttributeInstanceRateZeroDivisor"]);
    ctx.UInt32Value(value["indexTypeUint8"]);
    ctx.UInt32Value(value["dynamicRenderingLocalRead"]);
    ctx.UInt32Value(value["maintenance5"]);
    ctx.UInt32Value(value["maintenance6"]);
    ctx.UInt32Value(value["pipelineProtectedAccess"]);
    ctx.UInt32Value(value["pipelineRobustness"]);
    ctx.UInt32Value(value["hostImageCopy"]);
    ctx.UInt32Value(value["pushDescriptor"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceVulkan14Properties>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["lineSubPixelPrecisionBits"]);
    ctx.UInt32Value(value["maxVertexAttribDivisor"]);
    ctx.UInt32Value(value["supportsNonZeroFirstInstance"]);
    ctx.UInt32Value(value["maxPushDescriptors"]);
    ctx.UInt32Value(value["dynamicRenderingLocalReadDepthStencilAttachments"]);
    ctx.UInt32Value(value["dynamicRenderingLocalReadMultisampledAttachments"]);
    ctx.UInt32Value(value["earlyFragmentMultisampleCoverageAfterSampleCounting"]);
    ctx.UInt32Value(value["earlyFragmentSampleMaskTestBeforeSampleCounting"]);
    ctx.UInt32Value(value["depthStencilSwizzleOneSupport"]);
    ctx.UInt32Value(value["polygonModePointSize"]);
    ctx.UInt32Value(value["nonStrictSinglePixelWideLinesUseParallelogram"]);
    ctx.UInt32Value(value["nonStrictWideLinesUseParallelogram"]);
    ctx.UInt32Value(value["blockTexelViewCompatibleMultipleLayers"]);
    ctx.UInt32Value(value["maxCombinedImageSamplerDescriptorCount"]);
    ctx.UInt32Value(value["fragmentShadingRateClampCombinerInputs"]);
    ctx.EnumValue(value["defaultRobustnessStorageBuffers"], EnumFromString_VkPipelineRobustnessBufferBehavior);
    ctx.EnumValue(value["defaultRobustnessUniformBuffers"], EnumFromString_VkPipelineRobustnessBufferBehavior);
    ctx.EnumValue(value["defaultRobustnessVertexInputs"], EnumFromString_VkPipelineRobustnessBufferBehavior);
    ctx.EnumValue(value["defaultRobustnessImages"], EnumFromString_VkPipelineRobustnessImageBehavior);
    ctx.UInt32Value(value["copySrcLayoutCount"]);
    ctx.EnumArray(value["pCopySrcLayouts"], EnumFromString_VkImageLayout, ctx.Length(value["copySrcLayoutCount"]));
    ctx.UInt32Value(value["copyDstLayoutCount"]);
    ctx.EnumArray(value["pCopyDstLayouts"], EnumFromString_VkImageLayout, ctx.Length(value["copyDstLayoutCount"]));
    ctx.UInt8Array(value["optimalTilingLayoutUUID"]);
    ctx.UInt32Value(value["identicalMemoryTypeRequirements"]);
}

template <> void StructFromApiDump<VkDeviceQueueGlobalPriorityCreateInfo>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.EnumValue(value["globalPriority"], EnumFromString_VkQueueGlobalPriority);
}

template <> void StructFromApiDump<VkPhysicalDeviceGlobalPriorityQueryFeatures>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["globalPriorityQuery"]);
}

template <> void StructFromApiDump<VkQueueFamilyGlobalPriorityProperties>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["priorityCount"]);
    ctx.EnumArray(value["priorities"], EnumFromString_VkQueueGlobalPriority);
}

template <> void StructFromApiDump<VkPhysicalDeviceIndexTypeUint8Features>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["indexTypeUint8"]);
}

template <> void StructFromApiDump<VkMemoryMapInfo>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.FlagsValue(value["flags"], EnumFromString_VkMemoryMapFlagBits);
    ctx.VulkanHandleValue(value["memory"], VK_OBJECT_TYPE_DEVICE_MEMORY);
    ctx.UInt64Value(value["offset"]);
    ctx.UInt64Value(value["size"]);
}

template <> void StructFromApiDump<VkMemoryUnmapInfo>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.FlagsValue(value["flags"], EnumFromString_VkMemoryUnmapFlagBits);
    ctx.VulkanHandleValue(value["memory"], VK_OBJECT_TYPE_DEVICE_MEMORY);
}

template <> void StructFromApiDump<VkPhysicalDeviceMaintenance5Features>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["maintenance5"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceMaintenance5Properties>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["earlyFragmentMultisampleCoverageAfterSampleCounting"]);
    ctx.UInt32Value(value["earlyFragmentSampleMaskTestBeforeSampleCounting"]);
    ctx.UInt32Value(value["depthStencilSwizzleOneSupport"]);
    ctx.UInt32Value(value["polygonModePointSize"]);
    ctx.UInt32Value(value["nonStrictSinglePixelWideLinesUseParallelogram"]);
    ctx.UInt32Value(value["nonStrictWideLinesUseParallelogram"]);
}

template <> void StructFromApiDump<VkSubresourceLayout2>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    StructFromApiDump<VkSubresourceLayout>(ctx, value["subresourceLayout"]);
}

template <> void StructFromApiDump<VkImageSubresource2>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    StructFromApiDump<VkImageSubresource>(ctx, value["imageSubresource"]);
}

template <> void StructFromApiDump<VkDeviceImageSubresourceInfo>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    StructPtrFromApiDump<VkImageCreateInfo>(ctx, value["pCreateInfo"]);
    StructPtrFromApiDump<VkImageSubresource2>(ctx, value["pSubresource"]);
}

template <> void StructFromApiDump<VkBufferUsageFlags2CreateInfo>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.Flags64Value(value["usage"], EnumFromString_VkBufferUsageFlagBits2);
}

template <> void StructFromApiDump<VkPhysicalDeviceMaintenance6Features>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["maintenance6"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceMaintenance6Properties>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["blockTexelViewCompatibleMultipleLayers"]);
    ctx.UInt32Value(value["maxCombinedImageSamplerDescriptorCount"]);
    ctx.UInt32Value(value["fragmentShadingRateClampCombinerInputs"]);
}

template <> void StructFromApiDump<VkBindMemoryStatus>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.EnumPtr(value["pResult"], EnumFromString_VkResult);
}

template <> void StructFromApiDump<VkPhysicalDeviceHostImageCopyFeatures>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["hostImageCopy"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceHostImageCopyProperties>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["copySrcLayoutCount"]);
    ctx.EnumArray(value["pCopySrcLayouts"], EnumFromString_VkImageLayout, ctx.Length(value["copySrcLayoutCount"]));
    ctx.UInt32Value(value["copyDstLayoutCount"]);
    ctx.EnumArray(value["pCopyDstLayouts"], EnumFromString_VkImageLayout, ctx.Length(value["copyDstLayoutCount"]));
    ctx.UInt8Array(value["optimalTilingLayoutUUID"]);
    ctx.UInt32Value(value["identicalMemoryTypeRequirements"]);
}

template <> void StructFromApiDump<VkCopyImageToImageInfo>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.FlagsValue(value["flags"], EnumFromString_VkHostImageCopyFlagBits);
    ctx.VulkanHandleValue(value["srcImage"], VK_OBJECT_TYPE_IMAGE);
    ctx.EnumValue(value["srcImageLayout"], EnumFromString_VkImageLayout);
    ctx.VulkanHandleValue(value["dstImage"], VK_OBJECT_TYPE_IMAGE);
    ctx.EnumValue(value["dstImageLayout"], EnumFromString_VkImageLayout);
    ctx.UInt32Value(value["regionCount"]);
    StructArrayFromApiDump<VkImageCopy2>(ctx, value["pRegions"], ctx.Length(value["regionCount"]));
}

template <> void StructFromApiDump<VkHostImageLayoutTransitionInfo>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.VulkanHandleValue(value["image"], VK_OBJECT_TYPE_IMAGE);
    ctx.EnumValue(value["oldLayout"], EnumFromString_VkImageLayout);
    ctx.EnumValue(value["newLayout"], EnumFromString_VkImageLayout);
    StructFromApiDump<VkImageSubresourceRange>(ctx, value["subresourceRange"]);
}

template <> void StructFromApiDump<VkSubresourceHostMemcpySize>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt64Value(value["size"]);
}

template <> void StructFromApiDump<VkHostImageCopyDevicePerformanceQuery>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["optimalDeviceAccess"]);
    ctx.UInt32Value(value["identicalMemoryLayout"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceShaderSubgroupRotateFeatures>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["shaderSubgroupRotate"]);
    ctx.UInt32Value(value["shaderSubgroupRotateClustered"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceShaderFloatControls2Features>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["shaderFloatControls2"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceShaderExpectAssumeFeatures>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["shaderExpectAssume"]);
}

template <> void StructFromApiDump<VkPipelineCreateFlags2CreateInfo>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.Flags64Value(value["flags"], EnumFromString_VkPipelineCreateFlagBits2);
}

template <> void StructFromApiDump<VkPhysicalDevicePushDescriptorProperties>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["maxPushDescriptors"]);
}

template <> void StructFromApiDump<VkBindDescriptorSetsInfo>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.FlagsValue(value["stageFlags"], EnumFromString_VkShaderStageFlagBits);
    ctx.VulkanHandleValue(value["layout"], VK_OBJECT_TYPE_PIPELINE_LAYOUT);
    ctx.UInt32Value(value["firstSet"]);
    ctx.UInt32Value(value["descriptorSetCount"]);
    ctx.VulkanHandleArray(value["pDescriptorSets"], VK_OBJECT_TYPE_DESCRIPTOR_SET, ctx.Length(value["descriptorSetCount"]));
    ctx.UInt32Value(value["dynamicOffsetCount"]);
    ctx.UInt32Array(value["pDynamicOffsets"], ctx.Length(value["dynamicOffsetCount"]));
}

template <> void StructFromApiDump<VkPushConstantsInfo>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.VulkanHandleValue(value["layout"], VK_OBJECT_TYPE_PIPELINE_LAYOUT);
    ctx.FlagsValue(value["stageFlags"], EnumFromString_VkShaderStageFlagBits);
    ctx.UInt32Value(value["offset"]);
    ctx.UInt32Value(value["size"]);
    ctx.UInt8Array(value["pValues"], ctx.Length(value["size"]));
}

template <> void StructFromApiDump<VkPushDescriptorSetInfo>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.FlagsValue(value["stageFlags"], EnumFromString_VkShaderStageFlagBits);
    ctx.VulkanHandleValue(value["layout"], VK_OBJECT_TYPE_PIPELINE_LAYOUT);
    ctx.UInt32Value(value["set"]);
    ctx.UInt32Value(value["descriptorWriteCount"]);
    StructArrayFromApiDump<VkWriteDescriptorSet>(ctx, value["pDescriptorWrites"], ctx.Length(value["descriptorWriteCount"]));
}

template <> void StructFromApiDump<VkPhysicalDevicePipelineProtectedAccessFeatures>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["pipelineProtectedAccess"]);
}

template <> void StructFromApiDump<VkPhysicalDevicePipelineRobustnessFeatures>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["pipelineRobustness"]);
}

template <> void StructFromApiDump<VkPhysicalDevicePipelineRobustnessProperties>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.EnumValue(value["defaultRobustnessStorageBuffers"], EnumFromString_VkPipelineRobustnessBufferBehavior);
    ctx.EnumValue(value["defaultRobustnessUniformBuffers"], EnumFromString_VkPipelineRobustnessBufferBehavior);
    ctx.EnumValue(value["defaultRobustnessVertexInputs"], EnumFromString_VkPipelineRobustnessBufferBehavior);
    ctx.EnumValue(value["defaultRobustnessImages"], EnumFromString_VkPipelineRobustnessImageBehavior);
}

template <> void StructFromApiDump<VkPipelineRobustnessCreateInfo>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.EnumValue(value["storageBuffers"], EnumFromString_VkPipelineRobustnessBufferBehavior);
    ctx.EnumValue(value["uniformBuffers"], EnumFromString_VkPipelineRobustnessBufferBehavior);
    ctx.EnumValue(value["vertexInputs"], EnumFromString_VkPipelineRobustnessBufferBehavior);
    ctx.EnumValue(value["images"], EnumFromString_VkPipelineRobustnessImageBehavior);
}

template <> void StructFromApiDump<VkPhysicalDeviceLineRasterizationFeatures>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["rectangularLines"]);
    ctx.UInt32Value(value["bresenhamLines"]);
    ctx.UInt32Value(value["smoothLines"]);
    ctx.UInt32Value(value["stippledRectangularLines"]);
    ctx.UInt32Value(value["stippledBresenhamLines"]);
    ctx.UInt32Value(value["stippledSmoothLines"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceLineRasterizationProperties>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["lineSubPixelPrecisionBits"]);
}

template <> void StructFromApiDump<VkPipelineRasterizationLineStateCreateInfo>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.EnumValue(value["lineRasterizationMode"], EnumFromString_VkLineRasterizationMode);
    ctx.UInt32Value(value["stippledLineEnable"]);
    ctx.UInt32Value(value["lineStippleFactor"]);
    ctx.UInt16Value(value["lineStipplePattern"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceVertexAttributeDivisorProperties>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["maxVertexAttribDivisor"]);
    ctx.UInt32Value(value["supportsNonZeroFirstInstance"]);
}

template <> void StructFromApiDump<VkVertexInputBindingDivisorDescription>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.UInt32Value(value["binding"]);
    ctx.UInt32Value(value["divisor"]);
}

template <> void StructFromApiDump<VkPipelineVertexInputDivisorStateCreateInfo>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["vertexBindingDivisorCount"]);
    StructArrayFromApiDump<VkVertexInputBindingDivisorDescription>(ctx, value["pVertexBindingDivisors"], ctx.Length(value["vertexBindingDivisorCount"]));
}

template <> void StructFromApiDump<VkPhysicalDeviceVertexAttributeDivisorFeatures>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["vertexAttributeInstanceRateDivisor"]);
    ctx.UInt32Value(value["vertexAttributeInstanceRateZeroDivisor"]);
}

template <> void StructFromApiDump<VkRenderingAreaInfo>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["viewMask"]);
    ctx.UInt32Value(value["colorAttachmentCount"]);
    ctx.EnumArray(value["pColorAttachmentFormats"], EnumFromString_VkFormat, ctx.Length(value["colorAttachmentCount"]));
    ctx.EnumValue(value["depthAttachmentFormat"], EnumFromString_VkFormat);
    ctx.EnumValue(value["stencilAttachmentFormat"], EnumFromString_VkFormat);
}

template <> void StructFromApiDump<VkPhysicalDeviceDynamicRenderingLocalReadFeatures>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["dynamicRenderingLocalRead"]);
}

template <> void StructFromApiDump<VkRenderingAttachmentLocationInfo>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["colorAttachmentCount"]);
    ctx.UInt32Array(value["pColorAttachmentLocations"], ctx.Length(value["colorAttachmentCount"]));
}

template <> void StructFromApiDump<VkRenderingInputAttachmentIndexInfo>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["colorAttachmentCount"]);
    ctx.UInt32Array(value["pColorAttachmentInputIndices"], ctx.Length(value["colorAttachmentCount"]));
    ctx.UInt32Ptr(value["pDepthInputAttachmentIndex"]);
    ctx.UInt32Ptr(value["pStencilInputAttachmentIndex"]);
}

template <> void StructFromApiDump<VkSurfaceCapabilitiesKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.UInt32Value(value["minImageCount"]);
    ctx.UInt32Value(value["maxImageCount"]);
    StructFromApiDump<VkExtent2D>(ctx, value["currentExtent"]);
    StructFromApiDump<VkExtent2D>(ctx, value["minImageExtent"]);
    StructFromApiDump<VkExtent2D>(ctx, value["maxImageExtent"]);
    ctx.UInt32Value(value["maxImageArrayLayers"]);
    ctx.FlagsValue(value["supportedTransforms"], EnumFromString_VkSurfaceTransformFlagBitsKHR);
    ctx.EnumValue(value["currentTransform"], EnumFromString_VkSurfaceTransformFlagBitsKHR);
    ctx.FlagsValue(value["supportedCompositeAlpha"], EnumFromString_VkCompositeAlphaFlagBitsKHR);
    ctx.FlagsValue(value["supportedUsageFlags"], EnumFromString_VkImageUsageFlagBits);
}

template <> void StructFromApiDump<VkSurfaceFormatKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["format"], EnumFromString_VkFormat);
    ctx.EnumValue(value["colorSpace"], EnumFromString_VkColorSpaceKHR);
}

template <> void StructFromApiDump<VkSwapchainCreateInfoKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.FlagsValue(value["flags"], EnumFromString_VkSwapchainCreateFlagBitsKHR);
    ctx.VulkanHandleValue(value["surface"], VK_OBJECT_TYPE_SURFACE_KHR);
    ctx.UInt32Value(value["minImageCount"]);
    ctx.EnumValue(value["imageFormat"], EnumFromString_VkFormat);
    ctx.EnumValue(value["imageColorSpace"], EnumFromString_VkColorSpaceKHR);
    StructFromApiDump<VkExtent2D>(ctx, value["imageExtent"]);
    ctx.UInt32Value(value["imageArrayLayers"]);
    ctx.FlagsValue(value["imageUsage"], EnumFromString_VkImageUsageFlagBits);
    ctx.EnumValue(value["imageSharingMode"], EnumFromString_VkSharingMode);
    ctx.UInt32Value(value["queueFamilyIndexCount"]);
    ctx.UInt32Array(value["pQueueFamilyIndices"], ctx.Length(value["queueFamilyIndexCount"]));
    ctx.EnumValue(value["preTransform"], EnumFromString_VkSurfaceTransformFlagBitsKHR);
    ctx.EnumValue(value["compositeAlpha"], EnumFromString_VkCompositeAlphaFlagBitsKHR);
    ctx.EnumValue(value["presentMode"], EnumFromString_VkPresentModeKHR);
    ctx.UInt32Value(value["clipped"]);
    ctx.VulkanHandleValue(value["oldSwapchain"], VK_OBJECT_TYPE_SWAPCHAIN_KHR);
}

template <> void StructFromApiDump<VkPresentInfoKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["waitSemaphoreCount"]);
    ctx.VulkanHandleArray(value["pWaitSemaphores"], VK_OBJECT_TYPE_SEMAPHORE, ctx.Length(value["waitSemaphoreCount"]));
    ctx.UInt32Value(value["swapchainCount"]);
    ctx.VulkanHandleArray(value["pSwapchains"], VK_OBJECT_TYPE_SWAPCHAIN_KHR, ctx.Length(value["swapchainCount"]));
    ctx.UInt32Array(value["pImageIndices"], ctx.Length(value["swapchainCount"]));
    ctx.EnumArray(value["pResults"], EnumFromString_VkResult, ctx.Length(value["swapchainCount"]));
}

template <> void StructFromApiDump<VkImageSwapchainCreateInfoKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.VulkanHandleValue(value["swapchain"], VK_OBJECT_TYPE_SWAPCHAIN_KHR);
}

template <> void StructFromApiDump<VkBindImageMemorySwapchainInfoKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.VulkanHandleValue(value["swapchain"], VK_OBJECT_TYPE_SWAPCHAIN_KHR);
    ctx.UInt32Value(value["imageIndex"]);
}

template <> void StructFromApiDump<VkAcquireNextImageInfoKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.VulkanHandleValue(value["swapchain"], VK_OBJECT_TYPE_SWAPCHAIN_KHR);
    ctx.UInt64Value(value["timeout"]);
    ctx.VulkanHandleValue(value["semaphore"], VK_OBJECT_TYPE_SEMAPHORE);
    ctx.VulkanHandleValue(value["fence"], VK_OBJECT_TYPE_FENCE);
    ctx.UInt32Value(value["deviceMask"]);
}

template <> void StructFromApiDump<VkDeviceGroupPresentCapabilitiesKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Array(value["presentMask"]);
    ctx.FlagsValue(value["modes"], EnumFromString_VkDeviceGroupPresentModeFlagBitsKHR);
}

template <> void StructFromApiDump<VkDeviceGroupPresentInfoKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["swapchainCount"]);
    ctx.UInt32Array(value["pDeviceMasks"], ctx.Length(value["swapchainCount"]));
    ctx.EnumValue(value["mode"], EnumFromString_VkDeviceGroupPresentModeFlagBitsKHR);
}

template <> void StructFromApiDump<VkDeviceGroupSwapchainCreateInfoKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.FlagsValue(value["modes"], EnumFromString_VkDeviceGroupPresentModeFlagBitsKHR);
}

template <> void StructFromApiDump<VkDisplayModeParametersKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    StructFromApiDump<VkExtent2D>(ctx, value["visibleRegion"]);
    ctx.UInt32Value(value["refreshRate"]);
}

template <> void StructFromApiDump<VkDisplayModeCreateInfoKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.FlagsValue(value["flags"]);
    StructFromApiDump<VkDisplayModeParametersKHR>(ctx, value["parameters"]);
}

template <> void StructFromApiDump<VkDisplayModePropertiesKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.VulkanHandleValue(value["displayMode"], VK_OBJECT_TYPE_DISPLAY_MODE_KHR);
    StructFromApiDump<VkDisplayModeParametersKHR>(ctx, value["parameters"]);
}

template <> void StructFromApiDump<VkDisplayPlaneCapabilitiesKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.FlagsValue(value["supportedAlpha"], EnumFromString_VkDisplayPlaneAlphaFlagBitsKHR);
    StructFromApiDump<VkOffset2D>(ctx, value["minSrcPosition"]);
    StructFromApiDump<VkOffset2D>(ctx, value["maxSrcPosition"]);
    StructFromApiDump<VkExtent2D>(ctx, value["minSrcExtent"]);
    StructFromApiDump<VkExtent2D>(ctx, value["maxSrcExtent"]);
    StructFromApiDump<VkOffset2D>(ctx, value["minDstPosition"]);
    StructFromApiDump<VkOffset2D>(ctx, value["maxDstPosition"]);
    StructFromApiDump<VkExtent2D>(ctx, value["minDstExtent"]);
    StructFromApiDump<VkExtent2D>(ctx, value["maxDstExtent"]);
}

template <> void StructFromApiDump<VkDisplayPlanePropertiesKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.VulkanHandleValue(value["currentDisplay"], VK_OBJECT_TYPE_DISPLAY_KHR);
    ctx.UInt32Value(value["currentStackIndex"]);
}

template <> void StructFromApiDump<VkDisplayPropertiesKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.VulkanHandleValue(value["display"], VK_OBJECT_TYPE_DISPLAY_KHR);
    ctx.StringValue(value["displayName"]);
    StructFromApiDump<VkExtent2D>(ctx, value["physicalDimensions"]);
    StructFromApiDump<VkExtent2D>(ctx, value["physicalResolution"]);
    ctx.FlagsValue(value["supportedTransforms"], EnumFromString_VkSurfaceTransformFlagBitsKHR);
    ctx.UInt32Value(value["planeReorderPossible"]);
    ctx.UInt32Value(value["persistentContent"]);
}

template <> void StructFromApiDump<VkDisplaySurfaceCreateInfoKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.FlagsValue(value["flags"]);
    ctx.VulkanHandleValue(value["displayMode"], VK_OBJECT_TYPE_DISPLAY_MODE_KHR);
    ctx.UInt32Value(value["planeIndex"]);
    ctx.UInt32Value(value["planeStackIndex"]);
    ctx.EnumValue(value["transform"], EnumFromString_VkSurfaceTransformFlagBitsKHR);
    ctx.FloatValue(value["globalAlpha"]);
    ctx.EnumValue(value["alphaMode"], EnumFromString_VkDisplayPlaneAlphaFlagBitsKHR);
    StructFromApiDump<VkExtent2D>(ctx, value["imageExtent"]);
}

template <> void StructFromApiDump<VkDisplayPresentInfoKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    StructFromApiDump<VkRect2D>(ctx, value["srcRect"]);
    StructFromApiDump<VkRect2D>(ctx, value["dstRect"]);
    ctx.UInt32Value(value["persistent"]);
}

template <> void StructFromApiDump<VkXlibSurfaceCreateInfoKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.FlagsValue(value["flags"]);
    ctx.VoidPtrValue(value["dpy"]);
    ctx.SizeTValue(value["window"]);
}

template <> void StructFromApiDump<VkXcbSurfaceCreateInfoKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.FlagsValue(value["flags"]);
    ctx.VoidPtrValue(value["connection"]);
    ctx.UInt32Value(value["window"]);
}

template <> void StructFromApiDump<VkWaylandSurfaceCreateInfoKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.FlagsValue(value["flags"]);
    ctx.VoidPtrValue(value["display"]);
    ctx.VoidPtrValue(value["surface"]);
}

template <> void StructFromApiDump<VkAndroidSurfaceCreateInfoKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.FlagsValue(value["flags"]);
    ctx.VoidPtrValue(value["window"]);
}

template <> void StructFromApiDump<VkWin32SurfaceCreateInfoKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.FlagsValue(value["flags"]);
    ctx.VoidPtrValue(value["hinstance"]);
    ctx.VoidPtrValue(value["hwnd"]);
}

template <> void StructFromApiDump<VkQueueFamilyQueryResultStatusPropertiesKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["queryResultStatusSupport"]);
}

template <> void StructFromApiDump<VkQueueFamilyVideoPropertiesKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.FlagsValue(value["videoCodecOperations"], EnumFromString_VkVideoCodecOperationFlagBitsKHR);
}

template <> void StructFromApiDump<VkVideoProfileInfoKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.EnumValue(value["videoCodecOperation"], EnumFromString_VkVideoCodecOperationFlagBitsKHR);
    ctx.FlagsValue(value["chromaSubsampling"], EnumFromString_VkVideoChromaSubsamplingFlagBitsKHR);
    ctx.FlagsValue(value["lumaBitDepth"], EnumFromString_VkVideoComponentBitDepthFlagBitsKHR);
    ctx.FlagsValue(value["chromaBitDepth"], EnumFromString_VkVideoComponentBitDepthFlagBitsKHR);
}

template <> void StructFromApiDump<VkVideoProfileListInfoKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["profileCount"]);
    StructArrayFromApiDump<VkVideoProfileInfoKHR>(ctx, value["pProfiles"], ctx.Length(value["profileCount"]));
}

template <> void StructFromApiDump<VkVideoCapabilitiesKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.FlagsValue(value["flags"], EnumFromString_VkVideoCapabilityFlagBitsKHR);
    ctx.UInt64Value(value["minBitstreamBufferOffsetAlignment"]);
    ctx.UInt64Value(value["minBitstreamBufferSizeAlignment"]);
    StructFromApiDump<VkExtent2D>(ctx, value["pictureAccessGranularity"]);
    StructFromApiDump<VkExtent2D>(ctx, value["minCodedExtent"]);
    StructFromApiDump<VkExtent2D>(ctx, value["maxCodedExtent"]);
    ctx.UInt32Value(value["maxDpbSlots"]);
    ctx.UInt32Value(value["maxActiveReferencePictures"]);
    StructFromApiDump<VkExtensionProperties>(ctx, value["stdHeaderVersion"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceVideoFormatInfoKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.FlagsValue(value["imageUsage"], EnumFromString_VkImageUsageFlagBits);
}

template <> void StructFromApiDump<VkVideoFormatPropertiesKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.EnumValue(value["format"], EnumFromString_VkFormat);
    StructFromApiDump<VkComponentMapping>(ctx, value["componentMapping"]);
    ctx.FlagsValue(value["imageCreateFlags"], EnumFromString_VkImageCreateFlagBits);
    ctx.EnumValue(value["imageType"], EnumFromString_VkImageType);
    ctx.EnumValue(value["imageTiling"], EnumFromString_VkImageTiling);
    ctx.FlagsValue(value["imageUsageFlags"], EnumFromString_VkImageUsageFlagBits);
}

template <> void StructFromApiDump<VkVideoPictureResourceInfoKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    StructFromApiDump<VkOffset2D>(ctx, value["codedOffset"]);
    StructFromApiDump<VkExtent2D>(ctx, value["codedExtent"]);
    ctx.UInt32Value(value["baseArrayLayer"]);
    ctx.VulkanHandleValue(value["imageViewBinding"], VK_OBJECT_TYPE_IMAGE_VIEW);
}

template <> void StructFromApiDump<VkVideoReferenceSlotInfoKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.Int32Value(value["slotIndex"]);
    StructPtrFromApiDump<VkVideoPictureResourceInfoKHR>(ctx, value["pPictureResource"]);
}

template <> void StructFromApiDump<VkVideoSessionMemoryRequirementsKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["memoryBindIndex"]);
    StructFromApiDump<VkMemoryRequirements>(ctx, value["memoryRequirements"]);
}

template <> void StructFromApiDump<VkBindVideoSessionMemoryInfoKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["memoryBindIndex"]);
    ctx.VulkanHandleValue(value["memory"], VK_OBJECT_TYPE_DEVICE_MEMORY);
    ctx.UInt64Value(value["memoryOffset"]);
    ctx.UInt64Value(value["memorySize"]);
}

template <> void StructFromApiDump<VkVideoSessionCreateInfoKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["queueFamilyIndex"]);
    ctx.FlagsValue(value["flags"], EnumFromString_VkVideoSessionCreateFlagBitsKHR);
    StructPtrFromApiDump<VkVideoProfileInfoKHR>(ctx, value["pVideoProfile"]);
    ctx.EnumValue(value["pictureFormat"], EnumFromString_VkFormat);
    StructFromApiDump<VkExtent2D>(ctx, value["maxCodedExtent"]);
    ctx.EnumValue(value["referencePictureFormat"], EnumFromString_VkFormat);
    ctx.UInt32Value(value["maxDpbSlots"]);
    ctx.UInt32Value(value["maxActiveReferencePictures"]);
    StructPtrFromApiDump<VkExtensionProperties>(ctx, value["pStdHeaderVersion"]);
}

template <> void StructFromApiDump<VkVideoSessionParametersCreateInfoKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.FlagsValue(value["flags"], EnumFromString_VkVideoSessionParametersCreateFlagBitsKHR);
    ctx.VulkanHandleValue(value["videoSessionParametersTemplate"], VK_OBJECT_TYPE_VIDEO_SESSION_PARAMETERS_KHR);
    ctx.VulkanHandleValue(value["videoSession"], VK_OBJECT_TYPE_VIDEO_SESSION_KHR);
}

template <> void StructFromApiDump<VkVideoSessionParametersUpdateInfoKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["updateSequenceCount"]);
}

template <> void StructFromApiDump<VkVideoBeginCodingInfoKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.FlagsValue(value["flags"]);
    ctx.VulkanHandleValue(value["videoSession"], VK_OBJECT_TYPE_VIDEO_SESSION_KHR);
    ctx.VulkanHandleValue(value["videoSessionParameters"], VK_OBJECT_TYPE_VIDEO_SESSION_PARAMETERS_KHR);
    ctx.UInt32Value(value["referenceSlotCount"]);
    StructArrayFromApiDump<VkVideoReferenceSlotInfoKHR>(ctx, value["pReferenceSlots"], ctx.Length(value["referenceSlotCount"]));
}

template <> void StructFromApiDump<VkVideoEndCodingInfoKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.FlagsValue(value["flags"]);
}

template <> void StructFromApiDump<VkVideoCodingControlInfoKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.FlagsValue(value["flags"], EnumFromString_VkVideoCodingControlFlagBitsKHR);
}

template <> void StructFromApiDump<VkVideoDecodeCapabilitiesKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.FlagsValue(value["flags"], EnumFromString_VkVideoDecodeCapabilityFlagBitsKHR);
}

template <> void StructFromApiDump<VkVideoDecodeUsageInfoKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.FlagsValue(value["videoUsageHints"], EnumFromString_VkVideoDecodeUsageFlagBitsKHR);
}

template <> void StructFromApiDump<VkVideoDecodeInfoKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.FlagsValue(value["flags"]);
    ctx.VulkanHandleValue(value["srcBuffer"], VK_OBJECT_TYPE_BUFFER);
    ctx.UInt64Value(value["srcBufferOffset"]);
    ctx.UInt64Value(value["srcBufferRange"]);
    StructFromApiDump<VkVideoPictureResourceInfoKHR>(ctx, value["dstPictureResource"]);
    StructPtrFromApiDump<VkVideoReferenceSlotInfoKHR>(ctx, value["pSetupReferenceSlot"]);
    ctx.UInt32Value(value["referenceSlotCount"]);
    StructArrayFromApiDump<VkVideoReferenceSlotInfoKHR>(ctx, value["pReferenceSlots"], ctx.Length(value["referenceSlotCount"]));
}

template <> void StructFromApiDump<VkVideoEncodeH264CapabilitiesKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.FlagsValue(value["flags"], EnumFromString_VkVideoEncodeH264CapabilityFlagBitsKHR);
    ctx.EnumValue(value["maxLevelIdc"], EnumFromString_StdVideoH264LevelIdc);
    ctx.UInt32Value(value["maxSliceCount"]);
    ctx.UInt32Value(value["maxPPictureL0ReferenceCount"]);
    ctx.UInt32Value(value["maxBPictureL0ReferenceCount"]);
    ctx.UInt32Value(value["maxL1ReferenceCount"]);
    ctx.UInt32Value(value["maxTemporalLayerCount"]);
    ctx.UInt32Value(value["expectDyadicTemporalLayerPattern"]);
    ctx.Int32Value(value["minQp"]);
    ctx.Int32Value(value["maxQp"]);
    ctx.UInt32Value(value["prefersGopRemainingFrames"]);
    ctx.UInt32Value(value["requiresGopRemainingFrames"]);
    ctx.FlagsValue(value["stdSyntaxFlags"], EnumFromString_VkVideoEncodeH264StdFlagBitsKHR);
}

template <> void StructFromApiDump<VkVideoEncodeH264QpKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.Int32Value(value["qpI"]);
    ctx.Int32Value(value["qpP"]);
    ctx.Int32Value(value["qpB"]);
}

template <> void StructFromApiDump<VkVideoEncodeH264QualityLevelPropertiesKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.FlagsValue(value["preferredRateControlFlags"], EnumFromString_VkVideoEncodeH264RateControlFlagBitsKHR);
    ctx.UInt32Value(value["preferredGopFrameCount"]);
    ctx.UInt32Value(value["preferredIdrPeriod"]);
    ctx.UInt32Value(value["preferredConsecutiveBFrameCount"]);
    ctx.UInt32Value(value["preferredTemporalLayerCount"]);
    StructFromApiDump<VkVideoEncodeH264QpKHR>(ctx, value["preferredConstantQp"]);
    ctx.UInt32Value(value["preferredMaxL0ReferenceCount"]);
    ctx.UInt32Value(value["preferredMaxL1ReferenceCount"]);
    ctx.UInt32Value(value["preferredStdEntropyCodingModeFlag"]);
}

template <> void StructFromApiDump<VkVideoEncodeH264SessionCreateInfoKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["useMaxLevelIdc"]);
    ctx.EnumValue(value["maxLevelIdc"], EnumFromString_StdVideoH264LevelIdc);
}

template <> void StructFromApiDump<VkVideoEncodeH264SessionParametersAddInfoKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["stdSPSCount"]);
    StructArrayFromApiDump<StdVideoH264SequenceParameterSet>(ctx, value["pStdSPSs"], ctx.Length(value["stdSPSCount"]));
    ctx.UInt32Value(value["stdPPSCount"]);
    StructArrayFromApiDump<StdVideoH264PictureParameterSet>(ctx, value["pStdPPSs"], ctx.Length(value["stdPPSCount"]));
}

template <> void StructFromApiDump<VkVideoEncodeH264SessionParametersCreateInfoKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["maxStdSPSCount"]);
    ctx.UInt32Value(value["maxStdPPSCount"]);
    StructPtrFromApiDump<VkVideoEncodeH264SessionParametersAddInfoKHR>(ctx, value["pParametersAddInfo"]);
}

template <> void StructFromApiDump<VkVideoEncodeH264SessionParametersGetInfoKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["writeStdSPS"]);
    ctx.UInt32Value(value["writeStdPPS"]);
    ctx.UInt32Value(value["stdSPSId"]);
    ctx.UInt32Value(value["stdPPSId"]);
}

template <> void StructFromApiDump<VkVideoEncodeH264SessionParametersFeedbackInfoKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["hasStdSPSOverrides"]);
    ctx.UInt32Value(value["hasStdPPSOverrides"]);
}

template <> void StructFromApiDump<VkVideoEncodeH264NaluSliceInfoKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.Int32Value(value["constantQp"]);
    StructPtrFromApiDump<StdVideoEncodeH264SliceHeader>(ctx, value["pStdSliceHeader"]);
}

template <> void StructFromApiDump<VkVideoEncodeH264PictureInfoKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["naluSliceEntryCount"]);
    StructArrayFromApiDump<VkVideoEncodeH264NaluSliceInfoKHR>(ctx, value["pNaluSliceEntries"], ctx.Length(value["naluSliceEntryCount"]));
    StructPtrFromApiDump<StdVideoEncodeH264PictureInfo>(ctx, value["pStdPictureInfo"]);
    ctx.UInt32Value(value["generatePrefixNalu"]);
}

template <> void StructFromApiDump<VkVideoEncodeH264DpbSlotInfoKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    StructPtrFromApiDump<StdVideoEncodeH264ReferenceInfo>(ctx, value["pStdReferenceInfo"]);
}

template <> void StructFromApiDump<VkVideoEncodeH264ProfileInfoKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.EnumValue(value["stdProfileIdc"], EnumFromString_StdVideoH264ProfileIdc);
}

template <> void StructFromApiDump<VkVideoEncodeH264RateControlInfoKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.FlagsValue(value["flags"], EnumFromString_VkVideoEncodeH264RateControlFlagBitsKHR);
    ctx.UInt32Value(value["gopFrameCount"]);
    ctx.UInt32Value(value["idrPeriod"]);
    ctx.UInt32Value(value["consecutiveBFrameCount"]);
    ctx.UInt32Value(value["temporalLayerCount"]);
}

template <> void StructFromApiDump<VkVideoEncodeH264FrameSizeKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.UInt32Value(value["frameISize"]);
    ctx.UInt32Value(value["framePSize"]);
    ctx.UInt32Value(value["frameBSize"]);
}

template <> void StructFromApiDump<VkVideoEncodeH264RateControlLayerInfoKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["useMinQp"]);
    StructFromApiDump<VkVideoEncodeH264QpKHR>(ctx, value["minQp"]);
    ctx.UInt32Value(value["useMaxQp"]);
    StructFromApiDump<VkVideoEncodeH264QpKHR>(ctx, value["maxQp"]);
    ctx.UInt32Value(value["useMaxFrameSize"]);
    StructFromApiDump<VkVideoEncodeH264FrameSizeKHR>(ctx, value["maxFrameSize"]);
}

template <> void StructFromApiDump<VkVideoEncodeH264GopRemainingFrameInfoKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["useGopRemainingFrames"]);
    ctx.UInt32Value(value["gopRemainingI"]);
    ctx.UInt32Value(value["gopRemainingP"]);
    ctx.UInt32Value(value["gopRemainingB"]);
}

template <> void StructFromApiDump<VkVideoDecodeH264ProfileInfoKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.EnumValue(value["stdProfileIdc"], EnumFromString_StdVideoH264ProfileIdc);
    ctx.EnumValue(value["pictureLayout"], EnumFromString_VkVideoDecodeH264PictureLayoutFlagBitsKHR);
}

template <> void StructFromApiDump<VkVideoDecodeH264CapabilitiesKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.EnumValue(value["maxLevelIdc"], EnumFromString_StdVideoH264LevelIdc);
    StructFromApiDump<VkOffset2D>(ctx, value["fieldOffsetGranularity"]);
}

template <> void StructFromApiDump<VkVideoDecodeH264SessionParametersAddInfoKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["stdSPSCount"]);
    StructArrayFromApiDump<StdVideoH264SequenceParameterSet>(ctx, value["pStdSPSs"], ctx.Length(value["stdSPSCount"]));
    ctx.UInt32Value(value["stdPPSCount"]);
    StructArrayFromApiDump<StdVideoH264PictureParameterSet>(ctx, value["pStdPPSs"], ctx.Length(value["stdPPSCount"]));
}

template <> void StructFromApiDump<VkVideoDecodeH264SessionParametersCreateInfoKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["maxStdSPSCount"]);
    ctx.UInt32Value(value["maxStdPPSCount"]);
    StructPtrFromApiDump<VkVideoDecodeH264SessionParametersAddInfoKHR>(ctx, value["pParametersAddInfo"]);
}

template <> void StructFromApiDump<VkVideoDecodeH264PictureInfoKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    StructPtrFromApiDump<StdVideoDecodeH264PictureInfo>(ctx, value["pStdPictureInfo"]);
    ctx.UInt32Value(value["sliceCount"]);
    ctx.UInt32Array(value["pSliceOffsets"], ctx.Length(value["sliceCount"]));
}

template <> void StructFromApiDump<VkVideoDecodeH264DpbSlotInfoKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    StructPtrFromApiDump<StdVideoDecodeH264ReferenceInfo>(ctx, value["pStdReferenceInfo"]);
}

template <> void StructFromApiDump<VkImportMemoryWin32HandleInfoKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.EnumValue(value["handleType"], EnumFromString_VkExternalMemoryHandleTypeFlagBits);
    ctx.VoidPtrValue(value["handle"]);
    ctx.StringValue(value["name"]);
}

template <> void StructFromApiDump<VkExportMemoryWin32HandleInfoKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    StructPtrFromApiDump<SECURITY_ATTRIBUTES>(ctx, value["pAttributes"]);
    ctx.UInt32Value(value["dwAccess"]);
    ctx.StringValue(value["name"]);
}

template <> void StructFromApiDump<VkMemoryWin32HandlePropertiesKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["memoryTypeBits"]);
}

template <> void StructFromApiDump<VkMemoryGetWin32HandleInfoKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.VulkanHandleValue(value["memory"], VK_OBJECT_TYPE_DEVICE_MEMORY);
    ctx.EnumValue(value["handleType"], EnumFromString_VkExternalMemoryHandleTypeFlagBits);
}

template <> void StructFromApiDump<VkImportMemoryFdInfoKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.EnumValue(value["handleType"], EnumFromString_VkExternalMemoryHandleTypeFlagBits);
    ctx.Int32Value(value["fd"]);
}

template <> void StructFromApiDump<VkMemoryFdPropertiesKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["memoryTypeBits"]);
}

template <> void StructFromApiDump<VkMemoryGetFdInfoKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.VulkanHandleValue(value["memory"], VK_OBJECT_TYPE_DEVICE_MEMORY);
    ctx.EnumValue(value["handleType"], EnumFromString_VkExternalMemoryHandleTypeFlagBits);
}

template <> void StructFromApiDump<VkWin32KeyedMutexAcquireReleaseInfoKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["acquireCount"]);
    ctx.VulkanHandleArray(value["pAcquireSyncs"], VK_OBJECT_TYPE_DEVICE_MEMORY, ctx.Length(value["acquireCount"]));
    ctx.UInt64Array(value["pAcquireKeys"], ctx.Length(value["acquireCount"]));
    ctx.UInt32Array(value["pAcquireTimeouts"], ctx.Length(value["acquireCount"]));
    ctx.UInt32Value(value["releaseCount"]);
    ctx.VulkanHandleArray(value["pReleaseSyncs"], VK_OBJECT_TYPE_DEVICE_MEMORY, ctx.Length(value["releaseCount"]));
    ctx.UInt64Array(value["pReleaseKeys"], ctx.Length(value["releaseCount"]));
}

template <> void StructFromApiDump<VkImportSemaphoreWin32HandleInfoKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.VulkanHandleValue(value["semaphore"], VK_OBJECT_TYPE_SEMAPHORE);
    ctx.FlagsValue(value["flags"], EnumFromString_VkSemaphoreImportFlagBits);
    ctx.EnumValue(value["handleType"], EnumFromString_VkExternalSemaphoreHandleTypeFlagBits);
    ctx.VoidPtrValue(value["handle"]);
    ctx.StringValue(value["name"]);
}

template <> void StructFromApiDump<VkExportSemaphoreWin32HandleInfoKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    StructPtrFromApiDump<SECURITY_ATTRIBUTES>(ctx, value["pAttributes"]);
    ctx.UInt32Value(value["dwAccess"]);
    ctx.StringValue(value["name"]);
}

template <> void StructFromApiDump<VkD3D12FenceSubmitInfoKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["waitSemaphoreValuesCount"]);
    ctx.UInt64Array(value["pWaitSemaphoreValues"], ctx.Length(value["waitSemaphoreValuesCount"]));
    ctx.UInt32Value(value["signalSemaphoreValuesCount"]);
    ctx.UInt64Array(value["pSignalSemaphoreValues"], ctx.Length(value["signalSemaphoreValuesCount"]));
}

template <> void StructFromApiDump<VkSemaphoreGetWin32HandleInfoKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.VulkanHandleValue(value["semaphore"], VK_OBJECT_TYPE_SEMAPHORE);
    ctx.EnumValue(value["handleType"], EnumFromString_VkExternalSemaphoreHandleTypeFlagBits);
}

template <> void StructFromApiDump<VkImportSemaphoreFdInfoKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.VulkanHandleValue(value["semaphore"], VK_OBJECT_TYPE_SEMAPHORE);
    ctx.FlagsValue(value["flags"], EnumFromString_VkSemaphoreImportFlagBits);
    ctx.EnumValue(value["handleType"], EnumFromString_VkExternalSemaphoreHandleTypeFlagBits);
    ctx.Int32Value(value["fd"]);
}

template <> void StructFromApiDump<VkSemaphoreGetFdInfoKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.VulkanHandleValue(value["semaphore"], VK_OBJECT_TYPE_SEMAPHORE);
    ctx.EnumValue(value["handleType"], EnumFromString_VkExternalSemaphoreHandleTypeFlagBits);
}

template <> void StructFromApiDump<VkRectLayerKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    StructFromApiDump<VkOffset2D>(ctx, value["offset"]);
    StructFromApiDump<VkExtent2D>(ctx, value["extent"]);
    ctx.UInt32Value(value["layer"]);
}

template <> void StructFromApiDump<VkPresentRegionKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.UInt32Value(value["rectangleCount"]);
    StructArrayFromApiDump<VkRectLayerKHR>(ctx, value["pRectangles"], ctx.Length(value["rectangleCount"]));
}

template <> void StructFromApiDump<VkPresentRegionsKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["swapchainCount"]);
    StructArrayFromApiDump<VkPresentRegionKHR>(ctx, value["pRegions"], ctx.Length(value["swapchainCount"]));
}

template <> void StructFromApiDump<VkSharedPresentSurfaceCapabilitiesKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.FlagsValue(value["sharedPresentSupportedUsageFlags"], EnumFromString_VkImageUsageFlagBits);
}

template <> void StructFromApiDump<VkImportFenceWin32HandleInfoKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.VulkanHandleValue(value["fence"], VK_OBJECT_TYPE_FENCE);
    ctx.FlagsValue(value["flags"], EnumFromString_VkFenceImportFlagBits);
    ctx.EnumValue(value["handleType"], EnumFromString_VkExternalFenceHandleTypeFlagBits);
    ctx.VoidPtrValue(value["handle"]);
    ctx.StringValue(value["name"]);
}

template <> void StructFromApiDump<VkExportFenceWin32HandleInfoKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    StructPtrFromApiDump<SECURITY_ATTRIBUTES>(ctx, value["pAttributes"]);
    ctx.UInt32Value(value["dwAccess"]);
    ctx.StringValue(value["name"]);
}

template <> void StructFromApiDump<VkFenceGetWin32HandleInfoKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.VulkanHandleValue(value["fence"], VK_OBJECT_TYPE_FENCE);
    ctx.EnumValue(value["handleType"], EnumFromString_VkExternalFenceHandleTypeFlagBits);
}

template <> void StructFromApiDump<VkImportFenceFdInfoKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.VulkanHandleValue(value["fence"], VK_OBJECT_TYPE_FENCE);
    ctx.FlagsValue(value["flags"], EnumFromString_VkFenceImportFlagBits);
    ctx.EnumValue(value["handleType"], EnumFromString_VkExternalFenceHandleTypeFlagBits);
    ctx.Int32Value(value["fd"]);
}

template <> void StructFromApiDump<VkFenceGetFdInfoKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.VulkanHandleValue(value["fence"], VK_OBJECT_TYPE_FENCE);
    ctx.EnumValue(value["handleType"], EnumFromString_VkExternalFenceHandleTypeFlagBits);
}

template <> void StructFromApiDump<VkPhysicalDevicePerformanceQueryFeaturesKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["performanceCounterQueryPools"]);
    ctx.UInt32Value(value["performanceCounterMultipleQueryPools"]);
}

template <> void StructFromApiDump<VkPhysicalDevicePerformanceQueryPropertiesKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["allowCommandBufferQueryCopies"]);
}

template <> void StructFromApiDump<VkPerformanceCounterKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.EnumValue(value["unit"], EnumFromString_VkPerformanceCounterUnitKHR);
    ctx.EnumValue(value["scope"], EnumFromString_VkPerformanceCounterScopeKHR);
    ctx.EnumValue(value["storage"], EnumFromString_VkPerformanceCounterStorageKHR);
    ctx.UInt8Array(value["uuid"]);
}

template <> void StructFromApiDump<VkPerformanceCounterDescriptionKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.FlagsValue(value["flags"], EnumFromString_VkPerformanceCounterDescriptionFlagBitsKHR);
    ctx.StringValue(value["name"]);
    ctx.StringValue(value["category"]);
    ctx.StringValue(value["description"]);
}

template <> void StructFromApiDump<VkQueryPoolPerformanceCreateInfoKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["queueFamilyIndex"]);
    ctx.UInt32Value(value["counterIndexCount"]);
    ctx.UInt32Array(value["pCounterIndices"], ctx.Length(value["counterIndexCount"]));
}

template <> void StructFromApiDump<VkAcquireProfilingLockInfoKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.FlagsValue(value["flags"], EnumFromString_VkAcquireProfilingLockFlagBitsKHR);
    ctx.UInt64Value(value["timeout"]);
}

template <> void StructFromApiDump<VkPerformanceQuerySubmitInfoKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["counterPassIndex"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceSurfaceInfo2KHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.VulkanHandleValue(value["surface"], VK_OBJECT_TYPE_SURFACE_KHR);
}

template <> void StructFromApiDump<VkSurfaceCapabilities2KHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    StructFromApiDump<VkSurfaceCapabilitiesKHR>(ctx, value["surfaceCapabilities"]);
}

template <> void StructFromApiDump<VkSurfaceFormat2KHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    StructFromApiDump<VkSurfaceFormatKHR>(ctx, value["surfaceFormat"]);
}

template <> void StructFromApiDump<VkDisplayProperties2KHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    StructFromApiDump<VkDisplayPropertiesKHR>(ctx, value["displayProperties"]);
}

template <> void StructFromApiDump<VkDisplayPlaneProperties2KHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    StructFromApiDump<VkDisplayPlanePropertiesKHR>(ctx, value["displayPlaneProperties"]);
}

template <> void StructFromApiDump<VkDisplayModeProperties2KHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    StructFromApiDump<VkDisplayModePropertiesKHR>(ctx, value["displayModeProperties"]);
}

template <> void StructFromApiDump<VkDisplayPlaneInfo2KHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.VulkanHandleValue(value["mode"], VK_OBJECT_TYPE_DISPLAY_MODE_KHR);
    ctx.UInt32Value(value["planeIndex"]);
}

template <> void StructFromApiDump<VkDisplayPlaneCapabilities2KHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    StructFromApiDump<VkDisplayPlaneCapabilitiesKHR>(ctx, value["capabilities"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceShaderBfloat16FeaturesKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["shaderBFloat16Type"]);
    ctx.UInt32Value(value["shaderBFloat16DotProduct"]);
    ctx.UInt32Value(value["shaderBFloat16CooperativeMatrix"]);
}

template <> void StructFromApiDump<VkPhysicalDevicePortabilitySubsetFeaturesKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["constantAlphaColorBlendFactors"]);
    ctx.UInt32Value(value["events"]);
    ctx.UInt32Value(value["imageViewFormatReinterpretation"]);
    ctx.UInt32Value(value["imageViewFormatSwizzle"]);
    ctx.UInt32Value(value["imageView2DOn3DImage"]);
    ctx.UInt32Value(value["multisampleArrayImage"]);
    ctx.UInt32Value(value["mutableComparisonSamplers"]);
    ctx.UInt32Value(value["pointPolygons"]);
    ctx.UInt32Value(value["samplerMipLodBias"]);
    ctx.UInt32Value(value["separateStencilMaskRef"]);
    ctx.UInt32Value(value["shaderSampleRateInterpolationFunctions"]);
    ctx.UInt32Value(value["tessellationIsolines"]);
    ctx.UInt32Value(value["tessellationPointMode"]);
    ctx.UInt32Value(value["triangleFans"]);
    ctx.UInt32Value(value["vertexAttributeAccessBeyondStride"]);
}

template <> void StructFromApiDump<VkPhysicalDevicePortabilitySubsetPropertiesKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["minVertexInputBindingStrideAlignment"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceShaderClockFeaturesKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["shaderSubgroupClock"]);
    ctx.UInt32Value(value["shaderDeviceClock"]);
}

template <> void StructFromApiDump<VkFragmentShadingRateAttachmentInfoKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    StructPtrFromApiDump<VkAttachmentReference2>(ctx, value["pFragmentShadingRateAttachment"]);
    StructFromApiDump<VkExtent2D>(ctx, value["shadingRateAttachmentTexelSize"]);
}

template <> void StructFromApiDump<VkPipelineFragmentShadingRateStateCreateInfoKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    StructFromApiDump<VkExtent2D>(ctx, value["fragmentSize"]);
    ctx.EnumArray(value["combinerOps"], EnumFromString_VkFragmentShadingRateCombinerOpKHR, 2);
}

template <> void StructFromApiDump<VkPhysicalDeviceFragmentShadingRateFeaturesKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["pipelineFragmentShadingRate"]);
    ctx.UInt32Value(value["primitiveFragmentShadingRate"]);
    ctx.UInt32Value(value["attachmentFragmentShadingRate"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceFragmentShadingRatePropertiesKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    StructFromApiDump<VkExtent2D>(ctx, value["minFragmentShadingRateAttachmentTexelSize"]);
    StructFromApiDump<VkExtent2D>(ctx, value["maxFragmentShadingRateAttachmentTexelSize"]);
    ctx.UInt32Value(value["maxFragmentShadingRateAttachmentTexelSizeAspectRatio"]);
    ctx.UInt32Value(value["primitiveFragmentShadingRateWithMultipleViewports"]);
    ctx.UInt32Value(value["layeredShadingRateAttachments"]);
    ctx.UInt32Value(value["fragmentShadingRateNonTrivialCombinerOps"]);
    StructFromApiDump<VkExtent2D>(ctx, value["maxFragmentSize"]);
    ctx.UInt32Value(value["maxFragmentSizeAspectRatio"]);
    ctx.UInt32Value(value["maxFragmentShadingRateCoverageSamples"]);
    ctx.EnumValue(value["maxFragmentShadingRateRasterizationSamples"], EnumFromString_VkSampleCountFlagBits);
    ctx.UInt32Value(value["fragmentShadingRateWithShaderDepthStencilWrites"]);
    ctx.UInt32Value(value["fragmentShadingRateWithSampleMask"]);
    ctx.UInt32Value(value["fragmentShadingRateWithShaderSampleMask"]);
    ctx.UInt32Value(value["fragmentShadingRateWithConservativeRasterization"]);
    ctx.UInt32Value(value["fragmentShadingRateWithFragmentShaderInterlock"]);
    ctx.UInt32Value(value["fragmentShadingRateWithCustomSampleLocations"]);
    ctx.UInt32Value(value["fragmentShadingRateStrictMultiplyCombiner"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceFragmentShadingRateKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.FlagsValue(value["sampleCounts"], EnumFromString_VkSampleCountFlagBits);
    StructFromApiDump<VkExtent2D>(ctx, value["fragmentSize"]);
}

template <> void StructFromApiDump<VkRenderingFragmentShadingRateAttachmentInfoKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.VulkanHandleValue(value["imageView"], VK_OBJECT_TYPE_IMAGE_VIEW);
    ctx.EnumValue(value["imageLayout"], EnumFromString_VkImageLayout);
    StructFromApiDump<VkExtent2D>(ctx, value["shadingRateAttachmentTexelSize"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceShaderConstantDataFeaturesKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["shaderConstantData"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceShaderAbortFeaturesKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["shaderAbort"]);
}

template <> void StructFromApiDump<VkDeviceFaultShaderAbortMessageInfoKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt64Value(value["messageDataSize"]);
    ctx.UInt8Array(value["pMessageData"], ctx.Length(value["messageDataSize"]));
}

template <> void StructFromApiDump<VkPhysicalDeviceShaderAbortPropertiesKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt64Value(value["maxShaderAbortMessageSize"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceShaderQuadControlFeaturesKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["shaderQuadControl"]);
}

template <> void StructFromApiDump<VkSurfaceProtectedCapabilitiesKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["supportsProtected"]);
}

template <> void StructFromApiDump<VkPhysicalDevicePresentWaitFeaturesKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["presentWait"]);
}

template <> void StructFromApiDump<VkPhysicalDevicePipelineExecutablePropertiesFeaturesKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["pipelineExecutableInfo"]);
}

template <> void StructFromApiDump<VkPipelineInfoKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.VulkanHandleValue(value["pipeline"], VK_OBJECT_TYPE_PIPELINE);
}

template <> void StructFromApiDump<VkPipelineExecutablePropertiesKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.FlagsValue(value["stages"], EnumFromString_VkShaderStageFlagBits);
    ctx.StringValue(value["name"]);
    ctx.StringValue(value["description"]);
    ctx.UInt32Value(value["subgroupSize"]);
}

template <> void StructFromApiDump<VkPipelineExecutableInfoKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.VulkanHandleValue(value["pipeline"], VK_OBJECT_TYPE_PIPELINE);
    ctx.UInt32Value(value["executableIndex"]);
}

template <> void StructFromApiDump<VkPipelineExecutableStatisticKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.StringValue(value["name"]);
    ctx.StringValue(value["description"]);
    ctx.EnumValue(value["format"], EnumFromString_VkPipelineExecutableStatisticFormatKHR);
    StructFromApiDump<VkPipelineExecutableStatisticValueKHR>(ctx, value["value"]);
}

template <> void StructFromApiDump<VkPipelineExecutableInternalRepresentationKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.StringValue(value["name"]);
    ctx.StringValue(value["description"]);
    ctx.UInt32Value(value["isText"]);
    ctx.SizeTValue(value["dataSize"]);
    ctx.UInt8Array(value["pData"], ctx.Length(value["dataSize"]));
}

template <> void StructFromApiDump<VkPipelineLibraryCreateInfoKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["libraryCount"]);
    ctx.VulkanHandleArray(value["pLibraries"], VK_OBJECT_TYPE_PIPELINE, ctx.Length(value["libraryCount"]));
}

template <> void StructFromApiDump<VkPresentIdKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["swapchainCount"]);
    ctx.UInt64Array(value["pPresentIds"], ctx.Length(value["swapchainCount"]));
}

template <> void StructFromApiDump<VkPhysicalDevicePresentIdFeaturesKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["presentId"]);
}

template <> void StructFromApiDump<VkVideoEncodeInfoKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.FlagsValue(value["flags"], EnumFromString_VkVideoEncodeFlagBitsKHR);
    ctx.VulkanHandleValue(value["dstBuffer"], VK_OBJECT_TYPE_BUFFER);
    ctx.UInt64Value(value["dstBufferOffset"]);
    ctx.UInt64Value(value["dstBufferRange"]);
    StructFromApiDump<VkVideoPictureResourceInfoKHR>(ctx, value["srcPictureResource"]);
    StructPtrFromApiDump<VkVideoReferenceSlotInfoKHR>(ctx, value["pSetupReferenceSlot"]);
    ctx.UInt32Value(value["referenceSlotCount"]);
    StructArrayFromApiDump<VkVideoReferenceSlotInfoKHR>(ctx, value["pReferenceSlots"], ctx.Length(value["referenceSlotCount"]));
    ctx.UInt32Value(value["precedingExternallyEncodedBytes"]);
}

template <> void StructFromApiDump<VkVideoEncodeCapabilitiesKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.FlagsValue(value["flags"], EnumFromString_VkVideoEncodeCapabilityFlagBitsKHR);
    ctx.FlagsValue(value["rateControlModes"], EnumFromString_VkVideoEncodeRateControlModeFlagBitsKHR);
    ctx.UInt32Value(value["maxRateControlLayers"]);
    ctx.UInt64Value(value["maxBitrate"]);
    ctx.UInt32Value(value["maxQualityLevels"]);
    StructFromApiDump<VkExtent2D>(ctx, value["encodeInputPictureGranularity"]);
    ctx.FlagsValue(value["supportedEncodeFeedbackFlags"], EnumFromString_VkVideoEncodeFeedbackFlagBitsKHR);
}

template <> void StructFromApiDump<VkQueryPoolVideoEncodeFeedbackCreateInfoKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.FlagsValue(value["encodeFeedbackFlags"], EnumFromString_VkVideoEncodeFeedbackFlagBitsKHR);
}

template <> void StructFromApiDump<VkVideoEncodeUsageInfoKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.FlagsValue(value["videoUsageHints"], EnumFromString_VkVideoEncodeUsageFlagBitsKHR);
    ctx.FlagsValue(value["videoContentHints"], EnumFromString_VkVideoEncodeContentFlagBitsKHR);
    ctx.EnumValue(value["tuningMode"], EnumFromString_VkVideoEncodeTuningModeKHR);
}

template <> void StructFromApiDump<VkVideoEncodeRateControlLayerInfoKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt64Value(value["averageBitrate"]);
    ctx.UInt64Value(value["maxBitrate"]);
    ctx.UInt32Value(value["frameRateNumerator"]);
    ctx.UInt32Value(value["frameRateDenominator"]);
}

template <> void StructFromApiDump<VkVideoEncodeRateControlInfoKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.FlagsValue(value["flags"]);
    ctx.EnumValue(value["rateControlMode"], EnumFromString_VkVideoEncodeRateControlModeFlagBitsKHR);
    ctx.UInt32Value(value["layerCount"]);
    StructArrayFromApiDump<VkVideoEncodeRateControlLayerInfoKHR>(ctx, value["pLayers"], ctx.Length(value["layerCount"]));
    ctx.UInt32Value(value["virtualBufferSizeInMs"]);
    ctx.UInt32Value(value["initialVirtualBufferSizeInMs"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceVideoEncodeQualityLevelInfoKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    StructPtrFromApiDump<VkVideoProfileInfoKHR>(ctx, value["pVideoProfile"]);
    ctx.UInt32Value(value["qualityLevel"]);
}

template <> void StructFromApiDump<VkVideoEncodeQualityLevelPropertiesKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.EnumValue(value["preferredRateControlMode"], EnumFromString_VkVideoEncodeRateControlModeFlagBitsKHR);
    ctx.UInt32Value(value["preferredRateControlLayerCount"]);
}

template <> void StructFromApiDump<VkVideoEncodeQualityLevelInfoKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["qualityLevel"]);
}

template <> void StructFromApiDump<VkVideoEncodeSessionParametersGetInfoKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.VulkanHandleValue(value["videoSessionParameters"], VK_OBJECT_TYPE_VIDEO_SESSION_PARAMETERS_KHR);
}

template <> void StructFromApiDump<VkVideoEncodeSessionParametersFeedbackInfoKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["hasOverrides"]);
}

template <> void StructFromApiDump<VkDeviceAddressRangeKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.UInt64Value(value["address"]);
    ctx.UInt64Value(value["size"]);
}

template <> void StructFromApiDump<VkStridedDeviceAddressRangeKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.UInt64Value(value["address"]);
    ctx.UInt64Value(value["size"]);
    ctx.UInt64Value(value["stride"]);
}

template <> void StructFromApiDump<VkDeviceMemoryCopyKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    StructFromApiDump<VkDeviceAddressRangeKHR>(ctx, value["srcRange"]);
    ctx.FlagsValue(value["srcFlags"], EnumFromString_VkAddressCommandFlagBitsKHR);
    StructFromApiDump<VkDeviceAddressRangeKHR>(ctx, value["dstRange"]);
    ctx.FlagsValue(value["dstFlags"], EnumFromString_VkAddressCommandFlagBitsKHR);
}

template <> void StructFromApiDump<VkCopyDeviceMemoryInfoKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["regionCount"]);
    StructArrayFromApiDump<VkDeviceMemoryCopyKHR>(ctx, value["pRegions"], ctx.Length(value["regionCount"]));
}

template <> void StructFromApiDump<VkDeviceMemoryImageCopyKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    StructFromApiDump<VkDeviceAddressRangeKHR>(ctx, value["addressRange"]);
    ctx.FlagsValue(value["addressFlags"], EnumFromString_VkAddressCommandFlagBitsKHR);
    ctx.UInt32Value(value["addressRowLength"]);
    ctx.UInt32Value(value["addressImageHeight"]);
    StructFromApiDump<VkImageSubresourceLayers>(ctx, value["imageSubresource"]);
    ctx.EnumValue(value["imageLayout"], EnumFromString_VkImageLayout);
    StructFromApiDump<VkOffset3D>(ctx, value["imageOffset"]);
    StructFromApiDump<VkExtent3D>(ctx, value["imageExtent"]);
}

template <> void StructFromApiDump<VkCopyDeviceMemoryImageInfoKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.VulkanHandleValue(value["image"], VK_OBJECT_TYPE_IMAGE);
    ctx.UInt32Value(value["regionCount"]);
    StructArrayFromApiDump<VkDeviceMemoryImageCopyKHR>(ctx, value["pRegions"], ctx.Length(value["regionCount"]));
}

template <> void StructFromApiDump<VkMemoryRangeBarrierKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.Flags64Value(value["srcStageMask"], EnumFromString_VkPipelineStageFlagBits2);
    ctx.Flags64Value(value["srcAccessMask"], EnumFromString_VkAccessFlagBits2);
    ctx.Flags64Value(value["dstStageMask"], EnumFromString_VkPipelineStageFlagBits2);
    ctx.Flags64Value(value["dstAccessMask"], EnumFromString_VkAccessFlagBits2);
    ctx.UInt32Value(value["srcQueueFamilyIndex"]);
    ctx.UInt32Value(value["dstQueueFamilyIndex"]);
    StructFromApiDump<VkDeviceAddressRangeKHR>(ctx, value["addressRange"]);
    ctx.FlagsValue(value["addressFlags"], EnumFromString_VkAddressCommandFlagBitsKHR);
}

template <> void StructFromApiDump<VkMemoryRangeBarriersInfoKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["memoryRangeBarrierCount"]);
    StructArrayFromApiDump<VkMemoryRangeBarrierKHR>(ctx, value["pMemoryRangeBarriers"], ctx.Length(value["memoryRangeBarrierCount"]));
}

template <> void StructFromApiDump<VkPhysicalDeviceDeviceAddressCommandsFeaturesKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["deviceAddressCommands"]);
}

template <> void StructFromApiDump<VkBindIndexBuffer3InfoKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    StructFromApiDump<VkDeviceAddressRangeKHR>(ctx, value["addressRange"]);
    ctx.FlagsValue(value["addressFlags"], EnumFromString_VkAddressCommandFlagBitsKHR);
    ctx.EnumValue(value["indexType"], EnumFromString_VkIndexType);
}

template <> void StructFromApiDump<VkBindVertexBuffer3InfoKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["setStride"]);
    StructFromApiDump<VkStridedDeviceAddressRangeKHR>(ctx, value["addressRange"]);
    ctx.FlagsValue(value["addressFlags"], EnumFromString_VkAddressCommandFlagBitsKHR);
}

template <> void StructFromApiDump<VkDrawIndirect2InfoKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    StructFromApiDump<VkStridedDeviceAddressRangeKHR>(ctx, value["addressRange"]);
    ctx.FlagsValue(value["addressFlags"], EnumFromString_VkAddressCommandFlagBitsKHR);
    ctx.UInt32Value(value["drawCount"]);
}

template <> void StructFromApiDump<VkDrawIndirectCount2InfoKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    StructFromApiDump<VkStridedDeviceAddressRangeKHR>(ctx, value["addressRange"]);
    ctx.FlagsValue(value["addressFlags"], EnumFromString_VkAddressCommandFlagBitsKHR);
    StructFromApiDump<VkDeviceAddressRangeKHR>(ctx, value["countAddressRange"]);
    ctx.FlagsValue(value["countAddressFlags"], EnumFromString_VkAddressCommandFlagBitsKHR);
    ctx.UInt32Value(value["maxDrawCount"]);
}

template <> void StructFromApiDump<VkDispatchIndirect2InfoKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    StructFromApiDump<VkDeviceAddressRangeKHR>(ctx, value["addressRange"]);
    ctx.FlagsValue(value["addressFlags"], EnumFromString_VkAddressCommandFlagBitsKHR);
}

template <> void StructFromApiDump<VkConditionalRenderingBeginInfo2EXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    StructFromApiDump<VkDeviceAddressRangeKHR>(ctx, value["addressRange"]);
    ctx.FlagsValue(value["addressFlags"], EnumFromString_VkAddressCommandFlagBitsKHR);
    ctx.FlagsValue(value["flags"], EnumFromString_VkConditionalRenderingFlagBitsEXT);
}

template <> void StructFromApiDump<VkBindTransformFeedbackBuffer2InfoEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    StructFromApiDump<VkDeviceAddressRangeKHR>(ctx, value["addressRange"]);
    ctx.FlagsValue(value["addressFlags"], EnumFromString_VkAddressCommandFlagBitsKHR);
}

template <> void StructFromApiDump<VkMemoryMarkerInfoAMD>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.Flags64Value(value["stage"]);
    StructFromApiDump<VkDeviceAddressRangeKHR>(ctx, value["dstRange"]);
    ctx.FlagsValue(value["dstFlags"], EnumFromString_VkAddressCommandFlagBitsKHR);
    ctx.UInt32Value(value["marker"]);
}

template <> void StructFromApiDump<VkAccelerationStructureCreateInfo2KHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.FlagsValue(value["createFlags"], EnumFromString_VkAccelerationStructureCreateFlagBitsKHR);
    StructFromApiDump<VkDeviceAddressRangeKHR>(ctx, value["addressRange"]);
    ctx.FlagsValue(value["addressFlags"], EnumFromString_VkAddressCommandFlagBitsKHR);
    ctx.EnumValue(value["type"], EnumFromString_VkAccelerationStructureTypeKHR);
}

template <> void StructFromApiDump<VkPhysicalDeviceFragmentShaderBarycentricFeaturesKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["fragmentShaderBarycentric"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceFragmentShaderBarycentricPropertiesKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["triStripVertexOrderIndependentOfProvokingVertex"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceShaderSubgroupUniformControlFlowFeaturesKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["shaderSubgroupUniformControlFlow"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceWorkgroupMemoryExplicitLayoutFeaturesKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["workgroupMemoryExplicitLayout"]);
    ctx.UInt32Value(value["workgroupMemoryExplicitLayoutScalarBlockLayout"]);
    ctx.UInt32Value(value["workgroupMemoryExplicitLayout8BitAccess"]);
    ctx.UInt32Value(value["workgroupMemoryExplicitLayout16BitAccess"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceRayTracingMaintenance1FeaturesKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["rayTracingMaintenance1"]);
    ctx.UInt32Value(value["rayTracingPipelineTraceRaysIndirect2"]);
}

template <> void StructFromApiDump<VkTraceRaysIndirectCommand2KHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.UInt64Value(value["raygenShaderRecordAddress"]);
    ctx.UInt64Value(value["raygenShaderRecordSize"]);
    ctx.UInt64Value(value["missShaderBindingTableAddress"]);
    ctx.UInt64Value(value["missShaderBindingTableSize"]);
    ctx.UInt64Value(value["missShaderBindingTableStride"]);
    ctx.UInt64Value(value["hitShaderBindingTableAddress"]);
    ctx.UInt64Value(value["hitShaderBindingTableSize"]);
    ctx.UInt64Value(value["hitShaderBindingTableStride"]);
    ctx.UInt64Value(value["callableShaderBindingTableAddress"]);
    ctx.UInt64Value(value["callableShaderBindingTableSize"]);
    ctx.UInt64Value(value["callableShaderBindingTableStride"]);
    ctx.UInt32Value(value["width"]);
    ctx.UInt32Value(value["height"]);
    ctx.UInt32Value(value["depth"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceShaderUntypedPointersFeaturesKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["shaderUntypedPointers"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceShaderMaximalReconvergenceFeaturesKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["shaderMaximalReconvergence"]);
}

template <> void StructFromApiDump<VkSurfaceCapabilitiesPresentId2KHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["presentId2Supported"]);
}

template <> void StructFromApiDump<VkPresentId2KHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["swapchainCount"]);
    ctx.UInt64Array(value["pPresentIds"], ctx.Length(value["swapchainCount"]));
}

template <> void StructFromApiDump<VkPhysicalDevicePresentId2FeaturesKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["presentId2"]);
}

template <> void StructFromApiDump<VkSurfaceCapabilitiesPresentWait2KHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["presentWait2Supported"]);
}

template <> void StructFromApiDump<VkPhysicalDevicePresentWait2FeaturesKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["presentWait2"]);
}

template <> void StructFromApiDump<VkPresentWait2InfoKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt64Value(value["presentId"]);
    ctx.UInt64Value(value["timeout"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceRayTracingPositionFetchFeaturesKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["rayTracingPositionFetch"]);
}

template <> void StructFromApiDump<VkPhysicalDevicePipelineBinaryFeaturesKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["pipelineBinaries"]);
}

template <> void StructFromApiDump<VkPhysicalDevicePipelineBinaryPropertiesKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["pipelineBinaryInternalCache"]);
    ctx.UInt32Value(value["pipelineBinaryInternalCacheControl"]);
    ctx.UInt32Value(value["pipelineBinaryPrefersInternalCache"]);
    ctx.UInt32Value(value["pipelineBinaryPrecompiledInternalCache"]);
    ctx.UInt32Value(value["pipelineBinaryCompressedData"]);
}

template <> void StructFromApiDump<VkDevicePipelineBinaryInternalCacheControlKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["disableInternalCache"]);
}

template <> void StructFromApiDump<VkPipelineBinaryKeyKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["keySize"]);
    ctx.UInt8Array(value["key"]);
}

template <> void StructFromApiDump<VkPipelineBinaryDataKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.SizeTValue(value["dataSize"]);
    ctx.UInt8Array(value["pData"], ctx.Length(value["dataSize"]));
}

template <> void StructFromApiDump<VkPipelineBinaryKeysAndDataKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.UInt32Value(value["binaryCount"]);
    StructArrayFromApiDump<VkPipelineBinaryKeyKHR>(ctx, value["pPipelineBinaryKeys"], ctx.Length(value["binaryCount"]));
    StructArrayFromApiDump<VkPipelineBinaryDataKHR>(ctx, value["pPipelineBinaryData"], ctx.Length(value["binaryCount"]));
}

template <> void StructFromApiDump<VkPipelineCreateInfoKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
}

template <> void StructFromApiDump<VkPipelineBinaryCreateInfoKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    StructPtrFromApiDump<VkPipelineBinaryKeysAndDataKHR>(ctx, value["pKeysAndDataInfo"]);
    ctx.VulkanHandleValue(value["pipeline"], VK_OBJECT_TYPE_PIPELINE);
    StructPtrFromApiDump<VkPipelineCreateInfoKHR>(ctx, value["pPipelineCreateInfo"]);
}

template <> void StructFromApiDump<VkPipelineBinaryInfoKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["binaryCount"]);
    ctx.VulkanHandleArray(value["pPipelineBinaries"], VK_OBJECT_TYPE_PIPELINE_BINARY_KHR, ctx.Length(value["binaryCount"]));
}

template <> void StructFromApiDump<VkReleaseCapturedPipelineDataInfoKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.VulkanHandleValue(value["pipeline"], VK_OBJECT_TYPE_PIPELINE);
}

template <> void StructFromApiDump<VkPipelineBinaryDataInfoKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.VulkanHandleValue(value["pipelineBinary"], VK_OBJECT_TYPE_PIPELINE_BINARY_KHR);
}

template <> void StructFromApiDump<VkPipelineBinaryHandlesInfoKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["pipelineBinaryCount"]);
    ctx.VulkanHandleArray(value["pPipelineBinaries"], VK_OBJECT_TYPE_PIPELINE_BINARY_KHR, ctx.Length(value["pipelineBinaryCount"]));
}

template <> void StructFromApiDump<VkSurfacePresentModeKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.EnumValue(value["presentMode"], EnumFromString_VkPresentModeKHR);
}

template <> void StructFromApiDump<VkSurfacePresentScalingCapabilitiesKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.FlagsValue(value["supportedPresentScaling"], EnumFromString_VkPresentScalingFlagBitsKHR);
    ctx.FlagsValue(value["supportedPresentGravityX"], EnumFromString_VkPresentGravityFlagBitsKHR);
    ctx.FlagsValue(value["supportedPresentGravityY"], EnumFromString_VkPresentGravityFlagBitsKHR);
    StructFromApiDump<VkExtent2D>(ctx, value["minScaledImageExtent"]);
    StructFromApiDump<VkExtent2D>(ctx, value["maxScaledImageExtent"]);
}

template <> void StructFromApiDump<VkSurfacePresentModeCompatibilityKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["presentModeCount"]);
    ctx.EnumArray(value["pPresentModes"], EnumFromString_VkPresentModeKHR, ctx.Length(value["presentModeCount"]));
}

template <> void StructFromApiDump<VkPhysicalDeviceSwapchainMaintenance1FeaturesKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["swapchainMaintenance1"]);
}

template <> void StructFromApiDump<VkSwapchainPresentFenceInfoKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["swapchainCount"]);
    ctx.VulkanHandleArray(value["pFences"], VK_OBJECT_TYPE_FENCE, ctx.Length(value["swapchainCount"]));
}

template <> void StructFromApiDump<VkSwapchainPresentModesCreateInfoKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["presentModeCount"]);
    ctx.EnumArray(value["pPresentModes"], EnumFromString_VkPresentModeKHR, ctx.Length(value["presentModeCount"]));
}

template <> void StructFromApiDump<VkSwapchainPresentModeInfoKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["swapchainCount"]);
    ctx.EnumArray(value["pPresentModes"], EnumFromString_VkPresentModeKHR, ctx.Length(value["swapchainCount"]));
}

template <> void StructFromApiDump<VkSwapchainPresentScalingCreateInfoKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.FlagsValue(value["scalingBehavior"], EnumFromString_VkPresentScalingFlagBitsKHR);
    ctx.FlagsValue(value["presentGravityX"], EnumFromString_VkPresentGravityFlagBitsKHR);
    ctx.FlagsValue(value["presentGravityY"], EnumFromString_VkPresentGravityFlagBitsKHR);
}

template <> void StructFromApiDump<VkReleaseSwapchainImagesInfoKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.VulkanHandleValue(value["swapchain"], VK_OBJECT_TYPE_SWAPCHAIN_KHR);
    ctx.UInt32Value(value["imageIndexCount"]);
    ctx.UInt32Array(value["pImageIndices"], ctx.Length(value["imageIndexCount"]));
}

template <> void StructFromApiDump<VkPhysicalDeviceInternallySynchronizedQueuesFeaturesKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["internallySynchronizedQueues"]);
}

template <> void StructFromApiDump<VkCooperativeMatrixPropertiesKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["MSize"]);
    ctx.UInt32Value(value["NSize"]);
    ctx.UInt32Value(value["KSize"]);
    ctx.EnumValue(value["AType"], EnumFromString_VkComponentTypeKHR);
    ctx.EnumValue(value["BType"], EnumFromString_VkComponentTypeKHR);
    ctx.EnumValue(value["CType"], EnumFromString_VkComponentTypeKHR);
    ctx.EnumValue(value["ResultType"], EnumFromString_VkComponentTypeKHR);
    ctx.UInt32Value(value["saturatingAccumulation"]);
    ctx.EnumValue(value["scope"], EnumFromString_VkScopeKHR);
}

template <> void StructFromApiDump<VkPhysicalDeviceCooperativeMatrixFeaturesKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["cooperativeMatrix"]);
    ctx.UInt32Value(value["cooperativeMatrixRobustBufferAccess"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceCooperativeMatrixPropertiesKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.FlagsValue(value["cooperativeMatrixSupportedStages"], EnumFromString_VkShaderStageFlagBits);
}

template <> void StructFromApiDump<VkPhysicalDeviceComputeShaderDerivativesFeaturesKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["computeDerivativeGroupQuads"]);
    ctx.UInt32Value(value["computeDerivativeGroupLinear"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceComputeShaderDerivativesPropertiesKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["meshAndTaskShaderDerivatives"]);
}

template <> void StructFromApiDump<VkVideoDecodeAV1ProfileInfoKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.EnumValue(value["stdProfile"], EnumFromString_StdVideoAV1Profile);
    ctx.UInt32Value(value["filmGrainSupport"]);
}

template <> void StructFromApiDump<VkVideoDecodeAV1CapabilitiesKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.EnumValue(value["maxLevel"], EnumFromString_StdVideoAV1Level);
}

template <> void StructFromApiDump<VkVideoDecodeAV1SessionParametersCreateInfoKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    StructPtrFromApiDump<StdVideoAV1SequenceHeader>(ctx, value["pStdSequenceHeader"]);
}

template <> void StructFromApiDump<VkVideoDecodeAV1PictureInfoKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    StructPtrFromApiDump<StdVideoDecodeAV1PictureInfo>(ctx, value["pStdPictureInfo"]);
    ctx.Int32Array(value["referenceNameSlotIndices"]);
    ctx.UInt32Value(value["frameHeaderOffset"]);
    ctx.UInt32Value(value["tileCount"]);
    ctx.UInt32Array(value["pTileOffsets"], ctx.Length(value["tileCount"]));
    ctx.UInt32Array(value["pTileSizes"], ctx.Length(value["tileCount"]));
}

template <> void StructFromApiDump<VkVideoDecodeAV1DpbSlotInfoKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    StructPtrFromApiDump<StdVideoDecodeAV1ReferenceInfo>(ctx, value["pStdReferenceInfo"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceVideoEncodeAV1FeaturesKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["videoEncodeAV1"]);
}

template <> void StructFromApiDump<VkVideoEncodeAV1CapabilitiesKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.FlagsValue(value["flags"], EnumFromString_VkVideoEncodeAV1CapabilityFlagBitsKHR);
    ctx.EnumValue(value["maxLevel"], EnumFromString_StdVideoAV1Level);
    StructFromApiDump<VkExtent2D>(ctx, value["codedPictureAlignment"]);
    StructFromApiDump<VkExtent2D>(ctx, value["maxTiles"]);
    StructFromApiDump<VkExtent2D>(ctx, value["minTileSize"]);
    StructFromApiDump<VkExtent2D>(ctx, value["maxTileSize"]);
    ctx.FlagsValue(value["superblockSizes"], EnumFromString_VkVideoEncodeAV1SuperblockSizeFlagBitsKHR);
    ctx.UInt32Value(value["maxSingleReferenceCount"]);
    ctx.UInt32Value(value["singleReferenceNameMask"]);
    ctx.UInt32Value(value["maxUnidirectionalCompoundReferenceCount"]);
    ctx.UInt32Value(value["maxUnidirectionalCompoundGroup1ReferenceCount"]);
    ctx.UInt32Value(value["unidirectionalCompoundReferenceNameMask"]);
    ctx.UInt32Value(value["maxBidirectionalCompoundReferenceCount"]);
    ctx.UInt32Value(value["maxBidirectionalCompoundGroup1ReferenceCount"]);
    ctx.UInt32Value(value["maxBidirectionalCompoundGroup2ReferenceCount"]);
    ctx.UInt32Value(value["bidirectionalCompoundReferenceNameMask"]);
    ctx.UInt32Value(value["maxTemporalLayerCount"]);
    ctx.UInt32Value(value["maxSpatialLayerCount"]);
    ctx.UInt32Value(value["maxOperatingPoints"]);
    ctx.UInt32Value(value["minQIndex"]);
    ctx.UInt32Value(value["maxQIndex"]);
    ctx.UInt32Value(value["prefersGopRemainingFrames"]);
    ctx.UInt32Value(value["requiresGopRemainingFrames"]);
    ctx.FlagsValue(value["stdSyntaxFlags"], EnumFromString_VkVideoEncodeAV1StdFlagBitsKHR);
}

template <> void StructFromApiDump<VkVideoEncodeAV1QIndexKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.UInt32Value(value["intraQIndex"]);
    ctx.UInt32Value(value["predictiveQIndex"]);
    ctx.UInt32Value(value["bipredictiveQIndex"]);
}

template <> void StructFromApiDump<VkVideoEncodeAV1QualityLevelPropertiesKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.FlagsValue(value["preferredRateControlFlags"], EnumFromString_VkVideoEncodeAV1RateControlFlagBitsKHR);
    ctx.UInt32Value(value["preferredGopFrameCount"]);
    ctx.UInt32Value(value["preferredKeyFramePeriod"]);
    ctx.UInt32Value(value["preferredConsecutiveBipredictiveFrameCount"]);
    ctx.UInt32Value(value["preferredTemporalLayerCount"]);
    StructFromApiDump<VkVideoEncodeAV1QIndexKHR>(ctx, value["preferredConstantQIndex"]);
    ctx.UInt32Value(value["preferredMaxSingleReferenceCount"]);
    ctx.UInt32Value(value["preferredSingleReferenceNameMask"]);
    ctx.UInt32Value(value["preferredMaxUnidirectionalCompoundReferenceCount"]);
    ctx.UInt32Value(value["preferredMaxUnidirectionalCompoundGroup1ReferenceCount"]);
    ctx.UInt32Value(value["preferredUnidirectionalCompoundReferenceNameMask"]);
    ctx.UInt32Value(value["preferredMaxBidirectionalCompoundReferenceCount"]);
    ctx.UInt32Value(value["preferredMaxBidirectionalCompoundGroup1ReferenceCount"]);
    ctx.UInt32Value(value["preferredMaxBidirectionalCompoundGroup2ReferenceCount"]);
    ctx.UInt32Value(value["preferredBidirectionalCompoundReferenceNameMask"]);
}

template <> void StructFromApiDump<VkVideoEncodeAV1SessionCreateInfoKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["useMaxLevel"]);
    ctx.EnumValue(value["maxLevel"], EnumFromString_StdVideoAV1Level);
}

template <> void StructFromApiDump<VkVideoEncodeAV1SessionParametersCreateInfoKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    StructPtrFromApiDump<StdVideoAV1SequenceHeader>(ctx, value["pStdSequenceHeader"]);
    StructPtrFromApiDump<StdVideoEncodeAV1DecoderModelInfo>(ctx, value["pStdDecoderModelInfo"]);
    ctx.UInt32Value(value["stdOperatingPointCount"]);
    StructArrayFromApiDump<StdVideoEncodeAV1OperatingPointInfo>(ctx, value["pStdOperatingPoints"], ctx.Length(value["stdOperatingPointCount"]));
}

template <> void StructFromApiDump<VkVideoEncodeAV1PictureInfoKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.EnumValue(value["predictionMode"], EnumFromString_VkVideoEncodeAV1PredictionModeKHR);
    ctx.EnumValue(value["rateControlGroup"], EnumFromString_VkVideoEncodeAV1RateControlGroupKHR);
    ctx.UInt32Value(value["constantQIndex"]);
    StructPtrFromApiDump<StdVideoEncodeAV1PictureInfo>(ctx, value["pStdPictureInfo"]);
    ctx.Int32Array(value["referenceNameSlotIndices"]);
    ctx.UInt32Value(value["primaryReferenceCdfOnly"]);
    ctx.UInt32Value(value["generateObuExtensionHeader"]);
}

template <> void StructFromApiDump<VkVideoEncodeAV1DpbSlotInfoKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    StructPtrFromApiDump<StdVideoEncodeAV1ReferenceInfo>(ctx, value["pStdReferenceInfo"]);
}

template <> void StructFromApiDump<VkVideoEncodeAV1ProfileInfoKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.EnumValue(value["stdProfile"], EnumFromString_StdVideoAV1Profile);
}

template <> void StructFromApiDump<VkVideoEncodeAV1FrameSizeKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.UInt32Value(value["intraFrameSize"]);
    ctx.UInt32Value(value["predictiveFrameSize"]);
    ctx.UInt32Value(value["bipredictiveFrameSize"]);
}

template <> void StructFromApiDump<VkVideoEncodeAV1GopRemainingFrameInfoKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["useGopRemainingFrames"]);
    ctx.UInt32Value(value["gopRemainingIntra"]);
    ctx.UInt32Value(value["gopRemainingPredictive"]);
    ctx.UInt32Value(value["gopRemainingBipredictive"]);
}

template <> void StructFromApiDump<VkVideoEncodeAV1RateControlInfoKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.FlagsValue(value["flags"], EnumFromString_VkVideoEncodeAV1RateControlFlagBitsKHR);
    ctx.UInt32Value(value["gopFrameCount"]);
    ctx.UInt32Value(value["keyFramePeriod"]);
    ctx.UInt32Value(value["consecutiveBipredictiveFrameCount"]);
    ctx.UInt32Value(value["temporalLayerCount"]);
}

template <> void StructFromApiDump<VkVideoEncodeAV1RateControlLayerInfoKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["useMinQIndex"]);
    StructFromApiDump<VkVideoEncodeAV1QIndexKHR>(ctx, value["minQIndex"]);
    ctx.UInt32Value(value["useMaxQIndex"]);
    StructFromApiDump<VkVideoEncodeAV1QIndexKHR>(ctx, value["maxQIndex"]);
    ctx.UInt32Value(value["useMaxFrameSize"]);
    StructFromApiDump<VkVideoEncodeAV1FrameSizeKHR>(ctx, value["maxFrameSize"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceVideoDecodeVP9FeaturesKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["videoDecodeVP9"]);
}

template <> void StructFromApiDump<VkVideoDecodeVP9ProfileInfoKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.EnumValue(value["stdProfile"], EnumFromString_StdVideoVP9Profile);
}

template <> void StructFromApiDump<VkVideoDecodeVP9CapabilitiesKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.EnumValue(value["maxLevel"], EnumFromString_StdVideoVP9Level);
}

template <> void StructFromApiDump<VkVideoDecodeVP9PictureInfoKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    StructPtrFromApiDump<StdVideoDecodeVP9PictureInfo>(ctx, value["pStdPictureInfo"]);
    ctx.Int32Array(value["referenceNameSlotIndices"]);
    ctx.UInt32Value(value["uncompressedHeaderOffset"]);
    ctx.UInt32Value(value["compressedHeaderOffset"]);
    ctx.UInt32Value(value["tilesOffset"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceVideoMaintenance1FeaturesKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["videoMaintenance1"]);
}

template <> void StructFromApiDump<VkVideoInlineQueryInfoKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.VulkanHandleValue(value["queryPool"], VK_OBJECT_TYPE_QUERY_POOL);
    ctx.UInt32Value(value["firstQuery"]);
    ctx.UInt32Value(value["queryCount"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceUnifiedImageLayoutsFeaturesKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["unifiedImageLayouts"]);
    ctx.UInt32Value(value["unifiedImageLayoutsVideo"]);
}

template <> void StructFromApiDump<VkAttachmentFeedbackLoopInfoEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["feedbackLoopEnable"]);
}

template <> void StructFromApiDump<VkCalibratedTimestampInfoKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.EnumValue(value["timeDomain"], EnumFromString_VkTimeDomainKHR);
}

template <> void StructFromApiDump<VkSetDescriptorBufferOffsetsInfoEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.FlagsValue(value["stageFlags"], EnumFromString_VkShaderStageFlagBits);
    ctx.VulkanHandleValue(value["layout"], VK_OBJECT_TYPE_PIPELINE_LAYOUT);
    ctx.UInt32Value(value["firstSet"]);
    ctx.UInt32Value(value["setCount"]);
    ctx.UInt32Array(value["pBufferIndices"], ctx.Length(value["setCount"]));
    ctx.UInt64Array(value["pOffsets"], ctx.Length(value["setCount"]));
}

template <> void StructFromApiDump<VkBindDescriptorBufferEmbeddedSamplersInfoEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.FlagsValue(value["stageFlags"], EnumFromString_VkShaderStageFlagBits);
    ctx.VulkanHandleValue(value["layout"], VK_OBJECT_TYPE_PIPELINE_LAYOUT);
    ctx.UInt32Value(value["set"]);
}

template <> void StructFromApiDump<VkCopyMemoryIndirectCommandKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.UInt64Value(value["srcAddress"]);
    ctx.UInt64Value(value["dstAddress"]);
    ctx.UInt64Value(value["size"]);
}

template <> void StructFromApiDump<VkCopyMemoryIndirectInfoKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.FlagsValue(value["srcCopyFlags"], EnumFromString_VkAddressCopyFlagBitsKHR);
    ctx.FlagsValue(value["dstCopyFlags"], EnumFromString_VkAddressCopyFlagBitsKHR);
    ctx.UInt32Value(value["copyCount"]);
    StructFromApiDump<VkStridedDeviceAddressRangeKHR>(ctx, value["copyAddressRange"]);
}

template <> void StructFromApiDump<VkCopyMemoryToImageIndirectCommandKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.UInt64Value(value["srcAddress"]);
    ctx.UInt32Value(value["bufferRowLength"]);
    ctx.UInt32Value(value["bufferImageHeight"]);
    StructFromApiDump<VkImageSubresourceLayers>(ctx, value["imageSubresource"]);
    StructFromApiDump<VkOffset3D>(ctx, value["imageOffset"]);
    StructFromApiDump<VkExtent3D>(ctx, value["imageExtent"]);
}

template <> void StructFromApiDump<VkCopyMemoryToImageIndirectInfoKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.FlagsValue(value["srcCopyFlags"], EnumFromString_VkAddressCopyFlagBitsKHR);
    ctx.UInt32Value(value["copyCount"]);
    StructFromApiDump<VkStridedDeviceAddressRangeKHR>(ctx, value["copyAddressRange"]);
    ctx.VulkanHandleValue(value["dstImage"], VK_OBJECT_TYPE_IMAGE);
    ctx.EnumValue(value["dstImageLayout"], EnumFromString_VkImageLayout);
    StructArrayFromApiDump<VkImageSubresourceLayers>(ctx, value["pImageSubresources"], ctx.Length(value["copyCount"]));
}

template <> void StructFromApiDump<VkPhysicalDeviceCopyMemoryIndirectFeaturesKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["indirectMemoryCopy"]);
    ctx.UInt32Value(value["indirectMemoryToImageCopy"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceCopyMemoryIndirectPropertiesKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.FlagsValue(value["supportedQueues"], EnumFromString_VkQueueFlagBits);
}

template <> void StructFromApiDump<VkVideoEncodeIntraRefreshCapabilitiesKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.FlagsValue(value["intraRefreshModes"], EnumFromString_VkVideoEncodeIntraRefreshModeFlagBitsKHR);
    ctx.UInt32Value(value["maxIntraRefreshCycleDuration"]);
    ctx.UInt32Value(value["maxIntraRefreshActiveReferencePictures"]);
    ctx.UInt32Value(value["partitionIndependentIntraRefreshRegions"]);
    ctx.UInt32Value(value["nonRectangularIntraRefreshRegions"]);
}

template <> void StructFromApiDump<VkVideoEncodeSessionIntraRefreshCreateInfoKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.EnumValue(value["intraRefreshMode"], EnumFromString_VkVideoEncodeIntraRefreshModeFlagBitsKHR);
}

template <> void StructFromApiDump<VkVideoEncodeIntraRefreshInfoKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["intraRefreshCycleDuration"]);
    ctx.UInt32Value(value["intraRefreshIndex"]);
}

template <> void StructFromApiDump<VkVideoReferenceIntraRefreshInfoKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["dirtyIntraRefreshRegions"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceVideoEncodeIntraRefreshFeaturesKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["videoEncodeIntraRefresh"]);
}

template <> void StructFromApiDump<VkVideoEncodeQuantizationMapCapabilitiesKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    StructFromApiDump<VkExtent2D>(ctx, value["maxQuantizationMapExtent"]);
}

template <> void StructFromApiDump<VkVideoFormatQuantizationMapPropertiesKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    StructFromApiDump<VkExtent2D>(ctx, value["quantizationMapTexelSize"]);
}

template <> void StructFromApiDump<VkVideoEncodeQuantizationMapInfoKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.VulkanHandleValue(value["quantizationMap"], VK_OBJECT_TYPE_IMAGE_VIEW);
    StructFromApiDump<VkExtent2D>(ctx, value["quantizationMapExtent"]);
}

template <> void StructFromApiDump<VkVideoEncodeQuantizationMapSessionParametersCreateInfoKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    StructFromApiDump<VkExtent2D>(ctx, value["quantizationMapTexelSize"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceVideoEncodeQuantizationMapFeaturesKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["videoEncodeQuantizationMap"]);
}

template <> void StructFromApiDump<VkVideoEncodeH264QuantizationMapCapabilitiesKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.Int32Value(value["minQpDelta"]);
    ctx.Int32Value(value["maxQpDelta"]);
}

template <> void StructFromApiDump<VkVideoEncodeH265QuantizationMapCapabilitiesKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.Int32Value(value["minQpDelta"]);
    ctx.Int32Value(value["maxQpDelta"]);
}

template <> void StructFromApiDump<VkVideoFormatH265QuantizationMapPropertiesKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.FlagsValue(value["compatibleCtbSizes"], EnumFromString_VkVideoEncodeH265CtbSizeFlagBitsKHR);
}

template <> void StructFromApiDump<VkVideoEncodeAV1QuantizationMapCapabilitiesKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.Int32Value(value["minQIndexDelta"]);
    ctx.Int32Value(value["maxQIndexDelta"]);
}

template <> void StructFromApiDump<VkVideoFormatAV1QuantizationMapPropertiesKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.FlagsValue(value["compatibleSuperblockSizes"], EnumFromString_VkVideoEncodeAV1SuperblockSizeFlagBitsKHR);
}

template <> void StructFromApiDump<VkPhysicalDeviceShaderRelaxedExtendedInstructionFeaturesKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["shaderRelaxedExtendedInstruction"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceMaintenance7FeaturesKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["maintenance7"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceMaintenance7PropertiesKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["robustFragmentShadingRateAttachmentAccess"]);
    ctx.UInt32Value(value["separateDepthStencilAttachmentAccess"]);
    ctx.UInt32Value(value["maxDescriptorSetTotalUniformBuffersDynamic"]);
    ctx.UInt32Value(value["maxDescriptorSetTotalStorageBuffersDynamic"]);
    ctx.UInt32Value(value["maxDescriptorSetTotalBuffersDynamic"]);
    ctx.UInt32Value(value["maxDescriptorSetUpdateAfterBindTotalUniformBuffersDynamic"]);
    ctx.UInt32Value(value["maxDescriptorSetUpdateAfterBindTotalStorageBuffersDynamic"]);
    ctx.UInt32Value(value["maxDescriptorSetUpdateAfterBindTotalBuffersDynamic"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceLayeredApiPropertiesKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["vendorID"]);
    ctx.UInt32Value(value["deviceID"]);
    ctx.EnumValue(value["layeredAPI"], EnumFromString_VkPhysicalDeviceLayeredApiKHR);
    ctx.StringValue(value["deviceName"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceLayeredApiPropertiesListKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["layeredApiCount"]);
    StructArrayFromApiDump<VkPhysicalDeviceLayeredApiPropertiesKHR>(ctx, value["pLayeredApis"], ctx.Length(value["layeredApiCount"]));
}

template <> void StructFromApiDump<VkPhysicalDeviceLayeredApiVulkanPropertiesKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    StructFromApiDump<VkPhysicalDeviceProperties2>(ctx, value["properties"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceFaultFeaturesKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["deviceFault"]);
    ctx.UInt32Value(value["deviceFaultVendorBinary"]);
    ctx.UInt32Value(value["deviceFaultReportMasked"]);
    ctx.UInt32Value(value["deviceFaultDeviceLostOnMasked"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceFaultPropertiesKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["maxDeviceFaultCount"]);
}

template <> void StructFromApiDump<VkDeviceFaultAddressInfoKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["addressType"], EnumFromString_VkDeviceFaultAddressTypeKHR);
    ctx.UInt64Value(value["reportedAddress"]);
    ctx.UInt64Value(value["addressPrecision"]);
}

template <> void StructFromApiDump<VkDeviceFaultVendorInfoKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.StringValue(value["description"]);
    ctx.UInt64Value(value["vendorFaultCode"]);
    ctx.UInt64Value(value["vendorFaultData"]);
}

template <> void StructFromApiDump<VkDeviceFaultInfoKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.FlagsValue(value["flags"], EnumFromString_VkDeviceFaultFlagBitsKHR);
    ctx.UInt64Value(value["groupId"]);
    ctx.StringValue(value["description"]);
    StructFromApiDump<VkDeviceFaultAddressInfoKHR>(ctx, value["faultAddressInfo"]);
    StructFromApiDump<VkDeviceFaultAddressInfoKHR>(ctx, value["instructionAddressInfo"]);
    StructFromApiDump<VkDeviceFaultVendorInfoKHR>(ctx, value["vendorInfo"]);
}

template <> void StructFromApiDump<VkDeviceFaultDebugInfoKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["vendorBinarySize"]);
    ctx.UInt8Array(value["pVendorBinaryData"], ctx.Length(value["vendorBinarySize"]));
}

template <> void StructFromApiDump<VkDeviceFaultVendorBinaryHeaderVersionOneKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.UInt32Value(value["headerSize"]);
    ctx.EnumValue(value["headerVersion"], EnumFromString_VkDeviceFaultVendorBinaryHeaderVersionKHR);
    ctx.UInt32Value(value["vendorID"]);
    ctx.UInt32Value(value["deviceID"]);
    ctx.UInt32Value(value["driverVersion"]);
    ctx.UInt8Array(value["pipelineCacheUUID"]);
    ctx.UInt32Value(value["applicationNameOffset"]);
    ctx.UInt32Value(value["applicationVersion"]);
    ctx.UInt32Value(value["engineNameOffset"]);
    ctx.UInt32Value(value["engineVersion"]);
    ctx.UInt32Value(value["apiVersion"]);
}

template <> void StructFromApiDump<VkMemoryBarrierAccessFlags3KHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.Flags64Value(value["srcAccessMask3"], EnumFromString_VkAccessFlagBits3KHR);
    ctx.Flags64Value(value["dstAccessMask3"], EnumFromString_VkAccessFlagBits3KHR);
}

template <> void StructFromApiDump<VkPhysicalDeviceMaintenance8FeaturesKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["maintenance8"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceShaderFmaFeaturesKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["shaderFmaFloat16"]);
    ctx.UInt32Value(value["shaderFmaFloat32"]);
    ctx.UInt32Value(value["shaderFmaFloat64"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceMaintenance9FeaturesKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["maintenance9"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceMaintenance9PropertiesKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["image2DViewOf3DSparse"]);
    ctx.EnumValue(value["defaultVertexAttributeValue"], EnumFromString_VkDefaultVertexAttributeValueKHR);
}

template <> void StructFromApiDump<VkQueueFamilyOwnershipTransferPropertiesKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["optimalImageTransferToQueueFamilies"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceVideoEncodeFeedback2FeaturesKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["videoEncodeFeedback2"]);
}

template <> void StructFromApiDump<VkVideoEncodeFeedback2CapabilitiesKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["maxPerPartitionFeedbackEntries"]);
    ctx.FlagsValue(value["supportedPerPartitionEncodeFeedbackFlags"], EnumFromString_VkVideoEncodePerPartitionFeedbackFlagBitsKHR);
}

template <> void StructFromApiDump<VkQueryPoolVideoEncodePerPartitionFeedbackCreateInfoKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["maxPerPartitionFeedbackEntries"]);
    ctx.FlagsValue(value["perPartitionEncodeFeedbackFlags"], EnumFromString_VkVideoEncodePerPartitionFeedbackFlagBitsKHR);
}

template <> void StructFromApiDump<VkPhysicalDeviceDepthClampZeroOneFeaturesKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["depthClampZeroOne"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceRobustness2FeaturesKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["robustBufferAccess2"]);
    ctx.UInt32Value(value["robustImageAccess2"]);
    ctx.UInt32Value(value["nullDescriptor"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceRobustness2PropertiesKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt64Value(value["robustStorageBufferAccessSizeAlignment"]);
    ctx.UInt64Value(value["robustUniformBufferAccessSizeAlignment"]);
}

template <> void StructFromApiDump<VkPhysicalDevicePresentModeFifoLatestReadyFeaturesKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["presentModeFifoLatestReady"]);
}

template <> void StructFromApiDump<VkMicromapUsageKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.UInt32Value(value["count"]);
    ctx.UInt32Value(value["subdivisionLevel"]);
    ctx.EnumValue(value["format"], EnumFromString_VkOpacityMicromapFormatKHR);
}

template <> void StructFromApiDump<VkAccelerationStructureGeometryMicromapDataKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["usageCountsCount"]);
    StructArrayFromApiDump<VkMicromapUsageKHR>(ctx, value["pUsageCounts"], ctx.Length(value["usageCountsCount"]));
    StructArrayFromApiDump<VkMicromapUsageKHR>(ctx, value["ppUsageCounts"], (ctx.Length(value["usageCountsCount"]),1));
    ctx.UInt64Value(value["data"]);
    ctx.UInt64Value(value["triangleArray"]);
    ctx.UInt64Value(value["triangleArrayStride"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceOpacityMicromapFeaturesKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["micromap"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceOpacityMicromapPropertiesKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["maxOpacity2StateSubdivisionLevel"]);
    ctx.UInt32Value(value["maxOpacity4StateSubdivisionLevel"]);
    ctx.UInt32Value(value["maxOpacityLossy4StateSubdivisionLevel"]);
    ctx.UInt64Value(value["maxMicromapTriangles"]);
}

template <> void StructFromApiDump<VkMicromapTriangleKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.UInt32Value(value["dataOffset"]);
    ctx.UInt16Value(value["subdivisionLevel"]);
    ctx.UInt16Value(value["format"]);
}

template <> void StructFromApiDump<VkAccelerationStructureTrianglesOpacityMicromapKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.EnumValue(value["indexType"], EnumFromString_VkIndexType);
    ctx.UInt64Value(value["indexBuffer"]);
    ctx.UInt64Value(value["indexStride"]);
    ctx.UInt32Value(value["baseTriangle"]);
    ctx.VulkanHandleValue(value["micromap"], VK_OBJECT_TYPE_ACCELERATION_STRUCTURE_KHR);
}

template <> void StructFromApiDump<VkPhysicalDeviceMaintenance10FeaturesKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["maintenance10"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceMaintenance10PropertiesKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["rgba4OpaqueBlackSwizzled"]);
    ctx.UInt32Value(value["resolveSrgbFormatAppliesTransferFunction"]);
    ctx.UInt32Value(value["resolveSrgbFormatSupportsTransferFunctionControl"]);
}

template <> void StructFromApiDump<VkRenderingEndInfoKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
}

template <> void StructFromApiDump<VkRenderingAttachmentFlagsInfoKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.FlagsValue(value["flags"], EnumFromString_VkRenderingAttachmentFlagBitsKHR);
}

template <> void StructFromApiDump<VkResolveImageModeInfoKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.FlagsValue(value["flags"], EnumFromString_VkResolveImageFlagBitsKHR);
    ctx.EnumValue(value["resolveMode"], EnumFromString_VkResolveModeFlagBits);
    ctx.EnumValue(value["stencilResolveMode"], EnumFromString_VkResolveModeFlagBits);
}

template <> void StructFromApiDump<VkPhysicalDeviceMaintenance11FeaturesKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["maintenance11"]);
}

template <> void StructFromApiDump<VkQueueFamilyOptimalImageTransferGranularityPropertiesKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    StructFromApiDump<VkExtent3D>(ctx, value["optimalImageTransferGranularity"]);
}

template <> void StructFromApiDump<VkFormatProperties4KHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.Flags64Value(value["linearTilingFeatures"], EnumFromString_VkFormatFeatureFlagBits4KHR);
    ctx.Flags64Value(value["optimalTilingFeatures"], EnumFromString_VkFormatFeatureFlagBits4KHR);
    ctx.Flags64Value(value["bufferFeatures"], EnumFromString_VkFormatFeatureFlagBits4KHR);
}

template <> void StructFromApiDump<VkImageUsageFlags2CreateInfoKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.Flags64Value(value["usage"], EnumFromString_VkImageUsageFlagBits2KHR);
}

template <> void StructFromApiDump<VkImageCreateFlags2CreateInfoKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.Flags64Value(value["flags"], EnumFromString_VkImageCreateFlagBits2KHR);
}

template <> void StructFromApiDump<VkImageViewUsage2CreateInfoKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.Flags64Value(value["usage"], EnumFromString_VkImageUsageFlagBits2KHR);
}

template <> void StructFromApiDump<VkPhysicalDeviceExtendedFlagsFeaturesKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["extendedFlags"]);
}

template <> void StructFromApiDump<VkImageStencilUsage2CreateInfoKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.Flags64Value(value["stencilUsage"], EnumFromString_VkImageUsageFlagBits2KHR);
}

template <> void StructFromApiDump<VkSharedPresentSurfaceCapabilities2KHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.Flags64Value(value["sharedPresentSupportedUsageFlags"], EnumFromString_VkImageUsageFlagBits2KHR);
}

template <> void StructFromApiDump<VkDebugReportCallbackCreateInfoEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.FlagsValue(value["flags"], EnumFromString_VkDebugReportFlagBitsEXT);
    ctx.FunctionPtrValue(value["pfnCallback"]);
    ctx.VoidPtrValue(value["pUserData"]);
}

template <> void StructFromApiDump<VkPipelineRasterizationStateRasterizationOrderAMD>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.EnumValue(value["rasterizationOrder"], EnumFromString_VkRasterizationOrderAMD);
}

template <> void StructFromApiDump<VkDebugMarkerObjectNameInfoEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.EnumValue(value["objectType"], EnumFromString_VkDebugReportObjectTypeEXT);
    ctx.UInt64Value(value["object"]);
    ctx.StringValue(value["pObjectName"]);
}

template <> void StructFromApiDump<VkDebugMarkerObjectTagInfoEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.EnumValue(value["objectType"], EnumFromString_VkDebugReportObjectTypeEXT);
    ctx.UInt64Value(value["object"]);
    ctx.UInt64Value(value["tagName"]);
    ctx.SizeTValue(value["tagSize"]);
    ctx.UInt8Array(value["pTag"], ctx.Length(value["tagSize"]));
}

template <> void StructFromApiDump<VkDebugMarkerMarkerInfoEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.StringValue(value["pMarkerName"]);
    ctx.FloatArray(value["color"], 4);
}

template <> void StructFromApiDump<VkDedicatedAllocationImageCreateInfoNV>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["dedicatedAllocation"]);
}

template <> void StructFromApiDump<VkDedicatedAllocationBufferCreateInfoNV>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["dedicatedAllocation"]);
}

template <> void StructFromApiDump<VkDedicatedAllocationMemoryAllocateInfoNV>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.VulkanHandleValue(value["image"], VK_OBJECT_TYPE_IMAGE);
    ctx.VulkanHandleValue(value["buffer"], VK_OBJECT_TYPE_BUFFER);
}

template <> void StructFromApiDump<VkPhysicalDeviceTransformFeedbackFeaturesEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["transformFeedback"]);
    ctx.UInt32Value(value["geometryStreams"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceTransformFeedbackPropertiesEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["maxTransformFeedbackStreams"]);
    ctx.UInt32Value(value["maxTransformFeedbackBuffers"]);
    ctx.UInt64Value(value["maxTransformFeedbackBufferSize"]);
    ctx.UInt32Value(value["maxTransformFeedbackStreamDataSize"]);
    ctx.UInt32Value(value["maxTransformFeedbackBufferDataSize"]);
    ctx.UInt32Value(value["maxTransformFeedbackBufferDataStride"]);
    ctx.UInt32Value(value["transformFeedbackQueries"]);
    ctx.UInt32Value(value["transformFeedbackStreamsLinesTriangles"]);
    ctx.UInt32Value(value["transformFeedbackRasterizationStreamSelect"]);
    ctx.UInt32Value(value["transformFeedbackDraw"]);
}

template <> void StructFromApiDump<VkPipelineRasterizationStateStreamCreateInfoEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.FlagsValue(value["flags"]);
    ctx.UInt32Value(value["rasterizationStream"]);
}

template <> void StructFromApiDump<VkImageViewHandleInfoNVX>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.VulkanHandleValue(value["imageView"], VK_OBJECT_TYPE_IMAGE_VIEW);
    ctx.EnumValue(value["descriptorType"], EnumFromString_VkDescriptorType);
    ctx.VulkanHandleValue(value["sampler"], VK_OBJECT_TYPE_SAMPLER);
}

template <> void StructFromApiDump<VkImageViewAddressPropertiesNVX>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt64Value(value["deviceAddress"]);
    ctx.UInt64Value(value["size"]);
}

template <> void StructFromApiDump<VkTextureLODGatherFormatPropertiesAMD>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["supportsTextureGatherLODBiasAMD"]);
}

template <> void StructFromApiDump<VkShaderResourceUsageAMD>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.UInt32Value(value["numUsedVgprs"]);
    ctx.UInt32Value(value["numUsedSgprs"]);
    ctx.UInt32Value(value["ldsSizePerLocalWorkGroup"]);
    ctx.SizeTValue(value["ldsUsageSizeInBytes"]);
    ctx.SizeTValue(value["scratchMemUsageInBytes"]);
}

template <> void StructFromApiDump<VkShaderStatisticsInfoAMD>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.FlagsValue(value["shaderStageMask"], EnumFromString_VkShaderStageFlagBits);
    StructFromApiDump<VkShaderResourceUsageAMD>(ctx, value["resourceUsage"]);
    ctx.UInt32Value(value["numPhysicalVgprs"]);
    ctx.UInt32Value(value["numPhysicalSgprs"]);
    ctx.UInt32Value(value["numAvailableVgprs"]);
    ctx.UInt32Value(value["numAvailableSgprs"]);
    ctx.UInt32Array(value["computeWorkGroupSize"], 3);
}

template <> void StructFromApiDump<VkStreamDescriptorSurfaceCreateInfoGGP>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.FlagsValue(value["flags"]);
    ctx.UInt64Value(value["streamDescriptor"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceCornerSampledImageFeaturesNV>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["cornerSampledImage"]);
}

template <> void StructFromApiDump<VkExternalImageFormatPropertiesNV>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    StructFromApiDump<VkImageFormatProperties>(ctx, value["imageFormatProperties"]);
    ctx.FlagsValue(value["externalMemoryFeatures"], EnumFromString_VkExternalMemoryFeatureFlagBitsNV);
    ctx.FlagsValue(value["exportFromImportedHandleTypes"], EnumFromString_VkExternalMemoryHandleTypeFlagBitsNV);
    ctx.FlagsValue(value["compatibleHandleTypes"], EnumFromString_VkExternalMemoryHandleTypeFlagBitsNV);
}

template <> void StructFromApiDump<VkExternalMemoryImageCreateInfoNV>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.FlagsValue(value["handleTypes"], EnumFromString_VkExternalMemoryHandleTypeFlagBitsNV);
}

template <> void StructFromApiDump<VkExportMemoryAllocateInfoNV>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.FlagsValue(value["handleTypes"], EnumFromString_VkExternalMemoryHandleTypeFlagBitsNV);
}

template <> void StructFromApiDump<VkImportMemoryWin32HandleInfoNV>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.FlagsValue(value["handleType"], EnumFromString_VkExternalMemoryHandleTypeFlagBitsNV);
    ctx.VoidPtrValue(value["handle"]);
}

template <> void StructFromApiDump<VkExportMemoryWin32HandleInfoNV>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    StructPtrFromApiDump<SECURITY_ATTRIBUTES>(ctx, value["pAttributes"]);
    ctx.UInt32Value(value["dwAccess"]);
}

template <> void StructFromApiDump<VkWin32KeyedMutexAcquireReleaseInfoNV>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["acquireCount"]);
    ctx.VulkanHandleArray(value["pAcquireSyncs"], VK_OBJECT_TYPE_DEVICE_MEMORY, ctx.Length(value["acquireCount"]));
    ctx.UInt64Array(value["pAcquireKeys"], ctx.Length(value["acquireCount"]));
    ctx.UInt32Array(value["pAcquireTimeoutMilliseconds"], ctx.Length(value["acquireCount"]));
    ctx.UInt32Value(value["releaseCount"]);
    ctx.VulkanHandleArray(value["pReleaseSyncs"], VK_OBJECT_TYPE_DEVICE_MEMORY, ctx.Length(value["releaseCount"]));
    ctx.UInt64Array(value["pReleaseKeys"], ctx.Length(value["releaseCount"]));
}

template <> void StructFromApiDump<VkValidationFlagsEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["disabledValidationCheckCount"]);
    ctx.EnumArray(value["pDisabledValidationChecks"], EnumFromString_VkValidationCheckEXT, ctx.Length(value["disabledValidationCheckCount"]));
}

template <> void StructFromApiDump<VkViSurfaceCreateInfoNN>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.FlagsValue(value["flags"]);
    ctx.VoidPtrValue(value["window"]);
}

template <> void StructFromApiDump<VkImageViewASTCDecodeModeEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.EnumValue(value["decodeMode"], EnumFromString_VkFormat);
}

template <> void StructFromApiDump<VkPhysicalDeviceASTCDecodeFeaturesEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["decodeModeSharedExponent"]);
}

template <> void StructFromApiDump<VkConditionalRenderingBeginInfoEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.VulkanHandleValue(value["buffer"], VK_OBJECT_TYPE_BUFFER);
    ctx.UInt64Value(value["offset"]);
    ctx.FlagsValue(value["flags"], EnumFromString_VkConditionalRenderingFlagBitsEXT);
}

template <> void StructFromApiDump<VkPhysicalDeviceConditionalRenderingFeaturesEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["conditionalRendering"]);
    ctx.UInt32Value(value["inheritedConditionalRendering"]);
}

template <> void StructFromApiDump<VkCommandBufferInheritanceConditionalRenderingInfoEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["conditionalRenderingEnable"]);
}

template <> void StructFromApiDump<VkViewportWScalingNV>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.FloatValue(value["xcoeff"]);
    ctx.FloatValue(value["ycoeff"]);
}

template <> void StructFromApiDump<VkPipelineViewportWScalingStateCreateInfoNV>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["viewportWScalingEnable"]);
    ctx.UInt32Value(value["viewportCount"]);
    StructArrayFromApiDump<VkViewportWScalingNV>(ctx, value["pViewportWScalings"], ctx.Length(value["viewportCount"]));
}

template <> void StructFromApiDump<VkSurfaceCapabilities2EXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["minImageCount"]);
    ctx.UInt32Value(value["maxImageCount"]);
    StructFromApiDump<VkExtent2D>(ctx, value["currentExtent"]);
    StructFromApiDump<VkExtent2D>(ctx, value["minImageExtent"]);
    StructFromApiDump<VkExtent2D>(ctx, value["maxImageExtent"]);
    ctx.UInt32Value(value["maxImageArrayLayers"]);
    ctx.FlagsValue(value["supportedTransforms"], EnumFromString_VkSurfaceTransformFlagBitsKHR);
    ctx.EnumValue(value["currentTransform"], EnumFromString_VkSurfaceTransformFlagBitsKHR);
    ctx.FlagsValue(value["supportedCompositeAlpha"], EnumFromString_VkCompositeAlphaFlagBitsKHR);
    ctx.FlagsValue(value["supportedUsageFlags"], EnumFromString_VkImageUsageFlagBits);
    ctx.FlagsValue(value["supportedSurfaceCounters"], EnumFromString_VkSurfaceCounterFlagBitsEXT);
}

template <> void StructFromApiDump<VkDisplayPowerInfoEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.EnumValue(value["powerState"], EnumFromString_VkDisplayPowerStateEXT);
}

template <> void StructFromApiDump<VkDeviceEventInfoEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.EnumValue(value["deviceEvent"], EnumFromString_VkDeviceEventTypeEXT);
}

template <> void StructFromApiDump<VkDisplayEventInfoEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.EnumValue(value["displayEvent"], EnumFromString_VkDisplayEventTypeEXT);
}

template <> void StructFromApiDump<VkSwapchainCounterCreateInfoEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.FlagsValue(value["surfaceCounters"], EnumFromString_VkSurfaceCounterFlagBitsEXT);
}

template <> void StructFromApiDump<VkRefreshCycleDurationGOOGLE>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.UInt64Value(value["refreshDuration"]);
}

template <> void StructFromApiDump<VkPastPresentationTimingGOOGLE>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.UInt32Value(value["presentID"]);
    ctx.UInt64Value(value["desiredPresentTime"]);
    ctx.UInt64Value(value["actualPresentTime"]);
    ctx.UInt64Value(value["earliestPresentTime"]);
    ctx.UInt64Value(value["presentMargin"]);
}

template <> void StructFromApiDump<VkPresentTimeGOOGLE>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.UInt32Value(value["presentID"]);
    ctx.UInt64Value(value["desiredPresentTime"]);
}

template <> void StructFromApiDump<VkPresentTimesInfoGOOGLE>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["swapchainCount"]);
    StructArrayFromApiDump<VkPresentTimeGOOGLE>(ctx, value["pTimes"], ctx.Length(value["swapchainCount"]));
}

template <> void StructFromApiDump<VkPhysicalDeviceMultiviewPerViewAttributesPropertiesNVX>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["perViewPositionAllComponents"]);
}

template <> void StructFromApiDump<VkMultiviewPerViewAttributesInfoNVX>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["perViewAttributes"]);
    ctx.UInt32Value(value["perViewAttributesPositionXOnly"]);
}

template <> void StructFromApiDump<VkViewportSwizzleNV>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["x"], EnumFromString_VkViewportCoordinateSwizzleNV);
    ctx.EnumValue(value["y"], EnumFromString_VkViewportCoordinateSwizzleNV);
    ctx.EnumValue(value["z"], EnumFromString_VkViewportCoordinateSwizzleNV);
    ctx.EnumValue(value["w"], EnumFromString_VkViewportCoordinateSwizzleNV);
}

template <> void StructFromApiDump<VkPipelineViewportSwizzleStateCreateInfoNV>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.FlagsValue(value["flags"]);
    ctx.UInt32Value(value["viewportCount"]);
    StructArrayFromApiDump<VkViewportSwizzleNV>(ctx, value["pViewportSwizzles"], ctx.Length(value["viewportCount"]));
}

template <> void StructFromApiDump<VkPhysicalDeviceDiscardRectanglePropertiesEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["maxDiscardRectangles"]);
}

template <> void StructFromApiDump<VkPipelineDiscardRectangleStateCreateInfoEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.FlagsValue(value["flags"]);
    ctx.EnumValue(value["discardRectangleMode"], EnumFromString_VkDiscardRectangleModeEXT);
    ctx.UInt32Value(value["discardRectangleCount"]);
    StructArrayFromApiDump<VkRect2D>(ctx, value["pDiscardRectangles"], ctx.Length(value["discardRectangleCount"]));
}

template <> void StructFromApiDump<VkPhysicalDeviceConservativeRasterizationPropertiesEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.FloatValue(value["primitiveOverestimationSize"]);
    ctx.FloatValue(value["maxExtraPrimitiveOverestimationSize"]);
    ctx.FloatValue(value["extraPrimitiveOverestimationSizeGranularity"]);
    ctx.UInt32Value(value["primitiveUnderestimation"]);
    ctx.UInt32Value(value["conservativePointAndLineRasterization"]);
    ctx.UInt32Value(value["degenerateTrianglesRasterized"]);
    ctx.UInt32Value(value["degenerateLinesRasterized"]);
    ctx.UInt32Value(value["fullyCoveredFragmentShaderInputVariable"]);
    ctx.UInt32Value(value["conservativeRasterizationPostDepthCoverage"]);
}

template <> void StructFromApiDump<VkPipelineRasterizationConservativeStateCreateInfoEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.FlagsValue(value["flags"]);
    ctx.EnumValue(value["conservativeRasterizationMode"], EnumFromString_VkConservativeRasterizationModeEXT);
    ctx.FloatValue(value["extraPrimitiveOverestimationSize"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceDepthClipEnableFeaturesEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["depthClipEnable"]);
}

template <> void StructFromApiDump<VkPipelineRasterizationDepthClipStateCreateInfoEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.FlagsValue(value["flags"]);
    ctx.UInt32Value(value["depthClipEnable"]);
}

template <> void StructFromApiDump<VkXYColorEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.FloatValue(value["x"]);
    ctx.FloatValue(value["y"]);
}

template <> void StructFromApiDump<VkHdrMetadataEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    StructFromApiDump<VkXYColorEXT>(ctx, value["displayPrimaryRed"]);
    StructFromApiDump<VkXYColorEXT>(ctx, value["displayPrimaryGreen"]);
    StructFromApiDump<VkXYColorEXT>(ctx, value["displayPrimaryBlue"]);
    StructFromApiDump<VkXYColorEXT>(ctx, value["whitePoint"]);
    ctx.FloatValue(value["maxLuminance"]);
    ctx.FloatValue(value["minLuminance"]);
    ctx.FloatValue(value["maxContentLightLevel"]);
    ctx.FloatValue(value["maxFrameAverageLightLevel"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceRelaxedLineRasterizationFeaturesIMG>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["relaxedLineRasterization"]);
}

template <> void StructFromApiDump<VkIOSSurfaceCreateInfoMVK>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.FlagsValue(value["flags"]);
    ctx.VoidPtrValue(value["pView"]);
}

template <> void StructFromApiDump<VkMacOSSurfaceCreateInfoMVK>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.FlagsValue(value["flags"]);
    ctx.VoidPtrValue(value["pView"]);
}

template <> void StructFromApiDump<VkDebugUtilsLabelEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.StringValue(value["pLabelName"]);
    ctx.FloatArray(value["color"], 4);
}

template <> void StructFromApiDump<VkDebugUtilsObjectNameInfoEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.EnumValue(value["objectType"], EnumFromString_VkObjectType);
    ctx.UInt64Value(value["objectHandle"]);
    ctx.StringValue(value["pObjectName"]);
}

template <> void StructFromApiDump<VkDebugUtilsMessengerCallbackDataEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.FlagsValue(value["flags"]);
    ctx.StringValue(value["pMessageIdName"]);
    ctx.Int32Value(value["messageIdNumber"]);
    ctx.StringValue(value["pMessage"]);
    ctx.UInt32Value(value["queueLabelCount"]);
    StructArrayFromApiDump<VkDebugUtilsLabelEXT>(ctx, value["pQueueLabels"], ctx.Length(value["queueLabelCount"]));
    ctx.UInt32Value(value["cmdBufLabelCount"]);
    StructArrayFromApiDump<VkDebugUtilsLabelEXT>(ctx, value["pCmdBufLabels"], ctx.Length(value["cmdBufLabelCount"]));
    ctx.UInt32Value(value["objectCount"]);
    StructArrayFromApiDump<VkDebugUtilsObjectNameInfoEXT>(ctx, value["pObjects"], ctx.Length(value["objectCount"]));
}

template <> void StructFromApiDump<VkDebugUtilsMessengerCreateInfoEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.FlagsValue(value["flags"]);
    ctx.FlagsValue(value["messageSeverity"], EnumFromString_VkDebugUtilsMessageSeverityFlagBitsEXT);
    ctx.FlagsValue(value["messageType"], EnumFromString_VkDebugUtilsMessageTypeFlagBitsEXT);
    ctx.FunctionPtrValue(value["pfnUserCallback"]);
    ctx.VoidPtrValue(value["pUserData"]);
}

template <> void StructFromApiDump<VkDebugUtilsObjectTagInfoEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.EnumValue(value["objectType"], EnumFromString_VkObjectType);
    ctx.UInt64Value(value["objectHandle"]);
    ctx.UInt64Value(value["tagName"]);
    ctx.SizeTValue(value["tagSize"]);
    ctx.UInt8Array(value["pTag"], ctx.Length(value["tagSize"]));
}

template <> void StructFromApiDump<VkAndroidHardwareBufferUsageANDROID>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt64Value(value["androidHardwareBufferUsage"]);
}

template <> void StructFromApiDump<VkAndroidHardwareBufferPropertiesANDROID>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt64Value(value["allocationSize"]);
    ctx.UInt32Value(value["memoryTypeBits"]);
}

template <> void StructFromApiDump<VkAndroidHardwareBufferFormatPropertiesANDROID>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.EnumValue(value["format"], EnumFromString_VkFormat);
    ctx.UInt64Value(value["externalFormat"]);
    ctx.FlagsValue(value["formatFeatures"], EnumFromString_VkFormatFeatureFlagBits);
    StructFromApiDump<VkComponentMapping>(ctx, value["samplerYcbcrConversionComponents"]);
    ctx.EnumValue(value["suggestedYcbcrModel"], EnumFromString_VkSamplerYcbcrModelConversion);
    ctx.EnumValue(value["suggestedYcbcrRange"], EnumFromString_VkSamplerYcbcrRange);
    ctx.EnumValue(value["suggestedXChromaOffset"], EnumFromString_VkChromaLocation);
    ctx.EnumValue(value["suggestedYChromaOffset"], EnumFromString_VkChromaLocation);
}

template <> void StructFromApiDump<VkImportAndroidHardwareBufferInfoANDROID>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.VoidPtrValue(value["buffer"]);
}

template <> void StructFromApiDump<VkMemoryGetAndroidHardwareBufferInfoANDROID>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.VulkanHandleValue(value["memory"], VK_OBJECT_TYPE_DEVICE_MEMORY);
}

template <> void StructFromApiDump<VkExternalFormatANDROID>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt64Value(value["externalFormat"]);
}

template <> void StructFromApiDump<VkAndroidHardwareBufferFormatProperties2ANDROID>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.EnumValue(value["format"], EnumFromString_VkFormat);
    ctx.UInt64Value(value["externalFormat"]);
    ctx.Flags64Value(value["formatFeatures"], EnumFromString_VkFormatFeatureFlagBits2);
    StructFromApiDump<VkComponentMapping>(ctx, value["samplerYcbcrConversionComponents"]);
    ctx.EnumValue(value["suggestedYcbcrModel"], EnumFromString_VkSamplerYcbcrModelConversion);
    ctx.EnumValue(value["suggestedYcbcrRange"], EnumFromString_VkSamplerYcbcrRange);
    ctx.EnumValue(value["suggestedXChromaOffset"], EnumFromString_VkChromaLocation);
    ctx.EnumValue(value["suggestedYChromaOffset"], EnumFromString_VkChromaLocation);
}

template <> void StructFromApiDump<VkGpaPerfBlockPropertiesAMD>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["blockType"], EnumFromString_VkGpaPerfBlockAMD);
    ctx.FlagsValue(value["flags"]);
    ctx.UInt32Value(value["instanceCount"]);
    ctx.UInt32Value(value["maxEventID"]);
    ctx.UInt32Value(value["maxGlobalOnlyCounters"]);
    ctx.UInt32Value(value["maxGlobalSharedCounters"]);
    ctx.UInt32Value(value["maxStreamingCounters"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceGpaFeaturesAMD>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["perfCounters"]);
    ctx.UInt32Value(value["streamingPerfCounters"]);
    ctx.UInt32Value(value["sqThreadTracing"]);
    ctx.UInt32Value(value["clockModes"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceGpaPropertiesAMD>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.FlagsValue(value["flags"]);
    ctx.UInt64Value(value["maxSqttSeBufferSize"]);
    ctx.UInt32Value(value["shaderEngineCount"]);
    ctx.UInt32Value(value["perfBlockCount"]);
    StructArrayFromApiDump<VkGpaPerfBlockPropertiesAMD>(ctx, value["pPerfBlocks"], ctx.Length(value["perfBlockCount"]));
}

template <> void StructFromApiDump<VkPhysicalDeviceGpaProperties2AMD>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["revisionId"]);
}

template <> void StructFromApiDump<VkGpaPerfCounterAMD>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["blockType"], EnumFromString_VkGpaPerfBlockAMD);
    ctx.UInt32Value(value["blockInstance"]);
    ctx.UInt32Value(value["eventID"]);
}

template <> void StructFromApiDump<VkGpaSampleBeginInfoAMD>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.EnumValue(value["sampleType"], EnumFromString_VkGpaSampleTypeAMD);
    ctx.UInt32Value(value["sampleInternalOperations"]);
    ctx.UInt32Value(value["cacheFlushOnCounterCollection"]);
    ctx.UInt32Value(value["sqShaderMaskEnable"]);
    ctx.FlagsValue(value["sqShaderMask"], EnumFromString_VkGpaSqShaderStageFlagBitsAMD);
    ctx.UInt32Value(value["perfCounterCount"]);
    StructArrayFromApiDump<VkGpaPerfCounterAMD>(ctx, value["pPerfCounters"], ctx.Length(value["perfCounterCount"]));
    ctx.UInt32Value(value["streamingPerfTraceSampleInterval"]);
    ctx.UInt64Value(value["perfCounterDeviceMemoryLimit"]);
    ctx.UInt32Value(value["sqThreadTraceEnable"]);
    ctx.UInt32Value(value["sqThreadTraceSuppressInstructionTokens"]);
    ctx.UInt64Value(value["sqThreadTraceDeviceMemoryLimit"]);
    ctx.FlagsValue(value["timingPreSample"], EnumFromString_VkPipelineStageFlagBits);
    ctx.FlagsValue(value["timingPostSample"], EnumFromString_VkPipelineStageFlagBits);
}

template <> void StructFromApiDump<VkGpaDeviceClockModeInfoAMD>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.EnumValue(value["clockMode"], EnumFromString_VkGpaDeviceClockModeAMD);
    ctx.FloatValue(value["memoryClockRatioToPeak"]);
    ctx.FloatValue(value["engineClockRatioToPeak"]);
}

template <> void StructFromApiDump<VkGpaDeviceGetClockInfoAMD>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.FloatValue(value["memoryClockRatioToPeak"]);
    ctx.FloatValue(value["engineClockRatioToPeak"]);
    ctx.UInt32Value(value["memoryClockFrequency"]);
    ctx.UInt32Value(value["engineClockFrequency"]);
}

template <> void StructFromApiDump<VkGpaSessionCreateInfoAMD>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.VulkanHandleValue(value["secondaryCopySource"], VK_OBJECT_TYPE_GPA_SESSION_AMD);
}

template <> void StructFromApiDump<VkAttachmentSampleCountInfoAMD>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["colorAttachmentCount"]);
    ctx.EnumArray(value["pColorAttachmentSamples"], EnumFromString_VkSampleCountFlagBits, ctx.Length(value["colorAttachmentCount"]));
    ctx.EnumValue(value["depthStencilAttachmentSamples"], EnumFromString_VkSampleCountFlagBits);
}

template <> void StructFromApiDump<VkSampleLocationEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.FloatValue(value["x"]);
    ctx.FloatValue(value["y"]);
}

template <> void StructFromApiDump<VkSampleLocationsInfoEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.EnumValue(value["sampleLocationsPerPixel"], EnumFromString_VkSampleCountFlagBits);
    StructFromApiDump<VkExtent2D>(ctx, value["sampleLocationGridSize"]);
    ctx.UInt32Value(value["sampleLocationsCount"]);
    StructArrayFromApiDump<VkSampleLocationEXT>(ctx, value["pSampleLocations"], ctx.Length(value["sampleLocationsCount"]));
}

template <> void StructFromApiDump<VkAttachmentSampleLocationsEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.UInt32Value(value["attachmentIndex"]);
    StructFromApiDump<VkSampleLocationsInfoEXT>(ctx, value["sampleLocationsInfo"]);
}

template <> void StructFromApiDump<VkSubpassSampleLocationsEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.UInt32Value(value["subpassIndex"]);
    StructFromApiDump<VkSampleLocationsInfoEXT>(ctx, value["sampleLocationsInfo"]);
}

template <> void StructFromApiDump<VkRenderPassSampleLocationsBeginInfoEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["attachmentInitialSampleLocationsCount"]);
    StructArrayFromApiDump<VkAttachmentSampleLocationsEXT>(ctx, value["pAttachmentInitialSampleLocations"], ctx.Length(value["attachmentInitialSampleLocationsCount"]));
    ctx.UInt32Value(value["postSubpassSampleLocationsCount"]);
    StructArrayFromApiDump<VkSubpassSampleLocationsEXT>(ctx, value["pPostSubpassSampleLocations"], ctx.Length(value["postSubpassSampleLocationsCount"]));
}

template <> void StructFromApiDump<VkPipelineSampleLocationsStateCreateInfoEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["sampleLocationsEnable"]);
    StructFromApiDump<VkSampleLocationsInfoEXT>(ctx, value["sampleLocationsInfo"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceSampleLocationsPropertiesEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.FlagsValue(value["sampleLocationSampleCounts"], EnumFromString_VkSampleCountFlagBits);
    StructFromApiDump<VkExtent2D>(ctx, value["maxSampleLocationGridSize"]);
    ctx.FloatArray(value["sampleLocationCoordinateRange"], 2);
    ctx.UInt32Value(value["sampleLocationSubPixelBits"]);
    ctx.UInt32Value(value["variableSampleLocations"]);
}

template <> void StructFromApiDump<VkMultisamplePropertiesEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    StructFromApiDump<VkExtent2D>(ctx, value["maxSampleLocationGridSize"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceBlendOperationAdvancedFeaturesEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["advancedBlendCoherentOperations"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceBlendOperationAdvancedPropertiesEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["advancedBlendMaxColorAttachments"]);
    ctx.UInt32Value(value["advancedBlendIndependentBlend"]);
    ctx.UInt32Value(value["advancedBlendNonPremultipliedSrcColor"]);
    ctx.UInt32Value(value["advancedBlendNonPremultipliedDstColor"]);
    ctx.UInt32Value(value["advancedBlendCorrelatedOverlap"]);
    ctx.UInt32Value(value["advancedBlendAllOperations"]);
}

template <> void StructFromApiDump<VkPipelineColorBlendAdvancedStateCreateInfoEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["srcPremultiplied"]);
    ctx.UInt32Value(value["dstPremultiplied"]);
    ctx.EnumValue(value["blendOverlap"], EnumFromString_VkBlendOverlapEXT);
}

template <> void StructFromApiDump<VkPipelineCoverageToColorStateCreateInfoNV>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.FlagsValue(value["flags"]);
    ctx.UInt32Value(value["coverageToColorEnable"]);
    ctx.UInt32Value(value["coverageToColorLocation"]);
}

template <> void StructFromApiDump<VkPipelineCoverageModulationStateCreateInfoNV>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.FlagsValue(value["flags"]);
    ctx.EnumValue(value["coverageModulationMode"], EnumFromString_VkCoverageModulationModeNV);
    ctx.UInt32Value(value["coverageModulationTableEnable"]);
    ctx.UInt32Value(value["coverageModulationTableCount"]);
    ctx.FloatArray(value["pCoverageModulationTable"], ctx.Length(value["coverageModulationTableCount"]));
}

template <> void StructFromApiDump<VkPhysicalDeviceShaderSMBuiltinsPropertiesNV>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["shaderSMCount"]);
    ctx.UInt32Value(value["shaderWarpsPerSM"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceShaderSMBuiltinsFeaturesNV>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["shaderSMBuiltins"]);
}

template <> void StructFromApiDump<VkDrmFormatModifierPropertiesEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.UInt64Value(value["drmFormatModifier"]);
    ctx.UInt32Value(value["drmFormatModifierPlaneCount"]);
    ctx.FlagsValue(value["drmFormatModifierTilingFeatures"], EnumFromString_VkFormatFeatureFlagBits);
}

template <> void StructFromApiDump<VkDrmFormatModifierPropertiesListEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["drmFormatModifierCount"]);
    StructArrayFromApiDump<VkDrmFormatModifierPropertiesEXT>(ctx, value["pDrmFormatModifierProperties"], ctx.Length(value["drmFormatModifierCount"]));
}

template <> void StructFromApiDump<VkPhysicalDeviceImageDrmFormatModifierInfoEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt64Value(value["drmFormatModifier"]);
    ctx.EnumValue(value["sharingMode"], EnumFromString_VkSharingMode);
    ctx.UInt32Value(value["queueFamilyIndexCount"]);
    ctx.UInt32Array(value["pQueueFamilyIndices"], ctx.Length(value["queueFamilyIndexCount"]));
}

template <> void StructFromApiDump<VkImageDrmFormatModifierListCreateInfoEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["drmFormatModifierCount"]);
    ctx.UInt64Array(value["pDrmFormatModifiers"], ctx.Length(value["drmFormatModifierCount"]));
}

template <> void StructFromApiDump<VkImageDrmFormatModifierExplicitCreateInfoEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt64Value(value["drmFormatModifier"]);
    ctx.UInt32Value(value["drmFormatModifierPlaneCount"]);
    StructArrayFromApiDump<VkSubresourceLayout>(ctx, value["pPlaneLayouts"], ctx.Length(value["drmFormatModifierPlaneCount"]));
}

template <> void StructFromApiDump<VkImageDrmFormatModifierPropertiesEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt64Value(value["drmFormatModifier"]);
}

template <> void StructFromApiDump<VkDrmFormatModifierProperties2EXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.UInt64Value(value["drmFormatModifier"]);
    ctx.UInt32Value(value["drmFormatModifierPlaneCount"]);
    ctx.Flags64Value(value["drmFormatModifierTilingFeatures"], EnumFromString_VkFormatFeatureFlagBits2);
}

template <> void StructFromApiDump<VkDrmFormatModifierPropertiesList2EXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["drmFormatModifierCount"]);
    StructArrayFromApiDump<VkDrmFormatModifierProperties2EXT>(ctx, value["pDrmFormatModifierProperties"], ctx.Length(value["drmFormatModifierCount"]));
}

template <> void StructFromApiDump<VkValidationCacheCreateInfoEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.FlagsValue(value["flags"]);
    ctx.SizeTValue(value["initialDataSize"]);
    ctx.UInt8Array(value["pInitialData"], ctx.Length(value["initialDataSize"]));
}

template <> void StructFromApiDump<VkShaderModuleValidationCacheCreateInfoEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.VulkanHandleValue(value["validationCache"], VK_OBJECT_TYPE_VALIDATION_CACHE_EXT);
}

template <> void StructFromApiDump<VkShadingRatePaletteNV>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.UInt32Value(value["shadingRatePaletteEntryCount"]);
    ctx.EnumArray(value["pShadingRatePaletteEntries"], EnumFromString_VkShadingRatePaletteEntryNV, ctx.Length(value["shadingRatePaletteEntryCount"]));
}

template <> void StructFromApiDump<VkPipelineViewportShadingRateImageStateCreateInfoNV>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["shadingRateImageEnable"]);
    ctx.UInt32Value(value["viewportCount"]);
    StructArrayFromApiDump<VkShadingRatePaletteNV>(ctx, value["pShadingRatePalettes"], ctx.Length(value["viewportCount"]));
}

template <> void StructFromApiDump<VkPhysicalDeviceShadingRateImageFeaturesNV>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["shadingRateImage"]);
    ctx.UInt32Value(value["shadingRateCoarseSampleOrder"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceShadingRateImagePropertiesNV>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    StructFromApiDump<VkExtent2D>(ctx, value["shadingRateTexelSize"]);
    ctx.UInt32Value(value["shadingRatePaletteSize"]);
    ctx.UInt32Value(value["shadingRateMaxCoarseSamples"]);
}

template <> void StructFromApiDump<VkCoarseSampleLocationNV>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.UInt32Value(value["pixelX"]);
    ctx.UInt32Value(value["pixelY"]);
    ctx.UInt32Value(value["sample"]);
}

template <> void StructFromApiDump<VkCoarseSampleOrderCustomNV>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["shadingRate"], EnumFromString_VkShadingRatePaletteEntryNV);
    ctx.UInt32Value(value["sampleCount"]);
    ctx.UInt32Value(value["sampleLocationCount"]);
    StructArrayFromApiDump<VkCoarseSampleLocationNV>(ctx, value["pSampleLocations"], ctx.Length(value["sampleLocationCount"]));
}

template <> void StructFromApiDump<VkPipelineViewportCoarseSampleOrderStateCreateInfoNV>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.EnumValue(value["sampleOrderType"], EnumFromString_VkCoarseSampleOrderTypeNV);
    ctx.UInt32Value(value["customSampleOrderCount"]);
    StructArrayFromApiDump<VkCoarseSampleOrderCustomNV>(ctx, value["pCustomSampleOrders"], ctx.Length(value["customSampleOrderCount"]));
}

template <> void StructFromApiDump<VkRayTracingShaderGroupCreateInfoNV>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.EnumValue(value["type"], EnumFromString_VkRayTracingShaderGroupTypeKHR);
    ctx.UInt32Value(value["generalShader"]);
    ctx.UInt32Value(value["closestHitShader"]);
    ctx.UInt32Value(value["anyHitShader"]);
    ctx.UInt32Value(value["intersectionShader"]);
}

template <> void StructFromApiDump<VkRayTracingPipelineCreateInfoNV>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.FlagsValue(value["flags"], EnumFromString_VkPipelineCreateFlagBits);
    ctx.UInt32Value(value["stageCount"]);
    StructArrayFromApiDump<VkPipelineShaderStageCreateInfo>(ctx, value["pStages"], ctx.Length(value["stageCount"]));
    ctx.UInt32Value(value["groupCount"]);
    StructArrayFromApiDump<VkRayTracingShaderGroupCreateInfoNV>(ctx, value["pGroups"], ctx.Length(value["groupCount"]));
    ctx.UInt32Value(value["maxRecursionDepth"]);
    ctx.VulkanHandleValue(value["layout"], VK_OBJECT_TYPE_PIPELINE_LAYOUT);
    ctx.VulkanHandleValue(value["basePipelineHandle"], VK_OBJECT_TYPE_PIPELINE);
    ctx.Int32Value(value["basePipelineIndex"]);
}

template <> void StructFromApiDump<VkGeometryTrianglesNV>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.VulkanHandleValue(value["vertexData"], VK_OBJECT_TYPE_BUFFER);
    ctx.UInt64Value(value["vertexOffset"]);
    ctx.UInt32Value(value["vertexCount"]);
    ctx.UInt64Value(value["vertexStride"]);
    ctx.EnumValue(value["vertexFormat"], EnumFromString_VkFormat);
    ctx.VulkanHandleValue(value["indexData"], VK_OBJECT_TYPE_BUFFER);
    ctx.UInt64Value(value["indexOffset"]);
    ctx.UInt32Value(value["indexCount"]);
    ctx.EnumValue(value["indexType"], EnumFromString_VkIndexType);
    ctx.VulkanHandleValue(value["transformData"], VK_OBJECT_TYPE_BUFFER);
    ctx.UInt64Value(value["transformOffset"]);
}

template <> void StructFromApiDump<VkGeometryAABBNV>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.VulkanHandleValue(value["aabbData"], VK_OBJECT_TYPE_BUFFER);
    ctx.UInt32Value(value["numAABBs"]);
    ctx.UInt32Value(value["stride"]);
    ctx.UInt64Value(value["offset"]);
}

template <> void StructFromApiDump<VkGeometryDataNV>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    StructFromApiDump<VkGeometryTrianglesNV>(ctx, value["triangles"]);
    StructFromApiDump<VkGeometryAABBNV>(ctx, value["aabbs"]);
}

template <> void StructFromApiDump<VkGeometryNV>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.EnumValue(value["geometryType"], EnumFromString_VkGeometryTypeKHR);
    StructFromApiDump<VkGeometryDataNV>(ctx, value["geometry"]);
    ctx.FlagsValue(value["flags"], EnumFromString_VkGeometryFlagBitsKHR);
}

template <> void StructFromApiDump<VkAccelerationStructureInfoNV>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.EnumValue(value["type"], EnumFromString_VkAccelerationStructureTypeKHR);
    ctx.FlagsValue(value["flags"], EnumFromString_VkBuildAccelerationStructureFlagBitsKHR);
    ctx.UInt32Value(value["instanceCount"]);
    ctx.UInt32Value(value["geometryCount"]);
    StructArrayFromApiDump<VkGeometryNV>(ctx, value["pGeometries"], ctx.Length(value["geometryCount"]));
}

template <> void StructFromApiDump<VkAccelerationStructureCreateInfoNV>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt64Value(value["compactedSize"]);
    StructFromApiDump<VkAccelerationStructureInfoNV>(ctx, value["info"]);
}

template <> void StructFromApiDump<VkBindAccelerationStructureMemoryInfoNV>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.VulkanHandleValue(value["accelerationStructure"], VK_OBJECT_TYPE_ACCELERATION_STRUCTURE_NV);
    ctx.VulkanHandleValue(value["memory"], VK_OBJECT_TYPE_DEVICE_MEMORY);
    ctx.UInt64Value(value["memoryOffset"]);
    ctx.UInt32Value(value["deviceIndexCount"]);
    ctx.UInt32Array(value["pDeviceIndices"], ctx.Length(value["deviceIndexCount"]));
}

template <> void StructFromApiDump<VkWriteDescriptorSetAccelerationStructureNV>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["accelerationStructureCount"]);
    ctx.VulkanHandleArray(value["pAccelerationStructures"], VK_OBJECT_TYPE_ACCELERATION_STRUCTURE_NV, ctx.Length(value["accelerationStructureCount"]));
}

template <> void StructFromApiDump<VkAccelerationStructureMemoryRequirementsInfoNV>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.EnumValue(value["type"], EnumFromString_VkAccelerationStructureMemoryRequirementsTypeNV);
    ctx.VulkanHandleValue(value["accelerationStructure"], VK_OBJECT_TYPE_ACCELERATION_STRUCTURE_NV);
}

template <> void StructFromApiDump<VkPhysicalDeviceRayTracingPropertiesNV>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["shaderGroupHandleSize"]);
    ctx.UInt32Value(value["maxRecursionDepth"]);
    ctx.UInt32Value(value["maxShaderGroupStride"]);
    ctx.UInt32Value(value["shaderGroupBaseAlignment"]);
    ctx.UInt64Value(value["maxGeometryCount"]);
    ctx.UInt64Value(value["maxInstanceCount"]);
    ctx.UInt64Value(value["maxTriangleCount"]);
    ctx.UInt32Value(value["maxDescriptorSetAccelerationStructures"]);
}

template <> void StructFromApiDump<VkTransformMatrixKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.FloatArray(value["matrix"]);
}

template <> void StructFromApiDump<VkAabbPositionsKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.FloatValue(value["minX"]);
    ctx.FloatValue(value["minY"]);
    ctx.FloatValue(value["minZ"]);
    ctx.FloatValue(value["maxX"]);
    ctx.FloatValue(value["maxY"]);
    ctx.FloatValue(value["maxZ"]);
}

template <> void StructFromApiDump<VkAccelerationStructureInstanceKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    StructFromApiDump<VkTransformMatrixKHR>(ctx, value["transform"]);
    ctx.UInt32Value(value["instanceCustomIndex"]);
    ctx.UInt32Value(value["mask"]);
    ctx.UInt32Value(value["instanceShaderBindingTableRecordOffset"]);
    ctx.FlagsValue(value["flags"], EnumFromString_VkGeometryInstanceFlagBitsKHR);
    ctx.UInt64Value(value["accelerationStructureReference"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceRepresentativeFragmentTestFeaturesNV>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["representativeFragmentTest"]);
}

template <> void StructFromApiDump<VkPipelineRepresentativeFragmentTestStateCreateInfoNV>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["representativeFragmentTestEnable"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceImageViewImageFormatInfoEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.EnumValue(value["imageViewType"], EnumFromString_VkImageViewType);
}

template <> void StructFromApiDump<VkFilterCubicImageViewImageFormatPropertiesEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["filterCubic"]);
    ctx.UInt32Value(value["filterCubicMinmax"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceCooperativeMatrixConversionFeaturesQCOM>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["cooperativeMatrixConversion"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceElapsedTimerQueryFeaturesQCOM>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["elapsedTimerQuery"]);
}

template <> void StructFromApiDump<VkImportMemoryHostPointerInfoEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.EnumValue(value["handleType"], EnumFromString_VkExternalMemoryHandleTypeFlagBits);
    ctx.VoidPtrValue(value["pHostPointer"]);
}

template <> void StructFromApiDump<VkMemoryHostPointerPropertiesEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["memoryTypeBits"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceExternalMemoryHostPropertiesEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt64Value(value["minImportedHostPointerAlignment"]);
}

template <> void StructFromApiDump<VkPipelineCompilerControlCreateInfoAMD>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.FlagsValue(value["compilerControlFlags"], EnumFromString_VkPipelineCompilerControlFlagBitsAMD);
}

template <> void StructFromApiDump<VkPhysicalDeviceShaderCorePropertiesAMD>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["shaderEngineCount"]);
    ctx.UInt32Value(value["shaderArraysPerEngineCount"]);
    ctx.UInt32Value(value["computeUnitsPerShaderArray"]);
    ctx.UInt32Value(value["simdPerComputeUnit"]);
    ctx.UInt32Value(value["wavefrontsPerSimd"]);
    ctx.UInt32Value(value["wavefrontSize"]);
    ctx.UInt32Value(value["sgprsPerSimd"]);
    ctx.UInt32Value(value["minSgprAllocation"]);
    ctx.UInt32Value(value["maxSgprAllocation"]);
    ctx.UInt32Value(value["sgprAllocationGranularity"]);
    ctx.UInt32Value(value["vgprsPerSimd"]);
    ctx.UInt32Value(value["minVgprAllocation"]);
    ctx.UInt32Value(value["maxVgprAllocation"]);
    ctx.UInt32Value(value["vgprAllocationGranularity"]);
}

template <> void StructFromApiDump<VkDeviceMemoryOverallocationCreateInfoAMD>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.EnumValue(value["overallocationBehavior"], EnumFromString_VkMemoryOverallocationBehaviorAMD);
}

template <> void StructFromApiDump<VkPhysicalDeviceVertexAttributeDivisorPropertiesEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["maxVertexAttribDivisor"]);
}

template <> void StructFromApiDump<VkPresentFrameTokenGGP>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt64Value(value["frameToken"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceMeshShaderFeaturesNV>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["taskShader"]);
    ctx.UInt32Value(value["meshShader"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceMeshShaderPropertiesNV>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["maxDrawMeshTasksCount"]);
    ctx.UInt32Value(value["maxTaskWorkGroupInvocations"]);
    ctx.UInt32Array(value["maxTaskWorkGroupSize"], 3);
    ctx.UInt32Value(value["maxTaskTotalMemorySize"]);
    ctx.UInt32Value(value["maxTaskOutputCount"]);
    ctx.UInt32Value(value["maxMeshWorkGroupInvocations"]);
    ctx.UInt32Array(value["maxMeshWorkGroupSize"], 3);
    ctx.UInt32Value(value["maxMeshTotalMemorySize"]);
    ctx.UInt32Value(value["maxMeshOutputVertices"]);
    ctx.UInt32Value(value["maxMeshOutputPrimitives"]);
    ctx.UInt32Value(value["maxMeshMultiviewViewCount"]);
    ctx.UInt32Value(value["meshOutputPerVertexGranularity"]);
    ctx.UInt32Value(value["meshOutputPerPrimitiveGranularity"]);
}

template <> void StructFromApiDump<VkDrawMeshTasksIndirectCommandNV>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.UInt32Value(value["taskCount"]);
    ctx.UInt32Value(value["firstTask"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceShaderImageFootprintFeaturesNV>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["imageFootprint"]);
}

template <> void StructFromApiDump<VkPipelineViewportExclusiveScissorStateCreateInfoNV>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["exclusiveScissorCount"]);
    StructArrayFromApiDump<VkRect2D>(ctx, value["pExclusiveScissors"], ctx.Length(value["exclusiveScissorCount"]));
}

template <> void StructFromApiDump<VkPhysicalDeviceExclusiveScissorFeaturesNV>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["exclusiveScissor"]);
}

template <> void StructFromApiDump<VkQueueFamilyCheckpointPropertiesNV>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.FlagsValue(value["checkpointExecutionStageMask"], EnumFromString_VkPipelineStageFlagBits);
}

template <> void StructFromApiDump<VkCheckpointDataNV>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.EnumValue(value["stage"], EnumFromString_VkPipelineStageFlagBits);
    ctx.VoidPtrValue(value["pCheckpointMarker"]);
}

template <> void StructFromApiDump<VkQueueFamilyCheckpointProperties2NV>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.Flags64Value(value["checkpointExecutionStageMask"], EnumFromString_VkPipelineStageFlagBits2);
}

template <> void StructFromApiDump<VkCheckpointData2NV>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.Flags64Value(value["stage"], EnumFromString_VkPipelineStageFlagBits2);
    ctx.VoidPtrValue(value["pCheckpointMarker"]);
}

template <> void StructFromApiDump<VkPhysicalDevicePresentTimingFeaturesEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["presentTiming"]);
    ctx.UInt32Value(value["presentAtAbsoluteTime"]);
    ctx.UInt32Value(value["presentAtRelativeTime"]);
}

template <> void StructFromApiDump<VkPresentTimingSurfaceCapabilitiesEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["presentTimingSupported"]);
    ctx.UInt32Value(value["presentAtAbsoluteTimeSupported"]);
    ctx.UInt32Value(value["presentAtRelativeTimeSupported"]);
    ctx.FlagsValue(value["presentStageQueries"], EnumFromString_VkPresentStageFlagBitsEXT);
}

template <> void StructFromApiDump<VkSwapchainCalibratedTimestampInfoEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.VulkanHandleValue(value["swapchain"], VK_OBJECT_TYPE_SWAPCHAIN_KHR);
    ctx.FlagsValue(value["presentStage"], EnumFromString_VkPresentStageFlagBitsEXT);
    ctx.UInt64Value(value["timeDomainId"]);
}

template <> void StructFromApiDump<VkSwapchainTimingPropertiesEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt64Value(value["refreshDuration"]);
    ctx.UInt64Value(value["refreshInterval"]);
}

template <> void StructFromApiDump<VkSwapchainTimeDomainPropertiesEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["timeDomainCount"]);
    ctx.EnumArray(value["pTimeDomains"], EnumFromString_VkTimeDomainKHR, ctx.Length(value["timeDomainCount"]));
    ctx.UInt64Array(value["pTimeDomainIds"], ctx.Length(value["timeDomainCount"]));
}

template <> void StructFromApiDump<VkPastPresentationTimingInfoEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.FlagsValue(value["flags"], EnumFromString_VkPastPresentationTimingFlagBitsEXT);
    ctx.VulkanHandleValue(value["swapchain"], VK_OBJECT_TYPE_SWAPCHAIN_KHR);
}

template <> void StructFromApiDump<VkPresentStageTimeEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.FlagsValue(value["stage"], EnumFromString_VkPresentStageFlagBitsEXT);
    ctx.UInt64Value(value["time"]);
}

template <> void StructFromApiDump<VkPastPresentationTimingEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt64Value(value["presentId"]);
    ctx.UInt64Value(value["targetTime"]);
    ctx.UInt32Value(value["presentStageCount"]);
    StructArrayFromApiDump<VkPresentStageTimeEXT>(ctx, value["pPresentStages"], ctx.Length(value["presentStageCount"]));
    ctx.EnumValue(value["timeDomain"], EnumFromString_VkTimeDomainKHR);
    ctx.UInt64Value(value["timeDomainId"]);
    ctx.UInt32Value(value["reportComplete"]);
}

template <> void StructFromApiDump<VkPastPresentationTimingPropertiesEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt64Value(value["timingPropertiesCounter"]);
    ctx.UInt64Value(value["timeDomainsCounter"]);
    ctx.UInt32Value(value["presentationTimingCount"]);
    StructArrayFromApiDump<VkPastPresentationTimingEXT>(ctx, value["pPresentationTimings"], ctx.Length(value["presentationTimingCount"]));
}

template <> void StructFromApiDump<VkPresentTimingInfoEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.FlagsValue(value["flags"], EnumFromString_VkPresentTimingInfoFlagBitsEXT);
    ctx.UInt64Value(value["targetTime"]);
    ctx.UInt64Value(value["timeDomainId"]);
    ctx.FlagsValue(value["presentStageQueries"], EnumFromString_VkPresentStageFlagBitsEXT);
    ctx.FlagsValue(value["targetTimeDomainPresentStage"], EnumFromString_VkPresentStageFlagBitsEXT);
}

template <> void StructFromApiDump<VkPresentTimingsInfoEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["swapchainCount"]);
    StructArrayFromApiDump<VkPresentTimingInfoEXT>(ctx, value["pTimingInfos"], ctx.Length(value["swapchainCount"]));
}

template <> void StructFromApiDump<VkPhysicalDeviceShaderIntegerFunctions2FeaturesINTEL>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["shaderIntegerFunctions2"]);
}

template <> void StructFromApiDump<VkInitializePerformanceApiInfoINTEL>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.VoidPtrValue(value["pUserData"]);
}

template <> void StructFromApiDump<VkQueryPoolPerformanceQueryCreateInfoINTEL>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.EnumValue(value["performanceCountersSampling"], EnumFromString_VkQueryPoolSamplingModeINTEL);
}

template <> void StructFromApiDump<VkPerformanceMarkerInfoINTEL>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt64Value(value["marker"]);
}

template <> void StructFromApiDump<VkPerformanceStreamMarkerInfoINTEL>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["marker"]);
}

template <> void StructFromApiDump<VkPerformanceOverrideInfoINTEL>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.EnumValue(value["type"], EnumFromString_VkPerformanceOverrideTypeINTEL);
    ctx.UInt32Value(value["enable"]);
    ctx.UInt64Value(value["parameter"]);
}

template <> void StructFromApiDump<VkPerformanceConfigurationAcquireInfoINTEL>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.EnumValue(value["type"], EnumFromString_VkPerformanceConfigurationTypeINTEL);
}

template <> void StructFromApiDump<VkPhysicalDevicePCIBusInfoPropertiesEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["pciDomain"]);
    ctx.UInt32Value(value["pciBus"]);
    ctx.UInt32Value(value["pciDevice"]);
    ctx.UInt32Value(value["pciFunction"]);
}

template <> void StructFromApiDump<VkDisplayNativeHdrSurfaceCapabilitiesAMD>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["localDimmingSupport"]);
}

template <> void StructFromApiDump<VkSwapchainDisplayNativeHdrCreateInfoAMD>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["localDimmingEnable"]);
}

template <> void StructFromApiDump<VkImagePipeSurfaceCreateInfoFUCHSIA>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.FlagsValue(value["flags"]);
    ctx.UInt32Value(value["imagePipeHandle"]);
}

template <> void StructFromApiDump<VkMetalSurfaceCreateInfoEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.FlagsValue(value["flags"]);
    ctx.VoidPtrValue(value["pLayer"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceFragmentDensityMapFeaturesEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["fragmentDensityMap"]);
    ctx.UInt32Value(value["fragmentDensityMapDynamic"]);
    ctx.UInt32Value(value["fragmentDensityMapNonSubsampledImages"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceFragmentDensityMapPropertiesEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    StructFromApiDump<VkExtent2D>(ctx, value["minFragmentDensityTexelSize"]);
    StructFromApiDump<VkExtent2D>(ctx, value["maxFragmentDensityTexelSize"]);
    ctx.UInt32Value(value["fragmentDensityInvocations"]);
}

template <> void StructFromApiDump<VkRenderPassFragmentDensityMapCreateInfoEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    StructFromApiDump<VkAttachmentReference>(ctx, value["fragmentDensityMapAttachment"]);
}

template <> void StructFromApiDump<VkRenderingFragmentDensityMapAttachmentInfoEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.VulkanHandleValue(value["imageView"], VK_OBJECT_TYPE_IMAGE_VIEW);
    ctx.EnumValue(value["imageLayout"], EnumFromString_VkImageLayout);
}

template <> void StructFromApiDump<VkPhysicalDeviceShaderCoreProperties2AMD>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.FlagsValue(value["shaderCoreFeatures"], EnumFromString_VkShaderCorePropertiesFlagBitsAMD);
    ctx.UInt32Value(value["activeComputeUnitCount"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceCoherentMemoryFeaturesAMD>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["deviceCoherentMemory"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceShaderImageAtomicInt64FeaturesEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["shaderImageInt64Atomics"]);
    ctx.UInt32Value(value["sparseImageInt64Atomics"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceMemoryBudgetPropertiesEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt64Array(value["heapBudget"]);
    ctx.UInt64Array(value["heapUsage"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceMemoryPriorityFeaturesEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["memoryPriority"]);
}

template <> void StructFromApiDump<VkMemoryPriorityAllocateInfoEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.FloatValue(value["priority"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceDedicatedAllocationImageAliasingFeaturesNV>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["dedicatedAllocationImageAliasing"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceBufferDeviceAddressFeaturesEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["bufferDeviceAddress"]);
    ctx.UInt32Value(value["bufferDeviceAddressCaptureReplay"]);
    ctx.UInt32Value(value["bufferDeviceAddressMultiDevice"]);
}

template <> void StructFromApiDump<VkBufferDeviceAddressCreateInfoEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt64Value(value["deviceAddress"]);
}

template <> void StructFromApiDump<VkValidationFeaturesEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["enabledValidationFeatureCount"]);
    ctx.EnumArray(value["pEnabledValidationFeatures"], EnumFromString_VkValidationFeatureEnableEXT, ctx.Length(value["enabledValidationFeatureCount"]));
    ctx.UInt32Value(value["disabledValidationFeatureCount"]);
    ctx.EnumArray(value["pDisabledValidationFeatures"], EnumFromString_VkValidationFeatureDisableEXT, ctx.Length(value["disabledValidationFeatureCount"]));
}

template <> void StructFromApiDump<VkCooperativeMatrixPropertiesNV>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["MSize"]);
    ctx.UInt32Value(value["NSize"]);
    ctx.UInt32Value(value["KSize"]);
    ctx.EnumValue(value["AType"], EnumFromString_VkComponentTypeKHR);
    ctx.EnumValue(value["BType"], EnumFromString_VkComponentTypeKHR);
    ctx.EnumValue(value["CType"], EnumFromString_VkComponentTypeKHR);
    ctx.EnumValue(value["DType"], EnumFromString_VkComponentTypeKHR);
    ctx.EnumValue(value["scope"], EnumFromString_VkScopeKHR);
}

template <> void StructFromApiDump<VkPhysicalDeviceCooperativeMatrixFeaturesNV>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["cooperativeMatrix"]);
    ctx.UInt32Value(value["cooperativeMatrixRobustBufferAccess"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceCooperativeMatrixPropertiesNV>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.FlagsValue(value["cooperativeMatrixSupportedStages"], EnumFromString_VkShaderStageFlagBits);
}

template <> void StructFromApiDump<VkPhysicalDeviceCoverageReductionModeFeaturesNV>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["coverageReductionMode"]);
}

template <> void StructFromApiDump<VkPipelineCoverageReductionStateCreateInfoNV>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.FlagsValue(value["flags"]);
    ctx.EnumValue(value["coverageReductionMode"], EnumFromString_VkCoverageReductionModeNV);
}

template <> void StructFromApiDump<VkFramebufferMixedSamplesCombinationNV>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.EnumValue(value["coverageReductionMode"], EnumFromString_VkCoverageReductionModeNV);
    ctx.EnumValue(value["rasterizationSamples"], EnumFromString_VkSampleCountFlagBits);
    ctx.FlagsValue(value["depthStencilSamples"], EnumFromString_VkSampleCountFlagBits);
    ctx.FlagsValue(value["colorSamples"], EnumFromString_VkSampleCountFlagBits);
}

template <> void StructFromApiDump<VkPhysicalDeviceFragmentShaderInterlockFeaturesEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["fragmentShaderSampleInterlock"]);
    ctx.UInt32Value(value["fragmentShaderPixelInterlock"]);
    ctx.UInt32Value(value["fragmentShaderShadingRateInterlock"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceYcbcrImageArraysFeaturesEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["ycbcrImageArrays"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceProvokingVertexFeaturesEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["provokingVertexLast"]);
    ctx.UInt32Value(value["transformFeedbackPreservesProvokingVertex"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceProvokingVertexPropertiesEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["provokingVertexModePerPipeline"]);
    ctx.UInt32Value(value["transformFeedbackPreservesTriangleFanProvokingVertex"]);
}

template <> void StructFromApiDump<VkPipelineRasterizationProvokingVertexStateCreateInfoEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.EnumValue(value["provokingVertexMode"], EnumFromString_VkProvokingVertexModeEXT);
}

template <> void StructFromApiDump<VkSurfaceFullScreenExclusiveInfoEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.EnumValue(value["fullScreenExclusive"], EnumFromString_VkFullScreenExclusiveEXT);
}

template <> void StructFromApiDump<VkSurfaceCapabilitiesFullScreenExclusiveEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["fullScreenExclusiveSupported"]);
}

template <> void StructFromApiDump<VkSurfaceFullScreenExclusiveWin32InfoEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.VoidPtrValue(value["hmonitor"]);
}

template <> void StructFromApiDump<VkHeadlessSurfaceCreateInfoEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.FlagsValue(value["flags"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceShaderAtomicFloatFeaturesEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["shaderBufferFloat32Atomics"]);
    ctx.UInt32Value(value["shaderBufferFloat32AtomicAdd"]);
    ctx.UInt32Value(value["shaderBufferFloat64Atomics"]);
    ctx.UInt32Value(value["shaderBufferFloat64AtomicAdd"]);
    ctx.UInt32Value(value["shaderSharedFloat32Atomics"]);
    ctx.UInt32Value(value["shaderSharedFloat32AtomicAdd"]);
    ctx.UInt32Value(value["shaderSharedFloat64Atomics"]);
    ctx.UInt32Value(value["shaderSharedFloat64AtomicAdd"]);
    ctx.UInt32Value(value["shaderImageFloat32Atomics"]);
    ctx.UInt32Value(value["shaderImageFloat32AtomicAdd"]);
    ctx.UInt32Value(value["sparseImageFloat32Atomics"]);
    ctx.UInt32Value(value["sparseImageFloat32AtomicAdd"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceExtendedDynamicStateFeaturesEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["extendedDynamicState"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceMapMemoryPlacedFeaturesEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["memoryMapPlaced"]);
    ctx.UInt32Value(value["memoryMapRangePlaced"]);
    ctx.UInt32Value(value["memoryUnmapReserve"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceMapMemoryPlacedPropertiesEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt64Value(value["minPlacedMemoryMapAlignment"]);
}

template <> void StructFromApiDump<VkMemoryMapPlacedInfoEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.VoidPtrValue(value["pPlacedAddress"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceShaderAtomicFloat2FeaturesEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["shaderBufferFloat16Atomics"]);
    ctx.UInt32Value(value["shaderBufferFloat16AtomicAdd"]);
    ctx.UInt32Value(value["shaderBufferFloat16AtomicMinMax"]);
    ctx.UInt32Value(value["shaderBufferFloat32AtomicMinMax"]);
    ctx.UInt32Value(value["shaderBufferFloat64AtomicMinMax"]);
    ctx.UInt32Value(value["shaderSharedFloat16Atomics"]);
    ctx.UInt32Value(value["shaderSharedFloat16AtomicAdd"]);
    ctx.UInt32Value(value["shaderSharedFloat16AtomicMinMax"]);
    ctx.UInt32Value(value["shaderSharedFloat32AtomicMinMax"]);
    ctx.UInt32Value(value["shaderSharedFloat64AtomicMinMax"]);
    ctx.UInt32Value(value["shaderImageFloat32AtomicMinMax"]);
    ctx.UInt32Value(value["sparseImageFloat32AtomicMinMax"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceDeviceGeneratedCommandsPropertiesNV>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["maxGraphicsShaderGroupCount"]);
    ctx.UInt32Value(value["maxIndirectSequenceCount"]);
    ctx.UInt32Value(value["maxIndirectCommandsTokenCount"]);
    ctx.UInt32Value(value["maxIndirectCommandsStreamCount"]);
    ctx.UInt32Value(value["maxIndirectCommandsTokenOffset"]);
    ctx.UInt32Value(value["maxIndirectCommandsStreamStride"]);
    ctx.UInt32Value(value["minSequencesCountBufferOffsetAlignment"]);
    ctx.UInt32Value(value["minSequencesIndexBufferOffsetAlignment"]);
    ctx.UInt32Value(value["minIndirectCommandsBufferOffsetAlignment"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceDeviceGeneratedCommandsFeaturesNV>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["deviceGeneratedCommands"]);
}

template <> void StructFromApiDump<VkGraphicsShaderGroupCreateInfoNV>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["stageCount"]);
    StructArrayFromApiDump<VkPipelineShaderStageCreateInfo>(ctx, value["pStages"], ctx.Length(value["stageCount"]));
    StructPtrFromApiDump<VkPipelineVertexInputStateCreateInfo>(ctx, value["pVertexInputState"]);
    StructPtrFromApiDump<VkPipelineTessellationStateCreateInfo>(ctx, value["pTessellationState"]);
}

template <> void StructFromApiDump<VkGraphicsPipelineShaderGroupsCreateInfoNV>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["groupCount"]);
    StructArrayFromApiDump<VkGraphicsShaderGroupCreateInfoNV>(ctx, value["pGroups"], ctx.Length(value["groupCount"]));
    ctx.UInt32Value(value["pipelineCount"]);
    ctx.VulkanHandleArray(value["pPipelines"], VK_OBJECT_TYPE_PIPELINE, ctx.Length(value["pipelineCount"]));
}

template <> void StructFromApiDump<VkBindShaderGroupIndirectCommandNV>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.UInt32Value(value["groupIndex"]);
}

template <> void StructFromApiDump<VkBindIndexBufferIndirectCommandNV>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.UInt64Value(value["bufferAddress"]);
    ctx.UInt32Value(value["size"]);
    ctx.EnumValue(value["indexType"], EnumFromString_VkIndexType);
}

template <> void StructFromApiDump<VkBindVertexBufferIndirectCommandNV>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.UInt64Value(value["bufferAddress"]);
    ctx.UInt32Value(value["size"]);
    ctx.UInt32Value(value["stride"]);
}

template <> void StructFromApiDump<VkSetStateFlagsIndirectCommandNV>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.UInt32Value(value["data"]);
}

template <> void StructFromApiDump<VkIndirectCommandsStreamNV>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.VulkanHandleValue(value["buffer"], VK_OBJECT_TYPE_BUFFER);
    ctx.UInt64Value(value["offset"]);
}

template <> void StructFromApiDump<VkIndirectCommandsLayoutTokenNV>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.EnumValue(value["tokenType"], EnumFromString_VkIndirectCommandsTokenTypeNV);
    ctx.UInt32Value(value["stream"]);
    ctx.UInt32Value(value["offset"]);
    ctx.UInt32Value(value["vertexBindingUnit"]);
    ctx.UInt32Value(value["vertexDynamicStride"]);
    ctx.VulkanHandleValue(value["pushconstantPipelineLayout"], VK_OBJECT_TYPE_PIPELINE_LAYOUT);
    ctx.FlagsValue(value["pushconstantShaderStageFlags"], EnumFromString_VkShaderStageFlagBits);
    ctx.UInt32Value(value["pushconstantOffset"]);
    ctx.UInt32Value(value["pushconstantSize"]);
    ctx.FlagsValue(value["indirectStateFlags"], EnumFromString_VkIndirectStateFlagBitsNV);
    ctx.UInt32Value(value["indexTypeCount"]);
    ctx.EnumArray(value["pIndexTypes"], EnumFromString_VkIndexType, ctx.Length(value["indexTypeCount"]));
    ctx.UInt32Array(value["pIndexTypeValues"], ctx.Length(value["indexTypeCount"]));
}

template <> void StructFromApiDump<VkIndirectCommandsLayoutCreateInfoNV>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.FlagsValue(value["flags"], EnumFromString_VkIndirectCommandsLayoutUsageFlagBitsNV);
    ctx.EnumValue(value["pipelineBindPoint"], EnumFromString_VkPipelineBindPoint);
    ctx.UInt32Value(value["tokenCount"]);
    StructArrayFromApiDump<VkIndirectCommandsLayoutTokenNV>(ctx, value["pTokens"], ctx.Length(value["tokenCount"]));
    ctx.UInt32Value(value["streamCount"]);
    ctx.UInt32Array(value["pStreamStrides"], ctx.Length(value["streamCount"]));
}

template <> void StructFromApiDump<VkGeneratedCommandsInfoNV>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.EnumValue(value["pipelineBindPoint"], EnumFromString_VkPipelineBindPoint);
    ctx.VulkanHandleValue(value["pipeline"], VK_OBJECT_TYPE_PIPELINE);
    ctx.VulkanHandleValue(value["indirectCommandsLayout"], VK_OBJECT_TYPE_INDIRECT_COMMANDS_LAYOUT_NV);
    ctx.UInt32Value(value["streamCount"]);
    StructArrayFromApiDump<VkIndirectCommandsStreamNV>(ctx, value["pStreams"], ctx.Length(value["streamCount"]));
    ctx.UInt32Value(value["sequencesCount"]);
    ctx.VulkanHandleValue(value["preprocessBuffer"], VK_OBJECT_TYPE_BUFFER);
    ctx.UInt64Value(value["preprocessOffset"]);
    ctx.UInt64Value(value["preprocessSize"]);
    ctx.VulkanHandleValue(value["sequencesCountBuffer"], VK_OBJECT_TYPE_BUFFER);
    ctx.UInt64Value(value["sequencesCountOffset"]);
    ctx.VulkanHandleValue(value["sequencesIndexBuffer"], VK_OBJECT_TYPE_BUFFER);
    ctx.UInt64Value(value["sequencesIndexOffset"]);
}

template <> void StructFromApiDump<VkGeneratedCommandsMemoryRequirementsInfoNV>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.EnumValue(value["pipelineBindPoint"], EnumFromString_VkPipelineBindPoint);
    ctx.VulkanHandleValue(value["pipeline"], VK_OBJECT_TYPE_PIPELINE);
    ctx.VulkanHandleValue(value["indirectCommandsLayout"], VK_OBJECT_TYPE_INDIRECT_COMMANDS_LAYOUT_NV);
    ctx.UInt32Value(value["maxSequencesCount"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceInheritedViewportScissorFeaturesNV>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["inheritedViewportScissor2D"]);
}

template <> void StructFromApiDump<VkCommandBufferInheritanceViewportScissorInfoNV>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["viewportScissor2D"]);
    ctx.UInt32Value(value["viewportDepthCount"]);
    StructPtrFromApiDump<VkViewport>(ctx, value["pViewportDepths"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceTexelBufferAlignmentFeaturesEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["texelBufferAlignment"]);
}

template <> void StructFromApiDump<VkRenderPassTransformBeginInfoQCOM>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.EnumValue(value["transform"], EnumFromString_VkSurfaceTransformFlagBitsKHR);
}

template <> void StructFromApiDump<VkCommandBufferInheritanceRenderPassTransformInfoQCOM>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.EnumValue(value["transform"], EnumFromString_VkSurfaceTransformFlagBitsKHR);
    StructFromApiDump<VkRect2D>(ctx, value["renderArea"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceDepthBiasControlFeaturesEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["depthBiasControl"]);
    ctx.UInt32Value(value["leastRepresentableValueForceUnormRepresentation"]);
    ctx.UInt32Value(value["floatRepresentation"]);
    ctx.UInt32Value(value["depthBiasExact"]);
}

template <> void StructFromApiDump<VkDepthBiasInfoEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.FloatValue(value["depthBiasConstantFactor"]);
    ctx.FloatValue(value["depthBiasClamp"]);
    ctx.FloatValue(value["depthBiasSlopeFactor"]);
}

template <> void StructFromApiDump<VkDepthBiasRepresentationInfoEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.EnumValue(value["depthBiasRepresentation"], EnumFromString_VkDepthBiasRepresentationEXT);
    ctx.UInt32Value(value["depthBiasExact"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceDeviceMemoryReportFeaturesEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["deviceMemoryReport"]);
}

template <> void StructFromApiDump<VkDeviceMemoryReportCallbackDataEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.FlagsValue(value["flags"]);
    ctx.EnumValue(value["type"], EnumFromString_VkDeviceMemoryReportEventTypeEXT);
    ctx.UInt64Value(value["memoryObjectId"]);
    ctx.UInt64Value(value["size"]);
    ctx.EnumValue(value["objectType"], EnumFromString_VkObjectType);
    ctx.UInt64Value(value["objectHandle"]);
    ctx.UInt32Value(value["heapIndex"]);
}

template <> void StructFromApiDump<VkDeviceDeviceMemoryReportCreateInfoEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.FlagsValue(value["flags"]);
    ctx.FunctionPtrValue(value["pfnUserCallback"]);
    ctx.VoidPtrValue(value["pUserData"]);
}

template <> void StructFromApiDump<VkSamplerCustomBorderColorCreateInfoEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    StructFromApiDump<VkClearColorValue>(ctx, value["customBorderColor"]);
    ctx.EnumValue(value["format"], EnumFromString_VkFormat);
}

template <> void StructFromApiDump<VkPhysicalDeviceCustomBorderColorPropertiesEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["maxCustomBorderColorSamplers"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceCustomBorderColorFeaturesEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["customBorderColors"]);
    ctx.UInt32Value(value["customBorderColorWithoutFormat"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceTextureCompressionASTC3DFeaturesEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["textureCompressionASTC_3D"]);
}

template <> void StructFromApiDump<VkPhysicalDevicePresentBarrierFeaturesNV>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["presentBarrier"]);
}

template <> void StructFromApiDump<VkSurfaceCapabilitiesPresentBarrierNV>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["presentBarrierSupported"]);
}

template <> void StructFromApiDump<VkSwapchainPresentBarrierCreateInfoNV>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["presentBarrierEnable"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceDiagnosticsConfigFeaturesNV>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["diagnosticsConfig"]);
}

template <> void StructFromApiDump<VkDeviceDiagnosticsConfigCreateInfoNV>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.FlagsValue(value["flags"], EnumFromString_VkDeviceDiagnosticsConfigFlagBitsNV);
}

template <> void StructFromApiDump<VkPerfHintInfoQCOM>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.EnumValue(value["type"], EnumFromString_VkPerfHintTypeQCOM);
    ctx.UInt32Value(value["scale"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceQueuePerfHintFeaturesQCOM>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["queuePerfHint"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceQueuePerfHintPropertiesQCOM>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.FlagsValue(value["supportedQueues"], EnumFromString_VkQueueFlagBits);
}

template <> void StructFromApiDump<VkPhysicalDeviceImageProcessing3FeaturesQCOM>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["imageGatherLinear"]);
    ctx.UInt32Value(value["imageGatherExtendedModes"]);
    ctx.UInt32Value(value["blockMatchExtendedClampToEdge"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceShaderMultipleWaitQueuesFeaturesQCOM>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["shaderMultipleWaitQueues"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceShaderMultipleWaitQueuesPropertiesQCOM>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["maxShaderWaitQueues"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceShaderSplitBarrierFeaturesEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["shaderSplitBarrier"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceShaderSplitBarrierPropertiesEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["splitBarrierReservedSharedMemory"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceTileShadingFeaturesQCOM>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["tileShading"]);
    ctx.UInt32Value(value["tileShadingFragmentStage"]);
    ctx.UInt32Value(value["tileShadingColorAttachments"]);
    ctx.UInt32Value(value["tileShadingDepthAttachments"]);
    ctx.UInt32Value(value["tileShadingStencilAttachments"]);
    ctx.UInt32Value(value["tileShadingInputAttachments"]);
    ctx.UInt32Value(value["tileShadingSampledAttachments"]);
    ctx.UInt32Value(value["tileShadingPerTileDraw"]);
    ctx.UInt32Value(value["tileShadingPerTileDispatch"]);
    ctx.UInt32Value(value["tileShadingDispatchTile"]);
    ctx.UInt32Value(value["tileShadingApron"]);
    ctx.UInt32Value(value["tileShadingAnisotropicApron"]);
    ctx.UInt32Value(value["tileShadingAtomicOps"]);
    ctx.UInt32Value(value["tileShadingImageProcessing"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceTileShadingPropertiesQCOM>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["maxApronSize"]);
    ctx.UInt32Value(value["preferNonCoherent"]);
    StructFromApiDump<VkExtent2D>(ctx, value["tileGranularity"]);
    StructFromApiDump<VkExtent2D>(ctx, value["maxTileShadingRate"]);
}

template <> void StructFromApiDump<VkRenderPassTileShadingCreateInfoQCOM>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.FlagsValue(value["flags"], EnumFromString_VkTileShadingRenderPassFlagBitsQCOM);
    StructFromApiDump<VkExtent2D>(ctx, value["tileApronSize"]);
}

template <> void StructFromApiDump<VkPerTileBeginInfoQCOM>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
}

template <> void StructFromApiDump<VkPerTileEndInfoQCOM>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
}

template <> void StructFromApiDump<VkDispatchTileInfoQCOM>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceDescriptorBufferPropertiesEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["combinedImageSamplerDescriptorSingleArray"]);
    ctx.UInt32Value(value["bufferlessPushDescriptors"]);
    ctx.UInt32Value(value["allowSamplerImageViewPostSubmitCreation"]);
    ctx.UInt64Value(value["descriptorBufferOffsetAlignment"]);
    ctx.UInt32Value(value["maxDescriptorBufferBindings"]);
    ctx.UInt32Value(value["maxResourceDescriptorBufferBindings"]);
    ctx.UInt32Value(value["maxSamplerDescriptorBufferBindings"]);
    ctx.UInt32Value(value["maxEmbeddedImmutableSamplerBindings"]);
    ctx.UInt32Value(value["maxEmbeddedImmutableSamplers"]);
    ctx.SizeTValue(value["bufferCaptureReplayDescriptorDataSize"]);
    ctx.SizeTValue(value["imageCaptureReplayDescriptorDataSize"]);
    ctx.SizeTValue(value["imageViewCaptureReplayDescriptorDataSize"]);
    ctx.SizeTValue(value["samplerCaptureReplayDescriptorDataSize"]);
    ctx.SizeTValue(value["accelerationStructureCaptureReplayDescriptorDataSize"]);
    ctx.SizeTValue(value["samplerDescriptorSize"]);
    ctx.SizeTValue(value["combinedImageSamplerDescriptorSize"]);
    ctx.SizeTValue(value["sampledImageDescriptorSize"]);
    ctx.SizeTValue(value["storageImageDescriptorSize"]);
    ctx.SizeTValue(value["uniformTexelBufferDescriptorSize"]);
    ctx.SizeTValue(value["robustUniformTexelBufferDescriptorSize"]);
    ctx.SizeTValue(value["storageTexelBufferDescriptorSize"]);
    ctx.SizeTValue(value["robustStorageTexelBufferDescriptorSize"]);
    ctx.SizeTValue(value["uniformBufferDescriptorSize"]);
    ctx.SizeTValue(value["robustUniformBufferDescriptorSize"]);
    ctx.SizeTValue(value["storageBufferDescriptorSize"]);
    ctx.SizeTValue(value["robustStorageBufferDescriptorSize"]);
    ctx.SizeTValue(value["inputAttachmentDescriptorSize"]);
    ctx.SizeTValue(value["accelerationStructureDescriptorSize"]);
    ctx.UInt64Value(value["maxSamplerDescriptorBufferRange"]);
    ctx.UInt64Value(value["maxResourceDescriptorBufferRange"]);
    ctx.UInt64Value(value["samplerDescriptorBufferAddressSpaceSize"]);
    ctx.UInt64Value(value["resourceDescriptorBufferAddressSpaceSize"]);
    ctx.UInt64Value(value["descriptorBufferAddressSpaceSize"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceDescriptorBufferFeaturesEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["descriptorBuffer"]);
    ctx.UInt32Value(value["descriptorBufferCaptureReplay"]);
    ctx.UInt32Value(value["descriptorBufferImageLayoutIgnored"]);
    ctx.UInt32Value(value["descriptorBufferPushDescriptors"]);
}

template <> void StructFromApiDump<VkDescriptorAddressInfoEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt64Value(value["address"]);
    ctx.UInt64Value(value["range"]);
    ctx.EnumValue(value["format"], EnumFromString_VkFormat);
}

template <> void StructFromApiDump<VkDescriptorBufferBindingInfoEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt64Value(value["address"]);
    ctx.FlagsValue(value["usage"], EnumFromString_VkBufferUsageFlagBits);
}

template <> void StructFromApiDump<VkDescriptorBufferBindingPushDescriptorBufferHandleEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.VulkanHandleValue(value["buffer"], VK_OBJECT_TYPE_BUFFER);
}

template <> void StructFromApiDump<VkBufferCaptureDescriptorDataInfoEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.VulkanHandleValue(value["buffer"], VK_OBJECT_TYPE_BUFFER);
}

template <> void StructFromApiDump<VkImageCaptureDescriptorDataInfoEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.VulkanHandleValue(value["image"], VK_OBJECT_TYPE_IMAGE);
}

template <> void StructFromApiDump<VkImageViewCaptureDescriptorDataInfoEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.VulkanHandleValue(value["imageView"], VK_OBJECT_TYPE_IMAGE_VIEW);
}

template <> void StructFromApiDump<VkSamplerCaptureDescriptorDataInfoEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.VulkanHandleValue(value["sampler"], VK_OBJECT_TYPE_SAMPLER);
}

template <> void StructFromApiDump<VkOpaqueCaptureDescriptorDataCreateInfoEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.VoidPtrValue(value["opaqueCaptureDescriptorData"]);
}

template <> void StructFromApiDump<VkAccelerationStructureCaptureDescriptorDataInfoEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.VulkanHandleValue(value["accelerationStructure"], VK_OBJECT_TYPE_ACCELERATION_STRUCTURE_KHR);
    ctx.VulkanHandleValue(value["accelerationStructureNV"], VK_OBJECT_TYPE_ACCELERATION_STRUCTURE_NV);
}

template <> void StructFromApiDump<VkPhysicalDeviceDescriptorBufferDensityMapPropertiesEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.SizeTValue(value["combinedImageSamplerDensityMapDescriptorSize"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceGraphicsPipelineLibraryFeaturesEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["graphicsPipelineLibrary"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceGraphicsPipelineLibraryPropertiesEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["graphicsPipelineLibraryFastLinking"]);
    ctx.UInt32Value(value["graphicsPipelineLibraryIndependentInterpolationDecoration"]);
}

template <> void StructFromApiDump<VkGraphicsPipelineLibraryCreateInfoEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.FlagsValue(value["flags"], EnumFromString_VkGraphicsPipelineLibraryFlagBitsEXT);
}

template <> void StructFromApiDump<VkPhysicalDeviceShaderEarlyAndLateFragmentTestsFeaturesAMD>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["shaderEarlyAndLateFragmentTests"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceFragmentShadingRateEnumsFeaturesNV>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["fragmentShadingRateEnums"]);
    ctx.UInt32Value(value["supersampleFragmentShadingRates"]);
    ctx.UInt32Value(value["noInvocationFragmentShadingRates"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceFragmentShadingRateEnumsPropertiesNV>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.EnumValue(value["maxFragmentShadingRateInvocationCount"], EnumFromString_VkSampleCountFlagBits);
}

template <> void StructFromApiDump<VkPipelineFragmentShadingRateEnumStateCreateInfoNV>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.EnumValue(value["shadingRateType"], EnumFromString_VkFragmentShadingRateTypeNV);
    ctx.EnumValue(value["shadingRate"], EnumFromString_VkFragmentShadingRateNV);
    ctx.EnumArray(value["combinerOps"], EnumFromString_VkFragmentShadingRateCombinerOpKHR, 2);
}

template <> void StructFromApiDump<VkAccelerationStructureGeometryMotionTrianglesDataNV>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    StructFromApiDump<VkDeviceOrHostAddressConstKHR>(ctx, value["vertexData"]);
}

template <> void StructFromApiDump<VkAccelerationStructureMotionInfoNV>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["maxInstances"]);
    ctx.FlagsValue(value["flags"]);
}

template <> void StructFromApiDump<VkAccelerationStructureMatrixMotionInstanceNV>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    StructFromApiDump<VkTransformMatrixKHR>(ctx, value["transformT0"]);
    StructFromApiDump<VkTransformMatrixKHR>(ctx, value["transformT1"]);
    ctx.UInt32Value(value["instanceCustomIndex"]);
    ctx.UInt32Value(value["mask"]);
    ctx.UInt32Value(value["instanceShaderBindingTableRecordOffset"]);
    ctx.FlagsValue(value["flags"], EnumFromString_VkGeometryInstanceFlagBitsKHR);
    ctx.UInt64Value(value["accelerationStructureReference"]);
}

template <> void StructFromApiDump<VkSRTDataNV>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.FloatValue(value["sx"]);
    ctx.FloatValue(value["a"]);
    ctx.FloatValue(value["b"]);
    ctx.FloatValue(value["pvx"]);
    ctx.FloatValue(value["sy"]);
    ctx.FloatValue(value["c"]);
    ctx.FloatValue(value["pvy"]);
    ctx.FloatValue(value["sz"]);
    ctx.FloatValue(value["pvz"]);
    ctx.FloatValue(value["qx"]);
    ctx.FloatValue(value["qy"]);
    ctx.FloatValue(value["qz"]);
    ctx.FloatValue(value["qw"]);
    ctx.FloatValue(value["tx"]);
    ctx.FloatValue(value["ty"]);
    ctx.FloatValue(value["tz"]);
}

template <> void StructFromApiDump<VkAccelerationStructureSRTMotionInstanceNV>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    StructFromApiDump<VkSRTDataNV>(ctx, value["transformT0"]);
    StructFromApiDump<VkSRTDataNV>(ctx, value["transformT1"]);
    ctx.UInt32Value(value["instanceCustomIndex"]);
    ctx.UInt32Value(value["mask"]);
    ctx.UInt32Value(value["instanceShaderBindingTableRecordOffset"]);
    ctx.FlagsValue(value["flags"], EnumFromString_VkGeometryInstanceFlagBitsKHR);
    ctx.UInt64Value(value["accelerationStructureReference"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceRayTracingMotionBlurFeaturesNV>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["rayTracingMotionBlur"]);
    ctx.UInt32Value(value["rayTracingMotionBlurPipelineTraceRaysIndirect"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceYcbcr2Plane444FormatsFeaturesEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["ycbcr2plane444Formats"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceFragmentDensityMap2FeaturesEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["fragmentDensityMapDeferred"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceFragmentDensityMap2PropertiesEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["subsampledLoads"]);
    ctx.UInt32Value(value["subsampledCoarseReconstructionEarlyAccess"]);
    ctx.UInt32Value(value["maxSubsampledArrayLayers"]);
    ctx.UInt32Value(value["maxDescriptorSetSubsampledSamplers"]);
}

template <> void StructFromApiDump<VkCopyCommandTransformInfoQCOM>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.EnumValue(value["transform"], EnumFromString_VkSurfaceTransformFlagBitsKHR);
}

template <> void StructFromApiDump<VkPhysicalDeviceImageCompressionControlFeaturesEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["imageCompressionControl"]);
}

template <> void StructFromApiDump<VkImageCompressionControlEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.FlagsValue(value["flags"], EnumFromString_VkImageCompressionFlagBitsEXT);
    ctx.UInt32Value(value["compressionControlPlaneCount"]);
    ctx.FlagsArray(value["pFixedRateFlags"], EnumFromString_VkImageCompressionFixedRateFlagBitsEXT, ctx.Length(value["compressionControlPlaneCount"]));
}

template <> void StructFromApiDump<VkImageCompressionPropertiesEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.FlagsValue(value["imageCompressionFlags"], EnumFromString_VkImageCompressionFlagBitsEXT);
    ctx.FlagsValue(value["imageCompressionFixedRateFlags"], EnumFromString_VkImageCompressionFixedRateFlagBitsEXT);
}

template <> void StructFromApiDump<VkPhysicalDeviceAttachmentFeedbackLoopLayoutFeaturesEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["attachmentFeedbackLoopLayout"]);
}

template <> void StructFromApiDump<VkPhysicalDevice4444FormatsFeaturesEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["formatA4R4G4B4"]);
    ctx.UInt32Value(value["formatA4B4G4R4"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceFaultFeaturesEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["deviceFault"]);
    ctx.UInt32Value(value["deviceFaultVendorBinary"]);
}

template <> void StructFromApiDump<VkDeviceFaultCountsEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["addressInfoCount"]);
    ctx.UInt32Value(value["vendorInfoCount"]);
    ctx.UInt64Value(value["vendorBinarySize"]);
}

template <> void StructFromApiDump<VkDeviceFaultInfoEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.StringValue(value["description"]);
    StructPtrFromApiDump<VkDeviceFaultAddressInfoKHR>(ctx, value["pAddressInfos"]);
    StructPtrFromApiDump<VkDeviceFaultVendorInfoKHR>(ctx, value["pVendorInfos"]);
    ctx.VoidPtrValue(value["pVendorBinaryData"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceRasterizationOrderAttachmentAccessFeaturesEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["rasterizationOrderColorAttachmentAccess"]);
    ctx.UInt32Value(value["rasterizationOrderDepthAttachmentAccess"]);
    ctx.UInt32Value(value["rasterizationOrderStencilAttachmentAccess"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceRGBA10X6FormatsFeaturesEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["formatRgba10x6WithoutYCbCrSampler"]);
}

template <> void StructFromApiDump<VkDirectFBSurfaceCreateInfoEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.FlagsValue(value["flags"]);
    ctx.VoidPtrValue(value["dfb"]);
    ctx.VoidPtrValue(value["surface"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceMutableDescriptorTypeFeaturesEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["mutableDescriptorType"]);
}

template <> void StructFromApiDump<VkMutableDescriptorTypeListEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.UInt32Value(value["descriptorTypeCount"]);
    ctx.EnumArray(value["pDescriptorTypes"], EnumFromString_VkDescriptorType, ctx.Length(value["descriptorTypeCount"]));
}

template <> void StructFromApiDump<VkMutableDescriptorTypeCreateInfoEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["mutableDescriptorTypeListCount"]);
    StructArrayFromApiDump<VkMutableDescriptorTypeListEXT>(ctx, value["pMutableDescriptorTypeLists"], ctx.Length(value["mutableDescriptorTypeListCount"]));
}

template <> void StructFromApiDump<VkPhysicalDeviceVertexInputDynamicStateFeaturesEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["vertexInputDynamicState"]);
}

template <> void StructFromApiDump<VkVertexInputBindingDescription2EXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["binding"]);
    ctx.UInt32Value(value["stride"]);
    ctx.EnumValue(value["inputRate"], EnumFromString_VkVertexInputRate);
    ctx.UInt32Value(value["divisor"]);
}

template <> void StructFromApiDump<VkVertexInputAttributeDescription2EXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["location"]);
    ctx.UInt32Value(value["binding"]);
    ctx.EnumValue(value["format"], EnumFromString_VkFormat);
    ctx.UInt32Value(value["offset"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceDrmPropertiesEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["hasPrimary"]);
    ctx.UInt32Value(value["hasRender"]);
    ctx.Int64Value(value["primaryMajor"]);
    ctx.Int64Value(value["primaryMinor"]);
    ctx.Int64Value(value["renderMajor"]);
    ctx.Int64Value(value["renderMinor"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceAddressBindingReportFeaturesEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["reportAddressBinding"]);
}

template <> void StructFromApiDump<VkDeviceAddressBindingCallbackDataEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.FlagsValue(value["flags"], EnumFromString_VkDeviceAddressBindingFlagBitsEXT);
    ctx.UInt64Value(value["baseAddress"]);
    ctx.UInt64Value(value["size"]);
    ctx.EnumValue(value["bindingType"], EnumFromString_VkDeviceAddressBindingTypeEXT);
}

template <> void StructFromApiDump<VkPhysicalDeviceDepthClipControlFeaturesEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["depthClipControl"]);
}

template <> void StructFromApiDump<VkPipelineViewportDepthClipControlCreateInfoEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["negativeOneToOne"]);
}

template <> void StructFromApiDump<VkPhysicalDevicePrimitiveTopologyListRestartFeaturesEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["primitiveTopologyListRestart"]);
    ctx.UInt32Value(value["primitiveTopologyPatchListRestart"]);
}

template <> void StructFromApiDump<VkImportMemoryZirconHandleInfoFUCHSIA>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.EnumValue(value["handleType"], EnumFromString_VkExternalMemoryHandleTypeFlagBits);
    ctx.UInt32Value(value["handle"]);
}

template <> void StructFromApiDump<VkMemoryZirconHandlePropertiesFUCHSIA>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["memoryTypeBits"]);
}

template <> void StructFromApiDump<VkMemoryGetZirconHandleInfoFUCHSIA>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.VulkanHandleValue(value["memory"], VK_OBJECT_TYPE_DEVICE_MEMORY);
    ctx.EnumValue(value["handleType"], EnumFromString_VkExternalMemoryHandleTypeFlagBits);
}

template <> void StructFromApiDump<VkImportSemaphoreZirconHandleInfoFUCHSIA>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.VulkanHandleValue(value["semaphore"], VK_OBJECT_TYPE_SEMAPHORE);
    ctx.FlagsValue(value["flags"], EnumFromString_VkSemaphoreImportFlagBits);
    ctx.EnumValue(value["handleType"], EnumFromString_VkExternalSemaphoreHandleTypeFlagBits);
    ctx.UInt32Value(value["zirconHandle"]);
}

template <> void StructFromApiDump<VkSemaphoreGetZirconHandleInfoFUCHSIA>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.VulkanHandleValue(value["semaphore"], VK_OBJECT_TYPE_SEMAPHORE);
    ctx.EnumValue(value["handleType"], EnumFromString_VkExternalSemaphoreHandleTypeFlagBits);
}

template <> void StructFromApiDump<VkPhysicalDeviceInvocationMaskFeaturesHUAWEI>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["invocationMask"]);
}

template <> void StructFromApiDump<VkMemoryGetRemoteAddressInfoNV>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.VulkanHandleValue(value["memory"], VK_OBJECT_TYPE_DEVICE_MEMORY);
    ctx.EnumValue(value["handleType"], EnumFromString_VkExternalMemoryHandleTypeFlagBits);
}

template <> void StructFromApiDump<VkPhysicalDeviceExternalMemoryRDMAFeaturesNV>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["externalMemoryRDMA"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceFrameBoundaryFeaturesEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["frameBoundary"]);
}

template <> void StructFromApiDump<VkFrameBoundaryEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.FlagsValue(value["flags"], EnumFromString_VkFrameBoundaryFlagBitsEXT);
    ctx.UInt64Value(value["frameID"]);
    ctx.UInt32Value(value["imageCount"]);
    ctx.VulkanHandleArray(value["pImages"], VK_OBJECT_TYPE_IMAGE, ctx.Length(value["imageCount"]));
    ctx.UInt32Value(value["bufferCount"]);
    ctx.VulkanHandleArray(value["pBuffers"], VK_OBJECT_TYPE_BUFFER, ctx.Length(value["bufferCount"]));
    ctx.UInt64Value(value["tagName"]);
    ctx.SizeTValue(value["tagSize"]);
    ctx.UInt8Array(value["pTag"], ctx.Length(value["tagSize"]));
}

template <> void StructFromApiDump<VkPhysicalDeviceMultisampledRenderToSingleSampledFeaturesEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["multisampledRenderToSingleSampled"]);
}

template <> void StructFromApiDump<VkSubpassResolvePerformanceQueryEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["optimal"]);
}

template <> void StructFromApiDump<VkMultisampledRenderToSingleSampledInfoEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["multisampledRenderToSingleSampledEnable"]);
    ctx.EnumValue(value["rasterizationSamples"], EnumFromString_VkSampleCountFlagBits);
}

template <> void StructFromApiDump<VkPhysicalDeviceExtendedDynamicState2FeaturesEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["extendedDynamicState2"]);
    ctx.UInt32Value(value["extendedDynamicState2LogicOp"]);
    ctx.UInt32Value(value["extendedDynamicState2PatchControlPoints"]);
}

template <> void StructFromApiDump<VkScreenSurfaceCreateInfoQNX>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.FlagsValue(value["flags"]);
    ctx.VoidPtrValue(value["context"]);
    ctx.VoidPtrValue(value["window"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceColorWriteEnableFeaturesEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["colorWriteEnable"]);
}

template <> void StructFromApiDump<VkPipelineColorWriteCreateInfoEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["attachmentCount"]);
    ctx.UInt32Array(value["pColorWriteEnables"], ctx.Length(value["attachmentCount"]));
}

template <> void StructFromApiDump<VkPhysicalDevicePrimitivesGeneratedQueryFeaturesEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["primitivesGeneratedQuery"]);
    ctx.UInt32Value(value["primitivesGeneratedQueryWithRasterizerDiscard"]);
    ctx.UInt32Value(value["primitivesGeneratedQueryWithNonZeroStreams"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceVideoEncodeRgbConversionFeaturesVALVE>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["videoEncodeRgbConversion"]);
}

template <> void StructFromApiDump<VkVideoEncodeRgbConversionCapabilitiesVALVE>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.FlagsValue(value["rgbModels"], EnumFromString_VkVideoEncodeRgbModelConversionFlagBitsVALVE);
    ctx.FlagsValue(value["rgbRanges"], EnumFromString_VkVideoEncodeRgbRangeCompressionFlagBitsVALVE);
    ctx.FlagsValue(value["xChromaOffsets"], EnumFromString_VkVideoEncodeRgbChromaOffsetFlagBitsVALVE);
    ctx.FlagsValue(value["yChromaOffsets"], EnumFromString_VkVideoEncodeRgbChromaOffsetFlagBitsVALVE);
}

template <> void StructFromApiDump<VkVideoEncodeProfileRgbConversionInfoVALVE>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["performEncodeRgbConversion"]);
}

template <> void StructFromApiDump<VkVideoEncodeSessionRgbConversionCreateInfoVALVE>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.EnumValue(value["rgbModel"], EnumFromString_VkVideoEncodeRgbModelConversionFlagBitsVALVE);
    ctx.EnumValue(value["rgbRange"], EnumFromString_VkVideoEncodeRgbRangeCompressionFlagBitsVALVE);
    ctx.EnumValue(value["xChromaOffset"], EnumFromString_VkVideoEncodeRgbChromaOffsetFlagBitsVALVE);
    ctx.EnumValue(value["yChromaOffset"], EnumFromString_VkVideoEncodeRgbChromaOffsetFlagBitsVALVE);
}

template <> void StructFromApiDump<VkPhysicalDeviceImageViewMinLodFeaturesEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["minLod"]);
}

template <> void StructFromApiDump<VkImageViewMinLodCreateInfoEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.FloatValue(value["minLod"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceMultiDrawFeaturesEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["multiDraw"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceMultiDrawPropertiesEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["maxMultiDrawCount"]);
}

template <> void StructFromApiDump<VkMultiDrawInfoEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.UInt32Value(value["firstVertex"]);
    ctx.UInt32Value(value["vertexCount"]);
}

template <> void StructFromApiDump<VkMultiDrawIndexedInfoEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.UInt32Value(value["firstIndex"]);
    ctx.UInt32Value(value["indexCount"]);
    ctx.Int32Value(value["vertexOffset"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceImage2DViewOf3DFeaturesEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["image2DViewOf3D"]);
    ctx.UInt32Value(value["sampler2DViewOf3D"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceShaderTileImageFeaturesEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["shaderTileImageColorReadAccess"]);
    ctx.UInt32Value(value["shaderTileImageDepthReadAccess"]);
    ctx.UInt32Value(value["shaderTileImageStencilReadAccess"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceShaderTileImagePropertiesEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["shaderTileImageCoherentReadAccelerated"]);
    ctx.UInt32Value(value["shaderTileImageReadSampleFromPixelRateInvocation"]);
    ctx.UInt32Value(value["shaderTileImageReadFromHelperInvocation"]);
}

template <> void StructFromApiDump<VkMicromapUsageEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.UInt32Value(value["count"]);
    ctx.UInt32Value(value["subdivisionLevel"]);
    ctx.UInt32Value(value["format"]);
}

template <> void StructFromApiDump<VkMicromapBuildInfoEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.EnumValue(value["type"], EnumFromString_VkMicromapTypeEXT);
    ctx.FlagsValue(value["flags"], EnumFromString_VkBuildMicromapFlagBitsEXT);
    ctx.EnumValue(value["mode"], EnumFromString_VkBuildMicromapModeEXT);
    ctx.VulkanHandleValue(value["dstMicromap"], VK_OBJECT_TYPE_MICROMAP_EXT);
    ctx.UInt32Value(value["usageCountsCount"]);
    StructArrayFromApiDump<VkMicromapUsageEXT>(ctx, value["pUsageCounts"], ctx.Length(value["usageCountsCount"]));
    StructArrayFromApiDump<VkMicromapUsageEXT>(ctx, value["ppUsageCounts"], (ctx.Length(value["usageCountsCount"]),1));
    StructFromApiDump<VkDeviceOrHostAddressConstKHR>(ctx, value["data"]);
    StructFromApiDump<VkDeviceOrHostAddressKHR>(ctx, value["scratchData"]);
    StructFromApiDump<VkDeviceOrHostAddressConstKHR>(ctx, value["triangleArray"]);
    ctx.UInt64Value(value["triangleArrayStride"]);
}

template <> void StructFromApiDump<VkMicromapCreateInfoEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.FlagsValue(value["createFlags"], EnumFromString_VkMicromapCreateFlagBitsEXT);
    ctx.VulkanHandleValue(value["buffer"], VK_OBJECT_TYPE_BUFFER);
    ctx.UInt64Value(value["offset"]);
    ctx.UInt64Value(value["size"]);
    ctx.EnumValue(value["type"], EnumFromString_VkMicromapTypeEXT);
    ctx.UInt64Value(value["deviceAddress"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceOpacityMicromapFeaturesEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["micromap"]);
    ctx.UInt32Value(value["micromapCaptureReplay"]);
    ctx.UInt32Value(value["micromapHostCommands"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceOpacityMicromapPropertiesEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["maxOpacity2StateSubdivisionLevel"]);
    ctx.UInt32Value(value["maxOpacity4StateSubdivisionLevel"]);
}

template <> void StructFromApiDump<VkMicromapVersionInfoEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt8Array(value["pVersionData"]);
}

template <> void StructFromApiDump<VkCopyMicromapToMemoryInfoEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.VulkanHandleValue(value["src"], VK_OBJECT_TYPE_MICROMAP_EXT);
    StructFromApiDump<VkDeviceOrHostAddressKHR>(ctx, value["dst"]);
    ctx.EnumValue(value["mode"], EnumFromString_VkCopyMicromapModeEXT);
}

template <> void StructFromApiDump<VkCopyMemoryToMicromapInfoEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    StructFromApiDump<VkDeviceOrHostAddressConstKHR>(ctx, value["src"]);
    ctx.VulkanHandleValue(value["dst"], VK_OBJECT_TYPE_MICROMAP_EXT);
    ctx.EnumValue(value["mode"], EnumFromString_VkCopyMicromapModeEXT);
}

template <> void StructFromApiDump<VkCopyMicromapInfoEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.VulkanHandleValue(value["src"], VK_OBJECT_TYPE_MICROMAP_EXT);
    ctx.VulkanHandleValue(value["dst"], VK_OBJECT_TYPE_MICROMAP_EXT);
    ctx.EnumValue(value["mode"], EnumFromString_VkCopyMicromapModeEXT);
}

template <> void StructFromApiDump<VkMicromapBuildSizesInfoEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt64Value(value["micromapSize"]);
    ctx.UInt64Value(value["buildScratchSize"]);
    ctx.UInt32Value(value["discardable"]);
}

template <> void StructFromApiDump<VkAccelerationStructureTrianglesOpacityMicromapEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.EnumValue(value["indexType"], EnumFromString_VkIndexType);
    StructFromApiDump<VkDeviceOrHostAddressConstKHR>(ctx, value["indexBuffer"]);
    ctx.UInt64Value(value["indexStride"]);
    ctx.UInt32Value(value["baseTriangle"]);
    ctx.UInt32Value(value["usageCountsCount"]);
    StructArrayFromApiDump<VkMicromapUsageEXT>(ctx, value["pUsageCounts"], ctx.Length(value["usageCountsCount"]));
    StructArrayFromApiDump<VkMicromapUsageEXT>(ctx, value["ppUsageCounts"], (ctx.Length(value["usageCountsCount"]),1));
    ctx.VulkanHandleValue(value["micromap"], VK_OBJECT_TYPE_MICROMAP_EXT);
}

template <> void StructFromApiDump<VkPhysicalDeviceDisplacementMicromapFeaturesNV>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["displacementMicromap"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceDisplacementMicromapPropertiesNV>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["maxDisplacementMicromapSubdivisionLevel"]);
}

template <> void StructFromApiDump<VkAccelerationStructureTrianglesDisplacementMicromapNV>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.EnumValue(value["displacementBiasAndScaleFormat"], EnumFromString_VkFormat);
    ctx.EnumValue(value["displacementVectorFormat"], EnumFromString_VkFormat);
    StructFromApiDump<VkDeviceOrHostAddressConstKHR>(ctx, value["displacementBiasAndScaleBuffer"]);
    ctx.UInt64Value(value["displacementBiasAndScaleStride"]);
    StructFromApiDump<VkDeviceOrHostAddressConstKHR>(ctx, value["displacementVectorBuffer"]);
    ctx.UInt64Value(value["displacementVectorStride"]);
    StructFromApiDump<VkDeviceOrHostAddressConstKHR>(ctx, value["displacedMicromapPrimitiveFlags"]);
    ctx.UInt64Value(value["displacedMicromapPrimitiveFlagsStride"]);
    ctx.EnumValue(value["indexType"], EnumFromString_VkIndexType);
    StructFromApiDump<VkDeviceOrHostAddressConstKHR>(ctx, value["indexBuffer"]);
    ctx.UInt64Value(value["indexStride"]);
    ctx.UInt32Value(value["baseTriangle"]);
    ctx.UInt32Value(value["usageCountsCount"]);
    StructArrayFromApiDump<VkMicromapUsageEXT>(ctx, value["pUsageCounts"], ctx.Length(value["usageCountsCount"]));
    StructArrayFromApiDump<VkMicromapUsageEXT>(ctx, value["ppUsageCounts"], (ctx.Length(value["usageCountsCount"]),1));
    ctx.VulkanHandleValue(value["micromap"], VK_OBJECT_TYPE_MICROMAP_EXT);
}

template <> void StructFromApiDump<VkPhysicalDeviceClusterCullingShaderFeaturesHUAWEI>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["clustercullingShader"]);
    ctx.UInt32Value(value["multiviewClusterCullingShader"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceClusterCullingShaderPropertiesHUAWEI>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Array(value["maxWorkGroupCount"], 3);
    ctx.UInt32Array(value["maxWorkGroupSize"], 3);
    ctx.UInt32Value(value["maxOutputClusterCount"]);
    ctx.UInt64Value(value["indirectBufferOffsetAlignment"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceClusterCullingShaderVrsFeaturesHUAWEI>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["clusterShadingRate"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceBorderColorSwizzleFeaturesEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["borderColorSwizzle"]);
    ctx.UInt32Value(value["borderColorSwizzleFromImage"]);
}

template <> void StructFromApiDump<VkSamplerBorderColorComponentMappingCreateInfoEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    StructFromApiDump<VkComponentMapping>(ctx, value["components"]);
    ctx.UInt32Value(value["srgb"]);
}

template <> void StructFromApiDump<VkPhysicalDevicePageableDeviceLocalMemoryFeaturesEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["pageableDeviceLocalMemory"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceShaderCorePropertiesARM>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["pixelRate"]);
    ctx.UInt32Value(value["texelRate"]);
    ctx.UInt32Value(value["fmaRate"]);
}

template <> void StructFromApiDump<VkDeviceQueueShaderCoreControlCreateInfoARM>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["shaderCoreCount"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceSchedulingControlsFeaturesARM>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["schedulingControls"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceSchedulingControlsPropertiesARM>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.Flags64Value(value["schedulingControlsFlags"], EnumFromString_VkPhysicalDeviceSchedulingControlsFlagBitsARM);
}

template <> void StructFromApiDump<VkDispatchParametersARM>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["workGroupBatchSize"]);
    ctx.UInt32Value(value["maxQueuedWorkGroupBatches"]);
    ctx.UInt32Value(value["maxWarpsPerShaderCore"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceSchedulingControlsDispatchParametersPropertiesARM>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["schedulingControlsMaxWarpsCount"]);
    ctx.UInt32Value(value["schedulingControlsMaxQueuedBatchesCount"]);
    ctx.UInt32Value(value["schedulingControlsMaxWorkGroupBatchSize"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceImageSlicedViewOf3DFeaturesEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["imageSlicedViewOf3D"]);
}

template <> void StructFromApiDump<VkImageViewSlicedCreateInfoEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["sliceOffset"]);
    ctx.UInt32Value(value["sliceCount"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceDescriptorSetHostMappingFeaturesVALVE>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["descriptorSetHostMapping"]);
}

template <> void StructFromApiDump<VkDescriptorSetBindingReferenceVALVE>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.VulkanHandleValue(value["descriptorSetLayout"], VK_OBJECT_TYPE_DESCRIPTOR_SET_LAYOUT);
    ctx.UInt32Value(value["binding"]);
}

template <> void StructFromApiDump<VkDescriptorSetLayoutHostMappingInfoVALVE>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.SizeTValue(value["descriptorOffset"]);
    ctx.UInt32Value(value["descriptorSize"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceNonSeamlessCubeMapFeaturesEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["nonSeamlessCubeMap"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceRenderPassStripedFeaturesARM>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["renderPassStriped"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceRenderPassStripedPropertiesARM>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    StructFromApiDump<VkExtent2D>(ctx, value["renderPassStripeGranularity"]);
    ctx.UInt32Value(value["maxRenderPassStripes"]);
}

template <> void StructFromApiDump<VkRenderPassStripeInfoARM>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    StructFromApiDump<VkRect2D>(ctx, value["stripeArea"]);
}

template <> void StructFromApiDump<VkRenderPassStripeBeginInfoARM>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["stripeInfoCount"]);
    StructArrayFromApiDump<VkRenderPassStripeInfoARM>(ctx, value["pStripeInfos"], ctx.Length(value["stripeInfoCount"]));
}

template <> void StructFromApiDump<VkRenderPassStripeSubmitInfoARM>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["stripeSemaphoreInfoCount"]);
    StructArrayFromApiDump<VkSemaphoreSubmitInfo>(ctx, value["pStripeSemaphoreInfos"], ctx.Length(value["stripeSemaphoreInfoCount"]));
}

template <> void StructFromApiDump<VkPhysicalDeviceFragmentDensityMapOffsetFeaturesEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["fragmentDensityMapOffset"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceFragmentDensityMapOffsetPropertiesEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    StructFromApiDump<VkExtent2D>(ctx, value["fragmentDensityOffsetGranularity"]);
}

template <> void StructFromApiDump<VkRenderPassFragmentDensityMapOffsetEndInfoEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["fragmentDensityOffsetCount"]);
    StructArrayFromApiDump<VkOffset2D>(ctx, value["pFragmentDensityOffsets"], ctx.Length(value["fragmentDensityOffsetCount"]));
}

template <> void StructFromApiDump<VkPhysicalDeviceDeviceGeneratedCommandsComputeFeaturesNV>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["deviceGeneratedCompute"]);
    ctx.UInt32Value(value["deviceGeneratedComputePipelines"]);
    ctx.UInt32Value(value["deviceGeneratedComputeCaptureReplay"]);
}

template <> void StructFromApiDump<VkComputePipelineIndirectBufferInfoNV>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt64Value(value["deviceAddress"]);
    ctx.UInt64Value(value["size"]);
    ctx.UInt64Value(value["pipelineDeviceAddressCaptureReplay"]);
}

template <> void StructFromApiDump<VkPipelineIndirectDeviceAddressInfoNV>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.EnumValue(value["pipelineBindPoint"], EnumFromString_VkPipelineBindPoint);
    ctx.VulkanHandleValue(value["pipeline"], VK_OBJECT_TYPE_PIPELINE);
}

template <> void StructFromApiDump<VkBindPipelineIndirectCommandNV>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.UInt64Value(value["pipelineAddress"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceRayTracingLinearSweptSpheresFeaturesNV>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["spheres"]);
    ctx.UInt32Value(value["linearSweptSpheres"]);
}

template <> void StructFromApiDump<VkAccelerationStructureGeometryLinearSweptSpheresDataNV>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.EnumValue(value["vertexFormat"], EnumFromString_VkFormat);
    StructFromApiDump<VkDeviceOrHostAddressConstKHR>(ctx, value["vertexData"]);
    ctx.UInt64Value(value["vertexStride"]);
    ctx.EnumValue(value["radiusFormat"], EnumFromString_VkFormat);
    StructFromApiDump<VkDeviceOrHostAddressConstKHR>(ctx, value["radiusData"]);
    ctx.UInt64Value(value["radiusStride"]);
    ctx.EnumValue(value["indexType"], EnumFromString_VkIndexType);
    StructFromApiDump<VkDeviceOrHostAddressConstKHR>(ctx, value["indexData"]);
    ctx.UInt64Value(value["indexStride"]);
    ctx.EnumValue(value["indexingMode"], EnumFromString_VkRayTracingLssIndexingModeNV);
    ctx.EnumValue(value["endCapsMode"], EnumFromString_VkRayTracingLssPrimitiveEndCapsModeNV);
}

template <> void StructFromApiDump<VkAccelerationStructureGeometrySpheresDataNV>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.EnumValue(value["vertexFormat"], EnumFromString_VkFormat);
    StructFromApiDump<VkDeviceOrHostAddressConstKHR>(ctx, value["vertexData"]);
    ctx.UInt64Value(value["vertexStride"]);
    ctx.EnumValue(value["radiusFormat"], EnumFromString_VkFormat);
    StructFromApiDump<VkDeviceOrHostAddressConstKHR>(ctx, value["radiusData"]);
    ctx.UInt64Value(value["radiusStride"]);
    ctx.EnumValue(value["indexType"], EnumFromString_VkIndexType);
    StructFromApiDump<VkDeviceOrHostAddressConstKHR>(ctx, value["indexData"]);
    ctx.UInt64Value(value["indexStride"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceLinearColorAttachmentFeaturesNV>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["linearColorAttachment"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceImageCompressionControlSwapchainFeaturesEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["imageCompressionControlSwapchain"]);
}

template <> void StructFromApiDump<VkImageViewSampleWeightCreateInfoQCOM>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    StructFromApiDump<VkOffset2D>(ctx, value["filterCenter"]);
    StructFromApiDump<VkExtent2D>(ctx, value["filterSize"]);
    ctx.UInt32Value(value["numPhases"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceImageProcessingFeaturesQCOM>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["textureSampleWeighted"]);
    ctx.UInt32Value(value["textureBoxFilter"]);
    ctx.UInt32Value(value["textureBlockMatch"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceImageProcessingPropertiesQCOM>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["maxWeightFilterPhases"]);
    StructFromApiDump<VkExtent2D>(ctx, value["maxWeightFilterDimension"]);
    StructFromApiDump<VkExtent2D>(ctx, value["maxBlockMatchRegion"]);
    StructFromApiDump<VkExtent2D>(ctx, value["maxBoxFilterBlockSize"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceNestedCommandBufferFeaturesEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["nestedCommandBuffer"]);
    ctx.UInt32Value(value["nestedCommandBufferRendering"]);
    ctx.UInt32Value(value["nestedCommandBufferSimultaneousUse"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceNestedCommandBufferPropertiesEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["maxCommandBufferNestingLevel"]);
}

template <> void StructFromApiDump<VkExternalMemoryAcquireUnmodifiedEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["acquireUnmodifiedMemory"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceExtendedDynamicState3FeaturesEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["extendedDynamicState3TessellationDomainOrigin"]);
    ctx.UInt32Value(value["extendedDynamicState3DepthClampEnable"]);
    ctx.UInt32Value(value["extendedDynamicState3PolygonMode"]);
    ctx.UInt32Value(value["extendedDynamicState3RasterizationSamples"]);
    ctx.UInt32Value(value["extendedDynamicState3SampleMask"]);
    ctx.UInt32Value(value["extendedDynamicState3AlphaToCoverageEnable"]);
    ctx.UInt32Value(value["extendedDynamicState3AlphaToOneEnable"]);
    ctx.UInt32Value(value["extendedDynamicState3LogicOpEnable"]);
    ctx.UInt32Value(value["extendedDynamicState3ColorBlendEnable"]);
    ctx.UInt32Value(value["extendedDynamicState3ColorBlendEquation"]);
    ctx.UInt32Value(value["extendedDynamicState3ColorWriteMask"]);
    ctx.UInt32Value(value["extendedDynamicState3RasterizationStream"]);
    ctx.UInt32Value(value["extendedDynamicState3ConservativeRasterizationMode"]);
    ctx.UInt32Value(value["extendedDynamicState3ExtraPrimitiveOverestimationSize"]);
    ctx.UInt32Value(value["extendedDynamicState3DepthClipEnable"]);
    ctx.UInt32Value(value["extendedDynamicState3SampleLocationsEnable"]);
    ctx.UInt32Value(value["extendedDynamicState3ColorBlendAdvanced"]);
    ctx.UInt32Value(value["extendedDynamicState3ProvokingVertexMode"]);
    ctx.UInt32Value(value["extendedDynamicState3LineRasterizationMode"]);
    ctx.UInt32Value(value["extendedDynamicState3LineStippleEnable"]);
    ctx.UInt32Value(value["extendedDynamicState3DepthClipNegativeOneToOne"]);
    ctx.UInt32Value(value["extendedDynamicState3ViewportWScalingEnable"]);
    ctx.UInt32Value(value["extendedDynamicState3ViewportSwizzle"]);
    ctx.UInt32Value(value["extendedDynamicState3CoverageToColorEnable"]);
    ctx.UInt32Value(value["extendedDynamicState3CoverageToColorLocation"]);
    ctx.UInt32Value(value["extendedDynamicState3CoverageModulationMode"]);
    ctx.UInt32Value(value["extendedDynamicState3CoverageModulationTableEnable"]);
    ctx.UInt32Value(value["extendedDynamicState3CoverageModulationTable"]);
    ctx.UInt32Value(value["extendedDynamicState3CoverageReductionMode"]);
    ctx.UInt32Value(value["extendedDynamicState3RepresentativeFragmentTestEnable"]);
    ctx.UInt32Value(value["extendedDynamicState3ShadingRateImageEnable"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceExtendedDynamicState3PropertiesEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["dynamicPrimitiveTopologyUnrestricted"]);
}

template <> void StructFromApiDump<VkColorBlendEquationEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["srcColorBlendFactor"], EnumFromString_VkBlendFactor);
    ctx.EnumValue(value["dstColorBlendFactor"], EnumFromString_VkBlendFactor);
    ctx.EnumValue(value["colorBlendOp"], EnumFromString_VkBlendOp);
    ctx.EnumValue(value["srcAlphaBlendFactor"], EnumFromString_VkBlendFactor);
    ctx.EnumValue(value["dstAlphaBlendFactor"], EnumFromString_VkBlendFactor);
    ctx.EnumValue(value["alphaBlendOp"], EnumFromString_VkBlendOp);
}

template <> void StructFromApiDump<VkColorBlendAdvancedEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["advancedBlendOp"], EnumFromString_VkBlendOp);
    ctx.UInt32Value(value["srcPremultiplied"]);
    ctx.UInt32Value(value["dstPremultiplied"]);
    ctx.EnumValue(value["blendOverlap"], EnumFromString_VkBlendOverlapEXT);
    ctx.UInt32Value(value["clampResults"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceSubpassMergeFeedbackFeaturesEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["subpassMergeFeedback"]);
}

template <> void StructFromApiDump<VkRenderPassCreationControlEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["disallowMerging"]);
}

template <> void StructFromApiDump<VkRenderPassCreationFeedbackInfoEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.UInt32Value(value["postMergeSubpassCount"]);
}

template <> void StructFromApiDump<VkRenderPassCreationFeedbackCreateInfoEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    StructPtrFromApiDump<VkRenderPassCreationFeedbackInfoEXT>(ctx, value["pRenderPassFeedback"]);
}

template <> void StructFromApiDump<VkRenderPassSubpassFeedbackInfoEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["subpassMergeStatus"], EnumFromString_VkSubpassMergeStatusEXT);
    ctx.StringValue(value["description"]);
    ctx.UInt32Value(value["postMergeIndex"]);
}

template <> void StructFromApiDump<VkRenderPassSubpassFeedbackCreateInfoEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    StructPtrFromApiDump<VkRenderPassSubpassFeedbackInfoEXT>(ctx, value["pSubpassFeedback"]);
}

template <> void StructFromApiDump<VkDirectDriverLoadingInfoLUNARG>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.FlagsValue(value["flags"]);
    ctx.FunctionPtrValue(value["pfnGetInstanceProcAddr"]);
}

template <> void StructFromApiDump<VkDirectDriverLoadingListLUNARG>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.EnumValue(value["mode"], EnumFromString_VkDirectDriverLoadingModeLUNARG);
    ctx.UInt32Value(value["driverCount"]);
    StructArrayFromApiDump<VkDirectDriverLoadingInfoLUNARG>(ctx, value["pDrivers"], ctx.Length(value["driverCount"]));
}

template <> void StructFromApiDump<VkTensorDescriptionARM>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.EnumValue(value["tiling"], EnumFromString_VkTensorTilingARM);
    ctx.EnumValue(value["format"], EnumFromString_VkFormat);
    ctx.UInt32Value(value["dimensionCount"]);
    ctx.Int64Array(value["pDimensions"], ctx.Length(value["dimensionCount"]));
    ctx.Int64Array(value["pStrides"], ctx.Length(value["dimensionCount"]));
    ctx.Flags64Value(value["usage"], EnumFromString_VkTensorUsageFlagBitsARM);
}

template <> void StructFromApiDump<VkTensorCreateInfoARM>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.Flags64Value(value["flags"], EnumFromString_VkTensorCreateFlagBitsARM);
    StructPtrFromApiDump<VkTensorDescriptionARM>(ctx, value["pDescription"]);
    ctx.EnumValue(value["sharingMode"], EnumFromString_VkSharingMode);
    ctx.UInt32Value(value["queueFamilyIndexCount"]);
    ctx.UInt32Array(value["pQueueFamilyIndices"], ctx.Length(value["queueFamilyIndexCount"]));
}

template <> void StructFromApiDump<VkTensorViewCreateInfoARM>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.Flags64Value(value["flags"], EnumFromString_VkTensorViewCreateFlagBitsARM);
    ctx.VulkanHandleValue(value["tensor"], VK_OBJECT_TYPE_TENSOR_ARM);
    ctx.EnumValue(value["format"], EnumFromString_VkFormat);
}

template <> void StructFromApiDump<VkTensorMemoryRequirementsInfoARM>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.VulkanHandleValue(value["tensor"], VK_OBJECT_TYPE_TENSOR_ARM);
}

template <> void StructFromApiDump<VkBindTensorMemoryInfoARM>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.VulkanHandleValue(value["tensor"], VK_OBJECT_TYPE_TENSOR_ARM);
    ctx.VulkanHandleValue(value["memory"], VK_OBJECT_TYPE_DEVICE_MEMORY);
    ctx.UInt64Value(value["memoryOffset"]);
}

template <> void StructFromApiDump<VkWriteDescriptorSetTensorARM>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["tensorViewCount"]);
    ctx.VulkanHandleArray(value["pTensorViews"], VK_OBJECT_TYPE_TENSOR_VIEW_ARM, ctx.Length(value["tensorViewCount"]));
}

template <> void StructFromApiDump<VkTensorFormatPropertiesARM>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.Flags64Value(value["optimalTilingTensorFeatures"], EnumFromString_VkFormatFeatureFlagBits2);
    ctx.Flags64Value(value["linearTilingTensorFeatures"], EnumFromString_VkFormatFeatureFlagBits2);
}

template <> void StructFromApiDump<VkPhysicalDeviceTensorPropertiesARM>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["maxTensorDimensionCount"]);
    ctx.UInt64Value(value["maxTensorElements"]);
    ctx.UInt64Value(value["maxPerDimensionTensorElements"]);
    ctx.Int64Value(value["maxTensorStride"]);
    ctx.UInt64Value(value["maxTensorSize"]);
    ctx.UInt32Value(value["maxTensorShaderAccessArrayLength"]);
    ctx.UInt32Value(value["maxTensorShaderAccessSize"]);
    ctx.UInt32Value(value["maxDescriptorSetStorageTensors"]);
    ctx.UInt32Value(value["maxPerStageDescriptorSetStorageTensors"]);
    ctx.UInt32Value(value["maxDescriptorSetUpdateAfterBindStorageTensors"]);
    ctx.UInt32Value(value["maxPerStageDescriptorUpdateAfterBindStorageTensors"]);
    ctx.UInt32Value(value["shaderStorageTensorArrayNonUniformIndexingNative"]);
    ctx.FlagsValue(value["shaderTensorSupportedStages"], EnumFromString_VkShaderStageFlagBits);
}

template <> void StructFromApiDump<VkTensorMemoryBarrierARM>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.Flags64Value(value["srcStageMask"], EnumFromString_VkPipelineStageFlagBits2);
    ctx.Flags64Value(value["srcAccessMask"], EnumFromString_VkAccessFlagBits2);
    ctx.Flags64Value(value["dstStageMask"], EnumFromString_VkPipelineStageFlagBits2);
    ctx.Flags64Value(value["dstAccessMask"], EnumFromString_VkAccessFlagBits2);
    ctx.UInt32Value(value["srcQueueFamilyIndex"]);
    ctx.UInt32Value(value["dstQueueFamilyIndex"]);
    ctx.VulkanHandleValue(value["tensor"], VK_OBJECT_TYPE_TENSOR_ARM);
}

template <> void StructFromApiDump<VkTensorDependencyInfoARM>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["tensorMemoryBarrierCount"]);
    StructArrayFromApiDump<VkTensorMemoryBarrierARM>(ctx, value["pTensorMemoryBarriers"], ctx.Length(value["tensorMemoryBarrierCount"]));
}

template <> void StructFromApiDump<VkPhysicalDeviceTensorFeaturesARM>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["tensorNonPacked"]);
    ctx.UInt32Value(value["shaderTensorAccess"]);
    ctx.UInt32Value(value["shaderStorageTensorArrayDynamicIndexing"]);
    ctx.UInt32Value(value["shaderStorageTensorArrayNonUniformIndexing"]);
    ctx.UInt32Value(value["descriptorBindingStorageTensorUpdateAfterBind"]);
    ctx.UInt32Value(value["tensors"]);
}

template <> void StructFromApiDump<VkDeviceTensorMemoryRequirementsARM>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    StructPtrFromApiDump<VkTensorCreateInfoARM>(ctx, value["pCreateInfo"]);
}

template <> void StructFromApiDump<VkTensorCopyARM>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["dimensionCount"]);
    ctx.UInt64Array(value["pSrcOffset"], ctx.Length(value["dimensionCount"]));
    ctx.UInt64Array(value["pDstOffset"], ctx.Length(value["dimensionCount"]));
    ctx.UInt64Array(value["pExtent"], ctx.Length(value["dimensionCount"]));
}

template <> void StructFromApiDump<VkCopyTensorInfoARM>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.VulkanHandleValue(value["srcTensor"], VK_OBJECT_TYPE_TENSOR_ARM);
    ctx.VulkanHandleValue(value["dstTensor"], VK_OBJECT_TYPE_TENSOR_ARM);
    ctx.UInt32Value(value["regionCount"]);
    StructArrayFromApiDump<VkTensorCopyARM>(ctx, value["pRegions"], ctx.Length(value["regionCount"]));
}

template <> void StructFromApiDump<VkMemoryDedicatedAllocateInfoTensorARM>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.VulkanHandleValue(value["tensor"], VK_OBJECT_TYPE_TENSOR_ARM);
}

template <> void StructFromApiDump<VkPhysicalDeviceExternalTensorInfoARM>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.Flags64Value(value["flags"], EnumFromString_VkTensorCreateFlagBitsARM);
    StructPtrFromApiDump<VkTensorDescriptionARM>(ctx, value["pDescription"]);
    ctx.EnumValue(value["handleType"], EnumFromString_VkExternalMemoryHandleTypeFlagBits);
}

template <> void StructFromApiDump<VkExternalTensorPropertiesARM>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    StructFromApiDump<VkExternalMemoryProperties>(ctx, value["externalMemoryProperties"]);
}

template <> void StructFromApiDump<VkExternalMemoryTensorCreateInfoARM>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.FlagsValue(value["handleTypes"], EnumFromString_VkExternalMemoryHandleTypeFlagBits);
}

template <> void StructFromApiDump<VkPhysicalDeviceDescriptorBufferTensorFeaturesARM>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["descriptorBufferTensorDescriptors"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceDescriptorBufferTensorPropertiesARM>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.SizeTValue(value["tensorCaptureReplayDescriptorDataSize"]);
    ctx.SizeTValue(value["tensorViewCaptureReplayDescriptorDataSize"]);
    ctx.SizeTValue(value["tensorDescriptorSize"]);
}

template <> void StructFromApiDump<VkDescriptorGetTensorInfoARM>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.VulkanHandleValue(value["tensorView"], VK_OBJECT_TYPE_TENSOR_VIEW_ARM);
}

template <> void StructFromApiDump<VkTensorCaptureDescriptorDataInfoARM>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.VulkanHandleValue(value["tensor"], VK_OBJECT_TYPE_TENSOR_ARM);
}

template <> void StructFromApiDump<VkTensorViewCaptureDescriptorDataInfoARM>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.VulkanHandleValue(value["tensorView"], VK_OBJECT_TYPE_TENSOR_VIEW_ARM);
}

template <> void StructFromApiDump<VkFrameBoundaryTensorsARM>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["tensorCount"]);
    ctx.VulkanHandleArray(value["pTensors"], VK_OBJECT_TYPE_TENSOR_ARM, ctx.Length(value["tensorCount"]));
}

template <> void StructFromApiDump<VkPhysicalDeviceShaderModuleIdentifierFeaturesEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["shaderModuleIdentifier"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceShaderModuleIdentifierPropertiesEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt8Array(value["shaderModuleIdentifierAlgorithmUUID"]);
}

template <> void StructFromApiDump<VkPipelineShaderStageModuleIdentifierCreateInfoEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["identifierSize"]);
    ctx.UInt8Array(value["pIdentifier"], ctx.Length(value["identifierSize"]));
}

template <> void StructFromApiDump<VkShaderModuleIdentifierEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["identifierSize"]);
    ctx.UInt8Array(value["identifier"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceOpticalFlowFeaturesNV>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["opticalFlow"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceOpticalFlowPropertiesNV>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.FlagsValue(value["supportedOutputGridSizes"], EnumFromString_VkOpticalFlowGridSizeFlagBitsNV);
    ctx.FlagsValue(value["supportedHintGridSizes"], EnumFromString_VkOpticalFlowGridSizeFlagBitsNV);
    ctx.UInt32Value(value["hintSupported"]);
    ctx.UInt32Value(value["costSupported"]);
    ctx.UInt32Value(value["bidirectionalFlowSupported"]);
    ctx.UInt32Value(value["globalFlowSupported"]);
    ctx.UInt32Value(value["minWidth"]);
    ctx.UInt32Value(value["minHeight"]);
    ctx.UInt32Value(value["maxWidth"]);
    ctx.UInt32Value(value["maxHeight"]);
    ctx.UInt32Value(value["maxNumRegionsOfInterest"]);
}

template <> void StructFromApiDump<VkOpticalFlowImageFormatInfoNV>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.FlagsValue(value["usage"], EnumFromString_VkOpticalFlowUsageFlagBitsNV);
}

template <> void StructFromApiDump<VkOpticalFlowImageFormatPropertiesNV>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.EnumValue(value["format"], EnumFromString_VkFormat);
}

template <> void StructFromApiDump<VkOpticalFlowSessionCreateInfoNV>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["width"]);
    ctx.UInt32Value(value["height"]);
    ctx.EnumValue(value["imageFormat"], EnumFromString_VkFormat);
    ctx.EnumValue(value["flowVectorFormat"], EnumFromString_VkFormat);
    ctx.EnumValue(value["costFormat"], EnumFromString_VkFormat);
    ctx.FlagsValue(value["outputGridSize"], EnumFromString_VkOpticalFlowGridSizeFlagBitsNV);
    ctx.FlagsValue(value["hintGridSize"], EnumFromString_VkOpticalFlowGridSizeFlagBitsNV);
    ctx.EnumValue(value["performanceLevel"], EnumFromString_VkOpticalFlowPerformanceLevelNV);
    ctx.FlagsValue(value["flags"], EnumFromString_VkOpticalFlowSessionCreateFlagBitsNV);
}

template <> void StructFromApiDump<VkOpticalFlowSessionCreatePrivateDataInfoNV>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["id"]);
    ctx.UInt32Value(value["size"]);
    ctx.VoidPtrValue(value["pPrivateData"]);
}

template <> void StructFromApiDump<VkOpticalFlowExecuteInfoNV>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.FlagsValue(value["flags"], EnumFromString_VkOpticalFlowExecuteFlagBitsNV);
    ctx.UInt32Value(value["regionCount"]);
    StructArrayFromApiDump<VkRect2D>(ctx, value["pRegions"], ctx.Length(value["regionCount"]));
}

template <> void StructFromApiDump<VkPhysicalDeviceLegacyDitheringFeaturesEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["legacyDithering"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceExternalFormatResolveFeaturesANDROID>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["externalFormatResolve"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceExternalFormatResolvePropertiesANDROID>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["nullColorAttachmentWithExternalFormatResolve"]);
    ctx.EnumValue(value["externalFormatResolveChromaOffsetX"], EnumFromString_VkChromaLocation);
    ctx.EnumValue(value["externalFormatResolveChromaOffsetY"], EnumFromString_VkChromaLocation);
}

template <> void StructFromApiDump<VkAndroidHardwareBufferFormatResolvePropertiesANDROID>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.EnumValue(value["colorAttachmentFormat"], EnumFromString_VkFormat);
}

template <> void StructFromApiDump<VkPhysicalDeviceAntiLagFeaturesAMD>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["antiLag"]);
}

template <> void StructFromApiDump<VkAntiLagPresentationInfoAMD>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.EnumValue(value["stage"], EnumFromString_VkAntiLagStageAMD);
    ctx.UInt64Value(value["frameIndex"]);
}

template <> void StructFromApiDump<VkAntiLagDataAMD>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.EnumValue(value["mode"], EnumFromString_VkAntiLagModeAMD);
    ctx.UInt32Value(value["maxFPS"]);
    StructPtrFromApiDump<VkAntiLagPresentationInfoAMD>(ctx, value["pPresentationInfo"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceShaderObjectFeaturesEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["shaderObject"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceShaderObjectPropertiesEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt8Array(value["shaderBinaryUUID"]);
    ctx.UInt32Value(value["shaderBinaryVersion"]);
}

template <> void StructFromApiDump<VkShaderCreateInfoEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.FlagsValue(value["flags"], EnumFromString_VkShaderCreateFlagBitsEXT);
    ctx.EnumValue(value["stage"], EnumFromString_VkShaderStageFlagBits);
    ctx.FlagsValue(value["nextStage"], EnumFromString_VkShaderStageFlagBits);
    ctx.EnumValue(value["codeType"], EnumFromString_VkShaderCodeTypeEXT);
    ctx.SizeTValue(value["codeSize"]);
    ctx.UInt8Array(value["pCode"], ctx.Length(value["codeSize"]));
    ctx.StringValue(value["pName"]);
    ctx.UInt32Value(value["setLayoutCount"]);
    ctx.VulkanHandleArray(value["pSetLayouts"], VK_OBJECT_TYPE_DESCRIPTOR_SET_LAYOUT, ctx.Length(value["setLayoutCount"]));
    ctx.UInt32Value(value["pushConstantRangeCount"]);
    StructArrayFromApiDump<VkPushConstantRange>(ctx, value["pPushConstantRanges"], ctx.Length(value["pushConstantRangeCount"]));
    StructPtrFromApiDump<VkSpecializationInfo>(ctx, value["pSpecializationInfo"]);
}

template <> void StructFromApiDump<VkDepthClampRangeEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.FloatValue(value["minDepthClamp"]);
    ctx.FloatValue(value["maxDepthClamp"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceTilePropertiesFeaturesQCOM>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["tileProperties"]);
}

template <> void StructFromApiDump<VkTilePropertiesQCOM>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    StructFromApiDump<VkExtent3D>(ctx, value["tileSize"]);
    StructFromApiDump<VkExtent2D>(ctx, value["apronSize"]);
    StructFromApiDump<VkOffset2D>(ctx, value["origin"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceAmigoProfilingFeaturesSEC>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["amigoProfiling"]);
}

template <> void StructFromApiDump<VkAmigoProfilingSubmitInfoSEC>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt64Value(value["firstDrawTimestamp"]);
    ctx.UInt64Value(value["swapBufferTimestamp"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceMultiviewPerViewViewportsFeaturesQCOM>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["multiviewPerViewViewports"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceRayTracingInvocationReorderPropertiesNV>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.EnumValue(value["rayTracingInvocationReorderReorderingHint"], EnumFromString_VkRayTracingInvocationReorderModeEXT);
}

template <> void StructFromApiDump<VkPhysicalDeviceRayTracingInvocationReorderFeaturesNV>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["rayTracingInvocationReorder"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceCooperativeVectorPropertiesNV>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.FlagsValue(value["cooperativeVectorSupportedStages"], EnumFromString_VkShaderStageFlagBits);
    ctx.UInt32Value(value["cooperativeVectorTrainingFloat16Accumulation"]);
    ctx.UInt32Value(value["cooperativeVectorTrainingFloat32Accumulation"]);
    ctx.UInt32Value(value["maxCooperativeVectorComponents"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceCooperativeVectorFeaturesNV>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["cooperativeVector"]);
    ctx.UInt32Value(value["cooperativeVectorTraining"]);
}

template <> void StructFromApiDump<VkCooperativeVectorPropertiesNV>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.EnumValue(value["inputType"], EnumFromString_VkComponentTypeKHR);
    ctx.EnumValue(value["inputInterpretation"], EnumFromString_VkComponentTypeKHR);
    ctx.EnumValue(value["matrixInterpretation"], EnumFromString_VkComponentTypeKHR);
    ctx.EnumValue(value["biasInterpretation"], EnumFromString_VkComponentTypeKHR);
    ctx.EnumValue(value["resultType"], EnumFromString_VkComponentTypeKHR);
    ctx.UInt32Value(value["transpose"]);
}

template <> void StructFromApiDump<VkConvertCooperativeVectorMatrixInfoNV>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.SizeTValue(value["srcSize"]);
    StructFromApiDump<VkDeviceOrHostAddressConstKHR>(ctx, value["srcData"]);
    ctx.SizeTPtr(value["pDstSize"]);
    StructFromApiDump<VkDeviceOrHostAddressKHR>(ctx, value["dstData"]);
    ctx.EnumValue(value["srcComponentType"], EnumFromString_VkComponentTypeKHR);
    ctx.EnumValue(value["dstComponentType"], EnumFromString_VkComponentTypeKHR);
    ctx.UInt32Value(value["numRows"]);
    ctx.UInt32Value(value["numColumns"]);
    ctx.EnumValue(value["srcLayout"], EnumFromString_VkCooperativeVectorMatrixLayoutNV);
    ctx.SizeTValue(value["srcStride"]);
    ctx.EnumValue(value["dstLayout"], EnumFromString_VkCooperativeVectorMatrixLayoutNV);
    ctx.SizeTValue(value["dstStride"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceExtendedSparseAddressSpaceFeaturesNV>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["extendedSparseAddressSpace"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceExtendedSparseAddressSpacePropertiesNV>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt64Value(value["extendedSparseAddressSpaceSize"]);
    ctx.FlagsValue(value["extendedSparseImageUsageFlags"], EnumFromString_VkImageUsageFlagBits);
    ctx.FlagsValue(value["extendedSparseBufferUsageFlags"], EnumFromString_VkBufferUsageFlagBits);
}

template <> void StructFromApiDump<VkPhysicalDeviceLegacyVertexAttributesFeaturesEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["legacyVertexAttributes"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceLegacyVertexAttributesPropertiesEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["nativeUnalignedPerformance"]);
}

template <> void StructFromApiDump<VkLayerSettingsCreateInfoEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["settingCount"]);
    StructArrayFromApiDump<VkLayerSettingEXT>(ctx, value["pSettings"], ctx.Length(value["settingCount"]));
}

template <> void StructFromApiDump<VkPhysicalDeviceShaderCoreBuiltinsFeaturesARM>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["shaderCoreBuiltins"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceShaderCoreBuiltinsPropertiesARM>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt64Value(value["shaderCoreMask"]);
    ctx.UInt32Value(value["shaderCoreCount"]);
    ctx.UInt32Value(value["shaderWarpsPerCore"]);
}

template <> void StructFromApiDump<VkPhysicalDevicePipelineLibraryGroupHandlesFeaturesEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["pipelineLibraryGroupHandles"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceDynamicRenderingUnusedAttachmentsFeaturesEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["dynamicRenderingUnusedAttachments"]);
}

template <> void StructFromApiDump<VkLatencySleepModeInfoNV>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["lowLatencyMode"]);
    ctx.UInt32Value(value["lowLatencyBoost"]);
    ctx.UInt32Value(value["minimumIntervalUs"]);
}

template <> void StructFromApiDump<VkLatencySleepInfoNV>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.VulkanHandleValue(value["signalSemaphore"], VK_OBJECT_TYPE_SEMAPHORE);
    ctx.UInt64Value(value["value"]);
}

template <> void StructFromApiDump<VkSetLatencyMarkerInfoNV>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt64Value(value["presentID"]);
    ctx.EnumValue(value["marker"], EnumFromString_VkLatencyMarkerNV);
}

template <> void StructFromApiDump<VkLatencyTimingsFrameReportNV>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt64Value(value["presentID"]);
    ctx.UInt64Value(value["inputSampleTimeUs"]);
    ctx.UInt64Value(value["simStartTimeUs"]);
    ctx.UInt64Value(value["simEndTimeUs"]);
    ctx.UInt64Value(value["renderSubmitStartTimeUs"]);
    ctx.UInt64Value(value["renderSubmitEndTimeUs"]);
    ctx.UInt64Value(value["presentStartTimeUs"]);
    ctx.UInt64Value(value["presentEndTimeUs"]);
    ctx.UInt64Value(value["driverStartTimeUs"]);
    ctx.UInt64Value(value["driverEndTimeUs"]);
    ctx.UInt64Value(value["osRenderQueueStartTimeUs"]);
    ctx.UInt64Value(value["osRenderQueueEndTimeUs"]);
    ctx.UInt64Value(value["gpuRenderStartTimeUs"]);
    ctx.UInt64Value(value["gpuRenderEndTimeUs"]);
}

template <> void StructFromApiDump<VkGetLatencyMarkerInfoNV>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["timingCount"]);
    StructArrayFromApiDump<VkLatencyTimingsFrameReportNV>(ctx, value["pTimings"], ctx.Length(value["timingCount"]));
}

template <> void StructFromApiDump<VkLatencySubmissionPresentIdNV>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt64Value(value["presentID"]);
}

template <> void StructFromApiDump<VkSwapchainLatencyCreateInfoNV>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["latencyModeEnable"]);
}

template <> void StructFromApiDump<VkOutOfBandQueueTypeInfoNV>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.EnumValue(value["queueType"], EnumFromString_VkOutOfBandQueueTypeNV);
}

template <> void StructFromApiDump<VkLatencySurfaceCapabilitiesNV>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["presentModeCount"]);
    ctx.EnumArray(value["pPresentModes"], EnumFromString_VkPresentModeKHR, ctx.Length(value["presentModeCount"]));
}

template <> void StructFromApiDump<VkPhysicalDeviceDataGraphFeaturesARM>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["dataGraph"]);
    ctx.UInt32Value(value["dataGraphUpdateAfterBind"]);
    ctx.UInt32Value(value["dataGraphSpecializationConstants"]);
    ctx.UInt32Value(value["dataGraphDescriptorBuffer"]);
    ctx.UInt32Value(value["dataGraphShaderModule"]);
}

template <> void StructFromApiDump<VkDataGraphPipelineResourceInfoARM>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["descriptorSet"]);
    ctx.UInt32Value(value["binding"]);
    ctx.UInt32Value(value["arrayElement"]);
}

template <> void StructFromApiDump<VkDataGraphPipelineCompilerControlCreateInfoARM>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.StringValue(value["pVendorOptions"]);
}

template <> void StructFromApiDump<VkDataGraphPipelineCreateInfoARM>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.Flags64Value(value["flags"], EnumFromString_VkPipelineCreateFlagBits2);
    ctx.VulkanHandleValue(value["layout"], VK_OBJECT_TYPE_PIPELINE_LAYOUT);
    ctx.UInt32Value(value["resourceInfoCount"]);
    StructArrayFromApiDump<VkDataGraphPipelineResourceInfoARM>(ctx, value["pResourceInfos"], ctx.Length(value["resourceInfoCount"]));
}

template <> void StructFromApiDump<VkDataGraphPipelineShaderModuleCreateInfoARM>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.VulkanHandleValue(value["module"], VK_OBJECT_TYPE_SHADER_MODULE);
    ctx.StringValue(value["pName"]);
    StructPtrFromApiDump<VkSpecializationInfo>(ctx, value["pSpecializationInfo"]);
    ctx.UInt32Value(value["constantCount"]);
    StructArrayFromApiDump<VkDataGraphPipelineConstantARM>(ctx, value["pConstants"], ctx.Length(value["constantCount"]));
}

template <> void StructFromApiDump<VkDataGraphPipelineSessionCreateInfoARM>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.Flags64Value(value["flags"], EnumFromString_VkDataGraphPipelineSessionCreateFlagBitsARM);
    ctx.VulkanHandleValue(value["dataGraphPipeline"], VK_OBJECT_TYPE_PIPELINE);
}

template <> void StructFromApiDump<VkDataGraphPipelineSessionBindPointRequirementsInfoARM>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.VulkanHandleValue(value["session"], VK_OBJECT_TYPE_DATA_GRAPH_PIPELINE_SESSION_ARM);
}

template <> void StructFromApiDump<VkDataGraphPipelineSessionBindPointRequirementARM>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.EnumValue(value["bindPoint"], EnumFromString_VkDataGraphPipelineSessionBindPointARM);
    ctx.EnumValue(value["bindPointType"], EnumFromString_VkDataGraphPipelineSessionBindPointTypeARM);
    ctx.UInt32Value(value["numObjects"]);
}

template <> void StructFromApiDump<VkDataGraphPipelineSessionMemoryRequirementsInfoARM>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.VulkanHandleValue(value["session"], VK_OBJECT_TYPE_DATA_GRAPH_PIPELINE_SESSION_ARM);
    ctx.EnumValue(value["bindPoint"], EnumFromString_VkDataGraphPipelineSessionBindPointARM);
    ctx.UInt32Value(value["objectIndex"]);
}

template <> void StructFromApiDump<VkBindDataGraphPipelineSessionMemoryInfoARM>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.VulkanHandleValue(value["session"], VK_OBJECT_TYPE_DATA_GRAPH_PIPELINE_SESSION_ARM);
    ctx.EnumValue(value["bindPoint"], EnumFromString_VkDataGraphPipelineSessionBindPointARM);
    ctx.UInt32Value(value["objectIndex"]);
    ctx.VulkanHandleValue(value["memory"], VK_OBJECT_TYPE_DEVICE_MEMORY);
    ctx.UInt64Value(value["memoryOffset"]);
}

template <> void StructFromApiDump<VkDataGraphPipelineInfoARM>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.VulkanHandleValue(value["dataGraphPipeline"], VK_OBJECT_TYPE_PIPELINE);
}

template <> void StructFromApiDump<VkDataGraphPipelinePropertyQueryResultARM>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.EnumValue(value["property"], EnumFromString_VkDataGraphPipelinePropertyARM);
    ctx.UInt32Value(value["isText"]);
    ctx.SizeTValue(value["dataSize"]);
    ctx.UInt8Array(value["pData"], ctx.Length(value["dataSize"]));
}

template <> void StructFromApiDump<VkDataGraphPipelineIdentifierCreateInfoARM>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["identifierSize"]);
    ctx.UInt8Array(value["pIdentifier"], ctx.Length(value["identifierSize"]));
}

template <> void StructFromApiDump<VkDataGraphPipelineDispatchInfoARM>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.Flags64Value(value["flags"], EnumFromString_VkDataGraphPipelineDispatchFlagBitsARM);
}

template <> void StructFromApiDump<VkPhysicalDeviceDataGraphProcessingEngineARM>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["type"], EnumFromString_VkPhysicalDeviceDataGraphProcessingEngineTypeARM);
    ctx.UInt32Value(value["isForeign"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceDataGraphOperationSupportARM>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["operationType"], EnumFromString_VkPhysicalDeviceDataGraphOperationTypeARM);
    ctx.StringValue(value["name"]);
    ctx.UInt32Value(value["version"]);
}

template <> void StructFromApiDump<VkQueueFamilyDataGraphPropertiesARM>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    StructFromApiDump<VkPhysicalDeviceDataGraphProcessingEngineARM>(ctx, value["engine"]);
    StructFromApiDump<VkPhysicalDeviceDataGraphOperationSupportARM>(ctx, value["operation"]);
}

template <> void StructFromApiDump<VkDataGraphProcessingEngineCreateInfoARM>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["processingEngineCount"]);
    StructArrayFromApiDump<VkPhysicalDeviceDataGraphProcessingEngineARM>(ctx, value["pProcessingEngines"], ctx.Length(value["processingEngineCount"]));
}

template <> void StructFromApiDump<VkPhysicalDeviceQueueFamilyDataGraphProcessingEngineInfoARM>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["queueFamilyIndex"]);
    ctx.EnumValue(value["engineType"], EnumFromString_VkPhysicalDeviceDataGraphProcessingEngineTypeARM);
}

template <> void StructFromApiDump<VkQueueFamilyDataGraphProcessingEnginePropertiesARM>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.FlagsValue(value["foreignSemaphoreHandleTypes"], EnumFromString_VkExternalSemaphoreHandleTypeFlagBits);
    ctx.FlagsValue(value["foreignMemoryHandleTypes"], EnumFromString_VkExternalMemoryHandleTypeFlagBits);
}

template <> void StructFromApiDump<VkDataGraphPipelineConstantTensorSemiStructuredSparsityInfoARM>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["dimension"]);
    ctx.UInt32Value(value["zeroCount"]);
    ctx.UInt32Value(value["groupSize"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceMultiviewPerViewRenderAreasFeaturesQCOM>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["multiviewPerViewRenderAreas"]);
}

template <> void StructFromApiDump<VkMultiviewPerViewRenderAreasRenderPassBeginInfoQCOM>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["perViewRenderAreaCount"]);
    StructArrayFromApiDump<VkRect2D>(ctx, value["pPerViewRenderAreas"], ctx.Length(value["perViewRenderAreaCount"]));
}

template <> void StructFromApiDump<VkPhysicalDevicePerStageDescriptorSetFeaturesNV>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["perStageDescriptorSet"]);
    ctx.UInt32Value(value["dynamicPipelineLayout"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceImageProcessing2FeaturesQCOM>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["textureBlockMatch2"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceImageProcessing2PropertiesQCOM>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    StructFromApiDump<VkExtent2D>(ctx, value["maxBlockMatchWindow"]);
}

template <> void StructFromApiDump<VkSamplerBlockMatchWindowCreateInfoQCOM>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    StructFromApiDump<VkExtent2D>(ctx, value["windowExtent"]);
    ctx.EnumValue(value["windowCompareMode"], EnumFromString_VkBlockMatchWindowCompareModeQCOM);
}

template <> void StructFromApiDump<VkPhysicalDeviceCubicWeightsFeaturesQCOM>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["selectableCubicWeights"]);
}

template <> void StructFromApiDump<VkSamplerCubicWeightsCreateInfoQCOM>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.EnumValue(value["cubicWeights"], EnumFromString_VkCubicFilterWeightsQCOM);
}

template <> void StructFromApiDump<VkBlitImageCubicWeightsInfoQCOM>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.EnumValue(value["cubicWeights"], EnumFromString_VkCubicFilterWeightsQCOM);
}

template <> void StructFromApiDump<VkPhysicalDeviceYcbcrDegammaFeaturesQCOM>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["ycbcrDegamma"]);
}

template <> void StructFromApiDump<VkSamplerYcbcrConversionYcbcrDegammaCreateInfoQCOM>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["enableYDegamma"]);
    ctx.UInt32Value(value["enableCbCrDegamma"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceCubicClampFeaturesQCOM>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["cubicRangeClamp"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceAttachmentFeedbackLoopDynamicStateFeaturesEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["attachmentFeedbackLoopDynamicState"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceLayeredDriverPropertiesMSFT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.EnumValue(value["underlyingAPI"], EnumFromString_VkLayeredDriverUnderlyingApiMSFT);
}

template <> void StructFromApiDump<VkPhysicalDeviceDescriptorPoolOverallocationFeaturesNV>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["descriptorPoolOverallocation"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceTileMemoryHeapFeaturesQCOM>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["tileMemoryHeap"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceTileMemoryHeapPropertiesQCOM>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["queueSubmitBoundary"]);
    ctx.UInt32Value(value["tileBufferTransfers"]);
}

template <> void StructFromApiDump<VkTileMemoryRequirementsQCOM>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt64Value(value["size"]);
    ctx.UInt64Value(value["alignment"]);
}

template <> void StructFromApiDump<VkTileMemoryBindInfoQCOM>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.VulkanHandleValue(value["memory"], VK_OBJECT_TYPE_DEVICE_MEMORY);
}

template <> void StructFromApiDump<VkTileMemorySizeInfoQCOM>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt64Value(value["size"]);
}

template <> void StructFromApiDump<VkDecompressMemoryRegionEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.UInt64Value(value["srcAddress"]);
    ctx.UInt64Value(value["dstAddress"]);
    ctx.UInt64Value(value["compressedSize"]);
    ctx.UInt64Value(value["decompressedSize"]);
}

template <> void StructFromApiDump<VkDecompressMemoryInfoEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.Flags64Value(value["decompressionMethod"], EnumFromString_VkMemoryDecompressionMethodFlagBitsEXT);
    ctx.UInt32Value(value["regionCount"]);
    StructArrayFromApiDump<VkDecompressMemoryRegionEXT>(ctx, value["pRegions"], ctx.Length(value["regionCount"]));
}

template <> void StructFromApiDump<VkPhysicalDeviceMemoryDecompressionFeaturesEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["memoryDecompression"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceMemoryDecompressionPropertiesEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.Flags64Value(value["decompressionMethods"], EnumFromString_VkMemoryDecompressionMethodFlagBitsEXT);
    ctx.UInt64Value(value["maxDecompressionIndirectCount"]);
}

template <> void StructFromApiDump<VkDisplaySurfaceStereoCreateInfoNV>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.EnumValue(value["stereoType"], EnumFromString_VkDisplaySurfaceStereoTypeNV);
}

template <> void StructFromApiDump<VkDisplayModeStereoPropertiesNV>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["hdmi3DSupported"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceRawAccessChainsFeaturesNV>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["shaderRawAccessChains"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceCommandBufferInheritanceFeaturesNV>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["commandBufferInheritance"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceShaderAtomicFloat16VectorFeaturesNV>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["shaderFloat16VectorAtomics"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceShaderReplicatedCompositesFeaturesEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["shaderReplicatedComposites"]);
}

template <> void StructFromApiDump<VkTensorRollingBackingCreateInfoARM>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Array(value["wraps"]);
}

template <> void StructFromApiDump<VkTensorExplicitTilingFormatPropertiesARM>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.Flags64Value(value["brick16TilingTensorFeatures"], EnumFromString_VkFormatFeatureFlagBits2);
    ctx.Flags64Value(value["brick8TilingTensorFeatures"], EnumFromString_VkFormatFeatureFlagBits2);
    ctx.Flags64Value(value["brick4TilingTensorFeatures"], EnumFromString_VkFormatFeatureFlagBits2);
    ctx.Flags64Value(value["blockUTilingTensorFeatures"], EnumFromString_VkFormatFeatureFlagBits2);
    ctx.Flags64Value(value["blockU64kTilingTensorFeatures"], EnumFromString_VkFormatFeatureFlagBits2);
}

template <> void StructFromApiDump<VkPhysicalDeviceShaderFloat8FeaturesEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["shaderFloat8"]);
    ctx.UInt32Value(value["shaderFloat8CooperativeMatrix"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceRayTracingValidationFeaturesNV>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["rayTracingValidation"]);
}

template <> void StructFromApiDump<VkPhysicalDevicePartitionedAccelerationStructureFeaturesNV>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["partitionedAccelerationStructure"]);
}

template <> void StructFromApiDump<VkPhysicalDevicePartitionedAccelerationStructurePropertiesNV>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["maxPartitionCount"]);
}

template <> void StructFromApiDump<VkPartitionedAccelerationStructureFlagsNV>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["enablePartitionTranslation"]);
}

template <> void StructFromApiDump<VkStridedDeviceAddressNV>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.UInt64Value(value["startAddress"]);
    ctx.UInt64Value(value["strideInBytes"]);
}

template <> void StructFromApiDump<VkBuildPartitionedAccelerationStructureIndirectCommandNV>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["opType"], EnumFromString_VkPartitionedAccelerationStructureOpTypeNV);
    ctx.UInt32Value(value["argCount"]);
    StructFromApiDump<VkStridedDeviceAddressNV>(ctx, value["argData"]);
}

template <> void StructFromApiDump<VkPartitionedAccelerationStructureWriteInstanceDataNV>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    StructFromApiDump<VkTransformMatrixKHR>(ctx, value["transform"]);
    ctx.FloatArray(value["explicitAABB"], 6);
    ctx.UInt32Value(value["instanceID"]);
    ctx.UInt32Value(value["instanceMask"]);
    ctx.UInt32Value(value["instanceContributionToHitGroupIndex"]);
    ctx.FlagsValue(value["instanceFlags"], EnumFromString_VkPartitionedAccelerationStructureInstanceFlagBitsNV);
    ctx.UInt32Value(value["instanceIndex"]);
    ctx.UInt32Value(value["partitionIndex"]);
    ctx.UInt64Value(value["accelerationStructure"]);
}

template <> void StructFromApiDump<VkPartitionedAccelerationStructureUpdateInstanceDataNV>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.UInt32Value(value["instanceIndex"]);
    ctx.UInt32Value(value["instanceContributionToHitGroupIndex"]);
    ctx.UInt64Value(value["accelerationStructure"]);
}

template <> void StructFromApiDump<VkPartitionedAccelerationStructureWritePartitionTranslationDataNV>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.UInt32Value(value["partitionIndex"]);
    ctx.FloatArray(value["partitionTranslation"], 3);
}

template <> void StructFromApiDump<VkWriteDescriptorSetPartitionedAccelerationStructureNV>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["accelerationStructureCount"]);
    ctx.UInt64Array(value["pAccelerationStructures"], ctx.Length(value["accelerationStructureCount"]));
}

template <> void StructFromApiDump<VkPartitionedAccelerationStructureInstancesInputNV>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.FlagsValue(value["flags"], EnumFromString_VkBuildAccelerationStructureFlagBitsKHR);
    ctx.UInt32Value(value["instanceCount"]);
    ctx.UInt32Value(value["maxInstancePerPartitionCount"]);
    ctx.UInt32Value(value["partitionCount"]);
    ctx.UInt32Value(value["maxInstanceInGlobalPartitionCount"]);
}

template <> void StructFromApiDump<VkBuildPartitionedAccelerationStructureInfoNV>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    StructFromApiDump<VkPartitionedAccelerationStructureInstancesInputNV>(ctx, value["input"]);
    ctx.UInt64Value(value["srcAccelerationStructureData"]);
    ctx.UInt64Value(value["dstAccelerationStructureData"]);
    ctx.UInt64Value(value["scratchData"]);
    ctx.UInt64Value(value["srcInfos"]);
    ctx.UInt64Value(value["srcInfosCount"]);
}

template <> void StructFromApiDump<VkAccelerationStructureBuildSizesInfoKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt64Value(value["accelerationStructureSize"]);
    ctx.UInt64Value(value["updateScratchSize"]);
    ctx.UInt64Value(value["buildScratchSize"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceDeviceGeneratedCommandsFeaturesEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["deviceGeneratedCommands"]);
    ctx.UInt32Value(value["dynamicGeneratedPipelineLayout"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceDeviceGeneratedCommandsPropertiesEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["maxIndirectPipelineCount"]);
    ctx.UInt32Value(value["maxIndirectShaderObjectCount"]);
    ctx.UInt32Value(value["maxIndirectSequenceCount"]);
    ctx.UInt32Value(value["maxIndirectCommandsTokenCount"]);
    ctx.UInt32Value(value["maxIndirectCommandsTokenOffset"]);
    ctx.UInt32Value(value["maxIndirectCommandsIndirectStride"]);
    ctx.FlagsValue(value["supportedIndirectCommandsInputModes"], EnumFromString_VkIndirectCommandsInputModeFlagBitsEXT);
    ctx.FlagsValue(value["supportedIndirectCommandsShaderStages"], EnumFromString_VkShaderStageFlagBits);
    ctx.FlagsValue(value["supportedIndirectCommandsShaderStagesPipelineBinding"], EnumFromString_VkShaderStageFlagBits);
    ctx.FlagsValue(value["supportedIndirectCommandsShaderStagesShaderBinding"], EnumFromString_VkShaderStageFlagBits);
    ctx.UInt32Value(value["deviceGeneratedCommandsTransformFeedback"]);
    ctx.UInt32Value(value["deviceGeneratedCommandsMultiDrawIndirectCount"]);
}

template <> void StructFromApiDump<VkGeneratedCommandsMemoryRequirementsInfoEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.VulkanHandleValue(value["indirectExecutionSet"], VK_OBJECT_TYPE_INDIRECT_EXECUTION_SET_EXT);
    ctx.VulkanHandleValue(value["indirectCommandsLayout"], VK_OBJECT_TYPE_INDIRECT_COMMANDS_LAYOUT_EXT);
    ctx.UInt32Value(value["maxSequenceCount"]);
    ctx.UInt32Value(value["maxDrawCount"]);
}

template <> void StructFromApiDump<VkIndirectExecutionSetPipelineInfoEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.VulkanHandleValue(value["initialPipeline"], VK_OBJECT_TYPE_PIPELINE);
    ctx.UInt32Value(value["maxPipelineCount"]);
}

template <> void StructFromApiDump<VkIndirectExecutionSetShaderLayoutInfoEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["setLayoutCount"]);
    ctx.VulkanHandleArray(value["pSetLayouts"], VK_OBJECT_TYPE_DESCRIPTOR_SET_LAYOUT, ctx.Length(value["setLayoutCount"]));
}

template <> void StructFromApiDump<VkIndirectExecutionSetShaderInfoEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["shaderCount"]);
    ctx.VulkanHandleArray(value["pInitialShaders"], VK_OBJECT_TYPE_SHADER_EXT, ctx.Length(value["shaderCount"]));
    StructArrayFromApiDump<VkIndirectExecutionSetShaderLayoutInfoEXT>(ctx, value["pSetLayoutInfos"], ctx.Length(value["shaderCount"]));
    ctx.UInt32Value(value["maxShaderCount"]);
    ctx.UInt32Value(value["pushConstantRangeCount"]);
    StructArrayFromApiDump<VkPushConstantRange>(ctx, value["pPushConstantRanges"], ctx.Length(value["pushConstantRangeCount"]));
}

template <> void StructFromApiDump<VkGeneratedCommandsInfoEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.FlagsValue(value["shaderStages"], EnumFromString_VkShaderStageFlagBits);
    ctx.VulkanHandleValue(value["indirectExecutionSet"], VK_OBJECT_TYPE_INDIRECT_EXECUTION_SET_EXT);
    ctx.VulkanHandleValue(value["indirectCommandsLayout"], VK_OBJECT_TYPE_INDIRECT_COMMANDS_LAYOUT_EXT);
    ctx.UInt64Value(value["indirectAddress"]);
    ctx.UInt64Value(value["indirectAddressSize"]);
    ctx.UInt64Value(value["preprocessAddress"]);
    ctx.UInt64Value(value["preprocessSize"]);
    ctx.UInt32Value(value["maxSequenceCount"]);
    ctx.UInt64Value(value["sequenceCountAddress"]);
    ctx.UInt32Value(value["maxDrawCount"]);
}

template <> void StructFromApiDump<VkWriteIndirectExecutionSetPipelineEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["index"]);
    ctx.VulkanHandleValue(value["pipeline"], VK_OBJECT_TYPE_PIPELINE);
}

template <> void StructFromApiDump<VkIndirectCommandsPushConstantTokenEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    StructFromApiDump<VkPushConstantRange>(ctx, value["updateRange"]);
}

template <> void StructFromApiDump<VkIndirectCommandsVertexBufferTokenEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.UInt32Value(value["vertexBindingUnit"]);
}

template <> void StructFromApiDump<VkIndirectCommandsIndexBufferTokenEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["mode"], EnumFromString_VkIndirectCommandsInputModeFlagBitsEXT);
}

template <> void StructFromApiDump<VkIndirectCommandsExecutionSetTokenEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["type"], EnumFromString_VkIndirectExecutionSetInfoTypeEXT);
    ctx.FlagsValue(value["shaderStages"], EnumFromString_VkShaderStageFlagBits);
}

template <> void StructFromApiDump<VkIndirectCommandsLayoutCreateInfoEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.FlagsValue(value["flags"], EnumFromString_VkIndirectCommandsLayoutUsageFlagBitsEXT);
    ctx.FlagsValue(value["shaderStages"], EnumFromString_VkShaderStageFlagBits);
    ctx.UInt32Value(value["indirectStride"]);
    ctx.VulkanHandleValue(value["pipelineLayout"], VK_OBJECT_TYPE_PIPELINE_LAYOUT);
    ctx.UInt32Value(value["tokenCount"]);
    StructArrayFromApiDump<VkIndirectCommandsLayoutTokenEXT>(ctx, value["pTokens"], ctx.Length(value["tokenCount"]));
}

template <> void StructFromApiDump<VkDrawIndirectCountIndirectCommandEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.UInt64Value(value["bufferAddress"]);
    ctx.UInt32Value(value["stride"]);
    ctx.UInt32Value(value["commandCount"]);
}

template <> void StructFromApiDump<VkBindVertexBufferIndirectCommandEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.UInt64Value(value["bufferAddress"]);
    ctx.UInt32Value(value["size"]);
    ctx.UInt32Value(value["stride"]);
}

template <> void StructFromApiDump<VkBindIndexBufferIndirectCommandEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.UInt64Value(value["bufferAddress"]);
    ctx.UInt32Value(value["size"]);
    ctx.EnumValue(value["indexType"], EnumFromString_VkIndexType);
}

template <> void StructFromApiDump<VkGeneratedCommandsPipelineInfoEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.VulkanHandleValue(value["pipeline"], VK_OBJECT_TYPE_PIPELINE);
}

template <> void StructFromApiDump<VkGeneratedCommandsShaderInfoEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["shaderCount"]);
    ctx.VulkanHandleArray(value["pShaders"], VK_OBJECT_TYPE_SHADER_EXT, ctx.Length(value["shaderCount"]));
}

template <> void StructFromApiDump<VkWriteIndirectExecutionSetShaderEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["index"]);
    ctx.VulkanHandleValue(value["shader"], VK_OBJECT_TYPE_SHADER_EXT);
}

template <> void StructFromApiDump<VkPhysicalDeviceImageAlignmentControlFeaturesMESA>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["imageAlignmentControl"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceImageAlignmentControlPropertiesMESA>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["supportedImageAlignmentMask"]);
}

template <> void StructFromApiDump<VkImageAlignmentControlCreateInfoMESA>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["maximumRequestedAlignment"]);
}

template <> void StructFromApiDump<VkPushConstantBankInfoNV>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["bank"]);
}

template <> void StructFromApiDump<VkPhysicalDevicePushConstantBankFeaturesNV>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["pushConstantBank"]);
}

template <> void StructFromApiDump<VkPhysicalDevicePushConstantBankPropertiesNV>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["maxGraphicsPushConstantBanks"]);
    ctx.UInt32Value(value["maxComputePushConstantBanks"]);
    ctx.UInt32Value(value["maxGraphicsPushDataBanks"]);
    ctx.UInt32Value(value["maxComputePushDataBanks"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceRayTracingInvocationReorderPropertiesEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.EnumValue(value["rayTracingInvocationReorderReorderingHint"], EnumFromString_VkRayTracingInvocationReorderModeEXT);
    ctx.UInt32Value(value["maxShaderBindingTableRecordIndex"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceRayTracingInvocationReorderFeaturesEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["rayTracingInvocationReorder"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceDepthClampControlFeaturesEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["depthClampControl"]);
}

template <> void StructFromApiDump<VkPipelineViewportDepthClampControlCreateInfoEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.EnumValue(value["depthClampMode"], EnumFromString_VkDepthClampModeEXT);
    StructPtrFromApiDump<VkDepthClampRangeEXT>(ctx, value["pDepthClampRange"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceHdrVividFeaturesHUAWEI>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["hdrVivid"]);
}

template <> void StructFromApiDump<VkHdrVividDynamicMetadataHUAWEI>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.SizeTValue(value["dynamicMetadataSize"]);
    ctx.UInt8Array(value["pDynamicMetadata"], ctx.Length(value["dynamicMetadataSize"]));
}

template <> void StructFromApiDump<VkCooperativeMatrixFlexibleDimensionsPropertiesNV>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["MGranularity"]);
    ctx.UInt32Value(value["NGranularity"]);
    ctx.UInt32Value(value["KGranularity"]);
    ctx.EnumValue(value["AType"], EnumFromString_VkComponentTypeKHR);
    ctx.EnumValue(value["BType"], EnumFromString_VkComponentTypeKHR);
    ctx.EnumValue(value["CType"], EnumFromString_VkComponentTypeKHR);
    ctx.EnumValue(value["ResultType"], EnumFromString_VkComponentTypeKHR);
    ctx.UInt32Value(value["saturatingAccumulation"]);
    ctx.EnumValue(value["scope"], EnumFromString_VkScopeKHR);
    ctx.UInt32Value(value["workgroupInvocations"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceCooperativeMatrix2FeaturesNV>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["cooperativeMatrixWorkgroupScope"]);
    ctx.UInt32Value(value["cooperativeMatrixFlexibleDimensions"]);
    ctx.UInt32Value(value["cooperativeMatrixReductions"]);
    ctx.UInt32Value(value["cooperativeMatrixConversions"]);
    ctx.UInt32Value(value["cooperativeMatrixPerElementOperations"]);
    ctx.UInt32Value(value["cooperativeMatrixTensorAddressing"]);
    ctx.UInt32Value(value["cooperativeMatrixBlockLoads"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceCooperativeMatrix2PropertiesNV>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["cooperativeMatrixWorkgroupScopeMaxWorkgroupSize"]);
    ctx.UInt32Value(value["cooperativeMatrixFlexibleDimensionsMaxDimension"]);
    ctx.UInt32Value(value["cooperativeMatrixWorkgroupScopeReservedSharedMemory"]);
}

template <> void StructFromApiDump<VkPhysicalDevicePipelineOpacityMicromapFeaturesARM>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["pipelineOpacityMicromap"]);
}

template <> void StructFromApiDump<VkImportMemoryMetalHandleInfoEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.EnumValue(value["handleType"], EnumFromString_VkExternalMemoryHandleTypeFlagBits);
    ctx.VoidPtrValue(value["handle"]);
}

template <> void StructFromApiDump<VkMemoryMetalHandlePropertiesEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["memoryTypeBits"]);
}

template <> void StructFromApiDump<VkMemoryGetMetalHandleInfoEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.VulkanHandleValue(value["memory"], VK_OBJECT_TYPE_DEVICE_MEMORY);
    ctx.EnumValue(value["handleType"], EnumFromString_VkExternalMemoryHandleTypeFlagBits);
}

template <> void StructFromApiDump<VkPhysicalDevicePerformanceCountersByRegionFeaturesARM>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["performanceCountersByRegion"]);
}

template <> void StructFromApiDump<VkPhysicalDevicePerformanceCountersByRegionPropertiesARM>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["maxPerRegionPerformanceCounters"]);
    StructFromApiDump<VkExtent2D>(ctx, value["performanceCounterRegionSize"]);
    ctx.UInt32Value(value["rowStrideAlignment"]);
    ctx.UInt32Value(value["regionAlignment"]);
    ctx.UInt32Value(value["identityTransformOrder"]);
}

template <> void StructFromApiDump<VkPerformanceCounterARM>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["counterID"]);
}

template <> void StructFromApiDump<VkPerformanceCounterDescriptionARM>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.FlagsValue(value["flags"]);
    ctx.StringValue(value["name"]);
}

template <> void StructFromApiDump<VkRenderPassPerformanceCountersByRegionBeginInfoARM>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["counterAddressCount"]);
    ctx.UInt64Array(value["pCounterAddresses"], ctx.Length(value["counterAddressCount"]));
    ctx.UInt32Value(value["serializeRegions"]);
    ctx.UInt32Value(value["counterIndexCount"]);
    ctx.UInt32Array(value["pCounterIndices"], ctx.Length(value["counterIndexCount"]));
}

template <> void StructFromApiDump<VkPhysicalDeviceVertexAttributeRobustnessFeaturesEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["vertexAttributeRobustness"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceFormatPackFeaturesARM>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["formatPack"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceFragmentDensityMapLayeredFeaturesVALVE>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["fragmentDensityMapLayered"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceFragmentDensityMapLayeredPropertiesVALVE>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["maxFragmentDensityMapLayers"]);
}

template <> void StructFromApiDump<VkPipelineFragmentDensityMapLayeredCreateInfoVALVE>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["maxFragmentDensityMapLayers"]);
}

template <> void StructFromApiDump<VkSetPresentConfigNV>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["numFramesPerBatch"]);
    ctx.UInt32Value(value["presentConfigFeedback"]);
}

template <> void StructFromApiDump<VkPhysicalDevicePresentMeteringFeaturesNV>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["presentMetering"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceMultisampledRenderToSwapchainFeaturesEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["multisampledRenderToSwapchain"]);
}

template <> void StructFromApiDump<VkSwapchainFlagsSurfaceCapabilitiesEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.FlagsValue(value["swapchainSupportedFlags"], EnumFromString_VkSwapchainCreateFlagBitsKHR);
}

template <> void StructFromApiDump<VkPhysicalDeviceZeroInitializeDeviceMemoryFeaturesEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["zeroInitializeDeviceMemory"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceShader64BitIndexingFeaturesEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["shader64BitIndexing"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceCustomResolveFeaturesEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["customResolve"]);
}

template <> void StructFromApiDump<VkBeginCustomResolveInfoEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
}

template <> void StructFromApiDump<VkCustomResolveCreateInfoEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["customResolve"]);
    ctx.UInt32Value(value["colorAttachmentCount"]);
    ctx.EnumArray(value["pColorAttachmentFormats"], EnumFromString_VkFormat, ctx.Length(value["colorAttachmentCount"]));
    ctx.EnumValue(value["depthAttachmentFormat"], EnumFromString_VkFormat);
    ctx.EnumValue(value["stencilAttachmentFormat"], EnumFromString_VkFormat);
}

template <> void StructFromApiDump<VkPipelineCacheHeaderVersionDataGraphQCOM>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.UInt32Value(value["headerSize"]);
    ctx.EnumValue(value["headerVersion"], EnumFromString_VkPipelineCacheHeaderVersion);
    ctx.EnumValue(value["cacheType"], EnumFromString_VkDataGraphModelCacheTypeQCOM);
    ctx.UInt32Value(value["cacheVersion"]);
    ctx.UInt32Array(value["toolchainVersion"]);
}

template <> void StructFromApiDump<VkDataGraphPipelineBuiltinModelCreateInfoQCOM>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    StructPtrFromApiDump<VkPhysicalDeviceDataGraphOperationSupportARM>(ctx, value["pOperation"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceDataGraphModelFeaturesQCOM>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["dataGraphModel"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceDataGraphOpticalFlowFeaturesARM>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["dataGraphOpticalFlow"]);
}

template <> void StructFromApiDump<VkQueueFamilyDataGraphOpticalFlowPropertiesARM>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.FlagsValue(value["supportedOutputGridSizes"], EnumFromString_VkDataGraphOpticalFlowGridSizeFlagBitsARM);
    ctx.FlagsValue(value["supportedHintGridSizes"], EnumFromString_VkDataGraphOpticalFlowGridSizeFlagBitsARM);
    ctx.UInt32Value(value["hintSupported"]);
    ctx.UInt32Value(value["costSupported"]);
    ctx.UInt32Value(value["minWidth"]);
    ctx.UInt32Value(value["minHeight"]);
    ctx.UInt32Value(value["maxWidth"]);
    ctx.UInt32Value(value["maxHeight"]);
}

template <> void StructFromApiDump<VkDataGraphPipelineOpticalFlowCreateInfoARM>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["width"]);
    ctx.UInt32Value(value["height"]);
    ctx.EnumValue(value["imageFormat"], EnumFromString_VkFormat);
    ctx.EnumValue(value["flowVectorFormat"], EnumFromString_VkFormat);
    ctx.EnumValue(value["costFormat"], EnumFromString_VkFormat);
    ctx.FlagsValue(value["outputGridSize"], EnumFromString_VkDataGraphOpticalFlowGridSizeFlagBitsARM);
    ctx.FlagsValue(value["hintGridSize"], EnumFromString_VkDataGraphOpticalFlowGridSizeFlagBitsARM);
    ctx.EnumValue(value["performanceLevel"], EnumFromString_VkDataGraphOpticalFlowPerformanceLevelARM);
    ctx.FlagsValue(value["flags"], EnumFromString_VkDataGraphOpticalFlowCreateFlagBitsARM);
}

template <> void StructFromApiDump<VkDataGraphOpticalFlowImageFormatPropertiesARM>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.EnumValue(value["format"], EnumFromString_VkFormat);
}

template <> void StructFromApiDump<VkDataGraphOpticalFlowImageFormatInfoARM>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.FlagsValue(value["usage"], EnumFromString_VkDataGraphOpticalFlowImageUsageFlagBitsARM);
}

template <> void StructFromApiDump<VkDataGraphPipelineOpticalFlowDispatchInfoARM>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.FlagsValue(value["flags"], EnumFromString_VkDataGraphOpticalFlowExecuteFlagBitsARM);
    ctx.UInt32Value(value["meanFlowL1NormHint"]);
}

template <> void StructFromApiDump<VkDataGraphPipelineResourceInfoImageLayoutARM>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.EnumValue(value["layout"], EnumFromString_VkImageLayout);
}

template <> void StructFromApiDump<VkDataGraphPipelineSingleNodeConnectionARM>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["set"]);
    ctx.UInt32Value(value["binding"]);
    ctx.EnumValue(value["connection"], EnumFromString_VkDataGraphPipelineNodeConnectionTypeARM);
}

template <> void StructFromApiDump<VkDataGraphPipelineSingleNodeCreateInfoARM>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.EnumValue(value["nodeType"], EnumFromString_VkDataGraphPipelineNodeTypeARM);
    ctx.UInt32Value(value["connectionCount"]);
    StructArrayFromApiDump<VkDataGraphPipelineSingleNodeConnectionARM>(ctx, value["pConnections"], ctx.Length(value["connectionCount"]));
}

template <> void StructFromApiDump<VkPhysicalDeviceShaderLongVectorFeaturesEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["longVector"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceShaderLongVectorPropertiesEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["maxVectorComponents"]);
}

template <> void StructFromApiDump<VkPhysicalDevicePipelineCacheIncrementalModeFeaturesSEC>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["pipelineCacheIncrementalMode"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceShaderUniformBufferUnsizedArrayFeaturesEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["shaderUniformBufferUnsizedArray"]);
}

template <> void StructFromApiDump<VkComputeOccupancyPriorityParametersNV>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.FloatValue(value["occupancyPriority"]);
    ctx.FloatValue(value["occupancyThrottling"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceComputeOccupancyPriorityFeaturesNV>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["computeOccupancyPriority"]);
}

template <> void StructFromApiDump<VkCooperativeMatrixProperties2EXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["MGranularity"]);
    ctx.UInt32Value(value["NGranularity"]);
    ctx.UInt32Value(value["KGranularity"]);
    ctx.EnumValue(value["AType"], EnumFromString_VkComponentTypeKHR);
    ctx.EnumValue(value["BType"], EnumFromString_VkComponentTypeKHR);
    ctx.EnumValue(value["CType"], EnumFromString_VkComponentTypeKHR);
    ctx.EnumValue(value["ResultType"], EnumFromString_VkComponentTypeKHR);
}

template <> void StructFromApiDump<VkPhysicalDeviceCooperativeMatrixInfo2EXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.EnumValue(value["scope"], EnumFromString_VkScopeKHR);
    ctx.UInt32Value(value["invocations"]);
    ctx.UInt32Value(value["subgroupSize"]);
    ctx.FlagsValue(value["flags"], EnumFromString_VkCooperativeMatrixFlagBitsEXT);
}

template <> void StructFromApiDump<VkPhysicalDeviceCooperativeMatrixMaintenance1FeaturesEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["cooperativeMatrixProperties2"]);
    ctx.UInt32Value(value["cooperativeMatrixReductions"]);
    ctx.UInt32Value(value["cooperativeMatrixConversions"]);
    ctx.UInt32Value(value["cooperativeMatrixPerElementOperations"]);
    ctx.UInt32Value(value["cooperativeMatrixGetCoordinate"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceShaderSubgroupPartitionedFeaturesEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["shaderSubgroupPartitioned"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceShaderOCPMicroscalingTypesFeaturesEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["shaderFloat4"]);
    ctx.UInt32Value(value["shaderFloat6"]);
    ctx.UInt32Value(value["shaderFloat8UnsignedE8M0"]);
    ctx.UInt32Value(value["shaderMXInt8"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceShaderMixedFloatDotProductFeaturesVALVE>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["shaderMixedFloatDotProductFloat16AccFloat32"]);
    ctx.UInt32Value(value["shaderMixedFloatDotProductFloat16AccFloat16"]);
    ctx.UInt32Value(value["shaderMixedFloatDotProductBFloat16Acc"]);
    ctx.UInt32Value(value["shaderMixedFloatDotProductFloat8AccFloat32"]);
}

template <> void StructFromApiDump<VkThrottleHintSubmitInfoSEC>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.EnumValue(value["throttleHint"], EnumFromString_VkThrottleHintTypeSEC);
}

template <> void StructFromApiDump<VkPhysicalDeviceThrottleHintFeaturesSEC>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["throttleHint"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceDataGraphNeuralAcceleratorStatisticsFeaturesARM>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["dataGraphNeuralAcceleratorStatistics"]);
}

template <> void StructFromApiDump<VkDataGraphPipelineNeuralStatisticsCreateInfoARM>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["allowNeuralStatistics"]);
}

template <> void StructFromApiDump<VkDataGraphPipelineSessionNeuralStatisticsCreateInfoARM>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.EnumValue(value["mode"], EnumFromString_VkNeuralAcceleratorStatisticsModeARM);
}

template <> void StructFromApiDump<VkPhysicalDevicePrimitiveRestartIndexFeaturesEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["primitiveRestartIndex"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceImageTilingControlFeaturesEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["imageTilingControl"]);
}

template <> void StructFromApiDump<VkImageTilingControlCreateInfoEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.EnumValue(value["tilingControl"], EnumFromString_VkImageTilingControlEXT);
}

template <> void StructFromApiDump<VkPhysicalDeviceCooperativeMatrixDecodeVectorFeaturesNV>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["cooperativeMatrixDecodeVector"]);
}

template <> void StructFromApiDump<VkPhysicalDevicePrivateDataBaseHandleFeaturesNV>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["privateDataBaseHandle"]);
}

template <> void StructFromApiDump<VkAccelerationStructureBuildRangeInfoKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.UInt32Value(value["primitiveCount"]);
    ctx.UInt32Value(value["primitiveOffset"]);
    ctx.UInt32Value(value["firstVertex"]);
    ctx.UInt32Value(value["transformOffset"]);
}

template <> void StructFromApiDump<VkAccelerationStructureGeometryTrianglesDataKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.EnumValue(value["vertexFormat"], EnumFromString_VkFormat);
    StructFromApiDump<VkDeviceOrHostAddressConstKHR>(ctx, value["vertexData"]);
    ctx.UInt64Value(value["vertexStride"]);
    ctx.UInt32Value(value["maxVertex"]);
    ctx.EnumValue(value["indexType"], EnumFromString_VkIndexType);
    StructFromApiDump<VkDeviceOrHostAddressConstKHR>(ctx, value["indexData"]);
    StructFromApiDump<VkDeviceOrHostAddressConstKHR>(ctx, value["transformData"]);
}

template <> void StructFromApiDump<VkAccelerationStructureGeometryAabbsDataKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    StructFromApiDump<VkDeviceOrHostAddressConstKHR>(ctx, value["data"]);
    ctx.UInt64Value(value["stride"]);
}

template <> void StructFromApiDump<VkAccelerationStructureGeometryInstancesDataKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["arrayOfPointers"]);
    StructFromApiDump<VkDeviceOrHostAddressConstKHR>(ctx, value["data"]);
}

template <> void StructFromApiDump<VkAccelerationStructureBuildGeometryInfoKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.EnumValue(value["type"], EnumFromString_VkAccelerationStructureTypeKHR);
    ctx.FlagsValue(value["flags"], EnumFromString_VkBuildAccelerationStructureFlagBitsKHR);
    ctx.EnumValue(value["mode"], EnumFromString_VkBuildAccelerationStructureModeKHR);
    ctx.VulkanHandleValue(value["srcAccelerationStructure"], VK_OBJECT_TYPE_ACCELERATION_STRUCTURE_KHR);
    ctx.VulkanHandleValue(value["dstAccelerationStructure"], VK_OBJECT_TYPE_ACCELERATION_STRUCTURE_KHR);
    ctx.UInt32Value(value["geometryCount"]);
    StructArrayFromApiDump<VkAccelerationStructureGeometryKHR>(ctx, value["pGeometries"], ctx.Length(value["geometryCount"]));
    StructArrayFromApiDump<VkAccelerationStructureGeometryKHR>(ctx, value["ppGeometries"], (ctx.Length(value["geometryCount"]),1));
    StructFromApiDump<VkDeviceOrHostAddressKHR>(ctx, value["scratchData"]);
}

template <> void StructFromApiDump<VkAccelerationStructureCreateInfoKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.FlagsValue(value["createFlags"], EnumFromString_VkAccelerationStructureCreateFlagBitsKHR);
    ctx.VulkanHandleValue(value["buffer"], VK_OBJECT_TYPE_BUFFER);
    ctx.UInt64Value(value["offset"]);
    ctx.UInt64Value(value["size"]);
    ctx.EnumValue(value["type"], EnumFromString_VkAccelerationStructureTypeKHR);
    ctx.UInt64Value(value["deviceAddress"]);
}

template <> void StructFromApiDump<VkWriteDescriptorSetAccelerationStructureKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["accelerationStructureCount"]);
    ctx.VulkanHandleArray(value["pAccelerationStructures"], VK_OBJECT_TYPE_ACCELERATION_STRUCTURE_KHR, ctx.Length(value["accelerationStructureCount"]));
}

template <> void StructFromApiDump<VkPhysicalDeviceAccelerationStructureFeaturesKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["accelerationStructure"]);
    ctx.UInt32Value(value["accelerationStructureCaptureReplay"]);
    ctx.UInt32Value(value["accelerationStructureIndirectBuild"]);
    ctx.UInt32Value(value["accelerationStructureHostCommands"]);
    ctx.UInt32Value(value["descriptorBindingAccelerationStructureUpdateAfterBind"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceAccelerationStructurePropertiesKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt64Value(value["maxGeometryCount"]);
    ctx.UInt64Value(value["maxInstanceCount"]);
    ctx.UInt64Value(value["maxPrimitiveCount"]);
    ctx.UInt32Value(value["maxPerStageDescriptorAccelerationStructures"]);
    ctx.UInt32Value(value["maxPerStageDescriptorUpdateAfterBindAccelerationStructures"]);
    ctx.UInt32Value(value["maxDescriptorSetAccelerationStructures"]);
    ctx.UInt32Value(value["maxDescriptorSetUpdateAfterBindAccelerationStructures"]);
    ctx.UInt32Value(value["minAccelerationStructureScratchOffsetAlignment"]);
}

template <> void StructFromApiDump<VkAccelerationStructureDeviceAddressInfoKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.VulkanHandleValue(value["accelerationStructure"], VK_OBJECT_TYPE_ACCELERATION_STRUCTURE_KHR);
}

template <> void StructFromApiDump<VkAccelerationStructureVersionInfoKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt8Array(value["pVersionData"]);
}

template <> void StructFromApiDump<VkCopyAccelerationStructureToMemoryInfoKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.VulkanHandleValue(value["src"], VK_OBJECT_TYPE_ACCELERATION_STRUCTURE_KHR);
    StructFromApiDump<VkDeviceOrHostAddressKHR>(ctx, value["dst"]);
    ctx.EnumValue(value["mode"], EnumFromString_VkCopyAccelerationStructureModeKHR);
}

template <> void StructFromApiDump<VkCopyMemoryToAccelerationStructureInfoKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    StructFromApiDump<VkDeviceOrHostAddressConstKHR>(ctx, value["src"]);
    ctx.VulkanHandleValue(value["dst"], VK_OBJECT_TYPE_ACCELERATION_STRUCTURE_KHR);
    ctx.EnumValue(value["mode"], EnumFromString_VkCopyAccelerationStructureModeKHR);
}

template <> void StructFromApiDump<VkCopyAccelerationStructureInfoKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.VulkanHandleValue(value["src"], VK_OBJECT_TYPE_ACCELERATION_STRUCTURE_KHR);
    ctx.VulkanHandleValue(value["dst"], VK_OBJECT_TYPE_ACCELERATION_STRUCTURE_KHR);
    ctx.EnumValue(value["mode"], EnumFromString_VkCopyAccelerationStructureModeKHR);
}

template <> void StructFromApiDump<VkRayTracingShaderGroupCreateInfoKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.EnumValue(value["type"], EnumFromString_VkRayTracingShaderGroupTypeKHR);
    ctx.UInt32Value(value["generalShader"]);
    ctx.UInt32Value(value["closestHitShader"]);
    ctx.UInt32Value(value["anyHitShader"]);
    ctx.UInt32Value(value["intersectionShader"]);
    ctx.VoidPtrValue(value["pShaderGroupCaptureReplayHandle"]);
}

template <> void StructFromApiDump<VkRayTracingPipelineInterfaceCreateInfoKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["maxPipelineRayPayloadSize"]);
    ctx.UInt32Value(value["maxPipelineRayHitAttributeSize"]);
}

template <> void StructFromApiDump<VkRayTracingPipelineCreateInfoKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.FlagsValue(value["flags"], EnumFromString_VkPipelineCreateFlagBits);
    ctx.UInt32Value(value["stageCount"]);
    StructArrayFromApiDump<VkPipelineShaderStageCreateInfo>(ctx, value["pStages"], ctx.Length(value["stageCount"]));
    ctx.UInt32Value(value["groupCount"]);
    StructArrayFromApiDump<VkRayTracingShaderGroupCreateInfoKHR>(ctx, value["pGroups"], ctx.Length(value["groupCount"]));
    ctx.UInt32Value(value["maxPipelineRayRecursionDepth"]);
    StructPtrFromApiDump<VkPipelineLibraryCreateInfoKHR>(ctx, value["pLibraryInfo"]);
    StructPtrFromApiDump<VkRayTracingPipelineInterfaceCreateInfoKHR>(ctx, value["pLibraryInterface"]);
    StructPtrFromApiDump<VkPipelineDynamicStateCreateInfo>(ctx, value["pDynamicState"]);
    ctx.VulkanHandleValue(value["layout"], VK_OBJECT_TYPE_PIPELINE_LAYOUT);
    ctx.VulkanHandleValue(value["basePipelineHandle"], VK_OBJECT_TYPE_PIPELINE);
    ctx.Int32Value(value["basePipelineIndex"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceRayTracingPipelineFeaturesKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["rayTracingPipeline"]);
    ctx.UInt32Value(value["rayTracingPipelineShaderGroupHandleCaptureReplay"]);
    ctx.UInt32Value(value["rayTracingPipelineShaderGroupHandleCaptureReplayMixed"]);
    ctx.UInt32Value(value["rayTracingPipelineTraceRaysIndirect"]);
    ctx.UInt32Value(value["rayTraversalPrimitiveCulling"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceRayTracingPipelinePropertiesKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["shaderGroupHandleSize"]);
    ctx.UInt32Value(value["maxRayRecursionDepth"]);
    ctx.UInt32Value(value["maxShaderGroupStride"]);
    ctx.UInt32Value(value["shaderGroupBaseAlignment"]);
    ctx.UInt32Value(value["shaderGroupHandleCaptureReplaySize"]);
    ctx.UInt32Value(value["maxRayDispatchInvocationCount"]);
    ctx.UInt32Value(value["shaderGroupHandleAlignment"]);
    ctx.UInt32Value(value["maxRayHitAttributeSize"]);
}

template <> void StructFromApiDump<VkStridedDeviceAddressRegionKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.UInt64Value(value["deviceAddress"]);
    ctx.UInt64Value(value["stride"]);
    ctx.UInt64Value(value["size"]);
}

template <> void StructFromApiDump<VkTraceRaysIndirectCommandKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.UInt32Value(value["width"]);
    ctx.UInt32Value(value["height"]);
    ctx.UInt32Value(value["depth"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceRayQueryFeaturesKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["rayQuery"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceMeshShaderFeaturesEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["taskShader"]);
    ctx.UInt32Value(value["meshShader"]);
    ctx.UInt32Value(value["multiviewMeshShader"]);
    ctx.UInt32Value(value["primitiveFragmentShadingRateMeshShader"]);
    ctx.UInt32Value(value["meshShaderQueries"]);
}

template <> void StructFromApiDump<VkPhysicalDeviceMeshShaderPropertiesEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["maxTaskWorkGroupTotalCount"]);
    ctx.UInt32Array(value["maxTaskWorkGroupCount"], 3);
    ctx.UInt32Value(value["maxTaskWorkGroupInvocations"]);
    ctx.UInt32Array(value["maxTaskWorkGroupSize"], 3);
    ctx.UInt32Value(value["maxTaskPayloadSize"]);
    ctx.UInt32Value(value["maxTaskSharedMemorySize"]);
    ctx.UInt32Value(value["maxTaskPayloadAndSharedMemorySize"]);
    ctx.UInt32Value(value["maxMeshWorkGroupTotalCount"]);
    ctx.UInt32Array(value["maxMeshWorkGroupCount"], 3);
    ctx.UInt32Value(value["maxMeshWorkGroupInvocations"]);
    ctx.UInt32Array(value["maxMeshWorkGroupSize"], 3);
    ctx.UInt32Value(value["maxMeshSharedMemorySize"]);
    ctx.UInt32Value(value["maxMeshPayloadAndSharedMemorySize"]);
    ctx.UInt32Value(value["maxMeshOutputMemorySize"]);
    ctx.UInt32Value(value["maxMeshPayloadAndOutputMemorySize"]);
    ctx.UInt32Value(value["maxMeshOutputComponents"]);
    ctx.UInt32Value(value["maxMeshOutputVertices"]);
    ctx.UInt32Value(value["maxMeshOutputPrimitives"]);
    ctx.UInt32Value(value["maxMeshOutputLayers"]);
    ctx.UInt32Value(value["maxMeshMultiviewViewCount"]);
    ctx.UInt32Value(value["meshOutputPerVertexGranularity"]);
    ctx.UInt32Value(value["meshOutputPerPrimitiveGranularity"]);
    ctx.UInt32Value(value["maxPreferredTaskWorkGroupInvocations"]);
    ctx.UInt32Value(value["maxPreferredMeshWorkGroupInvocations"]);
    ctx.UInt32Value(value["prefersLocalInvocationVertexOutput"]);
    ctx.UInt32Value(value["prefersLocalInvocationPrimitiveOutput"]);
    ctx.UInt32Value(value["prefersCompactVertexOutput"]);
    ctx.UInt32Value(value["prefersCompactPrimitiveOutput"]);
}

template <> void StructFromApiDump<VkDrawMeshTasksIndirectCommandEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.UInt32Value(value["groupCountX"]);
    ctx.UInt32Value(value["groupCountY"]);
    ctx.UInt32Value(value["groupCountZ"]);
}

GFXRECON_END_NAMESPACE(decode)
GFXRECON_END_NAMESPACE(gfxrecon)
