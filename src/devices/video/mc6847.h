// license:BSD-3-Clause
// copyright-holders:Nathan Woods
/*********************************************************************

    mc6847.h

    Implementation of Motorola 6847 video hardware chip

***************************************************************************/
<<<<<<< HEAD

#pragma once

#ifndef __MC6847__
#define __MC6847__


#define MC6847_MODE_AG      0x80
#define MC6847_MODE_GM2     0x40
#define MC6847_MODE_GM1     0x20
#define MC6847_MODE_GM0     0x10
#define MC6847_MODE_CSS     0x08
#define MC6847_MODE_AS      0x04
#define MC6847_MODE_INTEXT  0x02
#define MC6847_MODE_INV     0x01
=======
#ifndef MAME_VIDEO_MC6847_H
#define MAME_VIDEO_MC6847_H

#pragma once

#include "screen.h"
>>>>>>> upstream/master


//**************************************************************************
//  MC6847 CONFIGURATION / INTERFACE
//**************************************************************************

#define MCFG_SCREEN_MC6847_NTSC_ADD(_tag, _mctag) \
	MCFG_SCREEN_ADD(_tag, RASTER)                               \
	MCFG_SCREEN_UPDATE_DEVICE(_mctag, mc6847_base_device, screen_update) \
	MCFG_SCREEN_REFRESH_RATE(60)                                \
	MCFG_SCREEN_SIZE(320, 243)                                  \
	MCFG_SCREEN_VISIBLE_AREA(0, 320-1, 1, 241-1)                \
	MCFG_SCREEN_VBLANK_TIME(0)

#define MCFG_SCREEN_MC6847_PAL_ADD(_tag, _mctag) \
	MCFG_SCREEN_ADD(_tag, RASTER)                               \
	MCFG_SCREEN_UPDATE_DEVICE(_mctag, mc6847_base_device, screen_update) \
	MCFG_SCREEN_REFRESH_RATE(50)                                \
	MCFG_SCREEN_SIZE(320, 243)                                  \
	MCFG_SCREEN_VISIBLE_AREA(0, 320-1, 1, 241-1)                \
	MCFG_SCREEN_VBLANK_TIME(0)

