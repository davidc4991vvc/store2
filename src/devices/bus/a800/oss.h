// license:BSD-3-Clause
// copyright-holders:Fabio Priuli
<<<<<<< HEAD
#ifndef __A800_OSS_H
#define __A800_OSS_H
=======
#ifndef MAME_BUS_A800_OSS_H
#define MAME_BUS_A800_OSS_H

#pragma once
>>>>>>> upstream/master

#include "rom.h"


// ======================> a800_rom_oss8k_device

class a800_rom_oss8k_device : public a800_rom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	a800_rom_oss8k_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual void device_reset();

	virtual DECLARE_READ8_MEMBER(read_80xx);
	virtual DECLARE_WRITE8_MEMBER(write_d5xx);

protected:
=======
	a800_rom_oss8k_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_READ8_MEMBER(read_80xx) override;
	virtual DECLARE_WRITE8_MEMBER(write_d5xx) override;

protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;

>>>>>>> upstream/master
	int m_bank;
};


// ======================> a800_rom_oss34_device

class a800_rom_oss34_device : public a800_rom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	a800_rom_oss34_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual void device_reset();

	virtual DECLARE_READ8_MEMBER(read_80xx);
	virtual DECLARE_WRITE8_MEMBER(write_d5xx);

protected:
=======
	a800_rom_oss34_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_READ8_MEMBER(read_80xx) override;
	virtual DECLARE_WRITE8_MEMBER(write_d5xx) override;

protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;

>>>>>>> upstream/master
	int m_bank;
};


// ======================> a800_rom_oss43_device

class a800_rom_oss43_device : public a800_rom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	a800_rom_oss43_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual void device_reset();

	virtual DECLARE_READ8_MEMBER(read_80xx);
	virtual DECLARE_WRITE8_MEMBER(write_d5xx);

protected:
=======
	a800_rom_oss43_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_READ8_MEMBER(read_80xx) override;
	virtual DECLARE_WRITE8_MEMBER(write_d5xx) override;

protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;

>>>>>>> upstream/master
	int m_bank;
};


// ======================> a800_rom_oss91_device

class a800_rom_oss91_device : public a800_rom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	a800_rom_oss91_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual void device_reset();

	virtual DECLARE_READ8_MEMBER(read_80xx);
	virtual DECLARE_WRITE8_MEMBER(write_d5xx);

protected:
=======
	a800_rom_oss91_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_READ8_MEMBER(read_80xx) override;
	virtual DECLARE_WRITE8_MEMBER(write_d5xx) override;

protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;

>>>>>>> upstream/master
	int m_bank;
};



// device type definition
<<<<<<< HEAD
extern const device_type A800_ROM_OSS8K;
extern const device_type A800_ROM_OSS34;
extern const device_type A800_ROM_OSS43;
extern const device_type A800_ROM_OSS91;


#endif
=======
DECLARE_DEVICE_TYPE(A800_ROM_OSS8K, a800_rom_oss8k_device)
DECLARE_DEVICE_TYPE(A800_ROM_OSS34, a800_rom_oss34_device)
DECLARE_DEVICE_TYPE(A800_ROM_OSS43, a800_rom_oss43_device)
DECLARE_DEVICE_TYPE(A800_ROM_OSS91, a800_rom_oss91_device)


#endif // MAME_BUS_A800_OSS_H
>>>>>>> upstream/master
