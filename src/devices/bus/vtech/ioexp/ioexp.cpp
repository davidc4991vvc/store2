// license:GPL-2.0+
// copyright-holders:Dirk Best
/***************************************************************************

    VTech Laser/VZ I/O Expansion Slot

    30-pin slot

***************************************************************************/

<<<<<<< HEAD
=======
#include "emu.h"
>>>>>>> upstream/master
#include "ioexp.h"


//**************************************************************************
//  DEVICE DEFINITIONS
//**************************************************************************

<<<<<<< HEAD
const device_type IOEXP_SLOT = &device_creator<ioexp_slot_device>;
=======
DEFINE_DEVICE_TYPE(VTECH_IOEXP_SLOT, vtech_ioexp_slot_device, "vtech_ioexp_slot", "Laser/VZ I/O Expansion Slot")
>>>>>>> upstream/master


//**************************************************************************
//  SLOT DEVICE
//**************************************************************************

//-------------------------------------------------
<<<<<<< HEAD
//  ioexp_slot_device - constructor
//-------------------------------------------------

ioexp_slot_device::ioexp_slot_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock) :
	device_t(mconfig, IOEXP_SLOT, "Peripheral Expansion Slot", tag, owner, clock, "ioexp_slot", __FILE__),
	device_slot_interface(mconfig, *this),
	m_io(NULL),
	m_cart(NULL)
=======
//  vtech_ioexp_slot_device - constructor
//-------------------------------------------------

vtech_ioexp_slot_device::vtech_ioexp_slot_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock) :
	device_t(mconfig, VTECH_IOEXP_SLOT, tag, owner, clock),
	device_slot_interface(mconfig, *this),
	m_io(nullptr),
	m_cart(nullptr)
>>>>>>> upstream/master
{
}

//-------------------------------------------------
<<<<<<< HEAD
//  ioexp_slot_device - destructor
//-------------------------------------------------

ioexp_slot_device::~ioexp_slot_device()
=======
//  vtech_ioexp_slot_device - destructor
//-------------------------------------------------

vtech_ioexp_slot_device::~vtech_ioexp_slot_device()
>>>>>>> upstream/master
{
}

//-------------------------------------------------
//  device_start - device-specific startup
//-------------------------------------------------

<<<<<<< HEAD
void ioexp_slot_device::device_start()
=======
void vtech_ioexp_slot_device::device_start()
>>>>>>> upstream/master
{
}

//-------------------------------------------------
//  device_reset - device-specific reset
//-------------------------------------------------

<<<<<<< HEAD
void ioexp_slot_device::device_reset()
=======
void vtech_ioexp_slot_device::device_reset()
>>>>>>> upstream/master
{
}

//-------------------------------------------------
//  set_io_space - set address space we are attached to
//-------------------------------------------------

<<<<<<< HEAD
void ioexp_slot_device::set_io_space(address_space *io)
=======
void vtech_ioexp_slot_device::set_io_space(address_space *io)
>>>>>>> upstream/master
{
	m_io = io;
}


//**************************************************************************
//  CARTRIDGE INTERFACE
//**************************************************************************

//-------------------------------------------------
<<<<<<< HEAD
//  device_ioexp_interface - constructor
//-------------------------------------------------

device_ioexp_interface::device_ioexp_interface(const machine_config &mconfig, device_t &device) :
	device_slot_card_interface(mconfig, device)
{
	m_slot = dynamic_cast<ioexp_slot_device *>(device.owner());
}

//-------------------------------------------------
//  ~device_ioexp_interface - destructor
//-------------------------------------------------

device_ioexp_interface::~device_ioexp_interface()
=======
//  device_vtech_ioexp_interface - constructor
//-------------------------------------------------

device_vtech_ioexp_interface::device_vtech_ioexp_interface(const machine_config &mconfig, device_t &device) :
	device_slot_card_interface(mconfig, device)
{
	m_slot = dynamic_cast<vtech_ioexp_slot_device *>(device.owner());
}

//-------------------------------------------------
//  ~device_vtech_ioexp_interface - destructor
//-------------------------------------------------

device_vtech_ioexp_interface::~device_vtech_ioexp_interface()
>>>>>>> upstream/master
{
}
