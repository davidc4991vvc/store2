// license:BSD-3-Clause
// copyright-holders:Curt Coder
/**********************************************************************

    Dinamic Software cartridge emulation

**********************************************************************/

<<<<<<< HEAD
=======
#include "emu.h"
>>>>>>> upstream/master
#include "dinamic.h"



//**************************************************************************
//  DEVICE DEFINITIONS
//**************************************************************************

<<<<<<< HEAD
const device_type C64_DINAMIC = &device_creator<c64_dinamic_cartridge_device>;
=======
DEFINE_DEVICE_TYPE(C64_DINAMIC, c64_dinamic_cartridge_device, "c64_dinamic", "C64 Dinamic cartridge")
>>>>>>> upstream/master



//**************************************************************************
//  LIVE DEVICE
//**************************************************************************

//-------------------------------------------------
//  c64_dinamic_cartridge_device - constructor
//-------------------------------------------------

<<<<<<< HEAD
c64_dinamic_cartridge_device::c64_dinamic_cartridge_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock) :
	device_t(mconfig, C64_DINAMIC, "C64 Dinamic cartridge", tag, owner, clock, "c64_dinamic", __FILE__),
=======
c64_dinamic_cartridge_device::c64_dinamic_cartridge_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock) :
	device_t(mconfig, C64_DINAMIC, tag, owner, clock),
>>>>>>> upstream/master
	device_c64_expansion_card_interface(mconfig, *this),
	m_bank(0)
{
}


//-------------------------------------------------
//  device_start - device-specific startup
//-------------------------------------------------

void c64_dinamic_cartridge_device::device_start()
{
	// state saving
	save_item(NAME(m_bank));
}


//-------------------------------------------------
//  device_reset - device-specific reset
//-------------------------------------------------

void c64_dinamic_cartridge_device::device_reset()
{
	m_bank = 0;
}


//-------------------------------------------------
//  c64_cd_r - cartridge data read
//-------------------------------------------------

<<<<<<< HEAD
UINT8 c64_dinamic_cartridge_device::c64_cd_r(address_space &space, offs_t offset, UINT8 data, int sphi2, int ba, int roml, int romh, int io1, int io2)
=======
uint8_t c64_dinamic_cartridge_device::c64_cd_r(address_space &space, offs_t offset, uint8_t data, int sphi2, int ba, int roml, int romh, int io1, int io2)
>>>>>>> upstream/master
{
	if (!roml)
	{
		offs_t addr = (m_bank << 13) | (offset & 0x1fff);
		data = m_roml[addr];
	}
	else if (!io1)
	{
		m_bank = offset & 0x0f;
	}

	return data;
}
