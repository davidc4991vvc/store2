// license:BSD-3-Clause
// copyright-holders:Curt Coder
/**********************************************************************

    Morrow Designs MM65K16S memory board emulation

**********************************************************************/

<<<<<<< HEAD
#pragma once

#ifndef __S100_MM65K16S__
#define __S100_MM65K16S__

#include "emu.h"
=======
#ifndef MAME_BUS_S100_MM65K16S_H
#define MAME_BUS_S100_MM65K16S_H

#pragma once

>>>>>>> upstream/master
#include "s100.h"



//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

// ======================> s100_mm65k16s_device

class s100_mm65k16s_device : public device_t,
								public device_s100_card_interface
{
public:
	// construction/destruction
<<<<<<< HEAD
	s100_mm65k16s_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// optional information overrides
	virtual const rom_entry *device_rom_region() const;
	virtual ioport_constructor device_input_ports() const;

protected:
	// device-level overrides
	virtual void device_start();
	virtual void device_reset();

	// device_s100_card_interface overrides
	virtual UINT8 s100_smemr_r(address_space &space, offs_t offset);
	virtual void s100_mwrt_w(address_space &space, offs_t offset, UINT8 data);
	virtual void s100_phantom_w(int state);

private:
	optional_shared_ptr<UINT8> m_ram;
=======
	s100_mm65k16s_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// optional information overrides
	virtual const tiny_rom_entry *device_rom_region() const override;
	virtual ioport_constructor device_input_ports() const override;

protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;

	// device_s100_card_interface overrides
	virtual uint8_t s100_smemr_r(address_space &space, offs_t offset) override;
	virtual void s100_mwrt_w(address_space &space, offs_t offset, uint8_t data) override;
	virtual void s100_phantom_w(int state) override;

private:
	optional_shared_ptr<uint8_t> m_ram;
>>>>>>> upstream/master
};


// device type definition
<<<<<<< HEAD
extern const device_type S100_MM65K16S;


#endif
=======
DECLARE_DEVICE_TYPE(S100_MM65K16S, s100_mm65k16s_device)

#endif // MAME_BUS_S100_MM65K16S_H
>>>>>>> upstream/master
