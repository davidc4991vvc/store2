// license:BSD-3-Clause
// copyright-holders:Karl Stenerud
<<<<<<< HEAD
#pragma once

#ifndef __G65816_H__
#define __G65816_H__
=======
#ifndef MAME_CPU_G65816_G65816_H
#define MAME_CPU_G65816_G65816_H

#pragma once
>>>>>>> upstream/master

#include "g65816cm.h"

/* ======================================================================== */
/* =============================== COPYRIGHT ============================== */
/* ======================================================================== */
/*

G65C816 CPU Emulator V0.92

Copyright Karl Stenerud
All rights reserved.

*/
/* ======================================================================== */
/* ============================= Configuration ============================ */
/* ======================================================================== */

/* GTE Microcircuits G65816 */

/* ======================================================================== */
/* =============================== DEFINES ================================ */
/* ======================================================================== */

/* Interrupt lines - used with g65816_set_irq_line() */
enum
{
	G65816_LINE_NONE,
	G65816_LINE_IRQ,
	G65816_LINE_NMI,
	G65816_LINE_ABORT,
	G65816_LINE_SO,
	G65816_LINE_RDY,
	G65816_LINE_RESET
};

#define G65816_INT_NONE G65816_LINE_NONE
#define G65816_INT_IRQ G65816_LINE_IRQ
#define G65816_INT_NMI G65816_LINE_NMI


<<<<<<< HEAD
/* Registers - used by g65816_set_reg() and g65816_get_reg() */
enum
{
	G65816_PC=1, G65816_S, G65816_P, G65816_A, G65816_X, G65816_Y,
	G65816_PB, G65816_DB, G65816_D, G65816_E,
	G65816_NMI_STATE, G65816_IRQ_STATE,
	_5A22_FASTROM
};


=======
>>>>>>> upstream/master
class g65816_device : public cpu_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	g65816_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
	g65816_device(const machine_config &mconfig, device_type type, const char *name, const char *tag, device_t *owner, UINT32 clock, const char *shortname, const char *source, int cpu_type, address_map_constructor internal = NULL);
=======
	g65816_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
>>>>>>> upstream/master

	void set_read_vector_callback(read8_delegate read_vector);

protected:
<<<<<<< HEAD
	// device-level overrides
	virtual void device_start();
	virtual void device_reset();

	// device_execute_interface overrides
	virtual UINT32 execute_min_cycles() const { return 1; }
	virtual UINT32 execute_max_cycles() const { return 20; }
	virtual UINT32 execute_input_lines() const { return 5; }
	virtual void execute_run();
	virtual void execute_set_input(int inputnum, int state);

	// device_memory_interface overrides
	virtual const address_space_config *memory_space_config(address_spacenum spacenum = AS_0) const { return (spacenum == AS_PROGRAM) ? &m_program_config : NULL; }

	// device_state_interface overrides
	virtual void state_import(const device_state_entry &entry);
	virtual void state_export(const device_state_entry &entry);
	virtual void state_string_export(const device_state_entry &entry, std::string &str);

	// device_disasm_interface overrides
	virtual UINT32 disasm_min_opcode_bytes() const { return 1; }
	virtual UINT32 disasm_max_opcode_bytes() const { return 4; }
	virtual offs_t disasm_disassemble(char *buffer, offs_t pc, const UINT8 *oprom, const UINT8 *opram, UINT32 options);
=======
	/* Registers - used by g65816_set_reg() and g65816_get_reg() */
	enum
	{
		G65816_PC=1, G65816_S, G65816_P, G65816_A, G65816_X, G65816_Y,
		G65816_PB, G65816_DB, G65816_D, G65816_E,
		G65816_NMI_STATE, G65816_IRQ_STATE,
		_5A22_FASTROM
	};

	g65816_device(const machine_config &mconfig, device_type type, const char *tag, device_t *owner, uint32_t clock, int cpu_type, address_map_constructor internal);

	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;

	// device_execute_interface overrides
	virtual uint32_t execute_min_cycles() const override { return 1; }
	virtual uint32_t execute_max_cycles() const override { return 20; }
	virtual uint32_t execute_input_lines() const override { return 5; }
	virtual void execute_run() override;
	virtual void execute_set_input(int inputnum, int state) override;

	// device_memory_interface overrides
	virtual space_config_vector memory_space_config() const override;

	// device_state_interface overrides
	virtual void state_import(const device_state_entry &entry) override;
	virtual void state_export(const device_state_entry &entry) override;
	virtual void state_string_export(const device_state_entry &entry, std::string &str) const override;

	// device_disasm_interface overrides
	virtual uint32_t disasm_min_opcode_bytes() const override { return 1; }
	virtual uint32_t disasm_max_opcode_bytes() const override { return 4; }
	virtual offs_t disasm_disassemble(std::ostream &stream, offs_t pc, const uint8_t *oprom, const uint8_t *opram, uint32_t options) override;
>>>>>>> upstream/master

	address_space_config m_program_config;

	typedef void (g65816_device::*opcode_func) ();
<<<<<<< HEAD
	typedef uint (g65816_device::*get_reg_func)(int regnum);
	typedef void (g65816_device::*set_reg_func)(int regnum, uint val);
=======
	typedef unsigned (g65816_device::*get_reg_func)(int regnum);
	typedef void (g65816_device::*set_reg_func)(int regnum, unsigned val);
>>>>>>> upstream/master
	typedef void (g65816_device::*set_line_func)(int line, int state);
	typedef int (g65816_device::*execute_func)(int cycles);

	static const opcode_func g65816i_opcodes_M0X0[];
<<<<<<< HEAD
	uint g65816i_get_reg_M0X0(int regnum);
	void g65816i_set_reg_M0X0(int regnum, uint val);
=======
	unsigned g65816i_get_reg_M0X0(int regnum);
	void g65816i_set_reg_M0X0(int regnum, unsigned val);
>>>>>>> upstream/master
	void g65816i_set_line_M0X0(int line, int state);
	int  g65816i_execute_M0X0(int cycles);

	static const opcode_func g65816i_opcodes_M0X1[];
<<<<<<< HEAD
	uint g65816i_get_reg_M0X1(int regnum);
	void g65816i_set_reg_M0X1(int regnum, uint val);
=======
	unsigned g65816i_get_reg_M0X1(int regnum);
	void g65816i_set_reg_M0X1(int regnum, unsigned val);
>>>>>>> upstream/master
	void g65816i_set_line_M0X1(int line, int state);
	int  g65816i_execute_M0X1(int cycles);

	static const opcode_func g65816i_opcodes_M1X0[];
<<<<<<< HEAD
	uint g65816i_get_reg_M1X0(int regnum);
	void g65816i_set_reg_M1X0(int regnum, uint val);
=======
	unsigned g65816i_get_reg_M1X0(int regnum);
	void g65816i_set_reg_M1X0(int regnum, unsigned val);
>>>>>>> upstream/master
	void g65816i_set_line_M1X0(int line, int state);
	int  g65816i_execute_M1X0(int cycles);

	static const opcode_func g65816i_opcodes_M1X1[];
<<<<<<< HEAD
	uint g65816i_get_reg_M1X1(int regnum);
	void g65816i_set_reg_M1X1(int regnum, uint val);
=======
	unsigned g65816i_get_reg_M1X1(int regnum);
	void g65816i_set_reg_M1X1(int regnum, unsigned val);
>>>>>>> upstream/master
	void g65816i_set_line_M1X1(int line, int state);
	int  g65816i_execute_M1X1(int cycles);

	static const opcode_func g65816i_opcodes_E[];
<<<<<<< HEAD
	uint g65816i_get_reg_E(int regnum);
	void g65816i_set_reg_E(int regnum, uint val);
	void g65816i_set_line_E(int line, int state);
	int  g65816i_execute_E(int cycles);

	void g65816i_set_execution_mode(uint mode);
	int bus_5A22_cycle_burst(uint addr);
=======
	unsigned g65816i_get_reg_E(int regnum);
	void g65816i_set_reg_E(int regnum, unsigned val);
	void g65816i_set_line_E(int line, int state);
	int  g65816i_execute_E(int cycles);

	void g65816i_set_execution_mode(unsigned mode);
	int bus_5A22_cycle_burst(unsigned addr);
>>>>>>> upstream/master
	unsigned g65816_get_pc();
	void g65816_set_pc(unsigned val);
	unsigned g65816_get_sp();
	void g65816_set_sp(unsigned val);
	unsigned g65816_get_reg(int regnum);
	void g65816_set_reg(int regnum, unsigned value);
	void g65816_restore_state();
