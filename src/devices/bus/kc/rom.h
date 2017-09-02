// license:BSD-3-Clause
// copyright-holders:Sandro Ronco
<<<<<<< HEAD
#pragma once

#ifndef __KC_ROM_H__
#define __KC_ROM_H__

#include "emu.h"
=======
#ifndef MAME_BUS_KC_ROM_H
#define MAME_BUS_KC_ROM_H

#pragma once

>>>>>>> upstream/master
#include "kc.h"

//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

// ======================> kc_8k_device

class kc_8k_device :
		public device_t,
		public device_kcexp_interface
{
public:
	// construction/destruction
<<<<<<< HEAD
	kc_8k_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
	kc_8k_device(const machine_config &mconfig, device_type type, const char *name, const char *tag, device_t *owner, UINT32 clock, const char *shortname, const char *source);

	// optional information overrides

protected:
	// device-level overrides
	virtual void device_start();
	virtual void device_reset();
	virtual const rom_entry *device_rom_region() const;

	// kcexp_interface overrides
	virtual UINT8 module_id_r() { return 0xfb; }
	virtual void control_w(UINT8 data);
	virtual void read(offs_t offset, UINT8 &data);
	virtual UINT8* get_cart_base();
	virtual DECLARE_WRITE_LINE_MEMBER( mei_w );
=======
	kc_8k_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

protected:
	kc_8k_device(const machine_config &mconfig, device_type type, const char *tag, device_t *owner, uint32_t clock);

	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;
	virtual const tiny_rom_entry *device_rom_region() const override;

	// kcexp_interface overrides
	virtual uint8_t module_id_r() override { return 0xfb; }
	virtual void control_w(uint8_t data) override;
	virtual void read(offs_t offset, uint8_t &data) override;
	virtual uint8_t* get_cart_base() override;
	virtual DECLARE_WRITE_LINE_MEMBER( mei_w ) override;
>>>>>>> upstream/master

protected:
	kcexp_slot_device *m_slot;

	// internal state
	int     m_mei;          // module enable line
<<<<<<< HEAD
	UINT8 * m_rom;
	UINT8   m_enabled;
	UINT16  m_base;
=======
	uint8_t * m_rom;
	uint8_t   m_enabled;
	uint16_t  m_base;
>>>>>>> upstream/master
};


// ======================> kc_m006_device

class kc_m006_device :
		public kc_8k_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	kc_m006_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

protected:
	// kcexp_interface overrides
	virtual UINT8 module_id_r() { return 0xfc; }
	virtual void control_w(UINT8 data);
	virtual void read(offs_t offset, UINT8 &data);
=======
	kc_m006_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

protected:
	// kcexp_interface overrides
	virtual uint8_t module_id_r() override { return 0xfc; }
	virtual void control_w(uint8_t data) override;
	virtual void read(offs_t offset, uint8_t &data) override;
>>>>>>> upstream/master
};


// ======================> kc_m033_device

class kc_m033_device :
		public kc_8k_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	kc_m033_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

protected:
	// device-level overrides
	virtual void device_reset();

	// kcexp_interface overrides
	virtual UINT8 module_id_r() { return 0x01; }
	virtual void control_w(UINT8 data);
	virtual void read(offs_t offset, UINT8 &data);

private:
	// internal state
	UINT16  m_bank;
=======
	kc_m033_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

protected:
	// device-level overrides
	virtual void device_reset() override;

	// kcexp_interface overrides
	virtual uint8_t module_id_r() override { return 0x01; }
	virtual void control_w(uint8_t data) override;
	virtual void read(offs_t offset, uint8_t &data) override;

private:
	// internal state
	uint16_t  m_bank;
>>>>>>> upstream/master
};


// device type definition
<<<<<<< HEAD
extern const device_type KC_STANDARD;
extern const device_type KC_M006;
extern const device_type KC_M033;

#endif  /* __KC_ROM_H__ */
=======
DECLARE_DEVICE_TYPE(KC_STANDARD, kc_8k_device)
DECLARE_DEVICE_TYPE(KC_M006,     kc_m006_device)
DECLARE_DEVICE_TYPE(KC_M033,     kc_m033_device)

#endif // MAME_BUS_KC_ROM_H
>>>>>>> upstream/master
