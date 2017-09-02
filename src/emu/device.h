// license:BSD-3-Clause
// copyright-holders:Aaron Giles
/***************************************************************************

    device.h

    Device interface functions.

***************************************************************************/

#pragma once

#ifndef __EMU_H__
#error Dont include this file directly; include emu.h instead.
#endif

<<<<<<< HEAD
#ifndef __DEVICE_H__
#define __DEVICE_H__
=======
#ifndef MAME_EMU_DEVICE_H
#define MAME_EMU_DEVICE_H

#include <iterator>
#include <memory>
#include <string>
#include <type_traits>
#include <typeinfo>
#include <unordered_map>
#include <vector>
>>>>>>> upstream/master



//**************************************************************************
//  MACROS
//**************************************************************************

// macro for specifying a clock derived from an owning device
#define DERIVED_CLOCK(num, den)     (0xff000000 | ((num) << 12) | ((den) << 0))



//**************************************************************************
//  DEVICE CONFIGURATION MACROS
//**************************************************************************

// configure devices
<<<<<<< HEAD
#define MCFG_DEVICE_CONFIG(_config) \
	device_t::static_set_static_config(*device, &(_config));
=======
>>>>>>> upstream/master
#define MCFG_DEVICE_CLOCK(_clock) \
	device_t::static_set_clock(*device, _clock);
#define MCFG_DEVICE_INPUT_DEFAULTS(_config) \
	device_t::static_set_input_default(*device, DEVICE_INPUT_DEFAULTS_NAME(_config));

#define DECLARE_READ_LINE_MEMBER(name)      int  name()
#define READ_LINE_MEMBER(name)              int  name()
#define DECLARE_WRITE_LINE_MEMBER(name)     void name(ATTR_UNUSED int state)
#define WRITE_LINE_MEMBER(name)             void name(ATTR_UNUSED int state)



//**************************************************************************
<<<<<<< HEAD
//  TYPE DEFINITIONS
//**************************************************************************

// forward references
class memory_region;
class device_debug;
class device_t;
class device_interface;
class device_execute_interface;
class device_memory_interface;
class device_state_interface;
class validity_checker;
struct rom_entry;
class machine_config;
class emu_timer;
struct input_device_default;
class finder_base;


// exception classes
class device_missing_dependencies : public emu_exception { };


// a device_type is simply a pointer to its alloc function
typedef device_t *(*device_type)(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);


// this template function creates a stub which constructs a device
template<class _DeviceClass>
device_t *device_creator(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock)
{
	return global_alloc(_DeviceClass(mconfig, tag, owner, clock));
}


// timer IDs for devices
typedef UINT32 device_timer_id;
=======
//  GLOBAL VARIABLES
//**************************************************************************

// use this to refer to the owning device when providing a device tag
static const char DEVICE_SELF[] = "";

// use this to refer to the owning device's owner when providing a device tag
static const char DEVICE_SELF_OWNER[] = "^";


//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

namespace emu { namespace detail {

class device_type_impl;


struct device_feature
{
	enum type : u32
	{
		PROTECTION  = u32(1) <<  0,
		PALETTE     = u32(1) <<  1,
		GRAPHICS    = u32(1) <<  2,
		SOUND       = u32(1) <<  3,
		CONTROLS    = u32(1) <<  4,
		KEYBOARD    = u32(1) <<  5,
		MOUSE       = u32(1) <<  6,
		MICROPHONE  = u32(1) <<  7,
		CAMERA      = u32(1) <<  8,
		DISK        = u32(1) <<  9,
		PRINTER     = u32(1) << 10,
		LAN         = u32(1) << 11,
		WAN         = u32(1) << 12,
		TIMING      = u32(1) << 13,

		NONE        = u32(0),
		ALL         = (u32(1) << 14) - 1U
	};
};

DECLARE_ENUM_BITWISE_OPERATORS(device_feature::type);


class device_registrar
{
private:
	class const_iterator_helper;

public:
	class const_iterator
	{
	public:
		typedef std::ptrdiff_t difference_type;
		typedef device_type_impl value_type;
		typedef device_type_impl *pointer;
		typedef device_type_impl &reference;
		typedef std::forward_iterator_tag iterator_category;

		const_iterator() = default;
		const_iterator(const_iterator const &) = default;
		const_iterator &operator=(const_iterator const &) = default;

		bool operator==(const_iterator const &that) const { return m_type == that.m_type; }
		bool operator!=(const_iterator const &that) const { return m_type != that.m_type; }
		reference operator*() const { assert(m_type); return *m_type; }
		pointer operator->() const { return m_type; }
		const_iterator &operator++();
		const_iterator operator++(int) { const_iterator const result(*this); ++*this; return result; }

	private:
		friend class const_iterator_helper;

		pointer m_type = nullptr;
	};

	// explicit constructor is required for const variable initialization
	constexpr device_registrar() { }

	const_iterator begin() const { return cbegin(); }
	const_iterator end() const { return cend(); }
	const_iterator cbegin() const;
	const_iterator cend() const;

private:
	friend class device_type_impl;

	class const_iterator_helper : public const_iterator
	{
	public:
		const_iterator_helper(device_type_impl *type) { m_type = type; }
	};

	static device_type_impl *register_device(device_type_impl &type);
};


template <class DeviceClass, char const *ShortName, char const *FullName, char const *Source>
struct device_tag_struct { typedef DeviceClass type; };
template <class DriverClass, char const *ShortName, char const *FullName, char const *Source, device_feature::type Unemulated, device_feature::type Imperfect>
struct driver_tag_struct { typedef DriverClass type; };

template <class DeviceClass, char const *ShortName, char const *FullName, char const *Source>
auto device_tag_func() { return device_tag_struct<DeviceClass, ShortName, FullName, Source>{ }; };
template <class DriverClass, char const *ShortName, char const *FullName, char const *Source, device_feature::type Unemulated, device_feature::type Imperfect>
auto driver_tag_func() { return driver_tag_struct<DriverClass, ShortName, FullName, Source, Unemulated, Imperfect>{ }; };

class device_type_impl
{
private:
	friend class device_registrar;

	typedef std::unique_ptr<device_t> (*create_func)(device_type_impl const &type, machine_config const &mconfig, char const *tag, device_t *owner, u32 clock);

