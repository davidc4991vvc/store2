// license:BSD-3-Clause
// copyright-holders:Nicola Salmoria, Aaron Giles
/***************************************************************************

    emucore.h

    General core utilities and macros used throughout the emulator.
***************************************************************************/

<<<<<<< HEAD
#pragma once

#ifndef __EMUCORE_H__
#define __EMUCORE_H__
=======
#ifndef MAME_EMU_EMUCORE_H
#define MAME_EMU_EMUCORE_H

#pragma once
>>>>>>> upstream/master

// standard C includes
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>

// some cleanups for Solaris for things defined in stdlib.h
#if defined(__sun__) && defined(__svr4__)
#undef si_status
#undef WWORD
#endif

// standard C++ includes
<<<<<<< HEAD
#include <exception>
=======
#include <cassert>
#include <exception>
#include <type_traits>
>>>>>>> upstream/master
#include <typeinfo>

// core system includes
#include "osdcomm.h"
#include "emualloc.h"
#include "corestr.h"
#include "bitmap.h"
<<<<<<< HEAD
#include "tagmap.h"
#include "ui/lang.h"

=======

#include "emufwd.h"
>>>>>>> upstream/master


//**************************************************************************
//  COMPILER-SPECIFIC NASTINESS
//**************************************************************************

// Suppress warnings about redefining the macro 'PPC' on LinuxPPC.
#undef PPC

// Suppress warnings about redefining the macro 'ARM' on ARM.
#undef ARM



//**************************************************************************
//  FUNDAMENTAL TYPES
//**************************************************************************

<<<<<<< HEAD
=======
// explicitly sized integers
using osd::u8;
using osd::u16;
using osd::u32;
using osd::u64;
using osd::s8;
using osd::s16;
using osd::s32;
using osd::s64;

>>>>>>> upstream/master
// genf is a generic function pointer; cast function pointers to this instead of void *
typedef void genf(void);

// pen_t is used to represent pixel values in bitmaps
<<<<<<< HEAD
typedef UINT32 pen_t;

// stream_sample_t is used to represent a single sample in a sound stream
typedef INT32 stream_sample_t;

// running_machine is core to pretty much everything
class running_machine;
=======
typedef u32 pen_t;

// stream_sample_t is used to represent a single sample in a sound stream
typedef s32 stream_sample_t;
>>>>>>> upstream/master



//**************************************************************************
//  USEFUL COMPOSITE TYPES
//**************************************************************************

<<<<<<< HEAD
// generic_ptr is a union of pointers to various sizes
union generic_ptr
{
	generic_ptr(void *value) { v = value; }
	void *      v;
	INT8 *      i8;
	UINT8 *     u8;
	INT16 *     i16;
	UINT16 *    u16;
	INT32 *     i32;
	UINT32 *    u32;
	INT64 *     i64;
	UINT64 *    u64;
};


=======
>>>>>>> upstream/master
// PAIR is an endian-safe union useful for representing 32-bit CPU registers
union PAIR
{
#ifdef LSB_FIRST
<<<<<<< HEAD
	struct { UINT8 l,h,h2,h3; } b;
	struct { UINT16 l,h; } w;
	struct { INT8 l,h,h2,h3; } sb;
	struct { INT16 l,h; } sw;
#else
	struct { UINT8 h3,h2,h,l; } b;
	struct { INT8 h3,h2,h,l; } sb;
	struct { UINT16 h,l; } w;
	struct { INT16 h,l; } sw;
#endif
	UINT32 d;
	INT32 sd;
=======
	struct { u8 l,h,h2,h3; } b;
	struct { u16 l,h; } w;
	struct { s8 l,h,h2,h3; } sb;
	struct { s16 l,h; } sw;
#else
	struct { u8 h3,h2,h,l; } b;
	struct { s8 h3,h2,h,l; } sb;
	struct { u16 h,l; } w;
	struct { s16 h,l; } sw;
#endif
	u32 d;
	s32 sd;
>>>>>>> upstream/master
};


