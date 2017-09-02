// license:BSD-3-Clause
// copyright-holders:David Haywood
/*

macs.c - Multi Amenity Cassette System

processor seems to be ST0016 (z80 based) from SETA

around 0x3700 of the bios (when interleaved) contains the ram test text

TODO:
(general)
-Hook-Up bios.
(yujan)
-Girls disappears when you win.
-Some gfx are offset.


----- Game Notes -----

Kisekae Mahjong  (c)1995 I'MAX
Kisekae Hanafuda (c)1995 I'MAX
Seimei-Kantei-Meimei-Ki Cult Name (c)1996 I'MAX

KISEKAE -- info

* DIP SWITCH *

                      | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 |
-------------------------------------------------------
 P2 Level |  Normal   |off|off|                       |
          |   Weak    |on |off|                       |
          |  Strong   |off|on |                       |
          |Very strong|on |on |                       |
-------------------------------------------------------
 P2 Points|  Normal   |       |off|off|               |
          |  Easy     |       |on |off|               |
          |  Hard     |       |off|on |               |
          | Very hard |       |on |on |               |
-------------------------------------------------------
 P1       |  1000pts  |               |off|           |
 points   |  2000pts  |               |on |           |
-------------------------------------------------------
  Auto    |   Yes     |                   |off|       |
  tumo    |   No      |                   |on |       |
-------------------------------------------------------
  Not     |           |                       |off|   |
  Used    |           |                       |on |   |
-------------------------------------------------------
  Tumo    |   Long    |                           |off|
  time    |   Short   |                           |on |
-------------------------------------------------------

* at slotA -> DIP SW3
     slotB -> DIP SW4


*/

#include "emu.h"
#include "machine/st0016.h"

<<<<<<< HEAD
=======
#include "bus/generic/slot.h"
#include "bus/generic/carts.h"
>>>>>>> upstream/master

class macs_state : public driver_device
{
public:
	macs_state(const machine_config &mconfig, device_type type, const char *tag)
		: driver_device(mconfig, type, tag),
<<<<<<< HEAD
			m_ram2(*this, "ram2"),
			m_maincpu(*this,"maincpu")

			{ }

	UINT8 m_mux_data;
	UINT8 m_rev;
	UINT8 *m_ram1;
	required_shared_ptr<UINT8> m_ram2;
=======
			m_cart_bank(0),
			m_ram2(*this, "ram2"),
			m_maincpu(*this,"maincpu"),
			m_cart1(*this, "slot_a"),
			m_cart2(*this, "slot_b")
			{ }

	uint8_t m_mux_data;
	uint8_t m_rev;
	uint8_t m_cart_bank;
	std::unique_ptr<uint8_t[]> m_ram1;
	required_shared_ptr<uint8_t> m_ram2;
>>>>>>> upstream/master
	DECLARE_WRITE8_MEMBER(rambank_w);
	DECLARE_READ8_MEMBER(macs_input_r);
	DECLARE_WRITE8_MEMBER(macs_rom_bank_w);
	DECLARE_WRITE8_MEMBER(macs_output_w);
	DECLARE_DRIVER_INIT(macs);
	DECLARE_DRIVER_INIT(kisekaeh);
	DECLARE_DRIVER_INIT(kisekaem);
	DECLARE_DRIVER_INIT(macs2);
	DECLARE_MACHINE_RESET(macs);
<<<<<<< HEAD

	UINT32 screen_update_macs(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);

	optional_device<st0016_cpu_device> m_maincpu;
=======
	DECLARE_MACHINE_START(macs);
	ST0016_DMA_OFFS_CB(dma_offset);

	uint32_t screen_update_macs(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);

	optional_device<st0016_cpu_device> m_maincpu;
	optional_device<generic_slot_device> m_cart1;
	optional_device<generic_slot_device> m_cart2;
>>>>>>> upstream/master

};



<<<<<<< HEAD


=======
>>>>>>> upstream/master
static ADDRESS_MAP_START( macs_mem, AS_PROGRAM, 8, macs_state )
	AM_RANGE(0x0000, 0x7fff) AM_ROMBANK("bank4")
	AM_RANGE(0x8000, 0xbfff) AM_ROMBANK("bank1")
	//AM_RANGE(0xc000, 0xcfff) AM_READ(st0016_sprite_ram_r) AM_WRITE(st0016_sprite_ram_w)
	//AM_RANGE(0xd000, 0xdfff) AM_READ(st0016_sprite2_ram_r) AM_WRITE(st0016_sprite2_ram_w)
	AM_RANGE(0xe000, 0xe7ff) AM_RAM /* work ram ? */
	AM_RANGE(0xe800, 0xe87f) AM_RAM AM_SHARE("ram2")
	//AM_RANGE(0xe900, 0xe9ff) // sound - internal
	//AM_RANGE(0xea00, 0xebff) AM_READ(st0016_palette_ram_r) AM_WRITE(st0016_palette_ram_w)
	//AM_RANGE(0xec00, 0xec1f) AM_READ(st0016_character_ram_r) AM_WRITE(st0016_character_ram_w)
	AM_RANGE(0xf000, 0xf7ff) AM_RAMBANK("bank3") /* common /backup ram ?*/
	AM_RANGE(0xf800, 0xffff) AM_RAMBANK("bank2") /* common /backup ram ?*/
ADDRESS_MAP_END

WRITE8_MEMBER(macs_state::rambank_w)
{
<<<<<<< HEAD
	membank("bank3")->set_base(&m_ram1[0x10000+(data&1)*0x800] );
=======
	membank("bank3")->set_entry(2 + (data & 1));
>>>>>>> upstream/master
}

READ8_MEMBER(macs_state::macs_input_r)
{
	switch(offset)
	{
		case 0:
		{
			/*It's bit-wise*/
			switch(m_mux_data&0x0f)
			{
				case 0x00: return ioport("IN0")->read();
				case 0x01: return ioport("IN1")->read();
				case 0x02: return ioport("IN2")->read();
				case 0x04: return ioport("IN3")->read();
				case 0x08: return ioport("IN4")->read();
				default:
				logerror("Unmapped mahjong panel mux data %02x\n",m_mux_data);
				return 0xff;
			}
		}
		case 1: return ioport("SYS0")->read();
		case 2: return ioport("DSW0")->read();
		case 3: return ioport("DSW1")->read();
		case 4: return ioport("DSW2")->read();
		case 5: return ioport("DSW3")->read();
		case 6: return ioport("DSW4")->read();
		case 7: return ioport("SYS1")->read();
		default:    popmessage("Unmapped I/O read at PC = %06x offset = %02x",space.device().safe_pc(),offset+0xc0);
	}

	return 0xff;
}


WRITE8_MEMBER(macs_state::macs_rom_bank_w)
{
<<<<<<< HEAD
	membank("bank1")->set_base(memregion("maincpu")->base() + (data* 0x4000) + macs_cart_slot*0x400000 );

//  m_st0016_rom_bank=data;
=======
	membank("bank1")->set_entry(m_cart_bank * 0x100 + data);
>>>>>>> upstream/master
}

