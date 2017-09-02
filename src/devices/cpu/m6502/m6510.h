// license:BSD-3-Clause
// copyright-holders:Olivier Galibert
/***************************************************************************

    m6510.h

    6502 with 6 i/o pins, also known as 8500

***************************************************************************/
<<<<<<< HEAD

#ifndef __M6510FAM_H__
#define __M6510FAM_H__
=======
#ifndef MAME_CPU_M6502_M6510_H
#define MAME_CPU_M6502_M6510_H

#pragma once
>>>>>>> upstream/master

#include "m6502.h"

#define MCFG_M6510_PORT_CALLBACKS(_read, _write) \
	downcast<m6510_device *>(device)->set_callbacks(DEVCB_##_read, DEVCB_##_write);

#define MCFG_M6510_PORT_PULLS(_up, _down) \
	downcast<m6510_device *>(device)->set_pulls(_up, _down);

class m6510_device : public m6502_device {
public:
<<<<<<< HEAD
	m6510_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
	m6510_device(const machine_config &mconfig, device_type type, const char *name, const char *tag, device_t *owner, UINT32 clock, const char *shortname, const char *source);

	UINT8 get_port();
	void set_port(UINT8 val);
	void set_pulls(UINT8 pullup, UINT8 pulldown);
=======
	m6510_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	uint8_t get_port();
	void set_pulls(uint8_t pullup, uint8_t pulldown);
>>>>>>> upstream/master

	template<class _read, class _write> void set_callbacks(_read rd, _write wr) {
		read_port.set_callback(rd);
		write_port.set_callback(wr);
	}

	static const disasm_entry disasm_entries[0x100];

<<<<<<< HEAD
	virtual offs_t disasm_disassemble(char *buffer, offs_t pc, const UINT8 *oprom, const UINT8 *opram, UINT32 options);
	virtual void do_exec_full();
	virtual void do_exec_partial();

protected:
=======
	virtual offs_t disasm_disassemble(std::ostream &stream, offs_t pc, const uint8_t *oprom, const uint8_t *opram, uint32_t options) override;
	virtual void do_exec_full() override;
	virtual void do_exec_partial() override;

protected:
	m6510_device(const machine_config &mconfig, device_type type, const char *tag, device_t *owner, uint32_t clock);

>>>>>>> upstream/master
	class mi_6510_normal : public memory_interface {
	public:
		m6510_device *base;

		mi_6510_normal(m6510_device *base);
		virtual ~mi_6510_normal() {}
<<<<<<< HEAD
		virtual UINT8 read(UINT16 adr);
		virtual UINT8 read_sync(UINT16 adr);
		virtual UINT8 read_arg(UINT16 adr);
		virtual void write(UINT16 adr, UINT8 val);
=======
		virtual uint8_t read(uint16_t adr) override;
		virtual uint8_t read_sync(uint16_t adr) override;
		virtual uint8_t read_arg(uint16_t adr) override;
		virtual void write(uint16_t adr, uint8_t val) override;
>>>>>>> upstream/master
	};

	class mi_6510_nd : public mi_6510_normal {
	public:
		mi_6510_nd(m6510_device *base);
		virtual ~mi_6510_nd() {}
<<<<<<< HEAD
		virtual UINT8 read_sync(UINT16 adr);
		virtual UINT8 read_arg(UINT16 adr);
=======
		virtual uint8_t read_sync(uint16_t adr) override;
		virtual uint8_t read_arg(uint16_t adr) override;
>>>>>>> upstream/master
	};

	devcb_read8  read_port;
	devcb_write8 write_port;

<<<<<<< HEAD
	UINT8 pullup, floating, dir, port, drive;

	virtual void device_start();
	virtual void device_reset();

	UINT8 dir_r();
	void dir_w(UINT8 data);
	UINT8 port_r();
	void port_w(UINT8 data);
=======
	uint8_t pullup, floating, dir, port, drive;

	virtual void device_start() override;
	virtual void device_reset() override;

	uint8_t dir_r();
	void dir_w(uint8_t data);
	uint8_t port_r();
	void port_w(uint8_t data);
>>>>>>> upstream/master

	void update_port();

#define O(o) void o ## _full(); void o ## _partial()

	// 6510 undocumented instructions in a C64 context
	// implementation follows what the test suites expect (usually an extra and)
	O(anc_10_imm);
	O(ane_10_imm);
	O(arr_10_imm);
	O(asr_10_imm);
	O(las_10_aby);
	O(lxa_10_imm);

#undef O
};

enum {
	M6510_IRQ_LINE = m6502_device::IRQ_LINE,
	M6510_NMI_LINE = m6502_device::NMI_LINE
};

<<<<<<< HEAD
extern const device_type M6510;

#endif
=======
DECLARE_DEVICE_TYPE(M6510, m6510_device)

#endif // MAME_CPU_M6502_M6510_H
>>>>>>> upstream/master
