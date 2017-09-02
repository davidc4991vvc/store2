// license:BSD-3-Clause
// copyright-holders:Olivier Galibert
/***************************************************************************

    i8x9x.h

    MCS96, 8x9x branch, the original version

***************************************************************************/

<<<<<<< HEAD
#ifndef __I8X9X_H__
#define __I8X9X_H__
=======
#ifndef MAME_CPU_MCS96_I8X9X_H
#define MAME_CPU_MCS96_I8X9X_H
>>>>>>> upstream/master

#include "mcs96.h"

class i8x9x_device : public mcs96_device {
public:
	enum {
		A0, A1, A2, A3, A4, A5, A6, A7,
		SERIAL,
		P0, P1, P2
	};

<<<<<<< HEAD
	i8x9x_device(const machine_config &mconfig, device_type type, const char *name, const char *tag, device_t *owner, UINT32 clock, const char *shortname, const char *source);

	void serial_w(UINT8 val);

protected:
	virtual void device_start();
	virtual void device_reset();
	virtual const address_space_config *memory_space_config(address_spacenum spacenum = AS_0) const;

	static const disasm_entry disasm_entries[0x100];

	virtual offs_t disasm_disassemble(char *buffer, offs_t pc, const UINT8 *oprom, const UINT8 *opram, UINT32 options);
	virtual void do_exec_full();
	virtual void do_exec_partial();
	virtual void internal_update(UINT64 current_time);
	virtual void io_w8(UINT8 adr, UINT8 data);
	virtual void io_w16(UINT8 adr, UINT16 data);
	virtual UINT8 io_r8(UINT8 adr);
	virtual UINT16 io_r16(UINT8 adr);
=======
	void serial_w(uint8_t val);

protected:
	i8x9x_device(const machine_config &mconfig, device_type type, const char *tag, device_t *owner, uint32_t clock);

	virtual void device_start() override;
	virtual void device_reset() override;
	virtual space_config_vector memory_space_config() const override;

	static const disasm_entry disasm_entries[0x100];

	virtual offs_t disasm_disassemble(std::ostream &stream, offs_t pc, const uint8_t *oprom, const uint8_t *opram, uint32_t options) override;
	virtual void do_exec_full() override;
	virtual void do_exec_partial() override;
	virtual void internal_update(uint64_t current_time) override;
	virtual void io_w8(uint8_t adr, uint8_t data) override;
	virtual void io_w16(uint8_t adr, uint16_t data) override;
	virtual uint8_t io_r8(uint8_t adr) override;
	virtual uint16_t io_r16(uint8_t adr) override;
>>>>>>> upstream/master

private:
	enum {
		IRQ_TIMER  = 0x01,
		IRQ_AD     = 0x02,
		IRQ_HSI    = 0x04,
		IRQ_HSO    = 0x08,
		IRQ_HSI0   = 0x10,
		IRQ_SOFT   = 0x20,
		IRQ_SERIAL = 0x40,
		IRQ_EXTINT = 0x80
	};

	struct hso_cam_entry {
		bool active;
<<<<<<< HEAD
		UINT8 command;
		UINT16 time;
=======
		uint8_t command;
		uint16_t time;
>>>>>>> upstream/master
	};

	address_space_config io_config;
	address_space *io;

	hso_cam_entry hso_info[8];
	hso_cam_entry hso_cam_hold;

<<<<<<< HEAD
	UINT64 base_timer2, ad_done;
	UINT8 hso_command, ad_command;
	UINT16 hso_time, ad_result;
	UINT8 ios0, ios1, ioc0, ioc1;
	UINT8 sbuf, sp_stat;
	UINT8 serial_send_buf;
	UINT64 serial_send_timer;

	UINT16 timer_value(int timer, UINT64 current_time) const;
	UINT64 timer_time_until(int timer, UINT64 current_time, UINT16 timer_value) const;
	void commit_hso_cam();
	void trigger_cam(int id, UINT64 current_time);
	void ad_start(UINT64 current_time);
	void serial_send(UINT8 data);
=======
	uint64_t base_timer2, ad_done;
	uint8_t hso_command, ad_command;
	uint16_t hso_time, ad_result;
	uint8_t ios0, ios1, ioc0, ioc1;
	uint8_t sbuf, sp_stat;
	uint8_t serial_send_buf;
	uint64_t serial_send_timer;

	uint16_t timer_value(int timer, uint64_t current_time) const;
	uint64_t timer_time_until(int timer, uint64_t current_time, uint16_t timer_value) const;
	void commit_hso_cam();
	void trigger_cam(int id, uint64_t current_time);
	void ad_start(uint64_t current_time);
	void serial_send(uint8_t data);
>>>>>>> upstream/master
	void serial_send_done();
};

class c8095_device : public i8x9x_device {
public:
<<<<<<< HEAD
	c8095_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
=======
	c8095_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
>>>>>>> upstream/master
};

class p8098_device : public i8x9x_device {
public:
<<<<<<< HEAD
	p8098_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
};

extern const device_type C8095;
extern const device_type P8098;

#endif
=======
	p8098_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
};

DECLARE_DEVICE_TYPE(C8095, c8095_device)
DECLARE_DEVICE_TYPE(P8098, p8098_device)

#endif // MAME_CPU_MCS96_I8X9X_H
>>>>>>> upstream/master
