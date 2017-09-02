// license:BSD-3-Clause
// copyright-holders:Joseba Epalza
class speedbal_state : public driver_device
{
public:
	speedbal_state(const machine_config &mconfig, device_type type, const char *tag)
		: driver_device(mconfig, type, tag),
		m_maincpu(*this, "maincpu"),
		m_gfxdecode(*this, "gfxdecode"),
		m_palette(*this, "palette"),
		m_spriteram(*this, "spriteram"),
		m_background_videoram(*this, "bg_videoram"),
		m_foreground_videoram(*this, "fg_videoram")
	{ }

	required_device<cpu_device> m_maincpu;
	required_device<gfxdecode_device> m_gfxdecode;
	required_device<palette_device> m_palette;

<<<<<<< HEAD
	required_shared_ptr<UINT8> m_spriteram;
	required_shared_ptr<UINT8> m_background_videoram;
	required_shared_ptr<UINT8> m_foreground_videoram;

	bool m_leds_start;
	UINT32 m_leds_shiftreg;
=======
	required_shared_ptr<uint8_t> m_spriteram;
	required_shared_ptr<uint8_t> m_background_videoram;
	required_shared_ptr<uint8_t> m_foreground_videoram;

	bool m_leds_start;
	uint32_t m_leds_shiftreg;
>>>>>>> upstream/master
	tilemap_t *m_bg_tilemap;
	tilemap_t *m_fg_tilemap;

	DECLARE_DRIVER_INIT(speedbal);
	DECLARE_DRIVER_INIT(musicbal);
<<<<<<< HEAD
	virtual void machine_start();
	virtual void video_start();
=======
	virtual void machine_start() override;
	virtual void video_start() override;
>>>>>>> upstream/master

	DECLARE_WRITE8_MEMBER(coincounter_w);
	DECLARE_WRITE8_MEMBER(foreground_videoram_w);
	DECLARE_WRITE8_MEMBER(background_videoram_w);
	DECLARE_WRITE8_MEMBER(maincpu_50_w);
	DECLARE_WRITE8_MEMBER(leds_output_block);
	DECLARE_WRITE8_MEMBER(leds_start_block);
	DECLARE_WRITE8_MEMBER(leds_shift_bit);

	TILE_GET_INFO_MEMBER(get_tile_info_bg);
	TILE_GET_INFO_MEMBER(get_tile_info_fg);

<<<<<<< HEAD
	UINT32 screen_update(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
=======
	uint32_t screen_update(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
>>>>>>> upstream/master
	void draw_sprites(bitmap_ind16 &bitmap, const rectangle &cliprect);
};
