// license:BSD-3-Clause
// copyright-holders:Fabio Priuli
/**********************************************************************

    Sega Master System "Gender Adapter" emulation

**********************************************************************/

<<<<<<< HEAD
#pragma once

#ifndef __SMS_GENDER_ADAPTER__
#define __SMS_GENDER_ADAPTER__


#include "emu.h"
=======
#ifndef MAME_BUS_SMS_EXP_GENDER_H
#define MAME_BUS_SMS_EXP_GENDER_H

#pragma once


>>>>>>> upstream/master
#include "smsexp.h"
#include "bus/sega8/sega8_slot.h"



//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

// ======================> sms_gender_adapter_device

class sms_gender_adapter_device : public device_t,
							public device_sms_expansion_slot_interface
{
public:
	// construction/destruction
<<<<<<< HEAD
	sms_gender_adapter_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device_sms_expansion_slot_interface overrides
	virtual DECLARE_READ8_MEMBER(read);
	virtual DECLARE_WRITE8_MEMBER(write);
	virtual DECLARE_WRITE8_MEMBER(write_mapper);
	virtual DECLARE_READ8_MEMBER(read_ram);
	virtual DECLARE_WRITE8_MEMBER(write_ram);

	virtual int get_lphaser_xoffs();

protected:
	// device-level overrides
	virtual void device_start();
	virtual machine_config_constructor device_mconfig_additions() const;
=======
	sms_gender_adapter_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// device_sms_expansion_slot_interface overrides
	virtual DECLARE_READ8_MEMBER(read) override;
	virtual DECLARE_WRITE8_MEMBER(write) override;
	virtual DECLARE_WRITE8_MEMBER(write_mapper) override;
	virtual DECLARE_READ8_MEMBER(read_ram) override;
	virtual DECLARE_WRITE8_MEMBER(write_ram) override;

	virtual int get_lphaser_xoffs() override;

protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_add_mconfig(machine_config &config) override;
>>>>>>> upstream/master

private:
	required_device<sega8_cart_slot_device> m_subslot;
};


// device type definition
<<<<<<< HEAD
extern const device_type SMS_GENDER_ADAPTER;


#endif
=======
DECLARE_DEVICE_TYPE(SMS_GENDER_ADAPTER, sms_gender_adapter_device)

#endif // MAME_BUS_SMS_EXP_GENDER_H
>>>>>>> upstream/master
