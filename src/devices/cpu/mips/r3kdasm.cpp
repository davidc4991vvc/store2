// license:BSD-3-Clause
// copyright-holders:Aaron Giles
/***************************************************************************

    r3kdasm.c
    Disassembler for the portable R3000 emulator.
    Written by Aaron Giles

***************************************************************************/

#include "emu.h"


static const char *const reg[32] =
{
	"0",    "r1",   "r2",   "r3",   "r4",   "r5",   "r6",   "r7",
	"r8",   "r9",   "r10",  "r11",  "r12",  "r13",  "r14",  "r15",
	"r16",  "r17",  "r18",  "r19",  "r20",  "r21",  "r22",  "r23",
	"r24",  "r25",  "r26",  "r27",  "r28",  "r29",  "r30",  "r31"
};


static const char *const cpreg[4][32] =
{
	{
		"Index","Random","EntryLo","cpr3",  "Context",  "cpr5", "cpr6", "cpr7",
		"BadVAddr", "cpr9", "EntryHi","cpr11","SR","Cause","EPC","PRId",
		"cpr16","cpr17","cpr18","cpr19","cpr20","cpr21","cpr22","cpr23",
		"cpr24","cpr25","cpr26","cpr27","cpr28","cpr29","cpr30","cpr31"
	},
	{
		"f0",   "f1",   "f2",   "f3",   "f4",   "f5",   "f6",   "f7",
		"f8",   "f9",   "f10",  "f11",  "f12",  "f13",  "f14",  "f15",
		"f16",  "f17",  "f18",  "f19",  "f20",  "f21",  "f22",  "f23",
		"f24",  "f25",  "f26",  "f27",  "f28",  "f29",  "f30",  "f31"
	},
	{
		"cpr0", "cpr1", "cpr2", "cpr3", "cpr4", "cpr5", "cpr6", "cpr7",
		"cpr8", "cpr9", "cpr10","cpr11","cpr12","cpr13","cpr14","cpr15",
		"cpr16","cpr17","cpr18","cpr19","cpr20","cpr21","cpr22","cpr23",
		"cpr24","cpr25","cpr26","cpr27","cpr28","cpr29","cpr30","cpr31"
	},
	{
		"cpr0", "cpr1", "cpr2", "cpr3", "cpr4", "cpr5", "cpr6", "cpr7",
		"cpr8", "cpr9", "cpr10","cpr11","cpr12","cpr13","cpr14","cpr15",
		"cpr16","cpr17","cpr18","cpr19","cpr20","cpr21","cpr22","cpr23",
		"cpr24","cpr25","cpr26","cpr27","cpr28","cpr29","cpr30","cpr31"
	}
};


static const char *const ccreg[4][32] =
{
	{
		"ccr0", "ccr1", "ccr2", "ccr3", "ccr4", "ccr5", "ccr6", "ccr7",
		"ccr8", "ccr9", "ccr10","ccr11","ccr12","ccr13","ccr14","ccr15",
		"ccr16","ccr17","ccr18","ccr19","ccr20","ccr21","ccr22","ccr23",
		"ccr24","ccr25","ccr26","ccr27","ccr28","ccr29","ccr30","ccr31"
	},
	{
		"ccr0", "ccr1", "ccr2", "ccr3", "ccr4", "ccr5", "ccr6", "ccr7",
		"ccr8", "ccr9", "ccr10","ccr11","ccr12","ccr13","ccr14","ccr15",
		"ccr16","ccr17","ccr18","ccr19","ccr20","ccr21","ccr22","ccr23",
		"ccr24","ccr25","ccr26","ccr27","ccr28","ccr29","ccr30","ccr31"
	},
	{
		"ccr0", "ccr1", "ccr2", "ccr3", "ccr4", "ccr5", "ccr6", "ccr7",
		"ccr8", "ccr9", "ccr10","ccr11","ccr12","ccr13","ccr14","ccr15",
		"ccr16","ccr17","ccr18","ccr19","ccr20","ccr21","ccr22","ccr23",
		"ccr24","ccr25","ccr26","ccr27","ccr28","ccr29","ccr30","ccr31"
	},
	{
		"ccr0", "ccr1", "ccr2", "ccr3", "ccr4", "ccr5", "ccr6", "ccr7",
		"ccr8", "ccr9", "ccr10","ccr11","ccr12","ccr13","ccr14","ccr15",
		"ccr16","ccr17","ccr18","ccr19","ccr20","ccr21","ccr22","ccr23",
		"ccr24","ccr25","ccr26","ccr27","ccr28","ccr29","ccr30","ccr31"
	}
};


/***************************************************************************
    CODE CODE
***************************************************************************/

<<<<<<< HEAD
INLINE char *signed_16bit(INT16 val)
=======
static inline char *signed_16bit(int16_t val)
>>>>>>> upstream/master
{
	static char temp[10];
	if (val < 0)
		sprintf(temp, "-$%x", -val);
	else
		sprintf(temp, "$%x", val);
	return temp;
}

