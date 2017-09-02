// license:BSD-3-Clause
// copyright-holders:Curt Coder
/**********************************************************************

    Commodore Magic Voice cartridge emulation

**********************************************************************/

<<<<<<< HEAD
#pragma once

#ifndef __MAGIC_VOICE__
#define __MAGIC_VOICE__

#include "emu.h"
#include "machine/40105.h"
#include "machine/6525tpi.h"
#include "exp.h"
=======
#ifndef MAME_BUS_C64_MAGIC_VOICE_H
#define MAME_BUS_C64_MAGIC_VOICE_H

#pragma once

#include "exp.h"
#include "machine/40105.h"
#include "machine/6525tpi.h"
>>>>>>> upstream/master
#include "sound/t6721a.h"



//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

// ======================> c64_magic_voice_cartridge_device

class c64_magic_voice_cartridge_device : public device_t,
											public device_c64_expansion_card_interface
{
public:
	// construction/destruction
<<<<<<< HEAD
	c64_magic_voice_cartridge_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// optional information overrides
	virtual machine_config_constructor device_mconfig_additions() const;
=======
	c64_magic_voice_cartridge_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;

	// optional information overrides
	virtual void device_add_mconfig(machine_config &config) override;

	// device_c64_expansion_card_interface overrides
	virtual uint8_t c64_cd_r(address_space &space, offs_t offset, uint8_t data, int sphi2, int ba, int roml, int romh, int io1, int io2) override;
	virtual void c64_cd_w(address_space &space, offs_t offset, uint8_t data, int sphi2, int ba, int roml, int romh, int io1, int io2) override;
	virtual int c64_game_r(offs_t offset, int sphi2, int ba, int rw) override;

private:
	offs_t get_offset(offs_t offset);
>>>>>>> upstream/master

	DECLARE_WRITE_LINE_MEMBER( tpi_irq_w );
	DECLARE_READ8_MEMBER( tpi_pa_r );
	DECLARE_WRITE8_MEMBER( tpi_pa_w );
	DECLARE_READ8_MEMBER( tpi_pb_r );
	DECLARE_WRITE8_MEMBER( tpi_pb_w );
<<<<<<< HEAD
	DECLARE_READ8_MEMBER( tpi_pc_r );
	DECLARE_WRITE8_MEMBER( tpi_pc_w );
=======
>>>>>>> upstream/master
	DECLARE_WRITE_LINE_MEMBER( tpi_ca_w );
	DECLARE_WRITE_LINE_MEMBER( tpi_cb_w );

	DECLARE_WRITE_LINE_MEMBER( phi2_w );
	DECLARE_WRITE_LINE_MEMBER( dtrd_w );
	DECLARE_WRITE_LINE_MEMBER( apd_w );

<<<<<<< HEAD
protected:
	// device-level overrides
	virtual void device_start();
	virtual void device_reset();

	// device_c64_expansion_card_interface overrides
	virtual UINT8 c64_cd_r(address_space &space, offs_t offset, UINT8 data, int sphi2, int ba, int roml, int romh, int io1, int io2);
	virtual void c64_cd_w(address_space &space, offs_t offset, UINT8 data, int sphi2, int ba, int roml, int romh, int io1, int io2);
	virtual int c64_game_r(offs_t offset, int sphi2, int ba, int rw);

private:
	offs_t get_offset(offs_t offset);

=======
>>>>>>> upstream/master
	required_device<t6721a_device> m_vslsi;
	required_device<tpi6525_device> m_tpi;
	required_device<cmos_40105_device> m_fifo;
	required_device<c64_expansion_slot_device> m_exp;

<<<<<<< HEAD
	UINT16 m_ca;
	UINT8 m_tpi_pb;
	int m_tpi_pc6;
	UINT8 m_pd;
=======
	uint16_t m_ca;
	uint8_t m_tpi_pb;
	int m_tpi_pc6;
	uint8_t m_pd;
>>>>>>> upstream/master
};


// device type definition
<<<<<<< HEAD
extern const device_type C64_MAGIC_VOICE;



#endif
=======
DECLARE_DEVICE_TYPE(C64_MAGIC_VOICE, c64_magic_voice_cartridge_device)


#endif // MAME_BUS_C64_MAGIC_VOICE_H
>>>>>>> upstream/master
