// SplitHandler.cpp

#include "StdAfx.h"

<<<<<<< HEAD
#include "Common/ComTry.h"
#include "Common/MyString.h"

#include "Windows/PropVariant.h"
=======
#include "../../Common/ComTry.h"
#include "../../Common/MyString.h"

#include "../../Windows/PropVariant.h"
>>>>>>> upstream/master

#include "../Common/ProgressUtils.h"
#include "../Common/RegisterArc.h"

#include "../Compress/CopyCoder.h"

#include "Common/MultiStream.h"

using namespace NWindows;

namespace NArchive {
namespace NSplit {

<<<<<<< HEAD
STATPROPSTG kProps[] =
{
  { NULL, kpidPath, VT_BSTR},
  { NULL, kpidSize, VT_UI8}
};

STATPROPSTG kArcProps[] =
{
  { NULL, kpidNumVolumes, VT_UI4}
=======
static const Byte kProps[] =
{
  kpidPath,
  kpidSize
};

static const Byte kArcProps[] =
{
  kpidNumVolumes,
  kpidTotalPhySize
>>>>>>> upstream/master
};

class CHandler:
  public IInArchive,
  public IInArchiveGetStream,
  public CMyUnknownImp
{
<<<<<<< HEAD
  UString _subName;
  CObjectVector<CMyComPtr<IInStream> > _streams;
  CRecordVector<UInt64> _sizes;
  UInt64 _totalSize;
=======
  CObjectVector<CMyComPtr<IInStream> > _streams;
  CRecordVector<UInt64> _sizes;
  UString _subName;
  UInt64 _totalSize;

  HRESULT Open2(IInStream *stream, IArchiveOpenCallback *callback);
>>>>>>> upstream/master
public:
  MY_UNKNOWN_IMP2(IInArchive, IInArchiveGetStream)
  INTERFACE_IInArchive(;)
  STDMETHOD(GetStream)(UInt32 index, ISequentialInStream **stream);
};

IMP_IInArchive_Props
IMP_IInArchive_ArcProps

STDMETHODIMP CHandler::GetArchiveProperty(PROPID propID, PROPVARIANT *value)
{
  NCOM::CPropVariant prop;
<<<<<<< HEAD
  switch(propID)
  {
    case kpidMainSubfile: prop = (UInt32)0; break;
=======
  switch (propID)
  {
    case kpidMainSubfile: prop = (UInt32)0; break;
    case kpidPhySize: if (!_sizes.IsEmpty()) prop = _sizes[0]; break;
    case kpidTotalPhySize: prop = _totalSize; break;
>>>>>>> upstream/master
    case kpidNumVolumes: prop = (UInt32)_streams.Size(); break;
  }
  prop.Detach(value);
  return S_OK;
}

struct CSeqName
{
  UString _unchangedPart;
  UString _changedPart;
  bool _splitStyle;
  
<<<<<<< HEAD
  UString GetNextName()
  {
    UString newName;
    if (_splitStyle)
    {
      int i;
      int numLetters = _changedPart.Length();
      for (i = numLetters - 1; i >= 0; i--)
      {
        wchar_t c = _changedPart[i];
        if (c == 'z')
        {
          c = 'a';
          newName = c + newName;
          continue;
        }
        else if (c == 'Z')
        {
          c = 'A';
          newName = c + newName;
          continue;
        }
        c++;
        if ((c == 'z' || c == 'Z') && i == 0)
        {
          _unchangedPart += c;
          wchar_t newChar = (c == 'z') ? L'a' : L'A';
          newName.Empty();
          numLetters++;
          for (int k = 0; k < numLetters; k++)
            newName += newChar;
          break;
        }
        newName = c + newName;
        i--;
        for (; i >= 0; i--)
          newName = _changedPart[i] + newName;
        break;
      }
    }
    else
    {
      int i;
      int numLetters = _changedPart.Length();
      for (i = numLetters - 1; i >= 0; i--)
      {
        wchar_t c = _changedPart[i];
        if (c == L'9')
        {
          c = L'0';
          newName = c + newName;
          if (i == 0)
            newName = UString(L'1') + newName;
          continue;
        }
        c++;
        newName = c + newName;
        i--;
        for (; i >= 0; i--)
          newName = _changedPart[i] + newName;
        break;
      }
    }
    _changedPart = newName;
    return _unchangedPart + _changedPart;
  }
};

STDMETHODIMP CHandler::Open(IInStream *stream,
    const UInt64 * /* maxCheckStartPosition */,
    IArchiveOpenCallback *openArchiveCallback)
{
  COM_TRY_BEGIN
  Close();
  if (openArchiveCallback == 0)
    return S_FALSE;
  // try
  {
    CMyComPtr<IArchiveOpenVolumeCallback> openVolumeCallback;
    CMyComPtr<IArchiveOpenCallback> openArchiveCallbackWrap = openArchiveCallback;
    if (openArchiveCallbackWrap.QueryInterface(IID_IArchiveOpenVolumeCallback,
        &openVolumeCallback) != S_OK)
      return S_FALSE;
    
    UString name;
    {
      NCOM::CPropVariant prop;
      RINOK(openVolumeCallback->GetProperty(kpidName, &prop));
      if (prop.vt != VT_BSTR)
        return S_FALSE;
      name = prop.bstrVal;
    }
    
    int dotPos = name.ReverseFind('.');
    UString prefix, ext;
    if (dotPos >= 0)
    {
      prefix = name.Left(dotPos + 1);
      ext = name.Mid(dotPos + 1);
    }
    else
      ext = name;
    UString extBig = ext;
    extBig.MakeUpper();

    CSeqName seqName;

    int numLetters = 2;
    bool splitStyle = false;
    if (extBig.Right(2) == L"AA")
    {
      splitStyle = true;
      while (numLetters < extBig.Length())
      {
        if (extBig[extBig.Length() - numLetters - 1] != 'A')
          break;
        numLetters++;
      }
    }
    else if (ext.Right(2) == L"01")
    {
      while (numLetters < extBig.Length())
      {
        if (extBig[extBig.Length() - numLetters - 1] != '0')
          break;
        numLetters++;
      }
      if (numLetters != ext.Length())
        return S_FALSE;
    }
    else
      return S_FALSE;

    _streams.Add(stream);

    seqName._unchangedPart = prefix + ext.Left(extBig.Length() - numLetters);
    seqName._changedPart = ext.Right(numLetters);
    seqName._splitStyle = splitStyle;

    if (prefix.Length() < 1)
      _subName = L"file";
    else
      _subName = prefix.Left(prefix.Length() - 1);

    _totalSize = 0;
    UInt64 size;
    {
      NCOM::CPropVariant prop;
      RINOK(openVolumeCallback->GetProperty(kpidSize, &prop));
      if (prop.vt != VT_UI8)
        return E_INVALIDARG;
      size = prop.uhVal.QuadPart;
    }
    _totalSize += size;
    _sizes.Add(size);
    
    if (openArchiveCallback != NULL)
    {
      UInt64 numFiles = _streams.Size();
      RINOK(openArchiveCallback->SetCompleted(&numFiles, NULL));
    }

    for (;;)
    {
      UString fullName = seqName.GetNextName();
      CMyComPtr<IInStream> nextStream;
      HRESULT result = openVolumeCallback->GetStream(fullName, &nextStream);
      if (result == S_FALSE)
        break;
      if (result != S_OK)
        return result;
      if (!stream)
        break;
      {
        NCOM::CPropVariant prop;
        RINOK(openVolumeCallback->GetProperty(kpidSize, &prop));
        if (prop.vt != VT_UI8)
          return E_INVALIDARG;
        size = prop.uhVal.QuadPart;
      }
      _totalSize += size;
      _sizes.Add(size);
      _streams.Add(nextStream);
      if (openArchiveCallback != NULL)
      {
        UInt64 numFiles = _streams.Size();
        RINOK(openArchiveCallback->SetCompleted(&numFiles, NULL));
      }
    }
  }
  /*
  catch(...)
  {
    return S_FALSE;
  }
  */
  return S_OK;
=======
  bool GetNextName(UString &s)
  {
    {
      unsigned i = _changedPart.Len();
      for (;;)
      {
        wchar_t c = _changedPart[--i];
        
        if (_splitStyle)
        {
          if (c == 'z')
          {
            _changedPart.ReplaceOneCharAtPos(i, L'a');
            if (i == 0)
              return false;
            continue;
          }
          else if (c == 'Z')
          {
            _changedPart.ReplaceOneCharAtPos(i, L'A');
            if (i == 0)
              return false;
            continue;
          }
        }
        else
        {
          if (c == '9')
          {
            _changedPart.ReplaceOneCharAtPos(i, L'0');
            if (i == 0)
            {
              _changedPart.InsertAtFront(L'1');
              break;
            }
            continue;
          }
        }

        c++;
        _changedPart.ReplaceOneCharAtPos(i, c);
        break;
      }
    }
    
    s = _unchangedPart + _changedPart;
    return true;
  }
};

HRESULT CHandler::Open2(IInStream *stream, IArchiveOpenCallback *callback)
{
  Close();
  if (!callback)
    return S_FALSE;

  CMyComPtr<IArchiveOpenVolumeCallback> volumeCallback;
  callback->QueryInterface(IID_IArchiveOpenVolumeCallback, (void **)&volumeCallback);
  if (!volumeCallback)
    return S_FALSE;
  
  UString name;
  {
    NCOM::CPropVariant prop;
    RINOK(volumeCallback->GetProperty(kpidName, &prop));
    if (prop.vt != VT_BSTR)
      return S_FALSE;
    name = prop.bstrVal;
  }
  
  int dotPos = name.ReverseFind_Dot();
  const UString prefix = name.Left(dotPos + 1);
  const UString ext = name.Ptr(dotPos + 1);
  UString ext2 = ext;
  ext2.MakeLower_Ascii();
  
  CSeqName seqName;
  
  unsigned numLetters = 2;
  bool splitStyle = false;
  
  if (ext2.Len() >= 2 && StringsAreEqual_Ascii(ext2.RightPtr(2), "aa"))
  {
    splitStyle = true;
    while (numLetters < ext2.Len())
    {
      if (ext2[ext2.Len() - numLetters - 1] != 'a')
        break;
      numLetters++;
    }
  }
  else if (ext.Len() >= 2 && StringsAreEqual_Ascii(ext2.RightPtr(2), "01"))
  {
    while (numLetters < ext2.Len())
    {
      if (ext2[ext2.Len() - numLetters - 1] != '0')
        break;
      numLetters++;
    }
    if (numLetters != ext.Len())
      return S_FALSE;
  }
  else
    return S_FALSE;
  
  seqName._unchangedPart = prefix + ext.Left(ext2.Len() - numLetters);
  seqName._changedPart = ext.RightPtr(numLetters);
  seqName._splitStyle = splitStyle;
  
  if (prefix.Len() < 1)
    _subName.SetFromAscii("file");
  else
    _subName.SetFrom(prefix, prefix.Len() - 1);
  
  UInt64 size;
  {
    /*
    NCOM::CPropVariant prop;
    RINOK(volumeCallback->GetProperty(kpidSize, &prop));
    if (prop.vt != VT_UI8)
      return E_INVALIDARG;
    size = prop.uhVal.QuadPart;
    */
    RINOK(stream->Seek(0, STREAM_SEEK_END, &size));
    RINOK(stream->Seek(0, STREAM_SEEK_SET, NULL));
  }
  
  _totalSize += size;
  _sizes.Add(size);
  _streams.Add(stream);
  
  {
    const UInt64 numFiles = _streams.Size();
    RINOK(callback->SetCompleted(&numFiles, NULL));
  }
  
  for (;;)
  {
    UString fullName;
    if (!seqName.GetNextName(fullName))
      break;
    CMyComPtr<IInStream> nextStream;
    HRESULT result = volumeCallback->GetStream(fullName, &nextStream);
    if (result == S_FALSE)
      break;
    if (result != S_OK)
      return result;
    if (!nextStream)
      break;
    {
      /*
      NCOM::CPropVariant prop;
      RINOK(volumeCallback->GetProperty(kpidSize, &prop));
      if (prop.vt != VT_UI8)
        return E_INVALIDARG;
      size = prop.uhVal.QuadPart;
      */
      RINOK(nextStream->Seek(0, STREAM_SEEK_END, &size));
      RINOK(nextStream->Seek(0, STREAM_SEEK_SET, NULL));
    }
    _totalSize += size;
    _sizes.Add(size);
    _streams.Add(nextStream);
    {
      const UInt64 numFiles = _streams.Size();
      RINOK(callback->SetCompleted(&numFiles, NULL));
    }
  }

  if (_streams.Size() == 1)
  {
    if (splitStyle)
      return S_FALSE;
  }
  return S_OK;
}

STDMETHODIMP CHandler::Open(IInStream *stream, const UInt64 *, IArchiveOpenCallback *callback)
{
  COM_TRY_BEGIN
  HRESULT res = Open2(stream, callback);
  if (res != S_OK)
    Close();
  return res;
>>>>>>> upstream/master
  COM_TRY_END
}

STDMETHODIMP CHandler::Close()
{
<<<<<<< HEAD
  _sizes.Clear();
  _streams.Clear();
=======
  _totalSize = 0;
  _subName.Empty();
  _streams.Clear();
  _sizes.Clear();
>>>>>>> upstream/master
  return S_OK;
}

STDMETHODIMP CHandler::GetNumberOfItems(UInt32 *numItems)
{
  *numItems = _streams.IsEmpty() ? 0 : 1;
  return S_OK;
}

STDMETHODIMP CHandler::GetProperty(UInt32 /* index */, PROPID propID, PROPVARIANT *value)
{
<<<<<<< HEAD
  NWindows::NCOM::CPropVariant prop;
  switch(propID)
=======
  NCOM::CPropVariant prop;
  switch (propID)
>>>>>>> upstream/master
  {
    case kpidPath: prop = _subName; break;
    case kpidSize:
    case kpidPackSize:
      prop = _totalSize;
      break;
  }
  prop.Detach(value);
  return S_OK;
}

STDMETHODIMP CHandler::Extract(const UInt32 *indices, UInt32 numItems,
    Int32 testMode, IArchiveExtractCallback *extractCallback)
{
  COM_TRY_BEGIN
  if (numItems == 0)
    return S_OK;
<<<<<<< HEAD
  if (numItems != (UInt32)-1 && (numItems != 1 || indices[0] != 0))
=======
  if (numItems != (UInt32)(Int32)-1 && (numItems != 1 || indices[0] != 0))
>>>>>>> upstream/master
    return E_INVALIDARG;

  UInt64 currentTotalSize = 0;
  RINOK(extractCallback->SetTotal(_totalSize));
  CMyComPtr<ISequentialOutStream> outStream;
  Int32 askMode = testMode ?
      NExtract::NAskMode::kTest :
      NExtract::NAskMode::kExtract;
  RINOK(extractCallback->GetStream(0, &outStream, askMode));
  if (!testMode && !outStream)
    return S_OK;
  RINOK(extractCallback->PrepareOperation(askMode));
  
  NCompress::CCopyCoder *copyCoderSpec = new NCompress::CCopyCoder;
  CMyComPtr<ICompressCoder> copyCoder = copyCoderSpec;

  CLocalProgress *lps = new CLocalProgress;
  CMyComPtr<ICompressProgressInfo> progress = lps;
  lps->Init(extractCallback, false);

<<<<<<< HEAD
  for (int i = 0; i < _streams.Size(); i++)
=======
  FOR_VECTOR (i, _streams)
>>>>>>> upstream/master
  {
    lps->InSize = lps->OutSize = currentTotalSize;
    RINOK(lps->SetCur());
    IInStream *inStream = _streams[i];
    RINOK(inStream->Seek(0, STREAM_SEEK_SET, NULL));
    RINOK(copyCoder->Code(inStream, outStream, NULL, NULL, progress));
    currentTotalSize += copyCoderSpec->TotalSize;
  }
  outStream.Release();
  return extractCallback->SetOperationResult(NExtract::NOperationResult::kOK);
  COM_TRY_END
}

STDMETHODIMP CHandler::GetStream(UInt32 index, ISequentialInStream **stream)
{
  COM_TRY_BEGIN
  if (index != 0)
    return E_INVALIDARG;
  *stream = 0;
  CMultiStream *streamSpec = new CMultiStream;
  CMyComPtr<ISequentialInStream> streamTemp = streamSpec;
<<<<<<< HEAD
  for (int i = 0; i < _streams.Size(); i++)
=======
  FOR_VECTOR (i, _streams)
>>>>>>> upstream/master
  {
    CMultiStream::CSubStreamInfo subStreamInfo;
    subStreamInfo.Stream = _streams[i];
    subStreamInfo.Size = _sizes[i];
    streamSpec->Streams.Add(subStreamInfo);
  }
  streamSpec->Init();
  *stream = streamTemp.Detach();
  return S_OK;
  COM_TRY_END
}

<<<<<<< HEAD
static IInArchive *CreateArc() { return new CHandler; }

static CArcInfo g_ArcInfo =
{ L"Split", L"001", 0, 0xEA, { 0 }, 0, false, CreateArc, 0 };

REGISTER_ARC(Split)
=======
REGISTER_ARC_I_NO_SIG(
  "Split", "001", 0, 0xEA,
  0,
  0,
  NULL)
>>>>>>> upstream/master

}}
