<<<<<<< HEAD
/* Bcj2.c -- Converter for x86 code (BCJ2)
2008-10-04 : Igor Pavlov : Public domain */

#include "Bcj2.h"

#ifdef _LZMA_PROB32
#define CProb UInt32
#else
#define CProb UInt16
#endif

#define IsJcc(b0, b1) ((b0) == 0x0F && ((b1) & 0xF0) == 0x80)
#define IsJ(b0, b1) ((b1 & 0xFE) == 0xE8 || IsJcc(b0, b1))

#define kNumTopBits 24
#define kTopValue ((UInt32)1 << kNumTopBits)

#define kNumBitModelTotalBits 11
#define kBitModelTotal (1 << kNumBitModelTotalBits)
#define kNumMoveBits 5

#define RC_READ_BYTE (*buffer++)
#define RC_TEST { if (buffer == bufferLim) return SZ_ERROR_DATA; }
#define RC_INIT2 code = 0; range = 0xFFFFFFFF; \
  { int i; for (i = 0; i < 5; i++) { RC_TEST; code = (code << 8) | RC_READ_BYTE; }}

#define NORMALIZE if (range < kTopValue) { RC_TEST; range <<= 8; code = (code << 8) | RC_READ_BYTE; }

#define IF_BIT_0(p) ttt = *(p); bound = (range >> kNumBitModelTotalBits) * ttt; if (code < bound)
#define UPDATE_0(p) range = bound; *(p) = (CProb)(ttt + ((kBitModelTotal - ttt) >> kNumMoveBits)); NORMALIZE;
#define UPDATE_1(p) range -= bound; code -= bound; *(p) = (CProb)(ttt - (ttt >> kNumMoveBits)); NORMALIZE;

