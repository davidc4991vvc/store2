// LzmaAlone.cpp

#include "StdAfx.h"

#include <stdio.h>

#if (defined(_WIN32) || defined(OS2) || defined(MSDOS)) && !defined(UNDER_CE)
#include <fcntl.h>
#include <io.h>
#define MY_SET_BINARY_MODE(file) _setmode(_fileno(file), O_BINARY)
#else
#define MY_SET_BINARY_MODE(file)
#endif

<<<<<<< HEAD
// #include "../../../Common/MyWindows.h"
=======
#include "../../../Common/MyWindows.h"
>>>>>>> upstream/master
#include "../../../Common/MyInitGuid.h"

#include "../../../../C/7zVersion.h"
#include "../../../../C/Alloc.h"
#include "../../../../C/Lzma86.h"

#include "../../../Windows/NtCheck.h"

#ifndef _7ZIP_ST
#include "../../../Windows/System.h"
#endif

<<<<<<< HEAD
=======
#include "../../../Common/IntToString.h"
>>>>>>> upstream/master
#include "../../../Common/CommandLineParser.h"
#include "../../../Common/StringConvert.h"
#include "../../../Common/StringToInt.h"

#include "../../Common/FileStreams.h"
#include "../../Common/StreamUtils.h"

#include "../../Compress/LzmaDecoder.h"
#include "../../Compress/LzmaEncoder.h"

#include "../../UI/Console/BenchCon.h"
<<<<<<< HEAD


using namespace NCommandLineParser;

=======
#include "../../UI/Console/ConsoleClose.h"

using namespace NCommandLineParser;

static const unsigned kDictSizeLog = 24;

static const char *kCopyrightString = "\nLZMA " MY_VERSION_COPYRIGHT_DATE "\n\n";

static const char *kHelpString =
    "Usage:  LZMA <command> [inputFile] [outputFile] [<switches>...]\n"
    "\n"
    "<command>\n"
    "  e : Encode file\n"
    "  d : Decode file\n"
    "  b : Benchmark\n"
    "<switches>\n"
    "  -a{N}  : set compression mode : [0, 1] : default = 1 (max)\n"
    "  -d{N}  : set dictionary size : [12, 30] : default = 24 (16 MiB)\n"
    "  -fb{N} : set number of fast bytes : [5, 273] : default = 128\n"
    "  -mc{N} : set number of cycles for match finder\n"
    "  -lc{N} : set number of literal context bits : [0, 8] : default = 3\n"
    "  -lp{N} : set number of literal pos bits : [0, 4] : default = 0\n"
    "  -pb{N} : set number of pos bits : [0, 4] : default = 2\n"
    "  -mf{M} : set match finder: [hc4, bt2, bt3, bt4] : default = bt4\n"
    "  -mt{N} : set number of CPU threads\n"
    "  -eos   : write end of stream marker\n"
    "  -si    : read data from stdin\n"
    "  -so    : write data to stdout\n";


>>>>>>> upstream/master
static const char *kCantAllocate = "Can not allocate memory";
static const char *kReadError = "Read error";
static const char *kWriteError = "Write error";

<<<<<<< HEAD
=======

>>>>>>> upstream/master
namespace NKey {
enum Enum
{
  kHelp1 = 0,
  kHelp2,
  kMethod,
  kLevel,
  kAlgo,
  kDict,
  kFb,
  kMc,
  kLc,
  kLp,
  kPb,
  kMatchFinder,
  kMultiThread,
  kEOS,
  kStdIn,
  kStdOut,
  kFilter86
};
}

static const CSwitchForm kSwitchForms[] =
{
<<<<<<< HEAD
  { L"?",  NSwitchType::kSimple, false },
  { L"H",  NSwitchType::kSimple, false },
  { L"MM", NSwitchType::kUnLimitedPostString, false, 1 },
  { L"X", NSwitchType::kUnLimitedPostString, false, 1 },
  { L"A", NSwitchType::kUnLimitedPostString, false, 1 },
  { L"D", NSwitchType::kUnLimitedPostString, false, 1 },
  { L"FB", NSwitchType::kUnLimitedPostString, false, 1 },
  { L"MC", NSwitchType::kUnLimitedPostString, false, 1 },
  { L"LC", NSwitchType::kUnLimitedPostString, false, 1 },
  { L"LP", NSwitchType::kUnLimitedPostString, false, 1 },
  { L"PB", NSwitchType::kUnLimitedPostString, false, 1 },
  { L"MF", NSwitchType::kUnLimitedPostString, false, 1 },
  { L"MT", NSwitchType::kUnLimitedPostString, false, 0 },
  { L"EOS", NSwitchType::kSimple, false },
  { L"SI",  NSwitchType::kSimple, false },
  { L"SO",  NSwitchType::kSimple, false },
  { L"F86",  NSwitchType::kPostChar, false, 0, 0, L"+" }
};

