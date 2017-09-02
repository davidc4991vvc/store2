// license:BSD-3-Clause
// copyright-holders:Barry Rodewald
<<<<<<< HEAD
#pragma once

#ifndef __ISA_SVGA_ET4K_H__
#define __ISA_SVGA_ET4K_H__

#include "emu.h"
=======
#ifndef MAME_BUS_ISA_SVGA_TSENG_H
#define MAME_BUS_ISA_SVGA_TSENG_H

#pragma once

>>>>>>> upstream/master
#include "isa.h"
#include "video/pc_vga.h"

//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

// ======================> isa8_vga_device

class isa8_svga_et4k_device :
		public device_t,
		public device_isa8_card_interface
{
public:
<<<<<<< HEAD
		// construction/destruction
		isa8_svga_et4k_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

		// optional information overrides
		virtual machine_config_constructor device_mconfig_additions() const;
		virtual const rom_entry *device_rom_region() const;

		DECLARE_READ8_MEMBER(input_port_0_r);
protected:
		// device-level overrides
		virtual void device_start();
		virtual void device_reset();
private:
		tseng_vga_device *m_vga;
=======
	// construction/destruction
	isa8_svga_et4k_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	DECLARE_READ8_MEMBER(input_port_0_r);

protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;

	// optional information overrides
	virtual void device_add_mconfig(machine_config &config) override;
	virtual const tiny_rom_entry *device_rom_region() const override;

private:
	tseng_vga_device *m_vga;
>>>>>>> upstream/master
};


// device type definition
<<<<<<< HEAD
extern const device_type ISA8_SVGA_ET4K;

#endif  /* __ISA_SVGA_ET4K_H__ */
=======
DECLARE_DEVICE_TYPE(ISA8_SVGA_ET4K, isa8_svga_et4k_device)

#endif // MAME_BUS_ISA_SVGA_TSENG_H
>>>>>>> upstream/master
