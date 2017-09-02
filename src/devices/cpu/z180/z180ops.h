// license:BSD-3-Clause
// copyright-holders:Juergen Buchmueller
/***************************************************************
 * Enter HALT state; write 1 to fake port on first execution
 ***************************************************************/
#define ENTER_HALT() {                                          \
	_PC--;                                                      \
	m_HALT = 1;                                                   \
}

/***************************************************************
 * Leave HALT state; write 0 to fake port
 ***************************************************************/
#define LEAVE_HALT() {                                          \
	if( m_HALT )                                                  \
	{                                                           \
		m_HALT = 0;                                               \
		_PC++;                                                  \
	}                                                           \
}

/***************************************************************
 * Input a byte from given I/O port
 ***************************************************************/
#define IN(port)                                                \
	(((port ^ IO_IOCR) & 0xffc0) == 0) ?                        \
		z180_readcontrol(port) : m_iospace->read_byte(port)

/***************************************************************
 * Output a byte to given I/O port
 ***************************************************************/
#define OUT(port,value)                                         \
	if (((port ^ IO_IOCR) & 0xffc0) == 0)                       \
		z180_writecontrol(port,value);                          \
	else m_iospace->write_byte(port,value)

/***************************************************************
<<<<<<< HEAD
 * MMU calculate the memory managemant lookup table
=======
 * MMU calculate the memory management lookup table
>>>>>>> upstream/master
 * bb and cb specify a 4K page
 * If the 4 most significant bits of an 16 bit address are
 * greater or equal to the bank base, the bank base register
 * specifies the 4K offset into the 20 bit address space.
 * If the 4 bits are also greater or equal to the common base,
 * the common base register is used to specify the offset.
 ***************************************************************/
void z180_device::z180_mmu()
{
	offs_t addr, page, bb, cb;
	bb = IO_CBAR & 15;
	cb = IO_CBAR >> 4;
	for( page = 0; page < 16; page++ )
	{
		addr = page << 12;
		if (page >= bb)
		{
			if (page >= cb)
				addr += (IO_CBR << 12);
			else
				addr += (IO_BBR << 12);
		}
		m_mmu[page] = (addr & 0xfffff);
	}
}


#define MMU_REMAP_ADDR(addr) (m_mmu[((addr)>>12)&15]|((addr)&4095))

/***************************************************************
 * Read a byte from given memory location
 ***************************************************************/
#define RM(addr) m_program->read_byte(MMU_REMAP_ADDR(addr))

/***************************************************************
 * Write a byte to given memory location
 ***************************************************************/
#define WM(addr,value) m_program->write_byte(MMU_REMAP_ADDR(addr),value)

/***************************************************************
 * Read a word from given memory location
 ***************************************************************/
void z180_device::RM16( offs_t addr, PAIR *r )
{
	r->b.l = RM(addr);
	r->b.h = RM(addr+1);
}

/***************************************************************
 * Write a word to given memory location
 ***************************************************************/
void z180_device::WM16( offs_t addr, PAIR *r )
{
	WM(addr, r->b.l);
	WM(addr+1, r->b.h);
}

/***************************************************************
 * ROP() is identical to RM() except it is used for
 * reading opcodes. In case of system with memory mapped I/O,
 * this function can be used to greatly speed up emulation
 ***************************************************************/
<<<<<<< HEAD
UINT8 z180_device::ROP()
=======
uint8_t z180_device::ROP()
>>>>>>> upstream/master
{
	offs_t addr = _PCD;
	_PC++;
	return m_odirect->read_byte(MMU_REMAP_ADDR(addr));
}

/****************************************************************
 * ARG() is identical to ROP() except it is used
 * for reading opcode arguments. This difference can be used to
 * support systems that use different encoding mechanisms for
 * opcodes and opcode arguments
 ***************************************************************/
<<<<<<< HEAD
UINT8 z180_device::ARG()
=======
uint8_t z180_device::ARG()
>>>>>>> upstream/master
{
	offs_t addr = _PCD;
	_PC++;
	return m_direct->read_byte(MMU_REMAP_ADDR(addr));
}

<<<<<<< HEAD
UINT32 z180_device::ARG16()
=======
uint32_t z180_device::ARG16()
>>>>>>> upstream/master
{
	offs_t addr = _PCD;
	_PC += 2;
	return m_direct->read_byte(MMU_REMAP_ADDR(addr)) | (m_direct->read_byte(MMU_REMAP_ADDR(addr+1)) << 8);
}

/***************************************************************
<<<<<<< HEAD
 * Calculate the effective addess m_ea of an opcode using
 * IX+offset resp. IY+offset addressing.
 ***************************************************************/
