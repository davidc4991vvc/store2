// license:BSD-3-Clause
// copyright-holders:Curt Coder
/**********************************************************************

    COMX PL-80 plotter emulation

**********************************************************************/

<<<<<<< HEAD
#pragma once

#ifndef __COMX_PL80__
#define __COMX_PL80__

#include "emu.h"
=======
#ifndef MAME_BUS_CENTRONICS_COMXPL80_H
#define MAME_BUS_CENTRONICS_COMXPL80_H

#pragma once

>>>>>>> upstream/master
#include "cpu/m6805/m6805.h"
#include "bus/centronics/ctronics.h"



//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

// ======================> comx_pl80_device

class comx_pl80_device :  public device_t,
	public device_centronics_peripheral_interface
{
public:
	// construction/destruction
<<<<<<< HEAD
	comx_pl80_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// optional information overrides
	virtual const rom_entry *device_rom_region() const;
	virtual machine_config_constructor device_mconfig_additions() const;
	virtual ioport_constructor device_input_ports() const;
=======
	comx_pl80_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
>>>>>>> upstream/master

	// not really public
	DECLARE_WRITE8_MEMBER( pa_w );
	DECLARE_WRITE8_MEMBER( pb_w );
	DECLARE_WRITE8_MEMBER( pc_w );
	DECLARE_READ8_MEMBER( pd_r );

protected:
	// device-level overrides
<<<<<<< HEAD
	virtual void device_start();
	virtual void device_reset();

	virtual DECLARE_WRITE_LINE_MEMBER( input_data0 ) { if (state) m_data |= 0x01; else m_data &= ~0x01; }
	virtual DECLARE_WRITE_LINE_MEMBER( input_data1 ) { if (state) m_data |= 0x02; else m_data &= ~0x02; }
	virtual DECLARE_WRITE_LINE_MEMBER( input_data2 ) { if (state) m_data |= 0x04; else m_data &= ~0x04; }
	virtual DECLARE_WRITE_LINE_MEMBER( input_data3 ) { if (state) m_data |= 0x08; else m_data &= ~0x08; }
	virtual DECLARE_WRITE_LINE_MEMBER( input_data4 ) { if (state) m_data |= 0x10; else m_data &= ~0x10; }
	virtual DECLARE_WRITE_LINE_MEMBER( input_data5 ) { if (state) m_data |= 0x20; else m_data &= ~0x20; }
	virtual DECLARE_WRITE_LINE_MEMBER( input_data6 ) { if (state) m_data |= 0x40; else m_data &= ~0x40; }
	virtual DECLARE_WRITE_LINE_MEMBER( input_data7 ) { if (state) m_data |= 0x80; else m_data &= ~0x80; }
=======
	virtual void device_start() override;
	virtual void device_reset() override;

	// optional information overrides
	virtual const tiny_rom_entry *device_rom_region() const override;
	virtual void device_add_mconfig(machine_config &config) override;
	virtual ioport_constructor device_input_ports() const override;

	virtual DECLARE_WRITE_LINE_MEMBER( input_data0 ) override { if (state) m_data |= 0x01; else m_data &= ~0x01; }
	virtual DECLARE_WRITE_LINE_MEMBER( input_data1 ) override { if (state) m_data |= 0x02; else m_data &= ~0x02; }
	virtual DECLARE_WRITE_LINE_MEMBER( input_data2 ) override { if (state) m_data |= 0x04; else m_data &= ~0x04; }
	virtual DECLARE_WRITE_LINE_MEMBER( input_data3 ) override { if (state) m_data |= 0x08; else m_data &= ~0x08; }
	virtual DECLARE_WRITE_LINE_MEMBER( input_data4 ) override { if (state) m_data |= 0x10; else m_data &= ~0x10; }
	virtual DECLARE_WRITE_LINE_MEMBER( input_data5 ) override { if (state) m_data |= 0x20; else m_data &= ~0x20; }
	virtual DECLARE_WRITE_LINE_MEMBER( input_data6 ) override { if (state) m_data |= 0x40; else m_data &= ~0x40; }
	virtual DECLARE_WRITE_LINE_MEMBER( input_data7 ) override { if (state) m_data |= 0x80; else m_data &= ~0x80; }
>>>>>>> upstream/master

private:
	required_memory_region m_plotter;
	required_ioport m_font;
	required_ioport m_sw;

	// PL-80 plotter state
<<<<<<< HEAD
	UINT16 m_font_addr;         // font ROM pack address latch
	UINT8 m_x_motor_phase;      // X motor phase
	UINT8 m_y_motor_phase;      // Y motor phase
	UINT8 m_z_motor_phase;      // Z motor phase
	UINT8 m_plotter_data;       // plotter data bus
	int m_plotter_ack;          // plotter acknowledge
	int m_plotter_online;       // online LED

	UINT8 m_data;
=======
	uint16_t m_font_addr;         // font ROM pack address latch
	uint8_t m_x_motor_phase;      // X motor phase
	uint8_t m_y_motor_phase;      // Y motor phase
	uint8_t m_z_motor_phase;      // Z motor phase
	uint8_t m_plotter_data;       // plotter data bus
	int m_plotter_ack;          // plotter acknowledge
	int m_plotter_online;       // online LED

	uint8_t m_data;
>>>>>>> upstream/master
};


// device type definition
<<<<<<< HEAD
extern const device_type COMX_PL80;



#endif
=======
DECLARE_DEVICE_TYPE(COMX_PL80, comx_pl80_device)



#endif // MAME_BUS_CENTRONICS_COMXPL80_H
>>>>>>> upstream/master
