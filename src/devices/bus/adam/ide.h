// license:BSD-3-Clause
// copyright-holders:Curt Coder
/**********************************************************************

    Micro Innovations Powermate IDE Hard Disk emulation

**********************************************************************/

<<<<<<< HEAD
#pragma once

#ifndef __ADAM_IDE__
#define __ADAM_IDE__

#include "emu.h"
=======
#ifndef MAME_BUS_ADAM_IDE_H
#define MAME_BUS_ADAM_IDE_H

#pragma once

>>>>>>> upstream/master
#include "exp.h"
#include "machine/ataintf.h"
#include "machine/latch.h"



//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

// ======================> powermate_ide_device

class powermate_ide_device :  public device_t,
	public device_adam_expansion_slot_card_interface
{
public:
	// construction/destruction
<<<<<<< HEAD
	powermate_ide_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// optional information overrides
	virtual const rom_entry *device_rom_region() const;
	virtual machine_config_constructor device_mconfig_additions() const;

protected:
	// device-level overrides
	virtual void device_start();

	// device_adam_expansion_slot_card_interface overrides
	virtual UINT8 adam_bd_r(address_space &space, offs_t offset, UINT8 data, int bmreq, int biorq, int aux_rom_cs, int cas1, int cas2);
	virtual void adam_bd_w(address_space &space, offs_t offset, UINT8 data, int bmreq, int biorq, int aux_rom_cs, int cas1, int cas2);
=======
	powermate_ide_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

protected:
	// device-level overrides
	virtual void device_start() override;

	// optional information overrides
	virtual const tiny_rom_entry *device_rom_region() const override;
	virtual void device_add_mconfig(machine_config &config) override;

	// device_adam_expansion_slot_card_interface overrides
	virtual uint8_t adam_bd_r(address_space &space, offs_t offset, uint8_t data, int bmreq, int biorq, int aux_rom_cs, int cas1, int cas2) override;
	virtual void adam_bd_w(address_space &space, offs_t offset, uint8_t data, int bmreq, int biorq, int aux_rom_cs, int cas1, int cas2) override;
>>>>>>> upstream/master

private:
	required_device<ata_interface_device> m_ata;
	required_device<output_latch_device> m_cent_data_out;

<<<<<<< HEAD
	UINT16 m_ata_data;
=======
	uint16_t m_ata_data;
>>>>>>> upstream/master
};


// device type definition
<<<<<<< HEAD
extern const device_type ADAM_IDE;



#endif
=======
DECLARE_DEVICE_TYPE(ADAM_IDE, powermate_ide_device)

#endif // MAME_BUS_ADAM_IDE_H
>>>>>>> upstream/master
