// license:BSD-3-Clause
// copyright-holders:smf
<<<<<<< HEAD
#include "linflash.h"

linear_flash_pccard_device::linear_flash_pccard_device(const machine_config &mconfig, device_type type, const char *name, const char *tag, device_t *owner, UINT32 clock,const char *shortname, const char *source) :
	device_t(mconfig, type, name, tag, owner, clock, shortname, source),
	device_memory_interface(mconfig, *this),
	device_slot_card_interface(mconfig, *this), m_space(nullptr)
=======
#include "emu.h"
#include "linflash.h"

DEFINE_DEVICE_TYPE(LINEAR_FLASH_PCCARD_16MB, linear_flash_pccard_16mb_device, "linearflash16mb", "Linear Flash PC Card (16MB)")
DEFINE_DEVICE_TYPE(LINEAR_FLASH_PCCARD_32MB, linear_flash_pccard_32mb_device, "linearflash32mb", "Linear Flash PC Card (32MB)")
DEFINE_DEVICE_TYPE(LINEAR_FLASH_PCCARD_64MB, linear_flash_pccard_64mb_device, "linearflash64mb", "Linear Flash PC Card (64MB)")


linear_flash_pccard_device::linear_flash_pccard_device(const machine_config &mconfig, device_type type, const char *tag, device_t *owner, uint32_t clock) :
	device_t(mconfig, type, tag, owner, clock),
	device_memory_interface(mconfig, *this),
	device_slot_card_interface(mconfig, *this),
	m_space(nullptr)
>>>>>>> upstream/master
{
}

void linear_flash_pccard_device::device_start()
{
<<<<<<< HEAD
	m_space = &space(AS_0);
}

const address_space_config *linear_flash_pccard_device::memory_space_config( address_spacenum spacenum ) const
{
	return ( spacenum == AS_0 ) ? &m_space_config : NULL;
=======
	m_space = &space(0);
}

device_memory_interface::space_config_vector linear_flash_pccard_device::memory_space_config() const
{
	return space_config_vector {
		std::make_pair(0, &m_space_config)
	};
>>>>>>> upstream/master
}

READ16_MEMBER( linear_flash_pccard_device::read_memory )
{
<<<<<<< HEAD
	UINT16 data = m_space->read_word(offset * 2, mem_mask);
=======
	uint16_t data = m_space->read_word(offset * 2, mem_mask);
>>>>>>> upstream/master
	//printf( "<%08x %04x %04x\n", offset, data, mem_mask );
	return data;
}

WRITE16_MEMBER( linear_flash_pccard_device::write_memory )
{
	//printf( ">%08x %04x %04x\n", offset, data, mem_mask );
	m_space->write_word(offset * 2, data, mem_mask);
}


<<<<<<< HEAD
const device_type LINEAR_FLASH_PCCARD_16MB = &device_creator<linear_flash_pccard_16mb_device>;

static ADDRESS_MAP_START(linear_flash_pccard_16mb, AS_0, 16, linear_flash_pccard_16mb_device)
=======
static ADDRESS_MAP_START(linear_flash_pccard_16mb, 0, 16, linear_flash_pccard_16mb_device)
>>>>>>> upstream/master
	ADDRESS_MAP_UNMAP_HIGH
	AM_RANGE(0x00000000, 0x003fffff) AM_DEVREADWRITE8("1l", intelfsh8_device, read, write, 0x00ff)
	AM_RANGE(0x00000000, 0x003fffff) AM_DEVREADWRITE8("1u", intelfsh8_device, read, write, 0xff00)
	AM_RANGE(0x00400000, 0x007fffff) AM_DEVREADWRITE8("2l", intelfsh8_device, read, write, 0x00ff)
	AM_RANGE(0x00400000, 0x007fffff) AM_DEVREADWRITE8("2u", intelfsh8_device, read, write, 0xff00)
	AM_RANGE(0x00800000, 0x00bfffff) AM_DEVREADWRITE8("3l", intelfsh8_device, read, write, 0x00ff)
	AM_RANGE(0x00800000, 0x00bfffff) AM_DEVREADWRITE8("3u", intelfsh8_device, read, write, 0xff00)
	AM_RANGE(0x00c00000, 0x00ffffff) AM_DEVREADWRITE8("4l", intelfsh8_device, read, write, 0x00ff)
	AM_RANGE(0x00c00000, 0x00ffffff) AM_DEVREADWRITE8("4u", intelfsh8_device, read, write, 0xff00)
