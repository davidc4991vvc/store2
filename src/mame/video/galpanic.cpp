// license:BSD-3-Clause
// copyright-holders:Nicola Salmoria
#include "emu.h"
#include "kan_pand.h"
#include "includes/galpanic.h"


<<<<<<< HEAD
VIDEO_START_MEMBER(galpanic_state,galpanic)
{
	m_screen->register_screen_bitmap(m_bitmap);
=======
void galpanic_state::video_start()
{
	m_screen->register_screen_bitmap(m_bitmap);

	save_item(NAME(m_bitmap));
>>>>>>> upstream/master
}

PALETTE_INIT_MEMBER(galpanic_state,galpanic)
{
<<<<<<< HEAD
	int i;

	/* first 1024 colors are dynamic */

	/* initialize 555 RGB lookup */
	for (i = 0;i < 32768;i++)
		palette.set_pen_color(i+1024,pal5bit(i >> 5),pal5bit(i >> 10),pal5bit(i >> 0));
}

WRITE16_MEMBER(galpanic_state::galpanic_bgvideoram_w)
{
	int sx,sy;


	data = COMBINE_DATA(&m_bgvideoram[offset]);

	sy = offset / 256;
	sx = offset % 256;
=======
	/* first 1024 colors are dynamic */

	/* initialize 555 RGB lookup */
	for (int i = 0;i < 32768;i++)
		palette.set_pen_color(i+1024,pal5bit(i >> 5),pal5bit(i >> 10),pal5bit(i >> 0));
}

WRITE16_MEMBER(galpanic_state::bgvideoram_w)
{
	data = COMBINE_DATA(&m_bgvideoram[offset]);

	int sy = offset / 256;
	int sx = offset % 256;
>>>>>>> upstream/master

	m_bitmap.pix16(sy, sx) = 1024 + (data >> 1);
}

void galpanic_state::draw_fgbitmap(bitmap_ind16 &bitmap, const rectangle &cliprect)
{
<<<<<<< HEAD
	int offs;

	for (offs = 0;offs < m_fgvideoram.bytes()/2;offs++)
	{
		int sx,sy,color;

		sx = offs % 256;
		sy = offs / 256;
		color = m_fgvideoram[offs];
=======
	for (int offs = 0;offs < m_fgvideoram.bytes()/2;offs++)
	{
		int sx = offs % 256;
		int sy = offs / 256;
		int color = m_fgvideoram[offs];
>>>>>>> upstream/master
		if (color)
			bitmap.pix16(sy, sx) = color;
	}
}

<<<<<<< HEAD
UINT32 galpanic_state::screen_update_galpanic(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect)
=======
uint32_t galpanic_state::screen_update(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect)
>>>>>>> upstream/master
{
	/* copy the temporary bitmap to the screen */
	copybitmap(bitmap,m_bitmap,0,0,0,0,cliprect);

	draw_fgbitmap(bitmap, cliprect);

	m_pandora->update(bitmap, cliprect);

	return 0;
}
