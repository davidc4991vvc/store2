// Common/Defs.h

#ifndef __COMMON_DEFS_H
#define __COMMON_DEFS_H

<<<<<<< HEAD
template <class T> inline T MyMin(T a, T b)
  {  return a < b ? a : b; }
template <class T> inline T MyMax(T a, T b)
  {  return a > b ? a : b; }

template <class T> inline int MyCompare(T a, T b)
  {  return a < b ? -1 : (a == b ? 0 : 1); }

inline int BoolToInt(bool value)
  { return (value ? 1: 0); }

inline bool IntToBool(int value)
  { return (value != 0); }
=======
template <class T> inline T MyMin(T a, T b) { return a < b ? a : b; }
template <class T> inline T MyMax(T a, T b) { return a > b ? a : b; }

template <class T> inline int MyCompare(T a, T b)
  { return a == b ? 0 : (a < b ? -1 : 1); }

inline int BoolToInt(bool v) { return (v ? 1 : 0); }
inline bool IntToBool(int v) { return (v != 0); }
>>>>>>> upstream/master

#endif
