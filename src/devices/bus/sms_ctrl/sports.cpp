// license:BSD-3-Clause
// copyright-holders:Fabio Priuli
/**********************************************************************

    Sega Master System "Sports Pad" (US model) emulation

<<<<<<< HEAD
**********************************************************************/

// The games designed for the US model of the Sports Pad controller use the
// TH line of the controller port as output, to select which nibble, of the
// two axis bytes, will be read at a time. The Japanese cartridge Sports Pad
// Soccer uses a different mode, because the Sega Mark III lacks TH output, so
// there is a different Sports Pad model released in Japan (see sportsjp.c).

// It was discovered that games designed for the Paddle Controller, released
// in Japan, switch to a mode incompatible with the original Paddle when
// detect the system region as Export. Similar to how the US model of the
// Sports Pad works, that mode uses the TH line as output to select which
// nibble of the X axis will be read. So, on an Export console version, paddle
// games are somewhat playable with the US Sport Pad model, though it needs to
// be used inverted and the trackball needs to be moved slowly, else the
// software for the paddle think it's moving backward.
// See http://mametesters.org/view.php?id=5872 for discussion.

=======

Release data from the Sega Retro project:

  Year: 1987    Country/region: US    Model code: 3040

TODO:

- For low-level emulation, a device for the TMP42C66P, a Toshiba 4bit
  microcontroller, needs to be created, but a dump of its internal ROM
  seems to be required.
- Auto-repeat and Control/Sports mode switches are not emulated.

Notes:

  Games designed for the US model of the Sports Pad controller use the
  TH line of the controller port to select which nibble, of the two axis
  bytes, will be read at a time. The Japanese cartridge Sports Pad Soccer
  uses a different mode when not detect a SMSJ, because the Sega Mark III
  lacks the TH line. There is a different Sports Pad model released in
  Japan and no information was found about it supporting both modes, so
  that model is currently emulated as a different device (see sportsjp.c).

  It was discovered that games designed for the Paddle Controller, released
  in Japan, switch to a mode incompatible with the original Paddle when
  detect the system region as Export. Similar to how the US model of the
  Sports Pad works, that mode uses the TH line as output to select which
  nibble of the X axis will be read. So, on an Export console version,
  paddle games are somewhat playable with the US Sport Pad model, though it
  needs to be used inverted and the trackball needs to be moved slowly, else
  the software for the paddle think it's moving backward.
  See http://mametesters.org/view.php?id=5872 for discussion.

**********************************************************************/

#include "emu.h"
>>>>>>> upstream/master
#include "sports.h"



//**************************************************************************
//  DEVICE DEFINITIONS
//**************************************************************************

<<<<<<< HEAD
const device_type SMS_SPORTS_PAD = &device_creator<sms_sports_pad_device>;

// time interval not verified
#define SPORTS_PAD_INTERVAL attotime::from_hz(XTAL_53_693175MHz/15/512)
=======
DEFINE_DEVICE_TYPE(SMS_SPORTS_PAD, sms_sports_pad_device, "sms_sports_pad", "Sega SMS Sports Pad (US)")

// time interval not verified
#define SPORTS_PAD_INTERVAL attotime::from_hz(XTAL_10_738635MHz/3/512)
>>>>>>> upstream/master


void sms_sports_pad_device::device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr)
{
	switch (id)
	{
	case TIMER_SPORTSPAD:
		// values for x and y axis need to be resetted for Sports Pad games, but
		// are not resetted for paddle games, so it was assumed the reset occurs
		// only when this timer fires after the read state reached maximum value.
		if (m_read_state == 3)
		{
			m_x_axis_reset_value = m_sports_x->read();
			m_y_axis_reset_value = m_sports_y->read();
		}
		else
		{
			// set to maximum value, so it wraps to 0 at next increment
			m_read_state = 3;
		}

		break;
	default:
<<<<<<< HEAD
		assert_always(FALSE, "Unknown id in sms_sports_pad_device::device_timer");
=======
		assert_always(false, "Unknown id in sms_sports_pad_device::device_timer");
>>>>>>> upstream/master
	}
}


