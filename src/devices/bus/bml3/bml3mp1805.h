// license:GPL-2.0+
// copyright-holders:Jonathan Edwards
/*********************************************************************

    bml3mp1805.h

    Hitachi MP-1805 floppy disk controller card for the MB-6890
    Floppy drive is attached

*********************************************************************/

<<<<<<< HEAD
#ifndef __BML3BUS_MP1805__
#define __BML3BUS_MP1805__

#include "emu.h"
=======
#ifndef MAME_BUS_BML3_BML3MP1805_H
#define MAME_BUS_BML3_BML3MP1805_H

#pragma once

>>>>>>> upstream/master
#include "bml3bus.h"
#include "imagedev/flopdrv.h"
#include "machine/mc6843.h"

//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

class bml3bus_mp1805_device:
	public device_t,
	public device_bml3bus_card_interface
{
public:
	// construction/destruction
<<<<<<< HEAD
	bml3bus_mp1805_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// optional information overrides
	virtual machine_config_constructor device_mconfig_additions() const;
	virtual const rom_entry *device_rom_region() const;
=======
	bml3bus_mp1805_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
>>>>>>> upstream/master

	DECLARE_READ8_MEMBER(bml3_mp1805_r);
	DECLARE_WRITE8_MEMBER(bml3_mp1805_w);

<<<<<<< HEAD
	DECLARE_WRITE_LINE_MEMBER( bml3_mc6843_intrq_w );

protected:
	virtual void device_start();
	virtual void device_reset();
=======
protected:
	virtual void device_start() override;
	virtual void device_reset() override;

	// optional information overrides
	virtual void device_add_mconfig(machine_config &config) override;
	virtual const tiny_rom_entry *device_rom_region() const override;
>>>>>>> upstream/master

	required_device<mc6843_device> m_mc6843;

private:
<<<<<<< HEAD
	UINT8 *m_rom;
};

// device type definition
extern const device_type BML3BUS_MP1805;

#endif /* __BML3BUS_MP1805__ */
=======
	DECLARE_WRITE_LINE_MEMBER( bml3_mc6843_intrq_w );

	uint8_t *m_rom;
};

// device type definition
DECLARE_DEVICE_TYPE(BML3BUS_MP1805, bml3bus_mp1805_device)

#endif // MAME_BUS_BML3_BML3MP1805_H
>>>>>>> upstream/master
