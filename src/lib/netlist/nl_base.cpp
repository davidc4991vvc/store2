// license:GPL-2.0+
// copyright-holders:Couriersud
/*
 * nlbase.c
 *
 */

<<<<<<< HEAD
#include <solver/nld_solver.h>
#include <cstring>
#include <algorithm>

#include "plib/palloc.h"

#include "nl_base.h"
#include "devices/nld_system.h"
#include "nl_util.h"

const netlist::netlist_time netlist::netlist_time::zero = netlist::netlist_time::from_raw(0);

namespace netlist
{
=======
#include "solver/nld_matrix_solver.h"
#include "solver/nld_solver.h"

#include "plib/putil.h"
#include "plib/palloc.h"

#include "nl_base.h"
#include "devices/nlid_system.h"
#include "devices/nlid_proxy.h"
#include "macro/nlm_base.h"

#include "nl_errstr.h"

#include <cstring>
#include <cmath>
#include <limits>

namespace netlist
{
namespace detail
{

	static plib::mempool *pool()
	{
		static plib::mempool *s_pool = nullptr;
		if (s_pool == nullptr)
			s_pool = new plib::mempool(65536, 16);
		return s_pool;
	}

	void * object_t::operator new (size_t size)
	{
		void *ret = nullptr;
		if ((USE_MEMPOOL))
			ret = pool()->alloc(size);
		else
			ret = ::operator new(size);
		return ret;
	}

	void object_t::operator delete (void * mem)
	{
		if (mem)
		{
			if ((USE_MEMPOOL))
				pool()->free(mem);
			else
				::operator delete(mem);
		}
	}

}

nl_exception::~nl_exception()
{
}


>>>>>>> upstream/master
// ----------------------------------------------------------------------------------------
// logic_family_ttl_t
// ----------------------------------------------------------------------------------------

<<<<<<< HEAD
=======
logic_family_desc_t::logic_family_desc_t()
{
}

logic_family_desc_t::~logic_family_desc_t()
{
}


>>>>>>> upstream/master
class logic_family_ttl_t : public logic_family_desc_t
{
public:
	logic_family_ttl_t() : logic_family_desc_t()
	{
<<<<<<< HEAD
		m_low_thresh_V = 0.8;
		m_high_thresh_V = 2.0;
		// m_low_V  - these depend on sinked/sourced current. Values should be suitable for typical applications.
		m_low_V = 0.1;
		m_high_V = 4.0;
		m_R_low = 1.0;
		m_R_high = 130.0;
		m_is_static = true;
	}
	virtual devices::nld_base_d_to_a_proxy *create_d_a_proxy(logic_output_t *proxied) const
	{
		return palloc(devices::nld_d_to_a_proxy(proxied));
	}
};

//FIXME: set to proper values
=======
		m_fixed_V = 5.0;
		m_low_thresh_PCNT = 0.8 / 5.0;
		m_high_thresh_PCNT = 2.0 / 5.0;
		// m_low_V  - these depend on sinked/sourced current. Values should be suitable for typical applications.
		m_low_VO = 0.1;
		m_high_VO = 1.0; // 4.0
		m_R_low = 1.0;
		m_R_high = 130.0;
	}
	virtual plib::owned_ptr<devices::nld_base_d_to_a_proxy> create_d_a_proxy(netlist_t &anetlist, const pstring &name, logic_output_t *proxied) const override;
	virtual plib::owned_ptr<devices::nld_base_a_to_d_proxy> create_a_d_proxy(netlist_t &anetlist, const pstring &name, logic_input_t *proxied) const override;
};

plib::owned_ptr<devices::nld_base_d_to_a_proxy> logic_family_ttl_t::create_d_a_proxy(netlist_t &anetlist, const pstring &name, logic_output_t *proxied) const
{
	return plib::owned_ptr<devices::nld_base_d_to_a_proxy>::Create<devices::nld_d_to_a_proxy>(anetlist, name, proxied);
}
plib::owned_ptr<devices::nld_base_a_to_d_proxy> logic_family_ttl_t::create_a_d_proxy(netlist_t &anetlist, const pstring &name, logic_input_t *proxied) const
{
	return plib::owned_ptr<devices::nld_base_a_to_d_proxy>::Create<devices::nld_a_to_d_proxy>(anetlist, name, proxied);
}

>>>>>>> upstream/master
class logic_family_cd4xxx_t : public logic_family_desc_t
{
public:
	logic_family_cd4xxx_t() : logic_family_desc_t()
	{
<<<<<<< HEAD
		m_low_thresh_V = 0.8;
		m_high_thresh_V = 2.0;
		// m_low_V  - these depend on sinked/sourced current. Values should be suitable for typical applications.
		m_low_V = 0.05;
		m_high_V = 4.95;
		m_R_low = 10.0;
		m_R_high = 10.0;
		m_is_static = true;
	}
	virtual devices::nld_base_d_to_a_proxy *create_d_a_proxy(logic_output_t *proxied) const
	{
		return palloc(devices::nld_d_to_a_proxy(proxied));
	}
};

logic_family_desc_t *netlist_family_TTL = palloc(logic_family_ttl_t);
logic_family_desc_t *netlist_family_CD4XXX = palloc(logic_family_cd4xxx_t);

// ----------------------------------------------------------------------------------------
// netlist_queue_t
// ----------------------------------------------------------------------------------------

queue_t::queue_t(netlist_t &nl)
	: timed_queue<net_t *, netlist_time>(512)
	, object_t(QUEUE, GENERIC)
	, pstate_callback_t()
	, m_qsize(0)
	, m_times(512)
	, m_names(512)
{
	this->init_object(nl, "QUEUE");
}

void queue_t::register_state(pstate_manager_t &manager, const pstring &module)
{
	netlist().log().debug("register_state\n");
	manager.save_item(m_qsize, this, module + "." + "qsize");
	manager.save_item(&m_times[0], this, module + "." + "times", m_times.size());
	manager.save_item(&(m_names[0].m_buf[0]), this, module + "." + "names", m_names.size() * sizeof(names_t));
}

void queue_t::on_pre_save()
{
	netlist().log().debug("on_pre_save\n");
	m_qsize = this->count();
	netlist().log().debug("current time {1} qsize {2}\n", netlist().time().as_double(), m_qsize);
	for (int i = 0; i < m_qsize; i++ )
	{
		m_times[i] =  this->listptr()[i].exec_time().as_raw();
		pstring p = this->listptr()[i].object()->name();
		int n = p.len();
		n = std::min(63, n);
		std::strncpy(m_names[i].m_buf, p.cstr(), n);
		m_names[i].m_buf[n] = 0;
=======
		m_fixed_V = 0.0;
		m_low_thresh_PCNT = 1.5 / 5.0;
		m_high_thresh_PCNT = 3.5 / 5.0;
		// m_low_V  - these depend on sinked/sourced current. Values should be suitable for typical applications.
		m_low_VO = 0.05;
		m_high_VO = 0.05; // 4.95
		m_R_low = 10.0;
		m_R_high = 10.0;
	}
	virtual plib::owned_ptr<devices::nld_base_d_to_a_proxy> create_d_a_proxy(netlist_t &anetlist, const pstring &name, logic_output_t *proxied) const override;
	virtual plib::owned_ptr<devices::nld_base_a_to_d_proxy> create_a_d_proxy(netlist_t &anetlist, const pstring &name, logic_input_t *proxied) const override;
};

plib::owned_ptr<devices::nld_base_d_to_a_proxy> logic_family_cd4xxx_t::create_d_a_proxy(netlist_t &anetlist, const pstring &name, logic_output_t *proxied) const
{
	return plib::owned_ptr<devices::nld_base_d_to_a_proxy>::Create<devices::nld_d_to_a_proxy>(anetlist, name, proxied);
}
plib::owned_ptr<devices::nld_base_a_to_d_proxy> logic_family_cd4xxx_t::create_a_d_proxy(netlist_t &anetlist, const pstring &name, logic_input_t *proxied) const
{
	return plib::owned_ptr<devices::nld_base_a_to_d_proxy>::Create<devices::nld_a_to_d_proxy>(anetlist, name, proxied);
}

const logic_family_desc_t *family_TTL()
{
	static logic_family_ttl_t obj;
	return &obj;
}
const logic_family_desc_t *family_CD4XXX()
{
	static logic_family_cd4xxx_t obj;
	return &obj;
}


// ----------------------------------------------------------------------------------------
// queue_t
// ----------------------------------------------------------------------------------------

