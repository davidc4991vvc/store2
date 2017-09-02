// license:BSD-3-Clause
// copyright-holders:Fabio Priuli
/**********************************************************************

<<<<<<< HEAD
    Sega Master System "Paddle Control" emulation

**********************************************************************/

#pragma once

#ifndef __SMS_PADDLE__
#define __SMS_PADDLE__


#include "emu.h"
=======
    Sega Mark III "Paddle Control" emulation

**********************************************************************/

#ifndef MAME_BUS_SMS_CTRL_PADDLE_H
#define MAME_BUS_SMS_CTRL_PADDLE_H

#pragma once


>>>>>>> upstream/master
#include "smsctrl.h"



//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

// ======================> sms_paddle_device

class sms_paddle_device : public device_t,
							public device_sms_control_port_interface
{
public:
	// construction/destruction
<<<<<<< HEAD
	sms_paddle_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// optional information overrides
	virtual ioport_constructor device_input_ports() const;

	DECLARE_CUSTOM_INPUT_MEMBER( dir_pins_r );
	DECLARE_CUSTOM_INPUT_MEMBER( tr_pin_r );

protected:
	// device-level overrides
	virtual void device_start();

	// device_sms_control_port_interface overrides
	virtual UINT8 peripheral_r();
=======
	sms_paddle_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// optional information overrides
	virtual ioport_constructor device_input_ports() const override;

	DECLARE_CUSTOM_INPUT_MEMBER( rldu_pins_r ); // Right, Left, Down and Up lines.
	DECLARE_READ_LINE_MEMBER( tr_pin_r );

protected:
	// device-level overrides
	virtual void device_start() override;

	// device_sms_control_port_interface overrides
	virtual uint8_t peripheral_r() override;
>>>>>>> upstream/master

private:
	required_ioport m_paddle_pins;
	required_ioport m_paddle_x;

<<<<<<< HEAD
	UINT8 m_read_state;
=======
	uint8_t m_read_state;
>>>>>>> upstream/master
	attotime m_start_time;
	const attotime m_interval;
};


// device type definition
extern const device_type SMS_PADDLE;


<<<<<<< HEAD
#endif
=======
#endif // MAME_BUS_SMS_CTRL_PADDLE_H
>>>>>>> upstream/master
