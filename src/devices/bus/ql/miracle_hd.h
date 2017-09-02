// license:BSD-3-Clause
// copyright-holders:Curt Coder
/**********************************************************************

    Miracle Hard Disk emulation

**********************************************************************/

<<<<<<< HEAD
#pragma once

#ifndef __MIRACLE_HARD_DISK__
#define __MIRACLE_HARD_DISK__
=======
#ifndef MAME_BUS_QL_MIRACLE_HD
#define MAME_BUS_QL_MIRACLE_HD

#pragma once
>>>>>>> upstream/master

#include "rom.h"



//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

<<<<<<< HEAD
// ======================> miracle_hard_disk_t

class miracle_hard_disk_t : public device_t,
=======
// ======================> miracle_hard_disk_device

class miracle_hard_disk_device : public device_t,
>>>>>>> upstream/master
							public device_ql_rom_cartridge_card_interface
{
public:
	// construction/destruction
<<<<<<< HEAD
	miracle_hard_disk_t(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
	miracle_hard_disk_t(const machine_config &mconfig, device_type type, const char *name, const char *tag, device_t *owner, UINT32 clock, const char *shortname, const char *source, int ram_size);

	// optional information overrides
	virtual const rom_entry *device_rom_region() const;

protected:
	// device-level overrides
	virtual void device_start();

	// device_ql_rom_cartridge_card_interface overrides
	virtual UINT8 read(address_space &space, offs_t offset, UINT8 data);
	virtual void write(address_space &space, offs_t offset, UINT8 data);

private:
};



// device type definition
extern const device_type MIRACLE_HARD_DISK;



#endif
=======
	miracle_hard_disk_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// optional information overrides
	virtual const tiny_rom_entry *device_rom_region() const override;

protected:
	// device-level overrides
	virtual void device_start() override;

	// device_ql_rom_cartridge_card_interface overrides
	virtual uint8_t read(address_space &space, offs_t offset, uint8_t data) override;
	virtual void write(address_space &space, offs_t offset, uint8_t data) override;
};


// device type definition
DECLARE_DEVICE_TYPE(MIRACLE_HARD_DISK, miracle_hard_disk_device)

#endif // MAME_BUS_QL_MIRACLE_HD
>>>>>>> upstream/master