detail::queue_t::queue_t(netlist_t &nl)
	: timed_queue<pqentry_t<net_t *, netlist_time>, false>(512)
	, netlist_ref(nl)
	, plib::state_manager_t::callback_t()
	, m_qsize(0)
	, m_times(512)
	, m_net_ids(512)
{
}

void detail::queue_t::register_state(plib::state_manager_t &manager, const pstring &module)
{
	netlist().log().debug("register_state\n");
	manager.save_item(this, m_qsize, module + "." + "qsize");
	manager.save_item(this, &m_times[0], module + "." + "times", m_times.size());
	manager.save_item(this, &m_net_ids[0], module + "." + "names", m_net_ids.size());
}

void detail::queue_t::on_pre_save()
{
	netlist().log().debug("on_pre_save\n");
	m_qsize = this->size();
	netlist().log().debug("current time {1} qsize {2}\n", netlist().time().as_double(), m_qsize);
	for (std::size_t i = 0; i < m_qsize; i++ )
	{
		m_times[i] =  this->listptr()[i].m_exec_time.as_raw();
		m_net_ids[i] = netlist().find_net_id(this->listptr()[i].m_object);
>>>>>>> upstream/master
	}
}


<<<<<<< HEAD
void queue_t::on_post_load()
{
	this->clear();
	netlist().log().debug("current time {1} qsize {2}\n", netlist().time().as_double(), m_qsize);
	for (int i = 0; i < m_qsize; i++ )
	{
		net_t *n = netlist().find_net(m_names[i].m_buf);
		//log().debug("Got {1} ==> {2}\n", qtemp[i].m_name, n));
		//log().debug("schedule time {1} ({2})\n", n->time().as_double(),  netlist_time::from_raw(m_times[i]).as_double()));
		this->push(queue_t::entry_t(netlist_time::from_raw(m_times[i]), n));
=======
void detail::queue_t::on_post_load()
{
	this->clear();
	netlist().log().debug("current time {1} qsize {2}\n", netlist().time().as_double(), m_qsize);
	for (std::size_t i = 0; i < m_qsize; i++ )
	{
		detail::net_t *n = netlist().m_nets[m_net_ids[i]].get();
		this->push(queue_t::entry_t(netlist_time::from_raw(m_times[i]),n));
>>>>>>> upstream/master
	}
}

// ----------------------------------------------------------------------------------------
<<<<<<< HEAD
// netlist_object_t
// ----------------------------------------------------------------------------------------

ATTR_COLD object_t::object_t(const type_t atype, const family_t afamily)
: m_objtype(atype)
, m_family(afamily)
, m_netlist(NULL)
{}

ATTR_COLD object_t::~object_t()
{
}

ATTR_COLD void object_t::init_object(netlist_t &nl, const pstring &aname)
{
	m_netlist = &nl;
	m_name = aname;
	save_register();
}

ATTR_COLD const pstring &object_t::name() const
{
	if (m_name == "")
		netlist().log().fatal("object not initialized");
	return m_name;
}

// ----------------------------------------------------------------------------------------
// netlist_owned_object_t
// ----------------------------------------------------------------------------------------

ATTR_COLD device_object_t::device_object_t(const type_t atype,
		const family_t afamily)
: object_t(atype, afamily)
, m_device(NULL)
{
}

ATTR_COLD void device_object_t::init_object(core_device_t &dev,
		const pstring &aname)
{
	object_t::init_object(dev.netlist(), aname);
	m_device = &dev;
}

// ----------------------------------------------------------------------------------------
// netlist_base_t
// ----------------------------------------------------------------------------------------

netlist_t::netlist_t()
	:   object_t(NETLIST, GENERIC), pstate_manager_t(),
		m_stop(netlist_time::zero),
		m_time(netlist_time::zero),
		m_use_deactivate(0),
		m_queue(*this),
		m_mainclock(NULL),
		m_solver(NULL),
		m_gnd(NULL),
		m_setup(NULL),
		m_log(this)
{
=======
// object_t
// ----------------------------------------------------------------------------------------

detail::object_t::object_t(const pstring &aname)
	: m_name(plib::make_unique<pstring>(aname))
{
}

detail::object_t::~object_t()
{
}

const pstring &detail::object_t::name() const
{
	return *m_name;
}

// ----------------------------------------------------------------------------------------
// device_object_t
// ----------------------------------------------------------------------------------------

detail::device_object_t::device_object_t(core_device_t &dev, const pstring &aname)
: object_t(aname)
, m_device(dev)
{
}

detail::terminal_type detail::core_terminal_t::type() const
{
	if (dynamic_cast<const terminal_t *>(this) != nullptr)
		return terminal_type::TERMINAL;
	else if (dynamic_cast<const logic_input_t *>(this) != nullptr)
		return terminal_type::INPUT;
	else if (dynamic_cast<const logic_output_t *>(this) != nullptr)
		return terminal_type::OUTPUT;
	else if (dynamic_cast<const analog_input_t *>(this) != nullptr)
		return terminal_type::INPUT;
	else if (dynamic_cast<const analog_output_t *>(this) != nullptr)
		return terminal_type::OUTPUT;
	else
	{
		netlist().log().fatal(MF_1_UNKNOWN_TYPE_FOR_OBJECT, name());
		return terminal_type::TERMINAL; // please compiler
	}
}

// ----------------------------------------------------------------------------------------
// netlist_t
// ----------------------------------------------------------------------------------------

netlist_t::netlist_t(const pstring &aname)
	: m_time(netlist_time::zero())
	, m_queue(*this)
	, m_mainclock(nullptr)
	, m_solver(nullptr)
	, m_params(nullptr)
	, m_name(aname)
	, m_log(*this)
	, m_lib(nullptr)
	, m_state()
{
	state().save_item(this, static_cast<plib::state_manager_t::callback_t &>(m_queue), "m_queue");
	state().save_item(this, m_time, "m_time");
	m_setup = plib::make_unique<setup_t>(*this);
	/* FIXME: doesn't really belong here */
	NETLIST_NAME(base)(*m_setup);
>>>>>>> upstream/master
}

netlist_t::~netlist_t()
{
<<<<<<< HEAD
	for (std::size_t i=0; i < m_nets.size(); i++)
	{
		if (!m_nets[i]->isRailNet())
		{
			pfree(m_nets[i]);
		}
	}

	m_nets.clear();

	m_devices.clear_and_free();

	pstring::resetmem();
}

ATTR_COLD void netlist_t::save_register()
{
	save(static_cast<pstate_callback_t &>(m_queue), "m_queue");
	save(NLNAME(m_time));
	object_t::save_register();
}

ATTR_HOT nl_double netlist_t::gmin() const
{
	return solver()->gmin();
}

ATTR_COLD void netlist_t::start()
{
	/* find the main clock and solver ... */

	log().debug("Searching for mainclock and solver ...\n");

	m_mainclock = get_single_device<devices:: NETLIB_NAME(mainclock)>("mainclock");
	m_solver = get_single_device<devices::NETLIB_NAME(solver)>("solver");
	m_gnd = get_single_device<devices::NETLIB_NAME(gnd)>("gnd");
	m_params = get_single_device<devices::NETLIB_NAME(netlistparams)>("parameter");

	/* make sure the solver and parameters are started first! */

	if (m_solver != NULL)
		m_solver->start_dev();

	if (m_params != NULL)
	{
		m_params->start_dev();
	}

	m_use_deactivate = (m_params->m_use_deactivate.Value() ? true : false);

	log().debug("Initializing devices ...\n");
	for (std::size_t i = 0; i < m_devices.size(); i++)
	{
		device_t *dev = m_devices[i];
		if (dev != m_solver && dev != m_params)
			dev->start_dev();
	}

}

ATTR_COLD void netlist_t::stop()
{
	/* find the main clock and solver ... */

	log().debug("Stopping all devices ...\n");

	// Step all devices once !
	for (std::size_t i = 0; i < m_devices.size(); i++)
	{
		m_devices[i]->stop_dev();
	}
}

ATTR_COLD net_t *netlist_t::find_net(const pstring &name)
{
	for (std::size_t i = 0; i < m_nets.size(); i++)
	{
		if (m_nets[i]->name() == name)
			return m_nets[i];
	}
	return NULL;
}

ATTR_COLD void netlist_t::rebuild_lists()
{
	for (std::size_t i = 0; i < m_nets.size(); i++)
		m_nets[i]->rebuild_list();
}


ATTR_COLD void netlist_t::reset()
{
	m_time = netlist_time::zero;
	m_queue.clear();
	if (m_mainclock != NULL)
		m_mainclock->m_Q.net().set_time(netlist_time::zero);
	if (m_solver != NULL)
		m_solver->do_reset();

	// Reset all nets once !
	for (std::size_t i = 0; i < m_nets.size(); i++)
		m_nets[i]->do_reset();

	// Reset all devices once !
	for (std::size_t i = 0; i < m_devices.size(); i++)
	{
		m_devices[i]->do_reset();
	}

	// Step all devices once !
	for (std::size_t i = 0; i < m_devices.size(); i++)
	{
		m_devices[i]->update_dev();
	}

	// FIXME: some const devices rely on this
	/* make sure params are set now .. */
	for (std::size_t i = 0; i < m_devices.size(); i++)
	{
		m_devices[i]->update_param();
	}
}


ATTR_HOT void netlist_t::process_queue(const netlist_time &delta)
{
	m_stop = m_time + delta;

	if (m_mainclock == NULL)
	{
		while ( (m_time < m_stop) && (m_queue.is_not_empty()))
		{
			const queue_t::entry_t e = *m_queue.pop();
			m_time = e.exec_time();
			e.object()->update_devs();

			add_to_stat(m_perf_out_processed, 1);
		}
		if (m_queue.is_empty())
			m_time = m_stop;

	} else {
		logic_net_t &mc_net = m_mainclock->m_Q.net().as_logic();
		const netlist_time inc = m_mainclock->m_inc;
		netlist_time mc_time = mc_net.time();

		while (m_time < m_stop)
		{
			if (m_queue.is_not_empty())
			{
				while (m_queue.peek()->exec_time() > mc_time)
				{
					m_time = mc_time;
					mc_time += inc;
					devices::NETLIB_NAME(mainclock)::mc_update(mc_net);
				}

				const queue_t::entry_t e = *m_queue.pop();
				m_time = e.exec_time();
				e.object()->update_devs();

			} else {
				m_time = mc_time;
				mc_time += inc;
				devices::NETLIB_NAME(mainclock)::mc_update(mc_net);
			}

			add_to_stat(m_perf_out_processed, 1);
		}
		mc_net.set_time(mc_time);
	}
}

// ----------------------------------------------------------------------------------------
// Default netlist elements ...
// ----------------------------------------------------------------------------------------



// ----------------------------------------------------------------------------------------
// net_core_device_t
// ----------------------------------------------------------------------------------------

ATTR_COLD core_device_t::core_device_t(const family_t afamily)
: object_t(DEVICE, afamily), logic_family_t()
#if (NL_KEEP_STATISTICS)
	, stat_total_time(0)
	, stat_update_count(0)
	, stat_call_count(0)
#endif
{
}

ATTR_COLD void core_device_t::init(netlist_t &anetlist, const pstring &name)
{
	if (logic_family() == NULL)
		set_logic_family(this->default_logic_family());
	init_object(anetlist, name);

#if (NL_PMF_TYPE == NL_PMF_TYPE_GNUC_PMF)
	void (core_device_t::* pFunc)() = &core_device_t::update;
	m_static_update = pFunc;
#elif (NL_PMF_TYPE == NL_PMF_TYPE_GNUC_PMF_CONV)
	void (core_device_t::* pFunc)() = &core_device_t::update;
	m_static_update = reinterpret_cast<net_update_delegate>((this->*pFunc));
#elif (NL_PMF_TYPE == NL_PMF_TYPE_INTERNAL)
	m_static_update = pmfp::get_mfp<net_update_delegate>(&core_device_t::update, this);
#endif
}

ATTR_COLD core_device_t::~core_device_t()
{
}

ATTR_COLD void core_device_t::start_dev()
{
#if (NL_KEEP_STATISTICS)
	netlist().m_started_devices.add(this, false);
#endif
	start();
}

ATTR_COLD void core_device_t::stop_dev()
{
#if (NL_KEEP_STATISTICS)
#endif
	stop();
}

ATTR_HOT netlist_sig_t core_device_t::INPLOGIC_PASSIVE(logic_input_t &inp)
{
	if (inp.state() != logic_t::STATE_INP_PASSIVE)
		return inp.Q();
	else
	{
		inp.activate();
		const netlist_sig_t ret = inp.Q();
		inp.inactivate();
		return ret;
	}
}


// ----------------------------------------------------------------------------------------
// netlist_device_t
// ----------------------------------------------------------------------------------------

device_t::device_t()
	: core_device_t(GENERIC),
		m_terminals(20)
{
}

device_t::device_t(const family_t afamily)
	: core_device_t(afamily),
		m_terminals(20)
=======
	m_nets.clear();
	m_devices.clear();
}

nl_double netlist_t::gmin() const NL_NOEXCEPT
{
	return solver()->gmin();
}

void netlist_t::register_dev(plib::owned_ptr<core_device_t> dev)
{
	for (auto & d : m_devices)
		if (d->name() == dev->name())
			log().fatal(MF_1_DUPLICATE_NAME_DEVICE_LIST, d->name());
	m_devices.push_back(std::move(dev));
}

void netlist_t::remove_dev(core_device_t *dev)
{
	m_devices.erase(
		std::remove_if(
			m_devices.begin(),
			m_devices.end(),
			[&] (plib::owned_ptr<core_device_t> const& p)
			{
				return p.get() == dev;
			}),
			m_devices.end()
		);
}



void netlist_t::start()
{
	setup().start_devices();

	/* load the library ... */

	/* make sure the solver and parameters are started first! */

	for (auto & e : setup().m_device_factory)
	{
		if ( setup().factory().is_class<devices::NETLIB_NAME(solver)>(e.second)
				|| setup().factory().is_class<devices::NETLIB_NAME(netlistparams)>(e.second))
		{
			auto dev = plib::owned_ptr<device_t>(e.second->Create(*this, e.first));
			register_dev(std::move(dev));
		}
	}

	log().debug("Searching for mainclock and solver ...\n");

	m_solver = get_single_device<devices::NETLIB_NAME(solver)>("solver");
	m_params = get_single_device<devices::NETLIB_NAME(netlistparams)>("parameter");

	/* create devices */

	log().debug("Creating devices ...\n");
	for (auto & e : setup().m_device_factory)
	{
		if ( !setup().factory().is_class<devices::NETLIB_NAME(solver)>(e.second)
				&& !setup().factory().is_class<devices::NETLIB_NAME(netlistparams)>(e.second))
		{
			auto dev = plib::owned_ptr<device_t>(e.second->Create(*this, e.first));
			register_dev(std::move(dev));
		}
	}

	log().debug("Searching for mainclock\n");
	m_mainclock = get_single_device<devices::NETLIB_NAME(mainclock)>("mainclock");

	bool use_deactivate = (m_params->m_use_deactivate() ? true : false);

	for (auto &d : m_devices)
	{
		if (use_deactivate)
		{
			auto p = setup().m_param_values.find(d->name() + ".HINT_NO_DEACTIVATE");
			if (p != setup().m_param_values.end())
			{
				//FIXME: turn this into a proper function
				bool error;
				auto v = p->second.as_double(&error);
				if (error || std::abs(v - std::floor(v)) > 1e-6 )
					log().fatal(MF_1_HND_VAL_NOT_SUPPORTED, p->second);
				d->set_hint_deactivate(v == 0.0);
			}
		}
		else
			d->set_hint_deactivate(false);
	}

	pstring libpath = plib::util::environment("NL_BOOSTLIB", plib::util::buildpath({".", "nlboost.so"}));
	m_lib = plib::make_unique<plib::dynlib>(libpath);

	/* resolve inputs */
	setup().resolve_inputs();

	log().verbose("looking for two terms connected to rail nets ...");
	for (auto & t : get_device_list<analog::NETLIB_NAME(twoterm)>())
	{
		if (t->m_N.net().isRailNet() && t->m_P.net().isRailNet())
		{
			log().warning(MW_3_REMOVE_DEVICE_1_CONNECTED_ONLY_TO_RAILS_2_3,
				t->name(), t->m_N.net().name(), t->m_P.net().name());
			t->m_N.net().remove_terminal(t->m_N);
			t->m_P.net().remove_terminal(t->m_P);
			remove_dev(t);
		}
	}

	log().verbose("initialize solver ...\n");

	if (m_solver == nullptr)
	{
		for (auto &p : m_nets)
			if (p->is_analog())
				log().fatal(MF_0_NO_SOLVER);
	}
	else
		m_solver->post_start();

	for (auto &n : m_nets)
		for (auto & term : n->m_core_terms)
		{
			//core_device_t *dev = reinterpret_cast<core_device_t *>(term->m_delegate.object());
			core_device_t *dev = &term->device();
			dev->set_default_delegate(*term);
		}

}

void netlist_t::stop()
{
	log().debug("Printing statistics ...\n");
	print_stats();
	log().debug("Stopping solver device ...\n");
	if (m_solver != nullptr)
		m_solver->stop();
}

detail::net_t *netlist_t::find_net(const pstring &name) const
{
	for (auto & net : m_nets)
		if (net->name() == name)
			return net.get();

	return nullptr;
}

std::size_t netlist_t::find_net_id(const detail::net_t *net) const
{
	for (std::size_t i = 0; i < m_nets.size(); i++)
		if (m_nets[i].get() == net)
			return i;
	return std::numeric_limits<std::size_t>::max();
}



void netlist_t::rebuild_lists()
{
	for (auto & net : m_nets)
		net->rebuild_list();
}


void netlist_t::reset()
{
	m_time = netlist_time::zero();
	m_queue.clear();
	if (m_mainclock != nullptr)
		m_mainclock->m_Q.net().set_time(netlist_time::zero());
	//if (m_solver != nullptr)
	//  m_solver->do_reset();

	std::unordered_map<core_device_t *, bool> m;

	for (auto &d : m_devices)
	{
		m[d.get()] = d->get_hint_deactivate();
	}


	// Reset all nets once !
	for (auto & n : m_nets)
		n->reset();

	// Reset all devices once !
	for (auto & dev : m_devices)
		dev->do_reset();

	// Make sure everything depending on parameters is set
	for (auto & dev : m_devices)
		dev->update_param();

	// Step all devices once !
	/*
	 * INFO: The order here affects power up of e.g. breakout. However, such
	 * variations are explicitly stated in the breakout manual.
	 */

	const unsigned startup_strategy = 1; //! \note make this a parameter

	switch (startup_strategy)
	{
		case 0:
		{
			std::vector<core_device_t *> d;
			std::vector<nldelegate *> t;
			log().verbose("Using default startup strategy");
			for (auto &n : m_nets)
				for (auto & term : n->m_core_terms)
					if (term->m_delegate.has_object())
					{
						if (!plib::container::contains(t, &term->m_delegate))
						{
							t.push_back(&term->m_delegate);
							term->m_delegate();
						}
						core_device_t *dev = reinterpret_cast<core_device_t *>(term->m_delegate.object());
						if (!plib::container::contains(d, dev))
							d.push_back(dev);
					}
			log().verbose("Call update on devices which need parameter update:");
			for (auto & dev : m_devices)
				if (dev->needs_update_after_param_change())
				{
					if (!plib::container::contains(d, dev.get()))
					{
						d.push_back(dev.get());
						log().verbose("\t ...{1}", dev->name());
						dev->update_dev();
					}
				}
			log().verbose("Devices not yet updated:");
			for (auto &dev : m_devices)
				if (!plib::container::contains(d, dev.get()))
					log().verbose("\t ...{1}", dev->name());
					//x->update_dev();
		}
		break;
		case 1:     // brute force backward
		{
			std::size_t i = m_devices.size();
			while (i>0)
				m_devices[--i]->update_dev();
		}
		break;
		case 2:     // brute force forward
		{
			for (auto &d : m_devices)
				d->update_dev();
		}
		break;
	}

#if 1
	/* the above may screw up m_active and the list */
	for (auto &n : m_nets)
		n->rebuild_list();
#endif
}


void netlist_t::process_queue(const netlist_time &delta) NL_NOEXCEPT
{
	netlist_time stop(m_time + delta);

	m_queue.push(detail::queue_t::entry_t(stop, nullptr));

	m_stat_mainloop.start();

	if (m_mainclock == nullptr)
	{
		detail::queue_t::entry_t e(m_queue.top());
		m_queue.pop();
		m_time = e.m_exec_time;
		while (e.m_object != nullptr)
		{
			e.m_object->update_devs();
			m_perf_out_processed.inc();
			e = m_queue.top();
			m_queue.pop();
			m_time = e.m_exec_time;
		}
	}
	else
	{
		logic_net_t &mc_net(m_mainclock->m_Q.net());
		const netlist_time inc(m_mainclock->m_inc);
		netlist_time mc_time(mc_net.time());

		detail::queue_t::entry_t e;

		do
		{
			while (m_queue.top().m_exec_time > mc_time)
			{
				m_time = mc_time;
				mc_net.toggle_new_Q();
				mc_net.update_devs();
				mc_time += inc;
			}

			e = m_queue.top();
			m_queue.pop();
			m_time = e.m_exec_time;
			if (e.m_object != nullptr)
			{
				e.m_object->update_devs();
				m_perf_out_processed.inc();
			}
		} while (e.m_object != nullptr);
		mc_net.set_time(mc_time);
	}
	m_stat_mainloop.stop();
}

void netlist_t::print_stats() const
{
	if (nperftime_t::enabled)
	{
		std::vector<size_t> index;
		for (size_t i=0; i<m_devices.size(); i++)
			index.push_back(i);

		std::sort(index.begin(), index.end(),
				[&](size_t i1, size_t i2) { return m_devices[i1]->m_stat_total_time.total() < m_devices[i2]->m_stat_total_time.total(); });

		nperftime_t::type total_time(0);
		uint_least64_t total_count(0);

		for (auto & j : index)
		{
			auto entry = m_devices[j].get();
			log().verbose("Device {1:20} : {2:12} {3:12} {4:15} {5:12}", entry->name(),
					entry->m_stat_call_count(), entry->m_stat_total_time.count(),
					entry->m_stat_total_time.total(), entry->m_stat_inc_active());
			total_time += entry->m_stat_total_time.total();
			total_count += entry->m_stat_total_time.count();
		}

		nperftime_t overhead;
		nperftime_t test;
		overhead.start();
		for (int j=0; j<100000;j++)
		{
			test.start();
			test.stop();
		}
		overhead.stop();

		nperftime_t::type total_overhead = overhead()
				* static_cast<nperftime_t::type>(total_count)
				/ static_cast<nperftime_t::type>(200000);

		log().verbose("Queue Pushes   {1:15}", queue().m_prof_call());
		log().verbose("Queue Moves    {1:15}", queue().m_prof_sortmove());

		log().verbose("Total loop     {1:15}", m_stat_mainloop());
		/* Only one serialization should be counted in total time */
		/* But two are contained in m_stat_mainloop */
		log().verbose("Total devices  {1:15}", total_time);
		log().verbose("");
		log().verbose("Take the next lines with a grain of salt. They depend on the measurement implementation.");
		log().verbose("Total overhead {1:15}", total_overhead);
		nperftime_t::type overhead_per_pop = (m_stat_mainloop()-2*total_overhead - (total_time - total_overhead))
				/ static_cast<nperftime_t::type>(queue().m_prof_call());
		log().verbose("Overhead per pop  {1:11}", overhead_per_pop );
		log().verbose("");
		for (auto &entry : m_devices)
		{
			if (entry->m_stat_inc_active() > 3 * entry->m_stat_total_time.count())
				log().verbose("HINT({}, NO_DEACTIVATE)", entry->name());
		}
	}
}

core_device_t *netlist_t::get_single_device(const pstring &classname, bool (*cc)(core_device_t *)) const
{
	core_device_t *ret = nullptr;
	for (auto &d : m_devices)
	{
		if (cc(d.get()))
		{
			if (ret != nullptr)
				this->log().fatal(MF_1_MORE_THAN_ONE_1_DEVICE_FOUND, classname);
			else
				ret = d.get();
		}
	}
	return ret;
}


// ----------------------------------------------------------------------------------------
// core_device_t
// ----------------------------------------------------------------------------------------

core_device_t::core_device_t(netlist_t &owner, const pstring &name)
	: object_t(name)
	, logic_family_t()
	, netlist_ref(owner)
	, m_hint_deactivate(false)
{
	if (logic_family() == nullptr)
		set_logic_family(family_TTL());
}

core_device_t::core_device_t(core_device_t &owner, const pstring &name)
	: object_t(owner.name() + "." + name)
	, logic_family_t()
	, netlist_ref(owner.netlist())
	, m_hint_deactivate(false)
{
	set_logic_family(owner.logic_family());
	if (logic_family() == nullptr)
		set_logic_family(family_TTL());
	owner.netlist().register_dev(plib::owned_ptr<core_device_t>(this, false));
}

core_device_t::~core_device_t()
{
}

void core_device_t::set_default_delegate(detail::core_terminal_t &term)
{
	if (!term.m_delegate.is_set())
		term.m_delegate.set(&core_device_t::update, this);
}

plib::plog_base<netlist_t, NL_DEBUG> &core_device_t::log()
{
	return netlist().log();
}

// ----------------------------------------------------------------------------------------
// device_t
// ----------------------------------------------------------------------------------------

device_t::device_t(netlist_t &owner, const pstring &name)
: core_device_t(owner, name)
{
}

device_t::device_t(core_device_t &owner, const pstring &name)
: core_device_t(owner, name)
>>>>>>> upstream/master
{
}

device_t::~device_t()
{
	//log().debug("~net_device_t\n");
}

<<<<<<< HEAD
ATTR_COLD setup_t &device_t::setup()
=======
setup_t &device_t::setup()
>>>>>>> upstream/master
{
	return netlist().setup();
}

<<<<<<< HEAD
ATTR_COLD void device_t::init(netlist_t &anetlist, const pstring &name)
{
	core_device_t::init(anetlist, name);
}


ATTR_COLD void device_t::register_sub(const pstring &name, device_t &dev)
{
	dev.init(netlist(), this->name() + "." + name);
	// subdevices always first inherit the logic family of the parent
	dev.set_logic_family(this->logic_family());
	dev.start_dev();
}

ATTR_COLD void device_t::register_subalias(const pstring &name, core_terminal_t &term)
=======
void device_t::register_subalias(const pstring &name, detail::core_terminal_t &term)
>>>>>>> upstream/master
{
	pstring alias = this->name() + "." + name;

	// everything already fully qualified
	setup().register_alias_nofqn(alias, term.name());
<<<<<<< HEAD

	if (term.isType(terminal_t::INPUT) || term.isType(terminal_t::TERMINAL))
		m_terminals.add(alias);
}

ATTR_COLD void device_t::register_subalias(const pstring &name, const pstring &aliased)
=======
}

void device_t::register_subalias(const pstring &name, const pstring &aliased)
>>>>>>> upstream/master
{
	pstring alias = this->name() + "." + name;
	pstring aliased_fqn = this->name() + "." + aliased;

	// everything already fully qualified
	setup().register_alias_nofqn(alias, aliased_fqn);
<<<<<<< HEAD

	// FIXME: make this working again
	//if (term.isType(terminal_t::INPUT) || term.isType(terminal_t::TERMINAL))
	//  m_terminals.add(name);
}

ATTR_COLD void device_t::register_terminal(const pstring &name, terminal_t &port)
{
	setup().register_object(*this, name, port);
	if (port.isType(terminal_t::INPUT) || port.isType(terminal_t::TERMINAL))
		m_terminals.add(port.name());
}

ATTR_COLD void device_t::register_output(const pstring &name, logic_output_t &port)
{
	port.set_logic_family(this->logic_family());
	setup().register_object(*this, name, port);
}

ATTR_COLD void device_t::register_output(const pstring &name, analog_output_t &port)
{
	setup().register_object(*this, name, port);
}

ATTR_COLD void device_t::register_input(const pstring &name, logic_input_t &inp)
{
	inp.set_logic_family(this->logic_family());
	setup().register_object(*this, name, inp);
	m_terminals.add(inp.name());
}

ATTR_COLD void device_t::register_input(const pstring &name, analog_input_t &inp)
{
	setup().register_object(*this, name, inp);
	m_terminals.add(inp.name());
}

ATTR_COLD void device_t::connect_late(core_terminal_t &t1, core_terminal_t &t2)
=======
}

