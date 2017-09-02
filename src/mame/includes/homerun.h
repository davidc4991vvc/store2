<<<<<<< HEAD
// license:LGPL-2.1+
=======
// license:BSD-3-Clause
>>>>>>> upstream/master
// copyright-holders:Tomasz Slanina
/*************************************************************************

    Jaleco Moero Pro Yakyuu Homerun hardware

*************************************************************************/

#include "sound/upd7759.h"
#include "sound/samples.h"
<<<<<<< HEAD
=======
#include "screen.h"
>>>>>>> upstream/master

class homerun_state : public driver_device
{
public:
	homerun_state(const machine_config &mconfig, device_type type, const char *tag)
		: driver_device(mconfig, type, tag),
		m_maincpu(*this, "maincpu"),
		m_videoram(*this, "videoram"),
		m_spriteram(*this, "spriteram"),
		m_colorram(*this, "colorram"),
		m_d7756(*this, "d7756"),
		m_samples(*this, "samples"),
		m_gfxdecode(*this, "gfxdecode"),
		m_screen(*this, "screen"),
		m_palette(*this, "palette")
	{ }

	required_device<cpu_device> m_maincpu;
<<<<<<< HEAD
	required_shared_ptr<UINT8> m_videoram;
	required_shared_ptr<UINT8> m_spriteram;
	required_shared_ptr<UINT8> m_colorram;
=======
	required_shared_ptr<uint8_t> m_videoram;
	required_shared_ptr<uint8_t> m_spriteram;
	required_shared_ptr<uint8_t> m_colorram;
>>>>>>> upstream/master
	optional_device<upd7756_device> m_d7756;
	optional_device<samples_device> m_samples;
	required_device<gfxdecode_device> m_gfxdecode;
	required_device<screen_device> m_screen;
	required_device<palette_device> m_palette;

<<<<<<< HEAD
	UINT8 m_control;
	UINT8 m_sample;
=======
	uint8_t m_control;
	uint8_t m_sample;
>>>>>>> upstream/master

	tilemap_t *m_tilemap;
	int m_gfx_ctrl;
	int m_scrollx;
	int m_scrolly;

	DECLARE_WRITE8_MEMBER(homerun_control_w);
	DECLARE_WRITE8_MEMBER(homerun_d7756_sample_w);
	DECLARE_WRITE8_MEMBER(homerun_videoram_w);
	DECLARE_WRITE8_MEMBER(homerun_color_w);
	DECLARE_WRITE8_MEMBER(homerun_scrollhi_w);
	DECLARE_WRITE8_MEMBER(homerun_scrolly_w);
	DECLARE_WRITE8_MEMBER(homerun_scrollx_w);

	DECLARE_CUSTOM_INPUT_MEMBER(homerun_sprite0_r);
	DECLARE_CUSTOM_INPUT_MEMBER(homerun_d7756_busy_r);
	DECLARE_CUSTOM_INPUT_MEMBER(ganjaja_d7756_busy_r);
	DECLARE_CUSTOM_INPUT_MEMBER(ganjaja_hopper_status_r);

	TILE_GET_INFO_MEMBER(get_homerun_tile_info);
<<<<<<< HEAD
	virtual void machine_start();
	virtual void machine_reset();
	virtual void video_start();
	UINT32 screen_update_homerun(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
=======
	virtual void machine_start() override;
	virtual void machine_reset() override;
	virtual void video_start() override;
	uint32_t screen_update_homerun(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
>>>>>>> upstream/master
	DECLARE_WRITE8_MEMBER(homerun_banking_w);
	void draw_sprites( bitmap_ind16 &bitmap, const rectangle &cliprect );
};
