// license:BSD-3-Clause
// copyright-holders:Fabio Priuli
/**********************************************************************

    Nintendo Super Famicom - Yonezawa / PartyRoom 21 Twin Tap Controller

    This controller consists of two 1-button small units attached to a
    single 7pin connector. You plug the connector to Port2 and two
    players can compete on the quiz game (Port1 should have a joypad
    plugged in, to start the game and browse the menus). By plugging
    a multitap adapter to Port2, up to 4 Twin Tap controllers can be
    attached at the same time, allowing for 8 players quiz sessions.

**********************************************************************/

<<<<<<< HEAD
=======
#include "emu.h"
>>>>>>> upstream/master
#include "twintap.h"

//**************************************************************************
//  DEVICE DEFINITIONS
//**************************************************************************

<<<<<<< HEAD
const device_type SNES_TWINTAP = &device_creator<snes_twintap_device>;
=======
DEFINE_DEVICE_TYPE(SNES_TWINTAP, snes_twintap_device, "snes_twintap", "Yonezawa Twin Tap Controller")
>>>>>>> upstream/master


static INPUT_PORTS_START( snes_twintap )
	PORT_START("INPUTS")
	PORT_BIT( 0x0001, IP_ACTIVE_HIGH, IPT_OTHER ) PORT_NAME("Button 2")
	PORT_BIT( 0x0002, IP_ACTIVE_HIGH, IPT_OTHER ) PORT_NAME("Button 1")
	PORT_BIT( 0x8ffc, IP_ACTIVE_HIGH, IPT_UNUSED )
	PORT_BIT( 0x7000, IP_ACTIVE_LOW, IPT_UNUSED )   // controller ID unknown
INPUT_PORTS_END


//-------------------------------------------------
//  input_ports - device-specific input ports
//-------------------------------------------------

ioport_constructor snes_twintap_device::device_input_ports() const
{
	return INPUT_PORTS_NAME( snes_twintap );
}


//**************************************************************************
//  LIVE DEVICE
//**************************************************************************

//-------------------------------------------------
//  snes_twintap_device - constructor
//-------------------------------------------------

<<<<<<< HEAD
snes_twintap_device::snes_twintap_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock) :
					device_t(mconfig, SNES_TWINTAP, "Yonezawa Twin Tap Controller", tag, owner, clock, "snes_twintap", __FILE__),
					device_snes_control_port_interface(mconfig, *this),
					m_inputs(*this, "INPUTS"), m_strobe(0), m_latch(0)
=======
snes_twintap_device::snes_twintap_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock) :
	device_t(mconfig, SNES_TWINTAP, tag, owner, clock),
	device_snes_control_port_interface(mconfig, *this),
	m_inputs(*this, "INPUTS"),
	m_strobe(0), m_latch(0)
>>>>>>> upstream/master
{
}


//-------------------------------------------------
//  device_start - device-specific startup
//-------------------------------------------------

void snes_twintap_device::device_start()
{
	save_item(NAME(m_latch));
	save_item(NAME(m_strobe));
}


//-------------------------------------------------
//  device_reset - device-specific reset
//-------------------------------------------------

void snes_twintap_device::device_reset()
{
	m_latch = 0;
	m_strobe = 0;
}


//-------------------------------------------------
//  poll
//-------------------------------------------------

void snes_twintap_device::port_poll()
{
	m_latch = m_inputs->read();
}

//-------------------------------------------------
//  read
//-------------------------------------------------

<<<<<<< HEAD
UINT8 snes_twintap_device::read_pin4()
{
	UINT8 ret = m_latch & 1;
=======
uint8_t snes_twintap_device::read_pin4()
{
	uint8_t ret = m_latch & 1;
>>>>>>> upstream/master
	m_latch >>= 1;
	return ret;
}

//-------------------------------------------------
//  write
//-------------------------------------------------

<<<<<<< HEAD
void snes_twintap_device::write_strobe(UINT8 data)
=======
void snes_twintap_device::write_strobe(uint8_t data)
>>>>>>> upstream/master
{
	int old = m_strobe;
	m_strobe = data & 0x01;

	if (m_strobe < old) // 1 -> 0 transition
		port_poll();
}
