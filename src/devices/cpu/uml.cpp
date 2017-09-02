// license:BSD-3-Clause
// copyright-holders:Aaron Giles
/***************************************************************************

    uml.c

    Universal machine language definitions and classes.

****************************************************************************

    Future improvements/changes:

    * UML optimizer:
        - constant folding

    * Write a back-end validator:
        - checks all combinations of memory/register/immediate on all params
        - checks behavior of all opcodes

    * Extend registers to 16? Depends on if PPC can use them

    * Support for FPU exceptions

    * New instructions?
<<<<<<< HEAD
        - FCOPYI, ICOPYF
            copy raw between float and integer registers

=======
>>>>>>> upstream/master
        - VALID opcode_desc,handle,param
            checksum/compare code referenced by opcode_desc; if not
            matching, generate exception with handle,param

        - RECALL handle
            change code at caller to call handle in the future

***************************************************************************/

#include "emu.h"
#include "drcuml.h"
#include "drcumlsh.h"

using namespace uml;



//**************************************************************************
//  DEBUGGING
//**************************************************************************

#define VALIDATE_BACKEND        (0)
#define LOG_SIMPLIFICATIONS     (0)



//**************************************************************************
//  CONSTANTS
//**************************************************************************

// opcode validation condition/flag valid bitmasks
#define OPFLAGS_NONE    0x00
#define OPFLAGS_C       FLAG_C
<<<<<<< HEAD
=======
#define OPFLAGS_Z       FLAG_Z
>>>>>>> upstream/master
#define OPFLAGS_SZ      (FLAG_S | FLAG_Z)
#define OPFLAGS_SZC     (FLAG_S | FLAG_Z | FLAG_C)
#define OPFLAGS_SZV     (FLAG_S | FLAG_Z | FLAG_V)
#define OPFLAGS_SZVC    (FLAG_S | FLAG_Z | FLAG_V | FLAG_C)
#define OPFLAGS_UZC     (FLAG_U | FLAG_Z | FLAG_C)
#define OPFLAGS_ALL     0x1f
#define OPFLAGS_P1      0x81
#define OPFLAGS_P2      0x82
#define OPFLAGS_P3      0x83
#define OPFLAGS_P4      0x84

// parameter input/output states
#define PIO_IN          0x01
#define PIO_OUT         0x02
#define PIO_INOUT       (PIO_IN | PIO_OUT)

// parameter sizes
#define PSIZE_4         SIZE_DWORD
#define PSIZE_8         SIZE_QWORD
#define PSIZE_OP        0x80
#define PSIZE_P1        0x81
#define PSIZE_P2        0x82
#define PSIZE_P3        0x83
#define PSIZE_P4        0x84

// basic parameter types
#define PTYPES_NONE     0
#define PTYPES_IMM      (1 << parameter::PTYPE_IMMEDIATE)
#define PTYPES_IREG     (1 << parameter::PTYPE_INT_REGISTER)
#define PTYPES_FREG     (1 << parameter::PTYPE_FLOAT_REGISTER)
#define PTYPES_VREG     (1 << parameter::PTYPE_VECTOR_REGISTER)
#define PTYPES_MVAR     (1 << parameter::PTYPE_MAPVAR)
#define PTYPES_MEM      (1 << parameter::PTYPE_MEMORY)
#define PTYPES_SIZE     (1 << parameter::PTYPE_SIZE)
#define PTYPES_SCSIZE   (1 << parameter::PTYPE_SIZE_SCALE)
#define PTYPES_SPSIZE   (1 << parameter::PTYPE_SIZE_SPACE)
#define PTYPES_HANDLE   (1 << parameter::PTYPE_CODE_HANDLE)
#define PTYPES_LABEL    (1 << parameter::PTYPE_CODE_LABEL)
#define PTYPES_CFUNC    (1 << parameter::PTYPE_C_FUNCTION)
#define PTYPES_ROUND    (1 << parameter::PTYPE_ROUNDING)
#define PTYPES_STR      (1 << parameter::PTYPE_STRING)

// special parameter types
#define PTYPES_PTR      (PTYPES_MEM | 0x1000)
#define PTYPES_STATE    (PTYPES_MEM | 0x2000)

// combinations of types
#define PTYPES_IRM      (PTYPES_IREG | PTYPES_MEM)
#define PTYPES_FRM      (PTYPES_FREG | PTYPES_MEM)
#define PTYPES_IMV      (PTYPES_IMM | PTYPES_MVAR)
#define PTYPES_IANY     (PTYPES_IRM | PTYPES_IMV)
#define PTYPES_FANY     (PTYPES_FRM)



//**************************************************************************
//  TABLES
//**************************************************************************

// macro to simplify the table
#define PINFO(inout, size, types)                                   { PIO_##inout, PSIZE_##size, PTYPES_##types }
#define OPINFO0(op,str,sizes,cond,iflag,oflag,mflag)                { OP_##op, str, sizes, cond, OPFLAGS_##iflag, OPFLAGS_##oflag, OPFLAGS_##mflag, { { 0 } } },
#define OPINFO1(op,str,sizes,cond,iflag,oflag,mflag,p0)             { OP_##op, str, sizes, cond, OPFLAGS_##iflag, OPFLAGS_##oflag, OPFLAGS_##mflag, { p0 } },
#define OPINFO2(op,str,sizes,cond,iflag,oflag,mflag,p0,p1)          { OP_##op, str, sizes, cond, OPFLAGS_##iflag, OPFLAGS_##oflag, OPFLAGS_##mflag, { p0, p1 } },
#define OPINFO3(op,str,sizes,cond,iflag,oflag,mflag,p0,p1,p2)       { OP_##op, str, sizes, cond, OPFLAGS_##iflag, OPFLAGS_##oflag, OPFLAGS_##mflag, { p0, p1, p2 } },
#define OPINFO4(op,str,sizes,cond,iflag,oflag,mflag,p0,p1,p2,p3)    { OP_##op, str, sizes, cond, OPFLAGS_##iflag, OPFLAGS_##oflag, OPFLAGS_##mflag, { p0, p1, p2, p3 } },

