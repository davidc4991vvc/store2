// license:BSD-3-Clause
// copyright-holders:Wilbert Pol
/**********************************************************************

    ColecoVision X-in-1 cartridge emulation

**********************************************************************/

<<<<<<< HEAD
#pragma once

#ifndef __COLECOVISION_XIN1_CARTRIDGE__
#define __COLECOVISION_XIN1_CARTRIDGE__
=======
#ifndef MAME_BUS_COLECO_XIN1_H
#define MAME_BUS_COLECO_XIN1_H

#pragma once
>>>>>>> upstream/master

#include "exp.h"



//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

// ======================> colecovision_xin1_cartridge_device

class colecovision_xin1_cartridge_device : public device_t,
												public device_colecovision_cartridge_interface
{
public:
	// construction/destruction
<<<<<<< HEAD
	colecovision_xin1_cartridge_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

protected:
	// device-level overrides
	virtual void device_start();
	virtual void device_reset();

	// device_colecovision_expansion_card_interface overrides
	virtual UINT8 bd_r(address_space &space, offs_t offset, UINT8 data, int _8000, int _a000, int _c000, int _e000);

private:
	UINT32 m_current_offset;
=======
	colecovision_xin1_cartridge_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;

	// device_colecovision_expansion_card_interface overrides
	virtual uint8_t bd_r(address_space &space, offs_t offset, uint8_t data, int _8000, int _a000, int _c000, int _e000) override;

private:
	uint32_t m_current_offset;
>>>>>>> upstream/master
};


// device type definition
<<<<<<< HEAD
extern const device_type COLECOVISION_XIN1;


#endif
=======
DECLARE_DEVICE_TYPE(COLECOVISION_XIN1, colecovision_xin1_cartridge_device)


#endif // MAME_BUS_COLECO_XIN1_H
>>>>>>> upstream/master
