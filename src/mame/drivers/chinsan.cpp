<<<<<<< HEAD
// license:BSD-3-Clause
// copyright-holders:David Haywood
/* Ganbare Chinsan Ooshoubu
 driver by David Haywood

ToDo:
Improve Inputs

Notes:
-ADPCM hook-up is virtually identical to the other Sanritsu games (Jantotsu, Appoooh, Dr. Micro etc.).

*/

/*

Ganbare Chinsan Ooshoubu
(c)1987 Sanritsu

C1-00114-B

CPU:    317-5012 (MC-8123A)
SOUND:  YM2203
        M5205
OSC:    10.000MHz
        384KHz
Chips:  8255AC-2


MM00.7D   prg.
MM01.8D

MM20.7K   chr.
MM21.8K
MM22.9K

MM40.13D  samples

MM60.2C   ?

MM61.9M   color
MM62.9N
MM63.10N

*/
=======
// license: BSD-3-Clause
// copyright-holders: David Haywood, Uki, Dirk Best
/***************************************************************************

    Ganbare Chinsan Ooshoubu (がんばれ珍さん！大勝負)
    © 1987 Sanritsu

    Kiki-Ippatsu Mayumi-chan (危機一髪真由美ちゃん)
    © 1988 Victory L.L.C. (developed by Sanritsu)

    TODO:
    - Figure out the rest of the dip switches
    - Verify clock speeds
    - Raw screen params

    Notes:
    - ADPCM hook-up is virtually identical to the other Sanritsu games
      (Jantotsu, Appoooh, Dr. Micro etc.).

***************************************************************************/
>>>>>>> upstream/master

#include "emu.h"
#include "cpu/z80/z80.h"
#include "machine/mc8123.h"
<<<<<<< HEAD
#include "sound/2203intf.h"
#include "sound/msm5205.h"
=======
#include "machine/nvram.h"
#include "machine/i8255.h"
#include "sound/2203intf.h"
#include "sound/msm5205.h"
#include "screen.h"
#include "speaker.h"


//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************
>>>>>>> upstream/master

class chinsan_state : public driver_device
{
public:
	chinsan_state(const machine_config &mconfig, device_type type, const char *tag)
		: driver_device(mconfig, type, tag),
<<<<<<< HEAD
		m_video(*this, "video"),
		m_maincpu(*this, "maincpu"),
		m_adpcm(*this, "adpcm"),
		m_gfxdecode(*this, "gfxdecode"),
		m_palette(*this, "palette") { }

	/* memory pointers */
	required_shared_ptr<UINT8> m_video;

	/* misc */
	UINT8    m_port_select;
	UINT32   m_adpcm_pos;
	UINT8    m_adpcm_idle;
	UINT8    m_adpcm_data;
	UINT8    m_trigger;
	DECLARE_WRITE8_MEMBER(ctrl_w);
	DECLARE_WRITE8_MEMBER(chinsan_port00_w);
	DECLARE_READ8_MEMBER(chinsan_input_port_0_r);
	DECLARE_READ8_MEMBER(chinsan_input_port_1_r);
	DECLARE_WRITE8_MEMBER(ym_port_w1);
	DECLARE_WRITE8_MEMBER(ym_port_w2);
	DECLARE_WRITE8_MEMBER(chin_adpcm_w);
	DECLARE_DRIVER_INIT(chinsan);
	virtual void machine_start();
	virtual void machine_reset();
	virtual void video_start();
	DECLARE_PALETTE_INIT(chinsan);
	UINT32 screen_update_chinsan(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
	DECLARE_WRITE_LINE_MEMBER(chin_adpcm_int);
	required_device<cpu_device> m_maincpu;
	required_device<msm5205_device> m_adpcm;
	required_device<gfxdecode_device> m_gfxdecode;
	required_device<palette_device> m_palette;
	UINT8 *m_decrypted_opcodes;
};


/*************************************
 *
 *  Video emulation
 *
 *************************************/

PALETTE_INIT_MEMBER(chinsan_state, chinsan)
{
	UINT8 *src = memregion( "color_proms" )->base();
	int i;

	for (i = 0; i < 0x100; i++)
		palette.set_pen_color(i, pal4bit(src[i + 0x200]), pal4bit(src[i + 0x100]), pal4bit(src[i + 0x000]));
}

void chinsan_state::video_start()
{
}

UINT32 chinsan_state::screen_update_chinsan(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect)
{
	int y, x, count;
	count = 0;
	for (y = 0; y < 32; y++)
	{
		for (x = 0; x < 64; x++)
		{
			int tileno, colour;
			tileno = m_video[count] | (m_video[count + 0x800] << 8);
			colour = m_video[count + 0x1000] >> 3;
			m_gfxdecode->gfx(0)->opaque(bitmap,cliprect,tileno,colour,0,0,x*8,y*8);
			count++;
		}
	}

	return 0;
}



/*************************************
 *
 *  Memory handlers
 *
 *************************************/

WRITE8_MEMBER(chinsan_state::ctrl_w)
{
	membank("bank1")->set_entry(data >> 6);
	membank("bank1d")->set_entry(data >> 6);
}

WRITE8_MEMBER(chinsan_state::ym_port_w1)
{
	logerror("ym_write port 1 %02x\n", data);
}


WRITE8_MEMBER(chinsan_state::ym_port_w2)
{
	logerror("ym_write port 2 %02x\n", data);
}

WRITE8_MEMBER(chinsan_state::chinsan_port00_w)
{
	m_port_select = data;

	if (
		(data != 0x40) &&
		(data != 0x4f) &&
		(data != 0x53) &&
		(data != 0x57) &&
		(data != 0x5b) &&
		(data != 0x5d) &&
		(data != 0x5e))
		logerror("write port 00 %02x\n", data);

}

READ8_MEMBER(chinsan_state::chinsan_input_port_0_r)
{
	//return 0xff; // the inputs don't seem to work, so just return ff for now

	switch (m_port_select)
	{
		/* i doubt these are both really the same.. */
		case 0x40:
		case 0x4f:
			return ioport("MAHJONG_P2_1")->read();

		case 0x53:
			return ioport("MAHJONG_P2_2")->read();

		case 0x57:
			return ioport("MAHJONG_P2_3")->read();

		case 0x5b:
			return ioport("MAHJONG_P2_4")->read();

		case 0x5d:
			return ioport("MAHJONG_P2_5")->read();

		case 0x5e:
			return ioport("MAHJONG_P2_6")->read();
	}

	printf("chinsan_input_port_0_r unk_r %02x\n", m_port_select);
	return machine().rand();
}

READ8_MEMBER(chinsan_state::chinsan_input_port_1_r)
{
	switch (m_port_select)
	{
		/* i doubt these are both really the same.. */
		case 0x40:
		case 0x4f:
			return ioport("MAHJONG_P1_1")->read();

		case 0x53:
			return ioport("MAHJONG_P1_2")->read();

		case 0x57:
			return ioport("MAHJONG_P1_3")->read();

		case 0x5b:
			return ioport("MAHJONG_P1_4")->read();

		case 0x5d:
			return ioport("MAHJONG_P1_5")->read();

		case 0x5e:
			return ioport("MAHJONG_P1_6")->read();
	}

	printf("chinsan_input_port_1_r unk_r %02x\n", m_port_select);
	return machine().rand();
}

WRITE8_MEMBER(chinsan_state::chin_adpcm_w)
{
	m_adpcm_pos = (data & 0xff) * 0x100;
	m_adpcm_idle = 0;
	m_adpcm->reset_w(0);
}

/*************************************
 *
 *  Address maps
 *
 *************************************/

static ADDRESS_MAP_START( chinsan_map, AS_PROGRAM, 8, chinsan_state )
	AM_RANGE(0x0000, 0x7fff) AM_ROM
	AM_RANGE(0x8000, 0xbfff) AM_ROMBANK("bank1")
	AM_RANGE(0xc000, 0xdfff) AM_RAM
	AM_RANGE(0xe000, 0xf7ff) AM_RAM AM_SHARE("video")
ADDRESS_MAP_END

static ADDRESS_MAP_START( decrypted_opcodes_map, AS_DECRYPTED_OPCODES, 8, chinsan_state )
	AM_RANGE(0x0000, 0x7fff) AM_ROMBANK("bank0d")
	AM_RANGE(0x8000, 0xbfff) AM_ROMBANK("bank1d")
ADDRESS_MAP_END

static ADDRESS_MAP_START( chinsan_io, AS_IO, 8, chinsan_state )
	ADDRESS_MAP_GLOBAL_MASK(0xff)
	AM_RANGE(0x00, 0x00) AM_WRITE(chinsan_port00_w)
	AM_RANGE(0x01, 0x01) AM_READ(chinsan_input_port_0_r)
	AM_RANGE(0x02, 0x02) AM_READ(chinsan_input_port_1_r)
	AM_RANGE(0x10, 0x11) AM_DEVREADWRITE("ymsnd", ym2203_device, read, write)
	AM_RANGE(0x20, 0x20) AM_WRITE(chin_adpcm_w)
	AM_RANGE(0x30, 0x30) AM_WRITE(ctrl_w)   // ROM bank + unknown stuff (input mutliplex?)
ADDRESS_MAP_END


/*************************************
 *
 *  Input ports
 *
 *************************************/

static INPUT_PORTS_START( chinsan )
	PORT_START("DSW1")
	PORT_DIPNAME( 0x01, 0x01, "DSW1" )
	PORT_DIPSETTING(    0x01, DEF_STR( Off ) )
	PORT_DIPSETTING(    0x00, DEF_STR( On ) )
	PORT_DIPNAME( 0x02, 0x02, DEF_STR( Unknown ) )
	PORT_DIPSETTING(    0x02, DEF_STR( Off ) )
	PORT_DIPSETTING(    0x00, DEF_STR( On ) )
	PORT_DIPNAME( 0x04, 0x04, DEF_STR( Unknown ) )
	PORT_DIPSETTING(    0x04, DEF_STR( Off ) )
	PORT_DIPSETTING(    0x00, DEF_STR( On ) )
	PORT_DIPNAME( 0x08, 0x08, DEF_STR( Unknown ) )
	PORT_DIPSETTING(    0x08, DEF_STR( Off ) )
	PORT_DIPSETTING(    0x00, DEF_STR( On ) )
	PORT_DIPNAME( 0x10, 0x10, DEF_STR( Unknown ) )
	PORT_DIPSETTING(    0x10, DEF_STR( Off ) )
	PORT_DIPSETTING(    0x00, DEF_STR( On ) )
	PORT_DIPNAME( 0x20, 0x20, DEF_STR( Unknown ) )
	PORT_DIPSETTING(    0x20, DEF_STR( Off ) )
	PORT_DIPSETTING(    0x00, DEF_STR( On ) )
	PORT_DIPNAME( 0x40, 0x40, DEF_STR( Unknown ) )
	PORT_DIPSETTING(    0x40, DEF_STR( Off ) )
	PORT_DIPSETTING(    0x00, DEF_STR( On ) )
	PORT_DIPNAME( 0x80, 0x80, DEF_STR( Unknown ) )
	PORT_DIPSETTING(    0x80, DEF_STR( Off ) )
	PORT_DIPSETTING(    0x00, DEF_STR( On ) )

