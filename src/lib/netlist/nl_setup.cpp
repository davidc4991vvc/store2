// license:GPL-2.0+
// copyright-holders:Couriersud
/*
 * nlsetup.c
 *
 */

<<<<<<< HEAD
#include <cstdio>

#include "solver/nld_solver.h"

#include "plib/palloc.h"
#include "nl_base.h"
#include "nl_setup.h"
#include "nl_parser.h"
#include "nl_util.h"
#include "nl_factory.h"
#include "devices/net_lib.h"
#include "devices/nld_system.h"
#include "analog/nld_twoterm.h"

static NETLIST_START(base)
	TTL_INPUT(ttlhigh, 1)
	TTL_INPUT(ttllow, 0)
	NET_REGISTER_DEV(GND, GND)
	NET_REGISTER_DEV(PARAMETER, NETLIST)

	LOCAL_SOURCE(diode_models)
	LOCAL_SOURCE(bjt_models)
	LOCAL_SOURCE(family_models)
	LOCAL_SOURCE(TTL74XX_lib)
	LOCAL_SOURCE(CD4XXX_lib)
	LOCAL_SOURCE(OPAMP_lib)
	LOCAL_SOURCE(otheric_lib)

	INCLUDE(diode_models);
	INCLUDE(bjt_models);
	INCLUDE(family_models);
	INCLUDE(TTL74XX_lib);
	INCLUDE(CD4XXX_lib);
	INCLUDE(OPAMP_lib);
	INCLUDE(otheric_lib);

NETLIST_END()

=======
#include "plib/palloc.h"
#include "plib/putil.h"
#include "nl_base.h"
#include "nl_setup.h"
#include "nl_parser.h"
#include "nl_factory.h"
#include "devices/nlid_system.h"
#include "devices/nlid_proxy.h"
#include "analog/nld_twoterm.h"
#include "solver/nld_solver.h"
#include "devices/nlid_truthtable.h"
>>>>>>> upstream/master

// ----------------------------------------------------------------------------------------
// setup_t
// ----------------------------------------------------------------------------------------

