// Common/String.h

#ifndef __COMMON_STRING_H
#define __COMMON_STRING_H

#include <string.h>

<<<<<<< HEAD
#include "Types.h"
#include "MyVector.h"

template <class T>
inline int MyStringLen(const T *s)
{
  int i;
  for (i = 0; s[i] != '\0'; i++);
  return i;
}

template <class T>
inline void MyStringCopy(T *dest, const T *src)
=======
#ifndef _WIN32
#include <wctype.h>
#include <wchar.h>
#endif

#include "MyWindows.h"
#include "MyTypes.h"
#include "MyVector.h"

#ifdef _WIN32
#define IS_PATH_SEPAR(c) ((c) == '\\' || (c) == '/')
#else
#define IS_PATH_SEPAR(c) ((c) == CHAR_PATH_SEPARATOR)
#endif

inline bool IsPathSepar(char    c) { return IS_PATH_SEPAR(c); }
inline bool IsPathSepar(wchar_t c) { return IS_PATH_SEPAR(c); }

inline unsigned MyStringLen(const char *s)
{
  unsigned i;
  for (i = 0; s[i] != 0; i++);
  return i;
}

inline void MyStringCopy(char *dest, const char *src)
>>>>>>> upstream/master
{
  while ((*dest++ = *src++) != 0);
}

<<<<<<< HEAD
int FindCharPosInString(const char *s, char c);
int FindCharPosInString(const wchar_t *s, wchar_t c);

inline wchar_t* MyStringGetNextCharPointer(wchar_t *p)
  { return (p + 1); }
inline const wchar_t* MyStringGetNextCharPointer(const wchar_t *p)
  { return (p + 1); }
inline wchar_t* MyStringGetPrevCharPointer(const wchar_t *, wchar_t *p)
  { return (p - 1); }
inline const wchar_t* MyStringGetPrevCharPointer(const wchar_t *, const wchar_t *p)
  { return (p - 1); }

wchar_t MyCharUpper(wchar_t c);
// wchar_t MyCharLower(wchar_t c);

char *MyStringUpper(char *s);
char *MyStringLower(char *s);

wchar_t *MyStringUpper(wchar_t *s);
wchar_t *MyStringLower(wchar_t *s);

const char* MyStringGetNextCharPointer(const char *p);
const char* MyStringGetPrevCharPointer(const char *base, const char *p);

//////////////////////////////////////
// Compare

int MyStringCompare(const char *s1, const char  *s2);
int MyStringCompare(const wchar_t *s1, const wchar_t *s2);

int MyStringCompareNoCase(const char *s1, const char  *s2);
int MyStringCompareNoCase(const wchar_t *s1, const wchar_t *s2);

template <class T>
class CStringBase
{
  void TrimLeftWithCharSet(const CStringBase &charSet)
  {
    const T *p = _chars;
    while (charSet.Find(*p) >= 0 && (*p != 0))
      p = GetNextCharPointer(p);
    Delete(0, (int)(p - _chars));
  }
  void TrimRightWithCharSet(const CStringBase &charSet)
  {
    const T *p = _chars;
    const T *pLast = NULL;
    while (*p != 0)
    {
      if (charSet.Find(*p) >= 0)
      {
        if (pLast == NULL)
          pLast = p;
      }
      else
        pLast = NULL;
      p = GetNextCharPointer(p);
    }
    if (pLast != NULL)
    {
      int i = (int)(pLast - _chars);
      Delete(i, _length - i);
    }

  }
  void MoveItems(int destIndex, int srcIndex)
  {
    memmove(_chars + destIndex, _chars + srcIndex,
        sizeof(T) * (_length - srcIndex + 1));
  }
  
  void InsertSpace(int &index, int size)
  {
    CorrectIndex(index);
    GrowLength(size);
    MoveItems(index + size, index);
  }

  static const T *GetNextCharPointer(const T *p)
    { return MyStringGetNextCharPointer(p); }
  static const T *GetPrevCharPointer(const T *base, const T *p)
    { return MyStringGetPrevCharPointer(base, p); }
protected:
  T *_chars;
  int _length;
  int _capacity;
  
  void SetCapacity(int newCapacity)
  {
    int realCapacity = newCapacity + 1;
    if (realCapacity == _capacity)
      return;
    /*
    const int kMaxStringSize = 0x20000000;
    if (newCapacity > kMaxStringSize || newCapacity < _length)
      throw 1052337;
    */
    T *newBuffer = new T[realCapacity];
    if (_capacity > 0)
    {
      for (int i = 0; i < _length; i++)
        newBuffer[i] = _chars[i];
      delete []_chars;
    }
    _chars = newBuffer;
    _chars[_length] = 0;
    _capacity = realCapacity;
  }

  void GrowLength(int n)
  {
    int freeSize = _capacity - _length - 1;
    if (n <= freeSize)
      return;
    int delta;
    if (_capacity > 64)
      delta = _capacity / 2;
    else if (_capacity > 8)
      delta = 16;
    else
      delta = 4;
    if (freeSize + delta < n)
      delta = n - freeSize;
    SetCapacity(_capacity + delta);
  }

