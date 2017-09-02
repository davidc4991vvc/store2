// license:BSD-3-Clause
// copyright-holders:Ernesto Corvi, Juergen Buchmueller, Alex Pasadyn, Aaron Giles, Nicola Salmoria
/*************************************************************************

    Pole Position hardware

*************************************************************************/
<<<<<<< HEAD

#include "sound/filter.h"
#include "sound/namco.h"
#include "sound/tms5220.h"
#include "sound/discrete.h"
=======
#ifndef MAME_INCLUDES_POLEPOS_H
#define MAME_INCLUDES_POLEPOS_H

#pragma once

#include "machine/74259.h"
#include "machine/gen_latch.h"
#include "sound/namco.h"
#include "sound/discrete.h"
#include "screen.h"

struct filter2_context
{
	filter2_context() :
		x0(0.0),
		x1(0.0),
		x2(0.0),
		y0(0.0),
		y1(0.0),
		y2(0.0),
		a1(0.0),
		a2(0.0),
		b0(0.0),
		b1(0.0),
		b2(0.0)
	{}

	double x0, x1, x2;  /* x[k], x[k-1], x[k-2], current and previous 2 input values */
	double y0, y1, y2;  /* y[k], y[k-1], y[k-2], current and previous 2 output values */
	double a1, a2;      /* digital filter coefficients, denominator */
	double b0, b1, b2;  /* digital filter coefficients, numerator */
};
>>>>>>> upstream/master


class polepos_state : public driver_device
{
public:
	polepos_state(const machine_config &mconfig, device_type type, const char *tag)
		: driver_device(mconfig, type, tag),
		m_maincpu(*this, "maincpu"),
		m_subcpu(*this, "sub"),
		m_subcpu2(*this, "sub2"),
<<<<<<< HEAD
		m_namco_sound(*this, "namco"),
		m_tms(*this, "tms"),
=======
		m_sound_z80(*this, "soundz80bl"),
		m_soundlatch(*this, "soundlatch"),
		m_namco_sound(*this, "namco"),
		m_latch(*this, "latch"),
>>>>>>> upstream/master
		m_sprite16_memory(*this, "sprite16_memory"),
		m_road16_memory(*this, "road16_memory"),
		m_alpha16_memory(*this, "alpha16_memory"),
		m_view16_memory(*this, "view16_memory"),
		m_gfxdecode(*this, "gfxdecode"),
		m_screen(*this, "screen"),
		m_palette(*this, "palette") { }

