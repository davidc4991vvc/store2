// license:BSD-3-Clause
// copyright-holders:Curt Coder
/**********************************************************************

    RCA Cosmac VIP Byte Input/Output port emulation

**********************************************************************

                            A   IN 0
                            B   IN 1
                            C   IN 2
                            D   IN 3
                            E   IN 4
                            F   IN 5
                            H   IN 6
                            J   IN 7
                            K   INST
                            L   _EF4
                            M   OUT 0
                            N   OUT 1
                            P   OUT 2
                            R   OUT 3
                            S   OUT 4
                            T   OUT 5
                            U   OUT 6
                            V   OUT 7
                            W   Q
                            X   _EF3
                            Y   +5 V
                            Z   GND

**********************************************************************/

<<<<<<< HEAD
#pragma once

#ifndef __VIP_BYTEIO_PORT__
#define __VIP_BYTEIO_PORT__

#include "emu.h"
=======
#ifndef MAME_BUS_VIP_BYTEIO_H
#define MAME_BUS_VIP_BYTEIO_H

#pragma once
>>>>>>> upstream/master



//**************************************************************************
//  CONSTANTS
//**************************************************************************

#define VIP_BYTEIO_PORT_TAG     "byteio"



//**************************************************************************
//  INTERFACE CONFIGURATION MACROS
//**************************************************************************

#define MCFG_VIP_BYTEIO_PORT_ADD(_tag, _slot_intf, _def_slot, _inst) \
	MCFG_DEVICE_ADD(_tag, VIP_BYTEIO_PORT, 0) \
	MCFG_DEVICE_SLOT_INTERFACE(_slot_intf, _def_slot, false) \
	downcast<vip_byteio_port_device *>(device)->set_inst_callback(DEVCB_##_inst);



//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

// ======================> vip_byteio_port_device

class device_vip_byteio_port_interface;

class vip_byteio_port_device : public device_t,
								public device_slot_interface
{
public:
	// construction/destruction
<<<<<<< HEAD
	vip_byteio_port_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
=======
	vip_byteio_port_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
>>>>>>> upstream/master

	template<class _inst> void set_inst_callback(_inst inst) { m_write_inst.set_callback(inst); }

	// computer interface
<<<<<<< HEAD
	UINT8 in_r();
	void out_w(UINT8 data);
=======
	uint8_t in_r();
	void out_w(uint8_t data);
>>>>>>> upstream/master
	DECLARE_READ_LINE_MEMBER( ef3_r );
	DECLARE_READ_LINE_MEMBER( ef4_r );
	DECLARE_WRITE_LINE_MEMBER( q_w );

	// cartridge interface
	DECLARE_WRITE_LINE_MEMBER( inst_w ) { m_write_inst(state); }

protected:
	// device-level overrides
<<<<<<< HEAD
	virtual void device_start();
	virtual void device_reset();
=======
	virtual void device_start() override;
	virtual void device_reset() override;
>>>>>>> upstream/master

	devcb_write_line m_write_inst;

	device_vip_byteio_port_interface *m_cart;
};


// ======================> device_vip_byteio_port_interface

// class representing interface-specific live c64_expansion card
class device_vip_byteio_port_interface : public device_slot_card_interface
{
public:
<<<<<<< HEAD
	// construction/destruction
	device_vip_byteio_port_interface(const machine_config &mconfig, device_t &device);

	virtual UINT8 vip_in_r() { return 0xff; };
	virtual void vip_out_w(UINT8 data) { };
=======
	virtual uint8_t vip_in_r() { return 0xff; }
	virtual void vip_out_w(uint8_t data) { }
>>>>>>> upstream/master

	virtual int vip_ef3_r() { return CLEAR_LINE; }
	virtual int vip_ef4_r() { return CLEAR_LINE; }

<<<<<<< HEAD
	virtual void vip_q_w(int state) { };

protected:
=======
	virtual void vip_q_w(int state) { }

protected:
	// construction/destruction
	device_vip_byteio_port_interface(const machine_config &mconfig, device_t &device);

>>>>>>> upstream/master
	vip_byteio_port_device *m_slot;
};


// device type definition
<<<<<<< HEAD
extern const device_type VIP_BYTEIO_PORT;
=======
DECLARE_DEVICE_TYPE(VIP_BYTEIO_PORT, vip_byteio_port_device)
>>>>>>> upstream/master


// slot devices
#include "vp620.h"

SLOT_INTERFACE_EXTERN( vip_byteio_cards );

<<<<<<< HEAD


#endif
=======
#endif // MAME_BUS_VIP_BYTEIO_H
>>>>>>> upstream/master
