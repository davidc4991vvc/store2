// license:BSD-3-Clause
// copyright-holders:Aaron Giles
/*** m6805: Portable 6805 emulator ******************************************/
<<<<<<< HEAD

#pragma once

#ifndef __M6805_H__
#define __M6805_H__
=======
#ifndef MAME_CPU_M6805_M6805_H
#define MAME_CPU_M6805_M6805_H

#pragma once

>>>>>>> upstream/master

//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

<<<<<<< HEAD
class m6805_device;

// device type definition
extern const device_type M6805;
extern const device_type M68HC05EG;
extern const device_type M68705;
extern const device_type HD63705;
=======
// device type definition
DECLARE_DEVICE_TYPE(M6805,     m6805_device)
DECLARE_DEVICE_TYPE(M68HC05EG, m68hc05eg_device)
DECLARE_DEVICE_TYPE(HD63705,   hd63705_device)
>>>>>>> upstream/master

// ======================> m6805_base_device

// Used by core CPU interface
class m6805_base_device : public cpu_device
{
<<<<<<< HEAD
public:
	// construction/destruction
	m6805_base_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock, const device_type type, const char *name, UINT32 addr_width, const char *shortname, const char *source);

protected:
	// device-level overrides
	virtual void device_start();
	virtual void device_reset();

	// device_execute_interface overrides
	virtual UINT32 execute_min_cycles() const;
	virtual UINT32 execute_max_cycles() const;
	virtual UINT32 execute_input_lines() const;
	virtual void execute_run();
	virtual void execute_set_input(int inputnum, int state) = 0;
	virtual UINT64 execute_clocks_to_cycles(UINT64 clocks) const;
	virtual UINT64 execute_cycles_to_clocks(UINT64 cycles) const;

	// device_memory_interface overrides
	virtual const address_space_config *memory_space_config(address_spacenum spacenum = AS_0) const;

	// device_disasm_interface overrides
	virtual UINT32 disasm_min_opcode_bytes() const;
	virtual UINT32 disasm_max_opcode_bytes() const;
	virtual offs_t disasm_disassemble(char *buffer, offs_t pc, const UINT8 *oprom, const UINT8 *opram, UINT32 options);

	// device_state_interface overrides
	virtual void state_string_export(const device_state_entry &entry, std::string &str);

private:
	// opcode/condition tables
	static const UINT8 m_flags8i[256];
	static const UINT8 m_flags8d[256];
	static const UINT8 m_cycles1[256];

protected:
	void rd_s_handler_b(UINT8 *b);
	void rd_s_handler_w(PAIR *p);
	void wr_s_handler_b(UINT8 *b);
	void wr_s_handler_w(PAIR *p);
	void RM16(UINT32 addr, PAIR *p);

	void brset(UINT8 bit);
	void brclr(UINT8 bit);
	void bset(UINT8 bit);
	void bclr(UINT8 bit);

	void bra();
	void brn();
	void bhi();
	void bls();
	void bcc();
	void bcs();
	void bne();
	void beq();
	void bhcc();
	void bhcs();
	void bpl();
	void bmi();
	void bmc();
	void bms();
	virtual void bil();
	virtual void bih();
	void bsr();

	void neg_di();
	void com_di();
	void lsr_di();
	void ror_di();
	void asr_di();
	void lsl_di();
	void rol_di();
	void dec_di();
	void inc_di();
	void tst_di();
	void clr_di();

	void nega();
