// license:BSD-3-Clause
// copyright-holders: Angelo Salese
/***************************************************************************

    uPD4992 RTC

***************************************************************************/

<<<<<<< HEAD
#pragma once

#ifndef __UPD4992DEV_H__
#define __UPD4992DEV_H__

=======
#ifndef MAME_MACHINE_UPD4992_H
#define MAME_MACHINE_UPD4992_H

#pragma once

#include "dirtc.h"
>>>>>>> upstream/master


//**************************************************************************
//  INTERFACE CONFIGURATION MACROS
//**************************************************************************

<<<<<<< HEAD
#define MCFG_UPD4992_ADD(_tag) \
	MCFG_DEVICE_ADD(_tag, UPD4992, XTAL_32_768kHz)
=======
#define MCFG_UPD4992_ADD(tag) \
		MCFG_DEVICE_ADD((tag), UPD4992, XTAL_32_768kHz)
>>>>>>> upstream/master

//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

// ======================> upd4992_device

<<<<<<< HEAD
class upd4992_device : public device_t,
						public device_rtc_interface
{
public:
	// construction/destruction
	upd4992_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
=======
class upd4992_device : public device_t, public device_rtc_interface
{
public:
	// construction/destruction
	upd4992_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
>>>>>>> upstream/master

	// I/O operations
	DECLARE_WRITE8_MEMBER( write );
	DECLARE_READ8_MEMBER( read );

protected:
	// device-level overrides
<<<<<<< HEAD
	virtual void device_validity_check(validity_checker &valid) const;
	virtual void device_start();
	virtual void device_reset();
	virtual void device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr);
	virtual void rtc_clock_updated(int year, int month, int day, int day_of_week, int hour, int minute, int second);
=======
	virtual void device_validity_check(validity_checker &valid) const override;
	virtual void device_start() override;
	virtual void device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr) override;
	virtual void rtc_clock_updated(int year, int month, int day, int day_of_week, int hour, int minute, int second) override;
>>>>>>> upstream/master

private:
	enum
	{
		TIMER_CLOCK
		//TIMER_TP,
		//TIMER_DATA_OUT,
		//TIMER_TEST_MODE
	};

	emu_timer *m_timer_clock;
<<<<<<< HEAD
	UINT8 m_rtc_regs[8];
=======
	uint8_t m_rtc_regs[8];
>>>>>>> upstream/master
};


// device type definition
extern const device_type UPD4992;
<<<<<<< HEAD



//**************************************************************************
//  GLOBAL VARIABLES
//**************************************************************************



#endif
=======
DECLARE_DEVICE_TYPE(UPD4992, upd4992_device)

#endif // MAME_MACHINE_UPD4992_H
>>>>>>> upstream/master
