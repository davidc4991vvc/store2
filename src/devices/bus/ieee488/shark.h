// license:BSD-3-Clause
// copyright-holders:Curt Coder
/**********************************************************************

    Mator Systems SHARK Intelligent Winchester Disc Subsystem emulation

    35MB PRIAM DISKOS 3450 8" Winchester Hard Disk (-chs 525,5,? -ss ?)

**********************************************************************/

<<<<<<< HEAD
#pragma once

#ifndef __SHARK__
#define __SHARK__
=======
#ifndef MAME_BUS_IEEE488_SHARK_H
#define MAME_BUS_IEEE488_SHARK_H

#pragma once
>>>>>>> upstream/master

#include "ieee488.h"



//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

// ======================> mshark_device

class mshark_device :  public device_t,
						public device_ieee488_interface
{
public:
	// construction/destruction
<<<<<<< HEAD
	mshark_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// optional information overrides
	virtual const rom_entry *device_rom_region() const;
	virtual machine_config_constructor device_mconfig_additions() const;
	virtual ioport_constructor device_input_ports() const;

protected:
	// device-level overrides
	virtual void device_start();
=======
	mshark_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

protected:
	// device-level overrides
	virtual void device_start() override;

	// optional information overrides
	virtual const tiny_rom_entry *device_rom_region() const override;
	virtual void device_add_mconfig(machine_config &config) override;
	virtual ioport_constructor device_input_ports() const override;
>>>>>>> upstream/master

private:
	required_device<cpu_device> m_maincpu;
};


// device type definition
<<<<<<< HEAD
extern const device_type SHARK;



#endif
=======
DECLARE_DEVICE_TYPE(MSHARK, mshark_device)

#endif // MAME_BUS_IEEE488_SHARK_H
>>>>>>> upstream/master
