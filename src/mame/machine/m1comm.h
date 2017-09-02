// license:BSD-3-Clause
// copyright-holders:Ariane Fugmann
<<<<<<< HEAD
#pragma once

#ifndef __M1COMM_H__
#define __M1COMM_H__

#define __M1COMM_SIMULATION__

#include "emu.h"
=======
#ifndef MAME_MACHINE_M1COMM_H
#define MAME_MACHINE_M1COMM_H

#pragma once

#define M1COMM_SIMULATION

>>>>>>> upstream/master
#include "cpu/z80/z80.h"

#define MCFG_M1COMM_ADD(_tag ) \
	MCFG_DEVICE_ADD(_tag, M1COMM, 0)

//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

class m1comm_device : public device_t
{
public:
	// construction/destruction
<<<<<<< HEAD
	m1comm_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// optional information overrides
	virtual machine_config_constructor device_mconfig_additions() const;

	required_device<z80_device> m_commcpu;
=======
	m1comm_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
>>>>>>> upstream/master

	// internal API - stuff that happens on the comm board
	// MB89374 registers
	DECLARE_READ8_MEMBER(dlc_reg_r);
	DECLARE_WRITE8_MEMBER(dlc_reg_w);
	// MB89237A registers
	DECLARE_READ8_MEMBER(dma_reg_r);
	DECLARE_WRITE8_MEMBER(dma_reg_w);
	// single bit registers (74LS74)
	DECLARE_READ8_MEMBER(syn_r);
	DECLARE_WRITE8_MEMBER(syn_w);
	DECLARE_READ8_MEMBER(zfg_r);
	DECLARE_WRITE8_MEMBER(zfg_w);
	// shared memory 4k
	DECLARE_READ8_MEMBER(share_r);
	DECLARE_WRITE8_MEMBER(share_w);

	// public API - stuff that gets called from the model1
	// shared memory 4k
	// reads/writes at I/O 0xB00xxx
	// - share_r
	// - share_w
	// single bit registers (74LS74)
	// reads/writes at I/O 0xB01000
	DECLARE_READ8_MEMBER(cn_r);
	DECLARE_WRITE8_MEMBER(cn_w);
	// reads/writes at I/O 0xB01002
	DECLARE_READ8_MEMBER(fg_r);
	DECLARE_WRITE8_MEMBER(fg_w);

	// IRQ logic - 5 = VINT, 7 = DLC
	void check_vint_irq();

protected:
	// device-level overrides
<<<<<<< HEAD
	virtual void device_start();
	virtual void device_reset();
	virtual const rom_entry *device_rom_region() const;

private:
	UINT8 m_shared[0x1000]; // 2x 2k = 4k; model1 accesses this with 16bit data and 11bit address (A0 to A10)
	UINT8 m_dlc_reg[0x20];  // MB89374 registers
	UINT8 m_dma_reg[0x20];  // MB89237A registers
	UINT8   m_syn;                      // bit0 is stored; purpose unknown, bit1 is used to enable/disable VINT/IRQ5
	UINT8   m_zfg;                      // z80 flip gate? purpose unknown, bit0 is stored
	UINT8   m_cn;                           // bit0 is used to enable/disable the comm board
	UINT8   m_fg;                           // flip gate? purpose unknown, bit0 is stored, bit7 is connected to ZFG bit 0

	emu_file m_line_rx;    // rx line - can be either differential, simple serial or toslink
	emu_file m_line_tx;    // tx line - is differential, simple serial and toslink
	char m_localhost[256];
	char m_remotehost[256];
	UINT8 m_buffer[0x1000];

#ifdef __M1COMM_SIMULATION__
	UINT8 m_linkenable;
	UINT16 m_linktimer;
	UINT8 m_linkalive;
	UINT8 m_linkid;
	UINT8 m_linkcount;
=======
	virtual void device_start() override;
	virtual void device_reset() override;
	virtual const tiny_rom_entry *device_rom_region() const override;
	// optional information overrides
	virtual void device_add_mconfig(machine_config &config) override;

private:
	required_device<z80_device> m_commcpu;

	uint8_t m_shared[0x1000]; // 2x 2k = 4k; model1 accesses this with 16bit data and 11bit address (A0 to A10)
	uint8_t m_dlc_reg[0x20];  // MB89374 registers
	uint8_t m_dma_reg[0x20];  // MB89237A registers
	uint8_t m_syn;            // bit0 is stored; purpose unknown, bit1 is used to enable/disable VINT/IRQ5
	uint8_t m_zfg;            // z80 flip gate? purpose unknown, bit0 is stored
	uint8_t m_cn;             // bit0 is used to enable/disable the comm board
	uint8_t m_fg;             // flip gate? purpose unknown, bit0 is stored, bit7 is connected to ZFG bit 0

	emu_file m_line_rx;       // rx line - can be either differential, simple serial or toslink
	emu_file m_line_tx;       // tx line - is differential, simple serial and toslink
	char m_localhost[256];
	char m_remotehost[256];
	uint8_t m_buffer[0x1000];

#ifdef M1COMM_SIMULATION
	uint8_t m_linkenable;
	uint16_t m_linktimer;
	uint8_t m_linkalive;
	uint8_t m_linkid;
	uint8_t m_linkcount;
>>>>>>> upstream/master

	void comm_tick();
#endif
};

// device type definition
extern const device_type M1COMM;

<<<<<<< HEAD
#endif  /* __M1COMM_H__ */
=======
#endif  // MAME_MACHINE_M1COMM_H
>>>>>>> upstream/master