WRITE8_MEMBER(macs_state::macs_output_w)
{
<<<<<<< HEAD
	UINT8 *ROM = memregion("maincpu")->base();

=======
>>>>>>> upstream/master
	switch(offset)
	{
		case 0:
		/*
		--x- ---- sets RAM bank?
		---- -x-- Cassette B slot
		---- --x- Cassette A slot
		*/

		if(m_rev == 1)
		{
<<<<<<< HEAD
			/* FIXME: dunno if this RAM bank is right, DASM tracking made on the POST screens indicates that there's just one RAM bank,
			          but then MACS2 games locks up. */
			membank("bank3")->set_base(&m_ram1[((data&0x20)>>5)*0x1000+0x000] );

			macs_cart_slot = (data & 0xc) >> 2;

			membank("bank4")->set_base(&ROM[macs_cart_slot*0x400000] );
		}

		membank("bank2")->set_base(&m_ram1[((data&0x20)>>5)*0x1000+0x800] );
=======
			/* FIXME: dunno if this RAM bank is right, DASM tracking made on the POST
			    screens indicates that there's just one RAM bank, but then MACS2 games
			    locks up. */
			membank("bank3")->set_entry(BIT(data, 5));

			m_cart_bank = (data & 0xc) >> 2;
			membank("bank4")->set_entry(m_cart_bank * 0x100);
		}

		membank("bank2")->set_entry(BIT(data, 5));
>>>>>>> upstream/master
		break;
		case 2: m_mux_data = data; break;

	}
}

static ADDRESS_MAP_START( macs_io, AS_IO, 8, macs_state )
	ADDRESS_MAP_GLOBAL_MASK(0xff)
	//AM_RANGE(0x00, 0xbf) AM_READ(st0016_vregs_r) AM_WRITE(st0016_vregs_w) /* video/crt regs ? */
	AM_RANGE(0xc0, 0xc7) AM_READWRITE(macs_input_r,macs_output_w)
	AM_RANGE(0xe0, 0xe0) AM_WRITENOP /* renju = $40, neratte = 0 */
	AM_RANGE(0xe1, 0xe1) AM_WRITE(macs_rom_bank_w)
	//AM_RANGE(0xe2, 0xe2) AM_WRITE(st0016_sprite_bank_w)
	//AM_RANGE(0xe3, 0xe4) AM_WRITE(st0016_character_bank_w)
	//AM_RANGE(0xe5, 0xe5) AM_WRITE(st0016_palette_bank_w)
	AM_RANGE(0xe6, 0xe6) AM_WRITE(rambank_w) /* banking ? ram bank ? shared rambank ? */
	AM_RANGE(0xe7, 0xe7) AM_WRITENOP /* watchdog */
	//AM_RANGE(0xf0, 0xf0) AM_READ(st0016_dma_r)
ADDRESS_MAP_END

//static GFXDECODE_START( macs )
<<<<<<< HEAD
//  GFXDECODE_ENTRY( NULL, 0, charlayout,      0, 16*4  )
//GFXDECODE_END

static INPUT_PORTS_START( macs_base )
	/*0*/
=======
//  GFXDECODE_ENTRY( nullptr, 0, charlayout,      0, 16*4  )
//GFXDECODE_END

static INPUT_PORTS_START( macs_base )
>>>>>>> upstream/master
	PORT_START("DSW0")
	PORT_DIPNAME( 0x01, 0x01, "DSW0 - BIT 1" )
	PORT_DIPSETTING(    0x01, DEF_STR( Off ) )
	PORT_DIPSETTING(    0x00, DEF_STR( On ) )
	PORT_DIPNAME( 0x02, 0x02, "DSW0 - BIT 2" )
	PORT_DIPSETTING(    0x02, DEF_STR( Off ) )
	PORT_DIPSETTING(    0x00, DEF_STR( On ) )
	PORT_DIPNAME( 0x04, 0x04, "DSW0 - BIT 4" )
	PORT_DIPSETTING(    0x04, DEF_STR( Off ) )
	PORT_DIPSETTING(    0x00, DEF_STR( On ) )
	PORT_DIPNAME( 0x08, 0x08, "DSW0 - BIT 8" )
	PORT_DIPSETTING(    0x08, DEF_STR( Off ) )
	PORT_DIPSETTING(    0x00, DEF_STR( On ) )
	PORT_DIPNAME( 0x10, 0x10, "DSW0 - BIT 10" )
	PORT_DIPSETTING(    0x10, DEF_STR( Off ) )
	PORT_DIPSETTING(    0x00, DEF_STR( On ) )
	PORT_DIPNAME( 0x20, 0x20, "DSW0 - BIT 20" )
	PORT_DIPSETTING(    0x20, DEF_STR( Off ) )
	PORT_DIPSETTING(    0x00, DEF_STR( On ) )
	PORT_DIPNAME( 0x40, 0x40, "DSW0 - BIT 40" )
	PORT_DIPSETTING(    0x40, DEF_STR( Off ) )
	PORT_DIPSETTING(    0x00, DEF_STR( On ) )
	PORT_DIPNAME( 0x80, 0x80, "DSW0 - BIT 80" )
	PORT_DIPSETTING(    0x80, DEF_STR( Off ) )
	PORT_DIPSETTING(    0x00, DEF_STR( On ) )

<<<<<<< HEAD
	/*1*/
=======
>>>>>>> upstream/master
	PORT_START("DSW1")
	PORT_DIPNAME( 0x01, 0x01, "DSW1 - BIT 1" )
	PORT_DIPSETTING(    0x01, DEF_STR( Off ) )
	PORT_DIPSETTING(    0x00, DEF_STR( On ) )
	PORT_DIPNAME( 0x02, 0x02, "DSW1 - BIT 2" )
	PORT_DIPSETTING(    0x02, DEF_STR( Off ) )
	PORT_DIPSETTING(    0x00, DEF_STR( On ) )
	PORT_DIPNAME( 0x04, 0x04, "DSW1 - BIT 4" )
	PORT_DIPSETTING(    0x04, DEF_STR( Off ) )
	PORT_DIPSETTING(    0x00, DEF_STR( On ) )
	PORT_DIPNAME( 0x08, 0x08, "DSW1 - BIT 8" )
	PORT_DIPSETTING(    0x08, DEF_STR( Off ) )
	PORT_DIPSETTING(    0x00, DEF_STR( On ) )
	PORT_DIPNAME( 0x10, 0x10, "DSW1 - BIT 10" )
	PORT_DIPSETTING(    0x10, DEF_STR( Off ) )
	PORT_DIPSETTING(    0x00, DEF_STR( On ) )
	PORT_DIPNAME( 0x20, 0x20, "DSW1 - BIT 20" )
	PORT_DIPSETTING(    0x20, DEF_STR( Off ) )
	PORT_DIPSETTING(    0x00, DEF_STR( On ) )
	PORT_DIPNAME( 0x40, 0x40, "DSW1 - BIT 40" )
	PORT_DIPSETTING(    0x40, DEF_STR( Off ) )
	PORT_DIPSETTING(    0x00, DEF_STR( On ) )
	PORT_DIPNAME( 0x80, 0x80, "DSW1 - BIT 80" )
	PORT_DIPSETTING(    0x80, DEF_STR( Off ) )
	PORT_DIPSETTING(    0x00, DEF_STR( On ) )

<<<<<<< HEAD
	/*2*/
