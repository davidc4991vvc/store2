// license:BSD-3-Clause
// copyright-holders:Curt Coder
/**********************************************************************

    RCA VIP Simple Sound Board VP595 emulation

**********************************************************************/

<<<<<<< HEAD
#pragma once

#ifndef __VP595__
#define __VP595__

#include "emu.h"
=======
#ifndef MAME_BUS_VIP_VP595_H
#define MAME_BUS_VIP_VP595_H

#pragma once

>>>>>>> upstream/master
#include "exp.h"
#include "sound/cdp1863.h"



//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

// ======================> vp595_device

class vp595_device : public device_t,
						public device_vip_expansion_card_interface
{
public:
	// construction/destruction
<<<<<<< HEAD
	vp595_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// optional information overrides
	virtual machine_config_constructor device_mconfig_additions() const;

protected:
	// device-level overrides
	virtual void device_start();

	// device_vip_expansion_card_interface overrides
	virtual void vip_io_w(address_space &space, offs_t offset, UINT8 data);
	virtual void vip_q_w(int state);
=======
	vp595_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_add_mconfig(machine_config &config) override;

	// device_vip_expansion_card_interface overrides
	virtual void vip_io_w(address_space &space, offs_t offset, uint8_t data) override;
	virtual void vip_q_w(int state) override;
>>>>>>> upstream/master

private:
	required_device<cdp1863_device> m_pfg;
};


// device type definition
<<<<<<< HEAD
extern const device_type VP595;


#endif
=======
DECLARE_DEVICE_TYPE(VP595, vp595_device)

#endif // MAME_BUS_VIP_VP595_H
>>>>>>> upstream/master
