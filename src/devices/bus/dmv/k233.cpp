// license:BSD-3-Clause
// copyright-holders:Sandro Ronco
/***************************************************************************

    K233 16K Shared RAM

***************************************************************************/

#include "emu.h"
#include "k233.h"


/***************************************************************************
    IMPLEMENTATION
***************************************************************************/

//**************************************************************************
//  GLOBAL VARIABLES
//**************************************************************************

<<<<<<< HEAD
const device_type DMV_K233 = &device_creator<dmv_k233_device>;
=======
DEFINE_DEVICE_TYPE(DMV_K233, dmv_k233_device, "dmv_k233", "K233 16K Shared RAM")
>>>>>>> upstream/master

//**************************************************************************
//  LIVE DEVICE
//**************************************************************************

//-------------------------------------------------
//  dmv_k233_device - constructor
//-------------------------------------------------

<<<<<<< HEAD
dmv_k233_device::dmv_k233_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock)
		: device_t(mconfig, DMV_K233, "K233 16K Shared RAM", tag, owner, clock, "dmv_k233", __FILE__),
		device_dmvslot_interface( mconfig, *this ),
	m_enabled(false),
	m_ram(nullptr)
	{
=======
dmv_k233_device::dmv_k233_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock)
	: device_t(mconfig, DMV_K233, tag, owner, clock)
	, device_dmvslot_interface(mconfig, *this)
	, m_enabled(false)
	, m_ram(nullptr)
{
>>>>>>> upstream/master
}

//-------------------------------------------------
//  device_start - device-specific startup
//-------------------------------------------------

void dmv_k233_device::device_start()
{
	m_ram = machine().memory().region_alloc( "sharedram", 0x4000, 1, ENDIANNESS_LITTLE )->base();
}

//-------------------------------------------------
//  device_reset - device-specific reset
//-------------------------------------------------

void dmv_k233_device::device_reset()
{
	m_enabled = false;
}

<<<<<<< HEAD
void dmv_k233_device::io_write(address_space &space, int ifsel, offs_t offset, UINT8 data)
=======
void dmv_k233_device::io_write(address_space &space, int ifsel, offs_t offset, uint8_t data)
>>>>>>> upstream/master
{
	if (ifsel == 1)
		m_enabled = !m_enabled;
}

//-------------------------------------------------
//  read
//-------------------------------------------------

<<<<<<< HEAD
bool dmv_k233_device::read(offs_t offset, UINT8 &data)
=======
bool dmv_k233_device::read(offs_t offset, uint8_t &data)
>>>>>>> upstream/master
{
	if (m_enabled && offset >= 0xc000 && offset < 0x10000)
	{
		data = m_ram[offset & 0x3fff];
		return true;
	}

	return false;
}

//-------------------------------------------------
//  write
//-------------------------------------------------

<<<<<<< HEAD
bool dmv_k233_device::write(offs_t offset, UINT8 data)
=======
bool dmv_k233_device::write(offs_t offset, uint8_t data)
>>>>>>> upstream/master
{
	if (m_enabled && offset >= 0xc000 && offset < 0x10000)
	{
		m_ram[offset & 0x3fff] = data;
		return true;
	}

	return false;
}
