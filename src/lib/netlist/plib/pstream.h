// license:GPL-2.0+
// copyright-holders:Couriersud
/*
 * pstream.h
 */

<<<<<<< HEAD
#ifndef _PSTREAM_H_
#define _PSTREAM_H_

#include <cstdarg>
#include <cstddef>
#include <stdexcept>

#include "pconfig.h"
#include "pstring.h"
#include "palloc.h"
#include "pfmtlog.h"

=======
#ifndef PSTREAM_H_
#define PSTREAM_H_

#include "pconfig.h"
#include "pstring.h"
#include "pfmtlog.h"
#include "pexception.h"

#include <vector>

namespace plib {
>>>>>>> upstream/master
// -----------------------------------------------------------------------------
// pstream: things common to all streams
// -----------------------------------------------------------------------------

<<<<<<< HEAD
class pstream
{
	P_PREVENT_COPYING(pstream)
public:

	typedef long unsigned pos_type;

	static const pos_type SEEK_EOF = (pos_type) -1;

	pstream(const unsigned flags) : m_flags(flags)
	{
	}
	virtual ~pstream()
	{
	}

	bool bad() const { return ((m_flags & FLAG_ERROR) != 0); }
=======
class pstream : nocopyassignmove
{
public:

	using pos_type = std::size_t;

	static constexpr pos_type SEEK_EOF = static_cast<pos_type>(-1);

>>>>>>> upstream/master
	bool seekable() const { return ((m_flags & FLAG_SEEKABLE) != 0); }

	void seek(const pos_type n)
	{
<<<<<<< HEAD
		check_seekable();
=======
>>>>>>> upstream/master
		return vseek(n);
	}

	pos_type tell()
	{
		return vtell();
	}

protected:
<<<<<<< HEAD
	virtual void vseek(const pos_type n) = 0;
	virtual pos_type vtell() = 0;

	static const unsigned FLAG_EOF = 0x01;
	static const unsigned FLAG_ERROR = 0x02;
	static const unsigned FLAG_SEEKABLE = 0x04;
	static const unsigned FLAG_CLOSED = 0x08;    /* convenience flag */

	bool closed() { return ((m_flags & FLAG_CLOSED) != 0); }
=======
	explicit pstream(const unsigned flags) : m_flags(flags)
	{
	}
	~pstream();

	virtual void vseek(const pos_type n) = 0;
	virtual pos_type vtell() = 0;

	static constexpr unsigned FLAG_EOF = 0x01;
	static constexpr unsigned FLAG_SEEKABLE = 0x04;
>>>>>>> upstream/master

	void set_flag(const unsigned flag)
	{
		m_flags |= flag;
	}
	void clear_flag(const unsigned flag)
	{
		m_flags &= ~flag;
	}
<<<<<<< HEAD

	void check_not_eof() const
	{
		if (m_flags & FLAG_EOF)
			throw pexception("unexpected eof");
	}

	void check_seekable() const
	{
		if (!(m_flags & FLAG_SEEKABLE))
			throw pexception("stream is not seekable");
	}

=======
>>>>>>> upstream/master
	unsigned flags() const { return m_flags; }
private:

	unsigned m_flags;
};

// -----------------------------------------------------------------------------
// pistream: input stream
// -----------------------------------------------------------------------------

class pistream : public pstream
{
<<<<<<< HEAD
	P_PREVENT_COPYING(pistream)
public:

	pistream(const unsigned flags) : pstream(flags) {}
	virtual ~pistream() {}

	bool eof() const { return ((flags() & FLAG_EOF) != 0) || bad(); }

	/* this digests linux & dos/windows text files */

	bool readline(pstring &line);

	bool read(UINT8 &c)
	{
		return (read(&c, 1) == 1);
	}

	unsigned read(void *buf, const unsigned n)
=======
public:

	virtual ~pistream();

	bool eof() const { return ((flags() & FLAG_EOF) != 0); }

	pos_type read(void *buf, const pos_type n)
>>>>>>> upstream/master
	{
		return vread(buf, n);
	}

protected:
<<<<<<< HEAD
	/* read up to n bytes from stream */
	virtual unsigned vread(void *buf, const unsigned n) = 0;

private:
=======
	explicit pistream(const unsigned flags) : pstream(flags) {}
	/* read up to n bytes from stream */
	virtual pos_type vread(void *buf, const pos_type n) = 0;

>>>>>>> upstream/master
};

// -----------------------------------------------------------------------------
// postream: output stream
// -----------------------------------------------------------------------------

class postream : public pstream
{
<<<<<<< HEAD
	P_PREVENT_COPYING(postream)
public:

