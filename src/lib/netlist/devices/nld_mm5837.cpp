// license:GPL-2.0+
// copyright-holders:Couriersud
/*
 * nld_MM5837.c
 *
 */

<<<<<<< HEAD
#include <solver/nld_solver.h>
#include "nld_mm5837.h"
#include "nl_setup.h"

#define R_LOW (1000)
#define R_HIGH (1000)

NETLIB_NAMESPACE_DEVICES_START()

NETLIB_START(MM5837_dip)
{
	/* clock */
	register_output("Q", m_Q);
	register_input("FB", m_feedback);
	m_inc = netlist_time::from_hz(56000);
	connect_late(m_feedback, m_Q);

	/* output */
	register_sub("RV", m_RV);
	register_terminal("_RV1", m_RV.m_P);
	register_terminal("_RV2", m_RV.m_N);
	register_output("_Q", m_V0);
	connect_late(m_RV.m_N, m_V0);

	/* device */
	register_input("1", m_VDD);
	register_input("2", m_VGG);
	register_subalias("3", m_RV.m_P);
	register_input("4", m_VSS);

	save(NLNAME(m_shift));
}

NETLIB_RESET(MM5837_dip)
{
	m_V0.initial(0.0);
	m_RV.do_reset();
	m_RV.set(NL_FCONST(1.0) / R_LOW, 0.0, 0.0);

	m_shift = 0x1ffff;
	m_is_timestep = m_RV.m_P.net().as_analog().solver()->is_timestep();
}

NETLIB_UPDATE(MM5837_dip)
{
	OUTLOGIC(m_Q, !m_Q.net().as_logic().new_Q(), m_inc  );

	/* shift register
	 *
	 * 17 bits, bits 17 & 14 feed back to input
	 *
	 */

	const UINT32 last_state = m_shift & 0x01;
	/* shift */
	m_shift = (m_shift >> 1) | (((m_shift & 0x01) ^ ((m_shift >> 3) & 0x01)) << 16);
	const UINT32 state = m_shift & 0x01;

	if (state != last_state)
	{
		const nl_double R = state ? R_HIGH : R_LOW;
		const nl_double V = state ? INPANALOG(m_VDD) : INPANALOG(m_VSS);

		// We only need to update the net first if this is a time stepping net
		if (m_is_timestep)
			m_RV.update_dev();
		m_RV.set(NL_FCONST(1.0) / R, V, 0.0);
		m_RV.m_P.schedule_after(NLTIME_FROM_NS(1));
	}

}



NETLIB_NAMESPACE_DEVICES_END()
=======
#include "nld_mm5837.h"
#include "../solver/nld_matrix_solver.h"
#include "../analog/nlid_twoterm.h"

#define R_LOW (1000.0)
#define R_HIGH (1000.0)

namespace netlist
{
	namespace devices
	{
	NETLIB_OBJECT(MM5837_dip)
	{
		NETLIB_CONSTRUCTOR(MM5837_dip)
		, m_RV(*this, "_RV")
		, m_VDD(*this, "1")
		, m_VGG(*this, "2")
		, m_VSS(*this, "4")
		, m_FREQ(*this, "FREQ", 24000)
		/* clock */
		, m_feedback(*this, "_FB")
		, m_Q(*this, "_Q")
		, m_inc(netlist_time::from_hz(24000))
		, m_shift(*this, "m_shift", 0)
		, m_is_timestep(false)
		{
			connect(m_feedback, m_Q);

			/* output */
			//register_term("_RV1", m_RV.m_P);
			//register_term("_RV2", m_RV.m_N);
			connect(m_RV.m_N, m_VDD);

			/* device */
			register_subalias("3", m_RV.m_P);
		}

		NETLIB_RESETI();
		NETLIB_UPDATEI();
		NETLIB_UPDATE_PARAMI();

	protected:
		analog::NETLIB_SUB(twoterm) m_RV;
		analog_input_t m_VDD;
		analog_input_t m_VGG;
		analog_input_t m_VSS;
		param_double_t m_FREQ;

		/* clock stage */
		logic_input_t m_feedback;
		logic_output_t m_Q;
		netlist_time m_inc;

		/* state */
		state_var_u32 m_shift;

		/* cache */
		bool m_is_timestep;
	};

	NETLIB_RESET(MM5837_dip)
	{
		//m_V0.initial(0.0);
		//m_RV.do_reset();
		m_RV.set(NL_FCONST(1.0) / R_LOW, 0.0, 0.0);
		m_inc = netlist_time::from_double(1.0 / m_FREQ());
		if (m_FREQ() < 24000 || m_FREQ() > 56000)
			log().warning(MW_1_FREQUENCY_OUTSIDE_OF_SPECS_1, m_FREQ());

		m_shift = 0x1ffff;
		m_is_timestep = m_RV.m_P.net().solver()->is_timestep();
	}

	NETLIB_UPDATE_PARAM(MM5837_dip)
	{
		m_inc = netlist_time::from_double(1.0 / m_FREQ());
		if (m_FREQ() < 24000 || m_FREQ() > 56000)
			log().warning(MW_1_FREQUENCY_OUTSIDE_OF_SPECS_1, m_FREQ());
	}

	NETLIB_UPDATE(MM5837_dip)
	{
		m_Q.push(!m_feedback(), m_inc);

		/* shift register
		 *
		 * 17 bits, bits 17 & 14 feed back to input
		 *
		 */

		const auto last_state = m_shift & 0x01;
		/* shift */
		m_shift = (m_shift >> 1) | (((m_shift & 0x01) ^ ((m_shift >> 3) & 0x01)) << 16);
		const auto state = m_shift & 0x01;

		if (state != last_state)
		{
			const nl_double R = state ? R_HIGH : R_LOW;
			const nl_double V = state ? m_VDD() : m_VSS();

			// We only need to update the net first if this is a time stepping net
			if (m_is_timestep)
				m_RV.update_dev();
			m_RV.set(NL_FCONST(1.0) / R, V, 0.0);
			m_RV.m_P.schedule_solve_after(NLTIME_FROM_NS(1));
		}

	}

	NETLIB_DEVICE_IMPL(MM5837_dip)

	} //namespace devices
} // namespace netlist
>>>>>>> upstream/master
