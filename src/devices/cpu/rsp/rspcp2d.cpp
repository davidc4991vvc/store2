// license:BSD-3-Clause
// copyright-holders:Ryan Holtz
/***************************************************************************

    rspcp2d.c

    Universal machine language-based Nintendo/SGI RSP COP2 emulator.
    Written by Ryan Holtz

***************************************************************************/

#include "emu.h"
<<<<<<< HEAD
#include "rsp.h"
#include "rspcp2.h"
#include "rspcp2d.h"
=======
#include "rspcp2d.h"

#include "rsp.h"
#include "rspcp2.h"

>>>>>>> upstream/master
#include "cpu/drcfe.h"
#include "cpu/drcuml.h"
#include "cpu/drcumlsh.h"

<<<<<<< HEAD
using namespace uml;

extern offs_t rsp_dasm_one(char *buffer, offs_t pc, UINT32 op);
=======
#include "rspdefs.h"


using namespace uml;
>>>>>>> upstream/master

/***************************************************************************
    Helpful Defines
***************************************************************************/

#define VDREG   ((op >> 6) & 0x1f)
#define VS1REG  ((op >> 11) & 0x1f)
#define VS2REG  ((op >> 16) & 0x1f)
#define EL      ((op >> 21) & 0xf)

#define RSVAL   (m_rsp.m_rsp_state->r[RSREG])
#define RTVAL   (m_rsp.m_rsp_state->r[RTREG])
#define RDVAL   (m_rsp.m_rsp_state->r[RDREG])

#define VREG_B(reg, offset)         m_v[(reg)].b[(offset)^1]
#define W_VREG_S(reg, offset)       m_v[(reg)].s[(offset)]
<<<<<<< HEAD
#define VREG_S(reg, offset)         (INT16)m_v[(reg)].s[(offset)]
=======
#define VREG_S(reg, offset)         (int16_t)m_v[(reg)].s[(offset)]
>>>>>>> upstream/master

#define VEC_EL_2(x,z)               (vector_elements_2[(x)][(z)])

#define ACCUM(x)        m_accum[x].q

#define CARRY       0
#define COMPARE     1
#define CLIP1       2
#define ZERO        3
#define CLIP2       4

static void cfunc_mfc2(void *param);
static void cfunc_cfc2(void *param);
static void cfunc_mtc2(void *param);
static void cfunc_ctc2(void *param);

<<<<<<< HEAD
#define ACCUM_H(x)           (UINT16)m_accum[x].w[3]
#define ACCUM_M(x)           (UINT16)m_accum[x].w[2]
#define ACCUM_L(x)           (UINT16)m_accum[x].w[1]
#define ACCUM_LL(x)          (UINT16)m_accum[x].w[0]
=======
#define ACCUM_H(x)           (uint16_t)m_accum[x].w[3]
#define ACCUM_M(x)           (uint16_t)m_accum[x].w[2]
#define ACCUM_L(x)           (uint16_t)m_accum[x].w[1]
#define ACCUM_LL(x)          (uint16_t)m_accum[x].w[0]
>>>>>>> upstream/master
#define ACCUM(x)             m_accum[x].q

#define SET_ACCUM_H(v, x)       m_accum[x].w[3] = v;
#define SET_ACCUM_M(v, x)       m_accum[x].w[2] = v;
#define SET_ACCUM_L(v, x)       m_accum[x].w[1] = v;
#define SET_ACCUM_LL(v, x)      m_accum[x].w[0] = v;
#define SET_ACCUM(v, x)         m_accum[x].q = v;

#define GET_VS1(out, i)         out = VREG_S(vs1reg, i)
#define GET_VS2(out, i)         out = VREG_S(vs2reg, VEC_EL_2(el, i))

#define CARRY_FLAG(x)          (m_vflag[CARRY][x & 7] != 0 ? 0xffff : 0)
#define COMPARE_FLAG(x)        (m_vflag[COMPARE][x & 7] != 0 ? 0xffff : 0)
#define CLIP1_FLAG(x)          (m_vflag[CLIP1][x & 7] != 0 ? 0xffff : 0)
#define ZERO_FLAG(x)           (m_vflag[ZERO][x & 7] != 0 ? 0xffff : 0)
#define CLIP2_FLAG(x)          (m_vflag[CLIP2][x & 7] != 0 ? 0xffff : 0)

#define CLEAR_CARRY_FLAGS()         { memset(m_vflag[CARRY], 0, 16); }
#define CLEAR_COMPARE_FLAGS()       { memset(m_vflag[COMPARE], 0, 16); }
#define CLEAR_CLIP1_FLAGS()         { memset(m_vflag[CLIP1], 0, 16); }
#define CLEAR_ZERO_FLAGS()          { memset(m_vflag[ZERO], 0, 16); }
#define CLEAR_CLIP2_FLAGS()         { memset(m_vflag[CLIP2], 0, 16); }

#define SET_CARRY_FLAG(x)           { m_vflag[CARRY][x & 7] = 0xffff; }
#define SET_COMPARE_FLAG(x)         { m_vflag[COMPARE][x & 7] = 0xffff; }
#define SET_CLIP1_FLAG(x)           { m_vflag[CLIP1][x & 7] = 0xffff; }
#define SET_ZERO_FLAG(x)            { m_vflag[ZERO][x & 7] = 0xffff; }
#define SET_CLIP2_FLAG(x)           { m_vflag[CLIP2][x & 7] = 0xffff; }

#define CLEAR_CARRY_FLAG(x)         { m_vflag[CARRY][x & 7] = 0; }
#define CLEAR_COMPARE_FLAG(x)       { m_vflag[COMPARE][x & 7] = 0; }
#define CLEAR_CLIP1_FLAG(x)         { m_vflag[CLIP1][x & 7] = 0; }
#define CLEAR_ZERO_FLAG(x)          { m_vflag[ZERO][x & 7] = 0; }
#define CLEAR_CLIP2_FLAG(x)         { m_vflag[CLIP2][x & 7] = 0; }

#define CACHE_VALUES() \
	const int op = m_rspcop2_state->op;    \
	const int vdreg = VDREG;    \
	const int vs1reg = VS1REG;  \
	const int vs2reg = VS2REG;  \
	const int el = EL;

#define WRITEBACK_RESULT() { \
		W_VREG_S(vdreg, 0) = m_vres[0];   \
		W_VREG_S(vdreg, 1) = m_vres[1];   \
		W_VREG_S(vdreg, 2) = m_vres[2];   \
		W_VREG_S(vdreg, 3) = m_vres[3];   \
		W_VREG_S(vdreg, 4) = m_vres[4];   \
		W_VREG_S(vdreg, 5) = m_vres[5];   \
		W_VREG_S(vdreg, 6) = m_vres[6];   \
		W_VREG_S(vdreg, 7) = m_vres[7];   \
}

static const int vector_elements_2[16][8] =
{
	{ 0, 1, 2, 3, 4, 5, 6, 7 },     // none
	{ 0, 1, 2, 3, 4, 5, 6, 7 },     // ???
	{ 0, 0, 2, 2, 4, 4, 6, 6 },     // 0q
	{ 1, 1, 3, 3, 5, 5, 7, 7 },     // 1q
	{ 0, 0, 0, 0, 4, 4, 4, 4 },     // 0h
	{ 1, 1, 1, 1, 5, 5, 5, 5 },     // 1h
	{ 2, 2, 2, 2, 6, 6, 6, 6 },     // 2h
	{ 3, 3, 3, 3, 7, 7, 7, 7 },     // 3h
	{ 0, 0, 0, 0, 0, 0, 0, 0 },     // 0
	{ 1, 1, 1, 1, 1, 1, 1, 1 },     // 1
	{ 2, 2, 2, 2, 2, 2, 2, 2 },     // 2
	{ 3, 3, 3, 3, 3, 3, 3, 3 },     // 3
	{ 4, 4, 4, 4, 4, 4, 4, 4 },     // 4
	{ 5, 5, 5, 5, 5, 5, 5, 5 },     // 5
	{ 6, 6, 6, 6, 6, 6, 6, 6 },     // 6
	{ 7, 7, 7, 7, 7, 7, 7, 7 },     // 7
};

