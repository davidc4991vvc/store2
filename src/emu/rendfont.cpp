// license:BSD-3-Clause
<<<<<<< HEAD
// copyright-holders:Aaron Giles
=======
// copyright-holders:Aaron Giles, Vas Crabb
>>>>>>> upstream/master
/***************************************************************************

    rendfont.c

    Rendering system font management.

***************************************************************************/

#include "emu.h"
#include "rendfont.h"
#include "emuopts.h"
#include "coreutil.h"

#include "osdepend.h"
<<<<<<< HEAD
#ifdef UI_COLOR_DISPLAY
//mamep: for ui_get_rgb_color()
#include "ui/ui.h"
#endif /* UI_COLOR_DISPLAY */

//mamep: embedded CJK and non-CJK font
#include "uismall11.fh"
#include "uismall14.fh"

//mamep: embedded command glyph
#include "uicmd11.fh"
#include "uicmd14.fh"


//mamep: command.dat symbols assigned to Unicode PUA U+E000
#define COMMAND_UNICODE	(0xe000)
#define MAX_GLYPH_FONT	(150)

#ifdef UI_COLOR_DISPLAY
//mamep: for color glyph
#define COLOR_BUTTONS	(90)
#endif /* UI_COLOR_DISPLAY */


=======
#include "uismall.fh"

#include "ui/uicmd14.fh"
#include "ui/cmddata.h"

#include <algorithm>
#include <cstddef>
#include <cstring>
#include <iterator>
#include <limits>


#define VERBOSE 0

#define LOG(...) do { if (VERBOSE) osd_printf_verbose(__VA_ARGS__); } while (0)


namespace {

template <typename Iterator>
class bdf_helper
{
public:
	bdf_helper(Iterator const &begin, Iterator const &end)
		: m_keyword_begin(begin)
		, m_keyword_end(begin)
		, m_value_begin(begin)
		, m_value_end(begin)
		, m_line_end(begin)
		, m_end(end)
	{
		next_line();
	}

	bool at_end() const { return m_end == m_keyword_begin; }

	void next_line()
	{
		m_keyword_begin = m_line_end;
		while ((m_end != m_keyword_begin) && (('\r' == *m_keyword_begin) || ('\n' == *m_keyword_begin)))
			++m_keyword_begin;

		m_keyword_end = m_keyword_begin;
		while ((m_end != m_keyword_end) && (' ' != *m_keyword_end) && ('\t' != *m_keyword_end) && ('\r' != *m_keyword_end) && ('\n' != *m_keyword_end))
			++m_keyword_end;

		m_value_begin = m_keyword_end;
		while ((m_end != m_value_begin) && ((' ' == *m_value_begin) || ('\t' == *m_value_begin)) && ('\r' != *m_value_begin) && ('\n' != *m_value_begin))
			++m_value_begin;

		m_value_end = m_line_end = m_value_begin;
		while ((m_end != m_line_end) && ('\r' != *m_line_end) && ('\n' != *m_line_end))
		{
			if ((' ' != *m_line_end) && ('\t' != *m_line_end))
				m_value_end = ++m_line_end;
			else
				++m_line_end;
		}
	}

	bool is_keyword(char const *keyword) const
	{
		Iterator pos(m_keyword_begin);
		while (true)
		{
			if (m_keyword_end == pos)
			{
				return '\0' == *keyword;
			}
			else if (('\0' == *keyword) || (*pos != *keyword))
			{
				return false;
			}
			else
			{
				++pos;
				++keyword;
			}
		}
	}

	Iterator const &keyword_begin() const { return m_keyword_begin; }
	Iterator const &keyword_end() const { return m_keyword_end; }
	auto keyword_length() const { return std::distance(m_keyword_begin, m_keyword_end); }

	Iterator const &value_begin() const { return m_value_begin; }
	Iterator const &value_end() const { return m_value_end; }
	auto value_length() const { return std::distance(m_value_begin, m_value_end); }

private:
	Iterator        m_keyword_begin;
	Iterator        m_keyword_end;
	Iterator        m_value_begin;
	Iterator        m_value_end;
	Iterator        m_line_end;
	Iterator const  m_end;
};


class bdc_header
{
public:
	static constexpr unsigned MAJVERSION = 1;
	static constexpr unsigned MINVERSION = 0;

	bool read(emu_file &f)
	{
		return f.read(m_data, sizeof(m_data)) == sizeof(m_data);
	}
	bool write(emu_file &f)
	{
		return f.write(m_data, sizeof(m_data)) == sizeof(m_data);
	}

	bool check_magic() const
	{
		return !std::memcmp(MAGIC, m_data + OFFS_MAGIC, OFFS_MAJVERSION - OFFS_MAGIC);
	}
	unsigned get_major_version() const
	{
		return m_data[OFFS_MAJVERSION];
	}
	unsigned get_minor_version() const
	{
		return m_data[OFFS_MINVERSION];
	}
	u64 get_original_length() const
	{
		return
				(u64(m_data[OFFS_ORIGLENGTH + 0]) << (7 * 8)) |
				(u64(m_data[OFFS_ORIGLENGTH + 1]) << (6 * 8)) |
				(u64(m_data[OFFS_ORIGLENGTH + 2]) << (5 * 8)) |
				(u64(m_data[OFFS_ORIGLENGTH + 3]) << (4 * 8)) |
				(u64(m_data[OFFS_ORIGLENGTH + 4]) << (3 * 8)) |
				(u64(m_data[OFFS_ORIGLENGTH + 5]) << (2 * 8)) |
				(u64(m_data[OFFS_ORIGLENGTH + 6]) << (1 * 8)) |
				(u64(m_data[OFFS_ORIGLENGTH + 7]) << (0 * 8));
	}
	u32 get_original_hash() const
	{
		return
				(u32(m_data[OFFS_ORIGHASH + 0]) << (3 * 8)) |
				(u32(m_data[OFFS_ORIGHASH + 1]) << (2 * 8)) |
				(u32(m_data[OFFS_ORIGHASH + 2]) << (1 * 8)) |
				(u32(m_data[OFFS_ORIGHASH + 3]) << (0 * 8));
	}
	u32 get_glyph_count() const
	{
		return
				(u32(m_data[OFFS_GLYPHCOUNT + 0]) << (3 * 8)) |
				(u32(m_data[OFFS_GLYPHCOUNT + 1]) << (2 * 8)) |
				(u32(m_data[OFFS_GLYPHCOUNT + 2]) << (1 * 8)) |
				(u32(m_data[OFFS_GLYPHCOUNT + 3]) << (0 * 8));
	}
	u16 get_height() const
	{
		return
				(u16(m_data[OFFS_HEIGHT + 0]) << (1 * 8)) |
				(u16(m_data[OFFS_HEIGHT + 1]) << (0 * 8));
	}
	s16 get_y_offset() const
	{
		return
				(u16(m_data[OFFS_YOFFSET + 0]) << (1 * 8)) |
				(u16(m_data[OFFS_YOFFSET + 1]) << (0 * 8));
	}
	s32 get_default_character() const
	{
		return
				(u32(m_data[OFFS_DEFCHAR + 0]) << (3 * 8)) |
				(u32(m_data[OFFS_DEFCHAR + 1]) << (2 * 8)) |
				(u32(m_data[OFFS_DEFCHAR + 2]) << (1 * 8)) |
				(u32(m_data[OFFS_DEFCHAR + 3]) << (0 * 8));
	}

	void set_magic()
	{
		std::memcpy(m_data + OFFS_MAGIC, MAGIC, OFFS_MAJVERSION - OFFS_MAGIC);
	}
	void set_version()
	{
		m_data[OFFS_MAJVERSION] = MAJVERSION;
		m_data[OFFS_MINVERSION] = MINVERSION;
	}
	void set_original_length(u64 value)
	{
		m_data[OFFS_ORIGLENGTH + 0] = u8((value >> (7 * 8)) & 0x00ff);
		m_data[OFFS_ORIGLENGTH + 1] = u8((value >> (6 * 8)) & 0x00ff);
		m_data[OFFS_ORIGLENGTH + 2] = u8((value >> (5 * 8)) & 0x00ff);
		m_data[OFFS_ORIGLENGTH + 3] = u8((value >> (4 * 8)) & 0x00ff);
		m_data[OFFS_ORIGLENGTH + 4] = u8((value >> (3 * 8)) & 0x00ff);
		m_data[OFFS_ORIGLENGTH + 5] = u8((value >> (2 * 8)) & 0x00ff);
		m_data[OFFS_ORIGLENGTH + 6] = u8((value >> (1 * 8)) & 0x00ff);
		m_data[OFFS_ORIGLENGTH + 7] = u8((value >> (0 * 8)) & 0x00ff);
	}
	void set_original_hash(u32 value)
	{
		m_data[OFFS_ORIGHASH + 0] = u8((value >> (3 * 8)) & 0x00ff);
		m_data[OFFS_ORIGHASH + 1] = u8((value >> (2 * 8)) & 0x00ff);
		m_data[OFFS_ORIGHASH + 2] = u8((value >> (1 * 8)) & 0x00ff);
		m_data[OFFS_ORIGHASH + 3] = u8((value >> (0 * 8)) & 0x00ff);
	}
	void set_glyph_count(u32 value)
	{
		m_data[OFFS_GLYPHCOUNT + 0] = u8((value >> (3 * 8)) & 0x00ff);
		m_data[OFFS_GLYPHCOUNT + 1] = u8((value >> (2 * 8)) & 0x00ff);
		m_data[OFFS_GLYPHCOUNT + 2] = u8((value >> (1 * 8)) & 0x00ff);
		m_data[OFFS_GLYPHCOUNT + 3] = u8((value >> (0 * 8)) & 0x00ff);
	}
	void set_height(u16 value)
	{
		m_data[OFFS_HEIGHT + 0] = u8((value >> (1 * 8)) & 0x00ff);
		m_data[OFFS_HEIGHT + 1] = u8((value >> (0 * 8)) & 0x00ff);
	}
	void set_y_offset(s16 value)
	{
		m_data[OFFS_YOFFSET + 0] = u8((value >> (1 * 8)) & 0x00ff);
		m_data[OFFS_YOFFSET + 1] = u8((value >> (0 * 8)) & 0x00ff);
	}
	void set_default_character(s32 value)
	{
		m_data[OFFS_DEFCHAR + 0] = u8((value >> (3 * 8)) & 0x00ff);
		m_data[OFFS_DEFCHAR + 1] = u8((value >> (2 * 8)) & 0x00ff);
		m_data[OFFS_DEFCHAR + 2] = u8((value >> (1 * 8)) & 0x00ff);
		m_data[OFFS_DEFCHAR + 3] = u8((value >> (0 * 8)) & 0x00ff);
	}

private:
	static constexpr std::size_t    OFFS_MAGIC      = 0x00; // 0x06 bytes
	static constexpr std::size_t    OFFS_MAJVERSION = 0x06; // 0x01 bytes (binary integer)
	static constexpr std::size_t    OFFS_MINVERSION = 0x07; // 0x01 bytes (binary integer)
	static constexpr std::size_t    OFFS_ORIGLENGTH = 0x08; // 0x08 bytes (big-endian binary integer)
	static constexpr std::size_t    OFFS_ORIGHASH   = 0x10; // 0x04 bytes
	static constexpr std::size_t    OFFS_GLYPHCOUNT = 0x14; // 0x04 bytes (big-endian binary integer)
	static constexpr std::size_t    OFFS_HEIGHT     = 0x18; // 0x02 bytes (big-endian binary integer)
	static constexpr std::size_t    OFFS_YOFFSET    = 0x1a; // 0x02 bytes (big-endian binary integer)
	static constexpr std::size_t    OFFS_DEFCHAR    = 0x1c; // 0x04 bytes (big-endian binary integer)
	static constexpr std::size_t    OFFS_END        = 0x20;

