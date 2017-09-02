// license:GPL-2.0+
// copyright-holders:Dirk Best
/***************************************************************************

    VTech Laser/VZ Memory Expansion Slot

    44-pin slot

***************************************************************************/

<<<<<<< HEAD
=======
#include "emu.h"
>>>>>>> upstream/master
#include "memexp.h"


//**************************************************************************
//  DEVICE DEFINITIONS
//**************************************************************************

<<<<<<< HEAD
const device_type MEMEXP_SLOT = &device_creator<memexp_slot_device>;
=======
DEFINE_DEVICE_TYPE(VTECH_MEMEXP_SLOT, vtech_memexp_slot_device, "vtech_memexp_slot", "Laser/VZ Memory Expansion Slot")
>>>>>>> upstream/master


//**************************************************************************
//  SLOT DEVICE
//**************************************************************************

//-------------------------------------------------
<<<<<<< HEAD
//  memexp_slot_device - constructor
//-------------------------------------------------

memexp_slot_device::memexp_slot_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock) :
	device_t(mconfig, MEMEXP_SLOT, "Memory Expansion Slot", tag, owner, clock, "memexp_slot", __FILE__),
	device_slot_interface(mconfig, *this),
	m_program(NULL),
	m_io(NULL),
	m_cart(NULL),
=======
//  vtech_memexp_slot_device - constructor
//-------------------------------------------------

vtech_memexp_slot_device::vtech_memexp_slot_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock) :
	device_t(mconfig, VTECH_MEMEXP_SLOT, tag, owner, clock),
	device_slot_interface(mconfig, *this),
	m_program(nullptr),
	m_io(nullptr),
	m_cart(nullptr),
>>>>>>> upstream/master
	m_int_handler(*this),
	m_nmi_handler(*this),
	m_reset_handler(*this)
{
}

//-------------------------------------------------
<<<<<<< HEAD
//  memexp_slot_device - destructor
//-------------------------------------------------

memexp_slot_device::~memexp_slot_device()
=======
//  vtech_memexp_slot_device - destructor
//-------------------------------------------------

vtech_memexp_slot_device::~vtech_memexp_slot_device()
>>>>>>> upstream/master
{
}

//-------------------------------------------------
//  device_start - device-specific startup
//-------------------------------------------------

<<<<<<< HEAD
void memexp_slot_device::device_start()
=======
void vtech_memexp_slot_device::device_start()
>>>>>>> upstream/master
{
	// resolve callbacks
	m_int_handler.resolve_safe();
	m_nmi_handler.resolve_safe();
	m_reset_handler.resolve_safe();
}

//-------------------------------------------------
//  device_reset - device-specific reset
//-------------------------------------------------

<<<<<<< HEAD
void memexp_slot_device::device_reset()
=======
void vtech_memexp_slot_device::device_reset()
>>>>>>> upstream/master
{
}

//-------------------------------------------------
//  set_program_space - set address space we are attached to
//-------------------------------------------------

<<<<<<< HEAD
void memexp_slot_device::set_program_space(address_space *program)
=======
void vtech_memexp_slot_device::set_program_space(address_space *program)
>>>>>>> upstream/master
{
	m_program = program;
}

//-------------------------------------------------
//  set_io_space - set address space we are attached to
//-------------------------------------------------

<<<<<<< HEAD
void memexp_slot_device::set_io_space(address_space *io)
=======
void vtech_memexp_slot_device::set_io_space(address_space *io)
>>>>>>> upstream/master
{
	m_io = io;
}


//**************************************************************************
//  CARTRIDGE INTERFACE
//**************************************************************************

//-------------------------------------------------
<<<<<<< HEAD
//  device_memexp_interface - constructor
//-------------------------------------------------

device_memexp_interface::device_memexp_interface(const machine_config &mconfig, device_t &device) :
	device_slot_card_interface(mconfig, device)
{
	m_slot = dynamic_cast<memexp_slot_device *>(device.owner());
}

//-------------------------------------------------
//  ~device_memexp_interface - destructor
//-------------------------------------------------

device_memexp_interface::~device_memexp_interface()
=======
//  device_vtech_memexp_interface - constructor
//-------------------------------------------------

device_vtech_memexp_interface::device_vtech_memexp_interface(const machine_config &mconfig, device_t &device) :
	device_slot_card_interface(mconfig, device)
{
	m_slot = dynamic_cast<vtech_memexp_slot_device *>(device.owner());
}

//-------------------------------------------------
//  ~device_vtech_memexp_interface - destructor
//-------------------------------------------------

device_vtech_memexp_interface::~device_vtech_memexp_interface()
>>>>>>> upstream/master
{
}
