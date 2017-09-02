// license:BSD-3-Clause
<<<<<<< HEAD
// copyright-holders:Couriersud
/**********************************************************************************************

     TMS6100 simulator

     Written for MAME by Couriersud

     Todo:
        - implement CS
        - implement 4 bit mode (mask programmed)
        - implement chip addressing (0-15 mask programmed)

     TMS6100:

                 +-----------------+
       VDD       |  1           28 |  NC
       NC        |  2           27 |  NC
       DATA/ADD1 |  3           26 |  NC
       DATA/ADD2 |  4           25 |  NC
       DATA/ADD4 |  5           24 |  NC
       DATA/ADD8 |  6           23 |  NC
       CLK       |  7           22 |  NC
       NC        |  8           21 |  NC
       NC        |  9           20 |  NC
       M0        | 10           19 |  NC
       M1        | 11           18 |  NC
       NC        | 12           17 |  NC
       /CS       | 13           16 |  NC
       VSS       | 14           15 |  NC
                 +-----------------+

     TMS6125:

                 +---------+
       DATA/ADD1 | 1    16 |  NC
       DATA/ADD2 | 2    15 |  NC
       DATA/ADD4 | 3    14 |  NC
       DATA/ADD8 | 4    13 |  NC
       CLK       | 5    12 |  VDD
       NC        | 6    11 |  /CS
       NC        | 7    10 |  M1
       M0        | 8     9 |  VSS
                 +---------+

    M58819 (from radarscope schematics):

                 +-----------------+
       AD0       |  1           40 |  AD1
       GND       |  2           39 |  AD2
       -5V       |  3           38 |  AD3
       A0        |  4           37 |  AD4
       NC        |  5           36 |  AD5
       NC        |  6           35 |  AD6
       A1        |  7           34 |  AD7
       A2        |  8           33 |  AD8
       A3        |  9           32 |  AD9
       CLK       | 10           31 |  AD10
       NC        | 11           30 |  AD11
       -5V       | 12           29 |  AD12
       C0        | 13           28 |  NC
       C1        | 14           27 |  NC
       NC        | 15           26 |  I7
       NC        | 16           25 |  NC
       +5V       | 17           24 |  I6
       I0        | 18           23 |  I5
       I1        | 19           22 |  I4
       I2        | 20           21 |  I3
                 +-----------------+

    The M58819 is used as an interface to external speech eproms.
    NC pins may have a function, although they are not connected in
    radarscope.
=======
// copyright-holders:hap, Couriersud
/**********************************************************************************************

    Texas Instruments TMS6100 Voice Synthesis Memory (VSM)

    References:
    - TMS 6100 Voice Synthesis Memory Data Manual
    - TMS 6125 Voice Synthesis Memory Data Manual
    - Speak & Spell patent US4189779 for low-level documentation
    - 1982 Mitsubishi Data Book (M58819S section)

    TODO:
    - implement clock pin(CLK) properly, xtal/timer
    - command processing timing is not accurate, on the real chip it will take a few microseconds
    - current implementation does not regard multi-chip configuration and pretends it is 1 chip,
      this will work fine under normal circumstances since CS would be disabled on invalid address
    - implement chip addressing (0-15 mask programmed, see above)
    - M58819S pins SL(PROM expansion input), POC(reset)
>>>>>>> upstream/master

***********************************************************************************************/

#include "emu.h"
#include "tms6100.h"

<<<<<<< HEAD
#define VERBOSE     (0)

#if VERBOSE
#define LOG(x)      logerror x
#else
#define LOG(x)
#endif

#define TMS6100_READ_PENDING        0x01
#define TMS6100_NEXT_READ_IS_DUMMY  0x02

/* Variants */

#define TMS6110_IS_TMS6100    (1)
#define TMS6110_IS_M58819     (2)


const device_type TMS6100 = &device_creator<tms6100_device>;

tms6100_device::tms6100_device(const machine_config &mconfig, device_type type, const char *name, const char *tag, device_t *owner, UINT32 clock, const char *shortname, const char *source)
	: device_t(mconfig, type, name, tag, owner, clock, shortname, source),
	m_rom(*this, DEVICE_SELF)
{
}

tms6100_device::tms6100_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock)
	: device_t(mconfig, TMS6100, "TMS6100", tag, owner, clock, "tms6100", __FILE__),
	m_rom(*this, DEVICE_SELF)
{
}

const device_type M58819 = &device_creator<m58819_device>;

m58819_device::m58819_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock)
	: tms6100_device(mconfig, M58819, "M58819 Memory Controller", tag, owner, clock, "m58819", __FILE__)
{
}

//-------------------------------------------------
//  device_config_complete - perform any
//  operations now that the configuration is
//  complete
//-------------------------------------------------

void tms6100_device::device_config_complete()
{
}
=======

// device definitions

DEFINE_DEVICE_TYPE(TMS6100, tms6100_device, "tms6100", "TMS6100 VSM")
DEFINE_DEVICE_TYPE(M58819,  m58819_device,  "m58819s", "M68819S")


