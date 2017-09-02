// license:BSD-3-Clause
// copyright-holders:Fabio Priuli
/**********************************************************************

    Sega Master System expansion slot emulation

**********************************************************************


**********************************************************************/

<<<<<<< HEAD
#pragma once

#ifndef __SMS_EXPANSION_SLOT__
#define __SMS_EXPANSION_SLOT__

#include "emu.h"
=======
#ifndef MAME_BUS_SMS_EXP_SMSEXP_H
#define MAME_BUS_SMS_EXP_SMSEXP_H

#pragma once

>>>>>>> upstream/master



//**************************************************************************
//  INTERFACE CONFIGURATION MACROS
//**************************************************************************

#define MCFG_SMS_EXPANSION_ADD(_tag, _slot_intf, _def_slot) \
	MCFG_DEVICE_ADD(_tag, SMS_EXPANSION_SLOT, 0) \
	MCFG_DEVICE_SLOT_INTERFACE(_slot_intf, _def_slot, false)



//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

<<<<<<< HEAD
// ======================> sms_expansion_slot_device

class device_sms_expansion_slot_interface;

class sms_expansion_slot_device : public device_t,
								public device_slot_interface
{
public:
	// construction/destruction
	sms_expansion_slot_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
	virtual ~sms_expansion_slot_device();

	// reading and writing
	DECLARE_READ8_MEMBER(read);
	DECLARE_WRITE8_MEMBER(write);
	DECLARE_WRITE8_MEMBER(write_mapper);
	DECLARE_READ8_MEMBER(read_ram);
	DECLARE_WRITE8_MEMBER(write_ram);

	int get_lphaser_xoffs();

	device_sms_expansion_slot_interface *m_device;

protected:
	// device-level overrides
	virtual void device_start();
};


// ======================> device_sms_expansion_slot_interface

// class representing interface-specific live sms_expansion card
class device_sms_expansion_slot_interface : public device_slot_card_interface
{
public:
	// construction/destruction
	device_sms_expansion_slot_interface(const machine_config &mconfig, device_t &device);
	virtual ~device_sms_expansion_slot_interface();

	// reading and writing
	virtual DECLARE_READ8_MEMBER(read) { return 0xff; };
	virtual DECLARE_WRITE8_MEMBER(write) { };
	virtual DECLARE_WRITE8_MEMBER(write_mapper) {};
	virtual DECLARE_READ8_MEMBER(read_ram) { return 0xff; };
	virtual DECLARE_WRITE8_MEMBER(write_ram) { };

	virtual int get_lphaser_xoffs() { return 0; };
=======
// ======================> device_sms_expansion_slot_interface

// class representing interface-specific live sms_expansion card
class device_sms_expansion_slot_interface : public device_slot_card_interface
{
public:
	// construction/destruction
	virtual ~device_sms_expansion_slot_interface();

	// reading and writing
	virtual DECLARE_READ8_MEMBER(read) { return 0xff; }
	virtual DECLARE_WRITE8_MEMBER(write) { }
	virtual DECLARE_WRITE8_MEMBER(write_mapper) { }
	virtual DECLARE_READ8_MEMBER(read_ram) { return 0xff; }
	virtual DECLARE_WRITE8_MEMBER(write_ram) { }

	virtual int get_lphaser_xoffs() { return 0; }

protected:
	device_sms_expansion_slot_interface(const machine_config &mconfig, device_t &device);
};


// ======================> sms_expansion_slot_device

class sms_expansion_slot_device : public device_t,
								public device_slot_interface
{
public:
	// construction/destruction
	sms_expansion_slot_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
	virtual ~sms_expansion_slot_device();

	// reading and writing
	DECLARE_READ8_MEMBER(read) { return m_device ? m_device->read(space, offset, mem_mask) : 0xff; }
	DECLARE_WRITE8_MEMBER(write) { if (m_device) m_device->write(space, offset, data, mem_mask); }
	DECLARE_WRITE8_MEMBER(write_mapper) { if (m_device) m_device->write_mapper(space, offset, data, mem_mask); }
	DECLARE_READ8_MEMBER(read_ram) { return m_device ? m_device->read_ram(space, offset, mem_mask) : 0xff; }
	DECLARE_WRITE8_MEMBER(write_ram) { if (m_device) m_device->write_ram(space, offset, data, mem_mask); }

	int get_lphaser_xoffs() { return m_device ? m_device->get_lphaser_xoffs() : 0; }

	bool device_present() const { return bool(m_device); }

protected:
	// device-level overrides
	virtual void device_start() override;

	device_sms_expansion_slot_interface *m_device;
>>>>>>> upstream/master
};


// device type definition
<<<<<<< HEAD
extern const device_type SMS_EXPANSION_SLOT;


// slot devices
#include "gender.h"
=======
DECLARE_DEVICE_TYPE(SMS_EXPANSION_SLOT, sms_expansion_slot_device)

>>>>>>> upstream/master

SLOT_INTERFACE_EXTERN( sms_expansion_devices );


<<<<<<< HEAD
#endif
=======
#endif // MAME_BUS_SMS_EXP_SMSEXP_H
>>>>>>> upstream/master
