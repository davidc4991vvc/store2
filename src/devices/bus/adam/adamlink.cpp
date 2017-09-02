// license:BSD-3-Clause
// copyright-holders:Curt Coder
/**********************************************************************

    Coleco AdamLink 300 Baud Modem emulation

**********************************************************************/

<<<<<<< HEAD
=======
#include "emu.h"
>>>>>>> upstream/master
#include "adamlink.h"



//**************************************************************************
//  DEVICE DEFINITIONS
//**************************************************************************

<<<<<<< HEAD
const device_type ADAMLINK = &device_creator<adamlink_device>;
=======
DEFINE_DEVICE_TYPE(ADAMLINK, adamlink_device, "adamlink", "AdamLink modem")
>>>>>>> upstream/master



//**************************************************************************
//  LIVE DEVICE
//**************************************************************************

//-------------------------------------------------
//  adamlink_device - constructor
//-------------------------------------------------

<<<<<<< HEAD
adamlink_device::adamlink_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock)
	: device_t(mconfig, ADAMLINK, "AdamLink modem", tag, owner, clock, "adamlink", __FILE__),
		device_adam_expansion_slot_card_interface(mconfig, *this)
=======
adamlink_device::adamlink_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock)
	: device_t(mconfig, ADAMLINK, tag, owner, clock)
	, device_adam_expansion_slot_card_interface(mconfig, *this)
>>>>>>> upstream/master
{
}


//-------------------------------------------------
//  device_start - device-specific startup
//-------------------------------------------------

void adamlink_device::device_start()
{
}


//-------------------------------------------------
//  adam_bd_r - buffered data read
//-------------------------------------------------

<<<<<<< HEAD
UINT8 adamlink_device::adam_bd_r(address_space &space, offs_t offset, UINT8 data, int bmreq, int biorq, int aux_rom_cs, int cas1, int cas2)
=======
uint8_t adamlink_device::adam_bd_r(address_space &space, offs_t offset, uint8_t data, int bmreq, int biorq, int aux_rom_cs, int cas1, int cas2)
>>>>>>> upstream/master
{
	if (!biorq)
	{
		switch (offset)
		{
		case 0x5e:
			break;

		case 0x5f:
			break;
		}
	}

	return data;
}


//-------------------------------------------------
//  adam_bd_w - buffered data write
//-------------------------------------------------

<<<<<<< HEAD
void adamlink_device::adam_bd_w(address_space &space, offs_t offset, UINT8 data, int bmreq, int biorq, int aux_rom_cs, int cas1, int cas2)
=======
void adamlink_device::adam_bd_w(address_space &space, offs_t offset, uint8_t data, int bmreq, int biorq, int aux_rom_cs, int cas1, int cas2)
>>>>>>> upstream/master
{
	if (!biorq)
	{
		switch (offset)
		{
		case 0x5e:
			break;

		case 0x5f:
			break;
		}
	}
}
