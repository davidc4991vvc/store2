// license:BSD-3-Clause
// copyright-holders:Miodrag Milanovic
/***************************************************************************

    Chips & Technologies CS8221 chipset

    a.k.a. NEW ENHANCED AT (NEAT)

    Consists of four individual chips:

    * 82C211 - CPU/Bus controller
    * 82C212 - Page/Interleave and EMS Memory controller
    * 82C215 - Data/Address buffer
    * 82C206 - Integrated Peripherals Controller(IPC)

***************************************************************************/

<<<<<<< HEAD
#pragma once

#ifndef __CS8221_H__
#define __CS8221_H__

#include "emu.h"
=======
#ifndef MAME_MACHINE_CS8221_H
#define MAME_MACHINE_CS8221_H

#pragma once

>>>>>>> upstream/master


//**************************************************************************
//  INTERFACE CONFIGURATION MACROS
//**************************************************************************

#define MCFG_CS8221_ADD(_tag, _cputag, _isatag, _biostag) \
	MCFG_DEVICE_ADD(_tag, CS8221, 0) \
	cs8221_device::static_set_cputag(*device, _cputag); \
	cs8221_device::static_set_isatag(*device, _isatag); \
	cs8221_device::static_set_biostag(*device, _biostag);


//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

// ======================> cs8221_device

class cs8221_device : public device_t
{
public:
	// construction/destruction
<<<<<<< HEAD
	cs8221_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
=======
	cs8221_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
>>>>>>> upstream/master

	DECLARE_WRITE8_MEMBER( address_w );
	DECLARE_READ8_MEMBER( data_r );
	DECLARE_WRITE8_MEMBER( data_w );
<<<<<<< HEAD
=======
	DECLARE_ADDRESS_MAP(map, 16);
>>>>>>> upstream/master

	// inline configuration
	static void static_set_cputag(device_t &device, const char *tag);
	static void static_set_isatag(device_t &device, const char *tag);
	static void static_set_biostag(device_t &device, const char *tag);

protected:
	// device-level overrides
<<<<<<< HEAD
	virtual void device_start();
	virtual void device_reset();
=======
	virtual void device_start() override;
	virtual void device_reset() override;
>>>>>>> upstream/master

private:

	// internal state
	//address_space *m_space;
<<<<<<< HEAD
	//UINT8 *m_isa;
	//UINT8 *m_bios;
	//UINT8 *m_ram;

	// address selection
	UINT8 m_address;
=======
	//uint8_t *m_isa;
	//uint8_t *m_bios;
	//uint8_t *m_ram;

	// address selection
	uint8_t m_address;
>>>>>>> upstream/master
	bool m_address_valid;

	const char *m_cputag;
	const char *m_isatag;
	const char *m_biostag;


<<<<<<< HEAD
	UINT8 m_registers[0x10];
=======
	uint8_t m_registers[0x10];
>>>>>>> upstream/master
};


// device type definition
<<<<<<< HEAD
extern const device_type CS8221;


#endif  /* __CS8221_H__ */
=======
DECLARE_DEVICE_TYPE(CS8221, cs8221_device)

#endif // MAME_MACHINE_CS8221_H
>>>>>>> upstream/master
