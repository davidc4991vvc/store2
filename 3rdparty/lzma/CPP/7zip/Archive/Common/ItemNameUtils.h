// Archive/Common/ItemNameUtils.h

<<<<<<< HEAD
#ifndef __ARCHIVE_ITEMNAMEUTILS_H
#define __ARCHIVE_ITEMNAMEUTILS_H
=======
#ifndef __ARCHIVE_ITEM_NAME_UTILS_H
#define __ARCHIVE_ITEM_NAME_UTILS_H
>>>>>>> upstream/master

#include "../../../Common/MyString.h"

namespace NArchive {
namespace NItemName {

<<<<<<< HEAD
  UString MakeLegalName(const UString &name);
  UString GetOSName(const UString &name);
  UString GetOSName2(const UString &name);
=======
  void ReplaceToOsPathSeparator(wchar_t *s);

  UString MakeLegalName(const UString &name);
  UString GetOSName(const UString &name);
  UString GetOSName2(const UString &name);
  void ConvertToOSName2(UString &name);
>>>>>>> upstream/master
  bool HasTailSlash(const AString &name, UINT codePage);

  #ifdef _WIN32
  inline UString WinNameToOSName(const UString &name)  { return name; }
  #else
  UString WinNameToOSName(const UString &name);
  #endif

}}

#endif
