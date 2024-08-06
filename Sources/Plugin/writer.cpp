//
// Copyright 2019 Google LLC
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//

#include "writer.h"
#include "exportTranslator.h"
#include "flag.h"

#include "pxr/pxrns.h"

#include <draco/compression/encode.h>
#include <draco/mesh/mesh.h>

#include <algorithm>
#include <fstream>
#include <vector>

PXR_NAMESPACE_OPEN_SCOPE

bool UsdDraco_WriteDraco(const UsdGeomMesh &usdMesh,
                         const std::string &fileName,
                         int qp,
                         int qt,
                         int qn,
                         int cl,
                         int preservePolygons,
                         int preservePositionOrder,
                         int preserveHoles)
{
  // Translate USD mesh to Draco mesh.
  draco::Mesh dracoMesh;
  bool success = UsdDracoExportTranslator::Translate(
      usdMesh,
      &dracoMesh,
      UsdDracoFlag<bool>::MakeBooleanFlag(preservePolygons),
      UsdDracoFlag<bool>::MakeBooleanFlag(preservePositionOrder),
      UsdDracoFlag<bool>::MakeBooleanFlag(preserveHoles));
  if (!success) {
    std::cout << "Could not translate USD mesh to Draco mesh." << std::endl;
    return false;
  }

  // Set Draco options and encode mesh.
  draco::EncoderBuffer buffer;
  draco::Encoder encoder;
  encoder.SetEncodingMethod(draco::MESH_EDGEBREAKER_ENCODING);
  if (qp != 0)
    encoder.SetAttributeQuantization(draco::GeometryAttribute::POSITION, qp);
  if (qt != 0)
    encoder.SetAttributeQuantization(draco::GeometryAttribute::TEX_COORD, qt);
  if (qn != 0)
    encoder.SetAttributeQuantization(draco::GeometryAttribute::NORMAL, qn);

  const int speed = 10 - cl;
  encoder.SetSpeedOptions(speed, speed);
  if (!encoder.EncodeMeshToBuffer(dracoMesh, &buffer).ok()) {
    std::cout << "Could not encode mesh." << std::endl;
    return false;
  }

  // Write encoded Draco mesh to file.
  std::ofstream fout(fileName.c_str(), std::ios::binary);
  if (!fout.is_open()) {
    std::cout << "Failed to open file " << fileName << std::endl;
    return false;
  }
  fout.write(buffer.data(), buffer.size());
  fout.close();
  return true;
}

bool UsdDraco_PrimvarSupported(const UsdGeomPrimvar &primvar)
{
  return UsdDracoExportTranslator::CreateAttributeFrom(primvar) != nullptr;
}

PXR_NAMESPACE_CLOSE_SCOPE
