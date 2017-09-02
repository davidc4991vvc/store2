// license:BSD-3-Clause
// copyright-holders:Sergey Svishchev
/**********************************************************************

    MC-1502 ROM cartridge device

**********************************************************************/

<<<<<<< HEAD
#pragma once

#ifndef __MC1502_ROM__
#define __MC1502_ROM__

#include "emu.h"
=======
#ifndef MAME_BUS_ISA_MC1502_ROM_H
#define MAME_BUS_ISA_MC1502_ROM_H

#pragma once

>>>>>>> upstream/master
#include "isa.h"

//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

class mc1502_rom_device : public device_t,
	public device_isa8_card_interface
{
public:
	// construction/destruction
<<<<<<< HEAD
	mc1502_rom_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// optional information overrides
	virtual const rom_entry *device_rom_region() const;

protected:
	// device-level overrides
	virtual void device_start();
	virtual void device_reset();
=======
	mc1502_rom_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// optional information overrides
	virtual const tiny_rom_entry *device_rom_region() const override;

protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;
>>>>>>> upstream/master
};


// device type definition
<<<<<<< HEAD
extern const device_type MC1502_ROM;


#endif
=======
DECLARE_DEVICE_TYPE(MC1502_ROM, mc1502_rom_device)


#endif // MAME_BUS_ISA_MC1502_ROM_H
>>>>>>> upstream/master