	required_device<cpu_device> m_maincpu;
	required_device<cpu_device> m_subcpu;
	required_device<cpu_device> m_subcpu2;
<<<<<<< HEAD
	optional_device<namco_device> m_namco_sound;
	optional_device<tms5220_device> m_tms;
	UINT8 m_steer_last;
	UINT8 m_steer_delta;
	INT16 m_steer_accum;
	INT16 m_last_result;
	INT8 m_last_signed;
	UINT8 m_last_unsigned;
	int m_adc_input;
	int m_auto_start_mask;
	required_shared_ptr<UINT16> m_sprite16_memory;
	required_shared_ptr<UINT16> m_road16_memory;
	required_shared_ptr<UINT16> m_alpha16_memory;
	required_shared_ptr<UINT16> m_view16_memory;
=======
	optional_device<cpu_device> m_sound_z80;
	optional_device<generic_latch_8_device> m_soundlatch;
	optional_device<namco_device> m_namco_sound;
	required_device<ls259_device> m_latch;
	uint8_t m_steer_last;
	uint8_t m_steer_delta;
	int16_t m_steer_accum;
	int16_t m_last_result;
	int8_t m_last_signed;
	uint8_t m_last_unsigned;
	int m_adc_input;
	int m_auto_start_mask;
	required_shared_ptr<uint16_t> m_sprite16_memory;
	required_shared_ptr<uint16_t> m_road16_memory;
	required_shared_ptr<uint16_t> m_alpha16_memory;
	required_shared_ptr<uint16_t> m_view16_memory;
>>>>>>> upstream/master
	required_device<gfxdecode_device> m_gfxdecode;
	required_device<screen_device> m_screen;
	required_device<palette_device> m_palette;

<<<<<<< HEAD
	UINT16 m_vertical_position_modifier[256];
	UINT16 m_road16_vscroll;
	tilemap_t *m_bg_tilemap;
	tilemap_t *m_tx_tilemap;
	int m_chacl;
	UINT16 m_scroll;
	UINT8 m_main_irq_mask;
	UINT8 m_sub_irq_mask;
	DECLARE_READ16_MEMBER(polepos2_ic25_r);
	DECLARE_READ8_MEMBER(polepos_adc_r);
	DECLARE_READ8_MEMBER(polepos_ready_r);
	DECLARE_WRITE8_MEMBER(polepos_latch_w);
=======
	uint16_t m_vertical_position_modifier[256];
	uint16_t m_road16_vscroll;
	tilemap_t *m_bg_tilemap;
	tilemap_t *m_tx_tilemap;
	int m_chacl;
	uint16_t m_scroll;
	uint8_t m_sub_irq_mask;
	DECLARE_READ16_MEMBER(polepos2_ic25_r);
	DECLARE_READ8_MEMBER(polepos_adc_r);
	DECLARE_READ8_MEMBER(polepos_ready_r);
	DECLARE_WRITE_LINE_MEMBER(iosel_w);
	DECLARE_WRITE_LINE_MEMBER(clson_w);
	DECLARE_WRITE_LINE_MEMBER(gasel_w);
	DECLARE_WRITE_LINE_MEMBER(sb0_w);
	DECLARE_WRITE_LINE_MEMBER(chacl_w);
>>>>>>> upstream/master
	DECLARE_WRITE16_MEMBER(polepos_z8002_nvi_enable_w);
	DECLARE_READ16_MEMBER(polepos_sprite16_r);
	DECLARE_WRITE16_MEMBER(polepos_sprite16_w);
	DECLARE_READ8_MEMBER(polepos_sprite_r);
	DECLARE_WRITE8_MEMBER(polepos_sprite_w);
	DECLARE_READ16_MEMBER(polepos_road16_r);
	DECLARE_WRITE16_MEMBER(polepos_road16_w);
	DECLARE_READ8_MEMBER(polepos_road_r);
	DECLARE_WRITE8_MEMBER(polepos_road_w);
	DECLARE_WRITE16_MEMBER(polepos_road16_vscroll_w);
	DECLARE_READ16_MEMBER(polepos_view16_r);
	DECLARE_WRITE16_MEMBER(polepos_view16_w);
	DECLARE_READ8_MEMBER(polepos_view_r);
	DECLARE_WRITE8_MEMBER(polepos_view_w);
	DECLARE_WRITE16_MEMBER(polepos_view16_hscroll_w);
	DECLARE_WRITE8_MEMBER(polepos_chacl_w);
	DECLARE_READ16_MEMBER(polepos_alpha16_r);
	DECLARE_WRITE16_MEMBER(polepos_alpha16_w);
	DECLARE_READ8_MEMBER(polepos_alpha_r);
	DECLARE_WRITE8_MEMBER(polepos_alpha_w);
<<<<<<< HEAD
	DECLARE_CUSTOM_INPUT_MEMBER(high_port_r);
	DECLARE_CUSTOM_INPUT_MEMBER(low_port_r);
=======
>>>>>>> upstream/master
	DECLARE_CUSTOM_INPUT_MEMBER(auto_start_r);
	DECLARE_WRITE8_MEMBER(out_0);
	DECLARE_WRITE8_MEMBER(out_1);
	DECLARE_READ8_MEMBER(namco_52xx_rom_r);
	DECLARE_READ8_MEMBER(namco_52xx_si_r);
	DECLARE_READ8_MEMBER(namco_53xx_k_r);
	DECLARE_READ8_MEMBER(steering_changed_r);
	DECLARE_READ8_MEMBER(steering_delta_r);
<<<<<<< HEAD
	DECLARE_DRIVER_INIT(topracern);
=======
	DECLARE_WRITE8_MEMBER(bootleg_soundlatch_w);
>>>>>>> upstream/master
	DECLARE_DRIVER_INIT(polepos2);
	TILE_GET_INFO_MEMBER(bg_get_tile_info);
	TILE_GET_INFO_MEMBER(tx_get_tile_info);
	DECLARE_MACHINE_RESET(polepos);
	DECLARE_VIDEO_START(polepos);
	DECLARE_PALETTE_INIT(polepos);
<<<<<<< HEAD
	UINT32 screen_update_polepos(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
	TIMER_DEVICE_CALLBACK_MEMBER(polepos_scanline);
	void draw_road(bitmap_ind16 &bitmap);
	void draw_sprites(bitmap_ind16 &bitmap, const rectangle &cliprect );
	void zoom_sprite(bitmap_ind16 &bitmap,int big,UINT32 code,UINT32 color,int flipx,int sx,int sy,int sizex,int sizey);
=======
	uint32_t screen_update_polepos(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
	TIMER_DEVICE_CALLBACK_MEMBER(polepos_scanline);
	void draw_road(bitmap_ind16 &bitmap);
	void draw_sprites(bitmap_ind16 &bitmap, const rectangle &cliprect );
	void zoom_sprite(bitmap_ind16 &bitmap,int big,uint32_t code,uint32_t color,int flipx,int sx,int sy,int sizex,int sizey);
>>>>>>> upstream/master
};


/*----------- defined in audio/polepos.c -----------*/

class polepos_sound_device : public device_t,
								public device_sound_interface
{
public:
<<<<<<< HEAD
	polepos_sound_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
=======
	polepos_sound_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
>>>>>>> upstream/master
	~polepos_sound_device() { }

protected:
	// device-level overrides
<<<<<<< HEAD
	virtual void device_start();
	virtual void device_reset();

	// sound stream update overrides
	virtual void sound_stream_update(sound_stream &stream, stream_sample_t **inputs, stream_sample_t **outputs, int samples);
=======
	virtual void device_start() override;
	virtual void device_reset() override;

	// sound stream update overrides
	virtual void sound_stream_update(sound_stream &stream, stream_sample_t **inputs, stream_sample_t **outputs, int samples) override;
>>>>>>> upstream/master

public:
	DECLARE_WRITE8_MEMBER( polepos_engine_sound_lsb_w );
	DECLARE_WRITE8_MEMBER( polepos_engine_sound_msb_w );

private:
<<<<<<< HEAD
	UINT32 m_current_position;
=======
	uint32_t m_current_position;
>>>>>>> upstream/master
	int m_sample_msb;
	int m_sample_lsb;
	int m_sample_enable;
	sound_stream *m_stream;
	filter2_context m_filter_engine[3];
};

<<<<<<< HEAD
extern const device_type POLEPOS;

DISCRETE_SOUND_EXTERN( polepos );
=======
DECLARE_DEVICE_TYPE(POLEPOS, polepos_sound_device)

DISCRETE_SOUND_EXTERN( polepos );

#endif // MAME_INCLUDES_POLEPOS_H
>>>>>>> upstream/master
