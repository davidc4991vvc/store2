// license:BSD-3-Clause
// copyright-holders:Barry Rodewald
/*
 * doubler.c  --  Draysoft Doubler - external cassette interface for the 464 (works on 664/6128 with external cassette?),
 *                intended for use in duplicating cassette software
 *
 * Uses only port F0E0 (may conflict with other peripherals, PPI port A is not usable while Doubler software is running)
 *
 */

<<<<<<< HEAD
#ifndef DOUBLER_H_
#define DOUBLER_H_

#include "emu.h"
=======
#ifndef MAME_BUS_CPC_DOUBLER_H
#define MAME_BUS_CPC_DOUBLER_H

#pragma once

>>>>>>> upstream/master
#include "cpcexp.h"
#include "imagedev/cassette.h"
#include "formats/tzx_cas.h"

class cpc_doubler_device  : public device_t,
						public device_cpc_expansion_card_interface
{
public:
	// construction/destruction
<<<<<<< HEAD
	cpc_doubler_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// optional information overrides
	virtual machine_config_constructor device_mconfig_additions() const;
=======
	cpc_doubler_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
>>>>>>> upstream/master

	DECLARE_READ8_MEMBER(ext_tape_r);

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

	required_device<cassette_image_device> m_tape;
};

// device type definition
<<<<<<< HEAD
extern const device_type CPC_DOUBLER;

#endif /* DOUBLER_H_ */
=======
DECLARE_DEVICE_TYPE(CPC_DOUBLER, cpc_doubler_device)

#endif // MAME_BUS_CPC_DOUBLER_H
>>>>>>> upstream/master
