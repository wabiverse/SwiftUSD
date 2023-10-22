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
#include "pxr/imaging/hgiMetal/capabilities.h"
#include "pxr/imaging/hgiMetal/conversions.h"
#include "pxr/imaging/hgiMetal/diagnostic.h"
#include "pxr/imaging/hgiMetal/graphicsPipeline.h"
#include "pxr/imaging/hgiMetal/resourceBindings.h"
#include "pxr/imaging/hgiMetal/shaderProgram.h"
#include "pxr/imaging/hgiMetal/shaderFunction.h"

#include "pxr/base/gf/half.h"

#include "pxr/base/tf/diagnostic.h"

#include <Foundation/Foundation.hpp>
#include <Metal/Metal.hpp>

PXR_NAMESPACE_OPEN_SCOPE

HgiMetalGraphicsPipeline::HgiMetalGraphicsPipeline(
    HgiMetal *hgi,
    HgiGraphicsPipelineDesc const& desc)
    : HgiGraphicsPipeline(desc)
    , _vertexDescriptor(nil)
    , _depthStencilState(nil)
    , _renderPipelineState(nil)
    , _constantTessFactors(nil)
{
    _CreateVertexDescriptor();
    _CreateDepthStencilState(hgi);
    _CreateRenderPipelineState(hgi);
}

HgiMetalGraphicsPipeline::~HgiMetalGraphicsPipeline()
{
    if (_renderPipelineState) {
        _renderPipelineState->release();
    }
    if (_depthStencilState) {
        _depthStencilState->release();
    }
    if (_vertexDescriptor) {
        _vertexDescriptor->release();
    }
    if (_constantTessFactors) {
        _constantTessFactors->release();
    }
}

void
HgiMetalGraphicsPipeline::_CreateVertexDescriptor()
{
    _vertexDescriptor = MTL::VertexDescriptor::alloc()->init();

    int index = 0;
    for (HgiVertexBufferDesc const& vbo : _descriptor.vertexBuffers) {

        HgiVertexAttributeDescVector const& vas = vbo.vertexAttributes;
        _vertexDescriptor->layouts()->object(index)->setStride(vbo.vertexStride);

        // Set the vertex step rate such that the attribute index
        // will advance only according to the base instance at the
        // start of each draw command of a multi-draw. To do this
        // we set the vertex attribute to be constant and advance
        // the vertex buffer offset appropriately when encoding
        // draw commands.
        if (vbo.vertexStepFunction == HgiVertexBufferStepFunctionConstant ||
            vbo.vertexStepFunction == HgiVertexBufferStepFunctionPerDrawCommand) {
            _vertexDescriptor->layouts()->object(index)->setStepFunction(MTL::VertexStepFunctionConstant);
            _vertexDescriptor->layouts()->object(index)->setStepRate(0);
        } else if (vbo.vertexStepFunction == HgiVertexBufferStepFunctionPerPatchControlPoint) {
            _vertexDescriptor->layouts()->object(index)->setStepFunction(MTL::VertexStepFunctionPerPatchControlPoint);
            _vertexDescriptor->layouts()->object(index)->setStepRate(1);
        }
        else {
            _vertexDescriptor->layouts()->object(index)->setStepFunction(MTL::VertexStepFunctionPerVertex);
            _vertexDescriptor->layouts()->object(index)->setStepRate(1);
        }

        // Describe each vertex attribute in the vertex buffer
        for (HgiVertexAttributeDesc const& va : vas) {
            uint32_t idx = va.shaderBindLocation;
            _vertexDescriptor->attributes()->object(idx)->setFormat(HgiMetalConversions::GetVertexFormat(va.format));
            _vertexDescriptor->attributes()->object(idx)->setBufferIndex(vbo.bindingIndex);
            _vertexDescriptor->attributes()->object(idx)->setOffset(va.offset);
        }

        index++;
    }
}