#define MCFG_MC6847_HSYNC_CALLBACK(_write) \
	devcb = &mc6847_friend_device::set_hsync_wr_callback(*device, DEVCB_##_write);

#define MCFG_MC6847_FSYNC_CALLBACK(_write) \
	devcb = &mc6847_friend_device::set_fsync_wr_callback(*device, DEVCB_##_write);

#define MCFG_MC6847_CHARROM_CALLBACK(_class, _method) \
<<<<<<< HEAD
	mc6847_friend_device::set_get_char_rom(*device, mc6847_get_char_rom_delegate(&_class::_method, #_class "::" #_method, downcast<_class *>(owner)));
=======
	mc6847_friend_device::set_get_char_rom(*device, mc6847_friend_device::get_char_rom_delegate(&_class::_method, #_class "::" #_method, downcast<_class *>(owner)));
>>>>>>> upstream/master

#define MCFG_MC6847_INPUT_CALLBACK(_read) \
	devcb = &mc6847_base_device::set_input_callback(*device, DEVCB_##_read);

#define MCFG_MC6847_FIXED_MODE(_mode) \
	mc6847_base_device::set_get_fixed_mode(*device, _mode);

#define MCFG_MC6847_BW(_bw) \
	mc6847_base_device::set_black_and_white(*device, _bw);


<<<<<<< HEAD
typedef device_delegate<UINT8 (UINT8 ch, int line)> mc6847_get_char_rom_delegate;
#define MC6847_GET_CHARROM_MEMBER(_name)   UINT8 _name(UINT8 ch, int line)
=======
#define MC6847_GET_CHARROM_MEMBER(_name)   uint8_t _name(uint8_t ch, int line)
>>>>>>> upstream/master


#define ARTIFACTING_TAG     "artifacting"

INPUT_PORTS_EXTERN(mc6847_artifacting);


//**************************************************************************
//  MC6847 CORE
//**************************************************************************

// base class so that the GIME emulation can access mc6847 stuff
class mc6847_friend_device : public device_t
{
public:
<<<<<<< HEAD
	// inlines
	bool hs_r(void)                 { return m_horizontal_sync; }
	bool fs_r(void)                 { return m_field_sync; }

	template<class _Object> static devcb_base &set_hsync_wr_callback(device_t &device, _Object object) { return downcast<mc6847_friend_device &>(device).m_write_hsync.set_callback(object); }
	template<class _Object> static devcb_base &set_fsync_wr_callback(device_t &device, _Object object) { return downcast<mc6847_friend_device &>(device).m_write_fsync.set_callback(object); }

	static void set_get_char_rom(device_t &device, mc6847_get_char_rom_delegate callback) { downcast<mc6847_friend_device &>(device).m_charrom_cb = callback; }

protected:
	mc6847_friend_device(const machine_config &mconfig, device_type type, const char *name, const char *tag, device_t *owner, UINT32 clock,
		const UINT8 *fontdata, bool is_mc6847t1, double tpfs, int field_sync_falling_edge_scanline, bool supports_partial_body_scanlines, const char *shortname, const char *source);

	// video mode constants
	static const UINT8 MODE_AG      = 0x80;
	static const UINT8 MODE_GM2     = 0x40;
	static const UINT8 MODE_GM1     = 0x20;
	static const UINT8 MODE_GM0     = 0x10;
	static const UINT8 MODE_CSS     = 0x08;
	static const UINT8 MODE_AS      = 0x04;
	static const UINT8 MODE_INTEXT  = 0x02;
	static const UINT8 MODE_INV     = 0x01;

	// timer constants
	static const device_timer_id TIMER_FRAME = 0;
	static const device_timer_id TIMER_HSYNC_OFF = 1;
	static const device_timer_id TIMER_HSYNC_ON = 2;
	static const device_timer_id TIMER_FSYNC = 3;

	// fonts
	static const UINT8 pal_round_fontdata8x12[];
	static const UINT8 pal_square_fontdata8x12[];
	static const UINT8 ntsc_round_fontdata8x12[];
	static const UINT8 ntsc_square_fontdata8x12[];
	static const UINT8 semigraphics4_fontdata8x12[];
	static const UINT8 semigraphics6_fontdata8x12[];
	static const UINT8 s68047_fontdata8x12[];

	// pixel definitions
	typedef UINT32 pixel_t;
=======
	// video mode constants
	static constexpr uint8_t MODE_AG      = 0x80;
	static constexpr uint8_t MODE_GM2     = 0x40;
	static constexpr uint8_t MODE_GM1     = 0x20;
	static constexpr uint8_t MODE_GM0     = 0x10;
	static constexpr uint8_t MODE_CSS     = 0x08;
	static constexpr uint8_t MODE_AS      = 0x04;
	static constexpr uint8_t MODE_INTEXT  = 0x02;
	static constexpr uint8_t MODE_INV     = 0x01;

	typedef device_delegate<uint8_t (uint8_t ch, int line)> get_char_rom_delegate;

	// inlines
	bool hs_r() const { return m_horizontal_sync; }
	bool fs_r() const { return m_field_sync; }

	template <class Object> static devcb_base &set_hsync_wr_callback(device_t &device, Object &&cb) { return downcast<mc6847_friend_device &>(device).m_write_hsync.set_callback(std::forward<Object>(cb)); }
	template <class Object> static devcb_base &set_fsync_wr_callback(device_t &device, Object &&cb) { return downcast<mc6847_friend_device &>(device).m_write_fsync.set_callback(std::forward<Object>(cb)); }

	static void set_get_char_rom(device_t &device, get_char_rom_delegate &&cb) { downcast<mc6847_friend_device &>(device).m_charrom_cb = std::move(cb); }

protected:
	mc6847_friend_device(const machine_config &mconfig, device_type type, const char *tag, device_t *owner, uint32_t clock,
			const uint8_t *fontdata, bool is_mc6847t1, double tpfs, int field_sync_falling_edge_scanline, bool supports_partial_body_scanlines);

	// timer constants
	static constexpr device_timer_id TIMER_FRAME = 0;
	static constexpr device_timer_id TIMER_HSYNC_OFF = 1;
	static constexpr device_timer_id TIMER_HSYNC_ON = 2;
	static constexpr device_timer_id TIMER_FSYNC = 3;

	// fonts
	static const uint8_t pal_round_fontdata8x12[];
	static const uint8_t pal_square_fontdata8x12[];
	static const uint8_t ntsc_round_fontdata8x12[];
	static const uint8_t ntsc_square_fontdata8x12[];
	static const uint8_t semigraphics4_fontdata8x12[];
	static const uint8_t semigraphics6_fontdata8x12[];
	static const uint8_t s68047_fontdata8x12[];
	static const uint8_t stripes[];

	// pixel definitions
	typedef uint32_t pixel_t;
>>>>>>> upstream/master

	pixel_t *bitmap_addr(bitmap_rgb32 &bitmap, int y, int x)
	{
		return &bitmap.pix32(y, x);
	}

<<<<<<< HEAD
	static UINT8 simplify_mode(UINT8 data, UINT8 mode)
=======
	static uint8_t simplify_mode(uint8_t data, uint8_t mode)
>>>>>>> upstream/master
	{
		// simplifies MC6847 modes to drop mode flags that are not significant
		return mode & ~((mode & MODE_AG) ? (MODE_AS | MODE_INV) : 0);
	}

	// internal class that represents a MC6847 character map
	class character_map
	{
	public:
		// constructor that sets up the font data
<<<<<<< HEAD
		character_map(const UINT8 *fontdata, bool is_mc6847t1);

		// optimized template function that emits a single character
		template<int xscale>
		ATTR_FORCE_INLINE void emit_character(UINT8 mode, const UINT8 *data, int length, pixel_t *RESTRICT pixels, int y, const pixel_t *palette)
=======
		character_map(const uint8_t *fontdata, bool is_mc6847t1);

		// optimized template function that emits a single character
		template<int xscale>
		ATTR_FORCE_INLINE void emit_character(uint8_t mode, const uint8_t *data, int length, pixel_t *RESTRICT pixels, int y, const pixel_t *palette)
>>>>>>> upstream/master
		{
			for (int i = 0; i < length; i++)
			{
				// get the character
<<<<<<< HEAD
				UINT8 character = data[i];
=======
				uint8_t character = data[i];
>>>>>>> upstream/master

				// based on the mode, determine which entry to use
				const entry *e = &m_entries[mode % ARRAY_LENGTH(m_entries)];

				// identify the character in the font data
<<<<<<< HEAD
				const UINT8 *font_character = e->m_fontdata + (character & e->m_character_mask) * 12;

				// get the particular slice out
				UINT8 font_character_slice = font_character[y % 12];

				// get the two colors
				UINT16 color_base_0 = e->m_color_base_0 + ((character >> e->m_color_shift_0) & e->m_color_mask_0);
				UINT16 color_base_1 = e->m_color_base_1 + ((character >> e->m_color_shift_1) & e->m_color_mask_1);
=======
				const uint8_t *font_character = e->m_fontdata + (character & e->m_character_mask) * 12;

				// get the particular slice out
				uint8_t font_character_slice = font_character[y % 12];

				// get the two colors
				uint16_t color_base_0 = e->m_color_base_0 + ((character >> e->m_color_shift_0) & e->m_color_mask_0);
				uint16_t color_base_1 = e->m_color_base_1 + ((character >> e->m_color_shift_1) & e->m_color_mask_1);
>>>>>>> upstream/master
				pixel_t color_0 = palette[color_base_0];
				pixel_t color_1 = palette[color_base_1];

				// emit the bits
				for (int j = 0; j < 8; j++)
				{
					for (int k = 0; k < xscale; k++)
					{
						pixels[(i * 8 + j) * xscale + k] = bit_test(font_character_slice, j, color_0, color_1);
					}
				}
			}
		}

	private:
		struct entry
		{
<<<<<<< HEAD
			const UINT8 *m_fontdata;
			UINT8 m_character_mask;
			UINT8 m_color_shift_0;
			UINT8 m_color_shift_1;
			UINT8 m_color_mask_0;
			UINT8 m_color_mask_1;
			UINT16 m_color_base_0;
			UINT16 m_color_base_1;
=======
			const uint8_t *m_fontdata;
			uint8_t m_character_mask;
			uint8_t m_color_shift_0;
			uint8_t m_color_shift_1;
			uint8_t m_color_mask_0;
			uint8_t m_color_mask_1;
			uint16_t m_color_base_0;
			uint16_t m_color_base_1;
>>>>>>> upstream/master
		};

		// lookup table for MC6847 modes to determine font data and color
		entry m_entries[128];

		// text font data calculated on startup
<<<<<<< HEAD
		UINT8 m_text_fontdata_inverse[64*12];
		UINT8 m_text_fontdata_lower_case[64*12];
		UINT8 m_text_fontdata_lower_case_inverse[64*12];

		// optimized function that tests a single bit
		ATTR_FORCE_INLINE pixel_t bit_test(UINT8 data, int shift, pixel_t color_0, pixel_t color_1)
=======
		uint8_t m_text_fontdata_inverse[64*12];
		uint8_t m_text_fontdata_lower_case[64*12];
		uint8_t m_text_fontdata_lower_case_inverse[64*12];
		uint8_t m_stripes[128*12];

		// optimized function that tests a single bit
		ATTR_FORCE_INLINE pixel_t bit_test(uint8_t data, int shift, pixel_t color_0, pixel_t color_1)
>>>>>>> upstream/master
		{
			return data & (0x80 >> shift) ? color_1 : color_0;
		}
	};

<<<<<<< HEAD
	// artficater internal class
=======
	// artificater internal class
>>>>>>> upstream/master
	class artifacter
	{
	public:
		artifacter();

		// artifacting config
		void setup_config(device_t *device);
<<<<<<< HEAD
		void poll_config(void) { m_artifacting = (m_config!=NULL) ? m_config->read() : 0; }

		// artifacting application
		template<int xscale>
		ATTR_FORCE_INLINE void process_artifacts(pixel_t *pixels, UINT8 mode, const pixel_t *palette)
=======
		void poll_config() { m_artifacting = (m_config!=nullptr) ? m_config->read() : 0; }

		// artifacting application
		template<int xscale>
		ATTR_FORCE_INLINE void process_artifacts(pixel_t *pixels, uint8_t mode, const pixel_t *palette)
>>>>>>> upstream/master
		{
			if (((mode & (MODE_AG|MODE_GM2|MODE_GM1|MODE_GM0)) == (MODE_AG|MODE_GM2|MODE_GM1|MODE_GM0))
				&& (m_artifacting != 0))
			{
				// identify the new colors and update
				pixel_t c0 = palette[(mode & MODE_CSS) ? 10 : 8];
				pixel_t c1 = palette[(mode & MODE_CSS) ? 11 : 9];
				update_colors(c0, c1);

				// generate the new line
				pixel_t new_line[256];
				int x, i;
				for (x = 0; x < 256; x += 2)
				{
<<<<<<< HEAD
					UINT8 val = ((pixels[(x - 2) * xscale] == c1) ? 0x20 : 0x00)
=======
					uint8_t val = ((pixels[(x - 2) * xscale] == c1) ? 0x20 : 0x00)
>>>>>>> upstream/master
						|   ((pixels[(x - 1) * xscale] == c1) ? 0x10 : 0x00)
						|   ((pixels[(x + 0) * xscale] == c1) ? 0x08 : 0x00)
						|   ((pixels[(x + 1) * xscale] == c1) ? 0x04 : 0x00)
						|   ((pixels[(x + 2) * xscale] == c1) ? 0x02 : 0x00)
						|   ((pixels[(x + 3) * xscale] == c1) ? 0x01 : 0x00);

					new_line[x + 0] = m_expanded_colors[val * 2 + 0];
					new_line[x + 1] = m_expanded_colors[val * 2 + 1];
				}

				// and copy it in
				for (x = 0; x < 256; x++)
				{
					for (i = 0; i < xscale; i++)
						pixels[x * xscale + i] = new_line[x];
				}
			}
		}

	private:
		ioport_port *m_config;
		ioport_value m_artifacting;
		ioport_value m_saved_artifacting;
		pixel_t m_saved_c0, m_saved_c1;
		pixel_t m_expanded_colors[128];

		void update_colors(pixel_t c0, pixel_t c1);
<<<<<<< HEAD
		static pixel_t mix_color(double factor, UINT8 c0, UINT8 c1);
=======
		static pixel_t mix_color(double factor, uint8_t c0, uint8_t c1);
>>>>>>> upstream/master
	};

	enum border_color_t
	{
		BORDER_COLOR_BLACK,
		BORDER_COLOR_GREEN,
		BORDER_COLOR_WHITE,
		BORDER_COLOR_ORANGE
	};

	// callbacks
	devcb_write_line   m_write_hsync;
	devcb_write_line   m_write_fsync;

	/* if specified, this reads the external char rom off of the driver state */
	// moved here from mc6847_base_device so to be useable in GIME
<<<<<<< HEAD
	mc6847_get_char_rom_delegate m_charrom_cb;
=======
	get_char_rom_delegate m_charrom_cb;
>>>>>>> upstream/master

	// incidentals
	character_map m_character_map;
	artifacter m_artifacter;

	// device-level overrides
<<<<<<< HEAD
	virtual void device_start(void);
	virtual void device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr);
	virtual void device_reset(void);
	virtual void device_post_load(void);

	// other overridables
	virtual void new_frame(void);
	virtual void horizontal_sync_changed(bool line);
	virtual void field_sync_changed(bool line);
	virtual void enter_bottom_border(void);
	virtual void record_border_scanline(UINT16 physical_scanline);
	virtual void record_body_scanline(UINT16 physical_scanline, UINT16 logical_scanline) = 0;
	virtual void record_partial_body_scanline(UINT16 physical_scanline, UINT16 logical_scanline, INT32 start_clock, INT32 end_clock) = 0;

	// miscellaneous
	void video_flush(void);
	const char *describe_context(void);
=======
	virtual void device_start() override;
	virtual void device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr) override;
	virtual void device_reset() override;
	virtual void device_post_load() override;

	// other overridables
	virtual void new_frame();
	virtual void horizontal_sync_changed(bool line);
	virtual void field_sync_changed(bool line);
	virtual void enter_bottom_border();
	virtual void record_border_scanline(uint16_t physical_scanline);
	virtual void record_body_scanline(uint16_t physical_scanline, uint16_t logical_scanline) = 0;
	virtual void record_partial_body_scanline(uint16_t physical_scanline, uint16_t logical_scanline, int32_t start_clock, int32_t end_clock) = 0;

	// miscellaneous
	void video_flush();
	std::string describe_context() const;
>>>>>>> upstream/master

	// setup functions
	emu_timer *setup_timer(device_timer_id id, double offset, double period);

	// converts to B&W
	static pixel_t black_and_white(rgb_t color)
	{
<<<<<<< HEAD
		UINT8 average_color = (color.r() + color.g() + color.b()) / 3;
=======
		uint8_t average_color = (color.r() + color.g() + color.b()) / 3;
>>>>>>> upstream/master
		return rgb_t(average_color, average_color, average_color);
	}

	// changes the geometry
<<<<<<< HEAD
	ATTR_FORCE_INLINE void set_geometry(UINT16 top_border_scanlines, UINT16 body_scanlines, bool wide)
=======
	ATTR_FORCE_INLINE void set_geometry(uint16_t top_border_scanlines, uint16_t body_scanlines, bool wide)
>>>>>>> upstream/master
	{
		if (UNEXPECTED((m_top_border_scanlines != top_border_scanlines)
			|| (m_body_scanlines != body_scanlines)
			|| (m_wide != wide)))
		{
			m_top_border_scanlines = top_border_scanlines;
			m_body_scanlines = body_scanlines;
			m_wide = wide;
			update_field_sync_timer();
		}
	}

	// calculates the border color
<<<<<<< HEAD
	static ATTR_FORCE_INLINE border_color_t border_value(UINT8 mode, bool is_mc6847t1)
=======
	static ATTR_FORCE_INLINE border_color_t border_value(uint8_t mode, bool is_mc6847t1)
>>>>>>> upstream/master
	{
		border_color_t result;

		if (mode & MODE_AG)
		{
			// graphics
			result = mode & MODE_CSS ? BORDER_COLOR_WHITE : BORDER_COLOR_GREEN;
		}
		else if (!is_mc6847t1 || ((mode & MODE_GM2) == 0))
		{
			// text, black border
			result = BORDER_COLOR_BLACK;
		}
		else
		{
			// text, green or orange border
			result = mode & MODE_CSS ? BORDER_COLOR_ORANGE : BORDER_COLOR_GREEN;
		}
		return result;
	}

	// checks to see if the video has changed
<<<<<<< HEAD
	ATTR_FORCE_INLINE bool has_video_changed(void)
=======
	ATTR_FORCE_INLINE bool has_video_changed()
>>>>>>> upstream/master
	{
		/* poll the artifacting config */
		m_artifacter.poll_config();

		/* if the video didn't change, indicate as much */
		bool video_changed = m_video_changed;
		m_video_changed = false;
		return video_changed;
	}

	// updates a byte in the video state
	template<class T>
	ATTR_FORCE_INLINE bool update_value(T *ptr, T byte)
	{
		bool result = false;
		if (*ptr != byte)
		{
			*ptr = byte;
			m_video_changed = true;
			result = true;
		}
		return result;
	}

	// template function for emitting graphics bytes
	template<int bits_per_pixel, int xscale>
<<<<<<< HEAD
	ATTR_FORCE_INLINE void emit_graphics(const UINT8 *data, int length, pixel_t *RESTRICT pixels, UINT16 color_base, const pixel_t *RESTRICT palette)
=======
	ATTR_FORCE_INLINE void emit_graphics(const uint8_t *data, int length, pixel_t *RESTRICT pixels, uint16_t color_base, const pixel_t *RESTRICT palette)
>>>>>>> upstream/master
	{
		for (int i = 0; i < length; i++)
		{
			for (int j = 0; j < (8 / bits_per_pixel); j++)
			{
				for (int k = 0; k < xscale; k++)
				{
<<<<<<< HEAD
					UINT16 color = color_base + ((data[i] >> (8 - (j + 1) * bits_per_pixel)) & ((1 << bits_per_pixel) - 1));
=======
					uint16_t color = color_base + ((data[i] >> (8 - (j + 1) * bits_per_pixel)) & ((1 << bits_per_pixel) - 1));
>>>>>>> upstream/master
					pixels[(i * (8 / bits_per_pixel) + j) * xscale + k] = palette[color];
				}
			}
		}
	}

	// template function for external bytes
	template<int bits_per_pixel, int xscale>
<<<<<<< HEAD
	ATTR_FORCE_INLINE void emit_extbytes(const UINT8 *data, int length, pixel_t *RESTRICT pixels, UINT16 color_base, const pixel_t *RESTRICT palette)
=======
	ATTR_FORCE_INLINE void emit_extbytes(const uint8_t *data, int length, pixel_t *RESTRICT pixels, uint16_t color_base, const pixel_t *RESTRICT palette)
>>>>>>> upstream/master
	{
		for (int i = 0; i < length; i++)
		{
			for (int j = 0; j < (8 / bits_per_pixel); j++)
			{
				for (int k = 0; k < xscale; k++)
				{
<<<<<<< HEAD
					UINT16 color = color_base + BIT(data[i], 7-j);
=======
					uint16_t color = color_base + BIT(data[i], 7-j);
>>>>>>> upstream/master
					pixels[(i * (8 / bits_per_pixel) + j) * xscale + k] = palette[color];
				}
			}
		}
	}

	// template function for emitting samples
	template<int xscale>
<<<<<<< HEAD
	UINT32 emit_mc6847_samples(UINT8 mode, const UINT8 *data, int length, pixel_t *RESTRICT pixels, const pixel_t *RESTRICT palette,
		mc6847_get_char_rom_delegate get_char_rom, int x, int y)
	{
		UINT32 result = 0;
=======
	uint32_t emit_mc6847_samples(uint8_t mode, const uint8_t *data, int length, pixel_t *RESTRICT pixels, const pixel_t *RESTRICT palette,
			get_char_rom_delegate const &get_char_rom, int x, int y)
	{
		uint32_t result;
>>>>>>> upstream/master
		if (mode & MODE_AG)
		{
			/* graphics */
			switch(mode & (MODE_GM2|MODE_GM1|MODE_GM0))
			{
				case 0:
					emit_graphics<2, xscale * 4>(data, length, pixels, (mode & MODE_CSS) ? 4 : 0, palette);
					result = length * 8 * xscale * 2;
					break;

				case MODE_GM0:
				case MODE_GM1|MODE_GM0:
				case MODE_GM2|MODE_GM0:
					emit_graphics<1, xscale * 2>(data, length, pixels, (mode & MODE_CSS) ? 10 : 8, palette);
					result = length * 8 * xscale * 2;
					break;

				case MODE_GM1:
				case MODE_GM2:
				case MODE_GM2|MODE_GM1:
					emit_graphics<2, xscale * 2>(data, length, pixels, (mode & MODE_CSS) ? 4 : 0, palette);
					result = length * 8 * xscale;
					break;

				case MODE_GM2|MODE_GM1|MODE_GM0:
					emit_graphics<1, xscale * 1>(data, length, pixels, (mode & MODE_CSS) ? 10 : 8, palette);
					result = length * 8 * xscale;
					break;

				default:
					/* should not get here */
					fatalerror("Should not get here\n");
					break;
			}
		}
<<<<<<< HEAD
		else if (!get_char_rom.isnull() && ((mode & (MODE_AG|MODE_AS|MODE_INTEXT)) == MODE_INTEXT))
=======
		else if (!m_charrom_cb.isnull() && ((mode & (MODE_AG|MODE_AS|MODE_INTEXT)) == MODE_INTEXT))
>>>>>>> upstream/master
		{
			/* external ROM */
			for (int i = 0; i < length; i++)
			{
<<<<<<< HEAD
				UINT8 byte = get_char_rom(data[i], y % 12) ^ (mode & MODE_INV ? 0xFF : 0x00);
=======
				uint8_t byte = m_charrom_cb(data[i], y % 12) ^ (mode & MODE_INV ? 0xFF : 0x00);
>>>>>>> upstream/master
				emit_extbytes<1, xscale>(&byte, 1, &pixels[i * 8], (mode & MODE_CSS) ? 14 : 12, palette);
			}
			result = length * 8 * xscale;
		}
		else
		{
			/* text/semigraphics */
			m_character_map.emit_character<xscale>(mode, data, length, pixels, y, palette);
			result = length * 8 * xscale;
		}
		return result;
	}

private:
	enum scanline_zone
	{
		SCANLINE_ZONE_TOP_BORDER,
		SCANLINE_ZONE_BODY,
		SCANLINE_ZONE_BOTTOM_BORDER,
		SCANLINE_ZONE_RETRACE,
		SCANLINE_ZONE_VBLANK,
		SCANLINE_ZONE_FRAME_END
	};

	// timers
	emu_timer *m_frame_timer;
	emu_timer *m_hsync_on_timer;
	emu_timer *m_hsync_off_timer;
	emu_timer *m_fsync_timer;

	// incidentals
	double m_tpfs;
	int m_field_sync_falling_edge_scanline;
	bool m_wide;
	bool m_video_changed;
<<<<<<< HEAD
	UINT16 m_top_border_scanlines;
	UINT16 m_body_scanlines;
=======
	uint16_t m_top_border_scanlines;
	uint16_t m_body_scanlines;
>>>>>>> upstream/master
	bool m_recording_scanline;
	bool m_supports_partial_body_scanlines;

	// video state
<<<<<<< HEAD
	UINT16 m_physical_scanline;
	UINT16 m_logical_scanline;
	UINT16 m_logical_scanline_zone;
	bool m_horizontal_sync;
	bool m_field_sync;
	UINT32 m_partial_scanline_clocks;
=======
	uint16_t m_physical_scanline;
	uint16_t m_logical_scanline;
	uint16_t m_logical_scanline_zone;
	bool m_horizontal_sync;
	bool m_field_sync;
	uint32_t m_partial_scanline_clocks;
>>>>>>> upstream/master

	// functions
	void change_horizontal_sync(bool line);
	void change_field_sync(bool line);
<<<<<<< HEAD
	void update_field_sync_timer(void);
	void next_scanline(void);
	INT32 get_clocks_since_hsync();

	// debugging
	const char *scanline_zone_string(scanline_zone zone);
=======
	void update_field_sync_timer();
	void next_scanline();
	int32_t get_clocks_since_hsync();

	// debugging
	std::string scanline_zone_string(scanline_zone zone) const;
>>>>>>> upstream/master
};

// actual base class for MC6847 family of devices
class mc6847_base_device : public mc6847_friend_device
{
public:
<<<<<<< HEAD
	template<class _Object> static devcb_base &set_input_callback(device_t &device, _Object object) { return downcast<mc6847_base_device &>(device).m_input_cb.set_callback(object); }

	static void set_get_fixed_mode(device_t &device, UINT8 mode) { downcast<mc6847_base_device &>(device).m_fixed_mode = mode; }
	static void set_black_and_white(device_t &device, bool bw) { downcast<mc6847_base_device &>(device).m_black_and_white = bw; }

	/* updates the screen -- this will call begin_update(),
	   followed by update_row() reapeatedly and after all row
	   updating is complete, end_update() */
	UINT32 screen_update(screen_device &screen, bitmap_rgb32 &bitmap, const rectangle &cliprect);
=======
	template <class Object> static devcb_base &set_input_callback(device_t &device, Object &&cb) { return downcast<mc6847_base_device &>(device).m_input_cb.set_callback(std::forward<Object>(cb)); }

	static void set_get_fixed_mode(device_t &device, uint8_t mode) { downcast<mc6847_base_device &>(device).m_fixed_mode = mode; }
	static void set_black_and_white(device_t &device, bool bw) { downcast<mc6847_base_device &>(device).m_black_and_white = bw; }

	/* updates the screen -- this will call begin_update(),
	   followed by update_row() repeatedly and after all row
	   updating is complete, end_update() */
	uint32_t screen_update(screen_device &screen, bitmap_rgb32 &bitmap, const rectangle &cliprect);
>>>>>>> upstream/master

	// mode changing operations
	DECLARE_WRITE_LINE_MEMBER( ag_w )       { change_mode(MODE_AG, state); }
	DECLARE_WRITE_LINE_MEMBER( gm2_w )      { change_mode(MODE_GM2, state); }
	DECLARE_WRITE_LINE_MEMBER( gm1_w )      { change_mode(MODE_GM1, state); }
	DECLARE_WRITE_LINE_MEMBER( gm0_w )      { change_mode(MODE_GM0, state); }
	DECLARE_WRITE_LINE_MEMBER( as_w )       { change_mode(MODE_AS, state); }
	DECLARE_WRITE_LINE_MEMBER( css_w )      { change_mode(MODE_CSS, state); }
	DECLARE_WRITE_LINE_MEMBER( intext_w )   { change_mode(MODE_INTEXT, state); }
	DECLARE_WRITE_LINE_MEMBER( inv_w )      { change_mode(MODE_INV, state); }

protected:
<<<<<<< HEAD
	mc6847_base_device(const machine_config &mconfig, device_type type, const char *name, const char *tag, device_t *owner, UINT32 clock, const UINT8 *fontdata, double tpfs, const char *shortname, const char *source);

	// device-level overrides
	virtual void device_start();
	virtual void device_reset();
	virtual ioport_constructor device_input_ports() const;

	// other overrides
	virtual void field_sync_changed(bool line);
	virtual void record_body_scanline(UINT16 physical_scanline, UINT16 scanline);
	virtual void record_partial_body_scanline(UINT16 physical_scanline, UINT16 logical_scanline, INT32 start_clock, INT32 end_clock);

	void set_custom_palette(const pixel_t *custom_palette)
	{
		if ( m_palette != m_bw_palette )
=======
	mc6847_base_device(const machine_config &mconfig, device_type type, const char *tag, device_t *owner, uint32_t clock, const uint8_t *fontdata, double tpfs);

	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;
	virtual ioport_constructor device_input_ports() const override;

	// other overrides
	virtual void field_sync_changed(bool line) override;
	virtual void record_body_scanline(uint16_t physical_scanline, uint16_t scanline) override;
	virtual void record_partial_body_scanline(uint16_t physical_scanline, uint16_t logical_scanline, int32_t start_clock, int32_t end_clock) override;

	void set_custom_palette(const pixel_t *custom_palette)
	{
		if (m_palette != m_bw_palette)
>>>>>>> upstream/master
		{
			m_palette = custom_palette ? custom_palette : s_palette;
		}
	}

private:
	struct video_scanline
	{
<<<<<<< HEAD
		UINT8 m_sample_count;
		UINT8 m_mode[32];
		UINT8 m_data[32];
=======
		uint8_t m_sample_count;
		uint8_t m_mode[32];
		uint8_t m_data[32];
>>>>>>> upstream/master
	};

	// palette
	static const int PALETTE_LENGTH = 16;
<<<<<<< HEAD
	static const UINT32 s_palette[PALETTE_LENGTH];
=======
	static const uint32_t s_palette[PALETTE_LENGTH];
>>>>>>> upstream/master

	// callbacks

	/* if specified, this gets called whenever reading a byte (offs_t ~0 specifies DA* entering the tristate mode) */
	devcb_read8 m_input_cb;

	/* if true, this is black and white */
	bool m_black_and_white;

	// incidentals
<<<<<<< HEAD
	UINT8 m_fixed_mode;
	UINT8 m_fixed_mode_mask;
=======
	uint8_t m_fixed_mode;
	uint8_t m_fixed_mode_mask;
>>>>>>> upstream/master
	const pixel_t *m_palette;
	pixel_t m_bw_palette[PALETTE_LENGTH];

	// state
<<<<<<< HEAD
	UINT8 m_mode;
	UINT16 m_video_address;
	bool m_dirty;
	video_scanline m_data[192];

	void change_mode(UINT8 mode, int state)
=======
	uint8_t m_mode;
	uint16_t m_video_address;
	bool m_dirty;
	video_scanline m_data[192];

	void change_mode(uint8_t mode, int state)
>>>>>>> upstream/master
	{
		// sanity check, to ensure that we're not changing fixed modes
		assert((mode & m_fixed_mode_mask) == 0);

		// calculate new mode
<<<<<<< HEAD
		UINT8 new_mode;
=======
		uint8_t new_mode;
>>>>>>> upstream/master
		if (state)
			new_mode = m_mode | mode;
		else
			new_mode = m_mode & ~mode;

		// has the mode changed?
		if (new_mode != m_mode)
		{
			// it has!  check dirty flag
			video_flush();
			if (!m_dirty)
			{
				m_dirty = true;
			}

			// and set the new mode
			m_mode = new_mode;
		}
	}

	// setup functions
	void setup_fixed_mode();

	// runtime functions
<<<<<<< HEAD
	void record_body_scanline(UINT16 physical_scanline, UINT16 scanline, INT32 start_pos, INT32 end_pos);
	pixel_t border_value(UINT8 mode, const pixel_t *palette, bool is_mc6847t1);

	template<int xscale>
	void emit_samples(UINT8 mode, const UINT8 *data, int length, pixel_t *pixels, int x, int y);

	// template function for doing video update collection
	template<int sample_count, int yres>
	void record_scanline_res(int scanline, INT32 start_pos, INT32 end_pos);

	// miscellaneous
	UINT8 input(UINT16 address);
	INT32 scanline_position_from_clock(INT32 clocks_since_hsync);
=======
	void record_body_scanline(uint16_t physical_scanline, uint16_t scanline, int32_t start_pos, int32_t end_pos);
	pixel_t border_value(uint8_t mode, const pixel_t *palette, bool is_mc6847t1);

	// template function for doing video update collection
	template<int sample_count, int yres>
	void record_scanline_res(int scanline, int32_t start_pos, int32_t end_pos);

	// miscellaneous
	uint8_t input(uint16_t address);
	int32_t scanline_position_from_clock(int32_t clocks_since_hsync);
>>>>>>> upstream/master
};


//**************************************************************************
//  VARIATIONS
//**************************************************************************

class mc6847_ntsc_device : public mc6847_base_device
{
public:
<<<<<<< HEAD
	mc6847_ntsc_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
=======
	mc6847_ntsc_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
>>>>>>> upstream/master
};

class mc6847_pal_device : public mc6847_base_device
{
public:
<<<<<<< HEAD
	mc6847_pal_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
=======
	mc6847_pal_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
>>>>>>> upstream/master
};

class mc6847y_ntsc_device : public mc6847_base_device
{
public:
<<<<<<< HEAD
	mc6847y_ntsc_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
=======
	mc6847y_ntsc_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
>>>>>>> upstream/master
};

class mc6847y_pal_device : public mc6847_base_device
{
public:
<<<<<<< HEAD
	mc6847y_pal_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
=======
	mc6847y_pal_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
>>>>>>> upstream/master
};

class mc6847t1_ntsc_device : public mc6847_base_device
{
public:
<<<<<<< HEAD
	mc6847t1_ntsc_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
=======
	mc6847t1_ntsc_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
>>>>>>> upstream/master
};

class mc6847t1_pal_device : public mc6847_base_device
{
public:
<<<<<<< HEAD
	mc6847t1_pal_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
=======
	mc6847t1_pal_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
>>>>>>> upstream/master
};

class s68047_device : public mc6847_base_device
{
public:
<<<<<<< HEAD
	s68047_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
=======
	s68047_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
>>>>>>> upstream/master

	void hack_black_becomes_blue(bool flag);

private:
<<<<<<< HEAD
	static const UINT32 s_s68047_hack_palette[16];
=======
	static const uint32_t s_s68047_hack_palette[16];
>>>>>>> upstream/master
};

class m5c6847p1_device : public mc6847_base_device
{
public:
<<<<<<< HEAD
	m5c6847p1_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
};


extern const device_type MC6847_NTSC;
extern const device_type MC6847_PAL;
extern const device_type MC6847Y_NTSC;
extern const device_type MC6847Y_PAL;
extern const device_type MC6847T1_NTSC;
extern const device_type MC6847T1_PAL;
extern const device_type S68047;
extern const device_type M5C6847P1;

#endif /* __MC6847__ */
=======
	m5c6847p1_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
};


DECLARE_DEVICE_TYPE(MC6847_NTSC,   mc6847_ntsc_device)
DECLARE_DEVICE_TYPE(MC6847_PAL,    mc6847_pal_device)
DECLARE_DEVICE_TYPE(MC6847Y_NTSC,  mc6847t1_ntsc_device)
DECLARE_DEVICE_TYPE(MC6847Y_PAL,   mc6847y_pal_device)
DECLARE_DEVICE_TYPE(MC6847T1_NTSC, mc6847t1_ntsc_device)
DECLARE_DEVICE_TYPE(MC6847T1_PAL,  mc6847t1_pal_device)
DECLARE_DEVICE_TYPE(S68047,        s68047_device)
DECLARE_DEVICE_TYPE(M5C6847P1,     m5c6847p1_device)

#endif // MAME_VIDEO_MC6847_H
>>>>>>> upstream/master
