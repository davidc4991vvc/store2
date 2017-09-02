// license:BSD-3-Clause
// copyright-holders:Aaron Giles
/***************************************************************************

    dsp32.h
    Interface file for the portable DSP32 emulator.

***************************************************************************/

<<<<<<< HEAD
#pragma once

#ifndef __DSP32_H__
#define __DSP32_H__
=======
#ifndef MAME_CPU_DSP32_DSP32_H
#define MAME_CPU_DSP32_DSP32_H

#pragma once
>>>>>>> upstream/master


//**************************************************************************
//  CONSTANTS
//**************************************************************************

// IRQ sources
const int DSP32_IRQ0        = 0;        // IRQ0
const int DSP32_IRQ1        = 1;        // IRQ1

// pin signal bits
const int DSP32_OUTPUT_PIF  = 0x01;
const int DSP32_OUTPUT_PDF  = 0x02;

<<<<<<< HEAD
// register enumeration
enum
{
	// CAU
	DSP32_PC=1,
	DSP32_R0,
	DSP32_R1,
	DSP32_R2,
	DSP32_R3,
	DSP32_R4,
	DSP32_R5,
	DSP32_R6,
	DSP32_R7,
	DSP32_R8,
	DSP32_R9,
	DSP32_R10,
	DSP32_R11,
	DSP32_R12,
	DSP32_R13,
	DSP32_R14,
	DSP32_R15,
	DSP32_R16,
	DSP32_R17,
	DSP32_R18,
	DSP32_R19,
	DSP32_R20,
	DSP32_R21,
	DSP32_R22,
	DSP32_PIN,
	DSP32_POUT,
	DSP32_IVTP,

	// DAU
	DSP32_A0,
	DSP32_A1,
	DSP32_A2,
	DSP32_A3,
	DSP32_DAUC,

	// PIO
	DSP32_PAR,
	DSP32_PDR,
	DSP32_PIR,
	DSP32_PCR,
	DSP32_EMR,
	DSP32_ESR,
	DSP32_PCW,
	DSP32_PIOP,

	// SIO
	DSP32_IBUF,
	DSP32_ISR,
	DSP32_OBUF,
	DSP32_OSR,
	DSP32_IOC
};

=======
>>>>>>> upstream/master

//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

