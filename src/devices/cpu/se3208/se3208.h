// license:BSD-3-Clause
// copyright-holders:ElSemi
<<<<<<< HEAD
=======
#ifndef MAME_CPU_SE3208_SE3208_H
#define MAME_CPU_SE3208_SE3208_H

#pragma once
>>>>>>> upstream/master

enum
{
	SE3208_PC=1, SE3208_SR, SE3208_ER, SE3208_SP,SE3208_PPC,
	SE3208_R0, SE3208_R1, SE3208_R2, SE3208_R3, SE3208_R4, SE3208_R5, SE3208_R6, SE3208_R7
};

#define SE3208_INT  0


class se3208_device :  public cpu_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	se3208_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

protected:
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
	virtual const address_space_config *memory_space_config(address_spacenum spacenum = AS_0) const { return (spacenum == AS_PROGRAM) ? &m_program_config : NULL; }

	// device_state_interface overrides
	void state_string_export(const device_state_entry &entry, std::string &str);

	// device_disasm_interface overrides
	virtual UINT32 disasm_min_opcode_bytes() const { return 2; }
	virtual UINT32 disasm_max_opcode_bytes() const { return 2; }
	virtual offs_t disasm_disassemble(char *buffer, offs_t pc, const UINT8 *oprom, const UINT8 *opram, UINT32 options);
=======
	se3208_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

protected:
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
	virtual void state_string_export(const device_state_entry &entry, std::string &str) const override;

	// device_disasm_interface overrides
	virtual uint32_t disasm_min_opcode_bytes() const override { return 2; }
	virtual uint32_t disasm_max_opcode_bytes() const override { return 2; }
	virtual offs_t disasm_disassemble(std::ostream &stream, offs_t pc, const uint8_t *oprom, const uint8_t *opram, uint32_t options) override;
>>>>>>> upstream/master

private:
	address_space_config m_program_config;

	//GPR
