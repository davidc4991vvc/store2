// license:BSD-3-Clause
// copyright-holders:Aaron Giles
/***************************************************************************

    chd.h

    MAME Compressed Hunks of Data file format

***************************************************************************/

#pragma once

#ifndef __CHD_H__
#define __CHD_H__

#include "osdcore.h"
#include "coretmpl.h"
#include "corestr.h"
#include <string>
#include "bitmap.h"
#include "corefile.h"
#include "hashing.h"
#include "chdcodec.h"
<<<<<<< HEAD

=======
#include <atomic>
>>>>>>> upstream/master

/***************************************************************************

    Compressed Hunks of Data header format. All numbers are stored in
    Motorola (big-endian) byte ordering.

    =========================================================================

    V1 header:

    [  0] char   tag[8];        // 'MComprHD'
<<<<<<< HEAD
    [  8] UINT32 length;        // length of header (including tag and length fields)
    [ 12] UINT32 version;       // drive format version
    [ 16] UINT32 flags;         // flags (see below)
    [ 20] UINT32 compression;   // compression type
    [ 24] UINT32 hunksize;      // 512-byte sectors per hunk
    [ 28] UINT32 totalhunks;    // total # of hunks represented
    [ 32] UINT32 cylinders;     // number of cylinders on hard disk
    [ 36] UINT32 heads;         // number of heads on hard disk
    [ 40] UINT32 sectors;       // number of sectors on hard disk
    [ 44] UINT8  md5[16];       // MD5 checksum of raw data
    [ 60] UINT8  parentmd5[16]; // MD5 checksum of parent file
=======
    [  8] uint32_t length;        // length of header (including tag and length fields)
    [ 12] uint32_t version;       // drive format version
    [ 16] uint32_t flags;         // flags (see below)
    [ 20] uint32_t compression;   // compression type
    [ 24] uint32_t hunksize;      // 512-byte sectors per hunk
    [ 28] uint32_t totalhunks;    // total # of hunks represented
    [ 32] uint32_t cylinders;     // number of cylinders on hard disk
    [ 36] uint32_t heads;         // number of heads on hard disk
    [ 40] uint32_t sectors;       // number of sectors on hard disk
    [ 44] uint8_t  md5[16];       // MD5 checksum of raw data
    [ 60] uint8_t  parentmd5[16]; // MD5 checksum of parent file
>>>>>>> upstream/master
    [ 76] (V1 header length)

    Flags:
        0x00000001 - set if this drive has a parent
        0x00000002 - set if this drive allows writes

    Compression types:
        CHDCOMPRESSION_NONE = 0
        CHDCOMPRESSION_ZLIB = 1

    V1 map format:

<<<<<<< HEAD
    [  0] UINT64 offset : 44;   // starting offset within the file
    [  0] UINT64 length : 20;   // length of data; if == hunksize, data is uncompressed
=======
    [  0] uint64_t offset : 44;   // starting offset within the file
    [  0] uint64_t length : 20;   // length of data; if == hunksize, data is uncompressed
>>>>>>> upstream/master

    =========================================================================

    V2 header:

    [  0] char   tag[8];        // 'MComprHD'
<<<<<<< HEAD
    [  8] UINT32 length;        // length of header (including tag and length fields)
    [ 12] UINT32 version;       // drive format version
    [ 16] UINT32 flags;         // flags (see below)
    [ 20] UINT32 compression;   // compression type
    [ 24] UINT32 hunksize;      // seclen-byte sectors per hunk
    [ 28] UINT32 totalhunks;    // total # of hunks represented
    [ 32] UINT32 cylinders;     // number of cylinders on hard disk
    [ 36] UINT32 heads;         // number of heads on hard disk
    [ 40] UINT32 sectors;       // number of sectors on hard disk
    [ 44] UINT8  md5[16];       // MD5 checksum of raw data
    [ 60] UINT8  parentmd5[16]; // MD5 checksum of parent file
    [ 76] UINT32 seclen;        // number of bytes per sector
=======
    [  8] uint32_t length;        // length of header (including tag and length fields)
    [ 12] uint32_t version;       // drive format version
    [ 16] uint32_t flags;         // flags (see below)
    [ 20] uint32_t compression;   // compression type
    [ 24] uint32_t hunksize;      // seclen-byte sectors per hunk
    [ 28] uint32_t totalhunks;    // total # of hunks represented
    [ 32] uint32_t cylinders;     // number of cylinders on hard disk
    [ 36] uint32_t heads;         // number of heads on hard disk
    [ 40] uint32_t sectors;       // number of sectors on hard disk
    [ 44] uint8_t  md5[16];       // MD5 checksum of raw data
    [ 60] uint8_t  parentmd5[16]; // MD5 checksum of parent file
    [ 76] uint32_t seclen;        // number of bytes per sector
>>>>>>> upstream/master
    [ 80] (V2 header length)

    Flags and map format are same as V1

    =========================================================================

    V3 header:

    [  0] char   tag[8];        // 'MComprHD'
<<<<<<< HEAD
    [  8] UINT32 length;        // length of header (including tag and length fields)
    [ 12] UINT32 version;       // drive format version
    [ 16] UINT32 flags;         // flags (see below)
    [ 20] UINT32 compression;   // compression type
    [ 24] UINT32 totalhunks;    // total # of hunks represented
    [ 28] UINT64 logicalbytes;  // logical size of the data (in bytes)
    [ 36] UINT64 metaoffset;    // offset to the first blob of metadata
    [ 44] UINT8  md5[16];       // MD5 checksum of raw data
    [ 60] UINT8  parentmd5[16]; // MD5 checksum of parent file
    [ 76] UINT32 hunkbytes;     // number of bytes per hunk
    [ 80] UINT8  sha1[20];      // SHA1 checksum of raw data
    [100] UINT8  parentsha1[20];// SHA1 checksum of parent file
=======
    [  8] uint32_t length;        // length of header (including tag and length fields)
    [ 12] uint32_t version;       // drive format version
    [ 16] uint32_t flags;         // flags (see below)
    [ 20] uint32_t compression;   // compression type
    [ 24] uint32_t totalhunks;    // total # of hunks represented
    [ 28] uint64_t logicalbytes;  // logical size of the data (in bytes)
    [ 36] uint64_t metaoffset;    // offset to the first blob of metadata
    [ 44] uint8_t  md5[16];       // MD5 checksum of raw data
    [ 60] uint8_t  parentmd5[16]; // MD5 checksum of parent file
    [ 76] uint32_t hunkbytes;     // number of bytes per hunk
    [ 80] uint8_t  sha1[20];      // SHA1 checksum of raw data
    [100] uint8_t  parentsha1[20];// SHA1 checksum of parent file
>>>>>>> upstream/master
    [120] (V3 header length)

    Flags are the same as V1

    Compression types:
        CHDCOMPRESSION_NONE = 0
        CHDCOMPRESSION_ZLIB = 1
        CHDCOMPRESSION_ZLIB_PLUS = 2

    V3 map format:

<<<<<<< HEAD
    [  0] UINT64 offset;        // starting offset within the file
    [  8] UINT32 crc32;         // 32-bit CRC of the uncompressed data
    [ 12] UINT16 length_lo;     // lower 16 bits of length
    [ 14] UINT8 length_hi;      // upper 8 bits of length
    [ 15] UINT8 flags;          // flags, indicating compression info
=======
    [  0] uint64_t offset;        // starting offset within the file
    [  8] uint32_t crc32;         // 32-bit CRC of the uncompressed data
    [ 12] uint16_t length_lo;     // lower 16 bits of length
    [ 14] uint8_t length_hi;      // upper 8 bits of length
    [ 15] uint8_t flags;          // flags, indicating compression info
>>>>>>> upstream/master

    =========================================================================

    V4 header:

    [  0] char   tag[8];        // 'MComprHD'
<<<<<<< HEAD
    [  8] UINT32 length;        // length of header (including tag and length fields)
    [ 12] UINT32 version;       // drive format version
    [ 16] UINT32 flags;         // flags (see below)
    [ 20] UINT32 compression;   // compression type
    [ 24] UINT32 totalhunks;    // total # of hunks represented
    [ 28] UINT64 logicalbytes;  // logical size of the data (in bytes)
    [ 36] UINT64 metaoffset;    // offset to the first blob of metadata
    [ 44] UINT32 hunkbytes;     // number of bytes per hunk
    [ 48] UINT8  sha1[20];      // combined raw+meta SHA1
    [ 68] UINT8  parentsha1[20];// combined raw+meta SHA1 of parent
    [ 88] UINT8  rawsha1[20];   // raw data SHA1
=======
    [  8] uint32_t length;        // length of header (including tag and length fields)
    [ 12] uint32_t version;       // drive format version
    [ 16] uint32_t flags;         // flags (see below)
    [ 20] uint32_t compression;   // compression type
    [ 24] uint32_t totalhunks;    // total # of hunks represented
    [ 28] uint64_t logicalbytes;  // logical size of the data (in bytes)
    [ 36] uint64_t metaoffset;    // offset to the first blob of metadata
    [ 44] uint32_t hunkbytes;     // number of bytes per hunk
    [ 48] uint8_t  sha1[20];      // combined raw+meta SHA1
    [ 68] uint8_t  parentsha1[20];// combined raw+meta SHA1 of parent
    [ 88] uint8_t  rawsha1[20];   // raw data SHA1
>>>>>>> upstream/master
    [108] (V4 header length)

    Flags are the same as V1

    Compression types:
        CHDCOMPRESSION_NONE = 0
        CHDCOMPRESSION_ZLIB = 1
        CHDCOMPRESSION_ZLIB_PLUS = 2
        CHDCOMPRESSION_AV = 3

    Map format is the same as V3

    =========================================================================

    V5 header:

    [  0] char   tag[8];        // 'MComprHD'
<<<<<<< HEAD
    [  8] UINT32 length;        // length of header (including tag and length fields)
    [ 12] UINT32 version;       // drive format version
    [ 16] UINT32 compressors[4];// which custom compressors are used?
    [ 32] UINT64 logicalbytes;  // logical size of the data (in bytes)
    [ 40] UINT64 mapoffset;     // offset to the map
    [ 48] UINT64 metaoffset;    // offset to the first blob of metadata
    [ 56] UINT32 hunkbytes;     // number of bytes per hunk (512k maximum)
    [ 60] UINT32 unitbytes;     // number of bytes per unit within each hunk
    [ 64] UINT8  rawsha1[20];   // raw data SHA1
    [ 84] UINT8  sha1[20];      // combined raw+meta SHA1
    [104] UINT8  parentsha1[20];// combined raw+meta SHA1 of parent
=======
    [  8] uint32_t length;        // length of header (including tag and length fields)
    [ 12] uint32_t version;       // drive format version
    [ 16] uint32_t compressors[4];// which custom compressors are used?
    [ 32] uint64_t logicalbytes;  // logical size of the data (in bytes)
    [ 40] uint64_t mapoffset;     // offset to the map
    [ 48] uint64_t metaoffset;    // offset to the first blob of metadata
    [ 56] uint32_t hunkbytes;     // number of bytes per hunk (512k maximum)
    [ 60] uint32_t unitbytes;     // number of bytes per unit within each hunk
    [ 64] uint8_t  rawsha1[20];   // raw data SHA1
    [ 84] uint8_t  sha1[20];      // combined raw+meta SHA1
    [104] uint8_t  parentsha1[20];// combined raw+meta SHA1 of parent
>>>>>>> upstream/master
    [124] (V5 header length)

    If parentsha1 != 0, we have a parent (no need for flags)
    If compressors[0] == 0, we are uncompressed (including maps)

    V5 uncompressed map format:

<<<<<<< HEAD
    [  0] UINT32 offset;        // starting offset / hunk size

    V5 compressed map format header:

    [  0] UINT32 length;        // length of compressed map
    [  4] UINT48 datastart;     // offset of first block
    [ 10] UINT16 crc;           // crc-16 of the map
    [ 12] UINT8 lengthbits;     // bits used to encode complength
    [ 13] UINT8 hunkbits;       // bits used to encode self-refs
    [ 14] UINT8 parentunitbits; // bits used to encode parent unit refs
    [ 15] UINT8 reserved;       // future use
=======
    [  0] uint32_t offset;        // starting offset / hunk size

    V5 compressed map format header:

    [  0] uint32_t length;        // length of compressed map
    [  4] UINT48 datastart;     // offset of first block
    [ 10] uint16_t crc;           // crc-16 of the map
    [ 12] uint8_t lengthbits;     // bits used to encode complength
    [ 13] uint8_t hunkbits;       // bits used to encode self-refs
    [ 14] uint8_t parentunitbits; // bits used to encode parent unit refs
    [ 15] uint8_t reserved;       // future use
>>>>>>> upstream/master
    [ 16] (compressed header length)

    Each compressed map entry, once expanded, looks like:

<<<<<<< HEAD
    [  0] UINT8 compression;    // compression type
    [  1] UINT24 complength;    // compressed length
    [  4] UINT48 offset;        // offset
    [ 10] UINT16 crc;           // crc-16 of the data
=======
    [  0] uint8_t compression;    // compression type
    [  1] UINT24 complength;    // compressed length
    [  4] UINT48 offset;        // offset
    [ 10] uint16_t crc;           // crc-16 of the data
>>>>>>> upstream/master

***************************************************************************/


