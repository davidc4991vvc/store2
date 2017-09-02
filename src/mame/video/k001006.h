// license:BSD-3-Clause
// copyright-holders:David Haywood
<<<<<<< HEAD
#pragma once
#ifndef __K001006_H__
#define __K001006_H__
=======
#ifndef MAME_VIDEO_K001006_H
#define MAME_VIDEO_K001006_H

#pragma once
>>>>>>> upstream/master



class k001006_device : public device_t
{
public:
<<<<<<< HEAD
	k001006_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
=======
	k001006_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
>>>>>>> upstream/master
	~k001006_device() {}

	// static configuration
	static void set_gfx_region(device_t &device, const char *tag) { downcast<k001006_device &>(device).m_gfx_region = tag; }
	static void set_tex_layout(device_t &device, int layout) { downcast<k001006_device &>(device).m_tex_layout = layout; }

<<<<<<< HEAD
	UINT32 fetch_texel(int page, int pal_index, int u, int v);
	void preprocess_texture_data(UINT8 *dst, UINT8 *src, int length, int gticlub);
=======
	uint32_t fetch_texel(int page, int pal_index, int u, int v);
	void preprocess_texture_data(uint8_t *dst, uint8_t *src, int length, int gticlub);
>>>>>>> upstream/master

	DECLARE_READ32_MEMBER( read );
	DECLARE_WRITE32_MEMBER( write );

protected:
	// device-level overrides
<<<<<<< HEAD
	virtual void device_config_complete();
	virtual void device_start();
	virtual void device_reset();

private:
	// internal state
	UINT16 *     m_pal_ram;
	UINT16 *     m_unknown_ram;
	UINT32       m_addr;
	int          m_device_sel;

	UINT8 *      m_texrom;

	UINT32 *     m_palette;

	const char * m_gfx_region;
	UINT8 *      m_gfxrom;
=======
	virtual void device_start() override;
	virtual void device_reset() override;

private:
	// internal state
	std::unique_ptr<uint16_t[]>      m_pal_ram;
	std::unique_ptr<uint16_t[]>     m_unknown_ram;
	uint32_t       m_addr;
	int          m_device_sel;

	std::unique_ptr<uint8_t[]>     m_texrom;

	std::unique_ptr<uint32_t[]>     m_palette;

	const char * m_gfx_region;
	uint8_t *      m_gfxrom;
>>>>>>> upstream/master
	//int m_tex_width;
	//int m_tex_height;
	//int m_tex_mirror_x;
	//int m_tex_mirror_y;
	int m_tex_layout;
};


extern const device_type K001006;
<<<<<<< HEAD
=======
DECLARE_DEVICE_TYPE(K001006, k001006_device)
>>>>>>> upstream/master


#define MCFG_K001006_GFX_REGION(_tag) \
	k001006_device::set_gfx_region(*device, _tag);

#define MCFG_K001006_TEX_LAYOUT(x) \
	k001006_device::set_tex_layout(*device, x);

<<<<<<< HEAD
#endif
=======
#endif // MAME_VIDEO_K001006_H
>>>>>>> upstream/master
