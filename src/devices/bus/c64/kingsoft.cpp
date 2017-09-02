// license:BSD-3-Clause
// copyright-holders:Curt Coder
/**********************************************************************

    Kingsoft cartridge emulation

**********************************************************************/

<<<<<<< HEAD
=======
#include "emu.h"
>>>>>>> upstream/master
#include "kingsoft.h"



//**************************************************************************
//  DEVICE DEFINITIONS
//**************************************************************************

<<<<<<< HEAD
const device_type C64_KINGSOFT = &device_creator<c64_kingsoft_cartridge_device>;
=======
DEFINE_DEVICE_TYPE(C64_KINGSOFT, c64_kingsoft_cartridge_device, "c64_kingsoft", "C64 Kingsoft cartridge")
>>>>>>> upstream/master



//**************************************************************************
//  LIVE DEVICE
//**************************************************************************

//-------------------------------------------------
//  c64_kingsoft_cartridge_device - constructor
//-------------------------------------------------

<<<<<<< HEAD
c64_kingsoft_cartridge_device::c64_kingsoft_cartridge_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock) :
	device_t(mconfig, C64_KINGSOFT, "C64 Kingsoft cartridge", tag, owner, clock, "c64_kingsoft", __FILE__),
=======
c64_kingsoft_cartridge_device::c64_kingsoft_cartridge_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock) :
	device_t(mconfig, C64_KINGSOFT, tag, owner, clock),
>>>>>>> upstream/master
	device_c64_expansion_card_interface(mconfig, *this)
{
}


//-------------------------------------------------
//  device_start - device-specific startup
//-------------------------------------------------

void c64_kingsoft_cartridge_device::device_start()
{
}


//-------------------------------------------------
//  device_reset - device-specific reset
//-------------------------------------------------

void c64_kingsoft_cartridge_device::device_reset()
{
	m_exrom = 0;
}


//-------------------------------------------------
//  c64_cd_r - cartridge data read
//-------------------------------------------------

<<<<<<< HEAD
UINT8 c64_kingsoft_cartridge_device::c64_cd_r(address_space &space, offs_t offset, UINT8 data, int sphi2, int ba, int roml, int romh, int io1, int io2)
=======
uint8_t c64_kingsoft_cartridge_device::c64_cd_r(address_space &space, offs_t offset, uint8_t data, int sphi2, int ba, int roml, int romh, int io1, int io2)
>>>>>>> upstream/master
{
	if (!roml)
	{
		data = m_roml[offset & 0x1fff];
	}
	else if (!romh)
	{
		data = m_romh[(m_exrom << 13) | (offset & 0x1fff)];
	}
	else if (!io1)
	{
		m_exrom = 0;
	}

	return data;
}


//-------------------------------------------------
//  c64_cd_w - cartridge data write
//-------------------------------------------------

<<<<<<< HEAD
void c64_kingsoft_cartridge_device::c64_cd_w(address_space &space, offs_t offset, UINT8 data, int sphi2, int ba, int roml, int romh, int io1, int io2)
=======
void c64_kingsoft_cartridge_device::c64_cd_w(address_space &space, offs_t offset, uint8_t data, int sphi2, int ba, int roml, int romh, int io1, int io2)
>>>>>>> upstream/master
{
	if (!io1)
	{
		m_exrom = 1;
	}
}


//-------------------------------------------------
//  c64_game_r - GAME read
//-------------------------------------------------

int c64_kingsoft_cartridge_device::c64_game_r(offs_t offset, int sphi2, int ba, int rw)
{
	return m_exrom & ((ba & rw & ((offset >= 0x8000 && offset < 0xc000) || (offset >= 0xe000))) ? 0 : 1);
}
