// license:BSD-3-Clause
// copyright-holders:Curt Coder
/**********************************************************************

    Western Digital WD1002A-WX1 Winchester Disk Controller emulation

**********************************************************************/

<<<<<<< HEAD
#pragma once

#ifndef __ISA_WD1002A_WX1__
#define __ISA_WD1002A_WX1__

#include "emu.h"
=======
#ifndef MAME_BUS_ISA_WD1002A_WX1_H
#define MAME_BUS_ISA_WD1002A_WX1_H

#pragma once

>>>>>>> upstream/master
#include "isa.h"



//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

// ======================> isa16_ide_device

class isa8_wd1002a_wx1_device : public device_t,
								public device_isa8_card_interface
{
public:
	// construction/destruction
<<<<<<< HEAD
	isa8_wd1002a_wx1_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// optional information overrides
	virtual const rom_entry *device_rom_region() const;

protected:
	// device-level overrides
	virtual void device_start();
	virtual void device_reset();
=======
	isa8_wd1002a_wx1_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// optional information overrides
	virtual const tiny_rom_entry *device_rom_region() const override;

protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;
>>>>>>> upstream/master
};


// device type definition
<<<<<<< HEAD
extern const device_type ISA8_WD1002A_WX1;


#endif
=======
DECLARE_DEVICE_TYPE(ISA8_WD1002A_WX1, isa8_wd1002a_wx1_device)


#endif // MAME_BUS_ISA_WD1002A_WX1_H
>>>>>>> upstream/master
