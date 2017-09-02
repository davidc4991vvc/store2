// license:BSD-3-Clause
// copyright-holders:Curt Coder, Phill Harvey-Smith
/**********************************************************************

    Sandy Super Disk emulation

**********************************************************************/

<<<<<<< HEAD
#pragma once

#ifndef __SANDY_SUPER_DISK__
#define __SANDY_SUPER_DISK__
=======
#ifndef MAME_BUS_QL_SANDY_SUPERDISK_H
#define MAME_BUS_QL_SANDY_SUPERDISK_H

#pragma once
>>>>>>> upstream/master

#include "exp.h"
#include "bus/centronics/ctronics.h"
#include "formats/ql_dsk.h"
#include "machine/wd_fdc.h"



//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

// ======================> sandy_super_disk_device

<<<<<<< HEAD
class sandy_super_disk_t : public device_t,
							public device_ql_expansion_card_interface
{
public:
	// construction/destruction
	sandy_super_disk_t(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// optional information overrides
	virtual const rom_entry *device_rom_region() const;
	virtual machine_config_constructor device_mconfig_additions() const;

	WRITE_LINE_MEMBER( busy_w );

	DECLARE_FLOPPY_FORMATS( floppy_formats );

protected:
	// device-level overrides
	virtual void device_start();
	virtual void device_reset();

	// device_ql_expansion_card_interface overrides
	virtual UINT8 read(address_space &space, offs_t offset, UINT8 data);
	virtual void write(address_space &space, offs_t offset, UINT8 data);

private:
	void check_interrupt();

	required_device<wd1772_t> m_fdc;
=======
class sandy_super_disk_device : public device_t, public device_ql_expansion_card_interface
{
public:
	// construction/destruction
	sandy_super_disk_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;

	// optional information overrides
	virtual const tiny_rom_entry *device_rom_region() const override;
	virtual void device_add_mconfig(machine_config &config) override;

	// device_ql_expansion_card_interface overrides
	virtual uint8_t read(address_space &space, offs_t offset, uint8_t data) override;
	virtual void write(address_space &space, offs_t offset, uint8_t data) override;

private:
	WRITE_LINE_MEMBER( busy_w );

	DECLARE_FLOPPY_FORMATS( floppy_formats );

	void check_interrupt();

	required_device<wd1772_device> m_fdc;
>>>>>>> upstream/master
	required_device<floppy_connector> m_floppy0;
	required_device<floppy_connector> m_floppy1;
	required_device<centronics_device> m_centronics;
	required_device<output_latch_device> m_latch;
	required_memory_region m_rom;

	int m_busy;
	int m_fd6;
};


// device type definition
<<<<<<< HEAD
extern const device_type SANDY_SUPER_DISK;


#endif
=======
DECLARE_DEVICE_TYPE(SANDY_SUPER_DISK, sandy_super_disk_device)


#endif // MAME_BUS_QL_SANDY_SUPERDISK_H
>>>>>>> upstream/master
