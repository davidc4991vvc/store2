// license:BSD-3-Clause
// copyright-holders:Aaron Giles
/***************************************************************************

    huffman.h

    Static Huffman compression and decompression helpers.

***************************************************************************/

#pragma once

#ifndef __HUFFMAN_H__
#define __HUFFMAN_H__

#include "osdcore.h"
#include "bitstream.h"


//**************************************************************************
//  CONSTANTS
//**************************************************************************

enum huffman_error
{
	HUFFERR_NONE = 0,
	HUFFERR_TOO_MANY_BITS,
	HUFFERR_INVALID_DATA,
	HUFFERR_INPUT_BUFFER_TOO_SMALL,
	HUFFERR_OUTPUT_BUFFER_TOO_SMALL,
	HUFFERR_INTERNAL_INCONSISTENCY,
	HUFFERR_TOO_MANY_CONTEXTS
};



//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

// ======================> huffman_context_base

// base class for encoding and decoding
class huffman_context_base
{
protected:
<<<<<<< HEAD
	typedef UINT16 lookup_value;
=======
	typedef uint16_t lookup_value;
>>>>>>> upstream/master

	// a node in the huffman tree
	struct node_t
	{
		node_t *            m_parent;               // pointer to parent node
<<<<<<< HEAD
		UINT32              m_count;                // number of hits on this node
		UINT32              m_weight;               // assigned weight of this node
		UINT32              m_bits;                 // bits used to encode the node
		UINT8               m_numbits;              // number of bits needed for this node
	};

	// construction/destruction
	huffman_context_base(int numcodes, int maxbits, lookup_value *lookup, UINT32 *histo, node_t *nodes);
=======
		uint32_t              m_count;                // number of hits on this node
		uint32_t              m_weight;               // assigned weight of this node
		uint32_t              m_bits;                 // bits used to encode the node
		uint8_t               m_numbits;              // number of bits needed for this node
	};

	// construction/destruction
	huffman_context_base(int numcodes, int maxbits, lookup_value *lookup, uint32_t *histo, node_t *nodes);
>>>>>>> upstream/master

	// tree creation
	huffman_error compute_tree_from_histo();

	// static tree import; huffman is notably more efficient
	huffman_error import_tree_rle(bitstream_in &bitbuf);
	huffman_error import_tree_huffman(bitstream_in &bitbuf);

	// static tree export
	huffman_error export_tree_rle(bitstream_out &bitbuf);
	huffman_error export_tree_huffman(bitstream_out &bitbuf);

	// internal helpers
	void write_rle_tree_bits(bitstream_out &bitbuf, int value, int repcount, int numbits);
	static int CLIB_DECL tree_node_compare(const void *item1, const void *item2);
<<<<<<< HEAD
	int build_tree(UINT32 totaldata, UINT32 totalweight);
=======
	int build_tree(uint32_t totaldata, uint32_t totalweight);
>>>>>>> upstream/master
	huffman_error assign_canonical_codes();
	void build_lookup_table();

protected:
	// internal state
<<<<<<< HEAD
	UINT32                  m_numcodes;             // number of total codes being processed
	UINT8                   m_maxbits;              // maximum bits per code
	UINT8                   m_prevdata;             // value of the previous data (for delta-RLE encoding)
	int                     m_rleremaining;         // number of RLE bytes remaining (for delta-RLE encoding)
	lookup_value *          m_lookup;               // pointer to the lookup table
	UINT32 *                m_datahisto;            // histogram of data values
=======
	uint32_t                  m_numcodes;             // number of total codes being processed
	uint8_t                   m_maxbits;              // maximum bits per code
	uint8_t                   m_prevdata;             // value of the previous data (for delta-RLE encoding)
	int                     m_rleremaining;         // number of RLE bytes remaining (for delta-RLE encoding)
	lookup_value *          m_lookup;               // pointer to the lookup table
	uint32_t *                m_datahisto;            // histogram of data values
>>>>>>> upstream/master
	node_t *                m_huffnode;             // array of nodes
};


// ======================> huffman_encoder

// template class for encoding
template<int _NumCodes = 256, int _MaxBits = 16>
class huffman_encoder : public huffman_context_base
{
public:
	// pass through to the underlying constructor
	huffman_encoder()
<<<<<<< HEAD
		: huffman_context_base(_NumCodes, _MaxBits, NULL, m_datahisto_array, m_huffnode_array) { histo_reset(); }

	// single item operations
	void histo_reset() { memset(m_datahisto_array, 0, sizeof(m_datahisto_array)); }
	void histo_one(UINT32 data);
	void encode_one(bitstream_out &bitbuf, UINT32 data);
=======
		: huffman_context_base(_NumCodes, _MaxBits, nullptr, m_datahisto_array, m_huffnode_array) { histo_reset(); }

