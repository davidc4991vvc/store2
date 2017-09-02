// license:BSD-3-Clause
// copyright-holders:Curt Coder
/**********************************************************************

    ColecoVision standard cartridge emulation

**********************************************************************/

<<<<<<< HEAD
#pragma once

#ifndef __COLECOVISION_STANDARD_CARTRIDGE__
#define __COLECOVISION_STANDARD_CARTRIDGE__
=======
#ifndef MAME_BUS_COLECO_STD_H
#define MAME_BUS_COLECO_STD_H

#pragma once
>>>>>>> upstream/master

#include "exp.h"



//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

// ======================> colecovision_standard_cartridge_device

class colecovision_standard_cartridge_device : public device_t,
												public device_colecovision_cartridge_interface
{
public:
	// construction/destruction
<<<<<<< HEAD
	colecovision_standard_cartridge_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

protected:
	// device-level overrides
	virtual void device_start();

	// device_colecovision_expansion_card_interface overrides
	virtual UINT8 bd_r(address_space &space, offs_t offset, UINT8 data, int _8000, int _a000, int _c000, int _e000);
=======
	colecovision_standard_cartridge_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

protected:
	// device-level overrides
	virtual void device_start() override;

	// device_colecovision_expansion_card_interface overrides
	virtual uint8_t bd_r(address_space &space, offs_t offset, uint8_t data, int _8000, int _a000, int _c000, int _e000) override;
>>>>>>> upstream/master
};


// device type definition
<<<<<<< HEAD
extern const device_type COLECOVISION_STANDARD;


#endif
=======
DECLARE_DEVICE_TYPE(COLECOVISION_STANDARD, colecovision_standard_cartridge_device)


#endif // MAME_BUS_COLECO_STD_H
>>>>>>> upstream/master