<<<<<<< HEAD
	UINT32 m_R[8];
	//SPR
	UINT32 m_PC;
	UINT32 m_SR;
	UINT32 m_SP;
	UINT32 m_ER;
	UINT32 m_PPC;

	address_space *m_program;
	direct_read_data *m_direct;
	UINT8 m_IRQ;
	UINT8 m_NMI;

	int m_icount;

	inline UINT32 read_dword_unaligned(address_space &space, UINT32 address);
	inline UINT16 read_word_unaligned(address_space &space, UINT32 address);
	inline void write_dword_unaligned(address_space &space, UINT32 address, UINT32 data);
	inline void write_word_unaligned(address_space &space, UINT32 address, UINT16 data);
	inline UINT8 SE3208_Read8(UINT32 addr);
	inline UINT16 SE3208_Read16(UINT32 addr);
	inline UINT32 SE3208_Read32(UINT32 addr);
	inline void SE3208_Write8(UINT32 addr,UINT8 val);
	inline void SE3208_Write16(UINT32 addr,UINT16 val);
	inline void SE3208_Write32(UINT32 addr,UINT32 val);
	inline UINT32 AddWithFlags(UINT32 a,UINT32 b);
	inline UINT32 SubWithFlags(UINT32 a,UINT32 b);
	inline UINT32 AdcWithFlags(UINT32 a,UINT32 b);
	inline UINT32 SbcWithFlags(UINT32 a,UINT32 b);
	inline UINT32 MulWithFlags(UINT32 a,UINT32 b);
	inline UINT32 NegWithFlags(UINT32 a);
	inline UINT32 AsrWithFlags(UINT32 Val, UINT8 By);
	inline UINT32 LsrWithFlags(UINT32 Val, UINT8 By);
	inline UINT32 AslWithFlags(UINT32 Val, UINT8 By);
	inline void PushVal(UINT32 Val);
	inline UINT32 PopVal();

	typedef void (se3208_device::*_OP)(UINT16 Opcode);
	_OP OpTable[0x10000];

	void INVALIDOP(UINT16 Opcode);
	void LDB(UINT16 Opcode);
	void STB(UINT16 Opcode);
	void LDS(UINT16 Opcode);
	void STS(UINT16 Opcode);
	void LD(UINT16 Opcode);
	void ST(UINT16 Opcode);
	void LDBU(UINT16 Opcode);
	void LDSU(UINT16 Opcode);
	void LERI(UINT16 Opcode);
	void LDSP(UINT16 Opcode);
	void STSP(UINT16 Opcode);
	void PUSH(UINT16 Opcode);
	void POP(UINT16 Opcode);
	void LEATOSP(UINT16 Opcode);
	void LEAFROMSP(UINT16 Opcode);
	void LEASPTOSP(UINT16 Opcode);
	void MOV(UINT16 Opcode);
	void LDI(UINT16 Opcode);
	void LDBSP(UINT16 Opcode);
	void STBSP(UINT16 Opcode);
	void LDSSP(UINT16 Opcode);
	void STSSP(UINT16 Opcode);
	void LDBUSP(UINT16 Opcode);
	void LDSUSP(UINT16 Opcode);
	void ADDI(UINT16 Opcode);
	void SUBI(UINT16 Opcode);
	void ADCI(UINT16 Opcode);
	void SBCI(UINT16 Opcode);
	void ANDI(UINT16 Opcode);
	void ORI(UINT16 Opcode);
	void XORI(UINT16 Opcode);
	void CMPI(UINT16 Opcode);
	void TSTI(UINT16 Opcode);
	void ADD(UINT16 Opcode);
	void SUB(UINT16 Opcode);
	void ADC(UINT16 Opcode);
	void SBC(UINT16 Opcode);
	void AND(UINT16 Opcode);
	void OR(UINT16 Opcode);
	void XOR(UINT16 Opcode);
	void CMP(UINT16 Opcode);
	void TST(UINT16 Opcode);
	void MULS(UINT16 Opcode);
	void NEG(UINT16 Opcode);
	void CALL(UINT16 Opcode);
	void JV(UINT16 Opcode);
	void JNV(UINT16 Opcode);
	void JC(UINT16 Opcode);
	void JNC(UINT16 Opcode);
	void JP(UINT16 Opcode);
	void JM(UINT16 Opcode);
	void JNZ(UINT16 Opcode);
	void JZ(UINT16 Opcode);
	void JGE(UINT16 Opcode);
	void JLE(UINT16 Opcode);
	void JHI(UINT16 Opcode);
	void JLS(UINT16 Opcode);
	void JGT(UINT16 Opcode);
	void JLT(UINT16 Opcode);
	void JMP(UINT16 Opcode);
	void JR(UINT16 Opcode);
	void CALLR(UINT16 Opcode);
	void ASR(UINT16 Opcode);
	void LSR(UINT16 Opcode);
	void ASL(UINT16 Opcode);
	void EXTB(UINT16 Opcode);
	void EXTS(UINT16 Opcode);
	void SET(UINT16 Opcode);
	void CLR(UINT16 Opcode);
	void SWI(UINT16 Opcode);
	void HALT(UINT16 Opcode);
	void MVTC(UINT16 Opcode);
	void MVFC(UINT16 Opcode);

	void BuildTable(void);
	_OP DecodeOp(UINT16 Opcode);
