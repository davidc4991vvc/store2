// PercentPrinter.h

#ifndef __PERCENT_PRINTER_H
#define __PERCENT_PRINTER_H

<<<<<<< HEAD
#include "Common/StdOutStream.h"

class CPercentPrinter
{
  UInt64 m_MinStepSize;
  UInt64 m_PrevValue;
  UInt64 m_CurValue;
  UInt64 m_Total;
  unsigned m_NumExtraChars;
public:
  CStdOutStream *OutStream;

  CPercentPrinter(UInt64 minStepSize = 1): m_MinStepSize(minStepSize),
      m_PrevValue(0), m_CurValue(0), m_Total((UInt64)(Int64)-1), m_NumExtraChars(0) {}
  void SetTotal(UInt64 total) { m_Total = total; m_PrevValue = 0; }
  void SetRatio(UInt64 doneValue) { m_CurValue = doneValue; }
  void PrintString(const char *s);
  void PrintString(const wchar_t *s);
  void PrintNewLine();
  void ClosePrint();
  void RePrintRatio();
  void PrintRatio();
=======
#include "../../../Common/StdOutStream.h"

struct CPercentPrinterState
{
  UInt64 Completed;
  UInt64 Total;
  
  UInt64 Files;

  AString Command;
  UString FileName;

  void ClearCurState();

  CPercentPrinterState():
      Completed(0),
      Total((UInt64)(Int64)-1),
      Files(0)
    {}
};

class CPercentPrinter: public CPercentPrinterState
{
  UInt32 _tickStep;
  DWORD _prevTick;

  AString _s;

  AString _printedString;
  AString _temp;
  UString _tempU;

  CPercentPrinterState _printedState;
  AString _printedPercents;

  void GetPercents();

public:
  CStdOutStream *_so;

  bool NeedFlush;
  unsigned MaxLen;
  
  CPercentPrinter(UInt32 tickStep = 200):
      _tickStep(tickStep),
      _prevTick(0),
      NeedFlush(true),
      MaxLen(80 - 1)
  {}

  ~CPercentPrinter();

  void ClosePrint(bool needFlush);
  void Print();
>>>>>>> upstream/master
};

#endif
