<<<<<<< HEAD
// license:???
// copyright-holders:Mike Coates, Peter J.C.Clare
/*****************************************************************************/
/*                                                                           */
/*                    (C) Copyright       Peter J.C.Clare                    */
/*                                                                           */
/*****************************************************************************/
/*                                                                           */
/*                                                                           */
/*      Module name:    carnival.c                                           */
/*                                                                           */
/*      Creation date:  15/03/98                Revision date:  09/01/99     */
/*                                                                           */
/*      Produced by:    Peter J.C.Clare                                      */
/*                                                                           */
/*                                                                           */
/*      Abstract:                                                            */
/*                                                                           */
/*              MAME sound & music driver for Sega/Gremlin Carnival.         */
/*                                                                           */
/*****************************************************************************/
/*                                                                           */
/*      Acknowledgements:                                                    */
/*                                                                           */
/*      Mike Coates, for the original Carnival MAME sound driver.            */
/*      Virtu-Al, for the sound samples & hardware information.              */
/*      The MAME Team, for the emulator framework.                           */
/*                                                                           */
/*****************************************************************************/
/*                                                                           */
/*      Revision history                                                     */
/*      ================                                                     */
/*                                                                           */
/*         Date     Vsn.  Initials   Description                             */
/*         ~~~~     ~~~~  ~~~~~~~~   ~~~~~~~~~~~                             */
/*      03/20/2007  1.1      ZV      Moved structures from driver to make    */
/*                                   file more self contained.               */
/*                                                                           */
/*****************************************************************************/
=======
// license:BSD-3-Clause
// copyright-holders:Zsolt Vasvari, hap
/*
 *  Carnival audio routines
 */
>>>>>>> upstream/master

#include "emu.h"
#include "includes/vicdual.h"


<<<<<<< HEAD
#define PSG_CLOCK       (3579545 / 3)   /* Hz */


/* output port 0x01 definitions - sound effect drive outputs */
#define OUT_PORT_1_RIFLE_SHOT   0x01
#define OUT_PORT_1_CLANG        0x02
#define OUT_PORT_1_DUCK_1       0x04
#define OUT_PORT_1_DUCK_2       0x08
#define OUT_PORT_1_DUCK_3       0x10
#define OUT_PORT_1_PIPE_HIT     0x20
#define OUT_PORT_1_BONUS_1      0x40
#define OUT_PORT_1_BONUS_2      0x80


/* output port 0x02 definitions - sound effect drive outputs */
#define OUT_PORT_2_BEAR         0x04
#define OUT_PORT_2_MUSIC_T1     0x08
#define OUT_PORT_2_MUSIC_RESET  0x10
#define OUT_PORT_2_RANKING      0x20


/* music CPU port definitions */
#define MUSIC_PORT2_PSG_BDIR    0x40    /* bit 6 on P2 */
#define MUSIC_PORT2_PSG_BC1     0x80    /* bit 7 on P2 */


#define PSG_BC_INACTIVE         0
#define PSG_BC_READ             MUSIC_PORT2_PSG_BC1
#define PSG_BC_WRITE            MUSIC_PORT2_PSG_BDIR
#define PSG_BC_LATCH_ADDRESS    ( MUSIC_PORT2_PSG_BDIR | MUSIC_PORT2_PSG_BC1 )


=======
/* output port 0x01 definitions - sound effect drive outputs */
#define OUT_PORT_1_RIFLE        0x01
#define OUT_PORT_1_CLANG        0x02
#define OUT_PORT_1_DUCK1        0x04
#define OUT_PORT_1_DUCK2        0x08
#define OUT_PORT_1_DUCK3        0x10
#define OUT_PORT_1_PIPEHIT      0x20
#define OUT_PORT_1_BONUS1       0x40
#define OUT_PORT_1_BONUS2       0x80

/* output port 0x02 definitions - sound effect drive outputs */
#define OUT_PORT_2_BEAR         0x04
#define OUT_PORT_2_RANKING      0x20


>>>>>>> upstream/master
#define PLAY(samp,id,loop)      samp->start( id, id, loop )
#define STOP(samp,id)           samp->stop( id )


