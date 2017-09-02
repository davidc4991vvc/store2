// license:BSD-3-Clause
<<<<<<< HEAD
// copyright-holders:Aaron Giles
/***************************************************************************

    devfind.h

    Device finding template helpers.

***************************************************************************/

#pragma once
=======
// copyright-holders:Aaron Giles, Vas Crabb
/**
 * \file devfind.h
 * Object auto-discovery helpers
 * \defgroup devfind
 * \{
 * Object auto-discovery helpers
 */
>>>>>>> upstream/master

#ifndef __EMU_H__
#error Dont include this file directly; include emu.h instead.
#endif

<<<<<<< HEAD
#ifndef __DEVFIND_H__
#define __DEVFIND_H__

#define FINDER_DUMMY_TAG "finder_dummy_tag"

//**************************************************************************
//  IOPORT ARRAY MACROS
//**************************************************************************

// these macros can be used to initialize an ioport_array with
// individual port names, instead of a base name + numeric suffix

#define IOPORT_ARRAY_MEMBER(name) const char * const name[] =
#define DECLARE_IOPORT_ARRAY(name) static const char * const name[]

//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

// ======================> finder_base

// helper class to request auto-object discovery in the constructor of a derived class
class finder_base
{
	friend class device_t;

public:
	// construction/destruction
	finder_base(device_t &base, const char *tag);
	virtual ~finder_base();

	// getters
	virtual bool findit(bool isvalidation = false) = 0;

	// setter for setting the object
	void set_tag(const char *tag) { m_tag = tag; }

protected:
	// helpers
	void *find_memregion(UINT8 width, size_t &length, bool required) const;
	void *find_memshare(UINT8 width, size_t &bytes, bool required);
	bool report_missing(bool found, const char *objname, bool required);

	void printf_warning(const char *format, ...) ATTR_PRINTF(2,3);

	// internal state
	finder_base *m_next;
	device_t &m_base;
	const char *m_tag;
};


// ======================> object_finder_base

// helper class to find objects of a particular type
template<class _ObjectClass>
class object_finder_base : public finder_base
{
public:
	// construction/destruction
	object_finder_base(device_t &base, const char *tag)
		: finder_base(base, tag),
			m_target(NULL) { }

	// operators to make use transparent
	operator _ObjectClass *() const { return m_target; }

	virtual _ObjectClass *operator->() const { assert(m_target != NULL); return m_target; }

	// getter for explicit fetching
	_ObjectClass *target() const { return m_target; }

	// setter for setting the object
	void set_target(_ObjectClass *target) { m_target = target; }

protected:
	// internal state
	_ObjectClass *m_target;
};


// ======================> device_finder

// device finder template
template<class _DeviceClass, bool _Required>
class device_finder : public object_finder_base<_DeviceClass>
{
public:
	// construction/destruction
	device_finder(device_t &base, const char *tag)
		: object_finder_base<_DeviceClass>(base, tag) { }

	// make reference use transparent as well
	operator _DeviceClass &() { assert(object_finder_base<_DeviceClass>::m_target != NULL); return *object_finder_base<_DeviceClass>::m_target; }

	// finder
	virtual bool findit(bool isvalidation = false)
	{
		device_t *device = this->m_base.subdevice(this->m_tag);
		this->m_target = dynamic_cast<_DeviceClass *>(device);
		if (device != NULL && this->m_target == NULL)
		{
			this->printf_warning("Device '%s' found but is of incorrect type (actual type is %s)\n", this->m_tag, device->name());
		}
		return this->report_missing(this->m_target != NULL, "device", _Required);
	}
};

// optional device finder
template<class _DeviceClass>
class optional_device : public device_finder<_DeviceClass, false>
{
public:
	optional_device(device_t &base, const char *tag = FINDER_DUMMY_TAG) : device_finder<_DeviceClass, false>(base, tag) { }
};

// required devices are similar but throw an error if they are not found
template<class _DeviceClass>
class required_device : public device_finder<_DeviceClass, true>
{
public:
	required_device(device_t &base, const char *tag = FINDER_DUMMY_TAG) : device_finder<_DeviceClass, true>(base, tag) { }
};


// ======================> memory_region_finder

// device finder template
template<bool _Required>
class memory_region_finder : public object_finder_base<memory_region>
{
public:
	// construction/destruction
	memory_region_finder(device_t &base, const char *tag)
		: object_finder_base<memory_region>(base, tag) { }

	// make reference use transparent as well
	operator memory_region &() { assert(object_finder_base<memory_region>::m_target != NULL); return *object_finder_base<memory_region>::m_target; }

	// finder
	virtual bool findit(bool isvalidation = false)
	{
		if (isvalidation) return true;
		m_target = m_base.memregion(m_tag);
		return this->report_missing(m_target != NULL, "memory region", _Required);
	}
};

// optional device finder
class optional_memory_region : public memory_region_finder<false>
{
public:
	optional_memory_region(device_t &base, const char *tag = FINDER_DUMMY_TAG) : memory_region_finder<false>(base, tag) { }
};

// required devices are similar but throw an error if they are not found
class required_memory_region : public memory_region_finder<true>
{
public:
	required_memory_region(device_t &base, const char *tag = FINDER_DUMMY_TAG) : memory_region_finder<true>(base, tag) { }
};


// ======================> memory_bank_finder

// device finder template
template<bool _Required>
class memory_bank_finder : public object_finder_base<memory_bank>
{
public:
	// construction/destruction
	memory_bank_finder(device_t &base, const char *tag)
		: object_finder_base<memory_bank>(base, tag) { }

	// make reference use transparent as well
	operator memory_bank &() { assert(object_finder_base<memory_bank>::m_target != NULL); return *object_finder_base<memory_bank>::m_target; }

	// finder
	virtual bool findit(bool isvalidation = false)
	{
		if (isvalidation) return true;
		m_target = m_base.membank(m_tag);
		return this->report_missing(m_target != NULL, "memory bank", _Required);
	}
};

// optional device finder
class optional_memory_bank : public memory_bank_finder<false>
{
public:
	optional_memory_bank(device_t &base, const char *tag = FINDER_DUMMY_TAG) : memory_bank_finder<false>(base, tag) { }
};

// required devices are similar but throw an error if they are not found
class required_memory_bank : public memory_bank_finder<true>
{
public:
	required_memory_bank(device_t &base, const char *tag = FINDER_DUMMY_TAG) : memory_bank_finder<true>(base, tag) { }
};


