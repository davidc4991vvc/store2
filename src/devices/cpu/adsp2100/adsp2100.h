// license:BSD-3-Clause
// copyright-holders:Aaron Giles
/***************************************************************************

    adsp2100.h

    ADSP-21xx series emulator.

***************************************************************************/

<<<<<<< HEAD
#pragma once

#ifndef __ADSP2100_H__
#define __ADSP2100_H__
=======
#ifndef MAME_CPU_ADSP2100_ADSP2100_H
#define MAME_CPU_ADSP2100_ADSP2100_H

#pragma once
>>>>>>> upstream/master


//**************************************************************************
//  DEBUGGING
//**************************************************************************

#define ADSP_TRACK_HOTSPOTS     0



//**************************************************************************
//  CONSTANTS
//**************************************************************************

// ADSP-2100 IRQs
const int ADSP2100_IRQ0         = 0;        // IRQ0
const int ADSP2100_SPORT1_RX    = 0;        // SPORT1 receive IRQ
const int ADSP2100_IRQ1         = 1;        // IRQ1
const int ADSP2100_SPORT1_TX    = 1;        // SPORT1 transmit IRQ
const int ADSP2100_IRQ2         = 2;        // IRQ2
const int ADSP2100_IRQ3         = 3;        // IRQ3

// ADSP-2101 IRQs
const int ADSP2101_IRQ0         = 0;        // IRQ0
const int ADSP2101_SPORT1_RX    = 0;        // SPORT1 receive IRQ
const int ADSP2101_IRQ1         = 1;        // IRQ1
const int ADSP2101_SPORT1_TX    = 1;        // SPORT1 transmit IRQ
const int ADSP2101_IRQ2         = 2;        // IRQ2
const int ADSP2101_SPORT0_RX    = 3;        // SPORT0 receive IRQ
const int ADSP2101_SPORT0_TX    = 4;        // SPORT0 transmit IRQ
const int ADSP2101_TIMER        = 5;        // internal timer IRQ

// ADSP-2104 IRQs
const int ADSP2104_IRQ0         = 0;        // IRQ0
const int ADSP2104_SPORT1_RX    = 0;        // SPORT1 receive IRQ
const int ADSP2104_IRQ1         = 1;        // IRQ1
const int ADSP2104_SPORT1_TX    = 1;        // SPORT1 transmit IRQ
const int ADSP2104_IRQ2         = 2;        // IRQ2
const int ADSP2104_SPORT0_RX    = 3;        // SPORT0 receive IRQ
const int ADSP2104_SPORT0_TX    = 4;        // SPORT0 transmit IRQ
const int ADSP2104_TIMER        = 5;        // internal timer IRQ

// ADSP-2105 IRQs
const int ADSP2105_IRQ0         = 0;        // IRQ0
const int ADSP2105_SPORT1_RX    = 0;        // SPORT1 receive IRQ
const int ADSP2105_IRQ1         = 1;        // IRQ1
const int ADSP2105_SPORT1_TX    = 1;        // SPORT1 transmit IRQ
const int ADSP2105_IRQ2         = 2;        // IRQ2
const int ADSP2105_TIMER        = 5;        // internal timer IRQ

// ADSP-2115 IRQs
const int ADSP2115_IRQ0         = 0;        // IRQ0
const int ADSP2115_SPORT1_RX    = 0;        // SPORT1 receive IRQ
const int ADSP2115_IRQ1         = 1;        // IRQ1
const int ADSP2115_SPORT1_TX    = 1;        // SPORT1 transmit IRQ
const int ADSP2115_IRQ2         = 2;        // IRQ2
const int ADSP2115_SPORT0_RX    = 3;        // SPORT0 receive IRQ
const int ADSP2115_SPORT0_TX    = 4;        // SPORT0 transmit IRQ
const int ADSP2115_TIMER        = 5;        // internal timer IRQ

