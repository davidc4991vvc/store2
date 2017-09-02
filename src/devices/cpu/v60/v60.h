// license:BSD-3-Clause
// copyright-holders:Farfetch'd, R. Belmont
<<<<<<< HEAD
#pragma once

#ifndef __V60_H__
#define __V60_H__
=======
#ifndef MAME_CPU_V60_V60_H
#define MAME_CPU_V60_V60_H

#pragma once
>>>>>>> upstream/master


enum
{
	V60_R0 = 1,
	V60_R1,
	V60_R2,
	V60_R3,
	V60_R4,
	V60_R5,
	V60_R6,
	V60_R7,
	V60_R8,
	V60_R9,
	V60_R10,
	V60_R11,
	V60_R12,
	V60_R13,
	V60_R14,
	V60_R15,
	V60_R16,
	V60_R17,
	V60_R18,
	V60_R19,
	V60_R20,
	V60_R21,
	V60_R22,
	V60_R23,
	V60_R24,
	V60_R25,
	V60_R26,
	V60_R27,
	V60_R28,
	V60_AP,
	V60_FP,
	V60_SP,
	V60_PC,
	V60_PSW,
	V60_U1,
	V60_U2,
	V60_ISP,
	V60_L0SP,
	V60_L1SP,
	V60_L2SP,
	V60_L3SP,
	V60_SBR,
	V60_TR,
	V60_SYCW,
	V60_TKCW,
	V60_PIR,
	V60_Res1,
	V60_Res2,
	V60_Res3,
	V60_Res4,
	V60_Res5,
	V60_PSW2,
	V60_ATBR0,
	V60_ATLR0,
	V60_ATBR1,
	V60_ATLR1,
	V60_ATBR2,
	V60_ATLR2,
	V60_ATBR3,
	V60_ATLR3,
	V60_TRMODE,
	V60_ADTR0,
	V60_ADTR1,
	V60_ADTMR0,
	V60_ADTMR1,
	V60_Res6,
	V60_Res7,
	V60_Res8,
	V60_REGMAX
};


class v60_device : public cpu_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	v60_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
	v60_device(const machine_config &mconfig, device_type type, const char *name, const char *tag, device_t *owner, UINT32 clock, const char *shortname, const char *source);
=======
	v60_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
>>>>>>> upstream/master

	void stall();

protected:
<<<<<<< HEAD
	// device-level overrides
	virtual void device_start();
	virtual void device_reset();

	// device_execute_interface overrides
	virtual UINT32 execute_min_cycles() const { return 1; }
	virtual UINT32 execute_max_cycles() const { return 1; }
	virtual UINT32 execute_input_lines() const { return 1; }
	virtual void execute_run();
	virtual void execute_set_input(int inputnum, int state);

	// device_memory_interface overrides
	virtual const address_space_config *memory_space_config(address_spacenum spacenum = AS_0) const { return (spacenum == AS_PROGRAM) ? &m_program_config : ( (spacenum == AS_IO) ? &m_io_config : NULL ); }

	// device_state_interface overrides
	virtual void state_import(const device_state_entry &entry);
	virtual void state_export(const device_state_entry &entry);

	// device_disasm_interface overrides
	virtual UINT32 disasm_min_opcode_bytes() const { return 1; }
	virtual UINT32 disasm_max_opcode_bytes() const { return 22; }
	virtual offs_t disasm_disassemble(char *buffer, offs_t pc, const UINT8 *oprom, const UINT8 *opram, UINT32 options);

private:
	typedef UINT32 (v60_device::*am_func)();
	typedef UINT32 (v60_device::*op6_func)(int reg);
=======
	v60_device(const machine_config &mconfig, device_type type, const char *tag, device_t *owner, uint32_t clock, int databits, int addrbits, uint32_t pir);

	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;

	// device_execute_interface overrides
	virtual uint32_t execute_min_cycles() const override { return 1; }
	virtual uint32_t execute_max_cycles() const override { return 1; }
	virtual uint32_t execute_input_lines() const override { return 1; }
	virtual void execute_run() override;
	virtual void execute_set_input(int inputnum, int state) override;

	// device_memory_interface overrides
	virtual space_config_vector memory_space_config() const override;

	// device_state_interface overrides
	virtual void state_import(const device_state_entry &entry) override;
	virtual void state_export(const device_state_entry &entry) override;

	// device_disasm_interface overrides
	virtual uint32_t disasm_min_opcode_bytes() const override { return 1; }
	virtual uint32_t disasm_max_opcode_bytes() const override { return 22; }
	virtual offs_t disasm_disassemble(std::ostream &stream, offs_t pc, const uint8_t *oprom, const uint8_t *opram, uint32_t options) override;

private:
	typedef uint32_t (v60_device::*am_func)();
	typedef uint32_t (v60_device::*op6_func)(int reg);
>>>>>>> upstream/master

	static const am_func s_AMTable1_G7a[16];
	static const am_func s_BAMTable1_G7a[16];
	static const am_func s_AMTable1_G7[32];
	static const am_func s_BAMTable1_G7[32];
	static const am_func s_AMTable1_G6[8];
	static const am_func s_BAMTable1_G6[8];
	static const am_func s_AMTable1[2][8];
	static const am_func s_BAMTable1[2][8];
	static const am_func s_AMTable2_G7a[16];
	static const am_func s_BAMTable2_G7a[16];
	static const am_func s_AMTable2_G7[32];
	static const am_func s_BAMTable2_G7[32];
	static const am_func s_AMTable2_G6[8];
	static const am_func s_BAMTable2_G6[8];
	static const am_func s_AMTable2[2][8];
	static const am_func s_BAMTable2[2][8];
	static const am_func s_AMTable3_G7a[16];
	static const am_func s_AMTable3_G7[32];
	static const am_func s_AMTable3_G6[8];
	static const am_func s_AMTable3[2][8];
	static const am_func s_Op5FTable[32];
	static const am_func s_Op5CTable[32];
	static const op6_func s_OpC6Table[8];
	static const op6_func s_OpC7Table[8];
	static const am_func s_Op59Table[32];
	static const am_func s_Op5BTable[32];
	static const am_func s_Op5DTable[32];
	static const am_func s_Op58Table[32];
	static const am_func s_Op5ATable[32];
	static const am_func s_OpCodeTable[256];

	address_space_config m_program_config;
	address_space_config m_io_config;

	offs_t              m_fetch_xor;
	offs_t              m_start_pc;
<<<<<<< HEAD
	UINT32              m_reg[68];
	struct {
		UINT8 CY;
		UINT8 OV;
		UINT8 S;
		UINT8 Z;
	}                   m_flags;
	UINT8               m_irq_line;
	UINT8               m_nmi_line;
	address_space *m_program;
	direct_read_data *  m_direct;
	address_space *m_io;
	UINT32              m_PPC;
	int                 m_icount;
	int                 m_stall_io;

	UINT32              m_op1, m_op2;
	UINT8               m_flag1, m_flag2;
	UINT8               m_instflags;
	UINT32              m_lenop1, m_lenop2;
	UINT8               m_subop;
	UINT32              m_bamoffset1, m_bamoffset2;

	// Output variables for ReadAMAddress(cpustate)
	UINT8               m_amflag;
	UINT32              m_amout;
	UINT32              m_bamoffset;

	// Appo temp var
	UINT32              m_amlength1, m_amlength2;

	// Global vars used by AM functions
	UINT32              m_modadd;
	UINT8               m_modm;
	UINT8               m_modval;
	UINT8               m_modval2;
	UINT8               m_modwritevalb;
	UINT16              m_modwritevalh;
	UINT32              m_modwritevalw;
	UINT8               m_moddim;

	UINT32 m_debugger_temp;
