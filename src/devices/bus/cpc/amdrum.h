// license:BSD-3-Clause
// copyright-holders:Barry Rodewald
/*
 * amdrum.h
 *
 *  Created on: 23/08/2014
 *
 *  Cheetah Marketing Amdrum
 *
 *  I/O FFxx - 8-bit unsigned DAC, write only  (Ferranti ZN428E-8)
 *  Lower 8 address bits are not decoded.
 *
 */

<<<<<<< HEAD
#ifndef AMDRUM_H_
#define AMDRUM_H_

#include "emu.h"
=======
#ifndef MAME_BUS_CPC_AMDRUM_H
#define MAME_BUS_CPC_AMDRUM_H

#pragma once

>>>>>>> upstream/master
#include "cpcexp.h"
#include "sound/dac.h"

class cpc_amdrum_device  : public device_t,
							public device_cpc_expansion_card_interface
{
public:
	// construction/destruction
<<<<<<< HEAD
	cpc_amdrum_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// optional information overrides
	virtual machine_config_constructor device_mconfig_additions() const;

	DECLARE_WRITE8_MEMBER(dac_w);
protected:
	// device-level overrides
	virtual void device_start();
	virtual void device_reset();
=======
	cpc_amdrum_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	DECLARE_WRITE8_MEMBER(dac_w);

protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;

	// optional information overrides
	virtual void device_add_mconfig(machine_config &config) override;
>>>>>>> upstream/master

private:
	cpc_expansion_slot_device *m_slot;

<<<<<<< HEAD
	required_device<dac_device> m_dac;
};

// device type definition
extern const device_type CPC_AMDRUM;


#endif /* AMDRUM_H_ */
=======
	required_device<dac_byte_interface> m_dac;
};

// device type definition
DECLARE_DEVICE_TYPE(CPC_AMDRUM, cpc_amdrum_device)


#endif // MAME_BUS_CPC_AMDRUM_H
>>>>>>> upstream/master
