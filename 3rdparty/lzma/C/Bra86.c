/* Bra86.c -- Converter for x86 code (BCJ)
<<<<<<< HEAD
2008-10-04 : Igor Pavlov : Public domain */

#include "Bra.h"

#define Test86MSByte(b) ((b) == 0 || (b) == 0xFF)

const Byte kMaskToAllowedStatus[8] = {1, 1, 1, 0, 1, 0, 0, 0};
const Byte kMaskToBitNumber[8] = {0, 1, 2, 2, 3, 3, 3, 3};

SizeT x86_Convert(Byte *data, SizeT size, UInt32 ip, UInt32 *state, int encoding)
{
  SizeT bufferPos = 0, prevPosT;
  UInt32 prevMask = *state & 0x7;
  if (size < 5)
    return 0;
  ip += 5;
  prevPosT = (SizeT)0 - 1;

  for (;;)
  {
    Byte *p = data + bufferPos;
    Byte *limit = data + size - 4;
    for (; p < limit; p++)
      if ((*p & 0xFE) == 0xE8)
        break;
    bufferPos = (SizeT)(p - data);
    if (p >= limit)
      break;
    prevPosT = bufferPos - prevPosT;
    if (prevPosT > 3)
      prevMask = 0;
    else
    {
      prevMask = (prevMask << ((int)prevPosT - 1)) & 0x7;
      if (prevMask != 0)
      {
        Byte b = p[4 - kMaskToBitNumber[prevMask]];
        if (!kMaskToAllowedStatus[prevMask] || Test86MSByte(b))
        {
          prevPosT = bufferPos;
          prevMask = ((prevMask << 1) & 0x7) | 1;
          bufferPos++;
=======
2013-11-12 : Igor Pavlov : Public domain */

#include "Precomp.h"

#include "Bra.h"

#define Test86MSByte(b) ((((b) + 1) & 0xFE) == 0)

SizeT x86_Convert(Byte *data, SizeT size, UInt32 ip, UInt32 *state, int encoding)
{
  SizeT pos = 0;
  UInt32 mask = *state & 7;
  if (size < 5)
    return 0;
  size -= 4;
  ip += 5;

  for (;;)
  {
    Byte *p = data + pos;
    const Byte *limit = data + size;
    for (; p < limit; p++)
      if ((*p & 0xFE) == 0xE8)
        break;

    {
      SizeT d = (SizeT)(p - data - pos);
      pos = (SizeT)(p - data);
      if (p >= limit)
      {
        *state = (d > 2 ? 0 : mask >> (unsigned)d);
        return pos;
      }
      if (d > 2)
        mask = 0;
      else
      {
        mask >>= (unsigned)d;
        if (mask != 0 && (mask > 4 || mask == 3 || Test86MSByte(p[(mask >> 1) + 1])))
        {
          mask = (mask >> 1) | 4;
          pos++;
>>>>>>> upstream/master
          continue;
        }
      }
    }
<<<<<<< HEAD
    prevPosT = bufferPos;

    if (Test86MSByte(p[4]))
    {
      UInt32 src = ((UInt32)p[4] << 24) | ((UInt32)p[3] << 16) | ((UInt32)p[2] << 8) | ((UInt32)p[1]);
      UInt32 dest;
      for (;;)
      {
        Byte b;
        int index;
        if (encoding)
          dest = (ip + (UInt32)bufferPos) + src;
        else
          dest = src - (ip + (UInt32)bufferPos);
        if (prevMask == 0)
          break;
        index = kMaskToBitNumber[prevMask] * 8;
        b = (Byte)(dest >> (24 - index));
        if (!Test86MSByte(b))
          break;
        src = dest ^ ((1 << (32 - index)) - 1);
      }
      p[4] = (Byte)(~(((dest >> 24) & 1) - 1));
      p[3] = (Byte)(dest >> 16);
      p[2] = (Byte)(dest >> 8);
      p[1] = (Byte)dest;
      bufferPos += 5;
    }
    else
    {
      prevMask = ((prevMask << 1) & 0x7) | 1;
      bufferPos++;
    }
  }
  prevPosT = bufferPos - prevPosT;
  *state = ((prevPosT > 3) ? 0 : ((prevMask << ((int)prevPosT - 1)) & 0x7));
  return bufferPos;
=======

    if (Test86MSByte(p[4]))
    {
      UInt32 v = ((UInt32)p[4] << 24) | ((UInt32)p[3] << 16) | ((UInt32)p[2] << 8) | ((UInt32)p[1]);
      UInt32 cur = ip + (UInt32)pos;
      pos += 5;
      if (encoding)
        v += cur;
      else
        v -= cur;
      if (mask != 0)
      {
        unsigned sh = (mask & 6) << 2;
        if (Test86MSByte((Byte)(v >> sh)))
        {
          v ^= (((UInt32)0x100 << sh) - 1);
          if (encoding)
            v += cur;
          else
            v -= cur;
        }
        mask = 0;
      }
      p[1] = (Byte)v;
      p[2] = (Byte)(v >> 8);
      p[3] = (Byte)(v >> 16);
      p[4] = (Byte)(0 - ((v >> 24) & 1));
    }
    else
    {
      mask = (mask >> 1) | 4;
      pos++;
    }
  }
>>>>>>> upstream/master
}
