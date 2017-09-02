// license:GPL-2.0+
// copyright-holders:Dirk Best
/***************************************************************************

    Commodore A2052

    Zorro-II RAM Expansion (0.5, 1 or 2 MB)

***************************************************************************/

<<<<<<< HEAD
#pragma once

#ifndef __A2052_H__
#define __A2052_H__

#include "emu.h"
=======
#ifndef MAME_BUS_AMIGA_ZORRO_A2052_H
#define MAME_BUS_AMIGA_ZORRO_A2052_H

#pragma once

>>>>>>> upstream/master
#include "zorro.h"
#include "machine/autoconfig.h"


//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

// ======================> a2052_device

class a2052_device : public device_t, public device_zorro2_card_interface, public amiga_autoconfig
{
public:
	// construction/destruction
<<<<<<< HEAD
	a2052_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

protected:
	virtual ioport_constructor device_input_ports() const;
	virtual void device_start();

	// device_zorro2_card_interface overrides
	virtual DECLARE_WRITE_LINE_MEMBER( cfgin_w );

	// amiga_autoconfig overrides
	virtual void autoconfig_base_address(offs_t address);

private:
	required_ioport m_config;
	std::vector<UINT16> m_ram;
};

// device type definition
extern const device_type A2052;

#endif
=======
	a2052_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

protected:
	virtual ioport_constructor device_input_ports() const override;
	virtual void device_start() override;

	// device_zorro2_card_interface overrides
	virtual DECLARE_WRITE_LINE_MEMBER( cfgin_w ) override;

	// amiga_autoconfig overrides
	virtual void autoconfig_base_address(offs_t address) override;

private:
	required_ioport m_config;
	std::vector<uint16_t> m_ram;
};

// device type definition
DECLARE_DEVICE_TYPE(A2052, a2052_device)

#endif // MAME_BUS_AMIGA_ZORRO_A2052_H
>>>>>>> upstream/master
