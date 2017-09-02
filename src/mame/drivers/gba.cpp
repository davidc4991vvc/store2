// license:BSD-3-Clause
// copyright-holders:R. Belmont,Ryan Holtz
/***************************************************************************

<<<<<<< HEAD
  gba.c
=======
  gba.cpp
>>>>>>> upstream/master

  Driver file to handle emulation of the Nintendo Game Boy Advance.

  By R. Belmont & Ryan Holtz

***************************************************************************/

#include "emu.h"
<<<<<<< HEAD
#include "cpu/arm7/arm7.h"
#include "cpu/arm7/arm7core.h"
#include "sound/dac.h"
#include "audio/gb.h"
#include "includes/gba.h"
#include "bus/gba/rom.h"
#include "rendlay.h"
#include "softlist.h"

#define VERBOSE_LEVEL   (0)

INLINE void ATTR_PRINTF(3,4) verboselog(device_t &device, int n_level, const char *s_fmt, ...)
=======
#include "includes/gba.h"

#include "bus/gba/rom.h"
#include "cpu/arm7/arm7.h"
#include "cpu/arm7/arm7core.h"
#include "sound/gb.h"
#include "sound/volt_reg.h"
#include "softlist.h"
#include "speaker.h"


/* Sound Registers */
#define SOUNDCNT_L  HWLO(0x080)  /* 0x4000080  2  R/W   Control Stereo/Volume/Enable */
#define SOUNDCNT_H  HWHI(0x080)  /* 0x4000082  2  R/W   Control Mixing/DMA Control */
#define SOUNDCNT_X  HWLO(0x084)  /* 0x4000084  2  R/W   Control Sound on/off */
								 /* 0x4000086  2  -     Unused */
#define SOUNDBIAS   HWLO(0x088)  /* 0x4000088  2  BIOS  Sound PWM Control */
								 /* 0x400008A  2  -     Unused */

/* DMA Registers (4 Transfer Channels) */
#define DMASAD(c)   WORD(0x0B0 + c * 0xC) /* 0x40000B0  4  W     DMA 0 Source Address */
#define DMADAD(c)   WORD(0x0B4 + c * 0xC) /* 0x40000B4  4  W     DMA 0 Destination Address */
#define DMACNT_L(c) HWLO(0x0B8 + c * 0xC) /* 0x40000B8  2  W     DMA 0 Word Count */
#define DMACNT_H(c) HWHI(0x0B8 + c * 0xC) /* 0x40000BA  2  R/W   DMA 0 Control */

/* Serial Communication (1) Registers */
#define SIODATA32   WORD(0x120)  /* 0x4000120  4  R/W   SIO Data (Normal-32bit Mode; shared with below) */
#define SIOMULTI0   HWLO(0x120)  /* 0x4000120  2  R/W   SIO Data 0 (Parent)    (Multi-Player Mode) */
#define SIOMULTI1   HWHI(0x120)  /* 0x4000122  2  R/W   SIO Data 1 (1st Child) (Multi-Player Mode) */
#define SIOMULTI2   HWLO(0x124)  /* 0x4000124  2  R/W   SIO Data 2 (2nd Child) (Multi-Player Mode) */
#define SIOMULTI3   HWHI(0x124)  /* 0x4000126  2  R/W   SIO Data 3 (3rd Child) (Multi-Player Mode) */
#define SIOCNT      HWLO(0x128)  /* 0x4000128  2  R/W   SIO Control Register */
#define SIOMLT_SEND HWHI(0x128)  /* 0x400012A  2  R/W   SIO Data (Local of MultiPlayer; shared below) */
#define SIODATA8    HWHI(0x128)  /* 0x400012A  2  R/W   SIO Data (Normal-8bit and UART Mode) */
								 /* 0x400012C  2  -     Unused */

/* Keypad Input Registers */
#define KEYINPUT    HWLO(0x130)  /* 0x4000130  2  R     Key Status */
#define KEYCNT      HWHI(0x130)  /* 0x4000132  2  R/W   Key Interrupt Control */

/* Serial Communication (2) Registers */
#define RCNT        HWLO(0x134)  /* 0x4000134  2  R/W   SIO Mode Select/General Purpose Data */
#define IR          HWHI(0x134)  /* 0x4000136  2  R/W   Ancient - Infrared Register (Prototypes only) */
								 /* 0x4000138  8  -     Unused */
#define JOYCNT      HWLO(0x140)  /* 0x4000140  2  R/W   SIO JOY Bus Control */
								 /* 0x4000142  2  -     Unused */
#define JOY_RECV    WORD(0x150)  /* 0x4000150  4  R/W   SIO JOY Bus Receive Data */
#define JOY_TRANS   WORD(0x154)  /* 0x4000154  4  R/W   SIO JOY Bus Transmit Data */
#define JOYSTAT     HWLO(0x158)  /* 0x4000158  2  R/?   SIO JOY Bus Receive Status */
								 /* 0x400015A  2  -     Unused */

/* Interrupt, Waitstate, and Power-Down Control Registers */
#define IE          HWLO(0x200)  /* 0x4000200  2  R/W   Interrupt Enable Register */
#define IF          HWHI(0x200)  /* 0x4000202  2  R/W   Interrupt Request Flags / IRQ Acknowledge */
#define WAITCNT     HWLO(0x204)  /* 0x4000204  2  R/W   Game Pak Waitstate Control */
								 /* 0x4000206     -     Unused */
#define IME         HWLO(0x208)  /* 0x4000208  2  R/W   Interrupt Master Enable Register */
								 /* 0x400020A     -     Unused */
								 /* 0x4000300  1  R/W   Undocumented - Post Boot Flag */
								 /* 0x4000301  1  W     Undocumented - Power Down Control */
								 /* 0x4000302     -     Unused */
								 /* 0x4000410  ?  ?     Undocumented - Purpose Unknown / Bug ??? 0FFh */
								 /* 0x4000411     -     Unused */
								 /* 0x4000800  4  R/W   Undocumented - Internal Memory Control (R/W) */
								 /* 0x4000804     -     Unused */
								 /* 0x4xx0800  4  R/W   Mirrors of 4000800h (repeated each 64K) */

#define SOUNDBIAS_SET(val)      HWLO_SET(0x088, val)

#define DMASAD_SET(c, val)      WORD_SET(0x0B0 + (c * 0xC), val)
#define DMADAD_SET(c, val)      WORD_SET(0x0B4 + (c * 0xC), val)
#define DMACNT_L_SET(c, val)    HWLO_SET(0x0B8 + (c * 0xC), val)
#define DMACNT_H_SET(c, val)    HWHI_SET(0x0B8 + (c * 0xC), val)
#define DMACNT_H_RESET(c, val)  HWHI_RESET(0x0B8 + (c * 0xC), val)

#define SIOMULTI0_SET(val)      HWLO_SET(0x120, val)
#define SIOMULTI1_SET(val)      HWHI_SET(0x120, val)
#define SIOMULTI2_SET(val)      HWLO_SET(0x124, val)
#define SIOMULTI3_SET(val)      HWHI_SET(0x124, val)

#define SIOCNT_RESET(val)       HWLO_RESET(0x128, val)

#define KEYCNT_SET(val)         HWHI_SET(0x130, val)

#define RCNT_SET(val)           HWLO_SET(0x134, val)

#define JOYSTAT_SET(val)        HWLO_SET(0x158, val)

#define IF_SET(val)             HWHI_SET(0x200, val)
#define IF_RESET(val)           HWHI_RESET(0x200, val)

#define INT_VBL                 0x0001
#define INT_HBL                 0x0002
#define INT_VCNT                0x0004
#define INT_TM0_OVERFLOW        0x0008
#define INT_TM1_OVERFLOW        0x0010
#define INT_TM2_OVERFLOW        0x0020
#define INT_TM3_OVERFLOW        0x0040
#define INT_SIO                 0x0080
#define INT_DMA0                0x0100
#define INT_DMA1                0x0200
#define INT_DMA2                0x0400
#define INT_DMA3                0x0800
#define INT_KEYPAD              0x1000
#define INT_GAMEPAK             0x2000

#define VERBOSE_LEVEL   (0)

static inline void ATTR_PRINTF(3,4) verboselog(device_t &device, int n_level, const char *s_fmt, ...)
>>>>>>> upstream/master
{
	if( VERBOSE_LEVEL >= n_level )
	{
		va_list v;
		char buf[ 32768 ];
		va_start( v, s_fmt );
		vsprintf( buf, s_fmt, v );
		va_end( v );
<<<<<<< HEAD
		device.logerror( "%08x: %s", device.machine().driver_data<gba_state>()->m_maincpu->pc(), buf );
	}
}

#define GBA_ATTOTIME_NORMALIZE(a)   a.normalize()

static const UINT32 timer_clks[4] = { 16777216, 16777216/64, 16777216/256, 16777216/1024 };


PALETTE_INIT_MEMBER(gba_state, gba)
{
	UINT8 r, g, b;
	for( b = 0; b < 32; b++ )
	{
		for( g = 0; g < 32; g++ )
		{
			for( r = 0; r < 32; r++ )
			{
				palette.set_pen_color( ( b << 10 ) | ( g << 5 ) | r, pal5bit(r), pal5bit(g), pal5bit(b) );
			}
		}
	}
}

void gba_state::request_irq(UINT32 int_type)
{
	// set flag for later recovery
	m_IF |= int_type;

	// is this specific interrupt enabled?
	int_type &= m_IE;
	if (int_type != 0)
	{
		// master enable?
		if (m_IME & 1)
=======
		device.logerror( "%08x: %s", device.machine().describe_context(), buf );
	}
}

static const uint32_t timer_clks[4] = { XTAL_16_777216MHz, XTAL_16_777216MHz / 64, XTAL_16_777216MHz / 256, XTAL_16_777216MHz / 1024 };


void gba_state::request_irq(uint32_t int_type)
{
	// set flag for later recovery
	IF_SET(int_type);

	// is this specific interrupt enabled?
	int_type &= IE;
	if (int_type != 0)
	{
		// master enable?
		if (IME & 1)
>>>>>>> upstream/master
		{
			m_maincpu->set_input_line(ARM7_IRQ_LINE, ASSERT_LINE);
			m_maincpu->set_input_line(ARM7_IRQ_LINE, CLEAR_LINE);
		}
	}
}

TIMER_CALLBACK_MEMBER(gba_state::dma_complete)
{
<<<<<<< HEAD
	int ctrl;
	FPTR ch;
	static const UINT32 ch_int[4] = { INT_DMA0, INT_DMA1, INT_DMA2, INT_DMA3 };

	ch = param;
=======
	static const uint32_t ch_int[4] = { INT_DMA0, INT_DMA1, INT_DMA2, INT_DMA3 };

	uintptr_t ch = param;
>>>>>>> upstream/master

//  printf("dma complete: ch %d\n", ch);

	m_dma_timer[ch]->adjust(attotime::never);

<<<<<<< HEAD
	ctrl = m_dma_regs[(ch*3)+2] >> 16;
=======
	int ctrl = DMACNT_H(ch);
>>>>>>> upstream/master

	// IRQ
	if (ctrl & 0x4000)
	{
		request_irq(ch_int[ch]);
	}

	// if we're supposed to repeat, don't clear "active" and then the next vbl/hbl will retrigger us
	// always clear active for immediate DMAs though
	if (!((ctrl>>9) & 1) || ((ctrl & 0x3000) == 0))
	{
<<<<<<< HEAD
//      printf("clear active for ch %d\n", ch);
		m_dma_regs[(ch*3)+2] &= ~0x80000000;    // clear "active" bit
=======
		DMACNT_H_RESET(ch, 0x8000); // clear "active" bit
>>>>>>> upstream/master
	}
	else
	{
		// if repeat, reload the count
		if ((ctrl>>9) & 1)
		{
<<<<<<< HEAD
			m_dma_cnt[ch] = m_dma_regs[(ch*3)+2]&0xffff;
=======
			m_dma_cnt[ch] = DMACNT_L(ch);
>>>>>>> upstream/master

			// if increment & reload mode, reload the destination
			if (((ctrl>>5)&3) == 3)
			{
<<<<<<< HEAD
				m_dma_dst[ch] = m_dma_regs[(ch*3)+1];
=======
				m_dma_dst[ch] = DMADAD(ch);
>>>>>>> upstream/master
			}
		}
	}
}