#define EAX() m_ea = (UINT32)(UINT16)(_IX + (INT8)ARG())
#define EAY() m_ea = (UINT32)(UINT16)(_IY + (INT8)ARG())
=======
 * Calculate the effective address m_ea of an opcode using
 * IX+offset resp. IY+offset addressing.
 ***************************************************************/
#define EAX() m_ea = (uint32_t)(uint16_t)(_IX + (int8_t)ARG())
#define EAY() m_ea = (uint32_t)(uint16_t)(_IY + (int8_t)ARG())
>>>>>>> upstream/master

/***************************************************************
 * POP
 ***************************************************************/
#define POP(DR) { RM16(_SPD, &m_##DR ); _SP += 2; }

/***************************************************************
 * PUSH
 ***************************************************************/
#define PUSH(SR) { _SP -= 2; WM16(_SPD, &m_##SR); }

/***************************************************************
 * JP
 ***************************************************************/
#define JP {                                                    \
	_PCD = ARG16();                                           \
}

/***************************************************************
 * JP_COND
 ***************************************************************/

#define JP_COND(cond)                                           \
	if( cond )                                                  \
	{                                                           \
		_PCD = ARG16();                                       \
	}                                                           \
	else                                                        \
	{                                                           \
		_PC += 2;                                             \
	}

/***************************************************************
 * JR
 ***************************************************************/
#define JR()                                                    \
{                                                               \
<<<<<<< HEAD
	INT8 arg = (INT8)ARG(); /* ARG() also increments _PC */   \
=======
	int8_t arg = (int8_t)ARG(); /* ARG() also increments _PC */   \
>>>>>>> upstream/master
	_PC += arg;           /* so don't do _PC += ARG() */      \
}

/***************************************************************
 * JR_COND
 ***************************************************************/
#define JR_COND(cond,opcode)                                    \
	if( cond )                                                  \
	{                                                           \
<<<<<<< HEAD
		INT8 arg = (INT8)ARG(); /* ARG() also increments _PC */ \
=======
		int8_t arg = (int8_t)ARG(); /* ARG() also increments _PC */ \
>>>>>>> upstream/master
		_PC += arg;           /* so don't do _PC += ARG() */  \
		CC(ex,opcode);                                          \
	}                                                           \
	else _PC++;
/***************************************************************
 * CALL
 ***************************************************************/
#define CALL()                                                  \
	m_ea = ARG16();                                             \
	PUSH( PC );                                               \
	_PCD = m_ea;

/***************************************************************
 * CALL_COND
 ***************************************************************/
#define CALL_COND(cond,opcode)                                  \
	if( cond )                                                  \
	{                                                           \
		m_ea = ARG16();                                         \
		PUSH( PC );                                           \
		_PCD = m_ea;                                              \
		CC(ex,opcode);                                          \
	}                                                           \
	else                                                        \
	{                                                           \
		_PC+=2;                                               \
	}

/***************************************************************
 * RET_COND
 ***************************************************************/
#define RET_COND(cond,opcode)                                   \
	if( cond )                                                  \
	{                                                           \
<<<<<<< HEAD
		POP(PC);                                              \
=======
		POP(PC);                                                \
>>>>>>> upstream/master
		CC(ex,opcode);                                          \
	}

/***************************************************************
 * RETN
 ***************************************************************/
#define RETN    {                                               \
<<<<<<< HEAD
	LOG(("Z180 '%s' RETN IFF1:%d IFF2:%d\n", tag(), m_IFF1, m_IFF2)); \
	POP(PC);                                                  \
	m_IFF1 = m_IFF2;                                                \
=======
	LOG("Z180 RETN IFF1:%d IFF2:%d\n", m_IFF1, m_IFF2);         \
	POP(PC);                                                    \
	m_IFF1 = m_IFF2;                                            \
>>>>>>> upstream/master
}

/***************************************************************
 * RETI
 ***************************************************************/
#define RETI    {                                               \
<<<<<<< HEAD
	POP(PC);                                                  \
/* according to http://www.msxnet.org/tech/Z80/z80undoc.txt */  \
/*  m_IFF1 = m_IFF2;  */                                            \
	m_daisy.call_reti_device();                 \
=======
	POP(PC);                                                    \
/* according to http://www.msxnet.org/tech/Z80/z80undoc.txt */  \
/*  m_IFF1 = m_IFF2;  */                                        \
	daisy_call_reti_device();                                   \
>>>>>>> upstream/master
}

/***************************************************************
 * LD   R,A
 ***************************************************************/