=======
>>>>>>> upstream/master
	PORT_START("DSW2")
	PORT_DIPNAME( 0x01, 0x01, "DSW2 - BIT 1" )
	PORT_DIPSETTING(    0x01, DEF_STR( Off ) )
	PORT_DIPSETTING(    0x00, DEF_STR( On ) )
	PORT_DIPNAME( 0x02, 0x02, "DSW2 - BIT 2" )
	PORT_DIPSETTING(    0x02, DEF_STR( Off ) )
	PORT_DIPSETTING(    0x00, DEF_STR( On ) )
	PORT_DIPNAME( 0x04, 0x04, "DSW2 - BIT 4" )
	PORT_DIPSETTING(    0x04, DEF_STR( Off ) )
	PORT_DIPSETTING(    0x00, DEF_STR( On ) )
	PORT_DIPNAME( 0x08, 0x08, "DSW2 - BIT 8" )
	PORT_DIPSETTING(    0x08, DEF_STR( Off ) )
	PORT_DIPSETTING(    0x00, DEF_STR( On ) )
	PORT_DIPNAME( 0x10, 0x10, "DSW2 - BIT 10" )
	PORT_DIPSETTING(    0x10, DEF_STR( Off ) )
	PORT_DIPSETTING(    0x00, DEF_STR( On ) )
	PORT_DIPNAME( 0x20, 0x20, "DSW2 - BIT 20" )
	PORT_DIPSETTING(    0x20, DEF_STR( Off ) )
	PORT_DIPSETTING(    0x00, DEF_STR( On ) )
	PORT_DIPNAME( 0x40, 0x40, "DSW2 - BIT 40" )
	PORT_DIPSETTING(    0x40, DEF_STR( Off ) )
	PORT_DIPSETTING(    0x00, DEF_STR( On ) )
	PORT_DIPNAME( 0x80, 0x80, "DSW2 - BIT 80" )
	PORT_DIPSETTING(    0x80, DEF_STR( Off ) )
	PORT_DIPSETTING(    0x00, DEF_STR( On ) )

<<<<<<< HEAD
	/*3*/
=======
>>>>>>> upstream/master
	PORT_START("DSW3")
	PORT_DIPNAME( 0x01, 0x01, "DSW3 - BIT 1" )
	PORT_DIPSETTING(    0x01, DEF_STR( Off ) )
	PORT_DIPSETTING(    0x00, DEF_STR( On ) )
	PORT_DIPNAME( 0x02, 0x02, "DSW3 - BIT 2" )
	PORT_DIPSETTING(    0x02, DEF_STR( Off ) )
	PORT_DIPSETTING(    0x00, DEF_STR( On ) )
	PORT_DIPNAME( 0x04, 0x04, DEF_STR( Demo_Sounds ) )
	PORT_DIPSETTING(    0x00, DEF_STR( Off ) )
	PORT_DIPSETTING(    0x04, DEF_STR( On ) )
	PORT_DIPNAME( 0x08, 0x00, "Game" )
	PORT_DIPSETTING(    0x08, "Bet Type" )
	PORT_DIPSETTING(    0x00, "Normal Type" )
	PORT_DIPNAME( 0x10, 0x10, DEF_STR( Level_Select ) )
	PORT_DIPSETTING(    0x00, DEF_STR( Off ) )
	PORT_DIPSETTING(    0x10, DEF_STR( On ) )
	PORT_DIPNAME( 0x20, 0x20, "Memory Reset" )
	PORT_DIPSETTING(    0x20, DEF_STR( Off ) )
	PORT_DIPSETTING(    0x00, DEF_STR( On ) )
	PORT_DIPNAME( 0x40, 0x40, "Analyzer" )
	PORT_DIPSETTING(    0x40, DEF_STR( Off ) )
	PORT_DIPSETTING(    0x00, DEF_STR( On ) )
	PORT_DIPNAME( 0x80, 0x80, "Test Mode" )
	PORT_DIPSETTING(    0x80, DEF_STR( Off ) )
	PORT_DIPSETTING(    0x00, DEF_STR( On ) )

<<<<<<< HEAD
	/*4 - external (printer  in cultname)*/
=======
	// external (printer  in cultname)
>>>>>>> upstream/master
	PORT_START("DSW4")
	PORT_DIPNAME( 0x01, 0x01, "DSW4 - BIT 1" )
	PORT_DIPSETTING(    0x01, DEF_STR( Off ) )
	PORT_DIPSETTING(    0x00, DEF_STR( On ) )
	PORT_DIPNAME( 0x02, 0x02, "DSW4 - BIT 2" )
	PORT_DIPSETTING(    0x02, DEF_STR( Off ) )
	PORT_DIPSETTING(    0x00, DEF_STR( On ) )
	PORT_DIPNAME( 0x04, 0x04, "DSW4 - BIT 4" )
	PORT_DIPSETTING(    0x04, DEF_STR( Off ) )
	PORT_DIPSETTING(    0x00, DEF_STR( On ) )
	PORT_DIPNAME( 0x08, 0x08, "DSW4 - BIT 8" )
	PORT_DIPSETTING(    0x08, DEF_STR( Off ) )
	PORT_DIPSETTING(    0x00, DEF_STR( On ) )
	PORT_DIPNAME( 0x10, 0x10, "DSW4 - BIT 10" )
	PORT_DIPSETTING(    0x10, DEF_STR( Off ) )
	PORT_DIPSETTING(    0x00, DEF_STR( On ) )
	PORT_DIPNAME( 0x20, 0x20, "DSW4 - BIT 20" )
	PORT_DIPSETTING(    0x20, DEF_STR( Off ) )
	PORT_DIPSETTING(    0x00, DEF_STR( On ) )
	PORT_DIPNAME( 0x40, 0x40, "DSW4 - BIT 40" )
	PORT_DIPSETTING(    0x40, DEF_STR( Off ) )
	PORT_DIPSETTING(    0x00, DEF_STR( On ) )
	PORT_DIPNAME( 0x80, 0x00, "DSW4 - BIT 80" )
	PORT_DIPSETTING(    0x80, DEF_STR( Off ) )
	PORT_DIPSETTING(    0x00, DEF_STR( On ) )

<<<<<<< HEAD
	/*
	Note: These could likely to be switches that are on the game board and not Dip Switches
	*/
=======
	//Note: These could likely to be switches that are on the game board and not Dip Switches
>>>>>>> upstream/master
	PORT_START("SYS0")
	PORT_BIT( 0x7f, IP_ACTIVE_LOW, IPT_UNUSED )
	PORT_BIT( 0x80, IP_ACTIVE_LOW, IPT_OTHER ) PORT_NAME("Note In") PORT_CODE(KEYCODE_4_PAD)

	PORT_START("SYS1")
	PORT_BIT( 0x01, IP_ACTIVE_LOW, IPT_COIN1 )
	PORT_BIT( 0x02, IP_ACTIVE_LOW, IPT_OTHER ) PORT_NAME("Clear Coin Counter") PORT_CODE(KEYCODE_1_PAD)
<<<<<<< HEAD
	PORT_BIT( 0x04, IP_ACTIVE_LOW, IPT_OTHER ) PORT_NAME("Memory Reset Key") PORT_CODE(KEYCODE_2_PAD)
=======
	PORT_BIT( 0x04, IP_ACTIVE_LOW, IPT_MEMORY_RESET ) PORT_CODE(KEYCODE_2_PAD)
>>>>>>> upstream/master
	PORT_BIT( 0x08, IP_ACTIVE_LOW, IPT_OTHER ) PORT_NAME("Analyzer Key") PORT_CODE(KEYCODE_3_PAD)
	PORT_BIT( 0xf0, IP_ACTIVE_LOW, IPT_UNUSED )
INPUT_PORTS_END

static INPUT_PORTS_START( macs_m )
	PORT_INCLUDE( macs_base )

<<<<<<< HEAD
	/*MAHJONG PANEL*/
=======
	// MAHJONG PANEL