	PORT_START("DSW2")
	PORT_DIPNAME( 0x01, 0x01, "DSW2" )
	PORT_DIPSETTING(    0x01, DEF_STR( Off ) )
	PORT_DIPSETTING(    0x00, DEF_STR( On ) )
	PORT_DIPNAME( 0x02, 0x02, DEF_STR( Unknown ) )
	PORT_DIPSETTING(    0x02, DEF_STR( Off ) )
	PORT_DIPSETTING(    0x00, DEF_STR( On ) )
	PORT_DIPNAME( 0x04, 0x04, DEF_STR( Unknown ) )
	PORT_DIPSETTING(    0x04, DEF_STR( Off ) )
	PORT_DIPSETTING(    0x00, DEF_STR( On ) )
	PORT_DIPNAME( 0x08, 0x08, DEF_STR( Unknown ) )
	PORT_DIPSETTING(    0x08, DEF_STR( Off ) )
	PORT_DIPSETTING(    0x00, DEF_STR( On ) )
	PORT_DIPNAME( 0x10, 0x10, DEF_STR( Unknown ) )
	PORT_DIPSETTING(    0x10, DEF_STR( Off ) )
	PORT_DIPSETTING(    0x00, DEF_STR( On ) )
	PORT_DIPNAME( 0x20, 0x20, DEF_STR( Unknown ) )
	PORT_DIPSETTING(    0x20, DEF_STR( Off ) )
	PORT_DIPSETTING(    0x00, DEF_STR( On ) )
	PORT_DIPNAME( 0x40, 0x40, DEF_STR( Unknown ) )
	PORT_DIPSETTING(    0x40, DEF_STR( Off ) )
	PORT_DIPSETTING(    0x00, DEF_STR( On ) )
	PORT_DIPNAME( 0x80, 0x80, DEF_STR( Unknown ) )
	PORT_DIPSETTING(    0x80, DEF_STR( Off ) )
	PORT_DIPSETTING(    0x00, DEF_STR( On ) )


	PORT_START("MAHJONG_P1_1")
	PORT_DIPNAME( 0x01, 0x01, "1-1" )
	PORT_DIPSETTING(    0x01, DEF_STR( Off ) )
	PORT_DIPSETTING(    0x00, DEF_STR( On ) )
	PORT_DIPNAME( 0x02, 0x02, DEF_STR( Unknown ) )
	PORT_DIPSETTING(    0x02, DEF_STR( Off ) )
	PORT_DIPSETTING(    0x00, DEF_STR( On ) )
	PORT_DIPNAME( 0x04, 0x04, "P1 FF" ) // labaled FF in test mode, is this coin1?
	PORT_DIPSETTING(    0x04, DEF_STR( Off ) )
	PORT_DIPSETTING(    0x00, DEF_STR( On ) )
	PORT_DIPNAME( 0x08, 0x08, DEF_STR( Unknown ) )
	PORT_DIPSETTING(    0x08, DEF_STR( Off ) )
	PORT_DIPSETTING(    0x00, DEF_STR( On ) )
	PORT_DIPNAME( 0x10, 0x10, DEF_STR( Unknown ) )
	PORT_DIPSETTING(    0x10, DEF_STR( Off ) )
	PORT_DIPSETTING(    0x00, DEF_STR( On ) )
	PORT_DIPNAME( 0x20, 0x20, DEF_STR( Unknown ) )
	PORT_DIPSETTING(    0x20, DEF_STR( Off ) )
	PORT_DIPSETTING(    0x00, DEF_STR( On ) )
	PORT_DIPNAME( 0x40, 0x40, DEF_STR( Unknown ) )
	PORT_DIPSETTING(    0x40, DEF_STR( Off ) )
	PORT_DIPSETTING(    0x00, DEF_STR( On ) )
	PORT_BIT( 0x80, IP_ACTIVE_LOW, IPT_COIN1 ) // adds coins?, but maybe its the service switch?

	PORT_START("MAHJONG_P1_2")
	PORT_DIPNAME( 0x01, 0x01, "1-2" )
	PORT_DIPSETTING(    0x01, DEF_STR( Off ) )
	PORT_DIPSETTING(    0x00, DEF_STR( On ) )
	PORT_DIPNAME( 0x02, 0x02, DEF_STR( Unknown ) )
	PORT_DIPSETTING(    0x02, DEF_STR( Off ) )
	PORT_DIPSETTING(    0x00, DEF_STR( On ) )
	PORT_DIPNAME( 0x04, 0x04, DEF_STR( Unknown ) )
	PORT_DIPSETTING(    0x04, DEF_STR( Off ) )
	PORT_DIPSETTING(    0x00, DEF_STR( On ) )
	PORT_DIPNAME( 0x08, 0x08, DEF_STR( Unknown ) )
	PORT_DIPSETTING(    0x08, DEF_STR( Off ) )
	PORT_DIPSETTING(    0x00, DEF_STR( On ) )
	PORT_DIPNAME( 0x10, 0x10, DEF_STR( Unknown ) )
	PORT_DIPSETTING(    0x10, DEF_STR( Off ) )
	PORT_DIPSETTING(    0x00, DEF_STR( On ) )
	PORT_DIPNAME( 0x20, 0x20, DEF_STR( Unknown ) )
	PORT_DIPSETTING(    0x20, DEF_STR( Off ) )
	PORT_DIPSETTING(    0x00, DEF_STR( On ) )
	PORT_DIPNAME( 0x40, 0x40, DEF_STR( Unknown ) )
	PORT_DIPSETTING(    0x40, DEF_STR( Off ) )
	PORT_DIPSETTING(    0x00, DEF_STR( On ) )
	PORT_DIPNAME( 0x80, 0x80, DEF_STR( Unknown ) )
	PORT_DIPSETTING(    0x80, DEF_STR( Off ) )
	PORT_DIPSETTING(    0x00, DEF_STR( On ) )

	PORT_START("MAHJONG_P1_3")
	PORT_BIT( 0x01, IP_ACTIVE_LOW, IPT_UNKNOWN ) // unused?
	PORT_BIT( 0x02, IP_ACTIVE_LOW, IPT_UNKNOWN ) // unused?
	PORT_BIT( 0x04, IP_ACTIVE_LOW, IPT_MAHJONG_PON )
	PORT_BIT( 0x08, IP_ACTIVE_LOW, IPT_MAHJONG_L )
	PORT_BIT( 0x10, IP_ACTIVE_LOW, IPT_MAHJONG_H )
	PORT_BIT( 0x20, IP_ACTIVE_LOW, IPT_MAHJONG_D )
	PORT_BIT( 0x40, IP_ACTIVE_LOW, IPT_UNKNOWN ) // unused?
	PORT_BIT( 0x80, IP_ACTIVE_LOW, IPT_UNKNOWN ) // unused?

