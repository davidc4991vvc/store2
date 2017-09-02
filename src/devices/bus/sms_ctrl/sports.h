// license:BSD-3-Clause
// copyright-holders:Fabio Priuli
/**********************************************************************

    Sega Master System "Sports Pad" (US model) emulation

**********************************************************************/

<<<<<<< HEAD
#pragma once

#ifndef __SMS_SPORTS_PAD__
#define __SMS_SPORTS_PAD__


#include "emu.h"
=======
#ifndef MAME_BUS_SMS_CTRL_SPORTS_H
#define MAME_BUS_SMS_CTRL_SPORTS_H

#pragma once


>>>>>>> upstream/master
#include "smsctrl.h"



//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

// ======================> sms_sports_pad_device

class sms_sports_pad_device : public device_t,
							public device_sms_control_port_interface
{
public:
	// construction/destruction
<<<<<<< HEAD
	sms_sports_pad_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// optional information overrides
	virtual ioport_constructor device_input_ports() const;

	DECLARE_CUSTOM_INPUT_MEMBER( dir_pins_r );
	DECLARE_CUSTOM_INPUT_MEMBER( th_pin_r );
	DECLARE_INPUT_CHANGED_MEMBER( th_pin_w );

protected:
	// device-level overrides
	virtual void device_start();

	// device_sms_control_port_interface overrides
	virtual UINT8 peripheral_r();
	virtual void peripheral_w(UINT8 data);
=======
	sms_sports_pad_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// optional information overrides
	virtual ioport_constructor device_input_ports() const override;

	DECLARE_CUSTOM_INPUT_MEMBER( rldu_pins_r ); // Right, Left, Down and Up lines.
	DECLARE_READ_LINE_MEMBER( th_pin_r );
	DECLARE_WRITE_LINE_MEMBER( th_pin_w );

protected:
	// device-level overrides
	virtual void device_start() override;

	// device_sms_control_port_interface overrides
	virtual uint8_t peripheral_r() override;
	virtual void peripheral_w(uint8_t data) override;
>>>>>>> upstream/master

private:
	required_ioport m_sports_in;
	required_ioport m_sports_out;
	required_ioport m_sports_x;
	required_ioport m_sports_y;

<<<<<<< HEAD
	UINT8 m_read_state;
	UINT8 m_last_data;
	UINT8 m_x_axis_reset_value;
	UINT8 m_y_axis_reset_value;
=======
	uint8_t m_read_state;
	uint8_t m_th_pin_state;
	uint8_t m_x_axis_reset_value;
	uint8_t m_y_axis_reset_value;
>>>>>>> upstream/master
	const attotime m_interval;
	emu_timer *m_sportspad_timer;
	static const device_timer_id TIMER_SPORTSPAD = 0;

<<<<<<< HEAD
	void device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr);
=======
	void device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr) override;
>>>>>>> upstream/master
};


// device type definition
<<<<<<< HEAD
extern const device_type SMS_SPORTS_PAD;


#endif
=======
DECLARE_DEVICE_TYPE(SMS_SPORTS_PAD, sms_sports_pad_device)


#endif // MAME_BUS_SMS_CTRL_SPORTS_H
>>>>>>> upstream/master
