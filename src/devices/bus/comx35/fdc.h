// license:BSD-3-Clause
// copyright-holders:Curt Coder
/**********************************************************************

    COMX-35 Disk Controller Card emulation

**********************************************************************/

<<<<<<< HEAD
#pragma once

#ifndef __COMX_FD__
#define __COMX_FD__

#include "emu.h"
=======
#ifndef MAME_BUS_COMX35_FD_H
#define MAME_BUS_COMX35_FD_H

#pragma once

>>>>>>> upstream/master
#include "exp.h"
#include "formats/comx35_dsk.h"
#include "machine/wd_fdc.h"



//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

// ======================> comx_fd_device

class comx_fd_device : public device_t,
						public device_comx_expansion_card_interface
{
public:
	// construction/destruction
<<<<<<< HEAD
	comx_fd_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// optional information overrides
	virtual const rom_entry *device_rom_region() const;
	virtual machine_config_constructor device_mconfig_additions() const;

	DECLARE_FLOPPY_FORMATS( floppy_formats );

protected:
	// device-level overrides
	virtual void device_start();
	virtual void device_reset();

	// device_comx_expansion_card_interface overrides
	virtual int comx_ef4_r();
	virtual void comx_q_w(int state);
	virtual UINT8 comx_mrd_r(address_space &space, offs_t offset, int *extrom);
	virtual UINT8 comx_io_r(address_space &space, offs_t offset);
	virtual void comx_io_w(address_space &space, offs_t offset, UINT8 data);

private:
	// internal state
	required_device<wd1770_t> m_fdc;
=======
	comx_fd_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;

	// optional information overrides
	virtual const tiny_rom_entry *device_rom_region() const override;
	virtual void device_add_mconfig(machine_config &config) override;

	// device_comx_expansion_card_interface overrides
	virtual int comx_ef4_r() override;
	virtual void comx_q_w(int state) override;
	virtual uint8_t comx_mrd_r(address_space &space, offs_t offset, int *extrom) override;
	virtual uint8_t comx_io_r(address_space &space, offs_t offset) override;
	virtual void comx_io_w(address_space &space, offs_t offset, uint8_t data) override;

private:
	DECLARE_FLOPPY_FORMATS( floppy_formats );

	// internal state
	required_device<wd1770_device> m_fdc;
>>>>>>> upstream/master
	required_device<floppy_connector> m_floppy0;
	required_device<floppy_connector> m_floppy1;
	required_memory_region m_rom;

	// floppy state
	int m_q;                // FDC register select
	int m_addr;             // FDC address
	int m_disb;             // data request disable
};


// device type definition
<<<<<<< HEAD
extern const device_type COMX_FD;


#endif
=======
DECLARE_DEVICE_TYPE(COMX_FD, comx_fd_device)


#endif // MAME_BUS_COMX35_FD_H
>>>>>>> upstream/master