=======
protected:
	// addressing mode selector for opcode handler templates
	enum class addr_mode { IM, DI, EX, IX, IX1, IX2 };

	// state index constants
	enum
	{
		M6805_PC = 1,
		M6805_S,
		M6805_CC,
		M6805_A,
		M6805_X,
		M6805_IRQ_STATE
	};

	// CC masks      H INZC
	//            7654 3210
	enum
	{
		CFLAG = 0x01,
		ZFLAG = 0x02,
		NFLAG = 0x04,
		IFLAG = 0x08,
		HFLAG = 0x10
	};

	typedef void (m6805_base_device::*op_handler_func)();
	typedef op_handler_func const op_handler_table[256];
	typedef u8 const cycle_count_table[256];

	struct configuration_params
	{
		configuration_params(
				op_handler_table &ops,
				cycle_count_table &cycles,
				u32 addr_width,
				u32 sp_mask,
				u32 sp_floor,
				u16 swi_vector)
			: m_ops(ops)
			, m_cycles(cycles)
			, m_addr_width(addr_width)
			, m_sp_mask(sp_mask)
			, m_sp_floor(sp_floor)
			, m_swi_vector(swi_vector)
		{
		}

		op_handler_table &m_ops;
		cycle_count_table &m_cycles;
		u32 m_addr_width;
		u32 m_sp_mask;
		u32 m_sp_floor;
		u16 m_swi_vector;
	};

	// opcode tables
	static op_handler_table s_hmos_ops;
	static op_handler_table s_cmos_ops;
	static op_handler_table s_hc_ops;
	static cycle_count_table s_hmos_cycles;
	static cycle_count_table s_cmos_cycles;
	static cycle_count_table s_hc_cycles;

	// construction/destruction
	m6805_base_device(
			machine_config const &mconfig,
			char const *tag,
			device_t *owner,
			uint32_t clock,
			device_type const type,
			configuration_params const &params);
	m6805_base_device(
			machine_config const &mconfig,
			char const *tag,
			device_t *owner,
			uint32_t clock,
			device_type const type,
			configuration_params const &params,
			address_map_delegate internal_map);

	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;

	// device_execute_interface overrides
	virtual uint32_t execute_min_cycles() const override;
	virtual uint32_t execute_max_cycles() const override;
	virtual uint32_t execute_input_lines() const override;
	virtual void execute_run() override;
	virtual void execute_set_input(int inputnum, int state) override;
	virtual uint64_t execute_clocks_to_cycles(uint64_t clocks) const override;
	virtual uint64_t execute_cycles_to_clocks(uint64_t cycles) const override;

	// device_memory_interface overrides
	virtual space_config_vector memory_space_config() const override;

	// device_disasm_interface overrides
	virtual uint32_t disasm_min_opcode_bytes() const override;
	virtual uint32_t disasm_max_opcode_bytes() const override;
	virtual offs_t disasm_disassemble(std::ostream &stream, offs_t pc, const uint8_t *oprom, const uint8_t *opram, uint32_t options) override;

	// device_state_interface overrides
	virtual void state_string_export(const device_state_entry &entry, std::string &str) const override;

	// for devices with timing-sensitive peripherals
	virtual void burn_cycles(unsigned count) { }

	void clr_nz()   { m_cc &= ~(NFLAG | ZFLAG); }
	void clr_nzc()  { m_cc &= ~(NFLAG | ZFLAG | CFLAG); }
	void clr_hc()   { m_cc &= ~(HFLAG | CFLAG); }
	void clr_hnzc() { m_cc &= ~(HFLAG | NFLAG | ZFLAG | CFLAG); }

	// macros for CC -- CC bits affected should be reset before calling
	void set_z8(u8 a)                       { if (!a) m_cc |= ZFLAG; }
	void set_n8(u8 a)                       { m_cc |= (a & 0x80) >> 5; }
	void set_h(u8 a, u8 b, u8 r)            { m_cc |= (a ^ b ^ r) & 0x10; }
	void set_c8(u16 a)                      { m_cc |= BIT(a, 8); }

	// combos
	void set_nz8(u8 a)                      { set_n8(a); set_z8(a); }
	void set_nzc8(u16 a)                    { set_nz8(a); set_c8(a); }
	void set_hnzc8(u8 a, u8 b, u16 r)       { set_h(a, b, r); set_nzc8(r); }

	unsigned    rdmem(u32 addr)             { return unsigned(m_program->read_byte(addr)); }
	void        wrmem(u32 addr, u8 value)   { m_program->write_byte(addr, value); }
	unsigned    rdop(u32 addr)              { return unsigned(m_direct->read_byte(addr)); }
	unsigned    rdop_arg(u32 addr)          { return unsigned(m_direct->read_byte(addr)); }

	unsigned    rm(u32 addr)                { return rdmem(addr); }
	void        rm16(u32 addr, PAIR &p);
	void        wm(u32 addr, u8 value)      { wrmem(addr, value); }

	void        pushbyte(u8 b);
	void        pushword(PAIR const &p);
	void        pullbyte(u8 &b);
	void        pullword(PAIR &p);

	template <typename T> void immbyte(T &b);
	void immword(PAIR &w);
	void skipbyte();

	template <unsigned B> void brset();
	template <unsigned B> void brclr();
	template <unsigned B> void bset();
	template <unsigned B> void bclr();

	template <bool C> void bra();
	template <bool C> void bhi();
	template <bool C> void bcc();
	template <bool C> void bne();
	template <bool C> void bhcc();
	template <bool C> void bpl();
	template <bool C> void bmc();
	template <bool C> void bil();
	void bsr();

	template <addr_mode M> void neg();
	template <addr_mode M> void com();
	template <addr_mode M> void lsr();
	template <addr_mode M> void ror();
	template <addr_mode M> void asr();
	template <addr_mode M> void lsl();
	template <addr_mode M> void rol();
	template <addr_mode M> void dec();
	template <addr_mode M> void inc();
	template <addr_mode M> void tst();
	template <addr_mode M> void clr();

	void nega();
	void mul();
