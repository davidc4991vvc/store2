// LoadCodecs.h

#ifndef __LOAD_CODECS_H
#define __LOAD_CODECS_H

<<<<<<< HEAD
#include "../../../Common/MyCom.h"
#include "../../../Common/MyString.h"
#include "../../../Common/Buffer.h"
#include "../../ICoder.h"
=======
/*
Client application uses LoadCodecs.* to load plugins to
CCodecs object, that contains 3 lists of plugins:
  1) Formats - internal and external archive handlers
  2) Codecs  - external codecs
  3) Hashers - external hashers

EXTERNAL_CODECS
---------------

  if EXTERNAL_CODECS is defined, then the code tries to load external
  plugins from DLL files (shared libraries).

  There are two types of executables in 7-Zip:
  
  1) Executable that uses external plugins must be compiled
     with EXTERNAL_CODECS defined:
       - 7z.exe, 7zG.exe, 7zFM.exe
    
     Note: EXTERNAL_CODECS is used also in CPP/7zip/Common/CreateCoder.h
           that code is used in plugin module (7z.dll).
  
  2) Standalone modules are compiled without EXTERNAL_CODECS:
    - SFX modules: 7z.sfx, 7zCon.sfx
    - standalone versions of console 7-Zip: 7za.exe, 7zr.exe

  if EXTERNAL_CODECS is defined, CCodecs class implements interfaces:
    - ICompressCodecsInfo : for Codecs
    - IHashers            : for Hashers
  
  The client application can send CCodecs object to each plugin module.
  And plugin module can use ICompressCodecsInfo or IHashers interface to access
  another plugins.

  There are 2 ways to send (ICompressCodecsInfo * compressCodecsInfo) to plugin
    1) for old versions:
        a) request ISetCompressCodecsInfo from created archive handler.
        b) call ISetCompressCodecsInfo::SetCompressCodecsInfo(compressCodecsInfo)
    2) for new versions:
        a) request "SetCodecs" function from DLL file
        b) call SetCodecs(compressCodecsInfo) function from DLL file
*/

#include "../../../Common/MyBuffer.h"
#include "../../../Common/MyCom.h"
#include "../../../Common/MyString.h"
#include "../../../Common/ComTry.h"
>>>>>>> upstream/master

#ifdef EXTERNAL_CODECS
#include "../../../Windows/DLL.h"
#endif

<<<<<<< HEAD
struct CDllCodecInfo
{
  CLSID Encoder;
  CLSID Decoder;
  bool EncoderIsAssigned;
  bool DecoderIsAssigned;
  int LibIndex;
  UInt32 CodecIndex;
};

#include "../../Archive/IArchive.h"

typedef IInArchive * (*CreateInArchiveP)();
typedef IOutArchive * (*CreateOutArchiveP)();
=======
#include "../../ICoder.h"

#include "../../Archive/IArchive.h"


#ifdef EXTERNAL_CODECS

struct CDllCodecInfo
{
  unsigned LibIndex;
  UInt32 CodecIndex;
  bool EncoderIsAssigned;
  bool DecoderIsAssigned;
  CLSID Encoder;
  CLSID Decoder;
};

struct CDllHasherInfo
{
  unsigned LibIndex;
  UInt32 HasherIndex;
};

#endif
>>>>>>> upstream/master

struct CArcExtInfo
{
  UString Ext;
  UString AddExt;
<<<<<<< HEAD
=======
  
>>>>>>> upstream/master
  CArcExtInfo() {}
  CArcExtInfo(const UString &ext): Ext(ext) {}
  CArcExtInfo(const UString &ext, const UString &addExt): Ext(ext), AddExt(addExt) {}
};


struct CArcInfoEx
{
<<<<<<< HEAD
  #ifdef EXTERNAL_CODECS
  int LibIndex;
  UInt32 FormatIndex;
  CLSID ClassID;
  #endif
  bool UpdateEnabled;
  CreateInArchiveP CreateInArchive;
  CreateOutArchiveP CreateOutArchive;
  UString Name;
  CObjectVector<CArcExtInfo> Exts;
  #ifndef _SFX
  CByteBuffer StartSignature;
  // CByteBuffer FinishSignature;
  #ifdef NEW_FOLDER_INTERFACE
  UStringVector AssociateExts;
  #endif
  #endif
  bool KeepName;
=======
  UInt32 Flags;
  
