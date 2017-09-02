// license:BSD-3-Clause
<<<<<<< HEAD
// copyright-holders:Mariusz Wojcieszek, Peter Trauner
/**********************************************************************

    Signetics 2636 video chip

    PVI REGISTER DESCRIPTION
    ------------------------
=======
// copyright-holders:Vas Crabb
/**********************************************************************

    Signetics 2636 Programmable Video Interface

    This emulation is pretty low-level.  For the most part it models
    the kinds of counters and flags you'd use if you were actually
    implementing it in programmable logic or on silicon.  I'm sure
    there are potential performance improvements in the drawing and
    collision detection code.

    At present the entire internal space of 256 bytes can be read and
    written.  This isn't accurate as some registers are read- or write-
    only, and there are several unused blocks in the address range.  We
    should be returning some fixed value on attempt to read unreadable
    locations.

    This implementation really needs proper display timing information
    information to work properly.  Audio pitch will be wrong if the
    screen's scan time is inaccurate.  Positioning objects depends on
    the screen's visible area representing the pixel clock periods
    periods between blanking pulses.  You also need to call the line
    rendering function at appropriate times if something expects to see
    collision or completion flags.

    The crude "offset" system for adjusting the position of the image
    has been maintained, but it's clearly inadequate for what games are
    doing with it, and it will inevitably lead to bugs.  If an object
    is positioned outside the visible area using the offset mechanism,
    it won't be displayed and neither will its duplicates.

    If what's happening in the games right now is correct, the hardware
    must  be feeding something other than the actual vertical and
    horizontal blanking signals to the S2623(s) so they start drawing
    inside the blanking region and have advanced to the desired
    location on reaching the visible area.  Implementing this properly
    would require decoupling the S2623 from the screen and giving it
    some other means to determine when it believes the blanking periods
    begin and end.

    Sorry, analog input isn't currently supported, and neither is
    interrupt request/acknowledge.  I have't got to them yet, and I'm
    still not sure whether reading a status register clears a pending
    interrupt.  The address decoding features still aren't implemented
    but they'd be pretty hard to fit in the MAME framework.


    ADDRESS MAP
    -----------
    start   end     description
    F00     F0D     object descriptor 1
    F0E     F0F     2 bytes scratch
    F10     F1D     object descriptor 2
    F1E     F1F     2 bytes scratch
    F20     F2D     object descriptor 3
    F2E     F3F     -
    F40     F4D     object descriptor 4
    F4E     F6D     32 bytes scratch
    F6E     F7F     -
    F80     FA7     background vertical bar definition
    FA8     FAC     background horizontal bar definition
    FAD     FAD     1 byte scratch
    FAE     FBF     -
    FC0     FCF     I/O and control
    FD0     FDF     I/O and control (mirror)
    FE0     FEF     I/O and control (mirror)
    FF0     FFF     I/O and control (mirror)


    OBJECT DESCRIPTOR
    -----------------
    0   9   basic shape of object (10 lines of 8 horizontal clocks)
    A   A   horizontal coordinate of object (HC)
    B   B   horizontal coordinate of duplicates (HCB)
    C   C   vertical coordinate of object (VC)
    D   D   vertical offset of duplicates (VCB)


    I/O AND CONTROL
    ---------------
>>>>>>> upstream/master

          |              bit              |R/W| description
    byte  | 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 |   |
          |                               |   |
<<<<<<< HEAD
    FC0   | size 4| size 3| size 2| size 1| W | size of the 4 objects(=sprites)
          |                               |   |
    FC1   |       |C1 |C2 |C3 |C1 |C2 |C3 | W | colors of the 4 objects
=======
    FC0   | size 4| size 3| size 2| size 1| W | size of 4 objects (scale 2^x)
          |                               |   |
    FC1   |       |C1 |C2 |C3 |C1 |C2 |C3 | W | colors of 4 objects
>>>>>>> upstream/master
          |       |  color 1  |  color 2  |   |
    FC2   |       |C1 |C2 |C3 |C1 |C2 |C3 | W |
          |       |  color 3  |  color 4  |   |
          |                               |   |
<<<<<<< HEAD
    FC3   |                       |sh |pos| W | 1=shape 0=position
          |                               |   | display format and position
    FC4   |            (free)             |   |
    FC5   |            (free)             |   |
          |                               |   |
    FC6   |   |C1 |C2 |C3 |BG |scrn colr  | W | background lock and color
          |   |backg colr |enb|C1 |C2 |C3 |   | 3="enable"
          |                               |   |
    FC7   |            sound              | W | squarewave output
          |                               |   |
    FC8   |       N1      |      N2       | W | range of the 4 display digits
    FC9   |       N3      |      N4       | W |
          |                               |   |
          |obj/backgrnd   |complete object| R |
    FCA   | 1 | 2 | 3 | 4 | 1 | 2 | 3 | 4 |   |
          |                               |   |
    FCB   |   |VR-|   object collisions   | R | Composition of object and back-
          |   |LE |1/2|1/3|1/3|1/4|2/4|3/4|   | ground,collision detection and
          |                               |   | object display as a state display
          |                               |   | for the status register.Set VRLE.
          |                               |   | wait for VRST.Read out or transmit
          |                               |   | [copy?] all bits until reset by
          |                               |   | VRST.
          |                               |   |
    FCC   |            PORT1              | R | PORT1 and PORT2 for the range of
    FCD   |            PORT2              |   | the A/D conversion.Cleared by VRST
    FCE   |            (free)             |   |
    FCF   |            (free)             |   |


    Size control by byte FC0

     bit  matrix
    |0|0|  8x10
    |0|1| 16x20
    |1|0| 32x40
    |1|1| 64x80

    CE1 and not-CE2 are outputs from the PVI.$E80..$EFF also controls the
    analog multiplexer.


    SPRITES
    -------

    each object field: (=sprite data structure)

    0 \ 10 bytes of bitmap (Each object is 8 pixels wide.)
    9 /
    A   HC  horizontal object coordinate
    B   HCB horizontal duplicate coordinate
    C   VC  vertical object coordinate
    D   VCB vertical duplicate coordinate

*************************************************************/

