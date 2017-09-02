// license:BSD-3-Clause
// copyright-holders:Aaron Giles, Nathan Woods
/***************************************************************************

    v9938 / v9958 emulation

***************************************************************************/

<<<<<<< HEAD
#pragma once

#ifndef __V9938_H__
#define __V9938_H__

=======
#ifndef MAME_VIDEO_V9938_H
#define MAME_VIDEO_V9938_H

#pragma once

#include "screen.h"
>>>>>>> upstream/master


//**************************************************************************
//  DEVICE CONFIGURATION MACROS
//**************************************************************************

#define MCFG_V9938_ADD(_tag, _screen, _vramsize, _clock) \
	MCFG_DEVICE_ADD(_tag, V9938, _clock) \
	MCFG_VIDEO_SET_SCREEN(_screen) \
	v9938_device::static_set_vram_size(*device, _vramsize);
#define MCFG_V9958_ADD(_tag, _screen, _vramsize, _clock) \
	MCFG_DEVICE_ADD(_tag, V9958, _clock) \
	MCFG_VIDEO_SET_SCREEN(_screen) \
	v9938_device::static_set_vram_size(*device, _vramsize);

#define MCFG_V99X8_SCREEN_ADD_NTSC(_screen_tag, _v9938_tag, _clock) \
	MCFG_SCREEN_ADD(_screen_tag, RASTER) \
	MCFG_SCREEN_RAW_PARAMS(_clock, \
		v99x8_device::HTOTAL, \
		0, \
		v99x8_device::HVISIBLE - 1, \
		v99x8_device::VTOTAL_NTSC * 2, \
		v99x8_device::VERTICAL_ADJUST * 2, \
		v99x8_device::VVISIBLE_NTSC * 2 - 1 - v99x8_device::VERTICAL_ADJUST * 2) \
	MCFG_SCREEN_UPDATE_DEVICE(_v9938_tag, v9938_device, screen_update) \
<<<<<<< HEAD
	MCFG_SCREEN_PALETTE(_v9938_tag":palette")
=======
	MCFG_SCREEN_PALETTE(_v9938_tag)
>>>>>>> upstream/master

#define MCFG_V99X8_SCREEN_ADD_PAL(_screen_tag, _v9938_tag, _clock) \
	MCFG_SCREEN_ADD(_screen_tag, RASTER) \
	MCFG_SCREEN_RAW_PARAMS(_clock, \
		v99x8_device::HTOTAL, \
		0, \
		v99x8_device::HVISIBLE - 1, \
		v99x8_device::VTOTAL_PAL * 2, \
		v99x8_device::VERTICAL_ADJUST * 2, \
		v99x8_device::VVISIBLE_PAL * 2 - 1 - v99x8_device::VERTICAL_ADJUST * 2) \
	MCFG_SCREEN_UPDATE_DEVICE(_v9938_tag, v9938_device, screen_update) \
<<<<<<< HEAD
	MCFG_SCREEN_PALETTE(_v9938_tag":palette")