//**************************************************************************
//  CONSTANTS
//**************************************************************************

// pseudo-codecs returned by hunk_info
const chd_codec_type CHD_CODEC_SELF         = 1;    // copy of another hunk
const chd_codec_type CHD_CODEC_PARENT       = 2;    // copy of a parent's hunk
const chd_codec_type CHD_CODEC_MINI         = 3;    // legacy "mini" 8-byte repeat

// core types
<<<<<<< HEAD
typedef UINT32 chd_metadata_tag;

// metadata parameters
const chd_metadata_tag CHDMETATAG_WILDCARD = 0;
const UINT32 CHDMETAINDEX_APPEND = ~0;

// metadata flags
const UINT8 CHD_MDFLAGS_CHECKSUM = 0x01;        // indicates data is checksummed
=======
typedef uint32_t chd_metadata_tag;

// metadata parameters
const chd_metadata_tag CHDMETATAG_WILDCARD = 0;
const uint32_t CHDMETAINDEX_APPEND = ~0;

// metadata flags
const uint8_t CHD_MDFLAGS_CHECKSUM = 0x01;        // indicates data is checksummed
>>>>>>> upstream/master

// standard hard disk metadata
const chd_metadata_tag HARD_DISK_METADATA_TAG = CHD_MAKE_TAG('G','D','D','D');
extern const char *HARD_DISK_METADATA_FORMAT;