ADDRESS_MAP_END

<<<<<<< HEAD
linear_flash_pccard_16mb_device::linear_flash_pccard_16mb_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock) :
	linear_flash_pccard_device(mconfig, LINEAR_FLASH_PCCARD_16MB, "Linear Flash PCCARD (16MB)", tag, owner, clock, "linearflash16mb", __FILE__)
=======
linear_flash_pccard_16mb_device::linear_flash_pccard_16mb_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock) :
	linear_flash_pccard_device(mconfig, LINEAR_FLASH_PCCARD_16MB, tag, owner, clock)
>>>>>>> upstream/master
{
	m_space_config = address_space_config("memory", ENDIANNESS_LITTLE, 16,  26, 0, *ADDRESS_MAP_NAME( linear_flash_pccard_16mb ) );
}

<<<<<<< HEAD
static MACHINE_CONFIG_FRAGMENT( linear_flash_pccard_16mb )
=======
MACHINE_CONFIG_MEMBER( linear_flash_pccard_16mb_device::device_add_mconfig )
>>>>>>> upstream/master
	MCFG_FUJITSU_29F016A_ADD("1l")
	MCFG_FUJITSU_29F016A_ADD("1u")
	MCFG_FUJITSU_29F016A_ADD("2l")
	MCFG_FUJITSU_29F016A_ADD("2u")
	MCFG_FUJITSU_29F016A_ADD("3l")
	MCFG_FUJITSU_29F016A_ADD("3u")
	MCFG_FUJITSU_29F016A_ADD("4l")
	MCFG_FUJITSU_29F016A_ADD("4u")
MACHINE_CONFIG_END

<<<<<<< HEAD
machine_config_constructor linear_flash_pccard_16mb_device::device_mconfig_additions() const
{
	return MACHINE_CONFIG_NAME( linear_flash_pccard_16mb );
}


const device_type LINEAR_FLASH_PCCARD_32MB = &device_creator<linear_flash_pccard_32mb_device>;

static ADDRESS_MAP_START(linear_flash_pccard_32mb, AS_0, 16, linear_flash_pccard_32mb_device)
=======

static ADDRESS_MAP_START(linear_flash_pccard_32mb, 0, 16, linear_flash_pccard_32mb_device)
>>>>>>> upstream/master
	ADDRESS_MAP_UNMAP_HIGH
	AM_RANGE(0x00000000, 0x003fffff) AM_DEVREADWRITE8("1l", intelfsh8_device, read, write, 0x00ff)
	AM_RANGE(0x00000000, 0x003fffff) AM_DEVREADWRITE8("1u", intelfsh8_device, read, write, 0xff00)
	AM_RANGE(0x00400000, 0x007fffff) AM_DEVREADWRITE8("2l", intelfsh8_device, read, write, 0x00ff)
	AM_RANGE(0x00400000, 0x007fffff) AM_DEVREADWRITE8("2u", intelfsh8_device, read, write, 0xff00)
	AM_RANGE(0x00800000, 0x00bfffff) AM_DEVREADWRITE8("3l", intelfsh8_device, read, write, 0x00ff)
	AM_RANGE(0x00800000, 0x00bfffff) AM_DEVREADWRITE8("3u", intelfsh8_device, read, write, 0xff00)
	AM_RANGE(0x00c00000, 0x00ffffff) AM_DEVREADWRITE8("4l", intelfsh8_device, read, write, 0x00ff)
	AM_RANGE(0x00c00000, 0x00ffffff) AM_DEVREADWRITE8("4u", intelfsh8_device, read, write, 0xff00)
	AM_RANGE(0x01000000, 0x013fffff) AM_DEVREADWRITE8("5l", intelfsh8_device, read, write, 0x00ff)
	AM_RANGE(0x01000000, 0x013fffff) AM_DEVREADWRITE8("5u", intelfsh8_device, read, write, 0xff00)
	AM_RANGE(0x01400000, 0x017fffff) AM_DEVREADWRITE8("6l", intelfsh8_device, read, write, 0x00ff)
	AM_RANGE(0x01400000, 0x017fffff) AM_DEVREADWRITE8("6u", intelfsh8_device, read, write, 0xff00)
	AM_RANGE(0x01800000, 0x01bfffff) AM_DEVREADWRITE8("7l", intelfsh8_device, read, write, 0x00ff)
	AM_RANGE(0x01800000, 0x01bfffff) AM_DEVREADWRITE8("7u", intelfsh8_device, read, write, 0xff00)
	AM_RANGE(0x01c00000, 0x01ffffff) AM_DEVREADWRITE8("8l", intelfsh8_device, read, write, 0x00ff)
	AM_RANGE(0x01c00000, 0x01ffffff) AM_DEVREADWRITE8("8u", intelfsh8_device, read, write, 0xff00)
