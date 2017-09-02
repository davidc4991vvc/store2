// license:BSD-3-Clause
// copyright-holders:Zsolt Vasvari
class marineb_state : public driver_device
{
public:
	marineb_state(const machine_config &mconfig, device_type type, const char *tag)
		: driver_device(mconfig, type, tag),
		m_videoram(*this, "videoram"),
		m_spriteram(*this, "spriteram"),
		m_colorram(*this, "colorram"),
		m_maincpu(*this, "maincpu"),
		m_audiocpu(*this, "audiocpu"),
		m_gfxdecode(*this, "gfxdecode"),
		m_palette(*this, "palette") { }

<<<<<<< HEAD
	required_shared_ptr<UINT8> m_videoram;
	required_shared_ptr<UINT8> m_spriteram;
	required_shared_ptr<UINT8> m_colorram;
=======
	required_shared_ptr<uint8_t> m_videoram;
	required_shared_ptr<uint8_t> m_spriteram;
	required_shared_ptr<uint8_t> m_colorram;
>>>>>>> upstream/master

	/* video-related */
	tilemap_t   *m_bg_tilemap;
	tilemap_t   *m_fg_tilemap;
<<<<<<< HEAD
	UINT8     m_palette_bank;
	UINT8     m_column_scroll;
	UINT8     m_flipscreen_x;
	UINT8     m_flipscreen_y;
	UINT8     m_marineb_active_low_flipscreen;
=======
	uint8_t     m_palette_bank;
	uint8_t     m_column_scroll;
	uint8_t     m_flipscreen_x;
	uint8_t     m_flipscreen_y;
>>>>>>> upstream/master

	/* devices */
	required_device<cpu_device> m_maincpu;
	optional_device<cpu_device> m_audiocpu;
	required_device<gfxdecode_device> m_gfxdecode;
	required_device<palette_device> m_palette;

<<<<<<< HEAD
	UINT8     m_irq_mask;
	DECLARE_WRITE8_MEMBER(irq_mask_w);
=======
	uint8_t     m_irq_mask;
	DECLARE_WRITE_LINE_MEMBER(irq_mask_w);
>>>>>>> upstream/master
	DECLARE_WRITE8_MEMBER(marineb_videoram_w);
	DECLARE_WRITE8_MEMBER(marineb_colorram_w);
	DECLARE_WRITE8_MEMBER(marineb_column_scroll_w);
	DECLARE_WRITE8_MEMBER(marineb_palette_bank_0_w);
	DECLARE_WRITE8_MEMBER(marineb_palette_bank_1_w);
<<<<<<< HEAD
	DECLARE_WRITE8_MEMBER(marineb_flipscreen_x_w);
	DECLARE_WRITE8_MEMBER(marineb_flipscreen_y_w);
	TILE_GET_INFO_MEMBER(get_tile_info);
	virtual void machine_start();
	virtual void machine_reset();
	virtual void video_start();
	DECLARE_PALETTE_INIT(marineb);
	DECLARE_MACHINE_RESET(springer);
	UINT32 screen_update_marineb(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
	UINT32 screen_update_changes(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
	UINT32 screen_update_springer(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
	UINT32 screen_update_hoccer(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
	UINT32 screen_update_hopprobo(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
=======
	DECLARE_WRITE_LINE_MEMBER(flipscreen_x_w);
	DECLARE_WRITE_LINE_MEMBER(flipscreen_y_w);
	TILE_GET_INFO_MEMBER(get_tile_info);
	virtual void machine_start() override;
	virtual void machine_reset() override;
	virtual void video_start() override;
	DECLARE_PALETTE_INIT(marineb);
	uint32_t screen_update_marineb(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
	uint32_t screen_update_changes(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
	uint32_t screen_update_springer(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
	uint32_t screen_update_hoccer(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
	uint32_t screen_update_hopprobo(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
>>>>>>> upstream/master
	INTERRUPT_GEN_MEMBER(marineb_vblank_irq);
	INTERRUPT_GEN_MEMBER(wanted_vblank_irq);
	void set_tilemap_scrolly( int cols );
};
