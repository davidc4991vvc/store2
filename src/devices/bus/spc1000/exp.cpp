// license:BSD-3-Clause
// copyright-holders:Fabio Priuli
/***********************************************************************************************************

    Samsung SPC-1000 Expansion port

 ***********************************************************************************************************/


#include "emu.h"
#include "exp.h"

//**************************************************************************
//  GLOBAL VARIABLES
//**************************************************************************

<<<<<<< HEAD
const device_type SPC1000_EXP_SLOT = &device_creator<spc1000_exp_device>;
=======
DEFINE_DEVICE_TYPE(SPC1000_EXP_SLOT, spc1000_exp_device, "spc1000_exp", "Samsung SPC-1000 expansion")
>>>>>>> upstream/master


device_spc1000_card_interface::device_spc1000_card_interface(const machine_config &mconfig, device_t &device)
	: device_slot_card_interface(mconfig, device)
{
}


device_spc1000_card_interface::~device_spc1000_card_interface()
{
}


//**************************************************************************
//  LIVE DEVICE
//**************************************************************************

//-------------------------------------------------
//  spc1000_exp_device - constructor
//-------------------------------------------------
<<<<<<< HEAD
spc1000_exp_device::spc1000_exp_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock) :
						device_t(mconfig, SPC1000_EXP_SLOT, "Samsung SPC-1000 expansion", tag, owner, clock, "spc1000_exp", __FILE__),
						device_slot_interface(mconfig, *this), m_card(nullptr)
=======
spc1000_exp_device::spc1000_exp_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock) :
	device_t(mconfig, SPC1000_EXP_SLOT, tag, owner, clock),
	device_slot_interface(mconfig, *this),
	m_card(nullptr)
>>>>>>> upstream/master
{
}


//-------------------------------------------------
//  spc1000_exp_device - destructor
//-------------------------------------------------

spc1000_exp_device::~spc1000_exp_device()
{
}

//-------------------------------------------------
//  device_start - device-specific startup
//-------------------------------------------------

void spc1000_exp_device::device_start()
{
	m_card = dynamic_cast<device_spc1000_card_interface *>(get_card_device());
}

/*-------------------------------------------------
 read
 -------------------------------------------------*/

READ8_MEMBER(spc1000_exp_device::read)
{
	if (m_card)
		return m_card->read(space, offset);
	else
		return 0xff;
}

/*-------------------------------------------------
 write
 -------------------------------------------------*/

WRITE8_MEMBER(spc1000_exp_device::write)
{
	if (m_card)
		m_card->write(space, offset, data);
}