  void CorrectIndex(int &index) const
  {
    if (index > _length)
      index = _length;
  }

public:
  CStringBase(): _chars(0), _length(0), _capacity(0) { SetCapacity(3); }
  CStringBase(T c):  _chars(0), _length(0), _capacity(0)
  {
    SetCapacity(1);
    _chars[0] = c;
    _chars[1] = 0;
    _length = 1;
  }
  CStringBase(const T *chars): _chars(0), _length(0), _capacity(0)
  {
    int length = MyStringLen(chars);
    SetCapacity(length);
    MyStringCopy(_chars, chars); // can be optimized by memove()
    _length = length;
  }
  CStringBase(const CStringBase &s):  _chars(0), _length(0), _capacity(0)
  {
    SetCapacity(s._length);
    MyStringCopy(_chars, s._chars);
    _length = s._length;
  }
  ~CStringBase() {  delete []_chars; }

  operator const T*() const { return _chars;}

  T Back() const { return _chars[_length - 1]; }

  // The minimum size of the character buffer in characters.
  // This value does not include space for a null terminator.
  T* GetBuffer(int minBufLength)
  {
    if (minBufLength >= _capacity)
      SetCapacity(minBufLength);
    return _chars;
  }
  void ReleaseBuffer() { ReleaseBuffer(MyStringLen(_chars)); }
  void ReleaseBuffer(int newLength)
  {
    /*
    if (newLength >= _capacity)
      throw 282217;
    */
    _chars[newLength] = 0;
    _length = newLength;
  }

  CStringBase& operator=(T c)
  {
    Empty();
    SetCapacity(1);
    _chars[0] = c;
    _chars[1] = 0;
    _length = 1;
    return *this;
  }
  CStringBase& operator=(const T *chars)
  {
    Empty();
    int length = MyStringLen(chars);
    SetCapacity(length);
    MyStringCopy(_chars, chars);
    _length = length;
    return *this;
  }
  CStringBase& operator=(const CStringBase& s)
  {
    if (&s == this)
      return *this;
    Empty();
    SetCapacity(s._length);
    MyStringCopy(_chars, s._chars);
    _length = s._length;
    return *this;
  }
  
  CStringBase& operator+=(T c)
  {
    GrowLength(1);
    _chars[_length] = c;
    _chars[++_length] = 0;
    return *this;
  }
  CStringBase& operator+=(const T *s)
  {
    int len = MyStringLen(s);
    GrowLength(len);
    MyStringCopy(_chars + _length, s);
    _length += len;
    return *this;
  }
  CStringBase& operator+=(const CStringBase &s)
  {
    GrowLength(s._length);
    MyStringCopy(_chars + _length, s._chars);
    _length += s._length;
    return *this;
  }
  void Empty()
  {
    _length = 0;
    _chars[0] = 0;
  }
  int Length() const { return _length; }
  bool IsEmpty() const { return (_length == 0); }

  CStringBase Mid(int startIndex) const
    { return Mid(startIndex, _length - startIndex); }
  CStringBase Mid(int startIndex, int count) const
  {
    if (startIndex + count > _length)
      count = _length - startIndex;
    
    if (startIndex == 0 && startIndex + count == _length)
      return *this;
    
    CStringBase<T> result;
    result.SetCapacity(count);
    // MyStringNCopy(result._chars, _chars + startIndex, count);
    for (int i = 0; i < count; i++)
      result._chars[i] = _chars[startIndex + i];
    result._chars[count] = 0;
    result._length = count;
    return result;
  }
  CStringBase Left(int count) const
    { return Mid(0, count); }
  CStringBase Right(int count) const
  {
    if (count > _length)
      count = _length;
    return Mid(_length - count, count);
  }

  void MakeUpper() { MyStringUpper(_chars); }
  void MakeLower() { MyStringLower(_chars); }

  int Compare(const CStringBase& s) const
    { return MyStringCompare(_chars, s._chars); }

  int Compare(const T *s) const
    { return MyStringCompare(_chars, s); }

  int CompareNoCase(const CStringBase& s) const
    { return MyStringCompareNoCase(_chars, s._chars); }

  int CompareNoCase(const T *s) const
    { return MyStringCompareNoCase(_chars, s); }

  /*
  int Collate(const CStringBase& s) const
    { return MyStringCollate(_chars, s._chars); }
  int CollateNoCase(const CStringBase& s) const
    { return MyStringCollateNoCase(_chars, s._chars); }
  */

  int Find(T c) const { return FindCharPosInString(_chars, c); }
  int Find(T c, int startIndex) const
  {
    int pos = FindCharPosInString(_chars + startIndex, c);
    return pos < 0 ? -1 : pos + startIndex;
  }
  int Find(const CStringBase &s) const { return Find(s, 0); }
  int Find(const CStringBase &s, int startIndex) const
  {
    if (s.IsEmpty())
      return startIndex;
    for (; startIndex < _length; startIndex++)
    {
      int j;
      for (j = 0; j < s._length && startIndex + j < _length; j++)
        if (_chars[startIndex+j] != s._chars[j])
          break;
      if (j == s._length)
        return startIndex;
    }
    return -1;
  }
  int ReverseFind(T c) const
  {
    if (_length == 0)
      return -1;
    const T *p = _chars + _length - 1;
    for (;;)
    {
      if (*p == c)
        return (int)(p - _chars);
      if (p == _chars)
        return -1;
      p = GetPrevCharPointer(_chars, p);
    }
  }
  int FindOneOf(const CStringBase &s) const
  {
    for (int i = 0; i < _length; i++)
      if (s.Find(_chars[i]) >= 0)
        return i;
      return -1;
  }

