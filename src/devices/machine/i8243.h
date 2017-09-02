// license:BSD-3-Clause
// copyright-holders:Aaron Giles
/***************************************************************************

    i8243.h

    Intel 8243 Port Expander

***************************************************************************/

<<<<<<< HEAD
#pragma once

#ifndef __I8243_H__
#define __I8243_H__

#include "emu.h"
#include "cpu/mcs48/mcs48.h"
=======
#ifndef MAME_MACHINE_I8243_H
#define MAME_MACHINE_I8243_H

#pragma once
>>>>>>> upstream/master



/***************************************************************************
    DEVICE CONFIGURATION MACROS
***************************************************************************/

#define MCFG_I8243_ADD(_tag, _read, _write) \
	MCFG_DEVICE_ADD(_tag, I8243, 0) \
	MCFG_I8243_READHANDLER(_read) \
	MCFG_I8243_WRITEHANDLER(_write)
#define MCFG_I8243_READHANDLER(_devcb) \
	devcb = &i8243_device::set_read_handler(*device, DEVCB_##_devcb);
#define MCFG_I8243_WRITEHANDLER(_devcb) \
	devcb = &i8243_device::set_write_handler(*device, DEVCB_##_devcb);
/***************************************************************************
    TYPE DEFINITIONS
***************************************************************************/


// ======================> i8243_device

class i8243_device :  public device_t
{
public:
	// construction/destruction
<<<<<<< HEAD
	i8243_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// static configuration helpers
	template<class _Object> static devcb_base &set_read_handler(device_t &device, _Object object) { return downcast<i8243_device &>(device).m_readhandler.set_callback(object); }
	template<class _Object> static devcb_base &set_write_handler(device_t &device, _Object object) { return downcast<i8243_device &>(device).m_writehandler.set_callback(object); }

	DECLARE_READ8_MEMBER(i8243_p2_r);
	DECLARE_WRITE8_MEMBER(i8243_p2_w);

	DECLARE_WRITE8_MEMBER(i8243_prog_w);

protected:
	// device-level overrides
	virtual void device_start();
	virtual void device_reset();
	virtual void device_post_load() { }
	virtual void device_clock_changed() { }

private:

	UINT8       m_p[4];             /* 4 ports' worth of data */
	UINT8       m_p2out;            /* port 2 bits that will be returned */
	UINT8       m_p2;               /* most recent port 2 value */
	UINT8       m_opcode;           /* latched opcode */
	UINT8       m_prog;             /* previous PROG state */
=======
	i8243_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// static configuration helpers
	template <class Object> static devcb_base &set_read_handler(device_t &device, Object &&cb) { return downcast<i8243_device &>(device).m_readhandler.set_callback(std::forward<Object>(cb)); }
	template <class Object> static devcb_base &set_write_handler(device_t &device, Object &&cb) { return downcast<i8243_device &>(device).m_writehandler.set_callback(std::forward<Object>(cb)); }

	DECLARE_READ8_MEMBER(p2_r);
	DECLARE_WRITE8_MEMBER(p2_w);

	DECLARE_WRITE_LINE_MEMBER(prog_w);

protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;
	virtual void device_post_load() override { }
	virtual void device_clock_changed() override { }

private:

	uint8_t       m_p[4];             /* 4 ports' worth of data */
	uint8_t       m_p2out;            /* port 2 bits that will be returned */
	uint8_t       m_p2;               /* most recent port 2 value */
	uint8_t       m_opcode;           /* latched opcode */
	uint8_t       m_prog;             /* previous PROG state */
>>>>>>> upstream/master

	devcb_read8    m_readhandler;
	devcb_write8   m_writehandler;
};


// device type definition
<<<<<<< HEAD
extern const device_type I8243;

#endif  /* __I8243_H__ */
=======
DECLARE_DEVICE_TYPE(I8243, i8243_device)

#endif /* __I8243_H__ */
>>>>>>> upstream/master
