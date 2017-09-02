// license:BSD-3-Clause
<<<<<<< HEAD
// copyright-holders:Aaron Giles
=======
// copyright-holders:Aaron Giles, Vas Crabb
>>>>>>> upstream/master
/*** m6805: Portable 6805 emulator ******************************************

    m6805.c (Also supports hd68705 and hd63705 variants)

    References:

        6809 Simulator V09, By L.C. Benschop, Eindhoven The Netherlands.

        m6809: Portable 6809 emulator, DS (6809 code in MAME, derived from
            the 6809 Simulator V09)

        6809 Microcomputer Programming & Interfacing with Experiments"
            by Andrew C. Staugaard, Jr.; Howard W. Sams & Co., Inc.

<<<<<<< HEAD
    System dependencies:    UINT16 must be 16 bit unsigned int
                            UINT8 must be 8 bit unsigned int
                            UINT32 must be more than 16 bits
=======
    System dependencies:    uint16_t must be 16 bit unsigned int
                            uint8_t must be 8 bit unsigned int
                            uint32_t must be more than 16 bits
>>>>>>> upstream/master
                            arrays up to 65536 bytes must be supported
                            machine must be twos complement

  Additional Notes:

  K.Wilkins 18/03/99 - Added 63705 functonality and modified all CPU functions
                       necessary to support:
                           Variable width address bus
                           Different stack pointer
                           Alternate boot vectors
                           Alternate interrups vectors


*****************************************************************************/

#include "emu.h"
<<<<<<< HEAD
#include "debugger.h"
#include "m6805.h"

#define IRQ_LEVEL_DETECT 0

/****************************************************************************/
/* Read a byte from given memory location                                   */
/****************************************************************************/
#define M6805_RDMEM(addr) ((unsigned)m_program->read_byte(addr))

/****************************************************************************/
/* Write a byte to given memory location                                    */
/****************************************************************************/
#define M6805_WRMEM(addr, value) (m_program->write_byte(addr, value))

/****************************************************************************/
/* M6805_RDOP() is identical to M6805_RDMEM() except it is used for reading */
/* opcodes. In case of system with memory mapped I/O, this function can be  */
/* used to greatly speed up emulation                                       */
/****************************************************************************/
#define M6805_RDOP(addr) ((unsigned)m_direct->read_byte(addr))

/****************************************************************************/
/* M6805_RDOP_ARG() is identical to M6805_RDOP() but it's used for reading  */
/* opcode arguments. This difference can be used to support systems that    */
/* use different encoding mechanisms for opcodes and opcode arguments       */
/****************************************************************************/
#define M6805_RDOP_ARG(addr) ((unsigned)m_direct->read_byte(addr))

#define SP_MASK m_sp_mask   /* stack pointer mask */
#define SP_LOW  m_sp_low    /* stack pointer low water mark */
#define PC      m_pc.w.l    /* program counter lower word */
#define S       m_s.w.l     /* stack pointer lower word */
#define A       m_a         /* accumulator */
#define X       m_x         /* index register */
#define CC      m_cc        /* condition codes */

#define EAD m_ea.d
#define EA  m_ea.w.l


/* DS -- THESE ARE RE-DEFINED IN m6805.h TO RAM, ROM or FUNCTIONS IN cpuintrf.c */
#define RM(addr)            M6805_RDMEM(addr)
#define WM(addr, value)     M6805_WRMEM(addr, value)
#define M_RDOP(addr)        M6805_RDOP(addr)
#define M_RDOP_ARG(addr)    M6805_RDOP_ARG(addr)

/* macros to tweak the PC and SP */
#define SP_INC  if( ++S > SP_MASK) S = SP_LOW
#define SP_DEC  if( --S < SP_LOW) S = SP_MASK
#define SP_ADJUST(s) ( ( (s) & SP_MASK ) | SP_LOW )

/* macros to access memory */
#define IMMBYTE(b) {b = M_RDOP_ARG(PC++);}
#define IMMWORD(w) {w.d = 0; w.b.h = M_RDOP_ARG(PC); w.b.l = M_RDOP_ARG(PC+1); PC+=2;}
#define SKIPBYTE() {M_RDOP_ARG(PC++);}

#define PUSHBYTE(b) wr_s_handler_b(&b)
#define PUSHWORD(w) wr_s_handler_w(&w)
#define PULLBYTE(b) rd_s_handler_b(&b)
#define PULLWORD(w) rd_s_handler_w(&w)

/* CC masks      H INZC
              7654 3210 */
#define CFLAG 0x01
#define ZFLAG 0x02
#define NFLAG 0x04
#define IFLAG 0x08
#define HFLAG 0x10

#define CLR_NZ    CC&=~(NFLAG|ZFLAG)
#define CLR_HNZC  CC&=~(HFLAG|NFLAG|ZFLAG|CFLAG)
#define CLR_Z     CC&=~(ZFLAG)
#define CLR_NZC   CC&=~(NFLAG|ZFLAG|CFLAG)
#define CLR_ZC    CC&=~(ZFLAG|CFLAG)

/* macros for CC -- CC bits affected should be reset before calling */
#define SET_Z(a)       if(!a)SEZ
#define SET_Z8(a)      SET_Z((UINT8)a)
#define SET_N8(a)      CC|=((a&0x80)>>5)
#define SET_H(a,b,r)   CC|=((a^b^r)&0x10)
#define SET_C8(a)      CC|=((a&0x100)>>8)

const UINT8 m6805_base_device::m_flags8i[256]=   /* increment */
{
	0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,
	0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,
	0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,
	0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,
	0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,
	0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,
	0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,
	0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04
};

const UINT8 m6805_base_device::m_flags8d[256]= /* decrement */
{
	0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,
	0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,
	0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,
	0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,
	0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,
	0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,
	0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,
	0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04
};
#define SET_FLAGS8I(a)      {CC |= m_flags8i[(a) & 0xff];}
#define SET_FLAGS8D(a)      {CC |= m_flags8d[(a) & 0xff];}

/* combos */
#define SET_NZ8(a)          {SET_N8(a); SET_Z(a);}
#define SET_FLAGS8(a,b,r)   {SET_N8(r); SET_Z8(r); SET_C8(r);}

/* for treating an unsigned UINT8 as a signed INT16 */
#define SIGNED(b) ((INT16)(b & 0x80 ? b | 0xff00 : b))

/* Macros for addressing modes */
#define DIRECT EAD=0; IMMBYTE(m_ea.b.l)
#define IMM8 EA = PC++
#define EXTENDED IMMWORD(m_ea)
#define INDEXED EA = X
#define INDEXED1 {EAD = 0; IMMBYTE(m_ea.b.l); EA += X;}
#define INDEXED2 {IMMWORD(m_ea); EA += X;}

/* macros to set status flags */
#if defined(SEC)
#undef SEC
#endif
#define SEC CC |= CFLAG
#define CLC CC &=~ CFLAG
#define SEZ CC |= ZFLAG
#define CLZ CC &=~ ZFLAG
#define SEN CC |= NFLAG
#define CLN CC &=~ NFLAG
#define SEH CC |= HFLAG
#define CLH CC &=~ HFLAG
#define SEI CC |= IFLAG
#define CLI CC &=~ IFLAG

/* macros for convenience */
#define DIRBYTE(b) {DIRECT; b = RM(EAD);}
#define EXTBYTE(b) {EXTENDED; b = RM(EAD);}
#define IDXBYTE(b) {INDEXED; b = RM(EAD);}
#define IDX1BYTE(b) {INDEXED1; b = RM(EAD);}
#define IDX2BYTE(b) {INDEXED2; b = RM(EAD);}
/* Macros for branch instructions */
#define BRANCH(f) { UINT8 t; IMMBYTE(t); if(f) { PC += SIGNED(t); } }

/* what they say it is ... */
const UINT8 m6805_base_device::m_cycles1[] =
=======
#include "m6805.h"
#include "m6805defs.h"

#include "debugger.h"

#include <algorithm>

#define OP(name)        (&m6805_base_device::name)
#define OP_T(name)      (&m6805_base_device::name<true>)
#define OP_F(name)      (&m6805_base_device::name<false>)
#define OP_IM(name)     (&m6805_base_device::name<addr_mode::IM>)
#define OP_DI(name)     (&m6805_base_device::name<addr_mode::DI>)
#define OP_EX(name)     (&m6805_base_device::name<addr_mode::EX>)
#define OP_IX(name)     (&m6805_base_device::name<addr_mode::IX>)
#define OP_IX1(name)    (&m6805_base_device::name<addr_mode::IX1>)
#define OP_IX2(name)    (&m6805_base_device::name<addr_mode::IX2>)

