// WorkDir.h

#ifndef __WORK_DIR_H
#define __WORK_DIR_H

<<<<<<< HEAD
#include "Windows/FileDir.h"

#include "ZipRegistry.h"

#include "../../Common/FileStreams.h"

=======
#include "../../../Windows/FileDir.h"

#include "../../Common/FileStreams.h"

#include "ZipRegistry.h"

>>>>>>> upstream/master
FString GetWorkDir(const NWorkDir::CInfo &workDirInfo, const FString &path, FString &fileName);

class CWorkDirTempFile
{
  FString _originalPath;
<<<<<<< HEAD
  NWindows::NFile::NDirectory::CTempFile _tempFile;
=======
  NWindows::NFile::NDir::CTempFile _tempFile;
>>>>>>> upstream/master
  COutFileStream *_outStreamSpec;
public:
  CMyComPtr<IOutStream> OutStream;

  HRESULT CreateTempFile(const FString &originalPath);
  HRESULT MoveToOriginal(bool deleteOriginal);
};

#endif
