// license:BSD-3-Clause
// copyright-holders:Mirko Buffoni
/*************************************************************************

    Bomb Jack

*************************************************************************/

class bombjack_state : public driver_device
{
public:
	bombjack_state(const machine_config &mconfig, device_type type, const char *tag)
		: driver_device(mconfig, type, tag),
		m_videoram(*this, "videoram"),
		m_colorram(*this, "colorram"),
		m_spriteram(*this, "spriteram"),
		m_maincpu(*this, "maincpu"),
		m_gfxdecode(*this, "gfxdecode"),
		m_palette(*this, "palette") { }

	/* memory pointers */
<<<<<<< HEAD
	required_shared_ptr<UINT8> m_videoram;
	required_shared_ptr<UINT8> m_colorram;
	required_shared_ptr<UINT8> m_spriteram;
=======
	required_shared_ptr<uint8_t> m_videoram;
	required_shared_ptr<uint8_t> m_colorram;
	required_shared_ptr<uint8_t> m_spriteram;
>>>>>>> upstream/master

	/* video-related */
	tilemap_t   *m_fg_tilemap;
	tilemap_t   *m_bg_tilemap;
<<<<<<< HEAD
	UINT8       m_background_image;

	/* sound-related */
	UINT8       m_latch;

	UINT8       m_nmi_mask;
=======
	uint8_t       m_background_image;

	/* sound-related */
	uint8_t       m_latch;

	uint8_t       m_nmi_mask;
>>>>>>> upstream/master
	DECLARE_WRITE8_MEMBER(bombjack_soundlatch_w);
	DECLARE_READ8_MEMBER(bombjack_soundlatch_r);
	DECLARE_WRITE8_MEMBER(irq_mask_w);
	DECLARE_WRITE8_MEMBER(bombjack_videoram_w);
	DECLARE_WRITE8_MEMBER(bombjack_colorram_w);
	DECLARE_WRITE8_MEMBER(bombjack_background_w);
	DECLARE_WRITE8_MEMBER(bombjack_flipscreen_w);
	TILE_GET_INFO_MEMBER(get_bg_tile_info);
	TILE_GET_INFO_MEMBER(get_fg_tile_info);
<<<<<<< HEAD
	virtual void machine_start();
	virtual void machine_reset();
	virtual void video_start();
	UINT32 screen_update_bombjack(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
=======
	virtual void machine_start() override;
	virtual void machine_reset() override;
	virtual void video_start() override;
	uint32_t screen_update_bombjack(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
>>>>>>> upstream/master
	INTERRUPT_GEN_MEMBER(vblank_irq);
	TIMER_CALLBACK_MEMBER(soundlatch_callback);
	void draw_sprites( bitmap_ind16 &bitmap, const rectangle &cliprect );
	required_device<cpu_device> m_maincpu;
	required_device<gfxdecode_device> m_gfxdecode;
	required_device<palette_device> m_palette;
};
