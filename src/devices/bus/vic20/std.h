// license:BSD-3-Clause
// copyright-holders:Curt Coder
/**********************************************************************

    Commodore VIC-20 Standard 8K/16K ROM Cartridge emulation

**********************************************************************/

<<<<<<< HEAD
#pragma once

#ifndef __VIC20_STD__
#define __VIC20_STD__

#include "emu.h"
=======
#ifndef MAME_BUS_VIC20_STD_H
#define MAME_BUS_VIC20_STD_H

#pragma once

>>>>>>> upstream/master
#include "exp.h"



//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

// ======================> vic20_standard_cartridge_device

class vic20_standard_cartridge_device :  public device_t,
											public device_vic20_expansion_card_interface
{
public:
	// construction/destruction
<<<<<<< HEAD
	vic20_standard_cartridge_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

protected:
	// device-level overrides
	virtual void device_start();

	// device_vic20_expansion_card_interface overrides
	virtual UINT8 vic20_cd_r(address_space &space, offs_t offset, UINT8 data, int ram1, int ram2, int ram3, int blk1, int blk2, int blk3, int blk5, int io2, int io3);
=======
	vic20_standard_cartridge_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

protected:
	// device-level overrides
	virtual void device_start() override;

	// device_vic20_expansion_card_interface overrides
	virtual uint8_t vic20_cd_r(address_space &space, offs_t offset, uint8_t data, int ram1, int ram2, int ram3, int blk1, int blk2, int blk3, int blk5, int io2, int io3) override;
>>>>>>> upstream/master
};


// device type definition
<<<<<<< HEAD
extern const device_type VIC20_STD;



#endif
=======
DECLARE_DEVICE_TYPE(VIC20_STD, vic20_standard_cartridge_device)

#endif // MAME_BUS_VIC20_STD_H
>>>>>>> upstream/master
