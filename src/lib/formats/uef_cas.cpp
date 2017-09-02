// license:BSD-3-Clause
// copyright-holders:Wilbert Pol
/*

<<<<<<< HEAD
UEF format support (for electron driver)
=======
The UEF file format is designed to store accurate images of the common media types associated
with the BBC Micro, Acorn Electron and Atom. Tape storage is compatible with the CUTS/BYTE/Kansas City
Format, and hence the format is also capable of storing software for non-Acorn systems such as the
Altair 8800, PT SOL-20, Ohio Scientific, Compukit UK101, Nascom 1/2/3, Motorola MEK D1 6800 and
SWTPC 6800 kit based computers.

UEF files are chunk based and optionally compressed.
>>>>>>> upstream/master

The UEF format supports gzipped images, i'm doing the gunzip step during uef_cas_to_wav_size
because that is when the length of the original file is known. This is needed to determine
the size of memory to alloc for the decoding.

Not nice, but it works...

*/

#include <string.h>
#include <math.h>
#include <assert.h>

#include <zlib.h>
#include "uef_cas.h"


#define UEF_WAV_FREQUENCY   4800
#define WAVE_LOW    -32768
#define WAVE_HIGH   32767
#define WAVE_NULL   0

<<<<<<< HEAD
static const UINT8 UEF_HEADER[10] = { 0x55, 0x45, 0x46, 0x20, 0x46, 0x69, 0x6c, 0x65, 0x21, 0x00 };
=======
static const uint8_t UEF_HEADER[10] = { 0x55, 0x45, 0x46, 0x20, 0x46, 0x69, 0x6c, 0x65, 0x21, 0x00 };
static const uint8_t GZ_HEADER[2] = { 0x1f, 0x8b };
>>>>>>> upstream/master

/*
    bytes are stored as
    start bit   1 * 0
    data bits   8 * X
    stop bit    1 * 1
*/

/* gzip flag byte */
#define ASCII_FLAG  0x01 /* bit 0 set: file probably ascii text */
#define HEAD_CRC    0x02 /* bit 1 set: header CRC present */
#define EXTRA_FIELD 0x04 /* bit 2 set: extra field present */
#define ORIG_NAME   0x08 /* bit 3 set: original file name present */
#define COMMENT     0x10 /* bit 4 set: file comment present */
#define RESERVED    0xE0 /* bits 5..7: reserved */

