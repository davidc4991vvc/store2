// license:BSD-3-Clause
// copyright-holders:Curt Coder
/**********************************************************************

    VizaWrite 64 cartridge emulation

**********************************************************************/

<<<<<<< HEAD
#pragma once

#ifndef __VW64__
#define __VW64__


#include "emu.h"
=======
#ifndef MAME_BUS_C64_VW64_H
#define MAME_BUS_C64_VW64_H

#pragma once


>>>>>>> upstream/master
#include "exp.h"



//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

// ======================> c64_vizawrite_cartridge_device

class c64_vizawrite_cartridge_device : public device_t,
										public device_c64_expansion_card_interface
{
public:
	// construction/destruction
<<<<<<< HEAD
	c64_vizawrite_cartridge_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

protected:
	// device-level overrides
	virtual void device_start();
	virtual void device_reset();
	virtual void device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr);

	// device_c64_expansion_card_interface overrides
	virtual UINT8 c64_cd_r(address_space &space, offs_t offset, UINT8 data, int sphi2, int ba, int roml, int romh, int io1, int io2);
	virtual int c64_exrom_r(offs_t offset, int sphi2, int ba, int rw) { return 0; }
=======
	c64_vizawrite_cartridge_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;
	virtual void device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr) override;

	// device_c64_expansion_card_interface overrides
	virtual uint8_t c64_cd_r(address_space &space, offs_t offset, uint8_t data, int sphi2, int ba, int roml, int romh, int io1, int io2) override;
	virtual int c64_exrom_r(offs_t offset, int sphi2, int ba, int rw) override { return 0; }
>>>>>>> upstream/master

private:
	emu_timer *m_game_timer;
};


// device type definition
<<<<<<< HEAD
extern const device_type C64_VW64;


#endif
=======
DECLARE_DEVICE_TYPE(C64_VW64, c64_vizawrite_cartridge_device)


#endif // MAME_BUS_C64_VW64_H
>>>>>>> upstream/master
