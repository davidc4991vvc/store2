// license:GPL-2.0+
// copyright-holders:Dirk Best
/**********************************************************************

    Epson EX-800 dot matrix printer emulation

**********************************************************************/

<<<<<<< HEAD
#pragma once

#ifndef __EPSON_EX800__
#define __EPSON_EX800__

#include "emu.h"
=======
#ifndef MAME_BUS_CENTRONICS_EPSON_EX800_H
#define MAME_BUS_CENTRONICS_EPSON_EX800_H

#pragma once

>>>>>>> upstream/master
#include "ctronics.h"
#include "cpu/upd7810/upd7810.h"
#include "sound/beep.h"



//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

<<<<<<< HEAD
// ======================> epson_ex800_t

class epson_ex800_t :  public device_t,
=======
// ======================> epson_ex800_device

class epson_ex800_device :  public device_t,
>>>>>>> upstream/master
						public device_centronics_peripheral_interface
{
public:
	// construction/destruction
<<<<<<< HEAD
	epson_ex800_t(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
	epson_ex800_t(const machine_config &mconfig, device_type type, const char *name, const char *tag, device_t *owner, UINT32 clock, const char *shortname, const char *source);

	// optional information overrides
	virtual const rom_entry *device_rom_region() const;
	virtual machine_config_constructor device_mconfig_additions() const;
	virtual ioport_constructor device_input_ports() const;

	DECLARE_READ8_MEMBER(porta_r);
	DECLARE_READ8_MEMBER(portb_r);
	DECLARE_READ8_MEMBER(portc_r);
	DECLARE_WRITE8_MEMBER(porta_w);
	DECLARE_WRITE8_MEMBER(portb_w);
	DECLARE_WRITE8_MEMBER(portc_w);
=======
	epson_ex800_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

>>>>>>> upstream/master
	DECLARE_READ8_MEMBER(devsel_r);
	DECLARE_WRITE8_MEMBER(devsel_w);
	DECLARE_READ8_MEMBER(gate5a_r);
	DECLARE_WRITE8_MEMBER(gate5a_w);
	DECLARE_READ8_MEMBER(iosel_r);
	DECLARE_WRITE8_MEMBER(iosel_w);
	DECLARE_READ8_MEMBER(gate7a_r);
	DECLARE_WRITE8_MEMBER(gate7a_w);

	DECLARE_INPUT_CHANGED_MEMBER(online_switch);

protected:
	// device-level overrides
<<<<<<< HEAD
	virtual void device_start();
	virtual void device_reset();

private:
=======
	virtual void device_start() override;
	virtual void device_reset() override;

	// optional information overrides
	virtual const tiny_rom_entry *device_rom_region() const override;
	virtual void device_add_mconfig(machine_config &config) override;
	virtual ioport_constructor device_input_ports() const override;

private:
	DECLARE_READ8_MEMBER(porta_r);
	DECLARE_READ8_MEMBER(portb_r);
	DECLARE_READ8_MEMBER(portc_r);
	DECLARE_WRITE8_MEMBER(porta_w);
	DECLARE_WRITE8_MEMBER(portb_w);
	DECLARE_WRITE8_MEMBER(portc_w);

>>>>>>> upstream/master
	required_device<cpu_device> m_maincpu;
	required_device<beep_device> m_beeper;

	int m_irq_state;
};



// device type definition
<<<<<<< HEAD
extern const device_type EPSON_EX800;



#endif
=======
DECLARE_DEVICE_TYPE(EPSON_EX800, epson_ex800_device)



#endif // MAME_BUS_CENTRONICS_EPSON_EX800_H
>>>>>>> upstream/master
