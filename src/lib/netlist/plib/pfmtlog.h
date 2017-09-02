// license:GPL-2.0+
// copyright-holders:Couriersud
/*
 * pfmtlog.h
 */

<<<<<<< HEAD
#ifndef _PFMT_H_
#define _PFMT_H_

//#include <cstdarg>
//#include <cstddef>

#include "pconfig.h"
#include "pstring.h"
#include "ptypes.h"

template <typename T>
struct ptype_treats
=======
#ifndef PFMT_H_
#define PFMT_H_

#include "pstring.h"
#include "ptypes.h"

#include <limits>

namespace plib {

P_ENUM(plog_level,
	DEBUG,
	INFO,
	VERBOSE,
	WARNING,
	ERROR,
	FATAL)

template <typename T>
struct ptype_traits_base
{
	static const T cast(const T &x) { return x; }
	static const bool is_signed = std::numeric_limits<T>::is_signed;
	static const char *size_spec() { return ""; }
	static char32_t fmt_spec() { return 'u'; }
};

template <>
struct ptype_traits_base<bool>
{
	static unsigned int cast(bool &x) { return static_cast<unsigned int>(x); }
	static unsigned int cast(const bool &x) { return static_cast<unsigned int>(x); }
	static const bool is_signed = std::numeric_limits<bool>::is_signed;
	static const char *size_spec() { return ""; }
	static char32_t fmt_spec() { return 'u'; }
};

template <typename T>
struct ptype_traits;

template<>
struct ptype_traits<bool> : ptype_traits_base<bool>
>>>>>>> upstream/master
{
};

template<>
<<<<<<< HEAD
struct ptype_treats<char>
{
	static short cast(char x) { return x; }
	static const bool is_signed = true;
	static const char *size_specifier() { return "h"; }
};

template<>
struct ptype_treats<short>
{
	static short cast(short x) { return x; }
	static const bool is_signed = true;
	static const char *size_specifier() { return "h"; }
};

template<>
struct ptype_treats<int>
{
	static int cast(int x) { return x; }
	static const bool is_signed = true;
	static const char *size_specifier() { return ""; }
};

template<>
struct ptype_treats<long>
{
	static long cast(long x) { return x; }
	static const bool is_signed = true;
	static const char *size_specifier() { return "l"; }
};

template<>
struct ptype_treats<long long>
{
	static long long cast(long long x) { return x; }
	static const bool is_signed = true;
	static const char *size_specifier() { return "ll"; }
};

template<>
struct ptype_treats<unsigned char>
{
	static unsigned short cast(unsigned char x) { return x; }
	static const bool is_signed = false;
	static const char *size_specifier() { return "h"; }
};

template<>
struct ptype_treats<unsigned short>
{
	static unsigned short cast(unsigned short x) { return x; }
	static const bool is_signed = false;
	static const char *size_specifier() { return "h"; }
};

template<>
struct ptype_treats<unsigned int>
{
	static unsigned int cast(unsigned int x) { return x; }
	static const bool is_signed = false;
	static const char *size_specifier() { return ""; }
};

template<>
struct ptype_treats<unsigned long>
{
	static unsigned long cast(unsigned long x) { return x; }
	static const bool is_signed = false;
	static const char *size_specifier() { return "l"; }
};

template<>
struct ptype_treats<unsigned long long>
{
	static unsigned long long cast(unsigned long long x) { return x; }
	static const bool is_signed = false;
	static const char *size_specifier() { return "ll"; }
};

template <typename P>
class pformat_base
{
public:

	virtual ~pformat_base() { }

	ATTR_COLD P &operator ()(const double x, const char *f = "") { format_element(f, "", "f", x); return static_cast<P &>(*this); }
	ATTR_COLD P &          e(const double x, const char *f = "") { format_element(f, "", "e", x); return static_cast<P &>(*this);  }
	ATTR_COLD P &          g(const double x, const char *f = "") { format_element(f, "", "g", x); return static_cast<P &>(*this);  }

