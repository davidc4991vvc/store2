// license:BSD-3-Clause
// copyright-holders:Andrew Gardner
#ifndef __DSP56K_INSTRUCTION_H__
#define __DSP56K_INSTRUCTION_H__

#include "opcode.h"
#include "tables.h"

#include "dsp56k.h"
#include "dsp56def.h"
#include "dsp56pcu.h"

//
// An Instruction is the base class all regular ops inherit from.
//
namespace DSP56K
{
#define ADDRESS(X) ((X)<<1)
#define UNIMPLEMENTED_OPCODE() osd_printf_error("Unimplemented opcode:  PC=%04x | %s;\n", PC, __PRETTY_FUNCTION__);

class Opcode;

class Instruction
{
public:
	Instruction(const Opcode* oco) : m_valid(false),
										m_oco(oco),
										m_sizeIncrement(0),
										m_source(iINVALID),
										m_destination(iINVALID) { }
	virtual ~Instruction() {}

<<<<<<< HEAD
	virtual bool decode(const UINT16 word0, const UINT16 word1) = 0;
=======
	virtual bool decode(const uint16_t word0, const uint16_t word1) = 0;
>>>>>>> upstream/master
	virtual void disassemble(std::string& retString) const = 0;
	virtual void evaluate(dsp56k_core* cpustate) = 0;

	virtual size_t size() const = 0;
	virtual size_t evalSize() const { return size(); }
	virtual size_t accumulatorBitsModified() const = 0;   // Potentially make this always return ALL (like flags)
	virtual size_t flags() const { return 0; }

<<<<<<< HEAD
	static Instruction* decodeInstruction(const Opcode* opc,
											const UINT16 word0,
											const UINT16 word1,
=======
	static std::unique_ptr<Instruction> decodeInstruction(const Opcode* opc,
											const uint16_t word0,
											const uint16_t word1,
>>>>>>> upstream/master
											bool shifted=false);

	bool valid() const { return m_valid; }

	const reg_id& source() const { return m_source; }
	const reg_id& destination() const { return m_destination; }

	size_t sizeIncrement() const { return m_sizeIncrement; }

protected:
	bool m_valid;
	const Opcode* m_oco;
	size_t m_sizeIncrement;

	// Parameters nearly everyone has
	reg_id m_source;
	reg_id m_destination;
};


////////////////////////////////////////////////////////////////////////////////
//  OPS                             ////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

// ABS : .... .... 0111 F001 : A-18 ////////////////////////////////////////////
class Abs: public Instruction
{
public:
<<<<<<< HEAD
	Abs(const Opcode* oco, const UINT16 word0, const UINT16 word1) : Instruction(oco)
	{
		m_valid = decode(word0, word1);
	}
	bool decode(const UINT16 word0, const UINT16 word1)
=======
	Abs(const Opcode* oco, const uint16_t word0, const uint16_t word1) : Instruction(oco)
	{
		m_valid = decode(word0, word1);
	}
	bool decode(const uint16_t word0, const uint16_t word1) override
>>>>>>> upstream/master
	{
		decode_F_table(BITSn(word0,0x08), m_destination);
		return true;
	}
<<<<<<< HEAD
	void disassemble(std::string& retString) const
	{
		retString = "abs " + regIdAsString(m_destination);
	}
	void evaluate(dsp56k_core* cpustate) {}
	size_t size() const { return 1; }
	size_t accumulatorBitsModified() const { return BM_HIGH | BM_MIDDLE | BM_LOW; }
=======
	void disassemble(std::string& retString) const override
	{
		retString = "abs " + regIdAsString(m_destination);
	}
	void evaluate(dsp56k_core* cpustate) override {}
	size_t size() const override { return 1; }
	size_t accumulatorBitsModified() const override { return BM_HIGH | BM_MIDDLE | BM_LOW; }
>>>>>>> upstream/master
};

// ADC : 0001 0101 0000 F01J : A-20 ////////////////////////////////////////////
class Adc: public Instruction
{
public:
<<<<<<< HEAD
	Adc(const Opcode* oco, const UINT16 word0, const UINT16 word1) : Instruction(oco)
	{
		m_valid = decode(word0, word1);
	}
	bool decode(const UINT16 word0, const UINT16 word1)
=======
	Adc(const Opcode* oco, const uint16_t word0, const uint16_t word1) : Instruction(oco)
	{
		m_valid = decode(word0, word1);
	}
	bool decode(const uint16_t word0, const uint16_t word1) override
>>>>>>> upstream/master
	{
		decode_JF_table(BITSn(word0,0x0001), BITSn(word0,0x0008),
						m_source, m_destination);
		return true;
	}
<<<<<<< HEAD
	void disassemble(std::string& retString) const
	{
		retString = "adc " + regIdAsString(m_source) + "," + regIdAsString(m_destination);
	}
	void evaluate(dsp56k_core* cpustate) {}
	size_t size() const { return 1; }
	size_t accumulatorBitsModified() const { return BM_HIGH | BM_MIDDLE | BM_LOW; }
=======
	void disassemble(std::string& retString) const override
	{
		retString = "adc " + regIdAsString(m_source) + "," + regIdAsString(m_destination);
	}
	void evaluate(dsp56k_core* cpustate) override {}
	size_t size() const override { return 1; }
	size_t accumulatorBitsModified() const override { return BM_HIGH | BM_MIDDLE | BM_LOW; }
>>>>>>> upstream/master
};

// ADD : .... .... 0000 FJJJ : A-22 ////////////////////////////////////////////
class Add: public Instruction
{
public:
<<<<<<< HEAD
	Add(const Opcode* oco, const UINT16 word0, const UINT16 word1) : Instruction(oco)
	{
		m_valid = decode(word0, word1);
	}
	bool decode(const UINT16 word0, const UINT16 word1)
=======
	Add(const Opcode* oco, const uint16_t word0, const uint16_t word1) : Instruction(oco)
	{
		m_valid = decode(word0, word1);
	}
	bool decode(const uint16_t word0, const uint16_t word1) override
>>>>>>> upstream/master
	{
		decode_JJJF_table(BITSn(word0,0x07), BITSn(word0,0x08),
							m_source, m_destination);
		return true;
	}
<<<<<<< HEAD
	void disassemble(std::string& retString) const
	{
		retString = "add " + regIdAsString(m_source) + "," + regIdAsString(m_destination);
	}
	void evaluate(dsp56k_core* cpustate) {}
	size_t size() const { return 1; }
	size_t accumulatorBitsModified() const { return BM_HIGH | BM_MIDDLE | BM_LOW; }
=======
	void disassemble(std::string& retString) const override
	{
		retString = "add " + regIdAsString(m_source) + "," + regIdAsString(m_destination);
	}
	void evaluate(dsp56k_core* cpustate) override {}
	size_t size() const override { return 1; }
	size_t accumulatorBitsModified() const override { return BM_HIGH | BM_MIDDLE | BM_LOW; }
>>>>>>> upstream/master
};

// ??? Odd that i should put the 011m mKKK everywhere ???  TODO
// ADD : 011m mKKK 0rru Fuuu : A-22 ////////////////////////////////////////////
class Add_2: public Instruction
{
public:
<<<<<<< HEAD
	Add_2(const Opcode* oco, const UINT16 word0, const UINT16 word1) : Instruction(oco)
=======
	Add_2(const Opcode* oco, const uint16_t word0, const uint16_t word1) : Instruction(oco)
>>>>>>> upstream/master
	{
		m_arg = "";
		m_opcode = "";
		m_valid = decode(word0, word1);
	}
<<<<<<< HEAD
	bool decode(const UINT16 word0, const UINT16 word1)
=======
	bool decode(const uint16_t word0, const uint16_t word1) override
>>>>>>> upstream/master
	{
		decode_uuuuF_table(BITSn(word0,0x17), BITSn(word0,0x08),
							m_opcode, m_source, m_destination);
		// TODO: m_opcode = "add";
		return true;
	}
<<<<<<< HEAD
	void disassemble(std::string& retString) const
	{
		retString = m_opcode + " " + regIdAsString(m_source) + "," + regIdAsString(m_destination);
	}
	void evaluate(dsp56k_core* cpustate) {}
	size_t size() const { return 1; }
	size_t accumulatorBitsModified() const { return BM_HIGH | BM_MIDDLE | BM_LOW; }
=======
	void disassemble(std::string& retString) const override
	{
		retString = m_opcode + " " + regIdAsString(m_source) + "," + regIdAsString(m_destination);
	}
	void evaluate(dsp56k_core* cpustate) override {}
	size_t size() const override { return 1; }
	size_t accumulatorBitsModified() const override { return BM_HIGH | BM_MIDDLE | BM_LOW; }
>>>>>>> upstream/master

private:
	std::string m_opcode;
	std::string m_arg;  // TODO: get rid of this Add|Sub thing.
};

// AND : .... .... 0110 F1JJ : A-24 ////////////////////////////////////////////
class And: public Instruction
{
public:
<<<<<<< HEAD
	And(const Opcode* oco, const UINT16 word0, const UINT16 word1) : Instruction(oco)
	{
		m_valid = decode(word0, word1);
	}
	bool decode(const UINT16 word0, const UINT16 word1)
=======
	And(const Opcode* oco, const uint16_t word0, const uint16_t word1) : Instruction(oco)
	{
		m_valid = decode(word0, word1);
	}
	bool decode(const uint16_t word0, const uint16_t word1) override
>>>>>>> upstream/master
	{
		decode_JJF_table(BITSn(word0,0x03),BITSn(word0,0x08),
							m_source, m_destination);
		return true;
	}
<<<<<<< HEAD
	void disassemble(std::string& retString) const
	{
		retString = "and " + regIdAsString(m_source) + "," + regIdAsString(m_destination);
	}
	void evaluate(dsp56k_core* cpustate) {}
	size_t size() const { return 1; }
	size_t accumulatorBitsModified() const { return BM_HIGH | BM_MIDDLE; }
=======
	void disassemble(std::string& retString) const override
	{
		retString = "and " + regIdAsString(m_source) + "," + regIdAsString(m_destination);
	}
	void evaluate(dsp56k_core* cpustate) override {}
	size_t size() const override { return 1; }
	size_t accumulatorBitsModified() const override { return BM_HIGH | BM_MIDDLE; }
>>>>>>> upstream/master
};

// ANDI : 0001 1EE0 iiii iiii : A-26 ///////////////////////////////////////////
class Andi: public Instruction
{
public:
<<<<<<< HEAD
	Andi(const Opcode* oco, const UINT16 word0, const UINT16 word1) : Instruction(oco)
=======
	Andi(const Opcode* oco, const uint16_t word0, const uint16_t word1) : Instruction(oco)
>>>>>>> upstream/master
	{
		m_immediate = 0;
		m_valid = decode(word0, word1);
	}
<<<<<<< HEAD
	bool decode(const UINT16 word0, const UINT16 word1)
=======
	bool decode(const uint16_t word0, const uint16_t word1) override
>>>>>>> upstream/master
	{
		m_immediate = BITSn(word0,0x00ff);
		decode_EE_table(BITSn(word0,0x0600), m_destination);
		return true;
	}
<<<<<<< HEAD
	void disassemble(std::string& retString) const
=======
	void disassemble(std::string& retString) const override
>>>>>>> upstream/master
	{
		char temp[32];
		sprintf(temp, "#$%x,%s", m_immediate, regIdAsString(m_destination).c_str());
		retString = "andi " + std::string(temp);
		// NEW // sprintf(opcode_str, "and(i)");
	}
<<<<<<< HEAD
	void evaluate(dsp56k_core* cpustate) {}
	size_t size() const { return 1; }
	size_t accumulatorBitsModified() const { return BM_HIGH | BM_MIDDLE | BM_LOW; }

private:
	UINT8 m_immediate;
=======
	void evaluate(dsp56k_core* cpustate) override {}
	size_t size() const override { return 1; }
	size_t accumulatorBitsModified() const override { return BM_HIGH | BM_MIDDLE | BM_LOW; }

private:
	uint8_t m_immediate;
>>>>>>> upstream/master
};

// ASL : .... .... 0011 F001 : A-28 ////////////////////////////////////////////
class Asl: public Instruction
{
public:
<<<<<<< HEAD
	Asl(const Opcode* oco, const UINT16 word0, const UINT16 word1) : Instruction(oco)
	{
		m_valid = decode(word0, word1);
	}
	bool decode(const UINT16 word0, const UINT16 word1)
=======
	Asl(const Opcode* oco, const uint16_t word0, const uint16_t word1) : Instruction(oco)
	{
		m_valid = decode(word0, word1);
	}
	bool decode(const uint16_t word0, const uint16_t word1) override
>>>>>>> upstream/master
	{
		decode_F_table(BITSn(word0,0x08), m_destination);
		return true;
	}
<<<<<<< HEAD
	void disassemble(std::string& retString) const
	{
		retString = "asl " + regIdAsString(m_destination);
	}
	void evaluate(dsp56k_core* cpustate) {}
	size_t size() const { return 1; }
	size_t accumulatorBitsModified() const { return BM_HIGH | BM_MIDDLE | BM_LOW; }
=======
	void disassemble(std::string& retString) const override
	{
		retString = "asl " + regIdAsString(m_destination);
	}
	void evaluate(dsp56k_core* cpustate) override {}
	size_t size() const override { return 1; }
	size_t accumulatorBitsModified() const override { return BM_HIGH | BM_MIDDLE | BM_LOW; }
>>>>>>> upstream/master
};

// ASL4 : 0001 0101 0011 F001 : A-30 ///////////////////////////////////////////
class Asl4: public Instruction
{
public:
<<<<<<< HEAD
	Asl4(const Opcode* oco, const UINT16 word0, const UINT16 word1) : Instruction(oco)
	{
		m_valid = decode(word0, word1);
	}
	bool decode(const UINT16 word0, const UINT16 word1)
=======
	Asl4(const Opcode* oco, const uint16_t word0, const uint16_t word1) : Instruction(oco)
	{
		m_valid = decode(word0, word1);
	}
	bool decode(const uint16_t word0, const uint16_t word1) override
>>>>>>> upstream/master
	{
		decode_F_table(BITSn(word0,0x0008), m_destination);
		return true;
	}
<<<<<<< HEAD
	void disassemble(std::string& retString) const
	{
		retString = "asl4 " + regIdAsString(m_destination);
	}
	void evaluate(dsp56k_core* cpustate) {}
	size_t size() const { return 1; }
	size_t accumulatorBitsModified() const { return BM_HIGH | BM_MIDDLE | BM_LOW; }
=======
	void disassemble(std::string& retString) const override
	{
		retString = "asl4 " + regIdAsString(m_destination);
	}
	void evaluate(dsp56k_core* cpustate) override {}
	size_t size() const override { return 1; }
	size_t accumulatorBitsModified() const override { return BM_HIGH | BM_MIDDLE | BM_LOW; }
>>>>>>> upstream/master
};

// ASR : .... .... 0011 F000 : A-32 ////////////////////////////////////////////
class Asr: public Instruction
{
public:
<<<<<<< HEAD
	Asr(const Opcode* oco, const UINT16 word0, const UINT16 word1) : Instruction(oco)
	{
		m_valid = decode(word0, word1);
	}
	bool decode(const UINT16 word0, const UINT16 word1)
=======
	Asr(const Opcode* oco, const uint16_t word0, const uint16_t word1) : Instruction(oco)
	{
		m_valid = decode(word0, word1);
	}
	bool decode(const uint16_t word0, const uint16_t word1) override
>>>>>>> upstream/master
	{
		decode_F_table(BITSn(word0,0x08), m_destination);
		return true;
	}
<<<<<<< HEAD
	void disassemble(std::string& retString) const
	{
		retString = "asr " + regIdAsString(m_destination);
	}
	void evaluate(dsp56k_core* cpustate) {}
	size_t size() const { return 1; }
	size_t accumulatorBitsModified() const { return BM_HIGH | BM_MIDDLE | BM_LOW; }
=======
	void disassemble(std::string& retString) const override
	{
		retString = "asr " + regIdAsString(m_destination);
	}
	void evaluate(dsp56k_core* cpustate) override {}
	size_t size() const override { return 1; }
	size_t accumulatorBitsModified() const override { return BM_HIGH | BM_MIDDLE | BM_LOW; }
>>>>>>> upstream/master
};

// ASR4 : 0001 0101 0011 F000 : A-34 ///////////////////////////////////////////
class Asr4: public Instruction
{
public:
<<<<<<< HEAD
	Asr4(const Opcode* oco, const UINT16 word0, const UINT16 word1) : Instruction(oco)
	{
		m_valid = decode(word0, word1);
	}
	bool decode(const UINT16 word0, const UINT16 word1)
=======
	Asr4(const Opcode* oco, const uint16_t word0, const uint16_t word1) : Instruction(oco)
	{
		m_valid = decode(word0, word1);
	}
	bool decode(const uint16_t word0, const uint16_t word1) override
>>>>>>> upstream/master
	{
		decode_F_table(BITSn(word0,0x0008), m_destination);
		return true;
	}
<<<<<<< HEAD
	void disassemble(std::string& retString) const
	{
		retString = "asr4 " + regIdAsString(m_destination);
	}
	void evaluate(dsp56k_core* cpustate) {}
	size_t size() const { return 1; }
	size_t accumulatorBitsModified() const { return BM_HIGH | BM_MIDDLE | BM_LOW; }
=======
	void disassemble(std::string& retString) const override
	{
		retString = "asr4 " + regIdAsString(m_destination);
	}
	void evaluate(dsp56k_core* cpustate) override {}
	size_t size() const override { return 1; }
	size_t accumulatorBitsModified() const override { return BM_HIGH | BM_MIDDLE | BM_LOW; }
>>>>>>> upstream/master
};

// ASR16 : 0001 0101 0111 F000 : A-36 //////////////////////////////////////////
class Asr16: public Instruction
{
public:
<<<<<<< HEAD
	Asr16(const Opcode* oco, const UINT16 word0, const UINT16 word1) : Instruction(oco)
	{
		m_valid = decode(word0, word1);
	}
	bool decode(const UINT16 word0, const UINT16 word1)
=======
	Asr16(const Opcode* oco, const uint16_t word0, const uint16_t word1) : Instruction(oco)
	{
		m_valid = decode(word0, word1);
	}
	bool decode(const uint16_t word0, const uint16_t word1) override
>>>>>>> upstream/master
	{
		decode_F_table(BITSn(word0,0x0008), m_destination);
		return true;
	}
<<<<<<< HEAD
	void disassemble(std::string& retString) const
	{
		retString = "asr16 " + regIdAsString(m_destination);
	}
	void evaluate(dsp56k_core* cpustate) {}
	size_t size() const { return 1; }
	size_t accumulatorBitsModified() const { return BM_HIGH | BM_MIDDLE | BM_LOW; }
=======
	void disassemble(std::string& retString) const override
	{
		retString = "asr16 " + regIdAsString(m_destination);
	}
	void evaluate(dsp56k_core* cpustate) override {}
	size_t size() const override { return 1; }
	size_t accumulatorBitsModified() const override { return BM_HIGH | BM_MIDDLE | BM_LOW; }
>>>>>>> upstream/master
};

/* BFCHG  : 0001 0100 11Pp pppp BBB1 0010 iiii iiii : A-38 */
/* BFCLR  : 0001 0100 11Pp pppp BBB0 0100 iiii iiii : A-40 */
/* BFSET  : 0001 0100 11Pp pppp BBB1 1000 iiii iiii : A-42 */
/* BFTSTH : 0001 0100 01Pp pppp BBB1 0000 iiii iiii : A-44 */
/* BFTSTL : 0001 0100 01Pp pppp BBB0 0000 iiii iiii : A-46 */
class BfInstruction: public Instruction
{
public:
<<<<<<< HEAD
	BfInstruction(const Opcode* oco, const UINT16 word0, const UINT16 word1) : Instruction(oco)
=======
	BfInstruction(const Opcode* oco, const uint16_t word0, const uint16_t word1) : Instruction(oco)
>>>>>>> upstream/master
	{
		dString = "";
		m_opcode = "";
		m_iVal = 0x0000;
		m_valid = decode(word0, word1);
	}
<<<<<<< HEAD
	bool decode(const UINT16 word0, const UINT16 word1)
=======
	bool decode(const uint16_t word0, const uint16_t word1) override
>>>>>>> upstream/master
	{
		/* Decode the common parts */
		m_iVal = BITSn(word1,0x00ff);

		bfShift upperMiddleLower = decode_BBB_table(BITSn(word1,0xe000));
		switch(upperMiddleLower)
		{
			case BBB_UPPER:  m_iVal <<= 8; break;
			case BBB_MIDDLE: m_iVal <<= 4; break;
			case BBB_LOWER:  m_iVal <<= 0; break;

			case BBB_INVALID: return false;
		}

		assemble_D_from_P_table(BITSn(word0,0x0020), BITSn(word0,0x001f), dString);

		if (dString.compare("!!") == 0)
			return false;

		switch(BITSn(word1,0x1f00))
		{
			case 0x12: m_opcode = "bfchg";  break;
			case 0x04: m_opcode = "bfclr";  break;
			case 0x18: m_opcode = "bfset";  break;
			case 0x10: m_opcode = "bftsth"; break;
			case 0x00: m_opcode = "bftstl"; break;
		}
		return true;
	}
<<<<<<< HEAD
	void disassemble(std::string& retString) const
=======
	void disassemble(std::string& retString) const override
>>>>>>> upstream/master
	{
		char temp[32];
		sprintf(temp, "#$%x", m_iVal);
		retString = m_opcode + " " + std::string(temp) + "," + dString;
		// NEW // sprintf(temp, "#$%04x", iVal);
	}
<<<<<<< HEAD
	void evaluate(dsp56k_core* cpustate) {}
	size_t size() const { return 2; }
	size_t accumulatorBitsModified() const { return BM_HIGH | BM_MIDDLE | BM_LOW; }
private:
	UINT16 m_iVal;
=======
	void evaluate(dsp56k_core* cpustate) override {}
	size_t size() const override { return 2; }
	size_t accumulatorBitsModified() const override { return BM_HIGH | BM_MIDDLE | BM_LOW; }
private:
	uint16_t m_iVal;
>>>>>>> upstream/master
	std::string m_opcode;
	std::string dString;
};

/* BFCHG  : 0001 0100 101- --RR BBB1 0010 iiii iiii : A-38 */
/* BFCLR  : 0001 0100 101- --RR BBB0 0100 iiii iiii : A-40 */
/* BFSET  : 0001 0100 101- --RR BBB1 1000 iiii iiii : A-42 */
/* BFTSTH : 0001 0100 001- --RR BBB1 0000 iiii iiii : A-44 */
/* BFTSTL : 0001 0100 001- --RR BBB0 0000 iiii iiii : A-46 */
class BfInstruction_2: public Instruction
{
public:
<<<<<<< HEAD
	BfInstruction_2(const Opcode* oco, const UINT16 word0, const UINT16 word1) : Instruction(oco)
=======
	BfInstruction_2(const Opcode* oco, const uint16_t word0, const uint16_t word1) : Instruction(oco)
>>>>>>> upstream/master
	{
		m_opcode = "";
		m_r = iINVALID;
		m_iVal = 0x0000;
		m_valid = decode(word0, word1);
	}
<<<<<<< HEAD
	bool decode(const UINT16 word0, const UINT16 word1)
=======
	bool decode(const uint16_t word0, const uint16_t word1) override
>>>>>>> upstream/master
	{
		/* Decode the common parts */
		m_iVal = BITSn(word1,0x00ff);

		bfShift upperMiddleLower = decode_BBB_table(BITSn(word1,0xe000));
		switch(upperMiddleLower)
		{
			case BBB_UPPER:  m_iVal <<= 8; break;
			case BBB_MIDDLE: m_iVal <<= 4; break;
			case BBB_LOWER:  m_iVal <<= 0; break;

			case BBB_INVALID: return false;
		}

		decode_RR_table(BITSn(word0,0x0003), m_r);

		if (m_r == iINVALID)
			return false;

		switch(BITSn(word1,0x1f00))
		{
			case 0x12: m_opcode = "bfchg";  break;
			case 0x04: m_opcode = "bfclr";  break;
			case 0x18: m_opcode = "bfset";  break;
			case 0x10: m_opcode = "bftsth"; break;
			case 0x00: m_opcode = "bftstl"; break;
		}
		return true;
	}
<<<<<<< HEAD
	void disassemble(std::string& retString) const
=======
	void disassemble(std::string& retString) const override
>>>>>>> upstream/master
	{
		char temp[32];
		sprintf(temp, "#$%x", m_iVal);
		std::string source = temp;

		sprintf(temp, "X:(%s)", regIdAsString(m_r).c_str());
		std::string destination = temp;

		retString = m_opcode + " " + source + "," + destination;
		// NEW // sprintf(temp, "#$%04x", m_iVal);
	}
<<<<<<< HEAD
	void evaluate(dsp56k_core* cpustate) {}
	size_t size() const { return 2; }
	size_t accumulatorBitsModified() const { return BM_HIGH | BM_MIDDLE | BM_LOW; }

private:
	reg_id m_r;
	UINT16 m_iVal;
=======
	void evaluate(dsp56k_core* cpustate) override {}
	size_t size() const override { return 2; }
	size_t accumulatorBitsModified() const override { return BM_HIGH | BM_MIDDLE | BM_LOW; }

private:
	reg_id m_r;
	uint16_t m_iVal;
>>>>>>> upstream/master
	std::string m_opcode;
};

/* BFCHG  : 0001 0100 100D DDDD BBB1 0010 iiii iiii : A-38 */
/* BFCLR  : 0001 0100 100D DDDD BBB0 0100 iiii iiii : A-40 */
/* BFSET  : 0001 0100 100D DDDD BBB1 1000 iiii iiii : A-42 */
/* BFTSTH : 0001 0100 000D DDDD BBB1 0000 iiii iiii : A-44 */
/* BFTSTL : 0001 0100 000D DDDD BBB0 0000 iiii iiii : A-46 */
class BfInstruction_3: public Instruction
{
public:
<<<<<<< HEAD
	BfInstruction_3(const Opcode* oco, const UINT16 word0, const UINT16 word1) : Instruction(oco)
=======
	BfInstruction_3(const Opcode* oco, const uint16_t word0, const uint16_t word1) : Instruction(oco)
>>>>>>> upstream/master
	{
		m_opcode = "";
		m_iVal = 0x0000;
		m_valid = decode(word0, word1);
	}
<<<<<<< HEAD
	bool decode(const UINT16 word0, const UINT16 word1)
=======
	bool decode(const uint16_t word0, const uint16_t word1) override
>>>>>>> upstream/master
	{
		/* Decode the common parts */
		m_iVal = BITSn(word1,0x00ff);

		bfShift upperMiddleLower = decode_BBB_table(BITSn(word1,0xe000));
		switch(upperMiddleLower)
		{
			case BBB_UPPER:  m_iVal <<= 8; break;
			case BBB_MIDDLE: m_iVal <<= 4; break;
			case BBB_LOWER:  m_iVal <<= 0; break;

			case BBB_INVALID: return false;
		}

		decode_DDDDD_table(BITSn(word0,0x001f), m_destination);

		if (m_destination == iINVALID)
			return false;

		switch(BITSn(word1,0x1f00))
		{
			case 0x12: m_opcode = "bfchg";  break;
			case 0x04: m_opcode = "bfclr";  break;
			case 0x18: m_opcode = "bfset";  break;
			case 0x10: m_opcode = "bftsth"; break;
			case 0x00: m_opcode = "bftstl"; break;
		}
		return true;
	}
<<<<<<< HEAD
	void disassemble(std::string& retString) const
=======
	void disassemble(std::string& retString) const override
>>>>>>> upstream/master
	{
		char temp[32];
		sprintf(temp, "#$%x", m_iVal);
		std::string source = temp;

		retString = m_opcode + " " + source + "," + regIdAsString(m_destination);
		// NEW // sprintf(temp, "#$%04x", m_iVal);
	}
<<<<<<< HEAD
	void evaluate(dsp56k_core* cpustate) {}
	size_t size() const { return 2; }
	size_t accumulatorBitsModified() const { return BM_HIGH | BM_MIDDLE | BM_LOW; }

private:
	UINT16 m_iVal;
=======
	void evaluate(dsp56k_core* cpustate) override {}
	size_t size() const override { return 2; }
	size_t accumulatorBitsModified() const override { return BM_HIGH | BM_MIDDLE | BM_LOW; }

private:
	uint16_t m_iVal;
>>>>>>> upstream/master
	std::string m_opcode;
};

// Bcc : 0000 0111 --11 cccc xxxx xxxx xxxx xxxx : A-48 ////////////////////////
class Bcc: public Instruction
{
public:
<<<<<<< HEAD
	Bcc(const Opcode* oco, const UINT16 word0, const UINT16 word1) : Instruction(oco)
=======
	Bcc(const Opcode* oco, const uint16_t word0, const uint16_t word1) : Instruction(oco)
>>>>>>> upstream/master
	{
		m_mnem = oINVALID;
		m_immediate = 0;
		m_valid = decode(word0, word1);
	}
<<<<<<< HEAD
	bool decode(const UINT16 word0, const UINT16 word1)
	{
		m_immediate = (INT16)word1;
		decode_cccc_table(BITSn(word0,0x000f), m_mnem);
		return true;
	}
	void disassemble(std::string& retString) const
=======
	bool decode(const uint16_t word0, const uint16_t word1) override
	{
		m_immediate = (int16_t)word1;
		decode_cccc_table(BITSn(word0,0x000f), m_mnem);
		return true;
	}
	void disassemble(std::string& retString) const override
>>>>>>> upstream/master
	{
		std::string opcode = "b" + opMnemonicAsString(m_mnem);
		// NEW // sprintf(opcode_str, "b.%s", M);

		char temp[32];
		sprintf(temp, ">*+$%x", 2 + m_immediate);
<<<<<<< HEAD
		// NEW // sprintf(temp, "$%04x (%d)", pc + 2 + (INT16)word1, (INT16)word1);
		retString = opcode + " " + std::string(temp);
	}
	void evaluate(dsp56k_core* cpustate) {}
	size_t size() const { return 2; }
	size_t accumulatorBitsModified() const { return BM_HIGH | BM_MIDDLE | BM_LOW; }

private:
	op_mnem m_mnem;
	INT16 m_immediate;
=======
		// NEW // sprintf(temp, "$%04x (%d)", pc + 2 + (int16_t)word1, (int16_t)word1);
		retString = opcode + " " + std::string(temp);
	}
	void evaluate(dsp56k_core* cpustate) override {}
	size_t size() const override { return 2; }
	size_t accumulatorBitsModified() const override { return BM_HIGH | BM_MIDDLE | BM_LOW; }

private:
	op_mnem m_mnem;
	int16_t m_immediate;
>>>>>>> upstream/master
};

// Bcc : 0010 11cc ccee eeee : A-48 ////////////////////////////////////////////
class Bcc_2: public Instruction
{
public:
<<<<<<< HEAD
	Bcc_2(const Opcode* oco, const UINT16 word0, const UINT16 word1) : Instruction(oco)
=======
	Bcc_2(const Opcode* oco, const uint16_t word0, const uint16_t word1) : Instruction(oco)
>>>>>>> upstream/master
	{
		m_immediate = 0;
		m_mnem = oINVALID;
		m_valid = decode(word0, word1);
	}
<<<<<<< HEAD
	bool decode(const UINT16 word0, const UINT16 word1)
=======
	bool decode(const uint16_t word0, const uint16_t word1) override
>>>>>>> upstream/master
	{
		decode_cccc_table(BITSn(word0,0x3c0), m_mnem);
		m_immediate = get_6_bit_signed_value(BITSn(word0,0x003f));
		return true;
	}
<<<<<<< HEAD
	void disassemble(std::string& retString) const
=======
	void disassemble(std::string& retString) const override
>>>>>>> upstream/master
	{
		std::string opcode = "b" + opMnemonicAsString(m_mnem);
		// NEW // sprintf(opcode_str, "b.%s", M);

		char temp[32];
		if (m_immediate >= 0) sprintf(temp, "<*+$%x", m_immediate + 1);
		else                  sprintf(temp, "<*-$%x", 1 - m_immediate - 2);
		// NEW // sprintf(temp, "$%04x (%d)", pc + 1 + relativeInt, relativeInt);

		retString = opcode + " " + std::string(temp);
	}
<<<<<<< HEAD
	void evaluate(dsp56k_core* cpustate) {}
	size_t size() const { return 1; }
	size_t accumulatorBitsModified() const { return BM_HIGH | BM_MIDDLE | BM_LOW; }

private:
	op_mnem m_mnem;
	INT8 m_immediate;
=======
	void evaluate(dsp56k_core* cpustate) override {}
	size_t size() const override { return 1; }
	size_t accumulatorBitsModified() const override { return BM_HIGH | BM_MIDDLE | BM_LOW; }

private:
	op_mnem m_mnem;
	int8_t m_immediate;
>>>>>>> upstream/master
};

// Bcc : 0000 0111 RR10 cccc : A-48 ////////////////////////////////////////////
class Bcc_3: public Instruction
{
public:
<<<<<<< HEAD
	Bcc_3(const Opcode* oco, const UINT16 word0, const UINT16 word1) : Instruction(oco)
=======
	Bcc_3(const Opcode* oco, const uint16_t word0, const uint16_t word1) : Instruction(oco)
>>>>>>> upstream/master
	{
		m_mnem = oINVALID;
		m_valid = decode(word0, word1);
	}
<<<<<<< HEAD
	bool decode(const UINT16 word0, const UINT16 word1)
=======
	bool decode(const uint16_t word0, const uint16_t word1) override
>>>>>>> upstream/master
	{
		decode_RR_table(BITSn(word0,0x00c0), m_destination);
		decode_cccc_table(BITSn(word0,0x000f), m_mnem);
		return true;
	}
<<<<<<< HEAD
	void disassemble(std::string& retString) const
=======
	void disassemble(std::string& retString) const override
>>>>>>> upstream/master
	{
		std::string opcode = "b" + opMnemonicAsString(m_mnem);
		retString = opcode + " " + regIdAsString(m_destination);
		// NEW // sprintf(opcode_str, "b.%s", M);
	}
<<<<<<< HEAD
	void evaluate(dsp56k_core* cpustate) {}
	size_t size() const { return 1; }
	size_t accumulatorBitsModified() const { return BM_HIGH | BM_MIDDLE | BM_LOW; }
=======
	void evaluate(dsp56k_core* cpustate) override {}
	size_t size() const override { return 1; }
	size_t accumulatorBitsModified() const override { return BM_HIGH | BM_MIDDLE | BM_LOW; }
>>>>>>> upstream/master

private:
	op_mnem m_mnem;
};

// BRA : 0000 0001 0011 11-- xxxx xxxx xxxx xxxx : A-50 ////////////////////////
class Bra: public Instruction
{
public:
<<<<<<< HEAD
	Bra(const Opcode* oco, const UINT16 word0, const UINT16 word1) : Instruction(oco)
=======
	Bra(const Opcode* oco, const uint16_t word0, const uint16_t word1) : Instruction(oco)
>>>>>>> upstream/master
	{
		m_immediate = 0;
		m_valid = decode(word0, word1);
	}
<<<<<<< HEAD
	bool decode(const UINT16 word0, const UINT16 word1)
	{
		m_immediate = (INT16)word1;
		return true;
	}
	void disassemble(std::string& retString) const
	{
		char temp[32];
		sprintf(temp, ">*+$%x", 2 + m_immediate);
		// NEW // sprintf(temp, "$%04x (%d)", pc + 2 + word1, (INT16)word1);
		retString = "bra " + std::string(temp);
	}
	void evaluate(dsp56k_core* cpustate) {}
	size_t size() const { return 2; }
	size_t accumulatorBitsModified() const { return BM_HIGH | BM_MIDDLE | BM_LOW; }

private:
	INT16 m_immediate;
=======
	bool decode(const uint16_t word0, const uint16_t word1) override
	{
		m_immediate = (int16_t)word1;
		return true;
	}
	void disassemble(std::string& retString) const override
	{
		char temp[32];
		sprintf(temp, ">*+$%x", 2 + m_immediate);
		// NEW // sprintf(temp, "$%04x (%d)", pc + 2 + word1, (int16_t)word1);
		retString = "bra " + std::string(temp);
	}
	void evaluate(dsp56k_core* cpustate) override {}
	size_t size() const override { return 2; }
	size_t accumulatorBitsModified() const override { return BM_HIGH | BM_MIDDLE | BM_LOW; }

private:
	int16_t m_immediate;
>>>>>>> upstream/master
};

// BRA : 0000 1011 aaaa aaaa : A-50 ////////////////////////////////////////////
class Bra_2: public Instruction
{
public:
<<<<<<< HEAD
	Bra_2(const Opcode* oco, const UINT16 word0, const UINT16 word1) : Instruction(oco)
=======
	Bra_2(const Opcode* oco, const uint16_t word0, const uint16_t word1) : Instruction(oco)
>>>>>>> upstream/master
	{
		m_immediate = 0;
		m_valid = decode(word0, word1);
	}
<<<<<<< HEAD
	bool decode(const UINT16 word0, const UINT16 word1)
	{
		m_immediate = (INT8)BITSn(word0,0x00ff);
		return true;
	}
	void disassemble(std::string& retString) const
=======
	bool decode(const uint16_t word0, const uint16_t word1) override
	{
		m_immediate = (int8_t)BITSn(word0,0x00ff);
		return true;
	}
	void disassemble(std::string& retString) const override
>>>>>>> upstream/master
	{
		char temp[32];
		if (m_immediate >= 0) sprintf(temp, "<*+$%x", 1 + m_immediate);
		else                  sprintf(temp, "<*-$%x", 1 - m_immediate - 2);
		// NEW // sprintf(temp, "$%04x (%d)", pc + 1 + iVal, iVal);
		retString = "bra " + std::string(temp);
	}
<<<<<<< HEAD
	void evaluate(dsp56k_core* cpustate) {}
	size_t size() const { return 1; }
	size_t accumulatorBitsModified() const { return BM_HIGH | BM_MIDDLE | BM_LOW; }

private:
	INT8 m_immediate;
=======
	void evaluate(dsp56k_core* cpustate) override {}
	size_t size() const override { return 1; }
	size_t accumulatorBitsModified() const override { return BM_HIGH | BM_MIDDLE | BM_LOW; }

private:
	int8_t m_immediate;
>>>>>>> upstream/master
};

// BRA : 0000 0001 0010 11RR : A-50 ////////////////////////////////////////////
class Bra_3: public Instruction
{
public:
<<<<<<< HEAD
	Bra_3(const Opcode* oco, const UINT16 word0, const UINT16 word1) : Instruction(oco)
	{
		m_valid = decode(word0, word1);
	}
	bool decode(const UINT16 word0, const UINT16 word1)
=======
	Bra_3(const Opcode* oco, const uint16_t word0, const uint16_t word1) : Instruction(oco)
	{
		m_valid = decode(word0, word1);
	}
	bool decode(const uint16_t word0, const uint16_t word1) override
>>>>>>> upstream/master
	{
		decode_RR_table(BITSn(word0,0x0003), m_destination);
		return true;
	}
<<<<<<< HEAD
	void disassemble(std::string& retString) const
	{
		retString = "bra " + regIdAsString(m_destination);
	}
	void evaluate(dsp56k_core* cpustate) {}
	size_t size() const { return 1; }
	size_t accumulatorBitsModified() const { return BM_HIGH | BM_MIDDLE | BM_LOW; }
=======
	void disassemble(std::string& retString) const override
	{
		retString = "bra " + regIdAsString(m_destination);
	}
	void evaluate(dsp56k_core* cpustate) override {}
	size_t size() const override { return 1; }
	size_t accumulatorBitsModified() const override { return BM_HIGH | BM_MIDDLE | BM_LOW; }
>>>>>>> upstream/master
};

// BRKcc : 0000 0001 0001 cccc : A-52 //////////////////////////////////////////
class Brkcc: public Instruction
{
public:
<<<<<<< HEAD
	Brkcc(const Opcode* oco, const UINT16 word0, const UINT16 word1) : Instruction(oco)
=======
	Brkcc(const Opcode* oco, const uint16_t word0, const uint16_t word1) : Instruction(oco)
>>>>>>> upstream/master
	{
		m_mnem = oINVALID;
		m_valid = decode(word0, word1);
	}
<<<<<<< HEAD
	bool decode(const UINT16 word0, const UINT16 word1)
=======
	bool decode(const uint16_t word0, const uint16_t word1) override
>>>>>>> upstream/master
	{
		decode_cccc_table(BITSn(word0,0x000f), m_mnem);
		return true;
	}
<<<<<<< HEAD
	void disassemble(std::string& retString) const
=======
	void disassemble(std::string& retString) const override
>>>>>>> upstream/master
	{
		std::string opcode = "brk" + opMnemonicAsString(m_mnem);
		retString = opcode;
		// NEW // sprintf(opcode_str, "brk.%s", M);
	}
<<<<<<< HEAD
	void evaluate(dsp56k_core* cpustate) {}
	size_t size() const { return 1; }
	size_t accumulatorBitsModified() const { return BM_HIGH | BM_MIDDLE | BM_LOW; }
=======
	void evaluate(dsp56k_core* cpustate) override {}
	size_t size() const override { return 1; }
	size_t accumulatorBitsModified() const override { return BM_HIGH | BM_MIDDLE | BM_LOW; }
>>>>>>> upstream/master

private:
	op_mnem m_mnem;
};

// BScc : 0000 0111 --01 cccc xxxx xxxx xxxx xxxx : A-54 ///////////////////////
class Bscc: public Instruction
{
public:
<<<<<<< HEAD
	Bscc(const Opcode* oco, const UINT16 word0, const UINT16 word1) : Instruction(oco)
=======
	Bscc(const Opcode* oco, const uint16_t word0, const uint16_t word1) : Instruction(oco)
>>>>>>> upstream/master
	{
		m_immediate = 0;
		m_mnem = oINVALID;
		m_valid = decode(word0, word1);
	}
<<<<<<< HEAD
	bool decode(const UINT16 word0, const UINT16 word1)
	{
		m_immediate = (INT16)word1;
		decode_cccc_table(BITSn(word0,0x000f), m_mnem);
		return true;
	}
	void disassemble(std::string& retString) const
=======
	bool decode(const uint16_t word0, const uint16_t word1) override
	{
		m_immediate = (int16_t)word1;
		decode_cccc_table(BITSn(word0,0x000f), m_mnem);
		return true;
	}
	void disassemble(std::string& retString) const override
>>>>>>> upstream/master
	{
		std::string opcode = "bs" + opMnemonicAsString(m_mnem);
		// NEW // sprintf(opcode_str, "bs.%s", M);

		char temp[32];
		if (m_immediate >= 0) sprintf(temp, ">*+$%x", 2 + m_immediate);
		else                  sprintf(temp, ">*-$%x", 1 - m_immediate - 1 - 2);
		//sprintf(temp, ">*+$%x", 2 + m_immediate);
<<<<<<< HEAD
		// NEW // sprintf(temp, "$%04x (%d)", pc + 2 + (INT16)word1, (INT16)word1);
		retString = opcode + " " + std::string(temp);
	}
	void evaluate(dsp56k_core* cpustate) {}
	size_t size() const { return 2; }
	size_t accumulatorBitsModified() const { return BM_HIGH | BM_MIDDLE | BM_LOW; }
	size_t flags() const { return DASMFLAG_STEP_OVER; }

private:
	op_mnem m_mnem;
	INT16 m_immediate;
=======
		// NEW // sprintf(temp, "$%04x (%d)", pc + 2 + (int16_t)word1, (int16_t)word1);
		retString = opcode + " " + std::string(temp);
	}
	void evaluate(dsp56k_core* cpustate) override {}
	size_t size() const override { return 2; }
	size_t accumulatorBitsModified() const override { return BM_HIGH | BM_MIDDLE | BM_LOW; }
	size_t flags() const override { return DASMFLAG_STEP_OVER; }

private:
	op_mnem m_mnem;
	int16_t m_immediate;
>>>>>>> upstream/master
};

