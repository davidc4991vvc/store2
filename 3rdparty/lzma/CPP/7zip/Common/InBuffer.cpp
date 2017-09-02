// InBuffer.cpp

#include "StdAfx.h"

#include "../../../C/Alloc.h"

#include "InBuffer.h"

<<<<<<< HEAD
CInBuffer::CInBuffer():
  _buffer(0),
  _bufferLimit(0),
  _bufferBase(0),
  _stream(0),
  _bufferSize(0)
{}

bool CInBuffer::Create(UInt32 bufferSize)
{
  const UInt32 kMinBlockSize = 1;
  if (bufferSize < kMinBlockSize)
    bufferSize = kMinBlockSize;
  if (_bufferBase != 0 && _bufferSize == bufferSize)
    return true;
  Free();
  _bufferSize = bufferSize;
  _bufferBase = (Byte *)::MidAlloc(bufferSize);
  return (_bufferBase != 0);
}

void CInBuffer::Free()
{
  ::MidFree(_bufferBase);
  _bufferBase = 0;
}

void CInBuffer::SetStream(ISequentialInStream *stream)
{
  _stream = stream;
}

void CInBuffer::Init()
{
  _processedSize = 0;
  _buffer = _bufferBase;
  _bufferLimit = _buffer;
=======
CInBufferBase::CInBufferBase() throw():
  _buf(0),
  _bufLim(0),
  _bufBase(0),
  _stream(0),
  _processedSize(0),
  _bufSize(0),
  _wasFinished(false),
  NumExtraBytes(0)
{}

bool CInBuffer::Create(size_t bufSize) throw()
{
  const unsigned kMinBlockSize = 1;
  if (bufSize < kMinBlockSize)
    bufSize = kMinBlockSize;
  if (_bufBase != 0 && _bufSize == bufSize)
    return true;
  Free();
  _bufSize = bufSize;
  _bufBase = (Byte *)::MidAlloc(bufSize);
  return (_bufBase != 0);
}

void CInBuffer::Free() throw()
{
  ::MidFree(_bufBase);
  _bufBase = 0;
}

void CInBufferBase::Init() throw()
{
  _processedSize = 0;
  _buf = _bufBase;
  _bufLim = _buf;
>>>>>>> upstream/master
  _wasFinished = false;
  #ifdef _NO_EXCEPTIONS
  ErrorCode = S_OK;
  #endif
<<<<<<< HEAD
}

bool CInBuffer::ReadBlock()
=======
  NumExtraBytes = 0;
}

bool CInBufferBase::ReadBlock()
>>>>>>> upstream/master
{
  #ifdef _NO_EXCEPTIONS
  if (ErrorCode != S_OK)
    return false;
  #endif
  if (_wasFinished)
    return false;
<<<<<<< HEAD
  _processedSize += (_buffer - _bufferBase);
  UInt32 numProcessedBytes;
  HRESULT result = _stream->Read(_bufferBase, _bufferSize, &numProcessedBytes);
=======
  _processedSize += (_buf - _bufBase);
  _buf = _bufBase;
  _bufLim = _bufBase;
  UInt32 processed;
  // FIX_ME: we can improve it to support (_bufSize >= (1 << 32))
  HRESULT result = _stream->Read(_bufBase, (UInt32)_bufSize, &processed);
>>>>>>> upstream/master
  #ifdef _NO_EXCEPTIONS
  ErrorCode = result;
  #else
  if (result != S_OK)
    throw CInBufferException(result);
  #endif
<<<<<<< HEAD
  _buffer = _bufferBase;
  _bufferLimit = _buffer + numProcessedBytes;
  _wasFinished = (numProcessedBytes == 0);
  return (!_wasFinished);
}

Byte CInBuffer::ReadBlock2()
{
  if (!ReadBlock())
  {
    _processedSize++;
    return 0xFF;
  }
  return *_buffer++;
=======
  _bufLim = _buf + processed;
  _wasFinished = (processed == 0);
  return !_wasFinished;
}

bool CInBufferBase::ReadByte_FromNewBlock(Byte &b)
{
  if (!ReadBlock())
  {
    NumExtraBytes++;
    b = 0xFF;
    return false;
  }
  b = *_buf++;
  return true;
}

Byte CInBufferBase::ReadByte_FromNewBlock()
{
  if (!ReadBlock())
  {
    NumExtraBytes++;
    return 0xFF;
  }
  return *_buf++;
}

size_t CInBufferBase::ReadBytes(Byte *buf, size_t size)
{
  if ((size_t)(_bufLim - _buf) >= size)
  {
    const Byte *src = _buf;
    for (size_t i = 0; i < size; i++)
      buf[i] = src[i];
    _buf += size;
    return size;
  }
  for (size_t i = 0; i < size; i++)
  {
    if (_buf >= _bufLim)
      if (!ReadBlock())
        return i;
    buf[i] = *_buf++;
  }
  return size;
}

size_t CInBufferBase::Skip(size_t size)
{
  size_t processed = 0;
  for (;;)
  {
    size_t rem = (_bufLim - _buf);
    if (rem >= size)
    {
      _buf += size;
      return processed + size;
    }
    _buf += rem;
    processed += rem;
    size -= rem;
    if (!ReadBlock())
      return processed;
  }
>>>>>>> upstream/master
}
