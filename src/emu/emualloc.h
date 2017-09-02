// license:BSD-3-Clause
// copyright-holders:Aaron Giles
/***************************************************************************

    emualloc.h

    Memory allocation helpers for the core emulator.

***************************************************************************/

<<<<<<< HEAD
#pragma once

#ifndef __EMUALLOC_H__
#define __EMUALLOC_H__

#include <new>
#include "osdcore.h"
#include "coretmpl.h"


//**************************************************************************
//  DEBUGGING
//**************************************************************************

// set to 1 to track memory allocated by emualloc.h itself as well
#define TRACK_SELF_MEMORY       (0)

=======
#ifndef MAME_EMU_EMUALLOC_H
#define MAME_EMU_EMUALLOC_H

#pragma once

#include "osdcore.h"
#include "coretmpl.h"

#include <memory>
#include <mutex>
#include <new>
>>>>>>> upstream/master


//**************************************************************************
//  MACROS
//**************************************************************************

<<<<<<< HEAD
// self-allocation helpers
#if TRACK_SELF_MEMORY
#define EMUALLOC_SELF_NEW new(__FILE__, __LINE__)
#else
#define EMUALLOC_SELF_NEW new
#endif

// pool allocation helpers
#define pool_alloc(_pool, _type)                    (_pool).add_object(new(__FILE__, __LINE__) _type)
#define pool_alloc_clear(_pool, _type)              (_pool).add_object(new(__FILE__, __LINE__, zeromem) _type)
#define pool_alloc_array(_pool, _type, _num)        (_pool).add_array(new(__FILE__, __LINE__) _type[_num], (_num))
#define pool_alloc_array_clear(_pool, _type, _num)  (_pool).add_array(new(__FILE__, __LINE__, zeromem) _type[_num], (_num))
=======
// pool allocation helpers
#define pool_alloc(_pool, _type)                    (_pool).add_object(global_alloc(_type))
#define pool_alloc_clear(_pool, _type)              (_pool).add_object(global_alloc_clear _type)
#define pool_alloc_array(_pool, _type, _num)        (_pool).add_array(global_alloc_array(_type,_num), (_num))
#define pool_alloc_array_clear(_pool, _type, _num)  (_pool).add_array(global_alloc_array_clear<_type>(_num), (_num))
>>>>>>> upstream/master
#define pool_free(_pool, v)                         (_pool).remove(v)



//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

// resource_pool_item is a base class for items that are tracked by a resource pool
class resource_pool_item
{
private:
<<<<<<< HEAD
	resource_pool_item(const resource_pool_item &);
	resource_pool_item &operator=(const resource_pool_item &);

public:
	resource_pool_item(void *ptr, size_t size)
		: m_next(NULL),
			m_ordered_next(NULL),
			m_ordered_prev(NULL),
			m_ptr(ptr),
			m_size(size),
			m_id(~(UINT64)0) { }
=======
	resource_pool_item(const resource_pool_item &) = delete;
	resource_pool_item &operator=(const resource_pool_item &) = delete;

public:
	resource_pool_item(void *ptr, size_t size)
		: m_next(nullptr)
		, m_ordered_next(nullptr)
		, m_ordered_prev(nullptr)
		, m_ptr(ptr)
		, m_size(size)
		, m_id(~osd::u64(0))
	{ }
>>>>>>> upstream/master
	virtual ~resource_pool_item() { }

	resource_pool_item *    m_next;
	resource_pool_item *    m_ordered_next;
	resource_pool_item *    m_ordered_prev;
	void *                  m_ptr;
	size_t                  m_size;
<<<<<<< HEAD
	UINT64                  m_id;
=======
	osd::u64                m_id;
>>>>>>> upstream/master
};


