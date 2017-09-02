// license:BSD-3-Clause
// copyright-holders:Sandro Ronco
<<<<<<< HEAD
#pragma once

#ifndef __IQ151_VIDEO64_H__
#define __IQ151_VIDEO64_H__

#include "emu.h"
=======
#ifndef MAME_BUS_IQ151_VIDEO64_H
#define MAME_BUS_IQ151_VIDEO64_H

#pragma once

>>>>>>> upstream/master
#include "iq151.h"

//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

// ======================> iq151_video64_device

class iq151_video64_device :
		public device_t,
<<<<<<< HEAD
=======
		public device_gfx_interface,
>>>>>>> upstream/master
		public device_iq151cart_interface
{
public:
	// construction/destruction
<<<<<<< HEAD
	iq151_video64_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// optional information overrides
	virtual const rom_entry *device_rom_region() const;
	virtual machine_config_constructor device_mconfig_additions() const;

protected:
	// device-level overrides
	virtual void device_start();
	virtual void device_reset();

	// iq151cart_interface overrides
	virtual void read(offs_t offset, UINT8 &data);
	virtual void write(offs_t offset, UINT8 data);
	virtual void io_read(offs_t offset, UINT8 &data);
	virtual void video_update(bitmap_ind16 &bitmap, const rectangle &cliprect);

private:
	UINT8 *     m_videoram;
	UINT8 *     m_chargen;
	required_device<gfxdecode_device> m_gfxdecode;
	required_device<palette_device> m_palette;
=======
	iq151_video64_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// optional information overrides
	virtual const tiny_rom_entry *device_rom_region() const override;

protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;

	// iq151cart_interface overrides
	virtual void read(offs_t offset, uint8_t &data) override;
	virtual void write(offs_t offset, uint8_t data) override;
	virtual void io_read(offs_t offset, uint8_t &data) override;
	virtual void video_update(bitmap_ind16 &bitmap, const rectangle &cliprect) override;

private:
	required_region_ptr<uint8_t> m_videoram;
	required_region_ptr<uint8_t> m_chargen;
>>>>>>> upstream/master
};


// device type definition
<<<<<<< HEAD
extern const device_type IQ151_VIDEO64;

#endif  /* __IQ151_VIDEO64_H__ */
=======
DECLARE_DEVICE_TYPE(IQ151_VIDEO64, iq151_video64_device)

#endif // MAME_BUS_IQ151_VIDEO64_H
>>>>>>> upstream/master
