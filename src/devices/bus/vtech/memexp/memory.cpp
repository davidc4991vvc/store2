// license:GPL-2.0+
// copyright-holders:Dirk Best
/***************************************************************************

    VTech Laser/VZ Laser Memory Expansions

***************************************************************************/

<<<<<<< HEAD
=======
#include "emu.h"
>>>>>>> upstream/master
#include "memory.h"


//**************************************************************************
//  DEVICE DEFINITIONS
//**************************************************************************

<<<<<<< HEAD
const device_type LASER110_16K = &device_creator<laser110_16k_device>;
const device_type LASER210_16K = &device_creator<laser210_16k_device>;
const device_type LASER310_16K = &device_creator<laser310_16k_device>;
const device_type LASER_64K = &device_creator<laser_64k_device>;
=======
DEFINE_DEVICE_TYPE(VTECH_LASER110_16K, vtech_laser110_16k_device, "vtech_laser110_16k", "Laser 110/200/VZ-200 16k Memory")
DEFINE_DEVICE_TYPE(VTECH_LASER210_16K, vtech_laser210_16k_device, "vtech_laser210_16k", "Laser 210/VZ-200 16k Memory")
DEFINE_DEVICE_TYPE(VTECH_LASER310_16K, vtech_laser310_16k_device, "vtech_laser310_16k", "Laser 310/VZ-300 16k Memory")
DEFINE_DEVICE_TYPE(VTECH_LASER_64K,    vtech_laser_64k_device,    "vtech_laser_64k",    "Laser/VZ 64k Memory")
>>>>>>> upstream/master


//**************************************************************************
//  LASER 110 16K DEVICE
//**************************************************************************

//-------------------------------------------------
//  laser110_16k_device - constructor
//-------------------------------------------------

<<<<<<< HEAD
laser110_16k_device::laser110_16k_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock) :
	device_t(mconfig, LASER110_16K, "Laser 110/200/VZ-200 16k Memory", tag, owner, clock, "laser110_16k", __FILE__),
	device_memexp_interface(mconfig, *this)
=======
vtech_laser110_16k_device::vtech_laser110_16k_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock) :
	device_t(mconfig, VTECH_LASER110_16K, tag, owner, clock),
	device_vtech_memexp_interface(mconfig, *this)
>>>>>>> upstream/master
{
}

//-------------------------------------------------
//  device_start - device-specific startup
//-------------------------------------------------

<<<<<<< HEAD
void laser110_16k_device::device_start()
=======
void vtech_laser110_16k_device::device_start()
>>>>>>> upstream/master
{
	m_ram.resize(16 * 1024);
}

//-------------------------------------------------
//  device_reset - device-specific reset
//-------------------------------------------------

<<<<<<< HEAD
void laser110_16k_device::device_reset()
{
	m_slot->m_program->install_ram(0x8000, 0xbfff, &m_ram[0]);
=======
void vtech_laser110_16k_device::device_reset()
{
	program_space().install_ram(0x8000, 0xbfff, &m_ram[0]);
>>>>>>> upstream/master
}


//**************************************************************************
//  LASER 210 16K DEVICE
//**************************************************************************

//-------------------------------------------------
<<<<<<< HEAD
//  laser210_16k_device - constructor
//-------------------------------------------------

laser210_16k_device::laser210_16k_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock) :
	device_t(mconfig, LASER210_16K, "Laser 210/VZ-200 (DSE) 16k Memory", tag, owner, clock, "laser210_16k", __FILE__),
	device_memexp_interface(mconfig, *this)
=======
//  vtech_laser210_16k_device - constructor
//-------------------------------------------------

vtech_laser210_16k_device::vtech_laser210_16k_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock) :
	device_t(mconfig, VTECH_LASER210_16K, tag, owner, clock),
	device_vtech_memexp_interface(mconfig, *this)
>>>>>>> upstream/master
{
}

//-------------------------------------------------
//  device_start - device-specific startup
//-------------------------------------------------

<<<<<<< HEAD
void laser210_16k_device::device_start()
=======
void vtech_laser210_16k_device::device_start()
>>>>>>> upstream/master
{
	m_ram.resize(16 * 1024);
}

//-------------------------------------------------
//  device_reset - device-specific reset
//-------------------------------------------------

