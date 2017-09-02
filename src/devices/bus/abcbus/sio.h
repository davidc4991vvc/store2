// license:BSD-3-Clause
// copyright-holders:Curt Coder
<<<<<<< HEAD
#pragma once

#ifndef __ABC_SIO__
#define __ABC_SIO__

#include "emu.h"
=======
#ifndef MAME_BUS_ABCBUS_SIO_H
#define MAME_BUS_ABCBUS_SIO_H

#pragma once

>>>>>>> upstream/master
#include "abcbus.h"
#include "machine/z80ctc.h"
#include "machine/z80dart.h"



//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

// ======================> abc_sio_device

class abc_sio_device :  public device_t,
						public device_abcbus_card_interface
{
public:
	// construction/destruction
<<<<<<< HEAD
	abc_sio_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// optional information overrides
	virtual const rom_entry *device_rom_region() const;
	virtual machine_config_constructor device_mconfig_additions() const;

protected:
	// device-level overrides
	virtual void device_start();
	virtual void device_reset();

	// device_abcbus_interface overrides
	virtual void abcbus_cs(UINT8 data);
	virtual UINT8 abcbus_xmemfl(offs_t offset);
=======
	abc_sio_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;

	// optional information overrides
	virtual const tiny_rom_entry *device_rom_region() const override;
	virtual void device_add_mconfig(machine_config &config) override;

	// device_abcbus_interface overrides
	virtual void abcbus_cs(uint8_t data) override;
	virtual uint8_t abcbus_xmemfl(offs_t offset) override;
>>>>>>> upstream/master

private:
	required_device<z80ctc_device> m_ctc;
	required_device<z80dart_device> m_sio;
	required_memory_region m_rom;
};


// device type definition
<<<<<<< HEAD
extern const device_type ABC_SIO;



#endif
=======
DECLARE_DEVICE_TYPE(ABC_SIO, abc_sio_device)

#endif // MAME_BUS_ABCBUS_SIO_H
>>>>>>> upstream/master
