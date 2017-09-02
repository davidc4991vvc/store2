// BranchMisc.h

#ifndef __COMPRESS_BRANCH_MISC_H
#define __COMPRESS_BRANCH_MISC_H

<<<<<<< HEAD
#include "BranchCoder.h"

MyClassA(BC_ARM,   0x05, 1)
MyClassA(BC_ARMT,  0x07, 1)
MyClassA(BC_PPC,   0x02, 5)
MyClassA(BC_SPARC, 0x08, 5)
MyClassA(BC_IA64,  0x04, 1)
=======
#include "../../Common/MyCom.h"

#include "../ICoder.h"

EXTERN_C_BEGIN

typedef SizeT (*Func_Bra)(Byte *data, SizeT size, UInt32 ip, int encoding);

EXTERN_C_END

namespace NCompress {
namespace NBranch {

class CCoder:
  public ICompressFilter,
  public CMyUnknownImp
{
  UInt32 _bufferPos;
  int _encode;
  Func_Bra BraFunc;
public:
  MY_UNKNOWN_IMP1(ICompressFilter);
  INTERFACE_ICompressFilter(;)

  CCoder(Func_Bra bra, int encode):  _bufferPos(0), _encode(encode), BraFunc(bra) {}
};

}}
>>>>>>> upstream/master

#endif