<<<<<<< HEAD
CUSTOM_INPUT_MEMBER( sms_sports_pad_device::th_pin_r )
{
	return m_last_data;
}


INPUT_CHANGED_MEMBER( sms_sports_pad_device::th_pin_w )
{
	m_read_state = (m_read_state + 1) & 3;
	m_sportspad_timer->adjust(m_interval);
	m_last_data = newval;
}


CUSTOM_INPUT_MEMBER( sms_sports_pad_device::dir_pins_r )
{
	UINT8 data = 0;
=======
READ_LINE_MEMBER( sms_sports_pad_device::th_pin_r )
{
	return m_th_pin_state;
}


WRITE_LINE_MEMBER( sms_sports_pad_device::th_pin_w )
{
	m_read_state = (m_read_state + 1) & 3;
	m_sportspad_timer->adjust(m_interval);
	m_th_pin_state = state;
}


CUSTOM_INPUT_MEMBER( sms_sports_pad_device::rldu_pins_r )
{
	uint8_t data = 0;
>>>>>>> upstream/master

	switch (m_read_state)
	{
	case 0:
		data = (m_sports_x->read() - m_x_axis_reset_value) >> 4;
		break;
	case 1:
		data = (m_sports_x->read() - m_x_axis_reset_value);
		break;
	case 2:
		data = (m_sports_y->read() - m_y_axis_reset_value) >> 4;
		break;
	case 3:
		data = (m_sports_y->read() - m_y_axis_reset_value);
		break;
	}

	// The returned value is inverted due to IP_ACTIVE_LOW mapping.
	return ~(data & 0x0f);
}


static INPUT_PORTS_START( sms_sports_pad )
	PORT_START("SPORTS_IN")
<<<<<<< HEAD
	PORT_BIT( 0x0f, IP_ACTIVE_LOW, IPT_SPECIAL ) PORT_CUSTOM_MEMBER(DEVICE_SELF, sms_sports_pad_device, dir_pins_r, NULL) // Directional pins
	PORT_BIT( 0x10, IP_ACTIVE_LOW, IPT_UNUSED ) // Vcc
	PORT_BIT( 0x20, IP_ACTIVE_LOW, IPT_BUTTON1 ) // TL (Button 1)
	PORT_BIT( 0x40, IP_ACTIVE_LOW, IPT_SPECIAL ) PORT_CUSTOM_MEMBER(DEVICE_SELF, sms_sports_pad_device, th_pin_r, NULL)
=======
	PORT_BIT( 0x0f, IP_ACTIVE_LOW, IPT_SPECIAL ) PORT_CUSTOM_MEMBER(DEVICE_SELF, sms_sports_pad_device, rldu_pins_r, nullptr) // R,L,D,U
	PORT_BIT( 0x10, IP_ACTIVE_LOW, IPT_UNUSED ) // Vcc
	PORT_BIT( 0x20, IP_ACTIVE_LOW, IPT_BUTTON1 ) // TL (Button 1)
	PORT_BIT( 0x40, IP_ACTIVE_LOW, IPT_SPECIAL ) PORT_READ_LINE_DEVICE_MEMBER(DEVICE_SELF, sms_sports_pad_device, th_pin_r) // TH
>>>>>>> upstream/master
	PORT_BIT( 0x80, IP_ACTIVE_LOW, IPT_BUTTON2 ) // TR (Button 2)

	PORT_START("SPORTS_OUT")
	PORT_BIT( 0x0f, IP_ACTIVE_LOW, IPT_UNUSED ) // Directional pins
	PORT_BIT( 0x10, IP_ACTIVE_LOW, IPT_UNUSED ) // Vcc
	PORT_BIT( 0x20, IP_ACTIVE_LOW, IPT_UNUSED ) // TL (Button 1)
<<<<<<< HEAD
	PORT_BIT( 0x40, IP_ACTIVE_LOW, IPT_OUTPUT ) PORT_CHANGED_MEMBER(DEVICE_SELF, sms_sports_pad_device, th_pin_w, NULL)
=======
	PORT_BIT( 0x40, IP_ACTIVE_LOW, IPT_OUTPUT ) PORT_WRITE_LINE_DEVICE_MEMBER(DEVICE_SELF, sms_sports_pad_device, th_pin_w) // TH
>>>>>>> upstream/master
	PORT_BIT( 0x80, IP_ACTIVE_LOW, IPT_UNUSED ) // TR (Button 2)

	PORT_START("SPORTS_X")    /* Sports Pad X axis */
	PORT_BIT( 0xff, 0x00, IPT_TRACKBALL_X ) PORT_SENSITIVITY(50) PORT_KEYDELTA(40) PORT_REVERSE

	PORT_START("SPORTS_Y")    /* Sports Pad Y axis */
	PORT_BIT( 0xff, 0x00, IPT_TRACKBALL_Y ) PORT_SENSITIVITY(50) PORT_KEYDELTA(40) PORT_REVERSE
INPUT_PORTS_END


//-------------------------------------------------
//  input_ports - device-specific input ports
//-------------------------------------------------

ioport_constructor sms_sports_pad_device::device_input_ports() const
{
	return INPUT_PORTS_NAME( sms_sports_pad );
}



//**************************************************************************
//  LIVE DEVICE
//**************************************************************************

//-------------------------------------------------
//  sms_sports_pad_device - constructor
//-------------------------------------------------

<<<<<<< HEAD
sms_sports_pad_device::sms_sports_pad_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock) :
	device_t(mconfig, SMS_SPORTS_PAD, "Sega SMS Sports Pad US", tag, owner, clock, "sms_sports_pad", __FILE__),
