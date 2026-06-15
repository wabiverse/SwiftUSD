//
// Copyright 2025 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#include "Vdf/object.h"

#include "Vdf/connection.h"
#include "Vdf/input.h"
#include "Vdf/node.h"
#include "Vdf/output.h"

PXR_NAMESPACE_OPEN_SCOPE

const VdfNode *VdfObjectPtr::GetOwningNode() const
{
    switch (GetType())
    {
        case Node:
            return &GetNode();

        case Input:
            return &GetInput().GetNode();

        case Output:
            return &GetOutput().GetNode();

        default :
            break;
    }

    return NULL;
}

std::string
VdfObjectPtr::GetDebugName() const
{
    std::string name;

    if (*this)
    {
        Type type = GetType();
    
        if (type == Node)
        {
            name = "NODE: '" + GetNode().GetDebugName() + "'";
        }
        else if (type == Connection)
        {
            name = "CONN: '" + GetConnection().GetDebugName() + "'";
        }
        else if (type == Input)
        {
            name = "INPT: '" + GetInput().GetNode().GetDebugName() +
                   " [" + GetInput().GetName().GetString() + "]'";
        }
        else if (type == Output)
        {
            name = "OUTP: '"  + GetOutput().GetNode().GetDebugName() +
                   " [" + GetOutput().GetName().GetString() + "]'";
        }
    
        if (IsConst())
            name += " (const)";
    }
    else
        name = "<NULL>";

    return name;
}

PXR_NAMESPACE_CLOSE_SCOPE