const m6805_base_device::op_handler_table m6805_base_device::s_hmos_ops =
{
	/*      0/8          1/9          2/A          3/B          4/C          5/D          6/E          7/F */
	/* 0 */ OP(brset<0>),OP(brclr<0>),OP(brset<1>),OP(brclr<1>),OP(brset<2>),OP(brclr<2>),OP(brset<3>),OP(brclr<3>),
			OP(brset<4>),OP(brclr<4>),OP(brset<5>),OP(brclr<5>),OP(brset<6>),OP(brclr<6>),OP(brset<7>),OP(brclr<7>),
	/* 1 */ OP(bset<0>), OP(bclr<0>), OP(bset<1>), OP(bclr<1>), OP(bset<2>), OP(bclr<2>), OP(bset<3>), OP(bclr<3>),
			OP(bset<4>), OP(bclr<4>), OP(bset<5>), OP(bclr<5>), OP(bset<6>), OP(bclr<6>), OP(bset<7>), OP(bclr<7>),
	/* 2 */ OP_T(bra),   OP_F(bra),   OP_T(bhi),   OP_F(bhi),   OP_T(bcc),   OP_F(bcc),   OP_T(bne),   OP_F(bne),
			OP_T(bhcc),  OP_F(bhcc),  OP_T(bpl),   OP_F(bpl),   OP_T(bmc),   OP_F(bmc),   OP_T(bil),   OP_F(bil),
	/* 3 */ OP_DI(neg),  OP(illegal), OP(illegal), OP_DI(com),  OP_DI(lsr),  OP(illegal), OP_DI(ror),  OP_DI(asr),
			OP_DI(lsl),  OP_DI(rol),  OP_DI(dec),  OP(illegal), OP_DI(inc),  OP_DI(tst),  OP(illegal), OP_DI(clr),
	/* 4 */ OP(nega),    OP(illegal), OP(illegal), OP(coma),    OP(lsra),    OP(illegal), OP(rora),    OP(asra),
			OP(lsla),    OP(rola),    OP(deca),    OP(illegal), OP(inca),    OP(tsta),    OP(illegal), OP(clra),
	/* 5 */ OP(negx),    OP(illegal), OP(illegal), OP(comx),    OP(lsrx),    OP(illegal), OP(rorx),    OP(asrx),
			OP(lslx),    OP(rolx),    OP(decx),    OP(illegal), OP(incx),    OP(tstx),    OP(illegal), OP(clrx),
	/* 6 */ OP_IX1(neg), OP(illegal), OP(illegal), OP_IX1(com), OP_IX1(lsr), OP(illegal), OP_IX1(ror), OP_IX1(asr),
			OP_IX1(lsl), OP_IX1(rol), OP_IX1(dec), OP(illegal), OP_IX1(inc), OP_IX1(tst), OP(illegal), OP_IX1(clr),
	/* 7 */ OP_IX(neg),  OP(illegal), OP(illegal), OP_IX(com),  OP_IX(lsr),  OP(illegal), OP_IX(ror),  OP_IX(asr),
			OP_IX(lsl),  OP_IX(rol),  OP_IX(dec),  OP(illegal), OP_IX(inc),  OP_IX(tst),  OP(illegal), OP_IX(clr),
	/* 8 */ OP(rti),     OP(rts),     OP(illegal), OP(swi),     OP(illegal), OP(illegal), OP(illegal), OP(illegal),
			OP(illegal), OP(illegal), OP(illegal), OP(illegal), OP(illegal), OP(illegal), OP(illegal), OP(illegal),
	/* 9 */ OP(illegal), OP(illegal), OP(illegal), OP(illegal), OP(illegal), OP(illegal), OP(illegal), OP(tax),
			OP(clc),     OP(sec),     OP(cli),     OP(sei),     OP(rsp),     OP(nop),     OP(illegal), OP(txa),
	/* A */ OP_IM(suba), OP_IM(cmpa), OP_IM(sbca), OP_IM(cpx),  OP_IM(anda), OP_IM(bita), OP_IM(lda),  OP(illegal),
			OP_IM(eora), OP_IM(adca), OP_IM(ora),  OP_IM(adda), OP(illegal), OP(bsr),     OP_IM(ldx),  OP(illegal),
	/* B */ OP_DI(suba), OP_DI(cmpa), OP_DI(sbca), OP_DI(cpx),  OP_DI(anda), OP_DI(bita), OP_DI(lda),  OP_DI(sta),
			OP_DI(eora), OP_DI(adca), OP_DI(ora),  OP_DI(adda), OP_DI(jmp),  OP_DI(jsr),  OP_DI(ldx),  OP_DI(stx),
	/* C */ OP_EX(suba), OP_EX(cmpa), OP_EX(sbca), OP_EX(cpx),  OP_EX(anda), OP_EX(bita), OP_EX(lda),  OP_EX(sta),
			OP_EX(eora), OP_EX(adca), OP_EX(ora),  OP_EX(adda), OP_EX(jmp),  OP_EX(jsr),  OP_EX(ldx),  OP_EX(stx),
	/* D */ OP_IX2(suba),OP_IX2(cmpa),OP_IX2(sbca),OP_IX2(cpx), OP_IX2(anda),OP_IX2(bita),OP_IX2(lda), OP_IX2(sta),
			OP_IX2(eora),OP_IX2(adca),OP_IX2(ora), OP_IX2(adda),OP_IX2(jmp), OP_IX2(jsr), OP_IX2(ldx), OP_IX2(stx),
	/* E */ OP_IX1(suba),OP_IX1(cmpa),OP_IX1(sbca),OP_IX1(cpx), OP_IX1(anda),OP_IX1(bita),OP_IX1(lda), OP_IX1(sta),
			OP_IX1(eora),OP_IX1(adca),OP_IX1(ora), OP_IX1(adda),OP_IX1(jmp), OP_IX1(jsr), OP_IX1(ldx), OP_IX1(stx),
	/* F */ OP_IX(suba), OP_IX(cmpa), OP_IX(sbca), OP_IX(cpx),  OP_IX(anda), OP_IX(bita), OP_IX(lda),  OP_IX(sta),
			OP_IX(eora), OP_IX(adca), OP_IX(ora),  OP_IX(adda), OP_IX(jmp),  OP_IX(jsr),  OP_IX(ldx),  OP_IX(stx)
};

