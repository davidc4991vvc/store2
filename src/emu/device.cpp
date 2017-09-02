// license:BSD-3-Clause
// copyright-holders:Aaron Giles
/***************************************************************************

    device.c

    Device interface functions.

***************************************************************************/

#include "emu.h"
<<<<<<< HEAD
#include "string.h"
#include "ui/ui.h"
#include "debug/debugcpu.h"

=======
#include "speaker.h"
#include "debug/debugcpu.h"

#include <string.h>


//**************************************************************************
//  DEVICE TYPE REGISTRATION
//**************************************************************************

namespace emu { namespace detail {

namespace {

struct device_registrations
{
	device_type_impl *first = nullptr;
	device_type_impl *last = nullptr;
	device_type_impl *unsorted = nullptr;
};

device_registrations &device_registration_data()
{
	// this is necessary to avoid issues with static initialisation order across units being indeterminate
	// thread safety issues are avoided by always calling this function during static initialisation before the app can go threaded
	static device_registrations instance;
	return instance;
}

} // anonymous namespace


device_registrar::const_iterator device_registrar::cbegin() const
{
	return const_iterator_helper(device_registration_data().first);
}


device_registrar::const_iterator device_registrar::cend() const
{
	return const_iterator_helper(nullptr);
}


device_type_impl *device_registrar::register_device(device_type_impl &type)
{
	device_registrations &data(device_registration_data());

	if (!data.first) data.first = &type;
	if (data.last) data.last->m_next = &type;
	if (!data.unsorted) data.unsorted = &type;
	data.last = &type;

	return nullptr;
}

} } // namespace emu::detail

emu::detail::device_registrar const registered_device_types;


>>>>>>> upstream/master

//**************************************************************************
//  LIVE DEVICE MANAGEMENT
//**************************************************************************

//-------------------------------------------------
//  device_t - constructor for a new
//  running device; initial state is derived
//  from the provided config
//-------------------------------------------------

