// license:GPL-2.0+
// copyright-holders:Dirk Best
/***************************************************************************

    EACA Colour Genie Floppy Controller Cartridge

***************************************************************************/

<<<<<<< HEAD
#pragma once

#ifndef __CGENIE_EXPANSION_FLOPPY_H__
#define __CGENIE_EXPANSION_FLOPPY_H__

#include "emu.h"
=======
#ifndef MAME_BUS_CGENIE_EXPANSION_FLOPPY_H
#define MAME_BUS_CGENIE_EXPANSION_FLOPPY_H

#pragma once

>>>>>>> upstream/master
#include "expansion.h"
#include "machine/wd_fdc.h"
#include "bus/generic/slot.h"


//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

// ======================> floppy_controller_device

<<<<<<< HEAD
class cgenie_fdc_device : public device_t, public device_expansion_interface
{
public:
	// construction/destruction
	cgenie_fdc_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
=======
class cgenie_fdc_device : public device_t, public device_cg_exp_interface
{
public:
	// construction/destruction
	cgenie_fdc_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
>>>>>>> upstream/master

	DECLARE_ADDRESS_MAP(mmio, 8);

	TIMER_DEVICE_CALLBACK_MEMBER(timer_callback);

<<<<<<< HEAD
	DECLARE_DEVICE_IMAGE_LOAD_MEMBER(socket_load);

	DECLARE_WRITE_LINE_MEMBER(intrq_w);
=======
>>>>>>> upstream/master
	DECLARE_READ8_MEMBER(irq_r);
	DECLARE_WRITE8_MEMBER(select_w);
	DECLARE_WRITE8_MEMBER(command_w);

<<<<<<< HEAD
	DECLARE_FLOPPY_FORMATS(floppy_formats);


protected:
	virtual const rom_entry *device_rom_region() const;
	virtual machine_config_constructor device_mconfig_additions() const;
	virtual void device_start();
	virtual void device_reset();

private:
	void update_irq();

	required_device<fd1793_t> m_fdc;
=======
protected:
	virtual const tiny_rom_entry *device_rom_region() const override;
	virtual void device_add_mconfig(machine_config &config) override;
	virtual void device_start() override;
	virtual void device_reset() override;

private:
	DECLARE_DEVICE_IMAGE_LOAD_MEMBER(socket_load);

	DECLARE_WRITE_LINE_MEMBER(intrq_w);

	DECLARE_FLOPPY_FORMATS(floppy_formats);

	required_device<fd1793_device> m_fdc;
>>>>>>> upstream/master
	required_device<floppy_connector> m_floppy0;
	required_device<floppy_connector> m_floppy1;
	required_device<floppy_connector> m_floppy2;
	required_device<floppy_connector> m_floppy3;
	required_device<generic_slot_device> m_socket;

	enum
	{
		IRQ_WDC = 0x40,
		IRQ_TIMER = 0x80
	};

	floppy_image_device *m_floppy;

<<<<<<< HEAD
	UINT8 m_irq_status;
};

// device type definition
extern const device_type CGENIE_FDC;

#endif // __CGENIE_EXPANSION_FLOPPY_H__
=======
	uint8_t m_irq_status;
};

// device type definition
DECLARE_DEVICE_TYPE(CGENIE_FDC, cgenie_fdc_device)

#endif // MAME_BUS_CGENIE_EXPANSION_FLOPPY_H
>>>>>>> upstream/master
