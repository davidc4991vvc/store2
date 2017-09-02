// license:BSD-3-Clause
// copyright-holders:Fabio Priuli
/**********************************************************************

    Sega Game Gear "SMS Controller Adaptor" emulation
    Also known as "Master Link" cable.

**********************************************************************/

<<<<<<< HEAD
=======
#include "emu.h"
>>>>>>> upstream/master
#include "smsctrladp.h"



//**************************************************************************
//  DEVICE DEFINITIONS
//**************************************************************************

<<<<<<< HEAD
const device_type SMS_CTRL_ADAPTOR = &device_creator<sms_ctrl_adaptor_device>;
=======
DEFINE_DEVICE_TYPE(SMS_CTRL_ADAPTOR, sms_ctrl_adaptor_device, "sms_ctrl_adaptor", "SMS Controller Adaptor")
>>>>>>> upstream/master


//**************************************************************************
//  LIVE DEVICE
//**************************************************************************

//-------------------------------------------------
//  sms_ctrl_adaptor_device - constructor
//-------------------------------------------------

<<<<<<< HEAD
sms_ctrl_adaptor_device::sms_ctrl_adaptor_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock) :
	device_t(mconfig, SMS_CTRL_ADAPTOR, "SMS Controller Adaptor", tag, owner, clock, "sms_ctrl_adaptor", __FILE__),
=======
sms_ctrl_adaptor_device::sms_ctrl_adaptor_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock) :
	device_t(mconfig, SMS_CTRL_ADAPTOR, tag, owner, clock),
>>>>>>> upstream/master
	device_gg_ext_port_interface(mconfig, *this),
	m_subctrl_port(*this, "ctrl")
{
}


//-------------------------------------------------
//  device_start - device-specific startup
//-------------------------------------------------

void sms_ctrl_adaptor_device::device_start()
{
<<<<<<< HEAD
	m_subctrl_port->device_start();
=======
>>>>>>> upstream/master
}


//-------------------------------------------------
<<<<<<< HEAD
//  sms_peripheral_r - rapid fire read
//-------------------------------------------------

UINT8 sms_ctrl_adaptor_device::peripheral_r()
=======
//  sms_peripheral_r - sms_ctrl_adaptor read
//-------------------------------------------------

uint8_t sms_ctrl_adaptor_device::peripheral_r()
>>>>>>> upstream/master
{
	return m_subctrl_port->port_r();
}


//-------------------------------------------------
<<<<<<< HEAD
//  sms_peripheral_w - rapid fire write
//-------------------------------------------------

void sms_ctrl_adaptor_device::peripheral_w(UINT8 data)
=======
//  sms_peripheral_w - sms_ctrl_adaptor write
//-------------------------------------------------

void sms_ctrl_adaptor_device::peripheral_w(uint8_t data)
>>>>>>> upstream/master
{
	m_subctrl_port->port_w(data);
}


<<<<<<< HEAD
//-------------------------------------------------
//  machine_config_additions - device-specific
//  machine configurations
//-------------------------------------------------

=======
>>>>>>> upstream/master
WRITE_LINE_MEMBER( sms_ctrl_adaptor_device::th_pin_w )
{
	m_port->th_pin_w(state);
}


READ32_MEMBER( sms_ctrl_adaptor_device::pixel_r )
{
	return m_port->pixel_r();
}


<<<<<<< HEAD
static MACHINE_CONFIG_FRAGMENT( sms_adp_slot )
=======
//-------------------------------------------------
//  device_add_mconfig - add device configuration
//-------------------------------------------------

MACHINE_CONFIG_MEMBER( sms_ctrl_adaptor_device::device_add_mconfig )
>>>>>>> upstream/master
	MCFG_SMS_CONTROL_PORT_ADD("ctrl", sms_control_port_devices, "joypad")
	MCFG_SMS_CONTROL_PORT_TH_INPUT_HANDLER(WRITELINE(sms_ctrl_adaptor_device, th_pin_w))
	MCFG_SMS_CONTROL_PORT_PIXEL_HANDLER(READ32(sms_ctrl_adaptor_device, pixel_r))
MACHINE_CONFIG_END

<<<<<<< HEAD

machine_config_constructor sms_ctrl_adaptor_device::device_mconfig_additions() const
{
	return MACHINE_CONFIG_NAME( sms_adp_slot );
}
=======
>>>>>>> upstream/master