namespace netlist
{
<<<<<<< HEAD
setup_t::setup_t(netlist_t *netlist)
	: m_netlist(netlist)
	, m_proxy_cnt(0)
{
	netlist->set_setup(this);
	m_factory = palloc(factory_list_t(*this));
}

void setup_t::init()
{
	initialize_factory(factory());
	NETLIST_NAME(base)(*this);
}


=======
setup_t::setup_t(netlist_t &netlist)
	: m_netlist(netlist)
	, m_factory(*this)
	, m_proxy_cnt(0)
	, m_frontier_cnt(0)
{
	devices::initialize_factory(m_factory);
}

>>>>>>> upstream/master
setup_t::~setup_t()
{
	m_links.clear();
	m_alias.clear();
	m_params.clear();
	m_terminals.clear();
<<<<<<< HEAD
	m_params_temp.clear();

	netlist().set_setup(NULL);
	pfree(m_factory);
	m_sources.clear_and_free();

	pstring::resetmem();
}

ATTR_COLD pstring setup_t::build_fqn(const pstring &obj_name) const
{
	if (m_stack.empty())
		return netlist().name() + "." + obj_name;
	else
		return m_stack.peek() + "." + obj_name;
=======
	m_param_values.clear();

	m_sources.clear();
}

pstring setup_t::build_fqn(const pstring &obj_name) const
{
	if (m_namespace_stack.empty())
		//return netlist().name() + "." + obj_name;
		return obj_name;
	else
		return m_namespace_stack.top() + "." + obj_name;
>>>>>>> upstream/master
}

void setup_t::namespace_push(const pstring &aname)
{
<<<<<<< HEAD
	if (m_stack.empty())
		m_stack.push(netlist().name() + "." + aname);
	else
		m_stack.push(m_stack.peek() + "." + aname);
=======
	if (m_namespace_stack.empty())
		//m_namespace_stack.push(netlist().name() + "." + aname);
		m_namespace_stack.push(aname);
	else
		m_namespace_stack.push(m_namespace_stack.top() + "." + aname);
>>>>>>> upstream/master
}

void setup_t::namespace_pop()
{
<<<<<<< HEAD
	m_stack.pop();
}


device_t *setup_t::register_dev(device_t *dev, const pstring &name)
{
	pstring fqn = build_fqn(name);

	dev->init(netlist(), fqn);

	if (!(netlist().m_devices.add(dev, false)==true))
		log().fatal("Error adding {1} to device list\n", name);
	return dev;
}

void setup_t::register_lib_entry(const pstring &name)
{
	if (m_lib.contains(name))
		log().warning("Lib entry collection already contains {1}. IGNORED", name);
	else
		m_lib.add(name);
}

device_t *setup_t::register_dev(const pstring &classname, const pstring &name)
{
	if (m_lib.contains(classname))
	{
		namespace_push(name);
		include(classname);
		namespace_pop();
		return NULL;
	}
	else
	{
		device_t *dev = factory().new_device_by_name(classname);
		//device_t *dev = factory().new_device_by_classname(classname);
		if (dev == NULL)
			log().fatal("Class {1} not found!\n", classname);
		return register_dev(dev, name);
	}
}

void setup_t::register_model(const pstring &model_in)
{
	int pos = model_in.find(" ");
	if (pos < 0)
		log().fatal("Unable to parse model: {1}", model_in);
	pstring model = model_in.left(pos).trim().ucase();
	pstring def = model_in.substr(pos + 1).trim();
	if (!m_models.add(model, def))
		log().fatal("Model already exists: {1}", model_in);
=======
	m_namespace_stack.pop();
}

void setup_t::register_lib_entry(const pstring &name, const pstring &sourcefile)
{
	factory().register_device(plib::make_unique_base<factory::element_t, factory::library_element_t>(*this, name, name, "", sourcefile));
}

void setup_t::register_dev(const pstring &classname, const pstring &name)
{
	auto f = factory().factory_by_name(classname);
	if (f == nullptr)
		log().fatal(MF_1_CLASS_1_NOT_FOUND, classname);
	/* make sure we parse macro library entries */
	f->macro_actions(netlist(), name);
	m_device_factory.push_back(std::pair<pstring, factory::element_t *>(build_fqn(name), f));
}

bool setup_t::device_exists(const pstring &name) const
{
	for (auto e : m_device_factory)
	{
		if (e.first == name)
			return true;
	}
	return false;
}


void setup_t::register_model(const pstring &model_in)
{
	auto pos = model_in.find(" ");
	if (pos == pstring::npos)
		log().fatal(MF_1_UNABLE_TO_PARSE_MODEL_1, model_in);
	pstring model = model_in.left(pos).trim().ucase();
	pstring def = model_in.substr(pos + 1).trim();
	if (!m_models.insert({model, def}).second)
		log().fatal(MF_1_MODEL_ALREADY_EXISTS_1, model_in);
>>>>>>> upstream/master
}

void setup_t::register_alias_nofqn(const pstring &alias, const pstring &out)
{
<<<<<<< HEAD
	if (!m_alias.add(alias, out))
		log().fatal("Error adding alias {1} to alias list\n", alias);
=======
	if (!m_alias.insert({alias, out}).second)
		log().fatal(MF_1_ADDING_ALI1_TO_ALIAS_LIST, alias);
>>>>>>> upstream/master
}

void setup_t::register_alias(const pstring &alias, const pstring &out)
{
	pstring alias_fqn = build_fqn(alias);
	pstring out_fqn = build_fqn(out);
	register_alias_nofqn(alias_fqn, out_fqn);
}

void setup_t::register_dippins_arr(const pstring &terms)
{
<<<<<<< HEAD
	pstring_list_t list(terms,", ");
	if (list.size() == 0 || (list.size() % 2) == 1)
		log().fatal("You must pass an equal number of pins to DIPPINS");
	unsigned n = list.size();
	for (unsigned i = 0; i < n / 2; i++)
	{
		register_alias(pfmt("{1}")(i+1), list[i * 2]);
		register_alias(pfmt("{1}")(n-i), list[i * 2 + 1]);
	}
}

pstring setup_t::objtype_as_astr(object_t &in) const
{
	switch (in.type())
	{
		case terminal_t::TERMINAL:
			return "TERMINAL";
		case terminal_t::INPUT:
			return "INPUT";
		case terminal_t::OUTPUT:
			return "OUTPUT";
		case terminal_t::NET:
			return "NET";
		case terminal_t::PARAM:
			return "PARAM";
		case terminal_t::DEVICE:
			return "DEVICE";
		case terminal_t::NETLIST:
			return "NETLIST";
		case terminal_t::QUEUE:
			return "QUEUE";
	}
	// FIXME: noreturn
	log().fatal("Unknown object type {1}\n", (unsigned) in.type());
	return "Error";
}


void setup_t::register_object(device_t &dev, const pstring &name, object_t &obj)
{
	switch (obj.type())
	{
		case terminal_t::TERMINAL:
		case terminal_t::INPUT:
		case terminal_t::OUTPUT:
			{
				core_terminal_t &term = dynamic_cast<core_terminal_t &>(obj);
				if (obj.isType(terminal_t::OUTPUT))
				{
					if (obj.isFamily(terminal_t::LOGIC))
						dynamic_cast<logic_output_t &>(term).init_object(dev, dev.name() + "." + name);
					else if (obj.isFamily(terminal_t::ANALOG))
						dynamic_cast<analog_output_t &>(term).init_object(dev, dev.name() + "." + name);
					else
						log().fatal("Error adding {1} {2} to terminal list, neither LOGIC nor ANALOG\n", objtype_as_astr(term), term.name());
				}
				else
					term.init_object(dev, dev.name() + "." + name);

				if (!m_terminals.add(term.name(), &term))
					log().fatal("Error adding {1} {2} to terminal list\n", objtype_as_astr(term), term.name());
				log().debug("{1} {2}\n", objtype_as_astr(term), name);
			}
			break;
		case terminal_t::NET:
			break;
		case terminal_t::PARAM:
			{
				param_t &param = dynamic_cast<param_t &>(obj);
				//printf("name: {1}\n", name);
				if (m_params_temp.contains(name))
				{
					const pstring val = m_params_temp[name];
					switch (param.param_type())
					{
						case param_t::DOUBLE:
						{
							log().debug("Found parameter ... {1} : {1}\n", name, val);
							double vald = 0;
							if (sscanf(val.cstr(), "%lf", &vald) != 1)
								log().fatal("Invalid number conversion {1} : {2}\n", name, val);
							dynamic_cast<param_double_t &>(param).initial(vald);
						}
						break;
						case param_t::INTEGER:
						case param_t::LOGIC:
						{
							log().debug("Found parameter ... {1} : {2}\n", name, val);
							double vald = 0;
							if (sscanf(val.cstr(), "%lf", &vald) != 1)
								log().fatal("Invalid number conversion {1} : {2}\n", name, val);
							dynamic_cast<param_int_t &>(param).initial((int) vald);
						}
						break;
						case param_t::STRING:
						{
							dynamic_cast<param_str_t &>(param).initial(val);
						}
						break;
						case param_t::MODEL:
							//dynamic_cast<param_model_t &>(param).initial(val);
							dynamic_cast<param_model_t &>(param).initial(val);
							break;
						default:
							log().fatal("Parameter is not supported {1} : {2}\n", name, val);
					}
				}
				if (!m_params.add(param.name(), &param))
					log().fatal("Error adding parameter {1} to parameter list\n", name);
			}
			break;
		case terminal_t::DEVICE:
			log().fatal("Device registration not yet supported - {1}\n", name);
			break;
		case terminal_t::NETLIST:
			log().fatal("Netlist registration not yet supported - {1}\n", name);
			break;
		case terminal_t::QUEUE:
			log().fatal("QUEUE registration not yet supported - {1}\n", name);
			break;
	}
=======
	std::vector<pstring> list(plib::psplit(terms,", "));
	if (list.size() == 0 || (list.size() % 2) == 1)
		log().fatal(MF_1_DIP_PINS_MUST_BE_AN_EQUAL_NUMBER_OF_PINS_1,
				build_fqn(""));
	std::size_t n = list.size();
	for (std::size_t i = 0; i < n / 2; i++)
	{
		register_alias(plib::pfmt("{1}")(i+1), list[i * 2]);
		register_alias(plib::pfmt("{1}")(n-i), list[i * 2 + 1]);
	}
}

pstring setup_t::termtype_as_str(detail::core_terminal_t &in) const
{
	switch (in.type())
	{
		case detail::terminal_type::TERMINAL:
			return pstring("TERMINAL");
		case detail::terminal_type::INPUT:
			return pstring("INPUT");
		case detail::terminal_type::OUTPUT:
			return pstring("OUTPUT");
	}
	log().fatal(MF_1_UNKNOWN_OBJECT_TYPE_1, static_cast<unsigned>(in.type()));
	return pstring("Error");
}

pstring setup_t::get_initial_param_val(const pstring &name, const pstring &def)
{
	auto i = m_param_values.find(name);
	if (i != m_param_values.end())
		return i->second;
	else
		return def;
}

double setup_t::get_initial_param_val(const pstring &name, const double def)
{
	auto i = m_param_values.find(name);
	if (i != m_param_values.end())
	{
		double vald = 0;
		if (sscanf(i->second.c_str(), "%lf", &vald) != 1)
			log().fatal(MF_2_INVALID_NUMBER_CONVERSION_1_2, name, i->second);
		return vald;
	}
	else
		return def;
}

int setup_t::get_initial_param_val(const pstring &name, const int def)
{
	auto i = m_param_values.find(name);
	if (i != m_param_values.end())
	{
		double vald = 0;
		if (sscanf(i->second.c_str(), "%lf", &vald) != 1)
			log().fatal(MF_2_INVALID_NUMBER_CONVERSION_1_2, name, i->second);
		return static_cast<int>(vald);
	}
	else
		return def;
}

void setup_t::register_param(const pstring &name, param_t &param)
{
	if (!m_params.insert({param.name(), param_ref_t(param.name(), param.device(), param)}).second)
		log().fatal(MF_1_ADDING_PARAMETER_1_TO_PARAMETER_LIST, name);
}

void setup_t::register_term(detail::core_terminal_t &term)
{
	if (!m_terminals.insert({term.name(), &term}).second)
		log().fatal(MF_2_ADDING_1_2_TO_TERMINAL_LIST, termtype_as_str(term),
				term.name());
	log().debug("{1} {2}\n", termtype_as_str(term), term.name());
>>>>>>> upstream/master
}

void setup_t::register_link_arr(const pstring &terms)
{
<<<<<<< HEAD
	pstring_list_t list(terms,", ");
	if (list.size() < 2)
		log().fatal("You must pass at least 2 terminals to NET_C");
=======
	std::vector<pstring> list(plib::psplit(terms,", "));
	if (list.size() < 2)
		log().fatal(MF_2_NET_C_NEEDS_AT_LEAST_2_TERMINAL);
>>>>>>> upstream/master
	for (std::size_t i = 1; i < list.size(); i++)
	{
		register_link(list[0], list[i]);
	}
}


void setup_t::register_link_fqn(const pstring &sin, const pstring &sout)
{
	link_t temp = link_t(sin, sout);
	log().debug("link {1} <== {2}\n", sin, sout);
<<<<<<< HEAD
	m_links.add(temp);
=======
	m_links.push_back(temp);
>>>>>>> upstream/master
}

void setup_t::register_link(const pstring &sin, const pstring &sout)
{
	register_link_fqn(build_fqn(sin), build_fqn(sout));
}

<<<<<<< HEAD
void setup_t::remove_connections(const pstring pin)
{
	pstring pinfn = build_fqn(pin);
	bool found = false;
	for (std::size_t i = 0; i < m_links.size(); i++)
	{
		if ((m_links[i].e1 == pinfn) || (m_links[i].e2 == pinfn))
		{
			log().verbose("removing connection: {1} <==> {2}\n", m_links[i].e1, m_links[i].e2);
			m_links.remove_at(i);
			found = true;
		}
	}
	if (!found)
		log().fatal("remove_connections: found no occurrence of {1}\n", pin);
}


void setup_t::register_frontier(const pstring attach, const double r_IN, const double r_OUT)
{
	static int frontier_cnt = 0;
	pstring frontier_name = pfmt("frontier_{1}")(frontier_cnt);
	frontier_cnt++;
	device_t *front = register_dev("FRONTIER_DEV", frontier_name);
=======
void setup_t::remove_connections(const pstring &pin)
{
	pstring pinfn = build_fqn(pin);
	bool found = false;

	for (auto link = m_links.begin(); link != m_links.end(); )
	{
		if ((link->first == pinfn) || (link->second == pinfn))
		{
			log().verbose("removing connection: {1} <==> {2}\n", link->first, link->second);
			link = m_links.erase(link);
			found = true;
		}
		else
			link++;
	}
	if (!found)
		log().fatal(MF_1_FOUND_NO_OCCURRENCE_OF_1, pin);
}


void setup_t::register_frontier(const pstring &attach, const double r_IN, const double r_OUT)
{
	pstring frontier_name = plib::pfmt("frontier_{1}")(m_frontier_cnt);
	m_frontier_cnt++;
	register_dev("FRONTIER_DEV", frontier_name);
>>>>>>> upstream/master
	register_param(frontier_name + ".RIN", r_IN);
	register_param(frontier_name + ".ROUT", r_OUT);
	register_link(frontier_name + ".G", "GND");
	pstring attfn = build_fqn(attach);
<<<<<<< HEAD
	bool found = false;
	for (std::size_t i = 0; i < m_links.size(); i++)
	{
		if (m_links[i].e1 == attfn)
		{
			m_links[i].e1 = front->name() + ".I";
			found = true;
		}
		else if (m_links[i].e2 == attfn)
		{
			m_links[i].e2 = front->name() + ".I";
=======
	pstring front_fqn = build_fqn(frontier_name);
	bool found = false;
	for (auto & link  : m_links)
	{
		if (link.first == attfn)
		{
			link.first = front_fqn + ".I";
			found = true;
		}
		else if (link.second == attfn)
		{
			link.second = front_fqn + ".I";
>>>>>>> upstream/master
			found = true;
		}
	}
	if (!found)
<<<<<<< HEAD
		log().fatal("Frontier setup: found no occurrence of {1}\n", attach);
=======
		log().fatal(MF_1_FOUND_NO_OCCURRENCE_OF_1, attach);
>>>>>>> upstream/master
	register_link(attach, frontier_name + ".Q");
}


void setup_t::register_param(const pstring &param, const double value)
{
<<<<<<< HEAD
	// FIXME: there should be a better way
	register_param(param, pfmt("{1}").e(value,".9"));
=======
	register_param(param, plib::pfmt("{1:.9}").e(value));
>>>>>>> upstream/master
}

void setup_t::register_param(const pstring &param, const pstring &value)
{
	pstring fqn = build_fqn(param);

<<<<<<< HEAD
	int idx = m_params_temp.index_of(fqn);
	if (idx < 0)
	{
		if (!m_params_temp.add(fqn, value))
			log().fatal("Unexpected error adding parameter {1} to parameter list\n", param);
	}
	else
	{
		log().warning("Overwriting {1} old <{2}> new <{3}>\n", fqn, m_params_temp.value_at(idx), value);
		m_params_temp[fqn] = value;
=======
	auto idx = m_param_values.find(fqn);
	if (idx == m_param_values.end())
	{
		if (!m_param_values.insert({fqn, value}).second)
			log().fatal(MF_1_ADDING_PARAMETER_1_TO_PARAMETER_LIST,
					param);
	}
	else
	{
		log().warning(MW_3_OVERWRITING_PARAM_1_OLD_2_NEW_3, fqn, idx->second,
				value);
		m_param_values[fqn] = value;
>>>>>>> upstream/master
	}
}

const pstring setup_t::resolve_alias(const pstring &name) const
{
	pstring temp = name;
	pstring ret;

	/* FIXME: Detect endless loop */
	do {
		ret = temp;
<<<<<<< HEAD
		int p = m_alias.index_of(ret);
		temp = (p>=0 ? m_alias.value_at(p) : "");
	} while (temp != "");
=======
		auto p = m_alias.find(ret);
		temp = (p != m_alias.end() ? p->second : "");
	} while (temp != "" && temp != ret);
>>>>>>> upstream/master

	log().debug("{1}==>{2}\n", name, ret);
	return ret;
}

<<<<<<< HEAD
core_terminal_t *setup_t::find_terminal(const pstring &terminal_in, bool required)
{
	const pstring &tname = resolve_alias(terminal_in);
	int ret;

	ret = m_terminals.index_of(tname);
	/* look for default */
	if (ret < 0)
	{
		/* look for ".Q" std output */
		ret = m_terminals.index_of(tname + ".Q");
	}

	core_terminal_t *term = (ret < 0 ? NULL : m_terminals.value_at(ret));

	if (term == NULL && required)
		log().fatal("terminal {1}({2}) not found!\n", terminal_in, tname);
	if (term != NULL)
=======
detail::core_terminal_t *setup_t::find_terminal(const pstring &terminal_in, bool required)
{
	const pstring &tname = resolve_alias(terminal_in);
	auto ret = m_terminals.find(tname);
	/* look for default */
	if (ret == m_terminals.end())
	{
		/* look for ".Q" std output */
		ret = m_terminals.find(tname + ".Q");
	}

	detail::core_terminal_t *term = (ret == m_terminals.end() ? nullptr : ret->second);

	if (term == nullptr && required)
		log().fatal(MF_2_TERMINAL_1_2_NOT_FOUND, terminal_in, tname);
	if (term != nullptr)
>>>>>>> upstream/master
		log().debug("Found input {1}\n", tname);
	return term;
}

<<<<<<< HEAD
core_terminal_t *setup_t::find_terminal(const pstring &terminal_in, object_t::type_t atype, bool required)
{
	const pstring &tname = resolve_alias(terminal_in);
	int ret;

	ret = m_terminals.index_of(tname);
	/* look for default */
	if (ret < 0 && atype == object_t::OUTPUT)
	{
		/* look for ".Q" std output */
		ret = m_terminals.index_of(tname + ".Q");
	}
	if (ret < 0 && required)
		log().fatal("terminal {1}({2}) not found!\n", terminal_in, tname);

	core_terminal_t *term = (ret < 0 ? NULL : m_terminals.value_at(ret));

	if (term != NULL && term->type() != atype)
	{
		if (required)
			log().fatal("object {1}({2}) found but wrong type\n", terminal_in, tname);
		else
			term = NULL;
	}
	if (term != NULL)
=======
detail::core_terminal_t *setup_t::find_terminal(const pstring &terminal_in,
		detail::terminal_type atype, bool required)
{
	const pstring &tname = resolve_alias(terminal_in);
	auto ret = m_terminals.find(tname);
	/* look for default */
	if (ret == m_terminals.end() && atype == detail::terminal_type::OUTPUT)
	{
		/* look for ".Q" std output */
		ret = m_terminals.find(tname + ".Q");
	}
	if (ret == m_terminals.end() && required)
		log().fatal(MF_2_TERMINAL_1_2_NOT_FOUND, terminal_in, tname);

	detail::core_terminal_t *term = (ret == m_terminals.end() ? nullptr : ret->second);

	if (term != nullptr && term->type() != atype)
	{
		if (required)
			log().fatal(MF_2_OBJECT_1_2_WRONG_TYPE, terminal_in, tname);
		else
			term = nullptr;
	}
	if (term != nullptr)
>>>>>>> upstream/master
		log().debug("Found input {1}\n", tname);

	return term;
}

<<<<<<< HEAD
param_t *setup_t::find_param(const pstring &param_in, bool required)
=======
param_t *setup_t::find_param(const pstring &param_in, bool required) const
>>>>>>> upstream/master
{
	const pstring param_in_fqn = build_fqn(param_in);

	const pstring &outname = resolve_alias(param_in_fqn);
<<<<<<< HEAD
	int ret;

	ret = m_params.index_of(outname);
	if (ret < 0 && required)
		log().fatal("parameter {1}({2}) not found!\n", param_in_fqn, outname);
	if (ret != -1)
		log().debug("Found parameter {1}\n", outname);
	return (ret == -1 ? NULL : m_params.value_at(ret));
}

// FIXME avoid dynamic cast here
devices::nld_base_proxy *setup_t::get_d_a_proxy(core_terminal_t &out)
{
	nl_assert(out.isFamily(terminal_t::LOGIC));

	//printf("proxy for {1}\n", out.name());;
	logic_output_t &out_cast = dynamic_cast<logic_output_t &>(out);
	devices::nld_base_proxy *proxy = out_cast.get_proxy();

	if (proxy == NULL)
	{
		// create a new one ...
		devices::nld_base_d_to_a_proxy *new_proxy = out_cast.logic_family()->create_d_a_proxy(&out_cast);
		pstring x = pfmt("proxy_da_{1}_{2}")(out.name())(m_proxy_cnt);
		m_proxy_cnt++;

		register_dev(new_proxy, x);
		new_proxy->start_dev();

#if 1
		/* connect all existing terminals to new net */

		for (std::size_t i = 0; i < out.net().m_core_terms.size(); i++)
		{
			core_terminal_t *p = out.net().m_core_terms[i];
			p->clear_net(); // de-link from all nets ...
			if (!connect(new_proxy->proxy_term(), *p))
				log().fatal("Error connecting {1} to {2}\n", new_proxy->proxy_term().name(), (*p).name());
		}
		out.net().m_core_terms.clear(); // clear the list
#endif
		out.net().register_con(new_proxy->in());
		out_cast.set_proxy(new_proxy);
		proxy = new_proxy;
=======
	auto ret = m_params.find(outname);
	if (ret == m_params.end() && required)
		log().fatal(MF_2_PARAMETER_1_2_NOT_FOUND, param_in_fqn, outname);
	if (ret != m_params.end())
		log().debug("Found parameter {1}\n", outname);
	return (ret == m_params.end() ? nullptr : &ret->second.m_param);
}

devices::nld_base_proxy *setup_t::get_d_a_proxy(detail::core_terminal_t &out)
{
	nl_assert(out.is_logic());

	logic_output_t &out_cast = static_cast<logic_output_t &>(out);
	devices::nld_base_proxy *proxy = out_cast.get_proxy();

	if (proxy == nullptr)
	{
		// create a new one ...
		pstring x = plib::pfmt("proxy_da_{1}_{2}")(out.name())(m_proxy_cnt);
		auto new_proxy =
				out_cast.logic_family()->create_d_a_proxy(netlist(), x, &out_cast);
		m_proxy_cnt++;

		//new_proxy->start_dev();

		/* connect all existing terminals to new net */

		for (auto & p : out.net().m_core_terms)
		{
			p->clear_net(); // de-link from all nets ...
			if (!connect(new_proxy->proxy_term(), *p))
				log().fatal(MF_2_CONNECTING_1_TO_2,
						new_proxy->proxy_term().name(), (*p).name());
		}
		out.net().m_core_terms.clear(); // clear the list

		out.net().add_terminal(new_proxy->in());
		out_cast.set_proxy(proxy);

		proxy = new_proxy.get();

		netlist().register_dev(std::move(new_proxy));
>>>>>>> upstream/master
	}
	return proxy;
}

<<<<<<< HEAD
void setup_t::connect_input_output(core_terminal_t &in, core_terminal_t &out)
{
	if (out.isFamily(terminal_t::ANALOG) && in.isFamily(terminal_t::LOGIC))
	{
		logic_input_t &incast = dynamic_cast<logic_input_t &>(in);
		devices::nld_a_to_d_proxy *proxy = palloc(devices::nld_a_to_d_proxy(&incast));
		incast.set_proxy(proxy);
		pstring x = pfmt("proxy_ad_{1}_{2}")(in.name())( m_proxy_cnt);
		m_proxy_cnt++;

		register_dev(proxy, x);
		proxy->start_dev();

		proxy->m_Q.net().register_con(in);
		out.net().register_con(proxy->m_I);

	}
	else if (out.isFamily(terminal_t::LOGIC) && in.isFamily(terminal_t::ANALOG))
=======
devices::nld_base_proxy *setup_t::get_a_d_proxy(detail::core_terminal_t &inp)
{
	nl_assert(inp.is_logic());

	logic_input_t &incast = dynamic_cast<logic_input_t &>(inp);
	devices::nld_base_proxy *proxy = incast.get_proxy();

	if (proxy != nullptr)
		return proxy;
	else
	{
		log().debug("connect_terminal_input: connecting proxy\n");
		pstring x = plib::pfmt("proxy_ad_{1}_{2}")(inp.name())(m_proxy_cnt);
		auto new_proxy = incast.logic_family()->create_a_d_proxy(netlist(), x, &incast);
		//auto new_proxy = plib::owned_ptr<devices::nld_a_to_d_proxy>::Create(netlist(), x, &incast);
		incast.set_proxy(new_proxy.get());
		m_proxy_cnt++;

		auto ret = new_proxy.get();

		/* connect all existing terminals to new net */

		if (inp.has_net())
		{
			for (auto & p : inp.net().m_core_terms)
			{
				p->clear_net(); // de-link from all nets ...
				if (!connect(ret->proxy_term(), *p))
					log().fatal(MF_2_CONNECTING_1_TO_2,
							ret->proxy_term().name(), (*p).name());
			}
			inp.net().m_core_terms.clear(); // clear the list
		}
		ret->out().net().add_terminal(inp);
		netlist().register_dev(std::move(new_proxy));
		return ret;
	}
}

void setup_t::merge_nets(detail::net_t &thisnet, detail::net_t &othernet)
{
	log().debug("merging nets ...\n");
	if (&othernet == &thisnet)
	{
		log().warning(MW_1_CONNECTING_1_TO_ITSELF, thisnet.name());
		return; // Nothing to do
	}

	if (thisnet.isRailNet() && othernet.isRailNet())
		log().fatal(MF_2_MERGE_RAIL_NETS_1_AND_2,
				thisnet.name(), othernet.name());

	if (othernet.isRailNet())
	{
		log().debug("othernet is railnet\n");
		merge_nets(othernet, thisnet);
	}
	else
	{
		othernet.move_connections(thisnet);
	}
}



void setup_t::connect_input_output(detail::core_terminal_t &in, detail::core_terminal_t &out)
{
	if (out.is_analog() && in.is_logic())
	{
		auto proxy = get_a_d_proxy(in);

		out.net().add_terminal(proxy->proxy_term());
	}
	else if (out.is_logic() && in.is_analog())
>>>>>>> upstream/master
	{
		devices::nld_base_proxy *proxy = get_d_a_proxy(out);

		connect_terminals(proxy->proxy_term(), in);
		//proxy->out().net().register_con(in);
	}
	else
	{
		if (in.has_net())
<<<<<<< HEAD
			out.net().merge_net(&in.net());
		else
			out.net().register_con(in);
=======
			merge_nets(out.net(), in.net());
		else
			out.net().add_terminal(in);
>>>>>>> upstream/master
	}
}


<<<<<<< HEAD
void setup_t::connect_terminal_input(terminal_t &term, core_terminal_t &inp)
{
	if (inp.isFamily(terminal_t::ANALOG))
	{
		connect_terminals(inp, term);
	}
	else if (inp.isFamily(terminal_t::LOGIC))
	{
		logic_input_t &incast = dynamic_cast<logic_input_t &>(inp);
		log().debug("connect_terminal_input: connecting proxy\n");
		devices::nld_a_to_d_proxy *proxy = palloc(devices::nld_a_to_d_proxy(&incast));
		incast.set_proxy(proxy);
		pstring x = pfmt("proxy_ad_{1}_{2}")(inp.name())(m_proxy_cnt);
		m_proxy_cnt++;

		register_dev(proxy, x);
		proxy->start_dev();

		connect_terminals(term, proxy->m_I);

		if (inp.has_net())
			//fatalerror("logic inputs can only belong to one net!\n");
			proxy->m_Q.net().merge_net(&inp.net());
		else
			proxy->m_Q.net().register_con(inp);
	}
	else
	{
		log().fatal("Netlist: Severe Error");
	}
}

void setup_t::connect_terminal_output(terminal_t &in, core_terminal_t &out)
{
	if (out.isFamily(terminal_t::ANALOG))
=======
void setup_t::connect_terminal_input(terminal_t &term, detail::core_terminal_t &inp)
{
	if (inp.is_analog())
	{
		connect_terminals(inp, term);
	}
	else if (inp.is_logic())
	{
		log().verbose("connect terminal {1} (in, {2}) to {3}\n", inp.name(),
				inp.is_analog() ? pstring("analog") : inp.is_logic() ? pstring("logic") : pstring("?"), term.name());
		auto proxy = get_a_d_proxy(inp);

		//out.net().register_con(proxy->proxy_term());
		connect_terminals(term, proxy->proxy_term());

	}
	else
	{
		log().fatal(MF_1_OBJECT_INPUT_TYPE_1, inp.name());
	}
}

void setup_t::connect_terminal_output(terminal_t &in, detail::core_terminal_t &out)
{
	if (out.is_analog())
>>>>>>> upstream/master
	{
		log().debug("connect_terminal_output: {1} {2}\n", in.name(), out.name());
		/* no proxy needed, just merge existing terminal net */
		if (in.has_net())
<<<<<<< HEAD
			out.net().merge_net(&in.net());
		else
			out.net().register_con(in);
	}
	else if (out.isFamily(terminal_t::LOGIC))
=======
			merge_nets(out.net(), in.net());
		else
			out.net().add_terminal(in);
	}
	else if (out.is_logic())
>>>>>>> upstream/master
	{
		log().debug("connect_terminal_output: connecting proxy\n");
		devices::nld_base_proxy *proxy = get_d_a_proxy(out);

		connect_terminals(proxy->proxy_term(), in);
	}
	else
	{
<<<<<<< HEAD
		log().fatal("Netlist: Severe Error");
	}
}

void setup_t::connect_terminals(core_terminal_t &t1, core_terminal_t &t2)
{
	//nl_assert(in.isType(netlist_terminal_t::TERMINAL));
	//nl_assert(out.isType(netlist_terminal_t::TERMINAL));

	if (t1.has_net() && t2.has_net())
	{
		log().debug("T2 and T1 have net\n");
		t1.net().merge_net(&t2.net());
=======
		log().fatal(MF_1_OBJECT_OUTPUT_TYPE_1, out.name());
	}
}

void setup_t::connect_terminals(detail::core_terminal_t &t1, detail::core_terminal_t &t2)
{
	if (t1.has_net() && t2.has_net())
	{
		log().debug("T2 and T1 have net\n");
		merge_nets(t1.net(), t2.net());
>>>>>>> upstream/master
	}
	else if (t2.has_net())
	{
		log().debug("T2 has net\n");
<<<<<<< HEAD
		t2.net().register_con(t1);
=======
		t2.net().add_terminal(t1);
>>>>>>> upstream/master
	}
	else if (t1.has_net())
	{
		log().debug("T1 has net\n");
<<<<<<< HEAD
		t1.net().register_con(t2);
	}
	else
	{
		log().debug("adding net ...\n");
		analog_net_t *anet =  palloc(analog_net_t);
		t1.set_net(*anet);
		//m_netlist.solver()->m_nets.add(anet);
		// FIXME: Nets should have a unique name
		t1.net().init_object(netlist(),"net." + t1.name() );
		t1.net().register_con(t2);
		t1.net().register_con(t1);
	}
}

static core_terminal_t &resolve_proxy(core_terminal_t &term)
{
	if (term.isFamily(core_terminal_t::LOGIC))
=======
		t1.net().add_terminal(t2);
	}
	else
	{
		log().debug("adding analog net ...\n");
		// FIXME: Nets should have a unique name
		auto anet = plib::palloc<analog_net_t>(netlist(),"net." + t1.name());
		netlist().m_nets.push_back(plib::owned_ptr<analog_net_t>(anet, true));
		t1.set_net(anet);
		anet->add_terminal(t2);
		anet->add_terminal(t1);
	}
}

static detail::core_terminal_t &resolve_proxy(detail::core_terminal_t &term)
{
	if (term.is_logic())
>>>>>>> upstream/master
	{
		logic_t &out = dynamic_cast<logic_t &>(term);
		if (out.has_proxy())
			return out.get_proxy()->proxy_term();
	}
	return term;
}

<<<<<<< HEAD
bool setup_t::connect_input_input(core_terminal_t &t1, core_terminal_t &t2)
=======
bool setup_t::connect_input_input(detail::core_terminal_t &t1, detail::core_terminal_t &t2)
>>>>>>> upstream/master
{
	bool ret = false;
	if (t1.has_net())
	{
		if (t1.net().isRailNet())
			ret = connect(t2, t1.net().railterminal());
		if (!ret)
		{
<<<<<<< HEAD
			for (std::size_t i=0; i<t1.net().m_core_terms.size(); i++)
			{
				if (t1.net().m_core_terms[i]->isType(core_terminal_t::TERMINAL)
						/*|| t1.net().m_core_terms[i]->isType(netlist_core_terminal_t::OUTPUT)*/)
				{
					ret = connect(t2, *t1.net().m_core_terms[i]);
				}
=======
			for (auto & t : t1.net().m_core_terms)
			{
				if (t->is_type(detail::terminal_type::TERMINAL))
					ret = connect(t2, *t);
>>>>>>> upstream/master
				if (ret)
					break;
			}
		}
	}
	if (!ret && t2.has_net())
	{
		if (t2.net().isRailNet())
			ret = connect(t1, t2.net().railterminal());
		if (!ret)
		{
<<<<<<< HEAD
			for (std::size_t i=0; i<t2.net().m_core_terms.size(); i++)
			{
				if (t2.net().m_core_terms[i]->isType(core_terminal_t::TERMINAL)
						/*|| t2.net().m_core_terms[i]->isType(netlist_core_terminal_t::OUTPUT)*/)
				{
					ret = connect(t1, *t2.net().m_core_terms[i]);
				}
=======
			for (auto & t : t2.net().m_core_terms)
			{
				if (t->is_type(detail::terminal_type::TERMINAL))
					ret = connect(t1, *t);
>>>>>>> upstream/master
				if (ret)
					break;
			}
		}
	}
	return ret;
}



<<<<<<< HEAD
bool setup_t::connect(core_terminal_t &t1_in, core_terminal_t &t2_in)
{
	log().debug("Connecting {1} to {2}\n", t1_in.name(), t2_in.name());
	core_terminal_t &t1 = resolve_proxy(t1_in);
	core_terminal_t &t2 = resolve_proxy(t2_in);
	bool ret = true;

	if (t1.isType(core_terminal_t::OUTPUT) && t2.isType(core_terminal_t::INPUT))
	{
		if (t2.has_net() && t2.net().isRailNet())
			log().fatal("Input {1} already connected\n", t2.name());
		connect_input_output(t2, t1);
	}
	else if (t1.isType(core_terminal_t::INPUT) && t2.isType(core_terminal_t::OUTPUT))
	{
		if (t1.has_net()  && t1.net().isRailNet())
			log().fatal("Input {1} already connected\n", t1.name());
		connect_input_output(t1, t2);
	}
	else if (t1.isType(core_terminal_t::OUTPUT) && t2.isType(core_terminal_t::TERMINAL))
	{
		connect_terminal_output(dynamic_cast<terminal_t &>(t2), t1);
	}
	else if (t1.isType(core_terminal_t::TERMINAL) && t2.isType(core_terminal_t::OUTPUT))
	{
		connect_terminal_output(dynamic_cast<terminal_t &>(t1), t2);
	}
	else if (t1.isType(core_terminal_t::INPUT) && t2.isType(core_terminal_t::TERMINAL))
	{
		connect_terminal_input(dynamic_cast<terminal_t &>(t2), t1);
	}
	else if (t1.isType(core_terminal_t::TERMINAL) && t2.isType(core_terminal_t::INPUT))
	{
		connect_terminal_input(dynamic_cast<terminal_t &>(t1), t2);
	}
	else if (t1.isType(core_terminal_t::TERMINAL) && t2.isType(core_terminal_t::TERMINAL))
	{
		connect_terminals(dynamic_cast<terminal_t &>(t1), dynamic_cast<terminal_t &>(t2));
	}
	else if (t1.isType(core_terminal_t::INPUT) && t2.isType(core_terminal_t::INPUT))
=======
bool setup_t::connect(detail::core_terminal_t &t1_in, detail::core_terminal_t &t2_in)
{
	log().debug("Connecting {1} to {2}\n", t1_in.name(), t2_in.name());
	detail::core_terminal_t &t1 = resolve_proxy(t1_in);
	detail::core_terminal_t &t2 = resolve_proxy(t2_in);
	bool ret = true;

	if (t1.is_type(detail::terminal_type::OUTPUT) && t2.is_type(detail::terminal_type::INPUT))
	{
		if (t2.has_net() && t2.net().isRailNet())
			log().fatal(MF_1_INPUT_1_ALREADY_CONNECTED, t2.name());
		connect_input_output(t2, t1);
	}
	else if (t1.is_type(detail::terminal_type::INPUT) && t2.is_type(detail::terminal_type::OUTPUT))
	{
		if (t1.has_net()  && t1.net().isRailNet())
			log().fatal(MF_1_INPUT_1_ALREADY_CONNECTED, t1.name());
		connect_input_output(t1, t2);
	}
	else if (t1.is_type(detail::terminal_type::OUTPUT) && t2.is_type(detail::terminal_type::TERMINAL))
	{
		connect_terminal_output(dynamic_cast<terminal_t &>(t2), t1);
	}
	else if (t1.is_type(detail::terminal_type::TERMINAL) && t2.is_type(detail::terminal_type::OUTPUT))
	{
		connect_terminal_output(dynamic_cast<terminal_t &>(t1), t2);
	}
	else if (t1.is_type(detail::terminal_type::INPUT) && t2.is_type(detail::terminal_type::TERMINAL))
	{
		connect_terminal_input(dynamic_cast<terminal_t &>(t2), t1);
	}
	else if (t1.is_type(detail::terminal_type::TERMINAL) && t2.is_type(detail::terminal_type::INPUT))
	{
		connect_terminal_input(dynamic_cast<terminal_t &>(t1), t2);
	}
	else if (t1.is_type(detail::terminal_type::TERMINAL) && t2.is_type(detail::terminal_type::TERMINAL))
	{
		connect_terminals(dynamic_cast<terminal_t &>(t1), dynamic_cast<terminal_t &>(t2));
	}
	else if (t1.is_type(detail::terminal_type::INPUT) && t2.is_type(detail::terminal_type::INPUT))
>>>>>>> upstream/master
	{
		ret = connect_input_input(t1, t2);
	}
	else
		ret = false;
		//netlist().error("Connecting {1} to {2} not supported!\n", t1.name(), t2.name());
	return ret;
}

void setup_t::resolve_inputs()
{
<<<<<<< HEAD
	bool has_twoterms = false;

=======
>>>>>>> upstream/master
	log().verbose("Resolving inputs ...");

	/* Netlist can directly connect input to input.
	 * We therefore first park connecting inputs and retry
	 * after all other terminals were connected.
	 */
<<<<<<< HEAD
	int tries = 100;
	while (m_links.size() > 0 && tries >  0) // FIXME: convert into constant
	{
		unsigned li = 0;
		while (li < m_links.size())
		{
			const pstring t1s = m_links[li].e1;
			const pstring t2s = m_links[li].e2;
			core_terminal_t *t1 = find_terminal(t1s);
			core_terminal_t *t2 = find_terminal(t2s);

			if (connect(*t1, *t2))
				m_links.remove_at(li);
=======
	int tries = NL_MAX_LINK_RESOLVE_LOOPS;
	while (m_links.size() > 0 && tries >  0)
	{

		for (auto li = m_links.begin(); li != m_links.end(); )
		{
			const pstring t1s = li->first;
			const pstring t2s = li->second;
			detail::core_terminal_t *t1 = find_terminal(t1s);
			detail::core_terminal_t *t2 = find_terminal(t2s);

			if (connect(*t1, *t2))
				li = m_links.erase(li);
>>>>>>> upstream/master
			else
				li++;
		}
		tries--;
	}
	if (tries == 0)
	{
<<<<<<< HEAD
		for (std::size_t i = 0; i < m_links.size(); i++ )
			log().warning("Error connecting {1} to {2}\n", m_links[i].e1, m_links[i].e2);

		log().fatal("Error connecting -- bailing out\n");
=======
		for (auto & link : m_links)
			log().warning(MF_2_CONNECTING_1_TO_2, link.first, link.second);

		log().fatal(MF_0_LINK_TRIES_EXCEEDED);
>>>>>>> upstream/master
	}

	log().verbose("deleting empty nets ...");

<<<<<<< HEAD
	// delete empty nets ... and save m_list ...

	net_t::list_t todelete;

	for (std::size_t i = 0; i<netlist().m_nets.size(); i++)
	{
		if (netlist().m_nets[i]->num_cons() == 0)
		{
			todelete.add(netlist().m_nets[i]);
		}
		else
		{
			netlist().m_nets[i]->rebuild_list();
		}
	}

	for (std::size_t i=0; i < todelete.size(); i++)
	{
		log().verbose("Deleting net {1} ...", todelete[i]->name());
		netlist().m_nets.remove(todelete[i]);
		if (!todelete[i]->isRailNet())
			pfree(todelete[i]);
	}
=======
	// delete empty nets

	netlist().m_nets.erase(
			std::remove_if(netlist().m_nets.begin(), netlist().m_nets.end(),
					[](plib::owned_ptr<detail::net_t> &x)
					{
						if (x->num_cons() == 0)
						{
							x->netlist().log().verbose("Deleting net {1} ...", x->name());
							return true;
						}
						else
							return false;
					}), netlist().m_nets.end());
>>>>>>> upstream/master

	pstring errstr("");

	log().verbose("looking for terminals not connected ...");
<<<<<<< HEAD
	for (std::size_t i = 0; i < m_terminals.size(); i++)
	{
		core_terminal_t *term = m_terminals.value_at(i);
		if (!term->has_net())
			errstr += pfmt("Found terminal {1} without a net\n")(term->name());
		else if (term->net().num_cons() == 0)
			log().warning("Found terminal {1} without connections",
					term->name());
	}
	if (errstr != "")
		log().fatal("{1}", errstr);


	log().verbose("looking for two terms connected to rail nets ...\n");
	// FIXME: doesn't find internal devices. This needs to be more clever
	for (std::size_t i=0; i < netlist().m_devices.size(); i++)
	{
		devices::NETLIB_NAME(twoterm) *t = dynamic_cast<devices::NETLIB_NAME(twoterm) *>(netlist().m_devices[i]);
		if (t != NULL)
		{
			has_twoterms = true;
			if (t->m_N.net().isRailNet() && t->m_P.net().isRailNet())
#if 0
				netlist().fatal("Found device {1} connected only to railterminals {2}/{3}\n",
						t->name(), t->m_N.net().name(), t->m_P.net().name());
#else
				log().warning("Found device {1} connected only to railterminals {2}/{3}\n",
					t->name(), t->m_N.net().name(), t->m_P.net().name());
#endif
		}
	}

	log().verbose("initialize solver ...\n");

	if (netlist().solver() == NULL)
	{
		if (has_twoterms)
			log().fatal("No solver found for this net although analog elements are present\n");
	}
	else
		netlist().solver()->post_start();

=======
	for (auto & i : m_terminals)
	{
		detail::core_terminal_t *term = i.second;
		if (!term->has_net() && dynamic_cast< devices::NETLIB_NAME(dummy_input) *>(&term->device()) != nullptr)
			log().warning(MW_1_DUMMY_1_WITHOUT_CONNECTIONS, term->name());
		else if (!term->has_net())
			errstr += plib::pfmt("Found terminal {1} without a net\n")(term->name());
		else if (term->net().num_cons() == 0)
			log().warning(MW_1_TERMINAL_1_WITHOUT_CONNECTIONS, term->name());
	}
	//FIXME: error string handling
	if (errstr != "")
		log().fatal("{1}", errstr);

>>>>>>> upstream/master
}

void setup_t::start_devices()
{
<<<<<<< HEAD
	pstring env = nl_util::environment("NL_LOGS");

	if (env != "")
	{
		log().debug("Creating dynamic logs ...\n");
		pstring_list_t ll(env, ":");
		for (unsigned i=0; i < ll.size(); i++)
		{
			log().debug("{1}: <{2}>\n",i, ll[i]);
			log().debug("{1}: <{2}>\n",i, ll[i]);
			device_t *nc = factory().new_device_by_name("LOG");
			pstring name = "log_" + ll[i];
			register_dev(nc, name);
			register_link(name + ".I", ll[i]);
		}
	}

	netlist().start();
}

void setup_t::print_stats() const
{
#if (NL_KEEP_STATISTICS)
	{
		for (std::size_t i = 0; i < netlist().m_started_devices.size(); i++)
		{
			core_device_t *entry = netlist().m_started_devices[i];
			printf("Device %20s : %12d %12d %15ld\n", entry->name(), entry->stat_call_count, entry->stat_update_count, (long int) entry->stat_total_time / (entry->stat_update_count + 1));
		}
		printf("Queue Pushes %15d\n", netlist().queue().m_prof_call);
		printf("Queue Moves  %15d\n", netlist().queue().m_prof_sortmove);
	}
#endif
}

// ----------------------------------------------------------------------------------------
// Model / family
// ----------------------------------------------------------------------------------------

class logic_family_std_proxy_t : public logic_family_desc_t
{
public:
	logic_family_std_proxy_t() { }
	virtual devices::nld_base_d_to_a_proxy *create_d_a_proxy(logic_output_t *proxied) const
	{
		return palloc(devices::nld_d_to_a_proxy(proxied));
	}
};

logic_family_desc_t *setup_t::family_from_model(const pstring &model)
{
	model_map_t map;
	model_parse(model, map);

	if (setup_t::model_value_str(map, "TYPE") == "TTL")
		return netlist_family_TTL;
	if (setup_t::model_value_str(map, "TYPE") == "CD4XXX")
		return netlist_family_CD4XXX;

	logic_family_std_proxy_t *ret = palloc(logic_family_std_proxy_t);

	ret->m_low_thresh_V = setup_t::model_value(map, "IVL");
	ret->m_high_thresh_V = setup_t::model_value(map, "IVH");
	ret->m_low_V = setup_t::model_value(map, "OVL");
	ret->m_high_V = setup_t::model_value(map, "OVH");
	ret->m_R_low = setup_t::model_value(map, "ORL");
	ret->m_R_high = setup_t::model_value(map, "ORH");

	return ret;
}

static pstring model_string(model_map_t &map)
{
	pstring ret = map["COREMODEL"] + "(";
	for (unsigned i=0; i<map.size(); i++)
		ret = ret + map.key_at(i) + "=" + map.value_at(i) + " ";
=======
	pstring env = plib::util::environment("NL_LOGS", "");

	if (env != "")
	{
		log().debug("Creating dynamic logs ...");
		std::vector<pstring> loglist(plib::psplit(env, ":"));
		for (pstring ll : loglist)
		{
			pstring name = "log_" + ll;
			auto nc = factory().factory_by_name("LOG")->Create(netlist(), name);
			register_link(name + ".I", ll);
			log().debug("    dynamic link {1}: <{2}>\n",ll, name);
			netlist().register_dev(std::move(nc));
		}
	}
}

plib::plog_base<netlist_t, NL_DEBUG> &setup_t::log()
{
	return netlist().log();
}
const plib::plog_base<netlist_t, NL_DEBUG> &setup_t::log() const
{
	return netlist().log();
}


// ----------------------------------------------------------------------------------------
// Model
// ----------------------------------------------------------------------------------------

static pstring model_string(detail::model_map_t &map)
{
	pstring ret = map["COREMODEL"] + "(";
	for (auto & i : map)
		ret = ret + i.first + "=" + i.second + " ";
>>>>>>> upstream/master

	return ret + ")";
}

<<<<<<< HEAD

void setup_t::model_parse(const pstring &model_in, model_map_t &map)
{
	pstring model = model_in;
	int pos = 0;
=======
void setup_t::model_parse(const pstring &model_in, detail::model_map_t &map)
{
	pstring model = model_in;
	std::size_t pos = 0;
>>>>>>> upstream/master
	pstring key;

	while (true)
	{
		pos = model.find("(");
<<<<<<< HEAD
		if (pos >= 0) break;

		key = model.ucase();
		if (!m_models.contains(key))
			log().fatal("Model {1} not found\n", model);
		model = m_models[key];
=======
		if (pos != pstring::npos) break;

		key = model.ucase();
		auto i = m_models.find(key);
		if (i == m_models.end())
			log().fatal(MF_1_MODEL_NOT_FOUND, model);
		model = i->second;
>>>>>>> upstream/master
	}
	pstring xmodel = model.left(pos);

	if (xmodel.equals("_"))
		map["COREMODEL"] = key;
	else
	{
<<<<<<< HEAD
		if (m_models.contains(xmodel))
			model_parse(xmodel, map);
		else
			log().fatal("Model doesn't exist {1}\n", xmodel);
	}

	pstring remainder=model.substr(pos+1).trim();
	if (!remainder.endsWith(")"))
		log().fatal("Model error {1}\n", model);
	remainder = remainder.left(remainder.len() - 1);

	pstring_list_t pairs(remainder," ", true);
	for (unsigned i=0; i<pairs.size(); i++)
	{
		int pose = pairs[i].find("=");
		if (pose < 0)
			log().fatal("Model error on pair {1}\n", model);
		map[pairs[i].left(pose).ucase()] = pairs[i].substr(pose+1);
	}
}

const pstring setup_t::model_value_str(model_map_t &map, const pstring &entity)
=======
		auto i = m_models.find(xmodel);
		if (i != m_models.end())
			model_parse(xmodel, map);
		else
			log().fatal(MF_1_MODEL_NOT_FOUND, model_in);
	}

	pstring remainder = model.substr(pos + 1).trim();
	if (!remainder.endsWith(")"))
		log().fatal(MF_1_MODEL_ERROR_1, model);
	// FIMXE: Not optimal
	remainder = remainder.left(remainder.length() - 1);

	std::vector<pstring> pairs(plib::psplit(remainder," ", true));
	for (pstring &pe : pairs)
	{
		auto pose = pe.find("=");
		if (pose == pstring::npos)
			log().fatal(MF_1_MODEL_ERROR_ON_PAIR_1, model);
		map[pe.left(pose).ucase()] = pe.substr(pose + 1);
	}
}

const pstring setup_t::model_value_str(detail::model_map_t &map, const pstring &entity)
>>>>>>> upstream/master
{
	pstring ret;

	if (entity != entity.ucase())
<<<<<<< HEAD
		log().fatal("model parameters should be uppercase:{1} {2}\n", entity, model_string(map));
	if (!map.contains(entity))
		log().fatal("Entity {1} not found in model {2}\n", entity, model_string(map));
=======
		log().fatal(MF_2_MODEL_PARAMETERS_NOT_UPPERCASE_1_2, entity,
				model_string(map));
	if (map.find(entity) == map.end())
		log().fatal(MF_2_ENTITY_1_NOT_FOUND_IN_MODEL_2, entity, model_string(map));
>>>>>>> upstream/master
	else
		ret = map[entity];

	return ret;
}

<<<<<<< HEAD
nl_double setup_t::model_value(model_map_t &map, const pstring &entity)
=======
nl_double setup_t::model_value(detail::model_map_t &map, const pstring &entity)
>>>>>>> upstream/master
{
	pstring tmp = model_value_str(map, entity);

	nl_double factor = NL_FCONST(1.0);
<<<<<<< HEAD
	pstring numfac = tmp.right(1);
	switch (numfac.code_at(0))
=======
	auto p = std::next(tmp.begin(), static_cast<pstring::difference_type>(tmp.length() - 1));
	switch (*p)
>>>>>>> upstream/master
	{
		case 'M': factor = 1e6; break;
		case 'k': factor = 1e3; break;
		case 'm': factor = 1e-3; break;
		case 'u': factor = 1e-6; break;
		case 'n': factor = 1e-9; break;
		case 'p': factor = 1e-12; break;
		case 'f': factor = 1e-15; break;
		case 'a': factor = 1e-18; break;
		default:
<<<<<<< HEAD
			if (numfac < "0" || numfac > "9")
				fatalerror_e(pfmt("Unknown number factor <{1}> in: {2}")(numfac)(entity));
	}
	if (factor != NL_FCONST(1.0))
		tmp = tmp.left(tmp.len() - 1);
	return tmp.as_double() * factor;
}

=======
			if (*p < '0' || *p > '9')
			log().fatal(MF_1_UNKNOWN_NUMBER_FACTOR_IN_1, entity);
	}
	if (factor != NL_FCONST(1.0))
		tmp = tmp.left(tmp.length() - 1);
	return tmp.as_double() * factor;
}

class logic_family_std_proxy_t : public logic_family_desc_t
{
public:
	logic_family_std_proxy_t() { }
	virtual plib::owned_ptr<devices::nld_base_d_to_a_proxy> create_d_a_proxy(netlist_t &anetlist,
			const pstring &name, logic_output_t *proxied) const override;
	virtual plib::owned_ptr<devices::nld_base_a_to_d_proxy> create_a_d_proxy(netlist_t &anetlist, const pstring &name, logic_input_t *proxied) const override;
};

plib::owned_ptr<devices::nld_base_d_to_a_proxy> logic_family_std_proxy_t::create_d_a_proxy(netlist_t &anetlist,
		const pstring &name, logic_output_t *proxied) const
{
	return plib::owned_ptr<devices::nld_base_d_to_a_proxy>::Create<devices::nld_d_to_a_proxy>(anetlist, name, proxied);
}
plib::owned_ptr<devices::nld_base_a_to_d_proxy> logic_family_std_proxy_t::create_a_d_proxy(netlist_t &anetlist, const pstring &name, logic_input_t *proxied) const
{
	return plib::owned_ptr<devices::nld_base_a_to_d_proxy>::Create<devices::nld_a_to_d_proxy>(anetlist, name, proxied);
}


const logic_family_desc_t *setup_t::family_from_model(const pstring &model)
{
	detail::model_map_t map;
	model_parse(model, map);

	if (model_value_str(map, "TYPE") == "TTL")
		return family_TTL();
	if (model_value_str(map, "TYPE") == "CD4XXX")
		return family_CD4XXX();

	for (auto & e : netlist().m_family_cache)
		if (e.first == model)
			return e.second.get();

	auto ret = plib::make_unique_base<logic_family_desc_t, logic_family_std_proxy_t>();

	ret->m_fixed_V = model_value(map, "FV");
	ret->m_low_thresh_PCNT = model_value(map, "IVL");
	ret->m_high_thresh_PCNT = model_value(map, "IVH");
	ret->m_low_VO = model_value(map, "OVL");
	ret->m_high_VO = model_value(map, "OVH");
	ret->m_R_low = model_value(map, "ORL");
	ret->m_R_high = model_value(map, "ORH");

	auto retp = ret.get();

	netlist().m_family_cache.emplace_back(model, std::move(ret));

	return retp;
}

void setup_t::tt_factory_create(tt_desc &desc, const pstring &sourcefile)
{
	devices::tt_factory_create(*this, desc, sourcefile);
}


>>>>>>> upstream/master
// ----------------------------------------------------------------------------------------
// Sources
// ----------------------------------------------------------------------------------------

void setup_t::include(const pstring &netlist_name)
{
<<<<<<< HEAD
	for (std::size_t i=0; i < m_sources.size(); i++)
	{
		if (m_sources[i]->parse(*this, netlist_name))
			return;
	}
	log().fatal("unable to find {1} in source collection", netlist_name);
=======
	for (auto &source : m_sources)
	{
		if (source->parse(netlist_name))
			return;
	}
	log().fatal(MF_1_NOT_FOUND_IN_SOURCE_COLLECTION, netlist_name);
}

std::unique_ptr<plib::pistream> setup_t::get_data_stream(const pstring &name)
{
	for (auto &source : m_sources)
	{
		if (source->type() == source_t::DATA)
		{
			auto strm = source->stream(name);
			if (strm)
				return strm;
		}
	}
	log().warning(MW_1_DATA_1_NOT_FOUND, name);
	return std::unique_ptr<plib::pistream>(nullptr);
}


bool setup_t::parse_stream(plib::putf8_reader &istrm, const pstring &name)
{
	plib::pomemstream ostrm;
	plib::putf8_writer owrt(ostrm);

	plib::ppreprocessor(&m_defines).process(istrm, owrt);
	plib::pimemstream istrm2(ostrm);
	plib::putf8_reader reader2(istrm2);
	return parser_t(reader2, *this).parse(name);
}

void setup_t::register_define(pstring defstr)
{
	auto p = defstr.find("=");
	if (p != pstring::npos)
		register_define(defstr.left(p), defstr.substr(p+1));
	else
		register_define(defstr, "1");
>>>>>>> upstream/master
}

// ----------------------------------------------------------------------------------------
// base sources
// ----------------------------------------------------------------------------------------

<<<<<<< HEAD
bool source_string_t::parse(setup_t &setup, const pstring &name)
{
	pimemstream istrm(m_str.cstr(), m_str.len());
	pomemstream ostrm;

	pimemstream istrm2(ppreprocessor().process(istrm, ostrm));
	return parser_t(istrm2, setup).parse(name);
}

bool source_mem_t::parse(setup_t &setup, const pstring &name)
{
	pimemstream istrm(m_str.cstr(), m_str.len());
	pomemstream ostrm;

	pimemstream istrm2(ppreprocessor().process(istrm, ostrm));
	return parser_t(istrm2, setup).parse(name);
}

bool source_file_t::parse(setup_t &setup, const pstring &name)
{
	pifilestream istrm(m_filename);
	pomemstream ostrm;

	pimemstream istrm2(ppreprocessor().process(istrm, ostrm));
	return parser_t(istrm2, setup).parse(name);
}

}
=======
bool source_t::parse(const pstring &name)
{
	if (m_type != SOURCE)
		return false;
	else
	{
		auto rstream = stream(name);
		plib::putf8_reader reader(*rstream);
		return m_setup.parse_stream(reader, name);
	}
}

std::unique_ptr<plib::pistream> source_string_t::stream(const pstring &name)
{
	return plib::make_unique_base<plib::pistream, plib::pimemstream>(m_str.c_str(), m_str.mem_t_size());
}

std::unique_ptr<plib::pistream> source_mem_t::stream(const pstring &name)
{
	return plib::make_unique_base<plib::pistream, plib::pimemstream>(m_str.c_str(), m_str.mem_t_size());
}

std::unique_ptr<plib::pistream> source_file_t::stream(const pstring &name)
{
	return plib::make_unique_base<plib::pistream, plib::pifilestream>(m_filename);
}

bool source_proc_t::parse(const pstring &name)
{
	if (name == m_setup_func_name)
	{
		m_setup_func(setup());
		return true;
	}
	else
		return false;
}

std::unique_ptr<plib::pistream> source_proc_t::stream(const pstring &name)
{
	std::unique_ptr<plib::pistream> p(nullptr);
	return p;
}

}

>>>>>>> upstream/master
