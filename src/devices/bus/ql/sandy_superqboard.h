// license:BSD-3-Clause
// copyright-holders:Curt Coder, Phill Harvey-Smith
/**********************************************************************

    Sandy SuperQBoard/SuperQMouse (with HD upgrade) emulation

**********************************************************************/

<<<<<<< HEAD
#pragma once

#ifndef __SANDY_SUPERQBOARD__
#define __SANDY_SUPERQBOARD__
=======
#ifndef MAME_BUS_QL_SANDY_SUPERQBOARD_H
#define MAME_BUS_QL_SANDY_SUPERQBOARD_H

#pragma once
>>>>>>> upstream/master

#include "exp.h"
#include "bus/centronics/ctronics.h"
#include "formats/ql_dsk.h"
#include "machine/wd_fdc.h"



//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

<<<<<<< HEAD
// ======================> sandy_superqboard_t

class sandy_superqboard_t : public device_t,
							public device_ql_expansion_card_interface
{
public:
	// construction/destruction
	sandy_superqboard_t(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
	sandy_superqboard_t(const machine_config &mconfig, device_type type, const char *name, const char *tag, device_t *owner, UINT32 clock, const char *shortname, const char *source, int ram_size);

	// optional information overrides
	virtual const rom_entry *device_rom_region() const;
	virtual machine_config_constructor device_mconfig_additions() const;

	WRITE_LINE_MEMBER( busy_w );

	DECLARE_FLOPPY_FORMATS( floppy_formats );
=======
// ======================> sandy_superqboard_device

class sandy_superqboard_device : public device_t, public device_ql_expansion_card_interface
{
public:
	// construction/destruction
	sandy_superqboard_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
>>>>>>> upstream/master

	DECLARE_INPUT_CHANGED_MEMBER( mouse_x_changed );
	DECLARE_INPUT_CHANGED_MEMBER( mouse_y_changed );

protected:
<<<<<<< HEAD
	// device-level overrides
	virtual void device_start();
	virtual void device_reset();

	// device_ql_expansion_card_interface overrides
	virtual UINT8 read(address_space &space, offs_t offset, UINT8 data);
	virtual void write(address_space &space, offs_t offset, UINT8 data);

private:
=======
	sandy_superqboard_device(const machine_config &mconfig, device_type type, const char *tag, device_t *owner, uint32_t clock, int ram_size);

	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;

	// optional information overrides
	virtual const tiny_rom_entry *device_rom_region() const override;
	virtual void device_add_mconfig(machine_config &config) override;

	// device_ql_expansion_card_interface overrides
	virtual uint8_t read(address_space &space, offs_t offset, uint8_t data) override;
	virtual void write(address_space &space, offs_t offset, uint8_t data) override;

private:
	WRITE_LINE_MEMBER( busy_w );

	DECLARE_FLOPPY_FORMATS( floppy_formats );

>>>>>>> upstream/master
	enum
	{
		ST_BUSY = 0x01,
		ST_MIDDLE = 0x02,
		ST_RIGHT = 0x04,
		ST_LEFT = 0x08,
		ST_Y_DIR = 0x10,
		ST_X_DIR = 0x20,
		ST_Y_INT = 0x40,
		ST_X_INT = 0x80
	};

	void check_interrupt();

<<<<<<< HEAD
	required_device<wd1772_t> m_fdc;
=======
	required_device<wd1772_device> m_fdc;
>>>>>>> upstream/master
	required_device<floppy_connector> m_floppy0;
	required_device<floppy_connector> m_floppy1;
	required_device<centronics_device> m_centronics;
	required_device<output_latch_device> m_latch;
	required_memory_region m_rom;
<<<<<<< HEAD
	optional_shared_ptr<UINT8> m_ram;
=======
	optional_shared_ptr<uint8_t> m_ram;
>>>>>>> upstream/master
	optional_ioport m_buttons;

	int m_ram_size;
	int m_fd6;
	int m_fd7;

<<<<<<< HEAD
	UINT8 m_status;
};


// ======================> sandy_superqboard_512k_t

class sandy_superqboard_512k_t :  public sandy_superqboard_t
{
public:
	// construction/destruction
	sandy_superqboard_512k_t(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
};


// ======================> sandy_superqmouse_t

class sandy_superqmouse_t :  public sandy_superqboard_t
{
public:
	// construction/destruction
	sandy_superqmouse_t(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// optional information overrides
	virtual ioport_constructor device_input_ports() const;
};


// ======================> sandy_superqmouse_512k_t

class sandy_superqmouse_512k_t :  public sandy_superqboard_t
{
public:
	// construction/destruction
	sandy_superqmouse_512k_t(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// optional information overrides
	virtual ioport_constructor device_input_ports() const;
=======
	uint8_t m_status;
};


// ======================> sandy_superqboard_512k_device

class sandy_superqboard_512k_device :  public sandy_superqboard_device
{
public:
	// construction/destruction
	sandy_superqboard_512k_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
};


// ======================> sandy_superqmouse_device

class sandy_superqmouse_device :  public sandy_superqboard_device
{
public:
	// construction/destruction
	sandy_superqmouse_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// optional information overrides
	virtual ioport_constructor device_input_ports() const override;
};


// ======================> sandy_superqmouse_512k_device

class sandy_superqmouse_512k_device :  public sandy_superqboard_device
{
public:
	// construction/destruction
	sandy_superqmouse_512k_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// optional information overrides
	virtual ioport_constructor device_input_ports() const override;
>>>>>>> upstream/master
};


// device type definition
<<<<<<< HEAD
extern const device_type SANDY_SUPERQBOARD;
extern const device_type SANDY_SUPERQBOARD_512K;
extern const device_type SANDY_SUPERQMOUSE;
extern const device_type SANDY_SUPERQMOUSE_512K;



#endif
=======
DECLARE_DEVICE_TYPE(SANDY_SUPERQBOARD,      sandy_superqboard_device)
DECLARE_DEVICE_TYPE(SANDY_SUPERQBOARD_512K, sandy_superqboard_512k_device)
DECLARE_DEVICE_TYPE(SANDY_SUPERQMOUSE,      sandy_superqmouse_device)
DECLARE_DEVICE_TYPE(SANDY_SUPERQMOUSE_512K, sandy_superqmouse_512k_device)

#endif // MAME_BUS_QL_SANDY_SUPERQBOARD_H
>>>>>>> upstream/master
