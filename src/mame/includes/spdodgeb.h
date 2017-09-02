// license:BSD-3-Clause
// copyright-holders:Paul Hampson, Nicola Salmoria
/*************************************************************************

    Super Dodge Ball hardware

*************************************************************************/

<<<<<<< HEAD
#include "sound/msm5205.h"
=======
#include "machine/gen_latch.h"
#include "sound/msm5205.h"
#include "screen.h"
>>>>>>> upstream/master

class spdodgeb_state : public driver_device
{
public:
	spdodgeb_state(const machine_config &mconfig, device_type type, const char *tag)
		: driver_device(mconfig, type, tag),
		m_maincpu(*this,"maincpu"),
		m_audiocpu(*this, "audiocpu"),
		m_msm1(*this, "msm1"),
		m_msm2(*this, "msm2"),
		m_gfxdecode(*this, "gfxdecode"),
		m_screen(*this, "screen"),
		m_palette(*this, "palette"),
<<<<<<< HEAD
=======
		m_soundlatch(*this, "soundlatch"),
>>>>>>> upstream/master
		m_videoram(*this, "videoram"),
		m_spriteram(*this, "spriteram") { }

	required_device<cpu_device> m_maincpu;
	required_device<cpu_device> m_audiocpu;
	required_device<msm5205_device> m_msm1;
	required_device<msm5205_device> m_msm2;
	required_device<gfxdecode_device> m_gfxdecode;
	required_device<screen_device> m_screen;
	required_device<palette_device> m_palette;
<<<<<<< HEAD

	required_shared_ptr<UINT8> m_videoram;
	required_shared_ptr<UINT8> m_spriteram;
=======
	required_device<generic_latch_8_device> m_soundlatch;

	required_shared_ptr<uint8_t> m_videoram;
	required_shared_ptr<uint8_t> m_spriteram;
>>>>>>> upstream/master

	int m_toggle;
	int m_adpcm_pos[2];
	int m_adpcm_end[2];
	int m_adpcm_idle[2];
	int m_adpcm_data[2];
	int m_mcu63701_command;
	int m_inputs[4];
<<<<<<< HEAD
	UINT8 m_tapc[4];
	UINT8 m_last_port[2];
	UINT8 m_last_dash[2];
=======
	uint8_t m_tapc[4];
	uint8_t m_last_port[2];
	uint8_t m_last_dash[2];
>>>>>>> upstream/master
#if 0
	int m_running[2];
	int m_jumped[2];
	int m_prev[2][2];
	int m_countup[2][2];
	int m_countdown[2][2];
	int m_prev[2];
#endif
	int m_tile_palbank;
	int m_sprite_palbank;
	tilemap_t *m_bg_tilemap;
	int m_lastscroll;

<<<<<<< HEAD
	DECLARE_WRITE8_MEMBER(sound_command_w);
=======
>>>>>>> upstream/master
	DECLARE_WRITE8_MEMBER(spd_adpcm_w);
	DECLARE_READ8_MEMBER(mcu63701_r);
	DECLARE_WRITE8_MEMBER(mcu63701_w);
	DECLARE_WRITE8_MEMBER(scrollx_lo_w);
	DECLARE_WRITE8_MEMBER(ctrl_w);
	DECLARE_WRITE8_MEMBER(videoram_w);
	DECLARE_WRITE_LINE_MEMBER(spd_adpcm_int_1);
	DECLARE_WRITE_LINE_MEMBER(spd_adpcm_int_2);

	TILEMAP_MAPPER_MEMBER(background_scan);
	TILE_GET_INFO_MEMBER(get_bg_tile_info);

<<<<<<< HEAD
	virtual void machine_start();
	virtual void machine_reset();
	virtual void video_start();
	DECLARE_PALETTE_INIT(spdodgeb);

	UINT32 screen_update(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
=======
	virtual void machine_start() override;
	virtual void machine_reset() override;
	virtual void video_start() override;
	DECLARE_PALETTE_INIT(spdodgeb);

	uint32_t screen_update(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
>>>>>>> upstream/master
	void draw_sprites(bitmap_ind16 &bitmap, const rectangle &cliprect );

	TIMER_DEVICE_CALLBACK_MEMBER(interrupt);
	DECLARE_CUSTOM_INPUT_MEMBER(mcu63705_busy_r);

	void mcu63705_update_inputs();
	void spd_adpcm_int(msm5205_device *device, int chip);
};
