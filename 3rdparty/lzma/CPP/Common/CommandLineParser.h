// Common/CommandLineParser.h

#ifndef __COMMON_COMMAND_LINE_PARSER_H
#define __COMMON_COMMAND_LINE_PARSER_H

#include "MyString.h"

namespace NCommandLineParser {

bool SplitCommandLine(const UString &src, UString &dest1, UString &dest2);
void SplitCommandLine(const UString &s, UStringVector &parts);

<<<<<<< HEAD
namespace NSwitchType {
  enum EEnum
  {
    kSimple,
    kPostMinus,
    kLimitedPostString,
    kUnLimitedPostString,
    kPostChar
=======
namespace NSwitchType
{
  enum EEnum
  {
    kSimple,
    kMinus,
    kString,
    kChar
>>>>>>> upstream/master
  };
}

struct CSwitchForm
{
<<<<<<< HEAD
  const wchar_t *IDString;
  NSwitchType::EEnum Type;
  bool Multi;
  int MinLen;
  int MaxLen;
  const wchar_t *PostCharSet;
=======
  const char *Key;
  Byte Type;
  bool Multi;
  Byte MinLen;
  // int MaxLen;
  const char *PostCharSet;
>>>>>>> upstream/master
};

struct CSwitchResult
{
  bool ThereIs;
  bool WithMinus;
<<<<<<< HEAD
  UStringVector PostStrings;
  int PostCharIndex;
=======
  int PostCharIndex;
  UStringVector PostStrings;
  
>>>>>>> upstream/master
  CSwitchResult(): ThereIs(false) {};
};
  
class CParser
{
<<<<<<< HEAD
  int _numSwitches;
  CSwitchResult *_switches;
  bool ParseString(const UString &s, const CSwitchForm *switchForms);
public:
  UStringVector NonSwitchStrings;
  CParser(int numSwitches);
  ~CParser();
  void ParseStrings(const CSwitchForm *switchForms,
    const UStringVector &commandStrings);
  const CSwitchResult& operator[](size_t index) const;
};

/////////////////////////////////
// Command parsing procedures

struct CCommandForm
{
  const wchar_t *IDString;
  bool PostStringMode;
};

// Returns: Index of form and postString; -1, if there is no match
int ParseCommand(int numCommandForms, const CCommandForm *commandForms,
    const UString &commandString, UString &postString);

=======
  unsigned _numSwitches;
  CSwitchResult *_switches;

  bool ParseString(const UString &s, const CSwitchForm *switchForms);
public:
  UStringVector NonSwitchStrings;
  AString ErrorMessage;
  UString ErrorLine;
  
  CParser(unsigned numSwitches);
  ~CParser();
  bool ParseStrings(const CSwitchForm *switchForms, const UStringVector &commandStrings);
  const CSwitchResult& operator[](size_t index) const { return _switches[index]; }
};

>>>>>>> upstream/master
}

#endif
