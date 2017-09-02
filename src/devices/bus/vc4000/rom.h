// license:BSD-3-Clause
// copyright-holders:Fabio Priuli
<<<<<<< HEAD
#ifndef __VC4000_ROM_H
#define __VC4000_ROM_H
=======
#ifndef MAME_BUS_VC4000_ROM_H
#define MAME_BUS_VC4000_ROM_H
>>>>>>> upstream/master

#include "slot.h"


// ======================> vc4000_rom_device

class vc4000_rom_device : public device_t,
						public device_vc4000_cart_interface
{
public:
	// construction/destruction
<<<<<<< HEAD
	vc4000_rom_device(const machine_config &mconfig, device_type type, const char *name, const char *tag, device_t *owner, UINT32 clock, const char *shortname, const char *source);
	vc4000_rom_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start() {}
	virtual void device_reset() {}

	// reading and writing
	virtual DECLARE_READ8_MEMBER(read_rom);
=======
	vc4000_rom_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// reading and writing
	virtual DECLARE_READ8_MEMBER(read_rom) override;

protected:
	vc4000_rom_device(const machine_config &mconfig, device_type type, const char *tag, device_t *owner, uint32_t clock);

	// device-level overrides
	virtual void device_start() override { }
	virtual void device_reset() override { }
>>>>>>> upstream/master
};

// ======================> vc4000_rom4k_device

class vc4000_rom4k_device : public vc4000_rom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	vc4000_rom4k_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
=======
	vc4000_rom4k_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
>>>>>>> upstream/master
};

// ======================> vc4000_ram1k_device

class vc4000_ram1k_device : public vc4000_rom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	vc4000_ram1k_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// reading and writing
	virtual DECLARE_READ8_MEMBER(read_ram);
	virtual DECLARE_WRITE8_MEMBER(write_ram);
=======
	vc4000_ram1k_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// reading and writing
	virtual DECLARE_READ8_MEMBER(read_ram) override;
	virtual DECLARE_WRITE8_MEMBER(write_ram) override;
>>>>>>> upstream/master
};

// ======================> vc4000_chess2_device

class vc4000_chess2_device : public vc4000_rom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	vc4000_chess2_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// reading and writing
	virtual DECLARE_READ8_MEMBER(extra_rom);
	virtual DECLARE_READ8_MEMBER(read_ram);
	virtual DECLARE_WRITE8_MEMBER(write_ram);
=======
	vc4000_chess2_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// reading and writing
	virtual DECLARE_READ8_MEMBER(extra_rom) override;
	virtual DECLARE_READ8_MEMBER(read_ram) override;
	virtual DECLARE_WRITE8_MEMBER(write_ram) override;
>>>>>>> upstream/master
};



<<<<<<< HEAD


// device type definition
extern const device_type VC4000_ROM_STD;
extern const device_type VC4000_ROM_ROM4K;
extern const device_type VC4000_ROM_RAM1K;
extern const device_type VC4000_ROM_CHESS2;


#endif
=======
// device type definition
DECLARE_DEVICE_TYPE(VC4000_ROM_STD,    vc4000_rom_device)
DECLARE_DEVICE_TYPE(VC4000_ROM_ROM4K,  vc4000_rom4k_device)
DECLARE_DEVICE_TYPE(VC4000_ROM_RAM1K,  vc4000_ram1k_device)
DECLARE_DEVICE_TYPE(VC4000_ROM_CHESS2, vc4000_chess2_device)

#endif // MAME_BUS_VC4000_ROM_H
>>>>>>> upstream/master
