<<<<<<< HEAD
// ProgressUtils.h
=======
// ProgressUtils.cpp
>>>>>>> upstream/master

#include "StdAfx.h"

#include "ProgressUtils.h"

<<<<<<< HEAD
CLocalProgress::CLocalProgress()
{
  ProgressOffset = InSize = OutSize = 0;
  SendRatio = SendProgress = true;
}
=======
CLocalProgress::CLocalProgress():
    ProgressOffset(0),
    InSize(0),
    OutSize(0),
    SendRatio(true),
    SendProgress(true)
  {}
>>>>>>> upstream/master

void CLocalProgress::Init(IProgress *progress, bool inSizeIsMain)
{
  _ratioProgress.Release();
  _progress = progress;
  _progress.QueryInterface(IID_ICompressProgressInfo, &_ratioProgress);
  _inSizeIsMain = inSizeIsMain;
}

STDMETHODIMP CLocalProgress::SetRatioInfo(const UInt64 *inSize, const UInt64 *outSize)
{
<<<<<<< HEAD
  UInt64 inSizeNew = InSize, outSizeNew = OutSize;
  if (inSize)
    inSizeNew += (*inSize);
  if (outSize)
    outSizeNew += (*outSize);
  if (SendRatio && _ratioProgress)
  {
    RINOK(_ratioProgress->SetRatioInfo(&inSizeNew, &outSizeNew));
  }
  inSizeNew += ProgressOffset;
  outSizeNew += ProgressOffset;
  if (SendProgress)
    return _progress->SetCompleted(_inSizeIsMain ? &inSizeNew : &outSizeNew);
=======
  UInt64 inSize2 = InSize;
  UInt64 outSize2 = OutSize;
  
  if (inSize)
    inSize2 += (*inSize);
  if (outSize)
    outSize2 += (*outSize);
  
  if (SendRatio && _ratioProgress)
  {
    RINOK(_ratioProgress->SetRatioInfo(&inSize2, &outSize2));
  }
  
  if (SendProgress)
  {
    inSize2 += ProgressOffset;
    outSize2 += ProgressOffset;
    return _progress->SetCompleted(_inSizeIsMain ? &inSize2 : &outSize2);
  }
  
>>>>>>> upstream/master
  return S_OK;
}

HRESULT CLocalProgress::SetCur()
{
  return SetRatioInfo(NULL, NULL);
}