#include "emu.h"
#include "machine/s2636.h"

=======
    FC3   |                       |frm|pos| W | score format and position
          |                               |   |
    FC4   |                               | - |
    FC5   |                               | - |
          |                               |   |
    FC6   |   |C1 |C2 |C3 |BG | scrn colr | W | background enable and color
          |   |backg colr |enb|C1 |C2 |C3 |   |
          |                               |   |
    FC7   |            sound              | W | sound square wave period
          |                               |   |
    FC8   |       N1      |      N2       | W | values of the four score digits
    FC9   |       N3      |      N4       | W |
          |                               |   |
          | obj/backgrnd  |object complete| R | object/background and inter-object
    FCA   | 1 | 2 | 3 | 4 | 1 | 2 | 3 | 4 |   | collision status and object display
          |                               |   | completion status
    FCB   |   |VR-|   object collisions   | R | VRLE set at leading edge of VRST,
          |   |LE |1/2|1/3|1/3|1/4|2/4|3/4|   | all bits reset when read or at
          |                               |   | trailing edge of VRST
          |                               |   |
    FCC   |           A/D POT 1           | R | POT1 and POT2 A/D conversion value
    FCD   |           A/D POT 2           | R | valid during VRST only
          |                               |   |
    FCE   |                               | - |
    FCF   |                               | - |

*************************************************************/

#include "emu.h"
#include "machine/s2636.h"

#include "screen.h"


int const s2636_device::OFFS_OBJ[s2636_device::OBJ_COUNT] = { 0x000, 0x010, 0x020, 0x040 };

int const s2636_device::SCORE_START_X[2][s2636_device::SCORE_DIGITS] { { 48, 64, 96, 112 }, { 48, 64, 80, 96 } };
int const s2636_device::SCORE_START_Y[2] = { 20, 200 };

uint16_t const s2636_device::SCORE_FONT[16][5] =
{
	{ 0x0fff, 0x0f0f, 0x0f0f, 0x0f0f, 0x0fff },
	{ 0x0f00, 0x0f00, 0x0f00, 0x0f00, 0x0f00 },
	{ 0x0fff, 0x0f00, 0x0fff, 0x000f, 0x0fff },
	{ 0x0fff, 0x0f00, 0x0fff, 0x0f00, 0x0fff },
	{ 0x0f0f, 0x0f0f, 0x0fff, 0x0f00, 0x0f00 },
	{ 0x0fff, 0x000f, 0x0fff, 0x0f00, 0x0fff },
	{ 0x0fff, 0x000f, 0x0fff, 0x0f0f, 0x0fff },
	{ 0x0fff, 0x0f00, 0x0f00, 0x0f00, 0x0f00 },
	{ 0x0fff, 0x0f0f, 0x0fff, 0x0f0f, 0x0fff },
	{ 0x0fff, 0x0f0f, 0x0fff, 0x0f00, 0x0fff },
	{ 0x0000, 0x0000, 0x0000, 0x0000, 0x0000 },
	{ 0x0000, 0x0000, 0x0000, 0x0000, 0x0000 },
	{ 0x0000, 0x0000, 0x0000, 0x0000, 0x0000 },
	{ 0x0000, 0x0000, 0x0000, 0x0000, 0x0000 },
	{ 0x0000, 0x0000, 0x0000, 0x0000, 0x0000 },
	{ 0x0000, 0x0000, 0x0000, 0x0000, 0x0000 }
};
>>>>>>> upstream/master

