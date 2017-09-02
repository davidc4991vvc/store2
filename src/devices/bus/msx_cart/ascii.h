// license:BSD-3-Clause
// copyright-holders:Wilbert Pol
<<<<<<< HEAD
#ifndef __MSX_CART_ASCII_H
#define __MSX_CART_ASCII_H
=======
#ifndef MAME_BUS_MSX_CART_ASCII_H
#define MAME_BUS_MSX_CART_ASCII_H

#pragma once
>>>>>>> upstream/master

#include "bus/msx_cart/cartridge.h"


<<<<<<< HEAD
extern const device_type MSX_CART_ASCII8;
extern const device_type MSX_CART_ASCII16;
extern const device_type MSX_CART_ASCII8_SRAM;
extern const device_type MSX_CART_ASCII16_SRAM;
extern const device_type MSX_CART_MSXWRITE;


class msx_cart_ascii8 : public device_t
						, public msx_cart_interface
{
public:
	msx_cart_ascii8(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual void device_reset();

	virtual void initialize_cartridge();

	virtual DECLARE_READ8_MEMBER(read_cart);
	virtual DECLARE_WRITE8_MEMBER(write_cart);
=======
DECLARE_DEVICE_TYPE(MSX_CART_ASCII8,       msx_cart_ascii8_device)
DECLARE_DEVICE_TYPE(MSX_CART_ASCII16,      msx_cart_ascii16_device)
DECLARE_DEVICE_TYPE(MSX_CART_ASCII8_SRAM,  msx_cart_ascii8_sram_device)
DECLARE_DEVICE_TYPE(MSX_CART_ASCII16_SRAM, msx_cart_ascii16_sram_device)
DECLARE_DEVICE_TYPE(MSX_CART_MSXWRITE,     msx_cart_msxwrite_device)


class msx_cart_ascii8_device : public device_t, public msx_cart_interface
{
public:
	msx_cart_ascii8_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual void initialize_cartridge() override;

	virtual DECLARE_READ8_MEMBER(read_cart) override;
	virtual DECLARE_WRITE8_MEMBER(write_cart) override;

protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;
>>>>>>> upstream/master

	void restore_banks();

private:
<<<<<<< HEAD
	UINT8 m_bank_mask;
	UINT8 m_selected_bank[4];
	UINT8 *m_bank_base[4];
};


class msx_cart_ascii16 : public device_t
						, public msx_cart_interface
{
public:
	msx_cart_ascii16(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual void device_reset();

	virtual void initialize_cartridge();

	virtual DECLARE_READ8_MEMBER(read_cart);
	virtual DECLARE_WRITE8_MEMBER(write_cart);
=======
	uint8_t m_bank_mask;
	uint8_t m_selected_bank[4];
	uint8_t *m_bank_base[4];
};


class msx_cart_ascii16_device : public device_t, public msx_cart_interface
{
public:
	msx_cart_ascii16_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual void initialize_cartridge() override;

	virtual DECLARE_READ8_MEMBER(read_cart) override;
	virtual DECLARE_WRITE8_MEMBER(write_cart) override;

protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;
>>>>>>> upstream/master

	void restore_banks();

private:
<<<<<<< HEAD
	UINT8 m_bank_mask;
	UINT8 m_selected_bank[2];
	UINT8 *m_bank_base[2];
};


class msx_cart_ascii8_sram : public device_t
						, public msx_cart_interface
{
public:
	msx_cart_ascii8_sram(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual void device_reset();

	virtual void initialize_cartridge();

	virtual DECLARE_READ8_MEMBER(read_cart);
	virtual DECLARE_WRITE8_MEMBER(write_cart);
=======
	uint8_t m_bank_mask;
	uint8_t m_selected_bank[2];
	uint8_t *m_bank_base[2];
};


class msx_cart_ascii8_sram_device : public device_t, public msx_cart_interface
{
public:
	msx_cart_ascii8_sram_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual void initialize_cartridge() override;

	virtual DECLARE_READ8_MEMBER(read_cart) override;
	virtual DECLARE_WRITE8_MEMBER(write_cart) override;

protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;
>>>>>>> upstream/master

	void restore_banks();

private:
<<<<<<< HEAD
	UINT8 m_bank_mask;
	UINT8 m_selected_bank[4];
	UINT8 *m_bank_base[4];
	UINT8 m_sram_select_mask;

	void setup_bank(UINT8 bank);
};


class msx_cart_ascii16_sram : public device_t
						, public msx_cart_interface
{
public:
	msx_cart_ascii16_sram(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual void device_reset();

	virtual void initialize_cartridge();

	virtual DECLARE_READ8_MEMBER(read_cart);
	virtual DECLARE_WRITE8_MEMBER(write_cart);
=======
	uint8_t m_bank_mask;
	uint8_t m_selected_bank[4];
	uint8_t *m_bank_base[4];
	uint8_t m_sram_select_mask;

	void setup_bank(uint8_t bank);
};


class msx_cart_ascii16_sram_device : public device_t, public msx_cart_interface
{
public:
	msx_cart_ascii16_sram_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual void initialize_cartridge() override;

	virtual DECLARE_READ8_MEMBER(read_cart) override;
	virtual DECLARE_WRITE8_MEMBER(write_cart) override;

protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;
>>>>>>> upstream/master

	void restore_banks();

private:
<<<<<<< HEAD
	UINT8 m_bank_mask;
	UINT8 m_selected_bank[2];
	UINT8 *m_bank_base[2];
	UINT8 m_sram_select_mask;

	void setup_bank(UINT8 bank);
};


class msx_cart_msxwrite : public device_t
						, public msx_cart_interface
{
public:
	msx_cart_msxwrite(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual void device_reset();

	virtual void initialize_cartridge();

	virtual DECLARE_READ8_MEMBER(read_cart);
	virtual DECLARE_WRITE8_MEMBER(write_cart);
=======
	uint8_t m_bank_mask;
	uint8_t m_selected_bank[2];
	uint8_t *m_bank_base[2];
	uint8_t m_sram_select_mask;

	void setup_bank(uint8_t bank);
};


class msx_cart_msxwrite_device : public device_t, public msx_cart_interface
{
public:
	msx_cart_msxwrite_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual void initialize_cartridge() override;

	virtual DECLARE_READ8_MEMBER(read_cart) override;
	virtual DECLARE_WRITE8_MEMBER(write_cart) override;

protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;
>>>>>>> upstream/master

	void restore_banks();

private:
<<<<<<< HEAD
	UINT8 m_bank_mask;
	UINT8 m_selected_bank[2];
	UINT8 *m_bank_base[2];
};

#endif
=======
	uint8_t m_bank_mask;
	uint8_t m_selected_bank[2];
	uint8_t *m_bank_base[2];
};

#endif // MAME_BUS_MSX_CART_ASCII_H
>>>>>>> upstream/master
