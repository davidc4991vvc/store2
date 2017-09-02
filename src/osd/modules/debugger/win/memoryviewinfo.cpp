// license:BSD-3-Clause
// copyright-holders:Aaron Giles, Vas Crabb
//============================================================
//
//  memoryviewinfo.c - Win32 debug window handling
//
//============================================================

<<<<<<< HEAD
=======
#include "emu.h"
>>>>>>> upstream/master
#include "memoryviewinfo.h"

#include "debug/dvmemory.h"


memoryview_info::memoryview_info(debugger_windows_interface &debugger, debugwin_info &owner, HWND parent) :
	debugview_info(debugger, owner, parent, DVT_MEMORY)
{
}


memoryview_info::~memoryview_info()
{
}


<<<<<<< HEAD
UINT8 memoryview_info::bytes_per_chunk() const
{
	return view<debug_view_memory>()->bytes_per_chunk();
}


UINT32 memoryview_info::chunks_per_row() const
=======
uint8_t memoryview_info::data_format() const
{
	return view<debug_view_memory>()->get_data_format();
}


uint32_t memoryview_info::chunks_per_row() const
>>>>>>> upstream/master
{
	return view<debug_view_memory>()->chunks_per_row();
}


bool memoryview_info::reverse() const
{
	return view<debug_view_memory>()->reverse();
}


bool memoryview_info::physical() const
{
	return view<debug_view_memory>()->physical();
}


<<<<<<< HEAD
void memoryview_info::set_expression(char const *string)
=======
void memoryview_info::set_expression(const std::string &string)
>>>>>>> upstream/master
{
	view<debug_view_memory>()->set_expression(string);
}

<<<<<<< HEAD
void memoryview_info::set_bytes_per_chunk(UINT8 chunkbytes)
{
	view<debug_view_memory>()->set_bytes_per_chunk(chunkbytes);
}

void memoryview_info::set_chunks_per_row(UINT32 rowchunks)
=======
void memoryview_info::set_data_format(uint8_t dataformat)
{
	view<debug_view_memory>()->set_data_format(dataformat);
}

void memoryview_info::set_chunks_per_row(uint32_t rowchunks)
>>>>>>> upstream/master
{
	view<debug_view_memory>()->set_chunks_per_row(rowchunks);
}

void memoryview_info::set_reverse(bool reverse)
{
	view<debug_view_memory>()->set_reverse(reverse);
}

void memoryview_info::set_physical(bool physical)
{
	view<debug_view_memory>()->set_physical(physical);
}