/*************************************
 *
 *  Device interface
 *
 *************************************/

<<<<<<< HEAD
const device_type S2636 = &device_creator<s2636_device>;

s2636_device::s2636_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock)
	: device_t(mconfig, S2636, "Signetics 2636", tag, owner, clock, "s2636", __FILE__),
		device_video_interface(mconfig, *this),
		device_sound_interface(mconfig, *this),
		m_channel(NULL),
		m_size(0),
		m_pos(0),
		m_level(0),
		m_work_ram_size(0),
		m_y_offset(0),
		m_x_offset(0)
{
	for (int i = 0; i < 1; i++)
		m_reg[i] = 0;
=======
DEFINE_DEVICE_TYPE(S2636, s2636_device, "s2636", "Signetics 2636 PVI")

s2636_device::s2636_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock)
	: device_t(mconfig, S2636, tag, owner, clock)
	, device_video_interface(mconfig, *this)
	, device_sound_interface(mconfig, *this)
	, m_divider(1)
	, m_y_offset(0)
	, m_x_offset(0)
	, m_intreq_cb(*this)
	, m_vrst(false)
	, m_screen_line(0)
	, m_vis_line(0)
	, m_intreq(CLEAR_LINE)
	, m_intack(CLEAR_LINE)
	, m_stream(nullptr)
	, m_sample_cnt(0)
	, m_sound_lvl(false)
{
	for (auto &elem : m_registers) elem = 0;
	for (auto &elem : m_obj_cnt) elem = 0;
	for (auto &elem : m_obj_disp) elem = false;
	for (auto &elem : m_obj_dup) elem = false;
>>>>>>> upstream/master
}

//-------------------------------------------------
//  device_start - device-specific startup
//-------------------------------------------------

void s2636_device::device_start()
{
<<<<<<< HEAD
	int width = m_screen->width();
	int height = m_screen->height();

	m_work_ram.resize(m_work_ram_size);
	memset(&m_work_ram[0], 0, m_work_ram_size);
	m_bitmap.resize(width, height);
	m_collision_bitmap.resize(width, height);

	save_item(NAME(m_work_ram));
	save_item(NAME(m_bitmap));
	save_item(NAME(m_collision_bitmap));

	m_channel = machine().sound().stream_alloc(*this, 0, 1, machine().sample_rate());
	save_item(NAME(m_size));
	save_item(NAME(m_pos));
	save_item(NAME(m_level));
	save_item(NAME(m_reg));
}

/*************************************
 *
 *  Constants
 *
 *************************************/

#define SPRITE_WIDTH    (8)
#define SPRITE_HEIGHT   (10)

static const int sprite_offsets[4] = { 0x00, 0x10, 0x20, 0x40 };


/*************************************
 *
 *  Draw a sprite
 *
 *************************************/

static void draw_sprite( UINT8 *gfx, int color, int y, int x, int expand, int or_mode, bitmap_ind16 &bitmap, const rectangle &cliprect )
{
	/* for each row */
	for (int sy = 0; sy < SPRITE_HEIGHT; sy++)
	{
		/* for each pixel on the row */
		for (int sx = 0; sx < SPRITE_WIDTH; sx++)
		{
			/* each pixel can be expanded */
			for (int ey = 0; ey <= expand; ey++)
			{
				for (int ex = 0; ex <= expand; ex++)
				{
					/* compute effective destination pixel */
					int ty = y + sy * (expand + 1) + ey;
					int tx = x + sx * (expand + 1) + ex;

					/* get out if outside the drawing region */
					if (!cliprect.contains(tx, ty))
						continue;

					/* get out if current image bit is transparent */
					if (((gfx[sy] << sx) & 0x80) == 0x00)
						continue;

					if (or_mode)
						bitmap.pix16(ty, tx) = 0x08 | bitmap.pix16(ty, tx) | color;
					else
						bitmap.pix16(ty, tx) = 0x08 | color;
				}
			}
		}
	}
}


