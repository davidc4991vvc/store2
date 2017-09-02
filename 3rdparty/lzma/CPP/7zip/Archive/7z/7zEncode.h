// 7zEncode.h

#ifndef __7Z_ENCODE_H
#define __7Z_ENCODE_H

<<<<<<< HEAD
// #include "../../Common/StreamObjects.h"

#include "7zCompressionMode.h"

#include "../Common/CoderMixer2.h"
#include "../Common/CoderMixer2MT.h"
#ifdef _ST_MODE
#include "../Common/CoderMixer2ST.h"
#endif
#include "7zItem.h"

#include "../../Common/CreateCoder.h"
=======
#include "7zCompressionMode.h"

#include "../Common/CoderMixer2.h"

#include "7zItem.h"
>>>>>>> upstream/master

namespace NArchive {
namespace N7z {

<<<<<<< HEAD
class CEncoder
{
  NCoderMixer::CCoderMixer2MT *_mixerCoderSpec;
  CMyComPtr<ICompressCoder2> _mixerCoder;

  CObjectVector<CCoderInfo> _codersInfo;

  CCompressionMethodMode _options;
  NCoderMixer::CBindInfo _bindInfo;
  NCoderMixer::CBindInfo _decompressBindInfo;
  NCoderMixer::CBindReverseConverter *_bindReverseConverter;
  CRecordVector<CMethodId> _decompressionMethods;

=======
class CMtEncMultiProgress:
  public ICompressProgressInfo,
  public CMyUnknownImp
{
  CMyComPtr<ICompressProgressInfo> _progress;
  #ifndef _7ZIP_ST
  NWindows::NSynchronization::CCriticalSection CriticalSection;
  #endif

public:
  UInt64 OutSize;

  CMtEncMultiProgress(): OutSize(0) {}

  void Init(ICompressProgressInfo *progress);

  void AddOutSize(UInt64 addOutSize)
  {
    #ifndef _7ZIP_ST
    NWindows::NSynchronization::CCriticalSectionLock lock(CriticalSection);
    #endif
    OutSize += addOutSize;
  }

  MY_UNKNOWN_IMP1(ICompressProgressInfo)

  STDMETHOD(SetRatioInfo)(const UInt64 *inSize, const UInt64 *outSize);
};

class CEncoder
{
  #ifdef USE_MIXER_ST
    NCoderMixer2::CMixerST *_mixerST;
  #endif
  #ifdef USE_MIXER_MT
    NCoderMixer2::CMixerMT *_mixerMT;
  #endif
  
  NCoderMixer2::CMixer *_mixer;
  CMyComPtr<IUnknown> _mixerRef;

  CCompressionMethodMode _options;
  NCoderMixer2::CBindInfo _bindInfo;
  CRecordVector<CMethodId> _decompressionMethods;

  CRecordVector<UInt32> _SrcIn_to_DestOut;
  CRecordVector<UInt32> _SrcOut_to_DestIn;
  // CRecordVector<UInt32> _DestIn_to_SrcOut;
  CRecordVector<UInt32> _DestOut_to_SrcIn;

  void InitBindConv();
  void SetFolder(CFolder &folder);

>>>>>>> upstream/master
  HRESULT CreateMixerCoder(DECL_EXTERNAL_CODECS_LOC_VARS
      const UInt64 *inSizeForReduce);

  bool _constructed;
public:
<<<<<<< HEAD
=======

>>>>>>> upstream/master
  CEncoder(const CCompressionMethodMode &options);
  ~CEncoder();
  HRESULT EncoderConstr();
  HRESULT Encode(
      DECL_EXTERNAL_CODECS_LOC_VARS
      ISequentialInStream *inStream,
<<<<<<< HEAD
      const UInt64 *inStreamSize, const UInt64 *inSizeForReduce,
      CFolder &folderItem,
=======
      // const UInt64 *inStreamSize,
      const UInt64 *inSizeForReduce,
      CFolder &folderItem,
      CRecordVector<UInt64> &coderUnpackSizes,
      UInt64 &unpackSize,
>>>>>>> upstream/master
      ISequentialOutStream *outStream,
      CRecordVector<UInt64> &packSizes,
      ICompressProgressInfo *compressProgress);
};

}}

#endif
