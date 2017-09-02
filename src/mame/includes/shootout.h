// license:BSD-3-Clause
// copyright-holders:Ernesto Corvi, Phil Stroffolino, Bryan McPhail
<<<<<<< HEAD
=======

#include "machine/gen_latch.h"

>>>>>>> upstream/master
class shootout_state : public driver_device
{
public:
	shootout_state(const machine_config &mconfig, device_type type, const char *tag)
		: driver_device(mconfig, type, tag),
		m_maincpu(*this, "maincpu"),
		m_audiocpu(*this, "audiocpu"),
		m_gfxdecode(*this, "gfxdecode"),
		m_palette(*this, "palette"),
<<<<<<< HEAD
=======
		m_soundlatch(*this, "soundlatch"),
>>>>>>> upstream/master
		m_spriteram(*this, "spriteram"),
		m_textram(*this, "textram"),
		m_videoram(*this, "videoram")  { }

	required_device<cpu_device> m_maincpu;
	optional_device<cpu_device> m_audiocpu;
	required_device<gfxdecode_device> m_gfxdecode;
	required_device<palette_device> m_palette;
<<<<<<< HEAD

	required_shared_ptr<UINT8> m_spriteram;
	required_shared_ptr<UINT8> m_textram;
	required_shared_ptr<UINT8> m_videoram;

	tilemap_t *m_background;
	tilemap_t *m_foreground;
	int m_bFlicker;

	DECLARE_WRITE8_MEMBER(bankswitch_w);
=======
	required_device<generic_latch_8_device> m_soundlatch;

	required_shared_ptr<uint8_t> m_spriteram;
	required_shared_ptr<uint8_t> m_textram;
	required_shared_ptr<uint8_t> m_videoram;

	tilemap_t *m_background;
	tilemap_t *m_foreground;

	int m_ccnt_old_val;

	DECLARE_WRITE8_MEMBER(bankswitch_w);
	DECLARE_READ8_MEMBER(sound_cpu_command_r);
>>>>>>> upstream/master
	DECLARE_WRITE8_MEMBER(sound_cpu_command_w);
	DECLARE_WRITE8_MEMBER(flipscreen_w);
	DECLARE_WRITE8_MEMBER(coincounter_w);
	DECLARE_WRITE8_MEMBER(videoram_w);
	DECLARE_WRITE8_MEMBER(textram_w);

	DECLARE_INPUT_CHANGED_MEMBER(coin_inserted);

	DECLARE_DRIVER_INIT(shootout);
<<<<<<< HEAD
	virtual void video_start();
=======

	virtual void machine_reset() override;
	virtual void video_start() override;

>>>>>>> upstream/master
	DECLARE_PALETTE_INIT(shootout);

	TILE_GET_INFO_MEMBER(get_bg_tile_info);
	TILE_GET_INFO_MEMBER(get_fg_tile_info);

<<<<<<< HEAD
	UINT32 screen_update_shootout(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
	UINT32 screen_update_shootouj(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
=======
	uint32_t screen_update_shootout(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
	uint32_t screen_update_shootouj(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
>>>>>>> upstream/master
	void draw_sprites(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect, int bank_bits );
};