>>>>>>> upstream/master
	PORT_START("IN0")
	PORT_BIT( 0x01, IP_ACTIVE_LOW, IPT_MAHJONG_LAST_CHANCE )
	PORT_BIT( 0x02, IP_ACTIVE_LOW, IPT_MAHJONG_SCORE )
	PORT_BIT( 0x04, IP_ACTIVE_LOW, IPT_MAHJONG_DOUBLE_UP )
	PORT_BIT( 0x08, IP_ACTIVE_LOW, IPT_MAHJONG_FLIP_FLOP )
	PORT_BIT( 0x10, IP_ACTIVE_LOW, IPT_MAHJONG_BIG )
	PORT_BIT( 0x20, IP_ACTIVE_LOW, IPT_MAHJONG_SMALL )
	PORT_BIT( 0xc0, IP_ACTIVE_LOW, IPT_UNUSED )

	PORT_START("IN1")
	PORT_BIT( 0x01, IP_ACTIVE_LOW, IPT_MAHJONG_A )
	PORT_BIT( 0x02, IP_ACTIVE_LOW, IPT_MAHJONG_E )
	PORT_BIT( 0x04, IP_ACTIVE_LOW, IPT_MAHJONG_I )
	PORT_BIT( 0x08, IP_ACTIVE_LOW, IPT_MAHJONG_M )
	PORT_BIT( 0x10, IP_ACTIVE_LOW, IPT_MAHJONG_KAN )
	PORT_BIT( 0x20, IP_ACTIVE_LOW, IPT_START1 )
	PORT_BIT( 0xc0, IP_ACTIVE_LOW, IPT_UNUSED )

	PORT_START("IN2")
	PORT_BIT( 0x01, IP_ACTIVE_LOW, IPT_MAHJONG_B )
	PORT_BIT( 0x02, IP_ACTIVE_LOW, IPT_MAHJONG_F )
	PORT_BIT( 0x04, IP_ACTIVE_LOW, IPT_MAHJONG_J )
	PORT_BIT( 0x08, IP_ACTIVE_LOW, IPT_MAHJONG_N )
	PORT_BIT( 0x10, IP_ACTIVE_LOW, IPT_MAHJONG_REACH )
	PORT_BIT( 0x20, IP_ACTIVE_LOW, IPT_MAHJONG_BET )
	PORT_BIT( 0xc0, IP_ACTIVE_LOW, IPT_UNUSED )

	PORT_START("IN3")
	PORT_BIT( 0x01, IP_ACTIVE_LOW, IPT_MAHJONG_C )
	PORT_BIT( 0x02, IP_ACTIVE_LOW, IPT_MAHJONG_G )
	PORT_BIT( 0x04, IP_ACTIVE_LOW, IPT_MAHJONG_K )
	PORT_BIT( 0x08, IP_ACTIVE_LOW, IPT_MAHJONG_CHI )
	PORT_BIT( 0x10, IP_ACTIVE_LOW, IPT_MAHJONG_RON )
	PORT_BIT( 0xe0, IP_ACTIVE_LOW, IPT_UNUSED )

	PORT_START("IN4")
	PORT_BIT( 0x01, IP_ACTIVE_LOW, IPT_MAHJONG_D )
	PORT_BIT( 0x02, IP_ACTIVE_LOW, IPT_MAHJONG_H )
	PORT_BIT( 0x04, IP_ACTIVE_LOW, IPT_MAHJONG_L )
	PORT_BIT( 0x08, IP_ACTIVE_LOW, IPT_MAHJONG_PON )
	PORT_BIT( 0xf0, IP_ACTIVE_LOW, IPT_UNUSED )
INPUT_PORTS_END

static INPUT_PORTS_START( kisekaem )
	PORT_INCLUDE( macs_m )

	PORT_MODIFY("SYS1")
	PORT_DIPNAME( 0x01, 0x01, "SYS1 - BIT 1" )
	PORT_DIPSETTING(    0x01, DEF_STR( Off ) )
	PORT_DIPSETTING(    0x00, DEF_STR( On ) )
	PORT_BIT( 0x02, IP_ACTIVE_LOW, IPT_COIN1 )
	PORT_DIPNAME( 0x04, 0x04, "SYS1 - BIT 4" )
	PORT_DIPSETTING(    0x04, DEF_STR( Off ) )
	PORT_DIPSETTING(    0x00, DEF_STR( On ) )
	PORT_DIPNAME( 0x08, 0x08, "SYS1 - BIT 8" )
	PORT_DIPSETTING(    0x08, DEF_STR( Off ) )
	PORT_DIPSETTING(    0x00, DEF_STR( On ) )
	PORT_DIPNAME( 0x10, 0x10, "SYS1 - BIT 10" )
	PORT_DIPSETTING(    0x10, DEF_STR( Off ) )
	PORT_DIPSETTING(    0x00, DEF_STR( On ) )
	PORT_DIPNAME( 0x20, 0x20, "SYS1 - BIT 20" )
	PORT_DIPSETTING(    0x20, DEF_STR( Off ) )
	PORT_DIPSETTING(    0x00, DEF_STR( On ) )
	PORT_DIPNAME( 0x40, 0x40, "SYS1 - BIT 40" )
	PORT_DIPSETTING(    0x40, DEF_STR( Off ) )
	PORT_DIPSETTING(    0x00, DEF_STR( On ) )
	PORT_DIPNAME( 0x80, 0x00, "SYS1 - BIT 80" )
	PORT_DIPSETTING(    0x80, DEF_STR( Off ) )
	PORT_DIPSETTING(    0x00, DEF_STR( On ) )
INPUT_PORTS_END

static INPUT_PORTS_START( macs_h )
	PORT_INCLUDE( macs_base )

<<<<<<< HEAD
	/*HANAFUDA PANEL*/
=======
	// HANAFUDA PANEL
>>>>>>> upstream/master
	// Also other inputs from the Mahjong panel are detected in Service Mode
	PORT_START("IN0")
	PORT_BIT( 0x01, IP_ACTIVE_LOW, IPT_MAHJONG_LAST_CHANCE )
	PORT_BIT( 0x02, IP_ACTIVE_LOW, IPT_MAHJONG_SCORE )
	PORT_BIT( 0x04, IP_ACTIVE_LOW, IPT_MAHJONG_DOUBLE_UP )
	PORT_BIT( 0x08, IP_ACTIVE_LOW, IPT_MAHJONG_FLIP_FLOP )
	PORT_BIT( 0x10, IP_ACTIVE_LOW, IPT_MAHJONG_BIG )
	PORT_BIT( 0x20, IP_ACTIVE_LOW, IPT_MAHJONG_SMALL )
	PORT_BIT( 0xc0, IP_ACTIVE_LOW, IPT_UNUSED )

	PORT_START("IN1")
	PORT_BIT( 0x01, IP_ACTIVE_LOW, IPT_HANAFUDA_A )
	PORT_BIT( 0x02, IP_ACTIVE_LOW, IPT_HANAFUDA_E )
	PORT_BIT( 0x04, IP_ACTIVE_LOW, IPT_UNUSED )
	PORT_BIT( 0x08, IP_ACTIVE_LOW, IPT_HANAFUDA_YES )
	PORT_BIT( 0x10, IP_ACTIVE_LOW, IPT_UNUSED )
	PORT_BIT( 0x20, IP_ACTIVE_LOW, IPT_START1 )
	PORT_BIT( 0xc0, IP_ACTIVE_LOW, IPT_UNUSED )

	PORT_START("IN2")
	PORT_BIT( 0x01, IP_ACTIVE_LOW, IPT_HANAFUDA_B )
	PORT_BIT( 0x02, IP_ACTIVE_LOW, IPT_HANAFUDA_F )
	PORT_BIT( 0x04, IP_ACTIVE_LOW, IPT_UNUSED )
	PORT_BIT( 0x08, IP_ACTIVE_LOW, IPT_HANAFUDA_NO )
	PORT_BIT( 0x10, IP_ACTIVE_LOW, IPT_UNUSED )
	PORT_BIT( 0x20, IP_ACTIVE_LOW, IPT_MAHJONG_BET )
	PORT_BIT( 0xc0, IP_ACTIVE_LOW, IPT_UNUSED )

	PORT_START("IN3")
	PORT_BIT( 0x01, IP_ACTIVE_LOW, IPT_HANAFUDA_C )
	PORT_BIT( 0x02, IP_ACTIVE_LOW, IPT_HANAFUDA_G )
	PORT_BIT( 0x04, IP_ACTIVE_LOW, IPT_UNUSED )
	PORT_BIT( 0x08, IP_ACTIVE_LOW, IPT_UNUSED )
	PORT_BIT( 0x10, IP_ACTIVE_LOW, IPT_UNUSED )
	PORT_BIT( 0xe0, IP_ACTIVE_LOW, IPT_UNUSED )

	PORT_START("IN4")
	PORT_BIT( 0x01, IP_ACTIVE_LOW, IPT_HANAFUDA_D )
	PORT_BIT( 0x02, IP_ACTIVE_LOW, IPT_HANAFUDA_H )
	PORT_BIT( 0x04, IP_ACTIVE_LOW, IPT_UNUSED )
	PORT_BIT( 0x08, IP_ACTIVE_LOW, IPT_UNUSED )
	PORT_BIT( 0xf0, IP_ACTIVE_LOW, IPT_UNUSED )