int Bcj2_Decode(
    const Byte *buf0, SizeT size0,
    const Byte *buf1, SizeT size1,
    const Byte *buf2, SizeT size2,
    const Byte *buf3, SizeT size3,
    Byte *outBuf, SizeT outSize)
{
  CProb p[256 + 2];
  SizeT inPos = 0, outPos = 0;

  const Byte *buffer, *bufferLim;
  UInt32 range, code;
  Byte prevByte = 0;

  unsigned int i;
  for (i = 0; i < sizeof(p) / sizeof(p[0]); i++)
    p[i] = kBitModelTotal >> 1;

  buffer = buf3;
  bufferLim = buffer + size3;
  RC_INIT2

  if (outSize == 0)
    return SZ_OK;

  for (;;)
  {
    Byte b;
    CProb *prob;
    UInt32 bound;
    UInt32 ttt;

    SizeT limit = size0 - inPos;
    if (outSize - outPos < limit)
      limit = outSize - outPos;
    while (limit != 0)
    {
      Byte b = buf0[inPos];
      outBuf[outPos++] = b;
      if (IsJ(prevByte, b))
        break;
      inPos++;
      prevByte = b;
      limit--;
    }

    if (limit == 0 || outPos == outSize)
      break;

    b = buf0[inPos++];

    if (b == 0xE8)
      prob = p + prevByte;
    else if (b == 0xE9)
      prob = p + 256;
    else
      prob = p + 257;

    IF_BIT_0(prob)
    {
      UPDATE_0(prob)
      prevByte = b;
    }
    else
    {
      UInt32 dest;
      const Byte *v;
      UPDATE_1(prob)
      if (b == 0xE8)
      {
        v = buf1;
        if (size1 < 4)
          return SZ_ERROR_DATA;
        buf1 += 4;
        size1 -= 4;
      }
      else
      {
        v = buf2;
        if (size2 < 4)
          return SZ_ERROR_DATA;
        buf2 += 4;
        size2 -= 4;
      }
      dest = (((UInt32)v[0] << 24) | ((UInt32)v[1] << 16) |
          ((UInt32)v[2] << 8) | ((UInt32)v[3])) - ((UInt32)outPos + 4);
      outBuf[outPos++] = (Byte)dest;
      if (outPos == outSize)
        break;
      outBuf[outPos++] = (Byte)(dest >> 8);
      if (outPos == outSize)
        break;
      outBuf[outPos++] = (Byte)(dest >> 16);
      if (outPos == outSize)
        break;
      outBuf[outPos++] = prevByte = (Byte)(dest >> 24);
    }
  }
  return (outPos == outSize) ? SZ_OK : SZ_ERROR_DATA;
=======
/* Bcj2.c -- BCJ2 Decoder (Converter for x86 code)
2015-08-01 : Igor Pavlov : Public domain */

#include "Precomp.h"

#include "Bcj2.h"
#include "CpuArch.h"

#define CProb UInt16

#define kTopValue ((UInt32)1 << 24)
#define kNumModelBits 11
#define kBitModelTotal (1 << kNumModelBits)
#define kNumMoveBits 5

#define _IF_BIT_0 ttt = *prob; bound = (p->range >> kNumModelBits) * ttt; if (p->code < bound)
#define _UPDATE_0 p->range = bound; *prob = (CProb)(ttt + ((kBitModelTotal - ttt) >> kNumMoveBits));
#define _UPDATE_1 p->range -= bound; p->code -= bound; *prob = (CProb)(ttt - (ttt >> kNumMoveBits));

void Bcj2Dec_Init(CBcj2Dec *p)
{
  unsigned i;

  p->state = BCJ2_DEC_STATE_OK;
  p->ip = 0;
  p->temp[3] = 0;
  p->range = 0;
  p->code = 0;
  for (i = 0; i < sizeof(p->probs) / sizeof(p->probs[0]); i++)
    p->probs[i] = kBitModelTotal >> 1;
}

SRes Bcj2Dec_Decode(CBcj2Dec *p)
{
  if (p->range <= 5)
  {
    p->state = BCJ2_DEC_STATE_OK;
    for (; p->range != 5; p->range++)
    {
      if (p->range == 1 && p->code != 0)
        return SZ_ERROR_DATA;
      
      if (p->bufs[BCJ2_STREAM_RC] == p->lims[BCJ2_STREAM_RC])
      {
        p->state = BCJ2_STREAM_RC;
        return SZ_OK;
      }

      p->code = (p->code << 8) | *(p->bufs[BCJ2_STREAM_RC])++;
    }
    
    if (p->code == 0xFFFFFFFF)
      return SZ_ERROR_DATA;
    
    p->range = 0xFFFFFFFF;
  }
  else if (p->state >= BCJ2_DEC_STATE_ORIG_0)
  {
    while (p->state <= BCJ2_DEC_STATE_ORIG_3)
    {
      Byte *dest = p->dest;
      if (dest == p->destLim)
        return SZ_OK;
      *dest = p->temp[p->state++ - BCJ2_DEC_STATE_ORIG_0];
      p->dest = dest + 1;
    }
  }

  /*
  if (BCJ2_IS_32BIT_STREAM(p->state))
  {
    const Byte *cur = p->bufs[p->state];
    if (cur == p->lims[p->state])
      return SZ_OK;
    p->bufs[p->state] = cur + 4;
    
    {
      UInt32 val;
      Byte *dest;
      SizeT rem;
      
      p->ip += 4;
      val = GetBe32(cur) - p->ip;
      dest = p->dest;
      rem = p->destLim - dest;
      if (rem < 4)
      {
        SizeT i;
        SetUi32(p->temp, val);
        for (i = 0; i < rem; i++)
          dest[i] = p->temp[i];
        p->dest = dest + rem;
        p->state = BCJ2_DEC_STATE_ORIG_0 + (unsigned)rem;
        return SZ_OK;
      }
      SetUi32(dest, val);
      p->temp[3] = (Byte)(val >> 24);
      p->dest = dest + 4;
      p->state = BCJ2_DEC_STATE_OK;
    }
  }
  */

  for (;;)
  {
    if (BCJ2_IS_32BIT_STREAM(p->state))
      p->state = BCJ2_DEC_STATE_OK;
    else
    {
      if (p->range < kTopValue)
      {
        if (p->bufs[BCJ2_STREAM_RC] == p->lims[BCJ2_STREAM_RC])
        {
          p->state = BCJ2_STREAM_RC;
          return SZ_OK;
        }
        p->range <<= 8;
        p->code = (p->code << 8) | *(p->bufs[BCJ2_STREAM_RC])++;
      }

      {
        const Byte *src = p->bufs[BCJ2_STREAM_MAIN];
        const Byte *srcLim;
        Byte *dest;
        SizeT num = p->lims[BCJ2_STREAM_MAIN] - src;
        
        if (num == 0)
        {
          p->state = BCJ2_STREAM_MAIN;
          return SZ_OK;
        }
        
        dest = p->dest;
        if (num > (SizeT)(p->destLim - dest))
        {
          num = p->destLim - dest;
          if (num == 0)
          {
            p->state = BCJ2_DEC_STATE_ORIG;
            return SZ_OK;
          }
        }
       
        srcLim = src + num;

        if (p->temp[3] == 0x0F && (src[0] & 0xF0) == 0x80)
          *dest = src[0];
        else for (;;)
        {
          Byte b = *src;
          *dest = b;
          if (b != 0x0F)
          {
            if ((b & 0xFE) == 0xE8)
              break;
            dest++;
            if (++src != srcLim)
              continue;
            break;
          }
          dest++;
          if (++src == srcLim)
            break;
          if ((*src & 0xF0) != 0x80)
            continue;
          *dest = *src;
          break;
        }
        
        num = src - p->bufs[BCJ2_STREAM_MAIN];
        
        if (src == srcLim)
        {
          p->temp[3] = src[-1];
          p->bufs[BCJ2_STREAM_MAIN] = src;
          p->ip += (UInt32)num;
          p->dest += num;
          p->state =
            p->bufs[BCJ2_STREAM_MAIN] ==
            p->lims[BCJ2_STREAM_MAIN] ?
              (unsigned)BCJ2_STREAM_MAIN :
              (unsigned)BCJ2_DEC_STATE_ORIG;
          return SZ_OK;
        }
        
        {
          UInt32 bound, ttt;
          CProb *prob;
          Byte b = src[0];
          Byte prev = (Byte)(num == 0 ? p->temp[3] : src[-1]);
          
          p->temp[3] = b;
          p->bufs[BCJ2_STREAM_MAIN] = src + 1;
          num++;
          p->ip += (UInt32)num;
          p->dest += num;
          
          prob = p->probs + (unsigned)(b == 0xE8 ? 2 + (unsigned)prev : (b == 0xE9 ? 1 : 0));
          
          _IF_BIT_0
          {
            _UPDATE_0
            continue;
          }
          _UPDATE_1
            
        }
      }
    }

    {
      UInt32 val;
      unsigned cj = (p->temp[3] == 0xE8) ? BCJ2_STREAM_CALL : BCJ2_STREAM_JUMP;
      const Byte *cur = p->bufs[cj];
      Byte *dest;
      SizeT rem;
      
      if (cur == p->lims[cj])
      {
        p->state = cj;
        break;
      }
      
      val = GetBe32(cur);
      p->bufs[cj] = cur + 4;

      p->ip += 4;
      val -= p->ip;
      dest = p->dest;
      rem = p->destLim - dest;
      
      if (rem < 4)
      {
        SizeT i;
        SetUi32(p->temp, val);
        for (i = 0; i < rem; i++)
          dest[i] = p->temp[i];
        p->dest = dest + rem;
        p->state = BCJ2_DEC_STATE_ORIG_0 + (unsigned)rem;
        break;
      }
      
      SetUi32(dest, val);
      p->temp[3] = (Byte)(val >> 24);
      p->dest = dest + 4;
    }
  }

  if (p->range < kTopValue && p->bufs[BCJ2_STREAM_RC] != p->lims[BCJ2_STREAM_RC])
  {
    p->range <<= 8;
    p->code = (p->code << 8) | *(p->bufs[BCJ2_STREAM_RC])++;
  }

  return SZ_OK;
>>>>>>> upstream/master
}
