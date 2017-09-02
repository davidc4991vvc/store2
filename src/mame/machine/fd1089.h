// license:BSD-3-Clause
// copyright-holders:Nicola Salmoria, Andreas Naive, Charles MacDonald
/***************************************************************************

    Hitachi FD1089A/FD1089B encryption emulation

****************************************************************************

    Copyright Nicola Salmoria, Andreas Naive, and Charles MacDonald.

    All rights reserved.

***************************************************************************/

<<<<<<< HEAD
#ifndef __FD1089_H__
#define __FD1089_H__
=======
#ifndef MAME_MACHINE_FD1089_H
#define MAME_MACHINE_FD1089_H

#pragma once
>>>>>>> upstream/master

#include "cpu/m68000/m68000.h"


//**************************************************************************
//  CONSTANTS
//**************************************************************************

// device type definition
<<<<<<< HEAD
extern const device_type FD1089A;
extern const device_type FD1089B;
=======
DECLARE_DEVICE_TYPE(FD1089A, fd1089a_device)
DECLARE_DEVICE_TYPE(FD1089B, fd1089b_device)
>>>>>>> upstream/master



//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

// ======================> fd1089_base_device

// base device, shared implementation between A and B variants
class fd1089_base_device : public m68000_device
{
public:
<<<<<<< HEAD
	// construction/destruction
	fd1089_base_device(const machine_config &mconfig, device_type type, const char *name, const char *tag, device_t *owner, UINT32 clock, const char *shortname, const char *source);

	// explicit decryption helpers
	void decrypt(offs_t baseaddr, UINT32 size, offs_t regionoffs, UINT16 *opcodesptr, UINT16 *dataptr) { decrypt(baseaddr, size, &m_plaintext[regionoffs/2], opcodesptr, dataptr); }

protected:
	// device overrides
	virtual void device_start();

	// internal helpers
	UINT8 rearrange_key(UINT8 table, bool opcode);
	virtual UINT8 decode(UINT8 val, UINT8 key, bool opcode) = 0;
	UINT16 decrypt_one(offs_t addr, UINT16 val, const UINT8 *key, bool opcode);
	void decrypt(offs_t baseaddr, UINT32 size, const UINT16 *srcptr, UINT16 *opcodesptr, UINT16 *dataptr);

	// internal state
	const UINT8 *           m_key;
	std::vector<UINT16>          m_plaintext;
	required_shared_ptr<UINT16>  m_decrypted_opcodes;
=======
	// explicit decryption helpers
	void decrypt(offs_t baseaddr, uint32_t size, offs_t regionoffs, uint16_t *opcodesptr, uint16_t *dataptr) { decrypt(baseaddr, size, &m_plaintext[regionoffs/2], opcodesptr, dataptr); }

protected:
	// construction/destruction
	fd1089_base_device(const machine_config &mconfig, device_type type, const char *tag, device_t *owner, uint32_t clock);

	// device overrides
	virtual void device_start() override;

	// internal helpers
	uint8_t rearrange_key(uint8_t table, bool opcode);
	virtual uint8_t decode(uint8_t val, uint8_t key, bool opcode) = 0;
	uint16_t decrypt_one(offs_t addr, uint16_t val, const uint8_t *key, bool opcode);
	void decrypt(offs_t baseaddr, uint32_t size, const uint16_t *srcptr, uint16_t *opcodesptr, uint16_t *dataptr);

	// internal state
	required_memory_region       m_region;
	required_region_ptr<uint8_t>   m_key;
	std::vector<uint16_t>          m_plaintext;
	required_shared_ptr<uint16_t>  m_decrypted_opcodes;
>>>>>>> upstream/master

	// internal types
	struct decrypt_parameters
	{
<<<<<<< HEAD
		UINT8 xorval;
		UINT8 s7,s6,s5,s4,s3,s2,s1,s0;
	};

	// static tables
	static const UINT8 s_basetable_fd1089[0x100];
=======
		uint8_t xorval;
		uint8_t s7,s6,s5,s4,s3,s2,s1,s0;
	};

	// static tables
	static const uint8_t s_basetable_fd1089[0x100];
>>>>>>> upstream/master
	static const decrypt_parameters s_addr_params[16];
	static const decrypt_parameters s_data_params_a[16];
};


// ======================> fd1089a_device

// FD1089A variant
class fd1089a_device : public fd1089_base_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	fd1089a_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

protected:
	virtual UINT8 decode(UINT8 val, UINT8 key, bool opcode);
=======
	fd1089a_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

protected:
	virtual uint8_t decode(uint8_t val, uint8_t key, bool opcode) override;
>>>>>>> upstream/master
};


// ======================> fd1089b_device

// FD1089B variant
class fd1089b_device : public fd1089_base_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	fd1089b_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

protected:
	virtual UINT8 decode(UINT8 val, UINT8 key, bool opcode);
};


#endif
=======
	fd1089b_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

protected:
	virtual uint8_t decode(uint8_t val, uint8_t key, bool opcode) override;
};


#endif // MAME_MACHINE_FD1089_H
>>>>>>> upstream/master