/*************************************
 *
 *  Collision detection
 *
 *************************************/

int s2636_device::check_collision( int spriteno1, int spriteno2, const rectangle &cliprect )
{
	int checksum = 0;

	UINT8* attr1 = &m_work_ram[sprite_offsets[spriteno1]];
	UINT8* attr2 = &m_work_ram[sprite_offsets[spriteno2]];

	/* TODO: does not check shadow sprites yet */

	m_collision_bitmap.fill(0, cliprect);

	if ((attr1[0x0a] != 0xff) && (attr2[0x0a] != 0xff))
	{
		int x, y;

		int x1 = attr1[0x0a] + m_x_offset;
		int y1 = attr1[0x0c] + m_y_offset;
		int x2 = attr2[0x0a] + m_x_offset;
		int y2 = attr2[0x0c] + m_y_offset;

		int expand1 = (m_work_ram[0xc0] >> (spriteno1 << 1)) & 0x03;
		int expand2 = (m_work_ram[0xc0] >> (spriteno2 << 1)) & 0x03;

		/* draw first sprite */
		draw_sprite(attr1, 1, y1, x1, expand1, FALSE, m_collision_bitmap, cliprect);

		/* get fingerprint */
		for (x = x1; x < x1 + SPRITE_WIDTH; x++)
			for (y = y1; y < y1 + SPRITE_HEIGHT; y++)
			{
				if (!cliprect.contains(x, y))
					continue;

				checksum = checksum + m_collision_bitmap.pix16(y, x);
			}

		/* black out second sprite */
		draw_sprite(attr2, 0, y2, x2, expand2, FALSE, m_collision_bitmap, cliprect);

		/* remove fingerprint */
		for (x = x1; x < x1 + SPRITE_WIDTH; x++)
			for (y = y1; y < y1 + SPRITE_HEIGHT; y++)
			{
				if (!cliprect.contains(x, y))
					continue;

				checksum = checksum - m_collision_bitmap.pix16(y, x);
			}
	}

	return (checksum != 0);
}



/*************************************
 *
 *  Main drawing
 *
 *************************************/

bitmap_ind16 &s2636_device::update( const rectangle &cliprect )
{
	UINT8 collision = 0;
	int spriteno;

	m_bitmap.fill(0, cliprect);

	for (spriteno = 0; spriteno < 4; spriteno++)
	{
		int color, expand, x, y;
		UINT8* attr = &m_work_ram[sprite_offsets[spriteno]];

		/* get out if sprite is turned off */
		if (attr[0x0a] == 0xff)
			continue;

		x = attr[0x0a] + m_x_offset;
		y = attr[0x0c] + m_y_offset;

		color = (m_work_ram[0xc1 + (spriteno >> 1)] >> ((spriteno & 1) ? 0 : 3)) & 0x07;
		expand = (m_work_ram[0xc0] >> (spriteno << 1)) & 0x03;

		draw_sprite(attr, color, y, x, expand, TRUE, m_bitmap, cliprect);

		/* bail if no shadow sprites */
		if ((attr[0x0b] == 0xff) || (attr[0x0d] == 0xfe))
			continue;

		x = attr[0x0b] + m_x_offset;

		while (y < 0xff)
		{
			y = y + SPRITE_HEIGHT + attr[0x0d];

			draw_sprite(attr, color, y, x, expand, TRUE, m_bitmap, cliprect);
		}
	}

	/* collision detection */
	if (check_collision(0, 1, cliprect))  collision |= 0x20;
	if (check_collision(0, 2, cliprect))  collision |= 0x10;
	if (check_collision(0, 3, cliprect))  collision |= 0x08;
	if (check_collision(1, 2, cliprect))  collision |= 0x04;
	if (check_collision(1, 3, cliprect))  collision |= 0x02;
	if (check_collision(2, 3, cliprect))  collision |= 0x01;

	m_work_ram[0xcb] = collision;

	return m_bitmap;
}


/*************************************
 *
 *  Work RAM access handlers
 *
 *************************************/

