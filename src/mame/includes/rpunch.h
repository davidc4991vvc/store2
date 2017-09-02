// license:BSD-3-Clause
// copyright-holders:Aaron Giles
<<<<<<< HEAD
#include "sound/upd7759.h"
=======

#include "machine/gen_latch.h"
#include "sound/upd7759.h"
#include "video/vsystem_gga.h"
#include "screen.h"
>>>>>>> upstream/master

class rpunch_state : public driver_device
{
public:
	rpunch_state(const machine_config &mconfig, device_type type, const char *tag)
		: driver_device(mconfig, type, tag),
		m_maincpu(*this, "maincpu"),
		m_audiocpu(*this, "audiocpu"),
<<<<<<< HEAD
=======
		m_soundlatch(*this, "soundlatch"),
>>>>>>> upstream/master
		m_upd7759(*this, "upd"),
		m_gfxdecode(*this, "gfxdecode"),
		m_screen(*this, "screen"),
		m_palette(*this, "palette"),
<<<<<<< HEAD
=======
		m_gga(*this, "gga"),
>>>>>>> upstream/master
		m_videoram(*this, "videoram"),
		m_bitmapram(*this, "bitmapram"),
		m_spriteram(*this, "spriteram") { }

	required_device<cpu_device> m_maincpu;
	required_device<cpu_device> m_audiocpu;
<<<<<<< HEAD
=======
	required_device<generic_latch_8_device> m_soundlatch;
>>>>>>> upstream/master
	required_device<upd7759_device> m_upd7759;
	required_device<gfxdecode_device> m_gfxdecode;
	required_device<screen_device> m_screen;
	required_device<palette_device> m_palette;
<<<<<<< HEAD

	required_shared_ptr<UINT16> m_videoram;
	required_shared_ptr<UINT16> m_bitmapram;
	required_shared_ptr<UINT16> m_spriteram;

	UINT8 m_sound_data;
	UINT8 m_sound_busy;
	UINT8 m_ym2151_irq;
	UINT8 m_upd_rom_bank;
	int m_sprite_palette;
	int m_sprite_xoffs;
	UINT16 m_videoflags;
	UINT8 m_crtc_register;
	UINT8 m_bins;
	UINT8 m_gins;
	tilemap_t *m_background[2];
	emu_timer *m_crtc_timer;
	DECLARE_WRITE_LINE_MEMBER(ym2151_irq_gen);
	DECLARE_WRITE16_MEMBER(sound_command_w);
	DECLARE_READ8_MEMBER(sound_command_r);
=======
	required_device<vsystem_gga_device> m_gga;

	required_shared_ptr<uint16_t> m_videoram;
	required_shared_ptr<uint16_t> m_bitmapram;
	required_shared_ptr<uint16_t> m_spriteram;

	uint8_t m_upd_rom_bank;
	int m_sprite_palette;
	int m_sprite_xoffs;
	uint16_t m_videoflags;
	uint8_t m_bins;
	uint8_t m_gins;
	tilemap_t *m_background[2];
	emu_timer *m_crtc_timer;

>>>>>>> upstream/master
	DECLARE_READ16_MEMBER(sound_busy_r);
	DECLARE_WRITE16_MEMBER(rpunch_videoram_w);
	DECLARE_WRITE16_MEMBER(rpunch_videoreg_w);
	DECLARE_WRITE16_MEMBER(rpunch_scrollreg_w);
<<<<<<< HEAD
	DECLARE_WRITE16_MEMBER(rpunch_crtc_data_w);
	DECLARE_WRITE16_MEMBER(rpunch_crtc_register_w);
=======
	DECLARE_WRITE8_MEMBER(rpunch_gga_w);
	DECLARE_WRITE8_MEMBER(rpunch_gga_data_w);
>>>>>>> upstream/master
	DECLARE_WRITE16_MEMBER(rpunch_ins_w);
	DECLARE_CUSTOM_INPUT_MEMBER(hi_bits_r);
	DECLARE_WRITE8_MEMBER(upd_control_w);
	DECLARE_WRITE8_MEMBER(upd_data_w);
	DECLARE_DRIVER_INIT(rabiolep);
	DECLARE_DRIVER_INIT(svolley);
	TILE_GET_INFO_MEMBER(get_bg0_tile_info);
	TILE_GET_INFO_MEMBER(get_bg1_tile_info);
<<<<<<< HEAD
	virtual void machine_start();
	virtual void machine_reset();
=======
	virtual void machine_start() override;
	virtual void machine_reset() override;
>>>>>>> upstream/master

	DECLARE_VIDEO_START(rpunch);
	DECLARE_VIDEO_START(svolley);


<<<<<<< HEAD
	UINT32 screen_update_rpunch(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
	TIMER_CALLBACK_MEMBER(sound_command_w_callback);
=======
	uint32_t screen_update_rpunch(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
>>>>>>> upstream/master
	TIMER_CALLBACK_MEMBER(crtc_interrupt_gen);
	void draw_sprites(bitmap_ind16 &bitmap, const rectangle &cliprect, int start, int stop);
	void draw_bitmap(bitmap_ind16 &bitmap, const rectangle &cliprect);
};
