// license:BSD-3-Clause
// copyright-holders:Juergen Buchmueller
/***************************************************************************

    z80daisy.c

    Z80/180 daisy chaining support functions.

***************************************************************************/

#include "emu.h"
#include "z80daisy.h"

<<<<<<< HEAD
=======
#define VERBOSE 0

>>>>>>> upstream/master

//**************************************************************************
//  DEVICE Z80 DAISY INTERFACE
//**************************************************************************

//-------------------------------------------------
//  device_z80daisy_interface - constructor
//-------------------------------------------------

device_z80daisy_interface::device_z80daisy_interface(const machine_config &mconfig, device_t &device)
<<<<<<< HEAD
	: device_interface(device, "z80daisy")
=======
	: device_interface(device, "z80daisy"),
		m_daisy_next(nullptr)
>>>>>>> upstream/master
{
}


//-------------------------------------------------
//  ~device_z80daisy_interface - destructor
//-------------------------------------------------

device_z80daisy_interface::~device_z80daisy_interface()
{
}



//**************************************************************************
//  Z80 DAISY CHAIN
//**************************************************************************

//-------------------------------------------------
<<<<<<< HEAD
//  z80_daisy_chain - constructor
//-------------------------------------------------

z80_daisy_chain::z80_daisy_chain()
	: m_daisy_list(NULL)
{
=======
//  z80_daisy_chain_interface - constructor
//-------------------------------------------------

z80_daisy_chain_interface::z80_daisy_chain_interface(const machine_config &mconfig, device_t &device)
	: device_interface(device, "z80daisychain"),
		m_daisy_config(nullptr),
		m_chain(nullptr)
{
}


//-------------------------------------------------
//  z80_daisy_chain_interface - destructor
//-------------------------------------------------
z80_daisy_chain_interface::~z80_daisy_chain_interface()
{
}


//-------------------------------------------------
//  static_set_daisy_config - configuration helper
//  to set up the daisy chain
//-------------------------------------------------
void z80_daisy_chain_interface::static_set_daisy_config(device_t &device, const z80_daisy_config *config)
{
	z80_daisy_chain_interface *daisyintf;
	if (!device.interface(daisyintf))
		throw emu_fatalerror("MCFG_Z80_DAISY_CHAIN called on device '%s' with no daisy chain interface", device.tag());
	daisyintf->m_daisy_config = config;
>>>>>>> upstream/master
}


//-------------------------------------------------
<<<<<<< HEAD
//  init - allocate the daisy chain based on the
//  provided configuration
//-------------------------------------------------

void z80_daisy_chain::init(device_t *cpudevice, const z80_daisy_config *daisy)
{
	// create a linked list of devices
	daisy_entry **tailptr = &m_daisy_list;
	for ( ; daisy->devname != NULL; daisy++)
	{
		// find the device
		device_t *target;
		if ((target = cpudevice->subdevice(daisy->devname)) == NULL)
		{
			if ((target = cpudevice->siblingdevice(daisy->devname)) == NULL)
=======
//  interface_post_start - work to be done after
//  actually starting a device
//-------------------------------------------------

void z80_daisy_chain_interface::interface_post_start()
{
	if (m_daisy_config != nullptr)
		daisy_init(m_daisy_config);
}

void z80_daisy_chain_interface::daisy_init(const z80_daisy_config *daisy)
{
	assert(daisy != nullptr);

	// create a linked list of devices
	device_z80daisy_interface **tailptr = &m_chain;
	for ( ; daisy->devname != nullptr; daisy++)
	{
		// find the device
		device_t *target = device().subdevice(daisy->devname);
		if (target == nullptr)
		{
			target = device().siblingdevice(daisy->devname);
			if (target == nullptr)
>>>>>>> upstream/master
				fatalerror("Unable to locate device '%s'\n", daisy->devname);
		}

		// make sure it has an interface
		device_z80daisy_interface *intf;
		if (!target->interface(intf))
			fatalerror("Device '%s' does not implement the z80daisy interface!\n", daisy->devname);

<<<<<<< HEAD
		// append to the end, or overwrite existing entry
		daisy_entry *next = (*tailptr) ? (*tailptr)->m_next : NULL;
		if (*tailptr != NULL)
			auto_free(cpudevice->machine(), *tailptr);
		*tailptr = auto_alloc(cpudevice->machine(), daisy_entry(target));
		(*tailptr)->m_next = next;
		tailptr = &(*tailptr)->m_next;
	}
=======
		// splice it out of the list if it was previously added
		device_z80daisy_interface **oldtailptr = tailptr;
		while (*oldtailptr != nullptr)
		{
			if (*oldtailptr == intf)
				*oldtailptr = (*oldtailptr)->m_daisy_next;
			else
				oldtailptr = &(*oldtailptr)->m_daisy_next;
		}

		// add the interface to the list
		intf->m_daisy_next = *tailptr;
		*tailptr = intf;
		tailptr = &(*tailptr)->m_daisy_next;
	}

	osd_printf_verbose("Daisy chain = %s\n", daisy_show_chain().c_str());
>>>>>>> upstream/master
}


//-------------------------------------------------
<<<<<<< HEAD
//  reset - send a reset signal to all chained
//  devices
//-------------------------------------------------

void z80_daisy_chain::reset()
{
	// loop over all devices and call their reset function
	for (daisy_entry *daisy = m_daisy_list; daisy != NULL; daisy = daisy->m_next)
		daisy->m_device->reset();
=======
//  interface_post_reset - work to be done after a
//  device is reset
//-------------------------------------------------

void z80_daisy_chain_interface::interface_post_reset()
{
	// loop over all chained devices and call their reset function
	for (device_z80daisy_interface *intf = m_chain; intf != nullptr; intf = intf->m_daisy_next)
		intf->device().reset();
>>>>>>> upstream/master
}


//-------------------------------------------------
//  update_irq_state - update the IRQ state and
//  return assert/clear based on the state
//-------------------------------------------------

<<<<<<< HEAD
int z80_daisy_chain::update_irq_state()
{
	// loop over all devices; dev[0] is highest priority
	for (daisy_entry *daisy = m_daisy_list; daisy != NULL; daisy = daisy->m_next)
	{
		// if this device is asserting the INT line, that's the one we want
		int state = daisy->m_interface->z80daisy_irq_state();
=======
int z80_daisy_chain_interface::daisy_update_irq_state()
{
	// loop over all devices; dev[0] is highest priority
	for (device_z80daisy_interface *intf = m_chain; intf != nullptr; intf = intf->m_daisy_next)
	{
		// if this device is asserting the INT line, that's the one we want
		int state = intf->z80daisy_irq_state();
>>>>>>> upstream/master
		if (state & Z80_DAISY_INT)
			return ASSERT_LINE;

		// if this device is asserting the IEO line, it blocks everyone else
		if (state & Z80_DAISY_IEO)
			return CLEAR_LINE;
	}
	return CLEAR_LINE;
}


//-------------------------------------------------
<<<<<<< HEAD
//  call_ack_device - acknowledge an interrupt
//  from a chained device and return the vector
//-------------------------------------------------

int z80_daisy_chain::call_ack_device()
{
	int vector = 0;

	// loop over all devices; dev[0] is the highest priority
	for (daisy_entry *daisy = m_daisy_list; daisy != NULL; daisy = daisy->m_next)
	{
		// if this device is asserting the INT line, that's the one we want
		int state = daisy->m_interface->z80daisy_irq_state();
		vector = daisy->m_interface->z80daisy_irq_ack();
		if (state & Z80_DAISY_INT)
			return vector;
	}
	//logerror("z80daisy_call_ack_device: failed to find an device to ack!\n");
	return vector;
=======
//  daisy_get_irq_device - return the device
//  in the chain that requested the interrupt
//-------------------------------------------------

device_z80daisy_interface *z80_daisy_chain_interface::daisy_get_irq_device()
{
	// loop over all devices; dev[0] is the highest priority
	for (device_z80daisy_interface *intf = m_chain; intf != nullptr; intf = intf->m_daisy_next)
	{
		// if this device is asserting the INT line, that's the one we want
		int state = intf->z80daisy_irq_state();
		if (state & Z80_DAISY_INT)
			return intf;
	}

	if (VERBOSE && daisy_chain_present())
		device().logerror("Interrupt from outside Z80 daisy chain\n");
	return nullptr;
>>>>>>> upstream/master
}


//-------------------------------------------------
//  call_reti_device - signal a RETI operator to
//  the chain
//-------------------------------------------------

<<<<<<< HEAD
void z80_daisy_chain::call_reti_device()
{
	// loop over all devices; dev[0] is the highest priority
	for (daisy_entry *daisy = m_daisy_list; daisy != NULL; daisy = daisy->m_next)
	{
		// if this device is asserting the IEO line, that's the one we want
		int state = daisy->m_interface->z80daisy_irq_state();
		if (state & Z80_DAISY_IEO)
		{
			daisy->m_interface->z80daisy_irq_reti();
			return;
		}
	}
	//logerror("z80daisy_call_reti_device: failed to find an device to reti!\n");
=======
void z80_daisy_chain_interface::daisy_call_reti_device()
{
	// loop over all devices; dev[0] is the highest priority
	for (device_z80daisy_interface *intf = m_chain; intf != nullptr; intf = intf->m_daisy_next)
	{
		// if this device is asserting the IEO line, that's the one we want
		int state = intf->z80daisy_irq_state();
		if (state & Z80_DAISY_IEO)
		{
			intf->z80daisy_irq_reti();
			return;
		}
	}
>>>>>>> upstream/master
}


//-------------------------------------------------
<<<<<<< HEAD
//  daisy_entry - constructor
//-------------------------------------------------

z80_daisy_chain::daisy_entry::daisy_entry(device_t *device)
	: m_next(NULL),
		m_device(device),
		m_interface(NULL)
{
	device->interface(m_interface);
=======
//  daisy_show_chain - list devices in the chain
//  in string format (for debugging purposes)
//-------------------------------------------------

std::string z80_daisy_chain_interface::daisy_show_chain() const
{
	std::ostringstream result;

	// loop over all devices
	for (device_z80daisy_interface *intf = m_chain; intf != nullptr; intf = intf->m_daisy_next)
	{
		if (intf != m_chain)
			result << " -> ";
		result << intf->device().tag();
	}

	return result.str();
>>>>>>> upstream/master
}
