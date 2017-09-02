// license:BSD-3-Clause
// copyright-holders:Aaron Giles
/***************************************************************************

    The Game Room Lethal Justice hardware

***************************************************************************/

#include "emu.h"
<<<<<<< HEAD
#include "cpu/tms34010/tms34010.h"
=======
>>>>>>> upstream/master
#include "includes/lethalj.h"


#define BLITTER_SOURCE_WIDTH        1024
#define BLITTER_DEST_WIDTH          512
#define BLITTER_DEST_HEIGHT         512


/*************************************
 *
 *  Compute X/Y coordinates
 *
 *************************************/

inline void lethalj_state::get_crosshair_xy(int player, int *x, int *y)
{
	const rectangle &visarea = m_screen->visible_area();
	int width = visarea.width();
	int height = visarea.height();

	if (player)
	{
<<<<<<< HEAD
		*x = (((m_light1_x ? m_light1_x->read() : 0) & 0xff) * width) / 255;
		*y = (((m_light1_y ? m_light1_y->read() : 0) & 0xff) * height) / 255;
	}
	else
	{
		*x = (((m_light0_x ? m_light0_x->read() : 0) & 0xff) * width) / 255;
		*y = (((m_light0_y ? m_light0_y->read() : 0) & 0xff) * height) / 255;
=======
		*x = ((m_light1_x.read_safe(0) & 0xff) * width) / 255;
		*y = ((m_light1_y.read_safe(0) & 0xff) * height) / 255;
	}
	else
	{
		*x = ((m_light0_x.read_safe(0) & 0xff) * width) / 255;
		*y = ((m_light0_y.read_safe(0) & 0xff) * height) / 255;
>>>>>>> upstream/master
	}
}



/*************************************
 *
 *  Gun input handling
 *
 *************************************/

READ16_MEMBER(lethalj_state::lethalj_gun_r)
{
<<<<<<< HEAD
	UINT16 result = 0;
=======
	uint16_t result = 0;
>>>>>>> upstream/master
	int beamx, beamy;

	switch (offset)
	{
		case 4:
		case 5:
			/* latch the crosshair position */
			get_crosshair_xy(offset - 4, &beamx, &beamy);
			m_gunx = beamx;
			m_guny = beamy;
			m_blank_palette = 1;
			break;

		case 6:
			result = m_gunx / 2;
			break;

		case 7:
			result = m_guny + 4;
			break;
	}
/*  logerror("%08X:lethalj_gun_r(%d) = %04X\n", space.device().safe_pc(), offset, result); */
	return result;
}



/*************************************
 *
 *  video startup
 *
 *************************************/

void lethalj_state::video_start()
{
	/* allocate video RAM for screen */
<<<<<<< HEAD
	m_screenram = auto_alloc_array(machine(), UINT16, BLITTER_DEST_WIDTH * BLITTER_DEST_HEIGHT);

	/* predetermine blitter info */
	m_blitter_base = (UINT16 *)memregion("gfx1")->base();
	m_blitter_rows = memregion("gfx1")->bytes() / (2*BLITTER_SOURCE_WIDTH);
=======
	m_screenram = std::make_unique<uint16_t[]>(BLITTER_DEST_WIDTH * BLITTER_DEST_HEIGHT);

	/* predetermine blitter info */
	m_blitter_base = (uint16_t *)memregion("gfx1")->base();
	m_blitter_rows = memregion("gfx1")->bytes() / (2*BLITTER_SOURCE_WIDTH);

	m_gen_ext1_int_timer = timer_alloc(TIMER_GEN_EXT1_INT);
>>>>>>> upstream/master
}



/*************************************
 *
 *  Memory maps
 *
 *************************************/

void lethalj_state::device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr)
{
	switch (id)
	{
	case TIMER_GEN_EXT1_INT:
		m_maincpu->set_input_line(0, ASSERT_LINE);
		break;
	default:
<<<<<<< HEAD
		assert_always(FALSE, "Unknown id in lethalj_state::device_timer");
=======
		assert_always(false, "Unknown id in lethalj_state::device_timer");
>>>>>>> upstream/master
	}
}


