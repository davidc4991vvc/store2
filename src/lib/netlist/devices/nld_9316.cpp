// license:GPL-2.0+
// copyright-holders:Couriersud
/*
 * nld_9316.c
 *
 */

#include "nld_9316.h"
<<<<<<< HEAD

#define MAXCNT 15

NETLIB_NAMESPACE_DEVICES_START()

NETLIB_START(9316)
{
	register_sub("subABCD", subABCD);
	sub.m_ABCD = &subABCD;
	register_sub("sub", sub);

	register_subalias("CLK", sub.m_CLK);

	register_input("ENP", m_ENP);
	register_input("ENT", m_ENT);
	register_input("CLRQ", m_CLRQ);
	register_input("LOADQ", m_LOADQ);

	register_subalias("A", subABCD.m_A);
	register_subalias("B", subABCD.m_B);
	register_subalias("C", subABCD.m_C);
	register_subalias("D", subABCD.m_D);

	register_subalias("QA", sub.m_QA);
	register_subalias("QB", sub.m_QB);
	register_subalias("QC", sub.m_QC);
	register_subalias("QD", sub.m_QD);
	register_subalias("RC", sub.m_RC);

}

NETLIB_RESET(9316)
{
	sub.do_reset();
	subABCD.do_reset();
}

NETLIB_START(9316_subABCD)
{
	register_input("A", m_A);
	register_input("B", m_B);
	register_input("C", m_C);
	register_input("D", m_D);

}

NETLIB_RESET(9316_subABCD)
{
#if 0
	m_A.inactivate();
	m_B.inactivate();
	m_C.inactivate();
	m_D.inactivate();
#endif
}

NETLIB_UPDATE(9316_subABCD)
{
}

NETLIB_START(9316_sub)
{
	register_input("CLK", m_CLK);

	register_output("QA", m_QA);
	register_output("QB", m_QB);
	register_output("QC", m_QC);
	register_output("QD", m_QD);
	register_output("RC", m_RC);

	save(NLNAME(m_cnt));
	save(NLNAME(m_loadq));
	save(NLNAME(m_ent));
}

NETLIB_RESET(9316_sub)
{
	m_CLK.set_state(logic_t::STATE_INP_LH);
	m_cnt = 0;
	m_loadq = 1;
	m_ent = 1;
}

NETLIB_UPDATE(9316_sub)
{
	if (m_loadq)
	{
		switch (m_cnt)
		{
			case MAXCNT - 1:
				m_cnt = MAXCNT;
				OUTLOGIC(m_RC, m_ent, NLTIME_FROM_NS(27));
				OUTLOGIC(m_QA, 1, NLTIME_FROM_NS(20));
				break;
			case MAXCNT:
				OUTLOGIC(m_RC, 0, NLTIME_FROM_NS(27));
				m_cnt = 0;
				update_outputs_all(m_cnt, NLTIME_FROM_NS(20));
				break;
			default:
				m_cnt++;
				update_outputs(m_cnt);
				break;
		}
	}
	else
	{
		m_cnt = m_ABCD->read_ABCD();
		OUTLOGIC(m_RC, m_ent & (m_cnt == MAXCNT), NLTIME_FROM_NS(27));
		update_outputs_all(m_cnt, NLTIME_FROM_NS(22));
	}
}

NETLIB_UPDATE(9316)
{
	sub.m_loadq = INPLOGIC(m_LOADQ);
	sub.m_ent = INPLOGIC(m_ENT);
	const netlist_sig_t clrq = INPLOGIC(m_CLRQ);

	if (((sub.m_loadq ^ 1) | (sub.m_ent & INPLOGIC(m_ENP))) & clrq)
	{
		sub.m_CLK.activate_lh();
		OUTLOGIC(sub.m_RC, sub.m_ent & (sub.m_cnt == MAXCNT), NLTIME_FROM_NS(27));
	}
	else
	{
		sub.m_CLK.inactivate();
		if (!clrq && (sub.m_cnt>0))
		{
			sub.update_outputs_all(0, NLTIME_FROM_NS(36));
			sub.m_cnt = 0;
			//return;
		}
		OUTLOGIC(sub.m_RC, sub.m_ent & (sub.m_cnt == MAXCNT), NLTIME_FROM_NS(27));
	}
}

