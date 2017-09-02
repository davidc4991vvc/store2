// license:BSD-3-Clause
<<<<<<< HEAD
// copyright-holders:Aaron Giles
=======
// copyright-holders:Aaron Giles, Vas Crabb
>>>>>>> upstream/master
/*********************************************************************

    png.c

    PNG reading functions.

***************************************************************************/

<<<<<<< HEAD
#include <math.h>
#include <stdlib.h>
#include <assert.h>

#include <zlib.h>
#include "png.h"

#include <new>


/***************************************************************************
    TYPE DEFINITIONS
***************************************************************************/

struct image_data_chunk
{
	image_data_chunk *  next;
	int                 length;
	UINT8 *             data;
};


struct png_private
{
	png_info *          pnginfo;
	image_data_chunk *  idata;
	image_data_chunk ** idata_next;
	UINT8               bpp;
	UINT32              rowbytes;
};
=======
#include "png.h"

#include "unicode.h"

#include <zlib.h>

#include <algorithm>
#include <cassert>
#include <cstdint>
#include <cstring>
#include <cmath>
#include <new>

#include <math.h>
#include <stdlib.h>
>>>>>>> upstream/master



/***************************************************************************
    GLOBAL VARIABLES
***************************************************************************/

static const int samples[] = { 1, 0, 3, 1, 2, 0, 4 };



/***************************************************************************
    INLINE FUNCTIONS
***************************************************************************/

<<<<<<< HEAD
INLINE UINT8 fetch_8bit(UINT8 *v)
{
	return *v;
}


#ifdef UNUSED_FUNCTION
INLINE UINT16 fetch_16bit(UINT8 *v)
{
	return BIG_ENDIANIZE_INT16(*(UINT16 *)v);
}
#endif

INLINE UINT32 fetch_32bit(UINT8 *v)
{
	return BIG_ENDIANIZE_INT32(*(UINT32 *)v);
}


INLINE void put_8bit(UINT8 *v, UINT8 data)
{
	*v = data;
}


#ifdef UNUSED_FUNCTION
INLINE void put_16bit(UINT8 *v, UINT16 data)
{
	*(UINT16 *)v = BIG_ENDIANIZE_INT16(data);
}
#endif

INLINE void put_32bit(UINT8 *v, UINT32 data)
{
	*(UINT32 *)v = BIG_ENDIANIZE_INT32(data);
}


INLINE int compute_bpp(const png_info *pnginfo)
{
	return samples[pnginfo->color_type] * pnginfo->bit_depth / 8;
}


