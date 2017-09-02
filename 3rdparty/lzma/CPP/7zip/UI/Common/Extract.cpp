// Extract.cpp

#include "StdAfx.h"

<<<<<<< HEAD
#include <stdio.h>

#include "Windows/FileDir.h"
#include "Windows/PropVariant.h"
#include "Windows/PropVariantConversions.h"
=======
#include "../../../../C/Sort.h"

#include "../../../Common/StringConvert.h"

#include "../../../Windows/FileDir.h"
#include "../../../Windows/PropVariant.h"
#include "../../../Windows/PropVariantConv.h"
>>>>>>> upstream/master

#include "../Common/ExtractingFilePath.h"

#include "Extract.h"
#include "SetProperties.h"

using namespace NWindows;
<<<<<<< HEAD

static HRESULT DecompressArchive(
    const CArc &arc,
    UInt64 packSize,
    const NWildcard::CCensorNode &wildcardCensor,
    const CExtractOptions &options,
    IExtractCallbackUI *callback,
    CArchiveExtractCallback *extractCallbackSpec,
    UString &errorMessage,
    UInt64 &stdInProcessed)
{
  stdInProcessed = 0;
  IInArchive *archive = arc.Archive;
  CRecordVector<UInt32> realIndices;
=======
using namespace NFile;
using namespace NDir;

static HRESULT DecompressArchive(
    CCodecs *codecs,
    const CArchiveLink &arcLink,
    UInt64 packSize,
    const NWildcard::CCensorNode &wildcardCensor,
    const CExtractOptions &options,
    bool calcCrc,
    IExtractCallbackUI *callback,
    CArchiveExtractCallback *ecs,
    UString &errorMessage,
    UInt64 &stdInProcessed)
{
  const CArc &arc = arcLink.Arcs.Back();
  stdInProcessed = 0;
  IInArchive *archive = arc.Archive;
  CRecordVector<UInt32> realIndices;
  
  UStringVector removePathParts;

  FString outDir = options.OutputDir;
  UString replaceName = arc.DefaultName;
  
  if (arcLink.Arcs.Size() > 1)
  {
    // Most "pe" archives have same name of archive subfile "[0]" or ".rsrc_1".
    // So it extracts different archives to one folder.
    // We will use top level archive name
    const CArc &arc0 = arcLink.Arcs[0];
    if (StringsAreEqualNoCase_Ascii(codecs->Formats[arc0.FormatIndex].Name, "pe"))
      replaceName = arc0.DefaultName;
  }

  outDir.Replace(FSTRING_ANY_MASK, us2fs(Get_Correct_FsFile_Name(replaceName)));

  bool elimIsPossible = false;
  UString elimPrefix; // only pure name without dir delimiter
  FString outDirReduced = outDir;
  
  if (options.ElimDup.Val && options.PathMode != NExtract::NPathMode::kAbsPaths)
  {
    UString dirPrefix;
    SplitPathToParts_Smart(fs2us(outDir), dirPrefix, elimPrefix);
    if (!elimPrefix.IsEmpty())
    {
      if (IsPathSepar(elimPrefix.Back()))
        elimPrefix.DeleteBack();
      if (!elimPrefix.IsEmpty())
      {
        outDirReduced = us2fs(dirPrefix);
        elimIsPossible = true;
      }
    }
  }

  bool allFilesAreAllowed = wildcardCensor.AreAllAllowed();

>>>>>>> upstream/master
  if (!options.StdInMode)
  {
    UInt32 numItems;
    RINOK(archive->GetNumberOfItems(&numItems));
    
<<<<<<< HEAD
    for (UInt32 i = 0; i < numItems; i++)
    {
      UString filePath;
      RINOK(arc.GetItemPath(i, filePath));
      bool isFolder;
      RINOK(IsArchiveItemFolder(archive, i, isFolder));
      if (!wildcardCensor.CheckPath(filePath, !isFolder))
        continue;
      realIndices.Add(i);
    }
    if (realIndices.Size() == 0)
    {
      callback->ThereAreNoFiles();
      return S_OK;
    }
  }

  UStringVector removePathParts;

  FString outDir = options.OutputDir;
  outDir.Replace(FSTRING_ANY_MASK, us2fs(GetCorrectFsPath(arc.DefaultName)));
=======
    CReadArcItem item;

    for (UInt32 i = 0; i < numItems; i++)
    {
      if (elimIsPossible || !allFilesAreAllowed)
      {
        RINOK(arc.GetItem(i, item));
      }
      else
      {
        #ifdef SUPPORT_ALT_STREAMS
        item.IsAltStream = false;
        if (!options.NtOptions.AltStreams.Val && arc.Ask_AltStream)
        {
          RINOK(Archive_IsItem_AltStream(arc.Archive, i, item.IsAltStream));
        }
        #endif
      }

      #ifdef SUPPORT_ALT_STREAMS
      if (!options.NtOptions.AltStreams.Val && item.IsAltStream)
        continue;
      #endif
      
      if (elimIsPossible)
      {
        const UString &s =
          #ifdef SUPPORT_ALT_STREAMS
            item.MainPath;
          #else
            item.Path;
          #endif
        if (!IsPath1PrefixedByPath2(s, elimPrefix))
          elimIsPossible = false;
        else
        {
          wchar_t c = s[elimPrefix.Len()];
          if (c == 0)
          {
            if (!item.MainIsDir)
              elimIsPossible = false;
          }
          else if (!IsPathSepar(c))
            elimIsPossible = false;
        }
      }

      if (!allFilesAreAllowed)
      {
        if (!CensorNode_CheckPath(wildcardCensor, item))
          continue;
      }

      realIndices.Add(i);
    }
    
    if (realIndices.Size() == 0)
    {
      callback->ThereAreNoFiles();
      return callback->ExtractResult(S_OK);
    }
  }

  if (elimIsPossible)
  {
    removePathParts.Add(elimPrefix);
    // outDir = outDirReduced;
  }

>>>>>>> upstream/master
  #ifdef _WIN32
  // GetCorrectFullFsPath doesn't like "..".
  // outDir.TrimRight();
  // outDir = GetCorrectFullFsPath(outDir);
  #endif

<<<<<<< HEAD
  if (!outDir.IsEmpty())
    if (!NFile::NDirectory::CreateComplexDirectory(outDir))
    {
      HRESULT res = ::GetLastError();
      if (res == S_OK)
        res = E_FAIL;
      errorMessage = ((UString)L"Can not create output directory ") + fs2us(outDir);
      return res;
    }

  extractCallbackSpec->Init(
      options.StdInMode ? &wildcardCensor : NULL,
      &arc,
      callback,
      options.StdOutMode, options.TestMode, options.CalcCrc,
      outDir,
      removePathParts,
      packSize);

  #if !defined(_7ZIP_ST) && !defined(_SFX)
  RINOK(SetProperties(archive, options.Properties));
  #endif

  HRESULT result;
  Int32 testMode = (options.TestMode && !options.CalcCrc) ? 1: 0;
  if (options.StdInMode)
  {
    result = archive->Extract(NULL, (UInt32)(Int32)-1, testMode, extractCallbackSpec);
    NCOM::CPropVariant prop;
    if (archive->GetArchiveProperty(kpidPhySize, &prop) == S_OK)
      if (prop.vt == VT_UI8 || prop.vt == VT_UI4)
        stdInProcessed = ConvertPropVariantToUInt64(prop);
  }
  else
    result = archive->Extract(&realIndices.Front(), realIndices.Size(), testMode, extractCallbackSpec);

  return callback->ExtractResult(result);
}

