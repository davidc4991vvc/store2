// license:BSD-3-Clause
<<<<<<< HEAD
// copyright-holders:Nicola Salmoria, Aaron Giles
=======
// copyright-holders:Nicola Salmoria, Aaron Giles, Vas Crabb
>>>>>>> upstream/master
/***************************************************************************

    output.c

    General purpose output routines.
***************************************************************************/

#include "emu.h"
#include "coreutil.h"
<<<<<<< HEAD

/***************************************************************************
    CONSTANTS
***************************************************************************/

#define HASH_SIZE       53



/***************************************************************************
    TYPE DEFINITIONS
***************************************************************************/

class output_notify
{
public:
	output_notify(output_notifier_func callback, void *param)
		: m_next(NULL),
			m_notifier(callback),
			m_param(param) { }

	output_notify *next() const { return m_next; }

	output_notify *         m_next;           /* link to next item */
	output_notifier_func    m_notifier;       /* callback to call */
	void *                  m_param;          /* parameter to pass the callback */
};


struct output_item
{
	output_item *       next;           /* next item in list */
	std::string         name;           /* string name of the item */
	UINT32              hash;           /* hash for this item name */
	UINT32              id;             /* unique ID for this item */
	INT32               value;          /* current value */
	simple_list<output_notify> notifylist;     /* list of notifier callbacks */
};



/***************************************************************************
    GLOBAL VARIABLES
***************************************************************************/

static output_item *itemtable[HASH_SIZE];
static simple_list<output_notify> global_notifylist;
static UINT32 uniqueid = 12345;



/***************************************************************************
    FUNCTION PROTOTYPES
***************************************************************************/

static void output_pause(running_machine &machine);
static void output_resume(running_machine &machine);
static void output_exit(running_machine &machine);



/***************************************************************************
    INLINE FUNCTIONS
***************************************************************************/

/*-------------------------------------------------
    get_hash - return the hash of an output value
-------------------------------------------------*/

INLINE UINT32 get_hash(const char *string)
{
	return core_crc32(0, (UINT8 *)string, (UINT32)strlen(string));
}


=======
#include "modules/output/output_module.h"


#define OUTPUT_VERBOSE  0



//**************************************************************************
//  OUTPUT ITEM
//**************************************************************************

output_manager::output_item::output_item(
		output_manager &manager,
		std::string &&name,
		u32 id,
		s32 value)
	: m_manager(manager)
	, m_name(std::move(name))
	, m_id(id)
	, m_value(value)
	, m_notifylist()
{
}


void output_manager::output_item::notify(s32 value)
{
	if (OUTPUT_VERBOSE)
		m_manager.machine().logerror("Output %s = %d (was %d)\n", m_name, value, m_value);
	m_value = value;

	// call the local notifiers first
	for (auto const &notify : m_notifylist)
		notify(m_name.c_str(), value);

	// call the global notifiers next
	for (auto const &notify : m_manager.m_global_notifylist)
		notify(m_name.c_str(), value);
}



//**************************************************************************
//  OUTPUT ITEM PROXY
//**************************************************************************

void output_manager::item_proxy::resolve(device_t &device, std::string const &name)
{
	assert(!m_item);
	m_item = device.machine().output().find_item(name.c_str());
	if (!m_item)
		m_item = &device.machine().output().create_new_item(name.c_str(), 0);
}



//**************************************************************************
//  OUTPUT MANAGER
//**************************************************************************

//-------------------------------------------------
//  output_manager - constructor
//-------------------------------------------------

output_manager::output_manager(running_machine &machine)
	: m_machine(machine),
		m_uniqueid(12345)
{
	/* add pause callback */
	machine.add_notifier(MACHINE_NOTIFY_PAUSE, machine_notify_delegate(&output_manager::pause, this));
	machine.add_notifier(MACHINE_NOTIFY_RESUME, machine_notify_delegate(&output_manager::resume, this));
}

>>>>>>> upstream/master
/*-------------------------------------------------
    find_item - find an item based on a string
-------------------------------------------------*/

