// license:LGPL-2.1+
// copyright-holders:Angelo Salese
/***************************************************************************

    Seibu CRTC device

***************************************************************************/

<<<<<<< HEAD
#pragma once

#ifndef __SEIBU_CRTCDEV_H__
#define __SEIBU_CRTCDEV_H__
=======
#ifndef MAME_VIDEO_SEIBU_CRTC_H
#define MAME_VIDEO_SEIBU_CRTC_H

#pragma once
>>>>>>> upstream/master


//**************************************************************************
//  INTERFACE CONFIGURATION MACROS
//**************************************************************************

<<<<<<< HEAD
=======
#define MCFG_SEIBU_CRTC_DECRYPT_KEY_CB(_devcb) \
	devcb = &seibu_crtc_device::set_decrypt_key_callback(*device, DEVCB_##_devcb);

>>>>>>> upstream/master
#define MCFG_SEIBU_CRTC_LAYER_EN_CB(_devcb) \
	devcb = &seibu_crtc_device::set_layer_en_callback(*device, DEVCB_##_devcb);

#define MCFG_SEIBU_CRTC_LAYER_SCROLL_CB(_devcb) \
	devcb = &seibu_crtc_device::set_layer_scroll_callback(*device, DEVCB_##_devcb);

<<<<<<< HEAD
=======
#define MCFG_SEIBU_CRTC_LAYER_SCROLL_BASE_CB(_devcb) \
	devcb = &seibu_crtc_device::set_layer_scroll_base_callback(*device, DEVCB_##_devcb);

#define MCFG_SEIBU_CRTC_REG_1A_CB(_devcb) \
	devcb = &seibu_crtc_device::set_reg_1a_callback(*device, DEVCB_##_devcb);

>>>>>>> upstream/master

//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

// ======================> seibu_crtc_device

class seibu_crtc_device : public device_t,
							public device_memory_interface,
							public device_video_interface
{
public:
	// construction/destruction
<<<<<<< HEAD
	seibu_crtc_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	template<class _Object> static devcb_base &set_layer_en_callback(device_t &device, _Object object) { return downcast<seibu_crtc_device &>(device).m_layer_en_cb.set_callback(object); }
	template<class _Object> static devcb_base &set_layer_scroll_callback(device_t &device, _Object object) { return downcast<seibu_crtc_device &>(device).m_layer_scroll_cb.set_callback(object); }
=======
	seibu_crtc_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	template <class Object> static devcb_base &set_decrypt_key_callback(device_t &device, Object &&cb) { return downcast<seibu_crtc_device &>(device).m_decrypt_key_cb.set_callback(std::forward<Object>(cb)); }
	template <class Object> static devcb_base &set_layer_en_callback(device_t &device, Object &&cb) { return downcast<seibu_crtc_device &>(device).m_layer_en_cb.set_callback(std::forward<Object>(cb)); }
	template <class Object> static devcb_base &set_layer_scroll_callback(device_t &device, Object &&cb) { return downcast<seibu_crtc_device &>(device).m_layer_scroll_cb.set_callback(std::forward<Object>(cb)); }
	template <class Object> static devcb_base &set_reg_1a_callback(device_t &device, Object &&cb) { return downcast<seibu_crtc_device &>(device).m_reg_1a_cb.set_callback(std::forward<Object>(cb)); }
	template <class Object> static devcb_base &set_layer_scroll_base_callback(device_t &device, Object &&cb) { return downcast<seibu_crtc_device &>(device).m_layer_scroll_base_cb.set_callback(std::forward<Object>(cb)); }
>>>>>>> upstream/master

	// I/O operations
	DECLARE_WRITE16_MEMBER( write );
	DECLARE_WRITE16_MEMBER( write_alt );
<<<<<<< HEAD
	DECLARE_WRITE16_MEMBER( write_xor );
	DECLARE_READ16_MEMBER( read );
	DECLARE_READ16_MEMBER( read_alt );
	DECLARE_READ16_MEMBER( read_xor );
	DECLARE_WRITE16_MEMBER(layer_en_w);
	DECLARE_WRITE16_MEMBER(layer_scroll_w);

protected:
	// device-level overrides
	virtual void device_validity_check(validity_checker &valid) const;
	virtual void device_start();
	virtual void device_reset();
	virtual const address_space_config *memory_space_config(address_spacenum spacenum = AS_0) const;

private:
	devcb_write16       m_layer_en_cb;
	devcb_write16       m_layer_scroll_cb;
	const address_space_config      m_space_config;
	inline UINT16 read_word(offs_t address);
	inline void write_word(offs_t address, UINT16 data);
=======
	DECLARE_READ16_MEMBER( read );
	DECLARE_READ16_MEMBER( read_alt );
	DECLARE_WRITE16_MEMBER(decrypt_key_w);
	DECLARE_WRITE16_MEMBER(layer_en_w);
	DECLARE_READ16_MEMBER(reg_1a_r);
	DECLARE_WRITE16_MEMBER(reg_1a_w);
	DECLARE_WRITE16_MEMBER(layer_scroll_w);
	DECLARE_WRITE16_MEMBER(layer_scroll_base_w);

protected:
	// device-level overrides
	virtual void device_validity_check(validity_checker &valid) const override;
	virtual void device_start() override;
	virtual void device_reset() override;
	virtual space_config_vector memory_space_config() const override;

private:
	devcb_write16       m_decrypt_key_cb;
	devcb_write16       m_layer_en_cb;
	devcb_write16       m_layer_scroll_cb;
	devcb_write16       m_reg_1a_cb;
	devcb_write16       m_layer_scroll_base_cb;
	const address_space_config      m_space_config;
	inline uint16_t read_word(offs_t address);
	inline void write_word(offs_t address, uint16_t data);

	uint16_t m_reg_1a;
>>>>>>> upstream/master
};


// device type definition
<<<<<<< HEAD
extern const device_type SEIBU_CRTC;

#endif
=======
DECLARE_DEVICE_TYPE(SEIBU_CRTC, seibu_crtc_device)

#endif // MAME_VIDEO_SEIBU_CRTC_H
>>>>>>> upstream/master
