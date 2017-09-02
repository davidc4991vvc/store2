// license:BSD-3-Clause
// copyright-holders:Robbbert
/********************************************************************

Support for Samsung SPC-1000 cassette images


Tape formats:

TAP: This is a series of 0x30 and 0x31 bytes, representing binary
     0 and 1. It includes the header and leaders.

CAS: Files in this format consist of a 16 bytes header (SPC-1000.CASfmt )
     followed by cassette bits packed together (each byte of a .cas file
     are 8 bits, most significant bit first)

STA: This format has not been investigated yet, but is assumed to
     be the save state of some other emulator.

IPL: This seems a quickload format containing RAM dump, not a real tape

********************************************************************/

#include <assert.h>

#include "spc1000_cas.h"

#define WAVEENTRY_LOW  -32768
#define WAVEENTRY_HIGH  32767

#define SPC1000_WAV_FREQUENCY   17000

// image size
static int spc1000_image_size;

<<<<<<< HEAD
static int spc1000_put_samples(INT16 *buffer, int sample_pos, int count, int level)
=======
static int spc1000_put_samples(int16_t *buffer, int sample_pos, int count, int level)
>>>>>>> upstream/master
{
	if (buffer)
	{
		for (int i=0; i<count; i++)
			buffer[sample_pos + i] = level;
	}

	return count;
}

<<<<<<< HEAD
static int spc1000_output_bit(INT16 *buffer, int sample_pos, bool bit)
=======
static int spc1000_output_bit(int16_t *buffer, int sample_pos, bool bit)
>>>>>>> upstream/master
{
	int samples = 0;

	if (bit)
	{
		samples += spc1000_put_samples(buffer, sample_pos + samples, 9, WAVEENTRY_LOW);
		samples += spc1000_put_samples(buffer, sample_pos + samples, 9, WAVEENTRY_HIGH);
	}
	else
	{
		samples += spc1000_put_samples(buffer, sample_pos + samples, 4, WAVEENTRY_LOW);
		samples += spc1000_put_samples(buffer, sample_pos + samples, 4, WAVEENTRY_HIGH);
	}

	return samples;
}

