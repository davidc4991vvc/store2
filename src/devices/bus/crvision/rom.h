// license:BSD-3-Clause
// copyright-holders:Fabio Priuli
<<<<<<< HEAD
#ifndef __CRVISION_ROM_H
#define __CRVISION_ROM_H
=======
#ifndef MAME_BUS_CPC_CRVISION_ROM_H
#define MAME_BUS_CPC_CRVISION_ROM_H

#pragma once
>>>>>>> upstream/master

#include "slot.h"


// ======================> crvision_rom_device

class crvision_rom_device : public device_t,
						public device_crvision_cart_interface
{
public:
	// construction/destruction
<<<<<<< HEAD
	crvision_rom_device(const machine_config &mconfig, device_type type, const char *name, const char *tag, device_t *owner, UINT32 clock, const char *shortname, const char *source);
	crvision_rom_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start() {}
	virtual void device_reset() {}

	// reading and writing
	virtual DECLARE_READ8_MEMBER(read_rom80);
=======
	crvision_rom_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// reading and writing
	virtual DECLARE_READ8_MEMBER(read_rom80) override;

protected:
	crvision_rom_device(const machine_config &mconfig, device_type type, const char *tag, device_t *owner, uint32_t clock);

	// device-level overrides
	virtual void device_start() override {}
	virtual void device_reset() override {}
>>>>>>> upstream/master
};

// ======================> crvision_rom6k_device

class crvision_rom6k_device : public crvision_rom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	crvision_rom6k_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// reading and writing
	virtual DECLARE_READ8_MEMBER(read_rom80);
=======
	crvision_rom6k_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// reading and writing
	virtual DECLARE_READ8_MEMBER(read_rom80) override;
>>>>>>> upstream/master
};

// ======================> crvision_rom8k_device

class crvision_rom8k_device : public crvision_rom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	crvision_rom8k_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// reading and writing
	virtual DECLARE_READ8_MEMBER(read_rom80);
=======
	crvision_rom8k_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// reading and writing
	virtual DECLARE_READ8_MEMBER(read_rom80) override;
>>>>>>> upstream/master
};

// ======================> crvision_rom10k_device

class crvision_rom10k_device : public crvision_rom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	crvision_rom10k_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// reading and writing
	virtual DECLARE_READ8_MEMBER(read_rom40);
	virtual DECLARE_READ8_MEMBER(read_rom80);
=======
	crvision_rom10k_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// reading and writing
	virtual DECLARE_READ8_MEMBER(read_rom40) override;
	virtual DECLARE_READ8_MEMBER(read_rom80) override;
>>>>>>> upstream/master
};

// ======================> crvision_rom12k_device

class crvision_rom12k_device : public crvision_rom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	crvision_rom12k_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// reading and writing
	virtual DECLARE_READ8_MEMBER(read_rom40);
	virtual DECLARE_READ8_MEMBER(read_rom80);
=======
	crvision_rom12k_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// reading and writing
	virtual DECLARE_READ8_MEMBER(read_rom40) override;
	virtual DECLARE_READ8_MEMBER(read_rom80) override;
>>>>>>> upstream/master
};

// ======================> crvision_rom16k_device

class crvision_rom16k_device : public crvision_rom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	crvision_rom16k_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// reading and writing
	virtual DECLARE_READ8_MEMBER(read_rom80);
=======
	crvision_rom16k_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// reading and writing
	virtual DECLARE_READ8_MEMBER(read_rom80) override;
>>>>>>> upstream/master
};

// ======================> crvision_rom18k_device

class crvision_rom18k_device : public crvision_rom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	crvision_rom18k_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// reading and writing
	virtual DECLARE_READ8_MEMBER(read_rom40);
	virtual DECLARE_READ8_MEMBER(read_rom80);
};





// device type definition
extern const device_type CRVISION_ROM_4K;
extern const device_type CRVISION_ROM_6K;
extern const device_type CRVISION_ROM_8K;
extern const device_type CRVISION_ROM_10K;
extern const device_type CRVISION_ROM_12K;
extern const device_type CRVISION_ROM_16K;
extern const device_type CRVISION_ROM_18K;


#endif
=======
	crvision_rom18k_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// reading and writing
	virtual DECLARE_READ8_MEMBER(read_rom40) override;
	virtual DECLARE_READ8_MEMBER(read_rom80) override;
};


// device type definition
DECLARE_DEVICE_TYPE(CRVISION_ROM_4K,  crvision_rom_device)
DECLARE_DEVICE_TYPE(CRVISION_ROM_6K,  crvision_rom6k_device)
DECLARE_DEVICE_TYPE(CRVISION_ROM_8K,  crvision_rom8k_device)
DECLARE_DEVICE_TYPE(CRVISION_ROM_10K, crvision_rom10k_device)
DECLARE_DEVICE_TYPE(CRVISION_ROM_12K, crvision_rom12k_device)
DECLARE_DEVICE_TYPE(CRVISION_ROM_16K, crvision_rom16k_device)
DECLARE_DEVICE_TYPE(CRVISION_ROM_18K, crvision_rom18k_device)


#endif // MAME_BUS_CPC_CRVISION_ROM_H
>>>>>>> upstream/master
