<<<<<<< HEAD
// DLLExports.cpp

#include "StdAfx.h"

#include "../../Common/MyInitGuid.h"

#if defined(_WIN32) && defined(_7ZIP_LARGE_PAGES)
=======
// DLLExports2.cpp

#include "StdAfx.h"

#include "../../Common/MyWindows.h"

#include "../../Common/MyInitGuid.h"

#if defined(_7ZIP_LARGE_PAGES)
>>>>>>> upstream/master
#include "../../../C/Alloc.h"
#endif

#include "../../Common/ComTry.h"

#include "../../Windows/NtCheck.h"
#include "../../Windows/PropVariant.h"

#include "../ICoder.h"
#include "../IPassword.h"

<<<<<<< HEAD
=======
#include "../Common/CreateCoder.h"

>>>>>>> upstream/master
#include "IArchive.h"

HINSTANCE g_hInstance;

#define NT_CHECK_FAIL_ACTION return FALSE;

<<<<<<< HEAD
=======
#ifdef _WIN32
>>>>>>> upstream/master
extern "C"
BOOL WINAPI DllMain(
  #ifdef UNDER_CE
  HANDLE
  #else
  HINSTANCE
  #endif
  hInstance, DWORD dwReason, LPVOID /*lpReserved*/)
{
  if (dwReason == DLL_PROCESS_ATTACH)
  {
<<<<<<< HEAD
    g_hInstance = (HINSTANCE)hInstance;
    NT_CHECK;
  }
  return TRUE;
}

DEFINE_GUID(CLSID_CArchiveHandler,
0x23170F69, 0x40C1, 0x278A, 0x10, 0x00, 0x00, 0x01, 0x10, 0x00, 0x00, 0x00);

static const UInt16 kDecodeId = 0x2790;

DEFINE_GUID(CLSID_CCodec,
0x23170F69, 0x40C1, kDecodeId, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);

STDAPI CreateCoder(const GUID *clsid, const GUID *iid, void **outObject);
STDAPI CreateArchiver(const GUID *classID, const GUID *iid, void **outObject);
=======
    // OutputDebugStringA("7z.dll DLL_PROCESS_ATTACH");
    g_hInstance = (HINSTANCE)hInstance;
    NT_CHECK;
  }
  /*
  if (dwReason == DLL_PROCESS_DETACH)
  {
    OutputDebugStringA("7z.dll DLL_PROCESS_DETACH");
  }
  */
  return TRUE;
}
#endif

DEFINE_GUID(CLSID_CArchiveHandler,
    k_7zip_GUID_Data1,
    k_7zip_GUID_Data2,
    k_7zip_GUID_Data3_Common,
    0x10, 0x00, 0x00, 0x01, 0x10, 0x00, 0x00, 0x00);

STDAPI CreateCoder(const GUID *clsid, const GUID *iid, void **outObject);
STDAPI CreateHasher(const GUID *clsid, IHasher **hasher);
STDAPI CreateArchiver(const GUID *clsid, const GUID *iid, void **outObject);
>>>>>>> upstream/master

STDAPI CreateObject(const GUID *clsid, const GUID *iid, void **outObject)
{
  // COM_TRY_BEGIN
  *outObject = 0;
<<<<<<< HEAD
  if (*iid == IID_ICompressCoder || *iid == IID_ICompressCoder2 || *iid == IID_ICompressFilter)
  {
    return CreateCoder(clsid, iid, outObject);
  }
  else
  {
    return CreateArchiver(clsid, iid, outObject);
  }
=======
  if (*iid == IID_ICompressCoder ||
      *iid == IID_ICompressCoder2 ||
      *iid == IID_ICompressFilter)
    return CreateCoder(clsid, iid, outObject);
  if (*iid == IID_IHasher)
    return CreateHasher(clsid, (IHasher **)outObject);
  return CreateArchiver(clsid, iid, outObject);
>>>>>>> upstream/master
  // COM_TRY_END
}

STDAPI SetLargePageMode()
{
<<<<<<< HEAD
  #if defined(_WIN32) && defined(_7ZIP_LARGE_PAGES)
=======
  #if defined(_7ZIP_LARGE_PAGES)
>>>>>>> upstream/master
  SetLargePageSize();
  #endif
  return S_OK;
}
<<<<<<< HEAD
=======

extern bool g_CaseSensitive;

STDAPI SetCaseSensitive(Int32 caseSensitive)
{
  g_CaseSensitive = (caseSensitive != 0);
  return S_OK;
}

#ifdef EXTERNAL_CODECS

CExternalCodecs g_ExternalCodecs;

STDAPI SetCodecs(ICompressCodecsInfo *compressCodecsInfo)
{
  COM_TRY_BEGIN

  // OutputDebugStringA(compressCodecsInfo ? "SetCodecs" : "SetCodecs NULL");
  if (compressCodecsInfo)
  {
    g_ExternalCodecs.GetCodecs = compressCodecsInfo;
    return g_ExternalCodecs.Load();
  }
  g_ExternalCodecs.ClearAndRelease();
  return S_OK;

  COM_TRY_END
}

#else

STDAPI SetCodecs(ICompressCodecsInfo *)
{
  return S_OK;
}

#endif
>>>>>>> upstream/master
