// license:BSD-3-Clause
// copyright-holders:Angelo Salese, David Haywood
/***************************************************************************

    rtc9701.h

    Serial rtc9701s.

***************************************************************************/

<<<<<<< HEAD
#pragma once

#ifndef __rtc9701DEV_H__
#define __rtc9701DEV_H__
=======
#ifndef MAME_MACHINE_RTC9701_H
#define MAME_MACHINE_RTC9701_H

#pragma once
>>>>>>> upstream/master



//**************************************************************************
//  INTERFACE CONFIGURATION MACROS
//**************************************************************************

<<<<<<< HEAD
#define MCFG_RTC9701_ADD(_tag) \
	MCFG_DEVICE_ADD(_tag, rtc9701, XTAL_32_768kHz)
=======
#define MCFG_RTC9701_ADD(tag) \
		MCFG_DEVICE_ADD((tag), RTC9701, XTAL_32_768kHz)
>>>>>>> upstream/master

//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************


<<<<<<< HEAD
enum rtc9701_state_t
{
	RTC9701_CMD_WAIT = 0,
	RTC9701_RTC_READ,
	RTC9701_RTC_WRITE,
	RTC9701_EEPROM_READ,
	RTC9701_EEPROM_WRITE,
	RTC9701_AFTER_WRITE_ENABLE

};

struct rtc_regs_t
{
	UINT8 sec, min, hour, day, wday, month, year;
};


=======
>>>>>>> upstream/master
// ======================> rtc9701_device

class rtc9701_device :  public device_t,
						public device_nvram_interface
{
public:
	// construction/destruction
<<<<<<< HEAD
	rtc9701_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
=======
	rtc9701_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
>>>>>>> upstream/master


	// I/O operations
	DECLARE_WRITE_LINE_MEMBER( write_bit );
	DECLARE_READ_LINE_MEMBER( read_bit );
	DECLARE_WRITE_LINE_MEMBER( set_cs_line );
	DECLARE_WRITE_LINE_MEMBER( set_clock_line );
<<<<<<< HEAD
	void timer_callback();

protected:
	// device-level overrides
	virtual void device_validity_check(validity_checker &valid) const;
	virtual void device_start();
	virtual void device_reset();

	// device_nvram_interface overrides
	virtual void nvram_default();
	virtual void nvram_read(emu_file &file);
	virtual void nvram_write(emu_file &file);
	inline UINT8 rtc_read(UINT8 offset);
	inline void rtc_write(UINT8 offset,UINT8 data);

	static TIMER_CALLBACK( rtc_inc_callback );
=======
	TIMER_CALLBACK_MEMBER(timer_callback);

protected:
	enum class state_t : u8
	{
		CMD_WAIT = 0,
		RTC_READ,
		RTC_WRITE,
		EEPROM_READ,
		EEPROM_WRITE,
		AFTER_WRITE_ENABLE

	};

	struct regs_t
	{
		uint8_t sec, min, hour, day, wday, month, year;
	};

	// device-level overrides
	virtual void device_validity_check(validity_checker &valid) const override;
	virtual void device_start() override;
	virtual void device_reset() override;

	// device_nvram_interface overrides
	virtual void nvram_default() override;
	virtual void nvram_read(emu_file &file) override;
	virtual void nvram_write(emu_file &file) override;
	inline uint8_t rtc_read(uint8_t offset);
	inline void rtc_write(uint8_t offset,uint8_t data);
>>>>>>> upstream/master

	int                     m_latch;
	int                     m_reset_line;
	int                     m_clock_line;


<<<<<<< HEAD
	rtc9701_state_t rtc_state;
=======
	state_t rtc_state;
>>>>>>> upstream/master
	int cmd_stream_pos;
	int current_cmd;

	int rtc9701_address_pos;
	int rtc9701_current_address;

<<<<<<< HEAD
	UINT16 rtc9701_current_data;
	int rtc9701_data_pos;

	UINT16 rtc9701_data[0x100];

	rtc_regs_t m_rtc;
=======
	uint16_t rtc9701_current_data;
	int rtc9701_data_pos;

	uint16_t rtc9701_data[0x100];

	regs_t m_rtc;

	emu_timer *m_timer;
>>>>>>> upstream/master
};


// device type definition
<<<<<<< HEAD
extern const device_type rtc9701;



//**************************************************************************
//  GLOBAL VARIABLES
//**************************************************************************



#endif
=======
DECLARE_DEVICE_TYPE(RTC9701, rtc9701_device)

#endif // MAME_MACHINE_RTC9701_H
>>>>>>> upstream/master