	PORT_START("MAHJONG_P1_4")
	PORT_BIT( 0x01, IP_ACTIVE_LOW, IPT_UNKNOWN ) // unused?
	PORT_BIT( 0x02, IP_ACTIVE_LOW, IPT_MAHJONG_RON )
	PORT_BIT( 0x04, IP_ACTIVE_LOW, IPT_MAHJONG_CHI )
	PORT_BIT( 0x08, IP_ACTIVE_LOW, IPT_MAHJONG_K )
	PORT_BIT( 0x10, IP_ACTIVE_LOW, IPT_MAHJONG_G )
	PORT_BIT( 0x20, IP_ACTIVE_LOW, IPT_MAHJONG_C )
	PORT_BIT( 0x40, IP_ACTIVE_LOW, IPT_UNKNOWN ) // unused?
	PORT_BIT( 0x80, IP_ACTIVE_LOW, IPT_UNKNOWN ) // unused?

	PORT_START("MAHJONG_P1_5")
	PORT_BIT( 0x01, IP_ACTIVE_LOW, IPT_UNKNOWN ) // unused?
	PORT_BIT( 0x02, IP_ACTIVE_LOW, IPT_MAHJONG_REACH )
	PORT_BIT( 0x04, IP_ACTIVE_LOW, IPT_MAHJONG_N )
	PORT_BIT( 0x08, IP_ACTIVE_LOW, IPT_MAHJONG_J )
	PORT_BIT( 0x10, IP_ACTIVE_LOW, IPT_MAHJONG_F )
	PORT_BIT( 0x20, IP_ACTIVE_LOW, IPT_MAHJONG_B )
	PORT_BIT( 0x40, IP_ACTIVE_LOW, IPT_UNKNOWN ) // unused?
	PORT_BIT( 0x80, IP_ACTIVE_LOW, IPT_UNKNOWN ) // unused?

	PORT_START("MAHJONG_P1_6")
	PORT_BIT( 0x01, IP_ACTIVE_LOW, IPT_START1 )
	PORT_BIT( 0x02, IP_ACTIVE_LOW, IPT_MAHJONG_KAN )
	PORT_BIT( 0x04, IP_ACTIVE_LOW, IPT_MAHJONG_M )
	PORT_BIT( 0x08, IP_ACTIVE_LOW, IPT_MAHJONG_I )
	PORT_BIT( 0x10, IP_ACTIVE_LOW, IPT_MAHJONG_E )
	PORT_BIT( 0x20, IP_ACTIVE_LOW, IPT_MAHJONG_A )
	PORT_BIT( 0x40, IP_ACTIVE_LOW, IPT_UNKNOWN ) // unused?
	PORT_BIT( 0x80, IP_ACTIVE_LOW, IPT_UNKNOWN ) // unused?

	PORT_START("MAHJONG_P2_1")
	PORT_DIPNAME( 0x01, 0x01, "2-1" )
	PORT_DIPSETTING(    0x01, DEF_STR( Off ) )
	PORT_DIPSETTING(    0x00, DEF_STR( On ) )
	PORT_DIPNAME( 0x02, 0x02, DEF_STR( Unknown ) )
	PORT_DIPSETTING(    0x02, DEF_STR( Off ) )
	PORT_DIPSETTING(    0x00, DEF_STR( On ) )
	PORT_DIPNAME( 0x04, 0x04, "P2 FF" ) // labaled FF in test mode, is this coin2 or some other button ?
	PORT_DIPSETTING(    0x04, DEF_STR( Off ) )
	PORT_DIPSETTING(    0x00, DEF_STR( On ) )
	PORT_DIPNAME( 0x08, 0x08, DEF_STR( Unknown ) )
	PORT_DIPSETTING(    0x08, DEF_STR( Off ) )
	PORT_DIPSETTING(    0x00, DEF_STR( On ) )
	PORT_DIPNAME( 0x10, 0x10, DEF_STR( Unknown ) )
	PORT_DIPSETTING(    0x10, DEF_STR( Off ) )
	PORT_DIPSETTING(    0x00, DEF_STR( On ) )
	PORT_DIPNAME( 0x20, 0x20, DEF_STR( Unknown ) )
	PORT_DIPSETTING(    0x20, DEF_STR( Off ) )
	PORT_DIPSETTING(    0x00, DEF_STR( On ) )
	PORT_DIPNAME( 0x40, 0x40, DEF_STR( Unknown ) )
	PORT_DIPSETTING(    0x40, DEF_STR( Off ) )
	PORT_DIPSETTING(    0x00, DEF_STR( On ) )
	PORT_DIPNAME( 0x80, 0x80, DEF_STR( Test ) )
	PORT_DIPSETTING(    0x80, DEF_STR( Off ) )
	PORT_DIPSETTING(    0x00, DEF_STR( On ) )

	PORT_START("MAHJONG_P2_2")
	PORT_DIPNAME( 0x01, 0x01, "2-2" )
	PORT_DIPSETTING(    0x01, DEF_STR( Off ) )
	PORT_DIPSETTING(    0x00, DEF_STR( On ) )
	PORT_DIPNAME( 0x02, 0x02, DEF_STR( Unknown ) )
	PORT_DIPSETTING(    0x02, DEF_STR( Off ) )
	PORT_DIPSETTING(    0x00, DEF_STR( On ) )
	PORT_DIPNAME( 0x04, 0x04, DEF_STR( Unknown ) )
	PORT_DIPSETTING(    0x04, DEF_STR( Off ) )
	PORT_DIPSETTING(    0x00, DEF_STR( On ) )
	PORT_DIPNAME( 0x08, 0x08, DEF_STR( Unknown ) )
	PORT_DIPSETTING(    0x08, DEF_STR( Off ) )
	PORT_DIPSETTING(    0x00, DEF_STR( On ) )
	PORT_DIPNAME( 0x10, 0x10, DEF_STR( Unknown ) )
	PORT_DIPSETTING(    0x10, DEF_STR( Off ) )
	PORT_DIPSETTING(    0x00, DEF_STR( On ) )
	PORT_DIPNAME( 0x20, 0x20, DEF_STR( Unknown ) )
	PORT_DIPSETTING(    0x20, DEF_STR( Off ) )
	PORT_DIPSETTING(    0x00, DEF_STR( On ) )
	PORT_DIPNAME( 0x40, 0x40, DEF_STR( Unknown ) )
	PORT_DIPSETTING(    0x40, DEF_STR( Off ) )
	PORT_DIPSETTING(    0x00, DEF_STR( On ) )
	PORT_DIPNAME( 0x80, 0x80, DEF_STR( Unknown ) )
	PORT_DIPSETTING(    0x80, DEF_STR( Off ) )
	PORT_DIPSETTING(    0x00, DEF_STR( On ) )

	PORT_START("MAHJONG_P2_3")
	PORT_BIT( 0x01, IP_ACTIVE_LOW, IPT_UNKNOWN ) // unused?
	PORT_BIT( 0x02, IP_ACTIVE_LOW, IPT_UNKNOWN ) // unused?
	PORT_BIT( 0x04, IP_ACTIVE_LOW, IPT_MAHJONG_PON ) PORT_PLAYER(2)
	PORT_BIT( 0x08, IP_ACTIVE_LOW, IPT_MAHJONG_L ) PORT_PLAYER(2)
	PORT_BIT( 0x10, IP_ACTIVE_LOW, IPT_MAHJONG_H ) PORT_PLAYER(2)
	PORT_BIT( 0x20, IP_ACTIVE_LOW, IPT_MAHJONG_D ) PORT_PLAYER(2)
	PORT_BIT( 0x40, IP_ACTIVE_LOW, IPT_UNKNOWN ) // unused?
	PORT_BIT( 0x80, IP_ACTIVE_LOW, IPT_UNKNOWN ) // unused?

	PORT_START("MAHJONG_P2_4")
	PORT_BIT( 0x01, IP_ACTIVE_LOW, IPT_UNKNOWN ) // unused?
	PORT_BIT( 0x02, IP_ACTIVE_LOW, IPT_MAHJONG_RON ) PORT_PLAYER(2)
	PORT_BIT( 0x04, IP_ACTIVE_LOW, IPT_MAHJONG_CHI ) PORT_PLAYER(2)
	PORT_BIT( 0x08, IP_ACTIVE_LOW, IPT_MAHJONG_K ) PORT_PLAYER(2)
	PORT_BIT( 0x10, IP_ACTIVE_LOW, IPT_MAHJONG_G ) PORT_PLAYER(2)
	PORT_BIT( 0x20, IP_ACTIVE_LOW, IPT_MAHJONG_C ) PORT_PLAYER(2)
	PORT_BIT( 0x40, IP_ACTIVE_LOW, IPT_UNKNOWN ) // unused?
	PORT_BIT( 0x80, IP_ACTIVE_LOW, IPT_UNKNOWN ) // unused?

