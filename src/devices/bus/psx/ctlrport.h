// license:BSD-3-Clause
// copyright-holders:Carl
<<<<<<< HEAD
#pragma once

#ifndef __PSXCPORT_H__
#define __PSXCPORT_H__
=======
#ifndef MAME_BUS_PSX_CTLRPORT_H
#define MAME_BUS_PSX_CTLRPORT_H

#pragma once

>>>>>>> upstream/master

#include "memcard.h"

#define MCFG_PSX_CTRL_PORT_ADD(_tag, _slot_intf, _def_slot) \
	MCFG_DEVICE_ADD(_tag, PSX_CONTROLLER_PORT, 0) \
	MCFG_DEVICE_SLOT_INTERFACE(_slot_intf, _def_slot, false)

SLOT_INTERFACE_EXTERN(psx_controllers);

<<<<<<< HEAD
extern const device_type PSXCONTROLLERPORTS;
extern const device_type PSX_CONTROLLER_PORT;
extern const device_type PSX_STANDARD_CONTROLLER;
=======
DECLARE_DEVICE_TYPE(PSXCONTROLLERPORTS,      psxcontrollerports_device)
DECLARE_DEVICE_TYPE(PSX_CONTROLLER_PORT,     psx_controller_port_device)
DECLARE_DEVICE_TYPE(PSX_STANDARD_CONTROLLER, psx_standard_controller_device)
>>>>>>> upstream/master

class psx_controller_port_device;

class device_psx_controller_interface : public device_slot_card_interface
{
	friend class psx_multitap_device;
public:
<<<<<<< HEAD
	device_psx_controller_interface(const machine_config &mconfig, device_t &device);
=======
>>>>>>> upstream/master
	virtual ~device_psx_controller_interface();

	void clock_w(bool state) { if(!m_clock && !m_sel && state && !m_memcard) do_pad(); m_clock = state; }
	void sel_w(bool state);

	bool rx_r() { return m_rx; }
	bool ack_r() { return m_ack; }

protected:
<<<<<<< HEAD
	virtual void interface_pre_reset();
	virtual void interface_pre_start();
=======
	device_psx_controller_interface(const machine_config &mconfig, device_t &device);

	virtual void interface_pre_reset() override;
	virtual void interface_pre_start() override;
>>>>>>> upstream/master

	enum
	{
		QUERY_PAD_STATE = 0x42,
		CONFIG_MODE = 0x43
	};

private:
<<<<<<< HEAD
	virtual bool get_pad(int count, UINT8 *odata, UINT8 idata) = 0;
	virtual void do_pad();
	void ack_timer(void *ptr, int param);

	UINT8 m_odata;
	UINT8 m_idata;
=======
	virtual bool get_pad(int count, uint8_t *odata, uint8_t idata) = 0;
	virtual void do_pad();
	void ack_timer(void *ptr, int param);

	uint8_t m_odata;
	uint8_t m_idata;
>>>>>>> upstream/master
	int m_bit;
	int m_count;
	bool m_memcard;

	bool m_clock;
	bool m_sel;
	bool m_ack;
	bool m_rx;

	emu_timer *m_ack_timer;
	psx_controller_port_device *m_owner;
};

class psx_standard_controller_device :  public device_t,
										public device_psx_controller_interface
{
public:
<<<<<<< HEAD
	psx_standard_controller_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	virtual ioport_constructor device_input_ports() const;

protected:
	virtual void device_start() { }
private:
	virtual bool get_pad(int count, UINT8 *odata, UINT8 idata);
=======
	psx_standard_controller_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual ioport_constructor device_input_ports() const override;

protected:
	virtual void device_start() override { }
private:
	virtual bool get_pad(int count, uint8_t *odata, uint8_t idata) override;
>>>>>>> upstream/master

	required_ioport m_pad0;
	required_ioport m_pad1;
};

