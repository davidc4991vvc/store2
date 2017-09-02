// license:BSD-3-Clause
// copyright-holders:Curt Coder
/**********************************************************************

    COMX-35 80-Column Card emulation

**********************************************************************/

<<<<<<< HEAD
#pragma once

#ifndef __COMX_CLM__
#define __COMX_CLM__

#include "emu.h"
=======
#ifndef MAME_BUS_COMX35_CLM_H
#define MAME_BUS_COMX35_CLM_H

#pragma once

>>>>>>> upstream/master
#include "exp.h"
#include "video/mc6845.h"



//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

// ======================> comx_clm_device

class comx_clm_device : public device_t,
<<<<<<< HEAD
						public device_comx_expansion_card_interface
{
public:
	// construction/destruction
	comx_clm_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// optional information overrides
	virtual const rom_entry *device_rom_region() const;
	virtual machine_config_constructor device_mconfig_additions() const;

	// not really public
	MC6845_UPDATE_ROW( crtc_update_row );

protected:
	// device-level overrides
	virtual void device_start();
	virtual void device_reset();

	// device_comx_expansion_card_interface overrides
	virtual int comx_ef4_r();
	virtual UINT8 comx_mrd_r(address_space &space, offs_t offset, int *extrom);
	virtual void comx_mwr_w(address_space &space, offs_t offset, UINT8 data);

private:
=======
						public device_comx_expansion_card_interface,
						public device_gfx_interface
{
public:
	// construction/destruction
	comx_clm_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;

	// optional information overrides
	virtual const tiny_rom_entry *device_rom_region() const override;
	virtual void device_add_mconfig(machine_config &config) override;

	// device_comx_expansion_card_interface overrides
	virtual int comx_ef4_r() override;
	virtual uint8_t comx_mrd_r(address_space &space, offs_t offset, int *extrom) override;
	virtual void comx_mwr_w(address_space &space, offs_t offset, uint8_t data) override;

private:
	MC6845_UPDATE_ROW( crtc_update_row );

>>>>>>> upstream/master
	required_device<mc6845_device> m_crtc;
	required_device<palette_device> m_palette;
	required_memory_region m_rom;
	required_memory_region m_char_rom;
<<<<<<< HEAD
	optional_shared_ptr<UINT8> m_video_ram;
=======
	optional_shared_ptr<uint8_t> m_video_ram;
>>>>>>> upstream/master
};


// device type definition
<<<<<<< HEAD
extern const device_type COMX_CLM;


#endif
=======
DECLARE_DEVICE_TYPE(COMX_CLM, comx_clm_device)


#endif // MAME_BUS_COMX35_CLM_H
>>>>>>> upstream/master
