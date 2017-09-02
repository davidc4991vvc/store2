// license:BSD-3-Clause
// copyright-holders:Curt Coder
/**********************************************************************

    Commodore SFX Sound Expander cartridge emulation

**********************************************************************/

<<<<<<< HEAD
#pragma once

#ifndef __SFX_SOUND_EXPANDER__
#define __SFX_SOUND_EXPANDER__

#include "emu.h"
=======
#ifndef MAME_BUS_C64_SFX_SOUND_EXPANDER_H
#define MAME_BUS_C64_SFX_SOUND_EXPANDER_H

#pragma once

>>>>>>> upstream/master
#include "exp.h"
#include "sound/3526intf.h"



//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

// ======================> c64_sfx_sound_expander_cartridge_device

class c64_sfx_sound_expander_cartridge_device : public device_t,
												public device_c64_expansion_card_interface
{
public:
	// construction/destruction
<<<<<<< HEAD
	c64_sfx_sound_expander_cartridge_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// optional information overrides
	virtual machine_config_constructor device_mconfig_additions() const;
	virtual ioport_constructor device_input_ports() const;

	DECLARE_WRITE_LINE_MEMBER( opl_irq_w );

protected:
	// device-level overrides
	virtual void device_start();
	virtual void device_reset();

	// device_c64_expansion_card_interface overrides
	virtual UINT8 c64_cd_r(address_space &space, offs_t offset, UINT8 data, int sphi2, int ba, int roml, int romh, int io1, int io2);
	virtual void c64_cd_w(address_space &space, offs_t offset, UINT8 data, int sphi2, int ba, int roml, int romh, int io1, int io2);
	virtual int c64_game_r(offs_t offset, int sphi2, int ba, int rw);
	virtual int c64_exrom_r(offs_t offset, int sphi2, int ba, int rw);

private:
	required_device<ym3526_device> m_opl;
	required_device<c64_expansion_slot_device> m_exp;
	required_ioport m_kb0;
	required_ioport m_kb1;
	required_ioport m_kb2;
	required_ioport m_kb3;
	required_ioport m_kb4;
	required_ioport m_kb5;
	required_ioport m_kb6;
	required_ioport m_kb7;
=======
	c64_sfx_sound_expander_cartridge_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;

	// optional information overrides
	virtual void device_add_mconfig(machine_config &config) override;
	virtual ioport_constructor device_input_ports() const override;

	// device_c64_expansion_card_interface overrides
	virtual uint8_t c64_cd_r(address_space &space, offs_t offset, uint8_t data, int sphi2, int ba, int roml, int romh, int io1, int io2) override;
	virtual void c64_cd_w(address_space &space, offs_t offset, uint8_t data, int sphi2, int ba, int roml, int romh, int io1, int io2) override;
	virtual int c64_game_r(offs_t offset, int sphi2, int ba, int rw) override;
	virtual int c64_exrom_r(offs_t offset, int sphi2, int ba, int rw) override;

private:
	DECLARE_WRITE_LINE_MEMBER( opl_irq_w );

	required_device<ym3526_device> m_opl;
	required_device<c64_expansion_slot_device> m_exp;
	required_ioport_array<8> m_kb;
>>>>>>> upstream/master

	inline offs_t get_offset(offs_t offset, int rw);
};


// device type definition
<<<<<<< HEAD
extern const device_type C64_SFX_SOUND_EXPANDER;



#endif
=======
DECLARE_DEVICE_TYPE(C64_SFX_SOUND_EXPANDER, c64_sfx_sound_expander_cartridge_device)


#endif // MAME_BUS_C64_SFX_SOUND_EXPANDER_H
>>>>>>> upstream/master
