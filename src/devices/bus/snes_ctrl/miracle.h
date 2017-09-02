// license:BSD-3-Clause
// copyright-holders:Fabio Priuli
/**********************************************************************

    Super Nintendo Entertainment System - Miracle Piano Keyboard

**********************************************************************/

<<<<<<< HEAD
#pragma once

#ifndef __SNES_MIRACLE__
#define __SNES_MIRACLE__


#include "emu.h"
=======
#ifndef MAME_BUS_SNES_CTRL_MIRACLE_H
#define MAME_BUS_SNES_CTRL_MIRACLE_H

#pragma once


>>>>>>> upstream/master
#include "ctrl.h"
#include "bus/midi/midi.h"

//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

// ======================> snes_miracle_device

class snes_miracle_device : public device_t,
							public device_serial_interface,
							public device_snes_control_port_interface
{
public:
<<<<<<< HEAD
	static const int XMIT_RING_SIZE = 64;
	static const int RECV_RING_SIZE = 64;

	// construction/destruction
	snes_miracle_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	virtual void device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr);
	virtual machine_config_constructor device_mconfig_additions() const;

	// serial overrides
	virtual void rcv_complete();    // Rx completed receiving byte
	virtual void tra_complete();    // Tx completed sending byte
	virtual void tra_callback();    // Tx send bit

	void xmit_char(UINT8 data);

	required_device<midi_port_device> m_midiin, m_midiout;

protected:
	// device-level overrides
	virtual void device_start();
	virtual void device_reset();

	UINT8 read_pin4();
	void write_pin6(UINT8 data);
	void write_strobe(UINT8 data);

	static const device_timer_id TIMER_STROBE_ON = 0;
	emu_timer *strobe_timer;

	int m_strobe_on, m_midi_mode, m_sent_bits;
	UINT32 m_strobe_clock;
	UINT8 m_data_sent;
	UINT8 m_xmitring[XMIT_RING_SIZE], m_recvring[RECV_RING_SIZE];
=======
	// construction/destruction
	snes_miracle_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

protected:
	static constexpr device_timer_id TIMER_STROBE_ON = 0;

	static constexpr int XMIT_RING_SIZE = 64;
	static constexpr int RECV_RING_SIZE = 64;

	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;
	virtual void device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr) override;

	virtual void device_add_mconfig(machine_config &config) override;

	// serial overrides
	virtual void rcv_complete() override;    // Rx completed receiving byte
	virtual void tra_complete() override;    // Tx completed sending byte
	virtual void tra_callback() override;    // Tx send bit

	uint8_t read_pin4() override;
	void write_pin6(uint8_t data) override;
	void write_strobe(uint8_t data) override;

	void xmit_char(uint8_t data);

	required_device<midi_port_device> m_midiin, m_midiout;

	emu_timer *strobe_timer;

	int m_strobe_on, m_midi_mode, m_sent_bits;
	uint32_t m_strobe_clock;
	uint8_t m_data_sent;
	uint8_t m_xmitring[XMIT_RING_SIZE], m_recvring[RECV_RING_SIZE];
>>>>>>> upstream/master
	int m_xmit_read, m_xmit_write;
	int m_recv_read, m_recv_write;
	bool m_tx_busy, m_read_status, m_status_bit;
};

// device type definition
<<<<<<< HEAD
extern const device_type SNES_MIRACLE;

#endif
=======
DECLARE_DEVICE_TYPE(SNES_MIRACLE, snes_miracle_device)

#endif // MAME_BUS_SNES_CTRL_MIRACLE_H
>>>>>>> upstream/master
