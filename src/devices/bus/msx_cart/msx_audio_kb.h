// license:BSD-3-Clause
// copyright-holders:Wilbert Pol
<<<<<<< HEAD
#ifndef __MSX_AUDIO_KB_H__
#define __MSX_AUDIO_KB_H__


extern const device_type MSX_AUDIO_KBDC_PORT;
=======
#ifndef MAME_BUS_MSX_CART_MSX_AUDIO_KB_H
#define MAME_BUS_MSX_CART_MSX_AUDIO_KB_H

#pragma once


DECLARE_DEVICE_TYPE(MSX_AUDIO_KBDC_PORT, msx_audio_kbdc_port_device)
>>>>>>> upstream/master


#define MCFG_MSX_AUDIO_KBDC_PORT_ADD(_tag, _slot_intf, _def_slot) \
	MCFG_DEVICE_ADD(_tag, MSX_AUDIO_KBDC_PORT, 0 ) \
	MCFG_DEVICE_SLOT_INTERFACE(_slot_intf, _def_slot, false)


class msx_audio_kb_port_interface : public device_slot_card_interface
{
public:
<<<<<<< HEAD
	// construction/destruction
	msx_audio_kb_port_interface(const machine_config &mconfig, device_t &device)
		: device_slot_card_interface(mconfig, device)
	{ };

	virtual DECLARE_READ8_MEMBER(read) { return 0xff; };
	virtual DECLARE_WRITE8_MEMBER(write) { };
};


class msx_audio_kbdc_port_device : public device_t,
							public device_slot_interface
{
public:
	// construction/destruction
	msx_audio_kbdc_port_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
=======

	virtual DECLARE_READ8_MEMBER(read) { return 0xff; }
	virtual DECLARE_WRITE8_MEMBER(write) { }

protected:
	// construction/destruction
	using device_slot_card_interface::device_slot_card_interface;
};


class msx_audio_kbdc_port_device : public device_t, public device_slot_interface
{
public:
	// construction/destruction
	msx_audio_kbdc_port_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// device-level overrides
	virtual void device_start() override;
>>>>>>> upstream/master

	// Physical connection simply consists of 8 input and 8 output lines split across 2 connectors
	DECLARE_WRITE8_MEMBER(write);
	DECLARE_READ8_MEMBER(read);

<<<<<<< HEAD
=======

protected:
>>>>>>> upstream/master
	msx_audio_kb_port_interface *m_keyboard;
};


SLOT_INTERFACE_EXTERN( msx_audio_keyboards );


<<<<<<< HEAD
#endif
=======
#endif // MAME_BUS_MSX_CART_MSX_AUDIO_KB_H
>>>>>>> upstream/master