INLINE int compute_rowbytes(const png_info *pnginfo)
{
	return (pnginfo->width * samples[pnginfo->color_type] * pnginfo->bit_depth + 7) / 8;
=======
static inline int compute_rowbytes(const png_info &pnginfo)
{
	return (pnginfo.width * samples[pnginfo.color_type] * pnginfo.bit_depth + 7) / 8;
>>>>>>> upstream/master
}



/***************************************************************************
    GENERAL FUNCTIONS
***************************************************************************/

/*-------------------------------------------------
<<<<<<< HEAD
    png_free - free all memory allocated in a
    pnginfo structure
-------------------------------------------------*/

void png_free(png_info *pnginfo)
{
	while (pnginfo->textlist != NULL)
	{
		png_text *temp = pnginfo->textlist;
		pnginfo->textlist = temp->next;
		if (temp->keyword != NULL)
			free((void *)temp->keyword);
		free(temp);
	}

	if (pnginfo->palette != NULL)
		free(pnginfo->palette);
	pnginfo->palette = NULL;

	if (pnginfo->trans != NULL)
		free(pnginfo->trans);
	pnginfo->trans = NULL;

	if (pnginfo->image != NULL)
		free(pnginfo->image);
	pnginfo->image = NULL;
=======
    free_data - free all memory allocated in a
    pnginfo structure
-------------------------------------------------*/

void png_info::free_data()
{
	textlist.clear();
	palette.reset();
	trans.reset();
	image.reset();
>>>>>>> upstream/master
}



<<<<<<< HEAD
/***************************************************************************
    PNG READING FUNCTIONS
***************************************************************************/

/*-------------------------------------------------
    verify_header - verify the PNG
    header at the current file location
-------------------------------------------------*/

static png_error verify_header(core_file *fp)
{
	UINT8 signature[8];

	/* read 8 bytes */
	if (core_fread(fp, signature, 8) != 8)
		return PNGERR_FILE_TRUNCATED;

	/* return an error if we don't match */
	if (memcmp(signature, PNG_Signature, 8) != 0)
		return PNGERR_BAD_SIGNATURE;

	return PNGERR_NONE;
}


/*-------------------------------------------------
    read_chunk - read the next PNG chunk
-------------------------------------------------*/

static png_error read_chunk(core_file *fp, UINT8 **data, UINT32 *type, UINT32 *length)
{
	UINT32 crc, chunk_crc;
	UINT8 tempbuff[4];

	/* fetch the length of this chunk */
	if (core_fread(fp, tempbuff, 4) != 4)
		return PNGERR_FILE_TRUNCATED;
	*length = fetch_32bit(tempbuff);

	/* fetch the type of this chunk */
	if (core_fread(fp, tempbuff, 4) != 4)
		return PNGERR_FILE_TRUNCATED;
	*type = fetch_32bit(tempbuff);

	/* stop when we hit an IEND chunk */
	if (*type == PNG_CN_IEND)
		return PNGERR_NONE;

	/* start the CRC with the chunk type (but not the length) */
	crc = crc32(0, tempbuff, 4);

	/* read the chunk itself into an allocated memory buffer */
	*data = NULL;
	if (*length != 0)
	{
		/* allocate memory for this chunk */
		*data = (UINT8 *)malloc(*length);
		if (*data == NULL)
			return PNGERR_OUT_OF_MEMORY;

		/* read the data from the file */
		if (core_fread(fp, *data, *length) != *length)
		{
			free(*data);
			*data = NULL;
			return PNGERR_FILE_TRUNCATED;
		}

		/* update the CRC */
		crc = crc32(crc, *data, *length);
	}

	/* read the CRC */
	if (core_fread(fp, tempbuff, 4) != 4)
	{
		free(*data);
		*data = NULL;
		return PNGERR_FILE_TRUNCATED;
	}
	chunk_crc = fetch_32bit(tempbuff);

	/* validate the CRC */
	if (crc != chunk_crc)
	{
		free(*data);
		*data = NULL;
		return PNGERR_FILE_CORRUPT;
	}
	return PNGERR_NONE;
}


/*-------------------------------------------------
    process_chunk - process a PNG chunk
-------------------------------------------------*/

static png_error process_chunk(png_private *png, UINT8 *data, UINT32 type, UINT32 length, int *keepmem)
{
	/* default to not keeping memory */
	*keepmem = FALSE;

	/* switch off of the type */
	switch (type)
	{
		/* image header */
		case PNG_CN_IHDR:
			png->pnginfo->width = fetch_32bit(data);
			png->pnginfo->height = fetch_32bit(data + 4);
			png->pnginfo->bit_depth = fetch_8bit(data + 8);
			png->pnginfo->color_type = fetch_8bit(data + 9);
			png->pnginfo->compression_method = fetch_8bit(data + 10);
			png->pnginfo->filter_method = fetch_8bit(data + 11);
			png->pnginfo->interlace_method = fetch_8bit(data + 12);
			break;

		/* palette */
		case PNG_CN_PLTE:
			png->pnginfo->num_palette = length / 3;
			png->pnginfo->palette = data;
			*keepmem = TRUE;
			break;

		/* transparency information */
		case PNG_CN_tRNS:
			png->pnginfo->num_trans = length;
			png->pnginfo->trans = data;
			*keepmem = TRUE;
			break;

		/* image data */
		case PNG_CN_IDAT:

			/* allocate a new image data descriptor */
			*png->idata_next = (image_data_chunk *)malloc(sizeof(**png->idata_next));
			if (*png->idata_next == NULL)
				return PNGERR_OUT_OF_MEMORY;

			/* add it to the tail of the list */
			(*png->idata_next)->next = NULL;
			(*png->idata_next)->length = length;
			(*png->idata_next)->data = data;
			png->idata_next = &(*png->idata_next)->next;
			*keepmem = TRUE;
			break;

		/* gamma */
		case PNG_CN_gAMA:
			png->pnginfo->source_gamma = fetch_32bit(data) / 100000.0;
			break;

		/* physical information */
		case PNG_CN_pHYs:
			png->pnginfo->xres = fetch_32bit(data);
			png->pnginfo->yres = fetch_32bit(data + 4);
			png->pnginfo->resolution_unit = fetch_8bit(data + 8);
			break;

		/* text */
		case PNG_CN_tEXt:
		{
			png_text *text, *pt, *ct;

			/* allocate a new text item */
			text = (png_text *)malloc(sizeof(*text));
			if (text == NULL)
				return PNGERR_OUT_OF_MEMORY;

			/* set the elements */
			text->keyword = (char *)data;
			text->text = text->keyword + strlen(text->keyword) + 1;
			text->next = NULL;

			/* add to the end of the list */
			for (pt = NULL, ct = png->pnginfo->textlist; ct != NULL; pt = ct, ct = ct->next) ;
			if (pt == NULL)
				png->pnginfo->textlist = text;
			else
				pt->next = text;

			*keepmem = TRUE;
			break;
		}
=======
namespace {

#define PNG_Signature       "\x89\x50\x4E\x47\x0D\x0A\x1A\x0A"
#define MNG_Signature       "\x8A\x4D\x4E\x47\x0D\x0A\x1A\x0A"

// Chunk names
constexpr std::uint32_t PNG_CN_IHDR     = 0x49484452L;
constexpr std::uint32_t PNG_CN_PLTE     = 0x504C5445L;
constexpr std::uint32_t PNG_CN_IDAT     = 0x49444154L;
constexpr std::uint32_t PNG_CN_IEND     = 0x49454E44L;
constexpr std::uint32_t PNG_CN_gAMA     = 0x67414D41L;
//constexpr std::uint32_t PNG_CN_sBIT     = 0x73424954L;
//constexpr std::uint32_t PNG_CN_cHRM     = 0x6348524DL;
constexpr std::uint32_t PNG_CN_tRNS     = 0x74524E53L;
//constexpr std::uint32_t PNG_CN_bKGD     = 0x624B4744L;
//constexpr std::uint32_t PNG_CN_hIST     = 0x68495354L;
constexpr std::uint32_t PNG_CN_tEXt     = 0x74455874L;
//constexpr std::uint32_t PNG_CN_zTXt     = 0x7A545874L;
constexpr std::uint32_t PNG_CN_pHYs     = 0x70485973L;
//constexpr std::uint32_t PNG_CN_oFFs     = 0x6F464673L;
//constexpr std::uint32_t PNG_CN_tIME     = 0x74494D45L;
//constexpr std::uint32_t PNG_CN_sCAL     = 0x7343414CL;

// MNG Chunk names
constexpr std::uint32_t MNG_CN_MHDR     = 0x4D484452L;
constexpr std::uint32_t MNG_CN_MEND     = 0x4D454E44L;
//constexpr std::uint32_t MNG_CN_TERM     = 0x5445524DL;
//constexpr std::uint32_t MNG_CN_BACK     = 0x4241434BL;

// Prediction filters
constexpr std::uint8_t  PNG_PF_None     = 0;
constexpr std::uint8_t  PNG_PF_Sub      = 1;
constexpr std::uint8_t  PNG_PF_Up       = 2;
constexpr std::uint8_t  PNG_PF_Average  = 3;
constexpr std::uint8_t  PNG_PF_Paeth    = 4;


inline uint8_t fetch_8bit(uint8_t const *v) { return *v; }
inline uint16_t fetch_16bit(uint8_t const *v) { return big_endianize_int16(*reinterpret_cast<uint16_t const *>(v)); }
inline uint32_t fetch_32bit(uint8_t const *v) { return big_endianize_int32(*reinterpret_cast<uint32_t const *>(v)); }

inline void put_8bit(uint8_t *v, uint8_t data) { *v = data; }
inline void put_16bit(uint8_t *v, uint16_t data) { *reinterpret_cast<uint16_t *>(v) = big_endianize_int16(data); }
inline void put_32bit(uint8_t *v, uint32_t data) { *reinterpret_cast<uint32_t *>(v) = big_endianize_int32(data); }


class png_private
{
private:
	static constexpr unsigned ADAM7_X_BIAS[7]   = { 7, 3, 3, 1, 1, 0, 0 };
	static constexpr unsigned ADAM7_Y_BIAS[7]   = { 7, 7, 3, 3, 1, 1, 0 };
	static constexpr unsigned ADAM7_X_SHIFT[7]  = { 3, 3, 2, 2, 1, 1, 0 };
	static constexpr unsigned ADAM7_Y_SHIFT[7]  = { 3, 3, 3, 2, 2, 1, 1 };
	static constexpr unsigned ADAM7_X_OFFS[7]   = { 0, 4, 0, 2, 0, 1, 0 };
	static constexpr unsigned ADAM7_Y_OFFS[7]   = { 0, 0, 4, 0, 2, 0, 1 };

	struct image_data_chunk
	{
		image_data_chunk(std::uint32_t l, std::unique_ptr<std::uint8_t []> &&d) : length(l), data(std::move(d)) { }

		std::uint32_t                       length;
		std::unique_ptr<std::uint8_t []>    data;
	};

	png_error process(std::list<image_data_chunk> const &idata)
	{
		// do some basic checks for unsupported images
		if (!pnginfo.bit_depth || (ARRAY_LENGTH(samples) <= pnginfo.color_type) || !samples[pnginfo.color_type])
			return PNGERR_UNSUPPORTED_FORMAT; // unknown colour format
		if ((0 != pnginfo.interlace_method) && (1 != pnginfo.interlace_method))
			return PNGERR_UNSUPPORTED_FORMAT; // unknown interlace method
		if ((3 == pnginfo.color_type) && (!pnginfo.num_palette || !pnginfo.palette))
			return PNGERR_FILE_CORRUPT; // indexed colour with no palette

		// calculate the offset for each pass of the interlace
		unsigned const pass_count(get_pass_count());
		std::uint32_t pass_offset[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
		for (unsigned pass = 0; pass_count > pass; ++pass)
			pass_offset[pass + 1] = pass_offset[pass] + get_pass_bytes(pass);

		// allocate memory for the filtered image
		try { pnginfo.image.reset(new std::uint8_t [pass_offset[pass_count]]); }
		catch (std::bad_alloc const &) { return PNGERR_OUT_OF_MEMORY; }

		// decompress image data
		png_error error = PNGERR_NONE;
		error = decompress(idata, pass_offset[pass_count]);
		std::uint32_t const bpp(get_bytes_per_pixel());
		for (unsigned pass = 0; (pass_count > pass) && (PNGERR_NONE == error); ++pass)
		{
			// compute some basic parameters
			std::pair<std::uint32_t, std::uint32_t> const dimensions(get_pass_dimensions(pass));
			std::uint32_t const rowbytes(get_row_bytes(dimensions.first));

			// we de-filter in place, stripping the filter bytes off the rows
			uint8_t *dst(&pnginfo.image[pass_offset[pass]]);
			uint8_t const *src(dst);
			for (std::uint32_t y = 0; (dimensions.second > y) && (PNGERR_NONE == error); ++y)
			{
				// first byte of each row is the filter type
				uint8_t const filter(*src++);
				error = unfilter_row(filter, src, dst, y ? (dst - rowbytes) : nullptr, bpp, rowbytes);
				src += rowbytes;
				dst += rowbytes;
			}
		}

		// if we errored, free the image data
		if (error != PNGERR_NONE)
			pnginfo.image.reset();

		return error;
	}

	png_error decompress(std::list<image_data_chunk> const &idata, std::uint32_t expected)
	{
		// only deflate is permitted
		if (0 != pnginfo.compression_method)
			return PNGERR_DECOMPRESS_ERROR;

		// allocate zlib stream
		z_stream stream;
		int zerr;
		std::memset(&stream, 0, sizeof(stream));
		stream.zalloc = Z_NULL;
		stream.zfree = Z_NULL;
		stream.opaque = Z_NULL;
		stream.avail_in = 0;
		stream.next_in = Z_NULL;
		zerr = inflateInit(&stream);
		if (Z_OK != zerr)
			return PNGERR_DECOMPRESS_ERROR;

		// decompress IDAT blocks
		stream.next_out = pnginfo.image.get();
		stream.avail_out = expected;
		stream.avail_in = 0;
		std::list<image_data_chunk>::const_iterator it = idata.begin();
		while ((idata.end() != it) && ((Z_OK == zerr) || (Z_BUF_ERROR == zerr)) && !stream.avail_in)
		{
			stream.avail_in = it->length;
			stream.next_in = it->data.get();
			do
			{
				zerr = inflate(&stream, Z_NO_FLUSH);
			}
			while (stream.avail_in && (Z_OK == zerr));
			if (!stream.avail_in)
				++it;
		}

		// it's all good if we got end-of-stream or we have with no data remaining
		if ((Z_OK == inflateEnd(&stream)) && ((Z_STREAM_END == zerr) || ((Z_OK == zerr) && (idata.end() == it) && !stream.avail_in)))
			return PNGERR_NONE;
		else
			return PNGERR_DECOMPRESS_ERROR;
	}

	png_error unfilter_row(std::uint8_t type, uint8_t const *src, uint8_t *dst, uint8_t const *dstprev, int bpp, std::uint32_t rowbytes)
	{
		if (0 != pnginfo.filter_method)
			return PNGERR_UNKNOWN_FILTER;

		switch (type)
		{
		case PNG_PF_None: // no filter, just copy
			std::copy_n(src, rowbytes, dst);
			return PNGERR_NONE;

		case PNG_PF_Sub: // SUB = previous pixel
			dst = std::copy_n(src, bpp, dst);
			src += bpp;
			for (std::uint32_t x = bpp; rowbytes > x; ++x, ++src, ++dst)
				*dst = *src + dst[-bpp];
			return PNGERR_NONE;

		case PNG_PF_Up: // UP = pixel above
			if (dstprev)
			{
				for (std::uint32_t x = 0; rowbytes > x; ++x, ++src, ++dst, ++dstprev)
					*dst = *src + *dstprev;
			}
			else
			{
				std::copy_n(src, rowbytes, dst);
			}
			return PNGERR_NONE;

		case PNG_PF_Average: // AVERAGE = average of pixel above and previous pixel
			if (dstprev)
			{
				for (std::uint32_t x = 0; bpp > x; ++x, ++src, ++dst, ++dstprev)
					*dst = *src + (*dstprev >> 1);
				for (std::uint32_t x = bpp; rowbytes > x; ++x, ++src, ++dst, ++dstprev)
					*dst = *src + ((*dstprev + dst[-bpp]) >> 1);
			}
			else
			{
				dst = std::copy_n(src, bpp, dst);
				src += bpp;
				for (std::uint32_t x = bpp; rowbytes > x; ++x, ++src, ++dst)
					*dst = *src + (dst[-bpp] >> 1);
			}
			return PNGERR_NONE;

		case PNG_PF_Paeth: // PAETH = special filter
			for (std::uint32_t x = 0; rowbytes > x; ++x, ++src, ++dst)
			{
				int32_t const pa((x < bpp) ? 0 : dst[-bpp]);
				int32_t const pc(((x < bpp) || !dstprev) ? 0 : dstprev[-bpp]);
				int32_t const pb(!dstprev ? 0 : *dstprev++);
				int32_t const prediction(pa + pb - pc);
				int32_t const da(std::abs(prediction - pa));
				int32_t const db(std::abs(prediction - pb));
				int32_t const dc(std::abs(prediction - pc));
				*dst = ((da <= db) && (da <= dc)) ? (*src + pa) : (db <= dc) ? (*src + pb) : (*src + pc);
			}
			return PNGERR_NONE;

		default: // unknown filter type
			return PNGERR_UNKNOWN_FILTER;
		}
	}

	png_error process_chunk(std::list<image_data_chunk> &idata, std::unique_ptr<std::uint8_t []> &&data, uint32_t type, uint32_t length)
	{
		switch (type)
		{
		case PNG_CN_IHDR: // image header
			if (13 > length)
				return PNGERR_FILE_CORRUPT;
			pnginfo.width = fetch_32bit(&data[0]);
			pnginfo.height = fetch_32bit(&data[4]);
			pnginfo.bit_depth = fetch_8bit(&data[8]);
			pnginfo.color_type = fetch_8bit(&data[9]);
			pnginfo.compression_method = fetch_8bit(&data[10]);
			pnginfo.filter_method = fetch_8bit(&data[11]);
			pnginfo.interlace_method = fetch_8bit(&data[12]);
			break;

		case PNG_CN_PLTE: // palette
			pnginfo.num_palette = length / 3;
			if ((length % 3) || ((3 == pnginfo.color_type) && ((1 << pnginfo.bit_depth) < pnginfo.num_palette)))
				return PNGERR_FILE_CORRUPT;
			pnginfo.palette = std::move(data);
			break;

		case PNG_CN_tRNS: // transparency information
			if (((0 == pnginfo.color_type) && (2 > length)) || ((2 == pnginfo.color_type) && (6 > length)))
				return PNGERR_FILE_CORRUPT;
			pnginfo.num_trans = length;
			pnginfo.trans = std::move(data);
			break;

		case PNG_CN_IDAT: // image data
			try { idata.emplace_back(length, std::move(data)); }
			catch (std::bad_alloc const &) { return PNGERR_OUT_OF_MEMORY; }
			break;

		case PNG_CN_gAMA: // gamma
			if (4 > length)
				return PNGERR_FILE_CORRUPT;
			pnginfo.source_gamma = fetch_32bit(data.get()) / 100000.0;
			break;

		case PNG_CN_pHYs: // physical information
			if (9 > length)
				return PNGERR_FILE_CORRUPT;
			pnginfo.xres = fetch_32bit(&data[0]);
			pnginfo.yres = fetch_32bit(&data[4]);
			pnginfo.resolution_unit = fetch_8bit(&data[8]);
			break;

		case PNG_CN_tEXt: // text
			try
			{
				// split into keyword and string
				std::uint8_t const *kwbegin(&data[0]);
				std::uint8_t const *const textend(kwbegin + length);
				std::uint8_t const *const kwend(std::find(kwbegin, textend, '\0'));
				std::uint8_t const *textbegin(kwend + ((textend == kwend) ? 0 : 1));

				// text is ISO-8859-1 but MAME likes UTF-8
				std::size_t buflen(2 * std::max(kwend - kwbegin, textend - textbegin));
				std::unique_ptr<char []> utf8buf(new char [buflen]);
				char const *const bufend(utf8buf.get() + buflen);
				char *dst;
				for (dst = utf8buf.get(); kwend > kwbegin; dst += utf8_from_uchar(dst, bufend - dst, *kwbegin++)) { }
				std::string keyword(utf8buf.get(), dst);
				for (dst = utf8buf.get(); textend > textbegin; dst += utf8_from_uchar(dst, bufend - dst, *textbegin++)) { }
				std::string text(utf8buf.get(), dst);

				// allocate a new text item
				pnginfo.textlist.emplace_back(std::move(keyword), std::move(text));
			}
			catch (std::bad_alloc const &)
			{
				return PNGERR_OUT_OF_MEMORY;
			}
			break;
>>>>>>> upstream/master

		/* anything else */
		default:
			if ((type & 0x20000000) == 0)
				return PNGERR_UNKNOWN_CHUNK;
			break;
<<<<<<< HEAD
	}
	return PNGERR_NONE;
}


/*-------------------------------------------------
    unfilter_row - unfilter a single row of pixels
-------------------------------------------------*/

static png_error unfilter_row(int type, UINT8 *src, UINT8 *dst, UINT8 *dstprev, int bpp, int rowbytes)
{
	int x;

	/* switch off of it */
	switch (type)
	{
		/* no filter, just copy */
		case PNG_PF_None:
			for (x = 0; x < rowbytes; x++)
				*dst++ = *src++;
			break;

		/* SUB = previous pixel */
		case PNG_PF_Sub:
			for (x = 0; x < bpp; x++)
				*dst++ = *src++;
			for (x = bpp; x < rowbytes; x++, dst++)
				*dst = *src++ + dst[-bpp];
			break;

		/* UP = pixel above */
		case PNG_PF_Up:
			if (dstprev == NULL)
				return unfilter_row(PNG_PF_None, src, dst, dstprev, bpp, rowbytes);
			for (x = 0; x < rowbytes; x++, dst++)
				*dst = *src++ + *dstprev++;
			break;

		/* AVERAGE = average of pixel above and previous pixel */
		case PNG_PF_Average:
			if (dstprev == NULL)
			{
				for (x = 0; x < bpp; x++)
					*dst++ = *src++;
				for (x = bpp; x < rowbytes; x++, dst++)
					*dst = *src++ + dst[-bpp] / 2;
			}
			else
			{
				for (x = 0; x < bpp; x++, dst++)
					*dst = *src++ + *dstprev++ / 2;
				for (x = bpp; x < rowbytes; x++, dst++)
					*dst = *src++ + (*dstprev++ + dst[-bpp]) / 2;
			}
			break;

		/* PAETH = special filter */
		case PNG_PF_Paeth:
			for (x = 0; x < rowbytes; x++)
			{
				INT32 pa = (x < bpp) ? 0 : dst[-bpp];
				INT32 pc = (x < bpp || dstprev == NULL) ? 0 : dstprev[-bpp];
				INT32 pb = (dstprev == NULL) ? 0 : *dstprev++;
				INT32 prediction = pa + pb - pc;
				INT32 da = abs(prediction - pa);
				INT32 db = abs(prediction - pb);
				INT32 dc = abs(prediction - pc);
				if (da <= db && da <= dc)
					*dst++ = *src++ + pa;
				else if (db <= dc)
					*dst++ = *src++ + pb;
				else
					*dst++ = *src++ + pc;
			}
			break;

		/* unknown filter type */
		default:
			return PNGERR_UNKNOWN_FILTER;
	}

	return PNGERR_NONE;
}


/*-------------------------------------------------
    process_image - post-process a loaded iamge
-------------------------------------------------*/

static png_error process_image(png_private *png)
{
	int rowbytes, bpp, imagesize;
	png_error error = PNGERR_NONE;
	image_data_chunk *idat;
	UINT8 *src, *dst;
	z_stream stream;
	int zerr, y;

	/* compute some basic parameters */
	bpp = compute_bpp(png->pnginfo);
	rowbytes = compute_rowbytes(png->pnginfo);
	imagesize = png->pnginfo->height * (rowbytes + 1);

	/* allocate memory for the filtered image */
	png->pnginfo->image = (UINT8 *)malloc(imagesize);
	if (png->pnginfo->image == NULL)
		return PNGERR_OUT_OF_MEMORY;

	/* initialize the stream */
	memset(&stream, 0, sizeof(stream));
	stream.next_out = png->pnginfo->image;
	stream.avail_out = imagesize;
	zerr = inflateInit(&stream);
	if (zerr != Z_OK)
	{
		error = PNGERR_DECOMPRESS_ERROR;
		goto handle_error;
	}

	/* loop over IDAT and decompress each as part of a larger stream */
	for (idat = png->idata; idat != NULL; idat = idat->next)
	{
		/* decompress this chunk */
		stream.next_in = idat->data;
		stream.avail_in = idat->length;
		zerr = inflate(&stream, Z_NO_FLUSH);

		/* stop at the end of the stream */
		if (zerr == Z_STREAM_END)
			break;

		/* other errors are fatal */
		if (zerr != Z_OK)
		{
			error = PNGERR_DECOMPRESS_ERROR;
			goto handle_error;
		}
	}

	/* clean up */
	zerr = inflateEnd(&stream);
	if (zerr != Z_OK)
	{
		error = PNGERR_DECOMPRESS_ERROR;
		goto handle_error;
	}

	/* we de-filter in place */
	src = dst = png->pnginfo->image;

	/* iterate over rows */
	for (y = 0; y < png->pnginfo->height && error == PNGERR_NONE; y++)
	{
		/* first byte of each row is the filter type */
		int filter = *src++;
		error = unfilter_row(filter, src, dst, (y == 0) ? NULL : &dst[-rowbytes], bpp, rowbytes);
		src += rowbytes;
		dst += rowbytes;
	}

handle_error:
	/* if we errored, free the image data */
	if (error != PNGERR_NONE)
	{
		free(png->pnginfo->image);
		png->pnginfo->image = NULL;
	}
	return error;
}


/*-------------------------------------------------
    png_read_file - read a PNG from a core stream
-------------------------------------------------*/

png_error png_read_file(core_file *fp, png_info *pnginfo)
{
	UINT8 *chunk_data = NULL;
	png_private png;
	png_error error;

	/* initialize the data structures */
	memset(&png, 0, sizeof(png));
	memset(pnginfo, 0, sizeof(*pnginfo));
	png.pnginfo = pnginfo;
	png.idata_next = &png.idata;

	/* verify the signature at the start of the file */
	error = verify_header(fp);
	if (error != PNGERR_NONE)
		goto handle_error;

	/* loop until we hit an IEND chunk */
	for ( ; ; )
	{
		UINT32 chunk_type, chunk_length;
		int keepmem;

		/* read a chunk */
		error = read_chunk(fp, &chunk_data, &chunk_type, &chunk_length);
		if (error != PNGERR_NONE)
			goto handle_error;

		/* stop when we hit an IEND chunk */
		if (chunk_type == PNG_CN_IEND)
			break;

		/* process the chunk */
		error = process_chunk(&png, chunk_data, chunk_type, chunk_length, &keepmem);
		if (error != PNGERR_NONE)
			goto handle_error;

		/* free memory if we didn't want to keep it */
		if (!keepmem)
			free(chunk_data);
		chunk_data = NULL;
	}

	/* finish processing the image */
	error = process_image(&png);
	if (error != PNGERR_NONE)
		goto handle_error;

handle_error:

	/* free all intermediate data */
	while (png.idata != NULL)
	{
		image_data_chunk *next = png.idata->next;
		if (png.idata->data != NULL)
			free(png.idata->data);
		free(png.idata);
		png.idata = next;
	}
	if (chunk_data != NULL)
		free(chunk_data);

	/* if we have an error, free all the other data as well */
	if (error != PNGERR_NONE)
	{
		png_free(pnginfo);
		memset(pnginfo, 0, sizeof(*pnginfo));
	}
	return error;
=======
		}
		return PNGERR_NONE;
	}

	unsigned get_pass_count() const
	{
		return (1 == pnginfo.interlace_method) ? 7 : 1;
	}

	std::pair<uint32_t, uint32_t> get_pass_dimensions(unsigned pass) const
	{
		if (0 == pnginfo.interlace_method)
			return std::make_pair(pnginfo.width, pnginfo.height);
		else
			return std::make_pair((pnginfo.width + ADAM7_X_BIAS[pass]) >> ADAM7_X_SHIFT[pass], (pnginfo.height + ADAM7_Y_BIAS[pass]) >> ADAM7_Y_SHIFT[pass]);
	}

	std::uint32_t get_pass_bytes(unsigned pass) const
	{
		return get_pass_bytes(pass, pnginfo.bit_depth);
	}

	std::uint32_t get_pass_bytes(unsigned pass, uint8_t bit_depth) const
	{
		std::pair<std::uint32_t, std::uint32_t> const dimensions(get_pass_dimensions(pass));
		return (get_row_bytes(dimensions.first, bit_depth) + 1) * dimensions.second;
	}

	std::uint32_t get_row_bytes(std::uint32_t width) const
	{
		return get_row_bytes(width, pnginfo.bit_depth);
	}

	std::uint32_t get_row_bytes(std::uint32_t width, uint8_t bit_depth) const
	{
		return ((width * samples[pnginfo.color_type] * bit_depth) + 7) >> 3;
	}

	std::uint32_t get_bytes_per_pixel() const
	{
		return ((samples[pnginfo.color_type] * pnginfo.bit_depth) + 7) >> 3;
	}

	static png_error verify_header(util::core_file &fp)
	{
		uint8_t signature[8];

		/* read 8 bytes */
		if (fp.read(signature, 8) != 8)
			return PNGERR_FILE_TRUNCATED;

		/* return an error if we don't match */
		if (memcmp(signature, PNG_Signature, 8) != 0)
			return PNGERR_BAD_SIGNATURE;

		return PNGERR_NONE;
	}

	static png_error read_chunk(util::core_file &fp, std::unique_ptr<std::uint8_t []> &data, std::uint32_t &type, std::uint32_t &length)
	{
		std::uint8_t tempbuff[4];

		/* fetch the length of this chunk */
		if (fp.read(tempbuff, 4) != 4)
			return PNGERR_FILE_TRUNCATED;
		length = fetch_32bit(tempbuff);

		/* fetch the type of this chunk */
		if (fp.read(tempbuff, 4) != 4)
			return PNGERR_FILE_TRUNCATED;
		type = fetch_32bit(tempbuff);

		/* stop when we hit an IEND chunk */
		if (type == PNG_CN_IEND)
			return PNGERR_NONE;

		/* start the CRC with the chunk type (but not the length) */
		std::uint32_t crc = crc32(0, tempbuff, 4);

		/* read the chunk itself into an allocated memory buffer */
		if (length)
		{
			/* allocate memory for this chunk */
			try { data.reset(new std::uint8_t [length]); }
			catch (std::bad_alloc const &) { return PNGERR_OUT_OF_MEMORY; }

			/* read the data from the file */
			if (fp.read(data.get(), length) != length)
			{
				data.reset();
				return PNGERR_FILE_TRUNCATED;
			}

			/* update the CRC */
			crc = crc32(crc, data.get(), length);
		}

		/* read the CRC */
		if (fp.read(tempbuff, 4) != 4)
		{
			data.reset();
			return PNGERR_FILE_TRUNCATED;
		}
		std::uint32_t const chunk_crc = fetch_32bit(tempbuff);

		/* validate the CRC */
		if (crc != chunk_crc)
		{
			data.reset();
			return PNGERR_FILE_CORRUPT;
		}

		return PNGERR_NONE;
	}

	png_info &  pnginfo;

public:
	png_private(png_info &info) : pnginfo(info)
	{
	}

	png_error copy_to_bitmap(bitmap_argb32 &bitmap, bool &hasalpha) const
	{
		// do some basic checks for unsupported images
		if ((8 > pnginfo.bit_depth) || (pnginfo.bit_depth % 8))
			return PNGERR_UNSUPPORTED_FORMAT; // only do multiples of 8bps here - expand lower bit depth first
		if ((ARRAY_LENGTH(samples) <= pnginfo.color_type) || !samples[pnginfo.color_type])
			return PNGERR_UNSUPPORTED_FORMAT; // unknown colour sample format
		if ((0 != pnginfo.interlace_method) && (1 != pnginfo.interlace_method))
			return PNGERR_UNSUPPORTED_FORMAT; // unknown interlace method
		if ((3 == pnginfo.color_type) && (8 != pnginfo.bit_depth))
			return PNGERR_UNSUPPORTED_FORMAT; // indexed colour must be exactly 8bpp

		// everything looks sane, allocate the bitmap and deinterlace into it
		bitmap.allocate(pnginfo.width, pnginfo.height);
		std::uint8_t accumalpha(0xff);
		uint32_t const bps(pnginfo.bit_depth >> 3);
		uint32_t const bpp(bps * samples[pnginfo.color_type]);
		unsigned const pass_count(get_pass_count());
		std::uint32_t pass_offset[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
		for (unsigned pass = 0; pass_count > pass; ++pass)
		{
			// calculate parameters for interlace pass
			pass_offset[pass + 1] = pass_offset[pass] + get_pass_bytes(pass);
			unsigned const x_shift(pnginfo.interlace_method ? ADAM7_X_SHIFT[pass] : 0);
			unsigned const y_shift(pnginfo.interlace_method ? ADAM7_Y_SHIFT[pass] : 0);
			unsigned const x_offs(pnginfo.interlace_method ? ADAM7_X_OFFS[pass] : 0);
			unsigned const y_offs(pnginfo.interlace_method ? ADAM7_Y_OFFS[pass] : 0);
			std::pair<std::uint32_t, std::uint32_t> const dimensions(get_pass_dimensions(pass));
			std::uint8_t const *src(&pnginfo.image[pass_offset[pass]]);

			if (3 == pnginfo.color_type)
			{
				// handle 8bpp palettized case
				for (std::uint32_t y = 0; dimensions.second > y; ++y)
				{
					for (std::uint32_t x = 0; dimensions.first > x; ++x, src += bpp)
					{
						// determine alpha and expand to 32bpp
						std::uint8_t const alpha((*src < pnginfo.num_trans) ? pnginfo.trans[*src] : 0xff);
						accumalpha &= alpha;
						std::uint16_t const paloffs(std::uint16_t(*src) * 3);
						rgb_t const pix(alpha, pnginfo.palette[paloffs], pnginfo.palette[paloffs + 1], pnginfo.palette[paloffs + 2]);
						bitmap.pix32((y << y_shift) + y_offs, (x << x_shift) + x_offs) = pix;
					}
				}
			}
			else if (0 == pnginfo.color_type)
			{
				// handle grayscale non-alpha case
				uint32_t const bpp(pnginfo.bit_depth >> 3);
				std::uint16_t const transpen(pnginfo.trans ? fetch_16bit(pnginfo.trans.get()) : 0U);
				unsigned const samp_shift((8 < pnginfo.bit_depth) ? 8 : 0);
				for (std::uint32_t y = 0; dimensions.second > y; ++y)
				{
					for (std::uint32_t x = 0; dimensions.first > x; ++x, src += bpp)
					{
						std::uint16_t i_val((8 < pnginfo.bit_depth) ? fetch_16bit(src) : fetch_8bit(src));
						std::uint8_t const a_val((pnginfo.trans && (transpen == i_val)) ? 0x00 : 0xff);
						i_val >>= samp_shift;
						accumalpha &= a_val;
						bitmap.pix32((y << y_shift) + y_offs, (x << x_shift) + x_offs) = rgb_t(a_val, i_val, i_val, i_val);
					}
				}
			}
			else if (4 == pnginfo.color_type)
			{
				// handle grayscale alpha case
				uint32_t const i(0 * bps);
				uint32_t const a(1 * bps);
				for (std::uint32_t y = 0; dimensions.second > y; ++y)
				{
					for (std::uint32_t x = 0; dimensions.first > x; ++x, src += bpp)
					{
						accumalpha &= src[a];
						rgb_t const pix(src[a], src[i], src[i], src[i]);
						bitmap.pix32((y << y_shift) + y_offs, (x << x_shift) + x_offs) = pix;
					}
				}
			}
			else if (2 == pnginfo.color_type)
			{
				// handle RGB non-alpha case
				uint32_t const r(0 * bps);
				uint32_t const g(1 * bps);
				uint32_t const b(2 * bps);
				std::uint16_t const transpen_r(pnginfo.trans ? fetch_16bit(&pnginfo.trans[0]) : 0U);
				std::uint16_t const transpen_g(pnginfo.trans ? fetch_16bit(&pnginfo.trans[2]) : 0U);
				std::uint16_t const transpen_b(pnginfo.trans ? fetch_16bit(&pnginfo.trans[4]) : 0U);
				unsigned const samp_shift((8 < pnginfo.bit_depth) ? 8 : 0);
				for (std::uint32_t y = 0; dimensions.second > y; ++y)
				{
					for (std::uint32_t x = 0; dimensions.first > x; ++x, src += bpp)
					{
						uint16_t r_val((8 < pnginfo.bit_depth) ? fetch_16bit(src) : fetch_8bit(src + r));
						uint16_t g_val((8 < pnginfo.bit_depth) ? fetch_16bit(src) : fetch_8bit(src + g));
						uint16_t b_val((8 < pnginfo.bit_depth) ? fetch_16bit(src) : fetch_8bit(src + b));
						std::uint8_t const a_val((pnginfo.trans && (transpen_r == r_val) && (transpen_g == g_val) && (transpen_b == b_val)) ? 0x00 : 0xff);
						r_val >>= samp_shift;
						g_val >>= samp_shift;
						b_val >>= samp_shift;
						accumalpha &= a_val;
						bitmap.pix32((y << y_shift) + y_offs, (x << x_shift) + x_offs) = rgb_t(a_val, r_val, g_val, b_val);
					}
				}
			}
			else
			{
				// handle RGB alpha case
				uint32_t const r(0 * bps);
				uint32_t const g(1 * bps);
				uint32_t const b(2 * bps);
				uint32_t const a(3 * bps);
				for (std::uint32_t y = 0; dimensions.second > y; ++y)
				{
					for (std::uint32_t x = 0; dimensions.first > x; ++x, src += bpp)
					{
						accumalpha &= src[a];
						rgb_t const pix(src[a], src[r], src[g], src[b]);
						bitmap.pix32((y << y_shift) + y_offs, (x << x_shift) + x_offs) = pix;
					}
				}
			}
		}

		// set hasalpha flag and return
		hasalpha = 0xffU != accumalpha;
		return PNGERR_NONE;
	}

	png_error expand_buffer_8bit()
	{
		// nothing to do if we're at 8 or greater already
		if (pnginfo.bit_depth >= 8)
			return PNGERR_NONE;

		// do some basic checks for unsupported images
		if (!pnginfo.bit_depth || (8 % pnginfo.bit_depth))
			return PNGERR_UNSUPPORTED_FORMAT; // bit depth must be a factor of eight
		if ((0 != pnginfo.color_type) && (3 != pnginfo.color_type))
			return PNGERR_UNSUPPORTED_FORMAT; // only upsample monochrome and indexed colour
		if ((0 != pnginfo.interlace_method) && (1 != pnginfo.interlace_method))
			return PNGERR_UNSUPPORTED_FORMAT; // unknown interlace method

		// calculate the offset for each pass of the interlace on the input and output
		unsigned const pass_count(get_pass_count());
		std::uint32_t inp_offset[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
		std::uint32_t outp_offset[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
		for (unsigned pass = 0; pass_count > pass; ++pass)
		{
			inp_offset[pass + 1] = inp_offset[pass] + get_pass_bytes(pass);
			outp_offset[pass + 1] = outp_offset[pass] + get_pass_bytes(pass, 8);
		}

		// allocate a new buffer at 8-bit
		std::unique_ptr<std::uint8_t []> outbuf;
		try { outbuf.reset(new std::uint8_t [outp_offset[pass_count]]); }
		catch (std::bad_alloc const &) { return PNGERR_OUT_OF_MEMORY; }

		// upsample bitmap
		std::uint8_t const bytesamples(8 / pnginfo.bit_depth);
		for (unsigned pass = 0; pass_count > pass; ++pass)
		{
			std::pair<std::uint32_t, std::uint32_t> const dimensions(get_pass_dimensions(pass));
			std::uint32_t const rowsamples(samples[pnginfo.color_type] * dimensions.first);
			std::uint32_t const wholebytes(rowsamples / bytesamples);
			std::uint32_t const leftover(rowsamples % bytesamples);
			std::uint8_t const *inp(&pnginfo.image[inp_offset[pass]]);
			std::uint8_t *outp(&outbuf[outp_offset[pass]]);

			for (std::uint32_t y = 0; dimensions.second > y; ++y)
			{
				for (std::uint32_t i = 0; wholebytes > i; ++i, ++inp)
				{
					for (std::int8_t j = bytesamples - 1; 0 <= j; --j, ++outp)
					{
						*outp = (*inp >> (j * pnginfo.bit_depth)) & (0xffU >> (8 - pnginfo.bit_depth));
						if (!pnginfo.color_type)
						{
							for (unsigned k = 4; pnginfo.bit_depth <= k; k >>= 1)
								*outp |= *outp << k;
						}
					}
				}
				if (leftover)
				{
					for (std::int8_t j = leftover - 1; 0 <= j; --j,++outp)
					{
						*outp = (*inp >> (j * pnginfo.bit_depth)) & (0xffU >> (8 - pnginfo.bit_depth));
						if (!pnginfo.color_type)
						{
							for (unsigned k = 4; pnginfo.bit_depth <= k; k >>= 1)
								*outp |= *outp << k;
						}
					}
					inp++;
				}
			}
		}

		// upsample transparent pen as well
		if ((0 == pnginfo.color_type) && pnginfo.trans)
		{
			std::uint16_t pen(fetch_16bit(&pnginfo.trans[0]));
			for (unsigned k = 4; pnginfo.bit_depth <= k; k >>= 1)
				pen |= pen << k;
			put_16bit(&pnginfo.trans[0], pen);
		}

		pnginfo.image = std::move(outbuf);
		pnginfo.bit_depth = 8;
		return PNGERR_NONE;
	}

	png_error read_file(util::core_file &fp)
	{
		// initialize the data structures
		png_error error = PNGERR_NONE;
		pnginfo.reset();
		std::list<image_data_chunk> idata;

		// verify the signature at the start of the file
		error = verify_header(fp);

		// loop until we hit an IEND chunk
		while (PNGERR_NONE == error)
		{
			// read a chunk
			std::unique_ptr<std::uint8_t []> chunk_data;
			std::uint32_t chunk_type, chunk_length;
			error = read_chunk(fp, chunk_data, chunk_type, chunk_length);
			if (PNGERR_NONE == error)
			{
				if (chunk_type == PNG_CN_IEND)
					break; // stop when we hit an IEND chunk
				else
					error = process_chunk(idata, std::move(chunk_data), chunk_type, chunk_length);
			}
		}

		// finish processing the image
		if (PNGERR_NONE == error)
			error = process(idata);

		// if we have an error, free all the output data
		if (error != PNGERR_NONE)
			pnginfo.reset();

		return error;
	}
};

constexpr unsigned png_private::ADAM7_X_BIAS[7];
constexpr unsigned png_private::ADAM7_Y_BIAS[7];
constexpr unsigned png_private::ADAM7_X_SHIFT[7];
constexpr unsigned png_private::ADAM7_Y_SHIFT[7];
constexpr unsigned png_private::ADAM7_X_OFFS[7];
constexpr unsigned png_private::ADAM7_Y_OFFS[7];

} // anonymous namespace




/*-------------------------------------------------
    read_file - read a PNG from a core stream
-------------------------------------------------*/

png_error png_info::read_file(util::core_file &fp)
{
	return png_private(*this).read_file(fp);
>>>>>>> upstream/master
}


/*-------------------------------------------------
    png_read_bitmap - load a PNG file into a
    bitmap
-------------------------------------------------*/

<<<<<<< HEAD
png_error png_read_bitmap(core_file *fp, bitmap_argb32 &bitmap)
{
	png_error result;
	png_info png;
	UINT8 *src;
	int x, y;

	/* read the PNG data */
	result = png_read_file(fp, &png);
	if (result != PNGERR_NONE)
		return result;

	/* verify we can handle this PNG */
	if (png.bit_depth > 8 || png.interlace_method != 0 ||
		(png.color_type != 0 && png.color_type != 3 && png.color_type != 2 && png.color_type != 6))
	{
		png_free(&png);
		return PNGERR_UNSUPPORTED_FORMAT;
	}

	/* if less than 8 bits, upsample */
	png_expand_buffer_8bit(&png);

	/* allocate a bitmap of the appropriate size and copy it */
	bitmap.allocate(png.width, png.height);

	/* handle 8bpp palettized case */
	src = png.image;
	if (png.color_type == 3)
	{
		/* loop over width/height */
		for (y = 0; y < png.height; y++)
			for (x = 0; x < png.width; x++, src++)
			{
				/* determine alpha and expand to 32bpp */
				UINT8 alpha = (*src < png.num_trans) ? png.trans[*src] : 0xff;
				bitmap.pix32(y, x) = (alpha << 24) | (png.palette[*src * 3] << 16) | (png.palette[*src * 3 + 1] << 8) | png.palette[*src * 3 + 2];
			}
	}

	/* handle 8bpp grayscale case */
	else if (png.color_type == 0)
	{
		for (y = 0; y < png.height; y++)
			for (x = 0; x < png.width; x++, src++)
				bitmap.pix32(y, x) = 0xff000000 | (*src << 16) | (*src << 8) | *src;
	}

	/* handle 32bpp non-alpha case */
	else if (png.color_type == 2)
	{
		for (y = 0; y < png.height; y++)
			for (x = 0; x < png.width; x++, src += 3)
				bitmap.pix32(y, x) = 0xff000000 | (src[0] << 16) | (src[1] << 8) | src[2];
	}

	/* handle 32bpp alpha case */
	else if (png.color_type == 6)
	{
		for (y = 0; y < png.height; y++)
			for (x = 0; x < png.width; x++, src += 4)
				bitmap.pix32(y, x) = (src[3] << 24) | (src[0] << 16) | (src[1] << 8) | src[2];
	}

	/* free our temporary data and return */
	png_free(&png);
	return PNGERR_NONE;
=======
png_error png_read_bitmap(util::core_file &fp, bitmap_argb32 &bitmap)
{
	png_error result;
	png_info pnginfo;
	png_private png(pnginfo);

	// read the PNG data
	result = png.read_file(fp);
	if (PNGERR_NONE != result)
		return result;

	// resample to 8bpp if necessary
	result = png.expand_buffer_8bit();
	if (PNGERR_NONE != result)
	{
		pnginfo.free_data();
		return result;
	}

	// allocate a bitmap of the appropriate size and copy it
	bool hasalpha;
	return png.copy_to_bitmap(bitmap, hasalpha);
}


/*-------------------------------------------------
    expand_buffer_8bit - copy PNG data into a
    bitmap
-------------------------------------------------*/

png_error png_info::copy_to_bitmap(bitmap_argb32 &bitmap, bool &hasalpha)
{
	return png_private(*this).copy_to_bitmap(bitmap, hasalpha);
>>>>>>> upstream/master
}


/*-------------------------------------------------
<<<<<<< HEAD
    png_expand_buffer_8bit - expand a buffer from
    sub 8-bit to 8-bit
-------------------------------------------------*/

png_error png_expand_buffer_8bit(png_info *pnginfo)
{
	int i,j, k;
	UINT8 *inp, *outp, *outbuf;

	/* nothing to do if we're at 8 or greater already */
	if (pnginfo->bit_depth >= 8)
		return PNGERR_NONE;

	/* allocate a new buffer at 8-bit */
	outbuf = (UINT8 *)malloc(pnginfo->width * pnginfo->height);
	if (outbuf == NULL)
		return PNGERR_OUT_OF_MEMORY;

	inp = pnginfo->image;
	outp = outbuf;

	for (i = 0; i < pnginfo->height; i++)
	{
		for(j = 0; j < pnginfo->width / ( 8 / pnginfo->bit_depth); j++)
		{
			for (k = 8 / pnginfo->bit_depth-1; k >= 0; k--)
				*outp++ = (*inp >> k * pnginfo->bit_depth) & (0xff >> (8 - pnginfo->bit_depth));
			inp++;
		}
		if (pnginfo->width % (8 / pnginfo->bit_depth))
		{
			for (k = pnginfo->width % (8 / pnginfo->bit_depth)-1; k >= 0; k--)
				*outp++ = (*inp >> k * pnginfo->bit_depth) & (0xff >> (8 - pnginfo->bit_depth));
			inp++;
		}
	}
	free (pnginfo->image);
	pnginfo->image = outbuf;

	return PNGERR_NONE;
=======
    expand_buffer_8bit - expand a buffer from
    sub 8-bit to 8-bit
-------------------------------------------------*/

png_error png_info::expand_buffer_8bit()
{
	return png_private(*this).expand_buffer_8bit();
>>>>>>> upstream/master
}



/***************************************************************************
    PNG WRITING FUNCTIONS
***************************************************************************/

/*-------------------------------------------------
<<<<<<< HEAD
    png_add_text - add a text entry to the png_info
-------------------------------------------------*/

png_error png_add_text(png_info *pnginfo, const char *keyword, const char *text)
{
	png_text *newtext, *pt, *ct;
	char *textdata;
	int keylen;

	/* allocate a new text element */
	newtext = (png_text *)malloc(sizeof(*newtext));
	if (newtext == NULL)
		return PNGERR_OUT_OF_MEMORY;

	/* allocate a string long enough to hold both */
	keylen = (int)strlen(keyword);
	textdata = (char *)malloc(keylen + 1 + strlen(text) + 1);
	if (textdata == NULL)
	{
		free(newtext);
		return PNGERR_OUT_OF_MEMORY;
	}

	/* copy in the data */
	strcpy(textdata, keyword);
	strcpy(textdata + keylen + 1, text);

	/* text follows a trailing NULL */
	newtext->keyword = textdata;
	newtext->text = textdata + keylen + 1;
	newtext->next = NULL;

	/* add us to the end of the linked list */
	for (pt = NULL, ct = pnginfo->textlist; ct != NULL; pt = ct, ct = ct->next) ;
	if (pt == NULL)
		pnginfo->textlist = newtext;
	else
		pt->next = newtext;

=======
    add_text - add a text entry to the png_info
-------------------------------------------------*/

png_error png_info::add_text(const char *keyword, const char *text)
{
	// apply rules to keyword
	char32_t prev(0);
	std::size_t cnt(0);
	char const *const kwend(keyword + std::strlen(keyword));
	for (char const *ptr = keyword; kwend > ptr; )
	{
		char32_t ch;
		int const len(uchar_from_utf8(&ch, ptr, kwend - ptr));
		if ((0 >= len) || (32 > ch) || (255 < ch) || ((126 < ch) && (161 > ch)) || (((32 == prev) || (keyword == ptr)) && (32 == ch)))
			return PNGERR_UNSUPPORTED_FORMAT;
		prev = ch;
		++cnt;
		ptr += len;
	}
	if ((32 == prev) || (1 > cnt) || (79 < cnt))
		return PNGERR_UNSUPPORTED_FORMAT;

	// apply rules to text
	char const *const textend(text + std::strlen(text));
	for (char const *ptr = text; textend > ptr; )
	{
		char32_t ch;
		int const len(uchar_from_utf8(&ch, ptr, textend - ptr));
		if ((0 >= len) || (1 > ch) || (255 < ch))
			return PNGERR_UNSUPPORTED_FORMAT;
		ptr += len;
	}

	// allocate a new text element
	try { textlist.emplace_back(std::piecewise_construct, std::forward_as_tuple(keyword, kwend), std::forward_as_tuple(text, textend)); }
	catch (std::bad_alloc const &) { return PNGERR_OUT_OF_MEMORY; }
>>>>>>> upstream/master
	return PNGERR_NONE;
}


/*-------------------------------------------------
    write_chunk - write an in-memory chunk to
    the given file
-------------------------------------------------*/

<<<<<<< HEAD
static png_error write_chunk(core_file *fp, const UINT8 *data, UINT32 type, UINT32 length)
{
	UINT8 tempbuff[8];
	UINT32 crc;
=======
static png_error write_chunk(util::core_file &fp, const uint8_t *data, uint32_t type, uint32_t length)
{
	uint8_t tempbuff[8];
	uint32_t crc;
>>>>>>> upstream/master

	/* stuff the length/type into the buffer */
	put_32bit(tempbuff + 0, length);
	put_32bit(tempbuff + 4, type);
	crc = crc32(0, tempbuff + 4, 4);

	/* write that data */
<<<<<<< HEAD
	if (core_fwrite(fp, tempbuff, 8) != 8)
=======
	if (fp.write(tempbuff, 8) != 8)
>>>>>>> upstream/master
		return PNGERR_FILE_ERROR;

	/* append the actual data */
	if (length > 0)
	{
<<<<<<< HEAD
		if (core_fwrite(fp, data, length) != length)
=======
		if (fp.write(data, length) != length)
>>>>>>> upstream/master
			return PNGERR_FILE_ERROR;
		crc = crc32(crc, data, length);
	}

	/* write the CRC */
	put_32bit(tempbuff, crc);
<<<<<<< HEAD
	if (core_fwrite(fp, tempbuff, 4) != 4)
=======
	if (fp.write(tempbuff, 4) != 4)
>>>>>>> upstream/master
		return PNGERR_FILE_ERROR;

	return PNGERR_NONE;
}


/*-------------------------------------------------
    write_deflated_chunk - write an in-memory
    chunk to the given file by deflating it
-------------------------------------------------*/

<<<<<<< HEAD
static png_error write_deflated_chunk(core_file *fp, UINT8 *data, UINT32 type, UINT32 length)
{
	UINT64 lengthpos = core_ftell(fp);
	UINT8 tempbuff[8192];
	UINT32 zlength = 0;
	z_stream stream;
	UINT32 crc;
=======
static png_error write_deflated_chunk(util::core_file &fp, uint8_t *data, uint32_t type, uint32_t length)
{
	uint64_t lengthpos = fp.tell();
	uint8_t tempbuff[8192];
	uint32_t zlength = 0;
	z_stream stream;
	uint32_t crc;
>>>>>>> upstream/master
	int zerr;

	/* stuff the length/type into the buffer */
	put_32bit(tempbuff + 0, length);
	put_32bit(tempbuff + 4, type);
	crc = crc32(0, tempbuff + 4, 4);

	/* write that data */
<<<<<<< HEAD
	if (core_fwrite(fp, tempbuff, 8) != 8)
=======
	if (fp.write(tempbuff, 8) != 8)
>>>>>>> upstream/master
		return PNGERR_FILE_ERROR;

	/* initialize the stream */
	memset(&stream, 0, sizeof(stream));
	stream.next_in = data;
	stream.avail_in = length;
	zerr = deflateInit(&stream, Z_DEFAULT_COMPRESSION);
	if (zerr != Z_OK)
		return PNGERR_COMPRESS_ERROR;

	/* now loop until we run out of data */
	for ( ; ; )
	{
		/* compress this chunk */
		stream.next_out = tempbuff;
		stream.avail_out = sizeof(tempbuff);
		zerr = deflate(&stream, Z_FINISH);

		/* if there's data to write, do it */
		if (stream.avail_out < sizeof(tempbuff))
		{
			int bytes = sizeof(tempbuff) - stream.avail_out;
<<<<<<< HEAD
			if (core_fwrite(fp, tempbuff, bytes) != bytes)
=======
			if (fp.write(tempbuff, bytes) != bytes)
>>>>>>> upstream/master
			{
				deflateEnd(&stream);
				return PNGERR_FILE_ERROR;
			}
			crc = crc32(crc, tempbuff, bytes);
			zlength += bytes;
		}

		/* stop at the end of the stream */
		if (zerr == Z_STREAM_END)
			break;

		/* other errors are fatal */
		if (zerr != Z_OK)
		{
			deflateEnd(&stream);
			return PNGERR_COMPRESS_ERROR;
		}
	}

	/* clean up deflater(maus) */
	zerr = deflateEnd(&stream);
	if (zerr != Z_OK)
		return PNGERR_COMPRESS_ERROR;

	/* write the CRC */
	put_32bit(tempbuff, crc);
<<<<<<< HEAD
	if (core_fwrite(fp, tempbuff, 4) != 4)
		return PNGERR_FILE_ERROR;

	/* seek back and update the length */
	core_fseek(fp, lengthpos, SEEK_SET);
	put_32bit(tempbuff + 0, zlength);
	if (core_fwrite(fp, tempbuff, 4) != 4)
		return PNGERR_FILE_ERROR;

	/* return to the end */
	core_fseek(fp, lengthpos + 8 + zlength + 4, SEEK_SET);
=======
	if (fp.write(tempbuff, 4) != 4)
		return PNGERR_FILE_ERROR;

	/* seek back and update the length */
	fp.seek(lengthpos, SEEK_SET);
	put_32bit(tempbuff + 0, zlength);
	if (fp.write(tempbuff, 4) != 4)
		return PNGERR_FILE_ERROR;

	/* return to the end */
	fp.seek(lengthpos + 8 + zlength + 4, SEEK_SET);
>>>>>>> upstream/master
	return PNGERR_NONE;
}


/*-------------------------------------------------
    convert_bitmap_to_image_palette - convert a
    bitmap to a palettized image
-------------------------------------------------*/

<<<<<<< HEAD
static png_error convert_bitmap_to_image_palette(png_info *pnginfo, const bitmap_t &bitmap, int palette_length, const rgb_t *palette)
=======
static png_error convert_bitmap_to_image_palette(png_info &pnginfo, const bitmap_t &bitmap, int palette_length, const rgb_t *palette)
>>>>>>> upstream/master
{
	int rowbytes;
	int x, y;

	/* set the common info */
<<<<<<< HEAD
	pnginfo->width = bitmap.width();
	pnginfo->height = bitmap.height();
	pnginfo->bit_depth = 8;
	pnginfo->color_type = 3;
	pnginfo->num_palette = 256;
	rowbytes = pnginfo->width;

	/* allocate memory for the palette */
	pnginfo->palette = (UINT8 *)malloc(3 * 256);
	if (pnginfo->palette == NULL)
		return PNGERR_OUT_OF_MEMORY;

	/* build the palette */
	memset(pnginfo->palette, 0, 3 * 256);
	for (x = 0; x < palette_length; x++)
	{
		rgb_t color = palette[x];
		pnginfo->palette[3 * x + 0] = color.r();
		pnginfo->palette[3 * x + 1] = color.g();
		pnginfo->palette[3 * x + 2] = color.b();
	}

	/* allocate memory for the image */
	pnginfo->image = (UINT8 *)malloc(pnginfo->height * (rowbytes + 1));
	if (pnginfo->image == NULL)
	{
		free(pnginfo->palette);
		return PNGERR_OUT_OF_MEMORY;
	}

	/* copy in the pixels, specifying a NULL filter */
	for (y = 0; y < pnginfo->height; y++)
	{
		UINT16 *src = reinterpret_cast<UINT16 *>(bitmap.raw_pixptr(y));
		UINT8 *dst = pnginfo->image + y * (rowbytes + 1);

		/* store the filter byte, then copy the data */
		*dst++ = 0;
		for (x = 0; x < pnginfo->width; x++)
=======
	pnginfo.width = bitmap.width();
	pnginfo.height = bitmap.height();
	pnginfo.bit_depth = 8;
	pnginfo.color_type = 3;
	pnginfo.num_palette = 256;
	rowbytes = pnginfo.width;

	/* allocate memory for the palette */
	try { pnginfo.palette.reset(new std::uint8_t [3 * 256]); }
	catch (std::bad_alloc const &) { return PNGERR_OUT_OF_MEMORY; }

	/* build the palette */
	std::fill_n(pnginfo.palette.get(), 3 * 256, 0);
	for (x = 0; x < palette_length; x++)
	{
		rgb_t color = palette[x];
		pnginfo.palette[3 * x + 0] = color.r();
		pnginfo.palette[3 * x + 1] = color.g();
		pnginfo.palette[3 * x + 2] = color.b();
	}

	/* allocate memory for the image */
	try
	{
		pnginfo.image.reset(new std::uint8_t [pnginfo.height * (rowbytes + 1)]);
	}
	catch (std::bad_alloc const &)
	{
		pnginfo.palette.reset();
		return PNGERR_OUT_OF_MEMORY;
	}

	/* copy in the pixels, specifying a nullptr filter */
	for (y = 0; y < pnginfo.height; y++)
	{
		uint16_t *src = reinterpret_cast<uint16_t *>(bitmap.raw_pixptr(y));
		uint8_t *dst = &pnginfo.image[y * (rowbytes + 1)];

		/* store the filter byte, then copy the data */
		*dst++ = 0;
		for (x = 0; x < pnginfo.width; x++)
>>>>>>> upstream/master
			*dst++ = *src++;
	}

	return PNGERR_NONE;
}


/*-------------------------------------------------
    convert_bitmap_to_image_rgb - convert a
    bitmap to an RGB image
-------------------------------------------------*/

<<<<<<< HEAD
static png_error convert_bitmap_to_image_rgb(png_info *pnginfo, const bitmap_t &bitmap, int palette_length, const rgb_t *palette)
=======
static png_error convert_bitmap_to_image_rgb(png_info &pnginfo, const bitmap_t &bitmap, int palette_length, const rgb_t *palette)
>>>>>>> upstream/master
{
	int alpha = (bitmap.format() == BITMAP_FORMAT_ARGB32);
	int rowbytes;
	int x, y;

	/* set the common info */
<<<<<<< HEAD
	pnginfo->width = bitmap.width();
	pnginfo->height = bitmap.height();
	pnginfo->bit_depth = 8;
	pnginfo->color_type = alpha ? 6 : 2;
	rowbytes = pnginfo->width * (alpha ? 4 : 3);

	/* allocate memory for the image */
	pnginfo->image = (UINT8 *)malloc(pnginfo->height * (rowbytes + 1));
	if (pnginfo->image == NULL)
		return PNGERR_OUT_OF_MEMORY;

	/* copy in the pixels, specifying a NULL filter */
	for (y = 0; y < pnginfo->height; y++)
	{
		UINT8 *dst = pnginfo->image + y * (rowbytes + 1);
=======
	pnginfo.width = bitmap.width();
	pnginfo.height = bitmap.height();
	pnginfo.bit_depth = 8;
	pnginfo.color_type = alpha ? 6 : 2;
	rowbytes = pnginfo.width * (alpha ? 4 : 3);

	/* allocate memory for the image */
	try { pnginfo.image.reset(new std::uint8_t [pnginfo.height * (rowbytes + 1)]); }
	catch (std::bad_alloc const &) { return PNGERR_OUT_OF_MEMORY; }

	/* copy in the pixels, specifying a nullptr filter */
	for (y = 0; y < pnginfo.height; y++)
	{
		uint8_t *dst = &pnginfo.image[y * (rowbytes + 1)];
>>>>>>> upstream/master

		/* store the filter byte, then copy the data */
		*dst++ = 0;

		/* 16bpp palettized format */
		if (bitmap.format() == BITMAP_FORMAT_IND16)
		{
<<<<<<< HEAD
			UINT16 *src16 = reinterpret_cast<UINT16 *>(bitmap.raw_pixptr(y));
			for (x = 0; x < pnginfo->width; x++)
=======
			uint16_t *src16 = reinterpret_cast<uint16_t *>(bitmap.raw_pixptr(y));
			for (x = 0; x < pnginfo.width; x++)
>>>>>>> upstream/master
			{
				rgb_t color = palette[*src16++];
				*dst++ = color.r();
				*dst++ = color.g();
				*dst++ = color.b();
			}
		}

		/* 32-bit RGB direct */
		else if (bitmap.format() == BITMAP_FORMAT_RGB32)
		{
<<<<<<< HEAD
			UINT32 *src32 = reinterpret_cast<UINT32 *>(bitmap.raw_pixptr(y));
			for (x = 0; x < pnginfo->width; x++)
=======
			uint32_t *src32 = reinterpret_cast<uint32_t *>(bitmap.raw_pixptr(y));
			for (x = 0; x < pnginfo.width; x++)
>>>>>>> upstream/master
			{
				rgb_t raw = *src32++;
				*dst++ = raw.r();
				*dst++ = raw.g();
				*dst++ = raw.b();
			}
		}

		/* 32-bit ARGB direct */
		else if (bitmap.format() == BITMAP_FORMAT_ARGB32)
		{
<<<<<<< HEAD
			UINT32 *src32 = reinterpret_cast<UINT32 *>(bitmap.raw_pixptr(y));
			for (x = 0; x < pnginfo->width; x++)
=======
			uint32_t *src32 = reinterpret_cast<uint32_t *>(bitmap.raw_pixptr(y));
			for (x = 0; x < pnginfo.width; x++)
>>>>>>> upstream/master
			{
				rgb_t raw = *src32++;
				*dst++ = raw.r();
				*dst++ = raw.g();
				*dst++ = raw.b();
				*dst++ = raw.a();
			}
		}

		/* unsupported format */
		else
			return PNGERR_UNSUPPORTED_FORMAT;
	}

	return PNGERR_NONE;
}


/*-------------------------------------------------
    write_png_stream - stream a series of PNG
    chunks to the given file
-------------------------------------------------*/

<<<<<<< HEAD
static png_error write_png_stream(core_file *fp, png_info *pnginfo, const bitmap_t &bitmap, int palette_length, const rgb_t *palette)
{
	UINT8 tempbuff[16];
	png_text *text;
	png_error error;

	/* create an unfiltered image in either palette or RGB form */
=======
static png_error write_png_stream(util::core_file &fp, png_info &pnginfo, const bitmap_t &bitmap, int palette_length, const rgb_t *palette)
{
	uint8_t tempbuff[16];
	png_error error;

	// create an unfiltered image in either palette or RGB form
>>>>>>> upstream/master
	if (bitmap.format() == BITMAP_FORMAT_IND16 && palette_length <= 256)
		error = convert_bitmap_to_image_palette(pnginfo, bitmap, palette_length, palette);
	else
		error = convert_bitmap_to_image_rgb(pnginfo, bitmap, palette_length, palette);
	if (error != PNGERR_NONE)
<<<<<<< HEAD
		goto handle_error;

	/* if we wanted to get clever and do filtering, we would do it here */

	/* write the IHDR chunk */
	put_32bit(tempbuff + 0, pnginfo->width);
	put_32bit(tempbuff + 4, pnginfo->height);
	put_8bit(tempbuff + 8, pnginfo->bit_depth);
	put_8bit(tempbuff + 9, pnginfo->color_type);
	put_8bit(tempbuff + 10, pnginfo->compression_method);
	put_8bit(tempbuff + 11, pnginfo->filter_method);
	put_8bit(tempbuff + 12, pnginfo->interlace_method);
	error = write_chunk(fp, tempbuff, PNG_CN_IHDR, 13);
	if (error != PNGERR_NONE)
		goto handle_error;

	/* write the PLTE chunk */
	if (pnginfo->num_palette > 0)
		error = write_chunk(fp, pnginfo->palette, PNG_CN_PLTE, pnginfo->num_palette * 3);
	if (error != PNGERR_NONE)
		goto handle_error;

	/* write a single IDAT chunk */
	error = write_deflated_chunk(fp, pnginfo->image, PNG_CN_IDAT, pnginfo->height * (compute_rowbytes(pnginfo) + 1));
	if (error != PNGERR_NONE)
		goto handle_error;

	/* write TEXT chunks */
	for (text = pnginfo->textlist; text != NULL; text = text->next)
	{
		error = write_chunk(fp, (UINT8 *)text->keyword, PNG_CN_tEXt, (UINT32)strlen(text->keyword) + 1 + (UINT32)strlen(text->text));
		if (error != PNGERR_NONE)
			goto handle_error;
	}

	/* write an IEND chunk */
	error = write_chunk(fp, NULL, PNG_CN_IEND, 0);

handle_error:
	return error;
}


png_error png_write_bitmap(core_file *fp, png_info *info, bitmap_t &bitmap, int palette_length, const rgb_t *palette)
{
	png_info pnginfo;
	png_error error;

	/* use a dummy pnginfo if none passed to us */
	if (info == NULL)
	{
		info = &pnginfo;
		memset(&pnginfo, 0, sizeof(pnginfo));
	}

	/* write the PNG signature */
	if (core_fwrite(fp, PNG_Signature, 8) != 8)
	{
		if (info == &pnginfo)
			png_free(&pnginfo);
		return PNGERR_FILE_ERROR;
	}

	/* write the rest of the PNG data */
	error = write_png_stream(fp, info, bitmap, palette_length, palette);
	if (info == &pnginfo)
		png_free(&pnginfo);
	return error;
=======
		return error;

	// if we wanted to get clever and do filtering, we would do it here

	// write the IHDR chunk
	put_32bit(tempbuff + 0, pnginfo.width);
	put_32bit(tempbuff + 4, pnginfo.height);
	put_8bit(tempbuff + 8, pnginfo.bit_depth);
	put_8bit(tempbuff + 9, pnginfo.color_type);
	put_8bit(tempbuff + 10, pnginfo.compression_method);
	put_8bit(tempbuff + 11, pnginfo.filter_method);
	put_8bit(tempbuff + 12, pnginfo.interlace_method);
	error = write_chunk(fp, tempbuff, PNG_CN_IHDR, 13);
	if (error != PNGERR_NONE)
		return error;

	// write the PLTE chunk
	if (pnginfo.num_palette > 0)
		error = write_chunk(fp, pnginfo.palette.get(), PNG_CN_PLTE, pnginfo.num_palette * 3);
	if (error != PNGERR_NONE)
		return error;

	// write a single IDAT chunk */
	error = write_deflated_chunk(fp, pnginfo.image.get(), PNG_CN_IDAT, pnginfo.height * (compute_rowbytes(pnginfo) + 1));
	if (error != PNGERR_NONE)
		return error;

	// write TEXT chunks
	std::vector<std::uint8_t> textbuf;
	for (png_info::png_text const &text : pnginfo.textlist)
	{
		try { textbuf.resize(text.first.length() + 1 + text.second.length()); }
		catch (std::bad_alloc const &) { return PNGERR_OUT_OF_MEMORY; }
		std::uint8_t *dst(&textbuf[0]);

		// convert keyword to ISO-8859-1
		char const *const kwend(text.first.c_str() + text.first.length());
		for (char const *src = text.first.c_str(); kwend > src; ++dst)
		{
			char32_t ch;
			int const len(uchar_from_utf8(&ch, src, kwend - src));
			if (0 >= len)
				break;
			*dst = std::uint8_t(ch);
			src += len;
		}

		// NUL separator between keword and text
		*dst++ = 0;

		// convert text to ISO-8859-1
		char const *const textend(text.second.c_str() + text.second.length());
		for (char const *src = text.second.c_str(); textend > src; ++dst)
		{
			char32_t ch;
			int const len(uchar_from_utf8(&ch, src, textend - src));
			if (0 >= len)
				break;
			*dst = std::uint8_t(ch);
			src += len;
		}

		error = write_chunk(fp, &textbuf[0], PNG_CN_tEXt, dst - &textbuf[0]);
		if (error != PNGERR_NONE)
			return error;
	}

	// write an IEND chunk
	return write_chunk(fp, nullptr, PNG_CN_IEND, 0);
}


png_error png_write_bitmap(util::core_file &fp, png_info *info, bitmap_t const &bitmap, int palette_length, const rgb_t *palette)
{
	// use a dummy pnginfo if none passed to us
	png_info pnginfo;
	if (info == nullptr)
		info = &pnginfo;

	// write the PNG signature
	if (fp.write(PNG_Signature, 8) != 8)
		return PNGERR_FILE_ERROR;

	/* write the rest of the PNG data */
	return write_png_stream(fp, *info, bitmap, palette_length, palette);
>>>>>>> upstream/master
}



/********************************************************************************

  MNG write functions

********************************************************************************/

<<<<<<< HEAD
png_error mng_capture_start(core_file *fp, bitmap_t &bitmap, double rate)
{
	UINT8 mhdr[28];
	png_error error;

	if (core_fwrite(fp, MNG_Signature, 8) != 8)
=======
/**
 * @fn  png_error mng_capture_start(util::core_file &fp, bitmap_t &bitmap, double rate)
 *
 * @brief   Mng capture start.
 *
 * @param [in,out]  fp      If non-null, the fp.
 * @param [in,out]  bitmap  The bitmap.
 * @param   rate            The rate.
 *
 * @return  A png_error.
 */

png_error mng_capture_start(util::core_file &fp, bitmap_t &bitmap, double rate)
{
	uint8_t mhdr[28];

	if (fp.write(MNG_Signature, 8) != 8)
>>>>>>> upstream/master
		return PNGERR_FILE_ERROR;

	memset(mhdr, 0, 28);
	put_32bit(mhdr + 0, bitmap.width());
	put_32bit(mhdr + 4, bitmap.height());
	put_32bit(mhdr + 8, rate);
<<<<<<< HEAD
	put_32bit(mhdr + 24, 0x0041); /* Simplicity profile */
	/* frame count and play time unspecified because
	   we don't know at this stage */
	error = write_chunk(fp, mhdr, MNG_CN_MHDR, 28);
	if (error != PNGERR_NONE)
		return error;

	return PNGERR_NONE;
}

png_error mng_capture_frame(core_file *fp, png_info *info, bitmap_t &bitmap, int palette_length, const rgb_t *palette)
=======
	put_32bit(mhdr + 24, 0x0041); // Simplicity profile - frame count and play time unspecified because we don't know at this stage
	return write_chunk(fp, mhdr, MNG_CN_MHDR, 28);
}

/**
 * @fn  png_error mng_capture_frame(util::core_file &fp, png_info *info, bitmap_t &bitmap, int palette_length, const rgb_t *palette)
 *
 * @brief   Mng capture frame.
 *
 * @param [in,out]  fp      If non-null, the fp.
 * @param [in,out]  info    If non-null, the information.
 * @param [in,out]  bitmap  The bitmap.
 * @param   palette_length  Length of the palette.
 * @param   palette         The palette.
 *
 * @return  A png_error.
 */

png_error mng_capture_frame(util::core_file &fp, png_info &info, bitmap_t const &bitmap, int palette_length, const rgb_t *palette)
>>>>>>> upstream/master
{
	return write_png_stream(fp, info, bitmap, palette_length, palette);
}

<<<<<<< HEAD
png_error mng_capture_stop(core_file *fp)
{
	return write_chunk(fp, NULL, MNG_CN_MEND, 0);
=======
/**
 * @fn  png_error mng_capture_stop(util::core_file &fp)
 *
 * @brief   Mng capture stop.
 *
 * @param [in,out]  fp  If non-null, the fp.
 *
 * @return  A png_error.
 */

png_error mng_capture_stop(util::core_file &fp)
{
	return write_chunk(fp, nullptr, MNG_CN_MEND, 0);
>>>>>>> upstream/master
}
