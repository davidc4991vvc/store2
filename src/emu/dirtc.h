// license:BSD-3-Clause
// copyright-holders:Curt Coder
/***************************************************************************

    dirtc.h

    Device Real Time Clock interfaces.

***************************************************************************/

<<<<<<< HEAD
#pragma once

#ifndef __EMU_H__
#error Dont include this file directly; include emu.h instead.
#endif

#ifndef __DIRTC_H__
#define __DIRTC_H__
=======
#ifndef MAME_EMU_DIRTC_H
#define MAME_EMU_DIRTC_H

#pragma once
>>>>>>> upstream/master



//**************************************************************************
//  MACROS / CONSTANTS
//**************************************************************************

// clock registers
enum
{
	RTC_SECOND = 0,
	RTC_MINUTE,
	RTC_HOUR,
	RTC_DAY,
	RTC_MONTH,
	RTC_DAY_OF_WEEK,
	RTC_YEAR
};



//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

// ======================> device_rtc_interface

// class representing interface-specific live rtc
class device_rtc_interface : public device_interface
{
public:
	// construction/destruction
	device_rtc_interface(const machine_config &mconfig, device_t &device);
	virtual ~device_rtc_interface();

	void set_time(bool update, int year, int month, int day, int day_of_week, int hour, int minute, int second);
<<<<<<< HEAD
	void set_current_time(running_machine &machine);

protected:
	static UINT8 convert_to_bcd(int val);
	static int bcd_to_integer(UINT8 val);
=======
	void set_current_time(const system_time &systime);

	bool has_battery() const { return rtc_battery_backed(); }

protected:
	static u8 convert_to_bcd(int val);
	static int bcd_to_integer(u8 val);
>>>>>>> upstream/master

	void set_clock_register(int register, int value);
	int get_clock_register(int register);
	void clock_updated();

	void advance_seconds();
	void advance_minutes();
	void advance_days();
	void adjust_seconds();

	// derived class overrides
<<<<<<< HEAD
	virtual bool rtc_feature_y2k() { return false; }
	virtual bool rtc_feature_leap_year() { return false; }
	virtual void rtc_clock_updated(int year, int month, int day, int day_of_week, int hour, int minute, int second) { }
=======
	virtual bool rtc_feature_y2k() const { return false; }
	virtual bool rtc_feature_leap_year() const { return false; }
	virtual bool rtc_battery_backed() const { return true; }
	virtual void rtc_clock_updated(int year, int month, int day, int day_of_week, int hour, int minute, int second) = 0;
>>>>>>> upstream/master

	int m_register[7];
};

<<<<<<< HEAD

#endif  /* __DIRTC_H__ */
=======
// iterator
typedef device_interface_iterator<device_rtc_interface> rtc_interface_iterator;


#endif // MAME_EMU_DIRTC_H
>>>>>>> upstream/master
