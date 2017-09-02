// license:LGPL-2.1+
// copyright-holders:Angelo Salese
<<<<<<< HEAD
class nb1414m4_device : public device_t,
									public device_video_interface
{
public:
	nb1414m4_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
	~nb1414m4_device() {}

	void exec(UINT16 mcu_cmd, UINT8 *vram, UINT16 &scrollx, UINT16 &scrolly, tilemap_t *tilemap);

protected:
	// device-level overrides
	virtual void device_start();
	virtual void device_reset();

private:
	void dma(UINT16 src, UINT16 dst, UINT16 size, UINT8 condition, UINT8 *vram);
	void fill(UINT16 dst, UINT8 tile, UINT8 pal, UINT8 *vram);
	void insert_coin_msg(UINT8 *vram);
	void credit_msg(UINT8 *vram);
	void kozure_score_msg(UINT16 dst, UINT8 src_base, UINT8 *vram);
	void _0200(UINT16 mcu_cmd, UINT8 *vram);
	void _0600(UINT8 is2p, UINT8 *vram);
	void _0e00(UINT16 mcu_cmd, UINT8 *vram);

	UINT8 *m_data;

};

extern const device_type NB1414M4;
=======
#ifndef MAME_INCLUDES_NB1414M4_H
#define MAME_INCLUDES_NB1414M4_H

#pragma once

class nb1414m4_device : public device_t, public device_video_interface
{
public:
	nb1414m4_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	void exec(uint16_t mcu_cmd, uint8_t *vram, uint16_t &scrollx, uint16_t &scrolly, tilemap_t *tilemap);

protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;

private:
	void dma(uint16_t src, uint16_t dst, uint16_t size, uint8_t condition, uint8_t *vram);
	void fill(uint16_t dst, uint8_t tile, uint8_t pal, uint8_t *vram);
	void insert_coin_msg(uint8_t *vram);
	void credit_msg(uint8_t *vram);
	void kozure_score_msg(uint16_t dst, uint8_t src_base, uint8_t *vram);
	void _0200(uint16_t mcu_cmd, uint8_t *vram);
	void _0600(uint8_t is2p, uint8_t *vram);
	void _0e00(uint16_t mcu_cmd, uint8_t *vram);

	required_region_ptr<uint8_t> m_data;

};

DECLARE_DEVICE_TYPE(NB1414M4, nb1414m4_device)

#endif // MAME_INCLUDES_NB1414M4_H
>>>>>>> upstream/master
