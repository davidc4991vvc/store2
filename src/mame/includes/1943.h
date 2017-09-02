<<<<<<< HEAD
// license:???
=======
// license:BSD-3-Clause
>>>>>>> upstream/master
// copyright-holders:Paul Leaman
/***************************************************************************

    1943

***************************************************************************/

class _1943_state : public driver_device
{
public:
	_1943_state(const machine_config &mconfig, device_type type, const char *tag)
		: driver_device(mconfig, type, tag),
		m_maincpu(*this, "maincpu"),
		m_videoram(*this, "videoram"),
		m_colorram(*this, "colorram"),
		m_scrollx(*this, "scrollx"),
		m_scrolly(*this, "scrolly"),
		m_bgscrollx(*this, "bgscrollx"),
		m_spriteram(*this, "spriteram"),
		m_gfxdecode(*this, "gfxdecode"),
		m_palette(*this, "palette")
	{ }

	/* devices / memory pointers */
	required_device<cpu_device> m_maincpu;
<<<<<<< HEAD
	required_shared_ptr<UINT8> m_videoram;
	required_shared_ptr<UINT8> m_colorram;
	required_shared_ptr<UINT8> m_scrollx;
	required_shared_ptr<UINT8> m_scrolly;
	required_shared_ptr<UINT8> m_bgscrollx;
	required_shared_ptr<UINT8> m_spriteram;
=======
	required_shared_ptr<uint8_t> m_videoram;
	required_shared_ptr<uint8_t> m_colorram;
	required_shared_ptr<uint8_t> m_scrollx;
	required_shared_ptr<uint8_t> m_scrolly;
	required_shared_ptr<uint8_t> m_bgscrollx;
	required_shared_ptr<uint8_t> m_spriteram;
>>>>>>> upstream/master
	required_device<gfxdecode_device> m_gfxdecode;
	required_device<palette_device> m_palette;

	/* video-related */
	tilemap_t *m_fg_tilemap;
	tilemap_t *m_bg_tilemap;
	tilemap_t *m_bg2_tilemap;
	int     m_char_on;
	int     m_obj_on;
	int     m_bg1_on;
	int     m_bg2_on;

	/* protection */
<<<<<<< HEAD
	UINT8   m_prot_value;
=======
	uint8_t   m_prot_value;
>>>>>>> upstream/master
	DECLARE_WRITE8_MEMBER(c1943_protection_w);
	DECLARE_READ8_MEMBER(c1943_protection_r);
	DECLARE_READ8_MEMBER(_1943b_c007_r);

	DECLARE_WRITE8_MEMBER(c1943_videoram_w);
	DECLARE_WRITE8_MEMBER(c1943_colorram_w);
	DECLARE_WRITE8_MEMBER(c1943_c804_w);
	DECLARE_WRITE8_MEMBER(c1943_d806_w);
	DECLARE_DRIVER_INIT(1943b);
	DECLARE_DRIVER_INIT(1943);
	TILE_GET_INFO_MEMBER(c1943_get_bg2_tile_info);
	TILE_GET_INFO_MEMBER(c1943_get_bg_tile_info);
	TILE_GET_INFO_MEMBER(c1943_get_fg_tile_info);
<<<<<<< HEAD
	virtual void machine_start();
	virtual void machine_reset();
	virtual void video_start();
	DECLARE_PALETTE_INIT(1943);
	UINT32 screen_update_1943(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
=======
	virtual void machine_start() override;
	virtual void machine_reset() override;
	virtual void video_start() override;
	DECLARE_PALETTE_INIT(1943);
	uint32_t screen_update_1943(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
>>>>>>> upstream/master
	void draw_sprites( bitmap_ind16 &bitmap, const rectangle &cliprect, int priority );
};
