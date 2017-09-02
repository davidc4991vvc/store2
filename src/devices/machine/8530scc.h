// license:BSD-3-Clause
// copyright-holders:R. Belmont
/*********************************************************************

    8530scc.h

    Zilog 8530 SCC (Serial Control Chip) code

*********************************************************************/

<<<<<<< HEAD
#ifndef __8530SCC_H__
#define __8530SCC_H__
=======
#ifndef MAME_MACHINE_8530SCC_H
#define MAME_MACHINE_8530SCC_H
>>>>>>> upstream/master

#define MCFG_Z8530_INTRQ_CALLBACK(_write) \
	devcb = &scc8530_t::set_intrq_wr_callback(*device, DEVCB_##_write);

class scc8530_t : public device_t
{
public:
	enum IRQType_t {
		IRQ_NONE,
		IRQ_A_RX,
		IRQ_A_RX_SPECIAL,
		IRQ_B_RX,
		IRQ_B_RX_SPECIAL,
		IRQ_A_TX,
		IRQ_B_TX,
		IRQ_A_EXT,
		IRQ_B_EXT
	};

<<<<<<< HEAD
	scc8530_t(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	template<class _Object> static devcb_base &set_intrq_wr_callback(device_t &device, _Object object) { return downcast<scc8530_t &>(device).intrq_cb.set_callback(object); }

	UINT8 get_reg_a(int reg);
	UINT8 get_reg_b(int reg);
	void set_reg_a(int reg, UINT8 data);
	void set_reg_b(int reg, UINT8 data);
=======
	scc8530_t(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	template <class Object> static devcb_base &set_intrq_wr_callback(device_t &device, Object &&cb) { return downcast<scc8530_t &>(device).intrq_cb.set_callback(std::forward<Object>(cb)); }

	uint8_t get_reg_a(int reg);
	uint8_t get_reg_b(int reg);
	void set_reg_a(int reg, uint8_t data);
	void set_reg_b(int reg, uint8_t data);
>>>>>>> upstream/master

	void set_status(int status);

	DECLARE_READ8_MEMBER(reg_r);
	DECLARE_WRITE8_MEMBER(reg_w);

<<<<<<< HEAD
protected:
	virtual void device_start();
	virtual void device_reset();
	virtual void device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr);
=======
	void write_reg(int offset, uint8_t data);
	uint8_t read_reg(int offset);

protected:
	virtual void device_start() override;
	virtual void device_reset() override;
	virtual void device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr) override;
>>>>>>> upstream/master

private:
	struct Chan {
		bool txIRQEnable;
		bool rxIRQEnable;
		bool extIRQEnable;
		bool baudIRQEnable;
		bool txIRQPending;
		bool rxIRQPending;
		bool extIRQPending;
		bool baudIRQPending;
		bool txEnable;
		bool rxEnable;
		bool txUnderrun;
		bool txUnderrunEnable;
		bool syncHunt;
		bool DCDEnable;
		bool CTSEnable;
<<<<<<< HEAD
		UINT8 rxData;
		UINT8 txData;

		emu_timer *baudtimer;

		UINT8 reg_val[16];
=======
		uint8_t rxData;
		uint8_t txData;

		emu_timer *baudtimer;

		uint8_t reg_val[16];
>>>>>>> upstream/master
	};

	int mode;
	int reg;
	int status;
	int IRQV;
	int MasterIRQEnable;
	int lastIRQStat;
	IRQType_t IRQType;

	Chan channel[2];

	devcb_write_line intrq_cb;

	void updateirqs();
	void initchannel(int ch);
	void resetchannel(int ch);
	void acknowledge();
<<<<<<< HEAD
	UINT8 getareg();
	UINT8 getbreg();
	void putreg(int ch, UINT8 data);
=======
	uint8_t getareg();
	uint8_t getbreg();
	void putreg(int ch, uint8_t data);
>>>>>>> upstream/master
};

/***************************************************************************
    MACROS
***************************************************************************/

<<<<<<< HEAD
extern const device_type SCC8530;

#endif /* __8530SCC_H__ */
=======
DECLARE_DEVICE_TYPE(SCC8530, scc8530_t)

#endif // MAME_MACHINE_8530SCC_H
>>>>>>> upstream/master
