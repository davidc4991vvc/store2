// license:BSD-3-Clause
// copyright-holders:F. Ulivi
//
// *****************************************
// Emulator for HP "hybrid" processor series
// *****************************************
//
// The HP hybrid processor series is composed of a few different models with different
// capabilities. The series was derived from HP's own 2116 processor by translating a
// discrete implementation of the 1960s into a multi-chip module (hence the "hybrid" name).
<<<<<<< HEAD
// This emulator currently supports the 5061-3011 version only.
=======
// This emulator currently supports both the 5061-3001 & the 5061-3011 versions.
>>>>>>> upstream/master
//
// For this emulator I mainly relied on these sources:
// - http://www.hp9845.net/ website
// - HP manual "Assembly development ROM manual for the HP9845": this is the most precious
//   and "enabling" resource of all
// - US Patent 4,180,854 describing the HP9845 system
<<<<<<< HEAD
// - Study of disassembly of firmware of HP64000 system
// - A lot of "educated" guessing

#ifndef _HPHYBRID_H_
#define _HPHYBRID_H_
=======
// - Study of disassembly of firmware of HP64000 & HP9845 systems
// - hp9800e emulator for inspiration on implementing EMC instructions
// - A lot of "educated" guessing

#ifndef MAME_CPU_HPHYBRID_HPHYBRID_H
#define MAME_CPU_HPHYBRID_HPHYBRID_H

#pragma once
>>>>>>> upstream/master

// Input lines
#define HPHYBRID_IRH    0       // High-level interrupt
#define HPHYBRID_IRL    1       // Low-level interrupt
#define HPHYBRID_INT_LVLS   2   // Levels of interrupt

<<<<<<< HEAD
#define HPHYBRID_DMAR   2       // DMA request
#define HPHYBRID_HALT   3       // "Halt" input
#define HPHYBRID_STS    4       // "Status" input
#define HPHYBRID_FLG    5       // "Flag" input

=======
>>>>>>> upstream/master
// I/O addressing space (16-bit wide)
// Addresses into this space are composed as follows:
// b[5..2] = Peripheral address 0..15
// b[1..0] = Register address (IC) 0..3
#define HP_IOADDR_PA_SHIFT      2
#define HP_IOADDR_IC_SHIFT      0

// Compose an I/O address from PA & IC
#define HP_MAKE_IOADDR(pa , ic)    (((pa) << HP_IOADDR_PA_SHIFT) | ((ic) << HP_IOADDR_IC_SHIFT))

<<<<<<< HEAD
// Addresses of memory mapped registers
#define HP_REG_A_ADDR   0x0000
#define HP_REG_B_ADDR   0x0001
#define HP_REG_P_ADDR   0x0002
#define HP_REG_R_ADDR   0x0003
#define HP_REG_R4_ADDR  0x0004
#define HP_REG_R5_ADDR  0x0005
#define HP_REG_R6_ADDR  0x0006
#define HP_REG_R7_ADDR  0x0007
#define HP_REG_IV_ADDR  0x0008
#define HP_REG_PA_ADDR  0x0009
#define HP_REG_DMAPA_ADDR       0x000B
#define HP_REG_DMAMA_ADDR       0x000C
#define HP_REG_DMAC_ADDR        0x000D
#define HP_REG_C_ADDR   0x000e
#define HP_REG_D_ADDR   0x000f
#define HP_REG_LAST_ADDR        0x001f

#define HP_REG_IV_MASK  0xfff0
#define HP_REG_PA_MASK  0x000f
=======
// Set boot mode of 5061-3001: either normal (false) or as in HP9845 system (true)
#define MCFG_HPHYBRID_SET_9845_BOOT(_mode) \
	hp_5061_3001_cpu_device::set_boot_mode_static(*device, _mode);