  void TrimLeft(T c)
  {
    const T *p = _chars;
    while (c == *p)
      p = GetNextCharPointer(p);
    Delete(0, p - _chars);
  }
  private:
  CStringBase GetTrimDefaultCharSet()
  {
    CStringBase<T> charSet;
    charSet += (T)' ';
    charSet += (T)'\n';
    charSet += (T)'\t';
    return charSet;
  }
  public:

  void TrimLeft()
  {
    TrimLeftWithCharSet(GetTrimDefaultCharSet());
  }
  void TrimRight()
  {
    TrimRightWithCharSet(GetTrimDefaultCharSet());
  }
  void TrimRight(T c)
  {
    const T *p = _chars;
    const T *pLast = NULL;
    while (*p != 0)
    {
      if (*p == c)
      {
        if (pLast == NULL)
          pLast = p;
      }
      else
        pLast = NULL;
      p = GetNextCharPointer(p);
    }
    if (pLast != NULL)
    {
      int i = pLast - _chars;
      Delete(i, _length - i);
    }
  }
=======
inline char *MyStpCpy(char *dest, const char *src)
{
  for (;;)
  {
    char c = *src;
    *dest = c;
    if (c == 0)
      return dest;
    src++;
    dest++;
  }
}

inline unsigned MyStringLen(const wchar_t *s)
{
  unsigned i;
  for (i = 0; s[i] != 0; i++);
  return i;
}

inline void MyStringCopy(wchar_t *dest, const wchar_t *src)
{
  while ((*dest++ = *src++) != 0);
}

/*
inline wchar_t *MyWcpCpy(wchar_t *dest, const wchar_t *src)
{
  for (;;)
  {
    wchar_t c = *src;
    *dest = c;
    if (c == 0)
      return dest;
    src++;
    dest++;
  }
}
*/

int FindCharPosInString(const char *s, char c) throw();
int FindCharPosInString(const wchar_t *s, wchar_t c) throw();

#ifdef _WIN32
  #ifndef _UNICODE
    #define STRING_UNICODE_THROW
  #endif
#endif

#ifndef STRING_UNICODE_THROW
  #define STRING_UNICODE_THROW throw()
#endif

/*
inline char MyCharUpper_Ascii(char c)
{
  if (c >= 'a' && c <= 'z')
    return (char)(c - 0x20);
  return c;
}
inline wchar_t MyCharUpper_Ascii(wchar_t c)
{
  if (c >= 'a' && c <= 'z')
    return (wchar_t)(c - 0x20);
  return c;
}
*/

inline char MyCharLower_Ascii(char c)
{
  if (c >= 'A' && c <= 'Z')
    return (char)((unsigned char)c + 0x20);
  return c;
}

inline wchar_t MyCharLower_Ascii(wchar_t c)
{
  if (c >= 'A' && c <= 'Z')
    return (wchar_t)(c + 0x20);
  return c;
}

wchar_t MyCharUpper_WIN(wchar_t c) throw();

inline wchar_t MyCharUpper(wchar_t c) throw()
{
  if (c < 'a') return c;
  if (c <= 'z') return (wchar_t)(c - 0x20);
  if (c <= 0x7F) return c;
  #ifdef _WIN32
    #ifdef _UNICODE
      return (wchar_t)(unsigned)(UINT_PTR)CharUpperW((LPWSTR)(UINT_PTR)(unsigned)c);
    #else
      return (wchar_t)MyCharUpper_WIN(c);
    #endif
  #else
    return (wchar_t)towupper(c);
  #endif
}

/*
wchar_t MyCharLower_WIN(wchar_t c) throw();

inline wchar_t MyCharLower(wchar_t c) throw()
{
  if (c < 'A') return c;
  if (c <= 'Z') return (wchar_t)(c + 0x20);
  if (c <= 0x7F) return c;
  #ifdef _WIN32
    #ifdef _UNICODE
      return (wchar_t)(unsigned)(UINT_PTR)CharLowerW((LPWSTR)(UINT_PTR)(unsigned)c);
    #else
      return (wchar_t)MyCharLower_WIN(c);
    #endif
  #else
    return (wchar_t)tolower(c);
  #endif
}
*/

// char *MyStringUpper(char *s) throw();
// char *MyStringLower(char *s) throw();

// void MyStringUpper_Ascii(wchar_t *s) throw();
void MyStringLower_Ascii(char *s) throw();
void MyStringLower_Ascii(wchar_t *s) throw();
// wchar_t *MyStringUpper(wchar_t *s) STRING_UNICODE_THROW;
// wchar_t *MyStringLower(wchar_t *s) STRING_UNICODE_THROW;

bool StringsAreEqualNoCase(const wchar_t *s1, const wchar_t *s2) throw();

bool IsString1PrefixedByString2(const char *s1, const char *s2) throw();
bool IsString1PrefixedByString2(const wchar_t *s1, const wchar_t *s2) throw();
bool IsString1PrefixedByString2_NoCase(const wchar_t *s1, const wchar_t *s2) throw();

int MyStringCompareNoCase(const wchar_t *s1, const wchar_t *s2) throw();
// int MyStringCompareNoCase_N(const wchar_t *s1, const wchar_t *s2, unsigned num) throw();

// ---------- ASCII ----------
// char values in ASCII strings must be less then 128
bool StringsAreEqual_Ascii(const wchar_t *u, const char *a) throw();
bool StringsAreEqualNoCase_Ascii(const char *s1, const char *s2) throw();
bool StringsAreEqualNoCase_Ascii(const wchar_t *s1, const char *s2) throw();
bool StringsAreEqualNoCase_Ascii(const wchar_t *s1, const wchar_t *s2) throw();

#define MY_STRING_DELETE(_p_) delete []_p_;
// #define MY_STRING_DELETE(_p_) my_delete(_p_);

class AString
{
  char *_chars;
  unsigned _len;
  unsigned _limit;

