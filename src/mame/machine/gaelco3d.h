// license:BSD-3-Clause
// copyright-holders:Aaron Giles
/***************************************************************************

    Gaelco 3D serial hardware

***************************************************************************/
<<<<<<< HEAD

=======
#ifndef MAME_MACHINE_GAELCO3D_H
#define MAME_MACHINE_GAELCO3D_H

#pragma once
>>>>>>> upstream/master


/***************************************************************************
    DEVICE CONFIGURATION MACROS
***************************************************************************/

#define MCFG_GAELCO_SERIAL_IRQ_HANDLER(_devcb) \
	devcb = &gaelco_serial_device::set_irq_handler(*device, DEVCB_##_devcb);

<<<<<<< HEAD
/* external status bits */
#define GAELCOSER_STATUS_READY          0x01
#define GAELCOSER_STATUS_RTS            0x02

/* only RTS currently understood ! */
//#define GAELCOSER_STATUS_DTR          0x04

#define GAELCOSER_EXT_STATUS_MASK       0x03

/* internal bits follow ... */
#define GAELCOSER_STATUS_IRQ_ENABLE     0x10
#define GAELCOSER_STATUS_RESET          0x20
#define GAELCOSER_STATUS_SEND           0x40

=======
>>>>>>> upstream/master


/***************************************************************************
    DEVICE INTERFACE TYPE
***************************************************************************/

/* ----- device interface ----- */

<<<<<<< HEAD
struct buf_t
{
	volatile UINT8 data;
	volatile UINT8 stat;
	volatile int cnt;
	volatile int data_cnt;
};

struct shmem_t
{
	volatile INT32  lock;
	buf_t               buf[2];
};

struct osd_shared_mem
{
	char *fn;
	size_t size;
	void *ptr;
	int creator;
};

class gaelco_serial_device : public device_t
{
public:
	gaelco_serial_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
	~gaelco_serial_device() {}

	template<class _Object> static devcb_base &set_irq_handler(device_t &device, _Object object) { return downcast<gaelco_serial_device &>(device).m_irq_handler.set_callback(object); }

	DECLARE_READ8_MEMBER( status_r);
	DECLARE_WRITE8_MEMBER( data_w);
	DECLARE_READ8_MEMBER( data_r);
	DECLARE_WRITE8_MEMBER( rts_w );
	/* Set to 1 during transmit, 0 for receive */
	DECLARE_WRITE8_MEMBER( tr_w);
=======
class gaelco_serial_device : public device_t
{
public:
	static constexpr unsigned EXT_STATUS_MASK = 0x03;

	gaelco_serial_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	template <class Object> static devcb_base &set_irq_handler(device_t &device, Object &&cb) { return downcast<gaelco_serial_device &>(device).m_irq_handler.set_callback(std::forward<Object>(cb)); }

	DECLARE_READ8_MEMBER(status_r);
	DECLARE_WRITE8_MEMBER(data_w);
	DECLARE_READ8_MEMBER(data_r);
	DECLARE_WRITE_LINE_MEMBER(rts_w);
	/* Set to 1 during transmit, 0 for receive */
	DECLARE_WRITE_LINE_MEMBER(tr_w);
>>>>>>> upstream/master


	/* Big questions marks, related to serial i/o */

	/* Not used in surfplnt, but in radikalb
	 * Set at beginning of transfer sub, cleared at end
	 */
<<<<<<< HEAD
	DECLARE_WRITE8_MEMBER( unknown_w);


	/* only used in radikalb, set at beginning of receive isr, cleared at end */
	DECLARE_WRITE8_MEMBER( irq_enable );

protected:
	// device-level overrides
	virtual void device_start();
	virtual void device_stop();
	virtual void device_reset();

private:
	// internal state
	devcb_write_line m_irq_handler;

	UINT8 m_status;
=======
	DECLARE_WRITE_LINE_MEMBER(unknown_w);


	/* only used in radikalb, set at beginning of receive isr, cleared at end */
	DECLARE_WRITE_LINE_MEMBER(irq_enable);

protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_stop() override;
	virtual void device_reset() override;

private:
	struct buf_t
	{
		volatile uint8_t data;
		volatile uint8_t stat;
		volatile int cnt;
		volatile int data_cnt;
	};

	struct shmem_t
	{
		buf_t               buf[2];
	};

	struct osd_shared_mem
	{
		char *fn;
		size_t size;
		void *ptr;
		int creator;
	};

	static osd_shared_mem *osd_sharedmem_alloc(const char *path, int create, size_t size);
	static void osd_sharedmem_free(osd_shared_mem *os_shmem);
	static void *osd_sharedmem_ptr(osd_shared_mem *os_shmem);

	static void buf_reset(buf_t *buf);

	// internal state
	devcb_write_line m_irq_handler;

	uint8_t m_status;
>>>>>>> upstream/master
	int m_last_in_msg_cnt;
	int m_slack_cnt;

	emu_timer *m_sync_timer;

	buf_t *m_in_ptr;
	buf_t *m_out_ptr;
	osd_shared_mem *m_os_shmem;
	shmem_t *m_shmem;
<<<<<<< HEAD

	TIMER_CALLBACK_MEMBER( set_status_cb );
	TIMER_CALLBACK_MEMBER( link_cb );
	void set_status(UINT8 mask, UINT8 set, int wait);
=======
	std::mutex m_mutex;

	TIMER_CALLBACK_MEMBER( set_status_cb );
	TIMER_CALLBACK_MEMBER( link_cb );
	void set_status(uint8_t mask, uint8_t set, int wait);
>>>>>>> upstream/master
	void process_in();
	void sync_link();
};

extern const device_type GAELCO_SERIAL;
<<<<<<< HEAD
=======

#endif // MAME_MACHINE_GAELCO3D_H
>>>>>>> upstream/master
