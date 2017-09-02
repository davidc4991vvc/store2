// Common/StdInStream.h

<<<<<<< HEAD
#ifndef __COMMON_STDINSTREAM_H
#define __COMMON_STDINSTREAM_H
=======
#ifndef __COMMON_STD_IN_STREAM_H
#define __COMMON_STD_IN_STREAM_H
>>>>>>> upstream/master

#include <stdio.h>

#include "MyString.h"
<<<<<<< HEAD
#include "Types.h"

class CStdInStream
{
  bool _streamIsOpen;
  FILE *_stream;
public:
  CStdInStream(): _streamIsOpen(false) {};
  CStdInStream(FILE *stream): _streamIsOpen(false), _stream(stream) {};
  ~CStdInStream();
  bool Open(LPCTSTR fileName);
  bool Close();
=======
#include "MyTypes.h"

class CStdInStream
{
  FILE *_stream;
  bool _streamIsOpen;
public:
  CStdInStream(): _stream(0), _streamIsOpen(false) {};
  CStdInStream(FILE *stream): _stream(stream), _streamIsOpen(false) {};
  ~CStdInStream() { Close(); }

  bool Open(LPCTSTR fileName) throw();
  bool Close() throw();
>>>>>>> upstream/master

  AString ScanStringUntilNewLine(bool allowEOF = false);
  void ReadToString(AString &resultString);
  UString ScanUStringUntilNewLine();

<<<<<<< HEAD
  bool Eof();
=======
  bool Eof() throw();
>>>>>>> upstream/master
  int GetChar();
};

extern CStdInStream g_StdIn;

#endif
