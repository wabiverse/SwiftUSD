//
// Copyright 2019 Google LLC
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//

#ifndef PXR_USD_PLUGIN_USD_DRACO_ATTRIBUTE_FACTORY_H
#define PXR_USD_PLUGIN_USD_DRACO_ATTRIBUTE_FACTORY_H

#include "attributeDescriptor.h"

#include "Sdf/valueTypeName.h"
#include "Tf/token.h"
#include "UsdGeom/primvarsAPI.h"
#include "pxr/pxrns.h"

#include <draco/attributes/geometry_attribute.h>
#include <draco/attributes/point_attribute.h>

PXR_NAMESPACE_OPEN_SCOPE

/// \class UsdDracoAttributeFactory
///
/// Class for instantiating import and export attributes from a given attribute
/// descriptor. This class also provides helper methods for resolving various
/// aspects of attribute type.
///
class UsdDracoAttributeFactory {
 public:
  // Creates an attribute according to attribute interface type and a given
  // descriptor. A given creator object must have a CreateAttribute<T> method
  // with matching return type that creates an attribute with values
  // of C++ type T. Used to create attributes of UsdDracoImportAttribute<T>
  // and UsdDracoExportAttribute<T> types.
  template<class InterfaceT, class CreatorT>
  static std::unique_ptr<InterfaceT> CreateAttribute(const UsdDracoAttributeDescriptor &descriptor,
                                                     const CreatorT &creator);

  // Returns SDF type name for a given attribute descriptor. Runtime error is
  // produced for unsupported attribute descriptors.
  static SdfValueTypeName GetSdfValueTypeName(const UsdDracoAttributeDescriptor &descriptor);

  // Returns Draco data type corresponding to a given type info.
  // draco::DT_INVALID is returned for unsupported type infos.
  static draco::DataType GetDracoDataType(const std::type_info &typeInfo);

  // Returns data shape corresponding to a given type info.
  // draco::DT_INVALID is returned for unsupported type infos.
  static UsdDracoAttributeDescriptor::Shape GetShape(const std::type_info &typeInfo);

  // Returns a bool indicating whether a given type info corresponds to a
  // 16-bit floating point data type.
  static bool IsHalf(const std::type_info &typeInfo);
};

// Macros to make the switch cases below more compact.
#define CASE_FOR_ATTRIBUTE_TYPE(dracoType, valueType) \
  { \
    case dracoType: \
      return creator.template CreateAttribute<valueType>(descriptor); \
  }

#define CASE_FOR_ATTRIBUTE_HALF(dracoType, valueType) \
  { \
    case dracoType: \
      if (descriptor.GetIsHalf()) \
        return creator.template CreateAttribute<valueType>(descriptor); \
      break; \
  }

template<class InterfaceT, class CreatorT>
std::unique_ptr<InterfaceT> UsdDracoAttributeFactory::CreateAttribute(
    const UsdDracoAttributeDescriptor &descriptor, const CreatorT &creator)
{
  // Create attribute from attribute descriptor.
  switch (descriptor.GetShape()) {
    case UsdDracoAttributeDescriptor::MATRIX:
      switch (descriptor.GetNumComponents()) {
        case 4:
          switch (descriptor.GetDataType()) {
            CASE_FOR_ATTRIBUTE_TYPE(draco::DT_FLOAT64, GfMatrix2d);
            default:
              break;
          }
          break;
        case 9:
          switch (descriptor.GetDataType()) {
            CASE_FOR_ATTRIBUTE_TYPE(draco::DT_FLOAT64, GfMatrix3d);
            default:
              break;
          }
          break;
        case 16:
          switch (descriptor.GetDataType()) {
            CASE_FOR_ATTRIBUTE_TYPE(draco::DT_FLOAT64, GfMatrix4d);
            default:
              break;
          }
          break;
        default:
          break;
      }
      break;
    case UsdDracoAttributeDescriptor::QUATERNION:
      if (descriptor.GetNumComponents() != 4)
        break;
      switch (descriptor.GetDataType()) {
        // USD halfs are stored as Draco 16-bit ints.
        CASE_FOR_ATTRIBUTE_HALF(draco::DT_INT16, GfQuath);
        CASE_FOR_ATTRIBUTE_TYPE(draco::DT_FLOAT32, GfQuatf);
        CASE_FOR_ATTRIBUTE_TYPE(draco::DT_FLOAT64, GfQuatd);
        default:
          break;
      }
      break;
    case UsdDracoAttributeDescriptor::VECTOR:
      switch (descriptor.GetNumComponents()) {
        case 1:
          switch (descriptor.GetDataType()) {
            CASE_FOR_ATTRIBUTE_TYPE(draco::DT_UINT8, uint8_t);
            CASE_FOR_ATTRIBUTE_TYPE(draco::DT_INT32, int32_t);
            CASE_FOR_ATTRIBUTE_TYPE(draco::DT_UINT32, uint32_t);
            CASE_FOR_ATTRIBUTE_TYPE(draco::DT_INT64, int64_t);
            CASE_FOR_ATTRIBUTE_TYPE(draco::DT_UINT64, uint64_t);
            // USD halfs are stored as Draco 16-bit ints.
            CASE_FOR_ATTRIBUTE_HALF(draco::DT_INT16, GfHalf);
            CASE_FOR_ATTRIBUTE_TYPE(draco::DT_FLOAT32, float);
            CASE_FOR_ATTRIBUTE_TYPE(draco::DT_FLOAT64, double);
            CASE_FOR_ATTRIBUTE_TYPE(draco::DT_BOOL, bool);
            default:
              break;
          }
        case 2:
          switch (descriptor.GetDataType()) {
            CASE_FOR_ATTRIBUTE_TYPE(draco::DT_INT32, GfVec2i);
            // USD halfs are stored as Draco 16-bit ints.
            CASE_FOR_ATTRIBUTE_HALF(draco::DT_INT16, GfVec2h);
            CASE_FOR_ATTRIBUTE_TYPE(draco::DT_FLOAT32, GfVec2f);
            CASE_FOR_ATTRIBUTE_TYPE(draco::DT_FLOAT64, GfVec2d);
            default:
              break;
          }
        case 3:
          switch (descriptor.GetDataType()) {
            CASE_FOR_ATTRIBUTE_TYPE(draco::DT_INT32, GfVec3i);
            // USD halfs are stored as Draco 16-bit ints.
            CASE_FOR_ATTRIBUTE_HALF(draco::DT_INT16, GfVec3h);
            CASE_FOR_ATTRIBUTE_TYPE(draco::DT_FLOAT32, GfVec3f);
            CASE_FOR_ATTRIBUTE_TYPE(draco::DT_FLOAT64, GfVec3d);
            default:
              break;
          }
        case 4:
          switch (descriptor.GetDataType()) {
            CASE_FOR_ATTRIBUTE_TYPE(draco::DT_INT32, GfVec4i);
            // USD halfs are stored as Draco 16-bit ints.
            CASE_FOR_ATTRIBUTE_HALF(draco::DT_INT16, GfVec4h);
            CASE_FOR_ATTRIBUTE_TYPE(draco::DT_FLOAT32, GfVec4f);
            CASE_FOR_ATTRIBUTE_TYPE(draco::DT_FLOAT64, GfVec4d);
            default:
              break;
          }
        default:
          break;
      }
      break;
    default:
      break;
  }
  return nullptr;
}

PXR_NAMESPACE_CLOSE_SCOPE

#endif  // PXR_USD_PLUGIN_USD_DRACO_ATTRIBUTE_FACTORY_H
