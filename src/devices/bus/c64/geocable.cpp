// license:BSD-3-Clause
// copyright-holders:Curt Coder, smf
/**********************************************************************

    geoCable Centronics Cable emulation

**********************************************************************/

<<<<<<< HEAD
=======
#include "emu.h"
>>>>>>> upstream/master
#include "geocable.h"



//**************************************************************************
//  MACROS / CONSTANTS
//**************************************************************************

#define CENTRONICS_TAG "centronics"



//**************************************************************************
//  DEVICE DEFINITIONS
//**************************************************************************

<<<<<<< HEAD
const device_type C64_GEOCABLE = &device_creator<c64_geocable_device>;


//-------------------------------------------------
//  MACHINE_CONFIG_FRAGMENT( c64_geocable )
//-------------------------------------------------

static MACHINE_CONFIG_FRAGMENT( c64_geocable )
=======
DEFINE_DEVICE_TYPE(C64_GEOCABLE, c64_geocable_device, "c64_geocable", "C64 geoCable")


//-------------------------------------------------
//  device_add_mconfig - add device configuration
//-------------------------------------------------

MACHINE_CONFIG_MEMBER( c64_geocable_device::device_add_mconfig )
>>>>>>> upstream/master
	MCFG_CENTRONICS_ADD("centronics", centronics_devices, "printer")
	MCFG_CENTRONICS_BUSY_HANDLER(WRITELINE(c64_geocable_device, output_b))
MACHINE_CONFIG_END


<<<<<<< HEAD
//-------------------------------------------------
//  machine_config_additions - device-specific
//  machine configurations
//-------------------------------------------------

machine_config_constructor c64_geocable_device::device_mconfig_additions() const
{
	return MACHINE_CONFIG_NAME( c64_geocable );
}


=======
>>>>>>> upstream/master

//**************************************************************************
//  LIVE DEVICE
//**************************************************************************

//-------------------------------------------------
//  c64_geocable_device - constructor
//-------------------------------------------------

<<<<<<< HEAD
c64_geocable_device::c64_geocable_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock) :
	device_t(mconfig, C64_GEOCABLE, "C64 geoCable", tag, owner, clock, "c64_geocable", __FILE__),
=======
c64_geocable_device::c64_geocable_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock) :
	device_t(mconfig, C64_GEOCABLE, tag, owner, clock),
>>>>>>> upstream/master
	device_pet_user_port_interface(mconfig, *this),
	m_centronics(*this, CENTRONICS_TAG)
{
}


//-------------------------------------------------
//  device_start - device-specific startup
//-------------------------------------------------

void c64_geocable_device::device_start()
{
}