inline NETLIB_FUNC_VOID(9316_sub, update_outputs_all, (const UINT8 cnt, const netlist_time out_delay))
{
	OUTLOGIC(m_QA, (cnt >> 0) & 1, out_delay);
	OUTLOGIC(m_QB, (cnt >> 1) & 1, out_delay);
	OUTLOGIC(m_QC, (cnt >> 2) & 1, out_delay);
	OUTLOGIC(m_QD, (cnt >> 3) & 1, out_delay);
}

inline NETLIB_FUNC_VOID(9316_sub, update_outputs, (const UINT8 cnt))
{
	/* static */ const netlist_time out_delay = NLTIME_FROM_NS(20);
#if 0
//    for (int i=0; i<4; i++)
//        OUTLOGIC(m_Q[i], (cnt >> i) & 1, delay[i]);
	OUTLOGIC(m_QA, (cnt >> 0) & 1, out_delay);
	OUTLOGIC(m_QB, (cnt >> 1) & 1, out_delay);
	OUTLOGIC(m_QC, (cnt >> 2) & 1, out_delay);
	OUTLOGIC(m_QD, (cnt >> 3) & 1, out_delay);
#else
	if ((cnt & 1) == 1)
		OUTLOGIC(m_QA, 1, out_delay);
	else
	{
		OUTLOGIC(m_QA, 0, out_delay);
		switch (cnt)
		{
		case 0x00:
			OUTLOGIC(m_QB, 0, out_delay);
			OUTLOGIC(m_QC, 0, out_delay);
			OUTLOGIC(m_QD, 0, out_delay);
			break;
		case 0x02:
		case 0x06:
		case 0x0A:
		case 0x0E:
			OUTLOGIC(m_QB, 1, out_delay);
			break;
		case 0x04:
		case 0x0C:
			OUTLOGIC(m_QB, 0, out_delay);
			OUTLOGIC(m_QC, 1, out_delay);
			break;
		case 0x08:
			OUTLOGIC(m_QB, 0, out_delay);
			OUTLOGIC(m_QC, 0, out_delay);
			OUTLOGIC(m_QD, 1, out_delay);
			break;
		}

	}
#endif
}

NETLIB_START(9316_dip)
{
	NETLIB_NAME(9316)::start();

	register_subalias("1", m_CLRQ);
	register_subalias("2", sub.m_CLK);
	register_subalias("3", subABCD.m_A);
	register_subalias("4", subABCD.m_B);
	register_subalias("5", subABCD.m_C);
	register_subalias("6", subABCD.m_D);
	register_subalias("7", m_ENP);
	// register_subalias("8", ); --> GND

	register_subalias("9", m_LOADQ);
	register_subalias("10", m_ENT);
	register_subalias("11", sub.m_QD);
	register_subalias("12", sub.m_QC);
	register_subalias("13", sub.m_QB);
	register_subalias("14", sub.m_QA);
	register_subalias("15", sub.m_RC);
	// register_subalias("16", ); --> VCC
}

NETLIB_UPDATE(9316_dip)
{
	NETLIB_NAME(9316)::update();
}

NETLIB_RESET(9316_dip)
{
	NETLIB_NAME(9316)::reset();
}

NETLIB_NAMESPACE_DEVICES_END()
=======
#include "../nl_base.h"

namespace netlist
{
	namespace devices
	{

	static constexpr const unsigned MAXCNT = 15;

