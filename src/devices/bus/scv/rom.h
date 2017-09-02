// license:BSD-3-Clause
// copyright-holders:Fabio Priuli
<<<<<<< HEAD
#ifndef __SCV_ROM_H
#define __SCV_ROM_H
=======
#ifndef MAME_BUS_SCV_ROM_H
#define MAME_BUS_SCV_ROM_H

#pragma once
>>>>>>> upstream/master

#include "slot.h"


// ======================> scv_rom8_device

class scv_rom8_device : public device_t,
						public device_scv_cart_interface
{
public:
	// construction/destruction
<<<<<<< HEAD
	scv_rom8_device(const machine_config &mconfig, device_type type, const char *name, const char *tag, device_t *owner, UINT32 clock, const char *shortname, const char *source);
	scv_rom8_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start() {}
	virtual void device_reset() {}

	// reading and writing
	virtual DECLARE_READ8_MEMBER(read_cart);
=======
	scv_rom8_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// reading and writing
	virtual DECLARE_READ8_MEMBER(read_cart) override;

protected:
	scv_rom8_device(const machine_config &mconfig, device_type type, const char *tag, device_t *owner, uint32_t clock);

	// device-level overrides
	virtual void device_start() override { }
	virtual void device_reset() override { }
>>>>>>> upstream/master
};

// ======================> scv_rom16_device

class scv_rom16_device : public scv_rom8_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	scv_rom16_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// reading and writing
	virtual DECLARE_READ8_MEMBER(read_cart);
=======
	scv_rom16_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// reading and writing
	virtual DECLARE_READ8_MEMBER(read_cart) override;
>>>>>>> upstream/master
};


// ======================> scv_rom32_device

class scv_rom32_device : public scv_rom8_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	scv_rom32_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// reading and writing
	virtual DECLARE_READ8_MEMBER(read_cart);
=======
	scv_rom32_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// reading and writing
	virtual DECLARE_READ8_MEMBER(read_cart) override;
>>>>>>> upstream/master
};


// ======================> scv_rom32ram8_device

class scv_rom32ram8_device : public scv_rom8_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	scv_rom32ram8_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual void device_reset();

	// reading and writing
	virtual DECLARE_READ8_MEMBER(read_cart);
	virtual DECLARE_WRITE8_MEMBER(write_cart);
	virtual DECLARE_WRITE8_MEMBER(write_bank);

private:
	UINT8 m_ram_enabled;
=======
	scv_rom32ram8_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// reading and writing
	virtual DECLARE_READ8_MEMBER(read_cart) override;
	virtual DECLARE_WRITE8_MEMBER(write_cart) override;
	virtual DECLARE_WRITE8_MEMBER(write_bank) override;

protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;

private:
	uint8_t m_ram_enabled;
>>>>>>> upstream/master
};


// ======================> scv_rom64_device

class scv_rom64_device : public scv_rom8_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	scv_rom64_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual void device_reset();

	// reading and writing
	virtual DECLARE_READ8_MEMBER(read_cart);
	virtual DECLARE_WRITE8_MEMBER(write_bank);

private:
	UINT8 m_bank_base;
=======
	scv_rom64_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;

	// reading and writing
	virtual DECLARE_READ8_MEMBER(read_cart) override;
	virtual DECLARE_WRITE8_MEMBER(write_bank) override;

private:
	uint8_t m_bank_base;
>>>>>>> upstream/master
};


// ======================> scv_rom128_device

class scv_rom128_device : public scv_rom8_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	scv_rom128_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual void device_reset();

	// reading and writing
	virtual DECLARE_READ8_MEMBER(read_cart);
	virtual DECLARE_WRITE8_MEMBER(write_bank);

private:
	UINT8 m_bank_base;
=======
	scv_rom128_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// reading and writing
	virtual DECLARE_READ8_MEMBER(read_cart) override;
	virtual DECLARE_WRITE8_MEMBER(write_bank) override;

protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;

private:
	uint8_t m_bank_base;
>>>>>>> upstream/master
};


// ======================> scv_rom128ram4_device

class scv_rom128ram4_device : public scv_rom8_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	scv_rom128ram4_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual void device_reset();

	// reading and writing
	virtual DECLARE_READ8_MEMBER(read_cart);
	virtual DECLARE_WRITE8_MEMBER(write_cart);
	virtual DECLARE_WRITE8_MEMBER(write_bank);

private:
	UINT8 m_bank_base, m_ram_enabled;
};



// device type definition
extern const device_type SCV_ROM8K;
extern const device_type SCV_ROM16K;
extern const device_type SCV_ROM32K;
extern const device_type SCV_ROM32K_RAM8K;
extern const device_type SCV_ROM64K;
extern const device_type SCV_ROM128K;
extern const device_type SCV_ROM128K_RAM4K;



#endif
=======
	scv_rom128ram4_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// reading and writing
	virtual DECLARE_READ8_MEMBER(read_cart) override;
	virtual DECLARE_WRITE8_MEMBER(write_cart) override;
	virtual DECLARE_WRITE8_MEMBER(write_bank) override;

protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;

private:
	uint8_t m_bank_base, m_ram_enabled;
};


// device type definition
DECLARE_DEVICE_TYPE(SCV_ROM8K,         scv_rom8_device)
DECLARE_DEVICE_TYPE(SCV_ROM16K,        scv_rom16_device)
DECLARE_DEVICE_TYPE(SCV_ROM32K,        scv_rom32_device)
DECLARE_DEVICE_TYPE(SCV_ROM32K_RAM8K,  scv_rom32ram8_device)
DECLARE_DEVICE_TYPE(SCV_ROM64K,        scv_rom64_device)
DECLARE_DEVICE_TYPE(SCV_ROM128K,       scv_rom128_device)
DECLARE_DEVICE_TYPE(SCV_ROM128K_RAM4K, scv_rom128ram4_device)

#endif // MAME_BUS_SCV_ROM_H
>>>>>>> upstream/master
