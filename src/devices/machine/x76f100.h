// license:BSD-3-Clause
// copyright-holders:smf
/*
 * x76f100.h
 *
 * Secure SerialFlash
 *
 */

<<<<<<< HEAD
#pragma once

#ifndef __X76F100_H__
#define __X76F100_H__

#include "emu.h"

#define MCFG_X76F100_ADD( _tag ) \
	MCFG_DEVICE_ADD( _tag, X76F100, 0 )

class x76f100_device : public device_t,
	public device_nvram_interface
{
public:
	// construction/destruction
	x76f100_device( const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock );
=======
#ifndef MAME_MACHINE_X76F100_H
#define MAME_MACHINE_X76F100_H

#pragma once


#define MCFG_X76F100_ADD( tag ) \
		MCFG_DEVICE_ADD( (tag), X76F100, 0 )

class x76f100_device : public device_t, public device_nvram_interface
{
public:
	// construction/destruction
	x76f100_device( const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock );
>>>>>>> upstream/master

	DECLARE_WRITE_LINE_MEMBER( write_cs );
	DECLARE_WRITE_LINE_MEMBER( write_rst );
	DECLARE_WRITE_LINE_MEMBER( write_scl );
	DECLARE_WRITE_LINE_MEMBER( write_sda );
	DECLARE_READ_LINE_MEMBER( read_sda );

protected:
	// device-level overrides
<<<<<<< HEAD
	virtual void device_start();

	// device_nvram_interface overrides
	virtual void nvram_default();
	virtual void nvram_read( emu_file &file );
	virtual void nvram_write( emu_file &file );
=======
	virtual void device_start() override;

	// device_nvram_interface overrides
	virtual void nvram_default() override;
	virtual void nvram_read( emu_file &file ) override;
	virtual void nvram_write( emu_file &file ) override;
>>>>>>> upstream/master

private:
	inline void verboselog(int n_level, const char *s_fmt, ...) ATTR_PRINTF(3,4);

<<<<<<< HEAD
	UINT8 *password();
=======
	uint8_t *password();
>>>>>>> upstream/master
	void password_ok();
	int data_offset();

	enum command_t
	{
		COMMAND_WRITE = 0x80,
		COMMAND_READ = 0x81,
		COMMAND_CHANGE_WRITE_PASSWORD = 0xfc,
		COMMAND_CHANGE_READ_PASSWORD = 0xfe,
		COMMAND_ACK_PASSWORD = 0x55
	};

	enum state_t
	{
		STATE_STOP,
		STATE_RESPONSE_TO_RESET,
		STATE_LOAD_COMMAND,
		STATE_LOAD_PASSWORD,
		STATE_VERIFY_PASSWORD,
		STATE_READ_DATA,
		STATE_WRITE_DATA
	};

<<<<<<< HEAD
=======
	optional_memory_region m_region;

>>>>>>> upstream/master
	// internal state
	int m_cs;
	int m_rst;
	int m_scl;
	int m_sdaw;
	int m_sdar;
	int m_state;
	int m_shift;
	int m_bit;
	int m_byte;
	int m_command;
<<<<<<< HEAD
	UINT8 m_write_buffer[ 8 ];
	UINT8 m_response_to_reset[ 4 ];
	UINT8 m_write_password[ 8 ];
	UINT8 m_read_password[ 8 ];
	UINT8 m_data[ 112 ];
};

// device type definition
extern const device_type X76F100;

#endif
=======
	uint8_t m_write_buffer[ 8 ];
	uint8_t m_response_to_reset[ 4 ];
	uint8_t m_write_password[ 8 ];
	uint8_t m_read_password[ 8 ];
	uint8_t m_data[ 112 ];
};

// device type definition
DECLARE_DEVICE_TYPE(X76F100, x76f100_device)

#endif // MAME_MACHINE_X76F100_H
>>>>>>> upstream/master
