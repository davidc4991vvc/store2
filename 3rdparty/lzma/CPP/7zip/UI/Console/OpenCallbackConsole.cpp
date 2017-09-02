// OpenCallbackConsole.cpp

#include "StdAfx.h"

#include "OpenCallbackConsole.h"

#include "ConsoleClose.h"
#include "UserInputUtils.h"

<<<<<<< HEAD
HRESULT COpenCallbackConsole::Open_CheckBreak()
{
  if (NConsoleClose::TestBreakSignal())
    return E_ABORT;
  return S_OK;
}

HRESULT COpenCallbackConsole::Open_SetTotal(const UInt64 *, const UInt64 *)
{
  return Open_CheckBreak();
}

HRESULT COpenCallbackConsole::Open_SetCompleted(const UInt64 *, const UInt64 *)
{
  return Open_CheckBreak();
}
 
=======
static HRESULT CheckBreak2()
{
  return NConsoleClose::TestBreakSignal() ? E_ABORT : S_OK;
}

HRESULT COpenCallbackConsole::Open_CheckBreak()
{
  return CheckBreak2();
}

HRESULT COpenCallbackConsole::Open_SetTotal(const UInt64 *files, const UInt64 *bytes)
{
  if (!MultiArcMode && NeedPercents())
  {
    if (files)
    {
      _totalFilesDefined = true;
      // _totalFiles = *files;
      _percent.Total = *files;
    }
    else
      _totalFilesDefined = false;

    if (bytes)
    {
      _totalBytesDefined = true;
      // _totalBytes = *bytes;
      if (!files)
        _percent.Total = *bytes;
    }
    else
      _totalBytesDefined = false;
  }

  return CheckBreak2();
}

HRESULT COpenCallbackConsole::Open_SetCompleted(const UInt64 *files, const UInt64 *bytes)
{
  if (!MultiArcMode && NeedPercents())
  {
    if (files)
    {
      _percent.Files = *files;
      if (_totalFilesDefined)
        _percent.Completed = *files;
    }

    if (bytes)
    {
      if (!_totalFilesDefined)
        _percent.Completed = *bytes;
    }
    _percent.Print();
  }

  return CheckBreak2();
}

HRESULT COpenCallbackConsole::Open_Finished()
{
  ClosePercents();
  return S_OK;
}


>>>>>>> upstream/master
#ifndef _NO_CRYPTO

HRESULT COpenCallbackConsole::Open_CryptoGetTextPassword(BSTR *password)
{
<<<<<<< HEAD
  PasswordWasAsked = true;
  RINOK(Open_CheckBreak());
  if (!PasswordIsDefined)
  {
    Password = GetPassword(OutStream);
=======
  *password = NULL;
  RINOK(CheckBreak2());

  if (!PasswordIsDefined)
  {
    ClosePercents();
    Password = GetPassword(_so);
>>>>>>> upstream/master
    PasswordIsDefined = true;
  }
  return StringToBstr(Password, password);
}

<<<<<<< HEAD
HRESULT COpenCallbackConsole::Open_GetPasswordIfAny(UString &password)
{
  if (PasswordIsDefined)
    password = Password;
=======
/*
HRESULT COpenCallbackConsole::Open_GetPasswordIfAny(bool &passwordIsDefined, UString &password)
{
  passwordIsDefined = PasswordIsDefined;
  password = Password;
>>>>>>> upstream/master
  return S_OK;
}

bool COpenCallbackConsole::Open_WasPasswordAsked()
{
  return PasswordWasAsked;
}

<<<<<<< HEAD
void COpenCallbackConsole::Open_ClearPasswordWasAskedFlag()
{
  PasswordWasAsked = false;
}
=======
void COpenCallbackConsole::Open_Clear_PasswordWasAsked_Flag ()
{
  PasswordWasAsked = false;
}
*/
>>>>>>> upstream/master

#endif
