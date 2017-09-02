// Lzma2Register.cpp

#include "StdAfx.h"

#include "../Common/RegisterCodec.h"

#include "Lzma2Decoder.h"

<<<<<<< HEAD
static void *CreateCodec() { return (void *)(ICompressCoder *)(new NCompress::NLzma2::CDecoder); }
#ifndef EXTRACT_ONLY
#include "Lzma2Encoder.h"
static void *CreateCodecOut() { return (void *)(ICompressCoder *)(new NCompress::NLzma2::CEncoder);  }
#else
#define CreateCodecOut 0
#endif

static CCodecInfo g_CodecInfo =
  { CreateCodec, CreateCodecOut, 0x21, L"LZMA2", 1, false };

REGISTER_CODEC(LZMA2)
=======
#ifndef EXTRACT_ONLY
#include "Lzma2Encoder.h"
#endif

namespace NCompress {
namespace NLzma2 {

REGISTER_CODEC_E(LZMA2,
    CDecoder(),
    CEncoder(),
    0x21,
    "LZMA2")

}}
>>>>>>> upstream/master
