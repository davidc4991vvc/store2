// license:BSD-3-Clause
// copyright-holders:Bryan McPhail,David Haywood
<<<<<<< HEAD
=======
#ifndef MAME_VIDEO_DECKARN_H
#define MAME_VIDEO_DECKARN_H

#pragma once
>>>>>>> upstream/master


class deco_karnovsprites_device : public device_t
{
public:
<<<<<<< HEAD
	deco_karnovsprites_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
	void set_gfxregion(int region) { m_gfxregion = region; };
	void draw_sprites( bitmap_ind16 &bitmap, const rectangle &cliprect, UINT16* spriteram, int size, int priority );

	// static configuration
	static void static_set_gfxdecode_tag(device_t &device, const char *tag);
	static void static_set_palette_tag(device_t &device, const char *tag);
	static void set_gfx_region(device_t &device, int region);

protected:
	virtual void device_start();
	virtual void device_reset();

	UINT8 m_gfxregion;
private:
	required_device<gfxdecode_device> m_gfxdecode;
	required_device<palette_device> m_palette;
};

extern const device_type DECO_KARNOVSPRITES;
=======
	deco_karnovsprites_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
	void set_gfxregion(int region) { m_gfxregion = region; };
	void draw_sprites( bitmap_ind16 &bitmap, const rectangle &cliprect, uint16_t* spriteram, int size, int priority );

	// static configuration
	static void static_set_gfxdecode_tag(device_t &device, const char *tag);
	static void set_gfx_region(device_t &device, int region);

protected:
	virtual void device_start() override;
	virtual void device_reset() override;

	uint8_t m_gfxregion;
private:
	required_device<gfxdecode_device> m_gfxdecode;
};

DECLARE_DEVICE_TYPE(DECO_KARNOVSPRITES, deco_karnovsprites_device)
>>>>>>> upstream/master

#define MCFG_DECO_KARNOVSPRITES_GFXDECODE(_gfxtag) \
	deco_karnovsprites_device::static_set_gfxdecode_tag(*device, "^" _gfxtag);

<<<<<<< HEAD
#define MCFG_DECO_KARNOVSPRITES_PALETTE(_palette_tag) \
	deco_karnovsprites_device::static_set_palette_tag(*device, "^" _palette_tag);
=======
#define MCFG_DECO_KARNOVSPRITES_GFX_REGION(_region) \
	deco_karnovsprites_device::set_gfx_region(*device, _region);

#endif // MAME_VIDEO_DECKARN_H
>>>>>>> upstream/master