// hard disk identify information
const chd_metadata_tag HARD_DISK_IDENT_METADATA_TAG = CHD_MAKE_TAG('I','D','N','T');

// hard disk key information
const chd_metadata_tag HARD_DISK_KEY_METADATA_TAG = CHD_MAKE_TAG('K','E','Y',' ');

// pcmcia CIS information
const chd_metadata_tag PCMCIA_CIS_METADATA_TAG = CHD_MAKE_TAG('C','I','S',' ');

// standard CD-ROM metadata
const chd_metadata_tag CDROM_OLD_METADATA_TAG = CHD_MAKE_TAG('C','H','C','D');
const chd_metadata_tag CDROM_TRACK_METADATA_TAG = CHD_MAKE_TAG('C','H','T','R');
extern const char *CDROM_TRACK_METADATA_FORMAT;
const chd_metadata_tag CDROM_TRACK_METADATA2_TAG = CHD_MAKE_TAG('C','H','T','2');
extern const char *CDROM_TRACK_METADATA2_FORMAT;
const chd_metadata_tag GDROM_OLD_METADATA_TAG = CHD_MAKE_TAG('C','H','G','T');
const chd_metadata_tag GDROM_TRACK_METADATA_TAG = CHD_MAKE_TAG('C', 'H', 'G', 'D');
extern const char *GDROM_TRACK_METADATA_FORMAT;