// BScc : 0000 0111 RR00 cccc : A-54 ///////////////////////////////////////////
class Bscc_2: public Instruction
{
public:
<<<<<<< HEAD
	Bscc_2(const Opcode* oco, const UINT16 word0, const UINT16 word1) : Instruction(oco)
=======
	Bscc_2(const Opcode* oco, const uint16_t word0, const uint16_t word1) : Instruction(oco)
>>>>>>> upstream/master
	{
		m_mnem = oINVALID;
		m_valid = decode(word0, word1);
	}
<<<<<<< HEAD
	bool decode(const UINT16 word0, const UINT16 word1)
=======
	bool decode(const uint16_t word0, const uint16_t word1) override
>>>>>>> upstream/master
	{
		decode_RR_table(BITSn(word0,0x00c0), m_destination);
		decode_cccc_table(BITSn(word0,0x000f), m_mnem);
		return true;
	}
<<<<<<< HEAD
	void disassemble(std::string& retString) const
=======
	void disassemble(std::string& retString) const override
>>>>>>> upstream/master
	{
		std::string opcode = "bs" + opMnemonicAsString(m_mnem);
		retString = opcode + " " + regIdAsString(m_destination);
		// NEW // sprintf(opcode_str, "bs.%s", M);
	}
<<<<<<< HEAD
	void evaluate(dsp56k_core* cpustate) {}
	size_t size() const { return 1; }
	size_t accumulatorBitsModified() const { return BM_HIGH | BM_MIDDLE | BM_LOW; }
	size_t flags() const { return DASMFLAG_STEP_OVER; }
=======
	void evaluate(dsp56k_core* cpustate) override {}
	size_t size() const override { return 1; }
	size_t accumulatorBitsModified() const override { return BM_HIGH | BM_MIDDLE | BM_LOW; }
	size_t flags() const override { return DASMFLAG_STEP_OVER; }
>>>>>>> upstream/master

private:
	op_mnem m_mnem;
};

// BSR : 0000 0001 0011 10-- xxxx xxxx xxxx xxxx : A-56 ////////////////////////
class Bsr: public Instruction
{
public:
<<<<<<< HEAD
	Bsr(const Opcode* oco, const UINT16 word0, const UINT16 word1) : Instruction(oco)
=======
	Bsr(const Opcode* oco, const uint16_t word0, const uint16_t word1) : Instruction(oco)
>>>>>>> upstream/master
	{
		m_immediate = 0;
		m_valid = decode(word0, word1);
	}
<<<<<<< HEAD
	bool decode(const UINT16 word0, const UINT16 word1)
	{
		m_immediate = (INT16)word1;
		return true;
	}
	void disassemble(std::string& retString) const
=======
	bool decode(const uint16_t word0, const uint16_t word1) override
	{
		m_immediate = (int16_t)word1;
		return true;
	}
	void disassemble(std::string& retString) const override
>>>>>>> upstream/master
	{
		char temp[32];
		if (m_immediate >= 0) sprintf(temp, ">*+$%x", 2 + m_immediate);
		else                  sprintf(temp, ">*-$%x", 1 - m_immediate - 1 - 2);
<<<<<<< HEAD
		// NEW // sprintf(temp, "$%04x (%d)", pc + 2 + (INT16)word1, (INT16)word1);
		retString = "bsr " + std::string(temp);
	}
	void evaluate(dsp56k_core* cpustate) {}
	size_t size() const { return 2; }
	size_t accumulatorBitsModified() const { return BM_HIGH | BM_MIDDLE | BM_LOW; }
	size_t flags() const { return DASMFLAG_STEP_OVER; }

private:
	INT16 m_immediate;
=======
		// NEW // sprintf(temp, "$%04x (%d)", pc + 2 + (int16_t)word1, (int16_t)word1);
		retString = "bsr " + std::string(temp);
	}
	void evaluate(dsp56k_core* cpustate) override {}
	size_t size() const override { return 2; }
	size_t accumulatorBitsModified() const override { return BM_HIGH | BM_MIDDLE | BM_LOW; }
	size_t flags() const override { return DASMFLAG_STEP_OVER; }

private:
	int16_t m_immediate;
>>>>>>> upstream/master
};

// BSR : 0000 0001 0010 10RR : A-56 ////////////////////////////////////////////
class Bsr_2: public Instruction
{
public:
<<<<<<< HEAD
	Bsr_2(const Opcode* oco, const UINT16 word0, const UINT16 word1) : Instruction(oco)
	{
		m_valid = decode(word0, word1);
	}
	bool decode(const UINT16 word0, const UINT16 word1)
=======
	Bsr_2(const Opcode* oco, const uint16_t word0, const uint16_t word1) : Instruction(oco)
	{
		m_valid = decode(word0, word1);
	}
	bool decode(const uint16_t word0, const uint16_t word1) override
>>>>>>> upstream/master
	{
		decode_RR_table(BITSn(word0,0x0003), m_destination);
		return true;
	}
<<<<<<< HEAD
	void disassemble(std::string& retString) const
	{
		retString = "bsr " + regIdAsString(m_destination);
	}
	void evaluate(dsp56k_core* cpustate) {}
	size_t size() const { return 1; }
	size_t accumulatorBitsModified() const { return BM_HIGH | BM_MIDDLE | BM_LOW; }
	size_t flags() const { return DASMFLAG_STEP_OVER; }
=======
	void disassemble(std::string& retString) const override
	{
		retString = "bsr " + regIdAsString(m_destination);
	}
	void evaluate(dsp56k_core* cpustate) override {}
	size_t size() const override { return 1; }
	size_t accumulatorBitsModified() const override { return BM_HIGH | BM_MIDDLE | BM_LOW; }
	size_t flags() const override { return DASMFLAG_STEP_OVER; }
>>>>>>> upstream/master
};

// CHKAAU : 0000 0000 0000 0100 : A-58 /////////////////////////////////////////
class Chkaau: public Instruction
{
public:
<<<<<<< HEAD
	Chkaau(const Opcode* oco, const UINT16 word0, const UINT16 word1) : Instruction(oco)
	{
		m_valid = decode(word0, word1);
	}
	bool decode(const UINT16 word0, const UINT16 word1)
	{
		return true;
	}
	void disassemble(std::string& retString) const
	{
		retString = "chkaau";
	}
	void evaluate(dsp56k_core* cpustate) {}
	size_t size() const { return 1; }
	size_t accumulatorBitsModified() const { return BM_HIGH | BM_MIDDLE | BM_LOW; }
=======
	Chkaau(const Opcode* oco, const uint16_t word0, const uint16_t word1) : Instruction(oco)
	{
		m_valid = decode(word0, word1);
	}
	bool decode(const uint16_t word0, const uint16_t word1) override
	{
		return true;
	}
	void disassemble(std::string& retString) const override
	{
		retString = "chkaau";
	}
	void evaluate(dsp56k_core* cpustate) override {}
	size_t size() const override { return 1; }
	size_t accumulatorBitsModified() const override { return BM_HIGH | BM_MIDDLE | BM_LOW; }
>>>>>>> upstream/master
};

// CLR : .... .... 0000 F001 : A-60 ////////////////////////////////////////////
class Clr: public Instruction
{
public:
<<<<<<< HEAD
	Clr(const Opcode* oco, const UINT16 word0, const UINT16 word1) : Instruction(oco)
	{
		m_valid = decode(word0, word1);
	}
	bool decode(const UINT16 word0, const UINT16 word1)
=======
	Clr(const Opcode* oco, const uint16_t word0, const uint16_t word1) : Instruction(oco)
	{
		m_valid = decode(word0, word1);
	}
	bool decode(const uint16_t word0, const uint16_t word1) override
>>>>>>> upstream/master
	{
		decode_F_table(BITSn(word0,0x08), m_destination);
		return true;
	}
<<<<<<< HEAD
	void disassemble(std::string& retString) const
	{
		retString = "clr " + regIdAsString(m_destination);
	}
	void evaluate(dsp56k_core* cpustate) {}
	size_t size() const { return 1; }
	size_t accumulatorBitsModified() const { return BM_HIGH | BM_MIDDLE | BM_LOW; }
=======
	void disassemble(std::string& retString) const override
	{
		retString = "clr " + regIdAsString(m_destination);
	}
	void evaluate(dsp56k_core* cpustate) override {}
	size_t size() const override { return 1; }
	size_t accumulatorBitsModified() const override { return BM_HIGH | BM_MIDDLE | BM_LOW; }
>>>>>>> upstream/master
};

// CLR24 : .... .... 0101 F001 : A-62 //////////////////////////////////////////
class Clr24: public Instruction
{
public:
<<<<<<< HEAD
	Clr24(const Opcode* oco, const UINT16 word0, const UINT16 word1) : Instruction(oco)
	{
		m_valid = decode(word0, word1);
	}
	bool decode(const UINT16 word0, const UINT16 word1)
=======
	Clr24(const Opcode* oco, const uint16_t word0, const uint16_t word1) : Instruction(oco)
	{
		m_valid = decode(word0, word1);
	}
	bool decode(const uint16_t word0, const uint16_t word1) override
>>>>>>> upstream/master
	{
		decode_F_table(BITSn(word0,0x08), m_destination);
		return true;
	}
<<<<<<< HEAD
	void disassemble(std::string& retString) const
	{
		retString = "clr24 " + regIdAsString(m_destination);
	}
	void evaluate(dsp56k_core* cpustate) {}
	size_t size() const { return 1; }
	size_t accumulatorBitsModified() const { return BM_HIGH | BM_MIDDLE; }
=======
	void disassemble(std::string& retString) const override
	{
		retString = "clr24 " + regIdAsString(m_destination);
	}
	void evaluate(dsp56k_core* cpustate) override {}
	size_t size() const override { return 1; }
	size_t accumulatorBitsModified() const override { return BM_HIGH | BM_MIDDLE; }
>>>>>>> upstream/master
};

