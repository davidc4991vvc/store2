// license:BSD-3-Clause
// copyright-holders:Curt Coder
/**********************************************************************

    Rex Datentechnik 256KB EPROM cartridge emulation

**********************************************************************/

<<<<<<< HEAD
=======
#include "emu.h"
>>>>>>> upstream/master
#include "rex_ep256.h"



//**************************************************************************
//  DEVICE DEFINITIONS
//**************************************************************************

<<<<<<< HEAD
const device_type C64_REX_EP256 = &device_creator<c64_rex_ep256_cartridge_device>;


//-------------------------------------------------
//  MACHINE_CONFIG_FRAGMENT( c64_rex_ep256 )
//-------------------------------------------------

static MACHINE_CONFIG_FRAGMENT( c64_rex_ep256 )
	MCFG_GENERIC_SOCKET_ADD("rom1", generic_linear_slot, NULL)
	MCFG_GENERIC_EXTENSIONS("bin,rom")
	MCFG_GENERIC_SOCKET_ADD("rom2", generic_linear_slot, NULL)
	MCFG_GENERIC_EXTENSIONS("bin,rom")
	MCFG_GENERIC_SOCKET_ADD("rom3", generic_linear_slot, NULL)
	MCFG_GENERIC_EXTENSIONS("bin,rom")
	MCFG_GENERIC_SOCKET_ADD("rom4", generic_linear_slot, NULL)
	MCFG_GENERIC_EXTENSIONS("bin,rom")
	MCFG_GENERIC_SOCKET_ADD("rom5", generic_linear_slot, NULL)
	MCFG_GENERIC_EXTENSIONS("bin,rom")
	MCFG_GENERIC_SOCKET_ADD("rom6", generic_linear_slot, NULL)
	MCFG_GENERIC_EXTENSIONS("bin,rom")
	MCFG_GENERIC_SOCKET_ADD("rom7", generic_linear_slot, NULL)
	MCFG_GENERIC_EXTENSIONS("bin,rom")
	MCFG_GENERIC_SOCKET_ADD("rom8", generic_linear_slot, NULL)
=======
DEFINE_DEVICE_TYPE(C64_REX_EP256, c64_rex_ep256_cartridge_device, "rexexp256", "C64 Rex 256KB EPROM cartridge")


//-------------------------------------------------
//  device_add_mconfig - add device configuration
//-------------------------------------------------

MACHINE_CONFIG_MEMBER( c64_rex_ep256_cartridge_device::device_add_mconfig )
	MCFG_GENERIC_SOCKET_ADD("rom1", generic_linear_slot, nullptr)
	MCFG_GENERIC_EXTENSIONS("bin,rom")
	MCFG_GENERIC_SOCKET_ADD("rom2", generic_linear_slot, nullptr)
	MCFG_GENERIC_EXTENSIONS("bin,rom")
	MCFG_GENERIC_SOCKET_ADD("rom3", generic_linear_slot, nullptr)
	MCFG_GENERIC_EXTENSIONS("bin,rom")
	MCFG_GENERIC_SOCKET_ADD("rom4", generic_linear_slot, nullptr)
	MCFG_GENERIC_EXTENSIONS("bin,rom")
	MCFG_GENERIC_SOCKET_ADD("rom5", generic_linear_slot, nullptr)
	MCFG_GENERIC_EXTENSIONS("bin,rom")
	MCFG_GENERIC_SOCKET_ADD("rom6", generic_linear_slot, nullptr)
	MCFG_GENERIC_EXTENSIONS("bin,rom")
	MCFG_GENERIC_SOCKET_ADD("rom7", generic_linear_slot, nullptr)
	MCFG_GENERIC_EXTENSIONS("bin,rom")
	MCFG_GENERIC_SOCKET_ADD("rom8", generic_linear_slot, nullptr)
>>>>>>> upstream/master
	MCFG_GENERIC_EXTENSIONS("bin,rom")
MACHINE_CONFIG_END