INPUT_PORTS_END


<<<<<<< HEAD
UINT32 macs_state::screen_update_macs(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect)
=======
uint32_t macs_state::screen_update_macs(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect)
>>>>>>> upstream/master
{
	return m_maincpu->update(screen,bitmap,cliprect);
}


<<<<<<< HEAD
static MACHINE_CONFIG_START( macs, macs_state )
=======
ST0016_DMA_OFFS_CB(macs_state::dma_offset)
{
	return m_cart_bank;
}

static MACHINE_CONFIG_START( macs )
>>>>>>> upstream/master
	/* basic machine hardware */
	MCFG_CPU_ADD("maincpu",ST0016_CPU,8000000) /* 8 MHz ? */
	MCFG_CPU_PROGRAM_MAP(macs_mem)
	MCFG_CPU_IO_MAP(macs_io)
<<<<<<< HEAD

	MCFG_CPU_VBLANK_INT_DRIVER("screen", macs_state,  irq0_line_hold)

	MCFG_MACHINE_RESET_OVERRIDE(macs_state,macs)
=======
	MCFG_ST0016_DMA_OFFS_CB(macs_state, dma_offset)

	MCFG_CPU_VBLANK_INT_DRIVER("screen", macs_state, irq0_line_hold)

	MCFG_MACHINE_START_OVERRIDE(macs_state, macs)
	MCFG_MACHINE_RESET_OVERRIDE(macs_state, macs)
>>>>>>> upstream/master

	/* video hardware */
	MCFG_SCREEN_ADD("screen", RASTER)
	MCFG_SCREEN_REFRESH_RATE(60)
	MCFG_SCREEN_VBLANK_TIME(ATTOSECONDS_IN_USEC(0))
	MCFG_SCREEN_SIZE(128*8, 128*8)
	MCFG_SCREEN_VISIBLE_AREA(0*8, 128*8-1, 0*8, 128*8-1)
	MCFG_SCREEN_UPDATE_DRIVER(macs_state, screen_update_macs)
	MCFG_SCREEN_PALETTE("maincpu:palette")
<<<<<<< HEAD
MACHINE_CONFIG_END



#define MACS_BIOS \
	ROM_REGION( 0x1000000, "user1", 0 ) \
	ROM_LOAD16_BYTE( "macsos_l.u43", 0x00000, 0x80000, CRC(0b5aed5e) SHA1(042e705017ee34656e2c6af45825bb2dd3447747) ) \
	ROM_LOAD16_BYTE( "macsos_h.u44", 0x00001, 0x80000, CRC(538b68e4) SHA1(a0534147791e94e726f49451d0e95671ae0a87d5) )
#define MACS2_BIOS \
	ROM_REGION( 0x1000000, "user1", 0 ) \
	ROM_LOAD16_BYTE( "macs2os_l.bin", 0x00000, 0x80000, NO_DUMP ) \
	ROM_LOAD16_BYTE( "macs2os_h.bin", 0x00001, 0x80000, NO_DUMP )
ROM_START( macsbios )
	MACS_BIOS
	ROM_REGION( 0x400000, "user2", ROMREGION_ERASEFF ) // Slot A
	ROM_REGION( 0x400000, "user3", ROMREGION_ERASEFF ) // Slot B

	ROM_REGION( 0x1000000, "maincpu", 0 )
	ROM_COPY( "user1",   0x00000, 0x000000, 0x400000 ) // Bios
=======

	MCFG_GENERIC_CARTSLOT_ADD_WITH_DEFAULT("slot_a", generic_plain_slot, "macs_cart", "rom")
	MCFG_SET_IMAGE_LOADABLE(false)
	MCFG_GENERIC_CARTSLOT_ADD_WITH_DEFAULT("slot_b", generic_plain_slot, "macs_cart", "rom")
	MCFG_SET_IMAGE_LOADABLE(false)

MACHINE_CONFIG_END


#define MACS_BIOS \
	ROM_REGION( 0x1000000, "bios", 0 ) \
	ROM_LOAD16_BYTE( "macsos_l.u43", 0x00000, 0x80000, CRC(0b5aed5e) SHA1(042e705017ee34656e2c6af45825bb2dd3447747) ) \
	ROM_LOAD16_BYTE( "macsos_h.u44", 0x00001, 0x80000, CRC(538b68e4) SHA1(a0534147791e94e726f49451d0e95671ae0a87d5) )

#define MACS2_BIOS \
	ROM_REGION( 0x1000000, "bios", 0 ) \
	ROM_LOAD16_BYTE( "macs2os_l.bin", 0x00000, 0x80000, NO_DUMP ) \
	ROM_LOAD16_BYTE( "macs2os_h.bin", 0x00001, 0x80000, NO_DUMP )

ROM_START( macsbios )
	MACS_BIOS

	ROM_REGION( 0x1000000, "maincpu", 0 )
	ROM_COPY( "bios",   0x000000, 0x000000, 0x400000 )

	ROM_REGION( 0x400000, "slot_a:rom", ROMREGION_ERASEFF )
	ROM_REGION( 0x400000, "slot_b:rom", ROMREGION_ERASEFF )
>>>>>>> upstream/master
ROM_END

ROM_START( mac2bios )
	MACS2_BIOS
<<<<<<< HEAD
	ROM_REGION( 0x400000, "user2", ROMREGION_ERASEFF ) // Slot A
	ROM_REGION( 0x400000, "user3", ROMREGION_ERASEFF ) // Slot B

	ROM_REGION( 0x1000000, "maincpu", 0 )
	ROM_COPY( "user1",   0x00000, 0x000000, 0x400000 ) // Bios
