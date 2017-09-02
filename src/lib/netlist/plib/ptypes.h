// license:GPL-2.0+
// copyright-holders:Couriersud
/*
 * ptypes.h
 *
 */

#ifndef PTYPES_H_
#define PTYPES_H_

#include "pconfig.h"
#include "pstring.h"

<<<<<<< HEAD
//============================================================
//  penum - strongly typed enumeration
//============================================================

struct penum_base
{
protected:
	static int from_string_int(const char *str, const char *x)
	{
		int cnt = 0;
		const char *cur = str;
		int lx = strlen(x);
		while (*str)
		{
			if (*str == ',')
			{
				int l = str-cur;
				if (l == lx)
					if (strncmp(cur, x, lx) == 0)
						return cnt;
			}
			else if (*str == ' ')
			{
				cur = str + 1;
				cnt++;
			}
			str++;
		}
		int l = str-cur;
		if (l == lx)
			if (strncmp(cur, x, lx) == 0)
				return cnt;
		return -1;
	}
	static pstring nthstr(int n, const char *str)
	{
		char buf[64];
		char *bufp = buf;
		int cur = 0;
		while (*str)
		{
			if (cur == n)
			{
				if (*str == ',')
				{
					*bufp = 0;
					return pstring(buf);
				}
				else if (*str != ' ')
					*bufp++ = *str;
			}
			else
			{
				if (*str == ',')
					cur++;
			}
			str++;
		}
		*bufp = 0;
		return pstring(buf);
	}
};

#define P_ENUM(_name, ...) \
	struct _name : public penum_base { \
		enum e { __VA_ARGS__ }; \
		_name (e v) : m_v(v) { } \
		bool set_from_string (const pstring &s) { \
			static const char *strings = # __VA_ARGS__; \
			int f = from_string_int(strings, s.cstr()); \
			if (f>=0) { m_v = (e) f; return true; } else { return false; } \
		} \
		operator e() const {return m_v;} \
		int as_int() const {return (int) m_v;} \
		bool operator==(const _name &rhs) const {return m_v == rhs.m_v;} \
		bool operator==(const e &rhs) const {return m_v == (int) rhs;} \
		const pstring name() const { \
			static const char *strings = # __VA_ARGS__; \
			return nthstr((int) m_v, strings); \
		} \
		private: e m_v; };
=======
#include <type_traits>
#include <limits>

namespace plib
{
	template<typename T> struct is_integral : public std::is_integral<T> { };
	template<typename T> struct numeric_limits : public std::numeric_limits<T> { };

	/* 128 bit support at least on GCC is not fully supported */
#if PHAS_INT128
	template<> struct is_integral<UINT128> { static constexpr bool value = true; };
	template<> struct is_integral<INT128> { static constexpr bool value = true; };
	template<> struct numeric_limits<UINT128>
	{
		static inline constexpr UINT128 max()
		{
			return ~((UINT128)0);
		}
	};
	template<> struct numeric_limits<INT128>
	{
		static inline constexpr INT128 max()
		{
			return (~((UINT128)0)) >> 1;
		}
	};
#endif

	//============================================================
	// prevent implicit copying
	//============================================================

	struct nocopyassignmove
	{
	protected:
		nocopyassignmove() = default;
		~nocopyassignmove() = default;
	private:
		nocopyassignmove(const nocopyassignmove &) = delete;
		nocopyassignmove(nocopyassignmove &&) = delete;
		nocopyassignmove &operator=(const nocopyassignmove &) = delete;
		nocopyassignmove &operator=(nocopyassignmove &&) = delete;
	};

	struct nocopyassign
	{
	protected:
		nocopyassign() = default;
		~nocopyassign() = default;
	private:
		nocopyassign(const nocopyassign &) = delete;
		nocopyassign &operator=(const nocopyassign &) = delete;
	};

	//============================================================
	//  penum - strongly typed enumeration
	//============================================================

	struct penum_base
	{
	protected:
		static int from_string_int(const char *str, const char *x);
		static pstring nthstr(int n, const char *str);
	};

}

#define P_ENUM(ename, ...) \
	struct ename : public plib::penum_base { \
		enum E { __VA_ARGS__ }; \
		ename (E v) : m_v(v) { } \
		bool set_from_string (const pstring &s) { \
			static const char *strings = # __VA_ARGS__; \
			int f = from_string_int(strings, s.c_str()); \
			if (f>=0) { m_v = static_cast<E>(f); return true; } else { return false; } \
		} \
		operator E() const {return m_v;} \
		bool operator==(const ename &rhs) const {return m_v == rhs.m_v;} \
		bool operator==(const E &rhs) const {return m_v == rhs;} \
		const pstring name() const { \
			static const char *strings = # __VA_ARGS__; \
			return nthstr(static_cast<int>(m_v), strings); \
		} \
		private: E m_v; };
>>>>>>> upstream/master


#endif /* PTYPES_H_ */
