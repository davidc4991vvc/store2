// license:GPL-2.0+
// copyright-holders:Couriersud
/*
 * pstate.h
 *
 */

#ifndef PSTATE_H_
#define PSTATE_H_

<<<<<<< HEAD
#include "plists.h"
#include "pstring.h"
=======
#include "pstring.h"
#include "ptypes.h"

#include <vector>
#include <memory>
>>>>>>> upstream/master

// ----------------------------------------------------------------------------------------
// state saving ...
// ----------------------------------------------------------------------------------------

<<<<<<< HEAD
#define PSTATE_INTERFACE_DECL()               \
	template<typename C> ATTR_COLD void save(C &state, const pstring &stname); \
	template<typename C, std::size_t N> ATTR_COLD void save(C (&state)[N], const pstring &stname); \
	template<typename C> ATTR_COLD void save(C *state, const pstring &stname, const int count);

#define PSTATE_INTERFACE(obj, manager, module)               \
	template<typename C> ATTR_COLD void obj::save(C &state, const pstring &stname) \
	{ manager->save_item(state, this, module + "." + stname); } \
	template<typename C, std::size_t N> ATTR_COLD void obj::save(C (&state)[N], const pstring &stname) \
	{ manager->save_state_ptr(module + "." + stname, pstate_datatype<C>::type, this, sizeof(state[0]), N, &(state[0]), false); } \
	template<typename C> ATTR_COLD void obj::save(C *state, const pstring &stname, const int count) \
	{ manager->save_state_ptr(module + "." + stname, pstate_datatype<C>::type, this, sizeof(C), count, state, false);   }

enum pstate_data_type_e {
	NOT_SUPPORTED,
	DT_CUSTOM,
	DT_DOUBLE,
#if (PHAS_INT128)
	DT_INT128,
#endif
	DT_INT64,
	DT_INT16,
	DT_INT8,
	DT_INT,
	DT_BOOLEAN,
	DT_FLOAT
};

template<typename _ItemType> struct pstate_datatype
{
	static const pstate_data_type_e type = pstate_data_type_e(NOT_SUPPORTED);
	static const bool is_ptr = false;
};

template<typename _ItemType> struct pstate_datatype<_ItemType *>
{
	static const pstate_data_type_e type = pstate_data_type_e(NOT_SUPPORTED);
	static const bool is_ptr = true;
};

//template<typename _ItemType> struct type_checker<_ItemType*> { static const bool is_atom = false; static const bool is_pointer = true; };

#define NETLIST_SAVE_TYPE(TYPE, TYPEDESC) \
		template<> struct pstate_datatype<TYPE>{ static const pstate_data_type_e type = pstate_data_type_e(TYPEDESC); static const bool is_ptr = false;}; \
		template<> struct pstate_datatype<TYPE *>{ static const pstate_data_type_e type = pstate_data_type_e(TYPEDESC); static const bool is_ptr = true;}

NETLIST_SAVE_TYPE(char, DT_INT8);
NETLIST_SAVE_TYPE(double, DT_DOUBLE);
NETLIST_SAVE_TYPE(float, DT_FLOAT);
NETLIST_SAVE_TYPE(INT8, DT_INT8);
NETLIST_SAVE_TYPE(UINT8, DT_INT8);
#if (PHAS_INT128)
NETLIST_SAVE_TYPE(INT128, DT_INT128);
NETLIST_SAVE_TYPE(UINT128, DT_INT128);
#endif
NETLIST_SAVE_TYPE(INT64, DT_INT64);
NETLIST_SAVE_TYPE(UINT64, DT_INT64);
NETLIST_SAVE_TYPE(bool, DT_BOOLEAN);
NETLIST_SAVE_TYPE(UINT32, DT_INT);
NETLIST_SAVE_TYPE(INT32, DT_INT);
NETLIST_SAVE_TYPE(UINT16, DT_INT16);
NETLIST_SAVE_TYPE(INT16, DT_INT16);
//NETLIST_SAVE_TYPE(std::size_t, DT_INT64);

class pstate_manager_t;

class pstate_callback_t
{
public:
	typedef plist_t<pstate_callback_t *> list_t;

	virtual ~pstate_callback_t() { };

	virtual void register_state(pstate_manager_t &manager, const pstring &module) = 0;
	virtual void on_pre_save() = 0;
	virtual void on_post_load() = 0;
protected:
};

struct pstate_entry_t
{
	typedef plist_t<pstate_entry_t *> list_t;

	pstate_entry_t(const pstring &stname, const pstate_data_type_e dt, const void *owner,
			const int size, const int count, void *ptr, bool is_ptr)
	: m_name(stname), m_dt(dt), m_owner(owner), m_callback(NULL), m_size(size), m_count(count), m_ptr(ptr), m_is_ptr(is_ptr) { }

	pstate_entry_t(const pstring &stname, const void *owner, pstate_callback_t *callback)
	: m_name(stname), m_dt(DT_CUSTOM), m_owner(owner), m_callback(callback), m_size(0), m_count(0), m_ptr(NULL), m_is_ptr(false) { }

