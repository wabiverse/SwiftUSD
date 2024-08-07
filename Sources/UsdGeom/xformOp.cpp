//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#include "UsdGeom/xformOp.h"
#include "Usd/prim.h"
#include "UsdGeom/xformable.h"
#include "pxr/pxrns.h"

#include "Gf/matrix3d.h"
#include "Gf/matrix4d.h"
#include "Gf/matrix4f.h"
#include "Gf/rotation.h"
#include "Gf/vec3d.h"
#include "Gf/vec4d.h"

#include <cstring>
#include <vector>

PXR_NAMESPACE_OPEN_SCOPE

TF_DEFINE_PUBLIC_TOKENS(UsdGeomXformOpTypes, USDGEOM_XFORM_OP_TYPES);

TF_REGISTRY_FUNCTION(TfEnum)
{
  // Type
  TF_ADD_ENUM_NAME(UsdGeomXformOp::Type::TypeInvalid, "");
  TF_ADD_ENUM_NAME(UsdGeomXformOp::Type::TypeTranslate, "translate");
  TF_ADD_ENUM_NAME(UsdGeomXformOp::Type::TypeScale, "scale");
  TF_ADD_ENUM_NAME(UsdGeomXformOp::Type::TypeRotateX, "rotateX");
  TF_ADD_ENUM_NAME(UsdGeomXformOp::Type::TypeRotateY, "rotateY");
  TF_ADD_ENUM_NAME(UsdGeomXformOp::Type::TypeRotateZ, "rotateZ");
  TF_ADD_ENUM_NAME(UsdGeomXformOp::Type::TypeRotateXYZ, "rotateXYZ");
  TF_ADD_ENUM_NAME(UsdGeomXformOp::Type::TypeRotateXZY, "rotateXZY");
  TF_ADD_ENUM_NAME(UsdGeomXformOp::Type::TypeRotateYXZ, "rotateYXZ");
  TF_ADD_ENUM_NAME(UsdGeomXformOp::Type::TypeRotateYZX, "rotateYZX");
  TF_ADD_ENUM_NAME(UsdGeomXformOp::Type::TypeRotateZXY, "rotateZXY");
  TF_ADD_ENUM_NAME(UsdGeomXformOp::Type::TypeRotateZYX, "rotateZYX");
  TF_ADD_ENUM_NAME(UsdGeomXformOp::Type::TypeOrient, "orient");
  TF_ADD_ENUM_NAME(UsdGeomXformOp::Type::TypeTransform, "transform");

  TF_ADD_ENUM_NAME(UsdGeomXformOp::Precision::PrecisionDouble, "Double");
  TF_ADD_ENUM_NAME(UsdGeomXformOp::Precision::PrecisionFloat, "Float");
  TF_ADD_ENUM_NAME(UsdGeomXformOp::Precision::PrecisionHalf, "Half");
};

TF_DEFINE_PRIVATE_TOKENS(
    _tokens,
    ((xformOpPrefix, "xformOp:"))((inverseXformOpPrefix, "!invert!xformOp:"))((invertPrefix,
                                                                               "!invert!"))

    // This following tokens are not used here, but they're listed so they
    // become immortal and are not ref-counted.
    // Tokens for the xformOps that are missing here (eg, RotateXYZ, translate,
    // scale etc.)are added in UsdGeomXformCommonAPI.
    ((xformOpTransform, "xformOp:transform"))((xformOpRotateX, "xformOp:rotateX"))((
        xformOpRotateY, "xformOp:rotateY"))((xformOpRotateZ,
                                             "xformOp:rotateZ"))((xformOpOrient, "xformOp:orient"))

    // XXX: backwards compatibility
    (transform)

);

// Validate that the given \p name contains the xform namespace.
// Does not validate name as a legal property identifier
static bool _IsNamespaced(const TfToken &opName)
{
  return TfStringStartsWith(opName, _tokens->xformOpPrefix);
}

