// license:BSD-3-Clause
// copyright-holders:Curt Coder
<<<<<<< HEAD
#pragma once

#ifndef __ABC_UNI800__
#define __ABC_UNI800__

#include "emu.h"
=======
#ifndef MAME_BUS_ABCBUS_UNI800_H
#define MAME_BUS_ABCBUS_UNI800_H

#pragma once

>>>>>>> upstream/master
#include "abcbus.h"



//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

// ======================> abc_uni800_device

class abc_uni800_device :  public device_t,
							public device_abcbus_card_interface
{
public:
	// construction/destruction
<<<<<<< HEAD
	abc_uni800_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// optional information overrides
	virtual const rom_entry *device_rom_region() const;

protected:
	// device-level overrides
	virtual void device_start();
	virtual void device_reset();

	// device_abcbus_interface overrides
	virtual void abcbus_cs(UINT8 data);
=======
	abc_uni800_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// optional information overrides
	virtual const tiny_rom_entry *device_rom_region() const override;

protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;

	// device_abcbus_interface overrides
	virtual void abcbus_cs(uint8_t data) override;
>>>>>>> upstream/master
};


// device type definition
<<<<<<< HEAD
extern const device_type ABC_UNI800;



#endif
=======
DECLARE_DEVICE_TYPE(ABC_UNI800, abc_uni800_device)

#endif // MAME_BUS_ABCBUS_UNI800_H
>>>>>>> upstream/master