#define LD_R_A {                                                \
	m_R = _A;                                                 \
	m_R2 = _A & 0x80;             /* keep bit 7 of R */       \
}

/***************************************************************
 * LD   A,R
 ***************************************************************/
#define LD_A_R {                                                \
	_A = (m_R & 0x7f) | m_R2;                                     \
	_F = (_F & CF) | SZ[_A] | ( m_IFF2 << 2 );                    \
}

/***************************************************************
 * LD   I,A
 ***************************************************************/
#define LD_I_A {                                                \
	m_I = _A;                                                 \
}

/***************************************************************
 * LD   A,I
 ***************************************************************/
#define LD_A_I {                                                \
	_A = m_I;                                                 \
	_F = (_F & CF) | SZ[_A] | ( m_IFF2 << 2 );                    \
}

/***************************************************************
 * RST
 ***************************************************************/
#define RST(addr)                                               \
	PUSH( PC );                                               \
	_PCD = addr;

/***************************************************************
 * INC  r8
 ***************************************************************/
<<<<<<< HEAD
UINT8 z180_device::INC(UINT8 value)
{
	UINT8 res = value + 1;
	_F = (_F & CF) | SZHV_inc[res];
	return (UINT8)res;
=======
uint8_t z180_device::INC(uint8_t value)
{
	uint8_t res = value + 1;
	_F = (_F & CF) | SZHV_inc[res];
	return (uint8_t)res;
>>>>>>> upstream/master
}

/***************************************************************
 * DEC  r8
 ***************************************************************/
<<<<<<< HEAD
UINT8 z180_device::DEC(UINT8 value)
{
	UINT8 res = value - 1;
=======
uint8_t z180_device::DEC(uint8_t value)
{
	uint8_t res = value - 1;
>>>>>>> upstream/master
	_F = (_F & CF) | SZHV_dec[res];
	return res;
}

/***************************************************************
 * RLCA
 ***************************************************************/
#define RLCA                                                    \
	_A = (_A << 1) | (_A >> 7);                               \
	_F = (_F & (SF | ZF | PF)) | (_A & (YF | XF | CF))

/***************************************************************
 * RRCA
 ***************************************************************/
#define RRCA                                                    \
	_F = (_F & (SF | ZF | PF)) | (_A & (YF | XF | CF));       \
	_A = (_A >> 1) | (_A << 7)

/***************************************************************
 * RLA
 ***************************************************************/
#define RLA {                                                   \
<<<<<<< HEAD
	UINT8 res = (_A << 1) | (_F & CF);                          \
	UINT8 c = (_A & 0x80) ? CF : 0;                           \
=======
	uint8_t res = (_A << 1) | (_F & CF);                          \
	uint8_t c = (_A & 0x80) ? CF : 0;                           \
>>>>>>> upstream/master
	_F = (_F & (SF | ZF | PF)) | c | (res & (YF | XF));         \
	_A = res;                                                 \
}

/***************************************************************
 * RRA
 ***************************************************************/
#define RRA {                                                   \
<<<<<<< HEAD
	UINT8 res = (_A >> 1) | (_F << 7);                          \
	UINT8 c = (_A & 0x01) ? CF : 0;                           \
=======
	uint8_t res = (_A >> 1) | (_F << 7);                          \
	uint8_t c = (_A & 0x01) ? CF : 0;                           \
>>>>>>> upstream/master
	_F = (_F & (SF | ZF | PF)) | c | (res & (YF | XF));         \
	_A = res;                                                 \
}

/***************************************************************
 * RRD
 ***************************************************************/
#define RRD {                                                   \
<<<<<<< HEAD
	UINT8 n = RM(_HL);                                          \
=======
	uint8_t n = RM(_HL);                                          \
>>>>>>> upstream/master
	WM( _HL, (n >> 4) | (_A << 4) );                          \
	_A = (_A & 0xf0) | (n & 0x0f);                              \
	_F = (_F & CF) | SZP[_A];                                 \
}

/***************************************************************
 * RLD
 ***************************************************************/
#define RLD {                                                   \
<<<<<<< HEAD
	UINT8 n = RM(_HL);                                          \
=======
	uint8_t n = RM(_HL);                                          \
>>>>>>> upstream/master
	WM( _HL, (n << 4) | (_A & 0x0f) );                            \
	_A = (_A & 0xf0) | (n >> 4);                                \
	_F = (_F & CF) | SZP[_A];                                 \
}

/***************************************************************
 * ADD  A,n
 ***************************************************************/
