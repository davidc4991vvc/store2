// license:GPL-2.0+
// copyright-holders:Couriersud
/*
 * nlsetup.h
 *
 */

#ifndef NLSETUP_H_
#define NLSETUP_H_

<<<<<<< HEAD
#include "nl_base.h"
=======
#include "plib/pstring.h"
#include "plib/putil.h"
#include "plib/pstream.h"
#include "plib/pparser.h"

#include "nl_factory.h"
#include "nl_config.h"
#include "netlist_types.h"

#include <stack>
#include <vector>
#include <memory>
>>>>>>> upstream/master

//============================================================
//  MACROS / inline netlist definitions
//============================================================

<<<<<<< HEAD
#define NET_STR(_x) # _x

#define NET_MODEL(_model)                                                           \
	setup.register_model(_model);

#define ALIAS(_alias, _name)                                                        \
	setup.register_alias(# _alias, # _name);

#define DIPPINS(_pin1, ...)                                                          \
		setup.register_dippins_arr( #_pin1 ", " # __VA_ARGS__);

/* to be used to reference new library truthtable devices */
#define NET_REGISTER_DEV(_type, _name)                                            \
		setup.register_dev(# _type, # _name);

#define NET_REGISTER_SIGNAL(_type, _name)                                           \
		NET_REGISTER_DEV(_type ## _ ## sig, _name)

#define NET_CONNECT(_name, _input, _output)                                         \
		setup.register_link(# _name "." # _input, # _output);

#define NET_C(_term1, ...)                                                          \
		setup.register_link_arr( #_term1 ", " # __VA_ARGS__);

#define PARAM(_name, _val)                                                          \
		setup.register_param(# _name, _val);

#define NETDEV_PARAMI(_name, _param, _val)                                          \
		setup.register_param(# _name "." # _param, _val);

#define NETLIST_NAME(_name) netlist ## _ ## _name

#define NETLIST_EXTERNAL(_name)                                                \
		ATTR_COLD void NETLIST_NAME(_name)(netlist::setup_t &setup);

#define NETLIST_START(_name)                                                   \
ATTR_COLD void NETLIST_NAME(_name)(netlist::setup_t &setup)                    \
{
#define NETLIST_END()  }

#define LOCAL_SOURCE(_name)                                                    \
		setup.register_source(palloc(netlist::source_proc_t(# _name, &NETLIST_NAME(_name))));

#define LOCAL_LIB_ENTRY(_name)                                                 \
		LOCAL_SOURCE(_name)                                                    \
		setup.register_lib_entry(# _name);

#define INCLUDE(_name)                                                         \
		setup.include(# _name);

#define SUBMODEL(_model, _name)                                                \
		setup.namespace_push(# _name);                                         \
		NETLIST_NAME(_model)(setup);                                           \
		setup.namespace_pop();

// ----------------------------------------------------------------------------------------
// netlist_setup_t
// ----------------------------------------------------------------------------------------

namespace netlist
{
	// Forward definition so we keep nl_factory.h out of the public
	class factory_list_t;


	class setup_t
	{
		P_PREVENT_COPYING(setup_t)
	public:

		// ----------------------------------------------------------------------------------------
		// A Generic netlist sources implementation
		// ----------------------------------------------------------------------------------------

		class source_t
		{
		public:
			typedef plist_t<source_t *> list_t;

			source_t()
			{}

			virtual ~source_t() { }

			virtual bool parse(setup_t &setup, const pstring &name) = 0;
		private:
		};

		struct link_t
		{
			link_t() { }
			link_t(void *) { }
			// Copy constructor
			link_t(const link_t &from)
			{
				e1 = from.e1;
				e2 = from.e2;
			}

			link_t(const pstring &ae1, const pstring &ae2)
			{
				e1 = ae1;
				e2 = ae2;
			}
			pstring e1;
			pstring e2;

			bool operator==(const link_t &rhs) const { return (e1 == rhs.e1) && (e2 == rhs.e2); }
			link_t &operator=(const link_t &rhs) { e1 = rhs.e1; e2 = rhs.e2; return *this; }

			const pstring &name() const { return e1; }
		};

		setup_t(netlist_t *netlist);
		~setup_t();

		void init();

		netlist_t &netlist() { return *m_netlist; }
		const netlist_t &netlist() const { return *m_netlist; }

		pstring build_fqn(const pstring &obj_name) const;

		device_t *register_dev(device_t *dev, const pstring &name);
		device_t *register_dev(const pstring &classname, const pstring &name);
		void remove_dev(const pstring &name);

		void register_lib_entry(const pstring &name);
=======
#define NET_STR(x) # x

#define NET_MODEL(model)                                                           \
	setup.register_model(model);

#define ALIAS(alias, name)                                                        \
	setup.register_alias(# alias, # name);

#define DIPPINS(pin1, ...)                                                          \
		setup.register_dippins_arr( # pin1 ", " # __VA_ARGS__);

/* to be used to reference new library truthtable devices */
#define NET_REGISTER_DEV(type, name)                                            \
		setup.register_dev(# type, # name);

#define NET_CONNECT(name, input, output)                                        \
		setup.register_link(# name "." # input, # output);

#define NET_C(term1, ...)                                                       \
		setup.register_link_arr( # term1 ", " # __VA_ARGS__);

#define PARAM(name, val)                                                        \
		setup.register_param(# name, val);

#define HINT(name, val)                                                        \
		setup.register_param(# name ".HINT_" # val, 1);

#define NETDEV_PARAMI(name, param, val)                                         \
		setup.register_param(# name "." # param, val);

#define NETLIST_NAME(name) netlist ## _ ## name

#define NETLIST_EXTERNAL(name)                                                 \
		void NETLIST_NAME(name)(netlist::setup_t &setup);

#define NETLIST_START(name)                                                    \
void NETLIST_NAME(name)(netlist::setup_t &setup)                               \
{
#define NETLIST_END()  }

#define LOCAL_SOURCE(name)                                                     \
		setup.register_source(plib::make_unique_base<netlist::source_t, netlist::source_proc_t>(setup, # name, &NETLIST_NAME(name)));

#define LOCAL_LIB_ENTRY(name)                                                  \
		LOCAL_SOURCE(name)                                                     \
		setup.register_lib_entry(# name, __FILE__);

#define INCLUDE(name)                                                          \
		setup.include(# name);

#define SUBMODEL(model, name)                                                  \
		setup.namespace_push(# name);                                          \
		NETLIST_NAME(model)(setup);                                            \
		setup.namespace_pop();

#define OPTIMIZE_FRONTIER(attach, r_in, r_out)                                  \
		setup.register_frontier(# attach, r_in, r_out);

// -----------------------------------------------------------------------------
// truthtable defines
// -----------------------------------------------------------------------------

#define TRUTHTABLE_START(cname, in, out, def_params) \
	{ \
		netlist::tt_desc desc; \
		desc.name = #cname ; \
		desc.classname = #cname ; \
		desc.ni = in; \
		desc.no = out; \
		desc.def_param = def_params; \
		desc.family = "";

#define TT_HEAD(x) \
		desc.desc.push_back(x);

#define TT_LINE(x) \
		desc.desc.push_back(x);

#define TT_FAMILY(x) \
		desc.family = x;

#define TRUTHTABLE_END() \
		setup.tt_factory_create(desc, __FILE__);       \
	}


namespace netlist
{

	namespace detail {
		class core_terminal_t;
		class net_t;
	}

	namespace devices {
		class nld_base_proxy;
	}

	class core_device_t;
	class param_t;
	class setup_t;
	class netlist_t;
	class logic_family_desc_t;
	class terminal_t;

	// -----------------------------------------------------------------------------
	// truthtable desc
	// -----------------------------------------------------------------------------

	struct tt_desc
	{
		pstring name;
		pstring classname;
		unsigned long ni;
		unsigned long no;
		pstring def_param;
		std::vector<pstring> desc;
		pstring family;
	};

	// -----------------------------------------------------------------------------
	// param_ref_t
	// -----------------------------------------------------------------------------

	struct param_ref_t
	{
		param_ref_t(const pstring &name, core_device_t &device, param_t &param)
		: m_name(name)
		, m_device(device)
		, m_param(param)
		{ }
		pstring m_name;
		core_device_t &m_device;
		param_t &m_param;
	};

	// ----------------------------------------------------------------------------------------
	// A Generic netlist sources implementation
	// ----------------------------------------------------------------------------------------

	class source_t
	{
	public:
		enum type_t
		{
			SOURCE,
			DATA
		};

		using list_t = std::vector<std::unique_ptr<source_t>>;

		source_t(setup_t &setup, const type_t type = SOURCE)
		: m_setup(setup), m_type(type)
		{}

		virtual ~source_t() { }

		virtual bool parse(const pstring &name);
		virtual std::unique_ptr<plib::pistream> stream(const pstring &name) = 0;

		setup_t &setup() { return m_setup; }
		type_t type() const { return m_type; }
	private:
		setup_t &m_setup;
		const type_t m_type;
	};

	// ----------------------------------------------------------------------------------------
	// setup_t
	// ----------------------------------------------------------------------------------------


	class setup_t : plib::nocopyassignmove
	{
	public:

		using link_t = std::pair<pstring, pstring>;

		explicit setup_t(netlist_t &netlist);
		~setup_t();

		netlist_t &netlist() { return m_netlist; }
		const netlist_t &netlist() const { return m_netlist; }

		pstring build_fqn(const pstring &obj_name) const;

		void register_param(const pstring &name, param_t &param);
		pstring get_initial_param_val(const pstring &name, const pstring &def);
		double get_initial_param_val(const pstring &name, const double def);
		int get_initial_param_val(const pstring &name, const int def);

		void register_term(detail::core_terminal_t &obj);

		void register_dev(const pstring &classname, const pstring &name);

		void register_lib_entry(const pstring &name, const pstring &sourcefile);
>>>>>>> upstream/master

		void register_model(const pstring &model_in);
		void register_alias(const pstring &alias, const pstring &out);
		void register_dippins_arr(const pstring &terms);

		void register_alias_nofqn(const pstring &alias, const pstring &out);

		void register_link_arr(const pstring &terms);
		void register_link_fqn(const pstring &sin, const pstring &sout);
		void register_link(const pstring &sin, const pstring &sout);

		void register_param(const pstring &param, const pstring &value);
		void register_param(const pstring &param, const double value);

<<<<<<< HEAD
		void register_frontier(const pstring attach, const double r_IN, const double r_OUT);
		void remove_connections(const pstring attach);

		void register_object(device_t &dev, const pstring &name, object_t &obj);
		bool connect(core_terminal_t &t1, core_terminal_t &t2);

		core_terminal_t *find_terminal(const pstring &outname_in, bool required = true);
		core_terminal_t *find_terminal(const pstring &outname_in, object_t::type_t atype, bool required = true);

		param_t *find_param(const pstring &param_in, bool required = true);
=======
		void register_frontier(const pstring &attach, const double r_IN, const double r_OUT);

		void remove_connections(const pstring &attach);

		bool connect(detail::core_terminal_t &t1, detail::core_terminal_t &t2);

		bool device_exists(const pstring &name) const;

		param_t *find_param(const pstring &param_in, bool required = true) const;
>>>>>>> upstream/master

		void start_devices();
		void resolve_inputs();

		/* handle namespace */

		void namespace_push(const pstring &aname);
		void namespace_pop();

		/* parse a source */

		void include(const pstring &netlist_name);

<<<<<<< HEAD
		/* register a source */

		void register_source(source_t *src) { m_sources.add(src); }

		factory_list_t &factory() { return *m_factory; }
		const factory_list_t &factory() const { return *m_factory; }

		bool is_library_item(const pstring &name) const { return m_lib.contains(name); }

		void print_stats() const;

		/* model / family related */

		logic_family_desc_t *family_from_model(const pstring &model);
		const pstring model_value_str(model_map_t &map, const pstring &entity);
		nl_double model_value(model_map_t &map, const pstring &entity);

		void model_parse(const pstring &model, model_map_t &map);

		plog_base<NL_DEBUG> &log() { return netlist().log(); }
		const plog_base<NL_DEBUG> &log() const { return netlist().log(); }

	protected:

	private:

		void connect_terminals(core_terminal_t &in, core_terminal_t &out);
		void connect_input_output(core_terminal_t &in, core_terminal_t &out);
		void connect_terminal_output(terminal_t &in, core_terminal_t &out);
		void connect_terminal_input(terminal_t &term, core_terminal_t &inp);
		bool connect_input_input(core_terminal_t &t1, core_terminal_t &t2);

		// helpers
		pstring objtype_as_astr(object_t &in) const;

		const pstring resolve_alias(const pstring &name) const;
		devices::nld_base_proxy *get_d_a_proxy(core_terminal_t &out);

		netlist_t *m_netlist;

		phashmap_t<pstring, pstring> m_alias;
		phashmap_t<pstring, param_t *>  m_params;
		phashmap_t<pstring, pstring> m_params_temp;
		phashmap_t<pstring, core_terminal_t *> m_terminals;

		plist_t<link_t> m_links;

		factory_list_t *m_factory;

		phashmap_t<pstring, pstring> m_models;

		int m_proxy_cnt;

		pstack_t<pstring> m_stack;
		source_t::list_t m_sources;
		plist_t<pstring> m_lib;

	};
=======
		std::unique_ptr<plib::pistream> get_data_stream(const pstring &name);

		bool parse_stream(plib::putf8_reader &istrm, const pstring &name);

		/* register a source */

		void register_source(std::unique_ptr<source_t> &&src)
		{
			m_sources.push_back(std::move(src));
		}

		void register_define(pstring def, pstring val) { m_defines.push_back(plib::ppreprocessor::define_t(def, val)); }
		void register_define(pstring defstr);

		factory::list_t &factory() { return m_factory; }
		const factory::list_t &factory() const { return m_factory; }

		/* model / family related */

		const pstring model_value_str(detail::model_map_t &map, const pstring &entity);
		double model_value(detail::model_map_t &map, const pstring &entity);

		void model_parse(const pstring &model, detail::model_map_t &map);

		const logic_family_desc_t *family_from_model(const pstring &model);

		void tt_factory_create(tt_desc &desc, const pstring &sourcefile);

		/* helper - also used by nltool */
		const pstring resolve_alias(const pstring &name) const;

		plib::plog_base<netlist_t, NL_DEBUG> &log();
		const plib::plog_base<netlist_t, NL_DEBUG> &log() const;

		std::vector<std::pair<pstring, factory::element_t *>> m_device_factory;

		std::unordered_map<pstring, pstring> m_alias;
		std::unordered_map<pstring, pstring> m_param_values;
		std::unordered_map<pstring, detail::core_terminal_t *> m_terminals;

		/* needed by proxy */
		detail::core_terminal_t *find_terminal(const pstring &outname_in, const detail::terminal_type atype, bool required = true);

	private:

		detail::core_terminal_t *find_terminal(const pstring &outname_in, bool required = true);

		void merge_nets(detail::net_t &thisnet, detail::net_t &othernet);

		void connect_terminals(detail::core_terminal_t &in, detail::core_terminal_t &out);
		void connect_input_output(detail::core_terminal_t &in, detail::core_terminal_t &out);
		void connect_terminal_output(terminal_t &in, detail::core_terminal_t &out);
		void connect_terminal_input(terminal_t &term, detail::core_terminal_t &inp);
		bool connect_input_input(detail::core_terminal_t &t1, detail::core_terminal_t &t2);

		// helpers
		pstring termtype_as_str(detail::core_terminal_t &in) const;

		devices::nld_base_proxy *get_d_a_proxy(detail::core_terminal_t &out);
		devices::nld_base_proxy *get_a_d_proxy(detail::core_terminal_t &inp);

		netlist_t                                   &m_netlist;
		std::unordered_map<pstring, param_ref_t>    m_params;
		std::vector<link_t>                         m_links;
		factory::list_t                             m_factory;
		std::unordered_map<pstring, pstring>        m_models;

		std::stack<pstring>                         m_namespace_stack;
		source_t::list_t                            m_sources;
		std::vector<plib::ppreprocessor::define_t>  m_defines;

		unsigned m_proxy_cnt;
		unsigned m_frontier_cnt;
};
>>>>>>> upstream/master

	// ----------------------------------------------------------------------------------------
	// base sources
	// ----------------------------------------------------------------------------------------


<<<<<<< HEAD
	class source_string_t : public setup_t::source_t
	{
	public:

		source_string_t(const pstring &source)
		: setup_t::source_t(), m_str(source)
		{
		}

		bool parse(setup_t &setup, const pstring &name);
=======
	class source_string_t : public source_t
	{
	public:

		source_string_t(setup_t &setup, const pstring &source)
		: source_t(setup), m_str(source)
		{
		}

		virtual std::unique_ptr<plib::pistream> stream(const pstring &name) override;
>>>>>>> upstream/master

	private:
		pstring m_str;
	};

<<<<<<< HEAD
	class source_file_t : public setup_t::source_t
	{
	public:

		source_file_t(const pstring &filename)
		: setup_t::source_t(), m_filename(filename)
		{
		}

		bool parse(setup_t &setup, const pstring &name);
=======
	class source_file_t : public source_t
	{
	public:

		source_file_t(setup_t &setup, const pstring &filename)
		: source_t(setup), m_filename(filename)
		{
		}

		virtual std::unique_ptr<plib::pistream> stream(const pstring &name) override;
>>>>>>> upstream/master

	private:
		pstring m_filename;
	};

<<<<<<< HEAD
	class source_mem_t : public setup_t::source_t
	{
	public:
		source_mem_t(const char *mem)
		: setup_t::source_t(), m_str(mem)
		{
		}

		bool parse(setup_t &setup, const pstring &name);
=======
	class source_mem_t : public source_t
	{
	public:
		source_mem_t(setup_t &setup, const char *mem)
		: source_t(setup), m_str(mem, pstring::UTF8)
		{
		}

		virtual std::unique_ptr<plib::pistream> stream(const pstring &name) override;
>>>>>>> upstream/master

	private:
		pstring m_str;
	};

<<<<<<< HEAD
	class source_proc_t : public setup_t::source_t
	{
	public:
		source_proc_t(pstring name, void (*setup_func)(setup_t &))
		: setup_t::source_t(),
=======
	class source_proc_t : public source_t
	{
	public:
		source_proc_t(setup_t &setup, pstring name, void (*setup_func)(setup_t &))
		: source_t(setup),
>>>>>>> upstream/master
			m_setup_func(setup_func),
			m_setup_func_name(name)
		{
		}

<<<<<<< HEAD
		bool parse(setup_t &setup, const pstring &name)
		{
			if (name == m_setup_func_name)
			{
				m_setup_func(setup);
				return true;
			}
			else
				return false;
		}
=======
		virtual bool parse(const pstring &name) override;
		virtual std::unique_ptr<plib::pistream> stream(const pstring &name) override;

>>>>>>> upstream/master
	private:
		void (*m_setup_func)(setup_t &);
		pstring m_setup_func_name;
	};

}


#endif /* NLSETUP_H_ */
