// license:BSD-3-Clause
// copyright-holders:Steve Ellenoff,Jarek Parchanski
/***************************************************************************
  Great Swordsman

  Functions to emulate the video hardware of the machine.

***************************************************************************/

#include "emu.h"
#include "includes/gsword.h"


<<<<<<< HEAD
PALETTE_INIT_MEMBER(gsword_state,josvolly)
{
	const UINT8 *color_prom = memregion("proms")->base();
	int i;

	/* create a lookup table for the palette */
	for (i = 0; i < 0x100; i++)
	{
		int r = pal4bit(color_prom[i + 0x000]);
		int g = pal4bit(color_prom[i + 0x100]);
		int b = pal4bit(color_prom[i + 0x200]);

		palette.set_indirect_color(i, rgb_t(r, g, b));
	}

	/* color_prom now points to the beginning of the lookup table */
	color_prom += 0x300;

	/* characters */
	for (i = 0; i < 0x100; i++)
		palette.set_pen_indirect(i, i);

	/* sprites */
	for (i = 0x100; i < 0x200; i++)
	{
		UINT8 ctabentry = (BITSWAP8(color_prom[i - 0x100],7,6,5,4,0,1,2,3) & 0x0f) | 0x80;
		palette.set_pen_indirect(i, ctabentry);
	}
}


PALETTE_INIT_MEMBER(gsword_state,gsword)
{
	const UINT8 *color_prom = memregion("proms")->base();
	int i;

	/* create a lookup table for the palette */
	for (i = 0; i < 0x100; i++)
	{
		int bit0, bit1, bit2;
		int r, g, b;

		/* red component */
		bit0 = (color_prom[i + 0x100] >> 0) & 1;
		bit1 = (color_prom[i + 0x100] >> 1) & 1;
		bit2 = (color_prom[i + 0x100] >> 2) & 1;
		r = 0x21 * bit0 + 0x47 * bit1 + 0x97 * bit2;

		/* green component */
		bit0 = (color_prom[i + 0x100] >> 3) & 1;
		bit1 = (color_prom[i + 0x000] >> 0) & 1;
		bit2 = (color_prom[i + 0x000] >> 1) & 1;
		g = 0x21 * bit0 + 0x47 * bit1 + 0x97 * bit2;

		/* blue component */
		bit0 = 0;
		bit1 = (color_prom[i + 0x000] >> 2) & 1;
		bit2 = (color_prom[i + 0x000] >> 3) & 1;
		b = 0x21 * bit0 + 0x47 * bit1 + 0x97 * bit2;

		palette.set_indirect_color(i, rgb_t(r, g, b));
	}

	/* color_prom now points to the beginning of the lookup table */
	color_prom += 0x200;

	/* characters */
	for (i = 0; i < 0x100; i++)
		palette.set_pen_indirect(i, i);

	/* sprites */
	for (i = 0x100; i < 0x200; i++)
	{
		UINT8 ctabentry = (BITSWAP8(color_prom[i - 0x100],7,6,5,4,0,1,2,3) & 0x0f) | 0x80;
		palette.set_pen_indirect(i, ctabentry);
	}
}

WRITE8_MEMBER(gsword_state::videoram_w)
=======
WRITE8_MEMBER(gsword_state_base::videoram_w)
>>>>>>> upstream/master
{
	m_videoram[offset] = data;
	m_bg_tilemap->mark_tile_dirty(offset);
}

<<<<<<< HEAD
WRITE8_MEMBER(gsword_state::charbank_w)
=======
WRITE8_MEMBER(gsword_state_base::charbank_w)
>>>>>>> upstream/master
{
	if (m_charbank != data)
	{
		m_charbank = data;
		machine().tilemap().mark_all_dirty();
	}
}

<<<<<<< HEAD
WRITE8_MEMBER(gsword_state::videoctrl_w)
=======
WRITE8_MEMBER(gsword_state_base::videoctrl_w)
>>>>>>> upstream/master
{
	if (data & 0x8f)
	{
		popmessage("videoctrl %02x",data);
	}

	/* bits 5-6 are char palette bank */

	if (m_charpalbank != ((data & 0x60) >> 5))
	{
		m_charpalbank = (data & 0x60) >> 5;
		machine().tilemap().mark_all_dirty();
	}

	/* bit 4 is flip screen */

	if (m_flipscreen != (data & 0x10))
	{
		m_flipscreen = data & 0x10;
		machine().tilemap().mark_all_dirty();
	}

	/* bit 0 could be used but unknown */

	/* other bits unused */
}

<<<<<<< HEAD
WRITE8_MEMBER(gsword_state::scroll_w)
=======
WRITE8_MEMBER(gsword_state_base::scroll_w)
>>>>>>> upstream/master
{
	m_bg_tilemap->set_scrolly(0, data);
}

<<<<<<< HEAD
TILE_GET_INFO_MEMBER(gsword_state::get_bg_tile_info)
=======
TILE_GET_INFO_MEMBER(gsword_state_base::get_bg_tile_info)
>>>>>>> upstream/master
{
	int code = m_videoram[tile_index] + ((m_charbank & 0x03) << 8);
	int color = ((code & 0x3c0) >> 6) + 16 * m_charpalbank;
	int flags = m_flipscreen ? (TILE_FLIPX | TILE_FLIPY) : 0;

	SET_TILE_INFO_MEMBER(0, code, color, flags);
}

