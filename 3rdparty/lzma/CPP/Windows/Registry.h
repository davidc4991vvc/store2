// Windows/Registry.h

#ifndef __WINDOWS_REGISTRY_H
#define __WINDOWS_REGISTRY_H

<<<<<<< HEAD
#include "Common/Buffer.h"
#include "Common/MyString.h"
#include "Common/Types.h"
=======
#include "../Common/MyBuffer.h"
#include "../Common/MyString.h"
>>>>>>> upstream/master

namespace NWindows {
namespace NRegistry {

LONG SetValue(HKEY parentKey, LPCTSTR keyName, LPCTSTR valueName, LPCTSTR value);

class CKey
{
  HKEY _object;
public:
  CKey(): _object(NULL) {}
  ~CKey() { Close(); }

  operator HKEY() const { return _object; }
  void Attach(HKEY key) { _object = key; }
  HKEY Detach()
  {
    HKEY key = _object;
    _object = NULL;
    return key;
  }

  LONG Create(HKEY parentKey, LPCTSTR keyName,
      LPTSTR keyClass = REG_NONE, DWORD options = REG_OPTION_NON_VOLATILE,
      REGSAM accessMask = KEY_ALL_ACCESS,
      LPSECURITY_ATTRIBUTES securityAttributes = NULL,
<<<<<<< HEAD
      LPDWORD disposition = NULL);
  LONG Open(HKEY parentKey, LPCTSTR keyName, REGSAM accessMask = KEY_ALL_ACCESS);

  LONG Close();

  LONG DeleteSubKey(LPCTSTR subKeyName);
  LONG RecurseDeleteKey(LPCTSTR subKeyName);

  LONG DeleteValue(LPCTSTR name);
=======
      LPDWORD disposition = NULL) throw();
  LONG Open(HKEY parentKey, LPCTSTR keyName, REGSAM accessMask = KEY_ALL_ACCESS) throw();

  LONG Close() throw();

  LONG DeleteSubKey(LPCTSTR subKeyName) throw();
  LONG RecurseDeleteKey(LPCTSTR subKeyName) throw();

  LONG DeleteValue(LPCTSTR name) throw();
>>>>>>> upstream/master
  #ifndef _UNICODE
  LONG DeleteValue(LPCWSTR name);
  #endif

<<<<<<< HEAD
  LONG SetValue(LPCTSTR valueName, UInt32 value);
  LONG SetValue(LPCTSTR valueName, bool value);
  LONG SetValue(LPCTSTR valueName, LPCTSTR value);
=======
  LONG SetValue(LPCTSTR valueName, UInt32 value) throw();
  LONG SetValue(LPCTSTR valueName, bool value) throw();
  LONG SetValue(LPCTSTR valueName, LPCTSTR value) throw();
>>>>>>> upstream/master
  // LONG SetValue(LPCTSTR valueName, const CSysString &value);
  #ifndef _UNICODE
  LONG SetValue(LPCWSTR name, LPCWSTR value);
  // LONG SetValue(LPCWSTR name, const UString &value);
  #endif

<<<<<<< HEAD
  LONG SetValue(LPCTSTR name, const void *value, UInt32 size);
=======
  LONG SetValue(LPCTSTR name, const void *value, UInt32 size) throw();
>>>>>>> upstream/master

  LONG SetValue_Strings(LPCTSTR valueName, const UStringVector &strings);
  LONG GetValue_Strings(LPCTSTR valueName, UStringVector &strings);

<<<<<<< HEAD
  LONG SetKeyValue(LPCTSTR keyName, LPCTSTR valueName, LPCTSTR value);

  LONG QueryValue(LPCTSTR name, UInt32 &value);
  LONG QueryValue(LPCTSTR name, bool &value);
  LONG QueryValue(LPCTSTR name, LPTSTR value, UInt32 &dataSize);
  LONG QueryValue(LPCTSTR name, CSysString &value);

  LONG GetValue_IfOk(LPCTSTR name, UInt32 &value);
  LONG GetValue_IfOk(LPCTSTR name, bool &value);
=======
  LONG SetKeyValue(LPCTSTR keyName, LPCTSTR valueName, LPCTSTR value) throw();

  LONG QueryValue(LPCTSTR name, UInt32 &value) throw();
  LONG QueryValue(LPCTSTR name, bool &value) throw();
  LONG QueryValue(LPCTSTR name, LPTSTR value, UInt32 &dataSize) throw();
  LONG QueryValue(LPCTSTR name, CSysString &value);

  LONG GetValue_IfOk(LPCTSTR name, UInt32 &value) throw();
  LONG GetValue_IfOk(LPCTSTR name, bool &value) throw();
>>>>>>> upstream/master

  #ifndef _UNICODE
  LONG QueryValue(LPCWSTR name, LPWSTR value, UInt32 &dataSize);
  LONG QueryValue(LPCWSTR name, UString &value);
  #endif

<<<<<<< HEAD
  LONG QueryValue(LPCTSTR name, void *value, UInt32 &dataSize);
=======
  LONG QueryValue(LPCTSTR name, void *value, UInt32 &dataSize) throw();
>>>>>>> upstream/master
  LONG QueryValue(LPCTSTR name, CByteBuffer &value, UInt32 &dataSize);

  LONG EnumKeys(CSysStringVector &keyNames);
};

}}

#endif
