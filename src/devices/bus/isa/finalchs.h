// license:BSD-3-Clause
// copyright-holders:Jonathan Gevaryahu
<<<<<<< HEAD
#pragma once

#ifndef __ISA_FINALCHS_H__
#define __ISA_FINALCHS_H__

#include "emu.h"
=======
#ifndef MAME_BUS_ISA_FINALCHS_H
#define MAME_BUS_ISA_FINALCHS_H

#pragma once

>>>>>>> upstream/master
#include "isa.h"

//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

// ======================> isa8_finalchs_device

class isa8_finalchs_device :
		public device_t,
		public device_isa8_card_interface
{
public:
<<<<<<< HEAD
		// construction/destruction
		isa8_finalchs_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

		DECLARE_READ8_MEMBER(finalchs_r);
		DECLARE_WRITE8_MEMBER(finalchs_w);

		DECLARE_WRITE8_MEMBER( io7ff8_write );
		DECLARE_READ8_MEMBER( io7ff8_read );
		DECLARE_READ8_MEMBER( io6000_read );
		DECLARE_WRITE8_MEMBER( io6000_write );

		// optional information overrides
		virtual machine_config_constructor device_mconfig_additions() const;
		virtual const rom_entry *device_rom_region() const;
protected:
		// device-level overrides
		virtual void device_start();
		virtual void device_reset();

private:
		// internal state
		UINT8 m_FCH_latch_data;
=======
	// construction/destruction
	isa8_finalchs_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	DECLARE_READ8_MEMBER(finalchs_r);
	DECLARE_WRITE8_MEMBER(finalchs_w);

	DECLARE_WRITE8_MEMBER( io7ff8_write );
	DECLARE_READ8_MEMBER( io7ff8_read );
	DECLARE_READ8_MEMBER( io6000_read );
	DECLARE_WRITE8_MEMBER( io6000_write );

protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;

	// optional information overrides
	virtual void device_add_mconfig(machine_config &config) override;
	virtual const tiny_rom_entry *device_rom_region() const override;

private:
	// internal state
	uint8_t m_FCH_latch_data;
>>>>>>> upstream/master
};


// device type definition
<<<<<<< HEAD
extern const device_type ISA8_FINALCHS;

#endif  /* __ISA_FINALCHS_H__ */
=======
DECLARE_DEVICE_TYPE(ISA8_FINALCHS, isa8_finalchs_device)

#endif // MAME_BUS_ISA_FINALCHS_H
>>>>>>> upstream/master