WRITE8_MEMBER( s2636_device::work_ram_w )
{
	assert(offset < m_work_ram_size);

	if ( offset == 0xc7 )
	{
		soundport_w(0, data);
	}

	m_work_ram[offset] = data;
}


READ8_MEMBER( s2636_device::work_ram_r )
{
	assert(offset < m_work_ram_size);

	return m_work_ram[offset];
}

/* Sound */

void s2636_device::soundport_w (int offset, int data)
{
	m_channel->update();
	m_reg[offset] = data;
	switch (offset)
	{
		case 0:
			m_pos = 0;
			m_level = TRUE;
			// frequency 7874/(data+1)
			m_size = machine().sample_rate() * (data + 1) /7874;
			break;
	}
=======
	m_bitmap.resize(m_screen->width(), m_screen->height());

	save_item(NAME(m_bitmap));

	save_item(NAME(m_registers));

	save_item(NAME(m_vrst));
	save_item(NAME(m_screen_line));
	save_item(NAME(m_vis_line));

	save_item(NAME(m_obj_cnt));
	save_item(NAME(m_obj_disp));
	save_item(NAME(m_obj_dup));

	save_item(NAME(m_intreq));
	save_item(NAME(m_intack));

	m_stream = machine().sound().stream_alloc(*this, 0, 1, machine().sample_rate());
	save_item(NAME(m_sample_cnt));
	save_item(NAME(m_sound_lvl));

	m_intreq_cb.resolve_safe();
}


//-------------------------------------------------
//  backwards-compatible update method
//-------------------------------------------------

bitmap_ind16 const &s2636_device::update(const rectangle &cliprect)
{
	m_vrst = true;
	m_screen_line = m_screen->visible_area().min_y;
	while (m_screen_line <= m_screen->visible_area().max_y)
		render_next_line();

	return m_bitmap;
}


//-------------------------------------------------
//  render the first line into the bitmap
//-------------------------------------------------

void s2636_device::render_first_line()
{
	m_screen_line = 0;
	render_next_line();
}


//-------------------------------------------------
//  render next line into the bitmap
//-------------------------------------------------

