// license:BSD-3-Clause
// copyright-holders:Angelo Salese
/***************************************************************************

    Generic Palette RAMDAC device

***************************************************************************/

<<<<<<< HEAD
#pragma once

#ifndef __ramdacDEV_H__
#define __ramdacDEV_H__

#include "emu.h"
=======
#ifndef MAME_VIDEO_RAMDAC_H
#define MAME_VIDEO_RAMDAC_H

#pragma once

>>>>>>> upstream/master


//**************************************************************************
//  INTERFACE CONFIGURATION MACROS
//**************************************************************************

#define MCFG_RAMDAC_ADD(_tag, _map, _palette_tag) \
	MCFG_DEVICE_ADD(_tag, RAMDAC, 0) \
<<<<<<< HEAD
	MCFG_DEVICE_ADDRESS_MAP(AS_0, _map) \
	ramdac_device::static_set_palette_tag(*device, "^" _palette_tag);

=======
	MCFG_DEVICE_ADDRESS_MAP(0, _map) \
	ramdac_device::static_set_palette_tag(*device, "^" _palette_tag);

#define MCFG_RAMDAC_COLOR_BASE(_color_base) \
	ramdac_device::static_set_color_base(*device, _color_base);

>>>>>>> upstream/master
#define MCFG_RAMDAC_SPLIT_READ(_split) \
	ramdac_device::set_split_read(*device, _split);


//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

// ======================> ramdac_device

class ramdac_device :   public device_t,
						public device_memory_interface
{
public:
	// construction/destruction
<<<<<<< HEAD
	ramdac_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// static configuration
	static void static_set_palette_tag(device_t &device, const char *tag);
=======
	ramdac_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// static configuration
	static void static_set_palette_tag(device_t &device, const char *tag);
	static void static_set_color_base(device_t &device, uint32_t color_base) { downcast<ramdac_device &>(device).m_color_base = color_base; }
>>>>>>> upstream/master
	static void set_split_read(device_t &device, int split) { downcast<ramdac_device &>(device).m_split_read_reg = split; }

	// I/O operations
	DECLARE_READ8_MEMBER( index_r );
	DECLARE_READ8_MEMBER( pal_r );
<<<<<<< HEAD
=======
	DECLARE_READ8_MEMBER( mask_r );
>>>>>>> upstream/master
	DECLARE_WRITE8_MEMBER( index_w );
	DECLARE_WRITE8_MEMBER( index_r_w );
	DECLARE_WRITE8_MEMBER( pal_w );
	DECLARE_WRITE8_MEMBER( mask_w );

	DECLARE_READ8_MEMBER( ramdac_pal_r );
	DECLARE_WRITE8_MEMBER( ramdac_rgb666_w );
	DECLARE_WRITE8_MEMBER( ramdac_rgb888_w );

<<<<<<< HEAD
	virtual const address_space_config *memory_space_config(address_spacenum spacenum = AS_0) const;

protected:
	// device-level overrides
	virtual void device_validity_check(validity_checker &valid) const;
	virtual void device_start();
	virtual void device_reset();
	inline UINT8 readbyte(offs_t address);
	inline void writebyte(offs_t address, UINT8 data);
	inline void reg_increment(UINT8 inc_type);

private:
	UINT8 m_pal_index[2];
	UINT8 m_pal_mask;
	UINT8 m_int_index[2];
	UINT8 *m_palram;
=======
	virtual space_config_vector memory_space_config() const override;

protected:
	// device-level overrides
	virtual void device_validity_check(validity_checker &valid) const override;
	virtual void device_start() override;
	virtual void device_reset() override;
	inline uint8_t readbyte(offs_t address);
	inline void writebyte(offs_t address, uint8_t data);
	inline void reg_increment(uint8_t inc_type);

private:
	uint8_t m_pal_index[2];
	uint8_t m_pal_mask;
	uint8_t m_int_index[2];
	std::unique_ptr<uint8_t[]> m_palram;
>>>>>>> upstream/master

	const address_space_config      m_space_config;
	required_device<palette_device> m_palette;

<<<<<<< HEAD
	UINT8 m_split_read_reg; // read register index is separated, seen in rltennis
=======
	uint32_t m_color_base;
	uint8_t m_split_read_reg; // read register index is separated, seen in rltennis
>>>>>>> upstream/master
};


// device type definition
<<<<<<< HEAD
extern const device_type RAMDAC;


#endif
=======
DECLARE_DEVICE_TYPE(RAMDAC, ramdac_device)

#endif // MAME_VIDEO_RAMDAC_H
>>>>>>> upstream/master
