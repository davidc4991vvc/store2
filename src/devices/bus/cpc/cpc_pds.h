// license:BSD-3-Clause
// copyright-holders:Barry Rodewald
/*
 * cpc_pds.h  --  CPC interface hardware for the Programmers Development System
 *
 *  Created on: 10/02/2014
 *
 *  Contains a Z80 PIO used to communicate with PC-side hardware (8-bit ISA card containing an 8255 PPI),
 *  connected via a 16-pin cable.  Although it would seem that the C64 has a different cable that directly
 *  interfaces with the user port.
 *
 *  The Z80 PIO is mapped to the CPC at:
 *  FBEC Z80 PIO Port A Data (8bit data to/from PC)
 *  FBED Z80 PIO Port B Data (handshake to/from PC)
 *  FBEE Z80 PIO Port A Control
 *  FBEF Z80 PIO Port B Control
 *
 *  More info: http://cpcwiki.eu/index.php/PDS_development_system
 *
 *  TODO: Come up with some way to connect two instances of MESS, one running the PC software, the other
 *  running the target side
 */

<<<<<<< HEAD
#ifndef CPC_PDS_H_
#define CPC_PDS_H_

#include "emu.h"
=======
#ifndef MAME_BUS_CPC_CPC_PDS_H
#define MAME_BUS_CPC_CPC_PDS_H

#pragma once

>>>>>>> upstream/master
#include "cpcexp.h"
#include "machine/z80pio.h"

class cpc_pds_device  : public device_t,
						public device_cpc_expansion_card_interface
{
public:
	// construction/destruction
<<<<<<< HEAD
	cpc_pds_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// optional information overrides
	virtual machine_config_constructor device_mconfig_additions() const;
=======
	cpc_pds_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
>>>>>>> upstream/master

	DECLARE_READ8_MEMBER(pio_r);
	DECLARE_WRITE8_MEMBER(pio_w);

protected:
	// device-level overrides
<<<<<<< HEAD
	virtual void device_start();
	virtual void device_reset();
=======
	virtual void device_start() override;
	virtual void device_reset() override;

	// optional information overrides
	virtual void device_add_mconfig(machine_config &config) override;
>>>>>>> upstream/master

private:
	cpc_expansion_slot_device *m_slot;

	required_device<z80pio_device> m_pio;
};

// device type definition
<<<<<<< HEAD
extern const device_type CPC_PDS;

#endif /* CPC_PDS_H_ */
=======
DECLARE_DEVICE_TYPE(CPC_PDS, cpc_pds_device)

#endif // MAME_BUS_CPC_CPC_PDS_H
>>>>>>> upstream/master
