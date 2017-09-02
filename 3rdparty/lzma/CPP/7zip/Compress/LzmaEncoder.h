// LzmaEncoder.h

#ifndef __LZMA_ENCODER_H
#define __LZMA_ENCODER_H

#include "../../../C/LzmaEnc.h"

#include "../../Common/MyCom.h"

#include "../ICoder.h"

namespace NCompress {
namespace NLzma {

class CEncoder:
  public ICompressCoder,
  public ICompressSetCoderProperties,
  public ICompressWriteCoderProperties,
  public CMyUnknownImp
{
  CLzmaEncHandle _encoder;
<<<<<<< HEAD
public:
  MY_UNKNOWN_IMP2(ICompressSetCoderProperties, ICompressWriteCoderProperties)
=======
  UInt64 _inputProcessed;
public:
  MY_UNKNOWN_IMP3(ICompressCoder, ICompressSetCoderProperties, ICompressWriteCoderProperties)
>>>>>>> upstream/master
    
  STDMETHOD(Code)(ISequentialInStream *inStream, ISequentialOutStream *outStream,
      const UInt64 *inSize, const UInt64 *outSize, ICompressProgressInfo *progress);
  STDMETHOD(SetCoderProperties)(const PROPID *propIDs, const PROPVARIANT *props, UInt32 numProps);
  STDMETHOD(WriteCoderProperties)(ISequentialOutStream *outStream);

  CEncoder();
  virtual ~CEncoder();
<<<<<<< HEAD
=======
  UInt64 GetInputProcessedSize() const { return _inputProcessed; }
>>>>>>> upstream/master
};

}}

#endif