	~pstate_entry_t() { }

	pstring m_name;
	const pstate_data_type_e m_dt;
	const void *m_owner;
	pstate_callback_t *m_callback;
	const int m_size;
	const int m_count;
	void *m_ptr;
	bool m_is_ptr;

	template<typename T>
	T *resolved()
	{
		if (m_is_ptr)
			return *static_cast<T **>(m_ptr);
		else
			return static_cast<T *>(m_ptr);
	}
};

class pstate_manager_t
{
public:

	pstate_manager_t();
	~pstate_manager_t();

	template<typename C> ATTR_COLD void save_item(C &state, const void *owner, const pstring &stname)
	{
		save_state_ptr(stname, pstate_datatype<C>::type, owner, sizeof(C), 1, &state, pstate_datatype<C>::is_ptr);
	}

	template<typename C, std::size_t N> ATTR_COLD void save_item(C (&state)[N], const void *owner, const pstring &stname)
	{
		save_state_ptr(stname, pstate_datatype<C>::type, owner, sizeof(state[0]), N, &(state[0]), false);
	}

	template<typename C> ATTR_COLD void save_item(C *state, const void *owner, const pstring &stname, const int count)
	{
		save_state_ptr(stname, pstate_datatype<C>::type, owner, sizeof(C), count, state, false);
	}

	ATTR_COLD void pre_save();
	ATTR_COLD void post_load();
	ATTR_COLD void remove_save_items(const void *owner);

	const pstate_entry_t::list_t &save_list() const { return m_save; }

	ATTR_COLD void save_state_ptr(const pstring &stname, const pstate_data_type_e, const void *owner, const int size, const int count, void *ptr, bool is_ptr);
=======
namespace plib {
class state_manager_t
{
public:

	struct datatype_t
	{
		datatype_t(std::size_t bsize, bool bintegral, bool bfloat)
		: size(bsize), is_integral(bintegral), is_float(bfloat), is_custom(false)
		{}
		explicit datatype_t(bool bcustom)
		: size(0), is_integral(false), is_float(false), is_custom(bcustom)
		{}

		const std::size_t size;
		const bool is_integral;
		const bool is_float;
		const bool is_custom;
	};

	template<typename T> struct datatype_f
	{
		static inline const datatype_t f()
		{
			return datatype_t(sizeof(T),
					plib::is_integral<T>::value || std::is_enum<T>::value,
					std::is_floating_point<T>::value);
		}
	};

	class callback_t
	{
	public:
		using list_t = std::vector<callback_t *>;

		virtual ~callback_t();

		virtual void register_state(state_manager_t &manager, const pstring &module) = 0;
		virtual void on_pre_save() = 0;
		virtual void on_post_load() = 0;
	protected:
	};

	struct entry_t
	{
		using list_t = std::vector<std::unique_ptr<entry_t>>;

		entry_t(const pstring &stname, const datatype_t &dt, const void *owner,
				const std::size_t count, void *ptr)
		: m_name(stname), m_dt(dt), m_owner(owner), m_callback(nullptr), m_count(count), m_ptr(ptr) { }

		entry_t(const pstring &stname, const void *owner, callback_t *callback)
		: m_name(stname), m_dt(datatype_t(true)), m_owner(owner), m_callback(callback), m_count(0), m_ptr(nullptr) { }

		~entry_t() { }

		pstring             m_name;
		const datatype_t    m_dt;
		const void *        m_owner;
		callback_t *        m_callback;
		const std::size_t   m_count;
		void *              m_ptr;
	};

	state_manager_t();
	~state_manager_t();

	template<typename C> void save_item(const void *owner, C &state, const pstring &stname)
	{
		save_state_ptr( owner, stname, datatype_f<C>::f(), 1, &state);
	}

	template<typename C, std::size_t N> void save_item(const void *owner, C (&state)[N], const pstring &stname)
	{
		save_state_ptr(owner, stname, datatype_f<C>::f(), N, &(state[0]));
	}

	template<typename C> void save_item(const void *owner, C *state, const pstring &stname, const std::size_t count)
	{
		save_state_ptr(owner, stname, datatype_f<C>::f(), count, state);
	}

	template<typename C>
	void save_item(const void *owner, std::vector<C> &v, const pstring &stname)
	{
		save_state(v.data(), owner, stname, v.size());
	}

	void pre_save();
	void post_load();
	void remove_save_items(const void *owner);

	const entry_t::list_t &save_list() const { return m_save; }

	void save_state_ptr(const void *owner, const pstring &stname, const datatype_t &dt, const std::size_t count, void *ptr);
>>>>>>> upstream/master

protected:

private:
<<<<<<< HEAD
	pstate_entry_t::list_t m_save;
};

template<> ATTR_COLD void pstate_manager_t::save_item(pstate_callback_t &state, const void *owner, const pstring &stname);

=======
	entry_t::list_t m_save;
	entry_t::list_t m_custom;

};

template<> void state_manager_t::save_item(const void *owner, callback_t &state, const pstring &stname);

}
>>>>>>> upstream/master

#endif /* PSTATE_H_ */
