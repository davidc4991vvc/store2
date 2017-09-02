// license:BSD-3-Clause
<<<<<<< HEAD
// copyright-holders:Nathan Woods
=======
// copyright-holders:Aaron Giles, Nathan Woods
>>>>>>> upstream/master
/**********************************************************************

    Motorola 6821 PIA interface and emulation

**********************************************************************/

#include "emu.h"
#include "6821pia.h"

<<<<<<< HEAD

=======
>>>>>>> upstream/master
//**************************************************************************
//  MACROS
//**************************************************************************

<<<<<<< HEAD
#define VERBOSE 1

#define LOG(x)  do { if (VERBOSE) logerror x; } while (0)
=======
#define LOG_GENERAL 0x01
#define LOG_SETUP   0x02
#define LOG_CA1     0x08

//#define VERBOSE (LOG_SETUP | LOG_GENERAL)

#include "logmacro.h"
#define LOGSETUP(...) LOGMASKED(LOG_SETUP,   __VA_ARGS__)
#define LOGCA1(...)   LOGMASKED(LOG_CA1,     __VA_ARGS__)
>>>>>>> upstream/master

#define PIA_IRQ1                (0x80)
#define PIA_IRQ2                (0x40)

<<<<<<< HEAD
#define IRQ1_ENABLED(c)         ( (((c) >> 0) & 0x01))
#define C1_LOW_TO_HIGH(c)       ( (((c) >> 1) & 0x01))
#define C1_HIGH_TO_LOW(c)       (!(((c) >> 1) & 0x01))
#define OUTPUT_SELECTED(c)      ( (((c) >> 2) & 0x01))
#define IRQ2_ENABLED(c)         ( (((c) >> 3) & 0x01))
#define STROBE_E_RESET(c)       ( (((c) >> 3) & 0x01))
#define STROBE_C1_RESET(c)      (!(((c) >> 3) & 0x01))
#define C2_SET(c)               ( (((c) >> 3) & 0x01))
#define C2_LOW_TO_HIGH(c)       ( (((c) >> 4) & 0x01))
#define C2_HIGH_TO_LOW(c)       (!(((c) >> 4) & 0x01))
#define C2_SET_MODE(c)          ( (((c) >> 4) & 0x01))
#define C2_STROBE_MODE(c)       (!(((c) >> 4) & 0x01))
#define C2_OUTPUT(c)            ( (((c) >> 5) & 0x01))
#define C2_INPUT(c)             (!(((c) >> 5) & 0x01))

=======
>>>>>>> upstream/master

//**************************************************************************
//  LIVE DEVICE
//**************************************************************************

// device type definition
<<<<<<< HEAD
const device_type PIA6821 = &device_creator<pia6821_device>;
=======
DEFINE_DEVICE_TYPE(PIA6821, pia6821_device, "pia6821", "6821 PIA")
>>>>>>> upstream/master


//-------------------------------------------------
//  pia6821_device - constructor
//-------------------------------------------------

<<<<<<< HEAD
pia6821_device::pia6821_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock)
	: device_t(mconfig, PIA6821, "6821 PIA", tag, owner, clock, "pia6821", __FILE__),
=======
pia6821_device::pia6821_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock)
	: device_t(mconfig, PIA6821, tag, owner, clock),
>>>>>>> upstream/master
		m_in_a_handler(*this),
		m_in_b_handler(*this),
		m_in_ca1_handler(*this),
		m_in_cb1_handler(*this),
		m_in_ca2_handler(*this),
		m_out_a_handler(*this),
		m_out_b_handler(*this),
		m_ca2_handler(*this),
		m_cb2_handler(*this),
		m_irqa_handler(*this),
		m_irqb_handler(*this), m_in_a(0),
		m_in_ca1(0), m_in_ca2(0), m_out_a(0), m_out_ca2(0), m_port_a_z_mask(0), m_ddr_a(0),
		m_ctl_a(0), m_irq_a1(0), m_irq_a2(0),
		m_irq_a_state(0), m_in_b(0),
		m_in_cb1(0), m_in_cb2(0), m_out_b(0), m_out_cb2(0), m_last_out_cb2_z(0), m_ddr_b(0),
		m_ctl_b(0), m_irq_b1(0), m_irq_b2(0),
		m_irq_b_state(0), m_in_a_pushed(false), m_out_a_needs_pulled(false), m_in_ca1_pushed(false),
		m_in_ca2_pushed(false), m_out_ca2_needs_pulled(false), m_in_b_pushed(false), m_out_b_needs_pulled(false),
		m_in_cb1_pushed(false), m_in_cb2_pushed(false), m_out_cb2_needs_pulled(false), m_logged_port_a_not_connected(false),
		m_logged_port_b_not_connected(false), m_logged_ca1_not_connected(false), m_logged_ca2_not_connected(false),
		m_logged_cb1_not_connected(false), m_logged_cb2_not_connected(false)
{
}


//-------------------------------------------------
//  device_start - device-specific startup
//-------------------------------------------------

