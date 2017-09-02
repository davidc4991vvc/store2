// license:BSD-3-Clause
// copyright-holders:Wilbert Pol
/**********************************************************************

    ISA 8 bit XT Hard Disk Controller

**********************************************************************/
<<<<<<< HEAD
#pragma once

#ifndef ISA_HDC_H
#define ISA_HDC_H

#include "emu.h"
=======
#ifndef MAME_BUS_ISA_HDC_H
#define MAME_BUS_ISA_HDC_H

#pragma once

>>>>>>> upstream/master
#include "isa.h"
#include "imagedev/harddriv.h"

//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

// XT HD controller device

#define MCFG_XTHDC_IRQ_HANDLER(_devcb) \
	devcb = &xt_hdc_device::set_irq_handler(*device, DEVCB_##_devcb);

#define MCFG_XTHDC_DRQ_HANDLER(_devcb) \
	devcb = &xt_hdc_device::set_drq_handler(*device, DEVCB_##_devcb);

class xt_hdc_device :
		public device_t
{
public:
	// construction/destruction
<<<<<<< HEAD
	xt_hdc_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
	xt_hdc_device(const machine_config &mconfig, device_type type, const char *name, const char *tag, device_t *owner, UINT32 clock, const char *shortname, const char *source);

	template<class _Object> static devcb_base &set_irq_handler(device_t &device, _Object object) { return downcast<xt_hdc_device &>(device).m_irq_handler.set_callback(object); }
	template<class _Object> static devcb_base &set_drq_handler(device_t &device, _Object object) { return downcast<xt_hdc_device &>(device).m_drq_handler.set_callback(object); }

	int dack_r();
=======
	xt_hdc_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	template <class Object> static devcb_base &set_irq_handler(device_t &device, Object &&cb) { return downcast<xt_hdc_device &>(device).m_irq_handler.set_callback(std::forward<Object>(cb)); }
	template <class Object> static devcb_base &set_drq_handler(device_t &device, Object &&cb) { return downcast<xt_hdc_device &>(device).m_drq_handler.set_callback(std::forward<Object>(cb)); }

	int dack_r();
	int dack_rs();
>>>>>>> upstream/master
	void dack_w(int data);
	void dack_ws(int data);

	virtual void command();
	void data_w(int data);
	void reset_w(int data);
	void select_w(int data);
	void control_w(int data);
<<<<<<< HEAD
	UINT8 data_r();
	UINT8 status_r();
	void set_ready();
	UINT8 get_command() { return buffer[0]; }

protected:
	// device-level overrides
	virtual void device_start();
	virtual void device_reset();
	virtual void device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr);
=======
	uint8_t data_r();
	uint8_t status_r();
	void set_ready();
	uint8_t get_command() { return buffer[0]; }
	bool install_rom() { return (m_type != EC1841); }

protected:
	xt_hdc_device(const machine_config &mconfig, device_type type, const char *tag, device_t *owner, uint32_t clock);

	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;
	virtual void device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr) override;
>>>>>>> upstream/master
	hard_disk_file *pc_hdc_file(int id);
	void pc_hdc_result(int set_error_info);
	int no_dma(void);
	int get_lbasector();
	void execute_read();
<<<<<<< HEAD
=======
	void execute_readsbuff();
>>>>>>> upstream/master
	void execute_write();
	void execute_writesbuff();
	void get_drive();
	void get_chsn();
	int test_ready();

<<<<<<< HEAD
	dynamic_buffer buffer;                  /* data buffer */
	UINT8 *buffer_ptr;          /* data pointer */
=======
	std::vector<uint8_t> buffer;                  /* data buffer */
	uint8_t *buffer_ptr;          /* data pointer */
>>>>>>> upstream/master
	int csb;                /* command status byte */
	int status;         /* drive status */
	int error;          /* error code */

	enum {
		STANDARD,
		EC1841,
		ST11M
	};
	int m_type;
<<<<<<< HEAD
	UINT8 m_current_cmd;
=======
	uint8_t m_current_cmd;
>>>>>>> upstream/master
	devcb_write_line m_irq_handler;
	devcb_write_line m_drq_handler;

private:
	int drv;                            /* 0 master, 1 slave drive */
	int cylinders[2];       /* number of cylinders */
	int rwc[2];         /* reduced write current from cyl */
	int wp[2];          /* write precompensation from cyl */
	int heads[2];           /* heads */
	int ecc[2];         /* ECC bytes */

	/* indexes */
	int cylinder[2];            /* current cylinder */
	int head[2];                /* current head */
	int sector[2];          /* current sector */
	int sector_cnt[2];      /* sector count */
	int control[2];         /* control */

	emu_timer *timer;

	int data_cnt;                /* data count */
<<<<<<< HEAD
	UINT8 hdc_control;

	UINT8 hdcdma_data[512];
	UINT8 *hdcdma_src;
	UINT8 *hdcdma_dst;
=======
	uint8_t hdc_control;

	uint8_t hdcdma_data[512];
	uint8_t *hdcdma_src;
	uint8_t *hdcdma_dst;
>>>>>>> upstream/master
	int hdcdma_read;
	int hdcdma_write;
	int hdcdma_size;
};

