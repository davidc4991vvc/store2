// license:BSD-3-Clause
// copyright-holders:Mariusz Wojcieszek
/***************************************************************************

    Akiko

    Used in the Amiga CD32

    - CD-ROM controller
    - Builtin 1KB NVRAM
    - Chunky to planar converter

***************************************************************************/

<<<<<<< HEAD
#pragma once

#ifndef __AKIKO_H__
#define __AKIKO_H__

#include "emu.h"
=======
#ifndef MAME_MACHINE_AKIKO_H
#define MAME_MACHINE_AKIKO_H

#pragma once

>>>>>>> upstream/master
#include "cdrom.h"
#include "sound/cdda.h"


//**************************************************************************
//  INTERFACE CONFIGURATION MACROS
//**************************************************************************

<<<<<<< HEAD
#define MCFG_AKIKO_ADD(_tag, _cputag) \
	MCFG_DEVICE_ADD(_tag, AKIKO, 0) \
	akiko_device::set_cputag(*device, _cputag);
=======
#define MCFG_AKIKO_ADD(_tag) \
	MCFG_DEVICE_ADD(_tag, AKIKO, 0)

#define MCFG_AKIKO_MEM_READ_CB(_devcb) \
	devcb = &akiko_device::set_mem_r_callback(*device, DEVCB_##_devcb);

#define MCFG_AKIKO_MEM_WRITE_CB(_devcb) \
	devcb = &akiko_device::set_mem_w_callback(*device, DEVCB_##_devcb);

#define MCFG_AKIKO_INT_CB(_devcb) \
	devcb = &akiko_device::set_int_w_callback(*device, DEVCB_##_devcb);
>>>>>>> upstream/master

#define MCFG_AKIKO_SCL_HANDLER(_devcb) \
	devcb = &akiko_device::set_scl_handler(*device, DEVCB_##_devcb);

#define MCFG_AKIKO_SDA_READ_HANDLER(_devcb) \
	devcb = &akiko_device::set_sda_read_handler(*device, DEVCB_##_devcb);

#define MCFG_AKIKO_SDA_WRITE_HANDLER(_devcb) \
	devcb = &akiko_device::set_sda_write_handler(*device, DEVCB_##_devcb);


//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

// ======================> akiko_device

class akiko_device : public device_t
{
public:
<<<<<<< HEAD
	akiko_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
	~akiko_device() {}

	// callbacks
	template<class _Object> static devcb_base &set_scl_handler(device_t &device, _Object object)
		{ return downcast<akiko_device &>(device).m_scl_w.set_callback(object); }

	template<class _Object> static devcb_base &set_sda_read_handler(device_t &device, _Object object)
		{ return downcast<akiko_device &>(device).m_sda_r.set_callback(object); }

	template<class _Object> static devcb_base &set_sda_write_handler(device_t &device, _Object object)
		{ return downcast<akiko_device &>(device).m_sda_w.set_callback(object); }
=======
	akiko_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// callbacks
	template <class Object> static devcb_base &set_mem_r_callback(device_t &device, Object &&cb)
	{ return downcast<akiko_device &>(device).m_mem_r.set_callback(std::forward<Object>(cb)); }

	template <class Object> static devcb_base &set_mem_w_callback(device_t &device, Object &&cb)
	{ return downcast<akiko_device &>(device).m_mem_w.set_callback(std::forward<Object>(cb)); }

	template <class Object> static devcb_base &set_int_w_callback(device_t &device, Object &&cb)
	{ return downcast<akiko_device &>(device).m_int_w.set_callback(std::forward<Object>(cb)); }

	template <class Object> static devcb_base &set_scl_handler(device_t &device, Object &&cb)
	{ return downcast<akiko_device &>(device).m_scl_w.set_callback(std::forward<Object>(cb)); }

	template <class Object> static devcb_base &set_sda_read_handler(device_t &device, Object &&cb)
	{ return downcast<akiko_device &>(device).m_sda_r.set_callback(std::forward<Object>(cb)); }

	template <class Object> static devcb_base &set_sda_write_handler(device_t &device, Object &&cb)
	{ return downcast<akiko_device &>(device).m_sda_w.set_callback(std::forward<Object>(cb)); }
>>>>>>> upstream/master

	DECLARE_READ32_MEMBER( read );
	DECLARE_WRITE32_MEMBER( write );

<<<<<<< HEAD
	// inline configuration
	static void set_cputag(device_t &device, const char *tag);

protected:
	// device-level overrides
	virtual void device_start();
	virtual void device_stop();
	virtual void device_reset();
	virtual machine_config_constructor device_mconfig_additions() const;

private:
	// 1X CDROM sector time in msec (300KBps)
	static const int CD_SECTOR_TIME = (1000/((150*1024)/2048));

	// internal state
	address_space *m_space;

	// chunky to planar converter
	UINT32 m_c2p_input_buffer[8];
	UINT32 m_c2p_output_buffer[8];
	UINT32 m_c2p_input_index;
	UINT32 m_c2p_output_index;
=======
protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_stop() override;
	virtual void device_reset() override;
	virtual void device_add_mconfig(machine_config &config) override;

private:
	// 1X CDROM sector time in msec (300KBps)
	static constexpr int CD_SECTOR_TIME = (1000/((150*1024)/2048));

	// chunky to planar converter
	uint32_t m_c2p_input_buffer[8];
	uint32_t m_c2p_output_buffer[8];
	uint32_t m_c2p_input_index;
	uint32_t m_c2p_output_index;
>>>>>>> upstream/master

	// i2c bus
	int m_i2c_scl_out;
	int m_i2c_scl_dir;
	int m_i2c_sda_out;
	int m_i2c_sda_dir;

	// cdrom
<<<<<<< HEAD
	UINT32 m_cdrom_status[2];
	UINT32 m_cdrom_address[2];
	UINT32 m_cdrom_track_index;
	UINT32 m_cdrom_lba_start;
	UINT32 m_cdrom_lba_end;
	UINT32 m_cdrom_lba_cur;
	UINT16 m_cdrom_readmask;
	UINT16 m_cdrom_readreqmask;
	UINT32 m_cdrom_dmacontrol;
	UINT32 m_cdrom_numtracks;
	UINT8 m_cdrom_speed;
	UINT8 m_cdrom_cmd_start;
	UINT8 m_cdrom_cmd_end;
	UINT8 m_cdrom_cmd_resp;
=======
	uint32_t m_cdrom_status[2];
	uint32_t m_cdrom_address[2];
	uint32_t m_cdrom_track_index;
	uint32_t m_cdrom_lba_start;
	uint32_t m_cdrom_lba_end;
	uint32_t m_cdrom_lba_cur;
	uint16_t m_cdrom_readmask;
	uint16_t m_cdrom_readreqmask;
	uint32_t m_cdrom_dmacontrol;
	uint32_t m_cdrom_numtracks;
	uint8_t m_cdrom_speed;
	uint8_t m_cdrom_cmd_start;
	uint8_t m_cdrom_cmd_end;
	uint8_t m_cdrom_cmd_resp;
>>>>>>> upstream/master

	cdda_device *m_cdda;
	cdrom_file *m_cdrom;

<<<<<<< HEAD
	UINT8 *m_cdrom_toc;
=======
	std::unique_ptr<uint8_t[]> m_cdrom_toc;
>>>>>>> upstream/master

	emu_timer *m_dma_timer;
	emu_timer *m_frame_timer;

	int m_cdrom_is_device;

<<<<<<< HEAD
	void nvram_write(UINT32 data);
	UINT32 nvram_read();

	void c2p_write(UINT32 data);
	UINT32 c2p_read();

	void cdda_stop();
	void cdda_play(UINT32 lba, UINT32 num_blocks);
	void cdda_pause(int pause);
	UINT8 cdda_getstatus(UINT32 *lba);
	void set_cd_status(UINT32 status);
=======
	void nvram_write(uint32_t data);
	uint32_t nvram_read();

	uint8_t mem_r8(offs_t offset);
	void mem_w8(offs_t offset, uint8_t data);

	void c2p_write(uint32_t data);
	uint32_t c2p_read();

	void cdda_stop();
	void cdda_play(uint32_t lba, uint32_t num_blocks);
	void cdda_pause(int pause);
	uint8_t cdda_getstatus(uint32_t *lba);
	void set_cd_status(uint32_t status);
>>>>>>> upstream/master

	TIMER_CALLBACK_MEMBER( frame_proc );
	TIMER_CALLBACK_MEMBER( dma_proc );

	void start_dma();
<<<<<<< HEAD
	void setup_response( int len, UINT8 *r1 );
=======
	void setup_response( int len, uint8_t *r1 );
>>>>>>> upstream/master

	TIMER_CALLBACK_MEMBER( cd_delayed_cmd );
	void update_cdrom();

<<<<<<< HEAD
	// i2c interface
	devcb_write_line m_scl_w;
	devcb_read_line m_sda_r;
	devcb_write_line m_sda_w;

	const char *m_cputag;
};

// device type definition
extern const device_type AKIKO;

#endif
=======
	// interface
	devcb_read16 m_mem_r;
	devcb_write16 m_mem_w;
	devcb_write_line m_int_w;
	devcb_write_line m_scl_w;
	devcb_read_line m_sda_r;
	devcb_write_line m_sda_w;
};

// device type definition
DECLARE_DEVICE_TYPE(AKIKO, akiko_device)

#endif // MAME_MACHINE_AKIKO_H
>>>>>>> upstream/master