// PAIR16 is a 16-bit extension of a PAIR
union PAIR16
{
#ifdef LSB_FIRST
<<<<<<< HEAD
	struct { UINT8 l,h; } b;
	struct { INT8 l,h; } sb;
#else
	struct { UINT8 h,l; } b;
	struct { INT8 h,l; } sb;
#endif
	UINT16 w;
	INT16 sw;
=======
	struct { u8 l,h; } b;
	struct { s8 l,h; } sb;
#else
	struct { u8 h,l; } b;
	struct { s8 h,l; } sb;
#endif
	u16 w;
	s16 sw;
>>>>>>> upstream/master
};


// PAIR64 is a 64-bit extension of a PAIR
union PAIR64
{
#ifdef LSB_FIRST
<<<<<<< HEAD
	struct { UINT8 l,h,h2,h3,h4,h5,h6,h7; } b;
	struct { UINT16 l,h,h2,h3; } w;
	struct { UINT32 l,h; } d;
	struct { INT8 l,h,h2,h3,h4,h5,h6,h7; } sb;
	struct { INT16 l,h,h2,h3; } sw;
	struct { INT32 l,h; } sd;
#else
	struct { UINT8 h7,h6,h5,h4,h3,h2,h,l; } b;
	struct { UINT16 h3,h2,h,l; } w;
	struct { UINT32 h,l; } d;
	struct { INT8 h7,h6,h5,h4,h3,h2,h,l; } sb;
	struct { INT16 h3,h2,h,l; } sw;
	struct { INT32 h,l; } sd;
#endif
	UINT64 q;
	INT64 sq;
=======
	struct { u8 l,h,h2,h3,h4,h5,h6,h7; } b;
	struct { u16 l,h,h2,h3; } w;
	struct { u32 l,h; } d;
	struct { s8 l,h,h2,h3,h4,h5,h6,h7; } sb;
	struct { s16 l,h,h2,h3; } sw;
	struct { s32 l,h; } sd;
#else
	struct { u8 h7,h6,h5,h4,h3,h2,h,l; } b;
	struct { u16 h3,h2,h,l; } w;
	struct { u32 h,l; } d;
	struct { s8 h7,h6,h5,h4,h3,h2,h,l; } sb;
	struct { s16 h3,h2,h,l; } sw;
	struct { s32 h,l; } sd;
#endif
	u64 q;
	s64 sq;
>>>>>>> upstream/master
};



//**************************************************************************
//  COMMON CONSTANTS
//**************************************************************************

// constants for expression endianness
enum endianness_t
{
	ENDIANNESS_LITTLE,
	ENDIANNESS_BIG
};


// declare native endianness to be one or the other
#ifdef LSB_FIRST
const endianness_t ENDIANNESS_NATIVE = ENDIANNESS_LITTLE;
#else
const endianness_t ENDIANNESS_NATIVE = ENDIANNESS_BIG;
#endif


// M_PI is not part of the C/C++ standards and is not present on
// strict ANSI compilers or when compiling under GCC with -ansi
#ifndef M_PI
#define M_PI                            3.14159265358979323846
#endif


// orientation of bitmaps
<<<<<<< HEAD
#define ORIENTATION_FLIP_X              0x0001  /* mirror everything in the X direction */
#define ORIENTATION_FLIP_Y              0x0002  /* mirror everything in the Y direction */
#define ORIENTATION_SWAP_XY             0x0004  /* mirror along the top-left/bottom-right diagonal */

