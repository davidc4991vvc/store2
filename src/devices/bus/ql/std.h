// license:BSD-3-Clause
// copyright-holders:Curt Coder
/**********************************************************************

    Sinclair QL standard ROM cartridge emulation

**********************************************************************/

<<<<<<< HEAD
#pragma once

#ifndef __QL_STANDARD_ROM_CARTRIDGE__
#define __QL_STANDARD_ROM_CARTRIDGE__
=======
#ifndef MAME_BUS_QL_STD_H
#define MAME_BUS_QL_STD_H

#pragma once
>>>>>>> upstream/master

#include "rom.h"



//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

<<<<<<< HEAD
// ======================> ql_standard_rom_cartridge_t

class ql_standard_rom_cartridge_t : public device_t,
									public device_ql_rom_cartridge_card_interface
{
public:
	// construction/destruction
	ql_standard_rom_cartridge_t(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

protected:
	// device-level overrides
	virtual void device_start();

	// device_ql_rom_cartridge_card_interface overrides
	virtual UINT8 read(address_space &space, offs_t offset, UINT8 data);
=======
// ======================> ql_standard_rom_cartridge_device

class ql_standard_rom_cartridge_device : public device_t, public device_ql_rom_cartridge_card_interface
{
public:
	// construction/destruction
	ql_standard_rom_cartridge_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

protected:
	// device-level overrides
	virtual void device_start() override;

	// device_ql_rom_cartridge_card_interface overrides
	virtual uint8_t read(address_space &space, offs_t offset, uint8_t data) override;
>>>>>>> upstream/master
};


// device type definition
<<<<<<< HEAD
extern const device_type QL_STANDARD_ROM_CARTRIDGE;


#endif
=======
DECLARE_DEVICE_TYPE(QL_STANDARD_ROM_CARTRIDGE, ql_standard_rom_cartridge_device)

#endif // MAME_BUS_QL_STD_H
>>>>>>> upstream/master
