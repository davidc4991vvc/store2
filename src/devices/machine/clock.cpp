// license:BSD-3-Clause
// copyright-holders:smf
<<<<<<< HEAD
#include "clock.h"

const device_type CLOCK = &device_creator<clock_device>;

clock_device::clock_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock)
	: device_t(mconfig, CLOCK, "Clock", tag, owner, clock, "clock", __FILE__),
	m_signal(0),
	m_timer(NULL),
=======
#include "emu.h"
#include "clock.h"

DEFINE_DEVICE_TYPE(CLOCK, clock_device, "clock", "Clock")

clock_device::clock_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock)
	: device_t(mconfig, CLOCK, tag, owner, clock),
	m_signal(0),
	m_timer(nullptr),
>>>>>>> upstream/master
	m_signal_handler(*this)
{
}

void clock_device::device_start()
{
	m_signal_handler.resolve();

	save_item(NAME(m_signal));
}

void clock_device::device_clock_changed()
{
	update_timer();
}

attotime clock_device::period()
{
	if (m_clock > 0)
		return attotime::from_hz(m_clock * 2);

	return attotime::never;
}

void clock_device::device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr)
{
	m_signal = !m_signal;
	m_signal_handler(m_signal);

	m_timer->adjust(period());
}

void clock_device::update_timer()
{
	if (!m_signal_handler.isnull() && m_clock > 0)
	{
<<<<<<< HEAD
		if (m_timer == NULL)
=======
		if (m_timer == nullptr)
>>>>>>> upstream/master
		{
			m_timer = timer_alloc(0);
			m_timer->adjust(period());
		}
		else
		{
			attotime next = period() - m_timer->elapsed();

			if (next < attotime::zero)
			{
				next = attotime::zero;
			}

			m_timer->adjust(next);
		}
	}
<<<<<<< HEAD
	else if (m_timer != NULL)
=======
	else if (m_timer != nullptr)
>>>>>>> upstream/master
	{
		m_timer->adjust(attotime::never);
	}
}