#define ROT0                            0
#define ROT90                           (ORIENTATION_SWAP_XY | ORIENTATION_FLIP_X)  /* rotate clockwise 90 degrees */
#define ROT180                          (ORIENTATION_FLIP_X | ORIENTATION_FLIP_Y)   /* rotate 180 degrees */
#define ROT270                          (ORIENTATION_SWAP_XY | ORIENTATION_FLIP_Y)  /* rotate counter-clockwise 90 degrees */
=======
constexpr int ORIENTATION_FLIP_X   = 0x0001;  // mirror everything in the X direction
constexpr int ORIENTATION_FLIP_Y   = 0x0002;  // mirror everything in the Y direction
constexpr int ORIENTATION_SWAP_XY  = 0x0004;  // mirror along the top-left/bottom-right diagonal

constexpr int ROT0                 = 0;
constexpr int ROT90                = ORIENTATION_SWAP_XY | ORIENTATION_FLIP_X;  // rotate clockwise 90 degrees
constexpr int ROT180               = ORIENTATION_FLIP_X | ORIENTATION_FLIP_Y;   // rotate 180 degrees
constexpr int ROT270               = ORIENTATION_SWAP_XY | ORIENTATION_FLIP_Y;  // rotate counter-clockwise 90 degrees
>>>>>>> upstream/master



//**************************************************************************
//  COMMON MACROS
//**************************************************************************

// macro for defining a copy constructor and assignment operator to prevent copying
<<<<<<< HEAD
#define DISABLE_COPYING(_Type) \
private: \
	_Type(const _Type &); \
	_Type &operator=(const _Type &)

// macro for declaring enumerator operators that increment/decrement like plain old C
#define DECLARE_ENUM_OPERATORS(_Type) \
inline void operator++(_Type &value) { value = (_Type)((int)value + 1); } \
inline void operator++(_Type &value, int) { value = (_Type)((int)value + 1); } \
inline void operator--(_Type &value) { value = (_Type)((int)value - 1); } \
inline void operator--(_Type &value, int) { value = (_Type)((int)value - 1); }
=======
#define DISABLE_COPYING(TYPE) \
	TYPE(const TYPE &) = delete; \
	TYPE &operator=(const TYPE &) = delete

// macro for declaring enumeration operators that increment/decrement like plain old C
#define DECLARE_ENUM_INCDEC_OPERATORS(TYPE) \
inline TYPE &operator++(TYPE &value) { return value = TYPE(std::underlying_type_t<TYPE>(value) + 1); } \
inline TYPE &operator--(TYPE &value) { return value = TYPE(std::underlying_type_t<TYPE>(value) - 1); } \
inline TYPE operator++(TYPE &value, int) { TYPE const old(value); ++value; return old; } \
inline TYPE operator--(TYPE &value, int) { TYPE const old(value); --value; return old; }

// macro for declaring bitwise operators for an enumerated type
#define DECLARE_ENUM_BITWISE_OPERATORS(TYPE) \
constexpr TYPE operator~(TYPE value) { return TYPE(~std::underlying_type_t<TYPE>(value)); } \
constexpr TYPE operator&(TYPE a, TYPE b) { return TYPE(std::underlying_type_t<TYPE>(a) & std::underlying_type_t<TYPE>(b)); } \
constexpr TYPE operator|(TYPE a, TYPE b) { return TYPE(std::underlying_type_t<TYPE>(a) | std::underlying_type_t<TYPE>(b)); } \
inline TYPE &operator&=(TYPE &a, TYPE b) { return a = a & b; } \
inline TYPE &operator|=(TYPE &a, TYPE b) { return a = a | b; }
>>>>>>> upstream/master


// this macro passes an item followed by a string version of itself as two consecutive parameters
#define NAME(x) x, #x

// this macro wraps a function 'x' and can be used to pass a function followed by its name
#define FUNC(x) &x, #x
<<<<<<< HEAD
#define FUNC_NULL NULL, "(null)"
=======
>>>>>>> upstream/master


// standard assertion macros
#undef assert
#undef assert_always

