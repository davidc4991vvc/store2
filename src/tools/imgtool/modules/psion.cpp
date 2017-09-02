// license:BSD-3-Clause
// copyright-holders:Sandro Ronco
/***************************************************************************

        Psion Organiser II Datapack

        08/18/2010 Sandro Ronco

        Known file types:
         0x00         invalid record
         0x01 - 0x7e  deleted record
         0x7f         invalid deleted record
         0x80         long record
         0x81         file name
         0x82         diary
         0x83         OPL/OB3 procedure
         0x84         RS232 setup
         0x85 - 0x8f  reserved
         0x90         MAIN Record
         0x91 - 0xfe  data records from files
         0xff         invalid record

****************************************************************************/

#include "imgtool.h"

#define MAXFILES 256

struct psion_file
{
	char filename[9];
<<<<<<< HEAD
	UINT8 type;
	UINT8 id;

	UINT16 name_rec;
	UINT16 data_rec;
=======
	uint8_t type;
	uint8_t id;

	uint16_t name_rec;
	uint16_t data_rec;
>>>>>>> upstream/master
};

struct psion_pack
{
<<<<<<< HEAD
	imgtool_stream *stream;

	UINT16 eop;
=======
	imgtool::stream *stream;

	uint16_t eop;
>>>>>>> upstream/master
	struct psion_file pack_index[MAXFILES];
};

struct psion_iter
{
<<<<<<< HEAD
	UINT16 index;
};

UINT16 head_checksum(UINT8* data)
{
	UINT16 checksum = 0;
=======
	uint16_t index;
};

static psion_pack *get_psion_pack(imgtool::image &image)
{
	return (psion_pack*)image.extra_bytes();
}

uint16_t head_checksum(uint8_t* data)
{
	uint16_t checksum = 0;
>>>>>>> upstream/master

	for (int i=0; i<6; i+=2)
		checksum += (data[i]<<8 | data[i+1]);

	return checksum;
}

