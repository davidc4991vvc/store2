// license:BSD-3-Clause
// copyright-holders:Curt Coder
/**********************************************************************

    Commodore VIC-1111 16K RAM Expansion Cartridge emulation

**********************************************************************/

<<<<<<< HEAD
#pragma once

#ifndef __VIC1111__
#define __VIC1111__

#include "emu.h"
=======
#ifndef MAME_BUS_VIC20_VIC1111_H
#define MAME_BUS_VIC20_VIC1111_H

#pragma once

>>>>>>> upstream/master
#include "exp.h"



//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

// ======================> vic1111_device

class vic1111_device :  public device_t,
						public device_vic20_expansion_card_interface
{
public:
	// construction/destruction
<<<<<<< HEAD
	vic1111_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

protected:
	// device-level overrides
	virtual void device_start();

	// device_vic20_expansion_card_interface overrides
	virtual UINT8 vic20_cd_r(address_space &space, offs_t offset, UINT8 data, int ram1, int ram2, int ram3, int blk1, int blk2, int blk3, int blk5, int io2, int io3);
	virtual void vic20_cd_w(address_space &space, offs_t offset, UINT8 data, int ram1, int ram2, int ram3, int blk1, int blk2, int blk3, int blk5, int io2, int io3);

private:
	optional_shared_ptr<UINT8> m_ram;
=======
	vic1111_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

protected:
	// device-level overrides
	virtual void device_start() override;

	// device_vic20_expansion_card_interface overrides
	virtual uint8_t vic20_cd_r(address_space &space, offs_t offset, uint8_t data, int ram1, int ram2, int ram3, int blk1, int blk2, int blk3, int blk5, int io2, int io3) override;
	virtual void vic20_cd_w(address_space &space, offs_t offset, uint8_t data, int ram1, int ram2, int ram3, int blk1, int blk2, int blk3, int blk5, int io2, int io3) override;

private:
	optional_shared_ptr<uint8_t> m_ram;
>>>>>>> upstream/master
};


// device type definition
<<<<<<< HEAD
extern const device_type VIC1111;



#endif
=======
DECLARE_DEVICE_TYPE(VIC1111, vic1111_device)

#endif // MAME_BUS_VIC20_VIC1111_H
>>>>>>> upstream/master
