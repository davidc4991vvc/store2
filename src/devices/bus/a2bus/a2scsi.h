// license:BSD-3-Clause
// copyright-holders:R. Belmont
/*********************************************************************

    a2scsi.h

    Implementation of the Apple II SCSI Card

*********************************************************************/

<<<<<<< HEAD
#ifndef __A2BUS_SCSI__
#define __A2BUS_SCSI__

#include "emu.h"
=======
#ifndef MAME_BUS_A2BUS_A2SCSI_H
#define MAME_BUS_A2BUS_A2SCSI_H

#pragma once

>>>>>>> upstream/master
#include "a2bus.h"
#include "machine/ncr5380n.h"

//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

class a2bus_scsi_device:
	public device_t,
	public device_a2bus_card_interface
{
public:
	// construction/destruction
<<<<<<< HEAD
	a2bus_scsi_device(const machine_config &mconfig, device_type type, const char *name, const char *tag, device_t *owner, UINT32 clock, const char *shortname, const char *source);
	a2bus_scsi_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// optional information overrides
	virtual machine_config_constructor device_mconfig_additions() const;
	virtual const rom_entry *device_rom_region() const;

	required_device<ncr5380n_device> m_ncr5380;
	required_device<nscsi_bus_device> m_scsibus;
=======
	a2bus_scsi_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
>>>>>>> upstream/master

	DECLARE_WRITE_LINE_MEMBER( drq_w );

protected:
<<<<<<< HEAD
	virtual void device_start();
	virtual void device_reset();

	// overrides of standard a2bus slot functions
	virtual UINT8 read_c0nx(address_space &space, UINT8 offset);
	virtual void write_c0nx(address_space &space, UINT8 offset, UINT8 data);
	virtual UINT8 read_cnxx(address_space &space, UINT8 offset);
	virtual void write_cnxx(address_space &space, UINT8 offset, UINT8 data);
	virtual UINT8 read_c800(address_space &space, UINT16 offset);
	virtual void write_c800(address_space &space, UINT16 offset, UINT8 data);

private:
	UINT8 *m_rom;
	UINT8 m_ram[8192];  // 8 banks of 1024 bytes
	int m_rambank, m_rombank;
	UINT8 m_drq;
	UINT8 m_bank;
=======
	a2bus_scsi_device(const machine_config &mconfig, device_type type, const char *tag, device_t *owner, uint32_t clock);

	virtual void device_start() override;
	virtual void device_reset() override;
	virtual void device_add_mconfig(machine_config &config) override;
	virtual const tiny_rom_entry *device_rom_region() const override;

	// overrides of standard a2bus slot functions
	virtual uint8_t read_c0nx(address_space &space, uint8_t offset) override;
	virtual void write_c0nx(address_space &space, uint8_t offset, uint8_t data) override;
	virtual uint8_t read_cnxx(address_space &space, uint8_t offset) override;
	virtual void write_cnxx(address_space &space, uint8_t offset, uint8_t data) override;
	virtual uint8_t read_c800(address_space &space, uint16_t offset) override;
	virtual void write_c800(address_space &space, uint16_t offset, uint8_t data) override;

	required_device<ncr5380n_device> m_ncr5380;
	required_device<nscsi_bus_device> m_scsibus;

private:
	uint8_t *m_rom;
	uint8_t m_ram[8192];  // 8 banks of 1024 bytes
	int m_rambank, m_rombank;
	uint8_t m_drq;
	uint8_t m_bank;
>>>>>>> upstream/master
	bool m_816block;
};

// device type definition
<<<<<<< HEAD
extern const device_type A2BUS_SCSI;

#endif /* __A2BUS_SCSI__ */
=======
DECLARE_DEVICE_TYPE(A2BUS_SCSI, a2bus_scsi_device)

#endif // MAME_BUS_A2BUS_A2SCSI_H
>>>>>>> upstream/master
