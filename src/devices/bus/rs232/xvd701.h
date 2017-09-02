// license:BSD-3-Clause
// copyright-holders:smf
<<<<<<< HEAD
#ifndef JVC_XV701_H_
#define JVC_XV701_H_
=======
#ifndef MAME_BUS_RS232_XVD701_H
#define MAME_BUS_RS232_XVD701_H
>>>>>>> upstream/master

#include "rs232.h"

class jvc_xvd701_device : public device_t,
	public device_serial_interface,
	public device_rs232_port_interface
{
public:
<<<<<<< HEAD
	jvc_xvd701_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
	virtual machine_config_constructor device_mconfig_additions() const;

	virtual WRITE_LINE_MEMBER( input_txd ) { device_serial_interface::rx_w(state); }

	DECLARE_WRITE_LINE_MEMBER(update_serial);

protected:
	virtual ioport_constructor device_input_ports() const;
	virtual void device_start();
	virtual void device_reset();
	virtual void device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr);

	virtual void tra_callback();
	virtual void tra_complete();
	virtual void rcv_complete();

private:
	static const int TIMER_RESPONSE = 1;
=======
	jvc_xvd701_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual WRITE_LINE_MEMBER( input_txd ) override { device_serial_interface::rx_w(state); }
protected:
	virtual ioport_constructor device_input_ports() const override;
	virtual void device_start() override;
	virtual void device_reset() override;
	virtual void device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr) override;
	virtual void device_add_mconfig(machine_config &config) override;

	virtual void tra_callback() override;
	virtual void tra_complete() override;
	virtual void rcv_complete() override;

private:
	static constexpr int TIMER_RESPONSE = 1;
>>>>>>> upstream/master

	void send_response();
	unsigned char sum(unsigned char *buffer, int length);

	unsigned char m_command[11];
	unsigned char m_response[11];
	int m_response_index;
	emu_timer *m_timer_response;
};

<<<<<<< HEAD
extern const device_type JVC_XVD701;

#endif
=======
DECLARE_DEVICE_TYPE(JVC_XVD701, jvc_xvd701_device)

#endif // MAME_BUS_RS232_XVD701_H
>>>>>>> upstream/master
