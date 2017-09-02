// license:BSD-3-Clause
// copyright-holders:Aaron Giles
/***************************************************************************

    fileio.h

    Core file I/O interface functions and definitions.

***************************************************************************/

<<<<<<< HEAD
#pragma once

#ifndef __FILEIO_H__
#define __FILEIO_H__
=======
#ifndef MAME_EMU_FILEIO_H
#define MAME_EMU_FILEIO_H

#pragma once
>>>>>>> upstream/master

#include "corefile.h"
#include "hash.h"

// some systems use macros for getc/putc rather than functions
#ifdef getc
#undef getc
#endif

//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

<<<<<<< HEAD
// forward declarations
struct zip_file_header;
struct zip_file;

struct _7z_file_header;
struct _7z_file;

=======
>>>>>>> upstream/master
// ======================> path_iterator

// helper class for iterating over configured paths
class path_iterator
{
public:
<<<<<<< HEAD
	// construction/destruction
	path_iterator(const char *searchpath);

	// getters
	bool next(std::string &buffer, const char *name = NULL);

	// reset
	void reset() { m_current = m_base; m_index = 0; }

private:
	// internal state
	const char *    m_base;
	const char *    m_current;
	int             m_index;
=======
	// constructors
	path_iterator(std::string &&searchpath);
	path_iterator(std::string const &searchpath);
	path_iterator(path_iterator &&that);
	path_iterator(path_iterator const &that);

	// assignment operators
	path_iterator &operator=(path_iterator &&that);
	path_iterator &operator=(path_iterator const &that);

	// main interface
	bool next(std::string &buffer, const char *name = nullptr);
	void reset();

private:
	// internal state
	std::string                 m_searchpath;
	std::string::const_iterator m_current;
	bool                        m_is_first;
>>>>>>> upstream/master
};



// ======================> file_enumerator

// iterate over all files in all paths specified in the searchpath
class file_enumerator
{
public:
	// construction/destruction
<<<<<<< HEAD
	file_enumerator(const char *searchpath);
	~file_enumerator();

	// iterator
	const osd_directory_entry *next();

private:
	// internal state
	path_iterator   m_iterator;
	osd_directory * m_curdir;
	std::string     m_pathbuffer;
	//int             m_buflen;
=======
	template <typename... T> file_enumerator(T &&... args) : m_iterator(std::forward<T>(args)...) { }
	file_enumerator(file_enumerator &&) = default;
	file_enumerator(file_enumerator const &) = delete;
	file_enumerator &operator=(file_enumerator &&) = default;
	file_enumerator &operator=(file_enumerator const &) = delete;

	// iterator
	const osd::directory::entry *next();

private:
	// internal state
	path_iterator       m_iterator;
	osd::directory::ptr m_curdir;
	std::string         m_pathbuffer;
>>>>>>> upstream/master
};



// ======================> emu_file

class emu_file
{
public:
	// file open/creation
<<<<<<< HEAD
	emu_file(UINT32 openflags);
	emu_file(const char *searchpath, UINT32 openflags);
	virtual ~emu_file();

	// getters
	operator core_file *();
	operator core_file &();
	bool is_open() const { return (m_file != NULL); }
	const char *filename() const { return m_filename.c_str(); }
	const char *fullpath() const { return m_fullpath.c_str(); }
	UINT32 openflags() const { return m_openflags; }
	hash_collection &hashes(const char *types);
	bool restrict_to_mediapath() { return m_restrict_to_mediapath; }
=======
	emu_file(u32 openflags);
	emu_file(std::string &&searchpath, u32 openflags);
	virtual ~emu_file();

	// getters
	operator util::core_file &();
	bool is_open() const { return bool(m_file); }
	const char *filename() const { return m_filename.c_str(); }
	const char *fullpath() const { return m_fullpath.c_str(); }
	u32 openflags() const { return m_openflags; }
	util::hash_collection &hashes(const char *types);
	bool restrict_to_mediapath() const { return m_restrict_to_mediapath; }
>>>>>>> upstream/master
	bool part_of_mediapath(std::string path);

	// setters
	void remove_on_close() { m_remove_on_close = true; }
<<<<<<< HEAD
	void set_openflags(UINT32 openflags) { assert(m_file == NULL); m_openflags = openflags; }
	void set_restrict_to_mediapath(bool rtmp = true) { m_restrict_to_mediapath = rtmp; }

	// open/close
	file_error open(const char *name);
	file_error open(const char *name1, const char *name2);
	file_error open(const char *name1, const char *name2, const char *name3);
	file_error open(const char *name1, const char *name2, const char *name3, const char *name4);
	file_error open(const char *name, UINT32 crc);
	file_error open(const char *name1, const char *name2, UINT32 crc);
	file_error open(const char *name1, const char *name2, const char *name3, UINT32 crc);
	file_error open(const char *name1, const char *name2, const char *name3, const char *name4, UINT32 crc);
	file_error open_next();
	file_error open_ram(const void *data, UINT32 length);
	void close();

