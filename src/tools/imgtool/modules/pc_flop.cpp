// license:BSD-3-Clause
// copyright-holders:Raphael Nabet
/****************************************************************************

    pc_flop.c

    PC floppies

****************************************************************************/

#include "imgtool.h"
#include "formats/imageutl.h"
#include "formats/pc_dsk.h"
#include "fat.h"
#include "iflopimg.h"

#define FAT_SECLEN              512


<<<<<<< HEAD
static imgtoolerr_t fat_image_create(imgtool_image *image, imgtool_stream *stream, option_resolution *opts)
{
	imgtoolerr_t err;
	UINT32 tracks, heads, sectors;
	UINT8 buffer[FAT_SECLEN];
	imgtool_class imgclass = { fat_get_info };
	imgtoolerr_t (*fat_partition_create)(imgtool_image *image, UINT64 first_block, UINT64 block_count);

	tracks = option_resolution_lookup_int(opts, 'T');
	heads = option_resolution_lookup_int(opts, 'H');
	sectors = option_resolution_lookup_int(opts, 'S');
=======
static imgtoolerr_t fat_image_create(imgtool::image &image, imgtool::stream::ptr &&stream, util::option_resolution *opts)
{
	imgtoolerr_t err;
	uint32_t tracks, heads, sectors;
	uint8_t buffer[FAT_SECLEN];
	imgtool_class imgclass = { fat_get_info };
	imgtoolerr_t (*fat_partition_create)(imgtool::image &image, uint64_t first_block, uint64_t block_count);

	tracks = opts->lookup_int('T');
	heads = opts->lookup_int('H');
	sectors = opts->lookup_int('S');
>>>>>>> upstream/master

	/* set up just enough of a boot sector to specify geometry */
	memset(buffer, 0, sizeof(buffer));
	place_integer_le(buffer, 24, 2, sectors);
	place_integer_le(buffer, 26, 2, heads);
<<<<<<< HEAD
	place_integer_le(buffer, 19, 2, (UINT16) (((UINT64) tracks * heads * sectors) >> 0));
	place_integer_le(buffer, 32, 4, (UINT16) (((UINT64) tracks * heads * sectors) >> 16));
	err = imgtool_image_write_block(image, 0, buffer);
=======
	place_integer_le(buffer, 19, 2, (uint16_t) (((uint64_t) tracks * heads * sectors) >> 0));
	place_integer_le(buffer, 32, 4, (uint16_t) (((uint64_t) tracks * heads * sectors) >> 16));
	err = image.write_block(0, buffer);
>>>>>>> upstream/master
	if (err)
		goto done;

	/* load fat_partition_create */
<<<<<<< HEAD
	fat_partition_create = (imgtoolerr_t (*)(imgtool_image *, UINT64, UINT64))
		imgtool_get_info_fct(&imgclass, IMGTOOLINFO_PTR_CREATE_PARTITION);

	/* actually create the partition */
	err = fat_partition_create(image, 0, ((UINT64) tracks) * heads * sectors);
=======
	fat_partition_create = (imgtoolerr_t (*)(imgtool::image &, uint64_t, uint64_t))
		imgtool_get_info_fct(&imgclass, IMGTOOLINFO_PTR_CREATE_PARTITION);

	/* actually create the partition */
	err = fat_partition_create(image, 0, ((uint64_t) tracks) * heads * sectors);
>>>>>>> upstream/master
	if (err)
		goto done;

done:
	return err;
}



<<<<<<< HEAD
static imgtoolerr_t fat_image_get_geometry(imgtool_image *image, UINT32 *tracks, UINT32 *heads, UINT32 *sectors)
{
	imgtoolerr_t err;
	UINT64 total_sectors;
	UINT8 buffer[FAT_SECLEN];

	err = imgtool_image_read_block(image, 0, buffer);
=======
static imgtoolerr_t fat_image_get_geometry(imgtool::image &image, uint32_t *tracks, uint32_t *heads, uint32_t *sectors)
{
	imgtoolerr_t err;
	uint64_t total_sectors;
	uint8_t buffer[FAT_SECLEN];

	err = image.read_block(0, buffer);
>>>>>>> upstream/master
	if (err)
		return err;

	total_sectors = pick_integer_le(buffer, 19, 2)
		| (pick_integer_le(buffer, 32, 4) << 16);

	*sectors = pick_integer_le(buffer, 24, 2);
	*heads = pick_integer_le(buffer, 26, 2);
	*tracks = total_sectors / *heads / *sectors;
	return IMGTOOLERR_SUCCESS;
}



<<<<<<< HEAD
static imgtoolerr_t fat_get_sector_position(imgtool_image *image, UINT32 sector_index,
	UINT32 *track, UINT32 *head, UINT32 *sector)
{
	imgtoolerr_t err;
	UINT32 tracks, heads, sectors;
=======
static imgtoolerr_t fat_get_sector_position(imgtool::image &image, uint32_t sector_index,
	uint32_t *track, uint32_t *head, uint32_t *sector)
{
	imgtoolerr_t err;
	uint32_t tracks, heads, sectors;
>>>>>>> upstream/master

	if (sector_index == 0)
	{
		/* special case */
		*head = 0;
		*track = 0;
		*sector = 1;
	}
	else
	{
<<<<<<< HEAD
		err = imgtool_image_get_geometry(image, &tracks, &heads, &sectors);
=======
		err = image.get_geometry(&tracks, &heads, &sectors);
>>>>>>> upstream/master
		if (err)
			return err;

		*track = sector_index / sectors / heads;
		*head = (sector_index / sectors) % heads;
		*sector = 1 + (sector_index % sectors);
	}
	return IMGTOOLERR_SUCCESS;
}



<<<<<<< HEAD
static imgtoolerr_t fat_image_readblock(imgtool_image *image, void *buffer, UINT64 block)
{
	imgtoolerr_t err;
	floperr_t ferr;
	UINT32 track, head, sector;
	UINT32 block_size;

	err = imgtool_image_get_block_size(image, &block_size);
=======
static imgtoolerr_t fat_image_readblock(imgtool::image &image, void *buffer, uint64_t block)
{
	imgtoolerr_t err;
	floperr_t ferr;
	uint32_t track, head, sector;
	uint32_t block_size;

	err = image.get_block_size(block_size);
>>>>>>> upstream/master
	if (err)
		return err;

	err = fat_get_sector_position(image, block, &track, &head, &sector);
	if (err)
		return err;

	ferr = floppy_read_sector(imgtool_floppy(image), head, track, sector, 0, buffer, block_size);
	if (ferr)
		return imgtool_floppy_error(ferr);
	return IMGTOOLERR_SUCCESS;
}



<<<<<<< HEAD
static imgtoolerr_t fat_image_writeblock(imgtool_image *image, const void *buffer, UINT64 block)
{
	imgtoolerr_t err;
	floperr_t ferr;
	UINT32 track, head, sector;
	UINT32 block_size;

	err = imgtool_image_get_block_size(image, &block_size);
=======
static imgtoolerr_t fat_image_writeblock(imgtool::image &image, const void *buffer, uint64_t block)
{
	imgtoolerr_t err;
	floperr_t ferr;
	uint32_t track, head, sector;
	uint32_t block_size;

	err = image.get_block_size(block_size);
>>>>>>> upstream/master
	if (err)
		return err;

	err = fat_get_sector_position(image, block, &track, &head, &sector);
	if (err)
		return err;

	ferr = floppy_write_sector(imgtool_floppy(image), head, track, sector, 0, buffer, block_size, 0);   /* TODO: pass ddam argument from imgtool */
	if (ferr)
		return imgtool_floppy_error(ferr);
	return IMGTOOLERR_SUCCESS;
}



<<<<<<< HEAD
void pc_floppy_get_info(const imgtool_class *imgclass, UINT32 state, union imgtoolinfo *info)
=======
void pc_floppy_get_info(const imgtool_class *imgclass, uint32_t state, union imgtoolinfo *info)
>>>>>>> upstream/master
{
	switch(state)
	{
		/* --- the following bits of info are returned as 64-bit signed integers --- */
		case IMGTOOLINFO_INT_BLOCK_SIZE:                    info->i = FAT_SECLEN; break;

		/* --- the following bits of info are returned as NULL-terminated strings --- */
		case IMGTOOLINFO_STR_NAME:                          strcpy(info->s = imgtool_temp_str(), "fat"); break;
		case IMGTOOLINFO_STR_DESCRIPTION:                   strcpy(info->s = imgtool_temp_str(), "FAT format"); break;

		/* --- the following bits of info are returned as pointers to data or functions --- */
		case IMGTOOLINFO_PTR_MAKE_CLASS:                    info->make_class = imgtool_floppy_make_class; break;
		case IMGTOOLINFO_PTR_FLOPPY_CREATE:                 info->create = fat_image_create; break;
		case IMGTOOLINFO_PTR_FLOPPY_FORMAT:                 info->p = (void *) floppyoptions_pc; break;
		case IMGTOOLINFO_PTR_READ_BLOCK:                    info->read_block = fat_image_readblock; break;
		case IMGTOOLINFO_PTR_WRITE_BLOCK:                   info->write_block = fat_image_writeblock; break;
		case IMGTOOLINFO_PTR_GET_GEOMETRY:                  info->get_geometry = fat_image_get_geometry; break;

		default: fat_get_info(imgclass, state, info); break;
	}
}
