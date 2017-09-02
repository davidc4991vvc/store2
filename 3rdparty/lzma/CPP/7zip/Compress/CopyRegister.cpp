// CopyRegister.cpp

#include "StdAfx.h"

#include "../Common/RegisterCodec.h"

#include "CopyCoder.h"

<<<<<<< HEAD
static void *CreateCodec() { return (void *)(ICompressCoder *)(new NCompress::CCopyCoder); }

static CCodecInfo g_CodecInfo =
{ CreateCodec, CreateCodec, 0x00, L"Copy", 1, false };

REGISTER_CODEC(Copy)
=======
namespace NCompress {

REGISTER_CODEC_CREATE(CreateCodec, CCopyCoder())

REGISTER_CODEC_2(Copy, CreateCodec, CreateCodec, 0, "Copy")

}
>>>>>>> upstream/master