#define MCFG_PSX_CONTROLLER_PORTS_DSR_HANDLER(_devcb) \
	devcb = &psxcontrollerports_device::set_dsr_handler(*device, DEVCB_##_devcb);

#define MCFG_PSX_CONTROLLER_PORTS_RXD_HANDLER(_devcb) \
	devcb = &psxcontrollerports_device::set_rxd_handler(*device, DEVCB_##_devcb);

class psxcontrollerports_device : public device_t
{
public:
<<<<<<< HEAD
	psxcontrollerports_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
	void ack();

	template<class _Object> static devcb_base &set_dsr_handler(device_t &device, _Object object) { return downcast<psxcontrollerports_device &>(device).m_dsr_handler.set_callback(object); }
	template<class _Object> static devcb_base &set_rxd_handler(device_t &device, _Object object) { return downcast<psxcontrollerports_device &>(device).m_rxd_handler.set_callback(object); }
=======
	psxcontrollerports_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	void ack();

	template <class Object> static devcb_base &set_dsr_handler(device_t &device, Object &&cb) { return downcast<psxcontrollerports_device &>(device).m_dsr_handler.set_callback(std::forward<Object>(cb)); }
	template <class Object> static devcb_base &set_rxd_handler(device_t &device, Object &&cb) { return downcast<psxcontrollerports_device &>(device).m_rxd_handler.set_callback(std::forward<Object>(cb)); }
>>>>>>> upstream/master

	DECLARE_WRITE_LINE_MEMBER(write_sck);
	DECLARE_WRITE_LINE_MEMBER(write_dtr);
	DECLARE_WRITE_LINE_MEMBER(write_txd);

protected:
<<<<<<< HEAD
	virtual void device_start();
=======
	virtual void device_start() override;
>>>>>>> upstream/master

private:
	psx_controller_port_device *m_port0;
	psx_controller_port_device *m_port1;

	devcb_write_line m_dsr_handler;
	devcb_write_line m_rxd_handler;
};

class psx_controller_port_device :  public device_t,
									public device_slot_interface
{
public:
<<<<<<< HEAD
	psx_controller_port_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
	virtual machine_config_constructor device_mconfig_additions() const;
=======
	psx_controller_port_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
>>>>>>> upstream/master

	typedef delegate<void ()> void_cb;
	void ack() { if(!ack_cb.isnull()) ack_cb(); }
	void setup_ack_cb(void_cb cb) { ack_cb = cb; }

	DECLARE_WRITE_LINE_MEMBER(tx_w) { m_tx = state; }
	DECLARE_WRITE_LINE_MEMBER(sel_w) { if(m_dev) m_dev->sel_w(state); m_card->sel_w(state); }
	DECLARE_WRITE_LINE_MEMBER(clock_w) { if(m_dev) m_dev->clock_w(state); m_card->clock_w(state); }

	DECLARE_READ_LINE_MEMBER(rx_r) { return (m_dev?m_dev->rx_r():true) && m_card->rx_r(); }
	DECLARE_READ_LINE_MEMBER(ack_r) { return (m_dev?m_dev->ack_r():true) && m_card->ack_r(); }
	DECLARE_READ_LINE_MEMBER(tx_r) { return m_tx; }

	void disable_card(bool status);

protected:
<<<<<<< HEAD
	virtual void device_start() {}
	virtual void device_reset() { m_tx = true; }
	virtual void device_config_complete();
=======
	virtual void device_start() override {}
	virtual void device_reset() override { m_tx = true; }
	virtual void device_config_complete() override;

	virtual void device_add_mconfig(machine_config &config) override;
>>>>>>> upstream/master

private:
	void_cb ack_cb;
	bool m_tx;

	device_psx_controller_interface *m_dev;
	required_device<psxcard_device> m_card;
};
<<<<<<< HEAD
#endif
=======

#endif // MAME_BUS_PSX_CTLRPORT_H
>>>>>>> upstream/master
