// license:BSD-3-Clause
// copyright-holders:Aaron Giles
/***************************************************************************

    corealloc.h

    Memory allocation helpers for the helper library.

***************************************************************************/

#pragma once

<<<<<<< HEAD
#ifndef __COREALLOC_H__
#define __COREALLOC_H__

#include <stdlib.h>
#include <new>
#include "osdcore.h"


//**************************************************************************
//  MACROS
//**************************************************************************

// global allocation helpers -- use these instead of new and delete
#define global_alloc(_type)                         new(__FILE__, __LINE__) _type
#define global_alloc_clear(_type)                   new(__FILE__, __LINE__, zeromem) _type
#define global_alloc_array(_type, _num)             new(__FILE__, __LINE__) _type[_num]
#define global_alloc_array_clear(_type, _num)       new(__FILE__, __LINE__, zeromem) _type[_num]
#define global_free(_ptr)                           do { delete _ptr; } while (0)
#define global_free_array(_ptr)                     do { delete[] _ptr; } while (0)



//**************************************************************************
//  FUNCTION PROTOTYPES
//**************************************************************************

// allocate memory with file and line number information
void *malloc_file_line(size_t size, const char *file, int line, bool array, bool throw_on_fail, bool clear);

// free memory with file and line number information
void free_file_line(void *memory, const char *file, int line, bool array);
inline void free_file_line(const void *memory, const char *file, int line, bool array) { free_file_line(const_cast<void *>(memory), file, line, array); }

// called from the exit path of any code that wants to check for unfreed memory
void track_memory(bool track);
UINT64 next_memory_id();
void dump_unfreed_mem(UINT64 start = 0);



//**************************************************************************
//  OPERATOR OVERLOADS - DECLARATIONS
//**************************************************************************

// zeromem_t is a dummy class used to tell new to zero memory after allocation
class zeromem_t { };

// file/line new/delete operators
void *operator new(std::size_t size, const char *file, int line) throw (std::bad_alloc);
void *operator new[](std::size_t size, const char *file, int line) throw (std::bad_alloc);
void operator delete(void *ptr, const char *file, int line);
void operator delete[](void *ptr, const char *file, int line);

// file/line new/delete operators with zeroing
void *operator new(std::size_t size, const char *file, int line, const zeromem_t &) throw (std::bad_alloc);
void *operator new[](std::size_t size, const char *file, int line, const zeromem_t &) throw (std::bad_alloc);
void operator delete(void *ptr, const char *file, int line, const zeromem_t &);
void operator delete[](void *ptr, const char *file, int line, const zeromem_t &);



//**************************************************************************
//  GLOBAL VARIABLES
//**************************************************************************

// dummy objects to pass to the specialized new variants
extern const zeromem_t zeromem;
=======
#ifndef MAME_LIB_UTIL_COREALLOC_H
#define MAME_LIB_UTIL_COREALLOC_H

#include "osdcore.h"

#include <stdlib.h>

#include <cstddef>
#include <cstring>
#include <new>
#include <memory>
#include <type_traits>
#include <utility>
>>>>>>> upstream/master



//**************************************************************************
<<<<<<< HEAD
//  ADDDITIONAL MACROS
//**************************************************************************

#ifndef NO_MEM_TRACKING
// re-route classic malloc-style allocations
#undef malloc
#undef realloc
#undef free

#define malloc(x)       malloc_file_line(x, __FILE__, __LINE__, true, false, false)
#define realloc(x,y)    __error_realloc_is_dangerous__
#define free(x)         free_file_line(x, __FILE__, __LINE__, true)

#if !defined(_MSC_VER) || _MSC_VER < 1900 // < VS2015
#undef calloc
#define calloc(x,y)     __error_use_auto_alloc_clear_or_global_alloc_clear_instead__
#endif

#endif

#endif  /* __COREALLOC_H__ */
=======
//  MACROS
//**************************************************************************

// global allocation helpers -- use these instead of new and delete
#define global_alloc(Type)                          new Type
#define global_alloc_nothrow(Type)                  new (std::nothrow) Type
#define global_alloc_array(Type, Num)               new Type[Num]
#define global_alloc_array_nothrow(Type, Num)       new (std::nothrow) Type[Num]
#define global_free(Ptr)                            do { delete Ptr; } while (0)
#define global_free_array(Ptr)                      do { delete[] Ptr; } while (0)



template<typename T, typename... Params>
inline T* global_alloc_clear(Params &&... args)
{
	void *const ptr = ::operator new(sizeof(T)); // allocate memory
	std::memset(ptr, 0, sizeof(T));
	return new(ptr) T(std::forward<Params>(args)...);
}

template<typename T>
inline T* global_alloc_array_clear(std::size_t num)
{
	auto const size = sizeof(T) * num;
	void *const ptr = new unsigned char[size]; // allocate memory
	std::memset(ptr, 0, size);
	return new(ptr) T[num]();
}



template<typename Tp> struct MakeUniqClearT { typedef std::unique_ptr<Tp> single_object; };

template<typename Tp> struct MakeUniqClearT<Tp[]> { typedef std::unique_ptr<Tp[]> array; };

template<typename Tp, size_t Bound> struct MakeUniqClearT<Tp[Bound]> { struct invalid_type { }; };

/// make_unique_clear for single objects
template<typename Tp, typename... Params>
inline typename MakeUniqClearT<Tp>::single_object make_unique_clear(Params&&... args)
{
	void *const ptr = ::operator new(sizeof(Tp)); // allocate memory
	std::memset(ptr, 0, sizeof(Tp));
	return std::unique_ptr<Tp>(new(ptr) Tp(std::forward<Params>(args)...));
}

/// make_unique_clear for arrays of unknown bound
template<typename Tp>
inline typename MakeUniqClearT<Tp>::array make_unique_clear(size_t num)
{
	auto size = sizeof(std::remove_extent_t<Tp>) * num;
	unsigned char* ptr = new unsigned char[size]; // allocate memory
	std::memset(ptr, 0, size);
	return std::unique_ptr<Tp>(new(ptr) std::remove_extent_t<Tp>[num]());
}

template<typename Tp, unsigned char F>
inline typename MakeUniqClearT<Tp>::array make_unique_clear(size_t num)
{
	auto size = sizeof(std::remove_extent_t<Tp>) * num;
	unsigned char* ptr = new unsigned char[size]; // allocate memory
	std::memset(ptr, F, size);
	return std::unique_ptr<Tp>(new(ptr) std::remove_extent_t<Tp>[num]());
}

/// Disable make_unique_clear for arrays of known bound
template<typename Tp, typename... Params>
inline typename MakeUniqClearT<Tp>::invalid_type make_unique_clear(Params&&...) = delete;

#endif  // MAME_LIB_UTIL_COREALLOC_H
>>>>>>> upstream/master