// ======================> ioport_finder

// device finder template
template<bool _Required>
class ioport_finder : public object_finder_base<ioport_port>
{
public:
	// construction/destruction
	ioport_finder(device_t &base, const char *tag)
		: object_finder_base<ioport_port>(base, tag) { }

	// make reference use transparent as well
	operator ioport_port &() { assert(object_finder_base<ioport_port>::m_target != NULL); return *object_finder_base<ioport_port>::m_target; }

	// allow dereference even when target is NULL so read_safe() can be used
	ioport_port *operator->() const { return object_finder_base<ioport_port>::m_target; }

	// finder
	virtual bool findit(bool isvalidation = false)
	{
		if (isvalidation) return true;
		m_target = m_base.ioport(m_tag);
		return this->report_missing(m_target != NULL, "I/O port", _Required);
	}
};

// optional device finder
class optional_ioport : public ioport_finder<false>
{
public:
	optional_ioport(device_t &base, const char *tag = FINDER_DUMMY_TAG) : ioport_finder<false>(base, tag) { }
};

// required devices are similar but throw an error if they are not found
class required_ioport : public ioport_finder<true>
{
public:
	required_ioport(device_t &base, const char *tag = FINDER_DUMMY_TAG) : ioport_finder<true>(base, tag) { }
};


// ======================> ioport_array_finder

// ioport array finder template
template<int _Count, bool _Required>
class ioport_array_finder
{
	typedef ioport_finder<_Required> ioport_finder_type;

public:
	// construction/destruction
	ioport_array_finder(device_t &base, const char *basetag)
	{
		for (int index = 0; index < _Count; index++)
		{
			strformat(m_tag[index], "%s.%d", basetag, index);
			m_array[index].reset(global_alloc(ioport_finder_type(base, m_tag[index].c_str())));
		}
	}

	ioport_array_finder(device_t &base, const char * const *tags)
	{
		for (int index = 0; index < _Count; index++)
			m_array[index].reset(global_alloc(ioport_finder_type(base, tags[index])));
	}

	// array accessors
	const ioport_finder_type &operator[](int index) const { assert(index < _Count); return *m_array[index]; }
	ioport_finder_type &operator[](int index) { assert(index < _Count); return *m_array[index]; }

protected:
	// internal state
	auto_pointer<ioport_finder_type> m_array[_Count];
	std::string m_tag[_Count];
};

// optional ioport array finder
template<int _Count>
class optional_ioport_array: public ioport_array_finder<_Count, false>
{
public:
	optional_ioport_array(device_t &base, const char *basetag) : ioport_array_finder<_Count, false>(base, basetag) { }
	optional_ioport_array(device_t &base, const char * const *tags) : ioport_array_finder<_Count, false>(base, tags) { }
};

// required ioport array finder
template<int _Count>
class required_ioport_array: public ioport_array_finder<_Count, true>
{
public:
	required_ioport_array(device_t &base, const char *basetag) : ioport_array_finder<_Count, true>(base, basetag) { }
	required_ioport_array(device_t &base, const char * const *tags) : ioport_array_finder<_Count, true>(base, tags) { }
};


// ======================> region_ptr_finder

// memory region pointer finder template
template<typename _PointerType, bool _Required>
class region_ptr_finder : public object_finder_base<_PointerType>
{
public:
	// construction/destruction
	region_ptr_finder(device_t &base, const char *tag)
		: object_finder_base<_PointerType>(base, tag),
			m_length(0) { }

	// operators to make use transparent
	_PointerType operator[](int index) const { assert(index < m_length); return this->m_target[index]; }
	_PointerType &operator[](int index) { assert(index < m_length); return this->m_target[index]; }

	// getter for explicit fetching
	UINT32 length() const { return m_length; }
	UINT32 bytes() const { return m_length * sizeof(_PointerType); }
	UINT32 mask() const { return m_length - 1; } // only valid if length is known to be a power of 2

	// finder
	virtual bool findit(bool isvalidation = false)
	{
		if (isvalidation) return true;
		this->m_target = reinterpret_cast<_PointerType *>(this->find_memregion(sizeof(_PointerType), m_length, _Required));
		return this->report_missing(this->m_target != NULL, "memory region", _Required);
	}

protected:
	// internal state
	size_t m_length;
};

// optional region pointer finder
template<class _PointerType>
class optional_region_ptr : public region_ptr_finder<_PointerType, false>
{
public:
	optional_region_ptr(device_t &base, const char *tag = FINDER_DUMMY_TAG) : region_ptr_finder<_PointerType, false>(base, tag) { }
};

// required region pointer finder
template<class _PointerType>
class required_region_ptr : public region_ptr_finder<_PointerType, true>
{
public:
	required_region_ptr(device_t &base, const char *tag = FINDER_DUMMY_TAG) : region_ptr_finder<_PointerType, true>(base, tag) { }
};
=======
#ifndef MAME_EMU_DEVFIND_H
#define MAME_EMU_DEVFIND_H

#pragma once

#include <iterator>
#include <stdexcept>
#include <type_traits>

//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

/// \brief Helper class to find arrays of devices, etc.
///
/// Useful when a machine/device has a number of similar subdevices, I/O
/// ports, memory regions, etc.  Template arguments are the element type
/// and number of elements in the array.  It's assumed that the element
/// can be constructed with a device_t reference and a C string tag.
template <typename T, unsigned Count>
class object_array_finder
{
private:
	template <unsigned... V> struct indices { };
	template <unsigned C, unsigned... V> struct range : public range<C - 1, C - 1, V...> { };
	template <unsigned... V> struct range<0U, V...> { typedef indices<V...> type; };
	template <unsigned C> using index_range = typename range<C>::type;

	template <typename F, typename... Param, unsigned... V>
	object_array_finder(device_t &base, F const &fmt, unsigned start, indices<V...>, Param const &... arg)
		: m_tag{ util::string_format(fmt, start + V)... }
		, m_array{ { base, m_tag[V].c_str(), arg... }... }
	{
	}

	template <typename... Param, unsigned... V>
	object_array_finder(device_t &base, std::array<char const *, Count> const &tags, indices<V...>, Param const &... arg)
		: m_array{ { base, tags[V], arg... }... }
	{
	}

