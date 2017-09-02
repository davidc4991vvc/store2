// license:BSD-3-Clause
// copyright-holders:Curt Coder
/**********************************************************************

    OKI MSM5832 Real Time Clock/Calendar emulation

**********************************************************************
                            _____   _____
                   Vdd   1 |*    \_/     | 18  HOLD
                 WRITE   2 |             | 17  _XT
                  READ   3 |             | 16  XT
                    A0   4 |             | 15  +- 30 ADJ
                    A1   5 |   MSM5832   | 14  TEST
                    A2   6 |             | 13  GND
                    A3   7 |             | 12  D3
                    CS   8 |             | 11  D2
                    D0   9 |_____________| 10  D1

**********************************************************************/

<<<<<<< HEAD
#pragma once

#ifndef __MSM5832__
#define __MSM5832__

#include "emu.h"
=======
#ifndef MAME_MACHINE_MSM5832_H
#define MAME_MACHINE_MSM5832_H

#pragma once

#include "dirtc.h"
>>>>>>> upstream/master



//**************************************************************************
//  INTERFACE CONFIGURATION MACROS
//**************************************************************************

<<<<<<< HEAD
#define MCFG_MSM5832_ADD(_tag, _clock) \
	MCFG_DEVICE_ADD(_tag, MSM5832, _clock)
=======
#define MCFG_MSM5832_ADD(tag, clock) \
		MCFG_DEVICE_ADD((tag), MSM5832, (clock))
>>>>>>> upstream/master



//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

// ======================> msm5832_device

class msm5832_device :  public device_t,
						public device_rtc_interface
{
public:
	// construction/destruction
<<<<<<< HEAD
	msm5832_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
=======
	msm5832_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
>>>>>>> upstream/master

	DECLARE_READ8_MEMBER( data_r );
	DECLARE_WRITE8_MEMBER( data_w );

<<<<<<< HEAD
	void address_w(UINT8 data);
=======
	void address_w(uint8_t data);
>>>>>>> upstream/master

	DECLARE_WRITE_LINE_MEMBER( adj_w );
	DECLARE_WRITE_LINE_MEMBER( test_w );
	DECLARE_WRITE_LINE_MEMBER( hold_w );

	DECLARE_WRITE_LINE_MEMBER( read_w );
	DECLARE_WRITE_LINE_MEMBER( write_w );
	DECLARE_WRITE_LINE_MEMBER( cs_w );

protected:
	// device-level overrides
<<<<<<< HEAD
	virtual void device_start();
	virtual void device_reset();
	virtual void device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr);

	// device_rtc_interface overrides
	virtual void rtc_clock_updated(int year, int month, int day, int day_of_week, int hour, int minute, int second);

private:
	static const device_timer_id TIMER_CLOCK = 0;
=======
	virtual void device_start() override;
	virtual void device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr) override;

	// device_rtc_interface overrides
	virtual void rtc_clock_updated(int year, int month, int day, int day_of_week, int hour, int minute, int second) override;

private:
	static constexpr device_timer_id TIMER_CLOCK = 0;
>>>>>>> upstream/master

	inline int read_counter(int counter);
	inline void write_counter(int counter, int value);

<<<<<<< HEAD
	UINT8 m_reg[13];            // registers

	int m_hold;                 // counter hold
	int m_address;              // address
=======
	uint8_t m_reg[13];            // registers

	int m_hold;                 // counter hold

	uint8_t m_address;              // address
	uint8_t m_data;                 // latched data
>>>>>>> upstream/master

	int m_read;
	int m_write;
	int m_cs;

	// timers
	emu_timer *m_clock_timer;
};


// device type definition
<<<<<<< HEAD
extern const device_type MSM5832;



#endif
=======
DECLARE_DEVICE_TYPE(MSM5832, msm5832_device)

#endif // MAME_MACHINE_MSM5832_H
>>>>>>> upstream/master