static TfToken _MakeNamespaced(const TfToken &name)
{
  return _IsNamespaced(name) ? name :
                               TfToken(_tokens->xformOpPrefix.GetString() + name.GetString());
}

// Returns whether the given op is an inverse operation. i.e, it starts with
// "!invert!:xformOp:".
static bool _IsInverseOp(TfToken const &opName)
{
  return TfStringStartsWith(opName, _tokens->inverseXformOpPrefix);
}

UsdGeomXformOp::UsdGeomXformOp(const UsdAttribute &attr, bool isInverseOp)
    : _attr(attr), _opType(UsdGeomXformOp::Type::TypeInvalid), _isInverseOp(isInverseOp)
{
  if (!attr) {
    // Legal to construct an XformOp with invalid attr, however IsDefined()
    // and explicit bool operator will return false.
    return;
  }

  // _Initialize _opType.
  const TfToken &name = GetName();
  const std::vector<std::string> &opNameComponents = SplitName();

  if (_IsNamespaced(name)) {
    _opType = GetOpTypeEnum(TfToken(opNameComponents[1]));
  }
  else {
    TF_CODING_ERROR("Invalid xform op: <%s>.", attr.GetPath().GetText());
  }
}

void UsdGeomXformOp::_Init()
{
  // _Initialize _opType.
  const TfToken &name = GetName();

  // Take the second namespace component.
  static char nsDelim = UsdObject::GetNamespaceDelimiter();
  char const *start = strchr(name.GetText(), nsDelim);
  if (!start) {
    TF_CODING_ERROR("Invalid xform op: <%s>.", GetAttr().GetPath().GetText());
    return;
  }
  ++start;
  char const *end = strchr(start, nsDelim);
  if (!end) {
    end = start + strlen(start);
  }
  _opType = _GetOpTypeEnumFromCString(start, end - start);
  if (_opType == UsdGeomXformOp::Type::TypeInvalid) {
    TF_CODING_ERROR("Invalid xform opType token '%s'.", std::string(start, end).c_str());
  }
}

UsdGeomXformOp::UsdGeomXformOp(const UsdAttribute &attr, bool isInverseOp, _ValidAttributeTagType)
    : _attr(attr), _opType(UsdGeomXformOp::Type::TypeInvalid), _isInverseOp(isInverseOp)
{
  _Init();
}

UsdGeomXformOp::UsdGeomXformOp(UsdAttributeQuery &&query, bool isInverseOp, _ValidAttributeTagType)
    : _attr(std::move(query)), _opType(UsdGeomXformOp::Type::TypeInvalid), _isInverseOp(isInverseOp)
{
  _Init();
}

TfToken UsdGeomXformOp::GetOpName() const
{
  return _isInverseOp ? TfToken(_tokens->invertPrefix.GetString() + GetName().GetString()) :
                        GetName();
}

/* static */
bool UsdGeomXformOp::IsXformOp(const UsdAttribute &attr)
{
  if (!attr)
    return false;

  return IsXformOp(attr.GetName());
}

/* static */
bool UsdGeomXformOp::IsXformOp(const TfToken &attrName)
{
  return _IsNamespaced(attrName);
}

/* static */
UsdAttribute UsdGeomXformOp::_GetXformOpAttr(UsdPrim const &prim,
                                             const TfToken &opName,
                                             bool *isInverseOp)
{
  *isInverseOp = _IsInverseOp(opName);

  // Is it is an inverse operation, strip off the "invert:" at the beginning
  // of opName to get the associated attribute's name.
  return *isInverseOp ? prim.GetAttribute(TfToken(
                            opName.GetString().substr(_tokens->invertPrefix.GetString().size()))) :
                        prim.GetAttribute(opName);
}

