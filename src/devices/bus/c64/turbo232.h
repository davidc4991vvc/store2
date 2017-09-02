// license:BSD-3-Clause
// copyright-holders:Curt Coder
/**********************************************************************

    CMD Turbo232 RS-232 cartridge emulation

**********************************************************************/

<<<<<<< HEAD
#pragma once

#ifndef __TURBO232__
#define __TURBO232__
=======
#ifndef MAME_BUS_C64_TURBO232_H
#define MAME_BUS_C64_TURBO232_H

#pragma once
>>>>>>> upstream/master


#include "exp.h"
#include "machine/mos6551.h"
#include "bus/rs232/rs232.h"



//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

// ======================> c64_turbo232_cartridge_device

class c64_turbo232_cartridge_device : public device_t,
										public device_c64_expansion_card_interface
{
public:
	// construction/destruction
<<<<<<< HEAD
	c64_turbo232_cartridge_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// optional information overrides
	virtual machine_config_constructor device_mconfig_additions() const;
	virtual ioport_constructor device_input_ports() const;

	DECLARE_WRITE_LINE_MEMBER( acia_irq_w );

protected:
	// device-level overrides
	virtual void device_start();
	virtual void device_reset();

	// device_c64_expansion_card_interface overrides
	virtual UINT8 c64_cd_r(address_space &space, offs_t offset, UINT8 data, int sphi2, int ba, int roml, int romh, int io1, int io2);
	virtual void c64_cd_w(address_space &space, offs_t offset, UINT8 data, int sphi2, int ba, int roml, int romh, int io1, int io2);

private:
=======
	c64_turbo232_cartridge_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;

	// optional information overrides
	virtual void device_add_mconfig(machine_config &config) override;
	virtual ioport_constructor device_input_ports() const override;

	// device_c64_expansion_card_interface overrides
	virtual uint8_t c64_cd_r(address_space &space, offs_t offset, uint8_t data, int sphi2, int ba, int roml, int romh, int io1, int io2) override;
	virtual void c64_cd_w(address_space &space, offs_t offset, uint8_t data, int sphi2, int ba, int roml, int romh, int io1, int io2) override;

private:
	DECLARE_WRITE_LINE_MEMBER( acia_irq_w );

>>>>>>> upstream/master
	required_device<mos6551_device> m_acia;
	required_device<rs232_port_device> m_rs232;
	required_ioport m_io_cs;
	required_ioport m_io_irq;

	enum
	{
		D700 = 0,
		DE00,
		DF00
	};

	enum
	{
		IRQ = 0,
		NMI
	};

	enum
	{
		ES_S_230400 = 0x00,
		ES_S_115200 = 0x01,
		ES_S_57600 = 0x02,
		ES_S_UNDEFINED = 0x03,
		ES_S_MASK = 0x03,
		ES_M = 0x04
	};

	int m_cs;
	int m_irq;

<<<<<<< HEAD
	UINT8 m_es;
=======
	uint8_t m_es;
>>>>>>> upstream/master
};


// device type definition
<<<<<<< HEAD
extern const device_type C64_TURBO232;


#endif
=======
DECLARE_DEVICE_TYPE(C64_TURBO232, c64_turbo232_cartridge_device)


#endif // MAME_BUS_C64_TURBO232_H
>>>>>>> upstream/master