tms6100_device::tms6100_device(const machine_config &mconfig, device_type type, const char *tag, device_t *owner, u32 clock)
	: device_t(mconfig, type, tag, owner, clock)
	, m_rom(*this, DEVICE_SELF)
	, m_reverse_bits(false)
	, m_4bit_mode(false)
{
}

tms6100_device::tms6100_device(const machine_config &mconfig, const char *tag, device_t *owner, u32 clock)
	: tms6100_device(mconfig, TMS6100, tag, owner, clock)
{
}


m58819_device::m58819_device(const machine_config &mconfig, const char *tag, device_t *owner, u32 clock)
	: tms6100_device(mconfig, M58819, tag, owner, clock)
{
}

>>>>>>> upstream/master

//-------------------------------------------------
//  device_start - device-specific startup
//-------------------------------------------------

void tms6100_device::device_start()
{
<<<<<<< HEAD
	// save device variables
	save_item(NAME(m_addr_bits));
	save_item(NAME(m_address));
	save_item(NAME(m_address_latch));
	save_item(NAME(m_tms_clock));
	save_item(NAME(m_data));
	save_item(NAME(m_loadptr));
	save_item(NAME(m_m0));
	save_item(NAME(m_m1));
	save_item(NAME(m_state));
	save_item(NAME(m_variant));
	set_variant(TMS6110_IS_TMS6100);

=======
	m_rommask = m_rom.bytes() - 1;

	// zerofill
	m_address = 0;
	m_sa = 0;
	m_count = 0;
	m_prev_cmd = 0;
	m_prev_m = 0;

	m_add = 0;
	m_data = 0;
	m_m0 = 0;
	m_m1 = 0;
	m_cs = 1;
	m_clk = 0;
	m_rck = 0;

	// register for savestates
	save_item(NAME(m_address));
	save_item(NAME(m_sa));
	save_item(NAME(m_count));
	save_item(NAME(m_prev_cmd));
	save_item(NAME(m_prev_m));
	save_item(NAME(m_add));
	save_item(NAME(m_data));
	save_item(NAME(m_m0));
	save_item(NAME(m_m1));
	save_item(NAME(m_cs));
	save_item(NAME(m_clk));
	save_item(NAME(m_rck));
>>>>>>> upstream/master
}

void m58819_device::device_start()
{
	tms6100_device::device_start();
<<<<<<< HEAD
	set_variant(TMS6110_IS_M58819);
}

//-------------------------------------------------
//  device_reset - device-specific reset
//-------------------------------------------------

void tms6100_device::device_reset()
{
	/* initialize the chip */
	m_addr_bits = 0;
	m_address = 0;
	m_address_latch = 0;
	m_loadptr = 0;
	m_m0 = 0;
	m_m1 = 0;
	m_state = 0;
	m_tms_clock = 0;
	m_data = 0;
}

void tms6100_device::set_variant(int variant)
{
	m_variant = variant;
}

WRITE_LINE_MEMBER(tms6100_device::tms6100_m0_w)
{
	if (state != m_m0)
		m_m0 = state;
}

WRITE_LINE_MEMBER(tms6100_device::tms6100_m1_w)
{
	if (state != m_m1)
		m_m1 = state;
}

WRITE_LINE_MEMBER(tms6100_device::tms6100_romclock_w)
{
	/* process on falling edge */
	if (m_tms_clock && !state)
	{
		switch ((m_m1<<1) | m_m0)
		{
		case 0x00:
			/* NOP in datasheet, not really ... */
			if (m_state & TMS6100_READ_PENDING)
			{
				if (m_state & TMS6100_NEXT_READ_IS_DUMMY)
				{
					m_address = (m_address_latch << 3);
					m_address_latch = 0;
					m_loadptr = 0;
					m_state &= ~TMS6100_NEXT_READ_IS_DUMMY;
					LOG(("loaded address %08x\n", m_address));
				}
				else
				{
					/* read bit at address */
					if (m_variant == TMS6110_IS_M58819)
					{
						m_data = (m_rom[m_address >> 3] >> (7-(m_address & 0x07))) & 1;
					}
					else // m_variant == (TMS6110_IS_TMS6100 || TMS6110_IS_TMS6125)
					{
						m_data = (m_rom[m_address >> 3] >> (m_address & 0x07)) & 1;
					}
					m_address++;
				}
				m_state &= ~TMS6100_READ_PENDING;
			}
			break;
		case 0x01:
			/* READ */
			m_state |= TMS6100_READ_PENDING;
			break;
		case 0x02:
			/* LOAD ADDRESS */
			m_state |= TMS6100_NEXT_READ_IS_DUMMY;
			m_address_latch |= (m_addr_bits << m_loadptr);
			LOG(("loaded address latch %08x\n", m_address_latch));
			m_loadptr += 4;
			break;
		case 0x03:
			/* READ AND BRANCH */
			if (m_state & TMS6100_NEXT_READ_IS_DUMMY)
			{
				m_state &= ~TMS6100_NEXT_READ_IS_DUMMY;  // clear - no dummy read according to datasheet
				LOG(("loaded address latch %08x\n", m_address_latch));
				m_address = m_rom[m_address_latch] | (m_rom[m_address_latch+1]<<8);
				m_address &= 0x3fff; // 14 bits
				LOG(("loaded indirect address %04x\n", m_address));
				m_address = (m_address << 3);
				m_address_latch = 0;
				m_loadptr = 0;
			}
			break;
		}
	}
	m_tms_clock = state;
}