#define ADD(value)                                              \
{                                                               \
<<<<<<< HEAD
	UINT32 ah = _AFD & 0xff00;                                    \
	UINT32 res = (UINT8)((ah >> 8) + value);                    \
=======
	uint32_t ah = _AFD & 0xff00;                                    \
	uint32_t res = (uint8_t)((ah >> 8) + value);                    \
>>>>>>> upstream/master
	_F = SZHVC_add[ah | res];                                 \
	_A = res;                                                 \
}

/***************************************************************
 * ADC  A,n
 ***************************************************************/
#define ADC(value)                                              \
{                                                               \
<<<<<<< HEAD
	UINT32 ah = _AFD & 0xff00, c = _AFD & 1;                    \
	UINT32 res = (UINT8)((ah >> 8) + value + c);                \
=======
	uint32_t ah = _AFD & 0xff00, c = _AFD & 1;                    \
	uint32_t res = (uint8_t)((ah >> 8) + value + c);                \
>>>>>>> upstream/master
	_F = SZHVC_add[(c << 16) | ah | res];                     \
	_A = res;                                                 \
}

/***************************************************************
 * SUB  n
 ***************************************************************/
#define SUB(value)                                              \
{                                                               \
<<<<<<< HEAD
	UINT32 ah = _AFD & 0xff00;                                    \
	UINT32 res = (UINT8)((ah >> 8) - value);                    \
=======
	uint32_t ah = _AFD & 0xff00;                                    \
	uint32_t res = (uint8_t)((ah >> 8) - value);                    \
>>>>>>> upstream/master
	_F = SZHVC_sub[ah | res];                                 \
	_A = res;                                                 \
}

/***************************************************************
 * SBC  A,n
 ***************************************************************/
#define SBC(value)                                              \
{                                                               \
<<<<<<< HEAD
	UINT32 ah = _AFD & 0xff00, c = _AFD & 1;                    \
	UINT32 res = (UINT8)((ah >> 8) - value - c);                \
=======
	uint32_t ah = _AFD & 0xff00, c = _AFD & 1;                    \
	uint32_t res = (uint8_t)((ah >> 8) - value - c);                \
>>>>>>> upstream/master
	_F = SZHVC_sub[(c<<16) | ah | res];                       \
	_A = res;                                                 \
}

/***************************************************************
 * NEG
 ***************************************************************/
#define NEG {                                                   \
<<<<<<< HEAD
	UINT8 value = _A;                                         \
=======
	uint8_t value = _A;                                         \
>>>>>>> upstream/master
	_A = 0;                                                   \
	SUB(value);                                                 \
}

/***************************************************************
 * DAA
 ***************************************************************/
#define DAA {                                                   \
<<<<<<< HEAD
	UINT8 r = _A;                                         \
=======
	uint8_t r = _A;                                         \
>>>>>>> upstream/master
	if (_F&NF) {                                          \
		if ((_F&HF)|((_A&0xf)>9)) r-=6;                     \
		if ((_F&CF)|(_A>0x99)) r-=0x60;                     \
	}                                                   \
	else {                                                  \
		if ((_F&HF)|((_A&0xf)>9)) r+=6;                     \
		if ((_F&CF)|(_A>0x99)) r+=0x60;                     \
	}                                                   \
	_F=(_F&3)|(_A>0x99)|((_A^r)&HF)|SZP[r];             \
	_A=r;                                             \
}

/***************************************************************
 * AND  n
 ***************************************************************/
#define AND(value)                                              \
	_A &= value;                                              \
	_F = SZP[_A] | HF

/***************************************************************
 * OR   n
 ***************************************************************/
#define OR(value)                                               \
	_A |= value;                                              \
	_F = SZP[_A]

/***************************************************************
 * XOR  n
 ***************************************************************/
#define XOR(value)                                              \
	_A ^= value;                                              \
	_F = SZP[_A]

/***************************************************************
 * CP   n
 ***************************************************************/
#define CP(value)                                               \
{                                                               \
<<<<<<< HEAD
	UINT32 ah = _AFD & 0xff00;                                    \
	UINT32 res = (UINT8)((ah >> 8) - value);                    \
=======
	uint32_t ah = _AFD & 0xff00;                                    \
	uint32_t res = (uint8_t)((ah >> 8) - value);                    \
>>>>>>> upstream/master
	_F = SZHVC_sub[ah | res];                                 \
}

/***************************************************************
 * EX   AF,AF'
 ***************************************************************/
#define EX_AF {                                                 \
	PAIR tmp;                                                   \
	tmp = m_AF; m_AF = m_AF2; m_AF2 = tmp;          \
}

/***************************************************************
 * EX   DE,HL
 ***************************************************************/
