// license:BSD-3-Clause
// copyright-holders:David Haywood, Luca Elia
/* Serial Flash */

<<<<<<< HEAD
#pragma once

#ifndef __SERFLASH_H__
#define __SERFLASH_H__


#define FLASH_PAGE_SIZE (2048+64)




=======
#ifndef MAME_MACHINE_SERFLASH_H
#define MAME_MACHINE_SERFLASH_H

#pragma once
>>>>>>> upstream/master


//**************************************************************************
//  INTERFACE CONFIGURATION MACROS
//**************************************************************************

#define MCFG_SERFLASH_ADD(_tag) \
<<<<<<< HEAD
	MCFG_DEVICE_ADD(_tag, SERFLASH, 0)
=======
		MCFG_DEVICE_ADD(_tag, SERFLASH, 0)


>>>>>>> upstream/master
//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

<<<<<<< HEAD
class serflash_device;

typedef enum                            { STATE_IDLE = 0,   STATE_READ,     STATE_READ_ID,  STATE_READ_STATUS, STATE_BLOCK_ERASE, STATE_PAGE_PROGRAM    } flash_state_t;
//const char *m_flash_state_name[] =    { "IDLE",           "READ",         "READ_ID",      "READ_STATUS",     "BLOCK ERASE",     "PAGE PROGRAM"        };

// custom initialization for default state
typedef device_delegate<void (serflash_device &, void *, size_t)> serflash_init_delegate;


// ======================> serflash_device

class serflash_device :    public device_t,
						public device_nvram_interface
{
public:

	// construction/destruction
	serflash_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
=======

// ======================> serflash_device

class serflash_device : public device_t, public device_nvram_interface
{
public:
	// custom initialization for default state
	typedef device_delegate<void (serflash_device &, void *, size_t)> init_delegate;


	// construction/destruction
	serflash_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
>>>>>>> upstream/master

	DECLARE_READ8_MEMBER( flash_ready_r );
	DECLARE_READ8_MEMBER( flash_io_r );
	DECLARE_WRITE8_MEMBER( flash_addr_w );
	DECLARE_WRITE8_MEMBER( flash_data_w );
	DECLARE_WRITE8_MEMBER( flash_cmd_w );
	DECLARE_WRITE8_MEMBER( flash_enab_w );
<<<<<<< HEAD
	void flash_hard_reset(running_machine &machine);
=======
	void flash_hard_reset();
>>>>>>> upstream/master

	DECLARE_READ8_MEMBER(n3d_flash_r);
	DECLARE_WRITE8_MEMBER(n3d_flash_cmd_w);
	DECLARE_WRITE8_MEMBER(n3d_flash_addr_w);

protected:
<<<<<<< HEAD
	// device-level overrides
	virtual void device_start();
	virtual void device_reset();

	// device_nvram_interface overrides
	virtual void nvram_default();
	virtual void nvram_read(emu_file &file);
	virtual void nvram_write(emu_file &file);

	void flash_change_state(running_machine &machine, flash_state_t state);

	// runtime state
	size_t                      m_length;
	UINT8* m_region;
=======
	static constexpr unsigned FLASH_PAGE_SIZE = 2048+64;

	enum class flash_state_t : u8 { IDLE = 0, READ, READ_ID, READ_STATUS, BLOCK_ERASE, PAGE_PROGRAM };

	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;

	// device_nvram_interface overrides
	virtual void nvram_default() override;
	virtual void nvram_read(emu_file &file) override;
	virtual void nvram_write(emu_file &file) override;

	void flash_change_state(flash_state_t state);

	// runtime state
	size_t                      m_length;
	uint8_t* m_region;
>>>>>>> upstream/master


	flash_state_t m_flash_state;

<<<<<<< HEAD
	UINT8 m_flash_enab;

	UINT8 m_flash_cmd_seq;
	UINT32 m_flash_cmd_prev;

	UINT8 m_flash_addr_seq;
	UINT8 m_flash_read_seq;

	UINT16 m_flash_row, m_flash_col;
	int m_flash_page_addr;
	UINT16 m_flash_page_index;


	dynamic_buffer m_flashwritemap;

	UINT8 m_last_flash_cmd;

	UINT32 m_flash_addr;

	UINT8 m_flash_page_data[FLASH_PAGE_SIZE];



=======
	uint8_t m_flash_enab;

	uint8_t m_flash_cmd_seq;
	uint32_t m_flash_cmd_prev;

	uint8_t m_flash_addr_seq;
	uint8_t m_flash_read_seq;

	uint16_t m_flash_row, m_flash_col;
	int m_flash_page_addr;
	uint16_t m_flash_page_index;


	std::vector<uint8_t> m_flashwritemap;

	uint8_t m_last_flash_cmd;

	uint32_t m_flash_addr;

	uint8_t m_flash_page_data[FLASH_PAGE_SIZE];
>>>>>>> upstream/master
};


// device type definition
<<<<<<< HEAD
extern const device_type SERFLASH;


#endif
=======
DECLARE_DEVICE_TYPE(SERFLASH, serflash_device)

#endif // MAME_MACHINE_SERFLASH_H
>>>>>>> upstream/master
