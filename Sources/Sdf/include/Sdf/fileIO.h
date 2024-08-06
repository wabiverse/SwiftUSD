//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#ifndef PXR_USD_SDF_FILE_IO_H
#define PXR_USD_SDF_FILE_IO_H

#include "pxr/pxrns.h"

#include "Ar/arImpl.h"

#include "Ar/writableAsset.h"
#include "Tf/diagnosticLite.h"

#include <algorithm>
#include <cstring>
#include <memory>
#include <ostream>
#include <sstream>

PXR_NAMESPACE_OPEN_SCOPE

class SdfSpec;

// ArWritableAsset implementation that writes to a std::ostream.
class Sdf_StreamWritableAsset : public ArWritableAsset {
 public:
  explicit Sdf_StreamWritableAsset(std::ostream &out) : _out(out) {}

  virtual ~Sdf_StreamWritableAsset();

  bool Close() override
  {
    _out.flush();
    return true;
  }

  size_t Write(const void *buffer, size_t count, size_t offset) override
  {
    // The offset is ignored as we assume this object will only be
    // used for sequential writes. This is a performance optimization,
    // since calling tellp repeatedly can be expensive.
    // if (_out.tellp() != static_cast<ssize_t>(offset)) {
    //     _out.seekp(offset);
    // }

    _out.write(static_cast<const char *>(buffer), count);
    return count;
  }

 private:
  std::ostream &_out;
};

// Helper class for writing out strings for the text file format.
class Sdf_TextOutput {
 public:
  explicit Sdf_TextOutput(std::ostream &out)
      : Sdf_TextOutput(std::make_shared<Sdf_StreamWritableAsset>(out))
  {
  }

  explicit Sdf_TextOutput(std::shared_ptr<ArWritableAsset> &&asset)
      : _asset(std::move(asset)), _offset(0), _buffer(new char[BUFFER_SIZE]), _bufferPos(0)
  {
  }

  ~Sdf_TextOutput()
  {
    if (_asset) {
      Close();
    }
  }

  Sdf_TextOutput(const Sdf_TextOutput &) = delete;
  const Sdf_TextOutput &operator=(const Sdf_TextOutput &) = delete;

  // Close the output, flushing contents to destination.
  bool Close()
  {
    if (!_asset) {
      return true;
    }

    const bool ok = _FlushBuffer() && _asset->Close();
    _asset.reset();
    return ok;
  }

  // Write given \p str to output.
  bool Write(const std::string &str)
  {
    return _Write(str.c_str(), str.length());
  }

  // Write NUL-terminated character string \p str to output.
  bool Write(const char *str)
  {
    return _Write(str, strlen(str));
  }

 private:
  bool _Write(const char *str, size_t strLength)
  {
    // Much of the text format writing code writes small number of
    // characters at a time. Buffer writes to batch writes into larger
    // chunks.
    while (strLength != 0) {
      const size_t numAvail = BUFFER_SIZE - _bufferPos;
      const size_t numToCopy = std::min(numAvail, strLength);
      memcpy(_buffer.get() + _bufferPos, str, numToCopy);

      _bufferPos += numToCopy;
      str += numToCopy;
      strLength -= numToCopy;

      if (_bufferPos == BUFFER_SIZE) {
        if (!_FlushBuffer()) {
          return false;
        }
      }
    }

    return true;
  }

  bool _FlushBuffer()
  {
    if (_bufferPos == 0) {
      return true;
    }

    const size_t nWritten = _asset->Write(_buffer.get(), _bufferPos, _offset);

    if (nWritten != _bufferPos) {
      TF_RUNTIME_ERROR("Failed to write bytes");
      return false;
    }
    _offset += nWritten;
    _bufferPos = 0;
    return true;
  };

  std::shared_ptr<ArWritableAsset> _asset;
  size_t _offset;

  const size_t BUFFER_SIZE = 4096;
  std::unique_ptr<char[]> _buffer;
  size_t _bufferPos;
};

// Helper class for writing out strings for the text file format
// into a single string.
class Sdf_StringOutput : public Sdf_TextOutput {
 public:
  explicit Sdf_StringOutput() : Sdf_TextOutput(_str) {}

  // Closes the output and returns the text output as a string.
  std::string GetString()
  {
    Close();
    return _str.str();
  }

 private:
  std::stringstream _str;
};

// Write the provided \a spec to \a out indented \a indent levels.
bool Sdf_WriteToStream(const SdfSpec &spec, std::ostream &out, size_t indent);

PXR_NAMESPACE_CLOSE_SCOPE

#endif