=======

	ROM_REGION( 0x1000000, "maincpu", 0 )
	ROM_COPY( "bios",   0x000000, 0x000000, 0x400000 )

	ROM_REGION( 0x400000, "slot_a:rom", ROMREGION_ERASEFF )
	ROM_REGION( 0x400000, "slot_b:rom", ROMREGION_ERASEFF )
>>>>>>> upstream/master
ROM_END

ROM_START( kisekaem )
	MACS_BIOS

<<<<<<< HEAD
	ROM_REGION( 0x400000, "user2", 0 ) // Slot A
=======
	ROM_REGION( 0x400000, "slot_a:rom", 0 )
>>>>>>> upstream/master
	ROM_LOAD16_BYTE( "am-mj.u8", 0x000000, 0x100000, CRC(3cf85151) SHA1(e05400065c384730f04ef565db5ba27eb3973d15) )
	ROM_LOAD16_BYTE( "am-mj.u7", 0x000001, 0x100000, CRC(4b645354) SHA1(1dbf9141c3724e5dff2cd8066117fb1b94671a80) )
	ROM_LOAD16_BYTE( "am-mj.u6", 0x200000, 0x100000, CRC(23b3aa24) SHA1(bfabdb16f9b1b60230bb636a944ab46fdfda49d7) )
	ROM_LOAD16_BYTE( "am-mj.u5", 0x200001, 0x100000, CRC(b4d53e29) SHA1(d7683fdd5531bf1aa0ef1e4e6f517b31e2d5829e) )
<<<<<<< HEAD


	ROM_REGION( 0x400000, "user3", ROMREGION_ERASEFF ) // Slot B

	ROM_REGION( 0x1000000, "maincpu", 0 )
	ROM_COPY( "user1",   0x00000, 0x000000, 0x400000 ) // Bios
	ROM_COPY( "user2",   0x00000, 0x400000, 0x400000 ) // Slot A
=======
	ROM_REGION( 0x400000, "slot_b:rom", ROMREGION_ERASEFF )

	ROM_REGION( 0x1000000, "maincpu", 0 )
	ROM_COPY( "bios",   0x000000, 0x000000, 0x400000 )
	ROM_COPY( "slot_a:rom", 0x000000, 0x400000, 0x400000 ) // Slot A
>>>>>>> upstream/master
ROM_END

ROM_START( kisekaeh )
	MACS_BIOS

<<<<<<< HEAD
	ROM_REGION( 0x400000, "user2", 0 ) // Slot A
=======
	ROM_REGION( 0x400000, "slot_a:rom", 0 )
>>>>>>> upstream/master
	ROM_LOAD16_BYTE( "kh-u8.bin", 0x000000, 0x100000, CRC(601b9e6a) SHA1(54508a6db3928f78897df64ce400791e4789d0f6) )
	ROM_LOAD16_BYTE( "kh-u7.bin", 0x000001, 0x100000, CRC(8f6e4bb3) SHA1(361545189feeda0887f930727d25655309b84629) )
	ROM_LOAD16_BYTE( "kh-u6.bin", 0x200000, 0x100000, CRC(8e700204) SHA1(876e5530d749828de077293cb109a71b67cef140) )
	ROM_LOAD16_BYTE( "kh-u5.bin", 0x200001, 0x100000, CRC(709bf7c8) SHA1(0a93e0c4f9be22a3302a1c5d2a6ec4739b202ea8) )
<<<<<<< HEAD


	ROM_REGION( 0x400000, "user3", ROMREGION_ERASEFF ) // Slot B

	ROM_REGION( 0x1000000, "maincpu", 0 )
	ROM_COPY( "user1",   0x00000, 0x000000, 0x400000 ) // Bios
	ROM_COPY( "user2",   0x00000, 0x400000, 0x400000 ) // Slot A
=======
	ROM_REGION( 0x400000, "slot_b:rom", ROMREGION_ERASEFF )

	ROM_REGION( 0x1000000, "maincpu", 0 )
	ROM_COPY( "bios",   0x000000, 0x000000, 0x400000 )
	ROM_COPY( "slot_a:rom", 0x000000, 0x400000, 0x400000 ) // Slot A
>>>>>>> upstream/master
ROM_END

ROM_START( cultname ) // uses printer - two different games ? (slot a - checks for printer, slot b - not)
	MACS_BIOS

<<<<<<< HEAD
	ROM_REGION( 0x400000, "user2", 0 ) // Slot A
=======
	ROM_REGION( 0x400000, "slot_a:rom", 0 )
>>>>>>> upstream/master
	ROM_LOAD16_BYTE( "cult-d0.u8", 0x000000, 0x100000, CRC(394bc1a6) SHA1(98df5406862234815b46c7b0ac0b19e4b597d1b6) )
	ROM_LOAD16_BYTE( "cult-d1.u7", 0x000001, 0x100000, CRC(f628133b) SHA1(f06e20212074e5d95cc7d419ac8ce98fb9be3b62) )
	ROM_LOAD16_BYTE( "cult-d2.u6", 0x200000, 0x100000, CRC(c5521bc6) SHA1(7554b56b0201b7d81754defa2244fb7ff7452bf6) )
	ROM_LOAD16_BYTE( "cult-d3.u5", 0x200001, 0x100000, CRC(4325b09b) SHA1(45699a0444a221f893724754c917d33041cabcb9) )

<<<<<<< HEAD

	ROM_REGION( 0x400000, "user3", 0 ) // Slot B
=======
	ROM_REGION( 0x400000, "slot_b:rom", 0 )
>>>>>>> upstream/master
	ROM_LOAD16_BYTE( "cult-g0.u8", 0x000000, 0x100000, CRC(f5ab977b) SHA1(e7ee758cc2864500b339e236b944f98df9a1c10e) )
	ROM_LOAD16_BYTE( "cult-g1.u7", 0x000001, 0x100000, CRC(32ae15a4) SHA1(061992efec1ed5527f200bf4c111344b156e759d) )
	ROM_LOAD16_BYTE( "cult-g2.u6", 0x200000, 0x100000, CRC(30ed056d) SHA1(71735339bb501b94402ef403b5a2a60effa39c36) )
	ROM_LOAD16_BYTE( "cult-g3.u5", 0x200001, 0x100000, CRC(fe58b418) SHA1(512f5c544cfafaa98bd2b3791ff1cf67adecec8d) )

<<<<<<< HEAD

	ROM_REGION( 0x1000000, "maincpu", 0 )
	ROM_COPY( "user1",   0x00000, 0x000000, 0x400000 ) // Bios
	ROM_COPY( "user2",   0x00000, 0x400000, 0x400000 ) // Slot A
	ROM_COPY( "user3",   0x00000, 0x800000, 0x400000 ) // Slot B
=======
	ROM_REGION( 0x1000000, "maincpu", 0 )
	ROM_COPY( "bios",   0x000000, 0x000000, 0x400000 )
	ROM_COPY( "slot_a:rom", 0x000000, 0x400000, 0x400000 ) // Slot A
	ROM_COPY( "slot_b:rom", 0x000000, 0x800000, 0x400000 ) // Slot B
>>>>>>> upstream/master
ROM_END

/* these are listed as MACS2 sub-boards, is it the same?  - it's not ;) */

ROM_START( yuka )
	MACS2_BIOS

<<<<<<< HEAD
	ROM_REGION( 0x400000, "user2", 0 ) // Slot A
=======
	ROM_REGION( 0x400000, "slot_a:rom", 0 )