void pia6821_device::device_start()
{
	// resolve callbacks
	m_in_a_handler.resolve();
	m_in_b_handler.resolve();
	m_in_ca1_handler.resolve();
	m_in_cb1_handler.resolve();
	m_in_ca2_handler.resolve();
	m_out_a_handler.resolve();
	m_out_b_handler.resolve();
	m_ca2_handler.resolve();
	m_cb2_handler.resolve();
	m_irqa_handler.resolve_safe();
	m_irqb_handler.resolve_safe();

	save_item(NAME(m_in_a));
	save_item(NAME(m_in_ca1));
	save_item(NAME(m_in_ca2));
	save_item(NAME(m_out_a));
	save_item(NAME(m_out_ca2));
	save_item(NAME(m_port_a_z_mask));
	save_item(NAME(m_ddr_a));
	save_item(NAME(m_ctl_a));
	save_item(NAME(m_irq_a1));
	save_item(NAME(m_irq_a2));
	save_item(NAME(m_irq_a_state));
	save_item(NAME(m_in_b));
	save_item(NAME(m_in_cb1));
	save_item(NAME(m_in_cb2));
	save_item(NAME(m_out_b));
	save_item(NAME(m_out_cb2));
	save_item(NAME(m_last_out_cb2_z));
	save_item(NAME(m_ddr_b));
	save_item(NAME(m_ctl_b));
	save_item(NAME(m_irq_b1));
	save_item(NAME(m_irq_b2));
	save_item(NAME(m_irq_b_state));
	save_item(NAME(m_in_a_pushed));
	save_item(NAME(m_out_a_needs_pulled));
	save_item(NAME(m_in_ca1_pushed));
	save_item(NAME(m_in_ca2_pushed));
	save_item(NAME(m_out_ca2_needs_pulled));
	save_item(NAME(m_in_b_pushed));
	save_item(NAME(m_out_b_needs_pulled));
	save_item(NAME(m_in_cb1_pushed));
	save_item(NAME(m_in_cb2_pushed));
	save_item(NAME(m_out_cb2_needs_pulled));
}


//-------------------------------------------------
//  device_reset - device-specific reset
//-------------------------------------------------

void pia6821_device::device_reset()
{
	//
	// set default read values.
	//
	// ports A,CA1,CA2 default to 1
	// ports B,CB1,CB2 are three-state and undefined (set to 0)
	//
	m_in_a = 0xff;
<<<<<<< HEAD
	m_in_ca1 = TRUE;
	m_in_ca2 = TRUE;
=======
	m_in_ca1 = true;
	m_in_ca2 = true;
>>>>>>> upstream/master
	m_out_a = 0;
	m_out_ca2 = 0;
	m_port_a_z_mask = 0;
	m_ddr_a = 0;
	m_ctl_a = 0;
	m_irq_a1 = 0;
	m_irq_a2 = 0;
	m_irq_a_state = 0;
	m_in_b = 0;
	m_in_cb1 = 0;
	m_in_cb2 = 0;
	m_out_b = 0;
	m_out_cb2 = 0;
	m_last_out_cb2_z = 0;
	m_ddr_b = 0;
	m_ctl_b = 0;
	m_irq_b1 = 0;
	m_irq_b2 = 0;
	m_irq_b_state = 0;
	m_in_a_pushed = false;
	m_out_a_needs_pulled = false;
	m_in_ca1_pushed = false;
	m_in_ca2_pushed = false;
	m_out_ca2_needs_pulled = false;
	m_in_b_pushed = false;
	m_out_b_needs_pulled = false;
	m_in_cb1_pushed = false;
	m_in_cb2_pushed = false;
	m_out_cb2_needs_pulled = false;
	m_logged_port_a_not_connected = false;
	m_logged_port_b_not_connected = false;
	m_logged_ca1_not_connected = false;
	m_logged_ca2_not_connected = false;
	m_logged_cb1_not_connected = false;
	m_logged_cb2_not_connected = false;


	// clear the IRQs
<<<<<<< HEAD
	m_irqa_handler(FALSE);
	m_irqb_handler(FALSE);
=======
	m_irqa_handler(false);
	m_irqb_handler(false);
>>>>>>> upstream/master
}


//-------------------------------------------------
//  update_interrupts
//-------------------------------------------------

void pia6821_device::update_interrupts()
{
	// start with IRQ A
<<<<<<< HEAD
	int new_state = (m_irq_a1 && IRQ1_ENABLED(m_ctl_a)) || (m_irq_a2 && IRQ2_ENABLED(m_ctl_a));
=======
	int new_state = (m_irq_a1 && irq1_enabled(m_ctl_a)) || (m_irq_a2 && irq2_enabled(m_ctl_a));
>>>>>>> upstream/master

	if (new_state != m_irq_a_state)
	{
		m_irq_a_state = new_state;
		m_irqa_handler(m_irq_a_state);
	}

	// then do IRQ B
<<<<<<< HEAD
	new_state = (m_irq_b1 && IRQ1_ENABLED(m_ctl_b)) || (m_irq_b2 && IRQ2_ENABLED(m_ctl_b));
=======
	new_state = (m_irq_b1 && irq1_enabled(m_ctl_b)) || (m_irq_b2 && irq2_enabled(m_ctl_b));
>>>>>>> upstream/master

	if (new_state != m_irq_b_state)
	{
		m_irq_b_state = new_state;
		m_irqb_handler(m_irq_b_state);
	}
}


//-------------------------------------------------
//  get_in_a_value
//-------------------------------------------------

