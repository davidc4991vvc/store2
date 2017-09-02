// license:BSD-3-Clause
// copyright-holders:Sergey Svishchev
/**********************************************************************

    Electronika MC 1502 FDC device

**********************************************************************/

<<<<<<< HEAD
#pragma once

#ifndef __MC1502_FDC__
#define __MC1502_FDC__

#include "emu.h"

#include "imagedev/flopdrv.h"
#include "isa.h"
=======
#ifndef MAME_BUS_ISA_MC1502_FDC_H
#define MAME_BUS_ISA_MC1502_FDC_H

#pragma once


#include "isa.h"
#include "imagedev/flopdrv.h"
>>>>>>> upstream/master
#include "machine/wd_fdc.h"

//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

class mc1502_fdc_device : public device_t,
	public device_isa8_card_interface
{
public:
	// construction/destruction
<<<<<<< HEAD
	mc1502_fdc_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// optional information overrides
	virtual machine_config_constructor device_mconfig_additions() const;
	virtual const rom_entry *device_rom_region() const;

	DECLARE_FLOPPY_FORMATS( floppy_formats );
	TIMER_CALLBACK_MEMBER( motor_callback );
=======
	mc1502_fdc_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);


	TIMER_CALLBACK_MEMBER(motor_callback);
>>>>>>> upstream/master

	DECLARE_READ8_MEMBER(mc1502_fdc_r);
	DECLARE_READ8_MEMBER(mc1502_fdcv2_r);
	DECLARE_WRITE8_MEMBER(mc1502_fdc_w);
<<<<<<< HEAD
	DECLARE_WRITE_LINE_MEMBER( mc1502_fdc_irq_drq );

protected:
	// device-level overrides
	virtual void device_start();

private:
	required_device<fd1793_t> m_fdc;
=======

protected:
	// device-level overrides
	virtual void device_start() override;

	// optional information overrides
	virtual void device_add_mconfig(machine_config &config) override;
	virtual const tiny_rom_entry *device_rom_region() const override;

private:
	DECLARE_FLOPPY_FORMATS(floppy_formats);

	DECLARE_WRITE_LINE_MEMBER(mc1502_fdc_irq_drq);

	required_device<fd1793_device> m_fdc;
>>>>>>> upstream/master
	int motor_on;
	emu_timer *motor_timer;

public:
<<<<<<< HEAD
	void mc1502_wd17xx_aux_w(UINT8 data);
	UINT8 mc1502_wd17xx_aux_r();
	UINT8 mc1502_wd17xx_drq_r();
	UINT8 mc1502_wd17xx_motor_r();

=======
	void mc1502_wd17xx_aux_w(uint8_t data);
	uint8_t mc1502_wd17xx_aux_r();
	uint8_t mc1502_wd17xx_drq_r();
	uint8_t mc1502_wd17xx_motor_r();
>>>>>>> upstream/master
};


// device type definition
<<<<<<< HEAD
extern const device_type MC1502_FDC;


#endif
=======
DECLARE_DEVICE_TYPE(MC1502_FDC, mc1502_fdc_device)

#endif // MAME_BUS_ISA_MC1502_FDC_H
>>>>>>> upstream/master
