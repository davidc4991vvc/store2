// license:BSD-3-Clause
// copyright-holders:Curt Coder
/**********************************************************************

    Coleco ADAMnet bus emulation

**********************************************************************/

<<<<<<< HEAD
#pragma once

#ifndef __ADAMNET__
#define __ADAMNET__

#include "emu.h"
=======
#ifndef MAME_BUS_ADAMNET_ADAMNET_H
#define MAME_BUS_ADAMNET_ADAMNET_H

#pragma once

>>>>>>> upstream/master



//**************************************************************************
//  CONSTANTS
//**************************************************************************

#define ADAMNET_TAG     "adamnet"



//**************************************************************************
//  INTERFACE CONFIGURATION MACROS
//**************************************************************************

#define MCFG_ADAMNET_BUS_ADD() \
	MCFG_DEVICE_ADD(ADAMNET_TAG, ADAMNET, 0)

#define MCFG_ADAMNET_SLOT_ADD(_tag, _slot_intf, _def_slot) \
	MCFG_DEVICE_ADD(_tag, ADAMNET_SLOT, 0) \
	MCFG_DEVICE_SLOT_INTERFACE(_slot_intf, _def_slot, false)



//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

class device_adamnet_card_interface;

// ======================> adamnet_device

class adamnet_device : public device_t
{
public:
	// construction/destruction
<<<<<<< HEAD
	adamnet_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
=======
	adamnet_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
>>>>>>> upstream/master

	void add_device(device_t *target);

	DECLARE_READ_LINE_MEMBER( rxd_r );
	int rxd_r(device_t *device);
	DECLARE_WRITE_LINE_MEMBER( txd_w );
	void txd_w(device_t *device, int state);

	DECLARE_READ_LINE_MEMBER( reset_r );
	DECLARE_WRITE_LINE_MEMBER( reset_w );

protected:
	// device-level overrides
<<<<<<< HEAD
	virtual void device_start();
	virtual void device_stop();
=======
	virtual void device_start() override;
	virtual void device_stop() override;
>>>>>>> upstream/master

private:
	class daisy_entry
	{
	public:
		daisy_entry(device_t *device);
		daisy_entry *next() const { return m_next; }

		daisy_entry *               m_next;         // next device
		device_t *                  m_device;       // associated device
		device_adamnet_card_interface * m_interface;    // associated device's daisy interface

		int m_txd;
	};

	simple_list<daisy_entry> m_device_list;

	int m_txd;
	int m_reset;
};


// ======================> adamnet_slot_device

class adamnet_slot_device : public device_t,
							public device_slot_interface
{
public:
	// construction/destruction
<<<<<<< HEAD
	adamnet_slot_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
=======
	adamnet_slot_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// device-level overrides
	virtual void device_start() override;
>>>>>>> upstream/master

protected:
	// configuration
	adamnet_device  *m_bus;
};


// ======================> device_adamnet_card_interface

class device_adamnet_card_interface : public device_slot_card_interface
{
<<<<<<< HEAD
public:
	// construction/destruction
	device_adamnet_card_interface(const machine_config &mconfig, device_t &device);
=======
	friend class adamnet_device;

public:
	// construction/destruction
>>>>>>> upstream/master
	virtual ~device_adamnet_card_interface();

	virtual void adamnet_reset_w(int state) = 0;

<<<<<<< HEAD
=======
protected:
	device_adamnet_card_interface(const machine_config &mconfig, device_t &device);

>>>>>>> upstream/master
	adamnet_device  *m_bus;
};


// device type definitions
<<<<<<< HEAD
extern const device_type ADAMNET;
extern const device_type ADAMNET_SLOT;
=======
DECLARE_DEVICE_TYPE(ADAMNET,      adamnet_device)
DECLARE_DEVICE_TYPE(ADAMNET_SLOT, adamnet_slot_device)
>>>>>>> upstream/master


SLOT_INTERFACE_EXTERN( adamnet_devices );



<<<<<<< HEAD
#endif
=======
#endif // MAME_BUS_ADAMNET_ADAMNET_H
>>>>>>> upstream/master
