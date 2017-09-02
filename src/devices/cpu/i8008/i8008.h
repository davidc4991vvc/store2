// license:BSD-3-Clause
// copyright-holders:Miodrag Milanovic
<<<<<<< HEAD
#ifndef __I8008_H__
#define __I8008_H__

//**************************************************************************
//  ENUMERATIONS
//**************************************************************************

enum
{
	I8008_PC,
	I8008_A,I8008_B,I8008_C,I8008_D,I8008_E,I8008_H,I8008_L,
	I8008_ADDR1,I8008_ADDR2,I8008_ADDR3,I8008_ADDR4,I8008_ADDR5,I8008_ADDR6,I8008_ADDR7,I8008_ADDR8,

	I8008_GENPC = STATE_GENPC,
	I8008_GENSP = STATE_GENSP,
	I8008_GENPCBASE = STATE_GENPCBASE
};
=======
#ifndef MAME_CPU_I8008_I8008_H
#define MAME_CPU_I8008_I8008_H

#pragma once
>>>>>>> upstream/master

//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

<<<<<<< HEAD
class i8008_device;

=======
>>>>>>> upstream/master
// ======================> asap_device
class i8008_device : public cpu_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	i8008_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

protected:
	// device-level overrides
	virtual void device_start();
	virtual void device_reset();

	// device_execute_interface overrides
	virtual UINT32 execute_min_cycles() const;
	virtual UINT32 execute_max_cycles() const;
	virtual void execute_run();
	virtual void execute_set_input(int inputnum, int state);

	// device_memory_interface overrides
	virtual const address_space_config *memory_space_config(address_spacenum spacenum = AS_0) const;

	// device_state_interface overrides
	virtual void state_import(const device_state_entry &entry);
	virtual void state_export(const device_state_entry &entry);
	virtual void state_string_export(const device_state_entry &entry, std::string &str);


	// device_disasm_interface overrides
	virtual UINT32 disasm_min_opcode_bytes() const;
	virtual UINT32 disasm_max_opcode_bytes() const;
	virtual offs_t disasm_disassemble(char *buffer, offs_t pc, const UINT8 *oprom, const UINT8 *opram, UINT32 options);
=======
	i8008_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

protected:
	enum
	{
		I8008_PC,
		I8008_A,I8008_B,I8008_C,I8008_D,I8008_E,I8008_H,I8008_L,
		I8008_ADDR1,I8008_ADDR2,I8008_ADDR3,I8008_ADDR4,I8008_ADDR5,I8008_ADDR6,I8008_ADDR7,I8008_ADDR8
	};

	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;

	// device_execute_interface overrides
	virtual uint32_t execute_min_cycles() const override;
	virtual uint32_t execute_max_cycles() const override;
	virtual void execute_run() override;
	virtual void execute_set_input(int inputnum, int state) override;

	// device_memory_interface overrides
	virtual space_config_vector memory_space_config() const override;

	// device_state_interface overrides
	virtual void state_import(const device_state_entry &entry) override;
	virtual void state_export(const device_state_entry &entry) override;
	virtual void state_string_export(const device_state_entry &entry, std::string &str) const override;


	// device_disasm_interface overrides
	virtual uint32_t disasm_min_opcode_bytes() const override;
	virtual uint32_t disasm_max_opcode_bytes() const override;
	virtual offs_t disasm_disassemble(std::ostream &stream, offs_t pc, const uint8_t *oprom, const uint8_t *opram, uint32_t options) override;
>>>>>>> upstream/master

	virtual void execute_one(int opcode);

	void push_stack();
	void pop_stack();
<<<<<<< HEAD
	UINT8 rop();
	UINT8 get_reg(UINT8 reg);
	void set_reg(UINT8 reg, UINT8 val);
	UINT8 arg();
	void update_flags(UINT8 val);
	UINT8 do_condition(UINT8 val);
	UINT16 get_addr();
	void illegal(UINT8 opcode);
	void take_interrupt();
	void init_tables(void);

	int m_pc_pos; // PC possition in ADDR
=======
	uint8_t rop();
	uint8_t get_reg(uint8_t reg);
	void set_reg(uint8_t reg, uint8_t val);
	uint8_t arg();
	void update_flags(uint8_t val);
	uint8_t do_condition(uint8_t val);
	uint16_t get_addr();
	void illegal(uint8_t opcode);
	void take_interrupt();
	void init_tables(void);

	int m_pc_pos; // PC position in ADDR
>>>>>>> upstream/master
	int m_icount;

	// configuration
	const address_space_config      m_program_config;
	const address_space_config      m_io_config;

<<<<<<< HEAD
	UINT8   m_A,m_B,m_C,m_D,m_E,m_H,m_L;
	PAIR    m_PC; // It is in fact one of ADDR regs
	PAIR    m_ADDR[8]; // Address registers
	UINT8   m_CF; // Carry flag
	UINT8   m_ZF; // Zero flag
	UINT8   m_SF; // Sign flag
	UINT8   m_PF; // Parity flag
	UINT8   m_HALT;
	UINT8   m_flags; // temporary I/O only

	UINT8   m_irq_state;

	UINT8 m_PARITY[256];
=======
	uint8_t   m_A,m_B,m_C,m_D,m_E,m_H,m_L;
	PAIR    m_PC; // It is in fact one of ADDR regs
	PAIR    m_ADDR[8]; // Address registers
	uint8_t   m_CF; // Carry flag
	uint8_t   m_ZF; // Zero flag
	uint8_t   m_SF; // Sign flag
	uint8_t   m_PF; // Parity flag
	uint8_t   m_HALT;
	uint8_t   m_flags; // temporary I/O only

	uint8_t   m_irq_state;

	uint8_t m_PARITY[256];
>>>>>>> upstream/master

	address_space *m_program;
	address_space *m_io;
	direct_read_data *m_direct;
};

// device type definition
<<<<<<< HEAD
extern const device_type I8008;

#endif
=======
DECLARE_DEVICE_TYPE(I8008, i8008_device)

#endif // MAME_CPU_I8008_I8008_H
>>>>>>> upstream/master
