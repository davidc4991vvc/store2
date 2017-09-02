// license:BSD-3-Clause
// copyright-holders:R. Belmont
<<<<<<< HEAD
#pragma once

#ifndef __MPU401_H__
#define __MPU401_H__

#include "emu.h"
#include "cpu/m6800/m6800.h"

#define MCFG_MPU401_ADD(_tag, _irqf ) \
	MCFG_DEVICE_ADD(_tag, MPU401, 0) \
	MCFG_IRQ_FUNC(_irqf)

#define MCFG_IRQ_FUNC(_irqf) \
	downcast<mpu401_device *>(device)->set_irqf(DEVCB_##_irqf);
=======
#ifndef MAME_MACHINE_MPU401_H
#define MAME_MACHINE_MPU401_H

#pragma once

#include "cpu/m6800/m6801.h"

#define MCFG_MPU401_ADD(tag, irqf) \
		MCFG_DEVICE_ADD((tag), MPU401, 0) \
		MCFG_IRQ_FUNC(irqf)

#define MCFG_IRQ_FUNC(irqf) \
		devcb = &downcast<mpu401_device *>(device)->set_irqf(DEVCB_##irqf);
>>>>>>> upstream/master

//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

class mpu401_device : public device_t
{
public:
	// construction/destruction
<<<<<<< HEAD
	mpu401_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// optional information overrides
	virtual machine_config_constructor device_mconfig_additions() const;

	required_device<m6801_cpu_device> m_ourcpu;

	template<class _write> void set_irqf(_write wr)
	{
		write_irq.set_callback(wr);
	}

	devcb_write_line write_irq;

=======
	mpu401_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	template <class Write> devcb_base &set_irqf(Write &&wr)
	{
		return write_irq.set_callback(std::forward<Write>(wr));
	}

>>>>>>> upstream/master
	DECLARE_READ8_MEMBER(regs_mode2_r);
	DECLARE_WRITE8_MEMBER(regs_mode2_w);
	DECLARE_READ8_MEMBER(asic_r);
	DECLARE_WRITE8_MEMBER(asic_w);
	DECLARE_READ8_MEMBER(port1_r);
	DECLARE_WRITE8_MEMBER(port1_w);
	DECLARE_READ8_MEMBER(port2_r);
	DECLARE_WRITE8_MEMBER(port2_w);
<<<<<<< HEAD
	DECLARE_WRITE_LINE_MEMBER(midi_rx_w);
=======
>>>>>>> upstream/master

	// public API - call for reads/writes at I/O 330/331 on PC, C0n0/C0n1 on Apple II, etc.
	DECLARE_READ8_MEMBER(mpu_r);
	DECLARE_WRITE8_MEMBER(mpu_w);

protected:
	// device-level overrides
<<<<<<< HEAD
	virtual void device_start();
	virtual void device_reset();
	virtual const rom_entry *device_rom_region() const;
	virtual void device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr);

private:
	UINT8 m_port2;
	UINT8 m_command;
	UINT8 m_mpudata;
	UINT8 m_gatearrstat;
=======
	virtual void device_start() override;
	virtual void device_reset() override;
	virtual const tiny_rom_entry *device_rom_region() const override;
	virtual void device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr) override;
	virtual void device_add_mconfig(machine_config &config) override;

private:
	DECLARE_WRITE_LINE_MEMBER(midi_rx_w);

	required_device<m6801_cpu_device> m_ourcpu;

	devcb_write_line write_irq;

	uint8_t m_port2;
	uint8_t m_command;
	uint8_t m_mpudata;
	uint8_t m_gatearrstat;
>>>>>>> upstream/master
	emu_timer *m_timer;
};

// device type definition
<<<<<<< HEAD
extern const device_type MPU401;

#endif  /* __MPU401_H__ */
=======
DECLARE_DEVICE_TYPE(MPU401, mpu401_device)

#endif // MAME_MACHINE_MPU401_H
>>>>>>> upstream/master
