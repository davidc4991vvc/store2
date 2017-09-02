// license:BSD-3-Clause
// copyright-holders:David Haywood, ElSemi
/* Common device stuff for IGS025 / IGS022, should be split into devices for each chip once we know where what part does what */
<<<<<<< HEAD


=======
#ifndef MAME_MACHINE_IGS025_H
#define MAME_MACHINE_IGS025_H

#pragma once
>>>>>>> upstream/master

// used to connect the 022
typedef device_delegate<void (void)> igs025_execute_external;

#define MCFG_IGS025_SET_EXTERNAL_EXECUTE( _class, _method) \
<<<<<<< HEAD
	igs025_device::set_external_cb(*device, igs025_execute_external(&_class::_method, #_class "::" #_method, NULL, (_class *)0));
=======
	igs025_device::set_external_cb(*device, igs025_execute_external(&_class::_method, #_class "::" #_method, nullptr, (_class *)nullptr));
>>>>>>> upstream/master

class igs025_device : public device_t
{
public:
<<<<<<< HEAD
	igs025_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	DECLARE_READ16_MEMBER( olds_r );
	DECLARE_READ16_MEMBER( killbld_igs025_prot_r );
	// use setters instead of making public?
	const UINT8 (*m_kb_source_data)[0xec];
	UINT32 m_kb_game_id;
	UINT32 m_kb_region;
=======
	igs025_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	DECLARE_READ16_MEMBER( killbld_igs025_prot_r );
	// use setters instead of making public?
	const uint8_t (*m_kb_source_data)[0xec];
	uint32_t m_kb_game_id;
	uint32_t m_kb_region;
>>>>>>> upstream/master


	igs025_execute_external m_execute_external;
	static void set_external_cb(device_t &device,igs025_execute_external newcb);

	DECLARE_WRITE16_MEMBER( olds_w );
	DECLARE_WRITE16_MEMBER( drgw2_d80000_protection_w );
	DECLARE_WRITE16_MEMBER( killbld_igs025_prot_w);


protected:
<<<<<<< HEAD
	virtual void device_config_complete();
	virtual void device_validity_check(validity_checker &valid) const;
	virtual void device_start();
	virtual void device_reset();


	UINT16        m_kb_prot_hold;
	UINT16        m_kb_prot_hilo;
	UINT16        m_kb_prot_hilo_select;
=======
	virtual void device_start() override;
	virtual void device_reset() override;


	uint16_t        m_kb_prot_hold;
	uint16_t        m_kb_prot_hilo;
	uint16_t        m_kb_prot_hilo_select;
>>>>>>> upstream/master

	int           m_kb_cmd;
	int           m_kb_reg;
	int           m_kb_ptr;
<<<<<<< HEAD
	UINT8         m_kb_swap;
=======
	uint8_t         m_kb_swap;
>>>>>>> upstream/master

	void killbld_protection_calculate_hilo();
	void killbld_protection_calculate_hold(int y, int z);

	void no_callback_setup(void);


<<<<<<< HEAD
	UINT16        m_olds_bs;
	UINT16        m_kb_cmd3;
=======
	uint16_t        m_olds_bs;
	uint16_t        m_kb_cmd3;
>>>>>>> upstream/master

};


<<<<<<< HEAD

extern const device_type IGS025;
=======
DECLARE_DEVICE_TYPE(IGS025, igs025_device)

#endif // MAME_MACHINE_IGS025_H
>>>>>>> upstream/master
