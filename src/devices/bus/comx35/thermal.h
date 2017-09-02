// license:BSD-3-Clause
// copyright-holders:Curt Coder
/**********************************************************************

    COMX-35 Thermal Printer Card emulation

**********************************************************************/

<<<<<<< HEAD
#pragma once

#ifndef __COMX_THM__
#define __COMX_THM__

#include "emu.h"
=======
#ifndef MAME_BUS_COMX35_THERMAL_H
#define MAME_BUS_COMX35_THERMAL_H

#pragma once

>>>>>>> upstream/master
#include "exp.h"



//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

// ======================> comx_thm_device

class comx_thm_device : public device_t,
						public device_comx_expansion_card_interface
{
public:
	// construction/destruction
<<<<<<< HEAD
	comx_thm_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// optional information overrides
	virtual const rom_entry *device_rom_region() const;

protected:
	// device-level overrides
	virtual void device_start();
	virtual void device_reset();

	// device_comx_expansion_card_interface overrides
	virtual UINT8 comx_mrd_r(address_space &space, offs_t offset, int *extrom);
	virtual UINT8 comx_io_r(address_space &space, offs_t offset);
	virtual void comx_io_w(address_space &space, offs_t offset, UINT8 data);
=======
	comx_thm_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// optional information overrides
	virtual const tiny_rom_entry *device_rom_region() const override;

protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;

	// device_comx_expansion_card_interface overrides
	virtual uint8_t comx_mrd_r(address_space &space, offs_t offset, int *extrom) override;
	virtual uint8_t comx_io_r(address_space &space, offs_t offset) override;
	virtual void comx_io_w(address_space &space, offs_t offset, uint8_t data) override;
>>>>>>> upstream/master

private:
	required_memory_region m_rom;
};


// device type definition
<<<<<<< HEAD
extern const device_type COMX_THM;


#endif
=======
DECLARE_DEVICE_TYPE(COMX_THM, comx_thm_device)


#endif // MAME_BUS_COMX35_THERMAL_H
>>>>>>> upstream/master