  Func_CreateInArchive CreateInArchive;
  Func_IsArc IsArcFunc;

  UString Name;
  CObjectVector<CArcExtInfo> Exts;
  
  #ifndef _SFX
    Func_CreateOutArchive CreateOutArchive;
    bool UpdateEnabled;
    bool NewInterface;
    // UInt32 Version;
    UInt32 SignatureOffset;
    CObjectVector<CByteBuffer> Signatures;
    #ifdef NEW_FOLDER_INTERFACE
      UStringVector AssociateExts;
    #endif
  #endif
  
  #ifdef EXTERNAL_CODECS
    int LibIndex;
    UInt32 FormatIndex;
    CLSID ClassID;
  #endif

  bool Flags_KeepName() const { return (Flags & NArcInfoFlags::kKeepName) != 0; }
  bool Flags_FindSignature() const { return (Flags & NArcInfoFlags::kFindSignature) != 0; }

  bool Flags_AltStreams() const { return (Flags & NArcInfoFlags::kAltStreams) != 0; }
  bool Flags_NtSecure() const { return (Flags & NArcInfoFlags::kNtSecure) != 0; }
  bool Flags_SymLinks() const { return (Flags & NArcInfoFlags::kSymLinks) != 0; }
  bool Flags_HardLinks() const { return (Flags & NArcInfoFlags::kHardLinks) != 0; }

  bool Flags_UseGlobalOffset() const { return (Flags & NArcInfoFlags::kUseGlobalOffset) != 0; }
  bool Flags_StartOpen() const { return (Flags & NArcInfoFlags::kStartOpen) != 0; }
  bool Flags_BackwardOpen() const { return (Flags & NArcInfoFlags::kBackwardOpen) != 0; }
  bool Flags_PreArc() const { return (Flags & NArcInfoFlags::kPreArc) != 0; }
  bool Flags_PureStartOpen() const { return (Flags & NArcInfoFlags::kPureStartOpen) != 0; }
>>>>>>> upstream/master
  
  UString GetMainExt() const
  {
    if (Exts.IsEmpty())
      return UString();
    return Exts[0].Ext;
  }
  int FindExtension(const UString &ext) const;
  
  /*
  UString GetAllExtensions() const
  {
    UString s;
    for (int i = 0; i < Exts.Size(); i++)
    {
      if (i > 0)
        s += ' ';
      s += Exts[i].Ext;
    }
    return s;
  }
  */

<<<<<<< HEAD
  void AddExts(const wchar_t* ext, const wchar_t* addExt);

  CArcInfoEx():
    #ifdef EXTERNAL_CODECS
    LibIndex(-1),
    #endif
    UpdateEnabled(false),
    CreateInArchive(0), CreateOutArchive(0),
    KeepName(false)
    #ifndef _SFX
    #endif
  {}
};

#ifdef EXTERNAL_CODECS
typedef UInt32 (WINAPI *GetMethodPropertyFunc)(UInt32 index, PROPID propID, PROPVARIANT *value);
typedef UInt32 (WINAPI *CreateObjectFunc)(const GUID *clsID, const GUID *interfaceID, void **outObject);


#ifdef NEW_FOLDER_INTERFACE
=======
  void AddExts(const UString &ext, const UString &addExt);

  bool IsSplit() const { return StringsAreEqualNoCase_Ascii(Name, "Split"); }
  // bool IsRar() const { return StringsAreEqualNoCase_Ascii(Name, "Rar"); }

  CArcInfoEx():
      Flags(0),
      CreateInArchive(NULL),
      IsArcFunc(NULL)
      #ifndef _SFX
      , CreateOutArchive(NULL)
      , UpdateEnabled(false)
      , NewInterface(false)
      // , Version(0)
      , SignatureOffset(0)
      #endif
      #ifdef EXTERNAL_CODECS
      , LibIndex(-1)
      #endif
  {}
};

