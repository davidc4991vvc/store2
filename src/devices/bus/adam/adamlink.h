// license:BSD-3-Clause
// copyright-holders:Curt Coder
/**********************************************************************

    Coleco AdamLink 300 Baud Modem emulation

**********************************************************************/

<<<<<<< HEAD
#pragma once

#ifndef __ADAMLINK__
#define __ADAMLINK__

#include "emu.h"
=======
#ifndef MAME_BUS_ADAM_ADAMLINK_H
#define MAME_BUS_ADAM_ADAMLINK_H

#pragma once

>>>>>>> upstream/master
#include "exp.h"



//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

// ======================> adamlink_device

class adamlink_device :  public device_t,
							public device_adam_expansion_slot_card_interface
{
public:
	// construction/destruction
<<<<<<< HEAD
	adamlink_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

protected:
	// device-level overrides
	virtual void device_start();

	// device_adam_expansion_slot_card_interface overrides
	virtual UINT8 adam_bd_r(address_space &space, offs_t offset, UINT8 data, int bmreq, int biorq, int aux_rom_cs, int cas1, int cas2);
	virtual void adam_bd_w(address_space &space, offs_t offset, UINT8 data, int bmreq, int biorq, int aux_rom_cs, int cas1, int cas2);
=======
	adamlink_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

protected:
	// device-level overrides
	virtual void device_start() override;

	// device_adam_expansion_slot_card_interface overrides
	virtual uint8_t adam_bd_r(address_space &space, offs_t offset, uint8_t data, int bmreq, int biorq, int aux_rom_cs, int cas1, int cas2) override;
	virtual void adam_bd_w(address_space &space, offs_t offset, uint8_t data, int bmreq, int biorq, int aux_rom_cs, int cas1, int cas2) override;
>>>>>>> upstream/master
};


// device type definition
<<<<<<< HEAD
extern const device_type ADAMLINK;



#endif
=======
DECLARE_DEVICE_TYPE(ADAMLINK, adamlink_device)

#endif // MAME_BUS_ADAM_ADAMLINK_H
>>>>>>> upstream/master
