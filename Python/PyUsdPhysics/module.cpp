/*
====
Copyright (c) 2018, NVIDIA CORPORATION
======
*/

//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#if PXR_PYTHON_SUPPORT_ENABLED
#include "boost/python.hpp"
#endif // PXR_PYTHON_SUPPORT_ENABLED
#include "pxr/pxrns.h"
#include "Tf/pyModule.h"

PXR_NAMESPACE_USING_DIRECTIVE

TF_WRAP_MODULE
{
	TF_WRAP(Metrics);
	TF_WRAP(ParseUtils);

    // Generated Schema classes.  Do not remove or edit the following line.
    #include "generatedSchema.module.h"
}