<<<<<<< HEAD
static UINT32 dasm_cop(UINT32 pc, int cop, UINT32 op, char *buffer)
{
	int rt = (op >> 16) & 31;
	int rd = (op >> 11) & 31;
	UINT32 flags = 0;

	switch ((op >> 21) & 31)
	{
		case 0x00:  sprintf(buffer, "mfc%d   %s,%s", cop, reg[rt], cpreg[cop][rd]);                 break;
		case 0x02:  sprintf(buffer, "cfc%d   %s,%s", cop, reg[rt], ccreg[cop][rd]);                 break;
		case 0x04:  sprintf(buffer, "mtc%d   %s,%s", cop, reg[rt], cpreg[cop][rd]);                 break;
		case 0x06:  sprintf(buffer, "ctc%d   %s,%s", cop, reg[rt], ccreg[cop][rd]);                 break;
		case 0x08:  /* BC */
			switch (rt)
			{
				case 0x00:  sprintf(buffer, "bc%df   $%08x", cop, pc + 4 + ((INT16)op << 2));       break;
				case 0x01:  sprintf(buffer, "bc%dt   $%08x", cop, pc + 4 + ((INT16)op << 2));       break;
				case 0x02:  sprintf(buffer, "bc%dfl [invalid]", cop);                               break;
				case 0x03:  sprintf(buffer, "bc%dtl [invalid]", cop);                               break;
				default:    sprintf(buffer, "dc.l    $%08x [invalid]", op);                         break;
=======
static uint32_t dasm_cop(uint32_t pc, int cop, uint32_t op, std::ostream &stream)
{
	int rt = (op >> 16) & 31;
	int rd = (op >> 11) & 31;
	uint32_t flags = 0;

	switch ((op >> 21) & 31)
	{
		case 0x00:  util::stream_format(stream, "mfc%d   %s,%s", cop, reg[rt], cpreg[cop][rd]);                 break;
		case 0x02:  util::stream_format(stream, "cfc%d   %s,%s", cop, reg[rt], ccreg[cop][rd]);                 break;
		case 0x04:  util::stream_format(stream, "mtc%d   %s,%s", cop, reg[rt], cpreg[cop][rd]);                 break;
		case 0x06:  util::stream_format(stream, "ctc%d   %s,%s", cop, reg[rt], ccreg[cop][rd]);                 break;
		case 0x08:  /* BC */
			switch (rt)
			{
				case 0x00:  util::stream_format(stream, "bc%df   $%08x", cop, pc + 4 + ((int16_t)op << 2));       break;
				case 0x01:  util::stream_format(stream, "bc%dt   $%08x", cop, pc + 4 + ((int16_t)op << 2));       break;
				case 0x02:  util::stream_format(stream, "bc%dfl [invalid]", cop);                               break;
				case 0x03:  util::stream_format(stream, "bc%dtl [invalid]", cop);                               break;
				default:    util::stream_format(stream, "dc.l    $%08x [invalid]", op);                         break;
>>>>>>> upstream/master
			}
			break;
		case 0x10:
		case 0x11:
		case 0x12:
		case 0x13:
		case 0x14:
		case 0x15:
		case 0x16:
		case 0x17:
		case 0x18:
		case 0x19:
		case 0x1a:
		case 0x1b:
		case 0x1c:
		case 0x1d:
		case 0x1e:
		case 0x1f:  /* COP */
			if (cop == 0)
			{
				switch (op & 0x01ffffff)
				{
<<<<<<< HEAD
					case 0x01:  sprintf(buffer, "tlbr");                                            break;
					case 0x02:  sprintf(buffer, "tlbwi");                                           break;
					case 0x06:  sprintf(buffer, "tlbwr");                                           break;
					case 0x08:  sprintf(buffer, "tlbp");                                            break;
					case 0x10:  sprintf(buffer, "rfe");                                             break;
					case 0x18:  sprintf(buffer, "eret [invalid]");                                  break;
					default:    sprintf(buffer, "cop%d  $%07x", cop, op & 0x01ffffff);              break;
				}
			}
			else
				sprintf(buffer, "cop%d  $%07x", cop, op & 0x01ffffff);                              break;
		default:    sprintf(buffer, "dc.l  $%08x [invalid]", op);                                   break;
=======
					case 0x01:  util::stream_format(stream, "tlbr");                                            break;
					case 0x02:  util::stream_format(stream, "tlbwi");                                           break;
					case 0x06:  util::stream_format(stream, "tlbwr");                                           break;
					case 0x08:  util::stream_format(stream, "tlbp");                                            break;
					case 0x10:  util::stream_format(stream, "rfe");                                             break;
					case 0x18:  util::stream_format(stream, "eret [invalid]");                                  break;
					default:    util::stream_format(stream, "cop%d  $%07x", cop, op & 0x01ffffff);              break;
				}
			}
			else
				util::stream_format(stream, "cop%d  $%07x", cop, op & 0x01ffffff);
			break;
		default:    util::stream_format(stream, "dc.l  $%08x [invalid]", op);                                   break;
>>>>>>> upstream/master
	}

	return flags;
}

<<<<<<< HEAD
static UINT32 dasm_cop1(UINT32 pc, UINT32 op, char *buffer)
=======
static uint32_t dasm_cop1(uint32_t pc, uint32_t op, std::ostream &stream)
>>>>>>> upstream/master
{
	static const char *const format_table[] =
	{
		"?","?","?","?","?","?","?","?","?","?","?","?","?","?","?","?",
		"s","d","?","?","w","l","?","?","?","?","?","?","?","?","?","?"
	};
	const char *fmt = format_table[(op >> 21) & 31];
	int ft = (op >> 16) & 31;
	int fs = (op >> 11) & 31;
	int fd = (op >> 6) & 31;
	int rt = (op >> 16) & 31;
	int rd = (op >> 11) & 31;
<<<<<<< HEAD
	UINT32 flags = 0;

	switch ((op >> 21) & 31)
	{
		case 0x00:  sprintf(buffer, "mfc1   %s,%s", reg[rt], cpreg[1][rd]);                     break;
		case 0x01:  sprintf(buffer, "dmfc1  %s,%s", reg[rt], cpreg[1][rd]);                     break;
		case 0x02:  sprintf(buffer, "cfc1   %s,%s", reg[rt], ccreg[1][rd]);                     break;
		case 0x04:  sprintf(buffer, "mtc1   %s,%s", reg[rt], cpreg[1][rd]);                     break;
		case 0x05:  sprintf(buffer, "dmtc1  %s,%s", reg[rt], cpreg[1][rd]);                     break;
		case 0x06:  sprintf(buffer, "ctc1   %s,%s", reg[rt], ccreg[1][rd]);                     break;
		case 0x08:  /* BC */
			switch (rt & 3)
			{
				case 0x00:  sprintf(buffer, "bc1f   $%08x,%d", pc + 4 + ((INT16)op << 2), (op >> 18) & 7);      break;
				case 0x01:  sprintf(buffer, "bc1t   $%08x,%d", pc + 4 + ((INT16)op << 2), (op >> 18) & 7);      break;
				case 0x02:  sprintf(buffer, "bc1fl  $%08x,%d", pc + 4 + ((INT16)op << 2), (op >> 18) & 7); flags = DASMFLAG_STEP_OVER | DASMFLAG_STEP_OVER_EXTRA(1); break;
				case 0x03:  sprintf(buffer, "bc1tl  $%08x,%d", pc + 4 + ((INT16)op << 2), (op >> 18) & 7); flags = DASMFLAG_STEP_OVER | DASMFLAG_STEP_OVER_EXTRA(1); break;
=======
	uint32_t flags = 0;

	switch ((op >> 21) & 31)
	{
		case 0x00:  util::stream_format(stream, "mfc1   %s,%s", reg[rt], cpreg[1][rd]);                     break;
		case 0x01:  util::stream_format(stream, "dmfc1  %s,%s", reg[rt], cpreg[1][rd]);                     break;
		case 0x02:  util::stream_format(stream, "cfc1   %s,%s", reg[rt], ccreg[1][rd]);                     break;
		case 0x04:  util::stream_format(stream, "mtc1   %s,%s", reg[rt], cpreg[1][rd]);                     break;
		case 0x05:  util::stream_format(stream, "dmtc1  %s,%s", reg[rt], cpreg[1][rd]);                     break;
		case 0x06:  util::stream_format(stream, "ctc1   %s,%s", reg[rt], ccreg[1][rd]);                     break;
		case 0x08:  /* BC */
			switch (rt & 3)
			{
				case 0x00:  util::stream_format(stream, "bc1f   $%08x,%d", pc + 4 + ((int16_t)op << 2), (op >> 18) & 7);      break;
				case 0x01:  util::stream_format(stream, "bc1t   $%08x,%d", pc + 4 + ((int16_t)op << 2), (op >> 18) & 7);      break;
				case 0x02:  util::stream_format(stream, "bc1fl  $%08x,%d", pc + 4 + ((int16_t)op << 2), (op >> 18) & 7); flags = DASMFLAG_STEP_OVER | DASMFLAG_STEP_OVER_EXTRA(1); break;
				case 0x03:  util::stream_format(stream, "bc1tl  $%08x,%d", pc + 4 + ((int16_t)op << 2), (op >> 18) & 7); flags = DASMFLAG_STEP_OVER | DASMFLAG_STEP_OVER_EXTRA(1); break;
>>>>>>> upstream/master
			}
			break;
		default:    /* COP */
			switch (op & 0x3f)
			{
<<<<<<< HEAD
				case 0x00:  sprintf(buffer, "add.%s  %s,%s,%s", fmt, cpreg[1][fd], cpreg[1][fs], cpreg[1][ft]); break;
				case 0x01:  sprintf(buffer, "sub.%s  %s,%s,%s", fmt, cpreg[1][fd], cpreg[1][fs], cpreg[1][ft]); break;
				case 0x02:  sprintf(buffer, "mul.%s  %s,%s,%s", fmt, cpreg[1][fd], cpreg[1][fs], cpreg[1][ft]); break;
				case 0x03:  sprintf(buffer, "div.%s  %s,%s,%s", fmt, cpreg[1][fd], cpreg[1][fs], cpreg[1][ft]); break;
				case 0x04:  sprintf(buffer, "sqrt.%s %s,%s", fmt, cpreg[1][fd], cpreg[1][fs]);                  break;
				case 0x05:  sprintf(buffer, "abs.%s  %s,%s", fmt, cpreg[1][fd], cpreg[1][fs]);                  break;
				case 0x06:  sprintf(buffer, "mov.%s  %s,%s", fmt, cpreg[1][fd], cpreg[1][fs]);                  break;
				case 0x07:  sprintf(buffer, "neg.%s  %s,%s", fmt, cpreg[1][fd], cpreg[1][fs]);                  break;
				case 0x08:  sprintf(buffer, "round.l.%s %s,%s", fmt, cpreg[1][fd], cpreg[1][fs]);               break;
				case 0x09:  sprintf(buffer, "trunc.l.%s %s,%s", fmt, cpreg[1][fd], cpreg[1][fs]);               break;
				case 0x0a:  sprintf(buffer, "ceil.l.%s %s,%s", fmt, cpreg[1][fd], cpreg[1][fs]);                break;
				case 0x0b:  sprintf(buffer, "floor.l.%s %s,%s", fmt, cpreg[1][fd], cpreg[1][fs]);               break;
				case 0x0c:  sprintf(buffer, "round.w.%s %s,%s", fmt, cpreg[1][fd], cpreg[1][fs]);               break;
				case 0x0d:  sprintf(buffer, "trunc.w.%s %s,%s", fmt, cpreg[1][fd], cpreg[1][fs]);               break;
				case 0x0e:  sprintf(buffer, "ceil.w.%s %s,%s", fmt, cpreg[1][fd], cpreg[1][fs]);                break;
				case 0x0f:  sprintf(buffer, "floor.w.%s %s,%s", fmt, cpreg[1][fd], cpreg[1][fs]);               break;
				case 0x11:  sprintf(buffer, "mov%c.%s  %s,%s,%d", ((op >> 16) & 1) ? 't' : 'f', fmt, cpreg[1][fd], cpreg[1][fs], (op >> 18) & 7);   break;
				case 0x12:  sprintf(buffer, "movz.%s  %s,%s,%s", fmt, cpreg[1][fd], cpreg[1][fs], reg[rt]);     break;
				case 0x13:  sprintf(buffer, "movn.%s  %s,%s,%s", fmt, cpreg[1][fd], cpreg[1][fs], reg[rt]);     break;
				case 0x15:  sprintf(buffer, "recip.%s  %s,%s", fmt, cpreg[1][fd], cpreg[1][fs]);                break;
				case 0x16:  sprintf(buffer, "rsqrt.%s  %s,%s", fmt, cpreg[1][fd], cpreg[1][fs]);                break;
				case 0x20:  sprintf(buffer, "cvt.s.%s %s,%s", fmt, cpreg[1][fd], cpreg[1][fs]);                 break;
				case 0x21:  sprintf(buffer, "cvt.d.%s %s,%s", fmt, cpreg[1][fd], cpreg[1][fs]);                 break;
				case 0x24:  sprintf(buffer, "cvt.w.%s %s,%s", fmt, cpreg[1][fd], cpreg[1][fs]);                 break;
				case 0x25:  sprintf(buffer, "cvt.l.%s %s,%s", fmt, cpreg[1][fd], cpreg[1][fs]);                 break;
				case 0x30:  sprintf(buffer, "c.f.%s  %s,%s,%d", fmt, cpreg[1][fs], cpreg[1][ft], (op >> 8) & 7);    break;
				case 0x31:  sprintf(buffer, "c.un.%s %s,%s,%d", fmt, cpreg[1][fs], cpreg[1][ft], (op >> 8) & 7);    break;
				case 0x32:  sprintf(buffer, "c.eq.%s %s,%s,%d", fmt, cpreg[1][fs], cpreg[1][ft], (op >> 8) & 7);    break;
				case 0x33:  sprintf(buffer, "c.ueq.%s %s,%s,%d", fmt, cpreg[1][fs], cpreg[1][ft], (op >> 8) & 7);   break;
				case 0x34:  sprintf(buffer, "c.olt.%s %s,%s,%d", fmt, cpreg[1][fs], cpreg[1][ft], (op >> 8) & 7);   break;
				case 0x35:  sprintf(buffer, "c.ult.%s %s,%s,%d", fmt, cpreg[1][fs], cpreg[1][ft], (op >> 8) & 7);   break;
				case 0x36:  sprintf(buffer, "c.ole.%s %s,%s,%d", fmt, cpreg[1][fs], cpreg[1][ft], (op >> 8) & 7);   break;
				case 0x37:  sprintf(buffer, "c.ule.%s %s,%s,%d", fmt, cpreg[1][fs], cpreg[1][ft], (op >> 8) & 7);   break;
				case 0x38:  sprintf(buffer, "c.sf.%s %s,%s,%d", fmt, cpreg[1][fs], cpreg[1][ft], (op >> 8) & 7);    break;
				case 0x39:  sprintf(buffer, "c.ngle.%s %s,%s,%d", fmt, cpreg[1][fs], cpreg[1][ft], (op >> 8) & 7);break;
				case 0x3a:  sprintf(buffer, "c.seq.%s %s,%s,%d", fmt, cpreg[1][fs], cpreg[1][ft], (op >> 8) & 7);   break;
				case 0x3b:  sprintf(buffer, "c.ngl.%s %s,%s,%d", fmt, cpreg[1][fs], cpreg[1][ft], (op >> 8) & 7);   break;
				case 0x3c:  sprintf(buffer, "c.lt.%s %s,%s,%d", fmt, cpreg[1][fs], cpreg[1][ft], (op >> 8) & 7);    break;
				case 0x3d:  sprintf(buffer, "c.nge.%s %s,%s,%d", fmt, cpreg[1][fs], cpreg[1][ft], (op >> 8) & 7);   break;
				case 0x3e:  sprintf(buffer, "c.le.%s %s,%s,%d", fmt, cpreg[1][fs], cpreg[1][ft], (op >> 8) & 7);    break;
				case 0x3f:  sprintf(buffer, "c.ngt.%s %s,%s,%d", fmt, cpreg[1][fs], cpreg[1][ft], (op >> 8) & 7);   break;
				default:    sprintf(buffer, "cop1   $%07x", op & 0x01ffffff);                                   break;
=======
				case 0x00:  util::stream_format(stream, "add.%s  %s,%s,%s", fmt, cpreg[1][fd], cpreg[1][fs], cpreg[1][ft]); break;
				case 0x01:  util::stream_format(stream, "sub.%s  %s,%s,%s", fmt, cpreg[1][fd], cpreg[1][fs], cpreg[1][ft]); break;
				case 0x02:  util::stream_format(stream, "mul.%s  %s,%s,%s", fmt, cpreg[1][fd], cpreg[1][fs], cpreg[1][ft]); break;
				case 0x03:  util::stream_format(stream, "div.%s  %s,%s,%s", fmt, cpreg[1][fd], cpreg[1][fs], cpreg[1][ft]); break;
				case 0x04:  util::stream_format(stream, "sqrt.%s %s,%s", fmt, cpreg[1][fd], cpreg[1][fs]);                  break;
				case 0x05:  util::stream_format(stream, "abs.%s  %s,%s", fmt, cpreg[1][fd], cpreg[1][fs]);                  break;
				case 0x06:  util::stream_format(stream, "mov.%s  %s,%s", fmt, cpreg[1][fd], cpreg[1][fs]);                  break;
				case 0x07:  util::stream_format(stream, "neg.%s  %s,%s", fmt, cpreg[1][fd], cpreg[1][fs]);                  break;
				case 0x08:  util::stream_format(stream, "round.l.%s %s,%s", fmt, cpreg[1][fd], cpreg[1][fs]);               break;
				case 0x09:  util::stream_format(stream, "trunc.l.%s %s,%s", fmt, cpreg[1][fd], cpreg[1][fs]);               break;
				case 0x0a:  util::stream_format(stream, "ceil.l.%s %s,%s", fmt, cpreg[1][fd], cpreg[1][fs]);                break;
				case 0x0b:  util::stream_format(stream, "floor.l.%s %s,%s", fmt, cpreg[1][fd], cpreg[1][fs]);               break;
				case 0x0c:  util::stream_format(stream, "round.w.%s %s,%s", fmt, cpreg[1][fd], cpreg[1][fs]);               break;
				case 0x0d:  util::stream_format(stream, "trunc.w.%s %s,%s", fmt, cpreg[1][fd], cpreg[1][fs]);               break;
				case 0x0e:  util::stream_format(stream, "ceil.w.%s %s,%s", fmt, cpreg[1][fd], cpreg[1][fs]);                break;
				case 0x0f:  util::stream_format(stream, "floor.w.%s %s,%s", fmt, cpreg[1][fd], cpreg[1][fs]);               break;
				case 0x11:  util::stream_format(stream, "mov%c.%s  %s,%s,%d", ((op >> 16) & 1) ? 't' : 'f', fmt, cpreg[1][fd], cpreg[1][fs], (op >> 18) & 7);   break;
				case 0x12:  util::stream_format(stream, "movz.%s  %s,%s,%s", fmt, cpreg[1][fd], cpreg[1][fs], reg[rt]);     break;
				case 0x13:  util::stream_format(stream, "movn.%s  %s,%s,%s", fmt, cpreg[1][fd], cpreg[1][fs], reg[rt]);     break;
				case 0x15:  util::stream_format(stream, "recip.%s  %s,%s", fmt, cpreg[1][fd], cpreg[1][fs]);                break;
				case 0x16:  util::stream_format(stream, "rsqrt.%s  %s,%s", fmt, cpreg[1][fd], cpreg[1][fs]);                break;
				case 0x20:  util::stream_format(stream, "cvt.s.%s %s,%s", fmt, cpreg[1][fd], cpreg[1][fs]);                 break;
				case 0x21:  util::stream_format(stream, "cvt.d.%s %s,%s", fmt, cpreg[1][fd], cpreg[1][fs]);                 break;
				case 0x24:  util::stream_format(stream, "cvt.w.%s %s,%s", fmt, cpreg[1][fd], cpreg[1][fs]);                 break;
				case 0x25:  util::stream_format(stream, "cvt.l.%s %s,%s", fmt, cpreg[1][fd], cpreg[1][fs]);                 break;
				case 0x30:  util::stream_format(stream, "c.f.%s  %s,%s,%d", fmt, cpreg[1][fs], cpreg[1][ft], (op >> 8) & 7);    break;
				case 0x31:  util::stream_format(stream, "c.un.%s %s,%s,%d", fmt, cpreg[1][fs], cpreg[1][ft], (op >> 8) & 7);    break;
				case 0x32:  util::stream_format(stream, "c.eq.%s %s,%s,%d", fmt, cpreg[1][fs], cpreg[1][ft], (op >> 8) & 7);    break;
				case 0x33:  util::stream_format(stream, "c.ueq.%s %s,%s,%d", fmt, cpreg[1][fs], cpreg[1][ft], (op >> 8) & 7);   break;
				case 0x34:  util::stream_format(stream, "c.olt.%s %s,%s,%d", fmt, cpreg[1][fs], cpreg[1][ft], (op >> 8) & 7);   break;
				case 0x35:  util::stream_format(stream, "c.ult.%s %s,%s,%d", fmt, cpreg[1][fs], cpreg[1][ft], (op >> 8) & 7);   break;
				case 0x36:  util::stream_format(stream, "c.ole.%s %s,%s,%d", fmt, cpreg[1][fs], cpreg[1][ft], (op >> 8) & 7);   break;
				case 0x37:  util::stream_format(stream, "c.ule.%s %s,%s,%d", fmt, cpreg[1][fs], cpreg[1][ft], (op >> 8) & 7);   break;
				case 0x38:  util::stream_format(stream, "c.sf.%s %s,%s,%d", fmt, cpreg[1][fs], cpreg[1][ft], (op >> 8) & 7);    break;
				case 0x39:  util::stream_format(stream, "c.ngle.%s %s,%s,%d", fmt, cpreg[1][fs], cpreg[1][ft], (op >> 8) & 7);break;
				case 0x3a:  util::stream_format(stream, "c.seq.%s %s,%s,%d", fmt, cpreg[1][fs], cpreg[1][ft], (op >> 8) & 7);   break;
				case 0x3b:  util::stream_format(stream, "c.ngl.%s %s,%s,%d", fmt, cpreg[1][fs], cpreg[1][ft], (op >> 8) & 7);   break;
				case 0x3c:  util::stream_format(stream, "c.lt.%s %s,%s,%d", fmt, cpreg[1][fs], cpreg[1][ft], (op >> 8) & 7);    break;
				case 0x3d:  util::stream_format(stream, "c.nge.%s %s,%s,%d", fmt, cpreg[1][fs], cpreg[1][ft], (op >> 8) & 7);   break;
				case 0x3e:  util::stream_format(stream, "c.le.%s %s,%s,%d", fmt, cpreg[1][fs], cpreg[1][ft], (op >> 8) & 7);    break;
				case 0x3f:  util::stream_format(stream, "c.ngt.%s %s,%s,%d", fmt, cpreg[1][fs], cpreg[1][ft], (op >> 8) & 7);   break;
				default:    util::stream_format(stream, "cop1   $%07x", op & 0x01ffffff);                                   break;
>>>>>>> upstream/master
			}
			break;
	}
	return flags;
}

<<<<<<< HEAD
static unsigned dasmr3k(char *buffer, unsigned pc, UINT32 op)
=======
static unsigned dasmr3k(std::ostream &stream, unsigned pc, uint32_t op)
>>>>>>> upstream/master
{
	int rs = (op >> 21) & 31;
	int rt = (op >> 16) & 31;
	int rd = (op >> 11) & 31;
	int shift = (op >> 6) & 31;
<<<<<<< HEAD
	UINT32 flags = 0;
=======
	uint32_t flags = 0;
>>>>>>> upstream/master

	switch (op >> 26)
	{
		case 0x00:  /* SPECIAL */
			switch (op & 63)
			{
				case 0x00:  if (op == 0)
<<<<<<< HEAD
							sprintf(buffer, "nop");
							else
							sprintf(buffer, "sll    %s,%s,%d", reg[rd], reg[rt], shift);            break;
				case 0x02:  sprintf(buffer, "srl    %s,%s,%d", reg[rd], reg[rt], shift);            break;
				case 0x03:  sprintf(buffer, "sra    %s,%s,%d", reg[rd], reg[rt], shift);            break;
				case 0x04:  sprintf(buffer, "sllv   %s,%s,%s", reg[rd], reg[rt], reg[rs]);          break;
				case 0x06:  sprintf(buffer, "srlv   %s,%s,%s", reg[rd], reg[rt], reg[rs]);          break;
				case 0x07:  sprintf(buffer, "srav   %s,%s,%s", reg[rd], reg[rt], reg[rs]);          break;
				case 0x08:  sprintf(buffer, "jr     %s", reg[rs]); if (rs == 31) flags = DASMFLAG_STEP_OUT; break;
				case 0x09:  if (rd == 31)
							sprintf(buffer, "jalr   %s", reg[rs]);
							else
							sprintf(buffer, "jalr   %s,%s", reg[rs], reg[rd]); flags = DASMFLAG_STEP_OVER | DASMFLAG_STEP_OVER_EXTRA(1); break;
				case 0x0c:  sprintf(buffer, "syscall"); flags = DASMFLAG_STEP_OVER;                 break;
				case 0x0d:  sprintf(buffer, "break"); flags = DASMFLAG_STEP_OVER;                   break;
				case 0x0f:  sprintf(buffer, "sync [invalid]");                                      break;
				case 0x10:  sprintf(buffer, "mfhi   %s", reg[rd]);                                  break;
				case 0x11:  sprintf(buffer, "mthi   %s", reg[rs]);                                  break;
				case 0x12:  sprintf(buffer, "mflo   %s", reg[rd]);                                  break;
				case 0x13:  sprintf(buffer, "mtlo   %s", reg[rs]);                                  break;
				case 0x18:  sprintf(buffer, "mult   %s,%s", reg[rs], reg[rt]);                      break;
				case 0x19:  sprintf(buffer, "multu  %s,%s", reg[rs], reg[rt]);                      break;
				case 0x1a:  sprintf(buffer, "div    %s,%s", reg[rs], reg[rt]);                      break;
				case 0x1b:  sprintf(buffer, "divu   %s,%s", reg[rs], reg[rt]);                      break;
				case 0x20:  sprintf(buffer, "add    %s,%s,%s", reg[rd], reg[rs], reg[rt]);          break;
				case 0x21:  sprintf(buffer, "addu   %s,%s,%s", reg[rd], reg[rs], reg[rt]);          break;
				case 0x22:  sprintf(buffer, "sub    %s,%s,%s", reg[rd], reg[rs], reg[rt]);          break;
				case 0x23:  sprintf(buffer, "subu   %s,%s,%s", reg[rd], reg[rs], reg[rt]);          break;
				case 0x24:  sprintf(buffer, "and    %s,%s,%s", reg[rd], reg[rs], reg[rt]);          break;
				case 0x25:  sprintf(buffer, "or     %s,%s,%s", reg[rd], reg[rs], reg[rt]);          break;
				case 0x26:  sprintf(buffer, "xor    %s,%s,%s", reg[rd], reg[rs], reg[rt]);          break;
				case 0x27:  sprintf(buffer, "nor    %s,%s,%s", reg[rd], reg[rs], reg[rt]);          break;
				case 0x2a:  sprintf(buffer, "slt    %s,%s,%s", reg[rd], reg[rs], reg[rt]);          break;
				case 0x2b:  sprintf(buffer, "sltu   %s,%s,%s", reg[rd], reg[rs], reg[rt]);          break;
				case 0x30:  sprintf(buffer, "teq [invalid]");                                       break;
				case 0x31:  sprintf(buffer, "tgeu [invalid]");                                      break;
				case 0x32:  sprintf(buffer, "tlt [invalid]");                                       break;
				case 0x33:  sprintf(buffer, "tltu [invalid]");                                      break;
				case 0x34:  sprintf(buffer, "tge [invalid]");                                       break;
				case 0x36:  sprintf(buffer, "tne [invalid]");                                       break;
				default:    sprintf(buffer, "dc.l   $%08x [invalid]", op);                          break;
=======
							util::stream_format(stream, "nop");
							else
							util::stream_format(stream, "sll    %s,%s,%d", reg[rd], reg[rt], shift);
					break;
				case 0x02:  util::stream_format(stream, "srl    %s,%s,%d", reg[rd], reg[rt], shift);            break;
				case 0x03:  util::stream_format(stream, "sra    %s,%s,%d", reg[rd], reg[rt], shift);            break;
				case 0x04:  util::stream_format(stream, "sllv   %s,%s,%s", reg[rd], reg[rt], reg[rs]);          break;
				case 0x06:  util::stream_format(stream, "srlv   %s,%s,%s", reg[rd], reg[rt], reg[rs]);          break;
				case 0x07:  util::stream_format(stream, "srav   %s,%s,%s", reg[rd], reg[rt], reg[rs]);          break;
				case 0x08:  util::stream_format(stream, "jr     %s", reg[rs]); if (rs == 31) flags = DASMFLAG_STEP_OUT; break;
				case 0x09:  if (rd == 31)
							util::stream_format(stream, "jalr   %s", reg[rs]);
							else
							util::stream_format(stream, "jalr   %s,%s", reg[rs], reg[rd]);
					flags = DASMFLAG_STEP_OVER | DASMFLAG_STEP_OVER_EXTRA(1);
					break;
				case 0x0c:  util::stream_format(stream, "syscall"); flags = DASMFLAG_STEP_OVER;                 break;
				case 0x0d:  util::stream_format(stream, "break"); flags = DASMFLAG_STEP_OVER;                   break;
				case 0x0f:  util::stream_format(stream, "sync [invalid]");                                      break;
				case 0x10:  util::stream_format(stream, "mfhi   %s", reg[rd]);                                  break;
				case 0x11:  util::stream_format(stream, "mthi   %s", reg[rs]);                                  break;
				case 0x12:  util::stream_format(stream, "mflo   %s", reg[rd]);                                  break;
				case 0x13:  util::stream_format(stream, "mtlo   %s", reg[rs]);                                  break;
				case 0x18:  util::stream_format(stream, "mult   %s,%s", reg[rs], reg[rt]);                      break;
				case 0x19:  util::stream_format(stream, "multu  %s,%s", reg[rs], reg[rt]);                      break;
				case 0x1a:  util::stream_format(stream, "div    %s,%s", reg[rs], reg[rt]);                      break;
				case 0x1b:  util::stream_format(stream, "divu   %s,%s", reg[rs], reg[rt]);                      break;
				case 0x20:  util::stream_format(stream, "add    %s,%s,%s", reg[rd], reg[rs], reg[rt]);          break;
				case 0x21:  util::stream_format(stream, "addu   %s,%s,%s", reg[rd], reg[rs], reg[rt]);          break;
				case 0x22:  util::stream_format(stream, "sub    %s,%s,%s", reg[rd], reg[rs], reg[rt]);          break;
				case 0x23:  util::stream_format(stream, "subu   %s,%s,%s", reg[rd], reg[rs], reg[rt]);          break;
				case 0x24:  util::stream_format(stream, "and    %s,%s,%s", reg[rd], reg[rs], reg[rt]);          break;
				case 0x25:  util::stream_format(stream, "or     %s,%s,%s", reg[rd], reg[rs], reg[rt]);          break;
				case 0x26:  util::stream_format(stream, "xor    %s,%s,%s", reg[rd], reg[rs], reg[rt]);          break;
				case 0x27:  util::stream_format(stream, "nor    %s,%s,%s", reg[rd], reg[rs], reg[rt]);          break;
				case 0x2a:  util::stream_format(stream, "slt    %s,%s,%s", reg[rd], reg[rs], reg[rt]);          break;
				case 0x2b:  util::stream_format(stream, "sltu   %s,%s,%s", reg[rd], reg[rs], reg[rt]);          break;
				case 0x30:  util::stream_format(stream, "teq [invalid]");                                       break;
				case 0x31:  util::stream_format(stream, "tgeu [invalid]");                                      break;
				case 0x32:  util::stream_format(stream, "tlt [invalid]");                                       break;
				case 0x33:  util::stream_format(stream, "tltu [invalid]");                                      break;
				case 0x34:  util::stream_format(stream, "tge [invalid]");                                       break;
				case 0x36:  util::stream_format(stream, "tne [invalid]");                                       break;
				default:    util::stream_format(stream, "dc.l   $%08x [invalid]", op);                          break;
>>>>>>> upstream/master
			}
			break;

		case 0x01:  /* REGIMM */
			switch ((op >> 16) & 31)
			{
<<<<<<< HEAD
				case 0x00:  sprintf(buffer, "bltz   %s,$%08x", reg[rs], pc + 4 + ((INT16)op << 2)); break;
				case 0x01:  sprintf(buffer, "bgez   %s,$%08x", reg[rs], pc + 4 + ((INT16)op << 2)); break;
				case 0x02:  sprintf(buffer, "bltzl [invalid]");                                     break;
				case 0x03:  sprintf(buffer, "bgezl [invalid]");                                     break;
				case 0x08:  sprintf(buffer, "tgei [invalid]");                                      break;
				case 0x09:  sprintf(buffer, "tgeiu [invalid]");                                     break;
				case 0x0a:  sprintf(buffer, "tlti [invalid]");                                      break;
				case 0x0b:  sprintf(buffer, "tltiu [invalid]");                                     break;
				case 0x0c:  sprintf(buffer, "teqi [invalid]");                                      break;
				case 0x0e:  sprintf(buffer, "tnei [invalid]");                                      break;
				case 0x10:  sprintf(buffer, "bltzal %s,$%08x", reg[rs], pc + 4 + ((INT16)op << 2)); flags = DASMFLAG_STEP_OVER | DASMFLAG_STEP_OVER_EXTRA(1); break;
				case 0x11:  sprintf(buffer, "bgezal %s,$%08x", reg[rs], pc + 4 + ((INT16)op << 2)); flags = DASMFLAG_STEP_OVER | DASMFLAG_STEP_OVER_EXTRA(1); break;
				case 0x12:  sprintf(buffer, "bltzall [invalid]");                                   break;
				case 0x13:  sprintf(buffer, "bgezall [invalid]");                                   break;
				default:    sprintf(buffer, "dc.l   $%08x [invalid]", op);                          break;
			}
			break;

		case 0x02:  sprintf(buffer, "j      $%08x", (pc & 0xf0000000) | ((op & 0x0fffffff) << 2));  break;
		case 0x03:  sprintf(buffer, "jal    $%08x", (pc & 0xf0000000) | ((op & 0x0fffffff) << 2)); flags = DASMFLAG_STEP_OVER | DASMFLAG_STEP_OVER_EXTRA(1); break;
		case 0x04:  if (rs == 0 && rt == 0)
					sprintf(buffer, "b      $%08x", pc + 4 + ((INT16)op << 2));
					else
					sprintf(buffer, "beq    %s,%s,$%08x", reg[rs], reg[rt], pc + 4 + ((INT16)op << 2));break;
		case 0x05:  sprintf(buffer, "bne    %s,%s,$%08x", reg[rs], reg[rt], pc + 4 + ((INT16)op << 2));break;
		case 0x06:  sprintf(buffer, "blez   %s,$%08x", reg[rs], pc + 4 + ((INT16)op << 2));         break;
		case 0x07:  sprintf(buffer, "bgtz   %s,$%08x", reg[rs], pc + 4 + ((INT16)op << 2));         break;
		case 0x08:  sprintf(buffer, "addi   %s,%s,%s", reg[rt], reg[rs], signed_16bit(op));         break;
		case 0x09:  sprintf(buffer, "addiu  %s,%s,%s", reg[rt], reg[rs], signed_16bit(op));         break;
		case 0x0a:  sprintf(buffer, "slti   %s,%s,%s", reg[rt], reg[rs], signed_16bit(op));         break;
		case 0x0b:  sprintf(buffer, "sltiu  %s,%s,%s", reg[rt], reg[rs], signed_16bit(op));         break;
		case 0x0c:  sprintf(buffer, "andi   %s,%s,$%04x", reg[rt], reg[rs], (UINT16)op);            break;
		case 0x0d:  sprintf(buffer, "ori    %s,%s,$%04x", reg[rt], reg[rs], (UINT16)op);            break;
		case 0x0e:  sprintf(buffer, "xori   %s,%s,$%04x", reg[rt], reg[rs], (UINT16)op);            break;
		case 0x0f:  sprintf(buffer, "lui    %s,$%04x", reg[rt], (UINT16)op);                        break;
		case 0x10:  flags = dasm_cop(pc, 0, op, buffer);                                            break;
		case 0x11:  flags = dasm_cop1(pc, op, buffer);                                          break;
		case 0x12:  flags = dasm_cop(pc, 2, op, buffer);                                            break;
		case 0x13:  flags = dasm_cop(pc, 3, op, buffer);                                            break;
		case 0x14:  sprintf(buffer, "beql [invalid]");                                              break;
		case 0x15:  sprintf(buffer, "bnel [invalid]");                                              break;
		case 0x16:  sprintf(buffer, "blezl [invalid]");                                             break;
		case 0x17:  sprintf(buffer, "bgtzl [invalid]");                                             break;
		case 0x20:  sprintf(buffer, "lb     %s,%s(%s)", reg[rt], signed_16bit(op), reg[rs]);        break;
		case 0x21:  sprintf(buffer, "lh     %s,%s(%s)", reg[rt], signed_16bit(op), reg[rs]);        break;
		case 0x22:  sprintf(buffer, "lwl    %s,%s(%s)", reg[rt], signed_16bit(op), reg[rs]);        break;
		case 0x23:  sprintf(buffer, "lw     %s,%s(%s)", reg[rt], signed_16bit(op), reg[rs]);        break;
		case 0x24:  sprintf(buffer, "lbu    %s,%s(%s)", reg[rt], signed_16bit(op), reg[rs]);        break;
		case 0x25:  sprintf(buffer, "lhu    %s,%s(%s)", reg[rt], signed_16bit(op), reg[rs]);        break;
		case 0x26:  sprintf(buffer, "lwr    %s,%s(%s)", reg[rt], signed_16bit(op), reg[rs]);        break;
		case 0x28:  sprintf(buffer, "sb     %s,%s(%s)", reg[rt], signed_16bit(op), reg[rs]);        break;
		case 0x29:  sprintf(buffer, "sh     %s,%s(%s)", reg[rt], signed_16bit(op), reg[rs]);        break;
		case 0x2a:  sprintf(buffer, "swl    %s,%s(%s)", reg[rt], signed_16bit(op), reg[rs]);        break;
		case 0x2b:  sprintf(buffer, "sw     %s,%s(%s)", reg[rt], signed_16bit(op), reg[rs]);        break;
		case 0x2e:  sprintf(buffer, "swr    %s,%s(%s)", reg[rt], signed_16bit(op), reg[rs]);        break;
		case 0x2f:  sprintf(buffer, "cache [invalid]");                                             break;
		case 0x30:  sprintf(buffer, "ll [invalid]");                                                break;
		case 0x31:  sprintf(buffer, "lwc1   %s,%s(%s)", cpreg[1][rt], signed_16bit(op), reg[rs]);   break;
		case 0x32:  sprintf(buffer, "lwc2   %s,%s(%s)", cpreg[2][rt], signed_16bit(op), reg[rs]);   break;
		case 0x33:  sprintf(buffer, "lwc3   %s,%s(%s)", cpreg[3][rt], signed_16bit(op), reg[rs]);   break;
		case 0x34:  sprintf(buffer, "ldc0 [invalid]");                                              break;
		case 0x35:  sprintf(buffer, "ldc1 [invalid]");                                              break;
		case 0x36:  sprintf(buffer, "ldc2 [invalid]");                                              break;
		case 0x37:  sprintf(buffer, "ldc3 [invalid]");                                              break;
		case 0x38:  sprintf(buffer, "sc [invalid]");                                                break;
		case 0x39:  sprintf(buffer, "swc1   %s,%s(%s)", cpreg[1][rt], signed_16bit(op), reg[rs]);   break;
		case 0x3a:  sprintf(buffer, "swc2   %s,%s(%s)", cpreg[2][rt], signed_16bit(op), reg[rs]);   break;
		case 0x3b:  sprintf(buffer, "swc3   %s,%s(%s)", cpreg[3][rt], signed_16bit(op), reg[rs]);   break;
		case 0x3c:  sprintf(buffer, "sdc0 [invalid]");                                              break;
		case 0x3d:  sprintf(buffer, "sdc1 [invalid]");                                              break;
		case 0x3e:  sprintf(buffer, "sdc2 [invalid]");                                              break;
		case 0x3f:  sprintf(buffer, "sdc3 [invalid]");                                              break;
		default:    sprintf(buffer, "dc.l   $%08x [invalid]", op);                                  break;
=======
				case 0x00:  util::stream_format(stream, "bltz   %s,$%08x", reg[rs], pc + 4 + ((int16_t)op << 2)); break;
				case 0x01:  util::stream_format(stream, "bgez   %s,$%08x", reg[rs], pc + 4 + ((int16_t)op << 2)); break;
				case 0x02:  util::stream_format(stream, "bltzl [invalid]");                                     break;
				case 0x03:  util::stream_format(stream, "bgezl [invalid]");                                     break;
				case 0x08:  util::stream_format(stream, "tgei [invalid]");                                      break;
				case 0x09:  util::stream_format(stream, "tgeiu [invalid]");                                     break;
				case 0x0a:  util::stream_format(stream, "tlti [invalid]");                                      break;
				case 0x0b:  util::stream_format(stream, "tltiu [invalid]");                                     break;
				case 0x0c:  util::stream_format(stream, "teqi [invalid]");                                      break;
				case 0x0e:  util::stream_format(stream, "tnei [invalid]");                                      break;
				case 0x10:  util::stream_format(stream, "bltzal %s,$%08x", reg[rs], pc + 4 + ((int16_t)op << 2)); flags = DASMFLAG_STEP_OVER | DASMFLAG_STEP_OVER_EXTRA(1); break;
				case 0x11:  util::stream_format(stream, "bgezal %s,$%08x", reg[rs], pc + 4 + ((int16_t)op << 2)); flags = DASMFLAG_STEP_OVER | DASMFLAG_STEP_OVER_EXTRA(1); break;
				case 0x12:  util::stream_format(stream, "bltzall [invalid]");                                   break;
				case 0x13:  util::stream_format(stream, "bgezall [invalid]");                                   break;
				default:    util::stream_format(stream, "dc.l   $%08x [invalid]", op);                          break;
			}
			break;

		case 0x02:  util::stream_format(stream, "j      $%08x", (pc & 0xf0000000) | ((op & 0x0fffffff) << 2));  break;
		case 0x03:  util::stream_format(stream, "jal    $%08x", (pc & 0xf0000000) | ((op & 0x0fffffff) << 2)); flags = DASMFLAG_STEP_OVER | DASMFLAG_STEP_OVER_EXTRA(1); break;
		case 0x04:  if (rs == 0 && rt == 0)
					util::stream_format(stream, "b      $%08x", pc + 4 + ((int16_t)op << 2));
					else
					util::stream_format(stream, "beq    %s,%s,$%08x", reg[rs], reg[rt], pc + 4 + ((int16_t)op << 2));
			break;
		case 0x05:  util::stream_format(stream, "bne    %s,%s,$%08x", reg[rs], reg[rt], pc + 4 + ((int16_t)op << 2));break;
		case 0x06:  util::stream_format(stream, "blez   %s,$%08x", reg[rs], pc + 4 + ((int16_t)op << 2));         break;
		case 0x07:  util::stream_format(stream, "bgtz   %s,$%08x", reg[rs], pc + 4 + ((int16_t)op << 2));         break;
		case 0x08:  util::stream_format(stream, "addi   %s,%s,%s", reg[rt], reg[rs], signed_16bit(op));         break;
		case 0x09:  util::stream_format(stream, "addiu  %s,%s,%s", reg[rt], reg[rs], signed_16bit(op));         break;
		case 0x0a:  util::stream_format(stream, "slti   %s,%s,%s", reg[rt], reg[rs], signed_16bit(op));         break;
		case 0x0b:  util::stream_format(stream, "sltiu  %s,%s,%s", reg[rt], reg[rs], signed_16bit(op));         break;
		case 0x0c:  util::stream_format(stream, "andi   %s,%s,$%04x", reg[rt], reg[rs], (uint16_t)op);            break;
		case 0x0d:  util::stream_format(stream, "ori    %s,%s,$%04x", reg[rt], reg[rs], (uint16_t)op);            break;
		case 0x0e:  util::stream_format(stream, "xori   %s,%s,$%04x", reg[rt], reg[rs], (uint16_t)op);            break;
		case 0x0f:  util::stream_format(stream, "lui    %s,$%04x", reg[rt], (uint16_t)op);                        break;
		case 0x10:  flags = dasm_cop(pc, 0, op, stream);                                            break;
		case 0x11:  flags = dasm_cop1(pc, op, stream);                                          break;
		case 0x12:  flags = dasm_cop(pc, 2, op, stream);                                            break;
		case 0x13:  flags = dasm_cop(pc, 3, op, stream);                                            break;
		case 0x14:  util::stream_format(stream, "beql [invalid]");                                              break;
		case 0x15:  util::stream_format(stream, "bnel [invalid]");                                              break;
		case 0x16:  util::stream_format(stream, "blezl [invalid]");                                             break;
		case 0x17:  util::stream_format(stream, "bgtzl [invalid]");                                             break;
		case 0x20:  util::stream_format(stream, "lb     %s,%s(%s)", reg[rt], signed_16bit(op), reg[rs]);        break;
		case 0x21:  util::stream_format(stream, "lh     %s,%s(%s)", reg[rt], signed_16bit(op), reg[rs]);        break;
		case 0x22:  util::stream_format(stream, "lwl    %s,%s(%s)", reg[rt], signed_16bit(op), reg[rs]);        break;
		case 0x23:  util::stream_format(stream, "lw     %s,%s(%s)", reg[rt], signed_16bit(op), reg[rs]);        break;
		case 0x24:  util::stream_format(stream, "lbu    %s,%s(%s)", reg[rt], signed_16bit(op), reg[rs]);        break;
		case 0x25:  util::stream_format(stream, "lhu    %s,%s(%s)", reg[rt], signed_16bit(op), reg[rs]);        break;
		case 0x26:  util::stream_format(stream, "lwr    %s,%s(%s)", reg[rt], signed_16bit(op), reg[rs]);        break;
		case 0x28:  util::stream_format(stream, "sb     %s,%s(%s)", reg[rt], signed_16bit(op), reg[rs]);        break;
		case 0x29:  util::stream_format(stream, "sh     %s,%s(%s)", reg[rt], signed_16bit(op), reg[rs]);        break;
		case 0x2a:  util::stream_format(stream, "swl    %s,%s(%s)", reg[rt], signed_16bit(op), reg[rs]);        break;
		case 0x2b:  util::stream_format(stream, "sw     %s,%s(%s)", reg[rt], signed_16bit(op), reg[rs]);        break;
		case 0x2e:  util::stream_format(stream, "swr    %s,%s(%s)", reg[rt], signed_16bit(op), reg[rs]);        break;
		case 0x2f:  util::stream_format(stream, "cache [invalid]");                                             break;
		case 0x30:  util::stream_format(stream, "ll [invalid]");                                                break;
		case 0x31:  util::stream_format(stream, "lwc1   %s,%s(%s)", cpreg[1][rt], signed_16bit(op), reg[rs]);   break;
		case 0x32:  util::stream_format(stream, "lwc2   %s,%s(%s)", cpreg[2][rt], signed_16bit(op), reg[rs]);   break;
		case 0x33:  util::stream_format(stream, "lwc3   %s,%s(%s)", cpreg[3][rt], signed_16bit(op), reg[rs]);   break;
		case 0x34:  util::stream_format(stream, "ldc0 [invalid]");                                              break;
		case 0x35:  util::stream_format(stream, "ldc1 [invalid]");                                              break;
		case 0x36:  util::stream_format(stream, "ldc2 [invalid]");                                              break;
		case 0x37:  util::stream_format(stream, "ldc3 [invalid]");                                              break;
		case 0x38:  util::stream_format(stream, "sc [invalid]");                                                break;
		case 0x39:  util::stream_format(stream, "swc1   %s,%s(%s)", cpreg[1][rt], signed_16bit(op), reg[rs]);   break;
		case 0x3a:  util::stream_format(stream, "swc2   %s,%s(%s)", cpreg[2][rt], signed_16bit(op), reg[rs]);   break;
		case 0x3b:  util::stream_format(stream, "swc3   %s,%s(%s)", cpreg[3][rt], signed_16bit(op), reg[rs]);   break;
		case 0x3c:  util::stream_format(stream, "sdc0 [invalid]");                                              break;
		case 0x3d:  util::stream_format(stream, "sdc1 [invalid]");                                              break;
		case 0x3e:  util::stream_format(stream, "sdc2 [invalid]");                                              break;
		case 0x3f:  util::stream_format(stream, "sdc3 [invalid]");                                              break;
		default:    util::stream_format(stream, "dc.l   $%08x [invalid]", op);                                  break;
>>>>>>> upstream/master
	}
	return 4 | flags | DASMFLAG_SUPPORTED;
}


CPU_DISASSEMBLE( r3000be )
{
<<<<<<< HEAD
	UINT32 op = *(UINT32 *)oprom;
	op = BIG_ENDIANIZE_INT32(op);
	return dasmr3k(buffer, pc, op);
=======
	uint32_t op = *(uint32_t *)oprom;
	op = big_endianize_int32(op);
	return dasmr3k(stream, pc, op);
>>>>>>> upstream/master
}


CPU_DISASSEMBLE( r3000le )
{
<<<<<<< HEAD
	UINT32 op = *(UINT32 *)oprom;
	op = LITTLE_ENDIANIZE_INT32(op);
	return dasmr3k(buffer, pc, op);
=======
	uint32_t op = *(uint32_t *)oprom;
	op = little_endianize_int32(op);
	return dasmr3k(stream, pc, op);
>>>>>>> upstream/master
}
