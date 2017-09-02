// license:BSD-3-Clause
// copyright-holders:Nicola Salmoria
/*************************************************************************

    Gun Dealer

*************************************************************************/

class gundealr_state : public driver_device
{
public:
	gundealr_state(const machine_config &mconfig, device_type type, const char *tag)
		: driver_device(mconfig, type, tag),
		m_paletteram(*this, "paletteram"),
		m_bg_videoram(*this, "bg_videoram"),
		m_fg_videoram(*this, "fg_videoram"),
		m_rambase(*this, "rambase"),
		m_maincpu(*this, "maincpu"),
		m_gfxdecode(*this, "gfxdecode"),
		m_palette(*this, "palette") { }

	/* memory pointers */
<<<<<<< HEAD
	required_shared_ptr<UINT8> m_paletteram;
	required_shared_ptr<UINT8> m_bg_videoram;
	required_shared_ptr<UINT8> m_fg_videoram;
	required_shared_ptr<UINT8> m_rambase;
=======
	required_shared_ptr<uint8_t> m_paletteram;
	required_shared_ptr<uint8_t> m_bg_videoram;
	required_shared_ptr<uint8_t> m_fg_videoram;
	required_shared_ptr<uint8_t> m_rambase;
>>>>>>> upstream/master

	/* video-related */
	tilemap_t    *m_bg_tilemap;
	tilemap_t    *m_fg_tilemap;
<<<<<<< HEAD
	int        m_flipscreen;
	UINT8      m_scroll[4];
=======
	uint8_t      m_scroll[4];
>>>>>>> upstream/master

	/* misc */
	int        m_input_ports_hack;
	DECLARE_WRITE8_MEMBER(yamyam_bankswitch_w);
	DECLARE_WRITE8_MEMBER(gundealr_bg_videoram_w);
	DECLARE_WRITE8_MEMBER(gundealr_fg_videoram_w);
	DECLARE_WRITE8_MEMBER(gundealr_paletteram_w);
	DECLARE_WRITE8_MEMBER(gundealr_fg_scroll_w);
	DECLARE_WRITE8_MEMBER(yamyam_fg_scroll_w);
	DECLARE_WRITE8_MEMBER(gundealr_flipscreen_w);
<<<<<<< HEAD
	TILE_GET_INFO_MEMBER(get_bg_tile_info);
	TILEMAP_MAPPER_MEMBER(gundealr_scan);
	TILE_GET_INFO_MEMBER(get_fg_tile_info);
	virtual void machine_start();
	virtual void machine_reset();
	virtual void video_start();
	UINT32 screen_update_gundealr(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
=======
	DECLARE_WRITE8_MEMBER(yamyam_flipscreen_w);
	TILE_GET_INFO_MEMBER(get_bg_tile_info);
	TILEMAP_MAPPER_MEMBER(gundealr_scan);
	TILE_GET_INFO_MEMBER(get_fg_tile_info);
	virtual void machine_start() override;
	virtual void machine_reset() override;
	virtual void video_start() override;
	uint32_t screen_update_gundealr(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
>>>>>>> upstream/master
	TIMER_DEVICE_CALLBACK_MEMBER(gundealr_scanline);
	TIMER_DEVICE_CALLBACK_MEMBER(yamyam_mcu_sim);
	required_device<cpu_device> m_maincpu;
	required_device<gfxdecode_device> m_gfxdecode;
	required_device<palette_device> m_palette;
};