/* static */
UsdGeomXformOp::Precision UsdGeomXformOp::GetPrecisionFromValueTypeName(
    const SdfValueTypeName &typeName)
{
  if (typeName == SdfValueTypeNames->Matrix4d)
    return UsdGeomXformOp::Precision::PrecisionDouble;
  else if (typeName == SdfValueTypeNames->Double3)
    return UsdGeomXformOp::Precision::PrecisionDouble;
  else if (typeName == SdfValueTypeNames->Float3)
    return UsdGeomXformOp::Precision::PrecisionFloat;
  else if (typeName == SdfValueTypeNames->Half3)
    return UsdGeomXformOp::Precision::PrecisionHalf;
  else if (typeName == SdfValueTypeNames->Double)
    return UsdGeomXformOp::Precision::PrecisionDouble;
  else if (typeName == SdfValueTypeNames->Float)
    return UsdGeomXformOp::Precision::PrecisionFloat;
  else if (typeName == SdfValueTypeNames->Half)
    return UsdGeomXformOp::Precision::PrecisionHalf;
  else if (typeName == SdfValueTypeNames->Quatd)
    return UsdGeomXformOp::Precision::PrecisionDouble;
  else if (typeName == SdfValueTypeNames->Quatf)
    return UsdGeomXformOp::Precision::PrecisionFloat;
  else if (typeName == SdfValueTypeNames->Quath)
    return UsdGeomXformOp::Precision::PrecisionHalf;

  TF_CODING_ERROR("Invalid typeName '%s' specified.", typeName.GetAsToken().GetText());
  // Return default precision, which is double.
  return UsdGeomXformOp::Precision::PrecisionDouble;
}

/* static */
TfToken const &UsdGeomXformOp::GetOpTypeToken(UsdGeomXformOp::Type const opType)
{
  switch (opType) {
    case UsdGeomXformOp::Type::TypeTransform:
      return UsdGeomXformOpTypes->transform;
    case UsdGeomXformOp::Type::TypeTranslate:
      return UsdGeomXformOpTypes->translate;
    case UsdGeomXformOp::Type::TypeScale:
      return UsdGeomXformOpTypes->scale;
    case UsdGeomXformOp::Type::TypeRotateX:
      return UsdGeomXformOpTypes->rotateX;
    case UsdGeomXformOp::Type::TypeRotateY:
      return UsdGeomXformOpTypes->rotateY;
    case UsdGeomXformOp::Type::TypeRotateZ:
      return UsdGeomXformOpTypes->rotateZ;
    case UsdGeomXformOp::Type::TypeRotateXYZ:
      return UsdGeomXformOpTypes->rotateXYZ;
    case UsdGeomXformOp::Type::TypeRotateXZY:
      return UsdGeomXformOpTypes->rotateXZY;
    case UsdGeomXformOp::Type::TypeRotateYXZ:
      return UsdGeomXformOpTypes->rotateYXZ;
    case UsdGeomXformOp::Type::TypeRotateYZX:
      return UsdGeomXformOpTypes->rotateYZX;
    case UsdGeomXformOp::Type::TypeRotateZXY:
      return UsdGeomXformOpTypes->rotateZXY;
    case UsdGeomXformOp::Type::TypeRotateZYX:
      return UsdGeomXformOpTypes->rotateZYX;
    case UsdGeomXformOp::Type::TypeOrient:
      return UsdGeomXformOpTypes->orient;
    case UsdGeomXformOp::Type::TypeInvalid:
    default:
      static TfToken empty;
      return empty;
  }
}

