// license:BSD-3-Clause
// copyright-holders:smf
/*  CAT702 security chip */

<<<<<<< HEAD
#pragma once

#ifndef __CAT702_H__
#define __CAT702_H__

#include "emu.h"

extern const device_type CAT702;
=======
#ifndef MAME_MACHINE_CAT702_H
#define MAME_MACHINE_CAT702_H

#pragma once


DECLARE_DEVICE_TYPE(CAT702, cat702_device)
>>>>>>> upstream/master

#define MCFG_CAT702_DATAOUT_HANDLER(_devcb) \
	devcb = &cat702_device::set_dataout_handler(*device, DEVCB_##_devcb);

class cat702_device : public device_t
{
public:
<<<<<<< HEAD
	cat702_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// static configuration helpers
	template<class _Object> static devcb_base &set_dataout_handler(device_t &device, _Object object) { return downcast<cat702_device &>(device).m_dataout_handler.set_callback(object); }

	void init(const UINT8 *transform); // TODO: region
=======
	cat702_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// static configuration helpers
	template <class Object> static devcb_base &set_dataout_handler(device_t &device, Object &&cb) { return downcast<cat702_device &>(device).m_dataout_handler.set_callback(std::forward<Object>(cb)); }
>>>>>>> upstream/master

	DECLARE_WRITE_LINE_MEMBER(write_select);
	DECLARE_WRITE_LINE_MEMBER(write_datain);
	DECLARE_WRITE_LINE_MEMBER(write_clock);

protected:
<<<<<<< HEAD
	virtual void device_start();

private:
	UINT8 compute_sbox_coef(int sel, int bit);
	void apply_bit_sbox(int sel);
	void apply_sbox(const UINT8 *sbox);

	const UINT8 *m_transform;
	int m_select;
	int m_clock;
	int m_datain;
	UINT8 m_state;
	UINT8 m_bit;
=======
	virtual void device_start() override;

private:
	uint8_t compute_sbox_coef(int sel, int bit);
	void apply_bit_sbox(int sel);
	void apply_sbox(const uint8_t *sbox);

	optional_memory_region m_region;
	uint8_t m_transform[8];

	int m_select;
	int m_clock;
	int m_datain;
	uint8_t m_state;
	uint8_t m_bit;
>>>>>>> upstream/master

	devcb_write_line m_dataout_handler;
};

<<<<<<< HEAD
#endif
=======
#endif // MAME_MACHINE_CAT702_H
>>>>>>> upstream/master
