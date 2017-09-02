// 7zUpdate.h

#ifndef __7Z_UPDATE_H
#define __7Z_UPDATE_H

<<<<<<< HEAD
=======
#include "../IArchive.h"

// #include "../../Common/UniqBlocks.h"

>>>>>>> upstream/master
#include "7zCompressionMode.h"
#include "7zIn.h"
#include "7zOut.h"

<<<<<<< HEAD
#include "../IArchive.h"

namespace NArchive {
namespace N7z {

=======
namespace NArchive {
namespace N7z {

/*
struct CTreeFolder
{
  UString Name;
  int Parent;
  CIntVector SubFolders;
  int UpdateItemIndex;
  int SortIndex;
  int SortIndexEnd;

  CTreeFolder(): UpdateItemIndex(-1) {}
};
*/

>>>>>>> upstream/master
struct CUpdateItem
{
  int IndexInArchive;
  int IndexInClient;
  
  UInt64 CTime;
  UInt64 ATime;
  UInt64 MTime;

  UInt64 Size;
  UString Name;
<<<<<<< HEAD
=======
  /*
  bool IsAltStream;
  int ParentFolderIndex;
  int TreeFolderIndex;
  */

  // that code is not used in 9.26
  // int ParentSortIndex;
  // int ParentSortIndexEnd;
>>>>>>> upstream/master

  UInt32 Attrib;
  
  bool NewData;
  bool NewProps;

  bool IsAnti;
  bool IsDir;

  bool AttribDefined;
  bool CTimeDefined;
  bool ATimeDefined;
  bool MTimeDefined;

<<<<<<< HEAD
  bool HasStream() const { return !IsDir && !IsAnti && Size != 0; }

  CUpdateItem():
=======
  // int SecureIndex; // 0 means (no_security)

  bool HasStream() const { return !IsDir && !IsAnti && Size != 0; }
  // bool HasStream() const { return !IsDir && !IsAnti /* && Size != 0 */; } // for test purposes

  CUpdateItem():
      // ParentSortIndex(-1),
      // IsAltStream(false),
>>>>>>> upstream/master
      IsAnti(false),
      IsDir(false),
      AttribDefined(false),
      CTimeDefined(false),
      ATimeDefined(false),
      MTimeDefined(false)
<<<<<<< HEAD
      {}
  void SetDirStatusFromAttrib() { IsDir = ((Attrib & FILE_ATTRIBUTE_DIRECTORY) != 0); };

  int GetExtensionPos() const;
  UString GetExtension() const;
=======
      // SecureIndex(0)
      {}
  void SetDirStatusFromAttrib() { IsDir = ((Attrib & FILE_ATTRIBUTE_DIRECTORY) != 0); }

  // unsigned GetExtensionPos() const;
  // UString GetExtension() const;
>>>>>>> upstream/master
};

struct CUpdateOptions
{
  const CCompressionMethodMode *Method;
  const CCompressionMethodMode *HeaderMethod;
<<<<<<< HEAD
  bool UseFilters;
  bool MaxFilter;
=======
  bool UseFilters; // use additional filters for some files
  bool MaxFilter;  // use BCJ2 filter instead of BCJ
  int AnalysisLevel;
>>>>>>> upstream/master

  CHeaderOptions HeaderOptions;

  UInt64 NumSolidFiles;
  UInt64 NumSolidBytes;
  bool SolidExtension;
<<<<<<< HEAD
  bool RemoveSfxBlock;
  bool VolumeMode;
=======
  
  bool UseTypeSorting;
  
  bool RemoveSfxBlock;
  bool MultiThreadMixer;

  CUpdateOptions():
      Method(NULL),
      HeaderMethod(NULL),
      UseFilters(false),
      MaxFilter(false),
      AnalysisLevel(-1),
      NumSolidFiles((UInt64)(Int64)(-1)),
      NumSolidBytes((UInt64)(Int64)(-1)),
      SolidExtension(false),
      UseTypeSorting(true),
      RemoveSfxBlock(false),
      MultiThreadMixer(true)
    {}
>>>>>>> upstream/master
};

HRESULT Update(
    DECL_EXTERNAL_CODECS_LOC_VARS
    IInStream *inStream,
<<<<<<< HEAD
    const CArchiveDatabaseEx *db,
    const CObjectVector<CUpdateItem> &updateItems,
    COutArchive &archive,
    CArchiveDatabase &newDatabase,
=======
    const CDbEx *db,
    const CObjectVector<CUpdateItem> &updateItems,
    // const CObjectVector<CTreeFolder> &treeFolders, // treeFolders[0] is root
    // const CUniqBlocks &secureBlocks,
    COutArchive &archive,
    CArchiveDatabaseOut &newDatabase,
>>>>>>> upstream/master
    ISequentialOutStream *seqOutStream,
    IArchiveUpdateCallback *updateCallback,
    const CUpdateOptions &options
    #ifndef _NO_CRYPTO
    , ICryptoGetTextPassword *getDecoderPassword
    #endif
    );
}}

#endif
