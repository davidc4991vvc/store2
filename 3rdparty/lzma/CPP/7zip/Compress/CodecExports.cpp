// CodecExports.cpp

#include "StdAfx.h"

<<<<<<< HEAD
#include "../../Common/ComTry.h"

#include "../../Windows/PropVariant.h"
=======
#include "../../../C/CpuArch.h"

#include "../../Common/ComTry.h"
#include "../../Common/MyCom.h"

#include "../../Windows/Defs.h"
>>>>>>> upstream/master

#include "../ICoder.h"

#include "../Common/RegisterCodec.h"

<<<<<<< HEAD
extern unsigned int g_NumCodecs;
extern const CCodecInfo *g_Codecs[];

static const UInt16 kDecodeId = 0x2790;

DEFINE_GUID(CLSID_CCodec,
0x23170F69, 0x40C1, kDecodeId, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);

static inline HRESULT SetPropString(const char *s, unsigned int size, PROPVARIANT *value)
{
  if ((value->bstrVal = ::SysAllocStringByteLen(s, size)) != 0)
    value->vt = VT_BSTR;
  return S_OK;
}

static inline HRESULT SetPropGUID(const GUID &guid, PROPVARIANT *value)
{
  return SetPropString((const char *)&guid, sizeof(GUID), value);
}

static HRESULT SetClassID(CMethodId id, bool encode, PROPVARIANT *value)
{
  GUID clsId = CLSID_CCodec;
  for (int i = 0; i < sizeof(id); i++, id >>= 8)
    clsId.Data4[i] = (Byte)(id & 0xFF);
  if (encode)
    clsId.Data3++;
  return SetPropGUID(clsId, value);
}

static HRESULT FindCodecClassId(const GUID *clsID, UInt32 isCoder2, bool isFilter, bool &encode, int &index)
{
  index = -1;
  if (clsID->Data1 != CLSID_CCodec.Data1 ||
      clsID->Data2 != CLSID_CCodec.Data2 ||
      (clsID->Data3 & ~1) != kDecodeId)
    return S_OK;
  encode = (clsID->Data3 != kDecodeId);
  UInt64 id = 0;
  for (int j = 0; j < 8; j++)
    id |= ((UInt64)clsID->Data4[j]) << (8 * j);
  for (unsigned i = 0; i < g_NumCodecs; i++)
  {
    const CCodecInfo &codec = *g_Codecs[i];
    if (id != codec.Id || encode && !codec.CreateEncoder || !encode && !codec.CreateDecoder)
      continue;
    if (!isFilter && codec.IsFilter || isFilter && !codec.IsFilter ||
        codec.NumInStreams != 1 && !isCoder2 || codec.NumInStreams == 1 && isCoder2)
      return E_NOINTERFACE;
    index = i;
    return S_OK;
  }
  return S_OK;
}

STDAPI CreateCoder2(bool encode, UInt32 index, const GUID *iid, void **outObject)
{
  COM_TRY_BEGIN
  *outObject = 0;
  bool isCoder = (*iid == IID_ICompressCoder) != 0;
  bool isCoder2 = (*iid == IID_ICompressCoder2) != 0;
  bool isFilter = (*iid == IID_ICompressFilter) != 0;
  const CCodecInfo &codec = *g_Codecs[index];
  if (!isFilter && codec.IsFilter || isFilter && !codec.IsFilter ||
      codec.NumInStreams != 1 && !isCoder2 || codec.NumInStreams == 1 && isCoder2)
    return E_NOINTERFACE;
  if (encode)
  {
    if (!codec.CreateEncoder)
      return CLASS_E_CLASSNOTAVAILABLE;
    *outObject = codec.CreateEncoder();
  }
  else
  {
    if (!codec.CreateDecoder)
      return CLASS_E_CLASSNOTAVAILABLE;
    *outObject = codec.CreateDecoder();
  }
  if (isCoder)
    ((ICompressCoder *)*outObject)->AddRef();
  else if (isCoder2)
    ((ICompressCoder2 *)*outObject)->AddRef();
  else
    ((ICompressFilter *)*outObject)->AddRef();
  return S_OK;
  COM_TRY_END
}

