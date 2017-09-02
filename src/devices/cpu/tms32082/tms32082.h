// license:BSD-3-Clause
// copyright-holders:Ville Linde
<<<<<<< HEAD
#pragma once

#ifndef __TMS32082_H__
#define __TMS32082_H__
=======
#ifndef MAME_CPU_TMS32082_TMS32082_H
#define MAME_CPU_TMS32082_TMS32082_H

#pragma once
>>>>>>> upstream/master

// Master Processor class
class tms32082_mp_device : public cpu_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	tms32082_mp_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
=======
	tms32082_mp_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
>>>>>>> upstream/master

	enum
	{
		MP_PC=1,
		MP_R0,
		MP_R1,
		MP_R2,
		MP_R3,
		MP_R4,
		MP_R5,
		MP_R6,
		MP_R7,
		MP_R8,
		MP_R9,
		MP_R10,
		MP_R11,
		MP_R12,
		MP_R13,
		MP_R14,
		MP_R15,
		MP_R16,
		MP_R17,
		MP_R18,
		MP_R19,
		MP_R20,
		MP_R21,
		MP_R22,
		MP_R23,
		MP_R24,
		MP_R25,
		MP_R26,
		MP_R27,
		MP_R28,
		MP_R29,
		MP_R30,
		MP_R31,
		MP_ACC0,
		MP_ACC1,
		MP_ACC2,
		MP_ACC3,
		MP_IN0P,
		MP_IN1P,
		MP_OUTP,
		MP_IE,
		MP_INTPEN,
		MP_TCOUNT,
		MP_TSCALE
	};

	enum
	{
		INPUT_X1        = 1,
		INPUT_X2        = 2,
		INPUT_X3        = 3,
		INPUT_X4        = 4
	};

	DECLARE_READ32_MEMBER(mp_param_r);
	DECLARE_WRITE32_MEMBER(mp_param_w);

<<<<<<< HEAD

protected:
	// device level overrides
	virtual void device_start();
	virtual void device_reset();

	// device_execute_interface overrides
	virtual UINT32 execute_min_cycles() const { return 1; }
	virtual UINT32 execute_max_cycles() const { return 1; }
	virtual UINT32 execute_input_lines() const { return 0; }
	virtual void execute_run();
	virtual void execute_set_input(int inputnum, int state);

	// device_memory_interface overrides
	virtual const address_space_config *memory_space_config(address_spacenum spacenum = AS_0) const
	{
		switch (spacenum)
		{
			case AS_PROGRAM: return &m_program_config;
			default:         return NULL;
		}
	}

	// device_state_interface overrides
	void state_string_export(const device_state_entry &entry, std::string &str);

	// device_disasm_interface overrides
	virtual UINT32 disasm_min_opcode_bytes() const { return 4; }
	virtual UINT32 disasm_max_opcode_bytes() const { return 8; }
	virtual offs_t disasm_disassemble(char *buffer, offs_t pc, const UINT8 *oprom, const UINT8 *opram, UINT32 options);

	address_space_config m_program_config;

	static const UINT32 SHIFT_MASK[33];


	UINT32 m_pc;
	UINT32 m_fetchpc;
	union
	{
		UINT32 m_reg[32];
		UINT64 m_fpair[16];
	};
	union
	{
		UINT64 m_acc[4];
		double m_facc[4];
	};
	UINT32 m_ir;

	UINT32 m_in0p;
	UINT32 m_in1p;
	UINT32 m_outp;
	UINT32 m_ie;
	UINT32 m_intpen;
	UINT32 m_epc;
	UINT32 m_eip;

	UINT32 m_tcount;
	UINT32 m_tscale;

	UINT32 m_param_ram[0x800];
=======
	void set_command_callback(write32_delegate callback);


protected:
	// device level overrides
	virtual void device_start() override;
	virtual void device_reset() override;

	// device_execute_interface overrides
	virtual uint32_t execute_min_cycles() const override { return 1; }
	virtual uint32_t execute_max_cycles() const override { return 1; }
	virtual uint32_t execute_input_lines() const override { return 0; }
	virtual void execute_run() override;
	virtual void execute_set_input(int inputnum, int state) override;

	// device_memory_interface overrides
	virtual space_config_vector memory_space_config() const override;

	// device_state_interface overrides
	virtual void state_string_export(const device_state_entry &entry, std::string &str) const override;

	// device_disasm_interface overrides
	virtual uint32_t disasm_min_opcode_bytes() const override { return 4; }
	virtual uint32_t disasm_max_opcode_bytes() const override { return 8; }
	virtual offs_t disasm_disassemble(std::ostream &stream, offs_t pc, const uint8_t *oprom, const uint8_t *opram, uint32_t options) override;

	address_space_config m_program_config;

	static const uint32_t SHIFT_MASK[33];


	uint32_t m_pc;
	uint32_t m_fetchpc;
	union
	{
		uint32_t m_reg[32];
		uint64_t m_fpair[16];
	};
	union
	{
		uint64_t m_acc[4];
		double m_facc[4];
	};
	uint32_t m_ir;

	uint32_t m_in0p;
	uint32_t m_in1p;
	uint32_t m_outp;
	uint32_t m_ie;
	uint32_t m_intpen;
	uint32_t m_epc;
	uint32_t m_eip;

	uint32_t m_tcount;
	uint32_t m_tscale;

	uint32_t m_param_ram[0x800];
