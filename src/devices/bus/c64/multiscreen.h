// license:BSD-3-Clause
// copyright-holders:Curt Coder
/**********************************************************************

    Multiscreen cartridge emulation

**********************************************************************/

<<<<<<< HEAD
#pragma once

#ifndef __MULTISCREEN__
#define __MULTISCREEN__


#include "emu.h"
=======
#ifndef MAME_BUS_C64_MULTISCREEN_H
#define MAME_BUS_C64_MULTISCREEN_H

#pragma once


>>>>>>> upstream/master
#include "cpu/m6800/m6800.h"
#include "machine/6821pia.h"
#include "exp.h"



//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

// ======================> c64_multiscreen_cartridge_device

class c64_multiscreen_cartridge_device : public device_t,
											public device_c64_expansion_card_interface
{
public:
	// construction/destruction
<<<<<<< HEAD
	c64_multiscreen_cartridge_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// optional information overrides
	virtual const rom_entry *device_rom_region() const;
	virtual machine_config_constructor device_mconfig_additions() const;

protected:
	// device-level overrides
	virtual void device_start();
	virtual void device_reset();

	// device_c64_expansion_card_interface overrides
	virtual UINT8 c64_cd_r(address_space &space, offs_t offset, UINT8 data, int sphi2, int ba, int roml, int romh, int io1, int io2);
	virtual void c64_cd_w(address_space &space, offs_t offset, UINT8 data, int sphi2, int ba, int roml, int romh, int io1, int io2);

private:
	UINT8 m_bank;
=======
	c64_multiscreen_cartridge_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;

	// optional information overrides
	virtual const tiny_rom_entry *device_rom_region() const override;
	virtual void device_add_mconfig(machine_config &config) override;

	// device_c64_expansion_card_interface overrides
	virtual uint8_t c64_cd_r(address_space &space, offs_t offset, uint8_t data, int sphi2, int ba, int roml, int romh, int io1, int io2) override;
	virtual void c64_cd_w(address_space &space, offs_t offset, uint8_t data, int sphi2, int ba, int roml, int romh, int io1, int io2) override;

private:
	uint8_t m_bank;
>>>>>>> upstream/master
};


// device type definition
<<<<<<< HEAD
extern const device_type C64_MULTISCREEN;


#endif
=======
DECLARE_DEVICE_TYPE(C64_MULTISCREEN, c64_multiscreen_cartridge_device)


#endif // MAME_BUS_C64_MULTISCREEN_H
>>>>>>> upstream/master