	PORT_START("MAHJONG_P2_5")
	PORT_BIT( 0x01, IP_ACTIVE_LOW, IPT_UNKNOWN ) // unused?
	PORT_BIT( 0x02, IP_ACTIVE_LOW, IPT_MAHJONG_REACH ) PORT_PLAYER(2)
	PORT_BIT( 0x04, IP_ACTIVE_LOW, IPT_MAHJONG_N ) PORT_PLAYER(2)
	PORT_BIT( 0x08, IP_ACTIVE_LOW, IPT_MAHJONG_J ) PORT_PLAYER(2)
	PORT_BIT( 0x10, IP_ACTIVE_LOW, IPT_MAHJONG_F ) PORT_PLAYER(2)
	PORT_BIT( 0x20, IP_ACTIVE_LOW, IPT_MAHJONG_B ) PORT_PLAYER(2)
	PORT_BIT( 0x40, IP_ACTIVE_LOW, IPT_UNKNOWN ) // unused?
	PORT_BIT( 0x80, IP_ACTIVE_LOW, IPT_UNKNOWN ) // unused?

	PORT_START("MAHJONG_P2_6")
	PORT_BIT( 0x01, IP_ACTIVE_LOW, IPT_START2 )
	PORT_BIT( 0x02, IP_ACTIVE_LOW, IPT_MAHJONG_KAN ) PORT_PLAYER(2)
	PORT_BIT( 0x04, IP_ACTIVE_LOW, IPT_MAHJONG_M ) PORT_PLAYER(2)
	PORT_BIT( 0x08, IP_ACTIVE_LOW, IPT_MAHJONG_I ) PORT_PLAYER(2)
	PORT_BIT( 0x10, IP_ACTIVE_LOW, IPT_MAHJONG_E ) PORT_PLAYER(2)
	PORT_BIT( 0x20, IP_ACTIVE_LOW, IPT_MAHJONG_A ) PORT_PLAYER(2)
	PORT_BIT( 0x40, IP_ACTIVE_LOW, IPT_UNKNOWN ) // unused?
	PORT_BIT( 0x80, IP_ACTIVE_LOW, IPT_UNKNOWN ) // unused?
INPUT_PORTS_END



/*************************************
 *
 *  Graphics definitions
 *
 *************************************/

static const gfx_layout tiles8x8_layout =
{
	8,8,
	RGN_FRAC(1,3),
	3,
	{ RGN_FRAC(0,3), RGN_FRAC(1,3), RGN_FRAC(2,3) },
	{ 0, 1, 2, 3, 4, 5, 6, 7 },
	{ 0*8, 1*8, 2*8, 3*8, 4*8, 5*8, 6*8, 7*8 },
	8*8
};

static GFXDECODE_START( chinsan )
	GFXDECODE_ENTRY( "gfx1", 0, tiles8x8_layout, 0, 32 )
GFXDECODE_END

/*************************************
 *
 *  Sound interface
 *
 *************************************/

WRITE_LINE_MEMBER(chinsan_state::chin_adpcm_int)
=======
		m_maincpu(*this, "maincpu"),
		m_video_ram(*this, "video_ram"), m_color_ram(*this, "color_ram"),
		m_gfxdecode(*this, "gfxdecode"),
		m_adpcm(*this, "adpcm"),
		m_inputs_p1{ {*this, "p1_0"}, {*this, "p1_1"}, {*this, "p1_2"}, {*this, "p1_3"}, {*this, "p1_4"} },
		m_inputs_p2{ {*this, "p2_0"}, {*this, "p2_1"}, {*this, "p2_2"}, {*this, "p2_3"}, {*this, "p2_4"} },
		m_bank1(*this, "bank1"), m_bank0d(*this, "bank0d"), m_bank1d(*this, "bank1d"),
		m_tilemap(nullptr),
		m_int_enabled(false),
		m_port_select(0xff),
		m_adpcm_pos(0), m_adpcm_idle(1), m_adpcm_data(0), m_trigger(0)
	{ }

	DECLARE_WRITE8_MEMBER(input_select_w);
	DECLARE_READ8_MEMBER(input_p2_r);
	DECLARE_READ8_MEMBER(input_p1_r);

	uint32_t screen_update(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
	TILE_GET_INFO_MEMBER(tile_info);

	DECLARE_WRITE8_MEMBER(adpcm_w);
	DECLARE_WRITE_LINE_MEMBER(adpcm_int_w);

	INTERRUPT_GEN_MEMBER(vblank_int);
	DECLARE_WRITE8_MEMBER(ctrl_w);
	DECLARE_DRIVER_INIT(chinsan);

protected:
	virtual void machine_start() override;
	virtual void machine_reset() override;

private:
	required_device<z80_device> m_maincpu;
	required_shared_ptr<uint8_t> m_video_ram;
	required_shared_ptr<uint8_t> m_color_ram;
	required_device<gfxdecode_device> m_gfxdecode;
	optional_device<msm5205_device> m_adpcm;
	required_ioport m_inputs_p1[5];
	required_ioport m_inputs_p2[5];
	required_memory_bank m_bank1;
	optional_memory_bank m_bank0d;
	optional_memory_bank m_bank1d;

	std::unique_ptr<uint8_t[]> m_decrypted_opcodes;

	tilemap_t *m_tilemap;

	bool m_int_enabled;
	uint8_t m_port_select;
	uint32_t m_adpcm_pos;
	uint8_t m_adpcm_idle;
	uint8_t m_adpcm_data;
	uint8_t m_trigger;
};


//**************************************************************************
//  ADDRESS MAPS
//**************************************************************************

static ADDRESS_MAP_START( chinsan_map, AS_PROGRAM, 8, chinsan_state )
	AM_RANGE(0x0000, 0x7fff) AM_ROM
	AM_RANGE(0x8000, 0xbfff) AM_ROMBANK("bank1")
	AM_RANGE(0xc000, 0xdfff) AM_RAM AM_SHARE("nvram")
	AM_RANGE(0xe000, 0xefff) AM_RAM AM_SHARE("video_ram")
	AM_RANGE(0xf000, 0xf7ff) AM_RAM AM_SHARE("color_ram")
ADDRESS_MAP_END

static ADDRESS_MAP_START( decrypted_opcodes_map, AS_OPCODES, 8, chinsan_state )
	AM_RANGE(0x0000, 0x7fff) AM_ROMBANK("bank0d")
	AM_RANGE(0x8000, 0xbfff) AM_ROMBANK("bank1d")
ADDRESS_MAP_END

static ADDRESS_MAP_START( chinsan_io_map, AS_IO, 8, chinsan_state )
	ADDRESS_MAP_GLOBAL_MASK(0xff)
	AM_RANGE(0x00, 0x03) AM_DEVREADWRITE("ppi", i8255_device, read, write)
	AM_RANGE(0x10, 0x11) AM_DEVREADWRITE("ymsnd", ym2203_device, read, write)
	AM_RANGE(0x20, 0x20) AM_WRITE(adpcm_w)
	AM_RANGE(0x30, 0x30) AM_WRITE(ctrl_w)
ADDRESS_MAP_END

static ADDRESS_MAP_START( mayumi_io_map, AS_IO, 8, chinsan_state )
	ADDRESS_MAP_GLOBAL_MASK(0xff)
	AM_RANGE(0x30, 0x30) AM_READ_PORT("extra") AM_WRITE(ctrl_w)
	AM_RANGE(0xc0, 0xc3) AM_DEVREADWRITE("ppi", i8255_device, read, write)
	AM_RANGE(0xd0, 0xd1) AM_DEVREADWRITE("ymsnd", ym2203_device, read, write)
ADDRESS_MAP_END


//**************************************************************************
//  INPUTS
//**************************************************************************

static INPUT_PORTS_START( chinsan )
	PORT_START("DSW1")
	PORT_DIPNAME(0x07, 0x07, DEF_STR( Coinage ))     PORT_DIPLOCATION("SW-1:1,2,3")
	PORT_DIPSETTING(   0x00, DEF_STR( 1C_5C ))
	PORT_DIPSETTING(   0x01, DEF_STR( 1C_4C ))
	PORT_DIPSETTING(   0x02, DEF_STR( 1C_3C ))
	PORT_DIPSETTING(   0x03, DEF_STR( 1C_2C ))
	PORT_DIPSETTING(   0x04, DEF_STR( 4C_1C ))
	PORT_DIPSETTING(   0x05, DEF_STR( 3C_1C ))
	PORT_DIPSETTING(   0x06, DEF_STR( 2C_1C ))
	PORT_DIPSETTING(   0x07, DEF_STR( 1C_1C ))
	PORT_DIPUNKNOWN_DIPLOC(0x08, 0x08, "SW-1:4")
	PORT_DIPUNKNOWN_DIPLOC(0x10, 0x10, "SW-1:5")
	PORT_DIPNAME(0x20, 0x00, DEF_STR( Demo_Sounds )) PORT_DIPLOCATION("SW-1:6")
	PORT_DIPSETTING(   0x00, DEF_STR( On ))
	PORT_DIPSETTING(   0x20, DEF_STR( Off ))
	PORT_DIPUNKNOWN_DIPLOC(0x40, 0x40, "SW-1:7")
	PORT_DIPNAME(0x80, 0x80, DEF_STR( Flip_Screen )) PORT_DIPLOCATION("SW-1:8")
	PORT_DIPSETTING(   0x00, DEF_STR( On ))
	PORT_DIPSETTING(   0x80, DEF_STR( Off ))

