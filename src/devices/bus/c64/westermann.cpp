// license:BSD-3-Clause
// copyright-holders:Curt Coder
/**********************************************************************

    Westermann Learning cartridge emulation

**********************************************************************/

<<<<<<< HEAD
=======
#include "emu.h"
>>>>>>> upstream/master
#include "westermann.h"



//**************************************************************************
//  DEVICE DEFINITIONS
//**************************************************************************

<<<<<<< HEAD
const device_type C64_WESTERMANN = &device_creator<c64_westermann_cartridge_device>;
=======
DEFINE_DEVICE_TYPE(C64_WESTERMANN, c64_westermann_cartridge_device, "c64_westermann", "C64 Westermann cartridge")
>>>>>>> upstream/master



//**************************************************************************
//  LIVE DEVICE
//**************************************************************************

//-------------------------------------------------
//  c64_westermann_cartridge_device - constructor
//-------------------------------------------------

<<<<<<< HEAD
c64_westermann_cartridge_device::c64_westermann_cartridge_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock) :
	device_t(mconfig, C64_WESTERMANN, "C64 Westermann cartridge", tag, owner, clock, "c64_westermann", __FILE__),
=======
c64_westermann_cartridge_device::c64_westermann_cartridge_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock) :
	device_t(mconfig, C64_WESTERMANN, tag, owner, clock),
>>>>>>> upstream/master
	device_c64_expansion_card_interface(mconfig, *this)
{
}


//-------------------------------------------------
//  device_start - device-specific startup
//-------------------------------------------------

void c64_westermann_cartridge_device::device_start()
{
}


//-------------------------------------------------
//  device_reset - device-specific reset
//-------------------------------------------------

void c64_westermann_cartridge_device::device_reset()
{
	m_game = 0;
}


//-------------------------------------------------
//  c64_cd_r - cartridge data read
//-------------------------------------------------

<<<<<<< HEAD
UINT8 c64_westermann_cartridge_device::c64_cd_r(address_space &space, offs_t offset, UINT8 data, int sphi2, int ba, int roml, int romh, int io1, int io2)
=======
uint8_t c64_westermann_cartridge_device::c64_cd_r(address_space &space, offs_t offset, uint8_t data, int sphi2, int ba, int roml, int romh, int io1, int io2)
>>>>>>> upstream/master
{
	if (!roml)
	{
		data = m_roml[offset & m_roml.mask()];
	}
	else if (!romh)
	{
		if (m_romh.bytes())
		{
			data = m_romh[offset & m_romh.mask()];
		}
		else
		{
			data = m_roml[offset & m_roml.mask()];
		}
	}
	else if (!io2)
	{
		m_game = 1;
	}

	return data;
}