static const int kNumSwitches = sizeof(kSwitchForms) / sizeof(kSwitchForms[0]);

static void PrintMessage(const char *s)
=======
  { "?",  NSwitchType::kSimple, false },
  { "H",  NSwitchType::kSimple, false },
  { "MM", NSwitchType::kString, false, 1 },
  { "X", NSwitchType::kString, false, 1 },
  { "A", NSwitchType::kString, false, 1 },
  { "D", NSwitchType::kString, false, 1 },
  { "FB", NSwitchType::kString, false, 1 },
  { "MC", NSwitchType::kString, false, 1 },
  { "LC", NSwitchType::kString, false, 1 },
  { "LP", NSwitchType::kString, false, 1 },
  { "PB", NSwitchType::kString, false, 1 },
  { "MF", NSwitchType::kString, false, 1 },
  { "MT", NSwitchType::kString, false, 0 },
  { "EOS", NSwitchType::kSimple, false },
  { "SI",  NSwitchType::kSimple, false },
  { "SO",  NSwitchType::kSimple, false },
  { "F86",  NSwitchType::kChar, false, 0, "+" }
};


static void PrintErr(const char *s)
>>>>>>> upstream/master
{
  fputs(s, stderr);
}

<<<<<<< HEAD
static void PrintHelp()
{
  PrintMessage("\nUsage:  LZMA <e|d> inputFile outputFile [<switches>...]\n"
             "  e: encode file\n"
             "  d: decode file\n"
             "  b: Benchmark\n"
    "<Switches>\n"
    "  -a{N}:  set compression mode - [0, 1], default: 1 (max)\n"
    "  -d{N}:  set dictionary size - [12, 30], default: 23 (8MB)\n"
    "  -fb{N}: set number of fast bytes - [5, 273], default: 128\n"
    "  -mc{N}: set number of cycles for match finder\n"
    "  -lc{N}: set number of literal context bits - [0, 8], default: 3\n"
    "  -lp{N}: set number of literal pos bits - [0, 4], default: 0\n"
    "  -pb{N}: set number of pos bits - [0, 4], default: 2\n"
    "  -mf{MF_ID}: set Match Finder: [bt2, bt3, bt4, hc4], default: bt4\n"
    "  -mt{N}: set number of CPU threads\n"
    "  -eos:   write End Of Stream marker\n"
    "  -si:    read data from stdin\n"
    "  -so:    write data to stdout\n"
    );
}

static void PrintHelpAndExit(const char *s)
{
  fprintf(stderr, "\nError: %s\n\n", s);
  PrintHelp();
  throw -1;
}

static void IncorrectCommand()
{
  PrintHelpAndExit("Incorrect command");
}

static void WriteArgumentsToStringList(int numArgs, const char *args[], UStringVector &strings)
{
  for (int i = 1; i < numArgs; i++)
    strings.Add(MultiByteToUnicodeString(args[i]));
}

static bool GetNumber(const wchar_t *s, UInt32 &value)
{
  value = 0;
  if (MyStringLen(s) == 0)
    return false;
  const wchar_t *end;
  UInt64 res = ConvertStringToUInt64(s, &end);
  if (*end != L'\0')
    return false;
  if (res > 0xFFFFFFFF)
    return false;
  value = UInt32(res);
  return true;
}

static void ParseUInt32(const CParser &parser, int index, UInt32 &res)
{
  if (parser[index].ThereIs)
    if (!GetNumber(parser[index].PostStrings[0], res))
      IncorrectCommand();
}

#define NT_CHECK_FAIL_ACTION PrintMessage("Unsupported Windows version"); return 1;