static
void
_SetTessellationStateFromShaderFunctions(
    MTL::RenderPipelineDescriptor *stateDesc,
    HgiShaderFunctionHandleVector const & shaderFuncs)
{
    const HgiShaderFunctionHandle *postTessVertexFunc = nullptr;
    for (const HgiShaderFunctionHandle &handle : shaderFuncs) {
        if (handle->GetDescriptor().shaderStage == HgiShaderStagePostTessellationVertex) {
            postTessVertexFunc = &handle;
        }
    }
    if (postTessVertexFunc == nullptr) {
        TF_CODING_ERROR("Did not find a post tess vertex function");
        return;
    }

    switch (postTessVertexFunc->Get()->GetDescriptor().tessellationDescriptor.spacing) {
        case HgiShaderFunctionTessellationDesc::Spacing::Equal:
            stateDesc->setTessellationPartitionMode(MTL::TessellationPartitionModeInteger);
            break;
        case HgiShaderFunctionTessellationDesc::Spacing::FractionalOdd:
            stateDesc->setTessellationPartitionMode(MTL::TessellationPartitionModeFractionalOdd);
            break;
        case HgiShaderFunctionTessellationDesc::Spacing::FractionalEven:
            stateDesc->setTessellationPartitionMode(MTL::TessellationPartitionModeFractionalEven);
            break;
        default:
            stateDesc->setTessellationPartitionMode(MTL::TessellationPartitionModeInteger);
            break;
    }

    switch (postTessVertexFunc->Get()->GetDescriptor().tessellationDescriptor.ordering) {
        case HgiShaderFunctionTessellationDesc::Ordering::CW:
            stateDesc->setTessellationOutputWindingOrder(MTL::WindingClockwise);
            break;
        case HgiShaderFunctionTessellationDesc::Ordering::CCW:
            stateDesc->setTessellationOutputWindingOrder(MTL::WindingCounterClockwise);
            break;
    }
}

void
HgiMetalGraphicsPipeline::_CreateRenderPipelineState(HgiMetal *hgi)
{
    MTL::RenderPipelineDescriptor *stateDesc = MTL::RenderPipelineDescriptor::alloc()->init();

    // Create a new render pipeline state object
    HGIMETAL_DEBUG_LABEL(stateDesc, _descriptor.debugName.c_str());
    stateDesc->setRasterSampleCount(_descriptor.multiSampleState.sampleCount);
    
    bool const icbSupport = hgi->GetCapabilities()->IsSet(HgiDeviceCapabilitiesBitsIndirectCommandBuffers);
    stateDesc->setSupportIndirectCommandBuffers(icbSupport);

    stateDesc->setInputPrimitiveTopology(HgiMetalConversions::GetPrimitiveClass(_descriptor.primitiveType));

    HgiMetalShaderProgram const *metalProgram = static_cast<HgiMetalShaderProgram*>(_descriptor.shaderProgram.Get());

    const bool usePTVSPath = _descriptor.primitiveType == HgiPrimitiveTypePatchList;
    if (usePTVSPath) {
        switch (_descriptor.tessellationState.tessFactorMode) {
            case HgiTessellationState::Constant:
                stateDesc->setVertexFunction(metalProgram->GetPostTessVertexFunction());
                stateDesc->setTessellationFactorStepFunction(MTL::TessellationFactorStepFunctionConstant);
                break;
            case HgiTessellationState::TessControl:
                stateDesc->setVertexFunction(metalProgram->GetPostTessControlFunction());
                stateDesc->setTessellationFactorStepFunction(MTL::TessellationFactorStepFunctionConstant);
                stateDesc->setTessellationPartitionMode(MTL::TessellationPartitionModePow2);
                break;
            case HgiTessellationState::TessVertex:
            {
                stateDesc->setVertexFunction(metalProgram->GetPostTessVertexFunction());
                stateDesc->setTessellationFactorStepFunction(MTL::TessellationFactorStepFunctionPerPatch);
                _SetTessellationStateFromShaderFunctions(stateDesc, metalProgram->GetShaderFunctions());
                break;
            }
            default:
                TF_CODING_ERROR("Unexpected tess factor mode");
        }

        // Basis curves should be treated as tris w/ polygonMode line
        // since Metal tessellation does not support isoline mode.
        if (stateDesc->inputPrimitiveTopology() == MTL::PrimitiveTopologyClassLine) {
            stateDesc->setInputPrimitiveTopology(MTL::PrimitiveTopologyClassTriangle);
        }

        if (_descriptor.tessellationState.patchType == HgiTessellationState::Isoline) {
            _descriptor.rasterizationState.polygonMode = HgiPolygonModeLine;
        }

        MTL::Winding winding = HgiMetalConversions::GetWinding(_descriptor.rasterizationState.winding);
        //flip the tess winding
        winding = (winding == MTL::WindingClockwise) ? MTL::WindingCounterClockwise : MTL::WindingClockwise;
        stateDesc->setTessellationOutputWindingOrder(winding);

        stateDesc->setTessellationControlPointIndexType(MTL::TessellationControlPointIndexTypeUInt32);

        // Set maxTessellationFactor to be consistent with GL etc.
        stateDesc->setMaxTessellationFactor(64);
    } else {
        stateDesc->setVertexFunction(metalProgram->GetVertexFunction());
    }
    
    MTL::Function *fragFunction = metalProgram->GetFragmentFunction();
    if (fragFunction && _descriptor.rasterizationState.rasterizerEnabled) {
        stateDesc->setFragmentFunction(fragFunction);
        stateDesc->setRasterizationEnabled(true);
    }
    else {
        stateDesc->setRasterizationEnabled(false);
    }

    // Color attachments
    for (size_t i = 0; i < _descriptor.colorAttachmentDescs.size(); i++) {
        HgiAttachmentDesc const &hgiColorAttachment = _descriptor.colorAttachmentDescs[i];
        MTL::RenderPipelineColorAttachmentDescriptor *metalColorAttachment = stateDesc->colorAttachments->object(i);
        
        metalColorAttachment->setPixelFormat(HgiMetalConversions::GetPixelFormat(hgiColorAttachment.format, hgiColorAttachment.usage));

        metalColorAttachment->setWriteMask(HgiMetalConversions::GetColorWriteMask(hgiColorAttachment.colorMask));

        if (hgiColorAttachment.blendEnabled) {
            metalColorAttachment->setBlendingEnabled(true);
            
            metalColorAttachment->setSourceRGBBlendFactor(HgiMetalConversions::GetBlendFactor(hgiColorAttachment.srcColorBlendFactor));
            metalColorAttachment->setDestinationRGBBlendFactor(HgiMetalConversions::GetBlendFactor(hgiColorAttachment.dstColorBlendFactor));
            
            metalColorAttachment->setSourceAlphaBlendFactor(HgiMetalConversions::GetBlendFactor(hgiColorAttachment.srcAlphaBlendFactor));
            metalColorAttachment->setDestinationAlphaBlendFactor(HgiMetalConversions::GetBlendFactor(hgiColorAttachment.dstAlphaBlendFactor));

            metalColorAttachment->setRgbBlendOperation(HgiMetalConversions::GetBlendEquation(hgiColorAttachment.colorBlendOp));
            metalColorAttachment->setAlphaBlendOperation(HgiMetalConversions::GetBlendEquation(hgiColorAttachment.alphaBlendOp));
        }
        else {
            metalColorAttachment->setBlendingEnabled(false);
        }
    }
    
    HgiAttachmentDesc const &hgiDepthAttachment = _descriptor.depthAttachmentDesc;

    MTL::PixelFormat depthPixelFormat = HgiMetalConversions::GetPixelFormat(hgiDepthAttachment.format, hgiDepthAttachment.usage);

    stateDesc->setDepthAttachmentPixelFormat(depthPixelFormat);
    
    if (_descriptor.depthAttachmentDesc.usage & HgiTextureUsageBitsStencilTarget) {
        stateDesc->setStencilAttachmentPixelFormat(depthPixelFormat);
    }

    stateDesc->setSampleCount(_descriptor.multiSampleState.sampleCount);
    if (_descriptor.multiSampleState.alphaToCoverageEnable) {
        stateDesc->setAlphaToCoverageEnabled(true);
    } else {
        stateDesc->setAlphaToCoverageEnabled(false);
    }
    if (_descriptor.multiSampleState.alphaToOneEnable) {
        stateDesc->setAlphaToOneEnabled(true);
    } else {
        stateDesc->setAlphaToOneEnabled(false);
    }

    stateDesc->setVertexDescriptor(_vertexDescriptor);

    NS::Error *error = NULL;
    MTL::Device *device = hgi->GetPrimaryDevice();
    _renderPipelineState = device->newRenderPipelineState(stateDesc, &error);
    stateDesc->release();
    
    if (!_renderPipelineState) {
        NS::String *err = error->localizedDescription();
        TF_WARN("Failed to created pipeline state, error %s", err->utf8String());
    }
}

