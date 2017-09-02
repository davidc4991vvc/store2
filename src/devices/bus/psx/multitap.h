// license:BSD-3-Clause
// copyright-holders:Carl
<<<<<<< HEAD
#ifndef PSXMULTITAP_H_
#define PSXMULTITAP_H_
=======
#ifndef MAME_BUS_PSX_MULTITAP_H
#define MAME_BUS_PSX_MULTITAP_H
>>>>>>> upstream/master

#include "ctlrport.h"

SLOT_INTERFACE_EXTERN(psx_controllers_nomulti);

class psx_multitap_device : public device_t,
							public device_psx_controller_interface
{
public:
<<<<<<< HEAD
	psx_multitap_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
	virtual machine_config_constructor device_mconfig_additions() const;

protected:
	virtual void device_start();
	virtual void device_stop() { device_psx_controller_interface::m_owner->disable_card(false); }
	virtual void device_reset() { device_psx_controller_interface::m_owner->disable_card(true); }
	virtual void device_config_complete() { m_shortname = "psx_multitap"; }
	virtual void interface_pre_reset();

private:
	virtual bool get_pad(int count, UINT8 *odata, UINT8 idata);
	virtual void do_pad();
=======
	psx_multitap_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

protected:
	virtual void device_start() override;
	virtual void device_stop() override { device_psx_controller_interface::m_owner->disable_card(false); }
	virtual void device_reset() override { device_psx_controller_interface::m_owner->disable_card(true); }
	virtual void interface_pre_reset() override;

	virtual void device_add_mconfig(machine_config &config) override;

private:
	virtual bool get_pad(int count, uint8_t *odata, uint8_t idata) override;
	virtual void do_pad() override;
>>>>>>> upstream/master
	void ack();
	void set_tx_line(bool tx, int port);
	bool get_rx_line(int port);

	int m_activeport;
	bool m_cack[4];
	bool m_singlemode, m_nextmode, m_tapmc;
<<<<<<< HEAD
	UINT8 m_data[3][8]; // port a is passed though
=======
	uint8_t m_data[3][8]; // port a is passed though
>>>>>>> upstream/master
	required_device<psx_controller_port_device> m_porta;
	required_device<psx_controller_port_device> m_portb;
	required_device<psx_controller_port_device> m_portc;
	required_device<psx_controller_port_device> m_portd;
};

extern const device_type PSX_MULTITAP;

<<<<<<< HEAD
#endif /* PSXMULTITAP_H_ */
=======
#endif // MAME_BUS_PSX_MULTITAP_H
>>>>>>> upstream/master
