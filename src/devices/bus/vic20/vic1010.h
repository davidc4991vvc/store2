// license:BSD-3-Clause
// copyright-holders:Curt Coder
/**********************************************************************

    Commodore VIC-1010 Expansion Module emulation

**********************************************************************/

<<<<<<< HEAD
#pragma once

#ifndef __VIC1010__
#define __VIC1010__

#include "emu.h"
=======
#ifndef MAME_BUS_VIC20_VIC1010_H
#define MAME_BUS_VIC20_VIC1010_H

#pragma once

>>>>>>> upstream/master
#include "exp.h"



//**************************************************************************
<<<<<<< HEAD
//  MACROS/CONSTANTS
//**************************************************************************

#define MAX_SLOTS 6



//**************************************************************************
=======
>>>>>>> upstream/master
//  TYPE DEFINITIONS
//**************************************************************************

// ======================> vic1010_device

class vic1010_device :  public device_t,
						public device_vic20_expansion_card_interface
{
public:
	// construction/destruction
<<<<<<< HEAD
	vic1010_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// optional information overrides
	virtual machine_config_constructor device_mconfig_additions() const;

protected:
	// device-level overrides
	virtual void device_start();
	virtual void device_reset();

	// device_vic20_expansion_card_interface overrides
	virtual UINT8 vic20_cd_r(address_space &space, offs_t offset, UINT8 data, int ram1, int ram2, int ram3, int blk1, int blk2, int blk3, int blk5, int io2, int io3);
	virtual void vic20_cd_w(address_space &space, offs_t offset, UINT8 data, int ram1, int ram2, int ram3, int blk1, int blk2, int blk3, int blk5, int io2, int io3);

private:
	required_device<vic20_expansion_slot_device> m_slot1;
	required_device<vic20_expansion_slot_device> m_slot2;
	required_device<vic20_expansion_slot_device> m_slot3;
	required_device<vic20_expansion_slot_device> m_slot4;
	required_device<vic20_expansion_slot_device> m_slot5;
	required_device<vic20_expansion_slot_device> m_slot6;

	vic20_expansion_slot_device *m_expansion_slot[MAX_SLOTS];
=======
	vic1010_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;

	// optional information overrides
	virtual void device_add_mconfig(machine_config &config) override;

	// device_vic20_expansion_card_interface overrides
	virtual uint8_t vic20_cd_r(address_space &space, offs_t offset, uint8_t data, int ram1, int ram2, int ram3, int blk1, int blk2, int blk3, int blk5, int io2, int io3) override;
	virtual void vic20_cd_w(address_space &space, offs_t offset, uint8_t data, int ram1, int ram2, int ram3, int blk1, int blk2, int blk3, int blk5, int io2, int io3) override;

private:
	static constexpr unsigned MAX_SLOTS = 6;

	required_device_array<vic20_expansion_slot_device, MAX_SLOTS> m_expansion_slot;
>>>>>>> upstream/master
};


// device type definition
<<<<<<< HEAD
extern const device_type VIC1010;



#endif
=======
DECLARE_DEVICE_TYPE(VIC1010, vic1010_device)

#endif // MAME_BUS_VIC20_VIC1010_H
>>>>>>> upstream/master
