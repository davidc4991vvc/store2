// license:BSD-3-Clause
// copyright-holders:Curt Coder, Mike Naberezny
/**********************************************************************

    SSE SoftBox emulation

**********************************************************************/

<<<<<<< HEAD
#pragma once

#ifndef __PET_SOFTBOX__
#define __PET_SOFTBOX__
=======
#ifndef MAME_BUS_IEEE488_SOFTBOX_H
#define MAME_BUS_IEEE488_SOFTBOX_H

#pragma once
>>>>>>> upstream/master

#include "ieee488.h"
#include "bus/rs232/rs232.h"
#include "cpu/z80/z80.h"
#include "imagedev/harddriv.h"
#include "machine/corvushd.h"
#include "machine/com8116.h"
#include "machine/i8251.h"
#include "machine/i8255.h"



//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

// ======================> softbox_device

class softbox_device :  public device_t,
						public device_ieee488_interface
{
public:
	// construction/destruction
<<<<<<< HEAD
	softbox_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// optional information overrides
	virtual const rom_entry *device_rom_region() const;
	virtual machine_config_constructor device_mconfig_additions() const;
	virtual ioport_constructor device_input_ports() const;

	DECLARE_WRITE8_MEMBER( dbrg_w );

=======
	softbox_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	DECLARE_WRITE8_MEMBER( dbrg_w );

protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset_after_children() override;

	// optional information overrides
	virtual const tiny_rom_entry *device_rom_region() const override;
	virtual void device_add_mconfig(machine_config &config) override;
	virtual ioport_constructor device_input_ports() const override;

	// device_ieee488_interface overrides
	virtual void ieee488_ifc(int state) override;

private:
>>>>>>> upstream/master
	DECLARE_READ8_MEMBER( ppi0_pa_r );
	DECLARE_WRITE8_MEMBER( ppi0_pb_w );

	DECLARE_READ8_MEMBER( ppi1_pa_r );
	DECLARE_WRITE8_MEMBER( ppi1_pb_w );
	DECLARE_READ8_MEMBER( ppi1_pc_r );
	DECLARE_WRITE8_MEMBER( ppi1_pc_w );

<<<<<<< HEAD
protected:
	// device-level overrides
	virtual void device_start();
	virtual void device_reset_after_children();

	// device_ieee488_interface overrides
	virtual void ieee488_ifc(int state);

private:
=======
>>>>>>> upstream/master
	enum
	{
		LED_A,
		LED_B,
		LED_READY
	};

	required_device<cpu_device> m_maincpu;
	required_device<com8116_device> m_dbrg;
<<<<<<< HEAD
	required_device<corvus_hdc_t> m_hdc;
=======
	required_device<corvus_hdc_device> m_hdc;
>>>>>>> upstream/master

	int m_ifc;  // Tracks previous state of IEEE-488 IFC line
};


// device type definition
<<<<<<< HEAD
extern const device_type SOFTBOX;



#endif
=======
DECLARE_DEVICE_TYPE(SOFTBOX, softbox_device)


#endif // MAME_BUS_IEEE488_SOFTBOX_H
>>>>>>> upstream/master