const m6805_base_device::op_handler_table m6805_base_device::s_cmos_ops =
{
	/*      0/8          1/9          2/A          3/B          4/C          5/D          6/E          7/F */
	/* 0 */ OP(brset<0>),OP(brclr<0>),OP(brset<1>),OP(brclr<1>),OP(brset<2>),OP(brclr<2>),OP(brset<3>),OP(brclr<3>),
			OP(brset<4>),OP(brclr<4>),OP(brset<5>),OP(brclr<5>),OP(brset<6>),OP(brclr<6>),OP(brset<7>),OP(brclr<7>),
	/* 1 */ OP(bset<0>), OP(bclr<0>), OP(bset<1>), OP(bclr<1>), OP(bset<2>), OP(bclr<2>), OP(bset<3>), OP(bclr<3>),
			OP(bset<4>), OP(bclr<4>), OP(bset<5>), OP(bclr<5>), OP(bset<6>), OP(bclr<6>), OP(bset<7>), OP(bclr<7>),
	/* 2 */ OP_T(bra),   OP_F(bra),   OP_T(bhi),   OP_F(bhi),   OP_T(bcc),   OP_F(bcc),   OP_T(bne),   OP_F(bne),
			OP_T(bhcc),  OP_F(bhcc),  OP_T(bpl),   OP_F(bpl),   OP_T(bmc),   OP_F(bmc),   OP_T(bil),   OP_F(bil),
	/* 3 */ OP_DI(neg),  OP(illegal), OP(illegal), OP_DI(com),  OP_DI(lsr),  OP(illegal), OP_DI(ror),  OP_DI(asr),
			OP_DI(lsl),  OP_DI(rol),  OP_DI(dec),  OP(illegal), OP_DI(inc),  OP_DI(tst),  OP(illegal), OP_DI(clr),
	/* 4 */ OP(nega),    OP(illegal), OP(illegal), OP(coma),    OP(lsra),    OP(illegal), OP(rora),    OP(asra),
			OP(lsla),    OP(rola),    OP(deca),    OP(illegal), OP(inca),    OP(tsta),    OP(illegal), OP(clra),
	/* 5 */ OP(negx),    OP(illegal), OP(illegal), OP(comx),    OP(lsrx),    OP(illegal), OP(rorx),    OP(asrx),
			OP(lslx),    OP(rolx),    OP(decx),    OP(illegal), OP(incx),    OP(tstx),    OP(illegal), OP(clrx),
	/* 6 */ OP_IX1(neg), OP(illegal), OP(illegal), OP_IX1(com), OP_IX1(lsr), OP(illegal), OP_IX1(ror), OP_IX1(asr),
			OP_IX1(lsl), OP_IX1(rol), OP_IX1(dec), OP(illegal), OP_IX1(inc), OP_IX1(tst), OP(illegal), OP_IX1(clr),
	/* 7 */ OP_IX(neg),  OP(illegal), OP(illegal), OP_IX(com),  OP_IX(lsr),  OP(illegal), OP_IX(ror),  OP_IX(asr),
			OP_IX(lsl),  OP_IX(rol),  OP_IX(dec),  OP(illegal), OP_IX(inc),  OP_IX(tst),  OP(illegal), OP_IX(clr),
	/* 8 */ OP(rti),     OP(rts),     OP(illegal), OP(swi),     OP(illegal), OP(illegal), OP(illegal), OP(illegal),
			OP(illegal), OP(illegal), OP(illegal), OP(illegal), OP(illegal), OP(illegal), OP(stop),    OP(wait),
	/* 9 */ OP(illegal), OP(illegal), OP(illegal), OP(illegal), OP(illegal), OP(illegal), OP(illegal), OP(tax),
			OP(clc),     OP(sec),     OP(cli),     OP(sei),     OP(rsp),     OP(nop),     OP(illegal), OP(txa),
	/* A */ OP_IM(suba), OP_IM(cmpa), OP_IM(sbca), OP_IM(cpx),  OP_IM(anda), OP_IM(bita), OP_IM(lda),  OP(illegal),
			OP_IM(eora), OP_IM(adca), OP_IM(ora),  OP_IM(adda), OP(illegal), OP(bsr),     OP_IM(ldx),  OP(illegal),
	/* B */ OP_DI(suba), OP_DI(cmpa), OP_DI(sbca), OP_DI(cpx),  OP_DI(anda), OP_DI(bita), OP_DI(lda),  OP_DI(sta),
			OP_DI(eora), OP_DI(adca), OP_DI(ora),  OP_DI(adda), OP_DI(jmp),  OP_DI(jsr),  OP_DI(ldx),  OP_DI(stx),
	/* C */ OP_EX(suba), OP_EX(cmpa), OP_EX(sbca), OP_EX(cpx),  OP_EX(anda), OP_EX(bita), OP_EX(lda),  OP_EX(sta),
			OP_EX(eora), OP_EX(adca), OP_EX(ora),  OP_EX(adda), OP_EX(jmp),  OP_EX(jsr),  OP_EX(ldx),  OP_EX(stx),
	/* D */ OP_IX2(suba),OP_IX2(cmpa),OP_IX2(sbca),OP_IX2(cpx), OP_IX2(anda),OP_IX2(bita),OP_IX2(lda), OP_IX2(sta),
			OP_IX2(eora),OP_IX2(adca),OP_IX2(ora), OP_IX2(adda),OP_IX2(jmp), OP_IX2(jsr), OP_IX2(ldx), OP_IX2(stx),
	/* E */ OP_IX1(suba),OP_IX1(cmpa),OP_IX1(sbca),OP_IX1(cpx), OP_IX1(anda),OP_IX1(bita),OP_IX1(lda), OP_IX1(sta),
			OP_IX1(eora),OP_IX1(adca),OP_IX1(ora), OP_IX1(adda),OP_IX1(jmp), OP_IX1(jsr), OP_IX1(ldx), OP_IX1(stx),
	/* F */ OP_IX(suba), OP_IX(cmpa), OP_IX(sbca), OP_IX(cpx),  OP_IX(anda), OP_IX(bita), OP_IX(lda),  OP_IX(sta),
			OP_IX(eora), OP_IX(adca), OP_IX(ora),  OP_IX(adda), OP_IX(jmp),  OP_IX(jsr),  OP_IX(ldx),  OP_IX(stx)
};

const m6805_base_device::op_handler_table m6805_base_device::s_hc_ops =
{
	/*      0/8          1/9          2/A          3/B          4/C          5/D          6/E          7/F */
	/* 0 */ OP(brset<0>),OP(brclr<0>),OP(brset<1>),OP(brclr<1>),OP(brset<2>),OP(brclr<2>),OP(brset<3>),OP(brclr<3>),
			OP(brset<4>),OP(brclr<4>),OP(brset<5>),OP(brclr<5>),OP(brset<6>),OP(brclr<6>),OP(brset<7>),OP(brclr<7>),
	/* 1 */ OP(bset<0>), OP(bclr<0>), OP(bset<1>), OP(bclr<1>), OP(bset<2>), OP(bclr<2>), OP(bset<3>), OP(bclr<3>),
			OP(bset<4>), OP(bclr<4>), OP(bset<5>), OP(bclr<5>), OP(bset<6>), OP(bclr<6>), OP(bset<7>), OP(bclr<7>),
	/* 2 */ OP_T(bra),   OP_F(bra),   OP_T(bhi),   OP_F(bhi),   OP_T(bcc),   OP_F(bcc),   OP_T(bne),   OP_F(bne),
			OP_T(bhcc),  OP_F(bhcc),  OP_T(bpl),   OP_F(bpl),   OP_T(bmc),   OP_F(bmc),   OP_T(bil),   OP_F(bil),
	/* 3 */ OP_DI(neg),  OP(illegal), OP(illegal), OP_DI(com),  OP_DI(lsr),  OP(illegal), OP_DI(ror),  OP_DI(asr),
			OP_DI(lsl),  OP_DI(rol),  OP_DI(dec),  OP(illegal), OP_DI(inc),  OP_DI(tst),  OP(illegal), OP_DI(clr),
	/* 4 */ OP(nega),    OP(illegal), OP(mul),     OP(coma),    OP(lsra),    OP(illegal), OP(rora),    OP(asra),
			OP(lsla),    OP(rola),    OP(deca),    OP(illegal), OP(inca),    OP(tsta),    OP(illegal), OP(clra),
	/* 5 */ OP(negx),    OP(illegal), OP(illegal), OP(comx),    OP(lsrx),    OP(illegal), OP(rorx),    OP(asrx),
			OP(lslx),    OP(rolx),    OP(decx),    OP(illegal), OP(incx),    OP(tstx),    OP(illegal), OP(clrx),
	/* 6 */ OP_IX1(neg), OP(illegal), OP(illegal), OP_IX1(com), OP_IX1(lsr), OP(illegal), OP_IX1(ror), OP_IX1(asr),
			OP_IX1(lsl), OP_IX1(rol), OP_IX1(dec), OP(illegal), OP_IX1(inc), OP_IX1(tst), OP(illegal), OP_IX1(clr),
	/* 7 */ OP_IX(neg),  OP(illegal), OP(illegal), OP_IX(com),  OP_IX(lsr),  OP(illegal), OP_IX(ror),  OP_IX(asr),
			OP_IX(lsl),  OP_IX(rol),  OP_IX(dec),  OP(illegal), OP_IX(inc),  OP_IX(tst),  OP(illegal), OP_IX(clr),
	/* 8 */ OP(rti),     OP(rts),     OP(illegal), OP(swi),     OP(illegal), OP(illegal), OP(illegal), OP(illegal),
			OP(illegal), OP(illegal), OP(illegal), OP(illegal), OP(illegal), OP(illegal), OP(stop),    OP(wait),
	/* 9 */ OP(illegal), OP(illegal), OP(illegal), OP(illegal), OP(illegal), OP(illegal), OP(illegal), OP(tax),
			OP(clc),     OP(sec),     OP(cli),     OP(sei),     OP(rsp),     OP(nop),     OP(illegal), OP(txa),
	/* A */ OP_IM(suba), OP_IM(cmpa), OP_IM(sbca), OP_IM(cpx),  OP_IM(anda), OP_IM(bita), OP_IM(lda),  OP(illegal),
			OP_IM(eora), OP_IM(adca), OP_IM(ora),  OP_IM(adda), OP(illegal), OP(bsr),     OP_IM(ldx),  OP(illegal),
	/* B */ OP_DI(suba), OP_DI(cmpa), OP_DI(sbca), OP_DI(cpx),  OP_DI(anda), OP_DI(bita), OP_DI(lda),  OP_DI(sta),
			OP_DI(eora), OP_DI(adca), OP_DI(ora),  OP_DI(adda), OP_DI(jmp),  OP_DI(jsr),  OP_DI(ldx),  OP_DI(stx),
	/* C */ OP_EX(suba), OP_EX(cmpa), OP_EX(sbca), OP_EX(cpx),  OP_EX(anda), OP_EX(bita), OP_EX(lda),  OP_EX(sta),
			OP_EX(eora), OP_EX(adca), OP_EX(ora),  OP_EX(adda), OP_EX(jmp),  OP_EX(jsr),  OP_EX(ldx),  OP_EX(stx),
	/* D */ OP_IX2(suba),OP_IX2(cmpa),OP_IX2(sbca),OP_IX2(cpx), OP_IX2(anda),OP_IX2(bita),OP_IX2(lda), OP_IX2(sta),
			OP_IX2(eora),OP_IX2(adca),OP_IX2(ora), OP_IX2(adda),OP_IX2(jmp), OP_IX2(jsr), OP_IX2(ldx), OP_IX2(stx),
	/* E */ OP_IX1(suba),OP_IX1(cmpa),OP_IX1(sbca),OP_IX1(cpx), OP_IX1(anda),OP_IX1(bita),OP_IX1(lda), OP_IX1(sta),
			OP_IX1(eora),OP_IX1(adca),OP_IX1(ora), OP_IX1(adda),OP_IX1(jmp), OP_IX1(jsr), OP_IX1(ldx), OP_IX1(stx),
	/* F */ OP_IX(suba), OP_IX(cmpa), OP_IX(sbca), OP_IX(cpx),  OP_IX(anda), OP_IX(bita), OP_IX(lda),  OP_IX(sta),
			OP_IX(eora), OP_IX(adca), OP_IX(ora),  OP_IX(adda), OP_IX(jmp),  OP_IX(jsr),  OP_IX(ldx),  OP_IX(stx)
};


