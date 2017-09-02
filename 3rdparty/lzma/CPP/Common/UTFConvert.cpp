// UTFConvert.cpp

#include "StdAfx.h"

<<<<<<< HEAD
#include "UTFConvert.h"
#include "Types.h"

static const Byte kUtf8Limits[5] = { 0xC0, 0xE0, 0xF0, 0xF8, 0xFC };

static Bool Utf8_To_Utf16(wchar_t *dest, size_t *destLen, const char *src, size_t srcLen)
{
  size_t destPos = 0, srcPos = 0;
  for (;;)
  {
    Byte c;
    int numAdds;
    if (srcPos == srcLen)
    {
      *destLen = destPos;
      return True;
    }
    c = (Byte)src[srcPos++];
=======
#include "MyTypes.h"
#include "UTFConvert.h"

#ifdef _WIN32
#define _WCHART_IS_16BIT 1
#endif

/*
  _UTF8_START(n) - is a base value for start byte (head), if there are (n) additional bytes after start byte
  
  n : _UTF8_START(n) : Bits of code point

  0 : 0x80 :    : unused
  1 : 0xC0 : 11 :
  2 : 0xE0 : 16 : Basic Multilingual Plane
  3 : 0xF0 : 21 : Unicode space
  3 : 0xF8 : 26 :
  5 : 0xFC : 31 : UCS-4
  6 : 0xFE : 36 : We can use it, if we want to encode any 32-bit value
  7 : 0xFF :
*/

#define _UTF8_START(n) (0x100 - (1 << (7 - (n))))

#define _UTF8_HEAD_PARSE2(n) if (c < _UTF8_START((n) + 1)) { numBytes = (n); c -= _UTF8_START(n); }

#define _UTF8_HEAD_PARSE \
         _UTF8_HEAD_PARSE2(1) \
    else _UTF8_HEAD_PARSE2(2) \
    else _UTF8_HEAD_PARSE2(3) \
    else _UTF8_HEAD_PARSE2(4) \
    else _UTF8_HEAD_PARSE2(5) \

    // else _UTF8_HEAD_PARSE2(6)

bool CheckUTF8(const char *src, bool allowReduced) throw()
{
  for (;;)
  {
    Byte c = *src++;
    if (c == 0)
      return true;

    if (c < 0x80)
      continue;
    if (c < 0xC0)   // (c < 0xC0 + 2) // if we support only optimal encoding chars
      return false;
    
    unsigned numBytes;
    _UTF8_HEAD_PARSE
    else
      return false;
    
    UInt32 val = c;

    do
    {
      Byte c2 = *src++;
      if (c2 < 0x80 || c2 >= 0xC0)
        return allowReduced && c2 == 0;
      val <<= 6;
      val |= (c2 - 0x80);
    }
    while (--numBytes);
    
    if (val >= 0x110000)
      return false;
  }
}


#define _ERROR_UTF8 \
  { if (dest) dest[destPos] = (wchar_t)0xFFFD; destPos++; ok = false; continue; }

static bool Utf8_To_Utf16(wchar_t *dest, size_t *destLen, const char *src, const char *srcLim) throw()
{
  size_t destPos = 0;
  bool ok = true;

  for (;;)
  {
    Byte c;
    if (src == srcLim)
    {
      *destLen = destPos;
      return ok;
    }
    c = *src++;
>>>>>>> upstream/master

    if (c < 0x80)
    {
      if (dest)
        dest[destPos] = (wchar_t)c;
      destPos++;
      continue;
    }
    if (c < 0xC0)
<<<<<<< HEAD
      break;
    for (numAdds = 1; numAdds < 5; numAdds++)
      if (c < kUtf8Limits[numAdds])
        break;
    UInt32 value = (c - kUtf8Limits[numAdds - 1]);
=======
      _ERROR_UTF8

    unsigned numBytes;
    _UTF8_HEAD_PARSE
    else
      _ERROR_UTF8
    
    UInt32 val = c;
>>>>>>> upstream/master

    do
    {
      Byte c2;
<<<<<<< HEAD
      if (srcPos == srcLen)
        break;
      c2 = (Byte)src[srcPos++];
      if (c2 < 0x80 || c2 >= 0xC0)
        break;
      value <<= 6;
      value |= (c2 - 0x80);
    }
    while (--numAdds != 0);
    
    if (value < 0x10000)
    {
      if (dest)
        dest[destPos] = (wchar_t)value;
=======
      if (src == srcLim)
        break;
      c2 = *src;
      if (c2 < 0x80 || c2 >= 0xC0)
        break;
      src++;
      val <<= 6;
      val |= (c2 - 0x80);
    }
    while (--numBytes);

    if (numBytes != 0)
      _ERROR_UTF8

    if (val < 0x10000)
    {
      if (dest)
        dest[destPos] = (wchar_t)val;
>>>>>>> upstream/master
      destPos++;
    }
    else
    {
<<<<<<< HEAD
      value -= 0x10000;
      if (value >= 0x100000)
        break;
      if (dest)
      {
        dest[destPos + 0] = (wchar_t)(0xD800 + (value >> 10));
        dest[destPos + 1] = (wchar_t)(0xDC00 + (value & 0x3FF));
=======
      val -= 0x10000;
      if (val >= 0x100000)
        _ERROR_UTF8
      if (dest)
      {
        dest[destPos + 0] = (wchar_t)(0xD800 + (val >> 10));
        dest[destPos + 1] = (wchar_t)(0xDC00 + (val & 0x3FF));
>>>>>>> upstream/master
      }
      destPos += 2;
    }
  }
<<<<<<< HEAD
  *destLen = destPos;
  return False;
}

static Bool Utf16_To_Utf8(char *dest, size_t *destLen, const wchar_t *src, size_t srcLen)
{
  size_t destPos = 0, srcPos = 0;
  for (;;)
  {
    unsigned numAdds;
    UInt32 value;
    if (srcPos == srcLen)
    {
      *destLen = destPos;
      return True;
    }
    value = src[srcPos++];
    if (value < 0x80)
    {
      if (dest)
        dest[destPos] = (char)value;
      destPos++;
      continue;
    }
    if (value >= 0xD800 && value < 0xE000)
    {
      UInt32 c2;
      if (value >= 0xDC00 || srcPos == srcLen)
        break;
      c2 = src[srcPos++];
      if (c2 < 0xDC00 || c2 >= 0xE000)
        break;
      value = (((value - 0xD800) << 10) | (c2 - 0xDC00)) + 0x10000;
    }
    for (numAdds = 1; numAdds < 5; numAdds++)
      if (value < (((UInt32)1) << (numAdds * 5 + 6)))
        break;
    if (dest)
      dest[destPos] = (char)(kUtf8Limits[numAdds - 1] + (value >> (6 * numAdds)));
    destPos++;
    do
    {
      numAdds--;
      if (dest)
        dest[destPos] = (char)(0x80 + ((value >> (6 * numAdds)) & 0x3F));
      destPos++;
    }
    while (numAdds != 0);
  }
  *destLen = destPos;
  return False;
=======
}

#define _UTF8_RANGE(n) (((UInt32)1) << ((n) * 5 + 6))

#define _UTF8_HEAD(n, val) ((char)(_UTF8_START(n) + (val >> (6 * (n)))))
#define _UTF8_CHAR(n, val) ((char)(0x80 + (((val) >> (6 * (n))) & 0x3F)))

static size_t Utf16_To_Utf8_Calc(const wchar_t *src, const wchar_t *srcLim)
{
  size_t size = srcLim - src;
  for (;;)
  {
    if (src == srcLim)
      return size;
    
    UInt32 val = *src++;
   
    if (val < 0x80)
      continue;

    if (val < _UTF8_RANGE(1))
    {
      size++;
      continue;
    }

    if (val >= 0xD800 && val < 0xDC00 && src != srcLim)
    {
      UInt32 c2 = *src;
      if (c2 >= 0xDC00 && c2 < 0xE000)
      {
        src++;
        size += 2;
        continue;
      }
    }

    #ifdef _WCHART_IS_16BIT
    
    size += 2;
    
    #else

         if (val < _UTF8_RANGE(2)) size += 2;
    else if (val < _UTF8_RANGE(3)) size += 3;
    else if (val < _UTF8_RANGE(4)) size += 4;
    else if (val < _UTF8_RANGE(5)) size += 5;
    else                           size += 6;
    
    #endif
  }
}

static char *Utf16_To_Utf8(char *dest, const wchar_t *src, const wchar_t *srcLim)
{
  for (;;)
  {
    if (src == srcLim)
      return dest;
    
    UInt32 val = *src++;
    
    if (val < 0x80)
    {
      *dest++ = (char)val;
      continue;
    }

    if (val < _UTF8_RANGE(1))
    {
      dest[0] = _UTF8_HEAD(1, val);
      dest[1] = _UTF8_CHAR(0, val);
      dest += 2;
      continue;
    }

    if (val >= 0xD800 && val < 0xDC00 && src != srcLim)
    {
      UInt32 c2 = *src;
      if (c2 >= 0xDC00 && c2 < 0xE000)
      {
        src++;
        val = (((val - 0xD800) << 10) | (c2 - 0xDC00)) + 0x10000;
        dest[0] = _UTF8_HEAD(3, val);
        dest[1] = _UTF8_CHAR(2, val);
        dest[2] = _UTF8_CHAR(1, val);
        dest[3] = _UTF8_CHAR(0, val);
        dest += 4;
        continue;
      }
    }
    
    #ifndef _WCHART_IS_16BIT
    if (val < _UTF8_RANGE(2))
    #endif
    {
      dest[0] = _UTF8_HEAD(2, val);
      dest[1] = _UTF8_CHAR(1, val);
      dest[2] = _UTF8_CHAR(0, val);
      dest += 3;
      continue;
    }
    
    #ifndef _WCHART_IS_16BIT

    UInt32 b;
    unsigned numBits;
         if (val < _UTF8_RANGE(3)) { numBits = 6 * 3; b = _UTF8_HEAD(3, val); }
    else if (val < _UTF8_RANGE(4)) { numBits = 6 * 4; b = _UTF8_HEAD(4, val); }
    else if (val < _UTF8_RANGE(5)) { numBits = 6 * 5; b = _UTF8_HEAD(5, val); }
    else                           { numBits = 6 * 6; b = _UTF8_START(6); }
    
    *dest++ = (Byte)b;
    
    do
    {
      numBits -= 6;
      *dest++ = (char)(0x80 + ((val >> numBits) & 0x3F));
    }
    while (numBits != 0);

    #endif
  }
>>>>>>> upstream/master
}

bool ConvertUTF8ToUnicode(const AString &src, UString &dest)
{
  dest.Empty();
  size_t destLen = 0;
<<<<<<< HEAD
  Utf8_To_Utf16(NULL, &destLen, src, src.Length());
  wchar_t *p = dest.GetBuffer((int)destLen);
  Bool res = Utf8_To_Utf16(p, &destLen, src, src.Length());
  p[destLen] = 0;
  dest.ReleaseBuffer();
  return res ? true : false;
}

bool ConvertUnicodeToUTF8(const UString &src, AString &dest)
{
  dest.Empty();
  size_t destLen = 0;
  Utf16_To_Utf8(NULL, &destLen, src, src.Length());
  char *p = dest.GetBuffer((int)destLen);
  Bool res = Utf16_To_Utf8(p, &destLen, src, src.Length());
  p[destLen] = 0;
  dest.ReleaseBuffer();
  return res ? true : false;
=======
  Utf8_To_Utf16(NULL, &destLen, src, src.Ptr(src.Len()));
  bool res = Utf8_To_Utf16(dest.GetBuf((unsigned)destLen), &destLen, src, src.Ptr(src.Len()));
  dest.ReleaseBuf_SetEnd((unsigned)destLen);
  return res;
}

void ConvertUnicodeToUTF8(const UString &src, AString &dest)
{
  dest.Empty();
  size_t destLen = Utf16_To_Utf8_Calc(src, src.Ptr(src.Len()));
  Utf16_To_Utf8(dest.GetBuf((unsigned)destLen), src, src.Ptr(src.Len()));
  dest.ReleaseBuf_SetEnd((unsigned)destLen);
>>>>>>> upstream/master
}
