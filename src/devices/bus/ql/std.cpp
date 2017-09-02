// license:BSD-3-Clause
// copyright-holders:Curt Coder
/**********************************************************************

    Sinclair QL standard ROM cartridge emulation

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
const device_type QL_STANDARD_ROM_CARTRIDGE = &device_creator<ql_standard_rom_cartridge_t>;
=======
DEFINE_DEVICE_TYPE(QL_STANDARD_ROM_CARTRIDGE, ql_standard_rom_cartridge_device, "ql_standard", "QL standard ROM cartridge")
>>>>>>> upstream/master



//**************************************************************************
//  LIVE DEVICE
//**************************************************************************

//-------------------------------------------------
<<<<<<< HEAD
//  ql_standard_rom_cartridge_t - constructor
//-------------------------------------------------

ql_standard_rom_cartridge_t::ql_standard_rom_cartridge_t(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock) :
	device_t(mconfig, QL_STANDARD_ROM_CARTRIDGE, "QL standard ROM cartridge", tag, owner, clock, "ql_standard", __FILE__),
=======
//  ql_standard_rom_cartridge_device - constructor
//-------------------------------------------------

ql_standard_rom_cartridge_device::ql_standard_rom_cartridge_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock) :
	device_t(mconfig, QL_STANDARD_ROM_CARTRIDGE, tag, owner, clock),
>>>>>>> upstream/master
	device_ql_rom_cartridge_card_interface(mconfig, *this)
{
}


//-------------------------------------------------
//  device_start - device-specific startup
//-------------------------------------------------

<<<<<<< HEAD
void ql_standard_rom_cartridge_t::device_start()
=======
void ql_standard_rom_cartridge_device::device_start()
>>>>>>> upstream/master
{
}


//-------------------------------------------------
//  read - cartridge data read
//-------------------------------------------------

<<<<<<< HEAD
UINT8 ql_standard_rom_cartridge_t::read(address_space &space, offs_t offset, UINT8 data)
=======
uint8_t ql_standard_rom_cartridge_device::read(address_space &space, offs_t offset, uint8_t data)
>>>>>>> upstream/master
{
	if (m_romoeh && m_rom.bytes())
	{
		data = m_rom[offset & m_rom.mask()];
	}

	return data;
}
