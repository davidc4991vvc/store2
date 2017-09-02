// license:BSD-3-Clause
// copyright-holders:David Haywood
<<<<<<< HEAD
=======
#ifndef MAME_VIDEO_VS920A_H
#define MAME_VIDEO_VS920A_H

#pragma once
>>>>>>> upstream/master


class vs920a_text_tilemap_device : public device_t
{
public:
<<<<<<< HEAD
	vs920a_text_tilemap_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
	static void static_set_gfxdecode_tag(device_t &device, const char *tag);
	static void set_gfx_region(device_t &device, int gfxregion);

	tilemap_t* m_tmap;
	UINT16* m_vram;
	UINT16 m_pal_base;

	TILE_GET_INFO_MEMBER(get_tile_info);
	tilemap_t* get_tilemap();
	void set_pal_base(int m_pal_base);
=======
	static void static_set_gfxdecode_tag(device_t &device, const char *tag);
	static void set_gfx_region(device_t &device, int gfxregion);

	vs920a_text_tilemap_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	void set_pal_base(int pal_base) { m_pal_base = pal_base; }
	void set_transparent_pen(pen_t pen) { m_tmap->set_transparent_pen(pen); }
>>>>>>> upstream/master
	void draw(screen_device &screen, bitmap_ind16& bitmap, const rectangle &cliprect, int priority);

	DECLARE_WRITE16_MEMBER(vram_w);
	DECLARE_READ16_MEMBER(vram_r);

<<<<<<< HEAD

protected:
	virtual void device_start();
	virtual void device_reset();


private:
	UINT8 m_gfx_region;
=======
protected:
	virtual void device_start() override;
	virtual void device_reset() override;

private:
	TILE_GET_INFO_MEMBER(get_tile_info);

	tilemap_t* m_tmap;
	std::unique_ptr<uint16_t[]> m_vram;
	uint16_t m_pal_base;

	uint8_t m_gfx_region;
>>>>>>> upstream/master

	required_device<gfxdecode_device> m_gfxdecode;
};

<<<<<<< HEAD
extern const device_type VS920A;
=======
DECLARE_DEVICE_TYPE(VS920A, vs920a_text_tilemap_device)
>>>>>>> upstream/master


#define MCFG_VS920A_GFX_REGION(_region) \
	vs920a_text_tilemap_device::set_gfx_region(*device, _region);

#define MCFG_VS920A_GFXDECODE(_gfxtag) \
	vs920a_text_tilemap_device::static_set_gfxdecode_tag(*device, "^" _gfxtag);
<<<<<<< HEAD
=======

#endif // MAME_VIDEO_VS920A_H
>>>>>>> upstream/master
