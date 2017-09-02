// license:BSD-3-Clause
// copyright-holders:Aaron Giles
//============================================================
//
<<<<<<< HEAD
//  strconv.c - Win32 string conversion
//
//============================================================

#if defined(SDLMAME_WIN32) || defined(OSD_WINDOWS)
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif

// MAMEOS headers
#include "strconv.h"

#if defined(SDLMAME_WIN32) || defined(OSD_WINDOWS)
//============================================================
//  LOCAL VARIABLES
//============================================================

static int ansi_codepage = CP_ACP;


//============================================================
//  set_osdcore_acp
//============================================================

void set_osdcore_acp(int cp)
{
	//TODO: check specified cp is valid
	//ansi_codepage = cp;
	ansi_codepage = CP_OEMCP;
=======
//  strconv.cpp - Win32 string conversion
//
//============================================================
#if defined(SDLMAME_WIN32) || defined(OSD_WINDOWS) || defined(OSD_UWP)
#include <windows.h>
#endif
#include <algorithm>
#include <assert.h>
// MAMEOS headers
#include "strconv.h"

#if defined(SDLMAME_WIN32) || defined(OSD_WINDOWS) || defined(OSD_UWP)

namespace
{
	// class designed to provide inputs to WideCharToMultiByte() and MultiByteToWideChar()
	template<typename T>
	class string_source
	{
	public:
		string_source(const T *str) : m_str(str), m_char_count(-1)
		{
			assert(str);
		}

		string_source(const std::basic_string<T> &str) : m_str(str.c_str()), m_char_count((int)str.size() + 1)
		{
		}

		const T *string() const { return m_str; };  // returns pointer to actual characters
		int char_count() const { return m_char_count; }     // returns the character count (including NUL terminater), or -1 if NUL terminated

	private:
		const T *m_str;
		int m_char_count;
	};
};

namespace osd {
namespace text {

//============================================================
//  mbstring_from_wstring
//============================================================

static std::string &mbstring_from_wstring(std::string &dst, UINT code_page, const string_source<wchar_t> &src)
{
	// convert UTF-16 to the specified code page
	int dst_char_count = WideCharToMultiByte(code_page, 0, src.string(), src.char_count(), nullptr, 0, nullptr, nullptr);
	dst.resize(dst_char_count - 1);
	WideCharToMultiByte(code_page, 0, src.string(), src.char_count(), &dst[0], dst_char_count, nullptr, nullptr);

	return dst;
}


//============================================================
//  wstring_from_mbstring
//============================================================

static std::wstring &wstring_from_mbstring(std::wstring &dst, const string_source<char> &src, UINT code_page)
{
	// convert multibyte string (in specified code page) to UTF-16
	int dst_char_count = MultiByteToWideChar(code_page, 0, src.string(), src.char_count(), nullptr, 0);
	dst.resize(dst_char_count - 1);
	MultiByteToWideChar(CP_UTF8, 0, src.string(), src.char_count(), &dst[0], dst_char_count - 1);

	return dst;
>>>>>>> upstream/master
}


//============================================================
<<<<<<< HEAD
//  get_osdcore_acp
//============================================================

int get_osdcore_acp(void)
{
	return ansi_codepage;
}


//============================================================
//  astring_from_utf8
//============================================================

CHAR *astring_from_utf8(const char *utf8string)
{
	WCHAR *wstring;
	int char_count;
	CHAR *result;

	// convert MAME string (UTF-8) to UTF-16
	char_count = MultiByteToWideChar(CP_UTF8, 0, utf8string, -1, NULL, 0);
	wstring = (WCHAR *)alloca(char_count * sizeof(*wstring));
	MultiByteToWideChar(CP_UTF8, 0, utf8string, -1, wstring, char_count);

	// convert UTF-16 to "ANSI code page" string
	char_count = WideCharToMultiByte(CP_ACP, 0, wstring, -1, NULL, 0, NULL, NULL);
	result = (CHAR *)osd_malloc_array(char_count * sizeof(*result));
	if (result != NULL)
		WideCharToMultiByte(CP_ACP, 0, wstring, -1, result, char_count, NULL, NULL);

=======
//  to_astring
//============================================================

std::string &to_astring(std::string &dst, const std::string &s)
{
	// convert MAME string (UTF-8) to UTF-16
	std::wstring wstring = to_wstring(s);

	// convert UTF-16 to "ANSI code page" string
	return mbstring_from_wstring(dst, CP_ACP, string_source<wchar_t>(wstring));
}



//============================================================
//  to_astring
//============================================================

std::string &to_astring(std::string &dst, const char *s)
{
	// convert MAME string (UTF-8) to UTF-16
	std::wstring wstring = to_wstring(s);

	// convert UTF-16 to "ANSI code page" string
	return mbstring_from_wstring(dst, CP_ACP, string_source<wchar_t>(wstring));
}


//============================================================
//  to_astring
//============================================================

std::string to_astring(const std::string &s)
{
	std::string result;
	to_astring(result, s);
	return result;
}


//============================================================
//  to_astring
//============================================================

std::string to_astring(const char *s)
{
	std::string result;
	to_astring(result, s);
>>>>>>> upstream/master
	return result;
}


//============================================================
<<<<<<< HEAD
//  utf8_from_astring
//============================================================

char *utf8_from_astring(const CHAR *astring)
{
	WCHAR *wstring;
	int char_count;
	CHAR *result;

	// convert "ANSI code page" string to UTF-16
	char_count = MultiByteToWideChar(CP_ACP, 0, astring, -1, NULL, 0);
	wstring = (WCHAR *)alloca(char_count * sizeof(*wstring));
	MultiByteToWideChar(CP_ACP, 0, astring, -1, wstring, char_count);

	// convert UTF-16 to MAME string (UTF-8)
	char_count = WideCharToMultiByte(CP_UTF8, 0, wstring, -1, NULL, 0, NULL, NULL);
	result = (CHAR *)osd_malloc_array(char_count * sizeof(*result));
	if (result != NULL)
		WideCharToMultiByte(CP_UTF8, 0, wstring, -1, result, char_count, NULL, NULL);

=======
//  from_astring
//============================================================

std::string &from_astring(std::string &dst, const std::string &s)
{
	// convert "ANSI code page" string to UTF-16
	std::wstring wstring;
	wstring_from_mbstring(wstring, string_source<char>(s), CP_ACP);

	// convert UTF-16 to MAME string (UTF-8)
	return from_wstring(dst, wstring);
}


//============================================================
//  from_astring
//============================================================

std::string &from_astring(std::string &dst, const CHAR *s)
{
	// convert "ANSI code page" string to UTF-16
	std::wstring wstring;
	wstring_from_mbstring(wstring, string_source<char>(s), CP_ACP);

	// convert UTF-16 to MAME string (UTF-8)
	return from_wstring(dst, wstring);
}


//============================================================
//  from_astring
//============================================================

std::string from_astring(const std::string &s)
{
	std::string result;
	from_astring(result, s);
>>>>>>> upstream/master
	return result;
}


//============================================================
<<<<<<< HEAD
//  wstring_from_utf8
//============================================================

WCHAR *wstring_from_utf8(const char *utf8string)
{
	int char_count;
	WCHAR *result;

	// convert MAME string (UTF-8) to UTF-16
	char_count = MultiByteToWideChar(CP_UTF8, 0, utf8string, -1, NULL, 0);
	result = (WCHAR *)osd_malloc_array(char_count * sizeof(*result));
	if (result != NULL)
		MultiByteToWideChar(CP_UTF8, 0, utf8string, -1, result, char_count);

=======
//  from_astring
//============================================================

std::string from_astring(const CHAR *s)
{
	std::string result;
	from_astring(result, s);
	return result;
}


//============================================================
//  to_wstring
//============================================================

std::wstring &to_wstring(std::wstring &dst, const std::string &s)
{
	// convert MAME string (UTF-8) to UTF-16
	return wstring_from_mbstring(dst, string_source<char>(s), CP_UTF8);
}


//============================================================
//  to_wstring
//============================================================

std::wstring &to_wstring(std::wstring &dst, const char *s)
{
	// convert MAME string (UTF-8) to UTF-16
	return wstring_from_mbstring(dst, string_source<char>(s), CP_UTF8);
}


//============================================================
//  to_wstring
//============================================================

std::wstring to_wstring(const std::string &s)
{
	std::wstring result;
	to_wstring(result, s);
>>>>>>> upstream/master
	return result;
}


//============================================================
<<<<<<< HEAD
//  utf8_from_wstring
//============================================================

char *utf8_from_wstring(const WCHAR *wstring)
{
	int char_count;
	char *result;

	// convert UTF-16 to MAME string (UTF-8)
	char_count = WideCharToMultiByte(CP_UTF8, 0, wstring, -1, NULL, 0, NULL, NULL);
	result = (char *)osd_malloc_array(char_count * sizeof(*result));
	if (result != NULL)
		WideCharToMultiByte(CP_UTF8, 0, wstring, -1, result, char_count, NULL, NULL);

	return result;
}

=======
//  to_wstring
//============================================================

std::wstring to_wstring(const char *s)
{
	std::wstring result;
	to_wstring(result, s);
	return result;
}


//============================================================
//  from_wstring
//============================================================

std::string &from_wstring(std::string &dst, const std::wstring &s)
{
	// convert UTF-16 to MAME string (UTF-8)
	return mbstring_from_wstring(dst, CP_UTF8, string_source<wchar_t>(s));
}


//============================================================
//  from_wstring
//============================================================

std::string &from_wstring(std::string &dst, const WCHAR *s)
{
	// convert UTF-16 to MAME string (UTF-8)
	return mbstring_from_wstring(dst, CP_UTF8, string_source<wchar_t>(s));
}


//============================================================
//  from_wstring
//============================================================

std::string from_wstring(const std::wstring &s)
{
	std::string result;
	from_wstring(result, s);
	return result;
}


//============================================================
//  from_wstring
//============================================================

std::string from_wstring(const WCHAR *s)
{
	std::string result;
	from_wstring(result, s);
	return result;
}

}; // namespace text
}; // namespace osd


>>>>>>> upstream/master
//============================================================
//  osd_uchar_from_osdchar
//============================================================

<<<<<<< HEAD
int osd_uchar_from_osdchar(UINT32 *uchar, const char *osdchar, size_t count)
{
	WCHAR wch;

	count = MIN(count, IsDBCSLeadByte(*osdchar) ? 2 : 1);
	if (MultiByteToWideChar(CP_ACP, 0, osdchar, (DWORD)count, &wch, 1) != 0)
		*uchar = wch;
	else
		*uchar = 0;
	return (int) count;
}

=======
int osd_uchar_from_osdchar(char32_t *uchar, const char *osdchar, size_t count)
{
	WCHAR wch;
	CPINFO cp;

	if (!GetCPInfo(CP_ACP, &cp))
		goto error;

	// The multibyte char can't be bigger than the max character size
	count = std::min(count, size_t(cp.MaxCharSize));

	if (MultiByteToWideChar(CP_ACP, 0, osdchar, static_cast<DWORD>(count), &wch, 1) == 0)
		goto error;

	*uchar = wch;
	return static_cast<int>(count);

error:
	*uchar = 0;
	return static_cast<int>(count);
}


>>>>>>> upstream/master
#else
#include "unicode.h"
//============================================================
//  osd_uchar_from_osdchar
//============================================================

<<<<<<< HEAD
int osd_uchar_from_osdchar(unicode_char *uchar, const char *osdchar, size_t count)
=======
int osd_uchar_from_osdchar(char32_t *uchar, const char *osdchar, size_t count)
>>>>>>> upstream/master
{
	wchar_t wch;

	count = mbstowcs(&wch, (char *)osdchar, 1);
	if (count != -1)
		*uchar = wch;
	else
		*uchar = 0;

	return count;
}

#endif