STDAPI CreateCoder(const GUID *clsid, const GUID *iid, void **outObject)
{
  *outObject = 0;
  bool isCoder = (*iid == IID_ICompressCoder) != 0;
  bool isCoder2 = (*iid == IID_ICompressCoder2) != 0;
  bool isFilter = (*iid == IID_ICompressFilter) != 0;
  if (!isCoder && !isCoder2 && !isFilter)
    return E_NOINTERFACE;
=======
extern unsigned g_NumCodecs;
extern const CCodecInfo *g_Codecs[];

extern unsigned g_NumHashers;
extern const CHasherInfo *g_Hashers[];

static void SetPropFromAscii(const char *s, PROPVARIANT *prop) throw()
{
  UINT len = (UINT)strlen(s);
  BSTR dest = ::SysAllocStringLen(NULL, len);
  if (dest)
  {
    for (UINT i = 0; i <= len; i++)
      dest[i] = (Byte)s[i];
    prop->bstrVal = dest;
    prop->vt = VT_BSTR;
  }
}

static inline HRESULT SetPropGUID(const GUID &guid, PROPVARIANT *value) throw()
{
  if ((value->bstrVal = ::SysAllocStringByteLen((const char *)&guid, sizeof(guid))) != NULL)
    value->vt = VT_BSTR;
  return S_OK;
}

static HRESULT MethodToClassID(UInt16 typeId, CMethodId id, PROPVARIANT *value) throw()
{
  GUID clsId;
  clsId.Data1 = k_7zip_GUID_Data1;
  clsId.Data2 = k_7zip_GUID_Data2;
  clsId.Data3 = typeId;
  SetUi64(clsId.Data4, id);
  return SetPropGUID(clsId, value);
}

static HRESULT FindCodecClassId(const GUID *clsid, bool isCoder2, bool isFilter, bool &encode, int &index) throw()
{
  index = -1;
  if (clsid->Data1 != k_7zip_GUID_Data1 ||
      clsid->Data2 != k_7zip_GUID_Data2)
    return S_OK;
  
  encode = true;
  
       if (clsid->Data3 == k_7zip_GUID_Data3_Decoder) encode = false;
  else if (clsid->Data3 != k_7zip_GUID_Data3_Encoder) return S_OK;
  
  UInt64 id = GetUi64(clsid->Data4);
  
  for (unsigned i = 0; i < g_NumCodecs; i++)
  {
    const CCodecInfo &codec = *g_Codecs[i];
    
    if (id != codec.Id
        || (encode ? !codec.CreateEncoder : !codec.CreateDecoder)
        || (isFilter ? !codec.IsFilter : codec.IsFilter))
      continue;

    if (codec.NumStreams == 1 ? isCoder2 : !isCoder2)
      return E_NOINTERFACE;
    
    index = i;
    return S_OK;
  }
  
  return S_OK;
}

static HRESULT CreateCoderMain(unsigned index, bool encode, void **coder)
{
  COM_TRY_BEGIN
  
  const CCodecInfo &codec = *g_Codecs[index];
  
  void *c;
  if (encode)
    c = codec.CreateEncoder();
  else
    c = codec.CreateDecoder();
  
  if (c)
  {
    IUnknown *unk;
    if (codec.IsFilter)
      unk = (IUnknown *)(ICompressFilter *)c;
    else if (codec.NumStreams != 1)
      unk = (IUnknown *)(ICompressCoder2 *)c;
    else
      unk = (IUnknown *)(ICompressCoder *)c;
    unk->AddRef();
    *coder = c;
  }
  return S_OK;
  
  COM_TRY_END
}

static HRESULT CreateCoder2(bool encode, UInt32 index, const GUID *iid, void **outObject)
{
  *outObject = NULL;

  const CCodecInfo &codec = *g_Codecs[index];

  if (encode ? !codec.CreateEncoder : !codec.CreateDecoder)
    return CLASS_E_CLASSNOTAVAILABLE;

  if (codec.IsFilter)
  {
    if (*iid != IID_ICompressFilter) return E_NOINTERFACE;
  }
  else if (codec.NumStreams != 1)
  {
    if (*iid != IID_ICompressCoder2) return E_NOINTERFACE;
  }
  else
  {
    if (*iid != IID_ICompressCoder) return E_NOINTERFACE;
  }
  
  return CreateCoderMain(index, encode, outObject);
}

STDAPI CreateDecoder(UInt32 index, const GUID *iid, void **outObject)
{
  return CreateCoder2(false, index, iid, outObject);
}

STDAPI CreateEncoder(UInt32 index, const GUID *iid, void **outObject)
{
  return CreateCoder2(true, index, iid, outObject);
}

STDAPI CreateCoder(const GUID *clsid, const GUID *iid, void **outObject)
{
  *outObject = NULL;

  bool isFilter = false;
  bool isCoder2 = false;
  bool isCoder = (*iid == IID_ICompressCoder) != 0;
  if (!isCoder)
  {
    isFilter = (*iid == IID_ICompressFilter) != 0;
    if (!isFilter)
    {
      isCoder2 = (*iid == IID_ICompressCoder2) != 0;
      if (!isCoder2)
        return E_NOINTERFACE;
    }
  }
  
>>>>>>> upstream/master
  bool encode;
  int codecIndex;
  HRESULT res = FindCodecClassId(clsid, isCoder2, isFilter, encode, codecIndex);
  if (res != S_OK)
    return res;
  if (codecIndex < 0)
    return CLASS_E_CLASSNOTAVAILABLE;
<<<<<<< HEAD
  return CreateCoder2(encode, codecIndex, iid, outObject);
}

=======

  return CreateCoderMain(codecIndex, encode, outObject);
}
 