#if defined(MAME_DEBUG_FAST)
#define assert(x)               do { } while (0)
#define assert_always(x, msg)   do { if (!(x)) throw emu_fatalerror("Fatal error: %s\nCaused by assert: %s:%d: %s", msg, __FILE__, __LINE__, #x); } while (0)
#elif defined(MAME_DEBUG)
#define assert(x)               do { if (!(x)) throw emu_fatalerror("assert: %s:%d: %s", __FILE__, __LINE__, #x); } while (0)
#define assert_always(x, msg)   do { if (!(x)) throw emu_fatalerror("Fatal error: %s\nCaused by assert: %s:%d: %s", msg, __FILE__, __LINE__, #x); } while (0)
#else
#define assert(x)               do { } while (0)
#define assert_always(x, msg)   do { if (!(x)) throw emu_fatalerror("Fatal error: %s (%s:%d)", msg, __FILE__, __LINE__); } while (0)
#endif


// macros to convert radians to degrees and degrees to radians
#define RADIAN_TO_DEGREE(x)   ((180.0 / M_PI) * (x))
#define DEGREE_TO_RADIAN(x)   ((M_PI / 180.0) * (x))


// endian-based value: first value is if 'endian' is little-endian, second is if 'endian' is big-endian
#define ENDIAN_VALUE_LE_BE(endian,leval,beval)  (((endian) == ENDIANNESS_LITTLE) ? (leval) : (beval))

// endian-based value: first value is if native endianness is little-endian, second is if native is big-endian
#define NATIVE_ENDIAN_VALUE_LE_BE(leval,beval)  ENDIAN_VALUE_LE_BE(ENDIANNESS_NATIVE, leval, beval)

// endian-based value: first value is if 'endian' matches native, second is if 'endian' doesn't match native
#define ENDIAN_VALUE_NE_NNE(endian,neval,nneval) (((endian) == ENDIANNESS_NATIVE) ? (neval) : (nneval))


<<<<<<< HEAD
// useful macros to deal with bit shuffling encryptions
#define BIT(x,n) (((x)>>(n))&1)

#define BITSWAP8(val,B7,B6,B5,B4,B3,B2,B1,B0) \
	((BIT(val,B7) << 7) | (BIT(val,B6) << 6) | (BIT(val,B5) << 5) | (BIT(val,B4) << 4) | \
		(BIT(val,B3) << 3) | (BIT(val,B2) << 2) | (BIT(val,B1) << 1) | (BIT(val,B0) << 0))

#define BITSWAP16(val,B15,B14,B13,B12,B11,B10,B9,B8,B7,B6,B5,B4,B3,B2,B1,B0) \
	((BIT(val,B15) << 15) | (BIT(val,B14) << 14) | (BIT(val,B13) << 13) | (BIT(val,B12) << 12) | \
		(BIT(val,B11) << 11) | (BIT(val,B10) << 10) | (BIT(val, B9) <<  9) | (BIT(val, B8) <<  8) | \
		(BIT(val, B7) <<  7) | (BIT(val, B6) <<  6) | (BIT(val, B5) <<  5) | (BIT(val, B4) <<  4) | \
		(BIT(val, B3) <<  3) | (BIT(val, B2) <<  2) | (BIT(val, B1) <<  1) | (BIT(val, B0) <<  0))

#define BITSWAP24(val,B23,B22,B21,B20,B19,B18,B17,B16,B15,B14,B13,B12,B11,B10,B9,B8,B7,B6,B5,B4,B3,B2,B1,B0) \
	((BIT(val,B23) << 23) | (BIT(val,B22) << 22) | (BIT(val,B21) << 21) | (BIT(val,B20) << 20) | \
		(BIT(val,B19) << 19) | (BIT(val,B18) << 18) | (BIT(val,B17) << 17) | (BIT(val,B16) << 16) | \
		(BIT(val,B15) << 15) | (BIT(val,B14) << 14) | (BIT(val,B13) << 13) | (BIT(val,B12) << 12) | \
		(BIT(val,B11) << 11) | (BIT(val,B10) << 10) | (BIT(val, B9) <<  9) | (BIT(val, B8) <<  8) | \
		(BIT(val, B7) <<  7) | (BIT(val, B6) <<  6) | (BIT(val, B5) <<  5) | (BIT(val, B4) <<  4) | \
		(BIT(val, B3) <<  3) | (BIT(val, B2) <<  2) | (BIT(val, B1) <<  1) | (BIT(val, B0) <<  0))

