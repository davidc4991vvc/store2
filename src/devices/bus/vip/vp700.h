// license:BSD-3-Clause
// copyright-holders:Curt Coder
/**********************************************************************

    RCA VIP Tiny BASIC VP-700 emulation

**********************************************************************/

<<<<<<< HEAD
#pragma once

#ifndef __VP700__
#define __VP700__

#include "emu.h"
=======
#ifndef MAME_BUS_VIP_VP700_H
#define MAME_BUS_VIP_VP700_H

#pragma once

>>>>>>> upstream/master
#include "exp.h"
#include "sound/cdp1863.h"



//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

// ======================> vp700_device

class vp700_device : public device_t,
						public device_vip_expansion_card_interface
{
public:
	// construction/destruction
<<<<<<< HEAD
	vp700_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// optional information overrides
	virtual const rom_entry *device_rom_region() const;

protected:
	// device-level overrides
	virtual void device_start();

	// device_vip_expansion_card_interface overrides
	virtual UINT8 vip_program_r(address_space &space, offs_t offset, int cs, int cdef, int *minh);
=======
	vp700_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// optional information overrides
	virtual const tiny_rom_entry *device_rom_region() const override;

protected:
	// device-level overrides
	virtual void device_start() override;

	// device_vip_expansion_card_interface overrides
	virtual uint8_t vip_program_r(address_space &space, offs_t offset, int cs, int cdef, int *minh) override;
>>>>>>> upstream/master

private:
	required_memory_region m_rom;
};


// device type definition
<<<<<<< HEAD
extern const device_type VP700;


#endif
=======
DECLARE_DEVICE_TYPE(VP700, vp700_device)

#endif // MAME_BUS_VIP_VP700_H
>>>>>>> upstream/master
