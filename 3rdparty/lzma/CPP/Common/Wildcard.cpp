// Common/Wildcard.cpp

#include "StdAfx.h"

<<<<<<< HEAD
#include "../../C/Types.h"

=======
>>>>>>> upstream/master
#include "Wildcard.h"

bool g_CaseSensitive =
  #ifdef _WIN32
    false;
  #else
    true;
  #endif

<<<<<<< HEAD
static const wchar_t kAnyCharsChar = L'*';
static const wchar_t kAnyCharChar = L'?';

#ifdef _WIN32
static const wchar_t kDirDelimiter1 = L'\\';
#endif
static const wchar_t kDirDelimiter2 = L'/';

static const UString kWildCardCharSet = L"?*";

static const UString kIllegalWildCardFileNameChars=
  L"\x1\x2\x3\x4\x5\x6\x7\x8\x9\xA\xB\xC\xD\xE\xF"
  L"\x10\x11\x12\x13\x14\x15\x16\x17\x18\x19\x1A\x1B\x1C\x1D\x1E\x1F"
  L"\"/:<>\\|";


static inline bool IsCharDirLimiter(wchar_t c)
{
  return (
    #ifdef _WIN32
    c == kDirDelimiter1 ||
    #endif
    c == kDirDelimiter2);
}

int CompareFileNames(const UString &s1, const UString &s2)
{
  if (g_CaseSensitive)
    return s1.Compare(s2);
  return s1.CompareNoCase(s2);
}
=======

bool IsPath1PrefixedByPath2(const wchar_t *s1, const wchar_t *s2)
{
  if (g_CaseSensitive)
    return IsString1PrefixedByString2(s1, s2);
  return IsString1PrefixedByString2_NoCase(s1, s2);
}

int CompareFileNames(const wchar_t *s1, const wchar_t *s2) STRING_UNICODE_THROW
{
  if (g_CaseSensitive)
    return wcscmp(s1, s2);
  return MyStringCompareNoCase(s1, s2);
}

#ifndef USE_UNICODE_FSTRING
int CompareFileNames(const char *s1, const char *s2)
{
  if (g_CaseSensitive)
    return wcscmp(fs2us(s1), fs2us(s2));
  return MyStringCompareNoCase(fs2us(s1), fs2us(s2));
}
#endif
>>>>>>> upstream/master

// -----------------------------------------
// this function compares name with mask
// ? - any char
// * - any char or empty

static bool EnhancedMaskTest(const wchar_t *mask, const wchar_t *name)
{
  for (;;)
  {
    wchar_t m = *mask;
    wchar_t c = *name;
    if (m == 0)
      return (c == 0);
<<<<<<< HEAD
    if (m == kAnyCharsChar)
=======
    if (m == '*')
>>>>>>> upstream/master
    {
      if (EnhancedMaskTest(mask + 1, name))
        return true;
      if (c == 0)
        return false;
    }
    else
    {
<<<<<<< HEAD
      if (m == kAnyCharChar)
=======
      if (m == '?')
>>>>>>> upstream/master
      {
        if (c == 0)
          return false;
      }
      else if (m != c)
        if (g_CaseSensitive || MyCharUpper(m) != MyCharUpper(c))
          return false;
      mask++;
    }
    name++;
  }
}

// --------------------------------------------------
// Splits path to strings

void SplitPathToParts(const UString &path, UStringVector &pathParts)
{
  pathParts.Clear();
<<<<<<< HEAD
  UString name;
  int len = path.Length();
  if (len == 0)
    return;
  for (int i = 0; i < len; i++)
  {
    wchar_t c = path[i];
    if (IsCharDirLimiter(c))
    {
      pathParts.Add(name);
      name.Empty();
    }
    else
      name += c;
  }
  pathParts.Add(name);
}

