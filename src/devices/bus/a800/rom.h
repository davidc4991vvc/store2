// license:BSD-3-Clause
// copyright-holders:Fabio Priuli
<<<<<<< HEAD
#ifndef __A800_ROM_H
#define __A800_ROM_H
=======
#ifndef MAME_BUS_A800_ROM_H
#define MAME_BUS_A800_ROM_H

#pragma once
>>>>>>> upstream/master

#include "a800_slot.h"


// ======================> a800_rom_device

class a800_rom_device : public device_t,
						public device_a800_cart_interface
{
public:
	// construction/destruction
<<<<<<< HEAD
	a800_rom_device(const machine_config &mconfig, device_type type, const char *name, const char *tag, device_t *owner, UINT32 clock, const char *shortname, const char *source);
	a800_rom_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual void device_reset();

	virtual DECLARE_READ8_MEMBER(read_80xx);
=======
	a800_rom_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_READ8_MEMBER(read_80xx) override;

protected:
	a800_rom_device(const machine_config &mconfig, device_type type, const char *tag, device_t *owner, uint32_t clock);

	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;
>>>>>>> upstream/master
};


// ======================> a800_rom_bbsb_device

class a800_rom_bbsb_device : public a800_rom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	a800_rom_bbsb_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual void device_reset();

	virtual DECLARE_READ8_MEMBER(read_80xx);
	virtual DECLARE_WRITE8_MEMBER(write_80xx);

protected:
=======
	a800_rom_bbsb_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_READ8_MEMBER(read_80xx) override;
	virtual DECLARE_WRITE8_MEMBER(write_80xx) override;

protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;

>>>>>>> upstream/master
	int m_banks[2];
};


// ======================> a800_rom_williams_device

class a800_rom_williams_device : public a800_rom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	a800_rom_williams_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual void device_reset();

	virtual DECLARE_READ8_MEMBER(read_80xx);
	virtual DECLARE_WRITE8_MEMBER(write_d5xx);

protected:
=======
	a800_rom_williams_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_READ8_MEMBER(read_80xx) override;
	virtual DECLARE_WRITE8_MEMBER(write_d5xx) override;

protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;

>>>>>>> upstream/master
	int m_bank;
};


// ======================> a800_rom_express_device

class a800_rom_express_device : public a800_rom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	a800_rom_express_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual void device_reset();

	virtual DECLARE_READ8_MEMBER(read_80xx);
	virtual DECLARE_WRITE8_MEMBER(write_d5xx);

protected:
=======
	a800_rom_express_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_READ8_MEMBER(read_80xx) override;
	virtual DECLARE_WRITE8_MEMBER(write_d5xx) override;

protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;

>>>>>>> upstream/master
	int m_bank;
};


// ======================> a800_rom_blizzard_device

class a800_rom_blizzard_device : public a800_rom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	a800_rom_blizzard_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual void device_reset();

	virtual DECLARE_READ8_MEMBER(read_80xx);
=======
	a800_rom_blizzard_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_READ8_MEMBER(read_80xx) override;

protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;
>>>>>>> upstream/master
};


// ======================> a800_rom_turbo_device

class a800_rom_turbo_device : public a800_rom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	a800_rom_turbo_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual void device_reset();

	virtual DECLARE_READ8_MEMBER(read_80xx);
	virtual DECLARE_WRITE8_MEMBER(write_d5xx);

protected:
=======
	a800_rom_turbo_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_READ8_MEMBER(read_80xx) override;
	virtual DECLARE_WRITE8_MEMBER(write_d5xx) override;

protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;

>>>>>>> upstream/master
	int m_bank;
};


// ======================> a800_rom_telelink2_device

class a800_rom_telelink2_device : public a800_rom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	a800_rom_telelink2_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	virtual DECLARE_READ8_MEMBER(read_80xx);
	virtual DECLARE_WRITE8_MEMBER(write_80xx);
	virtual DECLARE_READ8_MEMBER(read_d5xx);
	virtual DECLARE_WRITE8_MEMBER(write_d5xx);