<<<<<<< HEAD
	uint g65816i_read_8_normal(uint address);
	uint g65816i_read_8_immediate(uint address);
	uint g65816i_read_8_direct(uint address);
	uint g65816i_read_8_vector(uint address);
	void g65816i_write_8_normal(uint address, uint value);
	void g65816i_write_8_direct(uint address, uint value);
	uint g65816i_read_16_normal(uint address);
	uint g65816i_read_16_immediate(uint address);
	uint g65816i_read_16_direct(uint address);
	uint g65816i_read_16_vector(uint address);
	void g65816i_write_16_normal(uint address, uint value);
	void g65816i_write_16_direct(uint address, uint value);
	uint g65816i_read_24_normal(uint address);
	uint g65816i_read_24_immediate(uint address);
	uint g65816i_read_24_direct(uint address);
	void g65816i_push_8(uint value);
	uint g65816i_pull_8();
	void g65816i_push_16(uint value);
	uint g65816i_pull_16();
	void g65816i_push_24(uint value);
	uint g65816i_pull_24();
	void g65816i_jump_16(uint address);
	void g65816i_jump_24(uint address);
	void g65816i_branch_8(uint offset);
	void g65816i_branch_16(uint offset);
	void g65816i_set_flag_mx(uint value);
	void g65816i_set_flag_e(uint value);
	void g65816i_set_flag_i(uint value);
	uint g65816i_get_reg_p();
	void g65816i_set_reg_p(uint value);
	void g65816i_interrupt_hardware(uint vector);
	void g65816i_interrupt_software(uint vector);
	void g65816i_interrupt_nmi();
	void g65816i_check_maskable_interrupt();
	uint EA_IMM8();
	uint EA_IMM16();
	uint EA_IMM24();
	uint EA_D();
	uint EA_A();
	uint EA_AL();
	uint EA_DX();
	uint EA_DY();
	uint EA_AX();
	uint EA_ALX();
	uint EA_AY();
	uint EA_DI();
	uint EA_DLI();
	uint EA_AI();
	uint EA_ALI();
	uint EA_DXI();
	uint EA_DIY();
	uint EA_DLIY();
	uint EA_AXI();
	uint EA_S();
	uint EA_SIY();
=======
	unsigned g65816i_read_8_normal(unsigned address);
	unsigned g65816i_read_8_immediate(unsigned address);
	unsigned g65816i_read_8_direct(unsigned address);
	unsigned g65816i_read_8_vector(unsigned address);
	void g65816i_write_8_normal(unsigned address, unsigned value);
	void g65816i_write_8_direct(unsigned address, unsigned value);
	unsigned g65816i_read_16_normal(unsigned address);
	unsigned g65816i_read_16_immediate(unsigned address);
	unsigned g65816i_read_16_direct(unsigned address);
	unsigned g65816i_read_16_vector(unsigned address);
	void g65816i_write_16_normal(unsigned address, unsigned value);
	void g65816i_write_16_direct(unsigned address, unsigned value);
	unsigned g65816i_read_24_normal(unsigned address);
	unsigned g65816i_read_24_immediate(unsigned address);
	unsigned g65816i_read_24_direct(unsigned address);
	void g65816i_push_8(unsigned value);
	unsigned g65816i_pull_8();
	void g65816i_push_16(unsigned value);
	unsigned g65816i_pull_16();
	void g65816i_push_24(unsigned value);
	unsigned g65816i_pull_24();
	void g65816i_jump_16(unsigned address);
	void g65816i_jump_24(unsigned address);
	void g65816i_branch_8(unsigned offset);
	void g65816i_branch_16(unsigned offset);
	void g65816i_set_flag_mx(unsigned value);
	void g65816i_set_flag_e(unsigned value);
	void g65816i_set_flag_i(unsigned value);
	unsigned g65816i_get_reg_p();
	void g65816i_set_reg_p(unsigned value);
	void g65816i_interrupt_hardware(unsigned vector);
	void g65816i_interrupt_software(unsigned vector);
	void g65816i_interrupt_nmi();
	void g65816i_check_maskable_interrupt();
	unsigned EA_IMM8();
	unsigned EA_IMM16();
	unsigned EA_IMM24();
	unsigned EA_D();
	unsigned EA_A();
	unsigned EA_AL();
	unsigned EA_DX();
	unsigned EA_DY();
	unsigned EA_AX();
	unsigned EA_ALX();
	unsigned EA_AY();
	unsigned EA_DI();
	unsigned EA_DLI();
	unsigned EA_AI();
	unsigned EA_ALI();
	unsigned EA_DXI();
	unsigned EA_DIY();
	unsigned EA_DLIY();
	unsigned EA_AXI();
	unsigned EA_S();
	unsigned EA_SIY();
>>>>>>> upstream/master

	static const get_reg_func s_g65816_get_reg[5];
	static const set_reg_func s_g65816_set_reg[5];
	static const set_line_func s_g65816_set_line[5];
	static const execute_func s_g65816_execute[5];

<<<<<<< HEAD
	uint m_a;             /* Accumulator */
	uint m_b;             /* holds high byte of accumulator */
	uint m_x;             /* Index Register X */
	uint m_y;             /* Index Register Y */
	uint m_s;             /* Stack Pointer */
	uint m_pc;            /* Program Counter */
	uint m_ppc;           /* Previous Program Counter */
	uint m_pb;            /* Program Bank (shifted left 16) */
	uint m_db;            /* Data Bank (shifted left 16) */
	uint m_d;             /* Direct Register */
	uint m_flag_e;        /* Emulation Mode Flag */
	uint m_flag_m;        /* Memory/Accumulator Select Flag */
	uint m_flag_x;        /* Index Select Flag */
	uint m_flag_n;        /* Negative Flag */
	uint m_flag_v;        /* Overflow Flag */
	uint m_flag_d;        /* Decimal Mode Flag */
	uint m_flag_i;        /* Interrupt Mask Flag */
	uint m_flag_z;        /* Zero Flag (inverted) */
	uint m_flag_c;        /* Carry Flag */
	uint m_line_irq;      /* Status of the IRQ line */
	uint m_line_nmi;      /* Status of the NMI line */
	uint m_fastROM;       /* SNES specific */
	uint m_ir;            /* Instruction Register */
	uint m_irq_delay;     /* delay 1 instruction before checking irq */
	address_space *m_program;
	read8_delegate m_read_vector; /* Read vector override */
	uint m_stopped;       /* Sets how the CPU is stopped */
=======
	unsigned m_a;             /* Accumulator */
	unsigned m_b;             /* holds high byte of accumulator */
	unsigned m_x;             /* Index Register X */
	unsigned m_y;             /* Index Register Y */
	unsigned m_s;             /* Stack Pointer */
	unsigned m_pc;            /* Program Counter */
	unsigned m_ppc;           /* Previous Program Counter */
	unsigned m_pb;            /* Program Bank (shifted left 16) */
	unsigned m_db;            /* Data Bank (shifted left 16) */
	unsigned m_d;             /* Direct Register */
	unsigned m_flag_e;        /* Emulation Mode Flag */
	unsigned m_flag_m;        /* Memory/Accumulator Select Flag */
	unsigned m_flag_x;        /* Index Select Flag */
	unsigned m_flag_n;        /* Negative Flag */
	unsigned m_flag_v;        /* Overflow Flag */
	unsigned m_flag_d;        /* Decimal Mode Flag */
	unsigned m_flag_i;        /* Interrupt Mask Flag */
	unsigned m_flag_z;        /* Zero Flag (inverted) */
	unsigned m_flag_c;        /* Carry Flag */
	unsigned m_line_irq;      /* Status of the IRQ line */
	unsigned m_line_nmi;      /* Status of the NMI line */
	unsigned m_fastROM;       /* SNES specific */
	unsigned m_ir;            /* Instruction Register */
	unsigned m_irq_delay;     /* delay 1 instruction before checking irq */
	address_space *m_program;
	read8_delegate m_read_vector; /* Read vector override */
	unsigned m_stopped;       /* Sets how the CPU is stopped */
>>>>>>> upstream/master
	const opcode_func* m_opcodes;
	get_reg_func m_get_reg;
	set_reg_func m_set_reg;
	set_line_func m_set_line;
	execute_func m_execute;