=======
	uint32_t              m_reg[68];
	struct {
		uint8_t CY;
		uint8_t OV;
		uint8_t S;
		uint8_t Z;
	}                   m_flags;
	uint8_t               m_irq_line;
	uint8_t               m_nmi_line;
	address_space *m_program;
	direct_read_data *  m_direct;
	address_space *m_io;
	uint32_t              m_PPC;
	int                 m_icount;
	int                 m_stall_io;

	uint32_t              m_op1, m_op2;
	uint8_t               m_flag1, m_flag2;
	uint8_t               m_instflags;
	uint32_t              m_lenop1, m_lenop2;
	uint8_t               m_subop;
	uint32_t              m_bamoffset1, m_bamoffset2;

	// Output variables for ReadAMAddress(cpustate)
	uint8_t               m_amflag;
	uint32_t              m_amout;
	uint32_t              m_bamoffset;

	// Appo temp var
	uint32_t              m_amlength1, m_amlength2;

	// Global vars used by AM functions
	uint32_t              m_modadd;
	uint8_t               m_modm;
	uint8_t               m_modval;
	uint8_t               m_modval2;
	uint8_t               m_modwritevalb;
	uint16_t              m_modwritevalh;
	uint32_t              m_modwritevalw;
	uint8_t               m_moddim;

	uint32_t m_debugger_temp;
>>>>>>> upstream/master


	inline void v60SaveStack();
	inline void v60ReloadStack();
