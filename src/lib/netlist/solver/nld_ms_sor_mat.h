// license:GPL-2.0+
// copyright-holders:Couriersud
/*
 * nld_ms_sor.h
 *
 * Generic successive over relaxation solver.
 *
 * Fow w==1 we will do the classic Gauss-Seidel approach
 *
 */

#ifndef NLD_MS_SOR_MAT_H_
#define NLD_MS_SOR_MAT_H_

#include <algorithm>

<<<<<<< HEAD
#include "solver/nld_ms_direct.h"
#include "solver/nld_solver.h"

NETLIB_NAMESPACE_DEVICES_START()

template <unsigned m_N, unsigned _storage_N>
class matrix_solver_SOR_mat_t: public matrix_solver_direct_t<m_N, _storage_N>
{
public:

	matrix_solver_SOR_mat_t(const solver_parameters_t *params, int size)
		: matrix_solver_direct_t<m_N, _storage_N>(matrix_solver_t::GAUSS_SEIDEL, params, size)
		, m_omega(params->m_sor)
		, m_lp_fact(0)
		, m_gs_fail(0)
		, m_gs_total(0)
		{
		}

	virtual ~matrix_solver_SOR_mat_t() {}

	virtual void vsetup(analog_net_t::list_t &nets);

	ATTR_HOT inline int vsolve_non_dynamic(const bool newton_raphson);
protected:
	ATTR_HOT virtual nl_double vsolve();

private:
	nl_double m_Vdelta[_storage_N];

	nl_double m_omega;
	nl_double m_lp_fact;
	int m_gs_fail;
	int m_gs_total;
=======
#include "nld_ms_direct.h"
#include "nld_matrix_solver.h"
#include "nld_solver.h"

namespace netlist
{
	namespace devices
	{
template <std::size_t m_N, std::size_t storage_N>
class matrix_solver_SOR_mat_t: public matrix_solver_direct_t<m_N, storage_N>
{
	friend class matrix_solver_t;

public:

	matrix_solver_SOR_mat_t(netlist_t &anetlist, const pstring &name, const solver_parameters_t *params, std::size_t size)
		: matrix_solver_direct_t<m_N, storage_N>(anetlist, name, matrix_solver_t::DESCENDING, params, size)
		, m_Vdelta(*this, "m_Vdelta", 0.0)
		, m_omega(*this, "m_omega", params->m_gs_sor)
		, m_lp_fact(*this, "m_lp_fact", 0)
		, m_gs_fail(*this, "m_gs_fail", 0)
		, m_gs_total(*this, "m_gs_total", 0)
		{
		}

	virtual ~matrix_solver_SOR_mat_t() override {}

	virtual void vsetup(analog_net_t::list_t &nets) override;

	virtual unsigned vsolve_non_dynamic(const bool newton_raphson) override;

private:
	state_var<nl_double[storage_N]> m_Vdelta;

