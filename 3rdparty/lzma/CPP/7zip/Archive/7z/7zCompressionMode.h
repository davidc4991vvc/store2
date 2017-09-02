// 7zCompressionMode.h

#ifndef __7Z_COMPRESSION_MODE_H
#define __7Z_COMPRESSION_MODE_H

#include "../../Common/MethodId.h"
#include "../../Common/MethodProps.h"

namespace NArchive {
namespace N7z {

<<<<<<< HEAD
struct CMethodFull: public CProps
{
  CMethodId Id;
  UInt32 NumInStreams;
  UInt32 NumOutStreams;

  bool IsSimpleCoder() const { return (NumInStreams == 1) && (NumOutStreams == 1); }
};

struct CBind
{
  UInt32 InCoder;
  UInt32 InStream;
  UInt32 OutCoder;
  UInt32 OutStream;
=======
struct CMethodFull: public CMethodProps
{
  CMethodId Id;
  UInt32 NumStreams;

  bool IsSimpleCoder() const { return NumStreams == 1; }
};

struct CBond2
{
  UInt32 OutCoder;
  UInt32 OutStream;
  UInt32 InCoder;
>>>>>>> upstream/master
};

struct CCompressionMethodMode
{
<<<<<<< HEAD
  CObjectVector<CMethodFull> Methods;
  CRecordVector<CBind> Binds;
  #ifndef _7ZIP_ST
  UInt32 NumThreads;
  #endif
=======
  /*
    if (Bonds.Empty()), then default bonds must be created
    if (Filter_was_Inserted)
    {
      Methods[0] is filter method
      Bonds don't contain bonds for filter (these bonds must be created)
    }
  */

  CObjectVector<CMethodFull> Methods;
  CRecordVector<CBond2> Bonds;

  bool IsThereBond_to_Coder(unsigned coderIndex) const
  {
    FOR_VECTOR(i, Bonds)
      if (Bonds[i].InCoder == coderIndex)
        return true;
    return false;
  }

  bool DefaultMethod_was_Inserted;
  bool Filter_was_Inserted;

  #ifndef _7ZIP_ST
  UInt32 NumThreads;
  bool MultiThreadMixer;
  #endif
  
>>>>>>> upstream/master
  bool PasswordIsDefined;
  UString Password;

  bool IsEmpty() const { return (Methods.IsEmpty() && !PasswordIsDefined); }
<<<<<<< HEAD
  CCompressionMethodMode(): PasswordIsDefined(false)
      #ifndef _7ZIP_ST
      , NumThreads(1)
=======
  CCompressionMethodMode():
      DefaultMethod_was_Inserted(false),
      Filter_was_Inserted(false),
      PasswordIsDefined(false)
      #ifndef _7ZIP_ST
      , NumThreads(1)
      , MultiThreadMixer(true)
>>>>>>> upstream/master
      #endif
  {}
};

}}

#endif