void device_t::connect(detail::core_terminal_t &t1, detail::core_terminal_t &t2)
>>>>>>> upstream/master
{
	setup().register_link_fqn(t1.name(), t2.name());
}

<<<<<<< HEAD
ATTR_COLD void device_t::connect_late(const pstring &t1, const pstring &t2)
=======
void device_t::connect(const pstring &t1, const pstring &t2)
>>>>>>> upstream/master
{
	setup().register_link_fqn(name() + "." + t1, name() + "." + t2);
}

<<<<<<< HEAD
ATTR_COLD void device_t::connect_direct(core_terminal_t &t1, core_terminal_t &t2)
{
	if (!setup().connect(t1, t2))
		netlist().log().fatal("Error connecting {1} to {2}\n", t1.name(), t2.name());
}


template <class C, class T>
ATTR_COLD void device_t::register_param(const pstring &sname, C &param, const T initialVal)
{
	pstring fullname = this->name() + "." + sname;
	param.init_object(*this, fullname);
	param.initial(initialVal);
	setup().register_object(*this, fullname, param);
}

template ATTR_COLD void device_t::register_param(const pstring &sname, param_double_t &param, const double initialVal);
template ATTR_COLD void device_t::register_param(const pstring &sname, param_double_t &param, const float initialVal);
template ATTR_COLD void device_t::register_param(const pstring &sname, param_int_t &param, const int initialVal);
template ATTR_COLD void device_t::register_param(const pstring &sname, param_logic_t &param, const int initialVal);
template ATTR_COLD void device_t::register_param(const pstring &sname, param_str_t &param, const char * const initialVal);
template ATTR_COLD void device_t::register_param(const pstring &sname, param_str_t &param, const pstring &initialVal);
template ATTR_COLD void device_t::register_param(const pstring &sname, param_model_t &param, const char * const initialVal);


