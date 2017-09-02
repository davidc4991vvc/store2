// license:BSD-3-Clause
// copyright-holders:Curt Coder
/**********************************************************************

    Kontron Europe Card Bus emulation

**********************************************************************/

<<<<<<< HEAD
=======
#include "emu.h"
>>>>>>> upstream/master
#include "ecbbus.h"



//**************************************************************************
//  GLOBAL VARIABLES
//**************************************************************************

<<<<<<< HEAD
const device_type ECBBUS_SLOT = &device_creator<ecbbus_slot_device>;
=======
DEFINE_DEVICE_TYPE(ECBBUS_SLOT, ecbbus_slot_device, "ecbbus_slot", "ECB bus slot")
>>>>>>> upstream/master



//**************************************************************************
//  LIVE DEVICE
//**************************************************************************

//-------------------------------------------------
//  ecbbus_slot_device - constructor
//-------------------------------------------------

<<<<<<< HEAD
ecbbus_slot_device::ecbbus_slot_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock) :
		device_t(mconfig, ECBBUS_SLOT, "ECB bus slot", tag, owner, clock, "ecbbus_slot", __FILE__),
		device_slot_interface(mconfig, *this), m_bus_tag(nullptr), m_bus_num(0), m_bus(nullptr)
=======
ecbbus_slot_device::ecbbus_slot_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock) :
	device_t(mconfig, ECBBUS_SLOT, tag, owner, clock),
	device_slot_interface(mconfig, *this),
	m_bus_tag(nullptr), m_bus_num(0), m_bus(nullptr)
>>>>>>> upstream/master
{
}


//-------------------------------------------------
//  static_set_ecbbus_slot -
//-------------------------------------------------

void ecbbus_slot_device::static_set_ecbbus_slot(device_t &device, const char *tag, int num)
{
	ecbbus_slot_device &ecbbus_card = dynamic_cast<ecbbus_slot_device &>(device);
	ecbbus_card.m_bus_tag = tag;
	ecbbus_card.m_bus_num = num;
}


//-------------------------------------------------
//  device_start - device-specific startup
//-------------------------------------------------

void ecbbus_slot_device::device_start()
{
	m_bus = machine().device<ecbbus_device>(m_bus_tag);
	device_ecbbus_card_interface *dev = dynamic_cast<device_ecbbus_card_interface *>(get_card_device());
	if (dev) m_bus->add_card(dev, m_bus_num);
}



//**************************************************************************
//  DEVICE DEFINITIONS
//**************************************************************************

<<<<<<< HEAD
const device_type ECBBUS = &device_creator<ecbbus_device>;
=======
DEFINE_DEVICE_TYPE(ECBBUS, ecbbus_device, "ecbbus", "ECB bus")
>>>>>>> upstream/master



//**************************************************************************
//  DEVICE ECBBUS CARD INTERFACE
//**************************************************************************

//-------------------------------------------------
//  device_ecbbus_card_interface - constructor
//-------------------------------------------------

device_ecbbus_card_interface::device_ecbbus_card_interface(const machine_config &mconfig, device_t &device) :
	device_slot_card_interface(mconfig, device)
{
	m_slot = dynamic_cast<ecbbus_slot_device *>(device.owner());
}



//**************************************************************************
//  LIVE DEVICE
//**************************************************************************

//-------------------------------------------------
//  ecbbus_device - constructor
//-------------------------------------------------

<<<<<<< HEAD
ecbbus_device::ecbbus_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock) :
	device_t(mconfig, ECBBUS, "ECB bus", tag, owner, clock, "ecbbus", __FILE__),
	m_write_irq(*this),
	m_write_nmi(*this)
{
	for (int i = 0; i < MAX_ECBBUS_SLOTS; i++)
		m_ecbbus_device[i] = NULL;
=======
ecbbus_device::ecbbus_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock) :
	device_t(mconfig, ECBBUS, tag, owner, clock),
	m_write_irq(*this),
	m_write_nmi(*this)
{
	std::fill(std::begin(m_ecbbus_device), std::end(m_ecbbus_device), nullptr);
>>>>>>> upstream/master
}


