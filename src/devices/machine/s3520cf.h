// license:BSD-3-Clause
// copyright-holders:Angelo Salese
/***************************************************************************

Seiko/Epson S-3520CF

***************************************************************************/

<<<<<<< HEAD
#pragma once

#ifndef __S3520CFDEV_H__
#define __S3520CFDEV_H__
=======
#ifndef MAME_MACHINE_S3520CF_H
#define MAME_MACHINE_S3520CF_H

#pragma once
>>>>>>> upstream/master



//**************************************************************************
//  INTERFACE CONFIGURATION MACROS
//**************************************************************************

<<<<<<< HEAD
#define MCFG_S3520CF_ADD(_tag) \
	MCFG_DEVICE_ADD(_tag, S3520CF, XTAL_32_768kHz)
=======
#define MCFG_S3520CF_ADD(tag) \
		MCFG_DEVICE_ADD((tag), S3520CF, XTAL_32_768kHz)
>>>>>>> upstream/master

//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

<<<<<<< HEAD
enum s3520cf_state_t
{
	RTC_SET_ADDRESS = 0,
	RTC_SET_DATA
};

struct rtc_regs_t
{
	UINT8 sec, min, hour, day, wday, month, year;
};


=======
>>>>>>> upstream/master
// ======================> s3520cf_device

class s3520cf_device :  public device_t
{
public:
	// construction/destruction
<<<<<<< HEAD
	s3520cf_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
=======
	s3520cf_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
>>>>>>> upstream/master

	// I/O operations
	DECLARE_READ_LINE_MEMBER( read_bit );
	DECLARE_WRITE_LINE_MEMBER( set_dir_line );
	DECLARE_WRITE_LINE_MEMBER( set_cs_line );
	DECLARE_WRITE_LINE_MEMBER( set_clock_line );
	DECLARE_WRITE_LINE_MEMBER( write_bit );
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
=======
	TIMER_CALLBACK_MEMBER(timer_callback);

protected:
	enum state_t
	{
		RTC_SET_ADDRESS = 0,
		RTC_SET_DATA
	};

	struct rtc_regs_t
	{
		uint8_t sec, min, hour, day, wday, month, year;
	};

	// device-level overrides
	virtual void device_validity_check(validity_checker &valid) const override;
	virtual void device_start() override;
	virtual void device_reset() override;
	inline uint8_t rtc_read(uint8_t offset);
	inline void rtc_write(uint8_t offset,uint8_t data);
>>>>>>> upstream/master

	int m_dir;
	int m_latch;
	int m_reset_line;
	int m_read_latch;
<<<<<<< HEAD
	UINT8 m_current_cmd;
	UINT8 m_cmd_stream_pos;
	UINT8 m_rtc_addr;
	UINT8 m_mode, m_sysr;

	s3520cf_state_t m_rtc_state;
	rtc_regs_t m_rtc;

=======
	uint8_t m_current_cmd;
	uint8_t m_cmd_stream_pos;
	uint8_t m_rtc_addr;
	uint8_t m_mode, m_sysr;

	state_t m_rtc_state;
	rtc_regs_t m_rtc;

	emu_timer *m_timer;
>>>>>>> upstream/master
};


// device type definition
<<<<<<< HEAD
extern const device_type S3520CF;



//**************************************************************************
//  GLOBAL VARIABLES
//**************************************************************************



#endif
=======
DECLARE_DEVICE_TYPE(S3520CF, s3520cf_device)

#endif // MAME_MACHINE_S3520CF_H
>>>>>>> upstream/master