<<<<<<< HEAD
void laser210_16k_device::device_reset()
{
	m_slot->m_program->install_ram(0x9000, 0xcfff, &m_ram[0]);
=======
void vtech_laser210_16k_device::device_reset()
{
	program_space().install_ram(0x9000, 0xcfff, &m_ram[0]);
>>>>>>> upstream/master
}


//**************************************************************************
//  VZ300 16K DEVICE
//**************************************************************************

//-------------------------------------------------
<<<<<<< HEAD
//  laser310_16k_device - constructor
//-------------------------------------------------

laser310_16k_device::laser310_16k_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock) :
	device_t(mconfig, LASER310_16K, "Laser 310/VZ-300 16k Memory", tag, owner, clock, "laser310_16k", __FILE__),
	device_memexp_interface(mconfig, *this)
=======
//  vtech_laser310_16k_device - constructor
//-------------------------------------------------

vtech_laser310_16k_device::vtech_laser310_16k_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock) :
	device_t(mconfig, VTECH_LASER310_16K, tag, owner, clock),
	device_vtech_memexp_interface(mconfig, *this)
>>>>>>> upstream/master
{
}

//-------------------------------------------------
//  device_start - device-specific startup
//-------------------------------------------------

<<<<<<< HEAD
void laser310_16k_device::device_start()
=======
void vtech_laser310_16k_device::device_start()
>>>>>>> upstream/master
{
	m_ram.resize(16 * 1024);
}

//-------------------------------------------------
//  device_reset - device-specific reset
//-------------------------------------------------

<<<<<<< HEAD
void laser310_16k_device::device_reset()
{
	m_slot->m_program->install_ram(0xb800, 0xf7ff, &m_ram[0]);
=======
void vtech_laser310_16k_device::device_reset()
{
	program_space().install_ram(0xb800, 0xf7ff, &m_ram[0]);
>>>>>>> upstream/master
}


//**************************************************************************
//  VZ300 64K DEVICE
//**************************************************************************

//-------------------------------------------------
<<<<<<< HEAD
//  laser_64k_device - constructor
//-------------------------------------------------

laser_64k_device::laser_64k_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock) :
	device_t(mconfig, LASER_64K, "Laser/VZ 64k Memory", tag, owner, clock, "laser_64k", __FILE__),
	device_memexp_interface(mconfig, *this)
=======
//  vtech_laser_64k_device - constructor
//-------------------------------------------------

vtech_laser_64k_device::vtech_laser_64k_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock) :
	device_t(mconfig, VTECH_LASER_64K, tag, owner, clock),
	device_vtech_memexp_interface(mconfig, *this)
>>>>>>> upstream/master
{
}

//-------------------------------------------------
//  device_start - device-specific startup
//-------------------------------------------------

<<<<<<< HEAD
void laser_64k_device::device_start()
=======
void vtech_laser_64k_device::device_start()
>>>>>>> upstream/master
{
	m_ram.resize(64 * 1024);
}

//-------------------------------------------------
//  device_reset - device-specific reset
//-------------------------------------------------

<<<<<<< HEAD
void laser_64k_device::device_reset()
{
	// fixed first bank
	m_slot->m_program->install_ram(0x8000, 0xbfff, &m_ram[0]);

	// other banks
	m_slot->m_program->install_readwrite_bank(0xc000, 0xffff, tag());
=======
void vtech_laser_64k_device::device_reset()
{
	// fixed first bank
	program_space().install_ram(0x8000, 0xbfff, &m_ram[0]);

	// other banks
	program_space().install_readwrite_bank(0xc000, 0xffff, tag());
>>>>>>> upstream/master

	membank(tag())->configure_entries(0, 4, &m_ram[0], 0x4000);
	membank(tag())->set_entry(1);

	// bank switch
<<<<<<< HEAD
	m_slot->m_io->install_write_handler(0x70, 0x7f, write8_delegate(FUNC(laser_64k_device::bankswitch_w), this));
}

WRITE8_MEMBER( laser_64k_device::bankswitch_w )
=======
	io_space().install_write_handler(0x70, 0x7f, write8_delegate(FUNC(vtech_laser_64k_device::bankswitch_w), this));
}

WRITE8_MEMBER( vtech_laser_64k_device::bankswitch_w )
>>>>>>> upstream/master
{
	membank(tag())->set_entry(data & 0x03);
}
