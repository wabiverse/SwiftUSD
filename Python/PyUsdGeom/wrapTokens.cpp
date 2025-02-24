//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
// GENERATED FILE.  DO NOT EDIT.
#include "UsdGeom/tokens.h"
#include <boost/python/class.hpp>

PXR_NAMESPACE_USING_DIRECTIVE

namespace {

// Helper to return a static token as a string.  We wrap tokens as Python
// strings and for some reason simply wrapping the token using def_readonly
// bypasses to-Python conversion, leading to the error that there's no
// Python type for the C++ TfToken type.  So we wrap this functor instead.
class _WrapStaticToken {
 public:
  _WrapStaticToken(const TfToken *token) : _token(token) {}

  std::string operator()() const
  {
    return _token->GetString();
  }

 private:
  const TfToken *_token;
};

template<typename T> void _AddToken(T &cls, const char *name, const TfToken &token)
{
  cls.add_static_property(name,
                          boost::python::make_function(
                              _WrapStaticToken(&token),
                              boost::python::return_value_policy<boost::python::return_by_value>(),
                              boost::mpl::vector1<std::string>()));
}

}  // namespace

void wrapUsdGeomTokens()
{
  boost::python::class_<UsdGeomTokensType, boost::noncopyable> cls("Tokens",
                                                                   boost::python::no_init);
  _AddToken(cls, "accelerations", UsdGeomTokens->accelerations);
  _AddToken(cls, "all", UsdGeomTokens->all);
  _AddToken(cls, "angularVelocities", UsdGeomTokens->angularVelocities);
  _AddToken(cls, "axis", UsdGeomTokens->axis);
  _AddToken(cls, "basis", UsdGeomTokens->basis);
  _AddToken(cls, "bezier", UsdGeomTokens->bezier);
  _AddToken(cls, "bilinear", UsdGeomTokens->bilinear);
  _AddToken(cls, "boundaries", UsdGeomTokens->boundaries);
  _AddToken(cls, "bounds", UsdGeomTokens->bounds);
  _AddToken(cls, "box", UsdGeomTokens->box);
  _AddToken(cls, "bspline", UsdGeomTokens->bspline);
  _AddToken(cls, "cards", UsdGeomTokens->cards);
  _AddToken(cls, "catmullClark", UsdGeomTokens->catmullClark);
  _AddToken(cls, "catmullRom", UsdGeomTokens->catmullRom);
  _AddToken(cls, "clippingPlanes", UsdGeomTokens->clippingPlanes);
  _AddToken(cls, "clippingRange", UsdGeomTokens->clippingRange);
  _AddToken(cls, "closed", UsdGeomTokens->closed);
  _AddToken(cls, "constant", UsdGeomTokens->constant);
  _AddToken(cls, "cornerIndices", UsdGeomTokens->cornerIndices);
  _AddToken(cls, "cornerSharpnesses", UsdGeomTokens->cornerSharpnesses);
  _AddToken(cls, "cornersOnly", UsdGeomTokens->cornersOnly);
  _AddToken(cls, "cornersPlus1", UsdGeomTokens->cornersPlus1);
  _AddToken(cls, "cornersPlus2", UsdGeomTokens->cornersPlus2);
  _AddToken(cls, "creaseIndices", UsdGeomTokens->creaseIndices);
  _AddToken(cls, "creaseLengths", UsdGeomTokens->creaseLengths);
  _AddToken(cls, "creaseSharpnesses", UsdGeomTokens->creaseSharpnesses);
  _AddToken(cls, "cross", UsdGeomTokens->cross);
  _AddToken(cls, "cubic", UsdGeomTokens->cubic);
  _AddToken(cls, "curveVertexCounts", UsdGeomTokens->curveVertexCounts);
  _AddToken(cls, "default_", UsdGeomTokens->default_);
  _AddToken(cls, "doubleSided", UsdGeomTokens->doubleSided);
  _AddToken(cls, "edge", UsdGeomTokens->edge);
  _AddToken(cls, "edgeAndCorner", UsdGeomTokens->edgeAndCorner);
  _AddToken(cls, "edgeOnly", UsdGeomTokens->edgeOnly);
  _AddToken(cls, "elementSize", UsdGeomTokens->elementSize);
  _AddToken(cls, "elementType", UsdGeomTokens->elementType);
  _AddToken(cls, "exposure", UsdGeomTokens->exposure);
  _AddToken(cls, "extent", UsdGeomTokens->extent);
  _AddToken(cls, "extentsHint", UsdGeomTokens->extentsHint);
  _AddToken(cls, "face", UsdGeomTokens->face);
  _AddToken(cls, "faceVarying", UsdGeomTokens->faceVarying);
  _AddToken(cls, "faceVaryingLinearInterpolation", UsdGeomTokens->faceVaryingLinearInterpolation);
  _AddToken(cls, "faceVertexCounts", UsdGeomTokens->faceVertexCounts);
  _AddToken(cls, "faceVertexIndices", UsdGeomTokens->faceVertexIndices);
  _AddToken(cls, "familyName", UsdGeomTokens->familyName);
  _AddToken(cls, "focalLength", UsdGeomTokens->focalLength);
  _AddToken(cls, "focusDistance", UsdGeomTokens->focusDistance);
  _AddToken(cls, "fromTexture", UsdGeomTokens->fromTexture);
  _AddToken(cls, "fStop", UsdGeomTokens->fStop);
  _AddToken(cls, "guide", UsdGeomTokens->guide);
  _AddToken(cls, "guideVisibility", UsdGeomTokens->guideVisibility);
  _AddToken(cls, "height", UsdGeomTokens->height);
  _AddToken(cls, "hermite", UsdGeomTokens->hermite);
  _AddToken(cls, "holeIndices", UsdGeomTokens->holeIndices);
  _AddToken(cls, "horizontalAperture", UsdGeomTokens->horizontalAperture);
  _AddToken(cls, "horizontalApertureOffset", UsdGeomTokens->horizontalApertureOffset);
  _AddToken(cls, "ids", UsdGeomTokens->ids);
  _AddToken(cls, "inactiveIds", UsdGeomTokens->inactiveIds);
  _AddToken(cls, "indices", UsdGeomTokens->indices);
  _AddToken(cls, "inherited", UsdGeomTokens->inherited);
  _AddToken(cls, "interpolateBoundary", UsdGeomTokens->interpolateBoundary);
  _AddToken(cls, "interpolation", UsdGeomTokens->interpolation);
  _AddToken(cls, "invisible", UsdGeomTokens->invisible);
  _AddToken(cls, "invisibleIds", UsdGeomTokens->invisibleIds);
  _AddToken(cls, "knots", UsdGeomTokens->knots);
  _AddToken(cls, "left", UsdGeomTokens->left);
  _AddToken(cls, "leftHanded", UsdGeomTokens->leftHanded);
  _AddToken(cls, "length", UsdGeomTokens->length);
  _AddToken(cls, "linear", UsdGeomTokens->linear);
  _AddToken(cls, "loop", UsdGeomTokens->loop);
  _AddToken(cls, "metersPerUnit", UsdGeomTokens->metersPerUnit);
  _AddToken(cls, "modelApplyDrawMode", UsdGeomTokens->modelApplyDrawMode);
  _AddToken(cls, "modelCardGeometry", UsdGeomTokens->modelCardGeometry);
  _AddToken(cls, "modelCardTextureXNeg", UsdGeomTokens->modelCardTextureXNeg);
  _AddToken(cls, "modelCardTextureXPos", UsdGeomTokens->modelCardTextureXPos);
  _AddToken(cls, "modelCardTextureYNeg", UsdGeomTokens->modelCardTextureYNeg);
  _AddToken(cls, "modelCardTextureYPos", UsdGeomTokens->modelCardTextureYPos);
  _AddToken(cls, "modelCardTextureZNeg", UsdGeomTokens->modelCardTextureZNeg);
  _AddToken(cls, "modelCardTextureZPos", UsdGeomTokens->modelCardTextureZPos);
  _AddToken(cls, "modelDrawMode", UsdGeomTokens->modelDrawMode);
  _AddToken(cls, "modelDrawModeColor", UsdGeomTokens->modelDrawModeColor);
  _AddToken(cls, "mono", UsdGeomTokens->mono);
  _AddToken(cls, "motionBlurScale", UsdGeomTokens->motionBlurScale);
  _AddToken(cls, "motionNonlinearSampleCount", UsdGeomTokens->motionNonlinearSampleCount);
  _AddToken(cls, "motionVelocityScale", UsdGeomTokens->motionVelocityScale);
  _AddToken(cls, "none", UsdGeomTokens->none);
  _AddToken(cls, "nonOverlapping", UsdGeomTokens->nonOverlapping);
  _AddToken(cls, "nonperiodic", UsdGeomTokens->nonperiodic);
  _AddToken(cls, "normals", UsdGeomTokens->normals);
  _AddToken(cls, "open", UsdGeomTokens->open);
  _AddToken(cls, "order", UsdGeomTokens->order);
  _AddToken(cls, "orientation", UsdGeomTokens->orientation);
  _AddToken(cls, "orientations", UsdGeomTokens->orientations);
  _AddToken(cls, "orientationsf", UsdGeomTokens->orientationsf);
  _AddToken(cls, "origin", UsdGeomTokens->origin);
  _AddToken(cls, "orthographic", UsdGeomTokens->orthographic);
  _AddToken(cls, "partition", UsdGeomTokens->partition);
  _AddToken(cls, "periodic", UsdGeomTokens->periodic);
  _AddToken(cls, "perspective", UsdGeomTokens->perspective);
  _AddToken(cls, "pinned", UsdGeomTokens->pinned);
  _AddToken(cls, "pivot", UsdGeomTokens->pivot);
  _AddToken(cls, "point", UsdGeomTokens->point);
  _AddToken(cls, "points", UsdGeomTokens->points);
  _AddToken(cls, "pointWeights", UsdGeomTokens->pointWeights);
  _AddToken(cls, "positions", UsdGeomTokens->positions);
  _AddToken(cls, "power", UsdGeomTokens->power);
  _AddToken(cls, "primvarsDisplayColor", UsdGeomTokens->primvarsDisplayColor);
  _AddToken(cls, "primvarsDisplayOpacity", UsdGeomTokens->primvarsDisplayOpacity);
  _AddToken(cls, "projection", UsdGeomTokens->projection);
  _AddToken(cls, "protoIndices", UsdGeomTokens->protoIndices);
  _AddToken(cls, "prototypes", UsdGeomTokens->prototypes);
  _AddToken(cls, "proxy", UsdGeomTokens->proxy);
  _AddToken(cls, "proxyPrim", UsdGeomTokens->proxyPrim);
  _AddToken(cls, "proxyVisibility", UsdGeomTokens->proxyVisibility);
  _AddToken(cls, "purpose", UsdGeomTokens->purpose);
  _AddToken(cls, "radius", UsdGeomTokens->radius);
  _AddToken(cls, "radiusBottom", UsdGeomTokens->radiusBottom);
  _AddToken(cls, "radiusTop", UsdGeomTokens->radiusTop);
  _AddToken(cls, "ranges", UsdGeomTokens->ranges);
  _AddToken(cls, "render", UsdGeomTokens->render);
  _AddToken(cls, "renderVisibility", UsdGeomTokens->renderVisibility);
  _AddToken(cls, "right", UsdGeomTokens->right);
  _AddToken(cls, "rightHanded", UsdGeomTokens->rightHanded);
  _AddToken(cls, "scales", UsdGeomTokens->scales);
  _AddToken(cls, "shutterClose", UsdGeomTokens->shutterClose);
  _AddToken(cls, "shutterOpen", UsdGeomTokens->shutterOpen);
  _AddToken(cls, "size", UsdGeomTokens->size);
  _AddToken(cls, "smooth", UsdGeomTokens->smooth);
  _AddToken(cls, "stereoRole", UsdGeomTokens->stereoRole);
  _AddToken(cls, "subdivisionScheme", UsdGeomTokens->subdivisionScheme);
  _AddToken(cls, "surfaceFaceVertexIndices", UsdGeomTokens->surfaceFaceVertexIndices);
  _AddToken(cls, "tangents", UsdGeomTokens->tangents);
  _AddToken(cls, "tetrahedron", UsdGeomTokens->tetrahedron);
  _AddToken(cls, "tetVertexIndices", UsdGeomTokens->tetVertexIndices);
  _AddToken(cls, "triangleSubdivisionRule", UsdGeomTokens->triangleSubdivisionRule);
  _AddToken(cls, "trimCurveCounts", UsdGeomTokens->trimCurveCounts);
  _AddToken(cls, "trimCurveKnots", UsdGeomTokens->trimCurveKnots);
  _AddToken(cls, "trimCurveOrders", UsdGeomTokens->trimCurveOrders);
  _AddToken(cls, "trimCurvePoints", UsdGeomTokens->trimCurvePoints);
  _AddToken(cls, "trimCurveRanges", UsdGeomTokens->trimCurveRanges);
  _AddToken(cls, "trimCurveVertexCounts", UsdGeomTokens->trimCurveVertexCounts);
  _AddToken(cls, "type", UsdGeomTokens->type);
  _AddToken(cls, "uForm", UsdGeomTokens->uForm);
  _AddToken(cls, "uKnots", UsdGeomTokens->uKnots);
  _AddToken(cls, "unauthoredValuesIndex", UsdGeomTokens->unauthoredValuesIndex);
  _AddToken(cls, "uniform", UsdGeomTokens->uniform);
  _AddToken(cls, "unrestricted", UsdGeomTokens->unrestricted);
  _AddToken(cls, "uOrder", UsdGeomTokens->uOrder);
  _AddToken(cls, "upAxis", UsdGeomTokens->upAxis);
  _AddToken(cls, "uRange", UsdGeomTokens->uRange);
  _AddToken(cls, "uVertexCount", UsdGeomTokens->uVertexCount);
  _AddToken(cls, "varying", UsdGeomTokens->varying);
  _AddToken(cls, "velocities", UsdGeomTokens->velocities);
  _AddToken(cls, "vertex", UsdGeomTokens->vertex);
  _AddToken(cls, "verticalAperture", UsdGeomTokens->verticalAperture);
  _AddToken(cls, "verticalApertureOffset", UsdGeomTokens->verticalApertureOffset);
  _AddToken(cls, "vForm", UsdGeomTokens->vForm);
  _AddToken(cls, "visibility", UsdGeomTokens->visibility);
  _AddToken(cls, "visible", UsdGeomTokens->visible);
  _AddToken(cls, "vKnots", UsdGeomTokens->vKnots);
  _AddToken(cls, "vOrder", UsdGeomTokens->vOrder);
  _AddToken(cls, "vRange", UsdGeomTokens->vRange);
  _AddToken(cls, "vVertexCount", UsdGeomTokens->vVertexCount);
  _AddToken(cls, "width", UsdGeomTokens->width);
  _AddToken(cls, "widths", UsdGeomTokens->widths);
  _AddToken(cls, "wrap", UsdGeomTokens->wrap);
  _AddToken(cls, "x", UsdGeomTokens->x);
  _AddToken(cls, "xformOpOrder", UsdGeomTokens->xformOpOrder);
  _AddToken(cls, "y", UsdGeomTokens->y);
  _AddToken(cls, "z", UsdGeomTokens->z);
  _AddToken(cls, "BasisCurves", UsdGeomTokens->BasisCurves);
  _AddToken(cls, "Boundable", UsdGeomTokens->Boundable);
  _AddToken(cls, "Camera", UsdGeomTokens->Camera);
  _AddToken(cls, "Capsule", UsdGeomTokens->Capsule);
  _AddToken(cls, "Capsule_1", UsdGeomTokens->Capsule_1);
  _AddToken(cls, "Cone", UsdGeomTokens->Cone);
  _AddToken(cls, "Cube", UsdGeomTokens->Cube);
  _AddToken(cls, "Curves", UsdGeomTokens->Curves);
  _AddToken(cls, "Cylinder", UsdGeomTokens->Cylinder);
  _AddToken(cls, "Cylinder_1", UsdGeomTokens->Cylinder_1);
  _AddToken(cls, "GeomModelAPI", UsdGeomTokens->GeomModelAPI);
  _AddToken(cls, "GeomSubset", UsdGeomTokens->GeomSubset);
  _AddToken(cls, "Gprim", UsdGeomTokens->Gprim);
  _AddToken(cls, "HermiteCurves", UsdGeomTokens->HermiteCurves);
  _AddToken(cls, "Imageable", UsdGeomTokens->Imageable);
  _AddToken(cls, "Mesh", UsdGeomTokens->Mesh);
  _AddToken(cls, "MotionAPI", UsdGeomTokens->MotionAPI);
  _AddToken(cls, "NurbsCurves", UsdGeomTokens->NurbsCurves);
  _AddToken(cls, "NurbsPatch", UsdGeomTokens->NurbsPatch);
  _AddToken(cls, "Plane", UsdGeomTokens->Plane);
  _AddToken(cls, "PointBased", UsdGeomTokens->PointBased);
  _AddToken(cls, "PointInstancer", UsdGeomTokens->PointInstancer);
  _AddToken(cls, "Points", UsdGeomTokens->Points);
  _AddToken(cls, "PrimvarsAPI", UsdGeomTokens->PrimvarsAPI);
  _AddToken(cls, "Scope", UsdGeomTokens->Scope);
  _AddToken(cls, "Sphere", UsdGeomTokens->Sphere);
  _AddToken(cls, "TetMesh", UsdGeomTokens->TetMesh);
  _AddToken(cls, "VisibilityAPI", UsdGeomTokens->VisibilityAPI);
  _AddToken(cls, "Xform", UsdGeomTokens->Xform);
  _AddToken(cls, "Xformable", UsdGeomTokens->Xformable);
  _AddToken(cls, "XformCommonAPI", UsdGeomTokens->XformCommonAPI);
}
