// license:BSD-3-Clause
// copyright-holders:Angelo Salese
/*
 * NEC PC-6001 cassette format handling
 */

#include <assert.h>

#include "p6001_cas.h"

#define WAVE_HIGH        0x5a9e
#define WAVE_LOW        -0x5a9e

static int cas_size;

<<<<<<< HEAD
static int pc6001_fill_wave(INT16* buffer, UINT8 data, int sample_pos)
=======
static int pc6001_fill_wave(int16_t* buffer, uint8_t data, int sample_pos)
>>>>>>> upstream/master
{
	int x;
	int sample_count = 0;

	// one byte = 8 samples
	for(x=0;x<8;x++)
	{
		if(buffer)
			buffer[sample_pos+x] = ((data >> (7-x)) & 1) ? WAVE_HIGH : WAVE_LOW;
	}

	sample_count+=8;
	return sample_count;
}

<<<<<<< HEAD
static int pc6001_handle_cas(INT16* buffer, const UINT8* casdata)
=======
static int pc6001_handle_cas(int16_t* buffer, const uint8_t* casdata)
>>>>>>> upstream/master
{
	int sample_count = 0;
	int data_pos = 0;

	while(sample_count < cas_size)
	{
		sample_count += pc6001_fill_wave(buffer,casdata[data_pos],sample_count);
		data_pos++;
	}

	return sample_count;
}

/*******************************************************************
   Calculate the number of samples needed for this tape image
********************************************************************/
<<<<<<< HEAD
static int pc6001_cas_to_wav_size (const UINT8 *casdata, int caslen)
{
	cas_size = caslen*8;

	return pc6001_handle_cas(NULL,casdata);
=======
static int pc6001_cas_to_wav_size (const uint8_t *casdata, int caslen)
{
	cas_size = caslen*8;

	return pc6001_handle_cas(nullptr,casdata);
>>>>>>> upstream/master
}

/*******************************************************************
   Generate samples for the tape image
********************************************************************/
<<<<<<< HEAD
static int pc6001_cas_fill_wave(INT16 *buffer, int sample_count, UINT8 *bytes)
=======
static int pc6001_cas_fill_wave(int16_t *buffer, int sample_count, uint8_t *bytes)
>>>>>>> upstream/master
{
	return pc6001_handle_cas(buffer,bytes);
}

static const struct CassetteLegacyWaveFiller pc6001_legacy_fill_wave =
{
	pc6001_cas_fill_wave,                   /* fill_wave */
	-1,                                     /* chunk_size */
	0,                                      /* chunk_samples */
	pc6001_cas_to_wav_size,                 /* chunk_sample_calc */
	8000,                                   /* sample_frequency */
	0,                                      /* header_samples */
	0                                       /* trailer_samples */
};

<<<<<<< HEAD
static casserr_t pc6001_cas_identify(cassette_image *cassette, struct CassetteOptions *opts)
=======
static cassette_image::error pc6001_cas_identify(cassette_image *cassette, struct CassetteOptions *opts)
>>>>>>> upstream/master
{
	return cassette_legacy_identify(cassette, opts, &pc6001_legacy_fill_wave);
}



<<<<<<< HEAD
static casserr_t pc6001_cas_load(cassette_image *cassette)
=======
static cassette_image::error pc6001_cas_load(cassette_image *cassette)
>>>>>>> upstream/master
{
	return cassette_legacy_construct(cassette, &pc6001_legacy_fill_wave);
}


static const struct CassetteFormat pc6001_cassette_format = {
	"cas",
	pc6001_cas_identify,
	pc6001_cas_load,
<<<<<<< HEAD
	NULL
=======
	nullptr
>>>>>>> upstream/master
};

CASSETTE_FORMATLIST_START(pc6001_cassette_formats)
	CASSETTE_FORMAT(pc6001_cassette_format)
CASSETTE_FORMATLIST_END