void s2636_device::render_next_line()
{
	assert(m_screen_line < m_bitmap.height());

	// pre-clear the line for convenience
	rectangle const &vis_area = m_screen->visible_area();
	uint16_t *const   row = &m_bitmap.pix16(m_screen_line);
	m_bitmap.plot_box(0, m_screen_line, m_bitmap.width(), 1, 0);

	if ((vis_area.min_y > m_screen_line) || (vis_area.max_y < m_screen_line))
	{
		if (!m_vrst)
		{
			m_registers[REG_VBL_COL_OBJ] |= 0x40;
			m_vrst = true;
			update_intreq(ASSERT_LINE);
		}
	}
	else
	{
		// check for first visible line
		if (m_vrst)
		{
			// latch vertical position primary objects
			for (int i = 0; i < OBJ_COUNT; i++)
			{
				m_obj_cnt[i] = m_registers[OFFS_OBJ[i] + OFFS_VC] + m_y_offset;
				m_obj_disp[i] = false;
				m_obj_dup[i] = false;
			}

			// collision, completion and vertical reset flags are cleared here
			m_registers[REG_COL_BG_CMPL] = 0x00;
			m_registers[REG_VBL_COL_OBJ] = 0x00;

			// set our internal tracking flags and clear interrupt
			m_vrst = false;
			m_vis_line = 0;
			update_intreq(CLEAR_LINE);
		}

		// work out what object pixels belong in this line
		for (int i = 0; i < OBJ_COUNT; i++)
		{
			// repurpose counter and set flag when we've skipped enough lines
			if (!m_obj_cnt[i])
			{
				m_obj_cnt[i] = OBJ_HEIGHT << 3;
				m_obj_disp[i] = true;
			}

			if (m_obj_disp[i])
			{
				int const obj_inc = 1 << (3 - object_scale(i));
				m_obj_cnt[i] -= obj_inc;

				// fetch appropriate line from object
				uint8_t const     obj_bits = m_registers[OFFS_OBJ[i] + OBJ_HEIGHT - 1 - (m_obj_cnt[i] >> 3)];
				uint16_t const    obj_clr = object_color(i) | 0x08 | (0x10 << i);

				// blit it to the line ignoring intermediate pixels
				int const obj_h_cnt = m_registers[OFFS_OBJ[i] + (m_obj_dup[i] ? OFFS_HCB : OFFS_HC)] + m_x_offset;
				for (int x = 0, screen_col = vis_area.min_x + (obj_h_cnt * m_divider); (OBJ_WIDTH << 3) > x && (vis_area.max_x >= screen_col); )
				{
					bool const bit = bool((obj_bits << (x >> 3)) & 0x80);
					if (bit && (vis_area.min_x <= screen_col)) row[screen_col] |= obj_clr;
					x += obj_inc;
					screen_col += m_divider;
				}

				// if that's the last line of the object, flag completion and prepare for duplicates
				if (!m_obj_cnt[i])
				{
					m_registers[REG_COL_BG_CMPL] |= 0x01 << (3 - i);
					m_obj_cnt[i] = 1 + m_registers[OFFS_OBJ[i] + OFFS_VCB];
					m_obj_disp[i] = false;
					m_obj_dup[i] = true;
					update_intreq(ASSERT_LINE);
				}
			}
			else
			{
				// count down lines to display object
				m_obj_cnt[i]--;
			}
		}

		// let's take a look at the score display
		uint16_t const    bg_clr = m_registers[REG_BG_ENB_CLR] & 0x07;
		int const       score_row = m_vis_line - m_y_offset - SCORE_START_Y[m_registers[REG_SCORE_FMT] & 0x01];
		if ((0 <= score_row) && (SCORE_HEIGHT > score_row))
		{
			int const (&score_start_x)[SCORE_DIGITS] = SCORE_START_X[(m_registers[REG_SCORE_FMT] >> 1) & 0x01];
			for (int i = 0; i < SCORE_DIGITS; i++)
			{
				uint16_t  score_bits = SCORE_FONT[score_digit(i)][score_row >> 2];
				int     screen_col = vis_area.min_x + ((score_start_x[i] + m_x_offset) * m_divider);
				while (score_bits && (vis_area.max_x >= screen_col))
				{
					if (score_bits & 0x0001) row[screen_col] |= bg_clr | 0x08;
					score_bits >>= 1;
					screen_col += m_divider;
				}
			}
		}

		// work out how the background pattern will be drawn
		bool const      bg_enable = bool(m_registers[REG_BG_ENB_CLR] & 0x08);
		int const       bg_row = m_vis_line - m_y_offset - BG_START_Y;
		bool const      bg_draw = bg_enable && (0 <= bg_row) && (BG_HEIGHT > bg_row);
		int const       bg_vbar_offs = OFFS_VBAR_DEF + ((bg_row / 20) << 2) + (((bg_row % 20) >= 2) ? 2 : 0);
		int const       bg_hbar_offs = OFFS_HBAR_DEF + (bg_row / 40);
		uint16_t const    bg_vbar_bits = (uint16_t(m_registers[bg_vbar_offs]) << 8) | uint16_t(m_registers[bg_vbar_offs + 1]);
		uint8_t const     bg_hbar_bits = m_registers[bg_hbar_offs];
		bool const      bg_hbar_stretch = bool(bg_hbar_bits & (1 << ((((bg_row % 40) >= 20) ? 3 : 0) + (((bg_row % 20) >= 11) ? 2 : ((bg_row % 20) >= 2) ? 1 : 0))));
		int const       bg_hbar_width = bg_hbar_stretch ? 8 : (0xc0 == (bg_hbar_bits & 0xc0)) ? 4 : (0x40 == (bg_hbar_bits & 0xc0)) ? 2 : 1;
		uint16_t const    scrn_clr = bg_enable ? ((m_registers[REG_BG_ENB_CLR] >> 4) & 0x07) : 0x00;

		for (int screen_col = vis_area.min_x, x = 0; vis_area.max_x >= screen_col; x++)
		{
			// check object-object collisions
			if ((row[screen_col] & 0x10) && (row[screen_col] & 0x20)) m_registers[REG_VBL_COL_OBJ] |= 0x20;
			if ((row[screen_col] & 0x10) && (row[screen_col] & 0x40)) m_registers[REG_VBL_COL_OBJ] |= 0x10;
			if ((row[screen_col] & 0x10) && (row[screen_col] & 0x80)) m_registers[REG_VBL_COL_OBJ] |= 0x08;
			if ((row[screen_col] & 0x20) && (row[screen_col] & 0x40)) m_registers[REG_VBL_COL_OBJ] |= 0x04;
			if ((row[screen_col] & 0x20) && (row[screen_col] & 0x80)) m_registers[REG_VBL_COL_OBJ] |= 0x02;
			if ((row[screen_col] & 0x40) && (row[screen_col] & 0x80)) m_registers[REG_VBL_COL_OBJ] |= 0x01;

			// work out if the background hits this pixel
			int const   bg_col = x - m_x_offset - BG_START_X;
			bool const  bg = bool(bg_vbar_bits & (1U << (15 - (bg_col >> 3))));
			if (bg_draw && (0 <= bg_col) && (BG_WIDTH > bg_col) && bg && (bg_hbar_width > (bg_col & 0x07)))
			{
				// do object-background collisions
				if (row[screen_col] & 0x10) m_registers[REG_COL_BG_CMPL] |= 0x80;
				if (row[screen_col] & 0x20) m_registers[REG_COL_BG_CMPL] |= 0x40;
				if (row[screen_col] & 0x40) m_registers[REG_COL_BG_CMPL] |= 0x20;
				if (row[screen_col] & 0x80) m_registers[REG_COL_BG_CMPL] |= 0x10;
				if (!(row[screen_col] & 0x08)) row[screen_col] = bg_clr;
			}
			else if (!(row[screen_col] & 0x08))
			{
				// draw screen background if not obscured
				row[screen_col] = scrn_clr;
			}

			// clear collision crud and deal with pixel clock divider ratio
			row[screen_col++] &= 0x0f;
			for (int i = 1; (i < m_divider) && (vis_area.max_x >= screen_col); i++, screen_col++)
			{
				row[screen_col] = row[screen_col - 1];
			}
		}
	}

	m_screen_line++;
	m_vis_line++;
}


