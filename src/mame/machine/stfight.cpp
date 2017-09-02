// license:BSD-3-Clause
// copyright-holders:Mark McDougall
/***************************************************************************

  stfight.c

  Functions to emulate general aspects of the machine (RAM, ROM, interrupts,
  I/O ports)

***************************************************************************/

#include "emu.h"
<<<<<<< HEAD
#include "cpu/z80/z80.h"
#include "sound/msm5205.h"
#include "includes/stfight.h"


=======
#include "includes/stfight.h"

#include "cpu/m6805/m68705.h"
#include "cpu/z80/z80.h"
#include "sound/msm5205.h"
>>>>>>> upstream/master


/*

Encryption PAL 16R4 on CPU board

          +---U---+
     CP --|       |-- VCC
 ROM D1 --|       |-- ROM D0          M1 = 0                M1 = 1
 ROM D3 --|       |-- (NC)
 ROM D4 --|       |-- D6         D6 = D1 ^^ D3          D6 = / ( D1 ^^ D0 )
 ROM D6 --|       |-- D4         D4 = / ( D6 ^^ A7 )    D4 = D3 ^^ A0
     A0 --|       |-- D3         D3 = / ( D0 ^^ A1 )    D3 = D4 ^^ A4
     A1 --|       |-- D0         D0 = D1 ^^ D4          D0 = / ( D6 ^^ A0 )
     A4 --|       |-- (NC)
     A7 --|       |-- /M1
    GND --|       |-- /OE
          +-------+

*/


