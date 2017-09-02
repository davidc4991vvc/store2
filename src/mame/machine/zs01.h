// license:BSD-3-Clause
// copyright-holders:smf
/*
 * zs01.h
 *
 * Secure SerialFlash
 *
 */
<<<<<<< HEAD

#pragma once

#ifndef __ZS01_H__
#define __ZS01_H__
=======
#ifndef MAME_MACHINE_ZS01_H
#define MAME_MACHINE_ZS01_H

#pragma once

>>>>>>> upstream/master

#include "machine/ds2401.h"

#define MCFG_ZS01_ADD( _tag ) \
	MCFG_DEVICE_ADD( _tag, ZS01, 0 )
#define MCFG_ZS01_DS2401( ds2401_tag ) \
	zs01_device::static_set_ds2401_tag( *device, ds2401_tag );

class zs01_device : public device_t,
	public device_nvram_interface
{
public:
	// construction/destruction
<<<<<<< HEAD
	zs01_device( const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock );
=======
	zs01_device( const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock );
>>>>>>> upstream/master

	// inline configuration helpers
	static void static_set_ds2401_tag( device_t &device, const char *ds2401_tag ) { downcast<zs01_device &>( device ).m_ds2401_tag = ds2401_tag; }

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
	inline void ATTR_PRINTF( 3, 4 ) verboselog( int n_level, const char *s_fmt, ... );

<<<<<<< HEAD
	void decrypt( UINT8 *destination, UINT8 *source, int length, UINT8 *key, UINT8 previous_byte );
	void decrypt2( UINT8 *destination, UINT8 *source, int length, UINT8 *key, UINT8 previous_byte );
	void encrypt( UINT8 *destination, UINT8 *source, int length, UINT8 *key, UINT32 previous_byte );
	UINT16 calc_crc( UINT8 *buffer, UINT32 length );
=======
	void decrypt( uint8_t *destination, uint8_t *source, int length, uint8_t *key, uint8_t previous_byte );
	void decrypt2( uint8_t *destination, uint8_t *source, int length, uint8_t *key, uint8_t previous_byte );
	void encrypt( uint8_t *destination, uint8_t *source, int length, uint8_t *key, uint32_t previous_byte );
	uint16_t calc_crc( uint8_t *buffer, uint32_t length );
>>>>>>> upstream/master
	int data_offset();

	enum size_t
	{
		SIZE_DATA_BUFFER = 8
	};

	enum command_t
	{
		COMMAND_WRITE = 0x00,
		COMMAND_READ = 0x01
	};

	enum state_t
	{
		STATE_STOP,
		STATE_RESPONSE_TO_RESET,
		STATE_LOAD_COMMAND,
		STATE_READ_DATA
	};

	// internal state
	const char *m_ds2401_tag;
<<<<<<< HEAD
=======
	optional_memory_region m_region;
>>>>>>> upstream/master

	int m_cs;
	int m_rst;
	int m_scl;
	int m_sdaw;
	int m_sdar;
	int m_state;
	int m_shift;
	int m_bit;
	int m_byte;
<<<<<<< HEAD
	UINT8 m_write_buffer[ 12 ];
	UINT8 m_read_buffer[ 12 ];
	UINT8 m_response_key[ 8 ];
	UINT8 m_response_to_reset[ 4 ];
	UINT8 m_command_key[ 8 ];
	UINT8 m_data_key[ 8 ];
	UINT8 m_data[ 4096 ];
=======
	uint8_t m_write_buffer[ 12 ];
	uint8_t m_read_buffer[ 12 ];
	uint8_t m_response_key[ 8 ];
	uint8_t m_response_to_reset[ 4 ];
	uint8_t m_command_key[ 8 ];
	uint8_t m_data_key[ 8 ];
	uint8_t m_data[ 4096 ];
>>>>>>> upstream/master
	ds2401_device *m_ds2401;
};


// device type definition
<<<<<<< HEAD
extern const device_type ZS01;

#endif
=======
DECLARE_DEVICE_TYPE(ZS01, zs01_device)

#endif // MAME_MACHINE_ZS01_H
>>>>>>> upstream/master
