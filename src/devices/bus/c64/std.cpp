// license:BSD-3-Clause
// copyright-holders:Curt Coder
/**********************************************************************

    Commodore 64 Standard 8K/16K cartridge emulation

**********************************************************************/

<<<<<<< HEAD
=======
#include "emu.h"
>>>>>>> upstream/master
#include "std.h"



//**************************************************************************
//  DEVICE DEFINITIONS
//**************************************************************************

<<<<<<< HEAD
const device_type C64_STD = &device_creator<c64_standard_cartridge_device>;
=======
DEFINE_DEVICE_TYPE(C64_STD, c64_standard_cartridge_device, "c64_standard", "C64 standard cartridge")
>>>>>>> upstream/master



//**************************************************************************
//  LIVE DEVICE
//**************************************************************************

//-------------------------------------------------
//  c64_standard_cartridge_device - constructor
//-------------------------------------------------

<<<<<<< HEAD
c64_standard_cartridge_device::c64_standard_cartridge_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock) :
	device_t(mconfig, C64_STD, "C64 standard cartridge", tag, owner, clock, "c64_standard", __FILE__),
=======
c64_standard_cartridge_device::c64_standard_cartridge_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock) :
	device_t(mconfig, C64_STD, tag, owner, clock),
>>>>>>> upstream/master
	device_c64_expansion_card_interface(mconfig, *this)
{
}


//-------------------------------------------------
//  device_start - device-specific startup
//-------------------------------------------------

void c64_standard_cartridge_device::device_start()
{
}


//-------------------------------------------------
//  c64_cd_r - cartridge data read
//-------------------------------------------------

<<<<<<< HEAD
UINT8 c64_standard_cartridge_device::c64_cd_r(address_space &space, offs_t offset, UINT8 data, int sphi2, int ba, int roml, int romh, int io1, int io2)
=======
uint8_t c64_standard_cartridge_device::c64_cd_r(address_space &space, offs_t offset, uint8_t data, int sphi2, int ba, int roml, int romh, int io1, int io2)
>>>>>>> upstream/master
{
	if (!roml && m_roml.bytes())
	{
		data = m_roml[offset & m_roml.mask()];
	}
	else if (!romh)
	{
		if (m_romh.bytes())
		{
			data = m_romh[offset & m_romh.mask()];
		}
		else if (m_roml.mask() == 0x3fff)
		{
			data = m_roml[offset & m_roml.mask()];
		}
	}

	return data;
}
