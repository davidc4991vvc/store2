// license:BSD-3-Clause
// copyright-holders:Olivier Galibert
<<<<<<< HEAD
#ifndef PCI_APIC_H
#define PCI_APIC_H
=======
#ifndef MAME_MACHINE_PCI_APIC_H
#define MAME_MACHINE_PCI_APIC_H

#pragma once
>>>>>>> upstream/master

#include "pci.h"

#define MCFG_APIC_ADD(_tag, _main_id, _revision, _subdevice_id) \
	MCFG_PCI_DEVICE_ADD(_tag, APIC, _main_id, _revision, 0x0c0320, _subdevice_id)

class apic_device : public pci_device {
public:
<<<<<<< HEAD
	apic_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

protected:
	virtual void device_start();
	virtual void device_reset();
};

extern const device_type APIC;

#endif
=======
	apic_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

protected:
	virtual void device_start() override;
	virtual void device_reset() override;
};

DECLARE_DEVICE_TYPE(APIC, apic_device)

#endif // MAME_MACHINE_PCI_APIC_H
>>>>>>> upstream/master
