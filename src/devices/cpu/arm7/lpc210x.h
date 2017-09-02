// license:BSD-3-Clause
// copyright-holders:David Haywood

<<<<<<< HEAD
#pragma once

#ifndef __LPC2103__
#define __LPC2103__

#include "emu.h"
=======
#ifndef MAME_CPU_ARM7_LPC2103_H
#define MAME_CPU_ARM7_LPC2103_H

#pragma once

>>>>>>> upstream/master
#include "arm7.h"
#include "arm7core.h"

/***************************************************************************
    DEVICE CONFIGURATION MACROS
***************************************************************************/


/***************************************************************************
    TYPE DEFINITIONS
***************************************************************************/

class lpc210x_device : public arm7_cpu_device
{
public:
<<<<<<< HEAD
	lpc210x_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32);

	// static configuration helpers

	// todo, use an appropriate flash type instead
	UINT8 m_flash[0x8000];

=======
	lpc210x_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t);

	// static configuration helpers

>>>>>>> upstream/master

	DECLARE_READ32_MEMBER(arm_E01FC088_r);
	DECLARE_READ32_MEMBER(flash_r);
	DECLARE_WRITE32_MEMBER(flash_w);

	// timer 0 / 1
	DECLARE_READ32_MEMBER(timer0_r) { return read_timer(space, 0, offset, mem_mask); }
	DECLARE_WRITE32_MEMBER(timer0_w) { write_timer(space, 0, offset, data, mem_mask); }

	DECLARE_READ32_MEMBER(timer1_r) { return read_timer(space, 1, offset, mem_mask); }
	DECLARE_WRITE32_MEMBER(timer1_w) { write_timer(space, 1, offset, data, mem_mask); }

<<<<<<< HEAD
	void write_timer(address_space &space, int timer, int offset, UINT32 data, UINT32 mem_mask);
	UINT32 read_timer(address_space &space, int timer, int offset, UINT32 mem_mask);

	UINT32 m_TxPR[2];
=======
	void write_timer(address_space &space, int timer, int offset, uint32_t data, uint32_t mem_mask);
	uint32_t read_timer(address_space &space, int timer, int offset, uint32_t mem_mask);
>>>>>>> upstream/master

	// VIC
	DECLARE_READ32_MEMBER(vic_r);
	DECLARE_WRITE32_MEMBER(vic_w);

	// PIN select block
	DECLARE_READ32_MEMBER(pin_r);
	DECLARE_WRITE32_MEMBER(pin_w);

	//PLL Phase Locked Loop
	DECLARE_READ32_MEMBER(pll_r);
	DECLARE_WRITE32_MEMBER(pll_w);

	//MAM memory controller
	DECLARE_READ32_MEMBER(mam_r);
	DECLARE_WRITE32_MEMBER(mam_w);

	//APB divider
	DECLARE_READ32_MEMBER(apbdiv_r);
	DECLARE_WRITE32_MEMBER(apbdiv_w);

	//syscon misc
	DECLARE_READ32_MEMBER(scs_r);
	DECLARE_WRITE32_MEMBER(scs_w);

	// fio
	DECLARE_READ32_MEMBER(fio_r);
	DECLARE_WRITE32_MEMBER(fio_w);

<<<<<<< HEAD
protected:
	// device-level overrides
	virtual machine_config_constructor device_mconfig_additions() const;
	virtual void device_start();
	virtual void device_reset();

	virtual const address_space_config *memory_space_config(address_spacenum spacenum = AS_0) const;






private:
	address_space_config m_program_config;





=======
	// todo, use an appropriate flash type instead
	uint8_t m_flash[0x8000]; // needs to be public because the harmony/melody device injects contents with memcpy, yuck

protected:
	// device-level overrides
	virtual void device_add_mconfig(machine_config &config) override;
	virtual void device_start() override;
	virtual void device_reset() override;

	virtual space_config_vector memory_space_config() const override;

	uint32_t m_TxPR[2];

private:
	address_space_config m_program_config;
>>>>>>> upstream/master
};


// device type definition
<<<<<<< HEAD
extern const device_type LPC2103;


#endif /// __LPC2103__
=======
DECLARE_DEVICE_TYPE(LPC2103, lpc210x_device)

#endif // MAME_CPU_ARM7_LPC2103_H
>>>>>>> upstream/master