<<<<<<< HEAD
	inline UINT32 v60ReadPSW();
	inline void v60WritePSW(UINT32 newval);
	inline UINT32 v60_update_psw_for_exception(int is_interrupt, int target_level);

	UINT32 am1Register();
	UINT32 am1RegisterIndirect();
	UINT32 bam1RegisterIndirect();
	UINT32 am1RegisterIndirectIndexed();
	UINT32 bam1RegisterIndirectIndexed();
	UINT32 am1Autoincrement();
	UINT32 bam1Autoincrement();
	UINT32 am1Autodecrement();
	UINT32 bam1Autodecrement();
	UINT32 am1Displacement8();
	UINT32 bam1Displacement8();
	UINT32 am1Displacement16();
	UINT32 bam1Displacement16();
	UINT32 am1Displacement32();
	UINT32 bam1Displacement32();
	UINT32 am1DisplacementIndexed8();
	UINT32 bam1DisplacementIndexed8();
	UINT32 am1DisplacementIndexed16();
	UINT32 bam1DisplacementIndexed16();
	UINT32 am1DisplacementIndexed32();
	UINT32 bam1DisplacementIndexed32();
	UINT32 am1PCDisplacement8();
	UINT32 bam1PCDisplacement8();
	UINT32 am1PCDisplacement16();
	UINT32 bam1PCDisplacement16();
	UINT32 am1PCDisplacement32();
	UINT32 bam1PCDisplacement32();
	UINT32 am1PCDisplacementIndexed8();
	UINT32 bam1PCDisplacementIndexed8();
	UINT32 am1PCDisplacementIndexed16();
	UINT32 bam1PCDisplacementIndexed16();
	UINT32 am1PCDisplacementIndexed32();
	UINT32 bam1PCDisplacementIndexed32();
	UINT32 am1DisplacementIndirect8();
	UINT32 bam1DisplacementIndirect8();
	UINT32 am1DisplacementIndirect16();
	UINT32 bam1DisplacementIndirect16();
	UINT32 am1DisplacementIndirect32();
	UINT32 bam1DisplacementIndirect32();
	UINT32 am1DisplacementIndirectIndexed8();
	UINT32 bam1DisplacementIndirectIndexed8();
	UINT32 am1DisplacementIndirectIndexed16();
	UINT32 bam1DisplacementIndirectIndexed16();
	UINT32 am1DisplacementIndirectIndexed32();
	UINT32 bam1DisplacementIndirectIndexed32();
	UINT32 am1PCDisplacementIndirect8();
	UINT32 bam1PCDisplacementIndirect8();
	UINT32 am1PCDisplacementIndirect16();
	UINT32 bam1PCDisplacementIndirect16();
	UINT32 am1PCDisplacementIndirect32();
	UINT32 bam1PCDisplacementIndirect32();
	UINT32 am1PCDisplacementIndirectIndexed8();
	UINT32 bam1PCDisplacementIndirectIndexed8();
	UINT32 am1PCDisplacementIndirectIndexed16();
	UINT32 bam1PCDisplacementIndirectIndexed16();
	UINT32 am1PCDisplacementIndirectIndexed32();
	UINT32 bam1PCDisplacementIndirectIndexed32();
	UINT32 am1DoubleDisplacement8();
	UINT32 bam1DoubleDisplacement8();
	UINT32 am1DoubleDisplacement16();
	UINT32 bam1DoubleDisplacement16();
	UINT32 am1DoubleDisplacement32();
	UINT32 bam1DoubleDisplacement32();
	UINT32 am1PCDoubleDisplacement8();
	UINT32 bam1PCDoubleDisplacement8();
	UINT32 am1PCDoubleDisplacement16();
	UINT32 bam1PCDoubleDisplacement16();
	UINT32 am1PCDoubleDisplacement32();
	UINT32 bam1PCDoubleDisplacement32();
	UINT32 am1DirectAddress();
	UINT32 bam1DirectAddress();
	UINT32 am1DirectAddressIndexed();
	UINT32 bam1DirectAddressIndexed();
	UINT32 am1DirectAddressDeferred();
	UINT32 bam1DirectAddressDeferred();
	UINT32 am1DirectAddressDeferredIndexed();
	UINT32 bam1DirectAddressDeferredIndexed();
	UINT32 am1Immediate();
	UINT32 am1ImmediateQuick();
	UINT32 am1Error1();
	UINT32 bam1Error1();
	UINT32 am1Error2();
	UINT32 bam1Error2();
	UINT32 am1Error3();
	UINT32 bam1Error3();
	UINT32 am1Error4();
	UINT32 bam1Error4();
	UINT32 am1Error5();
	UINT32 bam1Error5();
	UINT32 bam1Error6();
	UINT32 am1Group7a();
	UINT32 bam1Group7a();
	UINT32 am1Group6();
	UINT32 bam1Group6();
	UINT32 am1Group7();
	UINT32 bam1Group7();
	UINT32 am2Register();
	UINT32 am2RegisterIndirect();
	UINT32 bam2RegisterIndirect();
	UINT32 am2RegisterIndirectIndexed();
	UINT32 bam2RegisterIndirectIndexed();
	UINT32 am2Autoincrement();
	UINT32 bam2Autoincrement();
	UINT32 am2Autodecrement();
	UINT32 bam2Autodecrement();
	UINT32 am2Displacement8();
	UINT32 bam2Displacement8();
	UINT32 am2Displacement16();
	UINT32 bam2Displacement16();
	UINT32 am2Displacement32();
	UINT32 bam2Displacement32();
	UINT32 am2DisplacementIndexed8();
	UINT32 bam2DisplacementIndexed8();
	UINT32 am2DisplacementIndexed16();
	UINT32 bam2DisplacementIndexed16();
	UINT32 am2DisplacementIndexed32();
	UINT32 bam2DisplacementIndexed32();
	UINT32 am2PCDisplacement8();
	UINT32 bam2PCDisplacement8();
	UINT32 am2PCDisplacement16();
	UINT32 bam2PCDisplacement16();
	UINT32 am2PCDisplacement32();
	UINT32 bam2PCDisplacement32();
	UINT32 am2PCDisplacementIndexed8();
	UINT32 bam2PCDisplacementIndexed8();
	UINT32 am2PCDisplacementIndexed16();
	UINT32 bam2PCDisplacementIndexed16();
	UINT32 am2PCDisplacementIndexed32();
	UINT32 bam2PCDisplacementIndexed32();
	UINT32 am2DisplacementIndirect8();
	UINT32 bam2DisplacementIndirect8();
	UINT32 am2DisplacementIndirect16();
	UINT32 bam2DisplacementIndirect16();
	UINT32 am2DisplacementIndirect32();
	UINT32 bam2DisplacementIndirect32();
	UINT32 am2DisplacementIndirectIndexed8();
	UINT32 bam2DisplacementIndirectIndexed8();
	UINT32 am2DisplacementIndirectIndexed16();
	UINT32 bam2DisplacementIndirectIndexed16();
	UINT32 am2DisplacementIndirectIndexed32();
	UINT32 bam2DisplacementIndirectIndexed32();
	UINT32 am2PCDisplacementIndirect8();
	UINT32 bam2PCDisplacementIndirect8();
	UINT32 am2PCDisplacementIndirect16();
	UINT32 bam2PCDisplacementIndirect16();
	UINT32 am2PCDisplacementIndirect32();
	UINT32 bam2PCDisplacementIndirect32();
	UINT32 am2PCDisplacementIndirectIndexed8();
	UINT32 bam2PCDisplacementIndirectIndexed8();
	UINT32 am2PCDisplacementIndirectIndexed16();
	UINT32 bam2PCDisplacementIndirectIndexed16();
	UINT32 am2PCDisplacementIndirectIndexed32();
	UINT32 bam2PCDisplacementIndirectIndexed32();
	UINT32 am2DoubleDisplacement8();
	UINT32 bam2DoubleDisplacement8();
	UINT32 am2DoubleDisplacement16();
	UINT32 bam2DoubleDisplacement16();
	UINT32 am2DoubleDisplacement32();
	UINT32 bam2DoubleDisplacement32();
	UINT32 am2PCDoubleDisplacement8();
	UINT32 bam2PCDoubleDisplacement8();
	UINT32 am2PCDoubleDisplacement16();
	UINT32 bam2PCDoubleDisplacement16();
	UINT32 am2PCDoubleDisplacement32();
	UINT32 bam2PCDoubleDisplacement32();
	UINT32 am2DirectAddress();
	UINT32 bam2DirectAddress();
	UINT32 am2DirectAddressIndexed();
	UINT32 bam2DirectAddressIndexed();
	UINT32 am2DirectAddressDeferred();
	UINT32 bam2DirectAddressDeferred();
	UINT32 am2DirectAddressDeferredIndexed();
	UINT32 bam2DirectAddressDeferredIndexed();
	UINT32 am2Immediate();
	UINT32 am2ImmediateQuick();
	UINT32 am2Error1();
	UINT32 am2Error2();
	UINT32 am2Error3();
	UINT32 am2Error4();
	UINT32 am2Error5();
	UINT32 bam2Error1();
	UINT32 bam2Error2();
	UINT32 bam2Error3();
	UINT32 bam2Error4();
	UINT32 bam2Error5();
	UINT32 bam2Error6();
	UINT32 am2Group7a();
	UINT32 bam2Group7a();
	UINT32 am2Group6();
	UINT32 bam2Group6();
	UINT32 am2Group7();
	UINT32 bam2Group7();
	UINT32 am3Register();
	UINT32 am3RegisterIndirect();
	UINT32 am3RegisterIndirectIndexed();
	UINT32 am3Autoincrement();
	UINT32 am3Autodecrement();
	UINT32 am3Displacement8();
	UINT32 am3Displacement16();
	UINT32 am3Displacement32();
	UINT32 am3DisplacementIndexed8();
	UINT32 am3DisplacementIndexed16();
	UINT32 am3DisplacementIndexed32();
	UINT32 am3PCDisplacement8();
	UINT32 am3PCDisplacement16();
	UINT32 am3PCDisplacement32();
	UINT32 am3PCDisplacementIndexed8();
	UINT32 am3PCDisplacementIndexed16();
	UINT32 am3PCDisplacementIndexed32();
	UINT32 am3DisplacementIndirect8();
	UINT32 am3DisplacementIndirect16();
	UINT32 am3DisplacementIndirect32();
	UINT32 am3DisplacementIndirectIndexed8();
	UINT32 am3DisplacementIndirectIndexed16();
	UINT32 am3DisplacementIndirectIndexed32();
	UINT32 am3PCDisplacementIndirect8();
	UINT32 am3PCDisplacementIndirect16();
	UINT32 am3PCDisplacementIndirect32();
	UINT32 am3PCDisplacementIndirectIndexed8();
	UINT32 am3PCDisplacementIndirectIndexed16();
	UINT32 am3PCDisplacementIndirectIndexed32();
	UINT32 am3DoubleDisplacement8();
	UINT32 am3DoubleDisplacement16();
	UINT32 am3DoubleDisplacement32();
	UINT32 am3PCDoubleDisplacement8();
	UINT32 am3PCDoubleDisplacement16();
	UINT32 am3PCDoubleDisplacement32();
	UINT32 am3DirectAddress();
	UINT32 am3DirectAddressIndexed();
	UINT32 am3DirectAddressDeferred();
	UINT32 am3DirectAddressDeferredIndexed();
	UINT32 am3Immediate();
	UINT32 am3ImmediateQuick();
	UINT32 am3Error1();
	UINT32 am3Error2();
	UINT32 am3Error3();
	UINT32 am3Error4();
	UINT32 am3Error5();
	UINT32 am3Group7a();
	UINT32 am3Group6();
	UINT32 am3Group7();
	UINT32 ReadAM();
	UINT32 BitReadAM();
	UINT32 ReadAMAddress();
	UINT32 BitReadAMAddress();
	UINT32 WriteAM();
	void F12DecodeFirstOperand(am_func DecodeOp1, UINT8 dim1);
	void F12WriteSecondOperand(UINT8 dim2);
	void F12DecodeOperands(am_func DecodeOp1, UINT8 dim1, am_func DecodeOp2, UINT8 dim2);
	UINT32 opADDB();
	UINT32 opADDH();
	UINT32 opADDW();
	UINT32 opADDCB();
	UINT32 opADDCH();
	UINT32 opADDCW();
	UINT32 opANDB();
	UINT32 opANDH();
	UINT32 opANDW();
	UINT32 opCALL();
	UINT32 opCHKAR();
	UINT32 opCHKAW();
	UINT32 opCHKAE();
	UINT32 opCHLVL();
	UINT32 opCLR1();
	UINT32 opCMPB();
	UINT32 opCMPH();
	UINT32 opCMPW();
	UINT32 opDIVB();
	UINT32 opDIVH();
	UINT32 opDIVW();
	UINT32 opDIVX();
	UINT32 opDIVUX();
	UINT32 opDIVUB();
	UINT32 opDIVUH();
	UINT32 opDIVUW();
	UINT32 opINB();
	UINT32 opINH();
	UINT32 opINW();
	UINT32 opLDPR();
	UINT32 opLDTASK();
	UINT32 opMOVD();
	UINT32 opMOVB();
	UINT32 opMOVH();
	UINT32 opMOVW();
	UINT32 opMOVEAB();
	UINT32 opMOVEAH();
	UINT32 opMOVEAW();
	UINT32 opMOVSBH();
	UINT32 opMOVSBW();
	UINT32 opMOVSHW();
	UINT32 opMOVTHB();
	UINT32 opMOVTWB();
	UINT32 opMOVTWH();
	UINT32 opMOVZBH();
	UINT32 opMOVZBW();
	UINT32 opMOVZHW();
	UINT32 opMULB();
	UINT32 opMULH();
	UINT32 opMULW();
	UINT32 opMULUB();
	UINT32 opMULUH();
	UINT32 opMULUW();
	UINT32 opNEGB();
	UINT32 opNEGH();
	UINT32 opNEGW();
	UINT32 opNOTB();
	UINT32 opNOTH();
	UINT32 opNOTW();
	UINT32 opNOT1();
	UINT32 opORB();
	UINT32 opORH();
	UINT32 opORW();
	UINT32 opOUTB();
	UINT32 opOUTH();
	UINT32 opOUTW();
	UINT32 opREMB();
	UINT32 opREMH();
	UINT32 opREMW();
	UINT32 opREMUB();
	UINT32 opREMUH();
	UINT32 opREMUW();
	UINT32 opROTB();
	UINT32 opROTH();
	UINT32 opROTW();
	UINT32 opROTCB();
	UINT32 opROTCH();
	UINT32 opROTCW();
	UINT32 opRVBIT();
	UINT32 opRVBYT();
	UINT32 opSET1();
	UINT32 opSETF();
	UINT32 opSHAB();
	UINT32 opSHAH();
	UINT32 opSHAW();
	UINT32 opSHLB();
	UINT32 opSHLH();
	UINT32 opSHLW();
	UINT32 opSTPR();
	UINT32 opSUBB();
	UINT32 opSUBH();
	UINT32 opSUBW();
	UINT32 opSUBCB();
	UINT32 opSUBCH();
	UINT32 opSUBCW();
	UINT32 opTEST1();
	UINT32 opUPDPSWW();
	UINT32 opUPDPSWH();
	UINT32 opXCHB();
	UINT32 opXCHH();
	UINT32 opXCHW();
	UINT32 opXORB();
	UINT32 opXORH();
	UINT32 opXORW();
	UINT32 opMULX();
	UINT32 opMULUX();
	void F2DecodeFirstOperand(am_func DecodeOp1, UINT8 dim1);
	void F2DecodeSecondOperand(am_func DecodeOp2, UINT8 dim2);
	void F2WriteSecondOperand(UINT8 dim2);
	UINT32 opCVTWS();
	UINT32 opCVTSW();
	UINT32 opMOVFS();
	UINT32 opNEGFS();
	UINT32 opABSFS();
	UINT32 opADDFS();
	UINT32 opSUBFS();
	UINT32 opMULFS();
	UINT32 opDIVFS();
	UINT32 opSCLFS();
	UINT32 opCMPF();
	UINT32 op5FUNHANDLED();
	UINT32 op5CUNHANDLED();
	UINT32 op5F();
	UINT32 op5C();
	UINT32 opINCB();
	UINT32 opINCH();
	UINT32 opINCW();
	UINT32 opDECB();
	UINT32 opDECH();
	UINT32 opDECW();
	UINT32 opJMP();
	UINT32 opJSR();
	UINT32 opPREPARE();
	UINT32 opRET();
	UINT32 opTRAP();
	UINT32 opRETIU();
	UINT32 opRETIS();
	UINT32 opSTTASK();
	UINT32 opGETPSW();
	UINT32 opTASI();
	UINT32 opCLRTLB();
	UINT32 opPOPM();
	UINT32 opPUSHM();
	UINT32 opTESTB();
	UINT32 opTESTH();
	UINT32 opTESTW();
	UINT32 opPUSH();
	UINT32 opPOP();
	UINT32 opINCB_0();
	UINT32 opINCB_1();
	UINT32 opINCH_0();
	UINT32 opINCH_1();
	UINT32 opINCW_0();
	UINT32 opINCW_1();
	UINT32 opDECB_0();
	UINT32 opDECB_1();
	UINT32 opDECH_0();
	UINT32 opDECH_1();
	UINT32 opDECW_0();
	UINT32 opDECW_1();
	UINT32 opJMP_0();
	UINT32 opJMP_1();
	UINT32 opJSR_0();
	UINT32 opJSR_1();
	UINT32 opPREPARE_0();
	UINT32 opPREPARE_1();
	UINT32 opRET_0();
	UINT32 opRET_1();
	UINT32 opTRAP_0();
	UINT32 opTRAP_1();
	UINT32 opRETIU_0();
	UINT32 opRETIU_1();
	UINT32 opRETIS_0();
	UINT32 opRETIS_1();
	UINT32 opGETPSW_0();
	UINT32 opGETPSW_1();
	UINT32 opTASI_0();
	UINT32 opTASI_1();
	UINT32 opCLRTLB_0();
	UINT32 opCLRTLB_1();
	UINT32 opPOPM_0();
	UINT32 opPOPM_1();
	UINT32 opPUSHM_0();
	UINT32 opPUSHM_1();
	UINT32 opTESTB_0();
	UINT32 opTESTB_1();
	UINT32 opTESTH_0();
	UINT32 opTESTH_1();
	UINT32 opTESTW_0();
	UINT32 opTESTW_1();
	UINT32 opPUSH_0();
	UINT32 opPUSH_1();
	UINT32 opPOP_0();
	UINT32 opPOP_1();
	UINT32 opSTTASK_0();
	UINT32 opSTTASK_1();
	UINT32 opBGT8();
	UINT32 opBGT16();
	UINT32 opBGE8();
	UINT32 opBGE16();
	UINT32 opBLT8();
	UINT32 opBLT16();
	UINT32 opBLE8();
	UINT32 opBLE16();
	UINT32 opBH8();
	UINT32 opBH16();
	UINT32 opBNH8();
	UINT32 opBNH16();
	UINT32 opBNL8();
	UINT32 opBNL16();
	UINT32 opBL8();
	UINT32 opBL16();
	UINT32 opBNE8();
	UINT32 opBNE16();
	UINT32 opBE8();
	UINT32 opBE16();
	UINT32 opBNV8();
	UINT32 opBNV16();
	UINT32 opBV8();
	UINT32 opBV16();
	UINT32 opBP8();
	UINT32 opBP16();
	UINT32 opBN8();
	UINT32 opBN16();
	UINT32 opBR8();
	UINT32 opBR16();
	UINT32 opBSR();
	UINT32 opBRK();
	UINT32 opBRKV();
	UINT32 opCLRTLBA();
	UINT32 opDISPOSE();
	UINT32 opHALT();
	UINT32 opNOP();
	UINT32 opRSR();
	UINT32 opTRAPFL();
	UINT32 opTB(int reg);
	UINT32 opDBGT(int reg);
	UINT32 opDBLE(int reg);
	UINT32 opDBGE(int reg);
	UINT32 opDBLT(int reg);
	UINT32 opDBH(int reg);
	UINT32 opDBNH(int reg);
	UINT32 opDBL(int reg);
	UINT32 opDBNL(int reg);
	UINT32 opDBE(int reg);
	UINT32 opDBNE(int reg);
	UINT32 opDBV(int reg);
	UINT32 opDBNV(int reg);
	UINT32 opDBN(int reg);
	UINT32 opDBP(int reg);
	UINT32 opDBR(int reg);
	UINT32 opC6();
	UINT32 opC7();
	void F7aDecodeOperands(am_func DecodeOp1, UINT8 dim1, am_func DecodeOp2, UINT8 dim2);
	void F7bDecodeFirstOperand(am_func DecodeOp1, UINT8 dim1);
	void F7bWriteSecondOperand(UINT8 dim2);
	void F7bDecodeOperands(am_func DecodeOp1, UINT8 dim1, am_func DecodeOp2, UINT8 dim2);
	void F7cDecodeOperands(am_func DecodeOp1, UINT8 dim1, am_func DecodeOp2, UINT8 dim2);
	UINT32 opCMPSTRB(UINT8 bFill, UINT8 bStop);
	UINT32 opCMPSTRH(UINT8 bFill, UINT8 bStop);
	UINT32 opMOVSTRUB(UINT8 bFill, UINT8 bStop);
	UINT32 opMOVSTRDB(UINT8 bFill, UINT8 bStop);
	UINT32 opMOVSTRUH(UINT8 bFill, UINT8 bStop);
	UINT32 opMOVSTRDH(UINT8 bFill, UINT8 bStop);
	UINT32 opSEARCHUB(UINT8 bSearch);
	UINT32 opSEARCHUH(UINT8 bSearch);
	UINT32 opSEARCHDB(UINT8 bSearch);
	UINT32 opSEARCHDH(UINT8 bSearch);
	UINT32 opSCHCUB();
	UINT32 opSCHCUH();
	UINT32 opSCHCDB();
	UINT32 opSCHCDH();
	UINT32 opSKPCUB();
	UINT32 opSKPCUH();
	UINT32 opSKPCDB();
	UINT32 opSKPCDH();
	UINT32 opCMPCB();
	UINT32 opCMPCH();
	UINT32 opCMPCFB();
	UINT32 opCMPCFH();
	UINT32 opCMPCSB();
	UINT32 opCMPCSH();
	UINT32 opMOVCUB();
	UINT32 opMOVCUH();
	UINT32 opMOVCFUB();
	UINT32 opMOVCFUH();
	UINT32 opMOVCSUB();
	UINT32 opMOVCSUH();
	UINT32 opMOVCDB();
	UINT32 opMOVCDH();
	UINT32 opMOVCFDB();
	UINT32 opMOVCFDH();
	UINT32 opEXTBFZ();
	UINT32 opEXTBFS();
	UINT32 opEXTBFL();
	UINT32 opSCHBS(UINT32 bSearch1);
	UINT32 opSCH0BSU();
	UINT32 opSCH1BSU();
	UINT32 opINSBFR();
	UINT32 opINSBFL();
	UINT32 opMOVBSD();
	UINT32 opMOVBSU();
	UINT32 opADDDC();
	UINT32 opSUBDC();
	UINT32 opSUBRDC();
	UINT32 opCVTDPZ();
	UINT32 opCVTDZP();
	UINT32 op58UNHANDLED();
	UINT32 op5AUNHANDLED();
	UINT32 op5BUNHANDLED();
	UINT32 op5DUNHANDLED();
	UINT32 op59UNHANDLED();
	UINT32 op58();
	UINT32 op5A();
	UINT32 op5B();
	UINT32 op5D();
	UINT32 op59();
	UINT32 opUNHANDLED();
