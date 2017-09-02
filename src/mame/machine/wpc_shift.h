// license:BSD-3-Clause
// copyright-holders:Olivier Galibert

// Williams Pinball Controller Shift-based protection simulation

<<<<<<< HEAD
#ifndef WPC_SHIFT_H
#define WPC_SHIFT_H
=======
#ifndef MAME_MACHINE_WPC_SHIFT_H
#define MAME_MACHINE_WPC_SHIFT_H
>>>>>>> upstream/master

#define MCFG_WPC_SHIFT_ADD( _tag ) \
	MCFG_DEVICE_ADD( _tag, WPC_SHIFT, 0 )

class wpc_shift_device : public device_t
{
public:
<<<<<<< HEAD
	wpc_shift_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
=======
	wpc_shift_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
>>>>>>> upstream/master
	virtual ~wpc_shift_device();

	DECLARE_ADDRESS_MAP(registers, 8);

	DECLARE_READ8_MEMBER(adrh_r);
	DECLARE_WRITE8_MEMBER(adrh_w);
	DECLARE_READ8_MEMBER(adrl_r);
	DECLARE_WRITE8_MEMBER(adrl_w);
	DECLARE_READ8_MEMBER(val1_r);
	DECLARE_WRITE8_MEMBER(val1_w);
	DECLARE_READ8_MEMBER(val2_r);
	DECLARE_WRITE8_MEMBER(val2_w);

protected:
<<<<<<< HEAD
	UINT16 adr;
	UINT8 val1, val2;

	virtual void device_start();
	virtual void device_reset();
};

extern const device_type WPC_SHIFT;

#endif
=======
	uint16_t adr;
	uint8_t val1, val2;

	virtual void device_start() override;
	virtual void device_reset() override;
};

DECLARE_DEVICE_TYPE(WPC_SHIFT, wpc_shift_device)

#endif // MAME_MACHINE_WPC_SHIFT_H
>>>>>>> upstream/master
