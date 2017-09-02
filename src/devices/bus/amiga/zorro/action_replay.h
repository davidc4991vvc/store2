// license:GPL-2.0+
// copyright-holders:Dirk Best
/***************************************************************************

    Datel Action Replay

    Freezer cartridge for Amiga 500 and Amiga 2000

***************************************************************************/

<<<<<<< HEAD
#pragma once

#ifndef __ACTION_REPLAY_H__
#define __ACTION_REPLAY_H__

#include "emu.h"
=======
#ifndef MAME_BUS_AMIGA_ZORRO_ACTION_REPLAY_H
#define MAME_BUS_AMIGA_ZORRO_ACTION_REPLAY_H

#pragma once

>>>>>>> upstream/master
#include "zorro.h"


//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

// ======================> action_replay_device

class action_replay_device : public device_t, public device_exp_card_interface
{
public:
<<<<<<< HEAD
	// construction/destruction
	action_replay_device(const machine_config &mconfig, device_type type, const char *tag,
		device_t *owner, UINT32 clock, const char *name, const char *shortname);

	// optional information overrides
	virtual ioport_constructor device_input_ports() const;
=======
	// optional information overrides
	virtual ioport_constructor device_input_ports() const override;
>>>>>>> upstream/master

	DECLARE_INPUT_CHANGED_MEMBER( freeze );

protected:
<<<<<<< HEAD
	// device-level overrides
	virtual void device_start();
	virtual void device_reset();
=======
	// construction/destruction
	action_replay_device(const machine_config &mconfig, device_type type, const char *tag, device_t *owner, uint32_t clock);

	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;
>>>>>>> upstream/master

private:
	required_ioport m_button;
};

class action_replay_mk1_device : public action_replay_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	action_replay_mk1_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// optional information overrides
	virtual const rom_entry *device_rom_region() const;
=======
	action_replay_mk1_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// optional information overrides
	virtual const tiny_rom_entry *device_rom_region() const override;
>>>>>>> upstream/master
};

class action_replay_mk2_device : public action_replay_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	action_replay_mk2_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// optional information overrides
	virtual const rom_entry *device_rom_region() const;
=======
	action_replay_mk2_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// optional information overrides
	virtual const tiny_rom_entry *device_rom_region() const override;
>>>>>>> upstream/master
};

class action_replay_mk3_device : public action_replay_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	action_replay_mk3_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// optional information overrides
	virtual const rom_entry *device_rom_region() const;
};

// device type definition
extern const device_type ACTION_REPLAY_MK1;
extern const device_type ACTION_REPLAY_MK2;
extern const device_type ACTION_REPLAY_MK3;

#endif
=======
	action_replay_mk3_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// optional information overrides
	virtual const tiny_rom_entry *device_rom_region() const override;
};

// device type definition
DECLARE_DEVICE_TYPE(ACTION_REPLAY_MK1, action_replay_mk1_device)
DECLARE_DEVICE_TYPE(ACTION_REPLAY_MK2, action_replay_mk2_device)
DECLARE_DEVICE_TYPE(ACTION_REPLAY_MK3, action_replay_mk3_device)

#endif // MAME_BUS_AMIGA_ZORRO_ACTION_REPLAY_H
>>>>>>> upstream/master