	/// \brief Generated tag names
	///
	/// Finder objects do not copy the search tag supplied at
	/// construction.  Tags that are programmatically generated at
	/// construction are stored here so they persist until resolution
	/// time (and beyond).
	std::string const m_tag[Count];

	/// \brief The object discovery elements
	///
	/// These are the actual object discovery helpers.  Note that this
	/// member must be initialised after m_tag, as it may depend on
	/// programmatically generated tags.
	T m_array[Count];

public:
	/// \brief Element type for Container concept
	typedef T value_type;

	/// \brief Reference to element type for Container concept
	typedef T &reference;

	/// \brief Reference to constant element type for Container concept
	typedef T const &const_reference;

	/// \brief Iterator for Container concept
	typedef T *iterator;

	/// \brief Constant iterator for Container concept
	typedef T const *const_iterator;

	/// \brief Iterator difference type for Container concept
	typedef typename std::iterator_traits<iterator>::difference_type difference_type;

	/// \brief Size type for Container concept
	typedef std::make_unsigned_t<difference_type> size_type;

	/// \brief Construct with programmatically generated tags
	///
	/// Specify a format string and starting number.  A single unsigned
	/// int format argument is supplied containing the (zero-based)
	/// element index added to the starting number.  For example if
	/// Count = 2, ("p%u_joy", 1) expands to ("p1_joy", "p2_joy").  The
	/// relaxed format rules used by util::string_format apply.
	/// \param [in] base Base device to search from.
	/// \param [in] fmt Search tag format, should expect single unsigned
	///   int argument.
	/// \param [in] start Number to add to element index when
	///   calculating values for string format argument.
	/// \arg [in] Optional additional constructor argument(s) passed to
	///   all elements.
	/// \sa util::string_format
	template <typename F, typename... Param>
	object_array_finder(device_t &base, F const &fmt, unsigned start, Param const &... arg)
		: object_array_finder(base, fmt, start, index_range<Count>(), arg...)
	{
	}

	/// \brief Construct with free-form list of tags
	///
	/// Specify arbitrary tags for objects.  Useful when there is no
	/// particular pattern to the object tags.
	/// \param [in] base Base device to search from.
	/// \param [in] tags Tags to search for, e.g. { "player", "dips" }.
	///   The tags are not copied, it is the caller's responsibility to
	///   ensure the pointers remain valid until resolution time.
	/// \arg [in] Optional additional constructor argument(s) passed to
	///   all elements.
	template <typename... Param>
	object_array_finder(device_t &base, std::array<char const *, Count> const &tags, Param const &... arg)
		: object_array_finder(base, tags, index_range<Count>(), arg...)
	{
	}

	/// \brief Get iterator to first element
	///
	/// Returns an iterator to the first element in the array.
	/// \return Iterator to first element.
	const_iterator begin() const { return m_array; }
	iterator begin() { return m_array; }

	/// \brief Get iterator beyond last element
	///
	/// Returns an iterator one past the last element in the array.
	/// \return Iterator one past last element.
	const_iterator end() const { return m_array + Count; }
	iterator end() { return m_array + Count; }

	/// \brief Get constant iterator to first element
	///
	/// Returns a constant iterator to the first element in the array.
	/// \return Constant iterator to first element.
	const_iterator cbegin() const { return m_array; }

	/// \brief Get constant iterator beyond last element
	///
	/// Returns aconstant iterator one past the last element in the
	/// array.
	/// \return Constant iterator one past last element.
	const_iterator cend() const { return m_array + Count; }

	/// \brief Get array size
	///
	/// Returns number of elements in the array (compile-time constant).
	/// \return The size of the array.
	constexpr size_type size() const { return Count; }

	/// \brief Get maximum array size
	///
	/// Returns maximum number of elements in the array (compile-time
	/// constant, always equal to the size of the array).
	/// \return The size of the array.
	constexpr size_type max_size() const { return Count; }

	/// \brief Does array have no elements
	///
	/// Returns whether the arary has no elements (compile-time
	/// constant).
	/// \return True if the array has no elements, false otherwise.
	constexpr bool empty() const { return !Count; }

	/// \brief Get first element
	///
	/// Returns a reference to the first element in the array.
	/// \return Reference to first element.
	T const &front() const { return m_array[0]; }
	T &front() { return m_array[0]; }

	/// \brief Get last element
	///
	/// Returns a reference to the last element in the array.
	/// \return Reference to last element.
	T const &back() const { return m_array[Count - 1]; }
	T &back() { return m_array[Count - 1]; }

	/// \brief Element accessor (const)
	///
	/// Returns a const reference to the element at the supplied index.
	/// \param [in] index Index of desired element (zero-based).
	/// \return Constant reference to element at specified index.
	T const &operator[](unsigned index) const { assert(index < Count); return m_array[index]; }

	/// \brief Element accessor (non-const)
	///
	/// Returns a reference to the element at the supplied index.
	/// \param [in] index Index of desired element (zero-based).
	/// \return Reference to element at specified index.
	T &operator[](unsigned index) { assert(index < Count); return m_array[index]; }

	/// \brief Checked element accesor
	///
	/// Returns a reference to the element at the supplied index if less
	/// than the size of the array, or throws std::out_of_range
	/// otherwise.
	/// \param [in] index Index of desired element (zero-based).
	/// \return Reference to element at specified index.
	/// \throw std::out_of_range
	T const &at(unsigned index) const { if (Count > index) return m_array[index]; else throw std::out_of_range("Index out of range"); }
	T &at(unsigned index) { if (Count > index) return m_array[index]; else throw std::out_of_range("Index out of range"); }
};


/// \brief Base class for object discovery helpers
///
/// Abstract non-template base class for object auto-discovery helpers.
/// Provides the interface that the device_t uses to manage discovery at
/// resolution time.
class finder_base
{
public:
	/// \brief Destructor
	///
	/// Destruction via base class pointer and dynamic type behaviour
	/// are allowed.
	virtual ~finder_base();

	/// \brief Get next registered object discovery helper
	///
	/// Implementation of basic single-linked list behaviour.
	/// \return Pointer to the next registered object discovery helper,
	///   or nullptr if this is the last.
	finder_base *next() const { return m_next; }

