// license:BSD-3-Clause
// copyright-holders:smf
/*
 * am53cf96.h
 *
 */

<<<<<<< HEAD
#ifndef _AM53CF96_H_
#define _AM53CF96_H_
=======
#ifndef MAME_MACHINE_AM53CF96_H
#define MAME_MACHINE_AM53CF96_H
>>>>>>> upstream/master

#pragma once

#include "legscsi.h"

#define MCFG_AM53CF96_IRQ_HANDLER(_devcb) \
	devcb = &am53cf96_device::set_irq_handler(*device, DEVCB_##_devcb);

<<<<<<< HEAD
// 53CF96 register set
enum
{
	REG_XFERCNTLOW = 0, // read = current xfer count lo byte, write = set xfer count lo byte
	REG_XFERCNTMID,     // read = current xfer count mid byte, write = set xfer count mid byte
	REG_FIFO,       // read/write = FIFO
	REG_COMMAND,        // read/write = command

	REG_STATUS,     // read = status, write = destination SCSI ID (4)
	REG_IRQSTATE,       // read = IRQ status, write = timeout         (5)
	REG_INTSTATE,       // read = internal state, write = sync xfer period (6)
	REG_FIFOSTATE,      // read = FIFO status, write = sync offset
	REG_CTRL1,      // read/write = control 1
	REG_CLOCKFCTR,      // clock factor (write only)
	REG_TESTMODE,       // test mode (write only)
	REG_CTRL2,      // read/write = control 2
	REG_CTRL3,      // read/write = control 3
	REG_CTRL4,      // read/write = control 4
	REG_XFERCNTHI,      // read = current xfer count hi byte, write = set xfer count hi byte
	REG_DATAALIGN       // data alignment (write only)
};

=======
>>>>>>> upstream/master
class am53cf96_device : public legacy_scsi_host_adapter
{
public:
	// construction/destruction
<<<<<<< HEAD
	am53cf96_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// static configuration helpers
	template<class _Object> static devcb_base &set_irq_handler(device_t &device, _Object object) { return downcast<am53cf96_device &>(device).m_irq_handler.set_callback(object); }
=======
	am53cf96_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// static configuration helpers
	template <class Object> static devcb_base &set_irq_handler(device_t &device, Object &&cb) { return downcast<am53cf96_device &>(device).m_irq_handler.set_callback(std::forward<Object>(cb)); }
>>>>>>> upstream/master

	DECLARE_READ8_MEMBER(read);
	DECLARE_WRITE8_MEMBER(write);

<<<<<<< HEAD
	void dma_read_data(int bytes, UINT8 *pData);
	void dma_write_data(int bytes, UINT8 *pData);

protected:
	// device-level overrides
	virtual void device_start();
	virtual void device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr);

private:
	static const device_timer_id TIMER_TRANSFER = 0;

	UINT8 scsi_regs[32];
	UINT8 fifo[16];
	UINT8 fptr;
	UINT8 xfer_state;
	UINT8 last_id;
=======
	void dma_read_data(int bytes, uint8_t *pData);
	void dma_write_data(int bytes, uint8_t *pData);

protected:
	// 53CF96 register set
	enum
	{
		REG_XFERCNTLOW = 0, // read = current xfer count lo byte, write = set xfer count lo byte
		REG_XFERCNTMID,     // read = current xfer count mid byte, write = set xfer count mid byte
		REG_FIFO,           // read/write = FIFO
		REG_COMMAND,        // read/write = command

		REG_STATUS,         // read = status, write = destination SCSI ID (4)
		REG_IRQSTATE,       // read = IRQ status, write = timeout         (5)
		REG_INTSTATE,       // read = internal state, write = sync xfer period (6)
		REG_FIFOSTATE,      // read = FIFO status, write = sync offset
		REG_CTRL1,          // read/write = control 1
		REG_CLOCKFCTR,      // clock factor (write only)
		REG_TESTMODE,       // test mode (write only)
		REG_CTRL2,          // read/write = control 2
		REG_CTRL3,          // read/write = control 3
		REG_CTRL4,          // read/write = control 4
		REG_XFERCNTHI,      // read = current xfer count hi byte, write = set xfer count hi byte
		REG_DATAALIGN       // data alignment (write only)
	};

	// device-level overrides
	virtual void device_start() override;
	virtual void device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr) override;

private:
	static constexpr device_timer_id TIMER_TRANSFER = 0;

	uint8_t scsi_regs[32];
	uint8_t fifo[16];
	uint8_t fptr;
	uint8_t xfer_state;
	uint8_t last_id;
>>>>>>> upstream/master

	emu_timer* m_transfer_timer;
	devcb_write_line m_irq_handler;
};

// device type definition
<<<<<<< HEAD
extern const device_type AM53CF96;

#endif
=======
DECLARE_DEVICE_TYPE(AM53CF96, am53cf96_device)

#endif // MAME_MACHINE_AM53CF96_H
>>>>>>> upstream/master
