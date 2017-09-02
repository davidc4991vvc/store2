// license:BSD-3-Clause
// copyright-holders:Fabio Priuli
/**********************************************************************

<<<<<<< HEAD
    Sega Master System "Rapid Fire Unit" emulation

**********************************************************************/

#pragma once

#ifndef __SMS_RAPID_FIRE__
#define __SMS_RAPID_FIRE__


#include "emu.h"
=======
    Sega SG-1000/Mark-III/SMS "Rapid Fire Unit" emulation

**********************************************************************/

#ifndef MAME_BUS_SMS_CTRL_RFU_H
#define MAME_BUS_SMS_CTRL_RFU_H

#pragma once


>>>>>>> upstream/master
#include "smsctrl.h"



//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

// ======================> sms_rapid_fire_device

class sms_rapid_fire_device : public device_t,
							public device_sms_control_port_interface
{
public:
	// construction/destruction
<<<<<<< HEAD
	sms_rapid_fire_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// optional information overrides
	virtual ioport_constructor device_input_ports() const;

	DECLARE_WRITE_LINE_MEMBER(th_pin_w);
	DECLARE_READ32_MEMBER(pixel_r);

protected:
	// device-level overrides
	virtual void device_start();
	virtual machine_config_constructor device_mconfig_additions() const;

	// device_sms_control_port_interface overrides
	virtual UINT8 peripheral_r();
	virtual void peripheral_w(UINT8 data);

private:
	required_ioport m_rfire_sw;
	required_device<sms_control_port_device> m_subctrl_port;

	UINT8 m_read_state;
=======
	sms_rapid_fire_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

protected:
	// device-level overrides
	virtual void device_start() override;

	// optional information overrides
	virtual ioport_constructor device_input_ports() const override;
	virtual void device_add_mconfig(machine_config &config) override;

	// device_sms_control_port_interface overrides
	virtual uint8_t peripheral_r() override;
	virtual void peripheral_w(uint8_t data) override;

private:
	DECLARE_WRITE_LINE_MEMBER(th_pin_w);
	DECLARE_READ32_MEMBER(pixel_r);

	required_ioport m_rfire_sw;
	required_device<sms_control_port_device> m_subctrl_port;

	uint8_t m_read_state;
>>>>>>> upstream/master
	attotime m_start_time;
	const attotime m_interval;
};


// device type definition
<<<<<<< HEAD
extern const device_type SMS_RAPID_FIRE;


#endif
=======
DECLARE_DEVICE_TYPE(SMS_RAPID_FIRE, sms_rapid_fire_device)


#endif // MAME_BUS_SMS_CTRL_RFU_H
>>>>>>> upstream/master
