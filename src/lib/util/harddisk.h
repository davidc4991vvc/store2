// license:BSD-3-Clause
// copyright-holders:Aaron Giles
/***************************************************************************

    harddisk.h

    Generic MAME hard disk implementation, with differencing files

***************************************************************************/

#pragma once

#ifndef __HARDDISK_H__
#define __HARDDISK_H__

#include "osdcore.h"
#include "chd.h"


/***************************************************************************
    TYPE DEFINITIONS
***************************************************************************/

struct hard_disk_file;

struct hard_disk_info
{
<<<<<<< HEAD
	UINT32          cylinders;
	UINT32          heads;
	UINT32          sectors;
	UINT32          sectorbytes;
=======
	uint32_t          cylinders;
	uint32_t          heads;
	uint32_t          sectors;
	uint32_t          sectorbytes;
>>>>>>> upstream/master
};



/***************************************************************************
    FUNCTION PROTOTYPES
***************************************************************************/

hard_disk_file *hard_disk_open(chd_file *chd);
void hard_disk_close(hard_disk_file *file);

chd_file *hard_disk_get_chd(hard_disk_file *file);
hard_disk_info *hard_disk_get_info(hard_disk_file *file);

<<<<<<< HEAD
UINT32 hard_disk_read(hard_disk_file *file, UINT32 lbasector, void *buffer);
UINT32 hard_disk_write(hard_disk_file *file, UINT32 lbasector, const void *buffer);
=======
uint32_t hard_disk_read(hard_disk_file *file, uint32_t lbasector, void *buffer);
uint32_t hard_disk_write(hard_disk_file *file, uint32_t lbasector, const void *buffer);
>>>>>>> upstream/master

#endif  /* __HARDDISK_H__ */