	ATTR_COLD P &operator ()(const char *x, const char *f = "") { format_element(f, "", "s", x); return static_cast<P &>(*this);  }
	ATTR_COLD P &operator ()(char *x, const char *f = "") { format_element(f, "", "s", x); return static_cast<P &>(*this);  }
	ATTR_COLD P &operator ()(const void *x, const char *f = "") { format_element(f, "", "p", x); return static_cast<P &>(*this);  }
	ATTR_COLD P &operator ()(const pstring &x, const char *f = "") { format_element(f, "", "s", x.cstr() ); return static_cast<P &>(*this);  }

	template<typename T>
	ATTR_COLD P &operator ()(const T x, const char *f = "")
	{
		if (ptype_treats<T>::is_signed)
			format_element(f, ptype_treats<T>::size_specifier(), "d", ptype_treats<T>::cast(x));
		else
			format_element(f, ptype_treats<T>::size_specifier(), "u", ptype_treats<T>::cast(x));
		return static_cast<P &>(*this);
	}

	template<typename T>
	ATTR_COLD P &x(const T x, const char *f = "")
	{
		format_element(f, ptype_treats<T>::size_specifier(), "x", x);
		return static_cast<P &>(*this);
	}

	template<typename T>
	ATTR_COLD P &o(const T x, const char *f = "")
	{
		format_element(f, ptype_treats<T>::size_specifier(), "o", x);
		return static_cast<P &>(*this);
	}

protected:

	virtual void format_element(const char *f, const char *l, const char *fmt_spec, ...) = 0;

};

class pfmt : public pformat_base<pfmt>
{
public:
	pfmt(const pstring &fmt);
	pfmt(const char *fmt);
	virtual ~pfmt();

	operator pstring() const { return m_str; }

	const char *cstr() { return m_str; }


protected:
	void format_element(const char *f, const char *l, const char *fmt_spec, ...);

private:

	char *m_str;
	char m_str_buf[256];
	unsigned m_allocated;
	unsigned m_arg;
};

P_ENUM(plog_level,
	DEBUG,
	INFO,
	VERBOSE,
	WARNING,
	ERROR,
	FATAL)

class plog_dispatch_intf;

template <bool build_enabled = true>
class pfmt_writer_t
{
public:
	pfmt_writer_t() : m_enabled(true)  { }
	virtual ~pfmt_writer_t() { }

	ATTR_COLD void operator ()(const char *fmt) const
	{
		if (build_enabled && m_enabled) vdowrite(fmt);
	}

	template<typename T1>
	ATTR_COLD void operator ()(const char *fmt, const T1 &v1) const
	{
		if (build_enabled && m_enabled) vdowrite(pfmt(fmt)(v1));
	}

	template<typename T1, typename T2>
	ATTR_COLD void operator ()(const char *fmt, const T1 &v1, const T2 &v2) const
	{
		if (build_enabled && m_enabled) vdowrite(pfmt(fmt)(v1)(v2));
	}

	template<typename T1, typename T2, typename T3>
	ATTR_COLD void operator ()(const char *fmt, const T1 &v1, const T2 &v2, const T3 &v3) const
	{
		if (build_enabled && m_enabled) vdowrite(pfmt(fmt)(v1)(v2)(v3));
	}

	template<typename T1, typename T2, typename T3, typename T4>
	ATTR_COLD void operator ()(const char *fmt, const T1 &v1, const T2 &v2, const T3 &v3, const T4 &v4) const
	{
		if (build_enabled && m_enabled) vdowrite(pfmt(fmt)(v1)(v2)(v3)(v4));
	}

