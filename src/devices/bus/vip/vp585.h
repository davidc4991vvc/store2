// license:BSD-3-Clause
// copyright-holders:Curt Coder
/**********************************************************************

    RCA VIP Expansion Keypad Interface Board VP585 emulation

**********************************************************************/

<<<<<<< HEAD
#pragma once

#ifndef __VP585__
#define __VP585__

#include "emu.h"
=======
#ifndef MAME_BUS_VIP_VP585_H
#define MAME_BUS_VIP_VP585_H

#pragma once

>>>>>>> upstream/master
#include "exp.h"



//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

// ======================> vp585_device

class vp585_device : public device_t,
						public device_vip_expansion_card_interface
{
public:
	// construction/destruction
<<<<<<< HEAD
	vp585_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// optional information overrides
	virtual ioport_constructor device_input_ports() const;

protected:
	// device-level overrides
	virtual void device_start();

	// device_vip_expansion_card_interface overrides
	virtual void vip_io_w(address_space &space, offs_t offset, UINT8 data);
	virtual int vip_ef3_r();
	virtual int vip_ef4_r();
=======
	vp585_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// optional information overrides
	virtual ioport_constructor device_input_ports() const override;

protected:
	// device-level overrides
	virtual void device_start() override;

	// device_vip_expansion_card_interface overrides
	virtual void vip_io_w(address_space &space, offs_t offset, uint8_t data) override;
	virtual int vip_ef3_r() override;
	virtual int vip_ef4_r() override;
>>>>>>> upstream/master

private:
	required_ioport m_j1;
	required_ioport m_j2;

<<<<<<< HEAD
	UINT8 m_keylatch;
=======
	uint8_t m_keylatch;
>>>>>>> upstream/master
};


// device type definition
<<<<<<< HEAD
extern const device_type VP585;


#endif
=======
DECLARE_DEVICE_TYPE(VP585, vp585_device)

#endif // MAME_BUS_VIP_VP585_H
>>>>>>> upstream/master
