// license:BSD-3-Clause
// copyright-holders:Curt Coder
/**********************************************************************

    IBM 5150 83-key keyboard emulation

*********************************************************************/

<<<<<<< HEAD
#pragma once

#ifndef __PC_KBD_IBM_PC_83__
#define __PC_KBD_IBM_PC_83__

#include "emu.h"
=======
#ifndef MAME_BUS_PC_KBD_PC83_H
#define MAME_BUS_PC_KBD_PC83_H

#pragma once

>>>>>>> upstream/master
#include "cpu/mcs48/mcs48.h"
#include "pc_kbdc.h"
#include "machine/rescap.h"



//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

// ======================> ibm_pc_83_keyboard_device

class ibm_pc_83_keyboard_device :  public device_t,
									public device_pc_kbd_interface
{
public:
	// construction/destruction
<<<<<<< HEAD
	ibm_pc_83_keyboard_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// optional information overrides
	virtual const rom_entry *device_rom_region() const;
	virtual machine_config_constructor device_mconfig_additions() const;
	virtual ioport_constructor device_input_ports() const;

	DECLARE_WRITE8_MEMBER( bus_w );
	DECLARE_READ8_MEMBER( p1_r );
	DECLARE_WRITE8_MEMBER( p2_w );
	DECLARE_READ8_MEMBER( t1_r );

protected:
	// device-level overrides
	virtual void device_start();
	virtual void device_reset();

	// device_pc_kbd_interface overrides
	virtual DECLARE_WRITE_LINE_MEMBER( clock_write ) { };
	virtual DECLARE_WRITE_LINE_MEMBER( data_write ) { };

private:
	required_device<cpu_device> m_maincpu;
	required_ioport m_dr00;
	required_ioport m_dr01;
	required_ioport m_dr02;
	required_ioport m_dr03;
	required_ioport m_dr04;
	required_ioport m_dr05;
	required_ioport m_dr06;
	required_ioport m_dr07;
	required_ioport m_dr08;
	required_ioport m_dr09;
	required_ioport m_dr10;
	required_ioport m_dr11;
	required_ioport m_dr12;
	required_ioport m_dr13;
	required_ioport m_dr14;
	required_ioport m_dr15;
	required_ioport m_dr16;
	required_ioport m_dr17;
	required_ioport m_dr18;
	required_ioport m_dr19;
	required_ioport m_dr20;
	required_ioport m_dr21;
	required_ioport m_dr22;
	required_ioport m_dr23;

	UINT8 m_cnt;
=======
	ibm_pc_83_keyboard_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;

	// optional information overrides
	virtual const tiny_rom_entry *device_rom_region() const override;
	virtual void device_add_mconfig(machine_config &config) override;
	virtual ioport_constructor device_input_ports() const override;

	// device_pc_kbd_interface overrides
	virtual DECLARE_WRITE_LINE_MEMBER( clock_write ) override { };
	virtual DECLARE_WRITE_LINE_MEMBER( data_write ) override { };

private:
	DECLARE_WRITE8_MEMBER( bus_w );
	DECLARE_READ8_MEMBER( p1_r );
	DECLARE_WRITE8_MEMBER( p2_w );
	DECLARE_READ_LINE_MEMBER( t0_r );

	required_device<cpu_device> m_maincpu;
	required_ioport_array<24> m_dr;

	uint8_t m_cnt;
>>>>>>> upstream/master
};


// device type definition
<<<<<<< HEAD
extern const device_type PC_KBD_IBM_PC_83;



#endif
=======
DECLARE_DEVICE_TYPE(PC_KBD_IBM_PC_83, ibm_pc_83_keyboard_device)


#endif // MAME_BUS_PC_KBD_PC83_H
>>>>>>> upstream/master
