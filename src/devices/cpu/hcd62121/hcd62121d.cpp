// license:BSD-3-Clause
// copyright-holders:Wilbert Pol

#include "emu.h"
<<<<<<< HEAD
#include "debugger.h"
#include "hcd62121.h"

#ifdef _MSC_VER
#undef _SP
#endif

enum
{
	_REG=1,     /* register */
	_REGREG,    /* register1, register2, or register2, register1 or register1, imm byte */
	_IRG,       /* register indirect */
	_IRGREG,    /* 2 register indirect */
	_A16,       /* 16bit address */
	_A24,       /* seg:address */
	_F,         /* flag register */
	_CS,        /* cs register */
	_DS,        /* ds register */
	_SS,        /* ss register */
	_PC,        /* program counter */
	_SP,        /* stack pointer */
	_I8,        /* immediate 8 bit value */
	_I16,       /* immediate 16 bit value */
	_I64,       /* immediate 64 bit value */
	_I80,       /* immediate 80 bit value */
	_ILR,       /* indirect last address register access */
	_LAR,       /* last address register */
	_DSZ,       /* dsize register? */
	_TIM,       /* timing related register? */
	_KLO,       /* KO1 - KO8 output lines */
	_KHI,       /* KO9 - KO14(?) output lines */
	_KI,        /* K input lines */
	_4          /* for nibble shifts */
=======

enum
{
	ARG_NONE=0,    /* no argument or unknown */
	ARG_REG,       /* register */
	ARG_REGREG,    /* register1, register2, or register2, register1 or register1, imm byte */
	ARG_IRG,       /* register indirect */
	ARG_IRGREG,    /* 2 register indirect */
	ARG_A16,       /* 16bit address */
	ARG_A24,       /* seg:address */
	ARG_F,         /* flag register */
	ARG_CS,        /* cs register */
	ARG_DS,        /* ds register */
	ARG_SS,        /* ss register */
	ARG_PC,        /* program counter */
	ARG_SP,        /* stack pointer */
	ARG_I8,        /* immediate 8 bit value */
	ARG_I16,       /* immediate 16 bit value */
	ARG_I64,       /* immediate 64 bit value */
	ARG_I80,       /* immediate 80 bit value */
	ARG_ILR,       /* indirect last address register access */
	ARG_LAR,       /* last address register */
	ARG_DSZ,       /* dsize register? */
	ARG_OPT,       /* OPTx (output) pins */
	ARG_PORT,      /* PORTx (output) pins */
	ARG_TIM,       /* timing related register? */
	ARG_KLO,       /* KO1 - KO8 output lines */
	ARG_KHI,       /* KO9 - KO14(?) output lines */
	ARG_KI,        /* K input lines */
	ARG_RS,        /* rotate/shift */
	ARG_RS4        /* nibble rotate/shift */
>>>>>>> upstream/master
};

struct hcd62121_dasm
{
	const char *str;
<<<<<<< HEAD
	UINT8       arg1;
	UINT8       arg2;
=======
	u8       arg1;
	u8       arg2;
>>>>>>> upstream/master
};


static const hcd62121_dasm hcd62121_ops[256] =
{
	/* 0x00 */
<<<<<<< HEAD
	{ "un00?", 0,       0 }, { "un01?", 0,       0 }, { "un02?", 0,       0 }, { "un03?", 0,       0 },
	{ "mskb",  _REGREG, 0 }, { "mskw",  _REGREG, 0 }, { "mskq",  _REGREG, 0 }, { "mskt",  _REGREG, 0 },
	{ "sh?b",  _REG,   _4 }, { "sh?w",  _REG,   _4 }, { "sh?q",  _REG,   _4 }, { "sh?t",  _REG,   _4 },
	{ "tstb",  _REGREG, 0 }, { "tstw",  _REGREG, 0 }, { "tstq",  _REGREG, 0 }, { "tstt",  _REGREG, 0 },
	{ "xorb",  _REGREG, 0 }, { "xorw",  _REGREG, 0 }, { "xorq",  _REGREG, 0 }, { "xort",  _REGREG, 0 },
	{ "cmpb",  _REGREG, 0 }, { "cmpw",  _REGREG, 0 }, { "cmpq",  _REGREG, 0 }, { "cmpt",  _REGREG, 0 },
	{ "movb",  _REGREG, 0 }, { "movw",  _REGREG, 0 }, { "movq",  _REGREG, 0 }, { "movt",  _REGREG, 0 },
	{ "imskb", _REGREG, 0 }, { "imskw", _REGREG, 0 }, { "imskq", _REGREG, 0 }, { "imskt", _REGREG, 0 },

	/* 0x20 */
	{ "shrb",  _REG,    0 }, { "shrw",  _REG,    0 }, { "shrq",  _REG,    0 }, { "shrt",  _REG,    0 },
	{ "orb",   _REGREG, 0 }, { "orw",   _REGREG, 0 }, { "orq",   _REGREG, 0 }, { "ort",   _REGREG, 0 },
	{ "shlb",  _REG,    0 }, { "shlw",  _REG,    0 }, { "shlq",  _REG,    0 }, { "shlt",  _REG,    0 },
	{ "andb",  _REGREG, 0 }, { "andw",  _REGREG, 0 }, { "andq",  _REGREG, 0 }, { "andt",  _REGREG, 0 },
	{ "sbbb",  _REGREG, 0 }, { "sbbw",  _REGREG, 0 }, { "sbbq",  _REGREG, 0 }, { "sbbt",  _REGREG, 0 },     /* BCD SUB */
	{ "subb",  _REGREG, 0 }, { "subw",  _REGREG, 0 }, { "subq",  _REGREG, 0 }, { "subt",  _REGREG, 0 },
	{ "adbb",  _REGREG, 0 }, { "adbw",  _REGREG, 0 }, { "adbq",  _REGREG, 0 }, { "adbt",  _REGREG, 0 },     /* BCD ADD */
	{ "addb",  _REGREG, 0 }, { "addw",  _REGREG, 0 }, { "addq",  _REGREG, 0 }, { "addt",  _REGREG, 0 },

	/* 0x40 */
	{ "shrb?", _IRG,    0 }, { "shrw?", _IRG,    0 }, { "shrq?", _IRG,    0 }, { "shrt?", _IRG,    0 },
	{ "mskb",  _IRGREG, 0 }, { "mskw",  _IRGREG, 0 }, { "mskq",  _IRGREG, 0 }, { "mskt",  _IRGREG, 0 },
	{ "shrb",  _IRG,    0 }, { "shrw",  _IRG,    0 }, { "shrq",  _IRG,    0 }, { "shrt",  _IRG,    0 },
	{ "tstb",  _IRGREG, 0 }, { "tstw",  _IRGREG, 0 }, { "tstq",  _IRGREG, 0 }, { "tstt",  _IRGREG, 0 },
	{ "xorb",  _IRGREG, 0 }, { "xorw",  _IRGREG, 0 }, { "xorq",  _IRGREG, 0 }, { "xort",  _IRGREG, 0 },
	{ "cmpb",  _IRGREG, 0 }, { "cmpw",  _IRGREG, 0 }, { "cmpq",  _IRGREG, 0 }, { "cmpt",  _IRGREG, 0 },
	{ "movb",  _IRGREG, 0 }, { "movw",  _IRGREG, 0 }, { "movq",  _IRGREG, 0 }, { "movt",  _IRGREG, 0 },
	{ "imskb", _IRGREG, 0 }, { "imskw", _IRGREG, 0 }, { "imskq", _IRGREG, 0 }, { "imskt", _IRGREG, 0 },

	/* 0x60 */
	{ "shrb",  _IRG,    0 }, { "shrw",  _IRG,    0 }, { "shrq",  _IRG,    0 }, { "shrt",  _IRG,    0 },
	{ "orb",   _IRGREG, 0 }, { "orw",   _IRGREG, 0 }, { "orq",   _IRGREG, 0 }, { "ort",   _IRGREG, 0 },
	{ "shlb",  _IRG,    0 }, { "shlw",  _IRG,    0 }, { "shlq",  _IRG,    0 }, { "shlt",  _IRG,    0 },
	{ "andb",  _IRGREG, 0 }, { "andw",  _IRGREG, 0 }, { "andq",  _IRGREG, 0 }, { "andt",  _IRGREG, 0 },
	{ "sbbb",  _IRGREG, 0 }, { "sbbw",  _IRGREG, 0 }, { "sbbq",  _IRGREG, 0 }, { "sbbt",  _IRGREG, 0 },     /* BCD SUB */
	{ "subb",  _IRGREG, 0 }, { "subw",  _IRGREG, 0 }, { "subq",  _IRGREG, 0 }, { "subt",  _IRGREG, 0 },
	{ "adbb",  _IRGREG, 0 }, { "adbw",  _IRGREG, 0 }, { "adbq",  _IRGREG, 0 }, { "adbt",  _IRGREG, 0 },     /* BCD ADD */
	{ "addb",  _IRGREG, 0 }, { "addw",  _IRGREG, 0 }, { "addq",  _IRGREG, 0 }, { "addt",  _IRGREG, 0 },

	/* 0x80 */
	{ "un80?",    0,    0 }, { "un81?",    0,    0 }, { "un82?",    0,    0 }, { "un83?",    0,    0 },
	{ "un84?",    0,    0 }, { "un85?",    0,    0 }, { "un86?",    0,    0 }, { "un87?",    0,    0 },
	{ "jump",  _A16,    0 }, { "jump",  _A24,    0 }, { "call",  _A16,    0 }, { "un8b?",    0,    0 },
	{ "un8C?",    0,    0 }, { "un8D?",    0,    0 }, { "un8E?",    0,    0 }, { "un8F?",    0,    0 },
	{ "retzh",    0,    0 }, { "retzl",    0,    0 }, { "retc",     0,    0 }, { "retz",     0,    0 },
	{ "retzc",    0,    0 }, { "retcl",    0,    0 }, { "retnc",    0,    0 }, { "retnz",    0,    0 },
	{ "jump",  _IRG,    0 }, { "un99?",    0,    0 }, { "un9A?",    0,    0 }, { "un9b?",    0,    0 },
	{ "un9C?",    0,    0 }, { "un9D?",    0,    0 }, { "reti",     0,    0 }, { "ret",      0,    0 },

	/* 0xa0 */
	{ "jmpzh",  _A16,   0 }, { "jmpzl",  _A16,   0 }, { "jmpc",   _A16,   0 }, { "jmpz",   _A16,   0 },
	{ "jmpzc",  _A16,   0 }, { "jmpcl",  _A16,   0 }, { "jmpnc",  _A16,   0 }, { "jmpnz",  _A16,   0 },
	{ "callzh", _A16,   0 }, { "callzl", _A16,   0 }, { "callc",  _A16,   0 }, { "callz",  _A16,   0 },
	{ "callzc", _A16,   0 }, { "callcl", _A16,   0 }, { "callnc", _A16,   0 }, { "callnz", _A16,   0 },
	{ "unB0?",     0,   0 }, { "unB1?",   _I8,   0 }, { "unB2?",     0,   0 }, { "unB3?",   _I8,   0 },
	{ "out",   _KHI, _REG }, { "out",    _KHI, _I8 }, { "out",   _KLO, _REG }, { "out",    _KLO, _I8 },
	{ "unB8?",     0,   0 }, { "unB9?",   _I8,   0 }, { "unBA?",     0,   0 }, { "jmpcl?", _A16,   0 },
	{ "unBC?",     0,   0 }, { "unBD?",     0,   0 }, { "unBE?",     0,   0 }, { "jmpncl?", _A16,  0 },

	/* 0xc0 */
	{ "movb",  _REG,  _I8 }, { "movw",  _REG, _I16 }, { "movq",  _REG, _I64 }, { "movt",  _REG, _I80 },
	{ "movb",  _ILR, _ILR }, { "movw",  _ILR, _ILR }, { "movq",  _ILR, _ILR }, { "movt",  _ILR, _ILR },
	{ "unC8?",    0,    0 }, { "unC9?",    0,    0 }, { "unCA?",    0,    0 }, { "unCb?",    0,    0 },
	{ "swapb", _IRGREG, 0 }, { "swapw", _IRGREG, 0 }, { "swapq", _IRGREG, 0 }, { "swapt", _IRGREG, 0 },
	{ "movb",   _CS, _REG }, { "movb",   _CS,  _I8 }, { "movb",  _DSZ, _REG }, { "movb",  _DSZ,  _I8 },
	{ "movb",   _SS, _REG }, { "movb",   _SS,  _I8 }, { "movw",   _SP, _REG }, { "movw",   _SP, _I16 },
	{ "movb",    _F, _REG }, { "movb",    _F,  _I8 }, { "unDA?",    0,    0 }, { "unDb?",    0,    0 },
	{ "movb",   _DS, _REG }, { "movb",   _DS,  _I8 }, { "movw",  _LAR, _REG }, { "movw?",  _LAR, _I16 },

	/* 0xe0 */
	{ "in0",   _REG,    0 }, { "unE1?",  _I8,    0 }, { "in",    _REG,  _KI }, { "movb",  _REG, _DSZ },
	{ "movb",  _REG,   _F }, { "movb",  _REG, _TIM }, { "unE6?",  _I8,    0 }, { "unE7?",  _I8,    0 },
	{ "movw",  _REG, _LAR }, { "movw?", _REG, _LAR }, { "movw",  _REG,  _PC }, { "movw",  _REG,  _SP },
	{ "unEC?",    0,    0 }, { "movb",  _REG,  _DS }, { "movb",  _REG,  _CS }, { "movb",  _REG,  _SS },
	{ "unF0?",  _I8,    0 }, { "unF1?",  _I8,    0 }, { "unF2?",  _I8,    0 }, { "unF3?",  _I8,    0 },
	{ "unF4?",  _I8,    0 }, { "unF5?",  _I8,    0 }, { "unF6?",  _I8,    0 }, { "unF7?",  _I8,    0 },
	{ "unF8?",    0,    0 }, { "unF9?",    0,    0 }, { "unFA?",    0,    0 }, { "unFb?",    0,    0 },
	{ "unFC?",    0,    0 }, { "unFD?",    0,    0 }, { "unFE?",    0,    0 }, { "nop",      0,    0 }
};


CPU_DISASSEMBLE( hcd62121 )
{
	UINT8 op, op1=0, op2=0;
	int pos = 0;
=======
	{ "ro?b",    ARG_REG,    ARG_RS4  }, { "ro?w",    ARG_REG,    ARG_RS4  },
	{ "ro?q",    ARG_REG,    ARG_RS4  }, { "ro?t",    ARG_REG,    ARG_RS4  },
	{ "mskb",    ARG_REGREG, ARG_NONE }, { "mskw",    ARG_REGREG, ARG_NONE },
	{ "mskq",    ARG_REGREG, ARG_NONE }, { "mskt",    ARG_REGREG, ARG_NONE },
	{ "sh?b",    ARG_REG,    ARG_RS4  }, { "sh?w",    ARG_REG,    ARG_RS4  },
	{ "sh?q",    ARG_REG,    ARG_RS4  }, { "sh?t",    ARG_REG,    ARG_RS4  },
	{ "tstb",    ARG_REGREG, ARG_NONE }, { "tstw",    ARG_REGREG, ARG_NONE },
	{ "tstq",    ARG_REGREG, ARG_NONE }, { "tstt",    ARG_REGREG, ARG_NONE },

	/* 0x10 */
	{ "xorb",    ARG_REGREG, ARG_NONE }, { "xorw",    ARG_REGREG, ARG_NONE },
	{ "xorq",    ARG_REGREG, ARG_NONE }, { "xort",    ARG_REGREG, ARG_NONE },
	{ "cmpb",    ARG_REGREG, ARG_NONE }, { "cmpw",    ARG_REGREG, ARG_NONE },
	{ "cmpq",    ARG_REGREG, ARG_NONE }, { "cmpt",    ARG_REGREG, ARG_NONE },
	{ "movb",    ARG_REGREG, ARG_NONE }, { "movw",    ARG_REGREG, ARG_NONE },
	{ "movq",    ARG_REGREG, ARG_NONE }, { "movt",    ARG_REGREG, ARG_NONE },
	{ "imskb",   ARG_REGREG, ARG_NONE }, { "imskw",   ARG_REGREG, ARG_NONE },
	{ "imskq",   ARG_REGREG, ARG_NONE }, { "imskt",   ARG_REGREG, ARG_NONE },

	/* 0x20 */
	{ "ro?b",    ARG_REG,    ARG_RS   }, { "ro?w",    ARG_REG,    ARG_RS   },
	{ "ro?q",    ARG_REG,    ARG_RS   }, { "ro?t",    ARG_REG,    ARG_RS   },
	{ "orb",     ARG_REGREG, ARG_NONE }, { "orw",     ARG_REGREG, ARG_NONE },
	{ "orq",     ARG_REGREG, ARG_NONE }, { "ort",     ARG_REGREG, ARG_NONE },
	{ "sh?b",    ARG_REG,    ARG_RS   }, { "sh?w",    ARG_REG,    ARG_RS   },
	{ "sh?q",    ARG_REG,    ARG_RS   }, { "sh?t",    ARG_REG,    ARG_RS   },
	{ "andb",    ARG_REGREG, ARG_NONE }, { "andw",    ARG_REGREG, ARG_NONE },
	{ "andq",    ARG_REGREG, ARG_NONE }, { "andt",    ARG_REGREG, ARG_NONE },

	/* 0x30 */
	{ "sbbb",    ARG_REGREG, ARG_NONE }, { "sbbw",    ARG_REGREG, ARG_NONE }, /* BCD SUB */
	{ "sbbq",    ARG_REGREG, ARG_NONE }, { "sbbt",    ARG_REGREG, ARG_NONE }, /* BCD SUB */
	{ "subb",    ARG_REGREG, ARG_NONE }, { "subw",    ARG_REGREG, ARG_NONE },
	{ "subq",    ARG_REGREG, ARG_NONE }, { "subt",    ARG_REGREG, ARG_NONE },
	{ "adbb",    ARG_REGREG, ARG_NONE }, { "adbw",    ARG_REGREG, ARG_NONE }, /* BCD ADD */
	{ "adbq",    ARG_REGREG, ARG_NONE }, { "adbt",    ARG_REGREG, ARG_NONE }, /* BCD ADD */
	{ "addb",    ARG_REGREG, ARG_NONE }, { "addw",    ARG_REGREG, ARG_NONE },
	{ "addq",    ARG_REGREG, ARG_NONE }, { "addt",    ARG_REGREG, ARG_NONE },

	/* 0x40 */
	{ "ro?b",    ARG_IRG,    ARG_RS4  }, { "ro?w",    ARG_IRG,    ARG_RS4  },
	{ "ro?q",    ARG_IRG,    ARG_RS4  }, { "ro?t",    ARG_IRG,    ARG_RS4  },
	{ "mskb",    ARG_IRGREG, ARG_NONE }, { "mskw",    ARG_IRGREG, ARG_NONE },
	{ "mskq",    ARG_IRGREG, ARG_NONE }, { "mskt",    ARG_IRGREG, ARG_NONE },
	{ "sh?b",    ARG_IRG,    ARG_RS4  }, { "sh?w",    ARG_IRG,    ARG_RS4  },
	{ "sh?q",    ARG_IRG,    ARG_RS4  }, { "sh?t",    ARG_IRG,    ARG_RS4  },
	{ "tstb",    ARG_IRGREG, ARG_NONE }, { "tstw",    ARG_IRGREG, ARG_NONE },
	{ "tstq",    ARG_IRGREG, ARG_NONE }, { "tstt",    ARG_IRGREG, ARG_NONE },

	/* 0x50 */
	{ "xorb",    ARG_IRGREG, ARG_NONE }, { "xorw",    ARG_IRGREG, ARG_NONE },
	{ "xorq",    ARG_IRGREG, ARG_NONE }, { "xort",    ARG_IRGREG, ARG_NONE },
	{ "cmpb",    ARG_IRGREG, ARG_NONE }, { "cmpw",    ARG_IRGREG, ARG_NONE },
	{ "cmpq",    ARG_IRGREG, ARG_NONE }, { "cmpt",    ARG_IRGREG, ARG_NONE },
	{ "movb",    ARG_IRGREG, ARG_NONE }, { "movw",    ARG_IRGREG, ARG_NONE },
	{ "movq",    ARG_IRGREG, ARG_NONE }, { "movt",    ARG_IRGREG, ARG_NONE },
	{ "imskb",   ARG_IRGREG, ARG_NONE }, { "imskw",   ARG_IRGREG, ARG_NONE },
	{ "imskq",   ARG_IRGREG, ARG_NONE }, { "imskt",   ARG_IRGREG, ARG_NONE },

	/* 0x60 */
	{ "ro?b",    ARG_IRG,    ARG_RS   }, { "ro?w",    ARG_IRG,    ARG_RS   },
	{ "ro?q",    ARG_IRG,    ARG_RS   }, { "ro?t",    ARG_IRG,    ARG_RS   },
	{ "orb",     ARG_IRGREG, ARG_NONE }, { "orw",     ARG_IRGREG, ARG_NONE },
	{ "orq",     ARG_IRGREG, ARG_NONE }, { "ort",     ARG_IRGREG, ARG_NONE },
	{ "sh?b",    ARG_IRG,    ARG_RS   }, { "sh?w",    ARG_IRG,    ARG_RS   },
	{ "sh?q",    ARG_IRG,    ARG_RS   }, { "sh?t",    ARG_IRG,    ARG_RS   },
	{ "andb",    ARG_IRGREG, ARG_NONE }, { "andw",    ARG_IRGREG, ARG_NONE },
	{ "andq",    ARG_IRGREG, ARG_NONE }, { "andt",    ARG_IRGREG, ARG_NONE },

	/* 0x70 */
	{ "sbbb",    ARG_IRGREG, ARG_NONE }, { "sbbw",    ARG_IRGREG, ARG_NONE }, /* BCD SUB */
	{ "sbbq",    ARG_IRGREG, ARG_NONE }, { "sbbt",    ARG_IRGREG, ARG_NONE }, /* BCD SUB */
	{ "subb",    ARG_IRGREG, ARG_NONE }, { "subw",    ARG_IRGREG, ARG_NONE },
	{ "subq",    ARG_IRGREG, ARG_NONE }, { "subt",    ARG_IRGREG, ARG_NONE },
	{ "adbb",    ARG_IRGREG, ARG_NONE }, { "adbw",    ARG_IRGREG, ARG_NONE }, /* BCD ADD */
	{ "adbq",    ARG_IRGREG, ARG_NONE }, { "adbt",    ARG_IRGREG, ARG_NONE }, /* BCD ADD */
	{ "addb",    ARG_IRGREG, ARG_NONE }, { "addw",    ARG_IRGREG, ARG_NONE },
	{ "addq",    ARG_IRGREG, ARG_NONE }, { "addt",    ARG_IRGREG, ARG_NONE },

	/* 0x80 */
	{ "un80?",   ARG_NONE,   ARG_NONE }, { "un81?",   ARG_NONE,   ARG_NONE },
	{ "un82?",   ARG_NONE,   ARG_NONE }, { "un83?",   ARG_NONE,   ARG_NONE },
	{ "un84?",   ARG_NONE,   ARG_NONE }, { "un85?",   ARG_NONE,   ARG_NONE },
	{ "un86?",   ARG_NONE,   ARG_NONE }, { "un87?",   ARG_NONE,   ARG_NONE },
	{ "jump",    ARG_A16,    ARG_NONE }, { "jump",    ARG_A24,    ARG_NONE },
	{ "call",    ARG_A16,    ARG_NONE }, { "un8b?",   ARG_NONE,   ARG_NONE },
	{ "un8C?",   ARG_NONE,   ARG_NONE }, { "un8D?",   ARG_NONE,   ARG_NONE },
	{ "un8E?",   ARG_NONE,   ARG_NONE }, { "un8F?",   ARG_NONE,   ARG_NONE },

	/* 0x90 */
	{ "retzh",   ARG_NONE,   ARG_NONE }, { "retzl",   ARG_NONE,   ARG_NONE },
	{ "retc",    ARG_NONE,   ARG_NONE }, { "retz",    ARG_NONE,   ARG_NONE },
	{ "retzc",   ARG_NONE,   ARG_NONE }, { "retcl",   ARG_NONE,   ARG_NONE },
	{ "retnc",   ARG_NONE,   ARG_NONE }, { "retnz",   ARG_NONE,   ARG_NONE },
	{ "jump",    ARG_IRG,    ARG_NONE }, { "un99?",   ARG_NONE,   ARG_NONE },
	{ "un9A?",   ARG_NONE,   ARG_NONE }, { "un9b?",   ARG_NONE,   ARG_NONE },
	{ "un9C?",   ARG_NONE,   ARG_NONE }, { "un9D?",   ARG_NONE,   ARG_NONE },
	{ "reti",    ARG_NONE,   ARG_NONE }, { "ret",     ARG_NONE,   ARG_NONE },

	/* 0xa0 */
	{ "jmpzh",   ARG_A16,    ARG_NONE }, { "jmpzl",   ARG_A16,    ARG_NONE },
	{ "jmpc",    ARG_A16,    ARG_NONE }, { "jmpz",    ARG_A16,    ARG_NONE },
	{ "jmpzc",   ARG_A16,    ARG_NONE }, { "jmpcl",   ARG_A16,    ARG_NONE },
	{ "jmpnc",   ARG_A16,    ARG_NONE }, { "jmpnz",   ARG_A16,    ARG_NONE },
	{ "callzh",  ARG_A16,    ARG_NONE }, { "callzl",  ARG_A16,    ARG_NONE },
	{ "callc",   ARG_A16,    ARG_NONE }, { "callz",   ARG_A16,    ARG_NONE },
	{ "callzc",  ARG_A16,    ARG_NONE }, { "callcl",  ARG_A16,    ARG_NONE },
	{ "callnc",  ARG_A16,    ARG_NONE }, { "callnz",  ARG_A16,    ARG_NONE },

	/* 0xb0 */
	{ "unB0?",   ARG_NONE,   ARG_NONE }, { "unB1?",   ARG_I8,     ARG_NONE },
	{ "unB2?",   ARG_NONE,   ARG_NONE }, { "unB3?",   ARG_I8,     ARG_NONE },
	{ "out",     ARG_KHI,    ARG_REG  }, { "out",     ARG_KHI,    ARG_I8   },
	{ "out",     ARG_KLO,    ARG_REG  }, { "out",     ARG_KLO,    ARG_I8   },
	{ "unB8?",   ARG_NONE,   ARG_NONE }, { "unB9?",   ARG_I8,     ARG_NONE },
	{ "unBA?",   ARG_NONE,   ARG_NONE }, { "jmpcl?",  ARG_A16,    ARG_NONE },
	{ "unBC?",   ARG_I8,     ARG_NONE }, { "unBD?",   ARG_NONE,   ARG_NONE },
	{ "unBE?",   ARG_NONE,   ARG_NONE }, { "jmpncl?", ARG_A16,    ARG_NONE },

	/* 0xc0 */
	{ "movb",    ARG_REG,    ARG_I8   }, { "movw",    ARG_REG,    ARG_I16  },
	{ "movq",    ARG_REG,    ARG_I64  }, { "movt",    ARG_REG,    ARG_I80  },
	{ "movb",    ARG_ILR,    ARG_ILR  }, { "movw",    ARG_ILR,    ARG_ILR  },
	{ "movq",    ARG_ILR,    ARG_ILR  }, { "movt",    ARG_ILR,    ARG_ILR  },
	{ "unC8?",   ARG_NONE,   ARG_NONE }, { "unC9?",   ARG_NONE,   ARG_NONE },
	{ "unCA?",   ARG_NONE,   ARG_NONE }, { "unCb?",   ARG_NONE,   ARG_NONE },
	{ "swapb",   ARG_IRGREG, ARG_NONE }, { "swapw",   ARG_IRGREG, ARG_NONE },
	{ "swapq",   ARG_IRGREG, ARG_NONE }, { "swapt",   ARG_IRGREG, ARG_NONE },

	/* 0xd0 */
	{ "movb",    ARG_CS,     ARG_REG  }, { "movb",    ARG_CS,     ARG_I8   },
	{ "movb",    ARG_DSZ,    ARG_REG  }, { "movb",    ARG_DSZ,    ARG_I8   },
	{ "movb",    ARG_SS,     ARG_REG  }, { "movb",    ARG_SS,     ARG_I8   },
	{ "movw",    ARG_SP,     ARG_REG  }, { "movw",    ARG_SP,     ARG_I16  },
	{ "movb",    ARG_F,      ARG_REG  }, { "movb",    ARG_F,      ARG_I8   },
	{ "unDA?",   ARG_NONE,   ARG_NONE }, { "unDb?",   ARG_NONE,   ARG_NONE },
	{ "movb",    ARG_DS,     ARG_REG  }, { "movb",    ARG_DS,     ARG_I8   },
	{ "movw",    ARG_LAR,    ARG_REG  }, { "movw?",   ARG_LAR,    ARG_I8   },

	/* 0xe0 */
	{ "in0",     ARG_REG,    ARG_NONE }, { "movb",    ARG_REG,    ARG_OPT  },
	{ "in",      ARG_REG,    ARG_KI   }, { "movb",    ARG_REG,    ARG_DSZ  },
	{ "movb",    ARG_REG,    ARG_F    }, { "unE5?",   ARG_I8,     ARG_NONE },
	{ "movb",    ARG_REG,    ARG_PORT }, { "unE7?",   ARG_I8,     ARG_NONE },
	{ "movw",    ARG_REG,    ARG_LAR  }, { "movw?",   ARG_REG,    ARG_LAR  },
	{ "movw",    ARG_REG,    ARG_PC   }, { "movw",    ARG_REG,    ARG_SP   },
	{ "unEC?",   ARG_NONE,   ARG_NONE }, { "movb",    ARG_REG,    ARG_DS   },
	{ "movb",    ARG_REG,    ARG_CS   }, { "movb",    ARG_REG,    ARG_SS   },

	/* 0xf0 */
	{ "movb",    ARG_OPT,    ARG_REG  }, { "unF1?",   ARG_I8,     ARG_NONE },
	{ "movb",    ARG_PORT,   ARG_REG  }, { "unF3?",   ARG_I8,     ARG_NONE },
	{ "unF4?",   ARG_I8,     ARG_NONE }, { "unF5?",   ARG_I8,     ARG_NONE },
	{ "unF6?",   ARG_I8,     ARG_NONE }, { "unF7?",   ARG_I8,     ARG_NONE },
	{ "unF8?",   ARG_NONE,   ARG_NONE }, { "unF9?",   ARG_NONE,   ARG_NONE },
	{ "unFA?",   ARG_NONE,   ARG_NONE }, { "unFb?",   ARG_NONE,   ARG_NONE },
	{ "unFC?",   ARG_NONE,   ARG_NONE }, { "unFD?",   ARG_NONE,   ARG_NONE },
	{ "unFE?",   ARG_NONE,   ARG_NONE }, { "nop",     ARG_NONE,   ARG_NONE }
};


CPU_DISASSEMBLE(hcd62121)
{
	u8 op;
	u8 op1;
	u8 op2;
	u32 pos = 0;
>>>>>>> upstream/master
	const hcd62121_dasm *inst;

	op = oprom[pos++];

	inst = &hcd62121_ops[op];

<<<<<<< HEAD
	/* Special case for nibble shift instruction */
	if ( inst->arg2 == _4 )
		buffer += sprintf(buffer,"sh%c%c    ", ( oprom[pos] & 0x80 ) ? 'l' : 'r', inst->str[3]);
	else
		buffer += sprintf(buffer,"%-8s", inst->str);

	switch( inst->arg1 )
	{
	case _REGREG:
		op1 = oprom[pos++];
		op2 = oprom[pos++];
		if ( op1 & 0x80 )
		{
			buffer += sprintf( buffer, "r%02x,0x%02x", op1 & 0x7f, op2 );
		}
		else
		{
			if ( op2 & 0x80 )
				buffer += sprintf( buffer, "r%02x,r%02x", op1 & 0x7f, op2 & 0x7f );
			else
				buffer += sprintf( buffer, "r%02x,r%02x", op2 & 0x7f, op1 & 0x7f );
		}
		break;
	case _REG:
		buffer += sprintf( buffer, "r%02x", oprom[pos++] & 0x7f );
		break;
	case _IRGREG:
		/* bit 6 = direction. 0 - regular, 1 - reverse */
		op1 = oprom[pos++];
		op2 = oprom[pos++];
		if ( op1 & 0x80 )
		{
			buffer += sprintf( buffer, "(r%02x),0x%02x", 0x40 | ( op1 & 0x3f ), op2 );
		}
		else
		{
			if ( op2 & 0x80 )
				buffer += sprintf( buffer, "(r%02x%s),r%02x", 0x40 | ( op1 & 0x3f ), (op1 & 0x40) ? ".r" : "", op2 & 0x7f );
			else
				buffer += sprintf( buffer, "r%02x,(r%02x%s)", op2 & 0x7f, 0x40 | ( op1 & 0x3f ), (op1 & 0x40) ? ".r" : "" );
		}
		break;
	case _IRG:
		/* bit 6 = direction. 0 - regular, 1 - reverse */
		op1 = oprom[pos++];
		buffer += sprintf( buffer, "(r%02x%s)", 0x40 | ( op1 & 0x3f ), (op1 & 0x40) ? ".r" : "" );
		break;
	case _F:
		buffer += sprintf( buffer, "F" );
		break;
	case _CS:
		buffer += sprintf( buffer, "CS" );
		break;
	case _DS:
		buffer += sprintf( buffer, "DS" );
		break;
	case _SS:
		buffer += sprintf( buffer, "SS" );
		break;
	case _PC:
		buffer += sprintf( buffer, "PC" );
		break;
	case _SP:
		buffer += sprintf( buffer, "SP" );
		break;
	case _I8:
		buffer += sprintf( buffer, "0x%02x", oprom[pos++] );
		break;
	case _I16:
	case _A16:
		buffer += sprintf( buffer, "0x%02x", oprom[pos++] );
		buffer += sprintf( buffer, "%02x", oprom[pos++] );
		break;
	case _I64:
		buffer += sprintf( buffer, "0x%02x", oprom[pos++] );
		buffer += sprintf( buffer, "%02x", oprom[pos++] );
		buffer += sprintf( buffer, "%02x", oprom[pos++] );
		buffer += sprintf( buffer, "%02x", oprom[pos++] );
		buffer += sprintf( buffer, "%02x", oprom[pos++] );
		buffer += sprintf( buffer, "%02x", oprom[pos++] );
		buffer += sprintf( buffer, "%02x", oprom[pos++] );
		buffer += sprintf( buffer, "%02x", oprom[pos++] );
		break;
	case _I80:
		buffer += sprintf( buffer, "0x%02x", oprom[pos++] );
		buffer += sprintf( buffer, "%02x", oprom[pos++] );
		buffer += sprintf( buffer, "%02x", oprom[pos++] );
		buffer += sprintf( buffer, "%02x", oprom[pos++] );
		buffer += sprintf( buffer, "%02x", oprom[pos++] );
		buffer += sprintf( buffer, "%02x", oprom[pos++] );
		buffer += sprintf( buffer, "%02x", oprom[pos++] );
		buffer += sprintf( buffer, "%02x", oprom[pos++] );
		buffer += sprintf( buffer, "%02x", oprom[pos++] );
		buffer += sprintf( buffer, "%02x", oprom[pos++] );
		break;
	case _A24:
		buffer += sprintf( buffer, "0x%02x:", oprom[pos++] );
		buffer += sprintf( buffer, "0x%02x", oprom[pos++] );
		buffer += sprintf( buffer, "%02x", oprom[pos++] );
		break;
	case _ILR:
		op1 = oprom[pos++];
		op2 = oprom[pos++];
		if ( ( op1 & 0x80 ) || ( op2 & 0x80 ) )
		{
			/* (lar),reg */
				buffer += sprintf( buffer, "(%slar%s),r%02x", (op1 & 0x20) ? ( (op1 & 0x40) ? "--" : "++" ) : "", (op1 & 0x20) ? "" : ( (op1 & 0x40) ? "--" : "++" ), op2 & 0x7f );
=======
	/* Special cases for shift and rotate instructions */
	if (inst->arg2 == ARG_RS || inst->arg2 == ARG_RS4)
		util::stream_format(stream, "%c%c%c%c    ", inst->str[0], inst->str[1], (oprom[pos] & 0x80) ? 'r' : 'l', inst->str[3]);
	else
		util::stream_format(stream, "%-8s", inst->str);

	switch(inst->arg1)
	{
	case ARG_REGREG:
		op1 = oprom[pos++];
		op2 = oprom[pos++];
		if (op1 & 0x80)
		{
			util::stream_format(stream, "r%02x,0x%02x", op1 & 0x7f, op2);
		}
		else
		{
			if (op2 & 0x80)
				util::stream_format(stream, "r%02x,r%02x", op1 & 0x7f, op2 & 0x7f);
			else
				util::stream_format(stream, "r%02x,r%02x", op2 & 0x7f, op1 & 0x7f);
		}
		break;
	case ARG_REG:
		util::stream_format(stream, "r%02x", oprom[pos++] & 0x7f);
		break;
	case ARG_IRGREG:
		/* bit 6 = direction. 0 - regular, 1 - reverse */
		op1 = oprom[pos++];
		op2 = oprom[pos++];
		if (op1 & 0x80)
		{
			util::stream_format(stream, "(r%02x),0x%02x", 0x40 | (op1 & 0x3f), op2);
		}
		else
		{
			if (op2 & 0x80)
				util::stream_format(stream, "(r%02x%s),r%02x", 0x40 | (op1 & 0x3f), (op1 & 0x40) ? ".r" : "", op2 & 0x7f);
			else
				util::stream_format(stream, "r%02x,(r%02x%s)", op2 & 0x7f, 0x40 | (op1 & 0x3f), (op1 & 0x40) ? ".r" : "");
		}
		break;
	case ARG_IRG:
		/* bit 6 = direction. 0 - regular, 1 - reverse */
		op1 = oprom[pos++];
		util::stream_format(stream, "(r%02x%s)", 0x40 | (op1 & 0x3f), (op1 & 0x40) ? ".r" : "");
		break;
	case ARG_F:
		util::stream_format(stream, "F");
		break;
	case ARG_CS:
		util::stream_format(stream, "CS");
		break;
	case ARG_DS:
		util::stream_format(stream, "DS");
		break;
	case ARG_SS:
		util::stream_format(stream, "SS");
		break;
	case ARG_PC:
		util::stream_format(stream, "PC");
		break;
	case ARG_SP:
		util::stream_format(stream, "SP");
		break;
	case ARG_I8:
		util::stream_format(stream, "0x%02x", oprom[pos++]);
		break;
	case ARG_I16:
	case ARG_A16:
		util::stream_format(stream, "0x%02x", oprom[pos++]);
		util::stream_format(stream, "%02x", oprom[pos++]);
		break;
	case ARG_I64:
		util::stream_format(stream, "0x%02x", oprom[pos++]);
		util::stream_format(stream, "%02x", oprom[pos++]);
		util::stream_format(stream, "%02x", oprom[pos++]);
		util::stream_format(stream, "%02x", oprom[pos++]);
		util::stream_format(stream, "%02x", oprom[pos++]);
		util::stream_format(stream, "%02x", oprom[pos++]);
		util::stream_format(stream, "%02x", oprom[pos++]);
		util::stream_format(stream, "%02x", oprom[pos++]);
		break;
	case ARG_I80:
		util::stream_format(stream, "0x%02x", oprom[pos++]);
		util::stream_format(stream, "%02x", oprom[pos++]);
		util::stream_format(stream, "%02x", oprom[pos++]);
		util::stream_format(stream, "%02x", oprom[pos++]);
		util::stream_format(stream, "%02x", oprom[pos++]);
		util::stream_format(stream, "%02x", oprom[pos++]);
		util::stream_format(stream, "%02x", oprom[pos++]);
		util::stream_format(stream, "%02x", oprom[pos++]);
		util::stream_format(stream, "%02x", oprom[pos++]);
		util::stream_format(stream, "%02x", oprom[pos++]);
		break;
	case ARG_A24:
		util::stream_format(stream, "0x%02x:", oprom[pos++]);
		util::stream_format(stream, "0x%02x", oprom[pos++]);
		util::stream_format(stream, "%02x", oprom[pos++]);
		break;
	case ARG_ILR:
		op1 = oprom[pos++];
		op2 = oprom[pos++];
		if ((op1 & 0x80) || (op2 & 0x80))
		{
			/* (lar),reg */
			util::stream_format(stream, "(%slar%s),r%02x", (op1 & 0x20) ? ((op1 & 0x40) ? "--" : "++") : "", (op1 & 0x20) ? "" : ((op1 & 0x40) ? "--" : "++"), op2 & 0x7f);
>>>>>>> upstream/master
		}
		else
		{
			/* reg,(lar) */
<<<<<<< HEAD
			buffer += sprintf( buffer, "r%02x,(%slar%s)", op2 & 0x7f, (op1 & 0x20) ? ( (op1 & 0x40) ? "--" : "++" ) : "", (op1 & 0x20) ? "" : ( (op1 & 0x40) ? "--" : "++" ) );
		}
		break;
	case _LAR:
		buffer += sprintf( buffer, "lar" );
		break;
	case _DSZ:
		buffer += sprintf( buffer, "dsize" );
		break;
	case _TIM:
		buffer += sprintf( buffer, "TIM?" );
		break;
	case _KLO:
		buffer += sprintf( buffer, "KOL" );
		break;
	case _KHI:
		buffer += sprintf( buffer, "KOH" );
=======
			util::stream_format(stream, "r%02x,(%slar%s)", op2 & 0x7f, (op1 & 0x20) ? ((op1 & 0x40) ? "--" : "++") : "", (op1 & 0x20) ? "" : ((op1 & 0x40) ? "--" : "++"));
		}
		break;
	case ARG_LAR:
		util::stream_format(stream, "lar");
		break;
	case ARG_DSZ:
		util::stream_format(stream, "dsize");
		break;
	case ARG_OPT:
		util::stream_format(stream, "OPT");
		break;
	case ARG_PORT:
		util::stream_format(stream, "PORT");
		break;
	case ARG_TIM:
		util::stream_format(stream, "TIM?");
		break;
	case ARG_KLO:
		util::stream_format(stream, "KOL");
		break;
	case ARG_KHI:
		util::stream_format(stream, "KOH");
>>>>>>> upstream/master
		break;
	default:
		break;
	}

<<<<<<< HEAD
	switch( inst->arg2 )
	{
	case _REG:
		buffer += sprintf( buffer, ",r%02x", oprom[pos++] & 0x7f );
		break;
	case _F:
		buffer += sprintf( buffer, ",F" );
		break;
	case _CS:
		buffer += sprintf( buffer, ",CS" );
		break;
	case _DS:
		buffer += sprintf( buffer, ",DS" );
		break;
	case _SS:
		buffer += sprintf( buffer, ",SS" );
		break;
	case _PC:
		buffer += sprintf( buffer, ",PC" );
		break;
	case _SP:
		buffer += sprintf( buffer, ",SP" );
		break;
	case _I8:
		buffer += sprintf( buffer, ",0x%02x", oprom[pos++] );
		break;
	case _I16:
	case _A16:
		buffer += sprintf( buffer, ",0x%02x", oprom[pos++] );
		buffer += sprintf( buffer, "%02x", oprom[pos++] );
		break;
	case _I64:
		buffer += sprintf( buffer, ",0x%02x", oprom[pos++] );
		buffer += sprintf( buffer, "%02x", oprom[pos++] );
		buffer += sprintf( buffer, "%02x", oprom[pos++] );
		buffer += sprintf( buffer, "%02x", oprom[pos++] );
		buffer += sprintf( buffer, "%02x", oprom[pos++] );
		buffer += sprintf( buffer, "%02x", oprom[pos++] );
		buffer += sprintf( buffer, "%02x", oprom[pos++] );
		buffer += sprintf( buffer, "%02x", oprom[pos++] );
		break;
	case _I80:
		buffer += sprintf( buffer, ",0x%02x", oprom[pos++] );
		buffer += sprintf( buffer, "%02x", oprom[pos++] );
		buffer += sprintf( buffer, "%02x", oprom[pos++] );
		buffer += sprintf( buffer, "%02x", oprom[pos++] );
		buffer += sprintf( buffer, "%02x", oprom[pos++] );
		buffer += sprintf( buffer, "%02x", oprom[pos++] );
		buffer += sprintf( buffer, "%02x", oprom[pos++] );
		buffer += sprintf( buffer, "%02x", oprom[pos++] );
		buffer += sprintf( buffer, "%02x", oprom[pos++] );
		buffer += sprintf( buffer, "%02x", oprom[pos++] );
		break;
	case _A24:
		buffer += sprintf( buffer, ",0x%02x:", oprom[pos++] );
		buffer += sprintf( buffer, "0x%02x", oprom[pos++] );
		buffer += sprintf( buffer, "%02x", oprom[pos++] );
		break;
	case _ILR:
		/* Implemented by _ILR section for arg1 */
		break;
	case _LAR:
		buffer += sprintf( buffer, ",lar" );
		break;
	case _DSZ:
		buffer += sprintf( buffer, ",dsize" );
		break;
	case _TIM:
		buffer += sprintf( buffer, ",TIM?" );
		break;
	case _KI:
		buffer += sprintf( buffer, ",KI" );
		break;
	case _4:
		buffer += sprintf( buffer, ",4" );
=======
	switch(inst->arg2)
	{
	case ARG_REG:
		util::stream_format(stream, ",r%02x", oprom[pos++] & 0x7f);
		break;
	case ARG_F:
		util::stream_format(stream, ",F");
		break;
	case ARG_CS:
		util::stream_format(stream, ",CS");
		break;
	case ARG_DS:
		util::stream_format(stream, ",DS");
		break;
	case ARG_SS:
		util::stream_format(stream, ",SS");
		break;
	case ARG_PC:
		util::stream_format(stream, ",PC");
		break;
	case ARG_SP:
		util::stream_format(stream, ",SP");
		break;
	case ARG_I8:
		util::stream_format(stream, ",0x%02x", oprom[pos++]);
		break;
	case ARG_I16:
		util::stream_format(stream, ",0x%02x", oprom[pos+1]);
		util::stream_format(stream, "%02x", oprom[pos]);
		pos += 2;
		break;
	case ARG_A16:
		util::stream_format(stream, ",0x%02x", oprom[pos++]);
		util::stream_format(stream, "%02x", oprom[pos++]);
		break;
	case ARG_I64:
		util::stream_format(stream, ",0x%02x", oprom[pos++]);
		util::stream_format(stream, "%02x", oprom[pos++]);
		util::stream_format(stream, "%02x", oprom[pos++]);
		util::stream_format(stream, "%02x", oprom[pos++]);
		util::stream_format(stream, "%02x", oprom[pos++]);
		util::stream_format(stream, "%02x", oprom[pos++]);
		util::stream_format(stream, "%02x", oprom[pos++]);
		util::stream_format(stream, "%02x", oprom[pos++]);
		break;
	case ARG_I80:
		util::stream_format(stream, ",0x%02x", oprom[pos++]);
		util::stream_format(stream, "%02x", oprom[pos++]);
		util::stream_format(stream, "%02x", oprom[pos++]);
		util::stream_format(stream, "%02x", oprom[pos++]);
		util::stream_format(stream, "%02x", oprom[pos++]);
		util::stream_format(stream, "%02x", oprom[pos++]);
		util::stream_format(stream, "%02x", oprom[pos++]);
		util::stream_format(stream, "%02x", oprom[pos++]);
		util::stream_format(stream, "%02x", oprom[pos++]);
		util::stream_format(stream, "%02x", oprom[pos++]);
		break;
	case ARG_A24:
		util::stream_format(stream, ",0x%02x:", oprom[pos++]);
		util::stream_format(stream, "0x%02x", oprom[pos++]);
		util::stream_format(stream, "%02x", oprom[pos++]);
		break;
	case ARG_ILR:
		/* Implemented by ARG_ILR section for arg1 */
		break;
	case ARG_LAR:
		util::stream_format(stream, ",lar");
		break;
	case ARG_DSZ:
		util::stream_format(stream, ",dsize");
		break;
	case ARG_OPT:
		util::stream_format(stream, ",OPT");
		break;
	case ARG_PORT:
		util::stream_format(stream, ",PORT");
		break;
	case ARG_TIM:
		util::stream_format(stream, ",TIM?");
		break;
	case ARG_KI:
		util::stream_format(stream, ",KI");
		break;
	case ARG_RS4:
		util::stream_format(stream, ",4");
>>>>>>> upstream/master
		break;
	default:
		break;
	}

	return pos | DASMFLAG_SUPPORTED;
}
<<<<<<< HEAD
=======

>>>>>>> upstream/master
