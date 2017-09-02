// BranchRegister.cpp

#include "StdAfx.h"

<<<<<<< HEAD
=======
#include "../../../C/Bra.h"

>>>>>>> upstream/master
#include "../Common/RegisterCodec.h"

#include "BranchMisc.h"

<<<<<<< HEAD
#define CREATE_CODEC(x) \
  static void *CreateCodec ## x() { return (void *)(ICompressFilter *)(new C ## x ## _Decoder); } \
  static void *CreateCodec ## x ## Out() { return (void *)(ICompressFilter *)(new C ## x ## _Encoder); }

CREATE_CODEC(BC_PPC)
CREATE_CODEC(BC_IA64)
CREATE_CODEC(BC_ARM)
CREATE_CODEC(BC_ARMT)
CREATE_CODEC(BC_SPARC)

#define METHOD_ITEM(x, id1, id2, name) { CreateCodec ## x, CreateCodec ## x ## Out, 0x03030000 + (id1 * 256) + id2, name, 1, true  }

static CCodecInfo g_CodecsInfo[] =
{
  METHOD_ITEM(BC_PPC,   0x02, 0x05, L"PPC"),
  METHOD_ITEM(BC_IA64,  0x04, 1, L"IA64"),
  METHOD_ITEM(BC_ARM,   0x05, 1, L"ARM"),
  METHOD_ITEM(BC_ARMT,  0x07, 1, L"ARMT"),
  METHOD_ITEM(BC_SPARC, 0x08, 0x05, L"SPARC")
};

REGISTER_CODECS(Branch)
=======
namespace NCompress {
namespace NBranch {

#define CREATE_BRA(n) \
    REGISTER_FILTER_CREATE(CreateBra_Decoder_ ## n, CCoder(n ## _Convert, false)) \
    REGISTER_FILTER_CREATE(CreateBra_Encoder_ ## n, CCoder(n ## _Convert, true)) \

CREATE_BRA(PPC)
CREATE_BRA(IA64)
CREATE_BRA(ARM)
CREATE_BRA(ARMT)
CREATE_BRA(SPARC)

#define METHOD_ITEM(n, id, name) \
    REGISTER_FILTER_ITEM( \
      CreateBra_Decoder_ ## n, \
      CreateBra_Encoder_ ## n, \
      0x3030000 + id, name)

REGISTER_CODECS_VAR
{
  METHOD_ITEM(PPC,   0x205, "PPC"),
  METHOD_ITEM(IA64,  0x401, "IA64"),
  METHOD_ITEM(ARM,   0x501, "ARM"),
  METHOD_ITEM(ARMT,  0x701, "ARMT"),
  METHOD_ITEM(SPARC, 0x805, "SPARC")
};

REGISTER_CODECS(Branch)

}}
>>>>>>> upstream/master
