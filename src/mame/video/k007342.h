// license:BSD-3-Clause
// copyright-holders:Fabio Priuli,Acho A. Tang, R. Belmont
<<<<<<< HEAD
#pragma once
#ifndef __K007342_H__
#define __K007342_H__
=======
#ifndef MAME_VIDEO_K007342_H
#define MAME_VIDEO_K007342_H

#pragma once

>>>>>>> upstream/master

typedef device_delegate<void (int layer, int bank, int *code, int *color, int *flags)> k007342_delegate;

class k007342_device : public device_t
{
public:
<<<<<<< HEAD
	k007342_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
	~k007342_device() {}
=======
	k007342_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
>>>>>>> upstream/master

	// static configuration
	static void static_set_gfxdecode_tag(device_t &device, const char *tag);
	static void static_set_gfxnum(device_t &device, int gfxnum) { downcast<k007342_device &>(device).m_gfxnum = gfxnum; }
	static void static_set_callback(device_t &device, k007342_delegate callback) { downcast<k007342_device &>(device).m_callback = callback; }

	DECLARE_READ8_MEMBER( read );
	DECLARE_WRITE8_MEMBER( write );
	DECLARE_READ8_MEMBER( scroll_r );
	DECLARE_WRITE8_MEMBER( scroll_w );
	DECLARE_WRITE8_MEMBER( vreg_w );

	void tilemap_update();
<<<<<<< HEAD
	void tilemap_draw(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect, int num, int flags, UINT32 priority);
=======
	void tilemap_draw(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect, int num, int flags, uint32_t priority);
>>>>>>> upstream/master
	int is_int_enabled();

protected:
	// device-level overrides
<<<<<<< HEAD
	virtual void device_start();
	virtual void device_reset();
private:
	// internal state
	UINT8    *m_ram;
	UINT8    *m_scroll_ram;
	UINT8    *m_videoram_0;
	UINT8    *m_videoram_1;
	UINT8    *m_colorram_0;
	UINT8    *m_colorram_1;

	tilemap_t  *m_tilemap[2];
	int      m_flipscreen, m_int_enabled;
	UINT8    m_regs[8];
	UINT16   m_scrollx[2];
	UINT8    m_scrolly[2];
=======
	virtual void device_start() override;
	virtual void device_reset() override;
private:
	// internal state
	std::unique_ptr<uint8_t[]>    m_ram;
	std::unique_ptr<uint8_t[]>    m_scroll_ram;
	uint8_t    *m_videoram_0;
	uint8_t    *m_videoram_1;
	uint8_t    *m_colorram_0;
	uint8_t    *m_colorram_1;

	tilemap_t  *m_tilemap[2];
	int      m_flipscreen, m_int_enabled;
	uint8_t    m_regs[8];
	uint16_t   m_scrollx[2];
	uint8_t    m_scrolly[2];
>>>>>>> upstream/master
	required_device<gfxdecode_device> m_gfxdecode;
	k007342_delegate m_callback;
	int m_gfxnum;

	TILEMAP_MAPPER_MEMBER(scan);
	TILE_GET_INFO_MEMBER(get_tile_info0);
	TILE_GET_INFO_MEMBER(get_tile_info1);
<<<<<<< HEAD
	void get_tile_info( tile_data &tileinfo, int tile_index, int layer, UINT8 *cram, UINT8 *vram );
};

extern const device_type K007342;
=======
	void get_tile_info( tile_data &tileinfo, int tile_index, int layer, uint8_t *cram, uint8_t *vram );
};

DECLARE_DEVICE_TYPE(K007342, k007342_device)
>>>>>>> upstream/master

#define MCFG_K007342_ADD(_tag) \
	MCFG_DEVICE_ADD(_tag, K007342, 0)
#define MCFG_K007342_GFXDECODE(_gfxtag) \
	k007342_device::static_set_gfxdecode_tag(*device, "^" _gfxtag);

#define MCFG_K007342_GFXNUM(_gfxnum) \
	k007342_device::static_set_gfxnum(*device, _gfxnum);

#define MCFG_K007342_CALLBACK_OWNER(_class, _method) \
	k007342_device::static_set_callback(*device, k007342_delegate(&_class::_method, #_class "::" #_method, downcast<_class *>(owner)));

#define MCFG_K007342_CALLBACK_DEVICE(_tag, _class, _method) \
	k007342_device::static_set_callback(*device, k007342_delegate(&_class::_method, #_class "::" #_method, _tag));

// function definition for a callback
#define K007342_CALLBACK_MEMBER(_name)     void _name(int layer, int bank, int *code, int *color, int *flags)

<<<<<<< HEAD
#endif
=======
#endif // MAME_VIDEO_K007342_H
>>>>>>> upstream/master
