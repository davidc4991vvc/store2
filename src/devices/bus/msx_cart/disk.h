// license:BSD-3-Clause
// copyright-holders:Wilbert Pol
<<<<<<< HEAD
#ifndef __MSX_CART_DISK_H
#define __MSX_CART_DISK_H
=======
#ifndef MAME_BUS_MSX_CART_DISK_H
#define MAME_BUS_MSX_CART_DISK_H

#pragma once
>>>>>>> upstream/master

#include "bus/msx_cart/cartridge.h"
#include "machine/wd_fdc.h"
#include "machine/upd765.h"
#include "imagedev/flopdrv.h"
#include "imagedev/floppy.h"


<<<<<<< HEAD
extern const device_type MSX_CART_VY0010;
extern const device_type MSX_CART_FSFD1;
extern const device_type MSX_CART_FSFD1A;
extern const device_type MSX_CART_FSCF351;


class msx_cart_disk : public device_t
						, public msx_cart_interface
{
public:
	msx_cart_disk(const machine_config &mconfig, device_type type, const char *name, const char *tag, device_t *owner, UINT32 clock, const char *shortname);

	virtual void initialize_cartridge();

	DECLARE_FLOPPY_FORMATS(floppy_formats);

protected:
	required_device<floppy_connector> m_floppy0;
	optional_device<floppy_connector> m_floppy1;
	floppy_image_device *m_floppy;
};


class msx_cart_disk_wd : public msx_cart_disk
{
public:
	msx_cart_disk_wd(const machine_config &mconfig, device_type type, const char *name, const char *tag, device_t *owner, UINT32 clock, const char *shortname);

protected:
	required_device<wd_fdc_analog_t> m_fdc;
};


class msx_cart_disk_type1 : public msx_cart_disk_wd
{
public:
	msx_cart_disk_type1(const machine_config &mconfig, device_type type, const char *name, const char *tag, device_t *owner, UINT32 clock, const char *shortname);

	// device-level overrides
	virtual void device_start();
	virtual void device_reset();

	virtual DECLARE_READ8_MEMBER(read_cart);
	virtual DECLARE_WRITE8_MEMBER(write_cart);

	void post_load();

protected:
	UINT8 m_side_control;
	UINT8 m_control;

	void set_side_control(UINT8 data);
	void set_control(UINT8 data);
};


class msx_cart_disk_type2 : public msx_cart_disk_wd
{
public:
	msx_cart_disk_type2(const machine_config &mconfig, device_type type, const char *name, const char *tag, device_t *owner, UINT32 clock, const char *shortname);

	// device-level overrides
	virtual void device_start();
	virtual void device_reset();

	virtual DECLARE_READ8_MEMBER(read_cart);
	virtual DECLARE_WRITE8_MEMBER(write_cart);

	void post_load();

protected:
	UINT8 m_control;

	void set_control(UINT8 data);
};


class msx_cart_vy0010 : public msx_cart_disk_type1
{
public:
	msx_cart_vy0010(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	virtual machine_config_constructor device_mconfig_additions() const;
};


class msx_cart_fsfd1 : public msx_cart_disk_type1
{
public:
	msx_cart_fsfd1(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	virtual machine_config_constructor device_mconfig_additions() const;
};


class msx_cart_fscf351 : public msx_cart_disk_type2
{
public:
	msx_cart_fscf351(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	virtual machine_config_constructor device_mconfig_additions() const;
};


class msx_cart_disk_tc8566 : public msx_cart_disk
{
public:
	msx_cart_disk_tc8566(const machine_config &mconfig, device_type type, const char *name, const char *tag, device_t *owner, UINT32 clock, const char *shortname);

protected:
=======
DECLARE_DEVICE_TYPE(MSX_CART_VY0010,  msx_cart_vy0010_device)
DECLARE_DEVICE_TYPE(MSX_CART_FSFD1,   msx_cart_fsfd1_device)
DECLARE_DEVICE_TYPE(MSX_CART_FSFD1A,  msx_cart_fsfd1a_device)
DECLARE_DEVICE_TYPE(MSX_CART_FSCF351, msx_cart_fscf351_device)


class msx_cart_disk_device : public device_t, public msx_cart_interface
{
public:
	virtual void initialize_cartridge() override;

protected:
	msx_cart_disk_device(const machine_config &mconfig, device_type type, const char *tag, device_t *owner, uint32_t clock);