ADDRESS_MAP_END

<<<<<<< HEAD
linear_flash_pccard_32mb_device::linear_flash_pccard_32mb_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock) :
	linear_flash_pccard_device(mconfig, LINEAR_FLASH_PCCARD_32MB, "Linear Flash PCCARD (32MB)", tag, owner, clock, "linearflash32mb", __FILE__)
=======
linear_flash_pccard_32mb_device::linear_flash_pccard_32mb_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock) :
	linear_flash_pccard_device(mconfig, LINEAR_FLASH_PCCARD_32MB, tag, owner, clock)
>>>>>>> upstream/master
{
	m_space_config = address_space_config("memory", ENDIANNESS_LITTLE, 16,  26, 0, *ADDRESS_MAP_NAME( linear_flash_pccard_32mb ) );
}

<<<<<<< HEAD
static MACHINE_CONFIG_FRAGMENT( linear_flash_pccard_32mb )
=======
MACHINE_CONFIG_MEMBER( linear_flash_pccard_32mb_device::device_add_mconfig )
>>>>>>> upstream/master
	MCFG_FUJITSU_29F016A_ADD("1l")
	MCFG_FUJITSU_29F016A_ADD("1u")
	MCFG_FUJITSU_29F016A_ADD("2l")
	MCFG_FUJITSU_29F016A_ADD("2u")
	MCFG_FUJITSU_29F016A_ADD("3l")
	MCFG_FUJITSU_29F016A_ADD("3u")
	MCFG_FUJITSU_29F016A_ADD("4l")
	MCFG_FUJITSU_29F016A_ADD("4u")
	MCFG_FUJITSU_29F016A_ADD("5l")
	MCFG_FUJITSU_29F016A_ADD("5u")
	MCFG_FUJITSU_29F016A_ADD("6l")
	MCFG_FUJITSU_29F016A_ADD("6u")
	MCFG_FUJITSU_29F016A_ADD("7l")
	MCFG_FUJITSU_29F016A_ADD("7u")
	MCFG_FUJITSU_29F016A_ADD("8l")
	MCFG_FUJITSU_29F016A_ADD("8u")
MACHINE_CONFIG_END

<<<<<<< HEAD
machine_config_constructor linear_flash_pccard_32mb_device::device_mconfig_additions() const
{
	return MACHINE_CONFIG_NAME( linear_flash_pccard_32mb );
}


const device_type LINEAR_FLASH_PCCARD_64MB = &device_creator<linear_flash_pccard_64mb_device>;

static ADDRESS_MAP_START(linear_flash_pccard_64mb, AS_0, 16, linear_flash_pccard_64mb_device)
=======

