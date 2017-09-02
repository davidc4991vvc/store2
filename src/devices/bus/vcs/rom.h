// license:BSD-3-Clause
// copyright-holders:Fabio Priuli
<<<<<<< HEAD
#ifndef __VCS_ROM_H
#define __VCS_ROM_H
=======
#ifndef MAME_BUS_VCS_ROM_H
#define MAME_BUS_VCS_ROM_H

#pragma once
>>>>>>> upstream/master

#include "vcs_slot.h"


// ======================> a26_rom_2k_device

class a26_rom_2k_device : public device_t,
						public device_vcs_cart_interface
{
public:
	// construction/destruction
<<<<<<< HEAD
	a26_rom_2k_device(const machine_config &mconfig, device_type type, const char *name, const char *tag, device_t *owner, UINT32 clock, const char *shortname, const char *source);
	a26_rom_2k_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual void device_reset();

	// reading and writing
	virtual DECLARE_READ8_MEMBER(read_rom);
=======
	a26_rom_2k_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// reading and writing
	virtual DECLARE_READ8_MEMBER(read_rom) override;

protected:
	a26_rom_2k_device(const machine_config &mconfig, device_type type, const char *tag, device_t *owner, uint32_t clock);

	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;
>>>>>>> upstream/master
};


// ======================> a26_rom_4k_device

class a26_rom_4k_device : public a26_rom_2k_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	a26_rom_4k_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
=======
	a26_rom_4k_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
>>>>>>> upstream/master

	// reading and writing

	// accesses just use the 2K ones, since it is just direct access to ROM/RAM
	// masked with its size!
};


// ======================> a26_rom_f6_device

class a26_rom_f6_device : public a26_rom_2k_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	a26_rom_f6_device(const machine_config &mconfig, device_type type, const char *name, const char *tag, device_t *owner, UINT32 clock, const char *shortname, const char *source);
	a26_rom_f6_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual void device_reset();

	// reading and writing
	virtual DECLARE_READ8_MEMBER(read_rom);
	virtual DECLARE_WRITE8_MEMBER(write_bank);
	virtual DECLARE_DIRECT_UPDATE_MEMBER(cart_opbase);

protected:
=======
	a26_rom_f6_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// reading and writing
	virtual DECLARE_READ8_MEMBER(read_rom) override;
	virtual DECLARE_WRITE8_MEMBER(write_bank) override;

protected:
	a26_rom_f6_device(const machine_config &mconfig, device_type type, const char *tag, device_t *owner, uint32_t clock);

	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;

>>>>>>> upstream/master
	int m_base_bank;
};


// ======================> a26_rom_f4_device

class a26_rom_f4_device : public a26_rom_f6_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	a26_rom_f4_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_reset();

	// reading and writing
	virtual DECLARE_READ8_MEMBER(read_rom);
	virtual DECLARE_WRITE8_MEMBER(write_bank);
=======
	a26_rom_f4_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// reading and writing
	virtual DECLARE_READ8_MEMBER(read_rom) override;
	virtual DECLARE_WRITE8_MEMBER(write_bank) override;

protected:
	// device-level overrides
	virtual void device_reset() override;
>>>>>>> upstream/master
};


// ======================> a26_rom_f8_device

class a26_rom_f8_device : public a26_rom_f6_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	a26_rom_f8_device(const machine_config &mconfig, device_type type, const char *name, const char *tag, device_t *owner, UINT32 clock, const char *shortname, const char *source);
	a26_rom_f8_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// reading and writing
	virtual DECLARE_READ8_MEMBER(read_rom);
	virtual DECLARE_WRITE8_MEMBER(write_bank);
=======
	a26_rom_f8_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// reading and writing
	virtual DECLARE_READ8_MEMBER(read_rom) override;
	virtual DECLARE_WRITE8_MEMBER(write_bank) override;

protected:
	a26_rom_f8_device(const machine_config &mconfig, device_type type, const char *tag, device_t *owner, uint32_t clock);
>>>>>>> upstream/master
};


// ======================> a26_rom_f8_sw_device