const m6805_base_device::cycle_count_table m6805_base_device::s_hmos_cycles =
>>>>>>> upstream/master
{
		/* 0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F */
	/*0*/ 10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,
	/*1*/  7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
<<<<<<< HEAD
	/*2*/  4, 0, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
	/*3*/  6, 0, 0, 6, 6, 0, 6, 6, 6, 6, 6, 6, 0, 6, 6, 0,
=======
	/*2*/  4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
	/*3*/  6, 0, 0, 6, 6, 0, 6, 6, 6, 6, 6, 0, 6, 6, 0, 6,
>>>>>>> upstream/master
	/*4*/  4, 0, 0, 4, 4, 0, 4, 4, 4, 4, 4, 0, 4, 4, 0, 4,
	/*5*/  4, 0, 0, 4, 4, 0, 4, 4, 4, 4, 4, 0, 4, 4, 0, 4,
	/*6*/  7, 0, 0, 7, 7, 0, 7, 7, 7, 7, 7, 0, 7, 7, 0, 7,
	/*7*/  6, 0, 0, 6, 6, 0, 6, 6, 6, 6, 6, 0, 6, 6, 0, 6,
	/*8*/  9, 6, 0,11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	/*9*/  0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 0, 2,
	/*A*/  2, 2, 2, 2, 2, 2, 2, 0, 2, 2, 2, 2, 0, 8, 2, 0,
	/*B*/  4, 4, 4, 4, 4, 4, 4, 5, 4, 4, 4, 4, 3, 7, 4, 5,
	/*C*/  5, 5, 5, 5, 5, 5, 5, 6, 5, 5, 5, 5, 4, 8, 5, 6,
	/*D*/  6, 6, 6, 6, 6, 6, 6, 7, 6, 6, 6, 6, 5, 9, 6, 7,
	/*E*/  5, 5, 5, 5, 5, 5, 5, 6, 5, 5, 5, 5, 4, 8, 5, 6,
	/*F*/  4, 4, 4, 4, 4, 4, 4, 5, 4, 4, 4, 4, 3, 7, 4, 5
};

<<<<<<< HEAD

/* pre-clear a PAIR union; clearing h2 and h3 only might be faster? */
#define CLEAR_PAIR(p)   p->d = 0

void m6805_base_device::rd_s_handler_b(UINT8 *b)
{
	SP_INC;
	*b = RM( S );
}

void m6805_base_device::rd_s_handler_w(PAIR *p)
{
	CLEAR_PAIR(p);
	SP_INC;
	p->b.h = RM( S );
	SP_INC;
	p->b.l = RM( S );
}

void m6805_base_device::wr_s_handler_b(UINT8 *b)
{
	WM( S, *b );
	SP_DEC;
}

void m6805_base_device::wr_s_handler_w(PAIR *p)
{
	WM( S, p->b.l );
	SP_DEC;
	WM( S, p->b.h );
	SP_DEC;
}

void m6805_base_device::RM16(UINT32 addr, PAIR *p)
{
	CLEAR_PAIR(p);
	p->b.h = RM(addr);
	++addr;
//  if( ++addr > AMASK ) addr = 0;
	p->b.l = RM(addr);
}

/* Generate interrupt - m68705 version */
void m68705_device::interrupt()
{
	if ((m_pending_interrupts & ((1 << M6805_IRQ_LINE) | M68705_INT_MASK)) != 0 )
	{
		if ((CC & IFLAG) == 0)
		{
			PUSHWORD(m_pc);
			PUSHBYTE(m_x);
			PUSHBYTE(m_a);
			PUSHBYTE(m_cc);
			SEI;
			standard_irq_callback(0);

			if ((m_pending_interrupts & (1 << M68705_IRQ_LINE)) != 0 )
			{
				m_pending_interrupts &= ~(1 << M68705_IRQ_LINE);
				RM16(0xfffa, &m_pc);
			}
			else if ((m_pending_interrupts & (1 << M68705_INT_TIMER)) != 0)
			{
				m_pending_interrupts &= ~(1 << M68705_INT_TIMER);
				RM16(0xfff8, &m_pc);
			}
		}
		m_icount -= 11;
	}
}

void m6805_base_device::interrupt_vector()
{
	RM16(0xffff - 5, &m_pc);
}

void m68hc05eg_device::interrupt_vector()
{
	if ((m_pending_interrupts & (1 << M68HC05EG_INT_IRQ)) != 0)
	{
		m_pending_interrupts &= ~(1 << M68HC05EG_INT_IRQ);
		RM16(0x1ffa, &m_pc);
	}
	else if((m_pending_interrupts & (1 << M68HC05EG_INT_TIMER)) != 0)
	{
		m_pending_interrupts &= ~(1 << M68HC05EG_INT_TIMER);
		RM16(0x1ff8, &m_pc);
	}
	else if((m_pending_interrupts & (1 << M68HC05EG_INT_CPI)) != 0)
	{
		m_pending_interrupts &= ~(1 << M68HC05EG_INT_CPI);
		RM16(0x1ff6, &m_pc);
	}
}

void hd63705_device::interrupt_vector()
{
	/* Need to add emulation of other interrupt sources here KW-2/4/99 */
	/* This is just a quick patch for Namco System 2 operation         */

	if ((m_pending_interrupts & (1 << HD63705_INT_IRQ1)) != 0)
	{
		m_pending_interrupts &= ~(1 << HD63705_INT_IRQ1);
		RM16(0x1ff8, &m_pc);
	}
	else if ((m_pending_interrupts & (1 << HD63705_INT_IRQ2)) != 0)
	{
		m_pending_interrupts &= ~(1 << HD63705_INT_IRQ2);
		RM16(0x1fec, &m_pc);
	}
	else if ((m_pending_interrupts & (1 << HD63705_INT_ADCONV)) != 0)
	{
		m_pending_interrupts &= ~(1 << HD63705_INT_ADCONV);
		RM16(0x1fea, &m_pc);
	}
	else if ((m_pending_interrupts & (1 << HD63705_INT_TIMER1)) != 0)
	{
		m_pending_interrupts &= ~(1 << HD63705_INT_TIMER1);
		RM16(0x1ff6, &m_pc);
	}
	else if ((m_pending_interrupts & (1 << HD63705_INT_TIMER2)) != 0)
	{
		m_pending_interrupts &= ~(1 << HD63705_INT_TIMER2);
		RM16(0x1ff4, &m_pc);
	}
	else if ((m_pending_interrupts & (1 << HD63705_INT_TIMER3)) != 0)
	{
		m_pending_interrupts &= ~(1<<HD63705_INT_TIMER3);
		RM16(0x1ff2, &m_pc);
	}
	else if ((m_pending_interrupts & (1 << HD63705_INT_PCI)) != 0)
	{
		m_pending_interrupts &= ~(1 << HD63705_INT_PCI);
		RM16(0x1ff0, &m_pc);
	}
	else if ((m_pending_interrupts & (1 << HD63705_INT_SCI)) != 0)
	{
		m_pending_interrupts &= ~(1 << HD63705_INT_SCI);
		RM16(0x1fee, &m_pc);
	}
}

/* Generate interrupts */
void m6805_base_device::interrupt()
{
	/* the 6805 latches interrupt requests internally, so we don't clear */
	/* pending_interrupts until the interrupt is taken, no matter what the */
	/* external IRQ pin does. */

	if ((m_pending_interrupts & (1 << HD63705_INT_NMI)) != 0)
	{
		PUSHWORD(m_pc);
		PUSHBYTE(m_x);
		PUSHBYTE(m_a);
		PUSHBYTE(m_cc);
		SEI;
		/* no vectors supported, just do the callback to clear irq_state if needed */
		standard_irq_callback(0);

		RM16(0x1ffc, &m_pc);
		m_pending_interrupts &= ~(1 << HD63705_INT_NMI);

		m_icount -= 11;
	}
	else if((m_pending_interrupts & ((1 << M6805_IRQ_LINE) | HD63705_INT_MASK)) != 0)
	{
		if ((CC & IFLAG) == 0)
		{
			/* standard IRQ */
			PUSHWORD(m_pc);
			PUSHBYTE(m_x);
			PUSHBYTE(m_a);
			PUSHBYTE(m_cc);
			SEI;
			/* no vectors supported, just do the callback to clear irq_state if needed */
			standard_irq_callback(0);

			interrupt_vector();

			m_pending_interrupts &= ~(1 << M6805_IRQ_LINE);
		}
		m_icount -= 11;
	}
}


