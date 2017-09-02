// license:BSD-3-Clause
// copyright-holders:Nathan Woods
/****************************************************************************

    imghd.h

    Bridge between Imgtool and CHD hard disk images

****************************************************************************/

#ifndef IMGHD_H
#define IMGHD_H

#include "harddisk.h"

struct mess_hard_disk_file
{
<<<<<<< HEAD
	imgtool_stream *stream;
	hard_disk_file *hard_disk;
	chd_file *chd;
=======
	imgtool::stream *stream;
	hard_disk_file *hard_disk;
	chd_file chd;
>>>>>>> upstream/master
};


/* create a new hard disk */
<<<<<<< HEAD
imgtoolerr_t imghd_create(imgtool_stream *stream, UINT32 blocksize, UINT32 cylinders, UINT32 heads, UINT32 sectors, UINT32 seclen);

/* opens a hard disk given an Imgtool stream */
imgtoolerr_t imghd_open(imgtool_stream *stream, struct mess_hard_disk_file *hard_disk);
=======
imgtoolerr_t imghd_create(imgtool::stream &stream, uint32_t blocksize, uint32_t cylinders, uint32_t heads, uint32_t sectors, uint32_t seclen);

/* opens a hard disk given an Imgtool stream */
imgtoolerr_t imghd_open(imgtool::stream &stream, mess_hard_disk_file *hard_disk);
>>>>>>> upstream/master

/* close a hard disk */
void imghd_close(struct mess_hard_disk_file *disk);

/* reads data from a hard disk */
<<<<<<< HEAD
imgtoolerr_t imghd_read(struct mess_hard_disk_file *disk, UINT32 lbasector, void *buffer);

/* writes data to a hard disk */
imgtoolerr_t imghd_write(struct mess_hard_disk_file *disk, UINT32 lbasector, const void *buffer);
=======
imgtoolerr_t imghd_read(struct mess_hard_disk_file *disk, uint32_t lbasector, void *buffer);

/* writes data to a hard disk */
imgtoolerr_t imghd_write(struct mess_hard_disk_file *disk, uint32_t lbasector, const void *buffer);
>>>>>>> upstream/master

/* gets the header from a hard disk */
const hard_disk_info *imghd_get_header(struct mess_hard_disk_file *disk);

#endif /* IMGHD_H */
