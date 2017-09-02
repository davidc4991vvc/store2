// license:BSD-3-Clause
// copyright-holders:David Haywood, Tomasz Slanina
<<<<<<< HEAD
=======

#include "machine/gen_latch.h"

>>>>>>> upstream/master
class mainsnk_state : public driver_device
{
public:
	mainsnk_state(const machine_config &mconfig, device_type type, const char *tag)
		: driver_device(mconfig, type, tag),
		m_maincpu(*this, "maincpu"),
		m_audiocpu(*this, "audiocpu"),
		m_gfxdecode(*this, "gfxdecode"),
		m_palette(*this, "palette"),
<<<<<<< HEAD
=======
		m_soundlatch(*this, "soundlatch"),
>>>>>>> upstream/master
		m_bgram(*this, "bgram"),
		m_spriteram(*this, "spriteram"),
		m_fgram(*this, "fgram") { }

	required_device<cpu_device> m_maincpu;
	required_device<cpu_device> m_audiocpu;
	required_device<gfxdecode_device> m_gfxdecode;
	required_device<palette_device> m_palette;
<<<<<<< HEAD

	required_shared_ptr<UINT8> m_bgram;
	required_shared_ptr<UINT8> m_spriteram;
	required_shared_ptr<UINT8> m_fgram;
=======
	required_device<generic_latch_8_device> m_soundlatch;

	required_shared_ptr<uint8_t> m_bgram;
	required_shared_ptr<uint8_t> m_spriteram;
	required_shared_ptr<uint8_t> m_fgram;
>>>>>>> upstream/master

	tilemap_t *m_tx_tilemap;
	tilemap_t *m_bg_tilemap;
	int m_sound_cpu_busy;
<<<<<<< HEAD
	UINT32 m_bg_tile_offset;

	DECLARE_WRITE8_MEMBER(sound_command_w);
=======
	uint32_t m_bg_tile_offset;

>>>>>>> upstream/master
	DECLARE_READ8_MEMBER(sound_ack_r);
	DECLARE_WRITE8_MEMBER(c600_w);
	DECLARE_WRITE8_MEMBER(fgram_w);
	DECLARE_WRITE8_MEMBER(bgram_w);

<<<<<<< HEAD
	DECLARE_CUSTOM_INPUT_MEMBER(sound_r);

=======
>>>>>>> upstream/master
	TILEMAP_MAPPER_MEMBER(marvins_tx_scan_cols);
	TILE_GET_INFO_MEMBER(get_tx_tile_info);
	TILE_GET_INFO_MEMBER(get_bg_tile_info);

<<<<<<< HEAD
	virtual void machine_start();
	virtual void video_start();
	DECLARE_PALETTE_INIT(mainsnk);

	UINT32 screen_update(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
=======
	virtual void video_start() override;
	DECLARE_PALETTE_INIT(mainsnk);

	uint32_t screen_update(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
>>>>>>> upstream/master
	void draw_sprites(bitmap_ind16 &bitmap, const rectangle &cliprect, int scrollx, int scrolly );
};
