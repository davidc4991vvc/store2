// license:BSD-3-Clause
// copyright-holders:Curt Coder
/**********************************************************************

    Commodore D9060/D9090 Hard Disk Drive emulation

**********************************************************************/

<<<<<<< HEAD
#pragma once

#ifndef __D9060__
#define __D9060__

#include "emu.h"
=======
#ifndef MAME_BUS_IEEE488_D9060_H
#define MAME_BUS_IEEE488_D9060_H

#pragma once

>>>>>>> upstream/master
#include "ieee488.h"
#include "cpu/m6502/m6502.h"
#include "machine/6522via.h"
#include "machine/mos6530n.h"
#include "bus/scsi/scsi.h"



//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************


<<<<<<< HEAD
// ======================> d9060_base_t

class d9060_base_t :  public device_t,
						public device_ieee488_interface
{
public:
=======
// ======================> d9060_device_base

class d9060_device_base : public device_t, public device_ieee488_interface
{
protected:
>>>>>>> upstream/master
	enum
	{
		TYPE_9060,
		TYPE_9090
	};

	// construction/destruction
<<<<<<< HEAD
	d9060_base_t(const machine_config &mconfig, device_type type, const char *name, const char *tag, device_t *owner, UINT32 clock, UINT32 variant, const char *shortname, const char *source);

	// optional information overrides
	virtual const rom_entry *device_rom_region() const;
	virtual machine_config_constructor device_mconfig_additions() const;
	virtual ioport_constructor device_input_ports() const;

	// not really public
=======
	d9060_device_base(const machine_config &mconfig, device_type type, const char *tag, device_t *owner, uint32_t clock, uint32_t variant);

	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;

	// optional information overrides
	virtual const tiny_rom_entry *device_rom_region() const override;
	virtual void device_add_mconfig(machine_config &config) override;
	virtual ioport_constructor device_input_ports() const override;

	// device_ieee488_interface overrides
	void ieee488_atn(int state) override;
	void ieee488_ifc(int state) override;

private:
	inline void update_ieee_signals();

>>>>>>> upstream/master
	DECLARE_READ8_MEMBER( dio_r );
	DECLARE_WRITE8_MEMBER( dio_w );
	DECLARE_READ8_MEMBER( riot1_pa_r );
	DECLARE_WRITE8_MEMBER( riot1_pa_w );
	DECLARE_READ8_MEMBER( riot1_pb_r );
	DECLARE_WRITE8_MEMBER( riot1_pb_w );
<<<<<<< HEAD
	DECLARE_READ8_MEMBER( via_pb_r );
=======
>>>>>>> upstream/master
	DECLARE_WRITE8_MEMBER( via_pb_w );
	DECLARE_WRITE_LINE_MEMBER( ack_w );
	DECLARE_WRITE_LINE_MEMBER( enable_w );
	DECLARE_WRITE8_MEMBER( scsi_data_w );

<<<<<<< HEAD
protected:
	// device-level overrides
	virtual void device_start();
	virtual void device_reset();

	// device_ieee488_interface overrides
	void ieee488_atn(int state);
	void ieee488_ifc(int state);

private:
	inline void update_ieee_signals();

	required_device<cpu_device> m_maincpu;
	required_device<cpu_device> m_hdccpu;
	required_device<mos6532_t> m_riot0;
	required_device<mos6532_t> m_riot1;
	required_device<via6522_device> m_via;
	required_device<SCSI_PORT_DEVICE> m_sasibus;
=======
	required_device<cpu_device> m_maincpu;
	required_device<cpu_device> m_hdccpu;
	required_device<mos6532_new_device> m_riot0;
	required_device<mos6532_new_device> m_riot1;
	required_device<via6522_device> m_via;
	required_device<scsi_port_device> m_sasibus;
>>>>>>> upstream/master
	required_device<output_latch_device> m_sasi_data_out;
	required_ioport m_address;

	// IEEE-488 bus
	int m_rfdo;                         // not ready for data output
	int m_daco;                         // not data accepted output
	int m_atna;                         // attention acknowledge
	int m_ifc;

	// SASI bus
	int m_enable;
<<<<<<< HEAD
	UINT8 m_data;
=======
	uint8_t m_data;
>>>>>>> upstream/master

	int m_variant;
};


<<<<<<< HEAD
// ======================> d9060_t

class d9060_t :  public d9060_base_t
{
public:
	// construction/destruction
	d9060_t(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
};


// ======================> d9090_t

class d9090_t :  public d9060_base_t
{
public:
	// construction/destruction
	d9090_t(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
=======
// ======================> d9060_device

class d9060_device : public d9060_device_base
{
public:
	// construction/destruction
	d9060_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
};


// ======================> d9090_device

class d9090_device : public d9060_device_base
{
public:
	// construction/destruction
	d9090_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
>>>>>>> upstream/master
};


// device type definition
<<<<<<< HEAD
extern const device_type D9060;
extern const device_type D9090;



#endif
=======
DECLARE_DEVICE_TYPE(D9060, d9060_device)
DECLARE_DEVICE_TYPE(D9090, d9090_device)

#endif // MAME_BUS_IEEE488_D9060_H
>>>>>>> upstream/master
