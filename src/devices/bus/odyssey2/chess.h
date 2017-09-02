// license:BSD-3-Clause
// copyright-holders:Fabio Priuli
<<<<<<< HEAD
#ifndef __O2_CHESS_H
#define __O2_CHESS_H
=======
#ifndef MAME_BUS_ODYSSEY2_CHESS_H
#define MAME_BUS_ODYSSEY2_CHESS_H

#pragma once
>>>>>>> upstream/master

#include "slot.h"
#include "rom.h"
#include "cpu/z80/z80.h"


// ======================> o2_chess_device

class o2_chess_device : public o2_rom_device
{
<<<<<<< HEAD
	virtual machine_config_constructor device_mconfig_additions() const;
//  virtual const rom_entry *device_rom_region() const;

public:
	// construction/destruction
	o2_chess_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
=======
public:
	// construction/destruction
	o2_chess_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

protected:
	virtual void device_add_mconfig(machine_config &config) override;
//  virtual const rom_entry *device_rom_region() const;
>>>>>>> upstream/master

private:
	required_device<nsc800_device> m_cpu;
};

<<<<<<< HEAD


// device type definition
extern const device_type O2_ROM_CHESS;


#endif
=======
// device type definition
DECLARE_DEVICE_TYPE(O2_ROM_CHESS, o2_chess_device)

#endif // MAME_BUS_ODYSSEY2_CHESS_H
>>>>>>> upstream/master
