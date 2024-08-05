#ifndef __PXR_BASE_JS_H__
#define __PXR_BASE_JS_H__

// js
#if defined(_WIN32)
#  include <Js/rapidjson/msinttypes/inttypes.h>
#  include <Js/rapidjson/msinttypes/stdint.h>
#endif  // defined(_WIN32)
#include <Js/rapidjson/allocators.h>
#include <Js/rapidjson/cursorstreamwrapper.h>
#include <Js/rapidjson/document.h>
#include <Js/rapidjson/encodedstream.h>
#include <Js/rapidjson/encodings.h>
#include <Js/rapidjson/error/en.h>
#include <Js/rapidjson/error/error.h>
#include <Js/rapidjson/filereadstream.h>
#include <Js/rapidjson/filewritestream.h>
#include <Js/rapidjson/fwd.h>
#include <Js/rapidjson/internal/biginteger.h>
#include <Js/rapidjson/internal/clzll.h>
#include <Js/rapidjson/internal/diyfp.h>
#include <Js/rapidjson/internal/dtoa.h>
#include <Js/rapidjson/internal/ieee754.h>
#include <Js/rapidjson/internal/itoa.h>
#include <Js/rapidjson/internal/meta.h>
#include <Js/rapidjson/internal/pow10.h>
#include <Js/rapidjson/internal/regex.h>
#include <Js/rapidjson/internal/stack.h>
#include <Js/rapidjson/internal/strfunc.h>
#include <Js/rapidjson/internal/strtod.h>
#include <Js/rapidjson/internal/swap.h>
#include <Js/rapidjson/istreamwrapper.h>
#include <Js/rapidjson/memorybuffer.h>
#include <Js/rapidjson/memorystream.h>
#include <Js/rapidjson/ostreamwrapper.h>
#include <Js/rapidjson/pointer.h>
#include <Js/rapidjson/prettywriter.h>
#include <Js/rapidjson/rapidjson.h>
#include <Js/rapidjson/reader.h>
#include <Js/rapidjson/schema.h>
#include <Js/rapidjson/stream.h>
#include <Js/rapidjson/stringbuffer.h>
#include <Js/rapidjson/uri.h>
#include <Js/rapidjson/writer.h>

#include <Js/api.h>
#include <Js/types.h>
#include <Js/value.h>

#include <Js/converter.h>
#include <Js/json.h>
#include <Js/utils.h>

#endif  // __PXR_BASE_JS_H__