	PORT_START("DSW2")
	PORT_DIPUNKNOWN_DIPLOC(0x01, 0x01, "SW-2:1")
	PORT_DIPUNKNOWN_DIPLOC(0x02, 0x02, "SW-2:2")
	PORT_DIPUNKNOWN_DIPLOC(0x04, 0x04, "SW-2:3")
	PORT_DIPUNKNOWN_DIPLOC(0x08, 0x08, "SW-2:4")
	PORT_DIPUNKNOWN_DIPLOC(0x10, 0x10, "SW-2:5")
	PORT_DIPUNKNOWN_DIPLOC(0x20, 0x20, "SW-2:6")
	PORT_DIPUNKNOWN_DIPLOC(0x40, 0x40, "SW-2:7")
	PORT_DIPUNKNOWN_DIPLOC(0x80, 0x80, "SW-2:8")

	PORT_START("p1_0")
	PORT_BIT( 0x01, IP_ACTIVE_LOW, IPT_START1 )
	PORT_BIT( 0x02, IP_ACTIVE_LOW, IPT_MAHJONG_KAN )
	PORT_BIT( 0x04, IP_ACTIVE_LOW, IPT_MAHJONG_M )
	PORT_BIT( 0x08, IP_ACTIVE_LOW, IPT_MAHJONG_I )
	PORT_BIT( 0x10, IP_ACTIVE_LOW, IPT_MAHJONG_E )
	PORT_BIT( 0x20, IP_ACTIVE_LOW, IPT_MAHJONG_A )
	PORT_BIT( 0x40, IP_ACTIVE_LOW, IPT_UNKNOWN )
	PORT_BIT( 0x80, IP_ACTIVE_LOW, IPT_UNKNOWN )

	PORT_START("p1_1")
	PORT_BIT( 0x01, IP_ACTIVE_LOW, IPT_UNKNOWN )
	PORT_BIT( 0x02, IP_ACTIVE_LOW, IPT_MAHJONG_REACH )
	PORT_BIT( 0x04, IP_ACTIVE_LOW, IPT_MAHJONG_N )
	PORT_BIT( 0x08, IP_ACTIVE_LOW, IPT_MAHJONG_J )
	PORT_BIT( 0x10, IP_ACTIVE_LOW, IPT_MAHJONG_F )
	PORT_BIT( 0x20, IP_ACTIVE_LOW, IPT_MAHJONG_B )
	PORT_BIT( 0x40, IP_ACTIVE_LOW, IPT_UNKNOWN )
	PORT_BIT( 0x80, IP_ACTIVE_LOW, IPT_UNKNOWN )

	PORT_START("p1_2")
	PORT_BIT( 0x01, IP_ACTIVE_LOW, IPT_UNKNOWN )
	PORT_BIT( 0x02, IP_ACTIVE_LOW, IPT_MAHJONG_RON )
	PORT_BIT( 0x04, IP_ACTIVE_LOW, IPT_MAHJONG_CHI )
	PORT_BIT( 0x08, IP_ACTIVE_LOW, IPT_MAHJONG_K )
	PORT_BIT( 0x10, IP_ACTIVE_LOW, IPT_MAHJONG_G )
	PORT_BIT( 0x20, IP_ACTIVE_LOW, IPT_MAHJONG_C )
	PORT_BIT( 0x40, IP_ACTIVE_LOW, IPT_UNKNOWN )
	PORT_BIT( 0x80, IP_ACTIVE_LOW, IPT_UNKNOWN )

	PORT_START("p1_3")
	PORT_BIT( 0x01, IP_ACTIVE_LOW, IPT_UNKNOWN )
	PORT_BIT( 0x02, IP_ACTIVE_LOW, IPT_UNKNOWN )
	PORT_BIT( 0x04, IP_ACTIVE_LOW, IPT_MAHJONG_PON )
	PORT_BIT( 0x08, IP_ACTIVE_LOW, IPT_MAHJONG_L )
	PORT_BIT( 0x10, IP_ACTIVE_LOW, IPT_MAHJONG_H )
	PORT_BIT( 0x20, IP_ACTIVE_LOW, IPT_MAHJONG_D )
	PORT_BIT( 0x40, IP_ACTIVE_LOW, IPT_UNKNOWN )
	PORT_BIT( 0x80, IP_ACTIVE_LOW, IPT_UNKNOWN )

	PORT_START("p1_4")
	PORT_BIT( 0x01, IP_ACTIVE_LOW, IPT_UNKNOWN )
	PORT_BIT( 0x02, IP_ACTIVE_LOW, IPT_UNKNOWN )
	PORT_BIT( 0x04, IP_ACTIVE_LOW, IPT_MAHJONG_FLIP_FLOP ) // labeled ff in test mode, i assume this means flip flop
	PORT_BIT( 0x08, IP_ACTIVE_LOW, IPT_UNKNOWN )
	PORT_BIT( 0x10, IP_ACTIVE_LOW, IPT_UNKNOWN )
	PORT_BIT( 0x20, IP_ACTIVE_LOW, IPT_UNKNOWN )
	PORT_BIT( 0x40, IP_ACTIVE_LOW, IPT_UNKNOWN )
	PORT_BIT( 0x80, IP_ACTIVE_LOW, IPT_COIN1 )

	PORT_START("p2_0")
	PORT_BIT( 0x01, IP_ACTIVE_LOW, IPT_START2 )
	PORT_BIT( 0x02, IP_ACTIVE_LOW, IPT_MAHJONG_KAN ) PORT_PLAYER(2)
	PORT_BIT( 0x04, IP_ACTIVE_LOW, IPT_MAHJONG_M )   PORT_PLAYER(2)
	PORT_BIT( 0x08, IP_ACTIVE_LOW, IPT_MAHJONG_I )   PORT_PLAYER(2)
	PORT_BIT( 0x10, IP_ACTIVE_LOW, IPT_MAHJONG_E )   PORT_PLAYER(2)
	PORT_BIT( 0x20, IP_ACTIVE_LOW, IPT_MAHJONG_A )   PORT_PLAYER(2)
	PORT_BIT( 0x40, IP_ACTIVE_LOW, IPT_UNKNOWN )
	PORT_BIT( 0x80, IP_ACTIVE_LOW, IPT_UNKNOWN )

	PORT_START("p2_1")
	PORT_BIT( 0x01, IP_ACTIVE_LOW, IPT_UNKNOWN )
	PORT_BIT( 0x02, IP_ACTIVE_LOW, IPT_MAHJONG_REACH ) PORT_PLAYER(2)
	PORT_BIT( 0x04, IP_ACTIVE_LOW, IPT_MAHJONG_N )     PORT_PLAYER(2)
	PORT_BIT( 0x08, IP_ACTIVE_LOW, IPT_MAHJONG_J )     PORT_PLAYER(2)
	PORT_BIT( 0x10, IP_ACTIVE_LOW, IPT_MAHJONG_F )     PORT_PLAYER(2)
	PORT_BIT( 0x20, IP_ACTIVE_LOW, IPT_MAHJONG_B )     PORT_PLAYER(2)
	PORT_BIT( 0x40, IP_ACTIVE_LOW, IPT_UNKNOWN )
	PORT_BIT( 0x80, IP_ACTIVE_LOW, IPT_UNKNOWN )

	PORT_START("p2_2")
	PORT_BIT( 0x01, IP_ACTIVE_LOW, IPT_UNKNOWN )
	PORT_BIT( 0x02, IP_ACTIVE_LOW, IPT_MAHJONG_RON ) PORT_PLAYER(2)
	PORT_BIT( 0x04, IP_ACTIVE_LOW, IPT_MAHJONG_CHI ) PORT_PLAYER(2)
	PORT_BIT( 0x08, IP_ACTIVE_LOW, IPT_MAHJONG_K )   PORT_PLAYER(2)
	PORT_BIT( 0x10, IP_ACTIVE_LOW, IPT_MAHJONG_G )   PORT_PLAYER(2)
	PORT_BIT( 0x20, IP_ACTIVE_LOW, IPT_MAHJONG_C )   PORT_PLAYER(2)
	PORT_BIT( 0x40, IP_ACTIVE_LOW, IPT_UNKNOWN )
	PORT_BIT( 0x80, IP_ACTIVE_LOW, IPT_UNKNOWN )

