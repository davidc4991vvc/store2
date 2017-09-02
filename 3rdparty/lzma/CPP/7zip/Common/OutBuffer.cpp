// OutBuffer.cpp

#include "StdAfx.h"

#include "../../../C/Alloc.h"

#include "OutBuffer.h"

<<<<<<< HEAD
bool COutBuffer::Create(UInt32 bufferSize)
{
  const UInt32 kMinBlockSize = 1;
  if (bufferSize < kMinBlockSize)
    bufferSize = kMinBlockSize;
  if (_buffer != 0 && _bufferSize == bufferSize)
    return true;
  Free();
  _bufferSize = bufferSize;
  _buffer = (Byte *)::MidAlloc(bufferSize);
  return (_buffer != 0);
}

void COutBuffer::Free()
{
  ::MidFree(_buffer);
  _buffer = 0;
}

void COutBuffer::SetStream(ISequentialOutStream *stream)
{
  _stream = stream;
}

void COutBuffer::Init()
{
  _streamPos = 0;
  _limitPos = _bufferSize;
=======
bool COutBuffer::Create(UInt32 bufSize) throw()
{
  const UInt32 kMinBlockSize = 1;
  if (bufSize < kMinBlockSize)
    bufSize = kMinBlockSize;
  if (_buf != 0 && _bufSize == bufSize)
    return true;
  Free();
  _bufSize = bufSize;
  _buf = (Byte *)::MidAlloc(bufSize);
  return (_buf != 0);
}

void COutBuffer::Free() throw()
{
  ::MidFree(_buf);
  _buf = 0;
}

void COutBuffer::Init() throw()
{
  _streamPos = 0;
  _limitPos = _bufSize;
>>>>>>> upstream/master
  _pos = 0;
  _processedSize = 0;
  _overDict = false;
  #ifdef _NO_EXCEPTIONS
  ErrorCode = S_OK;
  #endif
}

<<<<<<< HEAD
UInt64 COutBuffer::GetProcessedSize() const
{
  UInt64 res = _processedSize + _pos - _streamPos;
  if (_streamPos > _pos)
    res += _bufferSize;
=======
UInt64 COutBuffer::GetProcessedSize() const throw()
{
  UInt64 res = _processedSize + _pos - _streamPos;
  if (_streamPos > _pos)
    res += _bufSize;
>>>>>>> upstream/master
  return res;
}


<<<<<<< HEAD
HRESULT COutBuffer::FlushPart()
{
  // _streamPos < _bufferSize
  UInt32 size = (_streamPos >= _pos) ? (_bufferSize - _streamPos) : (_pos - _streamPos);
=======
HRESULT COutBuffer::FlushPart() throw()
{
  // _streamPos < _bufSize
  UInt32 size = (_streamPos >= _pos) ? (_bufSize - _streamPos) : (_pos - _streamPos);
>>>>>>> upstream/master
  HRESULT result = S_OK;
  #ifdef _NO_EXCEPTIONS
  result = ErrorCode;
  #endif
<<<<<<< HEAD
  if (_buffer2 != 0)
  {
    memmove(_buffer2, _buffer + _streamPos, size);
    _buffer2 += size;
=======
  if (_buf2 != 0)
  {
    memcpy(_buf2, _buf + _streamPos, size);
    _buf2 += size;
>>>>>>> upstream/master
  }

  if (_stream != 0
      #ifdef _NO_EXCEPTIONS
      && (ErrorCode == S_OK)
      #endif
     )
  {
    UInt32 processedSize = 0;
<<<<<<< HEAD
    result = _stream->Write(_buffer + _streamPos, size, &processedSize);
    size = processedSize;
  }
  _streamPos += size;
  if (_streamPos == _bufferSize)
    _streamPos = 0;
  if (_pos == _bufferSize)
=======
    result = _stream->Write(_buf + _streamPos, size, &processedSize);
    size = processedSize;
  }
  _streamPos += size;
  if (_streamPos == _bufSize)
    _streamPos = 0;
  if (_pos == _bufSize)
>>>>>>> upstream/master
  {
    _overDict = true;
    _pos = 0;
  }
<<<<<<< HEAD
  _limitPos = (_streamPos > _pos) ? _streamPos : _bufferSize;
=======
  _limitPos = (_streamPos > _pos) ? _streamPos : _bufSize;
>>>>>>> upstream/master
  _processedSize += size;
  return result;
}

<<<<<<< HEAD
HRESULT COutBuffer::Flush()
=======
HRESULT COutBuffer::Flush() throw()
>>>>>>> upstream/master
{
  #ifdef _NO_EXCEPTIONS
  if (ErrorCode != S_OK)
    return ErrorCode;
  #endif

<<<<<<< HEAD
  while(_streamPos != _pos)
=======
  while (_streamPos != _pos)
>>>>>>> upstream/master
  {
    HRESULT result = FlushPart();
    if (result != S_OK)
      return result;
  }
  return S_OK;
}

void COutBuffer::FlushWithCheck()
{
  HRESULT result = Flush();
  #ifdef _NO_EXCEPTIONS
  ErrorCode = result;
  #else
  if (result != S_OK)
    throw COutBufferException(result);
  #endif
}
