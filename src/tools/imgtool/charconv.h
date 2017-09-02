// license:BSD-3-Clause
// copyright-holders:Nathan Woods
/***************************************************************************

    charconv.h

    Imgtool character set conversion routines.

***************************************************************************/


<<<<<<< HEAD
#ifndef __CHARCONV_H__
#define __CHARCONV_H__


/* Supported character sets */
enum imgtool_charset
{
	IMGTOOL_CHARSET_UTF8,
	IMGTOOL_CHARSET_ISO_8859_1,
};


/* Convert specified charset to UTF-8 */
char *utf8_from_native(imgtool_charset charset, const char *src);

/* Convert UTF-8 string to specified charset */
char *native_from_utf8(imgtool_charset charset, const char *src);


#endif /* __CHARCONV_H__ */
=======
#ifndef IMGTOOL_CHARCONV_H
#define IMGTOOL_CHARCONV_H

#include "unicode.h"

namespace imgtool
{
	// ======================> charconverter

	// abstract base class for character conversions
	class charconverter
	{
	public:
		virtual void from_utf8(std::ostream &dest, const char *src, size_t src_length) const = 0;
		virtual void to_utf8(std::ostream &dest, const char *src, size_t src_length) const = 0;

		void from_utf8(std::ostream &dest, const std::string &src) const;
		void to_utf8(std::ostream &dest, const std::string &src) const;

		std::string from_utf8(const std::string &src) const
		{
			// inlining so that the return value can potentially be removed by return value optimization
			std::ostringstream stream;
			from_utf8(stream, src);
			return stream.str();
		}

		std::string to_utf8(const std::string &src) const
		{
			// inlining so that the return value can potentially be removed by return value optimization
			std::ostringstream stream;
			to_utf8(stream, src);
			return stream.str();
		}

	};

	// ======================> simple_charconverter

	// a simple implementation of charconverter that simply defines a code page for 0x80-0xFF
	class simple_charconverter : public charconverter
	{
	public:
		simple_charconverter(const char32_t highpage[0x80], unicode_normalization_form norm = unicode_normalization_form::C)
			: simple_charconverter(nullptr, highpage, norm)
		{
		}

		simple_charconverter(const char32_t lowpage[0x80], const char32_t highpage[0x80], unicode_normalization_form norm = unicode_normalization_form::C);

		virtual void from_utf8(std::ostream &dest, const char *src, size_t src_length) const override;
		virtual void to_utf8(std::ostream &dest, const char *src, size_t src_length) const override;

	private:
		std::vector<std::pair<char32_t, char> > m_reverse_lookup;
		unicode_normalization_form m_norm;
		const char32_t *m_lowpage;
		const char32_t *m_highpage;
	};

	// exception that can be thrown from charconverter::from_utf8() if a character is illegal (charconverter::to_utf8() should never throw this)
	class charconverter_exception
	{
	};

	extern simple_charconverter charconverter_iso_8859_1;
};


#endif // IMGTOOL_CHARCONV_H
>>>>>>> upstream/master
