// license:GPL-2.0+
// copyright-holders:Couriersud
/*
<<<<<<< HEAD
 * nld_7493.c
=======
 * nld_7493.cpp
>>>>>>> upstream/master
 *
 */

#include "nld_7493.h"
<<<<<<< HEAD
#include "nl_setup.h"

NETLIB_NAMESPACE_DEVICES_START()

NETLIB_START(7493)
{
	register_sub("A", A);
	register_sub("B", B);
	register_sub("C", C);
	register_sub("D", D);

	register_subalias("CLKA", A.m_I);
	register_subalias("CLKB", B.m_I);
	register_input("R1",  m_R1);
	register_input("R2",  m_R2);

	register_subalias("QA", A.m_Q);
	register_subalias("QB", B.m_Q);
	register_subalias("QC", C.m_Q);
	register_subalias("QD", D.m_Q);

	connect_late(C.m_I, B.m_Q);
	connect_late(D.m_I, C.m_Q);
}

NETLIB_RESET(7493)
{
	A.do_reset();
	B.do_reset();
	C.do_reset();
	D.do_reset();
}

NETLIB_START(7493ff)
{
	register_input("CLK", m_I);
	register_output("Q", m_Q);

	save(NLNAME(m_reset));
	save(NLNAME(m_state));
}

NETLIB_RESET(7493ff)
{
	m_reset = 1;
	m_state = 0;
	m_I.set_state(logic_t::STATE_INP_HL);
}

NETLIB_UPDATE(7493ff)
{
	const netlist_time out_delay = NLTIME_FROM_NS(18);
	if (m_reset != 0)
	{
		m_state ^= 1;
		OUTLOGIC(m_Q, m_state, out_delay);
	}
}

NETLIB_UPDATE(7493)
{
	const netlist_sig_t r = INPLOGIC(m_R1) & INPLOGIC(m_R2);

	if (r)
	{
		A.m_I.inactivate();
		B.m_I.inactivate();
		OUTLOGIC(A.m_Q, 0, NLTIME_FROM_NS(40));
		OUTLOGIC(B.m_Q, 0, NLTIME_FROM_NS(40));
		OUTLOGIC(C.m_Q, 0, NLTIME_FROM_NS(40));
		OUTLOGIC(D.m_Q, 0, NLTIME_FROM_NS(40));
		A.m_reset = B.m_reset = C.m_reset = D.m_reset = 0;
		A.m_state = B.m_state = C.m_state = D.m_state = 0;
	}
	else
	{
		A.m_I.activate_hl();
		B.m_I.activate_hl();
		A.m_reset = B.m_reset = C.m_reset = D.m_reset = 1;
	}
}

NETLIB_START(7493_dip)
{
	NETLIB_NAME(7493)::start();

	register_subalias("1", B.m_I);
	register_subalias("2", m_R1);
	register_subalias("3", m_R2);

	// register_subalias("4", ); --> NC
	// register_subalias("5", ); --> VCC
	// register_subalias("6", ); --> NC
	// register_subalias("7", ); --> NC

	register_subalias("8", C.m_Q);
	register_subalias("9", B.m_Q);
	// register_subalias("10", ); --> GND
	register_subalias("11", D.m_Q);
	register_subalias("12", A.m_Q);
	// register_subalias("13", ); --> NC
	register_subalias("14", A.m_I);
}


NETLIB_UPDATE(7493_dip)
{
	NETLIB_NAME(7493)::update();
}

NETLIB_RESET(7493_dip)
{
	NETLIB_NAME(7493)::reset();
}

NETLIB_NAMESPACE_DEVICES_END()
=======
#include "../nl_base.h"

namespace netlist
{
	namespace devices
	{

	static constexpr netlist_time out_delay = NLTIME_FROM_NS(18);
	static constexpr netlist_time out_delay2 = NLTIME_FROM_NS(36);
	static constexpr netlist_time out_delay3 = NLTIME_FROM_NS(54);

	NETLIB_OBJECT(7493)
	{
		NETLIB_CONSTRUCTOR(7493)
		, m_R1(*this, "R1")
		, m_R2(*this, "R2")
		, m_reset(*this, "_m_reset", 0)
		, m_a(*this, "_m_a", 0)
		, m_bcd(*this, "_m_b", 0)
		, m_CLKA(*this, "CLKA", NETLIB_DELEGATE(7493, updA))
		, m_CLKB(*this, "CLKB", NETLIB_DELEGATE(7493, updB))
		, m_QA(*this, "QA")
		, m_QB(*this, "QB")
		, m_QC(*this, "QC")
		, m_QD(*this, "QD")
		{
		}

	private:
		NETLIB_RESETI();
		NETLIB_UPDATEI();

		NETLIB_HANDLERI(updA)
		{
			if (m_reset)
			{
				m_a ^= 1;
				m_QA.push(m_a, out_delay);
			}
		}

		NETLIB_HANDLERI(updB)
		{
			if (m_reset)
			{
				++m_bcd &= static_cast<std::uint8_t>(0x07);
				m_QD.push((m_bcd >> 2) & 1, out_delay3);
				m_QC.push((m_bcd >> 1) & 1, out_delay2);
				m_QB.push(m_bcd & 1, out_delay);
			}
		}

		logic_input_t m_R1;
		logic_input_t m_R2;

		state_var_sig m_reset;
		state_var_sig m_a;
		state_var_sig m_bcd;

		logic_input_t m_CLKA;
		logic_input_t m_CLKB;

		logic_output_t m_QA;
		logic_output_t m_QB;
		logic_output_t m_QC;
		logic_output_t m_QD;
	};

	NETLIB_OBJECT_DERIVED(7493_dip, 7493)
	{
		NETLIB_CONSTRUCTOR_DERIVED(7493_dip, 7493)
		{
			register_subalias("1", "CLKB");
			register_subalias("2", "R1");
			register_subalias("3", "R2");

			// register_subalias("4", ); --> NC
			// register_subalias("5", ); --> VCC
			// register_subalias("6", ); --> NC
			// register_subalias("7", ); --> NC

			register_subalias("8", "QC");
			register_subalias("9", "QB");
			// register_subalias("10", ); -. GND
			register_subalias("11", "QD");
			register_subalias("12", "QA");
			// register_subalias("13", ); -. NC
			register_subalias("14", "CLKA");
		}
	};

	NETLIB_RESET(7493)
	{
		m_reset = 1;
		m_a = m_bcd = 0;
		m_CLKA.set_state(logic_t::STATE_INP_HL);
		m_CLKB.set_state(logic_t::STATE_INP_HL);
	}

	NETLIB_UPDATE(7493)
	{
		m_reset = (m_R1() & m_R2()) ^ 1;

		if (m_reset)
		{
			m_CLKA.activate_hl();
			m_CLKB.activate_hl();
		}
		else
		{
			m_CLKA.inactivate();
			m_CLKB.inactivate();
			m_QA.push_force(0, NLTIME_FROM_NS(40));
			m_QB.push_force(0, NLTIME_FROM_NS(40));
			m_QC.push_force(0, NLTIME_FROM_NS(40));
			m_QD.push_force(0, NLTIME_FROM_NS(40));
			m_a = m_bcd = 0;
		}
	}

	NETLIB_DEVICE_IMPL(7493)
	NETLIB_DEVICE_IMPL(7493_dip)

	} //namespace devices
} // namespace netlist
>>>>>>> upstream/master
