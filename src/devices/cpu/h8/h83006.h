// license:BSD-3-Clause
// copyright-holders:Olivier Galibert
/***************************************************************************

    h83006.h

    H8/3006 / H8/3007

    H8/300H-based mcus.


***************************************************************************/

<<<<<<< HEAD
#ifndef __H83006_H__
#define __H83006_H__
=======
#ifndef MAME_CPU_H8_H83006_H
#define MAME_CPU_H8_H83006_H

#pragma once
>>>>>>> upstream/master

#include "h8h.h"
#include "h8_adc.h"
#include "h8_port.h"
#include "h8_intc.h"
<<<<<<< HEAD
#include "h8_sci.h"
#include "h8_timer8.h"
#include "h8_timer16.h"

class h83006_device : public h8h_device {
public:
	h83006_device(const machine_config &mconfig, device_type type, const char *name, const char *tag, device_t *owner, UINT32 clock, const char *shortname, const char *source);
	h83006_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
=======
#include "h8_timer8.h"
#include "h8_timer16.h"
#include "h8_sci.h"
#include "h8_watchdog.h"

class h83006_device : public h8h_device {
public:
	h83006_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
>>>>>>> upstream/master

	DECLARE_READ8_MEMBER(syscr_r);
	DECLARE_WRITE8_MEMBER(syscr_w);

protected:
<<<<<<< HEAD
=======
	h83006_device(const machine_config &mconfig, device_type type, const char *tag, device_t *owner, uint32_t clock, uint32_t start);

>>>>>>> upstream/master
	required_device<h8h_intc_device> intc;
	required_device<h8_adc_device> adc;
	required_device<h8_port_device> port4;
	required_device<h8_port_device> port6;
	required_device<h8_port_device> port7;
	required_device<h8_port_device> port8;
	required_device<h8_port_device> port9;
	required_device<h8_port_device> porta;
	required_device<h8_port_device> portb;
	required_device<h8h_timer8_channel_device> timer8_0;
	required_device<h8h_timer8_channel_device> timer8_1;
	required_device<h8h_timer8_channel_device> timer8_2;
	required_device<h8h_timer8_channel_device> timer8_3;
	required_device<h8_timer16_device> timer16;
	required_device<h8h_timer16_channel_device> timer16_0;
	required_device<h8h_timer16_channel_device> timer16_1;
	required_device<h8h_timer16_channel_device> timer16_2;
	required_device<h8_sci_device> sci0;
	required_device<h8_sci_device> sci1;
	required_device<h8_sci_device> sci2;
<<<<<<< HEAD

	UINT8 syscr;
	UINT32 ram_start;

	virtual void update_irq_filter();
	virtual void interrupt_taken();
	virtual int trapa_setup();
	virtual void irq_setup();
	virtual void internal_update(UINT64 current_time);
	virtual machine_config_constructor device_mconfig_additions() const;
	DECLARE_ADDRESS_MAP(map, 16);

	virtual void device_start();
	virtual void device_reset();
	virtual void execute_set_input(int inputnum, int state);
=======
	required_device<h8_watchdog_device> watchdog;

	uint8_t syscr;
	uint32_t ram_start;

	virtual void update_irq_filter() override;
	virtual void interrupt_taken() override;
	virtual int trapa_setup() override;
	virtual void irq_setup() override;
	virtual void internal_update(uint64_t current_time) override;
	virtual void device_add_mconfig(machine_config &config) override;
	DECLARE_ADDRESS_MAP(map, 16);

	virtual void device_start() override;
	virtual void device_reset() override;
	virtual void execute_set_input(int inputnum, int state) override;
>>>>>>> upstream/master
};


class h83007_device : public h83006_device {
public:
<<<<<<< HEAD
	h83007_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
};

extern const device_type H83006;
extern const device_type H83007;

#endif
=======
	h83007_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
};

DECLARE_DEVICE_TYPE(H83006, h83006_device)
DECLARE_DEVICE_TYPE(H83007, h83007_device)

#endif // MAME_CPU_H8_H83006_H
>>>>>>> upstream/master
