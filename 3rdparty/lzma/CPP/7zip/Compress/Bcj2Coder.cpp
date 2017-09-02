// Bcj2Coder.cpp

#include "StdAfx.h"

#include "../../../C/Alloc.h"

<<<<<<< HEAD
=======
#include "../Common/StreamUtils.h"

>>>>>>> upstream/master
#include "Bcj2Coder.h"

namespace NCompress {
namespace NBcj2 {

<<<<<<< HEAD
inline bool IsJcc(Byte b0, Byte b1) { return (b0 == 0x0F && (b1 & 0xF0) == 0x80); }
inline bool IsJ(Byte b0, Byte b1) { return ((b1 & 0xFE) == 0xE8 || IsJcc(b0, b1)); }
inline unsigned GetIndex(Byte b0, Byte b1) { return ((b1 == 0xE8) ? b0 : ((b1 == 0xE9) ? 256 : 257)); }

#ifndef EXTRACT_ONLY

static const int kBufferSize = 1 << 17;

static bool inline Test86MSByte(Byte b)
{
  return (b == 0 || b == 0xFF);
}

bool CEncoder::Create()
{
  if (!_mainStream.Create(1 << 18))
    return false;
  if (!_callStream.Create(1 << 18))
    return false;
  if (!_jumpStream.Create(1 << 18))
    return false;
  if (!_rangeEncoder.Create(1 << 20))
    return false;
  if (_buffer == 0)
  {
    _buffer = (Byte *)MidAlloc(kBufferSize);
    if (_buffer == 0)
      return false;
  }
  return true;
}

CEncoder::~CEncoder()
{
  ::MidFree(_buffer);
}

HRESULT CEncoder::Flush()
{
  RINOK(_mainStream.Flush());
  RINOK(_callStream.Flush());
  RINOK(_jumpStream.Flush());
  _rangeEncoder.FlushData();
  return _rangeEncoder.FlushStream();
}

const UInt32 kDefaultLimit = (1 << 24);

HRESULT CEncoder::CodeReal(ISequentialInStream **inStreams, const UInt64 **inSizes, UInt32 numInStreams,
    ISequentialOutStream **outStreams, const UInt64 ** /* outSizes */, UInt32 numOutStreams,
    ICompressProgressInfo *progress)
{
  if (numInStreams != 1 || numOutStreams != 4)
    return E_INVALIDARG;

  if (!Create())
    return E_OUTOFMEMORY;

  bool sizeIsDefined = false;
  UInt64 inSize = 0;
  if (inSizes != NULL)
    if (inSizes[0] != NULL)
    {
      inSize = *inSizes[0];
      if (inSize <= kDefaultLimit)
        sizeIsDefined = true;
    }

  CCoderReleaser releaser(this);

  ISequentialInStream *inStream = inStreams[0];

  _mainStream.SetStream(outStreams[0]);
  _mainStream.Init();
  _callStream.SetStream(outStreams[1]);
  _callStream.Init();
  _jumpStream.SetStream(outStreams[2]);
  _jumpStream.Init();
  _rangeEncoder.SetStream(outStreams[3]);
  _rangeEncoder.Init();
  for (int i = 0; i < 256 + 2; i++)
    _statusEncoder[i].Init();

  CMyComPtr<ICompressGetSubStreamSize> getSubStreamSize;
  {
    inStream->QueryInterface(IID_ICompressGetSubStreamSize, (void **)&getSubStreamSize);
  }

  UInt32 nowPos = 0;
  UInt64 nowPos64 = 0;
  UInt32 bufferPos = 0;

  Byte prevByte = 0;

  UInt64 subStreamIndex = 0;
  UInt64 subStreamStartPos  = 0;
  UInt64 subStreamEndPos = 0;

  for (;;)
  {
    UInt32 processedSize = 0;
    for (;;)
    {
      UInt32 size = kBufferSize - (bufferPos + processedSize);
      UInt32 processedSizeLoc;
      if (size == 0)
        break;
      RINOK(inStream->Read(_buffer + bufferPos + processedSize, size, &processedSizeLoc));
      if (processedSizeLoc == 0)
        break;
      processedSize += processedSizeLoc;
    }
    UInt32 endPos = bufferPos + processedSize;
    
    if (endPos < 5)
    {
      // change it
      for (bufferPos = 0; bufferPos < endPos; bufferPos++)
      {
        Byte b = _buffer[bufferPos];
        _mainStream.WriteByte(b);
        UInt32 index;
        if (b == 0xE8)
          index = prevByte;
        else if (b == 0xE9)
          index = 256;
        else if (IsJcc(prevByte, b))
          index = 257;
        else
        {
          prevByte = b;
          continue;
        }
        _statusEncoder[index].Encode(&_rangeEncoder, 0);
        prevByte = b;
      }
      return Flush();
    }

    bufferPos = 0;

    UInt32 limit = endPos - 5;
    while(bufferPos <= limit)
    {
      Byte b = _buffer[bufferPos];
      _mainStream.WriteByte(b);
      if (!IsJ(prevByte, b))
      {
        bufferPos++;
        prevByte = b;
        continue;
      }
      Byte nextByte = _buffer[bufferPos + 4];
      UInt32 src =
        (UInt32(nextByte) << 24) |
        (UInt32(_buffer[bufferPos + 3]) << 16) |
        (UInt32(_buffer[bufferPos + 2]) << 8) |
        (_buffer[bufferPos + 1]);
      UInt32 dest = (nowPos + bufferPos + 5) + src;
      // if (Test86MSByte(nextByte))
      bool convert;
      if (getSubStreamSize != NULL)
      {
        UInt64 currentPos = (nowPos64 + bufferPos);
        while (subStreamEndPos < currentPos)
        {
          UInt64 subStreamSize;
          HRESULT result = getSubStreamSize->GetSubStreamSize(subStreamIndex, &subStreamSize);
          if (result == S_OK)
          {
            subStreamStartPos = subStreamEndPos;
            subStreamEndPos += subStreamSize;
            subStreamIndex++;
          }
          else if (result == S_FALSE || result == E_NOTIMPL)
          {
            getSubStreamSize.Release();
            subStreamStartPos = 0;
            subStreamEndPos = subStreamStartPos - 1;
          }
          else
            return result;
        }
        if (getSubStreamSize == NULL)
        {
          if (sizeIsDefined)
            convert = (dest < inSize);
          else
            convert = Test86MSByte(nextByte);
        }
        else if (subStreamEndPos - subStreamStartPos > kDefaultLimit)
          convert = Test86MSByte(nextByte);
        else
        {
          UInt64 dest64 = (currentPos + 5) + Int64(Int32(src));
          convert = (dest64 >= subStreamStartPos && dest64 < subStreamEndPos);
        }
      }
      else if (sizeIsDefined)
        convert = (dest < inSize);
      else
        convert = Test86MSByte(nextByte);
      unsigned index = GetIndex(prevByte, b);
      if (convert)
      {
        _statusEncoder[index].Encode(&_rangeEncoder, 1);
        bufferPos += 5;
        COutBuffer &s = (b == 0xE8) ? _callStream : _jumpStream;
        for (int i = 24; i >= 0; i -= 8)
          s.WriteByte((Byte)(dest >> i));
        prevByte = nextByte;
      }
      else
      {
        _statusEncoder[index].Encode(&_rangeEncoder, 0);
        bufferPos++;
        prevByte = b;
      }
    }
    nowPos += bufferPos;
    nowPos64 += bufferPos;

    if (progress != NULL)
    {
      /*
      const UInt64 compressedSize =
        _mainStream.GetProcessedSize() +
        _callStream.GetProcessedSize() +
        _jumpStream.GetProcessedSize() +
        _rangeEncoder.GetProcessedSize();
      */
      RINOK(progress->SetRatioInfo(&nowPos64, NULL));
    }
 
    UInt32 i = 0;
    while(bufferPos < endPos)
      _buffer[i++] = _buffer[bufferPos++];
    bufferPos = i;
  }
}

STDMETHODIMP CEncoder::Code(ISequentialInStream **inStreams, const UInt64 **inSizes, UInt32 numInStreams,
    ISequentialOutStream **outStreams, const UInt64 **outSizes, UInt32 numOutStreams,
=======
CBaseCoder::CBaseCoder()
{
  for (int i = 0; i < BCJ2_NUM_STREAMS + 1; i++)
  {
    _bufs[i] = NULL;
    _bufsCurSizes[i] = 0;
    _bufsNewSizes[i] = (1 << 18);
  }
}

CBaseCoder::~CBaseCoder()
{
  for (int i = 0; i < BCJ2_NUM_STREAMS + 1; i++)
    ::MidFree(_bufs[i]);
}

HRESULT CBaseCoder::Alloc(bool allocForOrig)
{
  unsigned num = allocForOrig ? BCJ2_NUM_STREAMS + 1 : BCJ2_NUM_STREAMS;
  for (unsigned i = 0; i < num; i++)
  {
    UInt32 newSize = _bufsNewSizes[i];
    const UInt32 kMinBufSize = 1;
    if (newSize < kMinBufSize)
      newSize = kMinBufSize;
    if (!_bufs[i] || newSize != _bufsCurSizes[i])
    {
      if (_bufs[i])
      {
        ::MidFree(_bufs[i]);
        _bufs[i] = 0;
      }
      _bufsCurSizes[i] = 0;
      Byte *buf = (Byte *)::MidAlloc(newSize);
      _bufs[i] = buf;
      if (!buf)
        return E_OUTOFMEMORY;
      _bufsCurSizes[i] = newSize;
    }
  }
  return S_OK;
}



#ifndef EXTRACT_ONLY

CEncoder::CEncoder(): _relatLim(BCJ2_RELAT_LIMIT) {}
CEncoder::~CEncoder() {}

STDMETHODIMP CEncoder::SetInBufSize(UInt32, UInt32 size) { _bufsNewSizes[BCJ2_NUM_STREAMS] = size; return S_OK; }
STDMETHODIMP CEncoder::SetOutBufSize(UInt32 streamIndex, UInt32 size) { _bufsNewSizes[streamIndex] = size; return S_OK; }

STDMETHODIMP CEncoder::SetCoderProperties(const PROPID *propIDs, const PROPVARIANT *props, UInt32 numProps)
{
  UInt32 relatLim = BCJ2_RELAT_LIMIT;
  
  for (UInt32 i = 0; i < numProps; i++)
  {
    const PROPVARIANT &prop = props[i];
    PROPID propID = propIDs[i];
    if (propID >= NCoderPropID::kReduceSize)
      continue;
    switch (propID)
    {
      /*
      case NCoderPropID::kDefaultProp:
      {
        if (prop.vt != VT_UI4)
          return E_INVALIDARG;
        UInt32 v = prop.ulVal;
        if (v > 31)
          return E_INVALIDARG;
        relatLim = (UInt32)1 << v;
        break;
      }
      */
      case NCoderPropID::kDictionarySize:
      {
        if (prop.vt != VT_UI4)
          return E_INVALIDARG;
        relatLim = prop.ulVal;
        if (relatLim > ((UInt32)1 << 31))
          return E_INVALIDARG;
        break;
      }

      case NCoderPropID::kNumThreads:
        continue;
      case NCoderPropID::kLevel:
        continue;
     
      default: return E_INVALIDARG;
    }
  }
  
  _relatLim = relatLim;
  
  return S_OK;
}


HRESULT CEncoder::CodeReal(ISequentialInStream * const *inStreams, const UInt64 * const *inSizes, UInt32 numInStreams,
    ISequentialOutStream * const *outStreams, const UInt64 * const * /* outSizes */, UInt32 numOutStreams,
    ICompressProgressInfo *progress)
{
  if (numInStreams != 1 || numOutStreams != BCJ2_NUM_STREAMS)
    return E_INVALIDARG;

  RINOK(Alloc());

  UInt32 fileSize_for_Conv = 0;
  if (inSizes && inSizes[0])
  {
    UInt64 inSize = *inSizes[0];
    if (inSize <= BCJ2_FileSize_MAX)
      fileSize_for_Conv = (UInt32)inSize;
  }

  CMyComPtr<ICompressGetSubStreamSize> getSubStreamSize;
  inStreams[0]->QueryInterface(IID_ICompressGetSubStreamSize, (void **)&getSubStreamSize);

  CBcj2Enc enc;
    
  enc.src = _bufs[BCJ2_NUM_STREAMS];
  enc.srcLim = enc.src;
    
  {
    for (int i = 0; i < BCJ2_NUM_STREAMS; i++)
    {
      enc.bufs[i] = _bufs[i];
      enc.lims[i] = _bufs[i] + _bufsCurSizes[i];
    }
  }

  size_t numBytes_in_ReadBuf = 0;
  UInt64 prevProgress = 0;
  UInt64 totalStreamRead = 0; // size read from InputStream
  UInt64 currentInPos = 0; // data that was processed, it doesn't include data in input buffer and data in enc.temp
  UInt64 outSizeRc = 0;

  Bcj2Enc_Init(&enc);

  enc.fileIp = 0;
  enc.fileSize = fileSize_for_Conv;

  enc.relatLimit = _relatLim;

  enc.finishMode = BCJ2_ENC_FINISH_MODE_CONTINUE;

  bool needSubSize = false;
  UInt64 subStreamIndex = 0;
  UInt64 subStreamStartPos = 0;
  bool readWasFinished = false;

  for (;;)
  {
    if (needSubSize && getSubStreamSize)
    {
      enc.fileIp = 0;
      enc.fileSize = fileSize_for_Conv;
      enc.finishMode = BCJ2_ENC_FINISH_MODE_CONTINUE;
      
      for (;;)
      {
        UInt64 subStreamSize = 0;
        HRESULT result = getSubStreamSize->GetSubStreamSize(subStreamIndex, &subStreamSize);
        needSubSize = false;
        
        if (result == S_OK)
        {
          UInt64 newEndPos = subStreamStartPos + subStreamSize;
          
          bool isAccurateEnd = (newEndPos < totalStreamRead ||
            (newEndPos <= totalStreamRead && readWasFinished));
          
          if (newEndPos <= currentInPos && isAccurateEnd)
          {
            subStreamStartPos = newEndPos;
            subStreamIndex++;
            continue;
          }
          
          enc.srcLim = _bufs[BCJ2_NUM_STREAMS] + numBytes_in_ReadBuf;
          
          if (isAccurateEnd)
          {
            // data in enc.temp is possible here
            size_t rem = (size_t)(totalStreamRead - newEndPos);
            
            /* Pos_of(enc.src) <= old newEndPos <= newEndPos
               in another case, it's fail in some code */
            if ((size_t)(enc.srcLim - enc.src) < rem)
              return E_FAIL;
            
            enc.srcLim -= rem;
            enc.finishMode = BCJ2_ENC_FINISH_MODE_END_BLOCK;
          }
          
          if (subStreamSize <= BCJ2_FileSize_MAX)
          {
            enc.fileIp = enc.ip + (UInt32)(subStreamStartPos - currentInPos);
            enc.fileSize = (UInt32)subStreamSize;
          }
          break;
        }
        
        if (result == S_FALSE)
          break;
        if (result == E_NOTIMPL)
        {
          getSubStreamSize.Release();
          break;
        }
        return result;
      }
    }

    if (readWasFinished && totalStreamRead - currentInPos == Bcj2Enc_Get_InputData_Size(&enc))
      enc.finishMode = BCJ2_ENC_FINISH_MODE_END_STREAM;

    Bcj2Enc_Encode(&enc);

    currentInPos = totalStreamRead - numBytes_in_ReadBuf + (enc.src - _bufs[BCJ2_NUM_STREAMS]) - enc.tempPos;
    
    if (Bcj2Enc_IsFinished(&enc))
      break;

    if (enc.state < BCJ2_NUM_STREAMS)
    {
      size_t curSize = enc.bufs[enc.state] - _bufs[enc.state];
      // printf("Write stream = %2d %6d\n", enc.state, curSize);
      RINOK(WriteStream(outStreams[enc.state], _bufs[enc.state], curSize));
      if (enc.state == BCJ2_STREAM_RC)
        outSizeRc += curSize;

      enc.bufs[enc.state] = _bufs[enc.state];
      enc.lims[enc.state] = _bufs[enc.state] + _bufsCurSizes[enc.state];
    }
    else if (enc.state != BCJ2_ENC_STATE_ORIG)
      return E_FAIL;
    else
    {
      needSubSize = true;

      if (numBytes_in_ReadBuf != (size_t)(enc.src - _bufs[BCJ2_NUM_STREAMS]))
      {
        enc.srcLim = _bufs[BCJ2_NUM_STREAMS] + numBytes_in_ReadBuf;
        continue;
      }

      if (readWasFinished)
        continue;
      
      numBytes_in_ReadBuf = 0;
      enc.src    = _bufs[BCJ2_NUM_STREAMS];
      enc.srcLim = _bufs[BCJ2_NUM_STREAMS];
 
      UInt32 curSize = _bufsCurSizes[BCJ2_NUM_STREAMS];
      RINOK(inStreams[0]->Read(_bufs[BCJ2_NUM_STREAMS], curSize, &curSize));

      // printf("Read %6d bytes\n", curSize);
      if (curSize == 0)
      {
        readWasFinished = true;
        continue;
      }

      numBytes_in_ReadBuf = curSize;
      totalStreamRead += numBytes_in_ReadBuf;
      enc.srcLim = _bufs[BCJ2_NUM_STREAMS] + numBytes_in_ReadBuf;
    }

    if (progress && currentInPos - prevProgress >= (1 << 20))
    {
      UInt64 outSize2 = currentInPos + outSizeRc + enc.bufs[BCJ2_STREAM_RC] - enc.bufs[BCJ2_STREAM_RC];
      prevProgress = currentInPos;
      // printf("progress %8d, %8d\n", (int)inSize2, (int)outSize2);
      RINOK(progress->SetRatioInfo(&currentInPos, &outSize2));
    }
  }

  for (int i = 0; i < BCJ2_NUM_STREAMS; i++)
  {
    RINOK(WriteStream(outStreams[i], _bufs[i], enc.bufs[i] - _bufs[i]));
  }

  // if (currentInPos != subStreamStartPos + subStreamSize) return E_FAIL;

  return S_OK;
}

STDMETHODIMP CEncoder::Code(ISequentialInStream * const *inStreams, const UInt64 * const *inSizes, UInt32 numInStreams,
    ISequentialOutStream * const *outStreams, const UInt64 * const *outSizes, UInt32 numOutStreams,
>>>>>>> upstream/master
    ICompressProgressInfo *progress)
{
  try
  {
    return CodeReal(inStreams, inSizes, numInStreams, outStreams, outSizes,numOutStreams, progress);
  }
<<<<<<< HEAD
  catch(const COutBufferException &e) { return e.ErrorCode; }
  catch(...) { return S_FALSE; }
=======
  catch(...) { return E_FAIL; }
>>>>>>> upstream/master
}

#endif


<<<<<<< HEAD
STDMETHODIMP CDecoder::SetInBufSize(UInt32 streamIndex, UInt32 size) { _inBufSizes[streamIndex] = size; return S_OK; }
STDMETHODIMP CDecoder::SetOutBufSize(UInt32 , UInt32 size) { _outBufSize = size; return S_OK; }

CDecoder::CDecoder():
  _outBufSize(1 << 16)
{
  _inBufSizes[0] = 1 << 20;
  _inBufSizes[1] = 1 << 20;
  _inBufSizes[2] = 1 << 20;
  _inBufSizes[3] = 1 << 20;
}

HRESULT CDecoder::CodeReal(ISequentialInStream **inStreams, const UInt64 ** /* inSizes */, UInt32 numInStreams,
    ISequentialOutStream **outStreams, const UInt64 ** /* outSizes */, UInt32 numOutStreams,
    ICompressProgressInfo *progress)
{
  if (numInStreams != 4 || numOutStreams != 1)
    return E_INVALIDARG;

  if (!_mainInStream.Create(_inBufSizes[0]))
    return E_OUTOFMEMORY;
  if (!_callStream.Create(_inBufSizes[1]))
    return E_OUTOFMEMORY;
  if (!_jumpStream.Create(_inBufSizes[2]))
    return E_OUTOFMEMORY;
  if (!_rangeDecoder.Create(_inBufSizes[3]))
    return E_OUTOFMEMORY;
  if (!_outStream.Create(_outBufSize))
    return E_OUTOFMEMORY;

  CCoderReleaser releaser(this);

  _mainInStream.SetStream(inStreams[0]);
  _callStream.SetStream(inStreams[1]);
  _jumpStream.SetStream(inStreams[2]);
  _rangeDecoder.SetStream(inStreams[3]);
  _outStream.SetStream(outStreams[0]);

  _mainInStream.Init();
  _callStream.Init();
  _jumpStream.Init();
  _rangeDecoder.Init();
  _outStream.Init();

  for (int i = 0; i < 256 + 2; i++)
    _statusDecoder[i].Init();

  Byte prevByte = 0;
  UInt32 processedBytes = 0;
  for (;;)
  {
    if (processedBytes >= (1 << 20) && progress != NULL)
    {
      /*
      const UInt64 compressedSize =
        _mainInStream.GetProcessedSize() +
        _callStream.GetProcessedSize() +
        _jumpStream.GetProcessedSize() +
        _rangeDecoder.GetProcessedSize();
      */
      const UInt64 nowPos64 = _outStream.GetProcessedSize();
      RINOK(progress->SetRatioInfo(NULL, &nowPos64));
      processedBytes = 0;
    }
    UInt32 i;
    Byte b = 0;
    const UInt32 kBurstSize = (1 << 18);
    for (i = 0; i < kBurstSize; i++)
    {
      if (!_mainInStream.ReadByte(b))
        return Flush();
      _outStream.WriteByte(b);
      if (IsJ(prevByte, b))
        break;
      prevByte = b;
    }
    processedBytes += i;
    if (i == kBurstSize)
      continue;
    unsigned index = GetIndex(prevByte, b);
    if (_statusDecoder[index].Decode(&_rangeDecoder) == 1)
    {
      UInt32 src = 0;
      CInBuffer &s = (b == 0xE8) ? _callStream : _jumpStream;
      for (int i = 0; i < 4; i++)
      {
        Byte b0;
        if(!s.ReadByte(b0))
          return S_FALSE;
        src <<= 8;
        src |= ((UInt32)b0);
      }
      UInt32 dest = src - (UInt32(_outStream.GetProcessedSize()) + 4) ;
      _outStream.WriteByte((Byte)(dest));
      _outStream.WriteByte((Byte)(dest >> 8));
      _outStream.WriteByte((Byte)(dest >> 16));
      _outStream.WriteByte((Byte)(dest >> 24));
      prevByte = (Byte)(dest >> 24);
      processedBytes += 4;
    }
    else
      prevByte = b;
  }
}

STDMETHODIMP CDecoder::Code(ISequentialInStream **inStreams, const UInt64 **inSizes, UInt32 numInStreams,
    ISequentialOutStream **outStreams, const UInt64 **outSizes, UInt32 numOutStreams,
    ICompressProgressInfo *progress)
{
  try
  {
    return CodeReal(inStreams, inSizes, numInStreams, outStreams, outSizes,numOutStreams, progress);
  }
  catch(const CInBufferException &e) { return e.ErrorCode; }
  catch(const COutBufferException &e) { return e.ErrorCode; }
  catch(...) { return S_FALSE; }
=======




STDMETHODIMP CDecoder::SetInBufSize(UInt32 streamIndex, UInt32 size) { _bufsNewSizes[streamIndex] = size; return S_OK; }
STDMETHODIMP CDecoder::SetOutBufSize(UInt32 , UInt32 size) { _bufsNewSizes[BCJ2_NUM_STREAMS] = size; return S_OK; }

CDecoder::CDecoder(): _finishMode(false), _outSizeDefined(false), _outSize(0)
{}

STDMETHODIMP CDecoder::SetFinishMode(UInt32 finishMode)
{
  _finishMode = (finishMode != 0);
  return S_OK;
}

void CDecoder::InitCommon()
{
  {
    for (int i = 0; i < BCJ2_NUM_STREAMS; i++)
      dec.lims[i] = dec.bufs[i] = _bufs[i];
  }

  {
    for (int i = 0; i < BCJ2_NUM_STREAMS; i++)
    {
      _extraReadSizes[i] = 0;
      _inStreamsProcessed[i] = 0;
      _readRes[i] = S_OK;
    }
  }
    
  Bcj2Dec_Init(&dec);
}

HRESULT CDecoder::Code(ISequentialInStream * const *inStreams, const UInt64 * const *inSizes, UInt32 numInStreams,
    ISequentialOutStream * const *outStreams, const UInt64 * const *outSizes, UInt32 numOutStreams,
    ICompressProgressInfo *progress)
{
  if (numInStreams != BCJ2_NUM_STREAMS || numOutStreams != 1)
    return E_INVALIDARG;

  RINOK(Alloc());
    
  InitCommon();

  dec.destLim = dec.dest = _bufs[BCJ2_NUM_STREAMS];
  
  UInt64 outSizeProcessed = 0;
  UInt64 prevProgress = 0;

  HRESULT res = S_OK;

  for (;;)
  {
    if (Bcj2Dec_Decode(&dec) != SZ_OK)
      return S_FALSE;
    
    if (dec.state < BCJ2_NUM_STREAMS)
    {
      size_t totalRead = _extraReadSizes[dec.state];
      {
        Byte *buf = _bufs[dec.state];
        for (size_t i = 0; i < totalRead; i++)
          buf[i] = dec.bufs[dec.state][i];
        dec.lims[dec.state] =
        dec.bufs[dec.state] = buf;
      }

      if (_readRes[dec.state] != S_OK)
      {
        res = _readRes[dec.state];
        break;
      }

      do
      {
        UInt32 curSize = _bufsCurSizes[dec.state] - (UInt32)totalRead;
        /*
        we want to call Read even even if size is 0
        if (inSizes && inSizes[dec.state])
        {
          UInt64 rem = *inSizes[dec.state] - _inStreamsProcessed[dec.state];
          if (curSize > rem)
            curSize = (UInt32)rem;
        }
        */

        HRESULT res2 = inStreams[dec.state]->Read(_bufs[dec.state] + totalRead, curSize, &curSize);
        _readRes[dec.state] = res2;
        if (curSize == 0)
          break;
        _inStreamsProcessed[dec.state] += curSize;
        totalRead += curSize;
        if (res2 != S_OK)
          break;
      }
      while (totalRead < 4 && BCJ2_IS_32BIT_STREAM(dec.state));

      if (_readRes[dec.state] != S_OK)
        res = _readRes[dec.state];

      if (totalRead == 0)
        break;

      // res == S_OK;

      if (BCJ2_IS_32BIT_STREAM(dec.state))
      {
        unsigned extraSize = ((unsigned)totalRead & 3);
        _extraReadSizes[dec.state] = extraSize;
        if (totalRead < 4)
        {
          res = (_readRes[dec.state] != S_OK) ? _readRes[dec.state] : S_FALSE;
          break;
        }
        totalRead -= extraSize;
      }

      dec.lims[dec.state] = _bufs[dec.state] + totalRead;
    }
    else // if (dec.state <= BCJ2_STATE_ORIG)
    {
      size_t curSize = dec.dest - _bufs[BCJ2_NUM_STREAMS];
      if (curSize != 0)
      {
        outSizeProcessed += curSize;
        RINOK(WriteStream(outStreams[0], _bufs[BCJ2_NUM_STREAMS], curSize));
      }
      dec.dest = _bufs[BCJ2_NUM_STREAMS];
      {
        size_t rem = _bufsCurSizes[BCJ2_NUM_STREAMS];
        if (outSizes && outSizes[0])
        {
          UInt64 outSize = *outSizes[0] - outSizeProcessed;
          if (rem > outSize)
            rem = (size_t)outSize;
        }
        dec.destLim = dec.dest + rem;
        if (rem == 0)
          break;
      }
    }

    if (progress)
    {
      UInt64 outSize2 = outSizeProcessed + (dec.dest - _bufs[BCJ2_NUM_STREAMS]);
      if (outSize2 - prevProgress >= (1 << 22))
      {
        UInt64 inSize2 = outSize2 + _inStreamsProcessed[BCJ2_STREAM_RC] - (dec.lims[BCJ2_STREAM_RC] - dec.bufs[BCJ2_STREAM_RC]);
        RINOK(progress->SetRatioInfo(&inSize2, &outSize2));
        prevProgress = outSize2;
      }
    }
  }

  size_t curSize = dec.dest - _bufs[BCJ2_NUM_STREAMS];
  if (curSize != 0)
  {
    outSizeProcessed += curSize;
    RINOK(WriteStream(outStreams[0], _bufs[BCJ2_NUM_STREAMS], curSize));
  }

  if (res != S_OK)
    return res;

  if (_finishMode)
  {
    if (!Bcj2Dec_IsFinished(&dec))
      return S_FALSE;

    // we still allow the cases when input streams are larger than required for decoding.
    // so the case (dec.state == BCJ2_STATE_ORIG) is also allowed, if MAIN stream is larger than required.
    if (dec.state != BCJ2_STREAM_MAIN &&
        dec.state != BCJ2_DEC_STATE_ORIG)
      return S_FALSE;

    if (inSizes)
    {
      for (int i = 0; i < BCJ2_NUM_STREAMS; i++)
      {
        size_t rem = dec.lims[i] - dec.bufs[i] + _extraReadSizes[i];
        /*
        if (rem != 0)
          return S_FALSE;
        */
        if (inSizes[i] && *inSizes[i] != _inStreamsProcessed[i] - rem)
          return S_FALSE;
      }
    }
  }

  return S_OK;
}

STDMETHODIMP CDecoder::SetInStream2(UInt32 streamIndex, ISequentialInStream *inStream)
{
  _inStreams[streamIndex] = inStream;
  return S_OK;
}

STDMETHODIMP CDecoder::ReleaseInStream2(UInt32 streamIndex)
{
  _inStreams[streamIndex].Release();
  return S_OK;
}

STDMETHODIMP CDecoder::SetOutStreamSize(const UInt64 *outSize)
{
  _outSizeDefined = (outSize != NULL);
  _outSize = 0;
  if (_outSizeDefined)
    _outSize = *outSize;

  _outSize_Processed = 0;

  HRESULT res = Alloc(false);
  
  InitCommon();
  dec.destLim = dec.dest = NULL;

  return res;
}


STDMETHODIMP CDecoder::Read(void *data, UInt32 size, UInt32 *processedSize)
{
  if (processedSize)
    *processedSize = 0;

  if (size == 0)
    return S_OK;

  UInt32 totalProcessed = 0;
 
  if (_outSizeDefined)
  {
    UInt64 rem = _outSize - _outSize_Processed;
    if (size > rem)
      size = (UInt32)rem;
  }
  dec.dest = (Byte *)data;
  dec.destLim = (const Byte *)data + size;

  HRESULT res = S_OK;

  for (;;)
  {
    SRes sres = Bcj2Dec_Decode(&dec);
    if (sres != SZ_OK)
      return S_FALSE;
    
    {
      UInt32 curSize = (UInt32)(dec.dest - (Byte *)data);
      if (curSize != 0)
      {
        totalProcessed += curSize;
        if (processedSize)
          *processedSize = totalProcessed;
        data = (void *)((Byte *)data + curSize);
        size -= curSize;
        _outSize_Processed += curSize;
      }
    }

    if (dec.state >= BCJ2_NUM_STREAMS)
      break;

    {
      size_t totalRead = _extraReadSizes[dec.state];
      {
        Byte *buf = _bufs[dec.state];
        for (size_t i = 0; i < totalRead; i++)
          buf[i] = dec.bufs[dec.state][i];
        dec.lims[dec.state] =
        dec.bufs[dec.state] = buf;
      }

      if (_readRes[dec.state] != S_OK)
        return _readRes[dec.state];

      do
      {
        UInt32 curSize = _bufsCurSizes[dec.state] - (UInt32)totalRead;
        HRESULT res2 = _inStreams[dec.state]->Read(_bufs[dec.state] + totalRead, curSize, &curSize);
        _readRes[dec.state] = res2;
        if (curSize == 0)
          break;
        _inStreamsProcessed[dec.state] += curSize;
        totalRead += curSize;
        if (res2 != S_OK)
          break;
      }
      while (totalRead < 4 && BCJ2_IS_32BIT_STREAM(dec.state));

      if (totalRead == 0)
      {
        if (totalProcessed == 0)
          res = _readRes[dec.state];
        break;
      }

      if (BCJ2_IS_32BIT_STREAM(dec.state))
      {
        unsigned extraSize = ((unsigned)totalRead & 3);
        _extraReadSizes[dec.state] = extraSize;
        if (totalRead < 4)
        {
          if (totalProcessed != 0)
            return S_OK;
          return (_readRes[dec.state] != S_OK) ? _readRes[dec.state] : S_FALSE;
        }
        totalRead -= extraSize;
      }

      dec.lims[dec.state] = _bufs[dec.state] + totalRead;
    }
  }

  if (_finishMode && _outSizeDefined && _outSize == _outSize_Processed)
  {
    if (!Bcj2Dec_IsFinished(&dec))
      return S_FALSE;

    if (dec.state != BCJ2_STREAM_MAIN &&
        dec.state != BCJ2_DEC_STATE_ORIG)
      return S_FALSE;
  
    /*
    for (int i = 0; i < BCJ2_NUM_STREAMS; i++)
      if (dec.bufs[i] != dec.lims[i] || _extraReadSizes[i] != 0)
        return S_FALSE;
    */
  }

  return res;
>>>>>>> upstream/master
}

}}
