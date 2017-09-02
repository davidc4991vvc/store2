// license:BSD-3-Clause
// copyright-holders:Barry Rodewald
/*
 *  Data East Pinball DMD Type 3 Display
 */

<<<<<<< HEAD
#ifndef DECODMD3_H_
#define DECODMD3_H_

#include "emu.h"
#include "cpu/m68000/m68000.h"
#include "video/mc6845.h"
#include "machine/ram.h"
=======
#ifndef MAME_VIDEO_DECODMD3_H
#define MAME_VIDEO_DECODMD3_H

#pragma once

#include "cpu/m68000/m68000.h"
#include "machine/ram.h"
#include "video/mc6845.h"
>>>>>>> upstream/master

#define MCFG_DECODMD_TYPE3_ADD(_tag, _region) \
	MCFG_DEVICE_ADD(_tag, DECODMD3, 0) \
	decodmd_type3_device::static_set_gfxregion(*device, _region);

class decodmd_type3_device : public device_t
{
public:
<<<<<<< HEAD
	decodmd_type3_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
	required_device<cpu_device> m_cpu;
	required_device<mc6845_device> m_mc6845;
	required_device<ram_device> m_ram;
	required_memory_bank m_rambank;
	required_memory_bank m_rombank;
=======
	decodmd_type3_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
>>>>>>> upstream/master

	DECLARE_WRITE8_MEMBER(data_w);
	DECLARE_READ8_MEMBER(busy_r);
	DECLARE_WRITE8_MEMBER(ctrl_w);
	DECLARE_READ16_MEMBER(latch_r);
	DECLARE_READ16_MEMBER(status_r);
	DECLARE_WRITE16_MEMBER(status_w);
	DECLARE_WRITE16_MEMBER(crtc_address_w);
	DECLARE_WRITE16_MEMBER(crtc_register_w);
	DECLARE_READ16_MEMBER(crtc_status_r);
<<<<<<< HEAD
	TIMER_DEVICE_CALLBACK_MEMBER(dmd_irq);
	MC6845_UPDATE_ROW(crtc_update_row);

	static void static_set_gfxregion(device_t &device, const char *tag);

	memory_region* m_rom;

protected:
	virtual machine_config_constructor device_mconfig_additions() const;
	virtual void device_start();
	virtual void device_reset();

private:
	UINT8 m_status;
	UINT8 m_crtc_index;
	UINT8 m_crtc_reg[0x100];
	UINT8 m_latch;
	UINT8 m_ctrl;
	UINT8 m_busy;
	UINT8 m_command;

	const char* m_gfxtag;
};

extern const device_type DECODMD3;


#endif /* DECODMD3_H_ */
=======

	static void static_set_gfxregion(device_t &device, const char *tag);

protected:
	virtual void device_add_mconfig(machine_config &config) override;
	virtual void device_start() override;
	virtual void device_reset() override;

private:
	required_device<cpu_device> m_cpu;
	required_device<mc6845_device> m_mc6845;
	required_device<ram_device> m_ram;
	required_memory_bank m_rambank;
	required_memory_bank m_rombank;

	memory_region* m_rom;

	uint8_t m_status;
	uint8_t m_crtc_index;
	uint8_t m_crtc_reg[0x100];
	uint8_t m_latch;
	uint8_t m_ctrl;
	uint8_t m_busy;
	uint8_t m_command;

	const char* m_gfxtag;

	TIMER_DEVICE_CALLBACK_MEMBER(dmd_irq);
	MC6845_UPDATE_ROW(crtc_update_row);
};

DECLARE_DEVICE_TYPE(DECODMD3, decodmd_type3_device)

#endif // MAME_VIDEO_DECODMD3_H
>>>>>>> upstream/master
