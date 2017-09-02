// license:BSD-3-Clause
// copyright-holders:Curt Coder
/**********************************************************************

    Commodore 64 CP/M cartridge emulation

**********************************************************************/

<<<<<<< HEAD
#pragma once

#ifndef __CPM__
#define __CPM__

#include "emu.h"
#include "cpu/z80/z80.h"
#include "exp.h"
=======
#ifndef MAME_BUS_C64_CPM_H
#define MAME_BUS_C64_CPM_H

#pragma once

#include "exp.h"
#include "cpu/z80/z80.h"
>>>>>>> upstream/master



//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

// ======================> c64_cpm_cartridge_device

class c64_cpm_cartridge_device : public device_t,
									public device_c64_expansion_card_interface
{
public:
	// construction/destruction
<<<<<<< HEAD
	c64_cpm_cartridge_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// optional information overrides
	virtual machine_config_constructor device_mconfig_additions() const;
=======
	c64_cpm_cartridge_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
>>>>>>> upstream/master

	// not really public
	DECLARE_READ8_MEMBER( dma_r );
	DECLARE_WRITE8_MEMBER( dma_w );

protected:
	// device-level overrides
<<<<<<< HEAD
	virtual void device_start();
	virtual void device_reset();

	// device_c64_expansion_card_interface overrides
	virtual void c64_cd_w(address_space &space, offs_t offset, UINT8 data, int sphi2, int ba, int roml, int romh, int io1, int io2);
	virtual int c64_game_r(offs_t offset, int sphi2, int ba, int rw);
=======
	virtual void device_start() override;
	virtual void device_reset() override;

	// optional information overrides
	virtual void device_add_mconfig(machine_config &config) override;

	// device_c64_expansion_card_interface overrides
	virtual void c64_cd_w(address_space &space, offs_t offset, uint8_t data, int sphi2, int ba, int roml, int romh, int io1, int io2) override;
	virtual int c64_game_r(offs_t offset, int sphi2, int ba, int rw) override;
>>>>>>> upstream/master

private:
	inline void update_signals();

	required_device<cpu_device> m_maincpu;

	int m_enabled;
	int m_ba;

	int m_reset;
};


// device type definition
<<<<<<< HEAD
extern const device_type C64_CPM;


#endif
=======
DECLARE_DEVICE_TYPE(C64_CPM, c64_cpm_cartridge_device)


#endif // MAME_BUS_C64_CPM_H
>>>>>>> upstream/master
