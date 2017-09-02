// license:BSD-3-Clause
// copyright-holders:smf
/**********************************************************************

    Commodore VIC-1011A/B RS-232C Adapter emulation

**********************************************************************/

<<<<<<< HEAD
=======
#include "emu.h"
>>>>>>> upstream/master
#include "vic1011.h"



//**************************************************************************
//  MACROS/CONSTANTS
//**************************************************************************

#define RS232_TAG       "rs232"



//**************************************************************************
//  DEVICE DEFINITIONS
//**************************************************************************

<<<<<<< HEAD
const device_type VIC1011 = &device_creator<vic1011_device>;


//-------------------------------------------------
//  MACHINE_DRIVER( vic1011 )
//-------------------------------------------------

static MACHINE_CONFIG_FRAGMENT( vic1011 )
	MCFG_RS232_PORT_ADD(RS232_TAG, default_rs232_devices, NULL)
=======
DEFINE_DEVICE_TYPE(VIC1011, vic1011_device, "vic1011", "VIC-1011 RS-232C")


//-------------------------------------------------
//  device_add_mconfig - add device configuration
//-------------------------------------------------

MACHINE_CONFIG_MEMBER( vic1011_device::device_add_mconfig )
	MCFG_RS232_PORT_ADD(RS232_TAG, default_rs232_devices, nullptr)
>>>>>>> upstream/master
	MCFG_RS232_RXD_HANDLER(DEVWRITELINE(DEVICE_SELF, vic1011_device, output_rxd))
	MCFG_RS232_DCD_HANDLER(DEVWRITELINE(DEVICE_SELF, vic1011_device, output_h)) MCFG_DEVCB_XOR(1)
	MCFG_RS232_CTS_HANDLER(DEVWRITELINE(DEVICE_SELF, vic1011_device, output_k)) MCFG_DEVCB_XOR(1)
	MCFG_RS232_DSR_HANDLER(DEVWRITELINE(DEVICE_SELF, vic1011_device, output_l)) MCFG_DEVCB_XOR(1)
MACHINE_CONFIG_END


<<<<<<< HEAD
//-------------------------------------------------
//  machine_config_additions - device-specific
//  machine configurations
//-------------------------------------------------

machine_config_constructor vic1011_device::device_mconfig_additions() const
{
	return MACHINE_CONFIG_NAME( vic1011 );
}



=======
>>>>>>> upstream/master
//**************************************************************************
//  LIVE DEVICE
//**************************************************************************

//-------------------------------------------------
//  vic1011_device - constructor
//-------------------------------------------------

<<<<<<< HEAD
vic1011_device::vic1011_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock)
	: device_t(mconfig, VIC1011, "VIC1011", tag, owner, clock, "vic1011", __FILE__),
		device_pet_user_port_interface(mconfig, *this),
		m_rs232(*this, RS232_TAG)
=======
vic1011_device::vic1011_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock)
	: device_t(mconfig, VIC1011, tag, owner, clock)
	, device_pet_user_port_interface(mconfig, *this)
	, m_rs232(*this, RS232_TAG)
>>>>>>> upstream/master
{
}


//-------------------------------------------------
//  device_start - device-specific startup
//-------------------------------------------------

void vic1011_device::device_start()
{
}

WRITE_LINE_MEMBER( vic1011_device::output_rxd )
{
	output_b(state);
	output_c(state);
}

void vic1011_device::input_d(int state)
{
	m_rs232->write_rts(!state);
}

void vic1011_device::input_e(int state)
{
	m_rs232->write_dtr(!state);
}

void vic1011_device::input_j(int state)
{
	/// dcdout
}

void vic1011_device::input_m(int state)
{
	m_rs232->write_txd(state);
}