>>>>>>> upstream/master
	void coma();
	void lsra();
	void rora();
	void asra();
	void lsla();
	void rola();
	void deca();
	void inca();
	void tsta();
	void clra();

	void negx();
	void comx();
	void lsrx();
	void rorx();
	void asrx();
<<<<<<< HEAD
	void aslx();
=======
>>>>>>> upstream/master
	void lslx();
	void rolx();
	void decx();
	void incx();
	void tstx();
	void clrx();

<<<<<<< HEAD
	void neg_ix1();
	void com_ix1();
	void lsr_ix1();
	void ror_ix1();
	void asr_ix1();
	void lsl_ix1();
	void rol_ix1();
	void dec_ix1();
	void inc_ix1();
	void tst_ix1();
	void clr_ix1();

	void neg_ix();
	void com_ix();
	void lsr_ix();
	void ror_ix();
	void asr_ix();
	void lsl_ix();
	void rol_ix();
	void dec_ix();
	void inc_ix();
	void tst_ix();
	void clr_ix();

	void rti();
	void rts();
	virtual void swi();
=======
	void rti();
	void rts();
	void swi();
	void stop();
	void wait();
>>>>>>> upstream/master

	void tax();
	void txa();

<<<<<<< HEAD
	void rsp();
	void nop();

	void suba_im();
	void cmpa_im();
	void sbca_im();
	void cpx_im();
	void anda_im();
	void bita_im();
	void lda_im();
	void eora_im();
	void adca_im();
	void ora_im();
	void adda_im();

	void ldx_im();
	void suba_di();
	void cmpa_di();
	void sbca_di();
	void cpx_di();
	void anda_di();
	void bita_di();
	void lda_di();
	void sta_di();
	void eora_di();
	void adca_di();
	void ora_di();
	void adda_di();
	void jmp_di();
	void jsr_di();
	void ldx_di();
	void stx_di();
	void suba_ex();
	void cmpa_ex();
	void sbca_ex();
	void cpx_ex();
	void anda_ex();
	void bita_ex();
	void lda_ex();
	void sta_ex();
	void eora_ex();
	void adca_ex();
	void ora_ex();
	void adda_ex();
	void jmp_ex();
	void jsr_ex();
	void ldx_ex();
	void stx_ex();
	void suba_ix2();
	void cmpa_ix2();
	void sbca_ix2();
	void cpx_ix2();
	void anda_ix2();
	void bita_ix2();
	void lda_ix2();
	void sta_ix2();
	void eora_ix2();
	void adca_ix2();
	void ora_ix2();
	void adda_ix2();
	void jmp_ix2();
	void jsr_ix2();
	void ldx_ix2();
	void stx_ix2();
	void suba_ix1();
	void cmpa_ix1();
	void sbca_ix1();
	void cpx_ix1();
	void anda_ix1();
	void bita_ix1();
	void lda_ix1();
	void sta_ix1();
	void eora_ix1();
	void adca_ix1();
	void ora_ix1();
	void adda_ix1();
	void jmp_ix1();
	void jsr_ix1();
	void ldx_ix1();
	void stx_ix1();
	void suba_ix();
	void cmpa_ix();
	void sbca_ix();
	void cpx_ix();
	void anda_ix();
	void bita_ix();
	void lda_ix();
	void sta_ix();
	void eora_ix();
	void adca_ix();
	void ora_ix();
	void adda_ix();
	void jmp_ix();
	void jsr_ix();
	void ldx_ix();
	void stx_ix();
