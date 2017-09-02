// license:GPL-2.0+
// copyright-holders:Couriersud
/*
 * nl_factory.h
 *
 *
 */

#ifndef NLFACTORY_H_
#define NLFACTORY_H_

<<<<<<< HEAD
#include "nl_config.h"
#include "plib/palloc.h"
#include "plib/plists.h"
#include "nl_base.h"

namespace netlist
{
=======
#include "plib/palloc.h"
#include "plib/ptypes.h"

#define NETLIB_DEVICE_IMPL(chip) \
	static std::unique_ptr<factory::element_t> NETLIB_NAME(chip ## _c)( \
			const pstring &name, const pstring &classname, const pstring &def_param) \
	{ \
		return std::unique_ptr<factory::element_t>(plib::palloc<factory::device_element_t<NETLIB_NAME(chip)>>(name, classname, def_param, pstring(__FILE__))); \
	} \
	factory::constructor_ptr_t decl_ ## chip = NETLIB_NAME(chip ## _c);

#define NETLIB_DEVICE_IMPL_NS(ns, chip) \
	static std::unique_ptr<factory::element_t> NETLIB_NAME(chip ## _c)( \
			const pstring &name, const pstring &classname, const pstring &def_param) \
	{ \
		return std::unique_ptr<factory::element_t>(plib::palloc<factory::device_element_t<ns :: NETLIB_NAME(chip)>>(name, classname, def_param, pstring(__FILE__))); \
	} \
	factory::constructor_ptr_t decl_ ## chip = NETLIB_NAME(chip ## _c);

namespace netlist {
	class netlist_t;
	class device_t;
	class setup_t;

namespace factory {
>>>>>>> upstream/master
	// -----------------------------------------------------------------------------
	// net_dev class factory
	// -----------------------------------------------------------------------------

<<<<<<< HEAD
	class base_factory_t
	{
		P_PREVENT_COPYING(base_factory_t)
	public:
		ATTR_COLD base_factory_t(const pstring &name, const pstring &classname,
				const pstring &def_param)
		: m_name(name), m_classname(classname), m_def_param(def_param)
		{}

		virtual ~base_factory_t() {}

		virtual device_t *Create() = 0;

		ATTR_COLD const pstring &name() const { return m_name; }
		ATTR_COLD const pstring &classname() const { return m_classname; }
		ATTR_COLD const pstring &param_desc() const { return m_def_param; }
		ATTR_COLD const pstring_list_t term_param_list();
		ATTR_COLD const pstring_list_t def_params();

	protected:
		pstring m_name;                             /* device name */
		pstring m_classname;                        /* device class name */
		pstring m_def_param;                        /* default parameter */
	};

	template <class C>
	class factory_t : public base_factory_t
	{
		P_PREVENT_COPYING(factory_t)
	public:
		ATTR_COLD factory_t(const pstring &name, const pstring &classname,
				const pstring &def_param)
		: base_factory_t(name, classname, def_param) { }

		ATTR_COLD device_t *Create()
		{
			device_t *r = palloc(C);
			//r->init(setup, name);
			return r;
		}
	};

	class factory_list_t : public phashmap_t<pstring, base_factory_t *>
	{
	public:
		factory_list_t(setup_t &m_setup);
		~factory_list_t();

		template<class _C>
		ATTR_COLD void register_device(const pstring &name, const pstring &classname,
				const pstring &def_param)
		{
			if (!add(name, palloc(factory_t< _C >(name, classname, def_param))))
				error("factory already contains " + name);
		}

		ATTR_COLD void register_device(base_factory_t *factory)
		{
			if (!add(factory->name(), factory))
				error("factory already contains " + factory->name());
		}

		//ATTR_COLD device_t *new_device_by_classname(const pstring &classname) const;
		ATTR_COLD device_t *new_device_by_name(const pstring &name);
		ATTR_COLD base_factory_t * factory_by_name(const pstring &name);

	private:
		void error(const pstring &s);

		setup_t &m_setup;
	};

=======
	class element_t : plib::nocopyassignmove
	{
	public:
		element_t(const pstring &name, const pstring &classname,
				const pstring &def_param);
		element_t(const pstring &name, const pstring &classname,
				const pstring &def_param, const pstring &sourcefile);
		virtual ~element_t();

		virtual plib::owned_ptr<device_t> Create(netlist_t &anetlist, const pstring &name) = 0;
		virtual void macro_actions(netlist_t &anetlist, const pstring &name) {}

		const pstring &name() const { return m_name; }
		const pstring &classname() const { return m_classname; }
		const pstring &param_desc() const { return m_def_param; }
		const pstring &sourcefile() const { return m_sourcefile; }

	private:
		pstring m_name;                             /* device name */
		pstring m_classname;                        /* device class name */
		pstring m_def_param;                        /* default parameter */
		pstring m_sourcefile;                       /* source file */
	};

	template <class C>
	class device_element_t : public element_t
	{
	public:
		device_element_t(const pstring &name, const pstring &classname,
				const pstring &def_param)
		: element_t(name, classname, def_param) { }
		device_element_t(const pstring &name, const pstring &classname,
				const pstring &def_param, const pstring &sourcefile)
		: element_t(name, classname, def_param, sourcefile) { }

		plib::owned_ptr<device_t> Create(netlist_t &anetlist, const pstring &name) override
		{
			return plib::owned_ptr<device_t>::Create<C>(anetlist, name);
		}
	};

	class list_t : public std::vector<std::unique_ptr<element_t>>
	{
	public:
		explicit list_t(setup_t &m_setup);
		~list_t();

		template<class device_class>
		void register_device(const pstring &name, const pstring &classname,
			const pstring &def_param)
		{
			register_device(std::unique_ptr<element_t>(plib::palloc<device_element_t<device_class>>(name, classname, def_param)));
		}

		void register_device(std::unique_ptr<element_t> &&factory);

		element_t * factory_by_name(const pstring &devname);

		template <class C>
		bool is_class(element_t *f)
		{
			return dynamic_cast<device_element_t<C> *>(f) != nullptr;
		}

	private:
		setup_t &m_setup;
	};

	// -----------------------------------------------------------------------------
	// factory_creator_ptr_t
	// -----------------------------------------------------------------------------

	using constructor_ptr_t = std::unique_ptr<element_t> (*)(const pstring &name, const pstring &classname,
			const pstring &def_param);

	template <typename T>
	std::unique_ptr<element_t> constructor_t(const pstring &name, const pstring &classname,
			const pstring &def_param)
	{
		return std::unique_ptr<element_t>(plib::palloc<device_element_t<T>>(name, classname, def_param));
	}

	// -----------------------------------------------------------------------------
	// factory_lib_entry_t: factory class to wrap macro based chips/elements
	// -----------------------------------------------------------------------------

	class library_element_t : public element_t
	{
	public:

		library_element_t(setup_t &setup, const pstring &name, const pstring &classname,
				const pstring &def_param, const pstring &source)
		: element_t(name, classname, def_param, source) {  }

		plib::owned_ptr<device_t> Create(netlist_t &anetlist, const pstring &name) override;

		void macro_actions(netlist_t &anetlist, const pstring &name) override;

	private:
	};

	}

	namespace devices {
		void initialize_factory(factory::list_t &factory);
	}
>>>>>>> upstream/master
}

#endif /* NLFACTORY_H_ */