//-------------------------------------------------
//  m6809_base_device - constructor
//-------------------------------------------------

m6805_base_device::m6805_base_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock, const device_type type, const char *name, UINT32 addr_width, const char *shortname, const char *source)
	: cpu_device(mconfig, type, name, tag, owner, clock, shortname, source),
	m_program_config("program", ENDIANNESS_BIG, 8, addr_width)
{
}
=======
const m6805_base_device::cycle_count_table m6805_base_device::s_cmos_cycles =
{
		/* 0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F */
	/*0*/  5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
	/*1*/  5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
	/*2*/  3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
	/*3*/  5, 0, 0, 5, 5, 0, 5, 5, 5, 5, 5, 0, 5, 4, 0, 5,
	/*4*/  3, 0, 0, 3, 3, 0, 3, 3, 3, 3, 3, 0, 3, 3, 0, 3,
	/*5*/  3, 0, 0, 3, 3, 0, 3, 3, 3, 3, 3, 0, 3, 3, 0, 3,
	/*6*/  6, 0, 0, 6, 6, 0, 6, 6, 6, 6, 6, 0, 6, 5, 0, 6,
	/*7*/  5, 0, 0, 5, 5, 0, 5, 5, 5, 5, 5, 0, 5, 4, 0, 5,
	/*8*/  9, 6, 0,10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2,
	/*9*/  0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 0, 2,
	/*A*/  2, 2, 2, 2, 2, 2, 2, 0, 2, 2, 2, 2, 0, 6, 2, 0,
	/*B*/  3, 3, 3, 3, 3, 3, 3, 4, 3, 3, 3, 3, 2, 5, 3, 4,
	/*C*/  4, 4, 4, 4, 4, 4, 4, 5, 4, 4, 4, 4, 3, 6, 4, 5,
	/*D*/  5, 5, 5, 5, 5, 5, 5, 6, 5, 5, 5, 5, 4, 7, 5, 6,
	/*E*/  4, 4, 4, 4, 4, 4, 4, 5, 4, 4, 4, 4, 3, 6, 4, 5,
	/*F*/  3, 3, 3, 3, 3, 3, 3, 4, 3, 3, 3, 3, 2, 5, 3, 4
};

const m6805_base_device::cycle_count_table m6805_base_device::s_hc_cycles =
{
		/* 0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F */
	/*0*/  5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
	/*1*/  5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
	/*2*/  3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
	/*3*/  5, 0, 0, 5, 5, 0, 5, 5, 5, 5, 5, 0, 5, 4, 0, 5,
	/*4*/  3, 0,11, 3, 3, 0, 3, 3, 3, 3, 3, 0, 3, 3, 0, 3,
	/*5*/  3, 0, 0, 3, 3, 0, 3, 3, 3, 3, 3, 0, 3, 3, 0, 3,
	/*6*/  6, 0, 0, 6, 6, 0, 6, 6, 6, 6, 6, 0, 6, 5, 0, 6,
	/*7*/  5, 0, 0, 5, 5, 0, 5, 5, 5, 5, 5, 0, 5, 4, 0, 5,
	/*8*/  9, 6, 0,10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2,
	/*9*/  0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 0, 2,
	/*A*/  2, 2, 2, 2, 2, 2, 2, 0, 2, 2, 2, 2, 0, 6, 2, 0,
	/*B*/  3, 3, 3, 3, 3, 3, 3, 4, 3, 3, 3, 3, 2, 5, 3, 4,
	/*C*/  4, 4, 4, 4, 4, 4, 4, 5, 4, 4, 4, 4, 3, 6, 4, 5,
	/*D*/  5, 5, 5, 5, 5, 5, 5, 6, 5, 5, 5, 5, 4, 7, 5, 6,
	/*E*/  4, 4, 4, 4, 4, 4, 4, 5, 4, 4, 4, 4, 3, 6, 4, 5,
	/*F*/  3, 3, 3, 3, 3, 3, 3, 4, 3, 3, 3, 3, 2, 5, 3, 4
};


//-------------------------------------------------
//  m6809_base_device - constructor
//-------------------------------------------------

m6805_base_device::m6805_base_device(
		machine_config const &mconfig,
		char const *tag,
		device_t *owner,
		uint32_t clock,
		device_type const type,
		configuration_params const &params)
	: cpu_device(mconfig, type, tag, owner, clock)
	, m_params(params)
	, m_program_config("program", ENDIANNESS_BIG, 8, params.m_addr_width)
{
}

m6805_base_device::m6805_base_device(
		machine_config const &mconfig,
		char const *tag,
		device_t *owner,
		uint32_t clock,
		device_type const type,
		configuration_params const &params,
		address_map_delegate internal_map)
	: cpu_device(mconfig, type, tag, owner, clock)
	, m_params(params)
	, m_program_config("program", ENDIANNESS_BIG, 8, params.m_addr_width, 0, internal_map)
{
}


>>>>>>> upstream/master

void m6805_base_device::device_start()
{
	m_program = &space(AS_PROGRAM);
	m_direct = &m_program->direct();

	// set our instruction counter
	m_icountptr = &m_icount;

	// register our state for the debugger
	state_add(STATE_GENPC,     "GENPC",     m_pc.w.l).noshow();
<<<<<<< HEAD
=======
	state_add(STATE_GENPCBASE, "CURPC",     m_pc.w.l).noshow();
>>>>>>> upstream/master
	state_add(STATE_GENFLAGS,  "GENFLAGS",  m_cc).callimport().callexport().formatstr("%8s").noshow();
	state_add(M6805_A,         "A",         m_a).mask(0xff);
	state_add(M6805_PC,        "PC",        m_pc.w.l).mask(0xffff);
	state_add(M6805_S,         "S",         m_s.w.l).mask(0xff);
	state_add(M6805_X,         "X",         m_x).mask(0xff);
	state_add(M6805_CC,        "CC",        m_cc).mask(0xff);

	// register for savestates
	save_item(NAME(EA));
<<<<<<< HEAD
	save_item(NAME(SP_MASK));
	save_item(NAME(SP_LOW));
=======
>>>>>>> upstream/master
	save_item(NAME(A));
	save_item(NAME(PC));
	save_item(NAME(S));
	save_item(NAME(X));
	save_item(NAME(CC));
	save_item(NAME(m_pending_interrupts));
	save_item(NAME(m_irq_state));
	save_item(NAME(m_nmi_state));
<<<<<<< HEAD
}

=======

	std::fill(std::begin(m_irq_state), std::end(m_irq_state), CLEAR_LINE);
}
>>>>>>> upstream/master

void m6805_base_device::device_reset()
{
	m_ea.w.l = 0;
<<<<<<< HEAD
	m_sp_mask = 0x07f;
	m_sp_low = 0x060;
=======
>>>>>>> upstream/master
	m_pc.w.l = 0;
	m_s.w.l = SP_MASK;
	m_a = 0;
	m_x = 0;
	m_cc = 0;
	m_pending_interrupts = 0;

<<<<<<< HEAD
	memset(m_irq_state, 0, sizeof(int) * 9);
=======
>>>>>>> upstream/master
	m_nmi_state = 0;

	m_program = &space(AS_PROGRAM);
	m_direct = &m_program->direct();

	/* IRQ disabled */
	SEI;

<<<<<<< HEAD
	RM16(0xfffe, &m_pc);
=======
	rm16(0xfffe, m_pc);
>>>>>>> upstream/master
}


//-------------------------------------------------
//  memory_space_config - return the configuration
<<<<<<< HEAD
//  of the specified address space, or NULL if
//  the space doesn't exist
//-------------------------------------------------

