// license:BSD-3-Clause
// copyright-holders:Alex W. Jackson
<<<<<<< HEAD
#pragma once

#ifndef __NAMCOMCU_H__
#define __NAMCOMCU_H__
=======
#ifndef MAME_MACHINE_NAMCOMCU_H
#define MAME_MACHINE_NAMCOMCU_H

#pragma once
>>>>>>> upstream/master

#include "cpu/m37710/m37710.h"


class namco_c69_device : public m37702m2_device
{
public:
<<<<<<< HEAD
	namco_c69_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
protected:
	virtual const rom_entry *device_rom_region() const;
=======
	namco_c69_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
protected:
	virtual const tiny_rom_entry *device_rom_region() const override;
>>>>>>> upstream/master
};


class namco_c70_device : public m37702m2_device
{
public:
<<<<<<< HEAD
	namco_c70_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
protected:
	virtual const rom_entry *device_rom_region() const;
=======
	namco_c70_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
protected:
	virtual const tiny_rom_entry *device_rom_region() const override;
>>>>>>> upstream/master
};


class namco_c74_device : public m37702m2_device
{
public:
<<<<<<< HEAD
	namco_c74_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
protected:
	virtual const rom_entry *device_rom_region() const;
=======
	namco_c74_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
protected:
	virtual const tiny_rom_entry *device_rom_region() const override;
>>>>>>> upstream/master
};


class namco_c75_device : public m37702m2_device
{
public:
<<<<<<< HEAD
	namco_c75_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
protected:
	virtual const rom_entry *device_rom_region() const;
=======
	namco_c75_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
protected:
	virtual const tiny_rom_entry *device_rom_region() const override;
>>>>>>> upstream/master
};


class namco_c76_device : public m37702m2_device
{
public:
<<<<<<< HEAD
	namco_c76_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
protected:
	virtual const rom_entry *device_rom_region() const;
};


extern const device_type NAMCO_C69;
extern const device_type NAMCO_C70;
extern const device_type NAMCO_C74;
extern const device_type NAMCO_C75;
extern const device_type NAMCO_C76;


#endif
=======
	namco_c76_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
protected:
	virtual const tiny_rom_entry *device_rom_region() const override;
};


DECLARE_DEVICE_TYPE(NAMCO_C69, namco_c69_device)
DECLARE_DEVICE_TYPE(NAMCO_C70, namco_c70_device)
DECLARE_DEVICE_TYPE(NAMCO_C74, namco_c74_device)
DECLARE_DEVICE_TYPE(NAMCO_C75, namco_c75_device)
DECLARE_DEVICE_TYPE(NAMCO_C76, namco_c76_device)


#endif // MAME_MACHINE_NAMCOMCU_H
>>>>>>> upstream/master