=======
	uint32_t m_R[8];
	//SPR
	uint32_t m_PC;
	uint32_t m_SR;
	uint32_t m_SP;
	uint32_t m_ER;
	uint32_t m_PPC;

	address_space *m_program;
	direct_read_data *m_direct;
	uint8_t m_IRQ;
	uint8_t m_NMI;

	int m_icount;

	inline uint32_t read_dword_unaligned(address_space &space, uint32_t address);
	inline uint16_t read_word_unaligned(address_space &space, uint32_t address);
	inline void write_dword_unaligned(address_space &space, uint32_t address, uint32_t data);
	inline void write_word_unaligned(address_space &space, uint32_t address, uint16_t data);
	inline uint8_t SE3208_Read8(uint32_t addr);
	inline uint16_t SE3208_Read16(uint32_t addr);
	inline uint32_t SE3208_Read32(uint32_t addr);
	inline void SE3208_Write8(uint32_t addr,uint8_t val);
	inline void SE3208_Write16(uint32_t addr,uint16_t val);
	inline void SE3208_Write32(uint32_t addr,uint32_t val);
	inline uint32_t AddWithFlags(uint32_t a,uint32_t b);
	inline uint32_t SubWithFlags(uint32_t a,uint32_t b);
	inline uint32_t AdcWithFlags(uint32_t a,uint32_t b);
	inline uint32_t SbcWithFlags(uint32_t a,uint32_t b);
	inline uint32_t MulWithFlags(uint32_t a,uint32_t b);
	inline uint32_t NegWithFlags(uint32_t a);
	inline uint32_t AsrWithFlags(uint32_t Val, uint8_t By);
	inline uint32_t LsrWithFlags(uint32_t Val, uint8_t By);
	inline uint32_t AslWithFlags(uint32_t Val, uint8_t By);
	inline void PushVal(uint32_t Val);
	inline uint32_t PopVal();

	typedef void (se3208_device::*OP)(uint16_t Opcode);
	OP OpTable[0x10000];

	void INVALIDOP(uint16_t Opcode);
	void LDB(uint16_t Opcode);
	void STB(uint16_t Opcode);
	void LDS(uint16_t Opcode);
	void STS(uint16_t Opcode);
	void LD(uint16_t Opcode);
	void ST(uint16_t Opcode);
	void LDBU(uint16_t Opcode);
	void LDSU(uint16_t Opcode);
	void LERI(uint16_t Opcode);
	void LDSP(uint16_t Opcode);
	void STSP(uint16_t Opcode);
	void PUSH(uint16_t Opcode);
	void POP(uint16_t Opcode);
	void LEATOSP(uint16_t Opcode);
	void LEAFROMSP(uint16_t Opcode);
	void LEASPTOSP(uint16_t Opcode);
	void MOV(uint16_t Opcode);
	void LDI(uint16_t Opcode);
	void LDBSP(uint16_t Opcode);
	void STBSP(uint16_t Opcode);
	void LDSSP(uint16_t Opcode);
	void STSSP(uint16_t Opcode);
	void LDBUSP(uint16_t Opcode);
	void LDSUSP(uint16_t Opcode);
	void ADDI(uint16_t Opcode);
	void SUBI(uint16_t Opcode);
	void ADCI(uint16_t Opcode);
	void SBCI(uint16_t Opcode);
	void ANDI(uint16_t Opcode);
	void ORI(uint16_t Opcode);
	void XORI(uint16_t Opcode);
	void CMPI(uint16_t Opcode);
	void TSTI(uint16_t Opcode);
	void ADD(uint16_t Opcode);
	void SUB(uint16_t Opcode);
	void ADC(uint16_t Opcode);
	void SBC(uint16_t Opcode);
	void AND(uint16_t Opcode);
	void OR(uint16_t Opcode);
	void XOR(uint16_t Opcode);
	void CMP(uint16_t Opcode);
	void TST(uint16_t Opcode);
	void MULS(uint16_t Opcode);
	void NEG(uint16_t Opcode);
	void CALL(uint16_t Opcode);
	void JV(uint16_t Opcode);
	void JNV(uint16_t Opcode);
	void JC(uint16_t Opcode);
	void JNC(uint16_t Opcode);
	void JP(uint16_t Opcode);
	void JM(uint16_t Opcode);
	void JNZ(uint16_t Opcode);
	void JZ(uint16_t Opcode);
	void JGE(uint16_t Opcode);
	void JLE(uint16_t Opcode);
	void JHI(uint16_t Opcode);
	void JLS(uint16_t Opcode);
	void JGT(uint16_t Opcode);
	void JLT(uint16_t Opcode);
	void JMP(uint16_t Opcode);
	void JR(uint16_t Opcode);
	void CALLR(uint16_t Opcode);
	void ASR(uint16_t Opcode);
	void LSR(uint16_t Opcode);
	void ASL(uint16_t Opcode);
	void EXTB(uint16_t Opcode);
	void EXTS(uint16_t Opcode);
	void SET(uint16_t Opcode);
	void CLR(uint16_t Opcode);
	void SWI(uint16_t Opcode);
	void HALT(uint16_t Opcode);
	void MVTC(uint16_t Opcode);
	void MVFC(uint16_t Opcode);

	void BuildTable(void);
	OP DecodeOp(uint16_t Opcode);
>>>>>>> upstream/master
	void SE3208_NMI();
	void SE3208_Interrupt();

};


<<<<<<< HEAD
extern const device_type SE3208;
=======
DECLARE_DEVICE_TYPE(SE3208, se3208_device)

#endif // MAME_CPU_SE3208_SE3208_H
>>>>>>> upstream/master
