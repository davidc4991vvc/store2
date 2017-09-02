<<<<<<< HEAD
// license:???
// copyright-holders:Bryan McPhail,Fuzz,Ernesto Corvi,Andrew Prime,Zsolt Vasvari
=======
// license:BSD-3-Clause
// copyright-holders:Bryan McPhail,Ernesto Corvi,Andrew Prime,Zsolt Vasvari
// thanks-to:Fuzz
>>>>>>> upstream/master
/* NeoGeo sprites (and fixed text layer) */

#include "emu.h"
#include "neogeo_spr.h"
<<<<<<< HEAD
#include "bus/neogeo/neogeo_helper.h"

// pure virtual functions
//const device_type NEOGEO_SPRITE_BASE = &device_creator<neosprite_base_device>;

/*
neosprite_base_device::neosprite_base_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock)
    : device_t(mconfig, NEOGEO_SPRITE_BASE, "NeoGeo Sprites", tag, owner, clock, "neospritebase", __FILE__),
    m_bppshift(4)
{

}
*/

neosprite_base_device::neosprite_base_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock, device_type type)
	: device_t(mconfig, type, "Neogeo Sprites", tag, owner, clock, "neosprite", __FILE__),
	m_bppshift(4)
=======
#include "screen.h"


// pure virtual functions
//const device_type NEOGEO_SPRITE_BASE = device_creator<neosprite_base_device>;

neosprite_base_device::neosprite_base_device(
		const machine_config &mconfig,
		device_type type,
		const char *tag,
		device_t *owner,
		uint32_t clock)
	: device_t(mconfig, type, tag, owner, clock)
	, m_bppshift(4)
>>>>>>> upstream/master
{
}

void neosprite_base_device::device_start()
{
<<<<<<< HEAD
	m_videoram = auto_alloc_array(machine(), UINT16, 0x8000 + 0x800);
	m_videoram_drawsource = m_videoram;

	/* clear allocated memory */
	memset(m_videoram, 0x00, (0x8000 + 0x800) * sizeof(UINT16));
=======
	m_videoram = std::make_unique<uint16_t[]>(0x8000 + 0x800);
	m_videoram_drawsource = m_videoram.get();

	/* clear allocated memory */
	memset(m_videoram.get(), 0x00, (0x8000 + 0x800) * sizeof(uint16_t));
>>>>>>> upstream/master

	create_sprite_line_timer();
	create_auto_animation_timer();

<<<<<<< HEAD


=======
>>>>>>> upstream/master
	/* initialize values that are not modified on a reset */
	m_vram_offset = 0;
	m_vram_read_buffer = 0;
	m_vram_modulo = 0;
	m_auto_animation_speed = 0;
	m_auto_animation_disabled = 0;
	m_auto_animation_counter = 0;
	m_auto_animation_frame_counter = 0;

	/* register for state saving */
<<<<<<< HEAD
	save_pointer(NAME(m_videoram), 0x8000 + 0x800);
=======
	save_pointer(NAME(m_videoram.get()), 0x8000 + 0x800);
>>>>>>> upstream/master
	save_item(NAME(m_vram_offset));
	save_item(NAME(m_vram_read_buffer));
	save_item(NAME(m_vram_modulo));
	save_item(NAME(m_fixed_layer_source));

	save_item(NAME(m_auto_animation_speed));
	save_item(NAME(m_auto_animation_disabled));
	save_item(NAME(m_auto_animation_counter));
	save_item(NAME(m_auto_animation_frame_counter));


	m_region_zoomy = memregion(":zoomy")->base();
}

void neosprite_base_device::device_reset()
{
	//m_sprite_gfx_address_mask = 0;
	optimize_sprite_data();

	start_sprite_line_timer();
	start_auto_animation_timer();
}



/*************************************
 *
 *  Video RAM access
 *
 *************************************/

<<<<<<< HEAD
void neosprite_base_device::set_videoram_offset( UINT16 data )
=======
void neosprite_base_device::set_videoram_offset(uint16_t data)
>>>>>>> upstream/master
{
	m_vram_offset = (data & 0x8000 ? data & 0x87ff : data);

	/* the read happens right away */
	m_vram_read_buffer = m_videoram[m_vram_offset];
}


<<<<<<< HEAD
UINT16 neosprite_base_device::get_videoram_data(  )
=======
uint16_t neosprite_base_device::get_videoram_data()
>>>>>>> upstream/master
{
	return m_vram_read_buffer;
}


<<<<<<< HEAD
void neosprite_base_device::set_videoram_data( UINT16 data)
=======
void neosprite_base_device::set_videoram_data(uint16_t data)
>>>>>>> upstream/master
{
	m_videoram[m_vram_offset] = data;

	/* auto increment/decrement the current offset - A15 is NOT affected */
	set_videoram_offset((m_vram_offset & 0x8000) | ((m_vram_offset + m_vram_modulo) & 0x7fff));
}