	static u8 const                 MAGIC[OFFS_MAJVERSION - OFFS_MAGIC];

	u8                              m_data[OFFS_END];
};

u8 const bdc_header::MAGIC[OFFS_MAJVERSION - OFFS_MAGIC] = { 'b', 'd', 'c', 'f', 'n', 't' };


class bdc_table_entry
{
public:
	bdc_table_entry(void *bytes)
		: m_ptr(reinterpret_cast<u8 *>(bytes))
	{
	}
	bdc_table_entry(bdc_table_entry const &that) = default;
	bdc_table_entry(bdc_table_entry &&that) = default;

	bdc_table_entry get_next() const
	{
		return bdc_table_entry(m_ptr + OFFS_END);
	}

	u32 get_encoding() const
	{
		return
				(u32(m_ptr[OFFS_ENCODING + 0]) << (3 * 8)) |
				(u32(m_ptr[OFFS_ENCODING + 1]) << (2 * 8)) |
				(u32(m_ptr[OFFS_ENCODING + 2]) << (1 * 8)) |
				(u32(m_ptr[OFFS_ENCODING + 3]) << (0 * 8));
	}
	u16 get_x_advance() const
	{
		return
				(u16(m_ptr[OFFS_XADVANCE + 0]) << (1 * 8)) |
				(u16(m_ptr[OFFS_XADVANCE + 1]) << (0 * 8));
	}
	s16 get_bb_x_offset() const
	{
		return
				(u16(m_ptr[OFFS_BBXOFFSET + 0]) << (1 * 8)) |
				(u16(m_ptr[OFFS_BBXOFFSET + 1]) << (0 * 8));
	}
	s16 get_bb_y_offset() const
	{
		return
				(u16(m_ptr[OFFS_BBYOFFSET + 0]) << (1 * 8)) |
				(u16(m_ptr[OFFS_BBYOFFSET + 1]) << (0 * 8));
	}
	u16 get_bb_width() const
	{
		return
				(u16(m_ptr[OFFS_BBWIDTH + 0]) << (1 * 8)) |
				(u16(m_ptr[OFFS_BBWIDTH + 1]) << (0 * 8));
	}
	u16 get_bb_height() const
	{
		return
				(u16(m_ptr[OFFS_BBHEIGHT + 0]) << (1 * 8)) |
				(u16(m_ptr[OFFS_BBHEIGHT + 1]) << (0 * 8));
	}

	void set_encoding(u32 value)
	{
		m_ptr[OFFS_ENCODING + 0] = u8((value >> (3 * 8)) & 0x00ff);
		m_ptr[OFFS_ENCODING + 1] = u8((value >> (2 * 8)) & 0x00ff);
		m_ptr[OFFS_ENCODING + 2] = u8((value >> (1 * 8)) & 0x00ff);
		m_ptr[OFFS_ENCODING + 3] = u8((value >> (0 * 8)) & 0x00ff);
	}
	void set_x_advance(u16 value)
	{
		m_ptr[OFFS_XADVANCE + 0] = u8((value >> (1 * 8)) & 0x00ff);
		m_ptr[OFFS_XADVANCE + 1] = u8((value >> (0 * 8)) & 0x00ff);
	}
	void set_bb_x_offset(s16 value)
	{
		m_ptr[OFFS_BBXOFFSET + 0] = u8((value >> (1 * 8)) & 0x00ff);
		m_ptr[OFFS_BBXOFFSET + 1] = u8((value >> (0 * 8)) & 0x00ff);
	}
	void set_bb_y_offset(s16 value)
	{
		m_ptr[OFFS_BBYOFFSET + 0] = u8((value >> (1 * 8)) & 0x00ff);
		m_ptr[OFFS_BBYOFFSET + 1] = u8((value >> (0 * 8)) & 0x00ff);
	}
	void set_bb_width(u16 value)
	{
		m_ptr[OFFS_BBWIDTH + 0] = u8((value >> (1 * 8)) & 0x00ff);
		m_ptr[OFFS_BBWIDTH + 1] = u8((value >> (0 * 8)) & 0x00ff);
	}
	void set_bb_height(u16 value)
	{
		m_ptr[OFFS_BBHEIGHT + 0] = u8((value >> (1 * 8)) & 0x00ff);
		m_ptr[OFFS_BBHEIGHT + 1] = u8((value >> (0 * 8)) & 0x00ff);
	}

	bdc_table_entry &operator=(bdc_table_entry const &that) = default;
	bdc_table_entry &operator=(bdc_table_entry &&that) = default;

	static std::size_t size()
	{
		return OFFS_END;
	}

private:
	static constexpr std::size_t    OFFS_ENCODING   = 0x00; // 0x04 bytes (big-endian binary integer)
	static constexpr std::size_t    OFFS_XADVANCE   = 0x04; // 0x02 bytes (big-endian binary integer)
	// two bytes reserved
	static constexpr std::size_t    OFFS_BBXOFFSET  = 0x08; // 0x02 bytes (big-endian binary integer)
	static constexpr std::size_t    OFFS_BBYOFFSET  = 0x0a; // 0x02 bytes (big-endian binary integer)
	static constexpr std::size_t    OFFS_BBWIDTH    = 0x0c; // 0x02 bytes (big-endian binary integer)
	static constexpr std::size_t    OFFS_BBHEIGHT   = 0x0e; // 0x02 bytes (big-endian binary integer)
	static constexpr std::size_t    OFFS_END        = 0x10;

	u8                              *m_ptr;
};

} // anonymous namespace


void convert_command_glyph(std::string &str)
{
	str.c_str(); // force NUL-termination - we depend on it later
	std::size_t const len(str.length());
	std::vector<char> buf(2 * (len + 1));
	std::size_t j(0);
	for (std::size_t i = 0; len > i; )
	{
		// decode UTF-8
		char32_t uchar;
		int const codelen(uchar_from_utf8(&uchar, &str[i], len - i));
		if (0 >= codelen)
			break;
		i += codelen;

		// check for three metacharacters
		fix_command_t const *fixcmd(nullptr);
		switch (uchar)
		{
		case COMMAND_CONVERT_TEXT:
			for (fix_strings_t *fixtext = convert_text; fixtext->glyph_code; ++fixtext)
			{
				if (!fixtext->glyph_str_len)
					fixtext->glyph_str_len = std::strlen(fixtext->glyph_str);

				if (!std::strncmp(fixtext->glyph_str, &str[i], fixtext->glyph_str_len))
				{
					uchar = fixtext->glyph_code + COMMAND_UNICODE;
					i += strlen(fixtext->glyph_str);
					break;
				}
			}
			break;

		case COMMAND_DEFAULT_TEXT:
			fixcmd = default_text;
			break;

		case COMMAND_EXPAND_TEXT:
			fixcmd = expand_text;
			break;
		}

		// this substitutes a single character
		if (fixcmd)
		{
			if (str[i] == uchar)
			{
				++i;
			}
			else
			{
				while (fixcmd->glyph_code && (fixcmd->glyph_char != str[i]))
					++fixcmd;
				if (fixcmd->glyph_code)
				{
					uchar = COMMAND_UNICODE + fixcmd->glyph_code;
					++i;
				}
			}
		}

		// copy character to output
		int const outlen(utf8_from_uchar(&buf[j], buf.size() - j, uchar));
		if (0 >= outlen)
			break;
		j += outlen;
	}
	str.assign(&buf[0], j);
}


const u64 render_font::CACHED_BDF_HASH_SIZE;

>>>>>>> upstream/master
//**************************************************************************
//  INLINE FUNCTIONS
//**************************************************************************

//-------------------------------------------------
//  next_line - return a pointer to the start of
//  the next line
//-------------------------------------------------

inline const char *next_line(const char *ptr)
{
	// scan forward until we hit the end or a carriage return
	while (*ptr != 13 && *ptr != 10 && *ptr != 0) ptr++;

<<<<<<< HEAD
	// if we hit the end, return NULL
	if (*ptr == 0)
		return NULL;
=======
	// if we hit the end, return nullptr
	if (*ptr == 0)
		return nullptr;
>>>>>>> upstream/master

	// eat the trailing linefeed if present
	if (*++ptr == 10)
		ptr++;
	return ptr;
}


//-------------------------------------------------
//  get_char - return a pointer to a character
//  in a font, expanding if necessary
//-------------------------------------------------

