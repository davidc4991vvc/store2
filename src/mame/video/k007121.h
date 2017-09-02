// license:BSD-3-Clause
// copyright-holders:Fabio Priuli,Acho A. Tang, R. Belmont
<<<<<<< HEAD
#pragma once
#ifndef __K007121_H__
#define __K007121_H__
=======
#ifndef MAME_VIDEO_K007121_H
#define MAME_VIDEO_K007121_H

#pragma once

>>>>>>> upstream/master

class k007121_device : public device_t
{
public:
<<<<<<< HEAD
	k007121_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
	~k007121_device() {}
=======
	k007121_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
>>>>>>> upstream/master

	static void static_set_palette_tag(device_t &device, const char *tag);

	DECLARE_READ8_MEMBER( ctrlram_r );
	DECLARE_WRITE8_MEMBER( ctrl_w );

	/* shall we move source in the interface? */
	/* also notice that now we directly pass *gfx[chip] instead of **gfx !! */
<<<<<<< HEAD
	void sprites_draw( bitmap_ind16 &bitmap, const rectangle &cliprect, gfx_element *gfx, palette_device *palette, const UINT8 *source, int base_color, int global_x_offset, int bank_base, bitmap_ind8 &priority_bitmap, UINT32 pri_mask );

protected:
	// device-level overrides
	virtual void device_config_complete();
	virtual void device_start();
	virtual void device_reset();

private:
	// internal state
	UINT8    m_ctrlram[8];
=======
	void sprites_draw( bitmap_ind16 &bitmap, const rectangle &cliprect, gfx_element *gfx, device_palette_interface &palette, const uint8_t *source, int base_color, int global_x_offset, int bank_base, bitmap_ind8 &priority_bitmap, uint32_t pri_mask, bool is_flakatck = false );

protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;

private:
	// internal state
	uint8_t    m_ctrlram[8];
>>>>>>> upstream/master
	int      m_flipscreen;
	required_device<palette_device> m_palette;
};

<<<<<<< HEAD
extern const device_type K007121;
=======
DECLARE_DEVICE_TYPE(K007121, k007121_device)
>>>>>>> upstream/master

#define MCFG_K007121_ADD(_tag) \
	MCFG_DEVICE_ADD(_tag, K007121, 0)

#define MCFG_K007121_PALETTE(_palette_tag) \
	k007121_device::static_set_palette_tag(*device, "^" _palette_tag);

<<<<<<< HEAD
#endif
=======
#endif // MAME_VIDEO_K007121_H
>>>>>>> upstream/master
