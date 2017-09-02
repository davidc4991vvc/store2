// license:BSD-3-Clause
// copyright-holders:Curt Coder
/**********************************************************************

    Wang PC Low-Resolution Video Controller emulation

**********************************************************************/

<<<<<<< HEAD
#pragma once

#ifndef __WANGPC_LVC__
#define __WANGPC_LVC__

#include "emu.h"
=======
#ifndef MAME_BUS_WANGPC_LVC_H
#define MAME_BUS_WANGPC_LVC_H

#pragma once

>>>>>>> upstream/master
#include "wangpc.h"
#include "video/mc6845.h"



//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

// ======================> wangpc_lvc_device

class wangpc_lvc_device : public device_t,
							public device_wangpcbus_card_interface
{
public:
	// construction/destruction
<<<<<<< HEAD
	wangpc_lvc_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// optional information overrides
	virtual machine_config_constructor device_mconfig_additions() const;

	// not really public
	MC6845_UPDATE_ROW( crtc_update_row );
	DECLARE_WRITE_LINE_MEMBER( vsync_w );

protected:
	// device-level overrides
	virtual void device_start();
	virtual void device_reset();

	// device_wangpcbus_card_interface overrides
	virtual UINT16 wangpcbus_mrdc_r(address_space &space, offs_t offset, UINT16 mem_mask);
	virtual void wangpcbus_amwc_w(address_space &space, offs_t offset, UINT16 mem_mask, UINT16 data);
	virtual UINT16 wangpcbus_iorc_r(address_space &space, offs_t offset, UINT16 mem_mask);
	virtual void wangpcbus_aiowc_w(address_space &space, offs_t offset, UINT16 mem_mask, UINT16 data);

private:
	inline void set_irq(int state);

	required_device<mc6845_device> m_crtc;
	optional_shared_ptr<UINT16> m_video_ram;

	rgb_t m_palette[16];
	UINT8 m_option;
	UINT16 m_scroll;
=======
	wangpc_lvc_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;
	virtual void device_add_mconfig(machine_config &config) override;

	// device_wangpcbus_card_interface overrides
	virtual uint16_t wangpcbus_mrdc_r(address_space &space, offs_t offset, uint16_t mem_mask) override;
	virtual void wangpcbus_amwc_w(address_space &space, offs_t offset, uint16_t mem_mask, uint16_t data) override;
	virtual uint16_t wangpcbus_iorc_r(address_space &space, offs_t offset, uint16_t mem_mask) override;
	virtual void wangpcbus_aiowc_w(address_space &space, offs_t offset, uint16_t mem_mask, uint16_t data) override;

private:
	MC6845_UPDATE_ROW( crtc_update_row );
	DECLARE_WRITE_LINE_MEMBER( vsync_w );

	inline void set_irq(int state);

	required_device<mc6845_device> m_crtc;
	optional_shared_ptr<uint16_t> m_video_ram;

	rgb_t m_palette[16];
	uint8_t m_option;
	uint16_t m_scroll;
>>>>>>> upstream/master
	int m_irq;
};


// device type definition
<<<<<<< HEAD
extern const device_type WANGPC_LVC;


#endif
=======
DECLARE_DEVICE_TYPE(WANGPC_LVC, wangpc_lvc_device)

#endif // MAME_BUS_WANGPC_LVC_H
>>>>>>> upstream/master
