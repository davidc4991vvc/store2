// license:BSD-3-Clause
// copyright-holders:Allard van der Bas
class vastar_state : public driver_device
{
public:
	vastar_state(const machine_config &mconfig, device_type type, const char *tag)
		: driver_device(mconfig, type, tag),
		m_maincpu(*this, "maincpu"),
		m_subcpu(*this, "sub"),
		m_gfxdecode(*this, "gfxdecode"),
		m_palette(*this, "palette"),
		m_bg1videoram(*this, "bg1videoram"),
		m_bg2videoram(*this, "bg2videoram"),
		m_fgvideoram(*this, "fgvideoram"),
		m_sprite_priority(*this, "sprite_priority"),
		m_sharedram(*this, "sharedram") { }

	required_device<cpu_device> m_maincpu;
	required_device<cpu_device> m_subcpu;
	required_device<gfxdecode_device> m_gfxdecode;
	required_device<palette_device> m_palette;

<<<<<<< HEAD
	required_shared_ptr<UINT8> m_bg1videoram;
	required_shared_ptr<UINT8> m_bg2videoram;
	required_shared_ptr<UINT8> m_fgvideoram;
	required_shared_ptr<UINT8> m_sprite_priority;
	required_shared_ptr<UINT8> m_sharedram;

	// these are pointers into m_fgvideoram
	UINT8* m_bg1_scroll;
	UINT8* m_bg2_scroll;
	UINT8* m_spriteram1;
	UINT8* m_spriteram2;
	UINT8* m_spriteram3;
=======
	required_shared_ptr<uint8_t> m_bg1videoram;
	required_shared_ptr<uint8_t> m_bg2videoram;
	required_shared_ptr<uint8_t> m_fgvideoram;
	required_shared_ptr<uint8_t> m_sprite_priority;
	required_shared_ptr<uint8_t> m_sharedram;

	// these are pointers into m_fgvideoram
	uint8_t* m_bg1_scroll;
	uint8_t* m_bg2_scroll;
	uint8_t* m_spriteram1;
	uint8_t* m_spriteram2;
	uint8_t* m_spriteram3;
>>>>>>> upstream/master

	tilemap_t *m_fg_tilemap;
	tilemap_t *m_bg1_tilemap;
	tilemap_t *m_bg2_tilemap;
<<<<<<< HEAD
	UINT8 m_nmi_mask;

	DECLARE_WRITE8_MEMBER(hold_cpu2_w);
	DECLARE_WRITE8_MEMBER(flip_screen_w);
	DECLARE_WRITE8_MEMBER(nmi_mask_w);
=======
	uint8_t m_nmi_mask;

	DECLARE_WRITE_LINE_MEMBER(flip_screen_w);
	DECLARE_WRITE_LINE_MEMBER(nmi_mask_w);
>>>>>>> upstream/master
	DECLARE_WRITE8_MEMBER(fgvideoram_w);
	DECLARE_WRITE8_MEMBER(bg1videoram_w);
	DECLARE_WRITE8_MEMBER(bg2videoram_w);

	TILE_GET_INFO_MEMBER(get_fg_tile_info);
	TILE_GET_INFO_MEMBER(get_bg1_tile_info);
	TILE_GET_INFO_MEMBER(get_bg2_tile_info);

<<<<<<< HEAD
	virtual void machine_start();
	virtual void machine_reset();
	virtual void video_start();

	UINT32 screen_update(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
=======
	virtual void machine_start() override;
	virtual void machine_reset() override;
	virtual void video_start() override;

	uint32_t screen_update(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
>>>>>>> upstream/master
	void draw_sprites(bitmap_ind16 &bitmap,const rectangle &cliprect);

	INTERRUPT_GEN_MEMBER(vblank_irq);
};