>>>>>>> upstream/master
STDAPI GetMethodProperty(UInt32 codecIndex, PROPID propID, PROPVARIANT *value)
{
  ::VariantClear((VARIANTARG *)value);
  const CCodecInfo &codec = *g_Codecs[codecIndex];
<<<<<<< HEAD
  switch(propID)
  {
    case NMethodPropID::kID:
    {
      value->uhVal.QuadPart = (UInt64)codec.Id;
      value->vt = VT_UI8;
      break;
    }
    case NMethodPropID::kName:
      if ((value->bstrVal = ::SysAllocString(codec.Name)) != 0)
        value->vt = VT_BSTR;
      break;
    case NMethodPropID::kDecoder:
      if (codec.CreateDecoder)
        return SetClassID(codec.Id, false, value);
      break;
    case NMethodPropID::kEncoder:
      if (codec.CreateEncoder)
        return SetClassID(codec.Id, true, value);
      break;
    case NMethodPropID::kInStreams:
    {
      if (codec.NumInStreams != 1)
      {
        value->vt = VT_UI4;
        value->ulVal = (ULONG)codec.NumInStreams;
      }
      break;
    }
=======
  switch (propID)
  {
    case NMethodPropID::kID:
      value->uhVal.QuadPart = (UInt64)codec.Id;
      value->vt = VT_UI8;
      break;
    case NMethodPropID::kName:
      SetPropFromAscii(codec.Name, value);
      break;
    case NMethodPropID::kDecoder:
      if (codec.CreateDecoder)
        return MethodToClassID(k_7zip_GUID_Data3_Decoder, codec.Id, value);
      break;
    case NMethodPropID::kEncoder:
      if (codec.CreateEncoder)
        return MethodToClassID(k_7zip_GUID_Data3_Encoder, codec.Id, value);
      break;
    case NMethodPropID::kDecoderIsAssigned:
        value->vt = VT_BOOL;
        value->boolVal = BoolToVARIANT_BOOL(codec.CreateDecoder != NULL);
      break;
    case NMethodPropID::kEncoderIsAssigned:
        value->vt = VT_BOOL;
        value->boolVal = BoolToVARIANT_BOOL(codec.CreateEncoder != NULL);
      break;
    case NMethodPropID::kPackStreams:
      if (codec.NumStreams != 1)
      {
        value->vt = VT_UI4;
        value->ulVal = (ULONG)codec.NumStreams;
      }
      break;
    /*
    case NMethodPropID::kIsFilter:
      // if (codec.IsFilter)
      {
        value->vt = VT_BOOL;
        value->boolVal = BoolToVARIANT_BOOL(codec.IsFilter);
      }
      break;
    */
    /*
    case NMethodPropID::kDecoderFlags:
      {
        value->vt = VT_UI4;
        value->ulVal = (ULONG)codec.DecoderFlags;
      }
      break;
    case NMethodPropID::kEncoderFlags:
      {
        value->vt = VT_UI4;
        value->ulVal = (ULONG)codec.EncoderFlags;
      }
      break;
    */
>>>>>>> upstream/master
  }
  return S_OK;
}

STDAPI GetNumberOfMethods(UINT32 *numCodecs)
{
  *numCodecs = g_NumCodecs;
  return S_OK;
}
<<<<<<< HEAD
=======


// ---------- Hashers ----------

static int FindHasherClassId(const GUID *clsid) throw()
{
  if (clsid->Data1 != k_7zip_GUID_Data1 ||
      clsid->Data2 != k_7zip_GUID_Data2 ||
      clsid->Data3 != k_7zip_GUID_Data3_Hasher)
    return -1;
  UInt64 id = GetUi64(clsid->Data4);
  for (unsigned i = 0; i < g_NumCodecs; i++)
    if (id == g_Hashers[i]->Id)
      return i;
  return -1;
}

static HRESULT CreateHasher2(UInt32 index, IHasher **hasher)
{
  COM_TRY_BEGIN
  *hasher = g_Hashers[index]->CreateHasher();
  if (*hasher)
    (*hasher)->AddRef();
  return S_OK;
  COM_TRY_END
}

STDAPI CreateHasher(const GUID *clsid, IHasher **outObject)
{
  COM_TRY_BEGIN
  *outObject = 0;
  int index = FindHasherClassId(clsid);
  if (index < 0)
    return CLASS_E_CLASSNOTAVAILABLE;
  return CreateHasher2(index, outObject);
  COM_TRY_END
}

STDAPI GetHasherProp(UInt32 codecIndex, PROPID propID, PROPVARIANT *value)
{
  ::VariantClear((VARIANTARG *)value);
  const CHasherInfo &codec = *g_Hashers[codecIndex];
  switch (propID)
  {
    case NMethodPropID::kID:
      value->uhVal.QuadPart = (UInt64)codec.Id;
      value->vt = VT_UI8;
      break;
    case NMethodPropID::kName:
      SetPropFromAscii(codec.Name, value);
      break;
    case NMethodPropID::kEncoder:
      if (codec.CreateHasher)
        return MethodToClassID(k_7zip_GUID_Data3_Hasher, codec.Id, value);
      break;
    case NMethodPropID::kDigestSize:
      value->ulVal = (ULONG)codec.DigestSize;
      value->vt = VT_UI4;
      break;
  }
  return S_OK;
}

class CHashers:
  public IHashers,
  public CMyUnknownImp
{
public:
  MY_UNKNOWN_IMP1(IHashers)

  STDMETHOD_(UInt32, GetNumHashers)();
  STDMETHOD(GetHasherProp)(UInt32 index, PROPID propID, PROPVARIANT *value);
  STDMETHOD(CreateHasher)(UInt32 index, IHasher **hasher);
};

STDAPI GetHashers(IHashers **hashers)
{
  COM_TRY_BEGIN
  *hashers = new CHashers;
  if (*hashers)
    (*hashers)->AddRef();
  return S_OK;
  COM_TRY_END
}

STDMETHODIMP_(UInt32) CHashers::GetNumHashers()
{
  return g_NumHashers;
}

STDMETHODIMP CHashers::GetHasherProp(UInt32 index, PROPID propID, PROPVARIANT *value)
{
  return ::GetHasherProp(index, propID, value);
}

STDMETHODIMP CHashers::CreateHasher(UInt32 index, IHasher **hasher)
{
  return ::CreateHasher2(index, hasher);
}
>>>>>>> upstream/master