#define BITSWAP32(val,B31,B30,B29,B28,B27,B26,B25,B24,B23,B22,B21,B20,B19,B18,B17,B16,B15,B14,B13,B12,B11,B10,B9,B8,B7,B6,B5,B4,B3,B2,B1,B0) \
	((BIT(val,B31) << 31) | (BIT(val,B30) << 30) | (BIT(val,B29) << 29) | (BIT(val,B28) << 28) | \
		(BIT(val,B27) << 27) | (BIT(val,B26) << 26) | (BIT(val,B25) << 25) | (BIT(val,B24) << 24) | \
		(BIT(val,B23) << 23) | (BIT(val,B22) << 22) | (BIT(val,B21) << 21) | (BIT(val,B20) << 20) | \
		(BIT(val,B19) << 19) | (BIT(val,B18) << 18) | (BIT(val,B17) << 17) | (BIT(val,B16) << 16) | \
		(BIT(val,B15) << 15) | (BIT(val,B14) << 14) | (BIT(val,B13) << 13) | (BIT(val,B12) << 12) | \
		(BIT(val,B11) << 11) | (BIT(val,B10) << 10) | (BIT(val, B9) <<  9) | (BIT(val, B8) <<  8) | \
		(BIT(val, B7) <<  7) | (BIT(val, B6) <<  6) | (BIT(val, B5) <<  5) | (BIT(val, B4) <<  4) | \
		(BIT(val, B3) <<  3) | (BIT(val, B2) <<  2) | (BIT(val, B1) <<  1) | (BIT(val, B0) <<  0))
=======
// useful functions to deal with bit shuffling encryptions
template <typename T, typename U> constexpr T BIT(T x, U n) { return (x >> n) & T(1); }

template <typename T, typename U> constexpr T bitswap(T val, U b)
{
	return BIT(val, b) << 0U;
}

template <typename T, typename U, typename... V> constexpr T bitswap(T val, U b, V... c)
{
	return (BIT(val, b) << sizeof...(c)) | bitswap(val, c...);
}

template <unsigned B, typename T, typename... U> T bitswap(T val, U... b)
{
	static_assert(sizeof...(b) == B, "wrong number of bits");
	static_assert((sizeof(std::remove_reference_t<T>) * 8) >= B, "return type too small for result");
	return bitswap(val, b...);
}

// explicit versions that check number of bit position arguments
template <typename T, typename... U> constexpr T BITSWAP8(T val, U... b) {  return bitswap<8U>(val, b...); }
template <typename T, typename... U> constexpr T BITSWAP16(T val, U... b) {  return bitswap<16U>(val, b...); }
template <typename T, typename... U> constexpr T BITSWAP24(T val, U... b) {  return bitswap<24U>(val, b...); }
template <typename T, typename... U> constexpr T BITSWAP32(T val, U... b) {  return bitswap<32U>(val, b...); }
template <typename T, typename... U> constexpr T BITSWAP40(T val, U... b) {  return bitswap<40U>(val, b...); }
template <typename T, typename... U> constexpr T BITSWAP48(T val, U... b) {  return bitswap<48U>(val, b...); }
template <typename T, typename... U> constexpr T BITSWAP56(T val, U... b) {  return bitswap<56U>(val, b...); }
template <typename T, typename... U> constexpr T BITSWAP64(T val, U... b) {  return bitswap<64U>(val, b...); }
>>>>>>> upstream/master



//**************************************************************************
//  EXCEPTION CLASSES
//**************************************************************************