	PORT_START("p2_3")
	PORT_BIT( 0x01, IP_ACTIVE_LOW, IPT_UNKNOWN )
	PORT_BIT( 0x02, IP_ACTIVE_LOW, IPT_UNKNOWN )
	PORT_BIT( 0x04, IP_ACTIVE_LOW, IPT_MAHJONG_PON ) PORT_PLAYER(2)
	PORT_BIT( 0x08, IP_ACTIVE_LOW, IPT_MAHJONG_L )   PORT_PLAYER(2)
	PORT_BIT( 0x10, IP_ACTIVE_LOW, IPT_MAHJONG_H )   PORT_PLAYER(2)
	PORT_BIT( 0x20, IP_ACTIVE_LOW, IPT_MAHJONG_D )   PORT_PLAYER(2)
	PORT_BIT( 0x40, IP_ACTIVE_LOW, IPT_UNKNOWN )
	PORT_BIT( 0x80, IP_ACTIVE_LOW, IPT_UNKNOWN )

	PORT_START("p2_4")
	PORT_BIT( 0x01, IP_ACTIVE_LOW, IPT_UNKNOWN )
	PORT_BIT( 0x02, IP_ACTIVE_LOW, IPT_UNKNOWN )
	PORT_BIT( 0x04, IP_ACTIVE_LOW, IPT_MAHJONG_FLIP_FLOP ) PORT_PLAYER(2) // labeled ff in test mode, i assume this means flip flop
	PORT_BIT( 0x08, IP_ACTIVE_LOW, IPT_UNKNOWN )
	PORT_BIT( 0x10, IP_ACTIVE_LOW, IPT_UNKNOWN )
	PORT_BIT( 0x20, IP_ACTIVE_LOW, IPT_UNKNOWN )
	PORT_BIT( 0x40, IP_ACTIVE_LOW, IPT_SERVICE1 ) PORT_NAME("Statistics")
	PORT_BIT( 0x80, IP_ACTIVE_LOW, IPT_SERVICE )
INPUT_PORTS_END

static INPUT_PORTS_START( mayumi )
	PORT_INCLUDE(chinsan)

	PORT_MODIFY("DSW1")
	PORT_DIPUNKNOWN_DIPLOC(0x01, 0x01, "SW-1:8")
	PORT_DIPUNKNOWN_DIPLOC(0x02, 0x02, "SW-1:7")
	PORT_DIPNAME( 0x04, 0x04, DEF_STR( Service_Mode )) PORT_DIPLOCATION("SW-1:6")
	PORT_DIPSETTING(    0x04, DEF_STR( Off ))
	PORT_DIPSETTING(    0x00, DEF_STR( On ))
	PORT_DIPNAME( 0x18, 0x00, DEF_STR( Coinage ))      PORT_DIPLOCATION("SW-1:5,4")
	PORT_DIPSETTING(    0x00, DEF_STR( 1C_1C ))
	PORT_DIPSETTING(    0x08, DEF_STR( 1C_2C ))
	PORT_DIPSETTING(    0x10, DEF_STR( 1C_3C ))
	PORT_DIPSETTING(    0x18, DEF_STR( 2C_1C ))
	PORT_DIPUNKNOWN_DIPLOC(0x20, 0x20, "SW-1:3")
	PORT_DIPUNKNOWN_DIPLOC(0x40, 0x40, "SW-1:2")
	PORT_DIPNAME(0x80, 0x80, DEF_STR( Flip_Screen ))   PORT_DIPLOCATION("SW-1:1")
	PORT_DIPSETTING(   0x00, DEF_STR( On ))
	PORT_DIPSETTING(   0x80, DEF_STR( Off ))

	PORT_MODIFY("DSW2")
	PORT_DIPUNKNOWN_DIPLOC(0x01, 0x01, "SW-2:8")
	PORT_DIPUNKNOWN_DIPLOC(0x02, 0x02, "SW-2:7")
	PORT_DIPUNKNOWN_DIPLOC(0x04, 0x04, "SW-2:6")
	PORT_DIPUNKNOWN_DIPLOC(0x08, 0x08, "SW-2:5")
	PORT_DIPUNKNOWN_DIPLOC(0x10, 0x10, "SW-2:4")
	PORT_DIPUNKNOWN_DIPLOC(0x20, 0x20, "SW-2:3")
	PORT_DIPUNKNOWN_DIPLOC(0x40, 0x40, "SW-2:2")
	PORT_DIPUNKNOWN_DIPLOC(0x80, 0x80, "SW-2:1")

	PORT_MODIFY("p1_4")
	PORT_BIT( 0xff, IP_ACTIVE_LOW, IPT_UNKNOWN )

	PORT_MODIFY("p2_4")
	PORT_BIT( 0xff, IP_ACTIVE_LOW, IPT_UNKNOWN )