class ec1841_device : public xt_hdc_device
{
public:
<<<<<<< HEAD
	ec1841_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
=======
	ec1841_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
>>>>>>> upstream/master
protected:
	devcb_write_line m_irq_handler;
	devcb_write_line m_drq_handler;
};

class st11m_device : public xt_hdc_device
{
public:
<<<<<<< HEAD
	st11m_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
=======
	st11m_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
>>>>>>> upstream/master

protected:
	devcb_write_line m_irq_handler;
	devcb_write_line m_drq_handler;
};

<<<<<<< HEAD
extern const device_type XT_HDC;
extern const device_type EC1841_HDC;
extern const device_type ST11M_HDC;
=======
DECLARE_DEVICE_TYPE(XT_HDC,     xt_hdc_device)
DECLARE_DEVICE_TYPE(EC1841_HDC, ec1841_device)
DECLARE_DEVICE_TYPE(ST11M_HDC,  st11m_device)
>>>>>>> upstream/master

// ======================> isa8_hdc_device

class isa8_hdc_device :
		public device_t,
		public device_isa8_card_interface
{
public:
<<<<<<< HEAD
		// construction/destruction
		isa8_hdc_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
		isa8_hdc_device(const machine_config &mconfig, device_type type, const char *name, const char *tag, device_t *owner, UINT32 clock, const char *shortname, const char *source);

		DECLARE_READ8_MEMBER(pc_hdc_r);
		DECLARE_WRITE8_MEMBER(pc_hdc_w);
		DECLARE_WRITE_LINE_MEMBER(irq_w);
		DECLARE_WRITE_LINE_MEMBER(drq_w);
		required_device<xt_hdc_device> m_hdc;

		// optional information overrides
		virtual machine_config_constructor device_mconfig_additions() const;
		virtual const rom_entry *device_rom_region() const;
		virtual ioport_constructor device_input_ports() const;
protected:
		// device-level overrides
		virtual void device_start();
		virtual void device_reset();
public:
		virtual UINT8 dack_r(int line);
		virtual void dack_w(int line,UINT8 data);
		UINT8 pc_hdc_dipswitch_r();

		int dip;                /* dip switches */
=======
	// construction/destruction
	isa8_hdc_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	DECLARE_READ8_MEMBER(pc_hdc_r);
	DECLARE_WRITE8_MEMBER(pc_hdc_w);
	required_device<xt_hdc_device> m_hdc;

protected:
	isa8_hdc_device(const machine_config &mconfig, device_type type, const char *tag, device_t *owner, uint32_t clock);

	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;

	// optional information overrides
	virtual void device_add_mconfig(machine_config &config) override;
	virtual const tiny_rom_entry *device_rom_region() const override;
	virtual ioport_constructor device_input_ports() const override;

	DECLARE_WRITE_LINE_MEMBER(irq_w);
	DECLARE_WRITE_LINE_MEMBER(drq_w);

public:
	virtual uint8_t dack_r(int line) override;
	virtual void dack_w(int line,uint8_t data) override;
	uint8_t pc_hdc_dipswitch_r();

	int dip;                /* dip switches */
>>>>>>> upstream/master
};


class isa8_hdc_ec1841_device : public isa8_hdc_device
{
public:
<<<<<<< HEAD
	isa8_hdc_ec1841_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// optional information overrides
	virtual machine_config_constructor device_mconfig_additions() const;
=======
	isa8_hdc_ec1841_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

protected:
	// optional information overrides
	virtual void device_add_mconfig(machine_config &config) override;
>>>>>>> upstream/master

	required_device<ec1841_device> m_hdc;
};

// device type definition
<<<<<<< HEAD
extern const device_type ISA8_HDC;
extern const device_type ISA8_HDC_EC1841;

#endif  /* ISA_HDC_H */
=======
DECLARE_DEVICE_TYPE(ISA8_HDC,        isa8_hdc_device)
DECLARE_DEVICE_TYPE(ISA8_HDC_EC1841, isa8_hdc_ec1841_device)

#endif // MAME_BUS_ISA_HDC_H
>>>>>>> upstream/master