	/// \brief Attempt discovery
	///
	/// Concrete derived classes must implement this member function.
	/// Should return false if the the object is required but not found,
	/// or true otherwise (the report_missing member function can assist
	/// in implementing this behaviour).
	/// \param [in] isvalidation Pass true if this is a dry run (i.e. no
	///   intention to actually start the device), or false otherwise.
	/// \return False if the object is required but not found, or true
	///   otherwise.
	virtual bool findit(bool isvalidation = false) = 0;

	/// \brief Get search tag
	///
	/// Returns the search tag.
	/// \return The object tag this helper will search for.
	const char *finder_tag() const { return m_tag; }

	/// \brief Set search tag
	///
	/// Allows search tag to be changed after construction.  Note that
	/// this must be done before resolution time to take effect.  Also
	/// note that the tag is not copied.
	/// \param [in] tag Updated search tag.  This is not copied, it is
	///   the caller's responsibility to ensure this pointer remains
	///   valid until resolution time.
	void set_tag(char const *tag) { m_tag = tag; }

	/// \brief Dummy tag always treated as not found
	constexpr static char DUMMY_TAG[17] = "finder_dummy_tag";

protected:
	/// \brief Designated constructor
	///
	/// Construct base object discovery helper and register with device
	/// to be invoked at resolution time.
	/// \param [in] base Base device to search from.
	/// \param [in] tag Object tag to search for.  This is not copied,
	///   it is the caller's responsibility to ensure this pointer
	///   remains valid until resolution time.
	finder_base(device_t &base, char const *tag);

	/// \brief Find a memory region
	///
	/// Look up memory region and check that its length and width match
	/// desired values.  Returns pointer to the base of the region if a
	/// matching region is found, or nullptr otherwise.  Prints a
	/// message at warning level if the region is required, a region
	/// with the requested tag is found, but it doesn't match the
	/// desired width and length.
	/// \param [in] width Desired region width in bytes.
	/// \param [in,out] length On entry, the desired region length in
	///   width units, or 0U to match any region length.  Set to the
	///   length of the region in width units if a matching region is
	///   found, or 0U otherwise.
	/// \param [in] required Whether warning message should be printed
	///   if a region with matching tag of incorrect width/length is
	///   found.
	/// \return Base pointer of the memory region if a matching region
	///   is found, or nullptr otherwise.
	void *find_memregion(u8 width, size_t &length, bool required) const;

	/// \brief Check that memory region exists
	///
	/// Walks ROM regions of all devices starting from the root looking
	/// for one with matching tag and length in bytes.  Prints a warning
	/// message if the region is required, a region iwth the requested
	/// tag is found, but its length does not match.  Calls
	/// report_missing to print an error message if the region is
	/// not found.  Returns true if the region is required but no
	/// matching region is found, or false otherwise.
	/// \param [in] bytes Desired region length in bytes, or 0U to match
	///   any length.
	/// \param [in] required True if the region is required, or false if
	///   it is optional.
	/// \return True if the region is optional, or if the region is
	///   required and a matching region is found, or false otherwise.
	bool validate_memregion(size_t bytes, bool required) const;

	/// \brief Find a memory share
	///
	/// Look up memory share and check that its width matches desired
	/// value.  Returns pointer to base of memory share if a matching
	/// share is found, or nullptr otherwise.  Prints a message at
	/// warning level if the memory share is required, a memory share
	/// with the requested tag is found, but it doesn't match the
	/// desired width.
	/// \param [in] width Desired memory share width in bits.
	/// \param [out] bytes Set to memoyr share length in bytes if a
	///   matching memory share is found, otherwise left unchanged.
	/// \param [in] required. Whether warning message should be printed
	///   if a memory share with matching tag of incorrect width is
	///   found.
	/// \return Pointer to base of memory share if a matching memory
	///   share is found, or nullptr otherwise.
	void *find_memshare(u8 width, size_t &bytes, bool required) const;

	/// \brief Log if object was not found
	///
	/// Logs a message at error level if the target object is required
	/// and the search tag is the dummy tag, or the target object is
	/// required and not found.  Logs a message at verbose level if the
	/// object is optional and not found.  Returns true if the object is
	/// found or not required, and false otherwise.
	/// \param [in] found Whether the target object has been found.
	/// \param [in] objname Display name for target object type.
	/// \param [in] required True if the object is required (validation
	///   error if not found), or false if optional.
	/// \return True if found or not required, false otherwise.
	bool report_missing(bool found, char const *objname, bool required) const;

	/// \brief Print a message at warning level
	///
	/// Prints a message if logging is enabled at warning level or more
	/// detailed.  Uses printf semantics of the C runtime library.
	/// \param [in] format Format string as used by printf function in
	///   runtime library
	void printf_warning(char const *format, ...) ATTR_PRINTF(2,3);


	/// \brief Pointer to next registered discovery helper
	///
	/// This is a polymorphic class, so it can't be held in a standardlist
	/// container that requires elements of the same type.  Hence it
	/// implements basic single-linked list behaviour.
	finder_base *const m_next;

	/// \brief Base device to search from
	device_t &m_base;

	/// \brief Object tag to search for
	char const *m_tag;
};


/// \brief Base class for object discovery helpers
///
/// Abstract template base for auto-discovery of objects of a particular
/// type.  Provides implicit cast-to-pointer and pointer member access
/// operators.  Template arguments are the type of object to discover,
/// and whether failure to find the object is considered an error.
/// Assumes that non-null pointer is found, and null pointer is not
/// found.
template <class ObjectClass, bool Required>
class object_finder_base : public finder_base
{
public:
	/// \brief Get pointer to target object
	/// \return Pointer to target object if found, or nullptr otherwise.
	ObjectClass *target() const { return m_target; }

	/// \brief Return whether target has been found
	///
	/// Works on the assumption that the target object pointer will be
	/// non-null if the target has been found, and null otherwise.
	/// \return True if object has been found, or false otherwise.
	bool found() const { return m_target != nullptr; }

	/// \brief Cast-to-pointer operator
	///
	/// Allows implicit casting to a pointer to the target object.
	/// Returns a null pointer if resolution has not been attempted or
	// object was not found.
	/// \return Pointer to target object if found, or nullptr otherwise.
	operator ObjectClass *() const { return m_target; }

