// license:GPL-2.0+
// copyright-holders:Couriersud
/***************************************************************************

    nl_factory.c

    Discrete netlist implementation.

****************************************************************************/

#include "nl_factory.h"
<<<<<<< HEAD
#include "nl_setup.h"

namespace netlist
{
// ----------------------------------------------------------------------------------------
// net_device_t_base_factory
// ----------------------------------------------------------------------------------------

ATTR_COLD const pstring_list_t base_factory_t::term_param_list()
{
	if (m_def_param.startsWith("+"))
		return pstring_list_t(m_def_param.substr(1), ",");
	else
		return pstring_list_t();
}

ATTR_COLD const pstring_list_t base_factory_t::def_params()
{
	if (m_def_param.startsWith("+") || m_def_param.equals("-"))
		return pstring_list_t();
	else
		return pstring_list_t(m_def_param, ",");
}


factory_list_t::factory_list_t( setup_t &setup)
=======
#include "nl_base.h"
#include "nl_setup.h"
#include "plib/putil.h"
#include "nl_errstr.h"

namespace netlist { namespace factory
{

class NETLIB_NAME(wrapper) : public device_t
{
public:
	NETLIB_NAME(wrapper)(netlist_t &anetlist, const pstring &name)
	: device_t(anetlist, name)
	{
	}
protected:
	NETLIB_RESETI();
	NETLIB_UPDATEI();
};



element_t::element_t(const pstring &name, const pstring &classname,
		const pstring &def_param, const pstring &sourcefile)
	: m_name(name), m_classname(classname), m_def_param(def_param),
	  m_sourcefile(sourcefile)
{
}

element_t::element_t(const pstring &name, const pstring &classname,
		const pstring &def_param)
	: m_name(name), m_classname(classname), m_def_param(def_param),
	  m_sourcefile("<unknown>")
{
}

element_t::~element_t()
{
}

// ----------------------------------------------------------------------------------------
// net_device_t_base_factory
// ----------------------------------------------------------------------------------------

list_t::list_t( setup_t &setup)
>>>>>>> upstream/master
: m_setup(setup)
{
}

<<<<<<< HEAD
factory_list_t::~factory_list_t()
{
	for (std::size_t i=0; i < size(); i++)
	{
		base_factory_t *p = value_at(i);
		pfree(p);
	}
	clear();
}

#if 0
device_t *factory_list_t::new_device_by_classname(const pstring &classname) const
{
	for (std::size_t i=0; i < m_list.size(); i++)
	{
		base_factory_t *p = m_list[i];
		if (p->classname() == classname)
		{
			device_t *ret = p->Create();
			return ret;
		}
		p++;
	}
	return NULL; // appease code analysis
}
#endif

void factory_list_t::error(const pstring &s)
{
	m_setup.log().fatal("{1}", s);
}

device_t *factory_list_t::new_device_by_name(const pstring &name)
{
	base_factory_t *f = factory_by_name(name);
	return f->Create();
}

base_factory_t * factory_list_t::factory_by_name(const pstring &name)
{
	if (contains(name))
		return (*this)[name];
	else
	{
		m_setup.log().fatal("Class {1} not found!\n", name);
		return NULL; // appease code analysis
	}
}

}
=======
list_t::~list_t()
{
	clear();
}

void list_t::register_device(std::unique_ptr<element_t> &&factory)
{
	for (auto & e : *this)
		if (e->name() == factory->name())
			m_setup.log().fatal(MF_1_FACTORY_ALREADY_CONTAINS_1, factory->name());
	push_back(std::move(factory));
}

factory::element_t * list_t::factory_by_name(const pstring &devname)
{
	for (auto & e : *this)
	{
		if (e->name() == devname)
			return e.get();
	}

	m_setup.log().fatal(MF_1_CLASS_1_NOT_FOUND, devname);
	return nullptr; // appease code analysis
}

// -----------------------------------------------------------------------------
// factory_lib_entry_t: factory class to wrap macro based chips/elements
// -----------------------------------------------------------------------------

plib::owned_ptr<device_t> library_element_t::Create(netlist_t &anetlist, const pstring &name)
{
	return plib::owned_ptr<device_t>::Create<NETLIB_NAME(wrapper)>(anetlist, name);
}

void library_element_t::macro_actions(netlist_t &anetlist, const pstring &name)
{
	anetlist.setup().namespace_push(name);
	anetlist.setup().include(this->name());
	anetlist.setup().namespace_pop();
}

NETLIB_RESET(wrapper)
{
}

NETLIB_UPDATE(wrapper)
{
}


} }
>>>>>>> upstream/master
