// license:BSD-3-Clause
// copyright-holders:Uki
/*************************************************************************

    Markham

*************************************************************************/

class markham_state : public driver_device
{
public:
	markham_state(const machine_config &mconfig, device_type type, const char *tag)
		: driver_device(mconfig, type, tag),
		m_spriteram(*this, "spriteram"),
		m_videoram(*this, "videoram"),
		m_xscroll(*this, "xscroll"),
		m_maincpu(*this, "maincpu"),
		m_gfxdecode(*this, "gfxdecode"),
		m_palette(*this, "palette") { }

	/* memory pointers */
<<<<<<< HEAD
	required_shared_ptr<UINT8> m_spriteram;
	required_shared_ptr<UINT8> m_videoram;
	required_shared_ptr<UINT8> m_xscroll;
=======
	required_shared_ptr<uint8_t> m_spriteram;
	required_shared_ptr<uint8_t> m_videoram;
	required_shared_ptr<uint8_t> m_xscroll;
>>>>>>> upstream/master

	/* video-related */
	tilemap_t  *m_bg_tilemap;
	DECLARE_READ8_MEMBER(markham_e004_r);
	DECLARE_WRITE8_MEMBER(markham_videoram_w);
	DECLARE_WRITE8_MEMBER(markham_flipscreen_w);
	TILE_GET_INFO_MEMBER(get_bg_tile_info);
<<<<<<< HEAD
	virtual void video_start();
	DECLARE_PALETTE_INIT(markham);
	UINT32 screen_update_markham(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
=======
	virtual void video_start() override;
	DECLARE_PALETTE_INIT(markham);
	uint32_t screen_update_markham(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
>>>>>>> upstream/master
	void draw_sprites( bitmap_ind16 &bitmap, const rectangle &cliprect );
	required_device<cpu_device> m_maincpu;
	required_device<gfxdecode_device> m_gfxdecode;
	required_device<palette_device> m_palette;
};
