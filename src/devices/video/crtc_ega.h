// license:BSD-3-Clause
// copyright-holders:Wilbert Pol
/**********************************************************************

    IBM EGA CRT Controller emulation

**********************************************************************/

<<<<<<< HEAD
#ifndef __CRTC_EGA__
#define __CRTC_EGA__

#include "emu.h"

/* callback definitions */
typedef device_delegate<void (bitmap_ind16 &bitmap, const rectangle &cliprect)> crtc_ega_begin_update_delegate;

typedef device_delegate<void (bitmap_ind16 &bitmap, const rectangle &cliprect, UINT16 ma, UINT8 ra,
										UINT16 y, UINT8 x_count, INT8 cursor_x)> crtc_ega_row_update_delegate;

typedef device_delegate<void (bitmap_ind16 &bitmap, const rectangle &cliprect)> crtc_ega_end_update_delegate;
=======
#ifndef MAME_VIDEO_CRTC_EGA_H
#define MAME_VIDEO_CRTC_EGA_H
>>>>>>> upstream/master


#define CRTC_EGA_BEGIN_UPDATE(_name) void _name(bitmap_ind16 &bitmap, const rectangle &cliprect)
#define CRTC_EGA_ROW_UPDATE(_name)   void _name(bitmap_ind16 &bitmap,    \
<<<<<<< HEAD
												const rectangle &cliprect, UINT16 ma, UINT8 ra,                 \
												UINT16 y, UINT8 x_count, INT8 cursor_x)
=======
												const rectangle &cliprect, uint16_t ma, uint8_t ra,                 \
												uint16_t y, uint8_t x_count, int8_t cursor_x)
>>>>>>> upstream/master
#define CRTC_EGA_END_UPDATE(_name)   void _name(bitmap_ind16 &bitmap, const rectangle &cliprect)



#define MCFG_CRTC_EGA_SET_SCREEN MCFG_VIDEO_SET_SCREEN

