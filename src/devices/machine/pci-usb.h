// license:BSD-3-Clause
// copyright-holders:Olivier Galibert
<<<<<<< HEAD
#ifndef PCI_USB_H
#define PCI_USB_H

#include "pci.h"

=======
#ifndef MAME_MACHINE_PCI_USB_H
#define MAME_MACHINE_PCI_USB_H

#pragma once

#include "pci.h"

#define MCFG_USB_OHCI_ADD(_tag, _main_id, _revision, _subdevice_id) \
	MCFG_PCI_DEVICE_ADD(_tag, USB_OHCI, _main_id, _revision, 0x0c0310, _subdevice_id)

>>>>>>> upstream/master
#define MCFG_USB_UHCI_ADD(_tag, _main_id, _revision, _subdevice_id) \
	MCFG_PCI_DEVICE_ADD(_tag, USB_UHCI, _main_id, _revision, 0x0c0300, _subdevice_id)

#define MCFG_USB_EHCI_ADD(_tag, _main_id, _revision, _subdevice_id) \
	MCFG_PCI_DEVICE_ADD(_tag, USB_EHCI, _main_id, _revision, 0x0c0320, _subdevice_id)

<<<<<<< HEAD
class usb_uhci_device : public pci_device {
public:
	usb_uhci_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

protected:
	virtual void device_start();
	virtual void device_reset();
=======
class usb_ohci_device : public pci_device {
public:
	usb_ohci_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

protected:
	virtual void device_start() override;
	virtual void device_reset() override;

private:
	DECLARE_ADDRESS_MAP(map, 32);
};

class usb_uhci_device : public pci_device {
public:
	usb_uhci_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

protected:
	virtual void device_start() override;
	virtual void device_reset() override;
>>>>>>> upstream/master

private:
	DECLARE_ADDRESS_MAP(map, 32);
};

class usb_ehci_device : public pci_device {
public:
<<<<<<< HEAD
	usb_ehci_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

protected:
	virtual void device_start();
	virtual void device_reset();
=======
	usb_ehci_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

protected:
	virtual void device_start() override;
	virtual void device_reset() override;
>>>>>>> upstream/master

private:
	DECLARE_ADDRESS_MAP(map, 32);
};

<<<<<<< HEAD
extern const device_type USB_UHCI;
extern const device_type USB_EHCI;

#endif
=======
DECLARE_DEVICE_TYPE(USB_OHCI, usb_ohci_device)
DECLARE_DEVICE_TYPE(USB_UHCI, usb_uhci_device)
DECLARE_DEVICE_TYPE(USB_EHCI, usb_ehci_device)

#endif // MAME_MACHINE_PCI_USB_H
>>>>>>> upstream/master
