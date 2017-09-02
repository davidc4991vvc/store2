// license:BSD-3-Clause
// copyright-holders:James Wallace
/***************************************************************************

    Motorola 6840 (PTM)

    Programmable Timer Module

    Written By J.Wallace based on previous work by Aaron Giles,
   'Re-Animator' and Mathis Rosenhauer.

    Todo:
         Confirm handling for 'Single Shot' operation.
         (Datasheet suggests that output starts high, going low
         on timeout, opposite of continuous case)
         Establish whether ptm6840_set_c? routines can replace
         hard coding of external clock frequencies.


    Operation:
    The interface is arranged as follows:

    Internal Clock frequency,
    Clock 1 frequency, Clock 2 frequency, Clock 3 frequency,
    Clock 1 output, Clock 2 output, Clock 3 output,
    IRQ function

    If the external clock frequencies are not fixed, they should be
    entered as '0', and the ptm6840_set_c?(which, state) functions
    should be used instead if necessary (This should allow the VBLANK
    clock on the MCR units to operate).


    2009-06 Converted to be a device

***************************************************************************/

#include "emu.h"
#include "6840ptm.h"

<<<<<<< HEAD

#define PTMVERBOSE 0
#define PLOG(x) do { if (PTMVERBOSE) logerror x; } while (0)
=======
//#define VERBOSE 1
#include "logmacro.h"

>>>>>>> upstream/master

/***************************************************************************
    LOCAL VARIABLES
***************************************************************************/

const char *const ptm6840_device::opmode[] =
{
	"000 continuous mode",
	"001 freq comparison mode",
	"010 continuous mode",
	"011 pulse width comparison mode",
	"100 single shot mode",
	"101 freq comparison mode",
	"110 single shot mode",
	"111 pulse width comparison mode"
};

/***************************************************************************
    IMPLEMENTATION
***************************************************************************/

// device type definition
<<<<<<< HEAD
const device_type PTM6840 = &device_creator<ptm6840_device>;
=======
DEFINE_DEVICE_TYPE(PTM6840, ptm6840_device, "ptm6840", "MC6840 PTM")
>>>>>>> upstream/master

//-------------------------------------------------
//  ptm6840_device - constructor
//-------------------------------------------------

<<<<<<< HEAD
ptm6840_device::ptm6840_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock)
	: device_t(mconfig, PTM6840, "6840 PTM", tag, owner, clock, "ptm6840", __FILE__),
		m_internal_clock(0.0),
		m_out0_cb(*this),
		m_out1_cb(*this),
		m_out2_cb(*this),
		m_irq_cb(*this)
{
	m_external_clock[0] = m_external_clock[1] = m_external_clock[2] = 0.0;
=======
ptm6840_device::ptm6840_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock)
	: device_t(mconfig, PTM6840, tag, owner, clock)
	, m_external_clock{ 0.0, 0.0, 0.0 }
	, m_out_cb{*this, *this, *this}
	, m_irq_cb(*this)
{
>>>>>>> upstream/master
}

//-------------------------------------------------
//  device_start - device-specific startup
//-------------------------------------------------