<<<<<<< HEAD
void gsword_state::video_start()
{
	m_bg_tilemap = &machine().tilemap().create(m_gfxdecode, tilemap_get_info_delegate(FUNC(gsword_state::get_bg_tile_info),this), TILEMAP_SCAN_ROWS,
=======
void gsword_state_base::video_start()
{
	m_bg_tilemap = &machine().tilemap().create(*m_gfxdecode, tilemap_get_info_delegate(FUNC(gsword_state_base::get_bg_tile_info),this), TILEMAP_SCAN_ROWS,
>>>>>>> upstream/master
			8, 8, 32, 64);

	save_item(NAME(m_charbank));
	save_item(NAME(m_charpalbank));
	save_item(NAME(m_flipscreen));
}

<<<<<<< HEAD
void gsword_state::draw_sprites(bitmap_ind16 &bitmap, const rectangle &cliprect)
=======
void gsword_state_base::draw_sprites(bitmap_ind16 &bitmap, const rectangle &cliprect)
>>>>>>> upstream/master
{
	for (int offs = 0; offs < m_spritexy_ram.bytes() - 1; offs+=2)
	{
		int sx,sy,flipx,flipy,spritebank,tile,color;

		if (m_spritexy_ram[offs]!=0xf1)
		{
			spritebank = 0;
			tile = m_spritetile_ram[offs];
			color = m_spritetile_ram[offs+1] & 0x3f;
			sy = 241-m_spritexy_ram[offs];
			sx = m_spritexy_ram[offs+1]-56;
			flipx = m_spriteattrib_ram[offs] & 0x02;
			flipy = m_spriteattrib_ram[offs] & 0x01;

			// Adjust sprites that should be far far right!
			if (sx<0) sx+=256;

			// Adjuste for 32x32 tiles(#128-256)
			if (tile > 127)
			{
				spritebank = 1;
				tile -= 128;
				sy-=16;
			}
			if (m_flipscreen)
			{
				flipx = !flipx;
				flipy = !flipy;
			}
			m_gfxdecode->gfx(1+spritebank)->transmask(bitmap,cliprect,
					tile,
					color,
					flipx,flipy,
					sx,sy,
					m_palette->transpen_mask(*m_gfxdecode->gfx(1+spritebank), color, 0x8f));
		}
	}
}

<<<<<<< HEAD
UINT32 gsword_state::screen_update_gsword(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect)
=======
uint32_t gsword_state_base::screen_update_gsword(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect)
>>>>>>> upstream/master
{
	m_bg_tilemap->draw(screen, bitmap, cliprect, 0, 0);
	draw_sprites(bitmap, cliprect);
	return 0;
}
<<<<<<< HEAD
=======


PALETTE_INIT_MEMBER(gsword_state, gsword)
{
	const uint8_t *color_prom = memregion("proms")->base();

	/* create a lookup table for the palette */
	for (unsigned i = 0; i < 0x100; i++)
	{
		int bit0, bit1, bit2;
		int r, g, b;

		/* red component */
		bit0 = BIT(color_prom[i + 0x100], 0);
		bit1 = BIT(color_prom[i + 0x100], 1);
		bit2 = BIT(color_prom[i + 0x100], 2);
		r = 0x21 * bit0 + 0x47 * bit1 + 0x97 * bit2;

		/* green component */
		bit0 = BIT(color_prom[i + 0x100], 3);
		bit1 = BIT(color_prom[i + 0x000], 0);
		bit2 = BIT(color_prom[i + 0x000], 1);
		g = 0x21 * bit0 + 0x47 * bit1 + 0x97 * bit2;

		/* blue component */
		bit0 = 0;
		bit1 = BIT(color_prom[i + 0x000], 2);
		bit2 = BIT(color_prom[i + 0x000], 3);
		b = 0x21 * bit0 + 0x47 * bit1 + 0x97 * bit2;

		palette.set_indirect_color(i, rgb_t(r, g, b));
	}

	/* color_prom now points to the beginning of the lookup table */
	color_prom += 0x200;

	/* characters */
	for (unsigned i = 0; i < 0x100; i++)
		palette.set_pen_indirect(i, i);

	/* sprites */
	for (unsigned i = 0x100; i < 0x200; i++)
	{
		uint8_t ctabentry = (BITSWAP8(color_prom[i - 0x100],7,6,5,4,0,1,2,3) & 0x0f) | 0x80;
		palette.set_pen_indirect(i, ctabentry);
	}
}



PALETTE_INIT_MEMBER(josvolly_state, josvolly)
{
	u8 const *const color_prom = memregion("proms")->base();

	// create a lookup table for the palette
	for (unsigned i = 0; i < 0x100; i++)
	{
		u8 const r = pal4bit(color_prom[i + 0x000]);
		u8 const g = pal4bit(color_prom[i + 0x100]);
		u8 const b = pal4bit(color_prom[i + 0x200]);

		palette.set_indirect_color(i, rgb_t(r, g, b));

		// characters
		palette.set_pen_indirect(i, i);

		// sprites
		u8 const ctabentry = bitswap(color_prom[i + 0x300], 0, 1, 2, 3) | 0x80;
		palette.set_pen_indirect(i + 0x100, ctabentry);
	}
}
>>>>>>> upstream/master
