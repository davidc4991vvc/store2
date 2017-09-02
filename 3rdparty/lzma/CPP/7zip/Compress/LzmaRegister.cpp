// LzmaRegister.cpp

#include "StdAfx.h"

#include "../Common/RegisterCodec.h"

#include "LzmaDecoder.h"

<<<<<<< HEAD
static void *CreateCodec() { return (void *)(ICompressCoder *)(new NCompress::NLzma::CDecoder); }
#ifndef EXTRACT_ONLY
#include "LzmaEncoder.h"
static void *CreateCodecOut() { return (void *)(ICompressCoder *)(new NCompress::NLzma::CEncoder);  }
#else
#define CreateCodecOut 0
#endif

static CCodecInfo g_CodecInfo =
  { CreateCodec, CreateCodecOut, 0x030101, L"LZMA", 1, false };

REGISTER_CODEC(LZMA)
=======
#ifndef EXTRACT_ONLY
#include "LzmaEncoder.h"
#endif

namespace NCompress {
namespace NLzma {

REGISTER_CODEC_E(LZMA,
    CDecoder(),
    CEncoder(),
    0x30101,
    "LZMA")

}}
>>>>>>> upstream/master
