// license:BSD-3-Clause
// copyright-holders:Roberto Fresca
class gatron_state : public driver_device
{
public:
	gatron_state(const machine_config &mconfig, device_type type, const char *tag)
		: driver_device(mconfig, type, tag),
		m_videoram(*this, "videoram"),
		m_maincpu(*this, "maincpu"),
		m_gfxdecode(*this, "gfxdecode") { }

<<<<<<< HEAD
	required_shared_ptr<UINT8> m_videoram;
=======
	required_shared_ptr<uint8_t> m_videoram;
>>>>>>> upstream/master
	tilemap_t *m_bg_tilemap;
	DECLARE_WRITE8_MEMBER(output_port_0_w);
	DECLARE_WRITE8_MEMBER(gat_videoram_w);
	DECLARE_WRITE8_MEMBER(output_port_1_w);
	TILE_GET_INFO_MEMBER(get_bg_tile_info);
<<<<<<< HEAD
	virtual void video_start();
	DECLARE_PALETTE_INIT(gatron);
	UINT32 screen_update_gat(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
=======
	virtual void video_start() override;
	DECLARE_PALETTE_INIT(gatron);
	uint32_t screen_update_gat(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
>>>>>>> upstream/master
	required_device<cpu_device> m_maincpu;
	required_device<gfxdecode_device> m_gfxdecode;
};
