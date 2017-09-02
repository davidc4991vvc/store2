// Common/StdOutStream.cpp

#include "StdAfx.h"

#include <tchar.h>

#include "IntToString.h"
#include "StdOutStream.h"
#include "StringConvert.h"
#include "UTFConvert.h"

<<<<<<< HEAD
#ifdef _MSC_VER
// "was declared deprecated" disabling
#pragma warning(disable : 4996 )
#endif

=======
>>>>>>> upstream/master
static const char kNewLineChar =  '\n';

static const char *kFileOpenMode = "wt";

extern int g_CodePage;

<<<<<<< HEAD
CStdOutStream  g_StdOut(stdout);
CStdOutStream  g_StdErr(stderr);

bool CStdOutStream::Open(const char *fileName)
=======
CStdOutStream g_StdOut(stdout);
CStdOutStream g_StdErr(stderr);

bool CStdOutStream::Open(const char *fileName) throw()
>>>>>>> upstream/master
{
  Close();
  _stream = fopen(fileName, kFileOpenMode);
  _streamIsOpen = (_stream != 0);
  return _streamIsOpen;
}

<<<<<<< HEAD
bool CStdOutStream::Close()
=======
bool CStdOutStream::Close() throw()
>>>>>>> upstream/master
{
  if (!_streamIsOpen)
    return true;
  if (fclose(_stream) != 0)
    return false;
  _stream = 0;
  _streamIsOpen = false;
  return true;
}

<<<<<<< HEAD
bool CStdOutStream::Flush()
=======
bool CStdOutStream::Flush() throw()
>>>>>>> upstream/master
{
  return (fflush(_stream) == 0);
}

<<<<<<< HEAD
CStdOutStream::~CStdOutStream ()
{
  Close();
}

CStdOutStream & CStdOutStream::operator<<(CStdOutStream & (*aFunction)(CStdOutStream  &))
{
  (*aFunction)(*this);
  return *this;
}

CStdOutStream & endl(CStdOutStream & outStream)
=======
CStdOutStream & endl(CStdOutStream & outStream) throw()
>>>>>>> upstream/master
{
  return outStream << kNewLineChar;
}

<<<<<<< HEAD
CStdOutStream & CStdOutStream::operator<<(const char *s)
{
  fputs(s, _stream);
  return *this;
}

=======
>>>>>>> upstream/master
CStdOutStream & CStdOutStream::operator<<(const wchar_t *s)
{
  int codePage = g_CodePage;
  if (codePage == -1)
    codePage = CP_OEMCP;
  AString dest;
  if (codePage == CP_UTF8)
    ConvertUnicodeToUTF8(s, dest);
  else
<<<<<<< HEAD
    dest = UnicodeStringToMultiByte(s, (UINT)codePage);
  *this << (const char *)dest;
  return *this;
}

CStdOutStream & CStdOutStream::operator<<(char c)
{
  fputc(c, _stream);
  return *this;
}

CStdOutStream & CStdOutStream::operator<<(int number)
{
  char textString[32];
  ConvertInt64ToString(number, textString);
  return operator<<(textString);
}

CStdOutStream & CStdOutStream::operator<<(UInt64 number)
{
  char textString[32];
  ConvertUInt64ToString(number, textString);
  return operator<<(textString);
=======
    UnicodeStringToMultiByte2(dest, s, (UINT)codePage);
  return operator<<((const char *)dest);
}

void StdOut_Convert_UString_to_AString(const UString &s, AString &temp)
{
  int codePage = g_CodePage;
  if (codePage == -1)
    codePage = CP_OEMCP;
  if (codePage == CP_UTF8)
    ConvertUnicodeToUTF8(s, temp);
  else
    UnicodeStringToMultiByte2(temp, s, (UINT)codePage);
}

void CStdOutStream::PrintUString(const UString &s, AString &temp)
{
  StdOut_Convert_UString_to_AString(s, temp);
  *this << (const char *)temp;
}

CStdOutStream & CStdOutStream::operator<<(Int32 number) throw()
{
  char s[32];
  ConvertInt64ToString(number, s);
  return operator<<(s);
}

CStdOutStream & CStdOutStream::operator<<(Int64 number) throw()
{
  char s[32];
  ConvertInt64ToString(number, s);
  return operator<<(s);
}

CStdOutStream & CStdOutStream::operator<<(UInt32 number) throw()
{
  char s[16];
  ConvertUInt32ToString(number, s);
  return operator<<(s);
}

CStdOutStream & CStdOutStream::operator<<(UInt64 number) throw()
{
  char s[32];
  ConvertUInt64ToString(number, s);
  return operator<<(s);
>>>>>>> upstream/master
}