//-------------------------------------------------
//  bus access handlers
//-------------------------------------------------

READ8_MEMBER( s2636_device::read_data )
{
	mask_offset(offset);
	uint8_t data = m_registers[offset];

	// TODO: some locations are not readable, should return some garbage

	switch (offset)
	{
	case REG_COL_BG_CMPL:
	case REG_VBL_COL_OBJ:
		if (!machine().side_effect_disabled())
			m_registers[offset] = 0x00; // collision/completion/VRESET flags reset on read
		break;
	}

	return data;
}

WRITE8_MEMBER( s2636_device::write_data )
{
	mask_offset(offset);

	if (REG_SND_PERIOD == offset)
		m_stream->update();

	m_registers[offset] = data;
}

WRITE_LINE_MEMBER( s2636_device::write_intack )
{
	assert((ASSERT_LINE == state) || (HOLD_LINE == state) || (CLEAR_LINE == state) || (PULSE_LINE == state));

	// pretend interrupt acknowledge is handled instantaneously
	m_intack = state;
	update_intreq(m_intreq);
	if (ASSERT_LINE != m_intreq)
		m_intack = CLEAR_LINE;
>>>>>>> upstream/master
}


//-------------------------------------------------
<<<<<<< HEAD
//  sound_stream_update - handle a stream update
=======
//  sound_stream_update - generate audio output
>>>>>>> upstream/master
//-------------------------------------------------

void s2636_device::sound_stream_update(sound_stream &stream, stream_sample_t **inputs, stream_sample_t **outputs, int samples)
{
<<<<<<< HEAD
	int i;
	stream_sample_t *buffer = outputs[0];

	for (i = 0; i < samples; i++, buffer++)
	{
		*buffer = 0;
		if (m_reg[0] && m_pos <= m_size / 2)
		{
			*buffer = 0x7fff;
		}
		if (m_pos <= m_size)
			m_pos++;
		if (m_pos > m_size)
			m_pos = 0;
=======
	stream_sample_t *buffer = outputs[0];
	while (samples--)
	{
		if (!m_sample_cnt)
		{
			if (m_registers[REG_SND_PERIOD])
			{
				m_sample_cnt = (machine().sample_rate() * (m_registers[REG_SND_PERIOD] + 1) * m_screen->scan_period()).seconds();
				m_sound_lvl = !m_sound_lvl;
			}
			else
			{
				m_sample_cnt = 1;
				m_sound_lvl = false;
			}
		}

		*buffer++ = m_sound_lvl ? 0x7fff : 0x0000;
		m_sample_cnt--;
	}
}


void s2636_device::update_intreq(int value)
{
	int const new_value = m_intack ? CLEAR_LINE : value;
	if (new_value != m_intreq)
	{
		m_intreq = new_value;
		m_intreq_cb(m_intreq);
>>>>>>> upstream/master
	}
}
