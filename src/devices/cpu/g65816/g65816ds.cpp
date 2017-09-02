// license:BSD-3-Clause
// copyright-holders:Karl Stenerud
/* ======================================================================== */
/* =============================== COPYRIGHT ============================== */
/* ======================================================================== */
/*

G65C816 CPU Emulator V0.90

Copyright Karl Stenerud
All rights reserved.

*/


#include "emu.h"
#include "g65816ds.h"

#ifdef SEC
#undef SEC
#endif

#define ADDRESS_65816(A) ((A)&0xffffff)


<<<<<<< HEAD
struct g65816_opcode_struct
{
	unsigned char name;
	unsigned char flag;
	unsigned char ea;
=======
namespace {

class g65816_opcode_struct
{
public:
	const char *name() const
	{
			return s_opnames[unsigned(m_name)];
	}

	bool is_call() const
	{
		switch (m_name)
		{
		case op::JSR:
		case op::JSL:
			return true;
		default:
			return false;
		}
	}

	bool is_return() const
	{
		switch (m_name)
		{
		case op::RTI:
		case op::RTL:
		case op::RTS:
			return true;
		default:
			return false;
		}
	}

	static const g65816_opcode_struct &get(unsigned char ins)
	{
		return s_opcodes[ins];
	}

	unsigned char flag;
	unsigned char ea;

protected:
	enum class op : unsigned
	{
		ADC ,  AND ,  ASL ,  BCC ,  BCS ,  BEQ ,  BIT ,  BMI ,  BNE ,  BPL ,  BRA ,
		BRK ,  BRL ,  BVC ,  BVS ,  CLC ,  CLD ,  CLI ,  CLV ,  CMP ,  COP ,  CPX ,
		CPY ,  DEA ,  DEC ,  DEX ,  DEY ,  EOR ,  INA ,  INC ,  INX ,  INY ,  JML ,
		JMP ,  JSL ,  JSR ,  LDA ,  LDX ,  LDY ,  LSR ,  MVN ,  MVP ,  NOP ,  ORA ,
		PEA ,  PEI ,  PER ,  PHA ,  PHB ,  PHD ,  PHK ,  PHP ,  PHX ,  PHY ,  PLA ,
		PLB ,  PLD ,  PLP ,  PLX ,  PLY ,  REP ,  ROL ,  ROR ,  RTI ,  RTL ,  RTS ,
		SBC ,  SEC ,  SED ,  SEI ,  SEP ,  STA ,  STP ,  STX ,  STY ,  STZ ,  TAX ,
		TAY ,  TCS ,  TCD ,  TDC ,  TRB ,  TSB ,  TSC ,  TSX ,  TXA ,  TXS ,  TXY ,
		TYA ,  TYX ,  WAI ,  WDM ,  XBA ,  XCE
	};

	g65816_opcode_struct(op n, unsigned char f, unsigned char e)
		: flag(f)
		, ea(e)
		, m_name(n)
	{
	}

	op m_name;

