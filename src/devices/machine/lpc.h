// license:BSD-3-Clause
// copyright-holders:Olivier Galibert
<<<<<<< HEAD
#ifndef LPC_H
#define LPC_H

#include "emu.h"

class lpc_device : public device_t {
public:
	lpc_device(const machine_config &mconfig, device_type type, const char *name, const char *tag, device_t *owner, UINT32 clock, const char *shortname, const char *source);

	virtual void map_device(UINT64 memory_window_start, UINT64 memory_window_end, UINT64 memory_offset, address_space *memory_space,
							UINT64 io_window_start, UINT64 io_window_end, UINT64 io_offset, address_space *io_space) = 0;
};

#endif
=======
#ifndef MAME_MACHINE_LPC_H
#define MAME_MACHINE_LPC_H

#pragma once


class lpc_device : public device_t {
public:
	virtual void map_device(uint64_t memory_window_start, uint64_t memory_window_end, uint64_t memory_offset, address_space *memory_space,
							uint64_t io_window_start, uint64_t io_window_end, uint64_t io_offset, address_space *io_space) = 0;

protected:
	using device_t::device_t;
};

#endif // MAME_MACHINE_LPC_H
>>>>>>> upstream/master
