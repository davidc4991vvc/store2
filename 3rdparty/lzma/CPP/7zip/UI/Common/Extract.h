// Extract.h

#ifndef __EXTRACT_H
#define __EXTRACT_H

<<<<<<< HEAD
#include "Windows/FileFind.h"
=======
#include "../../../Windows/FileFind.h"
>>>>>>> upstream/master

#include "../../Archive/IArchive.h"

#include "ArchiveExtractCallback.h"
#include "ArchiveOpenCallback.h"
#include "ExtractMode.h"
#include "Property.h"

#include "../Common/LoadCodecs.h"

<<<<<<< HEAD
struct CExtractOptions
=======
struct CExtractOptionsBase
{
  CBoolPair ElimDup;
  
  bool PathMode_Force;
  bool OverwriteMode_Force;
  NExtract::NPathMode::EEnum PathMode;
  NExtract::NOverwriteMode::EEnum OverwriteMode;
  
  FString OutputDir;
  CExtractNtOptions NtOptions;

  CExtractOptionsBase():
      PathMode_Force(false),
      OverwriteMode_Force(false),
      PathMode(NExtract::NPathMode::kFullPaths),
      OverwriteMode(NExtract::NOverwriteMode::kAsk)
      {}
};

struct CExtractOptions: public CExtractOptionsBase
>>>>>>> upstream/master
{
  bool StdInMode;
  bool StdOutMode;
  bool YesToAll;
  bool TestMode;
<<<<<<< HEAD
  bool CalcCrc;
  NExtract::NPathMode::EEnum PathMode;
  NExtract::NOverwriteMode::EEnum OverwriteMode;
  FString OutputDir;
=======
>>>>>>> upstream/master
  
  // bool ShowDialog;
  // bool PasswordEnabled;
  // UString Password;
<<<<<<< HEAD
  #if !defined(_7ZIP_ST) && !defined(_SFX)
=======
  #ifndef _SFX
>>>>>>> upstream/master
  CObjectVector<CProperty> Properties;
  #endif

  #ifdef EXTERNAL_CODECS
  CCodecs *Codecs;
  #endif

  CExtractOptions():
<<<<<<< HEAD
      StdInMode(false),
      StdOutMode(false),
      YesToAll(false),
      TestMode(false),
      CalcCrc(false),
      PathMode(NExtract::NPathMode::kFullPathnames),
      OverwriteMode(NExtract::NOverwriteMode::kAskBefore)
=======
      TestMode(false),
      StdInMode(false),
      StdOutMode(false),
      YesToAll(false)
>>>>>>> upstream/master
      {}
};

struct CDecompressStat
{
  UInt64 NumArchives;
  UInt64 UnpackSize;
<<<<<<< HEAD
  UInt64 PackSize;
  UInt64 NumFolders;
  UInt64 NumFiles;
  UInt32 CrcSum;

  void Clear()
  {
    NumArchives = UnpackSize = PackSize = NumFolders = NumFiles = 0;
    CrcSum = 0;
  }
};

HRESULT DecompressArchives(
    CCodecs *codecs, const CIntVector &formatIndices,
=======
  UInt64 AltStreams_UnpackSize;
  UInt64 PackSize;
  UInt64 NumFolders;
  UInt64 NumFiles;
  UInt64 NumAltStreams;

  void Clear()
  {
    NumArchives = UnpackSize = AltStreams_UnpackSize = PackSize = NumFolders = NumFiles = NumAltStreams = 0;
  }
};

HRESULT Extract(
    CCodecs *codecs,
    const CObjectVector<COpenType> &types,
    const CIntVector &excludedFormats,
>>>>>>> upstream/master
    UStringVector &archivePaths, UStringVector &archivePathsFull,
    const NWildcard::CCensorNode &wildcardCensor,
    const CExtractOptions &options,
    IOpenCallbackUI *openCallback,
    IExtractCallbackUI *extractCallback,
<<<<<<< HEAD
    UString &errorMessage,
    CDecompressStat &stat);
=======
    #ifndef _SFX
    IHashCalc *hash,
    #endif
    UString &errorMessage,
    CDecompressStat &st);
>>>>>>> upstream/master

#endif