#define EX_DE_HL {                                              \
	PAIR tmp;                                                   \
	tmp = m_DE; m_DE = m_HL; m_HL = tmp;            \
}

/***************************************************************
 * EXX
 ***************************************************************/
#define EXX {                                                   \
	PAIR tmp;                                                   \
	tmp = m_BC; m_BC = m_BC2; m_BC2 = tmp;          \
	tmp = m_DE; m_DE = m_DE2; m_DE2 = tmp;          \
	tmp = m_HL; m_HL = m_HL2; m_HL2 = tmp;          \
}

/***************************************************************
 * EX   (SP),r16
 ***************************************************************/
#define EXSP(DR)                                                \
{                                                               \
	PAIR tmp = { { 0, 0, 0, 0 } };                              \
	RM16( _SPD, &tmp );                                         \
	WM16( _SPD, &m_##DR );                                    \
	m_##DR = tmp;                                             \
}


/***************************************************************
 * ADD16
 ***************************************************************/
#define ADD16(DR,SR)                                            \
{                                                               \
<<<<<<< HEAD
	UINT32 res = m_##DR.d + m_##SR.d;                       \
	_F = (_F & (SF | ZF | VF)) |                                \
		(((m_##DR.d ^ res ^ m_##SR.d) >> 8) & HF) |         \
		((res >> 16) & CF);                                     \
	m_##DR.w.l = (UINT16)res;                                 \
=======
	uint32_t res = m_##DR.d + m_##SR.d;                       \
	_F = (_F & (SF | ZF | VF)) |                                \
		(((m_##DR.d ^ res ^ m_##SR.d) >> 8) & HF) |         \
		((res >> 16) & CF);                                     \
	m_##DR.w.l = (uint16_t)res;                                 \
>>>>>>> upstream/master
}

/***************************************************************
 * ADC  r16,r16
 ***************************************************************/
#define ADC16(DR)                                               \
{                                                               \
<<<<<<< HEAD
	UINT32 res = _HLD + m_##DR.d + (_F & CF);                 \
=======
	uint32_t res = _HLD + m_##DR.d + (_F & CF);                 \
>>>>>>> upstream/master
	_F = (((_HLD ^ res ^ m_##DR.d) >> 8) & HF) |              \
		((res >> 16) & CF) |                                    \
		((res >> 8) & SF) |                                     \
		((res & 0xffff) ? 0 : ZF) |                             \
		(((m_##DR.d ^ _HLD ^ 0x8000) & (m_##DR.d ^ res) & 0x8000) >> 13); \
<<<<<<< HEAD
	_HL = (UINT16)res;                                            \
=======
	_HL = (uint16_t)res;                                            \
>>>>>>> upstream/master
}

/***************************************************************
 * SBC  r16,r16
 ***************************************************************/
#define SBC16(DR)                                               \
{                                                               \
<<<<<<< HEAD
	UINT32 res = _HLD - m_##DR.d - (_F & CF);                 \
=======
	uint32_t res = _HLD - m_##DR.d - (_F & CF);                 \
>>>>>>> upstream/master
	_F = (((_HLD ^ res ^ m_##DR.d) >> 8) & HF) | NF |         \
		((res >> 16) & CF) |                                    \
		((res >> 8) & SF) |                                     \
		((res & 0xffff) ? 0 : ZF) |                             \
		(((m_##DR.d ^ _HLD) & (_HLD ^ res) &0x8000) >> 13);   \
<<<<<<< HEAD
	_HL = (UINT16)res;                                            \
=======
	_HL = (uint16_t)res;                                            \
>>>>>>> upstream/master
}

/***************************************************************
 * RLC  r8
 ***************************************************************/
<<<<<<< HEAD
UINT8 z180_device::RLC(UINT8 value)
=======
uint8_t z180_device::RLC(uint8_t value)
>>>>>>> upstream/master
{
	unsigned res = value;
	unsigned c = (res & 0x80) ? CF : 0;
	res = ((res << 1) | (res >> 7)) & 0xff;
	_F = SZP[res] | c;
	return res;
}

/***************************************************************
 * RRC  r8
 ***************************************************************/
<<<<<<< HEAD
UINT8 z180_device::RRC(UINT8 value)
=======
uint8_t z180_device::RRC(uint8_t value)
>>>>>>> upstream/master
{
	unsigned res = value;
	unsigned c = (res & 0x01) ? CF : 0;
	res = ((res >> 1) | (res << 7)) & 0xff;
	_F = SZP[res] | c;
	return res;
}

/***************************************************************
 * RL   r8
 ***************************************************************/
<<<<<<< HEAD
UINT8 z180_device::RL(UINT8 value)
=======
uint8_t z180_device::RL(uint8_t value)
>>>>>>> upstream/master
{
	unsigned res = value;
	unsigned c = (res & 0x80) ? CF : 0;
	res = ((res << 1) | (_F & CF)) & 0xff;
	_F = SZP[res] | c;
	return res;
}

/***************************************************************
 * RR   r8
 ***************************************************************/
<<<<<<< HEAD
UINT8 z180_device::RR(UINT8 value)
=======
uint8_t z180_device::RR(uint8_t value)
>>>>>>> upstream/master
{
	unsigned res = value;
	unsigned c = (res & 0x01) ? CF : 0;
	res = ((res >> 1) | (_F << 7)) & 0xff;
	_F = SZP[res] | c;
	return res;
}

/***************************************************************
 * SLA  r8
 ***************************************************************/
<<<<<<< HEAD
UINT8 z180_device::SLA(UINT8 value)
=======
uint8_t z180_device::SLA(uint8_t value)
>>>>>>> upstream/master
{
	unsigned res = value;
	unsigned c = (res & 0x80) ? CF : 0;
	res = (res << 1) & 0xff;
	_F = SZP[res] | c;
	return res;
}

/***************************************************************
 * SRA  r8
 ***************************************************************/
<<<<<<< HEAD
UINT8 z180_device::SRA(UINT8 value)
=======
uint8_t z180_device::SRA(uint8_t value)
>>>>>>> upstream/master
{
	unsigned res = value;
	unsigned c = (res & 0x01) ? CF : 0;
	res = ((res >> 1) | (res & 0x80)) & 0xff;
	_F = SZP[res] | c;
	return res;
}

/***************************************************************
 * SLL  r8
 ***************************************************************/
<<<<<<< HEAD
UINT8 z180_device::SLL(UINT8 value)
=======
uint8_t z180_device::SLL(uint8_t value)
>>>>>>> upstream/master
{
	unsigned res = value;
	unsigned c = (res & 0x80) ? CF : 0;
	res = ((res << 1) | 0x01) & 0xff;
	_F = SZP[res] | c;
	return res;
}

/***************************************************************
 * SRL  r8
 ***************************************************************/
<<<<<<< HEAD
UINT8 z180_device::SRL(UINT8 value)
=======
uint8_t z180_device::SRL(uint8_t value)
>>>>>>> upstream/master
{
	unsigned res = value;
	unsigned c = (res & 0x01) ? CF : 0;
	res = (res >> 1) & 0xff;
	_F = SZP[res] | c;
	return res;
}

/***************************************************************
 * BIT  bit,r8
 ***************************************************************/
#undef BIT
#define BIT(bit,reg)                                            \
	_F = (_F & CF) | HF | SZ_BIT[reg & (1<<bit)]

/***************************************************************
 * BIT  bit,(IX/Y+o)
 ***************************************************************/
#define BIT_XY(bit,reg)                                         \
	_F = (_F & CF) | HF | (SZ_BIT[reg & (1<<bit)] & ~(YF|XF)) | ((m_ea>>8) & (YF|XF))

/***************************************************************
 * RES  bit,r8
 ***************************************************************/
<<<<<<< HEAD
UINT8 z180_device::RES(UINT8 bit, UINT8 value)
=======
uint8_t z180_device::RES(uint8_t bit, uint8_t value)
>>>>>>> upstream/master
{
	return value & ~(1<<bit);
}

/***************************************************************
 * SET  bit,r8
 ***************************************************************/
<<<<<<< HEAD
UINT8 z180_device::SET(UINT8 bit, UINT8 value)
=======
uint8_t z180_device::SET(uint8_t bit, uint8_t value)
>>>>>>> upstream/master
{
	return value | (1<<bit);
}

/***************************************************************
 * LDI
 ***************************************************************/
#define LDI {                                                   \
<<<<<<< HEAD
	UINT8 io = RM(_HL);                                         \
=======
	uint8_t io = RM(_HL);                                         \
>>>>>>> upstream/master
	WM( _DE, io );                                              \
	_F &= SF | ZF | CF;                                       \
	if( (_A + io) & 0x02 ) _F |= YF; /* bit 1 -> flag 5 */      \
	if( (_A + io) & 0x08 ) _F |= XF; /* bit 3 -> flag 3 */      \
	_HL++; _DE++; _BC--;                                      \
	if( _BC ) _F |= VF;                                         \
}

/***************************************************************
 * CPI
 ***************************************************************/
#define CPI {                                                   \
<<<<<<< HEAD
	UINT8 val = RM(_HL);                                        \
	UINT8 res = _A - val;                                     \
=======
	uint8_t val = RM(_HL);                                        \
	uint8_t res = _A - val;                                     \
>>>>>>> upstream/master
	_HL++; _BC--;                                               \
	_F = (_F & CF) | (SZ[res] & ~(YF|XF)) | ((_A ^ val ^ res) & HF) | NF;  \
	if( _F & HF ) res -= 1;                                   \
	if( res & 0x02 ) _F |= YF; /* bit 1 -> flag 5 */          \
	if( res & 0x08 ) _F |= XF; /* bit 3 -> flag 3 */          \
	if( _BC ) _F |= VF;                                         \
}

/***************************************************************
 * INI
 ***************************************************************/
#define INI {                                                   \
<<<<<<< HEAD
	UINT8 io = IN(_BC);                                         \
=======
	uint8_t io = IN(_BC);                                         \
>>>>>>> upstream/master
	_B--;                                                     \
	WM( _HL, io );                                              \
	_HL++;                                                        \
	_F = SZ[_B];                                                \
	if( io & SF ) _F |= NF;                                   \
	if( (_C + io + 1) & 0x100 ) _F |= HF | CF;                  \
	if( (irep_tmp1[_C & 3][io & 3] ^                          \
			breg_tmp2[_B] ^                                       \
			(_C >> 2) ^                                           \
			(io >> 2)) & 1 )                                        \
		_F |= PF;                                             \
}

/***************************************************************
 * OUTI
 ***************************************************************/
#define OUTI {                                                  \
<<<<<<< HEAD
	UINT8 io = RM(_HL);                                         \
=======
	uint8_t io = RM(_HL);                                         \
>>>>>>> upstream/master
	_B--;                                                     \
	OUT( _BC, io );                                             \
	_HL++;                                                        \
	_F = SZ[_B];                                                \
	if( io & SF ) _F |= NF;                                   \
	if( (_C + io + 1) & 0x100 ) _F |= HF | CF;                  \
	if( (irep_tmp1[_C & 3][io & 3] ^                          \
			breg_tmp2[_B] ^                                       \
			(_C >> 2) ^                                           \
			(io >> 2)) & 1 )                                        \
		_F |= PF;                                             \
}

/***************************************************************
 * LDD
 ***************************************************************/
#define LDD {                                                   \
<<<<<<< HEAD
	UINT8 io = RM(_HL);                                         \
=======
	uint8_t io = RM(_HL);                                         \
>>>>>>> upstream/master
	WM( _DE, io );                                              \
	_F &= SF | ZF | CF;                                       \
	if( (_A + io) & 0x02 ) _F |= YF; /* bit 1 -> flag 5 */      \
	if( (_A + io) & 0x08 ) _F |= XF; /* bit 3 -> flag 3 */      \
	_HL--; _DE--; _BC--;                                      \
	if( _BC ) _F |= VF;                                         \
}

/***************************************************************
 * CPD
 ***************************************************************/
#define CPD {                                                   \
<<<<<<< HEAD
	UINT8 val = RM(_HL);                                        \
	UINT8 res = _A - val;                                     \
=======
	uint8_t val = RM(_HL);                                        \
	uint8_t res = _A - val;                                     \
>>>>>>> upstream/master
	_HL--; _BC--;                                               \
	_F = (_F & CF) | (SZ[res] & ~(YF|XF)) | ((_A ^ val ^ res) & HF) | NF;  \
	if( _F & HF ) res -= 1;                                   \
	if( res & 0x02 ) _F |= YF; /* bit 1 -> flag 5 */          \
	if( res & 0x08 ) _F |= XF; /* bit 3 -> flag 3 */          \
	if( _BC ) _F |= VF;                                         \
}

/***************************************************************
 * IND
 ***************************************************************/
#define IND {                                                   \
<<<<<<< HEAD
	UINT8 io = IN(_BC);                                         \
=======
	uint8_t io = IN(_BC);                                         \
>>>>>>> upstream/master
	_B--;                                                     \
	WM( _HL, io );                                              \
	_HL--;                                                        \
	_F = SZ[_B];                                                \
	if( io & SF ) _F |= NF;                                   \
	if( (_C + io - 1) & 0x100 ) _F |= HF | CF;                  \
	if( (drep_tmp1[_C & 3][io & 3] ^                          \
			breg_tmp2[_B] ^                                       \
			(_C >> 2) ^                                           \
			(io >> 2)) & 1 )                                        \
		_F |= PF;                                             \
}

/***************************************************************
 * OUTD
 ***************************************************************/
#define OUTD {                                                  \
<<<<<<< HEAD
	UINT8 io = RM(_HL);                                         \
=======
	uint8_t io = RM(_HL);                                         \
>>>>>>> upstream/master
	_B--;                                                     \
	OUT( _BC, io );                                             \
	_HL--;                                                        \
	_F = SZ[_B];                                                \
	if( io & SF ) _F |= NF;                                   \
	if( (_C + io - 1) & 0x100 ) _F |= HF | CF;                  \
	if( (drep_tmp1[_C & 3][io & 3] ^                          \
			breg_tmp2[_B] ^                                       \
			(_C >> 2) ^                                           \
			(io >> 2)) & 1 )                                        \
		_F |= PF;                                             \
}

/***************************************************************
 * LDIR
 ***************************************************************/
#define LDIR                                                    \
	LDI;                                                        \
	if( _BC )                                                 \
	{                                                           \
		_PC -= 2;                                             \
		CC(ex,0xb0);                                            \
	}

/***************************************************************
 * CPIR
 ***************************************************************/
#define CPIR                                                    \
	CPI;                                                        \
	if( _BC && !(_F & ZF) )                                     \
	{                                                           \
		_PC -= 2;                                             \
		CC(ex,0xb1);                                            \
	}

/***************************************************************
 * INIR
 ***************************************************************/
#define INIR                                                    \
	INI;                                                        \
	if( _B )                                                  \
	{                                                           \
		_PC -= 2;                                             \
		CC(ex,0xb2);                                            \
	}

/***************************************************************
 * OTIR
 ***************************************************************/
#define OTIR                                                    \
	OUTI;                                                       \
	if( _B )                                                  \
	{                                                           \
		_PC -= 2;                                             \
		CC(ex,0xb3);                                            \
	}

/***************************************************************
 * LDDR
 ***************************************************************/
#define LDDR                                                    \
	LDD;                                                        \
	if( _BC )                                                 \
	{                                                           \
		_PC -= 2;                                             \
		CC(ex,0xb8);                                            \
	}

/***************************************************************
 * CPDR
 ***************************************************************/
#define CPDR                                                    \
	CPD;                                                        \
	if( _BC && !(_F & ZF) )                                     \
	{                                                           \
		_PC -= 2;                                             \
		CC(ex,0xb9);                                            \
	}

/***************************************************************
 * INDR
 ***************************************************************/
#define INDR                                                    \
	IND;                                                        \
	if( _B )                                                  \
	{                                                           \
		_PC -= 2;                                             \
		CC(ex,0xba);                                            \
	}

/***************************************************************
 * OTDR
 ***************************************************************/
#define OTDR                                                    \
	OUTD;                                                       \
	if( _B )                                                  \
	{                                                           \
		_PC -= 2;                                             \
		CC(ex,0xbb);                                            \
	}

/***************************************************************
 * EI
 ***************************************************************/
#define EI {                                                    \
	m_IFF1 = m_IFF2 = 1;                                            \
	m_after_EI = 1;                                         \
}

/***************************************************************
 * TST  n
 ***************************************************************/
#define TST(value)                                              \
	_F = SZP[_A & value] | HF

/***************************************************************
 * MLT  rr
 ***************************************************************/
#define MLT(DR) {                                               \
	m_##DR.w.l = m_##DR.b.l * m_##DR.b.h;                 \
}

/***************************************************************
 * OTIM
 ***************************************************************/
#define OTIM {                                                  \
	_B--;                                                     \
	OUT( _C, RM(_HL) );                                         \
	_HL++;                                                        \
	_C++;                                                     \
	_F = (_B) ? NF : NF | ZF;                                   \
}

/***************************************************************
 * OTDM
 ***************************************************************/
#define OTDM {                                                  \
	_B--;                                                     \
	OUT( _C, RM(_HL) );                                         \
	_HL--;                                                        \
	_C--;                                                     \
	_F = (_B) ? NF : NF | ZF;                                   \
}

/***************************************************************
 * OTIMR
 ***************************************************************/
#define OTIMR                                                   \
	OTIM;                                                       \
	if( _B )                                                  \
	{                                                           \
		_PC -= 2;                                             \
		CC(ex,0xb3);                                            \
	}

/***************************************************************
 * OTDMR
 ***************************************************************/
#define OTDMR                                                   \
	OTDM;                                                       \
	if( _B )                                                  \
	{                                                           \
		_PC -= 2;                                             \
		CC(ex,0xb3);                                            \
	}

/***************************************************************
 * OTDMR
 ***************************************************************/
#define SLP {                                                   \
	m_icount = 0;                                           \
	m_HALT = 2;                                                 \
}
