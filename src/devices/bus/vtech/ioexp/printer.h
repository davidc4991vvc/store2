// license:GPL-2.0+
// copyright-holders:Dirk Best
/***************************************************************************

    VTech Laser/VZ Printer Interface

    Dick Smith Electronics X-7320

***************************************************************************/

<<<<<<< HEAD
#pragma once

#ifndef __VTECH_IOEXP_PRINTER_H__
#define __VTECH_IOEXP_PRINTER_H__

#include "emu.h"
=======
#ifndef MAME_BUS_VTECH_IOEXP_PRINTER_H
#define MAME_BUS_VTECH_IOEXP_PRINTER_H

#pragma once

>>>>>>> upstream/master
#include "ioexp.h"
#include "bus/centronics/ctronics.h"


//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

// ======================> printer_interface_device

<<<<<<< HEAD
class printer_interface_device : public device_t, public device_ioexp_interface
{
public:
	// construction/destruction
	printer_interface_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

=======
class vtech_printer_interface_device : public device_t, public device_vtech_ioexp_interface
{
public:
	// construction/destruction
	vtech_printer_interface_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

protected:
	virtual void device_add_mconfig(machine_config &config) override;
	virtual void device_start() override;
	virtual void device_reset() override;

private:
>>>>>>> upstream/master
	DECLARE_WRITE_LINE_MEMBER( busy_w );
	DECLARE_READ8_MEMBER( busy_r );
	DECLARE_WRITE8_MEMBER( strobe_w );

<<<<<<< HEAD
protected:
	virtual machine_config_constructor device_mconfig_additions() const;
	virtual void device_start();
	virtual void device_reset();

private:
=======
>>>>>>> upstream/master
	required_device<centronics_device> m_centronics;
	required_device<output_latch_device> m_latch;

	int m_centronics_busy;
};

// device type definition
<<<<<<< HEAD
extern const device_type PRINTER_INTERFACE;

#endif // __VTECH_IOEXP_PRINTER_H__
=======
DECLARE_DEVICE_TYPE(VTECH_PRINTER_INTERFACE, vtech_printer_interface_device)

#endif // MAME_BUS_VTECH_IOEXP_PRINTER_H
>>>>>>> upstream/master
