// license:BSD-3-Clause
// copyright-holders:Curt Coder
/**********************************************************************

    RCA VIP ASCII Keyboard Interface VP-620 emulation

**********************************************************************/

<<<<<<< HEAD
#pragma once

#ifndef __VP620__
#define __VP620__

#include "emu.h"
=======
#ifndef MAME_BUS_VIP_VP620_H
#define MAME_BUS_VIP_VP620_H

#pragma once

>>>>>>> upstream/master
#include "byteio.h"
#include "machine/keyboard.h"



//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

// ======================> vp620_device

class vp620_device : public device_t,
						public device_vip_byteio_port_interface
{
public:
	// construction/destruction
<<<<<<< HEAD
	vp620_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// optional information overrides
	virtual machine_config_constructor device_mconfig_additions() const;

	// not really public
	DECLARE_WRITE8_MEMBER( kb_w );

protected:
	// device-level overrides
	virtual void device_start();

	// device_vip_byteio_port_interface overrides
	virtual UINT8 vip_in_r();
	virtual int vip_ef4_r();

private:
	UINT8 m_keydata;
=======
	vp620_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_add_mconfig(machine_config &config) override;

	// device_vip_byteio_port_interface overrides
	virtual uint8_t vip_in_r() override;
	virtual int vip_ef4_r() override;

private:
	void kb_w(uint8_t data);

	uint8_t m_keydata;
>>>>>>> upstream/master
	int m_keystb;
};


// device type definition
<<<<<<< HEAD
extern const device_type VP620;


#endif
=======
DECLARE_DEVICE_TYPE(VP620, vp620_device)

#endif // MAME_BUS_VIP_VP620_H
>>>>>>> upstream/master