>>>>>>> upstream/master
	ROM_LOAD16_BYTE( "yu-ka_2.u6", 0x000001, 0x100000, CRC(c3c5728b) SHA1(e53cdcae556f34bab45d9342fd78ec29b6543c46) )
	ROM_LOAD16_BYTE( "yu-ka_4.u5", 0x000000, 0x100000, CRC(7e391ee6) SHA1(3a0c122c9d0e2a91df6d8039fb958b6d00997747) )
	ROM_LOAD16_BYTE( "yu-ka_1.u8", 0x200001, 0x100000, CRC(bccd1b15) SHA1(02511f3be60c53b5f5d90f12f0648f6e184ca667) )
	ROM_LOAD16_BYTE( "yu-ka_3.u7", 0x200000, 0x100000, CRC(45b8263e) SHA1(59e1846c91dc39a086e8306260506673eb91de0b) )

<<<<<<< HEAD
	ROM_REGION( 0x400000, "user3", ROMREGION_ERASE00 ) // Slot B

	ROM_REGION( 0x1000000, "maincpu", 0 )
	ROM_COPY( "user2",   0x00000, 0x000000, 0x400000 ) // Slot A
=======
	ROM_REGION( 0x400000, "slot_b:rom", ROMREGION_ERASE00 )

	ROM_REGION( 0x1000000, "maincpu", 0 )
	ROM_COPY( "slot_a:rom",   0x000000, 0x000000, 0x400000 )
>>>>>>> upstream/master
ROM_END

ROM_START( yujan )
	MACS2_BIOS

<<<<<<< HEAD
	ROM_REGION( 0x400000, "user2", 0 ) // Slot A
=======
	ROM_REGION( 0x400000, "slot_a:rom", 0 )
>>>>>>> upstream/master
	ROM_LOAD16_BYTE( "yu-jan_2.u6", 0x000001, 0x100000, CRC(2f4a8d4b) SHA1(4b328a253b1980a76f46a9a98a7f486813894a33) )
	ROM_LOAD16_BYTE( "yu-jan_4.u5", 0x000000, 0x100000, CRC(226df87b) SHA1(a887728f1ea2ef5f6b4dcd6b5b61586f5e8f267d) )
	ROM_LOAD16_BYTE( "yu-jan_1.u8", 0x200001, 0x100000, CRC(feeeee6a) SHA1(e9613f50d6d2e62fac6b529f81486250cfe83819) )
	ROM_LOAD16_BYTE( "yu-jan_3.u7", 0x200000, 0x100000, CRC(1c1d6997) SHA1(9b07ae6b9ef1c0b57fbaa5fd0bcf1d2d7f17351f) )

<<<<<<< HEAD
	ROM_REGION( 0x400000, "user3", ROMREGION_ERASEFF ) // Slot B

	ROM_REGION( 0x1000000, "maincpu", 0 )
	ROM_COPY( "user2",   0x00000, 0x000000, 0x400000 ) // Slot A
ROM_END

#if 0
static const UINT8 ramdata[160]=
=======
	ROM_REGION( 0x400000, "slot_b:rom", ROMREGION_ERASEFF )

	ROM_REGION( 0x1000000, "maincpu", 0 )
	ROM_COPY( "slot_a:rom",   0x000000, 0x000000, 0x400000 )
ROM_END

#if 0
static const uint8_t ramdata[160]=
>>>>>>> upstream/master
{
	0xAF, 0xED, 0x47, 0xD3, 0xC1, 0xD3, 0x0C, 0xD3, 0xAF, 0xED, 0x47, 0xD3, 0xC1, 0xD3, 0x0C, 0xD3,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0x00, 0x00, 0x00, 0x00, 0xAF, 0x32, 0x1F, 0xFE, 0xD3,
	0xE0, 0x3A, 0x0A, 0xE8, 0xF6, 0x04, 0x32, 0x0A, 0xE8, 0xD3, 0xC0, 0x01, 0x08, 0x00, 0x21, 0x00,
	0x01, 0x11, 0x00, 0xFE, 0xED, 0xB0, 0x01, 0x10, 0x00, 0x21, 0x10, 0x01, 0x11, 0x00, 0xF0, 0xED,
	0xB0, 0x3A, 0x0A, 0xE8, 0xE6, 0xF3, 0xF6, 0x08, 0x32, 0x0A, 0xE8, 0xD3, 0xC0, 0x01, 0x08, 0x00,
	0x21, 0x00, 0x01, 0x11, 0x08, 0xFE, 0xED, 0xB0, 0x01, 0x10, 0x00, 0x21, 0x10, 0x01, 0x11, 0x20,
	0xF0, 0xED, 0xB0, 0x3A, 0x0A, 0xE8, 0xE6, 0xF3, 0x32, 0x0A, 0xE8, 0xD3, 0xC0, 0xC9, 0x00, 0xF3
};
#endif

