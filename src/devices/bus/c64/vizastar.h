// license:BSD-3-Clause
// copyright-holders:Curt Coder
/**********************************************************************

    VizaStar 64 XL4 cartridge emulation

**********************************************************************/

<<<<<<< HEAD
#pragma once

#ifndef __VIZASTAR__
#define __VIZASTAR__


#include "emu.h"
=======
#ifndef MAME_BUS_C64_VIZASTAR_H
#define MAME_BUS_C64_VIZASTAR_H

#pragma once


>>>>>>> upstream/master
#include "exp.h"



//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

// ======================> c64_vizastar_cartridge_device

class c64_vizastar_cartridge_device : public device_t,
										public device_c64_expansion_card_interface
{
public:
	// construction/destruction
<<<<<<< HEAD
	c64_vizastar_cartridge_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

protected:
	// device-level overrides
	virtual void device_start();

	// device_c64_expansion_card_interface overrides
	virtual UINT8 c64_cd_r(address_space &space, offs_t offset, UINT8 data, int sphi2, int ba, int roml, int romh, int io1, int io2);
=======
	c64_vizastar_cartridge_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

protected:
	// device-level overrides
	virtual void device_start() override;

	// device_c64_expansion_card_interface overrides
	virtual uint8_t c64_cd_r(address_space &space, offs_t offset, uint8_t data, int sphi2, int ba, int roml, int romh, int io1, int io2) override;
>>>>>>> upstream/master
};


// device type definition
<<<<<<< HEAD
extern const device_type C64_VIZASTAR;


#endif
=======
DECLARE_DEVICE_TYPE(C64_VIZASTAR, c64_vizastar_cartridge_device)


#endif // MAME_BUS_C64_VIZASTAR_H
>>>>>>> upstream/master