	NETLIB_OBJECT(9316)
	{
		NETLIB_CONSTRUCTOR(9316)
		, m_CLK(*this, "CLK", NETLIB_DELEGATE(9316, clk))
		, m_ENT(*this, "ENT")
		, m_LOADQ(*this, "LOADQ")
		, m_cnt(*this, "m_cnt", 0)
		, m_ENP(*this, "ENP")
		, m_CLRQ(*this, "CLRQ")
		, m_A(*this, "A", NETLIB_DELEGATE(9316, noop))
		, m_B(*this, "B", NETLIB_DELEGATE(9316, noop))
		, m_C(*this, "C", NETLIB_DELEGATE(9316, noop))
		, m_D(*this, "D", NETLIB_DELEGATE(9316, noop))
		, m_Q(*this, {{ "QA", "QB", "QC", "QD" }})
		, m_RC(*this, "RC")
		{
		}

	private:
		NETLIB_RESETI();
		NETLIB_UPDATEI();
		NETLIB_HANDLERI(clk);
		NETLIB_HANDLERI(noop) { }

		logic_input_t m_CLK;

		logic_input_t m_ENT;
		logic_input_t m_LOADQ;

		state_var<unsigned> m_cnt;

		logic_input_t m_ENP;
		logic_input_t m_CLRQ;

		logic_input_t m_A;
		logic_input_t m_B;
		logic_input_t m_C;
		logic_input_t m_D;

		object_array_t<logic_output_t, 4> m_Q;
		logic_output_t m_RC;


	private:
		//inline void update_outputs_all(const unsigned &cnt, const netlist_time &out_delay) noexcept
		inline void update_outputs_all(const unsigned &cnt, const netlist_time &out_delay) noexcept
		{
			m_Q[0].push((cnt >> 0) & 1, out_delay);
			m_Q[1].push((cnt >> 1) & 1, out_delay);
			m_Q[2].push((cnt >> 2) & 1, out_delay);
			m_Q[3].push((cnt >> 3) & 1, out_delay);
		}
	};

	NETLIB_OBJECT_DERIVED(9316_dip, 9316)
	{
		NETLIB_CONSTRUCTOR_DERIVED(9316_dip, 9316)
		{
			register_subalias("1", "CLRQ");
			register_subalias("2", "CLK");
			register_subalias("3", "A");
			register_subalias("4", "B");
			register_subalias("5", "C");
			register_subalias("6", "D");
			register_subalias("7", "ENP");
			// register_subalias("8", "); -. GND

			register_subalias("9", "LOADQ");
			register_subalias("10", "ENT");
			register_subalias("11", "QD");
			register_subalias("12", "QC");
			register_subalias("13", "QB");
			register_subalias("14", "QA");
			register_subalias("15", "RC");
			// register_subalias("16", ); -. VCC
		}
	};

	NETLIB_RESET(9316)
	{
		m_CLK.set_state(logic_t::STATE_INP_LH);
		m_cnt = 0;
	}

	NETLIB_HANDLER(9316, clk)
	{
		if (m_LOADQ())
		{
			++m_cnt &= MAXCNT;
			//m_RC.push(m_ENT() && (m_cnt == MAXCNT), NLTIME_FROM_NS(27));
			if (m_cnt == MAXCNT)
			{
				m_RC.push(m_ENT(), NLTIME_FROM_NS(27));
				update_outputs_all(MAXCNT, NLTIME_FROM_NS(20));
			}
			else if (m_cnt == 0)
			{
				m_RC.push(0, NLTIME_FROM_NS(27));
				update_outputs_all(0, NLTIME_FROM_NS(20));
			}
			else
				update_outputs_all(m_cnt, NLTIME_FROM_NS(20));
		}
		else
		{
			m_cnt = (m_D() << 3) | (m_C() << 2) | (m_B() << 1) | (m_A() << 0);
			m_RC.push(m_ENT() && (m_cnt == MAXCNT), NLTIME_FROM_NS(27));
			update_outputs_all(m_cnt, NLTIME_FROM_NS(22));
		}
	}

	NETLIB_UPDATE(9316)
	{
		const netlist_sig_t CLRQ(m_CLRQ());
		const netlist_sig_t ENT(m_ENT());

		if (((m_LOADQ() ^ 1) || (ENT && m_ENP())) && CLRQ)
		{
			m_CLK.activate_lh();
		}
		else
		{
			m_CLK.inactivate();
			if (!CLRQ && (m_cnt>0))
			{
				m_cnt = 0;
				update_outputs_all(m_cnt, NLTIME_FROM_NS(36));
			}
		}
		m_RC.push(ENT && (m_cnt == MAXCNT), NLTIME_FROM_NS(27));
	}


	NETLIB_DEVICE_IMPL(9316)
	NETLIB_DEVICE_IMPL(9316_dip)

	} //namespace devices
} // namespace netlist
>>>>>>> upstream/master
