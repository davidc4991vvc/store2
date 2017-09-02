// license:BSD-3-Clause
// copyright-holders:Curt Coder
/**********************************************************************

    MyAB Turbo-Kontroller disk controller emulation

*********************************************************************/

<<<<<<< HEAD
#pragma once

#ifndef __TURBO_KONTROLLER__
#define __TURBO_KONTROLLER__

#include "emu.h"
=======
#ifndef MAME_BUS_ABCBUS_TURBO_H
#define MAME_BUS_ABCBUS_TURBO_H

#pragma once

>>>>>>> upstream/master
#include "abcbus.h"
#include "cpu/z80/z80.h"
#include "cpu/z80/z80daisy.h"



//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

// ======================> turbo_kontroller_device

class turbo_kontroller_device :  public device_t,
									public device_abcbus_card_interface
{
public:
	// construction/destruction
<<<<<<< HEAD
	turbo_kontroller_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// optional information overrides
	virtual const rom_entry *device_rom_region() const;
	virtual machine_config_constructor device_mconfig_additions() const;

protected:
	// device-level overrides
	virtual void device_start();
	virtual void device_reset();

	// device_abcbus_interface overrides
	virtual void abcbus_cs(UINT8 data);
=======
	turbo_kontroller_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;

	// optional information overrides
	virtual const tiny_rom_entry *device_rom_region() const override;
	virtual void device_add_mconfig(machine_config &config) override;

	// device_abcbus_interface overrides
	virtual void abcbus_cs(uint8_t data) override;
>>>>>>> upstream/master

private:
	required_device<cpu_device> m_maincpu;
};


// device type definition
extern const device_type TURBO_KONTROLLER;
<<<<<<< HEAD



#endif
=======
DECLARE_DEVICE_TYPE(TURBO_KONTROLLER, turbo_kontroller_device)

#endif // MAME_BUS_ABCBUS_TURBO_H
>>>>>>> upstream/master