	/// \brief Pointer member access operator
	///
	/// Allows pointer-member-style access to members of the target
	/// object.  Asserts that the target object has been found.
	/// \return Pointer to target object if found, or nullptr otherwise.
	virtual ObjectClass *operator->() const { assert(m_target); return m_target; }

protected:
	/// \brief Designated constructor
	///
	/// Construct base, register with base device to be invoked at
	/// resolution time, and initialise target object pointer to
	/// nullptr.
	/// \param [in] base Base device to search from.
	/// \param [in] tag Object tag to search for.  This is not copied,
	///   it is the caller's responsibility to ensure this pointer
	///   remains valid until resolution time.
	object_finder_base(device_t &base, const char *tag) : finder_base(base, tag), m_target(nullptr) { }

	/// \brief Log if object was not found
	///
	/// Logs a message if the target object was not found, and returns
	/// false if this is problematic.  Calls base implementation,
	/// supplying values for found and required parameters.  See base
	/// implementation for more detail.
	/// \param [in] objname Display name for target object type.
	/// \return True if found or not required, false otherwise.
	bool report_missing(char const *objname) const { return finder_base::report_missing(found(), objname, Required); }

	/// \brief Pointer to target object
	///
	/// Pointer to target object, or nullptr if resolution has not been
	/// attempted or the search failed.  Concrete derived classes must
	/// set this in their implementation of the findit member function.
	ObjectClass *m_target;
};


/// \brief Device finder template
///
/// Template arguments are the device class to find, and whether the
/// device is required.  It is a validation error if a required device
/// is not found.  If a device with matching tag is found but the class
/// does not match, a message is printed at warning level.  This class
/// is generally not used directly, instead the optional_device and
/// required_device helpers are used.
/// \sa optional_device required_device
template <class DeviceClass, bool Required>
class device_finder : public object_finder_base<DeviceClass, Required>
{
public:
	/// \brief Device finder constructor
	/// \param [in] base Base device to search from.
	/// \param [in] tag Device tag to search for.  This is not copied,
	///   it is the caller's responsibility to ensure this pointer
	///   remains valid until resolution time.
	device_finder(device_t &base, char const *tag) : object_finder_base<DeviceClass, Required>(base, tag) { }

private:
	/// \brief Find device
	///
	/// Find device of desired type with requested tag.  If a device
	/// with the requested tag is found but the type is incorrect, a
	/// warning message will be printed.  This method is called by the
	/// base device at resolution time.
	/// \param [in] isvalidation True if this is a dry run (not
	///   intending to run the machine, just checking for errors).
	/// \return True if the device is optional or if a matching device
	///   is found, false otherwise.
	virtual bool findit(bool isvalidation) override
	{
		device_t *const device = this->m_base.subdevice(this->m_tag);
		this->m_target = dynamic_cast<DeviceClass *>(device);
		if (device && !this->m_target)
			this->printf_warning("Device '%s' found but is of incorrect type (actual type is %s)\n", this->m_tag, device->name());

		return this->report_missing("device");
	}
};

/// \brief Optional device finder
///
/// Finds device with maching type and tag.  If a device with matching
/// tag is found but the type does not match, a message is printed at
/// warning level.  No error is generated if a matching device is not
/// found (the target object pointer will be null).  If you have a
/// number of similar optional devices, consider using
/// optional_device_array.
/// \sa required_device optional_device_array device_finder
template <class DeviceClass> using optional_device = device_finder<DeviceClass, false>;

/// \brief Required device finder
///
/// Finds device with maching type and tag.  If a device with matching
/// tag is found but the type does not match, a message is printed at
/// warning level.  A validation error is generated if a matching device
/// is not found.  If you have a number of similar required devices,
/// consider using required_device_array.
/// \sa optional_device required_device_array device_finder
template <class DeviceClass> using required_device = device_finder<DeviceClass, true>;

template <class DeviceClass, unsigned Count, bool Required> using device_array_finder = object_array_finder<device_finder<DeviceClass, Required>, Count>;
template <class DeviceClass, unsigned Count> using optional_device_array = device_array_finder<DeviceClass, Count, false>;
template <class DeviceClass, unsigned Count> using required_device_array = device_array_finder<DeviceClass, Count, true>;


/// \brief Memory region finder template
///
/// Template argument is whether the memory region is required.  It is a
/// validation error if a required memory region is not found.  This
/// class is generally not used directly, instead the
/// optional_memory_region and required_memory_region helpers are used.
/// \sa optional_memory_region required_memory_region
template <bool Required>
class memory_region_finder : public object_finder_base<memory_region, Required>
{
public:
	/// \brief Memory region finder constructor
	/// \param [in] base Base device to search from.
	/// \param [in] tag Memory region tag to search for.  This is not
	///   copied, it is the caller's responsibility to ensure this
	///   pointer remains valid until resolution time.
	memory_region_finder(device_t &base, char const *tag) : object_finder_base<memory_region, Required>(base, tag) { }

private:
	/// \brief Find memory region
	///
	/// Find memory region with requested tag.  For a dry run, the
	/// target object pointer will not be set.  This method is called by
	/// the base device at resolution time.
	/// \param [in] isvalidation True if this is a dry run (not
	///   intending to run the machine, just checking for errors).
	/// \return True if the memory region is optional or if a matching
	///   memory region is found, false otherwise.
	virtual bool findit(bool isvalidation) override
	{
		if (isvalidation) return this->validate_memregion(0, Required);
		this->m_target = this->m_base.memregion(this->m_tag);
		return this->report_missing("memory region");
	}
};

/// \brief Optional memory region finder
///
/// Finds memory region with maching tag.  No error is generated if a
/// matching memory region is not found (the target object pointer will
/// be null).  If you have a number of similar optional memory regions,
/// consider using optional_memory_region_array.
/// \sa required_memory_region optional_memory_region_array
///   memory_region_finder
using optional_memory_region = memory_region_finder<false>;

/// \brief Required memory region finder
///
/// Finds memory region with maching tag.  A validation error is
/// generated if a matching memory region is not found.  If you have a
/// number of similar required memory regions, consider using
/// required_memory_region_array.
/// \sa optional_memory_region required_memory_region_array
///   memory_region_finder
using required_memory_region = memory_region_finder<true>;

template <unsigned Count, bool Required> using memory_region_array_finder = object_array_finder<memory_region_finder<Required>, Count>;
template <unsigned Count> using optional_memory_region_array = memory_region_array_finder<Count, false>;
template <unsigned Count> using required_memory_region_array = memory_region_array_finder<Count, true>;


