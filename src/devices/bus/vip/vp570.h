// license:BSD-3-Clause
// copyright-holders:Curt Coder
/**********************************************************************

    RCA VIP Memory Expansion Board VP-570 emulation

**********************************************************************/

<<<<<<< HEAD
#pragma once

#ifndef __VP570__
#define __VP570__

#include "emu.h"
=======
#ifndef MAME_BUS_VIP_VP570_H
#define MAME_BUS_VIP_VP570_H

#pragma once

>>>>>>> upstream/master
#include "exp.h"



//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

// ======================> vp570_device

class vp570_device : public device_t,
						public device_vip_expansion_card_interface
{
public:
	// construction/destruction
<<<<<<< HEAD
	vp570_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// optional information overrides
	virtual ioport_constructor device_input_ports() const;

protected:
	// device-level overrides
	virtual void device_start();

	// device_vip_expansion_card_interface overrides
	virtual UINT8 vip_program_r(address_space &space, offs_t offset, int cs, int cdef, int *minh);
	virtual void vip_program_w(address_space &space, offs_t offset, UINT8 data, int cdef, int *minh);

private:
	optional_shared_ptr<UINT8> m_ram;
=======
	vp570_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// optional information overrides
	virtual ioport_constructor device_input_ports() const override;

protected:
	// device-level overrides
	virtual void device_start() override;

	// device_vip_expansion_card_interface overrides
	virtual uint8_t vip_program_r(address_space &space, offs_t offset, int cs, int cdef, int *minh) override;
	virtual void vip_program_w(address_space &space, offs_t offset, uint8_t data, int cdef, int *minh) override;

private:
	optional_shared_ptr<uint8_t> m_ram;
>>>>>>> upstream/master
	required_ioport m_base;
	required_ioport m_sw1;
};


// device type definition
<<<<<<< HEAD
extern const device_type VP570;


#endif
=======
DECLARE_DEVICE_TYPE(VP570, vp570_device)


#endif // MAME_BUS_VIP_VP570_H
>>>>>>> upstream/master
