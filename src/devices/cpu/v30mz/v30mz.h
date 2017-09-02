// license:BSD-3-Clause
// copyright-holders:Wilbert Pol,Bryan McPhail
<<<<<<< HEAD
#ifndef __V30MZ_H__
#define __V30MZ_H__
=======
#ifndef MAME_CPU_V32MZ_V30MZ_H
#define MAME_CPU_V32MZ_V30MZ_H
>>>>>>> upstream/master


struct nec_config
{
<<<<<<< HEAD
	const UINT8*    v25v35_decryptiontable; // internal decryption table
=======
	const uint8_t*    v25v35_decryptiontable; // internal decryption table
>>>>>>> upstream/master
};

enum
{
	NEC_PC=0,
	NEC_IP, NEC_AW, NEC_CW, NEC_DW, NEC_BW, NEC_SP, NEC_BP, NEC_IX, NEC_IY,
	NEC_FLAGS, NEC_ES, NEC_CS, NEC_SS, NEC_DS,
	NEC_VECTOR, NEC_PENDING
};


/////////////////////////////////////////////////////////////////

<<<<<<< HEAD
extern const device_type V30MZ;
=======
DECLARE_DEVICE_TYPE(V30MZ, v30mz_cpu_device)
>>>>>>> upstream/master

class v30mz_cpu_device : public cpu_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	v30mz_cpu_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

protected:
	// device-level overrides
	virtual void device_start();
	virtual void device_reset();

	// device_execute_interface overrides
	virtual UINT32 execute_min_cycles() const { return 1; }
	virtual UINT32 execute_max_cycles() const { return 80; }
	virtual UINT32 execute_input_lines() const { return 1; }
	virtual void execute_run();
	virtual void execute_set_input(int inputnum, int state);

	// device_memory_interface overrides
	virtual const address_space_config *memory_space_config(address_spacenum spacenum = AS_0) const { return (spacenum == AS_PROGRAM) ? &m_program_config : ( (spacenum == AS_IO) ? &m_io_config : NULL ); }

	// device_state_interface overrides
	void state_string_export(const device_state_entry &entry, std::string &str);

	// device_disasm_interface overrides
	virtual UINT32 disasm_min_opcode_bytes() const { return 1; }
	virtual UINT32 disasm_max_opcode_bytes() const { return 7; }
	virtual offs_t disasm_disassemble(char *buffer, offs_t pc, const UINT8 *oprom, const UINT8 *opram, UINT32 options);

	void interrupt(int int_num);

	inline UINT32 pc();
	// Accessing memory and io
	inline UINT8 read_byte(UINT32 addr);
	inline UINT16 read_word(UINT32 addr);
	inline void write_byte(UINT32 addr, UINT8 data);
	inline void write_word(UINT32 addr, UINT16 data);
	inline UINT8 read_port(UINT16 port);
	inline void write_port(UINT16 port, UINT8 data);

	// Executing instructions
	inline UINT8 fetch_op();
	inline UINT8 fetch();
	inline UINT16 fetch_word();
	inline UINT8 repx_op();

	// Cycles passed while executing instructions
	inline void CLK(UINT32 cycles);
	inline void CLKM(UINT32 cycles_reg, UINT32 cycles_mem);

	// Memory handling while executing instructions
	inline UINT32 default_base(int seg);
	inline UINT32 get_ea();
	inline void PutbackRMByte(UINT8 data);
	inline void PutbackRMWord(UINT16 data);
	inline void RegByte(UINT8 data);
	inline void RegWord(UINT16 data);
	inline UINT8 RegByte();
	inline UINT16 RegWord();
	inline UINT16 GetRMWord();
	inline UINT16 GetnextRMWord();
	inline UINT8 GetRMByte();
	inline void PutMemB(int seg, UINT16 offset, UINT8 data);
	inline void PutMemW(int seg, UINT16 offset, UINT16 data);
	inline UINT8 GetMemB(int seg, UINT16 offset);
	inline UINT16 GetMemW(int seg, UINT16 offset);
	inline void PutImmRMWord();
	inline void PutRMWord(UINT16 val);
	inline void PutRMByte(UINT8 val);
