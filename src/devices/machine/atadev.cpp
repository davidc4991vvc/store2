// license:BSD-3-Clause
// copyright-holders:smf
/***************************************************************************

    ATA Device implementation.

***************************************************************************/

<<<<<<< HEAD
#include "atadev.h"

//-------------------------------------------------
//  ata_device_interface - constructor
//-------------------------------------------------

ata_device_interface::ata_device_interface(const machine_config &mconfig, device_t &device) :
=======
#include "emu.h"
#include "atadev.h"

//-------------------------------------------------
//  device_ata_interface - constructor
//-------------------------------------------------

device_ata_interface::device_ata_interface(const machine_config &mconfig, device_t &device) :
	device_slot_card_interface(mconfig, device),
>>>>>>> upstream/master
	m_irq_handler(device),
	m_dmarq_handler(device),
	m_dasp_handler(device),
	m_pdiag_handler(device)
{
}
