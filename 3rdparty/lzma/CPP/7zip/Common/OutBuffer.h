// OutBuffer.h

<<<<<<< HEAD
#ifndef __OUTBUFFER_H
#define __OUTBUFFER_H
=======
#ifndef __OUT_BUFFER_H
#define __OUT_BUFFER_H
>>>>>>> upstream/master

#include "../IStream.h"
#include "../../Common/MyCom.h"
#include "../../Common/MyException.h"

#ifndef _NO_EXCEPTIONS
struct COutBufferException: public CSystemException
{
  COutBufferException(HRESULT errorCode): CSystemException(errorCode) {}
};
#endif

class COutBuffer
{
protected:
<<<<<<< HEAD
  Byte *_buffer;
  UInt32 _pos;
  UInt32 _limitPos;
  UInt32 _streamPos;
  UInt32 _bufferSize;
  CMyComPtr<ISequentialOutStream> _stream;
  UInt64 _processedSize;
  Byte  *_buffer2;
  bool _overDict;

  HRESULT FlushPart();
=======
  Byte *_buf;
  UInt32 _pos;
  UInt32 _limitPos;
  UInt32 _streamPos;
  UInt32 _bufSize;
  ISequentialOutStream *_stream;
  UInt64 _processedSize;
  Byte  *_buf2;
  bool _overDict;

  HRESULT FlushPart() throw();
>>>>>>> upstream/master
public:
  #ifdef _NO_EXCEPTIONS
  HRESULT ErrorCode;
  #endif

<<<<<<< HEAD
  COutBuffer(): _buffer(0), _pos(0), _stream(0), _buffer2(0) {}
  ~COutBuffer() { Free(); }
  
  bool Create(UInt32 bufferSize);
  void Free();

  void SetMemStream(Byte *buffer) { _buffer2 = buffer; }
  void SetStream(ISequentialOutStream *stream);
  void Init();
  HRESULT Flush();
  void FlushWithCheck();
  void ReleaseStream() {  _stream.Release(); }

  void WriteByte(Byte b)
  {
    _buffer[_pos++] = b;
    if(_pos == _limitPos)
=======
  COutBuffer(): _buf(0), _pos(0), _stream(0), _buf2(0) {}
  ~COutBuffer() { Free(); }
  
  bool Create(UInt32 bufSize) throw();
  void Free() throw();

  void SetMemStream(Byte *buf) { _buf2 = buf; }
  void SetStream(ISequentialOutStream *stream) { _stream = stream; }
  void Init() throw();
  HRESULT Flush() throw();
  void FlushWithCheck();

  void WriteByte(Byte b)
  {
    _buf[_pos++] = b;
    if (_pos == _limitPos)
>>>>>>> upstream/master
      FlushWithCheck();
  }
  void WriteBytes(const void *data, size_t size)
  {
    for (size_t i = 0; i < size; i++)
      WriteByte(((const Byte *)data)[i]);
  }

<<<<<<< HEAD
  UInt64 GetProcessedSize() const;
=======
  UInt64 GetProcessedSize() const throw();
>>>>>>> upstream/master
};

#endif
