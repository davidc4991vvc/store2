// license:BSD-3-Clause
// copyright-holders:Aaron Giles
/***************************************************************************

    chdcodec.h

    Codecs used by the CHD format

***************************************************************************/

#pragma once

#ifndef __CHDCODEC_H__
#define __CHDCODEC_H__

#include "osdcore.h"
<<<<<<< HEAD
=======
#include "coretmpl.h"
>>>>>>> upstream/master


#define CHDCODEC_VERIFY_COMPRESSION 0


//**************************************************************************
//  MACROS
//**************************************************************************

#define CHD_MAKE_TAG(a,b,c,d)       (((a) << 24) | ((b) << 16) | ((c) << 8) | (d))



//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

// forward references
class chd_file;

// base types
<<<<<<< HEAD
typedef UINT32 chd_codec_type;
=======
typedef uint32_t chd_codec_type;
>>>>>>> upstream/master


// ======================> chd_codec

// common base class for all compressors and decompressors
class chd_codec
{
protected:
	// can't create these directly
<<<<<<< HEAD
	chd_codec(chd_file &file, UINT32 hunkbytes, bool lossy);
=======
	chd_codec(chd_file &file, uint32_t hunkbytes, bool lossy);
>>>>>>> upstream/master

public:
	// allow public deletion
	virtual ~chd_codec();

	// accessors
	chd_file &chd() const { return m_chd; }
<<<<<<< HEAD
	UINT32 hunkbytes() const { return m_hunkbytes; }
=======
	uint32_t hunkbytes() const { return m_hunkbytes; }
>>>>>>> upstream/master
	bool lossy() const { return m_lossy; }

	// implementation
	virtual void configure(int param, void *config);

private:
	// internal state
	chd_file &          m_chd;
<<<<<<< HEAD
	UINT32              m_hunkbytes;
=======
	uint32_t              m_hunkbytes;
>>>>>>> upstream/master
	bool                m_lossy;
};


// ======================> chd_compressor

// base class for all compressors
class chd_compressor : public chd_codec
{
protected:
	// can't create these directly
<<<<<<< HEAD
	chd_compressor(chd_file &file, UINT32 hunkbytes, bool lossy);

public:
	// implementation
	virtual UINT32 compress(const UINT8 *src, UINT32 srclen, UINT8 *dest) = 0;
=======
	chd_compressor(chd_file &file, uint32_t hunkbytes, bool lossy);

public:
	// implementation
	virtual uint32_t compress(const uint8_t *src, uint32_t srclen, uint8_t *dest) = 0;
>>>>>>> upstream/master
};


// ======================> chd_decompressor

// base class for all decompressors
class chd_decompressor : public chd_codec
{
protected:
	// can't create these directly
<<<<<<< HEAD
	chd_decompressor(chd_file &file, UINT32 hunkbytes, bool lossy);

public:
	// implementation
	virtual void decompress(const UINT8 *src, UINT32 complen, UINT8 *dest, UINT32 destlen) = 0;
=======
	chd_decompressor(chd_file &file, uint32_t hunkbytes, bool lossy);

public:
	// implementation
	virtual void decompress(const uint8_t *src, uint32_t complen, uint8_t *dest, uint32_t destlen) = 0;
>>>>>>> upstream/master
};


// ======================> chd_codec_list

// wrapper to get at the list of codecs
class chd_codec_list
{
public:
	// create compressors or decompressors
	static chd_compressor *new_compressor(chd_codec_type type, chd_file &file);
	static chd_decompressor *new_decompressor(chd_codec_type type, chd_file &file);

	// utilities
<<<<<<< HEAD
	static bool codec_exists(chd_codec_type type) { return (find_in_list(type) != NULL); }
=======
	static bool codec_exists(chd_codec_type type) { return (find_in_list(type) != nullptr); }
>>>>>>> upstream/master
	static const char *codec_name(chd_codec_type type);

private:
	// an entry in the list
	struct codec_entry
	{
		chd_codec_type      m_type;
		bool                m_lossy;
		const char *        m_name;
<<<<<<< HEAD
		chd_compressor *    (*m_construct_compressor)(chd_file &, UINT32, bool);
		chd_decompressor *  (*m_construct_decompressor)(chd_file &, UINT32, bool);
=======
		chd_compressor *    (*m_construct_compressor)(chd_file &, uint32_t, bool);
		chd_decompressor *  (*m_construct_decompressor)(chd_file &, uint32_t, bool);
>>>>>>> upstream/master
	};

