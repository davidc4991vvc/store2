// license:BSD-3-Clause
// copyright-holders:Curt Coder
/**********************************************************************

    Coleco Adam Internal 64KB RAM Expansion emulation

**********************************************************************/

<<<<<<< HEAD
=======
#include "emu.h"
>>>>>>> upstream/master
#include "ram.h"



//**************************************************************************
//  DEVICE DEFINITIONS
//**************************************************************************

<<<<<<< HEAD
const device_type ADAM_RAM = &device_creator<adam_ram_expansion_device>;
=======
DEFINE_DEVICE_TYPE(ADAM_RAM, adam_ram_expansion_device, "adam_ram", "Adam 64KB RAM expansion")
>>>>>>> upstream/master



//**************************************************************************
//  LIVE DEVICE
//**************************************************************************

//-------------------------------------------------
//  adam_ram_expansion_device - constructor
//-------------------------------------------------

<<<<<<< HEAD
adam_ram_expansion_device::adam_ram_expansion_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock) :
	device_t(mconfig, ADAM_RAM, "Adam 64KB RAM expansion", tag, owner, clock, "adam_ram", __FILE__),
=======
adam_ram_expansion_device::adam_ram_expansion_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock) :
	device_t(mconfig, ADAM_RAM, tag, owner, clock),
>>>>>>> upstream/master
	device_adam_expansion_slot_card_interface(mconfig, *this),
	m_ram(*this, "ram")
{
}


//-------------------------------------------------
//  device_start - device-specific startup
//-------------------------------------------------

void adam_ram_expansion_device::device_start()
{
	m_ram.allocate(0x10000);
}


//-------------------------------------------------
//  adam_bd_r - buffered data read
//-------------------------------------------------

<<<<<<< HEAD
UINT8 adam_ram_expansion_device::adam_bd_r(address_space &space, offs_t offset, UINT8 data, int bmreq, int biorq, int aux_rom_cs, int cas1, int cas2)
=======
uint8_t adam_ram_expansion_device::adam_bd_r(address_space &space, offs_t offset, uint8_t data, int bmreq, int biorq, int aux_rom_cs, int cas1, int cas2)
>>>>>>> upstream/master
{
	if (!cas2)
	{
		data = m_ram[offset];
	}

	return data;
}


//-------------------------------------------------
//  adam_bd_w - buffered data write
//-------------------------------------------------

<<<<<<< HEAD
void adam_ram_expansion_device::adam_bd_w(address_space &space, offs_t offset, UINT8 data, int bmreq, int biorq, int aux_rom_cs, int cas1, int cas2)
=======
void adam_ram_expansion_device::adam_bd_w(address_space &space, offs_t offset, uint8_t data, int bmreq, int biorq, int aux_rom_cs, int cas1, int cas2)
>>>>>>> upstream/master
{
	if (!cas2)
	{
		m_ram[offset] = data;
	}
}
