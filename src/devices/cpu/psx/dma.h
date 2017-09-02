// license:BSD-3-Clause
// copyright-holders:smf
/*
 * PlayStation DMA emulator
 *
 * Copyright 2003-2011 smf
 *
 */

<<<<<<< HEAD
#pragma once

#ifndef __PSXDMA_H__
#define __PSXDMA_H__

#include "emu.h"

extern const device_type PSX_DMA;
=======
#ifndef MAME_CPU_PSX_DMA_H
#define MAME_CPU_PSX_DMA_H

#pragma once


DECLARE_DEVICE_TYPE(PSX_DMA, psxdma_device)
>>>>>>> upstream/master

#define MCFG_PSX_DMA_IRQ_HANDLER(_devcb) \
	devcb = &psxdma_device::set_irq_handler(*device, DEVCB_##_devcb);

<<<<<<< HEAD
typedef delegate<void (UINT32 *, UINT32, INT32)> psx_dma_read_delegate;
typedef delegate<void (UINT32 *, UINT32, INT32)> psx_dma_write_delegate;

struct psx_dma_channel
{
	UINT32 n_base;
	UINT32 n_blockcontrol;
	UINT32 n_channelcontrol;
	emu_timer *timer;
	psx_dma_read_delegate fn_read;
	psx_dma_write_delegate fn_write;
	UINT32 n_ticks;
	UINT32 b_running;
};

class psxdma_device : public device_t
{
public:
	psxdma_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
=======
class psxdma_device : public device_t
{
public:
	typedef delegate<void (uint32_t *, uint32_t, int32_t)> read_delegate;
	typedef delegate<void (uint32_t *, uint32_t, int32_t)> write_delegate;

	psxdma_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
>>>>>>> upstream/master

	// static configuration helpers
	template<class _Object> static devcb_base &set_irq_handler(device_t &device, _Object object) { return downcast<psxdma_device &>(device).m_irq_handler.set_callback(object); }

<<<<<<< HEAD
	void install_read_handler( int n_channel, psx_dma_read_delegate p_fn_dma_read );
	void install_write_handler( int n_channel, psx_dma_read_delegate p_fn_dma_write );
=======
	void install_read_handler( int n_channel, read_delegate p_fn_dma_read );
	void install_write_handler( int n_channel, write_delegate p_fn_dma_write );
>>>>>>> upstream/master

	DECLARE_WRITE32_MEMBER( write );
	DECLARE_READ32_MEMBER( read );

<<<<<<< HEAD
	UINT32 *m_ram;
	size_t m_ramsize;

protected:
	virtual void device_start();
	virtual void device_reset();
	virtual void device_post_load();
	virtual void device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr);

private:
	void dma_start_timer( int n_channel, UINT32 n_ticks );
=======
	uint32_t *m_ram;
	size_t m_ramsize;

protected:
	virtual void device_start() override;
	virtual void device_reset() override;
	virtual void device_post_load() override;
	virtual void device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr) override;

private:
	struct psx_dma_channel
	{
		uint32_t n_base;
		uint32_t n_blockcontrol;
		uint32_t n_channelcontrol;
		emu_timer *timer;
		read_delegate fn_read;
		write_delegate fn_write;
		uint32_t n_ticks;
		uint32_t b_running;
	};

	void dma_start_timer( int n_channel, uint32_t n_ticks );
>>>>>>> upstream/master
	void dma_stop_timer( int n_channel );
	void dma_timer_adjust( int n_channel );
	void dma_interrupt_update();
	void dma_finished( int n_channel );
<<<<<<< HEAD
	void write( offs_t offset, UINT32 data, UINT32 mem_mask );
	UINT32 read( offs_t offset, UINT32 mem_mask );

	psx_dma_channel m_channel[7];
	UINT32 m_dpcp;
	UINT32 m_dicr;
=======

	psx_dma_channel m_channel[7];
	uint32_t m_dpcp;
	uint32_t m_dicr;
>>>>>>> upstream/master

	devcb_write_line m_irq_handler;
};

#endif
