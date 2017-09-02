// license:BSD-3-Clause
// copyright-holders:Fabio Priuli
/**********************************************************************

    Sega Game Gear "SMS Controller Adaptor" emulation
    Also known as "Master Link" cable.

**********************************************************************/

<<<<<<< HEAD
#pragma once

#ifndef __SMS_CTRL_ADAPTOR__
#define __SMS_CTRL_ADAPTOR__


#include "emu.h"
=======
#ifndef MAME_BUS_GAMEGEAR_SMSCRTLADP_H
#define MAME_BUS_GAMEGEAR_SMSCRTLADP_H

#pragma once


>>>>>>> upstream/master
#include "ggext.h"
#include "bus/sms_ctrl/smsctrl.h"



//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

// ======================> sms_ctrl_adaptor_device

class sms_ctrl_adaptor_device : public device_t,
							public device_gg_ext_port_interface
{
public:
	// construction/destruction
<<<<<<< HEAD
	sms_ctrl_adaptor_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	DECLARE_WRITE_LINE_MEMBER(th_pin_w);
	DECLARE_READ32_MEMBER(pixel_r);

protected:
	// device-level overrides
	virtual void device_start();
	virtual machine_config_constructor device_mconfig_additions() const;

	// device_gg_ext_port_interface overrides
	virtual UINT8 peripheral_r();
	virtual void peripheral_w(UINT8 data);

private:
=======
	sms_ctrl_adaptor_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_add_mconfig(machine_config &config) override;

	// device_gg_ext_port_interface overrides
	virtual uint8_t peripheral_r() override;
	virtual void peripheral_w(uint8_t data) override;

private:
	DECLARE_WRITE_LINE_MEMBER(th_pin_w);
	DECLARE_READ32_MEMBER(pixel_r);

>>>>>>> upstream/master
	required_device<sms_control_port_device> m_subctrl_port;
};


// device type definition
<<<<<<< HEAD
extern const device_type SMS_CTRL_ADAPTOR;


#endif
=======
DECLARE_DEVICE_TYPE(SMS_CTRL_ADAPTOR, sms_ctrl_adaptor_device)


#endif // MAME_BUS_GAMEGEAR_SMSCRTLADP_H
>>>>>>> upstream/master
