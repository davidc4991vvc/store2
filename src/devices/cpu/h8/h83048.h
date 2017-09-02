// license:BSD-3-Clause
// copyright-holders:Olivier Galibert
/***************************************************************************

    h83048.h

    H8-3048 family emulation

    H8-300H-based mcus.

    Variant         ROM        RAM
    H8/3044         32K         2K
    H8/3045         64K         2K
    H8/3047         96K         4K
    H8/3048        192K         4K

    The 3394, 3396, and 3997 variants are the mask-rom versions.


***************************************************************************/

<<<<<<< HEAD
#ifndef __H83048_H__
#define __H83048_H__
=======
#ifndef MAME_CPU_H8_H83048_H
#define MAME_CPU_H8_H83048_H
>>>>>>> upstream/master

#include "h8h.h"
#include "h8_adc.h"
#include "h8_port.h"
#include "h8_intc.h"
<<<<<<< HEAD
#include "h8_sci.h"
#include "h8_timer16.h"

class h83048_device : public h8h_device {
public:
	h83048_device(const machine_config &mconfig, device_type type, const char *name, const char *tag, device_t *owner, UINT32 clock, const char *shortname, const char *source);
	h83048_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
=======
#include "h8_timer16.h"
#include "h8_sci.h"
#include "h8_watchdog.h"

class h83048_device : public h8h_device {
public:
	h83048_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
>>>>>>> upstream/master

	DECLARE_READ8_MEMBER(syscr_r);
	DECLARE_WRITE8_MEMBER(syscr_w);

protected:
<<<<<<< HEAD
=======
	h83048_device(const machine_config &mconfig, device_type type, const char *tag, device_t *owner, uint32_t clock, uint32_t start);

>>>>>>> upstream/master
	required_device<h8h_intc_device> intc;
	required_device<h8_adc_device> adc;
	required_device<h8_port_device> port1;
	required_device<h8_port_device> port2;
	required_device<h8_port_device> port3;
	required_device<h8_port_device> port4;
	required_device<h8_port_device> port5;
	required_device<h8_port_device> port6;
	required_device<h8_port_device> port7;
	required_device<h8_port_device> port8;
	required_device<h8_port_device> port9;
	required_device<h8_port_device> porta;
	required_device<h8_port_device> portb;
	required_device<h8_timer16_device> timer16;
	required_device<h8h_timer16_channel_device> timer16_0;
	required_device<h8h_timer16_channel_device> timer16_1;
	required_device<h8h_timer16_channel_device> timer16_2;
	required_device<h8h_timer16_channel_device> timer16_3;
	required_device<h8h_timer16_channel_device> timer16_4;
	required_device<h8_sci_device> sci0;
	required_device<h8_sci_device> sci1;
<<<<<<< HEAD

	UINT32 ram_start;
	UINT8 syscr;

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

	uint32_t ram_start;
	uint8_t syscr;

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

class h83044_device : public h83048_device {
public:
<<<<<<< HEAD
	h83044_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
=======
	h83044_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
>>>>>>> upstream/master
};

class h83045_device : public h83048_device {
public:
<<<<<<< HEAD
	h83045_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
=======
	h83045_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
>>>>>>> upstream/master
};

class h83047_device : public h83048_device {
public:
<<<<<<< HEAD
	h83047_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
};

extern const device_type H83044;
extern const device_type H83045;
extern const device_type H83047;
extern const device_type H83048;

#endif
=======
	h83047_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
};

DECLARE_DEVICE_TYPE(H83044, h83044_device)
DECLARE_DEVICE_TYPE(H83045, h83045_device)
DECLARE_DEVICE_TYPE(H83047, h83047_device)
DECLARE_DEVICE_TYPE(H83048, h83048_device)

#endif // MAME_CPU_H8_H83048_H
>>>>>>> upstream/master
