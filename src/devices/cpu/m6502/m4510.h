// license:BSD-3-Clause
// copyright-holders:Olivier Galibert
/***************************************************************************

    m4510.h

    65ce02 with a mmu and a port

***************************************************************************/

<<<<<<< HEAD
#ifndef __M4510_H__
#define __M4510_H__
=======
#ifndef MAME_CPU_M6502_M4510_H
#define MAME_CPU_M6502_M4510_H

#pragma once
>>>>>>> upstream/master

#include "m65ce02.h"

class m4510_device : public m65ce02_device {
public:
<<<<<<< HEAD
	m4510_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	static const disasm_entry disasm_entries[0x100];

	virtual offs_t disasm_disassemble(char *buffer, offs_t pc, const UINT8 *oprom, const UINT8 *opram, UINT32 options);
	virtual void do_exec_full();
	virtual void do_exec_partial();
=======
	m4510_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	static const disasm_entry disasm_entries[0x100];

	virtual offs_t disasm_disassemble(std::ostream &stream, offs_t pc, const uint8_t *oprom, const uint8_t *opram, uint32_t options) override;
	virtual void do_exec_full() override;
	virtual void do_exec_partial() override;
>>>>>>> upstream/master

	bool get_nomap() const { return nomap; }

protected:
<<<<<<< HEAD
	UINT32 map_offset[2];
	UINT8 map_enable;
=======
	uint32_t map_offset[2];
	uint8_t map_enable;
>>>>>>> upstream/master
	bool nomap;

	class mi_4510_normal : public memory_interface {
	public:
		m4510_device *base;

		mi_4510_normal(m4510_device *base);
		virtual ~mi_4510_normal() {}
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

	class mi_4510_nd : public mi_4510_normal {
	public:
		mi_4510_nd(m4510_device *base);
		virtual ~mi_4510_nd() {}
<<<<<<< HEAD
		virtual UINT8 read_sync(UINT16 adr);
		virtual UINT8 read_arg(UINT16 adr);
	};

	virtual void device_start();
	virtual void device_reset();
	virtual bool memory_translate(address_spacenum spacenum, int intention, offs_t &address);

	inline UINT32 map(UINT16 adr) {
=======
		virtual uint8_t read_sync(uint16_t adr) override;
		virtual uint8_t read_arg(uint16_t adr) override;
	};

	virtual void device_start() override;
	virtual void device_reset() override;
	virtual bool memory_translate(int spacenum, int intention, offs_t &address) override;

	inline uint32_t map(uint16_t adr) {
>>>>>>> upstream/master
		if(map_enable & (1 << (adr >> 13))) {
			nomap = false;
			return adr + map_offset[adr >> 15];
		}
		nomap = true;
		return adr;
	}

#define O(o) void o ## _full(); void o ## _partial()

	// 4510 opcodes
	O(eom_imp);
	O(map_imp);

#undef O
};

enum {
	M4510_IRQ_LINE = m6502_device::IRQ_LINE,
	M4510_NMI_LINE = m6502_device::NMI_LINE
};

<<<<<<< HEAD
extern const device_type M4510;

#endif
=======
DECLARE_DEVICE_TYPE(M4510, m4510_device)

#endif // MAME_CPU_M6502_M4510_H
>>>>>>> upstream/master
