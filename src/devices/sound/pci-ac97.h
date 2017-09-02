// license:BSD-3-Clause
// copyright-holders:Olivier Galibert
<<<<<<< HEAD
#ifndef PCI_AC97_H
#define PCI_AC97_H
=======
#ifndef MAME_SOUND_PCI_AC97_H
#define MAME_SOUND_PCI_AC97_H

#pragma once
>>>>>>> upstream/master

#include "machine/pci.h"

#define MCFG_AC97_ADD(_tag, _main_id, _revision, _subdevice_id) \
<<<<<<< HEAD
	MCFG_PCI_DEVICE_ADD(_tag, AC97, _main_id, _revision, 0x040300, _subdevice_id)

class ac97_device : public pci_device {
public:
	ac97_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

protected:
	virtual void device_start();
	virtual void device_reset();
=======
		MCFG_PCI_DEVICE_ADD(_tag, AC97, _main_id, _revision, 0x040300, _subdevice_id)

class ac97_device : public pci_device {
public:
	ac97_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

protected:
	virtual void device_start() override;
	virtual void device_reset() override;
>>>>>>> upstream/master

private:
	DECLARE_ADDRESS_MAP(native_audio_mixer_map, 32);
	DECLARE_ADDRESS_MAP(native_audio_bus_mastering_map, 32);
	DECLARE_ADDRESS_MAP(mixer_map, 32);
	DECLARE_ADDRESS_MAP(bus_mastering_map, 32);
};

<<<<<<< HEAD
extern const device_type AC97;

#endif
=======
DECLARE_DEVICE_TYPE(AC97, ac97_device)

#endif // MAME_SOUND_PCI_AC97_H
>>>>>>> upstream/master
