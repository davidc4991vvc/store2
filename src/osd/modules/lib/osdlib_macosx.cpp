// license:BSD-3-Clause
// copyright-holders:Olivier Galibert, R. Belmont
//============================================================
//
//  sdlos_*.c - OS specific low level code
//
//  SDLMAME by Olivier Galibert and R. Belmont
//
//============================================================

#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <signal.h>
<<<<<<< HEAD

#include <mach/mach.h>
#include <mach/mach_time.h>
#include <mach/mach_traps.h>
=======
#include <dlfcn.h>

#include <cstdio>
#include <iomanip>
#include <memory>


#include <mach/mach.h>
#include <mach/mach_time.h>
>>>>>>> upstream/master
#include <Carbon/Carbon.h>

// MAME headers
#include "osdcore.h"
#include "osdlib.h"

<<<<<<< HEAD
// FIXME: We shouldn't use SDL functions in here

#include "sdlinc.h"

=======
>>>>>>> upstream/master
//============================================================
//  osd_getenv
//============================================================

const char *osd_getenv(const char *name)
{
	return getenv(name);
}

//============================================================
//  osd_setenv
//============================================================

int osd_setenv(const char *name, const char *value, int overwrite)
{
	return setenv(name, value, overwrite);
}

//============================================================
//  osd_process_kill
//============================================================

<<<<<<< HEAD
void osd_process_kill(void)
=======
void osd_process_kill()
>>>>>>> upstream/master
{
	kill(getpid(), SIGKILL);
}

//============================================================
<<<<<<< HEAD
//  osd_num_processors
//============================================================

int osd_get_num_processors(void)
{
	int processors = 1;

	struct host_basic_info host_basic_info;
	unsigned int count;
	kern_return_t r;
	mach_port_t my_mach_host_self;

	count = HOST_BASIC_INFO_COUNT;
	my_mach_host_self = mach_host_self();
	if ( ( r = host_info(my_mach_host_self, HOST_BASIC_INFO, (host_info_t)(&host_basic_info), &count)) == KERN_SUCCESS )
	{
		processors = host_basic_info.avail_cpus;
	}
	mach_port_deallocate(mach_task_self(), my_mach_host_self);

	return processors;
}

//============================================================
//  osd_malloc
//============================================================

void *osd_malloc(size_t size)
{
#ifndef MALLOC_DEBUG
	return malloc(size);
#else
#error "MALLOC_DEBUG not yet supported"
#endif
}


//============================================================
//  osd_malloc_array
//============================================================

void *osd_malloc_array(size_t size)
{
#ifndef MALLOC_DEBUG
	return malloc(size);
#else
#error "MALLOC_DEBUG not yet supported"
#endif
}


//============================================================
//  osd_free
//============================================================

void osd_free(void *ptr)
{
#ifndef MALLOC_DEBUG
	free(ptr);
#else
#error "MALLOC_DEBUG not yet supported"
#endif
}


//============================================================
=======
>>>>>>> upstream/master
//  osd_alloc_executable
//
//  allocates "size" bytes of executable memory.  this must take
//  things like NX support into account.
//============================================================

void *osd_alloc_executable(size_t size)
{
#if defined(SDLMAME_BSD) || defined(SDLMAME_MACOSX)
	return (void *)mmap(0, size, PROT_EXEC|PROT_READ|PROT_WRITE, MAP_ANON|MAP_SHARED, -1, 0);
#elif defined(SDLMAME_UNIX)
	return (void *)mmap(0, size, PROT_EXEC|PROT_READ|PROT_WRITE, MAP_ANON|MAP_SHARED, 0, 0);
#endif
}

//============================================================
//  osd_free_executable
//
//  frees memory allocated with osd_alloc_executable
//============================================================

void osd_free_executable(void *ptr, size_t size)
{
#ifdef SDLMAME_SOLARIS
	munmap((char *)ptr, size);
#else
	munmap(ptr, size);
#endif
}

//============================================================
//  osd_break_into_debugger
//============================================================

void osd_break_into_debugger(const char *message)
{
	#ifdef MAME_DEBUG
	printf("MAME exception: %s\n", message);
	printf("Attempting to fall into debugger\n");
	kill(getpid(), SIGTRAP);
	#else
	printf("Ignoring MAME exception: %s\n", message);
	#endif
}


//============================================================
<<<<<<< HEAD
//  PROTOTYPES
//============================================================

static osd_ticks_t init_cycle_counter(void);
static osd_ticks_t mach_cycle_counter(void);

//============================================================
//  STATIC VARIABLES
//============================================================

static osd_ticks_t      (*cycle_counter)(void) = init_cycle_counter;
static osd_ticks_t      (*ticks_counter)(void) = init_cycle_counter;
static osd_ticks_t      ticks_per_second;

//============================================================
//  init_cycle_counter
//
//  to avoid total grossness, this function is split by subarch
//============================================================

static osd_ticks_t init_cycle_counter(void)
{
	osd_ticks_t start, end;
	osd_ticks_t a, b;

	cycle_counter = mach_cycle_counter;
	ticks_counter = mach_cycle_counter;

	// wait for an edge on the timeGetTime call
	a = SDL_GetTicks();
	do
	{
		b = SDL_GetTicks();
	} while (a == b);

	// get the starting cycle count
	start = (*cycle_counter)();

	// now wait for 1/4 second total
	do
	{
		a = SDL_GetTicks();
	} while (a - b < 250);

	// get the ending cycle count
	end = (*cycle_counter)();

	// compute ticks_per_sec
	ticks_per_second = (end - start) * 4;

	// return the current cycle count
	return (*cycle_counter)();
}

