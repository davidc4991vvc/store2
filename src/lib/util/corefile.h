// license:BSD-3-Clause
<<<<<<< HEAD
// copyright-holders:Aaron Giles
=======
// copyright-holders:Aaron Giles, Vas Crabb
>>>>>>> upstream/master
/***************************************************************************

    corefile.h

    Core file I/O interface functions and definitions.

***************************************************************************/

#pragma once

<<<<<<< HEAD
#ifndef __COREFILE_H__
#define __COREFILE_H__

#include <stdarg.h>
#include "corestr.h"
#include <string>
#include "coretmpl.h"



=======
#ifndef MAME_LIB_UTIL_COREFILE_H
#define MAME_LIB_UTIL_COREFILE_H

#include "corestr.h"
#include "coretmpl.h"
#include "strformat.h"

#include <cstdint>
#include <memory>
#include <string>


namespace util {
>>>>>>> upstream/master
/***************************************************************************
    ADDITIONAL OPEN FLAGS
***************************************************************************/

#define OPEN_FLAG_NO_BOM        0x0100      /* don't output BOM */

#define FCOMPRESS_NONE          0           /* no compression */
#define FCOMPRESS_MIN           1           /* minimal compression */
#define FCOMPRESS_MEDIUM        6           /* standard compression */
#define FCOMPRESS_MAX           9           /* maximum compression */


<<<<<<< HEAD

=======
>>>>>>> upstream/master
/***************************************************************************
    TYPE DEFINITIONS
***************************************************************************/

<<<<<<< HEAD
struct core_file;



/***************************************************************************
    FUNCTION PROTOTYPES
***************************************************************************/


/* ----- file open/close ----- */

/* open a file with the specified filename */
file_error core_fopen(const char *filename, UINT32 openflags, core_file **file);

/* open a RAM-based "file" using the given data and length (read-only) */
file_error core_fopen_ram(const void *data, size_t length, UINT32 openflags, core_file **file);

/* open a RAM-based "file" using the given data and length (read-only), copying the data */
file_error core_fopen_ram_copy(const void *data, size_t length, UINT32 openflags, core_file **file);

/* close an open file */
void core_fclose(core_file *file);

/* enable/disable streaming file compression via zlib; level is 0 to disable compression, or up to 9 for max compression */
file_error core_fcompress(core_file *file, int level);



/* ----- file positioning ----- */

/* adjust the file pointer within the file */
int core_fseek(core_file *file, INT64 offset, int whence);

/* return the current file pointer */
UINT64 core_ftell(core_file *file);

/* return true if we are at the EOF */
int core_feof(core_file *file);

/* return the total size of the file */
UINT64 core_fsize(core_file *file);



/* ----- file read ----- */

/* standard binary read from a file */
UINT32 core_fread(core_file *file, void *buffer, UINT32 length);

/* read one character from the file */
int core_fgetc(core_file *file);

/* put back one character from the file */
int core_ungetc(int c, core_file *file);

/* read a full line of text from the file */
char *core_fgets(char *s, int n, core_file *file);

/* get a pointer to a buffer that holds the full file data in RAM */
/* this function may cause the full file data to be read */
const void *core_fbuffer(core_file *file);

/* open a file with the specified filename, read it into memory, and return a pointer */
file_error core_fload(const char *filename, void **data, UINT32 *length);
file_error core_fload(const char *filename, dynamic_buffer &data);



/* ----- file write ----- */

/* standard binary write to a file */
UINT32 core_fwrite(core_file *file, const void *buffer, UINT32 length);

/* write a line of text to the file */
int core_fputs(core_file *f, const char *s);

/* printf-style text write to a file */
int core_vfprintf(core_file *f, const char *fmt, va_list va);
int CLIB_DECL core_fprintf(core_file *f, const char *fmt, ...) ATTR_PRINTF(2,3);

/* file truncation */
file_error core_truncate(core_file *f, UINT64 offset);



/* ----- filename utilities ----- */

/* extract the base part of a filename (remove extensions and paths) */
std::string &core_filename_extract_base(std::string &result, const char *name, bool strip_extension = false);

/* true if the given filename ends with a particular extension */
int core_filename_ends_with(const char *filename, const char *extension);


#endif  /* __COREFILE_H__ */
=======
class core_file
{
public:
	typedef std::unique_ptr<core_file> ptr;


	// ----- file open/close -----

	// open a file with the specified filename
	static osd_file::error open(std::string const &filename, std::uint32_t openflags, ptr &file);

	// open a RAM-based "file" using the given data and length (read-only)
	static osd_file::error open_ram(const void *data, std::size_t length, std::uint32_t openflags, ptr &file);

	// open a RAM-based "file" using the given data and length (read-only), copying the data
	static osd_file::error open_ram_copy(const void *data, std::size_t length, std::uint32_t openflags, ptr &file);

	// open a proxy "file" that forwards requests to another file object
	static osd_file::error open_proxy(core_file &file, ptr &proxy);

	// close an open file
	virtual ~core_file();

	// enable/disable streaming file compression via zlib; level is 0 to disable compression, or up to 9 for max compression
	virtual osd_file::error compress(int level) = 0;


	// ----- file positioning -----

	// adjust the file pointer within the file
	virtual int seek(std::int64_t offset, int whence) = 0;

	// return the current file pointer
	virtual std::uint64_t tell() const = 0;

	// return true if we are at the EOF
	virtual bool eof() const = 0;

	// return the total size of the file
	virtual std::uint64_t size() const = 0;


	// ----- file read -----

	// standard binary read from a file
	virtual std::uint32_t read(void *buffer, std::uint32_t length) = 0;

	// read one character from the file
	virtual int getc() = 0;

	// put back one character from the file
	virtual int ungetc(int c) = 0;

	// read a full line of text from the file
	virtual char *gets(char *s, int n) = 0;

	// get a pointer to a buffer that holds the full file data in RAM
	// this function may cause the full file data to be read
	virtual const void *buffer() = 0;

	// open a file with the specified filename, read it into memory, and return a pointer
	static osd_file::error load(std::string const &filename, void **data, std::uint32_t &length);
	static osd_file::error load(std::string const &filename, std::vector<uint8_t> &data);


	// ----- file write -----

	// standard binary write to a file
	virtual std::uint32_t write(const void *buffer, std::uint32_t length) = 0;

	// write a line of text to the file
	virtual int puts(const char *s) = 0;

	// printf-style text write to a file
	virtual int vprintf(util::format_argument_pack<std::ostream> const &args) = 0;
	template <typename Format, typename... Params> int printf(Format &&fmt, Params &&...args)
	{
		return vprintf(util::make_format_argument_pack(std::forward<Format>(fmt), std::forward<Params>(args)...));
	}

	// file truncation
	virtual osd_file::error truncate(std::uint64_t offset) = 0;

	// flush file buffers
	virtual osd_file::error flush() = 0;


protected:
	core_file();
};

} // namespace util


/***************************************************************************
    FUNCTION PROTOTYPES
***************************************************************************/

/* ----- filename utilities ----- */

// extract the base part of a filename (remove extensions and paths)
std::string core_filename_extract_base(const std::string &name, bool strip_extension = false);

// extracts the file extension from a filename
std::string core_filename_extract_extension(const std::string &filename, bool strip_period = false);

// true if the given filename ends with a particular extension
bool core_filename_ends_with(const std::string &filename, const std::string &extension);


#endif // MAME_LIB_UTIL_COREFILE_H
>>>>>>> upstream/master