<<<<<<< HEAD
void gba_state::dma_exec(FPTR ch)
{
	address_space &space = m_maincpu->space(AS_PROGRAM);
	UINT32 src = m_dma_src[ch];
	UINT32 dst = m_dma_dst[ch];
	int ctrl = m_dma_regs[(ch*3)+2] >> 16;
	int srcadd = m_dma_srcadd[ch];
	int dstadd = m_dma_dstadd[ch];

	int cnt = m_dma_cnt[ch];
	if (!cnt)
	{
		if (ch == 3)
		{
			cnt = 0x10000;
		}
		else
		{
			cnt = 0x4000;
		}
=======
void gba_state::dma_exec(int ch)
{
	address_space &space = m_maincpu->space(AS_PROGRAM);
	uint32_t src = m_dma_src[ch];
	uint32_t dst = m_dma_dst[ch];
	uint16_t ctrl = DMACNT_H(ch);
	int srcadd = (ctrl >> 7) & 3;
	int dstadd = (ctrl >> 5) & 3;

	int cnt = m_dma_cnt[ch];
	if (cnt == 0)
	{
		if (ch == 3)
			cnt = 0x10000;
		else
			cnt = 0x4000;
>>>>>>> upstream/master
	}

	// override special parameters
	if ((ctrl & 0x3000) == 0x3000)      // special xfer mode
	{
		switch (ch)
		{
			case 1:         // Ch 1&2 are for audio DMA
			case 2:
				dstadd = 2; // don't increment destination
				cnt = 4;    // always transfer 4 32-bit words
				ctrl |= 0x400;  // always 32-bit
				break;

			case 3:
				printf("Unsupported DMA 3 special mode\n");
				break;
		}
	}
	else
	{
//      if (dst >= 0x6000000 && dst <= 0x6017fff)
//      printf("DMA exec: ch %d from %08x to %08x, mode %04x, count %04x (%s)\n", (int)ch, src, dst, ctrl, cnt, ((ctrl>>10) & 1) ? "32" : "16");
	}

	for (int i = 0; i < cnt; i++)
	{
		if ((ctrl>>10) & 1)
		{
			src &= 0xfffffffc;
			dst &= 0xfffffffc;

			// 32-bit
			space.write_dword(dst, space.read_dword(src));
			switch (dstadd)
			{
				case 0: // increment
					dst += 4;
					break;
				case 1: // decrement
					dst -= 4;
					break;
				case 2: // don't move
					break;
				case 3: // increment and reload
					dst += 4;
					break;
			}
			switch (srcadd)
			{
				case 0: // increment
					src += 4;
					break;
				case 1: // decrement
					src -= 4;
					break;
				case 2: // don't move
					break;
				case 3: // not used ("Metal Max 2 Kai" expects no increment/decrement)
					break;
			}
		}
		else
		{
			src &= 0xfffffffe;
			dst &= 0xfffffffe;

			// 16-bit
			space.write_word(dst, space.read_word(src));
			switch (dstadd)
			{
				case 0: // increment
					dst += 2;
					break;
				case 1: // decrement
					dst -= 2;
					break;
				case 2: // don't move
					break;
				case 3: // increment and reload
					dst += 2;
					break;
			}
			switch (srcadd)
			{
				case 0: // increment
					src += 2;
					break;
				case 1: // decrement
					src -= 2;
					break;
				case 2: // don't move
					break;
				case 3: // not used (see note in 32-bit version above)
					break;
			}
		}
	}

	m_dma_src[ch] = src;
	m_dma_dst[ch] = dst;

<<<<<<< HEAD
//  printf("settng DMA timer %d for %d cycs (tmr %x)\n", ch, cnt, (UINT32)m_dma_timer[ch]);
//  m_dma_timer[ch]->adjust(ATTOTIME_IN_CYCLES(0, cnt), ch);
	dma_complete(NULL, ch);
=======
//  printf("settng DMA timer %d for %d cycs (tmr %x)\n", ch, cnt, (uint32_t)m_dma_timer[ch]);
//  m_dma_timer[ch]->adjust(ATTOTIME_IN_CYCLES(0, cnt), ch);
	dma_complete(nullptr, ch);
>>>>>>> upstream/master
}

void gba_state::audio_tick(int ref)
{
<<<<<<< HEAD
	if (!(m_SOUNDCNT_X & 0x80))
	{
		return;
	}
=======
	if (!(SOUNDCNT_X & 0x80))
		return;
>>>>>>> upstream/master

	if (!ref)
	{
		if (m_fifo_a_ptr != m_fifo_a_in)
		{
			if (m_fifo_a_ptr == 17)
			{
				m_fifo_a_ptr = 0;
			}

<<<<<<< HEAD
			if (m_SOUNDCNT_H & 0x200)
			{
				m_ladac->write_signed8(m_fifo_a[m_fifo_a_ptr]^0x80);
			}
			if (m_SOUNDCNT_H & 0x100)
			{
				m_radac->write_signed8(m_fifo_a[m_fifo_a_ptr]^0x80);
=======
			if (SOUNDCNT_H & 0x200)
			{
				m_ldaca->write(m_fifo_a[m_fifo_a_ptr]);
			}
			if (SOUNDCNT_H & 0x100)
			{
				m_rdaca->write(m_fifo_a[m_fifo_a_ptr]);
>>>>>>> upstream/master
			}
			m_fifo_a_ptr++;
		}

		// fifo empty?
		if (m_fifo_a_ptr == m_fifo_a_in)
		{
			// is a DMA set up to feed us?
<<<<<<< HEAD
			if ((m_dma_regs[(1*3)+1] == 0x40000a0) && ((m_dma_regs[(1*3)+2] & 0x30000000) == 0x30000000))
=======
			if ((DMADAD(1) == 0x40000a0) && ((DMACNT_H(1) & 0x3000) == 0x3000))
>>>>>>> upstream/master
			{
				// channel 1 it is
				dma_exec(1);
			}
<<<<<<< HEAD
			if ((m_dma_regs[(2*3)+1] == 0x40000a0) && ((m_dma_regs[(2*3)+2] & 0x30000000) == 0x30000000))
=======
			if ((DMADAD(2) == 0x40000a0) && ((DMACNT_H(2) & 0x3000) == 0x3000))
>>>>>>> upstream/master
			{
				// channel 2 it is
				dma_exec(2);
			}
		}
	}
	else
	{
		if (m_fifo_b_ptr != m_fifo_b_in)
		{
			if (m_fifo_b_ptr == 17)
			{
				m_fifo_b_ptr = 0;
			}

<<<<<<< HEAD
			if (m_SOUNDCNT_H & 0x2000)
			{
				m_lbdac->write_signed8(m_fifo_b[m_fifo_b_ptr]^0x80);
			}
			if (m_SOUNDCNT_H & 0x1000)
			{
				m_rbdac->write_signed8(m_fifo_b[m_fifo_b_ptr]^0x80);
=======
			if (SOUNDCNT_H & 0x2000)
			{
				m_ldacb->write(m_fifo_b[m_fifo_b_ptr]);
			}
			if (SOUNDCNT_H & 0x1000)
			{
				m_rdacb->write(m_fifo_b[m_fifo_b_ptr]);
>>>>>>> upstream/master
			}
			m_fifo_b_ptr++;
		}

		if (m_fifo_b_ptr == m_fifo_b_in)
		{
			// is a DMA set up to feed us?
<<<<<<< HEAD
			if ((m_dma_regs[(1*3)+1] == 0x40000a4) && ((m_dma_regs[(1*3)+2] & 0x30000000) == 0x30000000))
=======
			if ((DMADAD(1) == 0x40000a4) && ((DMACNT_H(1) & 0x3000) == 0x3000))
>>>>>>> upstream/master
			{
				// channel 1 it is
				dma_exec(1);
			}
<<<<<<< HEAD
			if ((m_dma_regs[(2*3)+1] == 0x40000a4) && ((m_dma_regs[(2*3)+2] & 0x30000000) == 0x30000000))
=======
			if ((DMADAD(2) == 0x40000a4) && ((DMACNT_H(2) & 0x3000) == 0x3000))
>>>>>>> upstream/master
			{
				// channel 2 it is
				dma_exec(2);
			}
		}
	}
}

TIMER_CALLBACK_MEMBER(gba_state::timer_expire)
{
<<<<<<< HEAD
	static const UINT32 tmr_ints[4] = { INT_TM0_OVERFLOW, INT_TM1_OVERFLOW, INT_TM2_OVERFLOW, INT_TM3_OVERFLOW };
	FPTR tmr = (FPTR) param;

//  printf("Timer %d expired, SOUNDCNT_H %04x\n", tmr, m_SOUNDCNT_H);
=======
	static const uint32_t tmr_ints[4] = { INT_TM0_OVERFLOW, INT_TM1_OVERFLOW, INT_TM2_OVERFLOW, INT_TM3_OVERFLOW };
	uintptr_t tmr = (uintptr_t) param;
>>>>>>> upstream/master

	// "The reload value is copied into the counter only upon following two situations: Automatically upon timer overflows,"
	// "or when the timer start bit becomes changed from 0 to 1."
	if (m_timer_recalc[tmr] != 0)
	{
		double rate, clocksel, final;
		attotime time;
		m_timer_recalc[tmr] = 0;
		m_timer_regs[tmr] = (m_timer_regs[tmr] & 0xFFFF0000) | (m_timer_reload[tmr] & 0x0000FFFF);
		rate = 0x10000 - (m_timer_regs[tmr] & 0xffff);
		clocksel = timer_clks[(m_timer_regs[tmr] >> 16) & 3];
		final = clocksel / rate;
		m_timer_hz[tmr] = final;
		time = attotime::from_hz(final);
<<<<<<< HEAD
		GBA_ATTOTIME_NORMALIZE(time);
=======
>>>>>>> upstream/master
		m_tmr_timer[tmr]->adjust(time, tmr, time);
	}

	// check if timers 0 or 1 are feeding directsound
	if (tmr == 0)
	{
<<<<<<< HEAD
		if ((m_SOUNDCNT_H & 0x400) == 0)
		{
			audio_tick(0);
		}

		if ((m_SOUNDCNT_H & 0x4000) == 0)
		{
			audio_tick(1);
		}
=======
		if (!(SOUNDCNT_H & 0x400))
			audio_tick(0);

		if (!(SOUNDCNT_H & 0x4000))
			audio_tick(1);
>>>>>>> upstream/master
	}

	if (tmr == 1)
	{
<<<<<<< HEAD
		if ((m_SOUNDCNT_H & 0x400) == 0x400)
		{
			audio_tick(0);
		}

		if ((m_SOUNDCNT_H & 0x4000) == 0x4000)
		{
			audio_tick(1);
		}
=======
		if (SOUNDCNT_H & 0x400)
			audio_tick(0);

		if (SOUNDCNT_H & 0x4000)
			audio_tick(1);
>>>>>>> upstream/master
	}

	// Handle count-up timing
	switch (tmr)
	{
	case 0:
		if (m_timer_regs[1] & 0x40000)
		{
			m_timer_regs[1] = (( ( m_timer_regs[1] & 0x0000ffff ) + 1 ) & 0x0000ffff) | (m_timer_regs[1] & 0xffff0000);
			if( ( m_timer_regs[1] & 0x0000ffff ) == 0 )
			{
				m_timer_regs[1] |= m_timer_reload[1];
<<<<<<< HEAD
				if( ( m_timer_regs[1] & 0x400000 ) && ( m_IME != 0 ) )
=======
				if( ( m_timer_regs[1] & 0x400000 ) && ( IME != 0 ) )
>>>>>>> upstream/master
				{
					request_irq(tmr_ints[1]);
				}
				if( ( m_timer_regs[2] & 0x40000 ) )
				{
					m_timer_regs[2] = (( ( m_timer_regs[2] & 0x0000ffff ) + 1 ) & 0x0000ffff) | (m_timer_regs[2] & 0xffff0000);
					if( ( m_timer_regs[2] & 0x0000ffff ) == 0 )
					{
						m_timer_regs[2] |= m_timer_reload[2];
<<<<<<< HEAD
						if( ( m_timer_regs[2] & 0x400000 ) && ( m_IME != 0 ) )
=======
						if( ( m_timer_regs[2] & 0x400000 ) && ( IME != 0 ) )
>>>>>>> upstream/master
						{
							request_irq(tmr_ints[2]);
						}
						if( ( m_timer_regs[3] & 0x40000 ) )
						{
							m_timer_regs[3] = (( ( m_timer_regs[3] & 0x0000ffff ) + 1 ) & 0x0000ffff) | (m_timer_regs[3] & 0xffff0000);
							if( ( m_timer_regs[3] & 0x0000ffff ) == 0 )
							{
								m_timer_regs[3] |= m_timer_reload[3];
<<<<<<< HEAD
								if( ( m_timer_regs[3] & 0x400000 ) && ( m_IME != 0 ) )
=======
								if( ( m_timer_regs[3] & 0x400000 ) && ( IME != 0 ) )
>>>>>>> upstream/master
								{
									request_irq(tmr_ints[3]);
								}
							}
						}
					}
				}
			}
		}
		break;
	case 1:
		if (m_timer_regs[2] & 0x40000)
		{
			m_timer_regs[2] = (( ( m_timer_regs[2] & 0x0000ffff ) + 1 ) & 0x0000ffff) | (m_timer_regs[2] & 0xffff0000);
			if( ( m_timer_regs[2] & 0x0000ffff ) == 0 )
			{
				m_timer_regs[2] |= m_timer_reload[2];
<<<<<<< HEAD
				if( ( m_timer_regs[2] & 0x400000 ) && ( m_IME != 0 ) )
=======
				if( ( m_timer_regs[2] & 0x400000 ) && ( IME != 0 ) )
>>>>>>> upstream/master
				{
					request_irq(tmr_ints[2]);
				}
				if( ( m_timer_regs[3] & 0x40000 ) )
				{
					m_timer_regs[3] = (( ( m_timer_regs[3] & 0x0000ffff ) + 1 ) & 0x0000ffff) | (m_timer_regs[3] & 0xffff0000);
					if( ( m_timer_regs[3] & 0x0000ffff ) == 0 )
					{
						m_timer_regs[3] |= m_timer_reload[3];
<<<<<<< HEAD
						if( ( m_timer_regs[3] & 0x400000 ) && ( m_IME != 0 ) )
=======
						if( ( m_timer_regs[3] & 0x400000 ) && ( IME != 0 ) )
>>>>>>> upstream/master
						{
							request_irq(tmr_ints[3]);
						}
					}
				}
			}
		}
		break;
	case 2:
		if (m_timer_regs[3] & 0x40000)
		{
			m_timer_regs[3] = (( ( m_timer_regs[3] & 0x0000ffff ) + 1 ) & 0x0000ffff) | (m_timer_regs[3] & 0xffff0000);
			if( ( m_timer_regs[3] & 0x0000ffff ) == 0 )
			{
				m_timer_regs[3] |= m_timer_reload[3];
<<<<<<< HEAD
				if( ( m_timer_regs[3] & 0x400000 ) && ( m_IME != 0 ) )
=======
				if( ( m_timer_regs[3] & 0x400000 ) && ( IME != 0 ) )
>>>>>>> upstream/master
				{
					request_irq(tmr_ints[3]);
				}
			}
		}
		break;
	}

	// are we supposed to IRQ?
<<<<<<< HEAD
	if ((m_timer_regs[tmr] & 0x400000) && (m_IME != 0))
=======
	if ((m_timer_regs[tmr] & 0x400000) && (IME != 0))
>>>>>>> upstream/master
	{
		request_irq(tmr_ints[tmr]);
	}
}

TIMER_CALLBACK_MEMBER(gba_state::handle_irq)
{
<<<<<<< HEAD
	request_irq(m_IF);
=======
	request_irq(IF);
>>>>>>> upstream/master

	m_irq_timer->adjust(attotime::never);
}

<<<<<<< HEAD
READ32_MEMBER(gba_state::gba_io_r)
{
	UINT32 retval = 0;

	switch( offset )
	{
		case 0x0000/4:
			if( (mem_mask) & 0x0000ffff )
			{
				verboselog(*this, 2, "GBA IO Register Read: DISPCNT (%08x) = %04x\n", 0x04000000 + ( offset << 2 ), m_DISPCNT );
				retval |= m_DISPCNT;
			}
			if( (mem_mask) & 0xffff0000 )
			{
				verboselog(*this, 2, "GBA IO Register Read: Green Swap (%08x) = %04x\n", 0x04000000 + ( offset << 2 ) + 2, m_GRNSWAP );
				retval |= m_GRNSWAP << 16;
			}
			break;
		case 0x0004/4:
			retval = (m_DISPSTAT & 0xffff) | (machine().first_screen()->vpos()<<16);
			break;
		case 0x0008/4:
			if( (mem_mask) & 0x0000ffff )
			{
				verboselog(*this, 2, "GBA IO Register Read: BG0CNT (%08x) = %04x\n", 0x04000000 + ( offset << 2 ), m_BG0CNT );
				retval |= m_BG0CNT;
			}
			if( (mem_mask) & 0xffff0000 )
			{
				verboselog(*this, 2, "GBA IO Register Read: BG1CNT (%08x) = %04x\n", 0x04000000 + ( offset << 2 ) + 2, m_BG1CNT );
				retval |= m_BG1CNT << 16;
			}
			break;
		case 0x000c/4:
			if( (mem_mask) & 0x0000ffff )
			{
				verboselog(*this, 2, "GBA IO Register Read: BG2CNT (%08x) = %04x\n", 0x04000000 + ( offset << 2 ), m_BG2CNT );
				retval |= m_BG2CNT;
			}
			if( (mem_mask) & 0xffff0000 )
			{
				verboselog(*this, 2, "GBA IO Register Read: BG3CNT (%08x) = %04x\n", 0x04000000 + ( offset << 2 ) + 2, m_BG3CNT );
				retval |= m_BG3CNT << 16;
			}
			break;
		case 0x0010/4:
			if( (mem_mask) & 0x0000ffff )
			{
				verboselog(*this, 2, "GBA IO Register Read: BG0HOFS (%08x) = %04x\n", 0x04000000 + ( offset << 2 ), 0 );
			}
			if( (mem_mask) & 0xffff0000 )
			{
				verboselog(*this, 2, "GBA IO Register Read: BG0VOFS (%08x) = %04x\n", 0x04000000 + ( offset << 2 ) + 2, 0 );
			}
			break;
		case 0x0014/4:
			if( (mem_mask) & 0x0000ffff )
			{
				verboselog(*this, 2, "GBA IO Register Read: BG1HOFS (%08x) = %04x\n", 0x04000000 + ( offset << 2 ), 0 );
			}
			if( (mem_mask) & 0xffff0000 )
			{
				verboselog(*this, 2, "GBA IO Register Read: BG1VOFS (%08x) = %04x\n", 0x04000000 + ( offset << 2 ) + 2, 0 );
			}
			break;
		case 0x0018/4:
			if( (mem_mask) & 0x0000ffff )
			{
				verboselog(*this, 2, "GBA IO Register Read: BG2HOFS (%08x) = %04x\n", 0x04000000 + ( offset << 2 ), 0 );
			}
			if( (mem_mask) & 0xffff0000 )
			{
				verboselog(*this, 2, "GBA IO Register Read: BG2VOFS (%08x) = %04x\n", 0x04000000 + ( offset << 2 ) + 2, 0 );
			}
			break;
		case 0x001c/4:
			if( (mem_mask) & 0x0000ffff )
			{
				verboselog(*this, 2, "GBA IO Register Read: BG3HOFS (%08x) = %04x\n", 0x04000000 + ( offset << 2 ), 0 );
			}
			if( (mem_mask) & 0xffff0000 )
			{
				verboselog(*this, 2, "GBA IO Register Read: BG3VOFS (%08x) = %04x\n", 0x04000000 + ( offset << 2 ) + 2, 0 );
			}
			break;
		case 0x0020/4:
			if( (mem_mask) & 0x0000ffff )
			{
				verboselog(*this, 2, "GBA IO Register Read: BG2PA (%08x) = %04x\n", 0x04000000 + ( offset << 2 ), 0 );
			}
			if( (mem_mask) & 0xffff0000 )
			{
				verboselog(*this, 2, "GBA IO Register Read: BG2PB (%08x) = %04x\n", 0x04000000 + ( offset << 2 ) + 2, 0 );
			}
			break;
		case 0x0024/4:
			if( (mem_mask) & 0x0000ffff )
			{
				verboselog(*this, 2, "GBA IO Register Read: BG2PC (%08x) = %04x\n", 0x04000000 + ( offset << 2 ), 0 );
			}
			if( (mem_mask) & 0xffff0000 )
			{
				verboselog(*this, 2, "GBA IO Register Read: BG2PD (%08x) = %04x\n", 0x04000000 + ( offset << 2 ) + 2, 0 );
			}
			break;
		case 0x0028/4:
			if( (mem_mask) & 0x0000ffff )
			{
				verboselog(*this, 2, "GBA IO Register Read: BG2X_LSW (%08x) = %04x\n", 0x04000000 + ( offset << 2 ), 0 );
			}
			if( (mem_mask) & 0xffff0000 )
			{
				verboselog(*this, 2, "GBA IO Register Read: BG2X_MSW (%08x) = %04x\n", 0x04000000 + ( offset << 2 ) + 2, 0 );
			}
			break;
		case 0x002c/4:
			if( (mem_mask) & 0x0000ffff )
			{
				verboselog(*this, 2, "GBA IO Register Read: BG2Y_LSW (%08x) = %04x\n", 0x04000000 + ( offset << 2 ), 0 );
			}
			if( (mem_mask) & 0xffff0000 )
			{
				verboselog(*this, 2, "GBA IO Register Read: BG2Y_MSW (%08x) = %04x\n", 0x04000000 + ( offset << 2 ) + 2, 0 );
			}
			break;
		case 0x0030/4:
			if( (mem_mask) & 0x0000ffff )
			{
				verboselog(*this, 2, "GBA IO Register Read: BG3PA (%08x) = %04x\n", 0x04000000 + ( offset << 2 ), 0 );
			}
			if( (mem_mask) & 0xffff0000 )
			{
				verboselog(*this, 2, "GBA IO Register Read: BG3PB (%08x) = %04x\n", 0x04000000 + ( offset << 2 ) + 2, 0 );
			}
			break;
		case 0x0034/4:
			if( (mem_mask) & 0x0000ffff )
			{
				verboselog(*this, 2, "GBA IO Register Read: BG3PC (%08x) = %04x\n", 0x04000000 + ( offset << 2 ), 0 );
			}
			if( (mem_mask) & 0xffff0000 )
			{
				verboselog(*this, 2, "GBA IO Register Read: BG3PD (%08x) = %04x\n", 0x04000000 + ( offset << 2 ) + 2, 0 );
			}
			break;
		case 0x0038/4:
			if( (mem_mask) & 0x0000ffff )
			{
				verboselog(*this, 2, "GBA IO Register Read: BG3X_LSW (%08x) = %04x\n", 0x04000000 + ( offset << 2 ), 0 );
			}
			if( (mem_mask) & 0xffff0000 )
			{
				verboselog(*this, 2, "GBA IO Register Read: BG3X_MSW (%08x) = %04x\n", 0x04000000 + ( offset << 2 ) + 2, 0 );
			}
			break;
		case 0x003c/4:
			if( (mem_mask) & 0x0000ffff )
			{
				verboselog(*this, 2, "GBA IO Register Read: BG3Y_LSW (%08x) = %04x\n", 0x04000000 + ( offset << 2 ), 0 );
			}
			if( (mem_mask) & 0xffff0000 )
			{
				verboselog(*this, 2, "GBA IO Register Read: BG3Y_MSW (%08x) = %04x\n", 0x04000000 + ( offset << 2 ) + 2, 0 );
			}
			break;
		case 0x0040/4:
			if( (mem_mask) & 0x0000ffff )
			{
				verboselog(*this, 2, "GBA IO Register Read: WIN0H (%08x) = %04x\n", 0x04000000 + ( offset << 2 ), 0 );
			}
			if( (mem_mask) & 0xffff0000 )
			{
				verboselog(*this, 2, "GBA IO Register Read: WIN1H (%08x) = %04x\n", 0x04000000 + ( offset << 2 ) + 2, 0 );
			}
			break;
		case 0x0044/4:
			if( (mem_mask) & 0x0000ffff )
			{
				verboselog(*this, 2, "GBA IO Register Read: WIN0V (%08x) = %04x\n", 0x04000000 + ( offset << 2 ), 0 );
			}
			if( (mem_mask) & 0xffff0000 )
			{
				verboselog(*this, 2, "GBA IO Register Read: WIN1V (%08x) = %04x\n", 0x04000000 + ( offset << 2 ) + 2, 0 );
			}
			break;
		case 0x0048/4:
			if( (mem_mask) & 0x0000ffff )
			{
				verboselog(*this, 2, "GBA IO Register Read: WININ (%08x) = %04x\n", 0x04000000 + ( offset << 2 ), m_WININ );
				retval |= m_WININ;
			}
			if( (mem_mask) & 0xffff0000 )
			{
				verboselog(*this, 2, "GBA IO Register Read: WINOUT (%08x) = %04x\n", 0x04000000 + ( offset << 2 ) + 2, m_WINOUT );
				retval |= m_WINOUT << 16;
			}
			break;
		case 0x004c/4:
			if( (mem_mask) & 0x0000ffff )
			{
				verboselog(*this, 2, "GBA IO Register Read: MOSAIC (%08x) = %04x\n", 0x04000000 + ( offset << 2 ), 0 );
			}
			if( (mem_mask) & 0xffff0000 )
			{
				verboselog(*this, 2, "GBA IO Register Read: UNKNOWN (%08x) = %04x\n", 0x04000000 + ( offset << 2 ) + 2, 0 );
			}
			break;
		case 0x0050/4:
			if( (mem_mask) & 0x0000ffff )
			{
				verboselog(*this, 2, "GBA IO Register Read: BLDCNT (%08x) = %04x\n", 0x04000000 + ( offset << 2 ), m_BLDCNT );
				retval |= m_BLDCNT;
			}
			if( (mem_mask) & 0xffff0000 )
			{
				verboselog(*this, 2, "GBA IO Register Read: BLDALPHA (%08x) = %04x\n", 0x04000000 + ( offset << 2 ) + 2, m_BLDALPHA );
				retval |= m_BLDALPHA << 16;
			}
			break;
		case 0x0054/4:
			if( (mem_mask) & 0x0000ffff )
			{
				verboselog(*this, 2, "GBA IO Register Read: BLDY (%08x) = %04x\n", 0x04000000 + ( offset << 2 ), 0 );
			}
			if( (mem_mask) & 0xffff0000 )
			{
				verboselog(*this, 2, "GBA IO Register Read: UNKNOWN (%08x) = %04x\n", 0x04000000 + ( offset << 2 ) + 2, 0 );
			}
			break;
		case 0x0058/4:
			if( (mem_mask) & 0x0000ffff )
			{
				verboselog(*this, 2, "GBA IO Register Read: UNKNOWN (%08x) = %04x\n", 0x04000000 + ( offset << 2 ), 0 );
			}
			if( (mem_mask) & 0xffff0000 )
			{
				verboselog(*this, 2, "GBA IO Register Read: UNKNOWN (%08x) = %04x\n", 0x04000000 + ( offset << 2 ) + 2, 0 );
			}
			break;
		case 0x005c/4:
			if( (mem_mask) & 0x0000ffff )
			{
				verboselog(*this, 2, "GBA IO Register Read: UNKNOWN (%08x) = %04x\n", 0x04000000 + ( offset << 2 ), 0 );
			}
			if( (mem_mask) & 0xffff0000 )
			{
				verboselog(*this, 2, "GBA IO Register Read: UNKNOWN (%08x) = %04x\n", 0x04000000 + ( offset << 2 ) + 2, 0 );
			}
			break;
=======
static const char *reg_names[] = {
	/* Sound Registers */
	"SOUND1CNT_L", "SOUND1CNT_H", "SOUND1CNT_X", "Unused",
	"SOUND2CNT_L", "Unused",      "SOUND2CNT_H", "Unused",
	"SOUND3CNT_L", "SOUND3CNT_H", "SOUND3CNT_X", "Unused",
	"SOUND4CNT_L", "Unused",      "SOUND4CNT_H", "Unused",
	"SOUNDCNT_L",  "SOUNDCNT_H",  "SOUNDCNT_X",  "Unused",
	"SOUNDBIAS",   "Unused",      "WAVE_RAM",    "WAVE_RAM",
	"WAVE_RAM",    "WAVE_RAM",    "WAVE_RAM",    "WAVE_RAM",
	"WAVE_RAM",    "WAVE_RAM",    "WAVE_RAM",    "WAVE_RAM",
	"WAVE_RAM",    "WAVE_RAM",    "WAVE_RAM",    "WAVE_RAM",
	"WAVE_RAM",    "WAVE_RAM",    "FIFO_A_L",    "FIFO_A_H",
	"FIFO_B_L",    "FIFO_B_H"
};

READ32_MEMBER(gba_state::gba_io_r)
{
	uint32_t retval = 0;

	switch( offset + 0x60/4 )
	{
>>>>>>> upstream/master
		case 0x0060/4:
			retval = m_gbsound->sound_r(space, 0) | m_gbsound->sound_r(space, 1)<<16 | m_gbsound->sound_r(space, 2)<<24;
			break;
		case 0x0064/4:
			retval = m_gbsound->sound_r(space, 3) | m_gbsound->sound_r(space, 4)<<8;
			break;
		case 0x0068/4:
			retval = m_gbsound->sound_r(space, 6) | m_gbsound->sound_r(space, 7)<<8;
			break;
		case 0x006c/4:
			retval = m_gbsound->sound_r(space, 8) | m_gbsound->sound_r(space, 9)<<8;
			break;
		case 0x0070/4:
			retval = m_gbsound->sound_r(space, 0xa) | m_gbsound->sound_r(space, 0xb)<<16 | m_gbsound->sound_r(space, 0xc)<<24;
			break;
		case 0x0074/4:
			retval = m_gbsound->sound_r(space, 0xd) | m_gbsound->sound_r(space, 0xe)<<8;
			break;
		case 0x0078/4:
			retval = m_gbsound->sound_r(space, 0x10) | m_gbsound->sound_r(space, 0x11)<<8;
			break;
		case 0x007c/4:
			retval = m_gbsound->sound_r(space, 0x12) | m_gbsound->sound_r(space, 0x13)<<8;
			break;
		case 0x0080/4:
			retval = m_gbsound->sound_r(space, 0x14) | m_gbsound->sound_r(space, 0x15)<<8;
<<<<<<< HEAD
			if( (mem_mask) & 0xffff0000 )
			{
				verboselog(*this, 2, "GBA IO Register Read: SOUNDCNT_H (%08x) = %04x\n", 0x04000000 + ( offset << 2 ) + 2, m_SOUNDCNT_H );
				retval |= m_SOUNDCNT_H << 16;
=======
			if( ACCESSING_BITS_16_31 )
			{
				retval |= SOUNDCNT_H << 16;
>>>>>>> upstream/master
			}
			break;
		case 0x0084/4:
			retval = m_gbsound->sound_r(space, 0x16);
			break;
<<<<<<< HEAD
		case 0x0088/4:
			if( (mem_mask) & 0x0000ffff )
			{
				verboselog(*this, 2, "GBA IO Register Read: SOUNDBIAS (%08x) = %04x\n", 0x04000000 + ( offset << 2 ), m_SOUNDBIAS );
				retval |= m_SOUNDBIAS;
			}
			if( (mem_mask) & 0xffff0000 )
			{
				verboselog(*this, 2, "GBA IO Register Read: UNKNOWN (%08x) = %04x\n", 0x04000000 + ( offset << 2 ) + 2, 0 );
			}
			break;
=======
>>>>>>> upstream/master
		case 0x0090/4:
			retval = m_gbsound->wave_r(space, 0) | m_gbsound->wave_r(space, 1)<<8 | m_gbsound->wave_r(space, 2)<<16 | m_gbsound->wave_r(space, 3)<<24;
			break;
		case 0x0094/4:
			retval = m_gbsound->wave_r(space, 4) | m_gbsound->wave_r(space, 5)<<8 | m_gbsound->wave_r(space, 6)<<16 | m_gbsound->wave_r(space, 7)<<24;
			break;
		case 0x0098/4:
			retval = m_gbsound->wave_r(space, 8) | m_gbsound->wave_r(space, 9)<<8 | m_gbsound->wave_r(space, 10)<<16 | m_gbsound->wave_r(space, 11)<<24;
			break;
		case 0x009c/4:
			retval = m_gbsound->wave_r(space, 12) | m_gbsound->wave_r(space, 13)<<8 | m_gbsound->wave_r(space, 14)<<16 | m_gbsound->wave_r(space, 15)<<24;
			break;
		case 0x00a0/4:
		case 0x00a4/4:
			retval = 0; // (does this actually do anything on real h/w?)
			break;
		case 0x00b0/4:
		case 0x00b4/4:
<<<<<<< HEAD
		case 0x00b8/4:
		case 0x00bc/4:
		case 0x00c0/4:
		case 0x00c4/4:
		case 0x00c8/4:
		case 0x00cc/4:
		case 0x00d0/4:
		case 0x00d4/4:
		case 0x00d8/4:
		case 0x00dc/4:
			{
				// no idea why here, but it matches VBA better
				// note: this suspicious piece of code crashes "Buffy The Vampire Slayer" (08008DB4) and "The Ant Bully", so disable it for now
				#if 0
				if (((offset-0xb0/4) % 3) == 2)
				{
					retval = m_dma_regs[offset-(0xb0/4)] & 0xff000000;
				}
				else
				#endif

				retval = m_dma_regs[offset-(0xb0/4)];
=======
			// read only
			break;
		case 0x00b8/4:
			if (ACCESSING_BITS_0_15)
			{
				// read only
			}
			if (ACCESSING_BITS_16_31)
			{
				retval |= DMACNT_H(0) << 16;
			}
			break;
		case 0x00bc/4:
		case 0x00c0/4:
			// read only
			break;
		case 0x00c4/4:
			if (ACCESSING_BITS_0_15)
			{
				// read only
			}
			if (ACCESSING_BITS_16_31)
			{
				retval |= DMACNT_H(1) << 16;
			}
			break;
		case 0x00c8/4:
		case 0x00cc/4:
			// read only
			break;
		case 0x00d0/4:
			if (ACCESSING_BITS_0_15)
			{
				// read only
			}
			if (ACCESSING_BITS_16_31)
			{
				retval |= DMACNT_H(2) << 16;
			}
			break;
		case 0x00d4/4:
		case 0x00d8/4:
			// read only
			break;
		case 0x00dc/4:
				// no idea why here, but it matches VBA better
				// note: this suspicious piece of code crashes "Buffy The Vampire Slayer" (08008DB4) and "The Ant Bully", so disable it for now
			if (ACCESSING_BITS_0_15)
			{
				// read only
			}
			if (ACCESSING_BITS_16_31)
			{
				retval |= DMACNT_H(3) << 16;
>>>>>>> upstream/master
			}
			break;
		case 0x0100/4:
		case 0x0104/4:
		case 0x0108/4:
		case 0x010c/4:
			{
<<<<<<< HEAD
				UINT32 elapsed;
				double time, ticks;
				int timer = offset-(0x100/4);
=======
				uint32_t elapsed;
				double time, ticks;
				int timer = offset + 0x60/4 - 0x100/4;
>>>>>>> upstream/master

//              printf("Read timer reg %x (PC=%x)\n", timer, space.device().safe_pc());

				// update times for
				if (m_timer_regs[timer] & 0x800000)
				{
					if (m_timer_regs[timer] & 0x00040000)
					{
						elapsed = m_timer_regs[timer] & 0xffff;
					}
					else
					{
<<<<<<< HEAD
					time = m_tmr_timer[timer]->elapsed().as_double();

					ticks = (double)(0x10000 - (m_timer_regs[timer] & 0xffff));

//                  printf("time %f ticks %f 1/hz %f\n", time, ticks, 1.0 / m_timer_hz[timer]);

					time *= ticks;
					time /= (1.0 / m_timer_hz[timer]);

					elapsed = (UINT32)time;

=======
						time = m_tmr_timer[timer]->elapsed().as_double();

						ticks = (double)(0x10000 - (m_timer_regs[timer] & 0xffff));

	//                  printf("time %f ticks %f 1/hz %f\n", time, ticks, 1.0 / m_timer_hz[timer]);

						time *= ticks;
						time /= (1.0 / m_timer_hz[timer]);

						elapsed = (uint32_t)time;
>>>>>>> upstream/master
					}

//                  printf("elapsed = %x\n", elapsed);
				}
				else
				{
//                  printf("Reading inactive timer!\n");
					elapsed = 0;
				}

				retval = (m_timer_regs[timer] & 0xffff0000) | (elapsed & 0xffff);
			}
			break;
<<<<<<< HEAD
		case 0x0120/4:
			if( (mem_mask) & 0x0000ffff )
			{
				verboselog(*this, 2, "GBA IO Register Read: SIOMULTI0 (%08x) = %04x\n", 0x04000000 + ( offset << 2 ), m_SIOMULTI0 );
				retval |= m_SIOMULTI0;
			}
			if( (mem_mask) & 0xffff0000 )
			{
				verboselog(*this, 2, "GBA IO Register Read: SIOMULTI1 (%08x) = %04x\n", 0x04000000 + ( offset << 2 ) + 2, m_SIOMULTI1 );
				retval |= m_SIOMULTI1 << 16;
			}
			break;
		case 0x0124/4:
			if( (mem_mask) & 0x0000ffff )
			{
				verboselog(*this, 2, "GBA IO Register Read: SIOMULTI2 (%08x) = %04x\n", 0x04000000 + ( offset << 2 ), m_SIOMULTI2 );
				retval |= m_SIOMULTI2;
			}
			if( (mem_mask) & 0xffff0000 )
			{
				verboselog(*this, 2, "GBA IO Register Read: SIOMULTI3 (%08x) = %04x\n", 0x04000000 + ( offset << 2 ) + 2, m_SIOMULTI3 );
				retval |= m_SIOMULTI3 << 16;
			}
			break;
		case 0x0128/4:
			if( (mem_mask) & 0x0000ffff )
			{
				verboselog(*this, 2, "GBA IO Register Read: SIOCNT (%08x) = %04x\n", 0x04000000 + ( offset << 2 ), m_SIOCNT );
				retval |= m_SIOCNT;
			}
			if( (mem_mask) & 0xffff0000 )
			{
				verboselog(*this, 2, "GBA IO Register Read: SIODATA8 (%08x) = %04x\n", 0x04000000 + ( offset << 2 ) + 2, m_SIODATA8 );
				retval |= m_SIODATA8 << 16;
			}
			break;
		case 0x0130/4:
			if( (mem_mask) & 0x0000ffff )   // KEYINPUT
			{
				retval = m_io_inputs->read();
			}
			else if( (mem_mask) & 0xffff0000 )
			{
				verboselog(*this, 2, "GBA IO Register Read: KEYCNT (%08x) = %04x\n", 0x04000000 + ( offset << 2 ) + 2, m_KEYCNT );
				retval |= m_KEYCNT << 16;
			}
			break;
		case 0x0134/4:
			if( (mem_mask) & 0x0000ffff )
			{
				verboselog(*this, 2, "GBA IO Register Read: RCNT (%08x) = %04x\n", 0x04000000 + ( offset << 2 ), m_RCNT );
				retval |= m_RCNT;
			}
			if( (mem_mask) & 0xffff0000 )
			{
				verboselog(*this, 2, "GBA IO Register Read: IR (%08x) = %04x\n", 0x04000000 + ( offset << 2 ) + 2, 0 );
			}
			break;
		case 0x0140/4:
			if( (mem_mask) & 0x0000ffff )
			{
				verboselog(*this, 2, "GBA IO Register Read: JOYCNT (%08x) = %04x\n", 0x04000000 + ( offset << 2 ), m_JOYCNT );
				retval |= m_JOYCNT;
			}
			if( (mem_mask) & 0xffff0000 )
			{
				verboselog(*this, 2, "GBA IO Register Read: UNKNOWN (%08x) = %04x\n", 0x04000000 + ( offset << 2 ) + 2, 0 );
			}
			break;
		case 0x0150/4:
			if( (mem_mask) & 0x0000ffff )
			{
				verboselog(*this, 2, "GBA IO Register Read: JOY_RECV_LSW (%08x) = %04x\n", 0x04000000 + ( offset << 2 ), m_JOY_RECV & 0x0000ffff );
				retval |= m_JOY_RECV & 0x0000ffff;
			}
			if( (mem_mask) & 0xffff0000 )
			{
				verboselog(*this, 2, "GBA IO Register Read: JOY_RECV_MSW (%08x) = %04x\n", 0x04000000 + ( offset << 2 ) + 2, ( m_JOY_RECV & 0xffff0000 ) >> 16 );
				retval |= m_JOY_RECV & 0xffff0000;
			}
			break;
		case 0x0154/4:
			if( (mem_mask) & 0x0000ffff )
			{
				verboselog(*this, 2, "GBA IO Register Read: JOY_TRANS_LSW (%08x) = %04x\n", 0x04000000 + ( offset << 2 ), m_JOY_TRANS & 0x0000ffff );
				retval |= m_JOY_TRANS & 0x0000ffff;
			}
			if( (mem_mask) & 0xffff0000 )
			{
				verboselog(*this, 2, "GBA IO Register Read: JOY_TRANS_MSW (%08x) = %04x\n", 0x04000000 + ( offset << 2 ) + 2, ( m_JOY_TRANS & 0xffff0000 ) >> 16 );
				retval |= m_JOY_TRANS & 0xffff0000;
			}
			break;
		case 0x0158/4:
			if( (mem_mask) & 0x0000ffff )
			{
				verboselog(*this, 2, "GBA IO Register Read: JOYSTAT (%08x) = %04x\n", 0x04000000 + ( offset << 2 ), m_JOYSTAT );
				retval |= m_JOYSTAT;
			}
			if( (mem_mask) & 0xffff0000 )
			{
				verboselog(*this, 2, "GBA IO Register Read: UNKNOWN (%08x) = %04x\n", 0x04000000 + ( offset << 2 ) + 2, 0 );
			}
			break;
		case 0x0200/4:
			if( (mem_mask) & 0x0000ffff )
			{
//              printf("Read: IE (%08x) = %04x\n", 0x04000000 + ( offset << 2 ), m_IE );
			}
			if( (mem_mask) & 0xffff0000 )
			{
				verboselog(*this, 2, "GBA IO Register Read: IF (%08x) = %04x\n", 0x04000000 + ( offset << 2 ) + 2, m_IF );
			}

			retval = m_IE | (m_IF<<16);
			break;
		case 0x0204/4:
			if( (mem_mask) & 0x0000ffff )
			{
				verboselog(*this, 2, "GBA IO Register Read: WAITCNT (%08x) = %04x\n", 0x04000000 + ( offset << 2 ), m_WAITCNT );
				retval |= m_WAITCNT;
			}
			if( (mem_mask) & 0xffff0000 )
			{
				verboselog(*this, 2, "GBA IO Register Read: UNKNOWN (%08x) = %04x\n", 0x04000000 + ( offset << 2 ) + 2, 0 );
			}
			break;
		case 0x0208/4:
			if( (mem_mask) & 0x0000ffff )
			{
				verboselog(*this, 2, "GBA IO Register Read: IME (%08x) = %04x\n", 0x04000000 + ( offset << 2 ), m_IME );
				retval |= m_IME;
			}
			if( (mem_mask) & 0xffff0000 )
			{
				verboselog(*this, 2, "GBA IO Register Read: UNKNOWN (%08x) = %04x\n", 0x04000000 + ( offset << 2 ) + 2, 0 );
			}
			break;
		case 0x0300/4:
			retval = m_HALTCNT << 8;
			break;
		default:
//          verboselog(*this, 0, "Unknown GBA I/O register Read: %08x (%08x)\n", 0x04000000 + ( offset << 2 ), ~mem_mask );
			break;
	}
	return retval;
}

WRITE32_MEMBER(gba_state::gba_io_w)
{
	switch( offset )
	{
		case 0x0000/4:
			if( (mem_mask) & 0x0000ffff )
			{
				verboselog(*this, 2, "GBA IO Register Write: DISPCNT (%08x) = %04x (%08x)\n", 0x04000000 + ( offset << 2 ), data & 0x0000ffff, ~mem_mask );
				m_DISPCNT = ( m_DISPCNT & ~mem_mask ) | ( data & mem_mask );
				if(m_DISPCNT & (DISPCNT_WIN0_EN | DISPCNT_WIN1_EN))
				{
					m_windowOn = 1;
				}
				else
				{
					m_windowOn = 0;
				}
			}
			if( (mem_mask) & 0xffff0000 )
			{
				verboselog(*this, 2, "GBA IO Register Write: Green Swap (%08x) = %04x (%08x)\n", 0x04000000 + ( offset << 2 ), ( data & 0xffff0000 ) >> 16, ~mem_mask );
				m_GRNSWAP = ( m_GRNSWAP & ( ~mem_mask >> 16 ) ) | ( ( data & mem_mask ) >> 16 );
			}
			break;
		case 0x0004/4:
			COMBINE_DATA(&m_DISPSTAT);
			break;
		case 0x0008/4:
			if( (mem_mask) & 0x0000ffff )
			{
				verboselog(*this, 2, "GBA IO Register Write: BG0CNT (%08x) = %04x (%08x)\n", 0x04000000 + ( offset << 2 ), data & 0x0000ffff, ~mem_mask );
				m_BG0CNT = ( m_BG0CNT & ~mem_mask ) | ( data & mem_mask );
			}
			if( (mem_mask) & 0xffff0000 )
			{
				verboselog(*this, 2, "GBA IO Register Write: BG1CNT (%08x) = %04x (%08x)\n", 0x04000000 + ( offset << 2 ), ( data & 0xffff0000 ) >> 16, ~mem_mask );
				m_BG1CNT = ( m_BG1CNT & ( ~mem_mask >> 16 ) ) | ( ( data & mem_mask ) >> 16 );
			}
			break;
		case 0x000c/4:
			if( (mem_mask) & 0x0000ffff )
			{
				verboselog(*this, 2, "GBA IO Register Write: BG2CNT (%08x) = %04x (%08x)\n", 0x04000000 + ( offset << 2 ), data & 0x0000ffff, ~mem_mask );
				m_BG2CNT = ( m_BG2CNT & ~mem_mask ) | ( data & mem_mask );
			}
			if( (mem_mask) & 0xffff0000 )
			{
				verboselog(*this, 2, "GBA IO Register Write: BG3CNT (%08x) = %04x (%08x)\n", 0x04000000 + ( offset << 2 ), ( data & 0xffff0000 ) >> 16, ~mem_mask );
				m_BG3CNT = ( m_BG3CNT & ( ~mem_mask >> 16 ) ) | ( ( data & mem_mask ) >> 16 );
			}
			break;
		case 0x0010/4:
			if( (mem_mask) & 0x0000ffff )
			{
				verboselog(*this, 2, "GBA IO Register Write: BG0HOFS (%08x) = %04x (%08x)\n", 0x04000000 + ( offset << 2 ), data & 0x0000ffff, ~mem_mask );
				m_BG0HOFS = ( m_BG0HOFS & ~mem_mask ) | ( data & mem_mask );
			}
			if( (mem_mask) & 0xffff0000 )
			{
				verboselog(*this, 2, "GBA IO Register Write: BG0VOFS (%08x) = %04x (%08x)\n", 0x04000000 + ( offset << 2 ), ( data & 0xffff0000 ) >> 16, ~mem_mask );
				m_BG0VOFS = ( m_BG0VOFS & ( ~mem_mask >> 16 ) ) | ( ( data & mem_mask ) >> 16 );
			}
			break;
		case 0x0014/4:
			if( (mem_mask) & 0x0000ffff )
			{
				verboselog(*this, 2, "GBA IO Register Write: BG1HOFS (%08x) = %04x (%08x)\n", 0x04000000 + ( offset << 2 ), data & 0x0000ffff, ~mem_mask );
				m_BG1HOFS = ( m_BG1HOFS & ~mem_mask ) | ( data & mem_mask );
			}
			if( (mem_mask) & 0xffff0000 )
			{
				verboselog(*this, 2, "GBA IO Register Write: BG1VOFS (%08x) = %04x (%08x)\n", 0x04000000 + ( offset << 2 ), ( data & 0xffff0000 ) >> 16, ~mem_mask );
				m_BG1VOFS = ( m_BG1VOFS & ( ~mem_mask >> 16 ) ) | ( ( data & mem_mask ) >> 16 );
			}
			break;
		case 0x0018/4:
			if( (mem_mask) & 0x0000ffff )
			{
				verboselog(*this, 2, "GBA IO Register Write: BG2HOFS (%08x) = %04x (%08x)\n", 0x04000000 + ( offset << 2 ), data & 0x0000ffff, ~mem_mask );
				m_BG2HOFS = ( m_BG2HOFS & ~mem_mask ) | ( data & mem_mask );
			}
			if( (mem_mask) & 0xffff0000 )
			{
				verboselog(*this, 2, "GBA IO Register Write: BG2VOFS (%08x) = %04x (%08x)\n", 0x04000000 + ( offset << 2 ), ( data & 0xffff0000 ) >> 16, ~mem_mask );
				m_BG2VOFS = ( m_BG2VOFS & ( ~mem_mask >> 16 ) ) | ( ( data & mem_mask ) >> 16 );
			}
			break;
		case 0x001c/4:
			if( (mem_mask) & 0x0000ffff )
			{
				verboselog(*this, 2, "GBA IO Register Write: BG3HOFS (%08x) = %04x (%08x)\n", 0x04000000 + ( offset << 2 ), data & 0x0000ffff, ~mem_mask );
				m_BG3HOFS = ( m_BG3HOFS & ~mem_mask ) | ( data & mem_mask );
			}
			if( (mem_mask) & 0xffff0000 )
			{
				verboselog(*this, 2, "GBA IO Register Write: BG3VOFS (%08x) = %04x (%08x)\n", 0x04000000 + ( offset << 2 ), ( data & 0xffff0000 ) >> 16, ~mem_mask );
				m_BG3VOFS = ( m_BG3VOFS & ( ~mem_mask >> 16 ) ) | ( ( data & mem_mask ) >> 16 );
			}
			break;
		case 0x0020/4:
			if( (mem_mask) & 0x0000ffff )
			{
				verboselog(*this, 2, "GBA IO Register Write: BG2PA (%08x) = %04x (%08x)\n", 0x04000000 + ( offset << 2 ), data & 0x0000ffff, ~mem_mask );
				m_BG2PA = ( m_BG2PA & ~mem_mask ) | ( data & mem_mask );
			}
			if( (mem_mask) & 0xffff0000 )
			{
				verboselog(*this, 2, "GBA IO Register Write: BG2PB (%08x) = %04x (%08x)\n", 0x04000000 + ( offset << 2 ), ( data & 0xffff0000 ) >> 16, ~mem_mask );
				m_BG2PB = ( m_BG2PB & ( ~mem_mask >> 16 ) ) | ( ( data & mem_mask ) >> 16 );
			}
			break;
		case 0x0024/4:
			if( (mem_mask) & 0x0000ffff )
			{
				verboselog(*this, 2, "GBA IO Register Write: BG2PC (%08x) = %04x (%08x)\n", 0x04000000 + ( offset << 2 ), data & 0x0000ffff, ~mem_mask );
				m_BG2PC = ( m_BG2PC & ~mem_mask ) | ( data & mem_mask );
			}
			if( (mem_mask) & 0xffff0000 )
			{
				verboselog(*this, 2, "GBA IO Register Write: BG2PD (%08x) = %04x (%08x)\n", 0x04000000 + ( offset << 2 ), ( data & 0xffff0000 ) >> 16, ~mem_mask );
				m_BG2PD = ( m_BG2PD & ( ~mem_mask >> 16 ) ) | ( ( data & mem_mask ) >> 16 );
			}
			break;
		case 0x0028/4:
			if( (mem_mask) & 0x0000ffff )
			{
				verboselog(*this, 2, "GBA IO Register Write: BG2X_LSW (%08x) = %04x (%08x)\n", 0x04000000 + ( offset << 2 ), data & 0x0000ffff, ~mem_mask );
			}
			if( (mem_mask) & 0xffff0000 )
			{
				verboselog(*this, 2, "GBA IO Register Write: BG2X_MSW (%08x) = %04x (%08x)\n", 0x04000000 + ( offset << 2 ), ( data & 0xffff0000 ) >> 16, ~mem_mask );
			}
			COMBINE_DATA(&m_BG2X);
			m_gfxBG2Changed |= 1;
			break;
		case 0x002c/4:
			if( (mem_mask) & 0x0000ffff )
			{
				verboselog(*this, 2, "GBA IO Register Write: BG2Y_LSW (%08x) = %04x (%08x)\n", 0x04000000 + ( offset << 2 ), data & 0x0000ffff, ~mem_mask );
			}
			if( (mem_mask) & 0xffff0000 )
			{
				verboselog(*this, 2, "GBA IO Register Write: BG2Y_MSW (%08x) = %04x (%08x)\n", 0x04000000 + ( offset << 2 ), ( data & 0xffff0000 ) >> 16, ~mem_mask );
			}
			COMBINE_DATA(&m_BG2Y);
			m_gfxBG2Changed |= 2;
			break;
		case 0x0030/4:
			if( (mem_mask) & 0x0000ffff )
			{
				verboselog(*this, 2, "GBA IO Register Write: BG3PA (%08x) = %04x (%08x)\n", 0x04000000 + ( offset << 2 ), data & 0x0000ffff, ~mem_mask );
				m_BG3PA = ( m_BG3PA & ~mem_mask ) | ( data & mem_mask );
			}
			if( (mem_mask) & 0xffff0000 )
			{
				verboselog(*this, 2, "GBA IO Register Write: BG3PB (%08x) = %04x (%08x)\n", 0x04000000 + ( offset << 2 ), ( data & 0xffff0000 ) >> 16, ~mem_mask );
				m_BG3PB = ( m_BG3PB & ( ~mem_mask >> 16 ) ) | ( ( data & mem_mask ) >> 16 );
			}
			break;
		case 0x0034/4:
			if( (mem_mask) & 0x0000ffff )
			{
				verboselog(*this, 2, "GBA IO Register Write: BG3PC (%08x) = %04x (%08x)\n", 0x04000000 + ( offset << 2 ), data & 0x0000ffff, ~mem_mask );
				m_BG3PC = ( m_BG3PC & ~mem_mask ) | ( data & mem_mask );
			}
			if( (mem_mask) & 0xffff0000 )
			{
				verboselog(*this, 2, "GBA IO Register Write: BG3PD (%08x) = %04x (%08x)\n", 0x04000000 + ( offset << 2 ), ( data & 0xffff0000 ) >> 16, ~mem_mask );
				m_BG3PD = ( m_BG3PD & ( ~mem_mask >> 16 ) ) | ( ( data & mem_mask ) >> 16 );
			}
			break;
		case 0x0038/4:
			if( (mem_mask) & 0x0000ffff )
			{
				verboselog(*this, 2, "GBA IO Register Write: BG3X_LSW (%08x) = %04x (%08x)\n", 0x04000000 + ( offset << 2 ), data & 0x0000ffff, ~mem_mask );
			}
			if( (mem_mask) & 0xffff0000 )
			{
				verboselog(*this, 2, "GBA IO Register Write: BG3X_MSW (%08x) = %04x (%08x)\n", 0x04000000 + ( offset << 2 ), ( data & 0xffff0000 ) >> 16, ~mem_mask );
			}
			COMBINE_DATA(&m_BG3X);
			m_gfxBG3Changed |= 1;
			break;
		case 0x003c/4:
			if( (mem_mask) & 0x0000ffff )
			{
				verboselog(*this, 2, "GBA IO Register Write: BG3Y_LSW (%08x) = %04x (%08x)\n", 0x04000000 + ( offset << 2 ), data & 0x0000ffff, ~mem_mask );
			}
			if( (mem_mask) & 0xffff0000 )
			{
				verboselog(*this, 2, "GBA IO Register Write: BG3Y_MSW (%08x) = %04x (%08x)\n", 0x04000000 + ( offset << 2 ), ( data & 0xffff0000 ) >> 16, ~mem_mask );
			}
			COMBINE_DATA(&m_BG3Y);
			m_gfxBG3Changed |= 2;
			break;
		case 0x0040/4:
			if( (mem_mask) & 0x0000ffff )
			{
				verboselog(*this, 2, "GBA IO Register Write: WIN0H (%08x) = %04x (%08x)\n", 0x04000000 + ( offset << 2 ), data & 0x0000ffff, ~mem_mask );
				m_WIN0H = ( m_WIN0H & ~mem_mask ) | ( data & mem_mask );
			}
			if( (mem_mask) & 0xffff0000 )
			{
				verboselog(*this, 2, "GBA IO Register Write: WIN1H (%08x) = %04x (%08x)\n", 0x04000000 + ( offset << 2 ), ( data & 0xffff0000 ) >> 16, ~mem_mask );
				m_WIN1H = ( m_WIN1H & ( ~mem_mask >> 16 ) ) | ( ( data & mem_mask ) >> 16 );
			}
			break;
		case 0x0044/4:
			if( (mem_mask) & 0x0000ffff )
			{
				verboselog(*this, 2, "GBA IO Register Write: WIN0V (%08x) = %04x (%08x)\n", 0x04000000 + ( offset << 2 ), data & 0x0000ffff, ~mem_mask );
				m_WIN0V = ( m_WIN0V & ~mem_mask ) | ( data & mem_mask );
			}
			if( (mem_mask) & 0xffff0000 )
			{
				verboselog(*this, 2, "GBA IO Register Write: WIN1V (%08x) = %04x (%08x)\n", 0x04000000 + ( offset << 2 ), ( data & 0xffff0000 ) >> 16, ~mem_mask );
				m_WIN1V = ( m_WIN1V & ( ~mem_mask >> 16 ) ) | ( ( data & mem_mask ) >> 16 );
			}
			break;
		case 0x0048/4:
			if( (mem_mask) & 0x0000ffff )
			{
				verboselog(*this, 2, "GBA IO Register Write: WININ (%08x) = %04x (%08x)\n", 0x04000000 + ( offset << 2 ), data & 0x0000ffff, ~mem_mask );
				m_WININ = ( m_WININ & ~mem_mask ) | ( data & mem_mask );
			}
			if( (mem_mask) & 0xffff0000 )
			{
				verboselog(*this, 2, "GBA IO Register Write: WINOUT (%08x) = %04x (%08x)\n", 0x04000000 + ( offset << 2 ), ( data & 0xffff0000 ) >> 16, ~mem_mask );
				m_WINOUT = ( m_WINOUT & ( ~mem_mask >> 16 ) ) | ( ( data & mem_mask ) >> 16 );
			}
			break;
		case 0x004c/4:
			if( (mem_mask) & 0x0000ffff )
			{
				verboselog(*this, 2, "GBA IO Register Write: MOSAIC (%08x) = %04x (%08x)\n", 0x04000000 + ( offset << 2 ), data & 0x0000ffff, ~mem_mask );
				m_MOSAIC = ( m_MOSAIC & ~mem_mask ) | ( data & mem_mask );
			}
			if( (mem_mask) & 0xffff0000 )
			{
				verboselog(*this, 2, "GBA IO Register Write: UNKNOWN (%08x) = %04x (%08x)\n", 0x04000000 + ( offset << 2 ), ( data & 0xffff0000 ) >> 16, ~mem_mask );
			}
			break;
		case 0x0050/4:
			if( (mem_mask) & 0x0000ffff )
			{
				verboselog(*this, 2, "GBA IO Register Write: BLDCNT (%08x) = %04x (%08x)\n", 0x04000000 + ( offset << 2 ), data & 0x0000ffff, ~mem_mask );
				m_BLDCNT = ( m_BLDCNT & ~mem_mask ) | ( data & mem_mask );
				if(m_BLDCNT & BLDCNT_SFX)
				{
					m_fxOn = 1;
				}
				else
				{
					m_fxOn = 0;
				}
			}
			if( (mem_mask) & 0xffff0000 )
			{
				verboselog(*this, 2, "GBA IO Register Write: BLDALPHA (%08x) = %04x (%08x)\n", 0x04000000 + ( offset << 2 ), ( data & 0xffff0000 ) >> 16, ~mem_mask );
				m_BLDALPHA = ( m_BLDALPHA & ( ~mem_mask >> 16 ) ) | ( ( data & mem_mask ) >> 16 );
			}
			break;
		case 0x0054/4:
			if( (mem_mask) & 0x0000ffff )
			{
				verboselog(*this, 2, "GBA IO Register Write: BLDY (%08x) = %04x (%08x)\n", 0x04000000 + ( offset << 2 ), data & 0x0000ffff, ~mem_mask );
				m_BLDY = ( m_BLDY & ~mem_mask ) | ( data & mem_mask );
			}
			if( (mem_mask) & 0xffff0000 )
			{
				verboselog(*this, 2, "GBA IO Register Write: UNKNOWN (%08x) = %04x (%08x)\n", 0x04000000 + ( offset << 2 ), ( data & 0xffff0000 ) >> 16, ~mem_mask );
			}
			break;
		case 0x0058/4:
			if( (mem_mask) & 0x0000ffff )
			{
				verboselog(*this, 2, "GBA IO Register Write: UNKNOWN (%08x) = %04x (%08x)\n", 0x04000000 + ( offset << 2 ), data & 0x0000ffff, ~mem_mask );
			}
			if( (mem_mask) & 0xffff0000 )
			{
				verboselog(*this, 2, "GBA IO Register Write: UNKNOWN (%08x) = %04x (%08x)\n", 0x04000000 + ( offset << 2 ), ( data & 0xffff0000 ) >> 16, ~mem_mask );
			}
			break;
		case 0x005c/4:
			if( (mem_mask) & 0x0000ffff )
			{
				verboselog(*this, 2, "GBA IO Register Write: UNKNOWN (%08x) = %04x (%08x)\n", 0x04000000 + ( offset << 2 ), data & 0x0000ffff, ~mem_mask );
			}
			if( (mem_mask) & 0xffff0000 )
			{
				verboselog(*this, 2, "GBA IO Register Write: UNKNOWN (%08x) = %04x (%08x)\n", 0x04000000 + ( offset << 2 ), ( data & 0xffff0000 ) >> 16, ~mem_mask );
			}
			break;
		case 0x0060/4:
			if( (mem_mask) & 0x000000ff )   // SOUNDCNTL
			{
				m_gbsound->sound_w(space, 0, data);
			}
			if( (mem_mask) & 0x00ff0000 )
			{
				m_gbsound->sound_w(space, 1, data>>16);  // SOUND1CNT_H
			}
			if( (mem_mask) & 0xff000000 )
			{
				m_gbsound->sound_w(space, 2, data>>24);
			}
			break;
		case 0x0064/4:
			if( (mem_mask) & 0x000000ff )   // SOUNDCNTL
			{
				m_gbsound->sound_w(space, 3, data);
			}
			if( (mem_mask) & 0x0000ff00 )
			{
				m_gbsound->sound_w(space, 4, data>>8);   // SOUND1CNT_H
			}
			break;
		case 0x0068/4:
			if( (mem_mask) & 0x000000ff )
			{
				m_gbsound->sound_w(space, 6, data);
			}
			if( (mem_mask) & 0x0000ff00 )
			{
				m_gbsound->sound_w(space, 7, data>>8);
			}
			break;
		case 0x006c/4:
			if( (mem_mask) & 0x000000ff )
			{
				m_gbsound->sound_w(space, 8, data);
			}
			if( (mem_mask) & 0x0000ff00 )
			{
				m_gbsound->sound_w(space, 9, data>>8);
			}
			break;
		case 0x0070/4:  //SND3CNTL and H
			if( (mem_mask) & 0x000000ff )   // SOUNDCNTL
			{
				m_gbsound->sound_w(space, 0xa, data);
			}
			if( (mem_mask) & 0x00ff0000 )
			{
				m_gbsound->sound_w(space, 0xb, data>>16);    // SOUND1CNT_H
			}
			if( (mem_mask) & 0xff000000 )
			{
				m_gbsound->sound_w(space, 0xc, data>>24);
			}
			break;
		case 0x0074/4:
			if( (mem_mask) & 0x000000ff )
			{
				m_gbsound->sound_w(space, 0xd, data);
			}
			if( (mem_mask) & 0x0000ff00 )
			{
				m_gbsound->sound_w(space, 0xe, data>>8);
			}
			break;
		case 0x0078/4:
			if( (mem_mask) & 0x000000ff )
			{
				m_gbsound->sound_w(space, 0x10, data);
			}
			if( (mem_mask) & 0x0000ff00 )
			{
				m_gbsound->sound_w(space, 0x11, data>>8);
			}
			break;
		case 0x007c/4:
			if( (mem_mask) & 0x000000ff )
			{
				m_gbsound->sound_w(space, 0x12, data);
			}
			if( (mem_mask) & 0x0000ff00 )
			{
				m_gbsound->sound_w(space, 0x13, data>>8);
			}
			break;
		case 0x0080/4:
			if( (mem_mask) & 0x000000ff )
			{
				m_gbsound->sound_w(space, 0x14, data);
			}
			if( (mem_mask) & 0x0000ff00 )
			{
				m_gbsound->sound_w(space, 0x15, data>>8);
			}

			if ((mem_mask) & 0xffff0000)
			{
				data >>= 16;
				m_SOUNDCNT_H = data;

				// DAC A reset?
				if (data & 0x0800)
				{
					m_fifo_a_ptr = 17;
					m_fifo_a_in = 17;
					m_ladac->write_signed8(0x80);
					m_radac->write_signed8(0x80);
				}

				// DAC B reset?
				if (data & 0x8000)
				{
					m_fifo_b_ptr = 17;
					m_fifo_b_in = 17;
					m_lbdac->write_signed8(0x80);
					m_rbdac->write_signed8(0x80);
=======
		case 0x0130/4:
			if( ACCESSING_BITS_0_15 )   // KEYINPUT
			{
				retval = m_io_inputs->read();
			}
			else if( ACCESSING_BITS_16_31 )
			{
				retval |= KEYCNT << 16;
			}
			break;
		case 0x0200/4:
			retval = IE | (IF << 16);
			break;
		default:
			if( ACCESSING_BITS_0_15 )
			{
				retval |= m_regs[offset] & 0x0000ffff;
			}
			if( ACCESSING_BITS_16_31 )
			{
				retval |= m_regs[offset] & 0xffff0000;
			}
			break;
	}

//  assert_always(offset < ARRAY_LENGTH(reg_names) / 2, "Not enough register names in gba_state");

	if (ACCESSING_BITS_0_15)
	{
		verboselog(*this, 2, "GBA I/O Read: %s = %04x\n", reg_names[offset * 2], retval & 0x0000ffff);
	}
	if (ACCESSING_BITS_16_31)
	{
		verboselog(*this, 2, "GBA I/O Read: %s = %04x\n", reg_names[offset * 2 + 1], (retval & 0xffff0000) >> 16);
	}

	return retval;
}

WRITE32_MEMBER(gba_state::gba_io_w)
{
	uint8_t soundcnt_x = SOUNDCNT_X;
	uint16_t siocnt = SIOCNT;
	uint16_t dmachcnt[4] = { DMACNT_H(0), DMACNT_H(1), DMACNT_H(2), DMACNT_H(3) };

	COMBINE_DATA(&m_regs[offset]);

//  assert_always(offset < ARRAY_LENGTH(reg_names) / 2, "Not enough register names in gba_state");

	if (ACCESSING_BITS_0_15)
	{
		verboselog(*this, 2, "GBA I/O Write: %s = %04x\n", reg_names[offset * 2], data & 0x0000ffff);
	}
	if (ACCESSING_BITS_16_31)
	{
		verboselog(*this, 2, "GBA I/O Write: %s = %04x\n", reg_names[offset * 2 + 1], (data & 0xffff0000) >> 16);
	}

	switch( offset + 0x60/4 )
	{
		case 0x0060/4:
			if( ACCESSING_BITS_0_7 )   // SOUNDCNTL
			{
				m_gbsound->sound_w(space, 0, data);
			}
			if( ACCESSING_BITS_16_23 )
			{
				m_gbsound->sound_w(space, 1, data>>16);  // SOUND1CNT_H
			}
			if( ACCESSING_BITS_24_31 )
			{
				m_gbsound->sound_w(space, 2, data>>24);
			}
			break;
		case 0x0064/4:
			if( ACCESSING_BITS_0_7 )   // SOUNDCNTL
			{
				m_gbsound->sound_w(space, 3, data);
			}
			if( ACCESSING_BITS_8_15 )
			{
				m_gbsound->sound_w(space, 4, data>>8);   // SOUND1CNT_H
			}
			break;
		case 0x0068/4:
			if( ACCESSING_BITS_0_7 )
			{
				m_gbsound->sound_w(space, 6, data);
			}
			if( ACCESSING_BITS_8_15 )
			{
				m_gbsound->sound_w(space, 7, data>>8);
			}
			break;
		case 0x006c/4:
			if( ACCESSING_BITS_0_7 )
			{
				m_gbsound->sound_w(space, 8, data);
			}
			if( ACCESSING_BITS_8_15 )
			{
				m_gbsound->sound_w(space, 9, data>>8);
			}
			break;
		case 0x0070/4:  //SND3CNTL and H
			if( ACCESSING_BITS_0_7 )   // SOUNDCNTL
			{
				m_gbsound->sound_w(space, 0xa, data);
			}
			if( ACCESSING_BITS_16_23 )
			{
				m_gbsound->sound_w(space, 0xb, data>>16);    // SOUND1CNT_H
			}
			if( ACCESSING_BITS_24_31 )
			{
				m_gbsound->sound_w(space, 0xc, data>>24);
			}
			break;
		case 0x0074/4:
			if( ACCESSING_BITS_0_7 )
			{
				m_gbsound->sound_w(space, 0xd, data);
			}
			if( ACCESSING_BITS_8_15 )
			{
				m_gbsound->sound_w(space, 0xe, data>>8);
			}
			break;
		case 0x0078/4:
			if( ACCESSING_BITS_0_7 )
			{
				m_gbsound->sound_w(space, 0x10, data);
			}
			if( ACCESSING_BITS_8_15 )
			{
				m_gbsound->sound_w(space, 0x11, data>>8);
			}
			break;
		case 0x007c/4:
			if( ACCESSING_BITS_0_7 )
			{
				m_gbsound->sound_w(space, 0x12, data);
			}
			if( ACCESSING_BITS_8_15 )
			{
				m_gbsound->sound_w(space, 0x13, data>>8);
			}
			break;
		case 0x0080/4:
			if( ACCESSING_BITS_0_7 )
			{
				m_gbsound->sound_w(space, 0x14, data);
			}
			if( ACCESSING_BITS_8_15 )
			{
				m_gbsound->sound_w(space, 0x15, data>>8);
			}

			if (ACCESSING_BITS_16_31)
			{
				// DAC A reset?
				if (data & 0x08000000)
				{
					m_fifo_a_ptr = 17;
					m_fifo_a_in = 17;
					m_ldaca->write(0);
					m_rdaca->write(0);
				}

				// DAC B reset?
				if (data & 0x80000000)
				{
					m_fifo_b_ptr = 17;
					m_fifo_b_in = 17;
					m_ldacb->write(0);
					m_rdacb->write(0);
>>>>>>> upstream/master
				}
			}
			break;
		case 0x0084/4:
<<<<<<< HEAD
			if( (mem_mask) & 0x000000ff )
			{
				m_gbsound->sound_w(space, 0x16, data);
				if ((data & 0x80) && !(m_SOUNDCNT_X & 0x80))
				{
					m_fifo_a_ptr = m_fifo_a_in = 17;
					m_fifo_b_ptr = m_fifo_b_in = 17;
					m_ladac->write_signed8(0x80);
					m_radac->write_signed8(0x80);
					m_lbdac->write_signed8(0x80);
					m_rbdac->write_signed8(0x80);
				}
				m_SOUNDCNT_X = data;
			}
			break;
		case 0x0088/4:
			if( (mem_mask) & 0x0000ffff )
			{
				verboselog(*this, 2, "GBA IO Register Write: SOUNDBIAS (%08x) = %04x (%08x)\n", 0x04000000 + ( offset << 2 ), data & 0x0000ffff, ~mem_mask );
				m_SOUNDBIAS = ( m_SOUNDBIAS & ~mem_mask ) | ( data & mem_mask );
			}
			if( (mem_mask) & 0xffff0000 )
			{
				verboselog(*this, 2, "GBA IO Register Write: UNKNOWN (%08x) = %04x (%08x)\n", 0x04000000 + ( offset << 2 ), ( data & 0xffff0000 ) >> 16, ~mem_mask );
			}
			break;
		case 0x0090/4:
			if( (mem_mask) & 0x000000ff )
			{
				m_gbsound->wave_w(space, 0, data);
			}
			if( (mem_mask) & 0x0000ff00 )
			{
				m_gbsound->wave_w(space, 1, data>>8);
			}
			if( (mem_mask) & 0x00ff0000 )
			{
				m_gbsound->wave_w(space, 2, data>>16);
			}
			if( (mem_mask) & 0xff000000 )
=======
			if( ACCESSING_BITS_0_7 )
			{
				m_gbsound->sound_w(space, 0x16, data);
				if ((data & 0x80) && !(soundcnt_x & 0x80))
				{
					m_fifo_a_ptr = m_fifo_a_in = 17;
					m_fifo_b_ptr = m_fifo_b_in = 17;
					m_ldaca->write(0);
					m_rdaca->write(0);
					m_ldacb->write(0);
					m_rdacb->write(0);
				}
			}
			break;
		case 0x0090/4:
			if( ACCESSING_BITS_0_7 )
			{
				m_gbsound->wave_w(space, 0, data);
			}
			if( ACCESSING_BITS_8_15 )
			{
				m_gbsound->wave_w(space, 1, data>>8);
			}
			if( ACCESSING_BITS_16_23 )
			{
				m_gbsound->wave_w(space, 2, data>>16);
			}
			if( ACCESSING_BITS_24_31 )
>>>>>>> upstream/master
			{
				m_gbsound->wave_w(space, 3, data>>24);
			}
			break;
		case 0x0094/4:
<<<<<<< HEAD
			if( (mem_mask) & 0x000000ff )
			{
				m_gbsound->wave_w(space, 4, data);
			}
			if( (mem_mask) & 0x0000ff00 )
			{
				m_gbsound->wave_w(space, 5, data>>8);
			}
			if( (mem_mask) & 0x00ff0000 )
			{
				m_gbsound->wave_w(space, 6, data>>16);
			}
			if( (mem_mask) & 0xff000000 )
=======
			if( ACCESSING_BITS_0_7 )
			{
				m_gbsound->wave_w(space, 4, data);
			}
			if( ACCESSING_BITS_8_15 )
			{
				m_gbsound->wave_w(space, 5, data>>8);
			}
			if( ACCESSING_BITS_16_23 )
			{
				m_gbsound->wave_w(space, 6, data>>16);
			}
			if( ACCESSING_BITS_24_31 )
>>>>>>> upstream/master
			{
				m_gbsound->wave_w(space, 7, data>>24);
			}
			break;
		case 0x0098/4:
<<<<<<< HEAD
			if( (mem_mask) & 0x000000ff )
			{
				m_gbsound->wave_w(space, 8, data);
			}
			if( (mem_mask) & 0x0000ff00 )
			{
				m_gbsound->wave_w(space, 9, data>>8);
			}
			if( (mem_mask) & 0x00ff0000 )
			{
				m_gbsound->wave_w(space, 0xa, data>>16);
			}
			if( (mem_mask) & 0xff000000 )
=======
			if( ACCESSING_BITS_0_7 )
			{
				m_gbsound->wave_w(space, 8, data);
			}
			if( ACCESSING_BITS_8_15 )
			{
				m_gbsound->wave_w(space, 9, data>>8);
			}
			if( ACCESSING_BITS_16_23 )
			{
				m_gbsound->wave_w(space, 0xa, data>>16);
			}
			if( ACCESSING_BITS_24_31 )
>>>>>>> upstream/master
			{
				m_gbsound->wave_w(space, 0xb, data>>24);
			}
			break;
		case 0x009c/4:
<<<<<<< HEAD
			if( (mem_mask) & 0x000000ff )
			{
				m_gbsound->wave_w(space, 0xc, data);
			}
			if( (mem_mask) & 0x0000ff00 )
			{
				m_gbsound->wave_w(space, 0xd, data>>8);
			}
			if( (mem_mask) & 0x00ff0000 )
			{
				m_gbsound->wave_w(space, 0xe, data>>16);
			}
			if( (mem_mask) & 0xff000000 )
=======
			if( ACCESSING_BITS_0_7 )
			{
				m_gbsound->wave_w(space, 0xc, data);
			}
			if( ACCESSING_BITS_8_15 )
			{
				m_gbsound->wave_w(space, 0xd, data>>8);
			}
			if( ACCESSING_BITS_16_23 )
			{
				m_gbsound->wave_w(space, 0xe, data>>16);
			}
			if( ACCESSING_BITS_24_31 )
>>>>>>> upstream/master
			{
				m_gbsound->wave_w(space, 0xf, data>>24);
			}
			break;
		case 0x00a0/4:
			m_fifo_a_in %= 17;
			m_fifo_a[m_fifo_a_in++] = (data)&0xff;
			m_fifo_a_in %= 17;
			m_fifo_a[m_fifo_a_in++] = (data>>8)&0xff;
			m_fifo_a_in %= 17;
			m_fifo_a[m_fifo_a_in++] = (data>>16)&0xff;
			m_fifo_a_in %= 17;
			m_fifo_a[m_fifo_a_in++] = (data>>24)&0xff;
			break;
		case 0x00a4/4:
			m_fifo_b_in %= 17;
			m_fifo_b[m_fifo_b_in++] = (data)&0xff;
			m_fifo_b_in %= 17;
			m_fifo_b[m_fifo_b_in++] = (data>>8)&0xff;
			m_fifo_b_in %= 17;
			m_fifo_b[m_fifo_b_in++] = (data>>16)&0xff;
			m_fifo_b_in %= 17;
			m_fifo_b[m_fifo_b_in++] = (data>>24)&0xff;
			break;
<<<<<<< HEAD
		case 0x00b0/4:
		case 0x00b4/4:
		case 0x00b8/4:

		case 0x00bc/4:
		case 0x00c0/4:
		case 0x00c4/4:

		case 0x00c8/4:
		case 0x00cc/4:
		case 0x00d0/4:

		case 0x00d4/4:
		case 0x00d8/4:
		case 0x00dc/4:
			{
				int ch;

				offset -= (0xb0/4);

				ch = offset / 3;

//              printf("%08x: DMA(%d): %x to reg %d (mask %08x)\n", space.device().safe_pc(), ch, data, offset%3, ~mem_mask);

				if (((offset % 3) == 2) && ((~mem_mask & 0xffff0000) == 0))
				{
					int ctrl = data>>16;

					// Note: Metroid Fusion fails if we enforce the "rising edge" requirement... (who wrote this note?)

					// Note: Caesar's Palace Advance fails if we DO NOT enforce the "rising edge" requirement
					// (value @ 0x3003F9C is accidentally incremented because DMA completion interrupt is accidentally triggered @ 08002F2A)

					// retrigger/restart on a rising edge.
					// also reload internal regs
					if ((ctrl & 0x8000) && !(m_dma_regs[offset] & 0x80000000))
					{
						m_dma_src[ch] = m_dma_regs[(ch*3)+0];
						m_dma_dst[ch] = m_dma_regs[(ch*3)+1];
						m_dma_srcadd[ch] = (ctrl>>7)&3;
						m_dma_dstadd[ch] = (ctrl>>5)&3;

						COMBINE_DATA(&m_dma_regs[offset]);
						m_dma_cnt[ch] = m_dma_regs[(ch*3)+2]&0xffff;

						// immediate start
						if ((ctrl & 0x3000) == 0)
						{
							dma_exec(ch);
							return;
						}
					}
				}

				COMBINE_DATA(&m_dma_regs[offset]);
=======
		case 0x00b8/4:
		case 0x00c4/4:
		case 0x00d0/4:
		case 0x00dc/4:
			if( ACCESSING_BITS_16_31 )
			{
				int ch = (offset + 0x60/4 - 0xb0/4) / 3;

				int ctrl = data>>16;

				// Note: Metroid Fusion fails if we enforce the "rising edge" requirement... (who wrote this note?)

				// Note: Caesar's Palace Advance fails if we DO NOT enforce the "rising edge" requirement
				// (value @ 0x3003F9C is accidentally incremented because DMA completion interrupt is accidentally triggered @ 08002F2A)

				// retrigger/restart on a rising edge.
				// also reload internal regs
				if ((ctrl & 0x8000) && !(dmachcnt[ch] & 0x8000))
				{
					m_dma_src[ch] = DMASAD(ch);
					m_dma_dst[ch] = DMADAD(ch);
					m_dma_cnt[ch] = DMACNT_L(ch);

					// immediate start
					if ((ctrl & 0x3000) == 0)
					{
						dma_exec(ch);
						return;
					}
				}
>>>>>>> upstream/master
			}
			break;
		case 0x0100/4:
		case 0x0104/4:
		case 0x0108/4:
		case 0x010c/4:
			{
				double rate, clocksel;
<<<<<<< HEAD
				UINT32 old_timer_regs;

				offset -= (0x100/4);

				old_timer_regs = m_timer_regs[offset];

				m_timer_regs[offset] = (m_timer_regs[offset] & ~(mem_mask & 0xFFFF0000)) | (data & (mem_mask & 0xFFFF0000));

//              printf("%x to timer %d (mask %x PC %x)\n", data, offset, ~mem_mask, space.device().safe_pc());

				if (ACCESSING_BITS_0_15)
				{
					m_timer_reload[offset] = ((m_timer_reload[offset] & ~mem_mask) | (data & mem_mask)) & 0x0000FFFF;
					m_timer_recalc[offset] = 1;
=======
				uint32_t old_timer_regs;

				int timer = offset + 0x60/4 - 0x100/4;

				old_timer_regs = m_timer_regs[timer];

				m_timer_regs[timer] = (m_timer_regs[timer] & ~(mem_mask & 0xFFFF0000)) | (data & (mem_mask & 0xFFFF0000));

//              printf("%x to timer %d (mask %x PC %x)\n", data, timer, ~mem_mask, space.device().safe_pc());

				if (ACCESSING_BITS_0_15)
				{
					m_timer_reload[timer] = ((m_timer_reload[timer] & ~mem_mask) | (data & mem_mask)) & 0x0000FFFF;
					m_timer_recalc[timer] = 1;
>>>>>>> upstream/master
				}

				// enabling this timer?
				if ((ACCESSING_BITS_16_31) && (data & 0x800000))
				{
					double final;

					if ((old_timer_regs & 0x00800000) == 0) // start bit 0 -> 1
					{
<<<<<<< HEAD
						m_timer_regs[offset] = (m_timer_regs[offset] & 0xFFFF0000) | (m_timer_reload[offset] & 0x0000FFFF);
					}

					rate = 0x10000 - (m_timer_regs[offset] & 0xffff);

					clocksel = timer_clks[(m_timer_regs[offset] >> 16) & 3];

					final = clocksel / rate;

					m_timer_hz[offset] = final;

					m_timer_recalc[offset] = 0;

//                  printf("Enabling timer %d @ %f Hz\n", offset, final);
=======
						m_timer_regs[timer] = (m_timer_regs[timer] & 0xFFFF0000) | (m_timer_reload[timer] & 0x0000FFFF);
					}

					rate = 0x10000 - (m_timer_regs[timer] & 0xffff);

					clocksel = timer_clks[(m_timer_regs[timer] >> 16) & 3];

					final = clocksel / rate;

					m_timer_hz[timer] = final;

					m_timer_recalc[timer] = 0;

//                  printf("Enabling timer %d @ %f Hz\n", timer, final);
>>>>>>> upstream/master

					// enable the timer
					if( !(data & 0x40000) ) // if we're not in Count-Up mode
					{
						attotime time = attotime::from_hz(final);
<<<<<<< HEAD
						GBA_ATTOTIME_NORMALIZE(time);
						m_tmr_timer[offset]->adjust(time, offset, time);
=======
						m_tmr_timer[timer]->adjust(time, timer, time);
>>>>>>> upstream/master
					}
				}
			}
			break;
<<<<<<< HEAD
		case 0x0120/4:
			if( (mem_mask) & 0x0000ffff )
			{
				verboselog(*this, 2, "GBA IO Register Write: SIOMULTI0 (%08x) = %04x (%08x)\n", 0x04000000 + ( offset << 2 ), data & mem_mask, ~mem_mask );
				m_SIOMULTI0 = ( m_SIOMULTI0 & ~mem_mask ) | ( data & mem_mask );
			}
			if( (mem_mask) & 0xffff0000 )
			{
				verboselog(*this, 2, "GBA IO Register Write: SIOMULTI1 (%08x) = %04x (%08x)\n", 0x04000000 + ( offset << 2 ), ( data & mem_mask ) >> 16, ~mem_mask );
				m_SIOMULTI1 = ( m_SIOMULTI1 & ( ~mem_mask >> 16 ) ) | ( ( data & mem_mask ) >> 16 );
			}
			break;
		case 0x0124/4:
			if( (mem_mask) & 0x0000ffff )
			{
				verboselog(*this, 2, "GBA IO Register Write: SIOMULTI2 (%08x) = %04x (%08x)\n", 0x04000000 + ( offset << 2 ), data & mem_mask, ~mem_mask );
				m_SIOMULTI2 = ( m_SIOMULTI2 & ~mem_mask ) | ( data & mem_mask );
			}
			if( (mem_mask) & 0xffff0000 )
			{
				verboselog(*this, 2, "GBA IO Register Write: SIOMULTI3 (%08x) = %04x (%08x)\n", 0x04000000 + ( offset << 2 ), ( data & mem_mask ) >> 16, ~mem_mask );
				m_SIOMULTI3 = ( m_SIOMULTI3 & ( ~mem_mask >> 16 ) ) | ( ( data & mem_mask ) >> 16 );
			}
			break;
		case 0x0128/4:
			if( (mem_mask) & 0x0000ffff )
			{
				verboselog(*this, 2, "GBA IO Register Write: SIOCNT (%08x) = %04x (%08x)\n", 0x04000000 + ( offset << 2 ), data & mem_mask, ~mem_mask );
				// normal mode ?
				if (((m_RCNT & 0x8000) == 0) && ((data & 0x2000) == 0))
				{
					// start ?
					if (((m_SIOCNT & 0x0080) == 0) && ((data & 0x0080) != 0))
					{
						data &= ~0x0080;
=======
		case 0x0128/4:
			if( ACCESSING_BITS_0_15 )
			{
				// normal mode ?
				if (!(RCNT & 0x8000) && !(data & 0x2000))
				{
					// start ?
					if (!(siocnt & 0x0080) && (data & 0x0080))
					{
						SIOCNT_RESET(0x0080);
>>>>>>> upstream/master
						// request interrupt ?
						if (data & 0x4000)
						{
							request_irq(INT_SIO);
						}
					}
				}
<<<<<<< HEAD
				m_SIOCNT = ( m_SIOCNT & ~mem_mask ) | ( data & mem_mask );
			}
			if( (mem_mask) & 0xffff0000 )
			{
				verboselog(*this, 2, "GBA IO Register Write: SIODATA8 (%08x) = %04x (%08x)\n", 0x04000000 + ( offset << 2 ), ( data & mem_mask ) >> 16, ~mem_mask );
				m_SIODATA8 = ( m_SIODATA8 & ( ~mem_mask >> 16 ) ) | ( ( data & mem_mask ) >> 16 );
			}
			break;
		case 0x0130/4:
			if( (mem_mask) & 0xffff0000 )
			{
//              printf("KEYCNT = %04x\n", data>>16);
				verboselog(*this, 2, "GBA IO Register Write: KEYCNT (%08x) = %04x (%08x)\n", 0x04000000 + ( offset << 2 ), ( data & mem_mask ) >> 16, ~mem_mask );
				m_KEYCNT = ( m_KEYCNT & ( ~mem_mask >> 16 ) ) | ( ( data & mem_mask ) >> 16 );
			}
			break;
		case 0x0134/4:
			if( (mem_mask) & 0x0000ffff )
			{
				verboselog(*this, 2, "GBA IO Register Write: RCNT (%08x) = %04x (%08x)\n", 0x04000000 + ( offset << 2 ), data & mem_mask, ~mem_mask );
				m_RCNT = ( m_RCNT & ~mem_mask ) | ( data & mem_mask );
			}
			if( (mem_mask) & 0xffff0000 )
			{
				verboselog(*this, 2, "GBA IO Register Write: IR (%08x) = %04x (%08x)\n", 0x04000000 + ( offset << 2 ), ( data & mem_mask ) >> 16, ~mem_mask );
				m_IR = ( m_IR & ( ~mem_mask >> 16 ) ) | ( ( data & mem_mask ) >> 16 );
			}
			break;
		case 0x0140/4:
			if( (mem_mask) & 0x0000ffff )
			{
				verboselog(*this, 2, "GBA IO Register Write: JOYCNT (%08x) = %04x (%08x)\n", 0x04000000 + ( offset << 2 ), data & mem_mask, ~mem_mask );
				m_JOYCNT = ( m_JOYCNT & ~mem_mask ) | ( data & mem_mask );
			}
			if( (mem_mask) & 0xffff0000 )
			{
				verboselog(*this, 2, "GBA IO Register Write: UNKNOWN (%08x) = %04x (%08x)\n", 0x04000000 + ( offset << 2 ), ( data & mem_mask ) >> 16, ~mem_mask );
			}
			break;
		case 0x0150/4:
			if( (mem_mask) & 0x0000ffff )
			{
				verboselog(*this, 2, "GBA IO Register Write: JOY_RECV_LSW (%08x) = %04x (%08x)\n", 0x04000000 + ( offset << 2 ), data & mem_mask, ~mem_mask );
				m_JOY_RECV = ( m_JOY_RECV & ~mem_mask ) | ( data & mem_mask );
			}
			if( (mem_mask) & 0xffff0000 )
			{
				verboselog(*this, 2, "GBA IO Register Write: JOY_RECV_MSW (%08x) = %04x (%08x)\n", 0x04000000 + ( offset << 2 ), ( data & mem_mask ) >> 16, ~mem_mask );
				m_JOY_RECV = ( m_JOY_RECV & ( ~mem_mask >> 16 ) ) | ( ( data & mem_mask ) >> 16 );
			}
			break;
		case 0x0154/4:
			if( (mem_mask) & 0x0000ffff )
			{
				verboselog(*this, 2, "GBA IO Register Write: JOY_TRANS_LSW (%08x) = %04x (%08x)\n", 0x04000000 + ( offset << 2 ), data & mem_mask, ~mem_mask );
				m_JOY_TRANS = ( m_JOY_TRANS & ~mem_mask ) | ( data & mem_mask );
			}
			if( (mem_mask) & 0xffff0000 )
			{
				verboselog(*this, 2, "GBA IO Register Write: JOY_TRANS_MSW (%08x) = %04x (%08x)\n", 0x04000000 + ( offset << 2 ), ( data & mem_mask ) >> 16, ~mem_mask );
				m_JOY_TRANS = ( m_JOY_TRANS & ( ~mem_mask >> 16 ) ) | ( ( data & mem_mask ) >> 16 );
			}
			break;
		case 0x0158/4:
			if( (mem_mask) & 0x0000ffff )
			{
				verboselog(*this, 2, "GBA IO Register Write: JOYSTAT (%08x) = %04x (%08x)\n", 0x04000000 + ( offset << 2 ), data & mem_mask, ~mem_mask );
				m_JOYSTAT = ( m_JOYSTAT & ~mem_mask ) | ( data & mem_mask );
			}
			if( (mem_mask) & 0xffff0000 )
			{
				verboselog(*this, 2, "GBA IO Register Write: UNKNOWN (%08x) = %04x (%08x)\n", 0x04000000 + ( offset << 2 ), ( data & mem_mask ) >> 16, ~mem_mask );
			}
			break;
		case 0x0200/4:
			if( (mem_mask) & 0x0000ffff )
			{
//              printf("IE (%08x) = %04x raw %x (%08x) (scan %d PC %x)\n", 0x04000000 + ( offset << 2 ), data & mem_mask, data, ~mem_mask, machine.first_screen()->vpos(), space.device().safe_pc());
				m_IE = ( m_IE & ~mem_mask ) | ( data & mem_mask );
#if 0
				if (m_IE & m_IF)
				{
					request_irq(m_IF);
				}
#endif
			}
			if( (mem_mask) & 0xffff0000 )
			{
				verboselog(*this, 2, "GBA IO Register Write: IF (%08x) = %04x (%08x)\n", 0x04000000 + ( offset << 2 ) + 2, ( data & mem_mask ) >> 16, ~mem_mask );
				m_IF &= ~( ( data & mem_mask ) >> 16 );

				// if we still have interrupts, yank the IRQ line again
				if (m_IF)
=======
			}
			break;
		case 0x0200/4:
			if( ACCESSING_BITS_0_15 )
			{
#if 0
				if (IE & IF)
				{
					request_irq(IF);
				}
#endif
			}
			if( ACCESSING_BITS_16_31 )
			{
				IF_RESET(( data & mem_mask ) >> 16);

				// if we still have interrupts, yank the IRQ line again
				if (IF)
>>>>>>> upstream/master
				{
					m_irq_timer->adjust(m_maincpu->clocks_to_attotime(120));
				}
			}
			break;
<<<<<<< HEAD
		case 0x0204/4:
			if( (mem_mask) & 0x0000ffff )
			{
				verboselog(*this, 2, "GBA IO Register Write: WAITCNT (%08x) = %04x (%08x)\n", 0x04000000 + ( offset << 2 ), data & mem_mask, ~mem_mask );
				m_WAITCNT = ( m_WAITCNT & ~mem_mask ) | ( data & mem_mask );
			}
			if( (mem_mask) & 0xffff0000 )
			{
				verboselog(*this, 2, "GBA IO Register Write: UNKNOWN (%08x) = %04x (%08x)\n", 0x04000000 + ( offset << 2 ), ( data & mem_mask ) >> 16, ~mem_mask );
			}
			break;
		case 0x0208/4:
			if( (mem_mask) & 0x0000ffff )
			{
				verboselog(*this, 3, "GBA IO Register Write: IME (%08x) = %04x (%08x)\n", 0x04000000 + ( offset << 2 ), data & mem_mask, ~mem_mask );
				m_IME = ( m_IME & ~mem_mask ) | ( data & mem_mask );
				if (m_IF)
=======
		case 0x0208/4:
			if( ACCESSING_BITS_0_15 )
			{
				if (IF)
>>>>>>> upstream/master
				{
					m_irq_timer->adjust(attotime::zero);
				}
			}
<<<<<<< HEAD
			if( (mem_mask) & 0xffff0000 )
			{
				verboselog(*this, 3, "GBA IO Register Write: UNKNOWN (%08x) = %04x (%08x)\n", 0x04000000 + ( offset << 2 ), ( data & mem_mask ) >> 16, ~mem_mask );
			}
			break;
		case 0x0300/4:
			if( (mem_mask) & 0x0000ffff )
			{
				if( (mem_mask) & 0x000000ff )
				{
					verboselog(*this, 2, "GBA IO Register Write: POSTFLG (%08x) = %02x (%08x)\n", 0x04000000 + ( offset << 2 ), data & 0x000000ff, ~mem_mask );
					m_POSTFLG = data & 0x000000ff;
				}
				else
				{
					m_HALTCNT = data & 0x000000ff;

					// either way, wait for an IRQ
					m_maincpu->spin_until_interrupt();
				}
			}
			if( (mem_mask) & 0xffff0000 )
			{
				verboselog(*this, 2, "GBA IO Register Write: UNKNOWN (%08x) = %04x (%08x)\n", 0x04000000 + ( offset << 2 ), ( data & 0xffff0000 ) >> 16, ~mem_mask );
			}
			break;
		default:
//          verboselog(machine, 0, "Unknown GBA I/O register write: %08x = %08x (%08x)\n", 0x04000000 + ( offset << 2 ), data, ~mem_mask );
=======
			break;
		case 0x0300/4:
			if( ACCESSING_BITS_8_15 )
			{
				// power down commanded, halt the CPU
				m_maincpu->spin_until_interrupt();
			}
>>>>>>> upstream/master
			break;
	}
}

<<<<<<< HEAD
INLINE UINT32 COMBINE_DATA32_16(UINT32 prev, UINT32 data, UINT32 mem_mask)
{
	COMBINE_DATA(&prev);
	switch(mem_mask)
	{
		case 0x000000ff:
			prev &= 0xffff00ff;
			prev |= data << 8;
			break;
		case 0x0000ff00:
			prev &= 0xffffff00;
			prev |= data >> 8;
			break;
		case 0x00ff0000:
			prev &= 0x00ffffff;
			prev |= data << 8;
			break;
		case 0xff000000:
			prev &= 0xff00ffff;
			prev |= data >> 8;
			break;
		default:
			break;
	}
	return prev;
}

WRITE32_MEMBER(gba_state::gba_pram_w)
{
	m_gba_pram[offset] = COMBINE_DATA32_16(m_gba_pram[offset], data, mem_mask);
}

WRITE32_MEMBER(gba_state::gba_vram_w)
{
	m_gba_vram[offset] = COMBINE_DATA32_16(m_gba_vram[offset], data, mem_mask);
}

WRITE32_MEMBER(gba_state::gba_oam_w)
{
	m_gba_oam[offset] = COMBINE_DATA32_16(m_gba_oam[offset], data, mem_mask);
}

READ32_MEMBER(gba_state::gba_bios_r)
{
	UINT32 *rom = m_region_maincpu;
=======
READ32_MEMBER(gba_state::gba_bios_r)
{
	uint32_t *rom = m_region_maincpu;
>>>>>>> upstream/master
	if (m_bios_hack->read())
	{
		// partially patch out logo and checksum checks
		// (useful to run some protos + to test homebrew)
		if (ACCESSING_BITS_0_15 && (offset == 0x6fc/4))
			return 0;
	}

<<<<<<< HEAD
	if (m_bios_protected != 0)
		offset = (m_bios_last_address + 8) / 4;
=======
	if (m_maincpu->pc() >= 0x4000)
	{
		//printf("GBA protection: blocking PC=%x\n", m_maincpu->pc());
		return 0;
	}
>>>>>>> upstream/master

	return rom[offset & 0x3fff];
}

READ32_MEMBER(gba_state::gba_10000000_r)
{
<<<<<<< HEAD
	UINT32 data;
	UINT32 pc = m_maincpu->state_int(ARM7_PC);
	UINT32 cpsr = m_maincpu->state_int(ARM7_CPSR);
=======
	uint32_t data;
	uint32_t pc = m_maincpu->state_int(ARM7_PC);
	uint32_t cpsr = m_maincpu->state_int(ARM7_CPSR);
>>>>>>> upstream/master
	if (T_IS_SET( cpsr))
	{
		data = space.read_dword(pc + 8);
	}
	else
	{
<<<<<<< HEAD
		UINT16 insn = space.read_word(pc + 4);
=======
		uint16_t insn = space.read_word(pc + 4);
>>>>>>> upstream/master
		data = (insn << 16) | (insn << 0);
	}
	logerror("%s: unmapped program memory read from %08X = %08X & %08X\n", machine().describe_context( ), 0x10000000 + (offset << 2), data, mem_mask);
	return data;
}

<<<<<<< HEAD
=======
WRITE_LINE_MEMBER(gba_state::int_hblank_callback)
{
	request_irq(INT_HBL);
}

WRITE_LINE_MEMBER(gba_state::int_vblank_callback)
{
	request_irq(INT_VBL);
}

WRITE_LINE_MEMBER(gba_state::int_vcount_callback)
{
	request_irq(INT_VCNT);
}

WRITE_LINE_MEMBER(gba_state::dma_hblank_callback)
{
	for (int ch = 0; ch < 4; ch++)
	{
		int ctrl = DMACNT_H(ch);

		if ((ctrl & 0x8000) && ((ctrl & 0x3000) == 0x2000))
			dma_exec(ch);
	}
}

WRITE_LINE_MEMBER(gba_state::dma_vblank_callback)
{
	for (int ch = 0; ch < 4; ch++)
	{
		int ctrl = DMACNT_H(ch);

		if ((ctrl & 0x8000) && ((ctrl & 0x3000) == 0x1000))
			dma_exec(ch);
	}
}

>>>>>>> upstream/master
static ADDRESS_MAP_START( gba_map, AS_PROGRAM, 32, gba_state )
	ADDRESS_MAP_UNMAP_HIGH // for "Fruit Mura no Doubutsu Tachi" and "Classic NES Series"
	AM_RANGE(0x00000000, 0x00003fff) AM_ROM AM_READ(gba_bios_r)
	AM_RANGE(0x02000000, 0x0203ffff) AM_RAM AM_MIRROR(0xfc0000)
	AM_RANGE(0x03000000, 0x03007fff) AM_RAM AM_MIRROR(0xff8000)
<<<<<<< HEAD
	AM_RANGE(0x04000000, 0x040003ff) AM_READWRITE(gba_io_r, gba_io_w)
	AM_RANGE(0x05000000, 0x050003ff) AM_RAM_WRITE(gba_pram_w) AM_SHARE("gba_pram")  // Palette RAM
	AM_RANGE(0x06000000, 0x06017fff) AM_RAM_WRITE(gba_vram_w) AM_SHARE("gba_vram")  // VRAM
	AM_RANGE(0x07000000, 0x070003ff) AM_RAM_WRITE(gba_oam_w) AM_SHARE("gba_oam")    // OAM
=======
	AM_RANGE(0x04000000, 0x0400005f) AM_DEVREADWRITE("lcd", gba_lcd_device, video_r, video_w)
	AM_RANGE(0x04000060, 0x040003ff) AM_READWRITE(gba_io_r, gba_io_w)
	AM_RANGE(0x04000400, 0x04ffffff) AM_NOP                                         // Not used
	AM_RANGE(0x05000000, 0x050003ff) AM_DEVREADWRITE("lcd", gba_lcd_device, gba_pram_r, gba_pram_w)  // Palette RAM
	AM_RANGE(0x06000000, 0x06017fff) AM_DEVREADWRITE("lcd", gba_lcd_device, gba_vram_r, gba_vram_w)  // VRAM
	AM_RANGE(0x07000000, 0x070003ff) AM_DEVREADWRITE("lcd", gba_lcd_device, gba_oam_r, gba_oam_w)    // OAM
	AM_RANGE(0x07000400, 0x07ffffff) AM_NOP                                         // Not used
>>>>>>> upstream/master
	//AM_RANGE(0x08000000, 0x0cffffff)  // cart ROM + mirrors, mapped here at machine_start if a cart is present
	AM_RANGE(0x10000000, 0xffffffff) AM_READ(gba_10000000_r) // for "Justice League Chronicles" (game bug)
ADDRESS_MAP_END

static INPUT_PORTS_START( gbadv )
	PORT_START("INPUTS")
<<<<<<< HEAD
	PORT_BIT( 0xfc00, IP_ACTIVE_HIGH, IPT_BUTTON5) PORT_UNUSED
=======
	PORT_BIT( 0xfc00, IP_ACTIVE_HIGH, IPT_UNUSED)
>>>>>>> upstream/master
	PORT_BIT( 0x0200, IP_ACTIVE_LOW, IPT_BUTTON3 ) PORT_NAME("P1 L") PORT_PLAYER(1) // L
	PORT_BIT( 0x0100, IP_ACTIVE_LOW, IPT_BUTTON4 ) PORT_NAME("P1 R") PORT_PLAYER(1) // R
	PORT_BIT( 0x0080, IP_ACTIVE_LOW, IPT_JOYSTICK_DOWN ) PORT_PLAYER(1)
	PORT_BIT( 0x0040, IP_ACTIVE_LOW, IPT_JOYSTICK_UP ) PORT_PLAYER(1)
	PORT_BIT( 0x0020, IP_ACTIVE_LOW, IPT_JOYSTICK_LEFT ) PORT_PLAYER(1)
	PORT_BIT( 0x0010, IP_ACTIVE_LOW, IPT_JOYSTICK_RIGHT ) PORT_PLAYER(1)
	PORT_BIT( 0x0008, IP_ACTIVE_LOW, IPT_START ) PORT_PLAYER(1) // START
	PORT_BIT( 0x0004, IP_ACTIVE_LOW, IPT_SELECT ) PORT_PLAYER(1)    // SELECT
	PORT_BIT( 0x0002, IP_ACTIVE_LOW, IPT_BUTTON1 ) PORT_NAME("B") PORT_PLAYER(1)    // B
	PORT_BIT( 0x0001, IP_ACTIVE_LOW, IPT_BUTTON2 ) PORT_NAME("A") PORT_PLAYER(1)    // A

	PORT_START("SKIP_CHECK")
	PORT_CONFNAME( 0x01, 0x00, "[HACK] Skip BIOS Logo check" )
	PORT_CONFSETTING(    0x00, DEF_STR( Off ) )
	PORT_CONFSETTING(    0x01, DEF_STR( On ) )
INPUT_PORTS_END


<<<<<<< HEAD
TIMER_CALLBACK_MEMBER(gba_state::perform_hbl)
{
	int ch, ctrl;
	int scanline = machine().first_screen()->vpos();

	// draw only visible scanlines
	if (scanline < 160)
	{
		draw_scanline(scanline);

		for (ch = 0; ch < 4; ch++)
		{
			ctrl = m_dma_regs[(ch*3)+2]>>16;

			// HBL-triggered DMA?
			if ((ctrl & 0x8000) && ((ctrl & 0x3000) == 0x2000))
			{
				dma_exec(ch);
			}
		}
	}

	if ((m_DISPSTAT & DISPSTAT_HBL_IRQ_EN ) != 0)
	{
		request_irq(INT_HBL);
	}

	m_DISPSTAT |= DISPSTAT_HBL;

	m_hbl_timer->adjust(attotime::never);
}

TIMER_CALLBACK_MEMBER(gba_state::perform_scan)
{
	int scanline;

	// clear hblank and raster IRQ flags
	m_DISPSTAT &= ~(DISPSTAT_HBL|DISPSTAT_VCNT);

	scanline = machine().first_screen()->vpos();

	// VBL is set for scanlines 160 through 226 (but not 227, which is the last line)
	if (scanline >= 160 && scanline < 227)
	{
		m_DISPSTAT |= DISPSTAT_VBL;

		// VBL IRQ and DMA on line 160
		if (scanline == 160)
		{
			int ch, ctrl;

			if (m_DISPSTAT & DISPSTAT_VBL_IRQ_EN)
			{
				request_irq(INT_VBL);
			}

			for (ch = 0; ch < 4; ch++)
			{
				ctrl = m_dma_regs[(ch*3)+2]>>16;

				// VBL-triggered DMA?
				if ((ctrl & 0x8000) && ((ctrl & 0x3000) == 0x1000))
				{
					dma_exec(ch);
				}
			}
		}
	}
	else
	{
		m_DISPSTAT &= ~DISPSTAT_VBL;
	}

	// handle VCNT match interrupt/flag
	if (scanline == ((m_DISPSTAT >> 8) & 0xff))
	{
		m_DISPSTAT |= DISPSTAT_VCNT;
		if (m_DISPSTAT & DISPSTAT_VCNT_IRQ_EN)
		{
			request_irq(INT_VCNT);
		}
	}

	m_hbl_timer->adjust(machine().first_screen()->time_until_pos(scanline, 240));
	m_scan_timer->adjust(machine().first_screen()->time_until_pos(( scanline + 1 ) % 228, 0));
}

void gba_state::machine_reset()
{
	//memset(this, 0, sizeof(this));
	m_SOUNDBIAS = 0x0200;
	m_SIOMULTI0 = 0xffff;
	m_SIOMULTI1 = 0xffff;
	m_SIOMULTI2 = 0xffff;
	m_SIOMULTI3 = 0xffff;
	m_KEYCNT = 0x03ff;
	m_RCNT = 0x8000;
	m_JOYSTAT = 0x0002;
	m_gfxBG2Changed = 0;
	m_gfxBG3Changed = 0;
	m_gfxBG2X = 0;
	m_gfxBG2Y = 0;
	m_gfxBG3X = 0;
	m_gfxBG3Y = 0;

	m_windowOn = 0;
	m_fxOn = 0;

	m_bios_protected = 0;

	m_scan_timer->adjust(machine().first_screen()->time_until_pos(0, 0));
	m_hbl_timer->adjust(attotime::never);
=======
void gba_state::machine_reset()
{
	memset(m_regs, 0, sizeof(m_regs));

	SOUNDBIAS_SET(0x0200);
	SIOMULTI0_SET(0xffff);
	SIOMULTI1_SET(0xffff);
	SIOMULTI2_SET(0xffff);
	SIOMULTI3_SET(0xffff);
	KEYCNT_SET(0x03ff);
	RCNT_SET(0x8000);
	JOYSTAT_SET(0x0002);

>>>>>>> upstream/master
	m_dma_timer[0]->adjust(attotime::never);
	m_dma_timer[1]->adjust(attotime::never, 1);
	m_dma_timer[2]->adjust(attotime::never, 2);
	m_dma_timer[3]->adjust(attotime::never, 3);

	m_fifo_a_ptr = m_fifo_b_ptr = 17;   // indicate empty
	m_fifo_a_in = m_fifo_b_in = 17;

	// and clear the DACs
<<<<<<< HEAD
	m_ladac->write_signed8(0x80);
	m_radac->write_signed8(0x80);
	m_lbdac->write_signed8(0x80);
	m_rbdac->write_signed8(0x80);
=======
	m_ldaca->write(0);
	m_rdaca->write(0);
	m_ldacb->write(0);
	m_rdacb->write(0);
>>>>>>> upstream/master
}

void gba_state::machine_start()
{
<<<<<<< HEAD
	/* create a timer to fire scanline functions */
	m_scan_timer = machine().scheduler().timer_alloc(timer_expired_delegate(FUNC(gba_state::perform_scan),this));
	m_hbl_timer = machine().scheduler().timer_alloc(timer_expired_delegate(FUNC(gba_state::perform_hbl),this));
	m_scan_timer->adjust(machine().first_screen()->time_until_pos(0, 0));

=======
>>>>>>> upstream/master
	/* and one for each DMA channel */
	m_dma_timer[0] = machine().scheduler().timer_alloc(timer_expired_delegate(FUNC(gba_state::dma_complete),this));
	m_dma_timer[1] = machine().scheduler().timer_alloc(timer_expired_delegate(FUNC(gba_state::dma_complete),this));
	m_dma_timer[2] = machine().scheduler().timer_alloc(timer_expired_delegate(FUNC(gba_state::dma_complete),this));
	m_dma_timer[3] = machine().scheduler().timer_alloc(timer_expired_delegate(FUNC(gba_state::dma_complete),this));
	m_dma_timer[0]->adjust(attotime::never);
	m_dma_timer[1]->adjust(attotime::never, 1);
	m_dma_timer[2]->adjust(attotime::never, 2);
	m_dma_timer[3]->adjust(attotime::never, 3);

	/* also one for each timer (heh) */
	m_tmr_timer[0] = machine().scheduler().timer_alloc(timer_expired_delegate(FUNC(gba_state::timer_expire),this));
	m_tmr_timer[1] = machine().scheduler().timer_alloc(timer_expired_delegate(FUNC(gba_state::timer_expire),this));
	m_tmr_timer[2] = machine().scheduler().timer_alloc(timer_expired_delegate(FUNC(gba_state::timer_expire),this));
	m_tmr_timer[3] = machine().scheduler().timer_alloc(timer_expired_delegate(FUNC(gba_state::timer_expire),this));
	m_tmr_timer[0]->adjust(attotime::never);
	m_tmr_timer[1]->adjust(attotime::never, 1);
	m_tmr_timer[2]->adjust(attotime::never, 2);
	m_tmr_timer[3]->adjust(attotime::never, 3);

	/* and an IRQ handling timer */
	m_irq_timer = machine().scheduler().timer_alloc(timer_expired_delegate(FUNC(gba_state::handle_irq),this));
	m_irq_timer->adjust(attotime::never);

	// install the cart ROM & SRAM into the address map, if present
	if (m_cart->exists())
	{
<<<<<<< HEAD
		m_maincpu->space(AS_PROGRAM).install_read_bank(0x08000000, 0x09ffffff, 0, 0, "rom1");
		m_maincpu->space(AS_PROGRAM).install_read_bank(0x0a000000, 0x0bffffff, 0, 0, "rom2");
		m_maincpu->space(AS_PROGRAM).install_read_bank(0x0c000000, 0x0cffffff, 0, 0, "rom3");
=======
		m_maincpu->space(AS_PROGRAM).install_read_bank(0x08000000, 0x09ffffff, "rom1");
		m_maincpu->space(AS_PROGRAM).install_read_bank(0x0a000000, 0x0bffffff, "rom2");
		m_maincpu->space(AS_PROGRAM).install_read_bank(0x0c000000, 0x0cffffff, "rom3");
>>>>>>> upstream/master

		std::string region_tag;
		memory_region *cart_rom = memregion(region_tag.assign(m_cart->tag()).append(GBASLOT_ROM_REGION_TAG).c_str());

		// install ROM accesses
		membank("rom1")->set_base(cart_rom->base());
		membank("rom2")->set_base(cart_rom->base());
		membank("rom3")->set_base(cart_rom->base());

<<<<<<< HEAD
=======
		m_maincpu->space(AS_PROGRAM).install_read_handler(0x80000c4, 0x80000cb, read32_delegate(FUNC(gba_cart_slot_device::read_gpio),(gba_cart_slot_device*)m_cart));
		m_maincpu->space(AS_PROGRAM).install_write_handler(0x80000c4, 0x80000cb, write32_delegate(FUNC(gba_cart_slot_device::write_gpio),(gba_cart_slot_device*)m_cart));

>>>>>>> upstream/master
		// add nvram to save state
		m_cart->save_nvram();

		// install the cart NVRAM handlers if necessary
<<<<<<< HEAD
		if (m_cart->get_type() == GBA_SRAM)
=======
		if (m_cart->get_type() == GBA_SRAM || m_cart->get_type() == GBA_DRILLDOZ || m_cart->get_type() == GBA_WARIOTWS)
>>>>>>> upstream/master
		{
			m_maincpu->space(AS_PROGRAM).install_read_handler(0xe000000, 0xe00ffff, read32_delegate(FUNC(gba_cart_slot_device::read_ram),(gba_cart_slot_device*)m_cart));
			m_maincpu->space(AS_PROGRAM).install_write_handler(0xe000000, 0xe00ffff, write32_delegate(FUNC(gba_cart_slot_device::write_ram),(gba_cart_slot_device*)m_cart));
		}
<<<<<<< HEAD
		if (m_cart->get_type() == GBA_EEPROM || m_cart->get_type() == GBA_EEPROM4 || m_cart->get_type() == GBA_EEPROM64)
=======
		if (m_cart->get_type() == GBA_EEPROM || m_cart->get_type() == GBA_EEPROM4 || m_cart->get_type() == GBA_EEPROM64 || m_cart->get_type() == GBA_BOKTAI)
>>>>>>> upstream/master
		{
			// for games larger than 16MB the actual range is smaller but read_ram/write_ram handles that!
			m_maincpu->space(AS_PROGRAM).install_read_handler(0xd000000, 0xdffffff, read32_delegate(FUNC(gba_cart_slot_device::read_ram),(gba_cart_slot_device*)m_cart));
			m_maincpu->space(AS_PROGRAM).install_write_handler(0xd000000, 0xdffffff, write32_delegate(FUNC(gba_cart_slot_device::write_ram),(gba_cart_slot_device*)m_cart));
		}
<<<<<<< HEAD
		// merge the two flash and mask accesses in read_ram?!?
		if (m_cart->get_type() == GBA_FLASH || m_cart->get_type() == GBA_FLASH512)
=======
		if (m_cart->get_type() == GBA_YOSHIUG)
		{
			// EEPROM
			m_maincpu->space(AS_PROGRAM).install_read_handler(0xd000000, 0xdffffff, read32_delegate(FUNC(gba_cart_slot_device::read_ram),(gba_cart_slot_device*)m_cart));
			m_maincpu->space(AS_PROGRAM).install_write_handler(0xd000000, 0xdffffff, write32_delegate(FUNC(gba_cart_slot_device::write_ram),(gba_cart_slot_device*)m_cart));
			// Tilt Sensor
			m_maincpu->space(AS_PROGRAM).install_read_handler(0xe008000, 0xe0085ff, read32_delegate(FUNC(gba_cart_slot_device::read_tilt),(gba_cart_slot_device*)m_cart));
			m_maincpu->space(AS_PROGRAM).install_write_handler(0xe008000, 0xe0085ff, write32_delegate(FUNC(gba_cart_slot_device::write_tilt),(gba_cart_slot_device*)m_cart));
		}
		// merge the two flash and mask accesses in read_ram?!?
		if (m_cart->get_type() == GBA_FLASH || m_cart->get_type() == GBA_FLASH512 || m_cart->get_type() == GBA_FLASH_RTC)
>>>>>>> upstream/master
		{
			m_maincpu->space(AS_PROGRAM).install_read_handler(0xe000000, 0xe00ffff, read32_delegate(FUNC(gba_cart_slot_device::read_ram),(gba_cart_slot_device*)m_cart));
			m_maincpu->space(AS_PROGRAM).install_write_handler(0xe000000, 0xe00ffff, write32_delegate(FUNC(gba_cart_slot_device::write_ram),(gba_cart_slot_device*)m_cart));
		}
<<<<<<< HEAD
		if (m_cart->get_type() == GBA_FLASH1M)
=======
		if (m_cart->get_type() == GBA_FLASH1M || m_cart->get_type() == GBA_FLASH1M_RTC)
>>>>>>> upstream/master
		{
			m_maincpu->space(AS_PROGRAM).install_read_handler(0xe000000, 0xe01ffff, read32_delegate(FUNC(gba_cart_slot_device::read_ram),(gba_cart_slot_device*)m_cart));
			m_maincpu->space(AS_PROGRAM).install_write_handler(0xe000000, 0xe01ffff, write32_delegate(FUNC(gba_cart_slot_device::write_ram),(gba_cart_slot_device*)m_cart));
		}
<<<<<<< HEAD
	}

	save_item(NAME(m_DISPSTAT));
	save_item(NAME(m_BG2X));
	save_item(NAME(m_BG2Y));
	save_item(NAME(m_BG3X));
	save_item(NAME(m_BG3Y));
	save_item(NAME(m_DISPCNT));
	save_item(NAME(m_GRNSWAP));
	save_item(NAME(m_BG0CNT));
	save_item(NAME(m_BG1CNT));
	save_item(NAME(m_BG2CNT));
	save_item(NAME(m_BG3CNT));
	save_item(NAME(m_BG0HOFS));
	save_item(NAME(m_BG0VOFS));
	save_item(NAME(m_BG1HOFS));
	save_item(NAME(m_BG1VOFS));
	save_item(NAME(m_BG2HOFS));
	save_item(NAME(m_BG2VOFS));
	save_item(NAME(m_BG3HOFS));
	save_item(NAME(m_BG3VOFS));
	save_item(NAME(m_BG2PA));
	save_item(NAME(m_BG2PB));
	save_item(NAME(m_BG2PC));
	save_item(NAME(m_BG2PD));
	save_item(NAME(m_BG3PA));
	save_item(NAME(m_BG3PB));
	save_item(NAME(m_BG3PC));
	save_item(NAME(m_BG3PD));
	save_item(NAME(m_WIN0H));
	save_item(NAME(m_WIN1H));
	save_item(NAME(m_WIN0V));
	save_item(NAME(m_WIN1V));
	save_item(NAME(m_WININ));
	save_item(NAME(m_WINOUT));
	save_item(NAME(m_MOSAIC));
	save_item(NAME(m_BLDCNT));
	save_item(NAME(m_BLDALPHA));
	save_item(NAME(m_BLDY));
	save_item(NAME(m_SOUNDCNT_X));
	save_item(NAME(m_SOUNDCNT_H));
	save_item(NAME(m_SOUNDBIAS));
	save_item(NAME(m_SIOMULTI0));
	save_item(NAME(m_SIOMULTI1));
	save_item(NAME(m_SIOMULTI2));
	save_item(NAME(m_SIOMULTI3));
	save_item(NAME(m_SIOCNT));
	save_item(NAME(m_SIODATA8));
	save_item(NAME(m_KEYCNT));
	save_item(NAME(m_RCNT));
	save_item(NAME(m_JOYCNT));
	save_item(NAME(m_JOY_RECV));
	save_item(NAME(m_JOY_TRANS));
	save_item(NAME(m_JOYSTAT));
	save_item(NAME(m_IR));
	save_item(NAME(m_IE));
	save_item(NAME(m_IF));
	save_item(NAME(m_IME));
	save_item(NAME(m_WAITCNT));
	save_item(NAME(m_POSTFLG));
	save_item(NAME(m_HALTCNT));
	save_item(NAME(m_windowOn));
	save_item(NAME(m_fxOn));
	save_item(NAME(m_gfxBG2Changed));
	save_item(NAME(m_gfxBG3Changed));
	save_item(NAME(m_gfxBG2X));
	save_item(NAME(m_gfxBG2Y));
	save_item(NAME(m_gfxBG3X));
	save_item(NAME(m_gfxBG3Y));
	save_item(NAME(m_dma_regs));
	save_item(NAME(m_dma_src));
	save_item(NAME(m_dma_dst));
	save_item(NAME(m_dma_cnt));
	save_item(NAME(m_dma_srcadd));
	save_item(NAME(m_dma_dstadd));
=======
		if (m_cart->get_type() == GBA_3DMATRIX)
		{
			m_maincpu->space(AS_PROGRAM).install_write_handler(0x08800000, 0x088001ff, write32_delegate(FUNC(gba_cart_slot_device::write_mapper),(gba_cart_slot_device*)m_cart));
			memory_region *cart_romhlp = memregion(region_tag.assign(m_cart->tag()).append(GBAHELP_ROM_REGION_TAG).c_str());
			membank("rom1")->set_base(cart_romhlp->base());
		}

	}

	save_item(NAME(m_regs));
	save_item(NAME(m_dma_src));
	save_item(NAME(m_dma_dst));
	save_item(NAME(m_dma_cnt));
>>>>>>> upstream/master
	save_item(NAME(m_timer_regs));
	save_item(NAME(m_timer_reload));
	save_item(NAME(m_timer_recalc));
	save_item(NAME(m_timer_hz));
	save_item(NAME(m_fifo_a_ptr));
	save_item(NAME(m_fifo_b_ptr));
	save_item(NAME(m_fifo_a_in));
	save_item(NAME(m_fifo_b_in));
	save_item(NAME(m_fifo_a));
	save_item(NAME(m_fifo_b));
<<<<<<< HEAD
	save_item(NAME(m_xferscan));
	save_item(NAME(m_bios_last_address));
	save_item(NAME(m_bios_protected));
}



static SLOT_INTERFACE_START(gba_cart)
	SLOT_INTERFACE_INTERNAL("gba_rom",         GBA_ROM_STD)
	SLOT_INTERFACE_INTERNAL("gba_sram",        GBA_ROM_SRAM)
	SLOT_INTERFACE_INTERNAL("gba_eeprom",      GBA_ROM_EEPROM)
	SLOT_INTERFACE_INTERNAL("gba_eeprom_4k",   GBA_ROM_EEPROM)
	SLOT_INTERFACE_INTERNAL("gba_eeprom_64k",  GBA_ROM_EEPROM64)
	SLOT_INTERFACE_INTERNAL("gba_flash",       GBA_ROM_FLASH)   // Panasonic
	SLOT_INTERFACE_INTERNAL("gba_flash_512",   GBA_ROM_FLASH)   // Panasonic
	SLOT_INTERFACE_INTERNAL("gba_flash_1m",    GBA_ROM_FLASH1M) // Sanyo
SLOT_INTERFACE_END


static MACHINE_CONFIG_START( gbadv, gba_state )

	MCFG_CPU_ADD("maincpu", ARM7, 16777216)
	MCFG_CPU_PROGRAM_MAP(gba_map)

	MCFG_SCREEN_ADD("gbalcd", RASTER)   // htot hst vwid vtot vst vis
	MCFG_SCREEN_RAW_PARAMS(16777216/4, 308, 0,  240, 228, 0,  160)
	MCFG_SCREEN_UPDATE_DRIVER(gba_state, screen_update)
	MCFG_SCREEN_PALETTE("palette")

	MCFG_DEFAULT_LAYOUT(layout_lcd)
	MCFG_PALETTE_ADD("palette", 32768)
	MCFG_PALETTE_INIT_OWNER(gba_state, gba)

	MCFG_SPEAKER_STANDARD_STEREO("spkleft", "spkright")
	MCFG_SOUND_ADD("custom", GAMEBOY, 0)
	MCFG_SOUND_ROUTE(0, "spkleft", 0.50)
	MCFG_SOUND_ROUTE(1, "spkright", 0.50)
	MCFG_SOUND_ADD("direct_a_left", DAC, 0)         // GBA direct sound A left
	MCFG_SOUND_ROUTE(ALL_OUTPUTS, "spkleft", 0.50)
	MCFG_SOUND_ADD("direct_a_right", DAC, 0)        // GBA direct sound A right
	MCFG_SOUND_ROUTE(ALL_OUTPUTS, "spkright", 0.50)
	MCFG_SOUND_ADD("direct_b_left", DAC, 0)         // GBA direct sound B left
	MCFG_SOUND_ROUTE(ALL_OUTPUTS, "spkleft", 0.50)
	MCFG_SOUND_ADD("direct_b_right", DAC, 0)        // GBA direct sound B right
	MCFG_SOUND_ROUTE(ALL_OUTPUTS, "spkright", 0.50)

	MCFG_GBA_CARTRIDGE_ADD("cartslot", gba_cart, NULL)
=======
}


static SLOT_INTERFACE_START(gba_cart)
	SLOT_INTERFACE_INTERNAL("gba_rom",          GBA_ROM_STD)
	SLOT_INTERFACE_INTERNAL("gba_sram",         GBA_ROM_SRAM)
	SLOT_INTERFACE_INTERNAL("gba_drilldoz",     GBA_ROM_DRILLDOZ)   // Rumble output unemulated
	SLOT_INTERFACE_INTERNAL("gba_wariotws",     GBA_ROM_WARIOTWS)   // Rumble output unemulated
	SLOT_INTERFACE_INTERNAL("gba_eeprom",       GBA_ROM_EEPROM)
	SLOT_INTERFACE_INTERNAL("gba_eeprom_4k",    GBA_ROM_EEPROM)
	SLOT_INTERFACE_INTERNAL("gba_yoshiug",      GBA_ROM_YOSHIUG)
	SLOT_INTERFACE_INTERNAL("gba_eeprom_64k",   GBA_ROM_EEPROM64)
	SLOT_INTERFACE_INTERNAL("gba_boktai",       GBA_ROM_BOKTAI)
	SLOT_INTERFACE_INTERNAL("gba_flash",        GBA_ROM_FLASH)   // Panasonic
	SLOT_INTERFACE_INTERNAL("gba_flash_rtc",    GBA_ROM_FLASH_RTC)   // Panasonic
	SLOT_INTERFACE_INTERNAL("gba_flash_512",    GBA_ROM_FLASH)   // Panasonic
	SLOT_INTERFACE_INTERNAL("gba_flash_1m",     GBA_ROM_FLASH1M) // Sanyo
	SLOT_INTERFACE_INTERNAL("gba_flash_1m_rtc", GBA_ROM_FLASH1M_RTC) // Sanyo
	SLOT_INTERFACE_INTERNAL("gba_3dmatrix",     GBA_ROM_3DMATRIX)
SLOT_INTERFACE_END


static MACHINE_CONFIG_START( gbadv )

	MCFG_CPU_ADD("maincpu", ARM7, XTAL_16_777216MHz)
	MCFG_CPU_PROGRAM_MAP(gba_map)

	MCFG_GBA_LCD_ADD("lcd")
	MCFG_GBA_LCD_INT_HBLANK(WRITELINE(gba_state, int_hblank_callback))
	MCFG_GBA_LCD_INT_VBLANK(WRITELINE(gba_state, int_vblank_callback))
	MCFG_GBA_LCD_INT_VCOUNT(WRITELINE(gba_state, int_vcount_callback))
	MCFG_GBA_LCD_DMA_HBLANK(WRITELINE(gba_state, dma_hblank_callback))
	MCFG_GBA_LCD_DMA_VBLANK(WRITELINE(gba_state, dma_vblank_callback))

	MCFG_SPEAKER_STANDARD_STEREO("lspeaker", "rspeaker")
	MCFG_SOUND_ADD("custom", CGB04_APU, XTAL_16_777216MHz/4)
	MCFG_SOUND_ROUTE(0, "lspeaker", 0.5)
	MCFG_SOUND_ROUTE(1, "rspeaker", 0.5)

	MCFG_SOUND_ADD("ldaca", DAC_8BIT_R2R_TWOS_COMPLEMENT, 0) MCFG_SOUND_ROUTE(ALL_OUTPUTS, "lspeaker", 0.5) // unknown DAC
	MCFG_SOUND_ADD("rdaca", DAC_8BIT_R2R_TWOS_COMPLEMENT, 0) MCFG_SOUND_ROUTE(ALL_OUTPUTS, "rspeaker", 0.5) // unknown DAC
	MCFG_SOUND_ADD("ldacb", DAC_8BIT_R2R_TWOS_COMPLEMENT, 0) MCFG_SOUND_ROUTE(ALL_OUTPUTS, "lspeaker", 0.5) // unknown DAC
	MCFG_SOUND_ADD("rdacb", DAC_8BIT_R2R_TWOS_COMPLEMENT, 0) MCFG_SOUND_ROUTE(ALL_OUTPUTS, "rspeaker", 0.5) // unknown DAC
	MCFG_DEVICE_ADD("vref", VOLTAGE_REGULATOR, 0) MCFG_VOLTAGE_REGULATOR_OUTPUT(5.0)
	MCFG_SOUND_ROUTE_EX(0, "ldaca", 1.0, DAC_VREF_POS_INPUT) MCFG_SOUND_ROUTE_EX(0, "ldaca", -1.0, DAC_VREF_NEG_INPUT)
	MCFG_SOUND_ROUTE_EX(0, "rdaca", 1.0, DAC_VREF_POS_INPUT) MCFG_SOUND_ROUTE_EX(0, "rdaca", -1.0, DAC_VREF_NEG_INPUT)
	MCFG_SOUND_ROUTE_EX(0, "ldacb", 1.0, DAC_VREF_POS_INPUT) MCFG_SOUND_ROUTE_EX(0, "ldacb", -1.0, DAC_VREF_NEG_INPUT)
	MCFG_SOUND_ROUTE_EX(0, "rdacb", 1.0, DAC_VREF_POS_INPUT) MCFG_SOUND_ROUTE_EX(0, "rdacb", -1.0, DAC_VREF_NEG_INPUT)

	MCFG_GBA_CARTRIDGE_ADD("cartslot", gba_cart, nullptr)
>>>>>>> upstream/master
	MCFG_SOFTWARE_LIST_ADD("cart_list","gba")
MACHINE_CONFIG_END


<<<<<<< HEAD

=======
>>>>>>> upstream/master
ROM_START( gba )
	ROM_REGION( 0x4000, "maincpu", 0 )
	ROM_LOAD( "gba.bin", 0x000000, 0x004000, CRC(81977335) SHA1(300c20df6731a33952ded8c436f7f186d25d3492) )
ROM_END


<<<<<<< HEAD

// this emulates the GBA's hardware protection: the BIOS returns only zeros when the PC is not in it,
// and some games verify that as a protection check (notably Metroid Fusion)
DIRECT_UPDATE_MEMBER(gba_state::gba_direct)
{
	if (address > 0x4000)
	{
		m_bios_protected = 1;
	}
	else
	{
		m_bios_protected = 0;
		m_bios_last_address = address;
	}
	return address;
}


DRIVER_INIT_MEMBER(gba_state,gbadv)
{
	m_maincpu->space(AS_PROGRAM).set_direct_update_handler(direct_update_delegate(FUNC(gba_state::gba_direct), this));
}


/*    YEAR  NAME PARENT COMPAT MACHINE INPUT   INIT   COMPANY     FULLNAME */
CONS(2001, gba, 0,     0,     gbadv,  gbadv, gba_state,  gbadv, "Nintendo", "Game Boy Advance", MACHINE_SUPPORTS_SAVE | MACHINE_IMPERFECT_GRAPHICS | MACHINE_IMPERFECT_SOUND)
=======
//   YEAR  NAME PARENT COMPAT MACHINE INPUT  STATE      INIT  COMPANY     FULLNAME            FLAGS
CONS(2001, gba, 0,     0,     gbadv,  gbadv, gba_state, 0,    "Nintendo", "Game Boy Advance", MACHINE_SUPPORTS_SAVE | MACHINE_IMPERFECT_GRAPHICS | MACHINE_IMPERFECT_SOUND)
>>>>>>> upstream/master
