// license:GPL-2.0+
// copyright-holders:Dirk Best
/**********************************************************************

    Epson LX-800 dot matrix printer emulation

**********************************************************************/

<<<<<<< HEAD
#pragma once

#ifndef __EPSON_LX800__
#define __EPSON_LX800__

#include "emu.h"
=======
#ifndef MAME_BUS_CENTRONICS_EPSON_LX800_H
#define MAME_BUS_CENTRONICS_EPSON_LX800_H

#pragma once

>>>>>>> upstream/master
#include "ctronics.h"
#include "cpu/upd7810/upd7810.h"
#include "machine/e05a03.h"
#include "sound/beep.h"



//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

<<<<<<< HEAD
// ======================> epson_lx800_t

class epson_lx800_t :  public device_t,
=======
// ======================> epson_lx800_device

class epson_lx800_device :  public device_t,
>>>>>>> upstream/master
						public device_centronics_peripheral_interface
{
public:
	// construction/destruction
<<<<<<< HEAD
	epson_lx800_t(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
	epson_lx800_t(const machine_config &mconfig, device_type type, const char *name, const char *tag, device_t *owner, UINT32 clock, const char *shortname, const char *source);

	// optional information overrides
	virtual const rom_entry *device_rom_region() const;
	virtual machine_config_constructor device_mconfig_additions() const;
	virtual ioport_constructor device_input_ports() const;

=======
	epson_lx800_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	DECLARE_READ8_MEMBER(centronics_data_r);
	DECLARE_WRITE_LINE_MEMBER(centronics_pe_w);
	DECLARE_WRITE_LINE_MEMBER(paperempty_led_w);
	DECLARE_WRITE_LINE_MEMBER(reset_w);

protected:
	epson_lx800_device(const machine_config &mconfig, device_type type, const char *tag, device_t *owner, uint32_t clock);

	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;

	// optional information overrides
	virtual const tiny_rom_entry *device_rom_region() const override;
	virtual void device_add_mconfig(machine_config &config) override;
	virtual ioport_constructor device_input_ports() const override;

private:
>>>>>>> upstream/master
	DECLARE_READ8_MEMBER(porta_r);
	DECLARE_WRITE8_MEMBER(porta_w);
	DECLARE_READ8_MEMBER(portc_r);
	DECLARE_WRITE8_MEMBER(portc_w);
<<<<<<< HEAD
	DECLARE_READ8_MEMBER(centronics_data_r);
	DECLARE_WRITE_LINE_MEMBER(centronics_pe_w);
	DECLARE_WRITE_LINE_MEMBER(paperempty_led_w);
	DECLARE_WRITE_LINE_MEMBER(reset_w);
=======

>>>>>>> upstream/master
	DECLARE_READ_LINE_MEMBER(an0_r);
	DECLARE_READ_LINE_MEMBER(an1_r);
	DECLARE_READ_LINE_MEMBER(an2_r);
	DECLARE_READ_LINE_MEMBER(an3_r);
	DECLARE_READ_LINE_MEMBER(an4_r);
	DECLARE_READ_LINE_MEMBER(an5_r);

<<<<<<< HEAD
protected:
	// device-level overrides
	virtual void device_start();
	virtual void device_reset();

private:
=======
>>>>>>> upstream/master
	required_device<cpu_device> m_maincpu;
	required_device<beep_device> m_beep;
};



// device type definition
<<<<<<< HEAD
extern const device_type EPSON_LX800;



#endif
=======
DECLARE_DEVICE_TYPE(EPSON_LX800, epson_lx800_device)



#endif // MAME_BUS_CENTRONICS_EPSON_LX800_H
>>>>>>> upstream/master