// ADSP-2181 IRQs
const int ADSP2181_IRQ0         = 0;        // IRQ0
const int ADSP2181_SPORT1_RX    = 0;        // SPORT1 receive IRQ
const int ADSP2181_IRQ1         = 1;        // IRQ1
const int ADSP2181_SPORT1_TX    = 1;        // SPORT1 transmit IRQ
const int ADSP2181_IRQ2         = 2;        // IRQ2
const int ADSP2181_SPORT0_RX    = 3;        // SPORT0 receive IRQ
const int ADSP2181_SPORT0_TX    = 4;        // SPORT0 transmit IRQ
const int ADSP2181_TIMER        = 5;        // internal timer IRQ
const int ADSP2181_IRQE         = 6;        // IRQE
<<<<<<< HEAD
const int ADSP2181_IRQL1        = 7;        // IRQL1
const int ADSP2181_IRQL2        = 8;        // IRQL2
=======
const int ADSP2181_BDMA         = 7;        // BDMA
const int ADSP2181_IRQL1        = 8;        // IRQL1
const int ADSP2181_IRQL0        = 9;        // IRQL0
>>>>>>> upstream/master

// register enumeration
enum
{
<<<<<<< HEAD
	ADSP2100_PC,
	ADSP2100_AX0,
=======
	ADSP2100_PC = STATE_GENPC,
	ADSP2100_AX0 = 0,
>>>>>>> upstream/master
	ADSP2100_AX1,
	ADSP2100_AY0,
	ADSP2100_AY1,
	ADSP2100_AR,
	ADSP2100_AF,
	ADSP2100_MX0,
	ADSP2100_MX1,
	ADSP2100_MY0,
	ADSP2100_MY1,
	ADSP2100_MR0,
	ADSP2100_MR1,
	ADSP2100_MR2,
	ADSP2100_MF,
	ADSP2100_SI,
	ADSP2100_SE,
	ADSP2100_SB,
	ADSP2100_SR0,
	ADSP2100_SR1,
	ADSP2100_I0,
	ADSP2100_I1,
	ADSP2100_I2,
	ADSP2100_I3,
	ADSP2100_I4,
	ADSP2100_I5,
	ADSP2100_I6,
	ADSP2100_I7,
	ADSP2100_L0,
	ADSP2100_L1,
	ADSP2100_L2,
	ADSP2100_L3,
	ADSP2100_L4,
	ADSP2100_L5,
	ADSP2100_L6,
	ADSP2100_L7,
	ADSP2100_M0,
	ADSP2100_M1,
	ADSP2100_M2,
	ADSP2100_M3,
	ADSP2100_M4,
	ADSP2100_M5,
	ADSP2100_M6,
	ADSP2100_M7,
	ADSP2100_PX,
	ADSP2100_CNTR,
	ADSP2100_ASTAT,
	ADSP2100_SSTAT,
	ADSP2100_MSTAT,
	ADSP2100_PCSP,
	ADSP2100_CNTRSP,
	ADSP2100_STATSP,
	ADSP2100_LOOPSP,
	ADSP2100_IMASK,
	ADSP2100_ICNTL,
	ADSP2100_IRQSTATE0,
	ADSP2100_IRQSTATE1,
	ADSP2100_IRQSTATE2,
	ADSP2100_IRQSTATE3,
	ADSP2100_FLAGIN,
	ADSP2100_FLAGOUT,
	ADSP2100_FL0,
	ADSP2100_FL1,
	ADSP2100_FL2,
	ADSP2100_AX0_SEC,
	ADSP2100_AX1_SEC,
	ADSP2100_AY0_SEC,
	ADSP2100_AY1_SEC,
	ADSP2100_AR_SEC,
	ADSP2100_AF_SEC,
	ADSP2100_MX0_SEC,
	ADSP2100_MX1_SEC,
	ADSP2100_MY0_SEC,
	ADSP2100_MY1_SEC,
	ADSP2100_MR0_SEC,
	ADSP2100_MR1_SEC,
	ADSP2100_MR2_SEC,
	ADSP2100_MF_SEC,
	ADSP2100_SI_SEC,
	ADSP2100_SE_SEC,
	ADSP2100_SB_SEC,
	ADSP2100_SR0_SEC,
<<<<<<< HEAD
	ADSP2100_SR1_SEC,