// ----------------------------------------------------------------------------------------
// netlist_net_t
// ----------------------------------------------------------------------------------------

ATTR_COLD net_t::net_t(const family_t afamily)
	: object_t(NET, afamily)
	, m_new_Q(0)
	, m_cur_Q (0)
	, m_railterminal(NULL)
	, m_time(netlist_time::zero)
	, m_active(0)
	, m_in_queue(2)
	, m_cur_Analog(0.0)
{
}

ATTR_COLD net_t::~net_t()
{
	if (isInitialized())
		netlist().remove_save_items(this);
}

ATTR_COLD void net_t::init_object(netlist_t &nl, const pstring &aname)
{
	object_t::init_object(nl, aname);
	nl.m_nets.add(this);
}

ATTR_HOT void net_t::inc_active(core_terminal_t &term)
{
	m_active++;
	m_list_active.insert(term);
	nl_assert(m_active <= num_cons());
	if (m_active == 1)
	{
		if (netlist().use_deactivate())
		{
			railterminal().device().inc_active();
			//m_cur_Q = m_new_Q;
		}
		if (m_in_queue == 0)
		{
			if (m_time > netlist().time())
			{
				m_in_queue = 1;     /* pending */
				netlist().push_to_queue(*this, m_time);
			}
			else
			{
				m_cur_Q = m_new_Q;
				m_in_queue = 2;
			}
		}
		//else if (netlist().use_deactivate())
		//  m_cur_Q = m_new_Q;
	}
}

