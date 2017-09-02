// license:BSD-3-Clause
// copyright-holders:Olivier Galibert
/*
  Sega system24 hardware

*/

<<<<<<< HEAD
#ifndef __SEGAIC24_H
#define __SEGAIC24_H

#define MCFG_S24TILE_DEVICE_ADD(_tag, tile_mask) \
	MCFG_DEVICE_ADD(_tag, S24TILE, 0) \
	segas24_tile::static_set_tile_mask(*device, tile_mask);
=======
#ifndef MAME_VIDEO_SEGAIC24_H
#define MAME_VIDEO_SEGAIC24_H

#pragma once

#define MCFG_S24TILE_DEVICE_ADD(_tag, tile_mask) \
	MCFG_DEVICE_ADD(_tag, S24TILE, 0) \
	segas24_tile_device::static_set_tile_mask(*device, tile_mask);
>>>>>>> upstream/master

#define MCFG_S24SPRITE_DEVICE_ADD(_tag) \
	MCFG_DEVICE_ADD(_tag, S24SPRITE, 0)

#define MCFG_S24MIXER_DEVICE_ADD(_tag) \
	MCFG_DEVICE_ADD(_tag, S24MIXER, 0)


<<<<<<< HEAD
#define MCFG_S24TILE_DEVICE_GFXDECODE(_gfxtag) \
	segas24_tile::static_set_gfxdecode_tag(*device, "^" _gfxtag);

#define MCFG_S24TILE_DEVICE_PALETTE(_palette_tag) \
	segas24_tile::static_set_palette_tag(*device, "^" _palette_tag);

class segas24_tile : public device_t
=======
#define MCFG_S24TILE_DEVICE_PALETTE(_palette_tag) \
	MCFG_GFX_PALETTE(_palette_tag)

class segas24_tile_device : public device_t, public device_gfx_interface
>>>>>>> upstream/master
{
	friend class segas24_tile_config;

public:
<<<<<<< HEAD
	segas24_tile(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// static configuration
	static void static_set_gfxdecode_tag(device_t &device, const char *tag);
	static void static_set_palette_tag(device_t &device, const char *tag);
	static void static_set_tile_mask(device_t &device, UINT16 tile_mask);
=======
	segas24_tile_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// static configuration
	static void static_set_tile_mask(device_t &device, uint16_t tile_mask);
>>>>>>> upstream/master

	DECLARE_READ16_MEMBER(tile_r);
	DECLARE_WRITE16_MEMBER(tile_w);
	DECLARE_READ16_MEMBER(char_r);
	DECLARE_WRITE16_MEMBER(char_w);

	DECLARE_READ32_MEMBER(tile32_r);
	DECLARE_WRITE32_MEMBER(tile32_w);
	DECLARE_READ32_MEMBER(char32_r);
	DECLARE_WRITE32_MEMBER(char32_w);

	void draw(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect, int layer, int pri, int flags);
	void draw(screen_device &screen, bitmap_rgb32 &bitmap, const rectangle &cliprect, int layer, int pri, int flags);

protected:
<<<<<<< HEAD
	virtual void device_start();
=======
	virtual void device_start() override;
>>>>>>> upstream/master

private:
	enum {
		SYS24_TILES = 0x4000
	};

<<<<<<< HEAD
	UINT16 *char_ram, *tile_ram;
	int char_gfx_index;
	tilemap_t *tile_layer[4];
	UINT16 tile_mask;

	static const gfx_layout char_layout;
	required_device<gfxdecode_device> m_gfxdecode;
	required_device<palette_device> m_palette;
=======
	std::unique_ptr<uint16_t[]> char_ram;
	std::unique_ptr<uint16_t[]> tile_ram;
	int char_gfx_index;
	tilemap_t *tile_layer[4];
	uint16_t tile_mask;

	static const gfx_layout char_layout;
>>>>>>> upstream/master

	void tile_info(int offset, tile_data &tileinfo, tilemap_memory_index tile_index);
	TILE_GET_INFO_MEMBER(tile_info_0s);
	TILE_GET_INFO_MEMBER(tile_info_0w);
	TILE_GET_INFO_MEMBER(tile_info_1s);
	TILE_GET_INFO_MEMBER(tile_info_1w);

<<<<<<< HEAD
	void draw_rect(screen_device &screen, bitmap_ind16 &bm, bitmap_ind8 &tm, bitmap_ind16 &dm, const UINT16 *mask,
					UINT16 tpri, UINT8 lpri, int win, int sx, int sy, int xx1, int yy1, int xx2, int yy2);
	void draw_rect(screen_device &screen, bitmap_ind16 &bm, bitmap_ind8 &tm, bitmap_rgb32 &dm, const UINT16 *mask,
					UINT16 tpri, UINT8 lpri, int win, int sx, int sy, int xx1, int yy1, int xx2, int yy2);
=======
	void draw_rect(screen_device &screen, bitmap_ind16 &bm, bitmap_ind8 &tm, bitmap_ind16 &dm, const uint16_t *mask,
					uint16_t tpri, uint8_t lpri, int win, int sx, int sy, int xx1, int yy1, int xx2, int yy2);
	void draw_rect(screen_device &screen, bitmap_ind16 &bm, bitmap_ind8 &tm, bitmap_rgb32 &dm, const uint16_t *mask,
					uint16_t tpri, uint8_t lpri, int win, int sx, int sy, int xx1, int yy1, int xx2, int yy2);
>>>>>>> upstream/master

	template<class _BitmapClass>
	void draw_common(screen_device &screen, _BitmapClass &bitmap, const rectangle &cliprect, int layer, int pri, int flags);
};

<<<<<<< HEAD
class segas24_sprite : public device_t
=======
class segas24_sprite_device : public device_t
>>>>>>> upstream/master
{
	friend class segas24_sprite_config;

public:
<<<<<<< HEAD
	segas24_sprite(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
=======
	segas24_sprite_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
>>>>>>> upstream/master

	DECLARE_READ16_MEMBER(read);
	DECLARE_WRITE16_MEMBER(write);

	void draw(bitmap_ind16 &bitmap, const rectangle &cliprect, bitmap_ind8 &priority_bitmap, const int *spri);

protected:
<<<<<<< HEAD
	virtual void device_start();

private:
	UINT16 *sprite_ram;
};


class segas24_mixer : public device_t
=======
	virtual void device_start() override;

private:
	std::unique_ptr<uint16_t[]> sprite_ram;
};


class segas24_mixer_device : public device_t
>>>>>>> upstream/master
{
	friend class segas24_mixer_config;

public:
<<<<<<< HEAD
	segas24_mixer(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
=======
	segas24_mixer_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
>>>>>>> upstream/master

	DECLARE_READ16_MEMBER(read);
	DECLARE_WRITE16_MEMBER(write);

<<<<<<< HEAD
	UINT16 get_reg(int reg);

protected:
	virtual void device_start();

private:
	UINT16 mixer_reg[16];
};

extern const device_type S24TILE;
extern const device_type S24SPRITE;
extern const device_type S24MIXER;

#endif
=======
	uint16_t get_reg(int reg);

protected:
	virtual void device_start() override;

private:
	uint16_t mixer_reg[16];
};

DECLARE_DEVICE_TYPE(S24TILE,   segas24_tile_device)
DECLARE_DEVICE_TYPE(S24SPRITE, segas24_sprite_device)
DECLARE_DEVICE_TYPE(S24MIXER,  segas24_mixer_device)

#endif // MAME_VIDEO_SEGAIC24_H
>>>>>>> upstream/master
