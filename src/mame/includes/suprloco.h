// license:BSD-3-Clause
// copyright-holders:Zsolt Vasvari
<<<<<<< HEAD
=======

#include "machine/i8255.h"

>>>>>>> upstream/master
class suprloco_state : public driver_device
{
public:
	suprloco_state(const machine_config &mconfig, device_type type, const char *tag)
		: driver_device(mconfig, type, tag),
		m_maincpu(*this, "maincpu"),
		m_audiocpu(*this, "audiocpu"),
		m_gfxdecode(*this, "gfxdecode"),
<<<<<<< HEAD
=======
		m_ppi(*this, "ppi"),
>>>>>>> upstream/master
		m_spriteram(*this, "spriteram"),
		m_videoram(*this, "videoram"),
		m_scrollram(*this, "scrollram"),
		m_decrypted_opcodes(*this, "decrypted_opcodes") { }

	required_device<cpu_device> m_maincpu;
	required_device<cpu_device> m_audiocpu;
	required_device<gfxdecode_device> m_gfxdecode;
<<<<<<< HEAD

	required_shared_ptr<UINT8> m_spriteram;
	required_shared_ptr<UINT8> m_videoram;
	required_shared_ptr<UINT8> m_scrollram;
	required_shared_ptr<UINT8> m_decrypted_opcodes;
=======
	required_device<i8255_device> m_ppi;

	required_shared_ptr<uint8_t> m_spriteram;
	required_shared_ptr<uint8_t> m_videoram;
	required_shared_ptr<uint8_t> m_scrollram;
	required_shared_ptr<uint8_t> m_decrypted_opcodes;
>>>>>>> upstream/master

	tilemap_t *m_bg_tilemap;
	int m_control;

<<<<<<< HEAD
	DECLARE_WRITE8_MEMBER(soundport_w);
	DECLARE_WRITE8_MEMBER(videoram_w);
	DECLARE_WRITE8_MEMBER(scrollram_w);
	DECLARE_WRITE8_MEMBER(control_w);
	DECLARE_READ8_MEMBER(control_r);

	TILE_GET_INFO_MEMBER(get_tile_info);

	virtual void video_start();
	DECLARE_PALETTE_INIT(suprloco);
	DECLARE_DRIVER_INIT(suprloco);

	UINT32 screen_update(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
=======
	DECLARE_READ8_MEMBER(soundport_r);
	DECLARE_WRITE8_MEMBER(videoram_w);
	DECLARE_WRITE8_MEMBER(scrollram_w);
	DECLARE_WRITE8_MEMBER(control_w);
	DECLARE_WRITE_LINE_MEMBER(pc0_w);

	TILE_GET_INFO_MEMBER(get_tile_info);

	virtual void video_start() override;
	DECLARE_PALETTE_INIT(suprloco);
	DECLARE_DRIVER_INIT(suprloco);

	uint32_t screen_update(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
>>>>>>> upstream/master
	inline void draw_pixel(bitmap_ind16 &bitmap,const rectangle &cliprect,int x,int y,int color,int flip);
	void draw_sprite(bitmap_ind16 &bitmap,const rectangle &cliprect,int spr_number);
	void draw_sprites(bitmap_ind16 &bitmap, const rectangle &cliprect);
};