/// \brief Memory bank finder template
///
/// Template argument is whether the memory bank is required.  It is a
/// validation error if a required memory bank is not found.  This class
/// is generally not used directly, instead the optional_memory_bank and
/// required_memory_bank helpers are used.
/// \sa optional_memory_bank required_memory_bank
template <bool Required>
class memory_bank_finder : public object_finder_base<memory_bank, Required>
{
public:
	/// \brief Memory bank finder constructor
	/// \param [in] base Base device to search from.
	/// \param [in] tag Memory bank tag to search for.  This is not
	///   copied, it is the caller's responsibility to ensure this
	///   pointer remains valid until resolution time.
	memory_bank_finder(device_t &base, char const *tag) : object_finder_base<memory_bank, Required>(base, tag) { }

	/// \brief Find memory bank
	///
	/// Find memory bank with requested tag.  Just returns true for a
	/// dry run.  This method is called by the base device at resolution
	/// time.
	/// \param [in] isvalidation True if this is a dry run (not
	///   intending to run the machine, just checking for errors).
	/// \return True if the memory bank is optional, a matching memory
	///   bank is found or this is a dry run, false otherwise.
	virtual bool findit(bool isvalidation) override
	{
		if (isvalidation) return true;
		this->m_target = this->m_base.membank(this->m_tag);
		return this->report_missing("memory bank");
	}
};

/// \brief Optional memory bank finder
///
/// Finds memory bank with maching tag.  No error is generated if a
/// matching memory bank is not found (the target object pointer will
/// be null).  If you have a number of similar optional memory banks,
/// consider using optional_memory_bank_array.
/// \sa required_memory_bank optional_memory_bank_array
///   memory_bank_finder
using optional_memory_bank = memory_bank_finder<false>;

/// \brief Required memory bank finder
///
/// Finds memory bank with maching tag.  A validation error is
/// generated if a matching memory bank is not found.  If you have a
/// number of similar required memory banks, consider using
/// required_memory_bank_array.
/// \sa optional_memory_bank required_memory_bank_array
///   memory_bank_finder
using required_memory_bank = memory_bank_finder<true>;

template <unsigned Count, bool Required> using memory_bank_array_finder = object_array_finder<memory_bank_finder<Required>, Count>;
template <unsigned Count> using optional_memory_bank_array = memory_bank_array_finder<Count, false>;
template <unsigned Count> using required_memory_bank_array = memory_bank_array_finder<Count, true>;


/// \brief I/O port finder template
///
/// Template argument is whether the I/O port is required.  It is a
/// validation error if a required I/O port is not found.  This class is
/// generally not used directly, instead the optional_ioport and
/// required_ioport helpers are used.
/// \sa optional_ioport required_ioport
template <bool Required>
class ioport_finder : public object_finder_base<ioport_port, Required>
{
public:
	/// \brief I/O port finder constructor
	/// \param [in] base Base device to search from.
	/// \param [in] tag I/O port tag to search for.  This is not copied,
	///   it is the caller's responsibility to ensure this pointer
	///   remains valid until resolution time.
	ioport_finder(device_t &base, char const *tag) : object_finder_base<ioport_port, Required>(base, tag) { }

	/// \brief Read I/O port if found or return default value
	///
	/// If the I/O port was found, this reads a value from the I/O port
	/// and returns it.  If the I/O port was not found, the default
	/// value (supplied as a parameter) is returned.
	/// \param [in] defval Value to return if I/O port was not found.
	/// \return Value read from I/O port if found, or supplied default
	///   value otherwise.
	ioport_value read_safe(ioport_value defval) { return this->m_target ? this->m_target->read() : defval; }

private:
	/// \brief Find I/O port
	///
	/// Find I/O port with requested tag.  Just returns true for a dry
	/// run.  This method is called by the base device at resolution
	/// time.
	/// \param [in] isvalidation True if this is a dry run (not
	///   intending to run the machine, just checking for errors).
	/// \return True if the I/O port is optional, a matching I/O port is
	///   is found or this is a dry run, false otherwise.
	virtual bool findit(bool isvalidation) override
	{
		if (isvalidation) return true;
		this->m_target = this->m_base.ioport(this->m_tag);
		return this->report_missing("I/O port");
	}
};

/// \brief Optional I/O port finder
///
/// Finds I/O port with maching tag.  No error is generated if a
/// matching I/O port is not found (the target object pointer will be
/// null).  If you have a number of similar optional I/O ports, consider
/// using optional_ioport_array.
/// \sa required_ioport optional_ioport_array ioport_finder
using optional_ioport = ioport_finder<false>;

/// \brief Required I/O port finder
///
/// Finds I/O port with maching tag.  A validation error is generated if
/// a matching I/O port is not found.  If you have a number of similar
/// required I/O ports, consider using required_ioport_array.
/// \sa optional_ioport required_ioport_array ioport_finder
using required_ioport = ioport_finder<true>;

template <unsigned Count, bool Required> using ioport_array_finder = object_array_finder<ioport_finder<Required>, Count>;
template <unsigned Count> using optional_ioport_array = ioport_array_finder<Count, false>;
template <unsigned Count> using required_ioport_array = ioport_array_finder<Count, true>;


/// \brief Memory region base pointer finder
///
/// Template arguments are the element type of the memory region and
/// whether the memory region is required.  It is a validation error if
/// a required memory region is not found.  This class is generally not
/// used directly, instead the optional_region_ptr and
/// required_region_ptr helpers are used.
/// \sa optional_region_ptr required_region_ptr
template <typename PointerType, bool Required>
class region_ptr_finder : public object_finder_base<PointerType, Required>
{
public:
	/// \brief Memory region base pointer finder constructor
	///
	/// Desired width is implied by sizeof(PointerType).
	/// \param [in] base Base device to search from.
	/// \param [in] tag Memory region tag to search for.  This is not
	///   copied, it is the caller's responsibility to ensure this
	///   pointer remains valid until resolution time.
	/// \param [in] length Desired memory region length in units of the
	///   size of the element type, or zero to match any region length.
	region_ptr_finder(device_t &base, char const *tag, size_t length = 0)
		: object_finder_base<PointerType, Required>(base, tag)
		, m_desired_length(length)
		, m_length(0)
	{
	}

	/// \brief Array access operator
	///
	/// Returns a non-const reference to the element of the memory
	/// region at the supplied zero-based index.
	/// Behaviour is undefined for negative element indices.
	/// \param [in] index Non-negative element index.
	/// \return Non-const reference to element at requested index.
	PointerType &operator[](int index) const { assert(index < m_length); return this->m_target[index]; }

