//
// Copyright 2025 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//

#include "Hd/legacyRenderControlInterface.h"

#include "Hd/renderDelegateInfo.h"

PXR_NAMESPACE_OPEN_SCOPE

HdRenderDelegateInfo
HdLegacyRenderControlInterface::GetRenderDelegateInfo() const
{
    HdRenderDelegateInfo info;

    info.materialBindingPurpose = GetMaterialBindingPurpose();
    info.materialRenderContexts = GetMaterialRenderContexts();
    info.renderSettingsNamespaces = GetRenderSettingsNamespaces();
    info.isPrimvarFilteringNeeded = IsPrimvarFilteringNeeded();
    info.shaderSourceTypes = GetShaderSourceTypes();
    info.isCoordSysSupported = IsCoordSysSupported();

    return info;
}

PXR_NAMESPACE_CLOSE_SCOPE
