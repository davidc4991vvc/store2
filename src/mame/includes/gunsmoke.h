<<<<<<< HEAD
// license:???
=======
// license:BSD-3-Clause
>>>>>>> upstream/master
// copyright-holders:Paul Leaman
/*************************************************************************

    Gun.Smoke

*************************************************************************/

class gunsmoke_state : public driver_device
{
public:
	gunsmoke_state(const machine_config &mconfig, device_type type, const char *tag)
		: driver_device(mconfig, type, tag),
		m_videoram(*this, "videoram"),
		m_colorram(*this, "colorram"),
		m_scrollx(*this, "scrollx"),
		m_scrolly(*this, "scrolly"),
		m_spriteram(*this, "spriteram"),
		m_maincpu(*this, "maincpu"),
		m_gfxdecode(*this, "gfxdecode"),
		m_palette(*this, "palette") { }

	/* memory pointers */
<<<<<<< HEAD
	required_shared_ptr<UINT8> m_videoram;
	required_shared_ptr<UINT8> m_colorram;
	required_shared_ptr<UINT8> m_scrollx;
	required_shared_ptr<UINT8> m_scrolly;
	required_shared_ptr<UINT8> m_spriteram;
=======
	required_shared_ptr<uint8_t> m_videoram;
	required_shared_ptr<uint8_t> m_colorram;
	required_shared_ptr<uint8_t> m_scrollx;
	required_shared_ptr<uint8_t> m_scrolly;
	required_shared_ptr<uint8_t> m_spriteram;
>>>>>>> upstream/master

	/* video-related */
	tilemap_t    *m_bg_tilemap;
	tilemap_t    *m_fg_tilemap;
<<<<<<< HEAD
	UINT8      m_chon;
	UINT8      m_objon;
	UINT8      m_bgon;
	UINT8      m_sprite3bank;
=======
	uint8_t      m_chon;
	uint8_t      m_objon;
	uint8_t      m_bgon;
	uint8_t      m_sprite3bank;
>>>>>>> upstream/master
	DECLARE_READ8_MEMBER(gunsmoke_protection_r);
	DECLARE_WRITE8_MEMBER(gunsmoke_videoram_w);
	DECLARE_WRITE8_MEMBER(gunsmoke_colorram_w);
	DECLARE_WRITE8_MEMBER(gunsmoke_c804_w);
	DECLARE_WRITE8_MEMBER(gunsmoke_d806_w);
	TILE_GET_INFO_MEMBER(get_bg_tile_info);
	TILE_GET_INFO_MEMBER(get_fg_tile_info);
<<<<<<< HEAD
	virtual void machine_start();
	virtual void machine_reset();
	virtual void video_start();
	DECLARE_PALETTE_INIT(gunsmoke);
	UINT32 screen_update_gunsmoke(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
=======
	virtual void machine_start() override;
	virtual void machine_reset() override;
	virtual void video_start() override;
	DECLARE_PALETTE_INIT(gunsmoke);
	uint32_t screen_update_gunsmoke(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
>>>>>>> upstream/master
	void draw_sprites( bitmap_ind16 &bitmap, const rectangle &cliprect );
	required_device<cpu_device> m_maincpu;
	required_device<gfxdecode_device> m_gfxdecode;
	required_device<palette_device> m_palette;
};