/* static */
UsdGeomXformOp::Type UsdGeomXformOp::GetOpTypeEnum(TfToken const &opTypeToken)
{
  if (opTypeToken == UsdGeomXformOpTypes->transform)
    return UsdGeomXformOp::Type::TypeTransform;
  else if (opTypeToken == UsdGeomXformOpTypes->translate)
    return UsdGeomXformOp::Type::TypeTranslate;
  // RotateXYZ is expected to be more common than the remaining ops.
  else if (opTypeToken == UsdGeomXformOpTypes->rotateXYZ)
    return UsdGeomXformOp::Type::TypeRotateXYZ;
  else if (opTypeToken == UsdGeomXformOpTypes->scale)
    return UsdGeomXformOp::Type::TypeScale;
  else if (opTypeToken == UsdGeomXformOpTypes->rotateX)
    return UsdGeomXformOp::Type::TypeRotateX;
  else if (opTypeToken == UsdGeomXformOpTypes->rotateY)
    return UsdGeomXformOp::Type::TypeRotateY;
  else if (opTypeToken == UsdGeomXformOpTypes->rotateZ)
    return UsdGeomXformOp::Type::TypeRotateZ;
  else if (opTypeToken == UsdGeomXformOpTypes->rotateXZY)
    return UsdGeomXformOp::Type::TypeRotateXZY;
  else if (opTypeToken == UsdGeomXformOpTypes->rotateYXZ)
    return UsdGeomXformOp::Type::TypeRotateYXZ;
  else if (opTypeToken == UsdGeomXformOpTypes->rotateYZX)
    return UsdGeomXformOp::Type::TypeRotateYZX;
  else if (opTypeToken == UsdGeomXformOpTypes->rotateZXY)
    return UsdGeomXformOp::Type::TypeRotateZXY;
  else if (opTypeToken == UsdGeomXformOpTypes->rotateZYX)
    return UsdGeomXformOp::Type::TypeRotateZYX;
  else if (opTypeToken == UsdGeomXformOpTypes->orient)
    return UsdGeomXformOp::Type::TypeOrient;
  else if (opTypeToken == "")
    return UsdGeomXformOp::Type::TypeInvalid;

  TF_CODING_ERROR("Invalid xform opType token '%s'.", opTypeToken.GetText());
  return UsdGeomXformOp::Type::TypeInvalid;
}

/* static */
UsdGeomXformOp::Type UsdGeomXformOp::_GetOpTypeEnumFromCString(char const *str, size_t len)

{
  auto check = [str, len](char const *name) {
    return (strlen(name) == len) && (strncmp(name, str, len) == 0);
  };
  if (check("transform"))
    return UsdGeomXformOp::Type::TypeTransform;
  else if (check("translate"))
    return UsdGeomXformOp::Type::TypeTranslate;
  else if (check("rotateXYZ"))
    return UsdGeomXformOp::Type::TypeRotateXYZ;
  else if (check("scale"))
    return UsdGeomXformOp::Type::TypeScale;
  else if (check("rotateX"))
    return UsdGeomXformOp::Type::TypeRotateX;
  else if (check("rotateY"))
    return UsdGeomXformOp::Type::TypeRotateY;
  else if (check("rotateZ"))
    return UsdGeomXformOp::Type::TypeRotateZ;
  else if (check("rotateXZY"))
    return UsdGeomXformOp::Type::TypeRotateXZY;
  else if (check("rotateYXZ"))
    return UsdGeomXformOp::Type::TypeRotateYXZ;
  else if (check("rotateYZX"))
    return UsdGeomXformOp::Type::TypeRotateYZX;
  else if (check("rotateZXY"))
    return UsdGeomXformOp::Type::TypeRotateZXY;
  else if (check("rotateZYX"))
    return UsdGeomXformOp::Type::TypeRotateZYX;
  else if (check("orient"))
    return UsdGeomXformOp::Type::TypeOrient;
  else if (check(""))
    return UsdGeomXformOp::Type::TypeInvalid;
  else
    return UsdGeomXformOp::Type::TypeInvalid;
}

