// PercentPrinter.cpp

#include "StdAfx.h"

<<<<<<< HEAD
#include "Common/IntToString.h"
#include "Common/MyString.h"

#include "PercentPrinter.h"

static const unsigned kPaddingSize = 2;
static const unsigned kPercentsSize = 4;
static const unsigned kMaxExtraSize = kPaddingSize + 32 + kPercentsSize;

static void ClearPrev(char *p, unsigned num)
{
  unsigned i;
  for (i = 0; i < num; i++) *p++ = '\b';
  for (i = 0; i < num; i++) *p++ = ' ';
  for (i = 0; i < num; i++) *p++ = '\b';
  *p = '\0';
}

void CPercentPrinter::ClosePrint()
{
  if (m_NumExtraChars == 0)
    return;
  char s[kMaxExtraSize * 3 + 1];
  ClearPrev(s, m_NumExtraChars);
  (*OutStream) << s;
  m_NumExtraChars = 0;
}

void CPercentPrinter::PrintString(const char *s)
{
  ClosePrint();
  (*OutStream) << s;
}

void CPercentPrinter::PrintString(const wchar_t *s)
{
  ClosePrint();
  (*OutStream) << s;
}

void CPercentPrinter::PrintNewLine()
{
  ClosePrint();
  (*OutStream) << "\n";
}

void CPercentPrinter::RePrintRatio()
=======
#include "../../../Common/IntToString.h"

#include "PercentPrinter.h"

static const unsigned kPercentsSize = 4;

CPercentPrinter::~CPercentPrinter()
{
  ClosePrint(false);
}

void CPercentPrinterState::ClearCurState()
{
  Completed = 0;
  Total = ((UInt64)(Int64)-1);
  Files = 0;
  Command.Empty();
  FileName.Empty();
}

void CPercentPrinter::ClosePrint(bool needFlush)
{
  unsigned num = _printedString.Len();
  if (num != 0)
  {

  unsigned i;
    
  /* '\r' in old MAC OS means "new line".
     So we can't use '\r' in some systems */
    
  #ifdef _WIN32
    char *start = _temp.GetBuf(num  + 2);
    char *p = start;
    *p++ = '\r';
    for (i = 0; i < num; i++) *p++ = ' ';
    *p++ = '\r';
  #else
    char *start = _temp.GetBuf(num * 3);
    char *p = start;
    for (i = 0; i < num; i++) *p++ = '\b';
    for (i = 0; i < num; i++) *p++ = ' ';
    for (i = 0; i < num; i++) *p++ = '\b';
  #endif
    
  *p = 0;
  _temp.ReleaseBuf_SetLen((unsigned)(p - start));
  *_so << _temp;
  }
  if (needFlush)
    _so->Flush();
  _printedString.Empty();
}

void CPercentPrinter::GetPercents()
>>>>>>> upstream/master
{
  char s[32];
  unsigned size;
  {
    char c = '%';
<<<<<<< HEAD
    UInt64 value = 0;
    if (m_Total == (UInt64)(Int64)-1)
    {
      value = m_CurValue >> 20;
      c = 'M';
    }
    else if (m_Total != 0)
      value = m_CurValue * 100 / m_Total;
    ConvertUInt64ToString(value, s);
    size = (unsigned)strlen(s);
    s[size++] = c;
    s[size] = '\0';
  }

  unsigned extraSize = kPaddingSize + MyMax(size, kPercentsSize);
  if (extraSize < m_NumExtraChars)
    extraSize = m_NumExtraChars;

  char fullString[kMaxExtraSize * 3];
  char *p = fullString;
  unsigned i;
  if (m_NumExtraChars == 0)
  {
    for (i = 0; i < extraSize; i++)
      *p++ = ' ';
    m_NumExtraChars = extraSize;
  }

  for (i = 0; i < m_NumExtraChars; i++)
    *p++ = '\b';
  m_NumExtraChars = extraSize;
  for (; size < extraSize; size++)
    *p++ = ' ';
  MyStringCopy(p, s);
  (*OutStream) << fullString;
  OutStream->Flush();
  m_PrevValue = m_CurValue;
}

void CPercentPrinter::PrintRatio()
{
  if (m_CurValue < m_PrevValue + m_MinStepSize &&
      m_CurValue + m_MinStepSize > m_PrevValue && m_NumExtraChars != 0)
    return;
  RePrintRatio();
=======
    UInt64 val = 0;
    if (Total == (UInt64)(Int64)-1)
    {
      val = Completed >> 20;
      c = 'M';
    }
    else if (Total != 0)
      val = Completed * 100 / Total;
    ConvertUInt64ToString(val, s);
    size = (unsigned)strlen(s);
    s[size++] = c;
    s[size] = 0;
  }

  while (size < kPercentsSize)
  {
    _s += ' ';
    size++;
  }

  _s += s;
}

void CPercentPrinter::Print()
{
  DWORD tick = 0;
  if (_tickStep != 0)
    tick = GetTickCount();

  bool onlyPercentsChanged = false;

  if (!_printedString.IsEmpty())
  {
    if (_tickStep != 0 && (UInt32)(tick - _prevTick) < _tickStep)
      return;
    
    CPercentPrinterState &st = *this;
    if (_printedState.Command == st.Command
        && _printedState.FileName == st.FileName
        && _printedState.Files == st.Files)
    {
      if (_printedState.Total == st.Total
          && _printedState.Completed == st.Completed)
        return;
      onlyPercentsChanged = true;
    }
  }

  _s.Empty();

  GetPercents();
  
  if (onlyPercentsChanged && _s == _printedPercents)
    return;

  _printedPercents = _s;

  if (Files != 0)
  {
    char s[32];
    ConvertUInt64ToString(Files, s);
    // unsigned size = (unsigned)strlen(s);
    // for (; size < 3; size++) _s += ' ';
    _s += ' ';
    _s += s;
    // _s += "f";
  }


  if (!Command.IsEmpty())
  {
    _s += ' ';
    _s += Command;
  }

  if (!FileName.IsEmpty() && _s.Len() < MaxLen)
  {
    _s += ' ';

    StdOut_Convert_UString_to_AString(FileName, _temp);
    _temp.Replace('\n', ' ');
    if (_s.Len() + _temp.Len() > MaxLen)
    {
      unsigned len = FileName.Len();
      for (; len != 0;)
      {
        unsigned delta = len / 8;
        if (delta == 0)
          delta = 1;
        len -= delta;
        _tempU = FileName;
        _tempU.Delete(len / 2, FileName.Len() - len);
        _tempU.Insert(len / 2, L" . ");
        StdOut_Convert_UString_to_AString(_tempU, _temp);
        if (_s.Len() + _temp.Len() <= MaxLen)
          break;
      }
      if (len == 0)
        _temp.Empty();
    }
    _s += _temp;
  }
  
  if (_printedString != _s)
  {
    ClosePrint(false);
    *_so << _s;
    if (NeedFlush)
      _so->Flush();
    _printedString = _s;
  }

  _printedState = *this;

  if (_tickStep != 0)
    _prevTick = tick;
>>>>>>> upstream/master
}