	postream(unsigned flags) : pstream(flags) {}
	virtual ~postream() {}

	/* this digests linux & dos/windows text files */

	void writeline(const pstring &line)
	{
		write(line);
		write(10);
	}

	void write(const pstring &text)
	{
		write(text.cstr(), text.blen());
	}

	void write(const char c)
	{
		write(&c, 1);
	}

	void write(const void *buf, const unsigned n)
=======
public:

	virtual ~postream();

	void write(const void *buf, const pos_type n)
>>>>>>> upstream/master
	{
		vwrite(buf, n);
	}

	void write(pistream &strm);

protected:
<<<<<<< HEAD
	/* write n bytes to stream */
	virtual void vwrite(const void *buf, const unsigned n) = 0;
=======
	explicit postream(unsigned flags) : pstream(flags) {}
	/* write n bytes to stream */
	virtual void vwrite(const void *buf, const pos_type n) = 0;
>>>>>>> upstream/master

private:
};

// -----------------------------------------------------------------------------
// pomemstream: output string stream
// -----------------------------------------------------------------------------

class pomemstream : public postream
{
<<<<<<< HEAD
	P_PREVENT_COPYING(pomemstream)
public:

	pomemstream();
	virtual ~pomemstream();

	char *memory() const { return m_mem; }
	unsigned size() const { return m_size; }

protected:
	/* write n bytes to stream */
	virtual void vwrite(const void *buf, const unsigned n);
	virtual void vseek(const pos_type n);
	virtual pos_type vtell();
=======
public:

	pomemstream();
	virtual ~pomemstream() override;

	char *memory() const { return m_mem; }
	pos_type size() const { return m_size; }

protected:
	/* write n bytes to stream */
	virtual void vwrite(const void *buf, const pos_type) override;
	virtual void vseek(const pos_type n) override;
	virtual pos_type vtell() override;
>>>>>>> upstream/master

private:
	pos_type m_pos;
	pos_type m_capacity;
	pos_type m_size;
	char *m_mem;
};

class postringstream : public postream
{
<<<<<<< HEAD
	P_PREVENT_COPYING(postringstream )

public:

	postringstream() : postream(0) { }
	virtual ~postringstream() { }

	const pstringbuffer &str() { return m_buf; }

protected:
	/* write n bytes to stream */
	virtual void vwrite(const void *buf, const unsigned n)
	{
		m_buf.cat(buf, n);
	}
	virtual void vseek(const pos_type n) { }
	virtual pos_type vtell() { return m_buf.len(); }

private:
	pstringbuffer m_buf;
=======
public:

	postringstream() : postream(0) { }
	virtual ~postringstream() override;

	const pstring &str() { return m_buf; }

protected:
	/* write n bytes to stream */
	virtual void vwrite(const void *buf, const pos_type n) override
	{
		m_buf += pstring(static_cast<const pstring::mem_t *>(buf), n, pstring::UTF8);
	}
	virtual void vseek(const pos_type n) override { }
	virtual pos_type vtell() override { return m_buf.mem_t_size(); }

private:
	pstring m_buf;
>>>>>>> upstream/master
};

// -----------------------------------------------------------------------------
// pofilestream: file output stream
// -----------------------------------------------------------------------------

class pofilestream : public postream
{
<<<<<<< HEAD
	P_PREVENT_COPYING(pofilestream)
public:

	pofilestream(const pstring &fname);
	virtual ~pofilestream();

	void close();

protected:
	pofilestream(void *file, const bool do_close);
	/* write n bytes to stream */
	virtual void vwrite(const void *buf, const unsigned n);
	virtual void vseek(const pos_type n);
	virtual pos_type vtell();
=======
public:

	explicit pofilestream(const pstring &fname);
	virtual ~pofilestream() override;

protected:
	pofilestream(void *file, const pstring &name, const bool do_close);
	/* write n bytes to stream */
	virtual void vwrite(const void *buf, const pos_type n) override;
	virtual void vseek(const pos_type n) override;
	virtual pos_type vtell() override;
>>>>>>> upstream/master

private:
	void *m_file;
	pos_type m_pos;
	bool m_actually_close;
<<<<<<< HEAD