void rsp_cop2_drc::cfunc_unimplemented_opcode()
{
<<<<<<< HEAD
	const UINT32 ppc = m_rsp.m_ppc;
	if ((m_machine.debug_flags & DEBUG_FLAG_ENABLED) != 0)
	{
		char string[200];
		rsp_dasm_one(string, ppc, m_rspcop2_state->op);
		osd_printf_debug("%08X: %s\n", ppc, string);
=======
	const uint32_t ppc = m_rsp.m_ppc;
	if ((m_machine.debug_flags & DEBUG_FLAG_ENABLED) != 0)
	{
		std::ostringstream stream;
		rsp_dasm_one(stream, ppc, m_rspcop2_state->op);
		const std::string stream_string = stream.str();
		osd_printf_debug("%08X: %s\n", ppc, stream_string.c_str());
>>>>>>> upstream/master
	}
	fatalerror("RSP: unknown opcode %02X (%08X) at %08X\n", m_rspcop2_state->op >> 26, m_rspcop2_state->op, ppc);
}

static void unimplemented_opcode(void *param)
{
	((rsp_cop2 *)param)->cfunc_unimplemented_opcode();
}

<<<<<<< HEAD
void rsp_cop2_drc::state_string_export(const int index, std::string &str)
=======
void rsp_cop2_drc::state_string_export(const int index, std::string &str) const
>>>>>>> upstream/master
{
	switch (index)
	{
		case RSP_V0:
<<<<<<< HEAD
			strprintf(str, "%04X|%04X|%04X|%04X|%04X|%04X|%04X|%04X", (UINT16)VREG_S( 0, 0), (UINT16)VREG_S( 0, 1), (UINT16)VREG_S( 0, 2), (UINT16)VREG_S( 0, 3), (UINT16)VREG_S( 0, 4), (UINT16)VREG_S( 0, 5), (UINT16)VREG_S( 0, 6), (UINT16)VREG_S( 0, 7));
			break;
		case RSP_V1:
			strprintf(str, "%04X|%04X|%04X|%04X|%04X|%04X|%04X|%04X", (UINT16)VREG_S( 1, 0), (UINT16)VREG_S( 1, 1), (UINT16)VREG_S( 1, 2), (UINT16)VREG_S( 1, 3), (UINT16)VREG_S( 1, 4), (UINT16)VREG_S( 1, 5), (UINT16)VREG_S( 1, 6), (UINT16)VREG_S( 1, 7));
			break;
		case RSP_V2:
			strprintf(str, "%04X|%04X|%04X|%04X|%04X|%04X|%04X|%04X", (UINT16)VREG_S( 2, 0), (UINT16)VREG_S( 2, 1), (UINT16)VREG_S( 2, 2), (UINT16)VREG_S( 2, 3), (UINT16)VREG_S( 2, 4), (UINT16)VREG_S( 2, 5), (UINT16)VREG_S( 2, 6), (UINT16)VREG_S( 2, 7));
			break;
		case RSP_V3:
			strprintf(str, "%04X|%04X|%04X|%04X|%04X|%04X|%04X|%04X", (UINT16)VREG_S( 3, 0), (UINT16)VREG_S( 3, 1), (UINT16)VREG_S( 3, 2), (UINT16)VREG_S( 3, 3), (UINT16)VREG_S( 3, 4), (UINT16)VREG_S( 3, 5), (UINT16)VREG_S( 3, 6), (UINT16)VREG_S( 3, 7));
			break;
		case RSP_V4:
			strprintf(str, "%04X|%04X|%04X|%04X|%04X|%04X|%04X|%04X", (UINT16)VREG_S( 4, 0), (UINT16)VREG_S( 4, 1), (UINT16)VREG_S( 4, 2), (UINT16)VREG_S( 4, 3), (UINT16)VREG_S( 4, 4), (UINT16)VREG_S( 4, 5), (UINT16)VREG_S( 4, 6), (UINT16)VREG_S( 4, 7));
			break;
		case RSP_V5:
			strprintf(str, "%04X|%04X|%04X|%04X|%04X|%04X|%04X|%04X", (UINT16)VREG_S( 5, 0), (UINT16)VREG_S( 5, 1), (UINT16)VREG_S( 5, 2), (UINT16)VREG_S( 5, 3), (UINT16)VREG_S( 5, 4), (UINT16)VREG_S( 5, 5), (UINT16)VREG_S( 5, 6), (UINT16)VREG_S( 5, 7));
			break;
		case RSP_V6:
			strprintf(str, "%04X|%04X|%04X|%04X|%04X|%04X|%04X|%04X", (UINT16)VREG_S( 6, 0), (UINT16)VREG_S( 6, 1), (UINT16)VREG_S( 6, 2), (UINT16)VREG_S( 6, 3), (UINT16)VREG_S( 6, 4), (UINT16)VREG_S( 6, 5), (UINT16)VREG_S( 6, 6), (UINT16)VREG_S( 6, 7));
			break;
		case RSP_V7:
			strprintf(str, "%04X|%04X|%04X|%04X|%04X|%04X|%04X|%04X", (UINT16)VREG_S( 7, 0), (UINT16)VREG_S( 7, 1), (UINT16)VREG_S( 7, 2), (UINT16)VREG_S( 7, 3), (UINT16)VREG_S( 7, 4), (UINT16)VREG_S( 7, 5), (UINT16)VREG_S( 7, 6), (UINT16)VREG_S( 7, 7));
			break;
		case RSP_V8:
			strprintf(str, "%04X|%04X|%04X|%04X|%04X|%04X|%04X|%04X", (UINT16)VREG_S( 8, 0), (UINT16)VREG_S( 8, 1), (UINT16)VREG_S( 8, 2), (UINT16)VREG_S( 8, 3), (UINT16)VREG_S( 8, 4), (UINT16)VREG_S( 8, 5), (UINT16)VREG_S( 8, 6), (UINT16)VREG_S( 8, 7));
			break;
		case RSP_V9:
			strprintf(str, "%04X|%04X|%04X|%04X|%04X|%04X|%04X|%04X", (UINT16)VREG_S( 9, 0), (UINT16)VREG_S( 9, 1), (UINT16)VREG_S( 9, 2), (UINT16)VREG_S( 9, 3), (UINT16)VREG_S( 9, 4), (UINT16)VREG_S( 9, 5), (UINT16)VREG_S( 9, 6), (UINT16)VREG_S( 9, 7));
			break;
		case RSP_V10:
			strprintf(str, "%04X|%04X|%04X|%04X|%04X|%04X|%04X|%04X", (UINT16)VREG_S(10, 0), (UINT16)VREG_S(10, 1), (UINT16)VREG_S(10, 2), (UINT16)VREG_S(10, 3), (UINT16)VREG_S(10, 4), (UINT16)VREG_S(10, 5), (UINT16)VREG_S(10, 6), (UINT16)VREG_S(10, 7));
			break;
		case RSP_V11:
			strprintf(str, "%04X|%04X|%04X|%04X|%04X|%04X|%04X|%04X", (UINT16)VREG_S(11, 0), (UINT16)VREG_S(11, 1), (UINT16)VREG_S(11, 2), (UINT16)VREG_S(11, 3), (UINT16)VREG_S(11, 4), (UINT16)VREG_S(11, 5), (UINT16)VREG_S(11, 6), (UINT16)VREG_S(11, 7));
			break;
		case RSP_V12:
			strprintf(str, "%04X|%04X|%04X|%04X|%04X|%04X|%04X|%04X", (UINT16)VREG_S(12, 0), (UINT16)VREG_S(12, 1), (UINT16)VREG_S(12, 2), (UINT16)VREG_S(12, 3), (UINT16)VREG_S(12, 4), (UINT16)VREG_S(12, 5), (UINT16)VREG_S(12, 6), (UINT16)VREG_S(12, 7));
			break;
		case RSP_V13:
			strprintf(str, "%04X|%04X|%04X|%04X|%04X|%04X|%04X|%04X", (UINT16)VREG_S(13, 0), (UINT16)VREG_S(13, 1), (UINT16)VREG_S(13, 2), (UINT16)VREG_S(13, 3), (UINT16)VREG_S(13, 4), (UINT16)VREG_S(13, 5), (UINT16)VREG_S(13, 6), (UINT16)VREG_S(13, 7));
			break;
		case RSP_V14:
			strprintf(str, "%04X|%04X|%04X|%04X|%04X|%04X|%04X|%04X", (UINT16)VREG_S(14, 0), (UINT16)VREG_S(14, 1), (UINT16)VREG_S(14, 2), (UINT16)VREG_S(14, 3), (UINT16)VREG_S(14, 4), (UINT16)VREG_S(14, 5), (UINT16)VREG_S(14, 6), (UINT16)VREG_S(14, 7));
			break;
		case RSP_V15:
			strprintf(str, "%04X|%04X|%04X|%04X|%04X|%04X|%04X|%04X", (UINT16)VREG_S(15, 0), (UINT16)VREG_S(15, 1), (UINT16)VREG_S(15, 2), (UINT16)VREG_S(15, 3), (UINT16)VREG_S(15, 4), (UINT16)VREG_S(15, 5), (UINT16)VREG_S(15, 6), (UINT16)VREG_S(15, 7));
			break;
		case RSP_V16:
			strprintf(str, "%04X|%04X|%04X|%04X|%04X|%04X|%04X|%04X", (UINT16)VREG_S(16, 0), (UINT16)VREG_S(16, 1), (UINT16)VREG_S(16, 2), (UINT16)VREG_S(16, 3), (UINT16)VREG_S(16, 4), (UINT16)VREG_S(16, 5), (UINT16)VREG_S(16, 6), (UINT16)VREG_S(16, 7));
			break;
		case RSP_V17:
			strprintf(str, "%04X|%04X|%04X|%04X|%04X|%04X|%04X|%04X", (UINT16)VREG_S(17, 0), (UINT16)VREG_S(17, 1), (UINT16)VREG_S(17, 2), (UINT16)VREG_S(17, 3), (UINT16)VREG_S(17, 4), (UINT16)VREG_S(17, 5), (UINT16)VREG_S(17, 6), (UINT16)VREG_S(17, 7));
			break;
		case RSP_V18:
			strprintf(str, "%04X|%04X|%04X|%04X|%04X|%04X|%04X|%04X", (UINT16)VREG_S(18, 0), (UINT16)VREG_S(18, 1), (UINT16)VREG_S(18, 2), (UINT16)VREG_S(18, 3), (UINT16)VREG_S(18, 4), (UINT16)VREG_S(18, 5), (UINT16)VREG_S(18, 6), (UINT16)VREG_S(18, 7));
			break;
		case RSP_V19:
			strprintf(str, "%04X|%04X|%04X|%04X|%04X|%04X|%04X|%04X", (UINT16)VREG_S(19, 0), (UINT16)VREG_S(19, 1), (UINT16)VREG_S(19, 2), (UINT16)VREG_S(19, 3), (UINT16)VREG_S(19, 4), (UINT16)VREG_S(19, 5), (UINT16)VREG_S(19, 6), (UINT16)VREG_S(19, 7));
			break;
		case RSP_V20:
			strprintf(str, "%04X|%04X|%04X|%04X|%04X|%04X|%04X|%04X", (UINT16)VREG_S(20, 0), (UINT16)VREG_S(20, 1), (UINT16)VREG_S(20, 2), (UINT16)VREG_S(20, 3), (UINT16)VREG_S(20, 4), (UINT16)VREG_S(20, 5), (UINT16)VREG_S(20, 6), (UINT16)VREG_S(20, 7));
			break;
		case RSP_V21:
			strprintf(str, "%04X|%04X|%04X|%04X|%04X|%04X|%04X|%04X", (UINT16)VREG_S(21, 0), (UINT16)VREG_S(21, 1), (UINT16)VREG_S(21, 2), (UINT16)VREG_S(21, 3), (UINT16)VREG_S(21, 4), (UINT16)VREG_S(21, 5), (UINT16)VREG_S(21, 6), (UINT16)VREG_S(21, 7));
			break;
		case RSP_V22:
			strprintf(str, "%04X|%04X|%04X|%04X|%04X|%04X|%04X|%04X", (UINT16)VREG_S(22, 0), (UINT16)VREG_S(22, 1), (UINT16)VREG_S(22, 2), (UINT16)VREG_S(22, 3), (UINT16)VREG_S(22, 4), (UINT16)VREG_S(22, 5), (UINT16)VREG_S(22, 6), (UINT16)VREG_S(22, 7));
			break;
		case RSP_V23:
			strprintf(str, "%04X|%04X|%04X|%04X|%04X|%04X|%04X|%04X", (UINT16)VREG_S(23, 0), (UINT16)VREG_S(23, 1), (UINT16)VREG_S(23, 2), (UINT16)VREG_S(23, 3), (UINT16)VREG_S(23, 4), (UINT16)VREG_S(23, 5), (UINT16)VREG_S(23, 6), (UINT16)VREG_S(23, 7));
			break;
		case RSP_V24:
			strprintf(str, "%04X|%04X|%04X|%04X|%04X|%04X|%04X|%04X", (UINT16)VREG_S(24, 0), (UINT16)VREG_S(24, 1), (UINT16)VREG_S(24, 2), (UINT16)VREG_S(24, 3), (UINT16)VREG_S(24, 4), (UINT16)VREG_S(24, 5), (UINT16)VREG_S(24, 6), (UINT16)VREG_S(24, 7));
			break;
		case RSP_V25:
			strprintf(str, "%04X|%04X|%04X|%04X|%04X|%04X|%04X|%04X", (UINT16)VREG_S(25, 0), (UINT16)VREG_S(25, 1), (UINT16)VREG_S(25, 2), (UINT16)VREG_S(25, 3), (UINT16)VREG_S(25, 4), (UINT16)VREG_S(25, 5), (UINT16)VREG_S(25, 6), (UINT16)VREG_S(25, 7));
			break;
		case RSP_V26:
			strprintf(str, "%04X|%04X|%04X|%04X|%04X|%04X|%04X|%04X", (UINT16)VREG_S(26, 0), (UINT16)VREG_S(26, 1), (UINT16)VREG_S(26, 2), (UINT16)VREG_S(26, 3), (UINT16)VREG_S(26, 4), (UINT16)VREG_S(26, 5), (UINT16)VREG_S(26, 6), (UINT16)VREG_S(26, 7));
			break;
		case RSP_V27:
			strprintf(str, "%04X|%04X|%04X|%04X|%04X|%04X|%04X|%04X", (UINT16)VREG_S(27, 0), (UINT16)VREG_S(27, 1), (UINT16)VREG_S(27, 2), (UINT16)VREG_S(27, 3), (UINT16)VREG_S(27, 4), (UINT16)VREG_S(27, 5), (UINT16)VREG_S(27, 6), (UINT16)VREG_S(27, 7));
			break;
		case RSP_V28:
			strprintf(str, "%04X|%04X|%04X|%04X|%04X|%04X|%04X|%04X", (UINT16)VREG_S(28, 0), (UINT16)VREG_S(28, 1), (UINT16)VREG_S(28, 2), (UINT16)VREG_S(28, 3), (UINT16)VREG_S(28, 4), (UINT16)VREG_S(28, 5), (UINT16)VREG_S(28, 6), (UINT16)VREG_S(28, 7));
			break;
		case RSP_V29:
			strprintf(str, "%04X|%04X|%04X|%04X|%04X|%04X|%04X|%04X", (UINT16)VREG_S(29, 0), (UINT16)VREG_S(29, 1), (UINT16)VREG_S(29, 2), (UINT16)VREG_S(29, 3), (UINT16)VREG_S(29, 4), (UINT16)VREG_S(29, 5), (UINT16)VREG_S(29, 6), (UINT16)VREG_S(29, 7));
			break;
		case RSP_V30:
			strprintf(str, "%04X|%04X|%04X|%04X|%04X|%04X|%04X|%04X", (UINT16)VREG_S(30, 0), (UINT16)VREG_S(30, 1), (UINT16)VREG_S(30, 2), (UINT16)VREG_S(30, 3), (UINT16)VREG_S(30, 4), (UINT16)VREG_S(30, 5), (UINT16)VREG_S(30, 6), (UINT16)VREG_S(30, 7));
			break;
		case RSP_V31:
			strprintf(str, "%04X|%04X|%04X|%04X|%04X|%04X|%04X|%04X", (UINT16)VREG_S(31, 0), (UINT16)VREG_S(31, 1), (UINT16)VREG_S(31, 2), (UINT16)VREG_S(31, 3), (UINT16)VREG_S(31, 4), (UINT16)VREG_S(31, 5), (UINT16)VREG_S(31, 6), (UINT16)VREG_S(31, 7));
=======
			str = string_format("%04X|%04X|%04X|%04X|%04X|%04X|%04X|%04X", (uint16_t)VREG_S( 0, 0), (uint16_t)VREG_S( 0, 1), (uint16_t)VREG_S( 0, 2), (uint16_t)VREG_S( 0, 3), (uint16_t)VREG_S( 0, 4), (uint16_t)VREG_S( 0, 5), (uint16_t)VREG_S( 0, 6), (uint16_t)VREG_S( 0, 7));
			break;
		case RSP_V1:
			str = string_format("%04X|%04X|%04X|%04X|%04X|%04X|%04X|%04X", (uint16_t)VREG_S( 1, 0), (uint16_t)VREG_S( 1, 1), (uint16_t)VREG_S( 1, 2), (uint16_t)VREG_S( 1, 3), (uint16_t)VREG_S( 1, 4), (uint16_t)VREG_S( 1, 5), (uint16_t)VREG_S( 1, 6), (uint16_t)VREG_S( 1, 7));
			break;
		case RSP_V2:
			str = string_format("%04X|%04X|%04X|%04X|%04X|%04X|%04X|%04X", (uint16_t)VREG_S( 2, 0), (uint16_t)VREG_S( 2, 1), (uint16_t)VREG_S( 2, 2), (uint16_t)VREG_S( 2, 3), (uint16_t)VREG_S( 2, 4), (uint16_t)VREG_S( 2, 5), (uint16_t)VREG_S( 2, 6), (uint16_t)VREG_S( 2, 7));
			break;
		case RSP_V3:
			str = string_format("%04X|%04X|%04X|%04X|%04X|%04X|%04X|%04X", (uint16_t)VREG_S( 3, 0), (uint16_t)VREG_S( 3, 1), (uint16_t)VREG_S( 3, 2), (uint16_t)VREG_S( 3, 3), (uint16_t)VREG_S( 3, 4), (uint16_t)VREG_S( 3, 5), (uint16_t)VREG_S( 3, 6), (uint16_t)VREG_S( 3, 7));
			break;
		case RSP_V4:
			str = string_format("%04X|%04X|%04X|%04X|%04X|%04X|%04X|%04X", (uint16_t)VREG_S( 4, 0), (uint16_t)VREG_S( 4, 1), (uint16_t)VREG_S( 4, 2), (uint16_t)VREG_S( 4, 3), (uint16_t)VREG_S( 4, 4), (uint16_t)VREG_S( 4, 5), (uint16_t)VREG_S( 4, 6), (uint16_t)VREG_S( 4, 7));
			break;
		case RSP_V5:
			str = string_format("%04X|%04X|%04X|%04X|%04X|%04X|%04X|%04X", (uint16_t)VREG_S( 5, 0), (uint16_t)VREG_S( 5, 1), (uint16_t)VREG_S( 5, 2), (uint16_t)VREG_S( 5, 3), (uint16_t)VREG_S( 5, 4), (uint16_t)VREG_S( 5, 5), (uint16_t)VREG_S( 5, 6), (uint16_t)VREG_S( 5, 7));
			break;
		case RSP_V6:
			str = string_format("%04X|%04X|%04X|%04X|%04X|%04X|%04X|%04X", (uint16_t)VREG_S( 6, 0), (uint16_t)VREG_S( 6, 1), (uint16_t)VREG_S( 6, 2), (uint16_t)VREG_S( 6, 3), (uint16_t)VREG_S( 6, 4), (uint16_t)VREG_S( 6, 5), (uint16_t)VREG_S( 6, 6), (uint16_t)VREG_S( 6, 7));
			break;
		case RSP_V7:
			str = string_format("%04X|%04X|%04X|%04X|%04X|%04X|%04X|%04X", (uint16_t)VREG_S( 7, 0), (uint16_t)VREG_S( 7, 1), (uint16_t)VREG_S( 7, 2), (uint16_t)VREG_S( 7, 3), (uint16_t)VREG_S( 7, 4), (uint16_t)VREG_S( 7, 5), (uint16_t)VREG_S( 7, 6), (uint16_t)VREG_S( 7, 7));
			break;
		case RSP_V8:
			str = string_format("%04X|%04X|%04X|%04X|%04X|%04X|%04X|%04X", (uint16_t)VREG_S( 8, 0), (uint16_t)VREG_S( 8, 1), (uint16_t)VREG_S( 8, 2), (uint16_t)VREG_S( 8, 3), (uint16_t)VREG_S( 8, 4), (uint16_t)VREG_S( 8, 5), (uint16_t)VREG_S( 8, 6), (uint16_t)VREG_S( 8, 7));
			break;
		case RSP_V9:
			str = string_format("%04X|%04X|%04X|%04X|%04X|%04X|%04X|%04X", (uint16_t)VREG_S( 9, 0), (uint16_t)VREG_S( 9, 1), (uint16_t)VREG_S( 9, 2), (uint16_t)VREG_S( 9, 3), (uint16_t)VREG_S( 9, 4), (uint16_t)VREG_S( 9, 5), (uint16_t)VREG_S( 9, 6), (uint16_t)VREG_S( 9, 7));
			break;
		case RSP_V10:
			str = string_format("%04X|%04X|%04X|%04X|%04X|%04X|%04X|%04X", (uint16_t)VREG_S(10, 0), (uint16_t)VREG_S(10, 1), (uint16_t)VREG_S(10, 2), (uint16_t)VREG_S(10, 3), (uint16_t)VREG_S(10, 4), (uint16_t)VREG_S(10, 5), (uint16_t)VREG_S(10, 6), (uint16_t)VREG_S(10, 7));
			break;
		case RSP_V11:
			str = string_format("%04X|%04X|%04X|%04X|%04X|%04X|%04X|%04X", (uint16_t)VREG_S(11, 0), (uint16_t)VREG_S(11, 1), (uint16_t)VREG_S(11, 2), (uint16_t)VREG_S(11, 3), (uint16_t)VREG_S(11, 4), (uint16_t)VREG_S(11, 5), (uint16_t)VREG_S(11, 6), (uint16_t)VREG_S(11, 7));
			break;
		case RSP_V12:
			str = string_format("%04X|%04X|%04X|%04X|%04X|%04X|%04X|%04X", (uint16_t)VREG_S(12, 0), (uint16_t)VREG_S(12, 1), (uint16_t)VREG_S(12, 2), (uint16_t)VREG_S(12, 3), (uint16_t)VREG_S(12, 4), (uint16_t)VREG_S(12, 5), (uint16_t)VREG_S(12, 6), (uint16_t)VREG_S(12, 7));
			break;
		case RSP_V13:
			str = string_format("%04X|%04X|%04X|%04X|%04X|%04X|%04X|%04X", (uint16_t)VREG_S(13, 0), (uint16_t)VREG_S(13, 1), (uint16_t)VREG_S(13, 2), (uint16_t)VREG_S(13, 3), (uint16_t)VREG_S(13, 4), (uint16_t)VREG_S(13, 5), (uint16_t)VREG_S(13, 6), (uint16_t)VREG_S(13, 7));
			break;
		case RSP_V14:
			str = string_format("%04X|%04X|%04X|%04X|%04X|%04X|%04X|%04X", (uint16_t)VREG_S(14, 0), (uint16_t)VREG_S(14, 1), (uint16_t)VREG_S(14, 2), (uint16_t)VREG_S(14, 3), (uint16_t)VREG_S(14, 4), (uint16_t)VREG_S(14, 5), (uint16_t)VREG_S(14, 6), (uint16_t)VREG_S(14, 7));
			break;
		case RSP_V15:
			str = string_format("%04X|%04X|%04X|%04X|%04X|%04X|%04X|%04X", (uint16_t)VREG_S(15, 0), (uint16_t)VREG_S(15, 1), (uint16_t)VREG_S(15, 2), (uint16_t)VREG_S(15, 3), (uint16_t)VREG_S(15, 4), (uint16_t)VREG_S(15, 5), (uint16_t)VREG_S(15, 6), (uint16_t)VREG_S(15, 7));
			break;
		case RSP_V16:
			str = string_format("%04X|%04X|%04X|%04X|%04X|%04X|%04X|%04X", (uint16_t)VREG_S(16, 0), (uint16_t)VREG_S(16, 1), (uint16_t)VREG_S(16, 2), (uint16_t)VREG_S(16, 3), (uint16_t)VREG_S(16, 4), (uint16_t)VREG_S(16, 5), (uint16_t)VREG_S(16, 6), (uint16_t)VREG_S(16, 7));
			break;
		case RSP_V17:
			str = string_format("%04X|%04X|%04X|%04X|%04X|%04X|%04X|%04X", (uint16_t)VREG_S(17, 0), (uint16_t)VREG_S(17, 1), (uint16_t)VREG_S(17, 2), (uint16_t)VREG_S(17, 3), (uint16_t)VREG_S(17, 4), (uint16_t)VREG_S(17, 5), (uint16_t)VREG_S(17, 6), (uint16_t)VREG_S(17, 7));
			break;
		case RSP_V18:
			str = string_format("%04X|%04X|%04X|%04X|%04X|%04X|%04X|%04X", (uint16_t)VREG_S(18, 0), (uint16_t)VREG_S(18, 1), (uint16_t)VREG_S(18, 2), (uint16_t)VREG_S(18, 3), (uint16_t)VREG_S(18, 4), (uint16_t)VREG_S(18, 5), (uint16_t)VREG_S(18, 6), (uint16_t)VREG_S(18, 7));
			break;
		case RSP_V19:
			str = string_format("%04X|%04X|%04X|%04X|%04X|%04X|%04X|%04X", (uint16_t)VREG_S(19, 0), (uint16_t)VREG_S(19, 1), (uint16_t)VREG_S(19, 2), (uint16_t)VREG_S(19, 3), (uint16_t)VREG_S(19, 4), (uint16_t)VREG_S(19, 5), (uint16_t)VREG_S(19, 6), (uint16_t)VREG_S(19, 7));
			break;
		case RSP_V20:
			str = string_format("%04X|%04X|%04X|%04X|%04X|%04X|%04X|%04X", (uint16_t)VREG_S(20, 0), (uint16_t)VREG_S(20, 1), (uint16_t)VREG_S(20, 2), (uint16_t)VREG_S(20, 3), (uint16_t)VREG_S(20, 4), (uint16_t)VREG_S(20, 5), (uint16_t)VREG_S(20, 6), (uint16_t)VREG_S(20, 7));
			break;
		case RSP_V21:
			str = string_format("%04X|%04X|%04X|%04X|%04X|%04X|%04X|%04X", (uint16_t)VREG_S(21, 0), (uint16_t)VREG_S(21, 1), (uint16_t)VREG_S(21, 2), (uint16_t)VREG_S(21, 3), (uint16_t)VREG_S(21, 4), (uint16_t)VREG_S(21, 5), (uint16_t)VREG_S(21, 6), (uint16_t)VREG_S(21, 7));
			break;
		case RSP_V22:
			str = string_format("%04X|%04X|%04X|%04X|%04X|%04X|%04X|%04X", (uint16_t)VREG_S(22, 0), (uint16_t)VREG_S(22, 1), (uint16_t)VREG_S(22, 2), (uint16_t)VREG_S(22, 3), (uint16_t)VREG_S(22, 4), (uint16_t)VREG_S(22, 5), (uint16_t)VREG_S(22, 6), (uint16_t)VREG_S(22, 7));
			break;
		case RSP_V23:
			str = string_format("%04X|%04X|%04X|%04X|%04X|%04X|%04X|%04X", (uint16_t)VREG_S(23, 0), (uint16_t)VREG_S(23, 1), (uint16_t)VREG_S(23, 2), (uint16_t)VREG_S(23, 3), (uint16_t)VREG_S(23, 4), (uint16_t)VREG_S(23, 5), (uint16_t)VREG_S(23, 6), (uint16_t)VREG_S(23, 7));
			break;
		case RSP_V24:
			str = string_format("%04X|%04X|%04X|%04X|%04X|%04X|%04X|%04X", (uint16_t)VREG_S(24, 0), (uint16_t)VREG_S(24, 1), (uint16_t)VREG_S(24, 2), (uint16_t)VREG_S(24, 3), (uint16_t)VREG_S(24, 4), (uint16_t)VREG_S(24, 5), (uint16_t)VREG_S(24, 6), (uint16_t)VREG_S(24, 7));
			break;
		case RSP_V25:
			str = string_format("%04X|%04X|%04X|%04X|%04X|%04X|%04X|%04X", (uint16_t)VREG_S(25, 0), (uint16_t)VREG_S(25, 1), (uint16_t)VREG_S(25, 2), (uint16_t)VREG_S(25, 3), (uint16_t)VREG_S(25, 4), (uint16_t)VREG_S(25, 5), (uint16_t)VREG_S(25, 6), (uint16_t)VREG_S(25, 7));
			break;
		case RSP_V26:
			str = string_format("%04X|%04X|%04X|%04X|%04X|%04X|%04X|%04X", (uint16_t)VREG_S(26, 0), (uint16_t)VREG_S(26, 1), (uint16_t)VREG_S(26, 2), (uint16_t)VREG_S(26, 3), (uint16_t)VREG_S(26, 4), (uint16_t)VREG_S(26, 5), (uint16_t)VREG_S(26, 6), (uint16_t)VREG_S(26, 7));
			break;
		case RSP_V27:
			str = string_format("%04X|%04X|%04X|%04X|%04X|%04X|%04X|%04X", (uint16_t)VREG_S(27, 0), (uint16_t)VREG_S(27, 1), (uint16_t)VREG_S(27, 2), (uint16_t)VREG_S(27, 3), (uint16_t)VREG_S(27, 4), (uint16_t)VREG_S(27, 5), (uint16_t)VREG_S(27, 6), (uint16_t)VREG_S(27, 7));
			break;
		case RSP_V28:
			str = string_format("%04X|%04X|%04X|%04X|%04X|%04X|%04X|%04X", (uint16_t)VREG_S(28, 0), (uint16_t)VREG_S(28, 1), (uint16_t)VREG_S(28, 2), (uint16_t)VREG_S(28, 3), (uint16_t)VREG_S(28, 4), (uint16_t)VREG_S(28, 5), (uint16_t)VREG_S(28, 6), (uint16_t)VREG_S(28, 7));
			break;
		case RSP_V29:
			str = string_format("%04X|%04X|%04X|%04X|%04X|%04X|%04X|%04X", (uint16_t)VREG_S(29, 0), (uint16_t)VREG_S(29, 1), (uint16_t)VREG_S(29, 2), (uint16_t)VREG_S(29, 3), (uint16_t)VREG_S(29, 4), (uint16_t)VREG_S(29, 5), (uint16_t)VREG_S(29, 6), (uint16_t)VREG_S(29, 7));
			break;
		case RSP_V30:
			str = string_format("%04X|%04X|%04X|%04X|%04X|%04X|%04X|%04X", (uint16_t)VREG_S(30, 0), (uint16_t)VREG_S(30, 1), (uint16_t)VREG_S(30, 2), (uint16_t)VREG_S(30, 3), (uint16_t)VREG_S(30, 4), (uint16_t)VREG_S(30, 5), (uint16_t)VREG_S(30, 6), (uint16_t)VREG_S(30, 7));
			break;
		case RSP_V31:
			str = string_format("%04X|%04X|%04X|%04X|%04X|%04X|%04X|%04X", (uint16_t)VREG_S(31, 0), (uint16_t)VREG_S(31, 1), (uint16_t)VREG_S(31, 2), (uint16_t)VREG_S(31, 3), (uint16_t)VREG_S(31, 4), (uint16_t)VREG_S(31, 5), (uint16_t)VREG_S(31, 6), (uint16_t)VREG_S(31, 7));
>>>>>>> upstream/master
			break;
	}
}


/***************************************************************************
    Vector Load Instructions
***************************************************************************/

// LBV
//
// 31       25      20      15      10     6        0
// --------------------------------------------------
// | 110010 | BBBBB | TTTTT | 00000 | IIII | Offset |
// --------------------------------------------------
//
// Load 1 byte to vector byte index

void rsp_cop2_drc::lbv()
{
<<<<<<< HEAD
	UINT32 op = m_rspcop2_state->op;

	UINT32 ea = 0;
=======
	uint32_t op = m_rspcop2_state->op;

	uint32_t ea;
>>>>>>> upstream/master
	int dest = (op >> 16) & 0x1f;
	int base = (op >> 21) & 0x1f;
	int index = (op >> 7) & 0xf;
	int offset = (op & 0x7f);
	if (offset & 0x40)
	{
		offset |= 0xffffffc0;
	}

	ea = (base) ? m_rsp.m_rsp_state->r[base] + offset : offset;
	VREG_B(dest, index) = m_rsp.DM_READ8(ea);
}

static void cfunc_lbv(void *param)
{
	((rsp_cop2 *)param)->lbv();
}


// LSV
//
// 31       25      20      15      10     6        0
// --------------------------------------------------
// | 110010 | BBBBB | TTTTT | 00001 | IIII | Offset |
// --------------------------------------------------
//
// Loads 2 bytes starting from vector byte index

void rsp_cop2_drc::lsv()
{
<<<<<<< HEAD
	UINT32 op = m_rspcop2_state->op;
	int dest = (op >> 16) & 0x1f;
	int base = (op >> 21) & 0x1f;
	int index = (op >> 7) & 0xe;
=======
	uint32_t op = m_rspcop2_state->op;
	int dest = (op >> 16) & 0x1f;
	int base = (op >> 21) & 0x1f;
	int index = (op >> 7) & 0xf;
>>>>>>> upstream/master
	int offset = (op & 0x7f);
	if (offset & 0x40)
	{
		offset |= 0xffffffc0;
	}

<<<<<<< HEAD
	UINT32 ea = (base) ? m_rsp.m_rsp_state->r[base] + (offset * 2) : (offset * 2);
=======
	uint32_t ea = (base) ? m_rsp.m_rsp_state->r[base] + (offset * 2) : (offset * 2);
>>>>>>> upstream/master
	int end = index + 2;
	for (int i = index; i < end; i++)
	{
		VREG_B(dest, i) = m_rsp.DM_READ8(ea);
		ea++;
	}
}

static void cfunc_lsv(void *param)
{
	((rsp_cop2 *)param)->lsv();
}


// LLV
//
// 31       25      20      15      10     6        0
// --------------------------------------------------
// | 110010 | BBBBB | TTTTT | 00010 | IIII | Offset |
// --------------------------------------------------
//
// Loads 4 bytes starting from vector byte index

void rsp_cop2_drc::llv()
{
<<<<<<< HEAD
	UINT32 op = m_rspcop2_state->op;
	UINT32 ea = 0;
	int dest = (op >> 16) & 0x1f;
	int base = (op >> 21) & 0x1f;
	int index = (op >> 7) & 0xc;
=======
	uint32_t op = m_rspcop2_state->op;
	uint32_t ea;
	int dest = (op >> 16) & 0x1f;
	int base = (op >> 21) & 0x1f;
	int index = (op >> 7) & 0xf;
>>>>>>> upstream/master
	int offset = (op & 0x7f);
	if (offset & 0x40)
	{
		offset |= 0xffffffc0;
	}

	ea = (base) ? m_rsp.m_rsp_state->r[base] + (offset * 4) : (offset * 4);

	int end = index + 4;

	for (int i = index; i < end; i++)
	{
		VREG_B(dest, i) = m_rsp.DM_READ8(ea);
		ea++;
	}
}

static void cfunc_llv(void *param)
{
	((rsp_cop2 *)param)->llv();
}


// LDV
//
// 31       25      20      15      10     6        0
// --------------------------------------------------
// | 110010 | BBBBB | TTTTT | 00011 | IIII | Offset |
// --------------------------------------------------
//
// Loads 8 bytes starting from vector byte index

void rsp_cop2_drc::ldv()
{
<<<<<<< HEAD
	UINT32 op = m_rspcop2_state->op;
	UINT32 ea = 0;
	int dest = (op >> 16) & 0x1f;
	int base = (op >> 21) & 0x1f;
	int index = (op >> 7) & 0x8;
=======
	uint32_t op = m_rspcop2_state->op;
	uint32_t ea;
	int dest = (op >> 16) & 0x1f;
	int base = (op >> 21) & 0x1f;
	int index = (op >> 7) & 0xf;
>>>>>>> upstream/master
	int offset = (op & 0x7f);
	if (offset & 0x40)
	{
		offset |= 0xffffffc0;
	}

	ea = (base) ? m_rsp.m_rsp_state->r[base] + (offset * 8) : (offset * 8);

	int end = index + 8;

	for (int i = index; i < end; i++)
	{
		VREG_B(dest, i) = m_rsp.DM_READ8(ea);
		ea++;
	}
}

static void cfunc_ldv(void *param)
{
	((rsp_cop2 *)param)->ldv();
}


// LQV
//
// 31       25      20      15      10     6        0
// --------------------------------------------------
// | 110010 | BBBBB | TTTTT | 00100 | IIII | Offset |
// --------------------------------------------------
//
// Loads up to 16 bytes starting from vector byte index

void rsp_cop2_drc::lqv()
{
<<<<<<< HEAD
	UINT32 op = m_rspcop2_state->op;
=======
	uint32_t op = m_rspcop2_state->op;
>>>>>>> upstream/master
	int dest = (op >> 16) & 0x1f;
	int base = (op >> 21) & 0x1f;
	int offset = (op & 0x7f);
	if (offset & 0x40)
	{
		offset |= 0xffffffc0;
	}

<<<<<<< HEAD
	UINT32 ea = (base) ? m_rsp.m_rsp_state->r[base] + (offset * 16) : (offset * 16);
=======
	uint32_t ea = (base) ? m_rsp.m_rsp_state->r[base] + (offset * 16) : (offset * 16);
>>>>>>> upstream/master

	int end = 16 - (ea & 0xf);
	if (end > 16) end = 16;

	for (int i = 0; i < end; i++)
	{
		VREG_B(dest, i) = m_rsp.DM_READ8(ea);
		ea++;
	}
}

static void cfunc_lqv(void *param)
{
	((rsp_cop2 *)param)->lqv();
}


// LRV
//
// 31       25      20      15      10     6        0
// --------------------------------------------------
// | 110010 | BBBBB | TTTTT | 00101 | IIII | Offset |
// --------------------------------------------------
//
// Stores up to 16 bytes starting from right side until 16-byte boundary

void rsp_cop2_drc::lrv()
{
<<<<<<< HEAD
	UINT32 op = m_rspcop2_state->op;
=======
	uint32_t op = m_rspcop2_state->op;
>>>>>>> upstream/master
	int dest = (op >> 16) & 0x1f;
	int base = (op >> 21) & 0x1f;
	int index = (op >> 7) & 0xf;
	int offset = (op & 0x7f);
	if (offset & 0x40)
	{
		offset |= 0xffffffc0;
	}

<<<<<<< HEAD
	UINT32 ea = (base) ? m_rsp.m_rsp_state->r[base] + (offset * 16) : (offset * 16);
=======
	uint32_t ea = (base) ? m_rsp.m_rsp_state->r[base] + (offset * 16) : (offset * 16);
>>>>>>> upstream/master

	index = 16 - ((ea & 0xf) - index);
	ea &= ~0xf;

	for (int i = index; i < 16; i++)
	{
		VREG_B(dest, i) = m_rsp.DM_READ8(ea);
		ea++;
	}
}

static void cfunc_lrv(void *param)
{
	((rsp_cop2 *)param)->lrv();
}


// LPV
//
// 31       25      20      15      10     6        0
// --------------------------------------------------
// | 110010 | BBBBB | TTTTT | 00110 | IIII | Offset |
// --------------------------------------------------
//
// Loads a byte as the upper 8 bits of each element

void rsp_cop2_drc::lpv()
{
<<<<<<< HEAD
	UINT32 op = m_rspcop2_state->op;
=======
	uint32_t op = m_rspcop2_state->op;
>>>>>>> upstream/master
	int dest = (op >> 16) & 0x1f;
	int base = (op >> 21) & 0x1f;
	int index = (op >> 7) & 0xf;
	int offset = (op & 0x7f);
	if (offset & 0x40)
	{
		offset |= 0xffffffc0;
	}

<<<<<<< HEAD
	UINT32 ea = (base) ? m_rsp.m_rsp_state->r[base] + (offset * 8) : (offset * 8);
=======
	uint32_t ea = (base) ? m_rsp.m_rsp_state->r[base] + (offset * 8) : (offset * 8);
>>>>>>> upstream/master

	for (int i = 0; i < 8; i++)
	{
		W_VREG_S(dest, i) = m_rsp.DM_READ8(ea + (((16-index) + i) & 0xf)) << 8;
	}
}

static void cfunc_lpv(void *param)
{
	((rsp_cop2 *)param)->lpv();
}


// LUV
//
// 31       25      20      15      10     6        0
// --------------------------------------------------
// | 110010 | BBBBB | TTTTT | 00111 | IIII | Offset |
// --------------------------------------------------
//
// Loads a byte as the bits 14-7 of each element

void rsp_cop2_drc::luv()
{
<<<<<<< HEAD
	UINT32 op = m_rspcop2_state->op;
=======
	uint32_t op = m_rspcop2_state->op;
>>>>>>> upstream/master
	int dest = (op >> 16) & 0x1f;
	int base = (op >> 21) & 0x1f;
	int index = (op >> 7) & 0xf;
	int offset = (op & 0x7f);
	if (offset & 0x40)
	{
		offset |= 0xffffffc0;
	}

<<<<<<< HEAD
	UINT32 ea = (base) ? m_rsp.m_rsp_state->r[base] + (offset * 8) : (offset * 8);
=======
	uint32_t ea = (base) ? m_rsp.m_rsp_state->r[base] + (offset * 8) : (offset * 8);
>>>>>>> upstream/master

	for (int i = 0; i < 8; i++)
	{
		W_VREG_S(dest, i) = m_rsp.DM_READ8(ea + (((16-index) + i) & 0xf)) << 7;
	}
}

static void cfunc_luv(void *param)
{
	((rsp_cop2 *)param)->luv();
}


// LHV
//
// 31       25      20      15      10     6        0
// --------------------------------------------------
// | 110010 | BBBBB | TTTTT | 01000 | IIII | Offset |
// --------------------------------------------------
//
// Loads a byte as the bits 14-7 of each element, with 2-byte stride

void rsp_cop2_drc::lhv()
{
<<<<<<< HEAD
	UINT32 op = m_rspcop2_state->op;
=======
	uint32_t op = m_rspcop2_state->op;
>>>>>>> upstream/master
	int dest = (op >> 16) & 0x1f;
	int base = (op >> 21) & 0x1f;
	int index = (op >> 7) & 0xf;
	int offset = (op & 0x7f);
	if (offset & 0x40)
	{
		offset |= 0xffffffc0;
	}

<<<<<<< HEAD
	UINT32 ea = (base) ? m_rsp.m_rsp_state->r[base] + (offset * 16) : (offset * 16);
=======
	uint32_t ea = (base) ? m_rsp.m_rsp_state->r[base] + (offset * 16) : (offset * 16);
>>>>>>> upstream/master

	for (int i = 0; i < 8; i++)
	{
		W_VREG_S(dest, i) = m_rsp.DM_READ8(ea + (((16-index) + (i<<1)) & 0xf)) << 7;
	}
}

static void cfunc_lhv(void *param)
{
	((rsp_cop2 *)param)->lhv();
}


// LFV
// 31       25      20      15      10     6        0
// --------------------------------------------------
// | 110010 | BBBBB | TTTTT | 01001 | IIII | Offset |
// --------------------------------------------------
//
// Loads a byte as the bits 14-7 of upper or lower quad, with 4-byte stride

void rsp_cop2_drc::lfv()
{
<<<<<<< HEAD
	UINT32 op = m_rspcop2_state->op;
=======
	uint32_t op = m_rspcop2_state->op;
>>>>>>> upstream/master
	int dest = (op >> 16) & 0x1f;
	int base = (op >> 21) & 0x1f;
	int index = (op >> 7) & 0xf;
	int offset = (op & 0x7f);
	if (offset & 0x40)
	{
		offset |= 0xffffffc0;
	}

<<<<<<< HEAD
	UINT32 ea = (base) ? m_rsp.m_rsp_state->r[base] + (offset * 16) : (offset * 16);
=======
	uint32_t ea = (base) ? m_rsp.m_rsp_state->r[base] + (offset * 16) : (offset * 16);
>>>>>>> upstream/master

	// not sure what happens if 16-byte boundary is crossed...

	int end = (index >> 1) + 4;

	for (int i = index >> 1; i < end; i++)
	{
		W_VREG_S(dest, i) = m_rsp.DM_READ8(ea) << 7;
		ea += 4;
	}
}

static void cfunc_lfv(void *param)
{
	((rsp_cop2 *)param)->lfv();
}


// LWV
//
// 31       25      20      15      10     6        0
// --------------------------------------------------
// | 110010 | BBBBB | TTTTT | 01010 | IIII | Offset |
// --------------------------------------------------
//
// Loads the full 128-bit vector starting from vector byte index and wrapping to index 0
// after byte index 15

void rsp_cop2_drc::lwv()
{
<<<<<<< HEAD
	UINT32 op = m_rspcop2_state->op;
=======
	uint32_t op = m_rspcop2_state->op;
>>>>>>> upstream/master
	int dest = (op >> 16) & 0x1f;
	int base = (op >> 21) & 0x1f;
	int index = (op >> 7) & 0xf;
	int offset = (op & 0x7f);
	if (offset & 0x40)
	{
		offset |= 0xffffffc0;
	}

<<<<<<< HEAD
	UINT32 ea = (base) ? m_rsp.m_rsp_state->r[base] + (offset * 16) : (offset * 16);
=======
	uint32_t ea = (base) ? m_rsp.m_rsp_state->r[base] + (offset * 16) : (offset * 16);
>>>>>>> upstream/master
	int end = (16 - index) + 16;

	for (int i = (16 - index); i < end; i++)
	{
		VREG_B(dest, i & 0xf) = m_rsp.DM_READ8(ea);
		ea += 4;
	}
}

static void cfunc_lwv(void *param)
{
	((rsp_cop2 *)param)->lwv();
}


// LTV
//
// 31       25      20      15      10     6        0
// --------------------------------------------------
// | 110010 | BBBBB | TTTTT | 01011 | IIII | Offset |
// --------------------------------------------------
//
// Loads one element to maximum of 8 vectors, while incrementing element index

void rsp_cop2_drc::ltv()
{
<<<<<<< HEAD
	UINT32 op = m_rspcop2_state->op;
=======
	uint32_t op = m_rspcop2_state->op;
>>>>>>> upstream/master
	int dest = (op >> 16) & 0x1f;
	int base = (op >> 21) & 0x1f;
	int index = (op >> 7) & 0xf;
	int offset = (op & 0x7f);

	// FIXME: has a small problem with odd indices

	int vs = dest;
	int ve = dest + 8;
	if (ve > 32)
	{
		ve = 32;
	}

<<<<<<< HEAD
	int element = 7 - (index >> 1);

	UINT32 ea = (base) ? m_rsp.m_rsp_state->r[base] + (offset * 16) : (offset * 16);
=======
	int element;

	uint32_t ea = (base) ? m_rsp.m_rsp_state->r[base] + (offset * 16) : (offset * 16);
>>>>>>> upstream/master

	ea = ((ea + 8) & ~0xf) + (index & 1);
	for (int i = vs; i < ve; i++)
	{
		element = (8 - (index >> 1) + (i - vs)) << 1;
		VREG_B(i, (element & 0xf)) = m_rsp.DM_READ8(ea);
		VREG_B(i, ((element + 1) & 0xf)) = m_rsp.DM_READ8(ea + 1);
		ea += 2;
	}
}

static void cfunc_ltv(void *param)
{
	((rsp_cop2 *)param)->ltv();
}


<<<<<<< HEAD
int rsp_cop2_drc::generate_lwc2(drcuml_block *block, rsp_device::compiler_state *compiler, const opcode_desc *desc)
{
	UINT32 op = desc->opptr.l[0];
=======
bool rsp_cop2_drc::generate_lwc2(drcuml_block *block, rsp_device::compiler_state *compiler, const opcode_desc *desc)
{
	uint32_t op = desc->opptr.l[0];
>>>>>>> upstream/master
	int offset = (op & 0x7f);
	if (offset & 0x40)
	{
		offset |= 0xffffffc0;
	}

	switch ((op >> 11) & 0x1f)
	{
		case 0x00:      /* LBV */
			UML_MOV(block, mem(&m_rspcop2_state->op), desc->opptr.l[0]);        // mov     [m_rspcop2_state->op],desc->opptr.l
			UML_CALLC(block, cfunc_lbv, this);
<<<<<<< HEAD
			return TRUE;
=======
			return true;
>>>>>>> upstream/master

		case 0x01:      /* LSV */
			UML_MOV(block, mem(&m_rspcop2_state->op), desc->opptr.l[0]);        // mov     [m_rspcop2_state->op],desc->opptr.l
			UML_CALLC(block, cfunc_lsv, this);
<<<<<<< HEAD
			return TRUE;
=======
			return true;
>>>>>>> upstream/master

		case 0x02:      /* LLV */
			UML_MOV(block, mem(&m_rspcop2_state->op), desc->opptr.l[0]);        // mov     [m_rspcop2_state->op],desc->opptr.l
			UML_CALLC(block, cfunc_llv, this);
<<<<<<< HEAD
			return TRUE;
=======
			return true;
>>>>>>> upstream/master

		case 0x03:      /* LDV */
			UML_MOV(block, mem(&m_rspcop2_state->op), desc->opptr.l[0]);        // mov     [m_rspcop2_state->op],desc->opptr.l
			UML_CALLC(block, cfunc_ldv, this);
<<<<<<< HEAD
			return TRUE;
=======
			return true;
>>>>>>> upstream/master

		case 0x04:      /* LQV */
			UML_MOV(block, mem(&m_rspcop2_state->op), desc->opptr.l[0]);        // mov     [m_rspcop2_state->op],desc->opptr.l
			UML_CALLC(block, cfunc_lqv, this);
<<<<<<< HEAD
			return TRUE;
=======
			return true;
>>>>>>> upstream/master

		case 0x05:      /* LRV */
			UML_MOV(block, mem(&m_rspcop2_state->op), desc->opptr.l[0]);        // mov     [m_rspcop2_state->op],desc->opptr.l
			UML_CALLC(block, cfunc_lrv, this);
<<<<<<< HEAD
			return TRUE;
=======
			return true;
>>>>>>> upstream/master

		case 0x06:      /* LPV */
			UML_MOV(block, mem(&m_rspcop2_state->op), desc->opptr.l[0]);        // mov     [m_rspcop2_state->op],desc->opptr.l
			UML_CALLC(block, cfunc_lpv, this);
<<<<<<< HEAD
			return TRUE;
=======
			return true;
>>>>>>> upstream/master

		case 0x07:      /* LUV */
			UML_MOV(block, mem(&m_rspcop2_state->op), desc->opptr.l[0]);        // mov     [m_rspcop2_state->op],desc->opptr.l
			UML_CALLC(block, cfunc_luv, this);
<<<<<<< HEAD
			return TRUE;
=======
			return true;
>>>>>>> upstream/master

		case 0x08:      /* LHV */
			UML_MOV(block, mem(&m_rspcop2_state->op), desc->opptr.l[0]);        // mov     [m_rspcop2_state->op],desc->opptr.l
			UML_CALLC(block, cfunc_lhv, this);
<<<<<<< HEAD
			return TRUE;
=======
			return true;
>>>>>>> upstream/master

		case 0x09:      /* LFV */
			UML_MOV(block, mem(&m_rspcop2_state->op), desc->opptr.l[0]);        // mov     [m_rspcop2_state->op],desc->opptr.l
			UML_CALLC(block, cfunc_lfv, this);
<<<<<<< HEAD
			return TRUE;
=======
			return true;
>>>>>>> upstream/master

		case 0x0a:      /* LWV */
			UML_MOV(block, mem(&m_rspcop2_state->op), desc->opptr.l[0]);        // mov     [m_rspcop2_state->op],desc->opptr.l
			UML_CALLC(block, cfunc_lwv, this);
<<<<<<< HEAD
			return TRUE;
=======
			return true;
>>>>>>> upstream/master

		case 0x0b:      /* LTV */
			UML_MOV(block, mem(&m_rspcop2_state->op), desc->opptr.l[0]);        // mov     [m_rspcop2_state->op],desc->opptr.l
			UML_CALLC(block, cfunc_ltv, this);
<<<<<<< HEAD
			return TRUE;

		default:
			return FALSE;
=======
			return true;

		default:
			return false;
>>>>>>> upstream/master
	}
}


/***************************************************************************
    Vector Store Instructions
***************************************************************************/

// SBV
//
// 31       25      20      15      10     6        0
// --------------------------------------------------
// | 111010 | BBBBB | TTTTT | 00000 | IIII | Offset |
// --------------------------------------------------
//
// Stores 1 byte from vector byte index

void rsp_cop2_drc::sbv()
{
<<<<<<< HEAD
	UINT32 op = m_rspcop2_state->op;
=======
	uint32_t op = m_rspcop2_state->op;
>>>>>>> upstream/master
	int dest = (op >> 16) & 0x1f;
	int base = (op >> 21) & 0x1f;
	int index = (op >> 7) & 0xf;
	int offset = (op & 0x7f);
	if (offset & 0x40)
	{
		offset |= 0xffffffc0;
	}

<<<<<<< HEAD
	UINT32 ea = (base) ? m_rsp.m_rsp_state->r[base] + offset : offset;
=======
	uint32_t ea = (base) ? m_rsp.m_rsp_state->r[base] + offset : offset;
>>>>>>> upstream/master
	m_rsp.DM_WRITE8(ea, VREG_B(dest, index));
}

static void cfunc_sbv(void *param)
{
	((rsp_cop2 *)param)->sbv();
}


// SSV
//
// 31       25      20      15      10     6        0
// --------------------------------------------------
// | 111010 | BBBBB | TTTTT | 00001 | IIII | Offset |
// --------------------------------------------------
//
// Stores 2 bytes starting from vector byte index

void rsp_cop2_drc::ssv()
{
<<<<<<< HEAD
	UINT32 op = m_rspcop2_state->op;
=======
	uint32_t op = m_rspcop2_state->op;
>>>>>>> upstream/master
	int dest = (op >> 16) & 0x1f;
	int base = (op >> 21) & 0x1f;
	int index = (op >> 7) & 0xf;
	int offset = (op & 0x7f);
	if (offset & 0x40)
	{
		offset |= 0xffffffc0;
	}

<<<<<<< HEAD
	UINT32 ea = (base) ? m_rsp.m_rsp_state->r[base] + (offset * 2) : (offset * 2);
=======
	uint32_t ea = (base) ? m_rsp.m_rsp_state->r[base] + (offset * 2) : (offset * 2);
>>>>>>> upstream/master

	int end = index + 2;
	for (int i = index; i < end; i++)
	{
		m_rsp.DM_WRITE8(ea, VREG_B(dest, i));
		ea++;
	}
}

static void cfunc_ssv(void *param)
{
	((rsp_cop2 *)param)->ssv();
}


// SLV
//
// 31       25      20      15      10     6        0
// --------------------------------------------------
// | 111010 | BBBBB | TTTTT | 00010 | IIII | Offset |
// --------------------------------------------------
//
// Stores 4 bytes starting from vector byte index

void rsp_cop2_drc::slv()
{
<<<<<<< HEAD
	UINT32 op = m_rspcop2_state->op;
=======
	uint32_t op = m_rspcop2_state->op;
>>>>>>> upstream/master
	int dest = (op >> 16) & 0x1f;
	int base = (op >> 21) & 0x1f;
	int index = (op >> 7) & 0xf;
	int offset = (op & 0x7f);
	if (offset & 0x40)
	{
		offset |= 0xffffffc0;
	}

<<<<<<< HEAD
	UINT32 ea = (base) ? m_rsp.m_rsp_state->r[base] + (offset * 4) : (offset * 4);
=======
	uint32_t ea = (base) ? m_rsp.m_rsp_state->r[base] + (offset * 4) : (offset * 4);
>>>>>>> upstream/master

	int end = index + 4;
	for (int i = index; i < end; i++)
	{
		m_rsp.DM_WRITE8(ea, VREG_B(dest, i));
		ea++;
	}
}

static void cfunc_slv(void *param)
{
	((rsp_cop2 *)param)->slv();
}


// SDV
//
// 31       25      20      15      10     6        0
// --------------------------------------------------
// | 111010 | BBBBB | TTTTT | 00011 | IIII | Offset |
// --------------------------------------------------
//
// Stores 8 bytes starting from vector byte index

void rsp_cop2_drc::sdv()
{
<<<<<<< HEAD
	UINT32 op = m_rspcop2_state->op;
	int dest = (op >> 16) & 0x1f;
	int base = (op >> 21) & 0x1f;
	int index = (op >> 7) & 0x8;
=======
	uint32_t op = m_rspcop2_state->op;
	int dest = (op >> 16) & 0x1f;
	int base = (op >> 21) & 0x1f;
	int index = (op >> 7) & 0xf;
>>>>>>> upstream/master
	int offset = (op & 0x7f);
	if (offset & 0x40)
	{
		offset |= 0xffffffc0;
	}
<<<<<<< HEAD
	UINT32 ea = (base) ? m_rsp.m_rsp_state->r[base] + (offset * 8) : (offset * 8);
=======
	uint32_t ea = (base) ? m_rsp.m_rsp_state->r[base] + (offset * 8) : (offset * 8);
>>>>>>> upstream/master

	int end = index + 8;
	for (int i = index; i < end; i++)
	{
		m_rsp.DM_WRITE8(ea, VREG_B(dest, i));
		ea++;
	}
}

static void cfunc_sdv(void *param)
{
	((rsp_cop2 *)param)->sdv();
}


// SQV
//
// 31       25      20      15      10     6        0
// --------------------------------------------------
// | 111010 | BBBBB | TTTTT | 00100 | IIII | Offset |
// --------------------------------------------------
//
// Stores up to 16 bytes starting from vector byte index until 16-byte boundary

void rsp_cop2_drc::sqv()
{
<<<<<<< HEAD
	UINT32 op = m_rspcop2_state->op;
=======
	uint32_t op = m_rspcop2_state->op;
>>>>>>> upstream/master
	int dest = (op >> 16) & 0x1f;
	int base = (op >> 21) & 0x1f;
	int index = (op >> 7) & 0xf;
	int offset = (op & 0x7f);
	if (offset & 0x40)
	{
		offset |= 0xffffffc0;
	}

<<<<<<< HEAD
	UINT32 ea = (base) ? m_rsp.m_rsp_state->r[base] + (offset * 16) : (offset * 16);
=======
	uint32_t ea = (base) ? m_rsp.m_rsp_state->r[base] + (offset * 16) : (offset * 16);
>>>>>>> upstream/master
	int end = index + (16 - (ea & 0xf));
	for (int i=index; i < end; i++)
	{
		m_rsp.DM_WRITE8(ea, VREG_B(dest, i & 0xf));
		ea++;
	}
}

static void cfunc_sqv(void *param)
{
	((rsp_cop2 *)param)->sqv();
}


// SRV
//
// 31       25      20      15      10     6        0
// --------------------------------------------------
// | 111010 | BBBBB | TTTTT | 00101 | IIII | Offset |
// --------------------------------------------------
//
// Stores up to 16 bytes starting from right side until 16-byte boundary

void rsp_cop2_drc::srv()
{
<<<<<<< HEAD
	UINT32 op = m_rspcop2_state->op;
=======
	uint32_t op = m_rspcop2_state->op;
>>>>>>> upstream/master
	int dest = (op >> 16) & 0x1f;
	int base = (op >> 21) & 0x1f;
	int index = (op >> 7) & 0xf;
	int offset = (op & 0x7f);
	if (offset & 0x40)
	{
		offset |= 0xffffffc0;
	}

<<<<<<< HEAD
	UINT32 ea = (base) ? m_rsp.m_rsp_state->r[base] + (offset * 16) : (offset * 16);
=======
	uint32_t ea = (base) ? m_rsp.m_rsp_state->r[base] + (offset * 16) : (offset * 16);
>>>>>>> upstream/master

	int end = index + (ea & 0xf);
	int o = (16 - (ea & 0xf)) & 0xf;
	ea &= ~0xf;

	for (int i = index; i < end; i++)
	{
		m_rsp.DM_WRITE8(ea, VREG_B(dest, ((i + o) & 0xf)));
		ea++;
	}
}

static void cfunc_srv(void *param)
{
	((rsp_cop2 *)param)->srv();
}


// SPV
//
// 31       25      20      15      10     6        0
// --------------------------------------------------
// | 111010 | BBBBB | TTTTT | 00110 | IIII | Offset |
// --------------------------------------------------
//
// Stores upper 8 bits of each element

void rsp_cop2_drc::spv()
{
<<<<<<< HEAD
	UINT32 op = m_rspcop2_state->op;
=======
	uint32_t op = m_rspcop2_state->op;
>>>>>>> upstream/master
	int dest = (op >> 16) & 0x1f;
	int base = (op >> 21) & 0x1f;
	int index = (op >> 7) & 0xf;
	int offset = (op & 0x7f);
	if (offset & 0x40)
	{
		offset |= 0xffffffc0;
	}

<<<<<<< HEAD
	UINT32 ea = (base) ? m_rsp.m_rsp_state->r[base] + (offset * 8) : (offset * 8);
=======
	uint32_t ea = (base) ? m_rsp.m_rsp_state->r[base] + (offset * 8) : (offset * 8);
>>>>>>> upstream/master
	int end = index + 8;
	for (int i=index; i < end; i++)
	{
		if ((i & 0xf) < 8)
		{
			m_rsp.DM_WRITE8(ea, VREG_B(dest, (i & 0xf) << 1));
		}
		else
		{
			m_rsp.DM_WRITE8(ea, VREG_S(dest, (i & 0x7)) >> 7);
		}
		ea++;
	}
}

static void cfunc_spv(void *param)
{
	((rsp_cop2 *)param)->spv();
}


// SUV
//
// 31       25      20      15      10     6        0
// --------------------------------------------------
// | 111010 | BBBBB | TTTTT | 00111 | IIII | Offset |
// --------------------------------------------------
//
// Stores bits 14-7 of each element

void rsp_cop2_drc::suv()
{
<<<<<<< HEAD
	UINT32 op = m_rspcop2_state->op;
=======
	uint32_t op = m_rspcop2_state->op;
>>>>>>> upstream/master
	int dest = (op >> 16) & 0x1f;
	int base = (op >> 21) & 0x1f;
	int index = (op >> 7) & 0xf;
	int offset = (op & 0x7f);
	if (offset & 0x40)
	{
		offset |= 0xffffffc0;
	}

<<<<<<< HEAD
	UINT32 ea = (base) ? m_rsp.m_rsp_state->r[base] + (offset * 8) : (offset * 8);
=======
	uint32_t ea = (base) ? m_rsp.m_rsp_state->r[base] + (offset * 8) : (offset * 8);
>>>>>>> upstream/master
	int end = index + 8;
	for (int i=index; i < end; i++)
	{
		if ((i & 0xf) < 8)
		{
			m_rsp.DM_WRITE8(ea, VREG_S(dest, (i & 0x7)) >> 7);
		}
		else
		{
			m_rsp.DM_WRITE8(ea, VREG_B(dest, ((i & 0x7) << 1)));
		}
		ea++;
	}
}

static void cfunc_suv(void *param)
{
	((rsp_cop2 *)param)->suv();
}


// SHV
//
// 31       25      20      15      10     6        0
// --------------------------------------------------
// | 111010 | BBBBB | TTTTT | 01000 | IIII | Offset |
// --------------------------------------------------
//
// Stores bits 14-7 of each element, with 2-byte stride

void rsp_cop2_drc::shv()
{
<<<<<<< HEAD
	UINT32 op = m_rspcop2_state->op;
=======
	uint32_t op = m_rspcop2_state->op;
>>>>>>> upstream/master
	int dest = (op >> 16) & 0x1f;
	int base = (op >> 21) & 0x1f;
	int index = (op >> 7) & 0xf;
	int offset = (op & 0x7f);
	if (offset & 0x40)
	{
		offset |= 0xffffffc0;
	}

<<<<<<< HEAD
	UINT32 ea = (base) ? m_rsp.m_rsp_state->r[base] + (offset * 16) : (offset * 16);
	for (int i=0; i < 8; i++)
	{
		int element = index + (i << 1);
		UINT8 d = (VREG_B(dest, (element & 0xf)) << 1) |
=======
	uint32_t ea = (base) ? m_rsp.m_rsp_state->r[base] + (offset * 16) : (offset * 16);
	for (int i=0; i < 8; i++)
	{
		int element = index + (i << 1);
		uint8_t d = (VREG_B(dest, (element & 0xf)) << 1) |
>>>>>>> upstream/master
					(VREG_B(dest, ((element + 1) & 0xf)) >> 7);
		m_rsp.DM_WRITE8(ea, d);
		ea += 2;
	}
}

static void cfunc_shv(void *param)
{
	((rsp_cop2 *)param)->shv();
}


// SFV
//
// 31       25      20      15      10     6        0
// --------------------------------------------------
// | 111010 | BBBBB | TTTTT | 01001 | IIII | Offset |
// --------------------------------------------------
//
// Stores bits 14-7 of upper or lower quad, with 4-byte stride

void rsp_cop2_drc::sfv()
{
<<<<<<< HEAD
	UINT32 op = m_rspcop2_state->op;
=======
	uint32_t op = m_rspcop2_state->op;
>>>>>>> upstream/master
	int dest = (op >> 16) & 0x1f;
	int base = (op >> 21) & 0x1f;
	int index = (op >> 7) & 0xf;
	int offset = (op & 0x7f);
	if (offset & 0x40)
	{
		offset |= 0xffffffc0;
	}

<<<<<<< HEAD
	UINT32 ea = (base) ? m_rsp.m_rsp_state->r[base] + (offset * 16) : (offset * 16);
=======
	uint32_t ea = (base) ? m_rsp.m_rsp_state->r[base] + (offset * 16) : (offset * 16);
>>>>>>> upstream/master
	int eaoffset = ea & 0xf;
	ea &= ~0xf;

	int end = (index >> 1) + 4;

	for (int i = index>>1; i < end; i++)
	{
		m_rsp.DM_WRITE8(ea + (eaoffset & 0xf), VREG_S(dest, i) >> 7);
		eaoffset += 4;
	}
}

static void cfunc_sfv(void *param)
{
	((rsp_cop2 *)param)->sfv();
}


// SWV
//
// 31       25      20      15      10     6        0
// --------------------------------------------------
// | 111010 | BBBBB | TTTTT | 01010 | IIII | Offset |
// --------------------------------------------------
//
// Stores the full 128-bit vector starting from vector byte index and wrapping to index 0
// after byte index 15

void rsp_cop2_drc::swv()
{
<<<<<<< HEAD
	UINT32 op = m_rspcop2_state->op;
=======
	uint32_t op = m_rspcop2_state->op;
>>>>>>> upstream/master
	int dest = (op >> 16) & 0x1f;
	int base = (op >> 21) & 0x1f;
	int index = (op >> 7) & 0xf;
	int offset = (op & 0x7f);
	if (offset & 0x40)
	{
		offset |= 0xffffffc0;
	}

<<<<<<< HEAD
	UINT32 ea = (base) ? m_rsp.m_rsp_state->r[base] + (offset * 16) : (offset * 16);
=======
	uint32_t ea = (base) ? m_rsp.m_rsp_state->r[base] + (offset * 16) : (offset * 16);
>>>>>>> upstream/master
	int eaoffset = ea & 0xf;
	ea &= ~0xf;

	int end = index + 16;
	for (int i = index; i < end; i++)
	{
		m_rsp.DM_WRITE8(ea + (eaoffset & 0xf), VREG_B(dest, i & 0xf));
		eaoffset++;
	}
}

static void cfunc_swv(void *param)
{
	((rsp_cop2 *)param)->swv();
}


// STV
//
// 31       25      20      15      10     6        0
// --------------------------------------------------
// | 111010 | BBBBB | TTTTT | 01011 | IIII | Offset |
// --------------------------------------------------
//
// Stores one element from maximum of 8 vectors, while incrementing element index

void rsp_cop2_drc::stv()
{
<<<<<<< HEAD
	UINT32 op = m_rspcop2_state->op;
=======
	uint32_t op = m_rspcop2_state->op;
>>>>>>> upstream/master
	int dest = (op >> 16) & 0x1f;
	int base = (op >> 21) & 0x1f;
	int index = (op >> 7) & 0xf;
	int offset = (op & 0x7f);

	if (offset & 0x40)
	{
		offset |= 0xffffffc0;
	}

	int vs = dest;
	int ve = dest + 8;
	if (ve > 32)
	{
		ve = 32;
	}

	int element = 8 - (index >> 1);

<<<<<<< HEAD
	UINT32 ea = (base) ? m_rsp.m_rsp_state->r[base] + (offset * 16) : (offset * 16);
=======
	uint32_t ea = (base) ? m_rsp.m_rsp_state->r[base] + (offset * 16) : (offset * 16);
>>>>>>> upstream/master
	int eaoffset = (ea & 0xf) + (element * 2);
	ea &= ~0xf;

	for (int i = vs; i < ve; i++)
	{
		m_rsp.DM_WRITE16(ea + (eaoffset & 0xf), VREG_S(i, element & 0x7));
		eaoffset += 2;
		element++;
	}
}

static void cfunc_stv(void *param)
{
	((rsp_cop2 *)param)->stv();
}

<<<<<<< HEAD
int rsp_cop2_drc::generate_swc2(drcuml_block *block, rsp_device::compiler_state *compiler, const opcode_desc *desc)
{
	UINT32 op = desc->opptr.l[0];
=======
bool rsp_cop2_drc::generate_swc2(drcuml_block *block, rsp_device::compiler_state *compiler, const opcode_desc *desc)
{
	uint32_t op = desc->opptr.l[0];
>>>>>>> upstream/master
	int offset = (op & 0x7f);
	if (offset & 0x40)
	{
		offset |= 0xffffffc0;
	}

	switch ((op >> 11) & 0x1f)
	{
		case 0x00:      /* SBV */
			UML_MOV(block, mem(&m_rspcop2_state->op), desc->opptr.l[0]);        // mov     [arg0],desc->opptr.l
			UML_CALLC(block, cfunc_sbv, this);
<<<<<<< HEAD
			return TRUE;
=======
			return true;
>>>>>>> upstream/master

		case 0x01:      /* SSV */
			UML_MOV(block, mem(&m_rspcop2_state->op), desc->opptr.l[0]);        // mov     [arg0],desc->opptr.l
			UML_CALLC(block, cfunc_ssv, this);
<<<<<<< HEAD
			return TRUE;
=======
			return true;
>>>>>>> upstream/master

		case 0x02:      /* SLV */
			UML_MOV(block, mem(&m_rspcop2_state->op), desc->opptr.l[0]);        // mov     [arg0],desc->opptr.l
			UML_CALLC(block, cfunc_slv, this);
<<<<<<< HEAD
			return TRUE;
=======
			return true;
>>>>>>> upstream/master

		case 0x03:      /* SDV */
			UML_MOV(block, mem(&m_rspcop2_state->op), desc->opptr.l[0]);        // mov     [arg0],desc->opptr.l
			UML_CALLC(block, cfunc_sdv, this);
<<<<<<< HEAD
			return TRUE;
=======
			return true;
>>>>>>> upstream/master

		case 0x04:      /* SQV */
			UML_MOV(block, mem(&m_rspcop2_state->op), desc->opptr.l[0]);        // mov     [arg0],desc->opptr.l
			UML_CALLC(block, cfunc_sqv, this);
<<<<<<< HEAD
			return TRUE;
=======
			return true;
>>>>>>> upstream/master

		case 0x05:      /* SRV */
			UML_MOV(block, mem(&m_rspcop2_state->op), desc->opptr.l[0]);        // mov     [arg0],desc->opptr.l
			UML_CALLC(block, cfunc_srv, this);
<<<<<<< HEAD
			return TRUE;
=======
			return true;
>>>>>>> upstream/master

		case 0x06:      /* SPV */
			UML_MOV(block, mem(&m_rspcop2_state->op), desc->opptr.l[0]);        // mov     [arg0],desc->opptr.l
			UML_CALLC(block, cfunc_spv, this);
<<<<<<< HEAD
			return TRUE;
=======
			return true;
>>>>>>> upstream/master

		case 0x07:      /* SUV */
			UML_MOV(block, mem(&m_rspcop2_state->op), desc->opptr.l[0]);        // mov     [arg0],desc->opptr.l
			UML_CALLC(block, cfunc_suv, this);
<<<<<<< HEAD
			return TRUE;
=======
			return true;
>>>>>>> upstream/master

		case 0x08:      /* SHV */
			UML_MOV(block, mem(&m_rspcop2_state->op), desc->opptr.l[0]);        // mov     [arg0],desc->opptr.l
			UML_CALLC(block, cfunc_shv, this);
<<<<<<< HEAD
			return TRUE;
=======
			return true;
>>>>>>> upstream/master

		case 0x09:      /* SFV */
			UML_MOV(block, mem(&m_rspcop2_state->op), desc->opptr.l[0]);        // mov     [arg0],desc->opptr.l
			UML_CALLC(block, cfunc_sfv, this);
<<<<<<< HEAD
			return TRUE;
=======
			return true;
>>>>>>> upstream/master

		case 0x0a:      /* SWV */
			UML_MOV(block, mem(&m_rspcop2_state->op), desc->opptr.l[0]);        // mov     [arg0],desc->opptr.l
			UML_CALLC(block, cfunc_swv, this);
<<<<<<< HEAD
			return TRUE;
=======
			return true;
>>>>>>> upstream/master

		case 0x0b:      /* STV */
			UML_MOV(block, mem(&m_rspcop2_state->op), desc->opptr.l[0]);        // mov     [arg0],desc->opptr.l
			UML_CALLC(block, cfunc_stv, this);
<<<<<<< HEAD
			return TRUE;

		default:
			m_rsp.unimplemented_opcode(op);
			return FALSE;
	}

	return TRUE;
=======
			return true;

		default:
			m_rsp.unimplemented_opcode(op);
			return false;
	}

	return true;
>>>>>>> upstream/master
}


/***************************************************************************
    Vector Opcodes
***************************************************************************/

// VMULF
//
// 31       25  24     20      15      10      5        0
// ------------------------------------------------------
// | 010010 | 1 | EEEE | SSSSS | TTTTT | DDDDD | 000000 |
// ------------------------------------------------------
//
// Multiplies signed integer by signed integer * 2

void rsp_cop2_drc::vmulf()
{
	CACHE_VALUES();

	for (int i = 0; i < 8; i++)
	{
<<<<<<< HEAD
		UINT16 w1, w2;
		GET_VS1(w1, i);
		GET_VS2(w2, i);
		INT32 s1 = (INT32)(INT16)w1;
		INT32 s2 = (INT32)(INT16)w2;
=======
		uint16_t w1, w2;
		GET_VS1(w1, i);
		GET_VS2(w2, i);
		int32_t s1 = (int32_t)(int16_t)w1;
		int32_t s2 = (int32_t)(int16_t)w2;
>>>>>>> upstream/master

		if (s1 == -32768 && s2 == -32768)
		{
			// overflow
<<<<<<< HEAD
			ACCUM(i) = S64(0x0000800080000000);
=======
			ACCUM(i) = s64(0x0000800080000000U);
>>>>>>> upstream/master
			m_vres[i] = 0x7fff;
		}
		else
		{
<<<<<<< HEAD
			ACCUM(i) = (INT64)(s1 * s2 * 2 + 0x8000) << 16; // rounding?
=======
			ACCUM(i) = (int64_t)(s1 * s2 * 2 + 0x8000) << 16; // rounding?
>>>>>>> upstream/master
			m_vres[i] = ACCUM_M(i);
		}
	}
	WRITEBACK_RESULT();
}

static void cfunc_vmulf(void *param)
{
	((rsp_cop2 *)param)->vmulf();
}


// VMULU
//
// 31       25  24     20      15      10      5        0
// ------------------------------------------------------
// | 010010 | 1 | EEEE | SSSSS | TTTTT | DDDDD | 000001 |
// ------------------------------------------------------
//

void rsp_cop2_drc::vmulu()
{
	CACHE_VALUES();

	for (int i = 0; i < 8; i++)
	{
<<<<<<< HEAD
		UINT16 w1, w2;
		GET_VS1(w1, i);
		GET_VS2(w2, i);
		INT32 s1 = (INT32)(INT16)w1;
		INT32 s2 = (INT32)(INT16)w2;

		INT64 r = s1 * s2 * 2 + 0x8000; // rounding?
=======
		uint16_t w1, w2;
		GET_VS1(w1, i);
		GET_VS2(w2, i);
		int32_t s1 = (int32_t)(int16_t)w1;
		int32_t s2 = (int32_t)(int16_t)w2;

		int64_t r = s1 * s2 * 2 + 0x8000; // rounding?
>>>>>>> upstream/master

		ACCUM(i) = r << 16;

		if (r < 0)
		{
			m_vres[i] = 0;
		}
<<<<<<< HEAD
		else if (((INT16)(ACCUM_H(i)) ^ (INT16)(ACCUM_M(i))) < 0)
=======
		else if (((int16_t)(ACCUM_H(i)) ^ (int16_t)(ACCUM_M(i))) < 0)
>>>>>>> upstream/master
		{
			m_vres[i] = -1;
		}
		else
		{
			m_vres[i] = ACCUM_M(i);
		}
	}
	WRITEBACK_RESULT();
}

static void cfunc_vmulu(void *param)
{
	((rsp_cop2 *)param)->vmulu();
}


// VMUDL
//
// 31       25  24     20      15      10      5        0
// ------------------------------------------------------
// | 010010 | 1 | EEEE | SSSSS | TTTTT | DDDDD | 001101 |
// ------------------------------------------------------
//
// Multiplies signed integer by unsigned fraction
// The result is added into accumulator
// The middle slice of accumulator is stored into destination element

void rsp_cop2_drc::vmudl()
{
	CACHE_VALUES();

	for (int i = 0; i < 8; i++)
	{
<<<<<<< HEAD
		UINT16 w1, w2;
		GET_VS1(w1, i);
		GET_VS2(w2, i);
		UINT32 s1 = (UINT32)(UINT16)w1;
		UINT32 s2 = (UINT32)(UINT16)w2;
=======
		uint16_t w1, w2;
		GET_VS1(w1, i);
		GET_VS2(w2, i);
		uint32_t s1 = (uint32_t)(uint16_t)w1;
		uint32_t s2 = (uint32_t)(uint16_t)w2;
>>>>>>> upstream/master

		ACCUM(i) = s1 * s2;

		m_vres[i] = ACCUM_L(i);
	}
	WRITEBACK_RESULT();
}

static void cfunc_vmudl(void *param)
{
	((rsp_cop2 *)param)->vmudl();
}


// VMUDM
//
// 31       25  24     20      15      10      5        0
// ------------------------------------------------------
// | 010010 | 1 | EEEE | SSSSS | TTTTT | DDDDD | 000101 |
// ------------------------------------------------------
//
// Multiplies signed integer by unsigned fraction
// The result is stored into accumulator
// The middle slice of accumulator is stored into destination element

void rsp_cop2_drc::vmudm()
{
	CACHE_VALUES();

	for (int i = 0; i < 8; i++)
	{
<<<<<<< HEAD
		UINT16 w1, w2;
		GET_VS1(w1, i);
		GET_VS2(w2, i);
		INT32 s1 = (INT32)(INT16)w1;
		INT32 s2 = (UINT16)w2;

		ACCUM(i) = (INT64)(s1 * s2) << 16;
=======
		uint16_t w1, w2;
		GET_VS1(w1, i);
		GET_VS2(w2, i);
		int32_t s1 = (int32_t)(int16_t)w1;
		int32_t s2 = (uint16_t)w2;

		ACCUM(i) = (int64_t)(s1 * s2) << 16;
>>>>>>> upstream/master

		m_vres[i] = ACCUM_M(i);
	}
	WRITEBACK_RESULT();
}

static void cfunc_vmudm(void *param)
{
	((rsp_cop2 *)param)->vmudm();
}


// VMUDN
//
// 31       25  24     20      15      10      5        0
// ------------------------------------------------------
// | 010010 | 1 | EEEE | SSSSS | TTTTT | DDDDD | 000110 |
// ------------------------------------------------------
//
// Multiplies unsigned fraction by signed integer
// The result is stored into accumulator
// The low slice of accumulator is stored into destination element

void rsp_cop2_drc::vmudn()
{
	CACHE_VALUES();

	for (int i = 0; i < 8; i++)
	{
<<<<<<< HEAD
		UINT16 w1, w2;
		GET_VS1(w1, i);
		GET_VS2(w2, i);
		INT32 s1 = (UINT16)w1;
		INT32 s2 = (INT32)(INT16)w2;

		INT32 r = s1 * s2;

		ACCUM(i) = (INT64)(s1 * s2) << 16;

		m_vres[i] = (UINT16)(r);
=======
		uint16_t w1, w2;
		GET_VS1(w1, i);
		GET_VS2(w2, i);
		int32_t s1 = (uint16_t)w1;
		int32_t s2 = (int32_t)(int16_t)w2;

		int32_t r = s1 * s2;

		ACCUM(i) = (int64_t)(s1 * s2) << 16;

		m_vres[i] = (uint16_t)(r);
>>>>>>> upstream/master
	}
	WRITEBACK_RESULT();
}

static void cfunc_vmudn(void *param)
{
	((rsp_cop2 *)param)->vmudn();
}


// VMUDH
//
// 31       25  24     20      15      10      5        0
// ------------------------------------------------------
// | 010010 | 1 | EEEE | SSSSS | TTTTT | DDDDD | 000111 |
// ------------------------------------------------------
//
// Multiplies signed integer by signed integer
// The result is stored into highest 32 bits of accumulator, the low slice is zero
// The highest 32 bits of accumulator is saturated into destination element

void rsp_cop2_drc::vmudh()
{
	CACHE_VALUES();

	for (int i = 0; i < 8; i++)
	{
<<<<<<< HEAD
		UINT16 w1, w2;
		GET_VS1(w1, i);
		GET_VS2(w2, i);
		INT32 s1 = (INT32)(INT16)w1;
		INT32 s2 = (INT32)(INT16)w2;

		INT32 r = s1 * s2;

		ACCUM(i) = (INT64)r << 32;

		if (r < -32768) r = -32768;
		if (r >  32767) r = 32767;
		m_vres[i] = (INT16)(r);
=======
		uint16_t w1, w2;
		GET_VS1(w1, i);
		GET_VS2(w2, i);
		int32_t s1 = (int32_t)(int16_t)w1;
		int32_t s2 = (int32_t)(int16_t)w2;

		int32_t r = s1 * s2;

		ACCUM(i) = (int64_t)r << 32;

		if (r < -32768) r = -32768;
		if (r >  32767) r = 32767;
		m_vres[i] = (int16_t)(r);
>>>>>>> upstream/master
	}
	WRITEBACK_RESULT();
}

static void cfunc_vmudh(void *param)
{
	((rsp_cop2 *)param)->vmudh();
}


// VMACF
//
// 31       25  24     20      15      10      5        0
// ------------------------------------------------------
// | 010010 | 1 | EEEE | SSSSS | TTTTT | DDDDD | 001000 |
// ------------------------------------------------------
//

void rsp_cop2_drc::vmacf()
{
	CACHE_VALUES();

	for (int i = 0; i < 8; i++)
	{
<<<<<<< HEAD
		UINT16 w1, w2;
		GET_VS1(w1, i);
		GET_VS2(w2, i);
		INT32 s1 = (INT32)(INT16)w1;
		INT32 s2 = (INT32)(INT16)w2;

		ACCUM(i) += (INT64)(s1 * s2 * 2) << 16;
=======
		uint16_t w1, w2;
		GET_VS1(w1, i);
		GET_VS2(w2, i);
		int32_t s1 = (int32_t)(int16_t)w1;
		int32_t s2 = (int32_t)(int16_t)w2;

		ACCUM(i) += (int64_t)(s1 * s2 * 2) << 16;
>>>>>>> upstream/master

		m_vres[i] = SATURATE_ACCUM(i, 1, 0x8000, 0x7fff);
	}
	WRITEBACK_RESULT();
}

static void cfunc_vmacf(void *param)
{
	((rsp_cop2 *)param)->vmacf();
}


// VMACU
//
// 31       25  24     20      15      10      5        0
// ------------------------------------------------------
// | 010010 | 1 | EEEE | SSSSS | TTTTT | DDDDD | 001001 |
// ------------------------------------------------------
//

void rsp_cop2_drc::vmacu()
{
	CACHE_VALUES();

	for (int i = 0; i < 8; i++)
	{
<<<<<<< HEAD
		UINT16 w1, w2;
		GET_VS1(w1, i);
		GET_VS2(w2, i);
		INT32 s1 = (INT32)(INT16)w1;
		INT32 s2 = (INT32)(INT16)w2;

		ACCUM(i) += (INT64)(s1 * s2 * 2) << 16;

		if ((INT16)ACCUM_H(i) < 0)
=======
		uint16_t w1, w2;
		GET_VS1(w1, i);
		GET_VS2(w2, i);
		int32_t s1 = (int32_t)(int16_t)w1;
		int32_t s2 = (int32_t)(int16_t)w2;

		ACCUM(i) += (int64_t)(s1 * s2 * 2) << 16;

		if ((int16_t)ACCUM_H(i) < 0)
>>>>>>> upstream/master
		{
			m_vres[i] = 0;
		}
		else
		{
			if (ACCUM_H(i) != 0)
			{
<<<<<<< HEAD
				m_vres[i] = (INT16)0xffff;
			}
			else
			{
				if ((INT16)ACCUM_M(i) < 0)
				{
					m_vres[i] = (INT16)0xffff;
=======
				m_vres[i] = (int16_t)0xffff;
			}
			else
			{
				if ((int16_t)ACCUM_M(i) < 0)
				{
					m_vres[i] = (int16_t)0xffff;
>>>>>>> upstream/master
				}
				else
				{
					m_vres[i] = ACCUM_M(i);
				}
			}
		}
	}
	WRITEBACK_RESULT();
}

static void cfunc_vmacu(void *param)
{
	((rsp_cop2 *)param)->vmacu();
}


// VMADL
//
// 31       25  24     20      15      10      5        0
// ------------------------------------------------------
// | 010010 | 1 | EEEE | SSSSS | TTTTT | DDDDD | 001100 |
// ------------------------------------------------------
//
// Multiplies unsigned fraction by unsigned fraction
// Adds the higher 16 bits of the 32-bit result to accumulator
// The low slice of accumulator is stored into destination element

void rsp_cop2_drc::vmadl()
{
	CACHE_VALUES();

	for (int i = 0; i < 8; i++)
	{
<<<<<<< HEAD
		UINT16 w1, w2;
		GET_VS1(w1, i);
		GET_VS2(w2, i);
		UINT32 s1 = w1;
		UINT32 s2 = w2;
=======
		uint16_t w1, w2;
		GET_VS1(w1, i);
		GET_VS2(w2, i);
		uint32_t s1 = w1;
		uint32_t s2 = w2;
>>>>>>> upstream/master

		ACCUM(i) += (s1 * s2) & 0xffff0000;

		m_vres[i] = SATURATE_ACCUM(i, 0, 0x0000, 0xffff);
	}
	WRITEBACK_RESULT();
}

static void cfunc_vmadl(void *param)
{
	((rsp_cop2 *)param)->vmadl();
}


// VMADM
//

void rsp_cop2_drc::vmadm()
{
	CACHE_VALUES();

	for (int i = 0; i < 8; i++)
	{
<<<<<<< HEAD
		UINT16 w1, w2;
		GET_VS1(w1, i);
		GET_VS2(w2, i);
		UINT32 s1 = (INT32)(INT16)w1;
		UINT32 s2 = (UINT16)w2;

		ACCUM(i) += (INT64)(INT32)(s1 * s2) << 16;
=======
		uint16_t w1, w2;
		GET_VS1(w1, i);
		GET_VS2(w2, i);
		uint32_t s1 = (int32_t)(int16_t)w1;
		uint32_t s2 = (uint16_t)w2;

		ACCUM(i) += (int64_t)(int32_t)(s1 * s2) << 16;
>>>>>>> upstream/master

		m_vres[i] = SATURATE_ACCUM(i, 1, 0x8000, 0x7fff);
	}
	WRITEBACK_RESULT();
}

static void cfunc_vmadm(void *param)
{
	((rsp_cop2 *)param)->vmadm();
}


// VMADN
//

void rsp_cop2_drc::vmadn()
{
	CACHE_VALUES();

	for (int i = 0; i < 8; i++)
	{
<<<<<<< HEAD
		UINT16 w1, w2;
		GET_VS1(w1, i);
		GET_VS2(w2, i);
		INT32 s1 = (UINT16)w1;
		INT32 s2 = (INT32)(INT16)w2;

		ACCUM(i) += (INT64)(s1 * s2) << 16;
=======
		uint16_t w1, w2;
		GET_VS1(w1, i);
		GET_VS2(w2, i);
		int32_t s1 = (uint16_t)w1;
		int32_t s2 = (int32_t)(int16_t)w2;

		ACCUM(i) += (int64_t)(s1 * s2) << 16;
>>>>>>> upstream/master

		m_vres[i] = SATURATE_ACCUM(i, 0, 0x0000, 0xffff);
	}
	WRITEBACK_RESULT();
}

static void cfunc_vmadn(void *param)
{
	((rsp_cop2 *)param)->vmadn();
}


// VMADH
//
// 31       25  24     20      15      10      5        0
// ------------------------------------------------------
// | 010010 | 1 | EEEE | SSSSS | TTTTT | DDDDD | 001111 |
// ------------------------------------------------------
//
// Multiplies signed integer by signed integer
// The result is added into highest 32 bits of accumulator, the low slice is zero
// The highest 32 bits of accumulator is saturated into destination element

void rsp_cop2_drc::vmadh()
{
	CACHE_VALUES();

	for (int i = 0; i < 8; i++)
	{
<<<<<<< HEAD
		INT16 w1, w2;
		GET_VS1(w1, i);
		GET_VS2(w2, i);
		INT32 s1 = (INT32)(INT16)w1;
		INT32 s2 = (INT32)(INT16)w2;

		ACCUM(i) += (INT64)(s1 * s2) << 32;
=======
		int16_t w1, w2;
		GET_VS1(w1, i);
		GET_VS2(w2, i);
		int32_t s1 = (int32_t)(int16_t)w1;
		int32_t s2 = (int32_t)(int16_t)w2;

		ACCUM(i) += (int64_t)(s1 * s2) << 32;
>>>>>>> upstream/master

		m_vres[i] = SATURATE_ACCUM(i, 1, 0x8000, 0x7fff);
	}
	WRITEBACK_RESULT();
}

static void cfunc_vmadh(void *param)
{
	((rsp_cop2 *)param)->vmadh();
}


// VADD
// 31       25  24     20      15      10      5        0
// ------------------------------------------------------
// | 010010 | 1 | EEEE | SSSSS | TTTTT | DDDDD | 010000 |
// ------------------------------------------------------
//
// Adds two vector registers and carry flag, the result is saturated to 32767

void rsp_cop2_drc::vadd()
{
	CACHE_VALUES();

	for (int i = 0; i < 8; i++)
	{
<<<<<<< HEAD
		INT16 w1, w2;
		GET_VS1(w1, i);
		GET_VS2(w2, i);
		INT32 s1 = (INT32)(INT16)w1;
		INT32 s2 = (INT32)(INT16)w2;
		INT32 r = s1 + s2 + (((CARRY_FLAG(i)) != 0) ? 1 : 0);

		SET_ACCUM_L((INT16)(r), i);

		if (r > 32767) r = 32767;
		if (r < -32768) r = -32768;
		m_vres[i] = (INT16)(r);
=======
		int16_t w1, w2;
		GET_VS1(w1, i);
		GET_VS2(w2, i);
		int32_t s1 = (int32_t)(int16_t)w1;
		int32_t s2 = (int32_t)(int16_t)w2;
		int32_t r = s1 + s2 + (((CARRY_FLAG(i)) != 0) ? 1 : 0);

		SET_ACCUM_L((int16_t)(r), i);

		if (r > 32767) r = 32767;
		if (r < -32768) r = -32768;
		m_vres[i] = (int16_t)(r);
>>>>>>> upstream/master
	}
	CLEAR_ZERO_FLAGS();
	CLEAR_CARRY_FLAGS();
	WRITEBACK_RESULT();
}

static void cfunc_vadd(void *param)
{
	((rsp_cop2 *)param)->vadd();
}


// VSUB
//
// 31       25  24     20      15      10      5        0
// ------------------------------------------------------
// | 010010 | 1 | EEEE | SSSSS | TTTTT | DDDDD | 010001 |
// ------------------------------------------------------
//
// Subtracts two vector registers and carry flag, the result is saturated to -32768
// TODO: check VS2REG == VDREG

void rsp_cop2_drc::vsub()
{
	CACHE_VALUES();

	for (int i = 0; i < 8; i++)
	{
<<<<<<< HEAD
		INT16 w1, w2;
		GET_VS1(w1, i);
		GET_VS2(w2, i);
		INT32 s1 = (INT32)(INT16)w1;
		INT32 s2 = (INT32)(INT16)w2;
		INT32 r = s1 - s2 - (((CARRY_FLAG(i)) != 0) ? 1 : 0);

		SET_ACCUM_L((INT16)(r), i);
=======
		int16_t w1, w2;
		GET_VS1(w1, i);
		GET_VS2(w2, i);
		int32_t s1 = (int32_t)(int16_t)w1;
		int32_t s2 = (int32_t)(int16_t)w2;
		int32_t r = s1 - s2 - (((CARRY_FLAG(i)) != 0) ? 1 : 0);

		SET_ACCUM_L((int16_t)(r), i);
>>>>>>> upstream/master

		if (r > 32767) r = 32767;
		if (r < -32768) r = -32768;

<<<<<<< HEAD
		m_vres[i] = (INT16)(r);
=======
		m_vres[i] = (int16_t)(r);
>>>>>>> upstream/master
	}
	CLEAR_ZERO_FLAGS();
	CLEAR_CARRY_FLAGS();
	WRITEBACK_RESULT();
}

static void cfunc_vsub(void *param)
{
	((rsp_cop2 *)param)->vsub();
}


// VABS
//
// 31       25  24     20      15      10      5        0
// ------------------------------------------------------
// | 010010 | 1 | EEEE | SSSSS | TTTTT | DDDDD | 010011 |
// ------------------------------------------------------
//
// Changes the sign of source register 2 if source register 1 is negative and stores the result to destination register

void rsp_cop2_drc::vabs()
{
	CACHE_VALUES();

	for (int i = 0; i < 8; i++)
	{
<<<<<<< HEAD
		INT16 s1, s2;
=======
		int16_t s1, s2;
>>>>>>> upstream/master
		GET_VS1(s1, i);
		GET_VS2(s2, i);

		if (s1 < 0)
		{
			if (s2 == -32768)
			{
				m_vres[i] = 32767;
			}
			else
			{
				m_vres[i] = -s2;
			}
		}
		else if (s1 > 0)
		{
			m_vres[i] = s2;
		}
		else
		{
			m_vres[i] = 0;
		}

		SET_ACCUM_L(m_vres[i], i);
	}
	WRITEBACK_RESULT();
}

static void cfunc_vabs(void *param)
{
	((rsp_cop2 *)param)->vabs();
}


// VADDC
//
// 31       25  24     20      15      10      5        0
// ------------------------------------------------------
// | 010010 | 1 | EEEE | SSSSS | TTTTT | DDDDD | 010100 |
// ------------------------------------------------------
//
// Adds two vector registers, the carry out is stored into carry register
// TODO: check VS2REG = VDREG

void rsp_cop2_drc::vaddc()
{
	CACHE_VALUES();

	CLEAR_ZERO_FLAGS();
	CLEAR_CARRY_FLAGS();

	for (int i = 0; i < 8; i++)
	{
<<<<<<< HEAD
		INT16 w1, w2;
		GET_VS1(w1, i);
		GET_VS2(w2, i);
		INT32 s1 = (UINT32)(UINT16)w1;
		INT32 s2 = (UINT32)(UINT16)w2;
		INT32 r = s1 + s2;

		m_vres[i] = (INT16)(r);
		SET_ACCUM_L((INT16)r, i);
=======
		int16_t w1, w2;
		GET_VS1(w1, i);
		GET_VS2(w2, i);
		int32_t s1 = (uint32_t)(uint16_t)w1;
		int32_t s2 = (uint32_t)(uint16_t)w2;
		int32_t r = s1 + s2;

		m_vres[i] = (int16_t)(r);
		SET_ACCUM_L((int16_t)r, i);
>>>>>>> upstream/master

		if (r & 0xffff0000)
		{
			SET_CARRY_FLAG(i);
		}
	}
	WRITEBACK_RESULT();
}

static void cfunc_vaddc(void *param)
{
	((rsp_cop2 *)param)->vaddc();
}


// VSUBC
//
// 31       25  24     20      15      10      5        0
// ------------------------------------------------------
// | 010010 | 1 | EEEE | SSSSS | TTTTT | DDDDD | 010101 |
// ------------------------------------------------------
//
// Subtracts two vector registers, the carry out is stored into carry register
// TODO: check VS2REG = VDREG

void rsp_cop2_drc::vsubc()
{
	CACHE_VALUES();

	CLEAR_ZERO_FLAGS();
	CLEAR_CARRY_FLAGS();

	for (int i = 0; i < 8; i++)
	{
<<<<<<< HEAD
		INT16 w1, w2;
		GET_VS1(w1, i);
		GET_VS2(w2, i);
		INT32 s1 = (UINT32)(UINT16)w1;
		INT32 s2 = (UINT32)(UINT16)w2;
		INT32 r = s1 - s2;

		m_vres[i] = (INT16)(r);
		SET_ACCUM_L((UINT16)r, i);

		if ((UINT16)(r) != 0)
=======
		int16_t w1, w2;
		GET_VS1(w1, i);
		GET_VS2(w2, i);
		int32_t s1 = (uint32_t)(uint16_t)w1;
		int32_t s2 = (uint32_t)(uint16_t)w2;
		int32_t r = s1 - s2;

		m_vres[i] = (int16_t)(r);
		SET_ACCUM_L((uint16_t)r, i);

		if ((uint16_t)(r) != 0)
>>>>>>> upstream/master
		{
			SET_ZERO_FLAG(i);
		}
		if (r & 0xffff0000)
		{
			SET_CARRY_FLAG(i);
		}
	}
	WRITEBACK_RESULT();
}

static void cfunc_vsubc(void *param)
{
	((rsp_cop2 *)param)->vsubc();
}


// VADDB
//
// 31       25  24     20      15      10      5        0
// ------------------------------------------------------
// | 010010 | 1 | EEEE | SSSSS | TTTTT | DDDDD | 010110 |
// ------------------------------------------------------
//
// Adds two vector registers bytewise with rounding

void rsp_cop2_drc::vaddb()
{
	CACHE_VALUES();
	const int round = (el == 0) ? 0 : (1 << (el - 1));

	for (int i = 0; i < 8; i++)
	{
<<<<<<< HEAD
		UINT16 w1, w2;
		GET_VS1(w1, i);
		GET_VS2(w2, i);

		UINT8 hb1 = w1 >> 8;
		UINT8 lb1 = w1 & 0xff;
		UINT8 hb2 = w2 >> 8;
		UINT8 lb2 = w2 & 0xff;

		UINT16 hs = hb1 + hb2 + round;
		UINT16 ls = lb1 + lb2 + round;
=======
		uint16_t w1, w2;
		GET_VS1(w1, i);
		GET_VS2(w2, i);

		uint8_t hb1 = w1 >> 8;
		uint8_t lb1 = w1 & 0xff;
		uint8_t hb2 = w2 >> 8;
		uint8_t lb2 = w2 & 0xff;

		uint16_t hs = hb1 + hb2 + round;
		uint16_t ls = lb1 + lb2 + round;
>>>>>>> upstream/master

		SET_ACCUM_L((hs << 8) | ls, i);

		hs >>= EL;
		if (hs > 255)
		{
			hs = 255;
		}

		ls >>= EL;
		if (ls > 255)
		{
			ls = 255;
		}

		m_vres[i] = 0; // VD writeback disabled on production hardware
		// m_vres[i] = (hs << 8) | ls;
	}
	WRITEBACK_RESULT();
}

static void cfunc_vaddb(void *param)
{
	((rsp_cop2 *)param)->vaddb();
}


// VSAW
//
// 31       25  24     20      15      10      5        0
// ------------------------------------------------------
// | 010010 | 1 | EEEE | SSSSS | TTTTT | DDDDD | 011101 |
// ------------------------------------------------------
//
// Stores high, middle or low slice of accumulator to destination vector

void rsp_cop2_drc::vsaw()
{
	const int op = m_rspcop2_state->op;
	const int vdreg = VDREG;
	const int el = EL;

	switch (el)
	{
		case 0x08:      // VSAWH
			for (int i = 0; i < 8; i++)
			{
				W_VREG_S(vdreg, i) = ACCUM_H(i);
			}
			break;
		case 0x09:      // VSAWM
			for (int i = 0; i < 8; i++)
			{
				W_VREG_S(vdreg, i) = ACCUM_M(i);
			}
			break;
		case 0x0a:      // VSAWL
			for (int i = 0; i < 8; i++)
			{
				W_VREG_S(vdreg, i) = ACCUM_L(i);
			}
			break;
		default:        // Unsupported
		{
			for (int i = 0; i < 8; i++)
			{
				W_VREG_S(vdreg, i) = 0;
			}
		}
	}
}

static void cfunc_vsaw(void *param)
{
	((rsp_cop2 *)param)->vsaw();
}


// VLT
//
// 31       25  24     20      15      10      5        0
// ------------------------------------------------------
// | 010010 | 1 | EEEE | SSSSS | TTTTT | DDDDD | 100000 |
// ------------------------------------------------------
//
// Sets compare flags if elements in VS1 are less than VS2
// Moves the element in VS2 to destination vector

void rsp_cop2_drc::vlt()
{
	CACHE_VALUES();

	CLEAR_COMPARE_FLAGS();
	CLEAR_CLIP2_FLAGS();

	for (int i = 0; i < 8; i++)
	{
<<<<<<< HEAD
		INT16 s1, s2;
=======
		int16_t s1, s2;
>>>>>>> upstream/master
		GET_VS1(s1, i);
		GET_VS2(s2, i);

		if (s1 < s2)
		{
			SET_COMPARE_FLAG(i);
		}
		else if (s1 == s2)
		{
			if (ZERO_FLAG(i) != 0 && CARRY_FLAG(i) != 0)
			{
				SET_COMPARE_FLAG(i);
			}
		}

		if (COMPARE_FLAG(i) != 0)
		{
			m_vres[i] = s1;
		}
		else
		{
			m_vres[i] = s2;
		}

		SET_ACCUM_L(m_vres[i], i);
	}

	CLEAR_ZERO_FLAGS();
	CLEAR_CARRY_FLAGS();
	WRITEBACK_RESULT();
}

static void cfunc_vlt(void *param)
{
	((rsp_cop2 *)param)->vlt();
}


// VEQ
//
// 31       25  24     20      15      10      5        0
// ------------------------------------------------------
// | 010010 | 1 | EEEE | SSSSS | TTTTT | DDDDD | 100001 |
// ------------------------------------------------------
//
// Sets compare flags if elements in VS1 are equal with VS2
// Moves the element in VS2 to destination vector

void rsp_cop2_drc::veq()
{
	CACHE_VALUES();

	CLEAR_COMPARE_FLAGS();
	CLEAR_CLIP2_FLAGS();

	for (int i = 0; i < 8; i++)
	{
<<<<<<< HEAD
		INT16 s1, s2;
=======
		int16_t s1, s2;
>>>>>>> upstream/master
		GET_VS1(s1, i);
		GET_VS2(s2, i);

		if ((s1 == s2) && ZERO_FLAG(i) == 0)
		{
			SET_COMPARE_FLAG(i);
			m_vres[i] = s1;
		}
		else
		{
			m_vres[i] = s2;
		}

		SET_ACCUM_L(m_vres[i], i);
	}

	CLEAR_ZERO_FLAGS();
	CLEAR_CARRY_FLAGS();
	WRITEBACK_RESULT();
}

static void cfunc_veq(void *param)
{
	((rsp_cop2 *)param)->veq();
}


// VNE
//
// 31       25  24     20      15      10      5        0
// ------------------------------------------------------
// | 010010 | 1 | EEEE | SSSSS | TTTTT | DDDDD | 100010 |
// ------------------------------------------------------
//
// Sets compare flags if elements in VS1 are not equal with VS2
// Moves the element in VS2 to destination vector

void rsp_cop2_drc::vne()
{
	CACHE_VALUES();

	CLEAR_COMPARE_FLAGS();
	CLEAR_CLIP2_FLAGS();

	for (int i = 0; i < 8; i++)
	{
<<<<<<< HEAD
		INT16 s1, s2;
=======
		int16_t s1, s2;
>>>>>>> upstream/master
		GET_VS1(s1, i);
		GET_VS2(s2, i);

		if (s1 != s2 || ZERO_FLAG(i) != 0)
		{
			SET_COMPARE_FLAG(i);
			m_vres[i] = s1;
		}
		else
		{
			m_vres[i] = s2;
		}

		SET_ACCUM_L(m_vres[i], i);
	}

	CLEAR_ZERO_FLAGS();
	CLEAR_CARRY_FLAGS();
	WRITEBACK_RESULT();
}

static void cfunc_vne(void *param)
{
	((rsp_cop2 *)param)->vne();
}


// VGE
//
// 31       25  24     20      15      10      5        0
// ------------------------------------------------------
// | 010010 | 1 | EEEE | SSSSS | TTTTT | DDDDD | 100011 |
// ------------------------------------------------------
//
// Sets compare flags if elements in VS1 are greater or equal with VS2
// Moves the element in VS2 to destination vector

void rsp_cop2_drc::vge()
{
	CACHE_VALUES();

	CLEAR_COMPARE_FLAGS();
	CLEAR_CLIP2_FLAGS();

	for (int i = 0; i < 8; i++)
	{
<<<<<<< HEAD
		INT16 s1, s2;
=======
		int16_t s1, s2;
>>>>>>> upstream/master
		GET_VS1(s1, i);
		GET_VS2(s2, i);
		if ((s1 == s2 && (ZERO_FLAG(i) == 0 || CARRY_FLAG(i) == 0)) || s1 > s2)
		{
			SET_COMPARE_FLAG(i);
			m_vres[i] = s1;
		}
		else
		{
			m_vres[i] = s2;
		}

		SET_ACCUM_L(m_vres[i], i);
	}

	CLEAR_ZERO_FLAGS();
	CLEAR_CARRY_FLAGS();
	WRITEBACK_RESULT();
}

static void cfunc_vge(void *param)
{
	((rsp_cop2 *)param)->vge();
}


// VCL
//
// 31       25  24     20      15      10      5        0
// ------------------------------------------------------
// | 010010 | 1 | EEEE | SSSSS | TTTTT | DDDDD | 100100 |
// ------------------------------------------------------
//
// Vector clip low

void rsp_cop2_drc::vcl()
{
	CACHE_VALUES();

	for (int i = 0; i < 8; i++)
	{
<<<<<<< HEAD
		INT16 s1, s2;
=======
		int16_t s1, s2;
>>>>>>> upstream/master
		GET_VS1(s1, i);
		GET_VS2(s2, i);

		if (CARRY_FLAG(i) != 0)
		{
			if (ZERO_FLAG(i) != 0)
			{
				if (COMPARE_FLAG(i) != 0)
				{
<<<<<<< HEAD
					SET_ACCUM_L(-(UINT16)s2, i);
=======
					SET_ACCUM_L(-(uint16_t)s2, i);
>>>>>>> upstream/master
				}
				else
				{
					SET_ACCUM_L(s1, i);
				}
			}
			else
			{
				if (CLIP1_FLAG(i) != 0)
				{
<<<<<<< HEAD
					if (((UINT32)(UINT16)(s1) + (UINT32)(UINT16)(s2)) > 0x10000)
=======
					if (((uint32_t)(uint16_t)(s1) + (uint32_t)(uint16_t)(s2)) > 0x10000)
>>>>>>> upstream/master
					{
						SET_ACCUM_L(s1, i);
						CLEAR_COMPARE_FLAG(i);
					}
					else
					{
<<<<<<< HEAD
						SET_ACCUM_L(-((UINT16)s2), i);
=======
						SET_ACCUM_L(-((uint16_t)s2), i);
>>>>>>> upstream/master
						SET_COMPARE_FLAG(i);
					}
				}
				else
				{
<<<<<<< HEAD
					if (((UINT32)(UINT16)(s1) + (UINT32)(UINT16)(s2)) != 0)
=======
					if (((uint32_t)(uint16_t)(s1) + (uint32_t)(uint16_t)(s2)) != 0)
>>>>>>> upstream/master
					{
						SET_ACCUM_L(s1, i);
						CLEAR_COMPARE_FLAG(i);
					}
					else
					{
<<<<<<< HEAD
						SET_ACCUM_L(-((UINT16)s2), i);
=======
						SET_ACCUM_L(-((uint16_t)s2), i);
>>>>>>> upstream/master
						SET_COMPARE_FLAG(i);
					}
				}
			}
		}
		else
		{
			if (ZERO_FLAG(i) != 0)
			{
				if (CLIP2_FLAG(i) != 0)
				{
					SET_ACCUM_L(s2, i);
				}
				else
				{
					SET_ACCUM_L(s1, i);
				}
			}
			else
			{
<<<<<<< HEAD
				if (((INT32)(UINT16)s1 - (INT32)(UINT16)s2) >= 0)
=======
				if (((int32_t)(uint16_t)s1 - (int32_t)(uint16_t)s2) >= 0)
>>>>>>> upstream/master
				{
					SET_ACCUM_L(s2, i);
					SET_CLIP2_FLAG(i);
				}
				else
				{
					SET_ACCUM_L(s1, i);
					CLEAR_CLIP2_FLAG(i);
				}
			}
		}
		m_vres[i] = ACCUM_L(i);
	}
	CLEAR_ZERO_FLAGS();
	CLEAR_CARRY_FLAGS();
	CLEAR_CLIP1_FLAGS();
	WRITEBACK_RESULT();
}

static void cfunc_vcl(void *param)
{
	((rsp_cop2 *)param)->vcl();
}


// VCH
//
// 31       25  24     20      15      10      5        0
// ------------------------------------------------------
// | 010010 | 1 | EEEE | SSSSS | TTTTT | DDDDD | 100101 |
// ------------------------------------------------------
//
// Vector clip high

void rsp_cop2_drc::vch()
{
	CACHE_VALUES();

	CLEAR_CARRY_FLAGS();
	CLEAR_COMPARE_FLAGS();
	CLEAR_CLIP1_FLAGS();
	CLEAR_ZERO_FLAGS();
	CLEAR_CLIP2_FLAGS();

<<<<<<< HEAD
	UINT32 vce = 0;
	for (int i = 0; i < 8; i++)
	{
		INT16 s1, s2;
=======
	uint32_t vce;
	for (int i = 0; i < 8; i++)
	{
		int16_t s1, s2;
>>>>>>> upstream/master
		GET_VS1(s1, i);
		GET_VS2(s2, i);

		if ((s1 ^ s2) < 0)
		{
			vce = (s1 + s2 == -1);
			SET_CARRY_FLAG(i);
			if (s2 < 0)
			{
				SET_CLIP2_FLAG(i);
			}

			if ((s1 + s2) <= 0)
			{
				SET_COMPARE_FLAG(i);
<<<<<<< HEAD
				m_vres[i] = -((UINT16)s2);
=======
				m_vres[i] = -((uint16_t)s2);
>>>>>>> upstream/master
			}
			else
			{
				m_vres[i] = s1;
			}

			if ((s1 + s2) != 0 && s1 != ~s2)
			{
				SET_ZERO_FLAG(i);
			}
		}//sign
		else
		{
			vce = 0;
			if (s2 < 0)
			{
				SET_COMPARE_FLAG(i);
			}
			if ((s1 - s2) >= 0)
			{
				SET_CLIP2_FLAG(i);
				m_vres[i] = s2;
			}
			else
			{
				m_vres[i] = s1;
			}

			if ((s1 - s2) != 0 && s1 != ~s2)
			{
				SET_ZERO_FLAG(i);
			}
		}
		if (vce)
		{
			SET_CLIP1_FLAG(i);
		}
		SET_ACCUM_L(m_vres[i], i);
	}
	WRITEBACK_RESULT();
}

static void cfunc_vch(void *param)
{
	((rsp_cop2 *)param)->vch();
}


// VCR
//
// 31       25  24     20      15      10      5        0
// ------------------------------------------------------
// | 010010 | 1 | EEEE | SSSSS | TTTTT | DDDDD | 100110 |
// ------------------------------------------------------
//
// Vector clip reverse

void rsp_cop2_drc::vcr()
{
	CACHE_VALUES();

	CLEAR_CARRY_FLAGS();
	CLEAR_COMPARE_FLAGS();
	CLEAR_CLIP1_FLAGS();
	CLEAR_ZERO_FLAGS();
	CLEAR_CLIP2_FLAGS();

	for (int i = 0; i < 8; i++)
	{
<<<<<<< HEAD
		INT16 s1, s2;
		GET_VS1(s1, i);
		GET_VS2(s2, i);

		if ((INT16)(s1 ^ s2) < 0)
=======
		int16_t s1, s2;
		GET_VS1(s1, i);
		GET_VS2(s2, i);

		if ((int16_t)(s1 ^ s2) < 0)
>>>>>>> upstream/master
		{
			if (s2 < 0)
			{
				SET_CLIP2_FLAG(i);
			}
			if ((s1 + s2) <= 0)
			{
<<<<<<< HEAD
				SET_ACCUM_L(~((UINT16)s2), i);
=======
				SET_ACCUM_L(~((uint16_t)s2), i);
>>>>>>> upstream/master
				SET_COMPARE_FLAG(i);
			}
			else
			{
				SET_ACCUM_L(s1, i);
			}
		}
		else
		{
			if (s2 < 0)
			{
				SET_COMPARE_FLAG(i);
			}
			if ((s1 - s2) >= 0)
			{
				SET_ACCUM_L(s2, i);
				SET_CLIP2_FLAG(i);
			}
			else
			{
				SET_ACCUM_L(s1, i);
			}
		}

		m_vres[i] = ACCUM_L(i);
	}
	WRITEBACK_RESULT();
}

static void cfunc_vcr(void *param)
{
	((rsp_cop2 *)param)->vcr();
}


// VMRG
//
// 31       25  24     20      15      10      5        0
// ------------------------------------------------------
// | 010010 | 1 | EEEE | SSSSS | TTTTT | DDDDD | 100111 |
// ------------------------------------------------------
//
// Merges two vectors according to compare flags

void rsp_cop2_drc::vmrg()
{
	CACHE_VALUES();

	for (int i = 0; i < 8; i++)
	{
<<<<<<< HEAD
		INT16 s1, s2;
=======
		int16_t s1, s2;
>>>>>>> upstream/master
		GET_VS1(s1, i);
		GET_VS2(s2, i);
		if (COMPARE_FLAG(i) != 0)
		{
			m_vres[i] = s1;
		}
		else
		{
			m_vres[i] = s2;
		}

		SET_ACCUM_L(m_vres[i], i);
	}
	WRITEBACK_RESULT();
}

static void cfunc_vmrg(void *param)
{
	((rsp_cop2 *)param)->vmrg();
}


// VAND
//
// 31       25  24     20      15      10      5        0
// ------------------------------------------------------
// | 010010 | 1 | EEEE | SSSSS | TTTTT | DDDDD | 101000 |
// ------------------------------------------------------
//
// Bitwise AND of two vector registers

void rsp_cop2_drc::vand()
{
	CACHE_VALUES();

	for (int i = 0; i < 8; i++)
	{
<<<<<<< HEAD
		UINT16 s1, s2;
=======
		uint16_t s1, s2;
>>>>>>> upstream/master
		GET_VS1(s1, i);
		GET_VS2(s2, i);
		m_vres[i] = s1 & s2;
		SET_ACCUM_L(m_vres[i], i);
	}
	WRITEBACK_RESULT();
}

static void cfunc_vand(void *param)
{
	((rsp_cop2 *)param)->vand();
}


// VNAND
//
// 31       25  24     20      15      10      5        0
// ------------------------------------------------------
// | 010010 | 1 | EEEE | SSSSS | TTTTT | DDDDD | 101001 |
// ------------------------------------------------------
//
// Bitwise NOT AND of two vector registers

void rsp_cop2_drc::vnand()
{
	CACHE_VALUES();

	for (int i = 0; i < 8; i++)
	{
<<<<<<< HEAD
		UINT16 s1, s2;
=======
		uint16_t s1, s2;
>>>>>>> upstream/master
		GET_VS1(s1, i);
		GET_VS2(s2, i);
		m_vres[i] = ~((s1 & s2));
		SET_ACCUM_L(m_vres[i], i);
	}
	WRITEBACK_RESULT();
}

static void cfunc_vnand(void *param)
{
	((rsp_cop2 *)param)->vnand();
}


// VOR
//
// 31       25  24     20      15      10      5        0
// ------------------------------------------------------
// | 010010 | 1 | EEEE | SSSSS | TTTTT | DDDDD | 101010 |
// ------------------------------------------------------
//
// Bitwise OR of two vector registers

void rsp_cop2_drc::vor()
{
	CACHE_VALUES();

	for (int i = 0; i < 8; i++)
	{
<<<<<<< HEAD
		UINT16 s1, s2;
=======
		uint16_t s1, s2;
>>>>>>> upstream/master
		GET_VS1(s1, i);
		GET_VS2(s2, i);
		m_vres[i] = s1 | s2;
		SET_ACCUM_L(m_vres[i], i);
	}
	WRITEBACK_RESULT();
}

static void cfunc_vor(void *param)
{
	((rsp_cop2 *)param)->vor();
}


// VNOR
//
// 31       25  24     20      15      10      5        0
// ------------------------------------------------------
// | 010010 | 1 | EEEE | SSSSS | TTTTT | DDDDD | 101011 |
// ------------------------------------------------------
//
// Bitwise NOT OR of two vector registers

void rsp_cop2_drc::vnor()
{
	CACHE_VALUES();

	for (int i = 0; i < 8; i++)
	{
<<<<<<< HEAD
		UINT16 s1, s2;
=======
		uint16_t s1, s2;
>>>>>>> upstream/master
		GET_VS1(s1, i);
		GET_VS2(s2, i);
		m_vres[i] = ~(s1 | s2);
		SET_ACCUM_L(m_vres[i], i);
	}
	WRITEBACK_RESULT();
}

static void cfunc_vnor(void *param)
{
	((rsp_cop2 *)param)->vnor();
}


// VXOR
//
// 31       25  24     20      15      10      5        0
// ------------------------------------------------------
// | 010010 | 1 | EEEE | SSSSS | TTTTT | DDDDD | 101100 |
// ------------------------------------------------------
//
// Bitwise XOR of two vector registers

void rsp_cop2_drc::vxor()
{
	CACHE_VALUES();

	for (int i = 0; i < 8; i++)
	{
<<<<<<< HEAD
		UINT16 s1, s2;
=======
		uint16_t s1, s2;
>>>>>>> upstream/master
		GET_VS1(s1, i);
		GET_VS2(s2, i);
		m_vres[i] = s1 ^ s2;
		SET_ACCUM_L(m_vres[i], i);
	}
	WRITEBACK_RESULT();
}

static void cfunc_vxor(void *param)
{
	((rsp_cop2 *)param)->vxor();
}


// VNXOR
//
// 31       25  24     20      15      10      5        0
// ------------------------------------------------------
// | 010010 | 1 | EEEE | SSSSS | TTTTT | DDDDD | 101101 |
// ------------------------------------------------------
//
// Bitwise NOT XOR of two vector registers

void rsp_cop2_drc::vnxor()
{
	CACHE_VALUES();

	for (int i = 0; i < 8; i++)
	{
<<<<<<< HEAD
		UINT16 s1, s2;
=======
		uint16_t s1, s2;
>>>>>>> upstream/master
		GET_VS1(s1, i);
		GET_VS2(s2, i);
		m_vres[i] = ~(s1 ^ s2);
		SET_ACCUM_L(m_vres[i], i);
	}
	WRITEBACK_RESULT();
}

static void cfunc_vnxor(void *param)
{
	((rsp_cop2 *)param)->vnxor();
}


// VRCP
//
// 31       25  24     20      15      10      5        0
// ------------------------------------------------------
// | 010010 | 1 | EEEE | SSSSS | ?FFFF | DDDDD | 110000 |
// ------------------------------------------------------
//
// Calculates reciprocal

void rsp_cop2_drc::vrcp()
{
	CACHE_VALUES();

<<<<<<< HEAD
	INT32 shifter = 0;
	INT32 rec = (INT16)(VREG_S(vs2reg, el & 7));
	INT32 datainput = (rec < 0) ? (-rec) : rec;
=======
	int32_t shifter = 0;
	int32_t rec = (int16_t)(VREG_S(vs2reg, el & 7));
	int32_t datainput = (rec < 0) ? (-rec) : rec;
>>>>>>> upstream/master
	if (datainput)
	{
		for (int i = 0; i < 32; i++)
		{
			if (datainput & (1 << ((~i) & 0x1f)))
			{
				shifter = i;
				break;
			}
		}
	}
	else
	{
		shifter = 0x10;
	}

<<<<<<< HEAD
	INT32 address = ((datainput << shifter) & 0x7fc00000) >> 22;
	INT32 fetchval = rsp_divtable[address];
	INT32 temp = (0x40000000 | (fetchval << 14)) >> ((~shifter) & 0x1f);
=======
	int32_t address = ((datainput << shifter) & 0x7fc00000) >> 22;
	int32_t fetchval = rsp_divtable[address];
	int32_t temp = (0x40000000 | (fetchval << 14)) >> ((~shifter) & 0x1f);
>>>>>>> upstream/master
	if (rec < 0)
	{
		temp = ~temp;
	}
	if (!rec)
	{
		temp = 0x7fffffff;
	}
	else if (rec == 0xffff8000)
	{
		temp = 0xffff0000;
	}
	rec = temp;

	m_reciprocal_res = rec;
	m_dp_allowed = 0;

<<<<<<< HEAD
	W_VREG_S(vdreg, vs1reg & 7) = (UINT16)rec;
=======
	W_VREG_S(vdreg, vs1reg & 7) = (uint16_t)rec;
>>>>>>> upstream/master
	for (int i = 0; i < 8; i++)
	{
		SET_ACCUM_L(VREG_S(vs2reg, VEC_EL_2(el, i)), i);
	}
}

static void cfunc_vrcp(void *param)
{
	((rsp_cop2 *)param)->vrcp();
}


// VRCPL
//
// 31       25  24     20      15      10      5        0
// ------------------------------------------------------
// | 010010 | 1 | EEEE | SSSSS | ?FFFF | DDDDD | 110001 |
// ------------------------------------------------------
//
// Calculates reciprocal low part

void rsp_cop2_drc::vrcpl()
{
	CACHE_VALUES();

<<<<<<< HEAD
	INT32 shifter = 0;
	INT32 rec = (INT16)VREG_S(vs2reg, el & 7);
	INT32 datainput = rec;
=======
	int32_t shifter = 0;
	int32_t rec = (int16_t)VREG_S(vs2reg, el & 7);
	int32_t datainput = rec;
>>>>>>> upstream/master

	if (m_dp_allowed)
	{
		rec = (rec & 0x0000ffff) | m_reciprocal_high;
		datainput = rec;

		if (rec < 0)
		{
			if (rec < -32768)
			{
				datainput = ~datainput;
			}
			else
			{
				datainput = -datainput;
			}
		}
	}
	else if (datainput < 0)
	{
		datainput = -datainput;

		shifter = 0x10;
	}

	if (datainput)
	{
		for (int i = 0; i < 32; i++)
		{
			if (datainput & (1 << ((~i) & 0x1f)))
			{
				shifter = i;
				break;
			}
		}
	}

<<<<<<< HEAD
	UINT32 address = (datainput << shifter) >> 22;
	INT32 fetchval = rsp_divtable[address & 0x1ff];
	INT32 temp = (0x40000000 | (fetchval << 14)) >> ((~shifter) & 0x1f);
=======
	uint32_t address = (datainput << shifter) >> 22;
	int32_t fetchval = rsp_divtable[address & 0x1ff];
	int32_t temp = (0x40000000 | (fetchval << 14)) >> ((~shifter) & 0x1f);
>>>>>>> upstream/master
	temp ^= rec >> 31;

	if (!rec)
	{
		temp = 0x7fffffff;
	}
	else if (rec == 0xffff8000)
	{
		temp = 0xffff0000;
	}
	rec = temp;

	m_reciprocal_res = rec;
	m_dp_allowed = 0;

<<<<<<< HEAD
	W_VREG_S(vdreg, vs1reg & 7) = (UINT16)rec;
=======
	W_VREG_S(vdreg, vs1reg & 7) = (uint16_t)rec;
>>>>>>> upstream/master

	for (int i = 0; i < 8; i++)
	{
		SET_ACCUM_L(VREG_S(vs2reg, VEC_EL_2(el, i)), i);
	}
}

static void cfunc_vrcpl(void *param)
{
	((rsp_cop2 *)param)->vrcpl();
}


// VRCPH
//
// 31       25  24     20      15      10      5        0
// ------------------------------------------------------
// | 010010 | 1 | EEEE | SSSSS | ?FFFF | DDDDD | 110010 |
// ------------------------------------------------------
//
// Calculates reciprocal high part

void rsp_cop2_drc::vrcph()
{
	CACHE_VALUES();

	m_reciprocal_high = (VREG_S(vs2reg, el & 7)) << 16;
	m_dp_allowed = 1;

	for (int i = 0; i < 8; i++)
	{
		SET_ACCUM_L(VREG_S(vs2reg, VEC_EL_2(el, i)), i);
	}

<<<<<<< HEAD
	W_VREG_S(vdreg, vs1reg & 7) = (INT16)(m_reciprocal_res >> 16);
=======
	W_VREG_S(vdreg, vs1reg & 7) = (int16_t)(m_reciprocal_res >> 16);
>>>>>>> upstream/master
}

static void cfunc_vrcph(void *param)
{
	((rsp_cop2 *)param)->vrcph();
}


// VMOV
//
// 31       25  24     20      15      10      5        0
// ------------------------------------------------------
// | 010010 | 1 | EEEE | SSSSS | ?FFFF | DDDDD | 110011 |
// ------------------------------------------------------
//
// Moves element from vector to destination vector

void rsp_cop2_drc::vmov()
{
	CACHE_VALUES();

	W_VREG_S(vdreg, vs1reg & 7) = VREG_S(vs2reg, el & 7);
	for (int i = 0; i < 8; i++)
	{
		SET_ACCUM_L(VREG_S(vs2reg, VEC_EL_2(el, i)), i);
	}
}

static void cfunc_vmov(void *param)
{
	((rsp_cop2 *)param)->vmov();
}


// VRSQ
//
// 31       25  24     20      15      10      5        0
// ------------------------------------------------------
// | 010010 | 1 | EEEE | SSSSS | ?FFFF | DDDDD | 110100 |
// ------------------------------------------------------
//
// Calculates reciprocal square-root

void rsp_cop2_drc::vrsq()
{
	CACHE_VALUES();

<<<<<<< HEAD
	INT32 shifter = 0;
	INT32 rec = (INT16)VREG_S(vs2reg, el & 7);
	INT32 datainput = (rec < 0) ? (-rec) : (rec);
=======
	int32_t shifter = 0;
	int32_t rec = (int16_t)VREG_S(vs2reg, el & 7);
	int32_t datainput = (rec < 0) ? (-rec) : (rec);
>>>>>>> upstream/master

	if (rec < 0)
	{
		if (rec < -32768)
		{
			datainput = ~datainput;
		}
		else
		{
			datainput = -datainput;
		}
	}

	if (datainput)
	{
		for (int i = 0; i < 32; i++)
		{
			if (datainput & (1 << ((~i) & 0x1f)))
			{
				shifter = i;
				break;
			}
		}
	}
	else
	{
		shifter = 0;
	}

<<<<<<< HEAD
	INT32 address = ((datainput << shifter) & 0x7fc00000) >> 22;
	address = ((address | 0x200) & 0x3fe) | (shifter & 1);

	INT32 fetchval = rsp_divtable[address];
	INT32 temp = (0x40000000 | (fetchval << 14)) >> (((~shifter) & 0x1f) >> 1);
=======
	int32_t address = ((datainput << shifter) & 0x7fc00000) >> 22;
	address = ((address | 0x200) & 0x3fe) | (shifter & 1);

	int32_t fetchval = rsp_divtable[address];
	int32_t temp = (0x40000000 | (fetchval << 14)) >> (((~shifter) & 0x1f) >> 1);
>>>>>>> upstream/master
	if (rec < 0)
	{
		temp = ~temp;
	}
	if (!rec)
	{
		temp = 0x7fffffff;
	}
	else if (rec == 0xffff8000)
	{
		temp = 0xffff0000;
	}
	rec = temp;

	if (rec < 0)
	{
		if (m_dp_allowed)
		{
			if (rec < -32768)
			{
				datainput = ~datainput;
			}
			else
			{
				datainput = -datainput;
			}
		}
		else
		{
			datainput = -datainput;
		}
	}

	if (datainput)
	{
		for (int i = 0; i < 32; i++)
		{
			if (datainput & (1 << ((~i) & 0x1f)))
			{
				shifter = i;
				break;
			}
		}
	}
	else
	{
		shifter = 0;
	}

	address = ((datainput << shifter) & 0x7fc00000) >> 22;
	address = ((address | 0x200) & 0x3fe) | (shifter & 1);

	fetchval = rsp_divtable[address];
	temp = (0x40000000 | (fetchval << 14)) >> (((~shifter) & 0x1f) >> 1);
	if (rec < 0)
	{
		temp = ~temp;
	}
	if (!rec)
	{
		temp = 0x7fff;
	}
	else if (rec == 0xffff8000)
	{
		temp = 0x0000;
	}
	rec = temp;

<<<<<<< HEAD
	W_VREG_S(vdreg, vs1reg & 7) = (UINT16)rec;
=======
	W_VREG_S(vdreg, vs1reg & 7) = (uint16_t)rec;
>>>>>>> upstream/master
	for (int i = 0; i < 8; i++)
	{
		SET_ACCUM_L(VREG_S(vs2reg, VEC_EL_2(el, i)), i);
	}
}

static void cfunc_vrsq(void *param)
{
	((rsp_cop2 *)param)->vrsq();
}


// VRSQL
//
// 31       25  24     20      15      10      5        0
// ------------------------------------------------------
// | 010010 | 1 | EEEE | SSSSS | ?FFFF | DDDDD | 110101 |
// ------------------------------------------------------
//
// Calculates reciprocal square-root low part

void rsp_cop2_drc::vrsql()
{
	CACHE_VALUES();

<<<<<<< HEAD
	INT32 shifter = 0;
	INT32 rec = (INT16)VREG_S(vs2reg, el & 7);
	INT32 datainput = rec;
=======
	int32_t shifter = 0;
	int32_t rec = (int16_t)VREG_S(vs2reg, el & 7);
	int32_t datainput = rec;
>>>>>>> upstream/master

	if (m_dp_allowed)
	{
		rec = (rec & 0x0000ffff) | m_reciprocal_high;
		datainput = rec;

		if (rec < 0)
		{
			if (rec < -32768)
			{
				datainput = ~datainput;
			}
			else
			{
				datainput = -datainput;
			}
		}
	}
	else if (datainput < 0)
	{
		datainput = -datainput;

		shifter = 0x10;
	}

	if (datainput)
	{
		for (int i = 0; i < 32; i++)
		{
			if (datainput & (1 << ((~i) & 0x1f)))
			{
				shifter = i;
				break;
			}
		}
	}

<<<<<<< HEAD
	INT32 address = ((datainput << shifter) & 0x7fc00000) >> 22;
	address = ((address | 0x200) & 0x3fe) | (shifter & 1);

	INT32 fetchval = rsp_divtable[address];
	INT32 temp = (0x40000000 | (fetchval << 14)) >> (((~shifter) & 0x1f) >> 1);
=======
	int32_t address = ((datainput << shifter) & 0x7fc00000) >> 22;
	address = ((address | 0x200) & 0x3fe) | (shifter & 1);

	int32_t fetchval = rsp_divtable[address];
	int32_t temp = (0x40000000 | (fetchval << 14)) >> (((~shifter) & 0x1f) >> 1);
>>>>>>> upstream/master
	temp ^= rec >> 31;

	if (!rec)
	{
		temp = 0x7fffffff;
	}
	else if (rec == 0xffff8000)
	{
		temp = 0xffff0000;
	}
	rec = temp;

	m_reciprocal_res = rec;
	m_dp_allowed = 0;

<<<<<<< HEAD
	W_VREG_S(vdreg, vs1reg & 7) = (UINT16)(rec & 0xffff);
=======
	W_VREG_S(vdreg, vs1reg & 7) = (uint16_t)(rec & 0xffff);
>>>>>>> upstream/master
	for (int i = 0; i < 8; i++)
	{
		SET_ACCUM_L(VREG_S(vs2reg, VEC_EL_2(el, i)), i);
	}
}

static void cfunc_vrsql(void *param)
{
	((rsp_cop2 *)param)->vrsql();
}


// VRSQH
//
// 31       25  24     20      15      10      5        0
// ------------------------------------------------------
// | 010010 | 1 | EEEE | SSSSS | ?FFFF | DDDDD | 110110 |
// ------------------------------------------------------
//
// Calculates reciprocal square-root high part

void rsp_cop2_drc::vrsqh()
{
	CACHE_VALUES();

	m_reciprocal_high = (VREG_S(vs2reg, el & 7)) << 16;
	m_dp_allowed = 1;

	for (int i = 0; i < 8; i++)
	{
		SET_ACCUM_L(VREG_S(vs2reg, VEC_EL_2(el, i)), i);
	}

<<<<<<< HEAD
	W_VREG_S(vdreg, vs1reg & 7) = (INT16)(m_reciprocal_res >> 16);  // store high part
=======
	W_VREG_S(vdreg, vs1reg & 7) = (int16_t)(m_reciprocal_res >> 16);  // store high part
>>>>>>> upstream/master
}

static void cfunc_vrsqh(void *param)
{
	((rsp_cop2 *)param)->vrsqh();
}


/*-------------------------------------------------
    generate_vector_opcode - generate code for a
    vector opcode
-------------------------------------------------*/

<<<<<<< HEAD
int rsp_cop2_drc::generate_vector_opcode(drcuml_block *block, rsp_device::compiler_state *compiler, const opcode_desc *desc)
{
	UINT32 op = desc->opptr.l[0];
=======
bool rsp_cop2_drc::generate_vector_opcode(drcuml_block *block, rsp_device::compiler_state *compiler, const opcode_desc *desc)
{
	uint32_t op = desc->opptr.l[0];
>>>>>>> upstream/master
	// Opcode legend:
	//    E = VS2 element type
	//    S = VS1, Source vector 1
	//    T = VS2, Source vector 2
	//    D = Destination vector

	switch (op & 0x3f)
	{
		case 0x00:      /* VMULF */
			UML_MOV(block, mem(&m_rspcop2_state->op), desc->opptr.l[0]);        // mov     [arg0],desc->opptr.l
			UML_CALLC(block, cfunc_vmulf, this);
<<<<<<< HEAD
			return TRUE;
=======
			return true;
>>>>>>> upstream/master

		case 0x01:      /* VMULU */
			UML_MOV(block, mem(&m_rspcop2_state->op), desc->opptr.l[0]);        // mov     [arg0],desc->opptr.l
			UML_CALLC(block, cfunc_vmulu, this);
<<<<<<< HEAD
			return TRUE;
=======
			return true;
>>>>>>> upstream/master

		case 0x04:      /* VMUDL */
			UML_MOV(block, mem(&m_rspcop2_state->op), desc->opptr.l[0]);        // mov     [arg0],desc->opptr.l
			UML_CALLC(block, cfunc_vmudl, this);
<<<<<<< HEAD
			return TRUE;
=======
			return true;
>>>>>>> upstream/master

		case 0x05:      /* VMUDM */
			UML_MOV(block, mem(&m_rspcop2_state->op), desc->opptr.l[0]);        // mov     [arg0],desc->opptr.l
			UML_CALLC(block, cfunc_vmudm, this);
<<<<<<< HEAD
			return TRUE;
=======
			return true;
>>>>>>> upstream/master

		case 0x06:      /* VMUDN */
			UML_MOV(block, mem(&m_rspcop2_state->op), desc->opptr.l[0]);        // mov     [arg0],desc->opptr.l
			UML_CALLC(block, cfunc_vmudn, this);
<<<<<<< HEAD
			return TRUE;
=======
			return true;
>>>>>>> upstream/master

		case 0x07:      /* VMUDH */
			UML_MOV(block, mem(&m_rspcop2_state->op), desc->opptr.l[0]);        // mov     [arg0],desc->opptr.l
			UML_CALLC(block, cfunc_vmudh, this);
<<<<<<< HEAD
			return TRUE;
=======
			return true;
>>>>>>> upstream/master

		case 0x08:      /* VMACF */
			UML_MOV(block, mem(&m_rspcop2_state->op), desc->opptr.l[0]);        // mov     [arg0],desc->opptr.l
			UML_CALLC(block, cfunc_vmacf, this);
<<<<<<< HEAD
			return TRUE;
=======
			return true;
>>>>>>> upstream/master

		case 0x09:      /* VMACU */
			UML_MOV(block, mem(&m_rspcop2_state->op), desc->opptr.l[0]);        // mov     [arg0],desc->opptr.l
			UML_CALLC(block, cfunc_vmacu, this);
<<<<<<< HEAD
			return TRUE;
=======
			return true;
>>>>>>> upstream/master

		case 0x0c:      /* VMADL */
			UML_MOV(block, mem(&m_rspcop2_state->op), desc->opptr.l[0]);        // mov     [arg0],desc->opptr.l
			UML_CALLC(block, cfunc_vmadl, this);
<<<<<<< HEAD
			return TRUE;
=======
			return true;
>>>>>>> upstream/master

		case 0x0d:      /* VMADM */
			UML_MOV(block, mem(&m_rspcop2_state->op), desc->opptr.l[0]);        // mov     [arg0],desc->opptr.l
			UML_CALLC(block, cfunc_vmadm, this);
<<<<<<< HEAD
			return TRUE;
=======
			return true;
>>>>>>> upstream/master

		case 0x0e:      /* VMADN */
			UML_MOV(block, mem(&m_rspcop2_state->op), desc->opptr.l[0]);        // mov     [arg0],desc->opptr.l
			UML_CALLC(block, cfunc_vmadn, this);
<<<<<<< HEAD
			return TRUE;
=======
			return true;
>>>>>>> upstream/master

		case 0x0f:      /* VMADH */
			UML_MOV(block, mem(&m_rspcop2_state->op), desc->opptr.l[0]);        // mov     [arg0],desc->opptr.l
			UML_CALLC(block, cfunc_vmadh, this);
<<<<<<< HEAD
			return TRUE;
=======
			return true;
>>>>>>> upstream/master

		case 0x10:      /* VADD */
			UML_MOV(block, mem(&m_rspcop2_state->op), desc->opptr.l[0]);        // mov     [arg0],desc->opptr.l
			UML_CALLC(block, cfunc_vadd, this);
<<<<<<< HEAD
			return TRUE;
=======
			return true;
>>>>>>> upstream/master

		case 0x11:      /* VSUB */
			UML_MOV(block, mem(&m_rspcop2_state->op), desc->opptr.l[0]);        // mov     [arg0],desc->opptr.l
			UML_CALLC(block, cfunc_vsub, this);
<<<<<<< HEAD
			return TRUE;
=======
			return true;
>>>>>>> upstream/master

		case 0x13:      /* VABS */
			UML_MOV(block, mem(&m_rspcop2_state->op), desc->opptr.l[0]);        // mov     [arg0],desc->opptr.l
			UML_CALLC(block, cfunc_vabs, this);
<<<<<<< HEAD
			return TRUE;
=======
			return true;
>>>>>>> upstream/master

		case 0x14:      /* VADDC */
			UML_MOV(block, mem(&m_rspcop2_state->op), desc->opptr.l[0]);        // mov     [arg0],desc->opptr.l
			UML_CALLC(block, cfunc_vaddc, this);
<<<<<<< HEAD
			return TRUE;
=======
			return true;
>>>>>>> upstream/master

		case 0x15:      /* VSUBC */
			UML_MOV(block, mem(&m_rspcop2_state->op), desc->opptr.l[0]);        // mov     [arg0],desc->opptr.l
			UML_CALLC(block, cfunc_vsubc, this);
<<<<<<< HEAD
			return TRUE;
=======
			return true;
>>>>>>> upstream/master

		case 0x16:      /* VADDB */
			UML_MOV(block, mem(&m_rspcop2_state->op), desc->opptr.l[0]);        // mov     [arg0],desc->opptr.l
			UML_CALLC(block, cfunc_vaddb, this);
<<<<<<< HEAD
			return TRUE;
=======
			return true;
>>>>>>> upstream/master

		case 0x17:      /* VSUBB (reserved, functionally identical to VADDB) */
			UML_MOV(block, mem(&m_rspcop2_state->op), desc->opptr.l[0]);        // mov     [arg0],desc->opptr.l
			UML_CALLC(block, cfunc_vaddb, this);
<<<<<<< HEAD
			return TRUE;
=======
			return true;
>>>>>>> upstream/master

		case 0x18:      /* VACCB (reserved, functionally identical to VADDB) */
			UML_MOV(block, mem(&m_rspcop2_state->op), desc->opptr.l[0]);        // mov     [arg0],desc->opptr.l
			UML_CALLC(block, cfunc_vaddb, this);
<<<<<<< HEAD
			return TRUE;
=======
			return true;
>>>>>>> upstream/master

		case 0x19:      /* VSUCB (reserved, functionally identical to VADDB) */
			UML_MOV(block, mem(&m_rspcop2_state->op), desc->opptr.l[0]);        // mov     [arg0],desc->opptr.l
			UML_CALLC(block, cfunc_vaddb, this);
<<<<<<< HEAD
			return TRUE;
=======
			return true;
>>>>>>> upstream/master

		case 0x1d:      /* VSAW */
			UML_MOV(block, mem(&m_rspcop2_state->op), desc->opptr.l[0]);        // mov     [arg0],desc->opptr.l
			UML_CALLC(block, cfunc_vsaw, this);
<<<<<<< HEAD
			return TRUE;
=======
			return true;
>>>>>>> upstream/master

		case 0x20:      /* VLT */
			UML_MOV(block, mem(&m_rspcop2_state->op), desc->opptr.l[0]);        // mov     [arg0],desc->opptr.l
			UML_CALLC(block, cfunc_vlt, this);
<<<<<<< HEAD
			return TRUE;
=======
			return true;
>>>>>>> upstream/master

		case 0x21:      /* VEQ */
			UML_MOV(block, mem(&m_rspcop2_state->op), desc->opptr.l[0]);        // mov     [arg0],desc->opptr.l
			UML_CALLC(block, cfunc_veq, this);
<<<<<<< HEAD
			return TRUE;
=======
			return true;
>>>>>>> upstream/master

		case 0x22:      /* VNE */
			UML_MOV(block, mem(&m_rspcop2_state->op), desc->opptr.l[0]);        // mov     [arg0],desc->opptr.l
			UML_CALLC(block, cfunc_vne, this);
<<<<<<< HEAD
			return TRUE;
=======
			return true;
>>>>>>> upstream/master

		case 0x23:      /* VGE */
			UML_MOV(block, mem(&m_rspcop2_state->op), desc->opptr.l[0]);        // mov     [arg0],desc->opptr.l
			UML_CALLC(block, cfunc_vge, this);
<<<<<<< HEAD
			return TRUE;
=======
			return true;
>>>>>>> upstream/master

		case 0x24:      /* VCL */
			UML_MOV(block, mem(&m_rspcop2_state->op), desc->opptr.l[0]);        // mov     [arg0],desc->opptr.l
			UML_CALLC(block, cfunc_vcl, this);
<<<<<<< HEAD
			return TRUE;
=======
			return true;
>>>>>>> upstream/master

		case 0x25:      /* VCH */
			UML_MOV(block, mem(&m_rspcop2_state->op), desc->opptr.l[0]);        // mov     [arg0],desc->opptr.l
			UML_CALLC(block, cfunc_vch, this);
<<<<<<< HEAD
			return TRUE;
=======
			return true;
>>>>>>> upstream/master

		case 0x26:      /* VCR */
			UML_MOV(block, mem(&m_rspcop2_state->op), desc->opptr.l[0]);        // mov     [arg0],desc->opptr.l
			UML_CALLC(block, cfunc_vcr, this);
<<<<<<< HEAD
			return TRUE;
=======
			return true;
>>>>>>> upstream/master

		case 0x27:      /* VMRG */
			UML_MOV(block, mem(&m_rspcop2_state->op), desc->opptr.l[0]);        // mov     [arg0],desc->opptr.l
			UML_CALLC(block, cfunc_vmrg, this);
<<<<<<< HEAD
			return TRUE;
=======
			return true;
>>>>>>> upstream/master

		case 0x28:      /* VAND */
			UML_MOV(block, mem(&m_rspcop2_state->op), desc->opptr.l[0]);        // mov     [arg0],desc->opptr.l
			UML_CALLC(block, cfunc_vand, this);
<<<<<<< HEAD
			return TRUE;
=======
			return true;
>>>>>>> upstream/master

		case 0x29:      /* VNAND */
			UML_MOV(block, mem(&m_rspcop2_state->op), desc->opptr.l[0]);        // mov     [arg0],desc->opptr.l
			UML_CALLC(block, cfunc_vnand, this);
<<<<<<< HEAD
			return TRUE;
=======
			return true;
>>>>>>> upstream/master

		case 0x2a:      /* VOR */
			UML_MOV(block, mem(&m_rspcop2_state->op), desc->opptr.l[0]);        // mov     [arg0],desc->opptr.l
			UML_CALLC(block, cfunc_vor, this);
<<<<<<< HEAD
			return TRUE;
=======
			return true;
>>>>>>> upstream/master

		case 0x2b:      /* VNOR */
			UML_MOV(block, mem(&m_rspcop2_state->op), desc->opptr.l[0]);        // mov     [arg0],desc->opptr.l
			UML_CALLC(block, cfunc_vnor, this);
<<<<<<< HEAD
			return TRUE;
=======
			return true;
>>>>>>> upstream/master

		case 0x2c:      /* VXOR */
			UML_MOV(block, mem(&m_rspcop2_state->op), desc->opptr.l[0]);        // mov     [arg0],desc->opptr.l
			UML_CALLC(block, cfunc_vxor, this);
<<<<<<< HEAD
			return TRUE;
=======
			return true;
>>>>>>> upstream/master

		case 0x2d:      /* VNXOR */
			UML_MOV(block, mem(&m_rspcop2_state->op), desc->opptr.l[0]);        // mov     [arg0],desc->opptr.l
			UML_CALLC(block, cfunc_vnxor, this);
<<<<<<< HEAD
			return TRUE;
=======
			return true;
>>>>>>> upstream/master

		case 0x30:      /* VRCP */
			UML_MOV(block, mem(&m_rspcop2_state->op), desc->opptr.l[0]);        // mov     [arg0],desc->opptr.l
			UML_CALLC(block, cfunc_vrcp, this);
<<<<<<< HEAD
			return TRUE;
=======
			return true;
>>>>>>> upstream/master

		case 0x31:      /* VRCPL */
			UML_MOV(block, mem(&m_rspcop2_state->op), desc->opptr.l[0]);        // mov     [arg0],desc->opptr.l
			UML_CALLC(block, cfunc_vrcpl, this);
<<<<<<< HEAD
			return TRUE;
=======
			return true;
>>>>>>> upstream/master

		case 0x32:      /* VRCPH */
			UML_MOV(block, mem(&m_rspcop2_state->op), desc->opptr.l[0]);        // mov     [arg0],desc->opptr.l
			UML_CALLC(block, cfunc_vrcph, this);
<<<<<<< HEAD
			return TRUE;
=======
			return true;
>>>>>>> upstream/master

		case 0x33:      /* VMOV */
			UML_MOV(block, mem(&m_rspcop2_state->op), desc->opptr.l[0]);        // mov     [arg0],desc->opptr.l
			UML_CALLC(block, cfunc_vmov, this);
<<<<<<< HEAD
			return TRUE;
=======
			return true;
>>>>>>> upstream/master

		case 0x34:      /* VRSQ */
			UML_MOV(block, mem(&m_rspcop2_state->op), desc->opptr.l[0]);         // mov     [arg0],desc->opptr.l
			UML_CALLC(block, cfunc_vrsq, this);
<<<<<<< HEAD
			return TRUE;
=======
			return true;
>>>>>>> upstream/master

		case 0x35:      /* VRSQL */
			UML_MOV(block, mem(&m_rspcop2_state->op), desc->opptr.l[0]);        // mov     [arg0],desc->opptr.l
			UML_CALLC(block, cfunc_vrsql, this);
<<<<<<< HEAD
			return TRUE;
=======
			return true;
>>>>>>> upstream/master

		case 0x36:      /* VRSQH */
			UML_MOV(block, mem(&m_rspcop2_state->op), desc->opptr.l[0]);        // mov     [arg0],desc->opptr.l
			UML_CALLC(block, cfunc_vrsqh, this);
<<<<<<< HEAD
			return TRUE;

		case 0x37:      /* VNOP */
		case 0x3F:      /* VNULL */
			return TRUE;
=======
			return true;

		case 0x37:      /* VNOP */
		case 0x3F:      /* VNULL */
			return true;
>>>>>>> upstream/master

		default:
			UML_MOV(block, mem(&m_rspcop2_state->op), desc->opptr.l[0]);        // mov     [arg0],desc->opptr.l
			UML_CALLC(block, unimplemented_opcode, &m_rsp);
<<<<<<< HEAD
			return FALSE;
=======
			return false;
>>>>>>> upstream/master
	}
}


/***************************************************************************
    Vector Flag Reading/Writing
***************************************************************************/

void rsp_cop2_drc::mfc2()
{
<<<<<<< HEAD
	UINT32 op = m_rspcop2_state->op;
	int el = (op >> 7) & 0xf;

	UINT16 b1 = VREG_B(VS1REG, (el+0) & 0xf);
	UINT16 b2 = VREG_B(VS1REG, (el+1) & 0xf);
	if (RTREG) RTVAL = (INT32)(INT16)((b1 << 8) | (b2));
=======
	uint32_t op = m_rspcop2_state->op;
	int el = (op >> 7) & 0xf;

	uint16_t b1 = VREG_B(VS1REG, (el+0) & 0xf);
	uint16_t b2 = VREG_B(VS1REG, (el+1) & 0xf);
	if (RTREG) RTVAL = (int32_t)(int16_t)((b1 << 8) | (b2));
>>>>>>> upstream/master
}

static void cfunc_mfc2(void *param)
{
	((rsp_cop2 *)param)->mfc2();
}

void rsp_cop2_drc::cfc2()
{
<<<<<<< HEAD
	UINT32 op = m_rspcop2_state->op;
=======
	uint32_t op = m_rspcop2_state->op;
>>>>>>> upstream/master
	if (RTREG)
	{
		switch(RDREG)
		{
			case 0:
				RTVAL = ((CARRY_FLAG(0) & 1) << 0) |
						((CARRY_FLAG(1) & 1) << 1) |
						((CARRY_FLAG(2) & 1) << 2) |
						((CARRY_FLAG(3) & 1) << 3) |
						((CARRY_FLAG(4) & 1) << 4) |
						((CARRY_FLAG(5) & 1) << 5) |
						((CARRY_FLAG(6) & 1) << 6) |
						((CARRY_FLAG(7) & 1) << 7) |
						((ZERO_FLAG(0) & 1) << 8) |
						((ZERO_FLAG(1) & 1) << 9) |
						((ZERO_FLAG(2) & 1) << 10) |
						((ZERO_FLAG(3) & 1) << 11) |
						((ZERO_FLAG(4) & 1) << 12) |
						((ZERO_FLAG(5) & 1) << 13) |
						((ZERO_FLAG(6) & 1) << 14) |
						((ZERO_FLAG(7) & 1) << 15);
				if (RTVAL & 0x8000) RTVAL |= 0xffff0000;
				break;
			case 1:
				RTVAL = ((COMPARE_FLAG(0) & 1) << 0) |
						((COMPARE_FLAG(1) & 1) << 1) |
						((COMPARE_FLAG(2) & 1) << 2) |
						((COMPARE_FLAG(3) & 1) << 3) |
						((COMPARE_FLAG(4) & 1) << 4) |
						((COMPARE_FLAG(5) & 1) << 5) |
						((COMPARE_FLAG(6) & 1) << 6) |
						((COMPARE_FLAG(7) & 1) << 7) |
						((CLIP2_FLAG(0) & 1) << 8) |
						((CLIP2_FLAG(1) & 1) << 9) |
						((CLIP2_FLAG(2) & 1) << 10) |
						((CLIP2_FLAG(3) & 1) << 11) |
						((CLIP2_FLAG(4) & 1) << 12) |
						((CLIP2_FLAG(5) & 1) << 13) |
						((CLIP2_FLAG(6) & 1) << 14) |
						((CLIP2_FLAG(7) & 1) << 15);
				if (RTVAL & 0x8000) RTVAL |= 0xffff0000;
				break;
			case 2:
				RTVAL = ((CLIP1_FLAG(0) & 1) << 0) |
						((CLIP1_FLAG(1) & 1) << 1) |
						((CLIP1_FLAG(2) & 1) << 2) |
						((CLIP1_FLAG(3) & 1) << 3) |
						((CLIP1_FLAG(4) & 1) << 4) |
						((CLIP1_FLAG(5) & 1) << 5) |
						((CLIP1_FLAG(6) & 1) << 6) |
						((CLIP1_FLAG(7) & 1) << 7);
				break;
		}
	}
}

static void cfunc_cfc2(void *param)
{
	((rsp_cop2 *)param)->cfc2();
}


void rsp_cop2_drc::mtc2()
{
<<<<<<< HEAD
	UINT32 op = m_rspcop2_state->op;
=======
	uint32_t op = m_rspcop2_state->op;
>>>>>>> upstream/master
	int el = (op >> 7) & 0xf;
	VREG_B(VS1REG, (el+0) & 0xf) = (RTVAL >> 8) & 0xff;
	VREG_B(VS1REG, (el+1) & 0xf) = (RTVAL >> 0) & 0xff;
}

static void cfunc_mtc2(void *param)
{
	((rsp_cop2 *)param)->mtc2();
}


void rsp_cop2_drc::ctc2()
{
<<<<<<< HEAD
	UINT32 op = m_rspcop2_state->op;
=======
	uint32_t op = m_rspcop2_state->op;
>>>>>>> upstream/master
	switch(RDREG)
	{
		case 0:
			CLEAR_CARRY_FLAGS();
			CLEAR_ZERO_FLAGS();
			m_vflag[0][0] = ((RTVAL >> 0) & 1) ? 0xffff : 0;
			m_vflag[0][1] = ((RTVAL >> 1) & 1) ? 0xffff : 0;
			m_vflag[0][2] = ((RTVAL >> 2) & 1) ? 0xffff : 0;
			m_vflag[0][3] = ((RTVAL >> 3) & 1) ? 0xffff : 0;
			m_vflag[0][4] = ((RTVAL >> 4) & 1) ? 0xffff : 0;
			m_vflag[0][5] = ((RTVAL >> 5) & 1) ? 0xffff : 0;
			m_vflag[0][6] = ((RTVAL >> 6) & 1) ? 0xffff : 0;
			m_vflag[0][7] = ((RTVAL >> 7) & 1) ? 0xffff : 0;
			if (RTVAL & (1 << 0))  { SET_CARRY_FLAG(0); }
			if (RTVAL & (1 << 1))  { SET_CARRY_FLAG(1); }
			if (RTVAL & (1 << 2))  { SET_CARRY_FLAG(2); }
			if (RTVAL & (1 << 3))  { SET_CARRY_FLAG(3); }
			if (RTVAL & (1 << 4))  { SET_CARRY_FLAG(4); }
			if (RTVAL & (1 << 5))  { SET_CARRY_FLAG(5); }
			if (RTVAL & (1 << 6))  { SET_CARRY_FLAG(6); }
			if (RTVAL & (1 << 7))  { SET_CARRY_FLAG(7); }
			m_vflag[3][0] = ((RTVAL >> 8) & 1) ? 0xffff : 0;
			m_vflag[3][1] = ((RTVAL >> 9) & 1) ? 0xffff : 0;
			m_vflag[3][2] = ((RTVAL >> 10) & 1) ? 0xffff : 0;
			m_vflag[3][3] = ((RTVAL >> 11) & 1) ? 0xffff : 0;
			m_vflag[3][4] = ((RTVAL >> 12) & 1) ? 0xffff : 0;
			m_vflag[3][5] = ((RTVAL >> 13) & 1) ? 0xffff : 0;
			m_vflag[3][6] = ((RTVAL >> 14) & 1) ? 0xffff : 0;
			m_vflag[3][7] = ((RTVAL >> 15) & 1) ? 0xffff : 0;
			if (RTVAL & (1 << 8))  { SET_ZERO_FLAG(0); }
			if (RTVAL & (1 << 9))  { SET_ZERO_FLAG(1); }
			if (RTVAL & (1 << 10)) { SET_ZERO_FLAG(2); }
			if (RTVAL & (1 << 11)) { SET_ZERO_FLAG(3); }
			if (RTVAL & (1 << 12)) { SET_ZERO_FLAG(4); }
			if (RTVAL & (1 << 13)) { SET_ZERO_FLAG(5); }
			if (RTVAL & (1 << 14)) { SET_ZERO_FLAG(6); }
			if (RTVAL & (1 << 15)) { SET_ZERO_FLAG(7); }
			break;
		case 1:
			CLEAR_COMPARE_FLAGS();
			CLEAR_CLIP2_FLAGS();
			m_vflag[1][0] = ((RTVAL >> 0) & 1) ? 0xffff : 0;
			m_vflag[1][1] = ((RTVAL >> 1) & 1) ? 0xffff : 0;
			m_vflag[1][2] = ((RTVAL >> 2) & 1) ? 0xffff : 0;
			m_vflag[1][3] = ((RTVAL >> 3) & 1) ? 0xffff : 0;
			m_vflag[1][4] = ((RTVAL >> 4) & 1) ? 0xffff : 0;
			m_vflag[1][5] = ((RTVAL >> 5) & 1) ? 0xffff : 0;
			m_vflag[1][6] = ((RTVAL >> 6) & 1) ? 0xffff : 0;
			m_vflag[1][7] = ((RTVAL >> 7) & 1) ? 0xffff : 0;
			if (RTVAL & (1 << 0)) { SET_COMPARE_FLAG(0); }
			if (RTVAL & (1 << 1)) { SET_COMPARE_FLAG(1); }
			if (RTVAL & (1 << 2)) { SET_COMPARE_FLAG(2); }
			if (RTVAL & (1 << 3)) { SET_COMPARE_FLAG(3); }
			if (RTVAL & (1 << 4)) { SET_COMPARE_FLAG(4); }
			if (RTVAL & (1 << 5)) { SET_COMPARE_FLAG(5); }
			if (RTVAL & (1 << 6)) { SET_COMPARE_FLAG(6); }
			if (RTVAL & (1 << 7)) { SET_COMPARE_FLAG(7); }
			m_vflag[4][0] = ((RTVAL >> 8) & 1) ? 0xffff : 0;
			m_vflag[4][1] = ((RTVAL >> 9) & 1) ? 0xffff : 0;
			m_vflag[4][2] = ((RTVAL >> 10) & 1) ? 0xffff : 0;
			m_vflag[4][3] = ((RTVAL >> 11) & 1) ? 0xffff : 0;
			m_vflag[4][4] = ((RTVAL >> 12) & 1) ? 0xffff : 0;
			m_vflag[4][5] = ((RTVAL >> 13) & 1) ? 0xffff : 0;
			m_vflag[4][6] = ((RTVAL >> 14) & 1) ? 0xffff : 0;
			m_vflag[4][7] = ((RTVAL >> 15) & 1) ? 0xffff : 0;
			if (RTVAL & (1 << 8))  { SET_CLIP2_FLAG(0); }
			if (RTVAL & (1 << 9))  { SET_CLIP2_FLAG(1); }
			if (RTVAL & (1 << 10)) { SET_CLIP2_FLAG(2); }
			if (RTVAL & (1 << 11)) { SET_CLIP2_FLAG(3); }
			if (RTVAL & (1 << 12)) { SET_CLIP2_FLAG(4); }
			if (RTVAL & (1 << 13)) { SET_CLIP2_FLAG(5); }
			if (RTVAL & (1 << 14)) { SET_CLIP2_FLAG(6); }
			if (RTVAL & (1 << 15)) { SET_CLIP2_FLAG(7); }
			break;
		case 2:
			CLEAR_CLIP1_FLAGS();
			m_vflag[2][0] = ((RTVAL >> 0) & 1) ? 0xffff : 0;
			m_vflag[2][1] = ((RTVAL >> 1) & 1) ? 0xffff : 0;
			m_vflag[2][2] = ((RTVAL >> 2) & 1) ? 0xffff : 0;
			m_vflag[2][3] = ((RTVAL >> 3) & 1) ? 0xffff : 0;
			m_vflag[2][4] = ((RTVAL >> 4) & 1) ? 0xffff : 0;
			m_vflag[2][5] = ((RTVAL >> 5) & 1) ? 0xffff : 0;
			m_vflag[2][6] = ((RTVAL >> 6) & 1) ? 0xffff : 0;
			m_vflag[2][7] = ((RTVAL >> 7) & 1) ? 0xffff : 0;
			if (RTVAL & (1 << 0)) { SET_CLIP1_FLAG(0); }
			if (RTVAL & (1 << 1)) { SET_CLIP1_FLAG(1); }
			if (RTVAL & (1 << 2)) { SET_CLIP1_FLAG(2); }
			if (RTVAL & (1 << 3)) { SET_CLIP1_FLAG(3); }
			if (RTVAL & (1 << 4)) { SET_CLIP1_FLAG(4); }
			if (RTVAL & (1 << 5)) { SET_CLIP1_FLAG(5); }
			if (RTVAL & (1 << 6)) { SET_CLIP1_FLAG(6); }
			if (RTVAL & (1 << 7)) { SET_CLIP1_FLAG(7); }
			break;
	}
}

static void cfunc_ctc2(void *param)
{
	((rsp_cop2 *)param)->ctc2();
}

/***************************************************************************
    COP2 Opcode Compilation
***************************************************************************/

<<<<<<< HEAD
int rsp_cop2_drc::generate_cop2(drcuml_block *block, rsp_device::compiler_state *compiler, const opcode_desc *desc)
{
	UINT32 op = desc->opptr.l[0];
	UINT8 opswitch = RSREG;
=======
bool rsp_cop2_drc::generate_cop2(drcuml_block *block, rsp_device::compiler_state *compiler, const opcode_desc *desc)
{
	uint32_t op = desc->opptr.l[0];
	uint8_t opswitch = RSREG;
>>>>>>> upstream/master

	switch (opswitch)
	{
		case 0x00:  /* MFCz */
			if (RTREG != 0)
			{
				UML_MOV(block, mem(&m_rspcop2_state->op), desc->opptr.l[0]);   // mov     [arg0],desc->opptr.l
				UML_CALLC(block, cfunc_mfc2, this);             // callc   mfc2
			}
<<<<<<< HEAD
			return TRUE;
=======
			return true;
>>>>>>> upstream/master

		case 0x02:  /* CFCz */
			if (RTREG != 0)
			{
				UML_MOV(block, mem(&m_rspcop2_state->op), desc->opptr.l[0]);   // mov     [arg0],desc->opptr.l
				UML_CALLC(block, cfunc_cfc2, this);             // callc   cfc2
			}
<<<<<<< HEAD
			return TRUE;
=======
			return true;
>>>>>>> upstream/master

		case 0x04:  /* MTCz */
			UML_MOV(block, mem(&m_rspcop2_state->op), desc->opptr.l[0]);   // mov     [arg0],desc->opptr.l
			UML_CALLC(block, cfunc_mtc2, this);             // callc   mtc2
<<<<<<< HEAD
			return TRUE;
=======
			return true;
>>>>>>> upstream/master

		case 0x06:  /* CTCz */
			UML_MOV(block, mem(&m_rspcop2_state->op), desc->opptr.l[0]);   // mov     [arg0],desc->opptr.l
			UML_CALLC(block, cfunc_ctc2, this);             // callc   ctc2
<<<<<<< HEAD
			return TRUE;
=======
			return true;
>>>>>>> upstream/master

		case 0x10: case 0x11: case 0x12: case 0x13: case 0x14: case 0x15: case 0x16: case 0x17:
		case 0x18: case 0x19: case 0x1a: case 0x1b: case 0x1c: case 0x1d: case 0x1e: case 0x1f:
			return generate_vector_opcode(block, compiler, desc);
	}
<<<<<<< HEAD
	return FALSE;
=======
	return false;
>>>>>>> upstream/master
}