=======
	v30mz_cpu_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;

	// device_execute_interface overrides
	virtual uint32_t execute_min_cycles() const override { return 1; }
	virtual uint32_t execute_max_cycles() const override { return 80; }
	virtual uint32_t execute_input_lines() const override { return 1; }
	virtual void execute_run() override;
	virtual void execute_set_input(int inputnum, int state) override;

	// device_memory_interface overrides
	virtual space_config_vector memory_space_config() const override;

	// device_state_interface overrides
	virtual void state_string_export(const device_state_entry &entry, std::string &str) const override;

	// device_disasm_interface overrides
	virtual uint32_t disasm_min_opcode_bytes() const override { return 1; }
	virtual uint32_t disasm_max_opcode_bytes() const override { return 7; }
	virtual offs_t disasm_disassemble(std::ostream &stream, offs_t pc, const uint8_t *oprom, const uint8_t *opram, uint32_t options) override;

	void interrupt(int int_num);

	inline uint32_t pc();
	// Accessing memory and io
	inline uint8_t read_byte(uint32_t addr);
	inline uint16_t read_word(uint32_t addr);
	inline void write_byte(uint32_t addr, uint8_t data);
	inline void write_word(uint32_t addr, uint16_t data);
	inline uint8_t read_port(uint16_t port);
	inline void write_port(uint16_t port, uint8_t data);

	// Executing instructions
	inline uint8_t fetch_op();
	inline uint8_t fetch();
	inline uint16_t fetch_word();
	inline uint8_t repx_op();

	// Cycles passed while executing instructions
	inline void CLK(uint32_t cycles);
	inline void CLKM(uint32_t cycles_reg, uint32_t cycles_mem);

	// Memory handling while executing instructions
	inline uint32_t default_base(int seg);
	inline uint32_t get_ea();
	inline void PutbackRMByte(uint8_t data);
	inline void PutbackRMWord(uint16_t data);
	inline void RegByte(uint8_t data);
	inline void RegWord(uint16_t data);
	inline uint8_t RegByte();
	inline uint16_t RegWord();
	inline uint16_t GetRMWord();
	inline uint16_t GetnextRMWord();
	inline uint8_t GetRMByte();
	inline void PutMemB(int seg, uint16_t offset, uint8_t data);
	inline void PutMemW(int seg, uint16_t offset, uint16_t data);
	inline uint8_t GetMemB(int seg, uint16_t offset);
	inline uint16_t GetMemW(int seg, uint16_t offset);
	inline void PutImmRMWord();
	inline void PutRMWord(uint16_t val);
	inline void PutRMByte(uint8_t val);
>>>>>>> upstream/master
	inline void PutImmRMByte();
	inline void DEF_br8();
	inline void DEF_wr16();
	inline void DEF_r8b();
	inline void DEF_r16w();
	inline void DEF_ald8();
	inline void DEF_axd16();

	// Flags
<<<<<<< HEAD
	inline void set_CFB(UINT32 x);
	inline void set_CFW(UINT32 x);
	inline void set_AF(UINT32 x,UINT32 y,UINT32 z);
	inline void set_SF(UINT32 x);
	inline void set_ZF(UINT32 x);
	inline void set_PF(UINT32 x);
	inline void set_SZPF_Byte(UINT32 x);
	inline void set_SZPF_Word(UINT32 x);
	inline void set_OFW_Add(UINT32 x,UINT32 y,UINT32 z);
	inline void set_OFB_Add(UINT32 x,UINT32 y,UINT32 z);
	inline void set_OFW_Sub(UINT32 x,UINT32 y,UINT32 z);
	inline void set_OFB_Sub(UINT32 x,UINT32 y,UINT32 z);
	inline UINT16 CompressFlags();
	inline void ExpandFlags(UINT16 f);
=======
	inline void set_CFB(uint32_t x);
	inline void set_CFW(uint32_t x);
	inline void set_AF(uint32_t x,uint32_t y,uint32_t z);
	inline void set_SF(uint32_t x);
	inline void set_ZF(uint32_t x);
	inline void set_PF(uint32_t x);
	inline void set_SZPF_Byte(uint32_t x);
	inline void set_SZPF_Word(uint32_t x);
	inline void set_OFW_Add(uint32_t x,uint32_t y,uint32_t z);
	inline void set_OFB_Add(uint32_t x,uint32_t y,uint32_t z);
	inline void set_OFW_Sub(uint32_t x,uint32_t y,uint32_t z);
	inline void set_OFB_Sub(uint32_t x,uint32_t y,uint32_t z);
	inline uint16_t CompressFlags() const;
	inline void ExpandFlags(uint16_t f);
>>>>>>> upstream/master

	// rep instructions
	inline void i_insb();
	inline void i_insw();
	inline void i_outsb();
	inline void i_outsw();
	inline void i_movsb();
	inline void i_movsw();
	inline void i_cmpsb();
	inline void i_cmpsw();
	inline void i_stosb();
	inline void i_stosw();
	inline void i_lodsb();
	inline void i_lodsw();
	inline void i_scasb();
	inline void i_scasw();
	inline void i_popf();

	// sub implementations
	inline void ADDB();
	inline void ADDW();
	inline void SUBB();
	inline void SUBW();
	inline void ORB();
	inline void ORW();
	inline void ANDB();
	inline void ANDW();
	inline void XORB();
	inline void XORW();
	inline void ROL_BYTE();
	inline void ROL_WORD();
	inline void ROR_BYTE();
	inline void ROR_WORD();
	inline void ROLC_BYTE();
	inline void ROLC_WORD();
	inline void RORC_BYTE();
	inline void RORC_WORD();
