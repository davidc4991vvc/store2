// license:BSD-3-Clause
// copyright-holders:Nicola Salmoria, Andreas Naive, Charles MacDonald
/***************************************************************************

    Hitachi FD1094 encryption emulation

****************************************************************************

    Copyright Nicola Salmoria, Andreas Naive, and Charles MacDonald.

    All rights reserved.

***************************************************************************/

<<<<<<< HEAD
#ifndef __FD1094_H__
#define __FD1094_H__
=======
#ifndef MAME_MACHINE_FD1094_H
#define MAME_MACHINE_FD1094_H

#pragma once
>>>>>>> upstream/master

#include "cpu/m68000/m68000.h"


//**************************************************************************
//  CONSTANTS
//**************************************************************************

// device type definition
extern const device_type FD1094;



//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

class fd1094_device;


// ======================> fd1094_decryption_cache

class fd1094_decryption_cache
{
public:
	// construction/destruction
	fd1094_decryption_cache(fd1094_device &fd1094);

	// getters
	fd1094_device &fd1094() const { return m_fd1094; }
<<<<<<< HEAD
	UINT16 *decrypted_opcodes(UINT8 state);

	// operations
	void reset();
	void configure(offs_t baseaddress, UINT32 size, offs_t rgnoffset);
=======
	uint16_t *decrypted_opcodes(uint8_t state);

	// operations
	void reset();
	void configure(offs_t baseaddress, uint32_t size, offs_t rgnoffset);
>>>>>>> upstream/master

protected:
	// internal state
	fd1094_device &         m_fd1094;
<<<<<<< HEAD
	UINT32                  m_baseaddress;
	UINT32                  m_size;
	UINT32                  m_rgnoffset;
	std::vector<UINT16>          m_decrypted_opcodes[256];
=======
	uint32_t                  m_baseaddress;
	uint32_t                  m_size;
	uint32_t                  m_rgnoffset;
	std::vector<uint16_t>     m_decrypted_opcodes[256];
>>>>>>> upstream/master
};


// ======================> fd1094_device

// base device, shared implementation between A and B variants
class fd1094_device : public m68000_device
{
public:
<<<<<<< HEAD
	typedef delegate<void (UINT8)> state_change_delegate;

	// construction/destruction
	fd1094_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// explicit decryption helpers
	void decrypt(offs_t baseaddr, UINT32 size, offs_t regionoffs, UINT16 *opcodesptr, UINT8 state) { decrypt(baseaddr, size, m_srcbase + regionoffs/2, opcodesptr, state); }

	// live state management
	UINT8 state() const { return m_irqmode ? m_key[0] : m_state; }
=======
	typedef delegate<void (uint8_t)> state_change_delegate;

	// construction/destruction
	fd1094_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// explicit decryption helpers
	void decrypt(offs_t baseaddr, uint32_t size, offs_t regionoffs, uint16_t *opcodesptr, uint8_t state) { decrypt(baseaddr, size, &m_srcbase[regionoffs/2], opcodesptr, state); }

	// live state management
	uint8_t state() const { return m_irqmode ? m_key[0] : m_state; }
>>>>>>> upstream/master
	void change_state(int newstate = -1);
	void notify_state_change(state_change_delegate callback) { m_state_change = callback; }

	// constants
	enum
	{
		STATE_RESET = 0x100,
		STATE_IRQ = 0x200,
		STATE_RTE = 0x300
	};

protected:
	required_memory_bank m_decrypted_opcodes_bank;

	// device overrides
<<<<<<< HEAD
	virtual void device_start();
	virtual void device_reset();
	virtual void device_postload();

	// internal helpers
	UINT16 decrypt_one(offs_t address, UINT16 val, const UINT8 *main_key, UINT8 state, bool vector_fetch);
	void decrypt(offs_t baseaddr, UINT32 size, const UINT16 *srcptr, UINT16 *opcodesptr, UINT8 state);
	void default_state_change(UINT8 state);
=======
	virtual void device_start() override;
	virtual void device_reset() override;
	virtual void device_postload();

	// internal helpers
	uint16_t decrypt_one(offs_t address, uint16_t val, const uint8_t *main_key, uint8_t state, bool vector_fetch);
	void decrypt(offs_t baseaddr, uint32_t size, const uint16_t *srcptr, uint16_t *opcodesptr, uint8_t state);
	void default_state_change(uint8_t state);
>>>>>>> upstream/master
	IRQ_CALLBACK_MEMBER( irq_callback );

	// static helpers
	DECLARE_WRITE32_MEMBER(cmp_callback);
	DECLARE_WRITE_LINE_MEMBER(rte_callback);

	// internal state
<<<<<<< HEAD
	UINT8                   m_state;
	bool                    m_irqmode;
	state_change_delegate   m_state_change;
	fd1094_decryption_cache m_cache;
	UINT16 *                m_srcbase;
	UINT32                  m_srcbytes;
	const UINT8 *           m_key;
	UINT8                   m_masked_opcodes_lookup[2][65536/8/2];

	// static tables
	static const UINT16 s_masked_opcodes[];
=======
	uint8_t                   m_state;
	bool                    m_irqmode;
	state_change_delegate   m_state_change;
	fd1094_decryption_cache m_cache;
	uint16_t const            *m_srcbase;
	optional_region_ptr<uint16_t> m_rom;
	required_region_ptr<uint8_t> m_key;
	uint8_t                   m_masked_opcodes_lookup[2][65536/8/2];

	// static tables
	static const uint16_t s_masked_opcodes[];
>>>>>>> upstream/master
};

struct fd1094_constraint
{
	offs_t  pc;
<<<<<<< HEAD
	UINT16  state;
	UINT16  value;
	UINT16  mask;
};

#endif
=======
	uint16_t  state;
	uint16_t  value;
	uint16_t  mask;
};

#endif // MAME_MACHINE_FD1094_H
>>>>>>> upstream/master
