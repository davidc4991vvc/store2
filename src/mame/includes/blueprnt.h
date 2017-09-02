// license:BSD-3-Clause
// copyright-holders:Nicola Salmoria
/***************************************************************************

    Blue Print

***************************************************************************/

<<<<<<< HEAD
=======
#include "machine/gen_latch.h"

>>>>>>> upstream/master
class blueprnt_state : public driver_device
{
public:
	blueprnt_state(const machine_config &mconfig, device_type type, const char *tag)
		: driver_device(mconfig, type, tag),
<<<<<<< HEAD
		m_audiocpu(*this, "audiocpu"),
		m_videoram(*this, "videoram"),
		m_scrollram(*this, "scrollram"),
		m_spriteram(*this, "spriteram"),
		m_colorram(*this, "colorram"),
		m_maincpu(*this, "maincpu"),
		m_gfxdecode(*this, "gfxdecode"),
		m_palette(*this, "palette") { }

	/* device/memory pointers */
	required_device<cpu_device> m_audiocpu;
	required_shared_ptr<UINT8> m_videoram;
	required_shared_ptr<UINT8> m_scrollram;
	required_shared_ptr<UINT8> m_spriteram;
	required_shared_ptr<UINT8> m_colorram;
=======
		m_maincpu(*this, "maincpu"),
		m_audiocpu(*this, "audiocpu"),
		m_gfxdecode(*this, "gfxdecode"),
		m_palette(*this, "palette"),
		m_soundlatch(*this, "soundlatch"),
		m_videoram(*this, "videoram"),
		m_scrollram(*this, "scrollram"),
		m_spriteram(*this, "spriteram"),
		m_colorram(*this, "colorram") { }

	/* device/memory pointers */
	required_device<cpu_device> m_maincpu;
	required_device<cpu_device> m_audiocpu;
	required_device<gfxdecode_device> m_gfxdecode;
	required_device<palette_device> m_palette;
	required_device<generic_latch_8_device> m_soundlatch;
	required_shared_ptr<uint8_t> m_videoram;
	required_shared_ptr<uint8_t> m_scrollram;
	required_shared_ptr<uint8_t> m_spriteram;
	required_shared_ptr<uint8_t> m_colorram;
>>>>>>> upstream/master

	/* video-related */
	tilemap_t *m_bg_tilemap;
	int     m_gfx_bank;

	/* misc */
	int     m_dipsw;

	DECLARE_READ8_MEMBER(blueprnt_sh_dipsw_r);
	DECLARE_READ8_MEMBER(grasspin_sh_dipsw_r);
	DECLARE_WRITE8_MEMBER(blueprnt_sound_command_w);
	DECLARE_WRITE8_MEMBER(blueprnt_coin_counter_w);
	DECLARE_WRITE8_MEMBER(blueprnt_videoram_w);
	DECLARE_WRITE8_MEMBER(blueprnt_colorram_w);
	DECLARE_WRITE8_MEMBER(blueprnt_flipscreen_w);
	DECLARE_WRITE8_MEMBER(dipsw_w);
	TILE_GET_INFO_MEMBER(get_bg_tile_info);
<<<<<<< HEAD
	virtual void machine_start();
	virtual void machine_reset();
	DECLARE_VIDEO_START(blueprnt);
	DECLARE_PALETTE_INIT(blueprnt);
	UINT32 screen_update_blueprnt(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
	void draw_sprites( bitmap_ind16 &bitmap, const rectangle &cliprect );
	required_device<cpu_device> m_maincpu;
	required_device<gfxdecode_device> m_gfxdecode;
	required_device<palette_device> m_palette;
=======
	virtual void machine_start() override;
	virtual void machine_reset() override;
	DECLARE_VIDEO_START(blueprnt);
	DECLARE_PALETTE_INIT(blueprnt);
	uint32_t screen_update_blueprnt(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
	void draw_sprites( bitmap_ind16 &bitmap, const rectangle &cliprect );
>>>>>>> upstream/master
};
