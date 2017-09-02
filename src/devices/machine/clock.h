// license:BSD-3-Clause
// copyright-holders:smf
<<<<<<< HEAD
#ifndef __CLOCK_H__
#define __CLOCK_H__

#pragma once

#include "emu.h"
=======
#ifndef MAME_MACHINE_CLOCK_H
#define MAME_MACHINE_CLOCK_H

#pragma once


#define MCFG_CLOCK_ADD(_tag, _clock) \
	MCFG_DEVICE_ADD(_tag, CLOCK, _clock)
>>>>>>> upstream/master

#define MCFG_CLOCK_SIGNAL_HANDLER(_devcb) \
	devcb = &clock_device::set_signal_handler(*device, DEVCB_##_devcb);

class clock_device : public device_t
{
public:
<<<<<<< HEAD
	clock_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	template<class _Object> static devcb_base &set_signal_handler(device_t &device, _Object object) { return downcast<clock_device &>(device).m_signal_handler.set_callback(object); }

protected:
	virtual void device_start();
	virtual void device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr);
	virtual void device_clock_changed();
=======
	clock_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	template <class Object> static devcb_base &set_signal_handler(device_t &device, Object &&cb) { return downcast<clock_device &>(device).m_signal_handler.set_callback(std::forward<Object>(cb)); }

protected:
	virtual void device_start() override;
	virtual void device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr) override;
	virtual void device_clock_changed() override;
>>>>>>> upstream/master

private:
	void update_timer();
	attotime period();

	int m_signal;
	emu_timer *m_timer;

	devcb_write_line m_signal_handler;
};

<<<<<<< HEAD
extern const device_type CLOCK;

#endif
=======
DECLARE_DEVICE_TYPE(CLOCK, clock_device)

#endif // MAME_MACHINE_CLOCK_H
>>>>>>> upstream/master