<<<<<<< HEAD
device_t::device_t(const machine_config &mconfig, device_type type, const char *name, const char *tag, device_t *owner, UINT32 clock, const char *shortname, const char *source)
	: m_type(type),
		m_name(name),
		m_shortname(shortname),
		m_searchpath(shortname),
		m_source(source),
		m_owner(owner),
		m_next(NULL),

		m_interface_list(NULL),
		m_execute(NULL),
		m_memory(NULL),
		m_state(NULL),

		m_configured_clock(clock),
		m_unscaled_clock(clock),
		m_clock(clock),
		m_clock_scale(1.0),
		m_attoseconds_per_clock((clock == 0) ? 0 : HZ_TO_ATTOSECONDS(clock)),

		m_region(NULL),
		m_machine_config(mconfig),
		m_static_config(NULL),
		m_input_defaults(NULL),
		m_default_bios_tag(""),

		m_machine(NULL),
		m_save(NULL),
		m_basetag(tag),
		m_config_complete(false),
		m_started(false),
		m_auto_finder_list(NULL)
{
	if (owner != NULL)
		m_tag.assign((owner->owner() == NULL) ? "" : owner->tag()).append(":").append(tag);
=======
device_t::device_t(const machine_config &mconfig, device_type type, const char *tag, device_t *owner, u32 clock)
	: m_type(type)
	, m_searchpath(type.shortname())
	, m_owner(owner)
	, m_next(nullptr)

	, m_configured_clock(clock)
	, m_unscaled_clock(clock)
	, m_clock(clock)
	, m_clock_scale(1.0)
	, m_attoseconds_per_clock((clock == 0) ? 0 : HZ_TO_ATTOSECONDS(clock))

	, m_machine_config(mconfig)
	, m_input_defaults(nullptr)
	, m_default_bios_tag("")

	, m_machine(nullptr)
	, m_save(nullptr)
	, m_basetag(tag)
	, m_config_complete(false)
	, m_started(false)
	, m_auto_finder_list(nullptr)
{
	if (owner != nullptr)
		m_tag.assign((owner->owner() == nullptr) ? "" : owner->tag()).append(":").append(tag);
>>>>>>> upstream/master
	else
		m_tag.assign(":");
	static_set_clock(*this, clock);
}


//-------------------------------------------------
//  ~device_t - destructor for a device_t
//-------------------------------------------------

device_t::~device_t()
{
}


//-------------------------------------------------
//  memregion - return a pointer to the region
//  info for a given region
//-------------------------------------------------

<<<<<<< HEAD
// NOTE: this being NULL in a C++ member function can lead to undefined behavior.
// However, it is relied on throughout MAME, so will remain for now.

memory_region *device_t::memregion(const char *_tag) const
{
	// safety first
	if (this == NULL)
		return NULL;

	// build a fully-qualified name and look it up
	return machine().memory().region(subtag(_tag).c_str());
=======
memory_region *device_t::memregion(const char *_tag) const
{
	// build a fully-qualified name and look it up
	if (_tag)
	{
		auto search = machine().memory().regions().find(subtag(_tag).c_str());
		if (search != machine().memory().regions().end())
			return search->second.get();
		else
			return nullptr;
	}
	else
		return nullptr;
>>>>>>> upstream/master
}


//-------------------------------------------------
//  memshare - return a pointer to the memory share
//  info for a given share
//-------------------------------------------------

memory_share *device_t::memshare(const char *_tag) const
{
<<<<<<< HEAD
	// safety first
	if (this == NULL)
		return NULL;

	// build a fully-qualified name and look it up
	return machine().memory().shared(subtag(_tag).c_str());
=======
	// build a fully-qualified name and look it up
	if (_tag)
	{
		auto search = machine().memory().shares().find(subtag(_tag).c_str());
		if (search != machine().memory().shares().end())
			return search->second.get();
		else
			return nullptr;
	}
	else
		return nullptr;
>>>>>>> upstream/master
}


//-------------------------------------------------
//  membank - return a pointer to the memory
//  bank info for a given bank
//-------------------------------------------------

memory_bank *device_t::membank(const char *_tag) const
{
<<<<<<< HEAD
	// safety first
	if (this == NULL)
		return NULL;

	// build a fully-qualified name and look it up
	return machine().memory().bank(subtag(_tag).c_str());
=======
	if (_tag)
	{
		auto search = machine().memory().banks().find(subtag(_tag).c_str());
		if (search != machine().memory().banks().end())
			return search->second.get();
		else
			return nullptr;
	}
	else
		return nullptr;
>>>>>>> upstream/master
}


//-------------------------------------------------
//  ioport - return a pointer to the I/O port
//  object for a given port name
//-------------------------------------------------

ioport_port *device_t::ioport(const char *tag) const
{
<<<<<<< HEAD
	// safety first
	if (this == NULL)
		return NULL;

=======
>>>>>>> upstream/master
	// build a fully-qualified name and look it up
	return machine().ioport().port(subtag(tag).c_str());
}


//-------------------------------------------------
//  ioport - return a pointer to the I/O port
//  object for a given port name
//-------------------------------------------------

std::string device_t::parameter(const char *tag) const
{
<<<<<<< HEAD
	// safety first
	if (this == NULL)
		return NULL;

=======
>>>>>>> upstream/master
	// build a fully-qualified name and look it up
	return machine().parameters().lookup(subtag(tag));
}


//-------------------------------------------------
//  static_set_clock - set/change the clock on
//  a device
//-------------------------------------------------

<<<<<<< HEAD
void device_t::static_set_clock(device_t &device, UINT32 clock)
{
	// derive the clock from our owner if requested
	if ((clock & 0xff000000) == 0xff000000)
	{
		assert(device.m_owner != NULL);
		clock = device.m_owner->m_configured_clock * ((clock >> 12) & 0xfff) / ((clock >> 0) & 0xfff);
	}

	device.m_clock = device.m_unscaled_clock = device.m_configured_clock = clock;
	device.m_attoseconds_per_clock = (clock == 0) ? 0 : HZ_TO_ATTOSECONDS(clock);
=======
void device_t::static_set_clock(device_t &device, u32 clock)
{
	device.m_configured_clock = clock;

	// derive the clock from our owner if requested
	if ((clock & 0xff000000) == 0xff000000)
		device.calculate_derived_clock();
	else
		device.set_unscaled_clock(clock);
>>>>>>> upstream/master
}


//-------------------------------------------------
//  config_complete - called when the
//  configuration of a device is complete
//-------------------------------------------------

void device_t::config_complete()
{
	// first notify the interfaces
<<<<<<< HEAD
	for (device_interface *intf = m_interface_list; intf != NULL; intf = intf->interface_next())
		intf->interface_config_complete();
=======
	for (device_interface &intf : interfaces())
		intf.interface_config_complete();
>>>>>>> upstream/master

	// then notify the device itself
	device_config_complete();

	// then mark ourselves complete
	m_config_complete = true;
}


//-------------------------------------------------
//  validity_check - validate a device after the
//  configuration has been constructed
//-------------------------------------------------

void device_t::validity_check(validity_checker &valid) const
{
	// validate via the interfaces
<<<<<<< HEAD
	for (device_interface *intf = m_interface_list; intf != NULL; intf = intf->interface_next())
		intf->interface_validity_check(valid);
=======
	for (device_interface &intf : interfaces())
		intf.interface_validity_check(valid);
>>>>>>> upstream/master

	// let the device itself validate
	device_validity_check(valid);
}


//-------------------------------------------------
//  reset - reset a device
//-------------------------------------------------

void device_t::reset()
{
	// let the interfaces do their pre-work
<<<<<<< HEAD
	for (device_interface *intf = m_interface_list; intf != NULL; intf = intf->interface_next())
		intf->interface_pre_reset();
=======
	for (device_interface &intf : interfaces())
		intf.interface_pre_reset();
>>>>>>> upstream/master

	// reset the device
	device_reset();

	// reset all child devices
<<<<<<< HEAD
	for (device_t *child = m_subdevice_list.first(); child != NULL; child = child->next())
		child->reset();
=======
	for (device_t &child : subdevices())
		child.reset();
>>>>>>> upstream/master

	// now allow for some post-child reset action
	device_reset_after_children();

	// let the interfaces do their post-work
<<<<<<< HEAD
	for (device_interface *intf = m_interface_list; intf != NULL; intf = intf->interface_next())
		intf->interface_post_reset();
=======
	for (device_interface &intf : interfaces())
		intf.interface_post_reset();
>>>>>>> upstream/master
}


//-------------------------------------------------
//  set_unscaled_clock - sets the given device's
//  unscaled clock
//-------------------------------------------------

<<<<<<< HEAD
void device_t::set_unscaled_clock(UINT32 clock)
{
	m_unscaled_clock = clock;
	m_clock = m_unscaled_clock * m_clock_scale;
	m_attoseconds_per_clock = (m_clock == 0) ? 0 : HZ_TO_ATTOSECONDS(m_clock);
	notify_clock_changed();
=======
void device_t::set_unscaled_clock(u32 clock)
{
	// do nothing if no actual change
	if (clock == m_unscaled_clock)
		return;

	m_unscaled_clock = clock;
	m_clock = m_unscaled_clock * m_clock_scale;
	m_attoseconds_per_clock = (m_clock == 0) ? 0 : HZ_TO_ATTOSECONDS(m_clock);

	// recalculate all derived clocks
	for (device_t &child : subdevices())
		child.calculate_derived_clock();

	// if the device has already started, make sure it knows about the new clock
	if (m_started)
		notify_clock_changed();
>>>>>>> upstream/master
}


//-------------------------------------------------
//  set_clock_scale - sets a scale factor for the
//  device's clock
//-------------------------------------------------

void device_t::set_clock_scale(double clockscale)
{
<<<<<<< HEAD
	m_clock_scale = clockscale;
	m_clock = m_unscaled_clock * m_clock_scale;
	m_attoseconds_per_clock = (m_clock == 0) ? 0 : HZ_TO_ATTOSECONDS(m_clock);
	notify_clock_changed();
=======
	// do nothing if no actual change
	if (clockscale == m_clock_scale)
		return;

	m_clock_scale = clockscale;
	m_clock = m_unscaled_clock * m_clock_scale;
	m_attoseconds_per_clock = (m_clock == 0) ? 0 : HZ_TO_ATTOSECONDS(m_clock);

	// recalculate all derived clocks
	for (device_t &child : subdevices())
		child.calculate_derived_clock();

	// if the device has already started, make sure it knows about the new clock
	if (m_started)
		notify_clock_changed();
}


//-------------------------------------------------
//  calculate_derived_clock - derive the device's
//  clock from its owner, if so configured
//-------------------------------------------------

void device_t::calculate_derived_clock()
{
	if ((m_configured_clock & 0xff000000) == 0xff000000)
	{
		assert(m_owner != nullptr);
		set_unscaled_clock(m_owner->m_clock * ((m_configured_clock >> 12) & 0xfff) / ((m_configured_clock >> 0) & 0xfff));
	}
>>>>>>> upstream/master
}


//-------------------------------------------------
//  clocks_to_attotime - converts a number of
//  clock ticks to an attotime
//-------------------------------------------------

<<<<<<< HEAD
attotime device_t::clocks_to_attotime(UINT64 numclocks) const
{
	if (numclocks < m_clock)
		return attotime(0, numclocks * m_attoseconds_per_clock);
	else
	{
		UINT32 remainder;
		UINT32 quotient = divu_64x32_rem(numclocks, m_clock, &remainder);
		return attotime(quotient, (UINT64)remainder * (UINT64)m_attoseconds_per_clock);
=======
attotime device_t::clocks_to_attotime(u64 numclocks) const
{
	if (m_clock == 0)
		return attotime::never;
	else if (numclocks < m_clock)
		return attotime(0, numclocks * m_attoseconds_per_clock);
	else
	{
		u32 remainder;
		u32 quotient = divu_64x32_rem(numclocks, m_clock, &remainder);
		return attotime(quotient, u64(remainder) * u64(m_attoseconds_per_clock));
>>>>>>> upstream/master
	}
}


//-------------------------------------------------
//  attotime_to_clocks - converts a duration as
//  attotime to CPU clock ticks
//-------------------------------------------------

<<<<<<< HEAD
UINT64 device_t::attotime_to_clocks(const attotime &duration) const
{
	return mulu_32x32(duration.seconds(), m_clock) + (UINT64)duration.attoseconds() / (UINT64)m_attoseconds_per_clock;
=======
u64 device_t::attotime_to_clocks(const attotime &duration) const
{
	if (m_clock == 0)
		return 0;
	else
		return mulu_32x32(duration.seconds(), m_clock) + u64(duration.attoseconds()) / u64(m_attoseconds_per_clock);
>>>>>>> upstream/master
}


//-------------------------------------------------
//  timer_alloc - allocate a timer for our device
//  callback
//-------------------------------------------------

emu_timer *device_t::timer_alloc(device_timer_id id, void *ptr)
{
	return machine().scheduler().timer_alloc(*this, id, ptr);
}


//-------------------------------------------------
//  timer_set - set a temporary timer that will
//  call our device callback
//-------------------------------------------------

void device_t::timer_set(const attotime &duration, device_timer_id id, int param, void *ptr)
{
	machine().scheduler().timer_set(duration, *this, id, param, ptr);
}


//-------------------------------------------------
//  set_machine - notify that the machine now
//  exists
//-------------------------------------------------

void device_t::set_machine(running_machine &machine)
{
	m_machine = &machine;
	m_save = &machine.save();
}

//-------------------------------------------------
<<<<<<< HEAD
//  findit - seach for all objects in auto finder
=======
//  findit - search for all objects in auto finder
>>>>>>> upstream/master
//  list and return status
//-------------------------------------------------

bool device_t::findit(bool isvalidation) const
{
	bool allfound = true;
<<<<<<< HEAD
	for (finder_base *autodev = m_auto_finder_list; autodev != NULL; autodev = autodev->m_next)
		allfound &= autodev->findit(isvalidation);
=======
	for (finder_base *autodev = m_auto_finder_list; autodev != nullptr; autodev = autodev->next())
	{
		if (isvalidation)
		{
			// sanity checking
			const char *tag = autodev->finder_tag();
			if (tag == nullptr)
			{
				osd_printf_error("Finder tag is null!\n");
				allfound = false;
				continue;
			}
			if (tag[0] == '^' && tag[1] == ':')
			{
				osd_printf_error("Malformed finder tag: %s\n", tag);
				allfound = false;
				continue;
			}
		}
		allfound &= autodev->findit(isvalidation);
	}
>>>>>>> upstream/master
	return allfound;
}

//-------------------------------------------------
//  start - start a device
//-------------------------------------------------

void device_t::start()
{
<<<<<<< HEAD
	// populate the machine and the region field
	m_region = machine().root_device().memregion(tag());
=======
	// prepare the logerror buffer
	if (m_machine->allow_logging())
		m_string_buffer.reserve(1024);
>>>>>>> upstream/master

	// find all the registered devices
	if (!findit(false))
		throw emu_fatalerror("Missing some required objects, unable to proceed");

	// let the interfaces do their pre-work
<<<<<<< HEAD
	for (device_interface *intf = m_interface_list; intf != NULL; intf = intf->interface_next())
		intf->interface_pre_start();
=======
	for (device_interface &intf : interfaces())
		intf.interface_pre_start();
>>>>>>> upstream/master

	// remember the number of state registrations
	int state_registrations = machine().save().registration_count();

	// start the device
	device_start();

	// complain if nothing was registered by the device
	state_registrations = machine().save().registration_count() - state_registrations;
	device_execute_interface *exec;
	device_sound_interface *sound;
	if (state_registrations == 0 && (interface(exec) || interface(sound)) && type() != SPEAKER)
	{
<<<<<<< HEAD
		logerror("Device '%s' did not register any state to save!\n", tag());
=======
		logerror("Device did not register any state to save!\n");
>>>>>>> upstream/master
		if ((machine().system().flags & MACHINE_SUPPORTS_SAVE) != 0)
			fatalerror("Device '%s' did not register any state to save!\n", tag());
	}

	// let the interfaces do their post-work
<<<<<<< HEAD
	for (device_interface *intf = m_interface_list; intf != NULL; intf = intf->interface_next())
		intf->interface_post_start();
=======
	for (device_interface &intf : interfaces())
		intf.interface_post_start();
>>>>>>> upstream/master

	// force an update of the clock
	notify_clock_changed();

	// if we're debugging, create a device_debug object
	if ((machine().debug_flags & DEBUG_FLAG_ENABLED) != 0)
	{
<<<<<<< HEAD
		m_debug.reset(global_alloc(device_debug(*this)));
=======
		m_debug = std::make_unique<device_debug>(*this);
>>>>>>> upstream/master
		debug_setup();
	}

	// register our save states
	save_item(NAME(m_clock));
	save_item(NAME(m_unscaled_clock));
	save_item(NAME(m_clock_scale));

	// we're now officially started
	m_started = true;
}


//-------------------------------------------------
//  stop - stop a device
//-------------------------------------------------

void device_t::stop()
{
	// let the interfaces do their pre-work
<<<<<<< HEAD
	for (device_interface *intf = m_interface_list; intf != NULL; intf = intf->interface_next())
		intf->interface_pre_stop();
=======
	for (device_interface &intf : interfaces())
		intf.interface_pre_stop();
>>>>>>> upstream/master

	// stop the device
	device_stop();

	// let the interfaces do their post-work
<<<<<<< HEAD
	for (device_interface *intf = m_interface_list; intf != NULL; intf = intf->interface_next())
		intf->interface_post_stop();
=======
	for (device_interface &intf : interfaces())
		intf.interface_post_stop();
>>>>>>> upstream/master

	// free any debugging info
	m_debug.reset();

	// we're now officially stopped, and the machine is off-limits
	m_started = false;
<<<<<<< HEAD
	m_machine = NULL;
=======
	m_machine = nullptr;
>>>>>>> upstream/master
}


//-------------------------------------------------
//  debug_setup - set up for debugging
//-------------------------------------------------

void device_t::debug_setup()
{
	// notify the interface
<<<<<<< HEAD
	for (device_interface *intf = m_interface_list; intf != NULL; intf = intf->interface_next())
		intf->interface_debug_setup();
=======
	for (device_interface &intf : interfaces())
		intf.interface_debug_setup();
>>>>>>> upstream/master

	// notify the device
	device_debug_setup();
}


//-------------------------------------------------
//  pre_save - tell the device and its interfaces
//  that we are about to save
//-------------------------------------------------

void device_t::pre_save()
{
	// notify the interface
<<<<<<< HEAD
	for (device_interface *intf = m_interface_list; intf != NULL; intf = intf->interface_next())
		intf->interface_pre_save();
=======
	for (device_interface &intf : interfaces())
		intf.interface_pre_save();
>>>>>>> upstream/master

	// notify the device
	device_pre_save();
}


//-------------------------------------------------
//  post_load - tell the device and its interfaces
//  that we just completed a load
//-------------------------------------------------

void device_t::post_load()
{
	// notify the interface
<<<<<<< HEAD
	for (device_interface *intf = m_interface_list; intf != NULL; intf = intf->interface_next())
		intf->interface_post_load();
=======
	for (device_interface &intf : interfaces())
		intf.interface_post_load();
>>>>>>> upstream/master

	// notify the device
	device_post_load();
}


//-------------------------------------------------
//  notify_clock_changed - notify all interfaces
//  that the clock has changed
//-------------------------------------------------

void device_t::notify_clock_changed()
{
	// first notify interfaces
<<<<<<< HEAD
	for (device_interface *intf = m_interface_list; intf != NULL; intf = intf->interface_next())
		intf->interface_clock_changed();
=======
	for (device_interface &intf : interfaces())
		intf.interface_clock_changed();
>>>>>>> upstream/master

	// then notify the device
	device_clock_changed();
}


//-------------------------------------------------
//  device_config_complete - perform any
//  operations now that the configuration is
//  complete
//-------------------------------------------------

void device_t::device_config_complete()
{
	// do nothing by default
}


//-------------------------------------------------
//  device_validity_check - validate a device after
//  the configuration has been constructed
//-------------------------------------------------

void device_t::device_validity_check(validity_checker &valid) const
{
	// do nothing by default
}


//-------------------------------------------------
//  rom_region - return a pointer to the implicit
//  rom region description for this device
//-------------------------------------------------

<<<<<<< HEAD
const rom_entry *device_t::device_rom_region() const
{
	// none by default
	return NULL;
=======
const tiny_rom_entry *device_t::device_rom_region() const
{
	// none by default
	return nullptr;
>>>>>>> upstream/master
}


//-------------------------------------------------
<<<<<<< HEAD
//  machine_config - return a pointer to a machine
//  config constructor describing sub-devices for
//  this device
//-------------------------------------------------

machine_config_constructor device_t::device_mconfig_additions() const
{
	// none by default
	return NULL;
=======
//  device_add_mconfig - add device-specific
//  machine configuration
//-------------------------------------------------

void device_t::device_add_mconfig(machine_config &config)
{
	// do nothing by default
>>>>>>> upstream/master
}


//-------------------------------------------------
//  input_ports - return a pointer to the implicit
//  input ports description for this device
//-------------------------------------------------

ioport_constructor device_t::device_input_ports() const
{
	// none by default
<<<<<<< HEAD
	return NULL;
=======
	return nullptr;
>>>>>>> upstream/master
}


//-------------------------------------------------
//  device_reset - actually handle resetting of
<<<<<<< HEAD
//  a device; designed to be overriden by the
=======
//  a device; designed to be overridden by the
>>>>>>> upstream/master
//  actual device implementation
//-------------------------------------------------

void device_t::device_reset()
{
	// do nothing by default
}


//-------------------------------------------------
//  device_reset_after_children - hook to do
//  reset logic that must happen after the children
<<<<<<< HEAD
//  are reset; designed to be overriden by the
=======
//  are reset; designed to be overridden by the
>>>>>>> upstream/master
//  actual device implementation
//-------------------------------------------------

void device_t::device_reset_after_children()
{
	// do nothing by default
}


//-------------------------------------------------
//  device_stop - clean up anything that needs to
//  happen before the running_machine goes away
//-------------------------------------------------

void device_t::device_stop()
{
	// do nothing by default
}


//-------------------------------------------------
//  device_pre_save - called prior to saving the
//  state, so that registered variables can be
//  properly normalized
//-------------------------------------------------

void device_t::device_pre_save()
{
	// do nothing by default
}


//-------------------------------------------------
//  device_post_load - called after the loading a
//  saved state, so that registered variables can
//  be expanded as necessary
//-------------------------------------------------

void device_t::device_post_load()
{
	// do nothing by default
}


//-------------------------------------------------
//  device_clock_changed - called when the
//  device clock is altered in any way; designed
//  to be overridden by the actual device
//  implementation
//-------------------------------------------------

void device_t::device_clock_changed()
{
	// do nothing by default
}


//-------------------------------------------------
//  device_debug_setup - called when the debugger
//  is active to allow for device-specific setup
//-------------------------------------------------

void device_t::device_debug_setup()
{
	// do nothing by default
}


//-------------------------------------------------
//  device_timer - called whenever a device timer
//  fires
//-------------------------------------------------

void device_t::device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr)
{
	// do nothing by default
}


//-------------------------------------------------
//  subdevice_slow - perform a slow name lookup,
//  caching the results
//-------------------------------------------------

device_t *device_t::subdevice_slow(const char *tag) const
{
	// resolve the full path
	std::string fulltag = subtag(tag);

	// we presume the result is a rooted path; also doubled colons mess up our
	// tree walk, so catch them early
	assert(fulltag[0] == ':');
	assert(fulltag.find("::") == -1);

	// walk the device list to the final path
	device_t *curdevice = &mconfig().root_device();
	if (fulltag.length() > 1)
<<<<<<< HEAD
		for (int start = 1, end = fulltag.find_first_of(':', start); start != 0 && curdevice != NULL; start = end + 1, end = fulltag.find_first_of(':', start))
		{
			std::string part(fulltag, start, (end == -1) ? -1 : end - start);
			for (curdevice = curdevice->m_subdevice_list.first(); curdevice != NULL; curdevice = curdevice->next())
				if (part.compare(curdevice->m_basetag)==0)
					break;
		}

	// if we got a match, add to the fast map
	if (curdevice != NULL)
		m_device_map.add(tag, curdevice);
=======
		for (int start = 1, end = fulltag.find_first_of(':', start); start != 0 && curdevice != nullptr; start = end + 1, end = fulltag.find_first_of(':', start))
		{
			std::string part(fulltag, start, (end == -1) ? -1 : end - start);
			curdevice = curdevice->subdevices().find(part);
		}

	// if we got a match, add to the fast map
	if (curdevice != nullptr)
		m_subdevices.m_tagmap.insert(std::make_pair(tag, curdevice));
>>>>>>> upstream/master
	return curdevice;
}


//-------------------------------------------------
//  subtag - create a fully resolved path relative
//  to our device based on the provided tag
//-------------------------------------------------

std::string device_t::subtag(const char *tag) const
{
	std::string result;
	// if the tag begins with a colon, ignore our path and start from the root
	if (*tag == ':')
	{
		tag++;
		result.assign(":");
	}

	// otherwise, start with our path
	else
	{
		result.assign(m_tag);
		if (result != ":")
			result.append(":");
	}

	// iterate over the tag, look for special path characters to resolve
	const char *caret;
<<<<<<< HEAD
	while ((caret = strchr(tag, '^')) != NULL)
=======
	while ((caret = strchr(tag, '^')) != nullptr)
>>>>>>> upstream/master
	{
		// copy everything up to there
		result.append(tag, caret - tag);
		tag = caret + 1;

		// strip trailing colons
		int len = result.length();
		while (result[--len] == ':')
			result = result.substr(0, len);

		// remove the last path part, leaving the last colon
		if (result != ":")
		{
			int lastcolon = result.find_last_of(':');
			if (lastcolon != -1)
				result = result.substr(0, lastcolon + 1);
		}
	}

	// copy everything else
	result.append(tag);

	// strip trailing colons up to the root
	int len = result.length();
	while (len > 1 && result[--len] == ':')
		result = result.substr(0, len);
	return result;
}


//-------------------------------------------------
<<<<<<< HEAD
//  add_subdevice - create a new device and add it
//  as a subdevice
//-------------------------------------------------

device_t *device_t::add_subdevice(device_type type, const char *tag, UINT32 clock)
{
	// allocate the device and append to our list
	device_t *device = (*type)(mconfig(), tag, this, clock);
	m_subdevice_list.append(*device);

	// apply any machine configuration owned by the device now
	machine_config_constructor additions = device->machine_config_additions();
	if (additions != NULL)
		(*additions)(const_cast<machine_config &>(mconfig()), device, NULL);
	return device;
}


//-------------------------------------------------
//  add_subdevice - create a new device and use it
//  to replace an existing subdevice
//-------------------------------------------------

device_t *device_t::replace_subdevice(device_t &old, device_type type, const char *tag, UINT32 clock)
{
	// iterate over all devices and remove any references to the old device
	device_iterator iter(mconfig().root_device());
	for (device_t *scan = iter.first(); scan != NULL; scan = iter.next())
		scan->m_device_map.reset(); //remove(&old);

	// create a new device, and substitute it for the old one
	device_t *device = (*type)(mconfig(), tag, this, clock);
	m_subdevice_list.replace_and_remove(*device, old);

	// apply any machine configuration owned by the device now
	machine_config_constructor additions = device->machine_config_additions();
	if (additions != NULL)
		(*additions)(const_cast<machine_config &>(mconfig()), device, NULL);
	return device;
}


//-------------------------------------------------
//  remove_subdevice - remove a given subdevice
//-------------------------------------------------

void device_t::remove_subdevice(device_t &device)
{
	// iterate over all devices and remove any references
	device_iterator iter(mconfig().root_device());
	for (device_t *scan = iter.first(); scan != NULL; scan = iter.next())
		scan->m_device_map.reset(); //remove(&device);

	// remove from our list
	m_subdevice_list.remove(device);
}


//-------------------------------------------------
=======
>>>>>>> upstream/master
//  register_auto_finder - add a new item to the
//  list of stuff to find after we go live
//-------------------------------------------------

finder_base *device_t::register_auto_finder(finder_base &autodev)
{
	// add to this list
	finder_base *old = m_auto_finder_list;
	m_auto_finder_list = &autodev;
	return old;
}

<<<<<<< HEAD
void device_t::popmessage(const char *format, ...) const
{
	// if the format is NULL, it is a signal to clear the popmessage
	if (format == NULL)
		machine().ui().popup_time(0, " ");

	// otherwise, generate the buffer and call the UI to display the message
	else
	{
		std::string temp;
		va_list arg;

		// dump to the buffer
		va_start(arg, format);
		strvprintf(temp, format, arg);
		va_end(arg);

		// pop it in the UI
		if (m_machine!=NULL) machine().ui().popup_time(temp.length() / 40 + 2, "%s", temp.c_str());
	}
}

void device_t::logerror(const char *format, ...) const
{
	va_list arg;
	va_start(arg, format);
	vlogerror(format, arg);
	va_end(arg);
}
void device_t::vlogerror(const char *format, va_list args) const
{
	std::string fmt("[");
	fmt += tag() + std::string("] ") + format;
	if (m_machine!=NULL) machine().vlogerror(fmt.c_str(), args);
}

=======
>>>>>>> upstream/master
//**************************************************************************
//  LIVE DEVICE INTERFACES
//**************************************************************************

//-------------------------------------------------
//  device_interface - constructor
//-------------------------------------------------

device_interface::device_interface(device_t &device, const char *type)
<<<<<<< HEAD
	: m_interface_next(NULL),
=======
	: m_interface_next(nullptr),
>>>>>>> upstream/master
		m_device(device),
		m_type(type)
{
	device_interface **tailptr;
<<<<<<< HEAD
	for (tailptr = &device.m_interface_list; *tailptr != NULL; tailptr = &(*tailptr)->m_interface_next) { }
=======
	for (tailptr = &device.interfaces().m_head; *tailptr != nullptr; tailptr = &(*tailptr)->m_interface_next) { }
>>>>>>> upstream/master
	*tailptr = this;
}


//-------------------------------------------------
//  ~device_interface - destructor
//-------------------------------------------------

device_interface::~device_interface()
{
}


//-------------------------------------------------
//  interface_config_complete - perform any
//  operations now that the configuration is
//  complete
//-------------------------------------------------

void device_interface::interface_config_complete()
{
	// do nothing by default
}


//-------------------------------------------------
//  interface_validity_check - default validation
//  for a device after the configuration has been
//  constructed
//-------------------------------------------------

void device_interface::interface_validity_check(validity_checker &valid) const
{
}


//-------------------------------------------------
//  interface_pre_start - called before the
//  device's own start function
//-------------------------------------------------

void device_interface::interface_pre_start()
{
	// do nothing by default
}


//-------------------------------------------------
//  interface_post_start - called after the
//  device's own start function
//-------------------------------------------------

void device_interface::interface_post_start()
{
	// do nothing by default
}


//-------------------------------------------------
//  interface_pre_reset - called before the
//  device's own reset function
//-------------------------------------------------

void device_interface::interface_pre_reset()
{
	// do nothing by default
}


//-------------------------------------------------
//  interface_post_reset - called after the
//  device's own reset function
//-------------------------------------------------

void device_interface::interface_post_reset()
{
	// do nothing by default
}


//-------------------------------------------------
//  interface_pre_stop - called before the
//  device's own stop function
//-------------------------------------------------

void device_interface::interface_pre_stop()
{
	// do nothing by default
}


//-------------------------------------------------
//  interface_post_stop - called after the
//  device's own stop function
//-------------------------------------------------

void device_interface::interface_post_stop()
{
	// do nothing by default
}


//-------------------------------------------------
//  interface_pre_save - called prior to saving the
//  state, so that registered variables can be
//  properly normalized
//-------------------------------------------------

void device_interface::interface_pre_save()
{
	// do nothing by default
}


//-------------------------------------------------
//  interface_post_load - called after the loading a
//  saved state, so that registered variables can
//  be expaneded as necessary
//-------------------------------------------------

void device_interface::interface_post_load()
{
	// do nothing by default
}


//-------------------------------------------------
//  interface_clock_changed - called when the
//  device clock is altered in any way; designed
//  to be overridden by the actual device
//  implementation
//-------------------------------------------------

void device_interface::interface_clock_changed()
{
	// do nothing by default
}


//-------------------------------------------------
//  interface_debug_setup - called to allow
//  interfaces to set up any debugging for this
//  device
//-------------------------------------------------

void device_interface::interface_debug_setup()
{
	// do nothing by default
}
<<<<<<< HEAD
=======


//-------------------------------------------------
// rom_region_vector
//-------------------------------------------------

const std::vector<rom_entry> &device_t::rom_region_vector() const
{
	if (m_rom_entries.empty())
	{
		m_rom_entries = rom_build_entries(device_rom_region());
	}
	return m_rom_entries;
}
>>>>>>> upstream/master
