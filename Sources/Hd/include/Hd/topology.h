//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#ifndef PXR_IMAGING_HD_TOPOLOGY_H
#define PXR_IMAGING_HD_TOPOLOGY_H

#include "Arch/inttypes.h"
#include "Hd/api.h"
#include "Hd/version.h"
#include "pxr/pxrns.h"

#include <ostream>

PXR_NAMESPACE_OPEN_SCOPE

class HdTopology {
 public:
  typedef uint64_t ID;

  HdTopology() {};
  virtual ~HdTopology() {};

  /// Returns the hash value of this topology to be used for instancing.
  virtual ID ComputeHash() const = 0;
};

HD_API
std::ostream &operator<<(std::ostream &out, HdTopology const &);

PXR_NAMESPACE_CLOSE_SCOPE

#endif  // PXR_IMAGING_HD_TOPOLOGY_H
