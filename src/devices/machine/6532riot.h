// license:BSD-3-Clause
// copyright-holders:Aaron Giles
/***************************************************************************

  RIOT 6532 emulation

***************************************************************************/

#pragma once

#ifndef __RIOT6532_H__
#define __RIOT6532_H__

<<<<<<< HEAD
#include "emu.h"
=======
>>>>>>> upstream/master


//**************************************************************************
//  INTERFACE CONFIGURATION MACROS
//**************************************************************************

#define MCFG_RIOT6532_IN_PA_CB(_devcb) \
	devcb = &riot6532_device::set_in_pa_callback(*device, DEVCB_##_devcb);

#define MCFG_RIOT6532_OUT_PA_CB(_devcb) \
	devcb = &riot6532_device::set_out_pa_callback(*device, DEVCB_##_devcb);

#define MCFG_RIOT6532_IN_PB_CB(_devcb) \
	devcb = &riot6532_device::set_in_pb_callback(*device, DEVCB_##_devcb);

#define MCFG_RIOT6532_OUT_PB_CB(_devcb) \
	devcb = &riot6532_device::set_out_pb_callback(*device, DEVCB_##_devcb);

#define MCFG_RIOT6532_IRQ_CB(_devcb) \
	devcb = &riot6532_device::set_irq_callback(*device, DEVCB_##_devcb);


/***************************************************************************
    TYPE DEFINITIONS
***************************************************************************/


// ======================> riot6532_device

class riot6532_device :  public device_t
{
public:
	// construction/destruction
<<<<<<< HEAD
	riot6532_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
=======
	riot6532_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
>>>>>>> upstream/master

	template<class _Object> static devcb_base &set_in_pa_callback(device_t &device, _Object object) { return downcast<riot6532_device &>(device).m_in_pa_cb.set_callback(object); }
	template<class _Object> static devcb_base &set_out_pa_callback(device_t &device, _Object object) { return downcast<riot6532_device &>(device).m_out_pa_cb.set_callback(object); }
	template<class _Object> static devcb_base &set_in_pb_callback(device_t &device, _Object object) { return downcast<riot6532_device &>(device).m_in_pb_cb.set_callback(object); }
	template<class _Object> static devcb_base &set_out_pb_callback(device_t &device, _Object object) { return downcast<riot6532_device &>(device).m_out_pb_cb.set_callback(object); }
	template<class _Object> static devcb_base &set_irq_callback(device_t &device, _Object object) { return downcast<riot6532_device &>(device).m_irq_cb.set_callback(object); }

	DECLARE_READ8_MEMBER( read );
	DECLARE_WRITE8_MEMBER( write );

<<<<<<< HEAD
	UINT8 reg_r(UINT8 offset, bool debugger_access = false);
	void reg_w(UINT8 offset, UINT8 data);

	void porta_in_set(UINT8 data, UINT8 mask);
	void portb_in_set(UINT8 data, UINT8 mask);

	UINT8 porta_in_get();
	UINT8 portb_in_get();

	UINT8 porta_out_get();
	UINT8 portb_out_get();
=======
	uint8_t reg_r(uint8_t offset, bool debugger_access = false);
	void reg_w(uint8_t offset, uint8_t data);

	void porta_in_set(uint8_t data, uint8_t mask);
	void portb_in_set(uint8_t data, uint8_t mask);

	DECLARE_WRITE_LINE_MEMBER(pa0_w);
	DECLARE_WRITE_LINE_MEMBER(pa1_w);
	DECLARE_WRITE_LINE_MEMBER(pa2_w);
	DECLARE_WRITE_LINE_MEMBER(pa3_w);
	DECLARE_WRITE_LINE_MEMBER(pa4_w);
	DECLARE_WRITE_LINE_MEMBER(pa5_w);
	DECLARE_WRITE_LINE_MEMBER(pa6_w);
	DECLARE_WRITE_LINE_MEMBER(pa7_w);
	DECLARE_WRITE_LINE_MEMBER(pb0_w);
	DECLARE_WRITE_LINE_MEMBER(pb1_w);
	DECLARE_WRITE_LINE_MEMBER(pb2_w);
	DECLARE_WRITE_LINE_MEMBER(pb3_w);
	DECLARE_WRITE_LINE_MEMBER(pb4_w);
	DECLARE_WRITE_LINE_MEMBER(pb5_w);
	DECLARE_WRITE_LINE_MEMBER(pb6_w);
	DECLARE_WRITE_LINE_MEMBER(pb7_w);

	uint8_t porta_in_get();
	uint8_t portb_in_get();

	uint8_t porta_out_get();
	uint8_t portb_out_get();
>>>>>>> upstream/master

	void timer_end();

protected:
	class riot6532_port
	{
	public:
<<<<<<< HEAD
		UINT8                   m_in;
		UINT8                   m_out;
		UINT8                   m_ddr;
=======
		uint8_t                   m_in;
		uint8_t                   m_out;
		uint8_t                   m_ddr;
>>>>>>> upstream/master
		devcb_read8             *m_in_cb;
		devcb_write8            *m_out_cb;
	};

	// device-level overrides
<<<<<<< HEAD
	virtual void device_start();
	virtual void device_reset();
	virtual void device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr);
	virtual void device_post_load() { }
	virtual void device_clock_changed() { }
=======
	virtual void device_start() override;
	virtual void device_reset() override;
	virtual void device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr) override;
	virtual void device_post_load() override { }
	virtual void device_clock_changed() override { }
>>>>>>> upstream/master


private:
	void update_irqstate();
<<<<<<< HEAD
	UINT8 apply_ddr(const riot6532_port *port);
	void update_pa7_state();
	UINT8 get_timer();
=======
	uint8_t apply_ddr(const riot6532_port *port);
	void update_pa7_state();
	uint8_t get_timer();
>>>>>>> upstream/master

	riot6532_port   m_port[2];

	devcb_read8         m_in_pa_cb;
	devcb_write8        m_out_pa_cb;
	devcb_read8         m_in_pb_cb;
	devcb_write8        m_out_pb_cb;
	devcb_write_line    m_irq_cb;

<<<<<<< HEAD
	UINT8           m_irqstate;
	UINT8           m_irqenable;
	int             m_irq;

	UINT8           m_pa7dir;     /* 0x80 = high-to-low, 0x00 = low-to-high */
	UINT8           m_pa7prev;

	UINT8           m_timershift;
	UINT8           m_timerstate;
=======
	uint8_t           m_irqstate;
	uint8_t           m_irqenable;
	int             m_irq;

	uint8_t           m_pa7dir;     /* 0x80 = high-to-low, 0x00 = low-to-high */
	uint8_t           m_pa7prev;

	uint8_t           m_timershift;
	uint8_t           m_timerstate;
>>>>>>> upstream/master
	emu_timer *     m_timer;

	enum
	{
		TIMER_END_CB
	};
};


// device type definition
<<<<<<< HEAD
extern const device_type RIOT6532;
=======
DECLARE_DEVICE_TYPE(RIOT6532, riot6532_device)
>>>>>>> upstream/master

#endif
