// license:BSD-3-Clause
// copyright-holders:Fabio Priuli
/**********************************************************************

    Sega Master System "Graphic Board" emulation

**********************************************************************/

<<<<<<< HEAD
#pragma once

#ifndef __SMS_GRAPHIC__
#define __SMS_GRAPHIC__


#include "emu.h"
=======
#ifndef MAME_BUS_SMS_CTRL_GRAPHIC_H
#define MAME_BUS_SMS_CTRL_GRAPHIC_H

#pragma once


>>>>>>> upstream/master
#include "smsctrl.h"



//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

// ======================> sms_graphic_device

class sms_graphic_device : public device_t,
							public device_sms_control_port_interface
{
public:
	// construction/destruction
<<<<<<< HEAD
	sms_graphic_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// optional information overrides
	virtual ioport_constructor device_input_ports() const;

protected:
	// device-level overrides
	virtual void device_start();

	// device_sms_control_port_interface overrides
	virtual UINT8 peripheral_r();
	virtual void peripheral_w(UINT8 data);
=======
	sms_graphic_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// optional information overrides
	virtual ioport_constructor device_input_ports() const override;

protected:
	// device-level overrides
	virtual void device_start() override;

	// device_sms_control_port_interface overrides
	virtual uint8_t peripheral_r() override;
	virtual void peripheral_w(uint8_t data) override;
>>>>>>> upstream/master

private:
	required_ioport m_buttons;
	required_ioport m_x;
	required_ioport m_y;

	int m_index;
<<<<<<< HEAD
	UINT8 m_previous_write;
	UINT8 m_pressure;
=======
	uint8_t m_previous_write;
	uint8_t m_pressure;
>>>>>>> upstream/master
};


// device type definition
<<<<<<< HEAD
extern const device_type SMS_GRAPHIC;


#endif
=======
DECLARE_DEVICE_TYPE(SMS_GRAPHIC, sms_graphic_device)


#endif // MAME_BUS_SMS_CTRL_GRAPHIC_H
>>>>>>> upstream/master