// emu_exception is the base class for all emu-related exceptions
class emu_exception : public std::exception { };


// emu_fatalerror is a generic fatal exception that provides an error string
class emu_fatalerror : public emu_exception
{
public:
	emu_fatalerror(const char *format, ...) ATTR_PRINTF(2,3);
	emu_fatalerror(const char *format, va_list ap);
	emu_fatalerror(int _exitcode, const char *format, ...) ATTR_PRINTF(3,4);
	emu_fatalerror(int _exitcode, const char *format, va_list ap);

	const char *string() const { return text; }
	int exitcode() const { return code; }

private:
	char text[1024];
	int code;
};

<<<<<<< HEAD

=======
class tag_add_exception
{
public:
	tag_add_exception(const char *tag) : m_tag(tag) { }
	const char *tag() const { return m_tag.c_str(); }
private:
	std::string m_tag;
};
>>>>>>> upstream/master

//**************************************************************************
//  CASTING TEMPLATES
//**************************************************************************

<<<<<<< HEAD
class device_t;

void report_bad_cast(const std::type_info &src_type, const std::type_info &dst_type);
void report_bad_device_cast(const device_t *dev, const std::type_info &src_type, const std::type_info &dst_type);

// template function for casting from a base class to a derived class that is checked
// in debug builds and fast in release builds
template<class _Dest, class _Source>
inline _Dest downcast(_Source *src)
{
#if defined(MAME_DEBUG) && !defined(MAME_DEBUG_FAST)
	try {
		if (dynamic_cast<_Dest>(src) != src)
		{
			if (dynamic_cast<const device_t *>(src) != NULL)
				report_bad_device_cast(dynamic_cast<const device_t *>(src), typeid(src), typeid(_Dest));
			else
				report_bad_cast(typeid(src), typeid(_Dest));
		}
	}
	catch (std::bad_cast &)
	{
		report_bad_cast(typeid(src), typeid(_Dest));
	}
#endif
	return static_cast<_Dest>(src);
}

