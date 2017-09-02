// license:BSD-3-Clause
// copyright-holders:Pierpaolo Prazzoli
/*************************************************************************

    Ghosts'n Goblins

*************************************************************************/

<<<<<<< HEAD
=======
#include "sound/2203intf.h"
>>>>>>> upstream/master
#include "video/bufsprite.h"

class gng_state : public driver_device
{
public:
	gng_state(const machine_config &mconfig, device_type type, const char *tag)
		: driver_device(mconfig, type, tag),
			m_spriteram(*this, "spriteram") ,
		m_fgvideoram(*this, "fgvideoram"),
		m_bgvideoram(*this, "bgvideoram"),
		m_maincpu(*this, "maincpu"),
<<<<<<< HEAD
=======
		m_ym(*this, "ym%u", 1),
>>>>>>> upstream/master
		m_gfxdecode(*this, "gfxdecode"),
		m_palette(*this, "palette") { }

	/* memory pointers */
	required_device<buffered_spriteram8_device> m_spriteram;
<<<<<<< HEAD
	required_shared_ptr<UINT8> m_fgvideoram;
	required_shared_ptr<UINT8> m_bgvideoram;
=======
	required_shared_ptr<uint8_t> m_fgvideoram;
	required_shared_ptr<uint8_t> m_bgvideoram;
>>>>>>> upstream/master

	/* video-related */
	tilemap_t    *m_bg_tilemap;
	tilemap_t    *m_fg_tilemap;
<<<<<<< HEAD
	UINT8      m_scrollx[2];
	UINT8      m_scrolly[2];

	DECLARE_WRITE8_MEMBER(gng_bankswitch_w);
	DECLARE_WRITE8_MEMBER(gng_coin_counter_w);
=======
	uint8_t      m_scrollx[2];
	uint8_t      m_scrolly[2];

	DECLARE_WRITE8_MEMBER(gng_bankswitch_w);
	DECLARE_WRITE_LINE_MEMBER(coin_counter_1_w);
	DECLARE_WRITE_LINE_MEMBER(coin_counter_2_w);
	DECLARE_WRITE_LINE_MEMBER(ym_reset_w);
>>>>>>> upstream/master
	DECLARE_READ8_MEMBER(diamond_hack_r);
	DECLARE_WRITE8_MEMBER(gng_fgvideoram_w);
	DECLARE_WRITE8_MEMBER(gng_bgvideoram_w);
	DECLARE_WRITE8_MEMBER(gng_bgscrollx_w);
	DECLARE_WRITE8_MEMBER(gng_bgscrolly_w);
<<<<<<< HEAD
	DECLARE_WRITE8_MEMBER(gng_flipscreen_w);
	DECLARE_DRIVER_INIT(diamond);
	TILE_GET_INFO_MEMBER(get_fg_tile_info);
	TILE_GET_INFO_MEMBER(get_bg_tile_info);
	virtual void machine_start();
	virtual void machine_reset();
	virtual void video_start();
	UINT32 screen_update_gng(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
	void draw_sprites( bitmap_ind16 &bitmap, const rectangle &cliprect );
	required_device<cpu_device> m_maincpu;
=======
	DECLARE_WRITE_LINE_MEMBER(flipscreen_w);
	DECLARE_DRIVER_INIT(diamond);
	TILE_GET_INFO_MEMBER(get_fg_tile_info);
	TILE_GET_INFO_MEMBER(get_bg_tile_info);
	virtual void machine_start() override;
	virtual void machine_reset() override;
	virtual void video_start() override;
	uint32_t screen_update_gng(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
	void draw_sprites( bitmap_ind16 &bitmap, const rectangle &cliprect );
	required_device<cpu_device> m_maincpu;
	required_device_array<ym2203_device, 2> m_ym;
>>>>>>> upstream/master
	required_device<gfxdecode_device> m_gfxdecode;
	required_device<palette_device> m_palette;
};
