// license:BSD-3-Clause
// copyright-holders:smf
/*****************************************************************************
 *
 * machine/ser_mouse.h
 *
 ****************************************************************************/

<<<<<<< HEAD
#ifndef SER_MOUSE_H_
#define SER_MOUSE_H_
=======
#ifndef MAME_BUS_RS232_SER_MOUSE_H
#define MAME_BUS_RS232_SER_MOUSE_H
>>>>>>> upstream/master

#include "rs232.h"

class serial_mouse_device :
		public device_t,
		public device_rs232_port_interface,
		public device_serial_interface
{
public:
<<<<<<< HEAD
	serial_mouse_device(const machine_config &mconfig, device_type type, const char *name, const char *tag, device_t *owner, UINT32 clock, const char *shortname, const char *source);

	virtual ioport_constructor device_input_ports() const;

protected:
	virtual void device_start();
	virtual void device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr);
	virtual void mouse_trans(int dx, int dy, int nb, int mbc) = 0;
	virtual void set_frame() = 0;
	void set_mouse_enable(bool state);
	void queue_data(UINT8 data) {m_queue[m_head] = data; ++m_head %= 256;}
	UINT8 unqueue_data() {UINT8 ret = m_queue[m_tail]; ++m_tail %= 256; return ret;}
	virtual void tra_complete();
	virtual void tra_callback();
	void reset_mouse();

	virtual WRITE_LINE_MEMBER(input_dtr);
	virtual WRITE_LINE_MEMBER(input_rts);
=======
	virtual ioport_constructor device_input_ports() const override;

protected:
	serial_mouse_device(const machine_config &mconfig, device_type type, const char *tag, device_t *owner, uint32_t clock);

	virtual void device_start() override;
	virtual void device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr) override;

	virtual void mouse_trans(int dx, int dy, int nb, int mbc) = 0;
	virtual void set_frame() = 0;
	void set_mouse_enable(bool state);
	void queue_data(uint8_t data) {m_queue[m_head] = data; ++m_head %= 256;}
	uint8_t unqueue_data() {uint8_t ret = m_queue[m_tail]; ++m_tail %= 256; return ret;}
	virtual void tra_complete() override;
	virtual void tra_callback() override;
	void reset_mouse();

	virtual WRITE_LINE_MEMBER(input_dtr) override;
	virtual WRITE_LINE_MEMBER(input_rts) override;

>>>>>>> upstream/master
	int m_dtr;
	int m_rts;

private:
<<<<<<< HEAD
	UINT8 m_queue[256];
	UINT8 m_head, m_tail, m_mb;
=======
	void check_state() { set_mouse_enable(!m_dtr && !m_rts); }

	uint8_t m_queue[256];
	uint8_t m_head, m_tail, m_mb;
>>>>>>> upstream/master

	emu_timer *m_timer;
	bool m_enabled;

	required_ioport m_x;
	required_ioport m_y;
	required_ioport m_btn;
<<<<<<< HEAD

	void check_state() { set_mouse_enable(!m_dtr && !m_rts); }
=======
>>>>>>> upstream/master
};

class microsoft_mouse_device : public serial_mouse_device
{
public:
<<<<<<< HEAD
	microsoft_mouse_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

protected:
	virtual WRITE_LINE_MEMBER(input_rts);

	virtual void set_frame() { set_data_frame(1, 7, PARITY_NONE, STOP_BITS_2); }
	virtual void mouse_trans(int dx, int dy, int nb, int mbc);
};

extern const device_type MSFT_SERIAL_MOUSE;
=======
	microsoft_mouse_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

protected:
	virtual WRITE_LINE_MEMBER(input_rts) override;

	virtual void set_frame() override { set_data_frame(1, 7, PARITY_NONE, STOP_BITS_2); }
	virtual void mouse_trans(int dx, int dy, int nb, int mbc) override;
};

DECLARE_DEVICE_TYPE(MSFT_SERIAL_MOUSE, microsoft_mouse_device)
>>>>>>> upstream/master

class mouse_systems_mouse_device : public serial_mouse_device
{
public:
<<<<<<< HEAD
	mouse_systems_mouse_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

protected:
	virtual void set_frame() { set_data_frame(1, 8, PARITY_NONE, STOP_BITS_2); }
	virtual void mouse_trans(int dx, int dy, int nb, int mbc);
};

extern const device_type MSYSTEM_SERIAL_MOUSE;

#endif /* SER_MOUSE_H_ */
=======
	mouse_systems_mouse_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

protected:
	virtual void set_frame() override { set_data_frame(1, 8, PARITY_NONE, STOP_BITS_2); }
	virtual void mouse_trans(int dx, int dy, int nb, int mbc) override;
};

DECLARE_DEVICE_TYPE(MSYSTEM_SERIAL_MOUSE, mouse_systems_mouse_device)

#endif // MAME_BUS_RS232_SER_MOUSE_H
>>>>>>> upstream/master
