// license:BSD-3-Clause
// copyright-holders:David Haywood
<<<<<<< HEAD

#include "cpu/m68000/m68000.h"

class m68307cpu_device;


#define m68307TIMER_TMR (0x0)
#define m68307TIMER_TRR (0x1)
#define m68307TIMER_TCR (0x2)
#define m68307TIMER_TCN (0x3)
#define m68307TIMER_TER (0x4)
#define m68307TIMER_WRR (0x5)
#define m68307TIMER_WCR (0x6)
#define m68307TIMER_XXX (0x7)

struct m68307_single_timer
{
	UINT16 regs[0x8];
	bool enabled;
	emu_timer *mametimer;
};


class m68307_timer
{
	public:
	m68307_single_timer singletimer[2];

	emu_timer *wd_mametimer;
	m68307cpu_device *parent;

	void write_tmr(UINT16 data, UINT16 mem_mask, int which);
	void write_trr(UINT16 data, UINT16 mem_mask, int which);
	void write_ter(UINT16 data, UINT16 mem_mask, int which);
	UINT16 read_tcn(UINT16 mem_mask, int which);

	void init(m68307cpu_device *device);
	void reset(void);
};
=======
#ifndef MAME_MACHINE_68307TMU_H
#define MAME_MACHINE_68307TMU_H

#pragma once

#include "68307.h"


class m68307_cpu_device::m68307_timer
{
public:
	struct single_timer
	{
		uint16_t regs[0x8];
		bool enabled;
		emu_timer *mametimer;
	};


	single_timer singletimer[2];

	emu_timer *wd_mametimer;
	m68307_cpu_device *parent;

	void write_tmr(uint16_t data, uint16_t mem_mask, int which);
	void write_trr(uint16_t data, uint16_t mem_mask, int which);
	void write_ter(uint16_t data, uint16_t mem_mask, int which);
	uint16_t read_tcn(uint16_t mem_mask, int which);

	void init(m68307_cpu_device *device);
	void reset();

	TIMER_CALLBACK_MEMBER(timer0_callback);
	TIMER_CALLBACK_MEMBER(timer1_callback);
	TIMER_CALLBACK_MEMBER(wd_timer_callback);
};

#endif // MAME_MACHINE_68307TMU_H
>>>>>>> upstream/master
