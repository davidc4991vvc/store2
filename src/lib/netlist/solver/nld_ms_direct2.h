// license:GPL-2.0+
// copyright-holders:Couriersud
/*
 * nld_ms_direct1.h
 *
 */

#ifndef NLD_MS_DIRECT2_H_
#define NLD_MS_DIRECT2_H_

<<<<<<< HEAD
#include "solver/nld_ms_direct.h"
#include "solver/nld_solver.h"

NETLIB_NAMESPACE_DEVICES_START()

=======
#include "nld_ms_direct.h"
#include "nld_solver.h"

namespace netlist
{
	namespace devices
	{
>>>>>>> upstream/master
class matrix_solver_direct2_t: public matrix_solver_direct_t<2,2>
{
public:

<<<<<<< HEAD
	matrix_solver_direct2_t(const solver_parameters_t *params)
		: matrix_solver_direct_t<2, 2>(params, 2)
		{}
	ATTR_HOT inline int vsolve_non_dynamic(const bool newton_raphson);
protected:
	ATTR_HOT virtual nl_double vsolve();
private:
=======
	matrix_solver_direct2_t(netlist_t &anetlist, const pstring &name, const solver_parameters_t *params)
		: matrix_solver_direct_t<2, 2>(anetlist, name, params, 2)
		{}
	virtual unsigned vsolve_non_dynamic(const bool newton_raphson) override;

>>>>>>> upstream/master
};

// ----------------------------------------------------------------------------------------
// matrix_solver - Direct2
// ----------------------------------------------------------------------------------------

<<<<<<< HEAD
ATTR_HOT nl_double matrix_solver_direct2_t::vsolve()
{
	solve_base<matrix_solver_direct2_t>(this);
	return this->compute_next_timestep();
}

ATTR_HOT inline int matrix_solver_direct2_t::vsolve_non_dynamic(ATTR_UNUSED const bool newton_raphson)
{
	build_LE_A();
	build_LE_RHS(m_RHS);
=======
inline unsigned matrix_solver_direct2_t::vsolve_non_dynamic(ATTR_UNUSED const bool newton_raphson)
{
	build_LE_A<matrix_solver_direct2_t>();
	build_LE_RHS<matrix_solver_direct2_t>();
>>>>>>> upstream/master

	const nl_double a = A(0,0);
	const nl_double b = A(0,1);
	const nl_double c = A(1,0);
	const nl_double d = A(1,1);

<<<<<<< HEAD
	nl_double new_val[2];
	new_val[1] = (a * m_RHS[1] - c * m_RHS[0]) / (a * d - b * c);
	new_val[0] = (m_RHS[0] - b * new_val[1]) / a;

	if (is_dynamic())
	{
		nl_double err = this->delta(new_val);
		store(new_val);
		if (err > m_params.m_accuracy )
			return 2;
		else
			return 1;
	}
	store(new_val);
	return 1;
}

NETLIB_NAMESPACE_DEVICES_END()
=======
	nl_double new_V[2];
	new_V[1] = (a * RHS(1) - c * RHS(0)) / (a * d - b * c);
	new_V[0] = (RHS(0) - b * new_V[1]) / a;

	const nl_double err = (newton_raphson ? delta(new_V) : 0.0);
	store(new_V);
	return (err > this->m_params.m_accuracy) ? 2 : 1;
}

	} //namespace devices
} // namespace netlist
>>>>>>> upstream/master

#endif /* NLD_MS_DIRECT2_H_ */
