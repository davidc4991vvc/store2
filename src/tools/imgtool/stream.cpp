// license:BSD-3-Clause
// copyright-holders:Nathan Woods
/***************************************************************************

<<<<<<< HEAD
    stream.c
=======
    stream.cpp
>>>>>>> upstream/master

    Code for implementing Imgtool streams

***************************************************************************/

#include <stdio.h>
#include <string.h>
#include <zlib.h>

#include "unzip.h"
#include "osdcore.h"
#include "imgtool.h"

<<<<<<< HEAD
enum imgtype_t
{
	IMG_FILE,
	IMG_MEM
};

struct imgtool_stream
{
	imgtype_t imgtype;
	int write_protect;
	const char *name; // needed for clear
	UINT64 position;
	UINT64 filesize;

	union
	{
		core_file *file;
		UINT8 *buffer;
	} u;
};



static imgtool_stream *stream_open_zip(const char *zipname, const char *subname, int read_or_write)
{
	imgtool_stream *imgfile = NULL;
//  zip_error ziperr;
	zip_file *z = NULL;
	const zip_file_header *zipent;
	FILE *f;

	if (read_or_write)
		goto error;

	/* check to see if the file exists */
	f = fopen(zipname, "r");
	if (!f)
		goto error;
	fclose(f);

	imgfile = (imgtool_stream *)malloc(sizeof(imgtool_stream));
	if (!imgfile)
		goto error;

	memset(imgfile, 0, sizeof(*imgfile));
	imgfile->imgtype = IMG_MEM;
	imgfile->write_protect = 1;
	imgfile->position = 0;

//  ziperr =
	zip_file_open(zipname, &z);
	if (!z)
		goto error;

	zipent = zip_file_first_file(z);
	while(zipent && subname && strcmp(subname, zipent->filename))
		zipent = zip_file_next_file(z);
	if (!zipent)
		goto error;

	imgfile->filesize = zipent->uncompressed_length;
	imgfile->u.buffer = (UINT8*)malloc(zipent->uncompressed_length);
	if (!imgfile->u.buffer)
		goto error;

	if (zip_file_decompress(z, imgfile->u.buffer, zipent->uncompressed_length))
		goto error;

	zip_file_close(z);
	return imgfile;

error:
	if (z)
		zip_file_close(z);
	if (imgfile)
	{
		if (imgfile->u.buffer)
			free(imgfile->u.buffer);
		free(imgfile);
	}
	return NULL;
=======

//-------------------------------------------------
//  ctor
//-------------------------------------------------

imgtool::stream::stream(bool wp)
	: imgtype(IMG_FILE)
	, write_protect(wp)
	, position(0)
	, filesize(0)
	, file()
	, buffer(nullptr)
{
}


//-------------------------------------------------
//  ctor
//-------------------------------------------------

imgtool::stream::stream(bool wp, util::core_file::ptr &&f)
	: imgtype(IMG_FILE)
	, write_protect(wp)
	, position(0)
	, filesize(f->size())
	, file(std::move(f))
	, buffer(nullptr)
{
}


//-------------------------------------------------
//  ctor
//-------------------------------------------------

imgtool::stream::stream(bool wp, std::size_t size)
	: imgtype(IMG_MEM)
	, write_protect(wp)
	, position(0)
	, filesize(size)
	, file()
	, buffer(reinterpret_cast<std::uint8_t *>(malloc(size)))
{
}


//-------------------------------------------------
//  ctor
//-------------------------------------------------

imgtool::stream::stream(bool wp, std::size_t size, void *buf)
	: imgtype(IMG_MEM)
	, write_protect(wp)
	, position(0)
	, filesize(size)
	, file()
	, buffer(reinterpret_cast<std::uint8_t *>(buf))
{
}


//-------------------------------------------------
//  dtor
//-------------------------------------------------

imgtool::stream::~stream()
{
	if (buffer)
		free(buffer);
}


//-------------------------------------------------
//  open_zip
//-------------------------------------------------

imgtool::stream::ptr imgtool::stream::open_zip(const std::string &zipname, const char *subname, int read_or_write)
{
	if (read_or_write)
		return imgtool::stream::ptr();

	/* check to see if the file exists */
	FILE *f = fopen(zipname.c_str(), "r");
	if (!f)
		return imgtool::stream::ptr();
	fclose(f);

	imgtool::stream::ptr imgfile(new imgtool::stream(true));

	imgfile->imgtype = IMG_MEM;

	util::archive_file::ptr z;
	util::archive_file::open_zip(zipname, z);
	if (!z)
		return imgtool::stream::ptr();

	int zipent = z->first_file();
	while ((zipent >= 0) && subname && strcmp(subname, z->current_name().c_str()))
		zipent = z->next_file();
	if (zipent < 0)
		return imgtool::stream::ptr();

	imgfile->filesize = z->current_uncompressed_length();
	imgfile->buffer = reinterpret_cast<std::uint8_t *>(malloc(z->current_uncompressed_length()));
	if (!imgfile->buffer)
		return imgtool::stream::ptr();

	if (z->decompress(imgfile->buffer, z->current_uncompressed_length()) != util::archive_file::error::NONE)
		return imgtool::stream::ptr();

	return imgfile;
>>>>>>> upstream/master
}



<<<<<<< HEAD
imgtool_stream *stream_open(const char *fname, int read_or_write)
{
	file_error filerr;
	const char *ext;
	imgtool_stream *imgfile = NULL;
	static const UINT32 write_modes[] =
=======
//-------------------------------------------------
//  open
//-------------------------------------------------

imgtool::stream::ptr imgtool::stream::open(const std::string &filename, int read_or_write)
{
	static const uint32_t write_modes[] =
>>>>>>> upstream/master
	{
		OPEN_FLAG_READ,
		OPEN_FLAG_WRITE | OPEN_FLAG_CREATE,
		OPEN_FLAG_READ | OPEN_FLAG_WRITE,
		OPEN_FLAG_READ | OPEN_FLAG_WRITE | OPEN_FLAG_CREATE
	};
<<<<<<< HEAD
	core_file *f = NULL;
	char *buf = NULL;
	int len, i;
	imgtool_stream *s = NULL;
	char c;

	/* maybe we are just a ZIP? */
	ext = strrchr(fname, '.');
	if (ext && !core_stricmp(ext, ".zip"))
		return stream_open_zip(fname, NULL, read_or_write);

	filerr = core_fopen(fname, write_modes[read_or_write], &f);
	if (filerr != FILERR_NONE)
	{
		if (!read_or_write)
		{
			len = strlen(fname);

			/* can't open the file; try opening ZIP files with other names */
			buf = (char*)malloc(len + 1);
			if (!buf)
				goto error;
			strcpy(buf, fname);

			for(i = len-1; !s && (i >= 0); i--)
=======
	imgtool::stream::ptr s;
	char c;

	// maybe we are just a ZIP?
	std::string ext = core_filename_extract_extension(filename);
	if (!core_stricmp(ext.c_str(), ".zip"))
		return open_zip(filename, nullptr, read_or_write);

	util::core_file::ptr f = nullptr;
	auto const filerr = util::core_file::open(filename, write_modes[read_or_write], f);
	if (filerr != osd_file::error::NONE)
	{
		if (!read_or_write)
		{
			int const len = filename.size();

			/* can't open the file; try opening ZIP files with other names */
			std::vector<char> buf(len + 1);
			strcpy(&buf[0], filename.c_str());

			for (int i = len-1; !s && (i >= 0); i--)
>>>>>>> upstream/master
			{
				if ((buf[i] == '\\') || (buf[i] == '/'))
				{
					c = buf[i];
					buf[i] = '\0';
<<<<<<< HEAD
					s = stream_open_zip(buf, buf + i + 1, read_or_write);
					buf[i] = c;
				}
			}
			free(buf);
			buf = NULL;
=======
					s = open_zip(&buf[0], &buf[i + 1], read_or_write);
					buf[i] = c;
				}
			}
>>>>>>> upstream/master

			if (s)
				return s;
		}

		/* ah well, it was worth a shot */
<<<<<<< HEAD
		goto error;
	}

	imgfile = (imgtool_stream *)malloc(sizeof(imgtool_stream));
	if (!imgfile)
		goto error;

	/* Normal file */
	memset(imgfile, 0, sizeof(*imgfile));
	imgfile->imgtype = IMG_FILE;
	imgfile->position = 0;
	imgfile->filesize = core_fsize(f);
	imgfile->write_protect = read_or_write ? 0 : 1;
	imgfile->u.file = f;
	imgfile->name = fname;
	return imgfile;

error:
	if (imgfile != NULL)
		free((void *) imgfile);
	if (f != NULL)
		core_fclose(f);
	if (buf)
		free(buf);
	return (imgtool_stream *) NULL;
}



imgtool_stream *stream_open_write_stream(int size)
{
	imgtool_stream *imgfile;

	imgfile = (imgtool_stream *)malloc(sizeof(imgtool_stream));
	if (!imgfile)
		return NULL;

	imgfile->imgtype = IMG_MEM;
	imgfile->write_protect = 0;
	imgfile->position = 0;
	imgfile->filesize = size;
	imgfile->u.buffer = (UINT8*)malloc(size);

	if (!imgfile->u.buffer)
	{
		free(imgfile);
		return NULL;
	}

=======
		return imgtool::stream::ptr();
	}

	imgtool::stream::ptr imgfile(new imgtool::stream(read_or_write ? false : true, std::move(f)));

	// normal file
>>>>>>> upstream/master
	return imgfile;
}


<<<<<<< HEAD

imgtool_stream *stream_open_mem(void *buf, size_t sz)
{
	imgtool_stream *imgfile;

	imgfile = (imgtool_stream *)malloc(sizeof(imgtool_stream));
	if (!imgfile)
		return NULL;

	memset(imgfile, 0, sizeof(*imgfile));
	imgfile->imgtype = IMG_MEM;
	imgfile->position = 0;
	imgfile->write_protect = 0;

	imgfile->filesize = sz;
	imgfile->u.buffer = (UINT8*)buf;
=======
//-------------------------------------------------
//  open_write_stream
//-------------------------------------------------

imgtool::stream::ptr imgtool::stream::open_write_stream(int size)
{
	imgtool::stream::ptr imgfile(new imgtool::stream(false, size));
	if (!imgfile->buffer)
		return imgtool::stream::ptr();

>>>>>>> upstream/master
	return imgfile;
}


<<<<<<< HEAD

void stream_close(imgtool_stream *s)
{
	assert(s != NULL);

	switch(s->imgtype)
	{
		case IMG_FILE:
			if (s->u.file != NULL)
			{
				core_fclose(s->u.file);
				s->u.file = NULL;
			}
			break;

		case IMG_MEM:
			if (s->u.buffer != NULL)
			{
				free(s->u.buffer);
				s->u.buffer = NULL;
			}
			break;

		default:
			assert(0);
			break;
	}
	free((void *) s);
}



core_file *stream_core_file(imgtool_stream *stream)
{
	return (stream->imgtype == IMG_FILE) ? stream->u.file : NULL;
}



UINT32 stream_read(imgtool_stream *stream, void *buf, UINT32 sz)
{
	UINT32 result = 0;

	switch(stream->imgtype)
	{
		case IMG_FILE:
			assert(sz == (UINT32) sz);
			core_fseek(stream->u.file, stream->position, SEEK_SET);
			result = core_fread(stream->u.file, buf, (UINT32) sz);
=======
//-------------------------------------------------
//  open_mem
//-------------------------------------------------

imgtool::stream::ptr imgtool::stream::open_mem(void *buf, size_t sz)
{
	imgtool::stream::ptr imgfile(new imgtool::stream(false, sz, buf));

	return imgfile;
}


//-------------------------------------------------
//  core_file
//-------------------------------------------------

util::core_file *imgtool::stream::core_file()
{
	return (imgtype == IMG_FILE) ? file.get() : nullptr;
}


//-------------------------------------------------
//  read
//-------------------------------------------------

uint32_t imgtool::stream::read(void *buf, uint32_t sz)
{
	uint32_t result = 0;

	switch(imgtype)
	{
		case IMG_FILE:
			assert(sz == (uint32_t) sz);
			file->seek(position, SEEK_SET);
			result = file->read(buf, (uint32_t) sz);
>>>>>>> upstream/master
			break;

		case IMG_MEM:
			/* do we have to limit sz? */
<<<<<<< HEAD
			if (sz > (stream->filesize - stream->position))
				sz = (UINT32) (stream->filesize - stream->position);

			memcpy(buf, stream->u.buffer + stream->position, sz);
=======
			if (sz > (filesize - position))
				sz = (uint32_t) (filesize - position);

			memcpy(buf, buffer + position, sz);
>>>>>>> upstream/master
			result = sz;
			break;

		default:
			assert(0);
			break;
	}
<<<<<<< HEAD
	stream->position += result;
=======
	position += result;
>>>>>>> upstream/master
	return result;
}


<<<<<<< HEAD

UINT32 stream_write(imgtool_stream *s, const void *buf, UINT32 sz)
{
	void *new_buffer;
	UINT32 result = 0;

	switch(s->imgtype)
	{
		case IMG_MEM:
			if (!s->write_protect)
			{
				/* do we have to expand the buffer? */
				if (s->filesize < s->position + sz)
				{
					/* try to expand the buffer */
					if (s->u.buffer) free(s->u.buffer);
					new_buffer = malloc(s->position + sz);
					if (new_buffer)
					{
						s->u.buffer = (UINT8*)new_buffer;
						s->filesize = s->position + sz;
=======
//-------------------------------------------------
//  write
//-------------------------------------------------

uint32_t imgtool::stream::write(const void *buf, uint32_t sz)
{
	void *new_buffer;
	uint32_t result = 0;

	switch(imgtype)
	{
		case IMG_MEM:
			if (!write_protect)
			{
				/* do we have to expand the buffer? */
				if (filesize < position + sz)
				{
					/* try to expand the buffer */
					new_buffer = realloc(buffer , position + sz);
					if (new_buffer)
					{
						buffer = (uint8_t*)new_buffer;
						filesize = position + sz;
>>>>>>> upstream/master
					}
				}

				/* do we have to limit sz? */
<<<<<<< HEAD
				if (sz > (s->filesize - s->position))
					sz = (UINT32) (s->filesize - s->position);

				memcpy(s->u.buffer + s->position, buf, sz);
=======
				if (sz > (filesize - position))
					sz = (uint32_t) (filesize - position);

				memcpy(buffer + position, buf, sz);
>>>>>>> upstream/master
				result = sz;
			}
			break;

		case IMG_FILE:
<<<<<<< HEAD
			core_fseek(s->u.file, s->position, SEEK_SET);
			result = core_fwrite(s->u.file, buf, sz);
=======
			file->seek(position, SEEK_SET);
			result = file->write(buf, sz);
>>>>>>> upstream/master
			break;

		default:
			assert(0);
			break;
	}

	/* advance the file pointer */
<<<<<<< HEAD
	s->position += result;

	/* did we grow the file */
	if (s->position > s->filesize)
		s->filesize = s->position;
=======
	position += result;

	/* did we grow the file */
	if (position > filesize)
		filesize = position;
>>>>>>> upstream/master
	return result;
}


<<<<<<< HEAD

UINT64 stream_size(imgtool_stream *s)
{
	return s->filesize;
}



void *stream_getptr(imgtool_stream *f)
{
	void *ptr;

	switch(f->imgtype)
	{
		case IMG_MEM:
			ptr = f->u.buffer;
			break;

		default:
			ptr = NULL;
=======
//-------------------------------------------------
//  size
//-------------------------------------------------

uint64_t imgtool::stream::size() const
{
	return filesize;
}


//-------------------------------------------------
//  getptr
//-------------------------------------------------

void *imgtool::stream::getptr()
{
	void *ptr;

	switch(imgtype)
	{
		case IMG_MEM:
			ptr = buffer;
			break;

		default:
			ptr = nullptr;
>>>>>>> upstream/master
			break;
	}
	return ptr;
}


<<<<<<< HEAD

int stream_seek(imgtool_stream *s, INT64 pos, int where)
{
	UINT64 size;

	size = stream_size(s);

	switch(where)
	{
		case SEEK_CUR:
			pos += s->position;
			break;
		case SEEK_END:
			pos += size;
=======
//-------------------------------------------------
//  seek
//-------------------------------------------------

int imgtool::stream::seek(int64_t pos, int where)
{
	switch(where)
	{
		case SEEK_CUR:
			pos += position;
			break;
		case SEEK_END:
			pos += size();
>>>>>>> upstream/master
			break;
	}

	if (pos < 0)
<<<<<<< HEAD
		s->position = 0;
	else
		s->position = MIN(size, pos);

	if (s->position < pos)
		stream_fill(s, '\0', pos - s->position);
=======
		position = 0;
	else
		position = std::min(size(), uint64_t(pos));

	if (position < pos)
		fill('\0', pos - position);
>>>>>>> upstream/master

	return 0;
}


<<<<<<< HEAD

UINT64 stream_tell(imgtool_stream *s)
{
	return s->position;
}



UINT64 stream_transfer(imgtool_stream *dest, imgtool_stream *source, UINT64 sz)
{
	UINT64 result = 0;
	UINT64 readsz;
	char buf[1024];

	while(sz && (readsz = stream_read(source, buf, MIN(sz, sizeof(buf)))))
	{
		stream_write(dest, buf, readsz);
=======
//-------------------------------------------------
//  tell
//-------------------------------------------------

uint64_t imgtool::stream::tell()
{
	return position;
}


//-------------------------------------------------
//  transfer
//-------------------------------------------------

uint64_t imgtool::stream::transfer(imgtool::stream &dest, imgtool::stream &source, uint64_t sz)
{
	uint64_t result = 0;
	uint64_t readsz;
	char buf[1024];

	while(sz && (readsz = source.read(buf, std::min(sz, uint64_t(sizeof(buf))))))
	{
		dest.write(buf, readsz);
>>>>>>> upstream/master
		sz -= readsz;
		result += readsz;
	}
	return result;
}


<<<<<<< HEAD

UINT64 stream_transfer_all(imgtool_stream *dest, imgtool_stream *source)
{
	return stream_transfer(dest, source, stream_size(source));
}



int stream_crc(imgtool_stream *s, unsigned long *result)
=======
//-------------------------------------------------
//  transfer_all
//-------------------------------------------------

uint64_t imgtool::stream::transfer_all(imgtool::stream &dest, imgtool::stream &source)
{
	return transfer(dest, source, source.size());
}


//-------------------------------------------------
//  crc
//-------------------------------------------------

int imgtool::stream::crc(unsigned long *result)
>>>>>>> upstream/master
{
	size_t sz;
	void *ptr;

<<<<<<< HEAD
	switch(s->imgtype)
	{
		case IMG_MEM:
			*result = crc32(0, (unsigned char *) s->u.buffer, (size_t) s->filesize);
			break;

		default:
			sz = stream_size(s);
			ptr = malloc(sz);
			if (!ptr)
				return IMGTOOLERR_OUTOFMEMORY;
			stream_seek(s, 0, SEEK_SET);
			if (stream_read(s, ptr, sz) != sz)
=======
	switch(imgtype)
	{
		case IMG_MEM:
			*result = crc32(0, (unsigned char *) buffer, (size_t) filesize);
			break;

		default:
			sz = size();
			ptr = malloc(sz);
			if (!ptr)
				return IMGTOOLERR_OUTOFMEMORY;
			seek(0, SEEK_SET);
			if (read(ptr, sz) != sz)
>>>>>>> upstream/master
			{
				free(ptr);
				return IMGTOOLERR_READERROR;
			}
			*result = crc32(0, (const Bytef*)ptr, sz);
			free(ptr);
			break;
	}
	return 0;
}


<<<<<<< HEAD

int file_crc(const char *fname,  unsigned long *result)
{
	int err;
	imgtool_stream *f;

	f = stream_open(fname, OSD_FOPEN_READ);
	if (!f)
		return IMGTOOLERR_FILENOTFOUND;

	err = stream_crc(f, result);
	stream_close(f);
=======
//-------------------------------------------------
//  file_crc
//-------------------------------------------------

int imgtool::stream::file_crc(const char *fname, unsigned long *result)
{
	int err;
	imgtool::stream::ptr f;

	f = imgtool::stream::open(fname, OSD_FOPEN_READ);
	if (!f)
		return IMGTOOLERR_FILENOTFOUND;

	err = f->crc(result);
>>>>>>> upstream/master
	return err;
}


<<<<<<< HEAD

UINT64 stream_fill(imgtool_stream *f, unsigned char b, UINT64 sz)
{
	UINT64 outsz;
	char buf[1024];

	outsz = 0;
	memset(buf, b, MIN(sz, sizeof(buf)));

	while(sz)
	{
		outsz += stream_write(f, buf, MIN(sz, sizeof(buf)));
		sz -= MIN(sz, sizeof(buf));
=======
//-------------------------------------------------
//  fill
//-------------------------------------------------

uint64_t imgtool::stream::fill(unsigned char b, uint64_t sz)
{
	uint64_t outsz;
	char buf[1024];

	outsz = 0;
	memset(buf, b, (std::min<uint64_t>)(sz, sizeof(buf)));

	while (sz)
	{
		outsz += write(buf, (std::min<uint64_t>)(sz, sizeof(buf)));
		sz -= (std::min<uint64_t>)(sz, sizeof(buf));
>>>>>>> upstream/master
	}
	return outsz;
}


<<<<<<< HEAD

int stream_isreadonly(imgtool_stream *s)
{
	return s->write_protect;
}



UINT32 stream_putc(imgtool_stream *stream, char c)
{
	return stream_write(stream, &c, 1);
}



UINT32 stream_puts(imgtool_stream *stream, const char *s)
{
	return stream_write(stream, s, strlen(s));
}



UINT32 stream_printf(imgtool_stream *stream, const char *fmt, ...)
=======
//-------------------------------------------------
//  is_read_only
//-------------------------------------------------

bool imgtool::stream::is_read_only()
{
	return write_protect;
}


//-------------------------------------------------
//  putc
//-------------------------------------------------

uint32_t imgtool::stream::putc(char c)
{
	return write(&c, 1);
}


//-------------------------------------------------
//  puts
//-------------------------------------------------

uint32_t imgtool::stream::puts(const char *s)
{
	return write(s, strlen(s));
}


//-------------------------------------------------
//  printf
//-------------------------------------------------

uint32_t imgtool::stream::printf(const char *fmt, ...)
>>>>>>> upstream/master
{
	va_list va;
	char buf[256];

	va_start(va, fmt);
	vsprintf(buf, fmt, va);
	va_end(va);

<<<<<<< HEAD
	return stream_puts(stream, buf);
=======
	return puts(buf);
>>>>>>> upstream/master
}
