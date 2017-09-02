// license:BSD-3-Clause
// copyright-holders:Sergey Svishchev
/**********************************************************************

    Poisk-1 FDC device (model B504)

**********************************************************************/

<<<<<<< HEAD
#pragma once

#ifndef __P1_FDC__
#define __P1_FDC__

#include "emu.h"

#include "imagedev/flopdrv.h"
#include "isa.h"
=======
#ifndef MAME_BUS_ISA_P1_FDC_H
#define MAME_BUS_ISA_P1_FDC_H

#pragma once


#include "isa.h"
#include "imagedev/flopdrv.h"
>>>>>>> upstream/master
#include "machine/wd_fdc.h"

//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

class p1_fdc_device : public device_t,
	public device_isa8_card_interface
{
public:
	// construction/destruction
<<<<<<< HEAD
	p1_fdc_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// optional information overrides
	virtual machine_config_constructor device_mconfig_additions() const;
	virtual const rom_entry *device_rom_region() const;

	DECLARE_FLOPPY_FORMATS( floppy_formats );
	DECLARE_READ8_MEMBER(p1_fdc_r);
	DECLARE_WRITE8_MEMBER(p1_fdc_w);
	DECLARE_WRITE_LINE_MEMBER( p1_fdc_irq_drq );
protected:
	// device-level overrides
	virtual void device_start();
	virtual void device_reset();

private:
	required_device<fd1793_t> m_fdc;

public:
	void p1_wd17xx_aux_w(int data);
	UINT8 p1_wd17xx_aux_r();
	UINT8 p1_wd17xx_motor_r();
=======
	p1_fdc_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	DECLARE_READ8_MEMBER(p1_fdc_r);
	DECLARE_WRITE8_MEMBER(p1_fdc_w);

protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;

	// optional information overrides
	virtual void device_add_mconfig(machine_config &config) override;
	virtual const tiny_rom_entry *device_rom_region() const override;

private:
	DECLARE_FLOPPY_FORMATS(floppy_formats);

	DECLARE_WRITE_LINE_MEMBER(p1_fdc_irq_drq);

	required_device<fd1793_device> m_fdc;

public:
	void p1_wd17xx_aux_w(int data);
	uint8_t p1_wd17xx_aux_r();
	uint8_t p1_wd17xx_motor_r();
>>>>>>> upstream/master
};


// device type definition
<<<<<<< HEAD
extern const device_type P1_FDC;


#endif
=======
DECLARE_DEVICE_TYPE(P1_FDC, p1_fdc_device)


#endif // MAME_BUS_ISA_P1_FDC_H
>>>>>>> upstream/master