int main2(int numArgs, const char *args[])
{
  NT_CHECK

  PrintMessage("\nLZMA " MY_VERSION_COPYRIGHT_DATE "\n");
=======
static void PrintErr_LF(const char *s)
{
  PrintErr(s);
  fputc('\n', stderr);
}


static void PrintError(const char *s)
{
  PrintErr("\nERROR: ");
  PrintErr_LF(s);
}

static void PrintError2(const char *s1, const wchar_t *s2)
{
  PrintError(s1);
  PrintErr_LF(GetOemString(s2));
}

static void PrintError_int(const char *s, int code)
{
  PrintError(s);
  char temp[32];
  ConvertInt64ToString(code, temp);
  PrintErr("Error code = ");
  PrintErr_LF(temp);
}



static void Print(const char *s)
{
  fputs(s, stdout);
}

static void Print_UInt64(UInt64 v)
{
  char temp[32];
  ConvertUInt64ToString(v, temp);
  Print(temp);
}

static void Print_MB(UInt64 v)
{
  Print_UInt64(v);
  Print(" MiB");
}

static void Print_Size(const char *s, UInt64 v)
{
  Print(s);
  Print_UInt64(v);
  Print(" (");
  Print_MB(v >> 20);
  Print(")\n");
}

static void PrintTitle()
{
  Print(kCopyrightString);
}

static void PrintHelp()
{
  PrintTitle();
  Print(kHelpString);
}

class CProgressPrint:
  public ICompressProgressInfo,
  public CMyUnknownImp
{
  UInt64 _size1;
  UInt64 _size2;
public:
  CProgressPrint(): _size1(0), _size2(0) {}

  void ClosePrint();

  MY_UNKNOWN_IMP1(ICompressProgressInfo)

  STDMETHOD(SetRatioInfo)(const UInt64 *inSize, const UInt64 *outSize);
};

#define BACK_STR \
"\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b"
static const char *kBackSpaces =
BACK_STR
"                                                                "
BACK_STR;


void CProgressPrint::ClosePrint()
{
  Print(kBackSpaces);
}

STDMETHODIMP CProgressPrint::SetRatioInfo(const UInt64 *inSize, const UInt64 *outSize)
{
  if (NConsoleClose::TestBreakSignal())
    return E_ABORT;
  if (inSize)
  {
    UInt64 v1 = *inSize >> 20;
    UInt64 v2 = _size2;
    if (outSize)
      v2 = *outSize >> 20;
    if (v1 != _size1 || v2 != _size2)
    {
      _size1 = v1;
      _size2 = v2;
      ClosePrint();
      Print_MB(_size1);
      Print(" -> ");
      Print_MB(_size2);
    }
  }
  return S_OK;
}


static void IncorrectCommand()
{
  throw "Incorrect command";
}

static UInt32 GetNumber(const wchar_t *s)
{
  const wchar_t *end;
  UInt32 v = ConvertStringToUInt32(s, &end);
  if (*end != 0)
    IncorrectCommand();
  return v;
}

static void ParseUInt32(const CParser &parser, unsigned index, UInt32 &res)
{
  if (parser[index].ThereIs)
    res = GetNumber(parser[index].PostStrings[0]);
}


static int Error_HRESULT(const char *s, HRESULT res)
{
  if (res == E_ABORT)
  {
    Print("\n\nBreak signaled\n");
    return 255;
  }

  PrintError(s);

  if (res == E_OUTOFMEMORY)
  {
    PrintErr_LF(kCantAllocate);
    return 8;
  }
  if (res == E_INVALIDARG)
  {
    PrintErr_LF("Ununsupported parameter");
  }
  else
  {
    char temp[32];
    ConvertUInt32ToHex(res, temp);
    PrintErr("Error code = 0x");
    PrintErr_LF(temp);
  }
  return 1;
}

#define NT_CHECK_FAIL_ACTION PrintError("Unsupported Windows version"); return 1;

static void AddProp(CObjectVector<CProperty> &props2, const char *name, const wchar_t *val)
{
  CProperty &prop = props2.AddNew();
  prop.Name.SetFromAscii(name);
  prop.Value = val;
}

static int main2(int numArgs, const char *args[])
{
  NT_CHECK
>>>>>>> upstream/master

  if (numArgs == 1)
  {
    PrintHelp();
    return 0;
  }

<<<<<<< HEAD
  bool unsupportedTypes = (sizeof(Byte) != 1 || sizeof(UInt32) < 4 || sizeof(UInt64) < 4);
  if (unsupportedTypes)
  {
    PrintMessage("Unsupported base types. Edit Common/Types.h and recompile");
    return 1;
  }

  UStringVector commandStrings;
  WriteArgumentsToStringList(numArgs, args, commandStrings);
  CParser parser(kNumSwitches);
  try
  {
    parser.ParseStrings(kSwitchForms, commandStrings);
=======
  /*
  bool unsupportedTypes = (sizeof(Byte) != 1 || sizeof(UInt32) < 4 || sizeof(UInt64) < 8);
  if (unsupportedTypes)
    throw "Unsupported base types. Edit Common/Types.h and recompile";
  */

  UStringVector commandStrings;
  for (int i = 1; i < numArgs; i++)
    commandStrings.Add(MultiByteToUnicodeString(args[i]));
  
  CParser parser(ARRAY_SIZE(kSwitchForms));
  try
  {
    if (!parser.ParseStrings(kSwitchForms, commandStrings))
    {
      PrintError2(parser.ErrorMessage, parser.ErrorLine);
      return 1;
    }
>>>>>>> upstream/master
  }
  catch(...)
  {
    IncorrectCommand();
  }

  if (parser[NKey::kHelp1].ThereIs || parser[NKey::kHelp2].ThereIs)
  {
    PrintHelp();
    return 0;
  }
<<<<<<< HEAD
  const UStringVector &nonSwitchStrings = parser.NonSwitchStrings;

  int paramIndex = 0;
  if (paramIndex >= nonSwitchStrings.Size())
    IncorrectCommand();
  const UString &command = nonSwitchStrings[paramIndex++];

  CObjectVector<CProperty> props;
  bool dictDefined = false;
  UInt32 dict = (UInt32)(Int32)-1;
  if (parser[NKey::kDict].ThereIs)
  {
    UInt32 dicLog;
    const UString &s = parser[NKey::kDict].PostStrings[0];
    if (!GetNumber(s, dicLog))
      IncorrectCommand();
    dict = 1 << dicLog;
    dictDefined = true;
    CProperty prop;
    prop.Name = L"d";
    prop.Value = s;
    props.Add(prop);
  }
  if (parser[NKey::kLevel].ThereIs)
  {
    UInt32 level = 5;
    const UString &s = parser[NKey::kLevel].PostStrings[0];
    if (!GetNumber(s, level))
      IncorrectCommand();
    CProperty prop;
    prop.Name = L"x";
    prop.Value = s;
    props.Add(prop);
  }
=======

  bool stdInMode = parser[NKey::kStdIn].ThereIs;
  bool stdOutMode = parser[NKey::kStdOut].ThereIs;

  if (!stdOutMode)
    PrintTitle();

  const UStringVector &params = parser.NonSwitchStrings;

  unsigned paramIndex = 0;
  if (paramIndex >= params.Size())
    IncorrectCommand();
  const UString &command = params[paramIndex++];

  CObjectVector<CProperty> props2;
  bool dictDefined = false;
  UInt32 dict = (UInt32)(Int32)-1;
  
  if (parser[NKey::kDict].ThereIs)
  {
    UInt32 dictLog;
    const UString &s = parser[NKey::kDict].PostStrings[0];
    dictLog = GetNumber(s);
    dict = 1 << dictLog;
    dictDefined = true;
    AddProp(props2, "d", s);
  }
  
  if (parser[NKey::kLevel].ThereIs)
  {
    const UString &s = parser[NKey::kLevel].PostStrings[0];
    /* UInt32 level = */ GetNumber(s);
    AddProp(props2, "x", s);
  }
  
>>>>>>> upstream/master
  UString mf = L"BT4";
  if (parser[NKey::kMatchFinder].ThereIs)
    mf = parser[NKey::kMatchFinder].PostStrings[0];

  UInt32 numThreads = (UInt32)(Int32)-1;

  #ifndef _7ZIP_ST
<<<<<<< HEAD
  if (parser[NKey::kMultiThread].ThereIs)
  {
    UInt32 numCPUs = NWindows::NSystem::GetNumberOfProcessors();
    const UString &s = parser[NKey::kMultiThread].PostStrings[0];
    if (s.IsEmpty())
      numThreads = numCPUs;
    else
      if (!GetNumber(s, numThreads))
        IncorrectCommand();
    CProperty prop;
    prop.Name = L"mt";
    prop.Value = s;
    props.Add(prop);
  }
  #endif

  if (parser[NKey::kMethod].ThereIs)
  {
    UString s = parser[NKey::kMethod].PostStrings[0];
    if (s.IsEmpty() || s[0] != '=')
      IncorrectCommand();
    CProperty prop;
    prop.Name = L"m";
    prop.Value = s.Mid(1);
    props.Add(prop);
  }

  if (command.CompareNoCase(L"b") == 0)
  {
    const UInt32 kNumDefaultItereations = 1;
    UInt32 numIterations = kNumDefaultItereations;
    {
      if (paramIndex < nonSwitchStrings.Size())
        if (!GetNumber(nonSwitchStrings[paramIndex++], numIterations))
          numIterations = kNumDefaultItereations;
    }
    HRESULT res = BenchCon(props, numIterations, stderr);
    if (res != S_OK)
    {
      if (res != E_ABORT)
      {
        PrintMessage("Benchmark Error");
        return 1;
      }
    }
    return 0;
=======
  
  if (parser[NKey::kMultiThread].ThereIs)
  {
    const UString &s = parser[NKey::kMultiThread].PostStrings[0];
    if (s.IsEmpty())
      numThreads = NWindows::NSystem::GetNumberOfProcessors();
    else
      numThreads = GetNumber(s);
    AddProp(props2, "mt", s);
  }
  
  #endif

  
  if (parser[NKey::kMethod].ThereIs)
  {
    const UString &s = parser[NKey::kMethod].PostStrings[0];
    if (s.IsEmpty() || s[0] != '=')
      IncorrectCommand();
    AddProp(props2, "m", s.Ptr(1));
  }

  if (StringsAreEqualNoCase_Ascii(command, "b"))
  {
    UInt32 numIterations = 1;
    if (paramIndex < params.Size())
      numIterations = GetNumber(params[paramIndex++]);
    if (params.Size() != paramIndex)
      IncorrectCommand();
  
    HRESULT res = BenchCon(props2, numIterations, stdout);
    
    if (res == S_OK)
      return 0;
    return Error_HRESULT("Benchmark error", res);
  }

  {
    UInt32 needParams = 3;
    if (stdInMode) needParams--;
    if (stdOutMode) needParams--;
    if (needParams != params.Size())
      IncorrectCommand();
>>>>>>> upstream/master
  }

  if (numThreads == (UInt32)(Int32)-1)
    numThreads = 1;

  bool encodeMode = false;
<<<<<<< HEAD
  if (command.CompareNoCase(L"e") == 0)
    encodeMode = true;
  else if (command.CompareNoCase(L"d") == 0)
    encodeMode = false;
  else
    IncorrectCommand();

  bool stdInMode = parser[NKey::kStdIn].ThereIs;
  bool stdOutMode = parser[NKey::kStdOut].ThereIs;

  CMyComPtr<ISequentialInStream> inStream;
  CInFileStream *inStreamSpec = 0;
=======
  
  if (StringsAreEqualNoCase_Ascii(command, "e"))
    encodeMode = true;
  else if (!StringsAreEqualNoCase_Ascii(command, "d"))
    IncorrectCommand();

  CMyComPtr<ISequentialInStream> inStream;
  CInFileStream *inStreamSpec = NULL;
  
>>>>>>> upstream/master
  if (stdInMode)
  {
    inStream = new CStdInFileStream;
    MY_SET_BINARY_MODE(stdin);
  }
  else
  {
<<<<<<< HEAD
    if (paramIndex >= nonSwitchStrings.Size())
      IncorrectCommand();
    const UString &inputName = nonSwitchStrings[paramIndex++];
=======
    const UString &inputName = params[paramIndex++];
>>>>>>> upstream/master
    inStreamSpec = new CInFileStream;
    inStream = inStreamSpec;
    if (!inStreamSpec->Open(us2fs(inputName)))
    {
<<<<<<< HEAD
      fprintf(stderr, "\nError: can not open input file %s\n",
          (const char *)GetOemString(inputName));
=======
      PrintError2("can not open input file", inputName);
>>>>>>> upstream/master
      return 1;
    }
  }

  CMyComPtr<ISequentialOutStream> outStream;
  COutFileStream *outStreamSpec = NULL;
<<<<<<< HEAD
=======
  
>>>>>>> upstream/master
  if (stdOutMode)
  {
    outStream = new CStdOutFileStream;
    MY_SET_BINARY_MODE(stdout);
  }
  else
  {
<<<<<<< HEAD
    if (paramIndex >= nonSwitchStrings.Size())
      IncorrectCommand();
    const UString &outputName = nonSwitchStrings[paramIndex++];
=======
    const UString &outputName = params[paramIndex++];
>>>>>>> upstream/master
    outStreamSpec = new COutFileStream;
    outStream = outStreamSpec;
    if (!outStreamSpec->Create(us2fs(outputName), true))
    {
<<<<<<< HEAD
      fprintf(stderr, "\nError: can not open output file %s\n",
        (const char *)GetOemString(outputName));
=======
      PrintError2("can not open output file", outputName);
>>>>>>> upstream/master
      return 1;
    }
  }

<<<<<<< HEAD
  if (parser[NKey::kFilter86].ThereIs)
  {
    // -f86 switch is for x86 filtered mode: BCJ + LZMA.
    if (parser[NKey::kEOS].ThereIs || stdInMode)
      throw "Can not use stdin in this mode";
    UInt64 fileSize;
    inStreamSpec->File.GetLength(fileSize);
    if (fileSize > 0xF0000000)
      throw "File is too big";
    size_t inSize = (size_t)fileSize;
    Byte *inBuffer = 0;
    if (inSize != 0)
    {
      inBuffer = (Byte *)MyAlloc((size_t)inSize);
      if (inBuffer == 0)
=======
  bool fileSizeDefined = false;
  UInt64 fileSize = 0;
  
  if (inStreamSpec)
  {
    if (!inStreamSpec->File.GetLength(fileSize))
      throw "Can not get file length";
    fileSizeDefined = true;
    if (!stdOutMode)
      Print_Size("Input size:  ", fileSize);
  }

  if (encodeMode && !dictDefined)
  {
    dict = 1 << kDictSizeLog;
    if (fileSizeDefined)
    {
      unsigned i;
      for (i = 16; i < kDictSizeLog; i++)
        if ((UInt32)((UInt32)1 << i) >= fileSize)
          break;
      dict = (UInt32)1 << i;
    }
  }

  if (parser[NKey::kFilter86].ThereIs)
  {
    /* -f86 switch is for x86 filtered mode: BCJ + LZMA.
       It uses modified header format.
       It's not recommended to use -f86 mode now.
       You can use xz format instead, if you want to use filters */

    if (parser[NKey::kEOS].ThereIs || stdInMode)
      throw "Can not use stdin in this mode";

    size_t inSize = (size_t)fileSize;

    if (inSize != fileSize)
      throw "File is too big";

    Byte *inBuffer = NULL;
    
    if (inSize != 0)
    {
      inBuffer = (Byte *)MyAlloc((size_t)inSize);
      if (!inBuffer)
>>>>>>> upstream/master
        throw kCantAllocate;
    }
    
    if (ReadStream_FAIL(inStream, inBuffer, inSize) != S_OK)
      throw "Can not read";

<<<<<<< HEAD
    Byte *outBuffer = 0;
    size_t outSize;
    if (encodeMode)
    {
      // we allocate 105% of original size for output buffer
      outSize = (size_t)fileSize / 20 * 21 + (1 << 16);
      if (outSize != 0)
      {
        outBuffer = (Byte *)MyAlloc((size_t)outSize);
        if (outBuffer == 0)
          throw kCantAllocate;
      }
      if (!dictDefined)
        dict = 1 << 23;
      int res = Lzma86_Encode(outBuffer, &outSize, inBuffer, inSize,
          5, dict, parser[NKey::kFilter86].PostCharIndex == 0 ? SZ_FILTER_YES : SZ_FILTER_AUTO);
      if (res != 0)
      {
        fprintf(stderr, "\nEncoder error = %d\n", (int)res);
=======
    Byte *outBuffer = NULL;
    size_t outSize;
    
    if (encodeMode)
    {
      // we allocate 105% of original size for output buffer
      UInt64 outSize64 = fileSize / 20 * 21 + (1 << 16);

      outSize = (size_t)outSize64;
      
      if (outSize != outSize64)
        throw "File is too big";

      if (outSize != 0)
      {
        outBuffer = (Byte *)MyAlloc((size_t)outSize);
        if (!outBuffer)
          throw kCantAllocate;
      }
      
      int res = Lzma86_Encode(outBuffer, &outSize, inBuffer, inSize,
          5, dict, parser[NKey::kFilter86].PostCharIndex == 0 ? SZ_FILTER_YES : SZ_FILTER_AUTO);
  
      if (res != 0)
      {
        PrintError_int("Encode error", (int)res);
>>>>>>> upstream/master
        return 1;
      }
    }
    else
    {
      UInt64 outSize64;
<<<<<<< HEAD
      if (Lzma86_GetUnpackSize(inBuffer, inSize, &outSize64) != 0)
        throw "data error";
      outSize = (size_t)outSize64;
      if (outSize != outSize64)
        throw "too big";
      if (outSize != 0)
      {
        outBuffer = (Byte *)MyAlloc(outSize);
        if (outBuffer == 0)
          throw kCantAllocate;
      }
      int res = Lzma86_Decode(outBuffer, &outSize, inBuffer, &inSize);
      if (inSize != (size_t)fileSize)
        throw "incorrect processed size";
      if (res != 0)
        throw "LzmaDecoder error";
    }
    if (WriteStream(outStream, outBuffer, outSize) != S_OK)
      throw kWriteError;
    MyFree(outBuffer);
    MyFree(inBuffer);
    return 0;
  }


  UInt64 fileSize;
=======
      
      if (Lzma86_GetUnpackSize(inBuffer, inSize, &outSize64) != 0)
        throw "data error";
      
      outSize = (size_t)outSize64;
      if (outSize != outSize64)
        throw "Unpack size is too big";
      if (outSize != 0)
      {
        outBuffer = (Byte *)MyAlloc(outSize);
        if (!outBuffer)
          throw kCantAllocate;
      }
      
      int res = Lzma86_Decode(outBuffer, &outSize, inBuffer, &inSize);
      
      if (inSize != (size_t)fileSize)
        throw "incorrect processed size";
      if (res != 0)
      {
        PrintError_int("Decode error", (int)res);
        return 1;
      }
    }
    
    if (WriteStream(outStream, outBuffer, outSize) != S_OK)
      throw kWriteError;
    
    MyFree(outBuffer);
    MyFree(inBuffer);
  }
  else
  {

  CProgressPrint *progressSpec = NULL;
  CMyComPtr<ICompressProgressInfo> progress;

  if (!stdOutMode)
  {
    progressSpec = new CProgressPrint;
    progress = progressSpec;
  }

>>>>>>> upstream/master
  if (encodeMode)
  {
    NCompress::NLzma::CEncoder *encoderSpec = new NCompress::NLzma::CEncoder;
    CMyComPtr<ICompressCoder> encoder = encoderSpec;

<<<<<<< HEAD
    if (!dictDefined)
      dict = 1 << 23;

=======
>>>>>>> upstream/master
    UInt32 pb = 2;
    UInt32 lc = 3; // = 0; for 32-bit data
    UInt32 lp = 0; // = 2; for 32-bit data
    UInt32 algo = 1;
    UInt32 fb = 128;
    UInt32 mc = 16 + fb / 2;
    bool mcDefined = false;

    bool eos = parser[NKey::kEOS].ThereIs || stdInMode;
 
    ParseUInt32(parser, NKey::kAlgo, algo);
    ParseUInt32(parser, NKey::kFb, fb);
    ParseUInt32(parser, NKey::kLc, lc);
    ParseUInt32(parser, NKey::kLp, lp);
    ParseUInt32(parser, NKey::kPb, pb);

    mcDefined = parser[NKey::kMc].ThereIs;
    if (mcDefined)
<<<<<<< HEAD
      if (!GetNumber(parser[NKey::kMc].PostStrings[0], mc))
        IncorrectCommand();
=======
      mc = GetNumber(parser[NKey::kMc].PostStrings[0]);
>>>>>>> upstream/master
    
    const PROPID propIDs[] =
    {
      NCoderPropID::kDictionarySize,
      NCoderPropID::kPosStateBits,
      NCoderPropID::kLitContextBits,
      NCoderPropID::kLitPosBits,
      NCoderPropID::kAlgorithm,
      NCoderPropID::kNumFastBytes,
      NCoderPropID::kMatchFinder,
      NCoderPropID::kEndMarker,
      NCoderPropID::kNumThreads,
      NCoderPropID::kMatchFinderCycles,
    };
<<<<<<< HEAD
    const int kNumPropsMax = sizeof(propIDs) / sizeof(propIDs[0]);
=======

    const unsigned kNumPropsMax = ARRAY_SIZE(propIDs);
>>>>>>> upstream/master

    PROPVARIANT props[kNumPropsMax];
    for (int p = 0; p < 6; p++)
      props[p].vt = VT_UI4;

    props[0].ulVal = (UInt32)dict;
    props[1].ulVal = (UInt32)pb;
    props[2].ulVal = (UInt32)lc;
    props[3].ulVal = (UInt32)lp;
    props[4].ulVal = (UInt32)algo;
    props[5].ulVal = (UInt32)fb;

    props[6].vt = VT_BSTR;
    props[6].bstrVal = const_cast<BSTR>((const wchar_t *)mf);

    props[7].vt = VT_BOOL;
    props[7].boolVal = eos ? VARIANT_TRUE : VARIANT_FALSE;

    props[8].vt = VT_UI4;
    props[8].ulVal = (UInt32)numThreads;

    // it must be last in property list
    props[9].vt = VT_UI4;
    props[9].ulVal = (UInt32)mc;

<<<<<<< HEAD
    int numProps = kNumPropsMax;
    if (!mcDefined)
      numProps--;

    if (encoderSpec->SetCoderProperties(propIDs, props, numProps) != S_OK)
      IncorrectCommand();
    encoderSpec->WriteCoderProperties(outStream);

    if (eos || stdInMode)
      fileSize = (UInt64)(Int64)-1;
    else
      inStreamSpec->File.GetLength(fileSize);

    for (int i = 0; i < 8; i++)
    {
      Byte b = Byte(fileSize >> (8 * i));
      if (outStream->Write(&b, 1, 0) != S_OK)
      {
        PrintMessage(kWriteError);
        return 1;
      }
    }
    HRESULT result = encoder->Code(inStream, outStream, 0, 0, 0);
    if (result == E_OUTOFMEMORY)
    {
      PrintMessage("\nError: Can not allocate memory\n");
      return 1;
    }
    else if (result != S_OK)
    {
      fprintf(stderr, "\nEncoder error = %X\n", (unsigned int)result);
      return 1;
    }
=======
    unsigned numProps = kNumPropsMax;
    if (!mcDefined)
      numProps--;

    HRESULT res = encoderSpec->SetCoderProperties(propIDs, props, numProps);
    if (res != S_OK)
      return Error_HRESULT("incorrect encoder properties", res);

    if (encoderSpec->WriteCoderProperties(outStream) != S_OK)
      throw kWriteError;

    bool fileSizeWasUsed = true;
    if (eos || stdInMode)
    {
      fileSize = (UInt64)(Int64)-1;
      fileSizeWasUsed = false;
    }

    {
      Byte temp[8];
      for (int i = 0; i < 8; i++)
        temp[i]= (Byte)(fileSize >> (8 * i));
      if (WriteStream(outStream, temp, 8) != S_OK)
        throw kWriteError;
    }
  
    res = encoder->Code(inStream, outStream, NULL, NULL, progress);
    if (progressSpec)
      progressSpec->ClosePrint();

    if (res != S_OK)
      return Error_HRESULT("Encoding error", res);

    UInt64 processedSize = encoderSpec->GetInputProcessedSize();
    
    if (fileSizeWasUsed && processedSize != fileSize)
      throw "Incorrect size of processed data";
>>>>>>> upstream/master
  }
  else
  {
    NCompress::NLzma::CDecoder *decoderSpec = new NCompress::NLzma::CDecoder;
    CMyComPtr<ICompressCoder> decoder = decoderSpec;
<<<<<<< HEAD
    decoderSpec->FinishStream = true;
    const UInt32 kPropertiesSize = 5;
    Byte header[kPropertiesSize + 8];
    if (ReadStream_FALSE(inStream, header, kPropertiesSize + 8) != S_OK)
    {
      PrintMessage(kReadError);
      return 1;
    }
    if (decoderSpec->SetDecoderProperties2(header, kPropertiesSize) != S_OK)
    {
      PrintMessage("SetDecoderProperties error");
      return 1;
    }
    fileSize = 0;
    for (int i = 0; i < 8; i++)
      fileSize |= ((UInt64)header[kPropertiesSize + i]) << (8 * i);

    if (decoder->Code(inStream, outStream, 0, (fileSize == (UInt64)(Int64)-1) ? 0 : &fileSize, 0) != S_OK)
    {
      PrintMessage("Decoder error");
      return 1;
    }
  }
  if (outStreamSpec != NULL)
  {
    if (outStreamSpec->Close() != S_OK)
    {
      PrintMessage("File closing error");
      return 1;
    }
  }
=======
    
    decoderSpec->FinishStream = true;
    
    const unsigned kPropertiesSize = 5;
    Byte header[kPropertiesSize + 8];

    if (ReadStream_FALSE(inStream, header, kPropertiesSize + 8) != S_OK)
      throw kReadError;
    
    if (decoderSpec->SetDecoderProperties2(header, kPropertiesSize) != S_OK)
      throw "SetDecoderProperties error";
    
    UInt64 unpackSize = 0;
    for (int i = 0; i < 8; i++)
      unpackSize |= ((UInt64)header[kPropertiesSize + i]) << (8 * i);

    bool unpackSizeDefined = (unpackSize != (UInt64)(Int64)-1);

    HRESULT res = decoder->Code(inStream, outStream, NULL, unpackSizeDefined ? &unpackSize : NULL, progress);
    if (progressSpec)
      progressSpec->ClosePrint();

    if (res != S_OK)
    {
      if (res == S_FALSE)
      {
        PrintError("Decoding error");
        return 1;
      }
      return Error_HRESULT("Decoding error", res);
    }
    
    if (unpackSizeDefined && unpackSize != decoderSpec->GetOutputProcessedSize())
      throw "incorrect uncompressed size in header";
  }
  }

  if (outStreamSpec)
  {
    if (!stdOutMode)
      Print_Size("Output size: ", outStreamSpec->ProcessedSize);
    if (outStreamSpec->Close() != S_OK)
      throw "File closing error";
  }

>>>>>>> upstream/master
  return 0;
}

int MY_CDECL main(int numArgs, const char *args[])
{
<<<<<<< HEAD
  try { return main2(numArgs, args); }
  catch (const char *s)
  {
    fprintf(stderr, "\nError: %s\n", s);
=======
  NConsoleClose::CCtrlHandlerSetter ctrlHandlerSetter;

  try { return main2(numArgs, args); }
  catch (const char *s)
  {
    PrintError(s);
>>>>>>> upstream/master
    return 1;
  }
  catch(...)
  {
<<<<<<< HEAD
    PrintMessage("\nError\n");
=======
    PrintError("Unknown Error");
>>>>>>> upstream/master
    return 1;
  }
}