#define MCFG_V99X8_INTERRUPT_CALLBACK(_irq) \
	downcast<v99x8_device *>(device)->set_interrupt_callback(DEVCB_##_irq);
=======
	MCFG_SCREEN_PALETTE(_v9938_tag)

#define MCFG_V99X8_INTERRUPT_CALLBACK(_irq) \
	devcb = &downcast<v99x8_device *>(device)->set_interrupt_callback(DEVCB_##_irq);
>>>>>>> upstream/master


//**************************************************************************
//  GLOBAL VARIABLES
//**************************************************************************

// device type definition
<<<<<<< HEAD
extern const device_type V9938;
extern const device_type V9958;
=======
DECLARE_DEVICE_TYPE(V9938, v9938_device)
DECLARE_DEVICE_TYPE(V9958, v9958_device)
>>>>>>> upstream/master



//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

// ======================> v99x8_device

class v99x8_device :    public device_t,
						public device_memory_interface,
<<<<<<< HEAD
						public device_video_interface
{
protected:
	// construction/destruction
	v99x8_device(const machine_config &mconfig, device_type type, const char *name, const char *shortname, const char *tag, device_t *owner, UINT32 clock);

public:
	template<class _irq> void set_interrupt_callback(_irq irq) {
		m_int_callback.set_callback(irq);
	}
=======
						public device_palette_interface,
						public device_video_interface
{
public:
	template <class Object> devcb_base &set_interrupt_callback(Object &&irq) { return m_int_callback.set_callback(std::forward<Object>(irq)); }
>>>>>>> upstream/master
	int get_transpen();
	bitmap_ind16 &get_bitmap() { return m_bitmap; }
	void update_mouse_state(int mx_delta, int my_delta, int button_state);

<<<<<<< HEAD
	UINT32 screen_update(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
=======
	uint32_t screen_update(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
>>>>>>> upstream/master

	DECLARE_READ8_MEMBER( read );
	DECLARE_WRITE8_MEMBER( write );

<<<<<<< HEAD
	UINT8 vram_r();
	UINT8 status_r();
	void palette_w(UINT8 data);
	void vram_w(UINT8 data);
	void command_w(UINT8 data);
	void register_w(UINT8 data);

	static void static_set_vram_size(device_t &device, UINT32 vram_size);
=======
	uint8_t vram_r();
	uint8_t status_r();
	void palette_w(uint8_t data);
	void vram_w(uint8_t data);
	void command_w(uint8_t data);
	void register_w(uint8_t data);

	static void static_set_vram_size(device_t &device, uint32_t vram_size);
>>>>>>> upstream/master

	/* RESET pin */
	void reset_line(int state) { if (state==ASSERT_LINE) device_reset(); }

<<<<<<< HEAD
	static const int HTOTAL = 684;
	static const int HVISIBLE = 544;
	static const int VTOTAL_NTSC = 262;
	static const int VTOTAL_PAL = 313;
	static const int VVISIBLE_NTSC = 26 + 192 + 25;
	static const int VVISIBLE_PAL = 53 + 192 + 49;
=======
	static constexpr int HTOTAL = 684;
	static constexpr int HVISIBLE = 544;
	static constexpr int VTOTAL_NTSC = 262;
	static constexpr int VTOTAL_PAL = 313;
	static constexpr int VVISIBLE_NTSC = 26 + 192 + 25;
	static constexpr int VVISIBLE_PAL = 53 + 192 + 49;
>>>>>>> upstream/master
	// Looking at some youtube videos of real units on real monitors
	// there appear to be small vertical timing differences. Some (LCD)
	// monitors show the full borders, other CRT monitors seem to
	// display ~5 lines less at the top and bottom of the screen.
<<<<<<< HEAD
	static const int VERTICAL_ADJUST = 5;
	static const int TOP_ERASE = 13;
	static const int VERTICAL_SYNC = 3;

protected:
	static const device_timer_id TIMER_LINE = 0;
	const address_space_config      m_space_config;
	address_space*                  m_vram_space;

	int m_model;

	// device overrides
	virtual void device_start();
	virtual void device_reset();
	virtual void device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr);

	// device_memory_interface overrides
	virtual const address_space_config *memory_space_config(address_spacenum spacenum = AS_DATA) const { return (spacenum == AS_DATA) ? &m_space_config : NULL; }
=======
	static constexpr int VERTICAL_ADJUST = 5;
	static constexpr int TOP_ERASE = 13;
	static constexpr int VERTICAL_SYNC = 3;

protected:
	// construction/destruction
	v99x8_device(const machine_config &mconfig, device_type type, const char *tag, device_t *owner, uint32_t clock, int model);

	static constexpr device_timer_id TIMER_LINE = 0;
	const address_space_config      m_space_config;
	address_space*                  m_vram_space;

	const int m_model;

	// device overrides
	virtual void device_start() override;
	virtual void device_reset() override;
	virtual void device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr) override;

	// device_memory_interface overrides
	virtual space_config_vector memory_space_config() const override;

	virtual void palette_init() = 0;
>>>>>>> upstream/master

	void configure_pal_ntsc();
	void set_screen_parameters();

private:
	// internal helpers
<<<<<<< HEAD
	inline int position_offset(UINT8 value) { value &= 0x0f; return (value < 8) ? -value : 16 - value; }
=======
	inline int position_offset(uint8_t value) { value &= 0x0f; return (value < 8) ? -value : 16 - value; }
>>>>>>> upstream/master
	void reset_palette();
	void vram_write(int offset, int data);
	int vram_read(int offset);
	void check_int();
	void register_write(int reg, int data);

<<<<<<< HEAD
	void default_border(const pen_t *pens, UINT16 *ln);
	void graphic7_border(const pen_t *pens, UINT16 *ln);
	void graphic5_border(const pen_t *pens, UINT16 *ln);
	void mode_text1(const pen_t *pens, UINT16 *ln, int line);
	void mode_text2(const pen_t *pens, UINT16 *ln, int line);
	void mode_multi(const pen_t *pens, UINT16 *ln, int line);
	void mode_graphic1(const pen_t *pens, UINT16 *ln, int line);
	void mode_graphic23(const pen_t *pens, UINT16 *ln, int line);
	void mode_graphic4(const pen_t *pens, UINT16 *ln, int line);
	void mode_graphic5(const pen_t *pens, UINT16 *ln, int line);
	void mode_graphic6(const pen_t *pens, UINT16 *ln, int line);
	void mode_graphic7(const pen_t *pens, UINT16 *ln, int line);
//  template<typename _PixelType, int _Width> void mode_yae(const pen_t *pens, _PixelType *ln, int line);
//  template<typename _PixelType, int _Width> void mode_yjk(const pen_t *pens, _PixelType *ln, int line);
	void mode_unknown(const pen_t *pens, UINT16 *ln, int line);
	void default_draw_sprite(const pen_t *pens, UINT16 *ln, UINT8 *col);
	void graphic5_draw_sprite(const pen_t *pens, UINT16 *ln, UINT8 *col);
	void graphic7_draw_sprite(const pen_t *pens, UINT16 *ln, UINT8 *col);

	void sprite_mode1(int line, UINT8 *col);
	void sprite_mode2(int line, UINT8 *col);
=======
	void default_border(uint16_t *ln);
	void graphic7_border(uint16_t *ln);
	void graphic5_border(uint16_t *ln);
	void mode_text1(uint16_t *ln, int line);
	void mode_text2(uint16_t *ln, int line);
	void mode_multi(uint16_t *ln, int line);
	void mode_graphic1(uint16_t *ln, int line);
	void mode_graphic23(uint16_t *ln, int line);
	void mode_graphic4(uint16_t *ln, int line);
	void mode_graphic5(uint16_t *ln, int line);
	void mode_graphic6(uint16_t *ln, int line);
	void mode_graphic7(uint16_t *ln, int line);
//  template<typename _PixelType, int _Width> void mode_yae(_PixelType *ln, int line);
//  template<typename _PixelType, int _Width> void mode_yjk(_PixelType *ln, int line);
	void mode_unknown(uint16_t *ln, int line);
	void default_draw_sprite(uint16_t *ln, uint8_t *col);
	void graphic5_draw_sprite(uint16_t *ln, uint8_t *col);
	void graphic7_draw_sprite(uint16_t *ln, uint8_t *col);

	void sprite_mode1(int line, uint8_t *col);
	void sprite_mode2(int line, uint8_t *col);
>>>>>>> upstream/master
	void set_mode();
	void refresh_16(int line);
	void refresh_line(int line);

	void interrupt_start_vblank();

<<<<<<< HEAD
	int VDPVRMP(UINT8 M, int MX, int X, int Y);

	UINT8 VDPpoint5(int MXS, int SX, int SY);
	UINT8 VDPpoint6(int MXS, int SX, int SY);
	UINT8 VDPpoint7(int MXS, int SX, int SY);
	UINT8 VDPpoint8(int MXS, int SX, int SY);

	UINT8 VDPpoint(UINT8 SM, int MXS, int SX, int SY);

	void VDPpsetlowlevel(int addr, UINT8 CL, UINT8 M, UINT8 OP);

	void VDPpset5(int MXD, int DX, int DY, UINT8 CL, UINT8 OP);
	void VDPpset6(int MXD, int DX, int DY, UINT8 CL, UINT8 OP);
	void VDPpset7(int MXD, int DX, int DY, UINT8 CL, UINT8 OP);
	void VDPpset8(int MXD, int DX, int DY, UINT8 CL, UINT8 OP);

	void VDPpset(UINT8 SM, int MXD, int DX, int DY, UINT8 CL, UINT8 OP);
=======
	int VDPVRMP(uint8_t M, int MX, int X, int Y);

	uint8_t VDPpoint5(int MXS, int SX, int SY);
	uint8_t VDPpoint6(int MXS, int SX, int SY);
	uint8_t VDPpoint7(int MXS, int SX, int SY);
	uint8_t VDPpoint8(int MXS, int SX, int SY);

	uint8_t VDPpoint(uint8_t SM, int MXS, int SX, int SY);

	void VDPpsetlowlevel(int addr, uint8_t CL, uint8_t M, uint8_t OP);

	void VDPpset5(int MXD, int DX, int DY, uint8_t CL, uint8_t OP);
	void VDPpset6(int MXD, int DX, int DY, uint8_t CL, uint8_t OP);
	void VDPpset7(int MXD, int DX, int DY, uint8_t CL, uint8_t OP);
	void VDPpset8(int MXD, int DX, int DY, uint8_t CL, uint8_t OP);

	void VDPpset(uint8_t SM, int MXD, int DX, int DY, uint8_t CL, uint8_t OP);
>>>>>>> upstream/master

	int get_vdp_timing_value(const int *);

	void srch_engine();
	void line_engine();
	void lmmv_engine();
	void lmmm_engine();
	void lmcm_engine();
	void lmmc_engine();
	void hmmv_engine();
	void hmmm_engine();
	void ymmm_engine();
	void hmmc_engine();

	inline bool v9938_second_field();

<<<<<<< HEAD
	void cpu_to_vdp(UINT8 V);
	UINT8 vdp_to_cpu();
	void report_vdp_command(UINT8 Op);
	UINT8 command_unit_w(UINT8 Op);
=======
	void cpu_to_vdp(uint8_t V);
	uint8_t vdp_to_cpu();
	void report_vdp_command(uint8_t Op);
	uint8_t command_unit_w(uint8_t Op);
>>>>>>> upstream/master
	void update_command();

	// general
	int m_offset_x, m_offset_y, m_visible_y, m_mode;
	// palette
	int m_pal_write_first, m_cmd_write_first;
<<<<<<< HEAD
	UINT8 m_pal_write, m_cmd_write;
	UINT8 m_pal_reg[32], m_stat_reg[10], m_cont_reg[48], m_read_ahead;
	UINT8 m_v9958_sp_mode;

	// memory
	UINT16 m_address_latch;
	int m_vram_size;

	// interrupt
	UINT8 m_int_state;
=======
	uint8_t m_pal_write, m_cmd_write;
	uint8_t m_pal_reg[32], m_stat_reg[10], m_cont_reg[48], m_read_ahead;
	uint8_t m_v9958_sp_mode;

	// memory
	uint16_t m_address_latch;
	int m_vram_size;

	// interrupt
	uint8_t m_int_state;
>>>>>>> upstream/master
	devcb_write_line   m_int_callback;
	int m_scanline;
	// blinking
	int m_blink, m_blink_count;
	// mouse
<<<<<<< HEAD
	UINT8 m_mx_delta, m_my_delta;
	// mouse & lightpen
	UINT8 m_button_state;
	// palette
	UINT16 m_pal_ind16[16];
	UINT16 m_pal_ind256[256];
=======
	uint8_t m_mx_delta, m_my_delta;
	// mouse & lightpen
	uint8_t m_button_state;
	// palette
	uint16_t m_pal_ind16[16];
	uint16_t m_pal_ind256[256];
>>>>>>> upstream/master
	// render bitmap
	bitmap_ind16 m_bitmap;
	// Command unit
	struct {
		int SX,SY;
		int DX,DY;
		int TX,TY;
		int NX,NY;
		int MX;
		int ASX,ADX,ANX;
<<<<<<< HEAD
		UINT8 CL;
		UINT8 LO;
		UINT8 CM;
		UINT8 MXS, MXD;
=======
		uint8_t CL;
		uint8_t LO;
		uint8_t CM;
		uint8_t MXS, MXD;
>>>>>>> upstream/master
	} m_mmc;
	int  m_vdp_ops_count;
	void (v99x8_device::*m_vdp_engine)();

	struct v99x8_mode
	{
<<<<<<< HEAD
		UINT8 m;
		void (v99x8_device::*visible_16)(const pen_t *, UINT16*, int);
		void (v99x8_device::*border_16)(const pen_t *, UINT16*);
		void (v99x8_device::*sprites)(int, UINT8*);
		void (v99x8_device::*draw_sprite_16)(const pen_t *, UINT16*, UINT8*);
	} ;
	static const v99x8_mode s_modes[];
	required_device<palette_device> m_palette;
	emu_timer *m_line_timer;
	UINT8 m_pal_ntsc;
=======
		uint8_t m;
		void (v99x8_device::*visible_16)(uint16_t*, int);
		void (v99x8_device::*border_16)(uint16_t*);
		void (v99x8_device::*sprites)(int, uint8_t*);
		void (v99x8_device::*draw_sprite_16)(uint16_t*, uint8_t*);
	} ;
	static const v99x8_mode s_modes[];
	emu_timer *m_line_timer;
	uint8_t m_pal_ntsc;
>>>>>>> upstream/master
	int m_scanline_start;
	int m_vblank_start;
	int m_scanline_max;
	int m_height;
protected:
<<<<<<< HEAD
	static UINT16 s_pal_indYJK[0x20000];
=======
	static uint16_t s_pal_indYJK[0x20000];
>>>>>>> upstream/master
};


class v9938_device : public v99x8_device
{
public:
<<<<<<< HEAD
	v9938_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	DECLARE_PALETTE_INIT(v9938);
protected:
	virtual machine_config_constructor device_mconfig_additions() const;
=======
	v9938_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

protected:
	virtual void palette_init() override;
	virtual u32 palette_entries() const override { return 512; }
>>>>>>> upstream/master
};

class v9958_device : public v99x8_device
{
public:
<<<<<<< HEAD
	v9958_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	DECLARE_PALETTE_INIT(v9958);

protected:
	virtual machine_config_constructor device_mconfig_additions() const;
};


#endif
=======
	v9958_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

protected:
	virtual void palette_init() override;
	virtual u32 palette_entries() const override { return 19780; }
};


#endif // MAME_DEVICES_VIDEO_V9938_H
>>>>>>> upstream/master
