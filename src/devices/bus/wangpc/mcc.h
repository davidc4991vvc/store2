// license:BSD-3-Clause
// copyright-holders:Curt Coder
/**********************************************************************

    Wang PC-PM043 Multiport Communications Controller emulation

**********************************************************************/

<<<<<<< HEAD
#pragma once

#ifndef __WANGPC_MCC__
#define __WANGPC_MCC__

#include "emu.h"
=======
#ifndef MAME_BUS_WANGPC_MCC_H
#define MAME_BUS_WANGPC_MCC_H

#pragma once

>>>>>>> upstream/master
#include "wangpc.h"
#include "machine/z80dart.h"



//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

// ======================> wangpc_mcc_device

class wangpc_mcc_device : public device_t,
							public device_wangpcbus_card_interface
{
public:
	// construction/destruction
<<<<<<< HEAD
	wangpc_mcc_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// optional information overrides
	virtual machine_config_constructor device_mconfig_additions() const;

protected:
	// device-level overrides
	virtual void device_start();
	virtual void device_reset();

	// device_wangpcbus_card_interface overrides
	virtual UINT16 wangpcbus_iorc_r(address_space &space, offs_t offset, UINT16 mem_mask);
	virtual void wangpcbus_aiowc_w(address_space &space, offs_t offset, UINT16 mem_mask, UINT16 data);
=======
	wangpc_mcc_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;
	virtual void device_add_mconfig(machine_config &config) override;

	// device_wangpcbus_card_interface overrides
	virtual uint16_t wangpcbus_iorc_r(address_space &space, offs_t offset, uint16_t mem_mask) override;
	virtual void wangpcbus_aiowc_w(address_space &space, offs_t offset, uint16_t mem_mask, uint16_t data) override;
>>>>>>> upstream/master

private:
	inline void set_irq(int state);

	required_device<z80dart_device> m_sio;
	required_device<z80dart_device> m_dart;

<<<<<<< HEAD
	UINT8 m_option;
=======
	uint8_t m_option;
>>>>>>> upstream/master
	int m_irq;
};


// device type definition
<<<<<<< HEAD
extern const device_type WANGPC_MCC;


#endif
=======
DECLARE_DEVICE_TYPE(WANGPC_MCC, wangpc_mcc_device)

#endif // MAME_BUS_WANGPC_MCC_H
>>>>>>> upstream/master
