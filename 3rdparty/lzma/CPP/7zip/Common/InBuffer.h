// InBuffer.h

<<<<<<< HEAD
#ifndef __INBUFFER_H
#define __INBUFFER_H

#include "../IStream.h"
#include "../../Common/MyCom.h"
#include "../../Common/MyException.h"
=======
#ifndef __IN_BUFFER_H
#define __IN_BUFFER_H

#include "../../Common/MyException.h"
#include "../IStream.h"
>>>>>>> upstream/master

#ifndef _NO_EXCEPTIONS
struct CInBufferException: public CSystemException
{
  CInBufferException(HRESULT errorCode): CSystemException(errorCode) {}
};
#endif

<<<<<<< HEAD
class CInBuffer
{
  Byte *_buffer;
  Byte *_bufferLimit;
  Byte *_bufferBase;
  CMyComPtr<ISequentialInStream> _stream;
  UInt64 _processedSize;
  UInt32 _bufferSize;
  bool _wasFinished;

  bool ReadBlock();
  Byte ReadBlock2();
=======
class CInBufferBase
{
protected:
  Byte *_buf;
  Byte *_bufLim;
  Byte *_bufBase;

  ISequentialInStream *_stream;
  UInt64 _processedSize;
  size_t _bufSize; // actually it's number of Bytes for next read. The buf can be larger
                   // only up to 32-bits values now are supported!
  bool _wasFinished;

  bool ReadBlock();
  bool ReadByte_FromNewBlock(Byte &b);
  Byte ReadByte_FromNewBlock();
>>>>>>> upstream/master

public:
  #ifdef _NO_EXCEPTIONS
  HRESULT ErrorCode;
  #endif
<<<<<<< HEAD

  CInBuffer();
  ~CInBuffer() { Free(); }

  bool Create(UInt32 bufferSize);
  void Free();
  
  void SetStream(ISequentialInStream *stream);
  void Init();
  void ReleaseStream() { _stream.Release(); }

  bool ReadByte(Byte &b)
  {
    if (_buffer >= _bufferLimit)
      if (!ReadBlock())
        return false;
    b = *_buffer++;
    return true;
  }
  Byte ReadByte()
  {
    if (_buffer >= _bufferLimit)
      return ReadBlock2();
    return *_buffer++;
  }
  UInt32 ReadBytes(Byte *buf, UInt32 size)
  {
    if ((UInt32)(_bufferLimit - _buffer) >= size)
    {
      for (UInt32 i = 0; i < size; i++)
        buf[i] = _buffer[i];
      _buffer += size;
      return size;
    }
    for (UInt32 i = 0; i < size; i++)
    {
      if (_buffer >= _bufferLimit)
        if (!ReadBlock())
          return i;
      buf[i] = *_buffer++;
    }
    return size;
  }
  UInt64 GetProcessedSize() const { return _processedSize + (_buffer - _bufferBase); }
  bool WasFinished() const { return _wasFinished; }
=======
  UInt32 NumExtraBytes;

  CInBufferBase() throw();

  UInt64 GetStreamSize() const { return _processedSize + (_buf - _bufBase); }
  UInt64 GetProcessedSize() const { return _processedSize + NumExtraBytes + (_buf - _bufBase); }
  bool WasFinished() const { return _wasFinished; }

  void SetStream(ISequentialInStream *stream) { _stream = stream; }
  
  void SetBuf(Byte *buf, size_t bufSize, size_t end, size_t pos)
  {
    _bufBase = buf;
    _bufSize = bufSize;
    _processedSize = 0;
    _buf = buf + pos;
    _bufLim = buf + end;
    _wasFinished = false;
    #ifdef _NO_EXCEPTIONS
    ErrorCode = S_OK;
    #endif
    NumExtraBytes = 0;
  }

  void Init() throw();

  bool ReadByte(Byte &b)
  {
    if (_buf >= _bufLim)
      return ReadByte_FromNewBlock(b);
    b = *_buf++;
    return true;
  }
  
  Byte ReadByte()
  {
    if (_buf >= _bufLim)
      return ReadByte_FromNewBlock();
    return *_buf++;
  }
  
  size_t ReadBytes(Byte *buf, size_t size);
  size_t Skip(size_t size);
};

class CInBuffer: public CInBufferBase
{
public:
  ~CInBuffer() { Free(); }
  bool Create(size_t bufSize) throw(); // only up to 32-bits values now are supported!
  void Free() throw();
>>>>>>> upstream/master
};

#endif
