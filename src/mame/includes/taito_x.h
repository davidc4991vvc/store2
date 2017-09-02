<<<<<<< HEAD
// license:???
// copyright-holders:Richard Bush, Howie Cohen, Yochizo
#include "includes/seta.h"
=======
// license:BSD-3-Clause
// copyright-holders:Howie Cohen, Yochizo
// thanks-to:Richard Bush
#ifndef MAME_INCLUDES_TAITO_X_H
#define MAME_INCLUDES_TAITO_X_H

#pragma once

#include "includes/seta.h"
#include "machine/taitocchip.h"
>>>>>>> upstream/master

class taitox_state : public seta_state
{
public:
	taitox_state(const machine_config &mconfig, device_type type, const char *tag)
<<<<<<< HEAD
		: seta_state(mconfig, type, tag) { }
=======
		: seta_state(mconfig, type, tag),
		m_cchip(*this, "cchip")
	{ }

	optional_device<taito_cchip_device> m_cchip;
>>>>>>> upstream/master

	DECLARE_READ16_MEMBER(superman_dsw_input_r);
	DECLARE_READ16_MEMBER(daisenpu_input_r);
	DECLARE_WRITE16_MEMBER(daisenpu_input_w);
	DECLARE_WRITE16_MEMBER(kyustrkr_input_w);
	DECLARE_WRITE8_MEMBER(sound_bankswitch_w);
	DECLARE_DRIVER_INIT(kyustrkr);
	DECLARE_MACHINE_START(taitox);
	DECLARE_MACHINE_START(superman);
<<<<<<< HEAD
	DECLARE_WRITE_LINE_MEMBER(irqhandler);

	// superman c-chip
	UINT16 m_current_bank;
	UINT8 m_cc_port;
=======

	// superman c-chip
	uint16_t m_current_bank;
	uint8_t m_cc_port;
>>>>>>> upstream/master
	DECLARE_READ16_MEMBER( cchip1_ctrl_r );
	DECLARE_READ16_MEMBER( cchip1_ram_r );
	DECLARE_WRITE16_MEMBER( cchip1_ctrl_w );
	DECLARE_WRITE16_MEMBER( cchip1_bank_w );
	DECLARE_WRITE16_MEMBER( cchip1_ram_w );
};
<<<<<<< HEAD
=======

#endif // MAME_INCLUDES_TAITO_X_H
>>>>>>> upstream/master
