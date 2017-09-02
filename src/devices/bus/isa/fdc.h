// license:BSD-3-Clause
// copyright-holders:Miodrag Milanovic
/**********************************************************************

    ISA 8 bit Floppy Disk Controller

**********************************************************************/
<<<<<<< HEAD
#pragma once

#ifndef ISA_FDC_H
#define ISA_FDC_H

#include "emu.h"
=======
#ifndef MAME_BUS_ISA_FDC_H
#define MAME_BUS_ISA_FDC_H

#pragma once

>>>>>>> upstream/master
#include "isa.h"
#include "machine/upd765.h"

//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

// ======================> isa8_fdc_device

class isa8_fdc_device :
	public device_t,
	public device_isa8_card_interface
{
public:
<<<<<<< HEAD
	// construction/destruction
	isa8_fdc_device(const machine_config &mconfig, device_type type, const char *name, const char *tag, device_t *owner, UINT32 clock, const char *shortname, const char *source);

	required_device<pc_fdc_interface> fdc;

=======
>>>>>>> upstream/master
	DECLARE_WRITE_LINE_MEMBER( irq_w );
	DECLARE_WRITE_LINE_MEMBER( drq_w );
	DECLARE_FLOPPY_FORMATS( floppy_formats );

protected:
<<<<<<< HEAD
	// device-level overrides
	virtual void device_start();
	virtual void device_reset();

	virtual UINT8 dack_r(int line);
	virtual void dack_w(int line, UINT8 data);
	virtual void eop_w(int state);
=======
	// construction/destruction
	isa8_fdc_device(const machine_config &mconfig, device_type type, const char *tag, device_t *owner, uint32_t clock);

	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;

	virtual uint8_t dack_r(int line) override;
	virtual void dack_w(int line, uint8_t data) override;
	virtual void eop_w(int state) override;

	required_device<pc_fdc_interface> fdc;
>>>>>>> upstream/master
};

class isa8_fdc_xt_device : public isa8_fdc_device {
public:
<<<<<<< HEAD
	isa8_fdc_xt_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
	virtual machine_config_constructor device_mconfig_additions() const;
=======
	isa8_fdc_xt_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

protected:
	virtual void device_add_mconfig(machine_config &config) override;
>>>>>>> upstream/master
};

class isa8_fdc_at_device : public isa8_fdc_device {
public:
<<<<<<< HEAD
	isa8_fdc_at_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
	virtual machine_config_constructor device_mconfig_additions() const;
=======
	isa8_fdc_at_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

protected:
	virtual void device_add_mconfig(machine_config &config) override;
>>>>>>> upstream/master
};

class isa8_fdc_smc_device : public isa8_fdc_device {
public:
<<<<<<< HEAD
	isa8_fdc_smc_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
	virtual machine_config_constructor device_mconfig_additions() const;
=======
	isa8_fdc_smc_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

protected:
	virtual void device_add_mconfig(machine_config &config) override;
>>>>>>> upstream/master
};

class isa8_fdc_ps2_device : public isa8_fdc_device {
public:
<<<<<<< HEAD
	isa8_fdc_ps2_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
	virtual machine_config_constructor device_mconfig_additions() const;
=======
	isa8_fdc_ps2_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

protected:
	virtual void device_add_mconfig(machine_config &config) override;
>>>>>>> upstream/master
};

class isa8_fdc_superio_device : public isa8_fdc_device {
public:
<<<<<<< HEAD
	isa8_fdc_superio_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
	virtual machine_config_constructor device_mconfig_additions() const;
};

// device type definition
extern const device_type ISA8_FDC_XT;
extern const device_type ISA8_FDC_AT;
extern const device_type ISA8_FDC_SMC;
extern const device_type ISA8_FDC_PS2;
extern const device_type ISA8_FDC_SUPERIO;

#endif  /* ISA_FDC_H */
=======
	isa8_fdc_superio_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

protected:
	virtual void device_add_mconfig(machine_config &config) override;
};

// device type definition
DECLARE_DEVICE_TYPE(ISA8_FDC_XT,      isa8_fdc_xt_device)
DECLARE_DEVICE_TYPE(ISA8_FDC_AT,      isa8_fdc_at_device)
DECLARE_DEVICE_TYPE(ISA8_FDC_SMC,     isa8_fdc_smc_device)
DECLARE_DEVICE_TYPE(ISA8_FDC_PS2,     isa8_fdc_ps2_device)
DECLARE_DEVICE_TYPE(ISA8_FDC_SUPERIO, isa8_fdc_superio_device)

#endif // MAME_BUS_ISA_FDC_H
>>>>>>> upstream/master
