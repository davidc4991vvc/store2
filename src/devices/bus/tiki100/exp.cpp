// license:BSD-3-Clause
// copyright-holders:Curt Coder
/**********************************************************************

    TIKI-100 expansion bus emulation

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
const device_type TIKI100_BUS = &device_creator<tiki100_bus_t>;
const device_type TIKI100_BUS_SLOT = &device_creator<tiki100_bus_slot_t>;
=======
DEFINE_DEVICE_TYPE(TIKI100_BUS,      tiki100_bus_device,      "tiki100bus",      "TIKI-100 expansion bus")
DEFINE_DEVICE_TYPE(TIKI100_BUS_SLOT, tiki100_bus_slot_device, "tiki100bus_slot", "TIKI-100 expansion bus slot")
>>>>>>> upstream/master



//**************************************************************************
//  LIVE DEVICE
//**************************************************************************

//-------------------------------------------------
<<<<<<< HEAD
//  tiki100_bus_slot_t - constructor
//-------------------------------------------------

tiki100_bus_slot_t::tiki100_bus_slot_t(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock) :
	device_t(mconfig, TIKI100_BUS_SLOT, "TIKI-100 expansion bus slot", tag, owner, clock, "tiki100bus_slot", __FILE__),
=======
//  tiki100_bus_slot_device - constructor
//-------------------------------------------------

tiki100_bus_slot_device::tiki100_bus_slot_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock) :
	device_t(mconfig, TIKI100_BUS_SLOT, tag, owner, clock),
>>>>>>> upstream/master
	device_slot_interface(mconfig, *this),
	device_z80daisy_interface(mconfig, *this),
	m_bus(nullptr),
	m_card(nullptr)
{
}


//-------------------------------------------------
//  device_start - device-specific startup
//-------------------------------------------------

<<<<<<< HEAD
void tiki100_bus_slot_t::device_start()
{
	m_bus = machine().device<tiki100_bus_t>(TIKI100_BUS_TAG);
=======
void tiki100_bus_slot_device::device_start()
{
	m_bus = machine().device<tiki100_bus_device>(TIKI100_BUS_TAG);
>>>>>>> upstream/master
	device_tiki100bus_card_interface *dev = dynamic_cast<device_tiki100bus_card_interface *>(get_card_device());
	if (dev)
	{
		m_bus->add_card(dev);
		m_card = dev;
	}
}


//-------------------------------------------------
<<<<<<< HEAD
//  tiki100_bus_t - constructor
//-------------------------------------------------

tiki100_bus_t::tiki100_bus_t(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock) :
	device_t(mconfig, TIKI100_BUS, "TIKI-100 expansion bus", tag, owner, clock, "tiki100bus", __FILE__),
=======
//  tiki100_bus_device - constructor
//-------------------------------------------------

tiki100_bus_device::tiki100_bus_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock) :
	device_t(mconfig, TIKI100_BUS, tag, owner, clock),
>>>>>>> upstream/master
	m_irq_cb(*this),
	m_nmi_cb(*this),
	m_busrq_cb(*this),
	m_in_mrq_cb(*this),
	m_out_mrq_cb(*this)
{
}


//-------------------------------------------------
//  device_start - device-specific startup
//-------------------------------------------------

<<<<<<< HEAD
void tiki100_bus_t::device_start()
=======
void tiki100_bus_device::device_start()
>>>>>>> upstream/master
{
	// resolve callbacks
	m_irq_cb.resolve_safe();
	m_nmi_cb.resolve_safe();
	m_busrq_cb.resolve_safe();
	m_in_mrq_cb.resolve();
	m_out_mrq_cb.resolve();
}


//-------------------------------------------------
//  add_card - add card
//-------------------------------------------------

<<<<<<< HEAD
void tiki100_bus_t::add_card(device_tiki100bus_card_interface *card)
=======
void tiki100_bus_device::add_card(device_tiki100bus_card_interface *card)
>>>>>>> upstream/master
{
	m_device_list.append(*card);

	card->m_bus = this;
}


//-------------------------------------------------
//  mrq_r - memory read
//-------------------------------------------------

<<<<<<< HEAD
UINT8 tiki100_bus_t::mrq_r(address_space &space, offs_t offset, UINT8 data, bool &mdis)
=======
uint8_t tiki100_bus_device::mrq_r(address_space &space, offs_t offset, uint8_t data, bool &mdis)
>>>>>>> upstream/master
{
	device_tiki100bus_card_interface *entry = m_device_list.first();

	while (entry)
	{
		data &= entry->mrq_r(space, offset, data, mdis);
		entry = entry->next();
	}

	return data;
}


//-------------------------------------------------
//  mrq_w - memory write
//-------------------------------------------------

<<<<<<< HEAD
WRITE8_MEMBER( tiki100_bus_t::mrq_w )
=======
WRITE8_MEMBER( tiki100_bus_device::mrq_w )
>>>>>>> upstream/master
{
	device_tiki100bus_card_interface *entry = m_device_list.first();

	while (entry)
	{
		entry->mrq_w(space, offset, data);
		entry = entry->next();
	}
}


//-------------------------------------------------
//  iorq_r - I/O read
//-------------------------------------------------

<<<<<<< HEAD
UINT8 tiki100_bus_t::iorq_r(address_space &space, offs_t offset, UINT8 data)
=======
uint8_t tiki100_bus_device::iorq_r(address_space &space, offs_t offset, uint8_t data)
>>>>>>> upstream/master
{
	device_tiki100bus_card_interface *entry = m_device_list.first();

	while (entry)
	{
		data &= entry->iorq_r(space, offset, data);
		entry = entry->next();
	}

	return data;
}


//-------------------------------------------------
//  iorq_w - I/O write
//-------------------------------------------------

<<<<<<< HEAD
WRITE8_MEMBER( tiki100_bus_t::iorq_w )
=======
WRITE8_MEMBER( tiki100_bus_device::iorq_w )
>>>>>>> upstream/master
{
	device_tiki100bus_card_interface *entry = m_device_list.first();

	while (entry)
	{
		entry->iorq_w(space, offset, data);
		entry = entry->next();
	}
}


//-------------------------------------------------
//  busak_w - bus acknowledge write
//-------------------------------------------------

<<<<<<< HEAD
WRITE_LINE_MEMBER( tiki100_bus_t::busak_w )
=======
WRITE_LINE_MEMBER( tiki100_bus_device::busak_w )
>>>>>>> upstream/master
{
	device_tiki100bus_card_interface *entry = m_device_list.first();

	while (entry)
	{
		entry->busak_w(state);
		entry = entry->next();
	}
}



//**************************************************************************
//  DEVICE TIKI-100 BUS CARD INTERFACE
//**************************************************************************

//-------------------------------------------------
//  device_tiki100bus_card_interface - constructor
//-------------------------------------------------

device_tiki100bus_card_interface::device_tiki100bus_card_interface(const machine_config &mconfig, device_t &device) :
	device_slot_card_interface(mconfig, device), m_bus(nullptr),
	m_busak(CLEAR_LINE), m_next(nullptr)
{
<<<<<<< HEAD
	m_slot = dynamic_cast<tiki100_bus_slot_t *>(device.owner());
=======
	m_slot = dynamic_cast<tiki100_bus_slot_device *>(device.owner());
>>>>>>> upstream/master
}


//-------------------------------------------------
//  SLOT_INTERFACE( tiki100_cards )
//-------------------------------------------------

// slot devices
#include "8088.h"
#include "hdc.h"

SLOT_INTERFACE_START( tiki100_cards )
	SLOT_INTERFACE("8088", TIKI100_8088)
	SLOT_INTERFACE("hdc", TIKI100_HDC)
SLOT_INTERFACE_END
