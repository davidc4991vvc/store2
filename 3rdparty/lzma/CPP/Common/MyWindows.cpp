// MyWindows.cpp

#include "StdAfx.h"

#ifndef _WIN32

<<<<<<< HEAD
#include "MyWindows.h"
#include "Types.h"
#include <malloc.h>
=======
#include <stdlib.h>

#include "MyWindows.h"
>>>>>>> upstream/master

static inline void *AllocateForBSTR(size_t cb) { return ::malloc(cb); }
static inline void FreeForBSTR(void *pv) { ::free(pv);}

<<<<<<< HEAD
static UINT MyStringLen(const wchar_t *s)
{
  UINT i;
  for (i = 0; s[i] != '\0'; i++);
  return i;
}

BSTR SysAllocStringByteLen(LPCSTR psz, UINT len)
{
  int realLen = len + sizeof(UINT) + sizeof(OLECHAR) + sizeof(OLECHAR);
  void *p = AllocateForBSTR(realLen);
  if (p == 0)
    return 0;
  *(UINT *)p = len;
  BSTR bstr = (BSTR)((UINT *)p + 1);
  if (psz)
  {
    memmove(bstr, psz, len);
    Byte *pb = ((Byte *)bstr) + len;
    for (unsigned i = 0; i < sizeof(OLECHAR) * 2; i++)
      pb[i] = 0;
  }
  return bstr;
}

BSTR SysAllocString(const OLECHAR *sz)
{
  if (sz == 0)
    return 0;
  UINT strLen = MyStringLen(sz);
  UINT len = (strLen + 1) * sizeof(OLECHAR);
  void *p = AllocateForBSTR(len + sizeof(UINT));
  if (p == 0)
    return 0;
  *(UINT *)p = strLen;
  BSTR bstr = (BSTR)((UINT *)p + 1);
  memmove(bstr, sz, len);
  return bstr;
=======
/* Win32 uses DWORD (32-bit) type to store size of string before (OLECHAR *) string.
  We must select CBstrSizeType for another systems (not Win32):

    if (CBstrSizeType is UINT32),
          then we support only strings smaller than 4 GB.
          Win32 version always has that limitation.
  
    if (CBstrSizeType is UINT),
          (UINT can be 16/32/64-bit)
          We can support strings larger than 4 GB (if UINT is 64-bit),
          but sizeof(UINT) can be different in parts compiled by
          different compilers/settings,
          and we can't send such BSTR strings between such parts.
*/

typedef UINT32 CBstrSizeType;
// typedef UINT CBstrSizeType;

#define k_BstrSize_Max 0xFFFFFFFF
// #define k_BstrSize_Max UINT_MAX
// #define k_BstrSize_Max ((UINT)(INT)-1)

BSTR SysAllocStringByteLen(LPCSTR s, UINT len)
{
  /* Original SysAllocStringByteLen in Win32 maybe fills only unaligned null OLECHAR at the end.
     We provide also aligned null OLECHAR at the end. */

  if (len >= (k_BstrSize_Max - sizeof(OLECHAR) - sizeof(OLECHAR) - sizeof(CBstrSizeType)))
    return NULL;

  UINT size = (len + sizeof(OLECHAR) + sizeof(OLECHAR) - 1) & ~(sizeof(OLECHAR) - 1);
  void *p = AllocateForBSTR(size + sizeof(CBstrSizeType));
  if (!p)
    return NULL;
  *(CBstrSizeType *)p = (CBstrSizeType)len;
  BSTR bstr = (BSTR)((CBstrSizeType *)p + 1);
  if (s)
    memcpy(bstr, s, len);
  for (; len < size; len++)
    ((Byte *)bstr)[len] = 0;
  return bstr;
}

BSTR SysAllocStringLen(const OLECHAR *s, UINT len)
{
  if (len >= (k_BstrSize_Max - sizeof(OLECHAR) - sizeof(CBstrSizeType)) / sizeof(OLECHAR))
    return NULL;

  UINT size = len * sizeof(OLECHAR);
  void *p = AllocateForBSTR(size + sizeof(CBstrSizeType) + sizeof(OLECHAR));
  if (!p)
    return NULL;
  *(CBstrSizeType *)p = (CBstrSizeType)size;
  BSTR bstr = (BSTR)((CBstrSizeType *)p + 1);
  if (s)
    memcpy(bstr, s, size);
  bstr[len] = 0;
  return bstr;
}

BSTR SysAllocString(const OLECHAR *s)
{
  if (!s)
    return 0;
  const OLECHAR *s2 = s;
  while (*s2 != 0)
    s2++;
  return SysAllocStringLen(s, (UINT)(s2 - s));
>>>>>>> upstream/master
}

void SysFreeString(BSTR bstr)
{
<<<<<<< HEAD
  if (bstr != 0)
    FreeForBSTR((UINT *)bstr - 1);
=======
  if (bstr)
    FreeForBSTR((CBstrSizeType *)bstr - 1);
>>>>>>> upstream/master
}

UINT SysStringByteLen(BSTR bstr)
{
<<<<<<< HEAD
  if (bstr == 0)
    return 0;
  return *((UINT *)bstr - 1);
=======
  if (!bstr)
    return 0;
  return *((CBstrSizeType *)bstr - 1);
>>>>>>> upstream/master
}

UINT SysStringLen(BSTR bstr)
{
<<<<<<< HEAD
  return SysStringByteLen(bstr) / sizeof(OLECHAR);
}

=======
  if (!bstr)
    return 0;
  return *((CBstrSizeType *)bstr - 1) / sizeof(OLECHAR);
}


>>>>>>> upstream/master
HRESULT VariantClear(VARIANTARG *prop)
{
  if (prop->vt == VT_BSTR)
    SysFreeString(prop->bstrVal);
  prop->vt = VT_EMPTY;
  return S_OK;
}

<<<<<<< HEAD
HRESULT VariantCopy(VARIANTARG *dest, VARIANTARG *src)
=======
HRESULT VariantCopy(VARIANTARG *dest, const VARIANTARG *src)
>>>>>>> upstream/master
{
  HRESULT res = ::VariantClear(dest);
  if (res != S_OK)
    return res;
  if (src->vt == VT_BSTR)
  {
    dest->bstrVal = SysAllocStringByteLen((LPCSTR)src->bstrVal,
        SysStringByteLen(src->bstrVal));
<<<<<<< HEAD
    if (dest->bstrVal == 0)
=======
    if (!dest->bstrVal)
>>>>>>> upstream/master
      return E_OUTOFMEMORY;
    dest->vt = VT_BSTR;
  }
  else
    *dest = *src;
  return S_OK;
}

LONG CompareFileTime(const FILETIME* ft1, const FILETIME* ft2)
{
  if (ft1->dwHighDateTime < ft2->dwHighDateTime) return -1;
  if (ft1->dwHighDateTime > ft2->dwHighDateTime) return 1;
  if (ft1->dwLowDateTime < ft2->dwLowDateTime) return -1;
  if (ft1->dwLowDateTime > ft2->dwLowDateTime) return 1;
  return 0;
}

DWORD GetLastError()
{
  return 0;
}

#endif