	// internal helper functions
	static const codec_entry *find_in_list(chd_codec_type type);

	template<class _CompressorClass>
<<<<<<< HEAD
	static chd_compressor *construct_compressor(chd_file &chd, UINT32 hunkbytes, bool lossy) { return new _CompressorClass(chd, hunkbytes, lossy); }

	template<class _DecompressorClass>
	static chd_decompressor *construct_decompressor(chd_file &chd, UINT32 hunkbytes, bool lossy) { return new _DecompressorClass(chd, hunkbytes, lossy); }
=======
	static chd_compressor *construct_compressor(chd_file &chd, uint32_t hunkbytes, bool lossy) { return new _CompressorClass(chd, hunkbytes, lossy); }

	template<class _DecompressorClass>
	static chd_decompressor *construct_decompressor(chd_file &chd, uint32_t hunkbytes, bool lossy) { return new _DecompressorClass(chd, hunkbytes, lossy); }
>>>>>>> upstream/master

	// the static list
	static const codec_entry s_codec_list[];
};


// ======================> chd_compressor_group

// helper class that wraps several compressors
class chd_compressor_group
{
public:
	// construction/destruction
	chd_compressor_group(chd_file &file, chd_codec_type compressor_list[4]);
	~chd_compressor_group();

	// find the best compressor
<<<<<<< HEAD
	INT8 find_best_compressor(const UINT8 *src, UINT8 *compressed, UINT32 &complen);

private:
	// internal state
	UINT32                  m_hunkbytes;        // number of bytes in a hunk
	chd_compressor *        m_compressor[4];    // array of active codecs
	dynamic_buffer          m_compress_test;    // test buffer for compression
#if CHDCODEC_VERIFY_COMPRESSION
	chd_decompressor *      m_decompressor[4];  // array of active codecs
	dynamic_buffer          m_decompressed;     // verification buffer
=======
	int8_t find_best_compressor(const uint8_t *src, uint8_t *compressed, uint32_t &complen);

private:
	// internal state
	uint32_t                  m_hunkbytes;        // number of bytes in a hunk
	chd_compressor *        m_compressor[4];    // array of active codecs
	std::vector<uint8_t>          m_compress_test;    // test buffer for compression
#if CHDCODEC_VERIFY_COMPRESSION
	chd_decompressor *      m_decompressor[4];  // array of active codecs
	std::vector<uint8_t>          m_decompressed;     // verification buffer
>>>>>>> upstream/master
#endif
};



//**************************************************************************
//  CONSTANTS
//**************************************************************************

// currently-defined codecs
const chd_codec_type CHD_CODEC_NONE         = 0;

// general codecs
const chd_codec_type CHD_CODEC_ZLIB         = CHD_MAKE_TAG('z','l','i','b');
const chd_codec_type CHD_CODEC_LZMA         = CHD_MAKE_TAG('l','z','m','a');
const chd_codec_type CHD_CODEC_HUFFMAN      = CHD_MAKE_TAG('h','u','f','f');
const chd_codec_type CHD_CODEC_FLAC         = CHD_MAKE_TAG('f','l','a','c');

// general codecs with CD frontend
const chd_codec_type CHD_CODEC_CD_ZLIB      = CHD_MAKE_TAG('c','d','z','l');
const chd_codec_type CHD_CODEC_CD_LZMA      = CHD_MAKE_TAG('c','d','l','z');
const chd_codec_type CHD_CODEC_CD_FLAC      = CHD_MAKE_TAG('c','d','f','l');

// A/V codecs
const chd_codec_type CHD_CODEC_AVHUFF       = CHD_MAKE_TAG('a','v','h','u');

// A/V codec configuration parameters
enum
{
	AVHUFF_CODEC_DECOMPRESS_CONFIG = 1
};


#endif // __CHDCODEC_H__
