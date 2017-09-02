// license:BSD-3-Clause
// copyright-holders:Miodrag Milanovic
/***************************************************************************

    pci.h

    PCI bus

***************************************************************************/

<<<<<<< HEAD
#ifndef PCI_H
#define PCI_H
=======
#ifndef MAME_BUS_LPCI_PCI_H
#define MAME_BUS_LPCI_PCI_H

#pragma once
>>>>>>> upstream/master

//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************
class pci_bus_device;

// ======================> pci_device_interface

class pci_device_interface :  public device_slot_card_interface
{
public:
	// construction/destruction
<<<<<<< HEAD
	pci_device_interface(const machine_config &mconfig, device_t &device);
	virtual ~pci_device_interface();

	virtual UINT32 pci_read(pci_bus_device *pcibus, int function, int offset, UINT32 mem_mask) = 0;
	virtual void pci_write(pci_bus_device *pcibus, int function, int offset, UINT32 data, UINT32 mem_mask) = 0;
private:
};

class pci_connector: public device_t,
						public device_slot_interface
{
public:
	pci_connector(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
	virtual ~pci_connector();
=======
	virtual ~pci_device_interface();

	virtual uint32_t pci_read(pci_bus_device *pcibus, int function, int offset, uint32_t mem_mask) = 0;
	virtual void pci_write(pci_bus_device *pcibus, int function, int offset, uint32_t data, uint32_t mem_mask) = 0;

protected:
	pci_device_interface(const machine_config &mconfig, device_t &device);
};

class pci_connector_device : public device_t,
						public device_slot_interface
{
public:
	pci_connector_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
	virtual ~pci_connector_device();
>>>>>>> upstream/master

	pci_device_interface *get_device();

protected:
<<<<<<< HEAD
	virtual void device_start();
};

extern const device_type PCI_CONNECTOR;
=======
	virtual void device_start() override;
};

DECLARE_DEVICE_TYPE(PCI_CONNECTOR, pci_connector_device)
>>>>>>> upstream/master

// ======================> pci_bus_device

class pci_bus_device :  public device_t
{
public:
	// construction/destruction
<<<<<<< HEAD
	pci_bus_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
=======
	pci_bus_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
>>>>>>> upstream/master

	DECLARE_READ32_MEMBER( read );
	DECLARE_WRITE32_MEMBER( write );

	DECLARE_READ64_MEMBER( read_64be );
	DECLARE_WRITE64_MEMBER( write_64be );

	void set_busnum(int busnum) { m_busnum = busnum; }
	void set_father(const char *father) { m_father = father; }
	void set_device(int num, const char *tag) {
		m_devtag[num] = tag; }

	pci_bus_device *pci_search_bustree(int busnum, int devicenum, pci_bus_device *pcibus);
	void add_sibling(pci_bus_device *sibling, int busnum);

protected:
	// device-level overrides
<<<<<<< HEAD
	virtual void device_start();
	virtual void device_reset();
	virtual void device_post_load();

private:
	UINT8               m_busnum;
=======
	virtual void device_start() override;
	virtual void device_reset() override;
	virtual void device_post_load() override;

private:
	uint8_t               m_busnum;
>>>>>>> upstream/master

	const char *        m_devtag[32];
	pci_device_interface *m_device[32];

	const char *        m_father;
	pci_bus_device *    m_siblings[8];
<<<<<<< HEAD
	UINT8               m_siblings_busnum[8];
	int                 m_siblings_count;

	offs_t              m_address;
	INT8                m_devicenum; // device number we are addressing
	INT8                m_busnumber; // pci bus number we are addressing
=======
	uint8_t               m_siblings_busnum[8];
	int                 m_siblings_count;

	offs_t              m_address;
	int8_t                m_devicenum; // device number we are addressing
	int8_t                m_busnumber; // pci bus number we are addressing
>>>>>>> upstream/master
	pci_bus_device *    m_busnumaddr; // pci bus we are addressing
};

// device type definition
<<<<<<< HEAD
extern const device_type PCI_BUS;
=======
DECLARE_DEVICE_TYPE(PCI_BUS, pci_bus_device)
>>>>>>> upstream/master


/***************************************************************************
    DEVICE CONFIGURATION MACROS
***************************************************************************/

#define MCFG_PCI_BUS_ADD(_tag, _busnum) \
	MCFG_DEVICE_ADD(_tag, PCI_BUS, 0) \
	downcast<pci_bus_device *>(device)->set_busnum(_busnum);
#define MCFG_PCI_BUS_DEVICE(_tag, _slot_intf, _def_slot, _fixed) \
	MCFG_DEVICE_ADD(_tag, PCI_CONNECTOR, 0) \
	MCFG_DEVICE_SLOT_INTERFACE(_slot_intf, _def_slot, _fixed)

#define MCFG_PCI_BUS_SIBLING(_father_tag) \
	downcast<pci_bus_device *>(device)->set_father(_father_tag);


<<<<<<< HEAD
#endif /* PCI_H */
=======
#endif // MAME_BUS_LPCI_PCI_H
>>>>>>> upstream/master
