// license:BSD-3-Clause
// copyright-holders:Curt Coder
/**********************************************************************

    TIKI-100 8/16 8088/8087 expansion card emulation

**********************************************************************/

<<<<<<< HEAD
=======
#include "emu.h"
>>>>>>> upstream/master
#include "8088.h"



//**************************************************************************
//  MACROS/CONSTANTS
//**************************************************************************

#define I8088_TAG   "u3"



//**************************************************************************
//  DEVICE DEFINITIONS
//**************************************************************************

<<<<<<< HEAD
const device_type TIKI100_8088 = &device_creator<tiki100_8088_t>;
=======
DEFINE_DEVICE_TYPE(TIKI100_8088, tiki100_8088_device, "tiki100_8088", "TIKI-100 8/16")
>>>>>>> upstream/master


//-------------------------------------------------
//  ROM( tiki100_8088 )
//-------------------------------------------------

ROM_START( tiki100_8088 )
	ROM_REGION( 0x1000, I8088_TAG, 0 )
	ROM_LOAD( "boot 1.0.u3", 0x0000, 0x1000, CRC(436974aa) SHA1(837087b3ab982d047e4f15799fef3daa37dd6c01) )

	ROM_REGION( 0x100, "u26", 0 )
	ROM_LOAD( "53ls140.u26", 0x000, 0x100, CRC(fc5902e1) SHA1(afb9cb54ab6fc449e7544ddb3cbebc3770c4f937) )
ROM_END


//-------------------------------------------------
//  rom_region - device-specific ROM region
//-------------------------------------------------

<<<<<<< HEAD
const rom_entry *tiki100_8088_t::device_rom_region() const
=======
const tiny_rom_entry *tiki100_8088_device::device_rom_region() const
>>>>>>> upstream/master
{
	return ROM_NAME( tiki100_8088 );
}


<<<<<<< HEAD
static ADDRESS_MAP_START( i8088_mem, AS_PROGRAM, 8, tiki100_8088_t )
	AM_RANGE(0x00000, 0xbffff) AM_RAM
	AM_RANGE(0xc0000, 0xcffff) AM_DEVREADWRITE(":" TIKI100_BUS_TAG, tiki100_bus_t, exin_mrq_r, exin_mrq_w)
=======
static ADDRESS_MAP_START( i8088_mem, AS_PROGRAM, 8, tiki100_8088_device )
	AM_RANGE(0x00000, 0xbffff) AM_RAM
	AM_RANGE(0xc0000, 0xcffff) AM_DEVREADWRITE(":" TIKI100_BUS_TAG, tiki100_bus_device, exin_mrq_r, exin_mrq_w)
>>>>>>> upstream/master
	AM_RANGE(0xff000, 0xfffff) AM_ROM AM_REGION(I8088_TAG, 0)
ADDRESS_MAP_END


<<<<<<< HEAD
static ADDRESS_MAP_START( i8088_io, AS_IO, 8, tiki100_8088_t )
=======
static ADDRESS_MAP_START( i8088_io, AS_IO, 8, tiki100_8088_device )
>>>>>>> upstream/master
	AM_RANGE(0x7f, 0x7f) AM_READWRITE(read, write)
ADDRESS_MAP_END


//-------------------------------------------------
<<<<<<< HEAD
//  MACHINE_CONFIG_FRAGMENT( tiki100_8088 )
//-------------------------------------------------

static MACHINE_CONFIG_FRAGMENT( tiki100_8088 )
=======
//  MACHINE_CONFIG_START( tiki100_8088 )
//-------------------------------------------------

MACHINE_CONFIG_MEMBER( tiki100_8088_device::device_add_mconfig )
>>>>>>> upstream/master
	MCFG_CPU_ADD(I8088_TAG, I8088, 6000000)
	MCFG_CPU_PROGRAM_MAP(i8088_mem)
	MCFG_CPU_IO_MAP(i8088_io)
MACHINE_CONFIG_END


<<<<<<< HEAD
//-------------------------------------------------
//  machine_config_additions - device-specific
//  machine configurations
//-------------------------------------------------

machine_config_constructor tiki100_8088_t::device_mconfig_additions() const
{
	return MACHINE_CONFIG_NAME( tiki100_8088 );
}


=======
>>>>>>> upstream/master

//**************************************************************************
//  LIVE DEVICE
//**************************************************************************

//-------------------------------------------------
<<<<<<< HEAD
//  tiki100_8088_t - constructor
//-------------------------------------------------

tiki100_8088_t::tiki100_8088_t(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock) :
	device_t(mconfig, TIKI100_8088, "TIKI-100 8/16", tag, owner, clock, "tiki100_8088", __FILE__),
=======
//  tiki100_8088_device - constructor
//-------------------------------------------------

tiki100_8088_device::tiki100_8088_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock) :
	device_t(mconfig, TIKI100_8088, tag, owner, clock),
>>>>>>> upstream/master
	device_tiki100bus_card_interface(mconfig, *this),
	m_maincpu(*this, I8088_TAG),
	m_data(0)
{
}


//-------------------------------------------------
//  device_start - device-specific startup
//-------------------------------------------------

<<<<<<< HEAD
void tiki100_8088_t::device_start()
=======
void tiki100_8088_device::device_start()
>>>>>>> upstream/master
{
}


//-------------------------------------------------
//  device_reset - device-specific reset
//-------------------------------------------------

<<<<<<< HEAD
void tiki100_8088_t::device_reset()
=======
void tiki100_8088_device::device_reset()
>>>>>>> upstream/master
{
	m_maincpu->reset();

	m_data = 0;
}


//-------------------------------------------------
//  tiki100bus_iorq_r - I/O read
//-------------------------------------------------

<<<<<<< HEAD
UINT8 tiki100_8088_t::iorq_r(address_space &space, offs_t offset, UINT8 data)
=======
uint8_t tiki100_8088_device::iorq_r(address_space &space, offs_t offset, uint8_t data)
>>>>>>> upstream/master
{
	if ((offset & 0xff) == 0x7f)
	{
		data = m_data;
	}

	return data;
}


//-------------------------------------------------
//  tiki100bus_iorq_w - I/O write
//-------------------------------------------------

<<<<<<< HEAD
void tiki100_8088_t::iorq_w(address_space &space, offs_t offset, UINT8 data)
=======
void tiki100_8088_device::iorq_w(address_space &space, offs_t offset, uint8_t data)
>>>>>>> upstream/master
{
	if ((offset & 0xff) == 0x7f)
	{
		m_data = data & 0x0f;

		if (BIT(data, 5))
		{
			device_reset();
		}
	}
}


//-------------------------------------------------
//  read -
//-------------------------------------------------

<<<<<<< HEAD
READ8_MEMBER( tiki100_8088_t::read )
=======
READ8_MEMBER( tiki100_8088_device::read )
>>>>>>> upstream/master
{
	return m_busak << 4 | m_data;
}


//-------------------------------------------------
//  write -
//-------------------------------------------------

<<<<<<< HEAD
WRITE8_MEMBER( tiki100_8088_t::write )
=======
WRITE8_MEMBER( tiki100_8088_device::write )
>>>>>>> upstream/master
{
	m_data = data & 0x0f;

	m_bus->busrq_w(BIT(data, 4));
}
