// license:BSD-3-Clause
// copyright-holders:Curt Coder
/**********************************************************************

    North Star MICRO-DISK System MDS-A-D (Double Density) emulation

**********************************************************************/

<<<<<<< HEAD
#pragma once

#ifndef __S100_MDS_AD__
#define __S100_MDS_AD__

#include "emu.h"
=======
#ifndef MAME_BUS_S100_NSMDSAD_H
#define MAME_BUS_S100_NSMDSAD_H

#pragma once

>>>>>>> upstream/master
#include "s100.h"
#include "imagedev/floppy.h"



//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

// ======================> s100_mds_ad_device

class s100_mds_ad_device : public device_t,
							public device_s100_card_interface
{
public:
	// construction/destruction
<<<<<<< HEAD
	s100_mds_ad_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// optional information overrides
	virtual const rom_entry *device_rom_region() const;
	virtual machine_config_constructor device_mconfig_additions() const;

protected:
	// device-level overrides
	virtual void device_start();
	virtual void device_reset();

	// device_s100_card_interface overrides
	virtual UINT8 s100_smemr_r(address_space &space, offs_t offset);
=======
	s100_mds_ad_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;

	// optional information overrides
	virtual const tiny_rom_entry *device_rom_region() const override;
	virtual void device_add_mconfig(machine_config &config) override;

	// device_s100_card_interface overrides
	virtual uint8_t s100_smemr_r(address_space &space, offs_t offset) override;
>>>>>>> upstream/master

private:
	required_device<floppy_connector> m_floppy0;
	required_device<floppy_connector> m_floppy1;
	required_memory_region m_dsel_rom;
	required_memory_region m_dpgm_rom;
	required_memory_region m_dwe_rom;
};


// device type definition
<<<<<<< HEAD
extern const device_type S100_MDS_AD;



#endif
=======
DECLARE_DEVICE_TYPE(S100_MDS_AD, s100_mds_ad_device)

#endif // MAME_BUS_S100_NSMDSAD_H
>>>>>>> upstream/master
