// license:BSD-3-Clause
// copyright-holders:Curt Coder
/**********************************************************************

    Cumana Floppy Disk Interface emulation

**********************************************************************/

<<<<<<< HEAD
#pragma once

#ifndef __CUMANA_FLOPPY_DISK_INTERFACE__
#define __CUMANA_FLOPPY_DISK_INTERFACE__
=======
#ifndef MAME_BUS_QL_CUMANA_FDI_H
#define MAME_BUS_QL_CUMANA_FDI_H

#pragma once
>>>>>>> upstream/master

#include "exp.h"



//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

// ======================> cumana_floppy_disk_interface_t

<<<<<<< HEAD
class cumana_floppy_disk_interface_t : public device_t,
										public device_ql_expansion_card_interface
{
public:
	// construction/destruction
	cumana_floppy_disk_interface_t(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
	cumana_floppy_disk_interface_t(const machine_config &mconfig, device_type type, const char *name, const char *tag, device_t *owner, UINT32 clock, const char *shortname, const char *source, int ram_size);

	// optional information overrides
	virtual const rom_entry *device_rom_region() const;

protected:
	// device-level overrides
	virtual void device_start();

	// device_ql_expansion_card_interface overrides
	virtual UINT8 read(address_space &space, offs_t offset, UINT8 data);
	virtual void write(address_space &space, offs_t offset, UINT8 data);

private:
};



// device type definition
extern const device_type CUMANA_FLOPPY_DISK_INTERFACE;



#endif
=======
class cumana_floppy_disk_interface_device : public device_t, public device_ql_expansion_card_interface
{
public:
	// construction/destruction
	cumana_floppy_disk_interface_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// optional information overrides
	virtual const tiny_rom_entry *device_rom_region() const override;

protected:
	// device-level overrides
	virtual void device_start() override;

	// device_ql_expansion_card_interface overrides
	virtual uint8_t read(address_space &space, offs_t offset, uint8_t data) override;
	virtual void write(address_space &space, offs_t offset, uint8_t data) override;
};


// device type definition
DECLARE_DEVICE_TYPE(CUMANA_FLOPPY_DISK_INTERFACE, cumana_floppy_disk_interface_device)

#endif // MAME_BUS_QL_CUMANA_FDI_H
>>>>>>> upstream/master
