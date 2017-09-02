// license:BSD-3-Clause
// copyright-holders:smf
/**********************************************************************

    Commodore PET User Port Diagnostic Connector emulation

**********************************************************************/

<<<<<<< HEAD
=======
#include "emu.h"
>>>>>>> upstream/master
#include "diag.h"



//**************************************************************************
//  DEVICE DEFINITIONS
//**************************************************************************

<<<<<<< HEAD
const device_type PET_USERPORT_DIAGNOSTIC_CONNECTOR = &device_creator<pet_userport_diagnostic_connector_t>;
=======
DEFINE_DEVICE_TYPE(PET_USERPORT_DIAGNOSTIC_CONNECTOR, pet_userport_diagnostic_connector_device, "pet_user_diag", "PET Userport Diagnostic Connector")
>>>>>>> upstream/master



//**************************************************************************
//  LIVE DEVICE
//**************************************************************************

//-------------------------------------------------
//  pet_userport_diagnostic_connector_t - constructor
//-------------------------------------------------

<<<<<<< HEAD
pet_userport_diagnostic_connector_t::pet_userport_diagnostic_connector_t(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock) :
	device_t(mconfig, PET_USERPORT_DIAGNOSTIC_CONNECTOR, "PET Userport Diagnostic Connector", tag, owner, clock, "pet_user_diag", __FILE__),
=======
pet_userport_diagnostic_connector_device::pet_userport_diagnostic_connector_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock) :
	device_t(mconfig, PET_USERPORT_DIAGNOSTIC_CONNECTOR, tag, owner, clock),
>>>>>>> upstream/master
	device_pet_user_port_interface(mconfig, *this)
{
}


//-------------------------------------------------
//  device_start - device-specific startup
//-------------------------------------------------

<<<<<<< HEAD
void pet_userport_diagnostic_connector_t::device_start()
=======
void pet_userport_diagnostic_connector_device::device_start()
>>>>>>> upstream/master
{
	output_5(0);
	output_e(0);
}