ATTR_HOT void net_t::dec_active(core_terminal_t &term)
{
	m_active--;
	nl_assert(m_active >= 0);
	m_list_active.remove(term);
	if (m_active == 0 && netlist().use_deactivate())
			railterminal().device().dec_active();
}

ATTR_COLD void net_t::register_railterminal(core_terminal_t &mr)
{
	nl_assert(m_railterminal == NULL);
	m_railterminal = &mr;
}

ATTR_COLD void net_t::rebuild_list()
{
	/* rebuild m_list */

	unsigned cnt = 0;
	m_list_active.clear();
	for (std::size_t i=0; i < m_core_terms.size(); i++)
		if (m_core_terms[i]->state() != logic_t::STATE_INP_PASSIVE)
		{
			m_list_active.add(*m_core_terms[i]);
=======
/* FIXME: this is only used by solver code since matrix solvers are started in
 *        post_start.
 */
void device_t::connect_post_start(detail::core_terminal_t &t1, detail::core_terminal_t &t2)
{
	if (!setup().connect(t1, t2))
		log().fatal(MF_2_ERROR_CONNECTING_1_TO_2, t1.name(), t2.name());
}


// -----------------------------------------------------------------------------
// family_setter_t
// -----------------------------------------------------------------------------

detail::family_setter_t::family_setter_t(core_device_t &dev, const pstring &desc)
{
	dev.set_logic_family(dev.netlist().setup().family_from_model(desc));
}

detail::family_setter_t::family_setter_t(core_device_t &dev, const logic_family_desc_t *desc)
{
	dev.set_logic_family(desc);
}

// ----------------------------------------------------------------------------------------
// net_t
// ----------------------------------------------------------------------------------------

detail::net_t::net_t(netlist_t &nl, const pstring &aname, core_terminal_t *mr)
	: object_t(aname)
	, netlist_ref(nl)
	, m_new_Q(*this, "m_new_Q", 0)
	, m_cur_Q (*this, "m_cur_Q", 0)
	, m_in_queue(*this, "m_in_queue", QS_DELIVERED)
	, m_active(*this, "m_active", 0)
	, m_time(*this, "m_time", netlist_time::zero())
	, m_railterminal(mr)
{
}

detail::net_t::~net_t()
{
	netlist().state().remove_save_items(this);
}

void detail::net_t::inc_active(core_terminal_t &term) NL_NOEXCEPT
{
	m_list_active.push_front(&term);
	++m_active;
	nl_assert(m_active <= static_cast<int>(num_cons()));
	if (m_active == 1)
	{
		railterminal().device().do_inc_active();
		if (m_in_queue == QS_DELAYED_DUE_TO_INACTIVE)
		{
			if (m_time > netlist().time())
			{
				m_in_queue = QS_QUEUED;     /* pending */
				netlist().queue().push({m_time, this});
			}
			else
			{
				m_in_queue = QS_DELIVERED;
				m_cur_Q = m_new_Q;
			}
		}
	}
}

void detail::net_t::dec_active(core_terminal_t &term) NL_NOEXCEPT
{
	--m_active;
	nl_assert(m_active >= 0);
	m_list_active.remove(&term);
	if (m_active == 0)
		railterminal().device().do_dec_active();
}

void detail::net_t::rebuild_list()
{
	/* rebuild m_list */

	int cnt = 0;
	m_list_active.clear();
	for (auto & term : m_core_terms)
		if (term->state() != logic_t::STATE_INP_PASSIVE)
		{
			m_list_active.push_back(term);
>>>>>>> upstream/master
			cnt++;
		}
	m_active = cnt;
}

<<<<<<< HEAD
ATTR_COLD void net_t::save_register()
{
	save(NLNAME(m_time));
	save(NLNAME(m_active));
	save(NLNAME(m_in_queue));
	save(NLNAME(m_cur_Analog));
	save(NLNAME(m_cur_Q));
	save(NLNAME(m_new_Q));
	object_t::save_register();
}

ATTR_HOT /* inline */ void core_terminal_t::update_dev(const UINT32 mask)
{
	inc_stat(netdev().stat_call_count);
	if ((state() & mask) != 0)
	{
		device().update_dev();
	}
}

ATTR_HOT /* inline */ void net_t::update_devs()
{
	//assert(m_num_cons != 0);
	nl_assert(this->isRailNet());

	const UINT32 masks[4] = { 1, 5, 3, 1 };
	const UINT32 mask = masks[ (m_cur_Q  << 1) | m_new_Q ];

	m_in_queue = 2; /* mark as taken ... */
	m_cur_Q = m_new_Q;
#if 0
	core_terminal_t * t[256];
	core_terminal_t *p = m_list_active.first();
	int cnt = 0;
	while (p != NULL)
	{
		if ((p->state() & mask) != 0)
			t[cnt++] = p;
		p = m_list_active.next(p);
	}

	for (int i=0; i<cnt; i++)
		t[i]->netdev().update_dev();
	core_terminal_t *p = m_list_active.first();

	while (p != NULL)
	{
		p->update_dev(mask);
		p = m_list_active.next(p);
	}

#else
	core_terminal_t *p = m_list_active.first();

	while (p != NULL)
	{
		p->update_dev(mask);
		p = p->m_next;
	}
#endif
}

ATTR_COLD void net_t::reset()
{
	m_time = netlist_time::zero;
	m_active = 0;
	m_in_queue = 2;

	m_new_Q = 0;
	m_cur_Q = 0;
	m_cur_Analog = 0.0;
=======
void detail::net_t::process(unsigned Mask)
{
	for (auto & p : m_list_active)
	{
		p.device().m_stat_call_count.inc();
		if ((p.state() & Mask) != 0)
		{
			p.device().m_stat_total_time.start();
			p.m_delegate();
			p.device().m_stat_total_time.stop();
		}
	}
}

void detail::net_t::update_devs() NL_NOEXCEPT
{
	nl_assert(this->isRailNet());

	const unsigned mask((m_new_Q << core_terminal_t::INP_LH_SHIFT)
			| (m_cur_Q<<core_terminal_t::INP_HL_SHIFT));

	m_in_queue = QS_DELIVERED; /* mark as taken ... */

	switch (mask)
	{
		case core_terminal_t::STATE_INP_HL:
			m_cur_Q = m_new_Q;
			process(core_terminal_t::STATE_INP_HL | core_terminal_t::STATE_INP_ACTIVE);
			break;
		case core_terminal_t::STATE_INP_LH:
			m_cur_Q = m_new_Q;
			process(core_terminal_t::STATE_INP_LH | core_terminal_t::STATE_INP_ACTIVE);
			break;
		default:
			break;
	}
}

void detail::net_t::reset()
{
	m_time = netlist_time::zero();
	m_active = 0;
	m_in_queue = QS_DELIVERED;

	m_new_Q = 0;
	m_cur_Q = 0;

	analog_net_t *p = dynamic_cast<analog_net_t *>(this);

	if (p != nullptr)
		p->m_cur_Analog = 0.0;
>>>>>>> upstream/master

	/* rebuild m_list */

	m_list_active.clear();
<<<<<<< HEAD
	for (std::size_t i=0; i < m_core_terms.size(); i++)
		m_list_active.add(*m_core_terms[i]);

	for (std::size_t i=0; i < m_core_terms.size(); i++)
		m_core_terms[i]->do_reset();

	for (std::size_t i=0; i < m_core_terms.size(); i++)
		if (m_core_terms[i]->state() != logic_t::STATE_INP_PASSIVE)
			m_active++;
}

ATTR_COLD void net_t::register_con(core_terminal_t &terminal)
{
	terminal.set_net(*this);

	m_core_terms.add(&terminal);
=======
	for (core_terminal_t *ct : m_core_terms)
		m_list_active.push_back(ct);

	for (core_terminal_t *ct : m_core_terms)
		ct->reset();

	for (core_terminal_t *ct : m_core_terms)
		if (ct->state() != logic_t::STATE_INP_PASSIVE)
			m_active++;
}

void detail::net_t::add_terminal(detail::core_terminal_t &terminal)
{
	for (auto &t : m_core_terms)
		if (t == &terminal)
			netlist().log().fatal(MF_2_NET_1_DUPLICATE_TERMINAL_2, name(),
					t->name());

	terminal.set_net(this);

	m_core_terms.push_back(&terminal);
>>>>>>> upstream/master

	if (terminal.state() != logic_t::STATE_INP_PASSIVE)
		m_active++;
}

<<<<<<< HEAD
ATTR_COLD void net_t::move_connections(net_t *dest_net)
{
	for (std::size_t i = 0; i < m_core_terms.size(); i++)
	{
		core_terminal_t *p = m_core_terms[i];
		dest_net->register_con(*p);
	}
	m_core_terms.clear();
	m_active = 0;
}

ATTR_COLD void net_t::merge_net(net_t *othernet)
{
	netlist().log().debug("merging nets ...\n");
	if (othernet == NULL)
		return; // Nothing to do

	if (othernet == this)
	{
		netlist().log().warning("Connecting {1} to itself. This may be right, though\n", this->name());
		return; // Nothing to do
	}

	if (this->isRailNet() && othernet->isRailNet())
		netlist().log().fatal("Trying to merge two rail nets: {1} and {2}\n", this->name(), othernet->name());

	if (othernet->isRailNet())
	{
		netlist().log().debug("othernet is railnet\n");
		othernet->merge_net(this);
	}
	else
	{
		othernet->move_connections(this);
	}
}


// ----------------------------------------------------------------------------------------
// netlist_logic_net_t
// ----------------------------------------------------------------------------------------

ATTR_COLD logic_net_t::logic_net_t()
	: net_t(LOGIC)
{
}


ATTR_COLD void logic_net_t::reset()
{
	net_t::reset();
}

ATTR_COLD void logic_net_t::save_register()
{
	net_t::save_register();
}

// ----------------------------------------------------------------------------------------
// netlist_analog_net_t
// ----------------------------------------------------------------------------------------

ATTR_COLD analog_net_t::analog_net_t()
	: net_t(ANALOG)
	, m_DD_n_m_1(0.0)
	, m_h_n_m_1(1e-6)
	, m_solver(NULL)
{
}

ATTR_COLD void analog_net_t::reset()
{
	net_t::reset();
}

ATTR_COLD void analog_net_t::save_register()
{
	save(NLNAME(m_DD_n_m_1));
	save(NLNAME(m_h_n_m_1));
	net_t::save_register();
}

ATTR_COLD bool analog_net_t::already_processed(list_t *groups, int cur_group)
{
	if (isRailNet())
		return true;
	for (int i = 0; i <= cur_group; i++)
	{
		if (groups[i].contains(this))
			return true;
	}
	return false;
}

ATTR_COLD void analog_net_t::process_net(list_t *groups, int &cur_group)
{
	if (num_cons() == 0)
		return;
	/* add the net */
	groups[cur_group].add(this);
	for (std::size_t i = 0; i < m_core_terms.size(); i++)
	{
		core_terminal_t *p = m_core_terms[i];
		if (p->isType(terminal_t::TERMINAL))
		{
			terminal_t *pt = static_cast<terminal_t *>(p);
			analog_net_t *other_net = &pt->m_otherterm->net().as_analog();
			if (!other_net->already_processed(groups, cur_group))
				other_net->process_net(groups, cur_group);
		}
	}
}


// ----------------------------------------------------------------------------------------
// netlist_core_terminal_t
// ----------------------------------------------------------------------------------------

ATTR_COLD core_terminal_t::core_terminal_t(const type_t atype, const family_t afamily)
: device_object_t(atype, afamily)
, plinkedlist_element_t<core_terminal_t>()
, m_net(NULL)
, m_state(STATE_NONEX)
{
}

ATTR_COLD void core_terminal_t::set_net(net_t &anet)
{
	m_net = &anet;
}

// ----------------------------------------------------------------------------------------
// netlist_terminal_t
// ----------------------------------------------------------------------------------------

ATTR_COLD terminal_t::terminal_t()
: core_terminal_t(TERMINAL, ANALOG)
, m_Idr1(NULL)
, m_go1(NULL)
, m_gt1(NULL)
, m_otherterm(NULL)
{
}

ATTR_HOT void terminal_t::schedule_solve()
{
	// FIXME: Remove this after we found a way to remove *ALL* twoterms connected to railnets only.
	if (net().as_analog().solver() != NULL)
		net().as_analog().solver()->update_forced();
}

ATTR_HOT void terminal_t::schedule_after(const netlist_time &after)
{
	// FIXME: Remove this after we found a way to remove *ALL* twoterms connected to railnets only.
	if (net().as_analog().solver() != NULL)
		net().as_analog().solver()->update_after(after);
}

ATTR_COLD void terminal_t::reset()
{
	set_state(STATE_INP_ACTIVE);
	set_ptr(m_Idr1, 0.0);
	set_ptr(m_go1, netlist().gmin());
	set_ptr(m_gt1, netlist().gmin());
}

ATTR_COLD void terminal_t::save_register()
{
	save(NLNAME(m_Idr1));
	save(NLNAME(m_go1));
	save(NLNAME(m_gt1));
	core_terminal_t::save_register();
}


=======
void detail::net_t::remove_terminal(detail::core_terminal_t &terminal)
{
	if (plib::container::contains(m_core_terms, &terminal))
	{
		terminal.set_net(nullptr);
		plib::container::remove(m_core_terms, &terminal);
	}
	else
		netlist().log().fatal(MF_2_REMOVE_TERMINAL_1_FROM_NET_2, terminal.name(),
				this->name());
	if (terminal.state() != logic_t::STATE_INP_PASSIVE)
		m_active--;
}

void detail::net_t::move_connections(detail::net_t &dest_net)
{
	for (auto &ct : m_core_terms)
		dest_net.add_terminal(*ct);
	m_core_terms.clear();
	m_active = 0;
}

// ----------------------------------------------------------------------------------------
// logic_net_t
// ----------------------------------------------------------------------------------------

logic_net_t::logic_net_t(netlist_t &nl, const pstring &aname, detail::core_terminal_t *mr)
	: net_t(nl, aname, mr)
{
}

logic_net_t::~logic_net_t()
{
}

// ----------------------------------------------------------------------------------------
// analog_net_t
// ----------------------------------------------------------------------------------------

analog_net_t::analog_net_t(netlist_t &nl, const pstring &aname, detail::core_terminal_t *mr)
	: net_t(nl, aname, mr)
	, m_cur_Analog(*this, "m_cur_Analog", 0.0)
	, m_solver(nullptr)
{
}

analog_net_t::~analog_net_t()
{
}

// ----------------------------------------------------------------------------------------
// core_terminal_t
// ----------------------------------------------------------------------------------------

detail::core_terminal_t::core_terminal_t(core_device_t &dev, const pstring &aname,
		const state_e state, nldelegate delegate)
: device_object_t(dev, dev.name() + "." + aname)
, plib::linkedlist_t<core_terminal_t>::element_t()
, m_delegate(delegate)
, m_net(nullptr)
, m_state(*this, "m_state", state)
{
}

detail::core_terminal_t::~core_terminal_t()
{
}

void detail::core_terminal_t::reset()
{
	if (is_type(OUTPUT))
		set_state(STATE_OUT);
	else
		set_state(STATE_INP_ACTIVE);
}

void detail::core_terminal_t::set_net(net_t *anet)
{
	m_net = anet;
}

void detail::core_terminal_t::clear_net()
{
	m_net = nullptr;
}

analog_t::analog_t(core_device_t &dev, const pstring &aname, const state_e state)
: core_terminal_t(dev, aname, state)
{
}

analog_t::~analog_t()
{
}

logic_t::logic_t(core_device_t &dev, const pstring &aname, const state_e state,
		nldelegate delegate)
	: core_terminal_t(dev, aname, state, delegate)
	, logic_family_t()
	, m_proxy(nullptr)
{
}

logic_t::~logic_t()
{
}

// ----------------------------------------------------------------------------------------
// terminal_t
// ----------------------------------------------------------------------------------------

terminal_t::terminal_t(core_device_t &dev, const pstring &aname)
: analog_t(dev, aname, STATE_BIDIR)
, m_otherterm(nullptr)
, m_Idr1(nullptr)
, m_go1(nullptr)
, m_gt1(nullptr)
{
	netlist().setup().register_term(*this);
}

terminal_t::~terminal_t()
{
}

void terminal_t::solve_now()
{
	// Nets may belong to railnets which do not have a solver attached
	if (this->has_net())
		if (net().solver() != nullptr)
			net().solver()->update_forced();
}

void terminal_t::schedule_solve_after(const netlist_time &after)
{
	// Nets may belong to railnets which do not have a solver attached
	if (this->has_net())
		if (net().solver() != nullptr)
			net().solver()->update_after(after);
}

>>>>>>> upstream/master
// ----------------------------------------------------------------------------------------
// net_input_t
// ----------------------------------------------------------------------------------------

// ----------------------------------------------------------------------------------------
// net_output_t
// ----------------------------------------------------------------------------------------

// ----------------------------------------------------------------------------------------
<<<<<<< HEAD
// netlist_logic_output_t
// ----------------------------------------------------------------------------------------

ATTR_COLD logic_output_t::logic_output_t()
	: logic_t(OUTPUT)
{
	set_state(STATE_OUT);
	this->set_net(m_my_net);
}

ATTR_COLD void logic_output_t::init_object(core_device_t &dev, const pstring &aname)
{
	core_terminal_t::init_object(dev, aname);
	net().init_object(dev.netlist(), aname + ".net");
	net().register_railterminal(*this);
}

ATTR_COLD void logic_output_t::initial(const netlist_sig_t val)
{
	net().as_logic().initial(val);
}


// ----------------------------------------------------------------------------------------
// netlist_analog_output_t
// ----------------------------------------------------------------------------------------

ATTR_COLD analog_output_t::analog_output_t()
	: netlist_analog_t(OUTPUT), m_proxied_net(NULL)
{
	this->set_net(m_my_net);
	set_state(STATE_OUT);

	net().as_analog().m_cur_Analog = NL_FCONST(0.99);
}

ATTR_COLD void analog_output_t::init_object(core_device_t &dev, const pstring &aname)
{
	core_terminal_t::init_object(dev, aname);
	net().init_object(dev.netlist(), aname + ".net");
	net().register_railterminal(*this);
}

ATTR_COLD void analog_output_t::initial(const nl_double val)
{
	net().as_analog().m_cur_Analog = val;
}

// ----------------------------------------------------------------------------------------
// netlist_param_t & friends
// ----------------------------------------------------------------------------------------

ATTR_COLD param_t::param_t(const param_type_t atype)
	: device_object_t(PARAM, ANALOG)
	, m_param_type(atype)
{
}

ATTR_COLD const pstring param_model_t::model_type()
=======
// logic_output_t
// ----------------------------------------------------------------------------------------

logic_output_t::logic_output_t(core_device_t &dev, const pstring &aname)
	: logic_t(dev, aname, STATE_OUT)
	, m_my_net(dev.netlist(), name() + ".net", this)
{
	this->set_net(&m_my_net);
	netlist().m_nets.push_back(plib::owned_ptr<logic_net_t>(&m_my_net, false));
	set_logic_family(dev.logic_family());
	netlist().setup().register_term(*this);
}

logic_output_t::~logic_output_t()
{
}

void logic_output_t::initial(const netlist_sig_t val)
{
	if (has_net())
		net().initial(val);
}

// ----------------------------------------------------------------------------------------
// analog_input_t
// ----------------------------------------------------------------------------------------

analog_input_t::analog_input_t(core_device_t &dev, const pstring &aname)
: analog_t(dev, aname, STATE_INP_ACTIVE)
{
	netlist().setup().register_term(*this);
}

analog_input_t::~analog_input_t()
{
}

// ----------------------------------------------------------------------------------------
// analog_output_t
// ----------------------------------------------------------------------------------------

analog_output_t::analog_output_t(core_device_t &dev, const pstring &aname)
	: analog_t(dev, aname, STATE_OUT)
	, m_my_net(dev.netlist(), name() + ".net", this)
{
	netlist().m_nets.push_back(plib::owned_ptr<analog_net_t>(&m_my_net, false));
	this->set_net(&m_my_net);

	//net().m_cur_Analog = NL_FCONST(0.0);
	netlist().setup().register_term(*this);
}

analog_output_t::~analog_output_t()
{
}

void analog_output_t::initial(const nl_double val)
{
	net().set_Q_Analog(val);
}

// -----------------------------------------------------------------------------
// logic_input_t
// -----------------------------------------------------------------------------

logic_input_t::logic_input_t(core_device_t &dev, const pstring &aname,
		nldelegate delegate)
		: logic_t(dev, aname, STATE_INP_ACTIVE, delegate)
{
	set_logic_family(dev.logic_family());
	netlist().setup().register_term(*this);
}

logic_input_t::~logic_input_t()
{
}

// ----------------------------------------------------------------------------------------
// Parameters ...
// ----------------------------------------------------------------------------------------

param_t::param_t(device_t &device, const pstring &name)
	: device_object_t(device, device.name() + "." + name)
{
	device.setup().register_param(this->name(), *this);
}

param_t::~param_t()
{
}

param_t::param_type_t param_t::param_type() const
{
	if (dynamic_cast<const param_str_t *>(this) != nullptr)
		return STRING;
	else if (dynamic_cast<const param_double_t *>(this) != nullptr)
		return DOUBLE;
	else if (dynamic_cast<const param_int_t *>(this) != nullptr)
		return INTEGER;
	else if (dynamic_cast<const param_logic_t *>(this) != nullptr)
		return LOGIC;
	else if (dynamic_cast<const param_ptr_t *>(this) != nullptr)
		return POINTER;
	else
	{
		netlist().log().fatal(MF_1_UNKNOWN_PARAM_TYPE, name());
		return POINTER; /* Please compiler */
	}
}


void param_t::update_param()
{
	device().update_param();
	if (device().needs_update_after_param_change())
		device().update_dev();
}

const pstring param_model_t::model_type()
>>>>>>> upstream/master
{
	if (m_map.size() == 0)
		netlist().setup().model_parse(this->Value(), m_map);
	return m_map["COREMODEL"];
}

<<<<<<< HEAD

ATTR_COLD const pstring param_model_t::model_value_str(const pstring &entity)
{
	if (m_map.size() == 0)
		netlist().setup().model_parse(this->Value(), m_map);
	return netlist().setup().model_value_str(m_map, entity);
}

ATTR_COLD nl_double param_model_t::model_value(const pstring &entity)
{
	if (m_map.size() == 0)
		netlist().setup().model_parse(this->Value(), m_map);
	return netlist().setup().model_value(m_map, entity);
}

} // namespace

NETLIB_NAMESPACE_DEVICES_START()

// ----------------------------------------------------------------------------------------
// mainclock
// ----------------------------------------------------------------------------------------

ATTR_HOT /* inline */ void NETLIB_NAME(mainclock)::mc_update(logic_net_t &net)
{
	net.toggle_new_Q();
	net.update_devs();
}

NETLIB_START(mainclock)
{
	register_output("Q", m_Q);

	register_param("FREQ", m_freq, 7159000.0 * 5);
	m_inc = netlist_time::from_hz(m_freq.Value()*2);
}

NETLIB_RESET(mainclock)
{
	m_Q.net().set_time(netlist_time::zero);
}

NETLIB_UPDATE_PARAM(mainclock)
{
	m_inc = netlist_time::from_hz(m_freq.Value()*2);
}

NETLIB_UPDATE(mainclock)
{
	logic_net_t &net = m_Q.net().as_logic();
	// this is only called during setup ...
	net.toggle_new_Q();
	net.set_time(netlist().time() + m_inc);
}

NETLIB_NAMESPACE_DEVICES_END()
=======
param_str_t::param_str_t(device_t &device, const pstring &name, const pstring &val)
: param_t(device, name)
{
	m_param = device.setup().get_initial_param_val(this->name(),val);
}

param_str_t::~param_str_t()
{
}

void param_str_t::changed()
{
}

param_double_t::param_double_t(device_t &device, const pstring &name, const double val)
: param_t(device, name)
{
	m_param = device.setup().get_initial_param_val(this->name(),val);
	netlist().save(*this, m_param, "m_param");
}

param_int_t::param_int_t(device_t &device, const pstring &name, const int val)
: param_t(device, name)
{
	m_param = device.setup().get_initial_param_val(this->name(),val);
	netlist().save(*this, m_param, "m_param");
}

param_logic_t::param_logic_t(device_t &device, const pstring &name, const bool val)
: param_t(device, name)
{
	m_param = device.setup().get_initial_param_val(this->name(),val);
	netlist().save(*this, m_param, "m_param");
}

param_ptr_t::param_ptr_t(device_t &device, const pstring &name, uint8_t * val)
: param_t(device, name)
{
	m_param = val; //device.setup().get_initial_param_val(this->name(),val);
	//netlist().save(*this, m_param, "m_param");
}

void param_model_t::changed()
{
	netlist().log().fatal(MF_1_MODEL_1_CAN_NOT_BE_CHANGED_AT_RUNTIME, name());
	m_map.clear();
}

const pstring param_model_t::model_value_str(const pstring &entity)
{
	if (m_map.size() == 0)
		netlist().setup().model_parse(this->Value(), m_map);
	return netlist().setup().model_value_str(m_map, entity);
}

nl_double param_model_t::model_value(const pstring &entity)
{
	if (m_map.size() == 0)
		netlist().setup().model_parse(this->Value(), m_map);
	return netlist().setup().model_value(m_map, entity);
}

param_data_t::param_data_t(device_t &device, const pstring &name)
: param_str_t(device, name, "")
{
}

void param_data_t::changed()
{
}

std::unique_ptr<plib::pistream> param_data_t::stream()
{
	return device().netlist().setup().get_data_stream(Value());
}

	namespace devices
	{
	// ----------------------------------------------------------------------------------------
	// mainclock
	// ----------------------------------------------------------------------------------------

	void NETLIB_NAME(mainclock)::mc_update(logic_net_t &net)
	{
		net.toggle_new_Q();
		net.update_devs();
	}


	} //namespace devices

	bool detail::core_terminal_t::is_logic() const NL_NOEXCEPT
	{
		return dynamic_cast<const logic_t *>(this) != nullptr;
	}

	bool detail::core_terminal_t::is_analog() const NL_NOEXCEPT
	{
		return dynamic_cast<const analog_t *>(this) != nullptr;
	}

	bool detail::net_t::is_logic() const NL_NOEXCEPT
	{
		return dynamic_cast<const logic_net_t *>(this) != nullptr;
	}

	bool detail::net_t::is_analog() const NL_NOEXCEPT
	{
		return dynamic_cast<const analog_net_t *>(this) != nullptr;
	}


} // namespace netlist
>>>>>>> upstream/master