	device_type_impl(device_type_impl const &) = delete;
	device_type_impl(device_type_impl &&) = delete;
	device_type_impl &operator=(device_type_impl const &) = delete;
	device_type_impl &operator=(device_type_impl &&) = delete;

	template <typename DeviceClass>
	static std::unique_ptr<device_t> create_device(device_type_impl const &type, machine_config const &mconfig, char const *tag, device_t *owner, u32 clock)
	{
		return make_unique_clear<DeviceClass>(mconfig, tag, owner, clock);
	}

	template <typename DriverClass>
	static std::unique_ptr<device_t> create_driver(device_type_impl const &type, machine_config const &mconfig, char const *tag, device_t *owner, u32 clock)
	{
		assert(!owner);
		assert(!clock);

		return make_unique_clear<DriverClass>(mconfig, type, tag);
	}

	create_func const m_creator;
	std::type_info const &m_type;
	char const *const m_shortname;
	char const *const m_fullname;
	char const *const m_source;
	device_feature::type const m_unemulated_features;
	device_feature::type const m_imperfect_features;

	device_type_impl *m_next;

public:
	device_type_impl(std::nullptr_t)
		: m_creator(nullptr)
		, m_type(typeid(std::nullptr_t))
		, m_shortname(nullptr)
		, m_fullname(nullptr)
		, m_source(nullptr)
		, m_unemulated_features(device_feature::NONE)
		, m_imperfect_features(device_feature::NONE)
		, m_next(nullptr)
	{
	}

	template <class DeviceClass, char const *ShortName, char const *FullName, char const *Source>
	device_type_impl(device_tag_struct<DeviceClass, ShortName, FullName, Source> (*)())
		: m_creator(&create_device<DeviceClass>)
		, m_type(typeid(DeviceClass))
		, m_shortname(ShortName)
		, m_fullname(FullName)
		, m_source(Source)
		, m_unemulated_features(DeviceClass::unemulated_features())
		, m_imperfect_features(DeviceClass::imperfect_features())
		, m_next(device_registrar::register_device(*this))
	{
	}

	template <class DriverClass, char const *ShortName, char const *FullName, char const *Source, device_feature::type Unemulated, device_feature::type Imperfect>
	device_type_impl(driver_tag_struct<DriverClass, ShortName, FullName, Source, Unemulated, Imperfect> (*)())
		: m_creator(&create_driver<DriverClass>)
		, m_type(typeid(DriverClass))
		, m_shortname(ShortName)
		, m_fullname(FullName)
		, m_source(Source)
		, m_unemulated_features(DriverClass::unemulated_features() | Unemulated)
		, m_imperfect_features((DriverClass::imperfect_features() & ~Unemulated) | Imperfect)
		, m_next(nullptr)
	{
	}

	std::type_info const &type() const { return m_type; }
	char const *shortname() const { return m_shortname; }
	char const *fullname() const { return m_fullname; }
	char const *source() const { return m_source; }
	device_feature::type unemulated_features() const { return m_unemulated_features; }
	device_feature::type imperfect_features() const { return m_imperfect_features; }

	std::unique_ptr<device_t> operator()(machine_config const &mconfig, char const *tag, device_t *owner, u32 clock) const
	{
		return m_creator(*this, mconfig, tag, owner, clock);
	}

	explicit operator bool() const { return bool(m_creator); }
	bool operator==(device_type_impl const &that) const { return &that == this; }
	bool operator!=(device_type_impl const &that) const { return &that != this; }
};


inline device_registrar::const_iterator &device_registrar::const_iterator::operator++() { m_type = m_type->m_next; return *this; }

} } // namespace emu::detail


// device types
typedef emu::detail::device_type_impl const &device_type;
typedef std::add_pointer_t<device_type> device_type_ptr;
extern emu::detail::device_registrar const registered_device_types;

template <
		typename DeviceClass,
		char const *ShortName,
		char const *FullName,
		char const *Source>
constexpr auto device_creator = &emu::detail::device_tag_func<DeviceClass, ShortName, FullName, Source>;

template <
		typename DriverClass,
		char const *ShortName,
		char const *FullName,
		char const *Source,
		emu::detail::device_feature::type Unemulated,
		emu::detail::device_feature::type Imperfect>
constexpr auto driver_device_creator = &emu::detail::driver_tag_func<DriverClass, ShortName, FullName, Source, Unemulated, Imperfect>;

#define DECLARE_DEVICE_TYPE(Type, Class) \
		extern device_type const Type; \
		class Class; \
		extern template class device_finder<Class, false>; \
		extern template class device_finder<Class, true>;

#define DECLARE_DEVICE_TYPE_NS(Type, Namespace, Class) \
		extern device_type const Type; \
		extern template class device_finder<Namespace::Class, false>; \
		extern template class device_finder<Namespace::Class, true>;

