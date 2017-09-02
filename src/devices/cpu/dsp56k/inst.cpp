// license:BSD-3-Clause
// copyright-holders:Andrew Gardner
<<<<<<< HEAD
=======
#include "emu.h"
>>>>>>> upstream/master
#include "inst.h"
#include "emu.h"

namespace DSP56K
{
// Factory
<<<<<<< HEAD
Instruction* Instruction::decodeInstruction(const Opcode* opc,
											const UINT16 word0,
											const UINT16 word1,
											bool shifted)
{
	UINT16 w0 = word0;
	UINT16 w1 = word1;
=======
std::unique_ptr<Instruction> Instruction::decodeInstruction(const Opcode* opc,
											const uint16_t word0,
											const uint16_t word1,
											bool shifted)
{
	uint16_t w0 = word0;
	uint16_t w1 = word1;
>>>>>>> upstream/master

	if (shifted)
	{
		w0 = w1;
		w1 = 0x0000;
	}

	/**************************************************************************/
	/* The very funky case of the XMemoryDataMoveWithShortDisplacement        */
	/**************************************************************************/
	if ((w0 & 0xff00) == 0x0500)
	{
		// Avoid "05-- 05--" recursion
<<<<<<< HEAD
		if (shifted) return NULL;

		auto_pointer<Instruction> op(decodeInstruction(opc, w0, w1, true));
=======
		if (shifted) return nullptr;

		std::unique_ptr<Instruction> op = decodeInstruction(opc, w0, w1, true);
>>>>>>> upstream/master
		if (op)
		{
			// This parallel move only works for certain trailing instructions.
			if (dynamic_cast<Add*>(op.get())  ||
				dynamic_cast<Asr*>(op.get())  ||
				dynamic_cast<Eor*>(op.get())  ||
				dynamic_cast<Mac*>(op.get())  ||
				dynamic_cast<Macr*>(op.get()) ||
				dynamic_cast<Mpy*>(op.get())  ||
				dynamic_cast<Neg*>(op.get())  ||
				dynamic_cast<Sub*>(op.get())  ||
				dynamic_cast<Tfr*>(op.get())  ||
				dynamic_cast<Tst*>(op.get())
				/* TODO: More? */)
			{
				op->m_sizeIncrement = 1;
				return op;
			}
		}
	}


	/**************************************************************************/
	/* Dual X Memory Data Read : 011m mKKK .rr. .... : A-142 */
	/* Quote: (MOVE, MAC(R), MPY(R), ADD, SUB, TFR) */
	/**************************************************************************/
	/* TFR : 011m mKKK 0rr1 F0DD : A-212 */
	if ((w0 & 0xe094) == 0x6010)
	{
<<<<<<< HEAD
		return global_alloc(Tfr_2(opc, w0, w1));
=======
		return std::make_unique<Tfr_2>(opc, w0, w1);
>>>>>>> upstream/master
	}
	/* MOVE : 011m mKKK 0rr1 0000 : A-128 */
	if ((w0 & 0xe097) == 0x6017)
	{
<<<<<<< HEAD
		return global_alloc(Move_2(opc, w0, w1));
=======
		return std::make_unique<Move_2>(opc, w0, w1);
>>>>>>> upstream/master
	}
	/* MAC : 011m mKKK 1xx0 F1QQ : A-122 */
	else if ((w0 & 0xe094) == 0x6084)
	{
<<<<<<< HEAD
		return global_alloc(Mac_3(opc, w0, w1));
=======
		return std::make_unique<Mac_3>(opc, w0, w1);
>>>>>>> upstream/master
	}
	/* MACR: 011m mKKK 1--1 F1QQ : A-124 */
	else if ((w0 & 0xe094) == 0x6094)
	{
<<<<<<< HEAD
		return global_alloc(Macr_2(opc, w0, w1));
=======
		return std::make_unique<Macr_2>(opc, w0, w1);
>>>>>>> upstream/master
	}
	/* MPY : 011m mKKK 1xx0 F0QQ : A-160 */
	else if ((w0 & 0xe094) == 0x6080)
	{
<<<<<<< HEAD
		return global_alloc(Mpy_2(opc, w0, w1));
=======
		return std::make_unique<Mpy_2>(opc, w0, w1);
>>>>>>> upstream/master
	}
	/* MPYR : 011m mKKK 1--1 F0QQ : A-162 */
	else if ((w0 & 0xe094) == 0x6090)
	{
<<<<<<< HEAD
		return global_alloc(Mpyr_2(opc, w0, w1));
=======
		return std::make_unique<Mpyr_2>(opc, w0, w1);
>>>>>>> upstream/master
	}
	/* ADD : 011m mKKK 0rru Fuuu : A-22 */
	/* SUB : 011m mKKK 0rru Fuuu : A-202 */
	else if ((w0 & 0xe080) == 0x6000)
	{
<<<<<<< HEAD
		return global_alloc(Add_2(opc, w0, w1));
=======
		return std::make_unique<Add_2>(opc, w0, w1);
>>>>>>> upstream/master
	}

	/****************************************************************************/
	/* X Memory Data Write and Register Data Move : 0001 011k RRDD .... : A-140 */
	/* Quote: (MPY or MAC) */
	/****************************************************************************/
	/* MPY : 0001 0110 RRDD FQQQ : A-160 */
	else if ((w0 & 0xff00) == 0x1600)
	{
<<<<<<< HEAD
		return global_alloc(Mpy_3(opc, w0, w1));
=======
		return std::make_unique<Mpy_3>(opc, w0, w1);
>>>>>>> upstream/master
	}
	/* MAC : 0001 0111 RRDD FQQQ : A-122 */
	else if ((w0 & 0xff00) == 0x1700)
	{
<<<<<<< HEAD
		return global_alloc(Mac_3(opc, w0, w1));
=======
		return std::make_unique<Mac_3>(opc, w0, w1);
>>>>>>> upstream/master
	}

	/****************************************************************/
	/* No Parallel Data Move :   0100 1010 .... .... : A-131 */
	/* Register to Register Data Move : 0100 IIII .... .... : A-133 */
	/* Address Register Update : 0011 0zRR .... .... : A-135 */
	/* X Memory Data Move :   1mRR HHHW .... .... : A-137 */
	/* X Memory Data Move :   0101 HHHW .... .... : A-137 */
	/* Quote: (32 General parallel move instructions) */
	/****************************************************************/
	else if (((w0 & 0xff00) == 0x4a00) ||
				((w0 & 0xf000) == 0x4000) ||
				((w0 & 0xf800) == 0x3000) ||
				((w0 & 0x8000) == 0x8000) ||
				((w0 & 0xf000) == 0x5000))
	{
		/* Note: There is much overlap down here, so certain ops must come before others */

		/* CLR : .... .... 0000 F001 : A-60 */
		if ((w0 & 0x00f7) == 0x0001)
		{
<<<<<<< HEAD
			return global_alloc(Clr(opc, w0, w1));
=======
			return std::make_unique<Clr>(opc, w0, w1);
>>>>>>> upstream/master
		}
		/* ADD : .... .... 0000 FJJJ : A-22 */
		else if ((w0 & 0x00f0) == 0x0000)
		{
<<<<<<< HEAD
			return global_alloc(Add(opc, w0, w1));
=======
			return std::make_unique<Add>(opc, w0, w1);
>>>>>>> upstream/master
		}

		/* MOVE : .... .... 0001 0001 : A-128 */
		else if ((w0 & 0x00ff) == 0x0011 || (w0 & 0x00ff) == 0x0019)
		// NEW // else if ((w0 & 0x00ff) == 0x0011)
		{
<<<<<<< HEAD
			return global_alloc(Move(opc, w0, w1));
=======
			return std::make_unique<Move>(opc, w0, w1);
>>>>>>> upstream/master
		}
		/* TFR : .... .... 0001 FJJJ : A-212 */
		else if ((w0 & 0x00f0) == 0x0010)
		{
<<<<<<< HEAD
			return global_alloc(Tfr(opc, w0, w1));
=======
			return std::make_unique<Tfr>(opc, w0, w1);
>>>>>>> upstream/master
		}

		/* RND : .... .... 0010 F000 : A-188 */
		else if ((w0 & 0x00f7) == 0x0020)
		{
<<<<<<< HEAD
			return global_alloc(Rnd(opc, w0, w1));
=======
			return std::make_unique<Rnd>(opc, w0, w1);
>>>>>>> upstream/master
		}
		/* TST : .... .... 0010 F001 : A-218 */
		else if ((w0 & 0x00f7) == 0x0021)
		{
<<<<<<< HEAD
			return global_alloc(Tst(opc, w0, w1));
=======
			return std::make_unique<Tst>(opc, w0, w1);
>>>>>>> upstream/master
		}
		/* INC : .... .... 0010 F010 : A-104 */
		else if ((w0 & 0x00f7) == 0x0022)
		{
<<<<<<< HEAD
			return global_alloc(Inc(opc, w0, w1));
=======
			return std::make_unique<Inc>(opc, w0, w1);
>>>>>>> upstream/master
		}
		/* INC24 : .... .... 0010 F011 : A-106 */
		else if ((w0 & 0x00f7) == 0x0023)
		{
<<<<<<< HEAD
			return global_alloc(Inc24(opc, w0, w1));
=======
			return std::make_unique<Inc24>(opc, w0, w1);
>>>>>>> upstream/master
		}
		/* OR : .... .... 0010 F1JJ : A-176 */
		else if ((w0 & 0x00f4) == 0x0024)
		{
<<<<<<< HEAD
			return global_alloc(Or(opc, w0, w1));
=======
			return std::make_unique<Or>(opc, w0, w1);
>>>>>>> upstream/master
		}

		/* ASR : .... .... 0011 F000 : A-32 */
		else if ((w0 & 0x00f7) == 0x0030)
		{
<<<<<<< HEAD
			return global_alloc(Asr(opc, w0, w1));
=======
			return std::make_unique<Asr>(opc, w0, w1);
>>>>>>> upstream/master
		}
		/* ASL : .... .... 0011 F001 : A-28 */
		else if ((w0 & 0x00f7) == 0x0031)
		{
<<<<<<< HEAD
			return global_alloc(Asl(opc, w0, w1));
=======
			return std::make_unique<Asl>(opc, w0, w1);
>>>>>>> upstream/master
		}
		/* LSR : .... .... 0011 F010 : A-120 */
		else if ((w0 & 0x00f7) == 0x0032)
		{
<<<<<<< HEAD
			return global_alloc(Lsr(opc, w0, w1));
=======
			return std::make_unique<Lsr>(opc, w0, w1);
>>>>>>> upstream/master
		}
		/* LSL : .... .... 0011 F011 : A-118 */
		else if ((w0 & 0x00f7) == 0x0033)
		{
<<<<<<< HEAD
			return global_alloc(Lsl(opc, w0, w1));
=======
			return std::make_unique<Lsl>(opc, w0, w1);
>>>>>>> upstream/master
		}
		/* EOR : .... .... 0011 F1JJ : A-94 */
		else if ((w0 & 0x00f4) == 0x0034)
		{
<<<<<<< HEAD
			return global_alloc(Eor(opc, w0, w1));
=======
			return std::make_unique<Eor>(opc, w0, w1);
>>>>>>> upstream/master
		}

		/* SUBL : .... .... 0100 F001 : A-204 */
		else if ((w0 & 0x00f7) == 0x0041)
		{
<<<<<<< HEAD
			return global_alloc(Subl(opc, w0, w1));
=======
			return std::make_unique<Subl>(opc, w0, w1);
>>>>>>> upstream/master
		}
		/* SUB : .... .... 0100 FJJJ : A-202 */
		else if ((w0 & 0x00f0) == 0x0040)
		{
<<<<<<< HEAD
			return global_alloc(Sub(opc, w0, w1));
=======
			return std::make_unique<Sub>(opc, w0, w1);
>>>>>>> upstream/master
		}

		/* CLR24 : .... .... 0101 F001 : A-62 */
		else if ((w0 & 0x00f7) == 0x0051)
		{
<<<<<<< HEAD
			return global_alloc(Clr24(opc, w0, w1));
=======
			return std::make_unique<Clr24>(opc, w0, w1);
>>>>>>> upstream/master
		}
		/* SBC : .... .... 0101 F01J : A-198 */
		else if ((w0 & 0x00f6) == 0x0052)
		{
<<<<<<< HEAD
			return global_alloc(Sbc(opc, w0, w1));
=======
			return std::make_unique<Sbc>(opc, w0, w1);
>>>>>>> upstream/master
		}
		/* CMP : .... .... 0101 FJJJ : A-64 */
		else if ((w0 & 0x00f0) == 0x0050)
		{
<<<<<<< HEAD
			return global_alloc(Cmp(opc, w0, w1));
=======
			return std::make_unique<Cmp>(opc, w0, w1);
>>>>>>> upstream/master
		}

		/* NEG : .... .... 0110 F000 : A-166 */
		else if ((w0 & 0x00f7) == 0x0060)
		{
<<<<<<< HEAD
			return global_alloc(Neg(opc, w0, w1));
=======
			return std::make_unique<Neg>(opc, w0, w1);
>>>>>>> upstream/master
		}
		/* NOT : .... .... 0110 F001 : A-174 */
		else if ((w0 & 0x00f7) == 0x0061)
		{
<<<<<<< HEAD
			return global_alloc(Not(opc, w0, w1));
=======
			return std::make_unique<Not>(opc, w0, w1);
>>>>>>> upstream/master
		}
		/* DEC : .... .... 0110 F010 : A-72 */
		else if ((w0 & 0x00f7) == 0x0062)
		{
<<<<<<< HEAD
			return global_alloc(Dec(opc, w0, w1));
=======
			return std::make_unique<Dec>(opc, w0, w1);
>>>>>>> upstream/master
		}
		/* DEC24 : .... .... 0110 F011 : A-74 */
		else if ((w0 & 0x00f7) == 0x0063)
		{
<<<<<<< HEAD
			return global_alloc(Dec24(opc, w0, w1));
=======
			return std::make_unique<Dec24>(opc, w0, w1);
>>>>>>> upstream/master
		}
		/* AND : .... .... 0110 F1JJ : A-24 */
		else if ((w0 & 0x00f4) == 0x0064)
		{
<<<<<<< HEAD
			return global_alloc(And(opc, w0, w1));
=======
			return std::make_unique<And>(opc, w0, w1);
>>>>>>> upstream/master
		}

		/* ABS : .... .... 0111 F001 : A-18 */
		if ((w0 & 0x00f7) == 0x0071)
		{
<<<<<<< HEAD
			return global_alloc(Abs(opc, w0, w1));
=======
			return std::make_unique<Abs>(opc, w0, w1);
>>>>>>> upstream/master
		}
		/* ROR : .... .... 0111 F010 : A-192 */
		else if ((w0 & 0x00f7) == 0x0072)
		{
<<<<<<< HEAD
			return global_alloc(Ror(opc, w0, w1));
=======
			return std::make_unique<Ror>(opc, w0, w1);
>>>>>>> upstream/master
		}
		/* ROL : .... .... 0111 F011 : A-190 */
		else if ((w0 & 0x00f7) == 0x0073)
		{
<<<<<<< HEAD
			return global_alloc(Rol(opc, w0, w1));
=======
			return std::make_unique<Rol>(opc, w0, w1);
>>>>>>> upstream/master
		}
		/* CMPM : .... .... 0111 FJJJ : A-66 */
		else if ((w0 & 0x00f0) == 0x0070)
		{
<<<<<<< HEAD
			return global_alloc(Cmpm(opc, w0, w1));
=======
			return std::make_unique<Cmpm>(opc, w0, w1);
>>>>>>> upstream/master
		}

		/* MPY : .... .... 1k00 FQQQ : A-160 */
		else if ((w0 & 0x00b0) == 0x0080)
		{
<<<<<<< HEAD
			return global_alloc(Mpy(opc, w0, w1));
=======
			return std::make_unique<Mpy>(opc, w0, w1);
>>>>>>> upstream/master
		}
		/* MPYR : .... .... 1k01 FQQQ : A-162 */
		else if ((w0 & 0x00b0) == 0x0090)
		{
<<<<<<< HEAD
			return global_alloc(Mpyr(opc, w0, w1));
=======
			return std::make_unique<Mpyr>(opc, w0, w1);
>>>>>>> upstream/master
		}
		/* MAC : .... .... 1k10 FQQQ : A-122 */
		else if ((w0 & 0x00b0) == 0x00a0)
		{
<<<<<<< HEAD
			return global_alloc(Mac(opc, w0, w1));
=======
			return std::make_unique<Mac>(opc, w0, w1);
>>>>>>> upstream/master
		}
		/* MACR : .... .... 1k11 FQQQ : A-124 */
		else if ((w0 & 0x00b0) == 0x00b0)
		{
<<<<<<< HEAD
			return global_alloc(Macr(opc, w0, w1));
=======
			return std::make_unique<Macr>(opc, w0, w1);
>>>>>>> upstream/master
		}
	}

	/******************************/
	/* Remaining non-parallel ops */
	/******************************/
	/* ADC : 0001 0101 0000 F01J : A-20 */
	else if ((w0 & 0xfff6) == 0x1502)
	{
<<<<<<< HEAD
		return global_alloc(Adc(opc, w0, w1));
=======
		return std::make_unique<Adc>(opc, w0, w1);
>>>>>>> upstream/master
	}
	/* ANDI : 0001 1EE0 iiii iiii : A-26 */
	/* Note: MoveP sneaks in here if you don't check 0x0600 */
	else if (((w0 & 0xf900) == 0x1800) & ((w0 & 0x0600) != 0x0000))
	{
<<<<<<< HEAD
		return global_alloc(Andi(opc, w0, w1));
=======
		return std::make_unique<Andi>(opc, w0, w1);
>>>>>>> upstream/master
	}
	/* ASL4 : 0001 0101 0011 F001 : A-30 */
	else if ((w0 & 0xfff7) == 0x1531)
	{
<<<<<<< HEAD
		return global_alloc(Asl4(opc, w0, w1));
=======
		return std::make_unique<Asl4>(opc, w0, w1);
>>>>>>> upstream/master
	}
	/* ASR4 : 0001 0101 0011 F000 : A-34 */
	else if ((w0 & 0xfff7) == 0x1530)
	{
<<<<<<< HEAD
		return global_alloc(Asr4(opc, w0, w1));
=======
		return std::make_unique<Asr4>(opc, w0, w1);
>>>>>>> upstream/master
	}
	/* ASR16 : 0001 0101 0111 F000 : A-36 */
	else if ((w0 & 0xfff7) == 0x1570)
	{
<<<<<<< HEAD
		return global_alloc(Asr16(opc, w0, w1));
=======
		return std::make_unique<Asr16>(opc, w0, w1);
>>>>>>> upstream/master
	}
	/* BFCHG : 0001 0100 11Pp pppp BBB1 0010 iiii iiii : A-38 */
	else if (((w0 & 0xffc0) == 0x14c0) && ((w1 & 0x1f00) == 0x1200))
	{
<<<<<<< HEAD
		return global_alloc(BfInstruction(opc, w0, w1));
=======
		return std::make_unique<BfInstruction>(opc, w0, w1);
>>>>>>> upstream/master
	}
	/* BFCHG : 0001 0100 101- --RR BBB1 0010 iiii iiii : A-38 */
	else if (((w0 & 0xfff0) == 0x14b0) && ((w1 & 0x1f00) == 0x1200))
	// NEW // else if (((w0 & 0xffe0) == 0x14a0) && ((w1 & 0x1f00) == 0x1200))
	{
<<<<<<< HEAD
		return global_alloc(BfInstruction_2(opc, w0, w1));
=======
		return std::make_unique<BfInstruction_2>(opc, w0, w1);
>>>>>>> upstream/master
	}
	/* BFCHG : 0001 0100 100D DDDD BBB1 0010 iiii iiii : A-38 */
	else if (((w0 & 0xffe0) == 0x1480) && ((w1 & 0x1f00) == 0x1200))
	{
<<<<<<< HEAD
		return global_alloc(BfInstruction_3(opc, w0, w1));
=======
		return std::make_unique<BfInstruction_3>(opc, w0, w1);
>>>>>>> upstream/master
	}
	/* BFCLR : 0001 0100 11Pp pppp BBB0 0100 iiii iiii : A-40 */
	else if (((w0 & 0xffc0) == 0x14c0) && ((w1 & 0x1f00) == 0x0400))
	{
<<<<<<< HEAD
		return global_alloc(BfInstruction(opc, w0, w1));
=======
		return std::make_unique<BfInstruction>(opc, w0, w1);
>>>>>>> upstream/master
	}
	/* BFCLR : 0001 0100 101- --RR BBB0 0100 iiii iiii : A-40 */
	else if (((w0 & 0xfff0) == 0x14b0) && ((w1 & 0x1f00) == 0x0400))
	// NEW // else if (((w0 & 0xffe0) == 0x14a0) && ((w1 & 0x1f00) == 0x0400))
	{
<<<<<<< HEAD
		return global_alloc(BfInstruction_2(opc, w0, w1));
=======
		return std::make_unique<BfInstruction_2>(opc, w0, w1);
>>>>>>> upstream/master
	}
	/* BFCLR : 0001 0100 100D DDDD BBB0 0100 iiii iiii : A-40 */
	else if (((w0 & 0xffe0) == 0x1480) && ((w1 & 0x1f00) == 0x0400))
	{
<<<<<<< HEAD
		return global_alloc(BfInstruction_3(opc, w0, w1));
=======
		return std::make_unique<BfInstruction_3>(opc, w0, w1);
>>>>>>> upstream/master
	}
	/* BFSET : 0001 0100 11Pp pppp BBB1 1000 iiii iiii : A-42 */
	else if (((w0 & 0xffc0) == 0x14c0) && ((w1 & 0x1f00) == 0x1800))
	{
<<<<<<< HEAD
		return global_alloc(BfInstruction(opc, w0, w1));
=======
		return std::make_unique<BfInstruction>(opc, w0, w1);
>>>>>>> upstream/master
	}
	/* BFSET : 0001 0100 101- --RR BBB1 1000 iiii iiii : A-42 */
	else if (((w0 & 0xfff0) == 0x14b0) && ((w1 & 0x1f00) == 0x1800))
	// NEW // else if (((w0 & 0xffe0) == 0x14a0) && ((w1 & 0x1f00) == 0x1800))
	{
<<<<<<< HEAD
		return global_alloc(BfInstruction_2(opc, w0, w1));
=======
		return std::make_unique<BfInstruction_2>(opc, w0, w1);
>>>>>>> upstream/master
	}
	/* BFSET : 0001 0100 100D DDDD BBB1 1000 iiii iiii : A-42 */
	else if (((w0 & 0xffe0) == 0x1480) && ((w1 & 0x1f00) == 0x1800))
	{
<<<<<<< HEAD
		return global_alloc(BfInstruction_3(opc, w0, w1));
=======
		return std::make_unique<BfInstruction_3>(opc, w0, w1);
>>>>>>> upstream/master
	}
	/* BFTSTH : 0001 0100 01Pp pppp BBB1 0000 iiii iiii : A-44 */
	else if (((w0 & 0xffc0) == 0x1440) && ((w1 & 0x1f00) == 0x1000))
	{
<<<<<<< HEAD
		return global_alloc(BfInstruction(opc, w0, w1));
=======
		return std::make_unique<BfInstruction>(opc, w0, w1);
>>>>>>> upstream/master
	}
	/* BFTSTH : 0001 0100 001- --RR BBB1 0000 iiii iiii : A-44 */
	else if (((w0 & 0xfff0) == 0x1430) && ((w1 & 0x1f00) == 0x1000))
	// NEW // else if (((w0 & 0xffe0) == 0x1420) && ((w1 & 0x1f00) == 0x1000))
	{
<<<<<<< HEAD
		return global_alloc(BfInstruction_2(opc, w0, w1));
=======
		return std::make_unique<BfInstruction_2>(opc, w0, w1);
>>>>>>> upstream/master
	}
	/* BFTSTH : 0001 0100 000D DDDD BBB1 0000 iiii iiii : A-44 */
	else if (((w0 & 0xffe0) == 0x1400) && ((w1 & 0x1f00) == 0x1000))
	{
<<<<<<< HEAD
		return global_alloc(BfInstruction_3(opc, w0, w1));
=======
		return std::make_unique<BfInstruction_3>(opc, w0, w1);
>>>>>>> upstream/master
	}
	/* BFTSTL : 0001 0100 01Pp pppp BBB0 0000 iiii iiii : A-46 */
	else if (((w0 & 0xffc0) == 0x1440) && ((w1 & 0x1f00) == 0x0000))
	{
<<<<<<< HEAD
		return global_alloc(BfInstruction(opc, w0, w1));
=======
		return std::make_unique<BfInstruction>(opc, w0, w1);
>>>>>>> upstream/master
	}
	/* BFTSTL : 0001 0100 001- --RR BBB0 0000 iiii iiii : A-46 */
	else if (((w0 & 0xfff0) == 0x1430) && ((w1 & 0x1f00) == 0x0000))
	// NEW // else if (((w0 & 0xffe0) == 0x1420) && ((w1 & 0x1f00) == 0x0000))
	{
<<<<<<< HEAD
		return global_alloc(BfInstruction_2(opc, w0, w1));
=======
		return std::make_unique<BfInstruction_2>(opc, w0, w1);
>>>>>>> upstream/master
	}
	/* BFTSTL : 0001 0100 000D DDDD BBB0 0000 iiii iiii : A-46 */
	else if (((w0 & 0xffe0) == 0x1400) && ((w1 & 0x1f00) == 0x0000))
	{
<<<<<<< HEAD
		return global_alloc(BfInstruction_3(opc, w0, w1));
=======
		return std::make_unique<BfInstruction_3>(opc, w0, w1);
>>>>>>> upstream/master
	}
	/* Bcc : 0000 0111 --11 cccc xxxx xxxx xxxx xxxx : A-48 */
	else if (((w0 & 0xff30) == 0x0730) && ((w1 & 0x0000) == 0x0000))
	{
<<<<<<< HEAD
		return global_alloc(Bcc(opc, w0, w1));
=======
		return std::make_unique<Bcc>(opc, w0, w1);
>>>>>>> upstream/master
	}
	/* Bcc : 0010 11cc ccee eeee : A-48 */
	else if ((w0 & 0xfc00) == 0x2c00)
	{
<<<<<<< HEAD
		return global_alloc(Bcc_2(opc, w0, w1));
=======
		return std::make_unique<Bcc_2>(opc, w0, w1);
>>>>>>> upstream/master
	}
	/* Bcc : 0000 0111 RR10 cccc : A-48 */
	else if ((w0 & 0xff30) == 0x0720)
	{
<<<<<<< HEAD
		return global_alloc(Bcc_3(opc, w0, w1));
=======
		return std::make_unique<Bcc_3>(opc, w0, w1);
>>>>>>> upstream/master
	}
	/* BRA : 0000 0001 0011 11-- xxxx xxxx xxxx xxxx : A-50 */
	else if (((w0 & 0xfffc) == 0x013c) && ((w1 & 0x0000) == 0x0000))
	{
<<<<<<< HEAD
		return global_alloc(Bra(opc, w0, w1));
=======
		return std::make_unique<Bra>(opc, w0, w1);
>>>>>>> upstream/master
	}
	/* BRA : 0000 1011 aaaa aaaa : A-50 */
	else if ((w0 & 0xff00) == 0x0b00)
	{
<<<<<<< HEAD
		return global_alloc(Bra_2(opc, w0, w1));
=======
		return std::make_unique<Bra_2>(opc, w0, w1);
>>>>>>> upstream/master
	}
	/* BRA : 0000 0001 0010 11RR : A-50 */
	else if ((w0 & 0xfffc) == 0x012c)
	{
<<<<<<< HEAD
		return global_alloc(Bra_3(opc, w0, w1));
=======
		return std::make_unique<Bra_3>(opc, w0, w1);
>>>>>>> upstream/master
	}
	/* BRKc : 0000 0001 0001 cccc : A-52 */
	else if ((w0 & 0xfff0) == 0x0110)
	{
<<<<<<< HEAD
		return global_alloc(Brkcc(opc, w0, w1));
=======
		return std::make_unique<Brkcc>(opc, w0, w1);
>>>>>>> upstream/master
	}
	/* BScc : 0000 0111 --01 cccc xxxx xxxx xxxx xxxx : A-54 */
	else if (((w0 & 0xff30) == 0x0710) && ((w1 & 0x0000) == 0x0000))
	{
<<<<<<< HEAD
		return global_alloc(Bscc(opc, w0, w1));
=======
		return std::make_unique<Bscc>(opc, w0, w1);
>>>>>>> upstream/master
	}
	/* BScc : 0000 0111 RR00 cccc : A-54 */
	else if ((w0 & 0xff30) == 0x0700)
	{
<<<<<<< HEAD
		return global_alloc(Bscc_2(opc, w0, w1));
=======
		return std::make_unique<Bscc_2>(opc, w0, w1);
>>>>>>> upstream/master
	}
	/* BSR : 0000 0001 0011 10-- xxxx xxxx xxxx xxxx : A-56 */
	else if (((w0 & 0xfffc) == 0x0138) && ((w1 & 0x0000) == 0x0000))
	{
<<<<<<< HEAD
		return global_alloc(Bsr(opc, w0, w1));
=======
		return std::make_unique<Bsr>(opc, w0, w1);
>>>>>>> upstream/master
	}
	/* BSR : 0000 0001 0010 10RR : A-56 */
	else if ((w0 & 0xfffc) == 0x0128)
	{
<<<<<<< HEAD
		return global_alloc(Bsr_2(opc, w0, w1));
=======
		return std::make_unique<Bsr_2>(opc, w0, w1);
>>>>>>> upstream/master
	}
	/* CHKAAU : 0000 0000 0000 0100 : A-58 */
	else if ((w0 & 0xffff) == 0x0004)
	{
<<<<<<< HEAD
		return global_alloc(Chkaau(opc, w0, w1));
=======
		return std::make_unique<Chkaau>(opc, w0, w1);
>>>>>>> upstream/master
	}
	/* DEBUG : 0000 0000 0000 0001 : A-68 */
	else if ((w0 & 0xffff) == 0x0001)
	{
<<<<<<< HEAD
		return global_alloc(Debug(opc, w0, w1));
=======
		return std::make_unique<Debug>(opc, w0, w1);
>>>>>>> upstream/master
	}
	/* DEBUGcc : 0000 0000 0101 cccc : A-70 */
	else if ((w0 & 0xfff0) == 0x0050)
	{
<<<<<<< HEAD
		return global_alloc(Debugcc(opc, w0, w1));
=======
		return std::make_unique<Debugcc>(opc, w0, w1);
>>>>>>> upstream/master
	}
	/* DIV : 0001 0101 0--0 F1DD : A-76 */
	else if ((w0 & 0xfff4) == 0x1504)
	// NEW // else if ((w0 & 0xff94) == 0x1504)
	{
<<<<<<< HEAD
		return global_alloc(Div(opc, w0, w1));
=======
		return std::make_unique<Div>(opc, w0, w1);
>>>>>>> upstream/master
	}
	/* DMAC : 0001 0101 10s1 FsQQ : A-80 */
	else if ((w0 & 0xffd0) == 0x1590)
	{
<<<<<<< HEAD
		return global_alloc(Dmac(opc, w0, w1));
=======
		return std::make_unique<Dmac>(opc, w0, w1);
>>>>>>> upstream/master
	}
	/* DO : 0000 0000 110- --RR xxxx xxxx xxxx xxxx : A-82 */
	else if (((w0 & 0xffe0) == 0x00c0) && ((w1 & 0x0000) == 0x0000))       // Wait.  Huh?
	{
<<<<<<< HEAD
		return global_alloc(Do(opc, w0, w1));
=======
		return std::make_unique<Do>(opc, w0, w1);
>>>>>>> upstream/master
	}
	/* DO : 0000 1110 iiii iiii xxxx xxxx xxxx xxxx : A-82 */
	else if (((w0 & 0xff00) == 0x0e00) && ((w1 & 0x0000) == 0x0000))       // Wait.  Huh?
	{
<<<<<<< HEAD
		return global_alloc(Do_2(opc, w0, w1));
=======
		return std::make_unique<Do_2>(opc, w0, w1);
>>>>>>> upstream/master
	}
	/* DO : 0000 0100 000D DDDD xxxx xxxx xxxx xxxx : A-82 */
	else if (((w0 & 0xffe0) == 0x0400) && ((w1 & 0x0000) == 0x0000))       // Wait.  Huh?
	{
<<<<<<< HEAD
		return global_alloc(Do_3(opc, w0, w1));
=======
		return std::make_unique<Do_3>(opc, w0, w1);
>>>>>>> upstream/master
	}
	/* DO FOREVER : 0000 0000 0000 0010 xxxx xxxx xxxx xxxx : A-88 */
	else if (((w0 & 0xffff) == 0x0002) && ((w1 & 0x0000) == 0x0000))       // Wait.  Huh?
	{
<<<<<<< HEAD
		return global_alloc(DoForever(opc, w0, w1));
=======
		return std::make_unique<DoForever>(opc, w0, w1);
>>>>>>> upstream/master
	}
	/* ENDDO : 0000 0000 0000 1001 : A-92 */
	else if ((w0 & 0xffff) == 0x0009)
	{
<<<<<<< HEAD
		return global_alloc(Enddo(opc, w0, w1));
=======
		return std::make_unique<Enddo>(opc, w0, w1);
>>>>>>> upstream/master
	}
	/* EXT : 0001 0101 0101 F010 : A-96 */
	else if ((w0 & 0xfff7) == 0x1552)
	{
<<<<<<< HEAD
		return global_alloc(Ext(opc, w0, w1));
=======
		return std::make_unique<Ext>(opc, w0, w1);
>>>>>>> upstream/master
	}
	/* ILLEGAL : 0000 0000 0000 1111 : A-98 */
	else if ((w0 & 0xffff) == 0x000f)
	{
<<<<<<< HEAD
		return global_alloc(Illegal(opc, w0, w1));
=======
		return std::make_unique<Illegal>(opc, w0, w1);
>>>>>>> upstream/master
	}
	/* IMAC : 0001 0101 1010 FQQQ : A-100 */
	else if ((w0 & 0xfff0) == 0x15a0)
	{
<<<<<<< HEAD
		return global_alloc(Imac(opc, w0, w1));
=======
		return std::make_unique<Imac>(opc, w0, w1);
>>>>>>> upstream/master
	}
	/* IMPY : 0001 0101 1000 FQQQ : A-102 */
	else if ((w0 & 0xfff0) == 0x1580)
	{
<<<<<<< HEAD
		return global_alloc(Impy(opc, w0, w1));
=======
		return std::make_unique<Impy>(opc, w0, w1);
>>>>>>> upstream/master
	}
	/* Jcc : 0000 0110 --11 cccc xxxx xxxx xxxx xxxx : A-108 */
	else if (((w0 & 0xff30) == 0x0630) && ((w1 & 0x0000) == 0x0000))
	{
<<<<<<< HEAD
		return global_alloc(Jcc(opc, w0, w1));
=======
		return std::make_unique<Jcc>(opc, w0, w1);
>>>>>>> upstream/master
	}
	/* Jcc : 0000 0110 RR10 cccc : A-108 */
	else if ((w0 & 0xff30) == 0x0620 )
	{
<<<<<<< HEAD
		return global_alloc(Jcc_2(opc, w0, w1));
=======
		return std::make_unique<Jcc_2>(opc, w0, w1);
>>>>>>> upstream/master
	}
	/* JMP : 0000 0001 0011 01-- xxxx xxxx xxxx xxxx : A-110 */
	else if (((w0 & 0xfffc) == 0x0134) && ((w1 & 0x0000) == 0x0000))
	{
<<<<<<< HEAD
		return global_alloc(Jmp(opc, w0, w1));
=======
		return std::make_unique<Jmp>(opc, w0, w1);
>>>>>>> upstream/master
	}
	/* JMP : 0000 0001 0010 01RR : A-110 */
	else if ((w0 & 0xfffc) == 0x0124)
	{
		//JMP2->m_oco = opc;
		//JMP2->decode(w0, w1);
		//return JMP2;
<<<<<<< HEAD
		return global_alloc(Jmp_2(opc, w0, w1));
=======
		return std::make_unique<Jmp_2>(opc, w0, w1);
>>>>>>> upstream/master
	}
	/* JScc : 0000 0110 --01 cccc xxxx xxxx xxxx xxxx : A-112 */
	else if (((w0 & 0xff30) == 0x0610) && ((w1 & 0x0000) == 0x0000))
	{
<<<<<<< HEAD
		return global_alloc(Jscc(opc, w0, w1));
=======
		return std::make_unique<Jscc>(opc, w0, w1);
>>>>>>> upstream/master
	}
	/* JScc : 0000 0110 RR00 cccc : A-112 */
	else if ((w0 & 0xff30) == 0x0600)
	{
<<<<<<< HEAD
		return global_alloc(Jscc_2(opc, w0, w1));
=======
		return std::make_unique<Jscc_2>(opc, w0, w1);
>>>>>>> upstream/master
	}
	/* JSR : 0000 0001 0011 00-- xxxx xxxx xxxx xxxx : A-114 */
	else if (((w0 & 0xfffc) == 0x0130) && ((w1 & 0x0000) == 0x0000))
	{
<<<<<<< HEAD
		return global_alloc(Jsr(opc, w0, w1));
=======
		return std::make_unique<Jsr>(opc, w0, w1);
>>>>>>> upstream/master
	}
	/* JSR : 0000 1010 AAAA AAAA : A-114 */
	else if ((w0 & 0xff00) == 0x0a00)
	{
<<<<<<< HEAD
		return global_alloc(Jsr_2(opc, w0, w1));
=======
		return std::make_unique<Jsr_2>(opc, w0, w1);
>>>>>>> upstream/master
	}
	/* JSR : 0000 0001 0010 00RR : A-114 */
	else if ((w0 & 0xfffc) == 0x0120)
	{
<<<<<<< HEAD
		return global_alloc(Jsr_3(opc, w0, w1));
=======
		return std::make_unique<Jsr_3>(opc, w0, w1);
>>>>>>> upstream/master
	}
	/* LEA : 0000 0001 11TT MMRR : A-116 */
	else if ((w0 & 0xffc0) == 0x01c0)
	{
<<<<<<< HEAD
		return global_alloc(Lea(opc, w0, w1));
=======
		return std::make_unique<Lea>(opc, w0, w1);
>>>>>>> upstream/master
	}
	/* LEA : 0000 0001 10NN MMRR : A-116 */
	else if ((w0 & 0xffc0) == 0x0180)
	{
<<<<<<< HEAD
		return global_alloc(Lea_2(opc, w0, w1));
=======
		return std::make_unique<Lea_2>(opc, w0, w1);
>>>>>>> upstream/master
	}
	/* MAC(su,uu) : 0001 0101 1110 FsQQ : A-126 */
	else if ((w0 & 0xfff0) == 0x15e0)
	{
<<<<<<< HEAD
		return global_alloc(Macsuuu(opc, w0, w1));
=======
		return std::make_unique<Macsuuu>(opc, w0, w1);
>>>>>>> upstream/master
	}
	/* MOVE : 0000 0101 BBBB BBBB ---- HHHW 0001 0001 : A-128 */
// NEW //   else if (((w0 & 0xff00) == 0x0500) && ((w1 & 0x00ff) == 0x0011))
// NEW //   {
<<<<<<< HEAD
// NEW //       return global_alloc(Move_3(opc, w0, w1));
=======
// NEW //       return std::make_unique<Move_3>(opc, w0, w1);
>>>>>>> upstream/master
// NEW //   }
	/* MOVE(C) : 0011 1WDD DDD0 MMRR : A-144 */
	else if ((w0 & 0xf810) == 0x3800)
	{
<<<<<<< HEAD
		return global_alloc(Movec(opc, w0, w1));
=======
		return std::make_unique<Movec>(opc, w0, w1);
>>>>>>> upstream/master
	}
	/* MOVE(C) : 0011 1WDD DDD1 q0RR : A-144 */
	else if ((w0 & 0xf814) == 0x3810)
	{
<<<<<<< HEAD
		return global_alloc(Movec_2(opc, w0, w1));
=======
		return std::make_unique<Movec_2>(opc, w0, w1);
>>>>>>> upstream/master
	}
	/* MOVE(C) : 0011 1WDD DDD1 Z11- : A-144 */
	else if ((w0 & 0xf816) == 0x3816)
	{
<<<<<<< HEAD
		return global_alloc(Movec_3(opc, w0, w1));
=======
		return std::make_unique<Movec_3>(opc, w0, w1);
>>>>>>> upstream/master
	}
	/* MOVE(C) : 0011 1WDD DDD1 t10- xxxx xxxx xxxx xxxx : A-144 */
	else if (((w0 & 0xf816) == 0x3814) && ((w1 & 0x0000) == 0x0000))
	{
<<<<<<< HEAD
		return global_alloc(Movec_4(opc, w0, w1));
=======
		return std::make_unique<Movec_4>(opc, w0, w1);
>>>>>>> upstream/master
	}
	/* MOVE(C) : 0010 10dd dddD DDDD : A-144 */
	else if ((w0 & 0xfc00) == 0x2800)
	{
<<<<<<< HEAD
		return global_alloc(Movec_5(opc, w0, w1));
=======
		return std::make_unique<Movec_5>(opc, w0, w1);
>>>>>>> upstream/master
	}
	/* MOVE(C) : 0000 0101 BBBB BBBB 0011 1WDD DDD0 ---- : A-144 */
	else if (((w0 & 0xff00) == 0x0500) && ((w1 & 0xf810) == 0x3800))
	{
<<<<<<< HEAD
		return global_alloc(Movec_6(opc, w0, w1));
=======
		return std::make_unique<Movec_6>(opc, w0, w1);
>>>>>>> upstream/master
	}
	/* MOVE(I) : 0010 00DD BBBB BBBB : A-150 */
	else if ((w0 & 0xfc00) == 0x2000)
	{
<<<<<<< HEAD
		return global_alloc(Movei(opc, w0, w1));
=======
		return std::make_unique<Movei>(opc, w0, w1);
>>>>>>> upstream/master
	}
	/* MOVE(M) : 0000 001W RR0M MHHH : A-152 */
	else if ((w0 & 0xfe20) == 0x0200)
	{
<<<<<<< HEAD
		return global_alloc(Movem(opc, w0, w1));
=======
		return std::make_unique<Movem>(opc, w0, w1);
>>>>>>> upstream/master
	}
	/* MOVE(M) : 0000 001W RR11 mmRR : A-152 */
	else if ((w0 & 0xfe30) == 0x0230)
	{
<<<<<<< HEAD
		return global_alloc(Movem_2(opc, w0, w1));
=======
		return std::make_unique<Movem_2>(opc, w0, w1);
>>>>>>> upstream/master
	}
	/* MOVE(M) : 0000 0101 BBBB BBBB 0000 001W --0- -HHH : A-152 */
	else if (((w0 & 0xff00) == 0x0500) && ((w1 & 0xfe20) == 0x0200))
	{
<<<<<<< HEAD
		return global_alloc(Movem_3(opc, w0, w1));
=======
		return std::make_unique<Movem_3>(opc, w0, w1);
>>>>>>> upstream/master
	}
	/* MOVE(P) : 0001 100W HH1p pppp : A-156 */
	else if ((w0 & 0xfe20) == 0x1820)
	{
<<<<<<< HEAD
		return global_alloc(Movep(opc, w0, w1));
=======
		return std::make_unique<Movep>(opc, w0, w1);
>>>>>>> upstream/master
	}
	/* MOVE(P) : 0000 110W RRmp pppp : A-156 */
	else if ((w0 & 0xfe00) == 0x0c00)
	{
<<<<<<< HEAD
		return global_alloc(Movep_2(opc, w0, w1));
=======
		return std::make_unique<Movep_2>(opc, w0, w1);
>>>>>>> upstream/master
	}
	/* MOVE(S) : 0001 100W HH0a aaaa : A-158 */
	else if ((w0 & 0xfe20) == 0x1800)
	{
<<<<<<< HEAD
		return global_alloc(Moves(opc, w0, w1));
=======
		return std::make_unique<Moves>(opc, w0, w1);
>>>>>>> upstream/master
	}
	/* MPY(su,uu) : 0001 0101 1100 FsQQ : A-164 */
	else if ((w0 & 0xfff0) == 0x15c0)
	{
<<<<<<< HEAD
		return global_alloc(Mpysuuu(opc, w0, w1));
=======
		return std::make_unique<Mpysuuu>(opc, w0, w1);
>>>>>>> upstream/master
	}
	/* NEGC : 0001 0101 0110 F000 : A-168 */
	else if ((w0 & 0xfff7) == 0x1560)
	{
<<<<<<< HEAD
		return global_alloc(Negc(opc, w0, w1));
=======
		return std::make_unique<Negc>(opc, w0, w1);
>>>>>>> upstream/master
	}
	/* NOP : 0000 0000 0000 0000 : A-170 */
	else if ((w0 & 0xffff) == 0x0000)
	{
<<<<<<< HEAD
		return global_alloc(Nop(opc, w0, w1));
=======
		return std::make_unique<Nop>(opc, w0, w1);
>>>>>>> upstream/master
	}
	/* NORM : 0001 0101 0010 F0RR : A-172 */
	else if ((w0 & 0xfff4) == 0x1520)
	{
<<<<<<< HEAD
		return global_alloc(Norm(opc, w0, w1));
=======
		return std::make_unique<Norm>(opc, w0, w1);
>>>>>>> upstream/master
	}
	/* ORI : 0001 1EE1 iiii iiii : A-178 */
	else if ((w0 & 0xf900) == 0x1900)
	{
<<<<<<< HEAD
		return global_alloc(Ori(opc, w0, w1));
=======
		return std::make_unique<Ori>(opc, w0, w1);
>>>>>>> upstream/master
	}
	/* REP : 0000 0000 111- --RR : A-180 */
	else if ((w0 & 0xffe0) == 0x00e0)
	{
<<<<<<< HEAD
		return global_alloc(Rep(opc, w0, w1));
=======
		return std::make_unique<Rep>(opc, w0, w1);
>>>>>>> upstream/master
	}
	/* REP : 0000 1111 iiii iiii : A-180 */
	else if ((w0 & 0xff00) == 0x0f00)
	{
<<<<<<< HEAD
		return global_alloc(Rep_2(opc, w0, w1));
=======
		return std::make_unique<Rep_2>(opc, w0, w1);
>>>>>>> upstream/master
	}
	/* REP : 0000 0100 001D DDDD : A-180 */
	else if ((w0 & 0xffe0) == 0x0420)
	{
<<<<<<< HEAD
		return global_alloc(Rep_3(opc, w0, w1));
=======
		return std::make_unique<Rep_3>(opc, w0, w1);
>>>>>>> upstream/master
	}
	/* REPcc : 0000 0001 0101 cccc : A-184 */
	else if ((w0 & 0xfff0) == 0x0150)
	{
<<<<<<< HEAD
		return global_alloc(Repcc(opc, w0, w1));
=======
		return std::make_unique<Repcc>(opc, w0, w1);
>>>>>>> upstream/master
	}
	/* RESET : 0000 0000 0000 1000 : A-186 */
	else if ((w0 & 0xffff) == 0x0008)
	{
<<<<<<< HEAD
		return global_alloc(Reset(opc, w0, w1));
=======
		return std::make_unique<Reset>(opc, w0, w1);
>>>>>>> upstream/master
	}
	/* RTI : 0000 0000 0000 0111 : A-194 */
	else if ((w0 & 0xffff) == 0x0007)
	{
<<<<<<< HEAD
		return global_alloc(Rti(opc, w0, w1));
=======
		return std::make_unique<Rti>(opc, w0, w1);
>>>>>>> upstream/master
	}
	/* RTS : 0000 0000 0000 0110 : A-196 */
	else if ((w0 & 0xffff) == 0x0006)
	{
<<<<<<< HEAD
		return global_alloc(Rts(opc, w0, w1));
=======
		return std::make_unique<Rts>(opc, w0, w1);
>>>>>>> upstream/master
	}
	/* STOP : 0000 0000 0000 1010 : A-200 */
	else if ((w0 & 0xffff) == 0x000a)
	{
<<<<<<< HEAD
		return global_alloc(Stop(opc, w0, w1));
=======
		return std::make_unique<Stop>(opc, w0, w1);
>>>>>>> upstream/master
	}
	/* SWAP : 0001 0101 0111 F001 : A-206 */
	else if ((w0 & 0xfff7) == 0x1571)
	{
<<<<<<< HEAD
		return global_alloc(Swap(opc, w0, w1));
=======
		return std::make_unique<Swap>(opc, w0, w1);
>>>>>>> upstream/master
	}
	/* SWI : 0000 0000 0000 0101 : A-208 */
	else if ((w0 & 0xffff) == 0x0005)
	{
<<<<<<< HEAD
		return global_alloc(Swi(opc, w0, w1));
=======
		return std::make_unique<Swi>(opc, w0, w1);
>>>>>>> upstream/master
	}
	/* Tcc : 0001 00cc ccTT Fh0h : A-210 */
	else if ((w0 & 0xfc02) == 0x1000)
	{
<<<<<<< HEAD
		return global_alloc(Tcc(opc, w0, w1));
=======
		return std::make_unique<Tcc>(opc, w0, w1);
>>>>>>> upstream/master
	}
	/* TFR(2) : 0001 0101 0000 F00J : A-214 */
	else if ((w0 & 0xfff6) == 0x1500)
	{
<<<<<<< HEAD
		return global_alloc(Tfr2(opc, w0, w1));
=======
		return std::make_unique<Tfr2>(opc, w0, w1);
>>>>>>> upstream/master
	}
	/* TFR(3) : 0010 01mW RRDD FHHH : A-216 */
	else if ((w0 & 0xfc00) == 0x2400)
	{
<<<<<<< HEAD
		return global_alloc(Tfr3(opc, w0, w1));
=======
		return std::make_unique<Tfr3>(opc, w0, w1);
>>>>>>> upstream/master
	}
	/* TST(2) : 0001 0101 0001 -1DD : A-220 */
	else if ((w0 & 0xfffc) == 0x1514)
	// NEW // else if ((w0 & 0xfff4) == 0x1514)
	{
<<<<<<< HEAD
		return global_alloc(Tst2(opc, w0, w1));
=======
		return std::make_unique<Tst2>(opc, w0, w1);
>>>>>>> upstream/master
	}
	/* WAIT : 0000 0000 0000 1011 : A-222 */
	else if ((w0 & 0xffff) == 0x000b)
	{
<<<<<<< HEAD
		return global_alloc(Wait(opc, w0, w1));
=======
		return std::make_unique<Wait>(opc, w0, w1);
>>>>>>> upstream/master
	}
	/* ZERO : 0001 0101 0101 F000 : A-224 */
	else if ((w0 & 0xfff7) == 0x1550)
	{
<<<<<<< HEAD
		return global_alloc(Zero(opc, w0, w1));
=======
		return std::make_unique<Zero>(opc, w0, w1);
>>>>>>> upstream/master
	}
	/* SHFL : 0001 0101 1101 FQQQ : !!UNDOCUMENTED!! */
	else if ((w0 & 0xfff0) ==  0x15d0)
	{
<<<<<<< HEAD
		return global_alloc(Shfl(opc, w0, w1));
=======
		return std::make_unique<Shfl>(opc, w0, w1);
>>>>>>> upstream/master
	}
	/* SHFR : 0001 0101 1111 FQQQ : !!UNDOCUMENTED!! */
	else if ((w0 & 0xfff0) ==  0x15f0)
	{
<<<<<<< HEAD
		return global_alloc(Shfr(opc, w0, w1));
	}

	return NULL;
=======
		return std::make_unique<Shfr>(opc, w0, w1);
	}

	return nullptr;
>>>>>>> upstream/master
}

}
