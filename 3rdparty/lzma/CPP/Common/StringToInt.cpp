// Common/StringToInt.cpp

#include "StdAfx.h"

#include "StringToInt.h"

<<<<<<< HEAD
UInt64 ConvertStringToUInt64(const char *s, const char **end)
{
  UInt64 result = 0;
  for (;;)
  {
    char c = *s;
    if (c < '0' || c > '9')
    {
      if (end != NULL)
        *end = s;
      return result;
    }
    result *= 10;
    result += (c - '0');
    s++;
  }
}

UInt64 ConvertOctStringToUInt64(const char *s, const char **end)
{
  UInt64 result = 0;
  for (;;)
  {
    char c = *s;
    if (c < '0' || c > '7')
    {
      if (end != NULL)
        *end = s;
      return result;
    }
    result <<= 3;
    result += (c - '0');
    s++;
  }
}

UInt64 ConvertHexStringToUInt64(const char *s, const char **end)
{
  UInt64 result = 0;
  for (;;)
  {
    char c = *s;
    UInt32 v;
=======
static const UInt32 k_UInt32_max = 0xFFFFFFFF;
static const UInt64 k_UInt64_max = UINT64_CONST(0xFFFFFFFFFFFFFFFF);
// static const UInt64 k_UInt64_max = (UInt64)(Int64)-1;

#define CONVERT_STRING_TO_UINT_FUNC(uintType, charType, charTypeUnsigned) \
  uintType ConvertStringTo ## uintType(const charType *s, const charType **end) throw() { \
    if (end) *end = s; \
    uintType res = 0; \
    for (;; s++) { \
      charTypeUnsigned c = (charTypeUnsigned)*s; \
      if (c < '0' || c > '9') { if (end) *end = s; return res; } \
      if (res > (k_ ## uintType ## _max) / 10) return 0; \
      res *= 10; \
      unsigned v = (c - '0'); \
      if (res > (k_ ## uintType ## _max) - v) return 0; \
      res += v; }}

CONVERT_STRING_TO_UINT_FUNC(UInt32, char, Byte)
CONVERT_STRING_TO_UINT_FUNC(UInt32, wchar_t, wchar_t)
CONVERT_STRING_TO_UINT_FUNC(UInt64, char, Byte)
CONVERT_STRING_TO_UINT_FUNC(UInt64, wchar_t, wchar_t)

Int32 ConvertStringToInt32(const wchar_t *s, const wchar_t **end) throw()
{
  if (end)
    *end = s;
  const wchar_t *s2 = s;
  if (*s == '-')
    s2++;
  if (*s2 == 0)
    return 0;
  const wchar_t *end2;
  UInt32 res = ConvertStringToUInt32(s2, &end2);
  if (*s == '-')
  {
    if (res > ((UInt32)1 << (32 - 1)))
      return 0;
  }
  else if ((res & ((UInt32)1 << (32 - 1))) != 0)
    return 0;
  if (end)
    *end = end2;
  if (*s == '-')
    return -(Int32)res;
  return (Int32)res;
}

UInt32 ConvertOctStringToUInt32(const char *s, const char **end) throw()
{
  if (end)
    *end = s;
  UInt32 res = 0;
  for (;; s++)
  {
    unsigned c = (unsigned char)*s;
    if (c < '0' || c > '7')
    {
      if (end)
        *end = s;
      return res;
    }
    if ((res & (UInt32)7 << (32 - 3)) != 0)
      return 0;
    res <<= 3;
    res |= (unsigned)(c - '0');
  }
}

UInt64 ConvertOctStringToUInt64(const char *s, const char **end) throw()
{
  if (end)
    *end = s;
  UInt64 res = 0;
  for (;; s++)
  {
    unsigned c = (unsigned char)*s;
    if (c < '0' || c > '7')
    {
      if (end)
        *end = s;
      return res;
    }
    if ((res & (UInt64)7 << (64 - 3)) != 0)
      return 0;
    res <<= 3;
    res |= (unsigned)(c - '0');
  }
}

UInt32 ConvertHexStringToUInt32(const char *s, const char **end) throw()
{
  if (end)
    *end = s;
  UInt32 res = 0;
  for (;; s++)
  {
    unsigned c = (Byte)*s;
    unsigned v;
>>>>>>> upstream/master
    if (c >= '0' && c <= '9') v = (c - '0');
    else if (c >= 'A' && c <= 'F') v = 10 + (c - 'A');
    else if (c >= 'a' && c <= 'f') v = 10 + (c - 'a');
    else
    {
<<<<<<< HEAD
      if (end != NULL)
        *end = s;
      return result;
    }
    result <<= 4;
    result |= v;
    s++;
  }
}


UInt64 ConvertStringToUInt64(const wchar_t *s, const wchar_t **end)
{
  UInt64 result = 0;
  for (;;)
  {
    wchar_t c = *s;
    if (c < '0' || c > '9')
    {
      if (end != NULL)
        *end = s;
      return result;
    }
    result *= 10;
    result += (c - '0');
    s++;
  }
}


Int64 ConvertStringToInt64(const char *s, const char **end)
{
  if (*s == '-')
    return -(Int64)ConvertStringToUInt64(s + 1, end);
  return ConvertStringToUInt64(s, end);
}

Int64 ConvertStringToInt64(const wchar_t *s, const wchar_t **end)
{
  if (*s == L'-')
    return -(Int64)ConvertStringToUInt64(s + 1, end);
  return ConvertStringToUInt64(s, end);
}
=======
      if (end)
        *end = s;
      return res;
    }
    if ((res & (UInt32)0xF << (32 - 4)) != 0)
      return 0;
    res <<= 4;
    res |= v;
  }
}

UInt64 ConvertHexStringToUInt64(const char *s, const char **end) throw()
{
  if (end)
    *end = s;
  UInt64 res = 0;
  for (;; s++)
  {
    unsigned c = (Byte)*s;
    unsigned v;
    if (c >= '0' && c <= '9') v = (c - '0');
    else if (c >= 'A' && c <= 'F') v = 10 + (c - 'A');
    else if (c >= 'a' && c <= 'f') v = 10 + (c - 'a');
    else
    {
      if (end)
        *end = s;
      return res;
    }
    if ((res & (UInt64)0xF << (64 - 4)) != 0)
      return 0;
    res <<= 4;
    res |= v;
  }
}
>>>>>>> upstream/master