void ptm6840_device::device_start()
{
	// resolve callbacks
<<<<<<< HEAD
	m_out0_cb.resolve_safe();
	m_out1_cb.resolve_safe();
	m_out2_cb.resolve_safe();
	m_irq_cb.resolve_safe();

	for (int i = 0; i < 3; i++)
	{
		if ( m_external_clock[i] == 0 )
			m_external_clock[i] = 1;
=======
	m_out_cb[0].resolve_safe();
	m_out_cb[1].resolve_safe();
	m_out_cb[2].resolve_safe();
	m_irq_cb.resolve_safe();

	for (auto & elem : m_external_clock)
	{
		if ( elem == 0 )
			elem = 1;
>>>>>>> upstream/master
	}

	m_timer[0] = timer_alloc(0);
	m_timer[1] = timer_alloc(1);
	m_timer[2] = timer_alloc(2);

<<<<<<< HEAD
	for (int i = 0; i < 3; i++)
	{
		m_timer[i]->enable(false);
=======
	for (auto & elem : m_timer)
	{
		elem->enable(false);
>>>>>>> upstream/master
	}

	// register for state saving
	save_item(NAME(m_lsb_buffer));
	save_item(NAME(m_msb_buffer));
	save_item(NAME(m_status_read_since_int));
	save_item(NAME(m_status_reg));
	save_item(NAME(m_t3_divisor));
	save_item(NAME(m_t3_scaler));
<<<<<<< HEAD
	save_item(NAME(m_internal_clock));
	save_item(NAME(m_IRQ));
=======
	save_item(NAME(m_irq));
>>>>>>> upstream/master

	save_item(NAME(m_control_reg));
	save_item(NAME(m_output));
	save_item(NAME(m_gate));
	save_item(NAME(m_clk));
	save_item(NAME(m_mode));
	save_item(NAME(m_fired));
	save_item(NAME(m_enabled));
	save_item(NAME(m_external_clock));
	save_item(NAME(m_counter));
	save_item(NAME(m_latch));
}


//-------------------------------------------------
//  device_reset - device-specific reset
//-------------------------------------------------

void ptm6840_device::device_reset()
{
	m_control_reg[2]         = 0;
	m_control_reg[1]         = 0;
	m_control_reg[0]         = 1;
	m_status_reg             = 0;
	m_t3_divisor             = 1;
	m_status_read_since_int = 0;
<<<<<<< HEAD
	m_IRQ                   = 0;
=======
	m_irq                   = 0;
>>>>>>> upstream/master
	m_t3_scaler             = 0;
	for (int i = 0; i < 3; i++)
	{
		m_counter[i] = 0xffff;
		m_latch[i]   = 0xffff;
		m_output[i]  = 0;
		m_fired[i]   = 0;
		m_enabled[i] = 0;
		m_mode[i] = 0;
	}
}


//-------------------------------------------------
//  device_timer - handle timer callbacks
//-------------------------------------------------

void ptm6840_device::device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr)
{
	timeout(id);
}


//-------------------------------------------------
//  subtract_from_counter - Subtract from Counter
//-------------------------------------------------

void ptm6840_device::subtract_from_counter(int counter, int count)
{
<<<<<<< HEAD
	double clock;

	// Determine the clock frequency for this timer
	if (m_control_reg[counter] & 0x02)
	{
		clock = m_internal_clock;
	}
	else
	{
		clock = m_external_clock[counter];
	}

	// Dual-byte mode
	if (m_control_reg[counter] & 0x04)
=======
	// Determine the clock frequency for this timer
	double clk = m_control_reg[counter] & INTERNAL_CLK_EN ? static_cast<double>(clock()) : m_external_clock[counter];

	// Dual-byte mode
	if (m_control_reg[counter] & COUNT_MODE_8BIT)
>>>>>>> upstream/master
	{
		int lsb = m_counter[counter] & 0xff;
		int msb = m_counter[counter] >> 8;

		// Count the clocks
		lsb -= count;

		// Loop while we're less than zero
		while (lsb < 0)
		{
			// Borrow from the MSB
			lsb += (m_latch[counter] & 0xff) + 1;
			msb--;

			// If MSB goes less than zero, we've expired
			if (msb < 0)
			{
				timeout(counter);
				msb = (m_latch[counter] >> 8) + 1;
			}
		}

		// Store the result
		m_counter[counter] = (msb << 8) | lsb;
	}

	// Word mode
	else
	{
		int word = m_counter[counter];

		// Count the clocks
		word -= count;

		// loop while we're less than zero
		while (word < 0)
		{
			// Borrow from the MSB
			word += m_latch[counter] + 1;

			// We've expired
			timeout(counter);
		}

		// Store the result
		m_counter[counter] = word;
	}

	if (m_enabled[counter])
	{
<<<<<<< HEAD
		attotime duration = attotime::from_hz(clock) * m_counter[counter];
=======
		attotime duration = attotime::from_hz(clk) * m_counter[counter];
>>>>>>> upstream/master

		if (counter == 2)
		{
			duration *= m_t3_divisor;
		}

		m_timer[counter]->adjust(duration);
	}
}



//-------------------------------------------------
//  tick
//-------------------------------------------------

void ptm6840_device::tick(int counter, int count)
{
	if (counter == 2)
	{
		m_t3_scaler += count;

		if ( m_t3_scaler > m_t3_divisor - 1)
		{
			subtract_from_counter(counter, 1);
			m_t3_scaler = 0;
		}
	}
	else
	{
		subtract_from_counter(counter, count);
	}
}



//-------------------------------------------------
//  update_interrupts - Update Internal Interrupts
//-------------------------------------------------

void ptm6840_device::update_interrupts()
{
<<<<<<< HEAD
	int new_state = ((m_status_reg & 0x01) && (m_control_reg[0] & 0x40)) ||
					((m_status_reg & 0x02) && (m_control_reg[1] & 0x40)) ||
					((m_status_reg & 0x04) && (m_control_reg[2] & 0x40));

	if (new_state != m_IRQ)
	{
		m_IRQ = new_state;

		if (m_IRQ)
		{
			m_status_reg |= 0x80;
		}
		else
		{
			m_status_reg &= ~0x80;
		}

		m_irq_cb(m_IRQ);
=======
	int new_state = ((m_status_reg & TIMER1_IRQ) && (m_control_reg[0] & INTERRUPT_EN)) ||
					((m_status_reg & TIMER2_IRQ) && (m_control_reg[1] & INTERRUPT_EN)) ||
					((m_status_reg & TIMER3_IRQ) && (m_control_reg[2] & INTERRUPT_EN));

	if (new_state != m_irq)
	{
		m_irq = new_state;

		if (m_irq)
		{
			m_status_reg |= ANY_IRQ;
		}
		else
		{
			m_status_reg &= ~ANY_IRQ;
		}

		m_irq_cb(m_irq);
>>>>>>> upstream/master
	}
}



//-------------------------------------------------
//  compute_counter - Compute Counter
//-------------------------------------------------

<<<<<<< HEAD
UINT16 ptm6840_device::compute_counter( int counter ) const
{
	double clock;
=======
uint16_t ptm6840_device::compute_counter( int counter ) const
{
	double clk;
>>>>>>> upstream/master

	// If there's no timer, return the count
	if (!m_enabled[counter])
	{
<<<<<<< HEAD
		PLOG(("MC6840 #%s: read counter(%d): %d\n", tag(), counter, m_counter[counter]));
=======
		LOG("MC6840: read counter(%d): %d\n", counter, m_counter[counter]);
>>>>>>> upstream/master
		return m_counter[counter];
	}

	// determine the clock frequency for this timer
<<<<<<< HEAD
	if (m_control_reg[counter] & 0x02)
	{
		clock = m_internal_clock;
		PLOG(("MC6840 #%s: %d internal clock freq %f \n", tag(), counter, clock));
	}
	else
	{
		clock = m_external_clock[counter];
		PLOG(("MC6840 #%s: %d external clock freq %f \n", tag(), counter, clock));
	}
	// See how many are left
	int remaining = (m_timer[counter]->remaining() * clock).as_double();

	// Adjust the count for dual byte mode
	if (m_control_reg[counter] & 0x04)
=======
	if (m_control_reg[counter] & INTERNAL_CLK_EN)
	{
		clk = static_cast<double>(clock());
		LOG("MC6840: %d internal clock freq %f \n", counter, clk);
	}
	else
	{
		clk = m_external_clock[counter];
		LOG("MC6840: %d external clock freq %f \n", counter, clk);
	}
	// See how many are left
	int remaining = (m_timer[counter]->remaining() * clk).as_double();

	// Adjust the count for dual byte mode
	if (m_control_reg[counter] & COUNT_MODE_8BIT)
>>>>>>> upstream/master
	{
		int divisor = (m_counter[counter] & 0xff) + 1;
		int msb = remaining / divisor;
		int lsb = remaining % divisor;
		remaining = (msb << 8) | lsb;
	}
<<<<<<< HEAD
	PLOG(("MC6840 #%s: read counter(%d): %d\n", tag(), counter, remaining));
=======
	LOG("MC6840: read counter(%d): %d\n", counter, remaining);
>>>>>>> upstream/master
	return remaining;
}



//-------------------------------------------------
//  reload_count - Reload Counter
//-------------------------------------------------

void ptm6840_device::reload_count(int idx)
{
<<<<<<< HEAD
	double clock;
=======
	double clk;
>>>>>>> upstream/master

	// Copy the latched value in
	m_counter[idx] = m_latch[idx];

<<<<<<< HEAD
	// Determine the clock frequency for this timer
	if (m_control_reg[idx] & 0x02)
	{
		clock = m_internal_clock;
		PLOG(("MC6840 #%s: %d internal clock freq %f \n", tag(), idx, clock));
	}
	else
	{
		clock = m_external_clock[idx];
		PLOG(("MC6840 #%s: %d external clock freq %f \n", tag(), idx, clock));
=======
	// If reset is held, don't start counting
	if (m_control_reg[0] & RESET_TIMERS)
		return;

	// Determine the clock frequency for this timer
	if (m_control_reg[idx] & INTERNAL_CLK_EN)
	{
		clk = static_cast<double> (clock());
		LOG("MC6840: %d internal clock freq %f \n", idx, clk);
	}
	else
	{
		clk = m_external_clock[idx];
		LOG("MC6840: %d external clock freq %f \n", idx, clk);
>>>>>>> upstream/master
	}

	// Determine the number of clock periods before we expire
	int count = m_counter[idx];
<<<<<<< HEAD
	if (m_control_reg[idx] & 0x04)
=======
	if (m_control_reg[idx] & COUNT_MODE_8BIT)
>>>>>>> upstream/master
	{
		count = ((count >> 8) + 1) * ((count & 0xff) + 1);
	}
	else
	{
		count = count + 1;
	}

	m_fired[idx] = 0;

	if ((m_mode[idx] == 4) || (m_mode[idx] == 6))
	{
		m_output[idx] = 1;
<<<<<<< HEAD
		switch (idx)
		{
			case 0:
				m_out0_cb((offs_t)0, m_output[0]);
				break;
			case 1:
				m_out1_cb((offs_t)0, m_output[1]);
				break;
			case 2:
				m_out2_cb((offs_t)0, m_output[2]);
				break;
		}
	}

	// Set the timer
	PLOG(("MC6840 #%s: reload_count(%d): clock = %f  count = %d\n", tag(), idx, clock, count));

	attotime duration = attotime::from_hz(clock) * count;
=======
		m_out_cb[idx](m_output[idx]);
	}

	// Set the timer
	LOG("MC6840: reload_count(%d): clock = %f  count = %d\n", idx, clk, count);

	attotime duration = attotime::from_hz(clk) * count;
>>>>>>> upstream/master
	if (idx == 2)
	{
		duration *= m_t3_divisor;
	}

<<<<<<< HEAD
	PLOG(("MC6840 #%s: reload_count(%d): output = %f\n", tag(), idx, duration.as_double()));

#if 0
	if (!(m_control_reg[idx] & 0x02))
=======
	LOG("MC6840: reload_count(%d): output = %f\n", idx, duration.as_double());

#if 0
	if (!(m_control_reg[idx] & INTERNAL_CLK_EN))
>>>>>>> upstream/master
	{
		if (!m_external_clock[idx])
		{
			m_enabled[idx] = 0;
			m_timer[idx]->enable(false);
		}
	}
	else
#endif
	{
		m_enabled[idx] = 1;
		m_timer[idx]->adjust(duration);
		m_timer[idx]->enable(true);
	}
}



//-------------------------------------------------
//  read - Read Timer
//-------------------------------------------------

READ8_MEMBER( ptm6840_device::read )
{
	int val;

	switch ( offset )
	{
		case PTM_6840_CTRL1:
		{
			val = 0;
			break;
		}

		case PTM_6840_STATUS:
		{
<<<<<<< HEAD
			PLOG(("%s: MC6840 #%s: Status read = %04X\n", machine().describe_context(), tag(), m_status_reg));
=======
			LOG("%s: MC6840: Status read = %04X\n", machine().describe_context(), m_status_reg);
>>>>>>> upstream/master
			m_status_read_since_int |= m_status_reg & 0x07;
			val = m_status_reg;
			break;
		}

		case PTM_6840_MSBBUF1:
		case PTM_6840_MSBBUF2:
		case PTM_6840_MSBBUF3:
		{
			int idx = (offset - 2) / 2;
			int result = compute_counter(idx);

			// Clear the interrupt if the status has been read
			if (m_status_read_since_int & (1 << idx))
			{
				m_status_reg &= ~(1 << idx);
				update_interrupts();
			}

			m_lsb_buffer = result & 0xff;

<<<<<<< HEAD
			PLOG(("%s: MC6840 #%s: Counter %d read = %04X\n", machine().describe_context(), tag(), idx, result >> 8));
=======
			LOG("%s: MC6840: Counter %d read = %04X\n", machine().describe_context(), idx, result >> 8);
>>>>>>> upstream/master
			val = result >> 8;
			break;
		}

		case PTM_6840_LSB1:
		case PTM_6840_LSB2:
		case PTM_6840_LSB3:
		{
			val = m_lsb_buffer;
			break;
		}

		default:
		{
			val = 0;
			break;
		}

	}
	return val;
}


//-------------------------------------------------
//  write - Write Timer
//-------------------------------------------------

WRITE8_MEMBER( ptm6840_device::write )
{
	switch ( offset )
	{
		case PTM_6840_CTRL1:
		case PTM_6840_CTRL2:
		{
<<<<<<< HEAD
			int idx = (offset == 1) ? 1 : (m_control_reg[1] & 0x01) ? 0 : 2;
			UINT8 diffs = data ^ m_control_reg[idx];
			m_t3_divisor = (m_control_reg[2] & 0x01) ? 8 : 1;
			m_mode[idx] = (data >> 3) & 0x07;
			m_control_reg[idx] = data;

			PLOG(("MC6840 #%s : Control register %d selected\n", tag(), idx));
			PLOG(("operation mode   = %s\n", opmode[ m_mode[idx] ]));
			PLOG(("value            = %04X\n", m_control_reg[idx]));
			PLOG(("t3divisor        = %d\n", m_t3_divisor));

			if (!(m_control_reg[idx] & 0x80 ))
			{
				// Output cleared
				switch (idx)
				{
					case 0:
						m_out0_cb((offs_t)0, 0);
						break;
					case 1:
						m_out1_cb((offs_t)0, 0);
						break;
					case 2:
						m_out2_cb((offs_t)0, 0);
						break;
				}
			}
			// Reset?
			if (idx == 0 && (diffs & 0x01))
			{
				// Holding reset down
				if (data & 0x01)
				{
					PLOG(("MC6840 #%s : Timer reset\n", tag()));
=======
			int idx = (offset == 1) ? 1 : (m_control_reg[1] & CR1_SELECT) ? 0 : 2;
			uint8_t diffs = data ^ m_control_reg[idx];
			m_t3_divisor = (m_control_reg[2] & T3_PRESCALE_EN) ? 8 : 1;
			m_mode[idx] = (data >> 3) & 0x07;
			m_control_reg[idx] = data;

			LOG("MC6840: Control register %d selected\n", idx);
			LOG("operation mode   = %s\n", opmode[m_mode[idx]]);
			LOG("value            = %04X\n", m_control_reg[idx]);
			LOG("t3divisor        = %d\n", m_t3_divisor);

			if (diffs & INTERRUPT_EN)
				update_interrupts();

			if (!(m_control_reg[idx] & COUNT_OUT_EN))
			{
				// Output cleared
				m_out_cb[idx](0);
			}

			// Reset?
			if (idx == 0 && (diffs & RESET_TIMERS))
			{
				// Holding reset down
				if (data & RESET_TIMERS)
				{
					LOG("MC6840: Timer reset\n");
>>>>>>> upstream/master
					for (int i = 0; i < 3; i++)
					{
						m_timer[i]->enable(false);
						m_enabled[i] = 0;
					}
				}
				// Releasing reset
				else
				{
					for (int i = 0; i < 3; i++)
					{
						reload_count(i);
					}
				}

				m_status_reg = 0;
				update_interrupts();
<<<<<<< HEAD

				// Changing the clock source? (e.g. Zwackery)
				if (diffs & 0x02)
				{
					reload_count(idx);
				}
=======
			}

			// Changing the clock source? (e.g. Zwackery)
			if (diffs & INTERNAL_CLK_EN)
			{
				reload_count(idx);
>>>>>>> upstream/master
			}
			break;
		}

		case PTM_6840_MSBBUF1:
		case PTM_6840_MSBBUF2:
		case PTM_6840_MSBBUF3:
		{
<<<<<<< HEAD
			PLOG(("MC6840 #%s msbbuf%d = %02X\n", tag(), offset / 2, data));
=======
			LOG("MC6840 msbbuf%d = %02X\n", offset / 2, data);
>>>>>>> upstream/master
			m_msb_buffer = data;
			break;
		}

		case PTM_6840_LSB1:
		case PTM_6840_LSB2:
		case PTM_6840_LSB3:
		{
			int idx = (offset - 3) / 2;
			m_latch[idx] = (m_msb_buffer << 8) | (data & 0xff);

			// Clear the interrupt
			m_status_reg &= ~(1 << idx);
			update_interrupts();

			// Reload the count if in an appropriate mode
<<<<<<< HEAD
			if (!(m_control_reg[idx] & 0x10))
=======
			if (!(m_control_reg[idx] & 0x10) || (m_control_reg[0] & RESET_TIMERS))
>>>>>>> upstream/master
			{
				reload_count(idx);
			}

<<<<<<< HEAD
			PLOG(("%s:MC6840 #%s: Counter %d latch = %04X\n", machine().describe_context(), tag(), idx, m_latch[idx]));
=======
			LOG("%s:MC6840: Counter %d latch = %04X\n", machine().describe_context(), idx, m_latch[idx]);
>>>>>>> upstream/master
			break;
		}
	}
}


//-------------------------------------------------
//  timeout - Called if timer is mature
//-------------------------------------------------

void ptm6840_device::timeout(int idx)
{
<<<<<<< HEAD
	PLOG(("**ptm6840 %s t%d timeout**\n", tag(), idx));
=======
	LOG("**ptm6840 t%d timeout**\n", idx);
>>>>>>> upstream/master

	// Set the interrupt flag
	m_status_reg |= (1 << idx);
	m_status_read_since_int &= ~(1 << idx);
	update_interrupts();

<<<<<<< HEAD
	if ( m_control_reg[idx] & 0x80 )
	{
		if ((m_mode[idx] == 0)||(m_mode[idx] == 2))
		{
			m_output[idx] = m_output[idx] ? 0 : 1;
			PLOG(("**ptm6840 %s t%d output %d **\n", tag(), idx, m_output[idx]));

			switch (idx)
			{
				case 0:
					m_out0_cb((offs_t)0, m_output[0]);
					break;
				case 1:
					m_out1_cb((offs_t)0, m_output[1]);
					break;
				case 2:
					m_out2_cb((offs_t)0, m_output[2]);
					break;
			}
		}
		if ((m_mode[idx] == 4)||(m_mode[idx] == 6))
		{
			if (!m_fired[idx])
			{
				m_output[idx] = 1;
				PLOG(("**ptm6840 %s t%d output %d **\n", tag(), idx, m_output[idx]));

				switch (idx)
				{
					case 0:
						m_out0_cb((offs_t)0, m_output[0]);
						break;
					case 1:
						m_out1_cb((offs_t)0, m_output[1]);
						break;
					case 2:
						m_out2_cb((offs_t)0, m_output[2]);
						break;
				}

				// No changes in output until reinit
				m_fired[idx] = 1;

				m_status_reg |= (1 << idx);
				m_status_read_since_int &= ~(1 << idx);
				update_interrupts();
			}
=======
	if (m_control_reg[idx] & COUNT_OUT_EN)
	{
		switch (m_mode[idx])
		{
			case 0:
			case 2:
				m_output[idx] = m_output[idx] ^ 1;
				LOG("**ptm6840 t%d output %d **\n", idx, m_output[idx]);
				m_out_cb[idx](m_output[idx]);
				break;

			case 4:
			case 6:
				if (!m_fired[idx])
				{
					m_output[idx] = 1;
					LOG("**ptm6840 t%d output %d **\n", idx, m_output[idx]);

					m_out_cb[idx](m_output[idx]);

					// No changes in output until reinit
					m_fired[idx] = 1;

					m_status_reg |= (1 << idx);
					m_status_read_since_int &= ~(1 << idx);
					update_interrupts();
				}
				break;
>>>>>>> upstream/master
		}
	}
	m_enabled[idx]= 0;
	reload_count(idx);
}


//-------------------------------------------------
//  set_gate - set gate status (0 or 1)
//-------------------------------------------------

void ptm6840_device::set_gate(int idx, int state)
{
	if ((m_mode[idx] & 1) == 0)
	{
		if (state == 0 && m_gate[idx])
		{
			reload_count(idx);
		}
	}
	m_gate[idx] = state;
}

WRITE_LINE_MEMBER( ptm6840_device::set_g1 ) { set_gate(0, state); }
WRITE_LINE_MEMBER( ptm6840_device::set_g2 ) { set_gate(1, state); }
WRITE_LINE_MEMBER( ptm6840_device::set_g3 ) { set_gate(2, state); }


//-------------------------------------------------
//  set_clock - set clock status (0 or 1)
//-------------------------------------------------

void ptm6840_device::set_clock(int idx, int state)
{
	m_clk[idx] = state;

<<<<<<< HEAD
	if (!(m_control_reg[idx] & 0x02))
=======
	if (!(m_control_reg[idx] & INTERNAL_CLK_EN))
>>>>>>> upstream/master
	{
		if (state)
		{
			tick(idx, 1);
		}
	}
}

WRITE_LINE_MEMBER( ptm6840_device::set_c1 ) { set_clock(0, state); }
WRITE_LINE_MEMBER( ptm6840_device::set_c2 ) { set_clock(1, state); }
WRITE_LINE_MEMBER( ptm6840_device::set_c3 ) { set_clock(2, state); }


//-------------------------------------------------
//  set_ext_clock - set external clock frequency
//-------------------------------------------------

void ptm6840_device::set_ext_clock(int counter, double clock)
{
	m_external_clock[counter] = clock;

<<<<<<< HEAD
	if (!(m_control_reg[counter] & 0x02))
=======
	if (!(m_control_reg[counter] & INTERNAL_CLK_EN))
>>>>>>> upstream/master
	{
		if (!m_external_clock[counter])
		{
			m_enabled[counter] = 0;
			m_timer[counter]->enable(false);
		}
	}
	else
	{
		int count;
		attotime duration;

		// Determine the number of clock periods before we expire
		count = m_counter[counter];

<<<<<<< HEAD
		if (m_control_reg[counter] & 0x04)
=======
		if (m_control_reg[counter] & COUNT_MODE_8BIT)
>>>>>>> upstream/master
		{
			count = ((count >> 8) + 1) * ((count & 0xff) + 1);
		}
		else
		{
			count = count + 1;
		}

		duration = attotime::from_hz(clock) * count;

		if (counter == 2)
		{
			duration *= m_t3_divisor;
		}

		m_enabled[counter] = 1;
		m_timer[counter]->adjust(duration);
		m_timer[counter]->enable(true);
	}
}
