//
//   Copyright 2020 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//

#include "Garch/glApi.h"

#include "Tf/diagnostic.h"

#include "Arch/defines.h"
#include "Arch/library.h"

#include <cassert>
#include <cstdlib>
#include <cstring>
#include <vector>

PXR_NAMESPACE_OPEN_SCOPE
namespace internal {
namespace GLApi {

bool GARCH_GL_VERSION_1_0 = false;
bool GARCH_GL_VERSION_1_1 = false;
bool GARCH_GL_VERSION_1_2 = false;
bool GARCH_GL_VERSION_1_3 = false;
bool GARCH_GL_VERSION_1_4 = false;
bool GARCH_GL_VERSION_1_5 = false;
bool GARCH_GL_VERSION_2_0 = false;
bool GARCH_GL_VERSION_2_1 = false;
bool GARCH_GL_VERSION_3_0 = false;
bool GARCH_GL_VERSION_3_1 = false;
bool GARCH_GL_VERSION_3_2 = false;
bool GARCH_GL_VERSION_3_3 = false;
bool GARCH_GL_VERSION_4_0 = false;
bool GARCH_GL_VERSION_4_1 = false;
bool GARCH_GL_VERSION_4_2 = false;
bool GARCH_GL_VERSION_4_3 = false;
bool GARCH_GL_VERSION_4_4 = false;
bool GARCH_GL_VERSION_4_5 = false;
bool GARCH_GL_VERSION_4_6 = false;

bool GARCH_GL_AMD_blend_minmax_factor = false;
bool GARCH_GL_AMD_conservative_depth = false;
bool GARCH_GL_AMD_debug_output = false;
bool GARCH_GL_AMD_depth_clamp_separate = false;
bool GARCH_GL_AMD_draw_buffers_blend = false;
bool GARCH_GL_AMD_framebuffer_multisample_advanced = false;
bool GARCH_GL_AMD_framebuffer_sample_positions = false;
bool GARCH_GL_AMD_gcn_shader = false;
bool GARCH_GL_AMD_gpu_shader_half_float = false;
bool GARCH_GL_AMD_gpu_shader_int16 = false;
bool GARCH_GL_AMD_gpu_shader_int64 = false;
bool GARCH_GL_AMD_interleaved_elements = false;
bool GARCH_GL_AMD_multi_draw_indirect = false;
bool GARCH_GL_AMD_name_gen_delete = false;
bool GARCH_GL_AMD_occlusion_query_event = false;
bool GARCH_GL_AMD_performance_monitor = false;
bool GARCH_GL_AMD_pinned_memory = false;
bool GARCH_GL_AMD_query_buffer_object = false;
bool GARCH_GL_AMD_sample_positions = false;
bool GARCH_GL_AMD_seamless_cubemap_per_texture = false;
bool GARCH_GL_AMD_shader_atomic_counter_ops = false;
bool GARCH_GL_AMD_shader_ballot = false;
bool GARCH_GL_AMD_shader_gpu_shader_half_float_fetch = false;
bool GARCH_GL_AMD_shader_image_load_store_lod = false;
bool GARCH_GL_AMD_shader_stencil_export = false;
bool GARCH_GL_AMD_shader_trinary_minmax = false;
bool GARCH_GL_AMD_shader_explicit_vertex_parameter = false;
bool GARCH_GL_AMD_sparse_texture = false;
bool GARCH_GL_AMD_stencil_operation_extended = false;
bool GARCH_GL_AMD_texture_gather_bias_lod = false;
bool GARCH_GL_AMD_texture_texture4 = false;
bool GARCH_GL_AMD_transform_feedback3_lines_triangles = false;
bool GARCH_GL_AMD_transform_feedback4 = false;
bool GARCH_GL_AMD_vertex_shader_layer = false;
bool GARCH_GL_AMD_vertex_shader_tessellator = false;
bool GARCH_GL_AMD_vertex_shader_viewport_index = false;
bool GARCH_GL_APPLE_aux_depth_stencil = false;
bool GARCH_GL_APPLE_client_storage = false;
bool GARCH_GL_APPLE_element_array = false;
bool GARCH_GL_APPLE_fence = false;
bool GARCH_GL_APPLE_float_pixels = false;
bool GARCH_GL_APPLE_flush_buffer_range = false;
bool GARCH_GL_APPLE_object_purgeable = false;
bool GARCH_GL_APPLE_rgb_422 = false;
bool GARCH_GL_APPLE_row_bytes = false;
bool GARCH_GL_APPLE_specular_vector = false;
bool GARCH_GL_APPLE_texture_range = false;
bool GARCH_GL_APPLE_transform_hint = false;
bool GARCH_GL_APPLE_vertex_array_object = false;
bool GARCH_GL_APPLE_vertex_array_range = false;
bool GARCH_GL_APPLE_vertex_program_evaluators = false;
bool GARCH_GL_APPLE_ycbcr_422 = false;
bool GARCH_GL_ARB_ES2_compatibility = false;
bool GARCH_GL_ARB_ES3_1_compatibility = false;
bool GARCH_GL_ARB_ES3_2_compatibility = false;
bool GARCH_GL_ARB_ES3_compatibility = false;
bool GARCH_GL_ARB_arrays_of_arrays = false;
bool GARCH_GL_ARB_base_instance = false;
bool GARCH_GL_ARB_bindless_texture = false;
bool GARCH_GL_ARB_blend_func_extended = false;
bool GARCH_GL_ARB_buffer_storage = false;
bool GARCH_GL_ARB_cl_event = false;
bool GARCH_GL_ARB_clear_buffer_object = false;
bool GARCH_GL_ARB_clear_texture = false;
bool GARCH_GL_ARB_clip_control = false;
bool GARCH_GL_ARB_color_buffer_float = false;
bool GARCH_GL_ARB_compatibility = false;
bool GARCH_GL_ARB_compressed_texture_pixel_storage = false;
bool GARCH_GL_ARB_compute_shader = false;
bool GARCH_GL_ARB_compute_variable_group_size = false;
bool GARCH_GL_ARB_conditional_render_inverted = false;
bool GARCH_GL_ARB_conservative_depth = false;
bool GARCH_GL_ARB_copy_buffer = false;
bool GARCH_GL_ARB_copy_image = false;
bool GARCH_GL_ARB_cull_distance = false;
bool GARCH_GL_ARB_debug_output = false;
bool GARCH_GL_ARB_depth_buffer_float = false;
bool GARCH_GL_ARB_depth_clamp = false;
bool GARCH_GL_ARB_depth_texture = false;
bool GARCH_GL_ARB_derivative_control = false;
bool GARCH_GL_ARB_direct_state_access = false;
bool GARCH_GL_ARB_draw_buffers = false;
bool GARCH_GL_ARB_draw_buffers_blend = false;
bool GARCH_GL_ARB_draw_elements_base_vertex = false;
bool GARCH_GL_ARB_draw_indirect = false;
bool GARCH_GL_ARB_draw_instanced = false;
bool GARCH_GL_ARB_enhanced_layouts = false;
bool GARCH_GL_ARB_explicit_attrib_location = false;
bool GARCH_GL_ARB_explicit_uniform_location = false;
bool GARCH_GL_ARB_fragment_coord_conventions = false;
bool GARCH_GL_ARB_fragment_layer_viewport = false;
bool GARCH_GL_ARB_fragment_program = false;
bool GARCH_GL_ARB_fragment_program_shadow = false;
bool GARCH_GL_ARB_fragment_shader = false;
bool GARCH_GL_ARB_fragment_shader_interlock = false;
bool GARCH_GL_ARB_framebuffer_no_attachments = false;
bool GARCH_GL_ARB_framebuffer_object = false;
bool GARCH_GL_ARB_framebuffer_sRGB = false;
bool GARCH_GL_ARB_geometry_shader4 = false;
bool GARCH_GL_ARB_get_program_binary = false;
bool GARCH_GL_ARB_get_texture_sub_image = false;
bool GARCH_GL_ARB_gl_spirv = false;
bool GARCH_GL_ARB_gpu_shader5 = false;
bool GARCH_GL_ARB_gpu_shader_fp64 = false;
bool GARCH_GL_ARB_gpu_shader_int64 = false;
bool GARCH_GL_ARB_half_float_pixel = false;
bool GARCH_GL_ARB_half_float_vertex = false;
bool GARCH_GL_ARB_imaging = false;
bool GARCH_GL_ARB_indirect_parameters = false;
bool GARCH_GL_ARB_instanced_arrays = false;
bool GARCH_GL_ARB_internalformat_query = false;
bool GARCH_GL_ARB_internalformat_query2 = false;
bool GARCH_GL_ARB_invalidate_subdata = false;
bool GARCH_GL_ARB_map_buffer_alignment = false;
bool GARCH_GL_ARB_map_buffer_range = false;
bool GARCH_GL_ARB_matrix_palette = false;
bool GARCH_GL_ARB_multi_bind = false;
bool GARCH_GL_ARB_multi_draw_indirect = false;
bool GARCH_GL_ARB_multisample = false;
bool GARCH_GL_ARB_multitexture = false;
bool GARCH_GL_ARB_occlusion_query = false;
bool GARCH_GL_ARB_occlusion_query2 = false;
bool GARCH_GL_ARB_parallel_shader_compile = false;
bool GARCH_GL_ARB_pipeline_statistics_query = false;
bool GARCH_GL_ARB_pixel_buffer_object = false;
bool GARCH_GL_ARB_point_parameters = false;
bool GARCH_GL_ARB_point_sprite = false;
bool GARCH_GL_ARB_polygon_offset_clamp = false;
bool GARCH_GL_ARB_post_depth_coverage = false;
bool GARCH_GL_ARB_program_interface_query = false;
bool GARCH_GL_ARB_provoking_vertex = false;
bool GARCH_GL_ARB_query_buffer_object = false;
bool GARCH_GL_ARB_robust_buffer_access_behavior = false;
bool GARCH_GL_ARB_robustness = false;
bool GARCH_GL_ARB_robustness_isolation = false;
bool GARCH_GL_ARB_sample_locations = false;
bool GARCH_GL_ARB_sample_shading = false;
bool GARCH_GL_ARB_sampler_objects = false;
bool GARCH_GL_ARB_seamless_cube_map = false;
bool GARCH_GL_ARB_seamless_cubemap_per_texture = false;
bool GARCH_GL_ARB_separate_shader_objects = false;
bool GARCH_GL_ARB_shader_atomic_counter_ops = false;
bool GARCH_GL_ARB_shader_atomic_counters = false;
bool GARCH_GL_ARB_shader_ballot = false;
bool GARCH_GL_ARB_shader_bit_encoding = false;
bool GARCH_GL_ARB_shader_clock = false;
bool GARCH_GL_ARB_shader_draw_parameters = false;
bool GARCH_GL_ARB_shader_group_vote = false;
bool GARCH_GL_ARB_shader_image_load_store = false;
bool GARCH_GL_ARB_shader_image_size = false;
bool GARCH_GL_ARB_shader_objects = false;
bool GARCH_GL_ARB_shader_precision = false;
bool GARCH_GL_ARB_shader_stencil_export = false;
bool GARCH_GL_ARB_shader_storage_buffer_object = false;
bool GARCH_GL_ARB_shader_subroutine = false;
bool GARCH_GL_ARB_shader_texture_image_samples = false;
bool GARCH_GL_ARB_shader_texture_lod = false;
bool GARCH_GL_ARB_shader_viewport_layer_array = false;
bool GARCH_GL_ARB_shading_language_100 = false;
bool GARCH_GL_ARB_shading_language_420pack = false;
bool GARCH_GL_ARB_shading_language_include = false;
bool GARCH_GL_ARB_shading_language_packing = false;
bool GARCH_GL_ARB_shadow = false;
bool GARCH_GL_ARB_shadow_ambient = false;
bool GARCH_GL_ARB_sparse_buffer = false;
bool GARCH_GL_ARB_sparse_texture = false;
bool GARCH_GL_ARB_sparse_texture2 = false;
bool GARCH_GL_ARB_sparse_texture_clamp = false;
bool GARCH_GL_ARB_spirv_extensions = false;
bool GARCH_GL_ARB_stencil_texturing = false;
bool GARCH_GL_ARB_sync = false;
bool GARCH_GL_ARB_tessellation_shader = false;
bool GARCH_GL_ARB_texture_barrier = false;
bool GARCH_GL_ARB_texture_border_clamp = false;
bool GARCH_GL_ARB_texture_buffer_object = false;
bool GARCH_GL_ARB_texture_buffer_object_rgb32 = false;
bool GARCH_GL_ARB_texture_buffer_range = false;
bool GARCH_GL_ARB_texture_compression = false;
bool GARCH_GL_ARB_texture_compression_bptc = false;
bool GARCH_GL_ARB_texture_compression_rgtc = false;
bool GARCH_GL_ARB_texture_cube_map = false;
bool GARCH_GL_ARB_texture_cube_map_array = false;
bool GARCH_GL_ARB_texture_env_add = false;
bool GARCH_GL_ARB_texture_env_combine = false;
bool GARCH_GL_ARB_texture_env_crossbar = false;
bool GARCH_GL_ARB_texture_env_dot3 = false;
bool GARCH_GL_ARB_texture_filter_anisotropic = false;
bool GARCH_GL_ARB_texture_filter_minmax = false;
bool GARCH_GL_ARB_texture_float = false;
bool GARCH_GL_ARB_texture_gather = false;
bool GARCH_GL_ARB_texture_mirror_clamp_to_edge = false;
bool GARCH_GL_ARB_texture_mirrored_repeat = false;
bool GARCH_GL_ARB_texture_multisample = false;
bool GARCH_GL_ARB_texture_non_power_of_two = false;
bool GARCH_GL_ARB_texture_query_levels = false;
bool GARCH_GL_ARB_texture_query_lod = false;
bool GARCH_GL_ARB_texture_rectangle = false;
bool GARCH_GL_ARB_texture_rg = false;
bool GARCH_GL_ARB_texture_rgb10_a2ui = false;
bool GARCH_GL_ARB_texture_stencil8 = false;
bool GARCH_GL_ARB_texture_storage = false;
bool GARCH_GL_ARB_texture_storage_multisample = false;
bool GARCH_GL_ARB_texture_swizzle = false;
bool GARCH_GL_ARB_texture_view = false;
bool GARCH_GL_ARB_timer_query = false;
bool GARCH_GL_ARB_transform_feedback2 = false;
bool GARCH_GL_ARB_transform_feedback3 = false;
bool GARCH_GL_ARB_transform_feedback_instanced = false;
bool GARCH_GL_ARB_transform_feedback_overflow_query = false;
bool GARCH_GL_ARB_transpose_matrix = false;
bool GARCH_GL_ARB_uniform_buffer_object = false;
bool GARCH_GL_ARB_vertex_array_bgra = false;
bool GARCH_GL_ARB_vertex_array_object = false;
bool GARCH_GL_ARB_vertex_attrib_64bit = false;
bool GARCH_GL_ARB_vertex_attrib_binding = false;
bool GARCH_GL_ARB_vertex_blend = false;
bool GARCH_GL_ARB_vertex_buffer_object = false;
bool GARCH_GL_ARB_vertex_program = false;
bool GARCH_GL_ARB_vertex_shader = false;
bool GARCH_GL_ARB_vertex_type_10f_11f_11f_rev = false;
bool GARCH_GL_ARB_vertex_type_2_10_10_10_rev = false;
bool GARCH_GL_ARB_viewport_array = false;
bool GARCH_GL_ARB_window_pos = false;
bool GARCH_GL_EXT_422_pixels = false;
bool GARCH_GL_EXT_EGL_image_storage = false;
bool GARCH_GL_EXT_EGL_sync = false;
bool GARCH_GL_EXT_abgr = false;
bool GARCH_GL_EXT_bgra = false;
bool GARCH_GL_EXT_bindable_uniform = false;
bool GARCH_GL_EXT_blend_color = false;
bool GARCH_GL_EXT_blend_equation_separate = false;
bool GARCH_GL_EXT_blend_func_separate = false;
bool GARCH_GL_EXT_blend_logic_op = false;
bool GARCH_GL_EXT_blend_minmax = false;
bool GARCH_GL_EXT_blend_subtract = false;
bool GARCH_GL_EXT_clip_volume_hint = false;
bool GARCH_GL_EXT_cmyka = false;
bool GARCH_GL_EXT_color_subtable = false;
bool GARCH_GL_EXT_compiled_vertex_array = false;
bool GARCH_GL_EXT_convolution = false;
bool GARCH_GL_EXT_coordinate_frame = false;
bool GARCH_GL_EXT_copy_texture = false;
bool GARCH_GL_EXT_cull_vertex = false;
bool GARCH_GL_EXT_debug_label = false;
bool GARCH_GL_EXT_debug_marker = false;
bool GARCH_GL_EXT_depth_bounds_test = false;
bool GARCH_GL_EXT_direct_state_access = false;
bool GARCH_GL_EXT_draw_buffers2 = false;
bool GARCH_GL_EXT_draw_instanced = false;
bool GARCH_GL_EXT_draw_range_elements = false;
bool GARCH_GL_EXT_external_buffer = false;
bool GARCH_GL_EXT_fog_coord = false;
bool GARCH_GL_EXT_framebuffer_blit = false;
bool GARCH_GL_EXT_framebuffer_multisample = false;
bool GARCH_GL_EXT_framebuffer_multisample_blit_scaled = false;
bool GARCH_GL_EXT_framebuffer_object = false;
bool GARCH_GL_EXT_framebuffer_sRGB = false;
bool GARCH_GL_EXT_geometry_shader4 = false;
bool GARCH_GL_EXT_gpu_program_parameters = false;
bool GARCH_GL_EXT_gpu_shader4 = false;
bool GARCH_GL_EXT_histogram = false;
bool GARCH_GL_EXT_index_array_formats = false;
bool GARCH_GL_EXT_index_func = false;
bool GARCH_GL_EXT_index_material = false;
bool GARCH_GL_EXT_index_texture = false;
bool GARCH_GL_EXT_light_texture = false;
bool GARCH_GL_EXT_memory_object = false;
bool GARCH_GL_EXT_memory_object_fd = false;
bool GARCH_GL_EXT_memory_object_win32 = false;
bool GARCH_GL_EXT_misc_attribute = false;
bool GARCH_GL_EXT_multi_draw_arrays = false;
bool GARCH_GL_EXT_multisample = false;
bool GARCH_GL_EXT_multiview_tessellation_geometry_shader = false;
bool GARCH_GL_EXT_multiview_texture_multisample = false;
bool GARCH_GL_EXT_multiview_timer_query = false;
bool GARCH_GL_EXT_packed_depth_stencil = false;
bool GARCH_GL_EXT_packed_float = false;
bool GARCH_GL_EXT_packed_pixels = false;
bool GARCH_GL_EXT_paletted_texture = false;
bool GARCH_GL_EXT_pixel_buffer_object = false;
bool GARCH_GL_EXT_pixel_transform = false;
bool GARCH_GL_EXT_pixel_transform_color_table = false;
bool GARCH_GL_EXT_point_parameters = false;
bool GARCH_GL_EXT_polygon_offset = false;
bool GARCH_GL_EXT_polygon_offset_clamp = false;
bool GARCH_GL_EXT_post_depth_coverage = false;
bool GARCH_GL_EXT_provoking_vertex = false;
bool GARCH_GL_EXT_raster_multisample = false;
bool GARCH_GL_EXT_rescale_normal = false;
bool GARCH_GL_EXT_semaphore = false;
bool GARCH_GL_EXT_semaphore_fd = false;
bool GARCH_GL_EXT_semaphore_win32 = false;
bool GARCH_GL_EXT_secondary_color = false;
bool GARCH_GL_EXT_separate_shader_objects = false;
bool GARCH_GL_EXT_separate_specular_color = false;
bool GARCH_GL_EXT_shader_framebuffer_fetch = false;
bool GARCH_GL_EXT_shader_framebuffer_fetch_non_coherent = false;
bool GARCH_GL_EXT_shader_image_load_formatted = false;
bool GARCH_GL_EXT_shader_image_load_store = false;
bool GARCH_GL_EXT_shader_integer_mix = false;
bool GARCH_GL_EXT_shadow_funcs = false;
bool GARCH_GL_EXT_shared_texture_palette = false;
bool GARCH_GL_EXT_sparse_texture2 = false;
bool GARCH_GL_EXT_stencil_clear_tag = false;
bool GARCH_GL_EXT_stencil_two_side = false;
bool GARCH_GL_EXT_stencil_wrap = false;
bool GARCH_GL_EXT_subtexture = false;
bool GARCH_GL_EXT_texture = false;
bool GARCH_GL_EXT_texture3D = false;
bool GARCH_GL_EXT_texture_array = false;
bool GARCH_GL_EXT_texture_buffer_object = false;
bool GARCH_GL_EXT_texture_compression_latc = false;
bool GARCH_GL_EXT_texture_compression_rgtc = false;
bool GARCH_GL_EXT_texture_compression_s3tc = false;
bool GARCH_GL_EXT_texture_cube_map = false;
bool GARCH_GL_EXT_texture_env_add = false;
bool GARCH_GL_EXT_texture_env_combine = false;
bool GARCH_GL_EXT_texture_env_dot3 = false;
bool GARCH_GL_EXT_texture_filter_anisotropic = false;
bool GARCH_GL_EXT_texture_filter_minmax = false;
bool GARCH_GL_EXT_texture_integer = false;
bool GARCH_GL_EXT_texture_lod_bias = false;
bool GARCH_GL_EXT_texture_mirror_clamp = false;
bool GARCH_GL_EXT_texture_object = false;
bool GARCH_GL_EXT_texture_perturb_normal = false;
bool GARCH_GL_EXT_texture_sRGB = false;
bool GARCH_GL_EXT_texture_sRGB_R8 = false;
bool GARCH_GL_EXT_texture_sRGB_decode = false;
bool GARCH_GL_EXT_texture_shared_exponent = false;
bool GARCH_GL_EXT_texture_snorm = false;
bool GARCH_GL_EXT_texture_swizzle = false;
bool GARCH_GL_NV_timeline_semaphore = false;
bool GARCH_GL_EXT_timer_query = false;
bool GARCH_GL_EXT_transform_feedback = false;
bool GARCH_GL_EXT_vertex_array = false;
bool GARCH_GL_EXT_vertex_array_bgra = false;
bool GARCH_GL_EXT_vertex_attrib_64bit = false;
bool GARCH_GL_EXT_vertex_shader = false;
bool GARCH_GL_EXT_vertex_weighting = false;
bool GARCH_GL_EXT_win32_keyed_mutex = false;
bool GARCH_GL_EXT_window_rectangles = false;
bool GARCH_GL_EXT_x11_sync_object = false;
bool GARCH_GL_INTEL_conservative_rasterization = false;
bool GARCH_GL_INTEL_fragment_shader_ordering = false;
bool GARCH_GL_INTEL_framebuffer_CMAA = false;
bool GARCH_GL_INTEL_map_texture = false;
bool GARCH_GL_INTEL_blackhole_render = false;
bool GARCH_GL_INTEL_parallel_arrays = false;
bool GARCH_GL_INTEL_performance_query = false;
bool GARCH_GL_KHR_blend_equation_advanced = false;
bool GARCH_GL_KHR_blend_equation_advanced_coherent = false;
bool GARCH_GL_KHR_context_flush_control = false;
bool GARCH_GL_KHR_debug = false;
bool GARCH_GL_KHR_no_error = false;
bool GARCH_GL_KHR_robust_buffer_access_behavior = false;
bool GARCH_GL_KHR_robustness = false;
bool GARCH_GL_KHR_shader_subgroup = false;
bool GARCH_GL_KHR_texture_compression_astc_hdr = false;
bool GARCH_GL_KHR_texture_compression_astc_ldr = false;
bool GARCH_GL_KHR_texture_compression_astc_sliced_3d = false;
bool GARCH_GL_KHR_parallel_shader_compile = false;
bool GARCH_GL_NVX_blend_equation_advanced_multi_draw_buffers = false;
bool GARCH_GL_NVX_conditional_render = false;
bool GARCH_GL_NVX_gpu_memory_info = false;
bool GARCH_GL_NVX_linked_gpu_multicast = false;
bool GARCH_GL_NV_alpha_to_coverage_dither_control = false;
bool GARCH_GL_NV_bindless_multi_draw_indirect = false;
bool GARCH_GL_NV_bindless_multi_draw_indirect_count = false;
bool GARCH_GL_NV_bindless_texture = false;
bool GARCH_GL_NV_blend_equation_advanced = false;
bool GARCH_GL_NV_blend_equation_advanced_coherent = false;
bool GARCH_GL_NV_blend_minmax_factor = false;
bool GARCH_GL_NV_blend_square = false;
bool GARCH_GL_NV_clip_space_w_scaling = false;
bool GARCH_GL_NV_command_list = false;
bool GARCH_GL_NV_compute_program5 = false;
bool GARCH_GL_NV_compute_shader_derivatives = false;
bool GARCH_GL_NV_conditional_render = false;
bool GARCH_GL_NV_conservative_raster = false;
bool GARCH_GL_NV_conservative_raster_dilate = false;
bool GARCH_GL_NV_conservative_raster_pre_snap = false;
bool GARCH_GL_NV_conservative_raster_pre_snap_triangles = false;
bool GARCH_GL_NV_conservative_raster_underestimation = false;
bool GARCH_GL_NV_copy_depth_to_color = false;
bool GARCH_GL_NV_copy_image = false;
bool GARCH_GL_NV_deep_texture3D = false;
bool GARCH_GL_NV_depth_buffer_float = false;
bool GARCH_GL_NV_depth_clamp = false;
bool GARCH_GL_NV_draw_texture = false;
bool GARCH_GL_NV_draw_vulkan_image = false;
bool GARCH_GL_NV_evaluators = false;
bool GARCH_GL_NV_explicit_multisample = false;
bool GARCH_GL_NV_fence = false;
bool GARCH_GL_NV_fill_rectangle = false;
bool GARCH_GL_NV_float_buffer = false;
bool GARCH_GL_NV_fog_distance = false;
bool GARCH_GL_NV_fragment_coverage_to_color = false;
bool GARCH_GL_NV_fragment_program = false;
bool GARCH_GL_NV_fragment_program2 = false;
bool GARCH_GL_NV_fragment_program4 = false;
bool GARCH_GL_NV_fragment_program_option = false;
bool GARCH_GL_NV_fragment_shader_barycentric = false;
bool GARCH_GL_NV_fragment_shader_interlock = false;
bool GARCH_GL_NV_framebuffer_mixed_samples = false;
bool GARCH_GL_NV_framebuffer_multisample_coverage = false;
bool GARCH_GL_NV_geometry_program4 = false;
bool GARCH_GL_NV_geometry_shader4 = false;
bool GARCH_GL_NV_geometry_shader_passthrough = false;
bool GARCH_GL_NV_gpu_program4 = false;
bool GARCH_GL_NV_gpu_program5 = false;
bool GARCH_GL_NV_gpu_program5_mem_extended = false;
bool GARCH_GL_NV_gpu_shader5 = false;
bool GARCH_GL_NV_half_float = false;
bool GARCH_GL_NV_internalformat_sample_query = false;
bool GARCH_GL_NV_light_max_exponent = false;
bool GARCH_GL_NV_gpu_multicast = false;
bool GARCH_GL_NVX_gpu_multicast2 = false;
bool GARCH_GL_NVX_progress_fence = false;
bool GARCH_GL_NV_memory_attachment = false;
bool GARCH_GL_NV_memory_object_sparse = false;
bool GARCH_GL_NV_mesh_shader = false;
bool GARCH_GL_NV_multisample_coverage = false;
bool GARCH_GL_NV_multisample_filter_hint = false;
bool GARCH_GL_NV_occlusion_query = false;
bool GARCH_GL_NV_packed_depth_stencil = false;
bool GARCH_GL_NV_parameter_buffer_object = false;
bool GARCH_GL_NV_parameter_buffer_object2 = false;
bool GARCH_GL_NV_path_rendering = false;
bool GARCH_GL_NV_path_rendering_shared_edge = false;
bool GARCH_GL_NV_pixel_data_range = false;
bool GARCH_GL_NV_point_sprite = false;
bool GARCH_GL_NV_present_video = false;
bool GARCH_GL_NV_primitive_restart = false;
bool GARCH_GL_NV_query_resource = false;
bool GARCH_GL_NV_query_resource_tag = false;
bool GARCH_GL_NV_register_combiners = false;
bool GARCH_GL_NV_register_combiners2 = false;
bool GARCH_GL_NV_representative_fragment_test = false;
bool GARCH_GL_NV_robustness_video_memory_purge = false;
bool GARCH_GL_NV_sample_locations = false;
bool GARCH_GL_NV_sample_mask_override_coverage = false;
bool GARCH_GL_NV_scissor_exclusive = false;
bool GARCH_GL_NV_shader_atomic_counters = false;
bool GARCH_GL_NV_shader_atomic_float = false;
bool GARCH_GL_NV_shader_atomic_float64 = false;
bool GARCH_GL_NV_shader_atomic_fp16_vector = false;
bool GARCH_GL_NV_shader_atomic_int64 = false;
bool GARCH_GL_NV_shader_buffer_load = false;
bool GARCH_GL_NV_shader_buffer_store = false;
bool GARCH_GL_NV_shader_storage_buffer_object = false;
bool GARCH_GL_NV_shader_subgroup_partitioned = false;
bool GARCH_GL_NV_shader_texture_footprint = false;
bool GARCH_GL_NV_shader_thread_group = false;
bool GARCH_GL_NV_shader_thread_shuffle = false;
bool GARCH_GL_NV_shading_rate_image = false;
bool GARCH_GL_NV_stereo_view_rendering = false;
bool GARCH_GL_NV_tessellation_program5 = false;
bool GARCH_GL_NV_texgen_emboss = false;
bool GARCH_GL_NV_texgen_reflection = false;
bool GARCH_GL_NV_texture_barrier = false;
bool GARCH_GL_NV_texture_compression_vtc = false;
bool GARCH_GL_NV_texture_env_combine4 = false;
bool GARCH_GL_NV_texture_expand_normal = false;
bool GARCH_GL_NV_texture_multisample = false;
bool GARCH_GL_NV_texture_rectangle = false;
bool GARCH_GL_NV_texture_rectangle_compressed = false;
bool GARCH_GL_NV_texture_shader = false;
bool GARCH_GL_NV_texture_shader2 = false;
bool GARCH_GL_NV_texture_shader3 = false;
bool GARCH_GL_NV_transform_feedback = false;
bool GARCH_GL_NV_transform_feedback2 = false;
bool GARCH_GL_NV_uniform_buffer_unified_memory = false;
bool GARCH_GL_NV_vdpau_interop = false;
bool GARCH_GL_NV_vdpau_interop2 = false;
bool GARCH_GL_NV_vertex_array_range = false;
bool GARCH_GL_NV_vertex_array_range2 = false;
bool GARCH_GL_NV_vertex_attrib_integer_64bit = false;
bool GARCH_GL_NV_vertex_buffer_unified_memory = false;
bool GARCH_GL_NV_vertex_program = false;
bool GARCH_GL_NV_vertex_program1_1 = false;
bool GARCH_GL_NV_vertex_program2 = false;
bool GARCH_GL_NV_vertex_program2_option = false;
bool GARCH_GL_NV_vertex_program3 = false;
bool GARCH_GL_NV_vertex_program4 = false;
bool GARCH_GL_NV_video_capture = false;
bool GARCH_GL_NV_viewport_array2 = false;
bool GARCH_GL_NV_viewport_swizzle = false;
bool GARCH_GL_EXT_texture_shadow_lod = false;

PFNGLACCUMPROC glAccum = NULL;
PFNGLACTIVEPROGRAMEXTPROC glActiveProgramEXT = NULL;
PFNGLACTIVESHADERPROGRAMPROC glActiveShaderProgram = NULL;
PFNGLACTIVESHADERPROGRAMEXTPROC glActiveShaderProgramEXT = NULL;
PFNGLACTIVESTENCILFACEEXTPROC glActiveStencilFaceEXT = NULL;
PFNGLACTIVETEXTUREPROC glActiveTexture = NULL;
PFNGLACTIVETEXTUREARBPROC glActiveTextureARB = NULL;
PFNGLACTIVEVARYINGNVPROC glActiveVaryingNV = NULL;
PFNGLALPHAFUNCPROC glAlphaFunc = NULL;
PFNGLALPHATOCOVERAGEDITHERCONTROLNVPROC glAlphaToCoverageDitherControlNV = NULL;
PFNGLAPPLYFRAMEBUFFERATTACHMENTCMAAINTELPROC glApplyFramebufferAttachmentCMAAINTEL = NULL;
PFNGLAPPLYTEXTUREEXTPROC glApplyTextureEXT = NULL;
PFNGLACQUIREKEYEDMUTEXWIN32EXTPROC glAcquireKeyedMutexWin32EXT = NULL;
PFNGLAREPROGRAMSRESIDENTNVPROC glAreProgramsResidentNV = NULL;
PFNGLARETEXTURESRESIDENTPROC glAreTexturesResident = NULL;
PFNGLARETEXTURESRESIDENTEXTPROC glAreTexturesResidentEXT = NULL;
PFNGLARRAYELEMENTPROC glArrayElement = NULL;
PFNGLARRAYELEMENTEXTPROC glArrayElementEXT = NULL;
PFNGLASYNCCOPYBUFFERSUBDATANVXPROC glAsyncCopyBufferSubDataNVX = NULL;
PFNGLASYNCCOPYIMAGESUBDATANVXPROC glAsyncCopyImageSubDataNVX = NULL;
PFNGLATTACHOBJECTARBPROC glAttachObjectARB = NULL;
PFNGLATTACHSHADERPROC glAttachShader = NULL;
PFNGLBEGINPROC glBegin = NULL;
PFNGLBEGINCONDITIONALRENDERPROC glBeginConditionalRender = NULL;
PFNGLBEGINCONDITIONALRENDERNVPROC glBeginConditionalRenderNV = NULL;
PFNGLBEGINCONDITIONALRENDERNVXPROC glBeginConditionalRenderNVX = NULL;
PFNGLBEGINOCCLUSIONQUERYNVPROC glBeginOcclusionQueryNV = NULL;
PFNGLBEGINPERFMONITORAMDPROC glBeginPerfMonitorAMD = NULL;
PFNGLBEGINPERFQUERYINTELPROC glBeginPerfQueryINTEL = NULL;
PFNGLBEGINQUERYPROC glBeginQuery = NULL;
PFNGLBEGINQUERYARBPROC glBeginQueryARB = NULL;
PFNGLBEGINQUERYINDEXEDPROC glBeginQueryIndexed = NULL;
PFNGLBEGINTRANSFORMFEEDBACKPROC glBeginTransformFeedback = NULL;
PFNGLBEGINTRANSFORMFEEDBACKEXTPROC glBeginTransformFeedbackEXT = NULL;
PFNGLBEGINTRANSFORMFEEDBACKNVPROC glBeginTransformFeedbackNV = NULL;
PFNGLBEGINVERTEXSHADEREXTPROC glBeginVertexShaderEXT = NULL;
PFNGLBEGINVIDEOCAPTURENVPROC glBeginVideoCaptureNV = NULL;
PFNGLBINDATTRIBLOCATIONPROC glBindAttribLocation = NULL;
PFNGLBINDATTRIBLOCATIONARBPROC glBindAttribLocationARB = NULL;
PFNGLBINDBUFFERPROC glBindBuffer = NULL;
PFNGLBINDBUFFERARBPROC glBindBufferARB = NULL;
PFNGLBINDBUFFERBASEPROC glBindBufferBase = NULL;
PFNGLBINDBUFFERBASEEXTPROC glBindBufferBaseEXT = NULL;
PFNGLBINDBUFFERBASENVPROC glBindBufferBaseNV = NULL;
PFNGLBINDBUFFEROFFSETEXTPROC glBindBufferOffsetEXT = NULL;
PFNGLBINDBUFFEROFFSETNVPROC glBindBufferOffsetNV = NULL;
PFNGLBINDBUFFERRANGEPROC glBindBufferRange = NULL;
PFNGLBINDBUFFERRANGEEXTPROC glBindBufferRangeEXT = NULL;
PFNGLBINDBUFFERRANGENVPROC glBindBufferRangeNV = NULL;
PFNGLBINDBUFFERSBASEPROC glBindBuffersBase = NULL;
PFNGLBINDBUFFERSRANGEPROC glBindBuffersRange = NULL;
PFNGLBINDFRAGDATALOCATIONPROC glBindFragDataLocation = NULL;
PFNGLBINDFRAGDATALOCATIONEXTPROC glBindFragDataLocationEXT = NULL;
PFNGLBINDFRAGDATALOCATIONINDEXEDPROC glBindFragDataLocationIndexed = NULL;
PFNGLBINDFRAMEBUFFERPROC glBindFramebuffer = NULL;
PFNGLBINDFRAMEBUFFEREXTPROC glBindFramebufferEXT = NULL;
PFNGLBINDIMAGETEXTUREPROC glBindImageTexture = NULL;
PFNGLBINDIMAGETEXTUREEXTPROC glBindImageTextureEXT = NULL;
PFNGLBINDIMAGETEXTURESPROC glBindImageTextures = NULL;
PFNGLBINDLIGHTPARAMETEREXTPROC glBindLightParameterEXT = NULL;
PFNGLBINDMATERIALPARAMETEREXTPROC glBindMaterialParameterEXT = NULL;
PFNGLBINDMULTITEXTUREEXTPROC glBindMultiTextureEXT = NULL;
PFNGLBINDPARAMETEREXTPROC glBindParameterEXT = NULL;
PFNGLBINDPROGRAMARBPROC glBindProgramARB = NULL;
PFNGLBINDPROGRAMNVPROC glBindProgramNV = NULL;
PFNGLBINDPROGRAMPIPELINEPROC glBindProgramPipeline = NULL;
PFNGLBINDPROGRAMPIPELINEEXTPROC glBindProgramPipelineEXT = NULL;
PFNGLBINDRENDERBUFFERPROC glBindRenderbuffer = NULL;
PFNGLBINDRENDERBUFFEREXTPROC glBindRenderbufferEXT = NULL;
PFNGLBINDSAMPLERPROC glBindSampler = NULL;
PFNGLBINDSAMPLERSPROC glBindSamplers = NULL;
PFNGLBINDSHADINGRATEIMAGENVPROC glBindShadingRateImageNV = NULL;
PFNGLBINDTEXGENPARAMETEREXTPROC glBindTexGenParameterEXT = NULL;
PFNGLBINDTEXTUREPROC glBindTexture = NULL;
PFNGLBINDTEXTUREEXTPROC glBindTextureEXT = NULL;
PFNGLBINDTEXTUREUNITPROC glBindTextureUnit = NULL;
PFNGLBINDTEXTUREUNITPARAMETEREXTPROC glBindTextureUnitParameterEXT = NULL;
PFNGLBINDTEXTURESPROC glBindTextures = NULL;
PFNGLBINDTRANSFORMFEEDBACKPROC glBindTransformFeedback = NULL;
PFNGLBINDTRANSFORMFEEDBACKNVPROC glBindTransformFeedbackNV = NULL;
PFNGLBINDVERTEXARRAYPROC glBindVertexArray = NULL;
PFNGLBINDVERTEXARRAYAPPLEPROC glBindVertexArrayAPPLE = NULL;
PFNGLBINDVERTEXBUFFERPROC glBindVertexBuffer = NULL;
PFNGLBINDVERTEXBUFFERSPROC glBindVertexBuffers = NULL;
PFNGLBINDVERTEXSHADEREXTPROC glBindVertexShaderEXT = NULL;
PFNGLBINDVIDEOCAPTURESTREAMBUFFERNVPROC glBindVideoCaptureStreamBufferNV = NULL;
PFNGLBINDVIDEOCAPTURESTREAMTEXTURENVPROC glBindVideoCaptureStreamTextureNV = NULL;
PFNGLBINORMAL3BEXTPROC glBinormal3bEXT = NULL;
PFNGLBINORMAL3BVEXTPROC glBinormal3bvEXT = NULL;
PFNGLBINORMAL3DEXTPROC glBinormal3dEXT = NULL;
PFNGLBINORMAL3DVEXTPROC glBinormal3dvEXT = NULL;
PFNGLBINORMAL3FEXTPROC glBinormal3fEXT = NULL;
PFNGLBINORMAL3FVEXTPROC glBinormal3fvEXT = NULL;
PFNGLBINORMAL3IEXTPROC glBinormal3iEXT = NULL;
PFNGLBINORMAL3IVEXTPROC glBinormal3ivEXT = NULL;
PFNGLBINORMAL3SEXTPROC glBinormal3sEXT = NULL;
PFNGLBINORMAL3SVEXTPROC glBinormal3svEXT = NULL;
PFNGLBINORMALPOINTEREXTPROC glBinormalPointerEXT = NULL;
PFNGLBITMAPPROC glBitmap = NULL;
PFNGLBLENDBARRIERKHRPROC glBlendBarrierKHR = NULL;
PFNGLBLENDBARRIERNVPROC glBlendBarrierNV = NULL;
PFNGLBLENDCOLORPROC glBlendColor = NULL;
PFNGLBLENDCOLOREXTPROC glBlendColorEXT = NULL;
PFNGLBLENDEQUATIONPROC glBlendEquation = NULL;
PFNGLBLENDEQUATIONEXTPROC glBlendEquationEXT = NULL;
PFNGLBLENDEQUATIONINDEXEDAMDPROC glBlendEquationIndexedAMD = NULL;
PFNGLBLENDEQUATIONSEPARATEPROC glBlendEquationSeparate = NULL;
PFNGLBLENDEQUATIONSEPARATEEXTPROC glBlendEquationSeparateEXT = NULL;
PFNGLBLENDEQUATIONSEPARATEINDEXEDAMDPROC glBlendEquationSeparateIndexedAMD = NULL;
PFNGLBLENDEQUATIONSEPARATEIPROC glBlendEquationSeparatei = NULL;
PFNGLBLENDEQUATIONSEPARATEIARBPROC glBlendEquationSeparateiARB = NULL;
PFNGLBLENDEQUATIONIPROC glBlendEquationi = NULL;
PFNGLBLENDEQUATIONIARBPROC glBlendEquationiARB = NULL;
PFNGLBLENDFUNCPROC glBlendFunc = NULL;
PFNGLBLENDFUNCINDEXEDAMDPROC glBlendFuncIndexedAMD = NULL;
PFNGLBLENDFUNCSEPARATEPROC glBlendFuncSeparate = NULL;
PFNGLBLENDFUNCSEPARATEEXTPROC glBlendFuncSeparateEXT = NULL;
PFNGLBLENDFUNCSEPARATEINDEXEDAMDPROC glBlendFuncSeparateIndexedAMD = NULL;
PFNGLBLENDFUNCSEPARATEIPROC glBlendFuncSeparatei = NULL;
PFNGLBLENDFUNCSEPARATEIARBPROC glBlendFuncSeparateiARB = NULL;
PFNGLBLENDFUNCIPROC glBlendFunci = NULL;
PFNGLBLENDFUNCIARBPROC glBlendFunciARB = NULL;
PFNGLBLENDPARAMETERINVPROC glBlendParameteriNV = NULL;
PFNGLBLITFRAMEBUFFERPROC glBlitFramebuffer = NULL;
PFNGLBLITFRAMEBUFFEREXTPROC glBlitFramebufferEXT = NULL;
PFNGLBLITNAMEDFRAMEBUFFERPROC glBlitNamedFramebuffer = NULL;
PFNGLBUFFERADDRESSRANGENVPROC glBufferAddressRangeNV = NULL;
PFNGLBUFFERATTACHMEMORYNVPROC glBufferAttachMemoryNV = NULL;
PFNGLBUFFERDATAPROC glBufferData = NULL;
PFNGLBUFFERDATAARBPROC glBufferDataARB = NULL;
PFNGLBUFFERPAGECOMMITMENTARBPROC glBufferPageCommitmentARB = NULL;
PFNGLBUFFERPAGECOMMITMENTMEMNVPROC glBufferPageCommitmentMemNV = NULL;
PFNGLBUFFERPARAMETERIAPPLEPROC glBufferParameteriAPPLE = NULL;
PFNGLBUFFERSTORAGEPROC glBufferStorage = NULL;
PFNGLBUFFERSTORAGEEXTERNALEXTPROC glBufferStorageExternalEXT = NULL;
PFNGLBUFFERSTORAGEMEMEXTPROC glBufferStorageMemEXT = NULL;
PFNGLBUFFERSUBDATAPROC glBufferSubData = NULL;
PFNGLBUFFERSUBDATAARBPROC glBufferSubDataARB = NULL;
PFNGLCALLCOMMANDLISTNVPROC glCallCommandListNV = NULL;
PFNGLCALLLISTPROC glCallList = NULL;
PFNGLCALLLISTSPROC glCallLists = NULL;
PFNGLCHECKFRAMEBUFFERSTATUSPROC glCheckFramebufferStatus = NULL;
PFNGLCHECKFRAMEBUFFERSTATUSEXTPROC glCheckFramebufferStatusEXT = NULL;
PFNGLCHECKNAMEDFRAMEBUFFERSTATUSPROC glCheckNamedFramebufferStatus = NULL;
PFNGLCHECKNAMEDFRAMEBUFFERSTATUSEXTPROC glCheckNamedFramebufferStatusEXT = NULL;
PFNGLCLAMPCOLORPROC glClampColor = NULL;
PFNGLCLAMPCOLORARBPROC glClampColorARB = NULL;
PFNGLCLEARPROC glClear = NULL;
PFNGLCLEARACCUMPROC glClearAccum = NULL;
PFNGLCLEARBUFFERDATAPROC glClearBufferData = NULL;
PFNGLCLEARBUFFERSUBDATAPROC glClearBufferSubData = NULL;
PFNGLCLEARBUFFERFIPROC glClearBufferfi = NULL;
PFNGLCLEARBUFFERFVPROC glClearBufferfv = NULL;
PFNGLCLEARBUFFERIVPROC glClearBufferiv = NULL;
PFNGLCLEARBUFFERUIVPROC glClearBufferuiv = NULL;
PFNGLCLEARCOLORPROC glClearColor = NULL;
PFNGLCLEARCOLORIIEXTPROC glClearColorIiEXT = NULL;
PFNGLCLEARCOLORIUIEXTPROC glClearColorIuiEXT = NULL;
PFNGLCLEARDEPTHPROC glClearDepth = NULL;
PFNGLCLEARDEPTHDNVPROC glClearDepthdNV = NULL;
PFNGLCLEARDEPTHFPROC glClearDepthf = NULL;
PFNGLCLEARINDEXPROC glClearIndex = NULL;
PFNGLCLEARNAMEDBUFFERDATAPROC glClearNamedBufferData = NULL;
PFNGLCLEARNAMEDBUFFERDATAEXTPROC glClearNamedBufferDataEXT = NULL;
PFNGLCLEARNAMEDBUFFERSUBDATAPROC glClearNamedBufferSubData = NULL;
PFNGLCLEARNAMEDBUFFERSUBDATAEXTPROC glClearNamedBufferSubDataEXT = NULL;
PFNGLCLEARNAMEDFRAMEBUFFERFIPROC glClearNamedFramebufferfi = NULL;
PFNGLCLEARNAMEDFRAMEBUFFERFVPROC glClearNamedFramebufferfv = NULL;
PFNGLCLEARNAMEDFRAMEBUFFERIVPROC glClearNamedFramebufferiv = NULL;
PFNGLCLEARNAMEDFRAMEBUFFERUIVPROC glClearNamedFramebufferuiv = NULL;
PFNGLCLEARSTENCILPROC glClearStencil = NULL;
PFNGLCLEARTEXIMAGEPROC glClearTexImage = NULL;
PFNGLCLEARTEXSUBIMAGEPROC glClearTexSubImage = NULL;
PFNGLCLIENTACTIVETEXTUREPROC glClientActiveTexture = NULL;
PFNGLCLIENTACTIVETEXTUREARBPROC glClientActiveTextureARB = NULL;
PFNGLCLIENTATTRIBDEFAULTEXTPROC glClientAttribDefaultEXT = NULL;
PFNGLCLIENTWAITSEMAPHOREUI64NVXPROC glClientWaitSemaphoreui64NVX = NULL;
PFNGLCLIENTWAITSYNCPROC glClientWaitSync = NULL;
PFNGLCLIPCONTROLPROC glClipControl = NULL;
PFNGLCLIPPLANEPROC glClipPlane = NULL;
PFNGLCOLOR3BPROC glColor3b = NULL;
PFNGLCOLOR3BVPROC glColor3bv = NULL;
PFNGLCOLOR3DPROC glColor3d = NULL;
PFNGLCOLOR3DVPROC glColor3dv = NULL;
PFNGLCOLOR3FPROC glColor3f = NULL;
PFNGLCOLOR3FVPROC glColor3fv = NULL;
PFNGLCOLOR3HNVPROC glColor3hNV = NULL;
PFNGLCOLOR3HVNVPROC glColor3hvNV = NULL;
PFNGLCOLOR3IPROC glColor3i = NULL;
PFNGLCOLOR3IVPROC glColor3iv = NULL;
PFNGLCOLOR3SPROC glColor3s = NULL;
PFNGLCOLOR3SVPROC glColor3sv = NULL;
PFNGLCOLOR3UBPROC glColor3ub = NULL;
PFNGLCOLOR3UBVPROC glColor3ubv = NULL;
PFNGLCOLOR3UIPROC glColor3ui = NULL;
PFNGLCOLOR3UIVPROC glColor3uiv = NULL;
PFNGLCOLOR3USPROC glColor3us = NULL;
PFNGLCOLOR3USVPROC glColor3usv = NULL;
PFNGLCOLOR4BPROC glColor4b = NULL;
PFNGLCOLOR4BVPROC glColor4bv = NULL;
PFNGLCOLOR4DPROC glColor4d = NULL;
PFNGLCOLOR4DVPROC glColor4dv = NULL;
PFNGLCOLOR4FPROC glColor4f = NULL;
PFNGLCOLOR4FVPROC glColor4fv = NULL;
PFNGLCOLOR4HNVPROC glColor4hNV = NULL;
PFNGLCOLOR4HVNVPROC glColor4hvNV = NULL;
PFNGLCOLOR4IPROC glColor4i = NULL;
PFNGLCOLOR4IVPROC glColor4iv = NULL;
PFNGLCOLOR4SPROC glColor4s = NULL;
PFNGLCOLOR4SVPROC glColor4sv = NULL;
PFNGLCOLOR4UBPROC glColor4ub = NULL;
PFNGLCOLOR4UBVPROC glColor4ubv = NULL;
PFNGLCOLOR4UIPROC glColor4ui = NULL;
PFNGLCOLOR4UIVPROC glColor4uiv = NULL;
PFNGLCOLOR4USPROC glColor4us = NULL;
PFNGLCOLOR4USVPROC glColor4usv = NULL;
PFNGLCOLORFORMATNVPROC glColorFormatNV = NULL;
PFNGLCOLORMASKPROC glColorMask = NULL;
PFNGLCOLORMASKINDEXEDEXTPROC glColorMaskIndexedEXT = NULL;
PFNGLCOLORMASKIPROC glColorMaski = NULL;
PFNGLCOLORMATERIALPROC glColorMaterial = NULL;
PFNGLCOLORP3UIPROC glColorP3ui = NULL;
PFNGLCOLORP3UIVPROC glColorP3uiv = NULL;
PFNGLCOLORP4UIPROC glColorP4ui = NULL;
PFNGLCOLORP4UIVPROC glColorP4uiv = NULL;
PFNGLCOLORPOINTERPROC glColorPointer = NULL;
PFNGLCOLORPOINTEREXTPROC glColorPointerEXT = NULL;
PFNGLCOLORPOINTERVINTELPROC glColorPointervINTEL = NULL;
PFNGLCOLORSUBTABLEPROC glColorSubTable = NULL;
PFNGLCOLORSUBTABLEEXTPROC glColorSubTableEXT = NULL;
PFNGLCOLORTABLEPROC glColorTable = NULL;
PFNGLCOLORTABLEEXTPROC glColorTableEXT = NULL;
PFNGLCOLORTABLEPARAMETERFVPROC glColorTableParameterfv = NULL;
PFNGLCOLORTABLEPARAMETERIVPROC glColorTableParameteriv = NULL;
PFNGLCOMBINERINPUTNVPROC glCombinerInputNV = NULL;
PFNGLCOMBINEROUTPUTNVPROC glCombinerOutputNV = NULL;
PFNGLCOMBINERPARAMETERFNVPROC glCombinerParameterfNV = NULL;
PFNGLCOMBINERPARAMETERFVNVPROC glCombinerParameterfvNV = NULL;
PFNGLCOMBINERPARAMETERINVPROC glCombinerParameteriNV = NULL;
PFNGLCOMBINERPARAMETERIVNVPROC glCombinerParameterivNV = NULL;
PFNGLCOMBINERSTAGEPARAMETERFVNVPROC glCombinerStageParameterfvNV = NULL;
PFNGLCOMMANDLISTSEGMENTSNVPROC glCommandListSegmentsNV = NULL;
PFNGLCOMPILECOMMANDLISTNVPROC glCompileCommandListNV = NULL;
PFNGLCOMPILESHADERPROC glCompileShader = NULL;
PFNGLCOMPILESHADERARBPROC glCompileShaderARB = NULL;
PFNGLCOMPILESHADERINCLUDEARBPROC glCompileShaderIncludeARB = NULL;
PFNGLCOMPRESSEDMULTITEXIMAGE1DEXTPROC glCompressedMultiTexImage1DEXT = NULL;
PFNGLCOMPRESSEDMULTITEXIMAGE2DEXTPROC glCompressedMultiTexImage2DEXT = NULL;
PFNGLCOMPRESSEDMULTITEXIMAGE3DEXTPROC glCompressedMultiTexImage3DEXT = NULL;
PFNGLCOMPRESSEDMULTITEXSUBIMAGE1DEXTPROC glCompressedMultiTexSubImage1DEXT = NULL;
PFNGLCOMPRESSEDMULTITEXSUBIMAGE2DEXTPROC glCompressedMultiTexSubImage2DEXT = NULL;
PFNGLCOMPRESSEDMULTITEXSUBIMAGE3DEXTPROC glCompressedMultiTexSubImage3DEXT = NULL;
PFNGLCOMPRESSEDTEXIMAGE1DPROC glCompressedTexImage1D = NULL;
PFNGLCOMPRESSEDTEXIMAGE1DARBPROC glCompressedTexImage1DARB = NULL;
PFNGLCOMPRESSEDTEXIMAGE2DPROC glCompressedTexImage2D = NULL;
PFNGLCOMPRESSEDTEXIMAGE2DARBPROC glCompressedTexImage2DARB = NULL;
PFNGLCOMPRESSEDTEXIMAGE3DPROC glCompressedTexImage3D = NULL;
PFNGLCOMPRESSEDTEXIMAGE3DARBPROC glCompressedTexImage3DARB = NULL;
PFNGLCOMPRESSEDTEXSUBIMAGE1DPROC glCompressedTexSubImage1D = NULL;
PFNGLCOMPRESSEDTEXSUBIMAGE1DARBPROC glCompressedTexSubImage1DARB = NULL;
PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC glCompressedTexSubImage2D = NULL;
PFNGLCOMPRESSEDTEXSUBIMAGE2DARBPROC glCompressedTexSubImage2DARB = NULL;
PFNGLCOMPRESSEDTEXSUBIMAGE3DPROC glCompressedTexSubImage3D = NULL;
PFNGLCOMPRESSEDTEXSUBIMAGE3DARBPROC glCompressedTexSubImage3DARB = NULL;
PFNGLCOMPRESSEDTEXTUREIMAGE1DEXTPROC glCompressedTextureImage1DEXT = NULL;
PFNGLCOMPRESSEDTEXTUREIMAGE2DEXTPROC glCompressedTextureImage2DEXT = NULL;
PFNGLCOMPRESSEDTEXTUREIMAGE3DEXTPROC glCompressedTextureImage3DEXT = NULL;
PFNGLCOMPRESSEDTEXTURESUBIMAGE1DPROC glCompressedTextureSubImage1D = NULL;
PFNGLCOMPRESSEDTEXTURESUBIMAGE1DEXTPROC glCompressedTextureSubImage1DEXT = NULL;
PFNGLCOMPRESSEDTEXTURESUBIMAGE2DPROC glCompressedTextureSubImage2D = NULL;
PFNGLCOMPRESSEDTEXTURESUBIMAGE2DEXTPROC glCompressedTextureSubImage2DEXT = NULL;
PFNGLCOMPRESSEDTEXTURESUBIMAGE3DPROC glCompressedTextureSubImage3D = NULL;
PFNGLCOMPRESSEDTEXTURESUBIMAGE3DEXTPROC glCompressedTextureSubImage3DEXT = NULL;
PFNGLCONSERVATIVERASTERPARAMETERFNVPROC glConservativeRasterParameterfNV = NULL;
PFNGLCONSERVATIVERASTERPARAMETERINVPROC glConservativeRasterParameteriNV = NULL;
PFNGLCONVOLUTIONFILTER1DPROC glConvolutionFilter1D = NULL;
PFNGLCONVOLUTIONFILTER1DEXTPROC glConvolutionFilter1DEXT = NULL;
PFNGLCONVOLUTIONFILTER2DPROC glConvolutionFilter2D = NULL;
PFNGLCONVOLUTIONFILTER2DEXTPROC glConvolutionFilter2DEXT = NULL;
PFNGLCONVOLUTIONPARAMETERFPROC glConvolutionParameterf = NULL;
PFNGLCONVOLUTIONPARAMETERFEXTPROC glConvolutionParameterfEXT = NULL;
PFNGLCONVOLUTIONPARAMETERFVPROC glConvolutionParameterfv = NULL;
PFNGLCONVOLUTIONPARAMETERFVEXTPROC glConvolutionParameterfvEXT = NULL;
PFNGLCONVOLUTIONPARAMETERIPROC glConvolutionParameteri = NULL;
PFNGLCONVOLUTIONPARAMETERIEXTPROC glConvolutionParameteriEXT = NULL;
PFNGLCONVOLUTIONPARAMETERIVPROC glConvolutionParameteriv = NULL;
PFNGLCONVOLUTIONPARAMETERIVEXTPROC glConvolutionParameterivEXT = NULL;
PFNGLCOPYBUFFERSUBDATAPROC glCopyBufferSubData = NULL;
PFNGLCOPYCOLORSUBTABLEPROC glCopyColorSubTable = NULL;
PFNGLCOPYCOLORSUBTABLEEXTPROC glCopyColorSubTableEXT = NULL;
PFNGLCOPYCOLORTABLEPROC glCopyColorTable = NULL;
PFNGLCOPYCONVOLUTIONFILTER1DPROC glCopyConvolutionFilter1D = NULL;
PFNGLCOPYCONVOLUTIONFILTER1DEXTPROC glCopyConvolutionFilter1DEXT = NULL;
PFNGLCOPYCONVOLUTIONFILTER2DPROC glCopyConvolutionFilter2D = NULL;
PFNGLCOPYCONVOLUTIONFILTER2DEXTPROC glCopyConvolutionFilter2DEXT = NULL;
PFNGLCOPYIMAGESUBDATAPROC glCopyImageSubData = NULL;
PFNGLCOPYIMAGESUBDATANVPROC glCopyImageSubDataNV = NULL;
PFNGLCOPYMULTITEXIMAGE1DEXTPROC glCopyMultiTexImage1DEXT = NULL;
PFNGLCOPYMULTITEXIMAGE2DEXTPROC glCopyMultiTexImage2DEXT = NULL;
PFNGLCOPYMULTITEXSUBIMAGE1DEXTPROC glCopyMultiTexSubImage1DEXT = NULL;
PFNGLCOPYMULTITEXSUBIMAGE2DEXTPROC glCopyMultiTexSubImage2DEXT = NULL;
PFNGLCOPYMULTITEXSUBIMAGE3DEXTPROC glCopyMultiTexSubImage3DEXT = NULL;
PFNGLCOPYNAMEDBUFFERSUBDATAPROC glCopyNamedBufferSubData = NULL;
PFNGLCOPYPATHNVPROC glCopyPathNV = NULL;
PFNGLCOPYPIXELSPROC glCopyPixels = NULL;
PFNGLCOPYTEXIMAGE1DPROC glCopyTexImage1D = NULL;
PFNGLCOPYTEXIMAGE1DEXTPROC glCopyTexImage1DEXT = NULL;
PFNGLCOPYTEXIMAGE2DPROC glCopyTexImage2D = NULL;
PFNGLCOPYTEXIMAGE2DEXTPROC glCopyTexImage2DEXT = NULL;
PFNGLCOPYTEXSUBIMAGE1DPROC glCopyTexSubImage1D = NULL;
PFNGLCOPYTEXSUBIMAGE1DEXTPROC glCopyTexSubImage1DEXT = NULL;
PFNGLCOPYTEXSUBIMAGE2DPROC glCopyTexSubImage2D = NULL;
PFNGLCOPYTEXSUBIMAGE2DEXTPROC glCopyTexSubImage2DEXT = NULL;
PFNGLCOPYTEXSUBIMAGE3DPROC glCopyTexSubImage3D = NULL;
PFNGLCOPYTEXSUBIMAGE3DEXTPROC glCopyTexSubImage3DEXT = NULL;
PFNGLCOPYTEXTUREIMAGE1DEXTPROC glCopyTextureImage1DEXT = NULL;
PFNGLCOPYTEXTUREIMAGE2DEXTPROC glCopyTextureImage2DEXT = NULL;
PFNGLCOPYTEXTURESUBIMAGE1DPROC glCopyTextureSubImage1D = NULL;
PFNGLCOPYTEXTURESUBIMAGE1DEXTPROC glCopyTextureSubImage1DEXT = NULL;
PFNGLCOPYTEXTURESUBIMAGE2DPROC glCopyTextureSubImage2D = NULL;
PFNGLCOPYTEXTURESUBIMAGE2DEXTPROC glCopyTextureSubImage2DEXT = NULL;
PFNGLCOPYTEXTURESUBIMAGE3DPROC glCopyTextureSubImage3D = NULL;
PFNGLCOPYTEXTURESUBIMAGE3DEXTPROC glCopyTextureSubImage3DEXT = NULL;
PFNGLCOVERFILLPATHINSTANCEDNVPROC glCoverFillPathInstancedNV = NULL;
PFNGLCOVERFILLPATHNVPROC glCoverFillPathNV = NULL;
PFNGLCOVERSTROKEPATHINSTANCEDNVPROC glCoverStrokePathInstancedNV = NULL;
PFNGLCOVERSTROKEPATHNVPROC glCoverStrokePathNV = NULL;
PFNGLCOVERAGEMODULATIONNVPROC glCoverageModulationNV = NULL;
PFNGLCOVERAGEMODULATIONTABLENVPROC glCoverageModulationTableNV = NULL;
PFNGLCREATEBUFFERSPROC glCreateBuffers = NULL;
PFNGLCREATECOMMANDLISTSNVPROC glCreateCommandListsNV = NULL;
PFNGLCREATEFRAMEBUFFERSPROC glCreateFramebuffers = NULL;
PFNGLCREATEMEMORYOBJECTSEXTPROC glCreateMemoryObjectsEXT = NULL;
PFNGLCREATEPERFQUERYINTELPROC glCreatePerfQueryINTEL = NULL;
PFNGLCREATEPROGRAMPROC glCreateProgram = NULL;
PFNGLCREATEPROGRAMOBJECTARBPROC glCreateProgramObjectARB = NULL;
PFNGLCREATEPROGRAMPIPELINESPROC glCreateProgramPipelines = NULL;
PFNGLCREATEPROGRESSFENCENVXPROC glCreateProgressFenceNVX = NULL;
PFNGLCREATEQUERIESPROC glCreateQueries = NULL;
PFNGLCREATERENDERBUFFERSPROC glCreateRenderbuffers = NULL;
PFNGLCREATESAMPLERSPROC glCreateSamplers = NULL;
PFNGLCREATESEMAPHORESNVPROC glCreateSemaphoresNV = NULL;
PFNGLCREATESHADERPROC glCreateShader = NULL;
PFNGLCREATESHADEROBJECTARBPROC glCreateShaderObjectARB = NULL;
PFNGLCREATESHADERPROGRAMEXTPROC glCreateShaderProgramEXT = NULL;
PFNGLCREATESHADERPROGRAMVPROC glCreateShaderProgramv = NULL;
PFNGLCREATESHADERPROGRAMVEXTPROC glCreateShaderProgramvEXT = NULL;
PFNGLCREATESTATESNVPROC glCreateStatesNV = NULL;
PFNGLCREATESYNCFROMCLEVENTARBPROC glCreateSyncFromCLeventARB = NULL;
PFNGLCREATETEXTURESPROC glCreateTextures = NULL;
PFNGLCREATETRANSFORMFEEDBACKSPROC glCreateTransformFeedbacks = NULL;
PFNGLCREATEVERTEXARRAYSPROC glCreateVertexArrays = NULL;
PFNGLCULLFACEPROC glCullFace = NULL;
PFNGLCULLPARAMETERDVEXTPROC glCullParameterdvEXT = NULL;
PFNGLCULLPARAMETERFVEXTPROC glCullParameterfvEXT = NULL;
PFNGLCURRENTPALETTEMATRIXARBPROC glCurrentPaletteMatrixARB = NULL;
PFNGLDEBUGMESSAGECALLBACKPROC glDebugMessageCallback = NULL;
PFNGLDEBUGMESSAGECALLBACKAMDPROC glDebugMessageCallbackAMD = NULL;
PFNGLDEBUGMESSAGECALLBACKARBPROC glDebugMessageCallbackARB = NULL;
PFNGLDEBUGMESSAGECALLBACKKHRPROC glDebugMessageCallbackKHR = NULL;
PFNGLDEBUGMESSAGECONTROLPROC glDebugMessageControl = NULL;
PFNGLDEBUGMESSAGECONTROLARBPROC glDebugMessageControlARB = NULL;
PFNGLDEBUGMESSAGECONTROLKHRPROC glDebugMessageControlKHR = NULL;
PFNGLDEBUGMESSAGEENABLEAMDPROC glDebugMessageEnableAMD = NULL;
PFNGLDEBUGMESSAGEINSERTPROC glDebugMessageInsert = NULL;
PFNGLDEBUGMESSAGEINSERTAMDPROC glDebugMessageInsertAMD = NULL;
PFNGLDEBUGMESSAGEINSERTARBPROC glDebugMessageInsertARB = NULL;
PFNGLDEBUGMESSAGEINSERTKHRPROC glDebugMessageInsertKHR = NULL;
PFNGLDELETEBUFFERSPROC glDeleteBuffers = NULL;
PFNGLDELETEBUFFERSARBPROC glDeleteBuffersARB = NULL;
PFNGLDELETECOMMANDLISTSNVPROC glDeleteCommandListsNV = NULL;
PFNGLDELETEFENCESAPPLEPROC glDeleteFencesAPPLE = NULL;
PFNGLDELETEFENCESNVPROC glDeleteFencesNV = NULL;
PFNGLDELETEFRAMEBUFFERSPROC glDeleteFramebuffers = NULL;
PFNGLDELETEFRAMEBUFFERSEXTPROC glDeleteFramebuffersEXT = NULL;
PFNGLDELETELISTSPROC glDeleteLists = NULL;
PFNGLDELETEMEMORYOBJECTSEXTPROC glDeleteMemoryObjectsEXT = NULL;
PFNGLDELETENAMEDSTRINGARBPROC glDeleteNamedStringARB = NULL;
PFNGLDELETENAMESAMDPROC glDeleteNamesAMD = NULL;
PFNGLDELETEOBJECTARBPROC glDeleteObjectARB = NULL;
PFNGLDELETEOCCLUSIONQUERIESNVPROC glDeleteOcclusionQueriesNV = NULL;
PFNGLDELETEPATHSNVPROC glDeletePathsNV = NULL;
PFNGLDELETEPERFMONITORSAMDPROC glDeletePerfMonitorsAMD = NULL;
PFNGLDELETEPERFQUERYINTELPROC glDeletePerfQueryINTEL = NULL;
PFNGLDELETEPROGRAMPROC glDeleteProgram = NULL;
PFNGLDELETEPROGRAMPIPELINESPROC glDeleteProgramPipelines = NULL;
PFNGLDELETEPROGRAMPIPELINESEXTPROC glDeleteProgramPipelinesEXT = NULL;
PFNGLDELETEPROGRAMSARBPROC glDeleteProgramsARB = NULL;
PFNGLDELETEPROGRAMSNVPROC glDeleteProgramsNV = NULL;
PFNGLDELETEQUERIESPROC glDeleteQueries = NULL;
PFNGLDELETEQUERIESARBPROC glDeleteQueriesARB = NULL;
PFNGLDELETEQUERYRESOURCETAGNVPROC glDeleteQueryResourceTagNV = NULL;
PFNGLDELETERENDERBUFFERSPROC glDeleteRenderbuffers = NULL;
PFNGLDELETERENDERBUFFERSEXTPROC glDeleteRenderbuffersEXT = NULL;
PFNGLDELETESAMPLERSPROC glDeleteSamplers = NULL;
PFNGLDELETESEMAPHORESEXTPROC glDeleteSemaphoresEXT = NULL;
PFNGLDELETESHADERPROC glDeleteShader = NULL;
PFNGLDELETESTATESNVPROC glDeleteStatesNV = NULL;
PFNGLDELETESYNCPROC glDeleteSync = NULL;
PFNGLDELETETEXTURESPROC glDeleteTextures = NULL;
PFNGLDELETETEXTURESEXTPROC glDeleteTexturesEXT = NULL;
PFNGLDELETETRANSFORMFEEDBACKSPROC glDeleteTransformFeedbacks = NULL;
PFNGLDELETETRANSFORMFEEDBACKSNVPROC glDeleteTransformFeedbacksNV = NULL;
PFNGLDELETEVERTEXARRAYSPROC glDeleteVertexArrays = NULL;
PFNGLDELETEVERTEXARRAYSAPPLEPROC glDeleteVertexArraysAPPLE = NULL;
PFNGLDELETEVERTEXSHADEREXTPROC glDeleteVertexShaderEXT = NULL;
PFNGLDEPTHBOUNDSEXTPROC glDepthBoundsEXT = NULL;
PFNGLDEPTHBOUNDSDNVPROC glDepthBoundsdNV = NULL;
PFNGLDEPTHFUNCPROC glDepthFunc = NULL;
PFNGLDEPTHMASKPROC glDepthMask = NULL;
PFNGLDEPTHRANGEPROC glDepthRange = NULL;
PFNGLDEPTHRANGEARRAYDVNVPROC glDepthRangeArraydvNV = NULL;
PFNGLDEPTHRANGEARRAYVPROC glDepthRangeArrayv = NULL;
PFNGLDEPTHRANGEINDEXEDPROC glDepthRangeIndexed = NULL;
PFNGLDEPTHRANGEINDEXEDDNVPROC glDepthRangeIndexeddNV = NULL;
PFNGLDEPTHRANGEDNVPROC glDepthRangedNV = NULL;
PFNGLDEPTHRANGEFPROC glDepthRangef = NULL;
PFNGLDETACHOBJECTARBPROC glDetachObjectARB = NULL;
PFNGLDETACHSHADERPROC glDetachShader = NULL;
PFNGLDISABLEPROC glDisable = NULL;
PFNGLDISABLECLIENTSTATEPROC glDisableClientState = NULL;
PFNGLDISABLECLIENTSTATEINDEXEDEXTPROC glDisableClientStateIndexedEXT = NULL;
PFNGLDISABLECLIENTSTATEIEXTPROC glDisableClientStateiEXT = NULL;
PFNGLDISABLEINDEXEDEXTPROC glDisableIndexedEXT = NULL;
PFNGLDISABLEVARIANTCLIENTSTATEEXTPROC glDisableVariantClientStateEXT = NULL;
PFNGLDISABLEVERTEXARRAYATTRIBPROC glDisableVertexArrayAttrib = NULL;
PFNGLDISABLEVERTEXARRAYATTRIBEXTPROC glDisableVertexArrayAttribEXT = NULL;
PFNGLDISABLEVERTEXARRAYEXTPROC glDisableVertexArrayEXT = NULL;
PFNGLDISABLEVERTEXATTRIBAPPLEPROC glDisableVertexAttribAPPLE = NULL;
PFNGLDISABLEVERTEXATTRIBARRAYPROC glDisableVertexAttribArray = NULL;
PFNGLDISABLEVERTEXATTRIBARRAYARBPROC glDisableVertexAttribArrayARB = NULL;
PFNGLDISABLEIPROC glDisablei = NULL;
PFNGLDISPATCHCOMPUTEPROC glDispatchCompute = NULL;
PFNGLDISPATCHCOMPUTEGROUPSIZEARBPROC glDispatchComputeGroupSizeARB = NULL;
PFNGLDISPATCHCOMPUTEINDIRECTPROC glDispatchComputeIndirect = NULL;
PFNGLDRAWARRAYSPROC glDrawArrays = NULL;
PFNGLDRAWARRAYSEXTPROC glDrawArraysEXT = NULL;
PFNGLDRAWARRAYSINDIRECTPROC glDrawArraysIndirect = NULL;
PFNGLDRAWARRAYSINSTANCEDPROC glDrawArraysInstanced = NULL;
PFNGLDRAWARRAYSINSTANCEDARBPROC glDrawArraysInstancedARB = NULL;
PFNGLDRAWARRAYSINSTANCEDBASEINSTANCEPROC glDrawArraysInstancedBaseInstance = NULL;
PFNGLDRAWARRAYSINSTANCEDEXTPROC glDrawArraysInstancedEXT = NULL;
PFNGLDRAWBUFFERPROC glDrawBuffer = NULL;
PFNGLDRAWBUFFERSPROC glDrawBuffers = NULL;
PFNGLDRAWBUFFERSARBPROC glDrawBuffersARB = NULL;
PFNGLDRAWCOMMANDSADDRESSNVPROC glDrawCommandsAddressNV = NULL;
PFNGLDRAWCOMMANDSNVPROC glDrawCommandsNV = NULL;
PFNGLDRAWCOMMANDSSTATESADDRESSNVPROC glDrawCommandsStatesAddressNV = NULL;
PFNGLDRAWCOMMANDSSTATESNVPROC glDrawCommandsStatesNV = NULL;
PFNGLDRAWELEMENTARRAYAPPLEPROC glDrawElementArrayAPPLE = NULL;
PFNGLDRAWELEMENTSPROC glDrawElements = NULL;
PFNGLDRAWELEMENTSBASEVERTEXPROC glDrawElementsBaseVertex = NULL;
PFNGLDRAWELEMENTSINDIRECTPROC glDrawElementsIndirect = NULL;
PFNGLDRAWELEMENTSINSTANCEDPROC glDrawElementsInstanced = NULL;
PFNGLDRAWELEMENTSINSTANCEDARBPROC glDrawElementsInstancedARB = NULL;
PFNGLDRAWELEMENTSINSTANCEDBASEINSTANCEPROC glDrawElementsInstancedBaseInstance = NULL;
PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXPROC glDrawElementsInstancedBaseVertex = NULL;
PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXBASEINSTANCEPROC
glDrawElementsInstancedBaseVertexBaseInstance = NULL;
PFNGLDRAWELEMENTSINSTANCEDEXTPROC glDrawElementsInstancedEXT = NULL;
PFNGLDRAWMESHTASKSNVPROC glDrawMeshTasksNV = NULL;
PFNGLDRAWMESHTASKSINDIRECTNVPROC glDrawMeshTasksIndirectNV = NULL;
PFNGLDRAWPIXELSPROC glDrawPixels = NULL;
PFNGLDRAWRANGEELEMENTARRAYAPPLEPROC glDrawRangeElementArrayAPPLE = NULL;
PFNGLDRAWRANGEELEMENTSPROC glDrawRangeElements = NULL;
PFNGLDRAWRANGEELEMENTSBASEVERTEXPROC glDrawRangeElementsBaseVertex = NULL;
PFNGLDRAWRANGEELEMENTSEXTPROC glDrawRangeElementsEXT = NULL;
PFNGLDRAWTEXTURENVPROC glDrawTextureNV = NULL;
PFNGLDRAWTRANSFORMFEEDBACKPROC glDrawTransformFeedback = NULL;
PFNGLDRAWTRANSFORMFEEDBACKINSTANCEDPROC glDrawTransformFeedbackInstanced = NULL;
PFNGLDRAWTRANSFORMFEEDBACKNVPROC glDrawTransformFeedbackNV = NULL;
PFNGLDRAWTRANSFORMFEEDBACKSTREAMPROC glDrawTransformFeedbackStream = NULL;
PFNGLDRAWTRANSFORMFEEDBACKSTREAMINSTANCEDPROC glDrawTransformFeedbackStreamInstanced = NULL;
PFNGLEGLIMAGETARGETTEXSTORAGEEXTPROC glEGLImageTargetTexStorageEXT = NULL;
PFNGLEGLIMAGETARGETTEXTURESTORAGEEXTPROC glEGLImageTargetTextureStorageEXT = NULL;
PFNGLEDGEFLAGPROC glEdgeFlag = NULL;
PFNGLEDGEFLAGFORMATNVPROC glEdgeFlagFormatNV = NULL;
PFNGLEDGEFLAGPOINTERPROC glEdgeFlagPointer = NULL;
PFNGLEDGEFLAGPOINTEREXTPROC glEdgeFlagPointerEXT = NULL;
PFNGLEDGEFLAGVPROC glEdgeFlagv = NULL;
PFNGLELEMENTPOINTERAPPLEPROC glElementPointerAPPLE = NULL;
PFNGLENABLEPROC glEnable = NULL;
PFNGLENABLECLIENTSTATEPROC glEnableClientState = NULL;
PFNGLENABLECLIENTSTATEINDEXEDEXTPROC glEnableClientStateIndexedEXT = NULL;
PFNGLENABLECLIENTSTATEIEXTPROC glEnableClientStateiEXT = NULL;
PFNGLENABLEINDEXEDEXTPROC glEnableIndexedEXT = NULL;
PFNGLENABLEVARIANTCLIENTSTATEEXTPROC glEnableVariantClientStateEXT = NULL;
PFNGLENABLEVERTEXARRAYATTRIBPROC glEnableVertexArrayAttrib = NULL;
PFNGLENABLEVERTEXARRAYATTRIBEXTPROC glEnableVertexArrayAttribEXT = NULL;
PFNGLENABLEVERTEXARRAYEXTPROC glEnableVertexArrayEXT = NULL;
PFNGLENABLEVERTEXATTRIBAPPLEPROC glEnableVertexAttribAPPLE = NULL;
PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray = NULL;
PFNGLENABLEVERTEXATTRIBARRAYARBPROC glEnableVertexAttribArrayARB = NULL;
PFNGLENABLEIPROC glEnablei = NULL;
PFNGLENDPROC glEnd = NULL;
PFNGLENDCONDITIONALRENDERPROC glEndConditionalRender = NULL;
PFNGLENDCONDITIONALRENDERNVPROC glEndConditionalRenderNV = NULL;
PFNGLENDCONDITIONALRENDERNVXPROC glEndConditionalRenderNVX = NULL;
PFNGLENDLISTPROC glEndList = NULL;
PFNGLENDOCCLUSIONQUERYNVPROC glEndOcclusionQueryNV = NULL;
PFNGLENDPERFMONITORAMDPROC glEndPerfMonitorAMD = NULL;
PFNGLENDPERFQUERYINTELPROC glEndPerfQueryINTEL = NULL;
PFNGLENDQUERYPROC glEndQuery = NULL;
PFNGLENDQUERYARBPROC glEndQueryARB = NULL;
PFNGLENDQUERYINDEXEDPROC glEndQueryIndexed = NULL;
PFNGLENDTRANSFORMFEEDBACKPROC glEndTransformFeedback = NULL;
PFNGLENDTRANSFORMFEEDBACKEXTPROC glEndTransformFeedbackEXT = NULL;
PFNGLENDTRANSFORMFEEDBACKNVPROC glEndTransformFeedbackNV = NULL;
PFNGLENDVERTEXSHADEREXTPROC glEndVertexShaderEXT = NULL;
PFNGLENDVIDEOCAPTURENVPROC glEndVideoCaptureNV = NULL;
PFNGLEVALCOORD1DPROC glEvalCoord1d = NULL;
PFNGLEVALCOORD1DVPROC glEvalCoord1dv = NULL;
PFNGLEVALCOORD1FPROC glEvalCoord1f = NULL;
PFNGLEVALCOORD1FVPROC glEvalCoord1fv = NULL;
PFNGLEVALCOORD2DPROC glEvalCoord2d = NULL;
PFNGLEVALCOORD2DVPROC glEvalCoord2dv = NULL;
PFNGLEVALCOORD2FPROC glEvalCoord2f = NULL;
PFNGLEVALCOORD2FVPROC glEvalCoord2fv = NULL;
PFNGLEVALMAPSNVPROC glEvalMapsNV = NULL;
PFNGLEVALMESH1PROC glEvalMesh1 = NULL;
PFNGLEVALMESH2PROC glEvalMesh2 = NULL;
PFNGLEVALPOINT1PROC glEvalPoint1 = NULL;
PFNGLEVALPOINT2PROC glEvalPoint2 = NULL;
PFNGLEVALUATEDEPTHVALUESARBPROC glEvaluateDepthValuesARB = NULL;
PFNGLEXECUTEPROGRAMNVPROC glExecuteProgramNV = NULL;
PFNGLEXTRACTCOMPONENTEXTPROC glExtractComponentEXT = NULL;
PFNGLFEEDBACKBUFFERPROC glFeedbackBuffer = NULL;
PFNGLFENCESYNCPROC glFenceSync = NULL;
PFNGLFINALCOMBINERINPUTNVPROC glFinalCombinerInputNV = NULL;
PFNGLFINISHPROC glFinish = NULL;
PFNGLFINISHFENCEAPPLEPROC glFinishFenceAPPLE = NULL;
PFNGLFINISHFENCENVPROC glFinishFenceNV = NULL;
PFNGLFINISHOBJECTAPPLEPROC glFinishObjectAPPLE = NULL;
PFNGLFLUSHPROC glFlush = NULL;
PFNGLFLUSHMAPPEDBUFFERRANGEPROC glFlushMappedBufferRange = NULL;
PFNGLFLUSHMAPPEDBUFFERRANGEAPPLEPROC glFlushMappedBufferRangeAPPLE = NULL;
PFNGLFLUSHMAPPEDNAMEDBUFFERRANGEPROC glFlushMappedNamedBufferRange = NULL;
PFNGLFLUSHMAPPEDNAMEDBUFFERRANGEEXTPROC glFlushMappedNamedBufferRangeEXT = NULL;
PFNGLFLUSHPIXELDATARANGENVPROC glFlushPixelDataRangeNV = NULL;
PFNGLFLUSHVERTEXARRAYRANGEAPPLEPROC glFlushVertexArrayRangeAPPLE = NULL;
PFNGLFLUSHVERTEXARRAYRANGENVPROC glFlushVertexArrayRangeNV = NULL;
PFNGLFOGCOORDFORMATNVPROC glFogCoordFormatNV = NULL;
PFNGLFOGCOORDPOINTERPROC glFogCoordPointer = NULL;
PFNGLFOGCOORDPOINTEREXTPROC glFogCoordPointerEXT = NULL;
PFNGLFOGCOORDDPROC glFogCoordd = NULL;
PFNGLFOGCOORDDEXTPROC glFogCoorddEXT = NULL;
PFNGLFOGCOORDDVPROC glFogCoorddv = NULL;
PFNGLFOGCOORDDVEXTPROC glFogCoorddvEXT = NULL;
PFNGLFOGCOORDFPROC glFogCoordf = NULL;
PFNGLFOGCOORDFEXTPROC glFogCoordfEXT = NULL;
PFNGLFOGCOORDFVPROC glFogCoordfv = NULL;
PFNGLFOGCOORDFVEXTPROC glFogCoordfvEXT = NULL;
PFNGLFOGCOORDHNVPROC glFogCoordhNV = NULL;
PFNGLFOGCOORDHVNVPROC glFogCoordhvNV = NULL;
PFNGLFOGFPROC glFogf = NULL;
PFNGLFOGFVPROC glFogfv = NULL;
PFNGLFOGIPROC glFogi = NULL;
PFNGLFOGIVPROC glFogiv = NULL;
PFNGLFRAGMENTCOVERAGECOLORNVPROC glFragmentCoverageColorNV = NULL;
PFNGLFRAMEBUFFERDRAWBUFFEREXTPROC glFramebufferDrawBufferEXT = NULL;
PFNGLFRAMEBUFFERDRAWBUFFERSEXTPROC glFramebufferDrawBuffersEXT = NULL;
PFNGLFRAMEBUFFERFETCHBARRIEREXTPROC glFramebufferFetchBarrierEXT = NULL;
PFNGLFRAMEBUFFERPARAMETERIPROC glFramebufferParameteri = NULL;
PFNGLFRAMEBUFFERREADBUFFEREXTPROC glFramebufferReadBufferEXT = NULL;
PFNGLFRAMEBUFFERRENDERBUFFERPROC glFramebufferRenderbuffer = NULL;
PFNGLFRAMEBUFFERRENDERBUFFEREXTPROC glFramebufferRenderbufferEXT = NULL;
PFNGLFRAMEBUFFERSAMPLELOCATIONSFVARBPROC glFramebufferSampleLocationsfvARB = NULL;
PFNGLFRAMEBUFFERSAMPLELOCATIONSFVNVPROC glFramebufferSampleLocationsfvNV = NULL;
PFNGLFRAMEBUFFERSAMPLEPOSITIONSFVAMDPROC glFramebufferSamplePositionsfvAMD = NULL;
PFNGLFRAMEBUFFERTEXTUREPROC glFramebufferTexture = NULL;
PFNGLFRAMEBUFFERTEXTURE1DPROC glFramebufferTexture1D = NULL;
PFNGLFRAMEBUFFERTEXTURE1DEXTPROC glFramebufferTexture1DEXT = NULL;
PFNGLFRAMEBUFFERTEXTURE2DPROC glFramebufferTexture2D = NULL;
PFNGLFRAMEBUFFERTEXTURE2DEXTPROC glFramebufferTexture2DEXT = NULL;
PFNGLFRAMEBUFFERTEXTURE3DPROC glFramebufferTexture3D = NULL;
PFNGLFRAMEBUFFERTEXTURE3DEXTPROC glFramebufferTexture3DEXT = NULL;
PFNGLFRAMEBUFFERTEXTUREARBPROC glFramebufferTextureARB = NULL;
PFNGLFRAMEBUFFERTEXTUREEXTPROC glFramebufferTextureEXT = NULL;
PFNGLFRAMEBUFFERTEXTUREFACEARBPROC glFramebufferTextureFaceARB = NULL;
PFNGLFRAMEBUFFERTEXTUREFACEEXTPROC glFramebufferTextureFaceEXT = NULL;
PFNGLFRAMEBUFFERTEXTURELAYERPROC glFramebufferTextureLayer = NULL;
PFNGLFRAMEBUFFERTEXTURELAYERARBPROC glFramebufferTextureLayerARB = NULL;
PFNGLFRAMEBUFFERTEXTURELAYEREXTPROC glFramebufferTextureLayerEXT = NULL;
PFNGLFRONTFACEPROC glFrontFace = NULL;
PFNGLFRUSTUMPROC glFrustum = NULL;
PFNGLGENBUFFERSPROC glGenBuffers = NULL;
PFNGLGENBUFFERSARBPROC glGenBuffersARB = NULL;
PFNGLGENFENCESAPPLEPROC glGenFencesAPPLE = NULL;
PFNGLGENFENCESNVPROC glGenFencesNV = NULL;
PFNGLGENFRAMEBUFFERSPROC glGenFramebuffers = NULL;
PFNGLGENFRAMEBUFFERSEXTPROC glGenFramebuffersEXT = NULL;
PFNGLGENLISTSPROC glGenLists = NULL;
PFNGLGENNAMESAMDPROC glGenNamesAMD = NULL;
PFNGLGENOCCLUSIONQUERIESNVPROC glGenOcclusionQueriesNV = NULL;
PFNGLGENPATHSNVPROC glGenPathsNV = NULL;
PFNGLGENPERFMONITORSAMDPROC glGenPerfMonitorsAMD = NULL;
PFNGLGENPROGRAMPIPELINESPROC glGenProgramPipelines = NULL;
PFNGLGENPROGRAMPIPELINESEXTPROC glGenProgramPipelinesEXT = NULL;
PFNGLGENPROGRAMSARBPROC glGenProgramsARB = NULL;
PFNGLGENPROGRAMSNVPROC glGenProgramsNV = NULL;
PFNGLGENQUERIESPROC glGenQueries = NULL;
PFNGLGENQUERIESARBPROC glGenQueriesARB = NULL;
PFNGLGENQUERYRESOURCETAGNVPROC glGenQueryResourceTagNV = NULL;
PFNGLGENRENDERBUFFERSPROC glGenRenderbuffers = NULL;
PFNGLGENRENDERBUFFERSEXTPROC glGenRenderbuffersEXT = NULL;
PFNGLGENSAMPLERSPROC glGenSamplers = NULL;
PFNGLGENSEMAPHORESEXTPROC glGenSemaphoresEXT = NULL;
PFNGLGENSYMBOLSEXTPROC glGenSymbolsEXT = NULL;
PFNGLGENTEXTURESPROC glGenTextures = NULL;
PFNGLGENTEXTURESEXTPROC glGenTexturesEXT = NULL;
PFNGLGENTRANSFORMFEEDBACKSPROC glGenTransformFeedbacks = NULL;
PFNGLGENTRANSFORMFEEDBACKSNVPROC glGenTransformFeedbacksNV = NULL;
PFNGLGENVERTEXARRAYSPROC glGenVertexArrays = NULL;
PFNGLGENVERTEXARRAYSAPPLEPROC glGenVertexArraysAPPLE = NULL;
PFNGLGENVERTEXSHADERSEXTPROC glGenVertexShadersEXT = NULL;
PFNGLGENERATEMIPMAPPROC glGenerateMipmap = NULL;
PFNGLGENERATEMIPMAPEXTPROC glGenerateMipmapEXT = NULL;
PFNGLGENERATEMULTITEXMIPMAPEXTPROC glGenerateMultiTexMipmapEXT = NULL;
PFNGLGENERATETEXTUREMIPMAPPROC glGenerateTextureMipmap = NULL;
PFNGLGENERATETEXTUREMIPMAPEXTPROC glGenerateTextureMipmapEXT = NULL;
PFNGLGETACTIVEATOMICCOUNTERBUFFERIVPROC glGetActiveAtomicCounterBufferiv = NULL;
PFNGLGETACTIVEATTRIBPROC glGetActiveAttrib = NULL;
PFNGLGETACTIVEATTRIBARBPROC glGetActiveAttribARB = NULL;
PFNGLGETACTIVESUBROUTINENAMEPROC glGetActiveSubroutineName = NULL;
PFNGLGETACTIVESUBROUTINEUNIFORMNAMEPROC glGetActiveSubroutineUniformName = NULL;
PFNGLGETACTIVESUBROUTINEUNIFORMIVPROC glGetActiveSubroutineUniformiv = NULL;
PFNGLGETACTIVEUNIFORMPROC glGetActiveUniform = NULL;
PFNGLGETACTIVEUNIFORMARBPROC glGetActiveUniformARB = NULL;
PFNGLGETACTIVEUNIFORMBLOCKNAMEPROC glGetActiveUniformBlockName = NULL;
PFNGLGETACTIVEUNIFORMBLOCKIVPROC glGetActiveUniformBlockiv = NULL;
PFNGLGETACTIVEUNIFORMNAMEPROC glGetActiveUniformName = NULL;
PFNGLGETACTIVEUNIFORMSIVPROC glGetActiveUniformsiv = NULL;
PFNGLGETACTIVEVARYINGNVPROC glGetActiveVaryingNV = NULL;
PFNGLGETATTACHEDOBJECTSARBPROC glGetAttachedObjectsARB = NULL;
PFNGLGETATTACHEDSHADERSPROC glGetAttachedShaders = NULL;
PFNGLGETATTRIBLOCATIONPROC glGetAttribLocation = NULL;
PFNGLGETATTRIBLOCATIONARBPROC glGetAttribLocationARB = NULL;
PFNGLGETBOOLEANINDEXEDVEXTPROC glGetBooleanIndexedvEXT = NULL;
PFNGLGETBOOLEANI_VPROC glGetBooleani_v = NULL;
PFNGLGETBOOLEANVPROC glGetBooleanv = NULL;
PFNGLGETBUFFERPARAMETERI64VPROC glGetBufferParameteri64v = NULL;
PFNGLGETBUFFERPARAMETERIVPROC glGetBufferParameteriv = NULL;
PFNGLGETBUFFERPARAMETERIVARBPROC glGetBufferParameterivARB = NULL;
PFNGLGETBUFFERPARAMETERUI64VNVPROC glGetBufferParameterui64vNV = NULL;
PFNGLGETBUFFERPOINTERVPROC glGetBufferPointerv = NULL;
PFNGLGETBUFFERPOINTERVARBPROC glGetBufferPointervARB = NULL;
PFNGLGETBUFFERSUBDATAPROC glGetBufferSubData = NULL;
PFNGLGETBUFFERSUBDATAARBPROC glGetBufferSubDataARB = NULL;
PFNGLGETCLIPPLANEPROC glGetClipPlane = NULL;
PFNGLGETCOLORTABLEPROC glGetColorTable = NULL;
PFNGLGETCOLORTABLEEXTPROC glGetColorTableEXT = NULL;
PFNGLGETCOLORTABLEPARAMETERFVPROC glGetColorTableParameterfv = NULL;
PFNGLGETCOLORTABLEPARAMETERFVEXTPROC glGetColorTableParameterfvEXT = NULL;
PFNGLGETCOLORTABLEPARAMETERIVPROC glGetColorTableParameteriv = NULL;
PFNGLGETCOLORTABLEPARAMETERIVEXTPROC glGetColorTableParameterivEXT = NULL;
PFNGLGETCOMBINERINPUTPARAMETERFVNVPROC glGetCombinerInputParameterfvNV = NULL;
PFNGLGETCOMBINERINPUTPARAMETERIVNVPROC glGetCombinerInputParameterivNV = NULL;
PFNGLGETCOMBINEROUTPUTPARAMETERFVNVPROC glGetCombinerOutputParameterfvNV = NULL;
PFNGLGETCOMBINEROUTPUTPARAMETERIVNVPROC glGetCombinerOutputParameterivNV = NULL;
PFNGLGETCOMBINERSTAGEPARAMETERFVNVPROC glGetCombinerStageParameterfvNV = NULL;
PFNGLGETCOMMANDHEADERNVPROC glGetCommandHeaderNV = NULL;
PFNGLGETCOMPRESSEDMULTITEXIMAGEEXTPROC glGetCompressedMultiTexImageEXT = NULL;
PFNGLGETCOMPRESSEDTEXIMAGEPROC glGetCompressedTexImage = NULL;
PFNGLGETCOMPRESSEDTEXIMAGEARBPROC glGetCompressedTexImageARB = NULL;
PFNGLGETCOMPRESSEDTEXTUREIMAGEPROC glGetCompressedTextureImage = NULL;
PFNGLGETCOMPRESSEDTEXTUREIMAGEEXTPROC glGetCompressedTextureImageEXT = NULL;
PFNGLGETCOMPRESSEDTEXTURESUBIMAGEPROC glGetCompressedTextureSubImage = NULL;
PFNGLGETCONVOLUTIONFILTERPROC glGetConvolutionFilter = NULL;
PFNGLGETCONVOLUTIONFILTEREXTPROC glGetConvolutionFilterEXT = NULL;
PFNGLGETCONVOLUTIONPARAMETERFVPROC glGetConvolutionParameterfv = NULL;
PFNGLGETCONVOLUTIONPARAMETERFVEXTPROC glGetConvolutionParameterfvEXT = NULL;
PFNGLGETCONVOLUTIONPARAMETERIVPROC glGetConvolutionParameteriv = NULL;
PFNGLGETCONVOLUTIONPARAMETERIVEXTPROC glGetConvolutionParameterivEXT = NULL;
PFNGLGETCOVERAGEMODULATIONTABLENVPROC glGetCoverageModulationTableNV = NULL;
PFNGLGETDEBUGMESSAGELOGPROC glGetDebugMessageLog = NULL;
PFNGLGETDEBUGMESSAGELOGAMDPROC glGetDebugMessageLogAMD = NULL;
PFNGLGETDEBUGMESSAGELOGARBPROC glGetDebugMessageLogARB = NULL;
PFNGLGETDEBUGMESSAGELOGKHRPROC glGetDebugMessageLogKHR = NULL;
PFNGLGETDOUBLEINDEXEDVEXTPROC glGetDoubleIndexedvEXT = NULL;
PFNGLGETDOUBLEI_VPROC glGetDoublei_v = NULL;
PFNGLGETDOUBLEI_VEXTPROC glGetDoublei_vEXT = NULL;
PFNGLGETDOUBLEVPROC glGetDoublev = NULL;
PFNGLGETERRORPROC glGetError = NULL;
PFNGLGETFENCEIVNVPROC glGetFenceivNV = NULL;
PFNGLGETFINALCOMBINERINPUTPARAMETERFVNVPROC glGetFinalCombinerInputParameterfvNV = NULL;
PFNGLGETFINALCOMBINERINPUTPARAMETERIVNVPROC glGetFinalCombinerInputParameterivNV = NULL;
PFNGLGETFIRSTPERFQUERYIDINTELPROC glGetFirstPerfQueryIdINTEL = NULL;
PFNGLGETFLOATINDEXEDVEXTPROC glGetFloatIndexedvEXT = NULL;
PFNGLGETFLOATI_VPROC glGetFloati_v = NULL;
PFNGLGETFLOATI_VEXTPROC glGetFloati_vEXT = NULL;
PFNGLGETFLOATVPROC glGetFloatv = NULL;
PFNGLGETFRAGDATAINDEXPROC glGetFragDataIndex = NULL;
PFNGLGETFRAGDATALOCATIONPROC glGetFragDataLocation = NULL;
PFNGLGETFRAGDATALOCATIONEXTPROC glGetFragDataLocationEXT = NULL;
PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC glGetFramebufferAttachmentParameteriv = NULL;
PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVEXTPROC glGetFramebufferAttachmentParameterivEXT = NULL;
PFNGLGETFRAMEBUFFERPARAMETERFVAMDPROC glGetFramebufferParameterfvAMD = NULL;
PFNGLGETFRAMEBUFFERPARAMETERIVPROC glGetFramebufferParameteriv = NULL;
PFNGLGETFRAMEBUFFERPARAMETERIVEXTPROC glGetFramebufferParameterivEXT = NULL;
PFNGLGETGRAPHICSRESETSTATUSPROC glGetGraphicsResetStatus = NULL;
PFNGLGETGRAPHICSRESETSTATUSARBPROC glGetGraphicsResetStatusARB = NULL;
PFNGLGETGRAPHICSRESETSTATUSKHRPROC glGetGraphicsResetStatusKHR = NULL;
PFNGLGETHANDLEARBPROC glGetHandleARB = NULL;
PFNGLGETHISTOGRAMPROC glGetHistogram = NULL;
PFNGLGETHISTOGRAMEXTPROC glGetHistogramEXT = NULL;
PFNGLGETHISTOGRAMPARAMETERFVPROC glGetHistogramParameterfv = NULL;
PFNGLGETHISTOGRAMPARAMETERFVEXTPROC glGetHistogramParameterfvEXT = NULL;
PFNGLGETHISTOGRAMPARAMETERIVPROC glGetHistogramParameteriv = NULL;
PFNGLGETHISTOGRAMPARAMETERIVEXTPROC glGetHistogramParameterivEXT = NULL;
PFNGLGETIMAGEHANDLEARBPROC glGetImageHandleARB = NULL;
PFNGLGETIMAGEHANDLENVPROC glGetImageHandleNV = NULL;
PFNGLGETINFOLOGARBPROC glGetInfoLogARB = NULL;
PFNGLGETINTEGER64I_VPROC glGetInteger64i_v = NULL;
PFNGLGETINTEGER64VPROC glGetInteger64v = NULL;
PFNGLGETINTEGERINDEXEDVEXTPROC glGetIntegerIndexedvEXT = NULL;
PFNGLGETINTEGERI_VPROC glGetIntegeri_v = NULL;
PFNGLGETINTEGERUI64I_VNVPROC glGetIntegerui64i_vNV = NULL;
PFNGLGETINTEGERUI64VNVPROC glGetIntegerui64vNV = NULL;
PFNGLGETINTEGERVPROC glGetIntegerv = NULL;
PFNGLGETINTERNALFORMATSAMPLEIVNVPROC glGetInternalformatSampleivNV = NULL;
PFNGLGETINTERNALFORMATI64VPROC glGetInternalformati64v = NULL;
PFNGLGETINTERNALFORMATIVPROC glGetInternalformativ = NULL;
PFNGLGETINVARIANTBOOLEANVEXTPROC glGetInvariantBooleanvEXT = NULL;
PFNGLGETINVARIANTFLOATVEXTPROC glGetInvariantFloatvEXT = NULL;
PFNGLGETINVARIANTINTEGERVEXTPROC glGetInvariantIntegervEXT = NULL;
PFNGLGETLIGHTFVPROC glGetLightfv = NULL;
PFNGLGETLIGHTIVPROC glGetLightiv = NULL;
PFNGLGETLOCALCONSTANTBOOLEANVEXTPROC glGetLocalConstantBooleanvEXT = NULL;
PFNGLGETLOCALCONSTANTFLOATVEXTPROC glGetLocalConstantFloatvEXT = NULL;
PFNGLGETLOCALCONSTANTINTEGERVEXTPROC glGetLocalConstantIntegervEXT = NULL;
PFNGLGETMAPATTRIBPARAMETERFVNVPROC glGetMapAttribParameterfvNV = NULL;
PFNGLGETMAPATTRIBPARAMETERIVNVPROC glGetMapAttribParameterivNV = NULL;
PFNGLGETMAPCONTROLPOINTSNVPROC glGetMapControlPointsNV = NULL;
PFNGLGETMAPPARAMETERFVNVPROC glGetMapParameterfvNV = NULL;
PFNGLGETMAPPARAMETERIVNVPROC glGetMapParameterivNV = NULL;
PFNGLGETMAPDVPROC glGetMapdv = NULL;
PFNGLGETMAPFVPROC glGetMapfv = NULL;
PFNGLGETMAPIVPROC glGetMapiv = NULL;
PFNGLGETMATERIALFVPROC glGetMaterialfv = NULL;
PFNGLGETMATERIALIVPROC glGetMaterialiv = NULL;
PFNGLGETMEMORYOBJECTDETACHEDRESOURCESUIVNVPROC glGetMemoryObjectDetachedResourcesuivNV = NULL;
PFNGLGETMEMORYOBJECTPARAMETERIVEXTPROC glGetMemoryObjectParameterivEXT = NULL;
PFNGLGETMINMAXPROC glGetMinmax = NULL;
PFNGLGETMINMAXEXTPROC glGetMinmaxEXT = NULL;
PFNGLGETMINMAXPARAMETERFVPROC glGetMinmaxParameterfv = NULL;
PFNGLGETMINMAXPARAMETERFVEXTPROC glGetMinmaxParameterfvEXT = NULL;
PFNGLGETMINMAXPARAMETERIVPROC glGetMinmaxParameteriv = NULL;
PFNGLGETMINMAXPARAMETERIVEXTPROC glGetMinmaxParameterivEXT = NULL;
PFNGLGETMULTITEXENVFVEXTPROC glGetMultiTexEnvfvEXT = NULL;
PFNGLGETMULTITEXENVIVEXTPROC glGetMultiTexEnvivEXT = NULL;
PFNGLGETMULTITEXGENDVEXTPROC glGetMultiTexGendvEXT = NULL;
PFNGLGETMULTITEXGENFVEXTPROC glGetMultiTexGenfvEXT = NULL;
PFNGLGETMULTITEXGENIVEXTPROC glGetMultiTexGenivEXT = NULL;
PFNGLGETMULTITEXIMAGEEXTPROC glGetMultiTexImageEXT = NULL;
PFNGLGETMULTITEXLEVELPARAMETERFVEXTPROC glGetMultiTexLevelParameterfvEXT = NULL;
PFNGLGETMULTITEXLEVELPARAMETERIVEXTPROC glGetMultiTexLevelParameterivEXT = NULL;
PFNGLGETMULTITEXPARAMETERIIVEXTPROC glGetMultiTexParameterIivEXT = NULL;
PFNGLGETMULTITEXPARAMETERIUIVEXTPROC glGetMultiTexParameterIuivEXT = NULL;
PFNGLGETMULTITEXPARAMETERFVEXTPROC glGetMultiTexParameterfvEXT = NULL;
PFNGLGETMULTITEXPARAMETERIVEXTPROC glGetMultiTexParameterivEXT = NULL;
PFNGLGETMULTISAMPLEFVPROC glGetMultisamplefv = NULL;
PFNGLGETMULTISAMPLEFVNVPROC glGetMultisamplefvNV = NULL;
PFNGLGETNAMEDBUFFERPARAMETERI64VPROC glGetNamedBufferParameteri64v = NULL;
PFNGLGETNAMEDBUFFERPARAMETERIVPROC glGetNamedBufferParameteriv = NULL;
PFNGLGETNAMEDBUFFERPARAMETERIVEXTPROC glGetNamedBufferParameterivEXT = NULL;
PFNGLGETNAMEDBUFFERPARAMETERUI64VNVPROC glGetNamedBufferParameterui64vNV = NULL;
PFNGLGETNAMEDBUFFERPOINTERVPROC glGetNamedBufferPointerv = NULL;
PFNGLGETNAMEDBUFFERPOINTERVEXTPROC glGetNamedBufferPointervEXT = NULL;
PFNGLGETNAMEDBUFFERSUBDATAPROC glGetNamedBufferSubData = NULL;
PFNGLGETNAMEDBUFFERSUBDATAEXTPROC glGetNamedBufferSubDataEXT = NULL;
PFNGLGETNAMEDFRAMEBUFFERPARAMETERFVAMDPROC glGetNamedFramebufferParameterfvAMD = NULL;
PFNGLGETNAMEDFRAMEBUFFERATTACHMENTPARAMETERIVPROC glGetNamedFramebufferAttachmentParameteriv =
    NULL;
PFNGLGETNAMEDFRAMEBUFFERATTACHMENTPARAMETERIVEXTPROC
glGetNamedFramebufferAttachmentParameterivEXT = NULL;
PFNGLGETNAMEDFRAMEBUFFERPARAMETERIVPROC glGetNamedFramebufferParameteriv = NULL;
PFNGLGETNAMEDFRAMEBUFFERPARAMETERIVEXTPROC glGetNamedFramebufferParameterivEXT = NULL;
PFNGLGETNAMEDPROGRAMLOCALPARAMETERIIVEXTPROC glGetNamedProgramLocalParameterIivEXT = NULL;
PFNGLGETNAMEDPROGRAMLOCALPARAMETERIUIVEXTPROC glGetNamedProgramLocalParameterIuivEXT = NULL;
PFNGLGETNAMEDPROGRAMLOCALPARAMETERDVEXTPROC glGetNamedProgramLocalParameterdvEXT = NULL;
PFNGLGETNAMEDPROGRAMLOCALPARAMETERFVEXTPROC glGetNamedProgramLocalParameterfvEXT = NULL;
PFNGLGETNAMEDPROGRAMSTRINGEXTPROC glGetNamedProgramStringEXT = NULL;
PFNGLGETNAMEDPROGRAMIVEXTPROC glGetNamedProgramivEXT = NULL;
PFNGLGETNAMEDRENDERBUFFERPARAMETERIVPROC glGetNamedRenderbufferParameteriv = NULL;
PFNGLGETNAMEDRENDERBUFFERPARAMETERIVEXTPROC glGetNamedRenderbufferParameterivEXT = NULL;
PFNGLGETNAMEDSTRINGARBPROC glGetNamedStringARB = NULL;
PFNGLGETNAMEDSTRINGIVARBPROC glGetNamedStringivARB = NULL;
PFNGLGETNEXTPERFQUERYIDINTELPROC glGetNextPerfQueryIdINTEL = NULL;
PFNGLGETOBJECTLABELPROC glGetObjectLabel = NULL;
PFNGLGETOBJECTLABELEXTPROC glGetObjectLabelEXT = NULL;
PFNGLGETOBJECTLABELKHRPROC glGetObjectLabelKHR = NULL;
PFNGLGETOBJECTPARAMETERFVARBPROC glGetObjectParameterfvARB = NULL;
PFNGLGETOBJECTPARAMETERIVAPPLEPROC glGetObjectParameterivAPPLE = NULL;
PFNGLGETOBJECTPARAMETERIVARBPROC glGetObjectParameterivARB = NULL;
PFNGLGETOBJECTPTRLABELPROC glGetObjectPtrLabel = NULL;
PFNGLGETOBJECTPTRLABELKHRPROC glGetObjectPtrLabelKHR = NULL;
PFNGLGETOCCLUSIONQUERYIVNVPROC glGetOcclusionQueryivNV = NULL;
PFNGLGETOCCLUSIONQUERYUIVNVPROC glGetOcclusionQueryuivNV = NULL;
PFNGLGETPATHCOLORGENFVNVPROC glGetPathColorGenfvNV = NULL;
PFNGLGETPATHCOLORGENIVNVPROC glGetPathColorGenivNV = NULL;
PFNGLGETPATHCOMMANDSNVPROC glGetPathCommandsNV = NULL;
PFNGLGETPATHCOORDSNVPROC glGetPathCoordsNV = NULL;
PFNGLGETPATHDASHARRAYNVPROC glGetPathDashArrayNV = NULL;
PFNGLGETPATHLENGTHNVPROC glGetPathLengthNV = NULL;
PFNGLGETPATHMETRICRANGENVPROC glGetPathMetricRangeNV = NULL;
PFNGLGETPATHMETRICSNVPROC glGetPathMetricsNV = NULL;
PFNGLGETPATHPARAMETERFVNVPROC glGetPathParameterfvNV = NULL;
PFNGLGETPATHPARAMETERIVNVPROC glGetPathParameterivNV = NULL;
PFNGLGETPATHSPACINGNVPROC glGetPathSpacingNV = NULL;
PFNGLGETPATHTEXGENFVNVPROC glGetPathTexGenfvNV = NULL;
PFNGLGETPATHTEXGENIVNVPROC glGetPathTexGenivNV = NULL;
PFNGLGETPERFCOUNTERINFOINTELPROC glGetPerfCounterInfoINTEL = NULL;
PFNGLGETPERFMONITORCOUNTERDATAAMDPROC glGetPerfMonitorCounterDataAMD = NULL;
PFNGLGETPERFMONITORCOUNTERINFOAMDPROC glGetPerfMonitorCounterInfoAMD = NULL;
PFNGLGETPERFMONITORCOUNTERSTRINGAMDPROC glGetPerfMonitorCounterStringAMD = NULL;
PFNGLGETPERFMONITORCOUNTERSAMDPROC glGetPerfMonitorCountersAMD = NULL;
PFNGLGETPERFMONITORGROUPSTRINGAMDPROC glGetPerfMonitorGroupStringAMD = NULL;
PFNGLGETPERFMONITORGROUPSAMDPROC glGetPerfMonitorGroupsAMD = NULL;
PFNGLGETPERFQUERYDATAINTELPROC glGetPerfQueryDataINTEL = NULL;
PFNGLGETPERFQUERYIDBYNAMEINTELPROC glGetPerfQueryIdByNameINTEL = NULL;
PFNGLGETPERFQUERYINFOINTELPROC glGetPerfQueryInfoINTEL = NULL;
PFNGLGETPIXELMAPFVPROC glGetPixelMapfv = NULL;
PFNGLGETPIXELMAPUIVPROC glGetPixelMapuiv = NULL;
PFNGLGETPIXELMAPUSVPROC glGetPixelMapusv = NULL;
PFNGLGETPIXELTRANSFORMPARAMETERFVEXTPROC glGetPixelTransformParameterfvEXT = NULL;
PFNGLGETPIXELTRANSFORMPARAMETERIVEXTPROC glGetPixelTransformParameterivEXT = NULL;
PFNGLGETPOINTERINDEXEDVEXTPROC glGetPointerIndexedvEXT = NULL;
PFNGLGETPOINTERI_VEXTPROC glGetPointeri_vEXT = NULL;
PFNGLGETPOINTERVPROC glGetPointerv = NULL;
PFNGLGETPOINTERVEXTPROC glGetPointervEXT = NULL;
PFNGLGETPOINTERVKHRPROC glGetPointervKHR = NULL;
PFNGLGETPOLYGONSTIPPLEPROC glGetPolygonStipple = NULL;
PFNGLGETPROGRAMBINARYPROC glGetProgramBinary = NULL;
PFNGLGETPROGRAMENVPARAMETERIIVNVPROC glGetProgramEnvParameterIivNV = NULL;
PFNGLGETPROGRAMENVPARAMETERIUIVNVPROC glGetProgramEnvParameterIuivNV = NULL;
PFNGLGETPROGRAMENVPARAMETERDVARBPROC glGetProgramEnvParameterdvARB = NULL;
PFNGLGETPROGRAMENVPARAMETERFVARBPROC glGetProgramEnvParameterfvARB = NULL;
PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog = NULL;
PFNGLGETPROGRAMINTERFACEIVPROC glGetProgramInterfaceiv = NULL;
PFNGLGETPROGRAMLOCALPARAMETERIIVNVPROC glGetProgramLocalParameterIivNV = NULL;
PFNGLGETPROGRAMLOCALPARAMETERIUIVNVPROC glGetProgramLocalParameterIuivNV = NULL;
PFNGLGETPROGRAMLOCALPARAMETERDVARBPROC glGetProgramLocalParameterdvARB = NULL;
PFNGLGETPROGRAMLOCALPARAMETERFVARBPROC glGetProgramLocalParameterfvARB = NULL;
PFNGLGETPROGRAMNAMEDPARAMETERDVNVPROC glGetProgramNamedParameterdvNV = NULL;
PFNGLGETPROGRAMNAMEDPARAMETERFVNVPROC glGetProgramNamedParameterfvNV = NULL;
PFNGLGETPROGRAMPARAMETERDVNVPROC glGetProgramParameterdvNV = NULL;
PFNGLGETPROGRAMPARAMETERFVNVPROC glGetProgramParameterfvNV = NULL;
PFNGLGETPROGRAMPIPELINEINFOLOGPROC glGetProgramPipelineInfoLog = NULL;
PFNGLGETPROGRAMPIPELINEINFOLOGEXTPROC glGetProgramPipelineInfoLogEXT = NULL;
PFNGLGETPROGRAMPIPELINEIVPROC glGetProgramPipelineiv = NULL;
PFNGLGETPROGRAMPIPELINEIVEXTPROC glGetProgramPipelineivEXT = NULL;
PFNGLGETPROGRAMRESOURCEINDEXPROC glGetProgramResourceIndex = NULL;
PFNGLGETPROGRAMRESOURCELOCATIONPROC glGetProgramResourceLocation = NULL;
PFNGLGETPROGRAMRESOURCELOCATIONINDEXPROC glGetProgramResourceLocationIndex = NULL;
PFNGLGETPROGRAMRESOURCENAMEPROC glGetProgramResourceName = NULL;
PFNGLGETPROGRAMRESOURCEFVNVPROC glGetProgramResourcefvNV = NULL;
PFNGLGETPROGRAMRESOURCEIVPROC glGetProgramResourceiv = NULL;
PFNGLGETPROGRAMSTAGEIVPROC glGetProgramStageiv = NULL;
PFNGLGETPROGRAMSTRINGARBPROC glGetProgramStringARB = NULL;
PFNGLGETPROGRAMSTRINGNVPROC glGetProgramStringNV = NULL;
PFNGLGETPROGRAMSUBROUTINEPARAMETERUIVNVPROC glGetProgramSubroutineParameteruivNV = NULL;
PFNGLGETPROGRAMIVPROC glGetProgramiv = NULL;
PFNGLGETPROGRAMIVARBPROC glGetProgramivARB = NULL;
PFNGLGETPROGRAMIVNVPROC glGetProgramivNV = NULL;
PFNGLGETQUERYBUFFEROBJECTI64VPROC glGetQueryBufferObjecti64v = NULL;
PFNGLGETQUERYBUFFEROBJECTIVPROC glGetQueryBufferObjectiv = NULL;
PFNGLGETQUERYBUFFEROBJECTUI64VPROC glGetQueryBufferObjectui64v = NULL;
PFNGLGETQUERYBUFFEROBJECTUIVPROC glGetQueryBufferObjectuiv = NULL;
PFNGLGETQUERYINDEXEDIVPROC glGetQueryIndexediv = NULL;
PFNGLGETQUERYOBJECTI64VPROC glGetQueryObjecti64v = NULL;
PFNGLGETQUERYOBJECTI64VEXTPROC glGetQueryObjecti64vEXT = NULL;
PFNGLGETQUERYOBJECTIVPROC glGetQueryObjectiv = NULL;
PFNGLGETQUERYOBJECTIVARBPROC glGetQueryObjectivARB = NULL;
PFNGLGETQUERYOBJECTUI64VPROC glGetQueryObjectui64v = NULL;
PFNGLGETQUERYOBJECTUI64VEXTPROC glGetQueryObjectui64vEXT = NULL;
PFNGLGETQUERYOBJECTUIVPROC glGetQueryObjectuiv = NULL;
PFNGLGETQUERYOBJECTUIVARBPROC glGetQueryObjectuivARB = NULL;
PFNGLGETQUERYIVPROC glGetQueryiv = NULL;
PFNGLGETQUERYIVARBPROC glGetQueryivARB = NULL;
PFNGLGETRENDERBUFFERPARAMETERIVPROC glGetRenderbufferParameteriv = NULL;
PFNGLGETRENDERBUFFERPARAMETERIVEXTPROC glGetRenderbufferParameterivEXT = NULL;
PFNGLGETSAMPLERPARAMETERIIVPROC glGetSamplerParameterIiv = NULL;
PFNGLGETSAMPLERPARAMETERIUIVPROC glGetSamplerParameterIuiv = NULL;
PFNGLGETSAMPLERPARAMETERFVPROC glGetSamplerParameterfv = NULL;
PFNGLGETSAMPLERPARAMETERIVPROC glGetSamplerParameteriv = NULL;
PFNGLGETSEMAPHOREPARAMETERIVNVPROC glGetSemaphoreParameterivNV = NULL;
PFNGLGETSEMAPHOREPARAMETERUI64VEXTPROC glGetSemaphoreParameterui64vEXT = NULL;
PFNGLGETSEPARABLEFILTERPROC glGetSeparableFilter = NULL;
PFNGLGETSEPARABLEFILTEREXTPROC glGetSeparableFilterEXT = NULL;
PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog = NULL;
PFNGLGETSHADERPRECISIONFORMATPROC glGetShaderPrecisionFormat = NULL;
PFNGLGETSHADERSOURCEPROC glGetShaderSource = NULL;
PFNGLGETSHADERSOURCEARBPROC glGetShaderSourceARB = NULL;
PFNGLGETSHADERIVPROC glGetShaderiv = NULL;
PFNGLGETSHADINGRATEIMAGEPALETTENVPROC glGetShadingRateImagePaletteNV = NULL;
PFNGLGETSHADINGRATESAMPLELOCATIONIVNVPROC glGetShadingRateSampleLocationivNV = NULL;
PFNGLGETSTAGEINDEXNVPROC glGetStageIndexNV = NULL;
PFNGLGETSTRINGPROC glGetString = NULL;
PFNGLGETSTRINGIPROC glGetStringi = NULL;
PFNGLGETSUBROUTINEINDEXPROC glGetSubroutineIndex = NULL;
PFNGLGETSUBROUTINEUNIFORMLOCATIONPROC glGetSubroutineUniformLocation = NULL;
PFNGLGETSYNCIVPROC glGetSynciv = NULL;
PFNGLGETTEXENVFVPROC glGetTexEnvfv = NULL;
PFNGLGETTEXENVIVPROC glGetTexEnviv = NULL;
PFNGLGETTEXGENDVPROC glGetTexGendv = NULL;
PFNGLGETTEXGENFVPROC glGetTexGenfv = NULL;
PFNGLGETTEXGENIVPROC glGetTexGeniv = NULL;
PFNGLGETTEXIMAGEPROC glGetTexImage = NULL;
PFNGLGETTEXLEVELPARAMETERFVPROC glGetTexLevelParameterfv = NULL;
PFNGLGETTEXLEVELPARAMETERIVPROC glGetTexLevelParameteriv = NULL;
PFNGLGETTEXPARAMETERIIVPROC glGetTexParameterIiv = NULL;
PFNGLGETTEXPARAMETERIIVEXTPROC glGetTexParameterIivEXT = NULL;
PFNGLGETTEXPARAMETERIUIVPROC glGetTexParameterIuiv = NULL;
PFNGLGETTEXPARAMETERIUIVEXTPROC glGetTexParameterIuivEXT = NULL;
PFNGLGETTEXPARAMETERPOINTERVAPPLEPROC glGetTexParameterPointervAPPLE = NULL;
PFNGLGETTEXPARAMETERFVPROC glGetTexParameterfv = NULL;
PFNGLGETTEXPARAMETERIVPROC glGetTexParameteriv = NULL;
PFNGLGETTEXTUREHANDLEARBPROC glGetTextureHandleARB = NULL;
PFNGLGETTEXTUREHANDLENVPROC glGetTextureHandleNV = NULL;
PFNGLGETTEXTUREIMAGEPROC glGetTextureImage = NULL;
PFNGLGETTEXTUREIMAGEEXTPROC glGetTextureImageEXT = NULL;
PFNGLGETTEXTURELEVELPARAMETERFVPROC glGetTextureLevelParameterfv = NULL;
PFNGLGETTEXTURELEVELPARAMETERFVEXTPROC glGetTextureLevelParameterfvEXT = NULL;
PFNGLGETTEXTURELEVELPARAMETERIVPROC glGetTextureLevelParameteriv = NULL;
PFNGLGETTEXTURELEVELPARAMETERIVEXTPROC glGetTextureLevelParameterivEXT = NULL;
PFNGLGETTEXTUREPARAMETERIIVPROC glGetTextureParameterIiv = NULL;
PFNGLGETTEXTUREPARAMETERIIVEXTPROC glGetTextureParameterIivEXT = NULL;
PFNGLGETTEXTUREPARAMETERIUIVPROC glGetTextureParameterIuiv = NULL;
PFNGLGETTEXTUREPARAMETERIUIVEXTPROC glGetTextureParameterIuivEXT = NULL;
PFNGLGETTEXTUREPARAMETERFVPROC glGetTextureParameterfv = NULL;
PFNGLGETTEXTUREPARAMETERFVEXTPROC glGetTextureParameterfvEXT = NULL;
PFNGLGETTEXTUREPARAMETERIVPROC glGetTextureParameteriv = NULL;
PFNGLGETTEXTUREPARAMETERIVEXTPROC glGetTextureParameterivEXT = NULL;
PFNGLGETTEXTURESAMPLERHANDLEARBPROC glGetTextureSamplerHandleARB = NULL;
PFNGLGETTEXTURESAMPLERHANDLENVPROC glGetTextureSamplerHandleNV = NULL;
PFNGLGETTEXTURESUBIMAGEPROC glGetTextureSubImage = NULL;
PFNGLGETTRACKMATRIXIVNVPROC glGetTrackMatrixivNV = NULL;
PFNGLGETTRANSFORMFEEDBACKVARYINGPROC glGetTransformFeedbackVarying = NULL;
PFNGLGETTRANSFORMFEEDBACKVARYINGEXTPROC glGetTransformFeedbackVaryingEXT = NULL;
PFNGLGETTRANSFORMFEEDBACKVARYINGNVPROC glGetTransformFeedbackVaryingNV = NULL;
PFNGLGETTRANSFORMFEEDBACKI64_VPROC glGetTransformFeedbacki64_v = NULL;
PFNGLGETTRANSFORMFEEDBACKI_VPROC glGetTransformFeedbacki_v = NULL;
PFNGLGETTRANSFORMFEEDBACKIVPROC glGetTransformFeedbackiv = NULL;
PFNGLGETUNIFORMBLOCKINDEXPROC glGetUniformBlockIndex = NULL;
PFNGLGETUNIFORMBUFFERSIZEEXTPROC glGetUniformBufferSizeEXT = NULL;
PFNGLGETUNIFORMINDICESPROC glGetUniformIndices = NULL;
PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation = NULL;
PFNGLGETUNIFORMLOCATIONARBPROC glGetUniformLocationARB = NULL;
PFNGLGETUNIFORMOFFSETEXTPROC glGetUniformOffsetEXT = NULL;
PFNGLGETUNIFORMSUBROUTINEUIVPROC glGetUniformSubroutineuiv = NULL;
PFNGLGETUNIFORMDVPROC glGetUniformdv = NULL;
PFNGLGETUNIFORMFVPROC glGetUniformfv = NULL;
PFNGLGETUNIFORMFVARBPROC glGetUniformfvARB = NULL;
PFNGLGETUNIFORMI64VARBPROC glGetUniformi64vARB = NULL;
PFNGLGETUNIFORMI64VNVPROC glGetUniformi64vNV = NULL;
PFNGLGETUNIFORMIVPROC glGetUniformiv = NULL;
PFNGLGETUNIFORMIVARBPROC glGetUniformivARB = NULL;
PFNGLGETUNIFORMUI64VARBPROC glGetUniformui64vARB = NULL;
PFNGLGETUNIFORMUI64VNVPROC glGetUniformui64vNV = NULL;
PFNGLGETUNIFORMUIVPROC glGetUniformuiv = NULL;
PFNGLGETUNIFORMUIVEXTPROC glGetUniformuivEXT = NULL;
PFNGLGETUNSIGNEDBYTEVEXTPROC glGetUnsignedBytevEXT = NULL;
PFNGLGETUNSIGNEDBYTEI_VEXTPROC glGetUnsignedBytei_vEXT = NULL;
PFNGLGETVARIANTBOOLEANVEXTPROC glGetVariantBooleanvEXT = NULL;
PFNGLGETVARIANTFLOATVEXTPROC glGetVariantFloatvEXT = NULL;
PFNGLGETVARIANTINTEGERVEXTPROC glGetVariantIntegervEXT = NULL;
PFNGLGETVARIANTPOINTERVEXTPROC glGetVariantPointervEXT = NULL;
PFNGLGETVARYINGLOCATIONNVPROC glGetVaryingLocationNV = NULL;
PFNGLGETVERTEXARRAYINDEXED64IVPROC glGetVertexArrayIndexed64iv = NULL;
PFNGLGETVERTEXARRAYINDEXEDIVPROC glGetVertexArrayIndexediv = NULL;
PFNGLGETVERTEXARRAYINTEGERI_VEXTPROC glGetVertexArrayIntegeri_vEXT = NULL;
PFNGLGETVERTEXARRAYINTEGERVEXTPROC glGetVertexArrayIntegervEXT = NULL;
PFNGLGETVERTEXARRAYPOINTERI_VEXTPROC glGetVertexArrayPointeri_vEXT = NULL;
PFNGLGETVERTEXARRAYPOINTERVEXTPROC glGetVertexArrayPointervEXT = NULL;
PFNGLGETVERTEXARRAYIVPROC glGetVertexArrayiv = NULL;
PFNGLGETVERTEXATTRIBIIVPROC glGetVertexAttribIiv = NULL;
PFNGLGETVERTEXATTRIBIIVEXTPROC glGetVertexAttribIivEXT = NULL;
PFNGLGETVERTEXATTRIBIUIVPROC glGetVertexAttribIuiv = NULL;
PFNGLGETVERTEXATTRIBIUIVEXTPROC glGetVertexAttribIuivEXT = NULL;
PFNGLGETVERTEXATTRIBLDVPROC glGetVertexAttribLdv = NULL;
PFNGLGETVERTEXATTRIBLDVEXTPROC glGetVertexAttribLdvEXT = NULL;
PFNGLGETVERTEXATTRIBLI64VNVPROC glGetVertexAttribLi64vNV = NULL;
PFNGLGETVERTEXATTRIBLUI64VARBPROC glGetVertexAttribLui64vARB = NULL;
PFNGLGETVERTEXATTRIBLUI64VNVPROC glGetVertexAttribLui64vNV = NULL;
PFNGLGETVERTEXATTRIBPOINTERVPROC glGetVertexAttribPointerv = NULL;
PFNGLGETVERTEXATTRIBPOINTERVARBPROC glGetVertexAttribPointervARB = NULL;
PFNGLGETVERTEXATTRIBPOINTERVNVPROC glGetVertexAttribPointervNV = NULL;
PFNGLGETVERTEXATTRIBDVPROC glGetVertexAttribdv = NULL;
PFNGLGETVERTEXATTRIBDVARBPROC glGetVertexAttribdvARB = NULL;
PFNGLGETVERTEXATTRIBDVNVPROC glGetVertexAttribdvNV = NULL;
PFNGLGETVERTEXATTRIBFVPROC glGetVertexAttribfv = NULL;
PFNGLGETVERTEXATTRIBFVARBPROC glGetVertexAttribfvARB = NULL;
PFNGLGETVERTEXATTRIBFVNVPROC glGetVertexAttribfvNV = NULL;
PFNGLGETVERTEXATTRIBIVPROC glGetVertexAttribiv = NULL;
PFNGLGETVERTEXATTRIBIVARBPROC glGetVertexAttribivARB = NULL;
PFNGLGETVERTEXATTRIBIVNVPROC glGetVertexAttribivNV = NULL;
PFNGLGETVIDEOCAPTURESTREAMDVNVPROC glGetVideoCaptureStreamdvNV = NULL;
PFNGLGETVIDEOCAPTURESTREAMFVNVPROC glGetVideoCaptureStreamfvNV = NULL;
PFNGLGETVIDEOCAPTURESTREAMIVNVPROC glGetVideoCaptureStreamivNV = NULL;
PFNGLGETVIDEOCAPTUREIVNVPROC glGetVideoCaptureivNV = NULL;
PFNGLGETVIDEOI64VNVPROC glGetVideoi64vNV = NULL;
PFNGLGETVIDEOIVNVPROC glGetVideoivNV = NULL;
PFNGLGETVIDEOUI64VNVPROC glGetVideoui64vNV = NULL;
PFNGLGETVIDEOUIVNVPROC glGetVideouivNV = NULL;
PFNGLGETNCOLORTABLEPROC glGetnColorTable = NULL;
PFNGLGETNCOLORTABLEARBPROC glGetnColorTableARB = NULL;
PFNGLGETNCOMPRESSEDTEXIMAGEPROC glGetnCompressedTexImage = NULL;
PFNGLGETNCOMPRESSEDTEXIMAGEARBPROC glGetnCompressedTexImageARB = NULL;
PFNGLGETNCONVOLUTIONFILTERPROC glGetnConvolutionFilter = NULL;
PFNGLGETNCONVOLUTIONFILTERARBPROC glGetnConvolutionFilterARB = NULL;
PFNGLGETNHISTOGRAMPROC glGetnHistogram = NULL;
PFNGLGETNHISTOGRAMARBPROC glGetnHistogramARB = NULL;
PFNGLGETNMAPDVPROC glGetnMapdv = NULL;
PFNGLGETNMAPDVARBPROC glGetnMapdvARB = NULL;
PFNGLGETNMAPFVPROC glGetnMapfv = NULL;
PFNGLGETNMAPFVARBPROC glGetnMapfvARB = NULL;
PFNGLGETNMAPIVPROC glGetnMapiv = NULL;
PFNGLGETNMAPIVARBPROC glGetnMapivARB = NULL;
PFNGLGETNMINMAXPROC glGetnMinmax = NULL;
PFNGLGETNMINMAXARBPROC glGetnMinmaxARB = NULL;
PFNGLGETNPIXELMAPFVPROC glGetnPixelMapfv = NULL;
PFNGLGETNPIXELMAPFVARBPROC glGetnPixelMapfvARB = NULL;
PFNGLGETNPIXELMAPUIVPROC glGetnPixelMapuiv = NULL;
PFNGLGETNPIXELMAPUIVARBPROC glGetnPixelMapuivARB = NULL;
PFNGLGETNPIXELMAPUSVPROC glGetnPixelMapusv = NULL;
PFNGLGETNPIXELMAPUSVARBPROC glGetnPixelMapusvARB = NULL;
PFNGLGETNPOLYGONSTIPPLEPROC glGetnPolygonStipple = NULL;
PFNGLGETNPOLYGONSTIPPLEARBPROC glGetnPolygonStippleARB = NULL;
PFNGLGETNSEPARABLEFILTERPROC glGetnSeparableFilter = NULL;
PFNGLGETNSEPARABLEFILTERARBPROC glGetnSeparableFilterARB = NULL;
PFNGLGETNTEXIMAGEPROC glGetnTexImage = NULL;
PFNGLGETNTEXIMAGEARBPROC glGetnTexImageARB = NULL;
PFNGLGETNUNIFORMDVPROC glGetnUniformdv = NULL;
PFNGLGETNUNIFORMDVARBPROC glGetnUniformdvARB = NULL;
PFNGLGETNUNIFORMFVPROC glGetnUniformfv = NULL;
PFNGLGETNUNIFORMFVARBPROC glGetnUniformfvARB = NULL;
PFNGLGETNUNIFORMFVKHRPROC glGetnUniformfvKHR = NULL;
PFNGLGETNUNIFORMI64VARBPROC glGetnUniformi64vARB = NULL;
PFNGLGETNUNIFORMIVPROC glGetnUniformiv = NULL;
PFNGLGETNUNIFORMIVARBPROC glGetnUniformivARB = NULL;
PFNGLGETNUNIFORMIVKHRPROC glGetnUniformivKHR = NULL;
PFNGLGETNUNIFORMUI64VARBPROC glGetnUniformui64vARB = NULL;
PFNGLGETNUNIFORMUIVPROC glGetnUniformuiv = NULL;
PFNGLGETNUNIFORMUIVARBPROC glGetnUniformuivARB = NULL;
PFNGLGETNUNIFORMUIVKHRPROC glGetnUniformuivKHR = NULL;
PFNGLHINTPROC glHint = NULL;
PFNGLHISTOGRAMPROC glHistogram = NULL;
PFNGLHISTOGRAMEXTPROC glHistogramEXT = NULL;
PFNGLIMPORTMEMORYFDEXTPROC glImportMemoryFdEXT = NULL;
PFNGLIMPORTMEMORYWIN32HANDLEEXTPROC glImportMemoryWin32HandleEXT = NULL;
PFNGLIMPORTMEMORYWIN32NAMEEXTPROC glImportMemoryWin32NameEXT = NULL;
PFNGLIMPORTSEMAPHOREFDEXTPROC glImportSemaphoreFdEXT = NULL;
PFNGLIMPORTSEMAPHOREWIN32HANDLEEXTPROC glImportSemaphoreWin32HandleEXT = NULL;
PFNGLIMPORTSEMAPHOREWIN32NAMEEXTPROC glImportSemaphoreWin32NameEXT = NULL;
PFNGLIMPORTSYNCEXTPROC glImportSyncEXT = NULL;
PFNGLINDEXFORMATNVPROC glIndexFormatNV = NULL;
PFNGLINDEXFUNCEXTPROC glIndexFuncEXT = NULL;
PFNGLINDEXMASKPROC glIndexMask = NULL;
PFNGLINDEXMATERIALEXTPROC glIndexMaterialEXT = NULL;
PFNGLINDEXPOINTERPROC glIndexPointer = NULL;
PFNGLINDEXPOINTEREXTPROC glIndexPointerEXT = NULL;
PFNGLINDEXDPROC glIndexd = NULL;
PFNGLINDEXDVPROC glIndexdv = NULL;
PFNGLINDEXFPROC glIndexf = NULL;
PFNGLINDEXFVPROC glIndexfv = NULL;
PFNGLINDEXIPROC glIndexi = NULL;
PFNGLINDEXIVPROC glIndexiv = NULL;
PFNGLINDEXSPROC glIndexs = NULL;
PFNGLINDEXSVPROC glIndexsv = NULL;
PFNGLINDEXUBPROC glIndexub = NULL;
PFNGLINDEXUBVPROC glIndexubv = NULL;
PFNGLINITNAMESPROC glInitNames = NULL;
PFNGLINSERTCOMPONENTEXTPROC glInsertComponentEXT = NULL;
PFNGLINSERTEVENTMARKEREXTPROC glInsertEventMarkerEXT = NULL;
PFNGLINTERLEAVEDARRAYSPROC glInterleavedArrays = NULL;
PFNGLINTERPOLATEPATHSNVPROC glInterpolatePathsNV = NULL;
PFNGLINVALIDATEBUFFERDATAPROC glInvalidateBufferData = NULL;
PFNGLINVALIDATEBUFFERSUBDATAPROC glInvalidateBufferSubData = NULL;
PFNGLINVALIDATEFRAMEBUFFERPROC glInvalidateFramebuffer = NULL;
PFNGLINVALIDATENAMEDFRAMEBUFFERDATAPROC glInvalidateNamedFramebufferData = NULL;
PFNGLINVALIDATENAMEDFRAMEBUFFERSUBDATAPROC glInvalidateNamedFramebufferSubData = NULL;
PFNGLINVALIDATESUBFRAMEBUFFERPROC glInvalidateSubFramebuffer = NULL;
PFNGLINVALIDATETEXIMAGEPROC glInvalidateTexImage = NULL;
PFNGLINVALIDATETEXSUBIMAGEPROC glInvalidateTexSubImage = NULL;
PFNGLISBUFFERPROC glIsBuffer = NULL;
PFNGLISBUFFERARBPROC glIsBufferARB = NULL;
PFNGLISBUFFERRESIDENTNVPROC glIsBufferResidentNV = NULL;
PFNGLISCOMMANDLISTNVPROC glIsCommandListNV = NULL;
PFNGLISENABLEDPROC glIsEnabled = NULL;
PFNGLISENABLEDINDEXEDEXTPROC glIsEnabledIndexedEXT = NULL;
PFNGLISENABLEDIPROC glIsEnabledi = NULL;
PFNGLISFENCEAPPLEPROC glIsFenceAPPLE = NULL;
PFNGLISFENCENVPROC glIsFenceNV = NULL;
PFNGLISFRAMEBUFFERPROC glIsFramebuffer = NULL;
PFNGLISFRAMEBUFFEREXTPROC glIsFramebufferEXT = NULL;
PFNGLISIMAGEHANDLERESIDENTARBPROC glIsImageHandleResidentARB = NULL;
PFNGLISIMAGEHANDLERESIDENTNVPROC glIsImageHandleResidentNV = NULL;
PFNGLISLISTPROC glIsList = NULL;
PFNGLISMEMORYOBJECTEXTPROC glIsMemoryObjectEXT = NULL;
PFNGLISNAMEAMDPROC glIsNameAMD = NULL;
PFNGLISNAMEDBUFFERRESIDENTNVPROC glIsNamedBufferResidentNV = NULL;
PFNGLISNAMEDSTRINGARBPROC glIsNamedStringARB = NULL;
PFNGLISOCCLUSIONQUERYNVPROC glIsOcclusionQueryNV = NULL;
PFNGLISPATHNVPROC glIsPathNV = NULL;
PFNGLISPOINTINFILLPATHNVPROC glIsPointInFillPathNV = NULL;
PFNGLISPOINTINSTROKEPATHNVPROC glIsPointInStrokePathNV = NULL;
PFNGLISPROGRAMPROC glIsProgram = NULL;
PFNGLISPROGRAMARBPROC glIsProgramARB = NULL;
PFNGLISPROGRAMNVPROC glIsProgramNV = NULL;
PFNGLISPROGRAMPIPELINEPROC glIsProgramPipeline = NULL;
PFNGLISPROGRAMPIPELINEEXTPROC glIsProgramPipelineEXT = NULL;
PFNGLISQUERYPROC glIsQuery = NULL;
PFNGLISQUERYARBPROC glIsQueryARB = NULL;
PFNGLISRENDERBUFFERPROC glIsRenderbuffer = NULL;
PFNGLISRENDERBUFFEREXTPROC glIsRenderbufferEXT = NULL;
PFNGLISSEMAPHOREEXTPROC glIsSemaphoreEXT = NULL;
PFNGLISSAMPLERPROC glIsSampler = NULL;
PFNGLISSHADERPROC glIsShader = NULL;
PFNGLISSTATENVPROC glIsStateNV = NULL;
PFNGLISSYNCPROC glIsSync = NULL;
PFNGLISTEXTUREPROC glIsTexture = NULL;
PFNGLISTEXTUREEXTPROC glIsTextureEXT = NULL;
PFNGLISTEXTUREHANDLERESIDENTARBPROC glIsTextureHandleResidentARB = NULL;
PFNGLISTEXTUREHANDLERESIDENTNVPROC glIsTextureHandleResidentNV = NULL;
PFNGLISTRANSFORMFEEDBACKPROC glIsTransformFeedback = NULL;
PFNGLISTRANSFORMFEEDBACKNVPROC glIsTransformFeedbackNV = NULL;
PFNGLISVARIANTENABLEDEXTPROC glIsVariantEnabledEXT = NULL;
PFNGLISVERTEXARRAYPROC glIsVertexArray = NULL;
PFNGLISVERTEXARRAYAPPLEPROC glIsVertexArrayAPPLE = NULL;
PFNGLISVERTEXATTRIBENABLEDAPPLEPROC glIsVertexAttribEnabledAPPLE = NULL;
PFNGLLGPUCOPYIMAGESUBDATANVXPROC glLGPUCopyImageSubDataNVX = NULL;
PFNGLLGPUINTERLOCKNVXPROC glLGPUInterlockNVX = NULL;
PFNGLLGPUNAMEDBUFFERSUBDATANVXPROC glLGPUNamedBufferSubDataNVX = NULL;
PFNGLLABELOBJECTEXTPROC glLabelObjectEXT = NULL;
PFNGLLIGHTMODELFPROC glLightModelf = NULL;
PFNGLLIGHTMODELFVPROC glLightModelfv = NULL;
PFNGLLIGHTMODELIPROC glLightModeli = NULL;
PFNGLLIGHTMODELIVPROC glLightModeliv = NULL;
PFNGLLIGHTFPROC glLightf = NULL;
PFNGLLIGHTFVPROC glLightfv = NULL;
PFNGLLIGHTIPROC glLighti = NULL;
PFNGLLIGHTIVPROC glLightiv = NULL;
PFNGLLINESTIPPLEPROC glLineStipple = NULL;
PFNGLLINEWIDTHPROC glLineWidth = NULL;
PFNGLLINKPROGRAMPROC glLinkProgram = NULL;
PFNGLLINKPROGRAMARBPROC glLinkProgramARB = NULL;
PFNGLLISTBASEPROC glListBase = NULL;
PFNGLLISTDRAWCOMMANDSSTATESCLIENTNVPROC glListDrawCommandsStatesClientNV = NULL;
PFNGLLOADIDENTITYPROC glLoadIdentity = NULL;
PFNGLLOADMATRIXDPROC glLoadMatrixd = NULL;
PFNGLLOADMATRIXFPROC glLoadMatrixf = NULL;
PFNGLLOADNAMEPROC glLoadName = NULL;
PFNGLLOADPROGRAMNVPROC glLoadProgramNV = NULL;
PFNGLLOADTRANSPOSEMATRIXDPROC glLoadTransposeMatrixd = NULL;
PFNGLLOADTRANSPOSEMATRIXDARBPROC glLoadTransposeMatrixdARB = NULL;
PFNGLLOADTRANSPOSEMATRIXFPROC glLoadTransposeMatrixf = NULL;
PFNGLLOADTRANSPOSEMATRIXFARBPROC glLoadTransposeMatrixfARB = NULL;
PFNGLLOCKARRAYSEXTPROC glLockArraysEXT = NULL;
PFNGLLOGICOPPROC glLogicOp = NULL;
PFNGLMAKEBUFFERNONRESIDENTNVPROC glMakeBufferNonResidentNV = NULL;
PFNGLMAKEBUFFERRESIDENTNVPROC glMakeBufferResidentNV = NULL;
PFNGLMAKEIMAGEHANDLENONRESIDENTARBPROC glMakeImageHandleNonResidentARB = NULL;
PFNGLMAKEIMAGEHANDLENONRESIDENTNVPROC glMakeImageHandleNonResidentNV = NULL;
PFNGLMAKEIMAGEHANDLERESIDENTARBPROC glMakeImageHandleResidentARB = NULL;
PFNGLMAKEIMAGEHANDLERESIDENTNVPROC glMakeImageHandleResidentNV = NULL;
PFNGLMAKENAMEDBUFFERNONRESIDENTNVPROC glMakeNamedBufferNonResidentNV = NULL;
PFNGLMAKENAMEDBUFFERRESIDENTNVPROC glMakeNamedBufferResidentNV = NULL;
PFNGLMAKETEXTUREHANDLENONRESIDENTARBPROC glMakeTextureHandleNonResidentARB = NULL;
PFNGLMAKETEXTUREHANDLENONRESIDENTNVPROC glMakeTextureHandleNonResidentNV = NULL;
PFNGLMAKETEXTUREHANDLERESIDENTARBPROC glMakeTextureHandleResidentARB = NULL;
PFNGLMAKETEXTUREHANDLERESIDENTNVPROC glMakeTextureHandleResidentNV = NULL;
PFNGLMAP1DPROC glMap1d = NULL;
PFNGLMAP1FPROC glMap1f = NULL;
PFNGLMAP2DPROC glMap2d = NULL;
PFNGLMAP2FPROC glMap2f = NULL;
PFNGLMAPBUFFERPROC glMapBuffer = NULL;
PFNGLMAPBUFFERARBPROC glMapBufferARB = NULL;
PFNGLMAPBUFFERRANGEPROC glMapBufferRange = NULL;
PFNGLMAPCONTROLPOINTSNVPROC glMapControlPointsNV = NULL;
PFNGLMAPGRID1DPROC glMapGrid1d = NULL;
PFNGLMAPGRID1FPROC glMapGrid1f = NULL;
PFNGLMAPGRID2DPROC glMapGrid2d = NULL;
PFNGLMAPGRID2FPROC glMapGrid2f = NULL;
PFNGLMAPNAMEDBUFFERPROC glMapNamedBuffer = NULL;
PFNGLMAPNAMEDBUFFEREXTPROC glMapNamedBufferEXT = NULL;
PFNGLMAPNAMEDBUFFERRANGEPROC glMapNamedBufferRange = NULL;
PFNGLMAPNAMEDBUFFERRANGEEXTPROC glMapNamedBufferRangeEXT = NULL;
PFNGLMAPPARAMETERFVNVPROC glMapParameterfvNV = NULL;
PFNGLMAPPARAMETERIVNVPROC glMapParameterivNV = NULL;
PFNGLMAPTEXTURE2DINTELPROC glMapTexture2DINTEL = NULL;
PFNGLMAPVERTEXATTRIB1DAPPLEPROC glMapVertexAttrib1dAPPLE = NULL;
PFNGLMAPVERTEXATTRIB1FAPPLEPROC glMapVertexAttrib1fAPPLE = NULL;
PFNGLMAPVERTEXATTRIB2DAPPLEPROC glMapVertexAttrib2dAPPLE = NULL;
PFNGLMAPVERTEXATTRIB2FAPPLEPROC glMapVertexAttrib2fAPPLE = NULL;
PFNGLMATERIALFPROC glMaterialf = NULL;
PFNGLMATERIALFVPROC glMaterialfv = NULL;
PFNGLMATERIALIPROC glMateriali = NULL;
PFNGLMATERIALIVPROC glMaterialiv = NULL;
PFNGLMATRIXFRUSTUMEXTPROC glMatrixFrustumEXT = NULL;
PFNGLMATRIXINDEXPOINTERARBPROC glMatrixIndexPointerARB = NULL;
PFNGLMATRIXINDEXUBVARBPROC glMatrixIndexubvARB = NULL;
PFNGLMATRIXINDEXUIVARBPROC glMatrixIndexuivARB = NULL;
PFNGLMATRIXINDEXUSVARBPROC glMatrixIndexusvARB = NULL;
PFNGLMATRIXLOAD3X2FNVPROC glMatrixLoad3x2fNV = NULL;
PFNGLMATRIXLOAD3X3FNVPROC glMatrixLoad3x3fNV = NULL;
PFNGLMATRIXLOADIDENTITYEXTPROC glMatrixLoadIdentityEXT = NULL;
PFNGLMATRIXLOADTRANSPOSE3X3FNVPROC glMatrixLoadTranspose3x3fNV = NULL;
PFNGLMATRIXLOADTRANSPOSEDEXTPROC glMatrixLoadTransposedEXT = NULL;
PFNGLMATRIXLOADTRANSPOSEFEXTPROC glMatrixLoadTransposefEXT = NULL;
PFNGLMATRIXLOADDEXTPROC glMatrixLoaddEXT = NULL;
PFNGLMATRIXLOADFEXTPROC glMatrixLoadfEXT = NULL;
PFNGLMATRIXMODEPROC glMatrixMode = NULL;
PFNGLMATRIXMULT3X2FNVPROC glMatrixMult3x2fNV = NULL;
PFNGLMATRIXMULT3X3FNVPROC glMatrixMult3x3fNV = NULL;
PFNGLMATRIXMULTTRANSPOSE3X3FNVPROC glMatrixMultTranspose3x3fNV = NULL;
PFNGLMATRIXMULTTRANSPOSEDEXTPROC glMatrixMultTransposedEXT = NULL;
PFNGLMATRIXMULTTRANSPOSEFEXTPROC glMatrixMultTransposefEXT = NULL;
PFNGLMATRIXMULTDEXTPROC glMatrixMultdEXT = NULL;
PFNGLMATRIXMULTFEXTPROC glMatrixMultfEXT = NULL;
PFNGLMATRIXORTHOEXTPROC glMatrixOrthoEXT = NULL;
PFNGLMATRIXPOPEXTPROC glMatrixPopEXT = NULL;
PFNGLMATRIXPUSHEXTPROC glMatrixPushEXT = NULL;
PFNGLMATRIXROTATEDEXTPROC glMatrixRotatedEXT = NULL;
PFNGLMATRIXROTATEFEXTPROC glMatrixRotatefEXT = NULL;
PFNGLMATRIXSCALEDEXTPROC glMatrixScaledEXT = NULL;
PFNGLMATRIXSCALEFEXTPROC glMatrixScalefEXT = NULL;
PFNGLMATRIXTRANSLATEDEXTPROC glMatrixTranslatedEXT = NULL;
PFNGLMATRIXTRANSLATEFEXTPROC glMatrixTranslatefEXT = NULL;
PFNGLMAXSHADERCOMPILERTHREADSKHRPROC glMaxShaderCompilerThreadsKHR = NULL;
PFNGLMAXSHADERCOMPILERTHREADSARBPROC glMaxShaderCompilerThreadsARB = NULL;
PFNGLMEMORYBARRIERPROC glMemoryBarrier = NULL;
PFNGLMEMORYBARRIERBYREGIONPROC glMemoryBarrierByRegion = NULL;
PFNGLMEMORYBARRIEREXTPROC glMemoryBarrierEXT = NULL;
PFNGLMEMORYOBJECTPARAMETERIVEXTPROC glMemoryObjectParameterivEXT = NULL;
PFNGLMINSAMPLESHADINGPROC glMinSampleShading = NULL;
PFNGLMINSAMPLESHADINGARBPROC glMinSampleShadingARB = NULL;
PFNGLMINMAXPROC glMinmax = NULL;
PFNGLMINMAXEXTPROC glMinmaxEXT = NULL;
PFNGLMULTMATRIXDPROC glMultMatrixd = NULL;
PFNGLMULTMATRIXFPROC glMultMatrixf = NULL;
PFNGLMULTTRANSPOSEMATRIXDPROC glMultTransposeMatrixd = NULL;
PFNGLMULTTRANSPOSEMATRIXDARBPROC glMultTransposeMatrixdARB = NULL;
PFNGLMULTTRANSPOSEMATRIXFPROC glMultTransposeMatrixf = NULL;
PFNGLMULTTRANSPOSEMATRIXFARBPROC glMultTransposeMatrixfARB = NULL;
PFNGLMULTIDRAWARRAYSPROC glMultiDrawArrays = NULL;
PFNGLMULTIDRAWARRAYSEXTPROC glMultiDrawArraysEXT = NULL;
PFNGLMULTIDRAWARRAYSINDIRECTPROC glMultiDrawArraysIndirect = NULL;
PFNGLMULTIDRAWARRAYSINDIRECTAMDPROC glMultiDrawArraysIndirectAMD = NULL;
PFNGLMULTIDRAWARRAYSINDIRECTBINDLESSCOUNTNVPROC glMultiDrawArraysIndirectBindlessCountNV = NULL;
PFNGLMULTIDRAWARRAYSINDIRECTBINDLESSNVPROC glMultiDrawArraysIndirectBindlessNV = NULL;
PFNGLMULTIDRAWARRAYSINDIRECTCOUNTPROC glMultiDrawArraysIndirectCount = NULL;
PFNGLMULTIDRAWARRAYSINDIRECTCOUNTARBPROC glMultiDrawArraysIndirectCountARB = NULL;
PFNGLMULTIDRAWELEMENTARRAYAPPLEPROC glMultiDrawElementArrayAPPLE = NULL;
PFNGLMULTIDRAWELEMENTSPROC glMultiDrawElements = NULL;
PFNGLMULTIDRAWELEMENTSBASEVERTEXPROC glMultiDrawElementsBaseVertex = NULL;
PFNGLMULTIDRAWELEMENTSEXTPROC glMultiDrawElementsEXT = NULL;
PFNGLMULTIDRAWELEMENTSINDIRECTPROC glMultiDrawElementsIndirect = NULL;
PFNGLMULTIDRAWELEMENTSINDIRECTAMDPROC glMultiDrawElementsIndirectAMD = NULL;
PFNGLMULTIDRAWELEMENTSINDIRECTBINDLESSCOUNTNVPROC glMultiDrawElementsIndirectBindlessCountNV =
    NULL;
PFNGLMULTIDRAWELEMENTSINDIRECTBINDLESSNVPROC glMultiDrawElementsIndirectBindlessNV = NULL;
PFNGLMULTIDRAWELEMENTSINDIRECTCOUNTPROC glMultiDrawElementsIndirectCount = NULL;
PFNGLMULTIDRAWELEMENTSINDIRECTCOUNTARBPROC glMultiDrawElementsIndirectCountARB = NULL;
PFNGLMULTIDRAWMESHTASKSINDIRECTNVPROC glMultiDrawMeshTasksIndirectNV = NULL;
PFNGLMULTIDRAWMESHTASKSINDIRECTCOUNTNVPROC glMultiDrawMeshTasksIndirectCountNV = NULL;
PFNGLMULTIDRAWRANGEELEMENTARRAYAPPLEPROC glMultiDrawRangeElementArrayAPPLE = NULL;
PFNGLMULTITEXBUFFEREXTPROC glMultiTexBufferEXT = NULL;
PFNGLMULTITEXCOORD1DPROC glMultiTexCoord1d = NULL;
PFNGLMULTITEXCOORD1DARBPROC glMultiTexCoord1dARB = NULL;
PFNGLMULTITEXCOORD1DVPROC glMultiTexCoord1dv = NULL;
PFNGLMULTITEXCOORD1DVARBPROC glMultiTexCoord1dvARB = NULL;
PFNGLMULTITEXCOORD1FPROC glMultiTexCoord1f = NULL;
PFNGLMULTITEXCOORD1FARBPROC glMultiTexCoord1fARB = NULL;
PFNGLMULTITEXCOORD1FVPROC glMultiTexCoord1fv = NULL;
PFNGLMULTITEXCOORD1FVARBPROC glMultiTexCoord1fvARB = NULL;
PFNGLMULTITEXCOORD1HNVPROC glMultiTexCoord1hNV = NULL;
PFNGLMULTITEXCOORD1HVNVPROC glMultiTexCoord1hvNV = NULL;
PFNGLMULTITEXCOORD1IPROC glMultiTexCoord1i = NULL;
PFNGLMULTITEXCOORD1IARBPROC glMultiTexCoord1iARB = NULL;
PFNGLMULTITEXCOORD1IVPROC glMultiTexCoord1iv = NULL;
PFNGLMULTITEXCOORD1IVARBPROC glMultiTexCoord1ivARB = NULL;
PFNGLMULTITEXCOORD1SPROC glMultiTexCoord1s = NULL;
PFNGLMULTITEXCOORD1SARBPROC glMultiTexCoord1sARB = NULL;
PFNGLMULTITEXCOORD1SVPROC glMultiTexCoord1sv = NULL;
PFNGLMULTITEXCOORD1SVARBPROC glMultiTexCoord1svARB = NULL;
PFNGLMULTITEXCOORD2DPROC glMultiTexCoord2d = NULL;
PFNGLMULTITEXCOORD2DARBPROC glMultiTexCoord2dARB = NULL;
PFNGLMULTITEXCOORD2DVPROC glMultiTexCoord2dv = NULL;
PFNGLMULTITEXCOORD2DVARBPROC glMultiTexCoord2dvARB = NULL;
PFNGLMULTITEXCOORD2FPROC glMultiTexCoord2f = NULL;
PFNGLMULTITEXCOORD2FARBPROC glMultiTexCoord2fARB = NULL;
PFNGLMULTITEXCOORD2FVPROC glMultiTexCoord2fv = NULL;
PFNGLMULTITEXCOORD2FVARBPROC glMultiTexCoord2fvARB = NULL;
PFNGLMULTITEXCOORD2HNVPROC glMultiTexCoord2hNV = NULL;
PFNGLMULTITEXCOORD2HVNVPROC glMultiTexCoord2hvNV = NULL;
PFNGLMULTITEXCOORD2IPROC glMultiTexCoord2i = NULL;
PFNGLMULTITEXCOORD2IARBPROC glMultiTexCoord2iARB = NULL;
PFNGLMULTITEXCOORD2IVPROC glMultiTexCoord2iv = NULL;
PFNGLMULTITEXCOORD2IVARBPROC glMultiTexCoord2ivARB = NULL;
PFNGLMULTITEXCOORD2SPROC glMultiTexCoord2s = NULL;
PFNGLMULTITEXCOORD2SARBPROC glMultiTexCoord2sARB = NULL;
PFNGLMULTITEXCOORD2SVPROC glMultiTexCoord2sv = NULL;
PFNGLMULTITEXCOORD2SVARBPROC glMultiTexCoord2svARB = NULL;
PFNGLMULTITEXCOORD3DPROC glMultiTexCoord3d = NULL;
PFNGLMULTITEXCOORD3DARBPROC glMultiTexCoord3dARB = NULL;
PFNGLMULTITEXCOORD3DVPROC glMultiTexCoord3dv = NULL;
PFNGLMULTITEXCOORD3DVARBPROC glMultiTexCoord3dvARB = NULL;
PFNGLMULTITEXCOORD3FPROC glMultiTexCoord3f = NULL;
PFNGLMULTITEXCOORD3FARBPROC glMultiTexCoord3fARB = NULL;
PFNGLMULTITEXCOORD3FVPROC glMultiTexCoord3fv = NULL;
PFNGLMULTITEXCOORD3FVARBPROC glMultiTexCoord3fvARB = NULL;
PFNGLMULTITEXCOORD3HNVPROC glMultiTexCoord3hNV = NULL;
PFNGLMULTITEXCOORD3HVNVPROC glMultiTexCoord3hvNV = NULL;
PFNGLMULTITEXCOORD3IPROC glMultiTexCoord3i = NULL;
PFNGLMULTITEXCOORD3IARBPROC glMultiTexCoord3iARB = NULL;
PFNGLMULTITEXCOORD3IVPROC glMultiTexCoord3iv = NULL;
PFNGLMULTITEXCOORD3IVARBPROC glMultiTexCoord3ivARB = NULL;
PFNGLMULTITEXCOORD3SPROC glMultiTexCoord3s = NULL;
PFNGLMULTITEXCOORD3SARBPROC glMultiTexCoord3sARB = NULL;
PFNGLMULTITEXCOORD3SVPROC glMultiTexCoord3sv = NULL;
PFNGLMULTITEXCOORD3SVARBPROC glMultiTexCoord3svARB = NULL;
PFNGLMULTITEXCOORD4DPROC glMultiTexCoord4d = NULL;
PFNGLMULTITEXCOORD4DARBPROC glMultiTexCoord4dARB = NULL;
PFNGLMULTITEXCOORD4DVPROC glMultiTexCoord4dv = NULL;
PFNGLMULTITEXCOORD4DVARBPROC glMultiTexCoord4dvARB = NULL;
PFNGLMULTITEXCOORD4FPROC glMultiTexCoord4f = NULL;
PFNGLMULTITEXCOORD4FARBPROC glMultiTexCoord4fARB = NULL;
PFNGLMULTITEXCOORD4FVPROC glMultiTexCoord4fv = NULL;
PFNGLMULTITEXCOORD4FVARBPROC glMultiTexCoord4fvARB = NULL;
PFNGLMULTITEXCOORD4HNVPROC glMultiTexCoord4hNV = NULL;
PFNGLMULTITEXCOORD4HVNVPROC glMultiTexCoord4hvNV = NULL;
PFNGLMULTITEXCOORD4IPROC glMultiTexCoord4i = NULL;
PFNGLMULTITEXCOORD4IARBPROC glMultiTexCoord4iARB = NULL;
PFNGLMULTITEXCOORD4IVPROC glMultiTexCoord4iv = NULL;
PFNGLMULTITEXCOORD4IVARBPROC glMultiTexCoord4ivARB = NULL;
PFNGLMULTITEXCOORD4SPROC glMultiTexCoord4s = NULL;
PFNGLMULTITEXCOORD4SARBPROC glMultiTexCoord4sARB = NULL;
PFNGLMULTITEXCOORD4SVPROC glMultiTexCoord4sv = NULL;
PFNGLMULTITEXCOORD4SVARBPROC glMultiTexCoord4svARB = NULL;
PFNGLMULTITEXCOORDP1UIPROC glMultiTexCoordP1ui = NULL;
PFNGLMULTITEXCOORDP1UIVPROC glMultiTexCoordP1uiv = NULL;
PFNGLMULTITEXCOORDP2UIPROC glMultiTexCoordP2ui = NULL;
PFNGLMULTITEXCOORDP2UIVPROC glMultiTexCoordP2uiv = NULL;
PFNGLMULTITEXCOORDP3UIPROC glMultiTexCoordP3ui = NULL;
PFNGLMULTITEXCOORDP3UIVPROC glMultiTexCoordP3uiv = NULL;
PFNGLMULTITEXCOORDP4UIPROC glMultiTexCoordP4ui = NULL;
PFNGLMULTITEXCOORDP4UIVPROC glMultiTexCoordP4uiv = NULL;
PFNGLMULTITEXCOORDPOINTEREXTPROC glMultiTexCoordPointerEXT = NULL;
PFNGLMULTITEXENVFEXTPROC glMultiTexEnvfEXT = NULL;
PFNGLMULTITEXENVFVEXTPROC glMultiTexEnvfvEXT = NULL;
PFNGLMULTITEXENVIEXTPROC glMultiTexEnviEXT = NULL;
PFNGLMULTITEXENVIVEXTPROC glMultiTexEnvivEXT = NULL;
PFNGLMULTITEXGENDEXTPROC glMultiTexGendEXT = NULL;
PFNGLMULTITEXGENDVEXTPROC glMultiTexGendvEXT = NULL;
PFNGLMULTITEXGENFEXTPROC glMultiTexGenfEXT = NULL;
PFNGLMULTITEXGENFVEXTPROC glMultiTexGenfvEXT = NULL;
PFNGLMULTITEXGENIEXTPROC glMultiTexGeniEXT = NULL;
PFNGLMULTITEXGENIVEXTPROC glMultiTexGenivEXT = NULL;
PFNGLMULTITEXIMAGE1DEXTPROC glMultiTexImage1DEXT = NULL;
PFNGLMULTITEXIMAGE2DEXTPROC glMultiTexImage2DEXT = NULL;
PFNGLMULTITEXIMAGE3DEXTPROC glMultiTexImage3DEXT = NULL;
PFNGLMULTITEXPARAMETERIIVEXTPROC glMultiTexParameterIivEXT = NULL;
PFNGLMULTITEXPARAMETERIUIVEXTPROC glMultiTexParameterIuivEXT = NULL;
PFNGLMULTITEXPARAMETERFEXTPROC glMultiTexParameterfEXT = NULL;
PFNGLMULTITEXPARAMETERFVEXTPROC glMultiTexParameterfvEXT = NULL;
PFNGLMULTITEXPARAMETERIEXTPROC glMultiTexParameteriEXT = NULL;
PFNGLMULTITEXPARAMETERIVEXTPROC glMultiTexParameterivEXT = NULL;
PFNGLMULTITEXRENDERBUFFEREXTPROC glMultiTexRenderbufferEXT = NULL;
PFNGLMULTITEXSUBIMAGE1DEXTPROC glMultiTexSubImage1DEXT = NULL;
PFNGLMULTITEXSUBIMAGE2DEXTPROC glMultiTexSubImage2DEXT = NULL;
PFNGLMULTITEXSUBIMAGE3DEXTPROC glMultiTexSubImage3DEXT = NULL;
PFNGLMULTICASTBARRIERNVPROC glMulticastBarrierNV = NULL;
PFNGLMULTICASTBLITFRAMEBUFFERNVPROC glMulticastBlitFramebufferNV = NULL;
PFNGLMULTICASTBUFFERSUBDATANVPROC glMulticastBufferSubDataNV = NULL;
PFNGLMULTICASTCOPYBUFFERSUBDATANVPROC glMulticastCopyBufferSubDataNV = NULL;
PFNGLMULTICASTCOPYIMAGESUBDATANVPROC glMulticastCopyImageSubDataNV = NULL;
PFNGLMULTICASTFRAMEBUFFERSAMPLELOCATIONSFVNVPROC glMulticastFramebufferSampleLocationsfvNV = NULL;
PFNGLMULTICASTGETQUERYOBJECTI64VNVPROC glMulticastGetQueryObjecti64vNV = NULL;
PFNGLMULTICASTGETQUERYOBJECTIVNVPROC glMulticastGetQueryObjectivNV = NULL;
PFNGLMULTICASTGETQUERYOBJECTUI64VNVPROC glMulticastGetQueryObjectui64vNV = NULL;
PFNGLMULTICASTGETQUERYOBJECTUIVNVPROC glMulticastGetQueryObjectuivNV = NULL;
PFNGLMULTICASTSCISSORARRAYVNVXPROC glMulticastScissorArrayvNVX = NULL;
PFNGLMULTICASTVIEWPORTARRAYVNVXPROC glMulticastViewportArrayvNVX = NULL;
PFNGLMULTICASTVIEWPORTPOSITIONWSCALENVXPROC glMulticastViewportPositionWScaleNVX = NULL;
PFNGLMULTICASTWAITSYNCNVPROC glMulticastWaitSyncNV = NULL;
PFNGLNAMEDBUFFERATTACHMEMORYNVPROC glNamedBufferAttachMemoryNV = NULL;
PFNGLNAMEDBUFFERDATAPROC glNamedBufferData = NULL;
PFNGLNAMEDBUFFERDATAEXTPROC glNamedBufferDataEXT = NULL;
PFNGLNAMEDBUFFERPAGECOMMITMENTARBPROC glNamedBufferPageCommitmentARB = NULL;
PFNGLNAMEDBUFFERPAGECOMMITMENTEXTPROC glNamedBufferPageCommitmentEXT = NULL;
PFNGLNAMEDBUFFERPAGECOMMITMENTMEMNVPROC glNamedBufferPageCommitmentMemNV = NULL;
PFNGLNAMEDBUFFERSTORAGEPROC glNamedBufferStorage = NULL;
PFNGLNAMEDBUFFERSTORAGEEXTERNALEXTPROC glNamedBufferStorageExternalEXT = NULL;
PFNGLNAMEDBUFFERSTORAGEEXTPROC glNamedBufferStorageEXT = NULL;
PFNGLNAMEDBUFFERSTORAGEMEMEXTPROC glNamedBufferStorageMemEXT = NULL;
PFNGLNAMEDBUFFERSUBDATAPROC glNamedBufferSubData = NULL;
PFNGLNAMEDBUFFERSUBDATAEXTPROC glNamedBufferSubDataEXT = NULL;
PFNGLNAMEDCOPYBUFFERSUBDATAEXTPROC glNamedCopyBufferSubDataEXT = NULL;
PFNGLNAMEDFRAMEBUFFERDRAWBUFFERPROC glNamedFramebufferDrawBuffer = NULL;
PFNGLNAMEDFRAMEBUFFERDRAWBUFFERSPROC glNamedFramebufferDrawBuffers = NULL;
PFNGLNAMEDFRAMEBUFFERPARAMETERIPROC glNamedFramebufferParameteri = NULL;
PFNGLNAMEDFRAMEBUFFERPARAMETERIEXTPROC glNamedFramebufferParameteriEXT = NULL;
PFNGLNAMEDFRAMEBUFFERREADBUFFERPROC glNamedFramebufferReadBuffer = NULL;
PFNGLNAMEDFRAMEBUFFERRENDERBUFFERPROC glNamedFramebufferRenderbuffer = NULL;
PFNGLNAMEDFRAMEBUFFERRENDERBUFFEREXTPROC glNamedFramebufferRenderbufferEXT = NULL;
PFNGLNAMEDFRAMEBUFFERSAMPLELOCATIONSFVARBPROC glNamedFramebufferSampleLocationsfvARB = NULL;
PFNGLNAMEDFRAMEBUFFERSAMPLELOCATIONSFVNVPROC glNamedFramebufferSampleLocationsfvNV = NULL;
PFNGLNAMEDFRAMEBUFFERTEXTUREPROC glNamedFramebufferTexture = NULL;
PFNGLNAMEDFRAMEBUFFERSAMPLEPOSITIONSFVAMDPROC glNamedFramebufferSamplePositionsfvAMD = NULL;
PFNGLNAMEDFRAMEBUFFERTEXTURE1DEXTPROC glNamedFramebufferTexture1DEXT = NULL;
PFNGLNAMEDFRAMEBUFFERTEXTURE2DEXTPROC glNamedFramebufferTexture2DEXT = NULL;
PFNGLNAMEDFRAMEBUFFERTEXTURE3DEXTPROC glNamedFramebufferTexture3DEXT = NULL;
PFNGLNAMEDFRAMEBUFFERTEXTUREEXTPROC glNamedFramebufferTextureEXT = NULL;
PFNGLNAMEDFRAMEBUFFERTEXTUREFACEEXTPROC glNamedFramebufferTextureFaceEXT = NULL;
PFNGLNAMEDFRAMEBUFFERTEXTURELAYERPROC glNamedFramebufferTextureLayer = NULL;
PFNGLNAMEDFRAMEBUFFERTEXTURELAYEREXTPROC glNamedFramebufferTextureLayerEXT = NULL;
PFNGLNAMEDPROGRAMLOCALPARAMETER4DEXTPROC glNamedProgramLocalParameter4dEXT = NULL;
PFNGLNAMEDPROGRAMLOCALPARAMETER4DVEXTPROC glNamedProgramLocalParameter4dvEXT = NULL;
PFNGLNAMEDPROGRAMLOCALPARAMETER4FEXTPROC glNamedProgramLocalParameter4fEXT = NULL;
PFNGLNAMEDPROGRAMLOCALPARAMETER4FVEXTPROC glNamedProgramLocalParameter4fvEXT = NULL;
PFNGLNAMEDPROGRAMLOCALPARAMETERI4IEXTPROC glNamedProgramLocalParameterI4iEXT = NULL;
PFNGLNAMEDPROGRAMLOCALPARAMETERI4IVEXTPROC glNamedProgramLocalParameterI4ivEXT = NULL;
PFNGLNAMEDPROGRAMLOCALPARAMETERI4UIEXTPROC glNamedProgramLocalParameterI4uiEXT = NULL;
PFNGLNAMEDPROGRAMLOCALPARAMETERI4UIVEXTPROC glNamedProgramLocalParameterI4uivEXT = NULL;
PFNGLNAMEDPROGRAMLOCALPARAMETERS4FVEXTPROC glNamedProgramLocalParameters4fvEXT = NULL;
PFNGLNAMEDPROGRAMLOCALPARAMETERSI4IVEXTPROC glNamedProgramLocalParametersI4ivEXT = NULL;
PFNGLNAMEDPROGRAMLOCALPARAMETERSI4UIVEXTPROC glNamedProgramLocalParametersI4uivEXT = NULL;
PFNGLNAMEDPROGRAMSTRINGEXTPROC glNamedProgramStringEXT = NULL;
PFNGLNAMEDRENDERBUFFERSTORAGEPROC glNamedRenderbufferStorage = NULL;
PFNGLNAMEDRENDERBUFFERSTORAGEEXTPROC glNamedRenderbufferStorageEXT = NULL;
PFNGLNAMEDRENDERBUFFERSTORAGEMULTISAMPLEPROC glNamedRenderbufferStorageMultisample = NULL;
PFNGLNAMEDRENDERBUFFERSTORAGEMULTISAMPLEADVANCEDAMDPROC
glNamedRenderbufferStorageMultisampleAdvancedAMD = NULL;
PFNGLNAMEDRENDERBUFFERSTORAGEMULTISAMPLECOVERAGEEXTPROC
glNamedRenderbufferStorageMultisampleCoverageEXT = NULL;
PFNGLNAMEDRENDERBUFFERSTORAGEMULTISAMPLEEXTPROC glNamedRenderbufferStorageMultisampleEXT = NULL;
PFNGLNAMEDSTRINGARBPROC glNamedStringARB = NULL;
PFNGLNEWLISTPROC glNewList = NULL;
PFNGLNORMAL3BPROC glNormal3b = NULL;
PFNGLNORMAL3BVPROC glNormal3bv = NULL;
PFNGLNORMAL3DPROC glNormal3d = NULL;
PFNGLNORMAL3DVPROC glNormal3dv = NULL;
PFNGLNORMAL3FPROC glNormal3f = NULL;
PFNGLNORMAL3FVPROC glNormal3fv = NULL;
PFNGLNORMAL3HNVPROC glNormal3hNV = NULL;
PFNGLNORMAL3HVNVPROC glNormal3hvNV = NULL;
PFNGLNORMAL3IPROC glNormal3i = NULL;
PFNGLNORMAL3IVPROC glNormal3iv = NULL;
PFNGLNORMAL3SPROC glNormal3s = NULL;
PFNGLNORMAL3SVPROC glNormal3sv = NULL;
PFNGLNORMALFORMATNVPROC glNormalFormatNV = NULL;
PFNGLNORMALP3UIPROC glNormalP3ui = NULL;
PFNGLNORMALP3UIVPROC glNormalP3uiv = NULL;
PFNGLNORMALPOINTERPROC glNormalPointer = NULL;
PFNGLNORMALPOINTEREXTPROC glNormalPointerEXT = NULL;
PFNGLNORMALPOINTERVINTELPROC glNormalPointervINTEL = NULL;
PFNGLOBJECTLABELPROC glObjectLabel = NULL;
PFNGLOBJECTLABELKHRPROC glObjectLabelKHR = NULL;
PFNGLOBJECTPTRLABELPROC glObjectPtrLabel = NULL;
PFNGLOBJECTPTRLABELKHRPROC glObjectPtrLabelKHR = NULL;
PFNGLOBJECTPURGEABLEAPPLEPROC glObjectPurgeableAPPLE = NULL;
PFNGLOBJECTUNPURGEABLEAPPLEPROC glObjectUnpurgeableAPPLE = NULL;
PFNGLORTHOPROC glOrtho = NULL;
PFNGLPASSTHROUGHPROC glPassThrough = NULL;
PFNGLPATCHPARAMETERFVPROC glPatchParameterfv = NULL;
PFNGLPATCHPARAMETERIPROC glPatchParameteri = NULL;
PFNGLPATHCOLORGENNVPROC glPathColorGenNV = NULL;
PFNGLPATHCOMMANDSNVPROC glPathCommandsNV = NULL;
PFNGLPATHCOORDSNVPROC glPathCoordsNV = NULL;
PFNGLPATHCOVERDEPTHFUNCNVPROC glPathCoverDepthFuncNV = NULL;
PFNGLPATHDASHARRAYNVPROC glPathDashArrayNV = NULL;
PFNGLPATHFOGGENNVPROC glPathFogGenNV = NULL;
PFNGLPATHGLYPHINDEXARRAYNVPROC glPathGlyphIndexArrayNV = NULL;
PFNGLPATHGLYPHINDEXRANGENVPROC glPathGlyphIndexRangeNV = NULL;
PFNGLPATHGLYPHRANGENVPROC glPathGlyphRangeNV = NULL;
PFNGLPATHGLYPHSNVPROC glPathGlyphsNV = NULL;
PFNGLPATHMEMORYGLYPHINDEXARRAYNVPROC glPathMemoryGlyphIndexArrayNV = NULL;
PFNGLPATHPARAMETERFNVPROC glPathParameterfNV = NULL;
PFNGLPATHPARAMETERFVNVPROC glPathParameterfvNV = NULL;
PFNGLPATHPARAMETERINVPROC glPathParameteriNV = NULL;
PFNGLPATHPARAMETERIVNVPROC glPathParameterivNV = NULL;
PFNGLPATHSTENCILDEPTHOFFSETNVPROC glPathStencilDepthOffsetNV = NULL;
PFNGLPATHSTENCILFUNCNVPROC glPathStencilFuncNV = NULL;
PFNGLPATHSTRINGNVPROC glPathStringNV = NULL;
PFNGLPATHSUBCOMMANDSNVPROC glPathSubCommandsNV = NULL;
PFNGLPATHSUBCOORDSNVPROC glPathSubCoordsNV = NULL;
PFNGLPATHTEXGENNVPROC glPathTexGenNV = NULL;
PFNGLPAUSETRANSFORMFEEDBACKPROC glPauseTransformFeedback = NULL;
PFNGLPAUSETRANSFORMFEEDBACKNVPROC glPauseTransformFeedbackNV = NULL;
PFNGLPIXELDATARANGENVPROC glPixelDataRangeNV = NULL;
PFNGLPIXELMAPFVPROC glPixelMapfv = NULL;
PFNGLPIXELMAPUIVPROC glPixelMapuiv = NULL;
PFNGLPIXELMAPUSVPROC glPixelMapusv = NULL;
PFNGLPIXELSTOREFPROC glPixelStoref = NULL;
PFNGLPIXELSTOREIPROC glPixelStorei = NULL;
PFNGLPIXELTRANSFERFPROC glPixelTransferf = NULL;
PFNGLPIXELTRANSFERIPROC glPixelTransferi = NULL;
PFNGLPIXELTRANSFORMPARAMETERFEXTPROC glPixelTransformParameterfEXT = NULL;
PFNGLPIXELTRANSFORMPARAMETERFVEXTPROC glPixelTransformParameterfvEXT = NULL;
PFNGLPIXELTRANSFORMPARAMETERIEXTPROC glPixelTransformParameteriEXT = NULL;
PFNGLPIXELTRANSFORMPARAMETERIVEXTPROC glPixelTransformParameterivEXT = NULL;
PFNGLPIXELZOOMPROC glPixelZoom = NULL;
PFNGLPOINTALONGPATHNVPROC glPointAlongPathNV = NULL;
PFNGLPOINTPARAMETERFPROC glPointParameterf = NULL;
PFNGLPOINTPARAMETERFARBPROC glPointParameterfARB = NULL;
PFNGLPOINTPARAMETERFEXTPROC glPointParameterfEXT = NULL;
PFNGLPOINTPARAMETERFVPROC glPointParameterfv = NULL;
PFNGLPOINTPARAMETERFVARBPROC glPointParameterfvARB = NULL;
PFNGLPOINTPARAMETERFVEXTPROC glPointParameterfvEXT = NULL;
PFNGLPOINTPARAMETERIPROC glPointParameteri = NULL;
PFNGLPOINTPARAMETERINVPROC glPointParameteriNV = NULL;
PFNGLPOINTPARAMETERIVPROC glPointParameteriv = NULL;
PFNGLPOINTPARAMETERIVNVPROC glPointParameterivNV = NULL;
PFNGLPOINTSIZEPROC glPointSize = NULL;
PFNGLPOLYGONMODEPROC glPolygonMode = NULL;
PFNGLPOLYGONOFFSETPROC glPolygonOffset = NULL;
PFNGLPOLYGONOFFSETCLAMPPROC glPolygonOffsetClamp = NULL;
PFNGLPOLYGONOFFSETCLAMPEXTPROC glPolygonOffsetClampEXT = NULL;
PFNGLPOLYGONOFFSETEXTPROC glPolygonOffsetEXT = NULL;
PFNGLPOLYGONSTIPPLEPROC glPolygonStipple = NULL;
PFNGLPOPATTRIBPROC glPopAttrib = NULL;
PFNGLPOPCLIENTATTRIBPROC glPopClientAttrib = NULL;
PFNGLPOPDEBUGGROUPPROC glPopDebugGroup = NULL;
PFNGLPOPDEBUGGROUPKHRPROC glPopDebugGroupKHR = NULL;
PFNGLPOPGROUPMARKEREXTPROC glPopGroupMarkerEXT = NULL;
PFNGLPOPMATRIXPROC glPopMatrix = NULL;
PFNGLPOPNAMEPROC glPopName = NULL;
PFNGLPRESENTFRAMEDUALFILLNVPROC glPresentFrameDualFillNV = NULL;
PFNGLPRESENTFRAMEKEYEDNVPROC glPresentFrameKeyedNV = NULL;
PFNGLPRIMITIVEBOUNDINGBOXARBPROC glPrimitiveBoundingBoxARB = NULL;
PFNGLPRIMITIVERESTARTINDEXPROC glPrimitiveRestartIndex = NULL;
PFNGLPRIMITIVERESTARTINDEXNVPROC glPrimitiveRestartIndexNV = NULL;
PFNGLPRIMITIVERESTARTNVPROC glPrimitiveRestartNV = NULL;
PFNGLPRIORITIZETEXTURESPROC glPrioritizeTextures = NULL;
PFNGLPRIORITIZETEXTURESEXTPROC glPrioritizeTexturesEXT = NULL;
PFNGLPROGRAMBINARYPROC glProgramBinary = NULL;
PFNGLPROGRAMBUFFERPARAMETERSIIVNVPROC glProgramBufferParametersIivNV = NULL;
PFNGLPROGRAMBUFFERPARAMETERSIUIVNVPROC glProgramBufferParametersIuivNV = NULL;
PFNGLPROGRAMBUFFERPARAMETERSFVNVPROC glProgramBufferParametersfvNV = NULL;
PFNGLPROGRAMENVPARAMETER4DARBPROC glProgramEnvParameter4dARB = NULL;
PFNGLPROGRAMENVPARAMETER4DVARBPROC glProgramEnvParameter4dvARB = NULL;
PFNGLPROGRAMENVPARAMETER4FARBPROC glProgramEnvParameter4fARB = NULL;
PFNGLPROGRAMENVPARAMETER4FVARBPROC glProgramEnvParameter4fvARB = NULL;
PFNGLPROGRAMENVPARAMETERI4INVPROC glProgramEnvParameterI4iNV = NULL;
PFNGLPROGRAMENVPARAMETERI4IVNVPROC glProgramEnvParameterI4ivNV = NULL;
PFNGLPROGRAMENVPARAMETERI4UINVPROC glProgramEnvParameterI4uiNV = NULL;
PFNGLPROGRAMENVPARAMETERI4UIVNVPROC glProgramEnvParameterI4uivNV = NULL;
PFNGLPROGRAMENVPARAMETERS4FVEXTPROC glProgramEnvParameters4fvEXT = NULL;
PFNGLPROGRAMENVPARAMETERSI4IVNVPROC glProgramEnvParametersI4ivNV = NULL;
PFNGLPROGRAMENVPARAMETERSI4UIVNVPROC glProgramEnvParametersI4uivNV = NULL;
PFNGLPROGRAMLOCALPARAMETER4DARBPROC glProgramLocalParameter4dARB = NULL;
PFNGLPROGRAMLOCALPARAMETER4DVARBPROC glProgramLocalParameter4dvARB = NULL;
PFNGLPROGRAMLOCALPARAMETER4FARBPROC glProgramLocalParameter4fARB = NULL;
PFNGLPROGRAMLOCALPARAMETER4FVARBPROC glProgramLocalParameter4fvARB = NULL;
PFNGLPROGRAMLOCALPARAMETERI4INVPROC glProgramLocalParameterI4iNV = NULL;
PFNGLPROGRAMLOCALPARAMETERI4IVNVPROC glProgramLocalParameterI4ivNV = NULL;
PFNGLPROGRAMLOCALPARAMETERI4UINVPROC glProgramLocalParameterI4uiNV = NULL;
PFNGLPROGRAMLOCALPARAMETERI4UIVNVPROC glProgramLocalParameterI4uivNV = NULL;
PFNGLPROGRAMLOCALPARAMETERS4FVEXTPROC glProgramLocalParameters4fvEXT = NULL;
PFNGLPROGRAMLOCALPARAMETERSI4IVNVPROC glProgramLocalParametersI4ivNV = NULL;
PFNGLPROGRAMLOCALPARAMETERSI4UIVNVPROC glProgramLocalParametersI4uivNV = NULL;
PFNGLPROGRAMNAMEDPARAMETER4DNVPROC glProgramNamedParameter4dNV = NULL;
PFNGLPROGRAMNAMEDPARAMETER4DVNVPROC glProgramNamedParameter4dvNV = NULL;
PFNGLPROGRAMNAMEDPARAMETER4FNVPROC glProgramNamedParameter4fNV = NULL;
PFNGLPROGRAMNAMEDPARAMETER4FVNVPROC glProgramNamedParameter4fvNV = NULL;
PFNGLPROGRAMPARAMETER4DNVPROC glProgramParameter4dNV = NULL;
PFNGLPROGRAMPARAMETER4DVNVPROC glProgramParameter4dvNV = NULL;
PFNGLPROGRAMPARAMETER4FNVPROC glProgramParameter4fNV = NULL;
PFNGLPROGRAMPARAMETER4FVNVPROC glProgramParameter4fvNV = NULL;
PFNGLPROGRAMPARAMETERIPROC glProgramParameteri = NULL;
PFNGLPROGRAMPARAMETERIARBPROC glProgramParameteriARB = NULL;
PFNGLPROGRAMPARAMETERIEXTPROC glProgramParameteriEXT = NULL;
PFNGLPROGRAMPARAMETERS4DVNVPROC glProgramParameters4dvNV = NULL;
PFNGLPROGRAMPARAMETERS4FVNVPROC glProgramParameters4fvNV = NULL;
PFNGLPROGRAMPATHFRAGMENTINPUTGENNVPROC glProgramPathFragmentInputGenNV = NULL;
PFNGLPROGRAMSTRINGARBPROC glProgramStringARB = NULL;
PFNGLPROGRAMSUBROUTINEPARAMETERSUIVNVPROC glProgramSubroutineParametersuivNV = NULL;
PFNGLPROGRAMUNIFORM1DPROC glProgramUniform1d = NULL;
PFNGLPROGRAMUNIFORM1DEXTPROC glProgramUniform1dEXT = NULL;
PFNGLPROGRAMUNIFORM1DVPROC glProgramUniform1dv = NULL;
PFNGLPROGRAMUNIFORM1DVEXTPROC glProgramUniform1dvEXT = NULL;
PFNGLPROGRAMUNIFORM1FPROC glProgramUniform1f = NULL;
PFNGLPROGRAMUNIFORM1FEXTPROC glProgramUniform1fEXT = NULL;
PFNGLPROGRAMUNIFORM1FVPROC glProgramUniform1fv = NULL;
PFNGLPROGRAMUNIFORM1FVEXTPROC glProgramUniform1fvEXT = NULL;
PFNGLPROGRAMUNIFORM1IPROC glProgramUniform1i = NULL;
PFNGLPROGRAMUNIFORM1I64ARBPROC glProgramUniform1i64ARB = NULL;
PFNGLPROGRAMUNIFORM1I64NVPROC glProgramUniform1i64NV = NULL;
PFNGLPROGRAMUNIFORM1I64VARBPROC glProgramUniform1i64vARB = NULL;
PFNGLPROGRAMUNIFORM1I64VNVPROC glProgramUniform1i64vNV = NULL;
PFNGLPROGRAMUNIFORM1IEXTPROC glProgramUniform1iEXT = NULL;
PFNGLPROGRAMUNIFORM1IVPROC glProgramUniform1iv = NULL;
PFNGLPROGRAMUNIFORM1IVEXTPROC glProgramUniform1ivEXT = NULL;
PFNGLPROGRAMUNIFORM1UIPROC glProgramUniform1ui = NULL;
PFNGLPROGRAMUNIFORM1UI64ARBPROC glProgramUniform1ui64ARB = NULL;
PFNGLPROGRAMUNIFORM1UI64NVPROC glProgramUniform1ui64NV = NULL;
PFNGLPROGRAMUNIFORM1UI64VARBPROC glProgramUniform1ui64vARB = NULL;
PFNGLPROGRAMUNIFORM1UI64VNVPROC glProgramUniform1ui64vNV = NULL;
PFNGLPROGRAMUNIFORM1UIEXTPROC glProgramUniform1uiEXT = NULL;
PFNGLPROGRAMUNIFORM1UIVPROC glProgramUniform1uiv = NULL;
PFNGLPROGRAMUNIFORM1UIVEXTPROC glProgramUniform1uivEXT = NULL;
PFNGLPROGRAMUNIFORM2DPROC glProgramUniform2d = NULL;
PFNGLPROGRAMUNIFORM2DEXTPROC glProgramUniform2dEXT = NULL;
PFNGLPROGRAMUNIFORM2DVPROC glProgramUniform2dv = NULL;
PFNGLPROGRAMUNIFORM2DVEXTPROC glProgramUniform2dvEXT = NULL;
PFNGLPROGRAMUNIFORM2FPROC glProgramUniform2f = NULL;
PFNGLPROGRAMUNIFORM2FEXTPROC glProgramUniform2fEXT = NULL;
PFNGLPROGRAMUNIFORM2FVPROC glProgramUniform2fv = NULL;
PFNGLPROGRAMUNIFORM2FVEXTPROC glProgramUniform2fvEXT = NULL;
PFNGLPROGRAMUNIFORM2IPROC glProgramUniform2i = NULL;
PFNGLPROGRAMUNIFORM2I64ARBPROC glProgramUniform2i64ARB = NULL;
PFNGLPROGRAMUNIFORM2I64NVPROC glProgramUniform2i64NV = NULL;
PFNGLPROGRAMUNIFORM2I64VARBPROC glProgramUniform2i64vARB = NULL;
PFNGLPROGRAMUNIFORM2I64VNVPROC glProgramUniform2i64vNV = NULL;
PFNGLPROGRAMUNIFORM2IEXTPROC glProgramUniform2iEXT = NULL;
PFNGLPROGRAMUNIFORM2IVPROC glProgramUniform2iv = NULL;
PFNGLPROGRAMUNIFORM2IVEXTPROC glProgramUniform2ivEXT = NULL;
PFNGLPROGRAMUNIFORM2UIPROC glProgramUniform2ui = NULL;
PFNGLPROGRAMUNIFORM2UI64ARBPROC glProgramUniform2ui64ARB = NULL;
PFNGLPROGRAMUNIFORM2UI64NVPROC glProgramUniform2ui64NV = NULL;
PFNGLPROGRAMUNIFORM2UI64VARBPROC glProgramUniform2ui64vARB = NULL;
PFNGLPROGRAMUNIFORM2UI64VNVPROC glProgramUniform2ui64vNV = NULL;
PFNGLPROGRAMUNIFORM2UIEXTPROC glProgramUniform2uiEXT = NULL;
PFNGLPROGRAMUNIFORM2UIVPROC glProgramUniform2uiv = NULL;
PFNGLPROGRAMUNIFORM2UIVEXTPROC glProgramUniform2uivEXT = NULL;
PFNGLPROGRAMUNIFORM3DPROC glProgramUniform3d = NULL;
PFNGLPROGRAMUNIFORM3DEXTPROC glProgramUniform3dEXT = NULL;
PFNGLPROGRAMUNIFORM3DVPROC glProgramUniform3dv = NULL;
PFNGLPROGRAMUNIFORM3DVEXTPROC glProgramUniform3dvEXT = NULL;
PFNGLPROGRAMUNIFORM3FPROC glProgramUniform3f = NULL;
PFNGLPROGRAMUNIFORM3FEXTPROC glProgramUniform3fEXT = NULL;
PFNGLPROGRAMUNIFORM3FVPROC glProgramUniform3fv = NULL;
PFNGLPROGRAMUNIFORM3FVEXTPROC glProgramUniform3fvEXT = NULL;
PFNGLPROGRAMUNIFORM3IPROC glProgramUniform3i = NULL;
PFNGLPROGRAMUNIFORM3I64ARBPROC glProgramUniform3i64ARB = NULL;
PFNGLPROGRAMUNIFORM3I64NVPROC glProgramUniform3i64NV = NULL;
PFNGLPROGRAMUNIFORM3I64VARBPROC glProgramUniform3i64vARB = NULL;
PFNGLPROGRAMUNIFORM3I64VNVPROC glProgramUniform3i64vNV = NULL;
PFNGLPROGRAMUNIFORM3IEXTPROC glProgramUniform3iEXT = NULL;
PFNGLPROGRAMUNIFORM3IVPROC glProgramUniform3iv = NULL;
PFNGLPROGRAMUNIFORM3IVEXTPROC glProgramUniform3ivEXT = NULL;
PFNGLPROGRAMUNIFORM3UIPROC glProgramUniform3ui = NULL;
PFNGLPROGRAMUNIFORM3UI64ARBPROC glProgramUniform3ui64ARB = NULL;
PFNGLPROGRAMUNIFORM3UI64NVPROC glProgramUniform3ui64NV = NULL;
PFNGLPROGRAMUNIFORM3UI64VARBPROC glProgramUniform3ui64vARB = NULL;
PFNGLPROGRAMUNIFORM3UI64VNVPROC glProgramUniform3ui64vNV = NULL;
PFNGLPROGRAMUNIFORM3UIEXTPROC glProgramUniform3uiEXT = NULL;
PFNGLPROGRAMUNIFORM3UIVPROC glProgramUniform3uiv = NULL;
PFNGLPROGRAMUNIFORM3UIVEXTPROC glProgramUniform3uivEXT = NULL;
PFNGLPROGRAMUNIFORM4DPROC glProgramUniform4d = NULL;
PFNGLPROGRAMUNIFORM4DEXTPROC glProgramUniform4dEXT = NULL;
PFNGLPROGRAMUNIFORM4DVPROC glProgramUniform4dv = NULL;
PFNGLPROGRAMUNIFORM4DVEXTPROC glProgramUniform4dvEXT = NULL;
PFNGLPROGRAMUNIFORM4FPROC glProgramUniform4f = NULL;
PFNGLPROGRAMUNIFORM4FEXTPROC glProgramUniform4fEXT = NULL;
PFNGLPROGRAMUNIFORM4FVPROC glProgramUniform4fv = NULL;
PFNGLPROGRAMUNIFORM4FVEXTPROC glProgramUniform4fvEXT = NULL;
PFNGLPROGRAMUNIFORM4IPROC glProgramUniform4i = NULL;
PFNGLPROGRAMUNIFORM4I64ARBPROC glProgramUniform4i64ARB = NULL;
PFNGLPROGRAMUNIFORM4I64NVPROC glProgramUniform4i64NV = NULL;
PFNGLPROGRAMUNIFORM4I64VARBPROC glProgramUniform4i64vARB = NULL;
PFNGLPROGRAMUNIFORM4I64VNVPROC glProgramUniform4i64vNV = NULL;
PFNGLPROGRAMUNIFORM4IEXTPROC glProgramUniform4iEXT = NULL;
PFNGLPROGRAMUNIFORM4IVPROC glProgramUniform4iv = NULL;
PFNGLPROGRAMUNIFORM4IVEXTPROC glProgramUniform4ivEXT = NULL;
PFNGLPROGRAMUNIFORM4UIPROC glProgramUniform4ui = NULL;
PFNGLPROGRAMUNIFORM4UI64ARBPROC glProgramUniform4ui64ARB = NULL;
PFNGLPROGRAMUNIFORM4UI64NVPROC glProgramUniform4ui64NV = NULL;
PFNGLPROGRAMUNIFORM4UI64VARBPROC glProgramUniform4ui64vARB = NULL;
PFNGLPROGRAMUNIFORM4UI64VNVPROC glProgramUniform4ui64vNV = NULL;
PFNGLPROGRAMUNIFORM4UIEXTPROC glProgramUniform4uiEXT = NULL;
PFNGLPROGRAMUNIFORM4UIVPROC glProgramUniform4uiv = NULL;
PFNGLPROGRAMUNIFORM4UIVEXTPROC glProgramUniform4uivEXT = NULL;
PFNGLPROGRAMUNIFORMHANDLEUI64ARBPROC glProgramUniformHandleui64ARB = NULL;
PFNGLPROGRAMUNIFORMHANDLEUI64NVPROC glProgramUniformHandleui64NV = NULL;
PFNGLPROGRAMUNIFORMHANDLEUI64VARBPROC glProgramUniformHandleui64vARB = NULL;
PFNGLPROGRAMUNIFORMHANDLEUI64VNVPROC glProgramUniformHandleui64vNV = NULL;
PFNGLPROGRAMUNIFORMMATRIX2DVPROC glProgramUniformMatrix2dv = NULL;
PFNGLPROGRAMUNIFORMMATRIX2DVEXTPROC glProgramUniformMatrix2dvEXT = NULL;
PFNGLPROGRAMUNIFORMMATRIX2FVPROC glProgramUniformMatrix2fv = NULL;
PFNGLPROGRAMUNIFORMMATRIX2FVEXTPROC glProgramUniformMatrix2fvEXT = NULL;
PFNGLPROGRAMUNIFORMMATRIX2X3DVPROC glProgramUniformMatrix2x3dv = NULL;
PFNGLPROGRAMUNIFORMMATRIX2X3DVEXTPROC glProgramUniformMatrix2x3dvEXT = NULL;
PFNGLPROGRAMUNIFORMMATRIX2X3FVPROC glProgramUniformMatrix2x3fv = NULL;
PFNGLPROGRAMUNIFORMMATRIX2X3FVEXTPROC glProgramUniformMatrix2x3fvEXT = NULL;
PFNGLPROGRAMUNIFORMMATRIX2X4DVPROC glProgramUniformMatrix2x4dv = NULL;
PFNGLPROGRAMUNIFORMMATRIX2X4DVEXTPROC glProgramUniformMatrix2x4dvEXT = NULL;
PFNGLPROGRAMUNIFORMMATRIX2X4FVPROC glProgramUniformMatrix2x4fv = NULL;
PFNGLPROGRAMUNIFORMMATRIX2X4FVEXTPROC glProgramUniformMatrix2x4fvEXT = NULL;
PFNGLPROGRAMUNIFORMMATRIX3DVPROC glProgramUniformMatrix3dv = NULL;
PFNGLPROGRAMUNIFORMMATRIX3DVEXTPROC glProgramUniformMatrix3dvEXT = NULL;
PFNGLPROGRAMUNIFORMMATRIX3FVPROC glProgramUniformMatrix3fv = NULL;
PFNGLPROGRAMUNIFORMMATRIX3FVEXTPROC glProgramUniformMatrix3fvEXT = NULL;
PFNGLPROGRAMUNIFORMMATRIX3X2DVPROC glProgramUniformMatrix3x2dv = NULL;
PFNGLPROGRAMUNIFORMMATRIX3X2DVEXTPROC glProgramUniformMatrix3x2dvEXT = NULL;
PFNGLPROGRAMUNIFORMMATRIX3X2FVPROC glProgramUniformMatrix3x2fv = NULL;
PFNGLPROGRAMUNIFORMMATRIX3X2FVEXTPROC glProgramUniformMatrix3x2fvEXT = NULL;
PFNGLPROGRAMUNIFORMMATRIX3X4DVPROC glProgramUniformMatrix3x4dv = NULL;
PFNGLPROGRAMUNIFORMMATRIX3X4DVEXTPROC glProgramUniformMatrix3x4dvEXT = NULL;
PFNGLPROGRAMUNIFORMMATRIX3X4FVPROC glProgramUniformMatrix3x4fv = NULL;
PFNGLPROGRAMUNIFORMMATRIX3X4FVEXTPROC glProgramUniformMatrix3x4fvEXT = NULL;
PFNGLPROGRAMUNIFORMMATRIX4DVPROC glProgramUniformMatrix4dv = NULL;
PFNGLPROGRAMUNIFORMMATRIX4DVEXTPROC glProgramUniformMatrix4dvEXT = NULL;
PFNGLPROGRAMUNIFORMMATRIX4FVPROC glProgramUniformMatrix4fv = NULL;
PFNGLPROGRAMUNIFORMMATRIX4FVEXTPROC glProgramUniformMatrix4fvEXT = NULL;
PFNGLPROGRAMUNIFORMMATRIX4X2DVPROC glProgramUniformMatrix4x2dv = NULL;
PFNGLPROGRAMUNIFORMMATRIX4X2DVEXTPROC glProgramUniformMatrix4x2dvEXT = NULL;
PFNGLPROGRAMUNIFORMMATRIX4X2FVPROC glProgramUniformMatrix4x2fv = NULL;
PFNGLPROGRAMUNIFORMMATRIX4X2FVEXTPROC glProgramUniformMatrix4x2fvEXT = NULL;
PFNGLPROGRAMUNIFORMMATRIX4X3DVPROC glProgramUniformMatrix4x3dv = NULL;
PFNGLPROGRAMUNIFORMMATRIX4X3DVEXTPROC glProgramUniformMatrix4x3dvEXT = NULL;
PFNGLPROGRAMUNIFORMMATRIX4X3FVPROC glProgramUniformMatrix4x3fv = NULL;
PFNGLPROGRAMUNIFORMMATRIX4X3FVEXTPROC glProgramUniformMatrix4x3fvEXT = NULL;
PFNGLPROGRAMUNIFORMUI64NVPROC glProgramUniformui64NV = NULL;
PFNGLPROGRAMUNIFORMUI64VNVPROC glProgramUniformui64vNV = NULL;
PFNGLPROGRAMVERTEXLIMITNVPROC glProgramVertexLimitNV = NULL;
PFNGLPROVOKINGVERTEXPROC glProvokingVertex = NULL;
PFNGLPROVOKINGVERTEXEXTPROC glProvokingVertexEXT = NULL;
PFNGLPUSHATTRIBPROC glPushAttrib = NULL;
PFNGLPUSHCLIENTATTRIBPROC glPushClientAttrib = NULL;
PFNGLPUSHCLIENTATTRIBDEFAULTEXTPROC glPushClientAttribDefaultEXT = NULL;
PFNGLPUSHDEBUGGROUPPROC glPushDebugGroup = NULL;
PFNGLPUSHDEBUGGROUPKHRPROC glPushDebugGroupKHR = NULL;
PFNGLPUSHGROUPMARKEREXTPROC glPushGroupMarkerEXT = NULL;
PFNGLPUSHMATRIXPROC glPushMatrix = NULL;
PFNGLPUSHNAMEPROC glPushName = NULL;
PFNGLQUERYCOUNTERPROC glQueryCounter = NULL;
PFNGLQUERYOBJECTPARAMETERUIAMDPROC glQueryObjectParameteruiAMD = NULL;
PFNGLQUERYRESOURCENVPROC glQueryResourceNV = NULL;
PFNGLQUERYRESOURCETAGNVPROC glQueryResourceTagNV = NULL;
PFNGLRASTERPOS2DPROC glRasterPos2d = NULL;
PFNGLRASTERPOS2DVPROC glRasterPos2dv = NULL;
PFNGLRASTERPOS2FPROC glRasterPos2f = NULL;
PFNGLRASTERPOS2FVPROC glRasterPos2fv = NULL;
PFNGLRASTERPOS2IPROC glRasterPos2i = NULL;
PFNGLRASTERPOS2IVPROC glRasterPos2iv = NULL;
PFNGLRASTERPOS2SPROC glRasterPos2s = NULL;
PFNGLRASTERPOS2SVPROC glRasterPos2sv = NULL;
PFNGLRASTERPOS3DPROC glRasterPos3d = NULL;
PFNGLRASTERPOS3DVPROC glRasterPos3dv = NULL;
PFNGLRASTERPOS3FPROC glRasterPos3f = NULL;
PFNGLRASTERPOS3FVPROC glRasterPos3fv = NULL;
PFNGLRASTERPOS3IPROC glRasterPos3i = NULL;
PFNGLRASTERPOS3IVPROC glRasterPos3iv = NULL;
PFNGLRASTERPOS3SPROC glRasterPos3s = NULL;
PFNGLRASTERPOS3SVPROC glRasterPos3sv = NULL;
PFNGLRASTERPOS4DPROC glRasterPos4d = NULL;
PFNGLRASTERPOS4DVPROC glRasterPos4dv = NULL;
PFNGLRASTERPOS4FPROC glRasterPos4f = NULL;
PFNGLRASTERPOS4FVPROC glRasterPos4fv = NULL;
PFNGLRASTERPOS4IPROC glRasterPos4i = NULL;
PFNGLRASTERPOS4IVPROC glRasterPos4iv = NULL;
PFNGLRASTERPOS4SPROC glRasterPos4s = NULL;
PFNGLRASTERPOS4SVPROC glRasterPos4sv = NULL;
PFNGLRASTERSAMPLESEXTPROC glRasterSamplesEXT = NULL;
PFNGLREADBUFFERPROC glReadBuffer = NULL;
PFNGLREADPIXELSPROC glReadPixels = NULL;
PFNGLREADNPIXELSPROC glReadnPixels = NULL;
PFNGLREADNPIXELSARBPROC glReadnPixelsARB = NULL;
PFNGLREADNPIXELSKHRPROC glReadnPixelsKHR = NULL;
PFNGLRELEASEKEYEDMUTEXWIN32EXTPROC glReleaseKeyedMutexWin32EXT = NULL;
PFNGLRECTDPROC glRectd = NULL;
PFNGLRECTDVPROC glRectdv = NULL;
PFNGLRECTFPROC glRectf = NULL;
PFNGLRECTFVPROC glRectfv = NULL;
PFNGLRECTIPROC glRecti = NULL;
PFNGLRECTIVPROC glRectiv = NULL;
PFNGLRECTSPROC glRects = NULL;
PFNGLRECTSVPROC glRectsv = NULL;
PFNGLRELEASESHADERCOMPILERPROC glReleaseShaderCompiler = NULL;
PFNGLRENDERGPUMASKNVPROC glRenderGpuMaskNV = NULL;
PFNGLRENDERMODEPROC glRenderMode = NULL;
PFNGLRENDERBUFFERSTORAGEPROC glRenderbufferStorage = NULL;
PFNGLRENDERBUFFERSTORAGEEXTPROC glRenderbufferStorageEXT = NULL;
PFNGLRENDERBUFFERSTORAGEMULTISAMPLEPROC glRenderbufferStorageMultisample = NULL;
PFNGLRENDERBUFFERSTORAGEMULTISAMPLEADVANCEDAMDPROC glRenderbufferStorageMultisampleAdvancedAMD =
    NULL;
PFNGLRENDERBUFFERSTORAGEMULTISAMPLECOVERAGENVPROC glRenderbufferStorageMultisampleCoverageNV =
    NULL;
PFNGLRENDERBUFFERSTORAGEMULTISAMPLEEXTPROC glRenderbufferStorageMultisampleEXT = NULL;
PFNGLREQUESTRESIDENTPROGRAMSNVPROC glRequestResidentProgramsNV = NULL;
PFNGLRESETHISTOGRAMPROC glResetHistogram = NULL;
PFNGLRESETHISTOGRAMEXTPROC glResetHistogramEXT = NULL;
PFNGLRESETMEMORYOBJECTPARAMETERNVPROC glResetMemoryObjectParameterNV = NULL;
PFNGLRESETMINMAXPROC glResetMinmax = NULL;
PFNGLRESETMINMAXEXTPROC glResetMinmaxEXT = NULL;
PFNGLRESOLVEDEPTHVALUESNVPROC glResolveDepthValuesNV = NULL;
PFNGLRESUMETRANSFORMFEEDBACKPROC glResumeTransformFeedback = NULL;
PFNGLRESUMETRANSFORMFEEDBACKNVPROC glResumeTransformFeedbackNV = NULL;
PFNGLROTATEDPROC glRotated = NULL;
PFNGLROTATEFPROC glRotatef = NULL;
PFNGLSAMPLECOVERAGEPROC glSampleCoverage = NULL;
PFNGLSAMPLECOVERAGEARBPROC glSampleCoverageARB = NULL;
PFNGLSAMPLEMASKEXTPROC glSampleMaskEXT = NULL;
PFNGLSAMPLEMASKINDEXEDNVPROC glSampleMaskIndexedNV = NULL;
PFNGLSAMPLEMASKIPROC glSampleMaski = NULL;
PFNGLSAMPLEPATTERNEXTPROC glSamplePatternEXT = NULL;
PFNGLSAMPLERPARAMETERIIVPROC glSamplerParameterIiv = NULL;
PFNGLSAMPLERPARAMETERIUIVPROC glSamplerParameterIuiv = NULL;
PFNGLSAMPLERPARAMETERFPROC glSamplerParameterf = NULL;
PFNGLSAMPLERPARAMETERFVPROC glSamplerParameterfv = NULL;
PFNGLSAMPLERPARAMETERIPROC glSamplerParameteri = NULL;
PFNGLSAMPLERPARAMETERIVPROC glSamplerParameteriv = NULL;
PFNGLSCALEDPROC glScaled = NULL;
PFNGLSCALEFPROC glScalef = NULL;
PFNGLSCISSORPROC glScissor = NULL;
PFNGLSCISSORARRAYVPROC glScissorArrayv = NULL;
PFNGLSCISSOREXCLUSIVEARRAYVNVPROC glScissorExclusiveArrayvNV = NULL;
PFNGLSCISSOREXCLUSIVENVPROC glScissorExclusiveNV = NULL;
PFNGLSCISSORINDEXEDPROC glScissorIndexed = NULL;
PFNGLSCISSORINDEXEDVPROC glScissorIndexedv = NULL;
PFNGLSECONDARYCOLOR3BPROC glSecondaryColor3b = NULL;
PFNGLSECONDARYCOLOR3BEXTPROC glSecondaryColor3bEXT = NULL;
PFNGLSECONDARYCOLOR3BVPROC glSecondaryColor3bv = NULL;
PFNGLSECONDARYCOLOR3BVEXTPROC glSecondaryColor3bvEXT = NULL;
PFNGLSECONDARYCOLOR3DPROC glSecondaryColor3d = NULL;
PFNGLSECONDARYCOLOR3DEXTPROC glSecondaryColor3dEXT = NULL;
PFNGLSECONDARYCOLOR3DVPROC glSecondaryColor3dv = NULL;
PFNGLSECONDARYCOLOR3DVEXTPROC glSecondaryColor3dvEXT = NULL;
PFNGLSECONDARYCOLOR3FPROC glSecondaryColor3f = NULL;
PFNGLSECONDARYCOLOR3FEXTPROC glSecondaryColor3fEXT = NULL;
PFNGLSECONDARYCOLOR3FVPROC glSecondaryColor3fv = NULL;
PFNGLSECONDARYCOLOR3FVEXTPROC glSecondaryColor3fvEXT = NULL;
PFNGLSECONDARYCOLOR3HNVPROC glSecondaryColor3hNV = NULL;
PFNGLSECONDARYCOLOR3HVNVPROC glSecondaryColor3hvNV = NULL;
PFNGLSECONDARYCOLOR3IPROC glSecondaryColor3i = NULL;
PFNGLSECONDARYCOLOR3IEXTPROC glSecondaryColor3iEXT = NULL;
PFNGLSECONDARYCOLOR3IVPROC glSecondaryColor3iv = NULL;
PFNGLSECONDARYCOLOR3IVEXTPROC glSecondaryColor3ivEXT = NULL;
PFNGLSECONDARYCOLOR3SPROC glSecondaryColor3s = NULL;
PFNGLSECONDARYCOLOR3SEXTPROC glSecondaryColor3sEXT = NULL;
PFNGLSECONDARYCOLOR3SVPROC glSecondaryColor3sv = NULL;
PFNGLSECONDARYCOLOR3SVEXTPROC glSecondaryColor3svEXT = NULL;
PFNGLSECONDARYCOLOR3UBPROC glSecondaryColor3ub = NULL;
PFNGLSECONDARYCOLOR3UBEXTPROC glSecondaryColor3ubEXT = NULL;
PFNGLSECONDARYCOLOR3UBVPROC glSecondaryColor3ubv = NULL;
PFNGLSECONDARYCOLOR3UBVEXTPROC glSecondaryColor3ubvEXT = NULL;
PFNGLSECONDARYCOLOR3UIPROC glSecondaryColor3ui = NULL;
PFNGLSECONDARYCOLOR3UIEXTPROC glSecondaryColor3uiEXT = NULL;
PFNGLSECONDARYCOLOR3UIVPROC glSecondaryColor3uiv = NULL;
PFNGLSECONDARYCOLOR3UIVEXTPROC glSecondaryColor3uivEXT = NULL;
PFNGLSECONDARYCOLOR3USPROC glSecondaryColor3us = NULL;
PFNGLSECONDARYCOLOR3USEXTPROC glSecondaryColor3usEXT = NULL;
PFNGLSECONDARYCOLOR3USVPROC glSecondaryColor3usv = NULL;
PFNGLSECONDARYCOLOR3USVEXTPROC glSecondaryColor3usvEXT = NULL;
PFNGLSECONDARYCOLORFORMATNVPROC glSecondaryColorFormatNV = NULL;
PFNGLSECONDARYCOLORP3UIPROC glSecondaryColorP3ui = NULL;
PFNGLSECONDARYCOLORP3UIVPROC glSecondaryColorP3uiv = NULL;
PFNGLSECONDARYCOLORPOINTERPROC glSecondaryColorPointer = NULL;
PFNGLSECONDARYCOLORPOINTEREXTPROC glSecondaryColorPointerEXT = NULL;
PFNGLSELECTBUFFERPROC glSelectBuffer = NULL;
PFNGLSELECTPERFMONITORCOUNTERSAMDPROC glSelectPerfMonitorCountersAMD = NULL;
PFNGLSEMAPHOREPARAMETERIVNVPROC glSemaphoreParameterivNV = NULL;
PFNGLSEMAPHOREPARAMETERUI64VEXTPROC glSemaphoreParameterui64vEXT = NULL;
PFNGLSEPARABLEFILTER2DPROC glSeparableFilter2D = NULL;
PFNGLSEPARABLEFILTER2DEXTPROC glSeparableFilter2DEXT = NULL;
PFNGLSETFENCEAPPLEPROC glSetFenceAPPLE = NULL;
PFNGLSETFENCENVPROC glSetFenceNV = NULL;
PFNGLSETINVARIANTEXTPROC glSetInvariantEXT = NULL;
PFNGLSETLOCALCONSTANTEXTPROC glSetLocalConstantEXT = NULL;
PFNGLSETMULTISAMPLEFVAMDPROC glSetMultisamplefvAMD = NULL;
PFNGLSHADEMODELPROC glShadeModel = NULL;
PFNGLSHADERBINARYPROC glShaderBinary = NULL;
PFNGLSHADEROP1EXTPROC glShaderOp1EXT = NULL;
PFNGLSHADEROP2EXTPROC glShaderOp2EXT = NULL;
PFNGLSHADEROP3EXTPROC glShaderOp3EXT = NULL;
PFNGLSHADERSOURCEPROC glShaderSource = NULL;
PFNGLSHADERSOURCEARBPROC glShaderSourceARB = NULL;
PFNGLSHADERSTORAGEBLOCKBINDINGPROC glShaderStorageBlockBinding = NULL;
PFNGLSHADINGRATEIMAGEBARRIERNVPROC glShadingRateImageBarrierNV = NULL;
PFNGLSHADINGRATEIMAGEPALETTENVPROC glShadingRateImagePaletteNV = NULL;
PFNGLSHADINGRATESAMPLEORDERNVPROC glShadingRateSampleOrderNV = NULL;
PFNGLSHADINGRATESAMPLEORDERCUSTOMNVPROC glShadingRateSampleOrderCustomNV = NULL;
PFNGLSIGNALSEMAPHOREEXTPROC glSignalSemaphoreEXT = NULL;
PFNGLSIGNALSEMAPHOREUI64NVXPROC glSignalSemaphoreui64NVX = NULL;
PFNGLSPECIALIZESHADERPROC glSpecializeShader = NULL;
PFNGLSPECIALIZESHADERARBPROC glSpecializeShaderARB = NULL;
PFNGLSTATECAPTURENVPROC glStateCaptureNV = NULL;
PFNGLSTENCILCLEARTAGEXTPROC glStencilClearTagEXT = NULL;
PFNGLSTENCILFILLPATHINSTANCEDNVPROC glStencilFillPathInstancedNV = NULL;
PFNGLSTENCILFILLPATHNVPROC glStencilFillPathNV = NULL;
PFNGLSTENCILFUNCPROC glStencilFunc = NULL;
PFNGLSTENCILFUNCSEPARATEPROC glStencilFuncSeparate = NULL;
PFNGLSTENCILMASKPROC glStencilMask = NULL;
PFNGLSTENCILMASKSEPARATEPROC glStencilMaskSeparate = NULL;
PFNGLSTENCILOPPROC glStencilOp = NULL;
PFNGLSTENCILOPSEPARATEPROC glStencilOpSeparate = NULL;
PFNGLSTENCILOPVALUEAMDPROC glStencilOpValueAMD = NULL;
PFNGLSTENCILSTROKEPATHINSTANCEDNVPROC glStencilStrokePathInstancedNV = NULL;
PFNGLSTENCILSTROKEPATHNVPROC glStencilStrokePathNV = NULL;
PFNGLSTENCILTHENCOVERFILLPATHINSTANCEDNVPROC glStencilThenCoverFillPathInstancedNV = NULL;
PFNGLSTENCILTHENCOVERFILLPATHNVPROC glStencilThenCoverFillPathNV = NULL;
PFNGLSTENCILTHENCOVERSTROKEPATHINSTANCEDNVPROC glStencilThenCoverStrokePathInstancedNV = NULL;
PFNGLSTENCILTHENCOVERSTROKEPATHNVPROC glStencilThenCoverStrokePathNV = NULL;
PFNGLSUBPIXELPRECISIONBIASNVPROC glSubpixelPrecisionBiasNV = NULL;
PFNGLSWIZZLEEXTPROC glSwizzleEXT = NULL;
PFNGLSYNCTEXTUREINTELPROC glSyncTextureINTEL = NULL;
PFNGLTANGENT3BEXTPROC glTangent3bEXT = NULL;
PFNGLTANGENT3BVEXTPROC glTangent3bvEXT = NULL;
PFNGLTANGENT3DEXTPROC glTangent3dEXT = NULL;
PFNGLTANGENT3DVEXTPROC glTangent3dvEXT = NULL;
PFNGLTANGENT3FEXTPROC glTangent3fEXT = NULL;
PFNGLTANGENT3FVEXTPROC glTangent3fvEXT = NULL;
PFNGLTANGENT3IEXTPROC glTangent3iEXT = NULL;
PFNGLTANGENT3IVEXTPROC glTangent3ivEXT = NULL;
PFNGLTANGENT3SEXTPROC glTangent3sEXT = NULL;
PFNGLTANGENT3SVEXTPROC glTangent3svEXT = NULL;
PFNGLTANGENTPOINTEREXTPROC glTangentPointerEXT = NULL;
PFNGLTESSELLATIONFACTORAMDPROC glTessellationFactorAMD = NULL;
PFNGLTESSELLATIONMODEAMDPROC glTessellationModeAMD = NULL;
PFNGLTESTFENCEAPPLEPROC glTestFenceAPPLE = NULL;
PFNGLTESTFENCENVPROC glTestFenceNV = NULL;
PFNGLTESTOBJECTAPPLEPROC glTestObjectAPPLE = NULL;
PFNGLTEXATTACHMEMORYNVPROC glTexAttachMemoryNV = NULL;
PFNGLTEXBUFFERPROC glTexBuffer = NULL;
PFNGLTEXBUFFERARBPROC glTexBufferARB = NULL;
PFNGLTEXBUFFEREXTPROC glTexBufferEXT = NULL;
PFNGLTEXBUFFERRANGEPROC glTexBufferRange = NULL;
PFNGLTEXCOORD1DPROC glTexCoord1d = NULL;
PFNGLTEXCOORD1DVPROC glTexCoord1dv = NULL;
PFNGLTEXCOORD1FPROC glTexCoord1f = NULL;
PFNGLTEXCOORD1FVPROC glTexCoord1fv = NULL;
PFNGLTEXCOORD1HNVPROC glTexCoord1hNV = NULL;
PFNGLTEXCOORD1HVNVPROC glTexCoord1hvNV = NULL;
PFNGLTEXCOORD1IPROC glTexCoord1i = NULL;
PFNGLTEXCOORD1IVPROC glTexCoord1iv = NULL;
PFNGLTEXCOORD1SPROC glTexCoord1s = NULL;
PFNGLTEXCOORD1SVPROC glTexCoord1sv = NULL;
PFNGLTEXCOORD2DPROC glTexCoord2d = NULL;
PFNGLTEXCOORD2DVPROC glTexCoord2dv = NULL;
PFNGLTEXCOORD2FPROC glTexCoord2f = NULL;
PFNGLTEXCOORD2FVPROC glTexCoord2fv = NULL;
PFNGLTEXCOORD2HNVPROC glTexCoord2hNV = NULL;
PFNGLTEXCOORD2HVNVPROC glTexCoord2hvNV = NULL;
PFNGLTEXCOORD2IPROC glTexCoord2i = NULL;
PFNGLTEXCOORD2IVPROC glTexCoord2iv = NULL;
PFNGLTEXCOORD2SPROC glTexCoord2s = NULL;
PFNGLTEXCOORD2SVPROC glTexCoord2sv = NULL;
PFNGLTEXCOORD3DPROC glTexCoord3d = NULL;
PFNGLTEXCOORD3DVPROC glTexCoord3dv = NULL;
PFNGLTEXCOORD3FPROC glTexCoord3f = NULL;
PFNGLTEXCOORD3FVPROC glTexCoord3fv = NULL;
PFNGLTEXCOORD3HNVPROC glTexCoord3hNV = NULL;
PFNGLTEXCOORD3HVNVPROC glTexCoord3hvNV = NULL;
PFNGLTEXCOORD3IPROC glTexCoord3i = NULL;
PFNGLTEXCOORD3IVPROC glTexCoord3iv = NULL;
PFNGLTEXCOORD3SPROC glTexCoord3s = NULL;
PFNGLTEXCOORD3SVPROC glTexCoord3sv = NULL;
PFNGLTEXCOORD4DPROC glTexCoord4d = NULL;
PFNGLTEXCOORD4DVPROC glTexCoord4dv = NULL;
PFNGLTEXCOORD4FPROC glTexCoord4f = NULL;
PFNGLTEXCOORD4FVPROC glTexCoord4fv = NULL;
PFNGLTEXCOORD4HNVPROC glTexCoord4hNV = NULL;
PFNGLTEXCOORD4HVNVPROC glTexCoord4hvNV = NULL;
PFNGLTEXCOORD4IPROC glTexCoord4i = NULL;
PFNGLTEXCOORD4IVPROC glTexCoord4iv = NULL;
PFNGLTEXCOORD4SPROC glTexCoord4s = NULL;
PFNGLTEXCOORD4SVPROC glTexCoord4sv = NULL;
PFNGLTEXCOORDFORMATNVPROC glTexCoordFormatNV = NULL;
PFNGLTEXCOORDP1UIPROC glTexCoordP1ui = NULL;
PFNGLTEXCOORDP1UIVPROC glTexCoordP1uiv = NULL;
PFNGLTEXCOORDP2UIPROC glTexCoordP2ui = NULL;
PFNGLTEXCOORDP2UIVPROC glTexCoordP2uiv = NULL;
PFNGLTEXCOORDP3UIPROC glTexCoordP3ui = NULL;
PFNGLTEXCOORDP3UIVPROC glTexCoordP3uiv = NULL;
PFNGLTEXCOORDP4UIPROC glTexCoordP4ui = NULL;
PFNGLTEXCOORDP4UIVPROC glTexCoordP4uiv = NULL;
PFNGLTEXCOORDPOINTERPROC glTexCoordPointer = NULL;
PFNGLTEXCOORDPOINTEREXTPROC glTexCoordPointerEXT = NULL;
PFNGLTEXCOORDPOINTERVINTELPROC glTexCoordPointervINTEL = NULL;
PFNGLTEXENVFPROC glTexEnvf = NULL;
PFNGLTEXENVFVPROC glTexEnvfv = NULL;
PFNGLTEXENVIPROC glTexEnvi = NULL;
PFNGLTEXENVIVPROC glTexEnviv = NULL;
PFNGLTEXGENDPROC glTexGend = NULL;
PFNGLTEXGENDVPROC glTexGendv = NULL;
PFNGLTEXGENFPROC glTexGenf = NULL;
PFNGLTEXGENFVPROC glTexGenfv = NULL;
PFNGLTEXGENIPROC glTexGeni = NULL;
PFNGLTEXGENIVPROC glTexGeniv = NULL;
PFNGLTEXIMAGE1DPROC glTexImage1D = NULL;
PFNGLTEXIMAGE2DPROC glTexImage2D = NULL;
PFNGLTEXIMAGE2DMULTISAMPLEPROC glTexImage2DMultisample = NULL;
PFNGLTEXIMAGE2DMULTISAMPLECOVERAGENVPROC glTexImage2DMultisampleCoverageNV = NULL;
PFNGLTEXIMAGE3DPROC glTexImage3D = NULL;
PFNGLTEXIMAGE3DEXTPROC glTexImage3DEXT = NULL;
PFNGLTEXIMAGE3DMULTISAMPLEPROC glTexImage3DMultisample = NULL;
PFNGLTEXIMAGE3DMULTISAMPLECOVERAGENVPROC glTexImage3DMultisampleCoverageNV = NULL;
PFNGLTEXPAGECOMMITMENTARBPROC glTexPageCommitmentARB = NULL;
PFNGLTEXPAGECOMMITMENTMEMNVPROC glTexPageCommitmentMemNV = NULL;
PFNGLTEXPARAMETERIIVPROC glTexParameterIiv = NULL;
PFNGLTEXPARAMETERIIVEXTPROC glTexParameterIivEXT = NULL;
PFNGLTEXPARAMETERIUIVPROC glTexParameterIuiv = NULL;
PFNGLTEXPARAMETERIUIVEXTPROC glTexParameterIuivEXT = NULL;
PFNGLTEXPARAMETERFPROC glTexParameterf = NULL;
PFNGLTEXPARAMETERFVPROC glTexParameterfv = NULL;
PFNGLTEXPARAMETERIPROC glTexParameteri = NULL;
PFNGLTEXPARAMETERIVPROC glTexParameteriv = NULL;
PFNGLTEXRENDERBUFFERNVPROC glTexRenderbufferNV = NULL;
PFNGLTEXSTORAGE1DPROC glTexStorage1D = NULL;
PFNGLTEXSTORAGE2DPROC glTexStorage2D = NULL;
PFNGLTEXSTORAGE2DMULTISAMPLEPROC glTexStorage2DMultisample = NULL;
PFNGLTEXSTORAGE3DPROC glTexStorage3D = NULL;
PFNGLTEXSTORAGE3DMULTISAMPLEPROC glTexStorage3DMultisample = NULL;
PFNGLTEXSTORAGEMEM1DEXTPROC glTexStorageMem1DEXT = NULL;
PFNGLTEXSTORAGEMEM2DEXTPROC glTexStorageMem2DEXT = NULL;
PFNGLTEXSTORAGEMEM2DMULTISAMPLEEXTPROC glTexStorageMem2DMultisampleEXT = NULL;
PFNGLTEXSTORAGEMEM3DEXTPROC glTexStorageMem3DEXT = NULL;
PFNGLTEXSTORAGEMEM3DMULTISAMPLEEXTPROC glTexStorageMem3DMultisampleEXT = NULL;
PFNGLTEXSTORAGESPARSEAMDPROC glTexStorageSparseAMD = NULL;
PFNGLTEXSUBIMAGE1DPROC glTexSubImage1D = NULL;
PFNGLTEXSUBIMAGE1DEXTPROC glTexSubImage1DEXT = NULL;
PFNGLTEXSUBIMAGE2DPROC glTexSubImage2D = NULL;
PFNGLTEXSUBIMAGE2DEXTPROC glTexSubImage2DEXT = NULL;
PFNGLTEXSUBIMAGE3DPROC glTexSubImage3D = NULL;
PFNGLTEXSUBIMAGE3DEXTPROC glTexSubImage3DEXT = NULL;
PFNGLTEXTUREATTACHMEMORYNVPROC glTextureAttachMemoryNV = NULL;
PFNGLTEXTUREBARRIERPROC glTextureBarrier = NULL;
PFNGLTEXTUREBARRIERNVPROC glTextureBarrierNV = NULL;
PFNGLTEXTUREBUFFERPROC glTextureBuffer = NULL;
PFNGLTEXTUREBUFFEREXTPROC glTextureBufferEXT = NULL;
PFNGLTEXTUREBUFFERRANGEPROC glTextureBufferRange = NULL;
PFNGLTEXTUREBUFFERRANGEEXTPROC glTextureBufferRangeEXT = NULL;
PFNGLTEXTUREIMAGE1DEXTPROC glTextureImage1DEXT = NULL;
PFNGLTEXTUREIMAGE2DEXTPROC glTextureImage2DEXT = NULL;
PFNGLTEXTUREIMAGE2DMULTISAMPLECOVERAGENVPROC glTextureImage2DMultisampleCoverageNV = NULL;
PFNGLTEXTUREIMAGE2DMULTISAMPLENVPROC glTextureImage2DMultisampleNV = NULL;
PFNGLTEXTUREIMAGE3DEXTPROC glTextureImage3DEXT = NULL;
PFNGLTEXTUREIMAGE3DMULTISAMPLECOVERAGENVPROC glTextureImage3DMultisampleCoverageNV = NULL;
PFNGLTEXTUREIMAGE3DMULTISAMPLENVPROC glTextureImage3DMultisampleNV = NULL;
PFNGLTEXTURELIGHTEXTPROC glTextureLightEXT = NULL;
PFNGLTEXTUREMATERIALEXTPROC glTextureMaterialEXT = NULL;
PFNGLTEXTURENORMALEXTPROC glTextureNormalEXT = NULL;
PFNGLTEXTUREPAGECOMMITMENTEXTPROC glTexturePageCommitmentEXT = NULL;
PFNGLTEXTUREPAGECOMMITMENTMEMNVPROC glTexturePageCommitmentMemNV = NULL;
PFNGLTEXTUREPARAMETERIIVPROC glTextureParameterIiv = NULL;
PFNGLTEXTUREPARAMETERIIVEXTPROC glTextureParameterIivEXT = NULL;
PFNGLTEXTUREPARAMETERIUIVPROC glTextureParameterIuiv = NULL;
PFNGLTEXTUREPARAMETERIUIVEXTPROC glTextureParameterIuivEXT = NULL;
PFNGLTEXTUREPARAMETERFPROC glTextureParameterf = NULL;
PFNGLTEXTUREPARAMETERFEXTPROC glTextureParameterfEXT = NULL;
PFNGLTEXTUREPARAMETERFVPROC glTextureParameterfv = NULL;
PFNGLTEXTUREPARAMETERFVEXTPROC glTextureParameterfvEXT = NULL;
PFNGLTEXTUREPARAMETERIPROC glTextureParameteri = NULL;
PFNGLTEXTUREPARAMETERIEXTPROC glTextureParameteriEXT = NULL;
PFNGLTEXTUREPARAMETERIVPROC glTextureParameteriv = NULL;
PFNGLTEXTUREPARAMETERIVEXTPROC glTextureParameterivEXT = NULL;
PFNGLTEXTURERANGEAPPLEPROC glTextureRangeAPPLE = NULL;
PFNGLTEXTURERENDERBUFFEREXTPROC glTextureRenderbufferEXT = NULL;
PFNGLTEXTURESTORAGE1DPROC glTextureStorage1D = NULL;
PFNGLTEXTURESTORAGE1DEXTPROC glTextureStorage1DEXT = NULL;
PFNGLTEXTURESTORAGE2DPROC glTextureStorage2D = NULL;
PFNGLTEXTURESTORAGE2DEXTPROC glTextureStorage2DEXT = NULL;
PFNGLTEXTURESTORAGE2DMULTISAMPLEPROC glTextureStorage2DMultisample = NULL;
PFNGLTEXTURESTORAGE2DMULTISAMPLEEXTPROC glTextureStorage2DMultisampleEXT = NULL;
PFNGLTEXTURESTORAGE3DPROC glTextureStorage3D = NULL;
PFNGLTEXTURESTORAGE3DEXTPROC glTextureStorage3DEXT = NULL;
PFNGLTEXTURESTORAGE3DMULTISAMPLEPROC glTextureStorage3DMultisample = NULL;
PFNGLTEXTURESTORAGE3DMULTISAMPLEEXTPROC glTextureStorage3DMultisampleEXT = NULL;
PFNGLTEXTURESTORAGEMEM1DEXTPROC glTextureStorageMem1DEXT = NULL;
PFNGLTEXTURESTORAGEMEM2DEXTPROC glTextureStorageMem2DEXT = NULL;
PFNGLTEXTURESTORAGEMEM2DMULTISAMPLEEXTPROC glTextureStorageMem2DMultisampleEXT = NULL;
PFNGLTEXTURESTORAGEMEM3DEXTPROC glTextureStorageMem3DEXT = NULL;
PFNGLTEXTURESTORAGEMEM3DMULTISAMPLEEXTPROC glTextureStorageMem3DMultisampleEXT = NULL;
PFNGLTEXTURESTORAGESPARSEAMDPROC glTextureStorageSparseAMD = NULL;
PFNGLTEXTURESUBIMAGE1DPROC glTextureSubImage1D = NULL;
PFNGLTEXTURESUBIMAGE1DEXTPROC glTextureSubImage1DEXT = NULL;
PFNGLTEXTURESUBIMAGE2DPROC glTextureSubImage2D = NULL;
PFNGLTEXTURESUBIMAGE2DEXTPROC glTextureSubImage2DEXT = NULL;
PFNGLTEXTURESUBIMAGE3DPROC glTextureSubImage3D = NULL;
PFNGLTEXTURESUBIMAGE3DEXTPROC glTextureSubImage3DEXT = NULL;
PFNGLTEXTUREVIEWPROC glTextureView = NULL;
PFNGLTRACKMATRIXNVPROC glTrackMatrixNV = NULL;
PFNGLTRANSFORMFEEDBACKATTRIBSNVPROC glTransformFeedbackAttribsNV = NULL;
PFNGLTRANSFORMFEEDBACKBUFFERBASEPROC glTransformFeedbackBufferBase = NULL;
PFNGLTRANSFORMFEEDBACKBUFFERRANGEPROC glTransformFeedbackBufferRange = NULL;
PFNGLTRANSFORMFEEDBACKSTREAMATTRIBSNVPROC glTransformFeedbackStreamAttribsNV = NULL;
PFNGLTRANSFORMFEEDBACKVARYINGSPROC glTransformFeedbackVaryings = NULL;
PFNGLTRANSFORMFEEDBACKVARYINGSEXTPROC glTransformFeedbackVaryingsEXT = NULL;
PFNGLTRANSFORMFEEDBACKVARYINGSNVPROC glTransformFeedbackVaryingsNV = NULL;
PFNGLTRANSFORMPATHNVPROC glTransformPathNV = NULL;
PFNGLTRANSLATEDPROC glTranslated = NULL;
PFNGLTRANSLATEFPROC glTranslatef = NULL;
PFNGLUNIFORM1DPROC glUniform1d = NULL;
PFNGLUNIFORM1DVPROC glUniform1dv = NULL;
PFNGLUNIFORM1FPROC glUniform1f = NULL;
PFNGLUNIFORM1FARBPROC glUniform1fARB = NULL;
PFNGLUNIFORM1FVPROC glUniform1fv = NULL;
PFNGLUNIFORM1FVARBPROC glUniform1fvARB = NULL;
PFNGLUNIFORM1IPROC glUniform1i = NULL;
PFNGLUNIFORM1I64ARBPROC glUniform1i64ARB = NULL;
PFNGLUNIFORM1I64NVPROC glUniform1i64NV = NULL;
PFNGLUNIFORM1I64VARBPROC glUniform1i64vARB = NULL;
PFNGLUNIFORM1I64VNVPROC glUniform1i64vNV = NULL;
PFNGLUNIFORM1IARBPROC glUniform1iARB = NULL;
PFNGLUNIFORM1IVPROC glUniform1iv = NULL;
PFNGLUNIFORM1IVARBPROC glUniform1ivARB = NULL;
PFNGLUNIFORM1UIPROC glUniform1ui = NULL;
PFNGLUNIFORM1UI64ARBPROC glUniform1ui64ARB = NULL;
PFNGLUNIFORM1UI64NVPROC glUniform1ui64NV = NULL;
PFNGLUNIFORM1UI64VARBPROC glUniform1ui64vARB = NULL;
PFNGLUNIFORM1UI64VNVPROC glUniform1ui64vNV = NULL;
PFNGLUNIFORM1UIEXTPROC glUniform1uiEXT = NULL;
PFNGLUNIFORM1UIVPROC glUniform1uiv = NULL;
PFNGLUNIFORM1UIVEXTPROC glUniform1uivEXT = NULL;
PFNGLUNIFORM2DPROC glUniform2d = NULL;
PFNGLUNIFORM2DVPROC glUniform2dv = NULL;
PFNGLUNIFORM2FPROC glUniform2f = NULL;
PFNGLUNIFORM2FARBPROC glUniform2fARB = NULL;
PFNGLUNIFORM2FVPROC glUniform2fv = NULL;
PFNGLUNIFORM2FVARBPROC glUniform2fvARB = NULL;
PFNGLUNIFORM2IPROC glUniform2i = NULL;
PFNGLUNIFORM2I64ARBPROC glUniform2i64ARB = NULL;
PFNGLUNIFORM2I64NVPROC glUniform2i64NV = NULL;
PFNGLUNIFORM2I64VARBPROC glUniform2i64vARB = NULL;
PFNGLUNIFORM2I64VNVPROC glUniform2i64vNV = NULL;
PFNGLUNIFORM2IARBPROC glUniform2iARB = NULL;
PFNGLUNIFORM2IVPROC glUniform2iv = NULL;
PFNGLUNIFORM2IVARBPROC glUniform2ivARB = NULL;
PFNGLUNIFORM2UIPROC glUniform2ui = NULL;
PFNGLUNIFORM2UI64ARBPROC glUniform2ui64ARB = NULL;
PFNGLUNIFORM2UI64NVPROC glUniform2ui64NV = NULL;
PFNGLUNIFORM2UI64VARBPROC glUniform2ui64vARB = NULL;
PFNGLUNIFORM2UI64VNVPROC glUniform2ui64vNV = NULL;
PFNGLUNIFORM2UIEXTPROC glUniform2uiEXT = NULL;
PFNGLUNIFORM2UIVPROC glUniform2uiv = NULL;
PFNGLUNIFORM2UIVEXTPROC glUniform2uivEXT = NULL;
PFNGLUNIFORM3DPROC glUniform3d = NULL;
PFNGLUNIFORM3DVPROC glUniform3dv = NULL;
PFNGLUNIFORM3FPROC glUniform3f = NULL;
PFNGLUNIFORM3FARBPROC glUniform3fARB = NULL;
PFNGLUNIFORM3FVPROC glUniform3fv = NULL;
PFNGLUNIFORM3FVARBPROC glUniform3fvARB = NULL;
PFNGLUNIFORM3IPROC glUniform3i = NULL;
PFNGLUNIFORM3I64ARBPROC glUniform3i64ARB = NULL;
PFNGLUNIFORM3I64NVPROC glUniform3i64NV = NULL;
PFNGLUNIFORM3I64VARBPROC glUniform3i64vARB = NULL;
PFNGLUNIFORM3I64VNVPROC glUniform3i64vNV = NULL;
PFNGLUNIFORM3IARBPROC glUniform3iARB = NULL;
PFNGLUNIFORM3IVPROC glUniform3iv = NULL;
PFNGLUNIFORM3IVARBPROC glUniform3ivARB = NULL;
PFNGLUNIFORM3UIPROC glUniform3ui = NULL;
PFNGLUNIFORM3UI64ARBPROC glUniform3ui64ARB = NULL;
PFNGLUNIFORM3UI64NVPROC glUniform3ui64NV = NULL;
PFNGLUNIFORM3UI64VARBPROC glUniform3ui64vARB = NULL;
PFNGLUNIFORM3UI64VNVPROC glUniform3ui64vNV = NULL;
PFNGLUNIFORM3UIEXTPROC glUniform3uiEXT = NULL;
PFNGLUNIFORM3UIVPROC glUniform3uiv = NULL;
PFNGLUNIFORM3UIVEXTPROC glUniform3uivEXT = NULL;
PFNGLUNIFORM4DPROC glUniform4d = NULL;
PFNGLUNIFORM4DVPROC glUniform4dv = NULL;
PFNGLUNIFORM4FPROC glUniform4f = NULL;
PFNGLUNIFORM4FARBPROC glUniform4fARB = NULL;
PFNGLUNIFORM4FVPROC glUniform4fv = NULL;
PFNGLUNIFORM4FVARBPROC glUniform4fvARB = NULL;
PFNGLUNIFORM4IPROC glUniform4i = NULL;
PFNGLUNIFORM4I64ARBPROC glUniform4i64ARB = NULL;
PFNGLUNIFORM4I64NVPROC glUniform4i64NV = NULL;
PFNGLUNIFORM4I64VARBPROC glUniform4i64vARB = NULL;
PFNGLUNIFORM4I64VNVPROC glUniform4i64vNV = NULL;
PFNGLUNIFORM4IARBPROC glUniform4iARB = NULL;
PFNGLUNIFORM4IVPROC glUniform4iv = NULL;
PFNGLUNIFORM4IVARBPROC glUniform4ivARB = NULL;
PFNGLUNIFORM4UIPROC glUniform4ui = NULL;
PFNGLUNIFORM4UI64ARBPROC glUniform4ui64ARB = NULL;
PFNGLUNIFORM4UI64NVPROC glUniform4ui64NV = NULL;
PFNGLUNIFORM4UI64VARBPROC glUniform4ui64vARB = NULL;
PFNGLUNIFORM4UI64VNVPROC glUniform4ui64vNV = NULL;
PFNGLUNIFORM4UIEXTPROC glUniform4uiEXT = NULL;
PFNGLUNIFORM4UIVPROC glUniform4uiv = NULL;
PFNGLUNIFORM4UIVEXTPROC glUniform4uivEXT = NULL;
PFNGLUNIFORMBLOCKBINDINGPROC glUniformBlockBinding = NULL;
PFNGLUNIFORMBUFFEREXTPROC glUniformBufferEXT = NULL;
PFNGLUNIFORMHANDLEUI64ARBPROC glUniformHandleui64ARB = NULL;
PFNGLUNIFORMHANDLEUI64NVPROC glUniformHandleui64NV = NULL;
PFNGLUNIFORMHANDLEUI64VARBPROC glUniformHandleui64vARB = NULL;
PFNGLUNIFORMHANDLEUI64VNVPROC glUniformHandleui64vNV = NULL;
PFNGLUNIFORMMATRIX2DVPROC glUniformMatrix2dv = NULL;
PFNGLUNIFORMMATRIX2FVPROC glUniformMatrix2fv = NULL;
PFNGLUNIFORMMATRIX2FVARBPROC glUniformMatrix2fvARB = NULL;
PFNGLUNIFORMMATRIX2X3DVPROC glUniformMatrix2x3dv = NULL;
PFNGLUNIFORMMATRIX2X3FVPROC glUniformMatrix2x3fv = NULL;
PFNGLUNIFORMMATRIX2X4DVPROC glUniformMatrix2x4dv = NULL;
PFNGLUNIFORMMATRIX2X4FVPROC glUniformMatrix2x4fv = NULL;
PFNGLUNIFORMMATRIX3DVPROC glUniformMatrix3dv = NULL;
PFNGLUNIFORMMATRIX3FVPROC glUniformMatrix3fv = NULL;
PFNGLUNIFORMMATRIX3FVARBPROC glUniformMatrix3fvARB = NULL;
PFNGLUNIFORMMATRIX3X2DVPROC glUniformMatrix3x2dv = NULL;
PFNGLUNIFORMMATRIX3X2FVPROC glUniformMatrix3x2fv = NULL;
PFNGLUNIFORMMATRIX3X4DVPROC glUniformMatrix3x4dv = NULL;
PFNGLUNIFORMMATRIX3X4FVPROC glUniformMatrix3x4fv = NULL;
PFNGLUNIFORMMATRIX4DVPROC glUniformMatrix4dv = NULL;
PFNGLUNIFORMMATRIX4FVPROC glUniformMatrix4fv = NULL;
PFNGLUNIFORMMATRIX4FVARBPROC glUniformMatrix4fvARB = NULL;
PFNGLUNIFORMMATRIX4X2DVPROC glUniformMatrix4x2dv = NULL;
PFNGLUNIFORMMATRIX4X2FVPROC glUniformMatrix4x2fv = NULL;
PFNGLUNIFORMMATRIX4X3DVPROC glUniformMatrix4x3dv = NULL;
PFNGLUNIFORMMATRIX4X3FVPROC glUniformMatrix4x3fv = NULL;
PFNGLUNIFORMSUBROUTINESUIVPROC glUniformSubroutinesuiv = NULL;
PFNGLUNIFORMUI64NVPROC glUniformui64NV = NULL;
PFNGLUNIFORMUI64VNVPROC glUniformui64vNV = NULL;
PFNGLUNLOCKARRAYSEXTPROC glUnlockArraysEXT = NULL;
PFNGLUNMAPBUFFERPROC glUnmapBuffer = NULL;
PFNGLUNMAPBUFFERARBPROC glUnmapBufferARB = NULL;
PFNGLUNMAPNAMEDBUFFERPROC glUnmapNamedBuffer = NULL;
PFNGLUNMAPNAMEDBUFFEREXTPROC glUnmapNamedBufferEXT = NULL;
PFNGLUNMAPTEXTURE2DINTELPROC glUnmapTexture2DINTEL = NULL;
PFNGLUPLOADGPUMASKNVXPROC glUploadGpuMaskNVX = NULL;
PFNGLUSEPROGRAMPROC glUseProgram = NULL;
PFNGLUSEPROGRAMOBJECTARBPROC glUseProgramObjectARB = NULL;
PFNGLUSEPROGRAMSTAGESPROC glUseProgramStages = NULL;
PFNGLUSEPROGRAMSTAGESEXTPROC glUseProgramStagesEXT = NULL;
PFNGLUSESHADERPROGRAMEXTPROC glUseShaderProgramEXT = NULL;
PFNGLVDPAUFININVPROC glVDPAUFiniNV = NULL;
PFNGLVDPAUGETSURFACEIVNVPROC glVDPAUGetSurfaceivNV = NULL;
PFNGLVDPAUINITNVPROC glVDPAUInitNV = NULL;
PFNGLVDPAUISSURFACENVPROC glVDPAUIsSurfaceNV = NULL;
PFNGLVDPAUMAPSURFACESNVPROC glVDPAUMapSurfacesNV = NULL;
PFNGLVDPAUREGISTEROUTPUTSURFACENVPROC glVDPAURegisterOutputSurfaceNV = NULL;
PFNGLVDPAUREGISTERVIDEOSURFACENVPROC glVDPAURegisterVideoSurfaceNV = NULL;
PFNGLVDPAUREGISTERVIDEOSURFACEWITHPICTURESTRUCTURENVPROC
glVDPAURegisterVideoSurfaceWithPictureStructureNV = NULL;
PFNGLVDPAUSURFACEACCESSNVPROC glVDPAUSurfaceAccessNV = NULL;
PFNGLVDPAUUNMAPSURFACESNVPROC glVDPAUUnmapSurfacesNV = NULL;
PFNGLVDPAUUNREGISTERSURFACENVPROC glVDPAUUnregisterSurfaceNV = NULL;
PFNGLVALIDATEPROGRAMPROC glValidateProgram = NULL;
PFNGLVALIDATEPROGRAMARBPROC glValidateProgramARB = NULL;
PFNGLVALIDATEPROGRAMPIPELINEPROC glValidateProgramPipeline = NULL;
PFNGLVALIDATEPROGRAMPIPELINEEXTPROC glValidateProgramPipelineEXT = NULL;
PFNGLVARIANTPOINTEREXTPROC glVariantPointerEXT = NULL;
PFNGLVARIANTBVEXTPROC glVariantbvEXT = NULL;
PFNGLVARIANTDVEXTPROC glVariantdvEXT = NULL;
PFNGLVARIANTFVEXTPROC glVariantfvEXT = NULL;
PFNGLVARIANTIVEXTPROC glVariantivEXT = NULL;
PFNGLVARIANTSVEXTPROC glVariantsvEXT = NULL;
PFNGLVARIANTUBVEXTPROC glVariantubvEXT = NULL;
PFNGLVARIANTUIVEXTPROC glVariantuivEXT = NULL;
PFNGLVARIANTUSVEXTPROC glVariantusvEXT = NULL;
PFNGLVERTEX2DPROC glVertex2d = NULL;
PFNGLVERTEX2DVPROC glVertex2dv = NULL;
PFNGLVERTEX2FPROC glVertex2f = NULL;
PFNGLVERTEX2FVPROC glVertex2fv = NULL;
PFNGLVERTEX2HNVPROC glVertex2hNV = NULL;
PFNGLVERTEX2HVNVPROC glVertex2hvNV = NULL;
PFNGLVERTEX2IPROC glVertex2i = NULL;
PFNGLVERTEX2IVPROC glVertex2iv = NULL;
PFNGLVERTEX2SPROC glVertex2s = NULL;
PFNGLVERTEX2SVPROC glVertex2sv = NULL;
PFNGLVERTEX3DPROC glVertex3d = NULL;
PFNGLVERTEX3DVPROC glVertex3dv = NULL;
PFNGLVERTEX3FPROC glVertex3f = NULL;
PFNGLVERTEX3FVPROC glVertex3fv = NULL;
PFNGLVERTEX3HNVPROC glVertex3hNV = NULL;
PFNGLVERTEX3HVNVPROC glVertex3hvNV = NULL;
PFNGLVERTEX3IPROC glVertex3i = NULL;
PFNGLVERTEX3IVPROC glVertex3iv = NULL;
PFNGLVERTEX3SPROC glVertex3s = NULL;
PFNGLVERTEX3SVPROC glVertex3sv = NULL;
PFNGLVERTEX4DPROC glVertex4d = NULL;
PFNGLVERTEX4DVPROC glVertex4dv = NULL;
PFNGLVERTEX4FPROC glVertex4f = NULL;
PFNGLVERTEX4FVPROC glVertex4fv = NULL;
PFNGLVERTEX4HNVPROC glVertex4hNV = NULL;
PFNGLVERTEX4HVNVPROC glVertex4hvNV = NULL;
PFNGLVERTEX4IPROC glVertex4i = NULL;
PFNGLVERTEX4IVPROC glVertex4iv = NULL;
PFNGLVERTEX4SPROC glVertex4s = NULL;
PFNGLVERTEX4SVPROC glVertex4sv = NULL;
PFNGLVERTEXARRAYATTRIBBINDINGPROC glVertexArrayAttribBinding = NULL;
PFNGLVERTEXARRAYATTRIBFORMATPROC glVertexArrayAttribFormat = NULL;
PFNGLVERTEXARRAYATTRIBIFORMATPROC glVertexArrayAttribIFormat = NULL;
PFNGLVERTEXARRAYATTRIBLFORMATPROC glVertexArrayAttribLFormat = NULL;
PFNGLVERTEXARRAYBINDVERTEXBUFFEREXTPROC glVertexArrayBindVertexBufferEXT = NULL;
PFNGLVERTEXARRAYBINDINGDIVISORPROC glVertexArrayBindingDivisor = NULL;
PFNGLVERTEXARRAYCOLOROFFSETEXTPROC glVertexArrayColorOffsetEXT = NULL;
PFNGLVERTEXARRAYEDGEFLAGOFFSETEXTPROC glVertexArrayEdgeFlagOffsetEXT = NULL;
PFNGLVERTEXARRAYELEMENTBUFFERPROC glVertexArrayElementBuffer = NULL;
PFNGLVERTEXARRAYFOGCOORDOFFSETEXTPROC glVertexArrayFogCoordOffsetEXT = NULL;
PFNGLVERTEXARRAYINDEXOFFSETEXTPROC glVertexArrayIndexOffsetEXT = NULL;
PFNGLVERTEXARRAYMULTITEXCOORDOFFSETEXTPROC glVertexArrayMultiTexCoordOffsetEXT = NULL;
PFNGLVERTEXARRAYNORMALOFFSETEXTPROC glVertexArrayNormalOffsetEXT = NULL;
PFNGLVERTEXARRAYPARAMETERIAPPLEPROC glVertexArrayParameteriAPPLE = NULL;
PFNGLVERTEXARRAYRANGEAPPLEPROC glVertexArrayRangeAPPLE = NULL;
PFNGLVERTEXARRAYRANGENVPROC glVertexArrayRangeNV = NULL;
PFNGLVERTEXARRAYSECONDARYCOLOROFFSETEXTPROC glVertexArraySecondaryColorOffsetEXT = NULL;
PFNGLVERTEXARRAYTEXCOORDOFFSETEXTPROC glVertexArrayTexCoordOffsetEXT = NULL;
PFNGLVERTEXARRAYVERTEXATTRIBBINDINGEXTPROC glVertexArrayVertexAttribBindingEXT = NULL;
PFNGLVERTEXARRAYVERTEXATTRIBDIVISOREXTPROC glVertexArrayVertexAttribDivisorEXT = NULL;
PFNGLVERTEXARRAYVERTEXATTRIBFORMATEXTPROC glVertexArrayVertexAttribFormatEXT = NULL;
PFNGLVERTEXARRAYVERTEXATTRIBIFORMATEXTPROC glVertexArrayVertexAttribIFormatEXT = NULL;
PFNGLVERTEXARRAYVERTEXATTRIBIOFFSETEXTPROC glVertexArrayVertexAttribIOffsetEXT = NULL;
PFNGLVERTEXARRAYVERTEXATTRIBLFORMATEXTPROC glVertexArrayVertexAttribLFormatEXT = NULL;
PFNGLVERTEXARRAYVERTEXATTRIBLOFFSETEXTPROC glVertexArrayVertexAttribLOffsetEXT = NULL;
PFNGLVERTEXARRAYVERTEXATTRIBOFFSETEXTPROC glVertexArrayVertexAttribOffsetEXT = NULL;
PFNGLVERTEXARRAYVERTEXBINDINGDIVISOREXTPROC glVertexArrayVertexBindingDivisorEXT = NULL;
PFNGLVERTEXARRAYVERTEXBUFFERPROC glVertexArrayVertexBuffer = NULL;
PFNGLVERTEXARRAYVERTEXBUFFERSPROC glVertexArrayVertexBuffers = NULL;
PFNGLVERTEXARRAYVERTEXOFFSETEXTPROC glVertexArrayVertexOffsetEXT = NULL;
PFNGLVERTEXATTRIB1DPROC glVertexAttrib1d = NULL;
PFNGLVERTEXATTRIB1DARBPROC glVertexAttrib1dARB = NULL;
PFNGLVERTEXATTRIB1DNVPROC glVertexAttrib1dNV = NULL;
PFNGLVERTEXATTRIB1DVPROC glVertexAttrib1dv = NULL;
PFNGLVERTEXATTRIB1DVARBPROC glVertexAttrib1dvARB = NULL;
PFNGLVERTEXATTRIB1DVNVPROC glVertexAttrib1dvNV = NULL;
PFNGLVERTEXATTRIB1FPROC glVertexAttrib1f = NULL;
PFNGLVERTEXATTRIB1FARBPROC glVertexAttrib1fARB = NULL;
PFNGLVERTEXATTRIB1FNVPROC glVertexAttrib1fNV = NULL;
PFNGLVERTEXATTRIB1FVPROC glVertexAttrib1fv = NULL;
PFNGLVERTEXATTRIB1FVARBPROC glVertexAttrib1fvARB = NULL;
PFNGLVERTEXATTRIB1FVNVPROC glVertexAttrib1fvNV = NULL;
PFNGLVERTEXATTRIB1HNVPROC glVertexAttrib1hNV = NULL;
PFNGLVERTEXATTRIB1HVNVPROC glVertexAttrib1hvNV = NULL;
PFNGLVERTEXATTRIB1SPROC glVertexAttrib1s = NULL;
PFNGLVERTEXATTRIB1SARBPROC glVertexAttrib1sARB = NULL;
PFNGLVERTEXATTRIB1SNVPROC glVertexAttrib1sNV = NULL;
PFNGLVERTEXATTRIB1SVPROC glVertexAttrib1sv = NULL;
PFNGLVERTEXATTRIB1SVARBPROC glVertexAttrib1svARB = NULL;
PFNGLVERTEXATTRIB1SVNVPROC glVertexAttrib1svNV = NULL;
PFNGLVERTEXATTRIB2DPROC glVertexAttrib2d = NULL;
PFNGLVERTEXATTRIB2DARBPROC glVertexAttrib2dARB = NULL;
PFNGLVERTEXATTRIB2DNVPROC glVertexAttrib2dNV = NULL;
PFNGLVERTEXATTRIB2DVPROC glVertexAttrib2dv = NULL;
PFNGLVERTEXATTRIB2DVARBPROC glVertexAttrib2dvARB = NULL;
PFNGLVERTEXATTRIB2DVNVPROC glVertexAttrib2dvNV = NULL;
PFNGLVERTEXATTRIB2FPROC glVertexAttrib2f = NULL;
PFNGLVERTEXATTRIB2FARBPROC glVertexAttrib2fARB = NULL;
PFNGLVERTEXATTRIB2FNVPROC glVertexAttrib2fNV = NULL;
PFNGLVERTEXATTRIB2FVPROC glVertexAttrib2fv = NULL;
PFNGLVERTEXATTRIB2FVARBPROC glVertexAttrib2fvARB = NULL;
PFNGLVERTEXATTRIB2FVNVPROC glVertexAttrib2fvNV = NULL;
PFNGLVERTEXATTRIB2HNVPROC glVertexAttrib2hNV = NULL;
PFNGLVERTEXATTRIB2HVNVPROC glVertexAttrib2hvNV = NULL;
PFNGLVERTEXATTRIB2SPROC glVertexAttrib2s = NULL;
PFNGLVERTEXATTRIB2SARBPROC glVertexAttrib2sARB = NULL;
PFNGLVERTEXATTRIB2SNVPROC glVertexAttrib2sNV = NULL;
PFNGLVERTEXATTRIB2SVPROC glVertexAttrib2sv = NULL;
PFNGLVERTEXATTRIB2SVARBPROC glVertexAttrib2svARB = NULL;
PFNGLVERTEXATTRIB2SVNVPROC glVertexAttrib2svNV = NULL;
PFNGLVERTEXATTRIB3DPROC glVertexAttrib3d = NULL;
PFNGLVERTEXATTRIB3DARBPROC glVertexAttrib3dARB = NULL;
PFNGLVERTEXATTRIB3DNVPROC glVertexAttrib3dNV = NULL;
PFNGLVERTEXATTRIB3DVPROC glVertexAttrib3dv = NULL;
PFNGLVERTEXATTRIB3DVARBPROC glVertexAttrib3dvARB = NULL;
PFNGLVERTEXATTRIB3DVNVPROC glVertexAttrib3dvNV = NULL;
PFNGLVERTEXATTRIB3FPROC glVertexAttrib3f = NULL;
PFNGLVERTEXATTRIB3FARBPROC glVertexAttrib3fARB = NULL;
PFNGLVERTEXATTRIB3FNVPROC glVertexAttrib3fNV = NULL;
PFNGLVERTEXATTRIB3FVPROC glVertexAttrib3fv = NULL;
PFNGLVERTEXATTRIB3FVARBPROC glVertexAttrib3fvARB = NULL;
PFNGLVERTEXATTRIB3FVNVPROC glVertexAttrib3fvNV = NULL;
PFNGLVERTEXATTRIB3HNVPROC glVertexAttrib3hNV = NULL;
PFNGLVERTEXATTRIB3HVNVPROC glVertexAttrib3hvNV = NULL;
PFNGLVERTEXATTRIB3SPROC glVertexAttrib3s = NULL;
PFNGLVERTEXATTRIB3SARBPROC glVertexAttrib3sARB = NULL;
PFNGLVERTEXATTRIB3SNVPROC glVertexAttrib3sNV = NULL;
PFNGLVERTEXATTRIB3SVPROC glVertexAttrib3sv = NULL;
PFNGLVERTEXATTRIB3SVARBPROC glVertexAttrib3svARB = NULL;
PFNGLVERTEXATTRIB3SVNVPROC glVertexAttrib3svNV = NULL;
PFNGLVERTEXATTRIB4NBVPROC glVertexAttrib4Nbv = NULL;
PFNGLVERTEXATTRIB4NBVARBPROC glVertexAttrib4NbvARB = NULL;
PFNGLVERTEXATTRIB4NIVPROC glVertexAttrib4Niv = NULL;
PFNGLVERTEXATTRIB4NIVARBPROC glVertexAttrib4NivARB = NULL;
PFNGLVERTEXATTRIB4NSVPROC glVertexAttrib4Nsv = NULL;
PFNGLVERTEXATTRIB4NSVARBPROC glVertexAttrib4NsvARB = NULL;
PFNGLVERTEXATTRIB4NUBPROC glVertexAttrib4Nub = NULL;
PFNGLVERTEXATTRIB4NUBARBPROC glVertexAttrib4NubARB = NULL;
PFNGLVERTEXATTRIB4NUBVPROC glVertexAttrib4Nubv = NULL;
PFNGLVERTEXATTRIB4NUBVARBPROC glVertexAttrib4NubvARB = NULL;
PFNGLVERTEXATTRIB4NUIVPROC glVertexAttrib4Nuiv = NULL;
PFNGLVERTEXATTRIB4NUIVARBPROC glVertexAttrib4NuivARB = NULL;
PFNGLVERTEXATTRIB4NUSVPROC glVertexAttrib4Nusv = NULL;
PFNGLVERTEXATTRIB4NUSVARBPROC glVertexAttrib4NusvARB = NULL;
PFNGLVERTEXATTRIB4BVPROC glVertexAttrib4bv = NULL;
PFNGLVERTEXATTRIB4BVARBPROC glVertexAttrib4bvARB = NULL;
PFNGLVERTEXATTRIB4DPROC glVertexAttrib4d = NULL;
PFNGLVERTEXATTRIB4DARBPROC glVertexAttrib4dARB = NULL;
PFNGLVERTEXATTRIB4DNVPROC glVertexAttrib4dNV = NULL;
PFNGLVERTEXATTRIB4DVPROC glVertexAttrib4dv = NULL;
PFNGLVERTEXATTRIB4DVARBPROC glVertexAttrib4dvARB = NULL;
PFNGLVERTEXATTRIB4DVNVPROC glVertexAttrib4dvNV = NULL;
PFNGLVERTEXATTRIB4FPROC glVertexAttrib4f = NULL;
PFNGLVERTEXATTRIB4FARBPROC glVertexAttrib4fARB = NULL;
PFNGLVERTEXATTRIB4FNVPROC glVertexAttrib4fNV = NULL;
PFNGLVERTEXATTRIB4FVPROC glVertexAttrib4fv = NULL;
PFNGLVERTEXATTRIB4FVARBPROC glVertexAttrib4fvARB = NULL;
PFNGLVERTEXATTRIB4FVNVPROC glVertexAttrib4fvNV = NULL;
PFNGLVERTEXATTRIB4HNVPROC glVertexAttrib4hNV = NULL;
PFNGLVERTEXATTRIB4HVNVPROC glVertexAttrib4hvNV = NULL;
PFNGLVERTEXATTRIB4IVPROC glVertexAttrib4iv = NULL;
PFNGLVERTEXATTRIB4IVARBPROC glVertexAttrib4ivARB = NULL;
PFNGLVERTEXATTRIB4SPROC glVertexAttrib4s = NULL;
PFNGLVERTEXATTRIB4SARBPROC glVertexAttrib4sARB = NULL;
PFNGLVERTEXATTRIB4SNVPROC glVertexAttrib4sNV = NULL;
PFNGLVERTEXATTRIB4SVPROC glVertexAttrib4sv = NULL;
PFNGLVERTEXATTRIB4SVARBPROC glVertexAttrib4svARB = NULL;
PFNGLVERTEXATTRIB4SVNVPROC glVertexAttrib4svNV = NULL;
PFNGLVERTEXATTRIB4UBNVPROC glVertexAttrib4ubNV = NULL;
PFNGLVERTEXATTRIB4UBVPROC glVertexAttrib4ubv = NULL;
PFNGLVERTEXATTRIB4UBVARBPROC glVertexAttrib4ubvARB = NULL;
PFNGLVERTEXATTRIB4UBVNVPROC glVertexAttrib4ubvNV = NULL;
PFNGLVERTEXATTRIB4UIVPROC glVertexAttrib4uiv = NULL;
PFNGLVERTEXATTRIB4UIVARBPROC glVertexAttrib4uivARB = NULL;
PFNGLVERTEXATTRIB4USVPROC glVertexAttrib4usv = NULL;
PFNGLVERTEXATTRIB4USVARBPROC glVertexAttrib4usvARB = NULL;
PFNGLVERTEXATTRIBBINDINGPROC glVertexAttribBinding = NULL;
PFNGLVERTEXATTRIBDIVISORPROC glVertexAttribDivisor = NULL;
PFNGLVERTEXATTRIBDIVISORARBPROC glVertexAttribDivisorARB = NULL;
PFNGLVERTEXATTRIBFORMATPROC glVertexAttribFormat = NULL;
PFNGLVERTEXATTRIBFORMATNVPROC glVertexAttribFormatNV = NULL;
PFNGLVERTEXATTRIBI1IPROC glVertexAttribI1i = NULL;
PFNGLVERTEXATTRIBI1IEXTPROC glVertexAttribI1iEXT = NULL;
PFNGLVERTEXATTRIBI1IVPROC glVertexAttribI1iv = NULL;
PFNGLVERTEXATTRIBI1IVEXTPROC glVertexAttribI1ivEXT = NULL;
PFNGLVERTEXATTRIBI1UIPROC glVertexAttribI1ui = NULL;
PFNGLVERTEXATTRIBI1UIEXTPROC glVertexAttribI1uiEXT = NULL;
PFNGLVERTEXATTRIBI1UIVPROC glVertexAttribI1uiv = NULL;
PFNGLVERTEXATTRIBI1UIVEXTPROC glVertexAttribI1uivEXT = NULL;
PFNGLVERTEXATTRIBI2IPROC glVertexAttribI2i = NULL;
PFNGLVERTEXATTRIBI2IEXTPROC glVertexAttribI2iEXT = NULL;
PFNGLVERTEXATTRIBI2IVPROC glVertexAttribI2iv = NULL;
PFNGLVERTEXATTRIBI2IVEXTPROC glVertexAttribI2ivEXT = NULL;
PFNGLVERTEXATTRIBI2UIPROC glVertexAttribI2ui = NULL;
PFNGLVERTEXATTRIBI2UIEXTPROC glVertexAttribI2uiEXT = NULL;
PFNGLVERTEXATTRIBI2UIVPROC glVertexAttribI2uiv = NULL;
PFNGLVERTEXATTRIBI2UIVEXTPROC glVertexAttribI2uivEXT = NULL;
PFNGLVERTEXATTRIBI3IPROC glVertexAttribI3i = NULL;
PFNGLVERTEXATTRIBI3IEXTPROC glVertexAttribI3iEXT = NULL;
PFNGLVERTEXATTRIBI3IVPROC glVertexAttribI3iv = NULL;
PFNGLVERTEXATTRIBI3IVEXTPROC glVertexAttribI3ivEXT = NULL;
PFNGLVERTEXATTRIBI3UIPROC glVertexAttribI3ui = NULL;
PFNGLVERTEXATTRIBI3UIEXTPROC glVertexAttribI3uiEXT = NULL;
PFNGLVERTEXATTRIBI3UIVPROC glVertexAttribI3uiv = NULL;
PFNGLVERTEXATTRIBI3UIVEXTPROC glVertexAttribI3uivEXT = NULL;
PFNGLVERTEXATTRIBI4BVPROC glVertexAttribI4bv = NULL;
PFNGLVERTEXATTRIBI4BVEXTPROC glVertexAttribI4bvEXT = NULL;
PFNGLVERTEXATTRIBI4IPROC glVertexAttribI4i = NULL;
PFNGLVERTEXATTRIBI4IEXTPROC glVertexAttribI4iEXT = NULL;
PFNGLVERTEXATTRIBI4IVPROC glVertexAttribI4iv = NULL;
PFNGLVERTEXATTRIBI4IVEXTPROC glVertexAttribI4ivEXT = NULL;
PFNGLVERTEXATTRIBI4SVPROC glVertexAttribI4sv = NULL;
PFNGLVERTEXATTRIBI4SVEXTPROC glVertexAttribI4svEXT = NULL;
PFNGLVERTEXATTRIBI4UBVPROC glVertexAttribI4ubv = NULL;
PFNGLVERTEXATTRIBI4UBVEXTPROC glVertexAttribI4ubvEXT = NULL;
PFNGLVERTEXATTRIBI4UIPROC glVertexAttribI4ui = NULL;
PFNGLVERTEXATTRIBI4UIEXTPROC glVertexAttribI4uiEXT = NULL;
PFNGLVERTEXATTRIBI4UIVPROC glVertexAttribI4uiv = NULL;
PFNGLVERTEXATTRIBI4UIVEXTPROC glVertexAttribI4uivEXT = NULL;
PFNGLVERTEXATTRIBI4USVPROC glVertexAttribI4usv = NULL;
PFNGLVERTEXATTRIBI4USVEXTPROC glVertexAttribI4usvEXT = NULL;
PFNGLVERTEXATTRIBIFORMATPROC glVertexAttribIFormat = NULL;
PFNGLVERTEXATTRIBIFORMATNVPROC glVertexAttribIFormatNV = NULL;
PFNGLVERTEXATTRIBIPOINTERPROC glVertexAttribIPointer = NULL;
PFNGLVERTEXATTRIBIPOINTEREXTPROC glVertexAttribIPointerEXT = NULL;
PFNGLVERTEXATTRIBL1DPROC glVertexAttribL1d = NULL;
PFNGLVERTEXATTRIBL1DEXTPROC glVertexAttribL1dEXT = NULL;
PFNGLVERTEXATTRIBL1DVPROC glVertexAttribL1dv = NULL;
PFNGLVERTEXATTRIBL1DVEXTPROC glVertexAttribL1dvEXT = NULL;
PFNGLVERTEXATTRIBL1I64NVPROC glVertexAttribL1i64NV = NULL;
PFNGLVERTEXATTRIBL1I64VNVPROC glVertexAttribL1i64vNV = NULL;
PFNGLVERTEXATTRIBL1UI64ARBPROC glVertexAttribL1ui64ARB = NULL;
PFNGLVERTEXATTRIBL1UI64NVPROC glVertexAttribL1ui64NV = NULL;
PFNGLVERTEXATTRIBL1UI64VARBPROC glVertexAttribL1ui64vARB = NULL;
PFNGLVERTEXATTRIBL1UI64VNVPROC glVertexAttribL1ui64vNV = NULL;
PFNGLVERTEXATTRIBL2DPROC glVertexAttribL2d = NULL;
PFNGLVERTEXATTRIBL2DEXTPROC glVertexAttribL2dEXT = NULL;
PFNGLVERTEXATTRIBL2DVPROC glVertexAttribL2dv = NULL;
PFNGLVERTEXATTRIBL2DVEXTPROC glVertexAttribL2dvEXT = NULL;
PFNGLVERTEXATTRIBL2I64NVPROC glVertexAttribL2i64NV = NULL;
PFNGLVERTEXATTRIBL2I64VNVPROC glVertexAttribL2i64vNV = NULL;
PFNGLVERTEXATTRIBL2UI64NVPROC glVertexAttribL2ui64NV = NULL;
PFNGLVERTEXATTRIBL2UI64VNVPROC glVertexAttribL2ui64vNV = NULL;
PFNGLVERTEXATTRIBL3DPROC glVertexAttribL3d = NULL;
PFNGLVERTEXATTRIBL3DEXTPROC glVertexAttribL3dEXT = NULL;
PFNGLVERTEXATTRIBL3DVPROC glVertexAttribL3dv = NULL;
PFNGLVERTEXATTRIBL3DVEXTPROC glVertexAttribL3dvEXT = NULL;
PFNGLVERTEXATTRIBL3I64NVPROC glVertexAttribL3i64NV = NULL;
PFNGLVERTEXATTRIBL3I64VNVPROC glVertexAttribL3i64vNV = NULL;
PFNGLVERTEXATTRIBL3UI64NVPROC glVertexAttribL3ui64NV = NULL;
PFNGLVERTEXATTRIBL3UI64VNVPROC glVertexAttribL3ui64vNV = NULL;
PFNGLVERTEXATTRIBL4DPROC glVertexAttribL4d = NULL;
PFNGLVERTEXATTRIBL4DEXTPROC glVertexAttribL4dEXT = NULL;
PFNGLVERTEXATTRIBL4DVPROC glVertexAttribL4dv = NULL;
PFNGLVERTEXATTRIBL4DVEXTPROC glVertexAttribL4dvEXT = NULL;
PFNGLVERTEXATTRIBL4I64NVPROC glVertexAttribL4i64NV = NULL;
PFNGLVERTEXATTRIBL4I64VNVPROC glVertexAttribL4i64vNV = NULL;
PFNGLVERTEXATTRIBL4UI64NVPROC glVertexAttribL4ui64NV = NULL;
PFNGLVERTEXATTRIBL4UI64VNVPROC glVertexAttribL4ui64vNV = NULL;
PFNGLVERTEXATTRIBLFORMATPROC glVertexAttribLFormat = NULL;
PFNGLVERTEXATTRIBLFORMATNVPROC glVertexAttribLFormatNV = NULL;
PFNGLVERTEXATTRIBLPOINTERPROC glVertexAttribLPointer = NULL;
PFNGLVERTEXATTRIBLPOINTEREXTPROC glVertexAttribLPointerEXT = NULL;
PFNGLVERTEXATTRIBP1UIPROC glVertexAttribP1ui = NULL;
PFNGLVERTEXATTRIBP1UIVPROC glVertexAttribP1uiv = NULL;
PFNGLVERTEXATTRIBP2UIPROC glVertexAttribP2ui = NULL;
PFNGLVERTEXATTRIBP2UIVPROC glVertexAttribP2uiv = NULL;
PFNGLVERTEXATTRIBP3UIPROC glVertexAttribP3ui = NULL;
PFNGLVERTEXATTRIBP3UIVPROC glVertexAttribP3uiv = NULL;
PFNGLVERTEXATTRIBP4UIPROC glVertexAttribP4ui = NULL;
PFNGLVERTEXATTRIBP4UIVPROC glVertexAttribP4uiv = NULL;
PFNGLVERTEXATTRIBPARAMETERIAMDPROC glVertexAttribParameteriAMD = NULL;
PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer = NULL;
PFNGLVERTEXATTRIBPOINTERARBPROC glVertexAttribPointerARB = NULL;
PFNGLVERTEXATTRIBPOINTERNVPROC glVertexAttribPointerNV = NULL;
PFNGLVERTEXATTRIBS1DVNVPROC glVertexAttribs1dvNV = NULL;
PFNGLVERTEXATTRIBS1FVNVPROC glVertexAttribs1fvNV = NULL;
PFNGLVERTEXATTRIBS1HVNVPROC glVertexAttribs1hvNV = NULL;
PFNGLVERTEXATTRIBS1SVNVPROC glVertexAttribs1svNV = NULL;
PFNGLVERTEXATTRIBS2DVNVPROC glVertexAttribs2dvNV = NULL;
PFNGLVERTEXATTRIBS2FVNVPROC glVertexAttribs2fvNV = NULL;
PFNGLVERTEXATTRIBS2HVNVPROC glVertexAttribs2hvNV = NULL;
PFNGLVERTEXATTRIBS2SVNVPROC glVertexAttribs2svNV = NULL;
PFNGLVERTEXATTRIBS3DVNVPROC glVertexAttribs3dvNV = NULL;
PFNGLVERTEXATTRIBS3FVNVPROC glVertexAttribs3fvNV = NULL;
PFNGLVERTEXATTRIBS3HVNVPROC glVertexAttribs3hvNV = NULL;
PFNGLVERTEXATTRIBS3SVNVPROC glVertexAttribs3svNV = NULL;
PFNGLVERTEXATTRIBS4DVNVPROC glVertexAttribs4dvNV = NULL;
PFNGLVERTEXATTRIBS4FVNVPROC glVertexAttribs4fvNV = NULL;
PFNGLVERTEXATTRIBS4HVNVPROC glVertexAttribs4hvNV = NULL;
PFNGLVERTEXATTRIBS4SVNVPROC glVertexAttribs4svNV = NULL;
PFNGLVERTEXATTRIBS4UBVNVPROC glVertexAttribs4ubvNV = NULL;
PFNGLVERTEXBINDINGDIVISORPROC glVertexBindingDivisor = NULL;
PFNGLVERTEXBLENDARBPROC glVertexBlendARB = NULL;
PFNGLVERTEXFORMATNVPROC glVertexFormatNV = NULL;
PFNGLVERTEXP2UIPROC glVertexP2ui = NULL;
PFNGLVERTEXP2UIVPROC glVertexP2uiv = NULL;
PFNGLVERTEXP3UIPROC glVertexP3ui = NULL;
PFNGLVERTEXP3UIVPROC glVertexP3uiv = NULL;
PFNGLVERTEXP4UIPROC glVertexP4ui = NULL;
PFNGLVERTEXP4UIVPROC glVertexP4uiv = NULL;
PFNGLVERTEXPOINTERPROC glVertexPointer = NULL;
PFNGLVERTEXPOINTEREXTPROC glVertexPointerEXT = NULL;
PFNGLVERTEXPOINTERVINTELPROC glVertexPointervINTEL = NULL;
PFNGLVERTEXWEIGHTPOINTEREXTPROC glVertexWeightPointerEXT = NULL;
PFNGLVERTEXWEIGHTFEXTPROC glVertexWeightfEXT = NULL;
PFNGLVERTEXWEIGHTFVEXTPROC glVertexWeightfvEXT = NULL;
PFNGLVERTEXWEIGHTHNVPROC glVertexWeighthNV = NULL;
PFNGLVERTEXWEIGHTHVNVPROC glVertexWeighthvNV = NULL;
PFNGLVIDEOCAPTURENVPROC glVideoCaptureNV = NULL;
PFNGLVIDEOCAPTURESTREAMPARAMETERDVNVPROC glVideoCaptureStreamParameterdvNV = NULL;
PFNGLVIDEOCAPTURESTREAMPARAMETERFVNVPROC glVideoCaptureStreamParameterfvNV = NULL;
PFNGLVIDEOCAPTURESTREAMPARAMETERIVNVPROC glVideoCaptureStreamParameterivNV = NULL;
PFNGLVIEWPORTPROC glViewport = NULL;
PFNGLVIEWPORTARRAYVPROC glViewportArrayv = NULL;
PFNGLVIEWPORTINDEXEDFPROC glViewportIndexedf = NULL;
PFNGLVIEWPORTINDEXEDFVPROC glViewportIndexedfv = NULL;
PFNGLVIEWPORTPOSITIONWSCALENVPROC glViewportPositionWScaleNV = NULL;
PFNGLVIEWPORTSWIZZLENVPROC glViewportSwizzleNV = NULL;
PFNGLWAITSEMAPHOREEXTPROC glWaitSemaphoreEXT = NULL;
PFNGLWAITSEMAPHOREUI64NVXPROC glWaitSemaphoreui64NVX = NULL;
PFNGLWAITSYNCPROC glWaitSync = NULL;
PFNGLWEIGHTPATHSNVPROC glWeightPathsNV = NULL;
PFNGLWEIGHTPOINTERARBPROC glWeightPointerARB = NULL;
PFNGLWEIGHTBVARBPROC glWeightbvARB = NULL;
PFNGLWEIGHTDVARBPROC glWeightdvARB = NULL;
PFNGLWEIGHTFVARBPROC glWeightfvARB = NULL;
PFNGLWEIGHTIVARBPROC glWeightivARB = NULL;
PFNGLWEIGHTSVARBPROC glWeightsvARB = NULL;
PFNGLWEIGHTUBVARBPROC glWeightubvARB = NULL;
PFNGLWEIGHTUIVARBPROC glWeightuivARB = NULL;
PFNGLWEIGHTUSVARBPROC glWeightusvARB = NULL;
PFNGLWINDOWPOS2DPROC glWindowPos2d = NULL;
PFNGLWINDOWPOS2DARBPROC glWindowPos2dARB = NULL;
PFNGLWINDOWPOS2DVPROC glWindowPos2dv = NULL;
PFNGLWINDOWPOS2DVARBPROC glWindowPos2dvARB = NULL;
PFNGLWINDOWPOS2FPROC glWindowPos2f = NULL;
PFNGLWINDOWPOS2FARBPROC glWindowPos2fARB = NULL;
PFNGLWINDOWPOS2FVPROC glWindowPos2fv = NULL;
PFNGLWINDOWPOS2FVARBPROC glWindowPos2fvARB = NULL;
PFNGLWINDOWPOS2IPROC glWindowPos2i = NULL;
PFNGLWINDOWPOS2IARBPROC glWindowPos2iARB = NULL;
PFNGLWINDOWPOS2IVPROC glWindowPos2iv = NULL;
PFNGLWINDOWPOS2IVARBPROC glWindowPos2ivARB = NULL;
PFNGLWINDOWPOS2SPROC glWindowPos2s = NULL;
PFNGLWINDOWPOS2SARBPROC glWindowPos2sARB = NULL;
PFNGLWINDOWPOS2SVPROC glWindowPos2sv = NULL;
PFNGLWINDOWPOS2SVARBPROC glWindowPos2svARB = NULL;
PFNGLWINDOWPOS3DPROC glWindowPos3d = NULL;
PFNGLWINDOWPOS3DARBPROC glWindowPos3dARB = NULL;
PFNGLWINDOWPOS3DVPROC glWindowPos3dv = NULL;
PFNGLWINDOWPOS3DVARBPROC glWindowPos3dvARB = NULL;
PFNGLWINDOWPOS3FPROC glWindowPos3f = NULL;
PFNGLWINDOWPOS3FARBPROC glWindowPos3fARB = NULL;
PFNGLWINDOWPOS3FVPROC glWindowPos3fv = NULL;
PFNGLWINDOWPOS3FVARBPROC glWindowPos3fvARB = NULL;
PFNGLWINDOWPOS3IPROC glWindowPos3i = NULL;
PFNGLWINDOWPOS3IARBPROC glWindowPos3iARB = NULL;
PFNGLWINDOWPOS3IVPROC glWindowPos3iv = NULL;
PFNGLWINDOWPOS3IVARBPROC glWindowPos3ivARB = NULL;
PFNGLWINDOWPOS3SPROC glWindowPos3s = NULL;
PFNGLWINDOWPOS3SARBPROC glWindowPos3sARB = NULL;
PFNGLWINDOWPOS3SVPROC glWindowPos3sv = NULL;
PFNGLWINDOWPOS3SVARBPROC glWindowPos3svARB = NULL;
PFNGLWINDOWRECTANGLESEXTPROC glWindowRectanglesEXT = NULL;
PFNGLWRITEMASKEXTPROC glWriteMaskEXT = NULL;
PFNGLDRAWVKIMAGENVPROC glDrawVkImageNV = NULL;
PFNGLGETVKPROCADDRNVPROC glGetVkProcAddrNV = NULL;
PFNGLWAITVKSEMAPHORENVPROC glWaitVkSemaphoreNV = NULL;
PFNGLSIGNALVKSEMAPHORENVPROC glSignalVkSemaphoreNV = NULL;
PFNGLSIGNALVKFENCENVPROC glSignalVkFenceNV = NULL;

static void *libHandle = NULL;
#if !defined(ARCH_OS_DARWIN)
typedef void *(*PFNGETPROCADDRESS)(const char *);
PFNGETPROCADDRESS libGetProcAddress = NULL;
#endif

static bool loadLibrary()
{
#if defined(ARCH_OS_WINDOWS)
  libHandle = ArchLibraryOpen("opengl32.dll", 0);
  libGetProcAddress = (PFNGETPROCADDRESS)ArchLibraryGetSymbolAddress(libHandle,
                                                                     "wglGetProcAddress");
#elif defined(ARCH_OS_DARWIN)
  libHandle = ArchLibraryOpen(
      "/System/Library/Frameworks/OpenGL.framework/Versions/Current/OpenGL",
      RTLD_LAZY | RTLD_LOCAL);
#elif defined(ARCH_OS_LINUX)
  libHandle = ArchLibraryOpen("libGL.so.1", RTLD_LAZY | RTLD_LOCAL);
  libGetProcAddress = (PFNGETPROCADDRESS)ArchLibraryGetSymbolAddress(libHandle,
                                                                     "glXGetProcAddressARB");
#else
  return false;
#endif

  return libHandle;
}

static void unloadLibrary()
{
  if (libHandle != NULL) {
    ArchLibraryClose(libHandle);
    libHandle = NULL;
  }
}

static void *loadFunction(const char *name)
{
  void *result = NULL;
  assert(libHandle != NULL);

#if !defined(ARCH_OS_DARWIN)
  result = libGetProcAddress(name);
  if (result == NULL) {
    result = ArchLibraryGetSymbolAddress(libHandle, name);
  }
#else
  result = ArchLibraryGetSymbolAddress(libHandle, name);
#endif

  return result;
}

static bool hasExt(const char *ext, const std::vector<const char *> &extensions)
{
  for (size_t i = 0; i < extensions.size(); ++i) {
    if (strcmp(ext, extensions[i]) == 0) {
      return true;
    }
  }
  return false;
}

static bool loadSymbols()
{
  glGetIntegerv = (PFNGLGETINTEGERVPROC)loadFunction("glGetIntegerv");
  glGetString = (PFNGLGETSTRINGPROC)loadFunction("glGetString");
  glGetStringi = (PFNGLGETSTRINGIPROC)loadFunction("glGetStringi");

  GLint major = 0, minor = 0;

  // direct version query is supported only for versions 3.x and greater
  const char *versionStr = (const char *)glGetString(GL_VERSION);
  if (versionStr && versionStr[0] == '1' && versionStr[1] == '.') {
    major = 1;
    minor = versionStr[2] - '0';
  }
  else if (versionStr && versionStr[0] == '2' && versionStr[1] == '.') {
    major = 2;
    minor = versionStr[2] - '0';
  }
  else {
    glGetIntegerv(GL_MAJOR_VERSION, &major);
    glGetIntegerv(GL_MINOR_VERSION, &minor);
  }

  std::vector<const char *> extensions;
  std::vector<char> extensionsBuffer;  // used when parsing extensions string

  // direct extension query is supported only for versions 3.x and greater
  if (major >= 3) {
    GLint numExtensions = 0;
    glGetIntegerv(GL_NUM_EXTENSIONS, &numExtensions);
    extensions.resize(numExtensions);
    for (size_t i = 0; i < extensions.size(); ++i) {
      extensions[i] = (const char *)glGetStringi(GL_EXTENSIONS, (GLuint)i);
    }
  }
  else if (major > 0) {
    const char *extStr = (const char *)glGetString(GL_EXTENSIONS);
    const size_t extStrLen = strlen(extStr);

    // make a copy so that we can terminate substrings
    extensionsBuffer.assign(extStr, extStr + extStrLen + 1);

    // identify and terminate substrings
    bool inSubstring = false;
    for (size_t i = 0; i < extStrLen; ++i) {
      if (extensionsBuffer[i] == ' ') {
        extensionsBuffer[i] = '\0';
        inSubstring = false;
      }
      else if (!inSubstring) {
        extensions.push_back(&extensionsBuffer[i]);
        inSubstring = true;
      }
    }
  }

  GARCH_GL_VERSION_1_0 = (major == 1 && minor >= 0) || major > 1;
  GARCH_GL_VERSION_1_1 = (major == 1 && minor >= 1) || major > 1;
  GARCH_GL_VERSION_1_2 = (major == 1 && minor >= 2) || major > 1;
  GARCH_GL_VERSION_1_3 = (major == 1 && minor >= 3) || major > 1;
  GARCH_GL_VERSION_1_4 = (major == 1 && minor >= 4) || major > 1;
  GARCH_GL_VERSION_1_5 = (major == 1 && minor >= 5) || major > 1;
  GARCH_GL_VERSION_2_0 = (major == 2 && minor >= 0) || major > 2;
  GARCH_GL_VERSION_2_1 = (major == 2 && minor >= 1) || major > 2;
  GARCH_GL_VERSION_3_0 = (major == 3 && minor >= 0) || major > 3;
  GARCH_GL_VERSION_3_1 = (major == 3 && minor >= 1) || major > 3;
  GARCH_GL_VERSION_3_2 = (major == 3 && minor >= 2) || major > 3;
  GARCH_GL_VERSION_3_3 = (major == 3 && minor >= 3) || major > 3;
  GARCH_GL_VERSION_4_0 = (major == 4 && minor >= 0) || major > 4;
  GARCH_GL_VERSION_4_1 = (major == 4 && minor >= 1) || major > 4;
  GARCH_GL_VERSION_4_2 = (major == 4 && minor >= 2) || major > 4;
  GARCH_GL_VERSION_4_3 = (major == 4 && minor >= 3) || major > 4;
  GARCH_GL_VERSION_4_4 = (major == 4 && minor >= 4) || major > 4;
  GARCH_GL_VERSION_4_5 = (major == 4 && minor >= 5) || major > 4;
  GARCH_GL_VERSION_4_6 = (major == 4 && minor >= 6) || major > 4;

  GARCH_GL_AMD_blend_minmax_factor = hasExt("GL_AMD_blend_minmax_factor", extensions);
  GARCH_GL_AMD_conservative_depth = hasExt("GL_AMD_conservative_depth", extensions);
  GARCH_GL_AMD_debug_output = hasExt("GL_AMD_debug_output", extensions);
  GARCH_GL_AMD_depth_clamp_separate = hasExt("GL_AMD_depth_clamp_separate", extensions);
  GARCH_GL_AMD_draw_buffers_blend = hasExt("GL_AMD_draw_buffers_blend", extensions);
  GARCH_GL_AMD_framebuffer_multisample_advanced = hasExt("GL_AMD_framebuffer_multisample_advanced",
                                                         extensions);
  GARCH_GL_AMD_framebuffer_sample_positions = hasExt("GL_AMD_framebuffer_sample_positions",
                                                     extensions);
  GARCH_GL_AMD_gcn_shader = hasExt("GL_AMD_gcn_shader", extensions);
  GARCH_GL_AMD_gpu_shader_half_float = hasExt("GL_AMD_gpu_shader_half_float", extensions);
  GARCH_GL_AMD_gpu_shader_int16 = hasExt("GL_AMD_gpu_shader_int16", extensions);
  GARCH_GL_AMD_gpu_shader_int64 = hasExt("GL_AMD_gpu_shader_int64", extensions);
  GARCH_GL_AMD_interleaved_elements = hasExt("GL_AMD_interleaved_elements", extensions);
  GARCH_GL_AMD_multi_draw_indirect = hasExt("GL_AMD_multi_draw_indirect", extensions);
  GARCH_GL_AMD_name_gen_delete = hasExt("GL_AMD_name_gen_delete", extensions);
  GARCH_GL_AMD_occlusion_query_event = hasExt("GL_AMD_occlusion_query_event", extensions);
  GARCH_GL_AMD_performance_monitor = hasExt("GL_AMD_performance_monitor", extensions);
  GARCH_GL_AMD_pinned_memory = hasExt("GL_AMD_pinned_memory", extensions);
  GARCH_GL_AMD_query_buffer_object = hasExt("GL_AMD_query_buffer_object", extensions);
  GARCH_GL_AMD_sample_positions = hasExt("GL_AMD_sample_positions", extensions);
  GARCH_GL_AMD_seamless_cubemap_per_texture = hasExt("GL_AMD_seamless_cubemap_per_texture",
                                                     extensions);
  GARCH_GL_AMD_shader_atomic_counter_ops = hasExt("GL_AMD_shader_atomic_counter_ops", extensions);
  GARCH_GL_AMD_shader_ballot = hasExt("GL_AMD_shader_ballot", extensions);
  GARCH_GL_AMD_shader_gpu_shader_half_float_fetch = hasExt(
      "GL_AMD_shader_gpu_shader_half_float_fetch", extensions);
  GARCH_GL_AMD_shader_image_load_store_lod = hasExt("GL_AMD_shader_image_load_store_lod",
                                                    extensions);
  GARCH_GL_AMD_shader_stencil_export = hasExt("GL_AMD_shader_stencil_export", extensions);
  GARCH_GL_AMD_shader_trinary_minmax = hasExt("GL_AMD_shader_trinary_minmax", extensions);
  GARCH_GL_AMD_shader_explicit_vertex_parameter = hasExt("GL_AMD_shader_explicit_vertex_parameter",
                                                         extensions);
  GARCH_GL_AMD_sparse_texture = hasExt("GL_AMD_sparse_texture", extensions);
  GARCH_GL_AMD_stencil_operation_extended = hasExt("GL_AMD_stencil_operation_extended",
                                                   extensions);
  GARCH_GL_AMD_texture_gather_bias_lod = hasExt("GL_AMD_texture_gather_bias_lod", extensions);
  GARCH_GL_AMD_texture_texture4 = hasExt("GL_AMD_texture_texture4", extensions);
  GARCH_GL_AMD_transform_feedback3_lines_triangles = hasExt(
      "GL_AMD_transform_feedback3_lines_triangles", extensions);
  GARCH_GL_AMD_transform_feedback4 = hasExt("GL_AMD_transform_feedback4", extensions);
  GARCH_GL_AMD_vertex_shader_layer = hasExt("GL_AMD_vertex_shader_layer", extensions);
  GARCH_GL_AMD_vertex_shader_tessellator = hasExt("GL_AMD_vertex_shader_tessellator", extensions);
  GARCH_GL_AMD_vertex_shader_viewport_index = hasExt("GL_AMD_vertex_shader_viewport_index",
                                                     extensions);
  GARCH_GL_APPLE_aux_depth_stencil = hasExt("GL_APPLE_aux_depth_stencil", extensions);
  GARCH_GL_APPLE_client_storage = hasExt("GL_APPLE_client_storage", extensions);
  GARCH_GL_APPLE_element_array = hasExt("GL_APPLE_element_array", extensions);
  GARCH_GL_APPLE_fence = hasExt("GL_APPLE_fence", extensions);
  GARCH_GL_APPLE_float_pixels = hasExt("GL_APPLE_float_pixels", extensions);
  GARCH_GL_APPLE_flush_buffer_range = hasExt("GL_APPLE_flush_buffer_range", extensions);
  GARCH_GL_APPLE_object_purgeable = hasExt("GL_APPLE_object_purgeable", extensions);
  GARCH_GL_APPLE_rgb_422 = hasExt("GL_APPLE_rgb_422", extensions);
  GARCH_GL_APPLE_row_bytes = hasExt("GL_APPLE_row_bytes", extensions);
  GARCH_GL_APPLE_specular_vector = hasExt("GL_APPLE_specular_vector", extensions);
  GARCH_GL_APPLE_texture_range = hasExt("GL_APPLE_texture_range", extensions);
  GARCH_GL_APPLE_transform_hint = hasExt("GL_APPLE_transform_hint", extensions);
  GARCH_GL_APPLE_vertex_array_object = hasExt("GL_APPLE_vertex_array_object", extensions);
  GARCH_GL_APPLE_vertex_array_range = hasExt("GL_APPLE_vertex_array_range", extensions);
  GARCH_GL_APPLE_vertex_program_evaluators = hasExt("GL_APPLE_vertex_program_evaluators",
                                                    extensions);
  GARCH_GL_APPLE_ycbcr_422 = hasExt("GL_APPLE_ycbcr_422", extensions);
  GARCH_GL_ARB_ES2_compatibility = hasExt("GL_ARB_ES2_compatibility", extensions);
  GARCH_GL_ARB_ES3_1_compatibility = hasExt("GL_ARB_ES3_1_compatibility", extensions);
  GARCH_GL_ARB_ES3_2_compatibility = hasExt("GL_ARB_ES3_2_compatibility", extensions);
  GARCH_GL_ARB_ES3_compatibility = hasExt("GL_ARB_ES3_compatibility", extensions);
  GARCH_GL_ARB_arrays_of_arrays = hasExt("GL_ARB_arrays_of_arrays", extensions);
  GARCH_GL_ARB_base_instance = hasExt("GL_ARB_base_instance", extensions);
  GARCH_GL_ARB_bindless_texture = hasExt("GL_ARB_bindless_texture", extensions);
  GARCH_GL_ARB_blend_func_extended = hasExt("GL_ARB_blend_func_extended", extensions);
  GARCH_GL_ARB_buffer_storage = hasExt("GL_ARB_buffer_storage", extensions);
  GARCH_GL_ARB_cl_event = hasExt("GL_ARB_cl_event", extensions);
  GARCH_GL_ARB_clear_buffer_object = hasExt("GL_ARB_clear_buffer_object", extensions);
  GARCH_GL_ARB_clear_texture = hasExt("GL_ARB_clear_texture", extensions);
  GARCH_GL_ARB_clip_control = hasExt("GL_ARB_clip_control", extensions);
  GARCH_GL_ARB_color_buffer_float = hasExt("GL_ARB_color_buffer_float", extensions);
  GARCH_GL_ARB_compatibility = hasExt("GL_ARB_compatibility", extensions);
  GARCH_GL_ARB_compressed_texture_pixel_storage = hasExt("GL_ARB_compressed_texture_pixel_storage",
                                                         extensions);
  GARCH_GL_ARB_compute_shader = hasExt("GL_ARB_compute_shader", extensions);
  GARCH_GL_ARB_compute_variable_group_size = hasExt("GL_ARB_compute_variable_group_size",
                                                    extensions);
  GARCH_GL_ARB_conditional_render_inverted = hasExt("GL_ARB_conditional_render_inverted",
                                                    extensions);
  GARCH_GL_ARB_conservative_depth = hasExt("GL_ARB_conservative_depth", extensions);
  GARCH_GL_ARB_copy_buffer = hasExt("GL_ARB_copy_buffer", extensions);
  GARCH_GL_ARB_copy_image = hasExt("GL_ARB_copy_image", extensions);
  GARCH_GL_ARB_cull_distance = hasExt("GL_ARB_cull_distance", extensions);
  GARCH_GL_ARB_debug_output = hasExt("GL_ARB_debug_output", extensions);
  GARCH_GL_ARB_depth_buffer_float = hasExt("GL_ARB_depth_buffer_float", extensions);
  GARCH_GL_ARB_depth_clamp = hasExt("GL_ARB_depth_clamp", extensions);
  GARCH_GL_ARB_depth_texture = hasExt("GL_ARB_depth_texture", extensions);
  GARCH_GL_ARB_derivative_control = hasExt("GL_ARB_derivative_control", extensions);
  GARCH_GL_ARB_direct_state_access = hasExt("GL_ARB_direct_state_access", extensions);
  GARCH_GL_ARB_draw_buffers = hasExt("GL_ARB_draw_buffers", extensions);
  GARCH_GL_ARB_draw_buffers_blend = hasExt("GL_ARB_draw_buffers_blend", extensions);
  GARCH_GL_ARB_draw_elements_base_vertex = hasExt("GL_ARB_draw_elements_base_vertex", extensions);
  GARCH_GL_ARB_draw_indirect = hasExt("GL_ARB_draw_indirect", extensions);
  GARCH_GL_ARB_draw_instanced = hasExt("GL_ARB_draw_instanced", extensions);
  GARCH_GL_ARB_enhanced_layouts = hasExt("GL_ARB_enhanced_layouts", extensions);
  GARCH_GL_ARB_explicit_attrib_location = hasExt("GL_ARB_explicit_attrib_location", extensions);
  GARCH_GL_ARB_explicit_uniform_location = hasExt("GL_ARB_explicit_uniform_location", extensions);
  GARCH_GL_ARB_fragment_coord_conventions = hasExt("GL_ARB_fragment_coord_conventions",
                                                   extensions);
  GARCH_GL_ARB_fragment_layer_viewport = hasExt("GL_ARB_fragment_layer_viewport", extensions);
  GARCH_GL_ARB_fragment_program = hasExt("GL_ARB_fragment_program", extensions);
  GARCH_GL_ARB_fragment_program_shadow = hasExt("GL_ARB_fragment_program_shadow", extensions);
  GARCH_GL_ARB_fragment_shader = hasExt("GL_ARB_fragment_shader", extensions);
  GARCH_GL_ARB_fragment_shader_interlock = hasExt("GL_ARB_fragment_shader_interlock", extensions);
  GARCH_GL_ARB_framebuffer_no_attachments = hasExt("GL_ARB_framebuffer_no_attachments",
                                                   extensions);
  GARCH_GL_ARB_framebuffer_object = hasExt("GL_ARB_framebuffer_object", extensions);
  GARCH_GL_ARB_framebuffer_sRGB = hasExt("GL_ARB_framebuffer_sRGB", extensions);
  GARCH_GL_ARB_geometry_shader4 = hasExt("GL_ARB_geometry_shader4", extensions);
  GARCH_GL_ARB_get_program_binary = hasExt("GL_ARB_get_program_binary", extensions);
  GARCH_GL_ARB_get_texture_sub_image = hasExt("GL_ARB_get_texture_sub_image", extensions);
  GARCH_GL_ARB_gl_spirv = hasExt("GL_ARB_gl_spirv", extensions);
  GARCH_GL_ARB_gpu_shader5 = hasExt("GL_ARB_gpu_shader5", extensions);
  GARCH_GL_ARB_gpu_shader_fp64 = hasExt("GL_ARB_gpu_shader_fp64", extensions);
  GARCH_GL_ARB_gpu_shader_int64 = hasExt("GL_ARB_gpu_shader_int64", extensions);
  GARCH_GL_ARB_half_float_pixel = hasExt("GL_ARB_half_float_pixel", extensions);
  GARCH_GL_ARB_half_float_vertex = hasExt("GL_ARB_half_float_vertex", extensions);
  GARCH_GL_ARB_imaging = hasExt("GL_ARB_imaging", extensions);
  GARCH_GL_ARB_indirect_parameters = hasExt("GL_ARB_indirect_parameters", extensions);
  GARCH_GL_ARB_instanced_arrays = hasExt("GL_ARB_instanced_arrays", extensions);
  GARCH_GL_ARB_internalformat_query = hasExt("GL_ARB_internalformat_query", extensions);
  GARCH_GL_ARB_internalformat_query2 = hasExt("GL_ARB_internalformat_query2", extensions);
  GARCH_GL_ARB_invalidate_subdata = hasExt("GL_ARB_invalidate_subdata", extensions);
  GARCH_GL_ARB_map_buffer_alignment = hasExt("GL_ARB_map_buffer_alignment", extensions);
  GARCH_GL_ARB_map_buffer_range = hasExt("GL_ARB_map_buffer_range", extensions);
  GARCH_GL_ARB_matrix_palette = hasExt("GL_ARB_matrix_palette", extensions);
  GARCH_GL_ARB_multi_bind = hasExt("GL_ARB_multi_bind", extensions);
  GARCH_GL_ARB_multi_draw_indirect = hasExt("GL_ARB_multi_draw_indirect", extensions);
  GARCH_GL_ARB_multisample = hasExt("GL_ARB_multisample", extensions);
  GARCH_GL_ARB_multitexture = hasExt("GL_ARB_multitexture", extensions);
  GARCH_GL_ARB_occlusion_query = hasExt("GL_ARB_occlusion_query", extensions);
  GARCH_GL_ARB_occlusion_query2 = hasExt("GL_ARB_occlusion_query2", extensions);
  GARCH_GL_ARB_parallel_shader_compile = hasExt("GL_ARB_parallel_shader_compile", extensions);
  GARCH_GL_ARB_pipeline_statistics_query = hasExt("GL_ARB_pipeline_statistics_query", extensions);
  GARCH_GL_ARB_pixel_buffer_object = hasExt("GL_ARB_pixel_buffer_object", extensions);
  GARCH_GL_ARB_point_parameters = hasExt("GL_ARB_point_parameters", extensions);
  GARCH_GL_ARB_point_sprite = hasExt("GL_ARB_point_sprite", extensions);
  GARCH_GL_ARB_polygon_offset_clamp = hasExt("GL_ARB_polygon_offset_clamp", extensions);
  GARCH_GL_ARB_post_depth_coverage = hasExt("GL_ARB_post_depth_coverage", extensions);
  GARCH_GL_ARB_program_interface_query = hasExt("GL_ARB_program_interface_query", extensions);
  GARCH_GL_ARB_provoking_vertex = hasExt("GL_ARB_provoking_vertex", extensions);
  GARCH_GL_ARB_query_buffer_object = hasExt("GL_ARB_query_buffer_object", extensions);
  GARCH_GL_ARB_robust_buffer_access_behavior = hasExt("GL_ARB_robust_buffer_access_behavior",
                                                      extensions);
  GARCH_GL_ARB_robustness = hasExt("GL_ARB_robustness", extensions);
  GARCH_GL_ARB_robustness_isolation = hasExt("GL_ARB_robustness_isolation", extensions);
  GARCH_GL_ARB_sample_locations = hasExt("GL_ARB_sample_locations", extensions);
  GARCH_GL_ARB_sample_shading = hasExt("GL_ARB_sample_shading", extensions);
  GARCH_GL_ARB_sampler_objects = hasExt("GL_ARB_sampler_objects", extensions);
  GARCH_GL_ARB_seamless_cube_map = hasExt("GL_ARB_seamless_cube_map", extensions);
  GARCH_GL_ARB_seamless_cubemap_per_texture = hasExt("GL_ARB_seamless_cubemap_per_texture",
                                                     extensions);
  GARCH_GL_ARB_separate_shader_objects = hasExt("GL_ARB_separate_shader_objects", extensions);
  GARCH_GL_ARB_shader_atomic_counter_ops = hasExt("GL_ARB_shader_atomic_counter_ops", extensions);
  GARCH_GL_ARB_shader_atomic_counters = hasExt("GL_ARB_shader_atomic_counters", extensions);
  GARCH_GL_ARB_shader_ballot = hasExt("GL_ARB_shader_ballot", extensions);
  GARCH_GL_ARB_shader_bit_encoding = hasExt("GL_ARB_shader_bit_encoding", extensions);
  GARCH_GL_ARB_shader_clock = hasExt("GL_ARB_shader_clock", extensions);
  GARCH_GL_ARB_shader_draw_parameters = hasExt("GL_ARB_shader_draw_parameters", extensions);
  GARCH_GL_ARB_shader_group_vote = hasExt("GL_ARB_shader_group_vote", extensions);
  GARCH_GL_ARB_shader_image_load_store = hasExt("GL_ARB_shader_image_load_store", extensions);
  GARCH_GL_ARB_shader_image_size = hasExt("GL_ARB_shader_image_size", extensions);
  GARCH_GL_ARB_shader_objects = hasExt("GL_ARB_shader_objects", extensions);
  GARCH_GL_ARB_shader_precision = hasExt("GL_ARB_shader_precision", extensions);
  GARCH_GL_ARB_shader_stencil_export = hasExt("GL_ARB_shader_stencil_export", extensions);
  GARCH_GL_ARB_shader_storage_buffer_object = hasExt("GL_ARB_shader_storage_buffer_object",
                                                     extensions);
  GARCH_GL_ARB_shader_subroutine = hasExt("GL_ARB_shader_subroutine", extensions);
  GARCH_GL_ARB_shader_texture_image_samples = hasExt("GL_ARB_shader_texture_image_samples",
                                                     extensions);
  GARCH_GL_ARB_shader_texture_lod = hasExt("GL_ARB_shader_texture_lod", extensions);
  GARCH_GL_ARB_shader_viewport_layer_array = hasExt("GL_ARB_shader_viewport_layer_array",
                                                    extensions);
  GARCH_GL_ARB_shading_language_100 = hasExt("GL_ARB_shading_language_100", extensions);
  GARCH_GL_ARB_shading_language_420pack = hasExt("GL_ARB_shading_language_420pack", extensions);
  GARCH_GL_ARB_shading_language_include = hasExt("GL_ARB_shading_language_include", extensions);
  GARCH_GL_ARB_shading_language_packing = hasExt("GL_ARB_shading_language_packing", extensions);
  GARCH_GL_ARB_shadow = hasExt("GL_ARB_shadow", extensions);
  GARCH_GL_ARB_shadow_ambient = hasExt("GL_ARB_shadow_ambient", extensions);
  GARCH_GL_ARB_sparse_buffer = hasExt("GL_ARB_sparse_buffer", extensions);
  GARCH_GL_ARB_sparse_texture = hasExt("GL_ARB_sparse_texture", extensions);
  GARCH_GL_ARB_sparse_texture2 = hasExt("GL_ARB_sparse_texture2", extensions);
  GARCH_GL_ARB_sparse_texture_clamp = hasExt("GL_ARB_sparse_texture_clamp", extensions);
  GARCH_GL_ARB_spirv_extensions = hasExt("GL_ARB_spirv_extensions", extensions);
  GARCH_GL_ARB_stencil_texturing = hasExt("GL_ARB_stencil_texturing", extensions);
  GARCH_GL_ARB_sync = hasExt("GL_ARB_sync", extensions);
  GARCH_GL_ARB_tessellation_shader = hasExt("GL_ARB_tessellation_shader", extensions);
  GARCH_GL_ARB_texture_barrier = hasExt("GL_ARB_texture_barrier", extensions);
  GARCH_GL_ARB_texture_border_clamp = hasExt("GL_ARB_texture_border_clamp", extensions);
  GARCH_GL_ARB_texture_buffer_object = hasExt("GL_ARB_texture_buffer_object", extensions);
  GARCH_GL_ARB_texture_buffer_object_rgb32 = hasExt("GL_ARB_texture_buffer_object_rgb32",
                                                    extensions);
  GARCH_GL_ARB_texture_buffer_range = hasExt("GL_ARB_texture_buffer_range", extensions);
  GARCH_GL_ARB_texture_compression = hasExt("GL_ARB_texture_compression", extensions);
  GARCH_GL_ARB_texture_compression_bptc = hasExt("GL_ARB_texture_compression_bptc", extensions);
  GARCH_GL_ARB_texture_compression_rgtc = hasExt("GL_ARB_texture_compression_rgtc", extensions);
  GARCH_GL_ARB_texture_cube_map = hasExt("GL_ARB_texture_cube_map", extensions);
  GARCH_GL_ARB_texture_cube_map_array = hasExt("GL_ARB_texture_cube_map_array", extensions);
  GARCH_GL_ARB_texture_env_add = hasExt("GL_ARB_texture_env_add", extensions);
  GARCH_GL_ARB_texture_env_combine = hasExt("GL_ARB_texture_env_combine", extensions);
  GARCH_GL_ARB_texture_env_crossbar = hasExt("GL_ARB_texture_env_crossbar", extensions);
  GARCH_GL_ARB_texture_env_dot3 = hasExt("GL_ARB_texture_env_dot3", extensions);
  GARCH_GL_ARB_texture_filter_anisotropic = hasExt("GL_ARB_texture_filter_anisotropic",
                                                   extensions);
  GARCH_GL_ARB_texture_filter_minmax = hasExt("GL_ARB_texture_filter_minmax", extensions);
  GARCH_GL_ARB_texture_float = hasExt("GL_ARB_texture_float", extensions);
  GARCH_GL_ARB_texture_gather = hasExt("GL_ARB_texture_gather", extensions);
  GARCH_GL_ARB_texture_mirror_clamp_to_edge = hasExt("GL_ARB_texture_mirror_clamp_to_edge",
                                                     extensions);
  GARCH_GL_ARB_texture_mirrored_repeat = hasExt("GL_ARB_texture_mirrored_repeat", extensions);
  GARCH_GL_ARB_texture_multisample = hasExt("GL_ARB_texture_multisample", extensions);
  GARCH_GL_ARB_texture_non_power_of_two = hasExt("GL_ARB_texture_non_power_of_two", extensions);
  GARCH_GL_ARB_texture_query_levels = hasExt("GL_ARB_texture_query_levels", extensions);
  GARCH_GL_ARB_texture_query_lod = hasExt("GL_ARB_texture_query_lod", extensions);
  GARCH_GL_ARB_texture_rectangle = hasExt("GL_ARB_texture_rectangle", extensions);
  GARCH_GL_ARB_texture_rg = hasExt("GL_ARB_texture_rg", extensions);
  GARCH_GL_ARB_texture_rgb10_a2ui = hasExt("GL_ARB_texture_rgb10_a2ui", extensions);
  GARCH_GL_ARB_texture_stencil8 = hasExt("GL_ARB_texture_stencil8", extensions);
  GARCH_GL_ARB_texture_storage = hasExt("GL_ARB_texture_storage", extensions);
  GARCH_GL_ARB_texture_storage_multisample = hasExt("GL_ARB_texture_storage_multisample",
                                                    extensions);
  GARCH_GL_ARB_texture_swizzle = hasExt("GL_ARB_texture_swizzle", extensions);
  GARCH_GL_ARB_texture_view = hasExt("GL_ARB_texture_view", extensions);
  GARCH_GL_ARB_timer_query = hasExt("GL_ARB_timer_query", extensions);
  GARCH_GL_ARB_transform_feedback2 = hasExt("GL_ARB_transform_feedback2", extensions);
  GARCH_GL_ARB_transform_feedback3 = hasExt("GL_ARB_transform_feedback3", extensions);
  GARCH_GL_ARB_transform_feedback_instanced = hasExt("GL_ARB_transform_feedback_instanced",
                                                     extensions);
  GARCH_GL_ARB_transform_feedback_overflow_query = hasExt(
      "GL_ARB_transform_feedback_overflow_query", extensions);
  GARCH_GL_ARB_transpose_matrix = hasExt("GL_ARB_transpose_matrix", extensions);
  GARCH_GL_ARB_uniform_buffer_object = hasExt("GL_ARB_uniform_buffer_object", extensions);
  GARCH_GL_ARB_vertex_array_bgra = hasExt("GL_ARB_vertex_array_bgra", extensions);
  GARCH_GL_ARB_vertex_array_object = hasExt("GL_ARB_vertex_array_object", extensions);
  GARCH_GL_ARB_vertex_attrib_64bit = hasExt("GL_ARB_vertex_attrib_64bit", extensions);
  GARCH_GL_ARB_vertex_attrib_binding = hasExt("GL_ARB_vertex_attrib_binding", extensions);
  GARCH_GL_ARB_vertex_blend = hasExt("GL_ARB_vertex_blend", extensions);
  GARCH_GL_ARB_vertex_buffer_object = hasExt("GL_ARB_vertex_buffer_object", extensions);
  GARCH_GL_ARB_vertex_program = hasExt("GL_ARB_vertex_program", extensions);
  GARCH_GL_ARB_vertex_shader = hasExt("GL_ARB_vertex_shader", extensions);
  GARCH_GL_ARB_vertex_type_10f_11f_11f_rev = hasExt("GL_ARB_vertex_type_10f_11f_11f_rev",
                                                    extensions);
  GARCH_GL_ARB_vertex_type_2_10_10_10_rev = hasExt("GL_ARB_vertex_type_2_10_10_10_rev",
                                                   extensions);
  GARCH_GL_ARB_viewport_array = hasExt("GL_ARB_viewport_array", extensions);
  GARCH_GL_ARB_window_pos = hasExt("GL_ARB_window_pos", extensions);
  GARCH_GL_EXT_422_pixels = hasExt("GL_EXT_422_pixels", extensions);
  GARCH_GL_EXT_EGL_image_storage = hasExt("GL_EXT_EGL_image_storage", extensions);
  GARCH_GL_EXT_EGL_sync = hasExt("GL_EXT_EGL_sync", extensions);
  GARCH_GL_EXT_abgr = hasExt("GL_EXT_abgr", extensions);
  GARCH_GL_EXT_bgra = hasExt("GL_EXT_bgra", extensions);
  GARCH_GL_EXT_bindable_uniform = hasExt("GL_EXT_bindable_uniform", extensions);
  GARCH_GL_EXT_blend_color = hasExt("GL_EXT_blend_color", extensions);
  GARCH_GL_EXT_blend_equation_separate = hasExt("GL_EXT_blend_equation_separate", extensions);
  GARCH_GL_EXT_blend_func_separate = hasExt("GL_EXT_blend_func_separate", extensions);
  GARCH_GL_EXT_blend_logic_op = hasExt("GL_EXT_blend_logic_op", extensions);
  GARCH_GL_EXT_blend_minmax = hasExt("GL_EXT_blend_minmax", extensions);
  GARCH_GL_EXT_blend_subtract = hasExt("GL_EXT_blend_subtract", extensions);
  GARCH_GL_EXT_clip_volume_hint = hasExt("GL_EXT_clip_volume_hint", extensions);
  GARCH_GL_EXT_cmyka = hasExt("GL_EXT_cmyka", extensions);
  GARCH_GL_EXT_color_subtable = hasExt("GL_EXT_color_subtable", extensions);
  GARCH_GL_EXT_compiled_vertex_array = hasExt("GL_EXT_compiled_vertex_array", extensions);
  GARCH_GL_EXT_convolution = hasExt("GL_EXT_convolution", extensions);
  GARCH_GL_EXT_coordinate_frame = hasExt("GL_EXT_coordinate_frame", extensions);
  GARCH_GL_EXT_copy_texture = hasExt("GL_EXT_copy_texture", extensions);
  GARCH_GL_EXT_cull_vertex = hasExt("GL_EXT_cull_vertex", extensions);
  GARCH_GL_EXT_debug_label = hasExt("GL_EXT_debug_label", extensions);
  GARCH_GL_EXT_debug_marker = hasExt("GL_EXT_debug_marker", extensions);
  GARCH_GL_EXT_depth_bounds_test = hasExt("GL_EXT_depth_bounds_test", extensions);
  GARCH_GL_EXT_direct_state_access = hasExt("GL_EXT_direct_state_access", extensions);
  GARCH_GL_EXT_draw_buffers2 = hasExt("GL_EXT_draw_buffers2", extensions);
  GARCH_GL_EXT_draw_instanced = hasExt("GL_EXT_draw_instanced", extensions);
  GARCH_GL_EXT_draw_range_elements = hasExt("GL_EXT_draw_range_elements", extensions);
  GARCH_GL_EXT_external_buffer = hasExt("GL_EXT_external_buffer", extensions);
  GARCH_GL_EXT_fog_coord = hasExt("GL_EXT_fog_coord", extensions);
  GARCH_GL_EXT_framebuffer_blit = hasExt("GL_EXT_framebuffer_blit", extensions);
  GARCH_GL_EXT_framebuffer_multisample = hasExt("GL_EXT_framebuffer_multisample", extensions);
  GARCH_GL_EXT_framebuffer_multisample_blit_scaled = hasExt(
      "GL_EXT_framebuffer_multisample_blit_scaled", extensions);
  GARCH_GL_EXT_framebuffer_object = hasExt("GL_EXT_framebuffer_object", extensions);
  GARCH_GL_EXT_framebuffer_sRGB = hasExt("GL_EXT_framebuffer_sRGB", extensions);
  GARCH_GL_EXT_geometry_shader4 = hasExt("GL_EXT_geometry_shader4", extensions);
  GARCH_GL_EXT_gpu_program_parameters = hasExt("GL_EXT_gpu_program_parameters", extensions);
  GARCH_GL_EXT_gpu_shader4 = hasExt("GL_EXT_gpu_shader4", extensions);
  GARCH_GL_EXT_histogram = hasExt("GL_EXT_histogram", extensions);
  GARCH_GL_EXT_index_array_formats = hasExt("GL_EXT_index_array_formats", extensions);
  GARCH_GL_EXT_index_func = hasExt("GL_EXT_index_func", extensions);
  GARCH_GL_EXT_index_material = hasExt("GL_EXT_index_material", extensions);
  GARCH_GL_EXT_index_texture = hasExt("GL_EXT_index_texture", extensions);
  GARCH_GL_EXT_light_texture = hasExt("GL_EXT_light_texture", extensions);
  GARCH_GL_EXT_memory_object = hasExt("GL_EXT_memory_object", extensions);
  GARCH_GL_EXT_memory_object_fd = hasExt("GL_EXT_memory_object_fd", extensions);
  GARCH_GL_EXT_memory_object_win32 = hasExt("GL_EXT_memory_object_win32", extensions);
  GARCH_GL_EXT_misc_attribute = hasExt("GL_EXT_misc_attribute", extensions);
  GARCH_GL_EXT_multi_draw_arrays = hasExt("GL_EXT_multi_draw_arrays", extensions);
  GARCH_GL_EXT_multisample = hasExt("GL_EXT_multisample", extensions);
  GARCH_GL_EXT_multiview_tessellation_geometry_shader = hasExt(
      "GL_EXT_multiview_tessellation_geometry_shader", extensions);
  GARCH_GL_EXT_multiview_texture_multisample = hasExt("GL_EXT_multiview_texture_multisample",
                                                      extensions);
  GARCH_GL_EXT_multiview_timer_query = hasExt("GL_EXT_multiview_timer_query", extensions);
  GARCH_GL_EXT_packed_depth_stencil = hasExt("GL_EXT_packed_depth_stencil", extensions);
  GARCH_GL_EXT_packed_float = hasExt("GL_EXT_packed_float", extensions);
  GARCH_GL_EXT_packed_pixels = hasExt("GL_EXT_packed_pixels", extensions);
  GARCH_GL_EXT_paletted_texture = hasExt("GL_EXT_paletted_texture", extensions);
  GARCH_GL_EXT_pixel_buffer_object = hasExt("GL_EXT_pixel_buffer_object", extensions);
  GARCH_GL_EXT_pixel_transform = hasExt("GL_EXT_pixel_transform", extensions);
  GARCH_GL_EXT_pixel_transform_color_table = hasExt("GL_EXT_pixel_transform_color_table",
                                                    extensions);
  GARCH_GL_EXT_point_parameters = hasExt("GL_EXT_point_parameters", extensions);
  GARCH_GL_EXT_polygon_offset = hasExt("GL_EXT_polygon_offset", extensions);
  GARCH_GL_EXT_polygon_offset_clamp = hasExt("GL_EXT_polygon_offset_clamp", extensions);
  GARCH_GL_EXT_post_depth_coverage = hasExt("GL_EXT_post_depth_coverage", extensions);
  GARCH_GL_EXT_provoking_vertex = hasExt("GL_EXT_provoking_vertex", extensions);
  GARCH_GL_EXT_raster_multisample = hasExt("GL_EXT_raster_multisample", extensions);
  GARCH_GL_EXT_rescale_normal = hasExt("GL_EXT_rescale_normal", extensions);
  GARCH_GL_EXT_semaphore = hasExt("GL_EXT_semaphore", extensions);
  GARCH_GL_EXT_semaphore_fd = hasExt("GL_EXT_semaphore_fd", extensions);
  GARCH_GL_EXT_semaphore_win32 = hasExt("GL_EXT_semaphore_win32", extensions);
  GARCH_GL_EXT_secondary_color = hasExt("GL_EXT_secondary_color", extensions);
  GARCH_GL_EXT_separate_shader_objects = hasExt("GL_EXT_separate_shader_objects", extensions);
  GARCH_GL_EXT_separate_specular_color = hasExt("GL_EXT_separate_specular_color", extensions);
  GARCH_GL_EXT_shader_framebuffer_fetch = hasExt("GL_EXT_shader_framebuffer_fetch", extensions);
  GARCH_GL_EXT_shader_framebuffer_fetch_non_coherent = hasExt(
      "GL_EXT_shader_framebuffer_fetch_non_coherent", extensions);
  GARCH_GL_EXT_shader_image_load_formatted = hasExt("GL_EXT_shader_image_load_formatted",
                                                    extensions);
  GARCH_GL_EXT_shader_image_load_store = hasExt("GL_EXT_shader_image_load_store", extensions);
  GARCH_GL_EXT_shader_integer_mix = hasExt("GL_EXT_shader_integer_mix", extensions);
  GARCH_GL_EXT_shadow_funcs = hasExt("GL_EXT_shadow_funcs", extensions);
  GARCH_GL_EXT_shared_texture_palette = hasExt("GL_EXT_shared_texture_palette", extensions);
  GARCH_GL_EXT_sparse_texture2 = hasExt("GL_EXT_sparse_texture2", extensions);
  GARCH_GL_EXT_stencil_clear_tag = hasExt("GL_EXT_stencil_clear_tag", extensions);
  GARCH_GL_EXT_stencil_two_side = hasExt("GL_EXT_stencil_two_side", extensions);
  GARCH_GL_EXT_stencil_wrap = hasExt("GL_EXT_stencil_wrap", extensions);
  GARCH_GL_EXT_subtexture = hasExt("GL_EXT_subtexture", extensions);
  GARCH_GL_EXT_texture = hasExt("GL_EXT_texture", extensions);
  GARCH_GL_EXT_texture3D = hasExt("GL_EXT_texture3D", extensions);
  GARCH_GL_EXT_texture_array = hasExt("GL_EXT_texture_array", extensions);
  GARCH_GL_EXT_texture_buffer_object = hasExt("GL_EXT_texture_buffer_object", extensions);
  GARCH_GL_EXT_texture_compression_latc = hasExt("GL_EXT_texture_compression_latc", extensions);
  GARCH_GL_EXT_texture_compression_rgtc = hasExt("GL_EXT_texture_compression_rgtc", extensions);
  GARCH_GL_EXT_texture_compression_s3tc = hasExt("GL_EXT_texture_compression_s3tc", extensions);
  GARCH_GL_EXT_texture_cube_map = hasExt("GL_EXT_texture_cube_map", extensions);
  GARCH_GL_EXT_texture_env_add = hasExt("GL_EXT_texture_env_add", extensions);
  GARCH_GL_EXT_texture_env_combine = hasExt("GL_EXT_texture_env_combine", extensions);
  GARCH_GL_EXT_texture_env_dot3 = hasExt("GL_EXT_texture_env_dot3", extensions);
  GARCH_GL_EXT_texture_filter_anisotropic = hasExt("GL_EXT_texture_filter_anisotropic",
                                                   extensions);
  GARCH_GL_EXT_texture_filter_minmax = hasExt("GL_EXT_texture_filter_minmax", extensions);
  GARCH_GL_EXT_texture_integer = hasExt("GL_EXT_texture_integer", extensions);
  GARCH_GL_EXT_texture_lod_bias = hasExt("GL_EXT_texture_lod_bias", extensions);
  GARCH_GL_EXT_texture_mirror_clamp = hasExt("GL_EXT_texture_mirror_clamp", extensions);
  GARCH_GL_EXT_texture_object = hasExt("GL_EXT_texture_object", extensions);
  GARCH_GL_EXT_texture_perturb_normal = hasExt("GL_EXT_texture_perturb_normal", extensions);
  GARCH_GL_EXT_texture_sRGB = hasExt("GL_EXT_texture_sRGB", extensions);
  GARCH_GL_EXT_texture_sRGB_R8 = hasExt("GL_EXT_texture_sRGB_R8", extensions);
  GARCH_GL_EXT_texture_sRGB_decode = hasExt("GL_EXT_texture_sRGB_decode", extensions);
  GARCH_GL_EXT_texture_shared_exponent = hasExt("GL_EXT_texture_shared_exponent", extensions);
  GARCH_GL_EXT_texture_snorm = hasExt("GL_EXT_texture_snorm", extensions);
  GARCH_GL_EXT_texture_swizzle = hasExt("GL_EXT_texture_swizzle", extensions);
  GARCH_GL_NV_timeline_semaphore = hasExt("GL_NV_timeline_semaphore", extensions);
  GARCH_GL_EXT_timer_query = hasExt("GL_EXT_timer_query", extensions);
  GARCH_GL_EXT_transform_feedback = hasExt("GL_EXT_transform_feedback", extensions);
  GARCH_GL_EXT_vertex_array = hasExt("GL_EXT_vertex_array", extensions);
  GARCH_GL_EXT_vertex_array_bgra = hasExt("GL_EXT_vertex_array_bgra", extensions);
  GARCH_GL_EXT_vertex_attrib_64bit = hasExt("GL_EXT_vertex_attrib_64bit", extensions);
  GARCH_GL_EXT_vertex_shader = hasExt("GL_EXT_vertex_shader", extensions);
  GARCH_GL_EXT_vertex_weighting = hasExt("GL_EXT_vertex_weighting", extensions);
  GARCH_GL_EXT_win32_keyed_mutex = hasExt("GL_EXT_win32_keyed_mutex", extensions);
  GARCH_GL_EXT_window_rectangles = hasExt("GL_EXT_window_rectangles", extensions);
  GARCH_GL_EXT_x11_sync_object = hasExt("GL_EXT_x11_sync_object", extensions);
  GARCH_GL_INTEL_conservative_rasterization = hasExt("GL_INTEL_conservative_rasterization",
                                                     extensions);
  GARCH_GL_INTEL_fragment_shader_ordering = hasExt("GL_INTEL_fragment_shader_ordering",
                                                   extensions);
  GARCH_GL_INTEL_framebuffer_CMAA = hasExt("GL_INTEL_framebuffer_CMAA", extensions);
  GARCH_GL_INTEL_map_texture = hasExt("GL_INTEL_map_texture", extensions);
  GARCH_GL_INTEL_blackhole_render = hasExt("GL_INTEL_blackhole_render", extensions);
  GARCH_GL_INTEL_parallel_arrays = hasExt("GL_INTEL_parallel_arrays", extensions);
  GARCH_GL_INTEL_performance_query = hasExt("GL_INTEL_performance_query", extensions);
  GARCH_GL_KHR_blend_equation_advanced = hasExt("GL_KHR_blend_equation_advanced", extensions);
  GARCH_GL_KHR_blend_equation_advanced_coherent = hasExt("GL_KHR_blend_equation_advanced_coherent",
                                                         extensions);
  GARCH_GL_KHR_context_flush_control = hasExt("GL_KHR_context_flush_control", extensions);
  GARCH_GL_KHR_debug = hasExt("GL_KHR_debug", extensions);
  GARCH_GL_KHR_no_error = hasExt("GL_KHR_no_error", extensions);
  GARCH_GL_KHR_robust_buffer_access_behavior = hasExt("GL_KHR_robust_buffer_access_behavior",
                                                      extensions);
  GARCH_GL_KHR_robustness = hasExt("GL_KHR_robustness", extensions);
  GARCH_GL_KHR_shader_subgroup = hasExt("GL_KHR_shader_subgroup", extensions);
  GARCH_GL_KHR_texture_compression_astc_hdr = hasExt("GL_KHR_texture_compression_astc_hdr",
                                                     extensions);
  GARCH_GL_KHR_texture_compression_astc_ldr = hasExt("GL_KHR_texture_compression_astc_ldr",
                                                     extensions);
  GARCH_GL_KHR_texture_compression_astc_sliced_3d = hasExt(
      "GL_KHR_texture_compression_astc_sliced_3d", extensions);
  GARCH_GL_KHR_parallel_shader_compile = hasExt("GL_KHR_parallel_shader_compile", extensions);
  GARCH_GL_NVX_blend_equation_advanced_multi_draw_buffers = hasExt(
      "GL_NVX_blend_equation_advanced_multi_draw_buffers", extensions);
  GARCH_GL_NVX_conditional_render = hasExt("GL_NVX_conditional_render", extensions);
  GARCH_GL_NVX_gpu_memory_info = hasExt("GL_NVX_gpu_memory_info", extensions);
  GARCH_GL_NVX_linked_gpu_multicast = hasExt("GL_NVX_linked_gpu_multicast", extensions);
  GARCH_GL_NV_alpha_to_coverage_dither_control = hasExt("GL_NV_alpha_to_coverage_dither_control",
                                                        extensions);
  GARCH_GL_NV_bindless_multi_draw_indirect = hasExt("GL_NV_bindless_multi_draw_indirect",
                                                    extensions);
  GARCH_GL_NV_bindless_multi_draw_indirect_count = hasExt(
      "GL_NV_bindless_multi_draw_indirect_count", extensions);
  GARCH_GL_NV_bindless_texture = hasExt("GL_NV_bindless_texture", extensions);
  GARCH_GL_NV_blend_equation_advanced = hasExt("GL_NV_blend_equation_advanced", extensions);
  GARCH_GL_NV_blend_equation_advanced_coherent = hasExt("GL_NV_blend_equation_advanced_coherent",
                                                        extensions);
  GARCH_GL_NV_blend_minmax_factor = hasExt("GL_NV_blend_minmax_factor", extensions);
  GARCH_GL_NV_blend_square = hasExt("GL_NV_blend_square", extensions);
  GARCH_GL_NV_clip_space_w_scaling = hasExt("GL_NV_clip_space_w_scaling", extensions);
  GARCH_GL_NV_command_list = hasExt("GL_NV_command_list", extensions);
  GARCH_GL_NV_compute_program5 = hasExt("GL_NV_compute_program5", extensions);
  GARCH_GL_NV_compute_shader_derivatives = hasExt("GL_NV_compute_shader_derivatives", extensions);
  GARCH_GL_NV_conditional_render = hasExt("GL_NV_conditional_render", extensions);
  GARCH_GL_NV_conservative_raster = hasExt("GL_NV_conservative_raster", extensions);
  GARCH_GL_NV_conservative_raster_dilate = hasExt("GL_NV_conservative_raster_dilate", extensions);
  GARCH_GL_NV_conservative_raster_pre_snap = hasExt("GL_NV_conservative_raster_pre_snap",
                                                    extensions);
  GARCH_GL_NV_conservative_raster_pre_snap_triangles = hasExt(
      "GL_NV_conservative_raster_pre_snap_triangles", extensions);
  GARCH_GL_NV_conservative_raster_underestimation = hasExt(
      "GL_NV_conservative_raster_underestimation", extensions);
  GARCH_GL_NV_copy_depth_to_color = hasExt("GL_NV_copy_depth_to_color", extensions);
  GARCH_GL_NV_copy_image = hasExt("GL_NV_copy_image", extensions);
  GARCH_GL_NV_deep_texture3D = hasExt("GL_NV_deep_texture3D", extensions);
  GARCH_GL_NV_depth_buffer_float = hasExt("GL_NV_depth_buffer_float", extensions);
  GARCH_GL_NV_depth_clamp = hasExt("GL_NV_depth_clamp", extensions);
  GARCH_GL_NV_draw_texture = hasExt("GL_NV_draw_texture", extensions);
  GARCH_GL_NV_draw_vulkan_image = hasExt("GL_NV_draw_vulkan_image", extensions);
  GARCH_GL_NV_evaluators = hasExt("GL_NV_evaluators", extensions);
  GARCH_GL_NV_explicit_multisample = hasExt("GL_NV_explicit_multisample", extensions);
  GARCH_GL_NV_fence = hasExt("GL_NV_fence", extensions);
  GARCH_GL_NV_fill_rectangle = hasExt("GL_NV_fill_rectangle", extensions);
  GARCH_GL_NV_float_buffer = hasExt("GL_NV_float_buffer", extensions);
  GARCH_GL_NV_fog_distance = hasExt("GL_NV_fog_distance", extensions);
  GARCH_GL_NV_fragment_coverage_to_color = hasExt("GL_NV_fragment_coverage_to_color", extensions);
  GARCH_GL_NV_fragment_program = hasExt("GL_NV_fragment_program", extensions);
  GARCH_GL_NV_fragment_program2 = hasExt("GL_NV_fragment_program2", extensions);
  GARCH_GL_NV_fragment_program4 = hasExt("GL_NV_fragment_program4", extensions);
  GARCH_GL_NV_fragment_program_option = hasExt("GL_NV_fragment_program_option", extensions);
  GARCH_GL_NV_fragment_shader_barycentric = hasExt("GL_NV_fragment_shader_barycentric",
                                                   extensions);
  GARCH_GL_NV_fragment_shader_interlock = hasExt("GL_NV_fragment_shader_interlock", extensions);
  GARCH_GL_NV_framebuffer_mixed_samples = hasExt("GL_NV_framebuffer_mixed_samples", extensions);
  GARCH_GL_NV_framebuffer_multisample_coverage = hasExt("GL_NV_framebuffer_multisample_coverage",
                                                        extensions);
  GARCH_GL_NV_geometry_program4 = hasExt("GL_NV_geometry_program4", extensions);
  GARCH_GL_NV_geometry_shader4 = hasExt("GL_NV_geometry_shader4", extensions);
  GARCH_GL_NV_geometry_shader_passthrough = hasExt("GL_NV_geometry_shader_passthrough",
                                                   extensions);
  GARCH_GL_NV_gpu_program4 = hasExt("GL_NV_gpu_program4", extensions);
  GARCH_GL_NV_gpu_program5 = hasExt("GL_NV_gpu_program5", extensions);
  GARCH_GL_NV_gpu_program5_mem_extended = hasExt("GL_NV_gpu_program5_mem_extended", extensions);
  GARCH_GL_NV_gpu_shader5 = hasExt("GL_NV_gpu_shader5", extensions);
  GARCH_GL_NV_half_float = hasExt("GL_NV_half_float", extensions);
  GARCH_GL_NV_internalformat_sample_query = hasExt("GL_NV_internalformat_sample_query",
                                                   extensions);
  GARCH_GL_NV_light_max_exponent = hasExt("GL_NV_light_max_exponent", extensions);
  GARCH_GL_NV_gpu_multicast = hasExt("GL_NV_gpu_multicast", extensions);
  GARCH_GL_NVX_gpu_multicast2 = hasExt("GL_NVX_gpu_multicast2", extensions);
  GARCH_GL_NVX_progress_fence = hasExt("GL_NVX_progress_fence", extensions);
  GARCH_GL_NV_memory_attachment = hasExt("GL_NV_memory_attachment", extensions);
  GARCH_GL_NV_memory_object_sparse = hasExt("GL_NV_memory_object_sparse", extensions);
  GARCH_GL_NV_mesh_shader = hasExt("GL_NV_mesh_shader", extensions);
  GARCH_GL_NV_multisample_coverage = hasExt("GL_NV_multisample_coverage", extensions);
  GARCH_GL_NV_multisample_filter_hint = hasExt("GL_NV_multisample_filter_hint", extensions);
  GARCH_GL_NV_occlusion_query = hasExt("GL_NV_occlusion_query", extensions);
  GARCH_GL_NV_packed_depth_stencil = hasExt("GL_NV_packed_depth_stencil", extensions);
  GARCH_GL_NV_parameter_buffer_object = hasExt("GL_NV_parameter_buffer_object", extensions);
  GARCH_GL_NV_parameter_buffer_object2 = hasExt("GL_NV_parameter_buffer_object2", extensions);
  GARCH_GL_NV_path_rendering = hasExt("GL_NV_path_rendering", extensions);
  GARCH_GL_NV_path_rendering_shared_edge = hasExt("GL_NV_path_rendering_shared_edge", extensions);
  GARCH_GL_NV_pixel_data_range = hasExt("GL_NV_pixel_data_range", extensions);
  GARCH_GL_NV_point_sprite = hasExt("GL_NV_point_sprite", extensions);
  GARCH_GL_NV_present_video = hasExt("GL_NV_present_video", extensions);
  GARCH_GL_NV_primitive_restart = hasExt("GL_NV_primitive_restart", extensions);
  GARCH_GL_NV_query_resource = hasExt("GL_NV_query_resource", extensions);
  GARCH_GL_NV_query_resource_tag = hasExt("GL_NV_query_resource_tag", extensions);
  GARCH_GL_NV_register_combiners = hasExt("GL_NV_register_combiners", extensions);
  GARCH_GL_NV_register_combiners2 = hasExt("GL_NV_register_combiners2", extensions);
  GARCH_GL_NV_representative_fragment_test = hasExt("GL_NV_representative_fragment_test",
                                                    extensions);
  GARCH_GL_NV_robustness_video_memory_purge = hasExt("GL_NV_robustness_video_memory_purge",
                                                     extensions);
  GARCH_GL_NV_sample_locations = hasExt("GL_NV_sample_locations", extensions);
  GARCH_GL_NV_sample_mask_override_coverage = hasExt("GL_NV_sample_mask_override_coverage",
                                                     extensions);
  GARCH_GL_NV_scissor_exclusive = hasExt("GL_NV_scissor_exclusive", extensions);
  GARCH_GL_NV_shader_atomic_counters = hasExt("GL_NV_shader_atomic_counters", extensions);
  GARCH_GL_NV_shader_atomic_float = hasExt("GL_NV_shader_atomic_float", extensions);
  GARCH_GL_NV_shader_atomic_float64 = hasExt("GL_NV_shader_atomic_float64", extensions);
  GARCH_GL_NV_shader_atomic_fp16_vector = hasExt("GL_NV_shader_atomic_fp16_vector", extensions);
  GARCH_GL_NV_shader_atomic_int64 = hasExt("GL_NV_shader_atomic_int64", extensions);
  GARCH_GL_NV_shader_buffer_load = hasExt("GL_NV_shader_buffer_load", extensions);
  GARCH_GL_NV_shader_buffer_store = hasExt("GL_NV_shader_buffer_store", extensions);
  GARCH_GL_NV_shader_storage_buffer_object = hasExt("GL_NV_shader_storage_buffer_object",
                                                    extensions);
  GARCH_GL_NV_shader_subgroup_partitioned = hasExt("GL_NV_shader_subgroup_partitioned",
                                                   extensions);
  GARCH_GL_NV_shader_texture_footprint = hasExt("GL_NV_shader_texture_footprint", extensions);
  GARCH_GL_NV_shader_thread_group = hasExt("GL_NV_shader_thread_group", extensions);
  GARCH_GL_NV_shader_thread_shuffle = hasExt("GL_NV_shader_thread_shuffle", extensions);
  GARCH_GL_NV_shading_rate_image = hasExt("GL_NV_shading_rate_image", extensions);
  GARCH_GL_NV_stereo_view_rendering = hasExt("GL_NV_stereo_view_rendering", extensions);
  GARCH_GL_NV_tessellation_program5 = hasExt("GL_NV_tessellation_program5", extensions);
  GARCH_GL_NV_texgen_emboss = hasExt("GL_NV_texgen_emboss", extensions);
  GARCH_GL_NV_texgen_reflection = hasExt("GL_NV_texgen_reflection", extensions);
  GARCH_GL_NV_texture_barrier = hasExt("GL_NV_texture_barrier", extensions);
  GARCH_GL_NV_texture_compression_vtc = hasExt("GL_NV_texture_compression_vtc", extensions);
  GARCH_GL_NV_texture_env_combine4 = hasExt("GL_NV_texture_env_combine4", extensions);
  GARCH_GL_NV_texture_expand_normal = hasExt("GL_NV_texture_expand_normal", extensions);
  GARCH_GL_NV_texture_multisample = hasExt("GL_NV_texture_multisample", extensions);
  GARCH_GL_NV_texture_rectangle = hasExt("GL_NV_texture_rectangle", extensions);
  GARCH_GL_NV_texture_rectangle_compressed = hasExt("GL_NV_texture_rectangle_compressed",
                                                    extensions);
  GARCH_GL_NV_texture_shader = hasExt("GL_NV_texture_shader", extensions);
  GARCH_GL_NV_texture_shader2 = hasExt("GL_NV_texture_shader2", extensions);
  GARCH_GL_NV_texture_shader3 = hasExt("GL_NV_texture_shader3", extensions);
  GARCH_GL_NV_transform_feedback = hasExt("GL_NV_transform_feedback", extensions);
  GARCH_GL_NV_transform_feedback2 = hasExt("GL_NV_transform_feedback2", extensions);
  GARCH_GL_NV_uniform_buffer_unified_memory = hasExt("GL_NV_uniform_buffer_unified_memory",
                                                     extensions);
  GARCH_GL_NV_vdpau_interop = hasExt("GL_NV_vdpau_interop", extensions);
  GARCH_GL_NV_vdpau_interop2 = hasExt("GL_NV_vdpau_interop2", extensions);
  GARCH_GL_NV_vertex_array_range = hasExt("GL_NV_vertex_array_range", extensions);
  GARCH_GL_NV_vertex_array_range2 = hasExt("GL_NV_vertex_array_range2", extensions);
  GARCH_GL_NV_vertex_attrib_integer_64bit = hasExt("GL_NV_vertex_attrib_integer_64bit",
                                                   extensions);
  GARCH_GL_NV_vertex_buffer_unified_memory = hasExt("GL_NV_vertex_buffer_unified_memory",
                                                    extensions);
  GARCH_GL_NV_vertex_program = hasExt("GL_NV_vertex_program", extensions);
  GARCH_GL_NV_vertex_program1_1 = hasExt("GL_NV_vertex_program1_1", extensions);
  GARCH_GL_NV_vertex_program2 = hasExt("GL_NV_vertex_program2", extensions);
  GARCH_GL_NV_vertex_program2_option = hasExt("GL_NV_vertex_program2_option", extensions);
  GARCH_GL_NV_vertex_program3 = hasExt("GL_NV_vertex_program3", extensions);
  GARCH_GL_NV_vertex_program4 = hasExt("GL_NV_vertex_program4", extensions);
  GARCH_GL_NV_video_capture = hasExt("GL_NV_video_capture", extensions);
  GARCH_GL_NV_viewport_array2 = hasExt("GL_NV_viewport_array2", extensions);
  GARCH_GL_NV_viewport_swizzle = hasExt("GL_NV_viewport_swizzle", extensions);
  GARCH_GL_EXT_texture_shadow_lod = hasExt("GL_EXT_texture_shadow_lod", extensions);

  glAccum = (PFNGLACCUMPROC)loadFunction("glAccum");
  glActiveProgramEXT = (PFNGLACTIVEPROGRAMEXTPROC)loadFunction("glActiveProgramEXT");
  glActiveShaderProgram = (PFNGLACTIVESHADERPROGRAMPROC)loadFunction("glActiveShaderProgram");
  glActiveShaderProgramEXT = (PFNGLACTIVESHADERPROGRAMEXTPROC)loadFunction(
      "glActiveShaderProgramEXT");
  glActiveStencilFaceEXT = (PFNGLACTIVESTENCILFACEEXTPROC)loadFunction("glActiveStencilFaceEXT");
  glActiveTexture = (PFNGLACTIVETEXTUREPROC)loadFunction("glActiveTexture");
  glActiveTextureARB = (PFNGLACTIVETEXTUREARBPROC)loadFunction("glActiveTextureARB");
  glActiveVaryingNV = (PFNGLACTIVEVARYINGNVPROC)loadFunction("glActiveVaryingNV");
  glAlphaFunc = (PFNGLALPHAFUNCPROC)loadFunction("glAlphaFunc");
  glAlphaToCoverageDitherControlNV = (PFNGLALPHATOCOVERAGEDITHERCONTROLNVPROC)loadFunction(
      "glAlphaToCoverageDitherControlNV");
  glApplyFramebufferAttachmentCMAAINTEL = (PFNGLAPPLYFRAMEBUFFERATTACHMENTCMAAINTELPROC)
      loadFunction("glApplyFramebufferAttachmentCMAAINTEL");
  glApplyTextureEXT = (PFNGLAPPLYTEXTUREEXTPROC)loadFunction("glApplyTextureEXT");
  glAcquireKeyedMutexWin32EXT = (PFNGLACQUIREKEYEDMUTEXWIN32EXTPROC)loadFunction(
      "glAcquireKeyedMutexWin32EXT");
  glAreProgramsResidentNV = (PFNGLAREPROGRAMSRESIDENTNVPROC)loadFunction(
      "glAreProgramsResidentNV");
  glAreTexturesResident = (PFNGLARETEXTURESRESIDENTPROC)loadFunction("glAreTexturesResident");
  glAreTexturesResidentEXT = (PFNGLARETEXTURESRESIDENTEXTPROC)loadFunction(
      "glAreTexturesResidentEXT");
  glArrayElement = (PFNGLARRAYELEMENTPROC)loadFunction("glArrayElement");
  glArrayElementEXT = (PFNGLARRAYELEMENTEXTPROC)loadFunction("glArrayElementEXT");
  glAsyncCopyBufferSubDataNVX = (PFNGLASYNCCOPYBUFFERSUBDATANVXPROC)loadFunction(
      "glAsyncCopyBufferSubDataNVX");
  glAsyncCopyImageSubDataNVX = (PFNGLASYNCCOPYIMAGESUBDATANVXPROC)loadFunction(
      "glAsyncCopyImageSubDataNVX");
  glAttachObjectARB = (PFNGLATTACHOBJECTARBPROC)loadFunction("glAttachObjectARB");
  glAttachShader = (PFNGLATTACHSHADERPROC)loadFunction("glAttachShader");
  glBegin = (PFNGLBEGINPROC)loadFunction("glBegin");
  glBeginConditionalRender = (PFNGLBEGINCONDITIONALRENDERPROC)loadFunction(
      "glBeginConditionalRender");
  glBeginConditionalRenderNV = (PFNGLBEGINCONDITIONALRENDERNVPROC)loadFunction(
      "glBeginConditionalRenderNV");
  glBeginConditionalRenderNVX = (PFNGLBEGINCONDITIONALRENDERNVXPROC)loadFunction(
      "glBeginConditionalRenderNVX");
  glBeginOcclusionQueryNV = (PFNGLBEGINOCCLUSIONQUERYNVPROC)loadFunction(
      "glBeginOcclusionQueryNV");
  glBeginPerfMonitorAMD = (PFNGLBEGINPERFMONITORAMDPROC)loadFunction("glBeginPerfMonitorAMD");
  glBeginPerfQueryINTEL = (PFNGLBEGINPERFQUERYINTELPROC)loadFunction("glBeginPerfQueryINTEL");
  glBeginQuery = (PFNGLBEGINQUERYPROC)loadFunction("glBeginQuery");
  glBeginQueryARB = (PFNGLBEGINQUERYARBPROC)loadFunction("glBeginQueryARB");
  glBeginQueryIndexed = (PFNGLBEGINQUERYINDEXEDPROC)loadFunction("glBeginQueryIndexed");
  glBeginTransformFeedback = (PFNGLBEGINTRANSFORMFEEDBACKPROC)loadFunction(
      "glBeginTransformFeedback");
  glBeginTransformFeedbackEXT = (PFNGLBEGINTRANSFORMFEEDBACKEXTPROC)loadFunction(
      "glBeginTransformFeedbackEXT");
  glBeginTransformFeedbackNV = (PFNGLBEGINTRANSFORMFEEDBACKNVPROC)loadFunction(
      "glBeginTransformFeedbackNV");
  glBeginVertexShaderEXT = (PFNGLBEGINVERTEXSHADEREXTPROC)loadFunction("glBeginVertexShaderEXT");
  glBeginVideoCaptureNV = (PFNGLBEGINVIDEOCAPTURENVPROC)loadFunction("glBeginVideoCaptureNV");
  glBindAttribLocation = (PFNGLBINDATTRIBLOCATIONPROC)loadFunction("glBindAttribLocation");
  glBindAttribLocationARB = (PFNGLBINDATTRIBLOCATIONARBPROC)loadFunction(
      "glBindAttribLocationARB");
  glBindBuffer = (PFNGLBINDBUFFERPROC)loadFunction("glBindBuffer");
  glBindBufferARB = (PFNGLBINDBUFFERARBPROC)loadFunction("glBindBufferARB");
  glBindBufferBase = (PFNGLBINDBUFFERBASEPROC)loadFunction("glBindBufferBase");
  glBindBufferBaseEXT = (PFNGLBINDBUFFERBASEEXTPROC)loadFunction("glBindBufferBaseEXT");
  glBindBufferBaseNV = (PFNGLBINDBUFFERBASENVPROC)loadFunction("glBindBufferBaseNV");
  glBindBufferOffsetEXT = (PFNGLBINDBUFFEROFFSETEXTPROC)loadFunction("glBindBufferOffsetEXT");
  glBindBufferOffsetNV = (PFNGLBINDBUFFEROFFSETNVPROC)loadFunction("glBindBufferOffsetNV");
  glBindBufferRange = (PFNGLBINDBUFFERRANGEPROC)loadFunction("glBindBufferRange");
  glBindBufferRangeEXT = (PFNGLBINDBUFFERRANGEEXTPROC)loadFunction("glBindBufferRangeEXT");
  glBindBufferRangeNV = (PFNGLBINDBUFFERRANGENVPROC)loadFunction("glBindBufferRangeNV");
  glBindBuffersBase = (PFNGLBINDBUFFERSBASEPROC)loadFunction("glBindBuffersBase");
  glBindBuffersRange = (PFNGLBINDBUFFERSRANGEPROC)loadFunction("glBindBuffersRange");
  glBindFragDataLocation = (PFNGLBINDFRAGDATALOCATIONPROC)loadFunction("glBindFragDataLocation");
  glBindFragDataLocationEXT = (PFNGLBINDFRAGDATALOCATIONEXTPROC)loadFunction(
      "glBindFragDataLocationEXT");
  glBindFragDataLocationIndexed = (PFNGLBINDFRAGDATALOCATIONINDEXEDPROC)loadFunction(
      "glBindFragDataLocationIndexed");
  glBindFramebuffer = (PFNGLBINDFRAMEBUFFERPROC)loadFunction("glBindFramebuffer");
  glBindFramebufferEXT = (PFNGLBINDFRAMEBUFFEREXTPROC)loadFunction("glBindFramebufferEXT");
  glBindImageTexture = (PFNGLBINDIMAGETEXTUREPROC)loadFunction("glBindImageTexture");
  glBindImageTextureEXT = (PFNGLBINDIMAGETEXTUREEXTPROC)loadFunction("glBindImageTextureEXT");
  glBindImageTextures = (PFNGLBINDIMAGETEXTURESPROC)loadFunction("glBindImageTextures");
  glBindLightParameterEXT = (PFNGLBINDLIGHTPARAMETEREXTPROC)loadFunction(
      "glBindLightParameterEXT");
  glBindMaterialParameterEXT = (PFNGLBINDMATERIALPARAMETEREXTPROC)loadFunction(
      "glBindMaterialParameterEXT");
  glBindMultiTextureEXT = (PFNGLBINDMULTITEXTUREEXTPROC)loadFunction("glBindMultiTextureEXT");
  glBindParameterEXT = (PFNGLBINDPARAMETEREXTPROC)loadFunction("glBindParameterEXT");
  glBindProgramARB = (PFNGLBINDPROGRAMARBPROC)loadFunction("glBindProgramARB");
  glBindProgramNV = (PFNGLBINDPROGRAMNVPROC)loadFunction("glBindProgramNV");
  glBindProgramPipeline = (PFNGLBINDPROGRAMPIPELINEPROC)loadFunction("glBindProgramPipeline");
  glBindProgramPipelineEXT = (PFNGLBINDPROGRAMPIPELINEEXTPROC)loadFunction(
      "glBindProgramPipelineEXT");
  glBindRenderbuffer = (PFNGLBINDRENDERBUFFERPROC)loadFunction("glBindRenderbuffer");
  glBindRenderbufferEXT = (PFNGLBINDRENDERBUFFEREXTPROC)loadFunction("glBindRenderbufferEXT");
  glBindSampler = (PFNGLBINDSAMPLERPROC)loadFunction("glBindSampler");
  glBindSamplers = (PFNGLBINDSAMPLERSPROC)loadFunction("glBindSamplers");
  glBindShadingRateImageNV = (PFNGLBINDSHADINGRATEIMAGENVPROC)loadFunction(
      "glBindShadingRateImageNV");
  glBindTexGenParameterEXT = (PFNGLBINDTEXGENPARAMETEREXTPROC)loadFunction(
      "glBindTexGenParameterEXT");
  glBindTexture = (PFNGLBINDTEXTUREPROC)loadFunction("glBindTexture");
  glBindTextureEXT = (PFNGLBINDTEXTUREEXTPROC)loadFunction("glBindTextureEXT");
  glBindTextureUnit = (PFNGLBINDTEXTUREUNITPROC)loadFunction("glBindTextureUnit");
  glBindTextureUnitParameterEXT = (PFNGLBINDTEXTUREUNITPARAMETEREXTPROC)loadFunction(
      "glBindTextureUnitParameterEXT");
  glBindTextures = (PFNGLBINDTEXTURESPROC)loadFunction("glBindTextures");
  glBindTransformFeedback = (PFNGLBINDTRANSFORMFEEDBACKPROC)loadFunction(
      "glBindTransformFeedback");
  glBindTransformFeedbackNV = (PFNGLBINDTRANSFORMFEEDBACKNVPROC)loadFunction(
      "glBindTransformFeedbackNV");
  glBindVertexArray = (PFNGLBINDVERTEXARRAYPROC)loadFunction("glBindVertexArray");
  glBindVertexArrayAPPLE = (PFNGLBINDVERTEXARRAYAPPLEPROC)loadFunction("glBindVertexArrayAPPLE");
  glBindVertexBuffer = (PFNGLBINDVERTEXBUFFERPROC)loadFunction("glBindVertexBuffer");
  glBindVertexBuffers = (PFNGLBINDVERTEXBUFFERSPROC)loadFunction("glBindVertexBuffers");
  glBindVertexShaderEXT = (PFNGLBINDVERTEXSHADEREXTPROC)loadFunction("glBindVertexShaderEXT");
  glBindVideoCaptureStreamBufferNV = (PFNGLBINDVIDEOCAPTURESTREAMBUFFERNVPROC)loadFunction(
      "glBindVideoCaptureStreamBufferNV");
  glBindVideoCaptureStreamTextureNV = (PFNGLBINDVIDEOCAPTURESTREAMTEXTURENVPROC)loadFunction(
      "glBindVideoCaptureStreamTextureNV");
  glBinormal3bEXT = (PFNGLBINORMAL3BEXTPROC)loadFunction("glBinormal3bEXT");
  glBinormal3bvEXT = (PFNGLBINORMAL3BVEXTPROC)loadFunction("glBinormal3bvEXT");
  glBinormal3dEXT = (PFNGLBINORMAL3DEXTPROC)loadFunction("glBinormal3dEXT");
  glBinormal3dvEXT = (PFNGLBINORMAL3DVEXTPROC)loadFunction("glBinormal3dvEXT");
  glBinormal3fEXT = (PFNGLBINORMAL3FEXTPROC)loadFunction("glBinormal3fEXT");
  glBinormal3fvEXT = (PFNGLBINORMAL3FVEXTPROC)loadFunction("glBinormal3fvEXT");
  glBinormal3iEXT = (PFNGLBINORMAL3IEXTPROC)loadFunction("glBinormal3iEXT");
  glBinormal3ivEXT = (PFNGLBINORMAL3IVEXTPROC)loadFunction("glBinormal3ivEXT");
  glBinormal3sEXT = (PFNGLBINORMAL3SEXTPROC)loadFunction("glBinormal3sEXT");
  glBinormal3svEXT = (PFNGLBINORMAL3SVEXTPROC)loadFunction("glBinormal3svEXT");
  glBinormalPointerEXT = (PFNGLBINORMALPOINTEREXTPROC)loadFunction("glBinormalPointerEXT");
  glBitmap = (PFNGLBITMAPPROC)loadFunction("glBitmap");
  glBlendBarrierKHR = (PFNGLBLENDBARRIERKHRPROC)loadFunction("glBlendBarrierKHR");
  glBlendBarrierNV = (PFNGLBLENDBARRIERNVPROC)loadFunction("glBlendBarrierNV");
  glBlendColor = (PFNGLBLENDCOLORPROC)loadFunction("glBlendColor");
  glBlendColorEXT = (PFNGLBLENDCOLOREXTPROC)loadFunction("glBlendColorEXT");
  glBlendEquation = (PFNGLBLENDEQUATIONPROC)loadFunction("glBlendEquation");
  glBlendEquationEXT = (PFNGLBLENDEQUATIONEXTPROC)loadFunction("glBlendEquationEXT");
  glBlendEquationIndexedAMD = (PFNGLBLENDEQUATIONINDEXEDAMDPROC)loadFunction(
      "glBlendEquationIndexedAMD");
  glBlendEquationSeparate = (PFNGLBLENDEQUATIONSEPARATEPROC)loadFunction(
      "glBlendEquationSeparate");
  glBlendEquationSeparateEXT = (PFNGLBLENDEQUATIONSEPARATEEXTPROC)loadFunction(
      "glBlendEquationSeparateEXT");
  glBlendEquationSeparateIndexedAMD = (PFNGLBLENDEQUATIONSEPARATEINDEXEDAMDPROC)loadFunction(
      "glBlendEquationSeparateIndexedAMD");
  glBlendEquationSeparatei = (PFNGLBLENDEQUATIONSEPARATEIPROC)loadFunction(
      "glBlendEquationSeparatei");
  glBlendEquationSeparateiARB = (PFNGLBLENDEQUATIONSEPARATEIARBPROC)loadFunction(
      "glBlendEquationSeparateiARB");
  glBlendEquationi = (PFNGLBLENDEQUATIONIPROC)loadFunction("glBlendEquationi");
  glBlendEquationiARB = (PFNGLBLENDEQUATIONIARBPROC)loadFunction("glBlendEquationiARB");
  glBlendFunc = (PFNGLBLENDFUNCPROC)loadFunction("glBlendFunc");
  glBlendFuncIndexedAMD = (PFNGLBLENDFUNCINDEXEDAMDPROC)loadFunction("glBlendFuncIndexedAMD");
  glBlendFuncSeparate = (PFNGLBLENDFUNCSEPARATEPROC)loadFunction("glBlendFuncSeparate");
  glBlendFuncSeparateEXT = (PFNGLBLENDFUNCSEPARATEEXTPROC)loadFunction("glBlendFuncSeparateEXT");
  glBlendFuncSeparateIndexedAMD = (PFNGLBLENDFUNCSEPARATEINDEXEDAMDPROC)loadFunction(
      "glBlendFuncSeparateIndexedAMD");
  glBlendFuncSeparatei = (PFNGLBLENDFUNCSEPARATEIPROC)loadFunction("glBlendFuncSeparatei");
  glBlendFuncSeparateiARB = (PFNGLBLENDFUNCSEPARATEIARBPROC)loadFunction(
      "glBlendFuncSeparateiARB");
  glBlendFunci = (PFNGLBLENDFUNCIPROC)loadFunction("glBlendFunci");
  glBlendFunciARB = (PFNGLBLENDFUNCIARBPROC)loadFunction("glBlendFunciARB");
  glBlendParameteriNV = (PFNGLBLENDPARAMETERINVPROC)loadFunction("glBlendParameteriNV");
  glBlitFramebuffer = (PFNGLBLITFRAMEBUFFERPROC)loadFunction("glBlitFramebuffer");
  glBlitFramebufferEXT = (PFNGLBLITFRAMEBUFFEREXTPROC)loadFunction("glBlitFramebufferEXT");
  glBlitNamedFramebuffer = (PFNGLBLITNAMEDFRAMEBUFFERPROC)loadFunction("glBlitNamedFramebuffer");
  glBufferAddressRangeNV = (PFNGLBUFFERADDRESSRANGENVPROC)loadFunction("glBufferAddressRangeNV");
  glBufferAttachMemoryNV = (PFNGLBUFFERATTACHMEMORYNVPROC)loadFunction("glBufferAttachMemoryNV");
  glBufferData = (PFNGLBUFFERDATAPROC)loadFunction("glBufferData");
  glBufferDataARB = (PFNGLBUFFERDATAARBPROC)loadFunction("glBufferDataARB");
  glBufferPageCommitmentARB = (PFNGLBUFFERPAGECOMMITMENTARBPROC)loadFunction(
      "glBufferPageCommitmentARB");
  glBufferPageCommitmentMemNV = (PFNGLBUFFERPAGECOMMITMENTMEMNVPROC)loadFunction(
      "glBufferPageCommitmentMemNV");
  glBufferParameteriAPPLE = (PFNGLBUFFERPARAMETERIAPPLEPROC)loadFunction(
      "glBufferParameteriAPPLE");
  glBufferStorage = (PFNGLBUFFERSTORAGEPROC)loadFunction("glBufferStorage");
  glBufferStorageExternalEXT = (PFNGLBUFFERSTORAGEEXTERNALEXTPROC)loadFunction(
      "glBufferStorageExternalEXT");
  glBufferStorageMemEXT = (PFNGLBUFFERSTORAGEMEMEXTPROC)loadFunction("glBufferStorageMemEXT");
  glBufferSubData = (PFNGLBUFFERSUBDATAPROC)loadFunction("glBufferSubData");
  glBufferSubDataARB = (PFNGLBUFFERSUBDATAARBPROC)loadFunction("glBufferSubDataARB");
  glCallCommandListNV = (PFNGLCALLCOMMANDLISTNVPROC)loadFunction("glCallCommandListNV");
  glCallList = (PFNGLCALLLISTPROC)loadFunction("glCallList");
  glCallLists = (PFNGLCALLLISTSPROC)loadFunction("glCallLists");
  glCheckFramebufferStatus = (PFNGLCHECKFRAMEBUFFERSTATUSPROC)loadFunction(
      "glCheckFramebufferStatus");
  glCheckFramebufferStatusEXT = (PFNGLCHECKFRAMEBUFFERSTATUSEXTPROC)loadFunction(
      "glCheckFramebufferStatusEXT");
  glCheckNamedFramebufferStatus = (PFNGLCHECKNAMEDFRAMEBUFFERSTATUSPROC)loadFunction(
      "glCheckNamedFramebufferStatus");
  glCheckNamedFramebufferStatusEXT = (PFNGLCHECKNAMEDFRAMEBUFFERSTATUSEXTPROC)loadFunction(
      "glCheckNamedFramebufferStatusEXT");
  glClampColor = (PFNGLCLAMPCOLORPROC)loadFunction("glClampColor");
  glClampColorARB = (PFNGLCLAMPCOLORARBPROC)loadFunction("glClampColorARB");
  glClear = (PFNGLCLEARPROC)loadFunction("glClear");
  glClearAccum = (PFNGLCLEARACCUMPROC)loadFunction("glClearAccum");
  glClearBufferData = (PFNGLCLEARBUFFERDATAPROC)loadFunction("glClearBufferData");
  glClearBufferSubData = (PFNGLCLEARBUFFERSUBDATAPROC)loadFunction("glClearBufferSubData");
  glClearBufferfi = (PFNGLCLEARBUFFERFIPROC)loadFunction("glClearBufferfi");
  glClearBufferfv = (PFNGLCLEARBUFFERFVPROC)loadFunction("glClearBufferfv");
  glClearBufferiv = (PFNGLCLEARBUFFERIVPROC)loadFunction("glClearBufferiv");
  glClearBufferuiv = (PFNGLCLEARBUFFERUIVPROC)loadFunction("glClearBufferuiv");
  glClearColor = (PFNGLCLEARCOLORPROC)loadFunction("glClearColor");
  glClearColorIiEXT = (PFNGLCLEARCOLORIIEXTPROC)loadFunction("glClearColorIiEXT");
  glClearColorIuiEXT = (PFNGLCLEARCOLORIUIEXTPROC)loadFunction("glClearColorIuiEXT");
  glClearDepth = (PFNGLCLEARDEPTHPROC)loadFunction("glClearDepth");
  glClearDepthdNV = (PFNGLCLEARDEPTHDNVPROC)loadFunction("glClearDepthdNV");
  glClearDepthf = (PFNGLCLEARDEPTHFPROC)loadFunction("glClearDepthf");
  glClearIndex = (PFNGLCLEARINDEXPROC)loadFunction("glClearIndex");
  glClearNamedBufferData = (PFNGLCLEARNAMEDBUFFERDATAPROC)loadFunction("glClearNamedBufferData");
  glClearNamedBufferDataEXT = (PFNGLCLEARNAMEDBUFFERDATAEXTPROC)loadFunction(
      "glClearNamedBufferDataEXT");
  glClearNamedBufferSubData = (PFNGLCLEARNAMEDBUFFERSUBDATAPROC)loadFunction(
      "glClearNamedBufferSubData");
  glClearNamedBufferSubDataEXT = (PFNGLCLEARNAMEDBUFFERSUBDATAEXTPROC)loadFunction(
      "glClearNamedBufferSubDataEXT");
  glClearNamedFramebufferfi = (PFNGLCLEARNAMEDFRAMEBUFFERFIPROC)loadFunction(
      "glClearNamedFramebufferfi");
  glClearNamedFramebufferfv = (PFNGLCLEARNAMEDFRAMEBUFFERFVPROC)loadFunction(
      "glClearNamedFramebufferfv");
  glClearNamedFramebufferiv = (PFNGLCLEARNAMEDFRAMEBUFFERIVPROC)loadFunction(
      "glClearNamedFramebufferiv");
  glClearNamedFramebufferuiv = (PFNGLCLEARNAMEDFRAMEBUFFERUIVPROC)loadFunction(
      "glClearNamedFramebufferuiv");
  glClearStencil = (PFNGLCLEARSTENCILPROC)loadFunction("glClearStencil");
  glClearTexImage = (PFNGLCLEARTEXIMAGEPROC)loadFunction("glClearTexImage");
  glClearTexSubImage = (PFNGLCLEARTEXSUBIMAGEPROC)loadFunction("glClearTexSubImage");
  glClientActiveTexture = (PFNGLCLIENTACTIVETEXTUREPROC)loadFunction("glClientActiveTexture");
  glClientActiveTextureARB = (PFNGLCLIENTACTIVETEXTUREARBPROC)loadFunction(
      "glClientActiveTextureARB");
  glClientAttribDefaultEXT = (PFNGLCLIENTATTRIBDEFAULTEXTPROC)loadFunction(
      "glClientAttribDefaultEXT");
  glClientWaitSemaphoreui64NVX = (PFNGLCLIENTWAITSEMAPHOREUI64NVXPROC)loadFunction(
      "glClientWaitSemaphoreui64NVX");
  glClientWaitSync = (PFNGLCLIENTWAITSYNCPROC)loadFunction("glClientWaitSync");
  glClipControl = (PFNGLCLIPCONTROLPROC)loadFunction("glClipControl");
  glClipPlane = (PFNGLCLIPPLANEPROC)loadFunction("glClipPlane");
  glColor3b = (PFNGLCOLOR3BPROC)loadFunction("glColor3b");
  glColor3bv = (PFNGLCOLOR3BVPROC)loadFunction("glColor3bv");
  glColor3d = (PFNGLCOLOR3DPROC)loadFunction("glColor3d");
  glColor3dv = (PFNGLCOLOR3DVPROC)loadFunction("glColor3dv");
  glColor3f = (PFNGLCOLOR3FPROC)loadFunction("glColor3f");
  glColor3fv = (PFNGLCOLOR3FVPROC)loadFunction("glColor3fv");
  glColor3hNV = (PFNGLCOLOR3HNVPROC)loadFunction("glColor3hNV");
  glColor3hvNV = (PFNGLCOLOR3HVNVPROC)loadFunction("glColor3hvNV");
  glColor3i = (PFNGLCOLOR3IPROC)loadFunction("glColor3i");
  glColor3iv = (PFNGLCOLOR3IVPROC)loadFunction("glColor3iv");
  glColor3s = (PFNGLCOLOR3SPROC)loadFunction("glColor3s");
  glColor3sv = (PFNGLCOLOR3SVPROC)loadFunction("glColor3sv");
  glColor3ub = (PFNGLCOLOR3UBPROC)loadFunction("glColor3ub");
  glColor3ubv = (PFNGLCOLOR3UBVPROC)loadFunction("glColor3ubv");
  glColor3ui = (PFNGLCOLOR3UIPROC)loadFunction("glColor3ui");
  glColor3uiv = (PFNGLCOLOR3UIVPROC)loadFunction("glColor3uiv");
  glColor3us = (PFNGLCOLOR3USPROC)loadFunction("glColor3us");
  glColor3usv = (PFNGLCOLOR3USVPROC)loadFunction("glColor3usv");
  glColor4b = (PFNGLCOLOR4BPROC)loadFunction("glColor4b");
  glColor4bv = (PFNGLCOLOR4BVPROC)loadFunction("glColor4bv");
  glColor4d = (PFNGLCOLOR4DPROC)loadFunction("glColor4d");
  glColor4dv = (PFNGLCOLOR4DVPROC)loadFunction("glColor4dv");
  glColor4f = (PFNGLCOLOR4FPROC)loadFunction("glColor4f");
  glColor4fv = (PFNGLCOLOR4FVPROC)loadFunction("glColor4fv");
  glColor4hNV = (PFNGLCOLOR4HNVPROC)loadFunction("glColor4hNV");
  glColor4hvNV = (PFNGLCOLOR4HVNVPROC)loadFunction("glColor4hvNV");
  glColor4i = (PFNGLCOLOR4IPROC)loadFunction("glColor4i");
  glColor4iv = (PFNGLCOLOR4IVPROC)loadFunction("glColor4iv");
  glColor4s = (PFNGLCOLOR4SPROC)loadFunction("glColor4s");
  glColor4sv = (PFNGLCOLOR4SVPROC)loadFunction("glColor4sv");
  glColor4ub = (PFNGLCOLOR4UBPROC)loadFunction("glColor4ub");
  glColor4ubv = (PFNGLCOLOR4UBVPROC)loadFunction("glColor4ubv");
  glColor4ui = (PFNGLCOLOR4UIPROC)loadFunction("glColor4ui");
  glColor4uiv = (PFNGLCOLOR4UIVPROC)loadFunction("glColor4uiv");
  glColor4us = (PFNGLCOLOR4USPROC)loadFunction("glColor4us");
  glColor4usv = (PFNGLCOLOR4USVPROC)loadFunction("glColor4usv");
  glColorFormatNV = (PFNGLCOLORFORMATNVPROC)loadFunction("glColorFormatNV");
  glColorMask = (PFNGLCOLORMASKPROC)loadFunction("glColorMask");
  glColorMaskIndexedEXT = (PFNGLCOLORMASKINDEXEDEXTPROC)loadFunction("glColorMaskIndexedEXT");
  glColorMaski = (PFNGLCOLORMASKIPROC)loadFunction("glColorMaski");
  glColorMaterial = (PFNGLCOLORMATERIALPROC)loadFunction("glColorMaterial");
  glColorP3ui = (PFNGLCOLORP3UIPROC)loadFunction("glColorP3ui");
  glColorP3uiv = (PFNGLCOLORP3UIVPROC)loadFunction("glColorP3uiv");
  glColorP4ui = (PFNGLCOLORP4UIPROC)loadFunction("glColorP4ui");
  glColorP4uiv = (PFNGLCOLORP4UIVPROC)loadFunction("glColorP4uiv");
  glColorPointer = (PFNGLCOLORPOINTERPROC)loadFunction("glColorPointer");
  glColorPointerEXT = (PFNGLCOLORPOINTEREXTPROC)loadFunction("glColorPointerEXT");
  glColorPointervINTEL = (PFNGLCOLORPOINTERVINTELPROC)loadFunction("glColorPointervINTEL");
  glColorSubTable = (PFNGLCOLORSUBTABLEPROC)loadFunction("glColorSubTable");
  glColorSubTableEXT = (PFNGLCOLORSUBTABLEEXTPROC)loadFunction("glColorSubTableEXT");
  glColorTable = (PFNGLCOLORTABLEPROC)loadFunction("glColorTable");
  glColorTableEXT = (PFNGLCOLORTABLEEXTPROC)loadFunction("glColorTableEXT");
  glColorTableParameterfv = (PFNGLCOLORTABLEPARAMETERFVPROC)loadFunction(
      "glColorTableParameterfv");
  glColorTableParameteriv = (PFNGLCOLORTABLEPARAMETERIVPROC)loadFunction(
      "glColorTableParameteriv");
  glCombinerInputNV = (PFNGLCOMBINERINPUTNVPROC)loadFunction("glCombinerInputNV");
  glCombinerOutputNV = (PFNGLCOMBINEROUTPUTNVPROC)loadFunction("glCombinerOutputNV");
  glCombinerParameterfNV = (PFNGLCOMBINERPARAMETERFNVPROC)loadFunction("glCombinerParameterfNV");
  glCombinerParameterfvNV = (PFNGLCOMBINERPARAMETERFVNVPROC)loadFunction(
      "glCombinerParameterfvNV");
  glCombinerParameteriNV = (PFNGLCOMBINERPARAMETERINVPROC)loadFunction("glCombinerParameteriNV");
  glCombinerParameterivNV = (PFNGLCOMBINERPARAMETERIVNVPROC)loadFunction(
      "glCombinerParameterivNV");
  glCombinerStageParameterfvNV = (PFNGLCOMBINERSTAGEPARAMETERFVNVPROC)loadFunction(
      "glCombinerStageParameterfvNV");
  glCommandListSegmentsNV = (PFNGLCOMMANDLISTSEGMENTSNVPROC)loadFunction(
      "glCommandListSegmentsNV");
  glCompileCommandListNV = (PFNGLCOMPILECOMMANDLISTNVPROC)loadFunction("glCompileCommandListNV");
  glCompileShader = (PFNGLCOMPILESHADERPROC)loadFunction("glCompileShader");
  glCompileShaderARB = (PFNGLCOMPILESHADERARBPROC)loadFunction("glCompileShaderARB");
  glCompileShaderIncludeARB = (PFNGLCOMPILESHADERINCLUDEARBPROC)loadFunction(
      "glCompileShaderIncludeARB");
  glCompressedMultiTexImage1DEXT = (PFNGLCOMPRESSEDMULTITEXIMAGE1DEXTPROC)loadFunction(
      "glCompressedMultiTexImage1DEXT");
  glCompressedMultiTexImage2DEXT = (PFNGLCOMPRESSEDMULTITEXIMAGE2DEXTPROC)loadFunction(
      "glCompressedMultiTexImage2DEXT");
  glCompressedMultiTexImage3DEXT = (PFNGLCOMPRESSEDMULTITEXIMAGE3DEXTPROC)loadFunction(
      "glCompressedMultiTexImage3DEXT");
  glCompressedMultiTexSubImage1DEXT = (PFNGLCOMPRESSEDMULTITEXSUBIMAGE1DEXTPROC)loadFunction(
      "glCompressedMultiTexSubImage1DEXT");
  glCompressedMultiTexSubImage2DEXT = (PFNGLCOMPRESSEDMULTITEXSUBIMAGE2DEXTPROC)loadFunction(
      "glCompressedMultiTexSubImage2DEXT");
  glCompressedMultiTexSubImage3DEXT = (PFNGLCOMPRESSEDMULTITEXSUBIMAGE3DEXTPROC)loadFunction(
      "glCompressedMultiTexSubImage3DEXT");
  glCompressedTexImage1D = (PFNGLCOMPRESSEDTEXIMAGE1DPROC)loadFunction("glCompressedTexImage1D");
  glCompressedTexImage1DARB = (PFNGLCOMPRESSEDTEXIMAGE1DARBPROC)loadFunction(
      "glCompressedTexImage1DARB");
  glCompressedTexImage2D = (PFNGLCOMPRESSEDTEXIMAGE2DPROC)loadFunction("glCompressedTexImage2D");
  glCompressedTexImage2DARB = (PFNGLCOMPRESSEDTEXIMAGE2DARBPROC)loadFunction(
      "glCompressedTexImage2DARB");
  glCompressedTexImage3D = (PFNGLCOMPRESSEDTEXIMAGE3DPROC)loadFunction("glCompressedTexImage3D");
  glCompressedTexImage3DARB = (PFNGLCOMPRESSEDTEXIMAGE3DARBPROC)loadFunction(
      "glCompressedTexImage3DARB");
  glCompressedTexSubImage1D = (PFNGLCOMPRESSEDTEXSUBIMAGE1DPROC)loadFunction(
      "glCompressedTexSubImage1D");
  glCompressedTexSubImage1DARB = (PFNGLCOMPRESSEDTEXSUBIMAGE1DARBPROC)loadFunction(
      "glCompressedTexSubImage1DARB");
  glCompressedTexSubImage2D = (PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC)loadFunction(
      "glCompressedTexSubImage2D");
  glCompressedTexSubImage2DARB = (PFNGLCOMPRESSEDTEXSUBIMAGE2DARBPROC)loadFunction(
      "glCompressedTexSubImage2DARB");
  glCompressedTexSubImage3D = (PFNGLCOMPRESSEDTEXSUBIMAGE3DPROC)loadFunction(
      "glCompressedTexSubImage3D");
  glCompressedTexSubImage3DARB = (PFNGLCOMPRESSEDTEXSUBIMAGE3DARBPROC)loadFunction(
      "glCompressedTexSubImage3DARB");
  glCompressedTextureImage1DEXT = (PFNGLCOMPRESSEDTEXTUREIMAGE1DEXTPROC)loadFunction(
      "glCompressedTextureImage1DEXT");
  glCompressedTextureImage2DEXT = (PFNGLCOMPRESSEDTEXTUREIMAGE2DEXTPROC)loadFunction(
      "glCompressedTextureImage2DEXT");
  glCompressedTextureImage3DEXT = (PFNGLCOMPRESSEDTEXTUREIMAGE3DEXTPROC)loadFunction(
      "glCompressedTextureImage3DEXT");
  glCompressedTextureSubImage1D = (PFNGLCOMPRESSEDTEXTURESUBIMAGE1DPROC)loadFunction(
      "glCompressedTextureSubImage1D");
  glCompressedTextureSubImage1DEXT = (PFNGLCOMPRESSEDTEXTURESUBIMAGE1DEXTPROC)loadFunction(
      "glCompressedTextureSubImage1DEXT");
  glCompressedTextureSubImage2D = (PFNGLCOMPRESSEDTEXTURESUBIMAGE2DPROC)loadFunction(
      "glCompressedTextureSubImage2D");
  glCompressedTextureSubImage2DEXT = (PFNGLCOMPRESSEDTEXTURESUBIMAGE2DEXTPROC)loadFunction(
      "glCompressedTextureSubImage2DEXT");
  glCompressedTextureSubImage3D = (PFNGLCOMPRESSEDTEXTURESUBIMAGE3DPROC)loadFunction(
      "glCompressedTextureSubImage3D");
  glCompressedTextureSubImage3DEXT = (PFNGLCOMPRESSEDTEXTURESUBIMAGE3DEXTPROC)loadFunction(
      "glCompressedTextureSubImage3DEXT");
  glConservativeRasterParameterfNV = (PFNGLCONSERVATIVERASTERPARAMETERFNVPROC)loadFunction(
      "glConservativeRasterParameterfNV");
  glConservativeRasterParameteriNV = (PFNGLCONSERVATIVERASTERPARAMETERINVPROC)loadFunction(
      "glConservativeRasterParameteriNV");
  glConvolutionFilter1D = (PFNGLCONVOLUTIONFILTER1DPROC)loadFunction("glConvolutionFilter1D");
  glConvolutionFilter1DEXT = (PFNGLCONVOLUTIONFILTER1DEXTPROC)loadFunction(
      "glConvolutionFilter1DEXT");
  glConvolutionFilter2D = (PFNGLCONVOLUTIONFILTER2DPROC)loadFunction("glConvolutionFilter2D");
  glConvolutionFilter2DEXT = (PFNGLCONVOLUTIONFILTER2DEXTPROC)loadFunction(
      "glConvolutionFilter2DEXT");
  glConvolutionParameterf = (PFNGLCONVOLUTIONPARAMETERFPROC)loadFunction(
      "glConvolutionParameterf");
  glConvolutionParameterfEXT = (PFNGLCONVOLUTIONPARAMETERFEXTPROC)loadFunction(
      "glConvolutionParameterfEXT");
  glConvolutionParameterfv = (PFNGLCONVOLUTIONPARAMETERFVPROC)loadFunction(
      "glConvolutionParameterfv");
  glConvolutionParameterfvEXT = (PFNGLCONVOLUTIONPARAMETERFVEXTPROC)loadFunction(
      "glConvolutionParameterfvEXT");
  glConvolutionParameteri = (PFNGLCONVOLUTIONPARAMETERIPROC)loadFunction(
      "glConvolutionParameteri");
  glConvolutionParameteriEXT = (PFNGLCONVOLUTIONPARAMETERIEXTPROC)loadFunction(
      "glConvolutionParameteriEXT");
  glConvolutionParameteriv = (PFNGLCONVOLUTIONPARAMETERIVPROC)loadFunction(
      "glConvolutionParameteriv");
  glConvolutionParameterivEXT = (PFNGLCONVOLUTIONPARAMETERIVEXTPROC)loadFunction(
      "glConvolutionParameterivEXT");
  glCopyBufferSubData = (PFNGLCOPYBUFFERSUBDATAPROC)loadFunction("glCopyBufferSubData");
  glCopyColorSubTable = (PFNGLCOPYCOLORSUBTABLEPROC)loadFunction("glCopyColorSubTable");
  glCopyColorSubTableEXT = (PFNGLCOPYCOLORSUBTABLEEXTPROC)loadFunction("glCopyColorSubTableEXT");
  glCopyColorTable = (PFNGLCOPYCOLORTABLEPROC)loadFunction("glCopyColorTable");
  glCopyConvolutionFilter1D = (PFNGLCOPYCONVOLUTIONFILTER1DPROC)loadFunction(
      "glCopyConvolutionFilter1D");
  glCopyConvolutionFilter1DEXT = (PFNGLCOPYCONVOLUTIONFILTER1DEXTPROC)loadFunction(
      "glCopyConvolutionFilter1DEXT");
  glCopyConvolutionFilter2D = (PFNGLCOPYCONVOLUTIONFILTER2DPROC)loadFunction(
      "glCopyConvolutionFilter2D");
  glCopyConvolutionFilter2DEXT = (PFNGLCOPYCONVOLUTIONFILTER2DEXTPROC)loadFunction(
      "glCopyConvolutionFilter2DEXT");
  glCopyImageSubData = (PFNGLCOPYIMAGESUBDATAPROC)loadFunction("glCopyImageSubData");
  glCopyImageSubDataNV = (PFNGLCOPYIMAGESUBDATANVPROC)loadFunction("glCopyImageSubDataNV");
  glCopyMultiTexImage1DEXT = (PFNGLCOPYMULTITEXIMAGE1DEXTPROC)loadFunction(
      "glCopyMultiTexImage1DEXT");
  glCopyMultiTexImage2DEXT = (PFNGLCOPYMULTITEXIMAGE2DEXTPROC)loadFunction(
      "glCopyMultiTexImage2DEXT");
  glCopyMultiTexSubImage1DEXT = (PFNGLCOPYMULTITEXSUBIMAGE1DEXTPROC)loadFunction(
      "glCopyMultiTexSubImage1DEXT");
  glCopyMultiTexSubImage2DEXT = (PFNGLCOPYMULTITEXSUBIMAGE2DEXTPROC)loadFunction(
      "glCopyMultiTexSubImage2DEXT");
  glCopyMultiTexSubImage3DEXT = (PFNGLCOPYMULTITEXSUBIMAGE3DEXTPROC)loadFunction(
      "glCopyMultiTexSubImage3DEXT");
  glCopyNamedBufferSubData = (PFNGLCOPYNAMEDBUFFERSUBDATAPROC)loadFunction(
      "glCopyNamedBufferSubData");
  glCopyPathNV = (PFNGLCOPYPATHNVPROC)loadFunction("glCopyPathNV");
  glCopyPixels = (PFNGLCOPYPIXELSPROC)loadFunction("glCopyPixels");
  glCopyTexImage1D = (PFNGLCOPYTEXIMAGE1DPROC)loadFunction("glCopyTexImage1D");
  glCopyTexImage1DEXT = (PFNGLCOPYTEXIMAGE1DEXTPROC)loadFunction("glCopyTexImage1DEXT");
  glCopyTexImage2D = (PFNGLCOPYTEXIMAGE2DPROC)loadFunction("glCopyTexImage2D");
  glCopyTexImage2DEXT = (PFNGLCOPYTEXIMAGE2DEXTPROC)loadFunction("glCopyTexImage2DEXT");
  glCopyTexSubImage1D = (PFNGLCOPYTEXSUBIMAGE1DPROC)loadFunction("glCopyTexSubImage1D");
  glCopyTexSubImage1DEXT = (PFNGLCOPYTEXSUBIMAGE1DEXTPROC)loadFunction("glCopyTexSubImage1DEXT");
  glCopyTexSubImage2D = (PFNGLCOPYTEXSUBIMAGE2DPROC)loadFunction("glCopyTexSubImage2D");
  glCopyTexSubImage2DEXT = (PFNGLCOPYTEXSUBIMAGE2DEXTPROC)loadFunction("glCopyTexSubImage2DEXT");
  glCopyTexSubImage3D = (PFNGLCOPYTEXSUBIMAGE3DPROC)loadFunction("glCopyTexSubImage3D");
  glCopyTexSubImage3DEXT = (PFNGLCOPYTEXSUBIMAGE3DEXTPROC)loadFunction("glCopyTexSubImage3DEXT");
  glCopyTextureImage1DEXT = (PFNGLCOPYTEXTUREIMAGE1DEXTPROC)loadFunction(
      "glCopyTextureImage1DEXT");
  glCopyTextureImage2DEXT = (PFNGLCOPYTEXTUREIMAGE2DEXTPROC)loadFunction(
      "glCopyTextureImage2DEXT");
  glCopyTextureSubImage1D = (PFNGLCOPYTEXTURESUBIMAGE1DPROC)loadFunction(
      "glCopyTextureSubImage1D");
  glCopyTextureSubImage1DEXT = (PFNGLCOPYTEXTURESUBIMAGE1DEXTPROC)loadFunction(
      "glCopyTextureSubImage1DEXT");
  glCopyTextureSubImage2D = (PFNGLCOPYTEXTURESUBIMAGE2DPROC)loadFunction(
      "glCopyTextureSubImage2D");
  glCopyTextureSubImage2DEXT = (PFNGLCOPYTEXTURESUBIMAGE2DEXTPROC)loadFunction(
      "glCopyTextureSubImage2DEXT");
  glCopyTextureSubImage3D = (PFNGLCOPYTEXTURESUBIMAGE3DPROC)loadFunction(
      "glCopyTextureSubImage3D");
  glCopyTextureSubImage3DEXT = (PFNGLCOPYTEXTURESUBIMAGE3DEXTPROC)loadFunction(
      "glCopyTextureSubImage3DEXT");
  glCoverFillPathInstancedNV = (PFNGLCOVERFILLPATHINSTANCEDNVPROC)loadFunction(
      "glCoverFillPathInstancedNV");
  glCoverFillPathNV = (PFNGLCOVERFILLPATHNVPROC)loadFunction("glCoverFillPathNV");
  glCoverStrokePathInstancedNV = (PFNGLCOVERSTROKEPATHINSTANCEDNVPROC)loadFunction(
      "glCoverStrokePathInstancedNV");
  glCoverStrokePathNV = (PFNGLCOVERSTROKEPATHNVPROC)loadFunction("glCoverStrokePathNV");
  glCoverageModulationNV = (PFNGLCOVERAGEMODULATIONNVPROC)loadFunction("glCoverageModulationNV");
  glCoverageModulationTableNV = (PFNGLCOVERAGEMODULATIONTABLENVPROC)loadFunction(
      "glCoverageModulationTableNV");
  glCreateBuffers = (PFNGLCREATEBUFFERSPROC)loadFunction("glCreateBuffers");
  glCreateCommandListsNV = (PFNGLCREATECOMMANDLISTSNVPROC)loadFunction("glCreateCommandListsNV");
  glCreateFramebuffers = (PFNGLCREATEFRAMEBUFFERSPROC)loadFunction("glCreateFramebuffers");
  glCreateMemoryObjectsEXT = (PFNGLCREATEMEMORYOBJECTSEXTPROC)loadFunction(
      "glCreateMemoryObjectsEXT");
  glCreatePerfQueryINTEL = (PFNGLCREATEPERFQUERYINTELPROC)loadFunction("glCreatePerfQueryINTEL");
  glCreateProgram = (PFNGLCREATEPROGRAMPROC)loadFunction("glCreateProgram");
  glCreateProgramObjectARB = (PFNGLCREATEPROGRAMOBJECTARBPROC)loadFunction(
      "glCreateProgramObjectARB");
  glCreateProgramPipelines = (PFNGLCREATEPROGRAMPIPELINESPROC)loadFunction(
      "glCreateProgramPipelines");
  glCreateProgressFenceNVX = (PFNGLCREATEPROGRESSFENCENVXPROC)loadFunction(
      "glCreateProgressFenceNVX");
  glCreateQueries = (PFNGLCREATEQUERIESPROC)loadFunction("glCreateQueries");
  glCreateRenderbuffers = (PFNGLCREATERENDERBUFFERSPROC)loadFunction("glCreateRenderbuffers");
  glCreateSamplers = (PFNGLCREATESAMPLERSPROC)loadFunction("glCreateSamplers");
  glCreateSemaphoresNV = (PFNGLCREATESEMAPHORESNVPROC)loadFunction("glCreateSemaphoresNV");
  glCreateShader = (PFNGLCREATESHADERPROC)loadFunction("glCreateShader");
  glCreateShaderObjectARB = (PFNGLCREATESHADEROBJECTARBPROC)loadFunction(
      "glCreateShaderObjectARB");
  glCreateShaderProgramEXT = (PFNGLCREATESHADERPROGRAMEXTPROC)loadFunction(
      "glCreateShaderProgramEXT");
  glCreateShaderProgramv = (PFNGLCREATESHADERPROGRAMVPROC)loadFunction("glCreateShaderProgramv");
  glCreateShaderProgramvEXT = (PFNGLCREATESHADERPROGRAMVEXTPROC)loadFunction(
      "glCreateShaderProgramvEXT");
  glCreateStatesNV = (PFNGLCREATESTATESNVPROC)loadFunction("glCreateStatesNV");
  glCreateSyncFromCLeventARB = (PFNGLCREATESYNCFROMCLEVENTARBPROC)loadFunction(
      "glCreateSyncFromCLeventARB");
  glCreateTextures = (PFNGLCREATETEXTURESPROC)loadFunction("glCreateTextures");
  glCreateTransformFeedbacks = (PFNGLCREATETRANSFORMFEEDBACKSPROC)loadFunction(
      "glCreateTransformFeedbacks");
  glCreateVertexArrays = (PFNGLCREATEVERTEXARRAYSPROC)loadFunction("glCreateVertexArrays");
  glCullFace = (PFNGLCULLFACEPROC)loadFunction("glCullFace");
  glCullParameterdvEXT = (PFNGLCULLPARAMETERDVEXTPROC)loadFunction("glCullParameterdvEXT");
  glCullParameterfvEXT = (PFNGLCULLPARAMETERFVEXTPROC)loadFunction("glCullParameterfvEXT");
  glCurrentPaletteMatrixARB = (PFNGLCURRENTPALETTEMATRIXARBPROC)loadFunction(
      "glCurrentPaletteMatrixARB");
  glDebugMessageCallback = (PFNGLDEBUGMESSAGECALLBACKPROC)loadFunction("glDebugMessageCallback");
  glDebugMessageCallbackAMD = (PFNGLDEBUGMESSAGECALLBACKAMDPROC)loadFunction(
      "glDebugMessageCallbackAMD");
  glDebugMessageCallbackARB = (PFNGLDEBUGMESSAGECALLBACKARBPROC)loadFunction(
      "glDebugMessageCallbackARB");
  glDebugMessageCallbackKHR = (PFNGLDEBUGMESSAGECALLBACKKHRPROC)loadFunction(
      "glDebugMessageCallbackKHR");
  glDebugMessageControl = (PFNGLDEBUGMESSAGECONTROLPROC)loadFunction("glDebugMessageControl");
  glDebugMessageControlARB = (PFNGLDEBUGMESSAGECONTROLARBPROC)loadFunction(
      "glDebugMessageControlARB");
  glDebugMessageControlKHR = (PFNGLDEBUGMESSAGECONTROLKHRPROC)loadFunction(
      "glDebugMessageControlKHR");
  glDebugMessageEnableAMD = (PFNGLDEBUGMESSAGEENABLEAMDPROC)loadFunction(
      "glDebugMessageEnableAMD");
  glDebugMessageInsert = (PFNGLDEBUGMESSAGEINSERTPROC)loadFunction("glDebugMessageInsert");
  glDebugMessageInsertAMD = (PFNGLDEBUGMESSAGEINSERTAMDPROC)loadFunction(
      "glDebugMessageInsertAMD");
  glDebugMessageInsertARB = (PFNGLDEBUGMESSAGEINSERTARBPROC)loadFunction(
      "glDebugMessageInsertARB");
  glDebugMessageInsertKHR = (PFNGLDEBUGMESSAGEINSERTKHRPROC)loadFunction(
      "glDebugMessageInsertKHR");
  glDeleteBuffers = (PFNGLDELETEBUFFERSPROC)loadFunction("glDeleteBuffers");
  glDeleteBuffersARB = (PFNGLDELETEBUFFERSARBPROC)loadFunction("glDeleteBuffersARB");
  glDeleteCommandListsNV = (PFNGLDELETECOMMANDLISTSNVPROC)loadFunction("glDeleteCommandListsNV");
  glDeleteFencesAPPLE = (PFNGLDELETEFENCESAPPLEPROC)loadFunction("glDeleteFencesAPPLE");
  glDeleteFencesNV = (PFNGLDELETEFENCESNVPROC)loadFunction("glDeleteFencesNV");
  glDeleteFramebuffers = (PFNGLDELETEFRAMEBUFFERSPROC)loadFunction("glDeleteFramebuffers");
  glDeleteFramebuffersEXT = (PFNGLDELETEFRAMEBUFFERSEXTPROC)loadFunction(
      "glDeleteFramebuffersEXT");
  glDeleteLists = (PFNGLDELETELISTSPROC)loadFunction("glDeleteLists");
  glDeleteMemoryObjectsEXT = (PFNGLDELETEMEMORYOBJECTSEXTPROC)loadFunction(
      "glDeleteMemoryObjectsEXT");
  glDeleteNamedStringARB = (PFNGLDELETENAMEDSTRINGARBPROC)loadFunction("glDeleteNamedStringARB");
  glDeleteNamesAMD = (PFNGLDELETENAMESAMDPROC)loadFunction("glDeleteNamesAMD");
  glDeleteObjectARB = (PFNGLDELETEOBJECTARBPROC)loadFunction("glDeleteObjectARB");
  glDeleteOcclusionQueriesNV = (PFNGLDELETEOCCLUSIONQUERIESNVPROC)loadFunction(
      "glDeleteOcclusionQueriesNV");
  glDeletePathsNV = (PFNGLDELETEPATHSNVPROC)loadFunction("glDeletePathsNV");
  glDeletePerfMonitorsAMD = (PFNGLDELETEPERFMONITORSAMDPROC)loadFunction(
      "glDeletePerfMonitorsAMD");
  glDeletePerfQueryINTEL = (PFNGLDELETEPERFQUERYINTELPROC)loadFunction("glDeletePerfQueryINTEL");
  glDeleteProgram = (PFNGLDELETEPROGRAMPROC)loadFunction("glDeleteProgram");
  glDeleteProgramPipelines = (PFNGLDELETEPROGRAMPIPELINESPROC)loadFunction(
      "glDeleteProgramPipelines");
  glDeleteProgramPipelinesEXT = (PFNGLDELETEPROGRAMPIPELINESEXTPROC)loadFunction(
      "glDeleteProgramPipelinesEXT");
  glDeleteProgramsARB = (PFNGLDELETEPROGRAMSARBPROC)loadFunction("glDeleteProgramsARB");
  glDeleteProgramsNV = (PFNGLDELETEPROGRAMSNVPROC)loadFunction("glDeleteProgramsNV");
  glDeleteQueries = (PFNGLDELETEQUERIESPROC)loadFunction("glDeleteQueries");
  glDeleteQueriesARB = (PFNGLDELETEQUERIESARBPROC)loadFunction("glDeleteQueriesARB");
  glDeleteQueryResourceTagNV = (PFNGLDELETEQUERYRESOURCETAGNVPROC)loadFunction(
      "glDeleteQueryResourceTagNV");
  glDeleteRenderbuffers = (PFNGLDELETERENDERBUFFERSPROC)loadFunction("glDeleteRenderbuffers");
  glDeleteRenderbuffersEXT = (PFNGLDELETERENDERBUFFERSEXTPROC)loadFunction(
      "glDeleteRenderbuffersEXT");
  glDeleteSamplers = (PFNGLDELETESAMPLERSPROC)loadFunction("glDeleteSamplers");
  glDeleteSemaphoresEXT = (PFNGLDELETESEMAPHORESEXTPROC)loadFunction("glDeleteSemaphoresEXT");
  glDeleteShader = (PFNGLDELETESHADERPROC)loadFunction("glDeleteShader");
  glDeleteStatesNV = (PFNGLDELETESTATESNVPROC)loadFunction("glDeleteStatesNV");
  glDeleteSync = (PFNGLDELETESYNCPROC)loadFunction("glDeleteSync");
  glDeleteTextures = (PFNGLDELETETEXTURESPROC)loadFunction("glDeleteTextures");
  glDeleteTexturesEXT = (PFNGLDELETETEXTURESEXTPROC)loadFunction("glDeleteTexturesEXT");
  glDeleteTransformFeedbacks = (PFNGLDELETETRANSFORMFEEDBACKSPROC)loadFunction(
      "glDeleteTransformFeedbacks");
  glDeleteTransformFeedbacksNV = (PFNGLDELETETRANSFORMFEEDBACKSNVPROC)loadFunction(
      "glDeleteTransformFeedbacksNV");
  glDeleteVertexArrays = (PFNGLDELETEVERTEXARRAYSPROC)loadFunction("glDeleteVertexArrays");
  glDeleteVertexArraysAPPLE = (PFNGLDELETEVERTEXARRAYSAPPLEPROC)loadFunction(
      "glDeleteVertexArraysAPPLE");
  glDeleteVertexShaderEXT = (PFNGLDELETEVERTEXSHADEREXTPROC)loadFunction(
      "glDeleteVertexShaderEXT");
  glDepthBoundsEXT = (PFNGLDEPTHBOUNDSEXTPROC)loadFunction("glDepthBoundsEXT");
  glDepthBoundsdNV = (PFNGLDEPTHBOUNDSDNVPROC)loadFunction("glDepthBoundsdNV");
  glDepthFunc = (PFNGLDEPTHFUNCPROC)loadFunction("glDepthFunc");
  glDepthMask = (PFNGLDEPTHMASKPROC)loadFunction("glDepthMask");
  glDepthRange = (PFNGLDEPTHRANGEPROC)loadFunction("glDepthRange");
  glDepthRangeArraydvNV = (PFNGLDEPTHRANGEARRAYDVNVPROC)loadFunction("glDepthRangeArraydvNV");
  glDepthRangeArrayv = (PFNGLDEPTHRANGEARRAYVPROC)loadFunction("glDepthRangeArrayv");
  glDepthRangeIndexed = (PFNGLDEPTHRANGEINDEXEDPROC)loadFunction("glDepthRangeIndexed");
  glDepthRangeIndexeddNV = (PFNGLDEPTHRANGEINDEXEDDNVPROC)loadFunction("glDepthRangeIndexeddNV");
  glDepthRangedNV = (PFNGLDEPTHRANGEDNVPROC)loadFunction("glDepthRangedNV");
  glDepthRangef = (PFNGLDEPTHRANGEFPROC)loadFunction("glDepthRangef");
  glDetachObjectARB = (PFNGLDETACHOBJECTARBPROC)loadFunction("glDetachObjectARB");
  glDetachShader = (PFNGLDETACHSHADERPROC)loadFunction("glDetachShader");
  glDisable = (PFNGLDISABLEPROC)loadFunction("glDisable");
  glDisableClientState = (PFNGLDISABLECLIENTSTATEPROC)loadFunction("glDisableClientState");
  glDisableClientStateIndexedEXT = (PFNGLDISABLECLIENTSTATEINDEXEDEXTPROC)loadFunction(
      "glDisableClientStateIndexedEXT");
  glDisableClientStateiEXT = (PFNGLDISABLECLIENTSTATEIEXTPROC)loadFunction(
      "glDisableClientStateiEXT");
  glDisableIndexedEXT = (PFNGLDISABLEINDEXEDEXTPROC)loadFunction("glDisableIndexedEXT");
  glDisableVariantClientStateEXT = (PFNGLDISABLEVARIANTCLIENTSTATEEXTPROC)loadFunction(
      "glDisableVariantClientStateEXT");
  glDisableVertexArrayAttrib = (PFNGLDISABLEVERTEXARRAYATTRIBPROC)loadFunction(
      "glDisableVertexArrayAttrib");
  glDisableVertexArrayAttribEXT = (PFNGLDISABLEVERTEXARRAYATTRIBEXTPROC)loadFunction(
      "glDisableVertexArrayAttribEXT");
  glDisableVertexArrayEXT = (PFNGLDISABLEVERTEXARRAYEXTPROC)loadFunction(
      "glDisableVertexArrayEXT");
  glDisableVertexAttribAPPLE = (PFNGLDISABLEVERTEXATTRIBAPPLEPROC)loadFunction(
      "glDisableVertexAttribAPPLE");
  glDisableVertexAttribArray = (PFNGLDISABLEVERTEXATTRIBARRAYPROC)loadFunction(
      "glDisableVertexAttribArray");
  glDisableVertexAttribArrayARB = (PFNGLDISABLEVERTEXATTRIBARRAYARBPROC)loadFunction(
      "glDisableVertexAttribArrayARB");
  glDisablei = (PFNGLDISABLEIPROC)loadFunction("glDisablei");
  glDispatchCompute = (PFNGLDISPATCHCOMPUTEPROC)loadFunction("glDispatchCompute");
  glDispatchComputeGroupSizeARB = (PFNGLDISPATCHCOMPUTEGROUPSIZEARBPROC)loadFunction(
      "glDispatchComputeGroupSizeARB");
  glDispatchComputeIndirect = (PFNGLDISPATCHCOMPUTEINDIRECTPROC)loadFunction(
      "glDispatchComputeIndirect");
  glDrawArrays = (PFNGLDRAWARRAYSPROC)loadFunction("glDrawArrays");
  glDrawArraysEXT = (PFNGLDRAWARRAYSEXTPROC)loadFunction("glDrawArraysEXT");
  glDrawArraysIndirect = (PFNGLDRAWARRAYSINDIRECTPROC)loadFunction("glDrawArraysIndirect");
  glDrawArraysInstanced = (PFNGLDRAWARRAYSINSTANCEDPROC)loadFunction("glDrawArraysInstanced");
  glDrawArraysInstancedARB = (PFNGLDRAWARRAYSINSTANCEDARBPROC)loadFunction(
      "glDrawArraysInstancedARB");
  glDrawArraysInstancedBaseInstance = (PFNGLDRAWARRAYSINSTANCEDBASEINSTANCEPROC)loadFunction(
      "glDrawArraysInstancedBaseInstance");
  glDrawArraysInstancedEXT = (PFNGLDRAWARRAYSINSTANCEDEXTPROC)loadFunction(
      "glDrawArraysInstancedEXT");
  glDrawBuffer = (PFNGLDRAWBUFFERPROC)loadFunction("glDrawBuffer");
  glDrawBuffers = (PFNGLDRAWBUFFERSPROC)loadFunction("glDrawBuffers");
  glDrawBuffersARB = (PFNGLDRAWBUFFERSARBPROC)loadFunction("glDrawBuffersARB");
  glDrawCommandsAddressNV = (PFNGLDRAWCOMMANDSADDRESSNVPROC)loadFunction(
      "glDrawCommandsAddressNV");
  glDrawCommandsNV = (PFNGLDRAWCOMMANDSNVPROC)loadFunction("glDrawCommandsNV");
  glDrawCommandsStatesAddressNV = (PFNGLDRAWCOMMANDSSTATESADDRESSNVPROC)loadFunction(
      "glDrawCommandsStatesAddressNV");
  glDrawCommandsStatesNV = (PFNGLDRAWCOMMANDSSTATESNVPROC)loadFunction("glDrawCommandsStatesNV");
  glDrawElementArrayAPPLE = (PFNGLDRAWELEMENTARRAYAPPLEPROC)loadFunction(
      "glDrawElementArrayAPPLE");
  glDrawElements = (PFNGLDRAWELEMENTSPROC)loadFunction("glDrawElements");
  glDrawElementsBaseVertex = (PFNGLDRAWELEMENTSBASEVERTEXPROC)loadFunction(
      "glDrawElementsBaseVertex");
  glDrawElementsIndirect = (PFNGLDRAWELEMENTSINDIRECTPROC)loadFunction("glDrawElementsIndirect");
  glDrawElementsInstanced = (PFNGLDRAWELEMENTSINSTANCEDPROC)loadFunction(
      "glDrawElementsInstanced");
  glDrawElementsInstancedARB = (PFNGLDRAWELEMENTSINSTANCEDARBPROC)loadFunction(
      "glDrawElementsInstancedARB");
  glDrawElementsInstancedBaseInstance = (PFNGLDRAWELEMENTSINSTANCEDBASEINSTANCEPROC)loadFunction(
      "glDrawElementsInstancedBaseInstance");
  glDrawElementsInstancedBaseVertex = (PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXPROC)loadFunction(
      "glDrawElementsInstancedBaseVertex");
  glDrawElementsInstancedBaseVertexBaseInstance =
      (PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXBASEINSTANCEPROC)loadFunction(
          "glDrawElementsInstancedBaseVertexBaseInstance");
  glDrawElementsInstancedEXT = (PFNGLDRAWELEMENTSINSTANCEDEXTPROC)loadFunction(
      "glDrawElementsInstancedEXT");
  glDrawMeshTasksNV = (PFNGLDRAWMESHTASKSNVPROC)loadFunction("glDrawMeshTasksNV");
  glDrawMeshTasksIndirectNV = (PFNGLDRAWMESHTASKSINDIRECTNVPROC)loadFunction(
      "glDrawMeshTasksIndirectNV");
  glDrawPixels = (PFNGLDRAWPIXELSPROC)loadFunction("glDrawPixels");
  glDrawRangeElementArrayAPPLE = (PFNGLDRAWRANGEELEMENTARRAYAPPLEPROC)loadFunction(
      "glDrawRangeElementArrayAPPLE");
  glDrawRangeElements = (PFNGLDRAWRANGEELEMENTSPROC)loadFunction("glDrawRangeElements");
  glDrawRangeElementsBaseVertex = (PFNGLDRAWRANGEELEMENTSBASEVERTEXPROC)loadFunction(
      "glDrawRangeElementsBaseVertex");
  glDrawRangeElementsEXT = (PFNGLDRAWRANGEELEMENTSEXTPROC)loadFunction("glDrawRangeElementsEXT");
  glDrawTextureNV = (PFNGLDRAWTEXTURENVPROC)loadFunction("glDrawTextureNV");
  glDrawTransformFeedback = (PFNGLDRAWTRANSFORMFEEDBACKPROC)loadFunction(
      "glDrawTransformFeedback");
  glDrawTransformFeedbackInstanced = (PFNGLDRAWTRANSFORMFEEDBACKINSTANCEDPROC)loadFunction(
      "glDrawTransformFeedbackInstanced");
  glDrawTransformFeedbackNV = (PFNGLDRAWTRANSFORMFEEDBACKNVPROC)loadFunction(
      "glDrawTransformFeedbackNV");
  glDrawTransformFeedbackStream = (PFNGLDRAWTRANSFORMFEEDBACKSTREAMPROC)loadFunction(
      "glDrawTransformFeedbackStream");
  glDrawTransformFeedbackStreamInstanced = (PFNGLDRAWTRANSFORMFEEDBACKSTREAMINSTANCEDPROC)
      loadFunction("glDrawTransformFeedbackStreamInstanced");
  glEGLImageTargetTexStorageEXT = (PFNGLEGLIMAGETARGETTEXSTORAGEEXTPROC)loadFunction(
      "glEGLImageTargetTexStorageEXT");
  glEGLImageTargetTextureStorageEXT = (PFNGLEGLIMAGETARGETTEXTURESTORAGEEXTPROC)loadFunction(
      "glEGLImageTargetTextureStorageEXT");
  glEdgeFlag = (PFNGLEDGEFLAGPROC)loadFunction("glEdgeFlag");
  glEdgeFlagFormatNV = (PFNGLEDGEFLAGFORMATNVPROC)loadFunction("glEdgeFlagFormatNV");
  glEdgeFlagPointer = (PFNGLEDGEFLAGPOINTERPROC)loadFunction("glEdgeFlagPointer");
  glEdgeFlagPointerEXT = (PFNGLEDGEFLAGPOINTEREXTPROC)loadFunction("glEdgeFlagPointerEXT");
  glEdgeFlagv = (PFNGLEDGEFLAGVPROC)loadFunction("glEdgeFlagv");
  glElementPointerAPPLE = (PFNGLELEMENTPOINTERAPPLEPROC)loadFunction("glElementPointerAPPLE");
  glEnable = (PFNGLENABLEPROC)loadFunction("glEnable");
  glEnableClientState = (PFNGLENABLECLIENTSTATEPROC)loadFunction("glEnableClientState");
  glEnableClientStateIndexedEXT = (PFNGLENABLECLIENTSTATEINDEXEDEXTPROC)loadFunction(
      "glEnableClientStateIndexedEXT");
  glEnableClientStateiEXT = (PFNGLENABLECLIENTSTATEIEXTPROC)loadFunction(
      "glEnableClientStateiEXT");
  glEnableIndexedEXT = (PFNGLENABLEINDEXEDEXTPROC)loadFunction("glEnableIndexedEXT");
  glEnableVariantClientStateEXT = (PFNGLENABLEVARIANTCLIENTSTATEEXTPROC)loadFunction(
      "glEnableVariantClientStateEXT");
  glEnableVertexArrayAttrib = (PFNGLENABLEVERTEXARRAYATTRIBPROC)loadFunction(
      "glEnableVertexArrayAttrib");
  glEnableVertexArrayAttribEXT = (PFNGLENABLEVERTEXARRAYATTRIBEXTPROC)loadFunction(
      "glEnableVertexArrayAttribEXT");
  glEnableVertexArrayEXT = (PFNGLENABLEVERTEXARRAYEXTPROC)loadFunction("glEnableVertexArrayEXT");
  glEnableVertexAttribAPPLE = (PFNGLENABLEVERTEXATTRIBAPPLEPROC)loadFunction(
      "glEnableVertexAttribAPPLE");
  glEnableVertexAttribArray = (PFNGLENABLEVERTEXATTRIBARRAYPROC)loadFunction(
      "glEnableVertexAttribArray");
  glEnableVertexAttribArrayARB = (PFNGLENABLEVERTEXATTRIBARRAYARBPROC)loadFunction(
      "glEnableVertexAttribArrayARB");
  glEnablei = (PFNGLENABLEIPROC)loadFunction("glEnablei");
  glEnd = (PFNGLENDPROC)loadFunction("glEnd");
  glEndConditionalRender = (PFNGLENDCONDITIONALRENDERPROC)loadFunction("glEndConditionalRender");
  glEndConditionalRenderNV = (PFNGLENDCONDITIONALRENDERNVPROC)loadFunction(
      "glEndConditionalRenderNV");
  glEndConditionalRenderNVX = (PFNGLENDCONDITIONALRENDERNVXPROC)loadFunction(
      "glEndConditionalRenderNVX");
  glEndList = (PFNGLENDLISTPROC)loadFunction("glEndList");
  glEndOcclusionQueryNV = (PFNGLENDOCCLUSIONQUERYNVPROC)loadFunction("glEndOcclusionQueryNV");
  glEndPerfMonitorAMD = (PFNGLENDPERFMONITORAMDPROC)loadFunction("glEndPerfMonitorAMD");
  glEndPerfQueryINTEL = (PFNGLENDPERFQUERYINTELPROC)loadFunction("glEndPerfQueryINTEL");
  glEndQuery = (PFNGLENDQUERYPROC)loadFunction("glEndQuery");
  glEndQueryARB = (PFNGLENDQUERYARBPROC)loadFunction("glEndQueryARB");
  glEndQueryIndexed = (PFNGLENDQUERYINDEXEDPROC)loadFunction("glEndQueryIndexed");
  glEndTransformFeedback = (PFNGLENDTRANSFORMFEEDBACKPROC)loadFunction("glEndTransformFeedback");
  glEndTransformFeedbackEXT = (PFNGLENDTRANSFORMFEEDBACKEXTPROC)loadFunction(
      "glEndTransformFeedbackEXT");
  glEndTransformFeedbackNV = (PFNGLENDTRANSFORMFEEDBACKNVPROC)loadFunction(
      "glEndTransformFeedbackNV");
  glEndVertexShaderEXT = (PFNGLENDVERTEXSHADEREXTPROC)loadFunction("glEndVertexShaderEXT");
  glEndVideoCaptureNV = (PFNGLENDVIDEOCAPTURENVPROC)loadFunction("glEndVideoCaptureNV");
  glEvalCoord1d = (PFNGLEVALCOORD1DPROC)loadFunction("glEvalCoord1d");
  glEvalCoord1dv = (PFNGLEVALCOORD1DVPROC)loadFunction("glEvalCoord1dv");
  glEvalCoord1f = (PFNGLEVALCOORD1FPROC)loadFunction("glEvalCoord1f");
  glEvalCoord1fv = (PFNGLEVALCOORD1FVPROC)loadFunction("glEvalCoord1fv");
  glEvalCoord2d = (PFNGLEVALCOORD2DPROC)loadFunction("glEvalCoord2d");
  glEvalCoord2dv = (PFNGLEVALCOORD2DVPROC)loadFunction("glEvalCoord2dv");
  glEvalCoord2f = (PFNGLEVALCOORD2FPROC)loadFunction("glEvalCoord2f");
  glEvalCoord2fv = (PFNGLEVALCOORD2FVPROC)loadFunction("glEvalCoord2fv");
  glEvalMapsNV = (PFNGLEVALMAPSNVPROC)loadFunction("glEvalMapsNV");
  glEvalMesh1 = (PFNGLEVALMESH1PROC)loadFunction("glEvalMesh1");
  glEvalMesh2 = (PFNGLEVALMESH2PROC)loadFunction("glEvalMesh2");
  glEvalPoint1 = (PFNGLEVALPOINT1PROC)loadFunction("glEvalPoint1");
  glEvalPoint2 = (PFNGLEVALPOINT2PROC)loadFunction("glEvalPoint2");
  glEvaluateDepthValuesARB = (PFNGLEVALUATEDEPTHVALUESARBPROC)loadFunction(
      "glEvaluateDepthValuesARB");
  glExecuteProgramNV = (PFNGLEXECUTEPROGRAMNVPROC)loadFunction("glExecuteProgramNV");
  glExtractComponentEXT = (PFNGLEXTRACTCOMPONENTEXTPROC)loadFunction("glExtractComponentEXT");
  glFeedbackBuffer = (PFNGLFEEDBACKBUFFERPROC)loadFunction("glFeedbackBuffer");
  glFenceSync = (PFNGLFENCESYNCPROC)loadFunction("glFenceSync");
  glFinalCombinerInputNV = (PFNGLFINALCOMBINERINPUTNVPROC)loadFunction("glFinalCombinerInputNV");
  glFinish = (PFNGLFINISHPROC)loadFunction("glFinish");
  glFinishFenceAPPLE = (PFNGLFINISHFENCEAPPLEPROC)loadFunction("glFinishFenceAPPLE");
  glFinishFenceNV = (PFNGLFINISHFENCENVPROC)loadFunction("glFinishFenceNV");
  glFinishObjectAPPLE = (PFNGLFINISHOBJECTAPPLEPROC)loadFunction("glFinishObjectAPPLE");
  glFlush = (PFNGLFLUSHPROC)loadFunction("glFlush");
  glFlushMappedBufferRange = (PFNGLFLUSHMAPPEDBUFFERRANGEPROC)loadFunction(
      "glFlushMappedBufferRange");
  glFlushMappedBufferRangeAPPLE = (PFNGLFLUSHMAPPEDBUFFERRANGEAPPLEPROC)loadFunction(
      "glFlushMappedBufferRangeAPPLE");
  glFlushMappedNamedBufferRange = (PFNGLFLUSHMAPPEDNAMEDBUFFERRANGEPROC)loadFunction(
      "glFlushMappedNamedBufferRange");
  glFlushMappedNamedBufferRangeEXT = (PFNGLFLUSHMAPPEDNAMEDBUFFERRANGEEXTPROC)loadFunction(
      "glFlushMappedNamedBufferRangeEXT");
  glFlushPixelDataRangeNV = (PFNGLFLUSHPIXELDATARANGENVPROC)loadFunction(
      "glFlushPixelDataRangeNV");
  glFlushVertexArrayRangeAPPLE = (PFNGLFLUSHVERTEXARRAYRANGEAPPLEPROC)loadFunction(
      "glFlushVertexArrayRangeAPPLE");
  glFlushVertexArrayRangeNV = (PFNGLFLUSHVERTEXARRAYRANGENVPROC)loadFunction(
      "glFlushVertexArrayRangeNV");
  glFogCoordFormatNV = (PFNGLFOGCOORDFORMATNVPROC)loadFunction("glFogCoordFormatNV");
  glFogCoordPointer = (PFNGLFOGCOORDPOINTERPROC)loadFunction("glFogCoordPointer");
  glFogCoordPointerEXT = (PFNGLFOGCOORDPOINTEREXTPROC)loadFunction("glFogCoordPointerEXT");
  glFogCoordd = (PFNGLFOGCOORDDPROC)loadFunction("glFogCoordd");
  glFogCoorddEXT = (PFNGLFOGCOORDDEXTPROC)loadFunction("glFogCoorddEXT");
  glFogCoorddv = (PFNGLFOGCOORDDVPROC)loadFunction("glFogCoorddv");
  glFogCoorddvEXT = (PFNGLFOGCOORDDVEXTPROC)loadFunction("glFogCoorddvEXT");
  glFogCoordf = (PFNGLFOGCOORDFPROC)loadFunction("glFogCoordf");
  glFogCoordfEXT = (PFNGLFOGCOORDFEXTPROC)loadFunction("glFogCoordfEXT");
  glFogCoordfv = (PFNGLFOGCOORDFVPROC)loadFunction("glFogCoordfv");
  glFogCoordfvEXT = (PFNGLFOGCOORDFVEXTPROC)loadFunction("glFogCoordfvEXT");
  glFogCoordhNV = (PFNGLFOGCOORDHNVPROC)loadFunction("glFogCoordhNV");
  glFogCoordhvNV = (PFNGLFOGCOORDHVNVPROC)loadFunction("glFogCoordhvNV");
  glFogf = (PFNGLFOGFPROC)loadFunction("glFogf");
  glFogfv = (PFNGLFOGFVPROC)loadFunction("glFogfv");
  glFogi = (PFNGLFOGIPROC)loadFunction("glFogi");
  glFogiv = (PFNGLFOGIVPROC)loadFunction("glFogiv");
  glFragmentCoverageColorNV = (PFNGLFRAGMENTCOVERAGECOLORNVPROC)loadFunction(
      "glFragmentCoverageColorNV");
  glFramebufferDrawBufferEXT = (PFNGLFRAMEBUFFERDRAWBUFFEREXTPROC)loadFunction(
      "glFramebufferDrawBufferEXT");
  glFramebufferDrawBuffersEXT = (PFNGLFRAMEBUFFERDRAWBUFFERSEXTPROC)loadFunction(
      "glFramebufferDrawBuffersEXT");
  glFramebufferFetchBarrierEXT = (PFNGLFRAMEBUFFERFETCHBARRIEREXTPROC)loadFunction(
      "glFramebufferFetchBarrierEXT");
  glFramebufferParameteri = (PFNGLFRAMEBUFFERPARAMETERIPROC)loadFunction(
      "glFramebufferParameteri");
  glFramebufferReadBufferEXT = (PFNGLFRAMEBUFFERREADBUFFEREXTPROC)loadFunction(
      "glFramebufferReadBufferEXT");
  glFramebufferRenderbuffer = (PFNGLFRAMEBUFFERRENDERBUFFERPROC)loadFunction(
      "glFramebufferRenderbuffer");
  glFramebufferRenderbufferEXT = (PFNGLFRAMEBUFFERRENDERBUFFEREXTPROC)loadFunction(
      "glFramebufferRenderbufferEXT");
  glFramebufferSampleLocationsfvARB = (PFNGLFRAMEBUFFERSAMPLELOCATIONSFVARBPROC)loadFunction(
      "glFramebufferSampleLocationsfvARB");
  glFramebufferSampleLocationsfvNV = (PFNGLFRAMEBUFFERSAMPLELOCATIONSFVNVPROC)loadFunction(
      "glFramebufferSampleLocationsfvNV");
  glFramebufferSamplePositionsfvAMD = (PFNGLFRAMEBUFFERSAMPLEPOSITIONSFVAMDPROC)loadFunction(
      "glFramebufferSamplePositionsfvAMD");
  glFramebufferTexture = (PFNGLFRAMEBUFFERTEXTUREPROC)loadFunction("glFramebufferTexture");
  glFramebufferTexture1D = (PFNGLFRAMEBUFFERTEXTURE1DPROC)loadFunction("glFramebufferTexture1D");
  glFramebufferTexture1DEXT = (PFNGLFRAMEBUFFERTEXTURE1DEXTPROC)loadFunction(
      "glFramebufferTexture1DEXT");
  glFramebufferTexture2D = (PFNGLFRAMEBUFFERTEXTURE2DPROC)loadFunction("glFramebufferTexture2D");
  glFramebufferTexture2DEXT = (PFNGLFRAMEBUFFERTEXTURE2DEXTPROC)loadFunction(
      "glFramebufferTexture2DEXT");
  glFramebufferTexture3D = (PFNGLFRAMEBUFFERTEXTURE3DPROC)loadFunction("glFramebufferTexture3D");
  glFramebufferTexture3DEXT = (PFNGLFRAMEBUFFERTEXTURE3DEXTPROC)loadFunction(
      "glFramebufferTexture3DEXT");
  glFramebufferTextureARB = (PFNGLFRAMEBUFFERTEXTUREARBPROC)loadFunction(
      "glFramebufferTextureARB");
  glFramebufferTextureEXT = (PFNGLFRAMEBUFFERTEXTUREEXTPROC)loadFunction(
      "glFramebufferTextureEXT");
  glFramebufferTextureFaceARB = (PFNGLFRAMEBUFFERTEXTUREFACEARBPROC)loadFunction(
      "glFramebufferTextureFaceARB");
  glFramebufferTextureFaceEXT = (PFNGLFRAMEBUFFERTEXTUREFACEEXTPROC)loadFunction(
      "glFramebufferTextureFaceEXT");
  glFramebufferTextureLayer = (PFNGLFRAMEBUFFERTEXTURELAYERPROC)loadFunction(
      "glFramebufferTextureLayer");
  glFramebufferTextureLayerARB = (PFNGLFRAMEBUFFERTEXTURELAYERARBPROC)loadFunction(
      "glFramebufferTextureLayerARB");
  glFramebufferTextureLayerEXT = (PFNGLFRAMEBUFFERTEXTURELAYEREXTPROC)loadFunction(
      "glFramebufferTextureLayerEXT");
  glFrontFace = (PFNGLFRONTFACEPROC)loadFunction("glFrontFace");
  glFrustum = (PFNGLFRUSTUMPROC)loadFunction("glFrustum");
  glGenBuffers = (PFNGLGENBUFFERSPROC)loadFunction("glGenBuffers");
  glGenBuffersARB = (PFNGLGENBUFFERSARBPROC)loadFunction("glGenBuffersARB");
  glGenFencesAPPLE = (PFNGLGENFENCESAPPLEPROC)loadFunction("glGenFencesAPPLE");
  glGenFencesNV = (PFNGLGENFENCESNVPROC)loadFunction("glGenFencesNV");
  glGenFramebuffers = (PFNGLGENFRAMEBUFFERSPROC)loadFunction("glGenFramebuffers");
  glGenFramebuffersEXT = (PFNGLGENFRAMEBUFFERSEXTPROC)loadFunction("glGenFramebuffersEXT");
  glGenLists = (PFNGLGENLISTSPROC)loadFunction("glGenLists");
  glGenNamesAMD = (PFNGLGENNAMESAMDPROC)loadFunction("glGenNamesAMD");
  glGenOcclusionQueriesNV = (PFNGLGENOCCLUSIONQUERIESNVPROC)loadFunction(
      "glGenOcclusionQueriesNV");
  glGenPathsNV = (PFNGLGENPATHSNVPROC)loadFunction("glGenPathsNV");
  glGenPerfMonitorsAMD = (PFNGLGENPERFMONITORSAMDPROC)loadFunction("glGenPerfMonitorsAMD");
  glGenProgramPipelines = (PFNGLGENPROGRAMPIPELINESPROC)loadFunction("glGenProgramPipelines");
  glGenProgramPipelinesEXT = (PFNGLGENPROGRAMPIPELINESEXTPROC)loadFunction(
      "glGenProgramPipelinesEXT");
  glGenProgramsARB = (PFNGLGENPROGRAMSARBPROC)loadFunction("glGenProgramsARB");
  glGenProgramsNV = (PFNGLGENPROGRAMSNVPROC)loadFunction("glGenProgramsNV");
  glGenQueries = (PFNGLGENQUERIESPROC)loadFunction("glGenQueries");
  glGenQueriesARB = (PFNGLGENQUERIESARBPROC)loadFunction("glGenQueriesARB");
  glGenQueryResourceTagNV = (PFNGLGENQUERYRESOURCETAGNVPROC)loadFunction(
      "glGenQueryResourceTagNV");
  glGenRenderbuffers = (PFNGLGENRENDERBUFFERSPROC)loadFunction("glGenRenderbuffers");
  glGenRenderbuffersEXT = (PFNGLGENRENDERBUFFERSEXTPROC)loadFunction("glGenRenderbuffersEXT");
  glGenSamplers = (PFNGLGENSAMPLERSPROC)loadFunction("glGenSamplers");
  glGenSemaphoresEXT = (PFNGLGENSEMAPHORESEXTPROC)loadFunction("glGenSemaphoresEXT");
  glGenSymbolsEXT = (PFNGLGENSYMBOLSEXTPROC)loadFunction("glGenSymbolsEXT");
  glGenTextures = (PFNGLGENTEXTURESPROC)loadFunction("glGenTextures");
  glGenTexturesEXT = (PFNGLGENTEXTURESEXTPROC)loadFunction("glGenTexturesEXT");
  glGenTransformFeedbacks = (PFNGLGENTRANSFORMFEEDBACKSPROC)loadFunction(
      "glGenTransformFeedbacks");
  glGenTransformFeedbacksNV = (PFNGLGENTRANSFORMFEEDBACKSNVPROC)loadFunction(
      "glGenTransformFeedbacksNV");
  glGenVertexArrays = (PFNGLGENVERTEXARRAYSPROC)loadFunction("glGenVertexArrays");
  glGenVertexArraysAPPLE = (PFNGLGENVERTEXARRAYSAPPLEPROC)loadFunction("glGenVertexArraysAPPLE");
  glGenVertexShadersEXT = (PFNGLGENVERTEXSHADERSEXTPROC)loadFunction("glGenVertexShadersEXT");
  glGenerateMipmap = (PFNGLGENERATEMIPMAPPROC)loadFunction("glGenerateMipmap");
  glGenerateMipmapEXT = (PFNGLGENERATEMIPMAPEXTPROC)loadFunction("glGenerateMipmapEXT");
  glGenerateMultiTexMipmapEXT = (PFNGLGENERATEMULTITEXMIPMAPEXTPROC)loadFunction(
      "glGenerateMultiTexMipmapEXT");
  glGenerateTextureMipmap = (PFNGLGENERATETEXTUREMIPMAPPROC)loadFunction(
      "glGenerateTextureMipmap");
  glGenerateTextureMipmapEXT = (PFNGLGENERATETEXTUREMIPMAPEXTPROC)loadFunction(
      "glGenerateTextureMipmapEXT");
  glGetActiveAtomicCounterBufferiv = (PFNGLGETACTIVEATOMICCOUNTERBUFFERIVPROC)loadFunction(
      "glGetActiveAtomicCounterBufferiv");
  glGetActiveAttrib = (PFNGLGETACTIVEATTRIBPROC)loadFunction("glGetActiveAttrib");
  glGetActiveAttribARB = (PFNGLGETACTIVEATTRIBARBPROC)loadFunction("glGetActiveAttribARB");
  glGetActiveSubroutineName = (PFNGLGETACTIVESUBROUTINENAMEPROC)loadFunction(
      "glGetActiveSubroutineName");
  glGetActiveSubroutineUniformName = (PFNGLGETACTIVESUBROUTINEUNIFORMNAMEPROC)loadFunction(
      "glGetActiveSubroutineUniformName");
  glGetActiveSubroutineUniformiv = (PFNGLGETACTIVESUBROUTINEUNIFORMIVPROC)loadFunction(
      "glGetActiveSubroutineUniformiv");
  glGetActiveUniform = (PFNGLGETACTIVEUNIFORMPROC)loadFunction("glGetActiveUniform");
  glGetActiveUniformARB = (PFNGLGETACTIVEUNIFORMARBPROC)loadFunction("glGetActiveUniformARB");
  glGetActiveUniformBlockName = (PFNGLGETACTIVEUNIFORMBLOCKNAMEPROC)loadFunction(
      "glGetActiveUniformBlockName");
  glGetActiveUniformBlockiv = (PFNGLGETACTIVEUNIFORMBLOCKIVPROC)loadFunction(
      "glGetActiveUniformBlockiv");
  glGetActiveUniformName = (PFNGLGETACTIVEUNIFORMNAMEPROC)loadFunction("glGetActiveUniformName");
  glGetActiveUniformsiv = (PFNGLGETACTIVEUNIFORMSIVPROC)loadFunction("glGetActiveUniformsiv");
  glGetActiveVaryingNV = (PFNGLGETACTIVEVARYINGNVPROC)loadFunction("glGetActiveVaryingNV");
  glGetAttachedObjectsARB = (PFNGLGETATTACHEDOBJECTSARBPROC)loadFunction(
      "glGetAttachedObjectsARB");
  glGetAttachedShaders = (PFNGLGETATTACHEDSHADERSPROC)loadFunction("glGetAttachedShaders");
  glGetAttribLocation = (PFNGLGETATTRIBLOCATIONPROC)loadFunction("glGetAttribLocation");
  glGetAttribLocationARB = (PFNGLGETATTRIBLOCATIONARBPROC)loadFunction("glGetAttribLocationARB");
  glGetBooleanIndexedvEXT = (PFNGLGETBOOLEANINDEXEDVEXTPROC)loadFunction(
      "glGetBooleanIndexedvEXT");
  glGetBooleani_v = (PFNGLGETBOOLEANI_VPROC)loadFunction("glGetBooleani_v");
  glGetBooleanv = (PFNGLGETBOOLEANVPROC)loadFunction("glGetBooleanv");
  glGetBufferParameteri64v = (PFNGLGETBUFFERPARAMETERI64VPROC)loadFunction(
      "glGetBufferParameteri64v");
  glGetBufferParameteriv = (PFNGLGETBUFFERPARAMETERIVPROC)loadFunction("glGetBufferParameteriv");
  glGetBufferParameterivARB = (PFNGLGETBUFFERPARAMETERIVARBPROC)loadFunction(
      "glGetBufferParameterivARB");
  glGetBufferParameterui64vNV = (PFNGLGETBUFFERPARAMETERUI64VNVPROC)loadFunction(
      "glGetBufferParameterui64vNV");
  glGetBufferPointerv = (PFNGLGETBUFFERPOINTERVPROC)loadFunction("glGetBufferPointerv");
  glGetBufferPointervARB = (PFNGLGETBUFFERPOINTERVARBPROC)loadFunction("glGetBufferPointervARB");
  glGetBufferSubData = (PFNGLGETBUFFERSUBDATAPROC)loadFunction("glGetBufferSubData");
  glGetBufferSubDataARB = (PFNGLGETBUFFERSUBDATAARBPROC)loadFunction("glGetBufferSubDataARB");
  glGetClipPlane = (PFNGLGETCLIPPLANEPROC)loadFunction("glGetClipPlane");
  glGetColorTable = (PFNGLGETCOLORTABLEPROC)loadFunction("glGetColorTable");
  glGetColorTableEXT = (PFNGLGETCOLORTABLEEXTPROC)loadFunction("glGetColorTableEXT");
  glGetColorTableParameterfv = (PFNGLGETCOLORTABLEPARAMETERFVPROC)loadFunction(
      "glGetColorTableParameterfv");
  glGetColorTableParameterfvEXT = (PFNGLGETCOLORTABLEPARAMETERFVEXTPROC)loadFunction(
      "glGetColorTableParameterfvEXT");
  glGetColorTableParameteriv = (PFNGLGETCOLORTABLEPARAMETERIVPROC)loadFunction(
      "glGetColorTableParameteriv");
  glGetColorTableParameterivEXT = (PFNGLGETCOLORTABLEPARAMETERIVEXTPROC)loadFunction(
      "glGetColorTableParameterivEXT");
  glGetCombinerInputParameterfvNV = (PFNGLGETCOMBINERINPUTPARAMETERFVNVPROC)loadFunction(
      "glGetCombinerInputParameterfvNV");
  glGetCombinerInputParameterivNV = (PFNGLGETCOMBINERINPUTPARAMETERIVNVPROC)loadFunction(
      "glGetCombinerInputParameterivNV");
  glGetCombinerOutputParameterfvNV = (PFNGLGETCOMBINEROUTPUTPARAMETERFVNVPROC)loadFunction(
      "glGetCombinerOutputParameterfvNV");
  glGetCombinerOutputParameterivNV = (PFNGLGETCOMBINEROUTPUTPARAMETERIVNVPROC)loadFunction(
      "glGetCombinerOutputParameterivNV");
  glGetCombinerStageParameterfvNV = (PFNGLGETCOMBINERSTAGEPARAMETERFVNVPROC)loadFunction(
      "glGetCombinerStageParameterfvNV");
  glGetCommandHeaderNV = (PFNGLGETCOMMANDHEADERNVPROC)loadFunction("glGetCommandHeaderNV");
  glGetCompressedMultiTexImageEXT = (PFNGLGETCOMPRESSEDMULTITEXIMAGEEXTPROC)loadFunction(
      "glGetCompressedMultiTexImageEXT");
  glGetCompressedTexImage = (PFNGLGETCOMPRESSEDTEXIMAGEPROC)loadFunction(
      "glGetCompressedTexImage");
  glGetCompressedTexImageARB = (PFNGLGETCOMPRESSEDTEXIMAGEARBPROC)loadFunction(
      "glGetCompressedTexImageARB");
  glGetCompressedTextureImage = (PFNGLGETCOMPRESSEDTEXTUREIMAGEPROC)loadFunction(
      "glGetCompressedTextureImage");
  glGetCompressedTextureImageEXT = (PFNGLGETCOMPRESSEDTEXTUREIMAGEEXTPROC)loadFunction(
      "glGetCompressedTextureImageEXT");
  glGetCompressedTextureSubImage = (PFNGLGETCOMPRESSEDTEXTURESUBIMAGEPROC)loadFunction(
      "glGetCompressedTextureSubImage");
  glGetConvolutionFilter = (PFNGLGETCONVOLUTIONFILTERPROC)loadFunction("glGetConvolutionFilter");
  glGetConvolutionFilterEXT = (PFNGLGETCONVOLUTIONFILTEREXTPROC)loadFunction(
      "glGetConvolutionFilterEXT");
  glGetConvolutionParameterfv = (PFNGLGETCONVOLUTIONPARAMETERFVPROC)loadFunction(
      "glGetConvolutionParameterfv");
  glGetConvolutionParameterfvEXT = (PFNGLGETCONVOLUTIONPARAMETERFVEXTPROC)loadFunction(
      "glGetConvolutionParameterfvEXT");
  glGetConvolutionParameteriv = (PFNGLGETCONVOLUTIONPARAMETERIVPROC)loadFunction(
      "glGetConvolutionParameteriv");
  glGetConvolutionParameterivEXT = (PFNGLGETCONVOLUTIONPARAMETERIVEXTPROC)loadFunction(
      "glGetConvolutionParameterivEXT");
  glGetCoverageModulationTableNV = (PFNGLGETCOVERAGEMODULATIONTABLENVPROC)loadFunction(
      "glGetCoverageModulationTableNV");
  glGetDebugMessageLog = (PFNGLGETDEBUGMESSAGELOGPROC)loadFunction("glGetDebugMessageLog");
  glGetDebugMessageLogAMD = (PFNGLGETDEBUGMESSAGELOGAMDPROC)loadFunction(
      "glGetDebugMessageLogAMD");
  glGetDebugMessageLogARB = (PFNGLGETDEBUGMESSAGELOGARBPROC)loadFunction(
      "glGetDebugMessageLogARB");
  glGetDebugMessageLogKHR = (PFNGLGETDEBUGMESSAGELOGKHRPROC)loadFunction(
      "glGetDebugMessageLogKHR");
  glGetDoubleIndexedvEXT = (PFNGLGETDOUBLEINDEXEDVEXTPROC)loadFunction("glGetDoubleIndexedvEXT");
  glGetDoublei_v = (PFNGLGETDOUBLEI_VPROC)loadFunction("glGetDoublei_v");
  glGetDoublei_vEXT = (PFNGLGETDOUBLEI_VEXTPROC)loadFunction("glGetDoublei_vEXT");
  glGetDoublev = (PFNGLGETDOUBLEVPROC)loadFunction("glGetDoublev");
  glGetError = (PFNGLGETERRORPROC)loadFunction("glGetError");
  glGetFenceivNV = (PFNGLGETFENCEIVNVPROC)loadFunction("glGetFenceivNV");
  glGetFinalCombinerInputParameterfvNV = (PFNGLGETFINALCOMBINERINPUTPARAMETERFVNVPROC)loadFunction(
      "glGetFinalCombinerInputParameterfvNV");
  glGetFinalCombinerInputParameterivNV = (PFNGLGETFINALCOMBINERINPUTPARAMETERIVNVPROC)loadFunction(
      "glGetFinalCombinerInputParameterivNV");
  glGetFirstPerfQueryIdINTEL = (PFNGLGETFIRSTPERFQUERYIDINTELPROC)loadFunction(
      "glGetFirstPerfQueryIdINTEL");
  glGetFloatIndexedvEXT = (PFNGLGETFLOATINDEXEDVEXTPROC)loadFunction("glGetFloatIndexedvEXT");
  glGetFloati_v = (PFNGLGETFLOATI_VPROC)loadFunction("glGetFloati_v");
  glGetFloati_vEXT = (PFNGLGETFLOATI_VEXTPROC)loadFunction("glGetFloati_vEXT");
  glGetFloatv = (PFNGLGETFLOATVPROC)loadFunction("glGetFloatv");
  glGetFragDataIndex = (PFNGLGETFRAGDATAINDEXPROC)loadFunction("glGetFragDataIndex");
  glGetFragDataLocation = (PFNGLGETFRAGDATALOCATIONPROC)loadFunction("glGetFragDataLocation");
  glGetFragDataLocationEXT = (PFNGLGETFRAGDATALOCATIONEXTPROC)loadFunction(
      "glGetFragDataLocationEXT");
  glGetFramebufferAttachmentParameteriv = (PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC)
      loadFunction("glGetFramebufferAttachmentParameteriv");
  glGetFramebufferAttachmentParameterivEXT = (PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVEXTPROC)
      loadFunction("glGetFramebufferAttachmentParameterivEXT");
  glGetFramebufferParameterfvAMD = (PFNGLGETFRAMEBUFFERPARAMETERFVAMDPROC)loadFunction(
      "glGetFramebufferParameterfvAMD");
  glGetFramebufferParameteriv = (PFNGLGETFRAMEBUFFERPARAMETERIVPROC)loadFunction(
      "glGetFramebufferParameteriv");
  glGetFramebufferParameterivEXT = (PFNGLGETFRAMEBUFFERPARAMETERIVEXTPROC)loadFunction(
      "glGetFramebufferParameterivEXT");
  glGetGraphicsResetStatus = (PFNGLGETGRAPHICSRESETSTATUSPROC)loadFunction(
      "glGetGraphicsResetStatus");
  glGetGraphicsResetStatusARB = (PFNGLGETGRAPHICSRESETSTATUSARBPROC)loadFunction(
      "glGetGraphicsResetStatusARB");
  glGetGraphicsResetStatusKHR = (PFNGLGETGRAPHICSRESETSTATUSKHRPROC)loadFunction(
      "glGetGraphicsResetStatusKHR");
  glGetHandleARB = (PFNGLGETHANDLEARBPROC)loadFunction("glGetHandleARB");
  glGetHistogram = (PFNGLGETHISTOGRAMPROC)loadFunction("glGetHistogram");
  glGetHistogramEXT = (PFNGLGETHISTOGRAMEXTPROC)loadFunction("glGetHistogramEXT");
  glGetHistogramParameterfv = (PFNGLGETHISTOGRAMPARAMETERFVPROC)loadFunction(
      "glGetHistogramParameterfv");
  glGetHistogramParameterfvEXT = (PFNGLGETHISTOGRAMPARAMETERFVEXTPROC)loadFunction(
      "glGetHistogramParameterfvEXT");
  glGetHistogramParameteriv = (PFNGLGETHISTOGRAMPARAMETERIVPROC)loadFunction(
      "glGetHistogramParameteriv");
  glGetHistogramParameterivEXT = (PFNGLGETHISTOGRAMPARAMETERIVEXTPROC)loadFunction(
      "glGetHistogramParameterivEXT");
  glGetImageHandleARB = (PFNGLGETIMAGEHANDLEARBPROC)loadFunction("glGetImageHandleARB");
  glGetImageHandleNV = (PFNGLGETIMAGEHANDLENVPROC)loadFunction("glGetImageHandleNV");
  glGetInfoLogARB = (PFNGLGETINFOLOGARBPROC)loadFunction("glGetInfoLogARB");
  glGetInteger64i_v = (PFNGLGETINTEGER64I_VPROC)loadFunction("glGetInteger64i_v");
  glGetInteger64v = (PFNGLGETINTEGER64VPROC)loadFunction("glGetInteger64v");
  glGetIntegerIndexedvEXT = (PFNGLGETINTEGERINDEXEDVEXTPROC)loadFunction(
      "glGetIntegerIndexedvEXT");
  glGetIntegeri_v = (PFNGLGETINTEGERI_VPROC)loadFunction("glGetIntegeri_v");
  glGetIntegerui64i_vNV = (PFNGLGETINTEGERUI64I_VNVPROC)loadFunction("glGetIntegerui64i_vNV");
  glGetIntegerui64vNV = (PFNGLGETINTEGERUI64VNVPROC)loadFunction("glGetIntegerui64vNV");
  glGetIntegerv = (PFNGLGETINTEGERVPROC)loadFunction("glGetIntegerv");
  glGetInternalformatSampleivNV = (PFNGLGETINTERNALFORMATSAMPLEIVNVPROC)loadFunction(
      "glGetInternalformatSampleivNV");
  glGetInternalformati64v = (PFNGLGETINTERNALFORMATI64VPROC)loadFunction(
      "glGetInternalformati64v");
  glGetInternalformativ = (PFNGLGETINTERNALFORMATIVPROC)loadFunction("glGetInternalformativ");
  glGetInvariantBooleanvEXT = (PFNGLGETINVARIANTBOOLEANVEXTPROC)loadFunction(
      "glGetInvariantBooleanvEXT");
  glGetInvariantFloatvEXT = (PFNGLGETINVARIANTFLOATVEXTPROC)loadFunction(
      "glGetInvariantFloatvEXT");
  glGetInvariantIntegervEXT = (PFNGLGETINVARIANTINTEGERVEXTPROC)loadFunction(
      "glGetInvariantIntegervEXT");
  glGetLightfv = (PFNGLGETLIGHTFVPROC)loadFunction("glGetLightfv");
  glGetLightiv = (PFNGLGETLIGHTIVPROC)loadFunction("glGetLightiv");
  glGetLocalConstantBooleanvEXT = (PFNGLGETLOCALCONSTANTBOOLEANVEXTPROC)loadFunction(
      "glGetLocalConstantBooleanvEXT");
  glGetLocalConstantFloatvEXT = (PFNGLGETLOCALCONSTANTFLOATVEXTPROC)loadFunction(
      "glGetLocalConstantFloatvEXT");
  glGetLocalConstantIntegervEXT = (PFNGLGETLOCALCONSTANTINTEGERVEXTPROC)loadFunction(
      "glGetLocalConstantIntegervEXT");
  glGetMapAttribParameterfvNV = (PFNGLGETMAPATTRIBPARAMETERFVNVPROC)loadFunction(
      "glGetMapAttribParameterfvNV");
  glGetMapAttribParameterivNV = (PFNGLGETMAPATTRIBPARAMETERIVNVPROC)loadFunction(
      "glGetMapAttribParameterivNV");
  glGetMapControlPointsNV = (PFNGLGETMAPCONTROLPOINTSNVPROC)loadFunction(
      "glGetMapControlPointsNV");
  glGetMapParameterfvNV = (PFNGLGETMAPPARAMETERFVNVPROC)loadFunction("glGetMapParameterfvNV");
  glGetMapParameterivNV = (PFNGLGETMAPPARAMETERIVNVPROC)loadFunction("glGetMapParameterivNV");
  glGetMapdv = (PFNGLGETMAPDVPROC)loadFunction("glGetMapdv");
  glGetMapfv = (PFNGLGETMAPFVPROC)loadFunction("glGetMapfv");
  glGetMapiv = (PFNGLGETMAPIVPROC)loadFunction("glGetMapiv");
  glGetMaterialfv = (PFNGLGETMATERIALFVPROC)loadFunction("glGetMaterialfv");
  glGetMaterialiv = (PFNGLGETMATERIALIVPROC)loadFunction("glGetMaterialiv");
  glGetMemoryObjectDetachedResourcesuivNV = (PFNGLGETMEMORYOBJECTDETACHEDRESOURCESUIVNVPROC)
      loadFunction("glGetMemoryObjectDetachedResourcesuivNV");
  glGetMemoryObjectParameterivEXT = (PFNGLGETMEMORYOBJECTPARAMETERIVEXTPROC)loadFunction(
      "glGetMemoryObjectParameterivEXT");
  glGetMinmax = (PFNGLGETMINMAXPROC)loadFunction("glGetMinmax");
  glGetMinmaxEXT = (PFNGLGETMINMAXEXTPROC)loadFunction("glGetMinmaxEXT");
  glGetMinmaxParameterfv = (PFNGLGETMINMAXPARAMETERFVPROC)loadFunction("glGetMinmaxParameterfv");
  glGetMinmaxParameterfvEXT = (PFNGLGETMINMAXPARAMETERFVEXTPROC)loadFunction(
      "glGetMinmaxParameterfvEXT");
  glGetMinmaxParameteriv = (PFNGLGETMINMAXPARAMETERIVPROC)loadFunction("glGetMinmaxParameteriv");
  glGetMinmaxParameterivEXT = (PFNGLGETMINMAXPARAMETERIVEXTPROC)loadFunction(
      "glGetMinmaxParameterivEXT");
  glGetMultiTexEnvfvEXT = (PFNGLGETMULTITEXENVFVEXTPROC)loadFunction("glGetMultiTexEnvfvEXT");
  glGetMultiTexEnvivEXT = (PFNGLGETMULTITEXENVIVEXTPROC)loadFunction("glGetMultiTexEnvivEXT");
  glGetMultiTexGendvEXT = (PFNGLGETMULTITEXGENDVEXTPROC)loadFunction("glGetMultiTexGendvEXT");
  glGetMultiTexGenfvEXT = (PFNGLGETMULTITEXGENFVEXTPROC)loadFunction("glGetMultiTexGenfvEXT");
  glGetMultiTexGenivEXT = (PFNGLGETMULTITEXGENIVEXTPROC)loadFunction("glGetMultiTexGenivEXT");
  glGetMultiTexImageEXT = (PFNGLGETMULTITEXIMAGEEXTPROC)loadFunction("glGetMultiTexImageEXT");
  glGetMultiTexLevelParameterfvEXT = (PFNGLGETMULTITEXLEVELPARAMETERFVEXTPROC)loadFunction(
      "glGetMultiTexLevelParameterfvEXT");
  glGetMultiTexLevelParameterivEXT = (PFNGLGETMULTITEXLEVELPARAMETERIVEXTPROC)loadFunction(
      "glGetMultiTexLevelParameterivEXT");
  glGetMultiTexParameterIivEXT = (PFNGLGETMULTITEXPARAMETERIIVEXTPROC)loadFunction(
      "glGetMultiTexParameterIivEXT");
  glGetMultiTexParameterIuivEXT = (PFNGLGETMULTITEXPARAMETERIUIVEXTPROC)loadFunction(
      "glGetMultiTexParameterIuivEXT");
  glGetMultiTexParameterfvEXT = (PFNGLGETMULTITEXPARAMETERFVEXTPROC)loadFunction(
      "glGetMultiTexParameterfvEXT");
  glGetMultiTexParameterivEXT = (PFNGLGETMULTITEXPARAMETERIVEXTPROC)loadFunction(
      "glGetMultiTexParameterivEXT");
  glGetMultisamplefv = (PFNGLGETMULTISAMPLEFVPROC)loadFunction("glGetMultisamplefv");
  glGetMultisamplefvNV = (PFNGLGETMULTISAMPLEFVNVPROC)loadFunction("glGetMultisamplefvNV");
  glGetNamedBufferParameteri64v = (PFNGLGETNAMEDBUFFERPARAMETERI64VPROC)loadFunction(
      "glGetNamedBufferParameteri64v");
  glGetNamedBufferParameteriv = (PFNGLGETNAMEDBUFFERPARAMETERIVPROC)loadFunction(
      "glGetNamedBufferParameteriv");
  glGetNamedBufferParameterivEXT = (PFNGLGETNAMEDBUFFERPARAMETERIVEXTPROC)loadFunction(
      "glGetNamedBufferParameterivEXT");
  glGetNamedBufferParameterui64vNV = (PFNGLGETNAMEDBUFFERPARAMETERUI64VNVPROC)loadFunction(
      "glGetNamedBufferParameterui64vNV");
  glGetNamedBufferPointerv = (PFNGLGETNAMEDBUFFERPOINTERVPROC)loadFunction(
      "glGetNamedBufferPointerv");
  glGetNamedBufferPointervEXT = (PFNGLGETNAMEDBUFFERPOINTERVEXTPROC)loadFunction(
      "glGetNamedBufferPointervEXT");
  glGetNamedBufferSubData = (PFNGLGETNAMEDBUFFERSUBDATAPROC)loadFunction(
      "glGetNamedBufferSubData");
  glGetNamedBufferSubDataEXT = (PFNGLGETNAMEDBUFFERSUBDATAEXTPROC)loadFunction(
      "glGetNamedBufferSubDataEXT");
  glGetNamedFramebufferParameterfvAMD = (PFNGLGETNAMEDFRAMEBUFFERPARAMETERFVAMDPROC)loadFunction(
      "glGetNamedFramebufferParameterfvAMD");
  glGetNamedFramebufferAttachmentParameteriv = (PFNGLGETNAMEDFRAMEBUFFERATTACHMENTPARAMETERIVPROC)
      loadFunction("glGetNamedFramebufferAttachmentParameteriv");
  glGetNamedFramebufferAttachmentParameterivEXT =
      (PFNGLGETNAMEDFRAMEBUFFERATTACHMENTPARAMETERIVEXTPROC)loadFunction(
          "glGetNamedFramebufferAttachmentParameterivEXT");
  glGetNamedFramebufferParameteriv = (PFNGLGETNAMEDFRAMEBUFFERPARAMETERIVPROC)loadFunction(
      "glGetNamedFramebufferParameteriv");
  glGetNamedFramebufferParameterivEXT = (PFNGLGETNAMEDFRAMEBUFFERPARAMETERIVEXTPROC)loadFunction(
      "glGetNamedFramebufferParameterivEXT");
  glGetNamedProgramLocalParameterIivEXT = (PFNGLGETNAMEDPROGRAMLOCALPARAMETERIIVEXTPROC)
      loadFunction("glGetNamedProgramLocalParameterIivEXT");
  glGetNamedProgramLocalParameterIuivEXT = (PFNGLGETNAMEDPROGRAMLOCALPARAMETERIUIVEXTPROC)
      loadFunction("glGetNamedProgramLocalParameterIuivEXT");
  glGetNamedProgramLocalParameterdvEXT = (PFNGLGETNAMEDPROGRAMLOCALPARAMETERDVEXTPROC)loadFunction(
      "glGetNamedProgramLocalParameterdvEXT");
  glGetNamedProgramLocalParameterfvEXT = (PFNGLGETNAMEDPROGRAMLOCALPARAMETERFVEXTPROC)loadFunction(
      "glGetNamedProgramLocalParameterfvEXT");
  glGetNamedProgramStringEXT = (PFNGLGETNAMEDPROGRAMSTRINGEXTPROC)loadFunction(
      "glGetNamedProgramStringEXT");
  glGetNamedProgramivEXT = (PFNGLGETNAMEDPROGRAMIVEXTPROC)loadFunction("glGetNamedProgramivEXT");
  glGetNamedRenderbufferParameteriv = (PFNGLGETNAMEDRENDERBUFFERPARAMETERIVPROC)loadFunction(
      "glGetNamedRenderbufferParameteriv");
  glGetNamedRenderbufferParameterivEXT = (PFNGLGETNAMEDRENDERBUFFERPARAMETERIVEXTPROC)loadFunction(
      "glGetNamedRenderbufferParameterivEXT");
  glGetNamedStringARB = (PFNGLGETNAMEDSTRINGARBPROC)loadFunction("glGetNamedStringARB");
  glGetNamedStringivARB = (PFNGLGETNAMEDSTRINGIVARBPROC)loadFunction("glGetNamedStringivARB");
  glGetNextPerfQueryIdINTEL = (PFNGLGETNEXTPERFQUERYIDINTELPROC)loadFunction(
      "glGetNextPerfQueryIdINTEL");
  glGetObjectLabel = (PFNGLGETOBJECTLABELPROC)loadFunction("glGetObjectLabel");
  glGetObjectLabelEXT = (PFNGLGETOBJECTLABELEXTPROC)loadFunction("glGetObjectLabelEXT");
  glGetObjectLabelKHR = (PFNGLGETOBJECTLABELKHRPROC)loadFunction("glGetObjectLabelKHR");
  glGetObjectParameterfvARB = (PFNGLGETOBJECTPARAMETERFVARBPROC)loadFunction(
      "glGetObjectParameterfvARB");
  glGetObjectParameterivAPPLE = (PFNGLGETOBJECTPARAMETERIVAPPLEPROC)loadFunction(
      "glGetObjectParameterivAPPLE");
  glGetObjectParameterivARB = (PFNGLGETOBJECTPARAMETERIVARBPROC)loadFunction(
      "glGetObjectParameterivARB");
  glGetObjectPtrLabel = (PFNGLGETOBJECTPTRLABELPROC)loadFunction("glGetObjectPtrLabel");
  glGetObjectPtrLabelKHR = (PFNGLGETOBJECTPTRLABELKHRPROC)loadFunction("glGetObjectPtrLabelKHR");
  glGetOcclusionQueryivNV = (PFNGLGETOCCLUSIONQUERYIVNVPROC)loadFunction(
      "glGetOcclusionQueryivNV");
  glGetOcclusionQueryuivNV = (PFNGLGETOCCLUSIONQUERYUIVNVPROC)loadFunction(
      "glGetOcclusionQueryuivNV");
  glGetPathColorGenfvNV = (PFNGLGETPATHCOLORGENFVNVPROC)loadFunction("glGetPathColorGenfvNV");
  glGetPathColorGenivNV = (PFNGLGETPATHCOLORGENIVNVPROC)loadFunction("glGetPathColorGenivNV");
  glGetPathCommandsNV = (PFNGLGETPATHCOMMANDSNVPROC)loadFunction("glGetPathCommandsNV");
  glGetPathCoordsNV = (PFNGLGETPATHCOORDSNVPROC)loadFunction("glGetPathCoordsNV");
  glGetPathDashArrayNV = (PFNGLGETPATHDASHARRAYNVPROC)loadFunction("glGetPathDashArrayNV");
  glGetPathLengthNV = (PFNGLGETPATHLENGTHNVPROC)loadFunction("glGetPathLengthNV");
  glGetPathMetricRangeNV = (PFNGLGETPATHMETRICRANGENVPROC)loadFunction("glGetPathMetricRangeNV");
  glGetPathMetricsNV = (PFNGLGETPATHMETRICSNVPROC)loadFunction("glGetPathMetricsNV");
  glGetPathParameterfvNV = (PFNGLGETPATHPARAMETERFVNVPROC)loadFunction("glGetPathParameterfvNV");
  glGetPathParameterivNV = (PFNGLGETPATHPARAMETERIVNVPROC)loadFunction("glGetPathParameterivNV");
  glGetPathSpacingNV = (PFNGLGETPATHSPACINGNVPROC)loadFunction("glGetPathSpacingNV");
  glGetPathTexGenfvNV = (PFNGLGETPATHTEXGENFVNVPROC)loadFunction("glGetPathTexGenfvNV");
  glGetPathTexGenivNV = (PFNGLGETPATHTEXGENIVNVPROC)loadFunction("glGetPathTexGenivNV");
  glGetPerfCounterInfoINTEL = (PFNGLGETPERFCOUNTERINFOINTELPROC)loadFunction(
      "glGetPerfCounterInfoINTEL");
  glGetPerfMonitorCounterDataAMD = (PFNGLGETPERFMONITORCOUNTERDATAAMDPROC)loadFunction(
      "glGetPerfMonitorCounterDataAMD");
  glGetPerfMonitorCounterInfoAMD = (PFNGLGETPERFMONITORCOUNTERINFOAMDPROC)loadFunction(
      "glGetPerfMonitorCounterInfoAMD");
  glGetPerfMonitorCounterStringAMD = (PFNGLGETPERFMONITORCOUNTERSTRINGAMDPROC)loadFunction(
      "glGetPerfMonitorCounterStringAMD");
  glGetPerfMonitorCountersAMD = (PFNGLGETPERFMONITORCOUNTERSAMDPROC)loadFunction(
      "glGetPerfMonitorCountersAMD");
  glGetPerfMonitorGroupStringAMD = (PFNGLGETPERFMONITORGROUPSTRINGAMDPROC)loadFunction(
      "glGetPerfMonitorGroupStringAMD");
  glGetPerfMonitorGroupsAMD = (PFNGLGETPERFMONITORGROUPSAMDPROC)loadFunction(
      "glGetPerfMonitorGroupsAMD");
  glGetPerfQueryDataINTEL = (PFNGLGETPERFQUERYDATAINTELPROC)loadFunction(
      "glGetPerfQueryDataINTEL");
  glGetPerfQueryIdByNameINTEL = (PFNGLGETPERFQUERYIDBYNAMEINTELPROC)loadFunction(
      "glGetPerfQueryIdByNameINTEL");
  glGetPerfQueryInfoINTEL = (PFNGLGETPERFQUERYINFOINTELPROC)loadFunction(
      "glGetPerfQueryInfoINTEL");
  glGetPixelMapfv = (PFNGLGETPIXELMAPFVPROC)loadFunction("glGetPixelMapfv");
  glGetPixelMapuiv = (PFNGLGETPIXELMAPUIVPROC)loadFunction("glGetPixelMapuiv");
  glGetPixelMapusv = (PFNGLGETPIXELMAPUSVPROC)loadFunction("glGetPixelMapusv");
  glGetPixelTransformParameterfvEXT = (PFNGLGETPIXELTRANSFORMPARAMETERFVEXTPROC)loadFunction(
      "glGetPixelTransformParameterfvEXT");
  glGetPixelTransformParameterivEXT = (PFNGLGETPIXELTRANSFORMPARAMETERIVEXTPROC)loadFunction(
      "glGetPixelTransformParameterivEXT");
  glGetPointerIndexedvEXT = (PFNGLGETPOINTERINDEXEDVEXTPROC)loadFunction(
      "glGetPointerIndexedvEXT");
  glGetPointeri_vEXT = (PFNGLGETPOINTERI_VEXTPROC)loadFunction("glGetPointeri_vEXT");
  glGetPointerv = (PFNGLGETPOINTERVPROC)loadFunction("glGetPointerv");
  glGetPointervEXT = (PFNGLGETPOINTERVEXTPROC)loadFunction("glGetPointervEXT");
  glGetPointervKHR = (PFNGLGETPOINTERVKHRPROC)loadFunction("glGetPointervKHR");
  glGetPolygonStipple = (PFNGLGETPOLYGONSTIPPLEPROC)loadFunction("glGetPolygonStipple");
  glGetProgramBinary = (PFNGLGETPROGRAMBINARYPROC)loadFunction("glGetProgramBinary");
  glGetProgramEnvParameterIivNV = (PFNGLGETPROGRAMENVPARAMETERIIVNVPROC)loadFunction(
      "glGetProgramEnvParameterIivNV");
  glGetProgramEnvParameterIuivNV = (PFNGLGETPROGRAMENVPARAMETERIUIVNVPROC)loadFunction(
      "glGetProgramEnvParameterIuivNV");
  glGetProgramEnvParameterdvARB = (PFNGLGETPROGRAMENVPARAMETERDVARBPROC)loadFunction(
      "glGetProgramEnvParameterdvARB");
  glGetProgramEnvParameterfvARB = (PFNGLGETPROGRAMENVPARAMETERFVARBPROC)loadFunction(
      "glGetProgramEnvParameterfvARB");
  glGetProgramInfoLog = (PFNGLGETPROGRAMINFOLOGPROC)loadFunction("glGetProgramInfoLog");
  glGetProgramInterfaceiv = (PFNGLGETPROGRAMINTERFACEIVPROC)loadFunction(
      "glGetProgramInterfaceiv");
  glGetProgramLocalParameterIivNV = (PFNGLGETPROGRAMLOCALPARAMETERIIVNVPROC)loadFunction(
      "glGetProgramLocalParameterIivNV");
  glGetProgramLocalParameterIuivNV = (PFNGLGETPROGRAMLOCALPARAMETERIUIVNVPROC)loadFunction(
      "glGetProgramLocalParameterIuivNV");
  glGetProgramLocalParameterdvARB = (PFNGLGETPROGRAMLOCALPARAMETERDVARBPROC)loadFunction(
      "glGetProgramLocalParameterdvARB");
  glGetProgramLocalParameterfvARB = (PFNGLGETPROGRAMLOCALPARAMETERFVARBPROC)loadFunction(
      "glGetProgramLocalParameterfvARB");
  glGetProgramNamedParameterdvNV = (PFNGLGETPROGRAMNAMEDPARAMETERDVNVPROC)loadFunction(
      "glGetProgramNamedParameterdvNV");
  glGetProgramNamedParameterfvNV = (PFNGLGETPROGRAMNAMEDPARAMETERFVNVPROC)loadFunction(
      "glGetProgramNamedParameterfvNV");
  glGetProgramParameterdvNV = (PFNGLGETPROGRAMPARAMETERDVNVPROC)loadFunction(
      "glGetProgramParameterdvNV");
  glGetProgramParameterfvNV = (PFNGLGETPROGRAMPARAMETERFVNVPROC)loadFunction(
      "glGetProgramParameterfvNV");
  glGetProgramPipelineInfoLog = (PFNGLGETPROGRAMPIPELINEINFOLOGPROC)loadFunction(
      "glGetProgramPipelineInfoLog");
  glGetProgramPipelineInfoLogEXT = (PFNGLGETPROGRAMPIPELINEINFOLOGEXTPROC)loadFunction(
      "glGetProgramPipelineInfoLogEXT");
  glGetProgramPipelineiv = (PFNGLGETPROGRAMPIPELINEIVPROC)loadFunction("glGetProgramPipelineiv");
  glGetProgramPipelineivEXT = (PFNGLGETPROGRAMPIPELINEIVEXTPROC)loadFunction(
      "glGetProgramPipelineivEXT");
  glGetProgramResourceIndex = (PFNGLGETPROGRAMRESOURCEINDEXPROC)loadFunction(
      "glGetProgramResourceIndex");
  glGetProgramResourceLocation = (PFNGLGETPROGRAMRESOURCELOCATIONPROC)loadFunction(
      "glGetProgramResourceLocation");
  glGetProgramResourceLocationIndex = (PFNGLGETPROGRAMRESOURCELOCATIONINDEXPROC)loadFunction(
      "glGetProgramResourceLocationIndex");
  glGetProgramResourceName = (PFNGLGETPROGRAMRESOURCENAMEPROC)loadFunction(
      "glGetProgramResourceName");
  glGetProgramResourcefvNV = (PFNGLGETPROGRAMRESOURCEFVNVPROC)loadFunction(
      "glGetProgramResourcefvNV");
  glGetProgramResourceiv = (PFNGLGETPROGRAMRESOURCEIVPROC)loadFunction("glGetProgramResourceiv");
  glGetProgramStageiv = (PFNGLGETPROGRAMSTAGEIVPROC)loadFunction("glGetProgramStageiv");
  glGetProgramStringARB = (PFNGLGETPROGRAMSTRINGARBPROC)loadFunction("glGetProgramStringARB");
  glGetProgramStringNV = (PFNGLGETPROGRAMSTRINGNVPROC)loadFunction("glGetProgramStringNV");
  glGetProgramSubroutineParameteruivNV = (PFNGLGETPROGRAMSUBROUTINEPARAMETERUIVNVPROC)loadFunction(
      "glGetProgramSubroutineParameteruivNV");
  glGetProgramiv = (PFNGLGETPROGRAMIVPROC)loadFunction("glGetProgramiv");
  glGetProgramivARB = (PFNGLGETPROGRAMIVARBPROC)loadFunction("glGetProgramivARB");
  glGetProgramivNV = (PFNGLGETPROGRAMIVNVPROC)loadFunction("glGetProgramivNV");
  glGetQueryBufferObjecti64v = (PFNGLGETQUERYBUFFEROBJECTI64VPROC)loadFunction(
      "glGetQueryBufferObjecti64v");
  glGetQueryBufferObjectiv = (PFNGLGETQUERYBUFFEROBJECTIVPROC)loadFunction(
      "glGetQueryBufferObjectiv");
  glGetQueryBufferObjectui64v = (PFNGLGETQUERYBUFFEROBJECTUI64VPROC)loadFunction(
      "glGetQueryBufferObjectui64v");
  glGetQueryBufferObjectuiv = (PFNGLGETQUERYBUFFEROBJECTUIVPROC)loadFunction(
      "glGetQueryBufferObjectuiv");
  glGetQueryIndexediv = (PFNGLGETQUERYINDEXEDIVPROC)loadFunction("glGetQueryIndexediv");
  glGetQueryObjecti64v = (PFNGLGETQUERYOBJECTI64VPROC)loadFunction("glGetQueryObjecti64v");
  glGetQueryObjecti64vEXT = (PFNGLGETQUERYOBJECTI64VEXTPROC)loadFunction(
      "glGetQueryObjecti64vEXT");
  glGetQueryObjectiv = (PFNGLGETQUERYOBJECTIVPROC)loadFunction("glGetQueryObjectiv");
  glGetQueryObjectivARB = (PFNGLGETQUERYOBJECTIVARBPROC)loadFunction("glGetQueryObjectivARB");
  glGetQueryObjectui64v = (PFNGLGETQUERYOBJECTUI64VPROC)loadFunction("glGetQueryObjectui64v");
  glGetQueryObjectui64vEXT = (PFNGLGETQUERYOBJECTUI64VEXTPROC)loadFunction(
      "glGetQueryObjectui64vEXT");
  glGetQueryObjectuiv = (PFNGLGETQUERYOBJECTUIVPROC)loadFunction("glGetQueryObjectuiv");
  glGetQueryObjectuivARB = (PFNGLGETQUERYOBJECTUIVARBPROC)loadFunction("glGetQueryObjectuivARB");
  glGetQueryiv = (PFNGLGETQUERYIVPROC)loadFunction("glGetQueryiv");
  glGetQueryivARB = (PFNGLGETQUERYIVARBPROC)loadFunction("glGetQueryivARB");
  glGetRenderbufferParameteriv = (PFNGLGETRENDERBUFFERPARAMETERIVPROC)loadFunction(
      "glGetRenderbufferParameteriv");
  glGetRenderbufferParameterivEXT = (PFNGLGETRENDERBUFFERPARAMETERIVEXTPROC)loadFunction(
      "glGetRenderbufferParameterivEXT");
  glGetSamplerParameterIiv = (PFNGLGETSAMPLERPARAMETERIIVPROC)loadFunction(
      "glGetSamplerParameterIiv");
  glGetSamplerParameterIuiv = (PFNGLGETSAMPLERPARAMETERIUIVPROC)loadFunction(
      "glGetSamplerParameterIuiv");
  glGetSamplerParameterfv = (PFNGLGETSAMPLERPARAMETERFVPROC)loadFunction(
      "glGetSamplerParameterfv");
  glGetSamplerParameteriv = (PFNGLGETSAMPLERPARAMETERIVPROC)loadFunction(
      "glGetSamplerParameteriv");
  glGetSemaphoreParameterivNV = (PFNGLGETSEMAPHOREPARAMETERIVNVPROC)loadFunction(
      "glGetSemaphoreParameterivNV");
  glGetSemaphoreParameterui64vEXT = (PFNGLGETSEMAPHOREPARAMETERUI64VEXTPROC)loadFunction(
      "glGetSemaphoreParameterui64vEXT");
  glGetSeparableFilter = (PFNGLGETSEPARABLEFILTERPROC)loadFunction("glGetSeparableFilter");
  glGetSeparableFilterEXT = (PFNGLGETSEPARABLEFILTEREXTPROC)loadFunction(
      "glGetSeparableFilterEXT");
  glGetShaderInfoLog = (PFNGLGETSHADERINFOLOGPROC)loadFunction("glGetShaderInfoLog");
  glGetShaderPrecisionFormat = (PFNGLGETSHADERPRECISIONFORMATPROC)loadFunction(
      "glGetShaderPrecisionFormat");
  glGetShaderSource = (PFNGLGETSHADERSOURCEPROC)loadFunction("glGetShaderSource");
  glGetShaderSourceARB = (PFNGLGETSHADERSOURCEARBPROC)loadFunction("glGetShaderSourceARB");
  glGetShaderiv = (PFNGLGETSHADERIVPROC)loadFunction("glGetShaderiv");
  glGetShadingRateImagePaletteNV = (PFNGLGETSHADINGRATEIMAGEPALETTENVPROC)loadFunction(
      "glGetShadingRateImagePaletteNV");
  glGetShadingRateSampleLocationivNV = (PFNGLGETSHADINGRATESAMPLELOCATIONIVNVPROC)loadFunction(
      "glGetShadingRateSampleLocationivNV");
  glGetStageIndexNV = (PFNGLGETSTAGEINDEXNVPROC)loadFunction("glGetStageIndexNV");
  glGetString = (PFNGLGETSTRINGPROC)loadFunction("glGetString");
  glGetStringi = (PFNGLGETSTRINGIPROC)loadFunction("glGetStringi");
  glGetSubroutineIndex = (PFNGLGETSUBROUTINEINDEXPROC)loadFunction("glGetSubroutineIndex");
  glGetSubroutineUniformLocation = (PFNGLGETSUBROUTINEUNIFORMLOCATIONPROC)loadFunction(
      "glGetSubroutineUniformLocation");
  glGetSynciv = (PFNGLGETSYNCIVPROC)loadFunction("glGetSynciv");
  glGetTexEnvfv = (PFNGLGETTEXENVFVPROC)loadFunction("glGetTexEnvfv");
  glGetTexEnviv = (PFNGLGETTEXENVIVPROC)loadFunction("glGetTexEnviv");
  glGetTexGendv = (PFNGLGETTEXGENDVPROC)loadFunction("glGetTexGendv");
  glGetTexGenfv = (PFNGLGETTEXGENFVPROC)loadFunction("glGetTexGenfv");
  glGetTexGeniv = (PFNGLGETTEXGENIVPROC)loadFunction("glGetTexGeniv");
  glGetTexImage = (PFNGLGETTEXIMAGEPROC)loadFunction("glGetTexImage");
  glGetTexLevelParameterfv = (PFNGLGETTEXLEVELPARAMETERFVPROC)loadFunction(
      "glGetTexLevelParameterfv");
  glGetTexLevelParameteriv = (PFNGLGETTEXLEVELPARAMETERIVPROC)loadFunction(
      "glGetTexLevelParameteriv");
  glGetTexParameterIiv = (PFNGLGETTEXPARAMETERIIVPROC)loadFunction("glGetTexParameterIiv");
  glGetTexParameterIivEXT = (PFNGLGETTEXPARAMETERIIVEXTPROC)loadFunction(
      "glGetTexParameterIivEXT");
  glGetTexParameterIuiv = (PFNGLGETTEXPARAMETERIUIVPROC)loadFunction("glGetTexParameterIuiv");
  glGetTexParameterIuivEXT = (PFNGLGETTEXPARAMETERIUIVEXTPROC)loadFunction(
      "glGetTexParameterIuivEXT");
  glGetTexParameterPointervAPPLE = (PFNGLGETTEXPARAMETERPOINTERVAPPLEPROC)loadFunction(
      "glGetTexParameterPointervAPPLE");
  glGetTexParameterfv = (PFNGLGETTEXPARAMETERFVPROC)loadFunction("glGetTexParameterfv");
  glGetTexParameteriv = (PFNGLGETTEXPARAMETERIVPROC)loadFunction("glGetTexParameteriv");
  glGetTextureHandleARB = (PFNGLGETTEXTUREHANDLEARBPROC)loadFunction("glGetTextureHandleARB");
  glGetTextureHandleNV = (PFNGLGETTEXTUREHANDLENVPROC)loadFunction("glGetTextureHandleNV");
  glGetTextureImage = (PFNGLGETTEXTUREIMAGEPROC)loadFunction("glGetTextureImage");
  glGetTextureImageEXT = (PFNGLGETTEXTUREIMAGEEXTPROC)loadFunction("glGetTextureImageEXT");
  glGetTextureLevelParameterfv = (PFNGLGETTEXTURELEVELPARAMETERFVPROC)loadFunction(
      "glGetTextureLevelParameterfv");
  glGetTextureLevelParameterfvEXT = (PFNGLGETTEXTURELEVELPARAMETERFVEXTPROC)loadFunction(
      "glGetTextureLevelParameterfvEXT");
  glGetTextureLevelParameteriv = (PFNGLGETTEXTURELEVELPARAMETERIVPROC)loadFunction(
      "glGetTextureLevelParameteriv");
  glGetTextureLevelParameterivEXT = (PFNGLGETTEXTURELEVELPARAMETERIVEXTPROC)loadFunction(
      "glGetTextureLevelParameterivEXT");
  glGetTextureParameterIiv = (PFNGLGETTEXTUREPARAMETERIIVPROC)loadFunction(
      "glGetTextureParameterIiv");
  glGetTextureParameterIivEXT = (PFNGLGETTEXTUREPARAMETERIIVEXTPROC)loadFunction(
      "glGetTextureParameterIivEXT");
  glGetTextureParameterIuiv = (PFNGLGETTEXTUREPARAMETERIUIVPROC)loadFunction(
      "glGetTextureParameterIuiv");
  glGetTextureParameterIuivEXT = (PFNGLGETTEXTUREPARAMETERIUIVEXTPROC)loadFunction(
      "glGetTextureParameterIuivEXT");
  glGetTextureParameterfv = (PFNGLGETTEXTUREPARAMETERFVPROC)loadFunction(
      "glGetTextureParameterfv");
  glGetTextureParameterfvEXT = (PFNGLGETTEXTUREPARAMETERFVEXTPROC)loadFunction(
      "glGetTextureParameterfvEXT");
  glGetTextureParameteriv = (PFNGLGETTEXTUREPARAMETERIVPROC)loadFunction(
      "glGetTextureParameteriv");
  glGetTextureParameterivEXT = (PFNGLGETTEXTUREPARAMETERIVEXTPROC)loadFunction(
      "glGetTextureParameterivEXT");
  glGetTextureSamplerHandleARB = (PFNGLGETTEXTURESAMPLERHANDLEARBPROC)loadFunction(
      "glGetTextureSamplerHandleARB");
  glGetTextureSamplerHandleNV = (PFNGLGETTEXTURESAMPLERHANDLENVPROC)loadFunction(
      "glGetTextureSamplerHandleNV");
  glGetTextureSubImage = (PFNGLGETTEXTURESUBIMAGEPROC)loadFunction("glGetTextureSubImage");
  glGetTrackMatrixivNV = (PFNGLGETTRACKMATRIXIVNVPROC)loadFunction("glGetTrackMatrixivNV");
  glGetTransformFeedbackVarying = (PFNGLGETTRANSFORMFEEDBACKVARYINGPROC)loadFunction(
      "glGetTransformFeedbackVarying");
  glGetTransformFeedbackVaryingEXT = (PFNGLGETTRANSFORMFEEDBACKVARYINGEXTPROC)loadFunction(
      "glGetTransformFeedbackVaryingEXT");
  glGetTransformFeedbackVaryingNV = (PFNGLGETTRANSFORMFEEDBACKVARYINGNVPROC)loadFunction(
      "glGetTransformFeedbackVaryingNV");
  glGetTransformFeedbacki64_v = (PFNGLGETTRANSFORMFEEDBACKI64_VPROC)loadFunction(
      "glGetTransformFeedbacki64_v");
  glGetTransformFeedbacki_v = (PFNGLGETTRANSFORMFEEDBACKI_VPROC)loadFunction(
      "glGetTransformFeedbacki_v");
  glGetTransformFeedbackiv = (PFNGLGETTRANSFORMFEEDBACKIVPROC)loadFunction(
      "glGetTransformFeedbackiv");
  glGetUniformBlockIndex = (PFNGLGETUNIFORMBLOCKINDEXPROC)loadFunction("glGetUniformBlockIndex");
  glGetUniformBufferSizeEXT = (PFNGLGETUNIFORMBUFFERSIZEEXTPROC)loadFunction(
      "glGetUniformBufferSizeEXT");
  glGetUniformIndices = (PFNGLGETUNIFORMINDICESPROC)loadFunction("glGetUniformIndices");
  glGetUniformLocation = (PFNGLGETUNIFORMLOCATIONPROC)loadFunction("glGetUniformLocation");
  glGetUniformLocationARB = (PFNGLGETUNIFORMLOCATIONARBPROC)loadFunction(
      "glGetUniformLocationARB");
  glGetUniformOffsetEXT = (PFNGLGETUNIFORMOFFSETEXTPROC)loadFunction("glGetUniformOffsetEXT");
  glGetUniformSubroutineuiv = (PFNGLGETUNIFORMSUBROUTINEUIVPROC)loadFunction(
      "glGetUniformSubroutineuiv");
  glGetUniformdv = (PFNGLGETUNIFORMDVPROC)loadFunction("glGetUniformdv");
  glGetUniformfv = (PFNGLGETUNIFORMFVPROC)loadFunction("glGetUniformfv");
  glGetUniformfvARB = (PFNGLGETUNIFORMFVARBPROC)loadFunction("glGetUniformfvARB");
  glGetUniformi64vARB = (PFNGLGETUNIFORMI64VARBPROC)loadFunction("glGetUniformi64vARB");
  glGetUniformi64vNV = (PFNGLGETUNIFORMI64VNVPROC)loadFunction("glGetUniformi64vNV");
  glGetUniformiv = (PFNGLGETUNIFORMIVPROC)loadFunction("glGetUniformiv");
  glGetUniformivARB = (PFNGLGETUNIFORMIVARBPROC)loadFunction("glGetUniformivARB");
  glGetUniformui64vARB = (PFNGLGETUNIFORMUI64VARBPROC)loadFunction("glGetUniformui64vARB");
  glGetUniformui64vNV = (PFNGLGETUNIFORMUI64VNVPROC)loadFunction("glGetUniformui64vNV");
  glGetUniformuiv = (PFNGLGETUNIFORMUIVPROC)loadFunction("glGetUniformuiv");
  glGetUniformuivEXT = (PFNGLGETUNIFORMUIVEXTPROC)loadFunction("glGetUniformuivEXT");
  glGetUnsignedBytevEXT = (PFNGLGETUNSIGNEDBYTEVEXTPROC)loadFunction("glGetUnsignedBytevEXT");
  glGetUnsignedBytei_vEXT = (PFNGLGETUNSIGNEDBYTEI_VEXTPROC)loadFunction(
      "glGetUnsignedBytei_vEXT");
  glGetVariantBooleanvEXT = (PFNGLGETVARIANTBOOLEANVEXTPROC)loadFunction(
      "glGetVariantBooleanvEXT");
  glGetVariantFloatvEXT = (PFNGLGETVARIANTFLOATVEXTPROC)loadFunction("glGetVariantFloatvEXT");
  glGetVariantIntegervEXT = (PFNGLGETVARIANTINTEGERVEXTPROC)loadFunction(
      "glGetVariantIntegervEXT");
  glGetVariantPointervEXT = (PFNGLGETVARIANTPOINTERVEXTPROC)loadFunction(
      "glGetVariantPointervEXT");
  glGetVaryingLocationNV = (PFNGLGETVARYINGLOCATIONNVPROC)loadFunction("glGetVaryingLocationNV");
  glGetVertexArrayIndexed64iv = (PFNGLGETVERTEXARRAYINDEXED64IVPROC)loadFunction(
      "glGetVertexArrayIndexed64iv");
  glGetVertexArrayIndexediv = (PFNGLGETVERTEXARRAYINDEXEDIVPROC)loadFunction(
      "glGetVertexArrayIndexediv");
  glGetVertexArrayIntegeri_vEXT = (PFNGLGETVERTEXARRAYINTEGERI_VEXTPROC)loadFunction(
      "glGetVertexArrayIntegeri_vEXT");
  glGetVertexArrayIntegervEXT = (PFNGLGETVERTEXARRAYINTEGERVEXTPROC)loadFunction(
      "glGetVertexArrayIntegervEXT");
  glGetVertexArrayPointeri_vEXT = (PFNGLGETVERTEXARRAYPOINTERI_VEXTPROC)loadFunction(
      "glGetVertexArrayPointeri_vEXT");
  glGetVertexArrayPointervEXT = (PFNGLGETVERTEXARRAYPOINTERVEXTPROC)loadFunction(
      "glGetVertexArrayPointervEXT");
  glGetVertexArrayiv = (PFNGLGETVERTEXARRAYIVPROC)loadFunction("glGetVertexArrayiv");
  glGetVertexAttribIiv = (PFNGLGETVERTEXATTRIBIIVPROC)loadFunction("glGetVertexAttribIiv");
  glGetVertexAttribIivEXT = (PFNGLGETVERTEXATTRIBIIVEXTPROC)loadFunction(
      "glGetVertexAttribIivEXT");
  glGetVertexAttribIuiv = (PFNGLGETVERTEXATTRIBIUIVPROC)loadFunction("glGetVertexAttribIuiv");
  glGetVertexAttribIuivEXT = (PFNGLGETVERTEXATTRIBIUIVEXTPROC)loadFunction(
      "glGetVertexAttribIuivEXT");
  glGetVertexAttribLdv = (PFNGLGETVERTEXATTRIBLDVPROC)loadFunction("glGetVertexAttribLdv");
  glGetVertexAttribLdvEXT = (PFNGLGETVERTEXATTRIBLDVEXTPROC)loadFunction(
      "glGetVertexAttribLdvEXT");
  glGetVertexAttribLi64vNV = (PFNGLGETVERTEXATTRIBLI64VNVPROC)loadFunction(
      "glGetVertexAttribLi64vNV");
  glGetVertexAttribLui64vARB = (PFNGLGETVERTEXATTRIBLUI64VARBPROC)loadFunction(
      "glGetVertexAttribLui64vARB");
  glGetVertexAttribLui64vNV = (PFNGLGETVERTEXATTRIBLUI64VNVPROC)loadFunction(
      "glGetVertexAttribLui64vNV");
  glGetVertexAttribPointerv = (PFNGLGETVERTEXATTRIBPOINTERVPROC)loadFunction(
      "glGetVertexAttribPointerv");
  glGetVertexAttribPointervARB = (PFNGLGETVERTEXATTRIBPOINTERVARBPROC)loadFunction(
      "glGetVertexAttribPointervARB");
  glGetVertexAttribPointervNV = (PFNGLGETVERTEXATTRIBPOINTERVNVPROC)loadFunction(
      "glGetVertexAttribPointervNV");
  glGetVertexAttribdv = (PFNGLGETVERTEXATTRIBDVPROC)loadFunction("glGetVertexAttribdv");
  glGetVertexAttribdvARB = (PFNGLGETVERTEXATTRIBDVARBPROC)loadFunction("glGetVertexAttribdvARB");
  glGetVertexAttribdvNV = (PFNGLGETVERTEXATTRIBDVNVPROC)loadFunction("glGetVertexAttribdvNV");
  glGetVertexAttribfv = (PFNGLGETVERTEXATTRIBFVPROC)loadFunction("glGetVertexAttribfv");
  glGetVertexAttribfvARB = (PFNGLGETVERTEXATTRIBFVARBPROC)loadFunction("glGetVertexAttribfvARB");
  glGetVertexAttribfvNV = (PFNGLGETVERTEXATTRIBFVNVPROC)loadFunction("glGetVertexAttribfvNV");
  glGetVertexAttribiv = (PFNGLGETVERTEXATTRIBIVPROC)loadFunction("glGetVertexAttribiv");
  glGetVertexAttribivARB = (PFNGLGETVERTEXATTRIBIVARBPROC)loadFunction("glGetVertexAttribivARB");
  glGetVertexAttribivNV = (PFNGLGETVERTEXATTRIBIVNVPROC)loadFunction("glGetVertexAttribivNV");
  glGetVideoCaptureStreamdvNV = (PFNGLGETVIDEOCAPTURESTREAMDVNVPROC)loadFunction(
      "glGetVideoCaptureStreamdvNV");
  glGetVideoCaptureStreamfvNV = (PFNGLGETVIDEOCAPTURESTREAMFVNVPROC)loadFunction(
      "glGetVideoCaptureStreamfvNV");
  glGetVideoCaptureStreamivNV = (PFNGLGETVIDEOCAPTURESTREAMIVNVPROC)loadFunction(
      "glGetVideoCaptureStreamivNV");
  glGetVideoCaptureivNV = (PFNGLGETVIDEOCAPTUREIVNVPROC)loadFunction("glGetVideoCaptureivNV");
  glGetVideoi64vNV = (PFNGLGETVIDEOI64VNVPROC)loadFunction("glGetVideoi64vNV");
  glGetVideoivNV = (PFNGLGETVIDEOIVNVPROC)loadFunction("glGetVideoivNV");
  glGetVideoui64vNV = (PFNGLGETVIDEOUI64VNVPROC)loadFunction("glGetVideoui64vNV");
  glGetVideouivNV = (PFNGLGETVIDEOUIVNVPROC)loadFunction("glGetVideouivNV");
  glGetnColorTable = (PFNGLGETNCOLORTABLEPROC)loadFunction("glGetnColorTable");
  glGetnColorTableARB = (PFNGLGETNCOLORTABLEARBPROC)loadFunction("glGetnColorTableARB");
  glGetnCompressedTexImage = (PFNGLGETNCOMPRESSEDTEXIMAGEPROC)loadFunction(
      "glGetnCompressedTexImage");
  glGetnCompressedTexImageARB = (PFNGLGETNCOMPRESSEDTEXIMAGEARBPROC)loadFunction(
      "glGetnCompressedTexImageARB");
  glGetnConvolutionFilter = (PFNGLGETNCONVOLUTIONFILTERPROC)loadFunction(
      "glGetnConvolutionFilter");
  glGetnConvolutionFilterARB = (PFNGLGETNCONVOLUTIONFILTERARBPROC)loadFunction(
      "glGetnConvolutionFilterARB");
  glGetnHistogram = (PFNGLGETNHISTOGRAMPROC)loadFunction("glGetnHistogram");
  glGetnHistogramARB = (PFNGLGETNHISTOGRAMARBPROC)loadFunction("glGetnHistogramARB");
  glGetnMapdv = (PFNGLGETNMAPDVPROC)loadFunction("glGetnMapdv");
  glGetnMapdvARB = (PFNGLGETNMAPDVARBPROC)loadFunction("glGetnMapdvARB");
  glGetnMapfv = (PFNGLGETNMAPFVPROC)loadFunction("glGetnMapfv");
  glGetnMapfvARB = (PFNGLGETNMAPFVARBPROC)loadFunction("glGetnMapfvARB");
  glGetnMapiv = (PFNGLGETNMAPIVPROC)loadFunction("glGetnMapiv");
  glGetnMapivARB = (PFNGLGETNMAPIVARBPROC)loadFunction("glGetnMapivARB");
  glGetnMinmax = (PFNGLGETNMINMAXPROC)loadFunction("glGetnMinmax");
  glGetnMinmaxARB = (PFNGLGETNMINMAXARBPROC)loadFunction("glGetnMinmaxARB");
  glGetnPixelMapfv = (PFNGLGETNPIXELMAPFVPROC)loadFunction("glGetnPixelMapfv");
  glGetnPixelMapfvARB = (PFNGLGETNPIXELMAPFVARBPROC)loadFunction("glGetnPixelMapfvARB");
  glGetnPixelMapuiv = (PFNGLGETNPIXELMAPUIVPROC)loadFunction("glGetnPixelMapuiv");
  glGetnPixelMapuivARB = (PFNGLGETNPIXELMAPUIVARBPROC)loadFunction("glGetnPixelMapuivARB");
  glGetnPixelMapusv = (PFNGLGETNPIXELMAPUSVPROC)loadFunction("glGetnPixelMapusv");
  glGetnPixelMapusvARB = (PFNGLGETNPIXELMAPUSVARBPROC)loadFunction("glGetnPixelMapusvARB");
  glGetnPolygonStipple = (PFNGLGETNPOLYGONSTIPPLEPROC)loadFunction("glGetnPolygonStipple");
  glGetnPolygonStippleARB = (PFNGLGETNPOLYGONSTIPPLEARBPROC)loadFunction(
      "glGetnPolygonStippleARB");
  glGetnSeparableFilter = (PFNGLGETNSEPARABLEFILTERPROC)loadFunction("glGetnSeparableFilter");
  glGetnSeparableFilterARB = (PFNGLGETNSEPARABLEFILTERARBPROC)loadFunction(
      "glGetnSeparableFilterARB");
  glGetnTexImage = (PFNGLGETNTEXIMAGEPROC)loadFunction("glGetnTexImage");
  glGetnTexImageARB = (PFNGLGETNTEXIMAGEARBPROC)loadFunction("glGetnTexImageARB");
  glGetnUniformdv = (PFNGLGETNUNIFORMDVPROC)loadFunction("glGetnUniformdv");
  glGetnUniformdvARB = (PFNGLGETNUNIFORMDVARBPROC)loadFunction("glGetnUniformdvARB");
  glGetnUniformfv = (PFNGLGETNUNIFORMFVPROC)loadFunction("glGetnUniformfv");
  glGetnUniformfvARB = (PFNGLGETNUNIFORMFVARBPROC)loadFunction("glGetnUniformfvARB");
  glGetnUniformfvKHR = (PFNGLGETNUNIFORMFVKHRPROC)loadFunction("glGetnUniformfvKHR");
  glGetnUniformi64vARB = (PFNGLGETNUNIFORMI64VARBPROC)loadFunction("glGetnUniformi64vARB");
  glGetnUniformiv = (PFNGLGETNUNIFORMIVPROC)loadFunction("glGetnUniformiv");
  glGetnUniformivARB = (PFNGLGETNUNIFORMIVARBPROC)loadFunction("glGetnUniformivARB");
  glGetnUniformivKHR = (PFNGLGETNUNIFORMIVKHRPROC)loadFunction("glGetnUniformivKHR");
  glGetnUniformui64vARB = (PFNGLGETNUNIFORMUI64VARBPROC)loadFunction("glGetnUniformui64vARB");
  glGetnUniformuiv = (PFNGLGETNUNIFORMUIVPROC)loadFunction("glGetnUniformuiv");
  glGetnUniformuivARB = (PFNGLGETNUNIFORMUIVARBPROC)loadFunction("glGetnUniformuivARB");
  glGetnUniformuivKHR = (PFNGLGETNUNIFORMUIVKHRPROC)loadFunction("glGetnUniformuivKHR");
  glHint = (PFNGLHINTPROC)loadFunction("glHint");
  glHistogram = (PFNGLHISTOGRAMPROC)loadFunction("glHistogram");
  glHistogramEXT = (PFNGLHISTOGRAMEXTPROC)loadFunction("glHistogramEXT");
  glImportMemoryFdEXT = (PFNGLIMPORTMEMORYFDEXTPROC)loadFunction("glImportMemoryFdEXT");
  glImportMemoryWin32HandleEXT = (PFNGLIMPORTMEMORYWIN32HANDLEEXTPROC)loadFunction(
      "glImportMemoryWin32HandleEXT");
  glImportMemoryWin32NameEXT = (PFNGLIMPORTMEMORYWIN32NAMEEXTPROC)loadFunction(
      "glImportMemoryWin32NameEXT");
  glImportSemaphoreFdEXT = (PFNGLIMPORTSEMAPHOREFDEXTPROC)loadFunction("glImportSemaphoreFdEXT");
  glImportSemaphoreWin32HandleEXT = (PFNGLIMPORTSEMAPHOREWIN32HANDLEEXTPROC)loadFunction(
      "glImportSemaphoreWin32HandleEXT");
  glImportSemaphoreWin32NameEXT = (PFNGLIMPORTSEMAPHOREWIN32NAMEEXTPROC)loadFunction(
      "glImportSemaphoreWin32NameEXT");
  glImportSyncEXT = (PFNGLIMPORTSYNCEXTPROC)loadFunction("glImportSyncEXT");
  glIndexFormatNV = (PFNGLINDEXFORMATNVPROC)loadFunction("glIndexFormatNV");
  glIndexFuncEXT = (PFNGLINDEXFUNCEXTPROC)loadFunction("glIndexFuncEXT");
  glIndexMask = (PFNGLINDEXMASKPROC)loadFunction("glIndexMask");
  glIndexMaterialEXT = (PFNGLINDEXMATERIALEXTPROC)loadFunction("glIndexMaterialEXT");
  glIndexPointer = (PFNGLINDEXPOINTERPROC)loadFunction("glIndexPointer");
  glIndexPointerEXT = (PFNGLINDEXPOINTEREXTPROC)loadFunction("glIndexPointerEXT");
  glIndexd = (PFNGLINDEXDPROC)loadFunction("glIndexd");
  glIndexdv = (PFNGLINDEXDVPROC)loadFunction("glIndexdv");
  glIndexf = (PFNGLINDEXFPROC)loadFunction("glIndexf");
  glIndexfv = (PFNGLINDEXFVPROC)loadFunction("glIndexfv");
  glIndexi = (PFNGLINDEXIPROC)loadFunction("glIndexi");
  glIndexiv = (PFNGLINDEXIVPROC)loadFunction("glIndexiv");
  glIndexs = (PFNGLINDEXSPROC)loadFunction("glIndexs");
  glIndexsv = (PFNGLINDEXSVPROC)loadFunction("glIndexsv");
  glIndexub = (PFNGLINDEXUBPROC)loadFunction("glIndexub");
  glIndexubv = (PFNGLINDEXUBVPROC)loadFunction("glIndexubv");
  glInitNames = (PFNGLINITNAMESPROC)loadFunction("glInitNames");
  glInsertComponentEXT = (PFNGLINSERTCOMPONENTEXTPROC)loadFunction("glInsertComponentEXT");
  glInsertEventMarkerEXT = (PFNGLINSERTEVENTMARKEREXTPROC)loadFunction("glInsertEventMarkerEXT");
  glInterleavedArrays = (PFNGLINTERLEAVEDARRAYSPROC)loadFunction("glInterleavedArrays");
  glInterpolatePathsNV = (PFNGLINTERPOLATEPATHSNVPROC)loadFunction("glInterpolatePathsNV");
  glInvalidateBufferData = (PFNGLINVALIDATEBUFFERDATAPROC)loadFunction("glInvalidateBufferData");
  glInvalidateBufferSubData = (PFNGLINVALIDATEBUFFERSUBDATAPROC)loadFunction(
      "glInvalidateBufferSubData");
  glInvalidateFramebuffer = (PFNGLINVALIDATEFRAMEBUFFERPROC)loadFunction(
      "glInvalidateFramebuffer");
  glInvalidateNamedFramebufferData = (PFNGLINVALIDATENAMEDFRAMEBUFFERDATAPROC)loadFunction(
      "glInvalidateNamedFramebufferData");
  glInvalidateNamedFramebufferSubData = (PFNGLINVALIDATENAMEDFRAMEBUFFERSUBDATAPROC)loadFunction(
      "glInvalidateNamedFramebufferSubData");
  glInvalidateSubFramebuffer = (PFNGLINVALIDATESUBFRAMEBUFFERPROC)loadFunction(
      "glInvalidateSubFramebuffer");
  glInvalidateTexImage = (PFNGLINVALIDATETEXIMAGEPROC)loadFunction("glInvalidateTexImage");
  glInvalidateTexSubImage = (PFNGLINVALIDATETEXSUBIMAGEPROC)loadFunction(
      "glInvalidateTexSubImage");
  glIsBuffer = (PFNGLISBUFFERPROC)loadFunction("glIsBuffer");
  glIsBufferARB = (PFNGLISBUFFERARBPROC)loadFunction("glIsBufferARB");
  glIsBufferResidentNV = (PFNGLISBUFFERRESIDENTNVPROC)loadFunction("glIsBufferResidentNV");
  glIsCommandListNV = (PFNGLISCOMMANDLISTNVPROC)loadFunction("glIsCommandListNV");
  glIsEnabled = (PFNGLISENABLEDPROC)loadFunction("glIsEnabled");
  glIsEnabledIndexedEXT = (PFNGLISENABLEDINDEXEDEXTPROC)loadFunction("glIsEnabledIndexedEXT");
  glIsEnabledi = (PFNGLISENABLEDIPROC)loadFunction("glIsEnabledi");
  glIsFenceAPPLE = (PFNGLISFENCEAPPLEPROC)loadFunction("glIsFenceAPPLE");
  glIsFenceNV = (PFNGLISFENCENVPROC)loadFunction("glIsFenceNV");
  glIsFramebuffer = (PFNGLISFRAMEBUFFERPROC)loadFunction("glIsFramebuffer");
  glIsFramebufferEXT = (PFNGLISFRAMEBUFFEREXTPROC)loadFunction("glIsFramebufferEXT");
  glIsImageHandleResidentARB = (PFNGLISIMAGEHANDLERESIDENTARBPROC)loadFunction(
      "glIsImageHandleResidentARB");
  glIsImageHandleResidentNV = (PFNGLISIMAGEHANDLERESIDENTNVPROC)loadFunction(
      "glIsImageHandleResidentNV");
  glIsList = (PFNGLISLISTPROC)loadFunction("glIsList");
  glIsMemoryObjectEXT = (PFNGLISMEMORYOBJECTEXTPROC)loadFunction("glIsMemoryObjectEXT");
  glIsNameAMD = (PFNGLISNAMEAMDPROC)loadFunction("glIsNameAMD");
  glIsNamedBufferResidentNV = (PFNGLISNAMEDBUFFERRESIDENTNVPROC)loadFunction(
      "glIsNamedBufferResidentNV");
  glIsNamedStringARB = (PFNGLISNAMEDSTRINGARBPROC)loadFunction("glIsNamedStringARB");
  glIsOcclusionQueryNV = (PFNGLISOCCLUSIONQUERYNVPROC)loadFunction("glIsOcclusionQueryNV");
  glIsPathNV = (PFNGLISPATHNVPROC)loadFunction("glIsPathNV");
  glIsPointInFillPathNV = (PFNGLISPOINTINFILLPATHNVPROC)loadFunction("glIsPointInFillPathNV");
  glIsPointInStrokePathNV = (PFNGLISPOINTINSTROKEPATHNVPROC)loadFunction(
      "glIsPointInStrokePathNV");
  glIsProgram = (PFNGLISPROGRAMPROC)loadFunction("glIsProgram");
  glIsProgramARB = (PFNGLISPROGRAMARBPROC)loadFunction("glIsProgramARB");
  glIsProgramNV = (PFNGLISPROGRAMNVPROC)loadFunction("glIsProgramNV");
  glIsProgramPipeline = (PFNGLISPROGRAMPIPELINEPROC)loadFunction("glIsProgramPipeline");
  glIsProgramPipelineEXT = (PFNGLISPROGRAMPIPELINEEXTPROC)loadFunction("glIsProgramPipelineEXT");
  glIsQuery = (PFNGLISQUERYPROC)loadFunction("glIsQuery");
  glIsQueryARB = (PFNGLISQUERYARBPROC)loadFunction("glIsQueryARB");
  glIsRenderbuffer = (PFNGLISRENDERBUFFERPROC)loadFunction("glIsRenderbuffer");
  glIsRenderbufferEXT = (PFNGLISRENDERBUFFEREXTPROC)loadFunction("glIsRenderbufferEXT");
  glIsSemaphoreEXT = (PFNGLISSEMAPHOREEXTPROC)loadFunction("glIsSemaphoreEXT");
  glIsSampler = (PFNGLISSAMPLERPROC)loadFunction("glIsSampler");
  glIsShader = (PFNGLISSHADERPROC)loadFunction("glIsShader");
  glIsStateNV = (PFNGLISSTATENVPROC)loadFunction("glIsStateNV");
  glIsSync = (PFNGLISSYNCPROC)loadFunction("glIsSync");
  glIsTexture = (PFNGLISTEXTUREPROC)loadFunction("glIsTexture");
  glIsTextureEXT = (PFNGLISTEXTUREEXTPROC)loadFunction("glIsTextureEXT");
  glIsTextureHandleResidentARB = (PFNGLISTEXTUREHANDLERESIDENTARBPROC)loadFunction(
      "glIsTextureHandleResidentARB");
  glIsTextureHandleResidentNV = (PFNGLISTEXTUREHANDLERESIDENTNVPROC)loadFunction(
      "glIsTextureHandleResidentNV");
  glIsTransformFeedback = (PFNGLISTRANSFORMFEEDBACKPROC)loadFunction("glIsTransformFeedback");
  glIsTransformFeedbackNV = (PFNGLISTRANSFORMFEEDBACKNVPROC)loadFunction(
      "glIsTransformFeedbackNV");
  glIsVariantEnabledEXT = (PFNGLISVARIANTENABLEDEXTPROC)loadFunction("glIsVariantEnabledEXT");
  glIsVertexArray = (PFNGLISVERTEXARRAYPROC)loadFunction("glIsVertexArray");
  glIsVertexArrayAPPLE = (PFNGLISVERTEXARRAYAPPLEPROC)loadFunction("glIsVertexArrayAPPLE");
  glIsVertexAttribEnabledAPPLE = (PFNGLISVERTEXATTRIBENABLEDAPPLEPROC)loadFunction(
      "glIsVertexAttribEnabledAPPLE");
  glLGPUCopyImageSubDataNVX = (PFNGLLGPUCOPYIMAGESUBDATANVXPROC)loadFunction(
      "glLGPUCopyImageSubDataNVX");
  glLGPUInterlockNVX = (PFNGLLGPUINTERLOCKNVXPROC)loadFunction("glLGPUInterlockNVX");
  glLGPUNamedBufferSubDataNVX = (PFNGLLGPUNAMEDBUFFERSUBDATANVXPROC)loadFunction(
      "glLGPUNamedBufferSubDataNVX");
  glLabelObjectEXT = (PFNGLLABELOBJECTEXTPROC)loadFunction("glLabelObjectEXT");
  glLightModelf = (PFNGLLIGHTMODELFPROC)loadFunction("glLightModelf");
  glLightModelfv = (PFNGLLIGHTMODELFVPROC)loadFunction("glLightModelfv");
  glLightModeli = (PFNGLLIGHTMODELIPROC)loadFunction("glLightModeli");
  glLightModeliv = (PFNGLLIGHTMODELIVPROC)loadFunction("glLightModeliv");
  glLightf = (PFNGLLIGHTFPROC)loadFunction("glLightf");
  glLightfv = (PFNGLLIGHTFVPROC)loadFunction("glLightfv");
  glLighti = (PFNGLLIGHTIPROC)loadFunction("glLighti");
  glLightiv = (PFNGLLIGHTIVPROC)loadFunction("glLightiv");
  glLineStipple = (PFNGLLINESTIPPLEPROC)loadFunction("glLineStipple");
  glLineWidth = (PFNGLLINEWIDTHPROC)loadFunction("glLineWidth");
  glLinkProgram = (PFNGLLINKPROGRAMPROC)loadFunction("glLinkProgram");
  glLinkProgramARB = (PFNGLLINKPROGRAMARBPROC)loadFunction("glLinkProgramARB");
  glListBase = (PFNGLLISTBASEPROC)loadFunction("glListBase");
  glListDrawCommandsStatesClientNV = (PFNGLLISTDRAWCOMMANDSSTATESCLIENTNVPROC)loadFunction(
      "glListDrawCommandsStatesClientNV");
  glLoadIdentity = (PFNGLLOADIDENTITYPROC)loadFunction("glLoadIdentity");
  glLoadMatrixd = (PFNGLLOADMATRIXDPROC)loadFunction("glLoadMatrixd");
  glLoadMatrixf = (PFNGLLOADMATRIXFPROC)loadFunction("glLoadMatrixf");
  glLoadName = (PFNGLLOADNAMEPROC)loadFunction("glLoadName");
  glLoadProgramNV = (PFNGLLOADPROGRAMNVPROC)loadFunction("glLoadProgramNV");
  glLoadTransposeMatrixd = (PFNGLLOADTRANSPOSEMATRIXDPROC)loadFunction("glLoadTransposeMatrixd");
  glLoadTransposeMatrixdARB = (PFNGLLOADTRANSPOSEMATRIXDARBPROC)loadFunction(
      "glLoadTransposeMatrixdARB");
  glLoadTransposeMatrixf = (PFNGLLOADTRANSPOSEMATRIXFPROC)loadFunction("glLoadTransposeMatrixf");
  glLoadTransposeMatrixfARB = (PFNGLLOADTRANSPOSEMATRIXFARBPROC)loadFunction(
      "glLoadTransposeMatrixfARB");
  glLockArraysEXT = (PFNGLLOCKARRAYSEXTPROC)loadFunction("glLockArraysEXT");
  glLogicOp = (PFNGLLOGICOPPROC)loadFunction("glLogicOp");
  glMakeBufferNonResidentNV = (PFNGLMAKEBUFFERNONRESIDENTNVPROC)loadFunction(
      "glMakeBufferNonResidentNV");
  glMakeBufferResidentNV = (PFNGLMAKEBUFFERRESIDENTNVPROC)loadFunction("glMakeBufferResidentNV");
  glMakeImageHandleNonResidentARB = (PFNGLMAKEIMAGEHANDLENONRESIDENTARBPROC)loadFunction(
      "glMakeImageHandleNonResidentARB");
  glMakeImageHandleNonResidentNV = (PFNGLMAKEIMAGEHANDLENONRESIDENTNVPROC)loadFunction(
      "glMakeImageHandleNonResidentNV");
  glMakeImageHandleResidentARB = (PFNGLMAKEIMAGEHANDLERESIDENTARBPROC)loadFunction(
      "glMakeImageHandleResidentARB");
  glMakeImageHandleResidentNV = (PFNGLMAKEIMAGEHANDLERESIDENTNVPROC)loadFunction(
      "glMakeImageHandleResidentNV");
  glMakeNamedBufferNonResidentNV = (PFNGLMAKENAMEDBUFFERNONRESIDENTNVPROC)loadFunction(
      "glMakeNamedBufferNonResidentNV");
  glMakeNamedBufferResidentNV = (PFNGLMAKENAMEDBUFFERRESIDENTNVPROC)loadFunction(
      "glMakeNamedBufferResidentNV");
  glMakeTextureHandleNonResidentARB = (PFNGLMAKETEXTUREHANDLENONRESIDENTARBPROC)loadFunction(
      "glMakeTextureHandleNonResidentARB");
  glMakeTextureHandleNonResidentNV = (PFNGLMAKETEXTUREHANDLENONRESIDENTNVPROC)loadFunction(
      "glMakeTextureHandleNonResidentNV");
  glMakeTextureHandleResidentARB = (PFNGLMAKETEXTUREHANDLERESIDENTARBPROC)loadFunction(
      "glMakeTextureHandleResidentARB");
  glMakeTextureHandleResidentNV = (PFNGLMAKETEXTUREHANDLERESIDENTNVPROC)loadFunction(
      "glMakeTextureHandleResidentNV");
  glMap1d = (PFNGLMAP1DPROC)loadFunction("glMap1d");
  glMap1f = (PFNGLMAP1FPROC)loadFunction("glMap1f");
  glMap2d = (PFNGLMAP2DPROC)loadFunction("glMap2d");
  glMap2f = (PFNGLMAP2FPROC)loadFunction("glMap2f");
  glMapBuffer = (PFNGLMAPBUFFERPROC)loadFunction("glMapBuffer");
  glMapBufferARB = (PFNGLMAPBUFFERARBPROC)loadFunction("glMapBufferARB");
  glMapBufferRange = (PFNGLMAPBUFFERRANGEPROC)loadFunction("glMapBufferRange");
  glMapControlPointsNV = (PFNGLMAPCONTROLPOINTSNVPROC)loadFunction("glMapControlPointsNV");
  glMapGrid1d = (PFNGLMAPGRID1DPROC)loadFunction("glMapGrid1d");
  glMapGrid1f = (PFNGLMAPGRID1FPROC)loadFunction("glMapGrid1f");
  glMapGrid2d = (PFNGLMAPGRID2DPROC)loadFunction("glMapGrid2d");
  glMapGrid2f = (PFNGLMAPGRID2FPROC)loadFunction("glMapGrid2f");
  glMapNamedBuffer = (PFNGLMAPNAMEDBUFFERPROC)loadFunction("glMapNamedBuffer");
  glMapNamedBufferEXT = (PFNGLMAPNAMEDBUFFEREXTPROC)loadFunction("glMapNamedBufferEXT");
  glMapNamedBufferRange = (PFNGLMAPNAMEDBUFFERRANGEPROC)loadFunction("glMapNamedBufferRange");
  glMapNamedBufferRangeEXT = (PFNGLMAPNAMEDBUFFERRANGEEXTPROC)loadFunction(
      "glMapNamedBufferRangeEXT");
  glMapParameterfvNV = (PFNGLMAPPARAMETERFVNVPROC)loadFunction("glMapParameterfvNV");
  glMapParameterivNV = (PFNGLMAPPARAMETERIVNVPROC)loadFunction("glMapParameterivNV");
  glMapTexture2DINTEL = (PFNGLMAPTEXTURE2DINTELPROC)loadFunction("glMapTexture2DINTEL");
  glMapVertexAttrib1dAPPLE = (PFNGLMAPVERTEXATTRIB1DAPPLEPROC)loadFunction(
      "glMapVertexAttrib1dAPPLE");
  glMapVertexAttrib1fAPPLE = (PFNGLMAPVERTEXATTRIB1FAPPLEPROC)loadFunction(
      "glMapVertexAttrib1fAPPLE");
  glMapVertexAttrib2dAPPLE = (PFNGLMAPVERTEXATTRIB2DAPPLEPROC)loadFunction(
      "glMapVertexAttrib2dAPPLE");
  glMapVertexAttrib2fAPPLE = (PFNGLMAPVERTEXATTRIB2FAPPLEPROC)loadFunction(
      "glMapVertexAttrib2fAPPLE");
  glMaterialf = (PFNGLMATERIALFPROC)loadFunction("glMaterialf");
  glMaterialfv = (PFNGLMATERIALFVPROC)loadFunction("glMaterialfv");
  glMateriali = (PFNGLMATERIALIPROC)loadFunction("glMateriali");
  glMaterialiv = (PFNGLMATERIALIVPROC)loadFunction("glMaterialiv");
  glMatrixFrustumEXT = (PFNGLMATRIXFRUSTUMEXTPROC)loadFunction("glMatrixFrustumEXT");
  glMatrixIndexPointerARB = (PFNGLMATRIXINDEXPOINTERARBPROC)loadFunction(
      "glMatrixIndexPointerARB");
  glMatrixIndexubvARB = (PFNGLMATRIXINDEXUBVARBPROC)loadFunction("glMatrixIndexubvARB");
  glMatrixIndexuivARB = (PFNGLMATRIXINDEXUIVARBPROC)loadFunction("glMatrixIndexuivARB");
  glMatrixIndexusvARB = (PFNGLMATRIXINDEXUSVARBPROC)loadFunction("glMatrixIndexusvARB");
  glMatrixLoad3x2fNV = (PFNGLMATRIXLOAD3X2FNVPROC)loadFunction("glMatrixLoad3x2fNV");
  glMatrixLoad3x3fNV = (PFNGLMATRIXLOAD3X3FNVPROC)loadFunction("glMatrixLoad3x3fNV");
  glMatrixLoadIdentityEXT = (PFNGLMATRIXLOADIDENTITYEXTPROC)loadFunction(
      "glMatrixLoadIdentityEXT");
  glMatrixLoadTranspose3x3fNV = (PFNGLMATRIXLOADTRANSPOSE3X3FNVPROC)loadFunction(
      "glMatrixLoadTranspose3x3fNV");
  glMatrixLoadTransposedEXT = (PFNGLMATRIXLOADTRANSPOSEDEXTPROC)loadFunction(
      "glMatrixLoadTransposedEXT");
  glMatrixLoadTransposefEXT = (PFNGLMATRIXLOADTRANSPOSEFEXTPROC)loadFunction(
      "glMatrixLoadTransposefEXT");
  glMatrixLoaddEXT = (PFNGLMATRIXLOADDEXTPROC)loadFunction("glMatrixLoaddEXT");
  glMatrixLoadfEXT = (PFNGLMATRIXLOADFEXTPROC)loadFunction("glMatrixLoadfEXT");
  glMatrixMode = (PFNGLMATRIXMODEPROC)loadFunction("glMatrixMode");
  glMatrixMult3x2fNV = (PFNGLMATRIXMULT3X2FNVPROC)loadFunction("glMatrixMult3x2fNV");
  glMatrixMult3x3fNV = (PFNGLMATRIXMULT3X3FNVPROC)loadFunction("glMatrixMult3x3fNV");
  glMatrixMultTranspose3x3fNV = (PFNGLMATRIXMULTTRANSPOSE3X3FNVPROC)loadFunction(
      "glMatrixMultTranspose3x3fNV");
  glMatrixMultTransposedEXT = (PFNGLMATRIXMULTTRANSPOSEDEXTPROC)loadFunction(
      "glMatrixMultTransposedEXT");
  glMatrixMultTransposefEXT = (PFNGLMATRIXMULTTRANSPOSEFEXTPROC)loadFunction(
      "glMatrixMultTransposefEXT");
  glMatrixMultdEXT = (PFNGLMATRIXMULTDEXTPROC)loadFunction("glMatrixMultdEXT");
  glMatrixMultfEXT = (PFNGLMATRIXMULTFEXTPROC)loadFunction("glMatrixMultfEXT");
  glMatrixOrthoEXT = (PFNGLMATRIXORTHOEXTPROC)loadFunction("glMatrixOrthoEXT");
  glMatrixPopEXT = (PFNGLMATRIXPOPEXTPROC)loadFunction("glMatrixPopEXT");
  glMatrixPushEXT = (PFNGLMATRIXPUSHEXTPROC)loadFunction("glMatrixPushEXT");
  glMatrixRotatedEXT = (PFNGLMATRIXROTATEDEXTPROC)loadFunction("glMatrixRotatedEXT");
  glMatrixRotatefEXT = (PFNGLMATRIXROTATEFEXTPROC)loadFunction("glMatrixRotatefEXT");
  glMatrixScaledEXT = (PFNGLMATRIXSCALEDEXTPROC)loadFunction("glMatrixScaledEXT");
  glMatrixScalefEXT = (PFNGLMATRIXSCALEFEXTPROC)loadFunction("glMatrixScalefEXT");
  glMatrixTranslatedEXT = (PFNGLMATRIXTRANSLATEDEXTPROC)loadFunction("glMatrixTranslatedEXT");
  glMatrixTranslatefEXT = (PFNGLMATRIXTRANSLATEFEXTPROC)loadFunction("glMatrixTranslatefEXT");
  glMaxShaderCompilerThreadsKHR = (PFNGLMAXSHADERCOMPILERTHREADSKHRPROC)loadFunction(
      "glMaxShaderCompilerThreadsKHR");
  glMaxShaderCompilerThreadsARB = (PFNGLMAXSHADERCOMPILERTHREADSARBPROC)loadFunction(
      "glMaxShaderCompilerThreadsARB");
  glMemoryBarrier = (PFNGLMEMORYBARRIERPROC)loadFunction("glMemoryBarrier");
  glMemoryBarrierByRegion = (PFNGLMEMORYBARRIERBYREGIONPROC)loadFunction(
      "glMemoryBarrierByRegion");
  glMemoryBarrierEXT = (PFNGLMEMORYBARRIEREXTPROC)loadFunction("glMemoryBarrierEXT");
  glMemoryObjectParameterivEXT = (PFNGLMEMORYOBJECTPARAMETERIVEXTPROC)loadFunction(
      "glMemoryObjectParameterivEXT");
  glMinSampleShading = (PFNGLMINSAMPLESHADINGPROC)loadFunction("glMinSampleShading");
  glMinSampleShadingARB = (PFNGLMINSAMPLESHADINGARBPROC)loadFunction("glMinSampleShadingARB");
  glMinmax = (PFNGLMINMAXPROC)loadFunction("glMinmax");
  glMinmaxEXT = (PFNGLMINMAXEXTPROC)loadFunction("glMinmaxEXT");
  glMultMatrixd = (PFNGLMULTMATRIXDPROC)loadFunction("glMultMatrixd");
  glMultMatrixf = (PFNGLMULTMATRIXFPROC)loadFunction("glMultMatrixf");
  glMultTransposeMatrixd = (PFNGLMULTTRANSPOSEMATRIXDPROC)loadFunction("glMultTransposeMatrixd");
  glMultTransposeMatrixdARB = (PFNGLMULTTRANSPOSEMATRIXDARBPROC)loadFunction(
      "glMultTransposeMatrixdARB");
  glMultTransposeMatrixf = (PFNGLMULTTRANSPOSEMATRIXFPROC)loadFunction("glMultTransposeMatrixf");
  glMultTransposeMatrixfARB = (PFNGLMULTTRANSPOSEMATRIXFARBPROC)loadFunction(
      "glMultTransposeMatrixfARB");
  glMultiDrawArrays = (PFNGLMULTIDRAWARRAYSPROC)loadFunction("glMultiDrawArrays");
  glMultiDrawArraysEXT = (PFNGLMULTIDRAWARRAYSEXTPROC)loadFunction("glMultiDrawArraysEXT");
  glMultiDrawArraysIndirect = (PFNGLMULTIDRAWARRAYSINDIRECTPROC)loadFunction(
      "glMultiDrawArraysIndirect");
  glMultiDrawArraysIndirectAMD = (PFNGLMULTIDRAWARRAYSINDIRECTAMDPROC)loadFunction(
      "glMultiDrawArraysIndirectAMD");
  glMultiDrawArraysIndirectBindlessCountNV = (PFNGLMULTIDRAWARRAYSINDIRECTBINDLESSCOUNTNVPROC)
      loadFunction("glMultiDrawArraysIndirectBindlessCountNV");
  glMultiDrawArraysIndirectBindlessNV = (PFNGLMULTIDRAWARRAYSINDIRECTBINDLESSNVPROC)loadFunction(
      "glMultiDrawArraysIndirectBindlessNV");
  glMultiDrawArraysIndirectCount = (PFNGLMULTIDRAWARRAYSINDIRECTCOUNTPROC)loadFunction(
      "glMultiDrawArraysIndirectCount");
  glMultiDrawArraysIndirectCountARB = (PFNGLMULTIDRAWARRAYSINDIRECTCOUNTARBPROC)loadFunction(
      "glMultiDrawArraysIndirectCountARB");
  glMultiDrawElementArrayAPPLE = (PFNGLMULTIDRAWELEMENTARRAYAPPLEPROC)loadFunction(
      "glMultiDrawElementArrayAPPLE");
  glMultiDrawElements = (PFNGLMULTIDRAWELEMENTSPROC)loadFunction("glMultiDrawElements");
  glMultiDrawElementsBaseVertex = (PFNGLMULTIDRAWELEMENTSBASEVERTEXPROC)loadFunction(
      "glMultiDrawElementsBaseVertex");
  glMultiDrawElementsEXT = (PFNGLMULTIDRAWELEMENTSEXTPROC)loadFunction("glMultiDrawElementsEXT");
  glMultiDrawElementsIndirect = (PFNGLMULTIDRAWELEMENTSINDIRECTPROC)loadFunction(
      "glMultiDrawElementsIndirect");
  glMultiDrawElementsIndirectAMD = (PFNGLMULTIDRAWELEMENTSINDIRECTAMDPROC)loadFunction(
      "glMultiDrawElementsIndirectAMD");
  glMultiDrawElementsIndirectBindlessCountNV = (PFNGLMULTIDRAWELEMENTSINDIRECTBINDLESSCOUNTNVPROC)
      loadFunction("glMultiDrawElementsIndirectBindlessCountNV");
  glMultiDrawElementsIndirectBindlessNV = (PFNGLMULTIDRAWELEMENTSINDIRECTBINDLESSNVPROC)
      loadFunction("glMultiDrawElementsIndirectBindlessNV");
  glMultiDrawElementsIndirectCount = (PFNGLMULTIDRAWELEMENTSINDIRECTCOUNTPROC)loadFunction(
      "glMultiDrawElementsIndirectCount");
  glMultiDrawElementsIndirectCountARB = (PFNGLMULTIDRAWELEMENTSINDIRECTCOUNTARBPROC)loadFunction(
      "glMultiDrawElementsIndirectCountARB");
  glMultiDrawMeshTasksIndirectNV = (PFNGLMULTIDRAWMESHTASKSINDIRECTNVPROC)loadFunction(
      "glMultiDrawMeshTasksIndirectNV");
  glMultiDrawMeshTasksIndirectCountNV = (PFNGLMULTIDRAWMESHTASKSINDIRECTCOUNTNVPROC)loadFunction(
      "glMultiDrawMeshTasksIndirectCountNV");
  glMultiDrawRangeElementArrayAPPLE = (PFNGLMULTIDRAWRANGEELEMENTARRAYAPPLEPROC)loadFunction(
      "glMultiDrawRangeElementArrayAPPLE");
  glMultiTexBufferEXT = (PFNGLMULTITEXBUFFEREXTPROC)loadFunction("glMultiTexBufferEXT");
  glMultiTexCoord1d = (PFNGLMULTITEXCOORD1DPROC)loadFunction("glMultiTexCoord1d");
  glMultiTexCoord1dARB = (PFNGLMULTITEXCOORD1DARBPROC)loadFunction("glMultiTexCoord1dARB");
  glMultiTexCoord1dv = (PFNGLMULTITEXCOORD1DVPROC)loadFunction("glMultiTexCoord1dv");
  glMultiTexCoord1dvARB = (PFNGLMULTITEXCOORD1DVARBPROC)loadFunction("glMultiTexCoord1dvARB");
  glMultiTexCoord1f = (PFNGLMULTITEXCOORD1FPROC)loadFunction("glMultiTexCoord1f");
  glMultiTexCoord1fARB = (PFNGLMULTITEXCOORD1FARBPROC)loadFunction("glMultiTexCoord1fARB");
  glMultiTexCoord1fv = (PFNGLMULTITEXCOORD1FVPROC)loadFunction("glMultiTexCoord1fv");
  glMultiTexCoord1fvARB = (PFNGLMULTITEXCOORD1FVARBPROC)loadFunction("glMultiTexCoord1fvARB");
  glMultiTexCoord1hNV = (PFNGLMULTITEXCOORD1HNVPROC)loadFunction("glMultiTexCoord1hNV");
  glMultiTexCoord1hvNV = (PFNGLMULTITEXCOORD1HVNVPROC)loadFunction("glMultiTexCoord1hvNV");
  glMultiTexCoord1i = (PFNGLMULTITEXCOORD1IPROC)loadFunction("glMultiTexCoord1i");
  glMultiTexCoord1iARB = (PFNGLMULTITEXCOORD1IARBPROC)loadFunction("glMultiTexCoord1iARB");
  glMultiTexCoord1iv = (PFNGLMULTITEXCOORD1IVPROC)loadFunction("glMultiTexCoord1iv");
  glMultiTexCoord1ivARB = (PFNGLMULTITEXCOORD1IVARBPROC)loadFunction("glMultiTexCoord1ivARB");
  glMultiTexCoord1s = (PFNGLMULTITEXCOORD1SPROC)loadFunction("glMultiTexCoord1s");
  glMultiTexCoord1sARB = (PFNGLMULTITEXCOORD1SARBPROC)loadFunction("glMultiTexCoord1sARB");
  glMultiTexCoord1sv = (PFNGLMULTITEXCOORD1SVPROC)loadFunction("glMultiTexCoord1sv");
  glMultiTexCoord1svARB = (PFNGLMULTITEXCOORD1SVARBPROC)loadFunction("glMultiTexCoord1svARB");
  glMultiTexCoord2d = (PFNGLMULTITEXCOORD2DPROC)loadFunction("glMultiTexCoord2d");
  glMultiTexCoord2dARB = (PFNGLMULTITEXCOORD2DARBPROC)loadFunction("glMultiTexCoord2dARB");
  glMultiTexCoord2dv = (PFNGLMULTITEXCOORD2DVPROC)loadFunction("glMultiTexCoord2dv");
  glMultiTexCoord2dvARB = (PFNGLMULTITEXCOORD2DVARBPROC)loadFunction("glMultiTexCoord2dvARB");
  glMultiTexCoord2f = (PFNGLMULTITEXCOORD2FPROC)loadFunction("glMultiTexCoord2f");
  glMultiTexCoord2fARB = (PFNGLMULTITEXCOORD2FARBPROC)loadFunction("glMultiTexCoord2fARB");
  glMultiTexCoord2fv = (PFNGLMULTITEXCOORD2FVPROC)loadFunction("glMultiTexCoord2fv");
  glMultiTexCoord2fvARB = (PFNGLMULTITEXCOORD2FVARBPROC)loadFunction("glMultiTexCoord2fvARB");
  glMultiTexCoord2hNV = (PFNGLMULTITEXCOORD2HNVPROC)loadFunction("glMultiTexCoord2hNV");
  glMultiTexCoord2hvNV = (PFNGLMULTITEXCOORD2HVNVPROC)loadFunction("glMultiTexCoord2hvNV");
  glMultiTexCoord2i = (PFNGLMULTITEXCOORD2IPROC)loadFunction("glMultiTexCoord2i");
  glMultiTexCoord2iARB = (PFNGLMULTITEXCOORD2IARBPROC)loadFunction("glMultiTexCoord2iARB");
  glMultiTexCoord2iv = (PFNGLMULTITEXCOORD2IVPROC)loadFunction("glMultiTexCoord2iv");
  glMultiTexCoord2ivARB = (PFNGLMULTITEXCOORD2IVARBPROC)loadFunction("glMultiTexCoord2ivARB");
  glMultiTexCoord2s = (PFNGLMULTITEXCOORD2SPROC)loadFunction("glMultiTexCoord2s");
  glMultiTexCoord2sARB = (PFNGLMULTITEXCOORD2SARBPROC)loadFunction("glMultiTexCoord2sARB");
  glMultiTexCoord2sv = (PFNGLMULTITEXCOORD2SVPROC)loadFunction("glMultiTexCoord2sv");
  glMultiTexCoord2svARB = (PFNGLMULTITEXCOORD2SVARBPROC)loadFunction("glMultiTexCoord2svARB");
  glMultiTexCoord3d = (PFNGLMULTITEXCOORD3DPROC)loadFunction("glMultiTexCoord3d");
  glMultiTexCoord3dARB = (PFNGLMULTITEXCOORD3DARBPROC)loadFunction("glMultiTexCoord3dARB");
  glMultiTexCoord3dv = (PFNGLMULTITEXCOORD3DVPROC)loadFunction("glMultiTexCoord3dv");
  glMultiTexCoord3dvARB = (PFNGLMULTITEXCOORD3DVARBPROC)loadFunction("glMultiTexCoord3dvARB");
  glMultiTexCoord3f = (PFNGLMULTITEXCOORD3FPROC)loadFunction("glMultiTexCoord3f");
  glMultiTexCoord3fARB = (PFNGLMULTITEXCOORD3FARBPROC)loadFunction("glMultiTexCoord3fARB");
  glMultiTexCoord3fv = (PFNGLMULTITEXCOORD3FVPROC)loadFunction("glMultiTexCoord3fv");
  glMultiTexCoord3fvARB = (PFNGLMULTITEXCOORD3FVARBPROC)loadFunction("glMultiTexCoord3fvARB");
  glMultiTexCoord3hNV = (PFNGLMULTITEXCOORD3HNVPROC)loadFunction("glMultiTexCoord3hNV");
  glMultiTexCoord3hvNV = (PFNGLMULTITEXCOORD3HVNVPROC)loadFunction("glMultiTexCoord3hvNV");
  glMultiTexCoord3i = (PFNGLMULTITEXCOORD3IPROC)loadFunction("glMultiTexCoord3i");
  glMultiTexCoord3iARB = (PFNGLMULTITEXCOORD3IARBPROC)loadFunction("glMultiTexCoord3iARB");
  glMultiTexCoord3iv = (PFNGLMULTITEXCOORD3IVPROC)loadFunction("glMultiTexCoord3iv");
  glMultiTexCoord3ivARB = (PFNGLMULTITEXCOORD3IVARBPROC)loadFunction("glMultiTexCoord3ivARB");
  glMultiTexCoord3s = (PFNGLMULTITEXCOORD3SPROC)loadFunction("glMultiTexCoord3s");
  glMultiTexCoord3sARB = (PFNGLMULTITEXCOORD3SARBPROC)loadFunction("glMultiTexCoord3sARB");
  glMultiTexCoord3sv = (PFNGLMULTITEXCOORD3SVPROC)loadFunction("glMultiTexCoord3sv");
  glMultiTexCoord3svARB = (PFNGLMULTITEXCOORD3SVARBPROC)loadFunction("glMultiTexCoord3svARB");
  glMultiTexCoord4d = (PFNGLMULTITEXCOORD4DPROC)loadFunction("glMultiTexCoord4d");
  glMultiTexCoord4dARB = (PFNGLMULTITEXCOORD4DARBPROC)loadFunction("glMultiTexCoord4dARB");
  glMultiTexCoord4dv = (PFNGLMULTITEXCOORD4DVPROC)loadFunction("glMultiTexCoord4dv");
  glMultiTexCoord4dvARB = (PFNGLMULTITEXCOORD4DVARBPROC)loadFunction("glMultiTexCoord4dvARB");
  glMultiTexCoord4f = (PFNGLMULTITEXCOORD4FPROC)loadFunction("glMultiTexCoord4f");
  glMultiTexCoord4fARB = (PFNGLMULTITEXCOORD4FARBPROC)loadFunction("glMultiTexCoord4fARB");
  glMultiTexCoord4fv = (PFNGLMULTITEXCOORD4FVPROC)loadFunction("glMultiTexCoord4fv");
  glMultiTexCoord4fvARB = (PFNGLMULTITEXCOORD4FVARBPROC)loadFunction("glMultiTexCoord4fvARB");
  glMultiTexCoord4hNV = (PFNGLMULTITEXCOORD4HNVPROC)loadFunction("glMultiTexCoord4hNV");
  glMultiTexCoord4hvNV = (PFNGLMULTITEXCOORD4HVNVPROC)loadFunction("glMultiTexCoord4hvNV");
  glMultiTexCoord4i = (PFNGLMULTITEXCOORD4IPROC)loadFunction("glMultiTexCoord4i");
  glMultiTexCoord4iARB = (PFNGLMULTITEXCOORD4IARBPROC)loadFunction("glMultiTexCoord4iARB");
  glMultiTexCoord4iv = (PFNGLMULTITEXCOORD4IVPROC)loadFunction("glMultiTexCoord4iv");
  glMultiTexCoord4ivARB = (PFNGLMULTITEXCOORD4IVARBPROC)loadFunction("glMultiTexCoord4ivARB");
  glMultiTexCoord4s = (PFNGLMULTITEXCOORD4SPROC)loadFunction("glMultiTexCoord4s");
  glMultiTexCoord4sARB = (PFNGLMULTITEXCOORD4SARBPROC)loadFunction("glMultiTexCoord4sARB");
  glMultiTexCoord4sv = (PFNGLMULTITEXCOORD4SVPROC)loadFunction("glMultiTexCoord4sv");
  glMultiTexCoord4svARB = (PFNGLMULTITEXCOORD4SVARBPROC)loadFunction("glMultiTexCoord4svARB");
  glMultiTexCoordP1ui = (PFNGLMULTITEXCOORDP1UIPROC)loadFunction("glMultiTexCoordP1ui");
  glMultiTexCoordP1uiv = (PFNGLMULTITEXCOORDP1UIVPROC)loadFunction("glMultiTexCoordP1uiv");
  glMultiTexCoordP2ui = (PFNGLMULTITEXCOORDP2UIPROC)loadFunction("glMultiTexCoordP2ui");
  glMultiTexCoordP2uiv = (PFNGLMULTITEXCOORDP2UIVPROC)loadFunction("glMultiTexCoordP2uiv");
  glMultiTexCoordP3ui = (PFNGLMULTITEXCOORDP3UIPROC)loadFunction("glMultiTexCoordP3ui");
  glMultiTexCoordP3uiv = (PFNGLMULTITEXCOORDP3UIVPROC)loadFunction("glMultiTexCoordP3uiv");
  glMultiTexCoordP4ui = (PFNGLMULTITEXCOORDP4UIPROC)loadFunction("glMultiTexCoordP4ui");
  glMultiTexCoordP4uiv = (PFNGLMULTITEXCOORDP4UIVPROC)loadFunction("glMultiTexCoordP4uiv");
  glMultiTexCoordPointerEXT = (PFNGLMULTITEXCOORDPOINTEREXTPROC)loadFunction(
      "glMultiTexCoordPointerEXT");
  glMultiTexEnvfEXT = (PFNGLMULTITEXENVFEXTPROC)loadFunction("glMultiTexEnvfEXT");
  glMultiTexEnvfvEXT = (PFNGLMULTITEXENVFVEXTPROC)loadFunction("glMultiTexEnvfvEXT");
  glMultiTexEnviEXT = (PFNGLMULTITEXENVIEXTPROC)loadFunction("glMultiTexEnviEXT");
  glMultiTexEnvivEXT = (PFNGLMULTITEXENVIVEXTPROC)loadFunction("glMultiTexEnvivEXT");
  glMultiTexGendEXT = (PFNGLMULTITEXGENDEXTPROC)loadFunction("glMultiTexGendEXT");
  glMultiTexGendvEXT = (PFNGLMULTITEXGENDVEXTPROC)loadFunction("glMultiTexGendvEXT");
  glMultiTexGenfEXT = (PFNGLMULTITEXGENFEXTPROC)loadFunction("glMultiTexGenfEXT");
  glMultiTexGenfvEXT = (PFNGLMULTITEXGENFVEXTPROC)loadFunction("glMultiTexGenfvEXT");
  glMultiTexGeniEXT = (PFNGLMULTITEXGENIEXTPROC)loadFunction("glMultiTexGeniEXT");
  glMultiTexGenivEXT = (PFNGLMULTITEXGENIVEXTPROC)loadFunction("glMultiTexGenivEXT");
  glMultiTexImage1DEXT = (PFNGLMULTITEXIMAGE1DEXTPROC)loadFunction("glMultiTexImage1DEXT");
  glMultiTexImage2DEXT = (PFNGLMULTITEXIMAGE2DEXTPROC)loadFunction("glMultiTexImage2DEXT");
  glMultiTexImage3DEXT = (PFNGLMULTITEXIMAGE3DEXTPROC)loadFunction("glMultiTexImage3DEXT");
  glMultiTexParameterIivEXT = (PFNGLMULTITEXPARAMETERIIVEXTPROC)loadFunction(
      "glMultiTexParameterIivEXT");
  glMultiTexParameterIuivEXT = (PFNGLMULTITEXPARAMETERIUIVEXTPROC)loadFunction(
      "glMultiTexParameterIuivEXT");
  glMultiTexParameterfEXT = (PFNGLMULTITEXPARAMETERFEXTPROC)loadFunction(
      "glMultiTexParameterfEXT");
  glMultiTexParameterfvEXT = (PFNGLMULTITEXPARAMETERFVEXTPROC)loadFunction(
      "glMultiTexParameterfvEXT");
  glMultiTexParameteriEXT = (PFNGLMULTITEXPARAMETERIEXTPROC)loadFunction(
      "glMultiTexParameteriEXT");
  glMultiTexParameterivEXT = (PFNGLMULTITEXPARAMETERIVEXTPROC)loadFunction(
      "glMultiTexParameterivEXT");
  glMultiTexRenderbufferEXT = (PFNGLMULTITEXRENDERBUFFEREXTPROC)loadFunction(
      "glMultiTexRenderbufferEXT");
  glMultiTexSubImage1DEXT = (PFNGLMULTITEXSUBIMAGE1DEXTPROC)loadFunction(
      "glMultiTexSubImage1DEXT");
  glMultiTexSubImage2DEXT = (PFNGLMULTITEXSUBIMAGE2DEXTPROC)loadFunction(
      "glMultiTexSubImage2DEXT");
  glMultiTexSubImage3DEXT = (PFNGLMULTITEXSUBIMAGE3DEXTPROC)loadFunction(
      "glMultiTexSubImage3DEXT");
  glMulticastBarrierNV = (PFNGLMULTICASTBARRIERNVPROC)loadFunction("glMulticastBarrierNV");
  glMulticastBlitFramebufferNV = (PFNGLMULTICASTBLITFRAMEBUFFERNVPROC)loadFunction(
      "glMulticastBlitFramebufferNV");
  glMulticastBufferSubDataNV = (PFNGLMULTICASTBUFFERSUBDATANVPROC)loadFunction(
      "glMulticastBufferSubDataNV");
  glMulticastCopyBufferSubDataNV = (PFNGLMULTICASTCOPYBUFFERSUBDATANVPROC)loadFunction(
      "glMulticastCopyBufferSubDataNV");
  glMulticastCopyImageSubDataNV = (PFNGLMULTICASTCOPYIMAGESUBDATANVPROC)loadFunction(
      "glMulticastCopyImageSubDataNV");
  glMulticastFramebufferSampleLocationsfvNV = (PFNGLMULTICASTFRAMEBUFFERSAMPLELOCATIONSFVNVPROC)
      loadFunction("glMulticastFramebufferSampleLocationsfvNV");
  glMulticastGetQueryObjecti64vNV = (PFNGLMULTICASTGETQUERYOBJECTI64VNVPROC)loadFunction(
      "glMulticastGetQueryObjecti64vNV");
  glMulticastGetQueryObjectivNV = (PFNGLMULTICASTGETQUERYOBJECTIVNVPROC)loadFunction(
      "glMulticastGetQueryObjectivNV");
  glMulticastGetQueryObjectui64vNV = (PFNGLMULTICASTGETQUERYOBJECTUI64VNVPROC)loadFunction(
      "glMulticastGetQueryObjectui64vNV");
  glMulticastGetQueryObjectuivNV = (PFNGLMULTICASTGETQUERYOBJECTUIVNVPROC)loadFunction(
      "glMulticastGetQueryObjectuivNV");
  glMulticastScissorArrayvNVX = (PFNGLMULTICASTSCISSORARRAYVNVXPROC)loadFunction(
      "glMulticastScissorArrayvNVX");
  glMulticastViewportArrayvNVX = (PFNGLMULTICASTVIEWPORTARRAYVNVXPROC)loadFunction(
      "glMulticastViewportArrayvNVX");
  glMulticastViewportPositionWScaleNVX = (PFNGLMULTICASTVIEWPORTPOSITIONWSCALENVXPROC)loadFunction(
      "glMulticastViewportPositionWScaleNVX");
  glMulticastWaitSyncNV = (PFNGLMULTICASTWAITSYNCNVPROC)loadFunction("glMulticastWaitSyncNV");
  glNamedBufferAttachMemoryNV = (PFNGLNAMEDBUFFERATTACHMEMORYNVPROC)loadFunction(
      "glNamedBufferAttachMemoryNV");
  glNamedBufferData = (PFNGLNAMEDBUFFERDATAPROC)loadFunction("glNamedBufferData");
  glNamedBufferDataEXT = (PFNGLNAMEDBUFFERDATAEXTPROC)loadFunction("glNamedBufferDataEXT");
  glNamedBufferPageCommitmentARB = (PFNGLNAMEDBUFFERPAGECOMMITMENTARBPROC)loadFunction(
      "glNamedBufferPageCommitmentARB");
  glNamedBufferPageCommitmentEXT = (PFNGLNAMEDBUFFERPAGECOMMITMENTEXTPROC)loadFunction(
      "glNamedBufferPageCommitmentEXT");
  glNamedBufferPageCommitmentMemNV = (PFNGLNAMEDBUFFERPAGECOMMITMENTMEMNVPROC)loadFunction(
      "glNamedBufferPageCommitmentMemNV");
  glNamedBufferStorage = (PFNGLNAMEDBUFFERSTORAGEPROC)loadFunction("glNamedBufferStorage");
  glNamedBufferStorageExternalEXT = (PFNGLNAMEDBUFFERSTORAGEEXTERNALEXTPROC)loadFunction(
      "glNamedBufferStorageExternalEXT");
  glNamedBufferStorageEXT = (PFNGLNAMEDBUFFERSTORAGEEXTPROC)loadFunction(
      "glNamedBufferStorageEXT");
  glNamedBufferStorageMemEXT = (PFNGLNAMEDBUFFERSTORAGEMEMEXTPROC)loadFunction(
      "glNamedBufferStorageMemEXT");
  glNamedBufferSubData = (PFNGLNAMEDBUFFERSUBDATAPROC)loadFunction("glNamedBufferSubData");
  glNamedBufferSubDataEXT = (PFNGLNAMEDBUFFERSUBDATAEXTPROC)loadFunction(
      "glNamedBufferSubDataEXT");
  glNamedCopyBufferSubDataEXT = (PFNGLNAMEDCOPYBUFFERSUBDATAEXTPROC)loadFunction(
      "glNamedCopyBufferSubDataEXT");
  glNamedFramebufferDrawBuffer = (PFNGLNAMEDFRAMEBUFFERDRAWBUFFERPROC)loadFunction(
      "glNamedFramebufferDrawBuffer");
  glNamedFramebufferDrawBuffers = (PFNGLNAMEDFRAMEBUFFERDRAWBUFFERSPROC)loadFunction(
      "glNamedFramebufferDrawBuffers");
  glNamedFramebufferParameteri = (PFNGLNAMEDFRAMEBUFFERPARAMETERIPROC)loadFunction(
      "glNamedFramebufferParameteri");
  glNamedFramebufferParameteriEXT = (PFNGLNAMEDFRAMEBUFFERPARAMETERIEXTPROC)loadFunction(
      "glNamedFramebufferParameteriEXT");
  glNamedFramebufferReadBuffer = (PFNGLNAMEDFRAMEBUFFERREADBUFFERPROC)loadFunction(
      "glNamedFramebufferReadBuffer");
  glNamedFramebufferRenderbuffer = (PFNGLNAMEDFRAMEBUFFERRENDERBUFFERPROC)loadFunction(
      "glNamedFramebufferRenderbuffer");
  glNamedFramebufferRenderbufferEXT = (PFNGLNAMEDFRAMEBUFFERRENDERBUFFEREXTPROC)loadFunction(
      "glNamedFramebufferRenderbufferEXT");
  glNamedFramebufferSampleLocationsfvARB = (PFNGLNAMEDFRAMEBUFFERSAMPLELOCATIONSFVARBPROC)
      loadFunction("glNamedFramebufferSampleLocationsfvARB");
  glNamedFramebufferSampleLocationsfvNV = (PFNGLNAMEDFRAMEBUFFERSAMPLELOCATIONSFVNVPROC)
      loadFunction("glNamedFramebufferSampleLocationsfvNV");
  glNamedFramebufferTexture = (PFNGLNAMEDFRAMEBUFFERTEXTUREPROC)loadFunction(
      "glNamedFramebufferTexture");
  glNamedFramebufferSamplePositionsfvAMD = (PFNGLNAMEDFRAMEBUFFERSAMPLEPOSITIONSFVAMDPROC)
      loadFunction("glNamedFramebufferSamplePositionsfvAMD");
  glNamedFramebufferTexture1DEXT = (PFNGLNAMEDFRAMEBUFFERTEXTURE1DEXTPROC)loadFunction(
      "glNamedFramebufferTexture1DEXT");
  glNamedFramebufferTexture2DEXT = (PFNGLNAMEDFRAMEBUFFERTEXTURE2DEXTPROC)loadFunction(
      "glNamedFramebufferTexture2DEXT");
  glNamedFramebufferTexture3DEXT = (PFNGLNAMEDFRAMEBUFFERTEXTURE3DEXTPROC)loadFunction(
      "glNamedFramebufferTexture3DEXT");
  glNamedFramebufferTextureEXT = (PFNGLNAMEDFRAMEBUFFERTEXTUREEXTPROC)loadFunction(
      "glNamedFramebufferTextureEXT");
  glNamedFramebufferTextureFaceEXT = (PFNGLNAMEDFRAMEBUFFERTEXTUREFACEEXTPROC)loadFunction(
      "glNamedFramebufferTextureFaceEXT");
  glNamedFramebufferTextureLayer = (PFNGLNAMEDFRAMEBUFFERTEXTURELAYERPROC)loadFunction(
      "glNamedFramebufferTextureLayer");
  glNamedFramebufferTextureLayerEXT = (PFNGLNAMEDFRAMEBUFFERTEXTURELAYEREXTPROC)loadFunction(
      "glNamedFramebufferTextureLayerEXT");
  glNamedProgramLocalParameter4dEXT = (PFNGLNAMEDPROGRAMLOCALPARAMETER4DEXTPROC)loadFunction(
      "glNamedProgramLocalParameter4dEXT");
  glNamedProgramLocalParameter4dvEXT = (PFNGLNAMEDPROGRAMLOCALPARAMETER4DVEXTPROC)loadFunction(
      "glNamedProgramLocalParameter4dvEXT");
  glNamedProgramLocalParameter4fEXT = (PFNGLNAMEDPROGRAMLOCALPARAMETER4FEXTPROC)loadFunction(
      "glNamedProgramLocalParameter4fEXT");
  glNamedProgramLocalParameter4fvEXT = (PFNGLNAMEDPROGRAMLOCALPARAMETER4FVEXTPROC)loadFunction(
      "glNamedProgramLocalParameter4fvEXT");
  glNamedProgramLocalParameterI4iEXT = (PFNGLNAMEDPROGRAMLOCALPARAMETERI4IEXTPROC)loadFunction(
      "glNamedProgramLocalParameterI4iEXT");
  glNamedProgramLocalParameterI4ivEXT = (PFNGLNAMEDPROGRAMLOCALPARAMETERI4IVEXTPROC)loadFunction(
      "glNamedProgramLocalParameterI4ivEXT");
  glNamedProgramLocalParameterI4uiEXT = (PFNGLNAMEDPROGRAMLOCALPARAMETERI4UIEXTPROC)loadFunction(
      "glNamedProgramLocalParameterI4uiEXT");
  glNamedProgramLocalParameterI4uivEXT = (PFNGLNAMEDPROGRAMLOCALPARAMETERI4UIVEXTPROC)loadFunction(
      "glNamedProgramLocalParameterI4uivEXT");
  glNamedProgramLocalParameters4fvEXT = (PFNGLNAMEDPROGRAMLOCALPARAMETERS4FVEXTPROC)loadFunction(
      "glNamedProgramLocalParameters4fvEXT");
  glNamedProgramLocalParametersI4ivEXT = (PFNGLNAMEDPROGRAMLOCALPARAMETERSI4IVEXTPROC)loadFunction(
      "glNamedProgramLocalParametersI4ivEXT");
  glNamedProgramLocalParametersI4uivEXT = (PFNGLNAMEDPROGRAMLOCALPARAMETERSI4UIVEXTPROC)
      loadFunction("glNamedProgramLocalParametersI4uivEXT");
  glNamedProgramStringEXT = (PFNGLNAMEDPROGRAMSTRINGEXTPROC)loadFunction(
      "glNamedProgramStringEXT");
  glNamedRenderbufferStorage = (PFNGLNAMEDRENDERBUFFERSTORAGEPROC)loadFunction(
      "glNamedRenderbufferStorage");
  glNamedRenderbufferStorageEXT = (PFNGLNAMEDRENDERBUFFERSTORAGEEXTPROC)loadFunction(
      "glNamedRenderbufferStorageEXT");
  glNamedRenderbufferStorageMultisample = (PFNGLNAMEDRENDERBUFFERSTORAGEMULTISAMPLEPROC)
      loadFunction("glNamedRenderbufferStorageMultisample");
  glNamedRenderbufferStorageMultisampleAdvancedAMD =
      (PFNGLNAMEDRENDERBUFFERSTORAGEMULTISAMPLEADVANCEDAMDPROC)loadFunction(
          "glNamedRenderbufferStorageMultisampleAdvancedAMD");
  glNamedRenderbufferStorageMultisampleCoverageEXT =
      (PFNGLNAMEDRENDERBUFFERSTORAGEMULTISAMPLECOVERAGEEXTPROC)loadFunction(
          "glNamedRenderbufferStorageMultisampleCoverageEXT");
  glNamedRenderbufferStorageMultisampleEXT = (PFNGLNAMEDRENDERBUFFERSTORAGEMULTISAMPLEEXTPROC)
      loadFunction("glNamedRenderbufferStorageMultisampleEXT");
  glNamedStringARB = (PFNGLNAMEDSTRINGARBPROC)loadFunction("glNamedStringARB");
  glNewList = (PFNGLNEWLISTPROC)loadFunction("glNewList");
  glNormal3b = (PFNGLNORMAL3BPROC)loadFunction("glNormal3b");
  glNormal3bv = (PFNGLNORMAL3BVPROC)loadFunction("glNormal3bv");
  glNormal3d = (PFNGLNORMAL3DPROC)loadFunction("glNormal3d");
  glNormal3dv = (PFNGLNORMAL3DVPROC)loadFunction("glNormal3dv");
  glNormal3f = (PFNGLNORMAL3FPROC)loadFunction("glNormal3f");
  glNormal3fv = (PFNGLNORMAL3FVPROC)loadFunction("glNormal3fv");
  glNormal3hNV = (PFNGLNORMAL3HNVPROC)loadFunction("glNormal3hNV");
  glNormal3hvNV = (PFNGLNORMAL3HVNVPROC)loadFunction("glNormal3hvNV");
  glNormal3i = (PFNGLNORMAL3IPROC)loadFunction("glNormal3i");
  glNormal3iv = (PFNGLNORMAL3IVPROC)loadFunction("glNormal3iv");
  glNormal3s = (PFNGLNORMAL3SPROC)loadFunction("glNormal3s");
  glNormal3sv = (PFNGLNORMAL3SVPROC)loadFunction("glNormal3sv");
  glNormalFormatNV = (PFNGLNORMALFORMATNVPROC)loadFunction("glNormalFormatNV");
  glNormalP3ui = (PFNGLNORMALP3UIPROC)loadFunction("glNormalP3ui");
  glNormalP3uiv = (PFNGLNORMALP3UIVPROC)loadFunction("glNormalP3uiv");
  glNormalPointer = (PFNGLNORMALPOINTERPROC)loadFunction("glNormalPointer");
  glNormalPointerEXT = (PFNGLNORMALPOINTEREXTPROC)loadFunction("glNormalPointerEXT");
  glNormalPointervINTEL = (PFNGLNORMALPOINTERVINTELPROC)loadFunction("glNormalPointervINTEL");
  glObjectLabel = (PFNGLOBJECTLABELPROC)loadFunction("glObjectLabel");
  glObjectLabelKHR = (PFNGLOBJECTLABELKHRPROC)loadFunction("glObjectLabelKHR");
  glObjectPtrLabel = (PFNGLOBJECTPTRLABELPROC)loadFunction("glObjectPtrLabel");
  glObjectPtrLabelKHR = (PFNGLOBJECTPTRLABELKHRPROC)loadFunction("glObjectPtrLabelKHR");
  glObjectPurgeableAPPLE = (PFNGLOBJECTPURGEABLEAPPLEPROC)loadFunction("glObjectPurgeableAPPLE");
  glObjectUnpurgeableAPPLE = (PFNGLOBJECTUNPURGEABLEAPPLEPROC)loadFunction(
      "glObjectUnpurgeableAPPLE");
  glOrtho = (PFNGLORTHOPROC)loadFunction("glOrtho");
  glPassThrough = (PFNGLPASSTHROUGHPROC)loadFunction("glPassThrough");
  glPatchParameterfv = (PFNGLPATCHPARAMETERFVPROC)loadFunction("glPatchParameterfv");
  glPatchParameteri = (PFNGLPATCHPARAMETERIPROC)loadFunction("glPatchParameteri");
  glPathColorGenNV = (PFNGLPATHCOLORGENNVPROC)loadFunction("glPathColorGenNV");
  glPathCommandsNV = (PFNGLPATHCOMMANDSNVPROC)loadFunction("glPathCommandsNV");
  glPathCoordsNV = (PFNGLPATHCOORDSNVPROC)loadFunction("glPathCoordsNV");
  glPathCoverDepthFuncNV = (PFNGLPATHCOVERDEPTHFUNCNVPROC)loadFunction("glPathCoverDepthFuncNV");
  glPathDashArrayNV = (PFNGLPATHDASHARRAYNVPROC)loadFunction("glPathDashArrayNV");
  glPathFogGenNV = (PFNGLPATHFOGGENNVPROC)loadFunction("glPathFogGenNV");
  glPathGlyphIndexArrayNV = (PFNGLPATHGLYPHINDEXARRAYNVPROC)loadFunction(
      "glPathGlyphIndexArrayNV");
  glPathGlyphIndexRangeNV = (PFNGLPATHGLYPHINDEXRANGENVPROC)loadFunction(
      "glPathGlyphIndexRangeNV");
  glPathGlyphRangeNV = (PFNGLPATHGLYPHRANGENVPROC)loadFunction("glPathGlyphRangeNV");
  glPathGlyphsNV = (PFNGLPATHGLYPHSNVPROC)loadFunction("glPathGlyphsNV");
  glPathMemoryGlyphIndexArrayNV = (PFNGLPATHMEMORYGLYPHINDEXARRAYNVPROC)loadFunction(
      "glPathMemoryGlyphIndexArrayNV");
  glPathParameterfNV = (PFNGLPATHPARAMETERFNVPROC)loadFunction("glPathParameterfNV");
  glPathParameterfvNV = (PFNGLPATHPARAMETERFVNVPROC)loadFunction("glPathParameterfvNV");
  glPathParameteriNV = (PFNGLPATHPARAMETERINVPROC)loadFunction("glPathParameteriNV");
  glPathParameterivNV = (PFNGLPATHPARAMETERIVNVPROC)loadFunction("glPathParameterivNV");
  glPathStencilDepthOffsetNV = (PFNGLPATHSTENCILDEPTHOFFSETNVPROC)loadFunction(
      "glPathStencilDepthOffsetNV");
  glPathStencilFuncNV = (PFNGLPATHSTENCILFUNCNVPROC)loadFunction("glPathStencilFuncNV");
  glPathStringNV = (PFNGLPATHSTRINGNVPROC)loadFunction("glPathStringNV");
  glPathSubCommandsNV = (PFNGLPATHSUBCOMMANDSNVPROC)loadFunction("glPathSubCommandsNV");
  glPathSubCoordsNV = (PFNGLPATHSUBCOORDSNVPROC)loadFunction("glPathSubCoordsNV");
  glPathTexGenNV = (PFNGLPATHTEXGENNVPROC)loadFunction("glPathTexGenNV");
  glPauseTransformFeedback = (PFNGLPAUSETRANSFORMFEEDBACKPROC)loadFunction(
      "glPauseTransformFeedback");
  glPauseTransformFeedbackNV = (PFNGLPAUSETRANSFORMFEEDBACKNVPROC)loadFunction(
      "glPauseTransformFeedbackNV");
  glPixelDataRangeNV = (PFNGLPIXELDATARANGENVPROC)loadFunction("glPixelDataRangeNV");
  glPixelMapfv = (PFNGLPIXELMAPFVPROC)loadFunction("glPixelMapfv");
  glPixelMapuiv = (PFNGLPIXELMAPUIVPROC)loadFunction("glPixelMapuiv");
  glPixelMapusv = (PFNGLPIXELMAPUSVPROC)loadFunction("glPixelMapusv");
  glPixelStoref = (PFNGLPIXELSTOREFPROC)loadFunction("glPixelStoref");
  glPixelStorei = (PFNGLPIXELSTOREIPROC)loadFunction("glPixelStorei");
  glPixelTransferf = (PFNGLPIXELTRANSFERFPROC)loadFunction("glPixelTransferf");
  glPixelTransferi = (PFNGLPIXELTRANSFERIPROC)loadFunction("glPixelTransferi");
  glPixelTransformParameterfEXT = (PFNGLPIXELTRANSFORMPARAMETERFEXTPROC)loadFunction(
      "glPixelTransformParameterfEXT");
  glPixelTransformParameterfvEXT = (PFNGLPIXELTRANSFORMPARAMETERFVEXTPROC)loadFunction(
      "glPixelTransformParameterfvEXT");
  glPixelTransformParameteriEXT = (PFNGLPIXELTRANSFORMPARAMETERIEXTPROC)loadFunction(
      "glPixelTransformParameteriEXT");
  glPixelTransformParameterivEXT = (PFNGLPIXELTRANSFORMPARAMETERIVEXTPROC)loadFunction(
      "glPixelTransformParameterivEXT");
  glPixelZoom = (PFNGLPIXELZOOMPROC)loadFunction("glPixelZoom");
  glPointAlongPathNV = (PFNGLPOINTALONGPATHNVPROC)loadFunction("glPointAlongPathNV");
  glPointParameterf = (PFNGLPOINTPARAMETERFPROC)loadFunction("glPointParameterf");
  glPointParameterfARB = (PFNGLPOINTPARAMETERFARBPROC)loadFunction("glPointParameterfARB");
  glPointParameterfEXT = (PFNGLPOINTPARAMETERFEXTPROC)loadFunction("glPointParameterfEXT");
  glPointParameterfv = (PFNGLPOINTPARAMETERFVPROC)loadFunction("glPointParameterfv");
  glPointParameterfvARB = (PFNGLPOINTPARAMETERFVARBPROC)loadFunction("glPointParameterfvARB");
  glPointParameterfvEXT = (PFNGLPOINTPARAMETERFVEXTPROC)loadFunction("glPointParameterfvEXT");
  glPointParameteri = (PFNGLPOINTPARAMETERIPROC)loadFunction("glPointParameteri");
  glPointParameteriNV = (PFNGLPOINTPARAMETERINVPROC)loadFunction("glPointParameteriNV");
  glPointParameteriv = (PFNGLPOINTPARAMETERIVPROC)loadFunction("glPointParameteriv");
  glPointParameterivNV = (PFNGLPOINTPARAMETERIVNVPROC)loadFunction("glPointParameterivNV");
  glPointSize = (PFNGLPOINTSIZEPROC)loadFunction("glPointSize");
  glPolygonMode = (PFNGLPOLYGONMODEPROC)loadFunction("glPolygonMode");
  glPolygonOffset = (PFNGLPOLYGONOFFSETPROC)loadFunction("glPolygonOffset");
  glPolygonOffsetClamp = (PFNGLPOLYGONOFFSETCLAMPPROC)loadFunction("glPolygonOffsetClamp");
  glPolygonOffsetClampEXT = (PFNGLPOLYGONOFFSETCLAMPEXTPROC)loadFunction(
      "glPolygonOffsetClampEXT");
  glPolygonOffsetEXT = (PFNGLPOLYGONOFFSETEXTPROC)loadFunction("glPolygonOffsetEXT");
  glPolygonStipple = (PFNGLPOLYGONSTIPPLEPROC)loadFunction("glPolygonStipple");
  glPopAttrib = (PFNGLPOPATTRIBPROC)loadFunction("glPopAttrib");
  glPopClientAttrib = (PFNGLPOPCLIENTATTRIBPROC)loadFunction("glPopClientAttrib");
  glPopDebugGroup = (PFNGLPOPDEBUGGROUPPROC)loadFunction("glPopDebugGroup");
  glPopDebugGroupKHR = (PFNGLPOPDEBUGGROUPKHRPROC)loadFunction("glPopDebugGroupKHR");
  glPopGroupMarkerEXT = (PFNGLPOPGROUPMARKEREXTPROC)loadFunction("glPopGroupMarkerEXT");
  glPopMatrix = (PFNGLPOPMATRIXPROC)loadFunction("glPopMatrix");
  glPopName = (PFNGLPOPNAMEPROC)loadFunction("glPopName");
  glPresentFrameDualFillNV = (PFNGLPRESENTFRAMEDUALFILLNVPROC)loadFunction(
      "glPresentFrameDualFillNV");
  glPresentFrameKeyedNV = (PFNGLPRESENTFRAMEKEYEDNVPROC)loadFunction("glPresentFrameKeyedNV");
  glPrimitiveBoundingBoxARB = (PFNGLPRIMITIVEBOUNDINGBOXARBPROC)loadFunction(
      "glPrimitiveBoundingBoxARB");
  glPrimitiveRestartIndex = (PFNGLPRIMITIVERESTARTINDEXPROC)loadFunction(
      "glPrimitiveRestartIndex");
  glPrimitiveRestartIndexNV = (PFNGLPRIMITIVERESTARTINDEXNVPROC)loadFunction(
      "glPrimitiveRestartIndexNV");
  glPrimitiveRestartNV = (PFNGLPRIMITIVERESTARTNVPROC)loadFunction("glPrimitiveRestartNV");
  glPrioritizeTextures = (PFNGLPRIORITIZETEXTURESPROC)loadFunction("glPrioritizeTextures");
  glPrioritizeTexturesEXT = (PFNGLPRIORITIZETEXTURESEXTPROC)loadFunction(
      "glPrioritizeTexturesEXT");
  glProgramBinary = (PFNGLPROGRAMBINARYPROC)loadFunction("glProgramBinary");
  glProgramBufferParametersIivNV = (PFNGLPROGRAMBUFFERPARAMETERSIIVNVPROC)loadFunction(
      "glProgramBufferParametersIivNV");
  glProgramBufferParametersIuivNV = (PFNGLPROGRAMBUFFERPARAMETERSIUIVNVPROC)loadFunction(
      "glProgramBufferParametersIuivNV");
  glProgramBufferParametersfvNV = (PFNGLPROGRAMBUFFERPARAMETERSFVNVPROC)loadFunction(
      "glProgramBufferParametersfvNV");
  glProgramEnvParameter4dARB = (PFNGLPROGRAMENVPARAMETER4DARBPROC)loadFunction(
      "glProgramEnvParameter4dARB");
  glProgramEnvParameter4dvARB = (PFNGLPROGRAMENVPARAMETER4DVARBPROC)loadFunction(
      "glProgramEnvParameter4dvARB");
  glProgramEnvParameter4fARB = (PFNGLPROGRAMENVPARAMETER4FARBPROC)loadFunction(
      "glProgramEnvParameter4fARB");
  glProgramEnvParameter4fvARB = (PFNGLPROGRAMENVPARAMETER4FVARBPROC)loadFunction(
      "glProgramEnvParameter4fvARB");
  glProgramEnvParameterI4iNV = (PFNGLPROGRAMENVPARAMETERI4INVPROC)loadFunction(
      "glProgramEnvParameterI4iNV");
  glProgramEnvParameterI4ivNV = (PFNGLPROGRAMENVPARAMETERI4IVNVPROC)loadFunction(
      "glProgramEnvParameterI4ivNV");
  glProgramEnvParameterI4uiNV = (PFNGLPROGRAMENVPARAMETERI4UINVPROC)loadFunction(
      "glProgramEnvParameterI4uiNV");
  glProgramEnvParameterI4uivNV = (PFNGLPROGRAMENVPARAMETERI4UIVNVPROC)loadFunction(
      "glProgramEnvParameterI4uivNV");
  glProgramEnvParameters4fvEXT = (PFNGLPROGRAMENVPARAMETERS4FVEXTPROC)loadFunction(
      "glProgramEnvParameters4fvEXT");
  glProgramEnvParametersI4ivNV = (PFNGLPROGRAMENVPARAMETERSI4IVNVPROC)loadFunction(
      "glProgramEnvParametersI4ivNV");
  glProgramEnvParametersI4uivNV = (PFNGLPROGRAMENVPARAMETERSI4UIVNVPROC)loadFunction(
      "glProgramEnvParametersI4uivNV");
  glProgramLocalParameter4dARB = (PFNGLPROGRAMLOCALPARAMETER4DARBPROC)loadFunction(
      "glProgramLocalParameter4dARB");
  glProgramLocalParameter4dvARB = (PFNGLPROGRAMLOCALPARAMETER4DVARBPROC)loadFunction(
      "glProgramLocalParameter4dvARB");
  glProgramLocalParameter4fARB = (PFNGLPROGRAMLOCALPARAMETER4FARBPROC)loadFunction(
      "glProgramLocalParameter4fARB");
  glProgramLocalParameter4fvARB = (PFNGLPROGRAMLOCALPARAMETER4FVARBPROC)loadFunction(
      "glProgramLocalParameter4fvARB");
  glProgramLocalParameterI4iNV = (PFNGLPROGRAMLOCALPARAMETERI4INVPROC)loadFunction(
      "glProgramLocalParameterI4iNV");
  glProgramLocalParameterI4ivNV = (PFNGLPROGRAMLOCALPARAMETERI4IVNVPROC)loadFunction(
      "glProgramLocalParameterI4ivNV");
  glProgramLocalParameterI4uiNV = (PFNGLPROGRAMLOCALPARAMETERI4UINVPROC)loadFunction(
      "glProgramLocalParameterI4uiNV");
  glProgramLocalParameterI4uivNV = (PFNGLPROGRAMLOCALPARAMETERI4UIVNVPROC)loadFunction(
      "glProgramLocalParameterI4uivNV");
  glProgramLocalParameters4fvEXT = (PFNGLPROGRAMLOCALPARAMETERS4FVEXTPROC)loadFunction(
      "glProgramLocalParameters4fvEXT");
  glProgramLocalParametersI4ivNV = (PFNGLPROGRAMLOCALPARAMETERSI4IVNVPROC)loadFunction(
      "glProgramLocalParametersI4ivNV");
  glProgramLocalParametersI4uivNV = (PFNGLPROGRAMLOCALPARAMETERSI4UIVNVPROC)loadFunction(
      "glProgramLocalParametersI4uivNV");
  glProgramNamedParameter4dNV = (PFNGLPROGRAMNAMEDPARAMETER4DNVPROC)loadFunction(
      "glProgramNamedParameter4dNV");
  glProgramNamedParameter4dvNV = (PFNGLPROGRAMNAMEDPARAMETER4DVNVPROC)loadFunction(
      "glProgramNamedParameter4dvNV");
  glProgramNamedParameter4fNV = (PFNGLPROGRAMNAMEDPARAMETER4FNVPROC)loadFunction(
      "glProgramNamedParameter4fNV");
  glProgramNamedParameter4fvNV = (PFNGLPROGRAMNAMEDPARAMETER4FVNVPROC)loadFunction(
      "glProgramNamedParameter4fvNV");
  glProgramParameter4dNV = (PFNGLPROGRAMPARAMETER4DNVPROC)loadFunction("glProgramParameter4dNV");
  glProgramParameter4dvNV = (PFNGLPROGRAMPARAMETER4DVNVPROC)loadFunction(
      "glProgramParameter4dvNV");
  glProgramParameter4fNV = (PFNGLPROGRAMPARAMETER4FNVPROC)loadFunction("glProgramParameter4fNV");
  glProgramParameter4fvNV = (PFNGLPROGRAMPARAMETER4FVNVPROC)loadFunction(
      "glProgramParameter4fvNV");
  glProgramParameteri = (PFNGLPROGRAMPARAMETERIPROC)loadFunction("glProgramParameteri");
  glProgramParameteriARB = (PFNGLPROGRAMPARAMETERIARBPROC)loadFunction("glProgramParameteriARB");
  glProgramParameteriEXT = (PFNGLPROGRAMPARAMETERIEXTPROC)loadFunction("glProgramParameteriEXT");
  glProgramParameters4dvNV = (PFNGLPROGRAMPARAMETERS4DVNVPROC)loadFunction(
      "glProgramParameters4dvNV");
  glProgramParameters4fvNV = (PFNGLPROGRAMPARAMETERS4FVNVPROC)loadFunction(
      "glProgramParameters4fvNV");
  glProgramPathFragmentInputGenNV = (PFNGLPROGRAMPATHFRAGMENTINPUTGENNVPROC)loadFunction(
      "glProgramPathFragmentInputGenNV");
  glProgramStringARB = (PFNGLPROGRAMSTRINGARBPROC)loadFunction("glProgramStringARB");
  glProgramSubroutineParametersuivNV = (PFNGLPROGRAMSUBROUTINEPARAMETERSUIVNVPROC)loadFunction(
      "glProgramSubroutineParametersuivNV");
  glProgramUniform1d = (PFNGLPROGRAMUNIFORM1DPROC)loadFunction("glProgramUniform1d");
  glProgramUniform1dEXT = (PFNGLPROGRAMUNIFORM1DEXTPROC)loadFunction("glProgramUniform1dEXT");
  glProgramUniform1dv = (PFNGLPROGRAMUNIFORM1DVPROC)loadFunction("glProgramUniform1dv");
  glProgramUniform1dvEXT = (PFNGLPROGRAMUNIFORM1DVEXTPROC)loadFunction("glProgramUniform1dvEXT");
  glProgramUniform1f = (PFNGLPROGRAMUNIFORM1FPROC)loadFunction("glProgramUniform1f");
  glProgramUniform1fEXT = (PFNGLPROGRAMUNIFORM1FEXTPROC)loadFunction("glProgramUniform1fEXT");
  glProgramUniform1fv = (PFNGLPROGRAMUNIFORM1FVPROC)loadFunction("glProgramUniform1fv");
  glProgramUniform1fvEXT = (PFNGLPROGRAMUNIFORM1FVEXTPROC)loadFunction("glProgramUniform1fvEXT");
  glProgramUniform1i = (PFNGLPROGRAMUNIFORM1IPROC)loadFunction("glProgramUniform1i");
  glProgramUniform1i64ARB = (PFNGLPROGRAMUNIFORM1I64ARBPROC)loadFunction(
      "glProgramUniform1i64ARB");
  glProgramUniform1i64NV = (PFNGLPROGRAMUNIFORM1I64NVPROC)loadFunction("glProgramUniform1i64NV");
  glProgramUniform1i64vARB = (PFNGLPROGRAMUNIFORM1I64VARBPROC)loadFunction(
      "glProgramUniform1i64vARB");
  glProgramUniform1i64vNV = (PFNGLPROGRAMUNIFORM1I64VNVPROC)loadFunction(
      "glProgramUniform1i64vNV");
  glProgramUniform1iEXT = (PFNGLPROGRAMUNIFORM1IEXTPROC)loadFunction("glProgramUniform1iEXT");
  glProgramUniform1iv = (PFNGLPROGRAMUNIFORM1IVPROC)loadFunction("glProgramUniform1iv");
  glProgramUniform1ivEXT = (PFNGLPROGRAMUNIFORM1IVEXTPROC)loadFunction("glProgramUniform1ivEXT");
  glProgramUniform1ui = (PFNGLPROGRAMUNIFORM1UIPROC)loadFunction("glProgramUniform1ui");
  glProgramUniform1ui64ARB = (PFNGLPROGRAMUNIFORM1UI64ARBPROC)loadFunction(
      "glProgramUniform1ui64ARB");
  glProgramUniform1ui64NV = (PFNGLPROGRAMUNIFORM1UI64NVPROC)loadFunction(
      "glProgramUniform1ui64NV");
  glProgramUniform1ui64vARB = (PFNGLPROGRAMUNIFORM1UI64VARBPROC)loadFunction(
      "glProgramUniform1ui64vARB");
  glProgramUniform1ui64vNV = (PFNGLPROGRAMUNIFORM1UI64VNVPROC)loadFunction(
      "glProgramUniform1ui64vNV");
  glProgramUniform1uiEXT = (PFNGLPROGRAMUNIFORM1UIEXTPROC)loadFunction("glProgramUniform1uiEXT");
  glProgramUniform1uiv = (PFNGLPROGRAMUNIFORM1UIVPROC)loadFunction("glProgramUniform1uiv");
  glProgramUniform1uivEXT = (PFNGLPROGRAMUNIFORM1UIVEXTPROC)loadFunction(
      "glProgramUniform1uivEXT");
  glProgramUniform2d = (PFNGLPROGRAMUNIFORM2DPROC)loadFunction("glProgramUniform2d");
  glProgramUniform2dEXT = (PFNGLPROGRAMUNIFORM2DEXTPROC)loadFunction("glProgramUniform2dEXT");
  glProgramUniform2dv = (PFNGLPROGRAMUNIFORM2DVPROC)loadFunction("glProgramUniform2dv");
  glProgramUniform2dvEXT = (PFNGLPROGRAMUNIFORM2DVEXTPROC)loadFunction("glProgramUniform2dvEXT");
  glProgramUniform2f = (PFNGLPROGRAMUNIFORM2FPROC)loadFunction("glProgramUniform2f");
  glProgramUniform2fEXT = (PFNGLPROGRAMUNIFORM2FEXTPROC)loadFunction("glProgramUniform2fEXT");
  glProgramUniform2fv = (PFNGLPROGRAMUNIFORM2FVPROC)loadFunction("glProgramUniform2fv");
  glProgramUniform2fvEXT = (PFNGLPROGRAMUNIFORM2FVEXTPROC)loadFunction("glProgramUniform2fvEXT");
  glProgramUniform2i = (PFNGLPROGRAMUNIFORM2IPROC)loadFunction("glProgramUniform2i");
  glProgramUniform2i64ARB = (PFNGLPROGRAMUNIFORM2I64ARBPROC)loadFunction(
      "glProgramUniform2i64ARB");
  glProgramUniform2i64NV = (PFNGLPROGRAMUNIFORM2I64NVPROC)loadFunction("glProgramUniform2i64NV");
  glProgramUniform2i64vARB = (PFNGLPROGRAMUNIFORM2I64VARBPROC)loadFunction(
      "glProgramUniform2i64vARB");
  glProgramUniform2i64vNV = (PFNGLPROGRAMUNIFORM2I64VNVPROC)loadFunction(
      "glProgramUniform2i64vNV");
  glProgramUniform2iEXT = (PFNGLPROGRAMUNIFORM2IEXTPROC)loadFunction("glProgramUniform2iEXT");
  glProgramUniform2iv = (PFNGLPROGRAMUNIFORM2IVPROC)loadFunction("glProgramUniform2iv");
  glProgramUniform2ivEXT = (PFNGLPROGRAMUNIFORM2IVEXTPROC)loadFunction("glProgramUniform2ivEXT");
  glProgramUniform2ui = (PFNGLPROGRAMUNIFORM2UIPROC)loadFunction("glProgramUniform2ui");
  glProgramUniform2ui64ARB = (PFNGLPROGRAMUNIFORM2UI64ARBPROC)loadFunction(
      "glProgramUniform2ui64ARB");
  glProgramUniform2ui64NV = (PFNGLPROGRAMUNIFORM2UI64NVPROC)loadFunction(
      "glProgramUniform2ui64NV");
  glProgramUniform2ui64vARB = (PFNGLPROGRAMUNIFORM2UI64VARBPROC)loadFunction(
      "glProgramUniform2ui64vARB");
  glProgramUniform2ui64vNV = (PFNGLPROGRAMUNIFORM2UI64VNVPROC)loadFunction(
      "glProgramUniform2ui64vNV");
  glProgramUniform2uiEXT = (PFNGLPROGRAMUNIFORM2UIEXTPROC)loadFunction("glProgramUniform2uiEXT");
  glProgramUniform2uiv = (PFNGLPROGRAMUNIFORM2UIVPROC)loadFunction("glProgramUniform2uiv");
  glProgramUniform2uivEXT = (PFNGLPROGRAMUNIFORM2UIVEXTPROC)loadFunction(
      "glProgramUniform2uivEXT");
  glProgramUniform3d = (PFNGLPROGRAMUNIFORM3DPROC)loadFunction("glProgramUniform3d");
  glProgramUniform3dEXT = (PFNGLPROGRAMUNIFORM3DEXTPROC)loadFunction("glProgramUniform3dEXT");
  glProgramUniform3dv = (PFNGLPROGRAMUNIFORM3DVPROC)loadFunction("glProgramUniform3dv");
  glProgramUniform3dvEXT = (PFNGLPROGRAMUNIFORM3DVEXTPROC)loadFunction("glProgramUniform3dvEXT");
  glProgramUniform3f = (PFNGLPROGRAMUNIFORM3FPROC)loadFunction("glProgramUniform3f");
  glProgramUniform3fEXT = (PFNGLPROGRAMUNIFORM3FEXTPROC)loadFunction("glProgramUniform3fEXT");
  glProgramUniform3fv = (PFNGLPROGRAMUNIFORM3FVPROC)loadFunction("glProgramUniform3fv");
  glProgramUniform3fvEXT = (PFNGLPROGRAMUNIFORM3FVEXTPROC)loadFunction("glProgramUniform3fvEXT");
  glProgramUniform3i = (PFNGLPROGRAMUNIFORM3IPROC)loadFunction("glProgramUniform3i");
  glProgramUniform3i64ARB = (PFNGLPROGRAMUNIFORM3I64ARBPROC)loadFunction(
      "glProgramUniform3i64ARB");
  glProgramUniform3i64NV = (PFNGLPROGRAMUNIFORM3I64NVPROC)loadFunction("glProgramUniform3i64NV");
  glProgramUniform3i64vARB = (PFNGLPROGRAMUNIFORM3I64VARBPROC)loadFunction(
      "glProgramUniform3i64vARB");
  glProgramUniform3i64vNV = (PFNGLPROGRAMUNIFORM3I64VNVPROC)loadFunction(
      "glProgramUniform3i64vNV");
  glProgramUniform3iEXT = (PFNGLPROGRAMUNIFORM3IEXTPROC)loadFunction("glProgramUniform3iEXT");
  glProgramUniform3iv = (PFNGLPROGRAMUNIFORM3IVPROC)loadFunction("glProgramUniform3iv");
  glProgramUniform3ivEXT = (PFNGLPROGRAMUNIFORM3IVEXTPROC)loadFunction("glProgramUniform3ivEXT");
  glProgramUniform3ui = (PFNGLPROGRAMUNIFORM3UIPROC)loadFunction("glProgramUniform3ui");
  glProgramUniform3ui64ARB = (PFNGLPROGRAMUNIFORM3UI64ARBPROC)loadFunction(
      "glProgramUniform3ui64ARB");
  glProgramUniform3ui64NV = (PFNGLPROGRAMUNIFORM3UI64NVPROC)loadFunction(
      "glProgramUniform3ui64NV");
  glProgramUniform3ui64vARB = (PFNGLPROGRAMUNIFORM3UI64VARBPROC)loadFunction(
      "glProgramUniform3ui64vARB");
  glProgramUniform3ui64vNV = (PFNGLPROGRAMUNIFORM3UI64VNVPROC)loadFunction(
      "glProgramUniform3ui64vNV");
  glProgramUniform3uiEXT = (PFNGLPROGRAMUNIFORM3UIEXTPROC)loadFunction("glProgramUniform3uiEXT");
  glProgramUniform3uiv = (PFNGLPROGRAMUNIFORM3UIVPROC)loadFunction("glProgramUniform3uiv");
  glProgramUniform3uivEXT = (PFNGLPROGRAMUNIFORM3UIVEXTPROC)loadFunction(
      "glProgramUniform3uivEXT");
  glProgramUniform4d = (PFNGLPROGRAMUNIFORM4DPROC)loadFunction("glProgramUniform4d");
  glProgramUniform4dEXT = (PFNGLPROGRAMUNIFORM4DEXTPROC)loadFunction("glProgramUniform4dEXT");
  glProgramUniform4dv = (PFNGLPROGRAMUNIFORM4DVPROC)loadFunction("glProgramUniform4dv");
  glProgramUniform4dvEXT = (PFNGLPROGRAMUNIFORM4DVEXTPROC)loadFunction("glProgramUniform4dvEXT");
  glProgramUniform4f = (PFNGLPROGRAMUNIFORM4FPROC)loadFunction("glProgramUniform4f");
  glProgramUniform4fEXT = (PFNGLPROGRAMUNIFORM4FEXTPROC)loadFunction("glProgramUniform4fEXT");
  glProgramUniform4fv = (PFNGLPROGRAMUNIFORM4FVPROC)loadFunction("glProgramUniform4fv");
  glProgramUniform4fvEXT = (PFNGLPROGRAMUNIFORM4FVEXTPROC)loadFunction("glProgramUniform4fvEXT");
  glProgramUniform4i = (PFNGLPROGRAMUNIFORM4IPROC)loadFunction("glProgramUniform4i");
  glProgramUniform4i64ARB = (PFNGLPROGRAMUNIFORM4I64ARBPROC)loadFunction(
      "glProgramUniform4i64ARB");
  glProgramUniform4i64NV = (PFNGLPROGRAMUNIFORM4I64NVPROC)loadFunction("glProgramUniform4i64NV");
  glProgramUniform4i64vARB = (PFNGLPROGRAMUNIFORM4I64VARBPROC)loadFunction(
      "glProgramUniform4i64vARB");
  glProgramUniform4i64vNV = (PFNGLPROGRAMUNIFORM4I64VNVPROC)loadFunction(
      "glProgramUniform4i64vNV");
  glProgramUniform4iEXT = (PFNGLPROGRAMUNIFORM4IEXTPROC)loadFunction("glProgramUniform4iEXT");
  glProgramUniform4iv = (PFNGLPROGRAMUNIFORM4IVPROC)loadFunction("glProgramUniform4iv");
  glProgramUniform4ivEXT = (PFNGLPROGRAMUNIFORM4IVEXTPROC)loadFunction("glProgramUniform4ivEXT");
  glProgramUniform4ui = (PFNGLPROGRAMUNIFORM4UIPROC)loadFunction("glProgramUniform4ui");
  glProgramUniform4ui64ARB = (PFNGLPROGRAMUNIFORM4UI64ARBPROC)loadFunction(
      "glProgramUniform4ui64ARB");
  glProgramUniform4ui64NV = (PFNGLPROGRAMUNIFORM4UI64NVPROC)loadFunction(
      "glProgramUniform4ui64NV");
  glProgramUniform4ui64vARB = (PFNGLPROGRAMUNIFORM4UI64VARBPROC)loadFunction(
      "glProgramUniform4ui64vARB");
  glProgramUniform4ui64vNV = (PFNGLPROGRAMUNIFORM4UI64VNVPROC)loadFunction(
      "glProgramUniform4ui64vNV");
  glProgramUniform4uiEXT = (PFNGLPROGRAMUNIFORM4UIEXTPROC)loadFunction("glProgramUniform4uiEXT");
  glProgramUniform4uiv = (PFNGLPROGRAMUNIFORM4UIVPROC)loadFunction("glProgramUniform4uiv");
  glProgramUniform4uivEXT = (PFNGLPROGRAMUNIFORM4UIVEXTPROC)loadFunction(
      "glProgramUniform4uivEXT");
  glProgramUniformHandleui64ARB = (PFNGLPROGRAMUNIFORMHANDLEUI64ARBPROC)loadFunction(
      "glProgramUniformHandleui64ARB");
  glProgramUniformHandleui64NV = (PFNGLPROGRAMUNIFORMHANDLEUI64NVPROC)loadFunction(
      "glProgramUniformHandleui64NV");
  glProgramUniformHandleui64vARB = (PFNGLPROGRAMUNIFORMHANDLEUI64VARBPROC)loadFunction(
      "glProgramUniformHandleui64vARB");
  glProgramUniformHandleui64vNV = (PFNGLPROGRAMUNIFORMHANDLEUI64VNVPROC)loadFunction(
      "glProgramUniformHandleui64vNV");
  glProgramUniformMatrix2dv = (PFNGLPROGRAMUNIFORMMATRIX2DVPROC)loadFunction(
      "glProgramUniformMatrix2dv");
  glProgramUniformMatrix2dvEXT = (PFNGLPROGRAMUNIFORMMATRIX2DVEXTPROC)loadFunction(
      "glProgramUniformMatrix2dvEXT");
  glProgramUniformMatrix2fv = (PFNGLPROGRAMUNIFORMMATRIX2FVPROC)loadFunction(
      "glProgramUniformMatrix2fv");
  glProgramUniformMatrix2fvEXT = (PFNGLPROGRAMUNIFORMMATRIX2FVEXTPROC)loadFunction(
      "glProgramUniformMatrix2fvEXT");
  glProgramUniformMatrix2x3dv = (PFNGLPROGRAMUNIFORMMATRIX2X3DVPROC)loadFunction(
      "glProgramUniformMatrix2x3dv");
  glProgramUniformMatrix2x3dvEXT = (PFNGLPROGRAMUNIFORMMATRIX2X3DVEXTPROC)loadFunction(
      "glProgramUniformMatrix2x3dvEXT");
  glProgramUniformMatrix2x3fv = (PFNGLPROGRAMUNIFORMMATRIX2X3FVPROC)loadFunction(
      "glProgramUniformMatrix2x3fv");
  glProgramUniformMatrix2x3fvEXT = (PFNGLPROGRAMUNIFORMMATRIX2X3FVEXTPROC)loadFunction(
      "glProgramUniformMatrix2x3fvEXT");
  glProgramUniformMatrix2x4dv = (PFNGLPROGRAMUNIFORMMATRIX2X4DVPROC)loadFunction(
      "glProgramUniformMatrix2x4dv");
  glProgramUniformMatrix2x4dvEXT = (PFNGLPROGRAMUNIFORMMATRIX2X4DVEXTPROC)loadFunction(
      "glProgramUniformMatrix2x4dvEXT");
  glProgramUniformMatrix2x4fv = (PFNGLPROGRAMUNIFORMMATRIX2X4FVPROC)loadFunction(
      "glProgramUniformMatrix2x4fv");
  glProgramUniformMatrix2x4fvEXT = (PFNGLPROGRAMUNIFORMMATRIX2X4FVEXTPROC)loadFunction(
      "glProgramUniformMatrix2x4fvEXT");
  glProgramUniformMatrix3dv = (PFNGLPROGRAMUNIFORMMATRIX3DVPROC)loadFunction(
      "glProgramUniformMatrix3dv");
  glProgramUniformMatrix3dvEXT = (PFNGLPROGRAMUNIFORMMATRIX3DVEXTPROC)loadFunction(
      "glProgramUniformMatrix3dvEXT");
  glProgramUniformMatrix3fv = (PFNGLPROGRAMUNIFORMMATRIX3FVPROC)loadFunction(
      "glProgramUniformMatrix3fv");
  glProgramUniformMatrix3fvEXT = (PFNGLPROGRAMUNIFORMMATRIX3FVEXTPROC)loadFunction(
      "glProgramUniformMatrix3fvEXT");
  glProgramUniformMatrix3x2dv = (PFNGLPROGRAMUNIFORMMATRIX3X2DVPROC)loadFunction(
      "glProgramUniformMatrix3x2dv");
  glProgramUniformMatrix3x2dvEXT = (PFNGLPROGRAMUNIFORMMATRIX3X2DVEXTPROC)loadFunction(
      "glProgramUniformMatrix3x2dvEXT");
  glProgramUniformMatrix3x2fv = (PFNGLPROGRAMUNIFORMMATRIX3X2FVPROC)loadFunction(
      "glProgramUniformMatrix3x2fv");
  glProgramUniformMatrix3x2fvEXT = (PFNGLPROGRAMUNIFORMMATRIX3X2FVEXTPROC)loadFunction(
      "glProgramUniformMatrix3x2fvEXT");
  glProgramUniformMatrix3x4dv = (PFNGLPROGRAMUNIFORMMATRIX3X4DVPROC)loadFunction(
      "glProgramUniformMatrix3x4dv");
  glProgramUniformMatrix3x4dvEXT = (PFNGLPROGRAMUNIFORMMATRIX3X4DVEXTPROC)loadFunction(
      "glProgramUniformMatrix3x4dvEXT");
  glProgramUniformMatrix3x4fv = (PFNGLPROGRAMUNIFORMMATRIX3X4FVPROC)loadFunction(
      "glProgramUniformMatrix3x4fv");
  glProgramUniformMatrix3x4fvEXT = (PFNGLPROGRAMUNIFORMMATRIX3X4FVEXTPROC)loadFunction(
      "glProgramUniformMatrix3x4fvEXT");
  glProgramUniformMatrix4dv = (PFNGLPROGRAMUNIFORMMATRIX4DVPROC)loadFunction(
      "glProgramUniformMatrix4dv");
  glProgramUniformMatrix4dvEXT = (PFNGLPROGRAMUNIFORMMATRIX4DVEXTPROC)loadFunction(
      "glProgramUniformMatrix4dvEXT");
  glProgramUniformMatrix4fv = (PFNGLPROGRAMUNIFORMMATRIX4FVPROC)loadFunction(
      "glProgramUniformMatrix4fv");
  glProgramUniformMatrix4fvEXT = (PFNGLPROGRAMUNIFORMMATRIX4FVEXTPROC)loadFunction(
      "glProgramUniformMatrix4fvEXT");
  glProgramUniformMatrix4x2dv = (PFNGLPROGRAMUNIFORMMATRIX4X2DVPROC)loadFunction(
      "glProgramUniformMatrix4x2dv");
  glProgramUniformMatrix4x2dvEXT = (PFNGLPROGRAMUNIFORMMATRIX4X2DVEXTPROC)loadFunction(
      "glProgramUniformMatrix4x2dvEXT");
  glProgramUniformMatrix4x2fv = (PFNGLPROGRAMUNIFORMMATRIX4X2FVPROC)loadFunction(
      "glProgramUniformMatrix4x2fv");
  glProgramUniformMatrix4x2fvEXT = (PFNGLPROGRAMUNIFORMMATRIX4X2FVEXTPROC)loadFunction(
      "glProgramUniformMatrix4x2fvEXT");
  glProgramUniformMatrix4x3dv = (PFNGLPROGRAMUNIFORMMATRIX4X3DVPROC)loadFunction(
      "glProgramUniformMatrix4x3dv");
  glProgramUniformMatrix4x3dvEXT = (PFNGLPROGRAMUNIFORMMATRIX4X3DVEXTPROC)loadFunction(
      "glProgramUniformMatrix4x3dvEXT");
  glProgramUniformMatrix4x3fv = (PFNGLPROGRAMUNIFORMMATRIX4X3FVPROC)loadFunction(
      "glProgramUniformMatrix4x3fv");
  glProgramUniformMatrix4x3fvEXT = (PFNGLPROGRAMUNIFORMMATRIX4X3FVEXTPROC)loadFunction(
      "glProgramUniformMatrix4x3fvEXT");
  glProgramUniformui64NV = (PFNGLPROGRAMUNIFORMUI64NVPROC)loadFunction("glProgramUniformui64NV");
  glProgramUniformui64vNV = (PFNGLPROGRAMUNIFORMUI64VNVPROC)loadFunction(
      "glProgramUniformui64vNV");
  glProgramVertexLimitNV = (PFNGLPROGRAMVERTEXLIMITNVPROC)loadFunction("glProgramVertexLimitNV");
  glProvokingVertex = (PFNGLPROVOKINGVERTEXPROC)loadFunction("glProvokingVertex");
  glProvokingVertexEXT = (PFNGLPROVOKINGVERTEXEXTPROC)loadFunction("glProvokingVertexEXT");
  glPushAttrib = (PFNGLPUSHATTRIBPROC)loadFunction("glPushAttrib");
  glPushClientAttrib = (PFNGLPUSHCLIENTATTRIBPROC)loadFunction("glPushClientAttrib");
  glPushClientAttribDefaultEXT = (PFNGLPUSHCLIENTATTRIBDEFAULTEXTPROC)loadFunction(
      "glPushClientAttribDefaultEXT");
  glPushDebugGroup = (PFNGLPUSHDEBUGGROUPPROC)loadFunction("glPushDebugGroup");
  glPushDebugGroupKHR = (PFNGLPUSHDEBUGGROUPKHRPROC)loadFunction("glPushDebugGroupKHR");
  glPushGroupMarkerEXT = (PFNGLPUSHGROUPMARKEREXTPROC)loadFunction("glPushGroupMarkerEXT");
  glPushMatrix = (PFNGLPUSHMATRIXPROC)loadFunction("glPushMatrix");
  glPushName = (PFNGLPUSHNAMEPROC)loadFunction("glPushName");
  glQueryCounter = (PFNGLQUERYCOUNTERPROC)loadFunction("glQueryCounter");
  glQueryObjectParameteruiAMD = (PFNGLQUERYOBJECTPARAMETERUIAMDPROC)loadFunction(
      "glQueryObjectParameteruiAMD");
  glQueryResourceNV = (PFNGLQUERYRESOURCENVPROC)loadFunction("glQueryResourceNV");
  glQueryResourceTagNV = (PFNGLQUERYRESOURCETAGNVPROC)loadFunction("glQueryResourceTagNV");
  glRasterPos2d = (PFNGLRASTERPOS2DPROC)loadFunction("glRasterPos2d");
  glRasterPos2dv = (PFNGLRASTERPOS2DVPROC)loadFunction("glRasterPos2dv");
  glRasterPos2f = (PFNGLRASTERPOS2FPROC)loadFunction("glRasterPos2f");
  glRasterPos2fv = (PFNGLRASTERPOS2FVPROC)loadFunction("glRasterPos2fv");
  glRasterPos2i = (PFNGLRASTERPOS2IPROC)loadFunction("glRasterPos2i");
  glRasterPos2iv = (PFNGLRASTERPOS2IVPROC)loadFunction("glRasterPos2iv");
  glRasterPos2s = (PFNGLRASTERPOS2SPROC)loadFunction("glRasterPos2s");
  glRasterPos2sv = (PFNGLRASTERPOS2SVPROC)loadFunction("glRasterPos2sv");
  glRasterPos3d = (PFNGLRASTERPOS3DPROC)loadFunction("glRasterPos3d");
  glRasterPos3dv = (PFNGLRASTERPOS3DVPROC)loadFunction("glRasterPos3dv");
  glRasterPos3f = (PFNGLRASTERPOS3FPROC)loadFunction("glRasterPos3f");
  glRasterPos3fv = (PFNGLRASTERPOS3FVPROC)loadFunction("glRasterPos3fv");
  glRasterPos3i = (PFNGLRASTERPOS3IPROC)loadFunction("glRasterPos3i");
  glRasterPos3iv = (PFNGLRASTERPOS3IVPROC)loadFunction("glRasterPos3iv");
  glRasterPos3s = (PFNGLRASTERPOS3SPROC)loadFunction("glRasterPos3s");
  glRasterPos3sv = (PFNGLRASTERPOS3SVPROC)loadFunction("glRasterPos3sv");
  glRasterPos4d = (PFNGLRASTERPOS4DPROC)loadFunction("glRasterPos4d");
  glRasterPos4dv = (PFNGLRASTERPOS4DVPROC)loadFunction("glRasterPos4dv");
  glRasterPos4f = (PFNGLRASTERPOS4FPROC)loadFunction("glRasterPos4f");
  glRasterPos4fv = (PFNGLRASTERPOS4FVPROC)loadFunction("glRasterPos4fv");
  glRasterPos4i = (PFNGLRASTERPOS4IPROC)loadFunction("glRasterPos4i");
  glRasterPos4iv = (PFNGLRASTERPOS4IVPROC)loadFunction("glRasterPos4iv");
  glRasterPos4s = (PFNGLRASTERPOS4SPROC)loadFunction("glRasterPos4s");
  glRasterPos4sv = (PFNGLRASTERPOS4SVPROC)loadFunction("glRasterPos4sv");
  glRasterSamplesEXT = (PFNGLRASTERSAMPLESEXTPROC)loadFunction("glRasterSamplesEXT");
  glReadBuffer = (PFNGLREADBUFFERPROC)loadFunction("glReadBuffer");
  glReadPixels = (PFNGLREADPIXELSPROC)loadFunction("glReadPixels");
  glReadnPixels = (PFNGLREADNPIXELSPROC)loadFunction("glReadnPixels");
  glReadnPixelsARB = (PFNGLREADNPIXELSARBPROC)loadFunction("glReadnPixelsARB");
  glReadnPixelsKHR = (PFNGLREADNPIXELSKHRPROC)loadFunction("glReadnPixelsKHR");
  glReleaseKeyedMutexWin32EXT = (PFNGLRELEASEKEYEDMUTEXWIN32EXTPROC)loadFunction(
      "glReleaseKeyedMutexWin32EXT");
  glRectd = (PFNGLRECTDPROC)loadFunction("glRectd");
  glRectdv = (PFNGLRECTDVPROC)loadFunction("glRectdv");
  glRectf = (PFNGLRECTFPROC)loadFunction("glRectf");
  glRectfv = (PFNGLRECTFVPROC)loadFunction("glRectfv");
  glRecti = (PFNGLRECTIPROC)loadFunction("glRecti");
  glRectiv = (PFNGLRECTIVPROC)loadFunction("glRectiv");
  glRects = (PFNGLRECTSPROC)loadFunction("glRects");
  glRectsv = (PFNGLRECTSVPROC)loadFunction("glRectsv");
  glReleaseShaderCompiler = (PFNGLRELEASESHADERCOMPILERPROC)loadFunction(
      "glReleaseShaderCompiler");
  glRenderGpuMaskNV = (PFNGLRENDERGPUMASKNVPROC)loadFunction("glRenderGpuMaskNV");
  glRenderMode = (PFNGLRENDERMODEPROC)loadFunction("glRenderMode");
  glRenderbufferStorage = (PFNGLRENDERBUFFERSTORAGEPROC)loadFunction("glRenderbufferStorage");
  glRenderbufferStorageEXT = (PFNGLRENDERBUFFERSTORAGEEXTPROC)loadFunction(
      "glRenderbufferStorageEXT");
  glRenderbufferStorageMultisample = (PFNGLRENDERBUFFERSTORAGEMULTISAMPLEPROC)loadFunction(
      "glRenderbufferStorageMultisample");
  glRenderbufferStorageMultisampleAdvancedAMD =
      (PFNGLRENDERBUFFERSTORAGEMULTISAMPLEADVANCEDAMDPROC)loadFunction(
          "glRenderbufferStorageMultisampleAdvancedAMD");
  glRenderbufferStorageMultisampleCoverageNV = (PFNGLRENDERBUFFERSTORAGEMULTISAMPLECOVERAGENVPROC)
      loadFunction("glRenderbufferStorageMultisampleCoverageNV");
  glRenderbufferStorageMultisampleEXT = (PFNGLRENDERBUFFERSTORAGEMULTISAMPLEEXTPROC)loadFunction(
      "glRenderbufferStorageMultisampleEXT");
  glRequestResidentProgramsNV = (PFNGLREQUESTRESIDENTPROGRAMSNVPROC)loadFunction(
      "glRequestResidentProgramsNV");
  glResetHistogram = (PFNGLRESETHISTOGRAMPROC)loadFunction("glResetHistogram");
  glResetHistogramEXT = (PFNGLRESETHISTOGRAMEXTPROC)loadFunction("glResetHistogramEXT");
  glResetMemoryObjectParameterNV = (PFNGLRESETMEMORYOBJECTPARAMETERNVPROC)loadFunction(
      "glResetMemoryObjectParameterNV");
  glResetMinmax = (PFNGLRESETMINMAXPROC)loadFunction("glResetMinmax");
  glResetMinmaxEXT = (PFNGLRESETMINMAXEXTPROC)loadFunction("glResetMinmaxEXT");
  glResolveDepthValuesNV = (PFNGLRESOLVEDEPTHVALUESNVPROC)loadFunction("glResolveDepthValuesNV");
  glResumeTransformFeedback = (PFNGLRESUMETRANSFORMFEEDBACKPROC)loadFunction(
      "glResumeTransformFeedback");
  glResumeTransformFeedbackNV = (PFNGLRESUMETRANSFORMFEEDBACKNVPROC)loadFunction(
      "glResumeTransformFeedbackNV");
  glRotated = (PFNGLROTATEDPROC)loadFunction("glRotated");
  glRotatef = (PFNGLROTATEFPROC)loadFunction("glRotatef");
  glSampleCoverage = (PFNGLSAMPLECOVERAGEPROC)loadFunction("glSampleCoverage");
  glSampleCoverageARB = (PFNGLSAMPLECOVERAGEARBPROC)loadFunction("glSampleCoverageARB");
  glSampleMaskEXT = (PFNGLSAMPLEMASKEXTPROC)loadFunction("glSampleMaskEXT");
  glSampleMaskIndexedNV = (PFNGLSAMPLEMASKINDEXEDNVPROC)loadFunction("glSampleMaskIndexedNV");
  glSampleMaski = (PFNGLSAMPLEMASKIPROC)loadFunction("glSampleMaski");
  glSamplePatternEXT = (PFNGLSAMPLEPATTERNEXTPROC)loadFunction("glSamplePatternEXT");
  glSamplerParameterIiv = (PFNGLSAMPLERPARAMETERIIVPROC)loadFunction("glSamplerParameterIiv");
  glSamplerParameterIuiv = (PFNGLSAMPLERPARAMETERIUIVPROC)loadFunction("glSamplerParameterIuiv");
  glSamplerParameterf = (PFNGLSAMPLERPARAMETERFPROC)loadFunction("glSamplerParameterf");
  glSamplerParameterfv = (PFNGLSAMPLERPARAMETERFVPROC)loadFunction("glSamplerParameterfv");
  glSamplerParameteri = (PFNGLSAMPLERPARAMETERIPROC)loadFunction("glSamplerParameteri");
  glSamplerParameteriv = (PFNGLSAMPLERPARAMETERIVPROC)loadFunction("glSamplerParameteriv");
  glScaled = (PFNGLSCALEDPROC)loadFunction("glScaled");
  glScalef = (PFNGLSCALEFPROC)loadFunction("glScalef");
  glScissor = (PFNGLSCISSORPROC)loadFunction("glScissor");
  glScissorArrayv = (PFNGLSCISSORARRAYVPROC)loadFunction("glScissorArrayv");
  glScissorExclusiveArrayvNV = (PFNGLSCISSOREXCLUSIVEARRAYVNVPROC)loadFunction(
      "glScissorExclusiveArrayvNV");
  glScissorExclusiveNV = (PFNGLSCISSOREXCLUSIVENVPROC)loadFunction("glScissorExclusiveNV");
  glScissorIndexed = (PFNGLSCISSORINDEXEDPROC)loadFunction("glScissorIndexed");
  glScissorIndexedv = (PFNGLSCISSORINDEXEDVPROC)loadFunction("glScissorIndexedv");
  glSecondaryColor3b = (PFNGLSECONDARYCOLOR3BPROC)loadFunction("glSecondaryColor3b");
  glSecondaryColor3bEXT = (PFNGLSECONDARYCOLOR3BEXTPROC)loadFunction("glSecondaryColor3bEXT");
  glSecondaryColor3bv = (PFNGLSECONDARYCOLOR3BVPROC)loadFunction("glSecondaryColor3bv");
  glSecondaryColor3bvEXT = (PFNGLSECONDARYCOLOR3BVEXTPROC)loadFunction("glSecondaryColor3bvEXT");
  glSecondaryColor3d = (PFNGLSECONDARYCOLOR3DPROC)loadFunction("glSecondaryColor3d");
  glSecondaryColor3dEXT = (PFNGLSECONDARYCOLOR3DEXTPROC)loadFunction("glSecondaryColor3dEXT");
  glSecondaryColor3dv = (PFNGLSECONDARYCOLOR3DVPROC)loadFunction("glSecondaryColor3dv");
  glSecondaryColor3dvEXT = (PFNGLSECONDARYCOLOR3DVEXTPROC)loadFunction("glSecondaryColor3dvEXT");
  glSecondaryColor3f = (PFNGLSECONDARYCOLOR3FPROC)loadFunction("glSecondaryColor3f");
  glSecondaryColor3fEXT = (PFNGLSECONDARYCOLOR3FEXTPROC)loadFunction("glSecondaryColor3fEXT");
  glSecondaryColor3fv = (PFNGLSECONDARYCOLOR3FVPROC)loadFunction("glSecondaryColor3fv");
  glSecondaryColor3fvEXT = (PFNGLSECONDARYCOLOR3FVEXTPROC)loadFunction("glSecondaryColor3fvEXT");
  glSecondaryColor3hNV = (PFNGLSECONDARYCOLOR3HNVPROC)loadFunction("glSecondaryColor3hNV");
  glSecondaryColor3hvNV = (PFNGLSECONDARYCOLOR3HVNVPROC)loadFunction("glSecondaryColor3hvNV");
  glSecondaryColor3i = (PFNGLSECONDARYCOLOR3IPROC)loadFunction("glSecondaryColor3i");
  glSecondaryColor3iEXT = (PFNGLSECONDARYCOLOR3IEXTPROC)loadFunction("glSecondaryColor3iEXT");
  glSecondaryColor3iv = (PFNGLSECONDARYCOLOR3IVPROC)loadFunction("glSecondaryColor3iv");
  glSecondaryColor3ivEXT = (PFNGLSECONDARYCOLOR3IVEXTPROC)loadFunction("glSecondaryColor3ivEXT");
  glSecondaryColor3s = (PFNGLSECONDARYCOLOR3SPROC)loadFunction("glSecondaryColor3s");
  glSecondaryColor3sEXT = (PFNGLSECONDARYCOLOR3SEXTPROC)loadFunction("glSecondaryColor3sEXT");
  glSecondaryColor3sv = (PFNGLSECONDARYCOLOR3SVPROC)loadFunction("glSecondaryColor3sv");
  glSecondaryColor3svEXT = (PFNGLSECONDARYCOLOR3SVEXTPROC)loadFunction("glSecondaryColor3svEXT");
  glSecondaryColor3ub = (PFNGLSECONDARYCOLOR3UBPROC)loadFunction("glSecondaryColor3ub");
  glSecondaryColor3ubEXT = (PFNGLSECONDARYCOLOR3UBEXTPROC)loadFunction("glSecondaryColor3ubEXT");
  glSecondaryColor3ubv = (PFNGLSECONDARYCOLOR3UBVPROC)loadFunction("glSecondaryColor3ubv");
  glSecondaryColor3ubvEXT = (PFNGLSECONDARYCOLOR3UBVEXTPROC)loadFunction(
      "glSecondaryColor3ubvEXT");
  glSecondaryColor3ui = (PFNGLSECONDARYCOLOR3UIPROC)loadFunction("glSecondaryColor3ui");
  glSecondaryColor3uiEXT = (PFNGLSECONDARYCOLOR3UIEXTPROC)loadFunction("glSecondaryColor3uiEXT");
  glSecondaryColor3uiv = (PFNGLSECONDARYCOLOR3UIVPROC)loadFunction("glSecondaryColor3uiv");
  glSecondaryColor3uivEXT = (PFNGLSECONDARYCOLOR3UIVEXTPROC)loadFunction(
      "glSecondaryColor3uivEXT");
  glSecondaryColor3us = (PFNGLSECONDARYCOLOR3USPROC)loadFunction("glSecondaryColor3us");
  glSecondaryColor3usEXT = (PFNGLSECONDARYCOLOR3USEXTPROC)loadFunction("glSecondaryColor3usEXT");
  glSecondaryColor3usv = (PFNGLSECONDARYCOLOR3USVPROC)loadFunction("glSecondaryColor3usv");
  glSecondaryColor3usvEXT = (PFNGLSECONDARYCOLOR3USVEXTPROC)loadFunction(
      "glSecondaryColor3usvEXT");
  glSecondaryColorFormatNV = (PFNGLSECONDARYCOLORFORMATNVPROC)loadFunction(
      "glSecondaryColorFormatNV");
  glSecondaryColorP3ui = (PFNGLSECONDARYCOLORP3UIPROC)loadFunction("glSecondaryColorP3ui");
  glSecondaryColorP3uiv = (PFNGLSECONDARYCOLORP3UIVPROC)loadFunction("glSecondaryColorP3uiv");
  glSecondaryColorPointer = (PFNGLSECONDARYCOLORPOINTERPROC)loadFunction(
      "glSecondaryColorPointer");
  glSecondaryColorPointerEXT = (PFNGLSECONDARYCOLORPOINTEREXTPROC)loadFunction(
      "glSecondaryColorPointerEXT");
  glSelectBuffer = (PFNGLSELECTBUFFERPROC)loadFunction("glSelectBuffer");
  glSelectPerfMonitorCountersAMD = (PFNGLSELECTPERFMONITORCOUNTERSAMDPROC)loadFunction(
      "glSelectPerfMonitorCountersAMD");
  glSemaphoreParameterivNV = (PFNGLSEMAPHOREPARAMETERIVNVPROC)loadFunction(
      "glSemaphoreParameterivNV");
  glSemaphoreParameterui64vEXT = (PFNGLSEMAPHOREPARAMETERUI64VEXTPROC)loadFunction(
      "glSemaphoreParameterui64vEXT");
  glSeparableFilter2D = (PFNGLSEPARABLEFILTER2DPROC)loadFunction("glSeparableFilter2D");
  glSeparableFilter2DEXT = (PFNGLSEPARABLEFILTER2DEXTPROC)loadFunction("glSeparableFilter2DEXT");
  glSetFenceAPPLE = (PFNGLSETFENCEAPPLEPROC)loadFunction("glSetFenceAPPLE");
  glSetFenceNV = (PFNGLSETFENCENVPROC)loadFunction("glSetFenceNV");
  glSetInvariantEXT = (PFNGLSETINVARIANTEXTPROC)loadFunction("glSetInvariantEXT");
  glSetLocalConstantEXT = (PFNGLSETLOCALCONSTANTEXTPROC)loadFunction("glSetLocalConstantEXT");
  glSetMultisamplefvAMD = (PFNGLSETMULTISAMPLEFVAMDPROC)loadFunction("glSetMultisamplefvAMD");
  glShadeModel = (PFNGLSHADEMODELPROC)loadFunction("glShadeModel");
  glShaderBinary = (PFNGLSHADERBINARYPROC)loadFunction("glShaderBinary");
  glShaderOp1EXT = (PFNGLSHADEROP1EXTPROC)loadFunction("glShaderOp1EXT");
  glShaderOp2EXT = (PFNGLSHADEROP2EXTPROC)loadFunction("glShaderOp2EXT");
  glShaderOp3EXT = (PFNGLSHADEROP3EXTPROC)loadFunction("glShaderOp3EXT");
  glShaderSource = (PFNGLSHADERSOURCEPROC)loadFunction("glShaderSource");
  glShaderSourceARB = (PFNGLSHADERSOURCEARBPROC)loadFunction("glShaderSourceARB");
  glShaderStorageBlockBinding = (PFNGLSHADERSTORAGEBLOCKBINDINGPROC)loadFunction(
      "glShaderStorageBlockBinding");
  glShadingRateImageBarrierNV = (PFNGLSHADINGRATEIMAGEBARRIERNVPROC)loadFunction(
      "glShadingRateImageBarrierNV");
  glShadingRateImagePaletteNV = (PFNGLSHADINGRATEIMAGEPALETTENVPROC)loadFunction(
      "glShadingRateImagePaletteNV");
  glShadingRateSampleOrderNV = (PFNGLSHADINGRATESAMPLEORDERNVPROC)loadFunction(
      "glShadingRateSampleOrderNV");
  glShadingRateSampleOrderCustomNV = (PFNGLSHADINGRATESAMPLEORDERCUSTOMNVPROC)loadFunction(
      "glShadingRateSampleOrderCustomNV");
  glSignalSemaphoreEXT = (PFNGLSIGNALSEMAPHOREEXTPROC)loadFunction("glSignalSemaphoreEXT");
  glSignalSemaphoreui64NVX = (PFNGLSIGNALSEMAPHOREUI64NVXPROC)loadFunction(
      "glSignalSemaphoreui64NVX");
  glSpecializeShader = (PFNGLSPECIALIZESHADERPROC)loadFunction("glSpecializeShader");
  glSpecializeShaderARB = (PFNGLSPECIALIZESHADERARBPROC)loadFunction("glSpecializeShaderARB");
  glStateCaptureNV = (PFNGLSTATECAPTURENVPROC)loadFunction("glStateCaptureNV");
  glStencilClearTagEXT = (PFNGLSTENCILCLEARTAGEXTPROC)loadFunction("glStencilClearTagEXT");
  glStencilFillPathInstancedNV = (PFNGLSTENCILFILLPATHINSTANCEDNVPROC)loadFunction(
      "glStencilFillPathInstancedNV");
  glStencilFillPathNV = (PFNGLSTENCILFILLPATHNVPROC)loadFunction("glStencilFillPathNV");
  glStencilFunc = (PFNGLSTENCILFUNCPROC)loadFunction("glStencilFunc");
  glStencilFuncSeparate = (PFNGLSTENCILFUNCSEPARATEPROC)loadFunction("glStencilFuncSeparate");
  glStencilMask = (PFNGLSTENCILMASKPROC)loadFunction("glStencilMask");
  glStencilMaskSeparate = (PFNGLSTENCILMASKSEPARATEPROC)loadFunction("glStencilMaskSeparate");
  glStencilOp = (PFNGLSTENCILOPPROC)loadFunction("glStencilOp");
  glStencilOpSeparate = (PFNGLSTENCILOPSEPARATEPROC)loadFunction("glStencilOpSeparate");
  glStencilOpValueAMD = (PFNGLSTENCILOPVALUEAMDPROC)loadFunction("glStencilOpValueAMD");
  glStencilStrokePathInstancedNV = (PFNGLSTENCILSTROKEPATHINSTANCEDNVPROC)loadFunction(
      "glStencilStrokePathInstancedNV");
  glStencilStrokePathNV = (PFNGLSTENCILSTROKEPATHNVPROC)loadFunction("glStencilStrokePathNV");
  glStencilThenCoverFillPathInstancedNV = (PFNGLSTENCILTHENCOVERFILLPATHINSTANCEDNVPROC)
      loadFunction("glStencilThenCoverFillPathInstancedNV");
  glStencilThenCoverFillPathNV = (PFNGLSTENCILTHENCOVERFILLPATHNVPROC)loadFunction(
      "glStencilThenCoverFillPathNV");
  glStencilThenCoverStrokePathInstancedNV = (PFNGLSTENCILTHENCOVERSTROKEPATHINSTANCEDNVPROC)
      loadFunction("glStencilThenCoverStrokePathInstancedNV");
  glStencilThenCoverStrokePathNV = (PFNGLSTENCILTHENCOVERSTROKEPATHNVPROC)loadFunction(
      "glStencilThenCoverStrokePathNV");
  glSubpixelPrecisionBiasNV = (PFNGLSUBPIXELPRECISIONBIASNVPROC)loadFunction(
      "glSubpixelPrecisionBiasNV");
  glSwizzleEXT = (PFNGLSWIZZLEEXTPROC)loadFunction("glSwizzleEXT");
  glSyncTextureINTEL = (PFNGLSYNCTEXTUREINTELPROC)loadFunction("glSyncTextureINTEL");
  glTangent3bEXT = (PFNGLTANGENT3BEXTPROC)loadFunction("glTangent3bEXT");
  glTangent3bvEXT = (PFNGLTANGENT3BVEXTPROC)loadFunction("glTangent3bvEXT");
  glTangent3dEXT = (PFNGLTANGENT3DEXTPROC)loadFunction("glTangent3dEXT");
  glTangent3dvEXT = (PFNGLTANGENT3DVEXTPROC)loadFunction("glTangent3dvEXT");
  glTangent3fEXT = (PFNGLTANGENT3FEXTPROC)loadFunction("glTangent3fEXT");
  glTangent3fvEXT = (PFNGLTANGENT3FVEXTPROC)loadFunction("glTangent3fvEXT");
  glTangent3iEXT = (PFNGLTANGENT3IEXTPROC)loadFunction("glTangent3iEXT");
  glTangent3ivEXT = (PFNGLTANGENT3IVEXTPROC)loadFunction("glTangent3ivEXT");
  glTangent3sEXT = (PFNGLTANGENT3SEXTPROC)loadFunction("glTangent3sEXT");
  glTangent3svEXT = (PFNGLTANGENT3SVEXTPROC)loadFunction("glTangent3svEXT");
  glTangentPointerEXT = (PFNGLTANGENTPOINTEREXTPROC)loadFunction("glTangentPointerEXT");
  glTessellationFactorAMD = (PFNGLTESSELLATIONFACTORAMDPROC)loadFunction(
      "glTessellationFactorAMD");
  glTessellationModeAMD = (PFNGLTESSELLATIONMODEAMDPROC)loadFunction("glTessellationModeAMD");
  glTestFenceAPPLE = (PFNGLTESTFENCEAPPLEPROC)loadFunction("glTestFenceAPPLE");
  glTestFenceNV = (PFNGLTESTFENCENVPROC)loadFunction("glTestFenceNV");
  glTestObjectAPPLE = (PFNGLTESTOBJECTAPPLEPROC)loadFunction("glTestObjectAPPLE");
  glTexAttachMemoryNV = (PFNGLTEXATTACHMEMORYNVPROC)loadFunction("glTexAttachMemoryNV");
  glTexBuffer = (PFNGLTEXBUFFERPROC)loadFunction("glTexBuffer");
  glTexBufferARB = (PFNGLTEXBUFFERARBPROC)loadFunction("glTexBufferARB");
  glTexBufferEXT = (PFNGLTEXBUFFEREXTPROC)loadFunction("glTexBufferEXT");
  glTexBufferRange = (PFNGLTEXBUFFERRANGEPROC)loadFunction("glTexBufferRange");
  glTexCoord1d = (PFNGLTEXCOORD1DPROC)loadFunction("glTexCoord1d");
  glTexCoord1dv = (PFNGLTEXCOORD1DVPROC)loadFunction("glTexCoord1dv");
  glTexCoord1f = (PFNGLTEXCOORD1FPROC)loadFunction("glTexCoord1f");
  glTexCoord1fv = (PFNGLTEXCOORD1FVPROC)loadFunction("glTexCoord1fv");
  glTexCoord1hNV = (PFNGLTEXCOORD1HNVPROC)loadFunction("glTexCoord1hNV");
  glTexCoord1hvNV = (PFNGLTEXCOORD1HVNVPROC)loadFunction("glTexCoord1hvNV");
  glTexCoord1i = (PFNGLTEXCOORD1IPROC)loadFunction("glTexCoord1i");
  glTexCoord1iv = (PFNGLTEXCOORD1IVPROC)loadFunction("glTexCoord1iv");
  glTexCoord1s = (PFNGLTEXCOORD1SPROC)loadFunction("glTexCoord1s");
  glTexCoord1sv = (PFNGLTEXCOORD1SVPROC)loadFunction("glTexCoord1sv");
  glTexCoord2d = (PFNGLTEXCOORD2DPROC)loadFunction("glTexCoord2d");
  glTexCoord2dv = (PFNGLTEXCOORD2DVPROC)loadFunction("glTexCoord2dv");
  glTexCoord2f = (PFNGLTEXCOORD2FPROC)loadFunction("glTexCoord2f");
  glTexCoord2fv = (PFNGLTEXCOORD2FVPROC)loadFunction("glTexCoord2fv");
  glTexCoord2hNV = (PFNGLTEXCOORD2HNVPROC)loadFunction("glTexCoord2hNV");
  glTexCoord2hvNV = (PFNGLTEXCOORD2HVNVPROC)loadFunction("glTexCoord2hvNV");
  glTexCoord2i = (PFNGLTEXCOORD2IPROC)loadFunction("glTexCoord2i");
  glTexCoord2iv = (PFNGLTEXCOORD2IVPROC)loadFunction("glTexCoord2iv");
  glTexCoord2s = (PFNGLTEXCOORD2SPROC)loadFunction("glTexCoord2s");
  glTexCoord2sv = (PFNGLTEXCOORD2SVPROC)loadFunction("glTexCoord2sv");
  glTexCoord3d = (PFNGLTEXCOORD3DPROC)loadFunction("glTexCoord3d");
  glTexCoord3dv = (PFNGLTEXCOORD3DVPROC)loadFunction("glTexCoord3dv");
  glTexCoord3f = (PFNGLTEXCOORD3FPROC)loadFunction("glTexCoord3f");
  glTexCoord3fv = (PFNGLTEXCOORD3FVPROC)loadFunction("glTexCoord3fv");
  glTexCoord3hNV = (PFNGLTEXCOORD3HNVPROC)loadFunction("glTexCoord3hNV");
  glTexCoord3hvNV = (PFNGLTEXCOORD3HVNVPROC)loadFunction("glTexCoord3hvNV");
  glTexCoord3i = (PFNGLTEXCOORD3IPROC)loadFunction("glTexCoord3i");
  glTexCoord3iv = (PFNGLTEXCOORD3IVPROC)loadFunction("glTexCoord3iv");
  glTexCoord3s = (PFNGLTEXCOORD3SPROC)loadFunction("glTexCoord3s");
  glTexCoord3sv = (PFNGLTEXCOORD3SVPROC)loadFunction("glTexCoord3sv");
  glTexCoord4d = (PFNGLTEXCOORD4DPROC)loadFunction("glTexCoord4d");
  glTexCoord4dv = (PFNGLTEXCOORD4DVPROC)loadFunction("glTexCoord4dv");
  glTexCoord4f = (PFNGLTEXCOORD4FPROC)loadFunction("glTexCoord4f");
  glTexCoord4fv = (PFNGLTEXCOORD4FVPROC)loadFunction("glTexCoord4fv");
  glTexCoord4hNV = (PFNGLTEXCOORD4HNVPROC)loadFunction("glTexCoord4hNV");
  glTexCoord4hvNV = (PFNGLTEXCOORD4HVNVPROC)loadFunction("glTexCoord4hvNV");
  glTexCoord4i = (PFNGLTEXCOORD4IPROC)loadFunction("glTexCoord4i");
  glTexCoord4iv = (PFNGLTEXCOORD4IVPROC)loadFunction("glTexCoord4iv");
  glTexCoord4s = (PFNGLTEXCOORD4SPROC)loadFunction("glTexCoord4s");
  glTexCoord4sv = (PFNGLTEXCOORD4SVPROC)loadFunction("glTexCoord4sv");
  glTexCoordFormatNV = (PFNGLTEXCOORDFORMATNVPROC)loadFunction("glTexCoordFormatNV");
  glTexCoordP1ui = (PFNGLTEXCOORDP1UIPROC)loadFunction("glTexCoordP1ui");
  glTexCoordP1uiv = (PFNGLTEXCOORDP1UIVPROC)loadFunction("glTexCoordP1uiv");
  glTexCoordP2ui = (PFNGLTEXCOORDP2UIPROC)loadFunction("glTexCoordP2ui");
  glTexCoordP2uiv = (PFNGLTEXCOORDP2UIVPROC)loadFunction("glTexCoordP2uiv");
  glTexCoordP3ui = (PFNGLTEXCOORDP3UIPROC)loadFunction("glTexCoordP3ui");
  glTexCoordP3uiv = (PFNGLTEXCOORDP3UIVPROC)loadFunction("glTexCoordP3uiv");
  glTexCoordP4ui = (PFNGLTEXCOORDP4UIPROC)loadFunction("glTexCoordP4ui");
  glTexCoordP4uiv = (PFNGLTEXCOORDP4UIVPROC)loadFunction("glTexCoordP4uiv");
  glTexCoordPointer = (PFNGLTEXCOORDPOINTERPROC)loadFunction("glTexCoordPointer");
  glTexCoordPointerEXT = (PFNGLTEXCOORDPOINTEREXTPROC)loadFunction("glTexCoordPointerEXT");
  glTexCoordPointervINTEL = (PFNGLTEXCOORDPOINTERVINTELPROC)loadFunction(
      "glTexCoordPointervINTEL");
  glTexEnvf = (PFNGLTEXENVFPROC)loadFunction("glTexEnvf");
  glTexEnvfv = (PFNGLTEXENVFVPROC)loadFunction("glTexEnvfv");
  glTexEnvi = (PFNGLTEXENVIPROC)loadFunction("glTexEnvi");
  glTexEnviv = (PFNGLTEXENVIVPROC)loadFunction("glTexEnviv");
  glTexGend = (PFNGLTEXGENDPROC)loadFunction("glTexGend");
  glTexGendv = (PFNGLTEXGENDVPROC)loadFunction("glTexGendv");
  glTexGenf = (PFNGLTEXGENFPROC)loadFunction("glTexGenf");
  glTexGenfv = (PFNGLTEXGENFVPROC)loadFunction("glTexGenfv");
  glTexGeni = (PFNGLTEXGENIPROC)loadFunction("glTexGeni");
  glTexGeniv = (PFNGLTEXGENIVPROC)loadFunction("glTexGeniv");
  glTexImage1D = (PFNGLTEXIMAGE1DPROC)loadFunction("glTexImage1D");
  glTexImage2D = (PFNGLTEXIMAGE2DPROC)loadFunction("glTexImage2D");
  glTexImage2DMultisample = (PFNGLTEXIMAGE2DMULTISAMPLEPROC)loadFunction(
      "glTexImage2DMultisample");
  glTexImage2DMultisampleCoverageNV = (PFNGLTEXIMAGE2DMULTISAMPLECOVERAGENVPROC)loadFunction(
      "glTexImage2DMultisampleCoverageNV");
  glTexImage3D = (PFNGLTEXIMAGE3DPROC)loadFunction("glTexImage3D");
  glTexImage3DEXT = (PFNGLTEXIMAGE3DEXTPROC)loadFunction("glTexImage3DEXT");
  glTexImage3DMultisample = (PFNGLTEXIMAGE3DMULTISAMPLEPROC)loadFunction(
      "glTexImage3DMultisample");
  glTexImage3DMultisampleCoverageNV = (PFNGLTEXIMAGE3DMULTISAMPLECOVERAGENVPROC)loadFunction(
      "glTexImage3DMultisampleCoverageNV");
  glTexPageCommitmentARB = (PFNGLTEXPAGECOMMITMENTARBPROC)loadFunction("glTexPageCommitmentARB");
  glTexPageCommitmentMemNV = (PFNGLTEXPAGECOMMITMENTMEMNVPROC)loadFunction(
      "glTexPageCommitmentMemNV");
  glTexParameterIiv = (PFNGLTEXPARAMETERIIVPROC)loadFunction("glTexParameterIiv");
  glTexParameterIivEXT = (PFNGLTEXPARAMETERIIVEXTPROC)loadFunction("glTexParameterIivEXT");
  glTexParameterIuiv = (PFNGLTEXPARAMETERIUIVPROC)loadFunction("glTexParameterIuiv");
  glTexParameterIuivEXT = (PFNGLTEXPARAMETERIUIVEXTPROC)loadFunction("glTexParameterIuivEXT");
  glTexParameterf = (PFNGLTEXPARAMETERFPROC)loadFunction("glTexParameterf");
  glTexParameterfv = (PFNGLTEXPARAMETERFVPROC)loadFunction("glTexParameterfv");
  glTexParameteri = (PFNGLTEXPARAMETERIPROC)loadFunction("glTexParameteri");
  glTexParameteriv = (PFNGLTEXPARAMETERIVPROC)loadFunction("glTexParameteriv");
  glTexRenderbufferNV = (PFNGLTEXRENDERBUFFERNVPROC)loadFunction("glTexRenderbufferNV");
  glTexStorage1D = (PFNGLTEXSTORAGE1DPROC)loadFunction("glTexStorage1D");
  glTexStorage2D = (PFNGLTEXSTORAGE2DPROC)loadFunction("glTexStorage2D");
  glTexStorage2DMultisample = (PFNGLTEXSTORAGE2DMULTISAMPLEPROC)loadFunction(
      "glTexStorage2DMultisample");
  glTexStorage3D = (PFNGLTEXSTORAGE3DPROC)loadFunction("glTexStorage3D");
  glTexStorage3DMultisample = (PFNGLTEXSTORAGE3DMULTISAMPLEPROC)loadFunction(
      "glTexStorage3DMultisample");
  glTexStorageMem1DEXT = (PFNGLTEXSTORAGEMEM1DEXTPROC)loadFunction("glTexStorageMem1DEXT");
  glTexStorageMem2DEXT = (PFNGLTEXSTORAGEMEM2DEXTPROC)loadFunction("glTexStorageMem2DEXT");
  glTexStorageMem2DMultisampleEXT = (PFNGLTEXSTORAGEMEM2DMULTISAMPLEEXTPROC)loadFunction(
      "glTexStorageMem2DMultisampleEXT");
  glTexStorageMem3DEXT = (PFNGLTEXSTORAGEMEM3DEXTPROC)loadFunction("glTexStorageMem3DEXT");
  glTexStorageMem3DMultisampleEXT = (PFNGLTEXSTORAGEMEM3DMULTISAMPLEEXTPROC)loadFunction(
      "glTexStorageMem3DMultisampleEXT");
  glTexStorageSparseAMD = (PFNGLTEXSTORAGESPARSEAMDPROC)loadFunction("glTexStorageSparseAMD");
  glTexSubImage1D = (PFNGLTEXSUBIMAGE1DPROC)loadFunction("glTexSubImage1D");
  glTexSubImage1DEXT = (PFNGLTEXSUBIMAGE1DEXTPROC)loadFunction("glTexSubImage1DEXT");
  glTexSubImage2D = (PFNGLTEXSUBIMAGE2DPROC)loadFunction("glTexSubImage2D");
  glTexSubImage2DEXT = (PFNGLTEXSUBIMAGE2DEXTPROC)loadFunction("glTexSubImage2DEXT");
  glTexSubImage3D = (PFNGLTEXSUBIMAGE3DPROC)loadFunction("glTexSubImage3D");
  glTexSubImage3DEXT = (PFNGLTEXSUBIMAGE3DEXTPROC)loadFunction("glTexSubImage3DEXT");
  glTextureAttachMemoryNV = (PFNGLTEXTUREATTACHMEMORYNVPROC)loadFunction(
      "glTextureAttachMemoryNV");
  glTextureBarrier = (PFNGLTEXTUREBARRIERPROC)loadFunction("glTextureBarrier");
  glTextureBarrierNV = (PFNGLTEXTUREBARRIERNVPROC)loadFunction("glTextureBarrierNV");
  glTextureBuffer = (PFNGLTEXTUREBUFFERPROC)loadFunction("glTextureBuffer");
  glTextureBufferEXT = (PFNGLTEXTUREBUFFEREXTPROC)loadFunction("glTextureBufferEXT");
  glTextureBufferRange = (PFNGLTEXTUREBUFFERRANGEPROC)loadFunction("glTextureBufferRange");
  glTextureBufferRangeEXT = (PFNGLTEXTUREBUFFERRANGEEXTPROC)loadFunction(
      "glTextureBufferRangeEXT");
  glTextureImage1DEXT = (PFNGLTEXTUREIMAGE1DEXTPROC)loadFunction("glTextureImage1DEXT");
  glTextureImage2DEXT = (PFNGLTEXTUREIMAGE2DEXTPROC)loadFunction("glTextureImage2DEXT");
  glTextureImage2DMultisampleCoverageNV = (PFNGLTEXTUREIMAGE2DMULTISAMPLECOVERAGENVPROC)
      loadFunction("glTextureImage2DMultisampleCoverageNV");
  glTextureImage2DMultisampleNV = (PFNGLTEXTUREIMAGE2DMULTISAMPLENVPROC)loadFunction(
      "glTextureImage2DMultisampleNV");
  glTextureImage3DEXT = (PFNGLTEXTUREIMAGE3DEXTPROC)loadFunction("glTextureImage3DEXT");
  glTextureImage3DMultisampleCoverageNV = (PFNGLTEXTUREIMAGE3DMULTISAMPLECOVERAGENVPROC)
      loadFunction("glTextureImage3DMultisampleCoverageNV");
  glTextureImage3DMultisampleNV = (PFNGLTEXTUREIMAGE3DMULTISAMPLENVPROC)loadFunction(
      "glTextureImage3DMultisampleNV");
  glTextureLightEXT = (PFNGLTEXTURELIGHTEXTPROC)loadFunction("glTextureLightEXT");
  glTextureMaterialEXT = (PFNGLTEXTUREMATERIALEXTPROC)loadFunction("glTextureMaterialEXT");
  glTextureNormalEXT = (PFNGLTEXTURENORMALEXTPROC)loadFunction("glTextureNormalEXT");
  glTexturePageCommitmentEXT = (PFNGLTEXTUREPAGECOMMITMENTEXTPROC)loadFunction(
      "glTexturePageCommitmentEXT");
  glTexturePageCommitmentMemNV = (PFNGLTEXTUREPAGECOMMITMENTMEMNVPROC)loadFunction(
      "glTexturePageCommitmentMemNV");
  glTextureParameterIiv = (PFNGLTEXTUREPARAMETERIIVPROC)loadFunction("glTextureParameterIiv");
  glTextureParameterIivEXT = (PFNGLTEXTUREPARAMETERIIVEXTPROC)loadFunction(
      "glTextureParameterIivEXT");
  glTextureParameterIuiv = (PFNGLTEXTUREPARAMETERIUIVPROC)loadFunction("glTextureParameterIuiv");
  glTextureParameterIuivEXT = (PFNGLTEXTUREPARAMETERIUIVEXTPROC)loadFunction(
      "glTextureParameterIuivEXT");
  glTextureParameterf = (PFNGLTEXTUREPARAMETERFPROC)loadFunction("glTextureParameterf");
  glTextureParameterfEXT = (PFNGLTEXTUREPARAMETERFEXTPROC)loadFunction("glTextureParameterfEXT");
  glTextureParameterfv = (PFNGLTEXTUREPARAMETERFVPROC)loadFunction("glTextureParameterfv");
  glTextureParameterfvEXT = (PFNGLTEXTUREPARAMETERFVEXTPROC)loadFunction(
      "glTextureParameterfvEXT");
  glTextureParameteri = (PFNGLTEXTUREPARAMETERIPROC)loadFunction("glTextureParameteri");
  glTextureParameteriEXT = (PFNGLTEXTUREPARAMETERIEXTPROC)loadFunction("glTextureParameteriEXT");
  glTextureParameteriv = (PFNGLTEXTUREPARAMETERIVPROC)loadFunction("glTextureParameteriv");
  glTextureParameterivEXT = (PFNGLTEXTUREPARAMETERIVEXTPROC)loadFunction(
      "glTextureParameterivEXT");
  glTextureRangeAPPLE = (PFNGLTEXTURERANGEAPPLEPROC)loadFunction("glTextureRangeAPPLE");
  glTextureRenderbufferEXT = (PFNGLTEXTURERENDERBUFFEREXTPROC)loadFunction(
      "glTextureRenderbufferEXT");
  glTextureStorage1D = (PFNGLTEXTURESTORAGE1DPROC)loadFunction("glTextureStorage1D");
  glTextureStorage1DEXT = (PFNGLTEXTURESTORAGE1DEXTPROC)loadFunction("glTextureStorage1DEXT");
  glTextureStorage2D = (PFNGLTEXTURESTORAGE2DPROC)loadFunction("glTextureStorage2D");
  glTextureStorage2DEXT = (PFNGLTEXTURESTORAGE2DEXTPROC)loadFunction("glTextureStorage2DEXT");
  glTextureStorage2DMultisample = (PFNGLTEXTURESTORAGE2DMULTISAMPLEPROC)loadFunction(
      "glTextureStorage2DMultisample");
  glTextureStorage2DMultisampleEXT = (PFNGLTEXTURESTORAGE2DMULTISAMPLEEXTPROC)loadFunction(
      "glTextureStorage2DMultisampleEXT");
  glTextureStorage3D = (PFNGLTEXTURESTORAGE3DPROC)loadFunction("glTextureStorage3D");
  glTextureStorage3DEXT = (PFNGLTEXTURESTORAGE3DEXTPROC)loadFunction("glTextureStorage3DEXT");
  glTextureStorage3DMultisample = (PFNGLTEXTURESTORAGE3DMULTISAMPLEPROC)loadFunction(
      "glTextureStorage3DMultisample");
  glTextureStorage3DMultisampleEXT = (PFNGLTEXTURESTORAGE3DMULTISAMPLEEXTPROC)loadFunction(
      "glTextureStorage3DMultisampleEXT");
  glTextureStorageMem1DEXT = (PFNGLTEXTURESTORAGEMEM1DEXTPROC)loadFunction(
      "glTextureStorageMem1DEXT");
  glTextureStorageMem2DEXT = (PFNGLTEXTURESTORAGEMEM2DEXTPROC)loadFunction(
      "glTextureStorageMem2DEXT");
  glTextureStorageMem2DMultisampleEXT = (PFNGLTEXTURESTORAGEMEM2DMULTISAMPLEEXTPROC)loadFunction(
      "glTextureStorageMem2DMultisampleEXT");
  glTextureStorageMem3DEXT = (PFNGLTEXTURESTORAGEMEM3DEXTPROC)loadFunction(
      "glTextureStorageMem3DEXT");
  glTextureStorageMem3DMultisampleEXT = (PFNGLTEXTURESTORAGEMEM3DMULTISAMPLEEXTPROC)loadFunction(
      "glTextureStorageMem3DMultisampleEXT");
  glTextureStorageSparseAMD = (PFNGLTEXTURESTORAGESPARSEAMDPROC)loadFunction(
      "glTextureStorageSparseAMD");
  glTextureSubImage1D = (PFNGLTEXTURESUBIMAGE1DPROC)loadFunction("glTextureSubImage1D");
  glTextureSubImage1DEXT = (PFNGLTEXTURESUBIMAGE1DEXTPROC)loadFunction("glTextureSubImage1DEXT");
  glTextureSubImage2D = (PFNGLTEXTURESUBIMAGE2DPROC)loadFunction("glTextureSubImage2D");
  glTextureSubImage2DEXT = (PFNGLTEXTURESUBIMAGE2DEXTPROC)loadFunction("glTextureSubImage2DEXT");
  glTextureSubImage3D = (PFNGLTEXTURESUBIMAGE3DPROC)loadFunction("glTextureSubImage3D");
  glTextureSubImage3DEXT = (PFNGLTEXTURESUBIMAGE3DEXTPROC)loadFunction("glTextureSubImage3DEXT");
  glTextureView = (PFNGLTEXTUREVIEWPROC)loadFunction("glTextureView");
  glTrackMatrixNV = (PFNGLTRACKMATRIXNVPROC)loadFunction("glTrackMatrixNV");
  glTransformFeedbackAttribsNV = (PFNGLTRANSFORMFEEDBACKATTRIBSNVPROC)loadFunction(
      "glTransformFeedbackAttribsNV");
  glTransformFeedbackBufferBase = (PFNGLTRANSFORMFEEDBACKBUFFERBASEPROC)loadFunction(
      "glTransformFeedbackBufferBase");
  glTransformFeedbackBufferRange = (PFNGLTRANSFORMFEEDBACKBUFFERRANGEPROC)loadFunction(
      "glTransformFeedbackBufferRange");
  glTransformFeedbackStreamAttribsNV = (PFNGLTRANSFORMFEEDBACKSTREAMATTRIBSNVPROC)loadFunction(
      "glTransformFeedbackStreamAttribsNV");
  glTransformFeedbackVaryings = (PFNGLTRANSFORMFEEDBACKVARYINGSPROC)loadFunction(
      "glTransformFeedbackVaryings");
  glTransformFeedbackVaryingsEXT = (PFNGLTRANSFORMFEEDBACKVARYINGSEXTPROC)loadFunction(
      "glTransformFeedbackVaryingsEXT");
  glTransformFeedbackVaryingsNV = (PFNGLTRANSFORMFEEDBACKVARYINGSNVPROC)loadFunction(
      "glTransformFeedbackVaryingsNV");
  glTransformPathNV = (PFNGLTRANSFORMPATHNVPROC)loadFunction("glTransformPathNV");
  glTranslated = (PFNGLTRANSLATEDPROC)loadFunction("glTranslated");
  glTranslatef = (PFNGLTRANSLATEFPROC)loadFunction("glTranslatef");
  glUniform1d = (PFNGLUNIFORM1DPROC)loadFunction("glUniform1d");
  glUniform1dv = (PFNGLUNIFORM1DVPROC)loadFunction("glUniform1dv");
  glUniform1f = (PFNGLUNIFORM1FPROC)loadFunction("glUniform1f");
  glUniform1fARB = (PFNGLUNIFORM1FARBPROC)loadFunction("glUniform1fARB");
  glUniform1fv = (PFNGLUNIFORM1FVPROC)loadFunction("glUniform1fv");
  glUniform1fvARB = (PFNGLUNIFORM1FVARBPROC)loadFunction("glUniform1fvARB");
  glUniform1i = (PFNGLUNIFORM1IPROC)loadFunction("glUniform1i");
  glUniform1i64ARB = (PFNGLUNIFORM1I64ARBPROC)loadFunction("glUniform1i64ARB");
  glUniform1i64NV = (PFNGLUNIFORM1I64NVPROC)loadFunction("glUniform1i64NV");
  glUniform1i64vARB = (PFNGLUNIFORM1I64VARBPROC)loadFunction("glUniform1i64vARB");
  glUniform1i64vNV = (PFNGLUNIFORM1I64VNVPROC)loadFunction("glUniform1i64vNV");
  glUniform1iARB = (PFNGLUNIFORM1IARBPROC)loadFunction("glUniform1iARB");
  glUniform1iv = (PFNGLUNIFORM1IVPROC)loadFunction("glUniform1iv");
  glUniform1ivARB = (PFNGLUNIFORM1IVARBPROC)loadFunction("glUniform1ivARB");
  glUniform1ui = (PFNGLUNIFORM1UIPROC)loadFunction("glUniform1ui");
  glUniform1ui64ARB = (PFNGLUNIFORM1UI64ARBPROC)loadFunction("glUniform1ui64ARB");
  glUniform1ui64NV = (PFNGLUNIFORM1UI64NVPROC)loadFunction("glUniform1ui64NV");
  glUniform1ui64vARB = (PFNGLUNIFORM1UI64VARBPROC)loadFunction("glUniform1ui64vARB");
  glUniform1ui64vNV = (PFNGLUNIFORM1UI64VNVPROC)loadFunction("glUniform1ui64vNV");
  glUniform1uiEXT = (PFNGLUNIFORM1UIEXTPROC)loadFunction("glUniform1uiEXT");
  glUniform1uiv = (PFNGLUNIFORM1UIVPROC)loadFunction("glUniform1uiv");
  glUniform1uivEXT = (PFNGLUNIFORM1UIVEXTPROC)loadFunction("glUniform1uivEXT");
  glUniform2d = (PFNGLUNIFORM2DPROC)loadFunction("glUniform2d");
  glUniform2dv = (PFNGLUNIFORM2DVPROC)loadFunction("glUniform2dv");
  glUniform2f = (PFNGLUNIFORM2FPROC)loadFunction("glUniform2f");
  glUniform2fARB = (PFNGLUNIFORM2FARBPROC)loadFunction("glUniform2fARB");
  glUniform2fv = (PFNGLUNIFORM2FVPROC)loadFunction("glUniform2fv");
  glUniform2fvARB = (PFNGLUNIFORM2FVARBPROC)loadFunction("glUniform2fvARB");
  glUniform2i = (PFNGLUNIFORM2IPROC)loadFunction("glUniform2i");
  glUniform2i64ARB = (PFNGLUNIFORM2I64ARBPROC)loadFunction("glUniform2i64ARB");
  glUniform2i64NV = (PFNGLUNIFORM2I64NVPROC)loadFunction("glUniform2i64NV");
  glUniform2i64vARB = (PFNGLUNIFORM2I64VARBPROC)loadFunction("glUniform2i64vARB");
  glUniform2i64vNV = (PFNGLUNIFORM2I64VNVPROC)loadFunction("glUniform2i64vNV");
  glUniform2iARB = (PFNGLUNIFORM2IARBPROC)loadFunction("glUniform2iARB");
  glUniform2iv = (PFNGLUNIFORM2IVPROC)loadFunction("glUniform2iv");
  glUniform2ivARB = (PFNGLUNIFORM2IVARBPROC)loadFunction("glUniform2ivARB");
  glUniform2ui = (PFNGLUNIFORM2UIPROC)loadFunction("glUniform2ui");
  glUniform2ui64ARB = (PFNGLUNIFORM2UI64ARBPROC)loadFunction("glUniform2ui64ARB");
  glUniform2ui64NV = (PFNGLUNIFORM2UI64NVPROC)loadFunction("glUniform2ui64NV");
  glUniform2ui64vARB = (PFNGLUNIFORM2UI64VARBPROC)loadFunction("glUniform2ui64vARB");
  glUniform2ui64vNV = (PFNGLUNIFORM2UI64VNVPROC)loadFunction("glUniform2ui64vNV");
  glUniform2uiEXT = (PFNGLUNIFORM2UIEXTPROC)loadFunction("glUniform2uiEXT");
  glUniform2uiv = (PFNGLUNIFORM2UIVPROC)loadFunction("glUniform2uiv");
  glUniform2uivEXT = (PFNGLUNIFORM2UIVEXTPROC)loadFunction("glUniform2uivEXT");
  glUniform3d = (PFNGLUNIFORM3DPROC)loadFunction("glUniform3d");
  glUniform3dv = (PFNGLUNIFORM3DVPROC)loadFunction("glUniform3dv");
  glUniform3f = (PFNGLUNIFORM3FPROC)loadFunction("glUniform3f");
  glUniform3fARB = (PFNGLUNIFORM3FARBPROC)loadFunction("glUniform3fARB");
  glUniform3fv = (PFNGLUNIFORM3FVPROC)loadFunction("glUniform3fv");
  glUniform3fvARB = (PFNGLUNIFORM3FVARBPROC)loadFunction("glUniform3fvARB");
  glUniform3i = (PFNGLUNIFORM3IPROC)loadFunction("glUniform3i");
  glUniform3i64ARB = (PFNGLUNIFORM3I64ARBPROC)loadFunction("glUniform3i64ARB");
  glUniform3i64NV = (PFNGLUNIFORM3I64NVPROC)loadFunction("glUniform3i64NV");
  glUniform3i64vARB = (PFNGLUNIFORM3I64VARBPROC)loadFunction("glUniform3i64vARB");
  glUniform3i64vNV = (PFNGLUNIFORM3I64VNVPROC)loadFunction("glUniform3i64vNV");
  glUniform3iARB = (PFNGLUNIFORM3IARBPROC)loadFunction("glUniform3iARB");
  glUniform3iv = (PFNGLUNIFORM3IVPROC)loadFunction("glUniform3iv");
  glUniform3ivARB = (PFNGLUNIFORM3IVARBPROC)loadFunction("glUniform3ivARB");
  glUniform3ui = (PFNGLUNIFORM3UIPROC)loadFunction("glUniform3ui");
  glUniform3ui64ARB = (PFNGLUNIFORM3UI64ARBPROC)loadFunction("glUniform3ui64ARB");
  glUniform3ui64NV = (PFNGLUNIFORM3UI64NVPROC)loadFunction("glUniform3ui64NV");
  glUniform3ui64vARB = (PFNGLUNIFORM3UI64VARBPROC)loadFunction("glUniform3ui64vARB");
  glUniform3ui64vNV = (PFNGLUNIFORM3UI64VNVPROC)loadFunction("glUniform3ui64vNV");
  glUniform3uiEXT = (PFNGLUNIFORM3UIEXTPROC)loadFunction("glUniform3uiEXT");
  glUniform3uiv = (PFNGLUNIFORM3UIVPROC)loadFunction("glUniform3uiv");
  glUniform3uivEXT = (PFNGLUNIFORM3UIVEXTPROC)loadFunction("glUniform3uivEXT");
  glUniform4d = (PFNGLUNIFORM4DPROC)loadFunction("glUniform4d");
  glUniform4dv = (PFNGLUNIFORM4DVPROC)loadFunction("glUniform4dv");
  glUniform4f = (PFNGLUNIFORM4FPROC)loadFunction("glUniform4f");
  glUniform4fARB = (PFNGLUNIFORM4FARBPROC)loadFunction("glUniform4fARB");
  glUniform4fv = (PFNGLUNIFORM4FVPROC)loadFunction("glUniform4fv");
  glUniform4fvARB = (PFNGLUNIFORM4FVARBPROC)loadFunction("glUniform4fvARB");
  glUniform4i = (PFNGLUNIFORM4IPROC)loadFunction("glUniform4i");
  glUniform4i64ARB = (PFNGLUNIFORM4I64ARBPROC)loadFunction("glUniform4i64ARB");
  glUniform4i64NV = (PFNGLUNIFORM4I64NVPROC)loadFunction("glUniform4i64NV");
  glUniform4i64vARB = (PFNGLUNIFORM4I64VARBPROC)loadFunction("glUniform4i64vARB");
  glUniform4i64vNV = (PFNGLUNIFORM4I64VNVPROC)loadFunction("glUniform4i64vNV");
  glUniform4iARB = (PFNGLUNIFORM4IARBPROC)loadFunction("glUniform4iARB");
  glUniform4iv = (PFNGLUNIFORM4IVPROC)loadFunction("glUniform4iv");
  glUniform4ivARB = (PFNGLUNIFORM4IVARBPROC)loadFunction("glUniform4ivARB");
  glUniform4ui = (PFNGLUNIFORM4UIPROC)loadFunction("glUniform4ui");
  glUniform4ui64ARB = (PFNGLUNIFORM4UI64ARBPROC)loadFunction("glUniform4ui64ARB");
  glUniform4ui64NV = (PFNGLUNIFORM4UI64NVPROC)loadFunction("glUniform4ui64NV");
  glUniform4ui64vARB = (PFNGLUNIFORM4UI64VARBPROC)loadFunction("glUniform4ui64vARB");
  glUniform4ui64vNV = (PFNGLUNIFORM4UI64VNVPROC)loadFunction("glUniform4ui64vNV");
  glUniform4uiEXT = (PFNGLUNIFORM4UIEXTPROC)loadFunction("glUniform4uiEXT");
  glUniform4uiv = (PFNGLUNIFORM4UIVPROC)loadFunction("glUniform4uiv");
  glUniform4uivEXT = (PFNGLUNIFORM4UIVEXTPROC)loadFunction("glUniform4uivEXT");
  glUniformBlockBinding = (PFNGLUNIFORMBLOCKBINDINGPROC)loadFunction("glUniformBlockBinding");
  glUniformBufferEXT = (PFNGLUNIFORMBUFFEREXTPROC)loadFunction("glUniformBufferEXT");
  glUniformHandleui64ARB = (PFNGLUNIFORMHANDLEUI64ARBPROC)loadFunction("glUniformHandleui64ARB");
  glUniformHandleui64NV = (PFNGLUNIFORMHANDLEUI64NVPROC)loadFunction("glUniformHandleui64NV");
  glUniformHandleui64vARB = (PFNGLUNIFORMHANDLEUI64VARBPROC)loadFunction(
      "glUniformHandleui64vARB");
  glUniformHandleui64vNV = (PFNGLUNIFORMHANDLEUI64VNVPROC)loadFunction("glUniformHandleui64vNV");
  glUniformMatrix2dv = (PFNGLUNIFORMMATRIX2DVPROC)loadFunction("glUniformMatrix2dv");
  glUniformMatrix2fv = (PFNGLUNIFORMMATRIX2FVPROC)loadFunction("glUniformMatrix2fv");
  glUniformMatrix2fvARB = (PFNGLUNIFORMMATRIX2FVARBPROC)loadFunction("glUniformMatrix2fvARB");
  glUniformMatrix2x3dv = (PFNGLUNIFORMMATRIX2X3DVPROC)loadFunction("glUniformMatrix2x3dv");
  glUniformMatrix2x3fv = (PFNGLUNIFORMMATRIX2X3FVPROC)loadFunction("glUniformMatrix2x3fv");
  glUniformMatrix2x4dv = (PFNGLUNIFORMMATRIX2X4DVPROC)loadFunction("glUniformMatrix2x4dv");
  glUniformMatrix2x4fv = (PFNGLUNIFORMMATRIX2X4FVPROC)loadFunction("glUniformMatrix2x4fv");
  glUniformMatrix3dv = (PFNGLUNIFORMMATRIX3DVPROC)loadFunction("glUniformMatrix3dv");
  glUniformMatrix3fv = (PFNGLUNIFORMMATRIX3FVPROC)loadFunction("glUniformMatrix3fv");
  glUniformMatrix3fvARB = (PFNGLUNIFORMMATRIX3FVARBPROC)loadFunction("glUniformMatrix3fvARB");
  glUniformMatrix3x2dv = (PFNGLUNIFORMMATRIX3X2DVPROC)loadFunction("glUniformMatrix3x2dv");
  glUniformMatrix3x2fv = (PFNGLUNIFORMMATRIX3X2FVPROC)loadFunction("glUniformMatrix3x2fv");
  glUniformMatrix3x4dv = (PFNGLUNIFORMMATRIX3X4DVPROC)loadFunction("glUniformMatrix3x4dv");
  glUniformMatrix3x4fv = (PFNGLUNIFORMMATRIX3X4FVPROC)loadFunction("glUniformMatrix3x4fv");
  glUniformMatrix4dv = (PFNGLUNIFORMMATRIX4DVPROC)loadFunction("glUniformMatrix4dv");
  glUniformMatrix4fv = (PFNGLUNIFORMMATRIX4FVPROC)loadFunction("glUniformMatrix4fv");
  glUniformMatrix4fvARB = (PFNGLUNIFORMMATRIX4FVARBPROC)loadFunction("glUniformMatrix4fvARB");
  glUniformMatrix4x2dv = (PFNGLUNIFORMMATRIX4X2DVPROC)loadFunction("glUniformMatrix4x2dv");
  glUniformMatrix4x2fv = (PFNGLUNIFORMMATRIX4X2FVPROC)loadFunction("glUniformMatrix4x2fv");
  glUniformMatrix4x3dv = (PFNGLUNIFORMMATRIX4X3DVPROC)loadFunction("glUniformMatrix4x3dv");
  glUniformMatrix4x3fv = (PFNGLUNIFORMMATRIX4X3FVPROC)loadFunction("glUniformMatrix4x3fv");
  glUniformSubroutinesuiv = (PFNGLUNIFORMSUBROUTINESUIVPROC)loadFunction(
      "glUniformSubroutinesuiv");
  glUniformui64NV = (PFNGLUNIFORMUI64NVPROC)loadFunction("glUniformui64NV");
  glUniformui64vNV = (PFNGLUNIFORMUI64VNVPROC)loadFunction("glUniformui64vNV");
  glUnlockArraysEXT = (PFNGLUNLOCKARRAYSEXTPROC)loadFunction("glUnlockArraysEXT");
  glUnmapBuffer = (PFNGLUNMAPBUFFERPROC)loadFunction("glUnmapBuffer");
  glUnmapBufferARB = (PFNGLUNMAPBUFFERARBPROC)loadFunction("glUnmapBufferARB");
  glUnmapNamedBuffer = (PFNGLUNMAPNAMEDBUFFERPROC)loadFunction("glUnmapNamedBuffer");
  glUnmapNamedBufferEXT = (PFNGLUNMAPNAMEDBUFFEREXTPROC)loadFunction("glUnmapNamedBufferEXT");
  glUnmapTexture2DINTEL = (PFNGLUNMAPTEXTURE2DINTELPROC)loadFunction("glUnmapTexture2DINTEL");
  glUploadGpuMaskNVX = (PFNGLUPLOADGPUMASKNVXPROC)loadFunction("glUploadGpuMaskNVX");
  glUseProgram = (PFNGLUSEPROGRAMPROC)loadFunction("glUseProgram");
  glUseProgramObjectARB = (PFNGLUSEPROGRAMOBJECTARBPROC)loadFunction("glUseProgramObjectARB");
  glUseProgramStages = (PFNGLUSEPROGRAMSTAGESPROC)loadFunction("glUseProgramStages");
  glUseProgramStagesEXT = (PFNGLUSEPROGRAMSTAGESEXTPROC)loadFunction("glUseProgramStagesEXT");
  glUseShaderProgramEXT = (PFNGLUSESHADERPROGRAMEXTPROC)loadFunction("glUseShaderProgramEXT");
  glVDPAUFiniNV = (PFNGLVDPAUFININVPROC)loadFunction("glVDPAUFiniNV");
  glVDPAUGetSurfaceivNV = (PFNGLVDPAUGETSURFACEIVNVPROC)loadFunction("glVDPAUGetSurfaceivNV");
  glVDPAUInitNV = (PFNGLVDPAUINITNVPROC)loadFunction("glVDPAUInitNV");
  glVDPAUIsSurfaceNV = (PFNGLVDPAUISSURFACENVPROC)loadFunction("glVDPAUIsSurfaceNV");
  glVDPAUMapSurfacesNV = (PFNGLVDPAUMAPSURFACESNVPROC)loadFunction("glVDPAUMapSurfacesNV");
  glVDPAURegisterOutputSurfaceNV = (PFNGLVDPAUREGISTEROUTPUTSURFACENVPROC)loadFunction(
      "glVDPAURegisterOutputSurfaceNV");
  glVDPAURegisterVideoSurfaceNV = (PFNGLVDPAUREGISTERVIDEOSURFACENVPROC)loadFunction(
      "glVDPAURegisterVideoSurfaceNV");
  glVDPAURegisterVideoSurfaceWithPictureStructureNV =
      (PFNGLVDPAUREGISTERVIDEOSURFACEWITHPICTURESTRUCTURENVPROC)loadFunction(
          "glVDPAURegisterVideoSurfaceWithPictureStructureNV");
  glVDPAUSurfaceAccessNV = (PFNGLVDPAUSURFACEACCESSNVPROC)loadFunction("glVDPAUSurfaceAccessNV");
  glVDPAUUnmapSurfacesNV = (PFNGLVDPAUUNMAPSURFACESNVPROC)loadFunction("glVDPAUUnmapSurfacesNV");
  glVDPAUUnregisterSurfaceNV = (PFNGLVDPAUUNREGISTERSURFACENVPROC)loadFunction(
      "glVDPAUUnregisterSurfaceNV");
  glValidateProgram = (PFNGLVALIDATEPROGRAMPROC)loadFunction("glValidateProgram");
  glValidateProgramARB = (PFNGLVALIDATEPROGRAMARBPROC)loadFunction("glValidateProgramARB");
  glValidateProgramPipeline = (PFNGLVALIDATEPROGRAMPIPELINEPROC)loadFunction(
      "glValidateProgramPipeline");
  glValidateProgramPipelineEXT = (PFNGLVALIDATEPROGRAMPIPELINEEXTPROC)loadFunction(
      "glValidateProgramPipelineEXT");
  glVariantPointerEXT = (PFNGLVARIANTPOINTEREXTPROC)loadFunction("glVariantPointerEXT");
  glVariantbvEXT = (PFNGLVARIANTBVEXTPROC)loadFunction("glVariantbvEXT");
  glVariantdvEXT = (PFNGLVARIANTDVEXTPROC)loadFunction("glVariantdvEXT");
  glVariantfvEXT = (PFNGLVARIANTFVEXTPROC)loadFunction("glVariantfvEXT");
  glVariantivEXT = (PFNGLVARIANTIVEXTPROC)loadFunction("glVariantivEXT");
  glVariantsvEXT = (PFNGLVARIANTSVEXTPROC)loadFunction("glVariantsvEXT");
  glVariantubvEXT = (PFNGLVARIANTUBVEXTPROC)loadFunction("glVariantubvEXT");
  glVariantuivEXT = (PFNGLVARIANTUIVEXTPROC)loadFunction("glVariantuivEXT");
  glVariantusvEXT = (PFNGLVARIANTUSVEXTPROC)loadFunction("glVariantusvEXT");
  glVertex2d = (PFNGLVERTEX2DPROC)loadFunction("glVertex2d");
  glVertex2dv = (PFNGLVERTEX2DVPROC)loadFunction("glVertex2dv");
  glVertex2f = (PFNGLVERTEX2FPROC)loadFunction("glVertex2f");
  glVertex2fv = (PFNGLVERTEX2FVPROC)loadFunction("glVertex2fv");
  glVertex2hNV = (PFNGLVERTEX2HNVPROC)loadFunction("glVertex2hNV");
  glVertex2hvNV = (PFNGLVERTEX2HVNVPROC)loadFunction("glVertex2hvNV");
  glVertex2i = (PFNGLVERTEX2IPROC)loadFunction("glVertex2i");
  glVertex2iv = (PFNGLVERTEX2IVPROC)loadFunction("glVertex2iv");
  glVertex2s = (PFNGLVERTEX2SPROC)loadFunction("glVertex2s");
  glVertex2sv = (PFNGLVERTEX2SVPROC)loadFunction("glVertex2sv");
  glVertex3d = (PFNGLVERTEX3DPROC)loadFunction("glVertex3d");
  glVertex3dv = (PFNGLVERTEX3DVPROC)loadFunction("glVertex3dv");
  glVertex3f = (PFNGLVERTEX3FPROC)loadFunction("glVertex3f");
  glVertex3fv = (PFNGLVERTEX3FVPROC)loadFunction("glVertex3fv");
  glVertex3hNV = (PFNGLVERTEX3HNVPROC)loadFunction("glVertex3hNV");
  glVertex3hvNV = (PFNGLVERTEX3HVNVPROC)loadFunction("glVertex3hvNV");
  glVertex3i = (PFNGLVERTEX3IPROC)loadFunction("glVertex3i");
  glVertex3iv = (PFNGLVERTEX3IVPROC)loadFunction("glVertex3iv");
  glVertex3s = (PFNGLVERTEX3SPROC)loadFunction("glVertex3s");
  glVertex3sv = (PFNGLVERTEX3SVPROC)loadFunction("glVertex3sv");
  glVertex4d = (PFNGLVERTEX4DPROC)loadFunction("glVertex4d");
  glVertex4dv = (PFNGLVERTEX4DVPROC)loadFunction("glVertex4dv");
  glVertex4f = (PFNGLVERTEX4FPROC)loadFunction("glVertex4f");
  glVertex4fv = (PFNGLVERTEX4FVPROC)loadFunction("glVertex4fv");
  glVertex4hNV = (PFNGLVERTEX4HNVPROC)loadFunction("glVertex4hNV");
  glVertex4hvNV = (PFNGLVERTEX4HVNVPROC)loadFunction("glVertex4hvNV");
  glVertex4i = (PFNGLVERTEX4IPROC)loadFunction("glVertex4i");
  glVertex4iv = (PFNGLVERTEX4IVPROC)loadFunction("glVertex4iv");
  glVertex4s = (PFNGLVERTEX4SPROC)loadFunction("glVertex4s");
  glVertex4sv = (PFNGLVERTEX4SVPROC)loadFunction("glVertex4sv");
  glVertexArrayAttribBinding = (PFNGLVERTEXARRAYATTRIBBINDINGPROC)loadFunction(
      "glVertexArrayAttribBinding");
  glVertexArrayAttribFormat = (PFNGLVERTEXARRAYATTRIBFORMATPROC)loadFunction(
      "glVertexArrayAttribFormat");
  glVertexArrayAttribIFormat = (PFNGLVERTEXARRAYATTRIBIFORMATPROC)loadFunction(
      "glVertexArrayAttribIFormat");
  glVertexArrayAttribLFormat = (PFNGLVERTEXARRAYATTRIBLFORMATPROC)loadFunction(
      "glVertexArrayAttribLFormat");
  glVertexArrayBindVertexBufferEXT = (PFNGLVERTEXARRAYBINDVERTEXBUFFEREXTPROC)loadFunction(
      "glVertexArrayBindVertexBufferEXT");
  glVertexArrayBindingDivisor = (PFNGLVERTEXARRAYBINDINGDIVISORPROC)loadFunction(
      "glVertexArrayBindingDivisor");
  glVertexArrayColorOffsetEXT = (PFNGLVERTEXARRAYCOLOROFFSETEXTPROC)loadFunction(
      "glVertexArrayColorOffsetEXT");
  glVertexArrayEdgeFlagOffsetEXT = (PFNGLVERTEXARRAYEDGEFLAGOFFSETEXTPROC)loadFunction(
      "glVertexArrayEdgeFlagOffsetEXT");
  glVertexArrayElementBuffer = (PFNGLVERTEXARRAYELEMENTBUFFERPROC)loadFunction(
      "glVertexArrayElementBuffer");
  glVertexArrayFogCoordOffsetEXT = (PFNGLVERTEXARRAYFOGCOORDOFFSETEXTPROC)loadFunction(
      "glVertexArrayFogCoordOffsetEXT");
  glVertexArrayIndexOffsetEXT = (PFNGLVERTEXARRAYINDEXOFFSETEXTPROC)loadFunction(
      "glVertexArrayIndexOffsetEXT");
  glVertexArrayMultiTexCoordOffsetEXT = (PFNGLVERTEXARRAYMULTITEXCOORDOFFSETEXTPROC)loadFunction(
      "glVertexArrayMultiTexCoordOffsetEXT");
  glVertexArrayNormalOffsetEXT = (PFNGLVERTEXARRAYNORMALOFFSETEXTPROC)loadFunction(
      "glVertexArrayNormalOffsetEXT");
  glVertexArrayParameteriAPPLE = (PFNGLVERTEXARRAYPARAMETERIAPPLEPROC)loadFunction(
      "glVertexArrayParameteriAPPLE");
  glVertexArrayRangeAPPLE = (PFNGLVERTEXARRAYRANGEAPPLEPROC)loadFunction(
      "glVertexArrayRangeAPPLE");
  glVertexArrayRangeNV = (PFNGLVERTEXARRAYRANGENVPROC)loadFunction("glVertexArrayRangeNV");
  glVertexArraySecondaryColorOffsetEXT = (PFNGLVERTEXARRAYSECONDARYCOLOROFFSETEXTPROC)loadFunction(
      "glVertexArraySecondaryColorOffsetEXT");
  glVertexArrayTexCoordOffsetEXT = (PFNGLVERTEXARRAYTEXCOORDOFFSETEXTPROC)loadFunction(
      "glVertexArrayTexCoordOffsetEXT");
  glVertexArrayVertexAttribBindingEXT = (PFNGLVERTEXARRAYVERTEXATTRIBBINDINGEXTPROC)loadFunction(
      "glVertexArrayVertexAttribBindingEXT");
  glVertexArrayVertexAttribDivisorEXT = (PFNGLVERTEXARRAYVERTEXATTRIBDIVISOREXTPROC)loadFunction(
      "glVertexArrayVertexAttribDivisorEXT");
  glVertexArrayVertexAttribFormatEXT = (PFNGLVERTEXARRAYVERTEXATTRIBFORMATEXTPROC)loadFunction(
      "glVertexArrayVertexAttribFormatEXT");
  glVertexArrayVertexAttribIFormatEXT = (PFNGLVERTEXARRAYVERTEXATTRIBIFORMATEXTPROC)loadFunction(
      "glVertexArrayVertexAttribIFormatEXT");
  glVertexArrayVertexAttribIOffsetEXT = (PFNGLVERTEXARRAYVERTEXATTRIBIOFFSETEXTPROC)loadFunction(
      "glVertexArrayVertexAttribIOffsetEXT");
  glVertexArrayVertexAttribLFormatEXT = (PFNGLVERTEXARRAYVERTEXATTRIBLFORMATEXTPROC)loadFunction(
      "glVertexArrayVertexAttribLFormatEXT");
  glVertexArrayVertexAttribLOffsetEXT = (PFNGLVERTEXARRAYVERTEXATTRIBLOFFSETEXTPROC)loadFunction(
      "glVertexArrayVertexAttribLOffsetEXT");
  glVertexArrayVertexAttribOffsetEXT = (PFNGLVERTEXARRAYVERTEXATTRIBOFFSETEXTPROC)loadFunction(
      "glVertexArrayVertexAttribOffsetEXT");
  glVertexArrayVertexBindingDivisorEXT = (PFNGLVERTEXARRAYVERTEXBINDINGDIVISOREXTPROC)loadFunction(
      "glVertexArrayVertexBindingDivisorEXT");
  glVertexArrayVertexBuffer = (PFNGLVERTEXARRAYVERTEXBUFFERPROC)loadFunction(
      "glVertexArrayVertexBuffer");
  glVertexArrayVertexBuffers = (PFNGLVERTEXARRAYVERTEXBUFFERSPROC)loadFunction(
      "glVertexArrayVertexBuffers");
  glVertexArrayVertexOffsetEXT = (PFNGLVERTEXARRAYVERTEXOFFSETEXTPROC)loadFunction(
      "glVertexArrayVertexOffsetEXT");
  glVertexAttrib1d = (PFNGLVERTEXATTRIB1DPROC)loadFunction("glVertexAttrib1d");
  glVertexAttrib1dARB = (PFNGLVERTEXATTRIB1DARBPROC)loadFunction("glVertexAttrib1dARB");
  glVertexAttrib1dNV = (PFNGLVERTEXATTRIB1DNVPROC)loadFunction("glVertexAttrib1dNV");
  glVertexAttrib1dv = (PFNGLVERTEXATTRIB1DVPROC)loadFunction("glVertexAttrib1dv");
  glVertexAttrib1dvARB = (PFNGLVERTEXATTRIB1DVARBPROC)loadFunction("glVertexAttrib1dvARB");
  glVertexAttrib1dvNV = (PFNGLVERTEXATTRIB1DVNVPROC)loadFunction("glVertexAttrib1dvNV");
  glVertexAttrib1f = (PFNGLVERTEXATTRIB1FPROC)loadFunction("glVertexAttrib1f");
  glVertexAttrib1fARB = (PFNGLVERTEXATTRIB1FARBPROC)loadFunction("glVertexAttrib1fARB");
  glVertexAttrib1fNV = (PFNGLVERTEXATTRIB1FNVPROC)loadFunction("glVertexAttrib1fNV");
  glVertexAttrib1fv = (PFNGLVERTEXATTRIB1FVPROC)loadFunction("glVertexAttrib1fv");
  glVertexAttrib1fvARB = (PFNGLVERTEXATTRIB1FVARBPROC)loadFunction("glVertexAttrib1fvARB");
  glVertexAttrib1fvNV = (PFNGLVERTEXATTRIB1FVNVPROC)loadFunction("glVertexAttrib1fvNV");
  glVertexAttrib1hNV = (PFNGLVERTEXATTRIB1HNVPROC)loadFunction("glVertexAttrib1hNV");
  glVertexAttrib1hvNV = (PFNGLVERTEXATTRIB1HVNVPROC)loadFunction("glVertexAttrib1hvNV");
  glVertexAttrib1s = (PFNGLVERTEXATTRIB1SPROC)loadFunction("glVertexAttrib1s");
  glVertexAttrib1sARB = (PFNGLVERTEXATTRIB1SARBPROC)loadFunction("glVertexAttrib1sARB");
  glVertexAttrib1sNV = (PFNGLVERTEXATTRIB1SNVPROC)loadFunction("glVertexAttrib1sNV");
  glVertexAttrib1sv = (PFNGLVERTEXATTRIB1SVPROC)loadFunction("glVertexAttrib1sv");
  glVertexAttrib1svARB = (PFNGLVERTEXATTRIB1SVARBPROC)loadFunction("glVertexAttrib1svARB");
  glVertexAttrib1svNV = (PFNGLVERTEXATTRIB1SVNVPROC)loadFunction("glVertexAttrib1svNV");
  glVertexAttrib2d = (PFNGLVERTEXATTRIB2DPROC)loadFunction("glVertexAttrib2d");
  glVertexAttrib2dARB = (PFNGLVERTEXATTRIB2DARBPROC)loadFunction("glVertexAttrib2dARB");
  glVertexAttrib2dNV = (PFNGLVERTEXATTRIB2DNVPROC)loadFunction("glVertexAttrib2dNV");
  glVertexAttrib2dv = (PFNGLVERTEXATTRIB2DVPROC)loadFunction("glVertexAttrib2dv");
  glVertexAttrib2dvARB = (PFNGLVERTEXATTRIB2DVARBPROC)loadFunction("glVertexAttrib2dvARB");
  glVertexAttrib2dvNV = (PFNGLVERTEXATTRIB2DVNVPROC)loadFunction("glVertexAttrib2dvNV");
  glVertexAttrib2f = (PFNGLVERTEXATTRIB2FPROC)loadFunction("glVertexAttrib2f");
  glVertexAttrib2fARB = (PFNGLVERTEXATTRIB2FARBPROC)loadFunction("glVertexAttrib2fARB");
  glVertexAttrib2fNV = (PFNGLVERTEXATTRIB2FNVPROC)loadFunction("glVertexAttrib2fNV");
  glVertexAttrib2fv = (PFNGLVERTEXATTRIB2FVPROC)loadFunction("glVertexAttrib2fv");
  glVertexAttrib2fvARB = (PFNGLVERTEXATTRIB2FVARBPROC)loadFunction("glVertexAttrib2fvARB");
  glVertexAttrib2fvNV = (PFNGLVERTEXATTRIB2FVNVPROC)loadFunction("glVertexAttrib2fvNV");
  glVertexAttrib2hNV = (PFNGLVERTEXATTRIB2HNVPROC)loadFunction("glVertexAttrib2hNV");
  glVertexAttrib2hvNV = (PFNGLVERTEXATTRIB2HVNVPROC)loadFunction("glVertexAttrib2hvNV");
  glVertexAttrib2s = (PFNGLVERTEXATTRIB2SPROC)loadFunction("glVertexAttrib2s");
  glVertexAttrib2sARB = (PFNGLVERTEXATTRIB2SARBPROC)loadFunction("glVertexAttrib2sARB");
  glVertexAttrib2sNV = (PFNGLVERTEXATTRIB2SNVPROC)loadFunction("glVertexAttrib2sNV");
  glVertexAttrib2sv = (PFNGLVERTEXATTRIB2SVPROC)loadFunction("glVertexAttrib2sv");
  glVertexAttrib2svARB = (PFNGLVERTEXATTRIB2SVARBPROC)loadFunction("glVertexAttrib2svARB");
  glVertexAttrib2svNV = (PFNGLVERTEXATTRIB2SVNVPROC)loadFunction("glVertexAttrib2svNV");
  glVertexAttrib3d = (PFNGLVERTEXATTRIB3DPROC)loadFunction("glVertexAttrib3d");
  glVertexAttrib3dARB = (PFNGLVERTEXATTRIB3DARBPROC)loadFunction("glVertexAttrib3dARB");
  glVertexAttrib3dNV = (PFNGLVERTEXATTRIB3DNVPROC)loadFunction("glVertexAttrib3dNV");
  glVertexAttrib3dv = (PFNGLVERTEXATTRIB3DVPROC)loadFunction("glVertexAttrib3dv");
  glVertexAttrib3dvARB = (PFNGLVERTEXATTRIB3DVARBPROC)loadFunction("glVertexAttrib3dvARB");
  glVertexAttrib3dvNV = (PFNGLVERTEXATTRIB3DVNVPROC)loadFunction("glVertexAttrib3dvNV");
  glVertexAttrib3f = (PFNGLVERTEXATTRIB3FPROC)loadFunction("glVertexAttrib3f");
  glVertexAttrib3fARB = (PFNGLVERTEXATTRIB3FARBPROC)loadFunction("glVertexAttrib3fARB");
  glVertexAttrib3fNV = (PFNGLVERTEXATTRIB3FNVPROC)loadFunction("glVertexAttrib3fNV");
  glVertexAttrib3fv = (PFNGLVERTEXATTRIB3FVPROC)loadFunction("glVertexAttrib3fv");
  glVertexAttrib3fvARB = (PFNGLVERTEXATTRIB3FVARBPROC)loadFunction("glVertexAttrib3fvARB");
  glVertexAttrib3fvNV = (PFNGLVERTEXATTRIB3FVNVPROC)loadFunction("glVertexAttrib3fvNV");
  glVertexAttrib3hNV = (PFNGLVERTEXATTRIB3HNVPROC)loadFunction("glVertexAttrib3hNV");
  glVertexAttrib3hvNV = (PFNGLVERTEXATTRIB3HVNVPROC)loadFunction("glVertexAttrib3hvNV");
  glVertexAttrib3s = (PFNGLVERTEXATTRIB3SPROC)loadFunction("glVertexAttrib3s");
  glVertexAttrib3sARB = (PFNGLVERTEXATTRIB3SARBPROC)loadFunction("glVertexAttrib3sARB");
  glVertexAttrib3sNV = (PFNGLVERTEXATTRIB3SNVPROC)loadFunction("glVertexAttrib3sNV");
  glVertexAttrib3sv = (PFNGLVERTEXATTRIB3SVPROC)loadFunction("glVertexAttrib3sv");
  glVertexAttrib3svARB = (PFNGLVERTEXATTRIB3SVARBPROC)loadFunction("glVertexAttrib3svARB");
  glVertexAttrib3svNV = (PFNGLVERTEXATTRIB3SVNVPROC)loadFunction("glVertexAttrib3svNV");
  glVertexAttrib4Nbv = (PFNGLVERTEXATTRIB4NBVPROC)loadFunction("glVertexAttrib4Nbv");
  glVertexAttrib4NbvARB = (PFNGLVERTEXATTRIB4NBVARBPROC)loadFunction("glVertexAttrib4NbvARB");
  glVertexAttrib4Niv = (PFNGLVERTEXATTRIB4NIVPROC)loadFunction("glVertexAttrib4Niv");
  glVertexAttrib4NivARB = (PFNGLVERTEXATTRIB4NIVARBPROC)loadFunction("glVertexAttrib4NivARB");
  glVertexAttrib4Nsv = (PFNGLVERTEXATTRIB4NSVPROC)loadFunction("glVertexAttrib4Nsv");
  glVertexAttrib4NsvARB = (PFNGLVERTEXATTRIB4NSVARBPROC)loadFunction("glVertexAttrib4NsvARB");
  glVertexAttrib4Nub = (PFNGLVERTEXATTRIB4NUBPROC)loadFunction("glVertexAttrib4Nub");
  glVertexAttrib4NubARB = (PFNGLVERTEXATTRIB4NUBARBPROC)loadFunction("glVertexAttrib4NubARB");
  glVertexAttrib4Nubv = (PFNGLVERTEXATTRIB4NUBVPROC)loadFunction("glVertexAttrib4Nubv");
  glVertexAttrib4NubvARB = (PFNGLVERTEXATTRIB4NUBVARBPROC)loadFunction("glVertexAttrib4NubvARB");
  glVertexAttrib4Nuiv = (PFNGLVERTEXATTRIB4NUIVPROC)loadFunction("glVertexAttrib4Nuiv");
  glVertexAttrib4NuivARB = (PFNGLVERTEXATTRIB4NUIVARBPROC)loadFunction("glVertexAttrib4NuivARB");
  glVertexAttrib4Nusv = (PFNGLVERTEXATTRIB4NUSVPROC)loadFunction("glVertexAttrib4Nusv");
  glVertexAttrib4NusvARB = (PFNGLVERTEXATTRIB4NUSVARBPROC)loadFunction("glVertexAttrib4NusvARB");
  glVertexAttrib4bv = (PFNGLVERTEXATTRIB4BVPROC)loadFunction("glVertexAttrib4bv");
  glVertexAttrib4bvARB = (PFNGLVERTEXATTRIB4BVARBPROC)loadFunction("glVertexAttrib4bvARB");
  glVertexAttrib4d = (PFNGLVERTEXATTRIB4DPROC)loadFunction("glVertexAttrib4d");
  glVertexAttrib4dARB = (PFNGLVERTEXATTRIB4DARBPROC)loadFunction("glVertexAttrib4dARB");
  glVertexAttrib4dNV = (PFNGLVERTEXATTRIB4DNVPROC)loadFunction("glVertexAttrib4dNV");
  glVertexAttrib4dv = (PFNGLVERTEXATTRIB4DVPROC)loadFunction("glVertexAttrib4dv");
  glVertexAttrib4dvARB = (PFNGLVERTEXATTRIB4DVARBPROC)loadFunction("glVertexAttrib4dvARB");
  glVertexAttrib4dvNV = (PFNGLVERTEXATTRIB4DVNVPROC)loadFunction("glVertexAttrib4dvNV");
  glVertexAttrib4f = (PFNGLVERTEXATTRIB4FPROC)loadFunction("glVertexAttrib4f");
  glVertexAttrib4fARB = (PFNGLVERTEXATTRIB4FARBPROC)loadFunction("glVertexAttrib4fARB");
  glVertexAttrib4fNV = (PFNGLVERTEXATTRIB4FNVPROC)loadFunction("glVertexAttrib4fNV");
  glVertexAttrib4fv = (PFNGLVERTEXATTRIB4FVPROC)loadFunction("glVertexAttrib4fv");
  glVertexAttrib4fvARB = (PFNGLVERTEXATTRIB4FVARBPROC)loadFunction("glVertexAttrib4fvARB");
  glVertexAttrib4fvNV = (PFNGLVERTEXATTRIB4FVNVPROC)loadFunction("glVertexAttrib4fvNV");
  glVertexAttrib4hNV = (PFNGLVERTEXATTRIB4HNVPROC)loadFunction("glVertexAttrib4hNV");
  glVertexAttrib4hvNV = (PFNGLVERTEXATTRIB4HVNVPROC)loadFunction("glVertexAttrib4hvNV");
  glVertexAttrib4iv = (PFNGLVERTEXATTRIB4IVPROC)loadFunction("glVertexAttrib4iv");
  glVertexAttrib4ivARB = (PFNGLVERTEXATTRIB4IVARBPROC)loadFunction("glVertexAttrib4ivARB");
  glVertexAttrib4s = (PFNGLVERTEXATTRIB4SPROC)loadFunction("glVertexAttrib4s");
  glVertexAttrib4sARB = (PFNGLVERTEXATTRIB4SARBPROC)loadFunction("glVertexAttrib4sARB");
  glVertexAttrib4sNV = (PFNGLVERTEXATTRIB4SNVPROC)loadFunction("glVertexAttrib4sNV");
  glVertexAttrib4sv = (PFNGLVERTEXATTRIB4SVPROC)loadFunction("glVertexAttrib4sv");
  glVertexAttrib4svARB = (PFNGLVERTEXATTRIB4SVARBPROC)loadFunction("glVertexAttrib4svARB");
  glVertexAttrib4svNV = (PFNGLVERTEXATTRIB4SVNVPROC)loadFunction("glVertexAttrib4svNV");
  glVertexAttrib4ubNV = (PFNGLVERTEXATTRIB4UBNVPROC)loadFunction("glVertexAttrib4ubNV");
  glVertexAttrib4ubv = (PFNGLVERTEXATTRIB4UBVPROC)loadFunction("glVertexAttrib4ubv");
  glVertexAttrib4ubvARB = (PFNGLVERTEXATTRIB4UBVARBPROC)loadFunction("glVertexAttrib4ubvARB");
  glVertexAttrib4ubvNV = (PFNGLVERTEXATTRIB4UBVNVPROC)loadFunction("glVertexAttrib4ubvNV");
  glVertexAttrib4uiv = (PFNGLVERTEXATTRIB4UIVPROC)loadFunction("glVertexAttrib4uiv");
  glVertexAttrib4uivARB = (PFNGLVERTEXATTRIB4UIVARBPROC)loadFunction("glVertexAttrib4uivARB");
  glVertexAttrib4usv = (PFNGLVERTEXATTRIB4USVPROC)loadFunction("glVertexAttrib4usv");
  glVertexAttrib4usvARB = (PFNGLVERTEXATTRIB4USVARBPROC)loadFunction("glVertexAttrib4usvARB");
  glVertexAttribBinding = (PFNGLVERTEXATTRIBBINDINGPROC)loadFunction("glVertexAttribBinding");
  glVertexAttribDivisor = (PFNGLVERTEXATTRIBDIVISORPROC)loadFunction("glVertexAttribDivisor");
  glVertexAttribDivisorARB = (PFNGLVERTEXATTRIBDIVISORARBPROC)loadFunction(
      "glVertexAttribDivisorARB");
  glVertexAttribFormat = (PFNGLVERTEXATTRIBFORMATPROC)loadFunction("glVertexAttribFormat");
  glVertexAttribFormatNV = (PFNGLVERTEXATTRIBFORMATNVPROC)loadFunction("glVertexAttribFormatNV");
  glVertexAttribI1i = (PFNGLVERTEXATTRIBI1IPROC)loadFunction("glVertexAttribI1i");
  glVertexAttribI1iEXT = (PFNGLVERTEXATTRIBI1IEXTPROC)loadFunction("glVertexAttribI1iEXT");
  glVertexAttribI1iv = (PFNGLVERTEXATTRIBI1IVPROC)loadFunction("glVertexAttribI1iv");
  glVertexAttribI1ivEXT = (PFNGLVERTEXATTRIBI1IVEXTPROC)loadFunction("glVertexAttribI1ivEXT");
  glVertexAttribI1ui = (PFNGLVERTEXATTRIBI1UIPROC)loadFunction("glVertexAttribI1ui");
  glVertexAttribI1uiEXT = (PFNGLVERTEXATTRIBI1UIEXTPROC)loadFunction("glVertexAttribI1uiEXT");
  glVertexAttribI1uiv = (PFNGLVERTEXATTRIBI1UIVPROC)loadFunction("glVertexAttribI1uiv");
  glVertexAttribI1uivEXT = (PFNGLVERTEXATTRIBI1UIVEXTPROC)loadFunction("glVertexAttribI1uivEXT");
  glVertexAttribI2i = (PFNGLVERTEXATTRIBI2IPROC)loadFunction("glVertexAttribI2i");
  glVertexAttribI2iEXT = (PFNGLVERTEXATTRIBI2IEXTPROC)loadFunction("glVertexAttribI2iEXT");
  glVertexAttribI2iv = (PFNGLVERTEXATTRIBI2IVPROC)loadFunction("glVertexAttribI2iv");
  glVertexAttribI2ivEXT = (PFNGLVERTEXATTRIBI2IVEXTPROC)loadFunction("glVertexAttribI2ivEXT");
  glVertexAttribI2ui = (PFNGLVERTEXATTRIBI2UIPROC)loadFunction("glVertexAttribI2ui");
  glVertexAttribI2uiEXT = (PFNGLVERTEXATTRIBI2UIEXTPROC)loadFunction("glVertexAttribI2uiEXT");
  glVertexAttribI2uiv = (PFNGLVERTEXATTRIBI2UIVPROC)loadFunction("glVertexAttribI2uiv");
  glVertexAttribI2uivEXT = (PFNGLVERTEXATTRIBI2UIVEXTPROC)loadFunction("glVertexAttribI2uivEXT");
  glVertexAttribI3i = (PFNGLVERTEXATTRIBI3IPROC)loadFunction("glVertexAttribI3i");
  glVertexAttribI3iEXT = (PFNGLVERTEXATTRIBI3IEXTPROC)loadFunction("glVertexAttribI3iEXT");
  glVertexAttribI3iv = (PFNGLVERTEXATTRIBI3IVPROC)loadFunction("glVertexAttribI3iv");
  glVertexAttribI3ivEXT = (PFNGLVERTEXATTRIBI3IVEXTPROC)loadFunction("glVertexAttribI3ivEXT");
  glVertexAttribI3ui = (PFNGLVERTEXATTRIBI3UIPROC)loadFunction("glVertexAttribI3ui");
  glVertexAttribI3uiEXT = (PFNGLVERTEXATTRIBI3UIEXTPROC)loadFunction("glVertexAttribI3uiEXT");
  glVertexAttribI3uiv = (PFNGLVERTEXATTRIBI3UIVPROC)loadFunction("glVertexAttribI3uiv");
  glVertexAttribI3uivEXT = (PFNGLVERTEXATTRIBI3UIVEXTPROC)loadFunction("glVertexAttribI3uivEXT");
  glVertexAttribI4bv = (PFNGLVERTEXATTRIBI4BVPROC)loadFunction("glVertexAttribI4bv");
  glVertexAttribI4bvEXT = (PFNGLVERTEXATTRIBI4BVEXTPROC)loadFunction("glVertexAttribI4bvEXT");
  glVertexAttribI4i = (PFNGLVERTEXATTRIBI4IPROC)loadFunction("glVertexAttribI4i");
  glVertexAttribI4iEXT = (PFNGLVERTEXATTRIBI4IEXTPROC)loadFunction("glVertexAttribI4iEXT");
  glVertexAttribI4iv = (PFNGLVERTEXATTRIBI4IVPROC)loadFunction("glVertexAttribI4iv");
  glVertexAttribI4ivEXT = (PFNGLVERTEXATTRIBI4IVEXTPROC)loadFunction("glVertexAttribI4ivEXT");
  glVertexAttribI4sv = (PFNGLVERTEXATTRIBI4SVPROC)loadFunction("glVertexAttribI4sv");
  glVertexAttribI4svEXT = (PFNGLVERTEXATTRIBI4SVEXTPROC)loadFunction("glVertexAttribI4svEXT");
  glVertexAttribI4ubv = (PFNGLVERTEXATTRIBI4UBVPROC)loadFunction("glVertexAttribI4ubv");
  glVertexAttribI4ubvEXT = (PFNGLVERTEXATTRIBI4UBVEXTPROC)loadFunction("glVertexAttribI4ubvEXT");
  glVertexAttribI4ui = (PFNGLVERTEXATTRIBI4UIPROC)loadFunction("glVertexAttribI4ui");
  glVertexAttribI4uiEXT = (PFNGLVERTEXATTRIBI4UIEXTPROC)loadFunction("glVertexAttribI4uiEXT");
  glVertexAttribI4uiv = (PFNGLVERTEXATTRIBI4UIVPROC)loadFunction("glVertexAttribI4uiv");
  glVertexAttribI4uivEXT = (PFNGLVERTEXATTRIBI4UIVEXTPROC)loadFunction("glVertexAttribI4uivEXT");
  glVertexAttribI4usv = (PFNGLVERTEXATTRIBI4USVPROC)loadFunction("glVertexAttribI4usv");
  glVertexAttribI4usvEXT = (PFNGLVERTEXATTRIBI4USVEXTPROC)loadFunction("glVertexAttribI4usvEXT");
  glVertexAttribIFormat = (PFNGLVERTEXATTRIBIFORMATPROC)loadFunction("glVertexAttribIFormat");
  glVertexAttribIFormatNV = (PFNGLVERTEXATTRIBIFORMATNVPROC)loadFunction(
      "glVertexAttribIFormatNV");
  glVertexAttribIPointer = (PFNGLVERTEXATTRIBIPOINTERPROC)loadFunction("glVertexAttribIPointer");
  glVertexAttribIPointerEXT = (PFNGLVERTEXATTRIBIPOINTEREXTPROC)loadFunction(
      "glVertexAttribIPointerEXT");
  glVertexAttribL1d = (PFNGLVERTEXATTRIBL1DPROC)loadFunction("glVertexAttribL1d");
  glVertexAttribL1dEXT = (PFNGLVERTEXATTRIBL1DEXTPROC)loadFunction("glVertexAttribL1dEXT");
  glVertexAttribL1dv = (PFNGLVERTEXATTRIBL1DVPROC)loadFunction("glVertexAttribL1dv");
  glVertexAttribL1dvEXT = (PFNGLVERTEXATTRIBL1DVEXTPROC)loadFunction("glVertexAttribL1dvEXT");
  glVertexAttribL1i64NV = (PFNGLVERTEXATTRIBL1I64NVPROC)loadFunction("glVertexAttribL1i64NV");
  glVertexAttribL1i64vNV = (PFNGLVERTEXATTRIBL1I64VNVPROC)loadFunction("glVertexAttribL1i64vNV");
  glVertexAttribL1ui64ARB = (PFNGLVERTEXATTRIBL1UI64ARBPROC)loadFunction(
      "glVertexAttribL1ui64ARB");
  glVertexAttribL1ui64NV = (PFNGLVERTEXATTRIBL1UI64NVPROC)loadFunction("glVertexAttribL1ui64NV");
  glVertexAttribL1ui64vARB = (PFNGLVERTEXATTRIBL1UI64VARBPROC)loadFunction(
      "glVertexAttribL1ui64vARB");
  glVertexAttribL1ui64vNV = (PFNGLVERTEXATTRIBL1UI64VNVPROC)loadFunction(
      "glVertexAttribL1ui64vNV");
  glVertexAttribL2d = (PFNGLVERTEXATTRIBL2DPROC)loadFunction("glVertexAttribL2d");
  glVertexAttribL2dEXT = (PFNGLVERTEXATTRIBL2DEXTPROC)loadFunction("glVertexAttribL2dEXT");
  glVertexAttribL2dv = (PFNGLVERTEXATTRIBL2DVPROC)loadFunction("glVertexAttribL2dv");
  glVertexAttribL2dvEXT = (PFNGLVERTEXATTRIBL2DVEXTPROC)loadFunction("glVertexAttribL2dvEXT");
  glVertexAttribL2i64NV = (PFNGLVERTEXATTRIBL2I64NVPROC)loadFunction("glVertexAttribL2i64NV");
  glVertexAttribL2i64vNV = (PFNGLVERTEXATTRIBL2I64VNVPROC)loadFunction("glVertexAttribL2i64vNV");
  glVertexAttribL2ui64NV = (PFNGLVERTEXATTRIBL2UI64NVPROC)loadFunction("glVertexAttribL2ui64NV");
  glVertexAttribL2ui64vNV = (PFNGLVERTEXATTRIBL2UI64VNVPROC)loadFunction(
      "glVertexAttribL2ui64vNV");
  glVertexAttribL3d = (PFNGLVERTEXATTRIBL3DPROC)loadFunction("glVertexAttribL3d");
  glVertexAttribL3dEXT = (PFNGLVERTEXATTRIBL3DEXTPROC)loadFunction("glVertexAttribL3dEXT");
  glVertexAttribL3dv = (PFNGLVERTEXATTRIBL3DVPROC)loadFunction("glVertexAttribL3dv");
  glVertexAttribL3dvEXT = (PFNGLVERTEXATTRIBL3DVEXTPROC)loadFunction("glVertexAttribL3dvEXT");
  glVertexAttribL3i64NV = (PFNGLVERTEXATTRIBL3I64NVPROC)loadFunction("glVertexAttribL3i64NV");
  glVertexAttribL3i64vNV = (PFNGLVERTEXATTRIBL3I64VNVPROC)loadFunction("glVertexAttribL3i64vNV");
  glVertexAttribL3ui64NV = (PFNGLVERTEXATTRIBL3UI64NVPROC)loadFunction("glVertexAttribL3ui64NV");
  glVertexAttribL3ui64vNV = (PFNGLVERTEXATTRIBL3UI64VNVPROC)loadFunction(
      "glVertexAttribL3ui64vNV");
  glVertexAttribL4d = (PFNGLVERTEXATTRIBL4DPROC)loadFunction("glVertexAttribL4d");
  glVertexAttribL4dEXT = (PFNGLVERTEXATTRIBL4DEXTPROC)loadFunction("glVertexAttribL4dEXT");
  glVertexAttribL4dv = (PFNGLVERTEXATTRIBL4DVPROC)loadFunction("glVertexAttribL4dv");
  glVertexAttribL4dvEXT = (PFNGLVERTEXATTRIBL4DVEXTPROC)loadFunction("glVertexAttribL4dvEXT");
  glVertexAttribL4i64NV = (PFNGLVERTEXATTRIBL4I64NVPROC)loadFunction("glVertexAttribL4i64NV");
  glVertexAttribL4i64vNV = (PFNGLVERTEXATTRIBL4I64VNVPROC)loadFunction("glVertexAttribL4i64vNV");
  glVertexAttribL4ui64NV = (PFNGLVERTEXATTRIBL4UI64NVPROC)loadFunction("glVertexAttribL4ui64NV");
  glVertexAttribL4ui64vNV = (PFNGLVERTEXATTRIBL4UI64VNVPROC)loadFunction(
      "glVertexAttribL4ui64vNV");
  glVertexAttribLFormat = (PFNGLVERTEXATTRIBLFORMATPROC)loadFunction("glVertexAttribLFormat");
  glVertexAttribLFormatNV = (PFNGLVERTEXATTRIBLFORMATNVPROC)loadFunction(
      "glVertexAttribLFormatNV");
  glVertexAttribLPointer = (PFNGLVERTEXATTRIBLPOINTERPROC)loadFunction("glVertexAttribLPointer");
  glVertexAttribLPointerEXT = (PFNGLVERTEXATTRIBLPOINTEREXTPROC)loadFunction(
      "glVertexAttribLPointerEXT");
  glVertexAttribP1ui = (PFNGLVERTEXATTRIBP1UIPROC)loadFunction("glVertexAttribP1ui");
  glVertexAttribP1uiv = (PFNGLVERTEXATTRIBP1UIVPROC)loadFunction("glVertexAttribP1uiv");
  glVertexAttribP2ui = (PFNGLVERTEXATTRIBP2UIPROC)loadFunction("glVertexAttribP2ui");
  glVertexAttribP2uiv = (PFNGLVERTEXATTRIBP2UIVPROC)loadFunction("glVertexAttribP2uiv");
  glVertexAttribP3ui = (PFNGLVERTEXATTRIBP3UIPROC)loadFunction("glVertexAttribP3ui");
  glVertexAttribP3uiv = (PFNGLVERTEXATTRIBP3UIVPROC)loadFunction("glVertexAttribP3uiv");
  glVertexAttribP4ui = (PFNGLVERTEXATTRIBP4UIPROC)loadFunction("glVertexAttribP4ui");
  glVertexAttribP4uiv = (PFNGLVERTEXATTRIBP4UIVPROC)loadFunction("glVertexAttribP4uiv");
  glVertexAttribParameteriAMD = (PFNGLVERTEXATTRIBPARAMETERIAMDPROC)loadFunction(
      "glVertexAttribParameteriAMD");
  glVertexAttribPointer = (PFNGLVERTEXATTRIBPOINTERPROC)loadFunction("glVertexAttribPointer");
  glVertexAttribPointerARB = (PFNGLVERTEXATTRIBPOINTERARBPROC)loadFunction(
      "glVertexAttribPointerARB");
  glVertexAttribPointerNV = (PFNGLVERTEXATTRIBPOINTERNVPROC)loadFunction(
      "glVertexAttribPointerNV");
  glVertexAttribs1dvNV = (PFNGLVERTEXATTRIBS1DVNVPROC)loadFunction("glVertexAttribs1dvNV");
  glVertexAttribs1fvNV = (PFNGLVERTEXATTRIBS1FVNVPROC)loadFunction("glVertexAttribs1fvNV");
  glVertexAttribs1hvNV = (PFNGLVERTEXATTRIBS1HVNVPROC)loadFunction("glVertexAttribs1hvNV");
  glVertexAttribs1svNV = (PFNGLVERTEXATTRIBS1SVNVPROC)loadFunction("glVertexAttribs1svNV");
  glVertexAttribs2dvNV = (PFNGLVERTEXATTRIBS2DVNVPROC)loadFunction("glVertexAttribs2dvNV");
  glVertexAttribs2fvNV = (PFNGLVERTEXATTRIBS2FVNVPROC)loadFunction("glVertexAttribs2fvNV");
  glVertexAttribs2hvNV = (PFNGLVERTEXATTRIBS2HVNVPROC)loadFunction("glVertexAttribs2hvNV");
  glVertexAttribs2svNV = (PFNGLVERTEXATTRIBS2SVNVPROC)loadFunction("glVertexAttribs2svNV");
  glVertexAttribs3dvNV = (PFNGLVERTEXATTRIBS3DVNVPROC)loadFunction("glVertexAttribs3dvNV");
  glVertexAttribs3fvNV = (PFNGLVERTEXATTRIBS3FVNVPROC)loadFunction("glVertexAttribs3fvNV");
  glVertexAttribs3hvNV = (PFNGLVERTEXATTRIBS3HVNVPROC)loadFunction("glVertexAttribs3hvNV");
  glVertexAttribs3svNV = (PFNGLVERTEXATTRIBS3SVNVPROC)loadFunction("glVertexAttribs3svNV");
  glVertexAttribs4dvNV = (PFNGLVERTEXATTRIBS4DVNVPROC)loadFunction("glVertexAttribs4dvNV");
  glVertexAttribs4fvNV = (PFNGLVERTEXATTRIBS4FVNVPROC)loadFunction("glVertexAttribs4fvNV");
  glVertexAttribs4hvNV = (PFNGLVERTEXATTRIBS4HVNVPROC)loadFunction("glVertexAttribs4hvNV");
  glVertexAttribs4svNV = (PFNGLVERTEXATTRIBS4SVNVPROC)loadFunction("glVertexAttribs4svNV");
  glVertexAttribs4ubvNV = (PFNGLVERTEXATTRIBS4UBVNVPROC)loadFunction("glVertexAttribs4ubvNV");
  glVertexBindingDivisor = (PFNGLVERTEXBINDINGDIVISORPROC)loadFunction("glVertexBindingDivisor");
  glVertexBlendARB = (PFNGLVERTEXBLENDARBPROC)loadFunction("glVertexBlendARB");
  glVertexFormatNV = (PFNGLVERTEXFORMATNVPROC)loadFunction("glVertexFormatNV");
  glVertexP2ui = (PFNGLVERTEXP2UIPROC)loadFunction("glVertexP2ui");
  glVertexP2uiv = (PFNGLVERTEXP2UIVPROC)loadFunction("glVertexP2uiv");
  glVertexP3ui = (PFNGLVERTEXP3UIPROC)loadFunction("glVertexP3ui");
  glVertexP3uiv = (PFNGLVERTEXP3UIVPROC)loadFunction("glVertexP3uiv");
  glVertexP4ui = (PFNGLVERTEXP4UIPROC)loadFunction("glVertexP4ui");
  glVertexP4uiv = (PFNGLVERTEXP4UIVPROC)loadFunction("glVertexP4uiv");
  glVertexPointer = (PFNGLVERTEXPOINTERPROC)loadFunction("glVertexPointer");
  glVertexPointerEXT = (PFNGLVERTEXPOINTEREXTPROC)loadFunction("glVertexPointerEXT");
  glVertexPointervINTEL = (PFNGLVERTEXPOINTERVINTELPROC)loadFunction("glVertexPointervINTEL");
  glVertexWeightPointerEXT = (PFNGLVERTEXWEIGHTPOINTEREXTPROC)loadFunction(
      "glVertexWeightPointerEXT");
  glVertexWeightfEXT = (PFNGLVERTEXWEIGHTFEXTPROC)loadFunction("glVertexWeightfEXT");
  glVertexWeightfvEXT = (PFNGLVERTEXWEIGHTFVEXTPROC)loadFunction("glVertexWeightfvEXT");
  glVertexWeighthNV = (PFNGLVERTEXWEIGHTHNVPROC)loadFunction("glVertexWeighthNV");
  glVertexWeighthvNV = (PFNGLVERTEXWEIGHTHVNVPROC)loadFunction("glVertexWeighthvNV");
  glVideoCaptureNV = (PFNGLVIDEOCAPTURENVPROC)loadFunction("glVideoCaptureNV");
  glVideoCaptureStreamParameterdvNV = (PFNGLVIDEOCAPTURESTREAMPARAMETERDVNVPROC)loadFunction(
      "glVideoCaptureStreamParameterdvNV");
  glVideoCaptureStreamParameterfvNV = (PFNGLVIDEOCAPTURESTREAMPARAMETERFVNVPROC)loadFunction(
      "glVideoCaptureStreamParameterfvNV");
  glVideoCaptureStreamParameterivNV = (PFNGLVIDEOCAPTURESTREAMPARAMETERIVNVPROC)loadFunction(
      "glVideoCaptureStreamParameterivNV");
  glViewport = (PFNGLVIEWPORTPROC)loadFunction("glViewport");
  glViewportArrayv = (PFNGLVIEWPORTARRAYVPROC)loadFunction("glViewportArrayv");
  glViewportIndexedf = (PFNGLVIEWPORTINDEXEDFPROC)loadFunction("glViewportIndexedf");
  glViewportIndexedfv = (PFNGLVIEWPORTINDEXEDFVPROC)loadFunction("glViewportIndexedfv");
  glViewportPositionWScaleNV = (PFNGLVIEWPORTPOSITIONWSCALENVPROC)loadFunction(
      "glViewportPositionWScaleNV");
  glViewportSwizzleNV = (PFNGLVIEWPORTSWIZZLENVPROC)loadFunction("glViewportSwizzleNV");
  glWaitSemaphoreEXT = (PFNGLWAITSEMAPHOREEXTPROC)loadFunction("glWaitSemaphoreEXT");
  glWaitSemaphoreui64NVX = (PFNGLWAITSEMAPHOREUI64NVXPROC)loadFunction("glWaitSemaphoreui64NVX");
  glWaitSync = (PFNGLWAITSYNCPROC)loadFunction("glWaitSync");
  glWeightPathsNV = (PFNGLWEIGHTPATHSNVPROC)loadFunction("glWeightPathsNV");
  glWeightPointerARB = (PFNGLWEIGHTPOINTERARBPROC)loadFunction("glWeightPointerARB");
  glWeightbvARB = (PFNGLWEIGHTBVARBPROC)loadFunction("glWeightbvARB");
  glWeightdvARB = (PFNGLWEIGHTDVARBPROC)loadFunction("glWeightdvARB");
  glWeightfvARB = (PFNGLWEIGHTFVARBPROC)loadFunction("glWeightfvARB");
  glWeightivARB = (PFNGLWEIGHTIVARBPROC)loadFunction("glWeightivARB");
  glWeightsvARB = (PFNGLWEIGHTSVARBPROC)loadFunction("glWeightsvARB");
  glWeightubvARB = (PFNGLWEIGHTUBVARBPROC)loadFunction("glWeightubvARB");
  glWeightuivARB = (PFNGLWEIGHTUIVARBPROC)loadFunction("glWeightuivARB");
  glWeightusvARB = (PFNGLWEIGHTUSVARBPROC)loadFunction("glWeightusvARB");
  glWindowPos2d = (PFNGLWINDOWPOS2DPROC)loadFunction("glWindowPos2d");
  glWindowPos2dARB = (PFNGLWINDOWPOS2DARBPROC)loadFunction("glWindowPos2dARB");
  glWindowPos2dv = (PFNGLWINDOWPOS2DVPROC)loadFunction("glWindowPos2dv");
  glWindowPos2dvARB = (PFNGLWINDOWPOS2DVARBPROC)loadFunction("glWindowPos2dvARB");
  glWindowPos2f = (PFNGLWINDOWPOS2FPROC)loadFunction("glWindowPos2f");
  glWindowPos2fARB = (PFNGLWINDOWPOS2FARBPROC)loadFunction("glWindowPos2fARB");
  glWindowPos2fv = (PFNGLWINDOWPOS2FVPROC)loadFunction("glWindowPos2fv");
  glWindowPos2fvARB = (PFNGLWINDOWPOS2FVARBPROC)loadFunction("glWindowPos2fvARB");
  glWindowPos2i = (PFNGLWINDOWPOS2IPROC)loadFunction("glWindowPos2i");
  glWindowPos2iARB = (PFNGLWINDOWPOS2IARBPROC)loadFunction("glWindowPos2iARB");
  glWindowPos2iv = (PFNGLWINDOWPOS2IVPROC)loadFunction("glWindowPos2iv");
  glWindowPos2ivARB = (PFNGLWINDOWPOS2IVARBPROC)loadFunction("glWindowPos2ivARB");
  glWindowPos2s = (PFNGLWINDOWPOS2SPROC)loadFunction("glWindowPos2s");
  glWindowPos2sARB = (PFNGLWINDOWPOS2SARBPROC)loadFunction("glWindowPos2sARB");
  glWindowPos2sv = (PFNGLWINDOWPOS2SVPROC)loadFunction("glWindowPos2sv");
  glWindowPos2svARB = (PFNGLWINDOWPOS2SVARBPROC)loadFunction("glWindowPos2svARB");
  glWindowPos3d = (PFNGLWINDOWPOS3DPROC)loadFunction("glWindowPos3d");
  glWindowPos3dARB = (PFNGLWINDOWPOS3DARBPROC)loadFunction("glWindowPos3dARB");
  glWindowPos3dv = (PFNGLWINDOWPOS3DVPROC)loadFunction("glWindowPos3dv");
  glWindowPos3dvARB = (PFNGLWINDOWPOS3DVARBPROC)loadFunction("glWindowPos3dvARB");
  glWindowPos3f = (PFNGLWINDOWPOS3FPROC)loadFunction("glWindowPos3f");
  glWindowPos3fARB = (PFNGLWINDOWPOS3FARBPROC)loadFunction("glWindowPos3fARB");
  glWindowPos3fv = (PFNGLWINDOWPOS3FVPROC)loadFunction("glWindowPos3fv");
  glWindowPos3fvARB = (PFNGLWINDOWPOS3FVARBPROC)loadFunction("glWindowPos3fvARB");
  glWindowPos3i = (PFNGLWINDOWPOS3IPROC)loadFunction("glWindowPos3i");
  glWindowPos3iARB = (PFNGLWINDOWPOS3IARBPROC)loadFunction("glWindowPos3iARB");
  glWindowPos3iv = (PFNGLWINDOWPOS3IVPROC)loadFunction("glWindowPos3iv");
  glWindowPos3ivARB = (PFNGLWINDOWPOS3IVARBPROC)loadFunction("glWindowPos3ivARB");
  glWindowPos3s = (PFNGLWINDOWPOS3SPROC)loadFunction("glWindowPos3s");
  glWindowPos3sARB = (PFNGLWINDOWPOS3SARBPROC)loadFunction("glWindowPos3sARB");
  glWindowPos3sv = (PFNGLWINDOWPOS3SVPROC)loadFunction("glWindowPos3sv");
  glWindowPos3svARB = (PFNGLWINDOWPOS3SVARBPROC)loadFunction("glWindowPos3svARB");
  glWindowRectanglesEXT = (PFNGLWINDOWRECTANGLESEXTPROC)loadFunction("glWindowRectanglesEXT");
  glWriteMaskEXT = (PFNGLWRITEMASKEXTPROC)loadFunction("glWriteMaskEXT");
  glDrawVkImageNV = (PFNGLDRAWVKIMAGENVPROC)loadFunction("glDrawVkImageNV");
  glGetVkProcAddrNV = (PFNGLGETVKPROCADDRNVPROC)loadFunction("glGetVkProcAddrNV");
  glWaitVkSemaphoreNV = (PFNGLWAITVKSEMAPHORENVPROC)loadFunction("glWaitVkSemaphoreNV");
  glSignalVkSemaphoreNV = (PFNGLSIGNALVKSEMAPHORENVPROC)loadFunction("glSignalVkSemaphoreNV");
  glSignalVkFenceNV = (PFNGLSIGNALVKFENCENVPROC)loadFunction("glSignalVkFenceNV");

  return true;
}

const GLubyte *gluErrorString(GLenum error)
{
  const char *result = NULL;
  switch (error) {
    case GL_NO_ERROR:
      result = "no error";
      break;
    case GL_INVALID_ENUM:
      result = "invalid enum";
      break;
    case GL_INVALID_VALUE:
      result = "invalid value";
      break;
    case GL_INVALID_OPERATION:
      result = "invalid operation";
      break;
    case GL_STACK_OVERFLOW:
      result = "stack overflow";
      break;
    case GL_STACK_UNDERFLOW:
      result = "stack underflow";
      break;
    case GL_OUT_OF_MEMORY:
      result = "out of memory";
      break;
    case GL_INVALID_FRAMEBUFFER_OPERATION:
      result = "invalid framebuffer operation";
      break;
    default:
      break;
  }
  return (const GLubyte *)result;
}

bool GarchGLApiLoad()
{
  static bool initialized = false;
  if (initialized) {
    return true;
  }
  initialized = true;

  return TF_VERIFY(loadLibrary()) && TF_VERIFY(loadSymbols());
}

void GarchGLApiUnload()
{
  unloadLibrary();
}

}  // namespace GLApi
}  // namespace internal
PXR_NAMESPACE_CLOSE_SCOPE
