// ExtractingFilePath.cpp

#include "StdAfx.h"

<<<<<<< HEAD
#include "../../../../C/Types.h"

#include "Common/Wildcard.h"

#include "ExtractingFilePath.h"

static UString ReplaceIncorrectChars(const UString &s)
{
  #ifdef _WIN32
  UString res;
  for (int i = 0; i < s.Length(); i++)
  {
    wchar_t c = s[i];
    if (c < 0x20 || c == '*' || c == '?' || c == '<' || c == '>'  || c == '|' || c == ':' || c == '"')
      c = '_';
    res += c;
  }
  res.TrimRight();
  while (!res.IsEmpty() && res.Back() == '.')
    res.DeleteBack();
  return res;
  #else
  return s;
=======
#include "../../../Common/Wildcard.h"

#include "../../../Windows/FileName.h"

#include "ExtractingFilePath.h"

static void ReplaceIncorrectChars(UString &s)
{
  {
    for (unsigned i = 0; i < s.Len(); i++)
    {
      wchar_t c = s[i];
      if (
          #ifdef _WIN32
          c == ':' || c == '*' || c == '?' || c < 0x20 || c == '<' || c == '>' || c == '|' || c == '"'
          || c == '/'
          // || c == 0x202E // RLO
          ||
          #endif
          c == WCHAR_PATH_SEPARATOR)
        s.ReplaceOneCharAtPos(i, '_');
    }
  }
  
  #ifdef _WIN32
  {
    for (unsigned i = s.Len(); i != 0;)
    {
      wchar_t c = s[--i];
      if (c != '.' && c != ' ')
        break;
      s.ReplaceOneCharAtPos(i, '_');
    }
  }
>>>>>>> upstream/master
  #endif
}

#ifdef _WIN32
<<<<<<< HEAD
static const wchar_t *g_ReservedNames[] =
{
  L"CON", L"PRN", L"AUX", L"NUL"
};

static bool CheckTail(const UString &name, int len)
{
  int dotPos = name.Find(L'.');
  if (dotPos < 0)
    dotPos = name.Length();
  UString s = name.Left(dotPos);
  s.TrimRight();
  return (s.Length() != len);
}

static bool CheckNameNum(const UString &name, const wchar_t *reservedName)
{
  int len = MyStringLen(reservedName);
  if (name.Length() <= len)
    return true;
  if (name.Left(len).CompareNoCase(reservedName) != 0)
    return true;
  wchar_t c = name[len];
  if (c < L'0' || c > L'9')
    return true;
  return CheckTail(name, len + 1);
}

static bool IsSupportedName(const UString &name)
{
  for (int i = 0; i < sizeof(g_ReservedNames) / sizeof(g_ReservedNames[0]); i++)
  {
    const wchar_t *reservedName = g_ReservedNames[i];
    int len = MyStringLen(reservedName);
    if (name.Length() < len)
      continue;
    if (name.Left(len).CompareNoCase(reservedName) != 0)
      continue;
    if (!CheckTail(name, len))
      return false;
  }
  if (!CheckNameNum(name, L"COM"))
    return false;
  return CheckNameNum(name, L"LPT");
}
#endif

static UString GetCorrectFileName(const UString &path)
{
  if (path == L".." || path == L".")
    return UString();
  return ReplaceIncorrectChars(path);
}

void MakeCorrectPath(UStringVector &pathParts)
{
  for (int i = 0; i < pathParts.Size();)
  {
    UString &s = pathParts[i];
    s = GetCorrectFileName(s);
    if (s.IsEmpty())
      pathParts.Delete(i);
    else
    {
      #ifdef _WIN32
      if (!IsSupportedName(s))
        s = (UString)L"_" + s;
      #endif
      i++;
    }
  }
}

UString MakePathNameFromParts(const UStringVector &parts)
{
  UString result;
  for (int i = 0; i < parts.Size(); i++)
  {
    if (i != 0)
      result += WCHAR_PATH_SEPARATOR;
    result += parts[i];
  }
  return result;
}

UString GetCorrectFsPath(const UString &path)
{
  UString res = GetCorrectFileName(path);
  #ifdef _WIN32
  if (!IsSupportedName(res))
    res = (UString)L"_" + res;
  #endif
  return res;
}
  
UString GetCorrectFullFsPath(const UString &path)
{
  UStringVector parts;
  SplitPathToParts(path, parts);
  for (int i = 0; i < parts.Size(); i++)
  {
    UString &s = parts[i];
    #ifdef _WIN32
    while (!s.IsEmpty() && s.Back() == '.')
      s.DeleteBack();
    if (!IsSupportedName(s))
      s = (UString)L"_" + s;
    #endif
  }
  return MakePathNameFromParts(parts);
=======

/* WinXP-64 doesn't support ':', '\\' and '/' symbols in name of alt stream.
   But colon in postfix ":$DATA" is allowed.
   WIN32 functions don't allow empty alt stream name "name:" */

void Correct_AltStream_Name(UString &s)
{
  unsigned len = s.Len();
  const unsigned kPostfixSize = 6;
  if (s.Len() >= kPostfixSize
      && StringsAreEqualNoCase_Ascii(s.RightPtr(kPostfixSize), ":$DATA"))
    len -= kPostfixSize;
  for (unsigned i = 0; i < len; i++)
  {
    wchar_t c = s[i];
    if (c == ':' || c == '\\' || c == '/'
        || c == 0x202E // RLO
        )
      s.ReplaceOneCharAtPos(i, '_');
  }
  if (s.IsEmpty())
    s = L'_';
}

static const unsigned g_ReservedWithNum_Index = 4;

static const char * const g_ReservedNames[] =
{
  "CON", "PRN", "AUX", "NUL",
  "COM", "LPT"
};

static bool IsSupportedName(const UString &name)
{
  for (unsigned i = 0; i < ARRAY_SIZE(g_ReservedNames); i++)
  {
    const char *reservedName = g_ReservedNames[i];
    unsigned len = MyStringLen(reservedName);
    if (name.Len() < len)
      continue;
    if (!name.IsPrefixedBy_Ascii_NoCase(reservedName))
      continue;
    if (i >= g_ReservedWithNum_Index)
    {
      wchar_t c = name[len];
      if (c < L'0' || c > L'9')
        continue;
      len++;
    }
    for (;;)
    {
      wchar_t c = name[len++];
      if (c == 0 || c == '.')
        return false;
      if (c != ' ')
        break;
    }
  }
  return true;
}

static void CorrectUnsupportedName(UString &name)
{
  if (!IsSupportedName(name))
    name.InsertAtFront(L'_');
}

#endif

static void Correct_PathPart(UString &s)
{
  // "." and ".."
  if (s[0] == '.' && (s[1] == 0 || s[1] == '.' && s[2] == 0))
    s.Empty();
  #ifdef _WIN32
  else
    ReplaceIncorrectChars(s);
  #endif
}

// static const wchar_t *k_EmptyReplaceName = L"[]";
static const wchar_t k_EmptyReplaceName = L'_';

UString Get_Correct_FsFile_Name(const UString &name)
{
  UString res = name;
  Correct_PathPart(res);
  
  #ifdef _WIN32
  CorrectUnsupportedName(res);
  #endif
  
  if (res.IsEmpty())
    res = k_EmptyReplaceName;
  return res;
}


void Correct_FsPath(bool absIsAllowed, UStringVector &parts, bool isDir)
{
  unsigned i = 0;

  if (absIsAllowed)
  {
    #if defined(_WIN32) && !defined(UNDER_CE)
    bool isDrive = false;
    #endif
    if (parts[0].IsEmpty())
    {
      i = 1;
      #if defined(_WIN32) && !defined(UNDER_CE)
      if (parts.Size() > 1 && parts[1].IsEmpty())
      {
        i = 2;
        if (parts.Size() > 2 && parts[2] == L"?")
        {
          i = 3;
          if (parts.Size() > 3  && NWindows::NFile::NName::IsDrivePath2(parts[3]))
          {
            isDrive = true;
            i = 4;
          }
        }
      }
      #endif
    }
    #if defined(_WIN32) && !defined(UNDER_CE)
    else if (NWindows::NFile::NName::IsDrivePath2(parts[0]))
    {
      isDrive = true;
      i = 1;
    }

    if (isDrive)
    {
      // we convert "c:name" to "c:\name", if absIsAllowed path.
      const UString &ds = parts[i - 1];
      if (ds.Len() != 2)
      {
        UString s = ds.Ptr(2);
        parts.Insert(i, s);
      }
    }
    #endif
  }

  for (; i < parts.Size();)
  {
    UString &s = parts[i];

    Correct_PathPart(s);

    if (s.IsEmpty())
    {
      if (isDir || i != parts.Size() - 1)
      {
        parts.Delete(i);
        continue;
      }
      s = k_EmptyReplaceName;
    }
    else
    {
      #ifdef _WIN32
      CorrectUnsupportedName(s);
      #endif
    }
    
    i++;
  }

  if (!isDir)
  {
    if (parts.IsEmpty())
      parts.Add(k_EmptyReplaceName);
    else
    {
      UString &s = parts.Back();
      if (s.IsEmpty())
        s = k_EmptyReplaceName;
    }
  }
}

UString MakePathFromParts(const UStringVector &parts)
{
  UString s;
  FOR_VECTOR (i, parts)
  {
    if (i != 0)
      s.Add_PathSepar();
    s += parts[i];
  }
  return s;
>>>>>>> upstream/master
}
