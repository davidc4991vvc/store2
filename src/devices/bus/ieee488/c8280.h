// license:BSD-3-Clause
// copyright-holders:Curt Coder
/**********************************************************************

    Commodore 8280 Dual 8" Disk Drive emulation

**********************************************************************/

<<<<<<< HEAD
#pragma once

#ifndef __C8280__
#define __C8280__

#include "emu.h"
=======
#ifndef MAME_BUS_IEEE488_C8280_H
#define MAME_BUS_IEEE488_C8280_H

#pragma once

>>>>>>> upstream/master
#include "ieee488.h"
#include "cpu/m6502/m6502.h"
#include "formats/c8280_dsk.h"
#include "machine/mos6530n.h"
#include "machine/wd_fdc.h"



//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

<<<<<<< HEAD
// ======================> c8280_t

class c8280_t :  public device_t,
					public device_ieee488_interface
{
public:
	// construction/destruction
	c8280_t(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// optional information overrides
	virtual const rom_entry *device_rom_region() const;
	virtual machine_config_constructor device_mconfig_additions() const;
	virtual ioport_constructor device_input_ports() const;

	// not really public
	DECLARE_READ8_MEMBER( dio_r );
	DECLARE_WRITE8_MEMBER( dio_w );
	DECLARE_READ8_MEMBER( riot1_pa_r );
	DECLARE_WRITE8_MEMBER( riot1_pa_w );
	DECLARE_READ8_MEMBER( riot1_pb_r );
	DECLARE_WRITE8_MEMBER( riot1_pb_w );
	DECLARE_READ8_MEMBER( fk5_r );
	DECLARE_WRITE8_MEMBER( fk5_w );

	DECLARE_FLOPPY_FORMATS( floppy_formats );

protected:
	// device-level overrides
	virtual void device_start();
	virtual void device_reset();

	// device_ieee488_interface overrides
	void ieee488_atn(int state);
	void ieee488_ifc(int state);
=======
// ======================> c8280_device

class c8280_device : public device_t, public device_ieee488_interface
{
public:
	// construction/destruction
	c8280_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	DECLARE_READ8_MEMBER( fk5_r );
	DECLARE_WRITE8_MEMBER( fk5_w );

protected:
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
>>>>>>> upstream/master

private:
	inline void update_ieee_signals();

<<<<<<< HEAD
	required_device<cpu_device> m_maincpu;
	required_device<cpu_device> m_fdccpu;
	required_device<mos6532_t> m_riot0;
	required_device<mos6532_t> m_riot1;
	required_device<fd1797_t> m_fdc;
=======
	DECLARE_READ8_MEMBER( dio_r );
	DECLARE_WRITE8_MEMBER( dio_w );
	DECLARE_READ8_MEMBER( riot1_pa_r );
	DECLARE_WRITE8_MEMBER( riot1_pa_w );
	DECLARE_READ8_MEMBER( riot1_pb_r );
	DECLARE_WRITE8_MEMBER( riot1_pb_w );

	DECLARE_FLOPPY_FORMATS( floppy_formats );

	required_device<cpu_device> m_maincpu;
	required_device<cpu_device> m_fdccpu;
	required_device<mos6532_new_device> m_riot0;
	required_device<mos6532_new_device> m_riot1;
	required_device<fd1797_device> m_fdc;
>>>>>>> upstream/master
	required_device<floppy_connector> m_floppy0;
	required_device<floppy_connector> m_floppy1;
	required_ioport m_address;
	floppy_image_device *m_floppy;

	// IEEE-488 bus
	int m_rfdo;                         // not ready for data output
	int m_daco;                         // not data accepted output
	int m_atna;                         // attention acknowledge
	int m_ifc;

<<<<<<< HEAD
	UINT8 m_fk5;
=======
	uint8_t m_fk5;
>>>>>>> upstream/master
};


// device type definition
<<<<<<< HEAD
extern const device_type C8280;



#endif
=======
DECLARE_DEVICE_TYPE(C8280, c8280_device)


#endif // MAME_BUS_IEEE488_C8280_H
>>>>>>> upstream/master