// CMP : .... .... 0101 FJJJ : A-64 ////////////////////////////////////////////
class Cmp: public Instruction
{
public:
<<<<<<< HEAD
	Cmp(const Opcode* oco, const UINT16 word0, const UINT16 word1) : Instruction(oco)
	{
		m_valid = decode(word0, word1);
	}
	bool decode(const UINT16 word0, const UINT16 word1)
=======
	Cmp(const Opcode* oco, const uint16_t word0, const uint16_t word1) : Instruction(oco)
	{
		m_valid = decode(word0, word1);
	}
	bool decode(const uint16_t word0, const uint16_t word1) override
>>>>>>> upstream/master
	{
		/* Note: This is a JJJF limited in the docs, but other opcodes sneak
		         in before cmp, so the same decode function can be used. */
		decode_JJJF_table(BITSn(word0,0x07), BITSn(word0,0x08),
							m_source, m_destination);
		return true;
	}
<<<<<<< HEAD
	void disassemble(std::string& retString) const
	{
		retString = "cmp " + regIdAsString(m_source) + "," + regIdAsString(m_destination);
	}
	void evaluate(dsp56k_core* cpustate) {}
	size_t size() const { return 1; }
	size_t accumulatorBitsModified() const { return BM_NONE; }
=======
	void disassemble(std::string& retString) const override
	{
		retString = "cmp " + regIdAsString(m_source) + "," + regIdAsString(m_destination);
	}
	void evaluate(dsp56k_core* cpustate) override {}
	size_t size() const override { return 1; }
	size_t accumulatorBitsModified() const override { return BM_NONE; }
>>>>>>> upstream/master
};

// CMPM : .... .... 0111 FJJJ : A-66 ///////////////////////////////////////////
class Cmpm: public Instruction
{
public:
<<<<<<< HEAD
	Cmpm(const Opcode* oco, const UINT16 word0, const UINT16 word1) : Instruction(oco)
	{
		m_valid = decode(word0, word1);
	}
	bool decode(const UINT16 word0, const UINT16 word1)
=======
	Cmpm(const Opcode* oco, const uint16_t word0, const uint16_t word1) : Instruction(oco)
	{
		m_valid = decode(word0, word1);
	}
	bool decode(const uint16_t word0, const uint16_t word1) override
>>>>>>> upstream/master
	{
		/* Note: This is a JJJF limited in the docs, but other opcodes sneak
		         in before cmp, so the same decode function can be used. */
		decode_JJJF_table(BITSn(word0,0x07), BITSn(word0,0x08),
							m_source, m_destination);
		return true;
	}
<<<<<<< HEAD
	void disassemble(std::string& retString) const
	{
		retString = "cmpm " + regIdAsString(m_source) + "," + regIdAsString(m_destination);
	}
	void evaluate(dsp56k_core* cpustate) {}
	size_t size() const { return 1; }
	size_t accumulatorBitsModified() const { return BM_NONE; }
=======
	void disassemble(std::string& retString) const override
	{
		retString = "cmpm " + regIdAsString(m_source) + "," + regIdAsString(m_destination);
	}
	void evaluate(dsp56k_core* cpustate) override {}
	size_t size() const override { return 1; }
	size_t accumulatorBitsModified() const override { return BM_NONE; }
>>>>>>> upstream/master
};

// DEBUG : 0000 0000 0000 0001 : A-68 //////////////////////////////////////////
class Debug: public Instruction
{
public:
<<<<<<< HEAD
	Debug(const Opcode* oco, const UINT16 word0, const UINT16 word1) : Instruction(oco)
	{
		m_valid = decode(word0, word1);
	}
	bool decode(const UINT16 word0, const UINT16 word1)
	{
		return true;
	}
	void disassemble(std::string& retString) const
	{
		retString = "debug";
	}
	void evaluate(dsp56k_core* cpustate) {}
	size_t size() const { return 1; }
	size_t accumulatorBitsModified() const { return BM_HIGH | BM_MIDDLE | BM_LOW; }
=======
	Debug(const Opcode* oco, const uint16_t word0, const uint16_t word1) : Instruction(oco)
	{
		m_valid = decode(word0, word1);
	}
	bool decode(const uint16_t word0, const uint16_t word1) override
	{
		return true;
	}
	void disassemble(std::string& retString) const override
	{
		retString = "debug";
	}
	void evaluate(dsp56k_core* cpustate) override {}
	size_t size() const override { return 1; }
	size_t accumulatorBitsModified() const override { return BM_HIGH | BM_MIDDLE | BM_LOW; }
>>>>>>> upstream/master
};

// DEBUGcc : 0000 0000 0101 cccc : A-70 ////////////////////////////////////////
class Debugcc: public Instruction
{
public:
<<<<<<< HEAD
	Debugcc(const Opcode* oco, const UINT16 word0, const UINT16 word1) : Instruction(oco)
=======
	Debugcc(const Opcode* oco, const uint16_t word0, const uint16_t word1) : Instruction(oco)
>>>>>>> upstream/master
	{
		m_mnem = oINVALID;
		m_valid = decode(word0, word1);
	}
<<<<<<< HEAD
	bool decode(const UINT16 word0, const UINT16 word1)
=======
	bool decode(const uint16_t word0, const uint16_t word1) override
>>>>>>> upstream/master
	{
		decode_cccc_table(BITSn(word0,0x000f), m_mnem);
		return true;
	}
<<<<<<< HEAD
	void disassemble(std::string& retString) const
=======
	void disassemble(std::string& retString) const override
>>>>>>> upstream/master
	{
		std::string opcode = "debug" + opMnemonicAsString(m_mnem);
		retString = opcode;
		// NEW // sprintf(opcode_str, "debug.%s", M);
	}
<<<<<<< HEAD
	void evaluate(dsp56k_core* cpustate) {}
	size_t size() const { return 1; }
	size_t accumulatorBitsModified() const { return BM_HIGH | BM_MIDDLE | BM_LOW; }
=======
	void evaluate(dsp56k_core* cpustate) override {}
	size_t size() const override { return 1; }
	size_t accumulatorBitsModified() const override { return BM_HIGH | BM_MIDDLE | BM_LOW; }
>>>>>>> upstream/master

private:
	op_mnem m_mnem;
};

// DEC : .... .... 0110 F010 : A-72 ////////////////////////////////////////////
class Dec: public Instruction
{
public:
<<<<<<< HEAD
	Dec(const Opcode* oco, const UINT16 word0, const UINT16 word1) : Instruction(oco)
	{
		m_valid = decode(word0, word1);
	}
	bool decode(const UINT16 word0, const UINT16 word1)
=======
	Dec(const Opcode* oco, const uint16_t word0, const uint16_t word1) : Instruction(oco)
	{
		m_valid = decode(word0, word1);
	}
	bool decode(const uint16_t word0, const uint16_t word1) override
>>>>>>> upstream/master
	{
		decode_F_table(BITSn(word0,0x08), m_destination);
		return true;
	}
<<<<<<< HEAD
	void disassemble(std::string& retString) const
	{
		retString = "dec " + regIdAsString(m_destination);
	}
	void evaluate(dsp56k_core* cpustate) {}
	size_t size() const { return 1; }
	size_t accumulatorBitsModified() const { return BM_HIGH | BM_MIDDLE | BM_LOW; }
=======
	void disassemble(std::string& retString) const override
	{
		retString = "dec " + regIdAsString(m_destination);
	}
	void evaluate(dsp56k_core* cpustate) override {}
	size_t size() const override { return 1; }
	size_t accumulatorBitsModified() const override { return BM_HIGH | BM_MIDDLE | BM_LOW; }
>>>>>>> upstream/master
};

// DEC24 : .... .... 0110 F011 : A-74 //////////////////////////////////////////
class Dec24: public Instruction
{
public:
<<<<<<< HEAD
	Dec24(const Opcode* oco, const UINT16 word0, const UINT16 word1) : Instruction(oco)
	{
		m_valid = decode(word0, word1);
	}
	bool decode(const UINT16 word0, const UINT16 word1)
=======
	Dec24(const Opcode* oco, const uint16_t word0, const uint16_t word1) : Instruction(oco)
	{
		m_valid = decode(word0, word1);
	}
	bool decode(const uint16_t word0, const uint16_t word1) override
>>>>>>> upstream/master
	{
		decode_F_table(BITSn(word0,0x08), m_destination);
		return true;
	}
<<<<<<< HEAD
	void disassemble(std::string& retString) const
	{
		retString = "dec24 " + regIdAsString(m_destination);
	}
	void evaluate(dsp56k_core* cpustate) {}
	size_t size() const { return 1; }
	size_t accumulatorBitsModified() const { return BM_HIGH | BM_MIDDLE; }
=======
	void disassemble(std::string& retString) const override
	{
		retString = "dec24 " + regIdAsString(m_destination);
	}
	void evaluate(dsp56k_core* cpustate) override {}
	size_t size() const override { return 1; }
	size_t accumulatorBitsModified() const override { return BM_HIGH | BM_MIDDLE; }
>>>>>>> upstream/master
};

// DIV : 0001 0101 0--0 F1DD : A-76 ////////////////////////////////////////////
class Div: public Instruction
{
public:
<<<<<<< HEAD
	Div(const Opcode* oco, const UINT16 word0, const UINT16 word1) : Instruction(oco)
	{
		m_valid = decode(word0, word1);
	}
	bool decode(const UINT16 word0, const UINT16 word1)
=======
	Div(const Opcode* oco, const uint16_t word0, const uint16_t word1) : Instruction(oco)
	{
		m_valid = decode(word0, word1);
	}
	bool decode(const uint16_t word0, const uint16_t word1) override
>>>>>>> upstream/master
	{
		decode_DDF_table(BITSn(word0,0x0003), BITSn(word0,0x0008),
							m_source, m_destination);
		return true;
	}
<<<<<<< HEAD
	void disassemble(std::string& retString) const
	{
		retString = "div " + regIdAsString(m_source) + "," + regIdAsString(m_destination);
	}
	void evaluate(dsp56k_core* cpustate) {}
	size_t size() const { return 1; }
	size_t accumulatorBitsModified() const { return BM_HIGH | BM_MIDDLE | BM_LOW; }
=======
	void disassemble(std::string& retString) const override
	{
		retString = "div " + regIdAsString(m_source) + "," + regIdAsString(m_destination);
	}
	void evaluate(dsp56k_core* cpustate) override {}
	size_t size() const override { return 1; }
	size_t accumulatorBitsModified() const override { return BM_HIGH | BM_MIDDLE | BM_LOW; }
>>>>>>> upstream/master
};

// DMAC : 0001 0101 10s1 FsQQ : A-80 ///////////////////////////////////////////
class Dmac: public Instruction
{
public:
<<<<<<< HEAD
	Dmac(const Opcode* oco, const UINT16 word0, const UINT16 word1) : Instruction(oco)
=======
	Dmac(const Opcode* oco, const uint16_t word0, const uint16_t word1) : Instruction(oco)
>>>>>>> upstream/master
	{
		m_mnem = oINVALID;
		m_source2 = iINVALID;
		m_valid = decode(word0, word1);
	}
<<<<<<< HEAD
	bool decode(const UINT16 word0, const UINT16 word1)
=======
	bool decode(const uint16_t word0, const uint16_t word1) override
>>>>>>> upstream/master
	{
		decode_QQF_special_table(BITSn(word0,0x0003), BITSn(word0,0x0008),
									m_source, m_source2, m_destination);

		decode_ss_table(BITSn(word0,0x0024), m_mnem);
		if (m_mnem == oINVALID) return false;
		return true;
	}
<<<<<<< HEAD
	void disassemble(std::string& retString) const
=======
	void disassemble(std::string& retString) const override
>>>>>>> upstream/master
	{
		std::string opcode = "dmac" + opMnemonicAsString(m_mnem);

		retString = opcode + " " +
					regIdAsString(m_source) + "," +
					regIdAsString(m_source2) + "," + regIdAsString(m_destination);
		// NEW // sprintf(opcode_str, "dmac(%s)", A);
	}
<<<<<<< HEAD
	void evaluate(dsp56k_core* cpustate) {}
	size_t size() const { return 1; }
	size_t accumulatorBitsModified() const { return BM_HIGH | BM_MIDDLE | BM_LOW; }
=======
	void evaluate(dsp56k_core* cpustate) override {}
	size_t size() const override { return 1; }
	size_t accumulatorBitsModified() const override { return BM_HIGH | BM_MIDDLE | BM_LOW; }
>>>>>>> upstream/master

private:
	op_mnem m_mnem;
	reg_id m_source2;
};

// DO : 0000 0000 110- --RR xxxx xxxx xxxx xxxx : A-82 /////////////////////////
class Do: public Instruction
{
public:
<<<<<<< HEAD
	Do(const Opcode* oco, const UINT16 word0, const UINT16 word1) : Instruction(oco)
=======
	Do(const Opcode* oco, const uint16_t word0, const uint16_t word1) : Instruction(oco)
>>>>>>> upstream/master
	{
		m_immediate = 0;
		m_valid = decode(word0, word1);
	}
<<<<<<< HEAD
	bool decode(const UINT16 word0, const UINT16 word1)
=======
	bool decode(const uint16_t word0, const uint16_t word1) override
>>>>>>> upstream/master
	{
		m_immediate = word1;
		decode_RR_table(BITSn(word0,0x0003), m_source);
		return true;
	}
<<<<<<< HEAD
	void disassemble(std::string& retString) const
=======
	void disassemble(std::string& retString) const override
>>>>>>> upstream/master
	{
		char temp[32];
		sprintf(temp, "*+$%x", 2 + m_immediate);
		std::string destination = temp;
		// NEW // sprintf(temp, "X:(R%d),$%02x", Rnum, pc + 2 + word1);

		sprintf(temp, "X:(%s)", regIdAsString(m_source).c_str());
		std::string source = temp;

		retString = "do " + source + "," + destination;
	}
<<<<<<< HEAD
	void evaluate(dsp56k_core* cpustate) {}
	size_t size() const { return 2; }
	size_t accumulatorBitsModified() const { return BM_HIGH | BM_MIDDLE | BM_LOW; }

private:
	UINT16 m_immediate;
=======
	void evaluate(dsp56k_core* cpustate) override {}
	size_t size() const override { return 2; }
	size_t accumulatorBitsModified() const override { return BM_HIGH | BM_MIDDLE | BM_LOW; }

private:
	uint16_t m_immediate;
>>>>>>> upstream/master
};

// DO : 0000 1110 iiii iiii xxxx xxxx xxxx xxxx : A-82 /////////////////////////
class Do_2: public Instruction
{
public:
<<<<<<< HEAD
	Do_2(const Opcode* oco, const UINT16 word0, const UINT16 word1) : Instruction(oco)
=======
	Do_2(const Opcode* oco, const uint16_t word0, const uint16_t word1) : Instruction(oco)
>>>>>>> upstream/master
	{
		m_immediate = 0;
		m_displacement = 0;
		m_valid = decode(word0, word1);
	}
<<<<<<< HEAD
	bool decode(const UINT16 word0, const UINT16 word1)
=======
	bool decode(const uint16_t word0, const uint16_t word1) override
>>>>>>> upstream/master
	{
		m_immediate = BITSn(word0,0x00ff);
		m_displacement = word1;
		return true;
	}
<<<<<<< HEAD
	void disassemble(std::string& retString) const
=======
	void disassemble(std::string& retString) const override
>>>>>>> upstream/master
	{
		char temp[32];
		sprintf(temp, "#<$%x,*+$%x", m_immediate, 2 + m_displacement);
		// NEW // sprintf(temp, "#$%02x,$%04x", BITSn(word0,0x00ff), pc + 2 + word1);
		retString = "do " + std::string(temp);
	}
<<<<<<< HEAD
	void evaluate(dsp56k_core* cpustate) {}
	size_t size() const { return 2; }
	size_t accumulatorBitsModified() const { return BM_HIGH | BM_MIDDLE | BM_LOW; }

private:
	UINT8 m_immediate;
	UINT16 m_displacement;
=======
	void evaluate(dsp56k_core* cpustate) override {}
	size_t size() const override { return 2; }
	size_t accumulatorBitsModified() const override { return BM_HIGH | BM_MIDDLE | BM_LOW; }

private:
	uint8_t m_immediate;
	uint16_t m_displacement;
>>>>>>> upstream/master
};

// DO : 0000 0100 000D DDDD xxxx xxxx xxxx xxxx : A-82 /////////////////////////
class Do_3: public Instruction
{
public:
<<<<<<< HEAD
	Do_3(const Opcode* oco, const UINT16 word0, const UINT16 word1) : Instruction(oco)
=======
	Do_3(const Opcode* oco, const uint16_t word0, const uint16_t word1) : Instruction(oco)
>>>>>>> upstream/master
	{
		m_displacement = 0;
		m_valid = decode(word0, word1);
	}
<<<<<<< HEAD
	bool decode(const UINT16 word0, const UINT16 word1)
=======
	bool decode(const uint16_t word0, const uint16_t word1) override
>>>>>>> upstream/master
	{
		m_displacement = word1;

		decode_DDDDD_table(BITSn(word0,0x001f), m_source);
		if (m_source == iSSH) return false;
		if (m_source == iINVALID) return false;
		return true;
	}
<<<<<<< HEAD
	void disassemble(std::string& retString) const
=======
	void disassemble(std::string& retString) const override
>>>>>>> upstream/master
	{
		char temp[32];
		sprintf(temp, "*+$%x", 2 + m_displacement);
		// NEW // sprintf(temp, "%s,$%04x", S1, pc + 2 + word1);
		retString = "do " + regIdAsString(m_source) + "," + std::string(temp);
	}
<<<<<<< HEAD
	void evaluate(dsp56k_core* cpustate) {}
	size_t size() const { return 2; }
	size_t accumulatorBitsModified() const { return BM_HIGH | BM_MIDDLE | BM_LOW; }

private:
	UINT16 m_displacement;
=======
	void evaluate(dsp56k_core* cpustate) override {}
	size_t size() const override { return 2; }
	size_t accumulatorBitsModified() const override { return BM_HIGH | BM_MIDDLE | BM_LOW; }

private:
	uint16_t m_displacement;
>>>>>>> upstream/master
};

// DO FOREVER : 0000 0000 0000 0010 xxxx xxxx xxxx xxxx : A-88 /////////////////
class DoForever: public Instruction
{
public:
<<<<<<< HEAD
	DoForever(const Opcode* oco, const UINT16 word0, const UINT16 word1) : Instruction(oco)
=======
	DoForever(const Opcode* oco, const uint16_t word0, const uint16_t word1) : Instruction(oco)
>>>>>>> upstream/master
	{
		m_displacement = 0;
		m_valid = decode(word0, word1);
	}
<<<<<<< HEAD
	bool decode(const UINT16 word0, const UINT16 word1)
=======
	bool decode(const uint16_t word0, const uint16_t word1) override
>>>>>>> upstream/master
	{
		m_displacement = word1;
		return true;
	}
<<<<<<< HEAD
	void disassemble(std::string& retString) const
=======
	void disassemble(std::string& retString) const override
>>>>>>> upstream/master
	{
		char temp[32];
		sprintf(temp, "*+$%x", m_displacement + 2);
		// NEW // sprintf(temp, "*+$%x", pc + word1);
		// NEW // sprintf(temp, "$%04x", pc + 2 + word1);
		retString = "do forever, " + std::string(temp);
	}
<<<<<<< HEAD
	void evaluate(dsp56k_core* cpustate) {}
	size_t size() const { return 2; }
	size_t accumulatorBitsModified() const { return BM_HIGH | BM_MIDDLE | BM_LOW; }

private:
	UINT16 m_displacement;
=======
	void evaluate(dsp56k_core* cpustate) override {}
	size_t size() const override { return 2; }
	size_t accumulatorBitsModified() const override { return BM_HIGH | BM_MIDDLE | BM_LOW; }

private:
	uint16_t m_displacement;
>>>>>>> upstream/master
};

// ENDDO : 0000 0000 0000 1001 : A-92 //////////////////////////////////////////
class Enddo: public Instruction
{
public:
<<<<<<< HEAD
	Enddo(const Opcode* oco, const UINT16 word0, const UINT16 word1) : Instruction(oco)
	{
		m_valid = decode(word0, word1);
	}
	bool decode(const UINT16 word0, const UINT16 word1)
	{
		return true;
	}
	void disassemble(std::string& retString) const
	{
		retString = "enddo";
	}
	void evaluate(dsp56k_core* cpustate) {}
	size_t size() const { return 1; }
	size_t accumulatorBitsModified() const { return BM_HIGH | BM_MIDDLE | BM_LOW; }
=======
	Enddo(const Opcode* oco, const uint16_t word0, const uint16_t word1) : Instruction(oco)
	{
		m_valid = decode(word0, word1);
	}
	bool decode(const uint16_t word0, const uint16_t word1) override
	{
		return true;
	}
	void disassemble(std::string& retString) const override
	{
		retString = "enddo";
	}
	void evaluate(dsp56k_core* cpustate) override {}
	size_t size() const override { return 1; }
	size_t accumulatorBitsModified() const override { return BM_HIGH | BM_MIDDLE | BM_LOW; }
>>>>>>> upstream/master
};

// EOR : .... .... 0011 F1JJ : A-94 ////////////////////////////////////////////
class Eor: public Instruction
{
public:
<<<<<<< HEAD
	Eor(const Opcode* oco, const UINT16 word0, const UINT16 word1) : Instruction(oco)
	{
		m_valid = decode(word0, word1);
	}
	bool decode(const UINT16 word0, const UINT16 word1)
=======
	Eor(const Opcode* oco, const uint16_t word0, const uint16_t word1) : Instruction(oco)
	{
		m_valid = decode(word0, word1);
	}
	bool decode(const uint16_t word0, const uint16_t word1) override
>>>>>>> upstream/master
	{
		decode_JJF_table(BITSn(word0,0x03),BITSn(word0,0x08),
							m_source, m_destination);
		return true;
	}
<<<<<<< HEAD
	void disassemble(std::string& retString) const
	{
		retString = "eor " + regIdAsString(m_source) + "," + regIdAsString(m_destination);
	}
	void evaluate(dsp56k_core* cpustate) {}
	size_t size() const { return 1; }
	size_t accumulatorBitsModified() const { return BM_HIGH | BM_MIDDLE; }
=======
	void disassemble(std::string& retString) const override
	{
		retString = "eor " + regIdAsString(m_source) + "," + regIdAsString(m_destination);
	}
	void evaluate(dsp56k_core* cpustate) override {}
	size_t size() const override { return 1; }
	size_t accumulatorBitsModified() const override { return BM_HIGH | BM_MIDDLE; }
>>>>>>> upstream/master
};

// EXT : 0001 0101 0101 F010 : A-96 ////////////////////////////////////////////
class Ext: public Instruction
{
public:
<<<<<<< HEAD
	Ext(const Opcode* oco, const UINT16 word0, const UINT16 word1) : Instruction(oco)
	{
		m_valid = decode(word0, word1);
	}
	bool decode(const UINT16 word0, const UINT16 word1)
=======
	Ext(const Opcode* oco, const uint16_t word0, const uint16_t word1) : Instruction(oco)
	{
		m_valid = decode(word0, word1);
	}
	bool decode(const uint16_t word0, const uint16_t word1) override
>>>>>>> upstream/master
	{
		decode_F_table(BITSn(word0,0x0008), m_destination);
		return true;
	}
<<<<<<< HEAD
	void disassemble(std::string& retString) const
	{
		retString = "ext " + regIdAsString(m_destination);
	}
	void evaluate(dsp56k_core* cpustate) {}
	size_t size() const { return 1; }
	size_t accumulatorBitsModified() const { return BM_HIGH | BM_MIDDLE | BM_LOW; }
=======
	void disassemble(std::string& retString) const override
	{
		retString = "ext " + regIdAsString(m_destination);
	}
	void evaluate(dsp56k_core* cpustate) override {}
	size_t size() const override { return 1; }
	size_t accumulatorBitsModified() const override { return BM_HIGH | BM_MIDDLE | BM_LOW; }
>>>>>>> upstream/master
};

// ILLEGAL : 0000 0000 0000 1111 : A-98 ////////////////////////////////////////
class Illegal: public Instruction
{
public:
<<<<<<< HEAD
	Illegal(const Opcode* oco, const UINT16 word0, const UINT16 word1) : Instruction(oco)
	{
		m_valid = decode(word0, word1);
	}
	bool decode(const UINT16 word0, const UINT16 word1)
	{
		return true;
	}
	void disassemble(std::string& retString) const
	{
		retString = "illegal";
	}
	void evaluate(dsp56k_core* cpustate) {}
	size_t size() const { return 1; }
	size_t accumulatorBitsModified() const { return BM_HIGH | BM_MIDDLE | BM_LOW; }
=======
	Illegal(const Opcode* oco, const uint16_t word0, const uint16_t word1) : Instruction(oco)
	{
		m_valid = decode(word0, word1);
	}
	bool decode(const uint16_t word0, const uint16_t word1) override
	{
		return true;
	}
	void disassemble(std::string& retString) const override
	{
		retString = "illegal";
	}
	void evaluate(dsp56k_core* cpustate) override {}
	size_t size() const override { return 1; }
	size_t accumulatorBitsModified() const override { return BM_HIGH | BM_MIDDLE | BM_LOW; }
>>>>>>> upstream/master
};

// IMAC : 0001 0101 1010 FQQQ : A-100 //////////////////////////////////////////
class Imac: public Instruction
{
public:
<<<<<<< HEAD
	Imac(const Opcode* oco, const UINT16 word0, const UINT16 word1) : Instruction(oco)
=======
	Imac(const Opcode* oco, const uint16_t word0, const uint16_t word1) : Instruction(oco)
>>>>>>> upstream/master
	{
		m_source2 = iINVALID;
		m_valid = decode(word0, word1);
	}
<<<<<<< HEAD
	bool decode(const UINT16 word0, const UINT16 word1)
=======
	bool decode(const uint16_t word0, const uint16_t word1) override
>>>>>>> upstream/master
	{
		decode_QQQF_table(BITSn(word0,0x0007), BITSn(word0,0x0008),
							m_source, m_source2, m_destination);
		return true;
	}
<<<<<<< HEAD
	void disassemble(std::string& retString) const
=======
	void disassemble(std::string& retString) const override
>>>>>>> upstream/master
	{
		retString = "imac " +
					regIdAsString(m_source) + "," +
					regIdAsString(m_source2) + "," + regIdAsString(m_destination);
	}
<<<<<<< HEAD
	void evaluate(dsp56k_core* cpustate) {}
	size_t size() const { return 1; }
	size_t accumulatorBitsModified() const { return BM_HIGH | BM_MIDDLE | BM_LOW; }
=======
	void evaluate(dsp56k_core* cpustate) override {}
	size_t size() const override { return 1; }
	size_t accumulatorBitsModified() const override { return BM_HIGH | BM_MIDDLE | BM_LOW; }
>>>>>>> upstream/master

private:
	reg_id m_source2;
};

// IMPY : 0001 0101 1000 FQQQ : A-102 //////////////////////////////////////////
class Impy: public Instruction
{
public:
<<<<<<< HEAD
	Impy(const Opcode* oco, const UINT16 word0, const UINT16 word1) : Instruction(oco)
=======
	Impy(const Opcode* oco, const uint16_t word0, const uint16_t word1) : Instruction(oco)
>>>>>>> upstream/master
	{
		m_source2 = iINVALID;
		m_valid = decode(word0, word1);
	}
<<<<<<< HEAD
	bool decode(const UINT16 word0, const UINT16 word1)
=======
	bool decode(const uint16_t word0, const uint16_t word1) override
>>>>>>> upstream/master
	{
		decode_QQQF_table(BITSn(word0,0x0007), BITSn(word0,0x0008),
							m_source, m_source2, m_destination);
		return true;
	}
<<<<<<< HEAD
	void disassemble(std::string& retString) const
=======
	void disassemble(std::string& retString) const override
>>>>>>> upstream/master
	{
		retString = "impy " +
					regIdAsString(m_source) + "," +
					regIdAsString(m_source2) + "," + regIdAsString(m_destination);
	}
<<<<<<< HEAD
	void evaluate(dsp56k_core* cpustate) {}
	size_t size() const { return 1; }
	size_t accumulatorBitsModified() const { return BM_HIGH | BM_MIDDLE | BM_LOW; }
=======
	void evaluate(dsp56k_core* cpustate) override {}
	size_t size() const override { return 1; }
	size_t accumulatorBitsModified() const override { return BM_HIGH | BM_MIDDLE | BM_LOW; }
>>>>>>> upstream/master

private:
	reg_id m_source2;
};