	/// \brief Get length in units of elements
	/// \return Length in units of elements or zero if no matching
	///   memory region has been found.
	u32 length() const { return m_length; }

	/// \brief Get length in units of bytes
	/// \return Length in units of bytes or zero if no matching memory
	///   region has been found.
	u32 bytes() const { return m_length * sizeof(PointerType); }

	/// \brief Get index mask
	///
	/// Returns the length in units of elements minus one, which can be
	/// used as a mask for index values if the length is a power of two.
	/// Result is undefined if no matching memory region has been found.
	/// \return Length in units of elements minus one.
	u32 mask() const { return m_length - 1; }

private:
	/// \brief Find memory region base pointer
	///
	/// Find base pointer of memory region with with requested tag,
	/// width and length.  Width of memory region is checked against
	/// sizeof(PointerType).  For a dry run, only the tag and length are
	/// checked - the width is not checked and the target pointer is not
	/// set.  This method is called by the base device at resolution
	/// time.
	/// \param [in] isvalidation True if this is a dry run (not
	///   intending to run the machine, just checking for errors).
	/// \return True if the memory region is optional or a matching
	///   memory region is found, or false otherwise.
	virtual bool findit(bool isvalidation) override
	{
		if (isvalidation) return this->validate_memregion(sizeof(PointerType) * m_desired_length, Required);
		m_length = m_desired_length;
		this->m_target = reinterpret_cast<PointerType *>(this->find_memregion(sizeof(PointerType), m_length, Required));
		return this->report_missing("memory region");
	}

	/// \brief Desired region length
	///
	/// Desired region length in units of elements.
	size_t const m_desired_length;

	/// \brief Matched region length
	///
	/// Actual length of the region that was found in units of
	/// elements, or zero if no matching region has been found.
	size_t m_length;
};

/// \brief Optional memory region base pointer finder
///
/// Finds base pointer of memory region with maching tag, width and
/// length.  No error is generated if a matching memory region is not
/// found (the target pointer will be null).  If you have a number of
/// similar optional memory regions, consider using
/// optional_region_ptr_array.
/// \sa required_region_ptr optional_region_ptr_array region_ptr_finder
template <typename PointerType> using optional_region_ptr = region_ptr_finder<PointerType, false>;

/// \brief Required memory region base pointer finder
///
/// Finds base pointer of memory region with maching tag, width and
/// length.  A validation error is generated if a matching memory region
/// is not found.  If you have a number of similar required memory
/// regions, consider using required_region_ptr_array.
/// \sa optional_region_ptr required_region_ptr_array region_ptr_finder
template <typename PointerType> using required_region_ptr = region_ptr_finder<PointerType, true>;

template <typename PointerType, unsigned Count, bool Required> using region_ptr_array_finder = object_array_finder<region_ptr_finder<PointerType, Required>, Count>;
template <typename PointerType, unsigned Count> using optional_region_ptr_array = region_ptr_array_finder<PointerType, Count, false>;
template <typename PointerType, unsigned Count> using required_region_ptr_array = region_ptr_array_finder<PointerType, Count, true>;
>>>>>>> upstream/master


// ======================> shared_ptr_finder

// shared pointer finder template
<<<<<<< HEAD
template<typename _PointerType, bool _Required>
class shared_ptr_finder : public object_finder_base<_PointerType>
{
public:
	// construction/destruction
	shared_ptr_finder(device_t &base, const char *tag, UINT8 width = sizeof(_PointerType) * 8)
		: object_finder_base<_PointerType>(base, tag),
			m_bytes(0),
			m_width(width) { }

	// operators to make use transparent
	_PointerType operator[](int index) const { return this->m_target[index]; }
	_PointerType &operator[](int index) { return this->m_target[index]; }

	// getter for explicit fetching
	UINT32 bytes() const { return m_bytes; }
	UINT32 mask() const { return m_bytes - 1; } // FIXME: wrong when sizeof(_PointerType) != 1

	// setter for setting the object
	void set_target(_PointerType *target, size_t bytes) { this->m_target = target; m_bytes = bytes; }

	// dynamic allocation of a shared pointer
	void allocate(UINT32 entries)
=======
template <typename PointerType, bool Required>
class shared_ptr_finder : public object_finder_base<PointerType, Required>
{
public:
	// construction/destruction
	shared_ptr_finder(device_t &base, char const *tag, u8 width = sizeof(PointerType) * 8)
		: object_finder_base<PointerType, Required>(base, tag)
		, m_width(width)
		, m_bytes(0)
		, m_allocated(0)
	{
	}

	// operators to make use transparent
	PointerType &operator[](int index) const { return this->m_target[index]; }

	// getter for explicit fetching
	u32 bytes() const { return m_bytes; }
	u32 mask() const { return m_bytes - 1; } // FIXME: wrong when sizeof(PointerType) != 1

	// setter for setting the object
	void set_target(PointerType *target, size_t bytes) { this->m_target = target; m_bytes = bytes; }

	// dynamic allocation of a shared pointer
	void allocate(u32 entries)
>>>>>>> upstream/master
	{
		assert(m_allocated.empty());
		m_allocated.resize(entries);
		this->m_target = &m_allocated[0];
<<<<<<< HEAD
		m_bytes = entries * sizeof(_PointerType);
		this->m_base.save_item(this->m_allocated, this->m_tag);
	}