#ifdef NEW_FOLDER_INTERFACE

>>>>>>> upstream/master
struct CCodecIcons
{
  struct CIconPair
  {
    UString Ext;
    int IconIndex;
  };
  CObjectVector<CIconPair> IconPairs;
<<<<<<< HEAD
  void LoadIcons(HMODULE m);
  bool FindIconIndex(const UString &ext, int &iconIndex) const;
};
#endif

struct CCodecLib
#ifdef NEW_FOLDER_INTERFACE
: public CCodecIcons
#endif
{
  NWindows::NDLL::CLibrary Lib;
  GetMethodPropertyFunc GetMethodProperty;
  CreateObjectFunc CreateObject;
  #ifdef NEW_FOLDER_INTERFACE
  FString Path;
  void LoadIcons() { CCodecIcons::LoadIcons((HMODULE)Lib); }
  #endif
  CCodecLib(): GetMethodProperty(0) {}
};
#endif

class CCodecs:
  #ifdef EXTERNAL_CODECS
  public ICompressCodecsInfo,
  #else
  public IUnknown,
  #endif
  public CMyUnknownImp
{
public:
  #ifdef EXTERNAL_CODECS
  CObjectVector<CCodecLib> Libs;
  CObjectVector<CDllCodecInfo> Codecs;

  #ifdef NEW_FOLDER_INTERFACE
  CCodecIcons InternalIcons;
  #endif

  HRESULT LoadCodecs();
  HRESULT LoadFormats();
  HRESULT LoadDll(const FString &path, bool needCheckDll);
  HRESULT LoadDllsFromFolder(const FString &folderPrefix);

  HRESULT CreateArchiveHandler(const CArcInfoEx &ai, void **archive, bool outHandler) const
  {
    return Libs[ai.LibIndex].CreateObject(&ai.ClassID, outHandler ? &IID_IOutArchive : &IID_IInArchive, (void **)archive);
  }
  #endif

public:
  CObjectVector<CArcInfoEx> Formats;
=======

  void LoadIcons(HMODULE m);
  bool FindIconIndex(const UString &ext, int &iconIndex) const;
};

#endif

#ifdef EXTERNAL_CODECS

struct CCodecLib
  #ifdef NEW_FOLDER_INTERFACE
    : public CCodecIcons
  #endif
{
  NWindows::NDLL::CLibrary Lib;
  FString Path;
  
  Func_CreateObject CreateObject;
  Func_GetMethodProperty GetMethodProperty;
  Func_CreateDecoder CreateDecoder;
  Func_CreateEncoder CreateEncoder;
  Func_SetCodecs SetCodecs;

  CMyComPtr<IHashers> ComHashers;
  
  #ifdef NEW_FOLDER_INTERFACE
  void LoadIcons() { CCodecIcons::LoadIcons((HMODULE)Lib); }
  #endif
  
  CCodecLib():
      CreateObject(NULL),
      GetMethodProperty(NULL),
      CreateDecoder(NULL),
      CreateEncoder(NULL),
      SetCodecs(NULL)
      {}
};

#endif