<<<<<<< HEAD
UINT16 get_long_rec_size(imgtool_stream *stream)
{
	UINT8 size_h, size_l;

	stream_read(stream, &size_h, 1);
	stream_read(stream, &size_l, 1);
=======
uint16_t get_long_rec_size(imgtool::stream &stream)
{
	uint8_t size_h, size_l;

	stream.read(&size_h, 1);
	stream.read(&size_l, 1);
>>>>>>> upstream/master

	return (size_h<<8) | size_l;
}

<<<<<<< HEAD
UINT32 update_pack_index(psion_pack *pack)
{
	UINT8 data, type;
	UINT16 size;
	UINT16 index = 0;
=======
uint32_t update_pack_index(psion_pack *pack)
{
	uint8_t data, type;
	uint16_t size;
	uint16_t index = 0;
>>>>>>> upstream/master

	memset(pack->pack_index, 0, sizeof(psion_file) * MAXFILES);

	// start at the first record
<<<<<<< HEAD
	stream_seek(pack->stream, 0x10, SEEK_SET);

	do
	{
		stream_read(pack->stream, &data, 1);

		if(data == 0xff)
		{
			pack->eop = stream_tell(pack->stream) - 1;
			return TRUE;
=======
	pack->stream->seek(0x10, SEEK_SET);

	do
	{
		pack->stream->read(&data, 1);

		if(data == 0xff)
		{
			pack->eop = pack->stream->tell() - 1;
			return true;
>>>>>>> upstream/master
		}
		else if (data == 0x02)
		{
			// long record without name are ignored
<<<<<<< HEAD
			stream_read(pack->stream, &data, 1);
			size = get_long_rec_size(pack->stream);
			stream_seek(pack->stream, size, SEEK_CUR);
		}
		else
		{
			stream_read(pack->stream, &type, 1);
=======
			pack->stream->read(&data, 1);
			size = get_long_rec_size(*pack->stream);
			pack->stream->seek(size, SEEK_CUR);
		}
		else
		{
			pack->stream->read(&type, 1);
>>>>>>> upstream/master

			// deleted record are not listed
			if (type < 0x90 && (type & 0x80))
			{
				pack->pack_index[index].type = type;
<<<<<<< HEAD
				stream_read(pack->stream, &pack->pack_index[index].filename, 8);
				stream_read(pack->stream, &pack->pack_index[index].id, 1);
				pack->pack_index[index].name_rec = stream_tell(pack->stream) - 11;

				//check for data record
				stream_read(pack->stream, &data, 1);
				if (data == 0x02)
					pack->pack_index[index].data_rec = stream_tell(pack->stream) - 1;

				stream_seek(pack->stream, -1, SEEK_CUR);
=======
				pack->stream->read(&pack->pack_index[index].filename, 8);
				pack->stream->read(&pack->pack_index[index].id, 1);
				pack->pack_index[index].name_rec = pack->stream->tell() - 11;

				//check for data record
				pack->stream->read(&data, 1);
				if (data == 0x02)
					pack->pack_index[index].data_rec = pack->stream->tell() - 1;

				pack->stream->seek(-1, SEEK_CUR);
>>>>>>> upstream/master

				index++;
			}
			else
<<<<<<< HEAD
				stream_seek(pack->stream, data, SEEK_CUR);
		}

	} while (stream_size(pack->stream) > stream_tell(pack->stream));

	// corrupted image
	return FALSE;
}

int seek_next_record(imgtool_stream *stream, UINT8 id)
{
	UINT8 data, rec_id;
	UINT16 size;

	do
	{
		stream_read(stream, &data, 1);
=======
				pack->stream->seek(data, SEEK_CUR);
		}

	} while (pack->stream->size() > pack->stream->tell());

	// corrupted image
	return false;
}

int seek_next_record(imgtool::stream &stream, uint8_t id)
{
	uint8_t data, rec_id;
	uint16_t size;

	do
	{
		stream.read(&data, 1);
>>>>>>> upstream/master

		if(data == 0xff)
			break;

		if (data == 2)
		{
<<<<<<< HEAD
			stream_read(stream, &rec_id, 1);
=======
			stream.read(&rec_id, 1);
>>>>>>> upstream/master
			size = get_long_rec_size(stream);

		}
		else
		{
<<<<<<< HEAD
			stream_read(stream, &rec_id, 1);
			if (id == rec_id)
			{
				stream_seek(stream, -2, SEEK_CUR);
				return TRUE;
=======
			stream.read(&rec_id, 1);
			if (id == rec_id)
			{
				stream.seek(-2, SEEK_CUR);
				return true;
>>>>>>> upstream/master
			}
			size = data;
		}

		// next record
<<<<<<< HEAD
		stream_seek(stream, size, SEEK_CUR);

	} while (stream_size(stream) > stream_tell(stream));

	return FALSE;
=======
		stream.seek(size, SEEK_CUR);

	} while (stream.size() > stream.tell());

	return false;
>>>>>>> upstream/master
}

// if there are multiple files with the same name, only the first is found
int seek_file_name(psion_pack *pack, const char *filename)
{
<<<<<<< HEAD
	UINT16 index = 0;
=======
	uint16_t index = 0;
>>>>>>> upstream/master

	while (pack->pack_index[index].name_rec)
	{
		if (!strncmp(filename, pack->pack_index[index].filename, strlen(filename)))
			return index;
		index++;
	}

	// filename not found
	return -1;
}

<<<<<<< HEAD
UINT8 get_free_file_id(psion_pack *pack)
{
	for (UINT8 file_id=0x91; file_id<0xff; file_id++)
=======
uint8_t get_free_file_id(psion_pack *pack)
{
	for (uint8_t file_id=0x91; file_id<0xff; file_id++)
>>>>>>> upstream/master
	{
		int index = 0;

		while (pack->pack_index[index].id != file_id)
			if (pack->pack_index[index++].name_rec == 0)
				return file_id;
	}

	return 0xff;
}

<<<<<<< HEAD
void put_name_record(imgtool_stream *stream, const char* filename, UINT8 record_type, UINT8 record_id)
=======
static void put_name_record(imgtool::stream &stream, const char* filename, uint8_t record_type, uint8_t record_id)
>>>>>>> upstream/master
{
	char data[0x10];
	int i = 0;

	data[i++] = 0x09;
	data[i++] = record_type;

	// filename is 8 char long space filled
	for (int j=0; j<8; j++)
		if (j < strlen(filename))
			data[i++] = filename[j];
		else
			data[i++] = 0x20;

	data[i++] = record_id;

<<<<<<< HEAD
	stream_write(stream, data, i);
}

void update_opk_head(imgtool_stream *stream)
{
	UINT16 size = stream_size(stream) - 6;

	stream_seek(stream, 4, SEEK_SET);
	stream_putc(stream, (size>>8) & 0xff);
	stream_putc(stream, size & 0xff);
}

char *stream_getline(imgtool_stream *source, UINT16 max_len)
{
	UINT16 pos = 0;
=======
	stream.write(data, i);
}

static void update_opk_head(imgtool::stream &stream)
{
	uint16_t size = stream.size() - 6;

	stream.seek(4, SEEK_SET);
	stream.putc((size>>8) & 0xff);
	stream.putc(size & 0xff);
}

char *stream_getline(imgtool::stream &source, uint16_t max_len)
{
	uint16_t pos = 0;
>>>>>>> upstream/master
	char data;
	char *line = (char*)malloc(max_len);
	memset(line, 0, max_len);

<<<<<<< HEAD
	while (pos < max_len && stream_size(source) > stream_tell(source))
	{
		stream_read(source, &data, 1);
=======
	while (pos < max_len && source.size() > source.tell())
	{
		source.read(&data, 1);
>>>>>>> upstream/master

		switch(data)
		{
			case '\r':
<<<<<<< HEAD
				stream_read(source, &data, 1);
				if (data != '\n')
					stream_seek(source, -1, SEEK_CUR);
=======
				source.read(&data, 1);
				if (data != '\n')
					source.seek(-1, SEEK_CUR);
>>>>>>> upstream/master
			case '\n':
				return line;
			default:
				line[pos++] = data;
				break;
		}
	}

	if (pos)
		return line;

	free(line);
	return NULL;
}

<<<<<<< HEAD
UINT16 put_odb(imgtool_stream *instream, imgtool_stream *outstream, UINT8 file_id)
{
	char *line;
	UINT16 out_size = 0;

	// reset stream
	stream_seek(instream, 0, SEEK_SET);

	while ((line = stream_getline(instream, 256)))
	{
		UINT16 len = strlen(line);

		stream_putc(outstream, (UINT8)len);
		stream_putc(outstream, file_id);
		stream_write(outstream, line, len);
=======
uint16_t put_odb(imgtool::stream &instream, imgtool::stream &outstream, uint8_t file_id)
{
	char *line;
	uint16_t out_size = 0;

	// reset stream
	instream.seek(0, SEEK_SET);

	while ((line = stream_getline(instream, 256)))
	{
		uint16_t len = strlen(line);

		outstream.putc((uint8_t)len);
		outstream.putc(file_id);
		outstream.write(line, len);
>>>>>>> upstream/master

		out_size += (len + 1);

		free(line);
	}

	// end of pack
<<<<<<< HEAD
	stream_fill(outstream, 0xff, 2);
=======
	outstream.fill(0xff, 2);
>>>>>>> upstream/master

	return out_size + 4;
}

<<<<<<< HEAD
UINT16 put_ob3(imgtool_stream *instream, imgtool_stream *outstream)
{
	UINT16 size = stream_size(instream) - 6;
	dynamic_buffer buffer(size);

	stream_seek(instream, 6, SEEK_SET);
	stream_read(instream, &buffer[0], size);

	stream_write(outstream, &buffer[0], size);

	// end of pack
	stream_fill(outstream, 0xff, 2);
=======
uint16_t put_ob3(imgtool::stream &instream, imgtool::stream &outstream)
{
	uint16_t size = instream.size() - 6;
	std::vector<uint8_t> buffer(size);

	instream.seek(6, SEEK_SET);
	instream.read(&buffer[0], size);

	outstream.write(&buffer[0], size);

	// end of pack
	outstream.fill(0xff, 2);
>>>>>>> upstream/master

	return size;
}

<<<<<<< HEAD
UINT16 put_opl(imgtool_stream *instream, imgtool_stream *outstream)
{
	UINT16 out_size = 0;
	UINT32 rec_start = stream_tell(outstream);
	char *line;

	// reset stream
	stream_seek(instream, 0, SEEK_SET);

	stream_fill(outstream, 0x00, 4);
=======
uint16_t put_opl(imgtool::stream &instream, imgtool::stream &outstream)
{
	uint16_t out_size = 0;
	uint32_t rec_start = outstream.tell();
	char *line;

	// reset stream
	instream.seek(0, SEEK_SET);

	outstream.fill(0x00, 4);
>>>>>>> upstream/master

	// replace all eol with 0x00
	while ((line = stream_getline(instream, 256)))
	{
		// replace tab with space
		for (int i=0; i<strlen(line); i++)
			if (line[i] == '\t') line[i] = ' ';

<<<<<<< HEAD
		stream_write(outstream, line, strlen(line));
		stream_putc(outstream, 0x00);
=======
		outstream.write(line, strlen(line));
		outstream.putc(0x00);
>>>>>>> upstream/master
		out_size += strlen(line) + 1;
		free(line);
	}

	// end of pack
<<<<<<< HEAD
	stream_fill(outstream, 0xff, 2);

	// update the size in the head
	stream_seek(outstream, rec_start + 2, SEEK_SET);
	stream_putc(outstream, (out_size>>8) & 0xff);
	stream_putc(outstream, out_size & 0xff);
=======
	outstream.fill(0xff, 2);

	// update the size in the head
	outstream.seek(rec_start + 2, SEEK_SET);
	outstream.putc((out_size>>8) & 0xff);
	outstream.putc(out_size & 0xff);
>>>>>>> upstream/master

	return out_size + 4;
}

<<<<<<< HEAD
UINT16 get_odb(imgtool_stream *instream, imgtool_stream *outstream, UINT8 type, UINT8 file_id)
{
	UINT8 data, *buffer;
	UINT16 out_size = 0;
=======
uint16_t get_odb(imgtool::stream &instream, imgtool::stream &outstream, uint8_t type, uint8_t file_id)
{
	uint8_t data, *buffer;
	uint16_t out_size = 0;
>>>>>>> upstream/master

	if (file_id >= 0x90)
		while (seek_next_record(instream, file_id))
		{
<<<<<<< HEAD
			stream_read(instream, &data, 1);
			stream_seek(instream, 1, SEEK_CUR);
			buffer = (UINT8*)malloc(data);
			stream_read(instream, buffer, data);
			stream_write(outstream, buffer, data);
			stream_putc(outstream, '\r');
			stream_putc(outstream, '\n');
=======
			instream.read(&data, 1);
			instream.seek(1, SEEK_CUR);
			buffer = (uint8_t*)malloc(data);
			instream.read(buffer, data);
			outstream.write(buffer, data);
			outstream.putc('\r');
			outstream.putc('\n');
>>>>>>> upstream/master
			free (buffer);
			out_size += data;
		}

	return out_size;
}

<<<<<<< HEAD
UINT16 get_ob3(imgtool_stream *instream, imgtool_stream *outstream, UINT8 type, UINT8 file_id)
{
	UINT8 data, *buffer = NULL;
	UINT16 size = 0;
	static const char ob3_magic[3] = {'O', 'R', 'G'};

	stream_read(instream, &data, 1);

	if (data == 0x02)
	{
		stream_seek(instream, 1, SEEK_CUR);
		size = get_long_rec_size(instream);
		buffer = (UINT8*)malloc(size);
		stream_read(instream, buffer, size);
	}

	stream_write(outstream, ob3_magic, 3);
	stream_putc(outstream, (size>>8) & 0xff);
	stream_putc(outstream, size & 0xff);
	stream_putc(outstream, type | 0x80);

	if (buffer)
	{
		stream_write(outstream, buffer, size);
=======
uint16_t get_ob3(imgtool::stream &instream, imgtool::stream &outstream, uint8_t type, uint8_t file_id)
{
	uint8_t data, *buffer = NULL;
	uint16_t size = 0;
	static const char ob3_magic[3] = {'O', 'R', 'G'};

	instream.read(&data, 1);

	if (data == 0x02)
	{
		instream.seek(1, SEEK_CUR);
		size = get_long_rec_size(instream);
		buffer = (uint8_t*)malloc(size);
		instream.read(buffer, size);
	}

	outstream.write(ob3_magic, 3);
	outstream.putc((size>>8) & 0xff);
	outstream.putc(size & 0xff);
	outstream.putc(type | 0x80);

	if (buffer)
	{
		outstream.write(buffer, size);
>>>>>>> upstream/master
		free (buffer);
	}

	return size;
}

<<<<<<< HEAD
static imgtoolerr_t datapack_open( imgtool_image *image, imgtool_stream *stream)
{
	psion_pack *pack = (psion_pack*)imgtool_image_extra_bytes(image);
	char opk_magic[4];

	stream_read(stream, opk_magic, 4);
=======
static imgtoolerr_t datapack_open(imgtool::image &image, imgtool::stream::ptr &&stream)
{
	psion_pack *pack = get_psion_pack(image);
	char opk_magic[4];

	stream->read(opk_magic, 4);
>>>>>>> upstream/master

	if(strcmp(opk_magic, "OPK\0"))
		return IMGTOOLERR_UNEXPECTED;

<<<<<<< HEAD
	pack->stream = stream;

	if (update_pack_index(pack))
		return IMGTOOLERR_SUCCESS;
	else
		return IMGTOOLERR_CORRUPTIMAGE;
}

static imgtoolerr_t datapack_create( imgtool_image *image, imgtool_stream *stream, option_resolution *opts)
{
	psion_pack *pack = (psion_pack*)imgtool_image_extra_bytes(image);
	static const UINT8 opk_magic[4] = {'O', 'P', 'K', 0x00};
	UINT8 pack_head[8] = {0x40, 0x00, 0x59, 0x01, 0x01, 0x01, 0x00, 0x00};
	UINT16 checksum;

	pack_head[0] |= (option_resolution_lookup_int(opts, 'R')) ? 0x00 : 0x02;
	pack_head[0] |= (option_resolution_lookup_int(opts, 'P')) ? 0x04 : 0x00;
	pack_head[0] |= (option_resolution_lookup_int(opts, 'W')) ? 0x00 : 0x08;
	pack_head[0] |= (option_resolution_lookup_int(opts, 'B')) ? 0x00 : 0x10;
	pack_head[0] |= (option_resolution_lookup_int(opts, 'C')) ? 0x20 : 0x00;
	pack_head[1] = option_resolution_lookup_int(opts, 'S');

	checksum = head_checksum(pack_head);

	stream_write(stream, opk_magic, 4);
	stream_fill(stream, 0x00, 2);
	stream_write(stream, pack_head, 8);

	stream_putc(stream, (checksum>>8) & 0xff);
	stream_putc(stream, checksum & 0xff);

	put_name_record(stream, "MAIN", 0x81, 0x90);

	stream_fill(stream, 0xff, 2);

	update_opk_head(stream);

	pack->stream = stream;

	if (update_pack_index(pack))
		return IMGTOOLERR_SUCCESS;
	else
		return IMGTOOLERR_CORRUPTIMAGE;
}

static void datapack_close( imgtool_image *image)
{
	psion_pack *pack = (psion_pack*)imgtool_image_extra_bytes(image);

	stream_close( pack->stream );
}

static imgtoolerr_t datapack_begin_enum(imgtool_directory *enumeration, const char *path)
{
	psion_iter *iter = (psion_iter*)imgtool_directory_extrabytes(enumeration);
=======
	pack->stream = stream.get();

	if (update_pack_index(pack))
	{
		pack->stream = stream.release();
		return IMGTOOLERR_SUCCESS;
	}
	else
	{
		return IMGTOOLERR_CORRUPTIMAGE;
	}
}

static imgtoolerr_t datapack_create(imgtool::image &image, imgtool::stream::ptr &&stream, util::option_resolution *opts)
{
	psion_pack *pack = get_psion_pack(image);
	static const uint8_t opk_magic[4] = {'O', 'P', 'K', 0x00};
	uint8_t pack_head[8] = {0x40, 0x00, 0x59, 0x01, 0x01, 0x01, 0x00, 0x00};
	uint16_t checksum;

	pack_head[0] |= (opts->lookup_int('R')) ? 0x00 : 0x02;
	pack_head[0] |= (opts->lookup_int('P')) ? 0x04 : 0x00;
	pack_head[0] |= (opts->lookup_int('W')) ? 0x00 : 0x08;
	pack_head[0] |= (opts->lookup_int('B')) ? 0x00 : 0x10;
	pack_head[0] |= (opts->lookup_int('C')) ? 0x20 : 0x00;
	pack_head[1] = opts->lookup_int('S');

	checksum = head_checksum(pack_head);

	stream->write(opk_magic, 4);
	stream->fill(0x00, 2);
	stream->write(pack_head, 8);

	stream->putc((checksum>>8) & 0xff);
	stream->putc(checksum & 0xff);

	put_name_record(*stream, "MAIN", 0x81, 0x90);

	stream->fill(0xff, 2);

	update_opk_head(*stream);

	pack->stream = stream.get();

	if (update_pack_index(pack))
	{
		pack->stream = stream.release();
		return IMGTOOLERR_SUCCESS;
	}
	else
	{
		return IMGTOOLERR_CORRUPTIMAGE;
	}
}

static void datapack_close(imgtool::image &image)
{
	psion_pack *pack = get_psion_pack(image);

	delete pack->stream;
}

static imgtoolerr_t datapack_begin_enum(imgtool::directory &enumeration, const char *path)
{
	psion_iter *iter = (psion_iter*)enumeration.extra_bytes();
>>>>>>> upstream/master
	iter->index = 0;

	return IMGTOOLERR_SUCCESS;
}

<<<<<<< HEAD
static imgtoolerr_t datapack_next_enum(imgtool_directory *enumeration, imgtool_dirent *ent)
{
	imgtool_image *image = imgtool_directory_image(enumeration);
	psion_pack *pack = (psion_pack*)imgtool_image_extra_bytes(image);
	psion_iter *iter = (psion_iter*)imgtool_directory_extrabytes(enumeration);
	UINT8 data = 0;

	if (!pack->pack_index[iter->index].name_rec)
	{
		ent->eof = 1;
		return IMGTOOLERR_SUCCESS;
	}
	memcpy(ent->filename, pack->pack_index[iter->index].filename, 8);
	sprintf(ent->attr, "Type: %02x ID: %02x", pack->pack_index[iter->index].type, pack->pack_index[iter->index].id);

	if (pack->pack_index[iter->index].data_rec)
	{
		stream_seek(pack->stream, pack->pack_index[iter->index].data_rec + 2, SEEK_SET);
		ent->filesize = get_long_rec_size(pack->stream);
=======
static imgtoolerr_t datapack_next_enum(imgtool::directory &enumeration, imgtool_dirent &ent)
{
	imgtool::image &image(enumeration.image());
	psion_pack *pack = get_psion_pack(image);
	psion_iter *iter = (psion_iter*)enumeration.extra_bytes();
	uint8_t data = 0;

	if (!pack->pack_index[iter->index].name_rec)
	{
		ent.eof = 1;
		return IMGTOOLERR_SUCCESS;
	}
	memcpy(ent.filename, pack->pack_index[iter->index].filename, 8);
	sprintf(ent.attr, "Type: %02x ID: %02x", pack->pack_index[iter->index].type, pack->pack_index[iter->index].id);

	if (pack->pack_index[iter->index].data_rec)
	{
		pack->stream->seek(pack->pack_index[iter->index].data_rec + 2, SEEK_SET);
		ent.filesize = get_long_rec_size(*pack->stream);
>>>>>>> upstream/master
	}

	// seek all file's records
	if (pack->pack_index[iter->index].id >= 0x90)
	{
<<<<<<< HEAD
		stream_seek(pack->stream, 0x10, SEEK_SET);
		while (seek_next_record(pack->stream, pack->pack_index[iter->index].id))
		{
			stream_read(pack->stream, &data, 1);
			stream_seek(pack->stream, data + 1, SEEK_CUR);
			ent->filesize +=data;
=======
		pack->stream->seek(0x10, SEEK_SET);
		while (seek_next_record(*pack->stream, pack->pack_index[iter->index].id))
		{
			pack->stream->read(&data, 1);
			pack->stream->seek(data + 1, SEEK_CUR);
			ent.filesize +=data;
>>>>>>> upstream/master
		}
	}

	iter->index++;
	return IMGTOOLERR_SUCCESS;
}

<<<<<<< HEAD
static void datapack_close_enum( imgtool_directory *enumeration)
{
}

static imgtoolerr_t datapack_free_space( imgtool_partition *partition, UINT64 *size)
{
	imgtool_image *image = imgtool_partition_image( partition);
	psion_pack *pack = (psion_pack*)imgtool_image_extra_bytes(image);
	UINT32 pack_size = 0;

	stream_seek(pack->stream, 0x07, SEEK_SET);
	stream_read(pack->stream, &pack_size, 1);
=======
static imgtoolerr_t datapack_free_space(imgtool::partition &partition, uint64_t *size)
{
	imgtool::image &image(partition.image());
	psion_pack *pack = get_psion_pack(image);
	uint32_t pack_size = 0;

	pack->stream->seek(0x07, SEEK_SET);
	pack->stream->read(&pack_size, 1);
>>>>>>> upstream/master

	if (size)
		*size = (pack_size * 0x2000) - pack->eop;

	return IMGTOOLERR_SUCCESS;
}

<<<<<<< HEAD
static imgtoolerr_t datapack_read_file(imgtool_partition *partition, const char *filename, const char *fork, imgtool_stream *destf)
{
	imgtool_image *image = imgtool_partition_image(partition);
	psion_pack *pack = (psion_pack*)imgtool_image_extra_bytes(image);
=======
static imgtoolerr_t datapack_read_file(imgtool::partition &partition, const char *filename, const char *fork, imgtool::stream &destf)
{
	imgtool::image &image(partition.image());
	psion_pack *pack = get_psion_pack(image);
>>>>>>> upstream/master
	int index = seek_file_name(pack, filename);

	if (index >= 0)
	{
		if ((pack->pack_index[index].type & 0x7f) == 0x01)
		{
			// ODB files
<<<<<<< HEAD
			stream_seek(pack->stream, 0x10, SEEK_SET);
			get_odb(pack->stream, destf, pack->pack_index[index].type, pack->pack_index[index].id);
=======
			pack->stream->seek(0x10, SEEK_SET);
			get_odb(*pack->stream, destf, pack->pack_index[index].type, pack->pack_index[index].id);
>>>>>>> upstream/master
		}
		else if ((pack->pack_index[index].type & 0x7f) == 0x03)
		{
			// OB3/OPL files
<<<<<<< HEAD
			stream_seek(pack->stream, pack->pack_index[index].data_rec, SEEK_SET);
			get_ob3(pack->stream, destf, pack->pack_index[index].type, pack->pack_index[index].id);
=======
			pack->stream->seek(pack->pack_index[index].data_rec, SEEK_SET);
			get_ob3(*pack->stream, destf, pack->pack_index[index].type, pack->pack_index[index].id);
>>>>>>> upstream/master
		}
		else
		{
			// Other files
			return IMGTOOLERR_UNIMPLEMENTED;
		}

		return IMGTOOLERR_SUCCESS;
	}
	else
		return IMGTOOLERR_FILENOTFOUND;
}

<<<<<<< HEAD
static imgtoolerr_t datapack_write_file( imgtool_partition *partition, const char *filename, const char *fork, imgtool_stream *sourcef, option_resolution *opts)
{
	imgtool_image *image = imgtool_partition_image(partition);
	psion_pack *pack = (psion_pack*)imgtool_image_extra_bytes(image);
	static const UINT8 data_head[4] = {0x02, 0x80, 0x00, 0x00};
	UINT8 head[3];
	UINT16 size = 0;
	UINT8 type = option_resolution_lookup_int(opts, 'T');
	UINT8 file_id = option_resolution_lookup_int(opts, 'I');
=======
static imgtoolerr_t datapack_write_file(imgtool::partition &partition, const char *filename, const char *fork, imgtool::stream &sourcef, util::option_resolution *opts)
{
	imgtool::image &image(partition.image());
	psion_pack *pack = get_psion_pack(image);
	static const uint8_t data_head[4] = {0x02, 0x80, 0x00, 0x00};
	uint8_t head[3];
	uint16_t size = 0;
	uint8_t type = opts->lookup_int('T');
	uint8_t file_id = opts->lookup_int('I');
>>>>>>> upstream/master

	if (!pack->eop)
		return IMGTOOLERR_CORRUPTIMAGE;

	// if not file_id is specified get the first free (for ODB only)
	if (file_id == 0 && type == 3)
	{
		file_id = get_free_file_id(pack);

		if (file_id == 0xff)
			return IMGTOOLERR_NOSPACE;
	}

<<<<<<< HEAD
	stream_read(sourcef, head, 3);
	stream_seek(pack->stream, pack->eop, SEEK_SET);
=======
	sourcef.read(head, 3);
	pack->stream->seek(pack->eop, SEEK_SET);
>>>>>>> upstream/master

	if (type == 0)
		type = (!strncmp((char*)head, "ORG", 3)) ? 1 : 2;

	switch (type)
	{
		case 1:     //OB3 file
<<<<<<< HEAD
			put_name_record(pack->stream, filename, 0x83, file_id);
			stream_write(pack->stream, data_head, 4);
			size = put_ob3(sourcef, pack->stream);
			break;
		case 2:     //OPL file
			put_name_record(pack->stream, filename, 0x83, file_id);
			stream_write(pack->stream, data_head, 4);
			size = put_opl(sourcef, pack->stream);
			break;
		case 3:     //ODB file
			put_name_record(pack->stream, filename, 0x81, file_id);
			size = put_odb(sourcef, pack->stream, file_id);
=======
			put_name_record(*pack->stream, filename, 0x83, file_id);
			pack->stream->write(data_head, 4);
			size = put_ob3(sourcef, *pack->stream);
			break;
		case 2:     //OPL file
			put_name_record(*pack->stream, filename, 0x83, file_id);
			pack->stream->write(data_head, 4);
			size = put_opl(sourcef, *pack->stream);
			break;
		case 3:     //ODB file
			put_name_record(*pack->stream, filename, 0x81, file_id);
			size = put_odb(sourcef, *pack->stream, file_id);
>>>>>>> upstream/master
			break;
	}

	if (type != 3)
	{
		// update the OB3/OPL long record size
<<<<<<< HEAD
		stream_seek(pack->stream, pack->eop + 13, SEEK_SET);
		stream_putc(pack->stream, (size>>8) & 0xff);
		stream_putc(pack->stream, size & 0xff);
	}

	update_opk_head(pack->stream);
=======
		pack->stream->seek(pack->eop + 13, SEEK_SET);
		pack->stream->putc((size>>8) & 0xff);
		pack->stream->putc(size & 0xff);
	}

	update_opk_head(*pack->stream);
>>>>>>> upstream/master

	if (update_pack_index(pack))
		return IMGTOOLERR_SUCCESS;
	else
		return IMGTOOLERR_CORRUPTIMAGE;
}

<<<<<<< HEAD
static imgtoolerr_t datapack_delete_file( imgtool_partition *partition, const char *filename)
{
	imgtool_image *image = imgtool_partition_image(partition);
	psion_pack *pack = (psion_pack*)imgtool_image_extra_bytes(image);
=======
static imgtoolerr_t datapack_delete_file(imgtool::partition &partition, const char *filename)
{
	imgtool::image &image(partition.image());
	psion_pack *pack = get_psion_pack(image);
>>>>>>> upstream/master
	int index = seek_file_name(pack, filename);

	if (index >= 0)
	{
		// clear the bit 7 of the file type to mark the file as deleted
<<<<<<< HEAD
		stream_seek(pack->stream, pack->pack_index[index].name_rec + 1, SEEK_SET);
		stream_putc(pack->stream, pack->pack_index[index].type & 0x7f);
=======
		pack->stream->seek(pack->pack_index[index].name_rec + 1, SEEK_SET);
		pack->stream->putc(pack->pack_index[index].type & 0x7f);
>>>>>>> upstream/master

		if (update_pack_index(pack))
			return IMGTOOLERR_SUCCESS;
		else
			return IMGTOOLERR_CORRUPTIMAGE;
	}
	else
		return IMGTOOLERR_FILENOTFOUND;
}

<<<<<<< HEAD
static OPTION_GUIDE_START( psion_create_optguide )
=======
OPTION_GUIDE_START( psion_create_optguide )
>>>>>>> upstream/master
	OPTION_ENUM_START( 'S', "size", "datapack size" )
		OPTION_ENUM( 1, "8k", "8 kbyte" )
		OPTION_ENUM( 2, "16k", "16 kbyts" )
		OPTION_ENUM( 4, "32k", "32 kbyte" )
		OPTION_ENUM( 8, "64k", "64 kbyte" )
		OPTION_ENUM( 16, "128k", "128 kbyte" ) // only paged datapacks can have this size
	OPTION_ENUM_END
	OPTION_INT('R', "ram", "EPROM/RAM datapack" )
	OPTION_INT('P', "paged", "linear/paged datapack" )
	OPTION_INT('W', "protect", "write-protected datapack" )
	OPTION_INT('B', "boot", "bootable datapack" )
	OPTION_INT('C', "copy", "copyable datapack" )
OPTION_GUIDE_END

<<<<<<< HEAD
static OPTION_GUIDE_START( psion_write_optguide )
=======
OPTION_GUIDE_START( psion_write_optguide )
>>>>>>> upstream/master
	OPTION_ENUM_START( 'T', "type", "file type" )
		OPTION_ENUM( 1, "OB3", "OB3 files" )
		OPTION_ENUM( 2, "OPL", "OPL files" )
		OPTION_ENUM( 3, "ODB", "ODB or text files" )
	OPTION_ENUM_END
	OPTION_INT( 'I', "id", "File ID" )
OPTION_GUIDE_END

<<<<<<< HEAD
void psion_get_info( const imgtool_class *imgclass, UINT32 state, union imgtoolinfo *info)
=======
void psion_get_info( const imgtool_class *imgclass, uint32_t state, union imgtoolinfo *info)
>>>>>>> upstream/master
{
	switch (state)
	{
		// --- the following bits of info are returned as 64-bit signed integers ---
		case IMGTOOLINFO_INT_IMAGE_EXTRA_BYTES          : info->i = sizeof(psion_pack); break;
		case IMGTOOLINFO_INT_DIRECTORY_EXTRA_BYTES      : info->i = sizeof(psion_iter); break;

		// --- the following bits of info are returned as pointers to data or functions ---
		case IMGTOOLINFO_PTR_OPEN        : info->open        = datapack_open; break;
		case IMGTOOLINFO_PTR_CREATE      : info->create      = datapack_create; break;
		case IMGTOOLINFO_PTR_CLOSE       : info->close       = datapack_close; break;
		case IMGTOOLINFO_PTR_BEGIN_ENUM  : info->begin_enum  = datapack_begin_enum; break;
		case IMGTOOLINFO_PTR_NEXT_ENUM   : info->next_enum   = datapack_next_enum; break;
<<<<<<< HEAD
		case IMGTOOLINFO_PTR_CLOSE_ENUM  : info->close_enum  = datapack_close_enum; break;
=======
>>>>>>> upstream/master
		case IMGTOOLINFO_PTR_FREE_SPACE  : info->free_space  = datapack_free_space; break;
		case IMGTOOLINFO_PTR_READ_FILE   : info->read_file   = datapack_read_file; break;
		case IMGTOOLINFO_PTR_WRITE_FILE  : info->write_file  = datapack_write_file; break;
		case IMGTOOLINFO_PTR_DELETE_FILE : info->delete_file = datapack_delete_file; break;
<<<<<<< HEAD
		case IMGTOOLINFO_PTR_CREATEIMAGE_OPTGUIDE : info->createimage_optguide = psion_create_optguide; break;
		case IMGTOOLINFO_PTR_WRITEFILE_OPTGUIDE : info->createimage_optguide = psion_write_optguide; break;
=======
		case IMGTOOLINFO_PTR_CREATEIMAGE_OPTGUIDE : info->createimage_optguide = &psion_create_optguide; break;
		case IMGTOOLINFO_PTR_WRITEFILE_OPTGUIDE : info->createimage_optguide = &psion_write_optguide; break;
>>>>>>> upstream/master

		// --- the following bits of info are returned as NULL-terminated strings ---
		case IMGTOOLINFO_STR_NAME            : strcpy( info->s = imgtool_temp_str(), "psionpack"); break;
		case IMGTOOLINFO_STR_DESCRIPTION     : strcpy( info->s = imgtool_temp_str(), "Psion Organiser II Datapack"); break;
		case IMGTOOLINFO_STR_FILE            : strcpy( info->s = imgtool_temp_str(), __FILE__); break;
		case IMGTOOLINFO_STR_FILE_EXTENSIONS : strcpy( info->s = imgtool_temp_str(), "opk"); break;
		case IMGTOOLINFO_STR_CREATEIMAGE_OPTSPEC : strcpy( info->s = imgtool_temp_str(), "S1/2/[4]/8/16;R[0]/1;P[0]/1;W0/[1];B[0]/1;C0/[1]"); break;
		case IMGTOOLINFO_STR_WRITEFILE_OPTSPEC : strcpy( info->s = imgtool_temp_str(), "T[1]/2/3;I[0]/145-255"); break;
	}
}
