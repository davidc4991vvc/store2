// license:BSD-3-Clause
// copyright-holders:Luca Elia,David Haywood
<<<<<<< HEAD



class st0020_device : public device_t
{
public:
	st0020_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// static configuration
	static void static_set_gfxdecode_tag(device_t &device, const char *tag);
	static void static_set_palette_tag(device_t &device, const char *tag);
	static void set_is_st0032(device_t &device, int is_st0032);
	static void set_is_jclub2o(device_t &device, int is_jclub2o);

	int m_gfx_index;

	// see if we can handle the difference between this and the st0032 in here, or if we need another
	// device
=======
#ifndef MAME_VIDEO_ST0020_H
#define MAME_VIDEO_ST0020_H

#pragma once


class st0020_device : public device_t, public device_gfx_interface
{
public:
	st0020_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// static configuration
	static void static_set_is_st0032(device_t &device, int is_st0032);
	static void static_set_is_jclub2(device_t &device, int is_jclub2);

	void update_screen(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect, bool update_visible_area);

	DECLARE_READ16_MEMBER(gfxram_r);
	DECLARE_WRITE16_MEMBER(gfxram_w);

	DECLARE_READ16_MEMBER(regs_r);
	DECLARE_WRITE16_MEMBER(regs_w);

	DECLARE_READ16_MEMBER(sprram_r);
	DECLARE_WRITE16_MEMBER(sprram_w);

protected:
	virtual void device_start() override;
	virtual void device_reset() override;

private:
	// see if we can handle the difference between this and the st0032 in here, or if we need another device
>>>>>>> upstream/master
	int m_is_st0032;

	// per-game hack
	int m_is_jclub2;

<<<<<<< HEAD
	void st0020_draw_all(bitmap_ind16 &bitmap, const rectangle &cliprect);

	DECLARE_READ16_MEMBER(st0020_gfxram_r);
	DECLARE_WRITE16_MEMBER(st0020_gfxram_w);
	DECLARE_READ16_MEMBER(st0020_blitram_r);
	DECLARE_WRITE16_MEMBER(st0020_blitram_w);
	DECLARE_READ16_MEMBER(st0020_sprram_r);
	DECLARE_WRITE16_MEMBER(st0020_sprram_w);

protected:
	virtual void device_start();
	virtual void device_reset();

private:

	int m_st0020_gfxram_bank;
	UINT16* m_st0020_gfxram;
	UINT16* m_st0020_spriteram;
	UINT16* m_st0020_blitram;
	void st0020_draw_zooming_sprites(bitmap_ind16 &bitmap, const rectangle &cliprect, int priority);
	DECLARE_READ16_MEMBER(st0020_blit_r);
	DECLARE_WRITE16_MEMBER(st0020_blit_w);
	required_device<gfxdecode_device> m_gfxdecode;
	required_device<palette_device> m_palette;
};

#define ST0020_ST0032_BYTESWAP_DATA \
	if (m_is_st0032) data = ((data & 0x00ff)<<8) | ((data & 0xff00)>>8);
#define ST0020_ST0032_BYTESWAP_MEM_MASK \
	if (m_is_st0032) mem_mask = ((mem_mask & 0x00ff)<<8) | ((mem_mask & 0xff00)>>8);
extern const device_type ST0020_SPRITES;

#define MCFG_ST0020_SPRITES_GFXDECODE(_gfxtag) \
	st0020_device::static_set_gfxdecode_tag(*device, "^" _gfxtag);

#define MCFG_ST0020_SPRITES_PALETTE(_palette_tag) \
	st0020_device::static_set_palette_tag(*device, "^" _palette_tag);
=======
	// RAM
	std::unique_ptr<uint16_t[]> m_gfxram;
	std::unique_ptr<uint16_t[]> m_spriteram;
	std::unique_ptr<uint16_t[]> m_regs;

	DECLARE_WRITE16_MEMBER(regs_st0020_w);
	DECLARE_WRITE16_MEMBER(regs_st0032_w);

	int m_gfxram_bank;
	DECLARE_WRITE16_MEMBER(gfxram_bank_w);

	// blitter
	uint8_t *m_rom_ptr;
	size_t m_rom_size;
	DECLARE_WRITE16_MEMBER(do_blit_w);

	// tilemaps
	tilemap_t *m_tmap[4];
	void get_tile_info_i(int i, tilemap_t &tilemap, tile_data &tileinfo, tilemap_memory_index tile_index);

	TILE_GET_INFO_MEMBER(get_tile_info_0);
	TILE_GET_INFO_MEMBER(get_tile_info_1);
	TILE_GET_INFO_MEMBER(get_tile_info_2);
	TILE_GET_INFO_MEMBER(get_tile_info_3);

	int tmap_offset(int i);
	int tmap_priority(int i);
	int tmap_is_enabled(int i);
	DECLARE_WRITE16_MEMBER(tmap_st0020_w);
	DECLARE_WRITE16_MEMBER(tmap_st0032_w);

	// sprites
	void draw_zooming_sprites(bitmap_ind16 &bitmap, const rectangle &cliprect, int priority);
};

DECLARE_DEVICE_TYPE(ST0020_SPRITES, st0020_device)

#define MCFG_ST0020_SPRITES_PALETTE(_palette_tag) \
	MCFG_GFX_PALETTE(_palette_tag)

#endif // MAME_VIDEO_ST0020_H
>>>>>>> upstream/master