// INC : .... .... 0010 F010 : A-104 ///////////////////////////////////////////
class Inc: public Instruction
{
public:
<<<<<<< HEAD
	Inc(const Opcode* oco, const UINT16 word0, const UINT16 word1) : Instruction(oco)
	{
		m_valid = decode(word0, word1);
	}
	bool decode(const UINT16 word0, const UINT16 word1)
=======
	Inc(const Opcode* oco, const uint16_t word0, const uint16_t word1) : Instruction(oco)
	{
		m_valid = decode(word0, word1);
	}
	bool decode(const uint16_t word0, const uint16_t word1) override
>>>>>>> upstream/master
	{
		decode_F_table(BITSn(word0,0x08), m_destination);
		return true;
	}
<<<<<<< HEAD
	void disassemble(std::string& retString) const
	{
		retString = "inc " + regIdAsString(m_destination);
	}
	void evaluate(dsp56k_core* cpustate) {}
	size_t size() const { return 1; }
	size_t accumulatorBitsModified() const { return BM_HIGH | BM_MIDDLE | BM_LOW; }
=======
	void disassemble(std::string& retString) const override
	{
		retString = "inc " + regIdAsString(m_destination);
	}
	void evaluate(dsp56k_core* cpustate) override {}
	size_t size() const override { return 1; }
	size_t accumulatorBitsModified() const override { return BM_HIGH | BM_MIDDLE | BM_LOW; }
>>>>>>> upstream/master
};

// INC24 : .... .... 0010 F011 : A-106 /////////////////////////////////////////
class Inc24: public Instruction
{
public:
<<<<<<< HEAD
	Inc24(const Opcode* oco, const UINT16 word0, const UINT16 word1) : Instruction(oco)
	{
		m_valid = decode(word0, word1);
	}
	bool decode(const UINT16 word0, const UINT16 word1)
=======
	Inc24(const Opcode* oco, const uint16_t word0, const uint16_t word1) : Instruction(oco)
	{
		m_valid = decode(word0, word1);
	}
	bool decode(const uint16_t word0, const uint16_t word1) override
>>>>>>> upstream/master
	{
		decode_F_table(BITSn(word0,0x08), m_destination);
		return true;
	}
<<<<<<< HEAD
	void disassemble(std::string& retString) const
	{
		retString = "inc24 " + regIdAsString(m_destination);
	}
	void evaluate(dsp56k_core* cpustate) {}
	size_t size() const { return 1; }
	size_t accumulatorBitsModified() const { return BM_HIGH | BM_MIDDLE; }
=======
	void disassemble(std::string& retString) const override
	{
		retString = "inc24 " + regIdAsString(m_destination);
	}
	void evaluate(dsp56k_core* cpustate) override {}
	size_t size() const override { return 1; }
	size_t accumulatorBitsModified() const override { return BM_HIGH | BM_MIDDLE; }
>>>>>>> upstream/master
};

// Jcc : 0000 0110 --11 cccc xxxx xxxx xxxx xxxx : A-108 ///////////////////////
class Jcc: public Instruction
{
public:
<<<<<<< HEAD
	Jcc(const Opcode* oco, const UINT16 word0, const UINT16 word1) : Instruction(oco)
=======
	Jcc(const Opcode* oco, const uint16_t word0, const uint16_t word1) : Instruction(oco)
>>>>>>> upstream/master
	{
		m_mnem = oINVALID;
		m_displacement = 0;
		m_valid = decode(word0, word1);
	}
<<<<<<< HEAD
	bool decode(const UINT16 word0, const UINT16 word1)
=======
	bool decode(const uint16_t word0, const uint16_t word1) override
>>>>>>> upstream/master
	{
		m_displacement = word1;
		decode_cccc_table(BITSn(word0,0x000f), m_mnem);
		return true;
	}
<<<<<<< HEAD
	void disassemble(std::string& retString) const
=======
	void disassemble(std::string& retString) const override
>>>>>>> upstream/master
	{
		std::string opcode = "j" + opMnemonicAsString(m_mnem);
		// NEW // sprintf(opcode_str, "j.%s", M);

		char temp[32];
		sprintf(temp, ">$%x", m_displacement);
		// NEW // sprintf(temp, "$%04x", word1);
		retString = opcode + " " + std::string(temp);
	}
<<<<<<< HEAD
	void evaluate(dsp56k_core* cpustate) {}
	size_t size() const { return 2; }
	size_t accumulatorBitsModified() const { return BM_HIGH | BM_MIDDLE | BM_LOW; }

private:
	op_mnem m_mnem;
	UINT16 m_displacement;
=======
	void evaluate(dsp56k_core* cpustate) override {}
	size_t size() const override { return 2; }
	size_t accumulatorBitsModified() const override { return BM_HIGH | BM_MIDDLE | BM_LOW; }

private:
	op_mnem m_mnem;
	uint16_t m_displacement;
>>>>>>> upstream/master
};

// Jcc : 0000 0110 RR10 cccc : A-108 ///////////////////////////////////////////
class Jcc_2: public Instruction
{
public:
<<<<<<< HEAD
	Jcc_2(const Opcode* oco, const UINT16 word0, const UINT16 word1) : Instruction(oco)
=======
	Jcc_2(const Opcode* oco, const uint16_t word0, const uint16_t word1) : Instruction(oco)
>>>>>>> upstream/master
	{
		m_mnem = oINVALID;
		m_valid = decode(word0, word1);
	}
<<<<<<< HEAD
	bool decode(const UINT16 word0, const UINT16 word1)
=======
	bool decode(const uint16_t word0, const uint16_t word1) override
>>>>>>> upstream/master
	{
		decode_RR_table(BITSn(word0,0x00c0), m_destination);
		decode_cccc_table(BITSn(word0,0x000f), m_mnem);
		return true;
	}
<<<<<<< HEAD
	void disassemble(std::string& retString) const
=======
	void disassemble(std::string& retString) const override
>>>>>>> upstream/master
	{
		std::string opcode = "j" + opMnemonicAsString(m_mnem);
		retString = opcode + " " + regIdAsString(m_destination);
		// NEW // sprintf(opcode_str, "j.%s", M);
	}
<<<<<<< HEAD
	void evaluate(dsp56k_core* cpustate) {}
	size_t size() const { return 1; }
	size_t accumulatorBitsModified() const { return BM_HIGH | BM_MIDDLE | BM_LOW; }
=======
	void evaluate(dsp56k_core* cpustate) override {}
	size_t size() const override { return 1; }
	size_t accumulatorBitsModified() const override { return BM_HIGH | BM_MIDDLE | BM_LOW; }
>>>>>>> upstream/master

private:
	op_mnem m_mnem;
};

