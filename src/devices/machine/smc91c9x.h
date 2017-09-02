// license:BSD-3-Clause
// copyright-holders:Aaron Giles
/*************************************************************************

    SMC91C9X ethernet controller implementation

    by Aaron Giles

**************************************************************************/

<<<<<<< HEAD
#ifndef __SMC91C9X__
#define __SMC91C9X__

#define ETHER_BUFFER_SIZE   (2048)
#define ETHER_RX_BUFFERS    (4)
=======
#ifndef MAME_MACHINE_SMC91C9X_H
#define MAME_MACHINE_SMC91C9X_H
>>>>>>> upstream/master

/***************************************************************************
    TYPE DEFINITIONS
***************************************************************************/

class smc91c9x_device : public device_t
{
public:
<<<<<<< HEAD
	smc91c9x_device(const machine_config &mconfig, device_type type, const char *name, const char *tag, device_t *owner, UINT32 clock, const char *shortname, const char *source);
	~smc91c9x_device() {}

	template<class _Object> static devcb_base &set_irq_callback(device_t &device, _Object object) { return downcast<smc91c9x_device &>(device).m_irq_handler.set_callback(object); }
=======
	template <class Object> static devcb_base &set_irq_callback(device_t &device, Object &&cb) { return downcast<smc91c9x_device &>(device).m_irq_handler.set_callback(std::forward<Object>(cb)); }
>>>>>>> upstream/master

	DECLARE_READ16_MEMBER( read );
	DECLARE_WRITE16_MEMBER( write );

protected:
<<<<<<< HEAD
	// device-level overrides
	virtual void device_start();
	virtual void device_reset();

private:
	// internal state
	devcb_write_line m_irq_handler;

	/* raw register data and masks */
	UINT16          m_reg[64];
	UINT16          m_regmask[64];

	/* IRQ information */
	UINT8           m_irq_state;

	/* allocate information */
	UINT8           m_alloc_count;

	/* transmit/receive FIFOs */
	UINT8           m_fifo_count;
	UINT8           m_rx[ETHER_BUFFER_SIZE * ETHER_RX_BUFFERS];
	UINT8           m_tx[ETHER_BUFFER_SIZE];

	/* counters */
	UINT32          m_sent;
	UINT32          m_recd;

	void update_ethernet_irq();
	void update_stats();
	void finish_enqueue(int param);
	void process_command(UINT16 data);
=======
	smc91c9x_device(const machine_config &mconfig, device_type type, const char *tag, device_t *owner, uint32_t clock);

	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;

private:
	static constexpr unsigned ETHER_BUFFER_SIZE   = 2048;
	static constexpr unsigned ETHER_RX_BUFFERS    = 4;

	// internal state
	devcb_write_line m_irq_handler;

	// link unconnected
	bool m_link_unconnected;

	/* raw register data and masks */
	uint16_t          m_reg[64];
	uint16_t          m_regmask[64];

	/* IRQ information */
	uint8_t           m_irq_state;

	/* allocate information */
	uint8_t           m_alloc_count;

	/* transmit/receive FIFOs */
	uint8_t           m_fifo_count;
	uint8_t           m_rx[ETHER_BUFFER_SIZE * ETHER_RX_BUFFERS];
	uint8_t           m_tx[ETHER_BUFFER_SIZE];

	/* counters */
	uint32_t          m_sent;
	uint32_t          m_recd;

	void update_ethernet_irq();
	void update_stats();
	TIMER_CALLBACK_MEMBER(finish_enqueue);
	void process_command(uint16_t data);
	emu_timer* m_tx_timer;

>>>>>>> upstream/master
};


class smc91c94_device : public smc91c9x_device
{
public:
<<<<<<< HEAD
	smc91c94_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
};

extern const device_type SMC91C94;

class smc91c96_device : public smc91c9x_device
{
public:
	smc91c96_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
};

extern const device_type SMC91C96;
=======
	smc91c94_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
};

class smc91c96_device : public smc91c9x_device
{
public:
	smc91c96_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
};


DECLARE_DEVICE_TYPE(SMC91C94, smc91c94_device)
DECLARE_DEVICE_TYPE(SMC91C96, smc91c96_device)

>>>>>>> upstream/master

/***************************************************************************
    DEVICE CONFIGURATION MACROS
***************************************************************************/

<<<<<<< HEAD
#define MCFG_SMC91C94_ADD(_tag) \
	MCFG_DEVICE_ADD(_tag, SMC91C94, 0)

#define MCFG_SMC91C94_IRQ_CALLBACK(_write) \
	devcb = &smc91c94_device::set_irq_callback(*device, DEVCB_##_write);

#define MCFG_SMC91C96_ADD(_tag) \
	MCFG_DEVICE_ADD(_tag, SMC91C96, 0)

#define MCFG_SMC91C96_IRQ_CALLBACK(_write) \
	devcb = &smc91c96_device::set_irq_callback(*device, DEVCB_##_write);


#endif
=======
#define MCFG_SMC91C94_ADD(tag) \
		MCFG_DEVICE_ADD((tag), SMC91C94, 0)

#define MCFG_SMC91C94_IRQ_CALLBACK(write) \
		devcb = &smc91c94_device::set_irq_callback(*device, DEVCB_##write);

#define MCFG_SMC91C96_ADD(tag) \
	MCFG_DEVICE_ADD((tag), SMC91C96, 0)

#define MCFG_SMC91C96_IRQ_CALLBACK(write) \
	devcb = &smc91c96_device::set_irq_callback(*device, DEVCB_##write);

#endif // MAME_MACHINE_SMC91C9X_H
>>>>>>> upstream/master
