/* LzmaLibExports.c -- LZMA library DLL Entry point
<<<<<<< HEAD
2008-10-04 : Igor Pavlov : Public domain */
=======
2015-11-08 : Igor Pavlov : Public domain */

#include "../../Precomp.h"
>>>>>>> upstream/master

#include <windows.h>

BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
<<<<<<< HEAD
  hInstance = hInstance;
  dwReason = dwReason;
  lpReserved = lpReserved;
=======
  UNUSED_VAR(hInstance);
  UNUSED_VAR(dwReason);
  UNUSED_VAR(lpReserved);
>>>>>>> upstream/master
  return TRUE;
}