class CCodecs:
  #ifdef EXTERNAL_CODECS
    public ICompressCodecsInfo,
    public IHashers,
  #else
    public IUnknown,
  #endif
  public CMyUnknownImp
{
  CLASS_NO_COPY(CCodecs);
public:
  #ifdef EXTERNAL_CODECS
  
  CObjectVector<CCodecLib> Libs;
  FString MainDll_ErrorPath;

  void CloseLibs();

  class CReleaser
  {
    CLASS_NO_COPY(CReleaser);

    /* CCodecsReleaser object releases CCodecs links.
         1) CCodecs is COM object that is deleted when all links to that object will be released/
         2) CCodecs::Libs[i] can hold (ICompressCodecsInfo *) link to CCodecs object itself.
       To break that reference loop, we must close all CCodecs::Libs in CCodecsReleaser desttructor. */

    CCodecs *_codecs;
      
    public:
    CReleaser(): _codecs(NULL) {}
    void Set(CCodecs *codecs) { _codecs = codecs; }
    ~CReleaser() { if (_codecs) _codecs->CloseLibs(); }
  };

  bool NeedSetLibCodecs; // = false, if we don't need to set codecs for archive handler via ISetCompressCodecsInfo

  HRESULT LoadCodecs();
  HRESULT LoadFormats();
  HRESULT LoadDll(const FString &path, bool needCheckDll, bool *loadedOK = NULL);
  HRESULT LoadDllsFromFolder(const FString &folderPrefix);

  HRESULT CreateArchiveHandler(const CArcInfoEx &ai, bool outHandler, void **archive) const
  {
    return Libs[ai.LibIndex].CreateObject(&ai.ClassID, outHandler ? &IID_IOutArchive : &IID_IInArchive, (void **)archive);
  }
  
  #endif

  #ifdef NEW_FOLDER_INTERFACE
  CCodecIcons InternalIcons;
  #endif

  CObjectVector<CArcInfoEx> Formats;
  
  #ifdef EXTERNAL_CODECS
  CRecordVector<CDllCodecInfo> Codecs;
  CRecordVector<CDllHasherInfo> Hashers;
  #endif

  bool CaseSensitiveChange;
  bool CaseSensitive;

  CCodecs():
      #ifdef EXTERNAL_CODECS
      NeedSetLibCodecs(true),
      #endif
      CaseSensitiveChange(false),
      CaseSensitive(false)
      {}

  ~CCodecs()
  {
    // OutputDebugStringA("~CCodecs");
  }
 
  const wchar_t *GetFormatNamePtr(int formatIndex) const
  {
    return formatIndex < 0 ? L"#" : (const wchar_t *)Formats[formatIndex].Name;
  }

>>>>>>> upstream/master
  HRESULT Load();
  
  #ifndef _SFX
  int FindFormatForArchiveName(const UString &arcPath) const;
  int FindFormatForExtension(const UString &ext) const;
  int FindFormatForArchiveType(const UString &arcType) const;
  bool FindFormatForArchiveType(const UString &arcType, CIntVector &formatIndices) const;
  #endif

<<<<<<< HEAD
  MY_UNKNOWN_IMP

  #ifdef EXTERNAL_CODECS
  STDMETHOD(GetNumberOfMethods)(UInt32 *numMethods);
  STDMETHOD(GetProperty)(UInt32 index, PROPID propID, PROPVARIANT *value);
  STDMETHOD(CreateDecoder)(UInt32 index, const GUID *interfaceID, void **coder);
  STDMETHOD(CreateEncoder)(UInt32 index, const GUID *interfaceID, void **coder);
  #endif

  int GetCodecLibIndex(UInt32 index);
  bool GetCodecEncoderIsAssigned(UInt32 index);
  HRESULT GetCodecId(UInt32 index, UInt64 &id);
  UString GetCodecName(UInt32 index);

  HRESULT CreateInArchive(int formatIndex, CMyComPtr<IInArchive> &archive) const
=======
  #ifdef EXTERNAL_CODECS

  MY_UNKNOWN_IMP2(ICompressCodecsInfo, IHashers)
    
  STDMETHOD(GetNumMethods)(UInt32 *numMethods);
  STDMETHOD(GetProperty)(UInt32 index, PROPID propID, PROPVARIANT *value);
  STDMETHOD(CreateDecoder)(UInt32 index, const GUID *iid, void **coder);
  STDMETHOD(CreateEncoder)(UInt32 index, const GUID *iid, void **coder);

  STDMETHOD_(UInt32, GetNumHashers)();
  STDMETHOD(GetHasherProp)(UInt32 index, PROPID propID, PROPVARIANT *value);
  STDMETHOD(CreateHasher)(UInt32 index, IHasher **hasher);

  #else

  MY_UNKNOWN_IMP

  #endif // EXTERNAL_CODECS

  
  #ifdef EXTERNAL_CODECS

  int GetCodec_LibIndex(UInt32 index) const;
  bool GetCodec_DecoderIsAssigned(UInt32 index) const;
  bool GetCodec_EncoderIsAssigned(UInt32 index) const;
  UInt32 GetCodec_NumStreams(UInt32 index);
  HRESULT GetCodec_Id(UInt32 index, UInt64 &id);
  AString GetCodec_Name(UInt32 index);

  int GetHasherLibIndex(UInt32 index);
  UInt64 GetHasherId(UInt32 index);
  AString GetHasherName(UInt32 index);
  UInt32 GetHasherDigestSize(UInt32 index);

  #endif

  HRESULT CreateInArchive(unsigned formatIndex, CMyComPtr<IInArchive> &archive) const
>>>>>>> upstream/master
  {
    const CArcInfoEx &ai = Formats[formatIndex];
    #ifdef EXTERNAL_CODECS
    if (ai.LibIndex < 0)
    #endif
    {
<<<<<<< HEAD
      archive = ai.CreateInArchive();
      return S_OK;
    }
    #ifdef EXTERNAL_CODECS
    return CreateArchiveHandler(ai, (void **)&archive, false);
    #endif
  }
  HRESULT CreateOutArchive(int formatIndex, CMyComPtr<IOutArchive> &archive) const
=======
      COM_TRY_BEGIN
      archive = ai.CreateInArchive();
      return S_OK;
      COM_TRY_END
    }
    #ifdef EXTERNAL_CODECS
    return CreateArchiveHandler(ai, false, (void **)&archive);
    #endif
  }
  
  #ifndef _SFX

  HRESULT CreateOutArchive(unsigned formatIndex, CMyComPtr<IOutArchive> &archive) const
