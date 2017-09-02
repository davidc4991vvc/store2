// license:GPL-2.0+
// copyright-holders:Dirk Best
/***************************************************************************

    EACA Colour Genie Parallel Slot

    20-pin slot

***************************************************************************/

<<<<<<< HEAD
=======
#include "emu.h"
>>>>>>> upstream/master
#include "parallel.h"


//**************************************************************************
//  DEVICE DEFINITIONS
//**************************************************************************

<<<<<<< HEAD
const device_type PARALLEL_SLOT = &device_creator<parallel_slot_device>;
=======
DEFINE_DEVICE_TYPE(CG_PARALLEL_SLOT, cg_parallel_slot_device, "cg_parallel_slot", "Colour Genie Parallel Slot")
>>>>>>> upstream/master


//**************************************************************************
//  SLOT DEVICE
//**************************************************************************

//-------------------------------------------------
<<<<<<< HEAD
//  parallel_slot_device - constructor
//-------------------------------------------------

parallel_slot_device::parallel_slot_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock) :
	device_t(mconfig, PARALLEL_SLOT, "Parallel Slot", tag, owner, clock, "parallel_slot", __FILE__),
	device_slot_interface(mconfig, *this),
	m_cart(NULL)
=======
//  cg_parallel_slot_device - constructor
//-------------------------------------------------

cg_parallel_slot_device::cg_parallel_slot_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock) :
	device_t(mconfig, CG_PARALLEL_SLOT, tag, owner, clock),
	device_slot_interface(mconfig, *this),
	m_cart(nullptr)
>>>>>>> upstream/master
{
}

//-------------------------------------------------
<<<<<<< HEAD
//  parallel_slot_device - destructor
//-------------------------------------------------

parallel_slot_device::~parallel_slot_device()
=======
//  cg_parallel_slot_device - destructor
//-------------------------------------------------

cg_parallel_slot_device::~cg_parallel_slot_device()
>>>>>>> upstream/master
{
}

//-------------------------------------------------
//  device_start - device-specific startup
//-------------------------------------------------

<<<<<<< HEAD
void parallel_slot_device::device_start()
{
	m_cart = dynamic_cast<device_parallel_interface *>(get_card_device());
=======
void cg_parallel_slot_device::device_start()
{
	m_cart = dynamic_cast<device_cg_parallel_interface *>(get_card_device());
>>>>>>> upstream/master
}

//-------------------------------------------------
//  device_reset - device-specific reset
//-------------------------------------------------

<<<<<<< HEAD
void parallel_slot_device::device_reset()
=======
void cg_parallel_slot_device::device_reset()
>>>>>>> upstream/master
{
}


//**************************************************************************
//  I/O PORTS
//**************************************************************************

<<<<<<< HEAD
READ8_MEMBER( parallel_slot_device::pa_r )
=======
READ8_MEMBER( cg_parallel_slot_device::pa_r )
>>>>>>> upstream/master
{
	if (m_cart)
		return m_cart->pa_r();
	else
		return 0xff;
}

<<<<<<< HEAD
WRITE8_MEMBER( parallel_slot_device::pa_w )
=======
WRITE8_MEMBER( cg_parallel_slot_device::pa_w )
>>>>>>> upstream/master
{
	if (m_cart)
		m_cart->pa_w(data);
}

<<<<<<< HEAD
READ8_MEMBER( parallel_slot_device::pb_r )
=======
READ8_MEMBER( cg_parallel_slot_device::pb_r )
>>>>>>> upstream/master
{
	if (m_cart)
		return m_cart->pb_r();
	else
		return 0xff;
}

<<<<<<< HEAD
WRITE8_MEMBER( parallel_slot_device::pb_w )
=======
WRITE8_MEMBER( cg_parallel_slot_device::pb_w )
>>>>>>> upstream/master
{
	if (m_cart)
		m_cart->pb_w(data);
}


//**************************************************************************
//  CARTRIDGE INTERFACE
//**************************************************************************

//-------------------------------------------------
<<<<<<< HEAD
//  device_parallel_interface - constructor
//-------------------------------------------------

device_parallel_interface::device_parallel_interface(const machine_config &mconfig, device_t &device) :
	device_slot_card_interface(mconfig, device)
{
	m_slot = dynamic_cast<parallel_slot_device *>(device.owner());
}

//-------------------------------------------------
//  ~device_parallel_interface - destructor
//-------------------------------------------------

device_parallel_interface::~device_parallel_interface()
=======
//  device_cg_parallel_interface - constructor
//-------------------------------------------------

device_cg_parallel_interface::device_cg_parallel_interface(const machine_config &mconfig, device_t &device) :
	device_slot_card_interface(mconfig, device)
{
	m_slot = dynamic_cast<cg_parallel_slot_device *>(device.owner());
}

//-------------------------------------------------
//  ~device_cg_parallel_interface - destructor
//-------------------------------------------------

device_cg_parallel_interface::~device_cg_parallel_interface()
>>>>>>> upstream/master
{
}