HRESULT DecompressArchives(
    CCodecs *codecs, const CIntVector &formatIndices,
=======
  if (outDir.IsEmpty())
    outDir = FTEXT(".") FSTRING_PATH_SEPARATOR;
  /*
  #ifdef _WIN32
  else if (NName::IsAltPathPrefix(outDir)) {}
  #endif
  */
  else if (!CreateComplexDir(outDir))
  {
    HRESULT res = ::GetLastError();
    if (res == S_OK)
      res = E_FAIL;
    errorMessage.SetFromAscii("Can not create output directory: ");
    errorMessage += fs2us(outDir);
    return res;
  }

  ecs->Init(
      options.NtOptions,
      options.StdInMode ? &wildcardCensor : NULL,
      &arc,
      callback,
      options.StdOutMode, options.TestMode,
      outDir,
      removePathParts, false,
      packSize);

  
  #ifdef SUPPORT_LINKS
  
  if (!options.StdInMode &&
      !options.TestMode &&
      options.NtOptions.HardLinks.Val)
  {
    RINOK(ecs->PrepareHardLinks(&realIndices));
  }
    
  #endif

  
  HRESULT result;
  Int32 testMode = (options.TestMode && !calcCrc) ? 1: 0;
  if (options.StdInMode)
  {
    result = archive->Extract(NULL, (UInt32)(Int32)-1, testMode, ecs);
    NCOM::CPropVariant prop;
    if (archive->GetArchiveProperty(kpidPhySize, &prop) == S_OK)
      ConvertPropVariantToUInt64(prop, stdInProcessed);
  }
  else
    result = archive->Extract(&realIndices.Front(), realIndices.Size(), testMode, ecs);
  if (result == S_OK && !options.StdInMode)
    result = ecs->SetDirsTimes();
  return callback->ExtractResult(result);
}

