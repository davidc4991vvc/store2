// license:GPL-2.0+
// copyright-holders:Dirk Best
/**********************************************************************

    EPSON SIO port emulation

**********************************************************************/

<<<<<<< HEAD
#pragma once

#ifndef __EPSON_SIO_H__
#define __EPSON_SIO_H__

#include "emu.h"
=======
#ifndef MAME_BUS_EPSON_SIO_EPSON_SIO_H
#define MAME_BUS_EPSON_SIO_EPSON_SIO_H

#pragma once

>>>>>>> upstream/master


//**************************************************************************
//  INTERFACE CONFIGURATION MACROS
//**************************************************************************

#define MCFG_EPSON_SIO_ADD(_tag, _def_slot) \
	MCFG_DEVICE_ADD(_tag, EPSON_SIO, 0) \
	MCFG_DEVICE_SLOT_INTERFACE(epson_sio_devices, _def_slot, false)

#define MCFG_EPSON_SIO_RX(_rx) \
<<<<<<< HEAD
	downcast<epson_sio_device *>(device)->set_rx_callback(DEVCB_##_rx);

#define MCFG_EPSON_SIO_PIN(_pin) \
	downcast<epson_sio_device *>(device)->set_pin_callback(DEVCB_##_pin);
=======
	devcb = &downcast<epson_sio_device *>(device)->set_rx_callback(DEVCB_##_rx);

#define MCFG_EPSON_SIO_PIN(_pin) \
	devcb = &downcast<epson_sio_device *>(device)->set_pin_callback(DEVCB_##_pin);
>>>>>>> upstream/master


//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

class device_epson_sio_interface;


class epson_sio_device : public device_t,
							public device_slot_interface
{
public:
	// construction/destruction
<<<<<<< HEAD
	epson_sio_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
	virtual ~epson_sio_device();

	// callbacks
	template<class _rx> void set_rx_callback(_rx rx) { m_write_rx.set_callback(rx); }
	template<class _pin> void set_pin_callback(_pin pin) { m_write_pin.set_callback(pin); }
=======
	epson_sio_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
	virtual ~epson_sio_device();

	// callbacks
	template<class _rx> devcb_base &set_rx_callback(_rx rx) { return m_write_rx.set_callback(rx); }
	template<class _pin> devcb_base &set_pin_callback(_pin pin) { return m_write_pin.set_callback(pin); }
>>>>>>> upstream/master

	// called from owner
	DECLARE_WRITE_LINE_MEMBER( tx_w );
	DECLARE_WRITE_LINE_MEMBER( pout_w );

	// called from subdevice
	DECLARE_WRITE_LINE_MEMBER( rx_w ) { m_write_rx(state); }
	DECLARE_WRITE_LINE_MEMBER( pin_w ) { m_write_pin(state); }

protected:
	// device-level overrides
<<<<<<< HEAD
	virtual void device_start();
	virtual void device_reset();
=======
	virtual void device_start() override;
	virtual void device_reset() override;
>>>>>>> upstream/master

	device_epson_sio_interface *m_cart;

private:
	devcb_write_line m_write_rx;
	devcb_write_line m_write_pin;
};


// class representing interface-specific live sio device
class device_epson_sio_interface : public device_slot_card_interface
{
public:
	// construction/destruction
<<<<<<< HEAD
	device_epson_sio_interface(const machine_config &mconfig, device_t &device);
=======
>>>>>>> upstream/master
	virtual ~device_epson_sio_interface();

	virtual void tx_w(int state) { };
	virtual void pout_w(int state) { };

protected:
<<<<<<< HEAD
=======
	device_epson_sio_interface(const machine_config &mconfig, device_t &device);

>>>>>>> upstream/master
	epson_sio_device *m_slot;
};


// device type definition
<<<<<<< HEAD
extern const device_type EPSON_SIO;
=======
DECLARE_DEVICE_TYPE(EPSON_SIO, epson_sio_device)
>>>>>>> upstream/master


// supported devices
SLOT_INTERFACE_EXTERN( epson_sio_devices );


<<<<<<< HEAD
#endif // __EPSON_SIO_H__
=======
#endif // MAME_BUS_EPSON_SIO_EPSON_SIO_H
>>>>>>> upstream/master
