// license:BSD-3-Clause
// copyright-holders:Aaron Giles
//============================================================
//
//  strconv.h - String conversion
//
//============================================================

<<<<<<< HEAD
#ifndef __OSD_STRCONV__
#define __OSD_STRCONV__
=======
#ifndef MAME_OSD_STRCONV_H
#define MAME_OSD_STRCONV_H
>>>>>>> upstream/master

#include "osdcore.h"



//============================================================
//  FUNCTION PROTOTYPES
//============================================================

<<<<<<< HEAD
#if defined(SDLMAME_WIN32) || defined(OSD_WINDOWS)

#if defined(SDLMAME_WIN32)
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif
// the result of these functions has to be released with osd_free()

CHAR *astring_from_utf8(const char *s);
char *utf8_from_astring(const CHAR *s);

WCHAR *wstring_from_utf8(const char *s);
char *utf8_from_wstring(const WCHAR *s);

#ifdef UNICODE
#define tstring_from_utf8   wstring_from_utf8
#define utf8_from_tstring   utf8_from_wstring
#else // !UNICODE
#define tstring_from_utf8   astring_from_utf8
#define utf8_from_tstring   utf8_from_astring
#endif // UNICODE

#endif //SDLMAME_WIN32


#endif // __OSD_STRCONV__
=======
#if defined(WIN32)

#include <windows.h>

namespace osd
{
	namespace text
	{
		std::string to_astring(const std::string &s);
		std::string to_astring(const char *s);
		std::string &to_astring(std::string &dst, const std::string &s);
		std::string &to_astring(std::string &dst, const char *s);
		std::string from_astring(const std::string &s);
		std::string from_astring(const CHAR *s);
		std::string &from_astring(std::string &dst, const std::string &s);
		std::string &from_astring(std::string &dst, const CHAR *s);

		std::wstring to_wstring(const std::string &s);
		std::wstring to_wstring(const char *s);
		std::wstring &to_wstring(std::wstring &dst, const std::string &s);
		std::wstring &to_wstring(std::wstring &dst, const char *s);
		std::string from_wstring(const std::wstring &s);
		std::string from_wstring(const WCHAR *s);
		std::string &from_wstring(std::string &dst, const std::wstring &s);
		std::string &from_wstring(std::string &dst, const WCHAR *s);

#ifdef UNICODE
typedef std::wstring tstring;
#define to_tstring   to_wstring
#define from_tstring   from_wstring
#else // !UNICODE
typedef std::string tstring;
#define to_tstring   to_astring
#define from_tstring   from_astring
#endif // UNICODE

	}
}

#endif // defined(WIN32)


#endif // MAME_OSD_STRCONV_H
>>>>>>> upstream/master
