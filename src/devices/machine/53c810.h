// license:BSD-3-Clause
// copyright-holders:smf
<<<<<<< HEAD
#ifndef LSI53C810_H
#define LSI53C810_H

#include "legscsi.h"

typedef device_delegate<void (int state)> lsi53c810_irq_delegate;
#define LSI53C810_IRQ_CB(name)  void name(int state)

typedef device_delegate<void (UINT32 src, UINT32 dst, int length, int byteswap)> lsi53c810_dma_delegate;
#define LSI53C810_DMA_CB(name)  void name(UINT32 src, UINT32 dst, int length, int byteswap)

typedef device_delegate<UINT32 (UINT32 dsp)> lsi53c810_fetch_delegate;
#define LSI53C810_FETCH_CB(name)  UINT32 name(UINT32 dsp)
=======
#ifndef MAME_MACHINE_53C810_H
#define MAME_MACHINE_53C810_H

#pragma once

#include "legscsi.h"

#define LSI53C810_IRQ_CB(name)  void name(int state)
#define LSI53C810_DMA_CB(name)  void name(uint32_t src, uint32_t dst, int length, int byteswap)
#define LSI53C810_FETCH_CB(name)  uint32_t name(uint32_t dsp)
>>>>>>> upstream/master


class lsi53c810_device : public legacy_scsi_host_adapter
{
public:
<<<<<<< HEAD
	// construction/destruction
	lsi53c810_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	static void set_irq_callback(device_t &device, lsi53c810_irq_delegate callback) { downcast<lsi53c810_device &>(device).m_irq_cb = callback; }
	static void set_dma_callback(device_t &device, lsi53c810_dma_delegate callback) { downcast<lsi53c810_device &>(device).m_dma_cb = callback; }
	static void set_fetch_callback(device_t &device, lsi53c810_fetch_delegate callback) { downcast<lsi53c810_device &>(device).m_fetch_cb = callback; }

	void lsi53c810_read_data(int bytes, UINT8 *pData);
	void lsi53c810_write_data(int bytes, UINT8 *pData);

	UINT8 lsi53c810_reg_r( int offset );
	void lsi53c810_reg_w(int offset, UINT8 data);

protected:
	// device-level overrides
	virtual void device_start();
=======
	typedef device_delegate<void (int state)> irq_delegate;
	typedef device_delegate<void (uint32_t src, uint32_t dst, int length, int byteswap)> dma_delegate;
	typedef device_delegate<uint32_t (uint32_t dsp)> fetch_delegate;

	// construction/destruction
	lsi53c810_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	static void set_irq_callback(device_t &device, irq_delegate &&callback) { downcast<lsi53c810_device &>(device).m_irq_cb = std::move(callback); }
	static void set_dma_callback(device_t &device, dma_delegate &&callback) { downcast<lsi53c810_device &>(device).m_dma_cb = std::move(callback); }
	static void set_fetch_callback(device_t &device, fetch_delegate &&callback) { downcast<lsi53c810_device &>(device).m_fetch_cb = std::move(callback); }

	uint8_t reg_r(int offset);
	void reg_w(int offset, uint8_t data);

protected:
	// device-level overrides
	virtual void device_start() override;
>>>>>>> upstream/master

private:
	typedef delegate<void (void)> opcode_handler_delegate;
	opcode_handler_delegate dma_opcode[256];

<<<<<<< HEAD
	lsi53c810_irq_delegate m_irq_cb;
	lsi53c810_dma_delegate m_dma_cb;
	lsi53c810_fetch_delegate m_fetch_cb;

	UINT32 FETCH();
=======
	irq_delegate m_irq_cb;
	dma_delegate m_dma_cb;
	fetch_delegate m_fetch_cb;

