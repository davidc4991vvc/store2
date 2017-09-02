// license:BSD-3-Clause
// copyright-holders:Curt Coder
/**********************************************************************

    Qubbesoft QubIDE emulation

**********************************************************************/

<<<<<<< HEAD
#pragma once

#ifndef __QUBIDE__
#define __QUBIDE__
=======
#ifndef MAME_BUS_QL_QUBIDE_H
#define MAME_BUS_QL_QUBIDE_H

#pragma once
>>>>>>> upstream/master

#include "exp.h"
#include "machine/ataintf.h"



//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

<<<<<<< HEAD
// ======================> qubide_t

class qubide_t : public device_t,
					public device_ql_expansion_card_interface
{
public:
	// construction/destruction
	qubide_t(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
	qubide_t(const machine_config &mconfig, device_type type, const char *name, const char *tag, device_t *owner, UINT32 clock, const char *shortname, const char *source, int ram_size);

	// optional information overrides
	virtual const rom_entry *device_rom_region() const;
	virtual machine_config_constructor device_mconfig_additions() const;
	virtual ioport_constructor device_input_ports() const;

protected:
	// device-level overrides
	virtual void device_start();
	virtual void device_reset();

	// device_ql_expansion_card_interface overrides
	virtual UINT8 read(address_space &space, offs_t offset, UINT8 data);
	virtual void write(address_space &space, offs_t offset, UINT8 data);
=======
// ======================> qubide_device

class qubide_device : public device_t, public device_ql_expansion_card_interface
{
public:
	// construction/destruction
	qubide_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;

	// optional information overrides
	virtual const tiny_rom_entry *device_rom_region() const override;
	virtual void device_add_mconfig(machine_config &config) override;
	virtual ioport_constructor device_input_ports() const override;

	// device_ql_expansion_card_interface overrides
	virtual uint8_t read(address_space &space, offs_t offset, uint8_t data) override;
	virtual void write(address_space &space, offs_t offset, uint8_t data) override;
>>>>>>> upstream/master

private:
	required_device<ata_interface_device> m_ata;
	required_memory_region m_rom;
	required_ioport m_j1_j5;

	offs_t m_base;
<<<<<<< HEAD
	UINT16 m_ata_data;
=======
	uint16_t m_ata_data;
>>>>>>> upstream/master
};



// device type definition
<<<<<<< HEAD
extern const device_type QUBIDE;



#endif
=======
DECLARE_DEVICE_TYPE(QUBIDE, qubide_device)

#endif // MAME_BUS_QL_QUBIDE_H
>>>>>>> upstream/master
