// license:BSD-3-Clause
// copyright-holders:Sergey Svishchev
/**********************************************************************

    Poisk-1 ROM cartridge device

**********************************************************************/

<<<<<<< HEAD
#pragma once

#ifndef __P1_ROM__
#define __P1_ROM__

#include "emu.h"
=======
#ifndef MAME_BUS_ISA_P1_ROM_H
#define MAME_BUS_ISA_P1_ROM_H

#pragma once

>>>>>>> upstream/master
#include "isa.h"

//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

class p1_rom_device : public device_t,
	public device_isa8_card_interface
{
public:
	// construction/destruction
<<<<<<< HEAD
	p1_rom_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// optional information overrides
	virtual const rom_entry *device_rom_region() const;

protected:
	// device-level overrides
	virtual void device_start();
	virtual void device_reset();
=======
	p1_rom_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// optional information overrides
	virtual const tiny_rom_entry *device_rom_region() const override;

protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;
>>>>>>> upstream/master
};


// device type definition
extern const device_type P1_ROM;


<<<<<<< HEAD
#endif
=======
#endif // MAME_BUS_ISA_P1_ROM_H
>>>>>>> upstream/master