	static const char *const s_opnames[];
	static const g65816_opcode_struct s_opcodes[256];
>>>>>>> upstream/master
};

enum
{
	IMP , ACC , RELB, RELW, IMM , A   , AI  , AL  , ALX , AX  , AXI ,
	AY  , D   , DI  , DIY , DLI , DLIY, DX  , DXI , DY  , S   , SIY ,
<<<<<<< HEAD
	SIG /*, MVN , MVP , PEA , PEI , PER */
=======
	SIG , MVN , MVP , PEA , PEI , PER
>>>>>>> upstream/master
};

enum
{
	I, /* ignore */
	M, /* check m bit */
	X  /* check x bit */
};

<<<<<<< HEAD
enum
{
	ADC ,  AND ,  ASL ,  BCC ,  BCS ,  BEQ ,  BIT ,  BMI ,  BNE ,  BPL ,  BRA ,
	BRK ,  BRL ,  BVC ,  BVS ,  CLC ,  CLD ,  CLI ,  CLV ,  CMP ,  COP ,  CPX ,
	CPY ,  DEA ,  DEC ,  DEX ,  DEY ,  EOR ,  INA ,  INC ,  INX ,  INY ,  JML ,
	JMP ,  JSL ,  JSR ,  LDA ,  LDX ,  LDY ,  LSR ,  MVN ,  MVP ,  NOP ,  ORA ,
	PEA ,  PEI ,  PER ,  PHA ,  PHB ,  PHD ,  PHK ,  PHP ,  PHX ,  PHY ,  PLA ,
	PLB ,  PLD ,  PLP ,  PLX ,  PLY ,  REP ,  ROL ,  ROR ,  RTI ,  RTL ,  RTS ,
	SBC ,  SEC ,  SED ,  SEI ,  SEP ,  STA ,  STP ,  STX ,  STY ,  STZ ,  TAX ,
	TAY ,  TCS ,  TCD ,  TDC ,  TRB ,  TSB ,  TSC ,  TSX ,  TXA ,  TXS ,  TXY ,
	TYA ,  TYX ,  WAI ,  WDM ,  XBA ,  XCE
};

static const char *const g_opnames[] =
=======
const char *const g65816_opcode_struct::s_opnames[] =
>>>>>>> upstream/master
{
	"ADC", "AND", "ASL", "BCC", "BCS", "BEQ", "BIT", "BMI", "BNE", "BPL", "BRA",
	"BRK", "BRL", "BVC", "BVS", "CLC", "CLD", "CLI", "CLV", "CMP", "COP", "CPX",
	"CPY", "DEA", "DEC", "DEX", "DEY", "EOR", "INA", "INC", "INX", "INY", "JML",
	"JMP", "JSL", "JSR", "LDA", "LDX", "LDY", "LSR", "MVN", "MVP", "NOP", "ORA",
	"PEA", "PEI", "PER", "PHA", "PHB", "PHD", "PHK", "PHP", "PHX", "PHY", "PLA",
	"PLB", "PLD", "PLP", "PLX", "PLY", "REP", "ROL", "ROR", "RTI", "RTL", "RTS",
	"SBC", "SEC", "SED", "SEI", "SEP", "STA", "STP", "STX", "STY", "STZ", "TAX",
	"TAY", "TCS", "TCD", "TDC", "TRB", "TSB", "TSC", "TSX", "TXA", "TXS", "TXY",
	"TYA", "TYX", "WAI", "WDM", "XBA", "XCE"
};

<<<<<<< HEAD
static const g65816_opcode_struct g_opcodes[256] =
{
	{BRK, I, SIG }, {ORA, M, DXI }, {COP, I, SIG }, {ORA, M, S   },
	{TSB, M, D   }, {ORA, M, D   }, {ASL, M, D   }, {ORA, M, DLI },
	{PHP, I, IMP }, {ORA, M, IMM }, {ASL, M, ACC }, {PHD, I, IMP },
	{TSB, M, A   }, {ORA, M, A   }, {ASL, M, A   }, {ORA, M, AL  },
	{BPL, I, RELB}, {ORA, M, DIY }, {ORA, M, DI  }, {ORA, M, SIY },
	{TRB, M, D   }, {ORA, M, DX  }, {ASL, M, DX  }, {ORA, M, DLIY},
	{CLC, I, IMP }, {ORA, M, AY  }, {INA, I, IMP }, {TCS, I, IMP },
	{TRB, M, A   }, {ORA, M, AX  }, {ASL, M, AX  }, {ORA, M, ALX },
	{JSR, I, A   }, {AND, M, DXI }, {JSL, I, AL  }, {AND, M, S   },
	{BIT, M, D   }, {AND, M, D   }, {ROL, M, D   }, {AND, M, DLI },
	{PLP, I, IMP }, {AND, M, IMM }, {ROL, M, ACC }, {PLD, I, IMP },
	{BIT, M, A   }, {AND, M, A   }, {ROL, M, A   }, {AND, M, AL  },
	{BMI, I, RELB}, {AND, M, DIY }, {AND, M, DI  }, {AND, M, SIY },
	{BIT, M, DX  }, {AND, M, DX  }, {ROL, M, DX  }, {AND, M, DLIY},
	{SEC, I, IMP }, {AND, M, AY  }, {DEA, I, IMP }, {TSC, I, IMP },
	{BIT, M, AX  }, {AND, M, AX  }, {ROL, M, AX  }, {AND, M, ALX },
	{RTI, I, IMP }, {EOR, M, DXI }, {WDM, I, IMP }, {EOR, M, S   },
	{MVP, I, MVP }, {EOR, M, D   }, {LSR, M, D   }, {EOR, M, DLI },
	{PHA, I, IMP }, {EOR, M, IMM }, {LSR, M, ACC }, {PHK, I, IMP },
	{JMP, I, A   }, {EOR, M, A   }, {LSR, M, A   }, {EOR, M, AL  },
	{BVC, I, RELB}, {EOR, M, DIY }, {EOR, M, DI  }, {EOR, M, SIY },
	{MVN, I, MVN }, {EOR, M, DX  }, {LSR, M, DX  }, {EOR, M, DLIY},
	{CLI, I, IMP }, {EOR, M, AY  }, {PHY, I, IMP }, {TCD, I, IMP },
	{JMP, I, AL  }, {EOR, M, AX  }, {LSR, M, AX  }, {EOR, M, ALX },
	{RTS, I, IMP }, {ADC, M, DXI }, {PER, I, PER }, {ADC, M, S   },
	{STZ, M, D   }, {ADC, M, D   }, {ROR, M, D   }, {ADC, M, DLI },
	{PLA, I, IMP }, {ADC, M, IMM }, {ROR, M, ACC }, {RTL, I, IMP },
	{JMP, I, AI  }, {ADC, M, A   }, {ROR, M, A   }, {ADC, M, AL  },
	{BVS, I, RELB}, {ADC, M, DIY }, {ADC, M, DI  }, {ADC, M, SIY },
	{STZ, M, DX  }, {ADC, M, DX  }, {ROR, M, DX  }, {ADC, M, DLIY},
	{SEI, I, IMP }, {ADC, M, AY  }, {PLY, I, IMP }, {TDC, I, IMP },
	{JMP, I, AXI }, {ADC, M, AX  }, {ROR, M, AX  }, {ADC, M, ALX },
	{BRA, I, RELB}, {STA, M, DXI }, {BRL, I, RELW}, {STA, M, S   },
	{STY, X, D   }, {STA, M, D   }, {STX, X, D   }, {STA, M, DLI },
	{DEY, I, IMP }, {BIT, M, IMM }, {TXA, I, IMP }, {PHB, I, IMP },
	{STY, X, A   }, {STA, M, A   }, {STX, X, A   }, {STA, M, AL  },
	{BCC, I, RELB}, {STA, M, DIY }, {STA, M, DI  }, {STA, M, SIY },
	{STY, X, DX  }, {STA, M, DX  }, {STX, X, DY  }, {STA, M, DLIY},
	{TYA, I, IMP }, {STA, M, AY  }, {TXS, I, IMP }, {TXY, I, IMP },
	{STZ, M, A   }, {STA, M, AX  }, {STZ, M, AX  }, {STA, M, ALX },
	{LDY, X, IMM }, {LDA, M, DXI }, {LDX, X, IMM }, {LDA, M, S   },
	{LDY, X, D   }, {LDA, M, D   }, {LDX, X, D   }, {LDA, M, DLI },
	{TAY, I, IMP }, {LDA, M, IMM }, {TAX, I, IMP }, {PLB, I, IMP },
	{LDY, X, A   }, {LDA, M, A   }, {LDX, X, A   }, {LDA, M, AL  },
	{BCS, I, RELB}, {LDA, M, DIY }, {LDA, M, DI  }, {LDA, M, SIY },
	{LDY, X, DX  }, {LDA, M, DX  }, {LDX, X, DY  }, {LDA, M, DLIY},
	{CLV, I, IMP }, {LDA, M, AY  }, {TSX, I, IMP }, {TYX, I, IMP },
	{LDY, X, AX  }, {LDA, M, AX  }, {LDX, X, AY  }, {LDA, M, ALX },
	{CPY, X, IMM }, {CMP, M, DXI }, {REP, I, IMM }, {CMP, M, S   },
	{CPY, X, D   }, {CMP, M, D   }, {DEC, M, D   }, {CMP, M, DLI },
	{INY, I, IMP }, {CMP, M, IMM }, {DEX, I, IMP }, {WAI, I, IMP },
	{CPY, X, A   }, {CMP, M, A   }, {DEC, M, A   }, {CMP, M, AL  },
	{BNE, I, RELB}, {CMP, M, DIY }, {CMP, M, DI  }, {CMP, M, SIY },
	{PEI, I, PEI }, {CMP, M, DX  }, {DEC, M, DX  }, {CMP, M, DLIY},
	{CLD, I, IMP }, {CMP, M, AY  }, {PHX, I, IMP }, {STP, I, IMP },
	{JML, I, AI  }, {CMP, M, AX  }, {DEC, M, AX  }, {CMP, M, ALX },
	{CPX, X, IMM }, {SBC, M, DXI }, {SEP, I, IMM }, {SBC, M, S   },
	{CPX, X, D   }, {SBC, M, D   }, {INC, M, D   }, {SBC, M, DLI },
	{INX, M, IMP }, {SBC, M, IMM }, {NOP, I, IMP }, {XBA, I, IMP },
	{CPX, X, A   }, {SBC, M, A   }, {INC, M, A   }, {SBC, M, AL  },
	{BEQ, I, RELB}, {SBC, M, DIY }, {SBC, M, DI  }, {SBC, M, SIY },
	{PEA, I, PEA }, {SBC, M, DX  }, {INC, M, DX  }, {SBC, M, DLIY},
	{SED, I, IMP }, {SBC, M, AY  }, {PLX, I, IMP }, {XCE, I, IMP },
	{JSR, I, AXI }, {SBC, M, AX  }, {INC, M, AX  }, {SBC, M, ALX }
};

static const UINT8 *base_oprom;
static UINT32 base_pc;

INLINE unsigned int read_8(unsigned int address)
=======
const g65816_opcode_struct g65816_opcode_struct::s_opcodes[256] =
{
	{op::BRK, I, SIG }, {op::ORA, M, DXI }, {op::COP, I, SIG }, {op::ORA, M, S   },
	{op::TSB, M, D   }, {op::ORA, M, D   }, {op::ASL, M, D   }, {op::ORA, M, DLI },
	{op::PHP, I, IMP }, {op::ORA, M, IMM }, {op::ASL, M, ACC }, {op::PHD, I, IMP },
	{op::TSB, M, A   }, {op::ORA, M, A   }, {op::ASL, M, A   }, {op::ORA, M, AL  },
	{op::BPL, I, RELB}, {op::ORA, M, DIY }, {op::ORA, M, DI  }, {op::ORA, M, SIY },
	{op::TRB, M, D   }, {op::ORA, M, DX  }, {op::ASL, M, DX  }, {op::ORA, M, DLIY},
	{op::CLC, I, IMP }, {op::ORA, M, AY  }, {op::INA, I, IMP }, {op::TCS, I, IMP },
	{op::TRB, M, A   }, {op::ORA, M, AX  }, {op::ASL, M, AX  }, {op::ORA, M, ALX },
	{op::JSR, I, A   }, {op::AND, M, DXI }, {op::JSL, I, AL  }, {op::AND, M, S   },
	{op::BIT, M, D   }, {op::AND, M, D   }, {op::ROL, M, D   }, {op::AND, M, DLI },
	{op::PLP, I, IMP }, {op::AND, M, IMM }, {op::ROL, M, ACC }, {op::PLD, I, IMP },
	{op::BIT, M, A   }, {op::AND, M, A   }, {op::ROL, M, A   }, {op::AND, M, AL  },
	{op::BMI, I, RELB}, {op::AND, M, DIY }, {op::AND, M, DI  }, {op::AND, M, SIY },
	{op::BIT, M, DX  }, {op::AND, M, DX  }, {op::ROL, M, DX  }, {op::AND, M, DLIY},
	{op::SEC, I, IMP }, {op::AND, M, AY  }, {op::DEA, I, IMP }, {op::TSC, I, IMP },
	{op::BIT, M, AX  }, {op::AND, M, AX  }, {op::ROL, M, AX  }, {op::AND, M, ALX },
	{op::RTI, I, IMP }, {op::EOR, M, DXI }, {op::WDM, I, IMP }, {op::EOR, M, S   },
	{op::MVP, I, MVP }, {op::EOR, M, D   }, {op::LSR, M, D   }, {op::EOR, M, DLI },
	{op::PHA, I, IMP }, {op::EOR, M, IMM }, {op::LSR, M, ACC }, {op::PHK, I, IMP },
	{op::JMP, I, A   }, {op::EOR, M, A   }, {op::LSR, M, A   }, {op::EOR, M, AL  },
	{op::BVC, I, RELB}, {op::EOR, M, DIY }, {op::EOR, M, DI  }, {op::EOR, M, SIY },
	{op::MVN, I, MVN }, {op::EOR, M, DX  }, {op::LSR, M, DX  }, {op::EOR, M, DLIY},
	{op::CLI, I, IMP }, {op::EOR, M, AY  }, {op::PHY, I, IMP }, {op::TCD, I, IMP },
	{op::JMP, I, AL  }, {op::EOR, M, AX  }, {op::LSR, M, AX  }, {op::EOR, M, ALX },
	{op::RTS, I, IMP }, {op::ADC, M, DXI }, {op::PER, I, PER }, {op::ADC, M, S   },
	{op::STZ, M, D   }, {op::ADC, M, D   }, {op::ROR, M, D   }, {op::ADC, M, DLI },
	{op::PLA, I, IMP }, {op::ADC, M, IMM }, {op::ROR, M, ACC }, {op::RTL, I, IMP },
	{op::JMP, I, AI  }, {op::ADC, M, A   }, {op::ROR, M, A   }, {op::ADC, M, AL  },
	{op::BVS, I, RELB}, {op::ADC, M, DIY }, {op::ADC, M, DI  }, {op::ADC, M, SIY },
	{op::STZ, M, DX  }, {op::ADC, M, DX  }, {op::ROR, M, DX  }, {op::ADC, M, DLIY},
	{op::SEI, I, IMP }, {op::ADC, M, AY  }, {op::PLY, I, IMP }, {op::TDC, I, IMP },
	{op::JMP, I, AXI }, {op::ADC, M, AX  }, {op::ROR, M, AX  }, {op::ADC, M, ALX },
	{op::BRA, I, RELB}, {op::STA, M, DXI }, {op::BRL, I, RELW}, {op::STA, M, S   },
	{op::STY, X, D   }, {op::STA, M, D   }, {op::STX, X, D   }, {op::STA, M, DLI },
	{op::DEY, I, IMP }, {op::BIT, M, IMM }, {op::TXA, I, IMP }, {op::PHB, I, IMP },
	{op::STY, X, A   }, {op::STA, M, A   }, {op::STX, X, A   }, {op::STA, M, AL  },
	{op::BCC, I, RELB}, {op::STA, M, DIY }, {op::STA, M, DI  }, {op::STA, M, SIY },
	{op::STY, X, DX  }, {op::STA, M, DX  }, {op::STX, X, DY  }, {op::STA, M, DLIY},
	{op::TYA, I, IMP }, {op::STA, M, AY  }, {op::TXS, I, IMP }, {op::TXY, I, IMP },
	{op::STZ, M, A   }, {op::STA, M, AX  }, {op::STZ, M, AX  }, {op::STA, M, ALX },
	{op::LDY, X, IMM }, {op::LDA, M, DXI }, {op::LDX, X, IMM }, {op::LDA, M, S   },
	{op::LDY, X, D   }, {op::LDA, M, D   }, {op::LDX, X, D   }, {op::LDA, M, DLI },
	{op::TAY, I, IMP }, {op::LDA, M, IMM }, {op::TAX, I, IMP }, {op::PLB, I, IMP },
	{op::LDY, X, A   }, {op::LDA, M, A   }, {op::LDX, X, A   }, {op::LDA, M, AL  },
	{op::BCS, I, RELB}, {op::LDA, M, DIY }, {op::LDA, M, DI  }, {op::LDA, M, SIY },
	{op::LDY, X, DX  }, {op::LDA, M, DX  }, {op::LDX, X, DY  }, {op::LDA, M, DLIY},
	{op::CLV, I, IMP }, {op::LDA, M, AY  }, {op::TSX, I, IMP }, {op::TYX, I, IMP },
	{op::LDY, X, AX  }, {op::LDA, M, AX  }, {op::LDX, X, AY  }, {op::LDA, M, ALX },
	{op::CPY, X, IMM }, {op::CMP, M, DXI }, {op::REP, I, IMM }, {op::CMP, M, S   },
	{op::CPY, X, D   }, {op::CMP, M, D   }, {op::DEC, M, D   }, {op::CMP, M, DLI },
	{op::INY, I, IMP }, {op::CMP, M, IMM }, {op::DEX, I, IMP }, {op::WAI, I, IMP },
	{op::CPY, X, A   }, {op::CMP, M, A   }, {op::DEC, M, A   }, {op::CMP, M, AL  },
	{op::BNE, I, RELB}, {op::CMP, M, DIY }, {op::CMP, M, DI  }, {op::CMP, M, SIY },
	{op::PEI, I, PEI }, {op::CMP, M, DX  }, {op::DEC, M, DX  }, {op::CMP, M, DLIY},
	{op::CLD, I, IMP }, {op::CMP, M, AY  }, {op::PHX, I, IMP }, {op::STP, I, IMP },
	{op::JML, I, AI  }, {op::CMP, M, AX  }, {op::DEC, M, AX  }, {op::CMP, M, ALX },
	{op::CPX, X, IMM }, {op::SBC, M, DXI }, {op::SEP, I, IMM }, {op::SBC, M, S   },
	{op::CPX, X, D   }, {op::SBC, M, D   }, {op::INC, M, D   }, {op::SBC, M, DLI },
	{op::INX, M, IMP }, {op::SBC, M, IMM }, {op::NOP, I, IMP }, {op::XBA, I, IMP },
	{op::CPX, X, A   }, {op::SBC, M, A   }, {op::INC, M, A   }, {op::SBC, M, AL  },
	{op::BEQ, I, RELB}, {op::SBC, M, DIY }, {op::SBC, M, DI  }, {op::SBC, M, SIY },
	{op::PEA, I, PEA }, {op::SBC, M, DX  }, {op::INC, M, DX  }, {op::SBC, M, DLIY},
	{op::SED, I, IMP }, {op::SBC, M, AY  }, {op::PLX, I, IMP }, {op::XCE, I, IMP },
	{op::JSR, I, AXI }, {op::SBC, M, AX  }, {op::INC, M, AX  }, {op::SBC, M, ALX }
};

} // anonymous namespace

static const uint8_t *base_oprom;
static uint32_t base_pc;

static inline unsigned int read_8(unsigned int address)
>>>>>>> upstream/master
{
	address = ADDRESS_65816(address);
	return base_oprom[address - base_pc];
}

<<<<<<< HEAD
INLINE unsigned int read_16(unsigned int address)
=======
static inline unsigned int read_16(unsigned int address)
>>>>>>> upstream/master
{
	unsigned int val = read_8(address);
	return val | (read_8(address+1)<<8);
}

<<<<<<< HEAD
INLINE unsigned int read_24(unsigned int address)
=======
static inline unsigned int read_24(unsigned int address)
>>>>>>> upstream/master
{
	unsigned int val = read_8(address);
	val |= (read_8(address+1)<<8);
	return val | (read_8(address+2)<<16);
}

<<<<<<< HEAD
INLINE char* int_8_str(unsigned int val)
=======
static inline char* int_8_str(unsigned int val)
>>>>>>> upstream/master
{
	static char str[20];

	val &= 0xff;

	if(val & 0x80)
		sprintf(str, "-$%x", (0-val) & 0x7f);
	else
		sprintf(str, "$%x", val & 0x7f);

	return str;
}

<<<<<<< HEAD
INLINE char* int_16_str(unsigned int val)
=======
static inline char* int_16_str(unsigned int val)
>>>>>>> upstream/master
{
	static char str[20];

	val &= 0xffff;

	if(val & 0x8000)
		sprintf(str, "-$%x", (0-val) & 0x7fff);
	else
		sprintf(str, "$%x", val & 0x7fff);

	return str;
}


<<<<<<< HEAD
unsigned g65816_disassemble(char* buff, unsigned int pc, unsigned int pb, const UINT8 *oprom, int m_flag, int x_flag)
{
	unsigned int instruction;
	const g65816_opcode_struct* opcode;
	char* ptr;
=======
unsigned g65816_disassemble(std::ostream &stream, unsigned int pc, unsigned int pb, const uint8_t *oprom, int m_flag, int x_flag)
{
	unsigned int instruction;
	const g65816_opcode_struct* opcode;
>>>>>>> upstream/master
	int var;
	int length = 1;
	unsigned int address;
	unsigned dasm_flags;

	pb <<= 16;
	address = pc | pb;

	base_oprom = oprom;
	base_pc = address;

	instruction = read_8(address);
<<<<<<< HEAD
	opcode = g_opcodes + instruction;

	strcpy(buff, g_opnames[opcode->name]);
	ptr = buff + strlen(buff);

	switch(opcode->name)
	{
		case JSR:
		case JSL:
			dasm_flags = DASMFLAG_STEP_OVER;
			break;

		case RTI:
		case RTL:
		case RTS:
			dasm_flags = DASMFLAG_STEP_OUT;
			break;

		default:
			dasm_flags = 0;
			break;
	}
=======
	opcode = &g65816_opcode_struct::get(instruction);

	stream << opcode->name();

	if (opcode->is_call())
		dasm_flags = DASMFLAG_STEP_OVER;
	else if (opcode->is_return())
		dasm_flags = DASMFLAG_STEP_OUT;
	else
		dasm_flags = 0;
>>>>>>> upstream/master

	switch(opcode->ea)
	{
		case IMP :
			break;
		case ACC :
<<<<<<< HEAD
			sprintf(ptr, "A");
			break;
		case RELB:
			var = (INT8) read_8(address+1);
			length++;
			sprintf(ptr, " %06x (%s)", pb | ((pc + length + var)&0xffff), int_8_str(var));
=======
			util::stream_format(stream, "A");
			break;
		case RELB:
			var = (int8_t) read_8(address+1);
			length++;
			util::stream_format(stream, " %06x (%s)", pb | ((pc + length + var)&0xffff), int_8_str(var));
>>>>>>> upstream/master
			break;
		case RELW:
		case PER :
			var = read_16(address+1);
			length += 2;
<<<<<<< HEAD
			sprintf(ptr, " %06x (%s)", pb | ((pc + length + var)&0xffff), int_16_str(var));
=======
			util::stream_format(stream, " %06x (%s)", pb | ((pc + length + var)&0xffff), int_16_str(var));
>>>>>>> upstream/master
			break;
		case IMM :
			if((opcode->flag == M && !m_flag) || (opcode->flag == X && !x_flag))
			{
<<<<<<< HEAD
				sprintf(ptr, " #$%04x", read_16(address+1));
=======
				util::stream_format(stream, " #$%04x", read_16(address+1));
>>>>>>> upstream/master
				length += 2;
			}
			else
			{
<<<<<<< HEAD
				sprintf(ptr, " #$%02x", read_8(address+1));
=======
				util::stream_format(stream, " #$%02x", read_8(address+1));
>>>>>>> upstream/master
				length++;
			}
			break;
		case A   :
		case PEA :
<<<<<<< HEAD
			sprintf(ptr, " $%04x", read_16(address+1));
			length += 2;
			break;
		case AI  :
			sprintf(ptr, " ($%04x)", read_16(address+1));
			length += 2;
			break;
		case AL  :
			sprintf(ptr, " $%06x", read_24(address+1));
			length += 3;
			break;
		case ALX :
			sprintf(ptr, " $%06x,X", read_24(address+1));
			length += 3;
			break;
		case AX  :
			sprintf(ptr, " $%04x,X", read_16(address+1));
			length += 2;
			break;
		case AXI :
			sprintf(ptr, " ($%04x,X)", read_16(address+1));
			length += 2;
			break;
		case AY  :
			sprintf(ptr, " $%04x,Y", read_16(address+1));
			length += 2;
			break;
		case D   :
			sprintf(ptr, " $%02x", read_8(address+1));
=======
			util::stream_format(stream, " $%04x", read_16(address+1));
			length += 2;
			break;
		case AI  :
			util::stream_format(stream, " ($%04x)", read_16(address+1));
			length += 2;
			break;
		case AL  :
			util::stream_format(stream, " $%06x", read_24(address+1));
			length += 3;
			break;
		case ALX :
			util::stream_format(stream, " $%06x,X", read_24(address+1));
			length += 3;
			break;
		case AX  :
			util::stream_format(stream, " $%04x,X", read_16(address+1));
			length += 2;
			break;
		case AXI :
			util::stream_format(stream, " ($%04x,X)", read_16(address+1));
			length += 2;
			break;
		case AY  :
			util::stream_format(stream, " $%04x,Y", read_16(address+1));
			length += 2;
			break;
		case D   :
			util::stream_format(stream, " $%02x", read_8(address+1));
>>>>>>> upstream/master
			length++;
			break;
		case DI  :
		case PEI :
<<<<<<< HEAD
			sprintf(ptr, " ($%02x)", read_8(address+1));
			length++;
			break;
		case DIY :
			sprintf(ptr, " ($%02x),Y", read_8(address+1));
			length++;
			break;
		case DLI :
			sprintf(ptr, " [$%02x]", read_8(address+1));
			length++;
			break;
		case DLIY:
			sprintf(ptr, " [$%02x],Y", read_8(address+1));
			length++;
			break;
		case DX  :
			sprintf(ptr, " $%02x,X", read_8(address+1));
			length++;
			break;
		case DXI :
			sprintf(ptr, " ($%02x,X)", read_8(address+1));
			length++;
			break;
		case DY  :
			sprintf(ptr, " $%02x,Y", read_8(address+1));
			length++;
			break;
		case S   :
			sprintf(ptr, " %s,S", int_8_str(read_8(address+1)));
			length++;
			break;
		case SIY :
			sprintf(ptr, " (%s,S),Y", int_8_str(read_8(address+1)));
			length++;
			break;
		case SIG :
			sprintf(ptr, " #$%02x", read_8(address+1));
=======
			util::stream_format(stream, " ($%02x)", read_8(address+1));
			length++;
			break;
		case DIY :
			util::stream_format(stream, " ($%02x),Y", read_8(address+1));
			length++;
			break;
		case DLI :
			util::stream_format(stream, " [$%02x]", read_8(address+1));
			length++;
			break;
		case DLIY:
			util::stream_format(stream, " [$%02x],Y", read_8(address+1));
			length++;
			break;
		case DX  :
			util::stream_format(stream, " $%02x,X", read_8(address+1));
			length++;
			break;
		case DXI :
			util::stream_format(stream, " ($%02x,X)", read_8(address+1));
			length++;
			break;
		case DY  :
			util::stream_format(stream, " $%02x,Y", read_8(address+1));
			length++;
			break;
		case S   :
			util::stream_format(stream, " %s,S", int_8_str(read_8(address+1)));
			length++;
			break;
		case SIY :
			util::stream_format(stream, " (%s,S),Y", int_8_str(read_8(address+1)));
			length++;
			break;
		case SIG :
			util::stream_format(stream, " #$%02x", read_8(address+1));
>>>>>>> upstream/master
			length++;
			break;
		case MVN :
		case MVP :
<<<<<<< HEAD
			sprintf(ptr, " $%02x, $%02x", read_8(address+2), read_8(address+1));
=======
			util::stream_format(stream, " $%02x, $%02x", read_8(address+2), read_8(address+1));
>>>>>>> upstream/master
			length += 2;
			break;
	}

	return length | DASMFLAG_SUPPORTED | dasm_flags;
}

CPU_DISASSEMBLE( g65816_generic )
{
<<<<<<< HEAD
	return g65816_disassemble(buffer, (pc & 0x00ffff), (pc & 0xff0000) >> 16, oprom, 0, 0);
=======
	return g65816_disassemble(stream, (pc & 0x00ffff), (pc & 0xff0000) >> 16, oprom, 0, 0);
>>>>>>> upstream/master
}
