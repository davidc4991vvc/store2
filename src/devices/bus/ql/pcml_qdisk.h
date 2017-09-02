// license:BSD-3-Clause
// copyright-holders:Curt Coder
/**********************************************************************

    PCML Q+ Disk Interface emulation

**********************************************************************/

<<<<<<< HEAD
#pragma once

#ifndef __PCML_Q_DISK_INTERFACE__
#define __PCML_Q_DISK_INTERFACE__
=======
#ifndef MAME_BUS_QL_PCML_QDISK_H
#define MAME_BUS_QL_PCML_QDISK_H

#pragma once
>>>>>>> upstream/master

#include "exp.h"



//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

<<<<<<< HEAD
// ======================> pcml_q_disk_interface_t

class pcml_q_disk_interface_t : public device_t,
								public device_ql_expansion_card_interface
{
public:
	// construction/destruction
	pcml_q_disk_interface_t(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
	pcml_q_disk_interface_t(const machine_config &mconfig, device_type type, const char *name, const char *tag, device_t *owner, UINT32 clock, const char *shortname, const char *source, int ram_size);

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
extern const device_type PCML_Q_DISK_INTERFACE;



#endif
=======
// ======================> pcml_q_disk_interface_device

class pcml_q_disk_interface_device : public device_t, public device_ql_expansion_card_interface
{
public:
	// construction/destruction
	pcml_q_disk_interface_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

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
DECLARE_DEVICE_TYPE(PCML_Q_DISK_INTERFACE, pcml_q_disk_interface_device)

#endif // MAME_BUS_QL_PCML_QDISK_H
>>>>>>> upstream/master
