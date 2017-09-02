// license:BSD-3-Clause
// copyright-holders:Curt Coder
/**********************************************************************

    Kingsoft cartridge emulation

**********************************************************************/

<<<<<<< HEAD
#pragma once

#ifndef __KINGSOFT__
#define __KINGSOFT__


#include "emu.h"
=======
#ifndef MAME_BUS_C64_KINGSOFT_H
#define MAME_BUS_C64_KINGSOFT_H

#pragma once


>>>>>>> upstream/master
#include "exp.h"



//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

// ======================> c64_kingsoft_cartridge_device

class c64_kingsoft_cartridge_device : public device_t,
										public device_c64_expansion_card_interface
{
public:
	// construction/destruction
<<<<<<< HEAD
	c64_kingsoft_cartridge_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

protected:
	// device-level overrides
	virtual void device_start();
	virtual void device_reset();

	// device_c64_expansion_card_interface overrides
	virtual UINT8 c64_cd_r(address_space &space, offs_t offset, UINT8 data, int sphi2, int ba, int roml, int romh, int io1, int io2);
	virtual void c64_cd_w(address_space &space, offs_t offset, UINT8 data, int sphi2, int ba, int roml, int romh, int io1, int io2);
	virtual int c64_game_r(offs_t offset, int sphi2, int ba, int rw);
=======
	c64_kingsoft_cartridge_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;

	// device_c64_expansion_card_interface overrides
	virtual uint8_t c64_cd_r(address_space &space, offs_t offset, uint8_t data, int sphi2, int ba, int roml, int romh, int io1, int io2) override;
	virtual void c64_cd_w(address_space &space, offs_t offset, uint8_t data, int sphi2, int ba, int roml, int romh, int io1, int io2) override;
	virtual int c64_game_r(offs_t offset, int sphi2, int ba, int rw) override;
>>>>>>> upstream/master
};


// device type definition
<<<<<<< HEAD
extern const device_type C64_KINGSOFT;


#endif
=======
DECLARE_DEVICE_TYPE(C64_KINGSOFT, c64_kingsoft_cartridge_device)


#endif // MAME_BUS_C64_KINGSOFT_H
>>>>>>> upstream/master