<<<<<<< HEAD
//-------------------------------------------------
//  machine_config_additions - device-specific
//  machine configurations
//-------------------------------------------------

machine_config_constructor c64_rex_ep256_cartridge_device::device_mconfig_additions() const
{
	return MACHINE_CONFIG_NAME( c64_rex_ep256 );
}


=======
>>>>>>> upstream/master

//**************************************************************************
//  LIVE DEVICE
//**************************************************************************

//-------------------------------------------------
//  c64_rex_ep256_cartridge_device - constructor
//-------------------------------------------------

<<<<<<< HEAD
c64_rex_ep256_cartridge_device::c64_rex_ep256_cartridge_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock) :
	device_t(mconfig, C64_REX_EP256, "C64 Rex 256KB EPROM cartridge", tag, owner, clock, "rexep256", __FILE__),
=======
c64_rex_ep256_cartridge_device::c64_rex_ep256_cartridge_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock) :
	device_t(mconfig, C64_REX_EP256, tag, owner, clock),
>>>>>>> upstream/master
	device_c64_expansion_card_interface(mconfig, *this)
{
	for (int i = 0; i < 8; i++)
	{
		char str[6];
		sprintf(str, "rom%i", i + 1);
		m_eproms[i] = subdevice<generic_slot_device>(str);
	}
}


//-------------------------------------------------
//  device_start - device-specific startup
//-------------------------------------------------

void c64_rex_ep256_cartridge_device::device_start()
{
	// state saving
	save_item(NAME(m_bank));
	save_item(NAME(m_reset));
	save_item(NAME(m_socket));
}


//-------------------------------------------------
//  device_reset - device-specific reset
//-------------------------------------------------

void c64_rex_ep256_cartridge_device::device_reset()
{
	m_exrom = 0;
	m_reset = 1;
	m_bank = 0;
	m_socket = 0;
}


//-------------------------------------------------
//  c64_cd_r - cartridge data read
//-------------------------------------------------

<<<<<<< HEAD
UINT8 c64_rex_ep256_cartridge_device::c64_cd_r(address_space &space, offs_t offset, UINT8 data, int sphi2, int ba, int roml, int romh, int io1, int io2)
=======
uint8_t c64_rex_ep256_cartridge_device::c64_cd_r(address_space &space, offs_t offset, uint8_t data, int sphi2, int ba, int roml, int romh, int io1, int io2)
>>>>>>> upstream/master
{
	if (!roml)
	{
		if (m_reset)
		{
			data = m_roml[offset & 0x1fff];
		}
		else
		{
			offs_t addr = (m_bank << 13) | (offset & 0x1fff);
			data = m_eproms[m_socket]->read_rom(space, addr);
		}
	}
	else if (!io2)
	{
		if ((offset & 0xf0) == 0xc0)
		{
			m_exrom = 1;
		}
		else if ((offset & 0xf0) == 0xe0)
		{
			m_exrom = 0;
		}
	}

	return data;
}


//-------------------------------------------------
//  c64_cd_w - cartridge data write
//-------------------------------------------------

<<<<<<< HEAD
void c64_rex_ep256_cartridge_device::c64_cd_w(address_space &space, offs_t offset, UINT8 data, int sphi2, int ba, int roml, int romh, int io1, int io2)
=======
void c64_rex_ep256_cartridge_device::c64_cd_w(address_space &space, offs_t offset, uint8_t data, int sphi2, int ba, int roml, int romh, int io1, int io2)
>>>>>>> upstream/master
{
	if (!io2 && ((offset & 0xf0) == 0xa0))
	{
		/*

		    bit     description

		    0       socket selection bit 0
		    1       socket selection bit 1
		    2       socket selection bit 2
		    3
		    4
		    5       bank selection bit 0
		    6       bank selection bit 1
		    7

		*/

		m_reset = 0;

		m_socket = data & 0x07;
		m_bank = (data >> 5) & 0x03;
	}
}
