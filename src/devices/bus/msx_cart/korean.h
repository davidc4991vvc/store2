// license:BSD-3-Clause
// copyright-holders:Wilbert Pol
<<<<<<< HEAD
#ifndef __MSX_CART_KOREAN_H
#define __MSX_CART_KOREAN_H
=======
#ifndef MAME_BUS_MSX_CART_KOREAN_H
#define MAME_BUS_MSX_CART_KOREAN_H

#pragma once
>>>>>>> upstream/master

#include "bus/msx_cart/cartridge.h"


<<<<<<< HEAD
extern const device_type MSX_CART_KOREAN_80IN1;
extern const device_type MSX_CART_KOREAN_90IN1;
extern const device_type MSX_CART_KOREAN_126IN1;


class msx_cart_korean_80in1 : public device_t
						, public msx_cart_interface
{
public:
	msx_cart_korean_80in1(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual void device_reset();

	virtual void initialize_cartridge();

	virtual DECLARE_READ8_MEMBER(read_cart);
	virtual DECLARE_WRITE8_MEMBER(write_cart);

	void restore_banks();

private:
	UINT8 m_bank_mask;
	UINT8 m_selected_bank[4];
	UINT8 *m_bank_base[4];

	void setup_bank(UINT8 bank);
};


class msx_cart_korean_90in1 : public device_t
						, public msx_cart_interface
{
public:
	msx_cart_korean_90in1(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual void device_reset();

	virtual void initialize_cartridge();

	virtual DECLARE_READ8_MEMBER(read_cart);

	DECLARE_WRITE8_MEMBER(banking);

	void restore_banks();

private:
	UINT8 m_bank_mask;
	UINT8 m_selected_bank;
	UINT8 *m_bank_base[4];
};


class msx_cart_korean_126in1 : public device_t
						, public msx_cart_interface
{
public:
	msx_cart_korean_126in1(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual void device_reset();

	virtual void initialize_cartridge();

	virtual DECLARE_READ8_MEMBER(read_cart);
	virtual DECLARE_WRITE8_MEMBER(write_cart);

	void restore_banks();

private:
	UINT8 m_bank_mask;
	UINT8 m_selected_bank[2];
	UINT8 *m_bank_base[2];

	void setup_bank(UINT8 bank);
};


#endif
=======
DECLARE_DEVICE_TYPE(MSX_CART_KOREAN_80IN1,  msx_cart_korean_80in1_device)
DECLARE_DEVICE_TYPE(MSX_CART_KOREAN_90IN1,  msx_cart_korean_90in1_device)
DECLARE_DEVICE_TYPE(MSX_CART_KOREAN_126IN1, msx_cart_korean_126in1_device)


class msx_cart_korean_80in1_device : public device_t, public msx_cart_interface
{
public:
	msx_cart_korean_80in1_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual void initialize_cartridge() override;

	virtual DECLARE_READ8_MEMBER(read_cart) override;
	virtual DECLARE_WRITE8_MEMBER(write_cart) override;

protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;

private:
	void restore_banks();
	void setup_bank(uint8_t bank);

	uint8_t m_bank_mask;
	uint8_t m_selected_bank[4];
	uint8_t *m_bank_base[4];
};


class msx_cart_korean_90in1_device : public device_t, public msx_cart_interface
{
public:
	msx_cart_korean_90in1_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual void initialize_cartridge() override;

	virtual DECLARE_READ8_MEMBER(read_cart) override;

	DECLARE_WRITE8_MEMBER(banking);

protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;

private:
	void restore_banks();

	uint8_t m_bank_mask;
	uint8_t m_selected_bank;
	uint8_t *m_bank_base[4];
};


class msx_cart_korean_126in1_device : public device_t, public msx_cart_interface
{
public:
	msx_cart_korean_126in1_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual void initialize_cartridge() override;

	virtual DECLARE_READ8_MEMBER(read_cart) override;
	virtual DECLARE_WRITE8_MEMBER(write_cart) override;

protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;

private:
	void restore_banks();
	void setup_bank(uint8_t bank);

	uint8_t m_bank_mask;
	uint8_t m_selected_bank[2];
	uint8_t *m_bank_base[2];
};


#endif // MAME_BUS_MSX_CART_KOREAN_H
>>>>>>> upstream/master
