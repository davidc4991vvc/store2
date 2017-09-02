// license:BSD-3-Clause
// copyright-holders:Hans Ostermeyer, R. Belmont
/*
 * sc499.h - Archive Cartridge tape controller SC-499
 *
 *  Created on: February 21, 2011
 *      Author: Hans Ostermeyer
 *
 */

<<<<<<< HEAD
#pragma once

#ifndef SC499_H_
#define SC499_H_

#include "emu.h"
#include "bus/isa/isa.h"
=======
#ifndef MAME_BUS_ISA_SC499_H
#define MAME_BUS_ISA_SC499_H

#pragma once

#include "bus/isa/isa.h"
#include "softlist_dev.h"

>>>>>>> upstream/master

//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

// ======================> sc499_ctape_image_device

class sc499_ctape_image_device : public device_t, public device_image_interface
{
public:
	// construction/destruction
<<<<<<< HEAD
	sc499_ctape_image_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// image-level overrides
	virtual bool call_load();
	virtual bool call_softlist_load(software_list_device &swlist, const char *swname, const rom_entry *start_entry) { return load_software(swlist, swname, start_entry); }
	virtual void call_unload();
	virtual iodevice_t image_type() const { return IO_MAGTAPE; }

	virtual bool is_readable()  const { return 1; }
	virtual bool is_writeable() const { return 1; }
	virtual bool is_creatable() const { return 1; }
	virtual bool must_be_loaded() const { return 0; }
	virtual bool is_reset_on_load() const { return 0; }
	virtual const char *image_interface() const { return "sc499_cass"; }
	virtual const char *file_extensions() const { return "act,ct"; }
	virtual const option_guide *create_option_guide() const { return NULL; }

	UINT8 *read_block(int block_num);
	void write_block(int block_num, UINT8 *ptr);
	UINT64 tapelen() { return m_ctape_data.size(); }

protected:
	// device-level overrides
	virtual void device_config_complete();
	virtual void device_start() { };

	dynamic_buffer m_ctape_data;
=======
	sc499_ctape_image_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// image-level overrides
	virtual image_init_result call_load() override;
	virtual const software_list_loader &get_software_list_loader() const override { return image_software_list_loader::instance(); }
	virtual void call_unload() override;
	virtual iodevice_t image_type() const override { return IO_MAGTAPE; }

	virtual bool is_readable()  const override { return 1; }
	virtual bool is_writeable() const override { return 1; }
	virtual bool is_creatable() const override { return 1; }
	virtual bool must_be_loaded() const override { return 0; }
	virtual bool is_reset_on_load() const override { return 0; }
	virtual bool support_command_line_image_creation() const override { return 1; }
	virtual const char *image_interface() const override { return "sc499_cass"; }
	virtual const char *file_extensions() const override { return "act,ct"; }
	virtual const char *custom_instance_name() const override { return "ctape"; }
	virtual const char *custom_brief_instance_name() const override { return "ct"; }

	uint8_t *read_block(int block_num);
	void write_block(int block_num, uint8_t *ptr);
	uint64_t tapelen() { return m_ctape_data.size(); }

protected:
	// device-level overrides
	virtual void device_start() override { }

	std::vector<uint8_t> m_ctape_data;
>>>>>>> upstream/master
};

// ======================> sc499_device

class sc499_device: public device_t, public device_isa8_card_interface
{
public:
	// construction/destruction
<<<<<<< HEAD
	sc499_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	int sc499_receive(const UINT8 data[], int length);

=======
	sc499_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

protected:
>>>>>>> upstream/master
	required_ioport m_iobase;
	required_ioport m_irqdrq;

private:
	// device-level overrides
<<<<<<< HEAD
	virtual void device_start();
	virtual void device_reset();
	virtual void device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr);
	virtual machine_config_constructor device_mconfig_additions() const;
	virtual ioport_constructor device_input_ports() const;

	// ISA overrides
	virtual UINT8 dack_r(int line);
	virtual void dack_w(int line,UINT8 data);
	virtual void eop_w(int state);

	const char *cpu_context();

	void tape_status_clear(UINT16 value);
	void tape_status_set(UINT16 value);