/* static */
const SdfValueTypeName &UsdGeomXformOp::GetValueTypeName(const UsdGeomXformOp::Type opType,
                                                         const UsdGeomXformOp::Precision precision)
{
  switch (opType) {
    case UsdGeomXformOp::Type::TypeTransform: {
      // Regardless of the requested precision, this must be Matrix4d,
      // because Matrix4f values are not supported in Sdf.
      if (precision != UsdGeomXformOp::Precision::PrecisionDouble)
        TF_CODING_ERROR(
            "Matrix transformations can only be encoded in "
            "double precision. Overriding precision to double.");
      return SdfValueTypeNames->Matrix4d;
    }
    case UsdGeomXformOp::Type::TypeTranslate:
    case UsdGeomXformOp::Type::TypeScale:
    case UsdGeomXformOp::Type::TypeRotateXYZ:
    case UsdGeomXformOp::Type::TypeRotateXZY:
    case UsdGeomXformOp::Type::TypeRotateYXZ:
    case UsdGeomXformOp::Type::TypeRotateYZX:
    case UsdGeomXformOp::Type::TypeRotateZXY:
    case UsdGeomXformOp::Type::TypeRotateZYX: {
      switch (precision) {
        case UsdGeomXformOp::Precision::PrecisionFloat:
          return SdfValueTypeNames->Float3;
        case UsdGeomXformOp::Precision::PrecisionHalf:
          return SdfValueTypeNames->Half3;
        case UsdGeomXformOp::Precision::PrecisionDouble:
        default:
          return SdfValueTypeNames->Double3;
      }
    }
    case UsdGeomXformOp::Type::TypeRotateX:
    case UsdGeomXformOp::Type::TypeRotateY:
    case UsdGeomXformOp::Type::TypeRotateZ: {
      switch (precision) {
        case UsdGeomXformOp::Precision::PrecisionFloat:
          return SdfValueTypeNames->Float;
        case UsdGeomXformOp::Precision::PrecisionHalf:
          return SdfValueTypeNames->Half;
        case UsdGeomXformOp::Precision::PrecisionDouble:
        default:
          return SdfValueTypeNames->Double;
      }
    }

    case UsdGeomXformOp::Type::TypeOrient: {
      switch (precision) {
        case UsdGeomXformOp::Precision::PrecisionFloat:
          return SdfValueTypeNames->Quatf;
        case UsdGeomXformOp::Precision::PrecisionHalf:
          return SdfValueTypeNames->Quath;
        case UsdGeomXformOp::Precision::PrecisionDouble:
        default:
          return SdfValueTypeNames->Quatd;
      }
    }

    case UsdGeomXformOp::Type::TypeInvalid:
    default: {
      static SdfValueTypeName empty;
      return empty;
    }
  }
}

UsdGeomXformOp::UsdGeomXformOp(UsdPrim const &prim,
                               UsdGeomXformOp::Type const opType,
                               UsdGeomXformOp::Precision const precision,
                               TfToken const &opSuffix,
                               bool isInverseOp)
    : _opType(opType), _isInverseOp(isInverseOp)
{
  // Determine the typeName of the xformOp attribute to be created.
  const SdfValueTypeName &typeName = GetValueTypeName(opType, precision);

  if (!typeName) {
    TF_CODING_ERROR(
        "Invalid xform-op: incompatible combination of "
        "opType (%s) and precision (%s).",
        TfEnum::GetName(opType).c_str(),
        TfEnum::GetName(precision).c_str());
    return;
  }

  TfToken attrName = UsdGeomXformOp::GetOpName(opType,
                                               opSuffix,
                                               // isInverseOp is handled below
                                               /*isInverseOp*/ false);

  // attrName can never be empty.
  TF_VERIFY(!attrName.IsEmpty());

  // Create an  attribute in the xformOp: namespace with the
  // computed typeName.
  _attr = prim.CreateAttribute(attrName, typeName, /* custom */ false);

  // If a problem occurred, an error should already have been issued,
  // and _attr will be invalid, which is what we want
}

UsdGeomXformOp::Precision UsdGeomXformOp::GetPrecision() const
{
  return GetPrecisionFromValueTypeName(GetTypeName());
}

