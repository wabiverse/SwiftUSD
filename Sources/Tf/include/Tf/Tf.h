//
// Copyright 2016 Pixar
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
#ifndef __PXR_BASE_TF_H__
#define __PXR_BASE_TF_H__

#include <Tf/anyUniquePtr.h>
#include <Tf/anyWeakPtr.h>
#include <Tf/api.h>
#include <Tf/atomicOfstreamWrapper.h>
#include <Tf/atomicRenameUtil.h>
#include <Tf/bigRWMutex.h>
#include <Tf/bitUtils.h>
#include <Tf/callContext.h>
#include <Tf/cxxCast.h>
#include <Tf/debug.h>
#include <Tf/debugCodes.h>
#include <Tf/debugNotice.h>
#include <Tf/declarePtrs.h>
#include <Tf/denseHashMap.h>
#include <Tf/denseHashSet.h>
#include <Tf/diagnostic.h>
#include <Tf/diagnosticBase.h>
#include <Tf/diagnosticHelper.h>
#include <Tf/diagnosticLite.h>
#include <Tf/diagnosticMgr.h>
#include <Tf/dl.h>
#include <Tf/enum.h>
#include <Tf/envSetting.h>
#include <Tf/error.h>
#include <Tf/errorMark.h>
#include <Tf/errorTransport.h>
#include <Tf/exception.h>
#include <Tf/expiryNotifier.h>
#include <Tf/fastCompression.h>
#include <Tf/fileUtils.h>
#include <Tf/functionRef.h>
#include <Tf/functionTraits.h>
#include <Tf/getenv.h>
#include <Tf/hash.h>
#include <Tf/hashmap.h>
#include <Tf/hashset.h>
#include <Tf/instantiateSingleton.h>
#include <Tf/instantiateStacked.h>
#include <Tf/instantiateType.h>
// #include <Tf/iterator.h>
// #include <Tf/makePyConstructor.h>
#include <Tf/mallocTag.h>
#include <Tf/meta.h>
#include <Tf/notice.h>
#include <Tf/noticeRegistry.h>
#include <Tf/nullPtr.h>
#include <Tf/ostreamMethods.h>
#include <Tf/pathUtils.h>
#include <Tf/patternMatcher.h>
#include <Tf/pointerAndBits.h>
#include <Tf/preprocessorUtils.h>
#include <Tf/preprocessorUtilsLite.h>
// #include <Tf/pxrCLI11/CLI11.h>
// #include <Tf/pxrDoubleConversion/bignum-dtoa.h>
// #include <Tf/pxrDoubleConversion/bignum.h>
// #include <Tf/pxrDoubleConversion/cached-powers.h>
// #include <Tf/pxrDoubleConversion/diy-fp.h>
// #include <Tf/pxrDoubleConversion/double-conversion.h>
// #include <Tf/pxrDoubleConversion/fast-dtoa.h>
// #include <Tf/pxrDoubleConversion/fixed-dtoa.h>
// #include <Tf/pxrDoubleConversion/ieee.h>
// #include <Tf/pxrDoubleConversion/strtod.h>
// #include <Tf/pxrDoubleConversion/utils.h>
// #include <Tf/pxrLZ4/lz4.h>
#include <Tf/pxrPEGTL/pegtl.h>
#include <Tf/pxrTslRobinMap/robin_growth_policy.h>
#include <Tf/pxrTslRobinMap/robin_hash.h>
#include <Tf/pxrTslRobinMap/robin_map.h>
#include <Tf/pxrTslRobinMap/robin_set.h>

#include <Tf/py3Compat.h>
#include <Tf/pyAnnotatedBoolResult.h>
#include <Tf/pyArg.h>
#include <Tf/pyCall.h>
#include <Tf/pyCallContext.h>
#include <Tf/pyClassMethod.h>
#include <Tf/pyContainerConversions.h>
#include <Tf/pyEnum.h>
#include <Tf/pyError.h>
#include <Tf/pyErrorInternal.h>
#include <Tf/pyExceptionState.h>
#include <Tf/pyFunction.h>
#include <Tf/pyIdentity.h>
#include <Tf/pyInterpreter.h>
#include <Tf/pyInvoke.h>
#include <Tf/pyLock.h>
#include <Tf/pyModule.h>
#include <Tf/pyModuleNotice.h>
#include <Tf/pyNoticeWrapper.h>
#include <Tf/pyObjWrapper.h>
#include <Tf/pyObjectFinder.h>
#include <Tf/pyOptional.h>
#include <Tf/pyOverride.h>
#include <Tf/pyPolymorphic.h>
#include <Tf/pyPtrHelpers.h>
#include <Tf/pyResultConversions.h>
#include <Tf/pySafePython.h>
#include <Tf/pySignatureExt.h>
#include <Tf/pySingleton.h>
#include <Tf/pyStaticTokens.h>
#include <Tf/pyTracing.h>
#include <Tf/pyUtils.h>
#include <Tf/pyWrapContext.h>

#include <Tf/refBase.h>
#include <Tf/refCount.h>
#include <Tf/refPtr.h>
#include <Tf/refPtrTracker.h>
#include <Tf/regTest.h>
#include <Tf/registryManager.h>
#include <Tf/safeOutputFile.h>
#include <Tf/safeTypeCompare.h>
#include <Tf/scopeDescription.h>
#include <Tf/scopeDescriptionPrivate.h>
#include <Tf/scoped.h>
#include <Tf/scriptModuleLoader.h>
#include <Tf/setenv.h>
#include <Tf/singleton.h>
#include <Tf/smallVector.h>
#include <Tf/span.h>
#include <Tf/spinRWMutex.h>
#include <Tf/stackTrace.h>
#include <Tf/stacked.h>
#include <Tf/staticData.h>
#include <Tf/staticTokens.h>
#include <Tf/status.h>
#include <Tf/stl.h>
#include <Tf/stopwatch.h>
#include <Tf/stringUtils.h>
#include <Tf/templateString.h>
#include <Tf/token.h>
#include <Tf/type.h>
#include <Tf/typeFunctions.h>
#include <Tf/typeInfoMap.h>
#include <Tf/typeNotice.h>
#include <Tf/type_Impl.h>
#include <Tf/warning.h>
#include <Tf/weakBase.h>
#include <Tf/weakPtr.h>
#include <Tf/weakPtrFacade.h>
#include <Tf/wrapTypeHelpers.h>

#endif  // __PXR_BASE_TF_H__