// standard A/V metadata
const chd_metadata_tag AV_METADATA_TAG = CHD_MAKE_TAG('A','V','A','V');
extern const char *AV_METADATA_FORMAT;

// A/V laserdisc frame metadata
const chd_metadata_tag AV_LD_METADATA_TAG = CHD_MAKE_TAG('A','V','L','D');

// error types
enum chd_error
{
	CHDERR_NONE,
	CHDERR_NO_INTERFACE,
	CHDERR_OUT_OF_MEMORY,
	CHDERR_NOT_OPEN,
	CHDERR_ALREADY_OPEN,
	CHDERR_INVALID_FILE,
	CHDERR_INVALID_PARAMETER,
	CHDERR_INVALID_DATA,
	CHDERR_FILE_NOT_FOUND,
	CHDERR_REQUIRES_PARENT,
	CHDERR_FILE_NOT_WRITEABLE,
	CHDERR_READ_ERROR,
	CHDERR_WRITE_ERROR,
	CHDERR_CODEC_ERROR,
	CHDERR_INVALID_PARENT,
	CHDERR_HUNK_OUT_OF_RANGE,
	CHDERR_DECOMPRESSION_ERROR,
	CHDERR_COMPRESSION_ERROR,
	CHDERR_CANT_CREATE_FILE,
	CHDERR_CANT_VERIFY,
	CHDERR_NOT_SUPPORTED,
	CHDERR_METADATA_NOT_FOUND,
	CHDERR_INVALID_METADATA_SIZE,
	CHDERR_UNSUPPORTED_VERSION,
	CHDERR_VERIFY_INCOMPLETE,
	CHDERR_INVALID_METADATA,
	CHDERR_INVALID_STATE,
	CHDERR_OPERATION_PENDING,
	CHDERR_UNSUPPORTED_FORMAT,
	CHDERR_UNKNOWN_COMPRESSION,
	CHDERR_WALKING_PARENT,
	CHDERR_COMPRESSING
};



//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

class chd_codec;


// ======================> chd_file

// core file class
class chd_file
{
	friend class chd_file_compressor;
	friend class chd_verifier;

	// constants
<<<<<<< HEAD
	static const UINT32 HEADER_VERSION = 5;
	static const UINT32 V3_HEADER_SIZE = 120;
	static const UINT32 V4_HEADER_SIZE = 108;
	static const UINT32 V5_HEADER_SIZE = 124;
	static const UINT32 MAX_HEADER_SIZE = V5_HEADER_SIZE;
=======
	static const uint32_t HEADER_VERSION = 5;
	static const uint32_t V3_HEADER_SIZE = 120;
	static const uint32_t V4_HEADER_SIZE = 108;
	static const uint32_t V5_HEADER_SIZE = 124;
	static const uint32_t MAX_HEADER_SIZE = V5_HEADER_SIZE;
>>>>>>> upstream/master

public:
	// construction/destruction
	chd_file();
	virtual ~chd_file();

	// operators
<<<<<<< HEAD
	operator core_file *() { return m_file; }

	// getters
	bool opened() const { return (m_file != NULL); }
	UINT32 version() const { return m_version; }
	UINT64 logical_bytes() const { return m_logicalbytes; }
	UINT32 hunk_bytes() const { return m_hunkbytes; }
	UINT32 hunk_count() const { return m_hunkcount; }
	UINT32 unit_bytes() const { return m_unitbytes; }
	UINT64 unit_count() const { return m_unitcount; }
	bool compressed() const { return (m_compression[0] != CHD_CODEC_NONE); }
	chd_codec_type compression(int index) const { return m_compression[index]; }
	chd_file *parent() const { return m_parent; }
	sha1_t sha1();
	sha1_t raw_sha1();
	sha1_t parent_sha1();
	chd_error hunk_info(UINT32 hunknum, chd_codec_type &compressor, UINT32 &compbytes);

	// setters
	void set_raw_sha1(sha1_t rawdata);
	void set_parent_sha1(sha1_t parent);

	// file create
	chd_error create(const char *filename, UINT64 logicalbytes, UINT32 hunkbytes, UINT32 unitbytes, chd_codec_type compression[4]);
	chd_error create(core_file &file, UINT64 logicalbytes, UINT32 hunkbytes, UINT32 unitbytes, chd_codec_type compression[4]);
	chd_error create(const char *filename, UINT64 logicalbytes, UINT32 hunkbytes, chd_codec_type compression[4], chd_file &parent);
	chd_error create(core_file &file, UINT64 logicalbytes, UINT32 hunkbytes, chd_codec_type compression[4], chd_file &parent);

