// license:BSD-3-Clause
// copyright-holders:Curt Coder
/**********************************************************************

    COMX-35 Expansion Slot emulation

**********************************************************************/

<<<<<<< HEAD
=======
#include "emu.h"
>>>>>>> upstream/master
#include "exp.h"


//**************************************************************************
//  DEVICE DEFINITIONS
//**************************************************************************

<<<<<<< HEAD
const device_type COMX_EXPANSION_SLOT = &device_creator<comx_expansion_slot_device>;
=======
DEFINE_DEVICE_TYPE(COMX_EXPANSION_SLOT, comx_expansion_slot_device, "comx_expansion_slot", "COMX-35 expansion slot")
>>>>>>> upstream/master



//**************************************************************************
//  DEVICE COMX_EXPANSION CARD INTERFACE
//**************************************************************************

//-------------------------------------------------
//  device_comx_expansion_card_interface - constructor
//-------------------------------------------------

device_comx_expansion_card_interface::device_comx_expansion_card_interface(const machine_config &mconfig, device_t &device) :
	device_slot_card_interface(mconfig, device),
	m_ds(1)
{
	m_slot = dynamic_cast<comx_expansion_slot_device *>(device.owner());
}



//**************************************************************************
//  LIVE DEVICE
//**************************************************************************

//-------------------------------------------------
//  comx_expansion_slot_device - constructor
//-------------------------------------------------

<<<<<<< HEAD
comx_expansion_slot_device::comx_expansion_slot_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock) :
	device_t(mconfig, COMX_EXPANSION_SLOT, "COMX-35 expansion slot", tag, owner, clock, "comx_expansion_slot", __FILE__),
=======
comx_expansion_slot_device::comx_expansion_slot_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock) :
	device_t(mconfig, COMX_EXPANSION_SLOT, tag, owner, clock),
>>>>>>> upstream/master
	device_slot_interface(mconfig, *this),
	m_write_irq(*this), m_card(nullptr)
{
}


//-------------------------------------------------
//  device_start - device-specific startup
//-------------------------------------------------

void comx_expansion_slot_device::device_start()
{
	m_card = dynamic_cast<device_comx_expansion_card_interface *>(get_card_device());

	// resolve callbacks
	m_write_irq.resolve_safe();
}


//-------------------------------------------------
//  mrd_r - memory read
//-------------------------------------------------

<<<<<<< HEAD
UINT8 comx_expansion_slot_device::mrd_r(address_space &space, offs_t offset, int *extrom)
{
	UINT8 data = 0;

	if (m_card != NULL)
=======
uint8_t comx_expansion_slot_device::mrd_r(address_space &space, offs_t offset, int *extrom)
{
	uint8_t data = 0;

	if (m_card != nullptr)
>>>>>>> upstream/master
	{
		data = m_card->comx_mrd_r(space, offset, extrom);
	}

	return data;
}


//-------------------------------------------------
//  mwr_w - memory write
//-------------------------------------------------

<<<<<<< HEAD
void comx_expansion_slot_device::mwr_w(address_space &space, offs_t offset, UINT8 data)
{
	if (m_card != NULL)
=======
void comx_expansion_slot_device::mwr_w(address_space &space, offs_t offset, uint8_t data)
{
	if (m_card != nullptr)
>>>>>>> upstream/master
	{
		m_card->comx_mwr_w(space, offset, data);
	}
}


//-------------------------------------------------
//  io_r - I/O read
//-------------------------------------------------

<<<<<<< HEAD
UINT8 comx_expansion_slot_device::io_r(address_space &space, offs_t offset)
{
	UINT8 data = 0;

	if (m_card != NULL)
=======
uint8_t comx_expansion_slot_device::io_r(address_space &space, offs_t offset)
{
	uint8_t data = 0;

	if (m_card != nullptr)
>>>>>>> upstream/master
	{
		data = m_card->comx_io_r(space, offset);
	}

	return data;
}


//-------------------------------------------------
//  sout_w - I/O write
//-------------------------------------------------

<<<<<<< HEAD
void comx_expansion_slot_device::io_w(address_space &space, offs_t offset, UINT8 data)
{
	if (m_card != NULL)
=======
void comx_expansion_slot_device::io_w(address_space &space, offs_t offset, uint8_t data)
{
	if (m_card != nullptr)
>>>>>>> upstream/master
	{
		m_card->comx_io_w(space, offset, data);
	}
}


//-------------------------------------------------
//  ds_w - device select write
//-------------------------------------------------

WRITE_LINE_MEMBER( comx_expansion_slot_device::ds_w )
{
<<<<<<< HEAD
	if (m_card != NULL)
=======
	if (m_card != nullptr)
>>>>>>> upstream/master
	{
		m_card->comx_ds_w(state);
	}
}


//-------------------------------------------------
//  q_w - Q write
//-------------------------------------------------

WRITE_LINE_MEMBER( comx_expansion_slot_device::q_w )
{
<<<<<<< HEAD
	if (m_card != NULL)
=======
	if (m_card != nullptr)
>>>>>>> upstream/master
	{
		m_card->comx_q_w(state);
	}
}

READ_LINE_MEMBER( comx_expansion_slot_device::ef4_r )
{
	int state = CLEAR_LINE;

<<<<<<< HEAD
	if (m_card != NULL)
=======
	if (m_card != nullptr)
>>>>>>> upstream/master
	{
		state = m_card->comx_ef4_r();
	}

	return state;
}


//-------------------------------------------------
//  SLOT_INTERFACE( comx_expansion_cards )
//-------------------------------------------------

// slot devices
#include "clm.h"
#include "eprom.h"
#include "expbox.h"
#include "fdc.h"
#include "joycard.h"
#include "printer.h"
#include "ram.h"
#include "thermal.h"

SLOT_INTERFACE_START( comx_expansion_cards )
	SLOT_INTERFACE("eb", COMX_EB)
	SLOT_INTERFACE("fd", COMX_FD)
	SLOT_INTERFACE("clm", COMX_CLM)
	SLOT_INTERFACE("ram", COMX_RAM)
	SLOT_INTERFACE("joy", COMX_JOY)
	SLOT_INTERFACE("prn", COMX_PRN)
	SLOT_INTERFACE("thm", COMX_THM)
	SLOT_INTERFACE("epr", COMX_EPR)
SLOT_INTERFACE_END
