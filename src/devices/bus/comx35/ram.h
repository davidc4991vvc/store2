// license:BSD-3-Clause
// copyright-holders:Curt Coder
/**********************************************************************

    COMX-35 RAM Card emulation

**********************************************************************/

<<<<<<< HEAD
#pragma once

#ifndef __COMX_RAM__
#define __COMX_RAM__

#include "emu.h"
=======
#ifndef MAME_BUS_COMX35_RAM_H
#define MAME_BUS_COMX35_RAM_H

#pragma once

>>>>>>> upstream/master
#include "exp.h"



//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

// ======================> comx_ram_device

class comx_ram_device : public device_t,
						public device_comx_expansion_card_interface
{
public:
	// construction/destruction
<<<<<<< HEAD
	comx_ram_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

protected:
	// device-level overrides
	virtual void device_start();
	virtual void device_reset();

	// device_comx_expansion_card_interface overrides
	virtual UINT8 comx_mrd_r(address_space &space, offs_t offset, int *extrom);
	virtual void comx_mwr_w(address_space &space, offs_t offset, UINT8 data);
	virtual void comx_io_w(address_space &space, offs_t offset, UINT8 data);

private:
	optional_shared_ptr<UINT8> m_ram;
=======
	comx_ram_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;

	// device_comx_expansion_card_interface overrides
	virtual uint8_t comx_mrd_r(address_space &space, offs_t offset, int *extrom) override;
	virtual void comx_mwr_w(address_space &space, offs_t offset, uint8_t data) override;
	virtual void comx_io_w(address_space &space, offs_t offset, uint8_t data) override;

private:
	optional_shared_ptr<uint8_t> m_ram;
>>>>>>> upstream/master

	int m_bank;
};


// device type definition
<<<<<<< HEAD
extern const device_type COMX_RAM;


#endif
=======
DECLARE_DEVICE_TYPE(COMX_RAM, comx_ram_device)


#endif // MAME_BUS_COMX35_RAM_H
>>>>>>> upstream/master
