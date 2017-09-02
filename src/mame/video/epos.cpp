// license:BSD-3-Clause
// copyright-holders:Zsolt Vasvari
/***************************************************************************

    Epos games

***************************************************************************/

#include "emu.h"
#include "includes/epos.h"

/***************************************************************************

  These games has one 32 byte palette PROM, connected to the RGB output this way:

  bit 7 -- 240 ohm resistor  -- RED
        -- 510 ohm resistor  -- RED
        -- 1  kohm resistor  -- RED
        -- 240 ohm resistor  -- GREEN
        -- 510 ohm resistor  -- GREEN
        -- 1  kohm resistor  -- GREEN
        -- 240 ohm resistor  -- BLUE
  bit 0 -- 510 ohm resistor  -- BLUE

***************************************************************************/

<<<<<<< HEAD
void epos_state::get_pens( pen_t *pens )
{
	offs_t i;
	const UINT8 *prom = memregion("proms")->base();
	int len = memregion("proms")->bytes();

	for (i = 0; i < len; i++)
	{
		int bit0, bit1, bit2, r, g, b;

		UINT8 data = prom[i];

		bit0 = (data >> 7) & 0x01;
		bit1 = (data >> 6) & 0x01;
		bit2 = (data >> 5) & 0x01;
		r = 0x92 * bit0 + 0x4a * bit1 + 0x23 * bit2;

		bit0 = (data >> 4) & 0x01;
		bit1 = (data >> 3) & 0x01;
		bit2 = (data >> 2) & 0x01;
		g = 0x92 * bit0 + 0x4a * bit1 + 0x23 * bit2;

		bit0 = (data >> 1) & 0x01;
		bit1 = (data >> 0) & 0x01;
		b = 0xad * bit0 + 0x52 * bit1;

		pens[i] = rgb_t(r, g, b);
	}
}


WRITE8_MEMBER(epos_state::epos_port_1_w)
=======
PALETTE_INIT_MEMBER(epos_state,epos)
{
	offs_t i;
	const uint8_t *color_prom = memregion("proms")->base();
	int len = memregion("proms")->bytes();

	for (i = 0; i < len; i++)
		set_pal_color(i, color_prom[i]);
}

void epos_state::set_pal_color( uint8_t offset, uint8_t data )
{
	int bit0, bit1, bit2, r, g, b;

	bit0 = (data >> 7) & 0x01;
	bit1 = (data >> 6) & 0x01;
	bit2 = (data >> 5) & 0x01;
	r = 0x92 * bit0 + 0x4a * bit1 + 0x23 * bit2;

	bit0 = (data >> 4) & 0x01;
	bit1 = (data >> 3) & 0x01;
	bit2 = (data >> 2) & 0x01;
	g = 0x92 * bit0 + 0x4a * bit1 + 0x23 * bit2;

	bit0 = (data >> 1) & 0x01;
	bit1 = (data >> 0) & 0x01;
	b = 0xad * bit0 + 0x52 * bit1;

	m_palette->set_pen_color(offset, rgb_t(r,g,b));
}

// later (tristar 9000) games uses a dynamic palette instead of prom
WRITE8_MEMBER(epos_state::dealer_pal_w)
{
	set_pal_color(offset,data);
}

WRITE8_MEMBER(epos_state::port_1_w)
>>>>>>> upstream/master
{
	/* D0 - start light #1
	   D1 - start light #2
	   D2 - coin counter
	   D3 - palette select
	   D4-D7 - unused
	 */

<<<<<<< HEAD
	set_led_status(machine(), 0, (data >> 0) & 0x01);
	set_led_status(machine(), 1, (data >> 1) & 0x01);

	coin_counter_w(machine(), 0, (data >> 2) & 0x01);

	m_palette = (data >> 3) & 0x01;
}


UINT32 epos_state::screen_update_epos(screen_device &screen, bitmap_rgb32 &bitmap, const rectangle &cliprect)
{
	pen_t pens[0x20];
	offs_t offs;

	get_pens(pens);

	for (offs = 0; offs < m_videoram.bytes(); offs++)
	{
		UINT8 data = m_videoram[offs];
=======
	output().set_led_value(0, (data >> 0) & 0x01);
	output().set_led_value(1, (data >> 1) & 0x01);

	machine().bookkeeping().coin_counter_w(0, (data >> 2) & 0x01);

	m_palette_bank = (data >> 3) & 0x01;
}


uint32_t epos_state::screen_update(screen_device &screen, bitmap_rgb32 &bitmap, const rectangle &cliprect)
{
	offs_t offs;

	for (offs = 0; offs < m_videoram.bytes(); offs++)
	{
		uint8_t data = m_videoram[offs];
>>>>>>> upstream/master

		int x = (offs % 136) * 2;
		int y = (offs / 136);

<<<<<<< HEAD
		bitmap.pix32(y, x + 0) = pens[(m_palette << 4) | (data & 0x0f)];
		bitmap.pix32(y, x + 1) = pens[(m_palette << 4) | (data >> 4)];
=======
		if (flip_screen())
		{
			bitmap.pix32(240 - y, 270 - x + 1) = m_palette->pen((m_palette_bank << 4) | (data & 0x0f));
			bitmap.pix32(240 - y, 270 - x + 0) = m_palette->pen((m_palette_bank << 4) | (data >> 4));
		}
		else
		{
			bitmap.pix32(y, x + 0) = m_palette->pen((m_palette_bank << 4) | (data & 0x0f));
			bitmap.pix32(y, x + 1) = m_palette->pen((m_palette_bank << 4) | (data >> 4));
		}
>>>>>>> upstream/master
	}

	return 0;
}