void SplitPathToParts(const UString &path, UString &dirPrefix, UString &name)
{
  int i;
  for (i = path.Length() - 1; i >= 0; i--)
    if (IsCharDirLimiter(path[i]))
      break;
  dirPrefix = path.Left(i + 1);
  name = path.Mid(i + 1);
=======
  unsigned len = path.Len();
  if (len == 0)
    return;
  UString name;
  unsigned prev = 0;
  for (unsigned i = 0; i < len; i++)
    if (IsPathSepar(path[i]))
    {
      name.SetFrom(path.Ptr(prev), i - prev);
      pathParts.Add(name);
      prev = i + 1;
    }
  name.SetFrom(path.Ptr(prev), len - prev);
  pathParts.Add(name);
}

void SplitPathToParts_2(const UString &path, UString &dirPrefix, UString &name)
{
  const wchar_t *start = path;
  const wchar_t *p = start + path.Len();
  for (; p != start; p--)
    if (IsPathSepar(*(p - 1)))
      break;
  dirPrefix.SetFrom(path, (unsigned)(p - start));
  name = p;
}

void SplitPathToParts_Smart(const UString &path, UString &dirPrefix, UString &name)
{
  const wchar_t *start = path;
  const wchar_t *p = start + path.Len();
  if (p != start)
  {
    if (IsPathSepar(*(p - 1)))
      p--;
    for (; p != start; p--)
      if (IsPathSepar(*(p - 1)))
        break;
  }
  dirPrefix.SetFrom(path, (unsigned)(p - start));
  name = p;
>>>>>>> upstream/master
}

UString ExtractDirPrefixFromPath(const UString &path)
{
<<<<<<< HEAD
  int i;
  for (i = path.Length() - 1; i >= 0; i--)
    if (IsCharDirLimiter(path[i]))
      break;
  return path.Left(i + 1);
=======
  const wchar_t *start = path;
  const wchar_t *p = start + path.Len();
  for (; p != start; p--)
    if (IsPathSepar(*(p - 1)))
      break;
  return path.Left((unsigned)(p - start));
>>>>>>> upstream/master
}

UString ExtractFileNameFromPath(const UString &path)
{
<<<<<<< HEAD
  int i;
  for (i = path.Length() - 1; i >= 0; i--)
    if (IsCharDirLimiter(path[i]))
      break;
  return path.Mid(i + 1);
}


bool CompareWildCardWithName(const UString &mask, const UString &name)
=======
  const wchar_t *start = path;
  const wchar_t *p = start + path.Len();
  for (; p != start; p--)
    if (IsPathSepar(*(p - 1)))
      break;
  return p;
}


bool DoesWildcardMatchName(const UString &mask, const UString &name)
>>>>>>> upstream/master
{
  return EnhancedMaskTest(mask, name);
}

