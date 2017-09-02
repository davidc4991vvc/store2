// license:BSD-3-Clause
// copyright-holders:Curt Coder
/**********************************************************************

    Acorn FileStore E01/E01S network hard disk emulation

**********************************************************************/

<<<<<<< HEAD
#pragma once

#ifndef __E01__
#define __E01__
=======
#ifndef MAME_BUS_ECONET_E01_H
#define MAME_BUS_ECONET_E01_H

#pragma once
>>>>>>> upstream/master

#include "econet.h"
#include "bus/centronics/ctronics.h"
#include "bus/scsi/scsi.h"
#include "cpu/m6502/m65c02.h"
#include "machine/6522via.h"
#include "machine/buffer.h"
#include "machine/latch.h"
#include "machine/mc146818.h"
#include "machine/mc6854.h"
#include "machine/ram.h"
#include "machine/wd_fdc.h"
<<<<<<< HEAD

class e01_device : public device_t,
=======
#include "formats/afs_dsk.h"

class econet_e01_device : public device_t,
>>>>>>> upstream/master
	public device_econet_interface
{
public:
	// construction/destruction
<<<<<<< HEAD
	e01_device(const machine_config &mconfig, device_type type, const char *name, const char *tag, device_t *owner, UINT32 clock, const char *shortname, const char *source);
	e01_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	enum
	{
		TYPE_E01 = 0,
		TYPE_E01S
	};
=======
	econet_e01_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
>>>>>>> upstream/master

	DECLARE_READ8_MEMBER( read );
	DECLARE_WRITE8_MEMBER( write );
	DECLARE_READ8_MEMBER( ram_select_r );
	DECLARE_WRITE8_MEMBER( floppy_w );
	DECLARE_READ8_MEMBER( network_irq_disable_r );
	DECLARE_WRITE8_MEMBER( network_irq_disable_w );
	DECLARE_READ8_MEMBER( network_irq_enable_r );
	DECLARE_WRITE8_MEMBER( network_irq_enable_w );
	DECLARE_READ8_MEMBER( hdc_data_r );
	DECLARE_WRITE8_MEMBER( hdc_data_w );
<<<<<<< HEAD
	DECLARE_READ8_MEMBER( hdc_status_r );
=======
>>>>>>> upstream/master
	DECLARE_WRITE8_MEMBER( hdc_select_w );
	DECLARE_WRITE8_MEMBER( hdc_irq_enable_w );
	DECLARE_READ8_MEMBER( rtc_address_r );
	DECLARE_WRITE8_MEMBER( rtc_address_w );
	DECLARE_READ8_MEMBER( rtc_data_r );
	DECLARE_WRITE8_MEMBER( rtc_data_w );
<<<<<<< HEAD
=======

protected:
	enum
	{
		TYPE_E01 = 0,
		TYPE_E01S
	};

	econet_e01_device(const machine_config &mconfig, device_type type, const char *tag, device_t *owner, uint32_t clock, int variant);

	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;
	virtual void device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr) override;

	// optional information overrides
	virtual const tiny_rom_entry *device_rom_region() const override;
	virtual void device_add_mconfig(machine_config &config) override;
	virtual ioport_constructor device_input_ports() const override;

	// device_econet_interface overrides
	virtual void econet_data(int state) override;
	virtual void econet_clk(int state) override;

private:
>>>>>>> upstream/master
	DECLARE_WRITE_LINE_MEMBER( rtc_irq_w );
	DECLARE_WRITE_LINE_MEMBER( adlc_irq_w );
	DECLARE_WRITE_LINE_MEMBER( econet_data_w );
	DECLARE_WRITE_LINE_MEMBER( via_irq_w );
	DECLARE_WRITE_LINE_MEMBER( clk_en_w );
	DECLARE_WRITE_LINE_MEMBER( fdc_irq_w );
	DECLARE_WRITE_LINE_MEMBER( fdc_drq_w );
	DECLARE_WRITE_LINE_MEMBER( scsi_bsy_w );
	DECLARE_WRITE_LINE_MEMBER( scsi_req_w );

<<<<<<< HEAD
protected:
	// device-level overrides
	virtual void device_start();
	virtual void device_reset();
	virtual void device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr);

	// optional information overrides
	virtual const rom_entry *device_rom_region() const;
	virtual machine_config_constructor device_mconfig_additions() const;
	virtual ioport_constructor device_input_ports() const;

	// device_econet_interface overrides
	virtual void econet_data(int state);
	virtual void econet_clk(int state);

	required_device<m65c02_device> m_maincpu;
	required_device<wd2793_t> m_fdc;
	required_device<mc6854_device> m_adlc;
	required_device<mc146818_device> m_rtc;
	required_device<ram_device> m_ram;
	required_device<SCSI_PORT_DEVICE> m_scsibus;
=======
	DECLARE_FLOPPY_FORMATS(floppy_formats_afs);

	required_device<m65c02_device> m_maincpu;
	required_device<wd2793_device> m_fdc;
	required_device<mc6854_device> m_adlc;
	required_device<mc146818_device> m_rtc;
	required_device<ram_device> m_ram;
	required_device<scsi_port_device> m_scsibus;
>>>>>>> upstream/master
	required_device<output_latch_device> m_scsi_data_out;
	required_device<input_buffer_device> m_scsi_data_in;
	required_device<input_buffer_device> m_scsi_ctrl_in;
	required_device<floppy_connector> m_floppy0;
	required_device<floppy_connector> m_floppy1;
	required_memory_region m_rom;
	required_device<centronics_device> m_centronics;

	inline void update_interrupts();
	inline void network_irq_enable(int enabled);
	inline void hdc_irq_enable(int enabled);

	// interrupt state
	int m_adlc_ie;
	int m_hdc_ie;
	int m_rtc_irq;
	int m_via_irq;
	int m_hdc_irq;
	int m_fdc_irq;
	bool m_fdc_drq;
	int m_adlc_irq;
	int m_clk_en;
	bool m_ram_en;

<<<<<<< HEAD
	int m_variant;
=======
	const int m_variant;
>>>>>>> upstream/master

	// timers
	emu_timer *m_clk_timer;
};


<<<<<<< HEAD
// ======================> e01s_device

class e01s_device :  public e01_device
{
public:
	// construction/destruction
	e01s_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
=======
// ======================> econet_e01s_device

class econet_e01s_device :  public econet_e01_device
{
public:
	// construction/destruction
	econet_e01s_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
>>>>>>> upstream/master
};


// device type definition
<<<<<<< HEAD
extern const device_type E01;
extern const device_type E01S;



#endif
=======
DECLARE_DEVICE_TYPE(ECONET_E01,  econet_e01_device)
DECLARE_DEVICE_TYPE(ECONET_E01S, econet_e01s_device)



#endif // MAME_BUS_ECONET_E01_H
>>>>>>> upstream/master
