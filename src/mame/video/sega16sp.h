// license:BSD-3-Clause
// copyright-holders:Aaron Giles
/***************************************************************************

    Sega 16-bit sprite hardware

***************************************************************************/
<<<<<<< HEAD

#pragma once

#include "sprite.h"
#include "segaic16.h"

#ifndef __SEGA16SP_H__
#define __SEGA16SP_H__
=======
#ifndef MAME_VIDEO_SEGA16SP_H
#define MAME_VIDEO_SEGA16SP_H

#pragma once

#include "video/sprite.h"
#include "segaic16.h"

>>>>>>> upstream/master


//**************************************************************************
//  INTERFACE CONFIGURATION MACROS
//**************************************************************************

#define MCFG_SEGA_HANGON_SPRITES_ADD(_tag) \
	MCFG_DEVICE_ADD(_tag, SEGA_HANGON_SPRITES, 0)
#define MCFG_SEGA_SHARRIER_SPRITES_ADD(_tag) \
	MCFG_DEVICE_ADD(_tag, SEGA_SHARRIER_SPRITES, 0)
#define MCFG_SEGA_OUTRUN_SPRITES_ADD(_tag) \
	MCFG_DEVICE_ADD(_tag, SEGA_OUTRUN_SPRITES, 0)
#define MCFG_SEGA_SYS16A_SPRITES_ADD(_tag) \
	MCFG_DEVICE_ADD(_tag, SEGA_SYS16A_SPRITES, 0)
#define MCFG_SEGA_SYS16B_SPRITES_ADD(_tag) \
	MCFG_DEVICE_ADD(_tag, SEGA_SYS16B_SPRITES, 0)
#define MCFG_SEGA_XBOARD_SPRITES_ADD(_tag) \
	MCFG_DEVICE_ADD(_tag, SEGA_XBOARD_SPRITES, 0)
#define MCFG_SEGA_YBOARD_SPRITES_ADD(_tag) \
	MCFG_DEVICE_ADD(_tag, SEGA_YBOARD_SPRITES, 0)

#define MCFG_BOOTLEG_SYS16A_SPRITES_ADD(_tag) \
	MCFG_DEVICE_ADD(_tag, BOOTLEG_SYS16A_SPRITES, 0)
#define MCFG_BOOTLEG_SYS16A_SPRITES_REMAP(_0,_1,_2,_3,_4,_5,_6,_7) \
	bootleg_sys16a_sprite_device::static_set_remap(*device, _0,_1,_2,_3,_4,_5,_6,_7);

#define MCFG_BOOTLEG_SYS16A_SPRITES_XORIGIN(_xorigin) \
<<<<<<< HEAD
	bootleg_sys16a_sprite_device::static_set_xorigin(*device, _xorigin);

#define MCFG_BOOTLEG_SYS16A_SPRITES_YORIGIN(_yorigin) \
	bootleg_sys16a_sprite_device::static_set_yorigin(*device, _yorigin);
=======
	bootleg_sys16a_sprite_device::set_local_originx(*device, _xorigin);

#define MCFG_BOOTLEG_SYS16A_SPRITES_YORIGIN(_yorigin) \
	bootleg_sys16a_sprite_device::set_local_originy(*device, _yorigin);
>>>>>>> upstream/master


#define MCFG_BOOTLEG_SYS16B_SPRITES_ADD(_tag) \
	MCFG_DEVICE_ADD(_tag, SEGA_SYS16B_SPRITES, 0)
#define MCFG_BOOTLEG_SYS16B_SPRITES_XORIGIN(_xorigin) \
<<<<<<< HEAD
	bootleg_sys16a_sprite_device::static_set_xorigin(*device, _xorigin);
=======
	sega_sys16b_sprite_device::set_local_originx(*device, _xorigin);
#define MCFG_BOOTLEG_SYS16B_SPRITES_YORIGIN(_yorigin) \
	sega_sys16b_sprite_device::set_local_originy(*device, _yorigin);
>>>>>>> upstream/master



//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************


// ======================> sega_16bit_sprite_device

class sega_16bit_sprite_device : public sprite16_device_ind16
{
protected:
	// construction/destruction
<<<<<<< HEAD
	sega_16bit_sprite_device(const machine_config &mconfig, device_type type, const char *name, const char *tag, device_t *owner, const char *shortname, const char *source);
=======
	sega_16bit_sprite_device(const machine_config &mconfig, device_type type, const char *tag, device_t *owner);
>>>>>>> upstream/master

public:
	// live configuration
	void set_bank(int banknum, int offset) { m_bank[banknum] = offset; }
	void set_flip(bool flip) { m_flip = flip; }
	void set_local_origin(int x, int y)
	{
		m_xoffs_flipped = m_xoffs = x;
		m_yoffs_flipped = m_yoffs = y;
		set_origin(x, y);
	}

