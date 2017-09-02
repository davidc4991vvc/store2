// license:BSD-3-Clause
// copyright-holders:Nathan Woods
/***************************************************************************

<<<<<<< HEAD
    charconv.c
=======
    charconv.cpp
>>>>>>> upstream/master

    Imgtool character set conversion routines.

***************************************************************************/

#include "corestr.h"
#include "charconv.h"
<<<<<<< HEAD


/*-------------------------------------------------
    utf8_from_latin1 - convert an ISO-8859-1
    character sequence to an UTF-8 string
-------------------------------------------------*/

static char *utf8_from_latin1(const char *src)
{
	char *buffer, *bufptr;

	/* validate input */
	if (!src)
	{
		return NULL;
	}

	/* allocate space for result, twice the source len to be safe */
	buffer = (char *) osd_malloc(strlen(src) * 2 + 1);

	/* point to the start */
	bufptr = buffer;

	do
	{
		unsigned char c = *src;

		if (c < 0x80)
		{
			*bufptr++ = c;
		}
		else if (c < 0xc0)
		{
			*bufptr++ = '\xc2';
			*bufptr++ = c;
		}
		else
		{
			*bufptr++ = '\xc3';
			*bufptr++ = c - 0x40;
		}
	} while (*src++);

	return buffer;
}


/*-------------------------------------------------
    latin1_from_utf8 - convert an UTF-8
    character sequence to an ISO-8859-1 string
-------------------------------------------------*/

static char *latin1_from_utf8(const char *src)
{
	char *buffer, *bufptr;

	/* validate input */
	if (!src)
	{
		return NULL;
	}

	/* allocate space for result */
	buffer = (char *) osd_malloc(strlen(src) + 1);

	/* point to the start */
	bufptr = buffer;

	do
	{
		unsigned char c = *src;

		if (c < 0x80)
		{
			*bufptr++ = c;
		}
		else if (c == 0xc2)
		{
			c = *++src;
			*bufptr++ = c;
		}
		else if (c == 0xc3)
		{
			c = *++src;
			*bufptr++ = c + 0x40;
		}
		else
		{
			/* conversion failed */
			*bufptr++ = '\0';
			break;
		}
	} while(*src++);

	return buffer;
}


/*-------------------------------------------------
    utf8_from_native - convert specified character
    sequence to an UTF-8 string
-------------------------------------------------*/

char *utf8_from_native(imgtool_charset charset, const char *src)
{
	char *result;

	switch (charset)
	{
		case IMGTOOL_CHARSET_UTF8:
			result = core_strdup(src);
			break;

		case IMGTOOL_CHARSET_ISO_8859_1:
			result = utf8_from_latin1(src);
			break;

		default:
			result = NULL;
			break;
	}
	return result;
}


/*-------------------------------------------------
    native_from_utf8 - convert an UTF-8 string
    to specified character set
-------------------------------------------------*/

char *native_from_utf8(imgtool_charset charset, const char *src)
{
	char *result;

	switch (charset)
	{
		case IMGTOOL_CHARSET_UTF8:
			result = core_strdup(src);
			break;

		case IMGTOOL_CHARSET_ISO_8859_1:
			result = latin1_from_utf8(src);
			break;

		default:
			result = NULL;
			break;
	}
	return result;
=======
#include "unicode.h"
#include "coretmpl.h"

imgtool::simple_charconverter imgtool::charconverter_iso_8859_1(nullptr, nullptr);


//-------------------------------------------------
//  from_utf8
//-------------------------------------------------

void imgtool::charconverter::from_utf8(std::ostream &dest, const std::string &src) const
{
	from_utf8(dest, src.c_str(), src.size());
}


//-------------------------------------------------
//  to_utf8
//-------------------------------------------------

void imgtool::charconverter::to_utf8(std::ostream &dest, const std::string &src) const
{
	to_utf8(dest, src.c_str(), src.size());
}


//-------------------------------------------------
//  simple_charconverter::simple_charconverter
//-------------------------------------------------

imgtool::simple_charconverter::simple_charconverter(const char32_t lowpage[0x80], const char32_t highpage[0x80], unicode_normalization_form norm)
	: m_norm(norm), m_lowpage(lowpage), m_highpage(highpage)
{
	// build the reverse lookup table
	for (int i = 0; i < 256; i++)
	{
		const char32_t *page = i >= 128 ? m_highpage : m_lowpage;
		char32_t unicode_char = page ? page[i % 128] : i;
		m_reverse_lookup.emplace_back(unicode_char, (char)i);
	}

	// and sort it
	std::sort(m_reverse_lookup.begin(), m_reverse_lookup.end(), [](const std::pair<char32_t, char> &a, const std::pair<char32_t, char> &b)
	{
		return b.first > a.first;
	});
}


//-------------------------------------------------
//  from_utf8
//-------------------------------------------------

void imgtool::simple_charconverter::from_utf8(std::ostream &dest, const char *src, size_t src_length) const
{
	// normalize the incoming unicode
	std::string normalized_src = normalize_unicode(src, src_length, m_norm);

	auto iter = normalized_src.begin();
	while (iter != normalized_src.end())
	{
		// get the next character
		char32_t ch;
		int rc = uchar_from_utf8(&ch, &*iter, normalized_src.end() - iter);
		if (rc < 0)
		{
			ch = 0xFFFD;
			rc = 1;
		}
		iter += rc;

		// do the reverse lookup
		auto lookup = std::lower_bound(m_reverse_lookup.begin(), m_reverse_lookup.end(), ch, [](const std::pair<char32_t, char> &a, const char32_t &b)
		{
			return a.first < b;
		});
		if (lookup == m_reverse_lookup.end())
			throw charconverter_exception();

		// and output the results
		dest << lookup->second;
	}
}


//-------------------------------------------------
//  to_utf8
//-------------------------------------------------

void imgtool::simple_charconverter::to_utf8(std::ostream &dest, const char *src, size_t src_length) const
{
	for (size_t i = 0; i < src_length; i++)
	{
		// which page is this in?
		const char32_t *page = ((src[i] & 0x80) == 0) ? m_lowpage : m_highpage;

		// is this page present?
		if ((src[i] & 0x80) == 0)
		{
			// no - pass it on
			dest << src[i];
		}
		else
		{
			// yes - we need to do a lookup
			size_t base = ((src[i] & 0x80) == 0) ? 0x00 : 0x80;
			char32_t ch = page[((unsigned char)(src[i])) - base];
			if (ch == 0)
				throw charconverter_exception();

			dest << utf8_from_uchar(ch);
		}
	}
>>>>>>> upstream/master
}
