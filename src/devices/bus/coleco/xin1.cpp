// license:BSD-3-Clause
// copyright-holders:Wilbert Pol
/**********************************************************************

    ColecoVision X-in-1 cartridge emulation

**********************************************************************/

<<<<<<< HEAD
=======
#include "emu.h"
>>>>>>> upstream/master
#include "xin1.h"



//**************************************************************************
//  DEVICE DEFINITIONS
//**************************************************************************

<<<<<<< HEAD
const device_type COLECOVISION_XIN1 = &device_creator<colecovision_xin1_cartridge_device>;
=======
DEFINE_DEVICE_TYPE(COLECOVISION_XIN1, colecovision_xin1_cartridge_device, "colecovision_xin1", "ColecoVision X-in-1 cartridge")
>>>>>>> upstream/master



//**************************************************************************
//  LIVE DEVICE
//**************************************************************************

//-------------------------------------------------
//  colecovision_xin1_cartridge_device - constructor
//-------------------------------------------------

<<<<<<< HEAD
colecovision_xin1_cartridge_device::colecovision_xin1_cartridge_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock) :
	device_t(mconfig, COLECOVISION_XIN1, "ColecoVision X-in-1 cartridge", tag, owner, clock, "colecovision_xin1", __FILE__),
=======
colecovision_xin1_cartridge_device::colecovision_xin1_cartridge_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock) :
	device_t(mconfig, COLECOVISION_XIN1, tag, owner, clock),
>>>>>>> upstream/master
	device_colecovision_cartridge_interface(mconfig, *this),
	m_current_offset(0)
{
}


//-------------------------------------------------
//  device_start - device-specific startup
//-------------------------------------------------

void colecovision_xin1_cartridge_device::device_start()
{
}


//-------------------------------------------------
//  device_reset - device-specific reset
//-------------------------------------------------

void colecovision_xin1_cartridge_device::device_reset()
{
	m_current_offset = m_rom_size - 0x8000;
}


//-------------------------------------------------
//  read - cartridge data read
//-------------------------------------------------

<<<<<<< HEAD
UINT8 colecovision_xin1_cartridge_device::bd_r(address_space &space, offs_t offset, UINT8 data, int _8000, int _a000, int _c000, int _e000)
=======
uint8_t colecovision_xin1_cartridge_device::bd_r(address_space &space, offs_t offset, uint8_t data, int _8000, int _a000, int _c000, int _e000)
>>>>>>> upstream/master
{
	if (!_8000 || !_a000 || !_c000 || !_e000)
	{
		data = m_rom[m_current_offset + offset];
		if (!_e000 && offset >= 0x7fc0) {
			m_current_offset = (0x8000 * (offset - 0x7fc0)) % m_rom_size;
		}
	}

	return data;
}
