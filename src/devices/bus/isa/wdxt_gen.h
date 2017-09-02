// license:BSD-3-Clause
// copyright-holders:Curt Coder
/**********************************************************************

    Western Digital WDXT-GEN ISA XT MFM Hard Disk Controller

**********************************************************************

    Emulated here is the variant supplied with Amstrad PC1512/1640,
    which has a custom BIOS and is coupled with a Tandom TM262 HDD.

    chdman -createblankhd tandon_tm262.chd 615 4 17 512

**********************************************************************/

<<<<<<< HEAD
#pragma once

#ifndef __ISA8_WDXT_GEN__
#define __ISA8_WDXT_GEN__


#include "emu.h"
#include "cpu/mcs48/mcs48.h"
#include "isa.h"
=======
#ifndef MAME_BUS_ISA8_WDXT_GEN_H
#define MAME_BUS_ISA8_WDXT_GEN_H

#pragma once


#include "isa.h"
#include "cpu/mcs48/mcs48.h"
>>>>>>> upstream/master
#include "machine/wd11c00_17.h"
#include "machine/wd2010.h"
#include "imagedev/harddriv.h"



//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

// ======================> wdxt_gen_device

class wdxt_gen_device : public device_t,
						public device_isa8_card_interface
{
public:
	// construction/destruction
<<<<<<< HEAD
	wdxt_gen_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// optional information overrides
	virtual machine_config_constructor device_mconfig_additions() const;
	virtual const rom_entry *device_rom_region() const;

	// not really public
=======
	wdxt_gen_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;

	// optional information overrides
	virtual void device_add_mconfig(machine_config &config) override;
	virtual const tiny_rom_entry *device_rom_region() const override;

	// device_isa8_card_interface
	virtual uint8_t dack_r(int line) override;
	virtual void dack_w(int line, uint8_t data) override;

private:
>>>>>>> upstream/master
	DECLARE_WRITE_LINE_MEMBER( irq5_w );
	DECLARE_WRITE_LINE_MEMBER( drq3_w );
	DECLARE_WRITE_LINE_MEMBER( mr_w );
	DECLARE_READ8_MEMBER( rd322_r );
	DECLARE_READ8_MEMBER( ram_r );
	DECLARE_WRITE8_MEMBER( ram_w );
<<<<<<< HEAD
	DECLARE_READ8_MEMBER( wd1015_t0_r );
	DECLARE_READ8_MEMBER( wd1015_t1_r );
=======
	DECLARE_READ_LINE_MEMBER( wd1015_t1_r );
>>>>>>> upstream/master
	DECLARE_READ8_MEMBER( wd1015_p1_r );
	DECLARE_WRITE8_MEMBER( wd1015_p1_w );
	DECLARE_READ8_MEMBER( wd1015_p2_r );
	DECLARE_WRITE8_MEMBER( wd1015_p2_w );

<<<<<<< HEAD
protected:
	// device-level overrides
	virtual void device_start();
	virtual void device_reset();

	// device_isa8_card_interface
	virtual UINT8 dack_r(int line);
	virtual void dack_w(int line, UINT8 data);

private:
=======
>>>>>>> upstream/master
	required_device<cpu_device> m_maincpu;
	required_device<wd11c00_17_device> m_host;
	required_device<wd2010_device> m_hdc;

<<<<<<< HEAD
	UINT8 m_ram[0x800];

	//UINT8 m_hdc_addr;
=======
	uint8_t m_ram[0x800];

	//uint8_t m_hdc_addr;
>>>>>>> upstream/master
};


// device type definition
<<<<<<< HEAD
extern const device_type ISA8_WDXT_GEN;

#endif
=======
DECLARE_DEVICE_TYPE(ISA8_WDXT_GEN, wdxt_gen_device)

#endif // MAME_BUS_ISA8_WDXT_GEN_H
>>>>>>> upstream/master