=======
	inline uint32_t v60ReadPSW();
	inline void v60WritePSW(uint32_t newval);
	inline uint32_t v60_update_psw_for_exception(int is_interrupt, int target_level);

	uint32_t am1Register();
	uint32_t am1RegisterIndirect();
	uint32_t bam1RegisterIndirect();
	uint32_t am1RegisterIndirectIndexed();
	uint32_t bam1RegisterIndirectIndexed();
	uint32_t am1Autoincrement();
	uint32_t bam1Autoincrement();
	uint32_t am1Autodecrement();
	uint32_t bam1Autodecrement();
	uint32_t am1Displacement8();
	uint32_t bam1Displacement8();
	uint32_t am1Displacement16();
	uint32_t bam1Displacement16();
	uint32_t am1Displacement32();
	uint32_t bam1Displacement32();
	uint32_t am1DisplacementIndexed8();
	uint32_t bam1DisplacementIndexed8();
	uint32_t am1DisplacementIndexed16();
	uint32_t bam1DisplacementIndexed16();
	uint32_t am1DisplacementIndexed32();
	uint32_t bam1DisplacementIndexed32();
	uint32_t am1PCDisplacement8();
	uint32_t bam1PCDisplacement8();
	uint32_t am1PCDisplacement16();
	uint32_t bam1PCDisplacement16();
	uint32_t am1PCDisplacement32();
	uint32_t bam1PCDisplacement32();
	uint32_t am1PCDisplacementIndexed8();
	uint32_t bam1PCDisplacementIndexed8();
	uint32_t am1PCDisplacementIndexed16();
	uint32_t bam1PCDisplacementIndexed16();
	uint32_t am1PCDisplacementIndexed32();
	uint32_t bam1PCDisplacementIndexed32();
	uint32_t am1DisplacementIndirect8();
	uint32_t bam1DisplacementIndirect8();
	uint32_t am1DisplacementIndirect16();
	uint32_t bam1DisplacementIndirect16();
	uint32_t am1DisplacementIndirect32();
	uint32_t bam1DisplacementIndirect32();
	uint32_t am1DisplacementIndirectIndexed8();
	uint32_t bam1DisplacementIndirectIndexed8();
	uint32_t am1DisplacementIndirectIndexed16();
	uint32_t bam1DisplacementIndirectIndexed16();
	uint32_t am1DisplacementIndirectIndexed32();
	uint32_t bam1DisplacementIndirectIndexed32();
	uint32_t am1PCDisplacementIndirect8();
	uint32_t bam1PCDisplacementIndirect8();
	uint32_t am1PCDisplacementIndirect16();
	uint32_t bam1PCDisplacementIndirect16();
	uint32_t am1PCDisplacementIndirect32();
	uint32_t bam1PCDisplacementIndirect32();
	uint32_t am1PCDisplacementIndirectIndexed8();
	uint32_t bam1PCDisplacementIndirectIndexed8();
	uint32_t am1PCDisplacementIndirectIndexed16();
	uint32_t bam1PCDisplacementIndirectIndexed16();
	uint32_t am1PCDisplacementIndirectIndexed32();
	uint32_t bam1PCDisplacementIndirectIndexed32();
	uint32_t am1DoubleDisplacement8();
	uint32_t bam1DoubleDisplacement8();
	uint32_t am1DoubleDisplacement16();
	uint32_t bam1DoubleDisplacement16();
	uint32_t am1DoubleDisplacement32();
	uint32_t bam1DoubleDisplacement32();
	uint32_t am1PCDoubleDisplacement8();
	uint32_t bam1PCDoubleDisplacement8();
	uint32_t am1PCDoubleDisplacement16();
	uint32_t bam1PCDoubleDisplacement16();
	uint32_t am1PCDoubleDisplacement32();
	uint32_t bam1PCDoubleDisplacement32();
	uint32_t am1DirectAddress();
	uint32_t bam1DirectAddress();
	uint32_t am1DirectAddressIndexed();
	uint32_t bam1DirectAddressIndexed();
	uint32_t am1DirectAddressDeferred();
	uint32_t bam1DirectAddressDeferred();
	uint32_t am1DirectAddressDeferredIndexed();
	uint32_t bam1DirectAddressDeferredIndexed();
	uint32_t am1Immediate();
	uint32_t am1ImmediateQuick();
	uint32_t am1Error1();
	uint32_t bam1Error1();
	uint32_t am1Error2();
	uint32_t bam1Error2();
	uint32_t am1Error4();
	uint32_t bam1Error4();
	uint32_t am1Error5();
	uint32_t bam1Error5();
	uint32_t bam1Error6();
	uint32_t am1Group7a();
	uint32_t bam1Group7a();
	uint32_t am1Group6();
	uint32_t bam1Group6();
	uint32_t am1Group7();
	uint32_t bam1Group7();
	uint32_t am2Register();
	uint32_t am2RegisterIndirect();
	uint32_t bam2RegisterIndirect();
	uint32_t am2RegisterIndirectIndexed();
	uint32_t bam2RegisterIndirectIndexed();
	uint32_t am2Autoincrement();
	uint32_t bam2Autoincrement();
	uint32_t am2Autodecrement();
	uint32_t bam2Autodecrement();
	uint32_t am2Displacement8();
	uint32_t bam2Displacement8();
	uint32_t am2Displacement16();
	uint32_t bam2Displacement16();
	uint32_t am2Displacement32();
	uint32_t bam2Displacement32();
	uint32_t am2DisplacementIndexed8();
	uint32_t bam2DisplacementIndexed8();
	uint32_t am2DisplacementIndexed16();
	uint32_t bam2DisplacementIndexed16();
	uint32_t am2DisplacementIndexed32();
	uint32_t bam2DisplacementIndexed32();
	uint32_t am2PCDisplacement8();
	uint32_t bam2PCDisplacement8();
	uint32_t am2PCDisplacement16();
	uint32_t bam2PCDisplacement16();
	uint32_t am2PCDisplacement32();
	uint32_t bam2PCDisplacement32();
	uint32_t am2PCDisplacementIndexed8();
	uint32_t bam2PCDisplacementIndexed8();
	uint32_t am2PCDisplacementIndexed16();
	uint32_t bam2PCDisplacementIndexed16();
	uint32_t am2PCDisplacementIndexed32();
	uint32_t bam2PCDisplacementIndexed32();
	uint32_t am2DisplacementIndirect8();
	uint32_t bam2DisplacementIndirect8();
	uint32_t am2DisplacementIndirect16();
	uint32_t bam2DisplacementIndirect16();
	uint32_t am2DisplacementIndirect32();
	uint32_t bam2DisplacementIndirect32();
	uint32_t am2DisplacementIndirectIndexed8();
	uint32_t bam2DisplacementIndirectIndexed8();
	uint32_t am2DisplacementIndirectIndexed16();
	uint32_t bam2DisplacementIndirectIndexed16();
	uint32_t am2DisplacementIndirectIndexed32();
	uint32_t bam2DisplacementIndirectIndexed32();
	uint32_t am2PCDisplacementIndirect8();
	uint32_t bam2PCDisplacementIndirect8();
	uint32_t am2PCDisplacementIndirect16();
	uint32_t bam2PCDisplacementIndirect16();
	uint32_t am2PCDisplacementIndirect32();
	uint32_t bam2PCDisplacementIndirect32();
	uint32_t am2PCDisplacementIndirectIndexed8();
	uint32_t bam2PCDisplacementIndirectIndexed8();
	uint32_t am2PCDisplacementIndirectIndexed16();
	uint32_t bam2PCDisplacementIndirectIndexed16();
	uint32_t am2PCDisplacementIndirectIndexed32();
	uint32_t bam2PCDisplacementIndirectIndexed32();
	uint32_t am2DoubleDisplacement8();
	uint32_t bam2DoubleDisplacement8();
	uint32_t am2DoubleDisplacement16();
	uint32_t bam2DoubleDisplacement16();
	uint32_t am2DoubleDisplacement32();
	uint32_t bam2DoubleDisplacement32();
	uint32_t am2PCDoubleDisplacement8();
	uint32_t bam2PCDoubleDisplacement8();
	uint32_t am2PCDoubleDisplacement16();
	uint32_t bam2PCDoubleDisplacement16();
	uint32_t am2PCDoubleDisplacement32();
	uint32_t bam2PCDoubleDisplacement32();
	uint32_t am2DirectAddress();
	uint32_t bam2DirectAddress();
	uint32_t am2DirectAddressIndexed();
	uint32_t bam2DirectAddressIndexed();
	uint32_t am2DirectAddressDeferred();
	uint32_t bam2DirectAddressDeferred();
	uint32_t am2DirectAddressDeferredIndexed();
	uint32_t bam2DirectAddressDeferredIndexed();
	uint32_t am2Immediate();
	uint32_t am2ImmediateQuick();
	uint32_t am2Error1();
	uint32_t am2Error2();
	uint32_t am2Error4();
	uint32_t am2Error5();
	uint32_t bam2Error1();
	uint32_t bam2Error2();
	uint32_t bam2Error4();
	uint32_t bam2Error5();
	uint32_t bam2Error6();
	uint32_t am2Group7a();
	uint32_t bam2Group7a();
	uint32_t am2Group6();
	uint32_t bam2Group6();
	uint32_t am2Group7();
	uint32_t bam2Group7();
	uint32_t am3Register();
	uint32_t am3RegisterIndirect();
	uint32_t am3RegisterIndirectIndexed();
	uint32_t am3Autoincrement();
	uint32_t am3Autodecrement();
	uint32_t am3Displacement8();
	uint32_t am3Displacement16();
	uint32_t am3Displacement32();
	uint32_t am3DisplacementIndexed8();
	uint32_t am3DisplacementIndexed16();
	uint32_t am3DisplacementIndexed32();
	uint32_t am3PCDisplacement8();
	uint32_t am3PCDisplacement16();
	uint32_t am3PCDisplacement32();
	uint32_t am3PCDisplacementIndexed8();
	uint32_t am3PCDisplacementIndexed16();
	uint32_t am3PCDisplacementIndexed32();
	uint32_t am3DisplacementIndirect8();
	uint32_t am3DisplacementIndirect16();
	uint32_t am3DisplacementIndirect32();
	uint32_t am3DisplacementIndirectIndexed8();
	uint32_t am3DisplacementIndirectIndexed16();
	uint32_t am3DisplacementIndirectIndexed32();
	uint32_t am3PCDisplacementIndirect8();
	uint32_t am3PCDisplacementIndirect16();
	uint32_t am3PCDisplacementIndirect32();
	uint32_t am3PCDisplacementIndirectIndexed8();
	uint32_t am3PCDisplacementIndirectIndexed16();
	uint32_t am3PCDisplacementIndirectIndexed32();
	uint32_t am3DoubleDisplacement8();
	uint32_t am3DoubleDisplacement16();
	uint32_t am3DoubleDisplacement32();
	uint32_t am3PCDoubleDisplacement8();
	uint32_t am3PCDoubleDisplacement16();
	uint32_t am3PCDoubleDisplacement32();
	uint32_t am3DirectAddress();
	uint32_t am3DirectAddressIndexed();
	uint32_t am3DirectAddressDeferred();
	uint32_t am3DirectAddressDeferredIndexed();
	uint32_t am3Immediate();
	uint32_t am3ImmediateQuick();
	uint32_t am3Error1();
	uint32_t am3Error2();
	uint32_t am3Error4();
	uint32_t am3Error5();
	uint32_t am3Group7a();
	uint32_t am3Group6();
	uint32_t am3Group7();
	uint32_t ReadAM();
	uint32_t BitReadAM();
	uint32_t ReadAMAddress();
	uint32_t BitReadAMAddress();
	uint32_t WriteAM();
	void F12DecodeFirstOperand(am_func DecodeOp1, uint8_t dim1);
	void F12WriteSecondOperand(uint8_t dim2);
	void F12DecodeOperands(am_func DecodeOp1, uint8_t dim1, am_func DecodeOp2, uint8_t dim2);
	uint32_t opADDB();
	uint32_t opADDH();
	uint32_t opADDW();
	uint32_t opADDCB();
	uint32_t opADDCH();
	uint32_t opADDCW();
	uint32_t opANDB();
	uint32_t opANDH();
	uint32_t opANDW();
	uint32_t opCALL();
	uint32_t opCHKAR();
	uint32_t opCHKAW();
	uint32_t opCHKAE();
	uint32_t opCHLVL();
	uint32_t opCLR1();
	uint32_t opCMPB();
	uint32_t opCMPH();
	uint32_t opCMPW();
	uint32_t opDIVB();
	uint32_t opDIVH();
	uint32_t opDIVW();
	uint32_t opDIVX();
	uint32_t opDIVUX();
	uint32_t opDIVUB();
	uint32_t opDIVUH();
	uint32_t opDIVUW();
	uint32_t opINB();
	uint32_t opINH();
	uint32_t opINW();
	uint32_t opLDPR();
	uint32_t opLDTASK();
	uint32_t opMOVD();
	uint32_t opMOVB();
	uint32_t opMOVH();
	uint32_t opMOVW();
	uint32_t opMOVEAB();
	uint32_t opMOVEAH();
	uint32_t opMOVEAW();
	uint32_t opMOVSBH();
	uint32_t opMOVSBW();
	uint32_t opMOVSHW();
	uint32_t opMOVTHB();
	uint32_t opMOVTWB();
	uint32_t opMOVTWH();
	uint32_t opMOVZBH();
	uint32_t opMOVZBW();
	uint32_t opMOVZHW();
	uint32_t opMULB();
	uint32_t opMULH();
	uint32_t opMULW();
	uint32_t opMULUB();
	uint32_t opMULUH();
	uint32_t opMULUW();
	uint32_t opNEGB();
	uint32_t opNEGH();
	uint32_t opNEGW();
	uint32_t opNOTB();
	uint32_t opNOTH();
	uint32_t opNOTW();
	uint32_t opNOT1();
	uint32_t opORB();
	uint32_t opORH();
	uint32_t opORW();
	uint32_t opOUTB();
	uint32_t opOUTH();
	uint32_t opOUTW();
	uint32_t opREMB();
	uint32_t opREMH();
	uint32_t opREMW();
	uint32_t opREMUB();
	uint32_t opREMUH();
	uint32_t opREMUW();
	uint32_t opROTB();
	uint32_t opROTH();
	uint32_t opROTW();
	uint32_t opROTCB();
	uint32_t opROTCH();
	uint32_t opROTCW();
	uint32_t opRVBIT();
	uint32_t opRVBYT();
	uint32_t opSET1();
	uint32_t opSETF();
	uint32_t opSHAB();
	uint32_t opSHAH();
	uint32_t opSHAW();
	uint32_t opSHLB();
	uint32_t opSHLH();
	uint32_t opSHLW();
	uint32_t opSTPR();
	uint32_t opSUBB();
	uint32_t opSUBH();
	uint32_t opSUBW();
	uint32_t opSUBCB();
	uint32_t opSUBCH();
	uint32_t opSUBCW();
	uint32_t opTEST1();
	uint32_t opUPDPSWW();
	uint32_t opUPDPSWH();
	uint32_t opXCHB();
	uint32_t opXCHH();
	uint32_t opXCHW();
	uint32_t opXORB();
	uint32_t opXORH();
	uint32_t opXORW();
	uint32_t opMULX();
	uint32_t opMULUX();
	void F2DecodeFirstOperand(am_func DecodeOp1, uint8_t dim1);
	void F2DecodeSecondOperand(am_func DecodeOp2, uint8_t dim2);
	void F2WriteSecondOperand(uint8_t dim2);
	uint32_t opCVTWS();
	uint32_t opCVTSW();
	uint32_t opMOVFS();
	uint32_t opNEGFS();
	uint32_t opABSFS();
	uint32_t opADDFS();
	uint32_t opSUBFS();
	uint32_t opMULFS();
	uint32_t opDIVFS();
	uint32_t opSCLFS();
	uint32_t opCMPF();
	uint32_t op5FUNHANDLED();
	uint32_t op5CUNHANDLED();
	uint32_t op5F();
	uint32_t op5C();
	uint32_t opINCB();
	uint32_t opINCH();
	uint32_t opINCW();
	uint32_t opDECB();
	uint32_t opDECH();
	uint32_t opDECW();
	uint32_t opJMP();
	uint32_t opJSR();
	uint32_t opPREPARE();
	uint32_t opRET();
	uint32_t opTRAP();
	uint32_t opRETIU();
	uint32_t opRETIS();
	uint32_t opSTTASK();
	uint32_t opGETPSW();
	uint32_t opTASI();
	uint32_t opCLRTLB();
	uint32_t opPOPM();
	uint32_t opPUSHM();
	uint32_t opTESTB();
	uint32_t opTESTH();
	uint32_t opTESTW();
	uint32_t opPUSH();
	uint32_t opPOP();
	uint32_t opINCB_0();
	uint32_t opINCB_1();
	uint32_t opINCH_0();
	uint32_t opINCH_1();
	uint32_t opINCW_0();
	uint32_t opINCW_1();
	uint32_t opDECB_0();
	uint32_t opDECB_1();
	uint32_t opDECH_0();
	uint32_t opDECH_1();
	uint32_t opDECW_0();
	uint32_t opDECW_1();
	uint32_t opJMP_0();
	uint32_t opJMP_1();
	uint32_t opJSR_0();
	uint32_t opJSR_1();
	uint32_t opPREPARE_0();
	uint32_t opPREPARE_1();
	uint32_t opRET_0();
	uint32_t opRET_1();
	uint32_t opTRAP_0();
	uint32_t opTRAP_1();
	uint32_t opRETIU_0();
	uint32_t opRETIU_1();
	uint32_t opRETIS_0();
	uint32_t opRETIS_1();
	uint32_t opGETPSW_0();
	uint32_t opGETPSW_1();
	uint32_t opTASI_0();
	uint32_t opTASI_1();
	uint32_t opCLRTLB_0();
	uint32_t opCLRTLB_1();
	uint32_t opPOPM_0();
	uint32_t opPOPM_1();
	uint32_t opPUSHM_0();
	uint32_t opPUSHM_1();
	uint32_t opTESTB_0();
	uint32_t opTESTB_1();
	uint32_t opTESTH_0();
	uint32_t opTESTH_1();
	uint32_t opTESTW_0();
	uint32_t opTESTW_1();
	uint32_t opPUSH_0();
	uint32_t opPUSH_1();
	uint32_t opPOP_0();
	uint32_t opPOP_1();
	uint32_t opSTTASK_0();
	uint32_t opSTTASK_1();
	uint32_t opBGT8();
	uint32_t opBGT16();
	uint32_t opBGE8();
	uint32_t opBGE16();
	uint32_t opBLT8();
	uint32_t opBLT16();
	uint32_t opBLE8();
	uint32_t opBLE16();
	uint32_t opBH8();
	uint32_t opBH16();
	uint32_t opBNH8();
	uint32_t opBNH16();
	uint32_t opBNL8();
	uint32_t opBNL16();
	uint32_t opBL8();
	uint32_t opBL16();
	uint32_t opBNE8();
	uint32_t opBNE16();
	uint32_t opBE8();
	uint32_t opBE16();
	uint32_t opBNV8();
	uint32_t opBNV16();
	uint32_t opBV8();
	uint32_t opBV16();
	uint32_t opBP8();
	uint32_t opBP16();
	uint32_t opBN8();
	uint32_t opBN16();
	uint32_t opBR8();
	uint32_t opBR16();
	uint32_t opBSR();
	uint32_t opBRK();
	uint32_t opBRKV();
	uint32_t opCLRTLBA();
	uint32_t opDISPOSE();
	uint32_t opHALT();
	uint32_t opNOP();
	uint32_t opRSR();
	uint32_t opTRAPFL();
	uint32_t opTB(int reg);
	uint32_t opDBGT(int reg);
	uint32_t opDBLE(int reg);
	uint32_t opDBGE(int reg);
	uint32_t opDBLT(int reg);
	uint32_t opDBH(int reg);
	uint32_t opDBNH(int reg);
	uint32_t opDBL(int reg);
	uint32_t opDBNL(int reg);
	uint32_t opDBE(int reg);
	uint32_t opDBNE(int reg);
	uint32_t opDBV(int reg);
	uint32_t opDBNV(int reg);
	uint32_t opDBN(int reg);
	uint32_t opDBP(int reg);
	uint32_t opDBR(int reg);
	uint32_t opC6();
	uint32_t opC7();
	void F7aDecodeOperands(am_func DecodeOp1, uint8_t dim1, am_func DecodeOp2, uint8_t dim2);
	void F7bDecodeFirstOperand(am_func DecodeOp1, uint8_t dim1);
	void F7bWriteSecondOperand(uint8_t dim2);
	void F7bDecodeOperands(am_func DecodeOp1, uint8_t dim1, am_func DecodeOp2, uint8_t dim2);
	void F7cDecodeOperands(am_func DecodeOp1, uint8_t dim1, am_func DecodeOp2, uint8_t dim2);
	uint32_t opCMPSTRB(uint8_t bFill, uint8_t bStop);
	uint32_t opCMPSTRH(uint8_t bFill, uint8_t bStop);
	uint32_t opMOVSTRUB(uint8_t bFill, uint8_t bStop);
	uint32_t opMOVSTRDB(uint8_t bFill, uint8_t bStop);
	uint32_t opMOVSTRUH(uint8_t bFill, uint8_t bStop);
	uint32_t opMOVSTRDH(uint8_t bFill, uint8_t bStop);
	uint32_t opSEARCHUB(uint8_t bSearch);
	uint32_t opSEARCHUH(uint8_t bSearch);
	uint32_t opSEARCHDB(uint8_t bSearch);
	uint32_t opSEARCHDH(uint8_t bSearch);
	uint32_t opSCHCUB();
	uint32_t opSCHCUH();
	uint32_t opSCHCDB();
	uint32_t opSCHCDH();
	uint32_t opSKPCUB();
	uint32_t opSKPCUH();
	uint32_t opSKPCDB();
	uint32_t opSKPCDH();
	uint32_t opCMPCB();
	uint32_t opCMPCH();
	uint32_t opCMPCFB();
	uint32_t opCMPCFH();
	uint32_t opCMPCSB();
	uint32_t opCMPCSH();
	uint32_t opMOVCUB();
	uint32_t opMOVCUH();
	uint32_t opMOVCFUB();
	uint32_t opMOVCFUH();
	uint32_t opMOVCSUB();
	uint32_t opMOVCSUH();
	uint32_t opMOVCDB();
	uint32_t opMOVCDH();
	uint32_t opMOVCFDB();
	uint32_t opMOVCFDH();
	uint32_t opEXTBFZ();
	uint32_t opEXTBFS();
	uint32_t opEXTBFL();
	uint32_t opSCHBS(uint32_t bSearch1);
	uint32_t opSCH0BSU();
	uint32_t opSCH1BSU();
	uint32_t opINSBFR();
	uint32_t opINSBFL();
	uint32_t opMOVBSD();
	uint32_t opMOVBSU();
	uint32_t opADDDC();
	uint32_t opSUBDC();
	uint32_t opSUBRDC();
	uint32_t opCVTDPZ();
	uint32_t opCVTDZP();
	uint32_t op58UNHANDLED();
	uint32_t op5AUNHANDLED();
	uint32_t op5BUNHANDLED();
	uint32_t op5DUNHANDLED();
	uint32_t op59UNHANDLED();
	uint32_t op58();
	uint32_t op5A();
	uint32_t op5B();
	uint32_t op5D();
	uint32_t op59();
	uint32_t opUNHANDLED();
>>>>>>> upstream/master
	void v60_do_irq(int vector);
	void v60_try_irq();

};


class v70_device : public v60_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	v70_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

protected:
	virtual offs_t disasm_disassemble(char *buffer, offs_t pc, const UINT8 *oprom, const UINT8 *opram, UINT32 options);
};


extern const device_type V60;
extern const device_type V70;


#endif /* __V60_H__ */
=======
	v70_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

protected:
	virtual offs_t disasm_disassemble(std::ostream &stream, offs_t pc, const uint8_t *oprom, const uint8_t *opram, uint32_t options) override;
};


DECLARE_DEVICE_TYPE(V60, v60_device)
DECLARE_DEVICE_TYPE(V70, v70_device)

#endif // MAME_CPU_V60_V60_H
>>>>>>> upstream/master
