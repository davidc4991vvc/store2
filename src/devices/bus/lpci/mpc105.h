// license:BSD-3-Clause
// copyright-holders:Miodrag Milanovic
/***************************************************************************

    mpc105.h

    Motorola MPC105 PCI bridge

***************************************************************************/

<<<<<<< HEAD
#ifndef MPC105_H
#define MPC105_H
=======
#ifndef MAME_BUS_LPCI_MPC105_H
#define MAME_BUS_LPCI_MPC105_H

#pragma once
>>>>>>> upstream/master

#include "pci.h"

#define MPC105_MEMORYBANK_COUNT     8

#define MCFG_MPC105_CPU( _tag ) \
	mpc105_device::static_set_cpu(*device, _tag);

#define MCFG_MPC105_BANK_BASE_DEFAULT( bank_base_default ) \
	mpc105_device::static_set_bank_base_default(*device, bank_base_default);

// ======================> mpc105_device

class mpc105_device : public device_t,
	public pci_device_interface
{
public:
	// construction/destruction
<<<<<<< HEAD
	mpc105_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
=======
	mpc105_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
>>>>>>> upstream/master

	static void static_set_cpu(device_t &device, const char *tag) { dynamic_cast<mpc105_device &>(device).m_cpu_tag = tag; }
	static void static_set_bank_base_default(device_t &device, int bank_base_default) { dynamic_cast<mpc105_device &>(device).m_bank_base_default = bank_base_default; }

<<<<<<< HEAD
	virtual UINT32 pci_read(pci_bus_device *pcibus, int function, int offset, UINT32 mem_mask);
	virtual void pci_write(pci_bus_device *pcibus, int function, int offset, UINT32 data, UINT32 mem_mask);

protected:
	// device-level overrides
	virtual void device_start();
	virtual void device_reset();
=======
	virtual uint32_t pci_read(pci_bus_device *pcibus, int function, int offset, uint32_t mem_mask) override;
	virtual void pci_write(pci_bus_device *pcibus, int function, int offset, uint32_t data, uint32_t mem_mask) override;

protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;
>>>>>>> upstream/master

	void update_memory();

private:
	const char *m_cpu_tag;
	int m_bank_base_default;
	int m_bank_base;
<<<<<<< HEAD
	UINT8 m_bank_enable;
	UINT32 m_bank_registers[8];
=======
	uint8_t m_bank_enable;
	uint32_t m_bank_registers[8];
>>>>>>> upstream/master

	cpu_device*   m_maincpu;
};


// device type definition
<<<<<<< HEAD
extern const device_type MPC105;

#endif /* MPC105_H */
=======
DECLARE_DEVICE_TYPE(MPC105, mpc105_device)

#endif // MAME_BUS_LPCI_MPC105_H
>>>>>>> upstream/master