=======
	void clc();
	void sec();
	void cli();
	void sei();

	void rsp();
	void nop();

	template <addr_mode M> void suba();
	template <addr_mode M> void cmpa();
	template <addr_mode M> void sbca();
	template <addr_mode M> void cpx();
	template <addr_mode M> void anda();
	template <addr_mode M> void bita();
	template <addr_mode M> void lda();
	template <addr_mode M> void sta();
	template <addr_mode M> void eora();
	template <addr_mode M> void adca();
	template <addr_mode M> void ora();
	template <addr_mode M> void adda();
	template <addr_mode M> void jmp();
	template <addr_mode M> void jsr();
	template <addr_mode M> void ldx();
	template <addr_mode M> void stx();
>>>>>>> upstream/master

	void illegal();

	virtual void interrupt();
	virtual void interrupt_vector();
<<<<<<< HEAD

	const char *m_tag;

	// address spaces
	const address_space_config m_program_config;

	// CPU registers
	PAIR    m_ea;           /* effective address */

	UINT32  m_sp_mask;      /* Stack pointer address mask */
	UINT32  m_sp_low;       /* Stack pointer low water mark (or floor) */
	PAIR    m_pc;           /* Program counter */
	PAIR    m_s;            /* Stack pointer */
	UINT8   m_a;            /* Accumulator */
	UINT8   m_x;            /* Index register */
	UINT8   m_cc;           /* Condition codes */

	UINT16  m_pending_interrupts; /* MB */
=======
	virtual bool test_il();

	configuration_params const m_params;

	// address spaces
	address_space_config const m_program_config;

	// CPU registers
	PAIR    m_ea;           // effective address (should really be a temporary in opcode handlers)

	PAIR    m_pc;           // Program counter
	PAIR    m_s;            // Stack pointer
	u8      m_a;            // Accumulator
	u8      m_x;            // Index register
	u8      m_cc;           // Condition codes

	uint16_t  m_pending_interrupts; /* MB */
>>>>>>> upstream/master

	int     m_irq_state[9]; /* KW Additional lines for HD63705 */
	int     m_nmi_state;

	// other internal states
	int     m_icount;

	// address spaces
	address_space *m_program;
	direct_read_data *m_direct;
};

<<<<<<< HEAD
=======

>>>>>>> upstream/master
// ======================> m6805_device

class m6805_device : public m6805_base_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	m6805_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock)
		: m6805_base_device(mconfig, tag, owner, clock, M6805, "M6805", 12, "m6805", __FILE__) { }

protected:
	virtual void execute_set_input(int inputnum, int state);
};

=======
	m6805_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
};


>>>>>>> upstream/master
// ======================> m68hc05eg_device

class m68hc05eg_device : public m6805_base_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	m68hc05eg_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock)
		: m6805_base_device(mconfig, tag, owner, clock, M68HC05EG, "M68HC05EG", 13, "m68hc05eg", __FILE__) { }

