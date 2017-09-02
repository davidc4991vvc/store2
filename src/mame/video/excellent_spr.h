// license:BSD-3-Clause
// copyright-holders:David Haywood
<<<<<<< HEAD

class excellent_spr_device : public device_t,
						public device_video_interface
{
public:
	excellent_spr_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	void draw_sprites(screen_device &screen, gfxdecode_device *gfxdecode, const rectangle &cliprect);
=======
#ifndef MAME_VIDEO_EXCELLENT_SPR_H
#define MAME_VIDEO_EXCELLENT_SPR_H

#pragma once


class excellent_spr_device : public device_t, public device_video_interface
{
public:
	excellent_spr_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
>>>>>>> upstream/master

	DECLARE_READ8_MEMBER(read);
	DECLARE_WRITE8_MEMBER(write);

	void aquarium_draw_sprites(bitmap_ind16 &bitmap, const rectangle &cliprect, gfxdecode_device *gfxdecode, int y_offs);
	void gcpinbal_draw_sprites(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect, gfxdecode_device *gfxdecode, int y_offs, int priority);

protected:
<<<<<<< HEAD
	UINT8* m_ram;

	virtual void device_start();
	virtual void device_reset();
private:
};

extern const device_type EXCELLENT_SPRITE;
=======
	std::unique_ptr<uint8_t[]> m_ram;

	virtual void device_start() override;
	virtual void device_reset() override;
private:
};

DECLARE_DEVICE_TYPE(EXCELLENT_SPRITE, excellent_spr_device)

#endif // MAME_VIDEO_EXCELLENT_SPR_H
>>>>>>> upstream/master