	PORT_START("extra")
	PORT_BIT( 0x80, IP_ACTIVE_HIGH, IPT_UNKNOWN )
	PORT_BIT( 0x40, IP_ACTIVE_LOW , IPT_COIN1 )
	PORT_BIT( 0x20, IP_ACTIVE_HIGH, IPT_UNKNOWN )
	PORT_BIT( 0x10, IP_ACTIVE_HIGH, IPT_SERVICE )  PORT_TOGGLE
	PORT_BIT( 0x08, IP_ACTIVE_HIGH, IPT_SERVICE1 ) PORT_TOGGLE PORT_NAME("Statistics")
	PORT_BIT( 0x04, IP_ACTIVE_HIGH, IPT_UNKNOWN )
	PORT_BIT( 0x02, IP_ACTIVE_HIGH, IPT_UNKNOWN )
	PORT_BIT( 0x01, IP_ACTIVE_HIGH, IPT_MEMORY_RESET )
INPUT_PORTS_END


//**************************************************************************
//  INPUT PORT HANDLING
//**************************************************************************

WRITE8_MEMBER( chinsan_state::input_select_w )
{
	// 765-----  unknown
	// ---43210  input select (shared for player 1 and 2)

	m_port_select = data;
}

READ8_MEMBER( chinsan_state::input_p1_r )
{
	uint8_t data = 0xff;

	if (BIT(m_port_select, 0) == 0) data &= m_inputs_p1[0]->read();
	if (BIT(m_port_select, 1) == 0) data &= m_inputs_p1[1]->read();
	if (BIT(m_port_select, 2) == 0) data &= m_inputs_p1[2]->read();
	if (BIT(m_port_select, 3) == 0) data &= m_inputs_p1[3]->read();
	if (BIT(m_port_select, 4) == 0) data &= m_inputs_p1[4]->read();

	return data;
}

READ8_MEMBER( chinsan_state::input_p2_r )
{
	uint8_t data = 0xff;

	if (BIT(m_port_select, 0) == 0) data &= m_inputs_p2[0]->read();
	if (BIT(m_port_select, 1) == 0) data &= m_inputs_p2[1]->read();
	if (BIT(m_port_select, 2) == 0) data &= m_inputs_p2[2]->read();
	if (BIT(m_port_select, 3) == 0) data &= m_inputs_p2[3]->read();
	if (BIT(m_port_select, 4) == 0) data &= m_inputs_p2[4]->read();

	return data;
}


//**************************************************************************
//  VIDEO EMULATION
//**************************************************************************

uint32_t chinsan_state::screen_update(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect)
{
	m_tilemap->mark_all_dirty();
	m_tilemap->draw(screen, bitmap, cliprect, 0, 0);

	return 0;
}


//**************************************************************************
//  DRAWGFX LAYOUTS
//**************************************************************************

static GFXDECODE_START( chinsan )
	GFXDECODE_ENTRY("gfx1", 0, gfx_8x8x3_planar, 0, 32)
GFXDECODE_END

TILE_GET_INFO_MEMBER( chinsan_state::tile_info )
{
	uint16_t code = m_video_ram[tile_index] | (m_video_ram[tile_index + 0x800] << 8);

	// 76543---  color
	// -----210  unknown
	uint8_t color = m_color_ram[tile_index] >> 3;

	SET_TILE_INFO_MEMBER(0, code, color, 0);
}


//**************************************************************************
//  AUDIO
//**************************************************************************

WRITE8_MEMBER( chinsan_state::adpcm_w )
{
	m_adpcm_pos = data << 8;
	m_adpcm_idle = 0;
	m_adpcm->reset_w(0);
}

WRITE_LINE_MEMBER( chinsan_state::adpcm_int_w )
>>>>>>> upstream/master
{
	if (m_adpcm_pos >= 0x10000 || m_adpcm_idle)
	{
		//m_adpcm_idle = 1;
		m_adpcm->reset_w(1);
		m_trigger = 0;
	}
	else
	{
<<<<<<< HEAD
		UINT8 *ROM = memregion("adpcm")->base();
=======
		uint8_t *ROM = memregion("adpcm")->base();
>>>>>>> upstream/master

		m_adpcm_data = ((m_trigger ? (ROM[m_adpcm_pos] & 0x0f) : (ROM[m_adpcm_pos] & 0xf0) >> 4));
		m_adpcm->data_w(m_adpcm_data & 0xf);
		m_trigger ^= 1;
<<<<<<< HEAD
		if(m_trigger == 0)
=======
		if (m_trigger == 0)
>>>>>>> upstream/master
		{
			m_adpcm_pos++;
			if ((ROM[m_adpcm_pos] & 0xff) == 0x70)
				m_adpcm_idle = 1;
		}
	}
}


<<<<<<< HEAD
/*************************************
 *
 *  Machine driver
 *
 *************************************/

void chinsan_state::machine_start()
{
	membank("bank1")->configure_entries(0, 4, memregion("maincpu")->base() + 0x8000, 0x4000);
	membank("bank0d")->set_base(m_decrypted_opcodes);
	membank("bank1d")->configure_entries(0, 4, m_decrypted_opcodes + 0x8000, 0x4000);

	save_item(NAME(m_adpcm_idle));
	save_item(NAME(m_port_select));
	save_item(NAME(m_adpcm_pos));
=======
//**************************************************************************
//  MACHINE EMULATION
//**************************************************************************

INTERRUPT_GEN_MEMBER( chinsan_state::vblank_int )
{
	if (m_int_enabled)
		device.execute().set_input_line(INPUT_LINE_IRQ0, HOLD_LINE);
}

WRITE8_MEMBER( chinsan_state::ctrl_w )
{
	// 76------  rom bank
	// --5432--  unknown
	// ------1-  flip screen
	// -------0  interrupt enable

	m_int_enabled = bool(BIT(data, 0));
	flip_screen_set(BIT(data, 1));

	if (m_bank1d.found())
	{
		int bank = (BIT(data, 7) << 1) | BIT(data, 6);
		m_bank1->set_entry(bank);
		m_bank1d->set_entry(bank);
	}
	else
	{
		// bank bits have switched for mayumi
		int bank = (BIT(data, 6) << 1) | BIT(data, 7);
		m_bank1->set_entry(bank);
	}
}

void chinsan_state::machine_start()
{
	m_tilemap = &machine().tilemap().create(*m_gfxdecode, tilemap_get_info_delegate(FUNC(chinsan_state::tile_info), this), TILEMAP_SCAN_ROWS, 8, 8, 64, 32);

	m_bank1->configure_entries(0, 4, memregion("maincpu")->base() + 0x8000, 0x4000);

	if (m_bank0d.found())
		m_bank0d->set_base(m_decrypted_opcodes.get());
	if (m_bank1d.found())
		m_bank1d->configure_entries(0, 4, m_decrypted_opcodes.get() + 0x8000, 0x4000);

	save_item(NAME(m_int_enabled));
	save_item(NAME(m_port_select));
	save_item(NAME(m_adpcm_pos));
	save_item(NAME(m_adpcm_idle));
>>>>>>> upstream/master
	save_item(NAME(m_adpcm_data));
	save_item(NAME(m_trigger));
}

void chinsan_state::machine_reset()
{
<<<<<<< HEAD
	m_adpcm_idle = 1;
	m_port_select = 0;
	m_adpcm_pos = 0;
=======
	m_int_enabled = false;
	m_port_select = 0xff;
	m_adpcm_pos = 0;
	m_adpcm_idle = 1;
>>>>>>> upstream/master
	m_adpcm_data = 0;
	m_trigger = 0;
}

<<<<<<< HEAD

static MACHINE_CONFIG_START( chinsan, chinsan_state )

	/* basic machine hardware */
	MCFG_CPU_ADD("maincpu", Z80,10000000/2)      /* ? MHz */
	MCFG_CPU_PROGRAM_MAP(chinsan_map)
	MCFG_CPU_IO_MAP(chinsan_io)
	MCFG_CPU_DECRYPTED_OPCODES_MAP(decrypted_opcodes_map)
	MCFG_CPU_VBLANK_INT_DRIVER("screen", chinsan_state,  irq0_line_hold)


	/* video hardware */
=======
DRIVER_INIT_MEMBER( chinsan_state, chinsan )
{
	m_decrypted_opcodes = std::make_unique<uint8_t[]>(0x18000);
	downcast<mc8123_device &>(*m_maincpu).decode(memregion("maincpu")->base(), m_decrypted_opcodes.get(), 0x18000);
}


//**************************************************************************
//  MACHINE DEFINTIONS
//**************************************************************************

// C1-00114-B
static MACHINE_CONFIG_START( chinsan )
	MCFG_CPU_ADD("maincpu", MC8123, XTAL_10MHz/2) // 317-5012
	MCFG_CPU_PROGRAM_MAP(chinsan_map)
	MCFG_CPU_IO_MAP(chinsan_io_map)
	MCFG_CPU_DECRYPTED_OPCODES_MAP(decrypted_opcodes_map)
	MCFG_CPU_VBLANK_INT_DRIVER("screen", chinsan_state, vblank_int)

	MCFG_NVRAM_ADD_0FILL("nvram")

	MCFG_DEVICE_ADD("ppi", I8255A, 0)
	MCFG_I8255_OUT_PORTA_CB(WRITE8(chinsan_state, input_select_w))
	MCFG_I8255_IN_PORTB_CB(READ8(chinsan_state, input_p2_r))
	MCFG_I8255_IN_PORTC_CB(READ8(chinsan_state, input_p1_r))

	// video hardware
>>>>>>> upstream/master
	MCFG_SCREEN_ADD("screen", RASTER)
	MCFG_SCREEN_SIZE(512, 256)
	MCFG_SCREEN_REFRESH_RATE(60)
	MCFG_SCREEN_VBLANK_TIME(ATTOSECONDS_IN_USEC(0))
	MCFG_SCREEN_VISIBLE_AREA(24, 512-24-1, 16, 256-16-1)
<<<<<<< HEAD
	MCFG_SCREEN_UPDATE_DRIVER(chinsan_state, screen_update_chinsan)
	MCFG_SCREEN_PALETTE("palette")

	MCFG_GFXDECODE_ADD("gfxdecode", "palette", chinsan)
	MCFG_PALETTE_ADD("palette", 0x100)
	MCFG_PALETTE_INIT_OWNER(chinsan_state, chinsan)

	/* sound hardware */
	MCFG_SPEAKER_STANDARD_MONO("mono")

	MCFG_SOUND_ADD("ymsnd", YM2203, 1500000) /* ? Mhz */
	MCFG_AY8910_PORT_A_READ_CB(IOPORT("DSW1"))
	MCFG_AY8910_PORT_B_READ_CB(IOPORT("DSW2"))
	MCFG_AY8910_PORT_A_WRITE_CB(WRITE8(chinsan_state, ym_port_w1))
	MCFG_AY8910_PORT_B_WRITE_CB(WRITE8(chinsan_state, ym_port_w2))
=======
	MCFG_SCREEN_UPDATE_DRIVER(chinsan_state, screen_update)
	MCFG_SCREEN_PALETTE("palette")

	MCFG_GFXDECODE_ADD("gfxdecode", "palette", chinsan)
	MCFG_PALETTE_ADD_RRRRGGGGBBBB_PROMS("palette", "proms", 256)

	// sound hardware
	MCFG_SPEAKER_STANDARD_MONO("mono")

	MCFG_SOUND_ADD("ymsnd", YM2203, XTAL_10MHz/8)
	MCFG_AY8910_PORT_A_READ_CB(IOPORT("DSW1"))
	MCFG_AY8910_PORT_B_READ_CB(IOPORT("DSW2"))
>>>>>>> upstream/master
	MCFG_SOUND_ROUTE(0, "mono", 0.15)
	MCFG_SOUND_ROUTE(1, "mono", 0.15)
	MCFG_SOUND_ROUTE(2, "mono", 0.15)
	MCFG_SOUND_ROUTE(3, "mono", 0.10)

<<<<<<< HEAD
	MCFG_SOUND_ADD("adpcm", MSM5205, 384000)
	MCFG_MSM5205_VCLK_CB(WRITELINE(chinsan_state, chin_adpcm_int)) /* interrupt function */
	MCFG_MSM5205_PRESCALER_SELECTOR(MSM5205_S64_4B)  /* 8kHz */
	MCFG_SOUND_ROUTE(ALL_OUTPUTS, "mono", 0.50)
MACHINE_CONFIG_END



/*************************************
 *
 *  ROM definition(s)
 *
 *************************************/
=======
	MCFG_SOUND_ADD("adpcm", MSM5205, XTAL_384kHz)
	MCFG_MSM5205_VCLK_CB(WRITELINE(chinsan_state, adpcm_int_w))
	MCFG_MSM5205_PRESCALER_SELECTOR(S64_4B) // 8kHz
	MCFG_SOUND_ROUTE(ALL_OUTPUTS, "mono", 0.50)
MACHINE_CONFIG_END

static MACHINE_CONFIG_DERIVED( mayumi, chinsan )
	// standard Z80 instead of MC-8123
	MCFG_DEVICE_REMOVE("maincpu")
	MCFG_CPU_ADD("maincpu", Z80, XTAL_10MHz/2)
	MCFG_CPU_PROGRAM_MAP(chinsan_map)
	MCFG_CPU_IO_MAP(mayumi_io_map)
	MCFG_CPU_VBLANK_INT_DRIVER("screen", chinsan_state, vblank_int)

	// no ADPCM
	MCFG_DEVICE_REMOVE("adpcm")
MACHINE_CONFIG_END


//**************************************************************************
//  ROM DEFINITIONS
//**************************************************************************
>>>>>>> upstream/master

ROM_START( chinsan )
	ROM_REGION( 0x18000, "maincpu", 0 ) /* encrypted code / data */
	ROM_LOAD( "mm00.7d", 0x00000, 0x08000, CRC(f7a4414f) SHA1(f65223b2928f610ab97fda2f2c008806cf2420e5) )
	ROM_CONTINUE(        0x00000, 0x08000 ) // first half is blank
	ROM_LOAD( "mm01.8d", 0x08000, 0x10000, CRC(c69ddbf5) SHA1(9533365c1761b113174d53a2e23ce6a7baca7dfe) )

<<<<<<< HEAD
	ROM_REGION( 0x2000, "user1", 0 ) /* MC8123 key */
	ROM_LOAD( "317-5012.key",  0x0000, 0x2000, CRC(2ecfb132) SHA1(3110ef82080dd7d908cc6bf34c6643f187f90b29) )

	ROM_REGION( 0x30000, "gfx1", 0 )
	ROM_LOAD( "mm20.7k", 0x00000, 0x10000, CRC(54efb409) SHA1(333adadd7f3dc3393dbe334303bae544b3d26c00) )
	ROM_LOAD( "mm21.8k", 0x10000, 0x10000, CRC(25f6c827) SHA1(add72a3cfa2f24105e36d0464c2db6a6bedd4139) )
	ROM_LOAD( "mm22.9k", 0x20000, 0x10000, CRC(6092f6e1) SHA1(32f53027dc954e314d7c5d04ff53f17358bbcf77) )
=======
	ROM_REGION( 0x2000, "maincpu:key", 0 ) /* MC8123 key */
	ROM_LOAD( "317-5012.key",  0x0000, 0x2000, CRC(2ecfb132) SHA1(3110ef82080dd7d908cc6bf34c6643f187f90b29) )

	ROM_REGION( 0x30000, "gfx1", 0 )
	ROM_LOAD( "mm22.9k", 0x00000, 0x10000, CRC(6092f6e1) SHA1(32f53027dc954e314d7c5d04ff53f17358bbcf77) )
	ROM_LOAD( "mm21.8k", 0x10000, 0x10000, CRC(25f6c827) SHA1(add72a3cfa2f24105e36d0464c2db6a6bedd4139) )
	ROM_LOAD( "mm20.7k", 0x20000, 0x10000, CRC(54efb409) SHA1(333adadd7f3dc3393dbe334303bae544b3d26c00) )
>>>>>>> upstream/master

	ROM_REGION( 0x10000, "adpcm", 0 ) /* M5205 samples */
	ROM_LOAD( "mm40.13d", 0x00000, 0x10000, CRC(a408b8f7) SHA1(60a2644922cb60c0a1a3409761c7e50924360313) )

	ROM_REGION( 0x20, "user2", 0 )
	ROM_LOAD( "mm60.2c", 0x000, 0x020, CRC(88477178) SHA1(03c1c9e3e88a5ae9970cb4b872ad4b6e4d77a6da) )

<<<<<<< HEAD
	ROM_REGION( 0x300, "color_proms", 0 )
	ROM_LOAD( "mm61.9m",  0x000, 0x100, CRC(57024262) SHA1(e084e6baa3c529217f6f8e37c9dd5f0687ba2fc4) ) // b
	ROM_LOAD( "mm62.9n",  0x100, 0x100, CRC(b5a1dbe5) SHA1(770a791c061ce422f860bb8d32f82bbbf9b4d12a) ) // g
	ROM_LOAD( "mm63.10n", 0x200, 0x100, CRC(b65e3567) SHA1(f146af51dfaa5b4bf44c4e27f1a0292f8fd07ce9) ) // r
ROM_END


/*************************************
 *
 *  Driver initialization
 *
 *************************************/

DRIVER_INIT_MEMBER(chinsan_state,chinsan)
{
	m_decrypted_opcodes = auto_alloc_array(machine(), UINT8, 0x18000);
	mc8123_decode(memregion("maincpu")->base(), m_decrypted_opcodes, memregion("user1")->base(), 0x18000);
}


/*************************************
 *
 *  Game driver(s)
 *
 *************************************/

GAME( 1987, chinsan,  0,    chinsan, chinsan, chinsan_state, chinsan, ROT0, "Sanritsu", "Ganbare Chinsan Ooshoubu (MC-8123A, 317-5012)", MACHINE_SUPPORTS_SAVE )
=======
	ROM_REGION( 0x300, "proms", 0 )
	ROM_LOAD( "mm63.10n", 0x000, 0x100, CRC(b65e3567) SHA1(f146af51dfaa5b4bf44c4e27f1a0292f8fd07ce9) ) // r
	ROM_LOAD( "mm62.9n",  0x100, 0x100, CRC(b5a1dbe5) SHA1(770a791c061ce422f860bb8d32f82bbbf9b4d12a) ) // g
	ROM_LOAD( "mm61.9m",  0x200, 0x100, CRC(57024262) SHA1(e084e6baa3c529217f6f8e37c9dd5f0687ba2fc4) ) // b
ROM_END

ROM_START( mayumi )
	ROM_REGION( 0x18000, "maincpu", 0 )
	ROM_LOAD( "my00.bin",  0x00000, 0x08000, CRC(33189e37) SHA1(cbf75f56360ef7da5b7b1207b58cd0d72bcaf207) )
	ROM_LOAD( "my01.bin",  0x08000, 0x10000, CRC(5280fb39) SHA1(cee7653f4353031701ec1608881b37073b178d9f) ) // banked

	ROM_REGION( 0x30000, "gfx1", 0 )
	ROM_LOAD( "my10.bin", 0x00000, 0x10000, CRC(3b4f4f97) SHA1(50bda1484e965f15630bd2e05861d74ddeb0d88e) )
	ROM_LOAD( "my20.bin", 0x10000, 0x10000, CRC(18544029) SHA1(74bd8bb422db33bd7af08afbf9b801bd31a3f199) )
	ROM_LOAD( "my30.bin", 0x20000, 0x10000, CRC(7f22d53f) SHA1(f8e5874ba0fa003ba0d6a504b2169acdf1491484) )

	ROM_REGION( 0x0300, "proms", 0 )
	ROM_LOAD( "my-9m.bin", 0x0000,  0x0100, CRC(b18fd669) SHA1(e2b1477c1bc49994b0b652d63a2205363aab9a74) ) // r
	ROM_LOAD( "my-9l.bin", 0x0100,  0x0100, CRC(f3fef561) SHA1(247f579fe91ad7e516c93a873b2ecca780bf6da0) ) // g
	ROM_LOAD( "my-9k.bin", 0x0200,  0x0100, CRC(3e7a8012) SHA1(24129586a1c39f68dad274b5afbdd6c027ab0901) ) // b
ROM_END


//**************************************************************************
//  SYSTEM DRIVERS
//**************************************************************************

//    YEAR  NAME      PARENT  MACHINE  INPUT    CLASS          INIT     ROTATION  COMPANY           FULLNAME                                         FLAGS
GAME( 1987, chinsan,  0,      chinsan, chinsan, chinsan_state, chinsan, ROT0,     "Sanritsu",       "Ganbare Chinsan Ooshoubu (MC-8123A, 317-5012)", MACHINE_SUPPORTS_SAVE )
GAME( 1988, mayumi,   0,      mayumi,  mayumi,  chinsan_state, 0,       ROT0,     "Victory L.L.C.", "Kiki-Ippatsu Mayumi-chan",                      MACHINE_SUPPORTS_SAVE )
>>>>>>> upstream/master