	void set_local_origin(int x, int y, int xf, int yf)
	{
		m_xoffs = x;
		m_yoffs = y;
		m_xoffs_flipped = xf;
		m_yoffs_flipped = yf;
		set_origin(x, y);
	}

<<<<<<< HEAD
=======
	void set_local_originx_(int x)  { m_xoffs_flipped = m_xoffs = x; set_origin(x, m_yoffs); }
	void set_local_originy_(int y) { m_yoffs_flipped = m_yoffs = y; set_origin(m_xoffs, y); }

	static void set_local_originx(device_t &device, int x)
	{
		sega_16bit_sprite_device &dev = downcast<sega_16bit_sprite_device &>(device);
		dev.set_local_originx_(x);
	};

	static void set_local_originy(device_t &device, int y)
	{
		sega_16bit_sprite_device &dev = downcast<sega_16bit_sprite_device &>(device);
		dev.set_local_originy_(y);
	};
>>>>>>> upstream/master

	// write trigger memory handler
	DECLARE_WRITE16_MEMBER( draw_write );

protected:
	// device-level overrides
<<<<<<< HEAD
	virtual void device_start();

	// internal state
	bool                        m_flip;                 // screen flip?
	UINT8                       m_bank[16];             // banking redirection
=======
	virtual void device_start() override;

	// internal state
	bool                        m_flip;                 // screen flip?
	uint8_t                       m_bank[16];             // banking redirection
>>>>>>> upstream/master
	int m_xoffs, m_yoffs;
	int m_xoffs_flipped, m_yoffs_flipped;

};


// ======================> sega_hangon_sprite_device

class sega_hangon_sprite_device : public sega_16bit_sprite_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	sega_hangon_sprite_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

protected:
	// subclass overrides
	virtual void draw(bitmap_ind16 &bitmap, const rectangle &cliprect);
=======
	sega_hangon_sprite_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

protected:
	// subclass overrides
	virtual void draw(bitmap_ind16 &bitmap, const rectangle &cliprect) override;

	// memory regions
	required_region_ptr<uint16_t> m_sprite_region_ptr;
>>>>>>> upstream/master
};


// ======================> sega_sharrier_sprite_device

class sega_sharrier_sprite_device : public sega_16bit_sprite_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	sega_sharrier_sprite_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

protected:
	// subclass overrides
	virtual void draw(bitmap_ind16 &bitmap, const rectangle &cliprect);
=======
	sega_sharrier_sprite_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

protected:
	// subclass overrides
	virtual void draw(bitmap_ind16 &bitmap, const rectangle &cliprect) override;

	// memory regions
	required_region_ptr<uint32_t> m_sprite_region_ptr;
>>>>>>> upstream/master
};


// ======================> sega_outrun_sprite_device

class sega_outrun_sprite_device : public sega_16bit_sprite_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	sega_outrun_sprite_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
protected:
	sega_outrun_sprite_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock, bool xboard_variant, const char *shortname, const char *source);

	// subclass overrides
	virtual void draw(bitmap_ind16 &bitmap, const rectangle &cliprect);

	// configuration
	bool            m_is_xboard;
=======
	sega_outrun_sprite_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
protected:
	sega_outrun_sprite_device(const machine_config &mconfig, device_type type, const char *tag, device_t *owner, uint32_t clock, bool xboard_variant);

protected:
	// subclass overrides
	virtual void draw(bitmap_ind16 &bitmap, const rectangle &cliprect) override;

	// configuration
	bool            m_is_xboard;
	required_region_ptr<uint32_t> m_sprite_region_ptr;
>>>>>>> upstream/master
};

class sega_xboard_sprite_device : public sega_outrun_sprite_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	sega_xboard_sprite_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
=======
	sega_xboard_sprite_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
>>>>>>> upstream/master
};


// ======================> sega_sys16a_sprite_device

class sega_sys16a_sprite_device : public sega_16bit_sprite_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	sega_sys16a_sprite_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

protected:
	// subclass overrides
	virtual void draw(bitmap_ind16 &bitmap, const rectangle &cliprect);
=======
	sega_sys16a_sprite_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