	// control
	file_error compress(int compress);
	int seek(INT64 offset, int whence);
	UINT64 tell();
	bool eof();
	UINT64 size();

	// reading
	UINT32 read(void *buffer, UINT32 length);
=======
	void set_openflags(u32 openflags) { assert(!m_file); m_openflags = openflags; }
	void set_restrict_to_mediapath(bool rtmp = true) { m_restrict_to_mediapath = rtmp; }

	// open/close
	osd_file::error open(const std::string &name);
	osd_file::error open(const std::string &name1, const std::string &name2);
	osd_file::error open(const std::string &name1, const std::string &name2, const std::string &name3);
	osd_file::error open(const std::string &name1, const std::string &name2, const std::string &name3, const std::string &name4);
	osd_file::error open(const std::string &name, u32 crc);
	osd_file::error open(const std::string &name1, const std::string &name2, u32 crc);
	osd_file::error open(const std::string &name1, const std::string &name2, const std::string &name3, u32 crc);
	osd_file::error open(const std::string &name1, const std::string &name2, const std::string &name3, const std::string &name4, u32 crc);
	osd_file::error open_next();
	osd_file::error open_ram(const void *data, u32 length);
	void close();

	// control
	osd_file::error compress(int compress);

	// position
	int seek(s64 offset, int whence);
	u64 tell();
	bool eof();
	u64 size();

	// reading
	u32 read(void *buffer, u32 length);
>>>>>>> upstream/master
	int getc();
	int ungetc(int c);
	char *gets(char *s, int n);

	// writing
<<<<<<< HEAD
	UINT32 write(const void *buffer, UINT32 length);
	int puts(const char *s);
	int vprintf(const char *fmt, va_list va);
	int printf(const char *fmt, ...) ATTR_PRINTF(2,3);
=======
	u32 write(const void *buffer, u32 length);
	int puts(const char *s);
	int vprintf(util::format_argument_pack<std::ostream> const &args);
	template <typename Format, typename... Params> int printf(Format &&fmt, Params &&...args)
	{
		return vprintf(util::make_format_argument_pack(std::forward<Format>(fmt), std::forward<Params>(args)...));
	}

	// buffers
	void flush();
>>>>>>> upstream/master

private:
	bool compressed_file_ready(void);

	// internal helpers
<<<<<<< HEAD
	file_error attempt_zipped();
	file_error load_zipped_file();
	bool zip_filename_match(const zip_file_header &header, const std::string &filename);
	bool zip_header_is_path(const zip_file_header &header);

	file_error attempt__7zped();
	file_error load__7zped_file();

	// internal state
	std::string     m_filename;                     // original filename provided
	std::string     m_fullpath;                     // full filename
	core_file *     m_file;                         // core file pointer
	path_iterator   m_iterator;                     // iterator for paths
	path_iterator   m_mediapaths;                   // media-path iterator
	UINT32          m_crc;                          // file's CRC
	UINT32          m_openflags;                    // flags we used for the open
	hash_collection m_hashes;                       // collection of hashes

	zip_file *      m_zipfile;                      // ZIP file pointer
	dynamic_buffer  m_zipdata;                      // ZIP file data
	UINT64          m_ziplength;                    // ZIP file length

	_7z_file *      m__7zfile;                      // 7Z file pointer
	dynamic_buffer  m__7zdata;                      // 7Z file data
	UINT64          m__7zlength;                    // 7Z file length

	bool            m_remove_on_close;              // flag: remove the file when closing
	bool            m_restrict_to_mediapath;        // flag: restrict to paths inside the media-path
};


#endif  /* __FILEIO_H__ */
=======
	osd_file::error attempt_zipped();
	osd_file::error load_zipped_file();

	// internal state
	std::string             m_filename;             // original filename provided
	std::string             m_fullpath;             // full filename
	util::core_file::ptr    m_file;                 // core file pointer
	path_iterator           m_iterator;             // iterator for paths
	path_iterator           m_mediapaths;           // media-path iterator
	u32                     m_crc;                  // file's CRC
	u32                     m_openflags;            // flags we used for the open
	util::hash_collection   m_hashes;               // collection of hashes

	std::unique_ptr<util::archive_file> m_zipfile;  // ZIP file pointer
	std::vector<u8>         m_zipdata;               // ZIP file data
	u64                     m_ziplength;             // ZIP file length

	bool                    m_remove_on_close;       // flag: remove the file when closing
	bool                    m_restrict_to_mediapath; // flag: restrict to paths inside the media-path
};

#endif // MAME_EMU_FILEIO_H
>>>>>>> upstream/master
