// license:BSD-3-Clause
// copyright-holders:Curt Coder
/**********************************************************************

    ColecoVision Super Action Controller emulation

**********************************************************************/

<<<<<<< HEAD
=======
#include "emu.h"
>>>>>>> upstream/master
#include "sac.h"



//**************************************************************************
//  DEVICE DEFINITIONS
//**************************************************************************

<<<<<<< HEAD
const device_type COLECO_SUPER_ACTION_CONTROLLER = &device_creator<coleco_super_action_controller_t>;


CUSTOM_INPUT_MEMBER( coleco_super_action_controller_t::keypad_r )
{
	UINT8 data = 0xf;
	UINT16 keypad = m_io_keypad->read();
=======
DEFINE_DEVICE_TYPE(COLECO_SUPER_ACTION_CONTROLLER, coleco_super_action_controller_device, "coleco_sac", "ColecoVision Super Action Controller")


CUSTOM_INPUT_MEMBER( coleco_super_action_controller_device::keypad_r )
{
	uint8_t data = 0xf;
	uint16_t keypad = m_io_keypad->read();
>>>>>>> upstream/master

	if (!BIT(keypad, 0)) data &= 0x0a;
	if (!BIT(keypad, 1)) data &= 0x0d;
	if (!BIT(keypad, 2)) data &= 0x07;
	if (!BIT(keypad, 3)) data &= 0x0c;
	if (!BIT(keypad, 4)) data &= 0x02;
	if (!BIT(keypad, 5)) data &= 0x03;
	if (!BIT(keypad, 6)) data &= 0x0e;
	if (!BIT(keypad, 7)) data &= 0x05;
	if (!BIT(keypad, 8)) data &= 0x01;
	if (!BIT(keypad, 9)) data &= 0x0b;
	if (!BIT(keypad, 10)) data &= 0x06;
	if (!BIT(keypad, 11)) data &= 0x09;
	if (!BIT(keypad, 12)) data &= 0x04;
	if (!BIT(keypad, 13)) data &= 0x08;

	return data;
}

<<<<<<< HEAD
INPUT_CHANGED_MEMBER( coleco_super_action_controller_t::slider_w )
=======
INPUT_CHANGED_MEMBER( coleco_super_action_controller_device::slider_w )
>>>>>>> upstream/master
{
	// TODO
}

static INPUT_PORTS_START( coleco_super_action_controller )
	PORT_START("COMMON0")
	PORT_BIT( 0x01, IP_ACTIVE_LOW, IPT_JOYSTICK_UP )
	PORT_BIT( 0x02, IP_ACTIVE_LOW, IPT_JOYSTICK_RIGHT )
	PORT_BIT( 0x04, IP_ACTIVE_LOW, IPT_JOYSTICK_DOWN )
	PORT_BIT( 0x08, IP_ACTIVE_LOW, IPT_JOYSTICK_LEFT )
	PORT_BIT( 0x30, IP_ACTIVE_LOW, IPT_UNUSED )
	PORT_BIT( 0x40, IP_ACTIVE_LOW, IPT_BUTTON1 )
	PORT_BIT( 0x80, IP_ACTIVE_HIGH, IPT_SPECIAL )

	PORT_START("COMMON1")
<<<<<<< HEAD
	PORT_BIT( 0x0f, IP_ACTIVE_HIGH, IPT_SPECIAL ) PORT_CUSTOM_MEMBER(DEVICE_SELF, coleco_super_action_controller_t, keypad_r, 0)
=======
	PORT_BIT( 0x0f, IP_ACTIVE_HIGH, IPT_SPECIAL ) PORT_CUSTOM_MEMBER(DEVICE_SELF, coleco_super_action_controller_device, keypad_r, nullptr)
>>>>>>> upstream/master
	PORT_BIT( 0x30, IP_ACTIVE_LOW, IPT_UNUSED )
	PORT_BIT( 0x40, IP_ACTIVE_LOW, IPT_BUTTON2 )
	PORT_BIT( 0x80, IP_ACTIVE_HIGH, IPT_SPECIAL )

	PORT_START("KEYPAD")
	PORT_BIT( 0x0001, IP_ACTIVE_LOW, IPT_KEYPAD ) PORT_NAME("Keypad 0") PORT_CODE(KEYCODE_0_PAD)
	PORT_BIT( 0x0002, IP_ACTIVE_LOW, IPT_KEYPAD ) PORT_NAME("Keypad 1") PORT_CODE(KEYCODE_1_PAD)
	PORT_BIT( 0x0004, IP_ACTIVE_LOW, IPT_KEYPAD ) PORT_NAME("Keypad 2") PORT_CODE(KEYCODE_2_PAD)
	PORT_BIT( 0x0008, IP_ACTIVE_LOW, IPT_KEYPAD ) PORT_NAME("Keypad 3") PORT_CODE(KEYCODE_3_PAD)
	PORT_BIT( 0x0010, IP_ACTIVE_LOW, IPT_KEYPAD ) PORT_NAME("Keypad 4") PORT_CODE(KEYCODE_4_PAD)
	PORT_BIT( 0x0020, IP_ACTIVE_LOW, IPT_KEYPAD ) PORT_NAME("Keypad 5") PORT_CODE(KEYCODE_5_PAD)
	PORT_BIT( 0x0040, IP_ACTIVE_LOW, IPT_KEYPAD ) PORT_NAME("Keypad 6") PORT_CODE(KEYCODE_6_PAD)
	PORT_BIT( 0x0080, IP_ACTIVE_LOW, IPT_KEYPAD ) PORT_NAME("Keypad 7") PORT_CODE(KEYCODE_7_PAD)
	PORT_BIT( 0x0100, IP_ACTIVE_LOW, IPT_KEYPAD ) PORT_NAME("Keypad 8") PORT_CODE(KEYCODE_8_PAD)
	PORT_BIT( 0x0200, IP_ACTIVE_LOW, IPT_KEYPAD ) PORT_NAME("Keypad 9") PORT_CODE(KEYCODE_9_PAD)
	PORT_BIT( 0x0400, IP_ACTIVE_LOW, IPT_KEYPAD ) PORT_NAME("Keypad #") PORT_CODE(KEYCODE_MINUS_PAD)
	PORT_BIT( 0x0800, IP_ACTIVE_LOW, IPT_KEYPAD ) PORT_NAME("Keypad *") PORT_CODE(KEYCODE_PLUS_PAD)
	PORT_BIT( 0x1000, IP_ACTIVE_LOW, IPT_BUTTON3 )
	PORT_BIT( 0x2000, IP_ACTIVE_LOW, IPT_BUTTON4 )

	PORT_START("SLIDER")
<<<<<<< HEAD
	PORT_BIT( 0xff, 0x00, IPT_DIAL ) PORT_SENSITIVITY(100) PORT_KEYDELTA(25) PORT_REVERSE PORT_RESET PORT_CHANGED_MEMBER(DEVICE_SELF, coleco_super_action_controller_t, slider_w, 0)
=======
	PORT_BIT( 0xff, 0x00, IPT_DIAL ) PORT_SENSITIVITY(100) PORT_KEYDELTA(25) PORT_REVERSE PORT_RESET PORT_CHANGED_MEMBER(DEVICE_SELF, coleco_super_action_controller_device, slider_w, nullptr)
>>>>>>> upstream/master
INPUT_PORTS_END


//-------------------------------------------------
//  input_ports - device-specific input ports
//-------------------------------------------------

<<<<<<< HEAD
ioport_constructor coleco_super_action_controller_t::device_input_ports() const
=======
ioport_constructor coleco_super_action_controller_device::device_input_ports() const
>>>>>>> upstream/master
{
	return INPUT_PORTS_NAME( coleco_super_action_controller );
}



//**************************************************************************
//  LIVE DEVICE
//**************************************************************************

//-------------------------------------------------
<<<<<<< HEAD
//  coleco_super_action_controller_t - constructor
//-------------------------------------------------

coleco_super_action_controller_t::coleco_super_action_controller_t(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock) :
	device_t(mconfig, COLECO_SUPER_ACTION_CONTROLLER, "ColecoVision Super Action Controller", tag, owner, clock, "coleco_sac", __FILE__),
=======
//  coleco_super_action_controller_device - constructor
//-------------------------------------------------

coleco_super_action_controller_device::coleco_super_action_controller_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock) :
	device_t(mconfig, COLECO_SUPER_ACTION_CONTROLLER, tag, owner, clock),
>>>>>>> upstream/master
	device_colecovision_control_port_interface(mconfig, *this),
	m_io_common0(*this, "COMMON0"),
	m_io_common1(*this, "COMMON1"),
	m_io_keypad(*this, "KEYPAD")
{
}


//-------------------------------------------------
//  device_start - device-specific startup
//-------------------------------------------------

<<<<<<< HEAD
void coleco_super_action_controller_t::device_start()
=======
void coleco_super_action_controller_device::device_start()
>>>>>>> upstream/master
{
	// state saving
	save_item(NAME(m_common0));
	save_item(NAME(m_common1));
}


//-------------------------------------------------
//  joy_r - joystick read
//-------------------------------------------------

<<<<<<< HEAD
UINT8 coleco_super_action_controller_t::joy_r()
{
	UINT8 data = 0x7f;
=======
uint8_t coleco_super_action_controller_device::joy_r()
{
	uint8_t data = 0x7f;
>>>>>>> upstream/master

	if (!m_common0) data &= m_io_common0->read();
	if (!m_common1) data &= m_io_common1->read();

	return data;
}