<<<<<<< HEAD
inline render_font::glyph &render_font::get_char(unicode_char chnum)
{
	static glyph dummy_glyph;

	// grab the table; if none, return the dummy character
	if (!m_glyphs[chnum / 256] && m_format == FF_OSD)
		m_glyphs[chnum / 256] = new glyph[256];
	if (!m_glyphs[chnum / 256])
	{
		//mamep: make table for command glyph
		if (chnum >= COMMAND_UNICODE && chnum < COMMAND_UNICODE + MAX_GLYPH_FONT)
			m_glyphs[chnum / 256] = new glyph[256];
=======
inline render_font::glyph &render_font::get_char(char32_t chnum)
{
	static glyph dummy_glyph;

	unsigned const page(chnum / 256);
	if (page >= ARRAY_LENGTH(m_glyphs))
	{
		if ((0 <= m_defchar) && (chnum != m_defchar))
			return get_char(m_defchar);
		else
			return dummy_glyph;
	}
	else if (!m_glyphs[page])
	{
		//mamep: make table for command glyph
		if ((m_format == format::OSD) || ((chnum >= COMMAND_UNICODE) && (chnum < COMMAND_UNICODE + MAX_GLYPH_FONT)))
			m_glyphs[page] = new glyph[256];
		else if ((0 <= m_defchar) && (chnum != m_defchar))
			return get_char(m_defchar);
>>>>>>> upstream/master
		else
			return dummy_glyph;
	}

	// if the character isn't generated yet, do it now
<<<<<<< HEAD
	glyph &gl = m_glyphs[chnum / 256][chnum % 256];
=======
	glyph &gl = m_glyphs[page][chnum % 256];
>>>>>>> upstream/master
	if (!gl.bitmap.valid())
	{
		//mamep: command glyph support
		if (m_height_cmd && chnum >= COMMAND_UNICODE && chnum < COMMAND_UNICODE + MAX_GLYPH_FONT)
		{
<<<<<<< HEAD
			glyph &glyph_ch = m_glyphs_cmd[chnum / 256][chnum % 256];
			float scale = (float)m_height / (float)m_height_cmd;
			if (m_format == FF_OSD) scale *= 0.90f;
=======
			glyph &glyph_ch = m_glyphs_cmd[page][chnum % 256];
			float scale = float(m_height) / float(m_height_cmd);
			if (m_format == format::OSD)
				scale *= 0.90f;
>>>>>>> upstream/master

			if (!glyph_ch.bitmap.valid())
				char_expand(chnum, glyph_ch);

<<<<<<< HEAD
#ifdef UI_COLOR_DISPLAY
			//mamep: for color glyph
			gl.color = glyph_ch.color;
#endif /* UI_COLOR_DISPLAY */
			gl.width = (int)(glyph_ch.width * scale + 0.5f);
			gl.xoffs = (int)(glyph_ch.xoffs * scale + 0.5f);
			gl.yoffs = (int)(glyph_ch.yoffs * scale + 0.5f);
			gl.bmwidth = (int)(glyph_ch.bmwidth * scale + 0.5f);
			gl.bmheight = (int)(glyph_ch.bmheight * scale + 0.5f);
=======
			//mamep: for color glyph
			gl.color = glyph_ch.color;

			gl.width = int(glyph_ch.width * scale + 0.5f);
			gl.xoffs = int(glyph_ch.xoffs * scale + 0.5f);
			gl.yoffs = int(glyph_ch.yoffs * scale + 0.5f);
			gl.bmwidth = int(glyph_ch.bmwidth * scale + 0.5f);
			gl.bmheight = int(glyph_ch.bmheight * scale + 0.5f);
>>>>>>> upstream/master

			gl.bitmap.allocate(gl.bmwidth, gl.bmheight);
			rectangle clip;
			clip.min_x = clip.min_y = 0;
			clip.max_x = glyph_ch.bitmap.width() - 1;
			clip.max_y = glyph_ch.bitmap.height() - 1;
<<<<<<< HEAD
			render_texture::hq_scale(gl.bitmap, glyph_ch.bitmap, clip, NULL);
=======
			render_texture::hq_scale(gl.bitmap, glyph_ch.bitmap, clip, nullptr);
>>>>>>> upstream/master

			/* wrap a texture around the bitmap */
			gl.texture = m_manager.texture_alloc(render_texture::hq_scale);
			gl.texture->set_bitmap(gl.bitmap, gl.bitmap.cliprect(), TEXFORMAT_ARGB32);
		}
		else
<<<<<<< HEAD
			char_expand(chnum, gl);
	}

	// return the resulting character
=======
		{
			char_expand(chnum, gl);
		}
	}

>>>>>>> upstream/master
	return gl;
}



//**************************************************************************
//  RENDER FONT
//**************************************************************************

<<<<<<< HEAD
//mamep: allocate command glyph font
void render_font::render_font_command_glyph()
{
	emu_file ramfile(OPEN_FLAG_READ);
	file_error filerr;

	if (m_height >= 14)
		filerr = ramfile.open_ram(font_uicmd14, sizeof(font_uicmd14));
	else
		filerr = ramfile.open_ram(font_uicmd11, sizeof(font_uicmd11));

	if (filerr == FILERR_NONE)
	{
		load_cached_cmd(ramfile, 0);
	}
}


=======
>>>>>>> upstream/master
//-------------------------------------------------
//  render_font - constructor
//-------------------------------------------------

render_font::render_font(render_manager &manager, const char *filename)
<<<<<<< HEAD
	: m_manager(manager),
		m_format(FF_UNKNOWN),
		m_height(0),
		m_yoffs(0),
		m_scale(1.0f),
		m_rawsize(0),
		m_osdfont(NULL),
		m_height_cmd(0),
		m_yoffs_cmd(0)
=======
	: m_manager(manager)
	, m_format(format::UNKNOWN)
	, m_height(0)
	, m_yoffs(0)
	, m_defchar(-1)
	, m_scale(1.0f)
	, m_rawsize(0)
	, m_osdfont()
	, m_height_cmd(0)
	, m_yoffs_cmd(0)
>>>>>>> upstream/master
{
	memset(m_glyphs, 0, sizeof(m_glyphs));
	memset(m_glyphs_cmd, 0, sizeof(m_glyphs_cmd));

	// if this is an OSD font, we're done
<<<<<<< HEAD
	if (filename != NULL)
	{
		m_osdfont = manager.machine().osd().font_alloc();
		if (m_osdfont != NULL)
		{
			if (m_osdfont->open(manager.machine().options().font_path(), filename, m_height))
			{
				m_scale = 1.0f / (float)m_height;
				m_format = FF_OSD;
				//mamep: allocate command glyph font
				render_font_command_glyph();
				return;
			}
			global_free(m_osdfont);
			m_osdfont = NULL;
		}
	}

	// if the filename is 'default' default to 'ui.bdf' for backwards compatibility
	if (filename != NULL && core_stricmp(filename, "default") == 0)
		filename = "ui.bdf";

	// attempt to load the cached version of the font first
	if (filename != NULL)
	{
		int loaded = 0;
		std::string filename_local = std::string(ui_lang_info[lang_get_langcode()].name).append(PATH_SEPARATOR).append(filename);
//		osd_printf_warning("%s\n", filename_local);

	 	if (filename_local.length() > 0 && load_cached_bdf(filename_local.c_str()))
			loaded++;
		else
		{
			if (load_cached_bdf(filename))
				loaded++;
		}

		if (loaded)
		{
=======
	if (filename)
	{
		m_osdfont = manager.machine().osd().font_alloc();
		if (m_osdfont && m_osdfont->open(manager.machine().options().font_path(), filename, m_height))
		{
			m_scale = 1.0f / float(m_height);
			m_format = format::OSD;

>>>>>>> upstream/master
			//mamep: allocate command glyph font
			render_font_command_glyph();
			return;
		}
<<<<<<< HEAD
	}

	// load the raw data instead
	emu_file ramfile(OPEN_FLAG_READ);
	file_error filerr;
	//mamep: embedded CJK font
	switch (lang_get_langcode())
	{
	case UI_LANG_JA_JP:
	case UI_LANG_ZH_CN:
	case UI_LANG_ZH_TW:
	case UI_LANG_KO_KR:
		filerr = ramfile.open_ram(font_uismall14, sizeof(font_uismall14));
		break;

	default:
		filerr = ramfile.open_ram(font_uismall11, sizeof(font_uismall11));
	}

	if (filerr == FILERR_NONE)
		load_cached(ramfile, 0);

	//mamep: allocate command glyph font
=======
		m_osdfont.reset();
	}

	// if the filename is 'default' default to 'ui.bdf' for backwards compatibility
	if (filename && !core_stricmp(filename, "default"))
		filename = "ui.bdf";

	// attempt to load an external BDF font first
	if (filename && load_cached_bdf(filename))
	{
		//mamep: allocate command glyph font
		render_font_command_glyph();
		return;
	}

	// load the compiled in data instead
	emu_file ramfile(OPEN_FLAG_READ);
	osd_file::error const filerr(ramfile.open_ram(font_uismall, sizeof(font_uismall)));
	if (osd_file::error::NONE == filerr)
		load_cached(ramfile, 0, 0);
>>>>>>> upstream/master
	render_font_command_glyph();
}


//-------------------------------------------------
//  ~render_font - destructor
//-------------------------------------------------

render_font::~render_font()
{
	// free all the subtables
<<<<<<< HEAD
	for (int tablenum = 0; tablenum < 256; tablenum++)
		if (m_glyphs[tablenum])
		{
			for (unsigned int charnum = 0; charnum < 256; charnum++)
			{
				glyph &gl = m_glyphs[tablenum][charnum];
				m_manager.texture_free(gl.texture);
			}
			delete[] m_glyphs[tablenum];
		}

	//mamep: free command glyph font
	for (int tablenum = 0; tablenum < 256; tablenum++)
		if (m_glyphs_cmd[tablenum])
		{
			for (unsigned int charnum = 0; charnum < 256; charnum++)
			{
				glyph &gl = m_glyphs_cmd[tablenum][charnum];
				m_manager.texture_free(gl.texture);
			}
			delete[] m_glyphs_cmd[tablenum];
		}

	// release the OSD font
	if (m_osdfont != NULL)
	{
		m_osdfont->close();
		global_free(m_osdfont);
	}
=======
	for (auto & elem : m_glyphs)
		if (elem)
		{
			for (unsigned int charnum = 0; charnum < 256; charnum++)
			{
				glyph &gl = elem[charnum];
				m_manager.texture_free(gl.texture);
			}
			delete[] elem;
		}

	for (auto & elem : m_glyphs_cmd)
		if (elem)
		{
			for (unsigned int charnum = 0; charnum < 256; charnum++)
			{
				glyph &gl = elem[charnum];
				m_manager.texture_free(gl.texture);
			}
			delete[] elem;
		}
>>>>>>> upstream/master
}


//-------------------------------------------------
//  char_expand - expand the raw data for a
//  character into a bitmap
//-------------------------------------------------

<<<<<<< HEAD
void render_font::char_expand(unicode_char chnum, glyph &gl)
{
	rgb_t color = rgb_t(0xff,0xff,0xff,0xff);
	bool is_cmd = (chnum >= COMMAND_UNICODE && chnum < COMMAND_UNICODE + MAX_GLYPH_FONT);

#ifdef UI_COLOR_DISPLAY
	//mamep: for color glyph
	if (gl.color)
		color = manager().machine().ui().get_rgb_color(gl.color);
#endif /* UI_COLOR_DISPLAY */

	//mamep: command glyph support
	if (is_cmd)
	{
		// punt if nothing there
		if (gl.bmwidth == 0 || gl.bmheight == 0 || gl.rawdata == NULL)
=======
void render_font::char_expand(char32_t chnum, glyph &gl)
{
	LOG("render_font::char_expand: expanding character %u\n", unsigned(chnum));

	rgb_t const fgcol(gl.color ? gl.color : rgb_t(0xff, 0xff, 0xff, 0xff));
	rgb_t const bgcol(0x00, 0xff, 0xff, 0xff);
	bool const is_cmd((chnum >= COMMAND_UNICODE) && (chnum < COMMAND_UNICODE + MAX_GLYPH_FONT));

	if (is_cmd)
	{
		// abort if nothing there
		if (gl.bmwidth == 0 || gl.bmheight == 0 || gl.rawdata == nullptr)
>>>>>>> upstream/master
			return;

		// allocate a new bitmap of the size we need
		gl.bitmap.allocate(gl.bmwidth, m_height_cmd);
		gl.bitmap.fill(0);

		// extract the data
		const char *ptr = gl.rawdata;
<<<<<<< HEAD
		UINT8 accum = 0, accumbit = 7;
		for (int y = 0; y < gl.bmheight; y++)
		{
			int desty = y + m_height_cmd + m_yoffs_cmd - gl.yoffs - gl.bmheight;
			UINT32 *dest = (desty >= 0 && desty < m_height_cmd) ? &gl.bitmap.pix32(desty, 0) : NULL;

=======
		u8 accum = 0, accumbit = 7;
		for (int y = 0; y < gl.bmheight; y++)
		{
			int desty = y + m_height_cmd + m_yoffs_cmd - gl.yoffs - gl.bmheight;
			u32 *dest = (desty >= 0 && desty < m_height_cmd) ? &gl.bitmap.pix32(desty, 0) : nullptr;
>>>>>>> upstream/master
			{
				for (int x = 0; x < gl.bmwidth; x++)
				{
					if (accumbit == 7)
						accum = *ptr++;
<<<<<<< HEAD
					if (dest != NULL)
						*dest++ = (accum & (1 << accumbit)) ? color : rgb_t(0x00,0xff,0xff,0xff);
=======
					if (dest != nullptr)
						*dest++ = (accum & (1 << accumbit)) ? fgcol : bgcol;
>>>>>>> upstream/master
					accumbit = (accumbit - 1) & 7;
				}
			}
		}
	}
<<<<<<< HEAD
	else

	// if we're an OSD font, query the info
	if (m_format == FF_OSD)
	{
		// we set bmwidth to -1 if we've previously queried and failed
		if (gl.bmwidth == -1)
			return;

		// attempt to get the font bitmap; if we fail, set bmwidth to -1
		if (!m_osdfont->get_bitmap(chnum, gl.bitmap, gl.width, gl.xoffs, gl.yoffs))
		{
=======
	else if (m_format == format::OSD)
	{
		// if we're an OSD font, query the info
		if (0 > gl.bmwidth)
		{
			// we set bmwidth to -1 if we've previously queried and failed
			LOG("render_font::char_expand: previously failed to get bitmap from OSD font\n");
			return;
		}
		if (!m_osdfont->get_bitmap(chnum, gl.bitmap, gl.width, gl.xoffs, gl.yoffs))
		{
			// attempt to get the font bitmap failed - set bmwidth to -1
			LOG("render_font::char_expand: get bitmap from OSD font failed\n");
>>>>>>> upstream/master
			gl.bitmap.reset();
			gl.bmwidth = -1;
			return;
		}
<<<<<<< HEAD

		// populate the bmwidth/bmheight fields
		gl.bmwidth = gl.bitmap.width();
		gl.bmheight = gl.bitmap.height();
	}

	// other formats need to parse their data
	else
	{
		// punt if nothing there
		if (gl.bmwidth == 0 || gl.bmheight == 0 || gl.rawdata == NULL)
			return;
=======
		else
		{
			// populate the bmwidth/bmheight fields
			LOG("render_font::char_expand: got %dx%d bitmap from OSD font\n", gl.bitmap.width(), gl.bitmap.height());
			gl.bmwidth = gl.bitmap.width();
			gl.bmheight = gl.bitmap.height();
		}
	}
	else if (!gl.bmwidth || !gl.bmheight || !gl.rawdata)
	{
		// abort if nothing there
		LOG("render_font::char_expand: empty bitmap bounds or no raw data\n");
		return;
	}
	else
	{
		// other formats need to parse their data
		LOG("render_font::char_expand: building bitmap from raw data\n");
>>>>>>> upstream/master

		// allocate a new bitmap of the size we need
		gl.bitmap.allocate(gl.bmwidth, m_height);
		gl.bitmap.fill(0);

		// extract the data
		const char *ptr = gl.rawdata;
<<<<<<< HEAD
		UINT8 accum = 0, accumbit = 7;
		for (int y = 0; y < gl.bmheight; y++)
		{
			int desty = y + m_height + m_yoffs - gl.yoffs - gl.bmheight;
			UINT32 *dest = (desty >= 0 && desty < m_height) ? &gl.bitmap.pix32(desty) : NULL;

			// text format
			if (m_format == FF_TEXT)
			{
				// loop over bytes
				for (int x = 0; x < gl.bmwidth; x += 4)
				{
					// scan for the next hex digit
					int bits = -1;
					while (*ptr != 13 && bits == -1)
					{
						if (*ptr >= '0' && *ptr <= '9')
							bits = *ptr++ - '0';
						else if (*ptr >= 'A' && *ptr <= 'F')
							bits = *ptr++ - 'A' + 10;
						else if (*ptr >= 'a' && *ptr <= 'f')
							bits = *ptr++ - 'a' + 10;
						else
							ptr++;
					}

					// expand the four bits
					if (dest != NULL)
					{
						*dest++ = (bits & 8) ? color : rgb_t(0x00,0xff,0xff,0xff);
						*dest++ = (bits & 4) ? color : rgb_t(0x00,0xff,0xff,0xff);
						*dest++ = (bits & 2) ? color : rgb_t(0x00,0xff,0xff,0xff);
						*dest++ = (bits & 1) ? color : rgb_t(0x00,0xff,0xff,0xff);
=======
		u8 accum(0), accumbit(7);
		for (int y = 0; y < gl.bmheight; ++y)
		{
			int const desty(y + m_height + m_yoffs - gl.yoffs - gl.bmheight);
			u32 *dest(((0 <= desty) && (m_height > desty)) ? &gl.bitmap.pix32(desty) : nullptr);

			if (m_format == format::TEXT)
			{
				if (dest)
				{
					for (int x = 0; gl.bmwidth > x; )
					{
						// scan for the next hex digit
						int bits = -1;
						while (('\r' != *ptr) && ('\n' != *ptr) && (0 > bits))
						{
							if (*ptr >= '0' && *ptr <= '9')
								bits = *ptr++ - '0';
							else if (*ptr >= 'A' && *ptr <= 'F')
								bits = *ptr++ - 'A' + 10;
							else if (*ptr >= 'a' && *ptr <= 'f')
								bits = *ptr++ - 'a' + 10;
							else
								ptr++;
						}

						// expand the four bits
						*dest++ = (bits & 8) ? fgcol : bgcol;
						if (gl.bmwidth > ++x)
							*dest++ = (bits & 4) ? fgcol : bgcol;
						if (gl.bmwidth > ++x)
							*dest++ = (bits & 2) ? fgcol : bgcol;
						if (gl.bmwidth > ++x)
							*dest++ = (bits & 1) ? fgcol : bgcol;
						++x;
>>>>>>> upstream/master
					}
				}

				// advance to the next line
				ptr = next_line(ptr);
			}
<<<<<<< HEAD

			// cached format
			else if (m_format == FF_CACHED)
=======
			else if (m_format == format::CACHED)
>>>>>>> upstream/master
			{
				for (int x = 0; x < gl.bmwidth; x++)
				{
					if (accumbit == 7)
						accum = *ptr++;
<<<<<<< HEAD
					if (dest != NULL)
						*dest++ = (accum & (1 << accumbit)) ? color : rgb_t(0x00,0xff,0xff,0xff);
=======
					if (dest != nullptr)
						*dest++ = (accum & (1 << accumbit)) ? fgcol : bgcol;
>>>>>>> upstream/master
					accumbit = (accumbit - 1) & 7;
				}
			}
		}
	}

	// wrap a texture around the bitmap
	gl.texture = m_manager.texture_alloc(render_texture::hq_scale);
	gl.texture->set_bitmap(gl.bitmap, gl.bitmap.cliprect(), TEXFORMAT_ARGB32);
}


//-------------------------------------------------
//  get_char_texture_and_bounds - return the
//  texture for a character and compute the
//  bounds of the final bitmap
//-------------------------------------------------

<<<<<<< HEAD
render_texture *render_font::get_char_texture_and_bounds(float height, float aspect, unicode_char chnum, render_bounds &bounds)
=======
render_texture *render_font::get_char_texture_and_bounds(float height, float aspect, char32_t chnum, render_bounds &bounds)
>>>>>>> upstream/master
{
	glyph &gl = get_char(chnum);

	// on entry, assume x0,y0 are the top,left coordinate of the cell and add
	// the character bounding box to that position
	float scale = m_scale * height;
	bounds.x0 += float(gl.xoffs) * scale * aspect;

	// compute x1,y1 from there based on the bitmap size
	bounds.x1 = bounds.x0 + float(gl.bmwidth) * scale * aspect;
	bounds.y1 = bounds.y0 + float(m_height) * scale;

	// return the texture
	return gl.texture;
}


//-------------------------------------------------
//  get_scaled_bitmap_and_bounds - return a
//  scaled bitmap and bounding rect for a char
//-------------------------------------------------

<<<<<<< HEAD
void render_font::get_scaled_bitmap_and_bounds(bitmap_argb32 &dest, float height, float aspect, unicode_char chnum, rectangle &bounds)
=======
void render_font::get_scaled_bitmap_and_bounds(bitmap_argb32 &dest, float height, float aspect, char32_t chnum, rectangle &bounds)
>>>>>>> upstream/master
{
	glyph &gl = get_char(chnum);

	// on entry, assume x0,y0 are the top,left coordinate of the cell and add
	// the character bounding box to that position
	float scale = m_scale * height;
	bounds.min_x = float(gl.xoffs) * scale * aspect;
	bounds.min_y = 0;

	// compute x1,y1 from there based on the bitmap size
	bounds.set_width(float(gl.bmwidth) * scale * aspect);
	bounds.set_height(float(m_height) * scale);

	// if the bitmap isn't big enough, bail
	if (dest.width() < bounds.width() || dest.height() < bounds.height())
		return;

	// if no texture, fill the target
<<<<<<< HEAD
	if (gl.texture == NULL)
=======
	if (gl.texture == nullptr)
>>>>>>> upstream/master
	{
		dest.fill(0);
		return;
	}

	// scale the font
	bitmap_argb32 tempbitmap(&dest.pix(0), bounds.width(), bounds.height(), dest.rowpixels());
<<<<<<< HEAD
	render_texture::hq_scale(tempbitmap, gl.bitmap, gl.bitmap.cliprect(), NULL);
=======
	render_texture::hq_scale(tempbitmap, gl.bitmap, gl.bitmap.cliprect(), nullptr);
>>>>>>> upstream/master
}


//-------------------------------------------------
//  char_width - return the width of a character
//  at the given height
//-------------------------------------------------

<<<<<<< HEAD
float render_font::char_width(float height, float aspect, unicode_char ch)
=======
float render_font::char_width(float height, float aspect, char32_t ch)
>>>>>>> upstream/master
{
	return float(get_char(ch).width) * m_scale * height * aspect;
}

<<<<<<< HEAD
//mamep: to render as fixed-width font
float render_font::char_width_no_margin(float height, float aspect, unicode_char ch)
{
	return (float)(get_char(ch).width - 1) * m_scale * height * aspect;
}

=======
>>>>>>> upstream/master

//-------------------------------------------------
//  string_width - return the width of a string
//  at the given height
//-------------------------------------------------

float render_font::string_width(float height, float aspect, const char *string)
{
	// loop over the string and accumulate widths
	int totwidth = 0;
<<<<<<< HEAD
	for (const unsigned char *ptr = (const unsigned char *)string; *ptr != 0; ptr++)
		totwidth += get_char(*ptr).width;
=======

	const char *ends = string + strlen(string);
	const char *s = string;
	char32_t schar;

	// loop over characters
	while (*s != 0)
	{
		int scharcount = uchar_from_utf8(&schar, s, ends - s);
		totwidth += get_char(schar).width;
		s += scharcount;
	}

>>>>>>> upstream/master

	// scale the final result based on height
	return float(totwidth) * m_scale * height * aspect;
}


//-------------------------------------------------
//  utf8string_width - return the width of a
//  UTF8-encoded string at the given height
//-------------------------------------------------

float render_font::utf8string_width(float height, float aspect, const char *utf8string)
{
<<<<<<< HEAD
	int length = strlen(utf8string);

	// loop over the string and accumulate widths
	int count;
	int totwidth = 0;
	for (int offset = 0; offset < length; offset += count)
	{
		unicode_char uchar;
		count = uchar_from_utf8(&uchar, utf8string + offset, length - offset);
		if (count == -1)
			break;
		if (uchar < 0x10000)
			totwidth += get_char(uchar).width;
=======
	std::size_t const length = std::strlen(utf8string);

	// loop over the string and accumulate widths
	int count;
	s32 totwidth = 0;
	for (std::size_t offset = 0U; offset < length; offset += unsigned(count))
	{
		char32_t uchar;
		count = uchar_from_utf8(&uchar, utf8string + offset, length - offset);
		if (count < 0)
			break;

		totwidth += get_char(uchar).width;
>>>>>>> upstream/master
	}

	// scale the final result based on height
	return float(totwidth) * m_scale * height * aspect;
}


//-------------------------------------------------
//  load_cached_bdf - attempt to load a cached
//  version of the BDF font 'filename'; if that
//  fails, fall back on the regular BDF loader
//  and create a new cached version
//-------------------------------------------------

bool render_font::load_cached_bdf(const char *filename)
{
<<<<<<< HEAD
	// first try to open the BDF itself
	emu_file file(manager().machine().options().font_path(), OPEN_FLAG_READ);
	file_error filerr = file.open(filename);
	if (filerr != FILERR_NONE)
		return false;

	// determine the file size and allocate memory
	m_rawsize = file.size();
	m_rawdata.resize(m_rawsize + 1);

	// read the first chunk
	UINT32 bytes = file.read(&m_rawdata[0], MIN(CACHED_BDF_HASH_SIZE, m_rawsize));
	if (bytes != MIN(CACHED_BDF_HASH_SIZE, m_rawsize))
		return false;

	// has the chunk
	UINT32 hash = core_crc32(0, (const UINT8 *)&m_rawdata[0], bytes) ^ (UINT32)m_rawsize;

	// create the cached filename, changing the 'F' to a 'C' on the extension
	std::string cachedname(filename);
	cachedname.erase(cachedname.length() - 3, 3).append("bdc");

	// attempt to open the cached version of the font
	{
		emu_file cachefile(manager().machine().options().font_path(), OPEN_FLAG_READ);
		filerr = cachefile.open(cachedname.c_str());
		if (filerr == FILERR_NONE)
		{
			// if we have a cached version, load it
			bool result = load_cached(cachefile, hash);

			// if that worked, we're done
			if (result)
			{
				// don't do that - glyphs data point into this array ...
				// m_rawdata.reset();
				return true;
			}
		}
	}

	// read in the rest of the font
	if (bytes < m_rawsize)
	{
		UINT32 read = file.read(&m_rawdata[bytes], m_rawsize - bytes);
		if (read != m_rawsize - bytes)
=======
	osd_file::error filerr;
	u32 chunk;
	u64 bytes;

	// first try to open the BDF itself
	emu_file file(m_manager.machine().options().font_path(), OPEN_FLAG_READ);
	filerr = file.open(filename);
	if (filerr != osd_file::error::NONE)
		return false;

	// determine the file size and allocate memory
	try
	{
		m_rawsize = file.size();
		std::vector<char>::size_type const sz(m_rawsize + 1);
		if (u64(sz) != (m_rawsize + 1))
			return false;
		m_rawdata.resize(sz);
	}
	catch (...)
	{
		return false;
	}

	// read the first chunk and hash it
	chunk = u32((std::min<u64>)(CACHED_BDF_HASH_SIZE, m_rawsize));
	bytes = file.read(&m_rawdata[0], chunk);
	if (bytes != chunk)
	{
		m_rawdata.clear();
		return false;
	}
	u32 const hash(core_crc32(0, reinterpret_cast<u8 const *>(&m_rawdata[0]), bytes));

	// create the cached filename, changing the 'F' to a 'C' on the extension
	std::string cachedname(filename);
	if ((4U < cachedname.length()) && !core_stricmp(&cachedname[cachedname.length() - 4], ".bdf"))
		cachedname.erase(cachedname.length() - 4);
	cachedname.append(".bdc");

	// attempt to open the cached version of the font
	{
		emu_file cachefile(m_manager.machine().options().font_path(), OPEN_FLAG_READ);
		filerr = cachefile.open(cachedname.c_str());
		if (filerr == osd_file::error::NONE)
		{
			// if we have a cached version, load it
			bool const result = load_cached(cachefile, m_rawsize, hash);

			// if that worked, we're done
			if (result)
				return true;
		}
	}

	// read in the rest of the font and NUL-terminate it
	while (bytes < m_rawsize)
	{
		chunk = u32((std::min<u64>)(std::numeric_limits<u32>::max(), m_rawsize - bytes));
		u32 const read(file.read(&m_rawdata[bytes], chunk));
		bytes += read;
		if (read != chunk)
>>>>>>> upstream/master
		{
			m_rawdata.clear();
			return false;
		}
	}
<<<<<<< HEAD

	// NULL-terminate the data and attach it to the font
	m_rawdata[m_rawsize] = 0;

	// load the BDF
	bool result = load_bdf();

	// if we loaded okay, create a cached one
	if (result)
		save_cached(cachedname.c_str(), hash);
=======
	m_rawdata[m_rawsize] = '\0';

	// load the BDF
	bool const result = load_bdf();

	// if we loaded okay, create a cached one
	if (result)
		save_cached(cachedname.c_str(), m_rawsize, hash);
	else
		m_rawdata.clear();
>>>>>>> upstream/master

	// close the file
	return result;
}


//-------------------------------------------------
//  load_bdf - parse and load a BDF font
//-------------------------------------------------

bool render_font::load_bdf()
{
	// set the format to text
<<<<<<< HEAD
	m_format = FF_TEXT;

	// first find the FONTBOUNDINGBOX tag
	const char *ptr;
	for (ptr = &m_rawdata[0]; ptr != NULL; ptr = next_line(ptr))
	{
		// we only care about a tiny few fields
		if (strncmp(ptr, "FONTBOUNDINGBOX ", 16) == 0)
		{
			int dummy1, dummy2;
			if (sscanf(ptr + 16, "%d %d %d %d", &dummy1, &m_height, &dummy2, &m_yoffs) != 4)
				return false;
			break;
=======
	m_format = format::TEXT;

	bdf_helper<std::vector<char>::const_iterator> helper(std::cbegin(m_rawdata), std::cend(m_rawdata));

	// the first thing we want to see is the STARTFONT declaration, failing that we can't do much
	for ( ; !helper.is_keyword("STARTFONT"); helper.next_line())
	{
		if (helper.at_end())
		{
			osd_printf_error("render_font::load_bdf: expected STARTFONT\n");
			return false;
		}
	}

	// parse out the global information we need
	bool have_bbox(false);
	bool have_properties(false);
	bool have_defchar(false);
	for (helper.next_line(); !helper.is_keyword("CHARS"); helper.next_line())
	{
		if (helper.at_end())
		{
			// font with no characters is useless
			osd_printf_error("render_font::load_bdf: no glyph section found\n");
			return false;
		}
		else if (helper.is_keyword("FONTBOUNDINGBOX"))
		{
			// check for duplicate bounding box
			if (have_bbox)
			{
				osd_printf_error("render_font::load_bdf: found additional bounding box \"%.*s\"\n", int(helper.value_length()), &*helper.value_begin());
				return false;
			}
			have_bbox = true;

			// parse bounding box and check that it's at least half sane
			int width, xoffs;
			if (4 == sscanf(&*helper.value_begin(), "%d %d %d %d", &width, &m_height, &xoffs, &m_yoffs))
			{
				LOG("render_font::load_bdf: got bounding box %dx%d %d,%d\n", width, m_height, xoffs, m_yoffs);
				if ((0 >= m_height) || (0 >= width))
				{
					osd_printf_error("render_font::load_bdf: bounding box is invalid\n");
					return false;
				}
			}
			else
			{
				osd_printf_error("render_font::load_bdf: failed to parse bounding box \"%.*s\"\n", int(helper.value_length()), &*helper.value_begin());
				return false;
			}
		}
		else if (helper.is_keyword("STARTPROPERTIES"))
		{
			// check for duplicated properties section
			if (have_properties)
			{
				osd_printf_error("render_font::load_bdf: found additional properties\n");
				return false;
			}
			have_properties = true;

			// get property count for sanity check
			int propcount;
			if (1 != sscanf(&*helper.value_begin(), "%d", &propcount))
			{
				osd_printf_error("render_font::load_bdf: failed to parse property count \"%.*s\"\n", int(helper.value_length()), &*helper.value_begin());
				return false;
			}

			int actual(0);
			for (helper.next_line(); !helper.is_keyword("ENDPROPERTIES"); helper.next_line())
			{
				++actual;
				if (helper.at_end())
				{
					// unterminated properties section
					osd_printf_error("render_font::load_bdf: end of properties not found\n");
					return false;
				}
				else if (helper.is_keyword("DEFAULT_CHAR"))
				{
					// check for duplicate default character
					if (have_defchar)
					{
						osd_printf_error("render_font::load_bdf: found additional default character \"%.*s\"\n", int(helper.value_length()), &*helper.value_begin());
						return false;
					}
					have_defchar = true;

					// parse default character
					if (1 == sscanf(&*helper.value_begin(), "%d", &m_defchar))
					{
						LOG("render_font::load_bdf: got default character 0x%x\n", m_defchar);
					}
					else
					{
						osd_printf_error("render_font::load_bdf: failed to parse default character \"%.*s\"\n", int(helper.value_length()), &*helper.value_begin());
						return false;
					}
				}
			}

			// sanity check on number of properties
			if (actual != propcount)
			{
				osd_printf_error("render_font::load_bdf: incorrect number of properties %d\n", actual);
				return false;
			}
>>>>>>> upstream/master
		}
	}

	// compute the scale factor
<<<<<<< HEAD
	m_scale = 1.0f / (float)m_height;

	// now scan for characters
	int charcount = 0;
	for ( ; ptr != NULL; ptr = next_line(ptr))
	{
		// stop at ENDFONT
		if (strncmp(ptr, "ENDFONT", 7) == 0)
			break;

		// once we hit a STARTCHAR, parse until the end
		if (strncmp(ptr, "STARTCHAR ", 10) == 0)
		{
			int bmwidth = -1, bmheight = -1, xoffs = -1, yoffs = -1;
			const char *rawdata = NULL;
			int charnum = -1;
			int width = -1;

			// scan for interesting per-character tags
			for ( ; ptr != NULL; ptr = next_line(ptr))
			{
				// ENCODING tells us which character
				if (strncmp(ptr, "ENCODING ", 9) == 0)
				{
					if (sscanf(ptr + 9, "%d", &charnum) != 1)
						return 1;
				}

				// DWIDTH tells us the width to the next character
				else if (strncmp(ptr, "DWIDTH ", 7) == 0)
				{
					int dummy1;
					if (sscanf(ptr + 7, "%d %d", &width, &dummy1) != 2)
						return 1;
				}

				// BBX tells us the height/width of the bitmap and the offsets
				else if (strncmp(ptr, "BBX ", 4) == 0)
				{
					if (sscanf(ptr + 4, "%d %d %d %d", &bmwidth, &bmheight, &xoffs, &yoffs) != 4)
						return 1;
				}

				// BITMAP is the start of the data
				else if (strncmp(ptr, "BITMAP", 6) == 0)
				{
					// stash the raw pointer and scan for the end of the character
					for (rawdata = ptr = next_line(ptr); ptr != NULL && strncmp(ptr, "ENDCHAR", 7) != 0; ptr = next_line(ptr)) ;
					break;
				}
			}

			// if we have everything, allocate a new character
			if (charnum >= 0 && charnum < 65536 && rawdata != NULL && bmwidth >= 0 && bmheight >= 0)
			{
				// if we don't have a subtable yet, make one
				if (!m_glyphs[charnum / 256])
					m_glyphs[charnum / 256] = new glyph[256];

				// fill in the entry
				glyph &gl = m_glyphs[charnum / 256][charnum % 256];
				gl.width = width;
				gl.bmwidth = bmwidth;
				gl.bmheight = bmheight;
				gl.xoffs = xoffs;
				gl.yoffs = yoffs;
				gl.rawdata = rawdata;
			}

			// some progress for big fonts
			if (++charcount % 256 == 0)
				osd_printf_warning(_("Loading BDF font... (%d characters loaded)\n"), charcount);
		}
	}

	// make sure all the numbers are the same width
	if (m_glyphs[0])
	{
		int maxwidth = 0;
		for (int ch = '0'; ch <= '9'; ch++)
			if (m_glyphs[0][ch].bmwidth > maxwidth)
				maxwidth = m_glyphs[0][ch].width;
		for (int ch = '0'; ch <= '9'; ch++)
			m_glyphs[0][ch].width = maxwidth;
	}

=======
	if (!have_bbox)
	{
		osd_printf_error("render_font::load_bdf: no bounding box found\n");
		return false;
	}
	m_scale = 1.0f / float(m_height);

	// get expected character count
	int expected;
	if (1 == sscanf(&*helper.value_begin(), "%d", &expected))
	{
		LOG("render_font::load_bdf: got character count %d\n", expected);
	}
	else
	{
		osd_printf_error("render_font::load_bdf: failed to parse character count \"%.*s\"\n", int(helper.value_length()), &*helper.value_begin());
		return false;
	}

	// now scan for characters
	auto const nothex([] (char ch) { return (('0' > ch) || ('9' < ch)) && (('A' > ch) || ('Z' < ch)) && (('a' > ch) || ('z' < ch)); });
	int charcount = 0;
	for (helper.next_line(); !helper.is_keyword("ENDFONT"); helper.next_line())
	{
		if (helper.at_end())
		{
			// unterminated font
			osd_printf_error("render_font::load_bdf: end of font not found\n");
			return false;
		}
		else if (helper.is_keyword("STARTCHAR"))
		{
			// required glyph properties
			bool have_encoding(false);
			bool have_advance(false);
			bool have_bbounds(false);
			int encoding(-1);
			int xadvance(-1);
			int bbw(-1), bbh(-1), bbxoff(-1), bbyoff(-1);

			// stuff for the bitmap data
			bool in_bitmap(false);
			int bitmap_rows(0);
			char const *bitmap_data(nullptr);

			// parse a glyph
			for (helper.next_line(); !helper.is_keyword("ENDCHAR"); helper.next_line())
			{
				if (helper.at_end())
				{
					// unterminated glyph
					osd_printf_error("render_font::load_bdf: end of glyph not found\n");
					return false;
				}
				else if (in_bitmap)
				{
					// quick sanity check
					if ((2 * ((bbw + 7) / 8)) != helper.keyword_length())
					{
						osd_printf_error("render_font::load_bdf: incorrect length for bitmap line \"%.*s\"\n", int(helper.keyword_length()), &*helper.keyword_begin());
						return false;
					}
					else if (std::find_if(helper.keyword_begin(), helper.keyword_end(), nothex) != helper.keyword_end())
					{
						osd_printf_error("render_font::load_bdf: found invalid character in bitmap line \"%.*s\"\n", int(helper.keyword_length()), &*helper.keyword_begin());
						return false;
					}

					// track number of rows
					if (1 == ++bitmap_rows)
						bitmap_data = &*helper.keyword_begin();

				}
				else if (helper.is_keyword("ENCODING"))
				{
					// check for duplicate glyph encoding
					if (have_encoding)
					{
						osd_printf_error("render_font::load_bdf: found additional glyph encoding \"%.*s\"\n", int(helper.value_length()), &*helper.value_begin());
						return false;
					}
					have_encoding = true;

					// need to support Adobe Standard Encoding "123" and non-standard glyph index "-1 123"
					std::string const value(helper.value_begin(), helper.value_end());
					int aux;
					int const cnt(sscanf(value.c_str(), "%d %d", &encoding, &aux));
					if ((2 == cnt) && (-1 == encoding) && (0 <= aux))
					{
						encoding = aux;
					}
					else if ((1 != cnt) || (0 > encoding))
					{
						osd_printf_error("render_font::load_bdf: failed to parse glyph encoding \"%.*s\"\n", int(helper.value_length()), &*helper.value_begin());
						return false;
					}
					LOG("render_font::load_bdf: got glyph encoding %d\n", encoding);
				}
				else if (helper.is_keyword("DWIDTH"))
				{
					// check for duplicate advance
					if (have_advance)
					{
						osd_printf_error("render_font::load_bdf: found additional pixel width \"%.*s\"\n", int(helper.value_length()), &*helper.value_begin());
						return false;
					}
					have_advance = true;

					// completely ignore vertical advance
					int yadvance;
					if (2 == sscanf(&*helper.value_begin(), "%d %d", &xadvance, &yadvance))
					{
						LOG("render_font::load_bdf: got pixel width %d,%d\n", xadvance, yadvance);
					}
					else
					{
						osd_printf_error("render_font::load_bdf: failed to parse pixel width \"%.*s\"\n", int(helper.value_length()), &*helper.value_begin());
						return false;
					}
				}
				else if (helper.is_keyword("BBX"))
				{
					// check for duplicate black pixel box
					if (have_bbounds)
					{
						osd_printf_error("render_font::load_bdf: found additional pixel width \"%.*s\"\n", int(helper.value_length()), &*helper.value_begin());
						return false;
					}
					have_bbounds = true;

					// extract position/size of black pixel area
					if (4 == sscanf(&*helper.value_begin(), "%d %d %d %d", &bbw, &bbh, &bbxoff, &bbyoff))
					{
						LOG("render_font::load_bdf: got black pixel box %dx%d %d,%d\n", bbw, bbh, bbxoff, bbyoff);
						if ((0 > bbw) || (0 > bbh))
						{
							osd_printf_error("render_font::load_bdf: black pixel box is invalid\n");
							return false;
						}
					}
					else
					{
						osd_printf_error("render_font::load_bdf: failed to parse black pixel box \"%.*s\"\n", int(helper.value_length()), &*helper.value_begin());
						return false;
					}
				}
				else if (helper.is_keyword("BITMAP"))
				{
					// this is the bitmap - we need to already have properties before we get here
					if (!have_advance)
					{
						osd_printf_error("render_font::load_bdf: glyph has no pixel width\n");
						return false;
					}
					else if (!have_bbounds)
					{
						osd_printf_error("render_font::load_bdf: glyph has no black pixel box\n");
						return false;
					}
					in_bitmap = true;
				}
			}

			// now check that we have what we need
			if (!in_bitmap)
			{
				osd_printf_error("render_font::load_bdf: glyph has no bitmap\n");
				return false;
			}
			else if (bitmap_rows != bbh)
			{
				osd_printf_error("render_font::load_bdf: incorrect number of bitmap lines %d\n", bitmap_rows);
				return false;
			}

			// some kinds of characters will screw us up
			if (0 > xadvance)
			{
				LOG("render_font::load_bdf: ignoring character with negative x advance\n");
			}
			else if ((256 * ARRAY_LENGTH(m_glyphs)) <= encoding)
			{
				LOG("render_font::load_bdf: ignoring character with encoding outside range\n");
			}
			else
			{
				// if we don't have a subtable yet, make one
				if (!m_glyphs[encoding / 256])
				{
					try
					{
						m_glyphs[encoding / 256] = new glyph[256];
					}
					catch (...)
					{
						osd_printf_error("render_font::load_bdf: allocation failed\n");
						return false;
					}
				}

				// fill in the entry
				glyph &gl = m_glyphs[encoding / 256][encoding % 256];
				gl.width = xadvance;
				gl.bmwidth = bbw;
				gl.bmheight = bbh;
				gl.xoffs = bbxoff;
				gl.yoffs = bbyoff;
				gl.rawdata = bitmap_data;
			}

			// some progress for big fonts
			if (0 == (++charcount % 256))
				osd_printf_warning("Loading BDF font... (%d characters loaded)\n", charcount);
		}
	}

	// check number of characters
	if (expected != charcount)
	{
		osd_printf_error("render_font::load_bdf: incorrect character count %d\n", charcount);
		return false;
	}

	// should have bailed by now if something went wrong
>>>>>>> upstream/master
	return true;
}


//-------------------------------------------------
//  load_cached - load a font in cached format
//-------------------------------------------------

<<<<<<< HEAD
bool render_font::load_cached(emu_file &file, UINT32 hash)
{
	// get the file size
	UINT64 filesize = file.size();

	// first read the header
	UINT8 header[CACHED_HEADER_SIZE];
	UINT32 bytes_read = file.read(header, CACHED_HEADER_SIZE);
	if (bytes_read != CACHED_HEADER_SIZE)
		return false;

	// validate the header
	if (header[0] != 'f' || header[1] != 'o' || header[2] != 'n' || header[3] != 't')
		return false;
	if (header[4] != (UINT8)(hash >> 24) || header[5] != (UINT8)(hash >> 16) || header[6] != (UINT8)(hash >> 8) || header[7] != (UINT8)hash)
		return false;
	m_height = (header[8] << 8) | header[9];
	m_scale = 1.0f / (float)m_height;
	m_yoffs = (INT16)((header[10] << 8) | header[11]);
	UINT32 numchars = (header[12] << 24) | (header[13] << 16) | (header[14] << 8) | header[15];
	if (filesize - CACHED_HEADER_SIZE < numchars * CACHED_CHAR_SIZE)
		return false;

	// now read the rest of the data
	m_rawdata.resize(filesize - CACHED_HEADER_SIZE);
	bytes_read = file.read(&m_rawdata[0], filesize - CACHED_HEADER_SIZE);
	if (bytes_read != filesize - CACHED_HEADER_SIZE)
	{
		m_rawdata.clear();
		return false;
	}

	// extract the data from the data
	UINT64 offset = numchars * CACHED_CHAR_SIZE;
	for (int chindex = 0; chindex < numchars; chindex++)
	{
		const UINT8 *info = reinterpret_cast<UINT8 *>(&m_rawdata[chindex * CACHED_CHAR_SIZE]);
		int chnum = (info[0] << 8) | info[1];

		// if we don't have a subtable yet, make one
		if (!m_glyphs[chnum / 256])
			m_glyphs[chnum / 256] = new glyph[256];

		// fill in the entry
		glyph &gl = m_glyphs[chnum / 256][chnum % 256];
		gl.width = (info[2] << 8) | info[3];
		gl.xoffs = (INT16)((info[4] << 8) | info[5]);
		gl.yoffs = (INT16)((info[6] << 8) | info[7]);
		gl.bmwidth = (info[8] << 8) | info[9];
		gl.bmheight = (info[10] << 8) | info[11];
		gl.rawdata = &m_rawdata[offset];

		// advance the offset past the character
		offset += (gl.bmwidth * gl.bmheight + 7) / 8;
		if (offset > filesize - CACHED_HEADER_SIZE)
		{
			m_rawdata.clear();
			return false;
		}
	}

	// reuse the chartable as a temporary buffer
	m_format = FF_CACHED;
	return true;
}

bool render_font::load_cached_cmd(emu_file &file, UINT32 hash)
{
#ifdef UI_COLOR_DISPLAY
	//mamep: color glyph
	#include "cmdtable.inc"
#endif /* UI_COLOR_DISPLAY */
	// get the file size
	UINT64 filesize = file.size();

	// first read the header
	UINT8 header[CACHED_HEADER_SIZE];
	UINT32 bytes_read = file.read(header, CACHED_HEADER_SIZE);
	if (bytes_read != CACHED_HEADER_SIZE)
		return false;

	// validate the header
	if (header[0] != 'f' || header[1] != 'o' || header[2] != 'n' || header[3] != 't')
		return false;
	if (header[4] != (UINT8)(hash >> 24) || header[5] != (UINT8)(hash >> 16) || header[6] != (UINT8)(hash >> 8) || header[7] != (UINT8)hash)
		return false;
	m_height_cmd = (header[8] << 8) | header[9];
//	m_scale = 1.0f / (float)m_height;
	m_yoffs_cmd = (INT16)((header[10] << 8) | header[11]);
	UINT32 numchars = (header[12] << 24) | (header[13] << 16) | (header[14] << 8) | header[15];
	if (filesize - CACHED_HEADER_SIZE < numchars * CACHED_CHAR_SIZE)
		return false;

	// now read the rest of the data
	m_rawdata_cmd.resize(filesize - CACHED_HEADER_SIZE);
	bytes_read = file.read(&m_rawdata_cmd[0], filesize - CACHED_HEADER_SIZE);
	if (bytes_read != filesize - CACHED_HEADER_SIZE)
	{
		m_rawdata_cmd.clear();
		return false;
	}

	// extract the data from the data
	UINT64 offset = numchars * CACHED_CHAR_SIZE;
	for (int chindex = 0; chindex < numchars; chindex++)
	{
		const UINT8 *info = reinterpret_cast<UINT8 *>(&m_rawdata_cmd[chindex * CACHED_CHAR_SIZE]);
		int chnum = (info[0] << 8) | info[1];

		// if we don't have a subtable yet, make one
		if (!m_glyphs_cmd[chnum / 256])
			m_glyphs_cmd[chnum / 256] = new glyph[256];

		// fill in the entry
		glyph &gl = m_glyphs_cmd[chnum / 256][chnum % 256];
#ifdef UI_COLOR_DISPLAY
		//mamep: color glyph
		if (chnum >= COMMAND_UNICODE && chnum < COMMAND_UNICODE + COLOR_BUTTONS)
			gl.color = color_table[chnum - COMMAND_UNICODE];
#endif /* UI_COLOR_DISPLAY */
		gl.width = (info[2] << 8) | info[3];
		gl.xoffs = (INT16)((info[4] << 8) | info[5]);
		gl.yoffs = (INT16)((info[6] << 8) | info[7]);
		gl.bmwidth = (info[8] << 8) | info[9];
		gl.bmheight = (info[10] << 8) | info[11];
		gl.rawdata = &m_rawdata_cmd[offset];

		// advance the offset past the character
		offset += (gl.bmwidth * gl.bmheight + 7) / 8;
		if (offset > filesize - CACHED_HEADER_SIZE)
		{
			m_rawdata_cmd.clear();
=======
bool render_font::load_cached(emu_file &file, u64 length, u32 hash)
{
	// get the file size, read the header, and check that it looks good
	u64 const filesize(file.size());
	bdc_header header;
	if (!header.read(file))
	{
		osd_printf_warning("render_font::load_cached: error reading BDC header\n");
		return false;
	}
	else if (!header.check_magic() || (bdc_header::MAJVERSION != header.get_major_version()) || (bdc_header::MINVERSION != header.get_minor_version()))
	{
		LOG("render_font::load_cached: incompatible BDC file\n");
		return false;
	}
	else if (length && ((header.get_original_length() != length) || (header.get_original_hash() != hash)))
	{
		LOG("render_font::load_cached: BDC file does not match original BDF file\n");
		return false;
	}

	// get global properties from the header
	m_height = header.get_height();
	m_scale = 1.0f / float(m_height);
	m_yoffs = header.get_y_offset();
	m_defchar = header.get_default_character();
	u32 const numchars(header.get_glyph_count());
	if ((file.tell() + (u64(numchars) * bdc_table_entry::size())) > filesize)
	{
		LOG("render_font::load_cached: BDC file is too small to hold glyph table\n");
		return false;
	}

	// now read the rest of the data
	u64 const remaining(filesize - file.tell());
	try
	{
		m_rawdata.resize(std::size_t(remaining));
	}
	catch (...)
	{
		osd_printf_error("render_font::load_cached: allocation error\n");
	}
	for (u64 bytes_read = 0; remaining > bytes_read; )
	{
		u32 const chunk((std::min)(u64(std::numeric_limits<u32>::max()), remaining));
		if (file.read(&m_rawdata[bytes_read], chunk) != chunk)
		{
			osd_printf_error("render_font::load_cached: error reading BDC data\n");
			m_rawdata.clear();
			return false;
		}
		bytes_read += chunk;
	}

	// extract the data from the data
	std::size_t offset(std::size_t(numchars) * bdc_table_entry::size());
	bdc_table_entry entry(m_rawdata.empty() ? nullptr : &m_rawdata[0]);
	for (unsigned chindex = 0; chindex < numchars; chindex++, entry = entry.get_next())
	{
		// if we don't have a subtable yet, make one
		int const chnum(entry.get_encoding());
		LOG("render_font::load_cached: loading character %d\n", chnum);
		if (!m_glyphs[chnum / 256])
		{
			try
			{
				m_glyphs[chnum / 256] = new glyph[256];
			}
			catch (...)
			{
				osd_printf_error("render_font::load_cached: allocation error\n");
				m_rawdata.clear();
				return false;
			}
		}

		// fill in the entry
		glyph &gl = m_glyphs[chnum / 256][chnum % 256];
		gl.width = entry.get_x_advance();
		gl.xoffs = entry.get_bb_x_offset();
		gl.yoffs = entry.get_bb_y_offset();
		gl.bmwidth = entry.get_bb_width();
		gl.bmheight = entry.get_bb_height();
		gl.rawdata = &m_rawdata[offset];

		// advance the offset past the character
		offset += (gl.bmwidth * gl.bmheight + 7) / 8;
		if (m_rawdata.size() < offset)
		{
			osd_printf_verbose("render_font::load_cached: BDC file too small to hold all glyphs\n");
			m_rawdata.clear();
>>>>>>> upstream/master
			return false;
		}
	}

<<<<<<< HEAD
	// reuse the chartable as a temporary buffer
//	m_format = FF_CACHED;
=======
	// got everything
	m_format = format::CACHED;
>>>>>>> upstream/master
	return true;
}


//-------------------------------------------------
//  save_cached - save a font in cached format
//-------------------------------------------------

<<<<<<< HEAD
bool render_font::save_cached(const char *filename, UINT32 hash)
=======
bool render_font::save_cached(const char *filename, u64 length, u32 hash)
>>>>>>> upstream/master
{
	osd_printf_warning("Generating cached BDF font...\n");

	// attempt to open the file
<<<<<<< HEAD
	emu_file file(manager().machine().options().font_path(), OPEN_FLAG_WRITE | OPEN_FLAG_CREATE);
	file_error filerr = file.open(filename);
	if (filerr != FILERR_NONE)
		return false;

	// determine the number of characters
	int numchars = 0;
	for (int chnum = 0; chnum < 65536; chnum++)
	{
		if (m_glyphs[chnum / 256])
		{
			glyph &gl = m_glyphs[chnum / 256][chnum % 256];
			if (gl.width > 0)
				numchars++;
		}
	}

	try
	{
		// allocate an array to hold the character data
		dynamic_buffer chartable(numchars * CACHED_CHAR_SIZE, 0);

		// allocate a temp buffer to compress into
		dynamic_buffer tempbuffer(65536);

		// write the header
		UINT8 *dest = &tempbuffer[0];
		*dest++ = 'f';
		*dest++ = 'o';
		*dest++ = 'n';
		*dest++ = 't';
		*dest++ = hash >> 24;
		*dest++ = hash >> 16;
		*dest++ = hash >> 8;
		*dest++ = hash & 0xff;
		*dest++ = m_height >> 8;
		*dest++ = m_height & 0xff;
		*dest++ = m_yoffs >> 8;
		*dest++ = m_yoffs & 0xff;
		*dest++ = numchars >> 24;
		*dest++ = numchars >> 16;
		*dest++ = numchars >> 8;
		*dest++ = numchars & 0xff;
		assert(dest == &tempbuffer[CACHED_HEADER_SIZE]);
		UINT32 bytes_written = file.write(&tempbuffer[0], CACHED_HEADER_SIZE);
		if (bytes_written != dest - &tempbuffer[0])
			throw emu_fatalerror("Error writing cached file");

		// write the empty table to the beginning of the file
		bytes_written = file.write(&chartable[0], numchars * CACHED_CHAR_SIZE);
		if (bytes_written != numchars * CACHED_CHAR_SIZE)
			throw emu_fatalerror("Error writing cached file");

		// loop over all characters
		int tableindex = 0;
		for (int chnum = 0; chnum < 65536; chnum++)
		{
			glyph &gl = get_char(chnum);
			if (gl.width > 0)
			{
=======
	emu_file file(m_manager.machine().options().font_path(), OPEN_FLAG_WRITE | OPEN_FLAG_CREATE);
	osd_file::error const filerr = file.open(filename);
	if (osd_file::error::NONE != filerr)
		return false;

	// count glyphs
	unsigned numchars = 0;
	for (glyph const *const page : m_glyphs)
	{
		for (unsigned chnum = 0; page && (256 > chnum); ++chnum)
		{
			if (0 < page[chnum].width)
				++numchars;
		}
	}
	LOG("render_font::save_cached: %u glyphs with positive advance to save\n", numchars);

	try
	{
		u32 bytes_written;

		{
			LOG("render_font::save_cached: writing header\n");
			bdc_header hdr;
			hdr.set_magic();
			hdr.set_version();
			hdr.set_original_length(length);
			hdr.set_original_hash(hash);
			hdr.set_glyph_count(numchars);
			hdr.set_height(m_height);
			hdr.set_y_offset(m_yoffs);
			hdr.set_default_character(m_defchar);
			if (!hdr.write(file))
				throw emu_fatalerror("Error writing cached file");
		}
		u64 const table_offs(file.tell());

		// allocate an array to hold the character data
		std::vector<u8> chartable(std::size_t(numchars) * bdc_table_entry::size(), 0);

		// allocate a temp buffer to compress into
		std::vector<u8> tempbuffer(65536);

		// write the empty table to the beginning of the file
		bytes_written = file.write(&chartable[0], chartable.size());
		if (bytes_written != chartable.size())
			throw emu_fatalerror("Error writing cached file");

		// loop over all characters
		bdc_table_entry table_entry(chartable.empty() ? nullptr : &chartable[0]);
		for (unsigned chnum = 0; chnum < (256 * ARRAY_LENGTH(m_glyphs)); chnum++)
		{
			if (m_glyphs[chnum / 256] && (0 < m_glyphs[chnum / 256][chnum % 256].width))
			{
				LOG("render_font::save_cached: writing glyph %u\n", chnum);
				glyph &gl(get_char(chnum));

>>>>>>> upstream/master
				// write out a bit-compressed bitmap if we have one
				if (gl.bitmap.valid())
				{
					// write the data to the tempbuffer
<<<<<<< HEAD
					dest = &tempbuffer[0];
					UINT8 accum = 0;
					UINT8 accbit = 7;
=======
					u8 *dest = &tempbuffer[0];
					u8 accum = 0;
					u8 accbit = 7;
>>>>>>> upstream/master

					// bit-encode the character data
					for (int y = 0; y < gl.bmheight; y++)
					{
						int desty = y + m_height + m_yoffs - gl.yoffs - gl.bmheight;
<<<<<<< HEAD
						const UINT32 *src = (desty >= 0 && desty < m_height) ? &gl.bitmap.pix32(desty) : NULL;
						for (int x = 0; x < gl.bmwidth; x++)
						{
							if (src != NULL && rgb_t(src[x]).a() != 0)
=======
						const u32 *src = (desty >= 0 && desty < m_height) ? &gl.bitmap.pix32(desty) : nullptr;
						for (int x = 0; x < gl.bmwidth; x++)
						{
							if (src != nullptr && rgb_t(src[x]).a() != 0)
>>>>>>> upstream/master
								accum |= 1 << accbit;
							if (accbit-- == 0)
							{
								*dest++ = accum;
								accum = 0;
								accbit = 7;
							}
						}
					}

					// flush any extra
					if (accbit != 7)
						*dest++ = accum;

					// write the data
					bytes_written = file.write(&tempbuffer[0], dest - &tempbuffer[0]);
					if (bytes_written != dest - &tempbuffer[0])
						throw emu_fatalerror("Error writing cached file");

					// free the bitmap and texture
					m_manager.texture_free(gl.texture);
					gl.bitmap.reset();
<<<<<<< HEAD
					gl.texture = NULL;
				}

				// compute the table entry
				dest = &chartable[tableindex++ * CACHED_CHAR_SIZE];
				*dest++ = chnum >> 8;
				*dest++ = chnum & 0xff;
				*dest++ = gl.width >> 8;
				*dest++ = gl.width & 0xff;
				*dest++ = gl.xoffs >> 8;
				*dest++ = gl.xoffs & 0xff;
				*dest++ = gl.yoffs >> 8;
				*dest++ = gl.yoffs & 0xff;
				*dest++ = gl.bmwidth >> 8;
				*dest++ = gl.bmwidth & 0xff;
				*dest++ = gl.bmheight >> 8;
				*dest++ = gl.bmheight & 0xff;
=======
					gl.texture = nullptr;
				}

				// compute the table entry
				table_entry.set_encoding(chnum);
				table_entry.set_x_advance(gl.width);
				table_entry.set_bb_x_offset(gl.xoffs);
				table_entry.set_bb_y_offset(gl.yoffs);
				table_entry.set_bb_width(gl.bmwidth);
				table_entry.set_bb_height(gl.bmheight);
				table_entry = table_entry.get_next();
>>>>>>> upstream/master
			}
		}

		// seek back to the beginning and rewrite the table
<<<<<<< HEAD
		file.seek(CACHED_HEADER_SIZE, SEEK_SET);
		bytes_written = file.write(&chartable[0], numchars * CACHED_CHAR_SIZE);
		if (bytes_written != numchars * CACHED_CHAR_SIZE)
			throw emu_fatalerror("Error writing cached file");
=======
		if (!chartable.empty())
		{
			LOG("render_font::save_cached: writing character table\n");
			file.seek(table_offs, SEEK_SET);
			u8 const *bytes(&chartable[0]);
			for (u64 remaining = chartable.size(); remaining; )
			{
				u32 const chunk((std::min<u64>)(std::numeric_limits<u32>::max(), remaining));
				bytes_written = file.write(bytes, chunk);
				if (chunk != bytes_written)
					throw emu_fatalerror("Error writing cached file");
				bytes += chunk;
				remaining -= chunk;
			}
		}

		// no trouble?
>>>>>>> upstream/master
		return true;
	}
	catch (...)
	{
		file.remove_on_close();
		return false;
	}
}


<<<<<<< HEAD
//mamep: convert command glyph
void convert_command_glyph(char *s, int buflen)
{
	unicode_char uchar;
	char *d;
	int ucharcount;
	int len;
	int i, j;

#include "cmdplus.cpp"

	d = global_alloc_array(char, buflen * sizeof (*d));
	if (d == NULL)
	{
		*s = '\0';
		return;
	}

	len = strlen(s);
	for (i = j = 0; i < len; )
	{
		struct fix_command_t *fixcmd = NULL;

		ucharcount = uchar_from_utf8(&uchar, s + i, len - i);
		if (ucharcount == -1)
			break;

		if (ucharcount != 1)
			goto process_next;

		if (s[i]  == '\\' && s[i + 1] == 'n')
		{
			uchar = '\n';
			goto process_next;
		}

#ifdef COMMAND_CONVERT_TEXT
		if (s[i] == COMMAND_CONVERT_TEXT)
		{
			struct fix_strings_t *fixtext = convert_text;

			if (s[i]  == s[i + 1])
			{
				i++;
				goto process_next;
			}

			while (fixtext->glyph_code)
			{
				if (!fixtext->glyph_str_len)
					fixtext->glyph_str_len = strlen(fixtext->glyph_str);

				if (strncmp(fixtext->glyph_str, s + i + 1, fixtext->glyph_str_len) == 0)
				{
					uchar = fixtext->glyph_code + COMMAND_UNICODE;
					i += strlen(fixtext->glyph_str);
					goto process_next;
				}

				fixtext++;
			}
		}
#endif /* COMMAND_CONVERT_TEXT */

#ifdef COMMAND_DEFAULT_TEXT
		if (s[i] == COMMAND_DEFAULT_TEXT)
			fixcmd = default_text;
#endif /* COMMAND_DEFAULT_TEXT */

#ifdef COMMAND_EXPAND_TEXT
		if (s[i] == COMMAND_EXPAND_TEXT)
			fixcmd = expand_text;
#endif /* COMMAND_EXPAND_TEXT */

		if (fixcmd)
		{
			if (s[i]  == s[i + 1])
			{
				i++;
				goto process_next;
			}

			while (fixcmd->glyph_code)
			{
				if (s[i + 1] == fixcmd->glyph_char)
				{
					uchar = fixcmd->glyph_code + COMMAND_UNICODE;
					i++;
					goto process_next;
				}

				fixcmd++;
			}
		}

process_next:
		i += ucharcount;

		ucharcount = utf8_from_uchar(d + j, buflen - j - 1, uchar);
		if (ucharcount == -1)
			break;

		j += ucharcount;
	}

	d[j] = '\0';

	strcpy(s, d);
	global_free_array(d);
=======
void render_font::render_font_command_glyph()
{
	// FIXME: this is copy/pasta from the BDC loading, and it shouldn't be injected into every font
	emu_file file(OPEN_FLAG_READ);
	if (file.open_ram(font_uicmd14, sizeof(font_uicmd14)) == osd_file::error::NONE)
	{
		// get the file size, read the header, and check that it looks good
		u64 const filesize(file.size());
		bdc_header header;
		if (!header.read(file))
		{
			osd_printf_warning("render_font::render_font_command_glyph: error reading BDC header\n");
			return;
		}
		else if (!header.check_magic() || (bdc_header::MAJVERSION != header.get_major_version()) || (bdc_header::MINVERSION != header.get_minor_version()))
		{
			LOG("render_font::render_font_command_glyph: incompatible BDC file\n");
			return;
		}

		// get global properties from the header
		m_height_cmd = header.get_height();
		m_yoffs_cmd = header.get_y_offset();
		u32 const numchars(header.get_glyph_count());
		if ((file.tell() + (u64(numchars) * bdc_table_entry::size())) > filesize)
		{
			LOG("render_font::render_font_command_glyph: BDC file is too small to hold glyph table\n");
			return;
		}

		// now read the rest of the data
		u64 const remaining(filesize - file.tell());
		try
		{
			m_rawdata_cmd.resize(std::size_t(remaining));
		}
		catch (...)
		{
			osd_printf_error("render_font::render_font_command_glyph: allocation error\n");
		}
		for (u64 bytes_read = 0; remaining > bytes_read; )
		{
			u32 const chunk((std::min)(u64(std::numeric_limits<u32>::max()), remaining));
			if (file.read(&m_rawdata_cmd[bytes_read], chunk) != chunk)
			{
				osd_printf_error("render_font::render_font_command_glyph: error reading BDC data\n");
				m_rawdata_cmd.clear();
				return;
			}
			bytes_read += chunk;
		}

		// extract the data from the data
		std::size_t offset(std::size_t(numchars) * bdc_table_entry::size());
		bdc_table_entry entry(m_rawdata_cmd.empty() ? nullptr : &m_rawdata_cmd[0]);
		for (unsigned chindex = 0; chindex < numchars; chindex++, entry = entry.get_next())
		{
			// if we don't have a subtable yet, make one
			int const chnum(entry.get_encoding());
			LOG("render_font::render_font_command_glyph: loading character %d\n", chnum);
			if (!m_glyphs_cmd[chnum / 256])
			{
				try
				{
					m_glyphs_cmd[chnum / 256] = new glyph[256];
				}
				catch (...)
				{
					osd_printf_error("render_font::render_font_command_glyph: allocation error\n");
					m_rawdata_cmd.clear();
					return;
				}
			}

			// fill in the entry
			glyph &gl = m_glyphs_cmd[chnum / 256][chnum % 256];
			gl.width = entry.get_x_advance();
			gl.xoffs = entry.get_bb_x_offset();
			gl.yoffs = entry.get_bb_y_offset();
			gl.bmwidth = entry.get_bb_width();
			gl.bmheight = entry.get_bb_height();
			gl.rawdata = &m_rawdata_cmd[offset];

			// advance the offset past the character
			offset += (gl.bmwidth * gl.bmheight + 7) / 8;
			if (m_rawdata_cmd.size() < offset)
			{
				osd_printf_verbose("render_font::render_font_command_glyph: BDC file too small to hold all glyphs\n");
				m_rawdata_cmd.clear();
				return;
			}
		}
	}
>>>>>>> upstream/master
}