	state_var<nl_double> m_omega;
	state_var<nl_double> m_lp_fact;
	state_var<int> m_gs_fail;
	state_var<int> m_gs_total;
>>>>>>> upstream/master
};

// ----------------------------------------------------------------------------------------
// matrix_solver - Gauss - Seidel
// ----------------------------------------------------------------------------------------

<<<<<<< HEAD
template <unsigned m_N, unsigned _storage_N>
void matrix_solver_SOR_mat_t<m_N, _storage_N>::vsetup(analog_net_t::list_t &nets)
{
	matrix_solver_direct_t<m_N, _storage_N>::vsetup(nets);
	this->save(NLNAME(m_omega));
	this->save(NLNAME(m_lp_fact));
	this->save(NLNAME(m_gs_fail));
	this->save(NLNAME(m_gs_total));
	this->save(NLNAME(m_Vdelta));
}


template <unsigned m_N, unsigned _storage_N>
ATTR_HOT nl_double matrix_solver_SOR_mat_t<m_N, _storage_N>::vsolve()
=======
template <std::size_t m_N, std::size_t storage_N>
void matrix_solver_SOR_mat_t<m_N, storage_N>::vsetup(analog_net_t::list_t &nets)
{
	matrix_solver_direct_t<m_N, storage_N>::vsetup(nets);
}

#if 0
//FIXME: move to solve_base
template <unsigned m_N, unsigned storage_N>
nl_double matrix_solver_SOR_mat_t<m_N, storage_N>::vsolve()
>>>>>>> upstream/master
{
	/*
	 * enable linear prediction on first newton pass
	 */

	if (USE_LINEAR_PREDICTION)
		for (unsigned k = 0; k < this->N(); k++)
		{
			this->m_last_V[k] = this->m_nets[k]->m_cur_Analog;
			this->m_nets[k]->m_cur_Analog = this->m_nets[k]->m_cur_Analog + this->m_Vdelta[k] * this->current_timestep() * m_lp_fact;
		}
	else
		for (unsigned k = 0; k < this->N(); k++)
		{
			this->m_last_V[k] = this->m_nets[k]->m_cur_Analog;
		}

	this->solve_base(this);

	if (USE_LINEAR_PREDICTION)
	{
		nl_double sq = 0;
		nl_double sqo = 0;
		const nl_double rez_cts = 1.0 / this->current_timestep();
		for (unsigned k = 0; k < this->N(); k++)
		{
			const analog_net_t *n = this->m_nets[k];
<<<<<<< HEAD
			const nl_double nv = (n->m_cur_Analog - this->m_last_V[k]) * rez_cts ;
=======
			const nl_double nv = (n->Q_Analog() - this->m_last_V[k]) * rez_cts ;
>>>>>>> upstream/master
			sq += nv * nv;
			sqo += this->m_Vdelta[k] * this->m_Vdelta[k];
			this->m_Vdelta[k] = nv;
		}

		// FIXME: used to be 1e90, but this would not be compatible with float
		if (sqo > NL_FCONST(1e-20))
<<<<<<< HEAD
			m_lp_fact = std::min(nl_math::sqrt(sq/sqo), (nl_double) 2.0);
=======
			m_lp_fact = std::min(std::sqrt(sq/sqo), (nl_double) 2.0);
>>>>>>> upstream/master
		else
			m_lp_fact = NL_FCONST(0.0);
	}


	return this->compute_next_timestep();
}
<<<<<<< HEAD

template <unsigned m_N, unsigned _storage_N>
ATTR_HOT inline int matrix_solver_SOR_mat_t<m_N, _storage_N>::vsolve_non_dynamic(const bool newton_raphson)
=======
#endif

template <std::size_t m_N, std::size_t storage_N>
unsigned matrix_solver_SOR_mat_t<m_N, storage_N>::vsolve_non_dynamic(const bool newton_raphson)
>>>>>>> upstream/master
{
	/* The matrix based code looks a lot nicer but actually is 30% slower than
	 * the optimized code which works directly on the data structures.
	 * Need something like that for gaussian elimination as well.
	 */


<<<<<<< HEAD
	ATTR_ALIGN nl_double new_v[_storage_N] = { 0.0 };
	const unsigned iN = this->N();

	bool resched = false;

	int  resched_cnt = 0;

	this->build_LE_A();
	this->build_LE_RHS(this->m_RHS);
=======
	nl_double new_v[storage_N] = { 0.0 };
	const std::size_t iN = this->N();

	matrix_solver_t::build_LE_A<matrix_solver_SOR_mat_t>();
	matrix_solver_t::build_LE_RHS<matrix_solver_SOR_mat_t>();

	bool resched = false;

	unsigned resched_cnt = 0;

>>>>>>> upstream/master

#if 0
	static int ws_cnt = 0;
	ws_cnt++;
	if (1 && ws_cnt % 200 == 0)
	{
		// update omega
		nl_double lambdaN = 0;
		nl_double lambda1 = 1e9;
		for (int k = 0; k < iN; k++)
		{
	#if 0
<<<<<<< HEAD
			nl_double akk = nl_math::abs(this->m_A[k][k]);
=======
			nl_double akk = std::abs(this->m_A[k][k]);
>>>>>>> upstream/master
			if ( akk > lambdaN)
				lambdaN = akk;
			if (akk < lambda1)
				lambda1 = akk;
	#else
<<<<<<< HEAD
			nl_double akk = nl_math::abs(this->m_A[k][k]);
			nl_double s = 0.0;
			for (int i=0; i<iN; i++)
				s = s + nl_math::abs(this->m_A[k][i]);
=======
			nl_double akk = std::abs(this->m_A[k][k]);
			nl_double s = 0.0;
			for (int i=0; i<iN; i++)
				s = s + std::abs(this->m_A[k][i]);
>>>>>>> upstream/master
			akk = s / akk - 1.0;
			if ( akk > lambdaN)
				lambdaN = akk;
			if (akk < lambda1)
				lambda1 = akk;
	#endif
		}
		//printf("lambda: %f %f\n", lambda, 2.0 / (1.0 + 2 * sqrt(lambda)) );

		//ws = 2.0 / (2.0 - lambdaN - lambda1);
		m_omega = 2.0 / (2.0 - lambda1);
		//printf("%f %f %f\n", m_omega, lambda1, lambdaN);
	}
#endif

<<<<<<< HEAD
	for (unsigned k = 0; k < iN; k++)
		new_v[k] = this->m_nets[k]->m_cur_Analog;
=======
	for (std::size_t k = 0; k < iN; k++)
		new_v[k] = this->m_nets[k]->Q_Analog();
>>>>>>> upstream/master

	do {
		resched = false;
		nl_double cerr = 0.0;

<<<<<<< HEAD
		for (unsigned k = 0; k < iN; k++)
		{
			nl_double Idrive = 0;

			const unsigned *p = this->m_terms[k]->m_nz.data();
			const unsigned e = this->m_terms[k]->m_nz.size();

			for (unsigned i = 0; i < e; i++)
				Idrive = Idrive + this->A(k,p[i]) * new_v[p[i]];

			const nl_double delta = m_omega * (this->m_RHS[k] - Idrive) / this->A(k,k);
			cerr = std::max(cerr, nl_math::abs(delta));
=======
		for (std::size_t k = 0; k < iN; k++)
		{
			nl_double Idrive = 0;

			const auto *p = this->m_terms[k]->m_nz.data();
			const std::size_t e = this->m_terms[k]->m_nz.size();

			for (std::size_t i = 0; i < e; i++)
				Idrive = Idrive + this->A(k,p[i]) * new_v[p[i]];

			const nl_double delta = m_omega * (this->RHS(k) - Idrive) / this->A(k,k);
			cerr = std::max(cerr, std::abs(delta));
>>>>>>> upstream/master
			new_v[k] += delta;
		}

		if (cerr > this->m_params.m_accuracy)
		{
			resched = true;
		}
		resched_cnt++;
	} while (resched && (resched_cnt < this->m_params.m_gs_loops));

	this->m_stat_calculations++;
<<<<<<< HEAD
=======
	this->m_iterative_total += resched_cnt;
>>>>>>> upstream/master
	this->m_gs_total += resched_cnt;

	if (resched)
	{
<<<<<<< HEAD
		//this->netlist().warning("Falling back to direct solver .. Consider increasing RESCHED_LOOPS");
		this->m_gs_fail++;

		this->LE_solve();
		return matrix_solver_direct_t<m_N, _storage_N>::solve_non_dynamic(newton_raphson);
=======
		this->m_iterative_fail++;
		//this->netlist().warning("Falling back to direct solver .. Consider increasing RESCHED_LOOPS");
		this->m_gs_fail++;

		return matrix_solver_direct_t<m_N, storage_N>::solve_non_dynamic(newton_raphson);
>>>>>>> upstream/master
	}
	else {
		this->store(new_v);
		return resched_cnt;
	}

}

<<<<<<< HEAD
NETLIB_NAMESPACE_DEVICES_END()
=======
	} //namespace devices
} // namespace netlist
>>>>>>> upstream/master

#endif /* NLD_MS_GAUSS_SEIDEL_H_ */