  void MoveItems(unsigned dest, unsigned src)
  {
    memmove(_chars + dest, _chars + src, (size_t)(_len - src + 1) * sizeof(char));
  }
  
  void InsertSpace(unsigned &index, unsigned size);
  
  void ReAlloc(unsigned newLimit);
  void ReAlloc2(unsigned newLimit);
  void SetStartLen(unsigned len);
  void Grow_1();
  void Grow(unsigned n);

  // AString(unsigned num, const char *s);
  AString(unsigned num, const AString &s);
  AString(const AString &s, char c); // it's for String + char
  AString(const char *s1, unsigned num1, const char *s2, unsigned num2);

  friend AString operator+(const AString &s, char c) { return AString(s, c); } ;
  // friend AString operator+(char c, const AString &s); // is not supported

  friend AString operator+(const AString &s1, const AString &s2);
  friend AString operator+(const AString &s1, const char    *s2);
  friend AString operator+(const char    *s1, const AString &s2);

  // ---------- forbidden functions ----------
  AString &operator+=(wchar_t c);
  AString &operator=(wchar_t c);
  AString(wchar_t c);
  void Find(wchar_t c) const;
  void Find(wchar_t c, unsigned startIndex) const;
  void ReverseFind(wchar_t c) const;
  void InsertAtFront(wchar_t c);
  void RemoveChar(wchar_t ch);
  void Replace(wchar_t oldChar, wchar_t newChar);

public:
  AString();
  AString(char c);
  AString(const char *s);
  AString(const AString &s);
  ~AString() { MY_STRING_DELETE(_chars); }

  unsigned Len() const { return _len; }
  bool IsEmpty() const { return _len == 0; }
  void Empty() { _len = 0; _chars[0] = 0; }

  operator const char *() const { return _chars; }
  const char *Ptr() const { return _chars; }
  const char *Ptr(unsigned pos) const { return _chars + pos; }
  const char *RightPtr(unsigned num) const { return _chars + _len - num; }
  char Back() const { return _chars[_len - 1]; }

  void ReplaceOneCharAtPos(unsigned pos, char c) { _chars[pos] = c; }

  /* GetBuf(minLen): provides the buffer that can store
     at least (minLen) characters and additional null terminator.
     9.35: GetBuf doesn't preserve old characters and terminator */
  char *GetBuf(unsigned minLen)
  {
    if (minLen > _limit)
      ReAlloc2(minLen);
    return _chars;
  }
  char *GetBuf_SetEnd(unsigned minLen)
  {
    if (minLen > _limit)
      ReAlloc2(minLen);
    char *chars = _chars;
    chars[minLen] = 0;
    _len = minLen;
    return chars;
  }

  void ReleaseBuf_SetLen(unsigned newLen) { _len = newLen; }
  void ReleaseBuf_SetEnd(unsigned newLen) { _len = newLen; _chars[newLen] = 0; }
  void ReleaseBuf_CalcLen(unsigned maxLen)
  {
    char *chars = _chars;
    chars[maxLen] = 0;
    _len = MyStringLen(chars);
  }

  AString &operator=(char c);
  AString &operator=(const char *s);
  AString &operator=(const AString &s);
  void SetFromWStr_if_Ascii(const wchar_t *s);
  // void SetFromBstr_if_Ascii(BSTR s);

  AString &operator+=(char c)
  {
    if (_limit == _len)
      Grow_1();
    unsigned len = _len;
    char *chars = _chars;
    chars[len++] = c;
    chars[len] = 0;
    _len = len;
    return *this;
  }
  
  void Add_Space();
  void Add_Space_if_NotEmpty();
  void Add_LF();
  void Add_PathSepar() { operator+=(CHAR_PATH_SEPARATOR); }

  AString &operator+=(const char *s);
  AString &operator+=(const AString &s);
  void AddAscii(const char *s) { operator+=(s); }

  void SetFrom(const char *s, unsigned len); // no check
  void SetFrom_CalcLen(const char *s, unsigned len);
  // void SetFromAscii(const char *s) { operator+=(s); }

  AString Mid(unsigned startIndex, unsigned count) const { return AString(count, _chars + startIndex); }
  AString Left(unsigned count) const { return AString(count, *this); }

  // void MakeUpper() { MyStringUpper(_chars); }
  // void MakeLower() { MyStringLower(_chars); }
  void MakeLower_Ascii() { MyStringLower_Ascii(_chars); }


