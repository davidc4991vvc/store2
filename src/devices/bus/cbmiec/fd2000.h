// license:BSD-3-Clause
// copyright-holders:Curt Coder
/**********************************************************************

    CMD FD-2000/FD-4000 disk drive emulation

**********************************************************************/

<<<<<<< HEAD
#pragma once

#ifndef __FD2000__
#define __FD2000__

#include "emu.h"
=======
#ifndef MAME_BUS_CBMIEC_FD2000_H
#define MAME_BUS_CBMIEC_FD2000_H

#pragma once

>>>>>>> upstream/master
#include "cbmiec.h"
#include "cpu/m6502/m65c02.h"
#include "formats/d81_dsk.h"
#include "machine/6522via.h"
#include "machine/upd765.h"



//**************************************************************************
//  MACROS / CONSTANTS
//**************************************************************************

#define FD2000_TAG          "fd2000"



//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

// ======================> fd2000_device

class fd2000_device :  public device_t,
						public device_cbm_iec_interface
{
public:
	// construction/destruction
<<<<<<< HEAD
	fd2000_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
	fd2000_device(const machine_config &mconfig, device_type type, const char *name, const char *tag, device_t *owner, UINT32 clock, UINT32 variant, const char *shortname, const char *source);

	enum
	{
		TYPE_FD2000,
		TYPE_FD4000
	};

	// optional information overrides
	virtual const rom_entry *device_rom_region() const;
	virtual machine_config_constructor device_mconfig_additions() const;
=======
	fd2000_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
>>>>>>> upstream/master

	DECLARE_READ8_MEMBER( via_pa_r );
	DECLARE_WRITE8_MEMBER( via_pa_w );
	DECLARE_READ8_MEMBER( via_pb_r );
	DECLARE_WRITE8_MEMBER( via_pb_w );

	//DECLARE_FLOPPY_FORMATS( floppy_formats );

protected:
<<<<<<< HEAD
	// device-level overrides
	virtual void device_start();
	virtual void device_reset();

	// device_cbm_iec_interface overrides
	void cbm_iec_srq(int state);
	void cbm_iec_atn(int state);
	void cbm_iec_data(int state);
	void cbm_iec_reset(int state);
=======
	fd2000_device(const machine_config &mconfig, device_type type, const char *tag, device_t *owner, uint32_t clock);

	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;

	// optional information overrides
	virtual const tiny_rom_entry *device_rom_region() const override;
	virtual void device_add_mconfig(machine_config &config) override;

	// device_cbm_iec_interface overrides
	void cbm_iec_srq(int state) override;
	void cbm_iec_atn(int state) override;
	void cbm_iec_data(int state) override;
	void cbm_iec_reset(int state) override;
>>>>>>> upstream/master

	required_device<m65c02_device> m_maincpu;
	required_device<upd765_family_device> m_fdc;
	required_device<floppy_connector> m_floppy0;
<<<<<<< HEAD

	int m_variant;
=======
>>>>>>> upstream/master
};


// ======================> fd4000_device

class fd4000_device :  public fd2000_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	fd4000_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
=======
	fd4000_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

protected:
	virtual const tiny_rom_entry *device_rom_region() const override;
	virtual void device_add_mconfig(machine_config &config) override;
>>>>>>> upstream/master
};


// device type definition
<<<<<<< HEAD
extern const device_type FD2000;
extern const device_type FD4000;



#endif
=======
DECLARE_DEVICE_TYPE(FD2000, fd2000_device)
DECLARE_DEVICE_TYPE(FD4000, fd4000_device)


#endif // MAME_BUS_CBMIEC_FD2000_H
>>>>>>> upstream/master
