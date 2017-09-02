// license:BSD-3-Clause
// copyright-holders:Fabio Priuli
<<<<<<< HEAD
#ifndef __NES_EVENT_H
#define __NES_EVENT_H
=======
#ifndef MAEM_BUS_NES_EVENT_H
#define MAEM_BUS_NES_EVENT_H

#pragma once
>>>>>>> upstream/master

#include "mmc1.h"


// ======================> nes_event_device

class nes_event_device : public nes_sxrom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_event_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual void device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr);
	virtual ioport_constructor device_input_ports() const;
	virtual void update_regs(int reg);

	required_ioport m_dsw;

	virtual void pcb_reset();

protected:
	virtual void set_prg();
	virtual void set_chr();
	int m_nwc_init;

	static const device_timer_id TIMER_EVENT = 0;
	emu_timer *event_timer;
	attotime timer_freq;

	UINT32 m_timer_count;
=======
	nes_event_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual ioport_constructor device_input_ports() const override;

	virtual void pcb_reset() override;

protected:
	static constexpr device_timer_id TIMER_EVENT = 0;

	// device-level overrides
	virtual void device_start() override;
	virtual void device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr) override;

	virtual void update_regs(int reg) override;
	virtual void set_prg() override;
	virtual void set_chr() override;

	required_ioport m_dsw;

	int m_nwc_init;

	emu_timer *event_timer;
	attotime timer_freq;

	uint32_t m_timer_count;
>>>>>>> upstream/master
	int m_timer_on, m_timer_enabled;
};


// device type definition
<<<<<<< HEAD
extern const device_type NES_EVENT;

#endif
=======
DECLARE_DEVICE_TYPE(NES_EVENT, nes_event_device)

#endif // MAEM_BUS_NES_EVENT_H
>>>>>>> upstream/master
