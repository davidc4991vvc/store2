// 7zRegister.cpp

#include "StdAfx.h"

#include "../../Common/RegisterArc.h"

#include "7zHandler.h"
<<<<<<< HEAD
static IInArchive *CreateArc() { return new NArchive::N7z::CHandler; }
#ifndef EXTRACT_ONLY
static IOutArchive *CreateArcOut() { return new NArchive::N7z::CHandler; }
#else
#define CreateArcOut 0
#endif

static CArcInfo g_ArcInfo =
  { L"7z", L"7z", 0, 7, {'7', 'z', 0xBC, 0xAF, 0x27, 0x1C}, 6, false, CreateArc, CreateArcOut };

REGISTER_ARC(7z)
=======

namespace NArchive {
namespace N7z {

static Byte k_Signature_Dec[kSignatureSize] = {'7' + 1, 'z', 0xBC, 0xAF, 0x27, 0x1C};

REGISTER_ARC_IO_DECREMENT_SIG(
  "7z", "7z", NULL, 7,
  k_Signature_Dec,
  0,
  NArcInfoFlags::kFindSignature,
  NULL);

}}
>>>>>>> upstream/master
