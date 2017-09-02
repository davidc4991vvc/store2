// license:BSD-3-Clause
// copyright-holders:Aaron Giles
/*********************************************************************

    dvmemory.h

    Memory debugger view.

***************************************************************************/

<<<<<<< HEAD
#ifndef __DVMEMORY_H__
#define __DVMEMORY_H__
=======
#ifndef MAME_EMU_DEBUG_DVMEMORY_H
#define MAME_EMU_DEBUG_DVMEMORY_H

#pragma once

#include "debugvw.h"

#include "softfloat/mamesf.h"
#include "softfloat/softfloat.h"

>>>>>>> upstream/master

//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

// a memory view_source
class debug_view_memory_source : public debug_view_source
{
	friend class debug_view_memory;

	debug_view_memory_source(const char *name, address_space &space);
	debug_view_memory_source(const char *name, memory_region &region);
	debug_view_memory_source(const char *name, void *base, int element_size, int num_elements);

public:
	address_space *space() const { return m_space; }

private:
	address_space *m_space;                     // address space we reference (if any)
	device_memory_interface *m_memintf;         // pointer to the memory interface of the device
	void *              m_base;                 // pointer to memory base
	offs_t              m_length;               // length of memory
	offs_t              m_offsetxor;            // XOR to apply to offsets
	endianness_t        m_endianness;           // endianness of memory
<<<<<<< HEAD
	UINT8               m_prefsize;             // preferred bytes per chunk
=======
	u8                  m_prefsize;             // preferred bytes per chunk
>>>>>>> upstream/master
};


// debug view for memory
class debug_view_memory : public debug_view
{
<<<<<<< HEAD
	friend resource_pool_object<debug_view_memory>::~resource_pool_object();
=======
>>>>>>> upstream/master
	friend class debug_view_manager;

	// construction/destruction
	debug_view_memory(running_machine &machine, debug_view_osd_update_func osdupdate, void *osdprivate);

public:
	// getters
<<<<<<< HEAD
	const char *expression() { return m_expression.string(); }
	UINT8 bytes_per_chunk() { flush_updates(); return m_bytes_per_chunk; }
	UINT32 chunks_per_row() { flush_updates(); return m_chunks_per_row; }
=======
	const char *expression() const { return m_expression.string(); }
	int get_data_format() { flush_updates(); return m_data_format; }
	u32 chunks_per_row() { flush_updates(); return m_chunks_per_row; }
>>>>>>> upstream/master
	bool reverse() const { return m_reverse_view; }
	bool ascii() const { return m_ascii_view; }
	bool physical() const { return m_no_translation; }
	offs_t addressAtCursorPosition(const debug_view_xy& pos) { return get_cursor_pos(pos).m_address; }

	// setters
<<<<<<< HEAD
	void set_expression(const char *expression);
	void set_bytes_per_chunk(UINT8 chunkbytes);
	void set_chunks_per_row(UINT32 rowchunks);
=======
	void set_expression(const std::string &expression);
	void set_chunks_per_row(u32 rowchunks);
	void set_data_format(int format); // 1-8 current values 9 32bit floating point
>>>>>>> upstream/master
	void set_reverse(bool reverse);
	void set_ascii(bool reverse);
	void set_physical(bool physical);

protected:
	// view overrides
<<<<<<< HEAD
	virtual void view_notify(debug_view_notification type);
	virtual void view_update();
	virtual void view_char(int chval);
	virtual void view_click(const int button, const debug_view_xy& pos);
=======
	virtual void view_notify(debug_view_notification type) override;
	virtual void view_update() override;
	virtual void view_char(int chval) override;
	virtual void view_click(const int button, const debug_view_xy& pos) override;
>>>>>>> upstream/master

private:
	struct cursor_pos
	{
<<<<<<< HEAD
		cursor_pos(offs_t address = 0, UINT8 shift = 0) : m_address(address), m_shift(shift) { }
		offs_t m_address;
		UINT8 m_shift;
=======
		cursor_pos(offs_t address = 0, u8 shift = 0) : m_address(address), m_shift(shift) { }
		offs_t m_address;
		u8 m_shift;
>>>>>>> upstream/master
	};

	// internal helpers
	void enumerate_sources();
	void recompute();
	bool needs_recompute();

	// cursor position management
	cursor_pos get_cursor_pos(const debug_view_xy& cursor);
	void set_cursor_pos(cursor_pos pos);
	cursor_pos begin_update_and_get_cursor_pos() { begin_update(); return get_cursor_pos(m_cursor); }
	void end_update_and_set_cursor_pos(cursor_pos pos) { set_cursor_pos(pos); end_update(); }

	// memory access
<<<<<<< HEAD
	bool read(UINT8 size, offs_t offs, UINT64 &data);
	void write(UINT8 size, offs_t offs, UINT64 data);

	// internal state
	debug_view_expression m_expression;         // expression describing the start address
	UINT32              m_chunks_per_row;       // number of chunks displayed per line
	UINT8               m_bytes_per_chunk;      // bytes per chunk
	bool                m_reverse_view;         // reverse-endian view?
	bool                m_ascii_view;           // display ASCII characters?
	bool                m_no_translation;       // don't run addresses through the cpu translation hook
	offs_t              m_maxaddr;              // (derived) maximum address to display
	UINT32              m_bytes_per_row;        // (derived) number of bytes displayed per line
	UINT32              m_byte_offset;          // (derived) offset of starting visible byte
=======
	bool read(u8 size, offs_t offs, u64 &data);
	void write(u8 size, offs_t offs, u64 data);
	bool read(u8 size, offs_t offs, floatx80 &data);

	// internal state
	debug_view_expression m_expression;         // expression describing the start address
	u32                 m_chunks_per_row;       // number of chunks displayed per line
	u8                  m_bytes_per_chunk;      // bytes per chunk
	int                 m_data_format;          // 1-8 current values 9 32bit floating point
	bool                m_reverse_view;         // reverse-endian view?
	bool                m_ascii_view;           // display ASCII characters?
	bool                m_no_translation;       // don't run addresses through the cpu translation hook
	bool                m_edit_enabled;         // can modify contents ?
	offs_t              m_maxaddr;              // (derived) maximum address to display
	u32                 m_bytes_per_row;        // (derived) number of bytes displayed per line
	u32                 m_byte_offset;          // (derived) offset of starting visible byte
>>>>>>> upstream/master
	std::string         m_addrformat;           // (derived) format string to use to print addresses

	struct section
	{
		bool contains(int x) const { return x >= m_pos && x < m_pos + m_width; }
<<<<<<< HEAD
		INT32           m_pos;                  /* starting position */
		INT32           m_width;                /* width of this section */
=======
		s32             m_pos;                  /* starting position */
		s32             m_width;                /* width of this section */
>>>>>>> upstream/master
	};
	section             m_section[3];           // (derived) 3 sections to manage

	struct memory_view_pos
	{
<<<<<<< HEAD
		UINT8           m_spacing;              /* spacing between each entry */
		UINT8           m_shift[24];            /* shift for each character */
	};
	static const memory_view_pos s_memory_pos_table[9]; // table for rendering at different chunk sizes

	// constants
	static const int MEM_MAX_LINE_WIDTH = 1024;
};


#endif
=======
		u8           m_spacing;              /* spacing between each entry */
		u8           m_shift[24];            /* shift for each character */
	};
	static const memory_view_pos s_memory_pos_table[12]; // table for rendering at different data formats

	// constants
	static constexpr int MEM_MAX_LINE_WIDTH = 1024;
};

#endif // MAME_EMU_DEBUG_DVMEMORY_H
>>>>>>> upstream/master
