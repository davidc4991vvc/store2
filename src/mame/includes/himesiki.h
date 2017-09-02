// license:BSD-3-Clause
// copyright-holders:Uki
<<<<<<< HEAD
=======

>>>>>>> upstream/master
/*************************************************************************

    Himeshikibu

*************************************************************************/

<<<<<<< HEAD
=======
#include "machine/gen_latch.h"

>>>>>>> upstream/master
class himesiki_state : public driver_device
{
public:
	himesiki_state(const machine_config &mconfig, device_type type, const char *tag)
		: driver_device(mconfig, type, tag),
		m_bg_ram(*this, "bg_ram"),
<<<<<<< HEAD
		m_spriteram(*this, "spriteram"),
		m_subcpu(*this, "sub"),
		m_maincpu(*this, "maincpu"),
		m_gfxdecode(*this, "gfxdecode"),
		m_palette(*this, "palette")  { }

	/* memory pointers */
	required_shared_ptr<UINT8> m_bg_ram;
	required_shared_ptr<UINT8> m_spriteram;
=======
		m_spriteram_p103a(*this, "sprram_p103a"),
		m_spriteram(*this, "spriteram"),
		m_maincpu(*this, "maincpu"),
		m_subcpu(*this, "sub"),
		m_gfxdecode(*this, "gfxdecode"),
		m_palette(*this, "palette"),
		m_soundlatch(*this, "soundlatch") { }

	/* memory pointers */
	required_shared_ptr<uint8_t> m_bg_ram;
	required_shared_ptr<uint8_t> m_spriteram_p103a;
	required_shared_ptr<uint8_t> m_spriteram;
>>>>>>> upstream/master

	/* video-related */
	tilemap_t    *m_bg_tilemap;
	int          m_scrollx[2];
<<<<<<< HEAD
	int        m_flipscreen;

	/* devices */
	required_device<cpu_device> m_subcpu;
=======
	int          m_scrolly;

	int        m_flipscreen;

	/* devices */
	required_device<cpu_device> m_maincpu;
	required_device<cpu_device> m_subcpu;
	required_device<gfxdecode_device> m_gfxdecode;
	required_device<palette_device> m_palette;
	required_device<generic_latch_8_device> m_soundlatch;

>>>>>>> upstream/master
	DECLARE_WRITE8_MEMBER(himesiki_rombank_w);
	DECLARE_WRITE8_MEMBER(himesiki_sound_w);
	DECLARE_WRITE8_MEMBER(himesiki_bg_ram_w);
	DECLARE_WRITE8_MEMBER(himesiki_scrollx_w);
<<<<<<< HEAD
	DECLARE_WRITE8_MEMBER(himesiki_flip_w);
	TILE_GET_INFO_MEMBER(get_bg_tile_info);
	virtual void machine_start();
	virtual void machine_reset();
	virtual void video_start();
	UINT32 screen_update_himesiki(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
	void himesiki_draw_sprites( bitmap_ind16 &bitmap, const rectangle &cliprect );
	required_device<cpu_device> m_maincpu;
	required_device<gfxdecode_device> m_gfxdecode;
	required_device<palette_device> m_palette;
=======
	DECLARE_WRITE8_MEMBER(himesiki_scrolly_w);
	TILE_GET_INFO_MEMBER(get_bg_tile_info);
	virtual void machine_start() override;
	virtual void machine_reset() override;
	virtual void video_start() override;
	uint32_t screen_update_himesiki(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
	void himesiki_draw_sprites( bitmap_ind16 &bitmap, const rectangle &cliprect );
>>>>>>> upstream/master
};
