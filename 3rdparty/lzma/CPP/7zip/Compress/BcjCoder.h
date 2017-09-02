// BcjCoder.h

#ifndef __COMPRESS_BCJ_CODER_H
#define __COMPRESS_BCJ_CODER_H

#include "../../../C/Bra.h"

<<<<<<< HEAD
#include "BranchCoder.h"

struct CBranch86
{
  UInt32 _prevMask;
  void x86Init() { x86_Convert_Init(_prevMask); }
};

MyClassB(BCJ_x86, 0x01, 3, CBranch86 ,
    virtual void SubInit() { x86Init(); })
=======
#include "../../Common/MyCom.h"

#include "../ICoder.h"

namespace NCompress {
namespace NBcj {

class CCoder:
  public ICompressFilter,
  public CMyUnknownImp
{
  UInt32 _bufferPos;
  UInt32 _prevMask;
  int _encode;
public:
  MY_UNKNOWN_IMP1(ICompressFilter);
  INTERFACE_ICompressFilter(;)

  CCoder(int encode): _bufferPos(0), _encode(encode) { x86_Convert_Init(_prevMask); }
};

}}
>>>>>>> upstream/master

#endif
