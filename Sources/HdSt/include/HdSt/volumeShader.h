//
// Copyright 2019 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#ifndef PXR_IMAGING_HD_ST_VOLUME_SHADER_H
#define PXR_IMAGING_HD_ST_VOLUME_SHADER_H

#include "Hd/version.h"
#include "HdSt/api.h"
#include "pxr/pxrns.h"

#include "HdSt/materialNetworkShader.h"

PXR_NAMESPACE_OPEN_SCOPE

using HdSt_VolumeShaderSharedPtr = std::shared_ptr<class HdSt_VolumeShader>;
using HdSt_MaterialParamVector = std::vector<class HdSt_MaterialParam>;
using HdVolumeFieldDescriptorVector = std::vector<struct HdVolumeFieldDescriptor>;

/// \class HdSt_VolumeShader
///
/// Adds the following behaviors to HdSt_MaterialNetworkShader:
/// - walk through field descriptors to allocate textures and update
///   the NamedTextureHandle's.
/// - compute volume bounding box, adds it to the shader bar and
///   computes points for the points bar (if requested)
/// - bind raymarching step sizes (querried from render delegate)
///   to uniforms in the shader
///
class HdSt_VolumeShader final : public HdSt_MaterialNetworkShader {
 public:
  explicit HdSt_VolumeShader();
  ~HdSt_VolumeShader() override;

  /// Adds custom bindings.
  void AddBindings(HdStBindingRequestVector *customBindings) override;

  /// Querries render delegate for step sizes and binds the uniforms and
  /// calls base class's method.
  ///
  void BindResources(int program, HdSt_ResourceBinder const &binder) override;

  void UnbindResources(int program, HdSt_ResourceBinder const &binder) override;

  /// Adds buffer sources to the shader bar (for volume bounding
  /// box) and points bar if requested (besides calling
  /// HdSt_TextureBinder::ComputeBufferSources).
  ///
  void AddResourcesFromTextures(ResourceContext &ctx) const override;

  /// Whether the volume shader is responsible for filling buffer
  /// sources from the volume bounding box computation.
  ///
  void SetPointsBar(HdBufferArrayRangeSharedPtr const &pointsBar);

  /// Set whether this shader is responsible for filling the points bar.
  ///
  /// If there are fields, it is the volume shader's responsibility
  /// to compute the volume bounding box after the field textures
  /// are committed. Otherwise, volume prim is falling back to the
  /// authored extents and uses them to create the corresponding
  /// buffer sources.
  ///
  void SetFillsPointsBar(bool fillsPointsBar);

  /// Check whether this shader is responsible for filling the points bar.
  ///
  bool GetFillsPointsBar() const
  {
    return _fillsPointsBar;
  }

  /// Set information to identify the field prims specifying what
  /// textures to load.
  ///
  /// Must line up with the NamedTextureHandle's passed to
  /// SetNamedTextureHandles.
  ///
  void SetFieldDescriptors(const HdVolumeFieldDescriptorVector &fieldDescs);

  /// Using the above field descriptors, (re-)allocate texture handles
  /// for the associated textures to update the NamedTextureHandle's.
  ///
  void UpdateTextureHandles(HdSceneDelegate *);

  /// Add params and specs to communicate volume bounding box and sample
  /// distance to shader.
  ///
  static void GetParamsAndBufferSpecsForBBoxAndSampleDistance(HdSt_MaterialParamVector *params,
                                                              HdBufferSpecVector *specs,
                                                              bool doublesSupported);

  /// Add buffer sources to communicate volume bounding box and sample
  /// distance to shader.
  ///
  static void GetBufferSourcesForBBoxAndSampleDistance(
      const std::pair<GfBBox3d, float> &bboxAndSampleDistance,
      HdBufferSourceSharedPtrVector *sources,
      bool doublesSupported);

  /// GfRange3d encodes empty range by (infinity, -infinity).
  /// Avoid those insane values by returning (0,0).
  ///
  static GfVec3d GetSafeMin(const GfRange3d &range);

  /// GfRange3d encodes empty range by (infinity, -infinity).
  /// Avoid those insane values by returning (0,0).
  ///
  static GfVec3d GetSafeMax(const GfRange3d &range);

 private:
  HdBufferArrayRangeSharedPtr _pointsBar;
  bool _fillsPointsBar;

  HdVolumeFieldDescriptorVector _fieldDescriptors;
};

PXR_NAMESPACE_CLOSE_SCOPE

#endif
