// license:BSD-3-Clause
// copyright-holders:Carl
<<<<<<< HEAD
#ifndef _DP8390_H_
#define _DP8390_H_

#include "emu.h"
=======
#ifndef MAME_MACHINE_DP8390_H
#define MAME_MACHINE_DP8390_H

#pragma once
>>>>>>> upstream/master


// device stuff

#define MCFG_DP8390D_IRQ_CB(_devcb) \
	devcb = &dp8390d_device::set_irq_callback(*device, DEVCB_##_devcb);

#define MCFG_DP8390D_BREQ_CB(_devcb) \
	devcb = &dp8390d_device::set_breq_callback(*device, DEVCB_##_devcb);

#define MCFG_DP8390D_MEM_READ_CB(_devcb) \
	devcb = &dp8390d_device::set_mem_read_callback(*device, DEVCB_##_devcb);

#define MCFG_DP8390D_MEM_WRITE_CB(_devcb) \
	devcb = &dp8390d_device::set_mem_write_callback(*device, DEVCB_##_devcb);

#define MCFG_RTL8019A_IRQ_CB(_devcb) \
	devcb = &rtl8019a_device::set_irq_callback(*device, DEVCB_##_devcb);

#define MCFG_RTL8019A_BREQ_CB(_devcb) \
	devcb = &rtl8019a_device::set_breq_callback(*device, DEVCB_##_devcb);

#define MCFG_RTL8019A_MEM_READ_CB(_devcb) \
	devcb = &rtl8019a_device::set_mem_read_callback(*device, DEVCB_##_devcb);

#define MCFG_RTL8019A_MEM_WRITE_CB(_devcb) \
	devcb = &rtl8019a_device::set_mem_write_callback(*device, DEVCB_##_devcb);


<<<<<<< HEAD
class dp8390_device : public device_t,
						public device_network_interface
{
public:
	// construction/destruction
	dp8390_device(const machine_config &mconfig, device_type type, const char *name, const char *tag, device_t *owner, UINT32 clock, float bandwidth, const char *shortname, const char *source);

	template<class _Object> static devcb_base &set_irq_callback(device_t &device, _Object object) { return downcast<dp8390_device &>(device).m_irq_cb.set_callback(object); }
	template<class _Object> static devcb_base &set_breq_callback(device_t &device, _Object object) { return downcast<dp8390_device &>(device).m_breq_cb.set_callback(object); }
	template<class _Object> static devcb_base &set_mem_read_callback(device_t &device, _Object object) { return downcast<dp8390_device &>(device).m_mem_read_cb.set_callback(object); }
	template<class _Object> static devcb_base &set_mem_write_callback(device_t &device, _Object object) { return downcast<dp8390_device &>(device).m_mem_write_cb.set_callback(object); }
=======
class dp8390_device : public device_t, public device_network_interface
{
public:
	template <class Object> static devcb_base &set_irq_callback(device_t &device, Object &&cb) { return downcast<dp8390_device &>(device).m_irq_cb.set_callback(std::forward<Object>(cb)); }
	template <class Object> static devcb_base &set_breq_callback(device_t &device, Object &&cb) { return downcast<dp8390_device &>(device).m_breq_cb.set_callback(std::forward<Object>(cb)); }
	template <class Object> static devcb_base &set_mem_read_callback(device_t &device, Object &&cb) { return downcast<dp8390_device &>(device).m_mem_read_cb.set_callback(std::forward<Object>(cb)); }
	template <class Object> static devcb_base &set_mem_write_callback(device_t &device, Object &&cb) { return downcast<dp8390_device &>(device).m_mem_write_cb.set_callback(std::forward<Object>(cb)); }
>>>>>>> upstream/master

	DECLARE_WRITE16_MEMBER( dp8390_w );
	DECLARE_READ16_MEMBER( dp8390_r );
	DECLARE_WRITE_LINE_MEMBER( dp8390_cs );
	DECLARE_WRITE_LINE_MEMBER( dp8390_reset );
<<<<<<< HEAD
	void recv_cb(UINT8 *buf, int len);

protected:
	// device-level overrides
	virtual void device_start();
	virtual void device_reset();

	int m_type;

	enum {
		TYPE_DP8390D = 0,
		TYPE_RTL8019A
	};
=======
	void recv_cb(uint8_t *buf, int len) override;

protected:
	enum class TYPE {
		DP8390D,
		RTL8019A
	};

	// construction/destruction
	dp8390_device(const machine_config &mconfig, device_type type, const char *tag, device_t *owner, uint32_t clock, TYPE varian, float bandwidth);

	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;

	TYPE const m_variant;
>>>>>>> upstream/master

private:
	devcb_write_line    m_irq_cb;
	devcb_write_line    m_breq_cb;
	devcb_read8         m_mem_read_cb;
	devcb_write8        m_mem_write_cb;

<<<<<<< HEAD
	void set_cr(UINT8 newcr);
	void check_dma_complete();
	void do_tx();
	bool mcast_ck(const UINT8 *buf, int len);
	void check_irq() { m_irq_cb((m_regs.imr & m_regs.isr & 0x7f)?ASSERT_LINE:CLEAR_LINE); }
	void recv_overflow();
	void stop();
	void recv(UINT8 *buf, int len);
=======
	void set_cr(uint8_t newcr);
	void check_dma_complete();
	void do_tx();
	void check_irq() { m_irq_cb((m_regs.imr & m_regs.isr & 0x7f)?ASSERT_LINE:CLEAR_LINE); }
	void recv_overflow();
	void stop();
	void recv(uint8_t *buf, int len);
>>>>>>> upstream/master

	int m_reset;
	bool m_cs;
	int m_rdma_active;

	struct {
<<<<<<< HEAD
		UINT8 cr;
		UINT16 clda;
		UINT8 pstart;
		UINT8 pstop;
		UINT8 bnry;
		UINT8 tsr;
		UINT8 tpsr;
		UINT8 ncr;
		UINT8 fifo;
		UINT16 tbcr;
		UINT8 isr;
		UINT16 crda;
		UINT16 rsar;
		UINT16 rbcr;
		UINT8 rsr;
		UINT8 rcr;
		UINT8 cntr0;
		UINT8 tcr;
		UINT8 cntr1;
		UINT8 dcr;
		UINT8 cntr2;
		UINT8 imr;

		UINT8 par[6];
		UINT8 curr;
		UINT8 mar[8];

		UINT8 rnpp;
		UINT8 lnpp;
		UINT16 ac;
	} m_regs;

	struct {
		UINT8 cr9346;
		UINT8 bpage;
		UINT8 config0;
		UINT8 config1;
		UINT8 config2;
		UINT8 config3;
		UINT8 config4;
		UINT8 csnsav;
		UINT8 intr;
=======
		uint8_t cr;
		uint16_t clda;
		uint8_t pstart;
		uint8_t pstop;
		uint8_t bnry;
		uint8_t tsr;
		uint8_t tpsr;
		uint8_t ncr;
		uint8_t fifo;
		uint16_t tbcr;
		uint8_t isr;
		uint16_t crda;
		uint16_t rsar;
		uint16_t rbcr;
		uint8_t rsr;
		uint8_t rcr;
		uint8_t cntr0;
		uint8_t tcr;
		uint8_t cntr1;
		uint8_t dcr;
		uint8_t cntr2;
		uint8_t imr;

		uint8_t par[6];
		uint8_t curr;
		uint8_t mar[8];

		uint8_t rnpp;
		uint8_t lnpp;
		uint16_t ac;
	} m_regs;

	struct {
		uint8_t cr9346;
		uint8_t bpage;
		uint8_t config0;
		uint8_t config1;
		uint8_t config2;
		uint8_t config3;
		uint8_t config4;
		uint8_t csnsav;
		uint8_t intr;
>>>>>>> upstream/master
	} m_8019regs;
};

class rtl8019a_device : public dp8390_device
{
public:
<<<<<<< HEAD
	rtl8019a_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
=======
	rtl8019a_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
>>>>>>> upstream/master
};

class dp8390d_device : public dp8390_device
{
public:
<<<<<<< HEAD
	dp8390d_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
};

// device type definition
extern const device_type DP8390D;
extern const device_type RTL8019A;

#endif
=======
	dp8390d_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
};

// device type definition
DECLARE_DEVICE_TYPE(DP8390D,  dp8390d_device)
DECLARE_DEVICE_TYPE(RTL8019A, rtl8019a_device)

#endif // MAME_MACHINE_DP8390_H
>>>>>>> upstream/master