<<<<<<< HEAD
UINT8 pia6821_device::get_in_a_value()
{
	UINT8 port_a_data = 0;
	UINT8 ret;
=======
uint8_t pia6821_device::get_in_a_value()
{
	uint8_t port_a_data = 0;
	uint8_t ret;
>>>>>>> upstream/master

	// update the input
	if (!m_in_a_handler.isnull())
	{
		port_a_data = m_in_a_handler(0);
	}
	else
	{
		if (m_in_a_pushed)
		{
			port_a_data = m_in_a;
		}
		else
		{
			// mark all pins disconnected
			m_port_a_z_mask = 0xff;

			if (!m_logged_port_a_not_connected && (m_ddr_a != 0xff))
			{
<<<<<<< HEAD
				logerror("PIA #%s: Warning! No port A read handler. Assuming pins 0x%02X not connected\n", tag(), m_ddr_a ^ 0xff);
=======
				logerror("Warning! No port A read handler. Assuming pins 0x%02X not connected\n", m_ddr_a ^ 0xff);
>>>>>>> upstream/master
				m_logged_port_a_not_connected = true;
			}
		}
	}

	// - connected pins are always read
	// - disconnected pins read the output buffer in output mode
	// - disconnected pins are HI in input mode
	ret = (~m_port_a_z_mask             & port_a_data) |
			( m_port_a_z_mask &  m_ddr_a & m_out_a) |
			( m_port_a_z_mask & ~m_ddr_a);

	return ret;
}


//-------------------------------------------------
//  get_in_b_value
//-------------------------------------------------

<<<<<<< HEAD
UINT8 pia6821_device::get_in_b_value()
{
	UINT8 ret;
=======
uint8_t pia6821_device::get_in_b_value()
{
	uint8_t ret;
>>>>>>> upstream/master

	if (m_ddr_b == 0xff)
	{
		// all output, just return buffer
		ret = m_out_b;
	}
	else
	{
<<<<<<< HEAD
		UINT8 port_b_data;
=======
		uint8_t port_b_data;
>>>>>>> upstream/master

		// update the input
		if (!m_in_b_handler.isnull())
		{
			port_b_data = m_in_b_handler(0);
		}
		else
		{
			if (m_in_b_pushed)
			{
				port_b_data = m_in_b;
			}
			else
			{
				if (!m_logged_port_b_not_connected && (m_ddr_b != 0xff))
				{
<<<<<<< HEAD
					logerror("PIA #%s: Error! No port B read handler. Three-state pins 0x%02X are undefined\n", tag(), m_ddr_b ^ 0xff);
=======
					logerror("Error! No port B read handler. Three-state pins 0x%02X are undefined\n", m_ddr_b ^ 0xff);
>>>>>>> upstream/master
					m_logged_port_b_not_connected = true;
				}

				// undefined -- need to return something
				port_b_data = 0x00;
			}
		}

		// the DDR determines if the pin or the output buffer is read
		ret = (m_out_b & m_ddr_b) | (port_b_data & ~m_ddr_b);
	}

	return ret;
}


//-------------------------------------------------
//  get_out_a_value
//-------------------------------------------------

<<<<<<< HEAD
UINT8 pia6821_device::get_out_a_value()
{
	UINT8 ret;
=======
uint8_t pia6821_device::get_out_a_value()
{
	uint8_t ret;
>>>>>>> upstream/master

	if (m_ddr_a == 0xff)
	{
		// all output
		ret = m_out_a;
	}
	else
	{
		// input pins don't change
		ret = (m_out_a & m_ddr_a) | (get_in_a_value() & ~m_ddr_a);
	}

	return ret;
}


//-------------------------------------------------
//  get_out_b_value
//-------------------------------------------------

<<<<<<< HEAD
UINT8 pia6821_device::get_out_b_value()
=======
uint8_t pia6821_device::get_out_b_value()
>>>>>>> upstream/master
{
	// input pins are high-impedance - we just send them as zeros for backwards compatibility
	return m_out_b & m_ddr_b;
}


//-------------------------------------------------
//  set_out_ca2
//-------------------------------------------------

void pia6821_device::set_out_ca2(int data)
{
	if (data != m_out_ca2)
	{
		m_out_ca2 = data;

		// send to output function
		if (!m_ca2_handler.isnull())
		{
			m_ca2_handler(m_out_ca2);
		}
		else
		{
			if (m_out_ca2_needs_pulled)
			{
<<<<<<< HEAD
				logerror("PIA #%s: Warning! No port CA2 write handler. Previous value has been lost!\n", tag());
=======
				logerror("Warning! No port CA2 write handler. Previous value has been lost!\n");
>>>>>>> upstream/master
			}

			m_out_ca2_needs_pulled = true;
		}
	}
}


//-------------------------------------------------
//  set_out_cb2
//-------------------------------------------------

void pia6821_device::set_out_cb2(int data)
{
	int z = cb2_output_z();

	if ((data != m_out_cb2) || (z != m_last_out_cb2_z))
	{
		m_out_cb2 = data;
		m_last_out_cb2_z = z;

		// send to output function
		if (!m_cb2_handler.isnull())
		{
			m_cb2_handler(m_out_cb2);
		}
		else
		{
			if (m_out_cb2_needs_pulled)
			{
<<<<<<< HEAD
				logerror("PIA #%s: Warning! No port CB2 write handler. Previous value has been lost!\n", tag());
=======
				logerror("Warning! No port CB2 write handler. Previous value has been lost!\n");
>>>>>>> upstream/master
			}

			m_out_cb2_needs_pulled = true;
		}
	}
}


//-------------------------------------------------
//  port_a_r
//-------------------------------------------------

<<<<<<< HEAD
UINT8 pia6821_device::port_a_r()
{
	UINT8 ret = get_in_a_value();

	// IRQ flags implicitly cleared by a read
	m_irq_a1 = FALSE;
	m_irq_a2 = FALSE;
	update_interrupts();

	// CA2 is configured as output and in read strobe mode
	if(C2_OUTPUT(m_ctl_a) && C2_STROBE_MODE(m_ctl_a))
	{
		// this will cause a transition low
		set_out_ca2(FALSE);

		// if the CA2 strobe is cleared by the E, reset it right away
		if(STROBE_E_RESET(m_ctl_a))
		{
			set_out_ca2(TRUE);
		}
	}

	LOG(("PIA #%s: port A read = %02X\n", tag(), ret));
=======
uint8_t pia6821_device::port_a_r()
{
	uint8_t ret = get_in_a_value();

	// IRQ flags implicitly cleared by a read
	m_irq_a1 = false;
	m_irq_a2 = false;
	update_interrupts();

	// CA2 is configured as output and in read strobe mode
	if(c2_output(m_ctl_a) && c2_strobe_mode(m_ctl_a))
	{
		// this will cause a transition low
		set_out_ca2(false);

		// if the CA2 strobe is cleared by the E, reset it right away
		if(strobe_e_reset(m_ctl_a))
		{
			set_out_ca2(true);
		}
	}

	LOG("PIA port A read = %02X\n", ret);
>>>>>>> upstream/master

	return ret;
}


//-------------------------------------------------
//  ddr_a_r
//-------------------------------------------------

<<<<<<< HEAD
UINT8 pia6821_device::ddr_a_r()
{
	UINT8 ret = m_ddr_a;

	LOG(("PIA #%s: DDR A read = %02X\n", tag(), ret));
=======
uint8_t pia6821_device::ddr_a_r()
{
	uint8_t ret = m_ddr_a;

	LOG("PIA DDR A read = %02X\n", ret);
>>>>>>> upstream/master

	return ret;
}


//-------------------------------------------------
//  port_b_r
//-------------------------------------------------

<<<<<<< HEAD
UINT8 pia6821_device::port_b_r()
{
	UINT8 ret = get_in_b_value();
=======
uint8_t pia6821_device::port_b_r()
{
	uint8_t ret = get_in_b_value();
>>>>>>> upstream/master

	// This read will implicitly clear the IRQ B1 flag.  If CB2 is in write-strobe
	// mode with CB1 restore, and a CB1 active transition set the flag,
	// clearing it will cause CB2 to go high again.  Note that this is different
	// from what happens with port A.
<<<<<<< HEAD
	if(m_irq_b1 && C2_STROBE_MODE(m_ctl_b) && STROBE_C1_RESET(m_ctl_b))
	{
		set_out_cb2(TRUE);
	}

	// IRQ flags implicitly cleared by a read
	m_irq_b1 = FALSE;
	m_irq_b2 = FALSE;
	update_interrupts();

	LOG(("PIA #%s: port B read = %02X\n", tag(), ret));
=======
	if(m_irq_b1 && c2_strobe_mode(m_ctl_b) && strobe_c1_reset(m_ctl_b))
	{
		set_out_cb2(true);
	}

	// IRQ flags implicitly cleared by a read
	m_irq_b1 = false;
	m_irq_b2 = false;
	update_interrupts();

	LOG("PIA port B read = %02X\n", ret);
>>>>>>> upstream/master

	return ret;
}


//-------------------------------------------------
//  ddr_b_r
//-------------------------------------------------

<<<<<<< HEAD
UINT8 pia6821_device::ddr_b_r()
{
	UINT8 ret = m_ddr_b;

	LOG(("PIA #%s: DDR B read = %02X\n", tag(), ret));
=======
uint8_t pia6821_device::ddr_b_r()
{
	uint8_t ret = m_ddr_b;

	LOG("PIA DDR B read = %02X\n", ret);
>>>>>>> upstream/master

	return ret;
}


//-------------------------------------------------
//  control_a_r
//-------------------------------------------------

<<<<<<< HEAD
UINT8 pia6821_device::control_a_r()
{
	UINT8 ret;
=======
uint8_t pia6821_device::control_a_r()
{
	uint8_t ret;
>>>>>>> upstream/master

	// update CA1 & CA2 if callback exists, these in turn may update IRQ's
	if (!m_in_ca1_handler.isnull())
	{
		ca1_w(m_in_ca1_handler());
	}
	else if(!m_logged_ca1_not_connected && (!m_in_ca1_pushed))
	{
<<<<<<< HEAD
		logerror("PIA #%s: Warning! No CA1 read handler. Assuming pin not connected\n", tag());
=======
		logerror("Warning! No CA1 read handler. Assuming pin not connected\n");
>>>>>>> upstream/master
		m_logged_ca1_not_connected = true;
	}

	if (!m_in_ca2_handler.isnull())
	{
		ca2_w(m_in_ca2_handler());
	}
<<<<<<< HEAD
	else if ( !m_logged_ca2_not_connected && C2_INPUT(m_ctl_a) && !m_in_ca2_pushed)
	{
		logerror("PIA #%s: Warning! No CA2 read handler. Assuming pin not connected\n", tag());
=======
	else if ( !m_logged_ca2_not_connected && c2_input(m_ctl_a) && !m_in_ca2_pushed)
	{
		logerror("Warning! No CA2 read handler. Assuming pin not connected\n");
>>>>>>> upstream/master
		m_logged_ca2_not_connected = true;
	}

	// read control register
	ret = m_ctl_a;

	// set the IRQ flags if we have pending IRQs
	if(m_irq_a1)
	{
		ret |= PIA_IRQ1;
	}

<<<<<<< HEAD
	if(m_irq_a2 && C2_INPUT(m_ctl_a))
=======
	if(m_irq_a2 && c2_input(m_ctl_a))
>>>>>>> upstream/master
	{
		ret |= PIA_IRQ2;
	}

<<<<<<< HEAD
	LOG(("PIA #%s: control A read = %02X\n", tag(), ret));
=======
	LOG("PIA control A read = %02X\n", ret);
>>>>>>> upstream/master

	return ret;
}


//-------------------------------------------------
//  control_b_r
//-------------------------------------------------

<<<<<<< HEAD
UINT8 pia6821_device::control_b_r()
{
	UINT8 ret;
=======
uint8_t pia6821_device::control_b_r()
{
	uint8_t ret;
>>>>>>> upstream/master

	// update CB1 & CB2 if callback exists, these in turn may update IRQ's
	if(!m_in_cb1_handler.isnull())
	{
		cb1_w(m_in_cb1_handler());
	}
	else if(!m_logged_cb1_not_connected && !m_in_cb1_pushed)
	{
<<<<<<< HEAD
		logerror("PIA #%s: Error! no CB1 read handler. Three-state pin is undefined\n", tag());
		m_logged_cb1_not_connected = true;
	}

	if(!m_logged_cb2_not_connected && C2_INPUT(m_ctl_b) && !m_in_cb2_pushed)
	{
		logerror("PIA #%s: Error! Three-state pin is undefined\n", tag());
=======
		logerror("Error! no CB1 read handler. Three-state pin is undefined\n");
		m_logged_cb1_not_connected = true;
	}

	if(!m_logged_cb2_not_connected && c2_input(m_ctl_b) && !m_in_cb2_pushed)
	{
		logerror("Error! Three-state pin is undefined\n");
>>>>>>> upstream/master
		m_logged_cb2_not_connected = true;
	}

	// read control register
	ret = m_ctl_b;

	// set the IRQ flags if we have pending IRQs
	if(m_irq_b1)
	{
		ret |= PIA_IRQ1;
	}

<<<<<<< HEAD
	if(m_irq_b2 && C2_INPUT(m_ctl_b))
=======
	if(m_irq_b2 && c2_input(m_ctl_b))
>>>>>>> upstream/master
	{
		ret |= PIA_IRQ2;
	}

<<<<<<< HEAD
	LOG(("PIA #%s: control B read = %02X\n", tag(), ret));
=======
	LOG("PIA control B read = %02X\n", ret);
>>>>>>> upstream/master

	return ret;
}


//-------------------------------------------------
//  read
//-------------------------------------------------

<<<<<<< HEAD
UINT8 pia6821_device::reg_r(UINT8 offset)
{
	UINT8 ret;
=======
uint8_t pia6821_device::reg_r(uint8_t offset)
{
	uint8_t ret;
>>>>>>> upstream/master

	switch (offset & 0x03)
	{
		default: // impossible
		case 0x00:
<<<<<<< HEAD
			if (OUTPUT_SELECTED(m_ctl_a))
=======
			if (output_selected(m_ctl_a))
>>>>>>> upstream/master
			{
				ret = port_a_r();
			}
			else
			{
				ret = ddr_a_r();
			}
			break;

		case 0x01:
			ret = control_a_r();
			break;

		case 0x02:
<<<<<<< HEAD
			if (OUTPUT_SELECTED(m_ctl_b))
=======
			if (output_selected(m_ctl_b))
>>>>>>> upstream/master
			{
				ret = port_b_r();
			}
			else
			{
				ret = ddr_b_r();
			}
			break;

		case 0x03:
			ret = control_b_r();
			break;
	}

	return ret;
}



//-------------------------------------------------
//  send_to_out_a_func
//-------------------------------------------------

void pia6821_device::send_to_out_a_func(const char* message)
{
	// input pins are pulled high
<<<<<<< HEAD
	UINT8 data = get_out_a_value();

	LOG(("PIA #%s: %s = %02X\n", tag(), message, data));
=======
	uint8_t data = get_out_a_value();

	LOG("PIA %s = %02X\n", message, data);
>>>>>>> upstream/master

	if(!m_out_a_handler.isnull())
	{
		m_out_a_handler((offs_t) 0, data);
	}
	else
	{
		if(m_out_a_needs_pulled)
		{
<<<<<<< HEAD
			logerror("PIA #%s: Warning! No port A write handler. Previous value has been lost!\n", tag());
=======
			logerror("Warning! No port A write handler. Previous value has been lost!\n");
>>>>>>> upstream/master
		}

		m_out_a_needs_pulled = true;
	}
}


//-------------------------------------------------
//  send_to_out_b_func
//-------------------------------------------------

void pia6821_device::send_to_out_b_func(const char* message)
{
	// input pins are high-impedance - we just send them as zeros for backwards compatibility
<<<<<<< HEAD
	UINT8 data = get_out_b_value();

	LOG(("PIA #%s: %s = %02X\n", tag(), message, data));
=======
	uint8_t data = get_out_b_value();

	LOG("PIA %s = %02X\n", message, data);
>>>>>>> upstream/master

	if(!m_out_b_handler.isnull())
	{
		m_out_b_handler((offs_t)0, data);
	}
	else
	{
		if(m_out_b_needs_pulled)
		{
<<<<<<< HEAD
			logerror("PIA #%s: Warning! No port B write handler. Previous value has been lost!\n", tag());
=======
			logerror("Warning! No port B write handler. Previous value has been lost!\n");
>>>>>>> upstream/master
		}

		m_out_b_needs_pulled = true;
	}
}


//-------------------------------------------------
//  port_a_w
//-------------------------------------------------

<<<<<<< HEAD
void pia6821_device::port_a_w(UINT8 data)
=======
void pia6821_device::port_a_w(uint8_t data)
>>>>>>> upstream/master
{
	// buffer the output value
	m_out_a = data;

	send_to_out_a_func("port A write");
}


//-------------------------------------------------
//  ddr_a_w
//-------------------------------------------------

<<<<<<< HEAD
void pia6821_device::ddr_a_w(UINT8 data)
{
	if(data == 0x00)
	{
		LOG(("PIA #%s: DDR A write = %02X (input mode)\n", tag(), data));
	}
	else if(data == 0xff)
	{
		LOG(("PIA #%s: DDR A write = %02X (output mode)\n", tag(), data));
	}
	else
	{
		LOG(("PIA #%s: DDR A write = %02X (mixed mode)\n", tag(), data));
=======
void pia6821_device::ddr_a_w(uint8_t data)
{
	if(data == 0x00)
	{
		LOGSETUP("PIA DDR A write = %02X (input mode)\n", data);
	}
	else if(data == 0xff)
	{
		LOGSETUP("PIA DDR A write = %02X (output mode)\n", data);
	}
	else
	{
		LOGSETUP("PIA DDR A write = %02X (mixed mode)\n", data);
>>>>>>> upstream/master
	}

	if(m_ddr_a != data)
	{
		// DDR changed, call the callback again
		m_ddr_a = data;
		m_logged_port_a_not_connected = false;
		send_to_out_a_func("port A write due to DDR change");
	}
}


//-------------------------------------------------
//  port_b_w
//-------------------------------------------------

<<<<<<< HEAD
void pia6821_device::port_b_w(UINT8 data)
=======
void pia6821_device::port_b_w(uint8_t data)
>>>>>>> upstream/master
{
	// buffer the output value
	m_out_b = data;

	send_to_out_b_func("port B write");

	// CB2 in write strobe mode
<<<<<<< HEAD
	if(C2_STROBE_MODE(m_ctl_b))
	{
		// this will cause a transition low
		set_out_cb2(FALSE);

		// if the CB2 strobe is cleared by the E, reset it right away
		if(STROBE_E_RESET(m_ctl_b))
		{
			set_out_cb2(TRUE);
=======
	if(c2_strobe_mode(m_ctl_b))
	{
		// this will cause a transition low
		set_out_cb2(false);

		// if the CB2 strobe is cleared by the E, reset it right away
		if(strobe_e_reset(m_ctl_b))
		{
			set_out_cb2(true);
>>>>>>> upstream/master
		}
	}
}


//-------------------------------------------------
//  ddr_b_w
//-------------------------------------------------

<<<<<<< HEAD
void pia6821_device::ddr_b_w(UINT8 data)
{
	if (data == 0x00)
	{
		LOG(("PIA #%s: DDR B write = %02X (input mode)\n", tag(), data));
	}
	else if (data == 0xff)
	{
		LOG(("PIA #%s: DDR B write = %02X (output mode)\n", tag(), data));
	}
	else
	{
		LOG(("PIA #%s: DDR B write = %02X (mixed mode)\n", tag(), data));
=======
void pia6821_device::ddr_b_w(uint8_t data)
{
	if (data == 0x00)
	{
		LOGSETUP("PIA DDR B write = %02X (input mode)\n", data);
	}
	else if (data == 0xff)
	{
		LOGSETUP("PIA DDR B write = %02X (output mode)\n", data);
	}
	else
	{
		LOGSETUP("PIA DDR B write = %02X (mixed mode)\n", data);
>>>>>>> upstream/master
	}

	if(m_ddr_b != data)
	{
		// DDR changed, call the callback again
		m_ddr_b = data;
		m_logged_port_b_not_connected = false;
		send_to_out_b_func("port B write due to DDR change");
	}
}


//-------------------------------------------------
//  control_a_w
//-------------------------------------------------

<<<<<<< HEAD
void pia6821_device::control_a_w(UINT8 data)
=======
void pia6821_device::control_a_w(uint8_t data)
>>>>>>> upstream/master
{
	// bit 7 and 6 are read only
	data &= 0x3f;

<<<<<<< HEAD
	LOG(("PIA #%s: control A write = %02X\n", tag(), data));
=======
	LOGSETUP("PIA control A write = %02X\n", data);
>>>>>>> upstream/master

	// update the control register
	m_ctl_a = data;

	// CA2 is configured as output
<<<<<<< HEAD
	if(C2_OUTPUT(m_ctl_a))
	{
		int temp;

		if(C2_SET_MODE(m_ctl_a))
		{
			// set/reset mode - bit value determines the new output
			temp = C2_SET(m_ctl_a);
=======
	if(c2_output(m_ctl_a))
	{
		bool temp;

		if(c2_set_mode(m_ctl_a))
		{
			// set/reset mode - bit value determines the new output
			temp = c2_set(m_ctl_a);
>>>>>>> upstream/master
		}
		else
		{
			// strobe mode - output is always high unless strobed
<<<<<<< HEAD
			temp = TRUE;
=======
			temp = true;
>>>>>>> upstream/master
		}

		set_out_ca2(temp);
	}

	// update externals
	update_interrupts();
}


//-------------------------------------------------
//  control_b_w
//-------------------------------------------------

<<<<<<< HEAD
void pia6821_device::control_b_w(UINT8 data)
{
	int temp;
=======
void pia6821_device::control_b_w(uint8_t data)
{
	bool temp;
>>>>>>> upstream/master

	// bit 7 and 6 are read only
	data &= 0x3f;

<<<<<<< HEAD
	LOG(("PIA #%s: control B write = %02X\n", tag(), data));
=======
	LOGSETUP("PIA control B write = %02X\n", data);
>>>>>>> upstream/master

	// update the control register
	m_ctl_b = data;

<<<<<<< HEAD
	if (C2_SET_MODE(m_ctl_b))
	{
		// set/reset mode - bit value determines the new output
		temp = C2_SET(m_ctl_b);
=======
	if (c2_set_mode(m_ctl_b))
	{
		// set/reset mode - bit value determines the new output
		temp = c2_set(m_ctl_b);
>>>>>>> upstream/master
	}
	else
	{
		// strobe mode - output is always high unless strobed
<<<<<<< HEAD
		temp = TRUE;
=======
		temp = true;
>>>>>>> upstream/master
	}

	set_out_cb2(temp);

	// update externals
	update_interrupts();
}


//-------------------------------------------------
//  write
//-------------------------------------------------

<<<<<<< HEAD
void pia6821_device::reg_w(UINT8 offset, UINT8 data)
=======
void pia6821_device::reg_w(uint8_t offset, uint8_t data)
>>>>>>> upstream/master
{
	switch (offset & 0x03)
	{
		default: // impossible
		case 0x00:
<<<<<<< HEAD
			if (OUTPUT_SELECTED(m_ctl_a))
=======
			if (output_selected(m_ctl_a))
>>>>>>> upstream/master
			{
				port_a_w(data);
			}
			else
			{
				ddr_a_w(data);
			}
			break;

		case 0x01:
			control_a_w( data);
			break;

		case 0x02:
<<<<<<< HEAD
			if(OUTPUT_SELECTED(m_ctl_b))
=======
			if(output_selected(m_ctl_b))
>>>>>>> upstream/master
			{
				port_b_w(data);
			}
			else
			{
				ddr_b_w(data);
			}
			break;

		case 0x03:
			control_b_w(data);
			break;
	}
}


//-------------------------------------------------
//  set_a_input
//-------------------------------------------------

<<<<<<< HEAD
void pia6821_device::set_a_input(UINT8 data, UINT8 z_mask)
{
	assert_always(m_in_a_handler.isnull(), "pia6821_porta_w() called when in_a_func implemented");

	LOG(("PIA #%s: set input port A = %02X\n", tag(), data));
=======
void pia6821_device::set_a_input(uint8_t data, uint8_t z_mask)
{
	assert_always(m_in_a_handler.isnull(), "pia6821_porta_w() called when in_a_func implemented");

	LOG("Set PIA input port A = %02X\n", data);
>>>>>>> upstream/master

	m_in_a = data;
	m_port_a_z_mask = z_mask;
	m_in_a_pushed = true;
}


//-------------------------------------------------
//  pia6821_porta_w
//-------------------------------------------------

<<<<<<< HEAD
void pia6821_device::porta_w(UINT8 data)
=======
void pia6821_device::porta_w(uint8_t data)
>>>>>>> upstream/master
{
	set_a_input(data, 0);
}


//-------------------------------------------------
//  a_output
//-------------------------------------------------

<<<<<<< HEAD
UINT8 pia6821_device::a_output()
=======
uint8_t pia6821_device::a_output()
>>>>>>> upstream/master
{
	m_out_a_needs_pulled = false;

	return get_out_a_value();
}


//-------------------------------------------------
//  ca1_w
//-------------------------------------------------

WRITE_LINE_MEMBER( pia6821_device::ca1_w )
{
<<<<<<< HEAD
	LOG(("PIA #%s: set input CA1 = %d\n", tag(), state));

	// the new state has caused a transition
	if((m_in_ca1 != state) && ((state && C1_LOW_TO_HIGH(m_ctl_a)) || (!state && C1_HIGH_TO_LOW(m_ctl_a))))
	{
		LOG(("PIA #%s: CA1 triggering\n", tag()));

		// mark the IRQ
		m_irq_a1 = TRUE;
=======
	LOGCA1("Set PIA input CA1 = %d\n", state);

	// the new state has caused a transition
	if((m_in_ca1 != state) && ((state && c1_low_to_high(m_ctl_a)) || (!state && c1_high_to_low(m_ctl_a))))
	{
		LOGCA1("CA1 triggering\n");

		// mark the IRQ
		m_irq_a1 = true;
>>>>>>> upstream/master

		// update externals
		update_interrupts();

		// CA2 is configured as output and in read strobe mode and cleared by a CA1 transition
<<<<<<< HEAD
		if(C2_OUTPUT(m_ctl_a) && C2_STROBE_MODE(m_ctl_a) && STROBE_C1_RESET(m_ctl_a))
		{
			set_out_ca2(TRUE);
=======
		if(c2_output(m_ctl_a) && c2_strobe_mode(m_ctl_a) && strobe_c1_reset(m_ctl_a))
		{
			set_out_ca2(true);
>>>>>>> upstream/master
		}
	}

	// set the new value for CA1
	m_in_ca1 = state;
	m_in_ca1_pushed = true;
}


//-------------------------------------------------
//  ca2_w
//-------------------------------------------------

WRITE_LINE_MEMBER( pia6821_device::ca2_w )
{
<<<<<<< HEAD
	LOG(("PIA #%s: set input CA2 = %d\n", tag(), state));

	// if input mode and the new state has caused a transition
	if(C2_INPUT(m_ctl_a) && (m_in_ca2 != state) && ((state && C2_LOW_TO_HIGH(m_ctl_a)) || (!state && C2_HIGH_TO_LOW(m_ctl_a))))
	{
		LOG(("PIA #%s: CA2 triggering\n", tag()));

		// mark the IRQ
		m_irq_a2 = TRUE;
=======
	LOG("Set PIA input CA2 = %d\n", state);

	// if input mode and the new state has caused a transition
	if(c2_input(m_ctl_a) && (m_in_ca2 != state) && ((state && c2_low_to_high(m_ctl_a)) || (!state && c2_high_to_low(m_ctl_a))))
	{
		LOG("CA2 triggering\n");

		// mark the IRQ
		m_irq_a2 = true;
>>>>>>> upstream/master

		// update externals
		update_interrupts();
	}

	// set the new value for CA2
	m_in_ca2 = state;
	m_in_ca2_pushed = true;
}


//-------------------------------------------------
//  ca2_output
//-------------------------------------------------

<<<<<<< HEAD
int pia6821_device::ca2_output()
=======
bool pia6821_device::ca2_output()
>>>>>>> upstream/master
{
	m_out_ca2_needs_pulled = false;

	return m_out_ca2;
}


//-------------------------------------------------
//  ca2_output_z - version of ca2_output which
//  takes account of internal pullup resistor
//-------------------------------------------------

<<<<<<< HEAD
int pia6821_device::ca2_output_z()
=======
bool pia6821_device::ca2_output_z()
>>>>>>> upstream/master
{
	m_out_ca2_needs_pulled = false;

	// If it's an output, output the bit, if it's an input, it's
	// pulled up
<<<<<<< HEAD
	return m_out_ca2 | C2_INPUT(m_ctl_a);
=======
	return m_out_ca2 | c2_input(m_ctl_a);
>>>>>>> upstream/master
}


//-------------------------------------------------
//  portb_w
//-------------------------------------------------

<<<<<<< HEAD
void pia6821_device::portb_w(UINT8 data)
{
	assert_always(m_in_b_handler.isnull(), "pia_set_input_b() called when in_b_func implemented");

	LOG(("PIA #%s: set input port B = %02X\n", tag(), data));
=======
void pia6821_device::portb_w(uint8_t data)
{
	assert_always(m_in_b_handler.isnull(), "pia_set_input_b() called when in_b_func implemented");

	LOG("Set PIA input port B = %02X\n", data);
>>>>>>> upstream/master

	m_in_b = data;
	m_in_b_pushed = true;
}


//-------------------------------------------------
//  b_output
//-------------------------------------------------

<<<<<<< HEAD
UINT8 pia6821_device::b_output()
=======
uint8_t pia6821_device::b_output()
>>>>>>> upstream/master
{
	m_out_b_needs_pulled = false;

	return get_out_b_value();
}


//-------------------------------------------------
//  cb1_w
//-------------------------------------------------

WRITE_LINE_MEMBER( pia6821_device::cb1_w )
{
<<<<<<< HEAD
	LOG(("PIA #%s: set input CB1 = %d\n", tag(), state));

	// the new state has caused a transition
	if((m_in_cb1 != state) && ((state && C1_LOW_TO_HIGH(m_ctl_b)) || (!state && C1_HIGH_TO_LOW(m_ctl_b))))
	{
		LOG(("PIA #%s: CB1 triggering\n", tag()));
=======
	LOG("Set PIA input CB1 = %d\n", state);

	// the new state has caused a transition
	if((m_in_cb1 != state) && ((state && c1_low_to_high(m_ctl_b)) || (!state && c1_high_to_low(m_ctl_b))))
	{
		LOG("CB1 triggering\n");
>>>>>>> upstream/master

		// mark the IRQ
		m_irq_b1 = 1;

		// update externals
		update_interrupts();

		// If CB2 is configured as a write-strobe output which is reset by a CB1
		// transition, this reset will only happen when a read from port B implicitly
		// clears the IRQ B1 flag.  So we handle the CB2 reset there.  Note that this
		// is different from what happens with port A.
	}

	// set the new value for CB1
	m_in_cb1 = state;
	m_in_cb1_pushed = true;
}


//-------------------------------------------------
//  cb2_w
//-------------------------------------------------

WRITE_LINE_MEMBER( pia6821_device::cb2_w )
{
<<<<<<< HEAD
	LOG(("PIA #%s: set input CB2 = %d\n", tag(), state));

	// if input mode and the new state has caused a transition
	if (C2_INPUT(m_ctl_b) &&
		(m_in_cb2 != state) &&
		((state && C2_LOW_TO_HIGH(m_ctl_b)) || (!state && C2_HIGH_TO_LOW(m_ctl_b))))
	{
		LOG(("PIA #%s: CB2 triggering\n", tag()));
=======
	LOG("Set PIA input CB2 = %d\n", state);

	// if input mode and the new state has caused a transition
	if (c2_input(m_ctl_b) &&
		(m_in_cb2 != state) &&
		((state && c2_low_to_high(m_ctl_b)) || (!state && c2_high_to_low(m_ctl_b))))
	{
		LOG("CB2 triggering\n");
>>>>>>> upstream/master

		// mark the IRQ
		m_irq_b2 = 1;

		// update externals
		update_interrupts();
	}

	// set the new value for CA2
	m_in_cb2 = state;
	m_in_cb2_pushed = true;
}


//-------------------------------------------------
//  output_cb2
//-------------------------------------------------

<<<<<<< HEAD
int pia6821_device::cb2_output()
=======
bool pia6821_device::cb2_output()
>>>>>>> upstream/master
{
	m_out_cb2_needs_pulled = false;

	return m_out_cb2;
}


//-------------------------------------------------
//  cb2_output_z
//-------------------------------------------------

<<<<<<< HEAD
int pia6821_device::cb2_output_z()
{
	return !C2_OUTPUT(m_ctl_b);
}
=======
bool pia6821_device::cb2_output_z()
{
	return !c2_output(m_ctl_b);
}


//-------------------------------------------------
//  control byte wrappers
//-------------------------------------------------

bool pia6821_device::irq1_enabled(uint8_t c)    { return  bool((c >> 0) & 0x01); }
bool pia6821_device::c1_low_to_high(uint8_t c)  { return  bool((c >> 1) & 0x01); }
bool pia6821_device::c1_high_to_low(uint8_t c)  { return !bool((c >> 1) & 0x01); }
bool pia6821_device::output_selected(uint8_t c) { return  bool((c >> 2) & 0x01); }
bool pia6821_device::irq2_enabled(uint8_t c)    { return  bool((c >> 3) & 0x01); }
bool pia6821_device::strobe_e_reset(uint8_t c)  { return  bool((c >> 3) & 0x01); }
bool pia6821_device::strobe_c1_reset(uint8_t c) { return !bool((c >> 3) & 0x01); }
bool pia6821_device::c2_set(uint8_t c)          { return  bool((c >> 3) & 0x01); }
bool pia6821_device::c2_low_to_high(uint8_t c)  { return  bool((c >> 4) & 0x01); }
bool pia6821_device::c2_high_to_low(uint8_t c)  { return !bool((c >> 4) & 0x01); }
bool pia6821_device::c2_set_mode(uint8_t c)     { return  bool((c >> 4) & 0x01); }
bool pia6821_device::c2_strobe_mode(uint8_t c)  { return !bool((c >> 4) & 0x01); }
bool pia6821_device::c2_output(uint8_t c)       { return  bool((c >> 5) & 0x01); }
bool pia6821_device::c2_input(uint8_t c)        { return !bool((c >> 5) & 0x01); }
>>>>>>> upstream/master