<<<<<<< HEAD
	inline void SHL_BYTE(UINT8 c);
	inline void SHL_WORD(UINT8 c);
	inline void SHR_BYTE(UINT8 c);
	inline void SHR_WORD(UINT8 c);
	inline void SHRA_BYTE(UINT8 c);
	inline void SHRA_WORD(UINT8 c);
	inline void XchgAWReg(UINT8 reg);
	inline void IncWordReg(UINT8 reg);
	inline void DecWordReg(UINT8 reg);
	inline void PUSH(UINT16 data);
	inline UINT16 POP();
	inline void JMP(bool cond);
	inline void ADJ4(INT8 param1, INT8 param2);
	inline void ADJB(INT8 param1, INT8 param2);

protected:
=======
	inline void SHL_BYTE(uint8_t c);
	inline void SHL_WORD(uint8_t c);
	inline void SHR_BYTE(uint8_t c);
	inline void SHR_WORD(uint8_t c);
	inline void SHRA_BYTE(uint8_t c);
	inline void SHRA_WORD(uint8_t c);
	inline void XchgAWReg(uint8_t reg);
	inline void IncWordReg(uint8_t reg);
	inline void DecWordReg(uint8_t reg);
	inline void PUSH(uint16_t data);
	inline uint16_t POP();
	inline void JMP(bool cond);
	inline void ADJ4(int8_t param1, int8_t param2);
	inline void ADJB(int8_t param1, int8_t param2);

>>>>>>> upstream/master
	address_space_config m_program_config;
	address_space_config m_io_config;

	union
	{                   /* eight general registers */
<<<<<<< HEAD
		UINT16 w[8];    /* viewed as 16 bits registers */
		UINT8  b[16];   /* or as 8 bit registers */
	} m_regs;
	UINT16  m_sregs[4];

	UINT16  m_ip;

	INT32   m_SignVal;
	UINT32  m_AuxVal, m_OverVal, m_ZeroVal, m_CarryVal, m_ParityVal; /* 0 or non-0 valued flags */
	UINT8   m_TF, m_IF, m_DF, m_MF;     /* 0 or 1 valued flags */   /* OB[19.07.99] added Mode Flag V30 */
	UINT32  m_int_vector;
	UINT32  m_pending_irq;
	UINT32  m_nmi_state;
	UINT32  m_irq_state;
	UINT8   m_no_interrupt;
	UINT8   m_fire_trap;
=======
		uint16_t w[8];    /* viewed as 16 bits registers */
		uint8_t  b[16];   /* or as 8 bit registers */
	} m_regs;
	uint16_t  m_sregs[4];

	uint16_t  m_ip;

	int32_t   m_SignVal;
	uint32_t  m_AuxVal, m_OverVal, m_ZeroVal, m_CarryVal, m_ParityVal; /* 0 or non-0 valued flags */
	uint8_t   m_TF, m_IF, m_DF, m_MF;     /* 0 or 1 valued flags */   /* OB[19.07.99] added Mode Flag V30 */
	uint32_t  m_int_vector;
	uint32_t  m_pending_irq;
	uint32_t  m_nmi_state;
	uint32_t  m_irq_state;
	uint8_t   m_no_interrupt;
	uint8_t   m_fire_trap;
>>>>>>> upstream/master

	address_space *m_program;
	direct_read_data *m_direct;
	address_space *m_io;
	int m_icount;

<<<<<<< HEAD
	UINT32 m_prefix_base;   /* base address of the latest prefix segment */
	bool m_seg_prefix;      /* prefix segment indicator */
	bool m_seg_prefix_next; /* prefix segment for next instruction */

	UINT32 m_ea;
	UINT16 m_eo;
	UINT16 m_e16;

	// Used during execution of instructions
	UINT8   m_modrm;
	UINT32  m_dst;
	UINT32  m_src;
	UINT32  m_pc;

	// Lookup tables
	UINT8 m_parity_table[256];
=======
	uint32_t m_prefix_base;   /* base address of the latest prefix segment */
	bool m_seg_prefix;      /* prefix segment indicator */
	bool m_seg_prefix_next; /* prefix segment for next instruction */

	uint32_t m_ea;
	uint16_t m_eo;
	uint16_t m_e16;

	// Used during execution of instructions
	uint8_t   m_modrm;
	uint32_t  m_dst;
	uint32_t  m_src;
	uint32_t  m_pc;

	// Lookup tables
	uint8_t m_parity_table[256];
>>>>>>> upstream/master
	struct {
		struct {
			int w[256];
			int b[256];
		} reg;
		struct {
			int w[256];
			int b[256];
		} RM;
	} m_Mod_RM;
};

<<<<<<< HEAD

#endif /* __V30MZ_H__ */
=======
#endif // MAME_CPU_V32MZ_V30MZ_H
>>>>>>> upstream/master