<<<<<<< HEAD
INLINE output_item *find_item(const char *string)
{
	UINT32 hash = get_hash(string);
	output_item *item;

	/* use the hash as a starting point and find an entry */
	for (item = itemtable[hash % HASH_SIZE]; item != NULL; item = item->next)
		if (item->hash == hash && strcmp(string, item->name.c_str()) == 0)
			return item;

	return NULL;
=======
output_manager::output_item* output_manager::find_item(const char *string)
{
	auto item = m_itemtable.find(std::string(string));
	if (item != m_itemtable.end())
		return &item->second;

	return nullptr;
>>>>>>> upstream/master
}


/*-------------------------------------------------
    create_new_item - create a new item
-------------------------------------------------*/

<<<<<<< HEAD
INLINE output_item *create_new_item(const char *outname, INT32 value)
{
	output_item *item = global_alloc(output_item);
	UINT32 hash = get_hash(outname);

	/* fill in the data */
	item->next = itemtable[hash % HASH_SIZE];
	item->name.assign(outname);
	item->hash = hash;
	item->id = uniqueid++;
	item->value = value;

	/* add us to the hash table */
	itemtable[hash % HASH_SIZE] = item;
	return item;
}



/***************************************************************************
    CORE IMPLEMENTATION
***************************************************************************/

/*-------------------------------------------------
    output_init - initialize everything
-------------------------------------------------*/

void output_init(running_machine &machine)
{
	/* add pause callback */
	machine.add_notifier(MACHINE_NOTIFY_PAUSE, machine_notify_delegate(FUNC(output_pause), &machine));
	machine.add_notifier(MACHINE_NOTIFY_RESUME, machine_notify_delegate(FUNC(output_resume), &machine));

	/* get a callback when done */
	machine.add_notifier(MACHINE_NOTIFY_EXIT, machine_notify_delegate(FUNC(output_exit), &machine));

	/* reset the lists */
	memset(itemtable, 0, sizeof(itemtable));
	global_notifylist.reset();
}


=======
output_manager::output_item &output_manager::create_new_item(const char *outname, s32 value)
{
	auto const ins(m_itemtable.emplace(
			std::piecewise_construct,
			std::forward_as_tuple(outname),
			std::forward_as_tuple(*this, outname, m_uniqueid++, value)));
	assert(ins.second);
	return ins.first->second;
}

>>>>>>> upstream/master
/*-------------------------------------------------
    output_pause - send pause message
-------------------------------------------------*/

<<<<<<< HEAD
static void output_pause(running_machine &machine)
{
	output_set_value("pause", 1);
}

static void output_resume(running_machine &machine)
{
	output_set_value("pause", 0);
}


/*-------------------------------------------------
    output_exit - cleanup on exit
-------------------------------------------------*/

static void output_exit(running_machine &machine)
{
	output_item *item;
	int hash;

	/* remove all items */
	for (hash = 0; hash < HASH_SIZE; hash++)
		for (item = itemtable[hash]; item != NULL; )
		{
			output_item *next = item->next;

			/* free the name and the item */
			global_free(item);
			item = next;
		}

	/* remove all global notifiers */
	global_notifylist.reset();
=======
void output_manager::pause()
{
	set_value("pause", 1);
}

void output_manager::resume()
{
	set_value("pause", 0);
>>>>>>> upstream/master
}


/*-------------------------------------------------
    output_set_value - set the value of an output
-------------------------------------------------*/

<<<<<<< HEAD
void output_set_value(const char *outname, INT32 value)
{
	output_item *item = find_item(outname);
	INT32 oldval;

	/* if no item of that name, create a new one and send the item's state */
	if (item == NULL)
	{
		item = create_new_item(outname, value);
		oldval = value + 1;
	}

	else
	{
		/* set the new value */
		oldval = item->value;
		item->value = value;
	}

	/* if the value is different, signal the notifier */
	if (oldval != value)
	{
		/* call the local notifiers first */
		for (output_notify *notify = item->notifylist.first(); notify != NULL; notify = notify->next())
			(*notify->m_notifier)(outname, value, notify->m_param);

		/* call the global notifiers next */
		for (output_notify *notify = global_notifylist.first(); notify != NULL; notify = notify->next())
			(*notify->m_notifier)(outname, value, notify->m_param);
	}
=======
void output_manager::set_value(const char *outname, s32 value)
{
	output_item *const item = find_item(outname);

	// if no item of that name, create a new one and force notification
	if (!item)
		create_new_item(outname, value).notify(value);
	else
		item->set(value); // set the new value (notifies on change)
>>>>>>> upstream/master
}


/*-------------------------------------------------
    output_set_indexed_value - set the value of an
    indexed output
-------------------------------------------------*/

<<<<<<< HEAD
void output_set_indexed_value(const char *basename, int index, int value)
=======
void output_manager::set_indexed_value(const char *basename, int index, int value)
>>>>>>> upstream/master
{
	char buffer[100];
	char *dest = buffer;

	/* copy the string */
	while (*basename != 0)
		*dest++ = *basename++;

	/* append the index */
	if (index >= 1000) *dest++ = '0' + ((index / 1000) % 10);
	if (index >= 100) *dest++ = '0' + ((index / 100) % 10);
	if (index >= 10) *dest++ = '0' + ((index / 10) % 10);
	*dest++ = '0' + (index % 10);
	*dest++ = 0;

	/* set the value */
<<<<<<< HEAD
	output_set_value(buffer, value);
=======
	set_value(buffer, value);
>>>>>>> upstream/master
}


/*-------------------------------------------------
    output_get_value - return the value of an
    output
-------------------------------------------------*/

<<<<<<< HEAD
INT32 output_get_value(const char *outname)
{
	output_item *item = find_item(outname);

	/* if no item, value is 0 */
	if (item == NULL)
		return 0;
	return item->value;
=======
s32 output_manager::get_value(const char *outname)
{
	output_item const *const item = find_item(outname);

	// if no item, value is 0
	return item ? item->get() : 0;
>>>>>>> upstream/master
}


/*-------------------------------------------------
    output_get_indexed_value - get the value of an
    indexed output
-------------------------------------------------*/

<<<<<<< HEAD
INT32 output_get_indexed_value(const char *basename, int index)
=======
s32 output_manager::get_indexed_value(const char *basename, int index)
>>>>>>> upstream/master
{
	char buffer[100];
	char *dest = buffer;

	/* copy the string */
	while (*basename != 0)
		*dest++ = *basename++;

	/* append the index */
	if (index >= 1000) *dest++ = '0' + ((index / 1000) % 10);
	if (index >= 100) *dest++ = '0' + ((index / 100) % 10);
	if (index >= 10) *dest++ = '0' + ((index / 10) % 10);
	*dest++ = '0' + (index % 10);
	*dest++ = 0;

	/* set the value */
<<<<<<< HEAD
	return output_get_value(buffer);
=======
	return get_value(buffer);
>>>>>>> upstream/master
}


/*-------------------------------------------------
    output_set_notifier - sets a notifier callback
    for a particular output, or for all outputs
<<<<<<< HEAD
    if NULL is specified
-------------------------------------------------*/

void output_set_notifier(const char *outname, output_notifier_func callback, void *param)
{
	/* if an item is specified, find it */
	if (outname != NULL)
	{
		output_item *item = find_item(outname);

		/* if no item of that name, create a new one */
		if (item == NULL)
			item = create_new_item(outname, 0);
		item->notifylist.append(*global_alloc(output_notify(callback, param)));
	}
	else
		global_notifylist.append(*global_alloc(output_notify(callback, param)));
=======
    if nullptr is specified
-------------------------------------------------*/

void output_manager::set_notifier(const char *outname, output_notifier_func callback, void *param)
{
	// if an item is specified, find/create it
	if (outname)
	{
		output_item *const item = find_item(outname);
		(item ? *item : create_new_item(outname, 0)).set_notifier(callback, param);
	}
	else
	{
		m_global_notifylist.emplace_back(callback, param);
	}
>>>>>>> upstream/master
}


/*-------------------------------------------------
    output_notify_all - immediately call the given
    notifier for all outputs
-------------------------------------------------*/

<<<<<<< HEAD
void output_notify_all(output_notifier_func callback, void *param)
{
	output_item *item;
	int hash;

	/* remove all items */
	for (hash = 0; hash < HASH_SIZE; hash++)
		for (item = itemtable[hash]; item != NULL; item = item->next)
			(*callback)(item->name.c_str(), item->value, param);
=======
void output_manager::notify_all(output_module *module)
{
	for (auto &item : m_itemtable)
		module->notify(item.second.name().c_str(), item.second.get());
>>>>>>> upstream/master
}


/*-------------------------------------------------
    output_name_to_id - returns a unique ID for
    a given name
-------------------------------------------------*/

<<<<<<< HEAD
UINT32 output_name_to_id(const char *outname)
{
	output_item *item = find_item(outname);

	/* if no item, ID is 0 */
	if (item == NULL)
		return 0;
	return item->id;
=======
u32 output_manager::name_to_id(const char *outname)
{
	// if no item, ID is 0
	output_item const *const item = find_item(outname);
	return item ? item->id() : 0;
>>>>>>> upstream/master
}


/*-------------------------------------------------
    output_id_to_name - returns a name that maps
    to a given unique ID
-------------------------------------------------*/

<<<<<<< HEAD
const char *output_id_to_name(UINT32 id)
{
	output_item *item;
	int hash;

	/* remove all items */
	for (hash = 0; hash < HASH_SIZE; hash++)
		for (item = itemtable[hash]; item != NULL; item = item->next)
			if (item->id == id)
				return item->name.c_str();

	/* nothing found, return NULL */
	return NULL;
=======
const char *output_manager::id_to_name(u32 id)
{
	for (auto &item : m_itemtable)
		if (item.second.id() == id)
			return item.second.name().c_str();

	/* nothing found, return nullptr */
	return nullptr;
>>>>>>> upstream/master
}