<<<<<<< HEAD
MACHINE_RESET_MEMBER(macs_state,macs)
{
	UINT8 *macs_ram1 = m_ram1;
	#if 0
	UINT8 *macs_ram2 = m_ram2;
=======
MACHINE_START_MEMBER(macs_state,macs)
{
	membank("bank1")->configure_entries(0  , 256, memregion("maincpu")->base(), 0x4000);
	membank("bank1")->configure_entries(256, 256, m_cart1->get_rom_base(), 0x4000);
	membank("bank1")->configure_entries(512, 256, m_cart2->get_rom_base(), 0x4000);
	membank("bank1")->set_entry(0);

	membank("bank2")->configure_entries(0, 2, m_ram1.get() + 0x2000, 0x800);
	membank("bank2")->set_entry(0);

	membank("bank3")->configure_entries(0, 4, m_ram1.get(), 0x800);
	membank("bank3")->set_entry(2);

	membank("bank4")->configure_entries(0  , 256, memregion("maincpu")->base(), 0x4000);
	membank("bank4")->configure_entries(256, 256, m_cart1->get_rom_base(), 0x4000);
	membank("bank4")->configure_entries(512, 256, m_cart2->get_rom_base(), 0x4000);
	membank("bank4")->set_entry(0);
}

MACHINE_RESET_MEMBER(macs_state,macs)
{
	#if 0
	uint8_t *macs_ram1 = m_ram1.get();
	uint8_t *macs_ram2 = m_ram2;
>>>>>>> upstream/master
/*
        BIOS ram init:

        72CA: 01 C7 00      ld   bc,$00C7
        72CD: 11 9F FE      ld   de,$FE9F
        72D0: 21 27 73      ld   hl,$7327
        72D3: ED B0         ldir
        72D5: 3E C3         ld   a,$C3
        72D7: 32 16 E8      ld   ($E816),a
        72DA: 32 19 E8      ld   ($E819),a
        72DD: 21 9F FE      ld   hl,$FE9F
        72E0: 22 17 E8      ld   ($E817),hl
        72E3: 21 E0 FE      ld   hl,$FEE0
        72E6: 22 1A E8      ld   ($E81A),hl
        ...
        //bank change ? = set 5th bit in port $c0
        ...
        72F8: 01 C7 00      ld   bc,$00C7
        72FB: 11 9F FE      ld   de,$FE9F
        72FE: 21 27 73      ld   hl,$7327
        7301: ED B0         ldir
        ...
        7305: 01 07 05      ld   bc,$0507
        7308: 11 00 F8      ld   de,$F800
        730B: 21 FA 73      ld   hl,$73FA
        730E: ED B0         ldir
        ...
*/
<<<<<<< HEAD
		memcpy(macs_ram1 + 0x0e9f, memregion("user1")->base()+0x7327, 0xc7);
		memcpy(macs_ram1 + 0x1e9f, memregion("user1")->base()+0x7327, 0xc7);

		memcpy(macs_ram1 + 0x0800, memregion("user1")->base()+0x73fa, 0x507);
		memcpy(macs_ram1 + 0x1800, memregion("user1")->base()+0x73fa, 0x507);
=======
		memcpy(macs_ram1 + 0x0e9f, memregion("bios")->base()+0x7327, 0xc7);
		memcpy(macs_ram1 + 0x1e9f, memregion("bios")->base()+0x7327, 0xc7);

		memcpy(macs_ram1 + 0x0800, memregion("bios")->base()+0x73fa, 0x507);
		memcpy(macs_ram1 + 0x1800, memregion("bios")->base()+0x73fa, 0x507);
>>>>>>> upstream/master

#define MAKEJMP(n,m)    macs_ram2[(n) - 0xe800 + 0]=0xc3;\
						macs_ram2[(n) - 0xe800 + 1]=(m)&0xff;\
						macs_ram2[(n) - 0xe800 + 2]=((m)>>8)&0xff;

		MAKEJMP(0xe810, 0xfe4b);
		MAKEJMP(0xe816, 0xfe9f);
		MAKEJMP(0xe81a, 0xfee0);

#undef MAKEJMP

		{
			int i;
			for(i=0;i<160;i++)
			{
				macs_ram1[0xe00+i]=ramdata[i];
				macs_ram1[0x1e00+i]=ramdata[i];
			}
		}
		macs_ram1[0x0f67]=0xff;
		macs_ram1[0x1f67]=0xff;

		macs_ram1[0x0ff6]=0x02;
		macs_ram1[0x1ff6]=0x02;

		macs_ram1[0x0ff7]=0x08;
		macs_ram1[0x1ff7]=0x08;

		macs_ram1[0x0ff8]=0x6c;
		macs_ram1[0x1ff8]=0x6c;

		macs_ram1[0x0ff9]=0x07;
		macs_ram1[0x1ff9]=0x07;
		#endif
<<<<<<< HEAD

		membank("bank1")->set_base(memregion("maincpu")->base() );
		membank("bank2")->set_base(macs_ram1+0x800);
		membank("bank3")->set_base(macs_ram1+0x10000);
		membank("bank4")->set_base(memregion("maincpu")->base() );
}

DRIVER_INIT_MEMBER(macs_state,macs)
{
	m_ram1=auto_alloc_array(machine(), UINT8, 0x20000);
	m_maincpu->st0016_game=10|0x80;
=======
}


DRIVER_INIT_MEMBER(macs_state,macs)
{
	m_ram1=std::make_unique<uint8_t[]>(0x20000);
	m_maincpu->set_st0016_game_flag((10 | 0x80));
>>>>>>> upstream/master
	m_rev = 1;
}

DRIVER_INIT_MEMBER(macs_state,macs2)
{
<<<<<<< HEAD
	m_ram1=auto_alloc_array(machine(), UINT8, 0x20000);
	m_maincpu->st0016_game=10|0x80;
=======
	m_ram1=std::make_unique<uint8_t[]>(0x20000);
	m_maincpu->set_st0016_game_flag((10 | 0x80));
>>>>>>> upstream/master
	m_rev = 2;
}

DRIVER_INIT_MEMBER(macs_state,kisekaeh)
{
<<<<<<< HEAD
	m_ram1=auto_alloc_array(machine(), UINT8, 0x20000);
	m_maincpu->st0016_game=11|0x180;
=======
	m_ram1=std::make_unique<uint8_t[]>(0x20000);
	m_maincpu->set_st0016_game_flag((11 | 0x180));
>>>>>>> upstream/master
	m_rev = 1;
}

DRIVER_INIT_MEMBER(macs_state,kisekaem)
{
<<<<<<< HEAD
	m_ram1=auto_alloc_array(machine(), UINT8, 0x20000);
	m_maincpu->st0016_game=10|0x180;
=======
	m_ram1=std::make_unique<uint8_t[]>(0x20000);
	m_maincpu->set_st0016_game_flag((10 | 0x180));
>>>>>>> upstream/master
	m_rev = 1;
}


<<<<<<< HEAD
GAME( 1995, macsbios, 0,        macs, macs_m, macs_state, macs,     ROT0, "I'Max", "Multi Amenity Cassette System BIOS", MACHINE_IS_BIOS_ROOT | MACHINE_IMPERFECT_SOUND | MACHINE_NOT_WORKING )
GAME( 1995, mac2bios, 0,        macs, macs_m, macs_state, macs2,     ROT0, "I'Max", "Multi Amenity Cassette System 2 BIOS", MACHINE_IS_BIOS_ROOT | MACHINE_IMPERFECT_SOUND | MACHINE_NOT_WORKING )

GAME( 1995, kisekaem, macsbios, macs, kisekaem, macs_state, kisekaem,   ROT0, "I'Max", "Kisekae Mahjong",  MACHINE_NOT_WORKING|MACHINE_IMPERFECT_SOUND )
GAME( 1995, kisekaeh, macsbios, macs, macs_h, macs_state,   kisekaeh,   ROT0, "I'Max", "Kisekae Hanafuda",  MACHINE_NOT_WORKING |MACHINE_IMPERFECT_SOUND)
GAME( 1996, cultname, macsbios, macs, macs_m, macs_state,   macs,       ROT0, "I'Max", "Seimei-Kantei-Meimei-Ki Cult Name",  MACHINE_NOT_WORKING |MACHINE_IMPERFECT_SOUND)
GAME( 1999, yuka,     macsbios, macs, macs_h, macs_state,   macs2,      ROT0, "Yubis / T.System", "Yu-Ka",  0 )
GAME( 1999, yujan,    macsbios, macs, macs_m, macs_state,   macs2,      ROT0, "Yubis / T.System", "Yu-Jan",  0 )
=======
GAME( 1995, macsbios, 0,        macs, macs_m,   macs_state, macs,     ROT0, "I'Max",            "Multi Amenity Cassette System BIOS",   MACHINE_IS_BIOS_ROOT | MACHINE_IMPERFECT_SOUND | MACHINE_NOT_WORKING )
GAME( 1995, mac2bios, 0,        macs, macs_m,   macs_state, macs2,    ROT0, "I'Max",            "Multi Amenity Cassette System 2 BIOS", MACHINE_IS_BIOS_ROOT | MACHINE_IMPERFECT_SOUND | MACHINE_NOT_WORKING )

GAME( 1995, kisekaem, macsbios, macs, kisekaem, macs_state, kisekaem, ROT0, "I'Max",            "Kisekae Mahjong",                      MACHINE_NOT_WORKING | MACHINE_IMPERFECT_SOUND )
GAME( 1995, kisekaeh, macsbios, macs, macs_h,   macs_state, kisekaeh, ROT0, "I'Max",            "Kisekae Hanafuda",                     MACHINE_NOT_WORKING | MACHINE_IMPERFECT_SOUND )
GAME( 1996, cultname, macsbios, macs, macs_m,   macs_state, macs,     ROT0, "I'Max",            "Seimei-Kantei-Meimei-Ki Cult Name",    MACHINE_NOT_WORKING | MACHINE_IMPERFECT_SOUND )
GAME( 1999, yuka,     macsbios, macs, macs_h,   macs_state, macs2,    ROT0, "Yubis / T.System", "Yu-Ka",                                0 )
GAME( 1999, yujan,    macsbios, macs, macs_m,   macs_state, macs2,    ROT0, "Yubis / T.System", "Yu-Jan",                               0 )
>>>>>>> upstream/master
