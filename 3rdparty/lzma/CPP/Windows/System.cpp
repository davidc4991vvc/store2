// Windows/System.cpp

#include "StdAfx.h"

<<<<<<< HEAD
=======
#include "../Common/MyWindows.h"

>>>>>>> upstream/master
#include "../Common/Defs.h"

#include "System.h"

namespace NWindows {
namespace NSystem {

<<<<<<< HEAD
=======
#ifdef _WIN32

>>>>>>> upstream/master
UInt32 GetNumberOfProcessors()
{
  SYSTEM_INFO systemInfo;
  GetSystemInfo(&systemInfo);
  return (UInt32)systemInfo.dwNumberOfProcessors;
}

<<<<<<< HEAD
=======
#else

UInt32 GetNumberOfProcessors()
{
  return 1;
}

#endif


#ifdef _WIN32

>>>>>>> upstream/master
#ifndef UNDER_CE

#if !defined(_WIN64) && defined(__GNUC__)

typedef struct _MY_MEMORYSTATUSEX {
  DWORD dwLength;
  DWORD dwMemoryLoad;
  DWORDLONG ullTotalPhys;
  DWORDLONG ullAvailPhys;
  DWORDLONG ullTotalPageFile;
  DWORDLONG ullAvailPageFile;
  DWORDLONG ullTotalVirtual;
  DWORDLONG ullAvailVirtual;
  DWORDLONG ullAvailExtendedVirtual;
} MY_MEMORYSTATUSEX, *MY_LPMEMORYSTATUSEX;

#else

#define MY_MEMORYSTATUSEX MEMORYSTATUSEX
#define MY_LPMEMORYSTATUSEX LPMEMORYSTATUSEX

#endif

typedef BOOL (WINAPI *GlobalMemoryStatusExP)(MY_LPMEMORYSTATUSEX lpBuffer);

#endif

<<<<<<< HEAD
UInt64 GetRamSize()
{
  #ifndef UNDER_CE
  MY_MEMORYSTATUSEX stat;
  stat.dwLength = sizeof(stat);
  #endif
  #ifdef _WIN64
  if (!::GlobalMemoryStatusEx(&stat))
    return 0;
  return MyMin(stat.ullTotalVirtual, stat.ullTotalPhys);
  #else
  #ifndef UNDER_CE
  GlobalMemoryStatusExP globalMemoryStatusEx = (GlobalMemoryStatusExP)
      ::GetProcAddress(::GetModuleHandle(TEXT("kernel32.dll")), "GlobalMemoryStatusEx");
  if (globalMemoryStatusEx != 0 && globalMemoryStatusEx(&stat))
    return MyMin(stat.ullTotalVirtual, stat.ullTotalPhys);
  #endif
  {
    MEMORYSTATUS stat;
    stat.dwLength = sizeof(stat);
    ::GlobalMemoryStatus(&stat);
    return MyMin(stat.dwTotalVirtual, stat.dwTotalPhys);
  }
=======
#endif


bool GetRamSize(UInt64 &size)
{
  size = (UInt64)(sizeof(size_t)) << 29;

  #ifdef _WIN32
  
  #ifndef UNDER_CE
    MY_MEMORYSTATUSEX stat;
    stat.dwLength = sizeof(stat);
  #endif
  
  #ifdef _WIN64
    
    if (!::GlobalMemoryStatusEx(&stat))
      return false;
    size = MyMin(stat.ullTotalVirtual, stat.ullTotalPhys);
    return true;

  #else
    
    #ifndef UNDER_CE
      GlobalMemoryStatusExP globalMemoryStatusEx = (GlobalMemoryStatusExP)
          ::GetProcAddress(::GetModuleHandle(TEXT("kernel32.dll")), "GlobalMemoryStatusEx");
      if (globalMemoryStatusEx && globalMemoryStatusEx(&stat))
      {
        size = MyMin(stat.ullTotalVirtual, stat.ullTotalPhys);
        return true;
      }
    #endif
  
    {
      MEMORYSTATUS stat2;
      stat2.dwLength = sizeof(stat2);
      ::GlobalMemoryStatus(&stat2);
      size = MyMin(stat2.dwTotalVirtual, stat2.dwTotalPhys);
      return true;
    }
  
  #endif

  #else

  return false;

>>>>>>> upstream/master
  #endif
}

}}