<<<<<<< HEAD
void neosprite_base_device::set_videoram_modulo( UINT16 data)
=======
void neosprite_base_device::set_videoram_modulo(uint16_t data)
>>>>>>> upstream/master
{
	m_vram_modulo = data;
}


<<<<<<< HEAD
UINT16 neosprite_base_device::get_videoram_modulo(  )
=======
uint16_t neosprite_base_device::get_videoram_modulo()
>>>>>>> upstream/master
{
	return m_vram_modulo;
}



/*************************************
 *
 *  Auto animation
 *
 *************************************/

<<<<<<< HEAD
void neosprite_base_device::set_auto_animation_speed( UINT8 data)
=======
void neosprite_base_device::set_auto_animation_speed(uint8_t data)
>>>>>>> upstream/master
{
	m_auto_animation_speed = data;
}


<<<<<<< HEAD
void neosprite_base_device::set_auto_animation_disabled( UINT8 data)
=======
void neosprite_base_device::set_auto_animation_disabled(uint8_t data)
>>>>>>> upstream/master
{
	m_auto_animation_disabled = data;
}


<<<<<<< HEAD
UINT8 neosprite_base_device::neogeo_get_auto_animation_counter(  )
=======
uint8_t neosprite_base_device::neogeo_get_auto_animation_counter()
>>>>>>> upstream/master
{
	return m_auto_animation_counter;
}


TIMER_CALLBACK_MEMBER(neosprite_base_device::auto_animation_timer_callback)
{
	if (m_auto_animation_frame_counter == 0)
	{
		m_auto_animation_frame_counter = m_auto_animation_speed;
		m_auto_animation_counter += 1;
	}
	else
		m_auto_animation_frame_counter = m_auto_animation_frame_counter - 1;

	m_auto_animation_timer->adjust(m_screen->time_until_pos(NEOGEO_VSSTART));
}


<<<<<<< HEAD
void neosprite_base_device::create_auto_animation_timer(  )
=======
void neosprite_base_device::create_auto_animation_timer()
>>>>>>> upstream/master
{
	m_auto_animation_timer = machine().scheduler().timer_alloc(timer_expired_delegate(FUNC(neosprite_base_device::auto_animation_timer_callback),this));
}


<<<<<<< HEAD
void neosprite_base_device::start_auto_animation_timer(  )
=======
void neosprite_base_device::start_auto_animation_timer()
>>>>>>> upstream/master
{
	m_auto_animation_timer->adjust(m_screen->time_until_pos(NEOGEO_VSSTART));
}



/*************************************
 *
 *  Fixed layer
 *
 *************************************/

<<<<<<< HEAD
void neosprite_base_device::neogeo_set_fixed_layer_source( UINT8 data )
=======
void neosprite_base_device::neogeo_set_fixed_layer_source(uint8_t data)
>>>>>>> upstream/master
{
	m_fixed_layer_source = data;
}