template<class _Dest, class _Source>
inline _Dest downcast(_Source &src)
{
#if defined(MAME_DEBUG) && !defined(MAME_DEBUG_FAST)
	try {
		if (&dynamic_cast<_Dest>(src) != &src)
		{
			if (dynamic_cast<const device_t *>(&src) != NULL)
				report_bad_device_cast(dynamic_cast<const device_t *>(&src), typeid(src), typeid(_Dest));
			else
				report_bad_cast(typeid(src), typeid(_Dest));
		}
	}
	catch (std::bad_cast &)
	{
		report_bad_cast(typeid(src), typeid(_Dest));
	}
#endif
	return static_cast<_Dest>(src);
=======
void report_bad_cast(const std::type_info &src_type, const std::type_info &dst_type);
void report_bad_device_cast(const device_t *dev, const std::type_info &src_type, const std::type_info &dst_type);

template <typename Dest, typename Source>
inline std::enable_if_t<std::is_base_of<device_t, Source>::value> report_bad_cast(Source *const src)
{
	if (src) report_bad_device_cast(src, typeid(Source), typeid(Dest));
	else report_bad_cast(typeid(Source), typeid(Dest));
}

template <typename Dest, typename Source>
inline std::enable_if_t<!std::is_base_of<device_t, Source>::value> report_bad_cast(Source *const src)
{
	device_t const *dev(dynamic_cast<device_t const *>(src));
	if (dev) report_bad_device_cast(dev, typeid(Source), typeid(Dest));
	else report_bad_cast(typeid(Source), typeid(Dest));
}

// template function for casting from a base class to a derived class that is checked
// in debug builds and fast in release builds
template <typename Dest, typename Source>
inline Dest downcast(Source *src)
{
#if defined(MAME_DEBUG) && !defined(MAME_DEBUG_FAST)
	Dest const chk(dynamic_cast<Dest>(src));
	if (chk != src) report_bad_cast<std::remove_pointer_t<Dest>, Source>(src);
#endif
	return static_cast<Dest>(src);
}

template<class Dest, class Source>
inline Dest downcast(Source &src)
{
#if defined(MAME_DEBUG) && !defined(MAME_DEBUG_FAST)
	std::remove_reference_t<Dest> *const chk(dynamic_cast<std::remove_reference_t<Dest> *>(&src));
	if (chk != &src) report_bad_cast<std::remove_reference_t<Dest>, Source>(&src);
#endif
	return static_cast<Dest>(src);
}

// template function which takes a strongly typed enumerator and returns its value as a compile-time constant
template <typename E>
using enable_enum_t = typename std::enable_if_t<std::is_enum<E>::value, typename std::underlying_type_t<E>>;

template <typename E>
constexpr inline enable_enum_t<E>
underlying_value(E e) noexcept
{
	return static_cast< typename std::underlying_type<E>::type >( e );
}

// template function which takes an integral value and returns its representation as enumerator (even strongly typed)
template <typename E , typename T>
constexpr inline typename std::enable_if_t<std::is_enum<E>::value && std::is_integral<T>::value, E>
enum_value(T value) noexcept
{
	return static_cast<E>(value);
>>>>>>> upstream/master
}



//**************************************************************************
//  FUNCTION PROTOTYPES
//**************************************************************************

<<<<<<< HEAD
ATTR_NORETURN void fatalerror(const char *format, ...) ATTR_PRINTF(1,2);
ATTR_NORETURN void fatalerror_exitcode(running_machine &machine, int exitcode, const char *format, ...) ATTR_PRINTF(3,4);
=======
[[noreturn]] void fatalerror(const char *format, ...) ATTR_PRINTF(1,2);
[[noreturn]] void fatalerror_exitcode(running_machine &machine, int exitcode, const char *format, ...) ATTR_PRINTF(3,4);
>>>>>>> upstream/master

//**************************************************************************
//  INLINE FUNCTIONS
//**************************************************************************

// population count
#if !defined(__NetBSD__)
<<<<<<< HEAD
inline int popcount(UINT32 val)
=======
inline int popcount(u32 val)
>>>>>>> upstream/master
{
	int count;

	for (count = 0; val != 0; count++)
		val &= val - 1;
	return count;
}
#endif


// convert a series of 32 bits into a float
<<<<<<< HEAD
inline float u2f(UINT32 v)
{
	union {
		float ff;
		UINT32 vv;
=======
inline float u2f(u32 v)
{
	union {
		float ff;
		u32 vv;
>>>>>>> upstream/master
	} u;
	u.vv = v;
	return u.ff;
}


// convert a float into a series of 32 bits
<<<<<<< HEAD
inline UINT32 f2u(float f)
{
	union {
		float ff;
		UINT32 vv;
=======
inline u32 f2u(float f)
{
	union {
		float ff;
		u32 vv;
>>>>>>> upstream/master
	} u;
	u.ff = f;
	return u.vv;
}


// convert a series of 64 bits into a double
<<<<<<< HEAD
inline double u2d(UINT64 v)
{
	union {
		double dd;
		UINT64 vv;
=======
inline double u2d(u64 v)
{
	union {
		double dd;
		u64 vv;
>>>>>>> upstream/master
	} u;
	u.vv = v;
	return u.dd;
}


// convert a double into a series of 64 bits
<<<<<<< HEAD
inline UINT64 d2u(double d)
{
	union {
		double dd;
		UINT64 vv;
=======
inline u64 d2u(double d)
{
	union {
		double dd;
		u64 vv;
>>>>>>> upstream/master
	} u;
	u.dd = d;
	return u.vv;
}

<<<<<<< HEAD
#endif  /* __EMUCORE_H__ */
=======
#endif  /* MAME_EMU_EMUCORE_H */
>>>>>>> upstream/master