<<<<<<< HEAD
	uint m_source;
	uint m_destination;
	int m_ICount;
	int m_cpu_type;
	UINT8 m_rw8_cycles, m_rw16_cycles, m_rw24_cycles;
	UINT32 m_debugger_temp;

	/* 5A22 specific registers */
	UINT8 m_wrmpya, m_wrmpyb;
	UINT16 m_rdmpy;
	UINT16 m_wrdiv;
	UINT8 m_dvdd;
	UINT16 m_rddiv;
=======
	unsigned m_source;
	unsigned m_destination;
	int m_ICount;
	int m_cpu_type;
	uint8_t m_rw8_cycles, m_rw16_cycles, m_rw24_cycles;
	uint32_t m_debugger_temp;

	/* 5A22 specific registers */
	uint8_t m_wrmpya, m_wrmpyb;
	uint16_t m_rdmpy;
	uint16_t m_wrdiv;
	uint8_t m_dvdd;
	uint16_t m_rddiv;
>>>>>>> upstream/master

	void g65816i_00_M0X0();
	void g65816i_01_M0X0();
	void g65816i_02_M0X0();
	void g65816i_03_M0X0();
	void g65816i_04_M0X0();
	void g65816i_05_M0X0();
	void g65816i_06_M0X0();
	void g65816i_07_M0X0();
	void g65816i_08_M0X0();
	void g65816i_09_M0X0();
	void g65816i_0a_M0X0();
	void g65816i_0b_M0X0();
	void g65816i_0c_M0X0();
	void g65816i_0d_M0X0();
	void g65816i_0e_M0X0();
	void g65816i_0f_M0X0();
	void g65816i_10_M0X0();
	void g65816i_11_M0X0();
	void g65816i_12_M0X0();
	void g65816i_13_M0X0();
	void g65816i_14_M0X0();
	void g65816i_15_M0X0();
	void g65816i_16_M0X0();
	void g65816i_17_M0X0();
	void g65816i_18_M0X0();
	void g65816i_19_M0X0();
	void g65816i_1a_M0X0();
	void g65816i_1b_M0X0();
	void g65816i_1c_M0X0();
	void g65816i_1d_M0X0();
	void g65816i_1e_M0X0();
	void g65816i_1f_M0X0();
	void g65816i_20_M0X0();
	void g65816i_21_M0X0();
	void g65816i_22_M0X0();
	void g65816i_23_M0X0();
	void g65816i_24_M0X0();
	void g65816i_25_M0X0();
	void g65816i_26_M0X0();
	void g65816i_27_M0X0();
	void g65816i_28_M0X0();
	void g65816i_29_M0X0();
	void g65816i_2a_M0X0();
	void g65816i_2b_M0X0();
	void g65816i_2c_M0X0();
	void g65816i_2d_M0X0();
	void g65816i_2e_M0X0();
	void g65816i_2f_M0X0();
	void g65816i_30_M0X0();
	void g65816i_31_M0X0();
	void g65816i_32_M0X0();
	void g65816i_33_M0X0();
	void g65816i_34_M0X0();
	void g65816i_35_M0X0();
	void g65816i_36_M0X0();
	void g65816i_37_M0X0();
	void g65816i_38_M0X0();
	void g65816i_39_M0X0();
	void g65816i_3a_M0X0();
	void g65816i_3b_M0X0();
	void g65816i_3c_M0X0();
	void g65816i_3d_M0X0();
	void g65816i_3e_M0X0();
	void g65816i_3f_M0X0();
	void g65816i_40_M0X0();
	void g65816i_41_M0X0();
	void g65816i_42_M0X0();
	void g65816i_43_M0X0();
	void g65816i_44_M0X0();
	void g65816i_45_M0X0();
	void g65816i_46_M0X0();
	void g65816i_47_M0X0();
	void g65816i_48_M0X0();
	void g65816i_49_M0X0();
	void g65816i_4a_M0X0();
	void g65816i_4b_M0X0();
	void g65816i_4c_M0X0();
	void g65816i_4d_M0X0();
	void g65816i_4e_M0X0();
	void g65816i_4f_M0X0();
	void g65816i_50_M0X0();
	void g65816i_51_M0X0();
	void g65816i_52_M0X0();
	void g65816i_53_M0X0();
	void g65816i_54_M0X0();
	void g65816i_55_M0X0();
	void g65816i_56_M0X0();
	void g65816i_57_M0X0();
	void g65816i_58_M0X0();
	void g65816i_59_M0X0();
	void g65816i_5a_M0X0();
	void g65816i_5b_M0X0();
	void g65816i_5c_M0X0();
	void g65816i_5d_M0X0();
	void g65816i_5e_M0X0();
	void g65816i_5f_M0X0();
	void g65816i_60_M0X0();
	void g65816i_61_M0X0();
	void g65816i_62_M0X0();
	void g65816i_63_M0X0();
	void g65816i_64_M0X0();
	void g65816i_65_M0X0();
	void g65816i_66_M0X0();
	void g65816i_67_M0X0();
	void g65816i_68_M0X0();
	void g65816i_69_M0X0();
	void g65816i_6a_M0X0();
	void g65816i_6b_M0X0();
	void g65816i_6c_M0X0();
	void g65816i_6d_M0X0();
	void g65816i_6e_M0X0();
	void g65816i_6f_M0X0();
	void g65816i_70_M0X0();
	void g65816i_71_M0X0();
	void g65816i_72_M0X0();
	void g65816i_73_M0X0();
	void g65816i_74_M0X0();
	void g65816i_75_M0X0();
	void g65816i_76_M0X0();
	void g65816i_77_M0X0();
	void g65816i_78_M0X0();
	void g65816i_79_M0X0();
	void g65816i_7a_M0X0();
	void g65816i_7b_M0X0();
	void g65816i_7c_M0X0();
	void g65816i_7d_M0X0();
	void g65816i_7e_M0X0();
	void g65816i_7f_M0X0();
	void g65816i_80_M0X0();
	void g65816i_81_M0X0();
	void g65816i_82_M0X0();
	void g65816i_83_M0X0();
	void g65816i_84_M0X0();
	void g65816i_85_M0X0();
	void g65816i_86_M0X0();
	void g65816i_87_M0X0();
	void g65816i_88_M0X0();
	void g65816i_89_M0X0();
	void g65816i_8a_M0X0();
	void g65816i_8b_M0X0();
	void g65816i_8c_M0X0();
	void g65816i_8d_M0X0();
	void g65816i_8e_M0X0();
	void g65816i_8f_M0X0();
	void g65816i_90_M0X0();
	void g65816i_91_M0X0();
	void g65816i_92_M0X0();
	void g65816i_93_M0X0();
	void g65816i_94_M0X0();
	void g65816i_95_M0X0();
	void g65816i_96_M0X0();
	void g65816i_97_M0X0();
	void g65816i_98_M0X0();
	void g65816i_99_M0X0();
	void g65816i_9a_M0X0();
	void g65816i_9b_M0X0();
	void g65816i_9c_M0X0();
	void g65816i_9d_M0X0();
	void g65816i_9e_M0X0();
	void g65816i_9f_M0X0();
	void g65816i_a0_M0X0();
	void g65816i_a1_M0X0();
	void g65816i_a2_M0X0();
	void g65816i_a3_M0X0();
	void g65816i_a4_M0X0();
	void g65816i_a5_M0X0();
	void g65816i_a6_M0X0();
	void g65816i_a7_M0X0();
	void g65816i_a8_M0X0();
	void g65816i_a9_M0X0();
	void g65816i_aa_M0X0();
	void g65816i_ab_M0X0();
	void g65816i_ac_M0X0();
	void g65816i_ad_M0X0();
	void g65816i_ae_M0X0();
	void g65816i_af_M0X0();
	void g65816i_b0_M0X0();
	void g65816i_b1_M0X0();
	void g65816i_b2_M0X0();
	void g65816i_b3_M0X0();
	void g65816i_b4_M0X0();
	void g65816i_b5_M0X0();
	void g65816i_b6_M0X0();
	void g65816i_b7_M0X0();
	void g65816i_b8_M0X0();
	void g65816i_b9_M0X0();
	void g65816i_ba_M0X0();
	void g65816i_bb_M0X0();
	void g65816i_bc_M0X0();
	void g65816i_bd_M0X0();
	void g65816i_be_M0X0();
	void g65816i_bf_M0X0();
	void g65816i_c0_M0X0();
	void g65816i_c1_M0X0();
	void g65816i_c2_M0X0();
	void g65816i_c3_M0X0();
	void g65816i_c4_M0X0();
	void g65816i_c5_M0X0();
	void g65816i_c6_M0X0();
	void g65816i_c7_M0X0();
	void g65816i_c8_M0X0();
	void g65816i_c9_M0X0();
	void g65816i_ca_M0X0();
	void g65816i_cb_M0X0();
	void g65816i_cc_M0X0();
	void g65816i_cd_M0X0();
	void g65816i_ce_M0X0();
	void g65816i_cf_M0X0();
	void g65816i_d0_M0X0();
	void g65816i_d1_M0X0();
	void g65816i_d2_M0X0();
	void g65816i_d3_M0X0();
	void g65816i_d4_M0X0();
	void g65816i_d5_M0X0();
	void g65816i_d6_M0X0();
	void g65816i_d7_M0X0();
	void g65816i_d8_M0X0();
	void g65816i_d9_M0X0();
	void g65816i_da_M0X0();
	void g65816i_db_M0X0();
	void g65816i_dc_M0X0();
	void g65816i_dd_M0X0();
	void g65816i_de_M0X0();
	void g65816i_df_M0X0();
	void g65816i_e0_M0X0();
	void g65816i_e1_M0X0();
	void g65816i_e2_M0X0();
	void g65816i_e3_M0X0();
	void g65816i_e4_M0X0();
	void g65816i_e5_M0X0();
	void g65816i_e6_M0X0();
	void g65816i_e7_M0X0();
	void g65816i_e8_M0X0();
	void g65816i_e9_M0X0();
	void g65816i_ea_M0X0();
	void g65816i_eb_M0X0();
	void g65816i_ec_M0X0();
	void g65816i_ed_M0X0();
	void g65816i_ee_M0X0();
	void g65816i_ef_M0X0();
	void g65816i_f0_M0X0();
	void g65816i_f1_M0X0();
	void g65816i_f2_M0X0();
	void g65816i_f3_M0X0();
	void g65816i_f4_M0X0();
	void g65816i_f5_M0X0();
	void g65816i_f6_M0X0();
	void g65816i_f7_M0X0();
	void g65816i_f8_M0X0();
	void g65816i_f9_M0X0();
	void g65816i_fa_M0X0();
	void g65816i_fb_M0X0();
	void g65816i_fc_M0X0();
	void g65816i_fd_M0X0();
	void g65816i_fe_M0X0();
	void g65816i_ff_M0X0();
	void g65816i_00_M0X1();
	void g65816i_01_M0X1();
	void g65816i_02_M0X1();
	void g65816i_03_M0X1();
	void g65816i_04_M0X1();
	void g65816i_05_M0X1();
	void g65816i_06_M0X1();
	void g65816i_07_M0X1();
	void g65816i_08_M0X1();
	void g65816i_09_M0X1();
	void g65816i_0a_M0X1();
	void g65816i_0b_M0X1();
	void g65816i_0c_M0X1();
	void g65816i_0d_M0X1();
	void g65816i_0e_M0X1();
	void g65816i_0f_M0X1();
	void g65816i_10_M0X1();
	void g65816i_11_M0X1();
	void g65816i_12_M0X1();
	void g65816i_13_M0X1();
	void g65816i_14_M0X1();
	void g65816i_15_M0X1();
	void g65816i_16_M0X1();
	void g65816i_17_M0X1();
	void g65816i_18_M0X1();
	void g65816i_19_M0X1();
	void g65816i_1a_M0X1();
	void g65816i_1b_M0X1();
	void g65816i_1c_M0X1();
	void g65816i_1d_M0X1();
	void g65816i_1e_M0X1();
	void g65816i_1f_M0X1();
	void g65816i_20_M0X1();
	void g65816i_21_M0X1();
	void g65816i_22_M0X1();
	void g65816i_23_M0X1();
	void g65816i_24_M0X1();
	void g65816i_25_M0X1();
	void g65816i_26_M0X1();
	void g65816i_27_M0X1();
	void g65816i_28_M0X1();
	void g65816i_29_M0X1();
	void g65816i_2a_M0X1();
	void g65816i_2b_M0X1();
	void g65816i_2c_M0X1();
	void g65816i_2d_M0X1();
	void g65816i_2e_M0X1();
	void g65816i_2f_M0X1();
	void g65816i_30_M0X1();
	void g65816i_31_M0X1();
	void g65816i_32_M0X1();
	void g65816i_33_M0X1();
	void g65816i_34_M0X1();
	void g65816i_35_M0X1();
	void g65816i_36_M0X1();
	void g65816i_37_M0X1();
	void g65816i_38_M0X1();
	void g65816i_39_M0X1();
	void g65816i_3a_M0X1();
	void g65816i_3b_M0X1();
	void g65816i_3c_M0X1();
	void g65816i_3d_M0X1();
	void g65816i_3e_M0X1();
	void g65816i_3f_M0X1();
	void g65816i_40_M0X1();
	void g65816i_41_M0X1();
	void g65816i_42_M0X1();
	void g65816i_43_M0X1();
	void g65816i_44_M0X1();
	void g65816i_45_M0X1();
	void g65816i_46_M0X1();
	void g65816i_47_M0X1();
	void g65816i_48_M0X1();
	void g65816i_49_M0X1();
	void g65816i_4a_M0X1();
	void g65816i_4b_M0X1();
	void g65816i_4c_M0X1();
	void g65816i_4d_M0X1();
	void g65816i_4e_M0X1();
	void g65816i_4f_M0X1();
	void g65816i_50_M0X1();
	void g65816i_51_M0X1();
	void g65816i_52_M0X1();
	void g65816i_53_M0X1();
	void g65816i_54_M0X1();
	void g65816i_55_M0X1();
	void g65816i_56_M0X1();
	void g65816i_57_M0X1();
	void g65816i_58_M0X1();
	void g65816i_59_M0X1();
	void g65816i_5a_M0X1();
	void g65816i_5b_M0X1();
	void g65816i_5c_M0X1();
	void g65816i_5d_M0X1();
	void g65816i_5e_M0X1();
	void g65816i_5f_M0X1();
	void g65816i_60_M0X1();
	void g65816i_61_M0X1();
	void g65816i_62_M0X1();
	void g65816i_63_M0X1();
	void g65816i_64_M0X1();
	void g65816i_65_M0X1();
	void g65816i_66_M0X1();
	void g65816i_67_M0X1();
	void g65816i_68_M0X1();
	void g65816i_69_M0X1();
	void g65816i_6a_M0X1();
	void g65816i_6b_M0X1();
	void g65816i_6c_M0X1();
	void g65816i_6d_M0X1();
	void g65816i_6e_M0X1();
	void g65816i_6f_M0X1();
	void g65816i_70_M0X1();
	void g65816i_71_M0X1();
	void g65816i_72_M0X1();
	void g65816i_73_M0X1();
	void g65816i_74_M0X1();
	void g65816i_75_M0X1();
	void g65816i_76_M0X1();
	void g65816i_77_M0X1();
	void g65816i_78_M0X1();
	void g65816i_79_M0X1();
	void g65816i_7a_M0X1();
	void g65816i_7b_M0X1();
	void g65816i_7c_M0X1();
	void g65816i_7d_M0X1();
	void g65816i_7e_M0X1();
	void g65816i_7f_M0X1();
	void g65816i_80_M0X1();
	void g65816i_81_M0X1();
	void g65816i_82_M0X1();
	void g65816i_83_M0X1();
	void g65816i_84_M0X1();
	void g65816i_85_M0X1();
	void g65816i_86_M0X1();
	void g65816i_87_M0X1();
	void g65816i_88_M0X1();
	void g65816i_89_M0X1();
	void g65816i_8a_M0X1();
	void g65816i_8b_M0X1();
	void g65816i_8c_M0X1();
	void g65816i_8d_M0X1();
	void g65816i_8e_M0X1();
	void g65816i_8f_M0X1();
	void g65816i_90_M0X1();
	void g65816i_91_M0X1();
	void g65816i_92_M0X1();
	void g65816i_93_M0X1();
	void g65816i_94_M0X1();
	void g65816i_95_M0X1();
	void g65816i_96_M0X1();
	void g65816i_97_M0X1();
	void g65816i_98_M0X1();
	void g65816i_99_M0X1();
	void g65816i_9a_M0X1();
	void g65816i_9b_M0X1();
	void g65816i_9c_M0X1();
	void g65816i_9d_M0X1();
	void g65816i_9e_M0X1();
	void g65816i_9f_M0X1();
	void g65816i_a0_M0X1();
	void g65816i_a1_M0X1();
	void g65816i_a2_M0X1();
	void g65816i_a3_M0X1();
	void g65816i_a4_M0X1();
	void g65816i_a5_M0X1();
	void g65816i_a6_M0X1();
	void g65816i_a7_M0X1();
	void g65816i_a8_M0X1();
	void g65816i_a9_M0X1();
	void g65816i_aa_M0X1();
	void g65816i_ab_M0X1();
	void g65816i_ac_M0X1();
	void g65816i_ad_M0X1();
	void g65816i_ae_M0X1();
	void g65816i_af_M0X1();
	void g65816i_b0_M0X1();
	void g65816i_b1_M0X1();
	void g65816i_b2_M0X1();
	void g65816i_b3_M0X1();
	void g65816i_b4_M0X1();
	void g65816i_b5_M0X1();
	void g65816i_b6_M0X1();
	void g65816i_b7_M0X1();
	void g65816i_b8_M0X1();
	void g65816i_b9_M0X1();
	void g65816i_ba_M0X1();
	void g65816i_bb_M0X1();
	void g65816i_bc_M0X1();
	void g65816i_bd_M0X1();
	void g65816i_be_M0X1();
	void g65816i_bf_M0X1();
	void g65816i_c0_M0X1();
	void g65816i_c1_M0X1();
	void g65816i_c2_M0X1();
	void g65816i_c3_M0X1();
	void g65816i_c4_M0X1();
	void g65816i_c5_M0X1();
	void g65816i_c6_M0X1();
	void g65816i_c7_M0X1();
	void g65816i_c8_M0X1();
	void g65816i_c9_M0X1();
	void g65816i_ca_M0X1();
	void g65816i_cb_M0X1();
	void g65816i_cc_M0X1();
	void g65816i_cd_M0X1();
	void g65816i_ce_M0X1();
	void g65816i_cf_M0X1();
	void g65816i_d0_M0X1();
	void g65816i_d1_M0X1();
	void g65816i_d2_M0X1();
	void g65816i_d3_M0X1();
	void g65816i_d4_M0X1();
	void g65816i_d5_M0X1();
	void g65816i_d6_M0X1();
	void g65816i_d7_M0X1();
	void g65816i_d8_M0X1();
	void g65816i_d9_M0X1();
	void g65816i_da_M0X1();
	void g65816i_db_M0X1();
	void g65816i_dc_M0X1();
	void g65816i_dd_M0X1();
	void g65816i_de_M0X1();
	void g65816i_df_M0X1();
	void g65816i_e0_M0X1();
	void g65816i_e1_M0X1();
	void g65816i_e2_M0X1();
	void g65816i_e3_M0X1();
	void g65816i_e4_M0X1();
	void g65816i_e5_M0X1();
	void g65816i_e6_M0X1();
	void g65816i_e7_M0X1();
	void g65816i_e8_M0X1();
	void g65816i_e9_M0X1();
	void g65816i_ea_M0X1();
	void g65816i_eb_M0X1();
	void g65816i_ec_M0X1();
	void g65816i_ed_M0X1();
	void g65816i_ee_M0X1();
	void g65816i_ef_M0X1();
	void g65816i_f0_M0X1();
	void g65816i_f1_M0X1();
	void g65816i_f2_M0X1();
	void g65816i_f3_M0X1();
	void g65816i_f4_M0X1();
	void g65816i_f5_M0X1();
	void g65816i_f6_M0X1();
	void g65816i_f7_M0X1();
	void g65816i_f8_M0X1();
	void g65816i_f9_M0X1();
	void g65816i_fa_M0X1();
	void g65816i_fb_M0X1();
	void g65816i_fc_M0X1();
	void g65816i_fd_M0X1();
	void g65816i_fe_M0X1();
	void g65816i_ff_M0X1();
	void g65816i_00_M1X0();
	void g65816i_01_M1X0();
	void g65816i_02_M1X0();
	void g65816i_03_M1X0();
	void g65816i_04_M1X0();
	void g65816i_05_M1X0();
	void g65816i_06_M1X0();
	void g65816i_07_M1X0();
	void g65816i_08_M1X0();
	void g65816i_09_M1X0();
	void g65816i_0a_M1X0();
	void g65816i_0b_M1X0();
	void g65816i_0c_M1X0();
	void g65816i_0d_M1X0();
	void g65816i_0e_M1X0();
	void g65816i_0f_M1X0();
	void g65816i_10_M1X0();
	void g65816i_11_M1X0();
	void g65816i_12_M1X0();
	void g65816i_13_M1X0();
	void g65816i_14_M1X0();
	void g65816i_15_M1X0();
	void g65816i_16_M1X0();
	void g65816i_17_M1X0();
	void g65816i_18_M1X0();
	void g65816i_19_M1X0();
	void g65816i_1a_M1X0();
	void g65816i_1b_M1X0();
	void g65816i_1c_M1X0();
	void g65816i_1d_M1X0();
	void g65816i_1e_M1X0();
	void g65816i_1f_M1X0();
	void g65816i_20_M1X0();
	void g65816i_21_M1X0();
	void g65816i_22_M1X0();
	void g65816i_23_M1X0();
	void g65816i_24_M1X0();
	void g65816i_25_M1X0();
	void g65816i_26_M1X0();
	void g65816i_27_M1X0();
	void g65816i_28_M1X0();
	void g65816i_29_M1X0();
	void g65816i_2a_M1X0();
	void g65816i_2b_M1X0();
	void g65816i_2c_M1X0();
	void g65816i_2d_M1X0();
	void g65816i_2e_M1X0();
	void g65816i_2f_M1X0();
	void g65816i_30_M1X0();
	void g65816i_31_M1X0();
	void g65816i_32_M1X0();
	void g65816i_33_M1X0();
	void g65816i_34_M1X0();
	void g65816i_35_M1X0();
	void g65816i_36_M1X0();
	void g65816i_37_M1X0();
	void g65816i_38_M1X0();
	void g65816i_39_M1X0();
	void g65816i_3a_M1X0();
	void g65816i_3b_M1X0();
	void g65816i_3c_M1X0();
	void g65816i_3d_M1X0();
	void g65816i_3e_M1X0();
	void g65816i_3f_M1X0();
	void g65816i_40_M1X0();
	void g65816i_41_M1X0();
	void g65816i_42_M1X0();
	void g65816i_43_M1X0();
	void g65816i_44_M1X0();
	void g65816i_45_M1X0();
	void g65816i_46_M1X0();
	void g65816i_47_M1X0();
	void g65816i_48_M1X0();
	void g65816i_49_M1X0();
	void g65816i_4a_M1X0();
	void g65816i_4b_M1X0();
	void g65816i_4c_M1X0();
	void g65816i_4d_M1X0();
	void g65816i_4e_M1X0();
	void g65816i_4f_M1X0();
	void g65816i_50_M1X0();
	void g65816i_51_M1X0();
	void g65816i_52_M1X0();
	void g65816i_53_M1X0();
	void g65816i_54_M1X0();
	void g65816i_55_M1X0();
	void g65816i_56_M1X0();
	void g65816i_57_M1X0();
	void g65816i_58_M1X0();
	void g65816i_59_M1X0();
	void g65816i_5a_M1X0();
	void g65816i_5b_M1X0();
	void g65816i_5c_M1X0();
	void g65816i_5d_M1X0();
	void g65816i_5e_M1X0();
	void g65816i_5f_M1X0();
	void g65816i_60_M1X0();
	void g65816i_61_M1X0();
	void g65816i_62_M1X0();
	void g65816i_63_M1X0();
	void g65816i_64_M1X0();
	void g65816i_65_M1X0();
	void g65816i_66_M1X0();
	void g65816i_67_M1X0();
	void g65816i_68_M1X0();
	void g65816i_69_M1X0();
	void g65816i_6a_M1X0();
	void g65816i_6b_M1X0();
	void g65816i_6c_M1X0();
	void g65816i_6d_M1X0();
	void g65816i_6e_M1X0();
	void g65816i_6f_M1X0();
	void g65816i_70_M1X0();
	void g65816i_71_M1X0();
	void g65816i_72_M1X0();
	void g65816i_73_M1X0();
	void g65816i_74_M1X0();
	void g65816i_75_M1X0();
	void g65816i_76_M1X0();
	void g65816i_77_M1X0();
	void g65816i_78_M1X0();
	void g65816i_79_M1X0();
	void g65816i_7a_M1X0();
	void g65816i_7b_M1X0();
	void g65816i_7c_M1X0();
	void g65816i_7d_M1X0();
	void g65816i_7e_M1X0();
	void g65816i_7f_M1X0();
	void g65816i_80_M1X0();
	void g65816i_81_M1X0();
	void g65816i_82_M1X0();
	void g65816i_83_M1X0();
	void g65816i_84_M1X0();
	void g65816i_85_M1X0();
	void g65816i_86_M1X0();
	void g65816i_87_M1X0();
	void g65816i_88_M1X0();
	void g65816i_89_M1X0();
	void g65816i_8a_M1X0();
	void g65816i_8b_M1X0();
	void g65816i_8c_M1X0();
	void g65816i_8d_M1X0();
	void g65816i_8e_M1X0();
	void g65816i_8f_M1X0();
	void g65816i_90_M1X0();
	void g65816i_91_M1X0();
	void g65816i_92_M1X0();
	void g65816i_93_M1X0();
	void g65816i_94_M1X0();
	void g65816i_95_M1X0();
	void g65816i_96_M1X0();
	void g65816i_97_M1X0();
	void g65816i_98_M1X0();
	void g65816i_99_M1X0();
	void g65816i_9a_M1X0();
	void g65816i_9b_M1X0();
	void g65816i_9c_M1X0();
	void g65816i_9d_M1X0();
	void g65816i_9e_M1X0();
	void g65816i_9f_M1X0();
	void g65816i_a0_M1X0();
	void g65816i_a1_M1X0();
	void g65816i_a2_M1X0();
	void g65816i_a3_M1X0();
	void g65816i_a4_M1X0();
	void g65816i_a5_M1X0();
	void g65816i_a6_M1X0();
	void g65816i_a7_M1X0();
	void g65816i_a8_M1X0();
	void g65816i_a9_M1X0();
	void g65816i_aa_M1X0();
	void g65816i_ab_M1X0();
	void g65816i_ac_M1X0();
	void g65816i_ad_M1X0();
	void g65816i_ae_M1X0();
	void g65816i_af_M1X0();
	void g65816i_b0_M1X0();
	void g65816i_b1_M1X0();
	void g65816i_b2_M1X0();
	void g65816i_b3_M1X0();
	void g65816i_b4_M1X0();
	void g65816i_b5_M1X0();
	void g65816i_b6_M1X0();
	void g65816i_b7_M1X0();
	void g65816i_b8_M1X0();
	void g65816i_b9_M1X0();
	void g65816i_ba_M1X0();
	void g65816i_bb_M1X0();
	void g65816i_bc_M1X0();
	void g65816i_bd_M1X0();
	void g65816i_be_M1X0();
	void g65816i_bf_M1X0();
	void g65816i_c0_M1X0();
	void g65816i_c1_M1X0();
	void g65816i_c2_M1X0();
	void g65816i_c3_M1X0();
	void g65816i_c4_M1X0();
	void g65816i_c5_M1X0();
	void g65816i_c6_M1X0();
	void g65816i_c7_M1X0();
	void g65816i_c8_M1X0();
	void g65816i_c9_M1X0();
	void g65816i_ca_M1X0();
	void g65816i_cb_M1X0();
	void g65816i_cc_M1X0();
	void g65816i_cd_M1X0();
	void g65816i_ce_M1X0();
	void g65816i_cf_M1X0();
	void g65816i_d0_M1X0();
	void g65816i_d1_M1X0();
	void g65816i_d2_M1X0();
	void g65816i_d3_M1X0();
	void g65816i_d4_M1X0();
	void g65816i_d5_M1X0();
	void g65816i_d6_M1X0();
	void g65816i_d7_M1X0();
	void g65816i_d8_M1X0();
	void g65816i_d9_M1X0();
	void g65816i_da_M1X0();
	void g65816i_db_M1X0();
	void g65816i_dc_M1X0();
	void g65816i_dd_M1X0();
	void g65816i_de_M1X0();
	void g65816i_df_M1X0();
	void g65816i_e0_M1X0();
	void g65816i_e1_M1X0();
	void g65816i_e2_M1X0();
	void g65816i_e3_M1X0();
	void g65816i_e4_M1X0();
	void g65816i_e5_M1X0();
	void g65816i_e6_M1X0();
	void g65816i_e7_M1X0();
	void g65816i_e8_M1X0();
	void g65816i_e9_M1X0();
	void g65816i_ea_M1X0();
	void g65816i_eb_M1X0();
	void g65816i_ec_M1X0();
	void g65816i_ed_M1X0();
	void g65816i_ee_M1X0();
	void g65816i_ef_M1X0();
	void g65816i_f0_M1X0();
	void g65816i_f1_M1X0();
	void g65816i_f2_M1X0();
	void g65816i_f3_M1X0();
	void g65816i_f4_M1X0();
	void g65816i_f5_M1X0();
	void g65816i_f6_M1X0();
	void g65816i_f7_M1X0();
	void g65816i_f8_M1X0();
	void g65816i_f9_M1X0();
	void g65816i_fa_M1X0();
	void g65816i_fb_M1X0();
	void g65816i_fc_M1X0();
	void g65816i_fd_M1X0();
	void g65816i_fe_M1X0();
	void g65816i_ff_M1X0();
	void g65816i_00_M1X1();
	void g65816i_01_M1X1();
	void g65816i_02_M1X1();
	void g65816i_03_M1X1();
	void g65816i_04_M1X1();
	void g65816i_05_M1X1();
	void g65816i_06_M1X1();
	void g65816i_07_M1X1();
	void g65816i_08_M1X1();
	void g65816i_09_M1X1();
	void g65816i_0a_M1X1();
	void g65816i_0b_M1X1();
	void g65816i_0c_M1X1();
	void g65816i_0d_M1X1();
	void g65816i_0e_M1X1();
	void g65816i_0f_M1X1();
	void g65816i_10_M1X1();
	void g65816i_11_M1X1();
	void g65816i_12_M1X1();
	void g65816i_13_M1X1();
	void g65816i_14_M1X1();
	void g65816i_15_M1X1();
	void g65816i_16_M1X1();
	void g65816i_17_M1X1();
	void g65816i_18_M1X1();
	void g65816i_19_M1X1();
	void g65816i_1a_M1X1();
	void g65816i_1b_M1X1();
	void g65816i_1c_M1X1();
	void g65816i_1d_M1X1();
	void g65816i_1e_M1X1();
	void g65816i_1f_M1X1();
	void g65816i_20_M1X1();
	void g65816i_21_M1X1();
	void g65816i_22_M1X1();
	void g65816i_23_M1X1();
	void g65816i_24_M1X1();
	void g65816i_25_M1X1();
	void g65816i_26_M1X1();
	void g65816i_27_M1X1();
	void g65816i_28_M1X1();
	void g65816i_29_M1X1();
	void g65816i_2a_M1X1();
	void g65816i_2b_M1X1();
	void g65816i_2c_M1X1();
	void g65816i_2d_M1X1();
	void g65816i_2e_M1X1();
	void g65816i_2f_M1X1();
	void g65816i_30_M1X1();
	void g65816i_31_M1X1();
	void g65816i_32_M1X1();
	void g65816i_33_M1X1();
	void g65816i_34_M1X1();
	void g65816i_35_M1X1();
	void g65816i_36_M1X1();
	void g65816i_37_M1X1();
	void g65816i_38_M1X1();
	void g65816i_39_M1X1();
	void g65816i_3a_M1X1();
	void g65816i_3b_M1X1();
	void g65816i_3c_M1X1();
	void g65816i_3d_M1X1();
	void g65816i_3e_M1X1();
	void g65816i_3f_M1X1();
	void g65816i_40_M1X1();
	void g65816i_41_M1X1();
	void g65816i_42_M1X1();
	void g65816i_43_M1X1();
	void g65816i_44_M1X1();
	void g65816i_45_M1X1();
	void g65816i_46_M1X1();
	void g65816i_47_M1X1();
	void g65816i_48_M1X1();
	void g65816i_49_M1X1();
	void g65816i_4a_M1X1();
	void g65816i_4b_M1X1();
	void g65816i_4c_M1X1();
	void g65816i_4d_M1X1();
	void g65816i_4e_M1X1();
	void g65816i_4f_M1X1();
	void g65816i_50_M1X1();
	void g65816i_51_M1X1();
	void g65816i_52_M1X1();
	void g65816i_53_M1X1();
	void g65816i_54_M1X1();
	void g65816i_55_M1X1();
	void g65816i_56_M1X1();
	void g65816i_57_M1X1();
	void g65816i_58_M1X1();
	void g65816i_59_M1X1();
	void g65816i_5a_M1X1();
	void g65816i_5b_M1X1();
	void g65816i_5c_M1X1();
	void g65816i_5d_M1X1();
	void g65816i_5e_M1X1();
	void g65816i_5f_M1X1();
	void g65816i_60_M1X1();
	void g65816i_61_M1X1();
	void g65816i_62_M1X1();
	void g65816i_63_M1X1();
	void g65816i_64_M1X1();
	void g65816i_65_M1X1();
	void g65816i_66_M1X1();
	void g65816i_67_M1X1();
	void g65816i_68_M1X1();
	void g65816i_69_M1X1();
	void g65816i_6a_M1X1();
	void g65816i_6b_M1X1();
	void g65816i_6c_M1X1();
	void g65816i_6d_M1X1();
	void g65816i_6e_M1X1();
	void g65816i_6f_M1X1();
	void g65816i_70_M1X1();
	void g65816i_71_M1X1();
	void g65816i_72_M1X1();
	void g65816i_73_M1X1();
	void g65816i_74_M1X1();
	void g65816i_75_M1X1();
	void g65816i_76_M1X1();
	void g65816i_77_M1X1();
	void g65816i_78_M1X1();
	void g65816i_79_M1X1();
	void g65816i_7a_M1X1();
	void g65816i_7b_M1X1();
	void g65816i_7c_M1X1();
	void g65816i_7d_M1X1();
	void g65816i_7e_M1X1();
	void g65816i_7f_M1X1();
	void g65816i_80_M1X1();
	void g65816i_81_M1X1();
	void g65816i_82_M1X1();
	void g65816i_83_M1X1();
	void g65816i_84_M1X1();
	void g65816i_85_M1X1();
	void g65816i_86_M1X1();
	void g65816i_87_M1X1();
	void g65816i_88_M1X1();
	void g65816i_89_M1X1();
	void g65816i_8a_M1X1();
	void g65816i_8b_M1X1();
	void g65816i_8c_M1X1();
	void g65816i_8d_M1X1();
	void g65816i_8e_M1X1();
	void g65816i_8f_M1X1();
	void g65816i_90_M1X1();
	void g65816i_91_M1X1();
	void g65816i_92_M1X1();
	void g65816i_93_M1X1();
	void g65816i_94_M1X1();
	void g65816i_95_M1X1();
	void g65816i_96_M1X1();
	void g65816i_97_M1X1();
	void g65816i_98_M1X1();
	void g65816i_99_M1X1();
	void g65816i_9a_M1X1();
	void g65816i_9b_M1X1();
	void g65816i_9c_M1X1();
	void g65816i_9d_M1X1();
	void g65816i_9e_M1X1();
	void g65816i_9f_M1X1();
	void g65816i_a0_M1X1();
	void g65816i_a1_M1X1();
	void g65816i_a2_M1X1();
	void g65816i_a3_M1X1();
	void g65816i_a4_M1X1();
	void g65816i_a5_M1X1();
	void g65816i_a6_M1X1();
	void g65816i_a7_M1X1();
	void g65816i_a8_M1X1();
	void g65816i_a9_M1X1();
	void g65816i_aa_M1X1();
	void g65816i_ab_M1X1();
	void g65816i_ac_M1X1();
	void g65816i_ad_M1X1();
	void g65816i_ae_M1X1();
	void g65816i_af_M1X1();
	void g65816i_b0_M1X1();
	void g65816i_b1_M1X1();
	void g65816i_b2_M1X1();
	void g65816i_b3_M1X1();
	void g65816i_b4_M1X1();
	void g65816i_b5_M1X1();
	void g65816i_b6_M1X1();
	void g65816i_b7_M1X1();
	void g65816i_b8_M1X1();
	void g65816i_b9_M1X1();
	void g65816i_ba_M1X1();
	void g65816i_bb_M1X1();
	void g65816i_bc_M1X1();
	void g65816i_bd_M1X1();
	void g65816i_be_M1X1();
	void g65816i_bf_M1X1();
	void g65816i_c0_M1X1();
	void g65816i_c1_M1X1();
	void g65816i_c2_M1X1();
	void g65816i_c3_M1X1();
	void g65816i_c4_M1X1();
	void g65816i_c5_M1X1();
	void g65816i_c6_M1X1();
	void g65816i_c7_M1X1();
	void g65816i_c8_M1X1();
	void g65816i_c9_M1X1();
	void g65816i_ca_M1X1();
	void g65816i_cb_M1X1();
	void g65816i_cc_M1X1();
	void g65816i_cd_M1X1();
	void g65816i_ce_M1X1();
	void g65816i_cf_M1X1();
	void g65816i_d0_M1X1();
	void g65816i_d1_M1X1();
	void g65816i_d2_M1X1();
	void g65816i_d3_M1X1();
	void g65816i_d4_M1X1();
	void g65816i_d5_M1X1();
	void g65816i_d6_M1X1();
	void g65816i_d7_M1X1();
	void g65816i_d8_M1X1();
	void g65816i_d9_M1X1();
	void g65816i_da_M1X1();
	void g65816i_db_M1X1();
	void g65816i_dc_M1X1();
	void g65816i_dd_M1X1();
	void g65816i_de_M1X1();
	void g65816i_df_M1X1();
	void g65816i_e0_M1X1();
	void g65816i_e1_M1X1();
	void g65816i_e2_M1X1();
	void g65816i_e3_M1X1();
	void g65816i_e4_M1X1();
	void g65816i_e5_M1X1();
	void g65816i_e6_M1X1();
	void g65816i_e7_M1X1();
	void g65816i_e8_M1X1();
	void g65816i_e9_M1X1();
	void g65816i_ea_M1X1();
	void g65816i_eb_M1X1();
	void g65816i_ec_M1X1();
	void g65816i_ed_M1X1();
	void g65816i_ee_M1X1();
	void g65816i_ef_M1X1();
	void g65816i_f0_M1X1();
	void g65816i_f1_M1X1();
	void g65816i_f2_M1X1();
	void g65816i_f3_M1X1();
	void g65816i_f4_M1X1();
	void g65816i_f5_M1X1();
	void g65816i_f6_M1X1();
	void g65816i_f7_M1X1();
	void g65816i_f8_M1X1();
	void g65816i_f9_M1X1();
	void g65816i_fa_M1X1();
	void g65816i_fb_M1X1();
	void g65816i_fc_M1X1();
	void g65816i_fd_M1X1();
	void g65816i_fe_M1X1();
	void g65816i_ff_M1X1();
	void g65816i_00_E();
	void g65816i_01_E();
	void g65816i_02_E();
	void g65816i_03_E();
	void g65816i_04_E();
	void g65816i_05_E();
	void g65816i_06_E();
	void g65816i_07_E();
	void g65816i_08_E();
	void g65816i_09_E();
	void g65816i_0a_E();
	void g65816i_0b_E();
	void g65816i_0c_E();
	void g65816i_0d_E();
	void g65816i_0e_E();
	void g65816i_0f_E();
	void g65816i_10_E();
	void g65816i_11_E();
	void g65816i_12_E();
	void g65816i_13_E();
	void g65816i_14_E();
	void g65816i_15_E();
	void g65816i_16_E();
	void g65816i_17_E();
	void g65816i_18_E();
	void g65816i_19_E();
	void g65816i_1a_E();
	void g65816i_1b_E();
	void g65816i_1c_E();
	void g65816i_1d_E();
	void g65816i_1e_E();
	void g65816i_1f_E();
	void g65816i_20_E();
	void g65816i_21_E();
	void g65816i_22_E();
	void g65816i_23_E();
	void g65816i_24_E();
	void g65816i_25_E();
	void g65816i_26_E();
	void g65816i_27_E();
	void g65816i_28_E();
	void g65816i_29_E();
	void g65816i_2a_E();
	void g65816i_2b_E();
	void g65816i_2c_E();
	void g65816i_2d_E();
	void g65816i_2e_E();
	void g65816i_2f_E();
	void g65816i_30_E();
	void g65816i_31_E();
	void g65816i_32_E();
	void g65816i_33_E();
	void g65816i_34_E();
	void g65816i_35_E();
	void g65816i_36_E();
	void g65816i_37_E();
	void g65816i_38_E();
	void g65816i_39_E();
	void g65816i_3a_E();
	void g65816i_3b_E();
	void g65816i_3c_E();
	void g65816i_3d_E();
	void g65816i_3e_E();
	void g65816i_3f_E();
	void g65816i_40_E();
	void g65816i_41_E();
	void g65816i_42_E();
	void g65816i_43_E();
	void g65816i_44_E();
	void g65816i_45_E();
	void g65816i_46_E();
	void g65816i_47_E();
	void g65816i_48_E();
	void g65816i_49_E();
	void g65816i_4a_E();
	void g65816i_4b_E();
	void g65816i_4c_E();
	void g65816i_4d_E();
	void g65816i_4e_E();
	void g65816i_4f_E();
	void g65816i_50_E();
	void g65816i_51_E();
	void g65816i_52_E();
	void g65816i_53_E();
	void g65816i_54_E();
	void g65816i_55_E();
	void g65816i_56_E();
	void g65816i_57_E();
	void g65816i_58_E();
	void g65816i_59_E();
	void g65816i_5a_E();
	void g65816i_5b_E();
	void g65816i_5c_E();
	void g65816i_5d_E();
	void g65816i_5e_E();
	void g65816i_5f_E();
	void g65816i_60_E();
	void g65816i_61_E();
	void g65816i_62_E();
	void g65816i_63_E();
	void g65816i_64_E();
	void g65816i_65_E();
	void g65816i_66_E();
	void g65816i_67_E();
	void g65816i_68_E();
	void g65816i_69_E();
	void g65816i_6a_E();
	void g65816i_6b_E();
	void g65816i_6c_E();
	void g65816i_6d_E();
	void g65816i_6e_E();
	void g65816i_6f_E();
	void g65816i_70_E();
	void g65816i_71_E();
	void g65816i_72_E();
	void g65816i_73_E();
	void g65816i_74_E();
	void g65816i_75_E();
	void g65816i_76_E();
	void g65816i_77_E();
	void g65816i_78_E();
	void g65816i_79_E();
	void g65816i_7a_E();
	void g65816i_7b_E();
	void g65816i_7c_E();
	void g65816i_7d_E();
	void g65816i_7e_E();
	void g65816i_7f_E();
	void g65816i_80_E();
	void g65816i_81_E();
	void g65816i_82_E();
	void g65816i_83_E();
	void g65816i_84_E();
	void g65816i_85_E();
	void g65816i_86_E();
	void g65816i_87_E();
	void g65816i_88_E();
	void g65816i_89_E();
	void g65816i_8a_E();
	void g65816i_8b_E();
	void g65816i_8c_E();
	void g65816i_8d_E();
	void g65816i_8e_E();
	void g65816i_8f_E();
	void g65816i_90_E();
	void g65816i_91_E();
	void g65816i_92_E();
	void g65816i_93_E();
	void g65816i_94_E();
	void g65816i_95_E();
	void g65816i_96_E();
	void g65816i_97_E();
	void g65816i_98_E();
	void g65816i_99_E();
	void g65816i_9a_E();
	void g65816i_9b_E();
	void g65816i_9c_E();
	void g65816i_9d_E();
	void g65816i_9e_E();
	void g65816i_9f_E();
	void g65816i_a0_E();
	void g65816i_a1_E();
	void g65816i_a2_E();
	void g65816i_a3_E();
	void g65816i_a4_E();
	void g65816i_a5_E();
	void g65816i_a6_E();
	void g65816i_a7_E();
	void g65816i_a8_E();
	void g65816i_a9_E();
	void g65816i_aa_E();
	void g65816i_ab_E();
	void g65816i_ac_E();
	void g65816i_ad_E();
	void g65816i_ae_E();
	void g65816i_af_E();
	void g65816i_b0_E();
	void g65816i_b1_E();
	void g65816i_b2_E();
	void g65816i_b3_E();
	void g65816i_b4_E();
	void g65816i_b5_E();
	void g65816i_b6_E();
	void g65816i_b7_E();
	void g65816i_b8_E();
	void g65816i_b9_E();
	void g65816i_ba_E();
	void g65816i_bb_E();
	void g65816i_bc_E();
	void g65816i_bd_E();
	void g65816i_be_E();
	void g65816i_bf_E();
	void g65816i_c0_E();
	void g65816i_c1_E();
	void g65816i_c2_E();
	void g65816i_c3_E();
	void g65816i_c4_E();
	void g65816i_c5_E();
	void g65816i_c6_E();
	void g65816i_c7_E();
	void g65816i_c8_E();
	void g65816i_c9_E();
	void g65816i_ca_E();
	void g65816i_cb_E();
	void g65816i_cc_E();
	void g65816i_cd_E();
	void g65816i_ce_E();
	void g65816i_cf_E();
	void g65816i_d0_E();
	void g65816i_d1_E();
	void g65816i_d2_E();
	void g65816i_d3_E();
	void g65816i_d4_E();
	void g65816i_d5_E();
	void g65816i_d6_E();
	void g65816i_d7_E();
	void g65816i_d8_E();
	void g65816i_d9_E();
	void g65816i_da_E();
	void g65816i_db_E();
	void g65816i_dc_E();
	void g65816i_dd_E();
	void g65816i_de_E();
	void g65816i_df_E();
	void g65816i_e0_E();
	void g65816i_e1_E();
	void g65816i_e2_E();
	void g65816i_e3_E();
	void g65816i_e4_E();
	void g65816i_e5_E();
	void g65816i_e6_E();
	void g65816i_e7_E();
	void g65816i_e8_E();
	void g65816i_e9_E();
	void g65816i_ea_E();
	void g65816i_eb_E();
	void g65816i_ec_E();
	void g65816i_ed_E();
	void g65816i_ee_E();
	void g65816i_ef_E();
	void g65816i_f0_E();
	void g65816i_f1_E();
	void g65816i_f2_E();
	void g65816i_f3_E();
	void g65816i_f4_E();
	void g65816i_f5_E();
	void g65816i_f6_E();
	void g65816i_f7_E();
	void g65816i_f8_E();
	void g65816i_f9_E();
	void g65816i_fa_E();
	void g65816i_fb_E();
	void g65816i_fc_E();
	void g65816i_fd_E();
	void g65816i_fe_E();
	void g65816i_ff_E();
};


