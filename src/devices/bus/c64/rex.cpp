// license:BSD-3-Clause
// copyright-holders:Curt Coder
/**********************************************************************

    REX Datentechnik cartridge emulation

**********************************************************************/

<<<<<<< HEAD
=======
#include "emu.h"
>>>>>>> upstream/master
#include "rex.h"



//**************************************************************************
//  DEVICE DEFINITIONS
//**************************************************************************

<<<<<<< HEAD
const device_type C64_REX = &device_creator<c64_rex_cartridge_device>;
=======
DEFINE_DEVICE_TYPE(C64_REX, c64_rex_cartridge_device, "c64_rex", "C64 Rex cartridge")
>>>>>>> upstream/master



//**************************************************************************
//  LIVE DEVICE
//**************************************************************************

//-------------------------------------------------
//  c64_rex_cartridge_device - constructor
//-------------------------------------------------

<<<<<<< HEAD
c64_rex_cartridge_device::c64_rex_cartridge_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock) :
	device_t(mconfig, C64_REX, "C64 Rex cartridge", tag, owner, clock, "c64_rex", __FILE__),
=======
c64_rex_cartridge_device::c64_rex_cartridge_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock) :
	device_t(mconfig, C64_REX, tag, owner, clock),
>>>>>>> upstream/master
	device_c64_expansion_card_interface(mconfig, *this)
{
}


//-------------------------------------------------
//  device_start - device-specific startup
//-------------------------------------------------

void c64_rex_cartridge_device::device_start()
{
}


//-------------------------------------------------
//  device_reset - device-specific reset
//-------------------------------------------------

void c64_rex_cartridge_device::device_reset()
{
	m_exrom = 0;
}


//-------------------------------------------------
//  c64_cd_r - cartridge data read
//-------------------------------------------------

<<<<<<< HEAD
UINT8 c64_rex_cartridge_device::c64_cd_r(address_space &space, offs_t offset, UINT8 data, int sphi2, int ba, int roml, int romh, int io1, int io2)
=======
uint8_t c64_rex_cartridge_device::c64_cd_r(address_space &space, offs_t offset, uint8_t data, int sphi2, int ba, int roml, int romh, int io1, int io2)
>>>>>>> upstream/master
{
	if (!roml)
	{
		data = m_roml[offset & 0x1fff];
	}
	else if (!io2)
	{
		if ((offset & 0xc0) == 0xc0)
		{
			m_exrom = 0;
		}
		else
		{
			m_exrom = 1;
		}
	}

	return data;
}
