// license:BSD-3-Clause
<<<<<<< HEAD
// copyright-holders:Angelo Salese
=======
// copyright-holders:<author_name>
>>>>>>> upstream/master
/*****************************************************************************
 *
 * template for CPU cores
 *
 *****************************************************************************/

<<<<<<< HEAD
#pragma once

#ifndef __XXX_H__
#define __XXX_H__
=======
#ifndef MAME_CPU_XXX_H
#define MAME_CPU_XXX_H

#pragma once
>>>>>>> upstream/master

enum
{
	#if UNUSED
	XXX_R0=1, XXX_R1, XXX_R2, XXX_R3,
	XXX_R4, XXX_R5, XXX_R6, XXX_R7
	#endif
};


class xxx_cpu_device :  public cpu_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	xxx_cpu_device(const machine_config &mconfig, const char *_tag, device_t *_owner, UINT32 _clock);

protected:
	// device-level overrides
	virtual void device_start();
	virtual void device_reset();

	// device_execute_interface overrides
	virtual UINT32 execute_min_cycles() const { return 1; }
	virtual UINT32 execute_max_cycles() const { return 7; }
	virtual UINT32 execute_input_lines() const { return 0; }
	virtual void execute_run();
	virtual void execute_set_input(int inputnum, int state);

	// device_memory_interface overrides
	virtual const address_space_config *memory_space_config(address_spacenum spacenum = AS_0) const { return (spacenum == AS_PROGRAM) ? &m_program_config : ( (spacenum == AS_DATA) ? &m_data_config : NULL ); }

	// device_state_interface overrides
	void state_string_export(const device_state_entry &entry, std::string &str);

	// device_disasm_interface overrides
	virtual UINT32 disasm_min_opcode_bytes() const { return 4; }
	virtual UINT32 disasm_max_opcode_bytes() const { return 4; }
	virtual offs_t disasm_disassemble(char *buffer, offs_t pc, const UINT8 *oprom, const UINT8 *opram, UINT32 options);
=======
	xxx_cpu_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;

	// device_execute_interface overrides
	virtual uint32_t execute_min_cycles() const override { return 1; }
	virtual uint32_t execute_max_cycles() const override { return 7; }
	virtual uint32_t execute_input_lines() const override { return 0; }
	virtual void execute_run() override;
	virtual void execute_set_input(int inputnum, int state) override;

	// device_memory_interface overrides
	virtual const address_space_config *memory_space_config(int spacenum) const override { return (spacenum == AS_PROGRAM) ? &m_program_config : (spacenum == AS_DATA) ? &m_data_config : nullptr; }

	// device_state_interface overrides
	virtual void state_string_export(const device_state_entry &entry, std::string &str) const override;

	// device_disasm_interface overrides
	virtual uint32_t disasm_min_opcode_bytes() const override { return 4; }
	virtual uint32_t disasm_max_opcode_bytes() const override { return 4; }
	virtual offs_t disasm_disassemble(char *buffer, offs_t pc, const uint8_t *oprom, const uint8_t *opram, uint32_t options) override;
>>>>>>> upstream/master

private:
	address_space_config m_program_config;

<<<<<<< HEAD
	UINT8   m_pc;   /* registers */
	UINT8   m_flags;  /* flags */
=======
	uint8_t   m_pc;   /* registers */
	uint8_t   m_flags;  /* flags */
>>>>>>> upstream/master
	address_space *m_program;
	address_space *m_data;
	int m_icount;

	void xxx_illegal();

};


<<<<<<< HEAD
extern const device_type XXX;
=======
DECLARE_DEVICE_TYPE(XXX, xxx_cpu_device)
>>>>>>> upstream/master


CPU_DISASSEMBLE( xxx );

<<<<<<< HEAD
#endif /* __XXX_H__ */
=======
#endif // MAME_CPU_XXX_H
>>>>>>> upstream/master
