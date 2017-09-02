// Bcj2Register.cpp

#include "StdAfx.h"

#include "../Common/RegisterCodec.h"

#include "Bcj2Coder.h"

<<<<<<< HEAD
static void *CreateCodec() { return (void *)(ICompressCoder2 *)(new NCompress::NBcj2::CDecoder()); }
#ifndef EXTRACT_ONLY
static void *CreateCodecOut() { return (void *)(ICompressCoder2 *)(new NCompress::NBcj2::CEncoder());  }
#else
#define CreateCodecOut 0
#endif

static CCodecInfo g_CodecInfo =
  { CreateCodec, CreateCodecOut, 0x0303011B, L"BCJ2", 4, false };

REGISTER_CODEC(BCJ2)
=======
namespace NCompress {
namespace NBcj2 {

REGISTER_CODEC_CREATE_2(CreateCodec, CDecoder(), ICompressCoder2)
#ifndef EXTRACT_ONLY
REGISTER_CODEC_CREATE_2(CreateCodecOut, CEncoder(), ICompressCoder2)
#else
#define CreateCodecOut NULL
#endif

REGISTER_CODEC_VAR
  { CreateCodec, CreateCodecOut, 0x303011B, "BCJ2", 4, false };

REGISTER_CODEC(BCJ2)

}}
>>>>>>> upstream/master
