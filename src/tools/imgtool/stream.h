// license:BSD-3-Clause
// copyright-holders:Nathan Woods
/***************************************************************************

    stream.h

    Code for implementing Imgtool streams

***************************************************************************/

#ifndef STREAM_H
#define STREAM_H

#include "imgterrs.h"
#include "corefile.h"

<<<<<<< HEAD
struct imgtool_stream;

imgtool_stream *stream_open(const char *fname, int read_or_write);  /* similar params to mame_fopen */
imgtool_stream *stream_open_write_stream(int filesize);
imgtool_stream *stream_open_mem(void *buf, size_t sz);
void stream_close(imgtool_stream *stream);
core_file *stream_core_file(imgtool_stream *stream);
UINT32 stream_read(imgtool_stream *stream, void *buf, UINT32 sz);
UINT32 stream_write(imgtool_stream *stream, const void *buf, UINT32 sz);
UINT64 stream_size(imgtool_stream *stream);
int stream_seek(imgtool_stream *stream, INT64 pos, int where);
UINT64 stream_tell(imgtool_stream *stream);
void *stream_getptr(imgtool_stream *stream);
UINT32 stream_putc(imgtool_stream *stream, char c);
UINT32 stream_puts(imgtool_stream *stream, const char *s);
UINT32 stream_printf(imgtool_stream *stream, const char *fmt, ...) ATTR_PRINTF(2,3);

/* Transfers sz bytes from source to dest */
UINT64 stream_transfer(imgtool_stream *dest, imgtool_stream *source, UINT64 sz);
UINT64 stream_transfer_all(imgtool_stream *dest, imgtool_stream *source);

/* Fills sz bytes with b */
UINT64 stream_fill(imgtool_stream *f, unsigned char b, UINT64 sz);

/* Returns the CRC of a file */
int stream_crc(imgtool_stream *f, unsigned long *result);
int file_crc(const char *fname,  unsigned long *result);

/* Returns whether a stream is read only or not */
int stream_isreadonly(imgtool_stream *f);
=======
namespace imgtool
{
	class stream
	{
	public:
		typedef std::unique_ptr<stream> ptr;

		~stream();

		static imgtool::stream::ptr open(const std::string &filename, int read_or_write);  /* similar params to mame_fopen */
		static imgtool::stream::ptr open_write_stream(int filesize);
		static imgtool::stream::ptr open_mem(void *buf, size_t sz);

		util::core_file *core_file();
		uint32_t read(void *buf, uint32_t sz);
		uint32_t write(const void *buf, uint32_t sz);
		uint64_t size() const;
		int seek(int64_t pos, int where);
		uint64_t tell();
		void *getptr();
		uint32_t putc(char c);
		uint32_t puts(const char *s);
		uint32_t printf(const char *fmt, ...) ATTR_PRINTF(2, 3);

		// transfers sz bytes from source to dest
		static uint64_t transfer(imgtool::stream &dest, imgtool::stream &source, uint64_t sz);
		static uint64_t transfer_all(imgtool::stream &dest, imgtool::stream &source);

		// fills sz bytes with b
		uint64_t fill(unsigned char b, uint64_t sz);

		// returns the CRC of a file
		int crc(unsigned long *result);
		static int file_crc(const char *fname, unsigned long *result);

		// returns whether a stream is read only or not
		bool is_read_only();

	private:
		enum imgtype_t
		{
			IMG_FILE,
			IMG_MEM
		};

		imgtype_t       imgtype;
		bool            write_protect;
		std::uint64_t   position;
		std::uint64_t   filesize;

		util::core_file::ptr file;
		std::uint8_t *buffer;

		// ctors
		stream(bool wp);
		stream(bool wp, util::core_file::ptr &&f);
		stream(bool wp, std::size_t size);
		stream(bool wp, std::size_t size, void *buf);

		// private methods
		static stream::ptr open_zip(const std::string &zipname, const char *subname, int read_or_write);
	};
}


>>>>>>> upstream/master

#endif /* STREAM_H */
