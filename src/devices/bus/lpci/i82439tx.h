// license:BSD-3-Clause
// copyright-holders:Miodrag Milanovic
/***************************************************************************

    Intel 82439TX System Controller (MTXC)

    Part of the Intel 430TX chipset

***************************************************************************/

<<<<<<< HEAD
#ifndef __I82439TX_H__
#define __I82439TX_H__
=======
#ifndef MAME_BUS_LPCI_I82439TX_H
#define MAME_BUS_LPCI_I82439TX_H

#pragma once
>>>>>>> upstream/master

#include "pci.h"
#include "northbridge.h"

#define MCFG_I82439TX_CPU( _tag ) \
	i82439tx_device::static_set_cpu(*device, _tag);

#define MCFG_I82439TX_REGION( _tag ) \
	i82439tx_device::static_set_region(*device, _tag);

// ======================> i82439tx_device

<<<<<<< HEAD
class i82439tx_device :  public northbridge_device,
	public pci_device_interface
{
public:
	// construction/destruction
	i82439tx_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
=======
class i82439tx_device : public northbridge_device, public pci_device_interface
{
public:
	// construction/destruction
	i82439tx_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
>>>>>>> upstream/master

	static void static_set_cpu(device_t &device, const char *tag) { dynamic_cast<i82439tx_device &>(device).m_cpu_tag = tag; }
	static void static_set_region(device_t &device, const char *tag) { dynamic_cast<i82439tx_device &>(device).m_region_tag = tag; }

<<<<<<< HEAD
	virtual UINT32 pci_read(pci_bus_device *pcibus, int function, int offset, UINT32 mem_mask);
	virtual void pci_write(pci_bus_device *pcibus, int function, int offset, UINT32 data, UINT32 mem_mask);

protected:
	// device-level overrides
	virtual void device_start();
	virtual void device_reset();

	void i82439tx_configure_memory(UINT8 val, offs_t begin, offs_t end);
=======
	virtual uint32_t pci_read(pci_bus_device *pcibus, int function, int offset, uint32_t mem_mask) override;
	virtual void pci_write(pci_bus_device *pcibus, int function, int offset, uint32_t data, uint32_t mem_mask) override;

protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;

	void i82439tx_configure_memory(uint8_t val, offs_t begin, offs_t end);
>>>>>>> upstream/master

private:
	const char *m_cpu_tag;
	const char *m_region_tag;

	address_space *m_space;
<<<<<<< HEAD
	UINT8 *m_rom;

	UINT32 m_regs[8];
	UINT32 m_bios_ram[0x40000 / 4];
};

// device type definition
extern const device_type I82439TX;

#endif /* __I82439TX_H__ */
=======
	uint8_t *m_rom;

	uint32_t m_regs[8];
	uint32_t m_bios_ram[0x40000 / 4];
};

// device type definition
DECLARE_DEVICE_TYPE(I82439TX, i82439tx_device)

#endif // MAME_BUS_LPCI_I82439TX_H
>>>>>>> upstream/master
