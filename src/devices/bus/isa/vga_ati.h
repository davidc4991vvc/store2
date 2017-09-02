// license:BSD-3-Clause
// copyright-holders:Barry Rodewald
/*
 * isa_vga_ati.h
 *
 *  Header for ATi Graphics Ultra/Graphics Ultra Pro ISA video cards
 *
 *  Created on: 9/09/2012
 */
<<<<<<< HEAD
#pragma once

#ifndef ISA_VGA_ATI_H_
#define ISA_VGA_ATI_H_

#include "emu.h"
=======
#ifndef MAME_BUS_ISA_VGA_ATI_H
#define MAME_BUS_ISA_VGA_ATI_H

#pragma once

>>>>>>> upstream/master
#include "isa.h"
#include "video/pc_vga.h"
#include "mach32.h"

//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

// ======================> isa16_vga_device

class isa16_vga_gfxultra_device :
		public device_t,
		public device_isa16_card_interface
{
public:
<<<<<<< HEAD
		// construction/destruction
		isa16_vga_gfxultra_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

		// optional information overrides
		virtual machine_config_constructor device_mconfig_additions() const;
		virtual const rom_entry *device_rom_region() const;

		DECLARE_READ8_MEMBER(input_port_0_r);
protected:
		// device-level overrides
		virtual void device_start();
		virtual void device_reset();
private:
		ati_vga_device *m_vga;
		mach8_device *m_8514;
=======
	// construction/destruction
	isa16_vga_gfxultra_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	DECLARE_READ8_MEMBER(input_port_0_r);

protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;

	// optional information overrides
	virtual void device_add_mconfig(machine_config &config) override;
	virtual const tiny_rom_entry *device_rom_region() const override;

private:
	ati_vga_device *m_vga;
	mach8_device *m_8514;
>>>>>>> upstream/master
};

class isa16_vga_gfxultrapro_device :
		public device_t,
		public device_isa16_card_interface
{
public:
<<<<<<< HEAD
		// construction/destruction
		isa16_vga_gfxultrapro_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

		// optional information overrides
		virtual machine_config_constructor device_mconfig_additions() const;
		virtual const rom_entry *device_rom_region() const;

		DECLARE_READ8_MEMBER(input_port_0_r);
protected:
		// device-level overrides
		virtual void device_start();
		virtual void device_reset();
private:
		mach32_device *m_vga;
=======
	// construction/destruction
	isa16_vga_gfxultrapro_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	DECLARE_READ8_MEMBER(input_port_0_r);

protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;

	// optional information overrides
	virtual void device_add_mconfig(machine_config &config) override;
	virtual const tiny_rom_entry *device_rom_region() const override;

	private:
	mach32_device *m_vga;
>>>>>>> upstream/master
};

class isa16_vga_mach64_device :
		public device_t,
		public device_isa16_card_interface
{
public:
<<<<<<< HEAD
		// construction/destruction
		isa16_vga_mach64_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

		// optional information overrides
		virtual machine_config_constructor device_mconfig_additions() const;
		virtual const rom_entry *device_rom_region() const;

		DECLARE_READ8_MEMBER(input_port_0_r);
protected:
		// device-level overrides
		virtual void device_start();
		virtual void device_reset();
private:
		mach64_device *m_vga;
=======
	// construction/destruction
	isa16_vga_mach64_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	DECLARE_READ8_MEMBER(input_port_0_r);

protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;

	// optional information overrides
	virtual void device_add_mconfig(machine_config &config) override;
	virtual const tiny_rom_entry *device_rom_region() const override;

private:
	mach64_device *m_vga;
>>>>>>> upstream/master
};


// device type definition
<<<<<<< HEAD
extern const device_type ISA16_VGA_GFXULTRA;
extern const device_type ISA16_SVGA_GFXULTRAPRO;
extern const device_type ISA16_SVGA_MACH64;


#endif /* ISA_VGA_ATI_H_ */
=======
DECLARE_DEVICE_TYPE(ISA16_VGA_GFXULTRA,     isa16_vga_gfxultra_device)
DECLARE_DEVICE_TYPE(ISA16_SVGA_GFXULTRAPRO, isa16_vga_gfxultrapro_device)
DECLARE_DEVICE_TYPE(ISA16_SVGA_MACH64,      isa16_vga_mach64_device)


#endif // MAME_BUS_ISA_VGA_ATI_H
>>>>>>> upstream/master
