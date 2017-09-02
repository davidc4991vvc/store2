// license:BSD-3-Clause
// copyright-holders:Curt Coder
/**********************************************************************

    Zaxxon/Super Zaxxon cartridge emulation

**********************************************************************/

<<<<<<< HEAD
=======
#include "emu.h"
>>>>>>> upstream/master
#include "zaxxon.h"



//**************************************************************************
//  DEVICE DEFINITIONS
//**************************************************************************

<<<<<<< HEAD
const device_type C64_ZAXXON = &device_creator<c64_zaxxon_cartridge_device>;
=======
DEFINE_DEVICE_TYPE(C64_ZAXXON, c64_zaxxon_cartridge_device, "c64_zaxxon", "C64 Zaxxon cartridge")
>>>>>>> upstream/master



//**************************************************************************
//  LIVE DEVICE
//**************************************************************************

//-------------------------------------------------
//  c64_zaxxon_cartridge_device - constructor
//-------------------------------------------------

<<<<<<< HEAD
c64_zaxxon_cartridge_device::c64_zaxxon_cartridge_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock) :
	device_t(mconfig, C64_ZAXXON, "C64 Zaxxon cartridge", tag, owner, clock, "c64_zaxxon", __FILE__),
=======
c64_zaxxon_cartridge_device::c64_zaxxon_cartridge_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock) :
	device_t(mconfig, C64_ZAXXON, tag, owner, clock),
>>>>>>> upstream/master
	device_c64_expansion_card_interface(mconfig, *this),
	m_bank(0)
{
}


//-------------------------------------------------
//  device_start - device-specific startup
//-------------------------------------------------

void c64_zaxxon_cartridge_device::device_start()
{
	// state saving
	save_item(NAME(m_bank));
}


//-------------------------------------------------
//  c64_cd_r - cartridge data read
//-------------------------------------------------

<<<<<<< HEAD
UINT8 c64_zaxxon_cartridge_device::c64_cd_r(address_space &space, offs_t offset, UINT8 data, int sphi2, int ba, int roml, int romh, int io1, int io2)
=======
uint8_t c64_zaxxon_cartridge_device::c64_cd_r(address_space &space, offs_t offset, uint8_t data, int sphi2, int ba, int roml, int romh, int io1, int io2)
>>>>>>> upstream/master
{
	if (!roml)
	{
		data = m_roml[offset & 0xfff];

		m_bank = BIT(offset, 12);
	}
	else if (!romh)
	{
		offs_t addr = (m_bank << 13) | (offset & 0x1fff);
		data = m_romh[addr];
	}

	return data;
}