WRITE8_MEMBER(tms6100_device::tms6100_addr_w)
{
	if (data != m_addr_bits)
		m_addr_bits = data;
}

READ_LINE_MEMBER(tms6100_device::tms6100_data_r)
{
	return m_data;
=======
	m_reverse_bits = true; // m58819 'vsm-emulator' chip expects ROM bit order backwards
}


// external i/o

WRITE_LINE_MEMBER(tms6100_device::m0_w)
{
	m_m0 = (state) ? 1 : 0;
}

WRITE_LINE_MEMBER(tms6100_device::m1_w)
{
	m_m1 = (state) ? 1 : 0;
}

WRITE_LINE_MEMBER(tms6100_device::cs_w)
{
	// chip select pin
	m_cs = (state) ? 1 : 0;
}

WRITE_LINE_MEMBER(tms6100_device::rck_w)
{
	// gate/mask for clk
	m_rck = (state) ? 1 : 0;
}

WRITE8_MEMBER(tms6100_device::add_w)
{
	m_add = data & 0xf;
}

READ8_MEMBER(tms6100_device::data_r)
{
	return m_data & 0xf;
}

READ_LINE_MEMBER(tms6100_device::data_line_r)
{
	// DATA/ADD8
	return (m_data & 8) ? 1 : 0;
}

WRITE_LINE_MEMBER(tms6100_device::clk_w)
{
	// process on falling edge
	if (m_clk && !m_rck && !state)
	{
		if (m_cs)
		{
			// new command enabled on rising edge of m0/m1
			u8 m = m_m1 << 1 | m_m0;
			if ((m & ~m_prev_m & 1) || (m & ~m_prev_m & 2))
				handle_command(m);

			m_prev_m = m;
		}
	}

	m_clk = (state) ? 1 : 0;
}


// m0/m1 commands

void tms6100_device::handle_command(u8 cmd)
{
	enum
	{
		M_NOP = 0, M_TB, M_LA, M_RB
	};

	switch (cmd)
	{
		// TB: transfer bit (read)
		case M_TB:
			if (m_prev_cmd == M_LA)
			{
				// dummy read after LA
				m_count = 0;
			}
			else
			{
				// load new data from rom
				if (m_count == 0)
				{
					m_sa = m_rom[m_address & m_rommask];

					// M58819S reads serial data reversed
					if (m_reverse_bits)
						m_sa = BITSWAP8(m_sa,0,1,2,3,4,5,6,7);
				}
				else
				{
					// or shift(rotate) right
					m_sa = (m_sa >> 1) | (m_sa << 7 & 0x80);
				}

				// output to DATA pin(s)
				if (!m_4bit_mode)
				{
					// 1-bit mode: SA0 to ADD8/DATA
					m_data = m_sa << 3 & 8;
				}
				else
				{
					// 4-bit mode: SA0-3 or SA3-6(!) to DATA
					if (m_count & 1)
						m_data = m_sa >> 3 & 0xf;
					else
						m_data = m_sa & 0xf;
				}

				// 8 bits in 1-bit mode, otherwise 2 nybbles
				m_count = (m_count + 1) & (m_4bit_mode ? 1 : 7);

				// TB8
				if (m_count == 0)
					m_address++; // CS bits too
			}
			break;

		// LA: load address
		case M_LA:
			if (m_prev_cmd == M_TB)
			{
				// start LA after TB
				m_address = (m_address & ~0xf) | m_add;
				m_count = 0;
			}
			else if (m_prev_cmd == M_LA)
			{
				// load consecutive address bits (including CS bits)
				// the 8-step counter PLA is shared between LA and TB
				if (m_count < 4)
				{
					const u8 shift = 4 * (m_count+1);
					m_address = (m_address & ~(0xf << shift)) | (m_add << shift);
				}

				m_count = (m_count + 1) & 7;
			}
			break;

		// RB: read and branch
		case M_RB:
			// process RB after LA or TB8
			if (m_prev_cmd == M_LA || (m_prev_cmd == M_TB && m_count == 0))
			{
				m_count = 0;

				// load new address bits (14 bits on TMS6100)
				u16 rb = m_rom[m_address & m_rommask];
				m_address++;
				rb |= (m_rom[m_address & m_rommask] << 8);
				m_address = (m_address & ~0x3fff) | (rb & 0x3fff);
			}
			break;

		default:
			break;
	}

	m_prev_cmd = cmd;
>>>>>>> upstream/master
}
