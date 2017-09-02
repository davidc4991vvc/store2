// license:BSD-3-Clause
// copyright-holders:Fabio Priuli
/**********************************************************************

<<<<<<< HEAD
    Sega Master System "Control Pad"/generic joystick emulation

**********************************************************************/

#pragma once

#ifndef __SMS_JOYPAD__
#define __SMS_JOYPAD__


#include "emu.h"
=======
    Sega Mark III "Joypad" / Master System "Control Pad" emulation

**********************************************************************/

#ifndef MAME_BUS_SMS_CTRL_JOYPAD_H
#define MAME_BUS_SMS_CTRL_JOYPAD_H

#pragma once


>>>>>>> upstream/master
#include "smsctrl.h"



//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

// ======================> sms_joypad_device

class sms_joypad_device : public device_t,
							public device_sms_control_port_interface
{
public:
	// construction/destruction
<<<<<<< HEAD
	sms_joypad_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// optional information overrides
	virtual ioport_constructor device_input_ports() const;

protected:
	// device-level overrides
	virtual void device_start();

	// device_sms_control_port_interface overrides
	virtual UINT8 peripheral_r();
=======
	sms_joypad_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// optional information overrides
	virtual ioport_constructor device_input_ports() const override;

protected:
	// device-level overrides
	virtual void device_start() override;

	// device_sms_control_port_interface overrides
	virtual uint8_t peripheral_r() override;
>>>>>>> upstream/master

private:
	required_ioport m_joypad;
};


// device type definition
<<<<<<< HEAD
extern const device_type SMS_JOYPAD;


#endif
=======
DECLARE_DEVICE_TYPE(SMS_JOYPAD, sms_joypad_device)


#endif // MAME_BUS_SMS_CTRL_JOYPAD_H
>>>>>>> upstream/master
