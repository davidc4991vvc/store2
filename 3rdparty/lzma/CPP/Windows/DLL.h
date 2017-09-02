// Windows/DLL.h

#ifndef __WINDOWS_DLL_H
#define __WINDOWS_DLL_H

#include "../Common/MyString.h"

namespace NWindows {
namespace NDLL {

#ifdef UNDER_CE
#define My_GetProcAddress(module, procName) ::GetProcAddressA(module, procName)
#else
#define My_GetProcAddress(module, procName) ::GetProcAddress(module, procName)
#endif
<<<<<<< HEAD
 
class CLibrary
{
  HMODULE _module;
=======

/* Win32: Don't call CLibrary::Free() and FreeLibrary() from another
    FreeLibrary() code: detaching code in DLL entry-point or in
    destructors of global objects in DLL module. */

class CLibrary
{
  HMODULE _module;

  // CLASS_NO_COPY(CLibrary);
>>>>>>> upstream/master
public:
  CLibrary(): _module(NULL) {};
  ~CLibrary() { Free(); }

  operator HMODULE() const { return _module; }
  HMODULE* operator&() { return &_module; }
<<<<<<< HEAD
  bool IsLoaded() const { return (_module != NULL); };
=======
  bool IsLoaded() const { return (_module != NULL); }
>>>>>>> upstream/master

  void Attach(HMODULE m)
  {
    Free();
    _module = m;
  }
  HMODULE Detach()
  {
    HMODULE m = _module;
    _module = NULL;
    return m;
  }

<<<<<<< HEAD
  bool Free();
  bool LoadEx(CFSTR path, DWORD flags = LOAD_LIBRARY_AS_DATAFILE);
  bool Load(CFSTR path);
=======
  bool Free() throw();
  bool LoadEx(CFSTR path, DWORD flags = LOAD_LIBRARY_AS_DATAFILE) throw();
  bool Load(CFSTR path) throw();
>>>>>>> upstream/master
  FARPROC GetProc(LPCSTR procName) const { return My_GetProcAddress(_module, procName); }
};

bool MyGetModuleFileName(FString &path);

FString GetModuleDirPrefix();

}}

#endif