	// file open
	chd_error open(const char *filename, bool writeable = false, chd_file *parent = NULL);
	chd_error open(core_file &file, bool writeable = false, chd_file *parent = NULL);
=======
	operator util::core_file &() { return *m_file; }

	// getters
	bool opened() const { return (m_file != nullptr); }
	uint32_t version() const { return m_version; }
	uint64_t logical_bytes() const { return m_logicalbytes; }
	uint32_t hunk_bytes() const { return m_hunkbytes; }
	uint32_t hunk_count() const { return m_hunkcount; }
	uint32_t unit_bytes() const { return m_unitbytes; }
	uint64_t unit_count() const { return m_unitcount; }
	bool compressed() const { return (m_compression[0] != CHD_CODEC_NONE); }
	chd_codec_type compression(int index) const { return m_compression[index]; }
	chd_file *parent() const { return m_parent; }
	util::sha1_t sha1();
	util::sha1_t raw_sha1();
	util::sha1_t parent_sha1();
	chd_error hunk_info(uint32_t hunknum, chd_codec_type &compressor, uint32_t &compbytes);

	// setters
	void set_raw_sha1(util::sha1_t rawdata);
	void set_parent_sha1(util::sha1_t parent);

	// file create
	chd_error create(const char *filename, uint64_t logicalbytes, uint32_t hunkbytes, uint32_t unitbytes, chd_codec_type compression[4]);
	chd_error create(util::core_file &file, uint64_t logicalbytes, uint32_t hunkbytes, uint32_t unitbytes, chd_codec_type compression[4]);
	chd_error create(const char *filename, uint64_t logicalbytes, uint32_t hunkbytes, chd_codec_type compression[4], chd_file &parent);
	chd_error create(util::core_file &file, uint64_t logicalbytes, uint32_t hunkbytes, chd_codec_type compression[4], chd_file &parent);

	// file open
	chd_error open(const char *filename, bool writeable = false, chd_file *parent = nullptr);
	chd_error open(util::core_file &file, bool writeable = false, chd_file *parent = nullptr);
>>>>>>> upstream/master

	// file close
	void close();

	// read/write
<<<<<<< HEAD
	chd_error read_hunk(UINT32 hunknum, void *buffer);
	chd_error write_hunk(UINT32 hunknum, const void *buffer);
	chd_error read_units(UINT64 unitnum, void *buffer, UINT32 count = 1);
	chd_error write_units(UINT64 unitnum, const void *buffer, UINT32 count = 1);
	chd_error read_bytes(UINT64 offset, void *buffer, UINT32 bytes);
	chd_error write_bytes(UINT64 offset, const void *buffer, UINT32 bytes);

	// metadata management
	chd_error read_metadata(chd_metadata_tag searchtag, UINT32 searchindex, std::string &output);
	chd_error read_metadata(chd_metadata_tag searchtag, UINT32 searchindex, dynamic_buffer &output);
	chd_error read_metadata(chd_metadata_tag searchtag, UINT32 searchindex, void *output, UINT32 outputlen, UINT32 &resultlen);
	chd_error read_metadata(chd_metadata_tag searchtag, UINT32 searchindex, dynamic_buffer &output, chd_metadata_tag &resulttag, UINT8 &resultflags);
	chd_error write_metadata(chd_metadata_tag metatag, UINT32 metaindex, const void *inputbuf, UINT32 inputlen, UINT8 flags = CHD_MDFLAGS_CHECKSUM);
	chd_error write_metadata(chd_metadata_tag metatag, UINT32 metaindex, const std::string &input, UINT8 flags = CHD_MDFLAGS_CHECKSUM) { return write_metadata(metatag, metaindex, input.c_str(), input.length() + 1, flags); }
	chd_error write_metadata(chd_metadata_tag metatag, UINT32 metaindex, const dynamic_buffer &input, UINT8 flags = CHD_MDFLAGS_CHECKSUM) { return write_metadata(metatag, metaindex, &input[0], input.size(), flags); }
	chd_error delete_metadata(chd_metadata_tag metatag, UINT32 metaindex);
	chd_error clone_all_metadata(chd_file &source);

	// hashing helper
	sha1_t compute_overall_sha1(sha1_t rawsha1);
=======
	chd_error read_hunk(uint32_t hunknum, void *buffer);
	chd_error write_hunk(uint32_t hunknum, const void *buffer);
	chd_error read_units(uint64_t unitnum, void *buffer, uint32_t count = 1);
	chd_error write_units(uint64_t unitnum, const void *buffer, uint32_t count = 1);
	chd_error read_bytes(uint64_t offset, void *buffer, uint32_t bytes);
	chd_error write_bytes(uint64_t offset, const void *buffer, uint32_t bytes);

