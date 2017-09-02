// license:GPL-2.0+
// copyright-holders:Couriersud
/*
 * pstream.c
 *
 */

<<<<<<< HEAD
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>

#include "pstream.h"
#include "palloc.h"
=======
#include "pstream.h"
#include "palloc.h"

#include <cstdio>
#include <cstdlib>
#include <algorithm>

// VS2015 prefers _dup
#ifdef _WIN32
#include <io.h>
#else
#include <unistd.h>
#endif

namespace plib {

pstream::~pstream()
{
}
>>>>>>> upstream/master

// -----------------------------------------------------------------------------
// pistream: input stream
// -----------------------------------------------------------------------------

<<<<<<< HEAD
bool pistream::readline(pstring &line)
{
	UINT8 c = 0;
	pstringbuffer buf;
	if (!this->read(c))
	{
		line = "";
		return false;
	}
	while (true)
	{
		if (c == 10)
			break;
		else if (c != 13) /* ignore CR */
			buf += c;
		if (!this->read(c))
			break;
	}
	line = buf;
	return true;
=======
pistream::~pistream()
{
>>>>>>> upstream/master
}

// -----------------------------------------------------------------------------
// postream: output stream
// -----------------------------------------------------------------------------

<<<<<<< HEAD
void postream::write(pistream &strm)
{
	char buf[1024];
	unsigned r;
	while ( !bad() && ((r=strm.read(buf, 1024)) > 0))
=======
postream::~postream()
{
}

void postream::write(pistream &strm)
{
	char buf[1024];
	pos_type r;
	while ((r=strm.read(buf, 1024)) > 0)
>>>>>>> upstream/master
		write(buf, r);
}

// -----------------------------------------------------------------------------
// Input file stream
// -----------------------------------------------------------------------------

pifilestream::pifilestream(const pstring &fname)
<<<<<<< HEAD
: pistream(0), m_pos(0), m_actually_close(true)
{
	init(fopen(fname.cstr(), "rb"));
}

pifilestream::pifilestream(void *file, const bool do_close)
: pistream(0), m_pos(0), m_actually_close(do_close)
{
	init(file);
}

void pifilestream::init(void *file)
{
	m_file = file;
	if (m_file == NULL)
	{
		set_flag(FLAG_ERROR);
		set_flag(FLAG_EOF);
		set_flag(FLAG_CLOSED);
	}
	else
	{
		if (ftell((FILE *) m_file) >= 0)
		{
			if (fseek((FILE *) m_file, 0, SEEK_SET) >= 0)
				set_flag(FLAG_SEEKABLE);
		}
=======
: pistream(0)
, m_file(fopen(fname.c_str(), "rb"))
, m_pos(0)
, m_actually_close(true)
, m_filename(fname)
{
	if (m_file == nullptr)
		throw file_open_e(fname);
	else
		init();
}

pifilestream::pifilestream(void *file, const pstring &name, const bool do_close)
: pistream(0), m_file(file), m_pos(0), m_actually_close(do_close), m_filename(name)
{
	if (m_file == nullptr)
		throw null_argument_e(m_filename);
	init();
}

void pifilestream::init()
{
	if (ftell(static_cast<FILE *>(m_file)) >= 0)
	{
		if (fseek(static_cast<FILE *>(m_file), 0, SEEK_SET) >= 0)
			set_flag(FLAG_SEEKABLE);
>>>>>>> upstream/master
	}
}

pifilestream::~pifilestream()
{
<<<<<<< HEAD
	if (!closed())
		close();
}

void pifilestream::close()
{
	if (m_actually_close)
	{
		fclose((FILE *) m_file);
		set_flag(FLAG_CLOSED);
	}
}

unsigned pifilestream::vread(void *buf, unsigned n)
{
	std::size_t r = fread(buf, 1, n, (FILE *) m_file);
	if (r < n)
	{
		if (feof((FILE *) m_file))
			set_flag(FLAG_EOF);
		if (ferror((FILE *) m_file))
			set_flag(FLAG_ERROR);
=======
	if (m_actually_close)
	{
		fclose(static_cast<FILE *>(m_file));
	}
}

pifilestream::pos_type pifilestream::vread(void *buf, const pos_type n)
{
	pos_type r = fread(buf, 1, n, static_cast<FILE *>(m_file));
	if (r < n)
	{
		if (feof(static_cast<FILE *>(m_file)))
			set_flag(FLAG_EOF);
		if (ferror(static_cast<FILE *>(m_file)))
			throw file_read_e(m_filename);
>>>>>>> upstream/master
	}
	m_pos += r;
	return r;
}

<<<<<<< HEAD
void pifilestream::vseek(pos_type n)
{
	check_seekable();
	if (fseek((FILE *) m_file, SEEK_SET, n) < 0)
		set_flag(FLAG_ERROR);
	else
		m_pos = n;
	if (feof((FILE *) m_file))
		set_flag(FLAG_EOF);
	else
		clear_flag(FLAG_EOF);
	if (ferror((FILE *) m_file))
		set_flag(FLAG_ERROR);
=======
void pifilestream::vseek(const pos_type n)
{
	if (fseek(static_cast<FILE *>(m_file), static_cast<long>(n), SEEK_SET) < 0)
		throw file_e("File seek failed: {}", m_filename);
	else
		m_pos = n;
	if (feof(static_cast<FILE *>(m_file)))
		set_flag(FLAG_EOF);
	else
		clear_flag(FLAG_EOF);
	if (ferror(static_cast<FILE *>(m_file)))
		throw file_e("Generic file operation failed: {}", m_filename);
>>>>>>> upstream/master
}

pifilestream::pos_type pifilestream::vtell()
{
<<<<<<< HEAD
	long ret = ftell((FILE *) m_file);
=======
	long ret = ftell(static_cast<FILE *>(m_file));
>>>>>>> upstream/master
	if (ret < 0)
	{
		return m_pos;
	}
	else
<<<<<<< HEAD
		return ret;
=======
		return static_cast<pos_type>(ret);
>>>>>>> upstream/master
}

// -----------------------------------------------------------------------------
// pstdin: reads from stdin
// -----------------------------------------------------------------------------

pstdin::pstdin()
<<<<<<< HEAD
: pifilestream(stdin, false)
=======
: pifilestream(stdin, "<stdin>", false)
>>>>>>> upstream/master
{
	/* nothing to do */
}

<<<<<<< HEAD
=======
pstdin::~pstdin()
{
}

>>>>>>> upstream/master
// -----------------------------------------------------------------------------
// Output file stream
// -----------------------------------------------------------------------------

pofilestream::pofilestream(const pstring &fname)
<<<<<<< HEAD
: postream(0), m_pos(0), m_actually_close(true)
{
	init(fopen(fname.cstr(), "wb"));
}

pofilestream::pofilestream(void *file, const bool do_close)
: postream(0), m_pos(0), m_actually_close(do_close)
{
	init(file);
}

void pofilestream::init(void *file)
{
	m_file = file;
	if (m_file == NULL)
	{
		set_flag(FLAG_ERROR);
		set_flag(FLAG_CLOSED);
	}
	else
	{
		if (ftell((FILE *) m_file) >= 0)
		{
			if (fseek((FILE *) m_file, 0, SEEK_SET) >= 0)
				set_flag(FLAG_SEEKABLE);
		}
	}
=======
: postream(0), m_file(fopen(fname.c_str(), "wb")), m_pos(0), m_actually_close(true), m_filename(fname)
{
	if (m_file == nullptr)
		throw file_open_e(m_filename);
	init();
}

pofilestream::pofilestream(void *file, const pstring &name, const bool do_close)
: postream(0), m_file(file), m_pos(0), m_actually_close(do_close), m_filename(name)
{
	if (m_file == nullptr)
		throw null_argument_e(m_filename);
	init();
}

void pofilestream::init()
{
	if (ftell(static_cast<FILE *>(m_file)) >= 0)
		if (fseek(static_cast<FILE *>(m_file), 0, SEEK_SET) >= 0)
			set_flag(FLAG_SEEKABLE);
>>>>>>> upstream/master
}

pofilestream::~pofilestream()
{
<<<<<<< HEAD
	if (!closed())
		close();
}

void pofilestream::close()
{
	if (m_actually_close)
	{
		fclose((FILE *) m_file);
		set_flag(FLAG_CLOSED);
	}
}

void pofilestream::vwrite(const void *buf, unsigned n)
{
	std::size_t r = fwrite(buf, 1, n, (FILE *) m_file);
	if (r < n)
	{
		if (ferror((FILE *) m_file))
			set_flag(FLAG_ERROR);
=======
	if (m_actually_close)
	{
		fflush(static_cast<FILE *>(m_file));
		fclose(static_cast<FILE *>(m_file));
	}
}

void pofilestream::vwrite(const void *buf, const pos_type n)
{
	std::size_t r = fwrite(buf, 1, n, static_cast<FILE *>(m_file));
	if (r < n)
	{
		//printf("%ld %ld %s\n", r, n, strerror(errno));
		if (ferror(static_cast<FILE *>(m_file)))
			throw file_write_e(m_filename);
>>>>>>> upstream/master
	}
	m_pos += r;
}

<<<<<<< HEAD
void pofilestream::vseek(pos_type n)
{
	check_seekable();
	if (fseek((FILE *) m_file, SEEK_SET, n) < 0)
		set_flag(FLAG_ERROR);
	else
	{
		m_pos = n;
		if (ferror((FILE *) m_file))
			set_flag(FLAG_ERROR);
=======
void pofilestream::vseek(const pos_type n)
{
	if (fseek(static_cast<FILE *>(m_file), static_cast<long>(n), SEEK_SET) < 0)
		throw file_e("File seek failed: {}", m_filename);
	else
	{
		m_pos = n;
		if (ferror(static_cast<FILE *>(m_file)))
			throw file_e("Generic file operation failed: {}", m_filename);
>>>>>>> upstream/master
	}
}

pstream::pos_type pofilestream::vtell()
{
<<<<<<< HEAD
	long ret = ftell((FILE *) m_file);
=======
	std::ptrdiff_t ret = ftell(static_cast<FILE *>(m_file));
>>>>>>> upstream/master
	if (ret < 0)
	{
		return m_pos;
	}
	else
<<<<<<< HEAD
		return ret;
}

=======
		return static_cast<pos_type>(ret);
}

postringstream::~postringstream()
{
}


>>>>>>> upstream/master
// -----------------------------------------------------------------------------
// pstderr: write to stderr
// -----------------------------------------------------------------------------

pstderr::pstderr()
<<<<<<< HEAD
: pofilestream(stderr, false)
=======
#ifdef _WIN32
: pofilestream(fdopen(_dup(fileno(stderr)), "wb"), "<stderr>", true)
#else
: pofilestream(fdopen(dup(fileno(stderr)), "wb"), "<stderr>", true)
#endif
{
}

pstderr::~pstderr()
>>>>>>> upstream/master
{
}

// -----------------------------------------------------------------------------
// pstdout: write to stdout
// -----------------------------------------------------------------------------

pstdout::pstdout()
<<<<<<< HEAD
: pofilestream(stdout, false)
=======
#ifdef _WIN32
: pofilestream(fdopen(_dup(fileno(stdout)), "wb"), "<stdout>", true)
#else
: pofilestream(fdopen(dup(fileno(stdout)), "wb"), "<stdout>", true)
#endif
{
}

pstdout::~pstdout()
>>>>>>> upstream/master
{
}

// -----------------------------------------------------------------------------
// Memory stream
// -----------------------------------------------------------------------------

pimemstream::pimemstream(const void *mem, const pos_type len)
<<<<<<< HEAD
	: pistream(FLAG_SEEKABLE), m_pos(0), m_len(len), m_mem((char *) mem)
=======
	: pistream(FLAG_SEEKABLE), m_pos(0), m_len(len), m_mem(static_cast<const pstring::mem_t *>(mem))
>>>>>>> upstream/master
{
}

pimemstream::pimemstream(const pomemstream &ostrm)
<<<<<<< HEAD
: pistream(FLAG_SEEKABLE), m_pos(0), m_len(ostrm.size()), m_mem((char *) ostrm.memory())
=======
: pistream(FLAG_SEEKABLE), m_pos(0), m_len(ostrm.size()), m_mem(reinterpret_cast<pstring::mem_t *>(ostrm.memory()))
>>>>>>> upstream/master
{
}

pimemstream::~pimemstream()
{
}

<<<<<<< HEAD
unsigned pimemstream::vread(void *buf, unsigned n)
{
	unsigned ret = (m_pos + n <= m_len) ? n :  m_len - m_pos;

	if (ret > 0)
	{
		memcpy(buf, m_mem + m_pos, ret);
=======
pimemstream::pos_type pimemstream::vread(void *buf, const pos_type n)
{
	pos_type ret = (m_pos + n <= m_len) ? n :  m_len - m_pos;

	if (ret > 0)
	{
		std::copy(m_mem + m_pos, m_mem + m_pos + ret, static_cast<char *>(buf));
>>>>>>> upstream/master
		m_pos += ret;
	}

	if (ret < n)
		set_flag(FLAG_EOF);

	return ret;
}

<<<<<<< HEAD
void pimemstream::vseek(pos_type n)
=======
void pimemstream::vseek(const pos_type n)
>>>>>>> upstream/master
{
	m_pos = (n>=m_len) ? m_len : n;
	clear_flag(FLAG_EOF);

}

pimemstream::pos_type pimemstream::vtell()
{
	return m_pos;
}

<<<<<<< HEAD
=======
pistringstream::~pistringstream()
{
}

>>>>>>> upstream/master
// -----------------------------------------------------------------------------
// Output memory stream
// -----------------------------------------------------------------------------

pomemstream::pomemstream()
: postream(FLAG_SEEKABLE), m_pos(0), m_capacity(1024), m_size(0)
{
<<<<<<< HEAD
	m_mem = palloc_array(char, m_capacity);
=======
	m_mem = palloc_array<char>(m_capacity);
>>>>>>> upstream/master
}

pomemstream::~pomemstream()
{
	pfree_array(m_mem);
}

<<<<<<< HEAD
void pomemstream::vwrite(const void *buf, unsigned n)
=======
void pomemstream::vwrite(const void *buf, const pos_type n)
>>>>>>> upstream/master
{
	if (m_pos + n >= m_capacity)
	{
		while (m_pos + n >= m_capacity)
			m_capacity *= 2;
		char *o = m_mem;
<<<<<<< HEAD
		m_mem = palloc_array(char, m_capacity);
		if (m_mem == NULL)
		{
			set_flag(FLAG_ERROR);
			return;
		}
		memcpy(m_mem, o, m_pos);
		pfree_array(o);
	}

	memcpy(m_mem + m_pos, buf, n);
=======
		m_mem = palloc_array<char>(m_capacity);
		if (m_mem == nullptr)
		{
			throw out_of_mem_e("pomemstream::vwrite");
		}
		std::copy(o, o + m_pos, m_mem);
		pfree_array(o);
	}

	std::copy(static_cast<const char *>(buf), static_cast<const char *>(buf) + n, m_mem + m_pos);
>>>>>>> upstream/master
	m_pos += n;
	m_size = std::max(m_pos, m_size);
}

<<<<<<< HEAD
void pomemstream::vseek(pos_type n)
=======
void pomemstream::vseek(const pos_type n)
>>>>>>> upstream/master
{
	m_pos = n;
	m_size = std::max(m_pos, m_size);
	if (m_size >= m_capacity)
	{
		while (m_size >= m_capacity)
			m_capacity *= 2;
		char *o = m_mem;
<<<<<<< HEAD
		m_mem = palloc_array(char, m_capacity);
		if (m_mem == NULL)
		{
			set_flag(FLAG_ERROR);
			return;
		}
		memcpy(m_mem, o, m_pos);
=======
		m_mem = palloc_array<char>(m_capacity);
		if (m_mem == nullptr)
		{
			throw out_of_mem_e("pomemstream::vseek");
		}
		std::copy(o, o + m_pos, m_mem);
>>>>>>> upstream/master
		pfree_array(o);
	}
}

pstream::pos_type pomemstream::vtell()
{
	return m_pos;
}
<<<<<<< HEAD
=======

bool putf8_reader::readline(pstring &line)
{
	pstring::code_t c = 0;
	m_linebuf = "";
	if (!this->readcode(c))
	{
		line = "";
		return false;
	}
	while (true)
	{
		if (c == 10)
			break;
		else if (c != 13) /* ignore CR */
			m_linebuf += pstring(c);
		if (!this->readcode(c))
			break;
	}
	line = m_linebuf;
	return true;
}

putf8_fmt_writer::putf8_fmt_writer(postream &strm)
: pfmt_writer_t()
, putf8_writer(strm)
{
}

putf8_fmt_writer::~putf8_fmt_writer()
{
}

void putf8_fmt_writer::vdowrite(const pstring &ls) const
{
	write(ls);
}



}
>>>>>>> upstream/master
