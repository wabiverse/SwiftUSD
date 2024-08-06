//
// Copyright 2017 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#ifndef PXR_IMAGING_PLUGIN_HD_EMBREE_CONFIG_H
#define PXR_IMAGING_PLUGIN_HD_EMBREE_CONFIG_H

#include "Tf/singleton.h"
#include "pxr/pxrns.h"

PXR_NAMESPACE_OPEN_SCOPE

/// \class HdEmbreeConfig
///
/// This class is a singleton, holding configuration parameters for HdEmbree.
/// Everything is provided with a default, but can be overridden using
/// environment variables before launching a hydra process.
///
/// Many of the parameters can be used to control quality/performance
/// tradeoffs, or to alter how HdEmbree takes advantage of parallelism.
///
/// At startup, this class will print config parameters if
/// *HDEMBREE_PRINT_CONFIGURATION* is true. Integer values greater than zero
/// are considered "true".
///
class HdEmbreeConfig {
 public:
  /// \brief Return the configuration singleton.
  static const HdEmbreeConfig &GetInstance();

  /// How many samples do we need before a pixel is considered
  /// converged?
  ///
  /// Override with *HDEMBREE_SAMPLES_TO_CONVERGENCE*.
  unsigned int samplesToConvergence;

  /// How many pixels are in an atomic unit of parallel work?
  /// A work item is a square of size [tileSize x tileSize] pixels.
  ///
  /// Override with *HDEMBREE_TILE_SIZE*.
  unsigned int tileSize;

  /// How many ambient occlusion rays should we generate per
  /// camera ray?
  ///
  /// Override with *HDEMBREE_AMBIENT_OCCLUSION_SAMPLES*.
  unsigned int ambientOcclusionSamples;

  /// Should the renderpass jitter camera rays for antialiasing?
  ///
  /// Override with *HDEMBREE_JITTER_CAMERA*. Integer values greater than
  /// zero are considered "true".
  bool jitterCamera;

  /// Should the renderpass use the color primvar, or flat white colors?
  /// (Flat white shows off ambient occlusion better).
  ///
  /// Override with *HDEMBREE_USE_FACE_COLORS*. Integer values greater than
  /// zero are considered "true".
  bool useFaceColors;

  /// What should the intensity of the camera light be, specified as a
  /// percent of <1, 1, 1>.  For example, 300 would be <3, 3, 3>.
  ///
  /// Override with *HDEMBREE_CAMERA_LIGHT_INTENSITY*.
  float cameraLightIntensity;

 private:
  // The constructor initializes the config variables with their
  // default or environment-provided override, and optionally prints
  // them.
  HdEmbreeConfig();
  ~HdEmbreeConfig() = default;

  HdEmbreeConfig(const HdEmbreeConfig &) = delete;
  HdEmbreeConfig &operator=(const HdEmbreeConfig &) = delete;

  friend class TfSingleton<HdEmbreeConfig>;
};

PXR_NAMESPACE_CLOSE_SCOPE

#endif  // PXR_IMAGING_PLUGIN_HD_EMBREE_CONFIG_H
