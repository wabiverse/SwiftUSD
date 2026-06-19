//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#ifndef EXECIR_GENERATED_CONTROLLER_H
#define EXECIR_GENERATED_CONTROLLER_H

/// \file execIr/controller.h

#include "pxr/pxrns.h"
#include "ExecIr/api.h"
#include "Usd/typed.h"
#include "Usd/prim.h"
#include "Usd/stage.h"

#include "Vt/value.h"

#include "Gf/vec3d.h"
#include "Gf/vec3f.h"
#include "Gf/matrix4d.h"

#include "Tf/token.h"
#include "Tf/type.h"

PXR_NAMESPACE_OPEN_SCOPE

class SdfAssetPath;

// -------------------------------------------------------------------------- //
// IRCONTROLLER                                                               //
// -------------------------------------------------------------------------- //

/// \class ExecIrController
///
/// 
/// An abstract schema that represents an invertible controller.
/// 
/// @warning
/// The functionality provided by this schema is very limited, subject to
/// change, and not yet ready for production use.
/// 
/// Controllers have explicit input and output attributes, a forward computation
/// that produces output values from input values and an inverse computation
/// that computes the input values that satisfy a given set of desired output
/// values.
/// 
///
class ExecIrController : public UsdTyped
{
public:
    /// Compile time constant representing what kind of schema this class is.
    ///
    /// \sa UsdSchemaKind
    static const UsdSchemaKind schemaKind = UsdSchemaKind::AbstractTyped;

    /// Construct a ExecIrController on UsdPrim \p prim .
    /// Equivalent to ExecIrController::Get(prim.GetStage(), prim.GetPath())
    /// for a \em valid \p prim, but will not immediately throw an error for
    /// an invalid \p prim
    explicit ExecIrController(const UsdPrim& prim=UsdPrim())
        : UsdTyped(prim)
    {
    }

    /// Construct a ExecIrController on the prim held by \p schemaObj .
    /// Should be preferred over ExecIrController(schemaObj.GetPrim()),
    /// as it preserves SchemaBase state.
    explicit ExecIrController(const UsdSchemaBase& schemaObj)
        : UsdTyped(schemaObj)
    {
    }

    /// Destructor.
    EXECIR_API
    virtual ~ExecIrController();

    /// Return a vector of names of all pre-declared attributes for this schema
    /// class and all its ancestor classes.  Does not include attributes that
    /// may be authored by custom/extended methods of the schemas involved.
    EXECIR_API
    static const TfTokenVector &
    GetSchemaAttributeNames(bool includeInherited=true);

    /// Return a ExecIrController holding the prim adhering to this
    /// schema at \p path on \p stage.  If no prim exists at \p path on
    /// \p stage, or if the prim at that path does not adhere to this schema,
    /// return an invalid schema object.  This is shorthand for the following:
    ///
    /// \code
    /// ExecIrController(stage->GetPrimAtPath(path));
    /// \endcode
    ///
    EXECIR_API
    static ExecIrController
    Get(const UsdStagePtr &stage, const SdfPath &path);


protected:
    /// Returns the kind of schema this class belongs to.
    ///
    /// \sa UsdSchemaKind
    EXECIR_API
    UsdSchemaKind _GetSchemaKind() const override;

private:
    // needs to invoke _GetStaticTfType.
    friend class UsdSchemaRegistry;
    EXECIR_API
    static const TfType &_GetStaticTfType();

    static bool _IsTypedSchema();

    // override SchemaBase virtuals.
    EXECIR_API
    const TfType &_GetTfType() const override;

public:
    // ===================================================================== //
    // Feel free to add custom code below this line, it will be preserved by 
    // the code generator. 
    //
    // Just remember to: 
    //  - Close the class declaration with }; 
    //  - Close the namespace with PXR_NAMESPACE_CLOSE_SCOPE
    //  - Close the include guard with #endif
    // ===================================================================== //
    // --(BEGIN CUSTOM CODE)--
};

PXR_NAMESPACE_CLOSE_SCOPE

#endif
