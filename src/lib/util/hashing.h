// license:BSD-3-Clause
// copyright-holders:Aaron Giles
/***************************************************************************

    hashing.h

    Hashing helper classes.

***************************************************************************/

#pragma once

#ifndef __HASHING_H__
#define __HASHING_H__

#include "osdcore.h"
#include "corestr.h"
<<<<<<< HEAD
#include <string>
#include "md5.h"
#include "sha1.h"


=======
#include "md5.h"
#include "sha1.h"

#include <functional>
#include <string>


namespace util {
>>>>>>> upstream/master
//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************


// ======================> SHA-1

// final digest
struct sha1_t
{
	bool operator==(const sha1_t &rhs) const { return memcmp(m_raw, rhs.m_raw, sizeof(m_raw)) == 0; }
	bool operator!=(const sha1_t &rhs) const { return memcmp(m_raw, rhs.m_raw, sizeof(m_raw)) != 0; }
<<<<<<< HEAD
	operator UINT8 *() { return m_raw; }
	bool from_string(const char *string, int length = -1);
	const char *as_string(std::string &buffer) const;
	UINT8 m_raw[20];
=======
	operator uint8_t *() { return m_raw; }
	bool from_string(const char *string, int length = -1);
	std::string as_string() const;
	uint8_t m_raw[20];
>>>>>>> upstream/master
	static const sha1_t null;
};

// creation helper
class sha1_creator
{
public:
	// construction/destruction
	sha1_creator() { reset(); }

	// reset
	void reset() { sha1_init(&m_context); }

	// append data
<<<<<<< HEAD
	void append(const void *data, UINT32 length) { sha1_update(&m_context, length, reinterpret_cast<const UINT8 *>(data)); }
=======
	void append(const void *data, uint32_t length) { sha1_update(&m_context, length, reinterpret_cast<const uint8_t *>(data)); }
>>>>>>> upstream/master

	// finalize and compute the final digest
	sha1_t finish()
	{
		sha1_t result;
		sha1_final(&m_context);
		sha1_digest(&m_context, sizeof(result.m_raw), result.m_raw);
		return result;
	}

	// static wrapper to just get the digest from a block
<<<<<<< HEAD
	static sha1_t simple(const void *data, UINT32 length)
=======
	static sha1_t simple(const void *data, uint32_t length)
>>>>>>> upstream/master
	{
		sha1_creator creator;
		creator.append(data, length);
		return creator.finish();
	}

protected:
	// internal state
	struct sha1_ctx     m_context;      // internal context
};



// ======================> MD5

// final digest
struct md5_t
{
	bool operator==(const md5_t &rhs) const { return memcmp(m_raw, rhs.m_raw, sizeof(m_raw)) == 0; }
	bool operator!=(const md5_t &rhs) const { return memcmp(m_raw, rhs.m_raw, sizeof(m_raw)) != 0; }
<<<<<<< HEAD
	operator UINT8 *() { return m_raw; }
	bool from_string(const char *string, int length = -1);
	const char *as_string(std::string &buffer) const;
	UINT8 m_raw[16];
=======
	operator uint8_t *() { return m_raw; }
	bool from_string(const char *string, int length = -1);
	std::string as_string() const;
	uint8_t m_raw[16];
>>>>>>> upstream/master
	static const md5_t null;
};

// creation helper
class md5_creator
{
public:
	// construction/destruction
	md5_creator() { reset(); }

	// reset
	void reset() { MD5Init(&m_context); }

	// append data
<<<<<<< HEAD
	void append(const void *data, UINT32 length) { MD5Update(&m_context, reinterpret_cast<const unsigned char *>(data), length); }
=======
	void append(const void *data, uint32_t length) { MD5Update(&m_context, reinterpret_cast<const unsigned char *>(data), length); }
>>>>>>> upstream/master

	// finalize and compute the final digest
	md5_t finish()
	{
		md5_t result;
		MD5Final(result.m_raw, &m_context);
		return result;
	}

	// static wrapper to just get the digest from a block
<<<<<<< HEAD
	static md5_t simple(const void *data, UINT32 length)
=======
	static md5_t simple(const void *data, uint32_t length)
>>>>>>> upstream/master
	{
		md5_creator creator;
		creator.append(data, length);
		return creator.finish();
	}

protected:
	// internal state
	struct MD5Context   m_context;      // internal context
};



// ======================> CRC-32

// final digest
struct crc32_t
{
<<<<<<< HEAD
	bool operator==(const crc32_t &rhs) const { return m_raw == rhs.m_raw; }
	bool operator!=(const crc32_t &rhs) const { return m_raw != rhs.m_raw; }
	crc32_t &operator=(const UINT32 crc) { m_raw = crc; return *this; }
	operator UINT32() const { return m_raw; }
	bool from_string(const char *string, int length = -1);
	const char *as_string(std::string &buffer) const;
	UINT32 m_raw;
=======
	crc32_t() { }
	constexpr crc32_t(const crc32_t &rhs) = default;
	constexpr crc32_t(const uint32_t crc) : m_raw(crc) { }

