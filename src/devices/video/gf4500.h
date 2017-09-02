// license:BSD-3-Clause
// copyright-holders:Tim Schuerewegen
/*

    NVIDIA GoForce 4500

    (c) 2010 Tim Schuerewegen

*/

<<<<<<< HEAD
#ifndef __GF4500_H__
#define __GF4500_H__
=======
#ifndef MAME_VIDEO_GF4500_H
#define MAME_VIDEO_GF4500_H

#pragma once
>>>>>>> upstream/master


class gf4500_device : public device_t
{
public:
<<<<<<< HEAD
	gf4500_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
	~gf4500_device() {}
=======
	gf4500_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
>>>>>>> upstream/master


	DECLARE_READ32_MEMBER( read );
	DECLARE_WRITE32_MEMBER( write );

<<<<<<< HEAD
	UINT32 screen_update(screen_device &device, bitmap_rgb32 &bitmap, const rectangle &cliprect);

protected:
	// device-level overrides
	virtual void device_config_complete();
	virtual void device_start();
	virtual void device_reset();
=======
	uint32_t screen_update(screen_device &device, bitmap_rgb32 &bitmap, const rectangle &cliprect);

protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;
>>>>>>> upstream/master

private:
	// internal state

<<<<<<< HEAD
	void vram_write16(UINT16 data);

	UINT32 *m_data;
=======
	void vram_write16(uint16_t data);

	std::unique_ptr<uint32_t[]> m_data;
>>>>>>> upstream/master
	int m_screen_x;
	int m_screen_y;
	int m_screen_x_max;
	int m_screen_y_max;
	int m_screen_x_min;
	int m_screen_y_min;
};



#define MCFG_GF4500_ADD(_tag) \
	MCFG_DEVICE_ADD(_tag, GF4500, 0)


<<<<<<< HEAD
extern const device_type GF4500;


#endif /* __GF4500_H__ */
=======
DECLARE_DEVICE_TYPE(GF4500, gf4500_device)

#endif // MAME_VIDEO_GF4500_H
>>>>>>> upstream/master
