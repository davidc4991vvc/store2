// license:BSD-3-Clause
// copyright-holders:Uki
/******************************************************************************

Ikki (c) 1985 Sun Electronics

Video hardware driver by Uki

    20/Jun/2001 -

******************************************************************************/

#include "emu.h"
#include "includes/ikki.h"

PALETTE_INIT_MEMBER(ikki_state, ikki)
{
<<<<<<< HEAD
	const UINT8 *color_prom = memregion("proms")->base();
=======
	const uint8_t *color_prom = memregion("proms")->base();
>>>>>>> upstream/master
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

	/* sprites lookup table */
	for (i = 0; i < 0x200; i++)
	{
<<<<<<< HEAD
		UINT16 ctabentry = color_prom[i] ^ 0xff;
=======
		uint16_t ctabentry = color_prom[i] ^ 0xff;
>>>>>>> upstream/master

		if (((i & 0x07) == 0x07) && (ctabentry == 0))
		{
			/* punch through */
			m_punch_through_pen = i;
			ctabentry = 0x100;
		}

		palette.set_pen_indirect(i, ctabentry);
	}

	/* bg lookup table */
	for (i = 0x200; i < 0x400; i++)
	{
<<<<<<< HEAD
		UINT8 ctabentry = color_prom[i];
=======
		uint8_t ctabentry = color_prom[i];
>>>>>>> upstream/master
		palette.set_pen_indirect(i, ctabentry);
	}
}

WRITE8_MEMBER(ikki_state::ikki_scrn_ctrl_w)
{
	m_flipscreen = (data >> 2) & 1;
}


void ikki_state::draw_sprites( bitmap_ind16 &bitmap, const rectangle &cliprect )
{
<<<<<<< HEAD
	UINT8 *spriteram = m_spriteram;
=======
	uint8_t *spriteram = m_spriteram;
>>>>>>> upstream/master
	int y;
	offs_t offs;

	m_sprite_bitmap.fill(m_punch_through_pen, cliprect);

	for (offs = 0; offs < m_spriteram.bytes(); offs += 4)
	{
		int code = (spriteram[offs + 2] & 0x80) | (spriteram[offs + 1] >> 1);
		int color = spriteram[offs + 2] & 0x3f;

		int x = spriteram[offs + 3];
			y = spriteram[offs + 0];

		if (m_flipscreen)
			x = 240 - x;
		else
			y = 224 - y;

		x = x & 0xff;
		y = y & 0xff;

		if (x > 248)
			x = x - 256;

		if (y > 240)
			y = y - 256;

		m_gfxdecode->gfx(1)->transmask(m_sprite_bitmap,cliprect,
				code, color,
				m_flipscreen,m_flipscreen,
				x,y,
				m_palette->transpen_mask(*m_gfxdecode->gfx(1), color, 0));
	}

	/* copy the sprite bitmap into the main bitmap, skipping the transparent pixels */
	for (y = cliprect.min_y; y <= cliprect.max_y; y++)
	{
		int x;

		for (x = cliprect.min_x; x <= cliprect.max_x; x++)
		{
<<<<<<< HEAD
			UINT16 pen = m_sprite_bitmap.pix16(y, x);
=======
			uint16_t pen = m_sprite_bitmap.pix16(y, x);
>>>>>>> upstream/master

			if (m_palette->pen_indirect(pen) != 0x100)
				bitmap.pix16(y, x) = pen;
		}
	}
}


void ikki_state::video_start()
{
	m_screen->register_screen_bitmap(m_sprite_bitmap);
	save_item(NAME(m_sprite_bitmap));
}


<<<<<<< HEAD
UINT32 ikki_state::screen_update_ikki(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect)
{
	offs_t offs;
	UINT8 *VIDEOATTR = memregion("user1")->base();
=======
uint32_t ikki_state::screen_update_ikki(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect)
{
	offs_t offs;
	uint8_t *VIDEOATTR = memregion("user1")->base();
>>>>>>> upstream/master

	/* draw bg layer */

	for (offs = 0; offs < (m_videoram.bytes() / 2); offs++)
	{
		int color, bank;

		int sx = offs / 32;
		int sy = offs % 32;
		int y = sy*8;
		int x = sx*8;

		int d = VIDEOATTR[sx];

		switch (d)
		{
			case 0x02: /* scroll area */
				x = sx * 8 - m_scroll[1];
				if (x < 0)
					x += 8 * 22;
				y = (sy * 8 + ~m_scroll[0]) & 0xff;
				break;

			case 0x03: /* non-scroll area */
				break;

			case 0x00: /* sprite disable? */
				break;

			case 0x0d: /* sprite disable? */
				break;

			case 0x0b: /* non-scroll area (?) */
				break;

			case 0x0e: /* unknown */
				break;
		}

		if (m_flipscreen)
		{
			x = 248 - x;
			y = 248 - y;
		}

		color = m_videoram[offs * 2];
		bank = (color & 0xe0) << 3;
		color = ((color & 0x1f)<<0) | ((color & 0x80) >> 2);

		m_gfxdecode->gfx(0)->opaque(bitmap,cliprect,
			m_videoram[offs * 2 + 1] + bank,
			color,
			m_flipscreen,m_flipscreen,
			x,y);
	}

	draw_sprites(bitmap, cliprect);

	/* mask sprites */

	for (offs = 0; offs < (m_videoram.bytes() / 2); offs++)
	{
		int sx = offs / 32;
		int sy = offs % 32;

		int d = VIDEOATTR[sx];

		if ((d == 0) || (d == 0x0d))
		{
			int color, bank;

			int y = sy * 8;
			int x = sx * 8;

			if (m_flipscreen)
			{
				x = 248 - x;
				y = 248 - y;
			}

			color = m_videoram[offs * 2];
			bank = (color & 0xe0) << 3;
			color = ((color & 0x1f)<<0) | ((color & 0x80) >> 2);

			m_gfxdecode->gfx(0)->opaque(bitmap,cliprect,
				m_videoram[offs * 2 + 1] + bank,
				color,
				m_flipscreen,m_flipscreen,
				x,y);
		}
	}

	return 0;
}