//============================================================
//  performance_cycle_counter
//============================================================

//============================================================
//  mach_cycle_counter
//============================================================
static osd_ticks_t mach_cycle_counter(void)
{
	return mach_absolute_time();
}

//============================================================
//   osd_ticks
//============================================================

osd_ticks_t osd_ticks(void)
{
	return (*cycle_counter)();
}


//============================================================
//  osd_ticks_per_second
//============================================================

osd_ticks_t osd_ticks_per_second(void)
{
	if (ticks_per_second == 0)
	{
		// if we haven't computed the value yet, there's no time like the present
		init_cycle_counter();
	}
	return ticks_per_second;
}



//============================================================
//  osd_sleep
//============================================================

void osd_sleep(osd_ticks_t duration)
{
	UINT32 msec;

	// make sure we've computed ticks_per_second
	if (ticks_per_second == 0)
		(void)osd_ticks();

	// convert to milliseconds, rounding down
	msec = (UINT32)(duration * 1000 / ticks_per_second);

	// only sleep if at least 2 full milliseconds
	if (msec >= 2)
	{
		// take a couple of msecs off the top for good measure
		msec -= 2;
		usleep(msec*1000);
	}
}
=======
//  osd_get_clipboard_text
//============================================================

char *osd_get_clipboard_text(void)
{
	OSStatus err;

	PasteboardRef pasteboard_ref;
	err = PasteboardCreate(kPasteboardClipboard, &pasteboard_ref);
	if (err)
		return nullptr;

	PasteboardSynchronize(pasteboard_ref);

	ItemCount item_count;
	err = PasteboardGetItemCount(pasteboard_ref, &item_count);

	char *result = nullptr; // core expects a malloced C string of uft8 data
	for (UInt32 item_index = 1; (item_index <= item_count) && !result; item_index++)
	{
		PasteboardItemID item_id;
		err = PasteboardGetItemIdentifier(pasteboard_ref, item_index, &item_id);
		if (err)
			continue;

		CFArrayRef flavor_type_array;
		err = PasteboardCopyItemFlavors(pasteboard_ref, item_id, &flavor_type_array);
		if (err)
			continue;

		CFIndex const flavor_count = CFArrayGetCount(flavor_type_array);
		for (CFIndex flavor_index = 0; (flavor_index < flavor_count) && !result; flavor_index++)
		{
			CFStringRef const flavor_type = (CFStringRef)CFArrayGetValueAtIndex(flavor_type_array, flavor_index);

			CFStringEncoding encoding;
			if (UTTypeConformsTo(flavor_type, kUTTypeUTF16PlainText))
				encoding = kCFStringEncodingUTF16;
			else if (UTTypeConformsTo (flavor_type, kUTTypeUTF8PlainText))
				encoding = kCFStringEncodingUTF8;
			else if (UTTypeConformsTo (flavor_type, kUTTypePlainText))
				encoding = kCFStringEncodingMacRoman;
			else
				continue;

			CFDataRef flavor_data;
			err = PasteboardCopyItemFlavorData(pasteboard_ref, item_id, flavor_type, &flavor_data);

			if (!err)
			{
				CFStringRef string_ref = CFStringCreateFromExternalRepresentation(kCFAllocatorDefault, flavor_data, encoding);
				CFDataRef data_ref = CFStringCreateExternalRepresentation (kCFAllocatorDefault, string_ref, kCFStringEncodingUTF8, '?');
				CFRelease(string_ref);
				CFRelease(flavor_data);

				CFIndex const length = CFDataGetLength(data_ref);
				CFRange const range = CFRangeMake(0, length);

				result = reinterpret_cast<char *>(malloc(length + 1));
				if (result)
				{
					CFDataGetBytes(data_ref, range, reinterpret_cast<unsigned char *>(result));
					result[length] = 0;
				}

				CFRelease(data_ref);
			}
		}

		CFRelease(flavor_type_array);
	}

	CFRelease(pasteboard_ref);

	return result;
}

//============================================================
//  dynamic_module_posix_impl
//============================================================

namespace osd {
class dynamic_module_posix_impl : public dynamic_module
{
public:
	dynamic_module_posix_impl(std::vector<std::string> &libraries)
		: m_module(nullptr)
	{
		m_libraries = libraries;
	}

	virtual ~dynamic_module_posix_impl() override
	{
		if (m_module != nullptr)
			dlclose(m_module);
	};

protected:
	virtual generic_fptr_t get_symbol_address(char const *symbol) override
	{
		/*
		 * given a list of libraries, if a first symbol is successfully loaded from
		 * one of them, all additional symbols will be loaded from the same library
		 */
		if (m_module)
		{
			return reinterpret_cast<generic_fptr_t>(dlsym(m_module, symbol));
		}

		for (auto const &library : m_libraries)
		{
			void *module = dlopen(library.c_str(), RTLD_LAZY);

			if (module != nullptr)
			{
				generic_fptr_t function = reinterpret_cast<generic_fptr_t>(dlsym(module, symbol));

				if (function != nullptr)
				{
					m_module = module;
					return function;
				}
				else
				{
					dlclose(module);
				}
			}
		}

		return nullptr;
	}

private:
	std::vector<std::string> m_libraries;
	void *                   m_module;
};

dynamic_module::ptr dynamic_module::open(std::vector<std::string> &&names)
{
	return std::make_unique<dynamic_module_posix_impl>(names);
}

} // namespace osd
>>>>>>> upstream/master