/* static */
TfToken UsdGeomXformOp::GetOpName(const Type opType, const TfToken &opSuffix, bool isInverseOp)
{
  TfToken opName = _MakeNamespaced(GetOpTypeToken(opType));

  if (!opSuffix.IsEmpty())
    opName = TfToken(opName.GetString() + ":" + opSuffix.GetString());

  if (isInverseOp)
    opName = TfToken(_tokens->invertPrefix.GetString() + opName.GetString());

  return opName;
}

bool UsdGeomXformOp::HasSuffix(const TfToken &suffix) const
{
  return TfStringEndsWith(GetName(), suffix);
}

/* static */
GfMatrix4d UsdGeomXformOp::GetOpTransform(UsdGeomXformOp::Type const opType,
                                          VtValue const &opVal,
                                          bool isInverseOp)
{
  // This will be the most common case.
  if (opType == UsdGeomXformOp::Type::TypeTransform) {
    GfMatrix4d mat(1.);
    bool isMatrixVal = true;
    if (opVal.IsHolding<GfMatrix4d>()) {
      mat = opVal.UncheckedGet<GfMatrix4d>();
    }
    else if (opVal.IsHolding<GfMatrix4f>()) {
      mat = GfMatrix4d(opVal.UncheckedGet<GfMatrix4f>());
    }
    else {
      isMatrixVal = false;
      TF_CODING_ERROR(
          "Invalid combination of opType (%s) "
          "and opVal (%s). Returning identity matrix.",
          TfEnum::GetName(opType).c_str(),
          TfStringify(opVal).c_str());
      return GfMatrix4d(1.);
    }

    if (isMatrixVal && isInverseOp) {
      double determinant = 0;
      mat = mat.GetInverse(&determinant);

      if (GfIsClose(determinant, 0.0, 1e-9)) {
        TF_CODING_ERROR(
            "Cannot invert singular transform op with "
            "value %s.",
            TfStringify(opVal).c_str());
      }
    }

    return mat;
  }

  double doubleVal = 0.;
  bool isScalarVal = true;
  if (opVal.IsHolding<double>()) {
    doubleVal = opVal.UncheckedGet<double>();
  }
  else if (opVal.IsHolding<float>()) {
    doubleVal = opVal.UncheckedGet<float>();
  }
  else if (opVal.IsHolding<GfHalf>()) {
    doubleVal = opVal.UncheckedGet<GfHalf>();
  }
  else {
    isScalarVal = false;
  }

  if (isScalarVal) {
    if (isInverseOp)
      doubleVal = -doubleVal;

    if (opType == UsdGeomXformOp::Type::TypeRotateX) {
      return GfMatrix4d(1.).SetRotate(GfRotation(GfVec3d::XAxis(), doubleVal));
    }
    else if (opType == UsdGeomXformOp::Type::TypeRotateY) {
      return GfMatrix4d(1.).SetRotate(GfRotation(GfVec3d::YAxis(), doubleVal));
    }
    else if (opType == UsdGeomXformOp::Type::TypeRotateZ) {
      return GfMatrix4d(1.).SetRotate(GfRotation(GfVec3d::ZAxis(), doubleVal));
    }
  }

  GfVec3d vec3dVal = GfVec3d(0.);
  bool isVecVal = true;
  if (opVal.IsHolding<GfVec3f>()) {
    vec3dVal = opVal.UncheckedGet<GfVec3f>();
  }
  else if (opVal.IsHolding<GfVec3d>()) {
    vec3dVal = opVal.UncheckedGet<GfVec3d>();
  }
  else if (opVal.IsHolding<GfVec3h>()) {
    vec3dVal = opVal.UncheckedGet<GfVec3h>();
  }
  else {
    isVecVal = false;
  }

  if (isVecVal) {
    switch (opType) {
      case UsdGeomXformOp::Type::TypeTranslate:
        if (isInverseOp)
          vec3dVal = -vec3dVal;
        return GfMatrix4d(1.).SetTranslate(vec3dVal);
      case UsdGeomXformOp::Type::TypeScale:
        if (isInverseOp) {
          vec3dVal = GfVec3d(1 / vec3dVal[0], 1 / vec3dVal[1], 1 / vec3dVal[2]);
        }
        return GfMatrix4d(1.).SetScale(vec3dVal);
      default: {
        if (isInverseOp)
          vec3dVal = -vec3dVal;
        // Must be one of the 3-axis rotates.
        GfMatrix3d xRot(GfRotation(GfVec3d::XAxis(), vec3dVal[0]));
        GfMatrix3d yRot(GfRotation(GfVec3d::YAxis(), vec3dVal[1]));
        GfMatrix3d zRot(GfRotation(GfVec3d::ZAxis(), vec3dVal[2]));
        GfMatrix3d rotationMat(1.);
        switch (opType) {
          case UsdGeomXformOp::Type::TypeRotateXYZ:
            // Inv(ABC) = Inv(C) * Inv(B) * Inv(A)
            rotationMat = !isInverseOp ? (xRot * yRot * zRot) : (zRot * yRot * xRot);
            break;
          case UsdGeomXformOp::Type::TypeRotateXZY:
            rotationMat = !isInverseOp ? (xRot * zRot * yRot) : (yRot * zRot * xRot);
            break;
          case UsdGeomXformOp::Type::TypeRotateYXZ:
            rotationMat = !isInverseOp ? (yRot * xRot * zRot) : (zRot * xRot * yRot);
            break;
          case UsdGeomXformOp::Type::TypeRotateYZX:
            rotationMat = !isInverseOp ? (yRot * zRot * xRot) : (xRot * zRot * yRot);
            break;
          case UsdGeomXformOp::Type::TypeRotateZXY:
            rotationMat = !isInverseOp ? (zRot * xRot * yRot) : (yRot * xRot * zRot);
            break;
          case UsdGeomXformOp::Type::TypeRotateZYX:
            rotationMat = !isInverseOp ? (zRot * yRot * xRot) : (xRot * yRot * zRot);
            break;
          default:
            TF_CODING_ERROR(
                "Invalid combination of opType (%s) "
                "and opVal (%s). Returning identity matrix.",
                TfEnum::GetName(opType).c_str(),
                TfStringify(opVal).c_str());
            return GfMatrix4d(1.);
        }
        return GfMatrix4d(1.).SetRotate(rotationMat);
      }
    }
  }

  if (opType == UsdGeomXformOp::Type::TypeOrient) {
    GfQuatd quatVal(0);
    if (opVal.IsHolding<GfQuatd>())
      quatVal = opVal.UncheckedGet<GfQuatd>();
    else if (opVal.IsHolding<GfQuatf>()) {
      const GfQuatf &quatf = opVal.UncheckedGet<GfQuatf>();
      quatVal = GfQuatd(quatf.GetReal(), quatf.GetImaginary());
    }
    else if (opVal.IsHolding<GfQuath>()) {
      const GfQuath &quath = opVal.UncheckedGet<GfQuath>();
      quatVal = GfQuatd(quath.GetReal(), quath.GetImaginary());
    }

    GfRotation quatRotation(quatVal);
    if (isInverseOp)
      quatRotation = quatRotation.GetInverse();

    return GfMatrix4d(quatRotation, GfVec3d(0.));
  }

  TF_CODING_ERROR(
      "Invalid combination of opType (%s) and opVal (%s). "
      "Returning identity matrix.",
      TfEnum::GetName(opType).c_str(),
      TfStringify(opVal).c_str());

  return GfMatrix4d(1.);
}

GfMatrix4d UsdGeomXformOp::GetOpTransform(UsdTimeCode time) const
{
  GfMatrix4d result(1);

  VtValue opVal;
  if (!Get(&opVal, time))
    return result;

  result = GetOpTransform(GetOpType(), opVal, _isInverseOp);

  return result;
}

PXR_NAMESPACE_CLOSE_SCOPE