<<<<<<< HEAD
void neosprite_base_device::draw_fixed_layer( bitmap_rgb32 &bitmap, int scanline )
{
	int x;

	UINT8* gfx_base = m_fixed_layer_source ? m_region_fixed : m_region_fixedbios->base();
	UINT32 addr_mask = ( m_fixed_layer_source ? m_region_fixed_size : m_region_fixedbios->bytes() ) - 1;
	UINT16 *video_data = &m_videoram_drawsource[0x7000 | (scanline >> 3)];
	UINT32 *pixel_addr = &bitmap.pix32(scanline, NEOGEO_HBEND);
=======
void neosprite_base_device::draw_fixed_layer(bitmap_rgb32 &bitmap, int scanline)
{
	int x;

	uint8_t* gfx_base = m_fixed_layer_source ? m_region_fixed : m_region_fixedbios->base();
	uint32_t addr_mask = ( m_fixed_layer_source ? m_region_fixed_size : m_region_fixedbios->bytes() ) - 1;
	uint16_t *video_data = &m_videoram_drawsource[0x7000 | (scanline >> 3)];
	uint32_t *pixel_addr = &bitmap.pix32(scanline, NEOGEO_HBEND);
>>>>>>> upstream/master

	int garouoffsets[32];
	int banked = m_fixed_layer_source && (addr_mask > 0x1ffff);

	/* thanks to Mr K for the garou & kof2000 banking info */
	/* Build line banking table for Garou & MS3 before starting render */
	if (banked && m_fixed_layer_bank_type == 1)
	{
		int garoubank = 0;
		int k = 0;
		int y = 0;
		while (y < 32)
		{
			if (m_videoram_drawsource[0x7500 + k] == 0x0200 && (m_videoram_drawsource[0x7580 + k] & 0xff00) == 0xff00)
			{
				garoubank = m_videoram_drawsource[0x7580 + k] & 3;
				garouoffsets[y++] = garoubank;
			}
			garouoffsets[y++] = garoubank;
			k += 2;
		}
	}

	for (x = 0; x < 40; x++)
	{
<<<<<<< HEAD
		UINT16 code_and_palette = *video_data;
		UINT16 code = code_and_palette & 0x0fff;
=======
		uint16_t code_and_palette = *video_data;
		uint16_t code = code_and_palette & 0x0fff;
>>>>>>> upstream/master

		if (banked)
		{
			int y = scanline >> 3;
			switch (m_fixed_layer_bank_type)
			{
			case 1:
				/* Garou, MSlug 3 */
				code += 0x1000 * (garouoffsets[(y - 2) & 31] ^ 3);
				break;
			case 2:
				code += 0x1000 * (((m_videoram_drawsource[0x7500 + ((y - 1) & 31) + 32 * (x / 6)] >> (5 - (x % 6)) * 2) & 3) ^ 3);
				break;
			}
		}

		{
			int i;
			int gfx_offset = ((code << 5) | (scanline & 0x07)) & addr_mask;

			const pen_t *char_pens;

			char_pens = &m_pens[code_and_palette >> 12 << m_bppshift];


<<<<<<< HEAD
			static const UINT32 pix_offsets[] = { 0x10, 0x18, 0x00, 0x08 };
=======
			static const uint32_t pix_offsets[] = { 0x10, 0x18, 0x00, 0x08 };
>>>>>>> upstream/master

			for (i = 0; i < 4; i++)
			{
				draw_fixed_layer_2pixels(pixel_addr, gfx_offset + pix_offsets[i], gfx_base, char_pens);
			}
		}

		video_data = video_data + 0x20;
	}
}


<<<<<<< HEAD
inline void neosprite_base_device::draw_fixed_layer_2pixels(UINT32*&pixel_addr, int offset, UINT8* gfx_base, const pen_t* char_pens)
{
	UINT8 data = gfx_base[offset];
=======
inline void neosprite_base_device::draw_fixed_layer_2pixels(uint32_t*&pixel_addr, int offset, uint8_t* gfx_base, const pen_t* char_pens)
{
	uint8_t data = gfx_base[offset];
>>>>>>> upstream/master

	if (data & 0x0f)
		*pixel_addr = char_pens[data & 0x0f];
	pixel_addr++;

	if (data & 0xf0)
		*pixel_addr = char_pens[(data & 0xf0) >> 4];
	pixel_addr++;

}

/*************************************
 *
 *  Sprite hardware
 *
 *************************************/

#define MAX_SPRITES_PER_SCREEN    (381)
#define MAX_SPRITES_PER_LINE      (96)


/* horizontal zoom table - verified on real hardware */
static const int zoom_x_tables[][16] =
{
	{ 0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0 },
	{ 0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0 },
	{ 0,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0 },
	{ 0,0,1,0,1,0,0,0,1,0,0,0,1,0,0,0 },
	{ 0,0,1,0,1,0,0,0,1,0,0,0,1,0,1,0 },
	{ 0,0,1,0,1,0,1,0,1,0,0,0,1,0,1,0 },
	{ 0,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0 },
	{ 1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0 },
	{ 1,0,1,0,1,0,1,0,1,1,1,0,1,0,1,0 },
	{ 1,0,1,1,1,0,1,0,1,1,1,0,1,0,1,0 },
	{ 1,0,1,1,1,0,1,0,1,1,1,0,1,0,1,1 },
	{ 1,0,1,1,1,0,1,1,1,1,1,0,1,0,1,1 },
	{ 1,0,1,1,1,0,1,1,1,1,1,0,1,1,1,1 },
	{ 1,1,1,1,1,0,1,1,1,1,1,0,1,1,1,1 },
	{ 1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1 },
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 }
};



inline bool neosprite_base_device::sprite_on_scanline(int scanline, int y, int rows)
{
	return (rows == 0) || (rows >= 0x20) || ((scanline - y) & 0x1ff) < (rows * 0x10);
}




<<<<<<< HEAD
void neosprite_base_device::draw_sprites( bitmap_rgb32 &bitmap, int scanline )
=======
void neosprite_base_device::draw_sprites(bitmap_rgb32 &bitmap, int scanline)
>>>>>>> upstream/master
{
	int sprite_index;
	int max_sprite_index;

	int y = 0;
	int x = 0;
	int rows = 0;
	int zoom_y = 0;
	int zoom_x = 0;
<<<<<<< HEAD
	UINT16 *sprite_list;
=======
	uint16_t *sprite_list;
>>>>>>> upstream/master

	/* select the active list */
	if (scanline & 0x01)
		sprite_list = &m_videoram_drawsource[0x8680];
	else
		sprite_list = &m_videoram_drawsource[0x8600];

	/* optimization -- find last non-zero entry and only draw that many +1
	   sprite.  This is not 100% correct as the hardware will keep drawing
	   the #0 sprite over and over, but we need the speed */
	for (max_sprite_index = (MAX_SPRITES_PER_LINE - 1); max_sprite_index >= 0; max_sprite_index--)
	{
		if (sprite_list[max_sprite_index] != 0)
			break;
	}

	/* add the +1 now, just in case the 0 at the end is real sprite */
	if (max_sprite_index != (MAX_SPRITES_PER_LINE - 1))
		max_sprite_index = max_sprite_index + 1;

	for (sprite_index = 0; sprite_index <= max_sprite_index; sprite_index++)
	{
<<<<<<< HEAD
		UINT16 sprite_number = sprite_list[sprite_index] & 0x01ff;
		UINT16 y_control = m_videoram_drawsource[0x8200 | sprite_number];
		UINT16 zoom_control = m_videoram_drawsource[0x8000 | sprite_number];
=======
		uint16_t sprite_number = sprite_list[sprite_index] & 0x01ff;
		uint16_t y_control = m_videoram_drawsource[0x8200 | sprite_number];
		uint16_t zoom_control = m_videoram_drawsource[0x8000 | sprite_number];
>>>>>>> upstream/master

		/* if chained, go to next X coordinate and get new X zoom */
		if (y_control & 0x40)
		{
			x = (x + zoom_x + 1) & 0x01ff;
			zoom_x = (zoom_control >> 8) & 0x0f;
		}
		/* new block */
		else
		{
			y = 0x200 - (y_control >> 7);
			x = m_videoram_drawsource[0x8400 | sprite_number] >> 7;

			zoom_y = (zoom_control & 0xff);

			zoom_x = (zoom_control >> 8) & 0x0f;
			rows = y_control & 0x3f;
		}

		/* skip if falls completely outside the screen */
		if ((x >= 0x140) && (x <= 0x1f0))
			continue;

		/* double check the Y coordinate, in case somebody modified the sprite coordinate
		   since we buffered it */
		if (sprite_on_scanline(scanline, y, rows))
		{
			int sprite_y;
			int tile;
<<<<<<< HEAD
			UINT8 sprite_y_and_tile;
			offs_t attr_and_code_offs;
			UINT16 attr;
			UINT32 code;
=======
			uint8_t sprite_y_and_tile;
			offs_t attr_and_code_offs;
			uint16_t attr;
			uint32_t code;
>>>>>>> upstream/master
			const int *zoom_x_table;
			const pen_t *line_pens;
			int x_inc;

			int sprite_line = (scanline - y) & 0x1ff;
			int zoom_line = sprite_line & 0xff;
			int invert = sprite_line & 0x100;

			if (invert)
				zoom_line ^= 0xff;

			if (rows > 0x20)
			{
				zoom_line = zoom_line % ((zoom_y + 1) << 1);

				if (zoom_line > zoom_y)
				{
					zoom_line = ((zoom_y + 1) << 1) - 1 - zoom_line;
					invert = !invert;
				}
			}

			sprite_y_and_tile = m_region_zoomy[(zoom_y << 8) | zoom_line];

			sprite_y = sprite_y_and_tile & 0x0f;
			tile = sprite_y_and_tile >> 4;

			if (invert)
			{
				sprite_y ^= 0x0f;
				tile ^= 0x1f;
			}

			attr_and_code_offs = (sprite_number << 6) | (tile << 1);
			attr = m_videoram_drawsource[attr_and_code_offs + 1];
<<<<<<< HEAD
			code = ((attr << 12) & 0x70000) | m_videoram_drawsource[attr_and_code_offs];
=======
			code = ((attr << 12) & 0xf0000) | m_videoram_drawsource[attr_and_code_offs];
>>>>>>> upstream/master

			/* substitute auto animation bits */
			if (!m_auto_animation_disabled)
			{
				if (attr & 0x0008)
					code = (code & ~0x07) | (m_auto_animation_counter & 0x07);
				else if (attr & 0x0004)
					code = (code & ~0x03) | (m_auto_animation_counter & 0x03);
			}

			/* vertical flip? */
			if (attr & 0x0002)
				sprite_y ^= 0x0f;

			zoom_x_table = zoom_x_tables[zoom_x];

			/* compute offset in gfx ROM and mask it to the number of bits available */
			int gfx_base = ((code << 8) | (sprite_y << 4)) & m_sprite_gfx_address_mask;


			line_pens = &m_pens[attr >> 8 << m_bppshift];


			/* horizontal flip? */
			if (attr & 0x0001)
			{
				gfx_base = gfx_base + 0x0f;
				x_inc = -1;
			}
			else
				x_inc = 1;

			/* draw the line - no wrap-around */
			if (x <= 0x01f0)
			{
				int i;

<<<<<<< HEAD
				UINT32 *pixel_addr = &bitmap.pix32(scanline, x + NEOGEO_HBEND);
=======
				uint32_t *pixel_addr = &bitmap.pix32(scanline, x + NEOGEO_HBEND);
>>>>>>> upstream/master

				for (i = 0; i < 0x10; i++)
				{
					if (*zoom_x_table)
					{
						draw_pixel(gfx_base, pixel_addr, line_pens);

						pixel_addr++;
					}

					zoom_x_table++;
					gfx_base += x_inc;
				}
			}
			/* wrap-around */
			else
			{
				int i;

				int x_save = x;
<<<<<<< HEAD
				UINT32 *pixel_addr = &bitmap.pix32(scanline, NEOGEO_HBEND);
=======
				uint32_t *pixel_addr = &bitmap.pix32(scanline, NEOGEO_HBEND);
>>>>>>> upstream/master

				for (i = 0; i < 0x10; i++)
				{
					if (*zoom_x_table)
					{
						if (x >= 0x200)
						{
							draw_pixel(gfx_base, pixel_addr, line_pens);

							pixel_addr++;
						}

						x++;
					}

					zoom_x_table++;
					gfx_base += x_inc;
				}

				x = x_save;
			}
		}
	}
}


<<<<<<< HEAD
void neosprite_base_device::parse_sprites( int scanline )
{
	UINT16 sprite_number;
	int y = 0;
	int rows = 0;
	UINT16 *sprite_list;
=======
void neosprite_base_device::parse_sprites(int scanline)
{
	uint16_t sprite_number;
	int y = 0;
	int rows = 0;
	uint16_t *sprite_list;
>>>>>>> upstream/master

	int active_sprite_count = 0;

	/* select the active list */
	if (scanline & 0x01)
		sprite_list = &m_videoram_drawsource[0x8680];
	else
		sprite_list = &m_videoram_drawsource[0x8600];

	/* scan all sprites */
	for (sprite_number = 0; sprite_number < MAX_SPRITES_PER_SCREEN; sprite_number++)
	{
<<<<<<< HEAD
		UINT16 y_control = m_videoram_drawsource[0x8200 | sprite_number];
=======
		uint16_t y_control = m_videoram_drawsource[0x8200 | sprite_number];
>>>>>>> upstream/master

		/* if not chained, get Y position and height, otherwise use previous values */
		if (~y_control & 0x40)
		{
			y = 0x200 - (y_control >> 7);
			rows = y_control & 0x3f;
		}

		/* skip sprites with 0 rows */
		if (rows == 0)
			continue;

		if (!sprite_on_scanline(scanline, y, rows))
			continue;

		/* sprite is on this scanline, add it to active list */
		*sprite_list = sprite_number;

		sprite_list++;

		/* increment sprite count, and if we reached the max, bail out */
		active_sprite_count++;

		if (active_sprite_count == MAX_SPRITES_PER_LINE)
			break;
	}

	/* fill the rest of the sprite list with 0, including one extra entry */
	memset(sprite_list, 0, sizeof(sprite_list[0]) * (MAX_SPRITES_PER_LINE - active_sprite_count + 1));
}


TIMER_CALLBACK_MEMBER(neosprite_base_device::sprite_line_timer_callback)
{
	int scanline = param;

	/* we are at the beginning of a scanline -
	   we need to draw the previous scanline and parse the sprites on the current one */
	if (scanline != 0)
		m_screen->update_partial(scanline - 1);

	parse_sprites(scanline);

	/* let's come back at the beginning of the next line */
	scanline = (scanline + 1) % NEOGEO_VTOTAL;

	m_sprite_line_timer->adjust(m_screen->time_until_pos(scanline), scanline);
}


<<<<<<< HEAD
void neosprite_base_device::create_sprite_line_timer(  )
=======
void neosprite_base_device::create_sprite_line_timer()
>>>>>>> upstream/master
{
	m_sprite_line_timer = machine().scheduler().timer_alloc(timer_expired_delegate(FUNC(neosprite_base_device::sprite_line_timer_callback),this));
}


<<<<<<< HEAD
void neosprite_base_device::start_sprite_line_timer(  )
=======
void neosprite_base_device::start_sprite_line_timer()
>>>>>>> upstream/master
{
	m_sprite_line_timer->adjust(m_screen->time_until_pos(0));
}


<<<<<<< HEAD
UINT32 neosprite_base_device::get_region_mask(UINT8* rgn, UINT32 rgn_size)
{
	/* convert the sprite graphics data into a format that
	   allows faster blitting */
	UINT32 mask;
	UINT32 len;
	UINT32 bit;
=======
uint32_t neosprite_base_device::get_region_mask(uint8_t* rgn, uint32_t rgn_size)
{
	/* convert the sprite graphics data into a format that
	   allows faster blitting */
	uint32_t mask;
	uint32_t len;
	uint32_t bit;
>>>>>>> upstream/master

	/* get mask based on the length rounded up to the nearest
	   power of 2 */
	mask = 0xffffffff;

	len = rgn_size;

	for (bit = 0x80000000; bit != 0; bit >>= 1)
	{
		if ((len * 2 - 1) & bit)
			break;

		mask >>= 1;
	}

	return mask;
}

void neosprite_base_device::optimize_sprite_data()
{
	// this does nothing in this implementation, it's used by neosprite_optimized_device
	// m_sprite_gfx_address_mask gets set when the GFX region is assigned
	return;
}

<<<<<<< HEAD
void neosprite_base_device::set_optimized_sprite_data(UINT8* sprdata, UINT32 mask)
=======
void neosprite_base_device::set_optimized_sprite_data(uint8_t* sprdata, uint32_t mask)
>>>>>>> upstream/master
{
	return;
}

<<<<<<< HEAD

// these are for passing in pointers from the main system
void neosprite_base_device::set_sprite_region(UINT8* region_sprites, UINT32 region_sprites_size)
=======
// these are for passing in pointers from the main system
void neosprite_base_device::set_sprite_region(uint8_t* region_sprites, uint32_t region_sprites_size)
>>>>>>> upstream/master
{
	m_region_sprites = region_sprites;
	m_region_sprites_size = region_sprites_size;
}

<<<<<<< HEAD
void neosprite_base_device::set_fixed_regions(UINT8* fix_cart, UINT32 fix_cart_size, memory_region* fix_bios)
=======
void neosprite_base_device::set_fixed_regions(uint8_t* fix_cart, uint32_t fix_cart_size, memory_region* fix_bios)
>>>>>>> upstream/master
{
	m_region_fixed = fix_cart;
	m_region_fixed_size = fix_cart_size;
	m_region_fixedbios = fix_bios;
}

void neosprite_base_device::set_screen(screen_device* screen)
{
	m_screen = screen;
}

void neosprite_base_device::set_pens(const pen_t* pens)
{
	m_pens = pens;
}



/*********************************************************************************************************************************/
/* Regular NeoGeo sprite handling - drawing directly from ROM (or RAM on NeoCD)                                                  */
/*                                                                                                                               */
/* note, we don't currently use this implementation, reference only                                                              */
/* if we do it will be important to ensure that all sprite regions are ^2 sizes - the optimized routine automatically allocates  */
/* ^2 sized regions when pre-decoding, but obviously we don't here, so if we want to be safe we'll have to adjust the actual     */
/* regions          (alternatively I could add an additional size check in the draw routine, but that would be slower)           */
/*********************************************************************************************************************************/

<<<<<<< HEAD
const device_type NEOGEO_SPRITE_REGULAR = &device_creator<neosprite_regular_device>;

neosprite_regular_device::neosprite_regular_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock)
	: neosprite_base_device(mconfig, tag, owner, clock, NEOGEO_SPRITE_REGULAR)
{
}



void neosprite_regular_device::set_sprite_region(UINT8* region_sprites, UINT32 region_sprites_size)
=======
DEFINE_DEVICE_TYPE(NEOGEO_SPRITE_REGULAR, neosprite_regular_device, "neosprite_reg", "Neo-Geo Sprites (regular)")

neosprite_regular_device::neosprite_regular_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock)
	: neosprite_base_device(mconfig, NEOGEO_SPRITE_REGULAR, tag, owner, clock)
{
}

void neosprite_regular_device::set_sprite_region(uint8_t* region_sprites, uint32_t region_sprites_size)
>>>>>>> upstream/master
{
	m_region_sprites = region_sprites;
	m_region_sprites_size = region_sprites_size;

<<<<<<< HEAD
	UINT32 mask = get_region_mask(m_region_sprites, m_region_sprites_size);
	UINT32 proper_size = (mask + 1) >>1;
=======
	uint32_t mask = get_region_mask(m_region_sprites, m_region_sprites_size);
	uint32_t proper_size = (mask + 1) >>1;
>>>>>>> upstream/master

	printf("lengths %08x %08x m_region_sprites", region_sprites_size, proper_size);

	if (m_region_sprites_size != proper_size)
	{
		fatalerror("please use power of 2 region sizes with neosprite_base_device to ensure masking works correctly");
	}

	m_sprite_gfx_address_mask = mask;
}

<<<<<<< HEAD
inline void neosprite_regular_device::draw_pixel(int romaddr, UINT32* dst, const pen_t *line_pens)
{
	const UINT8* src = m_region_sprites + (((romaddr &~0xff)>>1) | (((romaddr&0x8)^0x8)<<3) | ((romaddr & 0xf0)  >> 2));
	const int x = romaddr & 0x7;

	const UINT8 gfx = (((src[0x3] >> x) & 0x01) << 3) |
=======
inline void neosprite_regular_device::draw_pixel(int romaddr, uint32_t* dst, const pen_t *line_pens)
{
	const uint8_t* src = m_region_sprites + (((romaddr &~0xff)>>1) | (((romaddr&0x8)^0x8)<<3) | ((romaddr & 0xf0)  >> 2));
	const int x = romaddr & 0x7;

	const uint8_t gfx = (((src[0x3] >> x) & 0x01) << 3) |
>>>>>>> upstream/master
						(((src[0x1] >> x) & 0x01) << 2) |
						(((src[0x2] >> x) & 0x01) << 1) |
						(((src[0x0] >> x) & 0x01) << 0);

	if (gfx)
		*dst = line_pens[gfx];
}



/*********************************************************************************************************************************/
/* Regular NeoGeo sprite handling with pre-decode optimization                                                                   */
/*                                                                                                                               */
/* this is closer to the old MAME implementation where the 4bpp graphics have been expanded to an easier to draw 8bpp format     */
/* for additional speed                                                                                                          */
/*********************************************************************************************************************************/

<<<<<<< HEAD
const device_type NEOGEO_SPRITE_OPTIMZIED = &device_creator<neosprite_optimized_device>;

neosprite_optimized_device::neosprite_optimized_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock)
	: neosprite_base_device(mconfig, tag, owner, clock, NEOGEO_SPRITE_OPTIMZIED),
	m_spritegfx8(0)
{
}


void neosprite_optimized_device::optimize_sprite_data()
{
	m_sprite_gfx_address_mask = neogeohelper_optimize_sprite_data(m_sprite_gfx, m_region_sprites, m_region_sprites_size);
	m_spritegfx8 = &m_sprite_gfx[0];
}

void neosprite_optimized_device::set_optimized_sprite_data(UINT8* sprdata, UINT32 mask)
{
	m_spritegfx8 = sprdata;
	m_sprite_gfx_address_mask = mask;
}

inline void neosprite_optimized_device::draw_pixel(int romaddr, UINT32* dst, const pen_t *line_pens)
{
	const UINT8 gfx = m_spritegfx8[romaddr];
=======
DEFINE_DEVICE_TYPE(NEOGEO_SPRITE_OPTIMZIED, neosprite_optimized_device, "neosprite_opt", "Neo-Geo Sprites (optimized)")

neosprite_optimized_device::neosprite_optimized_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock)
	: neosprite_base_device(mconfig, NEOGEO_SPRITE_OPTIMZIED, tag, owner, clock)
	, m_spritegfx8(nullptr)
{
}

uint32_t neosprite_optimized_device::optimize_helper(std::vector<uint8_t> &spritegfx, uint8_t* region_sprites, uint32_t region_sprites_size)
{
	// convert the sprite graphics data into a format that allows faster blitting
	uint8_t *src;
	uint8_t *dest;

	uint32_t mask = get_region_mask(region_sprites, region_sprites_size);

	spritegfx.resize(mask + 1);
	uint32_t spritegfx_address_mask = mask;

	src = region_sprites;
	dest = &spritegfx[0];

	for (unsigned i = 0; i < region_sprites_size; i += 0x80, src += 0x80)
	{
		for (unsigned y = 0; y < 0x10; y++)
		{
			for (unsigned x = 0; x < 8; x++)
			{
				*(dest++) = (((src[0x43 | (y << 2)] >> x) & 0x01) << 3) |
				(((src[0x41 | (y << 2)] >> x) & 0x01) << 2) |
				(((src[0x42 | (y << 2)] >> x) & 0x01) << 1) |
				(((src[0x40 | (y << 2)] >> x) & 0x01) << 0);
			}

			for (unsigned x = 0; x < 8; x++)
			{
				*(dest++) = (((src[0x03 | (y << 2)] >> x) & 0x01) << 3) |
				(((src[0x01 | (y << 2)] >> x) & 0x01) << 2) |
				(((src[0x02 | (y << 2)] >> x) & 0x01) << 1) |
				(((src[0x00 | (y << 2)] >> x) & 0x01) << 0);
			}
		}
	}

	return spritegfx_address_mask;
}


void neosprite_optimized_device::optimize_sprite_data()
{
	m_sprite_gfx_address_mask = optimize_helper(m_sprite_gfx, m_region_sprites, m_region_sprites_size);
	m_spritegfx8 = &m_sprite_gfx[0];
}

void neosprite_optimized_device::set_optimized_sprite_data(uint8_t* sprdata, uint32_t mask)
{
	m_sprite_gfx_address_mask = mask;
	m_spritegfx8 = &sprdata[0];
}

inline void neosprite_optimized_device::draw_pixel(int romaddr, uint32_t* dst, const pen_t *line_pens)
{
	const uint8_t gfx = m_spritegfx8[romaddr];
>>>>>>> upstream/master

	if (gfx)
		*dst = line_pens[gfx];
}


/*********************************************************************************************************************************/
/* MIDAS specific sprite handling                                                                                                */
/*                                                                                                                               */
/* this is used by the midas.c hardware which is a reengineered NeoGeo, it has 8bbp tiles instead of 4bpp tiles                  */
/* and uploads the zoom table.  The additional videoram buffering is a guess because 'hammer' is very glitchy without it         */
/*********************************************************************************************************************************/

<<<<<<< HEAD
const device_type NEOGEO_SPRITE_MIDAS = &device_creator<neosprite_midas_device>;


neosprite_midas_device::neosprite_midas_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock)
	: neosprite_base_device(mconfig, tag, owner, clock, NEOGEO_SPRITE_MIDAS)
