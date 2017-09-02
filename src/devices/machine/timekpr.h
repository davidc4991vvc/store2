// license:BSD-3-Clause
// copyright-holders:Aaron Giles,smf
/***************************************************************************

    timekpr.h

    Various ST Microelectronics timekeeper SRAM implementations:
        - M48T02
        - M48T35
        - M48T37
        - M48T58
        - MK48T08
<<<<<<< HEAD

***************************************************************************/

#pragma once

#ifndef __TIMEKPR_H__
#define __TIMEKPR_H__

#include "emu.h"
=======
        - MK48T12

***************************************************************************/

#ifndef MAME_MACHINE_TIMEKPR_H
#define MAME_MACHINE_TIMEKPR_H

#pragma once

>>>>>>> upstream/master



//**************************************************************************
//  INTERFACE CONFIGURATION MACROS
//**************************************************************************

#define MCFG_M48T02_ADD(_tag) \
	MCFG_DEVICE_ADD(_tag, M48T02, 0)

#define MCFG_M48T35_ADD(_tag) \
	MCFG_DEVICE_ADD(_tag, M48T35, 0)

#define MCFG_M48T37_ADD(_tag) \
	MCFG_DEVICE_ADD(_tag, M48T37, 0)

<<<<<<< HEAD
=======
#define MCFG_M48T37_RESET_HANDLER(_devcb) \
	devcb = &timekeeper_device::set_reset_handler(*device, DEVCB_##_devcb);

#define MCFG_M48T37_IRQ_HANDLER(_devcb) \
	devcb = &timekeeper_device::set_irq_handler(*device, DEVCB_##_devcb);

>>>>>>> upstream/master
#define MCFG_M48T58_ADD(_tag) \
	MCFG_DEVICE_ADD(_tag, M48T58, 0)

#define MCFG_MK48T08_ADD(_tag) \
	MCFG_DEVICE_ADD(_tag, MK48T08, 0)

<<<<<<< HEAD
=======
#define MCFG_MK48T12_ADD(_tag) \
	MCFG_DEVICE_ADD(_tag, MK48T12, 0)

>>>>>>> upstream/master


//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************


// ======================> timekeeper_device

<<<<<<< HEAD
class timekeeper_device :   public device_t,
							public device_nvram_interface
{
protected:
	// construction/destruction
	timekeeper_device(const machine_config &mconfig, device_type type, const char *name, const char *tag, device_t *owner, UINT32 clock, const char *shortname, const char *source);

public:
	DECLARE_WRITE8_MEMBER( write );
	DECLARE_READ8_MEMBER( read );

protected:
	// device-level overrides
	virtual void device_start();
	virtual void device_reset();
	virtual void device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr);

	// device_nvram_interface overrides
	virtual void nvram_default();
	virtual void nvram_read(emu_file &file);
	virtual void nvram_write(emu_file &file);
=======
class timekeeper_device : public device_t, public device_nvram_interface
{
public:
	DECLARE_WRITE8_MEMBER( write );
	DECLARE_READ8_MEMBER( read );
	DECLARE_WRITE8_MEMBER(watchdog_write);
	template <class Object> static devcb_base &set_reset_handler(device_t &device, Object &&cb) { return downcast<timekeeper_device &>(device).m_reset_cb.set_callback(std::forward<Object>(cb)); }
	template <class Object> static devcb_base &set_irq_handler(device_t &device, Object &&cb) { return downcast<timekeeper_device &>(device).m_irq_cb.set_callback(std::forward<Object>(cb)); }

protected:
	// construction/destruction
	timekeeper_device(const machine_config &mconfig, device_type type, const char *tag, device_t *owner, uint32_t clock, int size);

	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;
	virtual void device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr) override;

	// device_nvram_interface overrides
	virtual void nvram_default() override;
	virtual void nvram_read(emu_file &file) override;
	virtual void nvram_write(emu_file &file) override;

	TIMER_CALLBACK_MEMBER(watchdog_callback);
	devcb_write_line m_reset_cb;
	devcb_write_line m_irq_cb;
>>>>>>> upstream/master

private:
	void counters_to_ram();
	void counters_from_ram();

	// internal state
<<<<<<< HEAD
	UINT8 m_control;
	UINT8 m_seconds;
	UINT8 m_minutes;
	UINT8 m_hours;
	UINT8 m_day;
	UINT8 m_date;
	UINT8 m_month;
	UINT8 m_year;
	UINT8 m_century;

	dynamic_buffer m_data;
	UINT8 *m_default_data;

protected:
	int m_size;
=======
	uint8_t m_control;
	uint8_t m_seconds;
	uint8_t m_minutes;
	uint8_t m_hours;
	uint8_t m_day;
	uint8_t m_date;
	uint8_t m_month;
	uint8_t m_year;
	uint8_t m_century;

	std::vector<uint8_t> m_data;
	optional_region_ptr<uint8_t> m_default_data;

	emu_timer* m_watchdog_timer;
	attotime m_watchdog_delay;
protected:
	int const m_size;
	int m_offset_watchdog;
>>>>>>> upstream/master
	int m_offset_control;
	int m_offset_seconds;
	int m_offset_minutes;
	int m_offset_hours;
	int m_offset_day;
	int m_offset_date;
	int m_offset_month;
	int m_offset_year;
	int m_offset_century;
	int m_offset_flags;
};

class m48t02_device : public timekeeper_device
{
public:
<<<<<<< HEAD
	m48t02_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
=======
	m48t02_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
>>>>>>> upstream/master
};

class m48t35_device : public timekeeper_device
{
public:
<<<<<<< HEAD
	m48t35_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
=======
	m48t35_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
>>>>>>> upstream/master
};

class m48t37_device : public timekeeper_device
{
public:
<<<<<<< HEAD
	m48t37_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
=======
	m48t37_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
>>>>>>> upstream/master
};

class m48t58_device : public timekeeper_device
{
public:
<<<<<<< HEAD
	m48t58_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
=======
	m48t58_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
>>>>>>> upstream/master
};

class mk48t08_device : public timekeeper_device
{
public:
<<<<<<< HEAD
	mk48t08_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
};

// device type definition
extern const device_type M48T02;
extern const device_type M48T35;
extern const device_type M48T37;
extern const device_type M48T58;
extern const device_type MK48T08;

#endif // __TIMEKPR_H__
=======
	mk48t08_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
};

class mk48t12_device : public timekeeper_device
{
public:
	mk48t12_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
};

// device type definition
DECLARE_DEVICE_TYPE(M48T02,  m48t02_device)
DECLARE_DEVICE_TYPE(M48T35,  m48t35_device)
DECLARE_DEVICE_TYPE(M48T37,  m48t37_device)
DECLARE_DEVICE_TYPE(M48T58,  m48t58_device)
DECLARE_DEVICE_TYPE(MK48T08, mk48t08_device)
DECLARE_DEVICE_TYPE(MK48T12, mk48t12_device)

#endif // MAME_MACHINE_TIMEKPR_H
>>>>>>> upstream/master
