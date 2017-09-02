// license:BSD-3-Clause
// copyright-holders:Curt Coder
/**********************************************************************

    Wang PC-PM001 Winchester Disk Controller emulation

**********************************************************************/

<<<<<<< HEAD
#pragma once

#ifndef __WANGPC_WDC__
#define __WANGPC_WDC__

#include "emu.h"
=======
#ifndef MAME_BUS_WANGPC_WDC_H
#define MAME_BUS_WANGPC_WDC_H

#pragma once

>>>>>>> upstream/master
#include "wangpc.h"
#include "cpu/z80/z80.h"
#include "imagedev/harddriv.h"
#include "machine/z80ctc.h"



//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

// ======================> wangpc_wdc_device

class wangpc_wdc_device : public device_t,
							public device_wangpcbus_card_interface
{
public:
	// construction/destruction
<<<<<<< HEAD
	wangpc_wdc_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// optional information overrides
	virtual const rom_entry *device_rom_region() const;
	virtual machine_config_constructor device_mconfig_additions() const;
=======
	wangpc_wdc_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
>>>>>>> upstream/master

	// not really public
	DECLARE_READ8_MEMBER( port_r );
	DECLARE_WRITE8_MEMBER( status_w );
	DECLARE_READ8_MEMBER( ctc_ch0_r );
	DECLARE_WRITE8_MEMBER( ctc_ch0_w );
	DECLARE_READ8_MEMBER( ctc_ch1_r );
	DECLARE_WRITE8_MEMBER( ctc_ch1_w );
	DECLARE_READ8_MEMBER( ctc_ch2_r );
	DECLARE_WRITE8_MEMBER( ctc_ch2_w );
	DECLARE_READ8_MEMBER( ctc_ch3_r );
	DECLARE_WRITE8_MEMBER( ctc_ch3_w );

protected:
	// device-level overrides
<<<<<<< HEAD
	virtual void device_start();
	virtual void device_reset();

	// device_wangpcbus_card_interface overrides
	virtual UINT16 wangpcbus_mrdc_r(address_space &space, offs_t offset, UINT16 mem_mask);
	virtual void wangpcbus_amwc_w(address_space &space, offs_t offset, UINT16 mem_mask, UINT16 data);
	virtual UINT16 wangpcbus_iorc_r(address_space &space, offs_t offset, UINT16 mem_mask);
	virtual void wangpcbus_aiowc_w(address_space &space, offs_t offset, UINT16 mem_mask, UINT16 data);
	virtual UINT8 wangpcbus_dack_r(address_space &space, int line);
	virtual void wangpcbus_dack_w(address_space &space, int line, UINT8 data);
	virtual bool wangpcbus_have_dack(int line);
=======
	virtual void device_start() override;
	virtual void device_reset() override;
	virtual const tiny_rom_entry *device_rom_region() const override;
	virtual void device_add_mconfig(machine_config &config) override;

	// device_wangpcbus_card_interface overrides
	virtual uint16_t wangpcbus_mrdc_r(address_space &space, offs_t offset, uint16_t mem_mask) override;
	virtual void wangpcbus_amwc_w(address_space &space, offs_t offset, uint16_t mem_mask, uint16_t data) override;
	virtual uint16_t wangpcbus_iorc_r(address_space &space, offs_t offset, uint16_t mem_mask) override;
	virtual void wangpcbus_aiowc_w(address_space &space, offs_t offset, uint16_t mem_mask, uint16_t data) override;
	virtual uint8_t wangpcbus_dack_r(address_space &space, int line) override;
	virtual void wangpcbus_dack_w(address_space &space, int line, uint8_t data) override;
	virtual bool wangpcbus_have_dack(int line) override;
>>>>>>> upstream/master

private:
	inline void set_irq(int state);

	required_device<cpu_device> m_maincpu;
	required_device<z80ctc_device> m_ctc;

<<<<<<< HEAD
	UINT8 m_status;
	UINT8 m_option;
=======
	uint8_t m_status;
	uint8_t m_option;
>>>>>>> upstream/master
	int m_irq;
};


// device type definition
<<<<<<< HEAD
extern const device_type WANGPC_WDC;


#endif
=======
DECLARE_DEVICE_TYPE(WANGPC_WDC, wangpc_wdc_device)

#endif // MAME_BUS_WANGPC_WDC_H
>>>>>>> upstream/master
