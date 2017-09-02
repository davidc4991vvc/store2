// HandlerOut.cpp

#include "StdAfx.h"

#ifndef _7ZIP_ST
#include "../../../Windows/System.h"
#endif

#include "../Common/ParseProperties.h"

#include "HandlerOut.h"

using namespace NWindows;

namespace NArchive {

static void SetMethodProp32(COneMethodInfo &m, PROPID propID, UInt32 value)
{
  if (m.FindProp(propID) < 0)
    m.AddProp32(propID, value);
}

void CMultiMethodProps::SetGlobalLevelAndThreads(COneMethodInfo &oneMethodInfo
    #ifndef _7ZIP_ST
    , UInt32 numThreads
    #endif
    )
{
  UInt32 level = _level;
<<<<<<< HEAD
  if (level != (UInt32)(UInt32)-1)
    SetMethodProp32(oneMethodInfo, NCoderPropID::kLevel, (UInt32)level);
=======
  if (level != (UInt32)(Int32)-1)
    SetMethodProp32(oneMethodInfo, NCoderPropID::kLevel, (UInt32)level);
  
>>>>>>> upstream/master
  #ifndef _7ZIP_ST
  SetMethodProp32(oneMethodInfo, NCoderPropID::kNumThreads, numThreads);
  #endif
}

void CMultiMethodProps::Init()
{
  #ifndef _7ZIP_ST
  _numProcessors = _numThreads = NSystem::GetNumberOfProcessors();
  #endif
  
<<<<<<< HEAD
  _level = (UInt32)(UInt32)-1;
=======
  _level = (UInt32)(Int32)-1;
  _analysisLevel = -1;

>>>>>>> upstream/master
  _autoFilter = true;
  _crcSize = 4;
  _filterMethod.Clear();
  _methods.Clear();
}

HRESULT CMultiMethodProps::SetProperty(const wchar_t *nameSpec, const PROPVARIANT &value)
{
  UString name = nameSpec;
<<<<<<< HEAD
  name.MakeUpper();
  if (name.IsEmpty())
    return E_INVALIDARG;
  
  if (name[0] == 'X')
=======
  name.MakeLower_Ascii();
  if (name.IsEmpty())
    return E_INVALIDARG;
  
  if (name[0] == 'x')
>>>>>>> upstream/master
  {
    name.Delete(0);
    _level = 9;
    return ParsePropToUInt32(name, value, _level);
  }
<<<<<<< HEAD
  
  if (name == L"CRC")
=======

  if (name.IsPrefixedBy_Ascii_NoCase("yx"))
  {
    name.Delete(0, 2);
    UInt32 v = 9;
    RINOK(ParsePropToUInt32(name, value, v));
    _analysisLevel = (int)v;
    return S_OK;
  }
  
  if (name.IsEqualTo("crc"))
>>>>>>> upstream/master
  {
    name.Delete(0, 3);
    _crcSize = 4;
    return ParsePropToUInt32(name, value, _crcSize);
  }
  
  UInt32 number;
<<<<<<< HEAD
  int index = ParseStringToUInt32(name, number);
  UString realName = name.Mid(index);
  if (index == 0)
  {
    if (name.Left(2).CompareNoCase(L"MT") == 0)
    {
      #ifndef _7ZIP_ST
      RINOK(ParseMtProp(name.Mid(2), value, _numProcessors, _numThreads));
      #endif
      return S_OK;
    }
    if (name.CompareNoCase(L"F") == 0)
=======
  unsigned index = ParseStringToUInt32(name, number);
  UString realName = name.Ptr(index);
  if (index == 0)
  {
    if (name.IsPrefixedBy_Ascii_NoCase("mt"))
    {
      #ifndef _7ZIP_ST
      RINOK(ParseMtProp(name.Ptr(2), value, _numProcessors, _numThreads));
      #endif
      
      return S_OK;
    }
    if (name.IsEqualTo("f"))
>>>>>>> upstream/master
    {
      HRESULT res = PROPVARIANT_to_bool(value, _autoFilter);
      if (res == S_OK)
        return res;
      if (value.vt != VT_BSTR)
        return E_INVALIDARG;
<<<<<<< HEAD
      return _filterMethod.ParseMethodFromPROPVARIANT(L"", value);
=======
      return _filterMethod.ParseMethodFromPROPVARIANT(UString(), value);
>>>>>>> upstream/master
    }
    number = 0;
  }
  if (number > 64)
    return E_FAIL;
  for (int j = _methods.Size(); j <= (int)number; j++)
    _methods.Add(COneMethodInfo());
  return _methods[number].ParseMethodFromPROPVARIANT(realName, value);
}

void CSingleMethodProps::Init()
{
  Clear();
<<<<<<< HEAD
  #ifndef _7ZIP_ST
  _numProcessors = _numThreads = NWindows::NSystem::GetNumberOfProcessors();
  AddNumThreadsProp(_numThreads);
  #endif
  _level = (UInt32)(UInt32)-1;
}

HRESULT CSingleMethodProps::SetProperties(const wchar_t **names, const PROPVARIANT *values, Int32 numProps)
{
  Init();
  for (int i = 0; i < numProps; i++)
  {
    UString name = names[i];
    name.MakeUpper();
    if (name.IsEmpty())
      return E_INVALIDARG;
    const PROPVARIANT &value = values[i];
    if (name[0] == L'X')
    {
      UInt32 a = 9;
      RINOK(ParsePropToUInt32(name.Mid(1), value, a));
      _level = a;
      AddLevelProp(a);
    }
    else if (name.Left(2).CompareNoCase(L"MT") == 0)
    {
      #ifndef _7ZIP_ST
      RINOK(ParseMtProp(name.Mid(2), value, _numProcessors, _numThreads));
      AddNumThreadsProp(_numThreads);
      #endif
    }
    else
      return ParseParamsFromPROPVARIANT(name, value);
=======
  _level = (UInt32)(Int32)-1;
  
  #ifndef _7ZIP_ST
  _numProcessors = _numThreads = NWindows::NSystem::GetNumberOfProcessors();
  AddProp_NumThreads(_numThreads);
  #endif
}

HRESULT CSingleMethodProps::SetProperties(const wchar_t * const *names, const PROPVARIANT *values, UInt32 numProps)
{
  Init();
  for (UInt32 i = 0; i < numProps; i++)
  {
    UString name = names[i];
    name.MakeLower_Ascii();
    if (name.IsEmpty())
      return E_INVALIDARG;
    const PROPVARIANT &value = values[i];
    if (name[0] == L'x')
    {
      UInt32 a = 9;
      RINOK(ParsePropToUInt32(name.Ptr(1), value, a));
      _level = a;
      AddProp_Level(a);
    }
    else if (name.IsPrefixedBy_Ascii_NoCase("mt"))
    {
      #ifndef _7ZIP_ST
      RINOK(ParseMtProp(name.Ptr(2), value, _numProcessors, _numThreads));
      AddProp_NumThreads(_numThreads);
      #endif
    }
    else
    {
      RINOK(ParseMethodFromPROPVARIANT(names[i], value));
    }
>>>>>>> upstream/master
  }
  return S_OK;
}

}
