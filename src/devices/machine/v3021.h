// license:BSD-3-Clause
// copyright-holders:Angelo Salese
/***************************************************************************

    v3021.h

    EM Microelectronic-Marin SA Ultra Low Power 32kHz CMOS RTC (DIP8)

    Serial Real Time Clock

***************************************************************************/

<<<<<<< HEAD
#pragma once

#ifndef __v3021DEV_H__
#define __v3021DEV_H__
=======
#ifndef MAME_MACHINE_V3021_H
#define MAME_MACHINE_V3021_H

#pragma once
>>>>>>> upstream/master



//**************************************************************************
//  INTERFACE CONFIGURATION MACROS
//**************************************************************************

#define MCFG_V3021_ADD(_tag) \
<<<<<<< HEAD
	MCFG_DEVICE_ADD(_tag, v3021, XTAL_32_768kHz)
=======
	MCFG_DEVICE_ADD(_tag, V3021, XTAL_32_768kHz)
>>>>>>> upstream/master

//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

<<<<<<< HEAD
struct rtc_regs_t
{
	UINT8 sec, min, hour, day, wday, month, year;
};


// ======================> v3021_device

class v3021_device :    public device_t
{
public:
	// construction/destruction
	v3021_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
=======
// ======================> v3021_device

class v3021_device : public device_t
{
public:
	// construction/destruction
	v3021_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
>>>>>>> upstream/master

	// I/O operations
	DECLARE_WRITE8_MEMBER( write );
	DECLARE_READ8_MEMBER( read );
<<<<<<< HEAD
	void timer_callback();

protected:
	// device-level overrides
	virtual void device_validity_check(validity_checker &valid) const;
	virtual void device_start();
	virtual void device_reset();

	inline UINT8 rtc_read(UINT8 offset);
	inline void rtc_write(UINT8 offset,UINT8 data);

	static TIMER_CALLBACK( rtc_inc_callback );

	UINT8 m_cal_mask,m_cal_com,m_cal_cnt,m_cal_val;

	rtc_regs_t m_rtc;
=======
	TIMER_CALLBACK_MEMBER(timer_callback);

protected:
	struct rtc_regs_t
	{
		uint8_t sec, min, hour, day, wday, month, year;
	};

	// device-level overrides
	virtual void device_validity_check(validity_checker &valid) const override;
	virtual void device_start() override;
	virtual void device_reset() override;

	uint8_t m_cal_mask,m_cal_com,m_cal_cnt,m_cal_val;

	rtc_regs_t m_rtc;

	emu_timer *m_timer;
>>>>>>> upstream/master
};


// device type definition
<<<<<<< HEAD
extern const device_type v3021;



//**************************************************************************
//  GLOBAL VARIABLES
//**************************************************************************



#endif
=======
DECLARE_DEVICE_TYPE(V3021, v3021_device)

#endif // MAME_MACHINE_V3021_H
>>>>>>> upstream/master