// opcode validation table
const opcode_info instruction::s_opcode_info_table[OP_MAX] =
{
	OPINFO0(INVALID, "invalid",  4,   false, NONE, NONE, NONE)

	// Compile-time opcodes
	OPINFO1(HANDLE,  "handle",   4,   false, NONE, NONE, NONE, PINFO(IN, OP, HANDLE))
	OPINFO2(HASH,    "hash",     4,   false, NONE, NONE, NONE, PINFO(IN, OP, IMV), PINFO(IN, OP, IMV))
	OPINFO1(LABEL,   "label",    4,   false, NONE, NONE, NONE, PINFO(IN, OP, LABEL))
	OPINFO1(COMMENT, "comment",  4,   false, NONE, NONE, NONE, PINFO(IN, OP, STR))
	OPINFO2(MAPVAR,  "mapvar",   4,   false, NONE, NONE, NONE, PINFO(OUT, OP, MVAR), PINFO(IN, OP, IMV))

	// Control Flow Operations
	OPINFO0(NOP,     "nop",      4,   false, NONE, NONE, NONE)
	OPINFO1(DEBUG,   "debug",    4,   false, NONE, NONE, ALL,  PINFO(IN, OP, IANY))
	OPINFO1(EXIT,    "exit",     4,   true,  NONE, NONE, ALL,  PINFO(IN, OP, IANY))
	OPINFO3(HASHJMP, "hashjmp",  4,   false, NONE, NONE, ALL,  PINFO(IN, OP, IANY), PINFO(IN, OP, IANY), PINFO(IN, OP, HANDLE))
	OPINFO1(JMP,     "jmp",      4,   true,  NONE, NONE, NONE, PINFO(IN, OP, LABEL))
	OPINFO2(EXH,     "exh",      4,   true,  NONE, NONE, ALL,  PINFO(IN, OP, HANDLE), PINFO(IN, OP, IANY))
	OPINFO1(CALLH,   "callh",    4,   true,  NONE, NONE, ALL,  PINFO(IN, OP, HANDLE))
	OPINFO0(RET,     "ret",      4,   true,  NONE, NONE, ALL)
	OPINFO2(CALLC,   "callc",    4,   true,  NONE, NONE, ALL,  PINFO(IN, OP, CFUNC), PINFO(IN, OP, PTR))
	OPINFO2(RECOVER, "recover",  4,   false, NONE, NONE, ALL,  PINFO(OUT, OP, IRM), PINFO(IN, OP, MVAR))

	// Internal Register Operations
	OPINFO1(SETFMOD, "setfmod",  4,   false, NONE, NONE, ALL,  PINFO(IN, OP, IANY))
	OPINFO1(GETFMOD, "getfmod",  4,   false, NONE, NONE, ALL,  PINFO(OUT, OP, IRM))
	OPINFO1(GETEXP,  "getexp",   4,   false, NONE, NONE, ALL,  PINFO(OUT, OP, IRM))
	OPINFO2(GETFLGS, "getflgs",  4,   false, P2,   NONE, ALL,  PINFO(OUT, OP, IRM), PINFO(IN, OP, IMV))
	OPINFO1(SAVE,    "save",     4,   false, ALL,  NONE, ALL,  PINFO(OUT, OP, STATE))
	OPINFO1(RESTORE, "restore",  4,   false, NONE, ALL,  ALL,  PINFO(IN, OP, STATE))

	// Integer Operations
	OPINFO4(LOAD,    "!load",    4|8, false, NONE, NONE, ALL,  PINFO(OUT, OP, IRM), PINFO(IN, OP, PTR), PINFO(IN, 4, IANY), PINFO(IN, OP, SCSIZE))
	OPINFO4(LOADS,   "!loads",   4|8, false, NONE, NONE, ALL,  PINFO(OUT, OP, IRM), PINFO(IN, OP, PTR), PINFO(IN, 4, IANY), PINFO(IN, OP, SCSIZE))
	OPINFO4(STORE,   "!store",   4|8, false, NONE, NONE, ALL,  PINFO(IN, OP, PTR), PINFO(IN, 4, IANY), PINFO(IN, OP, IANY), PINFO(IN, OP, SCSIZE))
	OPINFO3(READ,    "!read",    4|8, false, NONE, NONE, ALL,  PINFO(OUT, OP, IRM), PINFO(IN, 4, IANY), PINFO(IN, OP, SPSIZE))
	OPINFO4(READM,   "!readm",   4|8, false, NONE, NONE, ALL,  PINFO(OUT, OP, IRM), PINFO(IN, 4, IANY), PINFO(IN, OP, IANY), PINFO(IN, OP, SPSIZE))
	OPINFO3(WRITE,   "!write",   4|8, false, NONE, NONE, ALL,  PINFO(IN, 4, IANY), PINFO(IN, OP, IANY), PINFO(IN, OP, SPSIZE))
	OPINFO4(WRITEM,  "!writem",  4|8, false, NONE, NONE, ALL,  PINFO(IN, 4, IANY), PINFO(IN, OP, IANY), PINFO(IN, OP, IANY), PINFO(IN, OP, SPSIZE))
	OPINFO2(CARRY,   "!carry",   4|8, false, NONE, C,    ALL,  PINFO(IN, OP, IANY), PINFO(IN, OP, IANY))
	OPINFO1(SET,     "!set",     4|8, true,  NONE, NONE, ALL,  PINFO(OUT, OP, IRM))
	OPINFO2(MOV,     "!mov",     4|8, true,  NONE, NONE, NONE, PINFO(OUT, OP, IRM), PINFO(IN, OP, IANY))
	OPINFO3(SEXT,    "!sext",    4|8, false, NONE, SZ,   ALL,  PINFO(OUT, OP, IRM), PINFO(IN, P3, IANY), PINFO(IN, OP, SIZE))
	OPINFO4(ROLAND,  "!roland",  4|8, false, NONE, SZ,   ALL,  PINFO(OUT, OP, IRM), PINFO(IN, OP, IANY), PINFO(IN, OP, IANY), PINFO(IN, OP, IANY))
	OPINFO4(ROLINS,  "!rolins",  4|8, false, NONE, SZ,   ALL,  PINFO(INOUT, OP, IRM), PINFO(IN, OP, IANY), PINFO(IN, OP, IANY), PINFO(IN, OP, IANY))
	OPINFO3(ADD,     "!add",     4|8, false, NONE, SZVC, ALL,  PINFO(OUT, OP, IRM), PINFO(IN, OP, IANY), PINFO(IN, OP, IANY))
	OPINFO3(ADDC,    "!addc",    4|8, false, C,    SZVC, ALL,  PINFO(OUT, OP, IRM), PINFO(IN, OP, IANY), PINFO(IN, OP, IANY))
	OPINFO3(SUB,     "!sub",     4|8, false, NONE, SZVC, ALL,  PINFO(OUT, OP, IRM), PINFO(IN, OP, IANY), PINFO(IN, OP, IANY))
	OPINFO3(SUBB,    "!subb",    4|8, false, C,    SZVC, ALL,  PINFO(OUT, OP, IRM), PINFO(IN, OP, IANY), PINFO(IN, OP, IANY))
	OPINFO2(CMP,     "!cmp",     4|8, false, NONE, SZVC, ALL,  PINFO(IN, OP, IANY), PINFO(IN, OP, IANY))
	OPINFO4(MULU,    "!mulu",    4|8, false, NONE, SZV,  ALL,  PINFO(OUT, OP, IRM), PINFO(OUT, OP, IRM), PINFO(IN, OP, IANY), PINFO(IN, OP, IANY))
	OPINFO4(MULS,    "!muls",    4|8, false, NONE, SZV,  ALL,  PINFO(OUT, OP, IRM), PINFO(OUT, OP, IRM), PINFO(IN, OP, IANY), PINFO(IN, OP, IANY))
	OPINFO4(DIVU,    "!divu",    4|8, false, NONE, SZV,  ALL,  PINFO(OUT, OP, IRM), PINFO(OUT, OP, IRM), PINFO(IN, OP, IANY), PINFO(IN, OP, IANY))
	OPINFO4(DIVS,    "!divs",    4|8, false, NONE, SZV,  ALL,  PINFO(OUT, OP, IRM), PINFO(OUT, OP, IRM), PINFO(IN, OP, IANY), PINFO(IN, OP, IANY))
	OPINFO3(AND,     "!and",     4|8, false, NONE, SZ,   ALL,  PINFO(OUT, OP, IRM), PINFO(IN, OP, IANY), PINFO(IN, OP, IANY))
	OPINFO2(TEST,    "!test",    4|8, false, NONE, SZ,   ALL,  PINFO(IN, OP, IANY), PINFO(IN, OP, IANY))
	OPINFO3(OR,      "!or",      4|8, false, NONE, SZ,   ALL,  PINFO(OUT, OP, IRM), PINFO(IN, OP, IANY), PINFO(IN, OP, IANY))
	OPINFO3(XOR,     "!xor",     4|8, false, NONE, SZ,   ALL,  PINFO(OUT, OP, IRM), PINFO(IN, OP, IANY), PINFO(IN, OP, IANY))
	OPINFO2(LZCNT,   "!lzcnt",   4|8, false, NONE, SZ,   ALL,  PINFO(OUT, OP, IRM), PINFO(IN, OP, IANY))
<<<<<<< HEAD
=======
	OPINFO2(TZCNT,   "!tzcnt",   4|8, false, NONE, SZ,   ALL,  PINFO(OUT, OP, IRM), PINFO(IN, OP, IANY))
>>>>>>> upstream/master
	OPINFO2(BSWAP,   "!bswap",   4|8, false, NONE, SZ,   ALL,  PINFO(OUT, OP, IRM), PINFO(IN, OP, IANY))
	OPINFO3(SHL,     "!shl",     4|8, false, NONE, SZC,  ALL,  PINFO(OUT, OP, IRM), PINFO(IN, OP, IANY), PINFO(IN, OP, IANY))
	OPINFO3(SHR,     "!shr",     4|8, false, NONE, SZC,  ALL,  PINFO(OUT, OP, IRM), PINFO(IN, OP, IANY), PINFO(IN, OP, IANY))
	OPINFO3(SAR,     "!sar",     4|8, false, NONE, SZC,  ALL,  PINFO(OUT, OP, IRM), PINFO(IN, OP, IANY), PINFO(IN, OP, IANY))
	OPINFO3(ROL,     "!rol",     4|8, false, NONE, SZC,  ALL,  PINFO(OUT, OP, IRM), PINFO(IN, OP, IANY), PINFO(IN, OP, IANY))
	OPINFO3(ROLC,    "!rolc",    4|8, false, C,    SZC,  ALL,  PINFO(OUT, OP, IRM), PINFO(IN, OP, IANY), PINFO(IN, OP, IANY))
	OPINFO3(ROR,     "!ror",     4|8, false, NONE, SZC,  ALL,  PINFO(OUT, OP, IRM), PINFO(IN, OP, IANY), PINFO(IN, OP, IANY))
	OPINFO3(RORC,    "!rorc",    4|8, false, C,    SZC,  ALL,  PINFO(OUT, OP, IRM), PINFO(IN, OP, IANY), PINFO(IN, OP, IANY))

	// Floating Point Operations
	OPINFO3(FLOAD,   "f#load",   4|8, false, NONE, NONE, ALL,  PINFO(OUT, OP, FRM), PINFO(IN, OP, PTR), PINFO(IN, 4, IANY))
	OPINFO3(FSTORE,  "f#store",  4|8, false, NONE, NONE, ALL,  PINFO(IN, OP, PTR), PINFO(IN, 4, IANY), PINFO(IN, OP, FRM))
	OPINFO3(FREAD,   "f#read",   4|8, false, NONE, NONE, ALL,  PINFO(OUT, OP, FRM), PINFO(IN, 4, IANY), PINFO(IN, OP, SPSIZE))
	OPINFO3(FWRITE,  "f#write",  4|8, false, NONE, NONE, ALL,  PINFO(IN, 4, IANY), PINFO(IN, OP, FANY), PINFO(IN, OP, SPSIZE))
	OPINFO2(FMOV,    "f#mov",    4|8, true,  NONE, NONE, NONE, PINFO(OUT, OP, FRM), PINFO(IN, OP, FANY))
	OPINFO4(FTOINT,  "f#toint",  4|8, false, NONE, NONE, ALL,  PINFO(OUT, P3, IRM), PINFO(IN, OP, FANY), PINFO(IN, OP, SIZE), PINFO(IN, OP, ROUND))
	OPINFO3(FFRINT,  "f#frint",  4|8, false, NONE, NONE, ALL,  PINFO(OUT, OP, FRM), PINFO(IN, P3, IANY), PINFO(IN, OP, SIZE))
	OPINFO3(FFRFLT,  "f#frflt",  4|8, false, NONE, NONE, ALL,  PINFO(OUT, OP, FRM), PINFO(IN, P3, FANY), PINFO(IN, OP, SIZE))
	OPINFO2(FRNDS,   "f#rnds",     8, false, NONE, NONE, ALL,  PINFO(OUT, OP, FRM), PINFO(IN, P3, FANY))
	OPINFO3(FADD,    "f#add",    4|8, false, NONE, NONE, ALL,  PINFO(OUT, OP, FRM), PINFO(IN, OP, FANY), PINFO(IN, OP, FANY))
	OPINFO3(FSUB,    "f#sub",    4|8, false, NONE, NONE, ALL,  PINFO(OUT, OP, FRM), PINFO(IN, OP, FANY), PINFO(IN, OP, FANY))
	OPINFO2(FCMP,    "f#cmp",    4|8, false, NONE, UZC,  ALL,  PINFO(IN, OP, FANY), PINFO(IN, OP, FANY))
	OPINFO3(FMUL,    "f#mul",    4|8, false, NONE, NONE, ALL,  PINFO(OUT, OP, FRM), PINFO(IN, OP, FANY), PINFO(IN, OP, FANY))
	OPINFO3(FDIV,    "f#div",    4|8, false, NONE, NONE, ALL,  PINFO(OUT, OP, FRM), PINFO(IN, OP, FANY), PINFO(IN, OP, FANY))
	OPINFO2(FNEG,    "f#neg",    4|8, false, NONE, NONE, ALL,  PINFO(OUT, OP, FRM), PINFO(IN, OP, FANY))
	OPINFO2(FABS,    "f#abs",    4|8, false, NONE, NONE, ALL,  PINFO(OUT, OP, FRM), PINFO(IN, OP, FANY))
	OPINFO2(FSQRT,   "f#sqrt",   4|8, false, NONE, NONE, ALL,  PINFO(OUT, OP, FRM), PINFO(IN, OP, FANY))
	OPINFO2(FRECIP,  "f#recip",  4|8, false, NONE, NONE, ALL,  PINFO(OUT, OP, FRM), PINFO(IN, OP, FANY))
	OPINFO2(FRSQRT,  "f#rsqrt",  4|8, false, NONE, NONE, ALL,  PINFO(OUT, OP, FRM), PINFO(IN, OP, FANY))
<<<<<<< HEAD
=======
	OPINFO2(FCOPYI,  "f#copyi",  4|8, false, NONE, NONE, NONE, PINFO(OUT, OP, FRM), PINFO(IN, OP, IRM))
	OPINFO2(ICOPYF,  "icopyf#",  4|8, false, NONE, NONE, NONE, PINFO(OUT, OP, IRM), PINFO(IN, OP, FRM))
>>>>>>> upstream/master
};



