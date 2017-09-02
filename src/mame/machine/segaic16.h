// license:BSD-3-Clause
// copyright-holders:Aaron Giles
/***************************************************************************

    Sega 16-bit common hardware

***************************************************************************/

<<<<<<< HEAD
#pragma once

#ifndef __SEGAIC16_H__
#define __SEGAIC16_H__
=======
#ifndef MAME_MACHINE_SEGAIC16_H
#define MAME_MACHINE_SEGAIC16_H

#pragma once
>>>>>>> upstream/master

#include "cpu/m68000/m68000.h"
#include "machine/fd1089.h"
#include "machine/fd1094.h"
<<<<<<< HEAD
=======
#include "screen.h"
>>>>>>> upstream/master


//**************************************************************************
//  INTERFACE CONFIGURATION MACROS
//**************************************************************************

#define MCFG_SEGA_315_5195_MAPPER_ADD(_tag, _cputag, _class, _mapper, _read, _write) \
	MCFG_DEVICE_ADD(_tag, SEGA_315_5195_MEM_MAPPER, 0) \
<<<<<<< HEAD
	sega_315_5195_mapper_device::static_set_cputag(*device, _cputag); \
	sega_315_5195_mapper_device::static_set_mapper(*device, sega_315_5195_mapper_device::mapper_delegate(&_class::_mapper, #_class "::" #_mapper, NULL, (_class *)0)); \
	sega_315_5195_mapper_device::static_set_sound_readwrite(*device, sega_315_5195_mapper_device::sound_read_delegate(&_class::_read, #_class "::" #_read, NULL, (_class *)0), sega_315_5195_mapper_device::sound_write_delegate(&_class::_write, #_class "::" #_write, NULL, (_class *)0));
=======
	sega_315_5195_mapper_device::static_set_cputag(*device, "^" _cputag); \
	sega_315_5195_mapper_device::static_set_mapper(*device, sega_315_5195_mapper_device::mapper_delegate(&_class::_mapper, #_class "::" #_mapper, nullptr, (_class *)nullptr)); \
	sega_315_5195_mapper_device::static_set_sound_readwrite(*device, sega_315_5195_mapper_device::sound_read_delegate(&_class::_read, #_class "::" #_read, nullptr, (_class *)nullptr), sega_315_5195_mapper_device::sound_write_delegate(&_class::_write, #_class "::" #_write, nullptr, (_class *)nullptr));
>>>>>>> upstream/master

#define MCFG_SEGA_315_5248_MULTIPLIER_ADD(_tag) \
	MCFG_DEVICE_ADD(_tag, SEGA_315_5248_MULTIPLIER, 0)

#define MCFG_SEGA_315_5249_DIVIDER_ADD(_tag) \
	MCFG_DEVICE_ADD(_tag, SEGA_315_5249_DIVIDER, 0)

#define MCFG_SEGA_315_5250_COMPARE_TIMER_ADD(_tag) \
	MCFG_DEVICE_ADD(_tag, SEGA_315_5250_COMPARE_TIMER, 0)
#define MCFG_SEGA_315_5250_TIMER_ACK(_class, _func) \
<<<<<<< HEAD
	sega_315_5250_compare_timer_device::static_set_timer_ack(*device, sega_315_5250_compare_timer_device::timer_ack_delegate(&_class::_func, #_class "::" #_func, NULL, (_class *)0));
#define MCFG_SEGA_315_5250_SOUND_WRITE(_class, _func) \
	sega_315_5250_compare_timer_device::static_set_sound_write(*device, sega_315_5250_compare_timer_device::sound_write_delegate(&_class::_func, #_class "::" #_func, NULL, (_class *)0));
=======
	sega_315_5250_compare_timer_device::static_set_timer_ack(*device, sega_315_5250_compare_timer_device::timer_ack_delegate(&_class::_func, #_class "::" #_func, nullptr, (_class *)nullptr));
#define MCFG_SEGA_315_5250_SOUND_WRITE(_class, _func) \
	sega_315_5250_compare_timer_device::static_set_sound_write(*device, sega_315_5250_compare_timer_device::sound_write_delegate(&_class::_func, #_class "::" #_func, nullptr, (_class *)nullptr));
>>>>>>> upstream/master


//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************


// ======================> sega_16bit_common_base

class sega_16bit_common_base : public driver_device
{
public:
<<<<<<< HEAD
	// construction/destruction
	sega_16bit_common_base(const machine_config &mconfig, device_type type, const char *tag);

=======
>>>>>>> upstream/master
	// open bus read helpers
	DECLARE_READ16_MEMBER( open_bus_r );

	// palette helpers
	DECLARE_WRITE16_MEMBER( paletteram_w );
<<<<<<< HEAD

protected:
=======
	DECLARE_WRITE16_MEMBER( philko_paletteram_w );

protected:
	// construction/destruction
	sega_16bit_common_base(const machine_config &mconfig, device_type type, const char *tag);

>>>>>>> upstream/master
	// internal helpers
	void palette_init();

public: // -- stupid system16.c
	// memory pointers
<<<<<<< HEAD
	required_shared_ptr<UINT16> m_paletteram;
=======
	required_shared_ptr<uint16_t> m_paletteram;
>>>>>>> upstream/master
protected:

	// internal state
	bool        m_open_bus_recurse;         // flag to track recursion through open_bus_r
<<<<<<< HEAD
	UINT32      m_palette_entries;          // number of palette entries
	UINT8       m_palette_normal[32];       // RGB translations for normal pixels
	UINT8       m_palette_shadow[32];       // RGB translations for shadowed pixels
	UINT8       m_palette_hilight[32];      // RGB translations for hilighted pixels
=======
	uint32_t      m_palette_entries;          // number of palette entries
	uint8_t       m_palette_normal[32];       // RGB translations for normal pixels
	uint8_t       m_palette_shadow[32];       // RGB translations for shadowed pixels
	uint8_t       m_palette_hilight[32];      // RGB translations for hilighted pixels
>>>>>>> upstream/master
	required_device<screen_device> m_screen;
	required_device<palette_device> m_palette;
};


// ======================> sega_315_5195_mapper_device

class sega_315_5195_mapper_device : public device_t
{
public:
<<<<<<< HEAD
	typedef device_delegate<void (sega_315_5195_mapper_device &, UINT8)> mapper_delegate;
	typedef device_delegate<UINT8 ()> sound_read_delegate;
	typedef device_delegate<void (UINT8)> sound_write_delegate;

	// construction/destruction
	sega_315_5195_mapper_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
=======
	typedef device_delegate<void (sega_315_5195_mapper_device &, uint8_t)> mapper_delegate;
	typedef device_delegate<uint8_t ()> sound_read_delegate;
	typedef device_delegate<void (uint8_t)> sound_write_delegate;

	// construction/destruction
	sega_315_5195_mapper_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
>>>>>>> upstream/master

	// static configuration helpers
	static void static_set_cputag(device_t &device, const char *cpu);
	static void static_set_mapper(device_t &device, mapper_delegate callback);
	static void static_set_sound_readwrite(device_t &device, sound_read_delegate read, sound_write_delegate write);

	// public interface
	DECLARE_READ8_MEMBER( read );
	DECLARE_WRITE8_MEMBER( write );

	// mapping helpers
<<<<<<< HEAD
	void map_as_rom(UINT32 offset, UINT32 length, offs_t mirror, const char *bank_name, const char *decrypted_bank_name, offs_t rgnoffset, write16_delegate whandler);
	void map_as_ram(UINT32 offset, UINT32 length, offs_t mirror, const char *bank_share_name, write16_delegate whandler);
	void map_as_handler(UINT32 offset, UINT32 length, offs_t mirror, read16_delegate rhandler, write16_delegate whandler);

	// perform an explicit configuration (for bootlegs with hard-coded mappings)
	void configure_explicit(const UINT8 *map_data);

protected:
	// device-level overrides
	virtual void device_start();
	virtual void device_reset();
=======
	void map_as_rom(uint32_t offset, uint32_t length, offs_t mirror, const char *bank_name, const char *decrypted_bank_name, offs_t rgnoffset, write16_delegate whandler);
	void map_as_ram(uint32_t offset, uint32_t length, offs_t mirror, const char *bank_share_name, write16_delegate whandler);
	void map_as_handler(uint32_t offset, uint32_t length, offs_t mirror, read16_delegate rhandler, write16_delegate whandler);

	// perform an explicit configuration (for bootlegs with hard-coded mappings)
	void configure_explicit(const uint8_t *map_data);

protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;
>>>>>>> upstream/master

private:
	// internal region struct
	struct region_info
	{
		offs_t  size_mask;
		offs_t  base;
		offs_t  mirror;
		offs_t  start;
		offs_t  end;
	};

	// helper class for tracking banks mapped to ROM regions
	class decrypt_bank
	{
	public:
		// construction/destruction
		decrypt_bank();
		~decrypt_bank();

		// configuration
		void set_decrypt(fd1089_base_device *fd1089);
		void set_decrypt(fd1094_device *fd1094);
<<<<<<< HEAD
		void clear() { set(NULL, NULL, 0, 0, ~0, NULL); }
		void set(memory_bank *bank, memory_bank *decrypted_bank, offs_t start, offs_t end, offs_t rgnoffs, UINT8 *src);

		// updating
		void update();
		void reset() { m_fd1089_decrypted.clear(); if (m_fd1094_cache != NULL) m_fd1094_cache->reset(); }
=======
		void clear() { set(nullptr, nullptr, 0, 0, ~0, nullptr); }
		void set(memory_bank *bank, memory_bank *decrypted_bank, offs_t start, offs_t end, offs_t rgnoffs, uint8_t *src);

		// updating
		void update();
		void reset() { m_fd1089_decrypted.clear(); if (m_fd1094_cache != nullptr) m_fd1094_cache->reset(); }
>>>>>>> upstream/master

	private:
		// internal state
		memory_bank *           m_bank;
		memory_bank *           m_decrypted_bank;
		offs_t                  m_start;
		offs_t                  m_end;
		offs_t                  m_rgnoffs;
<<<<<<< HEAD
		UINT8 *                 m_srcptr;
		fd1089_base_device *    m_fd1089;
		std::vector<UINT16>   m_fd1089_decrypted;
		auto_pointer<fd1094_decryption_cache> m_fd1094_cache;
	};

	// internal helpers
	void compute_region(region_info &info, UINT8 index, UINT32 length, UINT32 mirror, UINT32 offset = 0);
	void update_mapping();
	void fd1094_state_change(UINT8 state);

	// configuration
	const char *                m_cputag;
=======
		uint8_t *                 m_srcptr;
		fd1089_base_device *    m_fd1089;
		std::vector<uint16_t>   m_fd1089_decrypted;
		std::unique_ptr<fd1094_decryption_cache> m_fd1094_cache;
	};

	// internal helpers
	void compute_region(region_info &info, uint8_t index, uint32_t length, uint32_t mirror, uint32_t offset = 0);
	void update_mapping();
	void fd1094_state_change(uint8_t state);

	// configuration
	required_device<m68000_device> m_cpu;
	required_memory_region      m_cpuregion;
>>>>>>> upstream/master
	mapper_delegate             m_mapper;
	sound_read_delegate         m_sound_read;
	sound_write_delegate        m_sound_write;

	// internal state
<<<<<<< HEAD
	m68000_device *             m_cpu;
	address_space *             m_space;
	address_space *             m_decrypted_space;
	UINT8                       m_regs[0x20];
	UINT8                       m_curregion;
=======
	address_space *             m_space;
	address_space *             m_decrypted_space;
	uint8_t                       m_regs[0x20];
	uint8_t                       m_curregion;
>>>>>>> upstream/master
	decrypt_bank                m_banks[8];
};


// ======================> sega_315_5248_multiplier_device

class sega_315_5248_multiplier_device : public device_t
{
public:
	// construction/destruction
<<<<<<< HEAD
	sega_315_5248_multiplier_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
=======
	sega_315_5248_multiplier_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
>>>>>>> upstream/master

	// public interface
	DECLARE_READ16_MEMBER( read );
	DECLARE_WRITE16_MEMBER( write );

protected:
	// device-level overrides
<<<<<<< HEAD
	virtual void device_start();
	virtual void device_reset();

private:
	// internal state
	UINT16                      m_regs[4];
=======
	virtual void device_start() override;
	virtual void device_reset() override;

private:
	// internal state
	uint16_t                      m_regs[4];
>>>>>>> upstream/master
};


// ======================> sega_315_5249_divider_device

class sega_315_5249_divider_device : public device_t
{
public:
	// construction/destruction
<<<<<<< HEAD
	sega_315_5249_divider_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
=======
	sega_315_5249_divider_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
>>>>>>> upstream/master

	// public interface
	DECLARE_READ16_MEMBER( read );
	DECLARE_WRITE16_MEMBER( write );

protected:
	// device-level overrides
<<<<<<< HEAD
	virtual void device_start();
	virtual void device_reset();
=======
	virtual void device_start() override;
	virtual void device_reset() override;
>>>>>>> upstream/master

private:
	// internal helpers
	void execute(int mode);

	// internal state
<<<<<<< HEAD
	UINT16                      m_regs[8];
=======
	uint16_t                      m_regs[8];
>>>>>>> upstream/master
};


// ======================> sega_315_5250_compare_timer_device

class sega_315_5250_compare_timer_device : public device_t
{
public:
<<<<<<< HEAD
	typedef device_delegate<void (UINT8)> sound_write_delegate;
	typedef device_delegate<void ()> timer_ack_delegate;

	// construction/destruction
	sega_315_5250_compare_timer_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
=======
	typedef device_delegate<void (uint8_t)> sound_write_delegate;
	typedef device_delegate<void ()> timer_ack_delegate;

	// construction/destruction
	sega_315_5250_compare_timer_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
>>>>>>> upstream/master

	// static configuration helpers
	static void static_set_timer_ack(device_t &device, timer_ack_delegate callback);
	static void static_set_sound_write(device_t &device, sound_write_delegate write);

	// public interface
	bool clock();
	DECLARE_READ16_MEMBER( read );
	DECLARE_WRITE16_MEMBER( write );

protected:
	// device-level overrides
<<<<<<< HEAD
	virtual void device_start();
	virtual void device_reset();
=======
	virtual void device_start() override;
	virtual void device_reset() override;
>>>>>>> upstream/master

private:
	// internal helpers
	void execute(bool update_history = false);
	void interrupt_ack() { if (!m_timer_ack.isnull()) m_timer_ack(); }

	// configuration
	timer_ack_delegate          m_timer_ack;
	sound_write_delegate        m_sound_write;

	// internal state
<<<<<<< HEAD
	UINT16                      m_regs[16];
	UINT16                      m_counter;
	UINT8                       m_bit;
=======
	uint16_t                      m_regs[16];
	uint16_t                      m_counter;
	uint8_t                       m_bit;
>>>>>>> upstream/master
};


// device type definition
<<<<<<< HEAD
extern const device_type SEGA_315_5195_MEM_MAPPER;
extern const device_type SEGA_315_5248_MULTIPLIER;
extern const device_type SEGA_315_5249_DIVIDER;
extern const device_type SEGA_315_5250_COMPARE_TIMER;


#endif
=======
DECLARE_DEVICE_TYPE(SEGA_315_5195_MEM_MAPPER,    sega_315_5195_mapper_device)
DECLARE_DEVICE_TYPE(SEGA_315_5248_MULTIPLIER,    sega_315_5248_multiplier_device)
DECLARE_DEVICE_TYPE(SEGA_315_5249_DIVIDER,       sega_315_5249_divider_device)
DECLARE_DEVICE_TYPE(SEGA_315_5250_COMPARE_TIMER, sega_315_5250_compare_timer_device)


#endif // MAME_MACHINE_SEGAIC16_H
>>>>>>> upstream/master
