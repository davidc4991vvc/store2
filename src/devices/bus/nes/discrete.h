// license:BSD-3-Clause
// copyright-holders:Fabio Priuli
<<<<<<< HEAD
#ifndef __NES_DISCRETE_H
#define __NES_DISCRETE_H
=======
#ifndef MAME_BUS_NES_DISCRETE_H
#define MAME_BUS_NES_DISCRETE_H

#pragma once
>>>>>>> upstream/master

#include "nxrom.h"


// ======================> nes_74x161x161x32_device

class nes_74x161x161x32_device : public nes_nrom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_74x161x161x32_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual DECLARE_WRITE8_MEMBER(write_h);

	virtual void pcb_reset();
=======
	nes_74x161x161x32_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_WRITE8_MEMBER(write_h) override;

	virtual void pcb_reset() override;

protected:
	// device-level overrides
	virtual void device_start() override;
>>>>>>> upstream/master
};


// ======================> nes_74x139x74_device

class nes_74x139x74_device : public nes_nrom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_74x139x74_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual DECLARE_WRITE8_MEMBER(write_m);

	virtual void pcb_reset();
=======
	nes_74x139x74_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_WRITE8_MEMBER(write_m) override;

	virtual void pcb_reset() override;

protected:
	// device-level overrides
	virtual void device_start() override;
>>>>>>> upstream/master
};


// ======================> nes_74x377_device

class nes_74x377_device : public nes_nrom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_74x377_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual DECLARE_WRITE8_MEMBER(write_h);

	virtual void pcb_reset();
=======
	nes_74x377_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_WRITE8_MEMBER(write_h) override;

	virtual void pcb_reset() override;

protected:
	// device-level overrides
	virtual void device_start() override;
>>>>>>> upstream/master
};


// ======================> nes_74x161x138_device

class nes_74x161x138_device : public nes_nrom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_74x161x138_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual DECLARE_WRITE8_MEMBER(write_m);

	virtual void pcb_reset();
};



// device type definition
extern const device_type NES_74X161X161X32;
extern const device_type NES_74X139X74;
extern const device_type NES_74X377;
extern const device_type NES_74X161X138;

#endif
=======
	nes_74x161x138_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_WRITE8_MEMBER(write_m) override;

	virtual void pcb_reset() override;

protected:
	// device-level overrides
	virtual void device_start() override;
};


// device type definition
DECLARE_DEVICE_TYPE(NES_74X161X161X32, nes_74x161x161x32_device)
DECLARE_DEVICE_TYPE(NES_74X139X74,     nes_74x139x74_device)
DECLARE_DEVICE_TYPE(NES_74X377,        nes_74x377_device)
DECLARE_DEVICE_TYPE(NES_74X161X138,    nes_74x161x138_device)

#endif // MAME_BUS_NES_DISCRETE_H
>>>>>>> upstream/master
