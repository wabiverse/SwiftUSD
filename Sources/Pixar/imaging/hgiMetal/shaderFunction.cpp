//
// Copyright 2020 Pixar
//
// Licensed under the Apache License, Version 2.0 (the "Apache License")
// with the following modification; you may not use this file except in
// compliance with the Apache License and the following modification to it:
// Section 6. Trademarks. is deleted and replaced with:
//
// 6. Trademarks. This License does not grant permission to use the trade
//    names, trademarks, service marks, or product names of the Licensor
//    and its affiliates, except as required to comply with Section 4(c) of
//    the License and to reproduce the content of the NOTICE file.
//
// You may obtain a copy of the Apache License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the Apache License with the above modification is
// distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
// KIND, either express or implied. See the Apache License for the specific
// language governing permissions and limitations under the Apache License.
//
#include "pxr/imaging/hgiMetal/hgi.h"
#include "pxr/imaging/hgiMetal/conversions.h"
#include "pxr/imaging/hgiMetal/diagnostic.h"
#include "pxr/imaging/hgiMetal/shaderFunction.h"
#include "pxr/imaging/hgiMetal/shaderGenerator.h"

#include "pxr/base/arch/defines.h"
#include "pxr/base/tf/diagnostic.h"

#include <unordered_map>

PXR_NAMESPACE_OPEN_SCOPE

void HgiMetalShaderFunction::ShaderErrorHandler(MTL::Library *library, NS::Error *error)
{
    if (error) {
        NS::String *err = error->localizedDescription();
        TF_CODING_ERROR("Error compiling shader: %s", err->utf8String());
        return;
    }

    NS::String *entryPoint = nullptr;
    switch (_descriptor.shaderStage) {
        case HgiShaderStageVertex:
            entryPoint = NS::String::string("vertexEntryPoint", NS::UTF8StringEncoding);
            break;
        case HgiShaderStageFragment:
            entryPoint = NS::String::string("fragmentEntryPoint", NS::UTF8StringEncoding);
            break;
        case HgiShaderStageCompute:
            entryPoint = NS::String::string("computeEntryPoint", NS::UTF8StringEncoding);
            break;
        case HgiShaderStagePostTessellationControl:
            entryPoint = NS::String::string("vertexEntryPoint", NS::UTF8StringEncoding);
            break;
        case HgiShaderStagePostTessellationVertex:
            entryPoint = NS::String::string("vertexEntryPoint", NS::UTF8StringEncoding);
            break;
        case HgiShaderStageTessellationControl:
        case HgiShaderStageTessellationEval:
        case HgiShaderStageGeometry:
            TF_CODING_ERROR("Todo: Unsupported shader stage");
            break;
    }

    // Load the function into the library
    const std::function<void(MTL::Function* func, NS::Error* error)>& libCompletionHandler = LibraryLoadShaderFuncErrorHandler;
    library->newFunction(entryPoint, nil, libCompletionHandler);
    library->release();
}

void HgiMetalShaderFunction::LibraryLoadShaderFuncErrorHandler(MTL::Function *func, NS::Error *error)
{
    if (error) {
        NS::String *err = error->localizedDescription();
        TF_CODING_ERROR("Error loading shader function: %s", err->utf8String());
    }

    if (!_shaderId) {
        NS::String *err = error->localizedDescription();
        _errors = err->utf8String();
    }
    else {
        HGIMETAL_DEBUG_LABEL(_shaderId, _descriptor.debugName.c_str());
    }
}

HgiMetalShaderFunction::HgiMetalShaderFunction(
    HgiMetal *hgi,
    HgiShaderFunctionDesc const& desc)
  : HgiShaderFunction(desc)
  , _shaderId(nil)
{
    if (desc.shaderCode) {
        MTL::Device *device = hgi->GetPrimaryDevice();
 
        HgiMetalShaderGenerator shaderGenerator {desc, device};
        shaderGenerator.Execute();
        const char *shaderCode = shaderGenerator.GetGeneratedShaderCode();

        MTL::CompileOptions *options = MTL::CompileOptions::alloc()->init();
        options->setFastMathEnabled(true);
        options->setLanguageVersion(MTL::LanguageVersion2_2);
        options->setPreprocessorMacros(
          NS::Dictionary::dictionary(NS::String::string("ARCH_GFX_METAL", NS::UTF8StringEncoding),
                                     NS::String::string("1", NS::UTF8StringEncoding))
        );

        // Compile the shader code into a library
        const MTL::NewLibraryCompletionHandlerFunction& errHandler = ShaderErrorHandler;
        hgi->GetPrimaryDevice()->newLibrary(NS::String::string(shaderCode, NS::UTF8StringEncoding), 
                                            options, 
                                            errHandler);
        options->release();
        options = nil;
    }

    // Clear these pointers in our copy of the descriptor since we
    // have to assume they could become invalid after we return.
    _descriptor.shaderCodeDeclarations = nullptr;
    _descriptor.shaderCode = nullptr;
    _descriptor.generatedShaderCodeOut = nullptr;
}

HgiMetalShaderFunction::~HgiMetalShaderFunction()
{
    _shaderId->release();
    _shaderId = nil;
}

bool
HgiMetalShaderFunction::IsValid() const
{
    return _errors.empty();
}

std::string const&
HgiMetalShaderFunction::GetCompileErrors()
{
    return _errors;
}

size_t
HgiMetalShaderFunction::GetByteSizeOfResource() const
{
    return 0;
}

uint64_t
HgiMetalShaderFunction::GetRawResource() const
{
    return (uint64_t) _shaderId;
}

MTL::Function*
HgiMetalShaderFunction::GetShaderId() const
{
    return _shaderId;
}

PXR_NAMESPACE_CLOSE_SCOPE