	void init(void *file);
=======
	pstring m_filename;

	void init();
>>>>>>> upstream/master
};

// -----------------------------------------------------------------------------
// pstderr: write to stderr
// -----------------------------------------------------------------------------

class pstderr : public pofilestream
{
<<<<<<< HEAD
	P_PREVENT_COPYING(pstderr)
public:
	pstderr();
=======
public:
	pstderr();
	virtual ~pstderr();
>>>>>>> upstream/master
};

// -----------------------------------------------------------------------------
// pstdout: write to stdout
// -----------------------------------------------------------------------------

class pstdout : public pofilestream
{
<<<<<<< HEAD
	P_PREVENT_COPYING(pstdout)
public:
	pstdout();
=======
public:
	pstdout();
	virtual ~pstdout();
>>>>>>> upstream/master
};

// -----------------------------------------------------------------------------
// pifilestream: file input stream
// -----------------------------------------------------------------------------

class pifilestream : public pistream
{
<<<<<<< HEAD
	P_PREVENT_COPYING(pifilestream)
public:

	pifilestream(const pstring &fname);
	virtual ~pifilestream();

	void close();

protected:
	pifilestream(void *file, const bool do_close);

	/* read up to n bytes from stream */
	virtual unsigned vread(void *buf, const unsigned n);
	virtual void vseek(const pos_type n);
	virtual pos_type vtell();
=======
public:

	explicit pifilestream(const pstring &fname);
	virtual ~pifilestream() override;

protected:
	pifilestream(void *file, const pstring &name, const bool do_close);

	/* read up to n bytes from stream */
	virtual pos_type vread(void *buf, const pos_type n) override;
	virtual void vseek(const pos_type n) override;
	virtual pos_type vtell() override;
>>>>>>> upstream/master

private:
	void *m_file;
	pos_type m_pos;
	bool m_actually_close;
<<<<<<< HEAD

	void init(void *file);
=======
	pstring m_filename;

	void init();
>>>>>>> upstream/master
};

// -----------------------------------------------------------------------------
// pstdin: reads from stdin
// -----------------------------------------------------------------------------

class pstdin : public pifilestream
{
<<<<<<< HEAD
	P_PREVENT_COPYING(pstdin)
public:

	pstdin();
=======
public:

	pstdin();
	virtual ~pstdin() override;
>>>>>>> upstream/master
};

// -----------------------------------------------------------------------------
// pimemstream: input memory stream
// -----------------------------------------------------------------------------

class pimemstream : public pistream
{
<<<<<<< HEAD
	P_PREVENT_COPYING(pimemstream)
public:

	pimemstream(const void *mem, const pos_type len);
	pimemstream(const pomemstream &ostrm);
	virtual ~pimemstream();

protected:
	/* read up to n bytes from stream */
	virtual unsigned vread(void *buf, const unsigned n);
	virtual void vseek(const pos_type n);
	virtual pos_type vtell();
=======
public:

	pimemstream(const void *mem, const pos_type len);
	explicit pimemstream(const pomemstream &ostrm);
	virtual ~pimemstream() override;

	pos_type size() const { return m_len; }
protected:
	/* read up to n bytes from stream */
	virtual pos_type vread(void *buf, const pos_type n) override;
	virtual void vseek(const pos_type n) override;
	virtual pos_type vtell() override;
>>>>>>> upstream/master

private:
	pos_type m_pos;
	pos_type m_len;
<<<<<<< HEAD
	char *m_mem;
=======
	const char *m_mem;
>>>>>>> upstream/master
};

// -----------------------------------------------------------------------------
// pistringstream: input string stream
// -----------------------------------------------------------------------------

class pistringstream : public pimemstream
{
<<<<<<< HEAD
	P_PREVENT_COPYING(pistringstream)
public:

	pistringstream(const pstring &str) : pimemstream(str.cstr(), str.len()), m_str(str) { }
=======
public:
	explicit pistringstream(const pstring &str) : pimemstream(str.c_str(), str.mem_t_size()), m_str(str) { }
	virtual ~pistringstream() override;
>>>>>>> upstream/master

private:
	/* only needed for a reference till destruction */
	pstring m_str;
};

// -----------------------------------------------------------------------------
<<<<<<< HEAD
// pstream_fmt_writer_t: writer on top of ostream
// -----------------------------------------------------------------------------

class pstream_fmt_writer_t : public pfmt_writer_t<>
{
	P_PREVENT_COPYING(pstream_fmt_writer_t)
public:

