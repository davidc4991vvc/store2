// license:BSD-3-Clause
// copyright-holders:Sandro Ronco
/***************************************************************************

        Toshiba T6A04 LCD controller

***************************************************************************/

<<<<<<< HEAD
#pragma once

#ifndef __T6A04_H__
#define __T6A04_H__
=======
#ifndef MAME_VIDEO_T6A04_H
#define MAME_VIDEO_T6A04_H

#pragma once
>>>>>>> upstream/master

//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

// ======================> t6a04_device

class t6a04_device : public device_t
{
public:
	// construction/destruction
<<<<<<< HEAD
	t6a04_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
=======
	t6a04_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
>>>>>>> upstream/master

	static void set_size(device_t &device, int w, int h)
	{
		t6a04_device &dev = downcast<t6a04_device &>(device);
		dev.m_width = w;
		dev.m_height = h;
	}

	// device interface
	DECLARE_WRITE8_MEMBER(control_write);
	DECLARE_READ8_MEMBER(control_read);
	DECLARE_WRITE8_MEMBER(data_write);
	DECLARE_READ8_MEMBER(data_read);

<<<<<<< HEAD
	UINT32 screen_update(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);

protected:
	// device-level overrides
	virtual void device_start();
	virtual void device_reset();
	virtual void device_validity_check(validity_checker &valid) const;

private:
	UINT8 m_busy_flag;
	UINT8 m_lcd_ram[960];   //7680 bit (64*120)
	UINT8 m_display_on;
	UINT8 m_contrast;
	UINT8 m_xpos;
	UINT8 m_ypos;
	UINT8 m_zpos;
	INT8  m_direction;
	UINT8 m_active_counter;
	UINT8 m_word_len;
	UINT8 m_opa1;
	UINT8 m_opa2;
	UINT8 m_output_reg;

	UINT8 m_height;           // number of lines
	UINT8 m_width;            // pixels for line
};

// device type definition
extern const device_type T6A04;
=======
	uint32_t screen_update(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);

protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;
	virtual void device_validity_check(validity_checker &valid) const override;

private:
	uint8_t m_busy_flag;
	uint8_t m_lcd_ram[960];   //7680 bit (64*120)
	uint8_t m_display_on;
	uint8_t m_contrast;
	uint8_t m_xpos;
	uint8_t m_ypos;
	uint8_t m_zpos;
	int8_t  m_direction;
	uint8_t m_active_counter;
	uint8_t m_word_len;
	uint8_t m_opa1;
	uint8_t m_opa2;
	uint8_t m_output_reg;

	uint8_t m_height;           // number of lines
	uint8_t m_width;            // pixels for line
};

// device type definition
DECLARE_DEVICE_TYPE(T6A04, t6a04_device)
>>>>>>> upstream/master

#define MCFG_T6A04_SIZE(_width, _height) \
	t6a04_device::set_size(*device, _width, _height);

<<<<<<< HEAD
#endif
=======
#endif // MAME_VIDEO_T6A04_H
>>>>>>> upstream/master