<<<<<<< HEAD
static int spc1000_handle_tap(INT16 *buffer, const UINT8 *bytes)
{
	UINT32 sample_count = 0;

	/* data */
	for (UINT32 i = 0; i < spc1000_image_size; i++)
=======
static int spc1000_handle_tap(int16_t *buffer, const uint8_t *bytes)
{
	uint32_t sample_count = 0;

	/* data */
	for (uint32_t i = 0; i < spc1000_image_size; i++)
>>>>>>> upstream/master
		sample_count += spc1000_output_bit(buffer, sample_count, bytes[i] & 1);

	return sample_count;
}

<<<<<<< HEAD
static int spc1000_handle_cas(INT16 *buffer, const UINT8 *bytes)
{
	UINT32 sample_count = 0;

	/* data (skipping first 16 bytes, which is CAS header) */
	for (UINT32 i = 0x10; i < spc1000_image_size; i++)
=======
static int spc1000_handle_cas(int16_t *buffer, const uint8_t *bytes)
{
	uint32_t sample_count = 0;

	/* data (skipping first 16 bytes, which is CAS header) */
	for (uint32_t i = 0x10; i < spc1000_image_size; i++)
>>>>>>> upstream/master
		for (int j = 0; j < 8; j++)
			sample_count += spc1000_output_bit(buffer, sample_count, (bytes[i] >> (7 - j)) & 1);

	return sample_count;
}


/*******************************************************************
   Generate samples for the tape image
********************************************************************/

<<<<<<< HEAD
static int spc1000_tap_fill_wave(INT16 *buffer, int length, UINT8 *bytes)
=======
static int spc1000_tap_fill_wave(int16_t *buffer, int length, uint8_t *bytes)
>>>>>>> upstream/master
{
	return spc1000_handle_tap(buffer, bytes);
}

<<<<<<< HEAD
static int spc1000_cas_fill_wave(INT16 *buffer, int length, UINT8 *bytes)
=======
static int spc1000_cas_fill_wave(int16_t *buffer, int length, uint8_t *bytes)
>>>>>>> upstream/master
{
	return spc1000_handle_cas(buffer, bytes);
}

/*******************************************************************
   Calculate the number of samples needed for this tape image
********************************************************************/

<<<<<<< HEAD
static int spc1000_tap_calculate_size_in_samples(const UINT8 *bytes, int length)
{
	spc1000_image_size = length;

	return spc1000_handle_tap(NULL, bytes);
}

static int spc1000_cas_calculate_size_in_samples(const UINT8 *bytes, int length)
{
	spc1000_image_size = length;

	return spc1000_handle_cas(NULL, bytes);
=======
static int spc1000_tap_calculate_size_in_samples(const uint8_t *bytes, int length)
{
	spc1000_image_size = length;

	return spc1000_handle_tap(nullptr, bytes);
}

static int spc1000_cas_calculate_size_in_samples(const uint8_t *bytes, int length)
{
	spc1000_image_size = length;

	return spc1000_handle_cas(nullptr, bytes);
>>>>>>> upstream/master
}


/*******************************************************************
   Formats
 ********************************************************************/


// TAP
static const struct CassetteLegacyWaveFiller spc1000_tap_legacy_fill_wave =
{
	spc1000_tap_fill_wave,                 /* fill_wave */
	-1,                                     /* chunk_size */
	0,                                      /* chunk_samples */
	spc1000_tap_calculate_size_in_samples, /* chunk_sample_calc */
	SPC1000_WAV_FREQUENCY,                      /* sample_frequency */
	0,                                      /* header_samples */
	0                                       /* trailer_samples */
};

<<<<<<< HEAD
static casserr_t spc1000_tap_cassette_identify(cassette_image *cassette, struct CassetteOptions *opts)
=======
static cassette_image::error spc1000_tap_cassette_identify(cassette_image *cassette, struct CassetteOptions *opts)
>>>>>>> upstream/master
{
	return cassette_legacy_identify(cassette, opts, &spc1000_tap_legacy_fill_wave);
}

<<<<<<< HEAD
static casserr_t spc1000_tap_cassette_load(cassette_image *cassette)
=======
static cassette_image::error spc1000_tap_cassette_load(cassette_image *cassette)
>>>>>>> upstream/master
{
	return cassette_legacy_construct(cassette, &spc1000_tap_legacy_fill_wave);
}

static const struct CassetteFormat spc1000_tap_cassette_image_format =
{
	"tap",
	spc1000_tap_cassette_identify,
	spc1000_tap_cassette_load,
<<<<<<< HEAD
	NULL
=======
	nullptr
>>>>>>> upstream/master
};


// CAS
static const struct CassetteLegacyWaveFiller spc1000_cas_legacy_fill_wave =
{
	spc1000_cas_fill_wave,                 /* fill_wave */
	-1,                                     /* chunk_size */
	0,                                      /* chunk_samples */
	spc1000_cas_calculate_size_in_samples, /* chunk_sample_calc */
	SPC1000_WAV_FREQUENCY,                      /* sample_frequency */
	0,                                      /* header_samples */
	0                                       /* trailer_samples */
};

<<<<<<< HEAD
static casserr_t spc1000_cas_cassette_identify(cassette_image *cassette, struct CassetteOptions *opts)
=======
static cassette_image::error spc1000_cas_cassette_identify(cassette_image *cassette, struct CassetteOptions *opts)
>>>>>>> upstream/master
{
	return cassette_legacy_identify(cassette, opts, &spc1000_cas_legacy_fill_wave);
}

<<<<<<< HEAD
static casserr_t spc1000_cas_cassette_load(cassette_image *cassette)
=======
static cassette_image::error spc1000_cas_cassette_load(cassette_image *cassette)
>>>>>>> upstream/master
{
	return cassette_legacy_construct(cassette, &spc1000_cas_legacy_fill_wave);
}

static const struct CassetteFormat spc1000_cas_cassette_image_format =
{
	"cas",
	spc1000_cas_cassette_identify,
	spc1000_cas_cassette_load,
<<<<<<< HEAD
	NULL
=======
	nullptr
>>>>>>> upstream/master
};



CASSETTE_FORMATLIST_START(spc1000_cassette_formats)
	CASSETTE_FORMAT(spc1000_tap_cassette_image_format)
	CASSETTE_FORMAT(spc1000_cas_cassette_image_format)
CASSETTE_FORMATLIST_END
