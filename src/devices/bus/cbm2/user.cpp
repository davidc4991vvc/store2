// license:BSD-3-Clause
// copyright-holders:Curt Coder
/**********************************************************************

    Commodore CBM-II User Port emulation

**********************************************************************/

<<<<<<< HEAD
=======
#include "emu.h"
>>>>>>> upstream/master
#include "user.h"



//**************************************************************************
//  DEVICE DEFINITIONS
//**************************************************************************

<<<<<<< HEAD
const device_type CBM2_USER_PORT = &device_creator<cbm2_user_port_device>;
=======
DEFINE_DEVICE_TYPE(CBM2_USER_PORT, cbm2_user_port_device, "cbm2_user_port", "CBM-II user port")
>>>>>>> upstream/master



//**************************************************************************
//  CARD INTERFACE
//**************************************************************************

//-------------------------------------------------
//  device_cbm2_user_port_interface - constructor
//-------------------------------------------------

device_cbm2_user_port_interface::device_cbm2_user_port_interface(const machine_config &mconfig, device_t &device) :
	device_slot_card_interface(mconfig,device)
{
	m_slot = dynamic_cast<cbm2_user_port_device *>(device.owner());
}



//**************************************************************************
//  LIVE DEVICE
//**************************************************************************

//-------------------------------------------------
//  cbm2_user_port_device - constructor
//-------------------------------------------------

<<<<<<< HEAD
cbm2_user_port_device::cbm2_user_port_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock) :
	device_t(mconfig, CBM2_USER_PORT, "CBM2 user port", tag, owner, clock, "cbm2_user_port", __FILE__),
=======
cbm2_user_port_device::cbm2_user_port_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock) :
	device_t(mconfig, CBM2_USER_PORT, tag, owner, clock),
>>>>>>> upstream/master
	device_slot_interface(mconfig, *this),
	m_write_irq(*this),
	m_write_sp(*this),
	m_write_cnt(*this),
	m_write_flag(*this), m_card(nullptr)
{
}


//-------------------------------------------------
//  device_start - device-specific startup
//-------------------------------------------------

void cbm2_user_port_device::device_start()
{
	m_card = dynamic_cast<device_cbm2_user_port_interface *>(get_card_device());

	// resolve callbacks
	m_write_irq.resolve_safe();
	m_write_sp.resolve_safe();
	m_write_cnt.resolve_safe();
	m_write_flag.resolve_safe();
}


//-------------------------------------------------
//  SLOT_INTERFACE( cbm2_user_port_cards )
//-------------------------------------------------

SLOT_INTERFACE_START( cbm2_user_port_cards )
SLOT_INTERFACE_END