	// metadata management
	chd_error read_metadata(chd_metadata_tag searchtag, uint32_t searchindex, std::string &output);
	chd_error read_metadata(chd_metadata_tag searchtag, uint32_t searchindex, std::vector<uint8_t> &output);
	chd_error read_metadata(chd_metadata_tag searchtag, uint32_t searchindex, void *output, uint32_t outputlen, uint32_t &resultlen);
	chd_error read_metadata(chd_metadata_tag searchtag, uint32_t searchindex, std::vector<uint8_t> &output, chd_metadata_tag &resulttag, uint8_t &resultflags);
	chd_error write_metadata(chd_metadata_tag metatag, uint32_t metaindex, const void *inputbuf, uint32_t inputlen, uint8_t flags = CHD_MDFLAGS_CHECKSUM);
	chd_error write_metadata(chd_metadata_tag metatag, uint32_t metaindex, const std::string &input, uint8_t flags = CHD_MDFLAGS_CHECKSUM) { return write_metadata(metatag, metaindex, input.c_str(), input.length() + 1, flags); }
	chd_error write_metadata(chd_metadata_tag metatag, uint32_t metaindex, const std::vector<uint8_t> &input, uint8_t flags = CHD_MDFLAGS_CHECKSUM) { return write_metadata(metatag, metaindex, &input[0], input.size(), flags); }
	chd_error delete_metadata(chd_metadata_tag metatag, uint32_t metaindex);
	chd_error clone_all_metadata(chd_file &source);

	// hashing helper
	util::sha1_t compute_overall_sha1(util::sha1_t rawsha1);
>>>>>>> upstream/master

	// codec interfaces
	chd_error codec_configure(chd_codec_type codec, int param, void *config);

	// static helpers
	static const char *error_string(chd_error err);

private:
	struct metadata_entry;
	struct metadata_hash;

	// inline helpers
<<<<<<< HEAD
	UINT64 be_read(const UINT8 *base, int numbytes);
	void be_write(UINT8 *base, UINT64 value, int numbytes);
	sha1_t be_read_sha1(const UINT8 *base);
	void be_write_sha1(UINT8 *base, sha1_t value);
	void file_read(UINT64 offset, void *dest, UINT32 length);
	void file_write(UINT64 offset, const void *source, UINT32 length);
	UINT64 file_append(const void *source, UINT32 length, UINT32 alignment = 0);
	UINT8 bits_for_value(UINT64 value);

	// internal helpers
	UINT32 guess_unitbytes();
	void parse_v3_header(UINT8 *rawheader, sha1_t &parentsha1);
	void parse_v4_header(UINT8 *rawheader, sha1_t &parentsha1);
	void parse_v5_header(UINT8 *rawheader, sha1_t &parentsha1);
=======
	uint64_t be_read(const uint8_t *base, int numbytes);
	void be_write(uint8_t *base, uint64_t value, int numbytes);
	util::sha1_t be_read_sha1(const uint8_t *base);
	void be_write_sha1(uint8_t *base, util::sha1_t value);
	void file_read(uint64_t offset, void *dest, uint32_t length);
	void file_write(uint64_t offset, const void *source, uint32_t length);
	uint64_t file_append(const void *source, uint32_t length, uint32_t alignment = 0);
	uint8_t bits_for_value(uint64_t value);

	// internal helpers
	uint32_t guess_unitbytes();
	void parse_v3_header(uint8_t *rawheader, util::sha1_t &parentsha1);
	void parse_v4_header(uint8_t *rawheader, util::sha1_t &parentsha1);
	void parse_v5_header(uint8_t *rawheader, util::sha1_t &parentsha1);
>>>>>>> upstream/master
	chd_error compress_v5_map();
	void decompress_v5_map();
	chd_error create_common();
	chd_error open_common(bool writeable);
	void create_open_common();
<<<<<<< HEAD
	void verify_proper_compression_append(UINT32 hunknum);
	void hunk_write_compressed(UINT32 hunknum, INT8 compression, const UINT8 *compressed, UINT32 complength, crc16_t crc16);
	void hunk_copy_from_self(UINT32 hunknum, UINT32 otherhunk);
	void hunk_copy_from_parent(UINT32 hunknum, UINT64 parentunit);
	bool metadata_find(chd_metadata_tag metatag, INT32 metaindex, metadata_entry &metaentry, bool resume = false);
	void metadata_set_previous_next(UINT64 prevoffset, UINT64 nextoffset);
=======
	void verify_proper_compression_append(uint32_t hunknum);
	void hunk_write_compressed(uint32_t hunknum, int8_t compression, const uint8_t *compressed, uint32_t complength, util::crc16_t crc16);
	void hunk_copy_from_self(uint32_t hunknum, uint32_t otherhunk);
	void hunk_copy_from_parent(uint32_t hunknum, uint64_t parentunit);
	bool metadata_find(chd_metadata_tag metatag, int32_t metaindex, metadata_entry &metaentry, bool resume = false);
	void metadata_set_previous_next(uint64_t prevoffset, uint64_t nextoffset);
>>>>>>> upstream/master
	void metadata_update_hash();
	static int CLIB_DECL metadata_hash_compare(const void *elem1, const void *elem2);

	// file characteristics
<<<<<<< HEAD
	core_file *             m_file;             // handle to the open core file
=======
	util::core_file *       m_file;             // handle to the open core file
>>>>>>> upstream/master
	bool                    m_owns_file;        // flag indicating if this file should be closed on chd_close()
	bool                    m_allow_reads;      // permit reads from this CHD?
	bool                    m_allow_writes;     // permit writes to this CHD?

