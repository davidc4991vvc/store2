// license:BSD-3-Clause
// copyright-holders:Ville Linde, Nicola Salmoria

<<<<<<< HEAD
// TODO: modernize code (spisprit.c too)

UINT32 partial_carry_sum32(UINT32 add1,UINT32 add2,UINT32 carry_mask);

void seibuspi_text_decrypt(UINT8 *rom);
void seibuspi_bg_decrypt(UINT8 *rom, int size);

void seibuspi_rise10_text_decrypt(UINT8 *rom);
void seibuspi_rise10_bg_decrypt(UINT8 *rom, int size);
void seibuspi_rise10_sprite_decrypt(UINT8 *rom, int romsize);

void seibuspi_rise11_text_decrypt(UINT8 *rom);
void seibuspi_rise11_bg_decrypt(UINT8 *rom, int size);
void seibuspi_rise11_sprite_decrypt_rfjet(UINT8 *rom, int romsize);
void seibuspi_rise11_sprite_decrypt_feversoc(UINT8 *rom, int romsize);
=======
// TODO: modernize code

uint32_t partial_carry_sum32(uint32_t add1,uint32_t add2,uint32_t carry_mask);
uint32_t partial_carry_sum24(uint32_t add1,uint32_t add2,uint32_t carry_mask);

void seibuspi_sprite_decrypt(uint8_t *src, int romsize);
void seibuspi_rise10_sprite_decrypt(uint8_t *rom, int romsize);
void seibuspi_rise11_sprite_decrypt_rfjet(uint8_t *rom, int romsize);
void seibuspi_rise11_sprite_decrypt_feversoc(uint8_t *rom, int romsize);
>>>>>>> upstream/master
