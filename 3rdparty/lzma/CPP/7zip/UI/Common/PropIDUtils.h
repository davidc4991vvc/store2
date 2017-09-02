// PropIDUtils.h

#ifndef __PROPID_UTILS_H
#define __PROPID_UTILS_H

<<<<<<< HEAD
#include "Common/MyString.h"
#include "Common/Types.h"

void ConvertUInt32ToHex(UInt32 value, wchar_t *s);
UString ConvertPropertyToString(const PROPVARIANT &propVariant, PROPID propID, bool full = true);
=======
#include "../../../Common/MyString.h"

// provide at least 64 bytes for buffer including zero-end
void ConvertPropertyToShortString(char *dest, const PROPVARIANT &propVariant, PROPID propID, bool full = true) throw();
void ConvertPropertyToString(UString &dest, const PROPVARIANT &propVariant, PROPID propID, bool full = true);

bool ConvertNtReparseToString(const Byte *data, UInt32 size, UString &s);
void ConvertNtSecureToString(const Byte *data, UInt32 size, AString &s);
bool CheckNtSecure(const Byte *data, UInt32 size) throw();;

void ConvertWinAttribToString(char *s, UInt32 wa) throw();
>>>>>>> upstream/master

#endif