	pstream_fmt_writer_t(postream &strm) : m_strm(strm) {}
	virtual ~pstream_fmt_writer_t() { }

protected:
	virtual void vdowrite(const pstring &ls) const
	{
		m_strm.write(ls);
=======
// putf8reader_t: reader on top of istream
// -----------------------------------------------------------------------------

/* this digests linux & dos/windows text files */

class putf8_reader : plib::nocopyassignmove
{
public:
	explicit putf8_reader(pistream &strm) : m_strm(strm) {}
	virtual ~putf8_reader() {}

	bool eof() const { return m_strm.eof(); }
	bool readline(pstring &line);

	bool readbyte1(char &b)
	{
		return (m_strm.read(&b, 1) == 1);
	}

	bool readcode(pstring::code_t &c)
	{
		char b[4];
		if (m_strm.read(&b[0], 1) != 1)
			return false;
		const std::size_t l = pstring::traits_type::codelen(b);
		for (std::size_t i = 1; i < l; i++)
			if (m_strm.read(&b[i], 1) != 1)
				return false;
		c = pstring::traits_type::code(b);
		return true;
	}

private:
	pistream &m_strm;
	pstring m_linebuf;
};

// -----------------------------------------------------------------------------
// putf8writer_t: writer on top of ostream
// -----------------------------------------------------------------------------

class putf8_writer : plib::nocopyassignmove
{
public:
	explicit putf8_writer(postream &strm) : m_strm(strm) {}
	virtual ~putf8_writer() {}

	void writeline(const pstring &line) const
	{
		write(line);
		write(10);
	}

	void write(const pstring &text) const
	{
		m_strm.write(text.c_str(), text.mem_t_size());
	}

	void write(const pstring::code_t c) const
	{
		write(pstring(c));
>>>>>>> upstream/master
	}

private:
	postream &m_strm;
};

<<<<<<< HEAD
#endif /* _PSTREAM_H_ */
=======
class putf8_fmt_writer : public pfmt_writer_t<putf8_fmt_writer>, public putf8_writer
{
public:

	explicit putf8_fmt_writer(postream &strm);
	virtual ~putf8_fmt_writer() override;

//protected:
	void vdowrite(const pstring &ls) const;

private:
};

// -----------------------------------------------------------------------------
// pbinary_writer_t: writer on top of ostream
// -----------------------------------------------------------------------------

class pbinary_writer : plib::nocopyassignmove
{
public:
	explicit pbinary_writer(postream &strm) : m_strm(strm) {}
	virtual ~pbinary_writer() {}

	template <typename T>
	void write(const T val)
	{
		m_strm.write(&val, sizeof(T));
	}

	void write(const pstring &s)
	{
		write(s.mem_t_size());
		m_strm.write(s.c_str(), s.mem_t_size());
	}

	template <typename T>
	void write(const std::vector<T> &val)
	{
		std::size_t sz = val.size();
		write(sz);
		m_strm.write(val.data(), sizeof(T) * sz);
	}

private:
	postream &m_strm;
};

class pbinary_reader : plib::nocopyassignmove
{
public:
	explicit pbinary_reader(pistream &strm) : m_strm(strm) {}
	virtual ~pbinary_reader() {}

	template <typename T>
	void read(T &val)
	{
		m_strm.read(&val, sizeof(T));
	}

	void read( pstring &s)
	{
		std::size_t sz = 0;
		read(sz);
		pstring::mem_t *buf = new pstring::mem_t[sz+1];
		m_strm.read(buf, sz);
		buf[sz] = 0;
		s = pstring(buf, pstring::UTF8);
		delete [] buf;
	}

	template <typename T>
	void read(std::vector<T> &val)
	{
		std::size_t sz = 0;
		read(sz);
		val.resize(sz);
		m_strm.read(val.data(), sizeof(T) * sz);
	}

private:
	pistream &m_strm;
};

}

#endif /* PSTREAM_H_ */
>>>>>>> upstream/master
