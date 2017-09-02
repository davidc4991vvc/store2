// license:BSD-3-Clause
// copyright-holders:R. Belmont
<<<<<<< HEAD
#pragma once

#ifndef __NUBUS_LVIEW_H__
#define __NUBUS_LVIEW_H__

#include "emu.h"
=======
#ifndef MAME_BUS_NUBUS_PDS30_SIGMALVIEW_H
#define MAME_BUS_NUBUS_PDS30_SIGMALVIEW_H

#pragma once

>>>>>>> upstream/master
#include "nubus.h"

//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

// ======================> nubus_lview_device

class nubus_lview_device :
		public device_t,
		public device_video_interface,
		public device_nubus_card_interface
{
public:
<<<<<<< HEAD
		// construction/destruction
		nubus_lview_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
		nubus_lview_device(const machine_config &mconfig, device_type type, const char *name, const char *tag, device_t *owner, UINT32 clock, const char *shortname, const char *source);

		// optional information overrides
		virtual machine_config_constructor device_mconfig_additions() const;
		virtual const rom_entry *device_rom_region() const;

		UINT32 screen_update(screen_device &screen, bitmap_rgb32 &bitmap, const rectangle &cliprect);
protected:
		// device-level overrides
		virtual void device_start();
		virtual void device_reset();
		virtual void device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr);

		DECLARE_READ32_MEMBER(lview_r);
		DECLARE_WRITE32_MEMBER(lview_w);
		DECLARE_READ32_MEMBER(vram_r);
		DECLARE_WRITE32_MEMBER(vram_w);

public:
		dynamic_buffer m_vram;
		UINT32 *m_vram32;
		UINT32 m_vbl_disable, m_toggle;
		UINT32 m_palette[256];
		emu_timer *m_timer;
		int m_protstate;
		std::string m_assembled_tag;
=======
	// construction/destruction
	nubus_lview_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

protected:
	nubus_lview_device(const machine_config &mconfig, device_type type, const char *tag, device_t *owner, uint32_t clock);

	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;
	virtual void device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr) override;

	// optional information overrides
	virtual void device_add_mconfig(machine_config &config) override;
	virtual const tiny_rom_entry *device_rom_region() const override;

private:
	DECLARE_READ32_MEMBER(lview_r);
	DECLARE_WRITE32_MEMBER(lview_w);
	DECLARE_READ32_MEMBER(vram_r);
	DECLARE_WRITE32_MEMBER(vram_w);

	uint32_t screen_update(screen_device &screen, bitmap_rgb32 &bitmap, const rectangle &cliprect);

	std::vector<uint8_t> m_vram;
	uint32_t *m_vram32;
	uint32_t m_vbl_disable, m_toggle;
	uint32_t m_palette[256];
	emu_timer *m_timer;
	int m_protstate;
	const std::string m_assembled_tag;
>>>>>>> upstream/master
};


// device type definition
<<<<<<< HEAD
extern const device_type PDS030_LVIEW;

#endif  /* __NUBUS_LVIEW_H__ */
=======
DECLARE_DEVICE_TYPE(PDS030_LVIEW, nubus_lview_device)

#endif // MAME_BUS_NUBUS_PDS30_SIGMALVIEW_H
>>>>>>> upstream/master
