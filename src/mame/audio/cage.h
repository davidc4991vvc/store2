// license:BSD-3-Clause
// copyright-holders:Aaron Giles
/***************************************************************************

    Atari CAGE Audio Board

****************************************************************************/

<<<<<<< HEAD
#ifndef __ATARI_CAGE__
#define __ATARI_CAGE__

=======
#ifndef MAME_AUDIO_CAGE_H
#define MAME_AUDIO_CAGE_H

#pragma once

#include "machine/gen_latch.h"
>>>>>>> upstream/master
#include "sound/dmadac.h"

#define CAGE_IRQ_REASON_DATA_READY      (1)
#define CAGE_IRQ_REASON_BUFFER_EMPTY    (2)

#define MCFG_ATARI_CAGE_IRQ_CALLBACK(_write) \
	devcb = &atari_cage_device::set_irqhandler_callback(*device, DEVCB_##_write);

#define MCFG_ATARI_CAGE_SPEEDUP(_speedup) \
	atari_cage_device::static_set_speedup(*device, _speedup);

class atari_cage_device : public device_t
{
public:
	// construction/destruction
<<<<<<< HEAD
	atari_cage_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
	atari_cage_device(const machine_config &mconfig, device_type type, const char *name, const char *tag, device_t *owner, UINT32 clock, const char *shortname, const char *source);

	static void static_set_speedup(device_t &device, offs_t speedup) { downcast<atari_cage_device &>(device).m_speedup = speedup; }
	template<class _Object> static devcb_base &set_irqhandler_callback(device_t &device, _Object object) { return downcast<atari_cage_device &>(device).m_irqhandler.set_callback(object); }

	// optional information overrides
	virtual machine_config_constructor device_mconfig_additions() const;

	void reset_w(int state);

	UINT16 main_r();
	void main_w(UINT16 data);

	UINT16 control_r();
	void control_w(UINT16 data);

	TIMER_DEVICE_CALLBACK_MEMBER( dma_timer_callback );
	void update_dma_state(address_space &space);
	TIMER_DEVICE_CALLBACK_MEMBER( cage_timer_callback );
=======
	atari_cage_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	static void static_set_speedup(device_t &device, offs_t speedup) { downcast<atari_cage_device &>(device).m_speedup = speedup; }
	template <class Object> static devcb_base &set_irqhandler_callback(device_t &device, Object &&cb) { return downcast<atari_cage_device &>(device).m_irqhandler.set_callback(std::forward<Object>(cb)); }

	void reset_w(int state);

	uint16_t main_r();
	void main_w(uint16_t data);

	uint16_t control_r();
	void control_w(uint16_t data);

	void update_dma_state(address_space &space);
>>>>>>> upstream/master
	void update_timer(int which);
	void update_serial();
	READ32_MEMBER( tms32031_io_r );
	WRITE32_MEMBER( tms32031_io_w );
	void update_control_lines();
	READ32_MEMBER( cage_from_main_r );
	WRITE32_MEMBER( cage_from_main_ack_w );
	WRITE32_MEMBER( cage_to_main_w );
	READ32_MEMBER( cage_io_status_r );
	TIMER_CALLBACK_MEMBER( cage_deferred_w );
	WRITE32_MEMBER( speedup_w );

protected:
<<<<<<< HEAD
	// device-level overrides
	virtual void device_start();

private:
	cpu_device *m_cpu;
	attotime m_cpu_h1_clock_period;

	UINT8 m_cpu_to_cage_ready;
	UINT8 m_cage_to_cpu_ready;
=======
	atari_cage_device(const machine_config &mconfig, device_type type, const char *tag, device_t *owner, uint32_t clock);

	// device-level overrides
	virtual void device_start() override;
	virtual void device_add_mconfig(machine_config &config) override;

	TIMER_DEVICE_CALLBACK_MEMBER( dma_timer_callback );
	TIMER_DEVICE_CALLBACK_MEMBER( cage_timer_callback );

private:
	required_shared_ptr<uint32_t> m_cageram;
	cpu_device *m_cpu;
	required_device<generic_latch_16_device> m_soundlatch;
	attotime m_cpu_h1_clock_period;

	uint8_t m_cpu_to_cage_ready;
	uint8_t m_cage_to_cpu_ready;
>>>>>>> upstream/master

	devcb_write8 m_irqhandler;


	attotime m_serial_period_per_word;

<<<<<<< HEAD
	UINT8 m_dma_enabled;
	UINT8 m_dma_timer_enabled;
	timer_device *m_dma_timer;

	UINT8 m_timer_enabled[2];
	timer_device *m_timer[2];

	UINT32 m_tms32031_io_regs[0x100];
	UINT16 m_from_main;
	UINT16 m_control;

	UINT32 *m_speedup_ram;
=======
	uint8_t m_dma_enabled;
	uint8_t m_dma_timer_enabled;
	timer_device *m_dma_timer;

	uint8_t m_timer_enabled[2];
	timer_device *m_timer[2];

	uint32_t m_tms32031_io_regs[0x100];
	uint16_t m_from_main;
	uint16_t m_control;

	uint32_t *m_speedup_ram;
>>>>>>> upstream/master
	dmadac_sound_device *m_dmadac[4];

	offs_t m_speedup;
};


// device type definition
<<<<<<< HEAD
extern const device_type ATARI_CAGE;
=======
DECLARE_DEVICE_TYPE(ATARI_CAGE, atari_cage_device)
>>>>>>> upstream/master

class atari_cage_seattle_device : public atari_cage_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	atari_cage_seattle_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// optional information overrides
	virtual machine_config_constructor device_mconfig_additions() const;
=======
	atari_cage_seattle_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

protected:
	// optional information overrides
	virtual void device_add_mconfig(machine_config &config) override;
>>>>>>> upstream/master

};

// device type definition
<<<<<<< HEAD
extern const device_type ATARI_CAGE_SEATTLE;

#endif // __ATARI_CAGE__
=======
DECLARE_DEVICE_TYPE(ATARI_CAGE_SEATTLE, atari_cage_seattle_device)

#endif // MAME_AUDIO_CAGE_H
>>>>>>> upstream/master