	// single item operations
	void histo_reset() { memset(m_datahisto_array, 0, sizeof(m_datahisto_array)); }
	void histo_one(uint32_t data);
	void encode_one(bitstream_out &bitbuf, uint32_t data);
>>>>>>> upstream/master

	// expose tree computation and export
	using huffman_context_base::compute_tree_from_histo;
	using huffman_context_base::export_tree_rle;
	using huffman_context_base::export_tree_huffman;

private:
	// array versions of the info we need
<<<<<<< HEAD
	UINT32                  m_datahisto_array[_NumCodes];
=======
	uint32_t                  m_datahisto_array[_NumCodes];
>>>>>>> upstream/master
	node_t                  m_huffnode_array[_NumCodes * 2];
};


// ======================> huffman_decoder

// template class for decoding
template<int _NumCodes = 256, int _MaxBits = 16>
class huffman_decoder : public huffman_context_base
{
public:
	// pass through to the underlying constructor
	huffman_decoder()
<<<<<<< HEAD
		: huffman_context_base(_NumCodes, _MaxBits, m_lookup_array, NULL, m_huffnode_array) { }

	// single item operations
	UINT32 decode_one(bitstream_in &bitbuf);
=======
		: huffman_context_base(_NumCodes, _MaxBits, m_lookup_array, nullptr, m_huffnode_array) { }

	// single item operations
	uint32_t decode_one(bitstream_in &bitbuf);
>>>>>>> upstream/master

	// expose tree import
	using huffman_context_base::import_tree_rle;
	using huffman_context_base::import_tree_huffman;

private:
	// array versions of the info we need
	node_t                  m_huffnode_array[_NumCodes];
	lookup_value            m_lookup_array[1 << _MaxBits];
};


// ======================> huffman_8bit_encoder

// generic 8-bit encoder/decoder
class huffman_8bit_encoder : public huffman_encoder<>
{
public:
	// construction/destruction
	huffman_8bit_encoder();

	// operations
<<<<<<< HEAD
	huffman_error encode(const UINT8 *source, UINT32 slength, UINT8 *dest, UINT32 destlength, UINT32 &complength);
=======
	huffman_error encode(const uint8_t *source, uint32_t slength, uint8_t *dest, uint32_t destlength, uint32_t &complength);
>>>>>>> upstream/master
};


// ======================> huffman_8bit_decoder

// generic 8-bit encoder/decoder
class huffman_8bit_decoder : public huffman_decoder<>
{
public:
	// construction/destruction
	huffman_8bit_decoder();

	// operations
<<<<<<< HEAD
	huffman_error decode(const UINT8 *source, UINT32 slength, UINT8 *dest, UINT32 destlength);
=======
	huffman_error decode(const uint8_t *source, uint32_t slength, uint8_t *dest, uint32_t destlength);
>>>>>>> upstream/master
};



//**************************************************************************
//  INLINE FUNCTIONS
//**************************************************************************

//-------------------------------------------------
//  histo_one - update the histogram
//-------------------------------------------------

template<int _NumCodes, int _MaxBits>
<<<<<<< HEAD
inline void huffman_encoder<_NumCodes, _MaxBits>::histo_one(UINT32 data)
=======
inline void huffman_encoder<_NumCodes, _MaxBits>::histo_one(uint32_t data)
>>>>>>> upstream/master
{
	m_datahisto[data]++;
}


//-------------------------------------------------
//  encode_one - encode a single code to the
//  huffman stream
//-------------------------------------------------

template<int _NumCodes, int _MaxBits>
<<<<<<< HEAD
inline void huffman_encoder<_NumCodes, _MaxBits>::encode_one(bitstream_out &bitbuf, UINT32 data)
=======
inline void huffman_encoder<_NumCodes, _MaxBits>::encode_one(bitstream_out &bitbuf, uint32_t data)
>>>>>>> upstream/master
{
	// write the data
	node_t &node = m_huffnode[data];
	bitbuf.write(node.m_bits, node.m_numbits);
}


//-------------------------------------------------
//  decode_one - decode a single code from the
//  huffman stream
//-------------------------------------------------

template<int _NumCodes, int _MaxBits>
<<<<<<< HEAD
inline UINT32 huffman_decoder<_NumCodes, _MaxBits>::decode_one(bitstream_in &bitbuf)
{
	// peek ahead to get maxbits worth of data
	UINT32 bits = bitbuf.peek(m_maxbits);
=======
inline uint32_t huffman_decoder<_NumCodes, _MaxBits>::decode_one(bitstream_in &bitbuf)
{
	// peek ahead to get maxbits worth of data
	uint32_t bits = bitbuf.peek(m_maxbits);
>>>>>>> upstream/master

	// look it up, then remove the actual number of bits for this code
	lookup_value lookup = m_lookup[bits];
	bitbuf.remove(lookup & 0x1f);

	// return the value
	return lookup >> 5;
}


#endif
