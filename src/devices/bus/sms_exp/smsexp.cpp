// license:BSD-3-Clause
// copyright-holders:Fabio Priuli
/**********************************************************************

    Sega Master System expansion slot emulation

**********************************************************************/

<<<<<<< HEAD
#include "smsexp.h"

=======
#include "emu.h"
#include "smsexp.h"

// slot devices
#include "gender.h"


>>>>>>> upstream/master


//**************************************************************************
//  GLOBAL VARIABLES
//**************************************************************************

<<<<<<< HEAD
const device_type SMS_EXPANSION_SLOT = &device_creator<sms_expansion_slot_device>;
=======
DEFINE_DEVICE_TYPE(SMS_EXPANSION_SLOT, sms_expansion_slot_device, "sms_expansion_slot", "Sega SMS expansion slot")
>>>>>>> upstream/master



//**************************************************************************
//  CARD INTERFACE
//**************************************************************************

//-------------------------------------------------
//  device_sms_expansion_slot_interface - constructor
//-------------------------------------------------

device_sms_expansion_slot_interface::device_sms_expansion_slot_interface(const machine_config &mconfig, device_t &device)
	: device_slot_card_interface(mconfig,device)
{
}


//-------------------------------------------------
//  ~device_sms_expansion_slot_interface - destructor
//-------------------------------------------------

device_sms_expansion_slot_interface::~device_sms_expansion_slot_interface()
{
}



//**************************************************************************
//  LIVE DEVICE
//**************************************************************************

//-------------------------------------------------
//  sms_expansion_slot_device - constructor
//-------------------------------------------------

<<<<<<< HEAD
sms_expansion_slot_device::sms_expansion_slot_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock) :
						device_t(mconfig, SMS_EXPANSION_SLOT, "Sega SMS expansion slot", tag, owner, clock, "sms_expansion_slot", __FILE__),
						device_slot_interface(mconfig, *this), m_device(nullptr)
=======
sms_expansion_slot_device::sms_expansion_slot_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock) :
	device_t(mconfig, SMS_EXPANSION_SLOT, tag, owner, clock),
	device_slot_interface(mconfig, *this),
	m_device(nullptr)
>>>>>>> upstream/master
{
}


//-------------------------------------------------
//  sms_expansion_slot_device - destructor
//-------------------------------------------------

sms_expansion_slot_device::~sms_expansion_slot_device()
{
}


//-------------------------------------------------
//  device_start - device-specific startup
//-------------------------------------------------

void sms_expansion_slot_device::device_start()
{
	m_device = dynamic_cast<device_sms_expansion_slot_interface *>(get_card_device());
}


//-------------------------------------------------
<<<<<<< HEAD
// read
//-------------------------------------------------

READ8_MEMBER(sms_expansion_slot_device::read)
{
	if (m_device)
		return m_device->read(space, offset);
	else
		return 0xff;
}

READ8_MEMBER(sms_expansion_slot_device::read_ram)
{
	if (m_device)
		return m_device->read_ram(space, offset);
	else
		return 0xff;
}

int sms_expansion_slot_device::get_lphaser_xoffs()
{
	if (m_device)
		return m_device->get_lphaser_xoffs();
	else
		return 0;
}


//-------------------------------------------------
// write
//-------------------------------------------------

WRITE8_MEMBER(sms_expansion_slot_device::write_mapper)
{
	if (m_device)
		m_device->write_mapper(space, offset, data);
}

WRITE8_MEMBER(sms_expansion_slot_device::write)
{
	if (m_device)
		m_device->write(space, offset, data);
}

WRITE8_MEMBER(sms_expansion_slot_device::write_ram)
{
	if (m_device)
		m_device->write_ram(space, offset, data);
}


//-------------------------------------------------
=======
>>>>>>> upstream/master
//  SLOT_INTERFACE( sms_expansion_devices )
//-------------------------------------------------

SLOT_INTERFACE_START( sms_expansion_devices )
	SLOT_INTERFACE("genderadp", SMS_GENDER_ADAPTER)
SLOT_INTERFACE_END