  bool IsEqualTo(const char *s) const { return strcmp(_chars, s) == 0; }
  bool IsEqualTo_Ascii_NoCase(const char *s) const { return StringsAreEqualNoCase_Ascii(_chars, s); }
  // int Compare(const char *s) const { return MyStringCompare(_chars, s); }
  // int Compare(const AString &s) const { return MyStringCompare(_chars, s._chars); }
  // int CompareNoCase(const char *s) const { return MyStringCompareNoCase(_chars, s); }
  // int CompareNoCase(const AString &s) const { return MyStringCompareNoCase(_chars, s._chars); }
  bool IsPrefixedBy(const char *s) const { return IsString1PrefixedByString2(_chars, s); }
  bool IsPrefixedBy_Ascii_NoCase(const char *s) const throw();
 
  bool IsAscii() const
  {
    unsigned len = Len();
    const char *s = _chars;
    for (unsigned i = 0; i < len; i++)
      if ((unsigned char)s[i] >= 0x80)
        return false;
    return true;
  }
  int Find(char c) const { return FindCharPosInString(_chars, c); }
  int Find(char c, unsigned startIndex) const
  {
    int pos = FindCharPosInString(_chars + startIndex, c);
    return pos < 0 ? -1 : (int)startIndex + pos;
  }
  
  int ReverseFind(char c) const throw();
  int ReverseFind_Dot() const throw() { return ReverseFind('.'); }
  int ReverseFind_PathSepar() const throw();

  int Find(const char *s) const { return Find(s, 0); }
  int Find(const char *s, unsigned startIndex) const throw();
  
  void TrimLeft() throw();
  void TrimRight() throw();
  void Trim()
  {
    TrimRight();
    TrimLeft();
  }

  void InsertAtFront(char c);
  // void Insert(unsigned index, char c);
  void Insert(unsigned index, const char *s);
  void Insert(unsigned index, const AString &s);

  void RemoveChar(char ch) throw();
  
  void Replace(char oldChar, char newChar) throw();
  void Replace(const AString &oldString, const AString &newString);

  void Delete(unsigned index) throw();
  void Delete(unsigned index, unsigned count) throw();
  void DeleteFrontal(unsigned num) throw();
  void DeleteBack() { _chars[--_len] = 0; }
  void DeleteFrom(unsigned index)
  {
    if (index < _len)
    {
      _len = index;
      _chars[index] = 0;
    }
  }
};

bool operator<(const AString &s1, const AString &s2);
bool operator>(const AString &s1, const AString &s2);

/*
bool operator==(const AString &s1, const AString &s2);
bool operator==(const AString &s1, const char    *s2);
bool operator==(const char    *s1, const AString &s2);

bool operator!=(const AString &s1, const AString &s2);
bool operator!=(const AString &s1, const char    *s2);
bool operator!=(const char    *s1, const AString &s2);
*/

inline bool operator==(const AString &s1, const AString &s2) { return s1.Len() == s2.Len() && strcmp(s1, s2) == 0; }
inline bool operator==(const AString &s1, const char    *s2) { return strcmp(s1, s2) == 0; }
inline bool operator==(const char    *s1, const AString &s2) { return strcmp(s1, s2) == 0; }

inline bool operator!=(const AString &s1, const AString &s2) { return s1.Len() != s2.Len() || strcmp(s1, s2) != 0; }
inline bool operator!=(const AString &s1, const char    *s2) { return strcmp(s1, s2) != 0; }
inline bool operator!=(const char    *s1, const AString &s2) { return strcmp(s1, s2) != 0; }

// ---------- forbidden functions ----------

void operator==(char c1, const AString &s2);
void operator==(const AString &s1, char c2);

void operator+(char c, const AString &s); // this function can be OK, but we don't use it

void operator+(const AString &s, int c);
void operator+(const AString &s, unsigned c);
void operator+(int c, const AString &s);
void operator+(unsigned c, const AString &s);
void operator-(const AString &s, int c);
void operator-(const AString &s, unsigned c);


class UString
{
  wchar_t *_chars;
  unsigned _len;
  unsigned _limit;

  void MoveItems(unsigned dest, unsigned src)
  {
    memmove(_chars + dest, _chars + src, (size_t)(_len - src + 1) * sizeof(wchar_t));
  }
  
  void InsertSpace(unsigned index, unsigned size);
  
  void ReAlloc(unsigned newLimit);
  void ReAlloc2(unsigned newLimit);
  void SetStartLen(unsigned len);
  void Grow_1();
  void Grow(unsigned n);

  UString(unsigned num, const wchar_t *s); // for Mid
  UString(unsigned num, const UString &s); // for Left
  UString(const UString &s, wchar_t c); // it's for String + char
  UString(const wchar_t *s1, unsigned num1, const wchar_t *s2, unsigned num2);

  friend UString operator+(const UString &s, wchar_t c) { return UString(s, c); } ;
  // friend UString operator+(wchar_t c, const UString &s); // is not supported

  friend UString operator+(const UString &s1, const UString &s2);
  friend UString operator+(const UString &s1, const wchar_t *s2);
  friend UString operator+(const wchar_t *s1, const UString &s2);

  // ---------- forbidden functions ----------
  
