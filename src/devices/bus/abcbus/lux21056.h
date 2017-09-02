// license:BSD-3-Clause
// copyright-holders:Curt Coder
/**********************************************************************

    Luxor 55 21056-00 Xebec Interface Host Adapter emulation

*********************************************************************/

<<<<<<< HEAD
#pragma once

#ifndef __LUXOR_55_21056__
#define __LUXOR_55_21056__

#include "emu.h"
=======
#ifndef MAME_BUS_ABCBUS_LUX21056_H
#define MAME_BUS_ABCBUS_LUX21056_H

#pragma once

>>>>>>> upstream/master
#include "abcbus.h"
#include "bus/scsi/scsi.h"
#include "cpu/z80/z80.h"
#include "cpu/z80/z80daisy.h"
#include "machine/z80dma.h"



//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

// ======================> luxor_55_21056_device

class luxor_55_21056_device :  public device_t,
								public device_abcbus_card_interface
{
public:
	// construction/destruction
<<<<<<< HEAD
	luxor_55_21056_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// optional information overrides
	virtual const rom_entry *device_rom_region() const;
	virtual machine_config_constructor device_mconfig_additions() const;
	virtual ioport_constructor device_input_ports() const;
=======
	luxor_55_21056_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
>>>>>>> upstream/master

	DECLARE_READ8_MEMBER( sasi_status_r );
	DECLARE_WRITE8_MEMBER( stat_w );
	DECLARE_READ8_MEMBER( out_r );
	DECLARE_WRITE8_MEMBER( inp_w );
	DECLARE_READ8_MEMBER( sasi_data_r );
	DECLARE_WRITE8_MEMBER( sasi_data_w );
	DECLARE_READ8_MEMBER( rdy_reset_r );
	DECLARE_WRITE8_MEMBER( rdy_reset_w );
	DECLARE_READ8_MEMBER( sasi_sel_r );
	DECLARE_WRITE8_MEMBER( sasi_sel_w );
	DECLARE_READ8_MEMBER( sasi_rst_r );
	DECLARE_WRITE8_MEMBER( sasi_rst_w );

<<<<<<< HEAD
=======
protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;

	// optional information overrides
	virtual const tiny_rom_entry *device_rom_region() const override;
	virtual void device_add_mconfig(machine_config &config) override;
	virtual ioport_constructor device_input_ports() const override;

	// device_abcbus_interface overrides
	virtual void abcbus_cs(uint8_t data) override;
	virtual uint8_t abcbus_inp() override;
	virtual void abcbus_out(uint8_t data) override;
	virtual uint8_t abcbus_stat() override;
	virtual void abcbus_c1(uint8_t data) override;
	virtual void abcbus_c3(uint8_t data) override;

private:
	void set_rdy(int state);

>>>>>>> upstream/master
	DECLARE_READ8_MEMBER( memory_read_byte );
	DECLARE_WRITE8_MEMBER( memory_write_byte );
	DECLARE_READ8_MEMBER( io_read_byte );
	DECLARE_WRITE8_MEMBER( io_write_byte );

	DECLARE_WRITE_LINE_MEMBER( write_sasi_req );
	DECLARE_WRITE_LINE_MEMBER( write_sasi_io );
	DECLARE_WRITE_LINE_MEMBER( write_sasi_cd );
	DECLARE_WRITE_LINE_MEMBER( write_sasi_msg );
	DECLARE_WRITE_LINE_MEMBER( write_sasi_bsy );

<<<<<<< HEAD
protected:
	// device-level overrides
	virtual void device_start();
	virtual void device_reset();

	// device_abcbus_interface overrides
	virtual void abcbus_cs(UINT8 data);
	virtual UINT8 abcbus_inp();
	virtual void abcbus_out(UINT8 data);
	virtual UINT8 abcbus_stat();
	virtual void abcbus_c1(UINT8 data);
	virtual void abcbus_c3(UINT8 data);

private:
	void set_rdy(int state);

	required_device<cpu_device> m_maincpu;
	required_device<z80dma_device> m_dma;
	required_device<SCSI_PORT_DEVICE> m_sasibus;
=======
	required_device<cpu_device> m_maincpu;
	required_device<z80dma_device> m_dma;
	required_device<scsi_port_device> m_sasibus;
>>>>>>> upstream/master
	required_device<output_latch_device> m_sasi_data_out;
	required_device<input_buffer_device> m_sasi_data_in;
	required_ioport m_s1;

	int m_cs;
	int m_rdy;
	int m_sasi_req;
	int m_sasi_io;
	int m_sasi_cd;
	int m_sasi_msg;
	int m_sasi_bsy;

<<<<<<< HEAD
	UINT8 m_inp;
	UINT8 m_out;
	UINT8 m_stat;
	UINT8 m_sasi_data;
=======
	uint8_t m_inp;
	uint8_t m_out;
	uint8_t m_stat;
	uint8_t m_sasi_data;
>>>>>>> upstream/master
};


// device type definition
<<<<<<< HEAD
extern const device_type LUXOR_55_21056;



#endif
=======
DECLARE_DEVICE_TYPE(LUXOR_55_21056, luxor_55_21056_device)

#endif // MAME_BUS_ABCBUS_LUX21056_H
>>>>>>> upstream/master