const address_space_config *m6805_base_device::memory_space_config(address_spacenum spacenum) const
{
	if (spacenum == AS_PROGRAM)
	{
		return &m_program_config;
	}
	return NULL;
=======
//  of the specified address space, or nullptr if
//  the space doesn't exist
//-------------------------------------------------

device_memory_interface::space_config_vector m6805_base_device::memory_space_config() const
{
	return space_config_vector {
		std::make_pair(AS_PROGRAM, &m_program_config)
	};
>>>>>>> upstream/master
}


//-------------------------------------------------
//  state_string_export - export state as a string
//  for the debugger
//-------------------------------------------------

<<<<<<< HEAD
void m6805_base_device::state_string_export(const device_state_entry &entry, std::string &str)
{
	switch (entry.index())
	{
		case STATE_GENFLAGS:
			strprintf(str, "%c%c%c%c%c%c%c%c",
				(m_cc & 0x80) ? '?' : '.',
				(m_cc & 0x40) ? '?' : '.',
				(m_cc & 0x20) ? '?' : '.',
				(m_cc & 0x10) ? 'H' : '.',
				(m_cc & 0x08) ? 'I' : '.',
				(m_cc & 0x04) ? 'N' : '.',
				(m_cc & 0x02) ? 'Z' : '.',
				(m_cc & 0x01) ? 'C' : '.');
			break;
=======
void m6805_base_device::state_string_export(const device_state_entry &entry, std::string &str) const
{
	switch (entry.index())
	{
	case STATE_GENFLAGS:
		str = string_format("%c%c%c%c%c%c%c%c",
			(m_cc & 0x80) ? '?' : '.',
			(m_cc & 0x40) ? '?' : '.',
			(m_cc & 0x20) ? '?' : '.',
			(m_cc & 0x10) ? 'H' : '.',
			(m_cc & 0x08) ? 'I' : '.',
			(m_cc & 0x04) ? 'N' : '.',
			(m_cc & 0x02) ? 'Z' : '.',
			(m_cc & 0x01) ? 'C' : '.');
		break;
	}
}


bool m6805_base_device::test_il()
{
	return CLEAR_LINE != m_irq_state[M6805_IRQ_LINE];
}

void m6805_base_device::interrupt_vector()
{
	rm16(0xfffa, m_pc);
}

/* Generate interrupts */
void m6805_base_device::interrupt()
{
	/* the 6805 latches interrupt requests internally, so we don't clear */
	/* pending_interrupts until the interrupt is taken, no matter what the */
	/* external IRQ pin does. */

	if (BIT(m_pending_interrupts, HD63705_INT_NMI))
	{
		pushword(m_pc);
		pushbyte(m_x);
		pushbyte(m_a);
		pushbyte(m_cc);
		SEI;
		/* no vectors supported, just do the callback to clear irq_state if needed */
		standard_irq_callback(0);

		rm16(0x1ffc, m_pc);
		m_pending_interrupts &= ~(1 << HD63705_INT_NMI);

		m_icount -= 11;
		burn_cycles(11);
	}
	else if ((m_pending_interrupts & ((1 << M6805_IRQ_LINE) | HD63705_INT_MASK)) != 0)
	{
		if ((CC & IFLAG) == 0)
		{
			/* standard IRQ */
			pushword(m_pc);
			pushbyte(m_x);
			pushbyte(m_a);
			pushbyte(m_cc);
			SEI;
			/* no vectors supported, just do the callback to clear irq_state if needed */
			standard_irq_callback(0);

			interrupt_vector();

			m_pending_interrupts &= ~(1 << M6805_IRQ_LINE);

			m_icount -= 11;
			burn_cycles(11);
		}
>>>>>>> upstream/master
	}
}


//-------------------------------------------------
//  disasm_min_opcode_bytes - return the length
//  of the shortest instruction, in bytes
//-------------------------------------------------

<<<<<<< HEAD
UINT32 m6805_base_device::disasm_min_opcode_bytes() const
=======
uint32_t m6805_base_device::disasm_min_opcode_bytes() const
>>>>>>> upstream/master
{
	return 1;
}


//-------------------------------------------------
//  disasm_max_opcode_bytes - return the length
//  of the longest instruction, in bytes
//-------------------------------------------------

<<<<<<< HEAD
UINT32 m6805_base_device::disasm_max_opcode_bytes() const
=======
uint32_t m6805_base_device::disasm_max_opcode_bytes() const
>>>>>>> upstream/master
{
	return 3;
}


//-------------------------------------------------
//  disasm_disassemble - call the disassembly
//  helper function
//-------------------------------------------------

<<<<<<< HEAD
offs_t m6805_base_device::disasm_disassemble(char *buffer, offs_t pc, const UINT8 *oprom, const UINT8 *opram, UINT32 options)
{
	extern CPU_DISASSEMBLE( m6805 );
	return CPU_DISASSEMBLE_NAME(m6805)(this, buffer, pc, oprom, opram, options);
}


void m6805_device::execute_set_input(int inputnum, int state)
{
	/* Basic 6805 only has one IRQ line */
	/* See HD63705 specific version     */
	if (m_irq_state[0] != state)
	{
		m_irq_state[0] = state;

		if (state != CLEAR_LINE)
		{
			m_pending_interrupts |= 1 << M6805_IRQ_LINE;
		}
	}
}

#include "6805ops.inc"
=======
offs_t m6805_base_device::disasm_disassemble(std::ostream &stream, offs_t pc, const uint8_t *oprom, const uint8_t *opram, uint32_t options)
{
	return CPU_DISASSEMBLE_NAME(m6805)(this, stream, pc, oprom, opram, options);
}


#include "6805ops.hxx"
>>>>>>> upstream/master

//-------------------------------------------------
//  execute_clocks_to_cycles - convert the raw
//  clock into cycles per second
//-------------------------------------------------

<<<<<<< HEAD
UINT64 m6805_base_device::execute_clocks_to_cycles(UINT64 clocks) const
=======
uint64_t m6805_base_device::execute_clocks_to_cycles(uint64_t clocks) const
>>>>>>> upstream/master
{
	return (clocks + 3) / 4;
}


//-------------------------------------------------
//  execute_cycles_to_clocks - convert a cycle
//  count back to raw clocks
//-------------------------------------------------

<<<<<<< HEAD
UINT64 m6805_base_device::execute_cycles_to_clocks(UINT64 cycles) const
=======
uint64_t m6805_base_device::execute_cycles_to_clocks(uint64_t cycles) const
>>>>>>> upstream/master
{
	return cycles * 4;
}


//-------------------------------------------------
//  execute_min_cycles - return minimum number of
//  cycles it takes for one instruction to execute
//-------------------------------------------------

<<<<<<< HEAD
UINT32 m6805_base_device::execute_min_cycles() const
{
	return 2;
=======
uint32_t m6805_base_device::execute_min_cycles() const
{
	// get the minimum not including the zero placeholders for illegal instructions
	u32 const result(*std::min_element(
			std::begin(m_params.m_cycles),
			std::end(m_params.m_cycles),
			[] (u8 x, u8 y) { return u8(x - 1) < u8(y - 1); }));
	return result;
>>>>>>> upstream/master
}


//-------------------------------------------------
//  execute_max_cycles - return maximum number of
//  cycles it takes for one instruction to execute
//-------------------------------------------------

<<<<<<< HEAD
UINT32 m6805_base_device::execute_max_cycles() const
{
	return 10;
=======
uint32_t m6805_base_device::execute_max_cycles() const
{
	u32 const result(*std::max_element(std::begin(m_params.m_cycles), std::end(m_params.m_cycles)));
	return result;
>>>>>>> upstream/master
}


//-------------------------------------------------
//  execute_input_lines - return the number of
//  input/interrupt lines
//-------------------------------------------------

<<<<<<< HEAD
UINT32 m6805_base_device::execute_input_lines() const
=======
uint32_t m6805_base_device::execute_input_lines() const
>>>>>>> upstream/master
{
	return 9;
}


/* execute instructions on this CPU until icount expires */
void m6805_base_device::execute_run()
{
<<<<<<< HEAD
	UINT8 ireg;

=======
>>>>>>> upstream/master
	S = SP_ADJUST( S );     /* Taken from CPU_SET_CONTEXT when pointer'afying */

	do
	{
		if (m_pending_interrupts != 0)
		{
			interrupt();
		}

		debugger_instruction_hook(this, PC);

<<<<<<< HEAD
		ireg=M_RDOP(PC++);

		switch( ireg )
		{
			case 0x00: brset(0x01); break;
			case 0x01: brclr(0x01); break;
			case 0x02: brset(0x02); break;
			case 0x03: brclr(0x02); break;
			case 0x04: brset(0x04); break;
			case 0x05: brclr(0x04); break;
			case 0x06: brset(0x08); break;
			case 0x07: brclr(0x08); break;
			case 0x08: brset(0x10); break;
			case 0x09: brclr(0x10); break;
			case 0x0A: brset(0x20); break;
			case 0x0B: brclr(0x20); break;
			case 0x0C: brset(0x40); break;
			case 0x0D: brclr(0x40); break;
			case 0x0E: brset(0x80); break;
			case 0x0F: brclr(0x80); break;
			case 0x10: bset(0x01); break;
			case 0x11: bclr(0x01); break;
			case 0x12: bset(0x02); break;
			case 0x13: bclr(0x02); break;
			case 0x14: bset(0x04); break;
			case 0x15: bclr(0x04); break;
			case 0x16: bset(0x08); break;
			case 0x17: bclr(0x08); break;
			case 0x18: bset(0x10); break;
			case 0x19: bclr(0x10); break;
			case 0x1a: bset(0x20); break;
			case 0x1b: bclr(0x20); break;
			case 0x1c: bset(0x40); break;
			case 0x1d: bclr(0x40); break;
			case 0x1e: bset(0x80); break;
			case 0x1f: bclr(0x80); break;
			case 0x20: bra(); break;
			case 0x21: brn(); break;
			case 0x22: bhi(); break;
			case 0x23: bls(); break;
			case 0x24: bcc(); break;
			case 0x25: bcs(); break;
			case 0x26: bne(); break;
			case 0x27: beq(); break;
			case 0x28: bhcc(); break;
			case 0x29: bhcs(); break;
			case 0x2a: bpl(); break;
			case 0x2b: bmi(); break;
			case 0x2c: bmc(); break;
			case 0x2d: bms(); break;
			case 0x2e: bil(); break;
			case 0x2f: bih(); break;
			case 0x30: neg_di(); break;
			case 0x31: illegal(); break;
			case 0x32: illegal(); break;
			case 0x33: com_di(); break;
			case 0x34: lsr_di(); break;
			case 0x35: illegal(); break;
			case 0x36: ror_di(); break;
			case 0x37: asr_di(); break;
			case 0x38: lsl_di(); break;
			case 0x39: rol_di(); break;
			case 0x3a: dec_di(); break;
			case 0x3b: illegal(); break;
			case 0x3c: inc_di(); break;
			case 0x3d: tst_di(); break;
			case 0x3e: illegal(); break;
			case 0x3f: clr_di(); break;
			case 0x40: nega(); break;
			case 0x41: illegal(); break;
			case 0x42: illegal(); break;
			case 0x43: coma(); break;
			case 0x44: lsra(); break;
			case 0x45: illegal(); break;
			case 0x46: rora(); break;
			case 0x47: asra(); break;
			case 0x48: lsla(); break;
			case 0x49: rola(); break;
			case 0x4a: deca(); break;
			case 0x4b: illegal(); break;
			case 0x4c: inca(); break;
			case 0x4d: tsta(); break;
			case 0x4e: illegal(); break;
			case 0x4f: clra(); break;
			case 0x50: negx(); break;
			case 0x51: illegal(); break;
			case 0x52: illegal(); break;
			case 0x53: comx(); break;
			case 0x54: lsrx(); break;
			case 0x55: illegal(); break;
			case 0x56: rorx(); break;
			case 0x57: asrx(); break;
			case 0x58: aslx(); break;
			case 0x59: rolx(); break;
			case 0x5a: decx(); break;
			case 0x5b: illegal(); break;
			case 0x5c: incx(); break;
			case 0x5d: tstx(); break;
			case 0x5e: illegal(); break;
			case 0x5f: clrx(); break;
			case 0x60: neg_ix1(); break;
			case 0x61: illegal(); break;
			case 0x62: illegal(); break;
			case 0x63: com_ix1(); break;
			case 0x64: lsr_ix1(); break;
			case 0x65: illegal(); break;
			case 0x66: ror_ix1(); break;
			case 0x67: asr_ix1(); break;
			case 0x68: lsl_ix1(); break;
			case 0x69: rol_ix1(); break;
			case 0x6a: dec_ix1(); break;
			case 0x6b: illegal(); break;
			case 0x6c: inc_ix1(); break;
			case 0x6d: tst_ix1(); break;
			case 0x6e: illegal(); break;
			case 0x6f: clr_ix1(); break;
			case 0x70: neg_ix(); break;
			case 0x71: illegal(); break;
			case 0x72: illegal(); break;
			case 0x73: com_ix(); break;
			case 0x74: lsr_ix(); break;
			case 0x75: illegal(); break;
			case 0x76: ror_ix(); break;
			case 0x77: asr_ix(); break;
			case 0x78: lsl_ix(); break;
			case 0x79: rol_ix(); break;
			case 0x7a: dec_ix(); break;
			case 0x7b: illegal(); break;
			case 0x7c: inc_ix(); break;
			case 0x7d: tst_ix(); break;
			case 0x7e: illegal(); break;
			case 0x7f: clr_ix(); break;
			case 0x80: rti(); break;
			case 0x81: rts(); break;
			case 0x82: illegal(); break;
			case 0x83: swi(); break;
			case 0x84: illegal(); break;
			case 0x85: illegal(); break;
			case 0x86: illegal(); break;
			case 0x87: illegal(); break;
			case 0x88: illegal(); break;
			case 0x89: illegal(); break;
			case 0x8a: illegal(); break;
			case 0x8b: illegal(); break;
			case 0x8c: illegal(); break;
			case 0x8d: illegal(); break;
			case 0x8e: illegal(); break;
			case 0x8f: illegal(); break;
			case 0x90: illegal(); break;
			case 0x91: illegal(); break;
			case 0x92: illegal(); break;
			case 0x93: illegal(); break;
			case 0x94: illegal(); break;
			case 0x95: illegal(); break;
			case 0x96: illegal(); break;
			case 0x97: tax(); break;
			case 0x98: CLC; break;
			case 0x99: SEC; break;
#if IRQ_LEVEL_DETECT
			case 0x9a: CLI; if (m_irq_state != CLEAR_LINE) m_pending_interrupts |= 1 << M6805_IRQ_LINE; break;
#else
			case 0x9a: CLI; break;
#endif
			case 0x9b: SEI; break;
			case 0x9c: rsp(); break;
			case 0x9d: nop(); break;
			case 0x9e: illegal(); break;
			case 0x9f: txa(); break;
			case 0xa0: suba_im(); break;
			case 0xa1: cmpa_im(); break;
			case 0xa2: sbca_im(); break;
			case 0xa3: cpx_im(); break;
			case 0xa4: anda_im(); break;
			case 0xa5: bita_im(); break;
			case 0xa6: lda_im(); break;
			case 0xa7: illegal(); break;
			case 0xa8: eora_im(); break;
			case 0xa9: adca_im(); break;
			case 0xaa: ora_im(); break;
			case 0xab: adda_im(); break;
			case 0xac: illegal(); break;
			case 0xad: bsr(); break;
			case 0xae: ldx_im(); break;
			case 0xaf: illegal(); break;
			case 0xb0: suba_di(); break;
			case 0xb1: cmpa_di(); break;
			case 0xb2: sbca_di(); break;
			case 0xb3: cpx_di(); break;
			case 0xb4: anda_di(); break;
			case 0xb5: bita_di(); break;
			case 0xb6: lda_di(); break;
			case 0xb7: sta_di(); break;
			case 0xb8: eora_di(); break;
			case 0xb9: adca_di(); break;
			case 0xba: ora_di(); break;
			case 0xbb: adda_di(); break;
			case 0xbc: jmp_di(); break;
			case 0xbd: jsr_di(); break;
			case 0xbe: ldx_di(); break;
			case 0xbf: stx_di(); break;
			case 0xc0: suba_ex(); break;
			case 0xc1: cmpa_ex(); break;
			case 0xc2: sbca_ex(); break;
			case 0xc3: cpx_ex(); break;
			case 0xc4: anda_ex(); break;
			case 0xc5: bita_ex(); break;
			case 0xc6: lda_ex(); break;
			case 0xc7: sta_ex(); break;
			case 0xc8: eora_ex(); break;
			case 0xc9: adca_ex(); break;
			case 0xca: ora_ex(); break;
			case 0xcb: adda_ex(); break;
			case 0xcc: jmp_ex(); break;
			case 0xcd: jsr_ex(); break;
			case 0xce: ldx_ex(); break;
			case 0xcf: stx_ex(); break;
			case 0xd0: suba_ix2(); break;
			case 0xd1: cmpa_ix2(); break;
			case 0xd2: sbca_ix2(); break;
			case 0xd3: cpx_ix2(); break;
			case 0xd4: anda_ix2(); break;
			case 0xd5: bita_ix2(); break;
			case 0xd6: lda_ix2(); break;
			case 0xd7: sta_ix2(); break;
			case 0xd8: eora_ix2(); break;
			case 0xd9: adca_ix2(); break;
			case 0xda: ora_ix2(); break;
			case 0xdb: adda_ix2(); break;
			case 0xdc: jmp_ix2(); break;
			case 0xdd: jsr_ix2(); break;
			case 0xde: ldx_ix2(); break;
			case 0xdf: stx_ix2(); break;
			case 0xe0: suba_ix1(); break;
			case 0xe1: cmpa_ix1(); break;
			case 0xe2: sbca_ix1(); break;
			case 0xe3: cpx_ix1(); break;
			case 0xe4: anda_ix1(); break;
			case 0xe5: bita_ix1(); break;
			case 0xe6: lda_ix1(); break;
			case 0xe7: sta_ix1(); break;
			case 0xe8: eora_ix1(); break;
			case 0xe9: adca_ix1(); break;
			case 0xea: ora_ix1(); break;
			case 0xeb: adda_ix1(); break;
			case 0xec: jmp_ix1(); break;
			case 0xed: jsr_ix1(); break;
			case 0xee: ldx_ix1(); break;
			case 0xef: stx_ix1(); break;
			case 0xf0: suba_ix(); break;
			case 0xf1: cmpa_ix(); break;
			case 0xf2: sbca_ix(); break;
			case 0xf3: cpx_ix(); break;
			case 0xf4: anda_ix(); break;
			case 0xf5: bita_ix(); break;
			case 0xf6: lda_ix(); break;
			case 0xf7: sta_ix(); break;
			case 0xf8: eora_ix(); break;
			case 0xf9: adca_ix(); break;
			case 0xfa: ora_ix(); break;
			case 0xfb: adda_ix(); break;
			case 0xfc: jmp_ix(); break;
			case 0xfd: jsr_ix(); break;
			case 0xfe: ldx_ix(); break;
			case 0xff: stx_ix(); break;
		}
		m_icount -= m_cycles1[ireg];
	} while( m_icount > 0 );
}

/****************************************************************************
 * M68HC05EG section
 ****************************************************************************/
void m68hc05eg_device::device_reset()
{
	m6805_base_device::device_reset();

	m_sp_mask = 0xff;
	m_sp_low = 0xc0;

	RM16(0x1ffe, &m_pc);
}

void m68hc05eg_device::execute_set_input(int inputnum, int state)
{
	if (m_irq_state[inputnum] != state)
	{
		m_irq_state[inputnum] = state;

		if (state != CLEAR_LINE)
		{
			m_pending_interrupts |= 1 << inputnum;
		}
=======
		u8 const ireg = rdop(PC++);

		(this->*m_params.m_ops[ireg])();
		m_icount -= m_params.m_cycles[ireg];
		burn_cycles(m_params.m_cycles[ireg]);
	}
	while (m_icount > 0);
}

void m6805_base_device::execute_set_input(int inputnum, int state)
{
	// Basic 6805 only has one IRQ line
	// See HD63705 specific version
	if (m_irq_state[inputnum] != state)
	{
		m_irq_state[inputnum] = (ASSERT_LINE == state) ? ASSERT_LINE : CLEAR_LINE;

		if (CLEAR_LINE != state)
			m_pending_interrupts |= (1 << inputnum);
>>>>>>> upstream/master
	}
}


<<<<<<< HEAD
/****************************************************************************
 * M68705 section
 ****************************************************************************/
void m68705_device::device_reset()
{
	m6805_base_device::device_reset();

	RM16(0xfffe, &m_pc);
}

void m68705_device::execute_set_input(int inputnum, int state)
{
	if (m_irq_state[inputnum] != state)
	{
		m_irq_state[inputnum] = state;

		if (state != CLEAR_LINE)
		{
			m_pending_interrupts |= 1 << inputnum;
		}
=======
m6805_device::m6805_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock)
	: m6805_base_device(
			mconfig,
			tag,
			owner,
			clock,
			M6805,
			{ s_hmos_ops, s_hmos_cycles, 12, 0x007f, 0x0060, 0xfffc })
{
}

/****************************************************************************
 * M68HC05EG section
 ****************************************************************************/
m68hc05eg_device::m68hc05eg_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock)
	: m6805_base_device(
			mconfig,
			tag,
			owner,
			clock,
			M68HC05EG,
			{ s_hmos_ops, s_hmos_cycles, 13, 0x00ff, 0x00c0, 0xfffc }) // completely wrong, but it preserves existing behaviour
{
}

void m68hc05eg_device::device_reset()
{
	m6805_base_device::device_reset();

	rm16(0x1ffe, m_pc);
}

void m68hc05eg_device::interrupt_vector()
{
	if (BIT(m_pending_interrupts, M68HC05EG_INT_IRQ))
	{
		m_pending_interrupts &= ~(1 << M68HC05EG_INT_IRQ);
		rm16(0x1ffa, m_pc);
	}
	else if (BIT(m_pending_interrupts, M68HC05EG_INT_TIMER))
	{
		m_pending_interrupts &= ~(1 << M68HC05EG_INT_TIMER);
		rm16(0x1ff8, m_pc);
	}
	else if (BIT(m_pending_interrupts, M68HC05EG_INT_CPI))
	{
		m_pending_interrupts &= ~(1 << M68HC05EG_INT_CPI);
		rm16(0x1ff6, m_pc);
>>>>>>> upstream/master
	}
}


/****************************************************************************
 * HD63705 section
 ****************************************************************************/
<<<<<<< HEAD
=======
hd63705_device::hd63705_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock)
	: m6805_base_device(mconfig,
			tag,
			owner,
			clock,
			HD63705,
			{ s_hmos_ops, s_hmos_cycles, 16, 0x017f, 0x0100, 0x1ffa })
{
}

>>>>>>> upstream/master
void hd63705_device::device_reset()
{
	m6805_base_device::device_reset();

<<<<<<< HEAD
	m_sp_mask = 0x17f;
	m_sp_low = 0x100;
	m_s.w.l = SP_MASK;

	RM16(0x1ffe, &m_pc);
=======
	m_s.w.l = SP_MASK;

	rm16(0x1ffe, m_pc);
>>>>>>> upstream/master
}

void hd63705_device::execute_set_input(int inputnum, int state)
{
	if (inputnum == INPUT_LINE_NMI)
	{
		if (m_nmi_state != state)
		{
			m_nmi_state = state;

			if (state != CLEAR_LINE)
			{
				m_pending_interrupts |= 1 << HD63705_INT_NMI;
			}
		}
	}
	else if (inputnum <= HD63705_INT_ADCONV)
	{
		if (m_irq_state[inputnum] != state)
		{
			m_irq_state[inputnum] = state;

			if (state != CLEAR_LINE)
			{
				m_pending_interrupts |= 1 << inputnum;
			}
		}
	}
}

<<<<<<< HEAD
const device_type M6805 = &device_creator<m6805_device>;
const device_type M68HC05EG = &device_creator<m68hc05eg_device>;
const device_type M68705 = &device_creator<m68705_device>;
const device_type HD63705 = &device_creator<hd63705_device>;
=======
void hd63705_device::interrupt_vector()
{
	/* Need to add emulation of other interrupt sources here KW-2/4/99 */
	/* This is just a quick patch for Namco System 2 operation         */

	if ((m_pending_interrupts & (1 << HD63705_INT_IRQ1)) != 0)
	{
		m_pending_interrupts &= ~(1 << HD63705_INT_IRQ1);
		rm16(0x1ff8, m_pc);
	}
	else if ((m_pending_interrupts & (1 << HD63705_INT_IRQ2)) != 0)
	{
		m_pending_interrupts &= ~(1 << HD63705_INT_IRQ2);
		rm16(0x1fec, m_pc);
	}
	else if ((m_pending_interrupts & (1 << HD63705_INT_ADCONV)) != 0)
	{
		m_pending_interrupts &= ~(1 << HD63705_INT_ADCONV);
		rm16(0x1fea, m_pc);
	}
	else if ((m_pending_interrupts & (1 << HD63705_INT_TIMER1)) != 0)
	{
		m_pending_interrupts &= ~(1 << HD63705_INT_TIMER1);
		rm16(0x1ff6, m_pc);
	}
	else if ((m_pending_interrupts & (1 << HD63705_INT_TIMER2)) != 0)
	{
		m_pending_interrupts &= ~(1 << HD63705_INT_TIMER2);
		rm16(0x1ff4, m_pc);
	}
	else if ((m_pending_interrupts & (1 << HD63705_INT_TIMER3)) != 0)
	{
		m_pending_interrupts &= ~(1<<HD63705_INT_TIMER3);
		rm16(0x1ff2, m_pc);
	}
	else if ((m_pending_interrupts & (1 << HD63705_INT_PCI)) != 0)
	{
		m_pending_interrupts &= ~(1 << HD63705_INT_PCI);
		rm16(0x1ff0, m_pc);
	}
	else if ((m_pending_interrupts & (1 << HD63705_INT_SCI)) != 0)
	{
		m_pending_interrupts &= ~(1 << HD63705_INT_SCI);
		rm16(0x1fee, m_pc);
	}
}


DEFINE_DEVICE_TYPE(M6805,     m6805_device,     "m6805",     "M6805")
DEFINE_DEVICE_TYPE(M68HC05EG, m68hc05eg_device, "m68hc05eg", "MC68HC05EG")
DEFINE_DEVICE_TYPE(HD63705,   hd63705_device,   "hd63705",   "HD63705")
>>>>>>> upstream/master
