// ExtractMode.h

#ifndef __EXTRACT_MODE_H
#define __EXTRACT_MODE_H

namespace NExtract {
  
<<<<<<< HEAD
  namespace NPathMode
  {
    enum EEnum
    {
      kFullPathnames,
      kCurrentPathnames,
      kNoPathnames
    };
  }
  
  namespace NOverwriteMode
  {
    enum EEnum
    {
      kAskBefore,
      kWithoutPrompt,
      kSkipExisting,
      kAutoRename,
      kAutoRenameExisting
    };
  }
=======
namespace NPathMode
{
  enum EEnum
  {
    kFullPaths,
    kCurPaths,
    kNoPaths,
    kAbsPaths,
    kNoPathsAlt // alt streams must be extracted without name of base file
  };
}

namespace NOverwriteMode
{
  enum EEnum
  {
    kAsk,
    kOverwrite,
    kSkip,
    kRename,
    kRenameExisting
  };
}

>>>>>>> upstream/master
}

#endif