class a26_rom_f8_sw_device : public a26_rom_f8_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	a26_rom_f8_sw_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_reset();
=======
	a26_rom_f8_sw_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

protected:
	// device-level overrides
	virtual void device_reset() override;
>>>>>>> upstream/master
};


// ======================> a26_rom_fa_device

class a26_rom_fa_device : public a26_rom_f6_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	a26_rom_fa_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// reading and writing
	virtual DECLARE_READ8_MEMBER(read_rom);
	virtual DECLARE_WRITE8_MEMBER(write_bank);
=======
	a26_rom_fa_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// reading and writing
	virtual DECLARE_READ8_MEMBER(read_rom) override;
	virtual DECLARE_WRITE8_MEMBER(write_bank) override;
>>>>>>> upstream/master
};


// ======================> a26_rom_fe_device

class a26_rom_fe_device : public a26_rom_2k_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	a26_rom_fe_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual void device_reset();

	// reading and writing
	virtual DECLARE_READ8_MEMBER(read_rom);
	virtual DECLARE_READ8_MEMBER(read_bank);
	virtual DECLARE_WRITE8_MEMBER(write_ram);
	virtual DECLARE_WRITE8_MEMBER(write_bank);

protected:
=======
	a26_rom_fe_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// reading and writing
	virtual DECLARE_READ8_MEMBER(read_rom) override;
	virtual DECLARE_READ8_MEMBER(read_bank) override;
	virtual DECLARE_WRITE8_MEMBER(write_ram) override;
	virtual DECLARE_WRITE8_MEMBER(write_bank) override;

protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;

>>>>>>> upstream/master
	int m_base_bank;
	int m_trigger_on_next_access;
};


// ======================> a26_rom_3e_device

class a26_rom_3e_device : public a26_rom_f6_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	a26_rom_3e_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual void device_reset();

	// reading and writing
	virtual DECLARE_READ8_MEMBER(read_rom);
	virtual DECLARE_WRITE8_MEMBER(write_bank);
	virtual DECLARE_WRITE8_MEMBER(write_ram);

protected:
=======
	a26_rom_3e_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// reading and writing
	virtual DECLARE_READ8_MEMBER(read_rom) override;
	virtual DECLARE_WRITE8_MEMBER(write_bank) override;
	virtual DECLARE_WRITE8_MEMBER(write_ram) override;

protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;

>>>>>>> upstream/master
	int m_num_bank;
	int m_ram_bank;
	int m_ram_enable;
};


// ======================> a26_rom_3f_device

class a26_rom_3f_device : public a26_rom_f6_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	a26_rom_3f_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_reset();

	// reading and writing
	virtual DECLARE_READ8_MEMBER(read_rom);
	virtual DECLARE_WRITE8_MEMBER(write_bank);

protected:
=======
	a26_rom_3f_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// reading and writing
	virtual DECLARE_READ8_MEMBER(read_rom) override;
	virtual DECLARE_WRITE8_MEMBER(write_bank) override;

protected:
	// device-level overrides
	virtual void device_reset() override;

>>>>>>> upstream/master
	int m_num_bank;
};


// ======================> a26_rom_e0_device

class a26_rom_e0_device : public a26_rom_f6_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	a26_rom_e0_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual void device_reset();

	// reading and writing
	virtual DECLARE_READ8_MEMBER(read_rom);
	virtual DECLARE_WRITE8_MEMBER(write_bank);

protected:
=======
	a26_rom_e0_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// reading and writing
	virtual DECLARE_READ8_MEMBER(read_rom) override;
	virtual DECLARE_WRITE8_MEMBER(write_bank) override;

protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;

>>>>>>> upstream/master
	int m_base_banks[4];
};


// ======================> a26_rom_e7_device

class a26_rom_e7_device : public a26_rom_f6_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	a26_rom_e7_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual void device_reset();

	// reading and writing
	virtual DECLARE_READ8_MEMBER(read_rom);
	virtual DECLARE_WRITE8_MEMBER(write_bank);

protected:
=======
	a26_rom_e7_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// reading and writing
	virtual DECLARE_READ8_MEMBER(read_rom) override;
	virtual DECLARE_WRITE8_MEMBER(write_bank) override;

protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;

>>>>>>> upstream/master
	int m_ram_bank;
};


// ======================> a26_rom_ua_device

class a26_rom_ua_device : public a26_rom_f6_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	a26_rom_ua_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_reset();

	// reading and writing
	virtual DECLARE_READ8_MEMBER(read_rom);
	virtual DECLARE_READ8_MEMBER(read_bank);
	virtual DECLARE_WRITE8_MEMBER(write_bank);
=======
	a26_rom_ua_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// reading and writing
	virtual DECLARE_READ8_MEMBER(read_rom) override;
	virtual DECLARE_READ8_MEMBER(read_bank) override;
	virtual DECLARE_WRITE8_MEMBER(write_bank) override;

protected:
	// device-level overrides
	virtual void device_reset() override;
>>>>>>> upstream/master
};


// ======================> a26_rom_cv_device

class a26_rom_cv_device : public a26_rom_2k_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	a26_rom_cv_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// reading and writing
	virtual DECLARE_READ8_MEMBER(read_rom);
	virtual DECLARE_WRITE8_MEMBER(write_bank);
=======
	a26_rom_cv_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// reading and writing
	virtual DECLARE_READ8_MEMBER(read_rom) override;
	virtual DECLARE_WRITE8_MEMBER(write_bank) override;
>>>>>>> upstream/master
};


// ======================> a26_rom_dc_device

class a26_rom_dc_device : public a26_rom_f6_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	a26_rom_dc_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// reading and writing
	virtual DECLARE_READ8_MEMBER(read_rom);
	virtual DECLARE_WRITE8_MEMBER(write_bank);
=======
	a26_rom_dc_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// reading and writing
	virtual DECLARE_READ8_MEMBER(read_rom) override;
	virtual DECLARE_WRITE8_MEMBER(write_bank) override;
>>>>>>> upstream/master
};


// ======================> a26_rom_fv_device

class a26_rom_fv_device : public a26_rom_f6_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	a26_rom_fv_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual void device_reset();

	// reading and writing
	virtual DECLARE_READ8_MEMBER(read_rom);
	virtual DECLARE_WRITE8_MEMBER(write_bank);

protected:
=======
	a26_rom_fv_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// reading and writing
	virtual DECLARE_READ8_MEMBER(read_rom) override;
	virtual DECLARE_WRITE8_MEMBER(write_bank) override;

protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;

>>>>>>> upstream/master
	int m_locked;
};


// ======================> a26_rom_jvp_device

class a26_rom_jvp_device : public a26_rom_f6_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	a26_rom_jvp_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// reading and writing
	virtual DECLARE_READ8_MEMBER(read_rom);
	virtual DECLARE_WRITE8_MEMBER(write_bank);
=======
	a26_rom_jvp_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// reading and writing
	virtual DECLARE_READ8_MEMBER(read_rom) override;
	virtual DECLARE_WRITE8_MEMBER(write_bank) override;
>>>>>>> upstream/master
};


// ======================> a26_rom_4in1_device

class a26_rom_4in1_device : public a26_rom_f6_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	a26_rom_4in1_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_reset();

	// reading and writing
	virtual DECLARE_READ8_MEMBER(read_rom);
=======
	a26_rom_4in1_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// reading and writing
	virtual DECLARE_READ8_MEMBER(read_rom) override;

protected:
	// device-level overrides
	virtual void device_reset() override;
>>>>>>> upstream/master
};


// ======================> a26_rom_8in1_device

class a26_rom_8in1_device : public a26_rom_f8_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	a26_rom_8in1_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual void device_reset();

	// reading and writing
	virtual DECLARE_READ8_MEMBER(read_rom);

protected:
=======
	a26_rom_8in1_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// reading and writing
	virtual DECLARE_READ8_MEMBER(read_rom) override;

protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;

>>>>>>> upstream/master
	int m_reset_bank;
};


// ======================> a26_rom_32in1_device