=======
DEFINE_DEVICE_TYPE(NEOGEO_SPRITE_MIDAS, neosprite_midas_device, "midassprite", "MIDAS Sprites")


neosprite_midas_device::neosprite_midas_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock)
	: neosprite_base_device(mconfig, NEOGEO_SPRITE_MIDAS, tag, owner, clock)
>>>>>>> upstream/master
{
	m_bppshift = 8;
}


<<<<<<< HEAD
inline void neosprite_midas_device::draw_pixel(int romaddr, UINT32* dst, const pen_t *line_pens)
{
	const UINT8* src = m_region_sprites + (((romaddr &~0xff)) | (((romaddr&0x8)^0x8)<<4) | ((romaddr & 0xf0)  >> 1));
	const int x = romaddr & 0x7;

	const UINT8 gfx =   (((src[0x7] >> x) & 0x01) << 7) |
=======
inline void neosprite_midas_device::draw_pixel(int romaddr, uint32_t* dst, const pen_t *line_pens)
{
	const uint8_t* src = m_region_sprites + (((romaddr &~0xff)) | (((romaddr&0x8)^0x8)<<4) | ((romaddr & 0xf0)  >> 1));
	const int x = romaddr & 0x7;

	const uint8_t gfx =   (((src[0x7] >> x) & 0x01) << 7) |
>>>>>>> upstream/master
						(((src[0x6] >> x) & 0x01) << 6) |
						(((src[0x5] >> x) & 0x01) << 5) |
						(((src[0x4] >> x) & 0x01) << 4) |
						(((src[0x3] >> x) & 0x01) << 3) |
						(((src[0x2] >> x) & 0x01) << 2) |
						(((src[0x1] >> x) & 0x01) << 1) |
						(((src[0x0] >> x) & 0x01) << 0);

	if (gfx)
		*dst = line_pens[gfx];
}


void neosprite_midas_device::device_start()
{
	neosprite_base_device::device_start();

<<<<<<< HEAD
	m_videoram_buffer = auto_alloc_array(machine(), UINT16, 0x8000 + 0x800);
	m_videoram_drawsource = m_videoram_buffer;

	memset(m_videoram_buffer, 0x00, (0x8000 + 0x800) * sizeof(UINT16));
=======
	m_videoram_buffer = std::make_unique<uint16_t[]>(0x8000 + 0x800);
	m_videoram_drawsource = m_videoram_buffer.get();

	memset(m_videoram_buffer.get(), 0x00, (0x8000 + 0x800) * sizeof(uint16_t));
>>>>>>> upstream/master

}

void neosprite_midas_device::buffer_vram()
{
<<<<<<< HEAD
	memcpy(m_videoram_buffer, m_videoram, (0x8000 + 0x800) * sizeof(UINT16));
}

inline void neosprite_midas_device::draw_fixed_layer_2pixels(UINT32*&pixel_addr, int offset, UINT8* gfx_base, const pen_t* char_pens)
{
	UINT8 data;
=======
	memcpy(m_videoram_buffer.get(), m_videoram.get(), (0x8000 + 0x800) * sizeof(uint16_t));
}

inline void neosprite_midas_device::draw_fixed_layer_2pixels(uint32_t*&pixel_addr, int offset, uint8_t* gfx_base, const pen_t* char_pens)
{
	uint8_t data;
>>>>>>> upstream/master

	data = ((gfx_base[(offset * 2)+0] & 0x0f)<<0) | ((gfx_base[(offset * 2)+1] & 0x0f)<<4);
	if (data)
		*pixel_addr = char_pens[data];
	pixel_addr++;

	data = ((gfx_base[(offset * 2)+0] & 0xf0)>>4) | ((gfx_base[(offset * 2)+1] & 0xf0)<<0);
	if (data)
		*pixel_addr = char_pens[data];
	pixel_addr++;
}

<<<<<<< HEAD
void neosprite_midas_device::set_sprite_region(UINT8* region_sprites, UINT32 region_sprites_size)
{
	m_region_sprites = region_sprites;
	m_region_sprites_size = region_sprites_size;
	UINT32 mask = get_region_mask(m_region_sprites, m_region_sprites_size);
=======
void neosprite_midas_device::set_sprite_region(uint8_t* region_sprites, uint32_t region_sprites_size)
{
	m_region_sprites = region_sprites;
	m_region_sprites_size = region_sprites_size;
	uint32_t mask = get_region_mask(m_region_sprites, m_region_sprites_size);
>>>>>>> upstream/master
	m_sprite_gfx_address_mask = mask;
}