	required_device<floppy_connector> m_floppy0;
	optional_device<floppy_connector> m_floppy1;
	floppy_image_device *m_floppy;

	DECLARE_FLOPPY_FORMATS(floppy_formats);
};


class msx_cart_disk_wd_device : public msx_cart_disk_device
{
protected:
	msx_cart_disk_wd_device(const machine_config &mconfig, device_type type, const char *tag, device_t *owner, uint32_t clock);

	required_device<wd_fdc_analog_device_base> m_fdc;
};


class msx_cart_disk_type1_device : public msx_cart_disk_wd_device
{
public:
	virtual DECLARE_READ8_MEMBER(read_cart) override;
	virtual DECLARE_WRITE8_MEMBER(write_cart) override;

protected:
	msx_cart_disk_type1_device(const machine_config &mconfig, device_type type, const char *tag, device_t *owner, uint32_t clock);

	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;

	void post_load();

	uint8_t m_side_control;
	uint8_t m_control;

	void set_side_control(uint8_t data);
	void set_control(uint8_t data);
};


class msx_cart_disk_type2_device : public msx_cart_disk_wd_device
{
public:
	virtual DECLARE_READ8_MEMBER(read_cart) override;
	virtual DECLARE_WRITE8_MEMBER(write_cart) override;

protected:
	msx_cart_disk_type2_device(const machine_config &mconfig, device_type type, const char *tag, device_t *owner, uint32_t clock);

	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;

	void post_load();

	uint8_t m_control;

	void set_control(uint8_t data);
};


class msx_cart_vy0010_device : public msx_cart_disk_type1_device
{
public:
	msx_cart_vy0010_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

protected:
	virtual void device_add_mconfig(machine_config &config) override;
};


class msx_cart_fsfd1_device : public msx_cart_disk_type1_device
{
public:
	msx_cart_fsfd1_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

protected:
	virtual void device_add_mconfig(machine_config &config) override;
};


class msx_cart_fscf351_device : public msx_cart_disk_type2_device
{
public:
	msx_cart_fscf351_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

protected:
	virtual void device_add_mconfig(machine_config &config) override;
};


class msx_cart_disk_tc8566_device : public msx_cart_disk_device
{
protected:
	msx_cart_disk_tc8566_device(const machine_config &mconfig, device_type type, const char *tag, device_t *owner, uint32_t clock);

>>>>>>> upstream/master
	required_device<tc8566af_device> m_fdc;
};


<<<<<<< HEAD
class msx_cart_fsfd1a : public msx_cart_disk_tc8566
{
public:
	msx_cart_fsfd1a(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual void device_reset();
	virtual machine_config_constructor device_mconfig_additions() const;

	virtual DECLARE_READ8_MEMBER(read_cart);
	virtual DECLARE_WRITE8_MEMBER(write_cart);

private:

};


#endif
=======
class msx_cart_fsfd1a_device : public msx_cart_disk_tc8566_device
{
public:
	msx_cart_fsfd1a_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

protected:
	virtual void device_start() override;
	virtual void device_reset() override;

	// device-level overrides
	virtual void device_add_mconfig(machine_config &config) override;

	virtual DECLARE_READ8_MEMBER(read_cart) override;
	virtual DECLARE_WRITE8_MEMBER(write_cart) override;
};


#endif // MAME_BUS_MSX_CART_DISK_H
>>>>>>> upstream/master
