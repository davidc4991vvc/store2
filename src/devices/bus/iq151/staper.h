// license:BSD-3-Clause
// copyright-holders:Sandro Ronco
<<<<<<< HEAD
#pragma once

#ifndef __IQ151_STAPER_H__
#define __IQ151_STAPER_H__

#include "emu.h"
=======
#ifndef MAME_BUS_IQ151_STAPER_H
#define MAME_BUS_IQ151_STAPER_H

#pragma once

>>>>>>> upstream/master
#include "iq151.h"
#include "machine/i8255.h"
#include "imagedev/printer.h"

//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

// ======================> iq151_staper_device

class iq151_staper_device :
		public device_t,
		public device_iq151cart_interface
{
public:
	// construction/destruction
<<<<<<< HEAD
	iq151_staper_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// optional information overrides
	virtual machine_config_constructor device_mconfig_additions() const;

	// i8255 callbacks
	DECLARE_READ8_MEMBER( ppi_porta_r );
	DECLARE_WRITE8_MEMBER( ppi_portb_w );
	DECLARE_WRITE8_MEMBER( ppi_portc_w );

protected:
	// device-level overrides
	virtual void device_start();
	virtual void device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr);

	// iq151cart_interface overrides
	virtual void io_read(offs_t offset, UINT8 &data);
	virtual void io_write(offs_t offset, UINT8 data);

private:
=======
	iq151_staper_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr) override;

	// optional information overrides
	virtual void device_add_mconfig(machine_config &config) override;

	// iq151cart_interface overrides
	virtual void io_read(offs_t offset, uint8_t &data) override;
	virtual void io_write(offs_t offset, uint8_t data) override;

private:
	// i8255 callbacks
	DECLARE_READ8_MEMBER( ppi_porta_r );
	DECLARE_WRITE8_MEMBER( ppi_portb_w );
	DECLARE_WRITE8_MEMBER( ppi_portc_w );
>>>>>>> upstream/master

	static const device_timer_id TIMER_PRINTER = 0;

	required_device<i8255_device>           m_ppi;
	required_device<printer_image_device>   m_printer;

	emu_timer*      m_printer_timer;
<<<<<<< HEAD
	UINT8           m_ppi_portc;
=======
	uint8_t           m_ppi_portc;
>>>>>>> upstream/master
};


// device type definition
<<<<<<< HEAD
extern const device_type IQ151_STAPER;

#endif  /* __IQ151_STAPER_H__ */
=======
DECLARE_DEVICE_TYPE(IQ151_STAPER, iq151_staper_device)

#endif // MAME_BUS_IQ151_STAPER_H
>>>>>>> upstream/master
