// PpmdRegister.cpp
<<<<<<< HEAD
// 2009-05-30 : Igor Pavlov : Public domain
=======
>>>>>>> upstream/master

#include "StdAfx.h"

#include "../Common/RegisterCodec.h"

#include "PpmdDecoder.h"

<<<<<<< HEAD
static void *CreateCodec() { return (void *)(ICompressCoder *)(new NCompress::NPpmd::CDecoder); }
#ifndef EXTRACT_ONLY
#include "PpmdEncoder.h"
static void *CreateCodecOut() { return (void *)(ICompressCoder *)(new NCompress::NPpmd::CEncoder);  }
#else
#define CreateCodecOut 0
#endif

static CCodecInfo g_CodecInfo =
  { CreateCodec, CreateCodecOut, 0x030401, L"PPMD", 1, false };

REGISTER_CODEC(PPMD)
=======
#ifndef EXTRACT_ONLY
#include "PpmdEncoder.h"
#endif

namespace NCompress {
namespace NPpmd {

REGISTER_CODEC_E(PPMD,
    CDecoder(),
    CEncoder(),
    0x30401,
    "PPMD")

}}
>>>>>>> upstream/master
