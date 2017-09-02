// license:BSD-3-Clause
// copyright-holders:Ville Linde
/*********************************************************

    Konami 056800 MIRAC sound interface

*********************************************************/

<<<<<<< HEAD
#ifndef __K056800_H__
#define __K056800_H__
=======
#ifndef MAME_SOUND_K056800_H
#define MAME_SOUND_K056800_H
>>>>>>> upstream/master


/***************************************************************************
    DEVICE CONFIGURATION MACROS
***************************************************************************/

<<<<<<< HEAD
#define MCFG_K056800_ADD(_tag, _clock) \
	MCFG_DEVICE_ADD(_tag, K056800, _clock)
#define MCFG_K056800_INT_HANDLER(_devcb) \
	devcb = &k056800_device::set_int_handler(*device, DEVCB_##_devcb);
=======
#define MCFG_K056800_ADD(tag, clock) \
		MCFG_DEVICE_ADD((tag), K056800, (clock))

#define MCFG_K056800_INT_HANDLER(cb) \
		devcb = &k056800_device::set_int_handler(*device, (DEVCB_##cb));
>>>>>>> upstream/master



/***************************************************************************
    TYPE DEFINITIONS
***************************************************************************/

class k056800_device : public device_t
{
public:
	// construction/destruction
<<<<<<< HEAD
	k056800_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// static configuration helpers
	template<class _Object> static devcb_base &set_int_handler(device_t &device, _Object object) { return downcast<k056800_device &>(device).m_int_handler.set_callback(object); }
=======
	k056800_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// static configuration helpers
	template <class Object> static devcb_base &set_int_handler(device_t &device, Object &&cb) { return downcast<k056800_device &>(device).m_int_handler.set_callback(std::forward<Object>(cb)); }
>>>>>>> upstream/master

	DECLARE_READ8_MEMBER( host_r );
	DECLARE_WRITE8_MEMBER( host_w );
	DECLARE_READ8_MEMBER( sound_r );
	DECLARE_WRITE8_MEMBER( sound_w );

protected:
	// device-level overrides
<<<<<<< HEAD
	virtual void device_start();
	virtual void device_reset();
=======
	virtual void device_start() override;
	virtual void device_reset() override;
>>>>>>> upstream/master

private:
	// internal state
	bool                m_int_pending;
	bool                m_int_enabled;
<<<<<<< HEAD
	UINT8               m_host_to_snd_regs[4];
	UINT8               m_snd_to_host_regs[2];
=======
	uint8_t               m_host_to_snd_regs[4];
	uint8_t               m_snd_to_host_regs[2];
>>>>>>> upstream/master

	devcb_write_line   m_int_handler;
};

<<<<<<< HEAD
extern const device_type K056800;



#endif /* __K056800_H__ */
=======
DECLARE_DEVICE_TYPE(K056800, k056800_device)

#endif // MAME_SOUND_K056800_H
>>>>>>> upstream/master