static ADDRESS_MAP_START(linear_flash_pccard_64mb, 0, 16, linear_flash_pccard_64mb_device)
>>>>>>> upstream/master
	ADDRESS_MAP_UNMAP_HIGH
	AM_RANGE(0x00000000, 0x003fffff) AM_DEVREADWRITE8("1l", intelfsh8_device, read, write, 0x00ff)
	AM_RANGE(0x00000000, 0x003fffff) AM_DEVREADWRITE8("1u", intelfsh8_device, read, write, 0xff00)
	AM_RANGE(0x00400000, 0x007fffff) AM_DEVREADWRITE8("2l", intelfsh8_device, read, write, 0x00ff)
	AM_RANGE(0x00400000, 0x007fffff) AM_DEVREADWRITE8("2u", intelfsh8_device, read, write, 0xff00)
	AM_RANGE(0x00800000, 0x00bfffff) AM_DEVREADWRITE8("3l", intelfsh8_device, read, write, 0x00ff)
	AM_RANGE(0x00800000, 0x00bfffff) AM_DEVREADWRITE8("3u", intelfsh8_device, read, write, 0xff00)
	AM_RANGE(0x00c00000, 0x00ffffff) AM_DEVREADWRITE8("4l", intelfsh8_device, read, write, 0x00ff)
	AM_RANGE(0x00c00000, 0x00ffffff) AM_DEVREADWRITE8("4u", intelfsh8_device, read, write, 0xff00)
	AM_RANGE(0x01000000, 0x013fffff) AM_DEVREADWRITE8("5l", intelfsh8_device, read, write, 0x00ff)
	AM_RANGE(0x01000000, 0x013fffff) AM_DEVREADWRITE8("5u", intelfsh8_device, read, write, 0xff00)
	AM_RANGE(0x01400000, 0x017fffff) AM_DEVREADWRITE8("6l", intelfsh8_device, read, write, 0x00ff)
	AM_RANGE(0x01400000, 0x017fffff) AM_DEVREADWRITE8("6u", intelfsh8_device, read, write, 0xff00)
	AM_RANGE(0x01800000, 0x01bfffff) AM_DEVREADWRITE8("7l", intelfsh8_device, read, write, 0x00ff)
	AM_RANGE(0x01800000, 0x01bfffff) AM_DEVREADWRITE8("7u", intelfsh8_device, read, write, 0xff00)
	AM_RANGE(0x01c00000, 0x01ffffff) AM_DEVREADWRITE8("8l", intelfsh8_device, read, write, 0x00ff)
	AM_RANGE(0x01c00000, 0x01ffffff) AM_DEVREADWRITE8("8u", intelfsh8_device, read, write, 0xff00)
	AM_RANGE(0x02000000, 0x023fffff) AM_DEVREADWRITE8("9l", intelfsh8_device, read, write, 0x00ff)
	AM_RANGE(0x02000000, 0x023fffff) AM_DEVREADWRITE8("9u", intelfsh8_device, read, write, 0xff00)
	AM_RANGE(0x02400000, 0x027fffff) AM_DEVREADWRITE8("10l", intelfsh8_device, read, write, 0x00ff)
	AM_RANGE(0x02400000, 0x027fffff) AM_DEVREADWRITE8("10u", intelfsh8_device, read, write, 0xff00)
	AM_RANGE(0x02800000, 0x02bfffff) AM_DEVREADWRITE8("11l", intelfsh8_device, read, write, 0x00ff)
	AM_RANGE(0x02800000, 0x02bfffff) AM_DEVREADWRITE8("11u", intelfsh8_device, read, write, 0xff00)
	AM_RANGE(0x02c00000, 0x02ffffff) AM_DEVREADWRITE8("12l", intelfsh8_device, read, write, 0x00ff)
	AM_RANGE(0x02c00000, 0x02ffffff) AM_DEVREADWRITE8("12u", intelfsh8_device, read, write, 0xff00)
	AM_RANGE(0x03000000, 0x033fffff) AM_DEVREADWRITE8("13l", intelfsh8_device, read, write, 0x00ff)
	AM_RANGE(0x03000000, 0x033fffff) AM_DEVREADWRITE8("13u", intelfsh8_device, read, write, 0xff00)
	AM_RANGE(0x03400000, 0x037fffff) AM_DEVREADWRITE8("14l", intelfsh8_device, read, write, 0x00ff)
	AM_RANGE(0x03400000, 0x037fffff) AM_DEVREADWRITE8("14u", intelfsh8_device, read, write, 0xff00)
	AM_RANGE(0x03800000, 0x03bfffff) AM_DEVREADWRITE8("15l", intelfsh8_device, read, write, 0x00ff)
	AM_RANGE(0x03800000, 0x03bfffff) AM_DEVREADWRITE8("15u", intelfsh8_device, read, write, 0xff00)
	AM_RANGE(0x03c00000, 0x03ffffff) AM_DEVREADWRITE8("16l", intelfsh8_device, read, write, 0x00ff)
	AM_RANGE(0x03c00000, 0x03ffffff) AM_DEVREADWRITE8("16u", intelfsh8_device, read, write, 0xff00)
