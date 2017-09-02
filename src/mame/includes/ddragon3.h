// license:BSD-3-Clause
// copyright-holders:Bryan McPhail, David Haywood
<<<<<<< HEAD
=======

>>>>>>> upstream/master
/*************************************************************************

    Double Dragon 3 & The Combatribes

*************************************************************************/
<<<<<<< HEAD
#include "sound/okim6295.h"
#include "video/bufsprite.h"
=======

#include "machine/gen_latch.h"
#include "sound/okim6295.h"
#include "video/bufsprite.h"
#include "screen.h"
>>>>>>> upstream/master


class ddragon3_state : public driver_device
{
public:
	ddragon3_state(const machine_config &mconfig, device_type type, const char *tag)
		: driver_device(mconfig, type, tag),
		m_bg_videoram(*this, "bg_videoram"),
		m_fg_videoram(*this, "fg_videoram"),
		m_spriteram(*this, "spriteram"),
		m_maincpu(*this, "maincpu"),
		m_audiocpu(*this, "audiocpu"),
		m_oki(*this, "oki"),
		m_gfxdecode(*this, "gfxdecode"),
		m_screen(*this, "screen"),
<<<<<<< HEAD
		m_palette(*this, "palette")

=======
		m_palette(*this, "palette"),
		m_soundlatch(*this, "soundlatch")
>>>>>>> upstream/master
	{
		vblank_level = 6;
		raster_level = 5;
	}

	/* memory pointers */
<<<<<<< HEAD
	required_shared_ptr<UINT16> m_bg_videoram;
	required_shared_ptr<UINT16> m_fg_videoram;
//  required_shared_ptr<UINT16> m_spriteram;
=======
	required_shared_ptr<uint16_t> m_bg_videoram;
	required_shared_ptr<uint16_t> m_fg_videoram;
//  required_shared_ptr<uint16_t> m_spriteram;
>>>>>>> upstream/master
	required_device<buffered_spriteram16_device> m_spriteram;

	/* video-related */
	tilemap_t         *m_fg_tilemap;
	tilemap_t         *m_bg_tilemap;
<<<<<<< HEAD
	UINT16          m_vreg;
	UINT16          m_bg_scrollx;
	UINT16          m_bg_scrolly;
	UINT16          m_fg_scrollx;
	UINT16          m_fg_scrolly;
	UINT16          m_bg_tilebase;

	UINT16 m_sprite_xoff;
	UINT16 m_bg0_dx;
	UINT16 m_bg1_dx[2];

	/* misc */
	UINT16          m_io_reg[8];
	UINT8 m_pri;
=======
	uint16_t          m_vreg;
	uint16_t          m_bg_scrollx;
	uint16_t          m_bg_scrolly;
	uint16_t          m_fg_scrollx;
	uint16_t          m_fg_scrolly;
	uint16_t          m_bg_tilebase;

	uint16_t m_sprite_xoff;
	uint16_t m_bg0_dx;
	uint16_t m_bg1_dx[2];

	/* misc */
	uint8_t m_pri;
>>>>>>> upstream/master

	/* devices */
	required_device<cpu_device> m_maincpu;
	required_device<cpu_device> m_audiocpu;
	required_device<okim6295_device> m_oki;
	required_device<gfxdecode_device> m_gfxdecode;
	required_device<screen_device> m_screen;
	required_device<palette_device> m_palette;
<<<<<<< HEAD

	DECLARE_WRITE16_MEMBER(ddragon3_io_w);
=======
	required_device<generic_latch_8_device> m_soundlatch;

	DECLARE_WRITE16_MEMBER(ddragon3_vreg_w);
	DECLARE_WRITE16_MEMBER(irq6_ack_w);
	DECLARE_WRITE16_MEMBER(irq5_ack_w);
>>>>>>> upstream/master
	DECLARE_WRITE16_MEMBER(ddragon3_scroll_w);
	DECLARE_READ16_MEMBER(ddragon3_scroll_r);
	DECLARE_WRITE16_MEMBER(ddragon3_bg_videoram_w);
	DECLARE_WRITE16_MEMBER(ddragon3_fg_videoram_w);
	DECLARE_WRITE8_MEMBER(oki_bankswitch_w);
	TILE_GET_INFO_MEMBER(get_bg_tile_info);
	TILE_GET_INFO_MEMBER(get_fg_tile_info);
<<<<<<< HEAD
	virtual void machine_start();
	virtual void machine_reset();
	virtual void video_start();
	UINT32 screen_update_ddragon3(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
	UINT32 screen_update_ctribe(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
=======
	virtual void machine_start() override;
	virtual void machine_reset() override;
	virtual void video_start() override;
	uint32_t screen_update_ddragon3(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
	uint32_t screen_update_ctribe(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
>>>>>>> upstream/master
	TIMER_DEVICE_CALLBACK_MEMBER(ddragon3_scanline);
	void draw_sprites(  bitmap_ind16 &bitmap, const rectangle &cliprect );

	int vblank_level;
	int raster_level;
};


class wwfwfest_state : public ddragon3_state
{
public:
	wwfwfest_state(const machine_config &mconfig, device_type type, const char *tag)
		: ddragon3_state(mconfig, type, tag),
		m_fg0_videoram(*this, "fg0_videoram"),
		m_paletteram(*this, "palette")
	{
		vblank_level = 3;
		raster_level = 2;
	}

	/* wwfwfest has an extra layer */
<<<<<<< HEAD
	required_shared_ptr<UINT16> m_fg0_videoram;
	required_shared_ptr<UINT16> m_paletteram;
=======
	required_shared_ptr<uint16_t> m_fg0_videoram;
	required_shared_ptr<uint16_t> m_paletteram;
>>>>>>> upstream/master
	tilemap_t *m_fg0_tilemap;
	DECLARE_WRITE16_MEMBER(wwfwfest_fg0_videoram_w);


	//required_device<buffered_spriteram16_device> m_spriteram;
	DECLARE_WRITE8_MEMBER(wwfwfest_priority_w);
<<<<<<< HEAD
	DECLARE_WRITE16_MEMBER(wwfwfest_scroll_write);
=======
>>>>>>> upstream/master
	DECLARE_WRITE16_MEMBER(wwfwfest_irq_ack_w);
	DECLARE_WRITE16_MEMBER(wwfwfest_flipscreen_w);
	DECLARE_READ16_MEMBER(wwfwfest_paletteram_r);
	DECLARE_WRITE16_MEMBER(wwfwfest_paletteram_w);
	DECLARE_WRITE16_MEMBER(wwfwfest_soundwrite);

	DECLARE_CUSTOM_INPUT_MEMBER(dsw_3f_r);
	DECLARE_CUSTOM_INPUT_MEMBER(dsw_c0_r);
	TILE_GET_INFO_MEMBER(get_fg0_tile_info);

<<<<<<< HEAD
	virtual void video_start();
	DECLARE_VIDEO_START(wwfwfstb);
	UINT32 screen_update_wwfwfest(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
=======
	virtual void video_start() override;
	DECLARE_VIDEO_START(wwfwfstb);
	uint32_t screen_update_wwfwfest(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
>>>>>>> upstream/master

};