=======
	virtual void device_start() override;
	virtual void device_reset() override;
	virtual void device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr) override;
	virtual void device_add_mconfig(machine_config &config) override;
	virtual ioport_constructor device_input_ports() const override;

	// ISA overrides
	virtual uint8_t dack_r(int line) override;
	virtual void dack_w(int line,uint8_t data) override;
	virtual void eop_w(int state) override;

	const char *cpu_context();
	template <typename Format, typename... Params> void logerror(Format &&fmt, Params &&... args) const;

	void tape_status_clear(uint16_t value);
	void tape_status_set(uint16_t value);
>>>>>>> upstream/master

	// device register I/O
	DECLARE_READ8_MEMBER(read);
	DECLARE_WRITE8_MEMBER(write);

	void check_tape();

	void set_interrupt(enum line_state state);

<<<<<<< HEAD
	void log_command(UINT8 data);
	void do_command(UINT8 data);
=======
	void log_command(uint8_t data);
	void do_command(uint8_t data);
>>>>>>> upstream/master
	void do_reset();

	void set_dma_drq(enum line_state state);

<<<<<<< HEAD
	void write_command_port( UINT8 data);
	UINT8 read_data_port();
	void write_control_port( UINT8 data);
	UINT8 read_status_port();
	void write_dma_go( UINT8 data);
	void write_dma_reset( UINT8 data);
=======
	void write_command_port( uint8_t data);
	uint8_t read_data_port();
	void write_control_port( uint8_t data);
	uint8_t read_status_port();
	void write_dma_go( uint8_t data);
	void write_dma_reset( uint8_t data);
>>>>>>> upstream/master

	void log_block(const char * text);
	void read_block();
	void write_block();
	int block_is_filemark();
	void block_set_filemark();

<<<<<<< HEAD
	UINT8 m_data;
	UINT8 m_command;
	UINT8 m_status;
	UINT8 m_control;

	UINT8 m_has_cartridge;
	UINT8 m_is_writable;

	UINT8 m_current_command;

	UINT8 m_first_block_hack;
	UINT8 m_nasty_readahead;
	UINT8 m_read_block_pending;

	UINT16 m_data_index;

	UINT16 m_tape_status;           /* Drive exception flags */
	UINT16 m_data_error_counter;    /* data error count: nr of blocks rewritten/soft read errors */
	UINT16 m_underrun_counter;      /* underrun count: nr of times streaming was interrupted */

	UINT32 m_tape_pos;
	UINT32 m_ctape_block_count;
	UINT32 m_ctape_block_index;
	UINT64 m_image_length;

	dynamic_buffer m_ctape_block_buffer;
=======
	uint8_t m_data;
	uint8_t m_command;
	uint8_t m_status;
	uint8_t m_control;

	uint8_t m_has_cartridge;
	uint8_t m_is_writable;

	uint8_t m_current_command;

	uint8_t m_first_block_hack;
	uint8_t m_nasty_readahead;
	uint8_t m_read_block_pending;

	uint16_t m_data_index;

	uint16_t m_tape_status;           /* Drive exception flags */
	uint16_t m_data_error_counter;    /* data error count: nr of blocks rewritten/soft read errors */
	uint16_t m_underrun_counter;      /* underrun count: nr of times streaming was interrupted */

	uint32_t m_tape_pos;
	uint32_t m_ctape_block_count;
	uint32_t m_ctape_block_index;
	uint64_t m_image_length;

	std::vector<uint8_t> m_ctape_block_buffer;
>>>>>>> upstream/master
	required_device<sc499_ctape_image_device> m_image;

	enum line_state irq_state;
	enum line_state dma_drq_state;

	emu_timer * m_timer; // timer to delay functions
	emu_timer * m_timer1; // timer to delay functions
<<<<<<< HEAD
	int m_timer_type;
=======
>>>>>>> upstream/master
	int m_irq, m_drq;

	bool m_installed;
};


// device type definition
<<<<<<< HEAD
extern const device_type ISA8_SC499;

#endif /* SC499_H_ */
=======
DECLARE_DEVICE_TYPE(ISA8_SC499, sc499_device)

#endif // MAME_BUS_ISA_SC499_H
>>>>>>> upstream/master
