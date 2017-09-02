// license:BSD-3-Clause
// copyright-holders:Sergey Svishchev
/**********************************************************************

    Poisk-1 HDC device (model B942)

**********************************************************************/

<<<<<<< HEAD
#pragma once

#ifndef __P1_HDC__
#define __P1_HDC__

#include "emu.h"

#include "imagedev/harddriv.h"
#include "isa.h"
=======
#ifndef MAME_BUS_ISA_P1_HDC_H
#define MAME_BUS_ISA_P1_HDC_H

#pragma once


#include "isa.h"
#include "imagedev/harddriv.h"
>>>>>>> upstream/master
#include "machine/wd2010.h"

//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

class p1_hdc_device : public device_t,
	public device_isa8_card_interface
{
public:
	// construction/destruction
<<<<<<< HEAD
	p1_hdc_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// optional information overrides
	virtual machine_config_constructor device_mconfig_additions() const;
	virtual const rom_entry *device_rom_region() const;

protected:
	// device-level overrides
	virtual void device_start();
	virtual void device_reset();
=======
	p1_hdc_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;

	// optional information overrides
	virtual void device_add_mconfig(machine_config &config) override;
	virtual const tiny_rom_entry *device_rom_region() const override;
>>>>>>> upstream/master

private:
	required_device<wd2010_device> m_hdc;

<<<<<<< HEAD
	//UINT8 m_ram[0x800];
=======
	// uint8_t m_ram[0x800];
>>>>>>> upstream/master

public:
	DECLARE_READ8_MEMBER(p1_HDC_r);
	DECLARE_WRITE8_MEMBER(p1_HDC_w);
};


// device type definition
<<<<<<< HEAD
extern const device_type P1_HDC;


#endif
=======
DECLARE_DEVICE_TYPE(P1_HDC, p1_hdc_device)


#endif // MAME_BUS_ISA_P1_HDC_H
>>>>>>> upstream/master