	// finder
	virtual bool findit(bool isvalidation = false)
	{
		if (isvalidation) return true;
		this->m_target = reinterpret_cast<_PointerType *>(this->find_memshare(m_width, m_bytes, _Required));
		return this->report_missing(this->m_target != NULL, "shared pointer", _Required);
	}

protected:
	// internal state
	size_t m_bytes;
	UINT8 m_width;
	std::vector<_PointerType> m_allocated;
};

// optional shared pointer finder
template<class _PointerType>
class optional_shared_ptr : public shared_ptr_finder<_PointerType, false>
{
public:
	optional_shared_ptr(device_t &base, const char *tag = FINDER_DUMMY_TAG, UINT8 width = sizeof(_PointerType) * 8) : shared_ptr_finder<_PointerType, false>(base, tag, width) { }
};

// required shared pointer finder
template<class _PointerType>
class required_shared_ptr : public shared_ptr_finder<_PointerType, true>
{
public:
	required_shared_ptr(device_t &base, const char *tag = FINDER_DUMMY_TAG, UINT8 width = sizeof(_PointerType) * 8) : shared_ptr_finder<_PointerType, true>(base, tag, width) { }
};


// ======================> shared_ptr_array_finder

// shared pointer array finder template
template<typename _PointerType, int _Count, bool _Required>
class shared_ptr_array_finder
{
	typedef shared_ptr_finder<_PointerType, _Required> shared_ptr_type;

public:
	// construction/destruction
	shared_ptr_array_finder(device_t &base, const char *basetag, UINT8 width = sizeof(_PointerType) * 8)
	{
		for (int index = 0; index < _Count; index++)
		{
			strformat(m_tag[index],"%s.%d", basetag, index);
			m_array[index].reset(global_alloc(shared_ptr_type(base, m_tag[index].c_str(), width)));
		}
	}

	// array accessors
	const shared_ptr_type &operator[](int index) const { assert(index < _Count); return *m_array[index]; }
	shared_ptr_type &operator[](int index) { assert(index < _Count); return *m_array[index]; }

protected:
	// internal state
	auto_pointer<shared_ptr_type> m_array[_Count];
	std::string m_tag[_Count];
};

// optional shared pointer array finder
template<class _PointerType, int _Count>
class optional_shared_ptr_array : public shared_ptr_array_finder<_PointerType, _Count, false>
{
public:
	optional_shared_ptr_array(device_t &base, const char *tag, UINT8 width = sizeof(_PointerType) * 8) : shared_ptr_array_finder<_PointerType, _Count, false>(base, tag, width) { }
};

// required shared pointer array finder
template<class _PointerType, int _Count>
class required_shared_ptr_array : public shared_ptr_array_finder<_PointerType, _Count, true>
{
public:
	required_shared_ptr_array(device_t &base, const char *tag, UINT8 width = sizeof(_PointerType) * 8) : shared_ptr_array_finder<_PointerType, _Count, true>(base, tag, width) { }
};


#endif  /* __DEVFIND_H__ */
=======
		m_bytes = entries * sizeof(PointerType);
		this->m_base.save_item(m_allocated, this->m_tag);
	}

private:
	// finder
	virtual bool findit(bool isvalidation) override
	{
		if (isvalidation) return true;
		this->m_target = reinterpret_cast<PointerType *>(this->find_memshare(m_width, m_bytes, Required));
		return this->report_missing("shared pointer");
	}

	// internal state
	u8 const m_width;
	size_t m_bytes;
	std::vector<PointerType> m_allocated;
};

template <typename PointerType> using optional_shared_ptr = shared_ptr_finder<PointerType, false>;
template <typename PointerType> using required_shared_ptr = shared_ptr_finder<PointerType, true>;
template <typename PointerType, unsigned Count, bool Required> using shared_ptr_array_finder = object_array_finder<shared_ptr_finder<PointerType, Required>, Count>;
template <typename PointerType, unsigned Count> using optional_shared_ptr_array = shared_ptr_array_finder<PointerType, Count, false>;
template <typename PointerType, unsigned Count> using required_shared_ptr_array = shared_ptr_array_finder<PointerType, Count, true>;



//**************************************************************************
//  EXTERNAL TEMPLATE INSTANTIATIONS
//**************************************************************************

extern template class object_finder_base<memory_region, false>;
extern template class object_finder_base<memory_region, true>;
extern template class object_finder_base<memory_bank, false>;
extern template class object_finder_base<memory_bank, true>;
extern template class object_finder_base<ioport_port, false>;
extern template class object_finder_base<ioport_port, true>;

extern template class object_finder_base<u8, false>;
extern template class object_finder_base<u8, true>;
extern template class object_finder_base<u16, false>;
extern template class object_finder_base<u16, true>;
extern template class object_finder_base<u32, false>;
extern template class object_finder_base<u32, true>;
extern template class object_finder_base<u64, false>;
extern template class object_finder_base<u64, true>;

extern template class object_finder_base<s8, false>;
extern template class object_finder_base<s8, true>;
extern template class object_finder_base<s16, false>;
extern template class object_finder_base<s16, true>;
extern template class object_finder_base<s32, false>;
extern template class object_finder_base<s32, true>;
extern template class object_finder_base<s64, false>;
extern template class object_finder_base<s64, true>;

extern template class memory_region_finder<false>;
extern template class memory_region_finder<true>;

extern template class memory_bank_finder<false>;
extern template class memory_bank_finder<true>;

extern template class ioport_finder<false>;
extern template class ioport_finder<true>;

extern template class region_ptr_finder<u8, false>;
extern template class region_ptr_finder<u8, true>;
extern template class region_ptr_finder<u16, false>;
extern template class region_ptr_finder<u16, true>;
extern template class region_ptr_finder<u32, false>;
extern template class region_ptr_finder<u32, true>;
extern template class region_ptr_finder<u64, false>;
extern template class region_ptr_finder<u64, true>;

extern template class region_ptr_finder<s8, false>;
extern template class region_ptr_finder<s8, true>;
extern template class region_ptr_finder<s16, false>;
extern template class region_ptr_finder<s16, true>;
extern template class region_ptr_finder<s32, false>;
extern template class region_ptr_finder<s32, true>;
extern template class region_ptr_finder<s64, false>;
extern template class region_ptr_finder<s64, true>;

extern template class shared_ptr_finder<u8, false>;
extern template class shared_ptr_finder<u8, true>;
extern template class shared_ptr_finder<u16, false>;
extern template class shared_ptr_finder<u16, true>;
extern template class shared_ptr_finder<u32, false>;
extern template class shared_ptr_finder<u32, true>;
extern template class shared_ptr_finder<u64, false>;
extern template class shared_ptr_finder<u64, true>;

extern template class shared_ptr_finder<s8, false>;
extern template class shared_ptr_finder<s8, true>;
extern template class shared_ptr_finder<s16, false>;
extern template class shared_ptr_finder<s16, true>;
extern template class shared_ptr_finder<s32, false>;
extern template class shared_ptr_finder<s32, true>;
extern template class shared_ptr_finder<s64, false>;
extern template class shared_ptr_finder<s64, true>;

#endif // MAME_EMU_DEVFIND_H
/** \} */
>>>>>>> upstream/master
