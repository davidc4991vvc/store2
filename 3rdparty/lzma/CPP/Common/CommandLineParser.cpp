// CommandLineParser.cpp

#include "StdAfx.h"

#include "CommandLineParser.h"

<<<<<<< HEAD
=======
static bool IsString1PrefixedByString2_NoCase(const wchar_t *u, const char *a)
{
  for (;;)
  {
    char c = *a;
    if (c == 0)
      return true;
    if ((unsigned char)MyCharLower_Ascii(c) != MyCharLower_Ascii(*u))
      return false;
    a++;
    u++;
  }
}

>>>>>>> upstream/master
namespace NCommandLineParser {

bool SplitCommandLine(const UString &src, UString &dest1, UString &dest2)
{
  dest1.Empty();
  dest2.Empty();
  bool quoteMode = false;
<<<<<<< HEAD
  int i;
  for (i = 0; i < src.Length(); i++)
  {
    wchar_t c = src[i];
    if (c == L' ' && !quoteMode)
    {
      dest2 = src.Mid(i + 1);
=======
  unsigned i;
  for (i = 0; i < src.Len(); i++)
  {
    wchar_t c = src[i];
    if ((c == L' ' || c == L'\t') && !quoteMode)
    {
      dest2 = src.Ptr(i + 1);
>>>>>>> upstream/master
      return i != 0;
    }
    if (c == L'\"')
      quoteMode = !quoteMode;
    else
      dest1 += c;
  }
  return i != 0;
}

void SplitCommandLine(const UString &s, UStringVector &parts)
{
  UString sTemp = s;
  sTemp.Trim();
  parts.Clear();
  for (;;)
  {
    UString s1, s2;
    if (SplitCommandLine(sTemp, s1, s2))
      parts.Add(s1);
    if (s2.IsEmpty())
      break;
    sTemp = s2;
  }
}


<<<<<<< HEAD
static const wchar_t kSwitchID1 = '-';
// static const wchar_t kSwitchID2 = '/';

static const wchar_t kSwitchMinus = '-';
static const wchar_t *kStopSwitchParsing = L"--";

static bool IsItSwitchChar(wchar_t c)
{
  return (c == kSwitchID1 /*|| c == kSwitchID2 */);
}

CParser::CParser(int numSwitches):
  _numSwitches(numSwitches)
{
  _switches = new CSwitchResult[_numSwitches];
=======
static const char *kStopSwitchParsing = "--";

static bool inline IsItSwitchChar(wchar_t c)
{
  return (c == '-');
}

CParser::CParser(unsigned numSwitches):
  _numSwitches(numSwitches),
  _switches(0)
{
  _switches = new CSwitchResult[numSwitches];
>>>>>>> upstream/master
}

CParser::~CParser()
{
  delete []_switches;
}

<<<<<<< HEAD
void CParser::ParseStrings(const CSwitchForm *switchForms,
  const UStringVector &commandStrings)
{
  int numCommandStrings = commandStrings.Size();
  bool stopSwitch = false;
  for (int i = 0; i < numCommandStrings; i++)
  {
    const UString &s = commandStrings[i];
    if (stopSwitch)
      NonSwitchStrings.Add(s);
    else
      if (s == kStopSwitchParsing)
        stopSwitch = true;
      else
        if (!ParseString(s, switchForms))
          NonSwitchStrings.Add(s);
  }
}

// if string contains switch then function updates switch structures
// out: (string is a switch)
bool CParser::ParseString(const UString &s, const CSwitchForm *switchForms)
{
  int len = s.Length();
  if (len == 0)
    return false;
  int pos = 0;
  if (!IsItSwitchChar(s[pos]))
    return false;
  while (pos < len)
  {
    if (IsItSwitchChar(s[pos]))
      pos++;
    const int kNoLen = -1;
    int matchedSwitchIndex = 0; // GCC Warning
    int maxLen = kNoLen;
    for (int switchIndex = 0; switchIndex < _numSwitches; switchIndex++)
    {
      int switchLen = MyStringLen(switchForms[switchIndex].IDString);
      if (switchLen <= maxLen || pos + switchLen > len)
        continue;

      UString temp = s + pos;
      temp = temp.Left(switchLen);
      if (temp.CompareNoCase(switchForms[switchIndex].IDString) == 0)
      // if (_strnicmp(switchForms[switchIndex].IDString, LPCSTR(s) + pos, switchLen) == 0)
      {
        matchedSwitchIndex = switchIndex;
        maxLen = switchLen;
      }
    }
    if (maxLen == kNoLen)
      throw "maxLen == kNoLen";
    CSwitchResult &matchedSwitch = _switches[matchedSwitchIndex];
    const CSwitchForm &switchForm = switchForms[matchedSwitchIndex];
    if ((!switchForm.Multi) && matchedSwitch.ThereIs)
      throw "switch must be single";
    matchedSwitch.ThereIs = true;
    pos += maxLen;
    int tailSize = len - pos;
    NSwitchType::EEnum type = switchForm.Type;
    switch(type)
    {
      case NSwitchType::kPostMinus:
        {
          if (tailSize == 0)
            matchedSwitch.WithMinus = false;
          else
          {
            matchedSwitch.WithMinus = (s[pos] == kSwitchMinus);
            if (matchedSwitch.WithMinus)
              pos++;
          }
          break;
        }
      case NSwitchType::kPostChar:
        {
          if (tailSize < switchForm.MinLen)
            throw "switch is not full";
          UString set = switchForm.PostCharSet;
          const int kEmptyCharValue = -1;
          if (tailSize == 0)
            matchedSwitch.PostCharIndex = kEmptyCharValue;
          else
          {
            int index = set.Find(s[pos]);
            if (index < 0)
              matchedSwitch.PostCharIndex =  kEmptyCharValue;
            else
            {
              matchedSwitch.PostCharIndex = index;
              pos++;
            }
          }
          break;
        }
      case NSwitchType::kLimitedPostString:
      case NSwitchType::kUnLimitedPostString:
        {
          int minLen = switchForm.MinLen;
          if (tailSize < minLen)
            throw "switch is not full";
          if (type == NSwitchType::kUnLimitedPostString)
          {
            matchedSwitch.PostStrings.Add(s.Mid(pos));
            return true;
          }
          int maxLen = switchForm.MaxLen;
          UString stringSwitch = s.Mid(pos, minLen);
          pos += minLen;
          for (int i = minLen; i < maxLen && pos < len; i++, pos++)
          {
            wchar_t c = s[pos];
            if (IsItSwitchChar(c))
              break;
            stringSwitch += c;
          }
          matchedSwitch.PostStrings.Add(stringSwitch);
          break;
        }
      case NSwitchType::kSimple:
          break;
    }
  }
  return true;
}

const CSwitchResult& CParser::operator[](size_t index) const
{
  return _switches[index];
}

/////////////////////////////////
// Command parsing procedures

int ParseCommand(int numCommandForms, const CCommandForm *commandForms,
    const UString &commandString, UString &postString)
{
  for (int i = 0; i < numCommandForms; i++)
  {
    const UString id = commandForms[i].IDString;
    if (commandForms[i].PostStringMode)
    {
      if (commandString.Find(id) == 0)
      {
        postString = commandString.Mid(id.Length());
        return i;
      }
    }
    else
      if (commandString == id)
      {
        postString.Empty();
        return i;
      }
  }
  return -1;
}
   
=======

// if (s) contains switch then function updates switch structures
// out: true, if (s) is a switch
bool CParser::ParseString(const UString &s, const CSwitchForm *switchForms)
{
  if (s.IsEmpty() || !IsItSwitchChar(s[0]))
    return false;

  unsigned pos = 1;
  unsigned switchIndex = 0;
  int maxLen = -1;
  
  for (unsigned i = 0; i < _numSwitches; i++)
  {
    const char *key = switchForms[i].Key;
    unsigned switchLen = MyStringLen(key);
    if ((int)switchLen <= maxLen || pos + switchLen > s.Len())
      continue;
    if (IsString1PrefixedByString2_NoCase((const wchar_t *)s + pos, key))
    {
      switchIndex = i;
      maxLen = switchLen;
    }
  }

  if (maxLen < 0)
  {
    ErrorMessage = "Unknown switch:";
    return false;
  }

  pos += maxLen;
  
  CSwitchResult &sw = _switches[switchIndex];
  const CSwitchForm &form = switchForms[switchIndex];
  
  if (!form.Multi && sw.ThereIs)
  {
    ErrorMessage = "Multiple instances for switch:";
    return false;
  }

  sw.ThereIs = true;

  int rem = s.Len() - pos;
  if (rem < form.MinLen)
  {
    ErrorMessage = "Too short switch:";
    return false;
  }
  
  sw.WithMinus = false;
  sw.PostCharIndex = -1;
  
  switch (form.Type)
  {
    case NSwitchType::kMinus:
      if (rem == 1)
      {
        sw.WithMinus = (s[pos] == '-');
        if (sw.WithMinus)
          return true;
        ErrorMessage = "Incorrect switch postfix:";
        return false;
      }
      break;
      
    case NSwitchType::kChar:
      if (rem == 1)
      {
        wchar_t c = s[pos];
        if (c <= 0x7F)
        {
          sw.PostCharIndex = FindCharPosInString(form.PostCharSet, (char)c);
          if (sw.PostCharIndex >= 0)
            return true;
        }
        ErrorMessage = "Incorrect switch postfix:";
        return false;
      }
      break;
      
    case NSwitchType::kString:
      sw.PostStrings.Add((const wchar_t *)s + pos);
      return true;
  }

  if (pos != s.Len())
  {
    ErrorMessage = "Too long switch:";
    return false;
  }
  return true;
}

bool CParser::ParseStrings(const CSwitchForm *switchForms, const UStringVector &commandStrings)
{
  ErrorLine.Empty();
  bool stopSwitch = false;
  FOR_VECTOR (i, commandStrings)
  {
    const UString &s = commandStrings[i];
    if (!stopSwitch)
    {
      if (s.IsEqualTo(kStopSwitchParsing))
      {
        stopSwitch = true;
        continue;
      }
      if (!s.IsEmpty() && IsItSwitchChar(s[0]))
      {
        if (ParseString(s, switchForms))
          continue;
        ErrorLine = s;
        return false;
      }
    }
    NonSwitchStrings.Add(s);
  }
  return true;
}

>>>>>>> upstream/master
}