protected:
	// subclass overrides
	virtual void draw(bitmap_ind16 &bitmap, const rectangle &cliprect) override;

	// memory regions
	required_region_ptr<uint16_t> m_sprite_region_ptr;
>>>>>>> upstream/master
};


// ======================> bootleg_sys16a_sprite_device

class bootleg_sys16a_sprite_device : public sega_16bit_sprite_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	bootleg_sys16a_sprite_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// configuration
	static void static_set_remap(device_t &device, UINT8 offs0, UINT8 offs1, UINT8 offs2, UINT8 offs3, UINT8 offs4, UINT8 offs5, UINT8 offs6, UINT8 offs7);

protected:
	// subclass overrides
	virtual void draw(bitmap_ind16 &bitmap, const rectangle &cliprect);

	// internal state
	UINT8       m_addrmap[8];
=======
	bootleg_sys16a_sprite_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// configuration
	static void static_set_remap(device_t &device, uint8_t offs0, uint8_t offs1, uint8_t offs2, uint8_t offs3, uint8_t offs4, uint8_t offs5, uint8_t offs6, uint8_t offs7);

protected:
	// subclass overrides
	virtual void draw(bitmap_ind16 &bitmap, const rectangle &cliprect) override;

	// memory regions
	required_region_ptr<uint16_t> m_sprite_region_ptr;

	// internal state
	uint8_t       m_addrmap[8];
>>>>>>> upstream/master
};


// ======================> sega_sys16b_sprite_device

class sega_sys16b_sprite_device : public sega_16bit_sprite_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	sega_sys16b_sprite_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

protected:
	// subclass overrides
	virtual void draw(bitmap_ind16 &bitmap, const rectangle &cliprect);
=======
	sega_sys16b_sprite_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

protected:
	// subclass overrides
	virtual void draw(bitmap_ind16 &bitmap, const rectangle &cliprect) override;

	// memory regions
	required_region_ptr<uint16_t> m_sprite_region_ptr;
>>>>>>> upstream/master
};


// ======================> sega_yboard_sprite_device

class sega_yboard_sprite_device : public sega_16bit_sprite_device
{
public:
<<<<<<< HEAD
	// construction/destruction
	sega_yboard_sprite_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
=======
	typedef segaic16_video_device::rotate_info rotate_info;

	// construction/destruction
	sega_yboard_sprite_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
>>>>>>> upstream/master
	void set_rotate_ptr(rotate_info* segaic16_rotate) { m_segaic16_rotate = segaic16_rotate; }

protected:
	// subclass overrides
<<<<<<< HEAD
	virtual void draw(bitmap_ind16 &bitmap, const rectangle &cliprect);

	rotate_info*                        m_segaic16_rotate;
=======
	virtual void draw(bitmap_ind16 &bitmap, const rectangle &cliprect) override;

	required_region_ptr<uint64_t>     m_sprite_region_ptr;
	rotate_info*                    m_segaic16_rotate;
>>>>>>> upstream/master
};


// device type definition
<<<<<<< HEAD
extern const device_type SEGA_HANGON_SPRITES;
extern const device_type SEGA_SHARRIER_SPRITES;
extern const device_type SEGA_OUTRUN_SPRITES;
extern const device_type SEGA_SYS16A_SPRITES;
extern const device_type BOOTLEG_SYS16A_SPRITES;
extern const device_type SEGA_SYS16B_SPRITES;
extern const device_type SEGA_XBOARD_SPRITES;
extern const device_type SEGA_YBOARD_SPRITES;


#endif
=======
DECLARE_DEVICE_TYPE(SEGA_HANGON_SPRITES,    sega_hangon_sprite_device)
DECLARE_DEVICE_TYPE(SEGA_SHARRIER_SPRITES,  sega_sharrier_sprite_device)
DECLARE_DEVICE_TYPE(SEGA_OUTRUN_SPRITES,    sega_outrun_sprite_device)
DECLARE_DEVICE_TYPE(SEGA_SYS16A_SPRITES,    sega_sys16a_sprite_device)
DECLARE_DEVICE_TYPE(BOOTLEG_SYS16A_SPRITES, bootleg_sys16a_sprite_device)
DECLARE_DEVICE_TYPE(SEGA_SYS16B_SPRITES,    sega_sys16b_sprite_device)
DECLARE_DEVICE_TYPE(SEGA_XBOARD_SPRITES,    sega_xboard_sprite_device)
DECLARE_DEVICE_TYPE(SEGA_YBOARD_SPRITES,    sega_yboard_sprite_device)


#endif // MAME_VIDEO_SEGA16SP_H
>>>>>>> upstream/master