>>>>>>> upstream/master

	int m_icount;

	address_space *m_program;
	direct_read_data* m_direct;

<<<<<<< HEAD
	void check_interrupts();
	void processor_command(UINT32 command);
	UINT32 fetch();
=======
	write32_delegate m_cmd_callback;

	void check_interrupts();
	void processor_command(uint32_t command);
	uint32_t fetch();
>>>>>>> upstream/master
	void delay_slot();
	void execute();
	void execute_short_imm();
	void execute_reg_long_imm();
<<<<<<< HEAD
	UINT32 read_creg(int reg);
	void write_creg(int reg, UINT32 data);
	bool test_condition(int condition, UINT32 value);
	UINT32 calculate_cmp(UINT32 src1, UINT32 src2);
=======
	uint32_t read_creg(int reg);
	void write_creg(int reg, uint32_t data);
	bool test_condition(int condition, uint32_t value);
	uint32_t calculate_cmp(uint32_t src1, uint32_t src2);
>>>>>>> upstream/master
	void vector_loadstore();
};


// Parallel Processor class
class tms32082_pp_device : public cpu_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	tms32082_pp_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
=======
	tms32082_pp_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
>>>>>>> upstream/master

	enum
	{
		PP_PC = 1
	};

protected:
	// device level overrides
<<<<<<< HEAD
	virtual void device_start();
	virtual void device_reset();

	// device_execute_interface overrides
	virtual UINT32 execute_min_cycles() const { return 1; }
	virtual UINT32 execute_max_cycles() const { return 1; }
	virtual UINT32 execute_input_lines() const { return 0; }
	virtual void execute_run();

	// device_memory_interface overrides
	virtual const address_space_config *memory_space_config(address_spacenum spacenum = AS_0) const
	{
		switch (spacenum)
		{
			case AS_PROGRAM: return &m_program_config;
			default:         return NULL;
		}
	}

	// device_state_interface overrides
	void state_string_export(const device_state_entry &entry, std::string &str);

	// device_disasm_interface overrides
	virtual UINT32 disasm_min_opcode_bytes() const { return 8; }
	virtual UINT32 disasm_max_opcode_bytes() const { return 8; }
	virtual offs_t disasm_disassemble(char *buffer, offs_t pc, const UINT8 *oprom, const UINT8 *opram, UINT32 options);

	address_space_config m_program_config;

	UINT32 m_pc;
	UINT32 m_fetchpc;
=======
	virtual void device_start() override;
	virtual void device_reset() override;

	// device_execute_interface overrides
	virtual uint32_t execute_min_cycles() const override { return 1; }
	virtual uint32_t execute_max_cycles() const override { return 1; }
	virtual uint32_t execute_input_lines() const override { return 0; }
	virtual void execute_run() override;

	// device_memory_interface overrides
	virtual space_config_vector memory_space_config() const override;

	// device_state_interface overrides
	virtual void state_string_export(const device_state_entry &entry, std::string &str) const override;

	// device_disasm_interface overrides
	virtual uint32_t disasm_min_opcode_bytes() const override { return 8; }
	virtual uint32_t disasm_max_opcode_bytes() const override { return 8; }
	virtual offs_t disasm_disassemble(std::ostream &stream, offs_t pc, const uint8_t *oprom, const uint8_t *opram, uint32_t options) override;

	address_space_config m_program_config;

	uint32_t m_pc;
	uint32_t m_fetchpc;
>>>>>>> upstream/master

	int m_icount;

	address_space *m_program;
	direct_read_data* m_direct;
};


<<<<<<< HEAD
extern const device_type TMS32082_MP;
extern const device_type TMS32082_PP;


#endif /* __TMS32082_H__ */
=======
DECLARE_DEVICE_TYPE(TMS32082_MP, tms32082_mp_device)
DECLARE_DEVICE_TYPE(TMS32082_PP, tms32082_pp_device)


#endif // MAME_CPU_TMS32082_TMS32082_H
>>>>>>> upstream/master
