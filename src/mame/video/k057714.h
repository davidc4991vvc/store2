// license:BSD-3-Clause
// copyright-holders:Ville Linde
<<<<<<< HEAD

#pragma once
#ifndef __K057714_H__
#define __K057714_H__
=======
#ifndef MAME_MACHINE_K057714_H
#define MAME_MACHINE_K057714_H

#pragma once

>>>>>>> upstream/master

class k057714_device : public device_t
{
public:
<<<<<<< HEAD
	k057714_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
	template<class _Object> static devcb_base &static_set_irq_callback(device_t &device, _Object object) { return downcast<k057714_device &>(device).m_irq.set_callback(object); }
=======
	k057714_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
	template <class Object> static devcb_base &static_set_irq_callback(device_t &device, Object &&cb) { return downcast<k057714_device &>(device).m_irq.set_callback(std::forward<Object>(cb)); }
>>>>>>> upstream/master

	int draw(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);

	DECLARE_READ32_MEMBER(read);
	DECLARE_WRITE32_MEMBER(write);
	DECLARE_WRITE32_MEMBER(fifo_w);

	struct framebuffer
	{
<<<<<<< HEAD
		UINT32 base;
=======
		uint32_t base;
>>>>>>> upstream/master
		int width;
		int height;
	};

protected:
<<<<<<< HEAD
	virtual void device_start();
	virtual void device_stop();
	virtual void device_reset();

private:
	void execute_command(UINT32 *cmd);
	void execute_display_list(UINT32 addr);
	void draw_object(UINT32 *cmd);
	void fill_rect(UINT32 *cmd);
	void draw_character(UINT32 *cmd);
	void fb_config(UINT32 *cmd);

	UINT32 *m_vram;
	UINT32 m_vram_read_addr;
	UINT32 m_vram_fifo0_addr;
	UINT32 m_vram_fifo1_addr;
	UINT32 m_vram_fifo0_mode;
	UINT32 m_vram_fifo1_mode;
	UINT32 m_command_fifo0[4];
	UINT32 m_command_fifo0_ptr;
	UINT32 m_command_fifo1[4];
	UINT32 m_command_fifo1_ptr;
	UINT32 m_ext_fifo_addr;
	UINT32 m_ext_fifo_count;
	UINT32 m_ext_fifo_line;
	UINT32 m_ext_fifo_num_lines;
	UINT32 m_ext_fifo_width;

	framebuffer m_frame[4];
	UINT32 m_fb_origin_x;
	UINT32 m_fb_origin_y;
=======
	virtual void device_start() override;
	virtual void device_stop() override;
	virtual void device_reset() override;

private:
	void execute_command(uint32_t *cmd);
	void execute_display_list(uint32_t addr);
	void draw_object(uint32_t *cmd);
	void fill_rect(uint32_t *cmd);
	void draw_character(uint32_t *cmd);
	void fb_config(uint32_t *cmd);

	std::unique_ptr<uint32_t[]> m_vram;
	uint32_t m_vram_read_addr;
	uint32_t m_vram_fifo0_addr;
	uint32_t m_vram_fifo1_addr;
	uint32_t m_vram_fifo0_mode;
	uint32_t m_vram_fifo1_mode;
	uint32_t m_command_fifo0[4];
	uint32_t m_command_fifo0_ptr;
	uint32_t m_command_fifo1[4];
	uint32_t m_command_fifo1_ptr;
	uint32_t m_ext_fifo_addr;
	uint32_t m_ext_fifo_count;
	uint32_t m_ext_fifo_line;
	uint32_t m_ext_fifo_num_lines;
	uint32_t m_ext_fifo_width;

	framebuffer m_frame[4];
	uint32_t m_fb_origin_x;
	uint32_t m_fb_origin_y;
>>>>>>> upstream/master

	devcb_write_line m_irq;
};

<<<<<<< HEAD
extern const device_type K057714;
=======
DECLARE_DEVICE_TYPE(K057714, k057714_device)
>>>>>>> upstream/master

#define MCFG_K057714_IRQ_CALLBACK(_devcb) \
	devcb = &k057714_device::static_set_irq_callback(*device, DEVCB_##_devcb);


<<<<<<< HEAD
#endif
=======
#endif // MAME_MACHINE_K057714_H
>>>>>>> upstream/master
