// CWrappers.h

#ifndef __C_WRAPPERS_H
#define __C_WRAPPERS_H

#include "../ICoder.h"
#include "../../Common/MyCom.h"

struct CCompressProgressWrap
{
  ICompressProgress p;
  ICompressProgressInfo *Progress;
  HRESULT Res;
<<<<<<< HEAD
  CCompressProgressWrap(ICompressProgressInfo *progress);
=======
  
  CCompressProgressWrap(ICompressProgressInfo *progress) throw();
>>>>>>> upstream/master
};

struct CSeqInStreamWrap
{
  ISeqInStream p;
  ISequentialInStream *Stream;
  HRESULT Res;
<<<<<<< HEAD
  CSeqInStreamWrap(ISequentialInStream *stream);
=======
  UInt64 Processed;
  
  CSeqInStreamWrap(ISequentialInStream *stream) throw();
>>>>>>> upstream/master
};

struct CSeekInStreamWrap
{
  ISeekInStream p;
  IInStream *Stream;
  HRESULT Res;
<<<<<<< HEAD
  CSeekInStreamWrap(IInStream *stream);
=======
  
  CSeekInStreamWrap(IInStream *stream) throw();
>>>>>>> upstream/master
};

struct CSeqOutStreamWrap
{
  ISeqOutStream p;
  ISequentialOutStream *Stream;
  HRESULT Res;
  UInt64 Processed;
<<<<<<< HEAD
  CSeqOutStreamWrap(ISequentialOutStream *stream);
};

HRESULT SResToHRESULT(SRes res);
=======
  
  CSeqOutStreamWrap(ISequentialOutStream *stream) throw();
};

HRESULT SResToHRESULT(SRes res) throw();
>>>>>>> upstream/master

struct CByteInBufWrap
{
  IByteIn p;
  const Byte *Cur;
  const Byte *Lim;
  Byte *Buf;
  UInt32 Size;
  ISequentialInStream *Stream;
  UInt64 Processed;
  bool Extra;
  HRESULT Res;
  
  CByteInBufWrap();
<<<<<<< HEAD
  ~CByteInBufWrap() { Free();  }
  void Free();
  bool Alloc(UInt32 size);
=======
  ~CByteInBufWrap() { Free(); }
  void Free() throw();
  bool Alloc(UInt32 size) throw();
>>>>>>> upstream/master
  void Init()
  {
    Lim = Cur = Buf;
    Processed = 0;
    Extra = false;
    Res = S_OK;
  }
  UInt64 GetProcessed() const { return Processed + (Cur - Buf); }
<<<<<<< HEAD
  Byte ReadByteFromNewBlock();
=======
  Byte ReadByteFromNewBlock() throw();
>>>>>>> upstream/master
  Byte ReadByte()
  {
    if (Cur != Lim)
      return *Cur++;
    return ReadByteFromNewBlock();
  }
};

struct CByteOutBufWrap
{
  IByteOut p;
  Byte *Cur;
  const Byte *Lim;
  Byte *Buf;
  size_t Size;
  ISequentialOutStream *Stream;
  UInt64 Processed;
  HRESULT Res;
  
<<<<<<< HEAD
  CByteOutBufWrap();
  ~CByteOutBufWrap() { Free();  }
  void Free();
  bool Alloc(size_t size);
=======
  CByteOutBufWrap() throw();
  ~CByteOutBufWrap() { Free(); }
  void Free() throw();
  bool Alloc(size_t size) throw();
>>>>>>> upstream/master
  void Init()
  {
    Cur = Buf;
    Lim = Buf + Size;
    Processed = 0;
    Res = S_OK;
  }
  UInt64 GetProcessed() const { return Processed + (Cur - Buf); }
<<<<<<< HEAD
  HRESULT Flush();
=======
  HRESULT Flush() throw();
>>>>>>> upstream/master
  void WriteByte(Byte b)
  {
    *Cur++ = b;
    if (Cur == Lim)
      Flush();
  }
};

#endif
