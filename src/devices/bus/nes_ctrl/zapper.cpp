// license:BSD-3-Clause
// copyright-holders:Fabio Priuli
/**********************************************************************

    Nintendo Family Computer & Entertainment System Zapper Lightgun

**********************************************************************/

<<<<<<< HEAD
=======
#include "emu.h"
>>>>>>> upstream/master
#include "zapper.h"

//**************************************************************************
//  DEVICE DEFINITIONS
//**************************************************************************

<<<<<<< HEAD
const device_type NES_ZAPPER = &device_creator<nes_zapper_device>;
=======
DEFINE_DEVICE_TYPE(NES_ZAPPER, nes_zapper_device, "nes_zapper", "Nintendo Zapper Lightgun")
>>>>>>> upstream/master


static INPUT_PORTS_START( nes_zapper )
	PORT_START("ZAPPER_X")
	PORT_BIT( 0xff, 0x80, IPT_LIGHTGUN_X) PORT_CROSSHAIR(X, 1.0, 0.0, 0) PORT_SENSITIVITY(70) PORT_KEYDELTA(30) PORT_MINMAX(0,255)
	PORT_START("ZAPPER_Y")
	PORT_BIT( 0xff, 0x80, IPT_LIGHTGUN_Y) PORT_CROSSHAIR(Y, 1.0, 0.0, 0) PORT_SENSITIVITY(50) PORT_KEYDELTA(30) PORT_MINMAX(0,255)
	PORT_START("ZAPPER_T")
	PORT_BIT( 0x10, IP_ACTIVE_HIGH, IPT_BUTTON1) PORT_NAME("Lightgun Trigger")
INPUT_PORTS_END


//-------------------------------------------------
//  input_ports - device-specific input ports
//-------------------------------------------------

ioport_constructor nes_zapper_device::device_input_ports() const
{
	return INPUT_PORTS_NAME( nes_zapper );
}



//**************************************************************************
//  LIVE DEVICE
//**************************************************************************

//-------------------------------------------------
//  nes_zapper_device - constructor
//-------------------------------------------------

<<<<<<< HEAD
nes_zapper_device::nes_zapper_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock) :
					device_t(mconfig, NES_ZAPPER, "Nintendo Zapper Lightgun", tag, owner, clock, "nes_zapper", __FILE__),
					device_nes_control_port_interface(mconfig, *this),
					m_lightx(*this, "ZAPPER_X"),
					m_lighty(*this, "ZAPPER_Y"),
					m_trigger(*this, "ZAPPER_T")
=======
nes_zapper_device::nes_zapper_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock) :
	device_t(mconfig, NES_ZAPPER, tag, owner, clock),
	device_nes_control_port_interface(mconfig, *this),
	m_lightx(*this, "ZAPPER_X"),
	m_lighty(*this, "ZAPPER_Y"),
	m_trigger(*this, "ZAPPER_T")
>>>>>>> upstream/master
{
}


//-------------------------------------------------
//  device_start
//-------------------------------------------------

void nes_zapper_device::device_start()
{
}


//-------------------------------------------------
//  device_reset
//-------------------------------------------------

void nes_zapper_device::device_reset()
{
}


//-------------------------------------------------
//  read
//-------------------------------------------------

<<<<<<< HEAD
UINT8 nes_zapper_device::read_bit34()
{
	UINT8 ret = m_trigger->read();
=======
uint8_t nes_zapper_device::read_bit34()
{
	uint8_t ret = m_trigger->read();
>>>>>>> upstream/master
	if (!m_port->m_brightpixel_cb.isnull() &&
		m_port->m_brightpixel_cb(m_lightx->read(), m_lighty->read()))
		ret &= ~0x08; // sprite hit
	else
		ret |= 0x08;  // no sprite hit
	return ret;
}

<<<<<<< HEAD
UINT8 nes_zapper_device::read_exp(offs_t offset)
{
	UINT8 ret = 0;
=======
uint8_t nes_zapper_device::read_exp(offs_t offset)
{
	uint8_t ret = 0;
>>>>>>> upstream/master
	if (offset == 1)    // $4017
		ret |= nes_zapper_device::read_bit34();
	return ret;
}