ADDRESS_MAP_END

<<<<<<< HEAD
linear_flash_pccard_64mb_device::linear_flash_pccard_64mb_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock) :
	linear_flash_pccard_device(mconfig, LINEAR_FLASH_PCCARD_64MB, "Linear Flash PCCARD (64MB)", tag, owner, clock, "linearflash64mb", __FILE__)
=======
linear_flash_pccard_64mb_device::linear_flash_pccard_64mb_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock) :
	linear_flash_pccard_device(mconfig, LINEAR_FLASH_PCCARD_64MB, tag, owner, clock)
>>>>>>> upstream/master
{
	m_space_config = address_space_config("memory", ENDIANNESS_LITTLE, 16,  26, 0, *ADDRESS_MAP_NAME( linear_flash_pccard_64mb ) );
}

<<<<<<< HEAD
static MACHINE_CONFIG_FRAGMENT( linear_flash_pccard_64mb )
=======
MACHINE_CONFIG_MEMBER( linear_flash_pccard_64mb_device::device_add_mconfig )
>>>>>>> upstream/master
	MCFG_FUJITSU_29F016A_ADD("1l")
	MCFG_FUJITSU_29F016A_ADD("1u")
	MCFG_FUJITSU_29F016A_ADD("2l")
	MCFG_FUJITSU_29F016A_ADD("2u")
	MCFG_FUJITSU_29F016A_ADD("3l")
	MCFG_FUJITSU_29F016A_ADD("3u")
	MCFG_FUJITSU_29F016A_ADD("4l")
	MCFG_FUJITSU_29F016A_ADD("4u")
	MCFG_FUJITSU_29F016A_ADD("5l")
	MCFG_FUJITSU_29F016A_ADD("5u")
	MCFG_FUJITSU_29F016A_ADD("6l")
	MCFG_FUJITSU_29F016A_ADD("6u")
	MCFG_FUJITSU_29F016A_ADD("7l")
	MCFG_FUJITSU_29F016A_ADD("7u")
	MCFG_FUJITSU_29F016A_ADD("8l")
	MCFG_FUJITSU_29F016A_ADD("8u")
	MCFG_FUJITSU_29F016A_ADD("9l")
	MCFG_FUJITSU_29F016A_ADD("9u")
	MCFG_FUJITSU_29F016A_ADD("10l")
	MCFG_FUJITSU_29F016A_ADD("10u")
	MCFG_FUJITSU_29F016A_ADD("11l")
	MCFG_FUJITSU_29F016A_ADD("11u")
	MCFG_FUJITSU_29F016A_ADD("12l")
	MCFG_FUJITSU_29F016A_ADD("12u")
	MCFG_FUJITSU_29F016A_ADD("13l")
	MCFG_FUJITSU_29F016A_ADD("13u")
	MCFG_FUJITSU_29F016A_ADD("14l")
	MCFG_FUJITSU_29F016A_ADD("14u")
	MCFG_FUJITSU_29F016A_ADD("15l")
	MCFG_FUJITSU_29F016A_ADD("15u")
	MCFG_FUJITSU_29F016A_ADD("16l")
	MCFG_FUJITSU_29F016A_ADD("16u")
MACHINE_CONFIG_END
<<<<<<< HEAD

machine_config_constructor linear_flash_pccard_64mb_device::device_mconfig_additions() const
{
	return MACHINE_CONFIG_NAME( linear_flash_pccard_64mb );
}
=======
>>>>>>> upstream/master