	constexpr bool operator==(const crc32_t &rhs) const { return m_raw == rhs.m_raw; }
	constexpr bool operator!=(const crc32_t &rhs) const { return m_raw != rhs.m_raw; }

	crc32_t &operator=(const crc32_t &rhs) = default;
	crc32_t &operator=(const uint32_t crc) { m_raw = crc; return *this; }

	constexpr operator uint32_t() const { return m_raw; }

	bool from_string(const char *string, int length = -1);
	std::string as_string() const;

	uint32_t m_raw;

>>>>>>> upstream/master
	static const crc32_t null;
};

// creation helper
class crc32_creator
{
public:
	// construction/destruction
	crc32_creator() { reset(); }

	// reset
	void reset() { m_accum.m_raw = 0; }

	// append data
<<<<<<< HEAD
	void append(const void *data, UINT32 length);
=======
	void append(const void *data, uint32_t length);
>>>>>>> upstream/master

	// finalize and compute the final digest
	crc32_t finish() { return m_accum; }

	// static wrapper to just get the digest from a block
<<<<<<< HEAD
	static crc32_t simple(const void *data, UINT32 length)
=======
	static crc32_t simple(const void *data, uint32_t length)
>>>>>>> upstream/master
	{
		crc32_creator creator;
		creator.append(data, length);
		return creator.finish();
	}

protected:
	// internal state
	crc32_t             m_accum;        // internal accumulator
};



// ======================> CRC-16

// final digest
struct crc16_t
{
<<<<<<< HEAD
	bool operator==(const crc16_t &rhs) const { return m_raw == rhs.m_raw; }
	bool operator!=(const crc16_t &rhs) const { return m_raw != rhs.m_raw; }
	crc16_t &operator=(const UINT16 crc) { m_raw = crc; return *this; }
	operator UINT16() const { return m_raw; }
	bool from_string(const char *string, int length = -1);
	const char *as_string(std::string &buffer) const;
	UINT16 m_raw;
=======
	crc16_t() { }
	constexpr crc16_t(const crc16_t &rhs) = default;
	constexpr crc16_t(const uint16_t crc) : m_raw(crc) { }

	constexpr bool operator==(const crc16_t &rhs) const { return m_raw == rhs.m_raw; }
	constexpr bool operator!=(const crc16_t &rhs) const { return m_raw != rhs.m_raw; }

	crc16_t &operator=(const crc16_t &rhs) = default;
	crc16_t &operator=(const uint16_t crc) { m_raw = crc; return *this; }

	constexpr operator uint16_t() const { return m_raw; }

	bool from_string(const char *string, int length = -1);
	std::string as_string() const;

	uint16_t m_raw;

>>>>>>> upstream/master
	static const crc16_t null;
};

// creation helper
class crc16_creator
{
public:
	// construction/destruction
	crc16_creator() { reset(); }

	// reset
	void reset() { m_accum.m_raw = 0xffff; }

	// append data
<<<<<<< HEAD
	void append(const void *data, UINT32 length);
=======
	void append(const void *data, uint32_t length);
>>>>>>> upstream/master

	// finalize and compute the final digest
	crc16_t finish() { return m_accum; }

	// static wrapper to just get the digest from a block
<<<<<<< HEAD
	static crc16_t simple(const void *data, UINT32 length)
=======
	static crc16_t simple(const void *data, uint32_t length)
>>>>>>> upstream/master
	{
		crc16_creator creator;
		creator.append(data, length);
		return creator.finish();
	}

protected:
	// internal state
	crc16_t             m_accum;        // internal accumulator
};


<<<<<<< HEAD
=======
} // namespace util

namespace std {

template <> struct hash<::util::crc32_t>
{
	typedef ::util::crc32_t argument_type;
	typedef std::size_t result_type;
	result_type operator()(argument_type const & s) const { return std::hash<std::uint32_t>()(s); }
};

template <> struct hash<::util::crc16_t>
{
	typedef ::util::crc16_t argument_type;
	typedef std::size_t result_type;
	result_type operator()(argument_type const & s) const { return std::hash<std::uint16_t>()(s); }
};

} // namespace std

>>>>>>> upstream/master
#endif // __HASHING_H__
