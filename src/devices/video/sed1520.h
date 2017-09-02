// license:BSD-3-Clause
// copyright-holders:Sandro Ronco
/***************************************************************************

        SED1520 LCD controller

***************************************************************************/

<<<<<<< HEAD
#pragma once

#ifndef __SED1520_H__
#define __SED1520_H__
=======
#ifndef MAME_VIDEO_SED1520_H
#define MAME_VIDEO_SED1520_H

#pragma once
>>>>>>> upstream/master


#define MCFG_SED1520_ADD( _tag, _cb ) \
	MCFG_DEVICE_ADD( _tag, SED1520, 0 ) \
	sed1520_device::static_set_screen_update_cb(*device, _cb);

//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

<<<<<<< HEAD
typedef UINT32 (*sed1520_screen_update_func)(device_t &device, bitmap_ind16 &bitmap, const rectangle &cliprect, UINT8 *vram, int start_line, int adc);
#define SED1520_UPDATE_CB(name) UINT32 name(device_t &device, bitmap_ind16 &bitmap, const rectangle &cliprect, UINT8 *vram, int start_line, int adc)
=======
#define SED1520_UPDATE_CB(name) uint32_t name(device_t &device, bitmap_ind16 &bitmap, const rectangle &cliprect, uint8_t *vram, int start_line, int adc)
>>>>>>> upstream/master


// ======================> sed1520_device

class sed1520_device :  public device_t
{
public:
<<<<<<< HEAD
	// construction/destruction
	sed1520_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// static configuration helpers
	static void static_set_screen_update_cb(device_t &device, sed1520_screen_update_func _cb) { downcast<sed1520_device &>(device).m_screen_update_func = _cb; }
=======
	typedef uint32_t (*screen_update_func)(device_t &device, bitmap_ind16 &bitmap, const rectangle &cliprect, uint8_t *vram, int start_line, int adc);

	// construction/destruction
	sed1520_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// static configuration helpers
	static void static_set_screen_update_cb(device_t &device, screen_update_func _cb) { downcast<sed1520_device &>(device).m_screen_update_func = _cb; }
>>>>>>> upstream/master

	// device interface
	virtual DECLARE_WRITE8_MEMBER(write);
	virtual DECLARE_READ8_MEMBER(read);
	virtual DECLARE_WRITE8_MEMBER(control_write);
	virtual DECLARE_READ8_MEMBER(status_read);
	virtual DECLARE_WRITE8_MEMBER(data_write);
	virtual DECLARE_READ8_MEMBER(data_read);
<<<<<<< HEAD
	UINT32 screen_update(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);

protected:
	// device-level overrides
	virtual void device_start();
	virtual void device_reset();

private:
	// internal state
	UINT8       m_lcd_on;
	UINT8       m_busy;
	UINT8       m_page;
	UINT8       m_column;
	UINT8       m_old_column;
	UINT8       m_start_line;
	UINT8       m_adc;
	UINT8       m_static_drive;
	bool        m_modify_write;
	sed1520_screen_update_func m_screen_update_func;

	UINT8       m_vram[0x140];
=======
	uint32_t screen_update(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);

protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;

private:
	// internal state
	uint8_t       m_lcd_on;
	uint8_t       m_busy;
	uint8_t       m_page;
	uint8_t       m_column;
	uint8_t       m_old_column;
	uint8_t       m_start_line;
	uint8_t       m_adc;
	uint8_t       m_static_drive;
	bool        m_modify_write;
	screen_update_func m_screen_update_func;

	uint8_t       m_vram[0x140];
>>>>>>> upstream/master
};


// device type definition
<<<<<<< HEAD
extern const device_type SED1520;

#endif
=======
DECLARE_DEVICE_TYPE(SED1520, sed1520_device)

#endif // MAME_VIDEO_SED1520_H
>>>>>>> upstream/master