	uint32_t FETCH();
>>>>>>> upstream/master
	void dmaop_invalid();
	void dmaop_move_memory();
	void dmaop_interrupt();
	void dmaop_block_move();
	void dmaop_select();
	void dmaop_wait_disconnect();
	void dmaop_wait_reselect();
	void dmaop_set();
	void dmaop_clear();
	void dmaop_move_from_sfbr();
	void dmaop_move_to_sfbr();
	void dmaop_read_modify_write();
	int scripts_compute_branch();
<<<<<<< HEAD
	UINT32 scripts_get_jump_dest();
=======
	uint32_t scripts_get_jump_dest();
>>>>>>> upstream/master
	void dmaop_jump();
	void dmaop_call();
	void dmaop_return();
	void dmaop_store();
	void dmaop_load();
	void dma_exec();
<<<<<<< HEAD
	void add_opcode(UINT8 op, UINT8 mask, opcode_handler_delegate handler);
	void lsi53c810_init();
	UINT32 lsi53c810_dasm_fetch(UINT32 pc);
	unsigned lsi53c810_dasm(char *buf, UINT32 pc);

	UINT8 last_id;

	UINT8 scntl0;
	UINT8 scntl1;
	UINT8 scntl2;
	UINT8 scntl3;
	UINT8 scid;
	UINT8 sxfer;
	UINT8 socl;
	UINT8 istat;
	UINT8 dstat;
	UINT8 sstat0;
	UINT8 sstat1;
	UINT8 sstat2;
	UINT8 dien;
	UINT8 dcntl;
	UINT8 dmode;
	UINT32 temp;
	UINT32 dsa;
	UINT32 dsp;
	UINT32 dsps;
	UINT32 dcmd;
	UINT8 sien0;
	UINT8 sien1;
	UINT8 stime0;
	UINT8 respid;
	UINT8 stest1;
	UINT8 scratch_a[4];
	UINT8 scratch_b[4];
=======
	void add_opcode(uint8_t op, uint8_t mask, opcode_handler_delegate handler);
	uint32_t lsi53c810_dasm_fetch(uint32_t pc);
	unsigned lsi53c810_dasm(char *buf, uint32_t pc);

	uint8_t scntl0;
	uint8_t scntl1;
	uint8_t scntl2;
	uint8_t scntl3;
	uint8_t scid;
	uint8_t sxfer;
	uint8_t socl;
	uint8_t istat;
	uint8_t dstat;
	uint8_t sstat0;
	uint8_t sstat1;
	uint8_t sstat2;
	uint8_t dien;
	uint8_t dcntl;
	uint8_t dmode;
	uint32_t temp;
	uint32_t dsa;
	uint32_t dsp;
	uint32_t dsps;
	uint32_t dcmd;
	uint8_t sien0;
	uint8_t sien1;
	uint8_t stime0;
	uint8_t respid;
	uint8_t stest1;
	uint8_t scratch_a[4];
	uint8_t scratch_b[4];
>>>>>>> upstream/master
	int dma_icount;
	int halted;
	int carry;
};

// device type definition
extern const device_type LSI53C810;
<<<<<<< HEAD


#define MCFG_LSI53C810_IRQ_CB(_class, _method) \
	lsi53c810_device::set_irq_callback(*device, lsi53c810_irq_delegate(&_class::_method, #_class "::" #_method, downcast<_class *>(owner)));

#define MCFG_LSI53C810_DMA_CB(_class, _method) \
	lsi53c810_device::set_dma_callback(*device, lsi53c810_dma_delegate(&_class::_method, #_class "::" #_method, downcast<_class *>(owner)));

#define MCFG_LSI53C810_FETCH_CB(_class, _method) \
	lsi53c810_device::set_fetch_callback(*device, lsi53c810_fetch_delegate(&_class::_method, #_class "::" #_method, downcast<_class *>(owner)));

#endif
=======
DECLARE_DEVICE_TYPE(LSI53C810, lsi53c810_device)


#define MCFG_LSI53C810_IRQ_CB(_class, _method) \
	lsi53c810_device::set_irq_callback(*device, lsi53c810_device::irq_delegate(&_class::_method, #_class "::" #_method, downcast<_class *>(owner)));

#define MCFG_LSI53C810_DMA_CB(_class, _method) \
	lsi53c810_device::set_dma_callback(*device, lsi53c810_device::dma_delegate(&_class::_method, #_class "::" #_method, downcast<_class *>(owner)));

#define MCFG_LSI53C810_FETCH_CB(_class, _method) \
	lsi53c810_device::set_fetch_callback(*device, lsi53c810_device::fetch_delegate(&_class::_method, #_class "::" #_method, downcast<_class *>(owner)));

#endif // MAME_MACHINE_53C810_H
>>>>>>> upstream/master
