// license:BSD-3-Clause
// copyright-holders:Aaron Giles
/***************************************************************************

    avhuff.h

    Audio/video compression and decompression helpers.

***************************************************************************/

#pragma once

#ifndef __AVHUFF_H__
#define __AVHUFF_H__

#include "osdcore.h"
#include "coretmpl.h"
#include "bitmap.h"
#include "huffman.h"
#include "flac.h"


//**************************************************************************
//  CONSTANTS
//**************************************************************************

#define AVHUFF_USE_FLAC     (1)


// errors
enum avhuff_error
{
	AVHERR_NONE = 0,
	AVHERR_INVALID_DATA,
	AVHERR_VIDEO_TOO_LARGE,
	AVHERR_AUDIO_TOO_LARGE,
	AVHERR_METADATA_TOO_LARGE,
	AVHERR_OUT_OF_MEMORY,
	AVHERR_COMPRESSION_ERROR,
	AVHERR_TOO_MANY_CHANNELS,
	AVHERR_INVALID_CONFIGURATION,
	AVHERR_INVALID_PARAMETER,
	AVHERR_BUFFER_TOO_SMALL
};



//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

// ======================> av_codec_decompress_config

// decompression configuration
class avhuff_decompress_config
{
public:
	avhuff_decompress_config()
		: maxsamples(0),
<<<<<<< HEAD
			actsamples(NULL),
			maxmetalength(0),
			actmetalength(NULL),
			metadata(NULL)
=======
			actsamples(nullptr),
			maxmetalength(0),
			actmetalength(nullptr),
			metadata(nullptr)
>>>>>>> upstream/master
	{
		memset(audio, 0, sizeof(audio));
	}

	bitmap_yuy16 video;                     // pointer to video bitmap
<<<<<<< HEAD
	UINT32      maxsamples;                 // maximum number of samples per channel
	UINT32 *    actsamples;                 // actual number of samples per channel
	INT16 *     audio[16];                  // pointer to individual audio channels
	UINT32      maxmetalength;              // maximum length of metadata
	UINT32 *    actmetalength;              // actual length of metadata
	UINT8 *     metadata;                   // pointer to metadata buffer
=======
	uint32_t      maxsamples;                 // maximum number of samples per channel
	uint32_t *    actsamples;                 // actual number of samples per channel
	int16_t *     audio[16];                  // pointer to individual audio channels
	uint32_t      maxmetalength;              // maximum length of metadata
	uint32_t *    actmetalength;              // actual length of metadata
	uint8_t *     metadata;                   // pointer to metadata buffer
>>>>>>> upstream/master
};


// ======================> avhuff_encoder

// core state for the codec
class avhuff_encoder
{
public:
	// construction/destruction
	avhuff_encoder();

	// encode/decode
<<<<<<< HEAD
	avhuff_error encode_data(const UINT8 *source, UINT8 *dest, UINT32 &complength);

	// static helpers
	static UINT32 raw_data_size(const UINT8 *data);
	static UINT32 raw_data_size(UINT32 width, UINT32 height, UINT8 channels, UINT32 numsamples, UINT32 metadatasize = 0) { return 12 + channels * numsamples * 2 + width * height * 2; }
	static avhuff_error assemble_data(dynamic_buffer &buffer, bitmap_yuy16 &bitmap, UINT8 channels, UINT32 numsamples, INT16 **samples, UINT8 *metadata = NULL, UINT32 metadatasize = 0);
=======
	avhuff_error encode_data(const uint8_t *source, uint8_t *dest, uint32_t &complength);

	// static helpers
	static uint32_t raw_data_size(const uint8_t *data);
	static uint32_t raw_data_size(uint32_t width, uint32_t height, uint8_t channels, uint32_t numsamples, uint32_t metadatasize = 0) { return 12 + channels * numsamples * 2 + width * height * 2; }
	static avhuff_error assemble_data(std::vector<uint8_t> &buffer, bitmap_yuy16 &bitmap, uint8_t channels, uint32_t numsamples, int16_t **samples, uint8_t *metadata = nullptr, uint32_t metadatasize = 0);
>>>>>>> upstream/master

private:
	// delta-RLE Huffman encoder
	class deltarle_encoder
	{
	public:
		// construction/destruction
		deltarle_encoder()
			: m_rlecount(0) { }

		// histogramming
<<<<<<< HEAD
		UINT16 *rle_and_histo_bitmap(const UINT8 *source, UINT32 items_per_row, UINT32 item_advance, UINT32 row_count);

		// encoding
		void flush_rle() { m_rlecount = 0; }
		void encode_one(bitstream_out &bitbuf, UINT16 *&rleptr);
=======
		uint16_t *rle_and_histo_bitmap(const uint8_t *source, uint32_t items_per_row, uint32_t item_advance, uint32_t row_count);

