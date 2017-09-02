// license:BSD-3-Clause
// copyright-holders:David Haywood
<<<<<<< HEAD
=======
#ifndef MAME_VIDEO_TIGEROAD_SPR_H
#define MAME_VIDEO_TIGEROAD_SPR_H

#pragma once
>>>>>>> upstream/master

class tigeroad_spr_device : public device_t
{
public:
<<<<<<< HEAD
	tigeroad_spr_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	void draw_sprites(bitmap_ind16 &bitmap, const rectangle &cliprect, gfxdecode_device *gfxdecode, int region, UINT16* ram, UINT32 size, int flip_screen, int rev_y);

protected:

	virtual void device_start();
	virtual void device_reset();
private:
};

extern const device_type TIGEROAD_SPRITE;
=======
	tigeroad_spr_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	void draw_sprites(bitmap_ind16 &bitmap, const rectangle &cliprect, gfxdecode_device *gfxdecode, int region, uint16_t* ram, uint32_t size, int flip_screen, int rev_y);

protected:

	virtual void device_start() override;
	virtual void device_reset() override;
private:
};

DECLARE_DEVICE_TYPE(TIGEROAD_SPRITE, tigeroad_spr_device)

#endif // MAME_VIDEO_TIGEROAD_SPR_H
>>>>>>> upstream/master
