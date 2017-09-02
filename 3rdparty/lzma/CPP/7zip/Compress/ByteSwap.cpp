// ByteSwap.cpp

#include "StdAfx.h"

#include "../../Common/MyCom.h"

#include "../ICoder.h"

#include "../Common/RegisterCodec.h"

<<<<<<< HEAD
=======
namespace NCompress {
namespace NByteSwap {

>>>>>>> upstream/master
class CByteSwap2:
  public ICompressFilter,
  public CMyUnknownImp
{
public:
<<<<<<< HEAD
  MY_UNKNOWN_IMP
  STDMETHOD(Init)();
  STDMETHOD_(UInt32, Filter)(Byte *data, UInt32 size);
=======
  MY_UNKNOWN_IMP1(ICompressFilter);
  INTERFACE_ICompressFilter(;)
>>>>>>> upstream/master
};

class CByteSwap4:
  public ICompressFilter,
  public CMyUnknownImp
{
public:
<<<<<<< HEAD
  MY_UNKNOWN_IMP
  STDMETHOD(Init)();
  STDMETHOD_(UInt32, Filter)(Byte *data, UInt32 size);
=======
  MY_UNKNOWN_IMP1(ICompressFilter);
  INTERFACE_ICompressFilter(;)
>>>>>>> upstream/master
};

STDMETHODIMP CByteSwap2::Init() { return S_OK; }

STDMETHODIMP_(UInt32) CByteSwap2::Filter(Byte *data, UInt32 size)
{
  const UInt32 kStep = 2;
<<<<<<< HEAD
  UInt32 i;
  for (i = 0; i + kStep <= size; i += kStep)
  {
    Byte b = data[i];
    data[i] = data[i + 1];
    data[i + 1] = b;
  }
  return i;
=======
  if (size < kStep)
    return 0;
  size &= ~(kStep - 1);
  
  const Byte *end = data + (size_t)size;
  
  do
  {
    Byte b0 = data[0];
    data[0] = data[1];
    data[1] = b0;
    data += kStep;
  }
  while (data != end);

  return size;
>>>>>>> upstream/master
}

STDMETHODIMP CByteSwap4::Init() { return S_OK; }

STDMETHODIMP_(UInt32) CByteSwap4::Filter(Byte *data, UInt32 size)
{
  const UInt32 kStep = 4;
<<<<<<< HEAD
  UInt32 i;
  for (i = 0; i + kStep <= size; i += kStep)
  {
    Byte b0 = data[i];
    Byte b1 = data[i + 1];
    data[i] = data[i + 3];
    data[i + 1] = data[i + 2];
    data[i + 2] = b1;
    data[i + 3] = b0;
  }
  return i;
}

static void *CreateCodec2() { return (void *)(ICompressFilter *)(new CByteSwap2); }
static void *CreateCodec4() { return (void *)(ICompressFilter *)(new CByteSwap4); }

static CCodecInfo g_CodecsInfo[] =
{
  { CreateCodec2, CreateCodec2, 0x020302, L"Swap2", 1, true },
  { CreateCodec4, CreateCodec4, 0x020304, L"Swap4", 1, true }
};

REGISTER_CODECS(ByteSwap)
=======
  if (size < kStep)
    return 0;
  size &= ~(kStep - 1);
  
  const Byte *end = data + (size_t)size;
  
  do
  {
    Byte b0 = data[0];
    Byte b1 = data[1];
    data[0] = data[3];
    data[1] = data[2];
    data[2] = b1;
    data[3] = b0;
    data += kStep;
  }
  while (data != end);

  return size;
}

REGISTER_FILTER_CREATE(CreateFilter2, CByteSwap2())
REGISTER_FILTER_CREATE(CreateFilter4, CByteSwap4())

REGISTER_CODECS_VAR
{
  REGISTER_FILTER_ITEM(CreateFilter2, CreateFilter2, 0x20302, "Swap2"),
  REGISTER_FILTER_ITEM(CreateFilter4, CreateFilter4, 0x20304, "Swap4")
};

REGISTER_CODECS(ByteSwap)

}}
>>>>>>> upstream/master
