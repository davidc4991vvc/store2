// license:BSD-3-Clause
// copyright-holders:Fabio Priuli
<<<<<<< HEAD
#ifndef __ASTROCADE_EXP_H
#define __ASTROCADE_EXP_H
=======
#ifndef MAME_BUS_ASTROCADE_EXP_H
#define MAME_BUS_ASTROCADE_EXP_H
>>>>>>> upstream/master

// ======================> device_astrocade_card_interface

class device_astrocade_card_interface : public device_slot_card_interface
{
public:
	// construction/destruction
<<<<<<< HEAD
	device_astrocade_card_interface(const machine_config &mconfig, device_t &device);
=======
>>>>>>> upstream/master
	virtual ~device_astrocade_card_interface();

	// reading and writing
	virtual DECLARE_READ8_MEMBER(read) { return 0xff; }
<<<<<<< HEAD
	virtual DECLARE_WRITE8_MEMBER(write) {}

protected:
=======
	virtual DECLARE_WRITE8_MEMBER(write) { }

protected:
	device_astrocade_card_interface(const machine_config &mconfig, device_t &device);
>>>>>>> upstream/master
};


// ======================> astrocade_exp_device

<<<<<<< HEAD
class astrocade_exp_device : public device_t,
								public device_slot_interface
{
public:
	// construction/destruction
	astrocade_exp_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
	virtual ~astrocade_exp_device();

	// device-level overrides
	virtual void device_start();
=======
class astrocade_exp_device : public device_t, public device_slot_interface
{
public:
	// construction/destruction
	astrocade_exp_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
	virtual ~astrocade_exp_device();

	// device-level overrides
	virtual void device_start() override;
>>>>>>> upstream/master

	bool get_card_mounted() { return m_card_mounted; }

	// reading and writing
	virtual DECLARE_READ8_MEMBER(read);
	virtual DECLARE_WRITE8_MEMBER(write);

protected:
	bool m_card_mounted;
	device_astrocade_card_interface* m_card;
};



// device type definition
<<<<<<< HEAD
extern const device_type ASTROCADE_EXP_SLOT;
=======
DECLARE_DEVICE_TYPE(ASTROCADE_EXP_SLOT, astrocade_exp_device)
>>>>>>> upstream/master


#define MCFG_ASTROCADE_EXPANSION_SLOT_ADD(_tag, _slot_intf, _def_slot) \
	MCFG_DEVICE_ADD(_tag, ASTROCADE_EXP_SLOT, 0) \
	MCFG_DEVICE_SLOT_INTERFACE(_slot_intf, _def_slot, false)

<<<<<<< HEAD
#endif
=======
#endif // MAME_BUS_ASTROCADE_EXP_H
>>>>>>> upstream/master