<<<<<<< HEAD
static const UINT8* skip_gz_header( const UINT8 *p ) {
	UINT8 method, flags;
=======
static const uint8_t* skip_gz_header( const uint8_t *p ) {
	uint8_t method, flags;
>>>>>>> upstream/master
	/* skip initial 1f 8b header */
	p += 2;
	/* get method and flags */
	method = *p; p++;
	flags = *p; p++;
	if ( method != Z_DEFLATED || ( flags & RESERVED ) != 0 ) {
<<<<<<< HEAD
		return NULL;
=======
		return nullptr;
>>>>>>> upstream/master
	}
	/* Skip time, xflags and OS code */
	p += 6;

	/* Skip the extra field */
	if ( ( flags & EXTRA_FIELD ) != 0 ) {
		int len = ( p[1] << 8 ) | p[0];
		p += 2 + len;
	}
	/* Skip the original file name */
	if ( ( flags & ORIG_NAME ) != 0 ) {
		for ( ; *p; p++ );
	}
	/* Skip the .gz file comment */
	if ( ( flags & COMMENT ) != 0 ) {
		for( ; *p; p++ );
	}
	/* Skip the header crc */
	if ( ( flags & HEAD_CRC ) != 0 ) {
		p += 2;
	}
	return p;
}

<<<<<<< HEAD
static UINT8 *gz_ptr = NULL;

static float get_uef_float( const UINT8 *Float)
=======
static uint8_t *gz_ptr = nullptr;

static float get_uef_float( const uint8_t *Float)
>>>>>>> upstream/master
{
		int Mantissa;
		float Result;
		int Exponent;

		/* assume a four byte array named Float exists, where Float[0]
		was the first byte read from the UEF, Float[1] the second, etc */

		/* decode mantissa */
		Mantissa = Float[0] | (Float[1] << 8) | ((Float[2]&0x7f)|0x80) << 16;

		Result = (float)Mantissa;
		Result = (float)ldexp(Result, -23);

		/* decode exponent */
		Exponent = ((Float[2]&0x80) >> 7) | (Float[3]&0x7f) << 1;
		Exponent -= 127;
		Result = (float)ldexp(Result, Exponent);

		/* flip sign if necessary */
		if(Float[3]&0x80)
			Result = -Result;

	/* floating point number is now in 'Result' */
	return Result;
}

<<<<<<< HEAD
static int uef_cas_to_wav_size( const UINT8 *casdata, int caslen ) {
=======
static int uef_cas_to_wav_size( const uint8_t *casdata, int caslen ) {
>>>>>>> upstream/master
	int pos, size;

	if ( casdata[0] == 0x1f && casdata[1] == 0x8b ) {
		int err;
		z_stream d_stream;
		int inflate_size = ( casdata[ caslen - 1 ] << 24 ) | ( casdata[ caslen - 2 ] << 16 ) | ( casdata[ caslen - 3 ] << 8 ) | casdata[ caslen - 4 ];
<<<<<<< HEAD
		const UINT8 *in_ptr = skip_gz_header( casdata );

		if ( in_ptr == NULL ) {
			goto cleanup;
		}
		gz_ptr = (UINT8 *)malloc( inflate_size );

		d_stream.zalloc = 0;
		d_stream.zfree = 0;
		d_stream.opaque = 0;
=======
		const uint8_t *in_ptr = skip_gz_header( casdata );

		if ( in_ptr == nullptr ) {
			goto cleanup;
		}
		gz_ptr = (uint8_t *)malloc( inflate_size );

		d_stream.zalloc = nullptr;
		d_stream.zfree = nullptr;
		d_stream.opaque = nullptr;
>>>>>>> upstream/master
		d_stream.next_in = (unsigned char *)in_ptr;
		d_stream.avail_in = caslen - ( in_ptr - casdata );
		d_stream.next_out = gz_ptr;
		d_stream.avail_out = inflate_size;

		err = inflateInit2( &d_stream, -MAX_WBITS );
		if ( err != Z_OK ) {
			LOG_FORMATS( "inflateInit2 error: %d\n", err );
			goto cleanup;
		}
		err = inflate( &d_stream, Z_NO_FLUSH );
		if ( err != Z_STREAM_END && err != Z_OK ) {
			LOG_FORMATS( "inflate error: %d\n", err );
			goto cleanup;
		}
		err = inflateEnd( &d_stream );
		if ( err != Z_OK ) {
			LOG_FORMATS( "inflateEnd error: %d\n", err );
			goto cleanup;
		}
		caslen = inflate_size;
		casdata = gz_ptr;
	}

	if ( caslen < 18 ) {
		LOG_FORMATS( "uef_cas_to_wav_size: cassette image too small\n" );
		goto cleanup;
	}
	if ( memcmp( casdata, UEF_HEADER, sizeof(UEF_HEADER) ) ) {
		LOG_FORMATS( "uef_cas_to_wav_size: cassette image has incompatible header\n" );
		goto cleanup;
	}

<<<<<<< HEAD
	LOG_FORMATS( "UEF: Determinig tape size\n" );
=======
	LOG_FORMATS( "UEF: Determining tape size\n" );
>>>>>>> upstream/master
	size = 0;
	pos = sizeof(UEF_HEADER) + 2;
	while( pos < caslen ) {
		int chunk_type = ( casdata[pos+1] << 8 ) | casdata[pos];
		int chunk_length = ( casdata[pos+5] << 24 ) | ( casdata[pos+4] << 16 ) | ( casdata[pos+3] << 8 ) | casdata[pos+2];
		int baud_length;

		pos += 6;
		switch( chunk_type ) {
		case 0x0100:    /* implicit start/stop bit data block */
			size += ( chunk_length * 10 ) * 4;
			break;
		case 0x0101:    /* multiplexed data block */
		case 0x0103:
			LOG_FORMATS( "Unsupported chunk type: %04x\n", chunk_type );
			break;
		case 0x0102:    /* explicit tape data block */
			size += ( ( chunk_length * 10 ) - casdata[pos] ) * 4;
			break;
<<<<<<< HEAD
		case 0x0104:
			LOG_FORMATS( "Unsupported chunk type: %04x\n", chunk_type );
			break;
		case 0x0110:
=======
		case 0x0104:    /* defined tape format data block */
			LOG_FORMATS( "Unsupported chunk type: %04x\n", chunk_type );
			break;
		case 0x0110:    /* carrier tone (previously referred to as 'high tone') */
>>>>>>> upstream/master
			baud_length = ( casdata[pos+1] << 8 ) | casdata[pos];
			size += baud_length * 2;
			break;
		case 0x0111:
			LOG_FORMATS( "Unsupported chunk type: %04x\n", chunk_type );
			break;
<<<<<<< HEAD
		case 0x0112:
			baud_length = ( casdata[pos+1] << 8 ) | casdata[pos];
			size += baud_length * 2 ;
			break;
		case 0x0116:
			size += get_uef_float(casdata+pos)*UEF_WAV_FREQUENCY;
			break;
		case 0x0113:
		case 0x0114:
		case 0x0115:
		case 0x0120:
=======
		case 0x0112:    /* integer gap */
			baud_length = ( casdata[pos+1] << 8 ) | casdata[pos];
			size += baud_length * 2 ;
			break;
		case 0x0116:    /* floating point gap */
			size += get_uef_float(casdata+pos)*UEF_WAV_FREQUENCY;
			break;
		case 0x0113:    /* change of base frequency */
		case 0x0114:    /* security cycles */
		case 0x0115:    /* phase change */
		case 0x0117:    /* data encoding format change */
		case 0x0120:    /* position marker */
		case 0x0130:    /* tape set info */
		case 0x0131:    /* start of tape side */
>>>>>>> upstream/master
			LOG_FORMATS( "Unsupported chunk type: %04x\n", chunk_type );
			break;
		}
		pos += chunk_length;
	}
	size = 2 * size;
	return size;

cleanup:
	if ( gz_ptr ) {
		free( gz_ptr );
<<<<<<< HEAD
		gz_ptr = NULL;
=======
		gz_ptr = nullptr;
>>>>>>> upstream/master
	}
	return -1;
}

<<<<<<< HEAD
static INT16* uef_cas_fill_bit( INT16 *buffer, int bit ) {
=======
static int16_t* uef_cas_fill_bit( int16_t *buffer, int bit ) {
>>>>>>> upstream/master
	if ( bit ) {
		*buffer = WAVE_LOW; buffer++;
		*buffer = WAVE_HIGH; buffer++;
		*buffer = WAVE_LOW; buffer++;
		*buffer = WAVE_HIGH; buffer++;
	} else {
		*buffer = WAVE_LOW; buffer++;
		*buffer = WAVE_LOW; buffer++;
		*buffer = WAVE_HIGH; buffer++;
		*buffer = WAVE_HIGH; buffer++;
	}
	return buffer;
}

<<<<<<< HEAD
static int uef_cas_fill_wave( INT16 *buffer, int length, UINT8 *bytes ) {
	int pos;
	INT16 *p = buffer;

	if ( bytes[0] == 0x1f && bytes[1] == 0x8b ) {
		if ( gz_ptr == NULL ) {
=======
static int uef_cas_fill_wave( int16_t *buffer, int length, uint8_t *bytes ) {
	int pos;
	int16_t *p = buffer;

	if ( bytes[0] == 0x1f && bytes[1] == 0x8b ) {
		if ( gz_ptr == nullptr ) {
>>>>>>> upstream/master
			return 1;
		}
		bytes = gz_ptr;
	}

	pos = sizeof(UEF_HEADER) + 2;
	length = length / 2;
	while( length > 0 ) {
		int chunk_type = ( bytes[pos+1] << 8 ) | bytes[pos];
		int chunk_length = ( bytes[pos+5] << 24 ) | ( bytes[pos+4] << 16 ) | ( bytes[pos+3] << 8 ) | bytes[pos+2];

		int baud_length, i, j;
<<<<<<< HEAD
		UINT8 *c;
=======
		uint8_t *c;
>>>>>>> upstream/master
		pos += 6;
		switch( chunk_type ) {
		case 0x0100:    /* implicit start/stop bit data block */
			for( j = 0; j < chunk_length; j++ ) {
<<<<<<< HEAD
				UINT8 byte = bytes[pos+j];
=======
				uint8_t byte = bytes[pos+j];
>>>>>>> upstream/master
				p = uef_cas_fill_bit( p, 0 );
				for( i = 0; i < 8; i++ ) {
					p = uef_cas_fill_bit( p, byte & 1 );
					byte = byte >> 1;
				}
				p = uef_cas_fill_bit( p, 1 );
				length -= ( 10 * 4 );
			}
			break;
		case 0x0101:    /* multiplexed data block */
		case 0x0103:
			LOG_FORMATS( "Unsupported chunk type: %04x\n", chunk_type );
			break;
		case 0x0102:    /* explicit tape data block */
			j = ( chunk_length * 10 ) - bytes[pos];
			c = bytes + pos;
			while( j ) {
<<<<<<< HEAD
				UINT8 byte = *c;
=======
				uint8_t byte = *c;
>>>>>>> upstream/master
				for( i = 0; i < 8 && i < j; i++ ) {
					p = uef_cas_fill_bit( p, byte & 1 );
					byte = byte >> 1;
					j--;
				}
				c++;
			}
			break;
<<<<<<< HEAD
		case 0x0110:
=======
		case 0x0110:    /* carrier tone (previously referred to as 'high tone') */
>>>>>>> upstream/master
			for( baud_length = ( ( bytes[pos+1] << 8 ) | bytes[pos] ) ; baud_length; baud_length-- ) {
				*p = WAVE_LOW; p++;
				*p = WAVE_HIGH; p++;
				length -= 2;
			}
			break;
<<<<<<< HEAD
		case 0x0112:
=======
		case 0x0112:    /* integer gap */
>>>>>>> upstream/master
			for( baud_length = ( ( bytes[pos+1] << 8 ) | bytes[pos] ) ; baud_length; baud_length-- ) {
				*p = WAVE_NULL; p++;
				*p = WAVE_NULL; p++;
				length -= 2;
			}
			break;
<<<<<<< HEAD
		case 0x0116:
=======
		case 0x0116:    /* floating point gap */
>>>>>>> upstream/master
			for( baud_length = (get_uef_float(bytes+pos)*UEF_WAV_FREQUENCY); baud_length; baud_length-- ) {
				*p = WAVE_NULL; p++;
				length -= 1;
			}
			break;
<<<<<<< HEAD


=======
>>>>>>> upstream/master
		}
		pos += chunk_length;
	}
	return p - buffer;
}

static const struct CassetteLegacyWaveFiller uef_legacy_fill_wave = {
<<<<<<< HEAD
	uef_cas_fill_wave,              /* fill_wave */
	-1,                     /* chunk_size */
	0,                      /* chunk_samples */
	uef_cas_to_wav_size,                /* chunk_sample_calc */
	UEF_WAV_FREQUENCY,              /* sample_frequency */
=======
	uef_cas_fill_wave,      /* fill_wave */
	-1,                     /* chunk_size */
	0,                      /* chunk_samples */
	uef_cas_to_wav_size,    /* chunk_sample_calc */
	UEF_WAV_FREQUENCY,      /* sample_frequency */
>>>>>>> upstream/master
	0,                      /* header_samples */
	0                       /* trailer_samples */
};

<<<<<<< HEAD
static casserr_t uef_cassette_identify( cassette_image *cassette, struct CassetteOptions *opts ) {
	return cassette_legacy_identify( cassette, opts, &uef_legacy_fill_wave );
}

static casserr_t uef_cassette_load( cassette_image *cassette ) {
=======
static cassette_image::error uef_cassette_identify( cassette_image *cassette, struct CassetteOptions *opts ) {
	uint8_t header[10];

	cassette_image_read(cassette, header, 0, sizeof(header));
	if (memcmp(&header[0], GZ_HEADER, sizeof(GZ_HEADER)) && memcmp(&header[0], UEF_HEADER, sizeof(UEF_HEADER))) {
		return cassette_image::error::INVALID_IMAGE;
	}
	return cassette_legacy_identify( cassette, opts, &uef_legacy_fill_wave );
}

static cassette_image::error uef_cassette_load( cassette_image *cassette ) {
>>>>>>> upstream/master
	return cassette_legacy_construct( cassette, &uef_legacy_fill_wave );
}

const struct CassetteFormat uef_cassette_format = {
	"uef",
	uef_cassette_identify,
	uef_cassette_load,
<<<<<<< HEAD
	NULL
=======
	nullptr
>>>>>>> upstream/master
};

CASSETTE_FORMATLIST_START(uef_cassette_formats)
	CASSETTE_FORMAT(uef_cassette_format)
CASSETTE_FORMATLIST_END
