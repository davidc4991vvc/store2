// license:BSD-3-Clause
// copyright-holders:Curt Coder
/**********************************************************************

    Coleco Adam printer controller emulation

**********************************************************************/

<<<<<<< HEAD
#pragma once

#ifndef __ADAM_PRN__
#define __ADAM_PRN__

#include "emu.h"
#include "adamnet.h"
#include "cpu/m6800/m6800.h"
=======
#ifndef MAME_BUS_ADAMNET_PRINTER_H
#define MAME_BUS_ADAMNET_PRINTER_H

#pragma once

#include "adamnet.h"
#include "cpu/m6800/m6801.h"
>>>>>>> upstream/master



//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

// ======================> adam_printer_device

class adam_printer_device :  public device_t,
								public device_adamnet_card_interface
{
public:
	// construction/destruction
<<<<<<< HEAD
	adam_printer_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// optional information overrides
	virtual const rom_entry *device_rom_region() const;
	virtual machine_config_constructor device_mconfig_additions() const;
=======
	adam_printer_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
>>>>>>> upstream/master

	// not really public
	DECLARE_WRITE8_MEMBER( p1_w );
	DECLARE_READ8_MEMBER( p2_r );
	DECLARE_WRITE8_MEMBER( p2_w );
	DECLARE_READ8_MEMBER( p3_r );
	DECLARE_READ8_MEMBER( p4_r );
	DECLARE_WRITE8_MEMBER( p4_w );

protected:
	// device-level overrides
<<<<<<< HEAD
	virtual void device_start();

	// device_adamnet_card_interface overrides
	virtual void adamnet_reset_w(int state);
=======
	virtual void device_start() override;

	// optional information overrides
	virtual const tiny_rom_entry *device_rom_region() const override;
	virtual void device_add_mconfig(machine_config &config) override;

	// device_adamnet_card_interface overrides
	virtual void adamnet_reset_w(int state) override;
>>>>>>> upstream/master

	required_device<cpu_device> m_maincpu;
};


// device type definition
<<<<<<< HEAD
extern const device_type ADAM_PRN;



#endif
=======
DECLARE_DEVICE_TYPE(ADAM_PRN, adam_printer_device)

#endif // MAME_BUS_ADAMNET_PRINTER_H
>>>>>>> upstream/master