class _5a22_device : public g65816_device
{
public:
<<<<<<< HEAD
	_5a22_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
=======
	_5a22_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
>>>>>>> upstream/master

	DECLARE_WRITE8_MEMBER( wrmpya_w );
	DECLARE_WRITE8_MEMBER( wrmpyb_w );
	DECLARE_WRITE8_MEMBER( wrdivl_w );
	DECLARE_WRITE8_MEMBER( wrdivh_w );
	DECLARE_WRITE8_MEMBER( wrdvdd_w );
	DECLARE_WRITE8_MEMBER( memsel_w );
	DECLARE_READ8_MEMBER( rddivl_r );
	DECLARE_READ8_MEMBER( rddivh_r );
	DECLARE_READ8_MEMBER( rdmpyl_r );
	DECLARE_READ8_MEMBER( rdmpyh_r );

	void set_5a22_map();

protected:
	// device-level overrides
<<<<<<< HEAD
	virtual void device_start();
	virtual void device_reset();

	// device_state_interface overrides
	virtual void state_import(const device_state_entry &entry);
	virtual void state_export(const device_state_entry &entry);
};


extern const device_type G65816;
extern const device_type _5A22;


#define CPU_TYPE_G65816 0
#define CPU_TYPE_5A22 1
=======
	virtual void device_start() override;
	virtual void device_reset() override;

	// device_state_interface overrides
	virtual void state_import(const device_state_entry &entry) override;
	virtual void state_export(const device_state_entry &entry) override;
};


DECLARE_DEVICE_TYPE(G65816, g65816_device)
DECLARE_DEVICE_TYPE(_5A22,  _5a22_device)
>>>>>>> upstream/master


/* ======================================================================== */
/* ============================== END OF FILE ============================= */
/* ======================================================================== */

#endif /* __G65816_H__ */