  UString &operator+=(char c);
  UString &operator+=(unsigned char c);
  UString &operator=(char c);
  UString &operator=(unsigned char c);
  UString(char c);
  UString(unsigned char c);
  void Find(char c) const;
  void Find(unsigned char c) const;
  void Find(char c, unsigned startIndex) const;
  void Find(unsigned char c, unsigned startIndex) const;
  void ReverseFind(char c) const;
  void ReverseFind(unsigned char c) const;
  void InsertAtFront(char c);
  void InsertAtFront(unsigned char c);
  void RemoveChar(char ch);
  void RemoveChar(unsigned char ch);
  void Replace(char oldChar, char newChar);
  void Replace(unsigned char oldChar, unsigned char newChar);

public:
  UString();
  UString(wchar_t c);
  UString(const wchar_t *s);
  UString(const UString &s);
  ~UString() { MY_STRING_DELETE(_chars); }

  unsigned Len() const { return _len; }
  bool IsEmpty() const { return _len == 0; }
  void Empty() { _len = 0; _chars[0] = 0; }

  operator const wchar_t *() const { return _chars; }
  const wchar_t *Ptr() const { return _chars; }
  const wchar_t *Ptr(unsigned pos) const { return _chars + pos; }
  const wchar_t *RightPtr(unsigned num) const { return _chars + _len - num; }
  wchar_t Back() const { return _chars[_len - 1]; }

  void ReplaceOneCharAtPos(unsigned pos, wchar_t c) { _chars[pos] = c; }

  wchar_t *GetBuf(unsigned minLen)
  {
    if (minLen > _limit)
      ReAlloc2(minLen);
    return _chars;
  }
  wchar_t *GetBuf_SetEnd(unsigned minLen)
  {
    if (minLen > _limit)
      ReAlloc2(minLen);
    wchar_t *chars = _chars;
    chars[minLen] = 0;
    _len = minLen;
    return chars;
  }

  void ReleaseBuf_SetLen(unsigned newLen) { _len = newLen; }
  void ReleaseBuf_SetEnd(unsigned newLen) { _len = newLen; _chars[newLen] = 0; }
  void ReleaseBuf_CalcLen(unsigned maxLen)
  {
    wchar_t *chars = _chars;
    chars[maxLen] = 0;
    _len = MyStringLen(chars);
  }

  UString &operator=(wchar_t c);
  UString &operator=(const wchar_t *s);
  UString &operator=(const UString &s);
  void SetFromBstr(BSTR s);

  UString &operator+=(wchar_t c)
  {
    if (_limit == _len)
      Grow_1();
    unsigned len = _len;
    wchar_t *chars = _chars;
    chars[len++] = c;
    chars[len] = 0;
    _len = len;
    return *this;
  }

  void Add_Space();
  void Add_Space_if_NotEmpty();
  void Add_LF();
  void Add_PathSepar() { operator+=(WCHAR_PATH_SEPARATOR); }

  UString &operator+=(const wchar_t *s);
  UString &operator+=(const UString &s);

  void SetFrom(const wchar_t *s, unsigned len); // no check

  void SetFromAscii(const char *s);
  void AddAscii(const char *s);

  UString Mid(unsigned startIndex, unsigned count) const { return UString(count, _chars + startIndex); }
  UString Left(unsigned count) const { return UString(count, *this); }

  // void MakeUpper() { MyStringUpper(_chars); }
  // void MakeUpper() { MyStringUpper_Ascii(_chars); }
  // void MakeUpper_Ascii() { MyStringUpper_Ascii(_chars); }
  void MakeLower_Ascii() { MyStringLower_Ascii(_chars); }

  bool IsEqualTo(const char *s) const { return StringsAreEqual_Ascii(_chars, s); }
  bool IsEqualTo_NoCase(const wchar_t *s) const { return StringsAreEqualNoCase(_chars, s); }
  bool IsEqualTo_Ascii_NoCase(const char *s) const { return StringsAreEqualNoCase_Ascii(_chars, s); }
  int Compare(const wchar_t *s) const { return wcscmp(_chars, s); }
  // int Compare(const UString &s) const { return MyStringCompare(_chars, s._chars); }
  // int CompareNoCase(const wchar_t *s) const { return MyStringCompareNoCase(_chars, s); }
  // int CompareNoCase(const UString &s) const { return MyStringCompareNoCase(_chars, s._chars); }
  bool IsPrefixedBy(const wchar_t *s) const { return IsString1PrefixedByString2(_chars, s); }
  bool IsPrefixedBy_NoCase(const wchar_t *s) const { return IsString1PrefixedByString2_NoCase(_chars, s); }
  bool IsPrefixedBy_Ascii_NoCase(const char *s) const throw();

  bool IsAscii() const
  {
    unsigned len = Len();
    const wchar_t *s = _chars;
    for (unsigned i = 0; i < len; i++)
      if (s[i] >= 0x80)
        return false;
    return true;
  }
  int Find(wchar_t c) const { return FindCharPosInString(_chars, c); }
  int Find(wchar_t c, unsigned startIndex) const
  {
    int pos = FindCharPosInString(_chars + startIndex, c);
    return pos < 0 ? -1 : (int)startIndex + pos;
  }

  int ReverseFind(wchar_t c) const throw();
  int ReverseFind_Dot() const throw() { return ReverseFind(L'.'); }
  int ReverseFind_PathSepar() const throw();

