// license:GPL-2.0+
// copyright-holders:Dirk Best
/***************************************************************************

    Commodore A590 / A2091

    DMAC based SCSI controller for the Amiga 500 and Zorro-II

***************************************************************************/

<<<<<<< HEAD
#pragma once

#ifndef __A590_H__
#define __A590_H__

#include "emu.h"
=======
#ifndef MAME_BUS_AMIGA_ZORRO_A590_H
#define MAME_BUS_AMIGA_ZORRO_A590_H

#pragma once

>>>>>>> upstream/master
#include "zorro.h"
#include "machine/dmac.h"
#include "machine/wd33c93.h"


//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

// ======================> dmac_hdc_device

class dmac_hdc_device : public device_t
{
<<<<<<< HEAD
public:
	// construction/destruction
	dmac_hdc_device(const machine_config &mconfig, device_type type, const char *tag,
		device_t *owner, UINT32 clock, const char *name, const char *shortname);

	// optional information overrides
	virtual machine_config_constructor device_mconfig_additions() const;
	virtual const rom_entry *device_rom_region() const;

	DECLARE_READ8_MEMBER( dmac_scsi_r );
	DECLARE_WRITE8_MEMBER( dmac_scsi_w );
	DECLARE_WRITE_LINE_MEMBER( dmac_int_w );
	DECLARE_WRITE_LINE_MEMBER( dmac_cfgout_w ) { cfgout_w(state); }
	DECLARE_WRITE_LINE_MEMBER( scsi_irq_w );

protected:
	// device-level overrides
	virtual void device_start();
	virtual void device_reset();
=======
protected:
	// construction/destruction
	dmac_hdc_device(const machine_config &mconfig, device_type type, const char *tag, device_t *owner, uint32_t clock);

	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;

	// optional information overrides
	virtual void device_add_mconfig(machine_config &config) override;
	virtual const tiny_rom_entry *device_rom_region() const override;
>>>>>>> upstream/master

	// to slot
	virtual void cfgout_w(int state) = 0;
	virtual void int2_w(int state) = 0;
	virtual void int6_w(int state) = 0;

	// should be called when the ram size changes
	void resize_ram(int config);

	// amiga interrupt target, int 2 or 6
	bool m_int6;

	// sub-devices
<<<<<<< HEAD
	required_device<dmac_device> m_dmac;
	required_device<wd33c93_device> m_wdc;

	dynamic_buffer m_ram;
=======
	required_device<amiga_dmac_device> m_dmac;
	required_device<wd33c93_device> m_wdc;

	std::vector<uint8_t> m_ram;

private:
	DECLARE_READ8_MEMBER( dmac_scsi_r );
	DECLARE_WRITE8_MEMBER( dmac_scsi_w );
	DECLARE_WRITE_LINE_MEMBER( dmac_int_w );
	DECLARE_WRITE_LINE_MEMBER( dmac_cfgout_w ) { cfgout_w(state); }
	DECLARE_WRITE_LINE_MEMBER( scsi_irq_w );
>>>>>>> upstream/master
};

// ======================> a590_device

class a590_device : public dmac_hdc_device, public device_exp_card_interface
{
public:
	// construction/destruction
<<<<<<< HEAD
	a590_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

protected:
	// device-level overrides
	virtual void device_start();
	virtual void device_reset();

	// optional information overrides
	virtual ioport_constructor device_input_ports() const;

	// output to slot
	virtual void cfgout_w(int state) { m_slot->cfgout_w(state); }
	virtual void int2_w(int state) { m_slot->int2_w(state); }
	virtual void int6_w(int state) { m_slot->int6_w(state); }

	// input from slot
	virtual DECLARE_WRITE_LINE_MEMBER( cfgin_w );
=======
	a590_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;

	// optional information overrides
	virtual ioport_constructor device_input_ports() const override;

	// output to slot
	virtual void cfgout_w(int state) override { m_slot->cfgout_w(state); }
	virtual void int2_w(int state) override { m_slot->int2_w(state); }
	virtual void int6_w(int state) override { m_slot->int6_w(state); }

	// input from slot
	virtual DECLARE_WRITE_LINE_MEMBER( cfgin_w ) override;
>>>>>>> upstream/master

private:
	required_ioport m_dips;
	required_ioport m_jp1;
	required_ioport m_jp2;
	required_ioport m_jp4;
};

// ======================> a2091_device

class a2091_device : public dmac_hdc_device, public device_zorro2_card_interface
{
public:
	// construction/destruction
<<<<<<< HEAD
	a2091_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual void device_reset();

	// optional information overrides
	virtual ioport_constructor device_input_ports() const;

	// output to slot
	virtual void cfgout_w(int state) { m_slot->cfgout_w(state); }
	virtual void int2_w(int state) { m_slot->int2_w(state); }
	virtual void int6_w(int state) { m_slot->int6_w(state); }

	// input from slot
	virtual DECLARE_WRITE_LINE_MEMBER( cfgin_w );
=======
	a2091_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;

	// optional information overrides
	virtual ioport_constructor device_input_ports() const override;

	// output to slot
	virtual void cfgout_w(int state) override { m_slot->cfgout_w(state); }
	virtual void int2_w(int state) override { m_slot->int2_w(state); }
	virtual void int6_w(int state) override { m_slot->int6_w(state); }

	// input from slot
	virtual DECLARE_WRITE_LINE_MEMBER( cfgin_w ) override;
>>>>>>> upstream/master

private:
	required_ioport m_jp1;
	required_ioport m_jp2;
	required_ioport m_jp3;
	required_ioport m_jp5;
	required_ioport m_jp201;
};

// device type definition
<<<<<<< HEAD
extern const device_type A590;
extern const device_type A2091;

#endif
=======
DECLARE_DEVICE_TYPE(A590,  a590_device)
DECLARE_DEVICE_TYPE(A2091, a2091_device)

#endif // MAME_BUS_AMIGA_ZORRO_A590_H
>>>>>>> upstream/master
