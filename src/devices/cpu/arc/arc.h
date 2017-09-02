// license:BSD-3-Clause
// copyright-holders:David Haywood
/*********************************\

 ARCtangent (A4) core
 ARC == Argonaut RISC Core

\*********************************/

<<<<<<< HEAD
#pragma once

#ifndef __ARC_H__
#define __ARC_H__

class arc_device : public cpu_device
{
public:
	// construction/destruction
	arc_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

protected:
	// device-level overrides
	virtual void device_start();
	virtual void device_reset();

	// device_execute_interface overrides
	virtual UINT32 execute_min_cycles() const { return 5; }
	virtual UINT32 execute_max_cycles() const { return 5; }
	virtual UINT32 execute_input_lines() const { return 0; }
	virtual void execute_run();
	virtual void execute_set_input(int inputnum, int state);

	// device_memory_interface overrides
	virtual const address_space_config *memory_space_config(address_spacenum spacenum = AS_0) const { return (spacenum == AS_PROGRAM) ? &m_program_config : NULL; }

	// device_state_interface overrides
	virtual void state_import(const device_state_entry &entry);
	virtual void state_export(const device_state_entry &entry);

	// device_disasm_interface overrides
	virtual UINT32 disasm_min_opcode_bytes() const { return 4; }
	virtual UINT32 disasm_max_opcode_bytes() const { return 4; }
	virtual offs_t disasm_disassemble(char *buffer, offs_t pc, const UINT8 *oprom, const UINT8 *opram, UINT32 options);
=======
#ifndef MAME_CPU_ARC_ARC_H
#define MAME_CPU_ARC_ARC_H

#pragma once

enum
{
	ARC_PC = STATE_GENPC
};

class arc_cpu_device : public cpu_device
{
public:
	// construction/destruction
	arc_cpu_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;

	// device_execute_interface overrides
	virtual uint32_t execute_min_cycles() const override { return 5; }
	virtual uint32_t execute_max_cycles() const override { return 5; }
	virtual uint32_t execute_input_lines() const override { return 0; }
	virtual void execute_run() override;
	virtual void execute_set_input(int inputnum, int state) override;

	// device_memory_interface overrides
	virtual space_config_vector memory_space_config() const override;

	// device_state_interface overrides
	virtual void state_import(const device_state_entry &entry) override;
	virtual void state_export(const device_state_entry &entry) override;

	// device_disasm_interface overrides
	virtual uint32_t disasm_min_opcode_bytes() const override { return 4; }
	virtual uint32_t disasm_max_opcode_bytes() const override { return 4; }
	virtual offs_t disasm_disassemble(std::ostream &stream, offs_t pc, const uint8_t *oprom, const uint8_t *opram, uint32_t options) override;
>>>>>>> upstream/master

private:
	address_space_config m_program_config;

	// 0 - 28 = r00 - r28 (General Purpose Registers)
	//     29 = r29 (ILINK1)
	//     30 = r30 (ILINE2)
	//     31 = r31 (BLINK)
	// 32- 59 = r32 - r59 (Reserved Registers)
	//     60 = LPCOUNT
	//     61 = Short Immediate Data Indicator Settings Flag
	//     62 = Long Immediate Data Indicator
	//     63 = Short Immediate Data Indicator NOT Settings Flag
<<<<<<< HEAD
	UINT32 m_pc;
	//UINT32 m_r[64];
=======
	uint32_t m_pc;
	//uint32_t m_r[64];
>>>>>>> upstream/master


	address_space *m_program;
	int m_icount;

<<<<<<< HEAD
	UINT32 m_debugger_temp;

	void unimplemented_opcode(UINT16 op);
	inline UINT32 READ32(UINT32 address);
	inline void WRITE32(UINT32 address, UINT32 data);
};


extern const device_type ARC;


#endif /* __ARC_H__ */
=======
	uint32_t m_debugger_temp;

	void unimplemented_opcode(uint16_t op);
	inline uint32_t READ32(uint32_t address);
	inline void WRITE32(uint32_t address, uint32_t data);
};


DECLARE_DEVICE_TYPE(ARC, arc_cpu_device)

#endif // MAME_CPU_ARC_ARC_H
>>>>>>> upstream/master