/* v9.31: BUG was fixed:
   Sorted list for file paths was sorted with case insensitive compare function.
   But FindInSorted function did binary search via case sensitive compare function */

int Find_FileName_InSortedVector(const UStringVector &fileName, const UString &name)
{
  unsigned left = 0, right = fileName.Size();
  while (left != right)
  {
    unsigned mid = (left + right) / 2;
    const UString &midValue = fileName[mid];
    int compare = CompareFileNames(name, midValue);
    if (compare == 0)
      return mid;
    if (compare < 0)
      right = mid;
    else
      left = mid + 1;
  }
  return -1;
}

HRESULT Extract(
    CCodecs *codecs,
    const CObjectVector<COpenType> &types,
    const CIntVector &excludedFormats,
>>>>>>> upstream/master
    UStringVector &arcPaths, UStringVector &arcPathsFull,
    const NWildcard::CCensorNode &wildcardCensor,
    const CExtractOptions &options,
    IOpenCallbackUI *openCallback,
    IExtractCallbackUI *extractCallback,
<<<<<<< HEAD
    UString &errorMessage,
    CDecompressStat &stat)
{
  stat.Clear();
  int i;
  UInt64 totalPackSize = 0;
  CRecordVector<UInt64> archiveSizes;

  int numArcs = options.StdInMode ? 1 : arcPaths.Size();

  for (i = 0; i < numArcs; i++)
  {
    NFile::NFind::CFileInfo fi;
=======
    #ifndef _SFX
    IHashCalc *hash,
    #endif
    UString &errorMessage,
    CDecompressStat &st)
{
  st.Clear();
  UInt64 totalPackSize = 0;
  CRecordVector<UInt64> arcSizes;

  unsigned numArcs = options.StdInMode ? 1 : arcPaths.Size();

  unsigned i;
  
  for (i = 0; i < numArcs; i++)
  {
    NFind::CFileInfo fi;
>>>>>>> upstream/master
    fi.Size = 0;
    if (!options.StdInMode)
    {
      const FString &arcPath = us2fs(arcPaths[i]);
      if (!fi.Find(arcPath))
        throw "there is no such archive";
      if (fi.IsDir())
        throw "can't decompress folder";
    }
<<<<<<< HEAD
    archiveSizes.Add(fi.Size);
    totalPackSize += fi.Size;
  }
  CArchiveExtractCallback *extractCallbackSpec = new CArchiveExtractCallback;
  CMyComPtr<IArchiveExtractCallback> ec(extractCallbackSpec);
  bool multi = (numArcs > 1);
  extractCallbackSpec->InitForMulti(multi, options.PathMode, options.OverwriteMode);
=======
    arcSizes.Add(fi.Size);
    totalPackSize += fi.Size;
  }

  CBoolArr skipArcs(numArcs);
  for (i = 0; i < numArcs; i++)
    skipArcs[i] = false;

  CArchiveExtractCallback *ecs = new CArchiveExtractCallback;
  CMyComPtr<IArchiveExtractCallback> ec(ecs);
  bool multi = (numArcs > 1);
  ecs->InitForMulti(multi, options.PathMode, options.OverwriteMode);
  #ifndef _SFX
  ecs->SetHashMethods(hash);
  #endif

>>>>>>> upstream/master
  if (multi)
  {
    RINOK(extractCallback->SetTotal(totalPackSize));
  }
<<<<<<< HEAD
  for (i = 0; i < numArcs; i++)
  {
    const UString &arcPath = arcPaths[i];
    NFile::NFind::CFileInfo fi;
=======

  UInt64 totalPackProcessed = 0;
  bool thereAreNotOpenArcs = false;
  
  for (i = 0; i < numArcs; i++)
  {
    if (skipArcs[i])
      continue;

    const UString &arcPath = arcPaths[i];
    NFind::CFileInfo fi;
>>>>>>> upstream/master
    if (options.StdInMode)
    {
      fi.Size = 0;
      fi.Attrib = 0;
    }
    else
    {
      if (!fi.Find(us2fs(arcPath)) || fi.IsDir())
        throw "there is no such archive";
    }

<<<<<<< HEAD
    #ifndef _NO_CRYPTO
    openCallback->Open_ClearPasswordWasAskedFlag();
    #endif

    RINOK(extractCallback->BeforeOpen(arcPath));
    CArchiveLink archiveLink;

    CIntVector formatIndices2 = formatIndices;
    #ifndef _SFX
    if (formatIndices.IsEmpty())
=======
    /*
    #ifndef _NO_CRYPTO
    openCallback->Open_Clear_PasswordWasAsked_Flag();
    #endif
    */

    RINOK(extractCallback->BeforeOpen(arcPath, options.TestMode));
    CArchiveLink arcLink;

    CObjectVector<COpenType> types2 = types;
    /*
    #ifndef _SFX
    if (types.IsEmpty())
>>>>>>> upstream/master
    {
      int pos = arcPath.ReverseFind(L'.');
      if (pos >= 0)
      {
<<<<<<< HEAD
        UString s = arcPath.Mid(pos + 1);
=======
        UString s = arcPath.Ptr(pos + 1);
>>>>>>> upstream/master
        int index = codecs->FindFormatForExtension(s);
        if (index >= 0 && s == L"001")
        {
          s = arcPath.Left(pos);
          pos = s.ReverseFind(L'.');
          if (pos >= 0)
          {
<<<<<<< HEAD
            int index2 = codecs->FindFormatForExtension(s.Mid(pos + 1));
            if (index2 >= 0 && s.CompareNoCase(L"rar") != 0)
            {
              formatIndices2.Add(index2);
              formatIndices2.Add(index);
=======
            int index2 = codecs->FindFormatForExtension(s.Ptr(pos + 1));
            if (index2 >= 0) // && s.CompareNoCase(L"rar") != 0
            {
              types2.Add(index2);
              types2.Add(index);
>>>>>>> upstream/master
            }
          }
        }
      }
    }
    #endif
<<<<<<< HEAD
    HRESULT result = archiveLink.Open2(codecs, formatIndices2, options.StdInMode, NULL, arcPath, openCallback);
    if (result == E_ABORT)
      return result;

    bool crypted = false;
    #ifndef _NO_CRYPTO
    crypted = openCallback->Open_WasPasswordAsked();
    #endif

    RINOK(extractCallback->OpenResult(arcPath, result, crypted));
    if (result != S_OK)
      continue;

    if (!options.StdInMode)
    for (int v = 0; v < archiveLink.VolumePaths.Size(); v++)
    {
      int index = arcPathsFull.FindInSorted(archiveLink.VolumePaths[v]);
      if (index >= 0 && index > i)
      {
        arcPaths.Delete(index);
        arcPathsFull.Delete(index);
        totalPackSize -= archiveSizes[index];
        archiveSizes.Delete(index);
        numArcs = arcPaths.Size();
      }
    }
    if (archiveLink.VolumePaths.Size() != 0)
    {
      totalPackSize += archiveLink.VolumesSize;
      RINOK(extractCallback->SetTotal(totalPackSize));
    }

    #ifndef _NO_CRYPTO
    UString password;
    RINOK(openCallback->Open_GetPasswordIfAny(password));
    if (!password.IsEmpty())
=======
    */

    COpenOptions op;
    #ifndef _SFX
    op.props = &options.Properties;
    #endif
    op.codecs = codecs;
    op.types = &types2;
    op.excludedFormats = &excludedFormats;
    op.stdInMode = options.StdInMode;
    op.stream = NULL;
    op.filePath = arcPath;

    HRESULT result = arcLink.Open_Strict(op, openCallback);

    if (result == E_ABORT)
      return result;

    // arcLink.Set_ErrorsText();
    RINOK(extractCallback->OpenResult(codecs, arcLink, arcPath, result));

    if (result != S_OK)
    {
      thereAreNotOpenArcs = true;
      if (!options.StdInMode)
      {
        NFind::CFileInfo fi2;
        if (fi2.Find(us2fs(arcPath)))
          if (!fi2.IsDir())
            totalPackProcessed += fi2.Size;
      }
      continue;
    }

    if (!options.StdInMode)
    {
      // numVolumes += arcLink.VolumePaths.Size();
      // arcLink.VolumesSize;

      // totalPackSize -= DeleteUsedFileNamesFromList(arcLink, i + 1, arcPaths, arcPathsFull, &arcSizes);
      // numArcs = arcPaths.Size();
      if (arcLink.VolumePaths.Size() != 0)
      {
        Int64 correctionSize = arcLink.VolumesSize;
        FOR_VECTOR (v, arcLink.VolumePaths)
        {
          int index = Find_FileName_InSortedVector(arcPathsFull, arcLink.VolumePaths[v]);
          if (index >= 0)
          {
            if ((unsigned)index > i)
            {
              skipArcs[(unsigned)index] = true;
              correctionSize -= arcSizes[(unsigned)index];
            }
          }
        }
        if (correctionSize != 0)
        {
          Int64 newPackSize = (Int64)totalPackSize + correctionSize;
          if (newPackSize < 0)
            newPackSize = 0;
          totalPackSize = newPackSize;
          RINOK(extractCallback->SetTotal(totalPackSize));
        }
      }
    }

    /*
    // Now openCallback and extractCallback use same object. So we don't need to send password.

    #ifndef _NO_CRYPTO
    bool passwordIsDefined;
    UString password;
    RINOK(openCallback->Open_GetPasswordIfAny(passwordIsDefined, password));
    if (passwordIsDefined)
>>>>>>> upstream/master
    {
      RINOK(extractCallback->SetPassword(password));
    }
    #endif
<<<<<<< HEAD

    for (int v = 0; v < archiveLink.Arcs.Size(); v++)
    {
      const UString &s = archiveLink.Arcs[v].ErrorMessage;
      if (!s.IsEmpty())
      {
        RINOK(extractCallback->MessageError(s));
      }
    }

    CArc &arc = archiveLink.Arcs.Back();
=======
    */

    CArc &arc = arcLink.Arcs.Back();
>>>>>>> upstream/master
    arc.MTimeDefined = (!options.StdInMode && !fi.IsDevice);
    arc.MTime = fi.MTime;

    UInt64 packProcessed;
<<<<<<< HEAD
    RINOK(DecompressArchive(arc,
        fi.Size + archiveLink.VolumesSize,
        wildcardCensor, options, extractCallback, extractCallbackSpec, errorMessage, packProcessed));
    if (!options.StdInMode)
      packProcessed = fi.Size + archiveLink.VolumesSize;
    extractCallbackSpec->LocalProgressSpec->InSize += packProcessed;
    extractCallbackSpec->LocalProgressSpec->OutSize = extractCallbackSpec->UnpackSize;
    if (!errorMessage.IsEmpty())
      return E_FAIL;
  }
  stat.NumFolders = extractCallbackSpec->NumFolders;
  stat.NumFiles = extractCallbackSpec->NumFiles;
  stat.UnpackSize = extractCallbackSpec->UnpackSize;
  stat.CrcSum = extractCallbackSpec->CrcSum;

  stat.NumArchives = arcPaths.Size();
  stat.PackSize = extractCallbackSpec->LocalProgressSpec->InSize;
=======
    bool calcCrc =
        #ifndef _SFX
          (hash != NULL);
        #else
          false;
        #endif

    RINOK(DecompressArchive(
        codecs,
        arcLink,
        fi.Size + arcLink.VolumesSize,
        wildcardCensor,
        options,
        calcCrc,
        extractCallback, ecs, errorMessage, packProcessed));

    if (!options.StdInMode)
      packProcessed = fi.Size + arcLink.VolumesSize;
    totalPackProcessed += packProcessed;
    ecs->LocalProgressSpec->InSize += packProcessed;
    ecs->LocalProgressSpec->OutSize = ecs->UnpackSize;
    if (!errorMessage.IsEmpty())
      return E_FAIL;
  }

  if (multi || thereAreNotOpenArcs)
  {
    RINOK(extractCallback->SetTotal(totalPackSize));
    RINOK(extractCallback->SetCompleted(&totalPackProcessed));
  }

  st.NumFolders = ecs->NumFolders;
  st.NumFiles = ecs->NumFiles;
  st.NumAltStreams = ecs->NumAltStreams;
  st.UnpackSize = ecs->UnpackSize;
  st.AltStreams_UnpackSize = ecs->AltStreams_UnpackSize;
  st.NumArchives = arcPaths.Size();
  st.PackSize = ecs->LocalProgressSpec->InSize;
>>>>>>> upstream/master
  return S_OK;
}