static MTL::StencilDescriptor*
_CreateStencilDescriptor(HgiStencilState const & stencilState)
{
    MTL::StencilDescriptor *stencilDescriptor = MTL::StencilDescriptor::alloc()->init();

    stencilDescriptor->setStencilCompareFunction(HgiMetalConversions::GetCompareFunction(stencilState.compareFn));
    stencilDescriptor->setStencilFailureOperation(HgiMetalConversions::GetStencilOp(stencilState.stencilFailOp));
    stencilDescriptor->setDepthFailureOperation(HgiMetalConversions::GetStencilOp(stencilState.depthFailOp));
    stencilDescriptor->setDepthStencilPassOperation(HgiMetalConversions::GetStencilOp(stencilState.depthStencilPassOp));
    stencilDescriptor->setReadMask(stencilState.readMask);
    stencilDescriptor->setWriteMask(stencilState.writeMask);

    return stencilDescriptor;
}

void
HgiMetalGraphicsPipeline::_CreateDepthStencilState(HgiMetal *hgi)
{
    MTL::DepthStencilDescriptor *depthStencilStateDescriptor = MTL::DepthStencilDescriptor::alloc()->init();
    
    HGIMETAL_DEBUG_LABEL(depthStencilStateDescriptor, _descriptor.debugName.c_str());

    if (_descriptor.depthState.depthTestEnabled) {
        MTL::CompareFunction depthFn = HgiMetalConversions::GetCompareFunction(_descriptor.depthState.depthCompareFn);
        depthStencilStateDescriptor->setDepthCompareFunction(depthFn);
        if (_descriptor.depthState.depthWriteEnabled) {
            depthStencilStateDescriptor->setDepthWriteEnabled(true);
        }
        else {
            depthStencilStateDescriptor->setDepthWriteEnabled(false);
        }
    }
    else {
        // Even if there is no depth attachment, some drivers may still perform
        // the depth test. So we pick Always over Never.
        depthStencilStateDescriptor->setDepthCompareFunction(MTL::CompareFunctionAlways);
        depthStencilStateDescriptor->setDepthWriteEnabled(false);
    }
    
    if (_descriptor.depthState.stencilTestEnabled) {
        depthStencilStateDescriptor->setBackFaceStencil(_CreateStencilDescriptor(_descriptor.depthState.stencilFront));
        depthStencilStateDescriptor->setFrontFaceStencil(_CreateStencilDescriptor(_descriptor.depthState.stencilBack));
    }
    
    MTL::Device *device = hgi->GetPrimaryDevice();
    _depthStencilState = device->newDepthStencilState(depthStencilStateDescriptor);
    depthStencilStateDescriptor->release();

    TF_VERIFY(_depthStencilState, "Failed to created depth stencil state");
}