  int Find(const wchar_t *s) const { return Find(s, 0); }
  int Find(const wchar_t *s, unsigned startIndex) const throw();

  void TrimLeft() throw();
  void TrimRight() throw();
>>>>>>> upstream/master
  void Trim()
  {
    TrimRight();
    TrimLeft();
  }

<<<<<<< HEAD
  int Insert(int index, T c)
  {
    InsertSpace(index, 1);
    _chars[index] = c;
    _length++;
    return _length;
  }
  int Insert(int index, const CStringBase &s)
  {
    CorrectIndex(index);
    if (s.IsEmpty())
      return _length;
    int numInsertChars = s.Length();
    InsertSpace(index, numInsertChars);
    for (int i = 0; i < numInsertChars; i++)
      _chars[index + i] = s[i];
    _length += numInsertChars;
    return _length;
  }

  // !!!!!!!!!!!!!!! test it if newChar = '\0'
  int Replace(T oldChar, T newChar)
  {
    if (oldChar == newChar)
      return 0;
    int number  = 0;
    int pos  = 0;
    while (pos < Length())
    {
      pos = Find(oldChar, pos);
      if (pos < 0)
        break;
      _chars[pos] = newChar;
      pos++;
      number++;
    }
    return number;
  }
  int Replace(const CStringBase &oldString, const CStringBase &newString)
  {
    if (oldString.IsEmpty())
      return 0;
    if (oldString == newString)
      return 0;
    int oldStringLength = oldString.Length();
    int newStringLength = newString.Length();
    int number  = 0;
    int pos  = 0;
    while (pos < _length)
    {
      pos = Find(oldString, pos);
      if (pos < 0)
        break;
      Delete(pos, oldStringLength);
      Insert(pos, newString);
      pos += newStringLength;
      number++;
    }
    return number;
  }
  int Delete(int index, int count = 1)
  {
    if (index + count > _length)
      count = _length - index;
    if (count > 0)
    {
      MoveItems(index, index + count);
      _length -= count;
    }
    return _length;
  }
  void DeleteBack() { Delete(_length - 1); }
};

template <class T>
CStringBase<T> operator+(const CStringBase<T>& s1, const CStringBase<T>& s2)
{
  CStringBase<T> result(s1);
  result += s2;
  return result;
}

template <class T>
CStringBase<T> operator+(const CStringBase<T>& s, T c)
{
  CStringBase<T> result(s);
  result += c;
  return result;
}

template <class T>
CStringBase<T> operator+(T c, const CStringBase<T>& s)
{
  CStringBase<T> result(c);
  result += s;
  return result;
}

template <class T>
CStringBase<T> operator+(const CStringBase<T>& s, const T * chars)
{
  CStringBase<T> result(s);
  result += chars;
  return result;
}

template <class T>
CStringBase<T> operator+(const T * chars, const CStringBase<T>& s)
{
  CStringBase<T> result(chars);
  result += s;
  return result;
}

template <class T>
bool operator==(const CStringBase<T>& s1, const CStringBase<T>& s2)
  { return (s1.Compare(s2) == 0); }

template <class T>
bool operator<(const CStringBase<T>& s1, const CStringBase<T>& s2)
  { return (s1.Compare(s2) < 0); }

template <class T>
bool operator==(const T *s1, const CStringBase<T>& s2)
  { return (s2.Compare(s1) == 0); }

template <class T>
bool operator==(const CStringBase<T>& s1, const T *s2)
  { return (s1.Compare(s2) == 0); }

template <class T>
bool operator!=(const CStringBase<T>& s1, const CStringBase<T>& s2)
  { return (s1.Compare(s2) != 0); }

template <class T>
bool operator!=(const T *s1, const CStringBase<T>& s2)
  { return (s2.Compare(s1) != 0); }

template <class T>
bool operator!=(const CStringBase<T>& s1, const T *s2)
  { return (s1.Compare(s2) != 0); }

typedef CStringBase<char> AString;
typedef CStringBase<wchar_t> UString;
=======
  void InsertAtFront(wchar_t c);
  // void Insert(unsigned index, wchar_t c);
  void Insert(unsigned index, const wchar_t *s);
  void Insert(unsigned index, const UString &s);

  void RemoveChar(wchar_t ch) throw();
  
  void Replace(wchar_t oldChar, wchar_t newChar) throw();
  void Replace(const UString &oldString, const UString &newString);

  void Delete(unsigned index) throw();
  void Delete(unsigned index, unsigned count) throw();
  void DeleteFrontal(unsigned num) throw();
  void DeleteBack() { _chars[--_len] = 0; }
  void DeleteFrom(unsigned index)
  {
    if (index < _len)
    {
      _len = index;
      _chars[index] = 0;
    }
  }
};

bool operator<(const UString &s1, const UString &s2);
bool operator>(const UString &s1, const UString &s2);

inline bool operator==(const UString &s1, const UString &s2) { return s1.Len() == s2.Len() && wcscmp(s1, s2) == 0; }
inline bool operator==(const UString &s1, const wchar_t *s2) { return wcscmp(s1, s2) == 0; }
inline bool operator==(const wchar_t *s1, const UString &s2) { return wcscmp(s1, s2) == 0; }

