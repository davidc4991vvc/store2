// license:BSD-3-Clause
// copyright-holders:David Haywood

/*** MB60553 **********************************************/
<<<<<<< HEAD
=======
#ifndef MAME_VIDEO_MB60533_H
#define MAME_VIDEO_MB60533_H

#pragma once
>>>>>>> upstream/master


class mb60553_zooming_tilemap_device : public device_t
{
public:
<<<<<<< HEAD
	mb60553_zooming_tilemap_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
	static void static_set_gfxdecode_tag(device_t &device, const char *tag);
	static void set_gfx_region(device_t &device, int gfxregion);

	tilemap_t* m_tmap;
	UINT16* m_vram;
	UINT16 m_regs[8];
	UINT8 m_bank[8];
	UINT16 m_pal_base;
	void reg_written( int num_reg);
	TILE_GET_INFO_MEMBER(get_tile_info);
	void set_pal_base( int m_pal_base);
	void draw( screen_device &screen, bitmap_ind16& bitmap, const rectangle &cliprect, int priority);
	tilemap_t* get_tilemap();

	UINT16* m_lineram;
=======
	static void static_set_gfxdecode_tag(device_t &device, const char *tag);
	static void set_gfx_region(device_t &device, int gfxregion);

	mb60553_zooming_tilemap_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	void set_pal_base(int pal_base) { m_pal_base = pal_base; }
	void set_transparent_pen(pen_t pen) { m_tmap->set_transparent_pen(pen); }
	void draw(screen_device &screen, bitmap_ind16& bitmap, const rectangle &cliprect, int priority);
>>>>>>> upstream/master

	TILEMAP_MAPPER_MEMBER(twc94_scan);

	DECLARE_WRITE16_MEMBER(regs_w);
	DECLARE_WRITE16_MEMBER(vram_w);
	DECLARE_WRITE16_MEMBER(line_w);

	DECLARE_READ16_MEMBER(regs_r);
	DECLARE_READ16_MEMBER(vram_r);
	DECLARE_READ16_MEMBER(line_r);

<<<<<<< HEAD
	void draw_roz_core(screen_device &screen, bitmap_ind16 &destbitmap, const rectangle &cliprect,
		UINT32 startx, UINT32 starty, int incxx, int incxy, int incyx, int incyy, bool wraparound);

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

	void draw_roz_core(screen_device &screen, bitmap_ind16 &destbitmap, const rectangle &cliprect,
		uint32_t startx, uint32_t starty, int incxx, int incxy, int incyx, int incyy, bool wraparound);

	void reg_written(int num_reg);
	TILE_GET_INFO_MEMBER(get_tile_info);

	tilemap_t* m_tmap;
	std::unique_ptr<uint16_t[]> m_vram;
	uint16_t m_regs[8];
	uint8_t m_bank[8];
	uint16_t m_pal_base;

	std::unique_ptr<uint16_t[]> m_lineram;

	uint8_t m_gfx_region;
>>>>>>> upstream/master

	required_device<gfxdecode_device> m_gfxdecode;

};

<<<<<<< HEAD
extern const device_type MB60553;
=======
DECLARE_DEVICE_TYPE(MB60553, mb60553_zooming_tilemap_device)
>>>>>>> upstream/master


#define MCFG_MB60553_GFX_REGION(_region) \
	mb60553_zooming_tilemap_device::set_gfx_region(*device, _region);

#define MCFG_MB60553_GFXDECODE(_gfxtag) \
	mb60553_zooming_tilemap_device::static_set_gfxdecode_tag(*device, "^" _gfxtag);
<<<<<<< HEAD
=======

#endif // MAME_VIDEO_MB60533_H
>>>>>>> upstream/master
