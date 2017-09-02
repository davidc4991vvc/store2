// license:BSD-3-Clause
// copyright-holders:R. Belmont
<<<<<<< HEAD
#pragma once

#ifndef __NUBUS_CB264_H__
#define __NUBUS_CB264_H__

#include "emu.h"
=======
#ifndef MAME_BUS_NUBUS_NUBUS_CB264_H
#define MAME_BUS_NUBUS_NUBUS_CB264_H

#pragma once

>>>>>>> upstream/master
#include "nubus.h"

//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

// ======================> nubus_cb264_device

class nubus_cb264_device :
		public device_t,
		public device_nubus_card_interface
{
public:
<<<<<<< HEAD
		// construction/destruction
		nubus_cb264_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
		nubus_cb264_device(const machine_config &mconfig, device_type type, const char *name, const char *tag, device_t *owner, UINT32 clock, const char *shortname, const char *source);

		// optional information overrides
		virtual machine_config_constructor device_mconfig_additions() const;
		virtual const rom_entry *device_rom_region() const;

		UINT32 screen_update(screen_device &screen, bitmap_rgb32 &bitmap, const rectangle &cliprect);
protected:
		// device-level overrides
		virtual void device_start();
		virtual void device_reset();

		DECLARE_READ32_MEMBER(cb264_r);
		DECLARE_WRITE32_MEMBER(cb264_w);
		DECLARE_READ32_MEMBER(cb264_ramdac_r);
		DECLARE_WRITE32_MEMBER(cb264_ramdac_w);

public:
		dynamic_buffer m_vram;
		UINT32 m_cb264_mode, m_cb264_vbl_disable, m_cb264_toggle;
		UINT32 m_palette[256], m_colors[3], m_count, m_clutoffs;
=======
	// construction/destruction
	nubus_cb264_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

protected:
	nubus_cb264_device(const machine_config &mconfig, device_type type, const char *tag, device_t *owner, uint32_t clock);

	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;

	// optional information overrides
	virtual void device_add_mconfig(machine_config &config) override;
	virtual const tiny_rom_entry *device_rom_region() const override;

	DECLARE_READ32_MEMBER(cb264_r);
	DECLARE_WRITE32_MEMBER(cb264_w);
	DECLARE_READ32_MEMBER(cb264_ramdac_r);
	DECLARE_WRITE32_MEMBER(cb264_ramdac_w);

private:
	uint32_t screen_update(screen_device &screen, bitmap_rgb32 &bitmap, const rectangle &cliprect);

	std::vector<uint8_t> m_vram;
	uint32_t m_cb264_mode, m_cb264_vbl_disable, m_cb264_toggle;
	uint32_t m_palette[256], m_colors[3], m_count, m_clutoffs;
>>>>>>> upstream/master
};


// device type definition
<<<<<<< HEAD
extern const device_type NUBUS_CB264;

#endif  /* __NUBUS_CB264_H__ */
=======
DECLARE_DEVICE_TYPE(NUBUS_CB264, nubus_cb264_device)

#endif // MAME_BUS_NUBUS_NUBUS_CB264_H
>>>>>>> upstream/master
