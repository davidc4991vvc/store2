// license:BSD-3-Clause
// copyright-holders:Carl
<<<<<<< HEAD
#ifndef PC_JOY_SW_H_
#define PC_JOY_SW_H_
=======
#ifndef MAME_BUS_PC_JOY_PC_JOY_SW_H
#define MAME_BUS_PC_JOY_PC_JOY_SW_H
>>>>>>> upstream/master

#include "pc_joy.h"

class pc_mssw_pad_device :  public device_t,
							public device_pc_joy_interface
{
public:
<<<<<<< HEAD
	pc_mssw_pad_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
	virtual ioport_constructor device_input_ports() const;

	virtual UINT8 btn() { return m_state; }
	// timing is guessed, calibrated for at486
	virtual void port_write() { if(!m_active) { m_timer->adjust(attotime::from_usec(50), 0, attotime::from_usec(5)); m_active = true; } }

protected:
	virtual void device_start();
	virtual void device_timer(emu_timer &timer, device_timer_id tid, int param, void *ptr);
	virtual void device_reset();
=======
	pc_mssw_pad_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
	virtual ioport_constructor device_input_ports() const override;

	virtual uint8_t btn() override { return m_state; }
	// timing is guessed, calibrated for at486
	virtual void port_write() override { if(!m_active) { m_timer->adjust(attotime::from_usec(50), 0, attotime::from_usec(5)); m_active = true; } }

protected:
	virtual void device_start() override;
	virtual void device_reset() override;
	virtual void device_timer(emu_timer &timer, device_timer_id tid, int param, void *ptr) override;
>>>>>>> upstream/master

private:
	required_ioport m_btn1;
	required_ioport m_btn2;
	required_ioport m_btn3;
	required_ioport m_btn4;
	required_ioport m_conf;
	emu_timer *m_timer;
	int m_count;
<<<<<<< HEAD
	UINT8 m_state;
	bool m_active;
};

extern const device_type PC_MSSW_PAD;

#endif /* PC_JOY_SW_H_ */
=======
	uint8_t m_state;
	bool m_active;
};

DECLARE_DEVICE_TYPE(PC_MSSW_PAD, pc_mssw_pad_device)

#endif // MAME_BUS_PC_JOY_PC_JOY_SW_H
>>>>>>> upstream/master
