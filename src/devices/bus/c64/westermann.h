// license:BSD-3-Clause
// copyright-holders:Curt Coder
/**********************************************************************

    Westermann Learning cartridge emulation

**********************************************************************/

<<<<<<< HEAD
#pragma once

#ifndef __WESTERMANN__
#define __WESTERMANN__


#include "emu.h"
=======
#ifndef MAME_BUS_C64_WESTERMANN_H
#define MAME_BUS_C64_WESTERMANN_H

#pragma once


>>>>>>> upstream/master
#include "exp.h"



//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

// ======================> c64_westermann_cartridge_device

class c64_westermann_cartridge_device : public device_t,
										public device_c64_expansion_card_interface
{
public:
	// construction/destruction
<<<<<<< HEAD
	c64_westermann_cartridge_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

protected:
	// device-level overrides
	virtual void device_start();
	virtual void device_reset();

	// device_c64_expansion_card_interface overrides
	virtual UINT8 c64_cd_r(address_space &space, offs_t offset, UINT8 data, int sphi2, int ba, int roml, int romh, int io1, int io2);
=======
	c64_westermann_cartridge_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;

	// device_c64_expansion_card_interface overrides
	virtual uint8_t c64_cd_r(address_space &space, offs_t offset, uint8_t data, int sphi2, int ba, int roml, int romh, int io1, int io2) override;
>>>>>>> upstream/master
};


// device type definition
<<<<<<< HEAD
extern const device_type C64_WESTERMANN;


#endif
=======
DECLARE_DEVICE_TYPE(C64_WESTERMANN, c64_westermann_cartridge_device)


#endif // MAME_BUS_C64_WESTERMANN_H
>>>>>>> upstream/master
