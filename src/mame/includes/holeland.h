// license:BSD-3-Clause
// copyright-holders:Mathis Rosenhauer
/*************************************************************************

    Hole Land

*************************************************************************/

<<<<<<< HEAD
=======
#include "machine/74259.h"

>>>>>>> upstream/master
class holeland_state : public driver_device
{
public:
	holeland_state(const machine_config &mconfig, device_type type, const char *tag)
		: driver_device(mconfig, type, tag),
<<<<<<< HEAD
		m_videoram(*this, "videoram"),
		m_colorram(*this, "colorram"),
		m_spriteram(*this, "spriteram"),
		m_maincpu(*this, "maincpu"),
		m_gfxdecode(*this, "gfxdecode"),
		m_palette(*this, "palette") { }

	/* memory pointers */
	required_shared_ptr<UINT8> m_videoram;
	required_shared_ptr<UINT8> m_colorram;
	required_shared_ptr<UINT8> m_spriteram;
=======
		m_maincpu(*this, "maincpu"),
		m_gfxdecode(*this, "gfxdecode"),
		m_palette(*this, "palette"),
		m_latch(*this, "latch"),
		m_videoram(*this, "videoram"),
		m_colorram(*this, "colorram"),
		m_spriteram(*this, "spriteram") { }


	/* devices */
	required_device<cpu_device> m_maincpu;
	required_device<gfxdecode_device> m_gfxdecode;
	required_device<palette_device> m_palette;
	required_device<ls259_device> m_latch;

	/* memory pointers */
	required_shared_ptr<uint8_t> m_videoram;
	required_shared_ptr<uint8_t> m_colorram;
	required_shared_ptr<uint8_t> m_spriteram;
>>>>>>> upstream/master

	/* video-related */
	tilemap_t    *m_bg_tilemap;
	int        m_palette_offset;
<<<<<<< HEAD
	int        m_po[2];
	DECLARE_WRITE8_MEMBER(holeland_videoram_w);
	DECLARE_WRITE8_MEMBER(holeland_colorram_w);
	DECLARE_WRITE8_MEMBER(holeland_pal_offs_w);
	DECLARE_WRITE8_MEMBER(holeland_scroll_w);
	DECLARE_WRITE8_MEMBER(holeland_flipscreen_w);
	TILE_GET_INFO_MEMBER(holeland_get_tile_info);
	TILE_GET_INFO_MEMBER(crzrally_get_tile_info);
	DECLARE_VIDEO_START(holeland);
	DECLARE_VIDEO_START(crzrally);
	UINT32 screen_update_holeland(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
	UINT32 screen_update_crzrally(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
	void holeland_draw_sprites( bitmap_ind16 &bitmap, const rectangle &cliprect );
	void crzrally_draw_sprites( bitmap_ind16 &bitmap,const rectangle &cliprect );
	required_device<cpu_device> m_maincpu;
	required_device<gfxdecode_device> m_gfxdecode;
	required_device<palette_device> m_palette;
=======

	DECLARE_WRITE_LINE_MEMBER(coin_counter_w);

	DECLARE_WRITE8_MEMBER(videoram_w);
	DECLARE_WRITE8_MEMBER(colorram_w);
	DECLARE_WRITE8_MEMBER(pal_offs_w);
	DECLARE_WRITE8_MEMBER(scroll_w);
	DECLARE_WRITE_LINE_MEMBER(flipscreen_x_w);
	DECLARE_WRITE_LINE_MEMBER(flipscreen_y_w);

	TILE_GET_INFO_MEMBER(holeland_get_tile_info);
	TILE_GET_INFO_MEMBER(crzrally_get_tile_info);

	DECLARE_VIDEO_START(holeland);
	DECLARE_VIDEO_START(crzrally);

	uint32_t screen_update_holeland(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
	uint32_t screen_update_crzrally(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
	void holeland_draw_sprites( bitmap_ind16 &bitmap, const rectangle &cliprect );
	void crzrally_draw_sprites( bitmap_ind16 &bitmap,const rectangle &cliprect );
>>>>>>> upstream/master
};
