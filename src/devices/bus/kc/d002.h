// license:BSD-3-Clause
// copyright-holders:Sandro Ronco
<<<<<<< HEAD
#pragma once

#ifndef __KC_D002_H__
#define __KC_D002_H__

#include "emu.h"
#include "kc.h"
#include "ram.h"
#include "rom.h"
#include "d004.h"
=======
#ifndef MAME_BUS_KC_D002_H
#define MAME_BUS_KC_D002_H

#pragma once

#include "kc.h"
>>>>>>> upstream/master

//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

// ======================> kc_d002_device

class kc_d002_device :
		public device_t,
		public device_kcexp_interface
{
public:
	// construction/destruction
<<<<<<< HEAD
	kc_d002_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// optional information overrides
	virtual machine_config_constructor device_mconfig_additions() const;
	virtual ioport_constructor device_input_ports() const;

=======
	kc_d002_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;

	// optional information overrides
	virtual void device_add_mconfig(machine_config &config) override;
	virtual ioport_constructor device_input_ports() const override;

	// kcexp_interface overrides
	virtual void read(offs_t offset, uint8_t &data) override;
	virtual void write(offs_t offset, uint8_t data) override;
	virtual void io_read(offs_t offset, uint8_t &data) override;
	virtual void io_write(offs_t offset, uint8_t data) override;
	virtual DECLARE_WRITE_LINE_MEMBER( mei_w ) override;

private:
>>>>>>> upstream/master
	// interface callbacks
	DECLARE_WRITE_LINE_MEMBER( out_irq_w );
	DECLARE_WRITE_LINE_MEMBER( out_nmi_w );
	DECLARE_WRITE_LINE_MEMBER( out_halt_w );

<<<<<<< HEAD
protected:
	// device-level overrides
	virtual void device_start();
	virtual void device_reset();

	// kcexp_interface overrides
	virtual void read(offs_t offset, UINT8 &data);
	virtual void write(offs_t offset, UINT8 data);
	virtual void io_read(offs_t offset, UINT8 &data);
	virtual void io_write(offs_t offset, UINT8 data);
	virtual DECLARE_WRITE_LINE_MEMBER( mei_w );

private:
	kcexp_slot_device *m_slot;

	// internal state
	kcexp_slot_device *m_expansions[5];
=======
	kcexp_slot_device *m_slot;

	// internal state
	required_device_array<kcexp_slot_device, 5> m_expansions;
>>>>>>> upstream/master
};


// device type definition
<<<<<<< HEAD
extern const device_type KC_D002;

#endif  /* __KC_D002_H__ */
=======
DECLARE_DEVICE_TYPE(KC_D002, kc_d002_device)

#endif // MAME_BUS_KC_D002_H
>>>>>>> upstream/master
