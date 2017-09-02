// license:BSD-3-Clause
// copyright-holders:Miodrag Milanovic
/***************************************************************************

    video/cirrus.h

    Cirrus SVGA card emulation (preliminary)

***************************************************************************/

<<<<<<< HEAD
#ifndef CIRRUS_H
#define CIRRUS_H

#include "bus/lpci/pci.h"

// ======================> cirrus_device

class cirrus_device : public device_t,
						public pci_device_interface
{
public:
		// construction/destruction
	cirrus_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	virtual UINT32 pci_read(pci_bus_device *pcibus, int function, int offset, UINT32 mem_mask);
	virtual void pci_write(pci_bus_device *pcibus, int function, int offset, UINT32 data, UINT32 mem_mask);
=======
#ifndef MAME_BUS_LPCI_CIRRUS_H
#define MAME_BUS_LPCI_CIRRUS_H

#pragma once

#include "bus/lpci/pci.h"

// ======================> pci_cirrus_svga_device

class pci_cirrus_svga_device : public device_t, public pci_device_interface
{
public:
		// construction/destruction
	pci_cirrus_svga_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual uint32_t pci_read(pci_bus_device *pcibus, int function, int offset, uint32_t mem_mask) override;
	virtual void pci_write(pci_bus_device *pcibus, int function, int offset, uint32_t data, uint32_t mem_mask) override;
>>>>>>> upstream/master

	DECLARE_WRITE8_MEMBER( cirrus_42E8_w );

protected:
	// device-level overrides
<<<<<<< HEAD
	virtual void device_start();
	virtual void device_reset();
private:
=======
	virtual void device_start() override;
	virtual void device_reset() override;
>>>>>>> upstream/master
};


// device type definition
<<<<<<< HEAD
extern const device_type CIRRUS;

#endif /* CIRRUS_H */
=======
DECLARE_DEVICE_TYPE(PCI_CIRRUS_SVGA, pci_cirrus_svga_device)

#endif // MAME_BUS_LPCI_CIRRUS_H
>>>>>>> upstream/master