=======
sms_sports_pad_device::sms_sports_pad_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock) :
	device_t(mconfig, SMS_SPORTS_PAD, tag, owner, clock),
>>>>>>> upstream/master
	device_sms_control_port_interface(mconfig, *this),
	m_sports_in(*this, "SPORTS_IN"),
	m_sports_out(*this, "SPORTS_OUT"),
	m_sports_x(*this, "SPORTS_X"),
	m_sports_y(*this, "SPORTS_Y"),
	m_read_state(0),
<<<<<<< HEAD
	m_last_data(0),
	m_x_axis_reset_value(0x80), // value 0x80 helps when start playing paddle games.
	m_y_axis_reset_value(0x80),
	m_interval(SPORTS_PAD_INTERVAL), m_sportspad_timer(nullptr)
=======
	m_th_pin_state(0),
	m_x_axis_reset_value(0x80), // value 0x80 helps when start playing paddle games.
	m_y_axis_reset_value(0x80),
	m_interval(SPORTS_PAD_INTERVAL),
	m_sportspad_timer(nullptr)
>>>>>>> upstream/master
{
}


//-------------------------------------------------
//  device_start - device-specific startup
//-------------------------------------------------

void sms_sports_pad_device::device_start()
{
	m_sportspad_timer = timer_alloc(TIMER_SPORTSPAD);

	save_item(NAME(m_read_state));
<<<<<<< HEAD
	save_item(NAME(m_last_data));
=======
	save_item(NAME(m_th_pin_state));
>>>>>>> upstream/master
	save_item(NAME(m_x_axis_reset_value));
	save_item(NAME(m_y_axis_reset_value));
}


//-------------------------------------------------
//  sms_peripheral_r - sports pad read
//-------------------------------------------------

<<<<<<< HEAD
UINT8 sms_sports_pad_device::peripheral_r()
=======
uint8_t sms_sports_pad_device::peripheral_r()
>>>>>>> upstream/master
{
	return m_sports_in->read();
}


//-------------------------------------------------
//  sms_peripheral_w - sports pad write
//-------------------------------------------------

<<<<<<< HEAD
void sms_sports_pad_device::peripheral_w(UINT8 data)
=======
void sms_sports_pad_device::peripheral_w(uint8_t data)
>>>>>>> upstream/master
{
	m_sports_out->write(data);
}
