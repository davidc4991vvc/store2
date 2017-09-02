// license:BSD-3-Clause
// copyright-holders:hap
/*

  Mitsubishi M58846 MCU

*/

<<<<<<< HEAD
#ifndef _M58846_H_
#define _M58846_H_
=======
#ifndef MAME_CPU_MELPS4_M58846_H
#define MAME_CPU_MELPS4_M58846_H

#pragma once
>>>>>>> upstream/master

#include "melps4.h"

// note: for pinout and more info, see melps4.h


class m58846_device : public melps4_cpu_device
{
public:
<<<<<<< HEAD
	m58846_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

protected:
	// device-level overrides
	virtual void device_start();
	virtual void device_reset();

	// device_execute_interface overrides
	virtual void execute_one();

	// device_disasm_interface overrides
	virtual offs_t disasm_disassemble(char *buffer, offs_t pc, const UINT8 *oprom, const UINT8 *opram, UINT32 options);

	// timers
	virtual void device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr);
	virtual void write_v(UINT8 data);
=======
	m58846_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;

	// device_execute_interface overrides
	virtual void execute_one() override;

	// device_disasm_interface overrides
	virtual offs_t disasm_disassemble(std::ostream &stream, offs_t pc, const uint8_t *oprom, const uint8_t *opram, uint32_t options) override;

	// timers
	virtual void device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr) override;
	virtual void write_v(uint8_t data) override;
>>>>>>> upstream/master

	emu_timer *m_timer;
	void reset_timer();
};


<<<<<<< HEAD

extern const device_type M58846;


#endif /* _M58846_H_ */
=======
DECLARE_DEVICE_TYPE(M58846, m58846_device)

#endif // MAME_CPU_MELPS4_M58846_H
>>>>>>> upstream/master
