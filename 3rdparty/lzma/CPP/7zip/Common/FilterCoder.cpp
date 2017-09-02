// FilterCoder.cpp

#include "StdAfx.h"

<<<<<<< HEAD
#include "../../../C/Alloc.h"

=======
>>>>>>> upstream/master
#include "../../Common/Defs.h"

#include "FilterCoder.h"
#include "StreamUtils.h"

<<<<<<< HEAD
static const UInt32 kBufferSize = 1 << 17;

CFilterCoder::CFilterCoder()
{
  _buffer = (Byte *)::MidAlloc(kBufferSize);
  if (_buffer == 0)
    throw 1;
}

CFilterCoder::~CFilterCoder()
{
  ::MidFree(_buffer);
}

HRESULT CFilterCoder::WriteWithLimit(ISequentialOutStream *outStream, UInt32 size)
{
  if (_outSizeIsDefined)
  {
    UInt64 remSize = _outSize - _nowPos64;
    if (size > remSize)
      size = (UInt32)remSize;
  }
  RINOK(WriteStream(outStream, _buffer, size));
  _nowPos64 += size;
  return S_OK;
=======
/*
  AES filters need 16-bytes alignment for HARDWARE-AES instructions.
  So we call IFilter::Filter(, size), where (size != 16 * N) only for last data block.

  AES-CBC filters need data size aligned for 16-bytes.
  So the encoder can add zeros to the end of original stream.

  Some filters (BCJ and others) don't process data at the end of stream in some cases.
  So the encoder and decoder write such last bytes without change.
*/


static const UInt32 kBufSize = 1 << 20;

STDMETHODIMP CFilterCoder::SetInBufSize(UInt32 , UInt32 size) { _inBufSize = size; return S_OK; }
STDMETHODIMP CFilterCoder::SetOutBufSize(UInt32 , UInt32 size) { _outBufSize = size; return S_OK; }

HRESULT CFilterCoder::Alloc()
{
  UInt32 size = MyMin(_inBufSize, _outBufSize);
  /* minimal bufSize is 16 bytes for AES and IA64 filter.
     bufSize for AES must be aligned for 16 bytes.
     We use (1 << 12) min size to support future aligned filters. */
  const UInt32 kMinSize = 1 << 12;
  size &= ~(UInt32)(kMinSize - 1);
  if (size < kMinSize)
    size = kMinSize;
  if (!_buf || _bufSize != size)
  {
    AllocAlignedMask(size, 16 - 1);
    if (!_buf)
      return E_OUTOFMEMORY;
    _bufSize = size;
  }
  return S_OK;
}

HRESULT CFilterCoder::Init_and_Alloc()
{
  RINOK(Filter->Init());
  return Alloc();
}

CFilterCoder::CFilterCoder(bool encodeMode):
    _bufSize(0),
    _inBufSize(kBufSize),
    _outBufSize(kBufSize),
    _encodeMode(encodeMode),
    _outSizeIsDefined(false),
    _outSize(0),
    _nowPos64(0)
  {}

CFilterCoder::~CFilterCoder()
{
>>>>>>> upstream/master
}

STDMETHODIMP CFilterCoder::Code(ISequentialInStream *inStream, ISequentialOutStream *outStream,
    const UInt64 * /* inSize */, const UInt64 *outSize, ICompressProgressInfo *progress)
{
<<<<<<< HEAD
  RINOK(Init());
  UInt32 bufferPos = 0;
  _outSizeIsDefined = (outSize != 0);
  if (_outSizeIsDefined)
    _outSize = *outSize;

  while (!_outSizeIsDefined || _nowPos64 < _outSize)
  {
    size_t processedSize = kBufferSize - bufferPos;
    
    // Change it: It can be optimized using ReadPart
    RINOK(ReadStream(inStream, _buffer + bufferPos, &processedSize));
    
    UInt32 endPos = bufferPos + (UInt32)processedSize;

    bufferPos = Filter->Filter(_buffer, endPos);
    if (bufferPos > endPos)
    {
      for (; endPos < bufferPos; endPos++)
        _buffer[endPos] = 0;
      bufferPos = Filter->Filter(_buffer, endPos);
    }

    if (bufferPos == 0)
    {
      if (endPos == 0)
        return S_OK;
      return WriteWithLimit(outStream, endPos);
    }
    RINOK(WriteWithLimit(outStream, bufferPos));
    if (progress != NULL)
    {
      RINOK(progress->SetRatioInfo(&_nowPos64, &_nowPos64));
    }
    UInt32 i = 0;
    while (bufferPos < endPos)
      _buffer[i++] = _buffer[bufferPos++];
    bufferPos = i;
  }
  return S_OK;
}

STDMETHODIMP CFilterCoder::SetOutStream(ISequentialOutStream *outStream)
{
  _bufferPos = 0;
  _outStream = outStream;
  return Init();
=======
  RINOK(Init_and_Alloc());
  
  UInt64 nowPos64 = 0;
  bool inputFinished = false;
  UInt32 pos = 0;

  while (!outSize || nowPos64 < *outSize)
  {
    UInt32 endPos = pos;
    
    if (!inputFinished)
    {
      size_t processedSize = _bufSize - pos;
      RINOK(ReadStream(inStream, _buf + pos, &processedSize));
      endPos = pos + (UInt32)processedSize;
      inputFinished = (endPos != _bufSize);
    }

    pos = Filter->Filter(_buf, endPos);
    
    if (pos > endPos)
    {
      // AES
      if (!inputFinished || pos > _bufSize)
        return E_FAIL;
      if (!_encodeMode)
        return S_FALSE;
      
      do
        _buf[endPos] = 0;
      while (++endPos != pos);
      
      if (pos != Filter->Filter(_buf, pos))
        return E_FAIL;
    }

    if (endPos == 0)
      return S_OK;

    UInt32 size = (pos != 0 ? pos : endPos);
    if (outSize)
    {
      UInt64 remSize = *outSize - nowPos64;
      if (size > remSize)
        size = (UInt32)remSize;
    }
    
    RINOK(WriteStream(outStream, _buf, size));
    nowPos64 += size;

    if (pos == 0)
      return S_OK;

    if (progress)
      RINOK(progress->SetRatioInfo(&nowPos64, &nowPos64));

    UInt32 i = 0;
    while (pos < endPos)
      _buf[i++] = _buf[pos++];
    pos = i;
  }

  return S_OK;
}



// ---------- Write to Filter ----------

STDMETHODIMP CFilterCoder::SetOutStream(ISequentialOutStream *outStream)
{
  _outStream = outStream;
  return S_OK;
>>>>>>> upstream/master
}

STDMETHODIMP CFilterCoder::ReleaseOutStream()
{
  _outStream.Release();
  return S_OK;
}

<<<<<<< HEAD

STDMETHODIMP CFilterCoder::Write(const void *data, UInt32 size, UInt32 *processedSize)
{
  if (processedSize != NULL)
    *processedSize = 0;
  while (size > 0)
  {
    UInt32 sizeTemp = MyMin(size, kBufferSize - _bufferPos);
    memcpy(_buffer + _bufferPos, data, sizeTemp);
    size -= sizeTemp;
    if (processedSize != NULL)
      *processedSize += sizeTemp;
    data = (const Byte *)data + sizeTemp;
    UInt32 endPos = _bufferPos + sizeTemp;
    _bufferPos = Filter->Filter(_buffer, endPos);
    if (_bufferPos == 0)
    {
      _bufferPos = endPos;
      break;
    }
    if (_bufferPos > endPos)
    {
      if (size != 0)
        return E_FAIL;
      break;
    }
    RINOK(WriteWithLimit(_outStream, _bufferPos));
    UInt32 i = 0;
    while (_bufferPos < endPos)
      _buffer[i++] = _buffer[_bufferPos++];
    _bufferPos = i;
  }
  return S_OK;
}

STDMETHODIMP CFilterCoder::Flush()
{
  if (_bufferPos != 0)
  {
    // _buffer contains only data refused by previous Filter->Filter call.
    UInt32 endPos = Filter->Filter(_buffer, _bufferPos);
    if (endPos > _bufferPos)
    {
      for (; _bufferPos < endPos; _bufferPos++)
        _buffer[_bufferPos] = 0;
      if (Filter->Filter(_buffer, endPos) != endPos)
        return E_FAIL;
    }
    RINOK(WriteWithLimit(_outStream, _bufferPos));
    _bufferPos = 0;
  }
  CMyComPtr<IOutStreamFlush> flush;
  _outStream.QueryInterface(IID_IOutStreamFlush, &flush);
  if (flush)
    return flush->Flush();
  return S_OK;
}


STDMETHODIMP CFilterCoder::SetInStream(ISequentialInStream *inStream)
{
  _convertedPosBegin = _convertedPosEnd = _bufferPos = 0;
  _inStream = inStream;
  return Init();
=======
HRESULT CFilterCoder::Flush2()
{
  while (_convSize != 0)
  {
    UInt32 num = _convSize;
    if (_outSizeIsDefined)
    {
      UInt64 rem = _outSize - _nowPos64;
      if (num > rem)
        num = (UInt32)rem;
      if (num == 0)
        return k_My_HRESULT_WritingWasCut;
    }
    
    UInt32 processed = 0;
    HRESULT res = _outStream->Write(_buf + _convPos, num, &processed);
    if (processed == 0)
      return res != S_OK ? res : E_FAIL;
    
    _convPos += processed;
    _convSize -= processed;
    _nowPos64 += processed;
    RINOK(res);
  }
    
  if (_convPos != 0)
  {
    UInt32 num = _bufPos - _convPos;
    for (UInt32 i = 0; i < num; i++)
      _buf[i] = _buf[_convPos + i];
    _bufPos = num;
    _convPos = 0;
  }
    
  return S_OK;
}

STDMETHODIMP CFilterCoder::Write(const void *data, UInt32 size, UInt32 *processedSize)
{
  if (processedSize)
    *processedSize = 0;
  
  while (size != 0)
  {
    RINOK(Flush2());

    // _convSize is 0
    // _convPos is 0
    // _bufPos is small

    if (_bufPos != _bufSize)
    {
      UInt32 num = MyMin(size, _bufSize - _bufPos);
      memcpy(_buf + _bufPos, data, num);
      size -= num;
      data = (const Byte *)data + num;
      if (processedSize)
        *processedSize += num;
      _bufPos += num;
      if (_bufPos != _bufSize)
        continue;
    }

    // _bufPos == _bufSize
    _convSize = Filter->Filter(_buf, _bufPos);
    
    if (_convSize == 0)
      break;
    if (_convSize > _bufPos)
    {
      // that case is not possible.
      _convSize = 0;
      return E_FAIL;
    }
  }

  return S_OK;
}

STDMETHODIMP CFilterCoder::OutStreamFinish()
{
  for (;;)
  {
    RINOK(Flush2());
    if (_bufPos == 0)
      break;
    _convSize = Filter->Filter(_buf, _bufPos);
    if (_convSize == 0)
      _convSize = _bufPos;
    else if (_convSize > _bufPos)
    {
      // AES
      if (_convSize > _bufSize)
      {
        _convSize = 0;
        return E_FAIL;
      }
      if (!_encodeMode)
      {
        _convSize = 0;
        return S_FALSE;
      }
      for (; _bufPos < _convSize; _bufPos++)
        _buf[_bufPos] = 0;
      _convSize = Filter->Filter(_buf, _bufPos);
      if (_convSize != _bufPos)
        return E_FAIL;
    }
  }
  
  CMyComPtr<IOutStreamFinish> finish;
  _outStream.QueryInterface(IID_IOutStreamFinish, &finish);
  if (finish)
    return finish->OutStreamFinish();
  return S_OK;
}

// ---------- Init functions ----------

STDMETHODIMP CFilterCoder::InitEncoder()
{
  InitSpecVars();
  return Init_and_Alloc();
}

HRESULT CFilterCoder::Init_NoSubFilterInit()
{
  InitSpecVars();
  return Alloc();
}

STDMETHODIMP CFilterCoder::SetOutStreamSize(const UInt64 *outSize)
{
  InitSpecVars();
  if (outSize)
  {
    _outSize = *outSize;
    _outSizeIsDefined = true;
  }
  return Init_and_Alloc();
}

// ---------- Read from Filter ----------

STDMETHODIMP CFilterCoder::SetInStream(ISequentialInStream *inStream)
{
  _inStream = inStream;
  return S_OK;
>>>>>>> upstream/master
}

STDMETHODIMP CFilterCoder::ReleaseInStream()
{
  _inStream.Release();
  return S_OK;
}

<<<<<<< HEAD
STDMETHODIMP CFilterCoder::Read(void *data, UInt32 size, UInt32 *processedSize)
{
  if (processedSize != NULL)
    *processedSize = 0;
  while (size > 0)
  {
    if (_convertedPosBegin != _convertedPosEnd)
    {
      UInt32 sizeTemp = MyMin(size, _convertedPosEnd - _convertedPosBegin);
      memcpy(data, _buffer + _convertedPosBegin, sizeTemp);
      _convertedPosBegin += sizeTemp;
      data = (void *)((Byte *)data + sizeTemp);
      size -= sizeTemp;
      if (processedSize != NULL)
        *processedSize += sizeTemp;
      break;
    }
    UInt32 i;
    for (i = 0; _convertedPosEnd + i < _bufferPos; i++)
      _buffer[i] = _buffer[_convertedPosEnd + i];
    _bufferPos = i;
    _convertedPosBegin = _convertedPosEnd = 0;
    size_t processedSizeTemp = kBufferSize - _bufferPos;
    RINOK(ReadStream(_inStream, _buffer + _bufferPos, &processedSizeTemp));
    _bufferPos += (UInt32)processedSizeTemp;
    _convertedPosEnd = Filter->Filter(_buffer, _bufferPos);
    if (_convertedPosEnd == 0)
    {
      if (_bufferPos == 0)
        break;
      _convertedPosEnd = _bufferPos; // check it
      continue;
    }
    if (_convertedPosEnd > _bufferPos)
    {
      for (; _bufferPos < _convertedPosEnd; _bufferPos++)
        _buffer[_bufferPos] = 0;
      _convertedPosEnd = Filter->Filter(_buffer, _bufferPos);
    }
  }
  return S_OK;
}

#ifndef _NO_CRYPTO
STDMETHODIMP CFilterCoder::CryptoSetPassword(const Byte *data, UInt32 size)
{
  return _setPassword->CryptoSetPassword(data, size);
}
#endif

#ifndef EXTRACT_ONLY
STDMETHODIMP CFilterCoder::SetCoderProperties(const PROPID *propIDs,
      const PROPVARIANT *properties, UInt32 numProperties)
{
  return _SetCoderProperties->SetCoderProperties(propIDs, properties, numProperties);
}

STDMETHODIMP CFilterCoder::WriteCoderProperties(ISequentialOutStream *outStream)
{
  return _writeCoderProperties->WriteCoderProperties(outStream);
}

/*
STDMETHODIMP CFilterCoder::ResetSalt()
{
  return _CryptoResetSalt->ResetSalt();
}
*/

STDMETHODIMP CFilterCoder::ResetInitVector()
{
  return _CryptoResetInitVector->ResetInitVector();
}
#endif

STDMETHODIMP CFilterCoder::SetDecoderProperties2(const Byte *data, UInt32 size)
{
  return _setDecoderProperties->SetDecoderProperties2(data, size);
}
=======

STDMETHODIMP CFilterCoder::Read(void *data, UInt32 size, UInt32 *processedSize)
{
  if (processedSize)
    *processedSize = 0;
  
  while (size != 0)
  {
    if (_convSize != 0)
    {
      if (size > _convSize)
        size = _convSize;
      if (_outSizeIsDefined)
      {
        UInt64 rem = _outSize - _nowPos64;
        if (size > rem)
          size = (UInt32)rem;
      }
      memcpy(data, _buf + _convPos, size);
      _convPos += size;
      _convSize -= size;
      _nowPos64 += size;
      if (processedSize)
        *processedSize = size;
      break;
    }
  
    if (_convPos != 0)
    {
      UInt32 num = _bufPos - _convPos;
      for (UInt32 i = 0; i < num; i++)
        _buf[i] = _buf[_convPos + i];
      _bufPos = num;
      _convPos = 0;
    }
    
    {
      size_t readSize = _bufSize - _bufPos;
      HRESULT res = ReadStream(_inStream, _buf + _bufPos, &readSize);
      _bufPos += (UInt32)readSize;
      RINOK(res);
    }
    
    _convSize = Filter->Filter(_buf, _bufPos);
    
    if (_convSize == 0)
    {
      if (_bufPos == 0)
        break;
      // BCJ
      _convSize = _bufPos;
      continue;
    }
    
    if (_convSize > _bufPos)
    {
      // AES
      if (_convSize > _bufSize)
        return E_FAIL;
      if (!_encodeMode)
        return S_FALSE;
      
      do
        _buf[_bufPos] = 0;
      while (++_bufPos != _convSize);
      
      _convSize = Filter->Filter(_buf, _convSize);
      if (_convSize != _bufPos)
        return E_FAIL;
    }
  }
 
  return S_OK;
}


#ifndef _NO_CRYPTO

STDMETHODIMP CFilterCoder::CryptoSetPassword(const Byte *data, UInt32 size)
  { return _SetPassword->CryptoSetPassword(data, size); }

STDMETHODIMP CFilterCoder::SetKey(const Byte *data, UInt32 size)
  { return _CryptoProperties->SetKey(data, size); }

STDMETHODIMP CFilterCoder::SetInitVector(const Byte *data, UInt32 size)
  { return _CryptoProperties->SetInitVector(data, size); }

#endif


#ifndef EXTRACT_ONLY

STDMETHODIMP CFilterCoder::SetCoderProperties(const PROPID *propIDs,
    const PROPVARIANT *properties, UInt32 numProperties)
  { return _SetCoderProperties->SetCoderProperties(propIDs, properties, numProperties); }

STDMETHODIMP CFilterCoder::WriteCoderProperties(ISequentialOutStream *outStream)
  { return _WriteCoderProperties->WriteCoderProperties(outStream); }

/*
STDMETHODIMP CFilterCoder::ResetSalt()
  { return _CryptoResetSalt->ResetSalt(); }
*/

STDMETHODIMP CFilterCoder::ResetInitVector()
  { return _CryptoResetInitVector->ResetInitVector(); }

#endif


STDMETHODIMP CFilterCoder::SetDecoderProperties2(const Byte *data, UInt32 size)
  { return _SetDecoderProperties2->SetDecoderProperties2(data, size); }
>>>>>>> upstream/master
