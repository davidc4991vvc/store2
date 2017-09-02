// license:BSD-3-Clause
// copyright-holders:Curt Coder
/**********************************************************************

    Commodore Plus/4 standard cartridge emulation

**********************************************************************/

<<<<<<< HEAD
#pragma once

#ifndef __PLUS4_STANDARD_CARTRIDGE__
#define __PLUS4_STANDARD_CARTRIDGE__

#include "emu.h"
=======
#ifndef MAME_BUS_PLUS4_STD_H
#define MAME_BUS_PLUS4_STD_H

#pragma once

>>>>>>> upstream/master
#include "exp.h"



//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

// ======================> plus4_standard_cartridge_device

class plus4_standard_cartridge_device : public device_t,
										public device_plus4_expansion_card_interface
{
public:
	// construction/destruction
<<<<<<< HEAD
	plus4_standard_cartridge_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

protected:
	// device-level overrides
	virtual void device_start();

	// device_plus4_expansion_card_interface overrides
	virtual UINT8 plus4_cd_r(address_space &space, offs_t offset, UINT8 data, int ba, int cs0, int c1l, int c2l, int cs1, int c1h, int c2h);


=======
	plus4_standard_cartridge_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

protected:
	// device-level overrides
	virtual void device_start() override;

	// device_plus4_expansion_card_interface overrides
	virtual uint8_t plus4_cd_r(address_space &space, offs_t offset, uint8_t data, int ba, int cs0, int c1l, int c2l, int cs1, int c1h, int c2h) override;
>>>>>>> upstream/master
};


// device type definition
<<<<<<< HEAD
extern const device_type PLUS4_STD;


#endif
=======
DECLARE_DEVICE_TYPE(PLUS4_STD, plus4_standard_cartridge_device)

#endif // MAME_BUS_PLUS4_STD_H
>>>>>>> upstream/master
