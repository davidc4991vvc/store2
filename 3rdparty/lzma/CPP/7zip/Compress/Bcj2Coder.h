// Bcj2Coder.h

#ifndef __COMPRESS_BCJ2_CODER_H
#define __COMPRESS_BCJ2_CODER_H

<<<<<<< HEAD
=======
#include "../../../C/Bcj2.h"

>>>>>>> upstream/master
#include "../../Common/MyCom.h"

#include "../ICoder.h"

<<<<<<< HEAD
#include "RangeCoderBit.h"

namespace NCompress {
namespace NBcj2 {

const int kNumMoveBits = 5;
=======
namespace NCompress {
namespace NBcj2 {

class CBaseCoder
{
protected:
  Byte *_bufs[BCJ2_NUM_STREAMS + 1];
  UInt32 _bufsCurSizes[BCJ2_NUM_STREAMS + 1];
  UInt32 _bufsNewSizes[BCJ2_NUM_STREAMS + 1];

  HRESULT Alloc(bool allocForOrig = true);
public:
  CBaseCoder();
  ~CBaseCoder();
};

>>>>>>> upstream/master

#ifndef EXTRACT_ONLY

class CEncoder:
  public ICompressCoder2,
<<<<<<< HEAD
  public CMyUnknownImp
{
  Byte *_buffer;
  bool Create();

  COutBuffer _mainStream;
  COutBuffer _callStream;
  COutBuffer _jumpStream;
  NCompress::NRangeCoder::CEncoder _rangeEncoder;
  NCompress::NRangeCoder::CBitEncoder<kNumMoveBits> _statusEncoder[256 + 2];

  HRESULT Flush();
public:
  void ReleaseStreams()
  {
    _mainStream.ReleaseStream();
    _callStream.ReleaseStream();
    _jumpStream.ReleaseStream();
    _rangeEncoder.ReleaseStream();
  }

  class CCoderReleaser
  {
    CEncoder *_coder;
  public:
    CCoderReleaser(CEncoder *coder): _coder(coder) {}
    ~CCoderReleaser() {  _coder->ReleaseStreams(); }
  };

public:
  MY_UNKNOWN_IMP

  HRESULT CodeReal(ISequentialInStream **inStreams, const UInt64 **inSizes, UInt32 numInStreams,
      ISequentialOutStream **outStreams, const UInt64 **outSizes, UInt32 numOutStreams,
      ICompressProgressInfo *progress);
  STDMETHOD(Code)(ISequentialInStream **inStreams, const UInt64 **inSizes, UInt32 numInStreams,
      ISequentialOutStream **outStreams, const UInt64 **outSizes, UInt32 numOutStreams,
      ICompressProgressInfo *progress);
  CEncoder(): _buffer(0) {};
=======
  public ICompressSetCoderProperties,
  public ICompressSetBufSize,
  public CMyUnknownImp,
  public CBaseCoder
{
  UInt32 _relatLim;

  HRESULT CodeReal(ISequentialInStream * const *inStreams, const UInt64 * const *inSizes, UInt32 numInStreams,
      ISequentialOutStream * const *outStreams, const UInt64 * const *outSizes, UInt32 numOutStreams,
      ICompressProgressInfo *progress);

public:
  MY_UNKNOWN_IMP3(ICompressCoder2, ICompressSetCoderProperties, ICompressSetBufSize)

  STDMETHOD(Code)(ISequentialInStream * const *inStreams, const UInt64 * const *inSizes, UInt32 numInStreams,
      ISequentialOutStream * const *outStreams, const UInt64 * const *outSizes, UInt32 numOutStreams,
      ICompressProgressInfo *progress);

  STDMETHOD(SetCoderProperties)(const PROPID *propIDs, const PROPVARIANT *props, UInt32 numProps);
  
  STDMETHOD(SetInBufSize)(UInt32 streamIndex, UInt32 size);
  STDMETHOD(SetOutBufSize)(UInt32 streamIndex, UInt32 size);
  
  CEncoder();
>>>>>>> upstream/master
  ~CEncoder();
};

#endif

class CDecoder:
  public ICompressCoder2,
<<<<<<< HEAD
  public ICompressSetBufSize,
  public CMyUnknownImp
{
  CInBuffer _mainInStream;
  CInBuffer _callStream;
  CInBuffer _jumpStream;
  NCompress::NRangeCoder::CDecoder _rangeDecoder;
  NCompress::NRangeCoder::CBitDecoder<kNumMoveBits> _statusDecoder[256 + 2];

  COutBuffer _outStream;
  UInt32 _inBufSizes[4];
  UInt32 _outBufSize;

public:
  void ReleaseStreams()
  {
    _mainInStream.ReleaseStream();
    _callStream.ReleaseStream();
    _jumpStream.ReleaseStream();
    _rangeDecoder.ReleaseStream();
    _outStream.ReleaseStream();
  }

  HRESULT Flush() { return _outStream.Flush(); }
  class CCoderReleaser
  {
    CDecoder *_coder;
  public:
    CCoderReleaser(CDecoder *coder): _coder(coder) {}
    ~CCoderReleaser()  { _coder->ReleaseStreams(); }
  };

public:
  MY_UNKNOWN_IMP1(ICompressSetBufSize);
  HRESULT CodeReal(ISequentialInStream **inStreams, const UInt64 **inSizes, UInt32 numInStreams,
      ISequentialOutStream **outStreams, const UInt64 **outSizes, UInt32 numOutStreams,
      ICompressProgressInfo *progress);
  STDMETHOD(Code)(ISequentialInStream **inStreams, const UInt64 **inSizes, UInt32 numInStreams,
      ISequentialOutStream **outStreams, const UInt64 **outSizes, UInt32 numOutStreams,
      ICompressProgressInfo *progress);

  STDMETHOD(SetInBufSize)(UInt32 streamIndex, UInt32 size);
  STDMETHOD(SetOutBufSize)(UInt32 streamIndex, UInt32 size);
=======
  public ICompressSetFinishMode,
  public ICompressSetInStream2,
  public ISequentialInStream,
  public ICompressSetOutStreamSize,
  public ICompressSetBufSize,
  public CMyUnknownImp,
  public CBaseCoder
{
  unsigned _extraReadSizes[BCJ2_NUM_STREAMS];
  UInt64 _inStreamsProcessed[BCJ2_NUM_STREAMS];
  HRESULT _readRes[BCJ2_NUM_STREAMS];
  CMyComPtr<ISequentialInStream> _inStreams[BCJ2_NUM_STREAMS];

  bool _finishMode;
  bool _outSizeDefined;
  UInt64 _outSize;
  UInt64 _outSize_Processed;
  CBcj2Dec dec;

  void InitCommon();
  // HRESULT ReadSpec();
  
public:
  MY_UNKNOWN_IMP6(
    ICompressCoder2,
    ICompressSetFinishMode,
    ICompressSetInStream2,
    ISequentialInStream,
    ICompressSetOutStreamSize,
    ICompressSetBufSize
    );
  
  STDMETHOD(Code)(ISequentialInStream * const *inStreams, const UInt64 * const *inSizes, UInt32 numInStreams,
      ISequentialOutStream * const *outStreams, const UInt64 * const *outSizes, UInt32 numOutStreams,
      ICompressProgressInfo *progress);

  STDMETHOD(SetFinishMode)(UInt32 finishMode);

  STDMETHOD(SetInStream2)(UInt32 streamIndex, ISequentialInStream *inStream);
  STDMETHOD(ReleaseInStream2)(UInt32 streamIndex);

  STDMETHOD(Read)(void *data, UInt32 size, UInt32 *processedSize);

  STDMETHOD(SetOutStreamSize)(const UInt64 *outSize);

  STDMETHOD(SetInBufSize)(UInt32 streamIndex, UInt32 size);
  STDMETHOD(SetOutBufSize)(UInt32 streamIndex, UInt32 size);

>>>>>>> upstream/master
  CDecoder();
};

}}

#endif