// a resource_pool_object is a simple object wrapper for the templatized type
<<<<<<< HEAD
template<class _ObjectClass>
class resource_pool_object : public resource_pool_item
{
private:
	resource_pool_object<_ObjectClass>(const resource_pool_object<_ObjectClass> &);
	resource_pool_object<_ObjectClass> &operator=(const resource_pool_object<_ObjectClass> &);

public:
	resource_pool_object(_ObjectClass *object)
		: resource_pool_item(reinterpret_cast<void *>(object), sizeof(_ObjectClass)),
			m_object(object) { }
	virtual ~resource_pool_object() { delete m_object; }

private:
	_ObjectClass *          m_object;
=======
template <class ObjectClass>
class resource_pool_object : public resource_pool_item
{
private:
	resource_pool_object(const resource_pool_object<ObjectClass> &) = delete;
	resource_pool_object &operator=(const resource_pool_object<ObjectClass> &) = delete;

public:
	resource_pool_object(ObjectClass *object)
		: resource_pool_item(reinterpret_cast<void *>(object), sizeof(ObjectClass))
		, m_object(object)
	{ }
	resource_pool_object(std::unique_ptr<ObjectClass> &&object)
		: resource_pool_object(object.release())
	{ }
	virtual ~resource_pool_object() { delete m_object; }

private:
	ObjectClass *const      m_object;
>>>>>>> upstream/master
};


// a resource_pool_array is a simple object wrapper for an allocated array of
// the templatized type
<<<<<<< HEAD
template<class _ObjectClass> class resource_pool_array : public resource_pool_item
{
private:
	resource_pool_array<_ObjectClass>(const resource_pool_array<_ObjectClass> &);
	resource_pool_array<_ObjectClass> &operator=(const resource_pool_array<_ObjectClass> &);

public:
	resource_pool_array(_ObjectClass *array, int count)
		: resource_pool_item(reinterpret_cast<void *>(array), sizeof(_ObjectClass) * count),
			m_array(array),
			m_count(count) { }
	virtual ~resource_pool_array() { delete[] m_array; }

private:
	_ObjectClass *          m_array;
	int                     m_count;
=======
template <class ObjectClass> class resource_pool_array : public resource_pool_item
{
private:
	resource_pool_array(const resource_pool_array<ObjectClass> &) = delete;
	resource_pool_array &operator=(const resource_pool_array<ObjectClass> &) = delete;

public:
	resource_pool_array(ObjectClass *array, int count)
		: resource_pool_item(reinterpret_cast<void *>(array), sizeof(ObjectClass) * count)
		, m_array(array)
		, m_count(count)
	{ }
	virtual ~resource_pool_array() { delete[] m_array; }

private:
	ObjectClass *const      m_array;
	int const               m_count;
>>>>>>> upstream/master
};


// a resource pool tracks items and frees them upon reset or destruction
class resource_pool
{
private:
<<<<<<< HEAD
	resource_pool(const resource_pool &);
	resource_pool &operator=(const resource_pool &);
=======
	resource_pool(const resource_pool &) = delete;
	resource_pool &operator=(const resource_pool &) = delete;
>>>>>>> upstream/master

public:
	resource_pool(int hash_size = 193);
	virtual ~resource_pool();

	void add(resource_pool_item &item, size_t size, const char *type);
	void remove(resource_pool_item &item) { remove(item.m_ptr); }
	void remove(void *ptr);
	void remove(const void *ptr) { remove(const_cast<void *>(ptr)); }
	resource_pool_item *find(void *ptr);
	bool contains(void *ptrstart, void *ptrend);
	void clear();

<<<<<<< HEAD
	template<class _ObjectClass> _ObjectClass *add_object(_ObjectClass* object) { add(*EMUALLOC_SELF_NEW resource_pool_object<_ObjectClass>(object), sizeof(_ObjectClass), typeid(_ObjectClass).name()); return object; }
	template<class _ObjectClass> _ObjectClass *add_array(_ObjectClass* array, int count) { add(*EMUALLOC_SELF_NEW resource_pool_array<_ObjectClass>(array, count), sizeof(_ObjectClass), typeid(_ObjectClass).name()); return array; }

private:
	int                     m_hash_size;
	osd_lock *              m_listlock;
	std::vector<resource_pool_item *> m_hash;
	resource_pool_item *    m_ordered_head;
	resource_pool_item *    m_ordered_tail;
	static UINT64           s_id;
};


#endif  /* __EMUALLOC_H__ */
=======
	template <class ObjectClass> ObjectClass *add_object(ObjectClass *object) { add(*new resource_pool_object<ObjectClass>(object), sizeof(ObjectClass), typeid(ObjectClass).name()); return object; }
	template <class ObjectClass> ObjectClass *add_object(std::unique_ptr<ObjectClass> &&object) { return add_object(object.release()); }
	template <class ObjectClass> ObjectClass *add_array(ObjectClass *array, int count) { add(*new resource_pool_array<ObjectClass>(array, count), sizeof(ObjectClass), typeid(ObjectClass).name()); return array; }

private:
	int                     m_hash_size;
	std::mutex              m_listlock;
	std::vector<resource_pool_item *> m_hash;
	resource_pool_item *    m_ordered_head;
	resource_pool_item *    m_ordered_tail;
	static osd::u64         s_id;
};


#endif // MAME_EMU_EMUALLOC_H
>>>>>>> upstream/master
