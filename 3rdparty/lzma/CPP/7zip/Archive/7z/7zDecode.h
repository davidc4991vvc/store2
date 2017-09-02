// 7zDecode.h

#ifndef __7Z_DECODE_H
#define __7Z_DECODE_H

<<<<<<< HEAD
#include "../../IStream.h"
#include "../../IPassword.h"

#include "../Common/CoderMixer2.h"
#include "../Common/CoderMixer2MT.h"
#ifdef _ST_MODE
#include "../Common/CoderMixer2ST.h"
#endif

#include "../../Common/CreateCoder.h"

#include "7zItem.h"
=======
#include "../Common/CoderMixer2.h"

#include "7zIn.h"
>>>>>>> upstream/master

namespace NArchive {
namespace N7z {

<<<<<<< HEAD
struct CBindInfoEx: public NCoderMixer::CBindInfo
{
  CRecordVector<CMethodId> CoderMethodIDs;
=======
struct CBindInfoEx: public NCoderMixer2::CBindInfo
{
  CRecordVector<CMethodId> CoderMethodIDs;

>>>>>>> upstream/master
  void Clear()
  {
    CBindInfo::Clear();
    CoderMethodIDs.Clear();
  }
};

class CDecoder
{
<<<<<<< HEAD
  bool _bindInfoExPrevIsDefined;
  CBindInfoEx _bindInfoExPrev;
  
  bool _multiThread;
  #ifdef _ST_MODE
  NCoderMixer::CCoderMixer2ST *_mixerCoderSTSpec;
  #endif
  NCoderMixer::CCoderMixer2MT *_mixerCoderMTSpec;
  NCoderMixer::CCoderMixer2 *_mixerCoderCommon;
  
  CMyComPtr<ICompressCoder2> _mixerCoder;
  CObjectVector<CMyComPtr<IUnknown> > _decoders;
  // CObjectVector<CMyComPtr<ICompressCoder2> > _decoders2;
public:
  CDecoder(bool multiThread);
=======
  bool _bindInfoPrev_Defined;
  CBindInfoEx _bindInfoPrev;
  
  bool _useMixerMT;
  
  #ifdef USE_MIXER_ST
    NCoderMixer2::CMixerST *_mixerST;
  #endif
  
  #ifdef USE_MIXER_MT
    NCoderMixer2::CMixerMT *_mixerMT;
  #endif
  
  NCoderMixer2::CMixer *_mixer;
  CMyComPtr<IUnknown> _mixerRef;

public:

  CDecoder(bool useMixerMT);
  
>>>>>>> upstream/master
  HRESULT Decode(
      DECL_EXTERNAL_CODECS_LOC_VARS
      IInStream *inStream,
      UInt64 startPos,
<<<<<<< HEAD
      const UInt64 *packSizes,
      const CFolder &folder,
      ISequentialOutStream *outStream,
      ICompressProgressInfo *compressProgress
      #ifndef _NO_CRYPTO
      , ICryptoGetTextPassword *getTextPasswordSpec, bool &passwordIsDefined
      #endif
=======
      const CFolders &folders, unsigned folderIndex,
      const UInt64 *unpackSize // if (!unpackSize), then full folder is required
                               // if (unpackSize), then only *unpackSize bytes from folder are required

      , ISequentialOutStream *outStream
      , ICompressProgressInfo *compressProgress
      , ISequentialInStream **inStreamMainRes
      
      _7Z_DECODER_CRYPRO_VARS_DECL
      
>>>>>>> upstream/master
      #if !defined(_7ZIP_ST) && !defined(_SFX)
      , bool mtMode, UInt32 numThreads
      #endif
      );
};

}}

#endif
