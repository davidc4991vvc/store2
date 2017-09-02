// license:BSD-3-Clause
<<<<<<< HEAD
// copyright-holders:Aaron Giles
=======
// copyright-holders:Aaron Giles, Vas Crabb
>>>>>>> upstream/master
/***************************************************************************

    rendfont.h

    Rendering system font management.

***************************************************************************/

<<<<<<< HEAD
#ifndef __RENDFONT_H__
#define __RENDFONT_H__

#include "render.h"

// forward instead of include
class osd_font;

=======
#ifndef MAME_EMU_RENDFONT_H
#define MAME_EMU_RENDFONT_H

#include "render.h"

>>>>>>> upstream/master
//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************


// ======================> render_font

// a render_font describes and provides an interface to a font
class render_font
{
	friend class render_manager;
<<<<<<< HEAD
	friend resource_pool_object<render_font>::~resource_pool_object();
=======
>>>>>>> upstream/master

	// construction/destruction
	render_font(render_manager &manager, const char *filename);
	virtual ~render_font();

public:
	// getters
	render_manager &manager() const { return m_manager; }

	// size queries
<<<<<<< HEAD
	INT32 pixel_height() const { return m_height; }
	float char_width(float height, float aspect, unicode_char ch);
	//mamep: to render as fixed-width font
	float char_width_no_margin(float height, float aspect, unicode_char ch);
=======
	s32 pixel_height() const { return m_height; }
	float char_width(float height, float aspect, char32_t ch);
>>>>>>> upstream/master
	float string_width(float height, float aspect, const char *string);
	float utf8string_width(float height, float aspect, const char *utf8string);

	// texture/bitmap queries
<<<<<<< HEAD
	render_texture *get_char_texture_and_bounds(float height, float aspect, unicode_char ch, render_bounds &bounds);
	void get_scaled_bitmap_and_bounds(bitmap_argb32 &dest, float height, float aspect, unicode_char chnum, rectangle &bounds);
=======
	render_texture *get_char_texture_and_bounds(float height, float aspect, char32_t ch, render_bounds &bounds);
	void get_scaled_bitmap_and_bounds(bitmap_argb32 &dest, float height, float aspect, char32_t chnum, rectangle &bounds);
>>>>>>> upstream/master

private:
	// a glyph describes a single glyph
	class glyph
	{
	public:
		glyph()
<<<<<<< HEAD
			: width(0),
				xoffs(0), yoffs(0),
				bmwidth(0), bmheight(0),
				rawdata(NULL),
				texture(NULL)
#ifdef UI_COLOR_DISPLAY
				,color(0)
#endif /* UI_COLOR_DISPLAY */
				{}

		INT32               width;              // width from this character to the next
		INT32               xoffs, yoffs;       // X and Y offset from baseline to top,left of bitmap
		INT32               bmwidth, bmheight;  // width and height of bitmap
		const char *        rawdata;            // pointer to the raw data for this one
		render_texture *    texture;            // pointer to a texture for rendering and sizing
		bitmap_argb32       bitmap;             // pointer to the bitmap containing the raw data
#ifdef UI_COLOR_DISPLAY
		//mamep: for color glyph
		int                 color;
#endif /* UI_COLOR_DISPLAY */
	};

	// internal format
	enum format
	{
		FF_UNKNOWN,
		FF_TEXT,
		FF_CACHED,
		FF_OSD
	};

	// helpers
	glyph &get_char(unicode_char chnum);
	void char_expand(unicode_char chnum, glyph &ch);
	bool load_cached_bdf(const char *filename);
	bool load_bdf();
	bool load_cached(emu_file &file, UINT32 hash);
	bool load_cached_cmd(emu_file &file, UINT32 hash);
	bool save_cached(const char *filename, UINT32 hash);
=======
			: width(-1)
			, xoffs(-1), yoffs(-1)
			, bmwidth(0), bmheight(0)
			, rawdata(nullptr)
			, texture(nullptr)
			, bitmap()
			, color()
		{
		}

		s32                 width;              // width from this character to the next
		s32                 xoffs, yoffs;       // X and Y offset from baseline to top,left of bitmap
		s32                 bmwidth, bmheight;  // width and height of bitmap
		const char *        rawdata;            // pointer to the raw data for this one
		render_texture *    texture;            // pointer to a texture for rendering and sizing
		bitmap_argb32       bitmap;             // pointer to the bitmap containing the raw data

		rgb_t               color;
	};

	// internal format
	enum class format
	{
		UNKNOWN,
		TEXT,
		CACHED,
		OSD
	};

	// helpers
	glyph &get_char(char32_t chnum);
	void char_expand(char32_t chnum, glyph &ch);
	bool load_cached_bdf(const char *filename);
	bool load_bdf();
	bool load_cached(emu_file &file, u64 length, u32 hash);
	bool save_cached(const char *filename, u64 length, u32 hash);

	void render_font_command_glyph();
>>>>>>> upstream/master

	// internal state
	render_manager &    m_manager;
	format              m_format;           // format of font data
	int                 m_height;           // height of the font, from ascent to descent
	int                 m_yoffs;            // y offset from baseline to descent
<<<<<<< HEAD
	float               m_scale;            // 1 / height precomputed
	glyph               *m_glyphs[256];     // array of glyph subtables
	std::vector<char>   m_rawdata;          // pointer to the raw data for the font
	UINT64              m_rawsize;          // size of the raw font data
	osd_font            *m_osdfont;         // handle to the OSD font
	//mamep: for command glyph
	int                 m_height_cmd;       // height of the font, from ascent to descent
	int                 m_yoffs_cmd;        // y offset from baseline to descent
	glyph               *m_glyphs_cmd[256]; // array of glyph subtables
	std::vector<char>   m_rawdata_cmd;      // pointer to the raw data for the font

	//mamep: allocate command glyph font
	void render_font_command_glyph();

	// constants
	static const int CACHED_CHAR_SIZE       = 12;
	static const int CACHED_HEADER_SIZE     = 16;
	static const int CACHED_BDF_HASH_SIZE   = 1024;
};


//mamep: convert command glyph
void convert_command_glyph(char *s, int buflen);

#endif  /* __RENDFONT_H__ */
=======
	int                 m_defchar;          // default substitute character
	float               m_scale;            // 1 / height precomputed
	glyph               *m_glyphs[17*256];  // array of glyph subtables
	std::vector<char>   m_rawdata;          // pointer to the raw data for the font
	u64                 m_rawsize;          // size of the raw font data
	std::unique_ptr<osd_font> m_osdfont;    // handle to the OSD font

	int                 m_height_cmd;       // height of the font, from ascent to descent
	int                 m_yoffs_cmd;        // y offset from baseline to descent
	EQUIVALENT_ARRAY(m_glyphs, glyph *) m_glyphs_cmd; // array of glyph subtables
	std::vector<char>   m_rawdata_cmd;      // pointer to the raw data for the font

	// constants
	static const u64 CACHED_BDF_HASH_SIZE   = 1024;
};

void convert_command_glyph(std::string &s);

#endif  /* MAME_EMU_RENDFONT_H */
>>>>>>> upstream/master
