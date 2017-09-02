/*
<<<<<<< HEAD
 * Copyright 2011-2015 Branimir Karadzic. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
=======
 * Copyright 2011-2017 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bx#license-bsd-2-clause
>>>>>>> upstream/master
 */

#ifndef DBG_H_HEADER_GUARD
#define DBG_H_HEADER_GUARD

<<<<<<< HEAD
#include <stdarg.h> // va_list
#include <stdint.h>
=======
#include <bx/debug.h>
>>>>>>> upstream/master

#define DBG_STRINGIZE(_x) DBG_STRINGIZE_(_x)
#define DBG_STRINGIZE_(_x) #_x
#define DBG_FILE_LINE_LITERAL "" __FILE__ "(" DBG_STRINGIZE(__LINE__) "): "
<<<<<<< HEAD
#define DBG(_format, ...) dbgPrintf(DBG_FILE_LINE_LITERAL "" _format "\n", ##__VA_ARGS__)

extern void dbgPrintfVargs(const char* _format, va_list _argList);
extern void dbgPrintf(const char* _format, ...);
extern void dbgPrintfData(const void* _data, uint32_t _size, const char* _format, ...);
=======
#define DBG(_format, ...) bx::debugPrintf(DBG_FILE_LINE_LITERAL "" _format "\n", ##__VA_ARGS__)
>>>>>>> upstream/master

#endif // DBG_H_HEADER_GUARD
