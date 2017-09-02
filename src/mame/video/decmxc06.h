// license:BSD-3-Clause
// copyright-holders:Bryan McPhail, David Haywood
<<<<<<< HEAD
/* MXC06 */


class deco_mxc06_device : public device_t,
								public device_video_interface
{
public:
	deco_mxc06_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// static configuration
	static void static_set_gfxdecode_tag(device_t &device, const char *tag);
	static void static_set_palette_tag(device_t &device, const char *tag);
=======
#ifndef MAME_VIDEO_DECMXC06_H
#define MAME_VIDEO_DECMXC06_H

#pragma once


class deco_mxc06_device : public device_t, public device_video_interface
{
public:
	deco_mxc06_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// static configuration
	static void static_set_gfxdecode_tag(device_t &device, const char *tag);
>>>>>>> upstream/master
	static void set_gfx_region(device_t &device, int region);
	static void set_ram_size(device_t &device, int size)
	{
		deco_mxc06_device &dev = downcast<deco_mxc06_device &>(device);
		dev.m_ramsize = size;
	}


	void set_gfxregion(int region) { m_gfxregion = region; };
<<<<<<< HEAD
	void draw_sprites( bitmap_ind16 &bitmap, const rectangle &cliprect, UINT16* spriteram16, int pri_mask, int pri_val, int col_mask );
	void draw_sprites_bootleg( bitmap_ind16 &bitmap, const rectangle &cliprect, UINT16* spriteram, int pri_mask, int pri_val, int col_mask );
	void set_pri_type( int type ) { m_priority_type = type; }

protected:
	virtual void device_start();
	virtual void device_reset();

	UINT8 m_gfxregion;
=======
	void draw_sprites( bitmap_ind16 &bitmap, const rectangle &cliprect, uint16_t* spriteram16, int pri_mask, int pri_val, int col_mask );
	void draw_sprites_bootleg( bitmap_ind16 &bitmap, const rectangle &cliprect, uint16_t* spriteram, int pri_mask, int pri_val, int col_mask );
	void set_pri_type( int type ) { m_priority_type = type; }

protected:
	virtual void device_start() override;
	virtual void device_reset() override;

	uint8_t m_gfxregion;
>>>>>>> upstream/master
	int m_priority_type; // just so we can support the existing drivers without converting everything to pdrawgfx just yet
	int m_ramsize;

private:
	required_device<gfxdecode_device> m_gfxdecode;
<<<<<<< HEAD
	required_device<palette_device> m_palette;
};

extern const device_type DECO_MXC06;
=======
};

DECLARE_DEVICE_TYPE(DECO_MXC06, deco_mxc06_device)
>>>>>>> upstream/master

#define MCFG_DECO_MXC06_GFXDECODE(_gfxtag) \
	deco_mxc06_device::static_set_gfxdecode_tag(*device, "^" _gfxtag);

<<<<<<< HEAD
#define MCFG_DECO_MXC06_PALETTE(_palette_tag) \
	deco_mxc06_device::static_set_palette_tag(*device, "^" _palette_tag);

#define MCFG_DECO_MXC06_RAMSIZE(_size) \
	deco_mxc06_device::set_ram_size(*device, _size);
=======
#define MCFG_DECO_MXC06_GFX_REGION(_region) \
	deco_mxc06_device::set_gfx_region(*device, _region);

#define MCFG_DECO_MXC06_RAMSIZE(_size) \
	deco_mxc06_device::set_ram_size(*device, _size);

#endif // MAME_VIDEO_DECMXC06_H
>>>>>>> upstream/master
