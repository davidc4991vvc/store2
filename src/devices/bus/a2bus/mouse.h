// license:BSD-3-Clause
// copyright-holders:R. Belmont
/*********************************************************************

    mouse.h

    Implemention of the Apple II Mouse Card

*********************************************************************/

<<<<<<< HEAD
#ifndef __A2BUS_MOUSE__
#define __A2BUS_MOUSE__

#include "emu.h"
#include "a2bus.h"
#include "machine/6821pia.h"
#include "cpu/m6805/m6805.h"
=======
#ifndef MAME_DEVICES_A2BUS_MOUSE_H
#define MAME_DEVICES_A2BUS_MOUSE_H

#pragma once

#include "a2bus.h"
#include "machine/6821pia.h"
#include "cpu/m6805/m68705.h"
>>>>>>> upstream/master

//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

class a2bus_mouse_device:
	public device_t,
	public device_a2bus_card_interface
{
public:
	// construction/destruction
<<<<<<< HEAD
	a2bus_mouse_device(const machine_config &mconfig, device_type type, const char *name, const char *tag, device_t *owner, UINT32 clock, const char *shortname, const char *source);
	a2bus_mouse_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// optional information overrides
	virtual machine_config_constructor device_mconfig_additions() const;
	virtual const rom_entry *device_rom_region() const;
	virtual ioport_constructor device_input_ports() const;
	virtual void device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr);

	DECLARE_READ8_MEMBER(pia_in_a);
	DECLARE_READ8_MEMBER(pia_in_b);
=======
	a2bus_mouse_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// optional information overrides
	virtual const tiny_rom_entry *device_rom_region() const override;
	virtual ioport_constructor device_input_ports() const override;

protected:
	a2bus_mouse_device(const machine_config &mconfig, device_type type, const char *tag, device_t *owner, uint32_t clock);

	virtual void device_add_mconfig(machine_config &config) override;
	virtual void device_start() override;
	virtual void device_reset() override;

	// overrides of standard a2bus slot functions
	virtual uint8_t read_c0nx(address_space &space, uint8_t offset) override;
	virtual void write_c0nx(address_space &space, uint8_t offset, uint8_t data) override;
	virtual uint8_t read_cnxx(address_space &space, uint8_t offset) override;

>>>>>>> upstream/master
	DECLARE_WRITE8_MEMBER(pia_out_a);
	DECLARE_WRITE8_MEMBER(pia_out_b);
	DECLARE_WRITE_LINE_MEMBER(pia_irqa_w);
	DECLARE_WRITE_LINE_MEMBER(pia_irqb_w);

	DECLARE_READ8_MEMBER(mcu_port_a_r);
	DECLARE_READ8_MEMBER(mcu_port_b_r);
<<<<<<< HEAD
	DECLARE_READ8_MEMBER(mcu_port_c_r);
	DECLARE_WRITE8_MEMBER(mcu_port_a_w);
	DECLARE_WRITE8_MEMBER(mcu_port_b_w);
	DECLARE_WRITE8_MEMBER(mcu_port_c_w);
	DECLARE_WRITE8_MEMBER(mcu_ddr_a_w);
	DECLARE_WRITE8_MEMBER(mcu_ddr_b_w);
	DECLARE_WRITE8_MEMBER(mcu_ddr_c_w);
	DECLARE_READ8_MEMBER(mcu_timer_r);
	DECLARE_WRITE8_MEMBER(mcu_timer_w);

protected:
	virtual void device_start();
	virtual void device_reset();

	// overrides of standard a2bus slot functions
	virtual UINT8 read_c0nx(address_space &space, UINT8 offset);
	virtual void write_c0nx(address_space &space, UINT8 offset, UINT8 data);
	virtual UINT8 read_cnxx(address_space &space, UINT8 offset);

	required_device<pia6821_device> m_pia;
	required_device<m68705_device> m_mcu;
	required_ioport m_mouseb, m_mousex, m_mousey;

private:
	UINT8 *m_rom;
	bool m_started;
	int m_rom_bank;
	UINT8 m_ddr_a;
	UINT8 m_ddr_b;
	UINT8 m_ddr_c;
	UINT8 m_port_a_out;
	UINT8 m_port_b_out;
	UINT8 m_port_c_out;
	UINT8 m_port_a_in;
	UINT8 m_port_b_in;
	UINT8 m_port_c_in;
	UINT8 m_timer_cnt;
	UINT8 m_timer_ctl;
	UINT8 m_mask_option;
	int last_mx, last_my, count_x, count_y;
	emu_timer *m_timer, *m_read_timer;
=======
	DECLARE_WRITE8_MEMBER(mcu_port_a_w);
	DECLARE_WRITE8_MEMBER(mcu_port_b_w);
	DECLARE_WRITE8_MEMBER(mcu_port_c_w);

	required_device<pia6821_device> m_pia;
	required_device<m68705p_device> m_mcu;
	required_ioport m_mouseb;
	required_ioport_array<2> m_mousexy;

private:
	template <unsigned AXIS, u8 DIR, u8 CLK> void update_axis();

	required_region_ptr<uint8_t> m_rom;
	int m_rom_bank;
	uint8_t m_port_a_in, m_port_b_in;
	int m_last[2], m_count[2];
>>>>>>> upstream/master
};

// device type definition
extern const device_type A2BUS_MOUSE;

<<<<<<< HEAD
#endif /* __A2BUS_MOUSE__ */
=======
#endif // MAME_DEVICES_A2BUS_MOUSE_H
>>>>>>> upstream/master