	// core parameters from the header
<<<<<<< HEAD
	UINT32                  m_version;          // version of the header
	UINT64                  m_logicalbytes;     // logical size of the raw CHD data in bytes
	UINT64                  m_mapoffset;        // offset of map
	UINT64                  m_metaoffset;       // offset to first metadata bit
	UINT32                  m_hunkbytes;        // size of each raw hunk in bytes
	UINT32                  m_hunkcount;        // number of hunks represented
	UINT32                  m_unitbytes;        // size of each unit in bytes
	UINT64                  m_unitcount;        // number of units represented
	chd_codec_type          m_compression[4];   // array of compression types used
	chd_file *              m_parent;           // pointer to parent file, or NULL if none
	bool                    m_parent_missing;   // are we missing our parent?

	// key offsets within the header
	UINT64                  m_mapoffset_offset; // offset of map offset field
	UINT64                  m_metaoffset_offset;// offset of metaoffset field
	UINT64                  m_sha1_offset;      // offset of SHA1 field
	UINT64                  m_rawsha1_offset;   // offset of raw SHA1 field
	UINT64                  m_parentsha1_offset;// offset of paren SHA1 field

	// map information
	UINT32                  m_mapentrybytes;    // length of each entry in a map
	dynamic_buffer          m_rawmap;           // raw map data

	// compression management
	chd_decompressor *      m_decompressor[4];  // array of decompression codecs
	dynamic_buffer          m_compressed;       // temporary buffer for compressed data

	// caching
	dynamic_buffer          m_cache;            // single-hunk cache for partial reads/writes
	UINT32                  m_cachehunk;        // which hunk is in the cache?
=======
	uint32_t                  m_version;          // version of the header
	uint64_t                  m_logicalbytes;     // logical size of the raw CHD data in bytes
	uint64_t                  m_mapoffset;        // offset of map
	uint64_t                  m_metaoffset;       // offset to first metadata bit
	uint32_t                  m_hunkbytes;        // size of each raw hunk in bytes
	uint32_t                  m_hunkcount;        // number of hunks represented
	uint32_t                  m_unitbytes;        // size of each unit in bytes
	uint64_t                  m_unitcount;        // number of units represented
	chd_codec_type          m_compression[4];   // array of compression types used
	chd_file *              m_parent;           // pointer to parent file, or nullptr if none
	bool                    m_parent_missing;   // are we missing our parent?

	// key offsets within the header
	uint64_t                  m_mapoffset_offset; // offset of map offset field
	uint64_t                  m_metaoffset_offset;// offset of metaoffset field
	uint64_t                  m_sha1_offset;      // offset of SHA1 field
	uint64_t                  m_rawsha1_offset;   // offset of raw SHA1 field
	uint64_t                  m_parentsha1_offset;// offset of paren SHA1 field

	// map information
	uint32_t                  m_mapentrybytes;    // length of each entry in a map
	std::vector<uint8_t>          m_rawmap;           // raw map data

	// compression management
	chd_decompressor *      m_decompressor[4];  // array of decompression codecs
	std::vector<uint8_t>          m_compressed;       // temporary buffer for compressed data

	// caching
	std::vector<uint8_t>          m_cache;            // single-hunk cache for partial reads/writes
	uint32_t                  m_cachehunk;        // which hunk is in the cache?
>>>>>>> upstream/master
};


// ======================> chd_file_compressor

// class for creating a new compressed CHD
class chd_file_compressor : public chd_file
{
public:
	// construction/destruction
	chd_file_compressor();
	virtual ~chd_file_compressor();

	// compression management
	void compress_begin();
	chd_error compress_continue(double &progress, double &ratio);

protected:
	// required override: read more data
<<<<<<< HEAD
	virtual UINT32 read_data(void *dest, UINT64 offset, UINT32 length) = 0;
=======
	virtual uint32_t read_data(void *dest, uint64_t offset, uint32_t length) = 0;
>>>>>>> upstream/master

private:
	// hash map for looking up values
	class hashmap
	{
	public:
		// construction/destruction
		hashmap();
		~hashmap();

		// operations
		void reset();
<<<<<<< HEAD
		UINT64 find(crc16_t crc16, sha1_t sha1);
		void add(UINT64 itemnum, crc16_t crc16, sha1_t sha1);

		// constants
		static const UINT64 NOT_FOUND = ~UINT64(0);
=======
		uint64_t find(util::crc16_t crc16, util::sha1_t sha1);
		void add(uint64_t itemnum, util::crc16_t crc16, util::sha1_t sha1);

		// constants
		static const uint64_t NOT_FOUND = ~uint64_t(0);
>>>>>>> upstream/master
	private:
		// internal entry
		struct entry_t
		{
			entry_t *           m_next;             // next entry in list
<<<<<<< HEAD
			UINT64              m_itemnum;          // item number
			sha1_t              m_sha1;             // SHA-1 of the block
=======
			uint64_t              m_itemnum;          // item number
			util::sha1_t        m_sha1;             // SHA-1 of the block
>>>>>>> upstream/master
		};

		// block of entries
		struct entry_block
		{
			entry_block(entry_block *prev)
				: m_next(prev), m_nextalloc(0) { }