<<<<<<< HEAD
bool DoesNameContainWildCard(const UString &path)
{
  return (path.FindOneOf(kWildCardCharSet) >= 0);
=======
bool DoesNameContainWildcard(const UString &path)
{
  for (unsigned i = 0; i < path.Len(); i++)
  {
    wchar_t c = path[i];
    if (c == '*' || c == '?')
      return true;
  }
  return false;
>>>>>>> upstream/master
}


// ----------------------------------------------------------'
// NWildcard

namespace NWildcard {

<<<<<<< HEAD

/*
=======
/*

>>>>>>> upstream/master
M = MaskParts.Size();
N = TestNameParts.Size();

                           File                          Dir
<<<<<<< HEAD
ForFile     req   M<=N  [N-M, N)                          -
         nonreq   M=N   [0, M)                            -
 
ForDir      req   M<N   [0, M) ... [N-M-1, N-1)  same as ForBoth-File
         nonreq         [0, M)                   same as ForBoth-File

ForBoth     req   m<=N  [0, M) ... [N-M, N)      same as ForBoth-File
         nonreq         [0, M)                   same as ForBoth-File

*/

=======
ForFile     rec   M<=N  [N-M, N)                          -
!ForDir  nonrec   M=N   [0, M)                            -
 
ForDir      rec   M<N   [0, M) ... [N-M-1, N-1)  same as ForBoth-File
!ForFile nonrec         [0, M)                   same as ForBoth-File

ForFile     rec   m<=N  [0, M) ... [N-M, N)      same as ForBoth-File
ForDir   nonrec         [0, M)                   same as ForBoth-File

*/

bool CItem::AreAllAllowed() const
{
  return ForFile && ForDir && WildcardMatching && PathParts.Size() == 1 && PathParts.Front() == L"*";
}

>>>>>>> upstream/master
bool CItem::CheckPath(const UStringVector &pathParts, bool isFile) const
{
  if (!isFile && !ForDir)
    return false;
<<<<<<< HEAD
=======

  /*
  if (PathParts.IsEmpty())
  {
    // PathParts.IsEmpty() means all items (universal wildcard)
    if (!isFile)
      return true;
    if (pathParts.Size() <= 1)
      return ForFile;
    return (ForDir || Recursive && ForFile);
  }
  */

>>>>>>> upstream/master
  int delta = (int)pathParts.Size() - (int)PathParts.Size();
  if (delta < 0)
    return false;
  int start = 0;
  int finish = 0;
<<<<<<< HEAD
  if (isFile)
  {
    if (!ForDir && !Recursive && delta !=0)
      return false;
    if (!ForFile && delta == 0)
      return false;
    if (!ForDir && Recursive)
      start = delta;
  }
=======
  
  if (isFile)
  {
    if (!ForDir)
    {
      if (Recursive)
        start = delta;
      else if (delta !=0)
        return false;
    }
    if (!ForFile && delta == 0)
      return false;
  }
  
>>>>>>> upstream/master
  if (Recursive)
  {
    finish = delta;
    if (isFile && !ForFile)
      finish = delta - 1;
  }
<<<<<<< HEAD
  for (int d = start; d <= finish; d++)
  {
    int i;
    for (i = 0; i < PathParts.Size(); i++)
      if (!CompareWildCardWithName(PathParts[i], pathParts[i + d]))
        break;
=======
  
  for (int d = start; d <= finish; d++)
  {
    unsigned i;
    for (i = 0; i < PathParts.Size(); i++)
    {
      if (WildcardMatching)
      {
        if (!DoesWildcardMatchName(PathParts[i], pathParts[i + d]))
          break;
      }
      else
      {
        if (CompareFileNames(PathParts[i], pathParts[i + d]) != 0)
          break;
      }
    }
>>>>>>> upstream/master
    if (i == PathParts.Size())
      return true;
  }
  return false;
}

<<<<<<< HEAD
int CCensorNode::FindSubNode(const UString &name) const
{
  for (int i = 0; i < SubNodes.Size(); i++)
=======
bool CCensorNode::AreAllAllowed() const
{
  if (!Name.IsEmpty() ||
      !SubNodes.IsEmpty() ||
      !ExcludeItems.IsEmpty() ||
      IncludeItems.Size() != 1)
    return false;
  return IncludeItems.Front().AreAllAllowed();
}

int CCensorNode::FindSubNode(const UString &name) const
{
  FOR_VECTOR (i, SubNodes)
>>>>>>> upstream/master
    if (CompareFileNames(SubNodes[i].Name, name) == 0)
      return i;
  return -1;
}

void CCensorNode::AddItemSimple(bool include, CItem &item)
{
  if (include)
    IncludeItems.Add(item);
  else
    ExcludeItems.Add(item);
}

<<<<<<< HEAD
void CCensorNode::AddItem(bool include, CItem &item)
{
  if (item.PathParts.Size() <= 1)
  {
=======
void CCensorNode::AddItem(bool include, CItem &item, int ignoreWildcardIndex)
{
  if (item.PathParts.Size() <= 1)
  {
    if (item.PathParts.Size() != 0 && item.WildcardMatching)
    {
      if (!DoesNameContainWildcard(item.PathParts.Front()))
        item.WildcardMatching = false;
    }
>>>>>>> upstream/master
    AddItemSimple(include, item);
    return;
  }
  const UString &front = item.PathParts.Front();
<<<<<<< HEAD
  if (DoesNameContainWildCard(front))
=======
  
  // WIN32 doesn't support wildcards in file names
  if (item.WildcardMatching
      && ignoreWildcardIndex != 0
      && DoesNameContainWildcard(front))
>>>>>>> upstream/master
  {
    AddItemSimple(include, item);
    return;
  }
  int index = FindSubNode(front);
  if (index < 0)
    index = SubNodes.Add(CCensorNode(front, this));
  item.PathParts.Delete(0);
<<<<<<< HEAD
  SubNodes[index].AddItem(include, item);
}

void CCensorNode::AddItem(bool include, const UString &path, bool recursive, bool forFile, bool forDir)
=======
  SubNodes[index].AddItem(include, item, ignoreWildcardIndex - 1);
}

void CCensorNode::AddItem(bool include, const UString &path, bool recursive, bool forFile, bool forDir, bool wildcardMatching)
>>>>>>> upstream/master
{
  CItem item;
  SplitPathToParts(path, item.PathParts);
  item.Recursive = recursive;
  item.ForFile = forFile;
  item.ForDir = forDir;
<<<<<<< HEAD
=======
  item.WildcardMatching = wildcardMatching;
>>>>>>> upstream/master
  AddItem(include, item);
}

bool CCensorNode::NeedCheckSubDirs() const
{
<<<<<<< HEAD
  for (int i = 0; i < IncludeItems.Size(); i++)
=======
  FOR_VECTOR (i, IncludeItems)
>>>>>>> upstream/master
  {
    const CItem &item = IncludeItems[i];
    if (item.Recursive || item.PathParts.Size() > 1)
      return true;
  }
  return false;
}

bool CCensorNode::AreThereIncludeItems() const
{
  if (IncludeItems.Size() > 0)
    return true;
<<<<<<< HEAD
  for (int i = 0; i < SubNodes.Size(); i++)
=======
  FOR_VECTOR (i, SubNodes)
>>>>>>> upstream/master
    if (SubNodes[i].AreThereIncludeItems())
      return true;
  return false;
}

bool CCensorNode::CheckPathCurrent(bool include, const UStringVector &pathParts, bool isFile) const
{
  const CObjectVector<CItem> &items = include ? IncludeItems : ExcludeItems;
<<<<<<< HEAD
  for (int i = 0; i < items.Size(); i++)
=======
  FOR_VECTOR (i, items)
>>>>>>> upstream/master
    if (items[i].CheckPath(pathParts, isFile))
      return true;
  return false;
}

<<<<<<< HEAD
bool CCensorNode::CheckPath(UStringVector &pathParts, bool isFile, bool &include) const
=======
bool CCensorNode::CheckPathVect(const UStringVector &pathParts, bool isFile, bool &include) const
>>>>>>> upstream/master
{
  if (CheckPathCurrent(false, pathParts, isFile))
  {
    include = false;
    return true;
  }
  include = true;
  bool finded = CheckPathCurrent(true, pathParts, isFile);
<<<<<<< HEAD
  if (pathParts.Size() == 1)
=======
  if (pathParts.Size() <= 1)
>>>>>>> upstream/master
    return finded;
  int index = FindSubNode(pathParts.Front());
  if (index >= 0)
  {
    UStringVector pathParts2 = pathParts;
    pathParts2.Delete(0);
<<<<<<< HEAD
    if (SubNodes[index].CheckPath(pathParts2, isFile, include))
=======
    if (SubNodes[index].CheckPathVect(pathParts2, isFile, include))
>>>>>>> upstream/master
      return true;
  }
  return finded;
}

<<<<<<< HEAD
bool CCensorNode::CheckPath(const UString &path, bool isFile, bool &include) const
{
  UStringVector pathParts;
  SplitPathToParts(path, pathParts);
  return CheckPath(pathParts, isFile, include);
}

bool CCensorNode::CheckPath(const UString &path, bool isFile) const
{
  bool include;
  if (CheckPath(path, isFile, include))
    return include;
  return false;
}
=======
/*
bool CCensorNode::CheckPath2(bool isAltStream, const UString &path, bool isFile, bool &include) const
{
  UStringVector pathParts;
  SplitPathToParts(path, pathParts);
  if (CheckPathVect(pathParts, isFile, include))
  {
    if (!include || !isAltStream)
      return true;
  }
  if (isAltStream && !pathParts.IsEmpty())
  {
    UString &back = pathParts.Back();
    int pos = back.Find(L':');
    if (pos > 0)
    {
      back.DeleteFrom(pos);
      return CheckPathVect(pathParts, isFile, include);
    }
  }
  return false;
}

bool CCensorNode::CheckPath(bool isAltStream, const UString &path, bool isFile) const
{
  bool include;
  if (CheckPath2(isAltStream, path, isFile, include))
    return include;
  return false;
}
*/
>>>>>>> upstream/master

bool CCensorNode::CheckPathToRoot(bool include, UStringVector &pathParts, bool isFile) const
{
  if (CheckPathCurrent(include, pathParts, isFile))
    return true;
  if (Parent == 0)
    return false;
  pathParts.Insert(0, Name);
  return Parent->CheckPathToRoot(include, pathParts, isFile);
}

/*
bool CCensorNode::CheckPathToRoot(bool include, const UString &path, bool isFile) const
{
  UStringVector pathParts;
  SplitPathToParts(path, pathParts);
  return CheckPathToRoot(include, pathParts, isFile);
}
*/

<<<<<<< HEAD
void CCensorNode::AddItem2(bool include, const UString &path, bool recursive)
=======
void CCensorNode::AddItem2(bool include, const UString &path, bool recursive, bool wildcardMatching)
>>>>>>> upstream/master
{
  if (path.IsEmpty())
    return;
  bool forFile = true;
  bool forFolder = true;
  UString path2 = path;
<<<<<<< HEAD
  if (IsCharDirLimiter(path.Back()))
=======
  if (IsPathSepar(path.Back()))
>>>>>>> upstream/master
  {
    path2.DeleteBack();
    forFile = false;
  }
<<<<<<< HEAD
  AddItem(include, path2, recursive, forFile, forFolder);
=======
  AddItem(include, path2, recursive, forFile, forFolder, wildcardMatching);
>>>>>>> upstream/master
}

void CCensorNode::ExtendExclude(const CCensorNode &fromNodes)
{
  ExcludeItems += fromNodes.ExcludeItems;
<<<<<<< HEAD
  for (int i = 0; i < fromNodes.SubNodes.Size(); i++)
=======
  FOR_VECTOR (i, fromNodes.SubNodes)
>>>>>>> upstream/master
  {
    const CCensorNode &node = fromNodes.SubNodes[i];
    int subNodeIndex = FindSubNode(node.Name);
    if (subNodeIndex < 0)
      subNodeIndex = SubNodes.Add(CCensorNode(node.Name, this));
    SubNodes[subNodeIndex].ExtendExclude(node);
  }
}

int CCensor::FindPrefix(const UString &prefix) const
{
<<<<<<< HEAD
  for (int i = 0; i < Pairs.Size(); i++)
=======
  FOR_VECTOR (i, Pairs)
>>>>>>> upstream/master
    if (CompareFileNames(Pairs[i].Prefix, prefix) == 0)
      return i;
  return -1;
}

<<<<<<< HEAD
void CCensor::AddItem(bool include, const UString &path, bool recursive)
{
  UStringVector pathParts;
  if (path.IsEmpty())
    throw "Empty file path";
  SplitPathToParts(path, pathParts);
=======
#ifdef _WIN32

bool IsDriveColonName(const wchar_t *s)
{
  wchar_t c = s[0];
  return c != 0 && s[1] == ':' && s[2] == 0 && (c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z');
}

unsigned GetNumPrefixParts_if_DrivePath(UStringVector &pathParts)
{
  if (pathParts.IsEmpty())
    return 0;
  
  unsigned testIndex = 0;
  if (pathParts[0].IsEmpty())
  {
    if (pathParts.Size() < 4
        || !pathParts[1].IsEmpty()
        || pathParts[2] != L"?")
      return 0;
    testIndex = 3;
  }
  if (NWildcard::IsDriveColonName(pathParts[testIndex]))
    return testIndex + 1;
  return 0;
}

#endif

static unsigned GetNumPrefixParts(const UStringVector &pathParts)
{
  if (pathParts.IsEmpty())
    return 0;
  
  #ifdef _WIN32
  
  if (IsDriveColonName(pathParts[0]))
    return 1;
  if (!pathParts[0].IsEmpty())
    return 0;

  if (pathParts.Size() == 1)
    return 1;
  if (!pathParts[1].IsEmpty())
    return 1;
  if (pathParts.Size() == 2)
    return 2;
  if (pathParts[2] == L".")
    return 3;

  unsigned networkParts = 2;
  if (pathParts[2] == L"?")
  {
    if (pathParts.Size() == 3)
      return 3;
    if (IsDriveColonName(pathParts[3]))
      return 4;
    if (!pathParts[3].IsEqualTo_Ascii_NoCase("UNC"))
      return 3;
    networkParts = 4;
  }

  networkParts +=
      // 2; // server/share
      1; // server
  if (pathParts.Size() <= networkParts)
    return pathParts.Size();
  return networkParts;

  #else
  
  return pathParts[0].IsEmpty() ? 1 : 0;
 
  #endif
}

void CCensor::AddItem(ECensorPathMode pathMode, bool include, const UString &path, bool recursive, bool wildcardMatching)
{
  if (path.IsEmpty())
    throw "Empty file path";

  UStringVector pathParts;
  SplitPathToParts(path, pathParts);

>>>>>>> upstream/master
  bool forFile = true;
  if (pathParts.Back().IsEmpty())
  {
    forFile = false;
    pathParts.DeleteBack();
  }
<<<<<<< HEAD
  const UString &front = pathParts.Front();
  bool isAbs = false;
  if (front.IsEmpty())
    isAbs = true;
  else if (front.Length() == 2 && front[1] == L':')
    isAbs = true;
  else
  {
    for (int i = 0; i < pathParts.Size(); i++)
    {
      const UString &part = pathParts[i];
      if (part == L".." || part == L".")
      {
        isAbs = true;
        break;
      }
    }
  }
  int numAbsParts = 0;
  if (isAbs)
    if (pathParts.Size() > 1)
      numAbsParts = pathParts.Size() - 1;
    else
      numAbsParts = 1;
  UString prefix;
  for (int i = 0; i < numAbsParts; i++)
  {
    const UString &front = pathParts.Front();
    if (DoesNameContainWildCard(front))
      break;
    prefix += front;
    prefix += WCHAR_PATH_SEPARATOR;
    pathParts.Delete(0);
  }
=======
  
  UString prefix;
  
  int ignoreWildcardIndex = -1;

  // #ifdef _WIN32
  // we ignore "?" wildcard in "\\?\" prefix.
  if (pathParts.Size() >= 3
      && pathParts[0].IsEmpty()
      && pathParts[1].IsEmpty()
      && pathParts[2] == L"?")
    ignoreWildcardIndex = 2;
  // #endif

  if (pathMode != k_AbsPath)
  {
    ignoreWildcardIndex = -1;

    const unsigned numPrefixParts = GetNumPrefixParts(pathParts);
    unsigned numSkipParts = numPrefixParts;

    if (pathMode != k_FullPath)
    {
      if (numPrefixParts != 0 && pathParts.Size() > numPrefixParts)
        numSkipParts = pathParts.Size() - 1;
    }
    {
      int dotsIndex = -1;
      for (unsigned i = numPrefixParts; i < pathParts.Size(); i++)
      {
        const UString &part = pathParts[i];
        if (part == L".." || part == L".")
          dotsIndex = i;
      }

      if (dotsIndex >= 0)
        if (dotsIndex == (int)pathParts.Size() - 1)
          numSkipParts = pathParts.Size();
        else
          numSkipParts = pathParts.Size() - 1;
    }

    for (unsigned i = 0; i < numSkipParts; i++)
    {
      {
        const UString &front = pathParts.Front();
        // WIN32 doesn't support wildcards in file names
        if (wildcardMatching)
          if (i >= numPrefixParts && DoesNameContainWildcard(front))
            break;
        prefix += front;
        prefix.Add_PathSepar();
      }
      pathParts.Delete(0);
    }
  }

>>>>>>> upstream/master
  int index = FindPrefix(prefix);
  if (index < 0)
    index = Pairs.Add(CPair(prefix));

<<<<<<< HEAD
=======
  if (pathMode != k_AbsPath)
  {
    if (pathParts.IsEmpty() || pathParts.Size() == 1 && pathParts[0].IsEmpty())
    {
      // we create universal item, if we skip all parts as prefix (like \ or L:\ )
      pathParts.Clear();
      pathParts.Add(L"*");
      forFile = true;
      wildcardMatching = true;
      recursive = false;
    }
  }

>>>>>>> upstream/master
  CItem item;
  item.PathParts = pathParts;
  item.ForDir = true;
  item.ForFile = forFile;
  item.Recursive = recursive;
<<<<<<< HEAD
  Pairs[index].Head.AddItem(include, item);
}

bool CCensor::CheckPath(const UString &path, bool isFile) const
{
  bool finded = false;
  for (int i = 0; i < Pairs.Size(); i++)
  {
    bool include;
    if (Pairs[i].Head.CheckPath(path, isFile, include))
=======
  item.WildcardMatching = wildcardMatching;
  Pairs[index].Head.AddItem(include, item, ignoreWildcardIndex);
}

/*
bool CCensor::CheckPath(bool isAltStream, const UString &path, bool isFile) const
{
  bool finded = false;
  FOR_VECTOR (i, Pairs)
  {
    bool include;
    if (Pairs[i].Head.CheckPath2(isAltStream, path, isFile, include))
>>>>>>> upstream/master
    {
      if (!include)
        return false;
      finded = true;
    }
  }
  return finded;
}
<<<<<<< HEAD

void CCensor::ExtendExclude()
{
  int i;
=======
*/

void CCensor::ExtendExclude()
{
  unsigned i;
>>>>>>> upstream/master
  for (i = 0; i < Pairs.Size(); i++)
    if (Pairs[i].Prefix.IsEmpty())
      break;
  if (i == Pairs.Size())
    return;
<<<<<<< HEAD
  int index = i;
=======
  unsigned index = i;
>>>>>>> upstream/master
  for (i = 0; i < Pairs.Size(); i++)
    if (index != i)
      Pairs[i].Head.ExtendExclude(Pairs[index].Head);
}

<<<<<<< HEAD
=======
void CCensor::AddPathsToCensor(ECensorPathMode censorPathMode)
{
  FOR_VECTOR(i, CensorPaths)
  {
    const CCensorPath &cp = CensorPaths[i];
    AddItem(censorPathMode, cp.Include, cp.Path, cp.Recursive, cp.WildcardMatching);
  }
  CensorPaths.Clear();
}

void CCensor::AddPreItem(bool include, const UString &path, bool recursive, bool wildcardMatching)
{
  CCensorPath &cp = CensorPaths.AddNew();
  cp.Path = path;
  cp.Include = include;
  cp.Recursive = recursive;
  cp.WildcardMatching = wildcardMatching;
}

>>>>>>> upstream/master
}