	ADSP2100_GENPC = STATE_GENPC,
	ADSP2100_GENSP = STATE_GENSP,
	ADSP2100_GENPCBASE = STATE_GENPCBASE
=======
	ADSP2100_SR1_SEC
>>>>>>> upstream/master
};



//**************************************************************************
//  INTERFACE CONFIGURATION MACROS
//**************************************************************************

#define MCFG_ADSP21XX_SPORT_RX_CB(_devcb) \
	devcb = &adsp21xx_device::set_sport_rx_callback(*device, DEVCB_##_devcb);

#define MCFG_ADSP21XX_SPORT_TX_CB(_devcb) \
	devcb = &adsp21xx_device::set_sport_tx_callback(*device, DEVCB_##_devcb);

#define MCFG_ADSP21XX_TIMER_FIRED_CB(_devcb) \
	devcb = &adsp21xx_device::set_timer_fired_callback(*device, DEVCB_##_devcb);

<<<<<<< HEAD
=======
#define MCFG_ADSP21XX_DMOVLAY_CB(_devcb) \
	devcb = &adsp21xx_device::set_dmovlay_callback(*device, DEVCB_##_devcb);

>>>>>>> upstream/master
//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

// ======================> adsp21xx_device

class adsp21xx_device : public cpu_device
{
<<<<<<< HEAD
=======
public:
	virtual ~adsp21xx_device();

	// inline configuration helpers
	template <class Object> static devcb_base &set_sport_rx_callback(device_t &device, Object &&cb) { return downcast<adsp21xx_device &>(device).m_sport_rx_cb.set_callback(std::forward<Object>(cb)); }
	template <class Object> static devcb_base &set_sport_tx_callback(device_t &device, Object &&cb) { return downcast<adsp21xx_device &>(device).m_sport_tx_cb.set_callback(std::forward<Object>(cb)); }
	template <class Object> static devcb_base &set_timer_fired_callback(device_t &device, Object &&cb) { return downcast<adsp21xx_device &>(device).m_timer_fired_cb.set_callback(std::forward<Object>(cb)); }
	template <class Object> static devcb_base &set_dmovlay_callback(device_t &device, Object &&cb) { return downcast<adsp21xx_device &>(device).m_dmovlay_cb.set_callback(std::forward<Object>(cb)); }

	// public interfaces
	void load_boot_data(uint8_t *srcdata, uint32_t *dstdata);
	// Returns base address for circular dag
	uint32_t get_ibase(int index) { return m_base[index]; };

>>>>>>> upstream/master
protected:
	enum
	{
		CHIP_TYPE_ADSP2100,
		CHIP_TYPE_ADSP2101,
		CHIP_TYPE_ADSP2104,
		CHIP_TYPE_ADSP2105,
		CHIP_TYPE_ADSP2115,
		CHIP_TYPE_ADSP2181
	};

	// construction/destruction
<<<<<<< HEAD
	adsp21xx_device(const machine_config &mconfig, device_type type, const char *name, const char *tag, device_t *owner, UINT32 clock, UINT32 chiptype, const char *shortname, const char *source);
	virtual ~adsp21xx_device();

public:
	// inline configuration helpers
	template<class _Object> static devcb_base &set_sport_rx_callback(device_t &device, _Object object) { return downcast<adsp21xx_device &>(device).m_sport_rx_cb.set_callback(object); }
	template<class _Object> static devcb_base &set_sport_tx_callback(device_t &device, _Object object) { return downcast<adsp21xx_device &>(device).m_sport_tx_cb.set_callback(object); }
	template<class _Object> static devcb_base &set_timer_fired_callback(device_t &device, _Object object) { return downcast<adsp21xx_device &>(device).m_timer_fired_cb.set_callback(object); }

	// public interfaces
	void load_boot_data(UINT8 *srcdata, UINT32 *dstdata);

protected:
	// device-level overrides
	virtual void device_start();
	virtual void device_reset();

	// device_execute_interface overrides
	virtual UINT32 execute_min_cycles() const;
	virtual UINT32 execute_max_cycles() const;
	virtual void execute_run();
	virtual void execute_set_input(int inputnum, int state);

	// device_state_interface overrides
	virtual void state_import(const device_state_entry &entry);
	virtual void state_string_export(const device_state_entry &entry, std::string &str);

	// device_disasm_interface overrides
	virtual UINT32 disasm_min_opcode_bytes() const;
	virtual UINT32 disasm_max_opcode_bytes() const;
	virtual offs_t disasm_disassemble(char *buffer, offs_t pc, const UINT8 *oprom, const UINT8 *opram, UINT32 options);
=======
	adsp21xx_device(const machine_config &mconfig, device_type type, const char *tag, device_t *owner, uint32_t clock, uint32_t chiptype);

	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;

	// device_execute_interface overrides
	virtual uint32_t execute_min_cycles() const override;
	virtual uint32_t execute_max_cycles() const override;
	virtual void execute_run() override;
	virtual void execute_set_input(int inputnum, int state) override;

	// device_state_interface overrides
	virtual void state_import(const device_state_entry &entry) override;
	virtual void state_string_export(const device_state_entry &entry, std::string &str) const override;

	// device_disasm_interface overrides
	virtual uint32_t disasm_min_opcode_bytes() const override;
	virtual uint32_t disasm_max_opcode_bytes() const override;
	virtual offs_t disasm_disassemble(std::ostream &stream, offs_t pc, const uint8_t *oprom, const uint8_t *opram, uint32_t options) override;
>>>>>>> upstream/master

	// helpers
	void create_tables();
	inline void update_mstat();
<<<<<<< HEAD
	inline UINT32 pc_stack_top();
	inline void set_pc_stack_top(UINT32 top);
	inline void pc_stack_push();
	inline void pc_stack_push_val(UINT32 val);
	inline void pc_stack_pop();
	inline UINT32 pc_stack_pop_val();
	inline UINT32 cntr_stack_top();
	inline void cntr_stack_push();
	inline void cntr_stack_pop();
	inline UINT32 loop_stack_top();
	inline void loop_stack_push(UINT32 value);
=======
	inline uint32_t pc_stack_top();
	inline void set_pc_stack_top(uint32_t top);
	inline void pc_stack_push();
	inline void pc_stack_push_val(uint32_t val);
	inline void pc_stack_pop();
	inline uint32_t pc_stack_pop_val();
	inline uint32_t cntr_stack_top();
	inline void cntr_stack_push();
	inline void cntr_stack_pop();
	inline uint32_t loop_stack_top();
	inline void loop_stack_push(uint32_t value);
>>>>>>> upstream/master
	inline void loop_stack_pop();
	inline void stat_stack_push();
	inline void stat_stack_pop();
//  inline int condition(int c);
	int slow_condition();
<<<<<<< HEAD
	inline void modify_address(UINT32 ireg, UINT32 mreg);
	inline void data_write_dag1(UINT32 op, INT32 val);
	inline UINT32 data_read_dag1(UINT32 op);
	inline void data_write_dag2(UINT32 op, INT32 val);
	inline UINT32 data_read_dag2(UINT32 op);
	inline void pgm_write_dag2(UINT32 op, INT32 val);
	inline UINT32 pgm_read_dag2(UINT32 op);
=======
	inline void modify_address(uint32_t ireg, uint32_t mreg);
	inline void data_write_dag1(uint32_t op, int32_t val);
	inline uint32_t data_read_dag1(uint32_t op);
	inline void data_write_dag2(uint32_t op, int32_t val);
	inline uint32_t data_read_dag2(uint32_t op);
	inline void pgm_write_dag2(uint32_t op, int32_t val);
	inline uint32_t pgm_read_dag2(uint32_t op);
>>>>>>> upstream/master
	void alu_op_ar(int op);
	void alu_op_ar_const(int op);
	void alu_op_af(int op);
	void alu_op_af_const(int op);
	void alu_op_none(int op);
	void mac_op_mr(int op);
	void mac_op_mr_xop(int op);
	void mac_op_mf(int op);
	void mac_op_mf_xop(int op);
	void shift_op(int op);
	void shift_op_imm(int op);

	// memory access
<<<<<<< HEAD
	inline UINT16 data_read(UINT32 addr);
	inline void data_write(UINT32 addr, UINT16 data);
	inline UINT16 io_read(UINT32 addr);
	inline void io_write(UINT32 addr, UINT16 data);
	inline UINT32 program_read(UINT32 addr);
	inline void program_write(UINT32 addr, UINT32 data);
	inline UINT32 opcode_read();
=======
	inline uint16_t data_read(uint32_t addr);
	inline void data_write(uint32_t addr, uint16_t data);
	inline uint16_t io_read(uint32_t addr);
	inline void io_write(uint32_t addr, uint16_t data);
	inline uint32_t program_read(uint32_t addr);
	inline void program_write(uint32_t addr, uint32_t data);
	inline uint32_t opcode_read();
>>>>>>> upstream/master

	// register read/write
	inline void update_i(int which);
	inline void update_l(int which);
<<<<<<< HEAD
	inline void write_reg0(int regnum, INT32 val);
	inline void write_reg1(int regnum, INT32 val);
	inline void write_reg2(int regnum, INT32 val);
	inline void write_reg3(int regnum, INT32 val);
	inline INT32 read_reg0(int regnum);
	inline INT32 read_reg1(int regnum);
	inline INT32 read_reg2(int regnum);
	inline INT32 read_reg3(int regnum);
=======
	inline void write_reg0(int regnum, int32_t val);
	inline void write_reg1(int regnum, int32_t val);
	inline void write_reg2(int regnum, int32_t val);
	inline void write_reg3(int regnum, int32_t val);
	inline int32_t read_reg0(int regnum);
	inline int32_t read_reg1(int regnum);
	inline int32_t read_reg2(int regnum);
	inline int32_t read_reg3(int regnum);
>>>>>>> upstream/master

	// interrupts
	virtual bool generate_irq(int which, int indx = 0) = 0;
	virtual void check_irqs() = 0;

	// internal state
	static const int PC_STACK_DEPTH     = 16;
	static const int CNTR_STACK_DEPTH   = 4;
	static const int STAT_STACK_DEPTH   = 4;
	static const int LOOP_STACK_DEPTH   = 4;

	// 16-bit registers that can be loaded signed or unsigned
	union adsp_reg16
	{
<<<<<<< HEAD
		UINT16  u;
		INT16   s;
=======
		uint16_t  u;
		int16_t   s;
>>>>>>> upstream/master
	};

	// the SHIFT result register is 32 bits
	union adsp_shift
	{
#ifdef LSB_FIRST
		struct { adsp_reg16 sr0, sr1; } srx;
#else
		struct { adsp_reg16 sr1, sr0; } srx;
#endif
<<<<<<< HEAD
		UINT32 sr;
=======
		uint32_t sr;
>>>>>>> upstream/master
	};

	// the MAC result register is 40 bits
	union adsp_mac
	{
#ifdef LSB_FIRST
		struct { adsp_reg16 mr0, mr1, mr2, mrzero; } mrx;
<<<<<<< HEAD
		struct { UINT32 mr0, mr1; } mry;
#else
		struct { adsp_reg16 mrzero, mr2, mr1, mr0; } mrx;
		struct { UINT32 mr1, mr0; } mry;
#endif
		UINT64 mr;
=======
		struct { uint32_t mr0, mr1; } mry;
#else
		struct { adsp_reg16 mrzero, mr2, mr1, mr0; } mrx;
		struct { uint32_t mr1, mr0; } mry;
#endif
		uint64_t mr;
>>>>>>> upstream/master
	};

	// core registers which are replicated
	struct adsp_core
	{
		// ALU registers
		adsp_reg16  ax0, ax1;
		adsp_reg16  ay0, ay1;
		adsp_reg16  ar;
		adsp_reg16  af;

		// MAC registers
		adsp_reg16  mx0, mx1;
		adsp_reg16  my0, my1;
		adsp_mac    mr;
		adsp_reg16  mf;

		// SHIFT registers
		adsp_reg16  si;
		adsp_reg16  se;
		adsp_reg16  sb;
		adsp_shift  sr;

		// dummy registers
		adsp_reg16  zero;
	};

	// configuration
	const address_space_config      m_program_config;
	const address_space_config      m_data_config;
<<<<<<< HEAD
	UINT32                          m_chip_type;

	// other CPU registers
	UINT32              m_pc;
	UINT32              m_ppc;
	UINT32              m_loop;
	UINT32              m_loop_condition;
	UINT32              m_cntr;

	// status registers
	UINT32              m_astat;
	UINT32              m_sstat;
	UINT32              m_mstat;
	UINT32              m_mstat_prev;
	UINT32              m_astat_clear;
	UINT32              m_idle;
=======
	uint32_t                          m_chip_type;

	// other CPU registers
	uint32_t              m_pc;
	uint32_t              m_ppc;
	uint32_t              m_loop;
	uint32_t              m_loop_condition;
	uint32_t              m_cntr;

	// status registers
	uint32_t              m_astat;
	uint32_t              m_sstat;
	uint32_t              m_mstat;
	uint32_t              m_mstat_prev;
	uint32_t              m_astat_clear;
	uint32_t              m_idle;
>>>>>>> upstream/master

	// live set of core registers
	adsp_core           m_core;

	// memory addressing registers
<<<<<<< HEAD
	UINT32              m_i[8];
	INT32               m_m[8];
	UINT32              m_l[8];
	UINT32              m_lmask[8];
	UINT32              m_base[8];
	UINT8               m_px;

	// stacks
	UINT32              m_loop_stack[LOOP_STACK_DEPTH];
	UINT32              m_cntr_stack[CNTR_STACK_DEPTH];
	UINT32              m_pc_stack[PC_STACK_DEPTH];
	UINT16              m_stat_stack[STAT_STACK_DEPTH][3];
	INT32               m_pc_sp;
	INT32               m_cntr_sp;
	INT32               m_stat_sp;
	INT32               m_loop_sp;

	// external I/O
	UINT8               m_flagout;
	UINT8               m_flagin;
	UINT8               m_fl0;
	UINT8               m_fl1;
	UINT8               m_fl2;
	UINT16              m_idma_addr;
	UINT16              m_idma_cache;
	UINT8               m_idma_offs;

	// interrupt handling
	UINT16              m_imask;
	UINT8               m_icntl;
	UINT16              m_ifc;
	UINT8               m_irq_state[9];
	UINT8               m_irq_latch[9];
=======
	uint32_t              m_i[8];
	int32_t               m_m[8];
	uint32_t              m_l[8];
	uint32_t              m_lmask[8];
	uint32_t              m_base[8];
	uint8_t               m_px;

	// stacks
	uint32_t              m_loop_stack[LOOP_STACK_DEPTH];
	uint32_t              m_cntr_stack[CNTR_STACK_DEPTH];
	uint32_t              m_pc_stack[PC_STACK_DEPTH];
	uint16_t              m_stat_stack[STAT_STACK_DEPTH][3];
	int32_t               m_pc_sp;
	int32_t               m_cntr_sp;
	int32_t               m_stat_sp;
	int32_t               m_loop_sp;

	// external I/O
	uint8_t               m_flagout;
	uint8_t               m_flagin;
	uint8_t               m_fl0;
	uint8_t               m_fl1;
	uint8_t               m_fl2;
	uint16_t              m_idma_addr;
	uint16_t              m_idma_cache;
	uint8_t               m_idma_offs;

	// interrupt handling
	uint16_t              m_imask;
	uint8_t               m_icntl;
	uint16_t              m_ifc;
	uint8_t               m_irq_state[10];
	uint8_t               m_irq_latch[10];
>>>>>>> upstream/master

	// other internal states
	int                 m_icount;
	int                 m_mstat_mask;
	int                 m_imask_mask;

	// register maps
<<<<<<< HEAD
	INT16 *             m_read0_ptr[16];
	UINT32 *            m_read1_ptr[16];
	UINT32 *            m_read2_ptr[16];
=======
	int16_t *             m_read0_ptr[16];
	uint32_t *            m_read1_ptr[16];
	uint32_t *            m_read2_ptr[16];
>>>>>>> upstream/master
	void *              m_alu_xregs[8];
	void *              m_alu_yregs[4];
	void *              m_mac_xregs[8];
	void *              m_mac_yregs[4];
	void *              m_shift_xregs[8];

	// alternate core registers (at end for performance)
	adsp_core           m_alt;

	// address spaces
	address_space *     m_program;
	address_space *     m_data;
	address_space *     m_io;
	direct_read_data *  m_direct;

	// tables
<<<<<<< HEAD
	UINT8               m_condition_table[0x1000];
	UINT16              m_mask_table[0x4000];
	UINT16              m_reverse_table[0x4000];
=======
	uint8_t               m_condition_table[0x1000];
	uint16_t              m_mask_table[0x4000];
	uint16_t              m_reverse_table[0x4000];
>>>>>>> upstream/master

	devcb_read32            m_sport_rx_cb;    // callback for serial receive
	devcb_write32           m_sport_tx_cb;    // callback for serial transmit
	devcb_write_line        m_timer_fired_cb;          // callback for timer fired
<<<<<<< HEAD

	// debugging
#if ADSP_TRACK_HOTSPOTS
	UINT32              m_pcbucket[0x4000];
=======
	devcb_write_line        m_dmovlay_cb;          // callback for DMOVLAY instruction

	// debugging
#if ADSP_TRACK_HOTSPOTS
	uint32_t              m_pcbucket[0x4000];
>>>>>>> upstream/master
#endif

	// flag definitions
	static const int SSFLAG     = 0x80;
	static const int MVFLAG     = 0x40;
	static const int QFLAG      = 0x20;
	static const int SFLAG      = 0x10;
	static const int CFLAG      = 0x08;
	static const int VFLAG      = 0x04;
	static const int NFLAG      = 0x02;
	static const int ZFLAG      = 0x01;
};


// ======================> adsp2100_device

class adsp2100_device : public adsp21xx_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	adsp2100_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

protected:
	// device_execute_interface overrides
	virtual UINT32 execute_input_lines() const;

	// device_memory_interface overrides
	virtual const address_space_config *memory_space_config(address_spacenum spacenum = AS_0) const;

	// interrupts
	virtual bool generate_irq(int which, int indx);
	virtual void check_irqs();
=======
	adsp2100_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

protected:
	// device_execute_interface overrides
	virtual uint32_t execute_input_lines() const override;

	// device_memory_interface overrides
	virtual space_config_vector memory_space_config() const override;

	// interrupts
	virtual bool generate_irq(int which, int indx) override;
	virtual void check_irqs() override;
>>>>>>> upstream/master
};


// ======================> adsp2101_device

class adsp2101_device : public adsp21xx_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	adsp2101_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

protected:
	adsp2101_device(const machine_config &mconfig, device_type type, const char *name, const char *tag, device_t *owner, UINT32 clock, UINT32 chiptype, const char *shortname, const char *source);

	// device_execute_interface overrides
	virtual UINT32 execute_input_lines() const;

	// device_memory_interface overrides
	virtual const address_space_config *memory_space_config(address_spacenum spacenum = AS_0) const;

	// interrupts
	virtual bool generate_irq(int which, int indx);
	virtual void check_irqs();
=======
	adsp2101_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

protected:
	adsp2101_device(const machine_config &mconfig, device_type type, const char *tag, device_t *owner, uint32_t clock, uint32_t chiptype);

	// device_execute_interface overrides
	virtual uint32_t execute_input_lines() const override;

	// device_memory_interface overrides
	virtual space_config_vector memory_space_config() const override;

	// interrupts
	virtual bool generate_irq(int which, int indx) override;
	virtual void check_irqs() override;
>>>>>>> upstream/master
};


// ======================> adsp2181_device

class adsp2181_device : public adsp21xx_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	adsp2181_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

protected:
	// device_execute_interface overrides
	virtual UINT32 execute_input_lines() const;

	// device_memory_interface overrides
	virtual const address_space_config *memory_space_config(address_spacenum spacenum = AS_0) const;

	// interrupts
	virtual bool generate_irq(int which, int indx);
	virtual void check_irqs();
=======
	adsp2181_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

protected:
	// device_execute_interface overrides
	virtual uint32_t execute_input_lines() const override;

	// device_memory_interface overrides
	virtual space_config_vector memory_space_config() const override;

	// interrupts
	virtual bool generate_irq(int which, int indx) override;
	virtual void check_irqs() override;
>>>>>>> upstream/master

	// address spaces
	const address_space_config      m_io_config;

public:
	// public interfaces
<<<<<<< HEAD
	void idma_addr_w(UINT16 data);
	UINT16 idma_addr_r();
	void idma_data_w(UINT16 data);
	UINT16 idma_data_r();
=======
	void idma_addr_w(uint16_t data);
	uint16_t idma_addr_r();
	void idma_data_w(uint16_t data);
	uint16_t idma_data_r();
>>>>>>> upstream/master
};


// ======================> trivial variants

class adsp2104_device : public adsp2101_device
{
public:
<<<<<<< HEAD
	adsp2104_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
=======
	adsp2104_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
>>>>>>> upstream/master
};

class adsp2105_device : public adsp2101_device
{
public:
<<<<<<< HEAD
	adsp2105_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
=======
	adsp2105_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
>>>>>>> upstream/master
};

class adsp2115_device : public adsp2101_device
{
public:
<<<<<<< HEAD
	adsp2115_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
=======
	adsp2115_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
>>>>>>> upstream/master
};



// device type definition
<<<<<<< HEAD
extern const device_type ADSP2100;
extern const device_type ADSP2101;
extern const device_type ADSP2104;
extern const device_type ADSP2105;
extern const device_type ADSP2115;
extern const device_type ADSP2181;


#endif /* __ADSP2100_H__ */
=======
DECLARE_DEVICE_TYPE(ADSP2100, adsp2100_device)
DECLARE_DEVICE_TYPE(ADSP2101, adsp2101_device)
DECLARE_DEVICE_TYPE(ADSP2104, adsp2104_device)
DECLARE_DEVICE_TYPE(ADSP2105, adsp2105_device)
DECLARE_DEVICE_TYPE(ADSP2115, adsp2115_device)
DECLARE_DEVICE_TYPE(ADSP2181, adsp2181_device)


#endif // MAME_CPU_ADSP2100_ADSP2100_H
>>>>>>> upstream/master
