// license:BSD-3-Clause
// copyright-holders:Nathan Woods
/***************************************************************************

<<<<<<< HEAD
    MSM6242 Real Time Clock

***************************************************************************/

#pragma once

#ifndef __MSM6242DEV_H__
#define __MSM6242DEV_H__

#include "emu.h"
=======
    MSM6242 / RTC-6242x / RTC-7242x Real Time Clock

****************************************************************************
                            _____   _____
                 STD.P   1 |*    \_/     | 18  Vdd
                  /CS0   2 |             | 17  /XT (MSM6242 only)
                   ALE   3 |             | 16  XT  (MSM6242 only)
                    A0   4 |  MSM6242RS  | 15  CS1
                    A1   5 |  RTC62421   | 14  D0
                    A2   6 |  RTC72421   | 13  D1
                    A3   7 |             | 12  D2
                   /RD   8 |             | 11  D3
                   GND   9 |_____________| 10  /WR

                            _____   _____
                 STD.P   1 |*    \_/     | 24  Vdd
                  /CS0   2 |             | 23  /XT (MSM6242 only)
                    NC   3 |             | 22  XT  (MSM6242 only)
                   ALE   4 |             | 21  NC
                    A0   5 |             | 20  CS1
                    NC   6 |  MSM6242GS  | 19  D0
                    A1   7 |  RTC62423   | 18  NC
                    NC   8 |  RTC72423   | 17  NC
                    A2   9 |             | 16  D1
                    A3  10 |             | 15  D2
                   /RD  11 |             | 14  D3
                   GND  12 |_____________| 13  /WR

***************************************************************************/

#ifndef MAME_MACHINE_MSM6242_H
#define MAME_MACHINE_MSM6242_H

#pragma once

#include "dirtc.h"
>>>>>>> upstream/master


#define MCFG_MSM6242_OUT_INT_HANDLER(_devcb) \
	devcb = &msm6242_device::set_out_int_handler(*device, DEVCB_##_devcb);


// ======================> msm6242_device

<<<<<<< HEAD
class msm6242_device :  public device_t,
								public device_rtc_interface
{
public:
	// construction/destruction
	msm6242_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);


	template<class _Object> static devcb_base &set_out_int_handler(device_t &device, _Object object) { return downcast<msm6242_device &>(device).m_out_int_handler.set_callback(object); }
=======
class msm6242_device : public device_t, public device_rtc_interface
{
public:
	// construction/destruction
	msm6242_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	template <class Object> static devcb_base &set_out_int_handler(device_t &device, Object &&cb) { return downcast<msm6242_device &>(device).m_out_int_handler.set_callback(std::forward<Object>(cb)); }
>>>>>>> upstream/master

	// I/O operations
	DECLARE_WRITE8_MEMBER( write );
	DECLARE_READ8_MEMBER( read );

protected:
<<<<<<< HEAD
	// device-level overrides
	virtual void device_start();
	virtual void device_reset();
	virtual void device_pre_save();
	virtual void device_post_load();
	virtual void device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr);

	// rtc overrides
	virtual void rtc_clock_updated(int year, int month, int day, int day_of_week, int hour, int minute, int second);

private:
	static const int RTC_TICKS = ~0;

	static const UINT8 IRQ_64THSECOND = 0;
	static const UINT8 IRQ_SECOND = 1;
	static const UINT8 IRQ_MINUTE = 2;
	static const UINT8 IRQ_HOUR = 3;

	// state
	UINT8                       m_reg[3];
	UINT8                       m_irq_flag;
	UINT8                       m_irq_type;
	UINT16                      m_tick;
=======
	msm6242_device(const machine_config &mconfig, device_type type, const char *tag, device_t *owner, uint32_t clock);

	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;
	virtual void device_pre_save() override;
	virtual void device_post_load() override;
	virtual void device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr) override;

	// rtc overrides
	virtual void rtc_clock_updated(int year, int month, int day, int day_of_week, int hour, int minute, int second) override;

private:
	static constexpr int RTC_TICKS = ~0;

	static constexpr uint8_t IRQ_64THSECOND = 0;
	static constexpr uint8_t IRQ_SECOND = 1;
	static constexpr uint8_t IRQ_MINUTE = 2;
	static constexpr uint8_t IRQ_HOUR = 3;

	// state
	uint8_t                       m_reg[3];
	uint8_t                       m_irq_flag;
	uint8_t                       m_irq_type;
	uint16_t                      m_tick;
>>>>>>> upstream/master

	// incidentals
	devcb_write_line m_out_int_handler;
	emu_timer *                 m_timer;
<<<<<<< HEAD
	UINT64                      m_last_update_time; // last update time, in clock cycles

	// methods
	void rtc_timer_callback();
	UINT64 current_time();
	void irq(UINT8 irq_type);
	UINT64 bump(int rtc_register, UINT64 delta, UINT64 register_min, UINT64 register_range);
	void update_rtc_registers();
	void update_timer();
	UINT8 get_clock_nibble(int rtc_register, bool high);
	static const char *irq_type_string(UINT8 irq_type);
=======
	uint64_t                      m_last_update_time; // last update time, in clock cycles

	// methods
	void rtc_timer_callback();
	uint64_t current_time();
	void irq(uint8_t irq_type);
	uint64_t bump(int rtc_register, uint64_t delta, uint64_t register_min, uint64_t register_range);
	void update_rtc_registers();
	void update_timer();
	uint8_t get_clock_nibble(int rtc_register, bool high);
	static const char *irq_type_string(uint8_t irq_type);
};

// ======================> rtc62421_device

class rtc62421_device : public msm6242_device
{
public:
	// construction/destruction
	rtc62421_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
};

// ======================> rtc62423_device

class rtc62423_device : public msm6242_device
{
public:
	// construction/destruction
	rtc62423_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
};

// ======================> rtc72421_device

class rtc72421_device : public msm6242_device
{
public:
	// construction/destruction
	rtc72421_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
};

// ======================> rtc72423_device

class rtc72423_device : public msm6242_device
{
public:
	// construction/destruction
	rtc72423_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
>>>>>>> upstream/master
};


// device type definition
<<<<<<< HEAD
extern const device_type MSM6242;


#endif /* __MSM6242DEV_H__ */
=======
DECLARE_DEVICE_TYPE(MSM6242,  msm6242_device)
DECLARE_DEVICE_TYPE(RTC62421, rtc62421_device)
DECLARE_DEVICE_TYPE(RTC62423, rtc62423_device)
DECLARE_DEVICE_TYPE(RTC72421, rtc72421_device)
DECLARE_DEVICE_TYPE(RTC72423, rtc72423_device)


#endif // MAME_MACHINE_MSM6242_H
>>>>>>> upstream/master