			entry_block *       m_next;             // next block in list
<<<<<<< HEAD
			UINT32              m_nextalloc;        // next to be allocated
=======
			uint32_t              m_nextalloc;        // next to be allocated
>>>>>>> upstream/master
			entry_t             m_array[16384];     // array of entries
		};

		// internal state
		entry_t *           m_map[65536];           // map, hashed by CRC-16
		entry_block *       m_block_list;           // list of allocated blocks
	};

	// status of a given work item
	enum work_status
	{
		WS_READY = 0,
		WS_READING,
		WS_QUEUED,
		WS_COMPLETE
	};

	// a CRC-16/SHA-1 pair
	struct hash_pair
	{
<<<<<<< HEAD
		crc16_t             m_crc16;            // calculated CRC-16
		sha1_t              m_sha1;             // calculated SHA-1
=======
		util::crc16_t             m_crc16;            // calculated CRC-16
		util::sha1_t              m_sha1;             // calculated SHA-1
>>>>>>> upstream/master
	};

	// a single work item
	struct work_item
	{
		work_item()
<<<<<<< HEAD
			: m_osd(NULL)
			, m_compressor(NULL)
			, m_status(WS_READY)
			, m_data(NULL)
			, m_compressed(NULL)
			, m_complen(0)
			, m_compression(0)
			, m_codecs(NULL)
=======
			: m_osd(nullptr)
			, m_compressor(nullptr)
			, m_status(WS_READY)
			, m_hunknum(0)
			, m_data(nullptr)
			, m_compressed(nullptr)
			, m_complen(0)
			, m_compression(0)
			, m_codecs(nullptr)
>>>>>>> upstream/master
		{ }

		osd_work_item *     m_osd;              // OSD work item running on this block
		chd_file_compressor *m_compressor;      // pointer back to the compressor
		// TODO: had to change this to be able to use atomic_* functions on this
		//volatile work_status m_status;          // current status of this item
<<<<<<< HEAD
		volatile INT32      m_status;           // current status of this item
		UINT32              m_hunknum;          // number of the hunk we're working on
		UINT8 *             m_data;             // pointer to the data we are working on
		UINT8 *             m_compressed;       // pointer to the compressed data
		UINT32              m_complen;          // compressed data length
		INT8                m_compression;      // type of compression used
=======
		std::atomic<int32_t>  m_status;           // current status of this item
		uint32_t              m_hunknum;          // number of the hunk we're working on
		uint8_t *             m_data;             // pointer to the data we are working on
		uint8_t *             m_compressed;       // pointer to the compressed data
		uint32_t              m_complen;          // compressed data length
		int8_t                m_compression;      // type of compression used
>>>>>>> upstream/master
		chd_compressor_group *m_codecs;         // codec instance
		std::vector<hash_pair> m_hash;        // array of hashes
	};

	// internal helpers
	static void *async_walk_parent_static(void *param, int threadid);
	void async_walk_parent(work_item &item);
	static void *async_compress_hunk_static(void *param, int threadid);
	void async_compress_hunk(work_item &item, int threadid);
	static void *async_read_static(void *param, int threadid);
	void async_read();

	// current compression status
	bool                    m_walking_parent;   // are we building the parent map?
<<<<<<< HEAD
	UINT64                  m_total_in;         // total bytes in
	UINT64                  m_total_out;        // total bytes out
	sha1_creator            m_compsha1;         // running SHA-1 on raw data
=======
	uint64_t                  m_total_in;         // total bytes in
	uint64_t                  m_total_out;        // total bytes out
	util::sha1_creator      m_compsha1;         // running SHA-1 on raw data
>>>>>>> upstream/master

	// hash lookup maps
	hashmap                 m_parent_map;       // hash map for parent
	hashmap                 m_current_map;      // hash map for current

	// read I/O thread
	osd_work_queue *        m_read_queue;       // work queue for reading
<<<<<<< HEAD
	UINT64                  m_read_queue_offset;// next offset to enqueue
	UINT64                  m_read_done_offset; // next offset that will complete
=======
	uint64_t                  m_read_queue_offset;// next offset to enqueue
	uint64_t                  m_read_done_offset; // next offset that will complete
>>>>>>> upstream/master
	bool                    m_read_error;       // error during reading?

	// work item thread
	static const int WORK_BUFFER_HUNKS = 256;
	osd_work_queue *        m_work_queue;       // queue for doing work on other threads
<<<<<<< HEAD
	dynamic_buffer          m_work_buffer;      // buffer containing hunk data to work on
	dynamic_buffer          m_compressed_buffer;// buffer containing compressed data
=======
	std::vector<uint8_t>          m_work_buffer;      // buffer containing hunk data to work on
	std::vector<uint8_t>          m_compressed_buffer;// buffer containing compressed data
>>>>>>> upstream/master
	work_item               m_work_item[WORK_BUFFER_HUNKS]; // status of each hunk
	chd_compressor_group *  m_codecs[WORK_MAX_THREADS]; // codecs to use

	// output state
<<<<<<< HEAD
	UINT32                  m_write_hunk;       // next hunk to write
=======
	uint32_t                  m_write_hunk;       // next hunk to write
>>>>>>> upstream/master
};


#endif // __CHD_H__