#define MCFG_CRTC_EGA_BEGIN_UPDATE_CB(_class, _method) \
<<<<<<< HEAD
	crtc_ega_device::set_begin_update_callback(*device, crtc_ega_begin_update_delegate(&_class::_method, #_class "::" #_method, downcast<_class *>(owner)));

#define MCFG_CRTC_EGA_ROW_UPDATE_CB(_class, _method) \
	crtc_ega_device::set_row_update_callback(*device, crtc_ega_row_update_delegate(&_class::_method, #_class "::" #_method, downcast<_class *>(owner)));

#define MCFG_CRTC_EGA_END_UPDATE_CB(_class, _method) \
	crtc_ega_device::set_end_update_callback(*device, crtc_ega_end_update_delegate(&_class::_method, #_class "::" #_method, downcast<_class *>(owner)));
=======
	crtc_ega_device::set_begin_update_callback(*device, crtc_ega_device::begin_update_delegate(&_class::_method, #_class "::" #_method, downcast<_class *>(owner)));

#define MCFG_CRTC_EGA_ROW_UPDATE_CB(_class, _method) \
	crtc_ega_device::set_row_update_callback(*device, crtc_ega_device::row_update_delegate(&_class::_method, #_class "::" #_method, downcast<_class *>(owner)));

#define MCFG_CRTC_EGA_END_UPDATE_CB(_class, _method) \
	crtc_ega_device::set_end_update_callback(*device, crtc_ega_device::end_update_delegate(&_class::_method, #_class "::" #_method, downcast<_class *>(owner)));
>>>>>>> upstream/master

#define MCFG_CRTC_EGA_HPIXELS_PER_COLUMN(_pix) \
	crtc_ega_device::set_hpixels_per_column(*device, _pix);

#define MCFG_CRTC_EGA_RES_OUT_DE_CB(_devcb) \
	devcb = &crtc_ega_device::set_res_out_de_callback(*device, DEVCB_##_devcb);

#define MCFG_CRTC_EGA_RES_OUT_HSYNC_CB(_devcb) \
	devcb = &crtc_ega_device::set_res_out_hsync_callback(*device, DEVCB_##_devcb);

#define MCFG_CRTC_EGA_RES_OUT_VSYNC_CB(_devcb) \
	devcb = &crtc_ega_device::set_res_out_vsync_callback(*device, DEVCB_##_devcb);

#define MCFG_CRTC_EGA_RES_OUT_VBLANK_CB(_devcb) \
	devcb = &crtc_ega_device::set_res_out_vblank_callback(*device, DEVCB_##_devcb);


class crtc_ega_device : public device_t,
						public device_video_interface
{
public:
<<<<<<< HEAD
	crtc_ega_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	template<class _Object> static devcb_base &set_res_out_de_callback(device_t &device, _Object object)
						{ return downcast<crtc_ega_device &>(device).m_res_out_de_cb.set_callback(object); }
	template<class _Object> static devcb_base &set_res_out_hsync_callback(device_t &device, _Object object)
						{ return downcast<crtc_ega_device &>(device).m_res_out_hsync_cb.set_callback(object); }
	template<class _Object> static devcb_base &set_res_out_vsync_callback(device_t &device, _Object object)
						{ return downcast<crtc_ega_device &>(device).m_res_out_vsync_cb.set_callback(object); }
	template<class _Object> static devcb_base &set_res_out_vblank_callback(device_t &device, _Object object)
						{ return downcast<crtc_ega_device &>(device).m_res_out_vblank_cb.set_callback(object); }

	static void set_begin_update_callback(device_t &device, crtc_ega_begin_update_delegate callback) { downcast<crtc_ega_device &>(device).m_begin_update_cb = callback; }
	static void set_row_update_callback(device_t &device, crtc_ega_row_update_delegate callback) { downcast<crtc_ega_device &>(device).m_row_update_cb = callback; }
	static void set_end_update_callback(device_t &device, crtc_ega_end_update_delegate callback) { downcast<crtc_ega_device &>(device).m_end_update_cb = callback; }
=======
	/* callback definitions */
	typedef device_delegate<void (bitmap_ind16 &bitmap, const rectangle &cliprect)> begin_update_delegate;
	typedef device_delegate<void (bitmap_ind16 &bitmap, const rectangle &cliprect, uint16_t ma, uint8_t ra, uint16_t y, uint8_t x_count, int8_t cursor_x)> row_update_delegate;
	typedef device_delegate<void (bitmap_ind16 &bitmap, const rectangle &cliprect)> end_update_delegate;


	crtc_ega_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	template <class Object> static devcb_base &set_res_out_de_callback(device_t &device, Object &&cb)
	{ return downcast<crtc_ega_device &>(device).m_res_out_de_cb.set_callback(std::forward<Object>(cb)); }
	template <class Object> static devcb_base &set_res_out_hsync_callback(device_t &device, Object &&cb)
	{ return downcast<crtc_ega_device &>(device).m_res_out_hsync_cb.set_callback(std::forward<Object>(cb)); }
	template <class Object> static devcb_base &set_res_out_vsync_callback(device_t &device, Object &&cb)
	{ return downcast<crtc_ega_device &>(device).m_res_out_vsync_cb.set_callback(std::forward<Object>(cb)); }
	template <class Object> static devcb_base &set_res_out_vblank_callback(device_t &device, Object &&cb)
	{ return downcast<crtc_ega_device &>(device).m_res_out_vblank_cb.set_callback(std::forward<Object>(cb)); }

	static void set_begin_update_callback(device_t &device, begin_update_delegate &&cb) { downcast<crtc_ega_device &>(device).m_begin_update_cb = std::move(cb); }
	static void set_row_update_callback(device_t &device, row_update_delegate &&cb) { downcast<crtc_ega_device &>(device).m_row_update_cb = std::move(cb); }
	static void set_end_update_callback(device_t &device, end_update_delegate &&cb) { downcast<crtc_ega_device &>(device).m_end_update_cb = std::move(cb); }
>>>>>>> upstream/master
	static void set_hpixels_per_column(device_t &device, int hpixels_per_column) { downcast<crtc_ega_device &>(device).m_hpixels_per_column = hpixels_per_column; }

	/* select one of the registers for reading or writing */
	DECLARE_WRITE8_MEMBER( address_w );

	/* read from the currently selected register */
	DECLARE_READ8_MEMBER( register_r );

	/* write to the currently selected register */
	DECLARE_WRITE8_MEMBER( register_w );

	/* return the current value on the MA0-MA15 pins */
<<<<<<< HEAD
	UINT16 get_ma();

	/* return the current value on the RA0-RA4 pins */
	UINT8 get_ra();
=======
	uint16_t get_ma();

	/* return the current value on the RA0-RA4 pins */
	uint8_t get_ra();
>>>>>>> upstream/master

	/* simulates the LO->HI clocking of the light pen pin */
	void assert_light_pen_input();

	/* set the clock of the chip */
	void set_clock(int clock);

	/* set number of pixels per video memory address */
	void set_hpixels_per_column(int hpixels_per_column);

	/* updates the screen -- this will call begin_update(), */
<<<<<<< HEAD
	/* followed by update_row() reapeatedly and after all row */
	/* updating is complete, end_update() */
	UINT32 screen_update(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);

protected:
	// device-level overrides
	virtual void device_start();
	virtual void device_reset();
	virtual void device_post_load();
	virtual void device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr);
=======
	/* followed by update_row() repeatedly and after all row */
	/* updating is complete, end_update() */
	uint32_t screen_update(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);

protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;
	virtual void device_post_load() override;
	virtual void device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr) override;
>>>>>>> upstream/master

private:
	devcb_write_line   m_res_out_de_cb;
	devcb_write_line   m_res_out_hsync_cb;
	devcb_write_line   m_res_out_vsync_cb;
	devcb_write_line   m_res_out_vblank_cb;

	/* if specified, this gets called before any pixel update,
	 optionally return a pointer that will be passed to the
	 update and tear down callbacks */
<<<<<<< HEAD
	crtc_ega_begin_update_delegate      m_begin_update_cb;
=======
	begin_update_delegate      m_begin_update_cb;
>>>>>>> upstream/master

	/* this gets called for every row, the driver must output
	 x_count * hpixels_per_column pixels.
	 cursor_x indicates the character position where the cursor is, or -1
	 if there is no cursor on this row */
<<<<<<< HEAD
	crtc_ega_row_update_delegate        m_row_update_cb;

	/* if specified, this gets called after all row updating is complete */
	crtc_ega_end_update_delegate        m_end_update_cb;

	/* ega/vga register file */
	UINT8   m_horiz_char_total; /* 0x00 */
	UINT8   m_horiz_disp;           /* 0x01 */
	UINT8   m_horiz_blank_start;    /* 0x02 */
	UINT8   m_horiz_blank_end;  /* 0x03/0x05 */
	UINT8   m_ena_vert_access;  /* 0x03 */
	UINT8   m_de_skew;          /* 0x03 */
	UINT8   m_horiz_retr_start; /* 0x04 */
	UINT8   m_horiz_retr_end;       /* 0x05 */
	UINT8   m_horiz_retr_skew;  /* 0x05 */
	UINT16  m_vert_total;           /* 0x06/0x07 */
	UINT8   m_preset_row_scan;  /* 0x08 */
	UINT8   m_byte_panning;     /* 0x08 */
	UINT8   m_max_ras_addr;     /* 0x09 */
	UINT8   m_scan_doubling;        /* 0x09 */
	UINT8   m_cursor_start_ras; /* 0x0a */
	UINT8   m_cursor_disable;       /* 0x0a */
	UINT8   m_cursor_end_ras;       /* 0x0b */
	UINT8   m_cursor_skew;      /* 0x0b */
	UINT16  m_disp_start_addr;  /* 0x0c/0x0d */
	UINT16  m_cursor_addr;      /* 0x0e/0x0f */
	UINT16  m_light_pen_addr;       /* 0x10/0x11 */
	UINT16  m_vert_retr_start;  /* 0x10/0x07 */
	UINT8   m_vert_retr_end;        /* 0x11 */
	UINT8   m_protect;          /* 0x11 */
	UINT8   m_bandwidth;            /* 0x11 */
	UINT16  m_vert_disp_end;        /* 0x12/0x07 */
	UINT8   m_offset;               /* 0x13 */
	UINT8   m_underline_loc;        /* 0x14 */
	UINT16  m_vert_blank_start; /* 0x15/0x07/0x09 */
	UINT8   m_vert_blank_end;       /* 0x16 */
	UINT8   m_mode_control;     /* 0x17 */
	UINT16  m_line_compare;     /* 0x18/0x07/0x09 */

	/* other internal state */
	UINT8   m_register_address_latch;
	bool    m_cursor_state; /* 0 = off, 1 = on */
	UINT8   m_cursor_blink_count;
=======
	row_update_delegate        m_row_update_cb;

	/* if specified, this gets called after all row updating is complete */
	end_update_delegate        m_end_update_cb;

	/* ega/vga register file */
	uint8_t   m_horiz_char_total; /* 0x00 */
	uint8_t   m_horiz_disp;           /* 0x01 */
	uint8_t   m_horiz_blank_start;    /* 0x02 */
	uint8_t   m_horiz_blank_end;  /* 0x03/0x05 */
	uint8_t   m_ena_vert_access;  /* 0x03 */
	uint8_t   m_de_skew;          /* 0x03 */
	uint8_t   m_horiz_retr_start; /* 0x04 */
	uint8_t   m_horiz_retr_end;       /* 0x05 */
	uint8_t   m_horiz_retr_skew;  /* 0x05 */
	uint16_t  m_vert_total;           /* 0x06/0x07 */
	uint8_t   m_preset_row_scan;  /* 0x08 */
	uint8_t   m_byte_panning;     /* 0x08 */
	uint8_t   m_max_ras_addr;     /* 0x09 */
	uint8_t   m_scan_doubling;        /* 0x09 */
	uint8_t   m_cursor_start_ras; /* 0x0a */
	uint8_t   m_cursor_disable;       /* 0x0a */
	uint8_t   m_cursor_end_ras;       /* 0x0b */
	uint8_t   m_cursor_skew;      /* 0x0b */
	uint16_t  m_disp_start_addr;  /* 0x0c/0x0d */
	uint16_t  m_cursor_addr;      /* 0x0e/0x0f */
	uint16_t  m_light_pen_addr;       /* 0x10/0x11 */
	uint16_t  m_vert_retr_start;  /* 0x10/0x07 */
	uint8_t   m_vert_retr_end;        /* 0x11 */
	uint8_t   m_protect;          /* 0x11 */
	uint8_t   m_bandwidth;            /* 0x11 */
	uint16_t  m_vert_disp_end;        /* 0x12/0x07 */
	uint8_t   m_offset;               /* 0x13 */
	uint8_t   m_underline_loc;        /* 0x14 */
	uint16_t  m_vert_blank_start; /* 0x15/0x07/0x09 */
	uint8_t   m_vert_blank_end;       /* 0x16 */
	uint8_t   m_mode_control;     /* 0x17 */
	uint16_t  m_line_compare;     /* 0x18/0x07/0x09 */

	/* other internal state */
	uint8_t   m_register_address_latch;
	bool    m_cursor_state; /* 0 = off, 1 = on */
	uint8_t   m_cursor_blink_count;
>>>>>>> upstream/master
	int     m_hpixels_per_column;       /* number of pixels per video memory address */

	/* output signals */
	int     m_cur;
	int     m_hsync;
	int     m_vsync;
	int     m_vblank;
	int     m_de;

	/* internal counters */
<<<<<<< HEAD
	UINT8   m_character_counter;
	UINT8   m_hsync_width_counter;
	UINT16  m_line_counter;
	UINT8   m_raster_counter;
	UINT8   m_vsync_width_counter;
	bool    m_line_enable_ff;       /* Internal flip flop which is set when the line_counter is reset and reset when vert_disp is reached */
	UINT8   m_vsync_ff;
	UINT8   m_adjust_active;
	UINT16  m_line_address;
	INT16   m_cursor_x;

	/* timers */
	static const device_timer_id TIMER_LINE = 0;
	static const device_timer_id TIMER_DE_OFF = 1;
	static const device_timer_id TIMER_CUR_ON = 2;
	static const device_timer_id TIMER_CUR_OFF = 3;
	static const device_timer_id TIMER_HSYNC_ON = 4;
	static const device_timer_id TIMER_HSYNC_OFF = 5;
	static const device_timer_id TIMER_LIGHT_PEN_LATCH = 6;
=======
	uint8_t   m_character_counter;
	uint8_t   m_hsync_width_counter;
	uint16_t  m_line_counter;
	uint8_t   m_raster_counter;
	uint8_t   m_vsync_width_counter;
	bool    m_line_enable_ff;       /* Internal flip flop which is set when the line_counter is reset and reset when vert_disp is reached */
	uint8_t   m_vsync_ff;
	uint8_t   m_adjust_active;
	uint16_t  m_line_address;
	int16_t   m_cursor_x;

	/* timers */
	static constexpr device_timer_id TIMER_LINE = 0;
	static constexpr device_timer_id TIMER_DE_OFF = 1;
	static constexpr device_timer_id TIMER_CUR_ON = 2;
	static constexpr device_timer_id TIMER_CUR_OFF = 3;
	static constexpr device_timer_id TIMER_HSYNC_ON = 4;
	static constexpr device_timer_id TIMER_HSYNC_OFF = 5;
	static constexpr device_timer_id TIMER_LIGHT_PEN_LATCH = 6;
>>>>>>> upstream/master

	emu_timer *m_line_timer;
	emu_timer *m_de_off_timer;
	emu_timer *m_cur_on_timer;
	emu_timer *m_cur_off_timer;
	emu_timer *m_hsync_on_timer;
	emu_timer *m_hsync_off_timer;
	emu_timer *m_light_pen_latch_timer;

	/* computed values - do NOT state save these! */
<<<<<<< HEAD
	UINT16  m_horiz_pix_total;
	UINT16  m_vert_pix_total;
	UINT16  m_max_visible_x;
	UINT16  m_max_visible_y;
	UINT16  m_hsync_on_pos;
	UINT16  m_hsync_off_pos;
	UINT16  m_vsync_on_pos;
	UINT16  m_vsync_off_pos;
	UINT16  m_current_disp_addr;    /* the display address currently drawn */
	UINT8   m_light_pen_latched;
=======
	uint16_t  m_horiz_pix_total;
	uint16_t  m_vert_pix_total;
	uint16_t  m_max_visible_x;
	uint16_t  m_max_visible_y;
	uint16_t  m_hsync_on_pos;
	uint16_t  m_hsync_off_pos;
	uint16_t  m_vsync_on_pos;
	uint16_t  m_vsync_off_pos;
	uint16_t  m_current_disp_addr;    /* the display address currently drawn */
	uint8_t   m_light_pen_latched;
>>>>>>> upstream/master
	bool    m_has_valid_parameters;

	void recompute_parameters(bool postload);
	void update_counters();
	void set_de(int state);
	void set_hsync(int state);
	void set_vsync(int state);
	void set_vblank(int state);
	void set_cur(int state);
	void handle_line_timer();
	void update_cursor_state();
};

<<<<<<< HEAD
extern const device_type CRTC_EGA;

#endif
=======
DECLARE_DEVICE_TYPE(CRTC_EGA, crtc_ega_device)

#endif // MAME_VIDEO_CRTC_EGA_H
>>>>>>> upstream/master
