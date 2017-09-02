// license:GPL-2.0+
// copyright-holders:Couriersud
/*
 * pstate.c
 *
 */

#include "pstate.h"
<<<<<<< HEAD

pstate_manager_t::pstate_manager_t()
{
}

pstate_manager_t::~pstate_manager_t()
{
	m_save.clear_and_free();
=======
#include "palloc.h"

namespace plib {
state_manager_t::state_manager_t()
{
}

state_manager_t::~state_manager_t()
{
	m_save.clear();
	m_custom.clear();
>>>>>>> upstream/master
}



<<<<<<< HEAD
ATTR_COLD void pstate_manager_t::save_state_ptr(const pstring &stname, const pstate_data_type_e dt, const void *owner, const int size, const int count, void *ptr, bool is_ptr)
{
	pstring fullname = stname;
	ATTR_UNUSED  pstring ts[] = {
			"NOT_SUPPORTED",
			"DT_CUSTOM",
			"DT_DOUBLE",
#if (PHAS_INT128)
			"DT_INT128",
#endif
			"DT_INT64",
			"DT_INT16",
			"DT_INT8",
			"DT_INT",
			"DT_BOOLEAN",
			"DT_FLOAT"
	};

	pstate_entry_t *p = palloc(pstate_entry_t(stname, dt, owner, size, count, ptr, is_ptr));
	m_save.add(p);
}

ATTR_COLD void pstate_manager_t::remove_save_items(const void *owner)
{
	pstate_entry_t::list_t todelete;

	for (std::size_t i=0; i < m_save.size(); i++)
	{
		if (m_save[i]->m_owner == owner)
			todelete.add(m_save[i]);
	}
	for (std::size_t i=0; i < todelete.size(); i++)
	{
		m_save.remove(todelete[i]);
	}
	todelete.clear_and_free();
}

ATTR_COLD void pstate_manager_t::pre_save()
{
	for (std::size_t i=0; i < m_save.size(); i++)
		if (m_save[i]->m_dt == DT_CUSTOM)
			m_save[i]->m_callback->on_pre_save();
}

ATTR_COLD void pstate_manager_t::post_load()
{
	for (std::size_t i=0; i < m_save.size(); i++)
		if (m_save[i]->m_dt == DT_CUSTOM)
			m_save[i]->m_callback->on_post_load();
}

template<> ATTR_COLD void pstate_manager_t::save_item(pstate_callback_t &state, const void *owner, const pstring &stname)
{
	//save_state_ptr(stname, DT_CUSTOM, 0, 1, &state);
	pstate_callback_t *state_p = &state;
	pstate_entry_t *p = palloc(pstate_entry_t(stname, owner, state_p));
	m_save.add(p);
	state.register_state(*this, stname);
}
=======
void state_manager_t::save_state_ptr(const void *owner, const pstring &stname, const datatype_t &dt, const std::size_t count, void *ptr)
{
	auto p = plib::make_unique<entry_t>(stname, dt, owner, count, ptr);
	m_save.push_back(std::move(p));
}

void state_manager_t::remove_save_items(const void *owner)
{
	for (auto i = m_save.begin(); i != m_save.end(); )
	{
		if (i->get()->m_owner == owner)
			i = m_save.erase(i);
		else
			i++;
	}
	for (auto i = m_custom.begin(); i != m_custom.end(); )
	{
		if (i->get()->m_owner == owner)
			i = m_custom.erase(i);
		else
			i++;
	}
}

void state_manager_t::pre_save()
{
	for (auto & s : m_custom)
		s->m_callback->on_pre_save();
}

void state_manager_t::post_load()
{
	for (auto & s : m_custom)
		s->m_callback->on_post_load();
}

template<> void state_manager_t::save_item(const void *owner, callback_t &state, const pstring &stname)
{
	//save_state_ptr(stname, DT_CUSTOM, 0, 1, &state);
	callback_t *state_p = &state;
	auto p = plib::make_unique<entry_t>(stname, owner, state_p);
	m_custom.push_back(std::move(p));
	state.register_state(*this, stname);
}

state_manager_t::callback_t::~callback_t()
{
}


}
>>>>>>> upstream/master