<<<<<<< HEAD
DRIVER_INIT_MEMBER(stfight_state,empcity)
{
	UINT8 *rom = memregion("maincpu")->base();

	for (UINT32 A = 0; A < 0x8000; ++A)
	{
		UINT8 src = rom[A];
=======
DRIVER_INIT_MEMBER(stfight_state, empcity)
{
	uint8_t *rom = memregion("maincpu")->base();

	for (uint32_t A = 0; A < 0x8000; ++A)
	{
		uint8_t src = rom[A];
>>>>>>> upstream/master

		// decode opcode
		m_decrypted_opcodes[A] =
				( src & 0xA6 ) |
				( ( ( ( src << 2 ) ^ src ) << 3 ) & 0x40 ) |
				( ~( ( src ^ ( A >> 1 ) ) >> 2 ) & 0x10 ) |
				( ~( ( ( src << 1 ) ^ A ) << 2 ) & 0x08 ) |
				( ( ( src ^ ( src >> 3 ) ) >> 1 ) & 0x01 );

		// decode operand
		rom[A] =
				( src & 0xA6 ) |
				( ~( ( src ^ ( src << 1 ) ) << 5 ) & 0x40 ) |
				( ( ( src ^ ( A << 3 ) ) << 1 ) & 0x10 ) |
				( ( ( src ^ A ) >> 1 ) & 0x08 ) |
				( ~( ( src >> 6 ) ^ A ) & 0x01 );
	}

}

<<<<<<< HEAD
DRIVER_INIT_MEMBER(stfight_state,stfight)
=======
DRIVER_INIT_MEMBER(stfight_state, stfight)
>>>>>>> upstream/master
{
	DRIVER_INIT_CALL(empcity);
}

<<<<<<< HEAD
DRIVER_INIT_MEMBER(stfight_state,cshooter)
=======
DRIVER_INIT_MEMBER(stfight_state, cshooter)
>>>>>>> upstream/master
{
}

void stfight_state::machine_start()
{
<<<<<<< HEAD
	save_item(NAME(m_fm_data));
	save_item(NAME(m_cpu_to_mcu_data));
	save_item(NAME(m_cpu_to_mcu_empty));
	save_item(NAME(m_adpcm_data_offs));
	save_item(NAME(m_adpcm_nibble));
	save_item(NAME(m_adpcm_reset));
	save_item(NAME(m_coin_state));
	save_item(NAME(m_sprite_base));
	save_item(NAME(m_portA_out));
	save_item(NAME(m_portA_in));
	save_item(NAME(m_portB_out));
	save_item(NAME(m_portB_in));
	save_item(NAME(m_portC_out));
	save_item(NAME(m_portC_in));
	save_item(NAME(m_ddrA));
	save_item(NAME(m_ddrB));
	save_item(NAME(m_ddrC));
}

void stfight_state::machine_reset()
{
	m_fm_data = 0;
	m_adpcm_reset = 1;
	m_cpu_to_mcu_empty = 1;

	// Coin signals are active low
	m_coin_state = 3;

	// initialise ROM bank
	stfight_bank_w(m_maincpu->space(AS_PROGRAM), 0, 0);
=======
	m_main_bank->configure_entries(0, 4, memregion("maincpu")->base() + 0x10000, 0x4000);
	m_main_bank->set_entry(0);

	m_int1_timer = timer_alloc(TIMER_STFIGHT_INTERRUPT_1);

	save_item(NAME(m_coin_state));

	save_item(NAME(m_fm_data));

	save_item(NAME(m_cpu_to_mcu_empty));
	save_item(NAME(m_cpu_to_mcu_data));
	save_item(NAME(m_port_a_out));
	save_item(NAME(m_port_c_out));

	save_item(NAME(m_vck2));
	save_item(NAME(m_adpcm_reset));
	save_item(NAME(m_adpcm_data_offs));
}


void stfight_state::machine_reset()
{
	m_fm_data = 0;
	m_cpu_to_mcu_empty = true;
	m_adpcm_reset = true;

	// Coin signals are active low
	m_coin_state = 3;
>>>>>>> upstream/master
}

// It's entirely possible that this bank is never switched out
// - in fact I don't even know how/where it's switched in!
WRITE8_MEMBER(stfight_state::stfight_bank_w)
{
<<<<<<< HEAD
	UINT8   *ROM2 = memregion("maincpu")->base() + 0x10000;
	UINT16 bank_num;

	bank_num = 0;

	if(data & 0x80)
		bank_num |= 0x8000;

	if(data & 0x04)
		bank_num |= 0x4000;

	membank("bank1")->set_base(&ROM2[bank_num]);
=======
	m_main_bank->set_entry(bitswap(data, 7, 2));
>>>>>>> upstream/master
}

/*
 *      CPU 1 timed interrupt - 60Hz???
 */

void stfight_state::device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr)
{
	switch (id)
	{
	case TIMER_STFIGHT_INTERRUPT_1:
		// Do a RST08
		m_maincpu->set_input_line_and_vector(0, HOLD_LINE, 0xd7);
		break;
	default:
<<<<<<< HEAD
		assert_always(FALSE, "Unknown id in stfight_state::device_timer");
=======
		assert_always(false, "Unknown id in stfight_state::device_timer");
>>>>>>> upstream/master
	}
}

INTERRUPT_GEN_MEMBER(stfight_state::stfight_vb_interrupt)
{
	// Do a RST10
	device.execute().set_input_line_and_vector(0, HOLD_LINE, 0xcf);
<<<<<<< HEAD
	timer_set(attotime::from_hz(120), TIMER_STFIGHT_INTERRUPT_1);
=======
	m_int1_timer->adjust(attotime::from_hz(120));
>>>>>>> upstream/master
}

/*
 *      Hardware handlers
 */

WRITE8_MEMBER(stfight_state::stfight_io_w)
{
	// TODO: What is bit 4?
<<<<<<< HEAD
	coin_counter_w(machine(), 0, data & 1);
	coin_counter_w(machine(), 1, data & 2);
=======
	machine().bookkeeping().coin_counter_w(0, data & 1);
	machine().bookkeeping().coin_counter_w(1, data & 2);
>>>>>>> upstream/master
}

READ8_MEMBER(stfight_state::stfight_coin_r)
{
	return m_coin_state;
}

WRITE8_MEMBER(stfight_state::stfight_coin_w)
{
	// Acknowledge coin signals (active low)
	if (!BIT(data, 0))
		m_coin_state |= 1;

	if (!BIT(data, 1))
		m_coin_state |= 2;
}

/*
 *      Machine hardware for MSM5205 ADPCM sound control
 */

WRITE_LINE_MEMBER(stfight_state::stfight_adpcm_int)
{
<<<<<<< HEAD
	static int m_vck2 = 0;

	// Falling edge triggered interrupt at half the rate of /VCK?
	if (m_vck2)
		m_mcu->set_input_line(0, HOLD_LINE);

	m_vck2 ^= 1;

	if (!m_adpcm_reset)
	{
		const UINT8 *samples = memregion("adpcm")->base();
		UINT8 adpcm_data = samples[m_adpcm_data_offs & 0x7fff];

		if (m_adpcm_nibble == 0)
			adpcm_data >>= 4;
		else
			++m_adpcm_data_offs;

		m_msm->data_w(adpcm_data & 0x0f);
		m_adpcm_nibble ^= 1;
=======
	// Falling edge triggered interrupt at half the rate of /VCK?
	m_mcu->set_input_line(M68705_IRQ_LINE, m_vck2 ? ASSERT_LINE : CLEAR_LINE);
	m_vck2 = !m_vck2;

	if (!m_adpcm_reset)
	{
		uint8_t adpcm_data = m_samples[(m_adpcm_data_offs >> 1) & 0x7fff];

		if (!BIT(m_adpcm_data_offs, 0))
			adpcm_data >>= 4;
		++m_adpcm_data_offs;

		m_msm->data_w(adpcm_data & 0x0f);
>>>>>>> upstream/master
	}
}


/*
 *      Machine hardware for YM2303 FM sound control
 */

WRITE8_MEMBER(stfight_state::stfight_fm_w)
{
	// The sound cpu ignores any FM data without bit 7 set
	m_fm_data = 0x80 | data;
}

READ8_MEMBER(stfight_state::stfight_fm_r)
{
<<<<<<< HEAD
	UINT8 data = m_fm_data;

	// Acknowledge the command
	m_fm_data &= ~0x80;
=======
	uint8_t const data = m_fm_data;

	// Acknowledge the command
	if (!machine().side_effect_disabled())
		m_fm_data &= ~0x80;
>>>>>>> upstream/master

	return data;
}


/*
 *  MCU communications
 */

WRITE8_MEMBER(stfight_state::stfight_mcu_w)
{
<<<<<<< HEAD
	m_cpu_to_mcu_data = data;
	m_cpu_to_mcu_empty = 0;
}

WRITE8_MEMBER(stfight_state::stfight_68705_ddr_a_w)
{
	m_ddrA = data;
}

WRITE8_MEMBER(stfight_state::stfight_68705_ddr_b_w)
{
	m_ddrB = data;
}

WRITE8_MEMBER(stfight_state::stfight_68705_ddr_c_w)
{
	m_ddrC = data;
}


READ8_MEMBER(stfight_state::stfight_68705_port_a_r)
{
	m_portA_in = m_cpu_to_mcu_data;

	return (m_portA_out & m_ddrA) | (m_portA_in & ~m_ddrA);
=======
	m_cpu_to_mcu_data = data & 0x0f;
	m_cpu_to_mcu_empty = false;
>>>>>>> upstream/master
}

WRITE8_MEMBER(stfight_state::stfight_68705_port_a_w)
{
<<<<<<< HEAD
	m_adpcm_data_offs = data << 8;
	m_portA_out = data;
=======
	m_port_a_out = data;
>>>>>>> upstream/master
}

READ8_MEMBER(stfight_state::stfight_68705_port_b_r)
{
<<<<<<< HEAD
	m_portB_in = (ioport("COIN")->read() << 6) | (m_cpu_to_mcu_empty << 4) | m_cpu_to_mcu_data;

	return (m_portB_out & m_ddrB) | (m_portB_in & ~m_ddrB);
=======
	return
			(m_coin_mech->read() << 6) |
			(m_cpu_to_mcu_empty ? 0x10 : 0x00) |
			(m_cpu_to_mcu_data & 0x0f);
>>>>>>> upstream/master
}

WRITE8_MEMBER(stfight_state::stfight_68705_port_b_w)
{
<<<<<<< HEAD
	if ((m_ddrB & 0x20) && (~data & 0x20))
	{
		// Acknowledge Z80 command
		m_cpu_to_mcu_empty = 1;
	}

	m_portB_out = data;
}

READ8_MEMBER(stfight_state::stfight_68705_port_c_r)
{
	return (m_portC_out & m_ddrC) | (m_portC_in & ~m_ddrC);
=======
	// Acknowledge Z80 command
	if (!BIT(data, 5))
		m_cpu_to_mcu_empty = true;
>>>>>>> upstream/master
}

WRITE8_MEMBER(stfight_state::stfight_68705_port_c_w)
{
	// Signal a valid coin on the falling edge
<<<<<<< HEAD
	if ((m_ddrC & 0x01) && (m_portC_out & 0x01) && !(data & 0x01))
	{
		m_coin_state &= ~1;
	}

	if ((m_ddrC & 0x02) && (m_portC_out & 0x02) && !(data & 0x02))
	{
		m_coin_state &= ~2;
	}

	if (m_ddrC & 0x04)
	{
		if (data & 0x04)
		{
			m_adpcm_reset = 1;
			m_adpcm_nibble = 0;
			m_msm->reset_w(1);
		}
		else
		{
			m_adpcm_reset = 0;
			m_msm->reset_w(0);
		}
	}

	if (m_ddrC & 0x08)
		m_maincpu->set_input_line(INPUT_LINE_NMI, data & 0x08 ? CLEAR_LINE : ASSERT_LINE);

	m_portC_out = data;
=======
	if (BIT(m_port_c_out, 0) && !BIT(data, 0))
		m_coin_state &= ~1;
	if (BIT(m_port_c_out, 1) && !BIT(data, 1))
		m_coin_state &= ~2;

	// Latch ADPCM data address when dropping the reset line
	m_adpcm_reset = BIT(data, 2);
	if (!m_adpcm_reset && BIT(m_port_c_out, 2))
		m_adpcm_data_offs = m_port_a_out << 9;
	m_msm->reset_w(m_adpcm_reset ? ASSERT_LINE : CLEAR_LINE);

	// Generate NMI on host CPU (used on handshake error or stuck coin)
	m_maincpu->set_input_line(INPUT_LINE_NMI, BIT(data, 3) ? CLEAR_LINE : ASSERT_LINE);

	m_port_c_out = data;
>>>>>>> upstream/master
}