//**************************************************************************
//  INLINE FUNCTIONS
//**************************************************************************

//-------------------------------------------------
//  rol32 - perform a 32-bit left rotate
//-------------------------------------------------

<<<<<<< HEAD
inline UINT32 rol32(UINT32 source, UINT8 count)
=======
inline uint32_t rol32(uint32_t source, uint8_t count)
>>>>>>> upstream/master
{
	count &= 31;
	return (source << count) | (source >> (32 - count));
}


//-------------------------------------------------
//  rol64 - perform a 64-bit left rotate
//-------------------------------------------------

<<<<<<< HEAD
inline UINT64 rol64(UINT64 source, UINT8 count)
=======
inline uint64_t rol64(uint64_t source, uint8_t count)
>>>>>>> upstream/master
{
	count &= 63;
	return (source << count) | (source >> (64 - count));
}



//**************************************************************************
//  UML CODE HANDLE
//**************************************************************************

//-------------------------------------------------
//  code_handle - constructor
//-------------------------------------------------

uml::code_handle::code_handle(drcuml_state &drcuml, const char *name)
	: m_code(reinterpret_cast<drccodeptr *>(drcuml.cache().alloc_near(sizeof(drccodeptr)))),
		m_string(name),
<<<<<<< HEAD
		m_next(NULL),
		m_drcuml(drcuml)
{
	if (m_code == NULL)
		throw std::bad_alloc();
	*m_code = NULL;
=======
		m_next(nullptr),
		m_drcuml(drcuml)
{
	if (m_code == nullptr)
		throw std::bad_alloc();
	*m_code = nullptr;
>>>>>>> upstream/master
}


//-------------------------------------------------
//  set_codeptr - set a new code pointer
//-------------------------------------------------

void uml::code_handle::set_codeptr(drccodeptr code)
{
<<<<<<< HEAD
	assert(*m_code == NULL);
=======
	assert(*m_code == nullptr);
>>>>>>> upstream/master
	assert_in_cache(m_drcuml.cache(), code);
	*m_code = code;
}



//**************************************************************************
//  UML INSTRUCTION
//**************************************************************************

//-------------------------------------------------
//  instruction - constructor
//-------------------------------------------------

uml::instruction::instruction()
	: m_opcode(OP_INVALID),
		m_condition(COND_ALWAYS),
		m_flags(0),
		m_size(4),
		m_numparams(0)
{
}


//-------------------------------------------------
//  configure - configure an opcode with no
//  parameters
//-------------------------------------------------

<<<<<<< HEAD
void uml::instruction::configure(opcode_t op, UINT8 size, condition_t condition)
{
	// fill in the instruction
	m_opcode = (opcode_t)(UINT8)op;
=======
void uml::instruction::configure(opcode_t op, uint8_t size, condition_t condition)
{
	// fill in the instruction
	m_opcode = (opcode_t)(uint8_t)op;
>>>>>>> upstream/master
	m_size = size;
	m_condition = condition;
	m_flags = 0;
	m_numparams = 0;

	// validate
	validate();
}


//-------------------------------------------------
//  configure - configure an opcode with 1
//  parameter
//-------------------------------------------------

<<<<<<< HEAD
void uml::instruction::configure(opcode_t op, UINT8 size, parameter p0, condition_t condition)
{
	// fill in the instruction
	m_opcode = (opcode_t)(UINT8)op;
=======
void uml::instruction::configure(opcode_t op, uint8_t size, parameter p0, condition_t condition)
{
	// fill in the instruction
	m_opcode = (opcode_t)(uint8_t)op;
>>>>>>> upstream/master
	m_size = size;
	m_condition = condition;
	m_flags = 0;
	m_numparams = 1;
	m_param[0] = p0;

	// validate
	validate();
}


//-------------------------------------------------
//  configure - configure an opcode with 2
//  parameters
//-------------------------------------------------

<<<<<<< HEAD
void uml::instruction::configure(opcode_t op, UINT8 size, parameter p0, parameter p1, condition_t condition)
{
	// fill in the instruction
	m_opcode = (opcode_t)(UINT8)op;
=======
void uml::instruction::configure(opcode_t op, uint8_t size, parameter p0, parameter p1, condition_t condition)
{
	// fill in the instruction
	m_opcode = (opcode_t)(uint8_t)op;
>>>>>>> upstream/master
	m_size = size;
	m_condition = condition;
	m_flags = 0;
	m_numparams = 2;
	m_param[0] = p0;
	m_param[1] = p1;

	// validate
	validate();
}


//-------------------------------------------------
//  configure - configure an opcode with 3
//  parameters
//-------------------------------------------------

<<<<<<< HEAD
void uml::instruction::configure(opcode_t op, UINT8 size, parameter p0, parameter p1, parameter p2, condition_t condition)
{
	// fill in the instruction
	m_opcode = (opcode_t)(UINT8)op;
=======
void uml::instruction::configure(opcode_t op, uint8_t size, parameter p0, parameter p1, parameter p2, condition_t condition)
{
	// fill in the instruction
	m_opcode = (opcode_t)(uint8_t)op;
>>>>>>> upstream/master
	m_size = size;
	m_condition = condition;
	m_flags = 0;
	m_numparams = 3;
	m_param[0] = p0;
	m_param[1] = p1;
	m_param[2] = p2;

	// validate
	validate();
}


//-------------------------------------------------
//  configure - configure an opcode with 4
//  parameters
//-------------------------------------------------

<<<<<<< HEAD
void uml::instruction::configure(opcode_t op, UINT8 size, parameter p0, parameter p1, parameter p2, parameter p3, condition_t condition)
{
	// fill in the instruction
	m_opcode = (opcode_t)(UINT8)op;
=======
void uml::instruction::configure(opcode_t op, uint8_t size, parameter p0, parameter p1, parameter p2, parameter p3, condition_t condition)
{
	// fill in the instruction
	m_opcode = (opcode_t)(uint8_t)op;
>>>>>>> upstream/master
	m_size = size;
	m_condition = condition;
	m_flags = 0;
	m_numparams = 4;
	m_param[0] = p0;
	m_param[1] = p1;
	m_param[2] = p2;
	m_param[3] = p3;

	// validate
	validate();
}


//-------------------------------------------------
//  simplify - simplify instructions that have
//  immediate values we can evaluate at compile
//  time
//-------------------------------------------------

void uml::instruction::simplify()
{
	// can't simplify if flags are in play
	if (m_flags != 0)
		return;

<<<<<<< HEAD
	static const UINT64 instsizemask[] = { 0, 0, 0, 0, 0xffffffff, 0, 0, 0, U64(0xffffffffffffffff) };
	static const UINT64 paramsizemask[] = { 0xff, 0xffff, 0xffffffff, U64(0xffffffffffffffff) };
=======
	static const uint64_t instsizemask[] = { 0, 0, 0, 0, 0xffffffff, 0, 0, 0, 0xffffffffffffffffU };
	static const uint64_t paramsizemask[] = { 0xff, 0xffff, 0xffffffff, 0xffffffffffffffffU };
>>>>>>> upstream/master

	// loop until we've simplified all we can
	opcode_t origop;
	do
	{
		// switch off the opcode
		origop = m_opcode;
		switch (m_opcode)
		{
			// READM: convert to READ if the mask is wide open
			case OP_READM:
				if (m_param[2].is_immediate_value(paramsizemask[m_param[3].size()]))
				{
					m_opcode = OP_READ;
					m_numparams = 2;
					m_param[2] = m_param[3];
				}
				break;

			// WRITEM: convert to WRITE if the mask is wide open
			case OP_WRITEM:
				if (m_param[2].is_immediate_value(paramsizemask[m_param[3].size()]))
				{
					m_opcode = OP_WRITE;
					m_numparams = 2;
					m_param[2] = m_param[3];
				}
				break;

			// SET: convert to MOV if constant condition
			case OP_SET:
				if (m_condition == COND_ALWAYS)
					convert_to_mov_immediate(1);
				break;

			// MOV: convert to NOP if move-to-self
			case OP_MOV:
				if (m_param[0] == m_param[1])
					nop();
				break;

			// SEXT: convert immediates to MOV
			case OP_SEXT:
				if (m_param[1].is_immediate())
					switch (m_param[2].size())
					{
<<<<<<< HEAD
						case SIZE_BYTE:     convert_to_mov_immediate((INT8)m_param[1].immediate());     break;
						case SIZE_WORD:     convert_to_mov_immediate((INT16)m_param[1].immediate());    break;
						case SIZE_DWORD:    convert_to_mov_immediate((INT32)m_param[1].immediate());    break;
						case SIZE_QWORD:    convert_to_mov_immediate((INT64)m_param[1].immediate());    break;
=======
						case SIZE_BYTE:     convert_to_mov_immediate((int8_t)m_param[1].immediate());     break;
						case SIZE_WORD:     convert_to_mov_immediate((int16_t)m_param[1].immediate());    break;
						case SIZE_DWORD:    convert_to_mov_immediate((int32_t)m_param[1].immediate());    break;
						case SIZE_QWORD:    convert_to_mov_immediate((int64_t)m_param[1].immediate());    break;
>>>>>>> upstream/master
						case SIZE_DQWORD:   fatalerror("Invalid SEXT target size\n");
					}
				break;

			// ROLAND: convert to MOV if all immediate, or to ROL or AND if one is not needed, or to SHL/SHR if the mask is right
			case OP_ROLAND:
				if (m_param[1].is_immediate() && m_param[2].is_immediate() && m_param[3].is_immediate())
				{
					assert(m_size == 4 || m_size == 8);
					if (m_size == 4)
						convert_to_mov_immediate(rol32(m_param[1].immediate(), m_param[2].immediate()) & m_param[3].immediate());
					else
						convert_to_mov_immediate(rol64(m_param[1].immediate(), m_param[2].immediate()) & m_param[3].immediate());
				}
				else if (m_param[2].is_immediate_value(0))
				{
					m_opcode = OP_AND;
					m_numparams = 3;
					m_param[2] = m_param[3];
				}
				else if (m_param[3].is_immediate_value(instsizemask[m_size]))
				{
					m_opcode = OP_ROL;
					m_numparams = 3;
				}
<<<<<<< HEAD
				else if (m_param[2].is_immediate() && m_param[3].is_immediate_value((U64(0xffffffffffffffff) << m_param[2].immediate()) & instsizemask[m_size]))
=======
				else if (m_param[2].is_immediate() && m_param[3].is_immediate_value((0xffffffffffffffffU << m_param[2].immediate()) & instsizemask[m_size]))
>>>>>>> upstream/master
				{
					m_opcode = OP_SHL;
					m_numparams = 3;
				}
				else if (m_param[2].is_immediate() && m_param[3].is_immediate_value(instsizemask[m_size] >> (8 * m_size - m_param[2].immediate())))
				{
					m_opcode = OP_SHR;
					m_numparams = 3;
					m_param[2] = 8 * m_size - m_param[2].immediate();
				}
				break;

			// ROLINS: convert to ROLAND if the mask is full
			case OP_ROLINS:
				if (m_param[3].is_immediate_value(instsizemask[m_size]))
					m_opcode = OP_ROLAND;
				break;

			// ADD: convert to MOV if immediate, or if adding 0
			case OP_ADD:
				if (m_param[1].is_immediate() && m_param[2].is_immediate())
					convert_to_mov_immediate(m_param[1].immediate() + m_param[2].immediate());
				else if (m_param[1].is_immediate_value(0))
					convert_to_mov_param(2);
				else if (m_param[2].is_immediate_value(0))
					convert_to_mov_param(1);
				break;

			// SUB: convert to MOV if immediate, or if subtracting 0
			case OP_SUB:
				if (m_param[1].is_immediate() && m_param[2].is_immediate())
					convert_to_mov_immediate(m_param[1].immediate() - m_param[2].immediate());
				else if (m_param[2].is_immediate_value(0))
					convert_to_mov_param(1);
				break;

			// CMP: no-op if no flags needed, compare i0 to i0 if the parameters are equal
			case OP_CMP:
				if (m_flags == 0)
					nop();
				else if (m_param[0] == m_param[1])
					cmp(I0, I0);
				break;

			// MULU: convert simple form to MOV if immediate, or if multiplying by 0
			case OP_MULU:
				if (m_param[0] == m_param[1])
				{
					if (m_param[2].is_immediate_value(0) || m_param[3].is_immediate_value(0))
						convert_to_mov_immediate(0);
					else if (m_param[2].is_immediate() && m_param[3].is_immediate())
					{
						if (m_size == 4)
<<<<<<< HEAD
							convert_to_mov_immediate((UINT32)((UINT32)m_param[1].immediate() * (UINT32)m_param[2].immediate()));
						else if (m_size == 8)
							convert_to_mov_immediate((UINT64)((UINT64)m_param[1].immediate() * (UINT64)m_param[2].immediate()));
=======
							convert_to_mov_immediate((uint32_t)((uint32_t)m_param[1].immediate() * (uint32_t)m_param[2].immediate()));
						else if (m_size == 8)
							convert_to_mov_immediate((uint64_t)((uint64_t)m_param[1].immediate() * (uint64_t)m_param[2].immediate()));
>>>>>>> upstream/master
					}
				}
				break;

			// MULS: convert simple form to MOV if immediate, or if multiplying by 0
			case OP_MULS:
				if (m_param[0] == m_param[1])
				{
					if (m_param[2].is_immediate_value(0) || m_param[3].is_immediate_value(0))
						convert_to_mov_immediate(0);
					else if (m_param[2].is_immediate() && m_param[3].is_immediate())
					{
						if (m_size == 4)
<<<<<<< HEAD
							convert_to_mov_immediate((INT32)((INT32)m_param[1].immediate() * (INT32)m_param[2].immediate()));
						else if (m_size == 8)
							convert_to_mov_immediate((INT64)((INT64)m_param[1].immediate() * (INT64)m_param[2].immediate()));
=======
							convert_to_mov_immediate((int32_t)((int32_t)m_param[1].immediate() * (int32_t)m_param[2].immediate()));
						else if (m_size == 8)
							convert_to_mov_immediate((int64_t)((int64_t)m_param[1].immediate() * (int64_t)m_param[2].immediate()));
>>>>>>> upstream/master
					}
				}
				break;

			// DIVU: convert simple form to MOV if immediate, or if dividing with 0
			case OP_DIVU:
				if (m_param[0] == m_param[1] && !m_param[3].is_immediate_value(0))
				{
					if (m_param[2].is_immediate_value(0))
						convert_to_mov_immediate(0);
					else if (m_param[2].is_immediate() && m_param[3].is_immediate())
					{
						if (m_size == 4)
<<<<<<< HEAD
							convert_to_mov_immediate((UINT32)((UINT32)m_param[1].immediate() / (UINT32)m_param[2].immediate()));
						else if (m_size == 8)
							convert_to_mov_immediate((UINT64)((UINT64)m_param[1].immediate() / (UINT64)m_param[2].immediate()));
=======
							convert_to_mov_immediate((uint32_t)((uint32_t)m_param[1].immediate() / (uint32_t)m_param[2].immediate()));
						else if (m_size == 8)
							convert_to_mov_immediate((uint64_t)((uint64_t)m_param[1].immediate() / (uint64_t)m_param[2].immediate()));
>>>>>>> upstream/master
					}
				}
				break;

			// DIVS: convert simple form to MOV if immediate, or if dividing with 0
			case OP_DIVS:
				if (m_param[0] == m_param[1] && !m_param[3].is_immediate_value(0))
				{
					if (m_param[2].is_immediate_value(0))
						convert_to_mov_immediate(0);
					else if (m_param[2].is_immediate() && m_param[3].is_immediate())
					{
						if (m_size == 4)
<<<<<<< HEAD
							convert_to_mov_immediate((INT32)((INT32)m_param[1].immediate() / (INT32)m_param[2].immediate()));
						else if (m_size == 8)
							convert_to_mov_immediate((INT64)((INT64)m_param[1].immediate() / (INT64)m_param[2].immediate()));
=======
							convert_to_mov_immediate((int32_t)((int32_t)m_param[1].immediate() / (int32_t)m_param[2].immediate()));
						else if (m_size == 8)
							convert_to_mov_immediate((int64_t)((int64_t)m_param[1].immediate() / (int64_t)m_param[2].immediate()));
>>>>>>> upstream/master
					}
				}
				break;

			// AND: convert to MOV if immediate, or if anding against 0 or 0xffffffff
			case OP_AND:
				if (m_param[1].is_immediate_value(0) || m_param[2].is_immediate_value(0))
					convert_to_mov_immediate(0);
				else if (m_param[1].is_immediate() && m_param[2].is_immediate())
					convert_to_mov_immediate(m_param[1].immediate() & m_param[2].immediate());
				else if (m_param[1].is_immediate_value(instsizemask[m_size]))
					convert_to_mov_param(2);
				else if (m_param[2].is_immediate_value(instsizemask[m_size]))
					convert_to_mov_param(1);
				break;

			// TEST: no-op if no flags needed
			case OP_TEST:
				if (m_flags == 0)
					nop();
				break;

			// OR: convert to MOV if immediate, or if oring against 0 or 0xffffffff
			case OP_OR:
				if (m_param[1].is_immediate_value(instsizemask[m_size]) || m_param[2].is_immediate_value(instsizemask[m_size]))
					convert_to_mov_immediate(instsizemask[m_size]);
				else if (m_param[1].is_immediate() && m_param[2].is_immediate())
					convert_to_mov_immediate(m_param[1].immediate() | m_param[2].immediate());
				else if (m_param[1].is_immediate_value(0))
					convert_to_mov_param(2);
				else if (m_param[2].is_immediate_value(0))
					convert_to_mov_param(1);
				break;

			// XOR: convert to MOV if immediate, or if xoring against 0
			case OP_XOR:
				if (m_param[1].is_immediate() && m_param[2].is_immediate())
					convert_to_mov_immediate(m_param[1].immediate() ^ m_param[2].immediate());
				else if (m_param[1].is_immediate_value(0))
					convert_to_mov_param(2);
				else if (m_param[2].is_immediate_value(0))
					convert_to_mov_param(1);
				break;

			// LZCNT: convert to MOV if immediate
			case OP_LZCNT:
				if (m_param[1].is_immediate())
				{
					if (m_size == 4)
						convert_to_mov_immediate(count_leading_zeros(m_param[1].immediate()));
					else if (m_size == 8)
					{
						if ((m_param[1].immediate() >> 32) == 0)
							convert_to_mov_immediate(32 + count_leading_zeros(m_param[1].immediate()));
						else
							convert_to_mov_immediate(count_leading_zeros(m_param[1].immediate() >> 32));
					}
				}
				break;

			// BSWAP: convert to MOV if immediate
			case OP_BSWAP:
				if (m_param[1].is_immediate())
				{
					if (m_size == 4)
<<<<<<< HEAD
						convert_to_mov_immediate(FLIPENDIAN_INT32(m_param[1].immediate()));
					else if (m_size == 8)
						convert_to_mov_immediate(FLIPENDIAN_INT64(m_param[1].immediate()));
=======
						convert_to_mov_immediate(flipendian_int32(m_param[1].immediate()));
					else if (m_size == 8)
						convert_to_mov_immediate(flipendian_int64(m_param[1].immediate()));
>>>>>>> upstream/master
				}
				break;

			// SHL: convert to MOV if immediate or shifting by 0
			case OP_SHL:
				if (m_param[1].is_immediate() && m_param[2].is_immediate())
					convert_to_mov_immediate(m_param[1].immediate() << m_param[2].immediate());
				else if (m_param[2].is_immediate_value(0))
					convert_to_mov_param(1);
				break;

			// SHR: convert to MOV if immediate or shifting by 0
			case OP_SHR:
				if (m_param[1].is_immediate() && m_param[2].is_immediate())
				{
					if (m_size == 4)
<<<<<<< HEAD
						convert_to_mov_immediate((UINT32)m_param[1].immediate() >> m_param[2].immediate());
					else if (m_size == 8)
						convert_to_mov_immediate((UINT64)m_param[1].immediate() >> m_param[2].immediate());
=======
						convert_to_mov_immediate((uint32_t)m_param[1].immediate() >> m_param[2].immediate());
					else if (m_size == 8)
						convert_to_mov_immediate((uint64_t)m_param[1].immediate() >> m_param[2].immediate());
>>>>>>> upstream/master
				}
				else if (m_param[2].is_immediate_value(0))
					convert_to_mov_param(1);
				break;

			// SAR: convert to MOV if immediate or shifting by 0
			case OP_SAR:
				if (m_param[1].is_immediate() && m_param[2].is_immediate())
				{
					if (m_size == 4)
<<<<<<< HEAD
						convert_to_mov_immediate((INT32)m_param[1].immediate() >> m_param[2].immediate());
					else if (m_size == 8)
						convert_to_mov_immediate((INT64)m_param[1].immediate() >> m_param[2].immediate());
=======
						convert_to_mov_immediate((int32_t)m_param[1].immediate() >> m_param[2].immediate());
					else if (m_size == 8)
						convert_to_mov_immediate((int64_t)m_param[1].immediate() >> m_param[2].immediate());
>>>>>>> upstream/master
				}
				else if (m_param[2].is_immediate_value(0))
					convert_to_mov_param(1);
				break;

			// ROL: convert to NOP if immediate or rotating by 0
			case OP_ROL:
				if (m_param[1].is_immediate() && m_param[2].is_immediate())
				{
					if (m_size == 4)
						convert_to_mov_immediate(rol32(m_param[1].immediate(), m_param[2].immediate()));
					else if (m_size == 8)
						convert_to_mov_immediate(rol64(m_param[1].immediate(), m_param[2].immediate()));
				}
				else if (m_param[2].is_immediate_value(0))
					convert_to_mov_param(1);
				break;

			// ROR: convert to NOP if immediate or rotating by 0
			case OP_ROR:
				if (m_param[1].is_immediate() && m_param[2].is_immediate())
				{
					if (m_size == 4)
						convert_to_mov_immediate(rol32(m_param[1].immediate(), 32 - m_param[2].immediate()));
					else if (m_size == 8)
						convert_to_mov_immediate(rol64(m_param[1].immediate(), 64 - m_param[2].immediate()));
				}
				else if (m_param[2].is_immediate_value(0))
					convert_to_mov_param(1);
				break;

			// FMOV: convert to NOP if move-to-self
			case OP_FMOV:
				if (m_param[0] == m_param[1])
					nop();
				break;

			default:
				break;
		}

	/*
	    if (LOG_SIMPLIFICATIONS && memcmp(&orig, inst, sizeof(orig)) != 0)
	    {
<<<<<<< HEAD
	        std::string disasm1, disasm2;
	        orig.disasm(disasm1, block->drcuml);
	        inst->disasm(disasm2, block->drcuml);
=======
	        std::string disasm1 = orig.disasm(block->drcuml);
	        std::string disasm2 = inst->disasm(block->drcuml);
>>>>>>> upstream/master
	        osd_printf_debug("Simplified: %-50.50s -> %s\n", disasm1.c_str(), disasm2.c_str());
	    }
	*/

		// loop until we stop changing opcodes
	} while (m_opcode != origop);
}


//-------------------------------------------------
//  validate - verify that the instruction created
//  meets all requirements
//-------------------------------------------------

void uml::instruction::validate()
{
#ifdef MAME_DEBUG
	const opcode_info &opinfo = s_opcode_info_table[m_opcode];
	assert(opinfo.opcode == m_opcode);

	// validate raw information
	assert(m_opcode != OP_INVALID && m_opcode < OP_MAX);
	assert(m_size == 1 || m_size == 2 || m_size == 4 || m_size == 8);

	// validate against opcode limits
	assert((opinfo.sizes & m_size) != 0);
	assert(m_condition == COND_ALWAYS || opinfo.condition);

	// validate each parameter
	for (int pnum = 0; pnum < m_numparams; pnum++)
	{
		// ensure the type is valid
		const parameter &param = m_param[pnum];
		assert((opinfo.param[pnum].typemask >> param.type()) & 1);
	}

	// make sure we aren't missing any parameters
	if (m_numparams < ARRAY_LENGTH(opinfo.param))
		assert(opinfo.param[m_numparams].typemask == 0);
#endif
}


//-------------------------------------------------
//  input_flags - return the effective input flags
//  based on any conditions encoded in an
//  instruction
//-------------------------------------------------

<<<<<<< HEAD
UINT8 uml::instruction::input_flags() const
{
	static const UINT8 flags_for_condition[] =
=======
uint8_t uml::instruction::input_flags() const
{
	static const uint8_t flags_for_condition[] =
>>>>>>> upstream/master
	{
		FLAG_Z,                     // COND_Z
		FLAG_Z,                     // COND_NZ
		FLAG_S,                     // COND_S
		FLAG_S,                     // COND_NS
		FLAG_C,                     // COND_C
		FLAG_C,                     // COND_NC
		FLAG_V,                     // COND_V
		FLAG_V,                     // COND_NV
		FLAG_U,                     // COND_U
		FLAG_U,                     // COND_NU
		FLAG_C | FLAG_Z,            // COND_A
		FLAG_C | FLAG_Z,            // COND_BE
		FLAG_S | FLAG_V | FLAG_Z,   // COND_G
		FLAG_S | FLAG_V | FLAG_Z,   // COND_LE
		FLAG_S | FLAG_V,            // COND_L
		FLAG_S | FLAG_V             // COND_GE
	};

<<<<<<< HEAD
	UINT8 flags = s_opcode_info_table[m_opcode].inflags;
=======
	uint8_t flags = s_opcode_info_table[m_opcode].inflags;
>>>>>>> upstream/master
	if (flags & 0x80)
		flags = m_param[flags - OPFLAGS_P1].immediate() & OPFLAGS_ALL;
	if (m_condition != COND_ALWAYS)
		flags |= flags_for_condition[m_condition & 0x0f];
	return flags;
}


//-------------------------------------------------
//  output_flags - return the effective output
//  flags based on any conditions encoded in an
//  instruction
//-------------------------------------------------

<<<<<<< HEAD
UINT8 uml::instruction::output_flags() const
{
	UINT8 flags = s_opcode_info_table[m_opcode].outflags;
=======
uint8_t uml::instruction::output_flags() const
{
	uint8_t flags = s_opcode_info_table[m_opcode].outflags;
>>>>>>> upstream/master
	if (flags & 0x80)
		flags = m_param[flags - OPFLAGS_P1].immediate() & OPFLAGS_ALL;
	return flags;
}


//-------------------------------------------------
//  modified_flags - return the effective output
//  flags based on any conditions encoded in an
//  instruction
//-------------------------------------------------

<<<<<<< HEAD
UINT8 uml::instruction::modified_flags() const
=======
uint8_t uml::instruction::modified_flags() const
>>>>>>> upstream/master
{
	return s_opcode_info_table[m_opcode].modflags;
}


//-------------------------------------------------
//  disasm - disassemble an instruction to the
//  given buffer
//-------------------------------------------------

<<<<<<< HEAD
const char *uml::instruction::disasm(std::string &buffer, drcuml_state *drcuml) const
=======
std::string uml::instruction::disasm(drcuml_state *drcuml) const
>>>>>>> upstream/master
{
	static const char *const conditions[] = { "z", "nz", "s", "ns", "c", "nc", "v", "nv", "u", "nu", "a", "be", "g", "le", "l", "ge" };
	static const char *const pound_size[] = { "?", "?", "?", "?", "s", "?", "?", "?", "d" };
	static const char *const bang_size[] = { "?", "b", "h", "?", "", "?", "?", "?", "d" };
	static const char *const fmods[] = { "trunc", "round", "ceil", "floor", "default" };
	static const char *const spaces[] = { "program", "data", "io", "3", "4", "5", "6", "7" };
	static const char *const sizes[] = { "byte", "word", "dword", "qword" };

	const opcode_info &opinfo = s_opcode_info_table[m_opcode];

	assert(m_opcode != OP_INVALID && m_opcode < OP_MAX);

	// start with the raw mnemonic and substitute sizes
<<<<<<< HEAD
	buffer.clear();
	for (const char *opsrc = opinfo.mnemonic; *opsrc != 0; opsrc++)
		if (*opsrc == '!')
			strcatprintf(buffer, "%s", bang_size[m_size]);
		else if (*opsrc == '#')
			strcatprintf(buffer, "%s", pound_size[m_size]);
		else
			buffer.push_back(*opsrc);

	// pad to 8 spaces
	int pad = 8 - buffer.length();
	for (int ch = 0; ch < pad; ch++)
		buffer.push_back(' ');
=======
	std::ostringstream buffer;
	for (const char *opsrc = opinfo.mnemonic; *opsrc != 0; opsrc++)
		if (*opsrc == '!')
			util::stream_format(buffer, "%s", bang_size[m_size]);
		else if (*opsrc == '#')
			util::stream_format(buffer, "%s", pound_size[m_size]);
		else
			util::stream_format(buffer, "%c", *opsrc);

	// pad to 8 spaces
	int pad = 8 - buffer.tellp();
	while (pad > 0)
	{
		buffer.put(' ');
		pad--;
	}
>>>>>>> upstream/master

	// iterate through parameters
	for (int pnum = 0; pnum < m_numparams; pnum++)
	{
		const parameter &param = m_param[pnum];

		// start with a comma for all except the first parameter
		if (pnum != 0)
<<<<<<< HEAD
			buffer.push_back(',');
=======
			buffer.put(',');
>>>>>>> upstream/master

		// ouput based on type
		switch (param.type())
		{
			// immediates have several special cases
			case parameter::PTYPE_IMMEDIATE:
				{
					// determine the size of the immediate
					int size;
					switch (opinfo.param[pnum].size)
					{
						case PSIZE_4:   size = 4; break;
						case PSIZE_8:   size = 8; break;
						case PSIZE_P1:  size = 1 << m_param[0].size(); break;
						case PSIZE_P2:  size = 1 << m_param[1].size(); break;
						case PSIZE_P3:  size = 1 << m_param[2].size(); break;
						case PSIZE_P4:  size = 1 << m_param[3].size(); break;
						default:
						case PSIZE_OP:  size = m_size; break;
					}

					// truncate to size
<<<<<<< HEAD
					UINT64 value = param.immediate();
					if (size == 1) value = (UINT8)value;
					if (size == 2) value = (UINT16)value;
					if (size == 4) value = (UINT32)value;
					if ((UINT32)value == value)
						strcatprintf(buffer, "$%X", (UINT32)value);
					else
						strcatprintf(buffer, "$%X%08X", (UINT32)(value >> 32), (UINT32)value);
=======
					uint64_t value = param.immediate();
					if (size == 1) value = (uint8_t)value;
					if (size == 2) value = (uint16_t)value;
					if (size == 4) value = (uint32_t)value;
					if ((uint32_t)value == value)
						util::stream_format(buffer, "$%X", (uint32_t)value);
					else
						util::stream_format(buffer, "$%X%08X", (uint32_t)(value >> 32), (uint32_t)value);
>>>>>>> upstream/master
				}
				break;

			// immediates have several special cases
			case parameter::PTYPE_SIZE:
<<<<<<< HEAD
				strcatprintf(buffer, "%s", sizes[param.size()]);
=======
				util::stream_format(buffer, "%s", sizes[param.size()]);
>>>>>>> upstream/master
				break;

			// size + address space immediate
			case parameter::PTYPE_SIZE_SPACE:
<<<<<<< HEAD
				strcatprintf(buffer, "%s_%s", spaces[param.space()], sizes[param.size()]);
=======
				util::stream_format(buffer, "%s_%s", spaces[param.space()], sizes[param.size()]);
>>>>>>> upstream/master
				break;

			// size + scale immediate
			case parameter::PTYPE_SIZE_SCALE:
				{
					int scale = param.scale();
					int size  = param.size();
					if (scale == size)
<<<<<<< HEAD
						strcatprintf(buffer, "%s", sizes[size]);
					else
						strcatprintf(buffer, "%s_x%d", sizes[size], 1 << scale);
=======
						util::stream_format(buffer, "%s", sizes[size]);
					else
						util::stream_format(buffer, "%s_x%d", sizes[size], 1 << scale);
>>>>>>> upstream/master
				}
				break;

			// fmod immediate
			case parameter::PTYPE_ROUNDING:
<<<<<<< HEAD
				strcatprintf(buffer, "%s", fmods[param.rounding()]);
=======
				util::stream_format(buffer, "%s", fmods[param.rounding()]);
>>>>>>> upstream/master
				break;

			// integer registers
			case parameter::PTYPE_INT_REGISTER:
<<<<<<< HEAD
				strcatprintf(buffer, "i%d", param.ireg() - REG_I0);
=======
				util::stream_format(buffer, "i%d", param.ireg() - REG_I0);
>>>>>>> upstream/master
				break;

			// floating point registers
			case parameter::PTYPE_FLOAT_REGISTER:
<<<<<<< HEAD
				strcatprintf(buffer, "f%d", param.freg() - REG_F0);
=======
				util::stream_format(buffer, "f%d", param.freg() - REG_F0);
>>>>>>> upstream/master
				break;

			// map variables
			case parameter::PTYPE_MAPVAR:
<<<<<<< HEAD
				strcatprintf(buffer, "m%d", param.mapvar() - MAPVAR_M0);
=======
				util::stream_format(buffer, "m%d", param.mapvar() - MAPVAR_M0);
>>>>>>> upstream/master
				break;

			// memory
			case parameter::PTYPE_MEMORY:
			{
				const char *symbol;
<<<<<<< HEAD
				UINT32 symoffset;

				// symbol
				if (drcuml != NULL && (symbol = drcuml->symbol_find(param.memory(), &symoffset)) != NULL)
				{
					if (symoffset == 0)
						strcatprintf(buffer, "[%s]", symbol);
					else
						strcatprintf(buffer, "[%s+$%X]", symbol, symoffset);
				}

				// cache memory
				else if (drcuml != NULL && drcuml->cache().contains_pointer(param.memory()))
					strcatprintf(buffer, "[+$%X]", (UINT32)(FPTR)((drccodeptr)param.memory() - drcuml->cache().near()));

				// general memory
				else
					strcatprintf(buffer, "[[$%p]]", param.memory());
=======
				uint32_t symoffset;

				// symbol
				if (drcuml != nullptr && (symbol = drcuml->symbol_find(param.memory(), &symoffset)) != nullptr)
				{
					if (symoffset == 0)
						util::stream_format(buffer, "[%s]", symbol);
					else
						util::stream_format(buffer, "[%s+$%X]", symbol, symoffset);
				}

				// cache memory
				else if (drcuml != nullptr && drcuml->cache().contains_pointer(param.memory()))
					util::stream_format(buffer, "[+$%X]", (uint32_t)(uintptr_t)((drccodeptr)param.memory() - drcuml->cache().near()));

				// general memory
				else
					util::stream_format(buffer, "[[$%p]]", param.memory());
>>>>>>> upstream/master
				break;
			}

			// string pointer
			case parameter::PTYPE_STRING:
<<<<<<< HEAD
				strcatprintf(buffer, "%s", (const char *)(FPTR)param.string());
=======
				util::stream_format(buffer, "%s", (const char *)(uintptr_t)param.string());
>>>>>>> upstream/master
				break;

			// handle pointer
			case parameter::PTYPE_CODE_HANDLE:
<<<<<<< HEAD
				strcatprintf(buffer, "%s", param.handle().string());
				break;

			default:
				strcatprintf(buffer, "???");
=======
				util::stream_format(buffer, "%s", param.handle().string());
				break;

			// label
			case parameter::PTYPE_CODE_LABEL:
				util::stream_format(buffer, "$%8X", param.label().label());
				break;

			default:
				util::stream_format(buffer, "???");
>>>>>>> upstream/master
				break;
		}
	}

	// if there's a condition, append it
	if (m_condition != COND_ALWAYS)
<<<<<<< HEAD
		strcatprintf(buffer, ",%s", conditions[m_condition & 0x0f]);
=======
		util::stream_format(buffer, ",%s", conditions[m_condition & 0x0f]);
>>>>>>> upstream/master

	// if there are flags, append them
	if (m_flags != 0)
	{
<<<<<<< HEAD
		buffer.push_back(',');
		if (m_flags & FLAG_U)
			buffer.push_back('U');
		if (m_flags & FLAG_S)
			buffer.push_back('S');
		if (m_flags & FLAG_Z)
			buffer.push_back('Z');
		if (m_flags & FLAG_V)
			buffer.push_back('V');
		if (m_flags & FLAG_C)
			buffer.push_back('C');
	}
	return buffer.c_str();
=======
		buffer.put(',');
		if (m_flags & FLAG_U)
			buffer.put('U');
		if (m_flags & FLAG_S)
			buffer.put('S');
		if (m_flags & FLAG_Z)
			buffer.put('Z');
		if (m_flags & FLAG_V)
			buffer.put('V');
		if (m_flags & FLAG_C)
			buffer.put('C');
	}
	return buffer.str();
>>>>>>> upstream/master
}