		// encoding
		void flush_rle() { m_rlecount = 0; }
		void encode_one(bitstream_out &bitbuf, uint16_t *&rleptr);
>>>>>>> upstream/master
		huffman_error export_tree_rle(bitstream_out &bitbuf) { return m_encoder.export_tree_rle(bitbuf); }

	private:
		// internal state
		int                         m_rlecount;
		huffman_encoder<256 + 16>   m_encoder;
<<<<<<< HEAD
		std::vector<UINT16>       m_rlebuffer;
	};

	// internal helpers
	avhuff_error encode_audio(const UINT8 *source, int channels, int samples, UINT8 *dest, UINT8 *sizes);
	avhuff_error encode_video(const UINT8 *source, int width, int height, UINT8 *dest, UINT32 &complength);
	avhuff_error encode_video_lossless(const UINT8 *source, int width, int height, UINT8 *dest, UINT32 &complength);
=======
		std::vector<uint16_t>       m_rlebuffer;
	};

	// internal helpers
	avhuff_error encode_audio(const uint8_t *source, int channels, int samples, uint8_t *dest, uint8_t *sizes);
	avhuff_error encode_video(const uint8_t *source, int width, int height, uint8_t *dest, uint32_t &complength);
	avhuff_error encode_video_lossless(const uint8_t *source, int width, int height, uint8_t *dest, uint32_t &complength);
>>>>>>> upstream/master

	// video encoding contexts
	deltarle_encoder            m_ycontext;
	deltarle_encoder            m_cbcontext;
	deltarle_encoder            m_crcontext;

	// audio encoding contexts
<<<<<<< HEAD
	dynamic_buffer              m_audiobuffer;
=======
	std::vector<uint8_t>              m_audiobuffer;
>>>>>>> upstream/master
#if AVHUFF_USE_FLAC
	flac_encoder                m_flac_encoder;
#else
	huffman_8bit_encoder        m_audiohi_encoder;
	huffman_8bit_encoder        m_audiolo_encoder;
#endif
};


// ======================> avhuff_decoder

// core state for the codec
class avhuff_decoder
{
public:
	// construction/destruction
	avhuff_decoder();

	// configuration
	void configure(const avhuff_decompress_config &config);

	// encode/decode
<<<<<<< HEAD
	avhuff_error decode_data(const UINT8 *source, UINT32 complength, UINT8 *dest);
=======
	avhuff_error decode_data(const uint8_t *source, uint32_t complength, uint8_t *dest);
>>>>>>> upstream/master

private:
	// delta-RLE Huffman decoder
	class deltarle_decoder
	{
	public:
		// construction/destruction
		deltarle_decoder()
			: m_rlecount(0), m_prevdata(0) { }

		// general
		void reset() { m_rlecount = m_prevdata = 0; }

		// decoding
		void flush_rle() { m_rlecount = 0; }
<<<<<<< HEAD
		UINT32 decode_one(bitstream_in &bitbuf);
=======
		uint32_t decode_one(bitstream_in &bitbuf);
>>>>>>> upstream/master
		huffman_error import_tree_rle(bitstream_in &bitbuf) { return m_decoder.import_tree_rle(bitbuf); }

	private:
		// internal state
		int                         m_rlecount;
<<<<<<< HEAD
		UINT8                       m_prevdata;
=======
		uint8_t                       m_prevdata;
>>>>>>> upstream/master
		huffman_decoder<256 + 16>   m_decoder;
	};


	// internal helpers
<<<<<<< HEAD
	avhuff_error decode_audio(int channels, int samples, const UINT8 *source, UINT8 **dest, UINT32 dxor, const UINT8 *sizes);
	avhuff_error decode_video(int width, int height, const UINT8 *source, UINT32 complength, UINT8 *dest, UINT32 dstride, UINT32 dxor);
	avhuff_error decode_video_lossless(int width, int height, const UINT8 *source, UINT32 complength, UINT8 *dest, UINT32 dstride, UINT32 dxor);
=======
	avhuff_error decode_audio(int channels, int samples, const uint8_t *source, uint8_t **dest, uint32_t dxor, const uint8_t *sizes);
	avhuff_error decode_video(int width, int height, const uint8_t *source, uint32_t complength, uint8_t *dest, uint32_t dstride, uint32_t dxor);
	avhuff_error decode_video_lossless(int width, int height, const uint8_t *source, uint32_t complength, uint8_t *dest, uint32_t dstride, uint32_t dxor);
>>>>>>> upstream/master

	// internal state
	avhuff_decompress_config    m_config;

	// video decoding contexts
	deltarle_decoder            m_ycontext;
	deltarle_decoder            m_cbcontext;
	deltarle_decoder            m_crcontext;

	// audio decoding contexts
	huffman_8bit_decoder        m_audiohi_decoder;
	huffman_8bit_decoder        m_audiolo_decoder;
#if AVHUFF_USE_FLAC
	flac_decoder                m_flac_decoder;
#endif
};


#endif
