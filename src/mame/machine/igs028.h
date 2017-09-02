// license:BSD-3-Clause
// copyright-holders:David Haywood, ElSemi
/* IGS 028 */
<<<<<<< HEAD

=======
#ifndef MAME_MACHINE_IGS028_H
#define MAME_MACHINE_IGS028_H

#pragma once
>>>>>>> upstream/master


class igs028_device : public device_t
{
public:
<<<<<<< HEAD
	igs028_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	UINT16* m_sharedprotram;
=======
	igs028_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	uint16_t* m_sharedprotram;
>>>>>>> upstream/master

	void IGS028_handle(void);

protected:
<<<<<<< HEAD
	virtual void device_config_complete();
	virtual void device_validity_check(validity_checker &valid) const;
	virtual void device_start();
	virtual void device_reset();

	UINT32 olds_prot_addr(UINT16 addr);
	UINT32 olds_read_reg(UINT16 addr);
	void olds_write_reg( UINT16 addr, UINT32 val );
	void IGS028_do_dma(UINT16 src, UINT16 dst, UINT16 size, UINT16 mode);
};



extern const device_type IGS028;
=======
	virtual void device_start() override;
	virtual void device_reset() override;

	uint32_t olds_prot_addr(uint16_t addr);
	uint32_t olds_read_reg(uint16_t addr);
	void olds_write_reg( uint16_t addr, uint32_t val );
	void IGS028_do_dma(uint16_t src, uint16_t dst, uint16_t size, uint16_t mode);
};


DECLARE_DEVICE_TYPE(IGS028, igs028_device)

#endif // MAME_MACHINE_IGS028_H
>>>>>>> upstream/master