// JMP : 0000 0001 0011 01-- xxxx xxxx xxxx xxxx : A-110 ///////////////////////
class Jmp: public Instruction
{
public:
<<<<<<< HEAD
	Jmp(const Opcode* oco, const UINT16 word0, const UINT16 word1) : Instruction(oco)
=======
	Jmp(const Opcode* oco, const uint16_t word0, const uint16_t word1) : Instruction(oco)
>>>>>>> upstream/master
	{
		m_displacement = 0;
		m_valid = decode(word0, word1);
	}
<<<<<<< HEAD
	bool decode(const UINT16 word0, const UINT16 word1)
=======
	bool decode(const uint16_t word0, const uint16_t word1) override
>>>>>>> upstream/master
	{
		m_displacement = word1;
		return true;
	}
<<<<<<< HEAD
	void disassemble(std::string& retString) const
=======
	void disassemble(std::string& retString) const override
>>>>>>> upstream/master
	{
		char temp[32];
		sprintf(temp, ">$%x", m_displacement);
		// NEW // sprintf(temp, "$%04x", word1);
		retString = "jmp " + std::string(temp);
	}
<<<<<<< HEAD
	void evaluate(dsp56k_core* cpustate)
	{
		cpustate->ppc = PC;
=======
	void evaluate(dsp56k_core* cpustate) override
	{
>>>>>>> upstream/master
		PC = m_displacement;

		/* S L E U N Z V C */
		/* - - - - - - - - */
	}
<<<<<<< HEAD
	size_t size() const { return 2; }
	size_t evalSize() const { return 0; }
	size_t accumulatorBitsModified() const { return BM_HIGH | BM_MIDDLE | BM_LOW; }

private:
	UINT16 m_displacement;
=======
	size_t size() const override { return 2; }
	size_t evalSize() const override { return 0; }
	size_t accumulatorBitsModified() const override { return BM_HIGH | BM_MIDDLE | BM_LOW; }

private:
	uint16_t m_displacement;
>>>>>>> upstream/master
};

// JMP : 0000 0001 0010 01RR : A-110 ///////////////////////////////////////////
class Jmp_2: public Instruction
{
public:
<<<<<<< HEAD
	Jmp_2(const Opcode* oco, const UINT16 word0, const UINT16 word1) : Instruction(oco)
	{
		m_valid = decode(word0, word1);
	}
	bool decode(const UINT16 word0, const UINT16 word1)
=======
	Jmp_2(const Opcode* oco, const uint16_t word0, const uint16_t word1) : Instruction(oco)
	{
		m_valid = decode(word0, word1);
	}
	bool decode(const uint16_t word0, const uint16_t word1) override
>>>>>>> upstream/master
	{
		decode_RR_table(BITSn(word0,0x0003), m_destination);
		return true;
	}
<<<<<<< HEAD
	void disassemble(std::string& retString) const
	{
		retString = "jmp " + regIdAsString(m_destination);
	}
	void evaluate(dsp56k_core* cpustate)
	{
		cpustate->ppc = PC;
=======
	void disassemble(std::string& retString) const override
	{
		retString = "jmp " + regIdAsString(m_destination);
	}
	void evaluate(dsp56k_core* cpustate) override
	{
>>>>>>> upstream/master
		PC = regValue16(cpustate, m_destination);

		/* S L E U N Z V C */
		/* - - - - - - - - */
	}
<<<<<<< HEAD
	size_t size() const { return 1; }
	size_t evalSize() const { return 0; }
	size_t accumulatorBitsModified() const { return BM_HIGH | BM_MIDDLE | BM_LOW; }
};

//static Jmp_2* JMP2 = new Jmp_2(NULL, 0x0000, 0x0000);
=======
	size_t size() const override { return 1; }
	size_t evalSize() const override { return 0; }
	size_t accumulatorBitsModified() const override { return BM_HIGH | BM_MIDDLE | BM_LOW; }
};

//static Jmp_2* JMP2 = new Jmp_2(nullptr, 0x0000, 0x0000);
>>>>>>> upstream/master

// JScc : 0000 0110 --01 cccc xxxx xxxx xxxx xxxx : A-112 //////////////////////
class Jscc: public Instruction
{
public:
<<<<<<< HEAD
	Jscc(const Opcode* oco, const UINT16 word0, const UINT16 word1) : Instruction(oco)
=======
	Jscc(const Opcode* oco, const uint16_t word0, const uint16_t word1) : Instruction(oco)
>>>>>>> upstream/master
	{
		m_mnem = oINVALID;
		m_displacement = 0;
		m_valid = decode(word0, word1);
	}
<<<<<<< HEAD
	bool decode(const UINT16 word0, const UINT16 word1)
=======
	bool decode(const uint16_t word0, const uint16_t word1) override
>>>>>>> upstream/master
	{
		m_displacement = word1;
		decode_cccc_table(BITSn(word0,0x000f), m_mnem);
		return true;
	}
<<<<<<< HEAD
	void disassemble(std::string& retString) const
=======
	void disassemble(std::string& retString) const override
>>>>>>> upstream/master
	{
		std::string opcode = "js" + opMnemonicAsString(m_mnem);
		// NEW // sprintf(opcode_str, "js.%s", M);

		char temp[32];
		sprintf(temp, ">$%x", m_displacement);
		// NEW // sprintf(temp, "$%04x", word1);
		retString = opcode + " " + std::string(temp);
	}
<<<<<<< HEAD
	void evaluate(dsp56k_core* cpustate) {}
	size_t size() const { return 2; }
	size_t accumulatorBitsModified() const { return BM_HIGH | BM_MIDDLE | BM_LOW; }
	size_t flags() const { return DASMFLAG_STEP_OVER; }

private:
	op_mnem m_mnem;
	UINT16 m_displacement;
=======
	void evaluate(dsp56k_core* cpustate) override {}
	size_t size() const override { return 2; }
	size_t accumulatorBitsModified() const override { return BM_HIGH | BM_MIDDLE | BM_LOW; }
	size_t flags() const override { return DASMFLAG_STEP_OVER; }

private:
	op_mnem m_mnem;
	uint16_t m_displacement;
>>>>>>> upstream/master
};

// JScc : 0000 0110 RR00 cccc : A-112 //////////////////////////////////////////
class Jscc_2: public Instruction
{
public:
<<<<<<< HEAD
	Jscc_2(const Opcode* oco, const UINT16 word0, const UINT16 word1) : Instruction(oco)
=======
	Jscc_2(const Opcode* oco, const uint16_t word0, const uint16_t word1) : Instruction(oco)
>>>>>>> upstream/master
	{
		m_mnem = oINVALID;
		m_valid = decode(word0, word1);
	}
<<<<<<< HEAD
	bool decode(const UINT16 word0, const UINT16 word1)
=======
	bool decode(const uint16_t word0, const uint16_t word1) override
>>>>>>> upstream/master
	{
		decode_RR_table(BITSn(word0,0x00c0), m_destination);
		decode_cccc_table(BITSn(word0,0x000f), m_mnem);
		return true;
	}
<<<<<<< HEAD
	void disassemble(std::string& retString) const
=======
	void disassemble(std::string& retString) const override
>>>>>>> upstream/master
	{
		std::string opcode = "js" + opMnemonicAsString(m_mnem);
		retString = opcode + " " + regIdAsString(m_destination);
		// NEW // sprintf(opcode_str, "js.%s", M);
	}
<<<<<<< HEAD
	void evaluate(dsp56k_core* cpustate) {}
	size_t size() const { return 1; }
	size_t accumulatorBitsModified() const { return BM_HIGH | BM_MIDDLE | BM_LOW; }
	size_t flags() const { return DASMFLAG_STEP_OVER; }
=======
	void evaluate(dsp56k_core* cpustate) override {}
	size_t size() const override { return 1; }
	size_t accumulatorBitsModified() const override { return BM_HIGH | BM_MIDDLE | BM_LOW; }
	size_t flags() const override { return DASMFLAG_STEP_OVER; }
>>>>>>> upstream/master

private:
	op_mnem m_mnem;
};

// JSR : 0000 0001 0011 00-- xxxx xxxx xxxx xxxx : A-114 ///////////////////////
class Jsr: public Instruction
{
public:
<<<<<<< HEAD
	Jsr(const Opcode* oco, const UINT16 word0, const UINT16 word1) : Instruction(oco)
=======
	Jsr(const Opcode* oco, const uint16_t word0, const uint16_t word1) : Instruction(oco)
>>>>>>> upstream/master
	{
		m_displacement = 0;
		m_valid = decode(word0, word1);
	}
<<<<<<< HEAD
	bool decode(const UINT16 word0, const UINT16 word1)
=======
	bool decode(const uint16_t word0, const uint16_t word1) override
>>>>>>> upstream/master
	{
		m_displacement = word1;
		return true;
	}
<<<<<<< HEAD
	void disassemble(std::string& retString) const
=======
	void disassemble(std::string& retString) const override
>>>>>>> upstream/master
	{
		char temp[32];
		sprintf(temp, ">$%x", m_displacement);
		// NEW // sprintf(temp, "$%04x", word1);
		retString = "jsr " + std::string(temp);
	}
<<<<<<< HEAD
	void evaluate(dsp56k_core* cpustate) {}
	size_t size() const { return 2; }
	size_t accumulatorBitsModified() const { return BM_HIGH | BM_MIDDLE | BM_LOW; }
	size_t flags() const { return DASMFLAG_STEP_OVER; }

private:
	UINT16 m_displacement;
=======
	void evaluate(dsp56k_core* cpustate) override {}
	size_t size() const override { return 2; }
	size_t accumulatorBitsModified() const override { return BM_HIGH | BM_MIDDLE | BM_LOW; }
	size_t flags() const override { return DASMFLAG_STEP_OVER; }

private:
	uint16_t m_displacement;
>>>>>>> upstream/master
};

// JSR : 0000 1010 AAAA AAAA : A-114 ///////////////////////////////////////////
class Jsr_2: public Instruction
{
public:
<<<<<<< HEAD
	Jsr_2(const Opcode* oco, const UINT16 word0, const UINT16 word1) : Instruction(oco)
=======
	Jsr_2(const Opcode* oco, const uint16_t word0, const uint16_t word1) : Instruction(oco)
>>>>>>> upstream/master
	{
		m_bAddr = 0;
		m_valid = decode(word0, word1);
	}
<<<<<<< HEAD
	bool decode(const UINT16 word0, const UINT16 word1)
=======
	bool decode(const uint16_t word0, const uint16_t word1) override
>>>>>>> upstream/master
	{
		m_bAddr = BITSn(word0,0x00ff);
		return true;
	}
<<<<<<< HEAD
	void disassemble(std::string& retString) const
=======
	void disassemble(std::string& retString) const override
>>>>>>> upstream/master
	{
		char temp[32];
		sprintf(temp, "<$%x", m_bAddr);
		// NEW // sprintf(temp, "#$%02x", BITSn(word0,0x00ff));
		retString = "jsr " + std::string(temp);
	}
<<<<<<< HEAD
	void evaluate(dsp56k_core* cpustate) {}
	size_t size() const { return 1; }
	size_t accumulatorBitsModified() const { return BM_HIGH | BM_MIDDLE | BM_LOW; }
	size_t flags() const { return DASMFLAG_STEP_OVER; }

private:
	UINT8 m_bAddr;
=======
	void evaluate(dsp56k_core* cpustate) override {}
	size_t size() const override { return 1; }
	size_t accumulatorBitsModified() const override { return BM_HIGH | BM_MIDDLE | BM_LOW; }
	size_t flags() const override { return DASMFLAG_STEP_OVER; }

private:
	uint8_t m_bAddr;
>>>>>>> upstream/master
};

// JSR : 0000 0001 0010 00RR : A-114 ///////////////////////////////////////////
class Jsr_3: public Instruction
{
public:
<<<<<<< HEAD
	Jsr_3(const Opcode* oco, const UINT16 word0, const UINT16 word1) : Instruction(oco)
	{
		m_valid = decode(word0, word1);
	}
	bool decode(const UINT16 word0, const UINT16 word1)
=======
	Jsr_3(const Opcode* oco, const uint16_t word0, const uint16_t word1) : Instruction(oco)
	{
		m_valid = decode(word0, word1);
	}
	bool decode(const uint16_t word0, const uint16_t word1) override
>>>>>>> upstream/master
	{
		decode_RR_table(BITSn(word0,0x0003), m_destination);
		return true;
	}
<<<<<<< HEAD
	void disassemble(std::string& retString) const
	{
		retString = "jsr " + regIdAsString(m_destination);
	}
	void evaluate(dsp56k_core* cpustate) {}
	size_t size() const { return 1; }
	size_t accumulatorBitsModified() const { return BM_HIGH | BM_MIDDLE | BM_LOW; }
	size_t flags() const { return DASMFLAG_STEP_OVER; }
=======
	void disassemble(std::string& retString) const override
	{
		retString = "jsr " + regIdAsString(m_destination);
	}
	void evaluate(dsp56k_core* cpustate) override {}
	size_t size() const override { return 1; }
	size_t accumulatorBitsModified() const override { return BM_HIGH | BM_MIDDLE | BM_LOW; }
	size_t flags() const override { return DASMFLAG_STEP_OVER; }
>>>>>>> upstream/master
};

// LEA : 0000 0001 11TT MMRR : A-116 ///////////////////////////////////////////
class Lea: public Instruction
{
public:
<<<<<<< HEAD
	Lea(const Opcode* oco, const UINT16 word0, const UINT16 word1) : Instruction(oco)
=======
	Lea(const Opcode* oco, const uint16_t word0, const uint16_t word1) : Instruction(oco)
>>>>>>> upstream/master
	{
		m_ea = "";
		m_valid = decode(word0, word1);
	}
<<<<<<< HEAD
	bool decode(const UINT16 word0, const UINT16 word1)
=======
	bool decode(const uint16_t word0, const uint16_t word1) override
>>>>>>> upstream/master
	{
		if ((word0 & 0x000c) == 0) return false;  // NEW TODO //

		decode_TT_table(BITSn(word0,0x0030), m_destination);

<<<<<<< HEAD
		INT8 rNum = BITSn(word0,0x0003);
=======
		int8_t rNum = BITSn(word0,0x0003);
>>>>>>> upstream/master
		assemble_ea_from_MM_table(BITSn(word0,0x000c), rNum, m_ea);

		return true;
	}
<<<<<<< HEAD
	void disassemble(std::string& retString) const
=======
	void disassemble(std::string& retString) const override
>>>>>>> upstream/master
	{
		// HACK
		retString = "lea " + m_ea + "," + regIdAsString(m_destination);
	}
<<<<<<< HEAD
	void evaluate(dsp56k_core* cpustate) {}
	size_t size() const { return 1; }
	size_t accumulatorBitsModified() const { return BM_HIGH | BM_MIDDLE | BM_LOW; }
=======
	void evaluate(dsp56k_core* cpustate) override {}
	size_t size() const override { return 1; }
	size_t accumulatorBitsModified() const override { return BM_HIGH | BM_MIDDLE | BM_LOW; }
>>>>>>> upstream/master

private:
	std::string m_ea;
};

// LEA : 0000 0001 10NN MMRR : A-116 ///////////////////////////////////////////
class Lea_2: public Instruction
{
public:
<<<<<<< HEAD
	Lea_2(const Opcode* oco, const UINT16 word0, const UINT16 word1) : Instruction(oco)
	{
		m_valid = decode(word0, word1);
	}
	bool decode(const UINT16 word0, const UINT16 word1)
=======
	Lea_2(const Opcode* oco, const uint16_t word0, const uint16_t word1) : Instruction(oco)
	{
		m_valid = decode(word0, word1);
	}
	bool decode(const uint16_t word0, const uint16_t word1) override
>>>>>>> upstream/master
	{
		if ((word0 & 0x000c) == 0) return false;  // NEW TODO //

		decode_NN_table(BITSn(word0,0x0030), m_destination);

<<<<<<< HEAD
		INT8 rNum = BITSn(word0,0x0003);
=======
		int8_t rNum = BITSn(word0,0x0003);
>>>>>>> upstream/master
		assemble_ea_from_MM_table(BITSn(word0,0x000c), rNum, m_ea);

		return true;
	}
<<<<<<< HEAD
	void disassemble(std::string& retString) const
=======
	void disassemble(std::string& retString) const override
>>>>>>> upstream/master
	{
		// HACK
		retString = "lea " + m_ea + "," + regIdAsString(m_destination);
	}
<<<<<<< HEAD
	void evaluate(dsp56k_core* cpustate) {}
	size_t size() const { return 1; }
	size_t accumulatorBitsModified() const { return BM_HIGH | BM_MIDDLE | BM_LOW; }
=======
	void evaluate(dsp56k_core* cpustate) override {}
	size_t size() const override { return 1; }
	size_t accumulatorBitsModified() const override { return BM_HIGH | BM_MIDDLE | BM_LOW; }
>>>>>>> upstream/master

private:
	std::string m_ea;
};

// LSL : .... .... 0011 F011 : A-118 ///////////////////////////////////////////
class Lsl: public Instruction
{
public:
<<<<<<< HEAD
	Lsl(const Opcode* oco, const UINT16 word0, const UINT16 word1) : Instruction(oco)
	{
		m_valid = decode(word0, word1);
	}
	bool decode(const UINT16 word0, const UINT16 word1)
=======
	Lsl(const Opcode* oco, const uint16_t word0, const uint16_t word1) : Instruction(oco)
	{
		m_valid = decode(word0, word1);
	}
	bool decode(const uint16_t word0, const uint16_t word1) override
>>>>>>> upstream/master
	{
		decode_F_table(BITSn(word0,0x08), m_destination);
		return true;
	}
<<<<<<< HEAD
	void disassemble(std::string& retString) const
	{
		retString = "lsl " + regIdAsString(m_destination);
	}
	void evaluate(dsp56k_core* cpustate) {}
	size_t size() const { return 1; }
	size_t accumulatorBitsModified() const { return BM_HIGH | BM_MIDDLE; }
=======
	void disassemble(std::string& retString) const override
	{
		retString = "lsl " + regIdAsString(m_destination);
	}
	void evaluate(dsp56k_core* cpustate) override {}
	size_t size() const override { return 1; }
	size_t accumulatorBitsModified() const override { return BM_HIGH | BM_MIDDLE; }
>>>>>>> upstream/master
};

// LSR : .... .... 0011 F010 : A-120 ///////////////////////////////////////////
class Lsr: public Instruction
{
public:
<<<<<<< HEAD
	Lsr(const Opcode* oco, const UINT16 word0, const UINT16 word1) : Instruction(oco)
	{
		m_valid = decode(word0, word1);
	}
	bool decode(const UINT16 word0, const UINT16 word1)
=======
	Lsr(const Opcode* oco, const uint16_t word0, const uint16_t word1) : Instruction(oco)
	{
		m_valid = decode(word0, word1);
	}
	bool decode(const uint16_t word0, const uint16_t word1) override
>>>>>>> upstream/master
	{
		decode_F_table(BITSn(word0,0x08), m_destination);
		return true;
	}
<<<<<<< HEAD
	void disassemble(std::string& retString) const
	{
		retString = "lsr " + regIdAsString(m_destination);
	}
	void evaluate(dsp56k_core* cpustate) {}
	size_t size() const { return 1; }
	size_t accumulatorBitsModified() const { return BM_HIGH | BM_MIDDLE; }
=======
	void disassemble(std::string& retString) const override
	{
		retString = "lsr " + regIdAsString(m_destination);
	}
	void evaluate(dsp56k_core* cpustate) override {}
	size_t size() const override { return 1; }
	size_t accumulatorBitsModified() const override { return BM_HIGH | BM_MIDDLE; }
>>>>>>> upstream/master
};

// MAC : .... .... 1k10 FQQQ : A-122 ///////////////////////////////////////////
class Mac: public Instruction
{
public:
<<<<<<< HEAD
	Mac(const Opcode* oco, const UINT16 word0, const UINT16 word1) : Instruction(oco)
=======
	Mac(const Opcode* oco, const uint16_t word0, const uint16_t word1) : Instruction(oco)
>>>>>>> upstream/master
	{
		m_sign = "";
		m_source2 = iINVALID;
		m_valid = decode(word0, word1);
	}
<<<<<<< HEAD
	bool decode(const UINT16 word0, const UINT16 word1)
=======
	bool decode(const uint16_t word0, const uint16_t word1) override
>>>>>>> upstream/master
	{
		decode_QQQF_table(BITSn(word0,0x07), BITSn(word0,0x08),
							m_source, m_source2, m_destination);

		decode_kSign_table(BITSn(word0,0x40), m_sign);
		return true;
	}
<<<<<<< HEAD
	void disassemble(std::string& retString) const
=======
	void disassemble(std::string& retString) const override
>>>>>>> upstream/master
	{
		std::string ts = m_sign;
		if (ts.compare("-") != 0) ts = "";
		retString = "mac " +
					ts +
					regIdAsString(m_source) + "," +
					regIdAsString(m_source2) + "," + regIdAsString(m_destination);
	}
<<<<<<< HEAD
	void evaluate(dsp56k_core* cpustate) {}
	size_t size() const { return 1; }
	size_t accumulatorBitsModified() const { return BM_HIGH | BM_MIDDLE | BM_LOW; }
=======
	void evaluate(dsp56k_core* cpustate) override {}
	size_t size() const override { return 1; }
	size_t accumulatorBitsModified() const override { return BM_HIGH | BM_MIDDLE | BM_LOW; }
>>>>>>> upstream/master

private:
	reg_id m_source2;
	std::string m_sign;
};

// MAC : 011m mKKK 1xx0 F1QQ : A-122 ///////////////////////////////////////////
class Mac_2: public Instruction
{
public:
<<<<<<< HEAD
	Mac_2(const Opcode* oco, const UINT16 word0, const UINT16 word1) : Instruction(oco)
=======
	Mac_2(const Opcode* oco, const uint16_t word0, const uint16_t word1) : Instruction(oco)
>>>>>>> upstream/master
	{
		m_source2 = iINVALID;
		m_valid = decode(word0, word1);
	}
<<<<<<< HEAD
	bool decode(const UINT16 word0, const UINT16 word1)
=======
	bool decode(const uint16_t word0, const uint16_t word1) override
>>>>>>> upstream/master
	{
		decode_QQF_table(BITSn(word0,0x03), BITSn(word0,0x08),
							m_source, m_source2, m_destination);
		return true;
	}
<<<<<<< HEAD
	void disassemble(std::string& retString) const
=======
	void disassemble(std::string& retString) const override
>>>>>>> upstream/master
	{
		retString = "mac " +
					regIdAsString(m_source) + "," +
					regIdAsString(m_source2) + "," + regIdAsString(m_destination);
	}
<<<<<<< HEAD
	void evaluate(dsp56k_core* cpustate) {}
	size_t size() const { return 1; }
	size_t accumulatorBitsModified() const { return BM_HIGH | BM_MIDDLE | BM_LOW; }
=======
	void evaluate(dsp56k_core* cpustate) override {}
	size_t size() const override { return 1; }
	size_t accumulatorBitsModified() const override { return BM_HIGH | BM_MIDDLE | BM_LOW; }
>>>>>>> upstream/master

private:
	reg_id m_source2;
};

// MAC : 0001 0111 RRDD FQQQ : A-122 ///////////////////////////////////////////
class Mac_3: public Instruction
{
public:
<<<<<<< HEAD
	Mac_3(const Opcode* oco, const UINT16 word0, const UINT16 word1) : Instruction(oco)
=======
	Mac_3(const Opcode* oco, const uint16_t word0, const uint16_t word1) : Instruction(oco)
>>>>>>> upstream/master
	{
		m_source2 = iINVALID;
		m_valid = decode(word0, word1);
	}
<<<<<<< HEAD
	bool decode(const UINT16 word0, const UINT16 word1)
=======
	bool decode(const uint16_t word0, const uint16_t word1) override
>>>>>>> upstream/master
	{
		decode_QQQF_table(BITSn(word0,0x0007), BITSn(word0,0x0008),
							m_source, m_source2, m_destination);
		return true;
	}
<<<<<<< HEAD
	void disassemble(std::string& retString) const
=======
	void disassemble(std::string& retString) const override
>>>>>>> upstream/master
	{
		retString = "mac " +
					regIdAsString(m_source) + "," +
					regIdAsString(m_source2) + "," + regIdAsString(m_destination);
	}
<<<<<<< HEAD
	void evaluate(dsp56k_core* cpustate) {}
	size_t size() const { return 1; }
	size_t accumulatorBitsModified() const { return BM_HIGH | BM_MIDDLE | BM_LOW; }
=======
	void evaluate(dsp56k_core* cpustate) override {}
	size_t size() const override { return 1; }
	size_t accumulatorBitsModified() const override { return BM_HIGH | BM_MIDDLE | BM_LOW; }
>>>>>>> upstream/master

private:
	reg_id m_source2;
};

// MACR : .... .... 1k11 FQQQ : A-124 //////////////////////////////////////////
class Macr: public Instruction
{
public:
<<<<<<< HEAD
	Macr(const Opcode* oco, const UINT16 word0, const UINT16 word1) : Instruction(oco)
=======
	Macr(const Opcode* oco, const uint16_t word0, const uint16_t word1) : Instruction(oco)
>>>>>>> upstream/master
	{
		m_sign = "";
		m_source2 = iINVALID;
		m_valid = decode(word0, word1);
	}
<<<<<<< HEAD
	bool decode(const UINT16 word0, const UINT16 word1)
=======
	bool decode(const uint16_t word0, const uint16_t word1) override
>>>>>>> upstream/master
	{
		decode_QQQF_table(BITSn(word0,0x07), BITSn(word0,0x08),
							m_source, m_source2, m_destination);

		decode_kSign_table(BITSn(word0,0x40), m_sign);
		return true;
	}
<<<<<<< HEAD
	void disassemble(std::string& retString) const
=======
	void disassemble(std::string& retString) const override
>>>>>>> upstream/master
	{
		std::string ts = m_sign;
		if (ts.compare("-") != 0) ts = "";
		retString = "macr " +
					ts +
					regIdAsString(m_source) + "," +
					regIdAsString(m_source2) + "," + regIdAsString(m_destination);
	}
<<<<<<< HEAD
	void evaluate(dsp56k_core* cpustate) {}
	size_t size() const { return 1; }
	size_t accumulatorBitsModified() const { return BM_HIGH | BM_MIDDLE | BM_LOW; }
=======
	void evaluate(dsp56k_core* cpustate) override {}
	size_t size() const override { return 1; }
	size_t accumulatorBitsModified() const override { return BM_HIGH | BM_MIDDLE | BM_LOW; }
>>>>>>> upstream/master

private:
	std::string m_sign;
	reg_id m_source2;
};

// MACR : 011m mKKK 1--1 F1QQ : A-124 //////////////////////////////////////////
class Macr_2: public Instruction
{
public:
<<<<<<< HEAD
	Macr_2(const Opcode* oco, const UINT16 word0, const UINT16 word1) : Instruction(oco)
=======
	Macr_2(const Opcode* oco, const uint16_t word0, const uint16_t word1) : Instruction(oco)
>>>>>>> upstream/master
	{
		m_source2 = iINVALID;
		m_valid = decode(word0, word1);
	}
<<<<<<< HEAD
	bool decode(const UINT16 word0, const UINT16 word1)
=======
	bool decode(const uint16_t word0, const uint16_t word1) override
>>>>>>> upstream/master
	{
		decode_QQF_table(BITSn(word0,0x03), BITSn(word0,0x08),
							m_source, m_source2, m_destination);
		return true;
	}
<<<<<<< HEAD
	void disassemble(std::string& retString) const
=======
	void disassemble(std::string& retString) const override
>>>>>>> upstream/master
	{
		retString = "macr " +
					regIdAsString(m_source) + "," +
					regIdAsString(m_source2) + "," + regIdAsString(m_destination);
	}
<<<<<<< HEAD
	void evaluate(dsp56k_core* cpustate) {}
	size_t size() const { return 1; }
	size_t accumulatorBitsModified() const { return BM_HIGH | BM_MIDDLE | BM_LOW; }
=======
	void evaluate(dsp56k_core* cpustate) override {}
	size_t size() const override { return 1; }
	size_t accumulatorBitsModified() const override { return BM_HIGH | BM_MIDDLE | BM_LOW; }
>>>>>>> upstream/master

private:
	reg_id m_source2;
};

// MAC(su,uu) : 0001 0101 1110 FsQQ : A-126 ////////////////////////////////////
class Macsuuu: public Instruction
{
public:
<<<<<<< HEAD
	Macsuuu(const Opcode* oco, const UINT16 word0, const UINT16 word1) : Instruction(oco)
=======
	Macsuuu(const Opcode* oco, const uint16_t word0, const uint16_t word1) : Instruction(oco)
>>>>>>> upstream/master
	{
		m_mnem = oINVALID;
		m_source2 = iINVALID;
		m_valid = decode(word0, word1);
	}
<<<<<<< HEAD
	bool decode(const UINT16 word0, const UINT16 word1)
=======
	bool decode(const uint16_t word0, const uint16_t word1) override
>>>>>>> upstream/master
	{
		// Special QQF
		decode_QQF_special_table(BITSn(word0,0x0003), BITSn(word0,0x0008),
									m_source, m_source2, m_destination);

		decode_s_table(BITSn(word0,0x0004), m_mnem);
		return true;
	}
<<<<<<< HEAD
	void disassemble(std::string& retString) const
=======
	void disassemble(std::string& retString) const override
>>>>>>> upstream/master
	{
		std::string opcode = "mac" + opMnemonicAsString(m_mnem);

		retString = opcode + " " +
					regIdAsString(m_source) + "," +
					regIdAsString(m_source2) + "," + regIdAsString(m_destination);
		// NEW // sprintf(opcode_str, "mac(%s)", A);
	}
<<<<<<< HEAD
	void evaluate(dsp56k_core* cpustate) {}
	size_t size() const { return 1; }
	size_t accumulatorBitsModified() const { return BM_HIGH | BM_MIDDLE | BM_LOW; }
=======
	void evaluate(dsp56k_core* cpustate) override {}
	size_t size() const override { return 1; }
	size_t accumulatorBitsModified() const override { return BM_HIGH | BM_MIDDLE | BM_LOW; }
>>>>>>> upstream/master

private:
	op_mnem m_mnem;
	reg_id m_source2;
};

// MOVE : .... .... 0001 0001 : A-128 //////////////////////////////////////////
class Move: public Instruction
{
public:
<<<<<<< HEAD
	Move(const Opcode* oco, const UINT16 word0, const UINT16 word1) : Instruction(oco)
=======
	Move(const Opcode* oco, const uint16_t word0, const uint16_t word1) : Instruction(oco)
>>>>>>> upstream/master
	{
		m_isNop = false;
		m_valid = decode(word0, word1);
	}
<<<<<<< HEAD
	bool decode(const UINT16 word0, const UINT16 word1)
=======
	bool decode(const uint16_t word0, const uint16_t word1) override
>>>>>>> upstream/master
	{
		// Equivalent to a NOP (+ parallel move)

		// This insures the debugger matches the reference disassembler
		// for the undocumented .... .... 0001 1001 Instruction.
		if(BITSn(word0, 0x000f) == 0x0001)
			m_destination = iA;
		else
			m_destination = iB;

		// Hack to match reference disassembler
<<<<<<< HEAD
		UINT8 BITSn = (word0 & 0xff00) >> 8;
=======
		uint8_t BITSn = (word0 & 0xff00) >> 8;
>>>>>>> upstream/master
		if (BITSn == 0x4a || BITSn == 0x4b)
			m_isNop = true;

		return true;
	}
<<<<<<< HEAD
	void disassemble(std::string& retString) const
=======
	void disassemble(std::string& retString) const override
>>>>>>> upstream/master
	{
		if (m_isNop)
			retString = "nop";
		else
			retString = "move";
	}
<<<<<<< HEAD
	void evaluate(dsp56k_core* cpustate) {}
	size_t size() const { return 1; }
	size_t accumulatorBitsModified() const { return BM_NONE; }
=======
	void evaluate(dsp56k_core* cpustate) override {}
	size_t size() const override { return 1; }
	size_t accumulatorBitsModified() const override { return BM_NONE; }
>>>>>>> upstream/master

private:
	bool m_isNop;
};

// MOVE : 011m mKKK 0rr1 0000 : A-128 //////////////////////////////////////////
class Move_2: public Instruction
{
public:
<<<<<<< HEAD
	Move_2(const Opcode* oco, const UINT16 word0, const UINT16 word1) : Instruction(oco)
	{
		m_valid = decode(word0, word1);
	}
	bool decode(const UINT16 word0, const UINT16 word1)
=======
	Move_2(const Opcode* oco, const uint16_t word0, const uint16_t word1) : Instruction(oco)
	{
		m_valid = decode(word0, word1);
	}
	bool decode(const uint16_t word0, const uint16_t word1) override
>>>>>>> upstream/master
	{
		// Amounts to a nop with two parallel moves.
		// This insures the debugger matches the reference disassembler
		if((word0 & 0x0008) == 0x0008)
			m_destination = iB;
		else
			m_destination = iA;

		return true;
	}
<<<<<<< HEAD
	void disassemble(std::string& retString) const
	{
		retString = "move";
	}
	void evaluate(dsp56k_core* cpustate) {}
	size_t size() const { return 1; }
	size_t accumulatorBitsModified() const { return BM_HIGH | BM_MIDDLE | BM_LOW; }
=======
	void disassemble(std::string& retString) const override
	{
		retString = "move";
	}
	void evaluate(dsp56k_core* cpustate) override {}
	size_t size() const override { return 1; }
	size_t accumulatorBitsModified() const override { return BM_HIGH | BM_MIDDLE | BM_LOW; }
>>>>>>> upstream/master
};

// MOVE : 0000 0101 BBBB BBBB ---- HHHW 0001 0001 : A-128 //////////////////////
class Move_3: public Instruction
{
public:
<<<<<<< HEAD
	Move_3(const Opcode* oco, const UINT16 word0, const UINT16 word1) : Instruction(oco)
=======
	Move_3(const Opcode* oco, const uint16_t word0, const uint16_t word1) : Instruction(oco)
>>>>>>> upstream/master
	{
		m_W = 0;
		m_b = 0;
		m_SD = iINVALID;
		m_valid = decode(word0, word1);
	}
<<<<<<< HEAD
	bool decode(const UINT16 word0, const UINT16 word1)
=======
	bool decode(const uint16_t word0, const uint16_t word1) override
>>>>>>> upstream/master
	{
		m_b = BITSn(word0,0x00ff);
		m_W = BITSn(word1,0x0100);
		decode_HHH_table(BITSn(word1,0x0e00), m_SD);
		return true;
	}
<<<<<<< HEAD
	void disassemble(std::string& retString) const
=======
	void disassemble(std::string& retString) const override
>>>>>>> upstream/master
	{
		std::string source;
		std::string destination;
		assemble_reg_from_W_table(m_W, 'X', m_SD, m_b, source, destination);
		retString = "move " + source + "," + destination;
	}
<<<<<<< HEAD
	void evaluate(dsp56k_core* cpustate) {}
	size_t size() const { return 2; }
	size_t accumulatorBitsModified() const { return BM_HIGH | BM_MIDDLE | BM_LOW; }

private:
	INT8 m_b;
	UINT8 m_W;
=======
	void evaluate(dsp56k_core* cpustate) override {}
	size_t size() const override { return 2; }
	size_t accumulatorBitsModified() const override { return BM_HIGH | BM_MIDDLE | BM_LOW; }

private:
	int8_t m_b;
	uint8_t m_W;
>>>>>>> upstream/master
	reg_id m_SD;
};

// MOVE(C) : 0011 1WDD DDD0 MMRR : A-144 ///////////////////////////////////////
class Movec: public Instruction
{
public:
<<<<<<< HEAD
	Movec(const Opcode* oco, const UINT16 word0, const UINT16 word1) : Instruction(oco)
=======
	Movec(const Opcode* oco, const uint16_t word0, const uint16_t word1) : Instruction(oco)
>>>>>>> upstream/master
	{
		m_W = 0;
		m_ea = "";
		m_SD = iINVALID;
		m_valid = decode(word0, word1);
	}
<<<<<<< HEAD
	bool decode(const UINT16 word0, const UINT16 word1)
	{
		INT8 rNum = BITSn(word0,0x0003);
=======
	bool decode(const uint16_t word0, const uint16_t word1) override
	{
		int8_t rNum = BITSn(word0,0x0003);
>>>>>>> upstream/master
		assemble_ea_from_MM_table(BITSn(word0,0x000c), rNum, m_ea);

		m_W = BITSn(word0,0x0400);
		decode_DDDDD_table(BITSn(word0,0x03e0), m_SD);
		if (m_SD == iINVALID) return false;
		return true;
	}
<<<<<<< HEAD
	void disassemble(std::string& retString) const
=======
	void disassemble(std::string& retString) const override
>>>>>>> upstream/master
	{
		std::string source;
		std::string destination;
		assemble_arguments_from_W_table(m_W, 'X', m_SD, m_ea, source, destination);
		retString = "move " + source + "," + destination;
		// NEW // sprintf(opcode_str, "move(c)");
	}
<<<<<<< HEAD
	void evaluate(dsp56k_core* cpustate) {}
	size_t size() const { return 1; }
	size_t accumulatorBitsModified() const { return BM_HIGH | BM_MIDDLE | BM_LOW; }

private:
	INT8 m_W;
=======
	void evaluate(dsp56k_core* cpustate) override {}
	size_t size() const override { return 1; }
	size_t accumulatorBitsModified() const override { return BM_HIGH | BM_MIDDLE | BM_LOW; }

private:
	int8_t m_W;
>>>>>>> upstream/master
	reg_id m_SD;
	std::string m_ea;
};

// MOVE(C) : 0011 1WDD DDD1 q0RR : A-144 ///////////////////////////////////////
class Movec_2: public Instruction
{
public:
<<<<<<< HEAD
	Movec_2(const Opcode* oco, const UINT16 word0, const UINT16 word1) : Instruction(oco)
=======
	Movec_2(const Opcode* oco, const uint16_t word0, const uint16_t word1) : Instruction(oco)
>>>>>>> upstream/master
	{
		m_W = 0;
		m_ea = "";
		m_SD = iINVALID;
		m_valid = decode(word0, word1);
	}
<<<<<<< HEAD
	bool decode(const UINT16 word0, const UINT16 word1)
	{
		INT8 rNum = BITSn(word0,0x0003);
=======
	bool decode(const uint16_t word0, const uint16_t word1) override
	{
		int8_t rNum = BITSn(word0,0x0003);
>>>>>>> upstream/master
		assemble_ea_from_q_table(BITSn(word0,0x0008), rNum, m_ea);

		decode_DDDDD_table(BITSn(word0,0x03e0), m_SD);
		m_W = BITSn(word0,0x0400);
		if (m_SD == iINVALID) return false;
		return true;
	}
<<<<<<< HEAD
	void disassemble(std::string& retString) const
=======
	void disassemble(std::string& retString) const override
>>>>>>> upstream/master
	{
		std::string source;
		std::string destination;
		assemble_arguments_from_W_table(m_W, 'X', m_SD, m_ea, source, destination);
		retString = "move " + source + "," + destination;
		// NEW // sprintf(opcode_str, "move(c)");
	}
<<<<<<< HEAD
	void evaluate(dsp56k_core* cpustate) {}
	size_t size() const { return 1; }
	size_t accumulatorBitsModified() const { return BM_HIGH | BM_MIDDLE | BM_LOW; }

private:
	INT8 m_W;
=======
	void evaluate(dsp56k_core* cpustate) override {}
	size_t size() const override { return 1; }
	size_t accumulatorBitsModified() const override { return BM_HIGH | BM_MIDDLE | BM_LOW; }

private:
	int8_t m_W;
>>>>>>> upstream/master
	reg_id m_SD;
	std::string m_ea;
};

// MOVE(C) : 0011 1WDD DDD1 Z11- : A-144 ///////////////////////////////////////
class Movec_3: public Instruction
{
public:
<<<<<<< HEAD
	Movec_3(const Opcode* oco, const UINT16 word0, const UINT16 word1) : Instruction(oco)
=======
	Movec_3(const Opcode* oco, const uint16_t word0, const uint16_t word1) : Instruction(oco)
>>>>>>> upstream/master
	{
		m_W = 0;
		m_ea = "";
		m_SD = iINVALID;
		m_valid = decode(word0, word1);
	}
<<<<<<< HEAD
	bool decode(const UINT16 word0, const UINT16 word1)
=======
	bool decode(const uint16_t word0, const uint16_t word1) override
>>>>>>> upstream/master
	{
		decode_Z_table(BITSn(word0,0x0008), m_ea);

		decode_DDDDD_table(BITSn(word0,0x03e0), m_SD);
		m_W = BITSn(word0,0x0400);
		if (m_SD == iINVALID) return false;
		return true;
	}
<<<<<<< HEAD
	void disassemble(std::string& retString) const
=======
	void disassemble(std::string& retString) const override
>>>>>>> upstream/master
	{
		std::string source;
		std::string destination;
		assemble_arguments_from_W_table(m_W, 'X', m_SD, m_ea, source, destination);
		retString = "move " + source + "," + destination;
		// NEW // sprintf(opcode_str, "move(c)");
	}
<<<<<<< HEAD
	void evaluate(dsp56k_core* cpustate) {}
	size_t size() const { return 1; }
	size_t accumulatorBitsModified() const { return BM_HIGH | BM_MIDDLE | BM_LOW; }

private:
	INT8 m_W;
=======
	void evaluate(dsp56k_core* cpustate) override {}
	size_t size() const override { return 1; }
	size_t accumulatorBitsModified() const override { return BM_HIGH | BM_MIDDLE | BM_LOW; }

private:
	int8_t m_W;
>>>>>>> upstream/master
	reg_id m_SD;
	std::string m_ea;
};

// MOVE(C) : 0011 1WDD DDD1 t10- xxxx xxxx xxxx xxxx : A-144 ///////////////////
class Movec_4: public Instruction
{
public:
<<<<<<< HEAD
	Movec_4(const Opcode* oco, const UINT16 word0, const UINT16 word1) : Instruction(oco)
=======
	Movec_4(const Opcode* oco, const uint16_t word0, const uint16_t word1) : Instruction(oco)
>>>>>>> upstream/master
	{
		m_t = 0;
		m_W = 0;
		m_sd = iINVALID;
		m_valid = decode(word0, word1);
	}
<<<<<<< HEAD
	bool decode(const UINT16 word0, const UINT16 word1)
=======
	bool decode(const uint16_t word0, const uint16_t word1) override
>>>>>>> upstream/master
	{
		m_value = word1;
		m_t = BITSn(word0,0x0008);
		m_W = BITSn(word0,0x0400);

		decode_DDDDD_table(BITSn(word0,0x03e0), m_sd);
		if (m_sd == iINVALID) return false;

		// TODO: Figure out what this means, exactly.
		if ((word0 & 0x000c) == 0x000c && (word0 & 0x0400) == 0x0000)
			return false;

		return true;
	}
<<<<<<< HEAD
	void disassemble(std::string& retString) const
=======
	void disassemble(std::string& retString) const override
>>>>>>> upstream/master
	{
		std::string ea;
		assemble_ea_from_t_table(m_t, m_value, ea);

		retString = "move ";
		if (m_W) retString += ea + "," + regIdAsString(m_sd);
		else     retString += regIdAsString(m_sd) + "," + ea;
		// NEW // sprintf(opcode_str, "move(c)");
	}
<<<<<<< HEAD
	void evaluate(dsp56k_core* cpustate)
=======
	void evaluate(dsp56k_core* cpustate) override
>>>>>>> upstream/master
	{
		if (m_W)
		{
			if (m_t)
			{
				setReg16(cpustate, m_value, m_sd);
			}
			else
			{
<<<<<<< HEAD
				//UINT16 memValue = memory_read_word_16le(cpustate->data, ADDRESS(m_value));
=======
				//uint16_t memValue = memory_read_word_16le(cpustate->data, ADDRESS(m_value));
>>>>>>> upstream/master
				//setReg16(cpustate, memValue, m_sd);
			}
		}
		else
		{
			if (m_t)
			{
				osd_printf_error("DSP561xx|Movec_4: This sure seems like it can't happen.");
			}
			else
			{
<<<<<<< HEAD
				//UINT16 regValue = regValue16(cpustate, m_sd);
=======
				//uint16_t regValue = regValue16(cpustate, m_sd);
>>>>>>> upstream/master
				//memory_write_word_16le(cpustate->data, m_value, regValue);
			}
		}

		/* S L E U N Z V C */
		/* * ? ? ? ? ? ? ? */
		// All ? bits - If SR is specified as a destination operand, set according to the corresponding
		// bit of the source operand. If SR is not specified as a destination operand, L is set if data
		// limiting occurred. All ? bits are not affected otherwise.
	}
<<<<<<< HEAD
	size_t size() const { return 2; }
	size_t accumulatorBitsModified() const { return BM_HIGH | BM_MIDDLE | BM_LOW; }

private:
	UINT8 m_t;
	UINT8 m_W;
	UINT16 m_value;
=======
	size_t size() const override { return 2; }
	size_t accumulatorBitsModified() const override { return BM_HIGH | BM_MIDDLE | BM_LOW; }

private:
	uint8_t m_t;
	uint8_t m_W;
	uint16_t m_value;
>>>>>>> upstream/master
	reg_id m_sd;
};

// MOVE(C) : 0010 10dd dddD DDDD : A-144 ///////////////////////////////////////
class Movec_5: public Instruction
{
public:
<<<<<<< HEAD
	Movec_5(const Opcode* oco, const UINT16 word0, const UINT16 word1) : Instruction(oco)
	{
		m_valid = decode(word0, word1);
	}
	bool decode(const UINT16 word0, const UINT16 word1)
=======
	Movec_5(const Opcode* oco, const uint16_t word0, const uint16_t word1) : Instruction(oco)
	{
		m_valid = decode(word0, word1);
	}
	bool decode(const uint16_t word0, const uint16_t word1) override
>>>>>>> upstream/master
	{
		decode_DDDDD_table(BITSn(word0,0x03e0), m_source);
		decode_DDDDD_table(BITSn(word0,0x001f), m_destination);

		if (m_source == iINVALID || m_destination == iINVALID) return false;
		if (m_source == iSSH && m_destination == iSSH) return false;
		return true;
	}
<<<<<<< HEAD
	void disassemble(std::string& retString) const
=======
	void disassemble(std::string& retString) const override
>>>>>>> upstream/master
	{
		retString = "move " + regIdAsString(m_source) + "," + regIdAsString(m_destination);
		// NEW // sprintf(opcode_str, "move(c)");
	}
<<<<<<< HEAD
	void evaluate(dsp56k_core* cpustate) {}
	size_t size() const { return 1; }
	size_t accumulatorBitsModified() const { return BM_HIGH | BM_MIDDLE | BM_LOW; }
=======
	void evaluate(dsp56k_core* cpustate) override {}
	size_t size() const override { return 1; }
	size_t accumulatorBitsModified() const override { return BM_HIGH | BM_MIDDLE | BM_LOW; }
>>>>>>> upstream/master
};

// MOVE(C) : 0000 0101 BBBB BBBB 0011 1WDD DDD0 ---- : A-144 ///////////////////
class Movec_6: public Instruction
{
public:
<<<<<<< HEAD
	Movec_6(const Opcode* oco, const UINT16 word0, const UINT16 word1) : Instruction(oco)
=======
	Movec_6(const Opcode* oco, const uint16_t word0, const uint16_t word1) : Instruction(oco)
>>>>>>> upstream/master
	{
		m_W = 0;
		m_b = 0;
		m_SD = iINVALID;
		m_mnem = oINVALID;
		m_valid = decode(word0, word1);
	}
<<<<<<< HEAD
	bool decode(const UINT16 word0, const UINT16 word1)
=======
	bool decode(const uint16_t word0, const uint16_t word1) override
>>>>>>> upstream/master
	{
		m_b = BITSn(word0,0x00ff);
		m_W = BITSn(word1,0x0400);
		decode_DDDDD_table(BITSn(word1,0x03e0), m_SD);
		return true;
	}
<<<<<<< HEAD
	void disassemble(std::string& retString) const
=======
	void disassemble(std::string& retString) const override
>>>>>>> upstream/master
	{
		std::string source;
		std::string destination;
		assemble_reg_from_W_table(m_W, 'X', m_SD, m_b, source, destination);
		retString = "move " + source + "," + destination;
		// NEW // opcode = "move(c)";
	}
<<<<<<< HEAD
	void evaluate(dsp56k_core* cpustate) {}
	size_t size() const { return 2; }
	size_t accumulatorBitsModified() const { return BM_HIGH | BM_MIDDLE | BM_LOW; }

private:
	INT8 m_b;
	UINT8 m_W;
=======
	void evaluate(dsp56k_core* cpustate) override {}
	size_t size() const override { return 2; }
	size_t accumulatorBitsModified() const override { return BM_HIGH | BM_MIDDLE | BM_LOW; }

private:
	int8_t m_b;
	uint8_t m_W;
>>>>>>> upstream/master
	reg_id m_SD;
	op_mnem m_mnem;
};

// MOVE(I) : 0010 00DD BBBB BBBB : A-150 ///////////////////////////////////////
class Movei: public Instruction
{
public:
<<<<<<< HEAD
	Movei(const Opcode* oco, const UINT16 word0, const UINT16 word1) : Instruction(oco)
=======
	Movei(const Opcode* oco, const uint16_t word0, const uint16_t word1) : Instruction(oco)
>>>>>>> upstream/master
	{
		m_immediate = 0;
		m_valid = decode(word0, word1);
	}
<<<<<<< HEAD
	bool decode(const UINT16 word0, const UINT16 word1)
	{
		m_immediate = (INT8)BITSn(word0,0x00ff);
		decode_DD_table(BITSn(word0,0x0300), m_destination);
		return true;
	}
	void disassemble(std::string& retString) const
=======
	bool decode(const uint16_t word0, const uint16_t word1) override
	{
		m_immediate = (int8_t)BITSn(word0,0x00ff);
		decode_DD_table(BITSn(word0,0x0300), m_destination);
		return true;
	}
	void disassemble(std::string& retString) const override
>>>>>>> upstream/master
	{
		char temp[32];
		if (m_immediate >= 0) sprintf(temp, "#<+$%x", m_immediate);
		else                  sprintf(temp, "#<-$%x", 1 - m_immediate - 1);
		// NEW // sprintf(temp, "#$%02x,%s", BITSn(word0,0x00ff), D1);

		retString = "move " +
			std::string(temp) + "," + regIdAsString(m_destination);
		// NEW // sprintf(opcode_str, "move(i)");
	}
<<<<<<< HEAD
	void evaluate(dsp56k_core* cpustate) {}
	size_t size() const { return 1; }
	size_t accumulatorBitsModified() const { return BM_HIGH | BM_MIDDLE | BM_LOW; }

private:
	INT8 m_immediate;
=======
	void evaluate(dsp56k_core* cpustate) override {}
	size_t size() const override { return 1; }
	size_t accumulatorBitsModified() const override { return BM_HIGH | BM_MIDDLE | BM_LOW; }

private:
	int8_t m_immediate;
>>>>>>> upstream/master
};

// MOVE(M) : 0000 001W RR0M MHHH : A-152 ///////////////////////////////////////
class Movem: public Instruction
{
public:
<<<<<<< HEAD
	Movem(const Opcode* oco, const UINT16 word0, const UINT16 word1) : Instruction(oco)
=======
	Movem(const Opcode* oco, const uint16_t word0, const uint16_t word1) : Instruction(oco)
>>>>>>> upstream/master
	{
		m_W = 0;
		m_ea = "";
		m_SD = iINVALID;
		m_valid = decode(word0, word1);
	}
<<<<<<< HEAD
	bool decode(const UINT16 word0, const UINT16 word1)
	{
		INT8 rNum = BITSn(word0,0x00c0);
=======
	bool decode(const uint16_t word0, const uint16_t word1) override
	{
		int8_t rNum = BITSn(word0,0x00c0);
>>>>>>> upstream/master

		decode_HHH_table(BITSn(word0,0x0007), m_SD);
		assemble_ea_from_MM_table(BITSn(word0,0x0018), rNum, m_ea);
		m_W = BITSn(word0,0x0100);
		return true;
	}
<<<<<<< HEAD
	void disassemble(std::string& retString) const
=======
	void disassemble(std::string& retString) const override
>>>>>>> upstream/master
	{
		std::string source;
		std::string destination;
		assemble_arguments_from_W_table(m_W, 'P', m_SD, m_ea, source, destination);
		retString = "move " + source + "," + destination;
		// NEW // sprintf(opcode_str, "move(m)");
	}
<<<<<<< HEAD
	void evaluate(dsp56k_core* cpustate) {}
	size_t size() const { return 1; }
	size_t accumulatorBitsModified() const { return BM_HIGH | BM_MIDDLE | BM_LOW; }

private:
	INT8 m_W;
=======
	void evaluate(dsp56k_core* cpustate) override {}
	size_t size() const override { return 1; }
	size_t accumulatorBitsModified() const override { return BM_HIGH | BM_MIDDLE | BM_LOW; }

private:
	int8_t m_W;
>>>>>>> upstream/master
	reg_id m_SD;
	std::string m_ea;
};

// MOVE(M) : 0000 001W RR11 mmRR : A-152 ///////////////////////////////////////
class Movem_2: public Instruction
{
public:
<<<<<<< HEAD
	Movem_2(const Opcode* oco, const UINT16 word0, const UINT16 word1) : Instruction(oco)
=======
	Movem_2(const Opcode* oco, const uint16_t word0, const uint16_t word1) : Instruction(oco)
>>>>>>> upstream/master
	{
		m_W = 0;
		m_ea = "";
		m_ea2 = "";
		m_valid = decode(word0, word1);
	}
<<<<<<< HEAD
	bool decode(const UINT16 word0, const UINT16 word1)
=======
	bool decode(const uint16_t word0, const uint16_t word1) override
>>>>>>> upstream/master
	{
		m_W = BITSn(word0,0x0100);
		assemble_eas_from_mm_table(BITSn(word0,0x000c), BITSn(word0,0x00c0), BITSn(word0,0x0003), m_ea, m_ea2);
		return true;
	}
<<<<<<< HEAD
	void disassemble(std::string& retString) const
=======
	void disassemble(std::string& retString) const override
>>>>>>> upstream/master
	{
		std::string source;
		std::string destination;
		if (m_W)
		{
			source = "X:" + m_ea;
			destination = "P:" + m_ea2;
		}
		else
		{
			source = "P:" + m_ea;
			destination = "X:" + m_ea2;
		}
		retString = "move " + source + "," + destination;
		// NEW // sprintf(opcode_str, "move(m)*");
	}
<<<<<<< HEAD
	void evaluate(dsp56k_core* cpustate) {}
	size_t size() const { return 1; }
	size_t accumulatorBitsModified() const { return BM_HIGH | BM_MIDDLE | BM_LOW; }

private:
	UINT8 m_W;
=======
	void evaluate(dsp56k_core* cpustate) override {}
	size_t size() const override { return 1; }
	size_t accumulatorBitsModified() const override { return BM_HIGH | BM_MIDDLE | BM_LOW; }

private:
	uint8_t m_W;
>>>>>>> upstream/master
	std::string m_ea;
	std::string m_ea2;
};

// MOVE(M) : 0000 0101 BBBB BBBB 0000 001W --0- -HHH : A-152 ///////////////////
class Movem_3: public Instruction
{
public:
<<<<<<< HEAD
	Movem_3(const Opcode* oco, const UINT16 word0, const UINT16 word1) : Instruction(oco)
=======
	Movem_3(const Opcode* oco, const uint16_t word0, const uint16_t word1) : Instruction(oco)
>>>>>>> upstream/master
	{
		m_b = 0;
		m_SD = iINVALID;
		m_mnem = oINVALID;
		m_valid = decode(word0, word1);
	}
<<<<<<< HEAD
	bool decode(const UINT16 word0, const UINT16 word1)
=======
	bool decode(const uint16_t word0, const uint16_t word1) override
>>>>>>> upstream/master
	{
		m_b = BITSn(word0,0x00ff);
		m_W = BITSn(word1,0x0100);
		decode_HHH_table(BITSn(word1,0x0007), m_SD);
		return true;
	}
<<<<<<< HEAD
	void disassemble(std::string& retString) const
=======
	void disassemble(std::string& retString) const override
>>>>>>> upstream/master
	{
		std::string source;
		std::string destination;
		assemble_reg_from_W_table(m_W, 'P', m_SD, m_b, source, destination);
		retString = "move " + source + "," + destination;
		// NEW // opcode = "move(m)";
	}
<<<<<<< HEAD
	void evaluate(dsp56k_core* cpustate) {}
	size_t size() const { return 2; }
	size_t accumulatorBitsModified() const { return BM_HIGH | BM_MIDDLE | BM_LOW; }

private:
	INT8 m_b;
	UINT8 m_W;
=======
	void evaluate(dsp56k_core* cpustate) override {}
	size_t size() const override { return 2; }
	size_t accumulatorBitsModified() const override { return BM_HIGH | BM_MIDDLE | BM_LOW; }

private:
	int8_t m_b;
	uint8_t m_W;
>>>>>>> upstream/master
	reg_id m_SD;
	op_mnem m_mnem;
};

// MOVE(P) : 0001 100W HH1p pppp : A-156 ///////////////////////////////////////
class Movep: public Instruction
{
public:
<<<<<<< HEAD
	Movep(const Opcode* oco, const UINT16 word0, const UINT16 word1) : Instruction(oco)
=======
	Movep(const Opcode* oco, const uint16_t word0, const uint16_t word1) : Instruction(oco)
>>>>>>> upstream/master
	{
		m_W = 0;
		m_ea = "";
		m_SD = iINVALID;
		m_valid = decode(word0, word1);
	}
<<<<<<< HEAD
	bool decode(const UINT16 word0, const UINT16 word1)
=======
	bool decode(const uint16_t word0, const uint16_t word1) override
>>>>>>> upstream/master
	{
		decode_HH_table(BITSn(word0,0x00c0), m_SD);

		assemble_address_from_IO_short_address(BITSn(word0,0x001f), m_ea);
		m_ea = "<<$" + m_ea;

		m_W = BITSn(word0,0x0100);
		return true;
	}
<<<<<<< HEAD
	void disassemble(std::string& retString) const
=======
	void disassemble(std::string& retString) const override
>>>>>>> upstream/master
	{
		std::string source;
		std::string destination;
		assemble_arguments_from_W_table(m_W, 'X', m_SD, m_ea, source, destination);
		retString = "movep " + source + "," + destination;
		// NEW // sprintf(opcode_str, "move(p)");
	}
<<<<<<< HEAD
	void evaluate(dsp56k_core* cpustate) {}
	size_t size() const { return 1; }
	size_t accumulatorBitsModified() const { return BM_HIGH | BM_MIDDLE | BM_LOW; }

private:
	INT8 m_W;
=======
	void evaluate(dsp56k_core* cpustate) override {}
	size_t size() const override { return 1; }
	size_t accumulatorBitsModified() const override { return BM_HIGH | BM_MIDDLE | BM_LOW; }

private:
	int8_t m_W;
>>>>>>> upstream/master
	reg_id m_SD;
	std::string m_ea;
};

// MOVE(P) : 0000 110W RRmp pppp : A-156 ///////////////////////////////////////
class Movep_2: public Instruction
{
public:
<<<<<<< HEAD
	Movep_2(const Opcode* oco, const UINT16 word0, const UINT16 word1) : Instruction(oco)
=======
	Movep_2(const Opcode* oco, const uint16_t word0, const uint16_t word1) : Instruction(oco)
>>>>>>> upstream/master
	{
		m_W = 0;
		m_ea = "";
		m_SD = "";
		m_valid = decode(word0, word1);
	}
<<<<<<< HEAD
	bool decode(const UINT16 word0, const UINT16 word1)
	{
		INT8 rNum = BITSn(word0,0x00c0);
=======
	bool decode(const uint16_t word0, const uint16_t word1) override
	{
		int8_t rNum = BITSn(word0,0x00c0);
>>>>>>> upstream/master

		assemble_ea_from_m_table(BITSn(word0,0x0020), rNum, m_ea);

		std::string fullAddy;    /* Convert Short Absolute Address to full 16-bit */
		assemble_address_from_IO_short_address(BITSn(word0,0x001f), fullAddy);

		m_W = BITSn(word0,0x0100);
		m_SD = "X:<<$" + fullAddy;
		// NEW // sprintf(SD, "X:$%s", fullAddy);
		return true;
	}
<<<<<<< HEAD
	void disassemble(std::string& retString) const
=======
	void disassemble(std::string& retString) const override
>>>>>>> upstream/master
	{
		std::string source;
		std::string destination;
		assemble_arguments_from_W_table(m_W, 'X', m_SD, m_ea, source, destination);
		retString = "movep " + source + "," + destination;
		// NEW // sprintf(opcode_str, "move(p)*");
	}
<<<<<<< HEAD
	void evaluate(dsp56k_core* cpustate) {}
	size_t size() const { return 1; }
	size_t accumulatorBitsModified() const { return BM_HIGH | BM_MIDDLE | BM_LOW; }

private:
	INT8 m_W;
=======
	void evaluate(dsp56k_core* cpustate) override {}
	size_t size() const override { return 1; }
	size_t accumulatorBitsModified() const override { return BM_HIGH | BM_MIDDLE | BM_LOW; }

private:
	int8_t m_W;
>>>>>>> upstream/master
	std::string m_SD;
	std::string m_ea;
};

// MOVE(S) : 0001 100W HH0a aaaa : A-158 ///////////////////////////////////////
class Moves: public Instruction
{
public:
<<<<<<< HEAD
	Moves(const Opcode* oco, const UINT16 word0, const UINT16 word1) : Instruction(oco)
=======
	Moves(const Opcode* oco, const uint16_t word0, const uint16_t word1) : Instruction(oco)
>>>>>>> upstream/master
	{
		m_W = 0;
		m_ea = "";
		m_SD = iINVALID;
		m_valid = decode(word0, word1);
	}
<<<<<<< HEAD
	bool decode(const UINT16 word0, const UINT16 word1)
=======
	bool decode(const uint16_t word0, const uint16_t word1) override
>>>>>>> upstream/master
	{
		decode_HH_table(BITSn(word0,0x00c0), m_SD);

		char temp[32];
		sprintf(temp, "<$%x", BITSn(word0,0x001f));
		m_ea = temp;

		m_W = BITSn(word0,0x0100);
		return true;
	}
<<<<<<< HEAD
	void disassemble(std::string& retString) const
=======
	void disassemble(std::string& retString) const override
>>>>>>> upstream/master
	{
		std::string source;
		std::string destination;
		assemble_arguments_from_W_table(m_W, 'X', m_SD, m_ea, source, destination);
		retString = "moves " + source + "," + destination;
		// NEW // sprintf(opcode_str, "move(s)");
	}
<<<<<<< HEAD
	void evaluate(dsp56k_core* cpustate) {}
	size_t size() const { return 1; }
	size_t accumulatorBitsModified() const { return BM_HIGH | BM_MIDDLE | BM_LOW; }

private:
	INT8 m_W;
=======
	void evaluate(dsp56k_core* cpustate) override {}
	size_t size() const override { return 1; }
	size_t accumulatorBitsModified() const override { return BM_HIGH | BM_MIDDLE | BM_LOW; }

private:
	int8_t m_W;
>>>>>>> upstream/master
	reg_id m_SD;
	std::string m_ea;
};

// MPY : .... .... 1k00 FQQQ : A-160 ///////////////////////////////////////////
class Mpy: public Instruction
{
public:
<<<<<<< HEAD
	Mpy(const Opcode* oco, const UINT16 word0, const UINT16 word1) : Instruction(oco)
=======
	Mpy(const Opcode* oco, const uint16_t word0, const uint16_t word1) : Instruction(oco)
>>>>>>> upstream/master
	{
		m_sign = "";
		m_source2 = iINVALID;
		m_valid = decode(word0, word1);
	}
<<<<<<< HEAD
	bool decode(const UINT16 word0, const UINT16 word1)
=======
	bool decode(const uint16_t word0, const uint16_t word1) override
>>>>>>> upstream/master
	{
		/* There are inconsistencies with the S1 & S2 operand ordering in the docs,
		   but since it's a multiply it doesn't matter */
		decode_QQQF_table(BITSn(word0,0x07), BITSn(word0,0x08),
							m_source, m_source2, m_destination);

		decode_kSign_table(BITSn(word0,0x40), m_sign);
		return true;
	}
<<<<<<< HEAD
	void disassemble(std::string& retString) const
=======
	void disassemble(std::string& retString) const override
>>>>>>> upstream/master
	{
		std::string ts = m_sign;
		if (ts.compare("-")!=0) ts = "";
		retString = "mpy " +
					ts +
					regIdAsString(m_source) + "," +
					regIdAsString(m_source2) + "," + regIdAsString(m_destination);
	}
<<<<<<< HEAD
	void evaluate(dsp56k_core* cpustate) {}
	size_t size() const { return 1; }
	size_t accumulatorBitsModified() const { return BM_HIGH | BM_MIDDLE | BM_LOW; }
=======
	void evaluate(dsp56k_core* cpustate) override {}
	size_t size() const override { return 1; }
	size_t accumulatorBitsModified() const override { return BM_HIGH | BM_MIDDLE | BM_LOW; }
>>>>>>> upstream/master

private:
	std::string m_sign;
	reg_id m_source2;
};

// MPY : 011m mKKK 1xx0 F0QQ : A-160 ///////////////////////////////////////////
class Mpy_2: public Instruction
{
public:
<<<<<<< HEAD
	Mpy_2(const Opcode* oco, const UINT16 word0, const UINT16 word1) : Instruction(oco)
=======
	Mpy_2(const Opcode* oco, const uint16_t word0, const uint16_t word1) : Instruction(oco)
>>>>>>> upstream/master
	{
		m_source2 = iINVALID;
		m_valid = decode(word0, word1);
	}
<<<<<<< HEAD
	bool decode(const UINT16 word0, const UINT16 word1)
=======
	bool decode(const uint16_t word0, const uint16_t word1) override
>>>>>>> upstream/master
	{
		decode_QQF_table(BITSn(word0,0x03), BITSn(word0,0x08),
							m_source, m_source2, m_destination);
		return true;
	}
<<<<<<< HEAD
	void disassemble(std::string& retString) const
=======
	void disassemble(std::string& retString) const override
>>>>>>> upstream/master
	{
		retString = "mpy " +
					regIdAsString(m_source) + "," +
					regIdAsString(m_source2) + "," + regIdAsString(m_destination);
	}
<<<<<<< HEAD
	void evaluate(dsp56k_core* cpustate) {}
	size_t size() const { return 1; }
	size_t accumulatorBitsModified() const { return BM_HIGH | BM_MIDDLE | BM_LOW; }
=======
	void evaluate(dsp56k_core* cpustate) override {}
	size_t size() const override { return 1; }
	size_t accumulatorBitsModified() const override { return BM_HIGH | BM_MIDDLE | BM_LOW; }
>>>>>>> upstream/master

private:
	reg_id m_source2;
};

// MPY : 0001 0110 RRDD FQQQ : A-160 ///////////////////////////////////////////
class Mpy_3: public Instruction
{
public:
<<<<<<< HEAD
	Mpy_3(const Opcode* oco, const UINT16 word0, const UINT16 word1) : Instruction(oco)
=======
	Mpy_3(const Opcode* oco, const uint16_t word0, const uint16_t word1) : Instruction(oco)
>>>>>>> upstream/master
	{
		m_source2 = iINVALID;
		m_valid = decode(word0, word1);
	}
<<<<<<< HEAD
	bool decode(const UINT16 word0, const UINT16 word1)
=======
	bool decode(const uint16_t word0, const uint16_t word1) override
>>>>>>> upstream/master
	{
		decode_QQQF_table(BITSn(word0,0x0007), BITSn(word0,0x0008),
							m_source, m_source2, m_destination);
		return true;
	}
<<<<<<< HEAD
	void disassemble(std::string& retString) const
=======
	void disassemble(std::string& retString) const override
>>>>>>> upstream/master
	{
		retString = "mpy " +
					regIdAsString(m_source) + "," +
					regIdAsString(m_source2) + "," + regIdAsString(m_destination);
	}
<<<<<<< HEAD
	void evaluate(dsp56k_core* cpustate) {}
	size_t size() const { return 1; }
	size_t accumulatorBitsModified() const { return BM_HIGH | BM_MIDDLE | BM_LOW; }
=======
	void evaluate(dsp56k_core* cpustate) override {}
	size_t size() const override { return 1; }
	size_t accumulatorBitsModified() const override { return BM_HIGH | BM_MIDDLE | BM_LOW; }
>>>>>>> upstream/master

private:
	reg_id m_source2;
};

// MPYR : .... .... 1k01 FQQQ : A-162 //////////////////////////////////////////
class Mpyr: public Instruction
{
public:
<<<<<<< HEAD
	Mpyr(const Opcode* oco, const UINT16 word0, const UINT16 word1) : Instruction(oco)
=======
	Mpyr(const Opcode* oco, const uint16_t word0, const uint16_t word1) : Instruction(oco)
>>>>>>> upstream/master
	{
		m_sign = "-";
		m_source2 = iINVALID;
		m_valid = decode(word0, word1);
	}
<<<<<<< HEAD
	bool decode(const UINT16 word0, const UINT16 word1)
=======
	bool decode(const uint16_t word0, const uint16_t word1) override
>>>>>>> upstream/master
	{
		/* There are inconsistencies with the S1 & S2 operand ordering in the docs,
		   but since it's a multiply it doesn't matter */
		decode_QQQF_table(BITSn(word0,0x07), BITSn(word0,0x08),
							m_source, m_source2, m_destination);

		decode_kSign_table(BITSn(word0,0x40), m_sign);
		return true;
	}
<<<<<<< HEAD
	void disassemble(std::string& retString) const
=======
	void disassemble(std::string& retString) const override
>>>>>>> upstream/master
	{
		std::string ts = m_sign;
		if (ts.compare("-") != 0) ts = "";
		retString = "mpyr " +
					ts +
					regIdAsString(m_source) + "," +
					regIdAsString(m_source2) + "," + regIdAsString(m_destination);
	}
<<<<<<< HEAD
	void evaluate(dsp56k_core* cpustate) {}
	size_t size() const { return 1; }
	size_t accumulatorBitsModified() const { return BM_HIGH | BM_MIDDLE | BM_LOW; }
=======
	void evaluate(dsp56k_core* cpustate) override {}
	size_t size() const override { return 1; }
	size_t accumulatorBitsModified() const override { return BM_HIGH | BM_MIDDLE | BM_LOW; }
>>>>>>> upstream/master

private:
	std::string m_sign;
	reg_id m_source2;
};

// MPYR : 011m mKKK 1--1 F0QQ : A-162 //////////////////////////////////////////
class Mpyr_2: public Instruction
{
public:
<<<<<<< HEAD
	Mpyr_2(const Opcode* oco, const UINT16 word0, const UINT16 word1) : Instruction(oco)
=======
	Mpyr_2(const Opcode* oco, const uint16_t word0, const uint16_t word1) : Instruction(oco)
>>>>>>> upstream/master
	{
		m_source2 = iINVALID;
		m_valid = decode(word0, word1);
	}
<<<<<<< HEAD
	bool decode(const UINT16 word0, const UINT16 word1)
=======
	bool decode(const uint16_t word0, const uint16_t word1) override
>>>>>>> upstream/master
	{
		decode_QQF_table(BITSn(word0,0x03), BITSn(word0,0x08),
							m_source, m_source2, m_destination);
		return true;
	}
<<<<<<< HEAD
	void disassemble(std::string& retString) const
=======
	void disassemble(std::string& retString) const override
>>>>>>> upstream/master
	{
		retString = "mpyr " +
					regIdAsString(m_source) + "," +
					regIdAsString(m_source2) + "," + regIdAsString(m_destination);
	}
<<<<<<< HEAD
	void evaluate(dsp56k_core* cpustate) {}
	size_t size() const { return 1; }
	size_t accumulatorBitsModified() const { return BM_HIGH | BM_MIDDLE | BM_LOW; }
=======
	void evaluate(dsp56k_core* cpustate) override {}
	size_t size() const override { return 1; }
	size_t accumulatorBitsModified() const override { return BM_HIGH | BM_MIDDLE | BM_LOW; }
>>>>>>> upstream/master

private:
	reg_id m_source2;
};

// MPY(su,uu) : 0001 0101 1100 FsQQ : A-164 ////////////////////////////////////
class Mpysuuu: public Instruction
{
public:
<<<<<<< HEAD
	Mpysuuu(const Opcode* oco, const UINT16 word0, const UINT16 word1) : Instruction(oco)
=======
	Mpysuuu(const Opcode* oco, const uint16_t word0, const uint16_t word1) : Instruction(oco)
>>>>>>> upstream/master
	{
		m_mnem = oINVALID;
		m_source2 = iINVALID;
		m_valid = decode(word0, word1);
	}
<<<<<<< HEAD
	bool decode(const UINT16 word0, const UINT16 word1)
=======
	bool decode(const uint16_t word0, const uint16_t word1) override
>>>>>>> upstream/master
	{
		decode_QQF_special_table(BITSn(word0,0x0003), BITSn(word0,0x0008),
									m_source, m_source2, m_destination);

		decode_s_table(BITSn(word0,0x0004), m_mnem);
		return true;
	}
<<<<<<< HEAD
	void disassemble(std::string& retString) const
=======
	void disassemble(std::string& retString) const override
>>>>>>> upstream/master
	{
		std::string opcode = "mpy" + opMnemonicAsString(m_mnem);

		retString = opcode + " " +
					regIdAsString(m_source) + "," +
					regIdAsString(m_source2) + "," + regIdAsString(m_destination);
		// NEW // sprintf(opcode_str, "mpy(%s)", A);
	}
<<<<<<< HEAD
	void evaluate(dsp56k_core* cpustate) {}
	size_t size() const { return 1; }
	size_t accumulatorBitsModified() const { return BM_HIGH | BM_MIDDLE | BM_LOW; }
=======
	void evaluate(dsp56k_core* cpustate) override {}
	size_t size() const override { return 1; }
	size_t accumulatorBitsModified() const override { return BM_HIGH | BM_MIDDLE | BM_LOW; }
>>>>>>> upstream/master

private:
	op_mnem m_mnem;
	reg_id m_source2;
};

// NEG : .... .... 0110 F000 : A-166 ///////////////////////////////////////////
class Neg: public Instruction
{
public:
<<<<<<< HEAD
	Neg(const Opcode* oco, const UINT16 word0, const UINT16 word1) : Instruction(oco)
	{
		m_valid = decode(word0, word1);
	}
	bool decode(const UINT16 word0, const UINT16 word1)
=======
	Neg(const Opcode* oco, const uint16_t word0, const uint16_t word1) : Instruction(oco)
	{
		m_valid = decode(word0, word1);
	}
	bool decode(const uint16_t word0, const uint16_t word1) override
>>>>>>> upstream/master
	{
		decode_F_table(BITSn(word0,0x08), m_destination);
		return true;
	}
<<<<<<< HEAD
	void disassemble(std::string& retString) const
	{
		retString = "neg " + regIdAsString(m_destination);
	}
	void evaluate(dsp56k_core* cpustate) {}
	size_t size() const { return 1; }
	size_t accumulatorBitsModified() const { return BM_HIGH | BM_MIDDLE | BM_LOW; }
=======
	void disassemble(std::string& retString) const override
	{
		retString = "neg " + regIdAsString(m_destination);
	}
	void evaluate(dsp56k_core* cpustate) override {}
	size_t size() const override { return 1; }
	size_t accumulatorBitsModified() const override { return BM_HIGH | BM_MIDDLE | BM_LOW; }
>>>>>>> upstream/master
};

// NEGC : 0001 0101 0110 F000 : A-168 //////////////////////////////////////////
class Negc: public Instruction
{
public:
<<<<<<< HEAD
	Negc(const Opcode* oco, const UINT16 word0, const UINT16 word1) : Instruction(oco)
	{
		m_valid = decode(word0, word1);
	}
	bool decode(const UINT16 word0, const UINT16 word1)
=======
	Negc(const Opcode* oco, const uint16_t word0, const uint16_t word1) : Instruction(oco)
	{
		m_valid = decode(word0, word1);
	}
	bool decode(const uint16_t word0, const uint16_t word1) override
>>>>>>> upstream/master
	{
		decode_F_table(BITSn(word0,0x0008), m_destination);
		return true;
	}
<<<<<<< HEAD
	void disassemble(std::string& retString) const
	{
		retString = "negc " + regIdAsString(m_destination);
	}
	void evaluate(dsp56k_core* cpustate) {}
	size_t size() const { return 1; }
	size_t accumulatorBitsModified() const { return BM_HIGH | BM_MIDDLE | BM_LOW; }
=======
	void disassemble(std::string& retString) const override
	{
		retString = "negc " + regIdAsString(m_destination);
	}
	void evaluate(dsp56k_core* cpustate) override {}
	size_t size() const override { return 1; }
	size_t accumulatorBitsModified() const override { return BM_HIGH | BM_MIDDLE | BM_LOW; }
>>>>>>> upstream/master
};

// NOP : 0000 0000 0000 0000 : A-170 ///////////////////////////////////////////
class Nop: public Instruction
{
public:
<<<<<<< HEAD
	Nop(const Opcode* oco, const UINT16 word0, const UINT16 word1) : Instruction(oco)
	{
		m_valid = decode(word0, word1);
	}
	bool decode(const UINT16 word0, const UINT16 word1)
	{
		return true;
	}
	void disassemble(std::string& retString) const
	{
		retString = "nop";
	}
	void evaluate(dsp56k_core* cpustate) {}
	size_t size() const { return 1; }
	size_t accumulatorBitsModified() const { return BM_HIGH | BM_MIDDLE | BM_LOW; }
=======
	Nop(const Opcode* oco, const uint16_t word0, const uint16_t word1) : Instruction(oco)
	{
		m_valid = decode(word0, word1);
	}
	bool decode(const uint16_t word0, const uint16_t word1) override
	{
		return true;
	}
	void disassemble(std::string& retString) const override
	{
		retString = "nop";
	}
	void evaluate(dsp56k_core* cpustate) override {}
	size_t size() const override { return 1; }
	size_t accumulatorBitsModified() const override { return BM_HIGH | BM_MIDDLE | BM_LOW; }
>>>>>>> upstream/master
};

// NORM : 0001 0101 0010 F0RR : A-172 //////////////////////////////////////////
class Norm: public Instruction
{
public:
<<<<<<< HEAD
	Norm(const Opcode* oco, const UINT16 word0, const UINT16 word1) : Instruction(oco)
	{
		m_valid = decode(word0, word1);
	}
	bool decode(const UINT16 word0, const UINT16 word1)
=======
	Norm(const Opcode* oco, const uint16_t word0, const uint16_t word1) : Instruction(oco)
	{
		m_valid = decode(word0, word1);
	}
	bool decode(const uint16_t word0, const uint16_t word1) override
>>>>>>> upstream/master
	{
		decode_F_table(BITSn(word0,0x0008), m_destination);

		decode_RR_table(BITSn(word0,0x0003), m_source);
		return true;
	}
<<<<<<< HEAD
	void disassemble(std::string& retString) const
	{
		retString = "norm " + regIdAsString(m_source) + "," + regIdAsString(m_destination);
	}
	void evaluate(dsp56k_core* cpustate) {}
	size_t size() const { return 1; }
	size_t accumulatorBitsModified() const { return BM_HIGH | BM_MIDDLE | BM_LOW; }
=======
	void disassemble(std::string& retString) const override
	{
		retString = "norm " + regIdAsString(m_source) + "," + regIdAsString(m_destination);
	}
	void evaluate(dsp56k_core* cpustate) override {}
	size_t size() const override { return 1; }
	size_t accumulatorBitsModified() const override { return BM_HIGH | BM_MIDDLE | BM_LOW; }
>>>>>>> upstream/master
};

// NOT : .... .... 0110 F001 : A-174 ///////////////////////////////////////////
class Not: public Instruction
{
public:
<<<<<<< HEAD
	Not(const Opcode* oco, const UINT16 word0, const UINT16 word1) : Instruction(oco)
	{
		m_valid = decode(word0, word1);
	}
	bool decode(const UINT16 word0, const UINT16 word1)
=======
	Not(const Opcode* oco, const uint16_t word0, const uint16_t word1) : Instruction(oco)
	{
		m_valid = decode(word0, word1);
	}
	bool decode(const uint16_t word0, const uint16_t word1) override
>>>>>>> upstream/master
	{
		decode_F_table(BITSn(word0,0x08), m_destination);
		return true;
	}
<<<<<<< HEAD
	void disassemble(std::string& retString) const
	{
		retString = "not " + regIdAsString(m_destination);
	}
	void evaluate(dsp56k_core* cpustate) {}
	size_t size() const { return 1; }
	size_t accumulatorBitsModified() const { return BM_HIGH | BM_MIDDLE; }
=======
	void disassemble(std::string& retString) const override
	{
		retString = "not " + regIdAsString(m_destination);
	}
	void evaluate(dsp56k_core* cpustate) override {}
	size_t size() const override { return 1; }
	size_t accumulatorBitsModified() const override { return BM_HIGH | BM_MIDDLE; }
>>>>>>> upstream/master
};

// OR : .... .... 0010 F1JJ : A-176 ////////////////////////////////////////////
class Or: public Instruction
{
public:
<<<<<<< HEAD
	Or(const Opcode* oco, const UINT16 word0, const UINT16 word1) : Instruction(oco)
	{
		m_valid = decode(word0, word1);
	}
	bool decode(const UINT16 word0, const UINT16 word1)
=======
	Or(const Opcode* oco, const uint16_t word0, const uint16_t word1) : Instruction(oco)
	{
		m_valid = decode(word0, word1);
	}
	bool decode(const uint16_t word0, const uint16_t word1) override
>>>>>>> upstream/master
	{
		decode_JJF_table(BITSn(word0,0x03),BITSn(word0,0x08),
							m_source, m_destination);
		return true;
	}
<<<<<<< HEAD
	void disassemble(std::string& retString) const
	{
		retString = "or " + regIdAsString(m_source) + "," + regIdAsString(m_destination);
	}
	void evaluate(dsp56k_core* cpustate) {}
	size_t size() const { return 1; }
	size_t accumulatorBitsModified() const { return BM_HIGH | BM_MIDDLE; }
=======
	void disassemble(std::string& retString) const override
	{
		retString = "or " + regIdAsString(m_source) + "," + regIdAsString(m_destination);
	}
	void evaluate(dsp56k_core* cpustate) override {}
	size_t size() const override { return 1; }
	size_t accumulatorBitsModified() const override { return BM_HIGH | BM_MIDDLE; }
>>>>>>> upstream/master
};

// ORI : 0001 1EE1 iiii iiii : A-178 ///////////////////////////////////////////
class Ori: public Instruction
{
public:
<<<<<<< HEAD
	Ori(const Opcode* oco, const UINT16 word0, const UINT16 word1) : Instruction(oco)
=======
	Ori(const Opcode* oco, const uint16_t word0, const uint16_t word1) : Instruction(oco)
>>>>>>> upstream/master
	{
		m_immediate = 0;
		m_valid = decode(word0, word1);
	}
<<<<<<< HEAD
	bool decode(const UINT16 word0, const UINT16 word1)
=======
	bool decode(const uint16_t word0, const uint16_t word1) override
>>>>>>> upstream/master
	{
		m_immediate = BITSn(word0,0x00ff);
		decode_EE_table(BITSn(word0,0x0600), m_destination);
		return true;
	}
<<<<<<< HEAD
	void disassemble(std::string& retString) const
=======
	void disassemble(std::string& retString) const override
>>>>>>> upstream/master
	{
		char temp[32];
		sprintf(temp, "#$%x", m_immediate);
		// NEW // sprintf(temp, "#$%02x", BITSn(word0,0x00ff));
		retString = "ori " + std::string(temp) + "," + regIdAsString(m_destination);
		// NEW // sprintf(opcode_str, "or(i)");
	}
<<<<<<< HEAD
	void evaluate(dsp56k_core* cpustate) {}
	size_t size() const { return 1; }
	size_t accumulatorBitsModified() const { return BM_HIGH | BM_MIDDLE | BM_LOW; }

private:
	UINT8 m_immediate;
=======
	void evaluate(dsp56k_core* cpustate) override {}
	size_t size() const override { return 1; }
	size_t accumulatorBitsModified() const override { return BM_HIGH | BM_MIDDLE | BM_LOW; }

private:
	uint8_t m_immediate;
>>>>>>> upstream/master
};

// REP : 0000 0000 111- --RR : A-180 ///////////////////////////////////////////
class Rep: public Instruction
{
public:
<<<<<<< HEAD
	Rep(const Opcode* oco, const UINT16 word0, const UINT16 word1) : Instruction(oco)
	{
		m_valid = decode(word0, word1);
	}
	bool decode(const UINT16 word0, const UINT16 word1)
=======
	Rep(const Opcode* oco, const uint16_t word0, const uint16_t word1) : Instruction(oco)
	{
		m_valid = decode(word0, word1);
	}
	bool decode(const uint16_t word0, const uint16_t word1) override
>>>>>>> upstream/master
	{
		decode_RR_table(BITSn(word0,0x0003), m_source);
		return true;
	}
<<<<<<< HEAD
	void disassemble(std::string& retString) const
=======
	void disassemble(std::string& retString) const override
>>>>>>> upstream/master
	{
		char temp[32];
		sprintf(temp, "X:(%s)", regIdAsString(m_source).c_str());
		retString = "rep " + std::string(temp);
	}
<<<<<<< HEAD
	void evaluate(dsp56k_core* cpustate) {}
	size_t size() const { return 1; }
	size_t accumulatorBitsModified() const { return BM_HIGH | BM_MIDDLE | BM_LOW; }
=======
	void evaluate(dsp56k_core* cpustate) override {}
	size_t size() const override { return 1; }
	size_t accumulatorBitsModified() const override { return BM_HIGH | BM_MIDDLE | BM_LOW; }
>>>>>>> upstream/master
};

// REP : 0000 1111 iiii iiii : A-180 ///////////////////////////////////////////
class Rep_2: public Instruction
{
public:
<<<<<<< HEAD
	Rep_2(const Opcode* oco, const UINT16 word0, const UINT16 word1) : Instruction(oco)
=======
	Rep_2(const Opcode* oco, const uint16_t word0, const uint16_t word1) : Instruction(oco)
>>>>>>> upstream/master
	{
		m_immediate = 0;
		m_valid = decode(word0, word1);
	}
<<<<<<< HEAD
	bool decode(const UINT16 word0, const UINT16 word1)
=======
	bool decode(const uint16_t word0, const uint16_t word1) override
>>>>>>> upstream/master
	{
		m_immediate = BITSn(word0,0x00ff);
		return true;
	}
<<<<<<< HEAD
	void disassemble(std::string& retString) const
=======
	void disassemble(std::string& retString) const override
>>>>>>> upstream/master
	{
		char temp[32];
		sprintf(temp, "#$%x", m_immediate);
		// NEW // sprintf(temp, "#$%02x (%d)", BITSn(word0,0x00ff), BITSn(word0,0x00ff));
		retString = "rep " + std::string(temp);
	}
<<<<<<< HEAD
	void evaluate(dsp56k_core* cpustate) {}
	size_t size() const { return 1; }
	size_t accumulatorBitsModified() const { return BM_HIGH | BM_MIDDLE | BM_LOW; }

private:
	UINT8 m_immediate;
=======
	void evaluate(dsp56k_core* cpustate) override {}
	size_t size() const override { return 1; }
	size_t accumulatorBitsModified() const override { return BM_HIGH | BM_MIDDLE | BM_LOW; }

private:
	uint8_t m_immediate;
>>>>>>> upstream/master
};

// REP : 0000 0100 001D DDDD : A-180 ///////////////////////////////////////////
class Rep_3: public Instruction
{
public:
<<<<<<< HEAD
	Rep_3(const Opcode* oco, const UINT16 word0, const UINT16 word1) : Instruction(oco)
	{
		m_valid = decode(word0, word1);
	}
	bool decode(const UINT16 word0, const UINT16 word1)
=======
	Rep_3(const Opcode* oco, const uint16_t word0, const uint16_t word1) : Instruction(oco)
	{
		m_valid = decode(word0, word1);
	}
	bool decode(const uint16_t word0, const uint16_t word1) override
>>>>>>> upstream/master
	{
		decode_DDDDD_table(BITSn(word0,0x001f), m_source);
		if (m_source == iINVALID) return false;
		return true;
	}
<<<<<<< HEAD
	void disassemble(std::string& retString) const
	{
		retString = "rep " + regIdAsString(m_source);
	}
	void evaluate(dsp56k_core* cpustate) {}
	size_t size() const { return 1; }
	size_t accumulatorBitsModified() const { return BM_HIGH | BM_MIDDLE | BM_LOW; }
=======
	void disassemble(std::string& retString) const override
	{
		retString = "rep " + regIdAsString(m_source);
	}
	void evaluate(dsp56k_core* cpustate) override {}
	size_t size() const override { return 1; }
	size_t accumulatorBitsModified() const override { return BM_HIGH | BM_MIDDLE | BM_LOW; }
>>>>>>> upstream/master
};

// REPcc : 0000 0001 0101 cccc : A-184 /////////////////////////////////////////
class Repcc: public Instruction
{
public:
<<<<<<< HEAD
	Repcc(const Opcode* oco, const UINT16 word0, const UINT16 word1) : Instruction(oco)
=======
	Repcc(const Opcode* oco, const uint16_t word0, const uint16_t word1) : Instruction(oco)
>>>>>>> upstream/master
	{
		m_mnem = oINVALID;
		m_valid = decode(word0, word1);
	}
<<<<<<< HEAD
	bool decode(const UINT16 word0, const UINT16 word1)
=======
	bool decode(const uint16_t word0, const uint16_t word1) override
>>>>>>> upstream/master
	{
		decode_cccc_table(BITSn(word0,0x000f), m_mnem);
		return true;
	}
<<<<<<< HEAD
	void disassemble(std::string& retString) const
=======
	void disassemble(std::string& retString) const override
>>>>>>> upstream/master
	{
		std::string opcode = "rep" + opMnemonicAsString(m_mnem);
		retString = opcode;
		// NEW // sprintf(opcode_str, "rep.%s", M);
	}
<<<<<<< HEAD
	void evaluate(dsp56k_core* cpustate) {}
	size_t size() const { return 1; }
	size_t accumulatorBitsModified() const { return BM_HIGH | BM_MIDDLE | BM_LOW; }
=======
	void evaluate(dsp56k_core* cpustate) override {}
	size_t size() const override { return 1; }
	size_t accumulatorBitsModified() const override { return BM_HIGH | BM_MIDDLE | BM_LOW; }
>>>>>>> upstream/master

private:
	op_mnem m_mnem;
};

// RESET : 0000 0000 0000 1000 : A-186 /////////////////////////////////////////
class Reset: public Instruction
{
public:
<<<<<<< HEAD
	Reset(const Opcode* oco, const UINT16 word0, const UINT16 word1) : Instruction(oco)
	{
		m_valid = decode(word0, word1);
	}
	bool decode(const UINT16 word0, const UINT16 word1)
	{
		return true;
	}
	void disassemble(std::string& retString) const
	{
		retString = "reset";
	}
	void evaluate(dsp56k_core* cpustate) {}
	size_t size() const { return 1; }
	size_t accumulatorBitsModified() const { return BM_HIGH | BM_MIDDLE | BM_LOW; }
=======
	Reset(const Opcode* oco, const uint16_t word0, const uint16_t word1) : Instruction(oco)
	{
		m_valid = decode(word0, word1);
	}
	bool decode(const uint16_t word0, const uint16_t word1) override
	{
		return true;
	}
	void disassemble(std::string& retString) const override
	{
		retString = "reset";
	}
	void evaluate(dsp56k_core* cpustate) override {}
	size_t size() const override { return 1; }
	size_t accumulatorBitsModified() const override { return BM_HIGH | BM_MIDDLE | BM_LOW; }
>>>>>>> upstream/master
};

// RND : .... .... 0010 F000 : A-188 ///////////////////////////////////////////
class Rnd: public Instruction
{
public:
<<<<<<< HEAD
	Rnd(const Opcode* oco, const UINT16 word0, const UINT16 word1) : Instruction(oco)
	{
		m_valid = decode(word0, word1);
	}
	bool decode(const UINT16 word0, const UINT16 word1)
=======
	Rnd(const Opcode* oco, const uint16_t word0, const uint16_t word1) : Instruction(oco)
	{
		m_valid = decode(word0, word1);
	}
	bool decode(const uint16_t word0, const uint16_t word1) override
>>>>>>> upstream/master
	{
		decode_F_table(BITSn(word0,0x08), m_destination);
		return true;
	}
<<<<<<< HEAD
	void disassemble(std::string& retString) const
	{
		retString = "rnd " + regIdAsString(m_destination);
	}
	void evaluate(dsp56k_core* cpustate) {}
	size_t size() const { return 1; }
	size_t accumulatorBitsModified() const { return BM_HIGH | BM_MIDDLE | BM_LOW; }
=======
	void disassemble(std::string& retString) const override
	{
		retString = "rnd " + regIdAsString(m_destination);
	}
	void evaluate(dsp56k_core* cpustate) override {}
	size_t size() const override { return 1; }
	size_t accumulatorBitsModified() const override { return BM_HIGH | BM_MIDDLE | BM_LOW; }
>>>>>>> upstream/master
};

// ROL : .... .... 0111 F011 : A-190 ///////////////////////////////////////////
class Rol: public Instruction
{
public:
<<<<<<< HEAD
	Rol(const Opcode* oco, const UINT16 word0, const UINT16 word1) : Instruction(oco)
	{
		m_valid = decode(word0, word1);
	}
	bool decode(const UINT16 word0, const UINT16 word1)
=======
	Rol(const Opcode* oco, const uint16_t word0, const uint16_t word1) : Instruction(oco)
	{
		m_valid = decode(word0, word1);
	}
	bool decode(const uint16_t word0, const uint16_t word1) override
>>>>>>> upstream/master
	{
		decode_F_table(BITSn(word0,0x08), m_destination);
		return true;
	}
<<<<<<< HEAD
	void disassemble(std::string& retString) const
	{
		retString = "rol " + regIdAsString(m_destination);
	}
	void evaluate(dsp56k_core* cpustate) {}
	size_t size() const { return 1; }
	size_t accumulatorBitsModified() const { return BM_HIGH | BM_MIDDLE; }
=======
	void disassemble(std::string& retString) const override
	{
		retString = "rol " + regIdAsString(m_destination);
	}
	void evaluate(dsp56k_core* cpustate) override {}
	size_t size() const override { return 1; }
	size_t accumulatorBitsModified() const override { return BM_HIGH | BM_MIDDLE; }
>>>>>>> upstream/master
};

// ROR : .... .... 0111 F010 : A-192 ///////////////////////////////////////////
class Ror: public Instruction
{
public:
<<<<<<< HEAD
	Ror(const Opcode* oco, const UINT16 word0, const UINT16 word1) : Instruction(oco)
	{
		m_valid = decode(word0, word1);
	}
	bool decode(const UINT16 word0, const UINT16 word1)
=======
	Ror(const Opcode* oco, const uint16_t word0, const uint16_t word1) : Instruction(oco)
	{
		m_valid = decode(word0, word1);
	}
	bool decode(const uint16_t word0, const uint16_t word1) override
>>>>>>> upstream/master
	{
		decode_F_table(BITSn(word0,0x08), m_destination);
		return true;
	}
<<<<<<< HEAD
	void disassemble(std::string& retString) const
	{
		retString = "ror " + regIdAsString(m_destination);
	}
	void evaluate(dsp56k_core* cpustate) {}
	size_t size() const { return 1; }
	size_t accumulatorBitsModified() const { return BM_HIGH | BM_MIDDLE; }
=======
	void disassemble(std::string& retString) const override
	{
		retString = "ror " + regIdAsString(m_destination);
	}
	void evaluate(dsp56k_core* cpustate) override {}
	size_t size() const override { return 1; }
	size_t accumulatorBitsModified() const override { return BM_HIGH | BM_MIDDLE; }
>>>>>>> upstream/master
};

// RTI : 0000 0000 0000 0111 : A-194 ///////////////////////////////////////////
class Rti: public Instruction
{
public:
<<<<<<< HEAD
	Rti(const Opcode* oco, const UINT16 word0, const UINT16 word1) : Instruction(oco)
	{
		m_valid = decode(word0, word1);
	}
	bool decode(const UINT16 word0, const UINT16 word1)
	{
		return true;
	}
	void disassemble(std::string& retString) const
	{
		retString = "rti";
	}
	void evaluate(dsp56k_core* cpustate) {}
	size_t size() const { return 1; }
	size_t accumulatorBitsModified() const { return BM_HIGH | BM_MIDDLE | BM_LOW; }
	size_t flags() const { return DASMFLAG_STEP_OUT; }
=======
	Rti(const Opcode* oco, const uint16_t word0, const uint16_t word1) : Instruction(oco)
	{
		m_valid = decode(word0, word1);
	}
	bool decode(const uint16_t word0, const uint16_t word1) override
	{
		return true;
	}
	void disassemble(std::string& retString) const override
	{
		retString = "rti";
	}
	void evaluate(dsp56k_core* cpustate) override {}
	size_t size() const override { return 1; }
	size_t accumulatorBitsModified() const override { return BM_HIGH | BM_MIDDLE | BM_LOW; }
	size_t flags() const override { return DASMFLAG_STEP_OUT; }
>>>>>>> upstream/master
};

// RTS : 0000 0000 0000 0110 : A-196 ///////////////////////////////////////////
class Rts: public Instruction
{
public:
<<<<<<< HEAD
	Rts(const Opcode* oco, const UINT16 word0, const UINT16 word1) : Instruction(oco)
	{
		m_valid = decode(word0, word1);
	}
	bool decode(const UINT16 word0, const UINT16 word1)
	{
		return true;
	}
	void disassemble(std::string& retString) const
	{
		retString = "rts";
	}
	void evaluate(dsp56k_core* cpustate) {}
	size_t size() const { return 1; }
	size_t accumulatorBitsModified() const { return BM_HIGH | BM_MIDDLE | BM_LOW; }
	size_t flags() const { return DASMFLAG_STEP_OUT; }
=======
	Rts(const Opcode* oco, const uint16_t word0, const uint16_t word1) : Instruction(oco)
	{
		m_valid = decode(word0, word1);
	}
	bool decode(const uint16_t word0, const uint16_t word1) override
	{
		return true;
	}
	void disassemble(std::string& retString) const override
	{
		retString = "rts";
	}
	void evaluate(dsp56k_core* cpustate) override {}
	size_t size() const override { return 1; }
	size_t accumulatorBitsModified() const override { return BM_HIGH | BM_MIDDLE | BM_LOW; }
	size_t flags() const override { return DASMFLAG_STEP_OUT; }
>>>>>>> upstream/master
};

// SBC : .... .... 0101 F01J : A-198 ///////////////////////////////////////////
class Sbc: public Instruction
{
public:
<<<<<<< HEAD
	Sbc(const Opcode* oco, const UINT16 word0, const UINT16 word1) : Instruction(oco)
	{
		m_valid = decode(word0, word1);
	}
	bool decode(const UINT16 word0, const UINT16 word1)
=======
	Sbc(const Opcode* oco, const uint16_t word0, const uint16_t word1) : Instruction(oco)
	{
		m_valid = decode(word0, word1);
	}
	bool decode(const uint16_t word0, const uint16_t word1) override
>>>>>>> upstream/master
	{
		decode_JF_table(BITSn(word0,0x01), BITSn(word0,0x08),
						m_source, m_destination);
		return true;
	}
<<<<<<< HEAD
	void disassemble(std::string& retString) const
	{
		retString = "sbc " + regIdAsString(m_source) + "," + regIdAsString(m_destination);
	}
	void evaluate(dsp56k_core* cpustate) {}
	size_t size() const { return 1; }
	size_t accumulatorBitsModified() const { return BM_HIGH | BM_MIDDLE | BM_LOW; }
=======
	void disassemble(std::string& retString) const override
	{
		retString = "sbc " + regIdAsString(m_source) + "," + regIdAsString(m_destination);
	}
	void evaluate(dsp56k_core* cpustate) override {}
	size_t size() const override { return 1; }
	size_t accumulatorBitsModified() const override { return BM_HIGH | BM_MIDDLE | BM_LOW; }
>>>>>>> upstream/master
};

// STOP : 0000 0000 0000 1010 : A-200 //////////////////////////////////////////
class Stop: public Instruction
{
public:
<<<<<<< HEAD
	Stop(const Opcode* oco, const UINT16 word0, const UINT16 word1) : Instruction(oco)
	{
		m_valid = decode(word0, word1);
	}
	bool decode(const UINT16 word0, const UINT16 word1)
	{
		return true;
	}
	void disassemble(std::string& retString) const
	{
		retString = "stop";
	}
	void evaluate(dsp56k_core* cpustate) {}
	size_t size() const { return 1; }
	size_t accumulatorBitsModified() const { return BM_HIGH | BM_MIDDLE | BM_LOW; }
=======
	Stop(const Opcode* oco, const uint16_t word0, const uint16_t word1) : Instruction(oco)
	{
		m_valid = decode(word0, word1);
	}
	bool decode(const uint16_t word0, const uint16_t word1) override
	{
		return true;
	}
	void disassemble(std::string& retString) const override
	{
		retString = "stop";
	}
	void evaluate(dsp56k_core* cpustate) override {}
	size_t size() const override { return 1; }
	size_t accumulatorBitsModified() const override { return BM_HIGH | BM_MIDDLE | BM_LOW; }
>>>>>>> upstream/master
};

// SUB : .... .... 0100 FJJJ : A-202 ///////////////////////////////////////////
class Sub: public Instruction
{
public:
<<<<<<< HEAD
	Sub(const Opcode* oco, const UINT16 word0, const UINT16 word1) : Instruction(oco)
	{
		m_valid = decode(word0, word1);
	}
	bool decode(const UINT16 word0, const UINT16 word1)
=======
	Sub(const Opcode* oco, const uint16_t word0, const uint16_t word1) : Instruction(oco)
	{
		m_valid = decode(word0, word1);
	}
	bool decode(const uint16_t word0, const uint16_t word1) override
>>>>>>> upstream/master
	{
		decode_JJJF_table(BITSn(word0,0x07), BITSn(word0,0x08),
							m_source, m_destination);
		return true;
	}
<<<<<<< HEAD
	void disassemble(std::string& retString) const
	{
		retString = "sub " + regIdAsString(m_source) + "," + regIdAsString(m_destination);
	}
	void evaluate(dsp56k_core* cpustate) {}
	size_t size() const { return 1; }
	size_t accumulatorBitsModified() const { return BM_HIGH | BM_MIDDLE | BM_LOW; }
=======
	void disassemble(std::string& retString) const override
	{
		retString = "sub " + regIdAsString(m_source) + "," + regIdAsString(m_destination);
	}
	void evaluate(dsp56k_core* cpustate) override {}
	size_t size() const override { return 1; }
	size_t accumulatorBitsModified() const override { return BM_HIGH | BM_MIDDLE | BM_LOW; }
>>>>>>> upstream/master
};

// SUB : 011m mKKK 0rru Fuuu : A-202 ///////////////////////////////////////////
class Sub_2: public Instruction
{
public:
<<<<<<< HEAD
	Sub_2(const Opcode* oco, const UINT16 word0, const UINT16 word1) : Instruction(oco)
=======
	Sub_2(const Opcode* oco, const uint16_t word0, const uint16_t word1) : Instruction(oco)
>>>>>>> upstream/master
	{
		m_opcode = "";
		m_valid = decode(word0, word1);
	}
<<<<<<< HEAD
	bool decode(const UINT16 word0, const UINT16 word1)
=======
	bool decode(const uint16_t word0, const uint16_t word1) override
>>>>>>> upstream/master
	{
		decode_uuuuF_table(BITSn(word0,0x17), BITSn(word0,0x08),
							m_opcode, m_source, m_destination);

		// TODO // m_opcode = "sub";
		return true;
	}
<<<<<<< HEAD
	void disassemble(std::string& retString) const
	{
		retString = m_opcode + " " + regIdAsString(m_source) + "," + regIdAsString(m_destination);
	}
	void evaluate(dsp56k_core* cpustate) {}
	size_t size() const { return 1; }
	size_t accumulatorBitsModified() const { return BM_HIGH | BM_MIDDLE | BM_LOW; }
=======
	void disassemble(std::string& retString) const override
	{
		retString = m_opcode + " " + regIdAsString(m_source) + "," + regIdAsString(m_destination);
	}
	void evaluate(dsp56k_core* cpustate) override {}
	size_t size() const override { return 1; }
	size_t accumulatorBitsModified() const override { return BM_HIGH | BM_MIDDLE | BM_LOW; }
>>>>>>> upstream/master

private:
	std::string m_opcode;
};

// SUBL : .... .... 0100 F001 : A-204 //////////////////////////////////////////
class Subl: public Instruction
{
public:
<<<<<<< HEAD
	Subl(const Opcode* oco, const UINT16 word0, const UINT16 word1) : Instruction(oco)
	{
		m_valid = decode(word0, word1);
	}
	bool decode(const UINT16 word0, const UINT16 word1)
=======
	Subl(const Opcode* oco, const uint16_t word0, const uint16_t word1) : Instruction(oco)
	{
		m_valid = decode(word0, word1);
	}
	bool decode(const uint16_t word0, const uint16_t word1) override
>>>>>>> upstream/master
	{
		/* There is only one option for the F table.  This is a very strange opcode. */
		if (!BITSn(word0,0x0008))
		{
			m_source = iB;
			m_destination = iA;
		}
		else
		{
			m_source = iA;
			m_destination = iB;
		}
		return true;
	}
<<<<<<< HEAD
	void disassemble(std::string& retString) const
	{
		retString = "subl " + regIdAsString(m_source) + "," + regIdAsString(m_destination);
	}
	void evaluate(dsp56k_core* cpustate) {}
	size_t size() const { return 1; }
	size_t accumulatorBitsModified() const { return BM_HIGH | BM_MIDDLE | BM_LOW; }
=======
	void disassemble(std::string& retString) const override
	{
		retString = "subl " + regIdAsString(m_source) + "," + regIdAsString(m_destination);
	}
	void evaluate(dsp56k_core* cpustate) override {}
	size_t size() const override { return 1; }
	size_t accumulatorBitsModified() const override { return BM_HIGH | BM_MIDDLE | BM_LOW; }
>>>>>>> upstream/master
};

// SWAP : 0001 0101 0111 F001 : A-206 //////////////////////////////////////////
class Swap: public Instruction
{
public:
<<<<<<< HEAD
	Swap(const Opcode* oco, const UINT16 word0, const UINT16 word1) : Instruction(oco)
	{
		m_valid = decode(word0, word1);
	}
	bool decode(const UINT16 word0, const UINT16 word1)
=======
	Swap(const Opcode* oco, const uint16_t word0, const uint16_t word1) : Instruction(oco)
	{
		m_valid = decode(word0, word1);
	}
	bool decode(const uint16_t word0, const uint16_t word1) override
>>>>>>> upstream/master
	{
		decode_F_table(BITSn(word0,0x0008), m_destination);
		return true;
	}
<<<<<<< HEAD
	void disassemble(std::string& retString) const
	{
		retString = "swap " + regIdAsString(m_destination);
	}
	void evaluate(dsp56k_core* cpustate) {}
	size_t size() const { return 1; }
	size_t accumulatorBitsModified() const { return BM_HIGH | BM_MIDDLE | BM_LOW; }
=======
	void disassemble(std::string& retString) const override
	{
		retString = "swap " + regIdAsString(m_destination);
	}
	void evaluate(dsp56k_core* cpustate) override {}
	size_t size() const override { return 1; }
	size_t accumulatorBitsModified() const override { return BM_HIGH | BM_MIDDLE | BM_LOW; }
>>>>>>> upstream/master
};

// SWI : 0000 0000 0000 0101 : A-208 ///////////////////////////////////////////
class Swi: public Instruction
{
public:
<<<<<<< HEAD
	Swi(const Opcode* oco, const UINT16 word0, const UINT16 word1) : Instruction(oco)
	{
		m_valid = decode(word0, word1);
	}
	bool decode(const UINT16 word0, const UINT16 word1)
	{
		return true;
	}
	void disassemble(std::string& retString) const
	{
		retString = "swi";
	}
	void evaluate(dsp56k_core* cpustate) {}
	size_t size() const { return 1; }
	size_t accumulatorBitsModified() const { return BM_HIGH | BM_MIDDLE | BM_LOW; }
=======
	Swi(const Opcode* oco, const uint16_t word0, const uint16_t word1) : Instruction(oco)
	{
		m_valid = decode(word0, word1);
	}
	bool decode(const uint16_t word0, const uint16_t word1) override
	{
		return true;
	}
	void disassemble(std::string& retString) const override
	{
		retString = "swi";
	}
	void evaluate(dsp56k_core* cpustate) override {}
	size_t size() const override { return 1; }
	size_t accumulatorBitsModified() const override { return BM_HIGH | BM_MIDDLE | BM_LOW; }
>>>>>>> upstream/master
};

// Tcc : 0001 00cc ccTT Fh0h : A-210 ///////////////////////////////////////////
class Tcc: public Instruction
{
public:
<<<<<<< HEAD
	Tcc(const Opcode* oco, const UINT16 word0, const UINT16 word1) : Instruction(oco)
=======
	Tcc(const Opcode* oco, const uint16_t word0, const uint16_t word1) : Instruction(oco)
>>>>>>> upstream/master
	{
		m_mnem = oINVALID;
		m_destination2 = iINVALID;
		m_valid = decode(word0, word1);
	}
<<<<<<< HEAD
	bool decode(const UINT16 word0, const UINT16 word1)
=======
	bool decode(const uint16_t word0, const uint16_t word1) override
>>>>>>> upstream/master
	{
		decode_h0hF_table(BITSn(word0,0x0007),BITSn(word0,0x0008),
							m_source, m_destination);

		decode_RR_table(BITSn(word0,0x0030), m_destination2);

		decode_cccc_table(BITSn(word0,0x03c0), m_mnem);
		if (m_source != m_destination)
			return true;
		if (m_destination2 != iR0)
			return true;

		return false;
	}
<<<<<<< HEAD
	void disassemble(std::string& retString) const
=======
	void disassemble(std::string& retString) const override
>>>>>>> upstream/master
	{
		std::string opcode = "t" + opMnemonicAsString(m_mnem);
		// NEW // sprintf(opcode_str, "t.%s", M);

		retString = opcode;
		if (m_source != m_destination)
			retString += std::string(" ") + regIdAsString(m_source) + "," + regIdAsString(m_destination);

		if (m_destination2 != iR0)
			retString += std::string(" R0,") + regIdAsString(m_destination2);
	}
<<<<<<< HEAD
	void evaluate(dsp56k_core* cpustate) {}
	size_t size() const { return 1; }
	size_t accumulatorBitsModified() const { return BM_HIGH | BM_MIDDLE | BM_LOW; }
=======
	void evaluate(dsp56k_core* cpustate) override {}
	size_t size() const override { return 1; }
	size_t accumulatorBitsModified() const override { return BM_HIGH | BM_MIDDLE | BM_LOW; }
>>>>>>> upstream/master

private:
	op_mnem m_mnem;
	reg_id m_destination2;
};

// TFR : .... .... 0001 FJJJ : A-212 ///////////////////////////////////////////
class Tfr: public Instruction
{
public:
<<<<<<< HEAD
	Tfr(const Opcode* oco, const UINT16 word0, const UINT16 word1) : Instruction(oco)
	{
		m_valid = decode(word0, word1);
	}
	bool decode(const UINT16 word0, const UINT16 word1)
=======
	Tfr(const Opcode* oco, const uint16_t word0, const uint16_t word1) : Instruction(oco)
	{
		m_valid = decode(word0, word1);
	}
	bool decode(const uint16_t word0, const uint16_t word1) override
>>>>>>> upstream/master
	{
		decode_JJJF_table(BITSn(word0,0x07), BITSn(word0,0x08),
							m_source, m_destination);
		return true;
	}
<<<<<<< HEAD
	void disassemble(std::string& retString) const
	{
		retString = "tfr " + regIdAsString(m_source) + "," + regIdAsString(m_destination);
	}
	void evaluate(dsp56k_core* cpustate) {}
	size_t size() const { return 1; }
	size_t accumulatorBitsModified() const { return BM_HIGH | BM_MIDDLE | BM_LOW; }
=======
	void disassemble(std::string& retString) const override
	{
		retString = "tfr " + regIdAsString(m_source) + "," + regIdAsString(m_destination);
	}
	void evaluate(dsp56k_core* cpustate) override {}
	size_t size() const override { return 1; }
	size_t accumulatorBitsModified() const override { return BM_HIGH | BM_MIDDLE | BM_LOW; }
>>>>>>> upstream/master
};

// TFR : 011m mKKK 0rr1 F0DD : A-212 ///////////////////////////////////////////
class Tfr_2: public Instruction
{
public:
<<<<<<< HEAD
	Tfr_2(const Opcode* oco, const UINT16 word0, const UINT16 word1) : Instruction(oco)
	{
		m_valid = decode(word0, word1);
	}
	bool decode(const UINT16 word0, const UINT16 word1)
=======
	Tfr_2(const Opcode* oco, const uint16_t word0, const uint16_t word1) : Instruction(oco)
	{
		m_valid = decode(word0, word1);
	}
	bool decode(const uint16_t word0, const uint16_t word1) override
>>>>>>> upstream/master
	{
		decode_DDF_table(BITSn(word0,0x03), BITSn(word0,0x08),
							m_source, m_destination);
		return true;
	}
<<<<<<< HEAD
	void disassemble(std::string& retString) const
	{
		retString = "tfr " + regIdAsString(m_source) + "," + regIdAsString(m_destination);
	}
	void evaluate(dsp56k_core* cpustate) {}
	size_t size() const { return 1; }
	size_t accumulatorBitsModified() const { return BM_HIGH | BM_MIDDLE | BM_LOW; }
=======
	void disassemble(std::string& retString) const override
	{
		retString = "tfr " + regIdAsString(m_source) + "," + regIdAsString(m_destination);
	}
	void evaluate(dsp56k_core* cpustate) override {}
	size_t size() const override { return 1; }
	size_t accumulatorBitsModified() const override { return BM_HIGH | BM_MIDDLE | BM_LOW; }
>>>>>>> upstream/master
};

// TFR(2) : 0001 0101 0000 F00J : A-214 ////////////////////////////////////////
class Tfr2: public Instruction
{
public:
<<<<<<< HEAD
	Tfr2(const Opcode* oco, const UINT16 word0, const UINT16 word1) : Instruction(oco)
	{
		m_valid = decode(word0, word1);
	}
	bool decode(const UINT16 word0, const UINT16 word1)
=======
	Tfr2(const Opcode* oco, const uint16_t word0, const uint16_t word1) : Instruction(oco)
	{
		m_valid = decode(word0, word1);
	}
	bool decode(const uint16_t word0, const uint16_t word1) override
>>>>>>> upstream/master
	{
		decode_JF_table(BITSn(word0,0x0001),BITSn(word0,0x0008),
						m_destination, m_source);
		return true;
	}
<<<<<<< HEAD
	void disassemble(std::string& retString) const
	{
		retString = "tfr2 " + regIdAsString(m_source) + "," + regIdAsString(m_destination);
	}
	void evaluate(dsp56k_core* cpustate) {}
	size_t size() const { return 1; }
	size_t accumulatorBitsModified() const { return BM_HIGH | BM_MIDDLE | BM_LOW; }
=======
	void disassemble(std::string& retString) const override
	{
		retString = "tfr2 " + regIdAsString(m_source) + "," + regIdAsString(m_destination);
	}
	void evaluate(dsp56k_core* cpustate) override {}
	size_t size() const override { return 1; }
	size_t accumulatorBitsModified() const override { return BM_HIGH | BM_MIDDLE | BM_LOW; }
>>>>>>> upstream/master
};

// TFR(3) : 0010 01mW RRDD FHHH : A-216 ////////////////////////////////////////
class Tfr3: public Instruction
{
public:
<<<<<<< HEAD
	Tfr3(const Opcode* oco, const UINT16 word0, const UINT16 word1) : Instruction(oco)
=======
	Tfr3(const Opcode* oco, const uint16_t word0, const uint16_t word1) : Instruction(oco)
>>>>>>> upstream/master
	{
		m_W = 0;
		m_ea = "";
		m_SD = iINVALID;
		m_source2 = iINVALID;
		m_destination2 = iINVALID;
		m_valid = decode(word0, word1);
	}
<<<<<<< HEAD
	bool decode(const UINT16 word0, const UINT16 word1)
=======
	bool decode(const uint16_t word0, const uint16_t word1) override
>>>>>>> upstream/master
	{
		decode_DDF_table(BITSn(word0,0x0030), BITSn(word0,0x0008),
							m_destination, m_source);

		decode_HHH_table(BITSn(word0,0x0007), m_SD);
		// If the destination of the second move is the same as the first, you're invalid
		if (m_SD == m_destination && BITSn(word0,0x0100)) return false;

<<<<<<< HEAD
		INT8 rNum = BITSn(word0,0x00c0);
=======
		int8_t rNum = BITSn(word0,0x00c0);
>>>>>>> upstream/master
		assemble_ea_from_m_table(BITSn(word0,0x0200), rNum, m_ea);

		m_W = BITSn(word0,0x0100);
		return true;
	}
<<<<<<< HEAD
	void disassemble(std::string& retString) const
=======
	void disassemble(std::string& retString) const override
>>>>>>> upstream/master
	{
		std::string source2;
		std::string destination2;
		assemble_arguments_from_W_table(m_W, 'X', m_SD, m_ea, source2, destination2);
		retString = "tfr3 " +
					regIdAsString(m_source) + "," + regIdAsString(m_destination) + " " +
					source2 + "," + destination2;
	}
<<<<<<< HEAD
	void evaluate(dsp56k_core* cpustate) {}
	size_t size() const { return 1; }
	size_t accumulatorBitsModified() const { return BM_HIGH | BM_MIDDLE | BM_LOW; }

private:
	INT8 m_W;
=======
	void evaluate(dsp56k_core* cpustate) override {}
	size_t size() const override { return 1; }
	size_t accumulatorBitsModified() const override { return BM_HIGH | BM_MIDDLE | BM_LOW; }

private:
	int8_t m_W;
>>>>>>> upstream/master
	reg_id m_SD;
	std::string m_ea;
	reg_id m_source2;
	reg_id m_destination2;
};

// TST : .... .... 0010 F001 : A-218 ///////////////////////////////////////////
class Tst: public Instruction
{
public:
<<<<<<< HEAD
	Tst(const Opcode* oco, const UINT16 word0, const UINT16 word1) : Instruction(oco)
	{
		m_valid = decode(word0, word1);
	}
	bool decode(const UINT16 word0, const UINT16 word1)
=======
	Tst(const Opcode* oco, const uint16_t word0, const uint16_t word1) : Instruction(oco)
	{
		m_valid = decode(word0, word1);
	}
	bool decode(const uint16_t word0, const uint16_t word1) override
>>>>>>> upstream/master
	{
		decode_F_table(BITSn(word0,0x08), m_destination);
		return true;
	}
<<<<<<< HEAD
	void disassemble(std::string& retString) const
	{
		retString = "tst " + regIdAsString(m_destination);
	}
	void evaluate(dsp56k_core* cpustate) {}
	size_t size() const { return 1; }
	size_t accumulatorBitsModified() const { return BM_NONE; }
=======
	void disassemble(std::string& retString) const override
	{
		retString = "tst " + regIdAsString(m_destination);
	}
	void evaluate(dsp56k_core* cpustate) override {}
	size_t size() const override { return 1; }
	size_t accumulatorBitsModified() const override { return BM_NONE; }
>>>>>>> upstream/master
};

// TST(2) : 0001 0101 0001 -1DD : A-220 ////////////////////////////////////////
class Tst2: public Instruction
{
public:
<<<<<<< HEAD
	Tst2(const Opcode* oco, const UINT16 word0, const UINT16 word1) : Instruction(oco)
	{
		m_valid = decode(word0, word1);
	}
	bool decode(const UINT16 word0, const UINT16 word1)
=======
	Tst2(const Opcode* oco, const uint16_t word0, const uint16_t word1) : Instruction(oco)
	{
		m_valid = decode(word0, word1);
	}
	bool decode(const uint16_t word0, const uint16_t word1) override
>>>>>>> upstream/master
	{
		decode_DD_table(BITSn(word0,0x0003), m_source);
		return true;
	}
<<<<<<< HEAD
	void disassemble(std::string& retString) const
	{
		retString = "tst2 " + regIdAsString(m_source);
	}
	void evaluate(dsp56k_core* cpustate) {}
	size_t size() const { return 1; }
	size_t accumulatorBitsModified() const { return BM_HIGH | BM_MIDDLE | BM_LOW; }
=======
	void disassemble(std::string& retString) const override
	{
		retString = "tst2 " + regIdAsString(m_source);
	}
	void evaluate(dsp56k_core* cpustate) override {}
	size_t size() const override { return 1; }
	size_t accumulatorBitsModified() const override { return BM_HIGH | BM_MIDDLE | BM_LOW; }
>>>>>>> upstream/master
};

// WAIT : 0000 0000 0000 1011 : A-222 //////////////////////////////////////////
class Wait: public Instruction
{
public:
<<<<<<< HEAD
	Wait(const Opcode* oco, const UINT16 word0, const UINT16 word1) : Instruction(oco)
	{
		m_valid = decode(word0, word1);
	}
	bool decode(const UINT16 word0, const UINT16 word1)
	{
		return true;
	}
	void disassemble(std::string& retString) const
	{
		retString = "wait";
	}
	void evaluate(dsp56k_core* cpustate) {}
	size_t size() const { return 1; }
	size_t accumulatorBitsModified() const { return BM_HIGH | BM_MIDDLE | BM_LOW; }
=======
	Wait(const Opcode* oco, const uint16_t word0, const uint16_t word1) : Instruction(oco)
	{
		m_valid = decode(word0, word1);
	}
	bool decode(const uint16_t word0, const uint16_t word1) override
	{
		return true;
	}
	void disassemble(std::string& retString) const override
	{
		retString = "wait";
	}
	void evaluate(dsp56k_core* cpustate) override {}
	size_t size() const override { return 1; }
	size_t accumulatorBitsModified() const override { return BM_HIGH | BM_MIDDLE | BM_LOW; }
>>>>>>> upstream/master
};

// ZERO : 0001 0101 0101 F000 : A-224 //////////////////////////////////////////
class Zero: public Instruction
{
public:
<<<<<<< HEAD
	Zero(const Opcode* oco, const UINT16 word0, const UINT16 word1) : Instruction(oco)
	{
		m_valid = decode(word0, word1);
	}
	bool decode(const UINT16 word0, const UINT16 word1)
=======
	Zero(const Opcode* oco, const uint16_t word0, const uint16_t word1) : Instruction(oco)
	{
		m_valid = decode(word0, word1);
	}
	bool decode(const uint16_t word0, const uint16_t word1) override
>>>>>>> upstream/master
	{
		decode_F_table(BITSn(word0,0x0008), m_destination);
		return true;
	}
<<<<<<< HEAD
	void disassemble(std::string& retString) const
	{
		retString = "zero " + regIdAsString(m_destination);
	}
	void evaluate(dsp56k_core* cpustate) {}
	size_t size() const { return 1; }
	size_t accumulatorBitsModified() const { return BM_HIGH | BM_MIDDLE | BM_LOW; }
=======
	void disassemble(std::string& retString) const override
	{
		retString = "zero " + regIdAsString(m_destination);
	}
	void evaluate(dsp56k_core* cpustate) override {}
	size_t size() const override { return 1; }
	size_t accumulatorBitsModified() const override { return BM_HIGH | BM_MIDDLE | BM_LOW; }
>>>>>>> upstream/master
};

// SHFL : 0001 0101 1101 FQQQ : !!UNDOCUMENTED!! ///////////////////////////////
class Shfl: public Instruction
{
public:
<<<<<<< HEAD
	Shfl(const Opcode* oco, const UINT16 word0, const UINT16 word1) : Instruction(oco)
=======
	Shfl(const Opcode* oco, const uint16_t word0, const uint16_t word1) : Instruction(oco)
>>>>>>> upstream/master
	{
		m_source2 = iINVALID;
		m_valid = decode(word0, word1);
	}
<<<<<<< HEAD
	bool decode(const UINT16 word0, const UINT16 word1)
=======
	bool decode(const uint16_t word0, const uint16_t word1) override
>>>>>>> upstream/master
	{
		decode_QQQF_table(BITSn(word0,0x0007), BITSn(word0,0x0008),
							m_source, m_source2, m_destination);

		// This hackery amounts to a very strange QQQF table...
		if (m_source == iX0 && m_source2 == iX0) return false;
		if (m_source == iX1 && m_source2 == iX0) return false;

		if (m_source == iY0 && m_source2 == iX1)
		{
			m_source  = iX1;
			m_source2 = iY0;
		}
		if (m_source == iY1 && m_source2 == iX1)
		{
			m_source  = iX1;
			m_source2 = iY1;
		}
		return true;
	}
<<<<<<< HEAD
	void disassemble(std::string& retString) const
=======
	void disassemble(std::string& retString) const override
>>>>>>> upstream/master
	{
		retString = "shfl " +
					regIdAsString(m_source) + "," +
					regIdAsString(m_source2) + "," + regIdAsString(m_destination);
	}
<<<<<<< HEAD
	void evaluate(dsp56k_core* cpustate) {}
	size_t size() const { return 1; }
	size_t accumulatorBitsModified() const { return BM_HIGH | BM_MIDDLE | BM_LOW; }
=======
	void evaluate(dsp56k_core* cpustate) override {}
	size_t size() const override { return 1; }
	size_t accumulatorBitsModified() const override { return BM_HIGH | BM_MIDDLE | BM_LOW; }
>>>>>>> upstream/master

private:
	reg_id m_source2;
};

// SHFR : 0001 0101 1111 FQQQ : !!UNDOCUMENTED!! ///////////////////////////////
class Shfr: public Instruction
{
public:
<<<<<<< HEAD
	Shfr(const Opcode* oco, const UINT16 word0, const UINT16 word1) : Instruction(oco)
=======
	Shfr(const Opcode* oco, const uint16_t word0, const uint16_t word1) : Instruction(oco)
>>>>>>> upstream/master
	{
		m_source2 = iINVALID;
		m_valid = decode(word0, word1);
	}
<<<<<<< HEAD
	bool decode(const UINT16 word0, const UINT16 word1)
=======
	bool decode(const uint16_t word0, const uint16_t word1) override
>>>>>>> upstream/master
	{
		decode_QQQF_table(BITSn(word0,0x0007), BITSn(word0,0x0008),
							m_source, m_source2, m_destination);

		// This hackery amounts to a very strange QQQF table...
		if (m_source == iX0 && m_source2 == iX0) return false;
		if (m_source == iX1 && m_source2 == iX0) return false;

		if (m_source == iY0 && m_source2 == iX1)
		{
			m_source  = iX1;
			m_source2 = iY0;
		}
		if (m_source == iY1 && m_source2 == iX1)
		{
			m_source  = iX1;
			m_source2 = iY1;
		}
		return true;
	}
<<<<<<< HEAD
	void disassemble(std::string& retString) const
=======
	void disassemble(std::string& retString) const override
>>>>>>> upstream/master
	{
		retString = "shfr " +
					regIdAsString(m_source) + "," +
					regIdAsString(m_source2) + "," + regIdAsString(m_destination);
	}
<<<<<<< HEAD
	void evaluate(dsp56k_core* cpustate) {}
	size_t size() const { return 1; }
	size_t accumulatorBitsModified() const { return BM_HIGH | BM_MIDDLE | BM_LOW; }
=======
	void evaluate(dsp56k_core* cpustate) override {}
	size_t size() const override { return 1; }
	size_t accumulatorBitsModified() const override { return BM_HIGH | BM_MIDDLE | BM_LOW; }
>>>>>>> upstream/master

private:
	reg_id m_source2;
};

}
#endif