class a26_rom_32in1_device : public a26_rom_f6_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	a26_rom_32in1_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_reset();

	// reading and writing
	virtual DECLARE_READ8_MEMBER(read_rom);
=======
	a26_rom_32in1_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// reading and writing
	virtual DECLARE_READ8_MEMBER(read_rom) override;

protected:
	// device-level overrides
	virtual void device_reset() override;
>>>>>>> upstream/master
};


// ======================> a26_rom_x07_device

class a26_rom_x07_device : public a26_rom_f6_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	a26_rom_x07_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// reading and writing
	virtual DECLARE_READ8_MEMBER(read_rom);
	virtual DECLARE_WRITE8_MEMBER(write_bank);
=======
	a26_rom_x07_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// reading and writing
	virtual DECLARE_READ8_MEMBER(read_rom) override;
	virtual DECLARE_WRITE8_MEMBER(write_bank) override;
>>>>>>> upstream/master
};



// device type definition
<<<<<<< HEAD
extern const device_type A26_ROM_2K;
extern const device_type A26_ROM_4K;
extern const device_type A26_ROM_F4;
extern const device_type A26_ROM_F6;
extern const device_type A26_ROM_F8;
extern const device_type A26_ROM_F8_SW;
extern const device_type A26_ROM_FA;
extern const device_type A26_ROM_FE;
extern const device_type A26_ROM_3E;
extern const device_type A26_ROM_3F;
extern const device_type A26_ROM_E0;
extern const device_type A26_ROM_E7;
extern const device_type A26_ROM_UA;
extern const device_type A26_ROM_CV;
extern const device_type A26_ROM_DC;
extern const device_type A26_ROM_FV;
extern const device_type A26_ROM_JVP;
extern const device_type A26_ROM_4IN1;
extern const device_type A26_ROM_8IN1;
extern const device_type A26_ROM_32IN1;
extern const device_type A26_ROM_X07;


#endif
=======
DECLARE_DEVICE_TYPE(A26_ROM_2K,    a26_rom_2k_device)
DECLARE_DEVICE_TYPE(A26_ROM_4K,    a26_rom_4k_device)
DECLARE_DEVICE_TYPE(A26_ROM_F4,    a26_rom_f4_device)
DECLARE_DEVICE_TYPE(A26_ROM_F6,    a26_rom_f6_device)
DECLARE_DEVICE_TYPE(A26_ROM_F8,    a26_rom_f8_device)
DECLARE_DEVICE_TYPE(A26_ROM_F8_SW, a26_rom_f8_sw_device)
DECLARE_DEVICE_TYPE(A26_ROM_FA,    a26_rom_fa_device)
DECLARE_DEVICE_TYPE(A26_ROM_FE,    a26_rom_fe_device)
DECLARE_DEVICE_TYPE(A26_ROM_3E,    a26_rom_3e_device)
DECLARE_DEVICE_TYPE(A26_ROM_3F,    a26_rom_3f_device)
DECLARE_DEVICE_TYPE(A26_ROM_E0,    a26_rom_e0_device)
DECLARE_DEVICE_TYPE(A26_ROM_E7,    a26_rom_e7_device)
DECLARE_DEVICE_TYPE(A26_ROM_UA,    a26_rom_ua_device)
DECLARE_DEVICE_TYPE(A26_ROM_CV,    a26_rom_cv_device)
DECLARE_DEVICE_TYPE(A26_ROM_DC,    a26_rom_dc_device)
DECLARE_DEVICE_TYPE(A26_ROM_FV,    a26_rom_fv_device)
DECLARE_DEVICE_TYPE(A26_ROM_JVP,   a26_rom_jvp_device)
DECLARE_DEVICE_TYPE(A26_ROM_4IN1,  a26_rom_4in1_device)
DECLARE_DEVICE_TYPE(A26_ROM_8IN1,  a26_rom_8in1_device)
DECLARE_DEVICE_TYPE(A26_ROM_32IN1, a26_rom_32in1_device)
DECLARE_DEVICE_TYPE(A26_ROM_X07,   a26_rom_x07_device)


#endif // MAME_BUS_VCS_ROM_H
>>>>>>> upstream/master