=======
	a800_rom_telelink2_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_READ8_MEMBER(read_80xx) override;
	virtual DECLARE_WRITE8_MEMBER(write_80xx) override;
	virtual DECLARE_READ8_MEMBER(read_d5xx) override;
	virtual DECLARE_WRITE8_MEMBER(write_d5xx) override;
>>>>>>> upstream/master
};


// ======================> a800_rom_microcalc_device

class a800_rom_microcalc_device : public a800_rom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	a800_rom_microcalc_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual void device_reset();

	virtual DECLARE_READ8_MEMBER(read_80xx);
	virtual DECLARE_WRITE8_MEMBER(write_d5xx);

protected:
=======
	a800_rom_microcalc_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_READ8_MEMBER(read_80xx) override;
	virtual DECLARE_WRITE8_MEMBER(write_d5xx) override;

protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;

>>>>>>> upstream/master
	int m_bank;
};


// ======================> xegs_rom_device

class xegs_rom_device : public a800_rom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	xegs_rom_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual void device_reset();

	virtual DECLARE_READ8_MEMBER(read_80xx);
	virtual DECLARE_WRITE8_MEMBER(write_d5xx);
=======
	xegs_rom_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;

	virtual DECLARE_READ8_MEMBER(read_80xx) override;
	virtual DECLARE_WRITE8_MEMBER(write_d5xx) override;
>>>>>>> upstream/master

protected:
	int m_bank;
};


// ======================> a5200_rom_2chips_device

class a5200_rom_2chips_device : public a800_rom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	a5200_rom_2chips_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	virtual DECLARE_READ8_MEMBER(read_80xx);
=======
	a5200_rom_2chips_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_READ8_MEMBER(read_80xx) override;
>>>>>>> upstream/master
};


// ======================> a5200_rom_bbsb_device

class a5200_rom_bbsb_device : public a800_rom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	a5200_rom_bbsb_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual void device_reset();

	virtual DECLARE_READ8_MEMBER(read_80xx);
	virtual DECLARE_WRITE8_MEMBER(write_80xx);

protected:
=======
	a5200_rom_bbsb_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_READ8_MEMBER(read_80xx) override;
	virtual DECLARE_WRITE8_MEMBER(write_80xx) override;

protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;

>>>>>>> upstream/master
	int m_banks[2];
};



// device type definition
<<<<<<< HEAD
extern const device_type A800_ROM;
extern const device_type A800_ROM_BBSB;
extern const device_type A800_ROM_WILLIAMS;
extern const device_type A800_ROM_EXPRESS;
extern const device_type A800_ROM_TURBO;
extern const device_type A800_ROM_TELELINK2;
extern const device_type A800_ROM_MICROCALC;
extern const device_type XEGS_ROM;
extern const device_type A5200_ROM_2CHIPS;
extern const device_type A5200_ROM_BBSB;


#endif
=======
DECLARE_DEVICE_TYPE(A800_ROM,           a800_rom_device)
DECLARE_DEVICE_TYPE(A800_ROM_BBSB,      a800_rom_bbsb_device)
DECLARE_DEVICE_TYPE(A800_ROM_WILLIAMS,  a800_rom_williams_device)
DECLARE_DEVICE_TYPE(A800_ROM_EXPRESS,   a800_rom_express_device)
DECLARE_DEVICE_TYPE(A800_ROM_TURBO,     a800_rom_turbo_device)
DECLARE_DEVICE_TYPE(A800_ROM_TELELINK2, a800_rom_telelink2_device)
DECLARE_DEVICE_TYPE(A800_ROM_MICROCALC, a800_rom_microcalc_device)
DECLARE_DEVICE_TYPE(XEGS_ROM,           xegs_rom_device)
DECLARE_DEVICE_TYPE(A5200_ROM_2CHIPS,   a5200_rom_2chips_device)
DECLARE_DEVICE_TYPE(A5200_ROM_BBSB,     a5200_rom_bbsb_device)


#endif // MAME_BUS_A800_ROM_H
>>>>>>> upstream/master