// PA changed callback
#define MCFG_HPHYBRID_PA_CHANGED(_devcb) \
	devcb = &hp_hybrid_cpu_device::set_pa_changed_func(*device , DEVCB_##_devcb);
>>>>>>> upstream/master

class hp_hybrid_cpu_device : public cpu_device
{
public:
<<<<<<< HEAD
		DECLARE_WRITE_LINE_MEMBER(dmar_w);

protected:
		hp_hybrid_cpu_device(const machine_config &mconfig, device_type type, const char *name, const char *tag, device_t *owner, UINT32 clock, const char *shortname);

		// device-level overrides
		virtual void device_start();
		virtual void device_reset();

		// device_execute_interface overrides
		virtual UINT32 execute_min_cycles() const { return 6; }
		virtual UINT32 execute_max_cycles() const { return 25; }
		virtual UINT32 execute_input_lines() const { return 2; }
		virtual UINT32 execute_default_irq_vector() const { return 0xffff; }
		virtual void execute_run();
		virtual void execute_set_input(int inputnum, int state);

		UINT16 execute_one(UINT16 opcode);
		UINT16 execute_one_sub(UINT16 opcode);

		// device_memory_interface overrides
		virtual const address_space_config *memory_space_config(address_spacenum spacenum = AS_0) const { return (spacenum == AS_PROGRAM) ? &m_program_config : ( (spacenum == AS_IO) ? &m_io_config : NULL ); }

		// device_state_interface overrides
		void state_string_export(const device_state_entry &entry, std::string &str);

		// device_disasm_interface overrides
		virtual UINT32 disasm_min_opcode_bytes() const { return 2; }
		virtual UINT32 disasm_max_opcode_bytes() const { return 2; }
		virtual offs_t disasm_disassemble(char *buffer, offs_t pc, const UINT8 *oprom, const UINT8 *opram, UINT32 options);

private:
		address_space_config m_program_config;
		address_space_config m_io_config;

		address_space *m_program;
		direct_read_data *m_direct;
		address_space *m_io;
		int m_icount;

		// State of processor
		UINT16 m_reg_A;     // Register A
		UINT16 m_reg_B;     // Register B
		UINT16 m_reg_P;     // Register P
		UINT16 m_reg_R;     // Register R
		UINT16 m_reg_C;     // Register C
		UINT16 m_reg_D;     // Register D
		UINT16 m_reg_IV;    // Register IV
		UINT8  m_reg_PA[ HPHYBRID_INT_LVLS + 1 ];   // Stack of register PA (4 bit-long)
		UINT16 m_flags;     // Flags (carry, overflow, cb, db, int en, dma en, dma dir)
		UINT8  m_dmapa;     // DMA peripheral address (4 bits)
		UINT16 m_dmama;     // DMA address
		UINT16 m_dmac;      // DMA counter
		UINT16 m_reg_I;     // Instruction register

		UINT16 get_ea(UINT16 opcode);
		void do_add(UINT16& addend1 , UINT16 addend2);
		UINT16 get_skip_addr(UINT16 opcode , bool condition) const;
		UINT16 get_skip_addr_sc(UINT16 opcode , UINT16& v , unsigned n);
		void do_pw(UINT16 opcode);
		void check_for_interrupts(void);
				void handle_dma(void);

		UINT16 RM(UINT16 addr);
		void   WM(UINT16 addr , UINT16 v);
		void   WMB(UINT32 addr , UINT8 v);
		UINT16 RIO(UINT8 pa , UINT8 ic);
		void   WIO(UINT8 pa , UINT8 ic , UINT16 v);
=======
	DECLARE_WRITE_LINE_MEMBER(dmar_w);
	DECLARE_WRITE_LINE_MEMBER(halt_w);
	DECLARE_WRITE_LINE_MEMBER(status_w);
	DECLARE_WRITE_LINE_MEMBER(flag_w);

	uint8_t pa_r() const;

	template <class Object> static devcb_base &set_pa_changed_func(device_t &device, Object &&cb) { return downcast<hp_hybrid_cpu_device &>(device).m_pa_changed_func.set_callback(std::forward<Object>(cb)); }

protected:
	hp_hybrid_cpu_device(const machine_config &mconfig, device_type type, const char *tag, device_t *owner, uint32_t clock, uint8_t addrwidth);

	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;

	// device_execute_interface overrides
	virtual uint32_t execute_min_cycles() const override { return 6; }
	virtual uint32_t execute_input_lines() const override { return 2; }
	virtual uint32_t execute_default_irq_vector() const  override { return 0xffff; }
	virtual void execute_run() override;
	virtual void execute_set_input(int inputnum, int state) override;

	uint16_t execute_one(uint16_t opcode);
	uint16_t execute_one_sub(uint16_t opcode);
	// Execute an instruction that doesn't belong to either BPC or IOC
	virtual uint16_t execute_no_bpc_ioc(uint16_t opcode) = 0;

	// device_memory_interface overrides
	virtual space_config_vector memory_space_config() const override;

	// device_state_interface overrides
	virtual void state_string_export(const device_state_entry &entry, std::string &str) const override;

	// device_disasm_interface overrides
	virtual uint32_t disasm_min_opcode_bytes() const override { return 2; }
	virtual uint32_t disasm_max_opcode_bytes() const override { return 2; }
	virtual offs_t disasm_disassemble(std::ostream &stream, offs_t pc, const uint8_t *oprom, const uint8_t *opram, uint32_t options) override;

	// Different cases of memory access
	// See patent @ pg 361
	typedef enum {
		AEC_CASE_A,     // Instr. fetches, non-base page fetches of link pointers, BPC direct non-base page accesses
		AEC_CASE_B,     // Base page fetches of link pointers, BPC direct base page accesses
		AEC_CASE_C,     // IOC, EMC & BPC indirect final destination accesses
		AEC_CASE_D      // DMA accesses
	} aec_cases_t;

	// do memory address extension
	virtual uint32_t add_mae(aec_cases_t aec_case , uint16_t addr) = 0;

	uint16_t remove_mae(uint32_t addr);

	uint16_t RM(aec_cases_t aec_case , uint16_t addr);
	uint16_t RM(uint32_t addr);
	virtual uint16_t read_non_common_reg(uint16_t addr) = 0;

	void   WM(aec_cases_t aec_case , uint16_t addr , uint16_t v);
	void   WM(uint32_t addr , uint16_t v);
	virtual void write_non_common_reg(uint16_t addr , uint16_t v) = 0;

	uint16_t fetch();

	uint16_t get_skip_addr(uint16_t opcode , bool condition) const;

	devcb_write8 m_pa_changed_func;

	int m_icount;
	bool m_forced_bsc_25;

	// State of processor
	uint16_t m_reg_A;     // Register A
	uint16_t m_reg_B;     // Register B
	uint16_t m_reg_P;     // Register P
	uint16_t m_reg_R;     // Register R
	uint16_t m_reg_C;     // Register C
	uint16_t m_reg_D;     // Register D
	uint16_t m_reg_IV;    // Register IV
	uint16_t m_reg_W; // Register W
	uint8_t  m_reg_PA[ HPHYBRID_INT_LVLS + 1 ];   // Stack of register PA (4 bit-long)
	uint32_t m_flags;     // Flags
	uint8_t  m_dmapa;     // DMA peripheral address (4 bits)
	uint16_t m_dmama;     // DMA address
	uint16_t m_dmac;      // DMA counter
	uint16_t m_reg_I;     // Instruction register
	uint32_t m_genpc; // Full PC

private:
	address_space_config m_program_config;
	address_space_config m_io_config;

	address_space *m_program;
	direct_read_data *m_direct;
	address_space *m_io;

	uint32_t get_ea(uint16_t opcode);
	void do_add(uint16_t& addend1 , uint16_t addend2);
	uint16_t get_skip_addr_sc(uint16_t opcode , uint16_t& v , unsigned n);
	uint16_t get_skip_addr_sc(uint16_t opcode , uint32_t& v , unsigned n);
	void do_pw(uint16_t opcode);
	void check_for_interrupts();
	virtual void enter_isr();
	void handle_dma();

	uint16_t RIO(uint8_t pa , uint8_t ic);
	void   WIO(uint8_t pa , uint8_t ic , uint16_t v);
};

class hp_5061_3001_cpu_device : public hp_hybrid_cpu_device
{
public:
	hp_5061_3001_cpu_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	static void set_boot_mode_static(device_t &device, bool mode) { downcast<hp_5061_3001_cpu_device &>(device).m_boot_mode = mode; }

protected:
	virtual void device_start() override;
	virtual void device_reset() override;
	virtual uint32_t execute_max_cycles() const override { return 237; }       // FMP 15

	static uint8_t do_dec_shift_r(uint8_t d1 , uint64_t& mantissa);
	static uint8_t do_dec_shift_l(uint8_t d12 , uint64_t& mantissa);
	uint64_t get_ar1();
	void set_ar1(uint64_t v);
	uint64_t get_ar2() const;
	void set_ar2(uint64_t v);
	uint64_t do_mrxy(uint64_t ar);
	bool do_dec_add(bool carry_in , uint64_t& a , uint64_t b);
	void do_mpy();

	virtual uint16_t execute_no_bpc_ioc(uint16_t opcode) override;
	virtual offs_t disasm_disassemble(std::ostream &stream, offs_t pc, const uint8_t *oprom, const uint8_t *opram, uint32_t options) override;
	virtual uint32_t add_mae(aec_cases_t aec_case, uint16_t addr) override;
	virtual uint16_t read_non_common_reg(uint16_t addr) override;
	virtual void write_non_common_reg(uint16_t addr , uint16_t v) override;

private:
	bool m_boot_mode;

	// Additional state of processor
	uint16_t m_reg_ar2[ 4 ];  // AR2 register
	uint16_t m_reg_se;        // SE register (4 bits)
	uint16_t m_reg_r25;       // R25 register
	uint16_t m_reg_r26;       // R26 register
	uint16_t m_reg_r27;       // R27 register
	uint16_t m_reg_aec[ 37 - 32 + 1 ];      // AEC registers R32-R37

	virtual void enter_isr() override;
>>>>>>> upstream/master
};

class hp_5061_3011_cpu_device : public hp_hybrid_cpu_device
{
public:
<<<<<<< HEAD
		hp_5061_3011_cpu_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
};

extern const device_type HP_5061_3011;

#endif /* _HPHYBRID_H_ */
=======
	hp_5061_3011_cpu_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

protected:
	virtual uint32_t execute_max_cycles() const override { return 25; }
	virtual uint16_t execute_no_bpc_ioc(uint16_t opcode) override;
	virtual uint32_t add_mae(aec_cases_t aec_case , uint16_t addr) override;
	virtual uint16_t read_non_common_reg(uint16_t addr) override;
	virtual void write_non_common_reg(uint16_t addr , uint16_t v) override;

};

DECLARE_DEVICE_TYPE(HP_5061_3001, hp_5061_3001_cpu_device)
DECLARE_DEVICE_TYPE(HP_5061_3011, hp_5061_3011_cpu_device)

#endif // MAME_CPU_HPHYBRID_HPHYBRID_H
>>>>>>> upstream/master
