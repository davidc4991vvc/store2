// license:GPL-2.0+
// copyright-holders:Dirk Best
/***************************************************************************

    EACA Colour Genie Expansion Slot

    50-pin slot

***************************************************************************/

<<<<<<< HEAD
=======
#include "emu.h"
>>>>>>> upstream/master
#include "expansion.h"


//**************************************************************************
//  DEVICE DEFINITIONS
//**************************************************************************

<<<<<<< HEAD
const device_type EXPANSION_SLOT = &device_creator<expansion_slot_device>;
=======
DEFINE_DEVICE_TYPE(CG_EXP_SLOT, cg_exp_slot_device, "cg_exp_slot", "Colour Genie Expansion Slot")
>>>>>>> upstream/master


//**************************************************************************
//  SLOT DEVICE
//**************************************************************************

//-------------------------------------------------
<<<<<<< HEAD
//  expansion_slot_device - constructor
//-------------------------------------------------

expansion_slot_device::expansion_slot_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock) :
	device_t(mconfig, EXPANSION_SLOT, "Expansion Slot", tag, owner, clock, "expansion_slot", __FILE__),
	device_slot_interface(mconfig, *this),
	m_program(NULL),
	m_io(NULL),
	m_cart(NULL),
=======
//  cg_exp - constructor
//-------------------------------------------------

cg_exp_slot_device::cg_exp_slot_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock) :
	device_t(mconfig, CG_EXP_SLOT, tag, owner, clock),
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
//  expansion_slot_device - destructor
//-------------------------------------------------

expansion_slot_device::~expansion_slot_device()
=======
//  cg_exp_slot_device - destructor
//-------------------------------------------------

cg_exp_slot_device::~cg_exp_slot_device()
>>>>>>> upstream/master
{
}

//-------------------------------------------------
//  device_start - device-specific startup
//-------------------------------------------------

<<<<<<< HEAD
void expansion_slot_device::device_start()
=======
void cg_exp_slot_device::device_start()
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
void expansion_slot_device::device_reset()
=======
void cg_exp_slot_device::device_reset()
>>>>>>> upstream/master
{
}

//-------------------------------------------------
//  set_program_space - set address space we are attached to
//-------------------------------------------------

<<<<<<< HEAD
void expansion_slot_device::set_program_space(address_space *program)
=======
void cg_exp_slot_device::set_program_space(address_space *program)
>>>>>>> upstream/master
{
	m_program = program;
}

//-------------------------------------------------
//  set_io_space - set address space we are attached to
//-------------------------------------------------

<<<<<<< HEAD
void expansion_slot_device::set_io_space(address_space *io)
=======
void cg_exp_slot_device::set_io_space(address_space *io)
>>>>>>> upstream/master
{
	m_io = io;
}


//**************************************************************************
//  CARTRIDGE INTERFACE
//**************************************************************************

//-------------------------------------------------
<<<<<<< HEAD
//  device_expansion_interface - constructor
//-------------------------------------------------

device_expansion_interface::device_expansion_interface(const machine_config &mconfig, device_t &device) :
	device_slot_card_interface(mconfig, device)
{
	m_slot = dynamic_cast<expansion_slot_device *>(device.owner());
}

//-------------------------------------------------
//  ~device_expansion_interface - destructor
//-------------------------------------------------

device_expansion_interface::~device_expansion_interface()
=======
//  device_cg_exp_interface - constructor
//-------------------------------------------------

device_cg_exp_interface::device_cg_exp_interface(const machine_config &mconfig, device_t &device) :
	device_slot_card_interface(mconfig, device)
{
	m_slot = dynamic_cast<cg_exp_slot_device *>(device.owner());
}

//-------------------------------------------------
//  ~device_cg_exp_interface - destructor
//-------------------------------------------------

device_cg_exp_interface::~device_cg_exp_interface()
>>>>>>> upstream/master
{
}
