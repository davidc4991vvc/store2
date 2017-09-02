// license:BSD-3-Clause
// copyright-holders:Curt Coder
/**********************************************************************

    VideoBrain Money Minder cartridge emulation

**********************************************************************/

<<<<<<< HEAD
#pragma once

#ifndef __VIDEOBRAIN_MONEY_MINDER_CARTRIDGE__
#define __VIDEOBRAIN_MONEY_MINDER_CARTRIDGE__

#include "emu.h"
=======
#ifndef MAME_BUS_VIDBRAIN_MONEY_MINDER_H
#define MAME_BUS_VIDBRAIN_MONEY_MINDER_H

#pragma once

>>>>>>> upstream/master
#include "exp.h"



//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

// ======================> videobrain_money_minder_cartridge_device

class videobrain_money_minder_cartridge_device : public device_t,
													public device_videobrain_expansion_card_interface
{
public:
	// construction/destruction
<<<<<<< HEAD
	videobrain_money_minder_cartridge_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

protected:
	// device-level overrides
	virtual void device_start();

	// device_videobrain_expansion_card_interface overrides
	virtual UINT8 videobrain_bo_r(address_space &space, offs_t offset, int cs1, int cs2);
	virtual void videobrain_bo_w(address_space &space, offs_t offset, UINT8 data, int cs1, int cs2);
=======
	videobrain_money_minder_cartridge_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

protected:
	// device-level overrides
	virtual void device_start() override;

	// device_videobrain_expansion_card_interface overrides
	virtual uint8_t videobrain_bo_r(address_space &space, offs_t offset, int cs1, int cs2) override;
	virtual void videobrain_bo_w(address_space &space, offs_t offset, uint8_t data, int cs1, int cs2) override;
>>>>>>> upstream/master
};


// device type definition
<<<<<<< HEAD
extern const device_type VB_MONEY_MINDER;


#endif
=======
DECLARE_DEVICE_TYPE(VB_MONEY_MINDER, videobrain_money_minder_cartridge_device)

#endif // MAME_BUS_VIDBRAIN_MONEY_MINDER_H
>>>>>>> upstream/master