	template<typename T1, typename T2, typename T3, typename T4, typename T5>
	ATTR_COLD void operator ()(const char *fmt, const T1 &v1, const T2 &v2, const T3 &v3, const T4 &v4, const T5 &v5) const
	{
		if (build_enabled && m_enabled) vdowrite(pfmt(fmt)(v1)(v2)(v3)(v4)(v5));
=======
struct ptype_traits<char> : ptype_traits_base<char>
{
	static const char *size_spec() { return "h"; }
	static char32_t fmt_spec() { return is_signed ? 'd' : 'u'; }
};

template<>
struct ptype_traits<short> : ptype_traits_base<short>
{
	static const char *size_spec() { return "h"; }
	static char32_t fmt_spec() { return 'd'; }
};

template<>
struct ptype_traits<int> : ptype_traits_base<int>
{
	static char32_t fmt_spec() { return 'd'; }
};

template<>
struct ptype_traits<long> : ptype_traits_base<long>
{
	static const char *size_spec() { return "l"; }
	static char32_t fmt_spec() { return 'd'; }
};

template<>
struct ptype_traits<long long> : ptype_traits_base<long long>
{
	static const char *size_spec() { return "ll"; }
	static char32_t fmt_spec() { return 'd'; }
};

template<>
struct ptype_traits<signed char> : ptype_traits_base<signed char>
{
	static const char *size_spec() { return "h"; }
	static char32_t fmt_spec() { return 'd'; }
};

template<>
struct ptype_traits<unsigned char> : ptype_traits_base<unsigned char>
{
	static const char *size_spec() { return "h"; }
	static char32_t fmt_spec() { return 'u'; }
};

template<>
struct ptype_traits<unsigned short> : ptype_traits_base<unsigned short>
{
	static const char *size_spec() { return "h"; }
	static char32_t fmt_spec() { return 'u'; }
};

template<>
struct ptype_traits<unsigned int> : ptype_traits_base<unsigned int>
{
	static char32_t fmt_spec() { return 'u'; }
};

template<>
struct ptype_traits<unsigned long> : ptype_traits_base<unsigned long>
{
	static const char *size_spec() { return "l"; }
	static char32_t fmt_spec() { return 'u'; }
};

template<>
struct ptype_traits<unsigned long long> : ptype_traits_base<unsigned long long>
{
	static const char *size_spec() { return "ll"; }
	static char32_t fmt_spec() { return 'u'; }
};

template<>
struct ptype_traits<float> : ptype_traits_base<float>
{
	static char32_t fmt_spec() { return 'f'; }
};

template<>
struct ptype_traits<double> : ptype_traits_base<double>
{
	static char32_t fmt_spec() { return 'f'; }
};


template<>
struct ptype_traits<char *> : ptype_traits_base<char *>
{
	static const char *cast(const char *x) { return x; }
	static char32_t fmt_spec() { return 's'; }
};

class pfmt
{
public:
	explicit pfmt(const pstring &fmt)
	: m_str(fmt), m_arg(0)
	{
	}

	pfmt(const pfmt &rhs) : m_str(rhs.m_str), m_arg(rhs.m_arg) { }

	~pfmt()
	{
	}

	operator pstring() const { return m_str; }
	pfmt &          e(const double &x) {return format_element("", 'e', x);  }
	pfmt &          g(const double &x) {return format_element("", 'g', x);  }

	pfmt &          e(const float &x) {return format_element("", 'e', static_cast<double>(x));  }
	pfmt &          g(const float &x) {return format_element("", 'g', static_cast<double>(x));  }

	pfmt &operator ()(const void *x) {return format_element("", 'p', x);  }
	pfmt &operator ()(const pstring &x) {return format_element("", 's', x.c_str() );  }

	template<typename T>
	pfmt &operator ()(const T &x)
	{
		return format_element(ptype_traits<T>::size_spec(), ptype_traits<T>::fmt_spec(), ptype_traits<T>::cast(x));
	}

	template<typename T>
	pfmt &operator ()(const T *x)
	{
		return format_element(ptype_traits<T *>::size_spec(), ptype_traits<T *>::fmt_spec(), ptype_traits<T *>::cast(x));
	}

	template<typename T>
	pfmt &x(const T &x)
	{
		return format_element(ptype_traits<T>::size_spec(), 'x', x);
	}

	template<typename T>
	pfmt &o(const T &x)
	{
		return format_element(ptype_traits<T>::size_spec(), 'o', x);
	}

protected:

	pfmt &format_element(const char *l, const unsigned fmt_spec, ...);

private:

	pstring m_str;
	unsigned m_arg;
};

template <class T, bool build_enabled = true>
class pfmt_writer_t : plib::nocopyassignmove
{
public:
	explicit pfmt_writer_t() : m_enabled(true)  { }

	/* runtime enable */
	template<bool enabled, typename... Args>
	void log(const pstring & fmt, Args&&... args) const
	{
		if (build_enabled && enabled && m_enabled)
		{
			pfmt pf(fmt);
			static_cast<T *>(this)->vdowrite(xlog(pf, std::forward<Args>(args)...));
		}
	}

	template<typename... Args>
	void operator ()(const pstring &fmt, Args&&... args) const
	{
		if (build_enabled && m_enabled)
		{
			pfmt pf(fmt);
			static_cast<const T *>(this)->vdowrite(xlog(pf, std::forward<Args>(args)...));
		}
>>>>>>> upstream/master
	}

	void set_enabled(const bool v)
	{
		m_enabled = v;
	}

	bool is_enabled() const { return m_enabled; }

protected:
<<<<<<< HEAD
	virtual void vdowrite(const pstring &ls) const {}

private:
=======
	~pfmt_writer_t() { }

private:
	pfmt &xlog(pfmt &fmt) const { return fmt; }

	template<typename X, typename... Args>
	pfmt &xlog(pfmt &fmt, X&& x, Args&&... args) const
	{
		return xlog(fmt(std::forward<X>(x)), std::forward<Args>(args)...);
	}

>>>>>>> upstream/master
	bool m_enabled;

};

<<<<<<< HEAD
template <plog_level::e L, bool build_enabled = true>
class plog_channel : public pfmt_writer_t<build_enabled>
{
public:
	plog_channel(plog_dispatch_intf *b) : pfmt_writer_t<build_enabled>(),  m_base(b) { }
	virtual ~plog_channel() { }

protected:
	virtual void vdowrite(const pstring &ls) const;

private:
	plog_dispatch_intf *m_base;
};

class plog_dispatch_intf
{
	template<plog_level::e, bool> friend class plog_channel;

public:
	virtual ~plog_dispatch_intf() { }
protected:
	virtual void vlog(const plog_level &l, const pstring &ls) const = 0;
};

template<bool debug_enabled>
=======
template <class T, plog_level::E L, bool build_enabled = true>
class plog_channel : public pfmt_writer_t<plog_channel<T, L, build_enabled>, build_enabled>
{
	friend class pfmt_writer_t<plog_channel<T, L, build_enabled>, build_enabled>;
public:
	explicit plog_channel(T &b) : pfmt_writer_t<plog_channel, build_enabled>(), m_base(b) { }
	~plog_channel() { }

protected:
	void vdowrite(const pstring &ls) const
	{
		m_base.vlog(L, ls);
	}

private:
	T &m_base;
};

template<class T, bool debug_enabled>
>>>>>>> upstream/master
class plog_base
{
public:

<<<<<<< HEAD
	plog_base(plog_dispatch_intf *proxy)
=======
	explicit plog_base(T &proxy)
>>>>>>> upstream/master
	: debug(proxy),
		info(proxy),
		verbose(proxy),
		warning(proxy),
		error(proxy),
		fatal(proxy)
	{}
<<<<<<< HEAD
	virtual ~plog_base() {};

	plog_channel<plog_level::DEBUG, debug_enabled> debug;
	plog_channel<plog_level::INFO> info;
	plog_channel<plog_level::VERBOSE> verbose;
	plog_channel<plog_level::WARNING> warning;
	plog_channel<plog_level::ERROR> error;
	plog_channel<plog_level::FATAL> fatal;
};


template <plog_level::e L, bool build_enabled>
void plog_channel<L, build_enabled>::vdowrite(const pstring &ls) const
{
	m_base->vlog(L, ls);
}

#endif /* _PSTRING_H_ */
=======
	virtual ~plog_base() {}

	plog_channel<T, plog_level::DEBUG, debug_enabled> debug;
	plog_channel<T, plog_level::INFO> info;
	plog_channel<T, plog_level::VERBOSE> verbose;
	plog_channel<T, plog_level::WARNING> warning;
	plog_channel<T, plog_level::ERROR> error;
	plog_channel<T, plog_level::FATAL> fatal;
};

}

template<typename T>
plib::pfmt& operator<<(plib::pfmt &p, T&& val) { return p(std::forward<T>(val)); }

#endif /* PSTRING_H_ */
>>>>>>> upstream/master