//-------------------------------------------------
//  device_start - device-specific startup
//-------------------------------------------------

void ecbbus_device::device_start()
{
	// resolve callbacks
	m_write_irq.resolve_safe();
	m_write_nmi.resolve_safe();
}


//-------------------------------------------------
//  add_card - add ECB bus card
//-------------------------------------------------

void ecbbus_device::add_card(device_ecbbus_card_interface *card, int pos)
{
	m_ecbbus_device[pos] = card;
}


//-------------------------------------------------
//  mem_r -
//-------------------------------------------------

READ8_MEMBER( ecbbus_device::mem_r )
{
<<<<<<< HEAD
	UINT8 data = 0;

	for (int i = 0; i < MAX_ECBBUS_SLOTS; i++)
	{
		if (m_ecbbus_device[i] != NULL)
		{
			data |= m_ecbbus_device[i]->ecbbus_mem_r(offset);
=======
	uint8_t data = 0;

	for (auto & elem : m_ecbbus_device)
	{
		if (elem != nullptr)
		{
			data |= elem->ecbbus_mem_r(offset);
>>>>>>> upstream/master
		}
	}

	return data;
}


//-------------------------------------------------
//  mem_w -
//-------------------------------------------------

WRITE8_MEMBER( ecbbus_device::mem_w )
{
<<<<<<< HEAD
	for (int i = 0; i < MAX_ECBBUS_SLOTS; i++)
	{
		if (m_ecbbus_device[i] != NULL)
		{
			m_ecbbus_device[i]->ecbbus_mem_w(offset, data);
=======
	for (auto & elem : m_ecbbus_device)
	{
		if (elem != nullptr)
		{
			elem->ecbbus_mem_w(offset, data);
>>>>>>> upstream/master
		}
	}
}


//-------------------------------------------------
//  io_r -
//-------------------------------------------------

READ8_MEMBER( ecbbus_device::io_r )
{
<<<<<<< HEAD
	UINT8 data = 0;

	for (int i = 0; i < MAX_ECBBUS_SLOTS; i++)
	{
		if (m_ecbbus_device[i] != NULL)
		{
			data |= m_ecbbus_device[i]->ecbbus_io_r(offset);
=======
	uint8_t data = 0;

	for (auto & elem : m_ecbbus_device)
	{
		if (elem != nullptr)
		{
			data |= elem->ecbbus_io_r(offset);
>>>>>>> upstream/master
		}
	}

	return data;
}


//-------------------------------------------------
//  io_w -
//-------------------------------------------------

WRITE8_MEMBER( ecbbus_device::io_w )
{
<<<<<<< HEAD
	for (int i = 0; i < MAX_ECBBUS_SLOTS; i++)
	{
		if (m_ecbbus_device[i] != NULL)
		{
			m_ecbbus_device[i]->ecbbus_io_w(offset, data);
=======
	for (auto & elem : m_ecbbus_device)
	{
		if (elem != nullptr)
		{
			elem->ecbbus_io_w(offset, data);
>>>>>>> upstream/master
		}
	}
}


//-------------------------------------------------
//  SLOT_INTERFACE( ecbbus_cards )
//-------------------------------------------------

// slot devices
#include "grip.h"

SLOT_INTERFACE_START( ecbbus_cards )
	SLOT_INTERFACE("grip21", ECB_GRIP21)
/*  SLOT_INTERFACE("grip25", ECB_GRIP25)
    SLOT_INTERFACE("grip26", ECB_GRIP26)
    SLOT_INTERFACE("grip31", ECB_GRIP31)
    SLOT_INTERFACE("grip562", ECB_GRIP562)
    SLOT_INTERFACE("grips115", ECB_GRIPS115)*/
SLOT_INTERFACE_END
