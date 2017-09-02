// license:BSD-3-Clause
// copyright-holders:Nicola Salmoria
<<<<<<< HEAD
#ifndef _TC0110PCR_H_
#define _TC0110PCR_H_
=======
#ifndef MAME_VIDEO_TC0110PCR_H
#define MAME_VIDEO_TC0110PCR_H

#pragma once
>>>>>>> upstream/master


class tc0110pcr_device : public device_t
{
public:
<<<<<<< HEAD
	tc0110pcr_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
	~tc0110pcr_device() {}
=======
	tc0110pcr_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
>>>>>>> upstream/master

	DECLARE_READ16_MEMBER( word_r );
	DECLARE_WRITE16_MEMBER( word_w ); /* color index goes up in step of 2 */
	DECLARE_WRITE16_MEMBER( step1_word_w );   /* color index goes up in step of 1 */
	DECLARE_WRITE16_MEMBER( step1_rbswap_word_w );    /* swaps red and blue components */
	DECLARE_WRITE16_MEMBER( step1_4bpg_word_w );  /* only 4 bits per color gun */

	void restore_colors();

	static void static_set_palette_tag(device_t &device, const char *tag);

protected:
	// device-level overrides
<<<<<<< HEAD
	virtual void device_start();
	virtual void device_reset();

private:
	UINT16 *     m_ram;
=======
	virtual void device_start() override;
	virtual void device_reset() override;

private:
	std::unique_ptr<uint16_t[]>     m_ram;
>>>>>>> upstream/master
	int          m_type;
	int          m_addr;
	required_device<palette_device> m_palette;
};

<<<<<<< HEAD
extern const device_type TC0110PCR;
=======
DECLARE_DEVICE_TYPE(TC0110PCR, tc0110pcr_device)
>>>>>>> upstream/master

#define MCFG_TC0110PCR_ADD(_tag) \
	MCFG_DEVICE_ADD(_tag, TC0110PCR, 0)
#define MCFG_TC0110PCR_PALETTE(_palette_tag) \
	tc0110pcr_device::static_set_palette_tag(*device, "^" _palette_tag);

<<<<<<< HEAD
#endif
=======
#endif // MAME_VIDEO_TC0110PCR_H
>>>>>>> upstream/master
