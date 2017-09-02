// license:BSD-3-Clause
// copyright-holders:Fabio Priuli
<<<<<<< HEAD
#ifndef __A78_XBOARD_H
#define __A78_XBOARD_H
=======
#ifndef MAME_BUS_A7800_XBOARD_H
#define MAME_BUS_A7800_XBOARD_H

#pragma once
>>>>>>> upstream/master

#include "a78_slot.h"
#include "rom.h"
#include "sound/pokey.h"
<<<<<<< HEAD
#include "sound/2151intf.h"
=======
#include "sound/ym2151.h"
>>>>>>> upstream/master


// ======================> a78_xboard_device

class a78_xboard_device : public a78_rom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	a78_xboard_device(const machine_config &mconfig, device_type type, const char *name, const char *tag, device_t *owner, UINT32 clock, const char *shortname, const char *source);
	a78_xboard_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual machine_config_constructor device_mconfig_additions() const;
	virtual void device_reset();

	// reading and writing
	virtual DECLARE_READ8_MEMBER(read_04xx);
	virtual DECLARE_WRITE8_MEMBER(write_04xx);
	virtual DECLARE_READ8_MEMBER(read_40xx);
	virtual DECLARE_WRITE8_MEMBER(write_40xx);

protected:
=======
	a78_xboard_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// reading and writing
	virtual DECLARE_READ8_MEMBER(read_04xx) override;
	virtual DECLARE_WRITE8_MEMBER(write_04xx) override;
	virtual DECLARE_READ8_MEMBER(read_40xx) override;
	virtual DECLARE_WRITE8_MEMBER(write_40xx) override;

protected:
	a78_xboard_device(const machine_config &mconfig, device_type type, const char *tag, device_t *owner, uint32_t clock);

	virtual void device_start() override;
	virtual void device_reset() override;
	virtual void device_add_mconfig(machine_config &config) override;

>>>>>>> upstream/master
	required_device<a78_cart_slot_device> m_xbslot;
	required_device<pokey_device> m_pokey;
	int m_reg, m_ram_bank;
};


// ======================> a78_xm_device

class a78_xm_device : public a78_xboard_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	a78_xm_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual machine_config_constructor device_mconfig_additions() const;
	virtual void device_reset();

	// reading and writing
	virtual DECLARE_READ8_MEMBER(read_04xx);
	virtual DECLARE_WRITE8_MEMBER(write_04xx);
	virtual DECLARE_READ8_MEMBER(read_10xx);
	virtual DECLARE_WRITE8_MEMBER(write_10xx);
	virtual DECLARE_READ8_MEMBER(read_30xx);

protected:
=======
	a78_xm_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// reading and writing
	virtual DECLARE_READ8_MEMBER(read_04xx) override;
	virtual DECLARE_WRITE8_MEMBER(write_04xx) override;
	virtual DECLARE_READ8_MEMBER(read_10xx) override;
	virtual DECLARE_WRITE8_MEMBER(write_10xx) override;
	virtual DECLARE_READ8_MEMBER(read_30xx) override;

protected:
	virtual void device_start() override;
	virtual void device_reset() override;
	virtual void device_add_mconfig(machine_config &config) override;

>>>>>>> upstream/master
	required_device<ym2151_device> m_ym;
	int m_ym_enabled;
};



// device type definition
<<<<<<< HEAD
extern const device_type A78_XBOARD;
extern const device_type A78_XM;


#endif
=======
DECLARE_DEVICE_TYPE(A78_XBOARD, a78_xboard_device)
DECLARE_DEVICE_TYPE(A78_XM,     a78_xm_device)


#endif // MAME_BUS_A7800_XBOARD_H
>>>>>>> upstream/master