/* sample file names */
static const char *const carnival_sample_names[] =
{
	"*carnival",
	"bear",
	"bonus1",
	"bonus2",
	"clang",
	"duck1",
	"duck2",
	"duck3",
	"pipehit",
	"ranking",
	"rifle",
<<<<<<< HEAD
	0
};

=======
	nullptr
};


>>>>>>> upstream/master
/* sample IDs - must match sample file name table above */
enum
{
	SND_BEAR = 0,
<<<<<<< HEAD
	SND_BONUS_1,
	SND_BONUS_2,
	SND_CLANG,
	SND_DUCK_1,
	SND_DUCK_2,
	SND_DUCK_3,
	SND_PIPE_HIT,
	SND_RANKING,
	SND_RIFLE_SHOT
};

WRITE8_MEMBER( vicdual_state::carnival_audio_1_w )
{
	static int port1State = 0;
=======
	SND_BONUS1,
	SND_BONUS2,
	SND_CLANG,
	SND_DUCK1,
	SND_DUCK2,
	SND_DUCK3,
	SND_PIPEHIT,
	SND_RANKING,
	SND_RIFLE
};


WRITE8_MEMBER( vicdual_state::carnival_audio_1_w )
{
>>>>>>> upstream/master
	int bitsChanged;
	int bitsGoneHigh;
	int bitsGoneLow;

<<<<<<< HEAD

	/* U64 74LS374 8 bit latch */

	/* bit 0: connector pin 36 - rifle shot */
	/* bit 1: connector pin 35 - clang */
	/* bit 2: connector pin 33 - duck #1 */
	/* bit 3: connector pin 34 - duck #2 */
	/* bit 4: connector pin 32 - duck #3 */
	/* bit 5: connector pin 31 - pipe hit */
	/* bit 6: connector pin 30 - bonus #1 */
	/* bit 7: connector pin 29 - bonus #2 */

	bitsChanged  = port1State ^ data;
	bitsGoneHigh = bitsChanged & data;
	bitsGoneLow  = bitsChanged & ~data;

	port1State = data;

	if ( bitsGoneLow & OUT_PORT_1_RIFLE_SHOT )
	{
		PLAY( m_samples, SND_RIFLE_SHOT, 0 );
=======
	bitsChanged  = m_port1State ^ data;
	bitsGoneHigh = bitsChanged & data;
	bitsGoneLow  = bitsChanged & ~data;

	m_port1State = data;

	if ( bitsGoneLow & OUT_PORT_1_RIFLE )
	{
		PLAY( m_samples, SND_RIFLE, 0 );
>>>>>>> upstream/master
	}

	if ( bitsGoneLow & OUT_PORT_1_CLANG )
	{
		PLAY( m_samples, SND_CLANG, 0 );
	}

<<<<<<< HEAD
	if ( bitsGoneLow & OUT_PORT_1_DUCK_1 )
	{
		PLAY( m_samples, SND_DUCK_1, 1 );
	}
	if ( bitsGoneHigh & OUT_PORT_1_DUCK_1 )
	{
		STOP( m_samples, SND_DUCK_1 );
	}

	if ( bitsGoneLow & OUT_PORT_1_DUCK_2 )
	{
		PLAY( m_samples, SND_DUCK_2, 1 );
	}
	if ( bitsGoneHigh & OUT_PORT_1_DUCK_2 )
	{
		STOP( m_samples, SND_DUCK_2 );
	}

	if ( bitsGoneLow & OUT_PORT_1_DUCK_3 )
	{
		PLAY( m_samples, SND_DUCK_3, 1 );
	}
	if ( bitsGoneHigh & OUT_PORT_1_DUCK_3 )
	{
		STOP( m_samples, SND_DUCK_3 );
	}

	if ( bitsGoneLow & OUT_PORT_1_PIPE_HIT )
	{
		PLAY( m_samples, SND_PIPE_HIT, 0 );
	}

	if ( bitsGoneLow & OUT_PORT_1_BONUS_1 )
	{
		PLAY( m_samples, SND_BONUS_1, 0 );
	}

	if ( bitsGoneLow & OUT_PORT_1_BONUS_2 )
	{
		PLAY( m_samples, SND_BONUS_2, 0 );
=======
	if ( bitsGoneLow & OUT_PORT_1_DUCK1 )
	{
		PLAY( m_samples, SND_DUCK1, 1 );
	}
	if ( bitsGoneHigh & OUT_PORT_1_DUCK1 )
	{
		STOP( m_samples, SND_DUCK1 );
	}

	if ( bitsGoneLow & OUT_PORT_1_DUCK2 )
	{
		PLAY( m_samples, SND_DUCK2, 1 );
	}
	if ( bitsGoneHigh & OUT_PORT_1_DUCK2 )
	{
		STOP( m_samples, SND_DUCK2 );
	}

	if ( bitsGoneLow & OUT_PORT_1_DUCK3 )
	{
		PLAY( m_samples, SND_DUCK3, 1 );
	}
	if ( bitsGoneHigh & OUT_PORT_1_DUCK3 )
	{
		STOP( m_samples, SND_DUCK3 );
	}

	if ( bitsGoneLow & OUT_PORT_1_PIPEHIT )
	{
		PLAY( m_samples, SND_PIPEHIT, 0 );
	}

	if ( bitsGoneLow & OUT_PORT_1_BONUS1 )
	{
		PLAY( m_samples, SND_BONUS1, 0 );
	}

	if ( bitsGoneLow & OUT_PORT_1_BONUS2 )
	{
		PLAY( m_samples, SND_BONUS2, 0 );
>>>>>>> upstream/master
	}
}


WRITE8_MEMBER( vicdual_state::carnival_audio_2_w )
{
	int bitsChanged;
<<<<<<< HEAD
	int bitsGoneHigh;
	int bitsGoneLow;

	/* U63 74LS374 8 bit latch */

	/* bit 0: connector pin 48 */
	/* bit 1: connector pin 47 */
	/* bit 2: connector pin 45 - bear */
	/* bit 3: connector pin 46 - Music !T1 input */
	/* bit 4: connector pin 44 - Music reset */
	/* bit 5: connector pin 43 - ranking */
	/* bit 6: connector pin 42 */
	/* bit 7: connector pin 41 */

	bitsChanged  = m_port2State ^ data;
	bitsGoneHigh = bitsChanged & data;
=======
	//int bitsGoneHigh;
	int bitsGoneLow;

	bitsChanged  = m_port2State ^ data;
	//bitsGoneHigh = bitsChanged & data;
>>>>>>> upstream/master
	bitsGoneLow  = bitsChanged & ~data;

	m_port2State = data;

	if ( bitsGoneLow & OUT_PORT_2_BEAR )
<<<<<<< HEAD
		PLAY( m_samples, SND_BEAR, 0 );

	if ( bitsGoneLow & OUT_PORT_2_RANKING )
		PLAY( m_samples, SND_RANKING, 0 );

	if ( bitsGoneHigh & OUT_PORT_2_MUSIC_RESET )
		/* reset output is no longer asserted active low */
		m_audiocpu->set_input_line(INPUT_LINE_RESET, PULSE_LINE );
}


READ8_MEMBER( vicdual_state::carnival_music_port_t1_r )
{
	/* note: 8039 T1 signal is inverted on music board */
	return ( m_port2State & OUT_PORT_2_MUSIC_T1 ) ? 0 : 1;
}


WRITE8_MEMBER( vicdual_state::carnival_music_port_1_w )
{
	m_psgData = data;
}


WRITE8_MEMBER( vicdual_state::carnival_music_port_2_w )
{
	static int psgSelect = 0;
	int newSelect;

	newSelect = data & ( MUSIC_PORT2_PSG_BDIR | MUSIC_PORT2_PSG_BC1 );
	if ( psgSelect != newSelect )
	{
		psgSelect = newSelect;

		switch ( psgSelect )
		{
		case PSG_BC_INACTIVE:
			/* do nowt */
			break;

		case PSG_BC_READ:
			/* not very sensible for a write */
			break;

		case PSG_BC_WRITE:
			m_psg->data_w(space, 0, m_psgData);
			break;

		case PSG_BC_LATCH_ADDRESS:
			m_psg->address_w(space, 0, m_psgData);
			break;
		}
	}
}


static ADDRESS_MAP_START( carnival_audio_map, AS_PROGRAM, 8, vicdual_state )
	AM_RANGE(0x0000, 0x07ff) AM_ROM
ADDRESS_MAP_END

static ADDRESS_MAP_START( carnival_audio_io_map, AS_IO, 8, vicdual_state )
	AM_RANGE(MCS48_PORT_T1, MCS48_PORT_T1) AM_READ(carnival_music_port_t1_r)
	AM_RANGE(MCS48_PORT_P1, MCS48_PORT_P1) AM_WRITE(carnival_music_port_1_w)
	AM_RANGE(MCS48_PORT_P2, MCS48_PORT_P2) AM_WRITE(carnival_music_port_2_w)
ADDRESS_MAP_END


MACHINE_CONFIG_FRAGMENT( carnival_audio )
	MCFG_CPU_ADD("audiocpu", I8039, 3579545)
	MCFG_CPU_PROGRAM_MAP(carnival_audio_map)
	MCFG_CPU_IO_MAP(carnival_audio_io_map)

	MCFG_QUANTUM_TIME(attotime::from_hz(600))

	MCFG_SOUND_ADD("psg", AY8910, PSG_CLOCK)
	MCFG_SOUND_ROUTE(ALL_OUTPUTS, "mono", 0.10)

	MCFG_SOUND_ADD("samples", SAMPLES, 0)
	MCFG_SAMPLES_CHANNELS(10)
	MCFG_SAMPLES_NAMES(carnival_sample_names)
	MCFG_SOUND_ROUTE(ALL_OUTPUTS, "mono", 0.25)
=======
	{
		PLAY( m_samples, SND_BEAR, 0 );
	}

	if ( bitsGoneLow & OUT_PORT_2_RANKING )
	{
		PLAY( m_samples, SND_RANKING, 0 );
	}

	// d4: music board MCU reset
	m_audiocpu->set_input_line(INPUT_LINE_RESET, (data & 0x10) ? CLEAR_LINE : ASSERT_LINE);
}


/* Music board */

void vicdual_state::carnival_psg_latch(address_space &space)
{
	if (m_psgBus & 1)
	{
		// BDIR W, BC1 selects address or data
		if (m_psgBus & 2)
			m_psg->address_w(space, 0, m_psgData);
		else
			m_psg->data_w(space, 0, m_psgData);
	}
}

WRITE8_MEMBER( vicdual_state::carnival_music_port_1_w )
{
	// P1: ay8912 d0-d7
	m_psgData = data;
	carnival_psg_latch(space);
}

WRITE8_MEMBER( vicdual_state::carnival_music_port_2_w )
{
	// P2 d6: AY8912 BDIR(R/W)
	// P2 d7: AY8912 BC1
	m_psgBus = data >> 6 & 3;
	carnival_psg_latch(space);
}


READ_LINE_MEMBER( vicdual_state::carnival_music_port_t1_r )
{
	// T1: comms from audio port 2 d3
	return ~m_port2State >> 3 & 1;
}


static ADDRESS_MAP_START( mboard_map, AS_PROGRAM, 8, vicdual_state )
	AM_RANGE(0x0000, 0x03ff) AM_ROM
ADDRESS_MAP_END


MACHINE_CONFIG_START( carnival_audio )

	/* music board */
	MCFG_CPU_ADD("audiocpu", I8039, XTAL_3_579545MHz)
	MCFG_CPU_PROGRAM_MAP(mboard_map)
	MCFG_MCS48_PORT_P1_OUT_CB(WRITE8(vicdual_state, carnival_music_port_1_w))
	MCFG_MCS48_PORT_P2_OUT_CB(WRITE8(vicdual_state, carnival_music_port_2_w))
	MCFG_MCS48_PORT_T1_IN_CB(READLINE(vicdual_state, carnival_music_port_t1_r))

	MCFG_SOUND_ADD("psg", AY8912, XTAL_3_579545MHz/3)
	MCFG_SOUND_ROUTE(ALL_OUTPUTS, "mono", 0.25)

	/* samples */
	MCFG_SOUND_ADD("samples", SAMPLES, 0)
	MCFG_SAMPLES_CHANNELS(10)
	MCFG_SAMPLES_NAMES(carnival_sample_names)
	MCFG_SOUND_ROUTE(ALL_OUTPUTS, "mono", 0.5)
>>>>>>> upstream/master
MACHINE_CONFIG_END
