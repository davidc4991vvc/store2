// license:BSD-3-Clause
// copyright-holders:R. Belmont
/*********************************************************************

    a2videoterm.h

    Implementation of the Apple II Memory Expansion Card

*********************************************************************/

<<<<<<< HEAD
#ifndef __A2BUS_VIDEOTERM__
#define __A2BUS_VIDEOTERM__

#include "emu.h"
=======
#ifndef MAME_BUS_A2BUS_A2VIDEOTERM_H
#define MAME_BUS_A2BUS_A2VIDEOTERM_H

#pragma once

>>>>>>> upstream/master
#include "a2bus.h"
#include "video/mc6845.h"

//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

class a2bus_videx80_device:
	public device_t,
	public device_a2bus_card_interface
{
<<<<<<< HEAD
public:
	// construction/destruction
	a2bus_videx80_device(const machine_config &mconfig, device_type type, const char *name, const char *tag, device_t *owner, UINT32 clock, const char *shortname, const char *source);

	// optional information overrides
	virtual machine_config_constructor device_mconfig_additions() const;

	DECLARE_WRITE_LINE_MEMBER(vsync_changed);
	MC6845_UPDATE_ROW(crtc_update_row);

	UINT8 *m_rom, *m_chrrom;
	UINT8 m_ram[512*4];
	int m_framecnt;

protected:
	virtual void device_start();
	virtual void device_reset();

	// overrides of standard a2bus slot functions
	virtual UINT8 read_c0nx(address_space &space, UINT8 offset);
	virtual void write_c0nx(address_space &space, UINT8 offset, UINT8 data);
	virtual UINT8 read_cnxx(address_space &space, UINT8 offset);
	virtual void write_cnxx(address_space &space, UINT8 offset, UINT8 data);
	virtual UINT8 read_c800(address_space &space, UINT16 offset);
	virtual void write_c800(address_space &space, UINT16 offset, UINT8 data);

	required_device<mc6845_device> m_crtc;

private:
	int m_rambank;
public:
	required_device<palette_device> m_palette;
=======
protected:
	// construction/destruction
	a2bus_videx80_device(const machine_config &mconfig, device_type type, const char *tag, device_t *owner, uint32_t clock);

	virtual void device_start() override;
	virtual void device_reset() override;
	virtual void device_add_mconfig(machine_config &config) override;

	// overrides of standard a2bus slot functions
	virtual uint8_t read_c0nx(address_space &space, uint8_t offset) override;
	virtual void write_c0nx(address_space &space, uint8_t offset, uint8_t data) override;
	virtual uint8_t read_cnxx(address_space &space, uint8_t offset) override;
	virtual void write_cnxx(address_space &space, uint8_t offset, uint8_t data) override;
	virtual uint8_t read_c800(address_space &space, uint16_t offset) override;
	virtual void write_c800(address_space &space, uint16_t offset, uint8_t data) override;

	uint8_t *m_rom, *m_chrrom;
	uint8_t m_ram[512*4];
	int m_framecnt;

	required_device<mc6845_device> m_crtc;
	required_device<palette_device> m_palette;

private:
	DECLARE_WRITE_LINE_MEMBER(vsync_changed);
	MC6845_UPDATE_ROW(crtc_update_row);

	int m_rambank;
>>>>>>> upstream/master
};

class a2bus_videoterm_device : public a2bus_videx80_device
{
public:
<<<<<<< HEAD
	a2bus_videoterm_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	virtual const rom_entry *device_rom_region() const;
=======
	a2bus_videoterm_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual const tiny_rom_entry *device_rom_region() const override;
>>>>>>> upstream/master
};

class a2bus_ap16_device : public a2bus_videx80_device
{
public:
<<<<<<< HEAD
	a2bus_ap16_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	virtual const rom_entry *device_rom_region() const;

	virtual UINT8 read_cnxx(address_space &space, UINT8 offset);
=======
	a2bus_ap16_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual const tiny_rom_entry *device_rom_region() const override;

protected:
	virtual uint8_t read_cnxx(address_space &space, uint8_t offset) override;
>>>>>>> upstream/master
};


class a2bus_ap16alt_device : public a2bus_videx80_device
{
public:
<<<<<<< HEAD
	a2bus_ap16alt_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	virtual const rom_entry *device_rom_region() const;

	virtual UINT8 read_cnxx(address_space &space, UINT8 offset);
=======
	a2bus_ap16alt_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual const tiny_rom_entry *device_rom_region() const override;

protected:
	virtual uint8_t read_cnxx(address_space &space, uint8_t offset) override;
>>>>>>> upstream/master
};

class a2bus_vtc1_device : public a2bus_videx80_device
{
public:
<<<<<<< HEAD
	a2bus_vtc1_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	virtual const rom_entry *device_rom_region() const;
=======
	a2bus_vtc1_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual const tiny_rom_entry *device_rom_region() const override;
>>>>>>> upstream/master
};

class a2bus_vtc2_device : public a2bus_videx80_device
{
public:
<<<<<<< HEAD
	a2bus_vtc2_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	virtual const rom_entry *device_rom_region() const;
=======
	a2bus_vtc2_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual const tiny_rom_entry *device_rom_region() const override;
>>>>>>> upstream/master
};

class a2bus_aevm80_device : public a2bus_videx80_device
{
public:
<<<<<<< HEAD
	a2bus_aevm80_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	virtual const rom_entry *device_rom_region() const;
};

// device type definition
extern const device_type A2BUS_VIDEOTERM;
extern const device_type A2BUS_IBSAP16;
extern const device_type A2BUS_IBSAP16ALT;
extern const device_type A2BUS_VTC1;
extern const device_type A2BUS_VTC2;
extern const device_type A2BUS_AEVIEWMASTER80;

#endif /* __A2BUS_VIDEOTERM__ */
=======
	a2bus_aevm80_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual const tiny_rom_entry *device_rom_region() const override;
};

// device type definition
DECLARE_DEVICE_TYPE(A2BUS_VIDEOTERM,      a2bus_videoterm_device)
DECLARE_DEVICE_TYPE(A2BUS_IBSAP16,        a2bus_ap16_device)
DECLARE_DEVICE_TYPE(A2BUS_IBSAP16ALT,     a2bus_ap16alt_device)
DECLARE_DEVICE_TYPE(A2BUS_VTC1,           a2bus_vtc1_device)
DECLARE_DEVICE_TYPE(A2BUS_VTC2,           a2bus_vtc2_device)
DECLARE_DEVICE_TYPE(A2BUS_AEVIEWMASTER80, a2bus_aevm80_device)

#endif // MAME_BUS_A2BUS_A2VIDEOTERM_H
>>>>>>> upstream/master