#define DEFINE_DEVICE_TYPE(Type, Class, ShortName, FullName) \
		namespace { \
			struct Class##_device_traits { static constexpr char const shortname[] = ShortName, fullname[] = FullName, source[] = __FILE__; }; \
			constexpr char const Class##_device_traits::shortname[], Class##_device_traits::fullname[], Class##_device_traits::source[]; \
		} \
		device_type const Type = device_creator<Class, (Class##_device_traits::shortname), (Class##_device_traits::fullname), (Class##_device_traits::source)>; \
		template class device_finder<Class, false>; \
		template class device_finder<Class, true>;

#define DEFINE_DEVICE_TYPE_NS(Type, Namespace, Class, ShortName, FullName) \
		namespace { \
			struct Class##_device_traits { static constexpr char const shortname[] = ShortName, fullname[] = FullName, source[] = __FILE__; }; \
			constexpr char const Class##_device_traits::shortname[], Class##_device_traits::fullname[], Class##_device_traits::source[]; \
		} \
		device_type const Type = device_creator<Namespace::Class, (Class##_device_traits::shortname), (Class##_device_traits::fullname), (Class##_device_traits::source)>; \
		template class device_finder<Namespace::Class, false>; \
		template class device_finder<Namespace::Class, true>;


// exception classes
class device_missing_dependencies : public emu_exception { };


// timer IDs for devices
typedef u32 device_timer_id;
>>>>>>> upstream/master

// ======================> device_t

// device_t represents a device
class device_t : public delegate_late_bind
{
	DISABLE_COPYING(device_t);

<<<<<<< HEAD
	friend class device_interface;
	friend class device_memory_interface;
	friend class device_state_interface;
	friend class device_execute_interface;
	friend class simple_list<device_t>;
	friend class device_list;
	friend class machine_config;
	friend class running_machine;
	friend class finder_base;

protected:
	// construction/destruction
	device_t(const machine_config &mconfig, device_type type, const char *name, const char *tag, device_t *owner, UINT32 clock, const char *shortname, const char *source);
public:
	virtual ~device_t();

	// getters
	running_machine &machine() const { /*assert(m_machine != NULL);*/ return *m_machine; }
	const char *tag() const { return m_tag.c_str(); }
	const char *basetag() const { return m_basetag.c_str(); }
	device_type type() const { return m_type; }
	const char *name() const { return m_name.c_str(); }
	const char *shortname() const { return m_shortname.c_str(); }
	const char *searchpath() const { return m_searchpath.c_str(); }
	const char *source() const { return m_source.c_str(); }
	device_t *owner() const { return m_owner; }
	device_t *next() const { return m_next; }
	UINT32 configured_clock() const { return m_configured_clock; }
	const void *static_config() const { return m_static_config; }
	const machine_config &mconfig() const { return m_machine_config; }
	const input_device_default *input_ports_defaults() const { return m_input_defaults; }
	const rom_entry *rom_region() const { return device_rom_region(); }
	machine_config_constructor machine_config_additions() const { return device_mconfig_additions(); }
	ioport_constructor input_ports() const { return device_input_ports(); }
	UINT8 default_bios() const { return m_default_bios; }
	UINT8 system_bios() const { return m_system_bios; }
	std::string default_bios_tag() const { return m_default_bios_tag; }
	std::string parameter(const char *tag) const;

	// interface helpers
	device_interface *first_interface() const { return m_interface_list; }
	template<class _DeviceClass> bool interface(_DeviceClass *&intf) { intf = dynamic_cast<_DeviceClass *>(this); return (intf != NULL); }
	template<class _DeviceClass> bool interface(_DeviceClass *&intf) const { intf = dynamic_cast<const _DeviceClass *>(this); return (intf != NULL); }

	// specialized helpers for common core interfaces
	bool interface(device_execute_interface *&intf) { intf = m_execute; return (intf != NULL); }
	bool interface(device_execute_interface *&intf) const { intf = m_execute; return (intf != NULL); }
	bool interface(device_memory_interface *&intf) { intf = m_memory; return (intf != NULL); }
	bool interface(device_memory_interface *&intf) const { intf = m_memory; return (intf != NULL); }
	bool interface(device_state_interface *&intf) { intf = m_state; return (intf != NULL); }
	bool interface(device_state_interface *&intf) const { intf = m_state; return (intf != NULL); }
	device_execute_interface &execute() const { assert(m_execute != NULL); return *m_execute; }
	device_memory_interface &memory() const { assert(m_memory != NULL); return *m_memory; }
	device_state_interface &state() const { assert(m_state != NULL); return *m_state; }

	// owned object helpers
	device_t *first_subdevice() const { return m_subdevice_list.first(); }
	std::string subtag(const char *tag) const;
	std::string siblingtag(const char *tag) const { return (this != NULL && m_owner != NULL) ? m_owner->subtag(tag) : std::string(tag); }
=======
	friend class simple_list<device_t>;
	friend class running_machine;
	friend class finder_base;

	class subdevice_list
	{
		friend class device_t;
		friend class machine_config;

	public:
		// construction/destruction
		subdevice_list() { }

		// getters
		device_t *first() const { return m_list.first(); }
		int count() const { return m_list.count(); }
		bool empty() const { return m_list.empty(); }

		// range iterators
		using auto_iterator = simple_list<device_t>::auto_iterator;
		auto_iterator begin() const { return m_list.begin(); }
		auto_iterator end() const { return m_list.end(); }

	private:
		// private helpers
		device_t *find(const std::string &name) const
		{
			device_t *curdevice;
			for (curdevice = m_list.first(); curdevice != nullptr; curdevice = curdevice->next())
				if (name.compare(curdevice->m_basetag) == 0)
					return curdevice;
			return nullptr;
		}

		// private state
		simple_list<device_t>   m_list;         // list of sub-devices we own
		mutable std::unordered_map<std::string,device_t *> m_tagmap;      // map of devices looked up and found by subtag
	};

	class interface_list
	{
		friend class device_t;
		friend class device_interface;
		friend class device_memory_interface;
		friend class device_state_interface;
		friend class device_execute_interface;

	public:
		class auto_iterator
		{
		public:
			typedef std::ptrdiff_t difference_type;
			typedef device_interface value_type;
			typedef device_interface *pointer;
			typedef device_interface &reference;
			typedef std::forward_iterator_tag iterator_category;

			// construction/destruction
			auto_iterator(device_interface *intf) : m_current(intf) { }

			// required operator overloads
			bool operator==(const auto_iterator &iter) const { return m_current == iter.m_current; }
			bool operator!=(const auto_iterator &iter) const { return m_current != iter.m_current; }
			device_interface &operator*() const { return *m_current; }
			device_interface *operator->() const { return m_current; }
			auto_iterator &operator++();
			auto_iterator operator++(int);

		private:
			// private state
			device_interface *m_current;
		};

		// construction/destruction
		interface_list() : m_head(nullptr), m_execute(nullptr), m_memory(nullptr), m_state(nullptr) { }

		// getters
		device_interface *first() const { return m_head; }

		// range iterators
		auto_iterator begin() const { return auto_iterator(m_head); }
		auto_iterator end() const { return auto_iterator(nullptr); }

	private:
		device_interface *m_head;               // head of interface list
		device_execute_interface *m_execute;    // pre-cached pointer to execute interface
		device_memory_interface *m_memory;      // pre-cached pointer to memory interface
		device_state_interface *m_state;        // pre-cached pointer to state interface
	};

protected:
	// construction/destruction
	device_t(
			const machine_config &mconfig,
			device_type type,
			const char *tag,
			device_t *owner,
			u32 clock);

public:
	// device flags
	using feature = emu::detail::device_feature;
	using feature_type = emu::detail::device_feature::type;
	static constexpr feature_type unemulated_features() { return feature::NONE; }
	static constexpr feature_type imperfect_features() { return feature::NONE; }

	virtual ~device_t();

	// getters
	bool has_running_machine() const { return m_machine != nullptr; }
	running_machine &machine() const { /*assert(m_machine != nullptr);*/ return *m_machine; }
	const char *tag() const { return m_tag.c_str(); }
	const char *basetag() const { return m_basetag.c_str(); }
	device_type type() const { return m_type; }
	const char *name() const { return m_type.fullname(); }
	const char *shortname() const { return m_type.shortname(); }
	const char *searchpath() const { return m_searchpath.c_str(); }
	const char *source() const { return m_type.source(); }
	device_t *owner() const { return m_owner; }
	device_t *next() const { return m_next; }
	u32 configured_clock() const { return m_configured_clock; }
	const machine_config &mconfig() const { return m_machine_config; }
	const input_device_default *input_ports_defaults() const { return m_input_defaults; }
	const std::vector<rom_entry> &rom_region_vector() const;
	const rom_entry *rom_region() const { return rom_region_vector().data(); }
	ioport_constructor input_ports() const { return device_input_ports(); }
	u8 default_bios() const { return m_default_bios; }
	u8 system_bios() const { return m_system_bios; }
	const std::string &default_bios_tag() const { return m_default_bios_tag; }

	// interface helpers
	interface_list &interfaces() { return m_interfaces; }
	const interface_list &interfaces() const { return m_interfaces; }
	template<class _DeviceClass> bool interface(_DeviceClass *&intf) { intf = dynamic_cast<_DeviceClass *>(this); return (intf != nullptr); }
	template<class _DeviceClass> bool interface(_DeviceClass *&intf) const { intf = dynamic_cast<const _DeviceClass *>(this); return (intf != nullptr); }

	// specialized helpers for common core interfaces
	bool interface(device_execute_interface *&intf) { intf = m_interfaces.m_execute; return (intf != nullptr); }
	bool interface(device_execute_interface *&intf) const { intf = m_interfaces.m_execute; return (intf != nullptr); }
	bool interface(device_memory_interface *&intf) { intf = m_interfaces.m_memory; return (intf != nullptr); }
	bool interface(device_memory_interface *&intf) const { intf = m_interfaces.m_memory; return (intf != nullptr); }
	bool interface(device_state_interface *&intf) { intf = m_interfaces.m_state; return (intf != nullptr); }
	bool interface(device_state_interface *&intf) const { intf = m_interfaces.m_state; return (intf != nullptr); }
	device_execute_interface &execute() const { assert(m_interfaces.m_execute != nullptr); return *m_interfaces.m_execute; }
	device_memory_interface &memory() const { assert(m_interfaces.m_memory != nullptr); return *m_interfaces.m_memory; }
	device_state_interface &state() const { assert(m_interfaces.m_state != nullptr); return *m_interfaces.m_state; }

	// owned object helpers
	subdevice_list &subdevices() { return m_subdevices; }
	const subdevice_list &subdevices() const { return m_subdevices; }

	// device-relative tag lookups
	std::string subtag(const char *tag) const;
	std::string siblingtag(const char *tag) const { return (m_owner != nullptr) ? m_owner->subtag(tag) : std::string(tag); }
>>>>>>> upstream/master
	memory_region *memregion(const char *tag) const;
	memory_share *memshare(const char *tag) const;
	memory_bank *membank(const char *tag) const;
	ioport_port *ioport(const char *tag) const;
	device_t *subdevice(const char *tag) const;
	device_t *siblingdevice(const char *tag) const;
	template<class _DeviceClass> inline _DeviceClass *subdevice(const char *tag) const { return downcast<_DeviceClass *>(subdevice(tag)); }
	template<class _DeviceClass> inline _DeviceClass *siblingdevice(const char *tag) const { return downcast<_DeviceClass *>(siblingdevice(tag)); }
<<<<<<< HEAD
	memory_region *region() const { return m_region; }

	// configuration helpers
	static void static_set_clock(device_t &device, UINT32 clock);
	static void static_set_static_config(device_t &device, const void *config) { device.m_static_config = config; }
	static void static_set_input_default(device_t &device, const input_device_default *config) { device.m_input_defaults = config; }
	static void static_set_default_bios_tag(device_t &device, const char *tag) { std::string default_bios_tag(tag); device.m_default_bios_tag = default_bios_tag; }
=======
	std::string parameter(const char *tag) const;

	// configuration helpers
	void add_machine_configuration(machine_config &config) { device_add_mconfig(config); }
	static void static_set_clock(device_t &device, u32 clock);
	static void static_set_input_default(device_t &device, const input_device_default *config) { device.m_input_defaults = config; }
	static void static_set_default_bios_tag(device_t &device, const char *tag) { device.m_default_bios_tag = tag; }
>>>>>>> upstream/master

	// state helpers
	void config_complete();
	bool configured() const { return m_config_complete; }
	void validity_check(validity_checker &valid) const;
	bool started() const { return m_started; }
	void reset();

	// clock/timing accessors
<<<<<<< HEAD
	UINT32 clock() const { return m_clock; }
	UINT32 unscaled_clock() const { return m_unscaled_clock; }
	void set_unscaled_clock(UINT32 clock);
	double clock_scale() const { return m_clock_scale; }
	void set_clock_scale(double clockscale);
	attotime clocks_to_attotime(UINT64 clocks) const;
	UINT64 attotime_to_clocks(const attotime &duration) const;

	// timer interfaces
	emu_timer *timer_alloc(device_timer_id id = 0, void *ptr = NULL);
	void timer_set(const attotime &duration, device_timer_id id = 0, int param = 0, void *ptr = NULL);
	void synchronize(device_timer_id id = 0, int param = 0, void *ptr = NULL) { timer_set(attotime::zero, id, param, ptr); }
=======
	u32 clock() const { return m_clock; }
	u32 unscaled_clock() const { return m_unscaled_clock; }
	void set_unscaled_clock(u32 clock);
	double clock_scale() const { return m_clock_scale; }
	void set_clock_scale(double clockscale);
	attotime clocks_to_attotime(u64 clocks) const;
	u64 attotime_to_clocks(const attotime &duration) const;

	// timer interfaces
	emu_timer *timer_alloc(device_timer_id id = 0, void *ptr = nullptr);
	void timer_set(const attotime &duration, device_timer_id id = 0, int param = 0, void *ptr = nullptr);
	void synchronize(device_timer_id id = 0, int param = 0, void *ptr = nullptr) { timer_set(attotime::zero, id, param, ptr); }
>>>>>>> upstream/master
	void timer_expired(emu_timer &timer, device_timer_id id, int param, void *ptr) { device_timer(timer, id, param, ptr); }

	// state saving interfaces
	template<typename _ItemType>
<<<<<<< HEAD
	void ATTR_COLD save_item(_ItemType &value, const char *valname, int index = 0) { assert(m_save != NULL); m_save->save_item(this, name(), tag(), index, value, valname); }
	template<typename _ItemType>
	void ATTR_COLD save_pointer(_ItemType *value, const char *valname, UINT32 count, int index = 0) { assert(m_save != NULL); m_save->save_pointer(this, name(), tag(), index, value, valname, count); }

	// debugging
	device_debug *debug() const { return m_debug; }
	offs_t safe_pc() const;
	offs_t safe_pcbase() const;

	void set_default_bios(UINT8 bios) { m_default_bios = bios; }
	void set_system_bios(UINT8 bios) { m_system_bios = bios; }
	bool findit(bool isvalidation = false) const;

	// misc
	void popmessage(const char *format, ...) const;
	void logerror(const char *format, ...) const;
	void vlogerror(const char *format, va_list args) const;
=======
	void ATTR_COLD save_item(_ItemType &value, const char *valname, int index = 0) { assert(m_save != nullptr); m_save->save_item(this, name(), tag(), index, value, valname); }
	template<typename _ItemType>
	void ATTR_COLD save_pointer(_ItemType *value, const char *valname, u32 count, int index = 0) { assert(m_save != nullptr); m_save->save_pointer(this, name(), tag(), index, value, valname, count); }

	// debugging
	device_debug *debug() const { return m_debug.get(); }
	offs_t safe_pc() const;
	offs_t safe_pcbase() const;

	void set_default_bios(u8 bios) { m_default_bios = bios; }
	void set_system_bios(u8 bios) { m_system_bios = bios; }
	bool findit(bool isvalidation = false) const;

	// misc
	template <typename Format, typename... Params> void popmessage(Format &&fmt, Params &&... args) const;
	template <typename Format, typename... Params> void logerror(Format &&fmt, Params &&... args) const;
>>>>>>> upstream/master

protected:
	// miscellaneous helpers
	void set_machine(running_machine &machine);
	void start();
	void stop();
	void debug_setup();
	void pre_save();
	void post_load();
	void notify_clock_changed();
	finder_base *register_auto_finder(finder_base &autodev);

	//------------------- begin derived class overrides

	// device-level overrides
<<<<<<< HEAD
	virtual const rom_entry *device_rom_region() const;
	virtual machine_config_constructor device_mconfig_additions() const;
=======
	virtual const tiny_rom_entry *device_rom_region() const;
	virtual void device_add_mconfig(machine_config &config);
>>>>>>> upstream/master
	virtual ioport_constructor device_input_ports() const;
	virtual void device_config_complete();
	virtual void device_validity_check(validity_checker &valid) const ATTR_COLD;
	virtual void device_start() ATTR_COLD = 0;
	virtual void device_stop() ATTR_COLD;
	virtual void device_reset() ATTR_COLD;
	virtual void device_reset_after_children() ATTR_COLD;
	virtual void device_pre_save() ATTR_COLD;
	virtual void device_post_load() ATTR_COLD;
	virtual void device_clock_changed();
	virtual void device_debug_setup();
	virtual void device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr);

	//------------------- end derived class overrides

	// core device properties
<<<<<<< HEAD
	const device_type       m_type;                 // device type
	std::string             m_name;                 // name of the device
	std::string             m_shortname;            // short name of the device
	std::string             m_searchpath;           // search path, used for media loading
	std::string             m_source;               // device source file name

	// device relationships
	device_t *              m_owner;                // device that owns us
	device_t *              m_next;                 // next device by the same owner (of any type/class)
	simple_list<device_t>   m_subdevice_list;       // list of sub-devices we own
	mutable tagmap_t<device_t *> m_device_map;      // map of device names looked up and found

	// device interfaces
	device_interface *      m_interface_list;       // head of interface list
	device_execute_interface *m_execute;            // pre-cached pointer to execute interface
	device_memory_interface *m_memory;              // pre-cached pointer to memory interface
	device_state_interface *m_state;                // pre-cached pointer to state interface

	// device clocks
	UINT32                  m_configured_clock;     // originally configured device clock
	UINT32                  m_unscaled_clock;       // current unscaled device clock
	UINT32                  m_clock;                // current device clock, after scaling
	double                  m_clock_scale;          // clock scale factor
	attoseconds_t           m_attoseconds_per_clock;// period in attoseconds

	auto_pointer<device_debug> m_debug;
	memory_region *         m_region;               // our device-local region
	const machine_config &  m_machine_config;       // reference to the machine's configuration
	const void *            m_static_config;        // static device configuration
	const input_device_default *m_input_defaults;   // devices input ports default overrides

	UINT8                   m_system_bios;          // the system BIOS we wish to load
	UINT8                   m_default_bios;         // the default system BIOS
	std::string             m_default_bios_tag;     // tag of the default system BIOS

private:
	// private helpers
	device_t *add_subdevice(device_type type, const char *tag, UINT32 clock);
	device_t *replace_subdevice(device_t &old, device_type type, const char *tag, UINT32 clock);
	void remove_subdevice(device_t &device);
	device_t *subdevice_slow(const char *tag) const;
=======
	device_type             m_type;                 // device type
	std::string             m_searchpath;           // search path, used for media loading

	// device relationships & interfaces
	device_t *              m_owner;                // device that owns us
	device_t *              m_next;                 // next device by the same owner (of any type/class)
	subdevice_list          m_subdevices;           // container for list of subdevices
	interface_list          m_interfaces;           // container for list of interfaces

	// device clocks
	u32                     m_configured_clock;     // originally configured device clock
	u32                     m_unscaled_clock;       // current unscaled device clock
	u32                     m_clock;                // current device clock, after scaling
	double                  m_clock_scale;          // clock scale factor
	attoseconds_t           m_attoseconds_per_clock;// period in attoseconds

	std::unique_ptr<device_debug> m_debug;
	const machine_config &  m_machine_config;       // reference to the machine's configuration
	const input_device_default *m_input_defaults;   // devices input ports default overrides

	u8                      m_system_bios;          // the system BIOS we wish to load
	u8                      m_default_bios;         // the default system BIOS
	std::string             m_default_bios_tag;     // tag of the default system BIOS

private:
	// internal helpers
	device_t *subdevice_slow(const char *tag) const;
	void calculate_derived_clock();
>>>>>>> upstream/master

	// private state; accessor use required
	running_machine *       m_machine;
	save_manager *          m_save;
	std::string             m_tag;                  // full tag for this instance
	std::string             m_basetag;              // base part of the tag
	bool                    m_config_complete;      // have we completed our configuration?
	bool                    m_started;              // true if the start function has succeeded
	finder_base *           m_auto_finder_list;     // list of objects to auto-find
<<<<<<< HEAD
=======
	mutable std::vector<rom_entry>  m_rom_entries;

	// string formatting buffer for logerror
	mutable util::ovectorstream m_string_buffer;
>>>>>>> upstream/master
};


// ======================> device_interface

// device_interface represents runtime information for a particular device interface
class device_interface
{
	DISABLE_COPYING(device_interface);

protected:
	// construction/destruction
	device_interface(device_t &device, const char *type);
	virtual ~device_interface();

public:
	const char *interface_type() const { return m_type; }

	// casting helpers
	device_t &device() { return m_device; }
	const device_t &device() const { return m_device; }
	operator device_t &() { return m_device; }
	operator device_t *() { return &m_device; }

	// iteration helpers
	device_interface *interface_next() const { return m_interface_next; }
<<<<<<< HEAD
	template<class _InterfaceClass> bool next(_InterfaceClass *&intf) const { return m_device.next(intf); }
=======
>>>>>>> upstream/master

	// optional operation overrides
	//
	// WARNING: interface_pre_start must be callable multiple times in
	// case another interface throws a missing dependency.  In
	// particular, state saving registrations should be done in post.
	virtual void interface_config_complete();
	virtual void interface_validity_check(validity_checker &valid) const;
	virtual void interface_pre_start();
	virtual void interface_post_start();
	virtual void interface_pre_reset();
	virtual void interface_post_reset();
	virtual void interface_pre_stop();
	virtual void interface_post_stop();
	virtual void interface_pre_save();
	virtual void interface_post_load();
	virtual void interface_clock_changed();
	virtual void interface_debug_setup();

protected:
	// internal state
	device_interface *      m_interface_next;
	device_t &              m_device;
	const char *            m_type;
};


// ======================> device_iterator

// helper class to iterate over the hierarchy of devices depth-first
class device_iterator
{
public:
<<<<<<< HEAD
	// construction
	device_iterator(device_t &root, int maxdepth = 255)
		: m_root(&root),
			m_current(NULL),
			m_curdepth(0),
			m_maxdepth(maxdepth) { }

	// getters
	device_t *current() const { return m_current; }

	// reset and return first item
	device_t *first()
	{
		m_current = m_root;
		return m_current;
	}

	// advance depth-first
	device_t *next()
	{
		// remember our starting position, and end immediately if we're NULL
		device_t *start = m_current;
		if (start == NULL)
			return NULL;

		// search down first
		if (m_curdepth < m_maxdepth)
		{
			m_current = start->first_subdevice();
			if (m_current != NULL)
			{
				m_curdepth++;
				return m_current;
			}
		}

		// search next for neighbors up the ownership chain
		while (m_curdepth > 0)
		{
			// found a neighbor? great!
			m_current = start->next();
			if (m_current != NULL)
				return m_current;

			// no? try our parent
			start = start->owner();
			m_curdepth--;
		}

		// returned to the top; we're done
		return m_current = NULL;
	}

	// return the number of items available
	int count()
	{
		int result = 0;
		for (device_t *item = first(); item != NULL; item = next())
			result++;
=======
	class auto_iterator
	{
	public:
		typedef std::ptrdiff_t difference_type;
		typedef device_t value_type;
		typedef device_t *pointer;
		typedef device_t &reference;
		typedef std::forward_iterator_tag iterator_category;

		// construction
		auto_iterator(device_t *devptr, int curdepth, int maxdepth)
			: m_curdevice(devptr)
			, m_curdepth(curdepth)
			, m_maxdepth(maxdepth)
		{
		}

		// getters
		device_t *current() const { return m_curdevice; }
		int depth() const { return m_curdepth; }

		// required operator overrides
		bool operator==(auto_iterator const &iter) const { return m_curdevice == iter.m_curdevice; }
		bool operator!=(auto_iterator const &iter) const { return m_curdevice != iter.m_curdevice; }
		device_t &operator*() const { assert(m_curdevice); return *m_curdevice; }
		device_t *operator->() const { return m_curdevice; }
		auto_iterator &operator++() { advance(); return *this; }
		auto_iterator operator++(int) { auto_iterator const result(*this); ++*this; return result; }

	protected:
		// search depth-first for the next device
		void advance()
		{
			// remember our starting position, and end immediately if we're nullptr
			if (m_curdevice)
			{
				device_t *start = m_curdevice;

				// search down first
				if (m_curdepth < m_maxdepth)
				{
					m_curdevice = start->subdevices().first();
					if (m_curdevice)
					{
						m_curdepth++;
						return;
					}
				}

				// search next for neighbors up the ownership chain
				while (m_curdepth > 0 && start)
				{
					// found a neighbor? great!
					m_curdevice = start->next();
					if (m_curdevice)
						return;

					// no? try our parent
					start = start->owner();
					m_curdepth--;
				}

				// returned to the top; we're done
				m_curdevice = nullptr;
			}
		}

		// protected state
		device_t *      m_curdevice;
		int             m_curdepth;
		const int       m_maxdepth;
	};

	// construction
	device_iterator(device_t &root, int maxdepth = 255)
		: m_root(root), m_maxdepth(maxdepth) { }

	// standard iterators
	auto_iterator begin() const { return auto_iterator(&m_root, 0, m_maxdepth); }
	auto_iterator end() const { return auto_iterator(nullptr, 0, m_maxdepth); }

	// return first item
	device_t *first() const { return begin().current(); }

	// return the number of items available
	int count() const
	{
		int result = 0;
		for (device_t &item : *this)
		{
			(void)&item;
			result++;
		}
>>>>>>> upstream/master
		return result;
	}

	// return the index of a given item in the virtual list
<<<<<<< HEAD
	int indexof(device_t &device)
	{
		int index = 0;
		for (device_t *item = first(); item != NULL; item = next(), index++)
			if (item == &device)
				return index;
=======
	int indexof(device_t &device) const
	{
		int index = 0;
		for (device_t &item : *this)
		{
			if (&item == &device)
				return index;
			else
				index++;
		}
>>>>>>> upstream/master
		return -1;
	}

	// return the indexed item in the list
<<<<<<< HEAD
	device_t *byindex(int index)
	{
		for (device_t *item = first(); item != NULL; item = next(), index--)
			if (index == 0)
				return item;
		return NULL;
=======
	device_t *byindex(int index) const
	{
		for (device_t &item : *this)
			if (index-- == 0)
				return &item;
		return nullptr;
>>>>>>> upstream/master
	}

private:
	// internal state
<<<<<<< HEAD
	device_t *      m_root;
	device_t *      m_current;
	int             m_curdepth;
=======
	device_t &      m_root;
>>>>>>> upstream/master
	int             m_maxdepth;
};


// ======================> device_type_iterator

// helper class to find devices of a given type in the device hierarchy
<<<<<<< HEAD
template<device_type _DeviceType, class _DeviceClass = device_t>
class device_type_iterator
{
public:
	// construction
	device_type_iterator(device_t &root, int maxdepth = 255)
		: m_iterator(root, maxdepth) { }

	// getters
	_DeviceClass *current() const { return downcast<_DeviceClass *>(m_iterator.current()); }

	// reset and return first item
	_DeviceClass *first()
	{
		for (device_t *device = m_iterator.first(); device != NULL; device = m_iterator.next())
			if (device->type() == _DeviceType)
				return downcast<_DeviceClass *>(device);
		return NULL;
	}

	// advance depth-first
	_DeviceClass *next()
	{
		for (device_t *device = m_iterator.next(); device != NULL; device = m_iterator.next())
			if (device->type() == _DeviceType)
				return downcast<_DeviceClass *>(device);
		return NULL;
	}

	// return the number of items available
	int count()
	{
		int result = 0;
		for (_DeviceClass *item = first(); item != NULL; item = next())
			result++;
		return result;
	}

	// return the index of a given item in the virtual list
	int indexof(_DeviceClass &device)
	{
		int index = 0;
		for (_DeviceClass *item = first(); item != NULL; item = next(), index++)
			if (item == &device)
				return index;
=======
template <class DeviceType, class DeviceClass = DeviceType>
class device_type_iterator
{
public:
	class auto_iterator : protected device_iterator::auto_iterator
	{
	public:
		using device_iterator::auto_iterator::difference_type;
		using device_iterator::auto_iterator::iterator_category;
		using device_iterator::auto_iterator::depth;

		typedef DeviceClass value_type;
		typedef DeviceClass *pointer;
		typedef DeviceClass &reference;

		// construction
		auto_iterator(device_t *devptr, int curdepth, int maxdepth)
			: device_iterator::auto_iterator(devptr, curdepth, maxdepth)
		{
			// make sure the first device is of the specified type
			while (m_curdevice && (m_curdevice->type().type() != typeid(DeviceType)))
				advance();
		}

		// required operator overrides
		bool operator==(auto_iterator const &iter) const { return m_curdevice == iter.m_curdevice; }
		bool operator!=(auto_iterator const &iter) const { return m_curdevice != iter.m_curdevice; }

		// getters returning specified device type
		DeviceClass *current() const { return downcast<DeviceClass *>(m_curdevice); }
		DeviceClass &operator*() const { assert(m_curdevice); return downcast<DeviceClass &>(*m_curdevice); }
		DeviceClass *operator->() const { return downcast<DeviceClass *>(m_curdevice); }

		// search for devices of the specified type
		auto_iterator &operator++()
		{
			advance();
			while (m_curdevice && (m_curdevice->type().type() != typeid(DeviceType)))
				advance();
			return *this;
		}

		auto_iterator operator++(int) { auto_iterator const result(*this); ++*this; return result; }
	};

	// construction
	device_type_iterator(device_t &root, int maxdepth = 255) : m_root(root), m_maxdepth(maxdepth) { }

	// standard iterators
	auto_iterator begin() const { return auto_iterator(&m_root, 0, m_maxdepth); }
	auto_iterator end() const { return auto_iterator(nullptr, 0, m_maxdepth); }
	auto_iterator cbegin() const { return auto_iterator(&m_root, 0, m_maxdepth); }
	auto_iterator cend() const { return auto_iterator(nullptr, 0, m_maxdepth); }

	// return first item
	DeviceClass *first() const { return begin().current(); }

	// return the number of items available
	int count() const { return std::distance(cbegin(), cend()); }

	// return the index of a given item in the virtual list
	int indexof(DeviceClass &device) const
	{
		int index = 0;
		for (DeviceClass &item : *this)
		{
			if (&item == &device)
				return index;
			else
				index++;
		}
>>>>>>> upstream/master
		return -1;
	}

	// return the indexed item in the list
<<<<<<< HEAD
	_DeviceClass *byindex(int index)
	{
		for (_DeviceClass *item = first(); item != NULL; item = next(), index--)
			if (index == 0)
				return item;
		return NULL;
=======
	DeviceClass *byindex(int index) const
	{
		for (DeviceClass &item : *this)
			if (index-- == 0)
				return &item;
		return nullptr;
>>>>>>> upstream/master
	}

private:
	// internal state
<<<<<<< HEAD
	device_iterator     m_iterator;
=======
	device_t &      m_root;
	int             m_maxdepth;
>>>>>>> upstream/master
};


// ======================> device_interface_iterator

// helper class to find devices with a given interface in the device hierarchy
<<<<<<< HEAD
// also works for findnig devices derived from a given subclass
=======
// also works for finding devices derived from a given subclass
>>>>>>> upstream/master
template<class _InterfaceClass>
class device_interface_iterator
{
public:
<<<<<<< HEAD
	// construction
	device_interface_iterator(device_t &root, int maxdepth = 255)
		: m_iterator(root, maxdepth),
			m_current(NULL) { }

	// getters
	_InterfaceClass *current() const { return m_current; }

	// reset and return first item
	_InterfaceClass *first()
	{
		for (device_t *device = m_iterator.first(); device != NULL; device = m_iterator.next())
			if (device->interface(m_current))
				return m_current;
		return NULL;
	}

	// advance depth-first
	_InterfaceClass *next()
	{
		for (device_t *device = m_iterator.next(); device != NULL; device = m_iterator.next())
			if (device->interface(m_current))
				return m_current;
		return NULL;
	}

	// return the number of items available
	int count()
	{
		int result = 0;
		for (_InterfaceClass *item = first(); item != NULL; item = next())
			result++;
=======
	class auto_iterator : public device_iterator::auto_iterator
	{
public:
		// construction
		auto_iterator(device_t *devptr, int curdepth, int maxdepth)
			: device_iterator::auto_iterator(devptr, curdepth, maxdepth)
		{
			// set the iterator for the first device with the interface
			find_interface();
		}

		// getters returning specified interface type
		_InterfaceClass *current() const { return m_interface; }
		_InterfaceClass &operator*() const { assert(m_interface != nullptr); return *m_interface; }

		// search for devices with the specified interface
		const auto_iterator &operator++() { advance(); find_interface(); return *this; }

private:
		// private helper
		void find_interface()
		{
			// advance until finding a device with the interface
			for ( ; m_curdevice != nullptr; advance())
				if (m_curdevice->interface(m_interface))
					return;

			// if we run out of devices, make sure the interface pointer is null
			m_interface = nullptr;
		}

		// private state
		_InterfaceClass *m_interface;
	};

public:
	// construction
	device_interface_iterator(device_t &root, int maxdepth = 255)
		: m_root(root), m_maxdepth(maxdepth) { }

	// standard iterators
	auto_iterator begin() const { return auto_iterator(&m_root, 0, m_maxdepth); }
	auto_iterator end() const { return auto_iterator(nullptr, 0, m_maxdepth); }

	// return first item
	_InterfaceClass *first() const { return begin().current(); }

	// return the number of items available
	int count() const
	{
		int result = 0;
		for (_InterfaceClass &item : *this)
		{
			(void)&item;
			result++;
		}
>>>>>>> upstream/master
		return result;
	}

	// return the index of a given item in the virtual list
<<<<<<< HEAD
	int indexof(_InterfaceClass &intrf)
	{
		int index = 0;
		for (_InterfaceClass *item = first(); item != NULL; item = next(), index++)
			if (item == &intrf)
				return index;
=======
	int indexof(_InterfaceClass &intrf) const
	{
		int index = 0;
		for (_InterfaceClass &item : *this)
		{
			if (&item == &intrf)
				return index;
			else
				index++;
		}
>>>>>>> upstream/master
		return -1;
	}

	// return the indexed item in the list
<<<<<<< HEAD
	_InterfaceClass *byindex(int index)
	{
		for (_InterfaceClass *item = first(); item != NULL; item = next(), index--)
			if (index == 0)
				return item;
		return NULL;
=======
	_InterfaceClass *byindex(int index) const
	{
		for (_InterfaceClass &item : *this)
			if (index-- == 0)
				return &item;
		return nullptr;
>>>>>>> upstream/master
	}

private:
	// internal state
<<<<<<< HEAD
	device_iterator     m_iterator;
	_InterfaceClass *   m_current;
=======
	device_t &      m_root;
	int             m_maxdepth;
>>>>>>> upstream/master
};



//**************************************************************************
//  INLINE FUNCTIONS
//**************************************************************************

//-------------------------------------------------
//  subdevice - given a tag, find the device by
//  name relative to this device
//-------------------------------------------------

inline device_t *device_t::subdevice(const char *tag) const
{
<<<<<<< HEAD
	// safety first
	if (this == NULL)
		return NULL;

	// empty string or NULL means this device
	if (tag == NULL || *tag == 0)
		return const_cast<device_t *>(this);

	// do a quick lookup and return that if possible
	device_t *quick = m_device_map.find(tag);
	return (quick != NULL) ? quick : subdevice_slow(tag);
=======
	// empty string or nullptr means this device
	if (tag == nullptr || *tag == 0)
		return const_cast<device_t *>(this);

	// do a quick lookup and return that if possible
	auto quick = m_subdevices.m_tagmap.find(tag);
	return (quick != m_subdevices.m_tagmap.end()) ? quick->second : subdevice_slow(tag);
>>>>>>> upstream/master
}


//-------------------------------------------------
//  siblingdevice - given a tag, find the device
//  by name relative to this device's parent
//-------------------------------------------------

inline device_t *device_t::siblingdevice(const char *tag) const
{
<<<<<<< HEAD
	// safety first
	if (this == NULL)
		return NULL;

	// empty string or NULL means this device
	if (tag == NULL || *tag == 0)
=======
	// empty string or nullptr means this device
	if (tag == nullptr || *tag == 0)
>>>>>>> upstream/master
		return const_cast<device_t *>(this);

	// leading caret implies the owner, just skip it
	if (tag[0] == '^') tag++;

	// query relative to the parent, if we have one
<<<<<<< HEAD
	if (m_owner != NULL)
		return m_owner->subdevice(tag);

	// otherwise, it's NULL unless the tag is absolute
	return (tag[0] == ':') ? subdevice(tag) : NULL;
}

#endif  /* __DEVICE_H__ */
=======
	if (m_owner != nullptr)
		return m_owner->subdevice(tag);

	// otherwise, it's nullptr unless the tag is absolute
	return (tag[0] == ':') ? subdevice(tag) : nullptr;
}


// these operators requires device_interface to be a complete type
inline device_t::interface_list::auto_iterator &device_t::interface_list::auto_iterator::operator++()
{
	m_current = m_current->interface_next();
	return *this;
}

inline device_t::interface_list::auto_iterator device_t::interface_list::auto_iterator::operator++(int)
{
	auto_iterator result(*this);
	m_current = m_current->interface_next();
	return result;
}


#endif  /* MAME_EMU_DEVICE_H */
>>>>>>> upstream/master