protected:
	// device-level overrides
	virtual void device_reset();

	virtual void execute_set_input(int inputnum, int state);

	virtual void interrupt_vector();
};

// ======================> m68705_device

class m68705_device : public m6805_base_device
{
public:
	// construction/destruction
	m68705_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock)
		: m6805_base_device(mconfig, tag, owner, clock, M68705, "M68705", 12, "m68705", __FILE__) { }

protected:
	// device-level overrides
	virtual void device_reset();

	virtual void execute_set_input(int inputnum, int state);

	virtual void interrupt();
=======
	m68hc05eg_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

protected:
	// device-level overrides
	virtual void device_reset() override;

	virtual void interrupt_vector() override;
>>>>>>> upstream/master
};

// ======================> hd63705_device

class hd63705_device : public m6805_base_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	hd63705_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock)
		: m6805_base_device(mconfig, tag, owner, clock, HD63705, "HD63705", 16, "hd63705", __FILE__) { }

protected:
	// device-level overrides
	virtual void device_reset();

	virtual void execute_set_input(int inputnum, int state);

	virtual void interrupt_vector();

	// opcodes
	virtual void bil();
	virtual void bih();
	virtual void swi();
};

enum { M6805_PC=1, M6805_S, M6805_CC, M6805_A, M6805_X, M6805_IRQ_STATE };

=======
	hd63705_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

protected:
	// device-level overrides
	virtual void device_reset() override;

	virtual void execute_set_input(int inputnum, int state) override;

	virtual void interrupt_vector() override;
	virtual bool test_il() override { return m_nmi_state != CLEAR_LINE; }
};

>>>>>>> upstream/master
#define M6805_IRQ_LINE      0

/****************************************************************************
 * 68HC05EG section
 ****************************************************************************/

#define M68HC05EG_INT_IRQ   (M6805_IRQ_LINE)
#define M68HC05EG_INT_TIMER (M6805_IRQ_LINE+1)
#define M68HC05EG_INT_CPI   (M6805_IRQ_LINE+2)

/****************************************************************************
<<<<<<< HEAD
 * 68705 section
 ****************************************************************************/

#define M68705_A                    M6805_A
#define M68705_PC                   M6805_PC
#define M68705_S                    M6805_S
#define M68705_X                    M6805_X
#define M68705_CC                   M6805_CC
#define M68705_IRQ_STATE            M6805_IRQ_STATE

#define M68705_INT_MASK             0x03
#define M68705_IRQ_LINE             M6805_IRQ_LINE
#define M68705_INT_TIMER            0x01

/****************************************************************************
=======
>>>>>>> upstream/master
 * HD63705 section
 ****************************************************************************/

#define HD63705_A                   M6805_A
#define HD63705_PC                  M6805_PC
#define HD63705_S                   M6805_S
#define HD63705_X                   M6805_X
#define HD63705_CC                  M6805_CC
#define HD63705_NMI_STATE           M6805_IRQ_STATE
#define HD63705_IRQ1_STATE          M6805_IRQ_STATE+1
#define HD63705_IRQ2_STATE          M6805_IRQ_STATE+2
#define HD63705_ADCONV_STATE        M6805_IRQ_STATE+3

#define HD63705_INT_MASK            0x1ff

#define HD63705_INT_IRQ1            0x00
#define HD63705_INT_IRQ2            0x01
#define HD63705_INT_TIMER1          0x02
#define HD63705_INT_TIMER2          0x03
#define HD63705_INT_TIMER3          0x04
#define HD63705_INT_PCI             0x05
#define HD63705_INT_SCI             0x06
#define HD63705_INT_ADCONV          0x07
#define HD63705_INT_NMI             0x08

CPU_DISASSEMBLE( m6805 );
<<<<<<< HEAD

#endif /* __M6805_H__ */
=======
CPU_DISASSEMBLE( m146805 );
CPU_DISASSEMBLE( m68hc05 );

#endif // MAME_CPU_M6805_M6805_H
>>>>>>> upstream/master
