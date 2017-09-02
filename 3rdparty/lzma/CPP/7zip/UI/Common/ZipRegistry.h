// ZipRegistry.h

#ifndef __ZIP_REGISTRY_H
#define __ZIP_REGISTRY_H

<<<<<<< HEAD
#include "Common/MyString.h"
#include "Common/Types.h"
=======
#include "../../../Common/MyTypes.h"
#include "../../../Common/MyString.h"
>>>>>>> upstream/master

#include "ExtractMode.h"

namespace NExtract
{
  struct CInfo
  {
    NPathMode::EEnum PathMode;
    NOverwriteMode::EEnum OverwriteMode;
<<<<<<< HEAD
    bool ShowPassword;
=======
    bool PathMode_Force;
    bool OverwriteMode_Force;
    
    CBoolPair SplitDest;
    CBoolPair ElimDup;
    // CBoolPair AltStreams;
    CBoolPair NtSecurity;
    CBoolPair ShowPassword;

>>>>>>> upstream/master
    UStringVector Paths;

    void Save() const;
    void Load();
  };
<<<<<<< HEAD
=======
  
>>>>>>> upstream/master
  void Save_ShowPassword(bool showPassword);
  bool Read_ShowPassword();
}

namespace NCompression
{
  struct CFormatOptions
  {
    UInt32 Level;
    UInt32 Dictionary;
    UInt32 Order;
    UInt32 BlockLogSize;
    UInt32 NumThreads;
    
    CSysString FormatID;
    UString Method;
    UString Options;
    UString EncryptionMethod;

    void ResetForLevelChange()
    {
      BlockLogSize = NumThreads = Level = Dictionary = Order = UInt32(-1);
      Method.Empty();
      // Options.Empty();
      // EncryptionMethod.Empty();
    }
    CFormatOptions() { ResetForLevelChange(); }
  };

  struct CInfo
  {
    UInt32 Level;
    bool ShowPassword;
    bool EncryptHeaders;
    UString ArcType;
    UStringVector ArcPaths;

    CObjectVector<CFormatOptions> Formats;

<<<<<<< HEAD
=======
    CBoolPair NtSecurity;
    CBoolPair AltStreams;
    CBoolPair HardLinks;
    CBoolPair SymLinks;

>>>>>>> upstream/master
    void Save() const;
    void Load();
  };
}

namespace NWorkDir
{
  namespace NMode
  {
    enum EEnum
    {
      kSystem,
      kCurrent,
      kSpecified
    };
  }
  struct CInfo
  {
    NMode::EEnum Mode;
    FString Path;
    bool ForRemovableOnly;

    void SetForRemovableOnlyDefault() { ForRemovableOnly = true; }
    void SetDefault()
    {
      Mode = NMode::kSystem;
      Path.Empty();
      SetForRemovableOnlyDefault();
    }

    void Save() const;
    void Load();
  };
}


struct CContextMenuInfo
{
<<<<<<< HEAD
  bool Cascaded;
=======
  CBoolPair Cascaded;
  CBoolPair MenuIcons;
  CBoolPair ElimDup;

  bool Flags_Def;
>>>>>>> upstream/master
  UInt32 Flags;

  void Save() const;
  void Load();
};

#endif