void lethalj_state::do_blit()
{
<<<<<<< HEAD
	int dsty = (INT16)m_blitter_data[1];
	int srcx = (UINT16)m_blitter_data[2];
	int srcy = (UINT16)(m_blitter_data[3] + 1);
	int width = (UINT16)m_blitter_data[5];
	int dstx = (INT16)m_blitter_data[6];
	int height = (UINT16)m_blitter_data[7];
=======
	int dsty = (int16_t)m_blitter_data[1];
	int srcx = (uint16_t)m_blitter_data[2];
	int srcy = (uint16_t)(m_blitter_data[3] + 1);
	int width = (uint16_t)m_blitter_data[5];
	int dstx = (int16_t)m_blitter_data[6];
	int height = (uint16_t)m_blitter_data[7];
>>>>>>> upstream/master
	int y;
/*
    logerror("blitter data = %04X %04X %04X %04X %04X %04X %04X %04X\n",
            m_blitter_data[0], m_blitter_data[1], m_blitter_data[2], m_blitter_data[3],
            m_blitter_data[4], m_blitter_data[5], m_blitter_data[6], m_blitter_data[7]);
*/
	/* loop over Y coordinates */
	for (y = 0; y <= height; y++, srcy++, dsty++)
	{
		/* clip in Y */
		if (dsty >= 0 && dsty < BLITTER_DEST_HEIGHT/2)
		{
<<<<<<< HEAD
			UINT16 *source = m_blitter_base + (srcy % m_blitter_rows) * BLITTER_SOURCE_WIDTH;
			UINT16 *dest = m_screenram + (dsty + (m_vispage ^ 1) * 256) * BLITTER_DEST_WIDTH;
=======
			uint16_t *source = m_blitter_base + (srcy % m_blitter_rows) * BLITTER_SOURCE_WIDTH;
			uint16_t *dest = m_screenram.get() + (dsty + (m_vispage ^ 1) * 256) * BLITTER_DEST_WIDTH;
>>>>>>> upstream/master
			int sx = srcx;
			int dx = dstx;
			int x;

			/* loop over X coordinates */
			for (x = 0; x <= width; x++, sx++, dx++)
			{
				dx &= BLITTER_DEST_WIDTH -1 ;

				int pix = source[sx % BLITTER_SOURCE_WIDTH];
				if (pix)
					dest[dx] = pix;

			}
		}
	}
}


WRITE16_MEMBER(lethalj_state::lethalj_blitter_w)
{
	/* combine the data */
	COMBINE_DATA(&m_blitter_data[offset]);

	/* blit on a write to offset 7, and signal an IRQ */
	if (offset == 7)
	{
		if (m_blitter_data[6] == 2 && m_blitter_data[7] == 2)
			m_vispage ^= 1;
		else
			do_blit();

<<<<<<< HEAD
		timer_set(attotime::from_hz(XTAL_32MHz) * ((m_blitter_data[5] + 1) * (m_blitter_data[7] + 1)), TIMER_GEN_EXT1_INT);
=======
		m_gen_ext1_int_timer->adjust(attotime::from_hz(XTAL_32MHz) * ((m_blitter_data[5] + 1) * (m_blitter_data[7] + 1)));
>>>>>>> upstream/master
	}

	/* clear the IRQ on offset 0 */
	else if (offset == 0)
		m_maincpu->set_input_line(0, CLEAR_LINE);
}



/*************************************
 *
 *  video update
 *
 *************************************/

TMS340X0_SCANLINE_IND16_CB_MEMBER(lethalj_state::scanline_update)
{
<<<<<<< HEAD
	UINT16 *src = &m_screenram[(m_vispage << 17) | ((params->rowaddr << 9) & 0x3fe00)];
	UINT16 *dest = &bitmap.pix16(scanline);
=======
	uint16_t *src = &m_screenram[(m_vispage << 17) | ((params->rowaddr << 9) & 0x3fe00)];
	uint16_t *dest = &bitmap.pix16(scanline);
>>>>>>> upstream/master
	int coladdr = params->coladdr << 1;
	int x;

	/* blank palette: fill with white */
	if (m_blank_palette)
	{
		for (x = params->heblnk; x < params->hsblnk; x++)
			dest[x] = 0x7fff;
		if (scanline == screen.visible_area().max_y)
			m_blank_palette = 0;
		return;
	}

	/* copy the non-blanked portions of this scanline */
	for (x = params->heblnk; x < params->hsblnk; x++)
		dest[x] = src[coladdr++ & 0x1ff] & 0x7fff;
}