#define MCFG_DSP32C_OUTPUT_CALLBACK(_write) \
	devcb = &dsp32c_device::set_output_pins_callback(*device, DEVCB_##_write);

// ======================> dsp32c_device

class dsp32c_device : public cpu_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	dsp32c_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	template<class _Object> static devcb_base &set_output_pins_callback(device_t &device, _Object object) { return downcast<dsp32c_device &>(device).m_output_pins_changed.set_callback(object); }
=======
	dsp32c_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	template <class Object> static devcb_base &set_output_pins_callback(device_t &device, Object &&cb) { return downcast<dsp32c_device &>(device).m_output_pins_changed.set_callback(std::forward<Object>(cb)); }
>>>>>>> upstream/master


	// public interfaces
	void pio_w(int reg, int data);
	int pio_r(int reg);

protected:
<<<<<<< HEAD
	// device-level overrides
	virtual void device_start();
	virtual void device_reset();

	// device_execute_interface overrides
	virtual UINT32 execute_min_cycles() const;
	virtual UINT32 execute_max_cycles() const;
	virtual UINT32 execute_input_lines() const;
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

	// memory accessors
	UINT32 ROPCODE(offs_t pc);
	UINT8 RBYTE(offs_t addr);
	void WBYTE(offs_t addr, UINT8 data);
	UINT16 RWORD(offs_t addr);
	UINT32 RLONG(offs_t addr);
	void WWORD(offs_t addr, UINT16 data);
	void WLONG(offs_t addr, UINT32 data);
=======
	// register enumeration
	enum
	{
		// CAU
		DSP32_PC=1,
		DSP32_R0,
		DSP32_R1,
		DSP32_R2,
		DSP32_R3,
		DSP32_R4,
		DSP32_R5,
		DSP32_R6,
		DSP32_R7,
		DSP32_R8,
		DSP32_R9,
		DSP32_R10,
		DSP32_R11,
		DSP32_R12,
		DSP32_R13,
		DSP32_R14,
		DSP32_R15,
		DSP32_R16,
		DSP32_R17,
		DSP32_R18,
		DSP32_R19,
		DSP32_R20,
		DSP32_R21,
		DSP32_R22,
		DSP32_PIN,
		DSP32_POUT,
		DSP32_IVTP,

		// DAU
		DSP32_A0,
		DSP32_A1,
		DSP32_A2,
		DSP32_A3,
		DSP32_DAUC,

		// PIO
		DSP32_PAR,
		DSP32_PDR,
		DSP32_PIR,
		DSP32_PCR,
		DSP32_EMR,
		DSP32_ESR,
		DSP32_PCW,
		DSP32_PIOP,

		// SIO
		DSP32_IBUF,
		DSP32_ISR,
		DSP32_OBUF,
		DSP32_OSR,
		DSP32_IOC
	};

	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;

	// device_execute_interface overrides
	virtual uint32_t execute_min_cycles() const override;
	virtual uint32_t execute_max_cycles() const override;
	virtual uint32_t execute_input_lines() const override;
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

	// memory accessors
	uint32_t ROPCODE(offs_t pc);
	uint8_t RBYTE(offs_t addr);
	void WBYTE(offs_t addr, uint8_t data);
	uint16_t RWORD(offs_t addr);
	uint32_t RLONG(offs_t addr);
	void WWORD(offs_t addr, uint16_t data);
	void WLONG(offs_t addr, uint32_t data);
>>>>>>> upstream/master

	// interrupts
	void check_irqs();
	void set_irq_line(int irqline, int state);

<<<<<<< HEAD
	void update_pcr(UINT16 newval);
	void update_pins(void);
	void illegal(UINT32 op);
	void unimplemented(UINT32 op);
	void execute_one();

	// CAU helpers
	UINT32 cau_read_pi_special(UINT8 i);
	void cau_write_pi_special(UINT8 i, UINT32 val);
	UINT8 cau_read_pi_1byte(int pi);
	UINT16 cau_read_pi_2byte(int pi);
	UINT32 cau_read_pi_4byte(int pi);
	void cau_write_pi_1byte(int pi, UINT8 val);
	void cau_write_pi_2byte(int pi, UINT16 val);
	void cau_write_pi_4byte(int pi, UINT32 val);
=======
	void update_pcr(uint16_t newval);
	void update_pins(void);
	void illegal(uint32_t op);
	void unimplemented(uint32_t op);
	void execute_one();

	// CAU helpers
	uint32_t cau_read_pi_special(uint8_t i);
	void cau_write_pi_special(uint8_t i, uint32_t val);
	uint8_t cau_read_pi_1byte(int pi);
	uint16_t cau_read_pi_2byte(int pi);
	uint32_t cau_read_pi_4byte(int pi);
	void cau_write_pi_1byte(int pi, uint8_t val);
	void cau_write_pi_2byte(int pi, uint16_t val);
	void cau_write_pi_4byte(int pi, uint32_t val);
>>>>>>> upstream/master

	// DAU helpers
	double dau_get_amult(int aidx);
	double dau_get_anzflags();
<<<<<<< HEAD
	UINT8 dau_get_avuflags();
	void remember_last_dau(int aidx);
	void dau_set_val_noflags(int aidx, double res);
	void dau_set_val_flags(int aidx, double res);
	double dsp_to_double(UINT32 val);
	UINT32 double_to_dsp(double val);
=======
	uint8_t dau_get_avuflags();
	void remember_last_dau(int aidx);
	void dau_set_val_noflags(int aidx, double res);
	void dau_set_val_flags(int aidx, double res);
	double dsp_to_double(uint32_t val);
	uint32_t double_to_dsp(double val);
>>>>>>> upstream/master
	double dau_read_pi_special(int i);
	void dau_write_pi_special(int i, double val);
	double dau_read_pi_double_1st(int pi, int multiplier);
	double dau_read_pi_double_2nd(int pi, int multiplier, double xval);
<<<<<<< HEAD
	UINT32 dau_read_pi_4bytes(int pi);
	UINT16 dau_read_pi_2bytes(int pi);
	void dau_write_pi_double(int pi, double val);
	void dau_write_pi_4bytes(int pi, UINT32 val);
	void dau_write_pi_2bytes(int pi, UINT16 val);
=======
	uint32_t dau_read_pi_4bytes(int pi);
	uint16_t dau_read_pi_2bytes(int pi);
	void dau_write_pi_double(int pi, double val);
	void dau_write_pi_4bytes(int pi, uint32_t val);
	void dau_write_pi_2bytes(int pi, uint16_t val);
>>>>>>> upstream/master

	// common condition routine
	int condition(int cond);

	// CAU branch instruction implementation
<<<<<<< HEAD
	void nop(UINT32 op);
	void goto_t(UINT32 op);
	void goto_pl(UINT32 op);
	void goto_mi(UINT32 op);
	void goto_ne(UINT32 op);
	void goto_eq(UINT32 op);
	void goto_vc(UINT32 op);
	void goto_vs(UINT32 op);
	void goto_cc(UINT32 op);
	void goto_cs(UINT32 op);
	void goto_ge(UINT32 op);
	void goto_lt(UINT32 op);
	void goto_gt(UINT32 op);
	void goto_le(UINT32 op);
	void goto_hi(UINT32 op);
	void goto_ls(UINT32 op);
	void goto_auc(UINT32 op);
	void goto_aus(UINT32 op);
	void goto_age(UINT32 op);
	void goto_alt(UINT32 op);
	void goto_ane(UINT32 op);
	void goto_aeq(UINT32 op);
	void goto_avc(UINT32 op);
	void goto_avs(UINT32 op);
	void goto_agt(UINT32 op);
	void goto_ale(UINT32 op);
	void goto_ibe(UINT32 op);
	void goto_ibf(UINT32 op);
	void goto_obf(UINT32 op);
	void goto_obe(UINT32 op);
	void goto_pde(UINT32 op);
	void goto_pdf(UINT32 op);
	void goto_pie(UINT32 op);
	void goto_pif(UINT32 op);
	void goto_syc(UINT32 op);
	void goto_sys(UINT32 op);
	void goto_fbc(UINT32 op);
	void goto_fbs(UINT32 op);
	void goto_irq1lo(UINT32 op);
	void goto_irq1hi(UINT32 op);
	void goto_irq2lo(UINT32 op);
	void goto_irq2hi(UINT32 op);
	void dec_goto(UINT32 op);
	void call(UINT32 op);
	void goto24(UINT32 op);
	void call24(UINT32 op);
	void do_i(UINT32 op);
	void do_r(UINT32 op);

	// CAU 16-bit arithmetic implementation
	void add_si(UINT32 op);
	void add_ss(UINT32 op);
	void mul2_s(UINT32 op);
	void subr_ss(UINT32 op);
	void addr_ss(UINT32 op);
	void sub_ss(UINT32 op);
	void neg_s(UINT32 op);
	void andc_ss(UINT32 op);
	void cmp_ss(UINT32 op);
	void xor_ss(UINT32 op);
	void rcr_s(UINT32 op);
	void or_ss(UINT32 op);
	void rcl_s(UINT32 op);
	void shr_s(UINT32 op);
	void div2_s(UINT32 op);
	void and_ss(UINT32 op);
	void test_ss(UINT32 op);
	void add_di(UINT32 op);
	void subr_di(UINT32 op);
	void addr_di(UINT32 op);
	void sub_di(UINT32 op);
	void andc_di(UINT32 op);
	void cmp_di(UINT32 op);
	void xor_di(UINT32 op);
	void or_di(UINT32 op);
	void and_di(UINT32 op);
	void test_di(UINT32 op);

	// CAU 24-bit arithmetic implementation
	void adde_si(UINT32 op);
	void adde_ss(UINT32 op);
	void mul2e_s(UINT32 op);
	void subre_ss(UINT32 op);
	void addre_ss(UINT32 op);
	void sube_ss(UINT32 op);
	void nege_s(UINT32 op);
	void andce_ss(UINT32 op);
	void cmpe_ss(UINT32 op);
	void xore_ss(UINT32 op);
	void rcre_s(UINT32 op);
	void ore_ss(UINT32 op);
	void rcle_s(UINT32 op);
	void shre_s(UINT32 op);
	void div2e_s(UINT32 op);
	void ande_ss(UINT32 op);
	void teste_ss(UINT32 op);
	void adde_di(UINT32 op);
	void subre_di(UINT32 op);
	void addre_di(UINT32 op);
	void sube_di(UINT32 op);
	void andce_di(UINT32 op);
	void cmpe_di(UINT32 op);
	void xore_di(UINT32 op);
	void ore_di(UINT32 op);
	void ande_di(UINT32 op);
	void teste_di(UINT32 op);

	// CAU load/store implementation
	void load_hi(UINT32 op);
	void load_li(UINT32 op);
	void load_i(UINT32 op);
	void load_ei(UINT32 op);
	void store_hi(UINT32 op);
	void store_li(UINT32 op);
	void store_i(UINT32 op);
	void store_ei(UINT32 op);
	void load_hr(UINT32 op);
	void load_lr(UINT32 op);
	void load_r(UINT32 op);
	void load_er(UINT32 op);
	void store_hr(UINT32 op);
	void store_lr(UINT32 op);
	void store_r(UINT32 op);
	void store_er(UINT32 op);
	void load24(UINT32 op);

	// DAU form 1 implementation
	void d1_aMpp(UINT32 op);
	void d1_aMpm(UINT32 op);
	void d1_aMmp(UINT32 op);
	void d1_aMmm(UINT32 op);
	void d1_0px(UINT32 op);
	void d1_0mx(UINT32 op);
	void d1_1pp(UINT32 op);
	void d1_1pm(UINT32 op);
	void d1_1mp(UINT32 op);
	void d1_1mm(UINT32 op);
	void d1_aMppr(UINT32 op);
	void d1_aMpmr(UINT32 op);
	void d1_aMmpr(UINT32 op);
	void d1_aMmmr(UINT32 op);

	// DAU form 2 implementation
	void d2_aMpp(UINT32 op);
	void d2_aMpm(UINT32 op);
	void d2_aMmp(UINT32 op);
	void d2_aMmm(UINT32 op);
	void d2_aMppr(UINT32 op);
	void d2_aMpmr(UINT32 op);
	void d2_aMmpr(UINT32 op);
	void d2_aMmmr(UINT32 op);

	// DAU form 3 implementation
	void d3_aMpp(UINT32 op);
	void d3_aMpm(UINT32 op);
	void d3_aMmp(UINT32 op);
	void d3_aMmm(UINT32 op);
	void d3_aMppr(UINT32 op);
	void d3_aMpmr(UINT32 op);
	void d3_aMmpr(UINT32 op);
	void d3_aMmmr(UINT32 op);

	// DAU form 4 implementation
	void d4_pp(UINT32 op);
	void d4_pm(UINT32 op);
	void d4_mp(UINT32 op);
	void d4_mm(UINT32 op);
	void d4_ppr(UINT32 op);
	void d4_pmr(UINT32 op);
	void d4_mpr(UINT32 op);
	void d4_mmr(UINT32 op);

	// DAU form 5 implementation
	void d5_ic(UINT32 op);
	void d5_oc(UINT32 op);
	void d5_float(UINT32 op);
	void d5_int(UINT32 op);
	void d5_round(UINT32 op);
	void d5_ifalt(UINT32 op);
	void d5_ifaeq(UINT32 op);
	void d5_ifagt(UINT32 op);
	void d5_float24(UINT32 op);
	void d5_int24(UINT32 op);
	void d5_ieee(UINT32 op);
	void d5_dsp(UINT32 op);
	void d5_seed(UINT32 op);
=======
	void nop(uint32_t op);
	void goto_t(uint32_t op);
	void goto_pl(uint32_t op);
	void goto_mi(uint32_t op);
	void goto_ne(uint32_t op);
	void goto_eq(uint32_t op);
	void goto_vc(uint32_t op);
	void goto_vs(uint32_t op);
	void goto_cc(uint32_t op);
	void goto_cs(uint32_t op);
	void goto_ge(uint32_t op);
	void goto_lt(uint32_t op);
	void goto_gt(uint32_t op);
	void goto_le(uint32_t op);
	void goto_hi(uint32_t op);
	void goto_ls(uint32_t op);
	void goto_auc(uint32_t op);
	void goto_aus(uint32_t op);
	void goto_age(uint32_t op);
	void goto_alt(uint32_t op);
	void goto_ane(uint32_t op);
	void goto_aeq(uint32_t op);
	void goto_avc(uint32_t op);
	void goto_avs(uint32_t op);
	void goto_agt(uint32_t op);
	void goto_ale(uint32_t op);
	void goto_ibe(uint32_t op);
	void goto_ibf(uint32_t op);
	void goto_obf(uint32_t op);
	void goto_obe(uint32_t op);
	void goto_pde(uint32_t op);
	void goto_pdf(uint32_t op);
	void goto_pie(uint32_t op);
	void goto_pif(uint32_t op);
	void goto_syc(uint32_t op);
	void goto_sys(uint32_t op);
	void goto_fbc(uint32_t op);
	void goto_fbs(uint32_t op);
	void goto_irq1lo(uint32_t op);
	void goto_irq1hi(uint32_t op);
	void goto_irq2lo(uint32_t op);
	void goto_irq2hi(uint32_t op);
	void dec_goto(uint32_t op);
	void call(uint32_t op);
	void goto24(uint32_t op);
	void call24(uint32_t op);
	void do_i(uint32_t op);
	void do_r(uint32_t op);

	// CAU 16-bit arithmetic implementation
	void add_si(uint32_t op);
	void add_ss(uint32_t op);
	void mul2_s(uint32_t op);
	void subr_ss(uint32_t op);
	void addr_ss(uint32_t op);
	void sub_ss(uint32_t op);
	void neg_s(uint32_t op);
	void andc_ss(uint32_t op);
	void cmp_ss(uint32_t op);
	void xor_ss(uint32_t op);
	void rcr_s(uint32_t op);
	void or_ss(uint32_t op);
	void rcl_s(uint32_t op);
	void shr_s(uint32_t op);
	void div2_s(uint32_t op);
	void and_ss(uint32_t op);
	void test_ss(uint32_t op);
	void add_di(uint32_t op);
	void subr_di(uint32_t op);
	void addr_di(uint32_t op);
	void sub_di(uint32_t op);
	void andc_di(uint32_t op);
	void cmp_di(uint32_t op);
	void xor_di(uint32_t op);
	void or_di(uint32_t op);
	void and_di(uint32_t op);
	void test_di(uint32_t op);

	// CAU 24-bit arithmetic implementation
	void adde_si(uint32_t op);
	void adde_ss(uint32_t op);
	void mul2e_s(uint32_t op);
	void subre_ss(uint32_t op);
	void addre_ss(uint32_t op);
	void sube_ss(uint32_t op);
	void nege_s(uint32_t op);
	void andce_ss(uint32_t op);
	void cmpe_ss(uint32_t op);
	void xore_ss(uint32_t op);
	void rcre_s(uint32_t op);
	void ore_ss(uint32_t op);
	void rcle_s(uint32_t op);
	void shre_s(uint32_t op);
	void div2e_s(uint32_t op);
	void ande_ss(uint32_t op);
	void teste_ss(uint32_t op);
	void adde_di(uint32_t op);
	void subre_di(uint32_t op);
	void addre_di(uint32_t op);
	void sube_di(uint32_t op);
	void andce_di(uint32_t op);
	void cmpe_di(uint32_t op);
	void xore_di(uint32_t op);
	void ore_di(uint32_t op);
	void ande_di(uint32_t op);
	void teste_di(uint32_t op);

	// CAU load/store implementation
	void load_hi(uint32_t op);
	void load_li(uint32_t op);
	void load_i(uint32_t op);
	void load_ei(uint32_t op);
	void store_hi(uint32_t op);
	void store_li(uint32_t op);
	void store_i(uint32_t op);
	void store_ei(uint32_t op);
	void load_hr(uint32_t op);
	void load_lr(uint32_t op);
	void load_r(uint32_t op);
	void load_er(uint32_t op);
	void store_hr(uint32_t op);
	void store_lr(uint32_t op);
	void store_r(uint32_t op);
	void store_er(uint32_t op);
	void load24(uint32_t op);

	// DAU form 1 implementation
	void d1_aMpp(uint32_t op);
	void d1_aMpm(uint32_t op);
	void d1_aMmp(uint32_t op);
	void d1_aMmm(uint32_t op);
	void d1_0px(uint32_t op);
	void d1_0mx(uint32_t op);
	void d1_1pp(uint32_t op);
	void d1_1pm(uint32_t op);
	void d1_1mp(uint32_t op);
	void d1_1mm(uint32_t op);
	void d1_aMppr(uint32_t op);
	void d1_aMpmr(uint32_t op);
	void d1_aMmpr(uint32_t op);
	void d1_aMmmr(uint32_t op);

	// DAU form 2 implementation
	void d2_aMpp(uint32_t op);
	void d2_aMpm(uint32_t op);
	void d2_aMmp(uint32_t op);
	void d2_aMmm(uint32_t op);
	void d2_aMppr(uint32_t op);
	void d2_aMpmr(uint32_t op);
	void d2_aMmpr(uint32_t op);
	void d2_aMmmr(uint32_t op);

	// DAU form 3 implementation
	void d3_aMpp(uint32_t op);
	void d3_aMpm(uint32_t op);
	void d3_aMmp(uint32_t op);
	void d3_aMmm(uint32_t op);
	void d3_aMppr(uint32_t op);
	void d3_aMpmr(uint32_t op);
	void d3_aMmpr(uint32_t op);
	void d3_aMmmr(uint32_t op);

	// DAU form 4 implementation
	void d4_pp(uint32_t op);
	void d4_pm(uint32_t op);
	void d4_mp(uint32_t op);
	void d4_mm(uint32_t op);
	void d4_ppr(uint32_t op);
	void d4_pmr(uint32_t op);
	void d4_mpr(uint32_t op);
	void d4_mmr(uint32_t op);

	// DAU form 5 implementation
	void d5_ic(uint32_t op);
	void d5_oc(uint32_t op);
	void d5_float(uint32_t op);
	void d5_int(uint32_t op);
	void d5_round(uint32_t op);
	void d5_ifalt(uint32_t op);
	void d5_ifaeq(uint32_t op);
	void d5_ifagt(uint32_t op);
	void d5_float24(uint32_t op);
	void d5_int24(uint32_t op);
	void d5_ieee(uint32_t op);
	void d5_dsp(uint32_t op);
	void d5_seed(uint32_t op);
>>>>>>> upstream/master

	// dma helpers
	void dma_increment();
	void dma_load();
	void dma_store();

	// configuration
	const address_space_config      m_program_config;

	// internal state
<<<<<<< HEAD
	UINT32          m_r[32];
	UINT32          m_pin, m_pout;
	UINT32          m_ivtp;
	UINT32          m_nzcflags;
	UINT32          m_vflags;

	double          m_a[6];
	double          m_NZflags;
	UINT8           m_VUflags;

	double          m_abuf[4];
	UINT8           m_abufreg[4];
	UINT8           m_abufVUflags[4];
	UINT8           m_abufNZflags[4];
	int             m_abufcycle[4];
	int             m_abuf_index;

	INT32           m_mbufaddr[4];
	UINT32          m_mbufdata[4];
	int             m_mbuf_index;

	UINT16          m_par;
	UINT8           m_pare;
	UINT16          m_pdr;
	UINT16          m_pdr2;
	UINT16          m_pir;
	UINT16          m_pcr;
	UINT16          m_emr;
	UINT8           m_esr;
	UINT16          m_pcw;
	UINT8           m_piop;

	UINT32          m_ibuf;
	UINT32          m_isr;
	UINT32          m_obuf;
	UINT32          m_osr;

	UINT32          m_iotemp;
=======
	uint32_t          m_r[32];
	uint32_t          m_pin, m_pout;
	uint32_t          m_ivtp;
	uint32_t          m_nzcflags;
	uint32_t          m_vflags;

	double          m_a[6];
	double          m_NZflags;
	uint8_t           m_VUflags;

	double          m_abuf[4];
	uint8_t           m_abufreg[4];
	uint8_t           m_abufVUflags[4];
	uint8_t           m_abufNZflags[4];
	int             m_abufcycle[4];
	int             m_abuf_index;

	int32_t           m_mbufaddr[4];
	uint32_t          m_mbufdata[4];
	int             m_mbuf_index;

	uint16_t          m_par;
	uint8_t           m_pare;
	uint16_t          m_pdr;
	uint16_t          m_pdr2;
	uint16_t          m_pir;
	uint16_t          m_pcr;
	uint16_t          m_emr;
	uint8_t           m_esr;
	uint16_t          m_pcw;
	uint8_t           m_piop;

	uint32_t          m_ibuf;
	uint32_t          m_isr;
	uint32_t          m_obuf;
	uint32_t          m_osr;

	uint32_t          m_iotemp;
>>>>>>> upstream/master

	// internal stuff
	int             m_lastp;
	int             m_icount;
<<<<<<< HEAD
	UINT8           m_lastpins;
	UINT32          m_ppc;
=======
	uint8_t           m_lastpins;
	uint32_t          m_ppc;
>>>>>>> upstream/master
	address_space * m_program;
	direct_read_data *m_direct;

	devcb_write32 m_output_pins_changed;
	// tables
<<<<<<< HEAD
	static void (dsp32c_device::*const s_dsp32ops[])(UINT32 op);
	static const UINT32 s_regmap[4][16];
};


extern const device_type DSP32C;



#endif /* __DSP32_H__ */
=======
	static void (dsp32c_device::*const s_dsp32ops[])(uint32_t op);
	static const uint32_t s_regmap[4][16];
};


DECLARE_DEVICE_TYPE(DSP32C, dsp32c_device)

#endif // MAME_CPU_DSP32_DSP32_H
>>>>>>> upstream/master
