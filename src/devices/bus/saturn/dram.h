// license:BSD-3-Clause
// copyright-holders:Fabio Priuli
<<<<<<< HEAD
#ifndef __SAT_DRAM_H
#define __SAT_DRAM_H
=======
#ifndef MAME_BUS_SATURN_DRAM_H
#define MAME_BUS_SATURN_DRAM_H
>>>>>>> upstream/master

#include "sat_slot.h"


// ======================> saturn_dram_device

class saturn_dram_device : public device_t,
							public device_sat_cart_interface
{
public:
<<<<<<< HEAD
	// construction/destruction
	saturn_dram_device(const machine_config &mconfig, device_type type, const char *name, const char *tag, device_t *owner, UINT32 clock, const char *shortname, const char *source);

	// device-level overrides
	virtual void device_start();
	virtual void device_reset();

	// reading and writing
	virtual DECLARE_READ32_MEMBER(read_ext_dram0);
	virtual DECLARE_READ32_MEMBER(read_ext_dram1);
	virtual DECLARE_WRITE32_MEMBER(write_ext_dram0);
	virtual DECLARE_WRITE32_MEMBER(write_ext_dram1);
=======
	// reading and writing
	virtual DECLARE_READ32_MEMBER(read_ext_dram0) override;
	virtual DECLARE_READ32_MEMBER(read_ext_dram1) override;
	virtual DECLARE_WRITE32_MEMBER(write_ext_dram0) override;
	virtual DECLARE_WRITE32_MEMBER(write_ext_dram1) override;

protected:
	// construction/destruction
	saturn_dram_device(const machine_config &mconfig, device_type type, const char *tag, device_t *owner, uint32_t clock, int cart_type);

	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;
>>>>>>> upstream/master
};

class saturn_dram8mb_device : public saturn_dram_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	saturn_dram8mb_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
=======
	saturn_dram8mb_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
>>>>>>> upstream/master
};

class saturn_dram32mb_device : public saturn_dram_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	saturn_dram32mb_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
=======
	saturn_dram32mb_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
>>>>>>> upstream/master
};



// device type definition
<<<<<<< HEAD
extern const device_type SATURN_DRAM_8MB;
extern const device_type SATURN_DRAM_32MB;

#endif
=======
DECLARE_DEVICE_TYPE(SATURN_DRAM_8MB,  saturn_dram8mb_device)
DECLARE_DEVICE_TYPE(SATURN_DRAM_32MB, saturn_dram32mb_device)

#endif // MAME_BUS_SATURN_DRAM_H
>>>>>>> upstream/master