void
HgiMetalGraphicsPipeline::BindPipeline(MTL::RenderCommandEncoder *renderEncoder)
{
    renderEncoder->setRenderPipelineState(_renderPipelineState);
    if (_descriptor.primitiveType == HgiPrimitiveTypePatchList) {
        if (_constantTessFactors == nullptr) {

            // tess factors are half floats encoded as uint16_t
            uint16_t const factorZero = reinterpret_cast<uint16_t>(GfHalf(0.0f).bits());
            uint16_t const factorOne = reinterpret_cast<uint16_t>(GfHalf(1.0f).bits());

            if (_descriptor.tessellationState.patchType == HgiTessellationState::PatchType::Triangle) {
                MTL::TriangleTessellationFactorsHalf triangleFactors;
                triangleFactors.insideTessellationFactor = factorZero;
                triangleFactors.edgeTessellationFactor[0] = factorOne;
                triangleFactors.edgeTessellationFactor[1] = factorOne;
                triangleFactors.edgeTessellationFactor[2] = factorOne;
                _constantTessFactors = renderEncoder->device()->newBuffer(&triangleFactors, sizeof(triangleFactors), MTL::ResourceStorageModeShared);
            } else { // is Quad tess factor
                MTL::QuadTessellationFactorsHalf quadFactors;
                quadFactors.insideTessellationFactor[0] = factorZero;
                quadFactors.insideTessellationFactor[1] = factorZero;
                quadFactors.edgeTessellationFactor[0] = factorOne;
                quadFactors.edgeTessellationFactor[1] = factorOne;
                quadFactors.edgeTessellationFactor[2] = factorOne;
                quadFactors.edgeTessellationFactor[3] = factorOne;
                _constantTessFactors = renderEncoder->device()->newBuffer(&quadFactors, sizeof(quadFactors), MTL::ResourceStorageModeShared);
            }
        }
        renderEncoder->setTessellationFactorBuffer(_constantTessFactors, 0, 0);
    }

    //
    // DepthStencil state
    //
    HgiDepthStencilState const & dsState = _descriptor.depthState;
    if (_descriptor.depthState.depthBiasEnabled) {
        renderEncoder->setDepthBias(dsState.depthBiasConstantFactor, dsState.depthBiasSlopeFactor, 0.0f);
    }

    if (_descriptor.depthState.stencilTestEnabled) {
        renderEncoder->setStencilReferenceValues(dsState.stencilFront.referenceValue, dsState.stencilBack.referenceValue);
    }

    //
    // Rasterization state
    //
    renderEncoder->setCullMode(HgiMetalConversions::GetCullMode(_descriptor.rasterizationState.cullMode));
    renderEncoder->setTriangleFillMode(HgiMetalConversions::GetPolygonMode(_descriptor.rasterizationState.polygonMode));
    renderEncoder->setFrontFacingWinding(HgiMetalConversions::GetWinding(_descriptor.rasterizationState.winding));
    renderEncoder->setDepthStencilState(_depthStencilState);

    if (_descriptor.rasterizationState.depthClampEnabled) {
        renderEncoder->setDepthClipMode(MTL::DepthClipModeClamp);     
    }

    TF_VERIFY(_descriptor.rasterizationState.lineWidth == 1.0f, "Missing implementation buffers");
}

PXR_NAMESPACE_CLOSE_SCOPE