>>>>>>> upstream/master
  {
    const CArcInfoEx &ai = Formats[formatIndex];
    #ifdef EXTERNAL_CODECS
    if (ai.LibIndex < 0)
    #endif
    {
<<<<<<< HEAD
      archive = ai.CreateOutArchive();
      return S_OK;
    }
    #ifdef EXTERNAL_CODECS
    return CreateArchiveHandler(ai, (void **)&archive, true);
    #endif
  }
  int FindOutFormatFromName(const UString &name) const
  {
    for (int i = 0; i < Formats.Size(); i++)
=======
      COM_TRY_BEGIN
      archive = ai.CreateOutArchive();
      return S_OK;
      COM_TRY_END
    }
    
    #ifdef EXTERNAL_CODECS
    return CreateArchiveHandler(ai, true, (void **)&archive);
    #endif
  }
  
  int FindOutFormatFromName(const UString &name) const
  {
    FOR_VECTOR (i, Formats)
>>>>>>> upstream/master
    {
      const CArcInfoEx &arc = Formats[i];
      if (!arc.UpdateEnabled)
        continue;
<<<<<<< HEAD
      if (arc.Name.CompareNoCase(name) == 0)
=======
      if (arc.Name.IsEqualTo_NoCase(name))
>>>>>>> upstream/master
        return i;
    }
    return -1;
  }

<<<<<<< HEAD
  #ifdef EXTERNAL_CODECS
  HRESULT CreateCoder(const UString &name, bool encode, CMyComPtr<ICompressCoder> &coder) const;
  #endif

};

=======
  #endif // _SFX
};

#ifdef EXTERNAL_CODECS
  #define CREATE_CODECS_OBJECT \
    CCodecs *codecs = new CCodecs; \
    CExternalCodecs __externalCodecs; \
    __externalCodecs.GetCodecs = codecs; \
    __externalCodecs.GetHashers = codecs; \
    CCodecs::CReleaser codecsReleaser; \
    codecsReleaser.Set(codecs);
#else
  #define CREATE_CODECS_OBJECT \
    CCodecs *codecs = new CCodecs; \
    CMyComPtr<IUnknown> __codecsRef = codecs;
#endif
  
>>>>>>> upstream/master
#endif
