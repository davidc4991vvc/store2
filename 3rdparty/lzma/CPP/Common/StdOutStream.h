// Common/StdOutStream.h

<<<<<<< HEAD
#ifndef __COMMON_STDOUTSTREAM_H
#define __COMMON_STDOUTSTREAM_H

#include <stdio.h>

#include "Types.h"

class CStdOutStream
{
  bool _streamIsOpen;
  FILE *_stream;
public:
  CStdOutStream (): _streamIsOpen(false), _stream(0) {};
  CStdOutStream (FILE *stream): _streamIsOpen(false), _stream(stream) {};
  ~CStdOutStream ();
  operator FILE *() { return _stream; }
  bool Open(const char *fileName);
  bool Close();
  bool Flush();
  CStdOutStream & operator<<(CStdOutStream & (* aFunction)(CStdOutStream  &));
  CStdOutStream & operator<<(const char *string);
  CStdOutStream & operator<<(const wchar_t *string);
  CStdOutStream & operator<<(char c);
  CStdOutStream & operator<<(int number);
  CStdOutStream & operator<<(UInt64 number);
};

CStdOutStream & endl(CStdOutStream & outStream);
=======
#ifndef __COMMON_STD_OUT_STREAM_H
#define __COMMON_STD_OUT_STREAM_H

#include <stdio.h>

#include "MyString.h"
#include "MyTypes.h"

class CStdOutStream
{
  FILE *_stream;
  bool _streamIsOpen;
public:
  CStdOutStream(): _stream(0), _streamIsOpen(false) {};
  CStdOutStream(FILE *stream): _stream(stream), _streamIsOpen(false) {};
  ~CStdOutStream() { Close(); }

  // void AttachStdStream(FILE *stream) { _stream  = stream; _streamIsOpen = false; }
  // bool IsDefined() const { return _stream  != NULL; }

  operator FILE *() { return _stream; }
  bool Open(const char *fileName) throw();
  bool Close() throw();
  bool Flush() throw();
  
  CStdOutStream & operator<<(CStdOutStream & (* func)(CStdOutStream  &))
  {
    (*func)(*this);
    return *this;
  }

  CStdOutStream & operator<<(const char *s) throw()
  {
    fputs(s, _stream);
    return *this;
  }

  CStdOutStream & operator<<(char c) throw()
  {
    fputc((unsigned char)c, _stream);
    return *this;
  }

  CStdOutStream & operator<<(Int32 number) throw();
  CStdOutStream & operator<<(Int64 number) throw();
  CStdOutStream & operator<<(UInt32 number) throw();
  CStdOutStream & operator<<(UInt64 number) throw();

  CStdOutStream & operator<<(const wchar_t *s);
  void PrintUString(const UString &s, AString &temp);
};

CStdOutStream & endl(CStdOutStream & outStream) throw();
>>>>>>> upstream/master

extern CStdOutStream g_StdOut;
extern CStdOutStream g_StdErr;

<<<<<<< HEAD
=======
void StdOut_Convert_UString_to_AString(const UString &s, AString &temp);

>>>>>>> upstream/master
#endif
