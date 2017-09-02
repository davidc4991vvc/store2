// license:BSD-3-Clause
// copyright-holders:Curt Coder
/**********************************************************************

    COMX-35 Serial/Parallel Printer Card emulation

**********************************************************************/

<<<<<<< HEAD
#pragma once

#ifndef __COMX_PRN__
#define __COMX_PRN__

#include "emu.h"
=======
#ifndef MAME_BUS_COMX35_PRINTER_H
#define MAME_BUS_COMX35_PRINTER_H

#pragma once

>>>>>>> upstream/master
#include "exp.h"
#include "machine/buffer.h"
#include "bus/centronics/ctronics.h"



//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

// ======================> comx_prn_device

<<<<<<< HEAD
class comx_prn_device : public device_t,
	public device_comx_expansion_card_interface
{
public:
	// construction/destruction
	comx_prn_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// optional information overrides
	virtual const rom_entry *device_rom_region() const;
	virtual machine_config_constructor device_mconfig_additions() const;

protected:
	// device-level overrides
	virtual void device_start();
	virtual void device_reset();

	// device_comx_expansion_card_interface overrides
	virtual UINT8 comx_mrd_r(address_space &space, offs_t offset, int *extrom);
	virtual UINT8 comx_io_r(address_space &space, offs_t offset);
	virtual void comx_io_w(address_space &space, offs_t offset, UINT8 data);
=======
class comx_prn_device : public device_t, public device_comx_expansion_card_interface
{
public:
	// construction/destruction
	comx_prn_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;

	// optional information overrides
	virtual const tiny_rom_entry *device_rom_region() const override;
	virtual void device_add_mconfig(machine_config &config) override;

	// device_comx_expansion_card_interface overrides
	virtual uint8_t comx_mrd_r(address_space &space, offs_t offset, int *extrom) override;
	virtual uint8_t comx_io_r(address_space &space, offs_t offset) override;
	virtual void comx_io_w(address_space &space, offs_t offset, uint8_t data) override;
>>>>>>> upstream/master

private:
	required_device<centronics_device> m_centronics;
	required_device<output_latch_device> m_cent_data_out;
	required_device<input_buffer_device> m_cent_status_in;
	required_memory_region m_rom;
};


// device type definition
<<<<<<< HEAD
extern const device_type COMX_PRN;


#endif
=======
DECLARE_DEVICE_TYPE(COMX_PRN, comx_prn_device)


#endif // MAME_BUS_COMX35_PRINTER_H
>>>>>>> upstream/master
