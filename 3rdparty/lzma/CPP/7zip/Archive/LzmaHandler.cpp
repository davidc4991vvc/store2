// LzmaHandler.cpp

#include "StdAfx.h"

#include "../../../C/CpuArch.h"

<<<<<<< HEAD
#include "Common/ComTry.h"
#include "Common/IntToString.h"

#include "Windows/PropVariant.h"

#include "../Common/CreateCoder.h"
=======
#include "../../Common/ComTry.h"
#include "../../Common/IntToString.h"

#include "../../Windows/PropVariant.h"

#include "../Common/FilterCoder.h"
>>>>>>> upstream/master
#include "../Common/ProgressUtils.h"
#include "../Common/RegisterArc.h"
#include "../Common/StreamUtils.h"

<<<<<<< HEAD
=======
#include "../Compress/BcjCoder.h"
>>>>>>> upstream/master
#include "../Compress/LzmaDecoder.h"

#include "Common/DummyOutStream.h"

using namespace NWindows;

namespace NArchive {
namespace NLzma {

static bool CheckDicSize(const Byte *p)
{
  UInt32 dicSize = GetUi32(p);
<<<<<<< HEAD
  for (int i = 1; i <= 30; i++)
=======
  if (dicSize == 1)
    return true;
  for (unsigned i = 0; i <= 30; i++)
>>>>>>> upstream/master
    if (dicSize == ((UInt32)2 << i) || dicSize == ((UInt32)3 << i))
      return true;
  return (dicSize == 0xFFFFFFFF);
}

<<<<<<< HEAD
STATPROPSTG kProps[] =
{
  { NULL, kpidSize, VT_UI8},
  { NULL, kpidPackSize, VT_UI8},
  { NULL, kpidMethod, VT_BSTR}
=======
static const Byte kProps[] =
{
  kpidSize,
  kpidPackSize,
  kpidMethod
};

static const Byte kArcProps[] =
{
  kpidNumStreams
>>>>>>> upstream/master
};

struct CHeader
{
  UInt64 Size;
  Byte FilterID;
  Byte LzmaProps[5];

  UInt32 GetDicSize() const { return GetUi32(LzmaProps + 1); }
  bool HasSize() const { return (Size != (UInt64)(Int64)-1); }
  bool Parse(const Byte *buf, bool isThereFilter);
};

bool CHeader::Parse(const Byte *buf, bool isThereFilter)
{
  FilterID = 0;
  if (isThereFilter)
    FilterID = buf[0];
  const Byte *sig = buf + (isThereFilter ? 1 : 0);
  for (int i = 0; i < 5; i++)
    LzmaProps[i] = sig[i];
  Size = GetUi64(sig + 5);
  return
    LzmaProps[0] < 5 * 5 * 9 &&
    FilterID < 2 &&
<<<<<<< HEAD
    (!HasSize() || Size < ((UInt64)1 << 56)) &&
    CheckDicSize(LzmaProps + 1);
=======
    (!HasSize() || Size < ((UInt64)1 << 56))
    && CheckDicSize(LzmaProps + 1);
>>>>>>> upstream/master
}

class CDecoder
{
<<<<<<< HEAD
  NCompress::NLzma::CDecoder *_lzmaDecoderSpec;
  CMyComPtr<ICompressCoder> _lzmaDecoder;
  CMyComPtr<ISequentialOutStream> _bcjStream;
public:
  ~CDecoder();
  HRESULT Create(DECL_EXTERNAL_CODECS_LOC_VARS
      bool filtered, ISequentialInStream *inStream);
=======
  CMyComPtr<ISequentialOutStream> _bcjStream;
  CFilterCoder *_filterCoder;
  CMyComPtr<ICompressCoder> _lzmaDecoder;
public:
  NCompress::NLzma::CDecoder *_lzmaDecoderSpec;

  ~CDecoder();
  HRESULT Create(bool filtered, ISequentialInStream *inStream);
>>>>>>> upstream/master

  HRESULT Code(const CHeader &header, ISequentialOutStream *outStream, ICompressProgressInfo *progress);

  UInt64 GetInputProcessedSize() const { return _lzmaDecoderSpec->GetInputProcessedSize(); }

  void ReleaseInStream() { if (_lzmaDecoder) _lzmaDecoderSpec->ReleaseInStream(); }

  HRESULT ReadInput(Byte *data, UInt32 size, UInt32 *processedSize)
    { return _lzmaDecoderSpec->ReadFromInputStream(data, size, processedSize); }
};

<<<<<<< HEAD
static const UInt64 k_BCJ = 0x03030103;
  
HRESULT CDecoder::Create(
    DECL_EXTERNAL_CODECS_LOC_VARS
    bool filteredMode, ISequentialInStream *inStream)
=======
HRESULT CDecoder::Create(bool filteredMode, ISequentialInStream *inStream)
>>>>>>> upstream/master
{
  if (!_lzmaDecoder)
  {
    _lzmaDecoderSpec = new NCompress::NLzma::CDecoder;
<<<<<<< HEAD
=======
    _lzmaDecoderSpec->FinishStream = true;
>>>>>>> upstream/master
    _lzmaDecoder = _lzmaDecoderSpec;
  }

  if (filteredMode)
  {
    if (!_bcjStream)
    {
<<<<<<< HEAD
      CMyComPtr<ICompressCoder> coder;
      RINOK(CreateCoder(EXTERNAL_CODECS_LOC_VARS k_BCJ, coder, false));
      if (!coder)
        return E_NOTIMPL;
      coder.QueryInterface(IID_ISequentialOutStream, &_bcjStream);
      if (!_bcjStream)
        return E_NOTIMPL;
=======
      _filterCoder = new CFilterCoder(false);
      CMyComPtr<ICompressCoder> coder = _filterCoder;
      _filterCoder->Filter = new NCompress::NBcj::CCoder(false);
      _bcjStream = _filterCoder;
>>>>>>> upstream/master
    }
  }

  return _lzmaDecoderSpec->SetInStream(inStream);
}

CDecoder::~CDecoder()
{
  ReleaseInStream();
}

HRESULT CDecoder::Code(const CHeader &header, ISequentialOutStream *outStream,
    ICompressProgressInfo *progress)
{
  if (header.FilterID > 1)
    return E_NOTIMPL;

  {
    CMyComPtr<ICompressSetDecoderProperties2> setDecoderProperties;
    _lzmaDecoder.QueryInterface(IID_ICompressSetDecoderProperties2, &setDecoderProperties);
    if (!setDecoderProperties)
      return E_NOTIMPL;
    RINOK(setDecoderProperties->SetDecoderProperties2(header.LzmaProps, 5));
  }

<<<<<<< HEAD
  CMyComPtr<ICompressSetOutStream> setOutStream;

=======
>>>>>>> upstream/master
  bool filteredMode = (header.FilterID == 1);

  if (filteredMode)
  {
<<<<<<< HEAD
    _bcjStream.QueryInterface(IID_ICompressSetOutStream, &setOutStream);
    if (!setOutStream)
      return E_NOTIMPL;
    RINOK(setOutStream->SetOutStream(outStream));
    outStream = _bcjStream;
=======
    RINOK(_filterCoder->SetOutStream(outStream));
    outStream = _bcjStream;
    RINOK(_filterCoder->SetOutStreamSize(NULL));
>>>>>>> upstream/master
  }

  const UInt64 *Size = header.HasSize() ? &header.Size : NULL;
  HRESULT res = _lzmaDecoderSpec->CodeResume(outStream, Size, progress);

  if (filteredMode)
  {
<<<<<<< HEAD
    CMyComPtr<IOutStreamFlush> flush;
    _bcjStream.QueryInterface(IID_IOutStreamFlush, &flush);
    if (flush)
    {
      HRESULT res2 = flush->Flush();
      if (res == S_OK)
        res = res2;
    }
    HRESULT res2 = setOutStream->ReleaseOutStream();
    if (res == S_OK)
      res = res2;
  }
  RINOK(res);

=======
    {
      HRESULT res2 = _filterCoder->OutStreamFinish();
      if (res == S_OK)
        res = res2;
    }
    HRESULT res2 = _filterCoder->ReleaseOutStream();
    if (res == S_OK)
      res = res2;
  }
  
  RINOK(res);

  if (header.HasSize())
    if (_lzmaDecoderSpec->GetOutputProcessedSize() != header.Size)
      return S_FALSE;

>>>>>>> upstream/master
  return S_OK;
}


class CHandler:
  public IInArchive,
  public IArchiveOpenSeq,
<<<<<<< HEAD
  PUBLIC_ISetCompressCodecsInfo
=======
>>>>>>> upstream/master
  public CMyUnknownImp
{
  CHeader _header;
  bool _lzma86;
<<<<<<< HEAD
  UInt64 _startPosition;
  UInt64 _packSize;
  bool _packSizeDefined;
  CMyComPtr<IInStream> _stream;
  CMyComPtr<ISequentialInStream> _seqStream;

  DECL_EXTERNAL_CODECS_VARS
  DECL_ISetCompressCodecsInfo

public:
  MY_QUERYINTERFACE_BEGIN2(IInArchive)
  MY_QUERYINTERFACE_ENTRY(IArchiveOpenSeq)
  QUERY_ENTRY_ISetCompressCodecsInfo
  MY_QUERYINTERFACE_END
  MY_ADDREF_RELEASE
=======
  CMyComPtr<IInStream> _stream;
  CMyComPtr<ISequentialInStream> _seqStream;
  
  bool _isArc;
  bool _needSeekToStart;
  bool _dataAfterEnd;
  bool _needMoreInput;

  bool _packSize_Defined;
  bool _unpackSize_Defined;
  bool _numStreams_Defined;

  bool _unsupported;
  bool _dataError;

  UInt64 _packSize;
  UInt64 _unpackSize;
  UInt64 _numStreams;

public:
  MY_UNKNOWN_IMP2(IInArchive, IArchiveOpenSeq)
>>>>>>> upstream/master

  INTERFACE_IInArchive(;)
  STDMETHOD(OpenSeq)(ISequentialInStream *stream);

  CHandler(bool lzma86) { _lzma86 = lzma86; }

  unsigned GetHeaderSize() const { return 5 + 8 + (_lzma86 ? 1 : 0); }

};

IMP_IInArchive_Props
<<<<<<< HEAD
IMP_IInArchive_ArcProps_NO_Table
=======
IMP_IInArchive_ArcProps
>>>>>>> upstream/master

STDMETHODIMP CHandler::GetArchiveProperty(PROPID propID, PROPVARIANT *value)
{
  NCOM::CPropVariant prop;
<<<<<<< HEAD
  switch(propID)
  {
    case kpidPhySize: if (_packSizeDefined) prop = _packSize; break;
=======
  switch (propID)
  {
    case kpidPhySize: if (_packSize_Defined) prop = _packSize; break;
    case kpidNumStreams: if (_numStreams_Defined) prop = _numStreams; break;
    case kpidUnpackSize: if (_unpackSize_Defined) prop = _unpackSize; break;
    case kpidErrorFlags:
    {
      UInt32 v = 0;
      if (!_isArc) v |= kpv_ErrorFlags_IsNotArc;;
      if (_needMoreInput) v |= kpv_ErrorFlags_UnexpectedEnd;
      if (_dataAfterEnd) v |= kpv_ErrorFlags_DataAfterEnd;
      if (_unsupported) v |= kpv_ErrorFlags_UnsupportedMethod;
      if (_dataError) v |= kpv_ErrorFlags_DataError;
      prop = v;
    }
>>>>>>> upstream/master
  }
  prop.Detach(value);
  return S_OK;
}

STDMETHODIMP CHandler::GetNumberOfItems(UInt32 *numItems)
{
  *numItems = 1;
  return S_OK;
}

static void DictSizeToString(UInt32 value, char *s)
{
  for (int i = 0; i <= 31; i++)
<<<<<<< HEAD
    if ((UInt32(1) << i) == value)
=======
    if (((UInt32)1 << i) == value)
>>>>>>> upstream/master
    {
      ::ConvertUInt32ToString(i, s);
      return;
    }
  char c = 'b';
<<<<<<< HEAD
  if ((value & ((1 << 20) - 1)) == 0)
  {
    value >>= 20;
    c = 'm';
  }
  else if ((value & ((1 << 10) - 1)) == 0)
  {
    value >>= 10;
    c = 'k';
  }
  ::ConvertUInt32ToString(value, s);
  int p = MyStringLen(s);
  s[p++] = c;
  s[p++] = '\0';
}

static void MyStrCat(char *d, const char *s)
{
  MyStringCopy(d + MyStringLen(d), s);
}

STDMETHODIMP CHandler::GetProperty(UInt32 /* index */, PROPID propID,  PROPVARIANT *value)
{
  NCOM::CPropVariant prop;
  switch(propID)
  {
    case kpidSize: if (_stream && _header.HasSize()) prop = _header.Size; break;
    case kpidPackSize: if (_packSizeDefined) prop = _packSize; break;
    case kpidMethod:
      if (_stream)
      {
        char s[64];
        s[0] = '\0';
        if (_header.FilterID != 0)
          MyStrCat(s, "BCJ ");
        MyStrCat(s, "LZMA:");
        DictSizeToString(_header.GetDicSize(), s + MyStringLen(s));
        prop = s;
=======
       if ((value & ((1 << 20) - 1)) == 0) { value >>= 20; c = 'm'; }
  else if ((value & ((1 << 10) - 1)) == 0) { value >>= 10; c = 'k'; }
  ::ConvertUInt32ToString(value, s);
  s += MyStringLen(s);
  *s++ = c;
  *s = 0;
}

STDMETHODIMP CHandler::GetProperty(UInt32 /* index */, PROPID propID, PROPVARIANT *value)
{
  NCOM::CPropVariant prop;
  switch (propID)
  {
    case kpidSize: if (_stream && _header.HasSize()) prop = _header.Size; break;
    case kpidPackSize: if (_packSize_Defined) prop = _packSize; break;
    case kpidMethod:
      if (_stream)
      {
        char sz[64];
        char *s = sz;
        if (_header.FilterID != 0)
          s = MyStpCpy(s, "BCJ ");
        s = MyStpCpy(s, "LZMA:");
        DictSizeToString(_header.GetDicSize(), s);
        prop = sz;
>>>>>>> upstream/master
      }
      break;
  }
  prop.Detach(value);
  return S_OK;
}

<<<<<<< HEAD
STDMETHODIMP CHandler::Open(IInStream *inStream, const UInt64 *, IArchiveOpenCallback *)
{
  RINOK(inStream->Seek(0, STREAM_SEEK_CUR, &_startPosition));
  
  const UInt32 kBufSize = 1 + 5 + 8 + 1;
=======
API_FUNC_static_IsArc IsArc_Lzma(const Byte *p, size_t size)
{
  const UInt32 kHeaderSize = 1 + 4 + 8;
  if (size < kHeaderSize)
    return k_IsArc_Res_NEED_MORE;
  if (p[0] >= 5 * 5 * 9)
    return k_IsArc_Res_NO;
  UInt64 unpackSize = GetUi64(p + 1 + 4);
  if (unpackSize != (UInt64)(Int64)-1)
  {
    if (size >= ((UInt64)1 << 56))
      return k_IsArc_Res_NO;
  }
  if (unpackSize != 0)
  {
    if (size < kHeaderSize + 2)
      return k_IsArc_Res_NEED_MORE;
    if (p[kHeaderSize] != 0)
      return k_IsArc_Res_NO;
    if (unpackSize != (UInt64)(Int64)-1)
    {
      if ((p[kHeaderSize + 1] & 0x80) != 0)
        return k_IsArc_Res_NO;
    }
  }
  if (!CheckDicSize(p + 1))
    // return k_IsArc_Res_YES_LOW_PROB;
    return k_IsArc_Res_NO;
  return k_IsArc_Res_YES;
}
}

API_FUNC_static_IsArc IsArc_Lzma86(const Byte *p, size_t size)
{
  if (size < 1)
    return k_IsArc_Res_NEED_MORE;
  Byte filterID = p[0];
  if (filterID != 0 && filterID != 1)
    return k_IsArc_Res_NO;
  return IsArc_Lzma(p + 1, size - 1);
}
}

STDMETHODIMP CHandler::Open(IInStream *inStream, const UInt64 *, IArchiveOpenCallback *)
{
  Close();
  
  const UInt32 kBufSize = 1 + 5 + 8 + 2;
>>>>>>> upstream/master
  Byte buf[kBufSize];
  
  RINOK(ReadStream_FALSE(inStream, buf, kBufSize));
  
  if (!_header.Parse(buf, _lzma86))
    return S_FALSE;
  const Byte *start = buf + GetHeaderSize();
<<<<<<< HEAD
  if (start[0] != 0)
    return S_FALSE;
  
  UInt64 endPos;
  RINOK(inStream->Seek(0, STREAM_SEEK_END, &endPos));
  _packSize = endPos - _startPosition;
  _packSizeDefined = true;
  if (_packSize >= 24 && _header.Size == 0 && _header.FilterID == 0 && _header.LzmaProps[0] == 0)
    return S_FALSE;
  _stream = inStream;
  _seqStream = inStream;
=======
  if (start[0] != 0 /* || (start[1] & 0x80) != 0 */ ) // empty stream with EOS is not 0x80
    return S_FALSE;
  
  RINOK(inStream->Seek(0, STREAM_SEEK_END, &_packSize));
  if (_packSize >= 24 && _header.Size == 0 && _header.FilterID == 0 && _header.LzmaProps[0] == 0)
    return S_FALSE;
  _isArc = true;
  _stream = inStream;
  _seqStream = inStream;
  _needSeekToStart = true;
>>>>>>> upstream/master
  return S_OK;
}

STDMETHODIMP CHandler::OpenSeq(ISequentialInStream *stream)
{
  Close();
<<<<<<< HEAD
=======
  _isArc = true;
>>>>>>> upstream/master
  _seqStream = stream;
  return S_OK;
}

STDMETHODIMP CHandler::Close()
{
<<<<<<< HEAD
  _packSizeDefined = false;
=======
  _isArc = false;
  _packSize_Defined = false;
  _unpackSize_Defined = false;
  _numStreams_Defined = false;

  _dataAfterEnd = false;
  _needMoreInput = false;
  _unsupported = false;
  _dataError = false;

  _packSize = 0;

  _needSeekToStart = false;

>>>>>>> upstream/master
  _stream.Release();
  _seqStream.Release();
   return S_OK;
}

<<<<<<< HEAD
=======
class CCompressProgressInfoImp:
  public ICompressProgressInfo,
  public CMyUnknownImp
{
  CMyComPtr<IArchiveOpenCallback> Callback;
public:
  UInt64 Offset;
 
  MY_UNKNOWN_IMP1(ICompressProgressInfo)
  STDMETHOD(SetRatioInfo)(const UInt64 *inSize, const UInt64 *outSize);
  void Init(IArchiveOpenCallback *callback) { Callback = callback; }
};

STDMETHODIMP CCompressProgressInfoImp::SetRatioInfo(const UInt64 *inSize, const UInt64 * /* outSize */)
{
  if (Callback)
  {
    UInt64 files = 0;
    UInt64 value = Offset + *inSize;
    return Callback->SetCompleted(&files, &value);
  }
  return S_OK;
}
>>>>>>> upstream/master

STDMETHODIMP CHandler::Extract(const UInt32 *indices, UInt32 numItems,
    Int32 testMode, IArchiveExtractCallback *extractCallback)
{
  COM_TRY_BEGIN
<<<<<<< HEAD
  if (numItems == 0)
    return S_OK;
  if (numItems != (UInt32)-1 && (numItems != 1 || indices[0] != 0))
    return E_INVALIDARG;

  if (_stream)
=======

  if (numItems == 0)
    return S_OK;
  if (numItems != (UInt32)(Int32)-1 && (numItems != 1 || indices[0] != 0))
    return E_INVALIDARG;

  if (_packSize_Defined)
>>>>>>> upstream/master
    extractCallback->SetTotal(_packSize);
    
  
  CMyComPtr<ISequentialOutStream> realOutStream;
  Int32 askMode = testMode ?
      NExtract::NAskMode::kTest :
      NExtract::NAskMode::kExtract;
  RINOK(extractCallback->GetStream(0, &realOutStream, askMode));
  if (!testMode && !realOutStream)
    return S_OK;
  
  extractCallback->PrepareOperation(askMode);

  CDummyOutStream *outStreamSpec = new CDummyOutStream;
  CMyComPtr<ISequentialOutStream> outStream(outStreamSpec);
  outStreamSpec->SetStream(realOutStream);
  outStreamSpec->Init();
  realOutStream.Release();

  CLocalProgress *lps = new CLocalProgress;
  CMyComPtr<ICompressProgressInfo> progress = lps;
  lps->Init(extractCallback, true);

<<<<<<< HEAD
  if (_stream)
  {
    RINOK(_stream->Seek(_startPosition, STREAM_SEEK_SET, NULL));
  }

  CDecoder decoder;
  HRESULT result = decoder.Create(
      EXTERNAL_CODECS_VARS
      _lzma86, _seqStream);
  RINOK(result);
 
  Int32 opRes = NExtract::NOperationResult::kOK;
  bool firstItem = true;

  for (;;)
  {
    lps->OutSize = outStreamSpec->GetSize();
    lps->InSize = _packSize = decoder.GetInputProcessedSize();
    _packSizeDefined = true;
    RINOK(lps->SetCur());

    CHeader st;

=======
  if (_needSeekToStart)
  {
    if (!_stream)
      return E_FAIL;
    RINOK(_stream->Seek(0, STREAM_SEEK_SET, NULL));
  }
  else
    _needSeekToStart = true;

  CDecoder decoder;
  HRESULT result = decoder.Create(_lzma86, _seqStream);
  RINOK(result);
 
  bool firstItem = true;

  UInt64 packSize = 0;
  UInt64 unpackSize = 0;
  UInt64 numStreams = 0;

  bool dataAfterEnd = false;
  
  for (;;)
  {
    lps->InSize = packSize;
    lps->OutSize = unpackSize;
    RINOK(lps->SetCur());

>>>>>>> upstream/master
    const UInt32 kBufSize = 1 + 5 + 8;
    Byte buf[kBufSize];
    const UInt32 headerSize = GetHeaderSize();
    UInt32 processed;
    RINOK(decoder.ReadInput(buf, headerSize, &processed));
    if (processed != headerSize)
<<<<<<< HEAD
      break;
  
    if (!st.Parse(buf, _lzma86))
      break;
    firstItem = false;

    result = decoder.Code(st, outStream, progress);
    if (result == E_NOTIMPL)
    {
      opRes = NExtract::NOperationResult::kUnSupportedMethod;
      break;
    }
    if (result == S_FALSE)
    {
      opRes = NExtract::NOperationResult::kDataError;
      break;
    }
    RINOK(result);
  }
  if (firstItem)
    return E_FAIL;
  outStream.Release();
  return extractCallback->SetOperationResult(opRes);
  COM_TRY_END
}

IMPL_ISetCompressCodecsInfo

static IInArchive *CreateArc() { return new CHandler(false); }
static IInArchive *CreateArc86() { return new CHandler(true); }

namespace NLzmaAr {
  
static CArcInfo g_ArcInfo =
  { L"lzma", L"lzma", 0, 0xA, { 0 }, 0, true, CreateArc, NULL };
REGISTER_ARC(Lzma)

=======
    {
      if (processed != 0)
        dataAfterEnd = true;
      break;
    }
  
    CHeader st;
    if (!st.Parse(buf, _lzma86))
    {
      dataAfterEnd = true;
      break;
    }
    numStreams++;
    firstItem = false;

    result = decoder.Code(st, outStream, progress);

    packSize = decoder.GetInputProcessedSize();
    unpackSize = outStreamSpec->GetSize();
    
    if (result == E_NOTIMPL)
    {
      _unsupported = true;
      result = S_FALSE;
      break;
    }
    if (result == S_FALSE)
      break;
    RINOK(result);
  }

  if (firstItem)
  {
    _isArc = false;
    result = S_FALSE;
  }
  else if (result == S_OK || result == S_FALSE)
  {
    if (dataAfterEnd)
      _dataAfterEnd = true;
    else if (decoder._lzmaDecoderSpec->NeedMoreInput)
      _needMoreInput = true;

    _packSize = packSize;
    _unpackSize = unpackSize;
    _numStreams = numStreams;
  
    _packSize_Defined = true;
    _unpackSize_Defined = true;
    _numStreams_Defined = true;
  }
  
  Int32 opResult = NExtract::NOperationResult::kOK;

  if (!_isArc)
    opResult = NExtract::NOperationResult::kIsNotArc;
  else if (_needMoreInput)
    opResult = NExtract::NOperationResult::kUnexpectedEnd;
  else if (_unsupported)
    opResult = NExtract::NOperationResult::kUnsupportedMethod;
  else if (_dataAfterEnd)
    opResult = NExtract::NOperationResult::kDataAfterEnd;
  else if (result == S_FALSE)
    opResult = NExtract::NOperationResult::kDataError;
  else if (result == S_OK)
    opResult = NExtract::NOperationResult::kOK;
  else
    return result;

  outStream.Release();
  return extractCallback->SetOperationResult(opResult);

  COM_TRY_END
}

namespace NLzmaAr {

// 2, { 0x5D, 0x00 },

REGISTER_ARC_I_CLS_NO_SIG(
  CHandler(false),
  "lzma", "lzma", 0, 0xA,
  0,
  NArcInfoFlags::kStartOpen |
  NArcInfoFlags::kKeepName,
  IsArc_Lzma)
 
>>>>>>> upstream/master
}

namespace NLzma86Ar {

<<<<<<< HEAD
static CArcInfo g_ArcInfo =
  { L"lzma86", L"lzma86", 0, 0xB, { 0 }, 0, true, CreateArc86, NULL };
REGISTER_ARC(Lzma86)

=======
REGISTER_ARC_I_CLS_NO_SIG(
  CHandler(true),
  "lzma86", "lzma86", 0, 0xB,
  0,
  NArcInfoFlags::kKeepName,
  IsArc_Lzma86)
 
>>>>>>> upstream/master
}

}}
