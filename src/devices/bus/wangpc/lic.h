// license:BSD-3-Clause
// copyright-holders:Curt Coder
/**********************************************************************

    Wang PC-PM070 Local Interconnect option card emulation

**********************************************************************/

<<<<<<< HEAD
#pragma once

#ifndef __WANGPC_LIC__
#define __WANGPC_LIC__

#include "emu.h"
=======
#ifndef MAME_BUS_WANGPC_LIC_H
#define MAME_BUS_WANGPC_LIC_H

#pragma once

>>>>>>> upstream/master
#include "wangpc.h"



//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

// ======================> wangpc_lic_device

class wangpc_lic_device : public device_t,
								public device_wangpcbus_card_interface
{
public:
	// construction/destruction
<<<<<<< HEAD
	wangpc_lic_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// optional information overrides
	virtual const rom_entry *device_rom_region() const;
	virtual machine_config_constructor device_mconfig_additions() const;

protected:
	// device-level overrides
	virtual void device_start();
	virtual void device_reset();

	// device_wangpcbus_card_interface overrides
	virtual UINT16 wangpcbus_mrdc_r(address_space &space, offs_t offset, UINT16 mem_mask);
	virtual void wangpcbus_amwc_w(address_space &space, offs_t offset, UINT16 mem_mask, UINT16 data);
	virtual UINT16 wangpcbus_iorc_r(address_space &space, offs_t offset, UINT16 mem_mask);
	virtual void wangpcbus_aiowc_w(address_space &space, offs_t offset, UINT16 mem_mask, UINT16 data);
=======
	wangpc_lic_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;
	virtual const tiny_rom_entry *device_rom_region() const override;
	virtual void device_add_mconfig(machine_config &config) override;

	// device_wangpcbus_card_interface overrides
	virtual uint16_t wangpcbus_mrdc_r(address_space &space, offs_t offset, uint16_t mem_mask) override;
	virtual void wangpcbus_amwc_w(address_space &space, offs_t offset, uint16_t mem_mask, uint16_t data) override;
	virtual uint16_t wangpcbus_iorc_r(address_space &space, offs_t offset, uint16_t mem_mask) override;
	virtual void wangpcbus_aiowc_w(address_space &space, offs_t offset, uint16_t mem_mask, uint16_t data) override;
>>>>>>> upstream/master
};


// device type definition
<<<<<<< HEAD
extern const device_type WANGPC_LIC;


#endif
=======
DECLARE_DEVICE_TYPE(WANGPC_LIC, wangpc_lic_device)

#endif // MAME_BUS_WANGPC_LIC_H
>>>>>>> upstream/master