inline bool operator!=(const UString &s1, const UString &s2) { return s1.Len() != s2.Len() || wcscmp(s1, s2) != 0; }
inline bool operator!=(const UString &s1, const wchar_t *s2) { return wcscmp(s1, s2) != 0; }
inline bool operator!=(const wchar_t *s1, const UString &s2) { return wcscmp(s1, s2) != 0; }


// ---------- forbidden functions ----------

void operator==(wchar_t c1, const UString &s2);
void operator==(const UString &s1, wchar_t c2);

void operator+(wchar_t c, const UString &s); // this function can be OK, but we don't use it

void operator+(const UString &s, char c);
void operator+(const UString &s, unsigned char c);
void operator+(char c, const UString &s);
void operator+(unsigned char c, const UString &s);
void operator-(const UString &s1, wchar_t c);

#ifdef _WIN32
// can we forbid these functions, if wchar_t is 32-bit ?
void operator+(const UString &s, int c);
void operator+(const UString &s, unsigned c);
void operator+(int c, const UString &s);
void operator+(unsigned c, const UString &s);
void operator-(const UString &s1, int c);
void operator-(const UString &s1, unsigned c);
#endif







class UString2
{
  wchar_t *_chars;
  unsigned _len;

  void ReAlloc2(unsigned newLimit);
  void SetStartLen(unsigned len);

  // ---------- forbidden functions ----------
  
  UString2 &operator=(char c);
  UString2 &operator=(unsigned char c);
  UString2 &operator=(wchar_t c);
  UString2(char c);
  UString2(unsigned char c);

public:
  UString2(): _chars(NULL), _len(0) {}
  // UString2(wchar_t c);
  UString2(const wchar_t *s);
  UString2(const UString2 &s);
  ~UString2() { if (_chars) MY_STRING_DELETE(_chars); }

  unsigned Len() const { return _len; }
  bool IsEmpty() const { return _len == 0; }
  // void Empty() { _len = 0; _chars[0] = 0; }

  // operator const wchar_t *() const { return _chars; }
  const wchar_t *GetRawPtr() const { return _chars; }

  wchar_t *GetBuf(unsigned minLen)
  {
    if (!_chars || minLen > _len)
      ReAlloc2(minLen);
    return _chars;
  }
  void ReleaseBuf_SetLen(unsigned newLen) { _len = newLen; }

  UString2 &operator=(const wchar_t *s);
  UString2 &operator=(const UString2 &s);
  void SetFromAscii(const char *s);
};

bool operator==(const UString2 &s1, const UString2 &s2);
bool operator==(const UString2 &s1, const wchar_t *s2);
bool operator==(const wchar_t *s1, const UString2 &s2);

inline bool operator!=(const UString2 &s1, const UString2 &s2) { return !(s1 == s2); }
inline bool operator!=(const UString2 &s1, const wchar_t *s2) { return !(s1 == s2); }
inline bool operator!=(const wchar_t *s1, const UString2 &s2) { return !(s1 == s2); }


// ---------- forbidden functions ----------

void operator==(wchar_t c1, const UString2 &s2);
void operator==(const UString2 &s1, wchar_t c2);
bool operator<(const UString2 &s1, const UString2 &s2);
bool operator>(const UString2 &s1, const UString2 &s2);

void operator+(const UString2 &s1, const UString2 &s2);
void operator+(const UString2 &s1, const wchar_t *s2);
void operator+(const wchar_t *s1, const UString2 &s2);
void operator+(wchar_t c, const UString2 &s);
void operator+(const UString2 &s, wchar_t c);
void operator+(const UString2 &s, char c);
void operator+(const UString2 &s, unsigned char c);
void operator+(char c, const UString2 &s);
void operator+(unsigned char c, const UString2 &s);
void operator-(const UString2 &s1, wchar_t c);





>>>>>>> upstream/master

typedef CObjectVector<AString> AStringVector;
typedef CObjectVector<UString> UStringVector;

#ifdef _UNICODE
  typedef UString CSysString;
#else
  typedef AString CSysString;
#endif

typedef CObjectVector<CSysString> CSysStringVector;


// ---------- FString ----------

#ifdef _WIN32
  #define USE_UNICODE_FSTRING
#endif

#ifdef USE_UNICODE_FSTRING

  #define __FTEXT(quote) L##quote

  typedef wchar_t FChar;
  typedef UString FString;

  #define fs2us(_x_) (_x_)
  #define us2fs(_x_) (_x_)
  FString fas2fs(const AString &s);
  AString fs2fas(const FChar *s);

#else

  #define __FTEXT(quote) quote

  typedef char FChar;
  typedef AString FString;

  UString fs2us(const FString &s);
  FString us2fs(const wchar_t *s);
  #define fas2fs(_x_) (_x_)
  #define fs2fas(_x_) (_x_)

#endif

#define FTEXT(quote) __FTEXT(quote)

#define FCHAR_PATH_SEPARATOR FTEXT(CHAR_PATH_SEPARATOR)
#define FSTRING_PATH_SEPARATOR FTEXT(STRING_PATH_SEPARATOR)
#define FCHAR_ANY_MASK FTEXT('*')
#define FSTRING_ANY_MASK FTEXT("*")
typedef const FChar *CFSTR;

typedef CObjectVector<FString> FStringVector;

#endif
