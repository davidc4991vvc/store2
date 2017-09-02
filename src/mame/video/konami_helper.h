// license:BSD-3-Clause
// copyright-holders:David Haywood
/* Konami video helper functions */

#pragma once
#ifndef __KONAMI_HELPER_H__
#define __KONAMI_HELPER_H__

<<<<<<< HEAD
void konami_decode_gfx(running_machine &machine, gfxdecode_device * gfxdecode, palette_device &palette, int gfx_index, UINT8 *data, UINT32 total, const gfx_layout *layout, int bpp);
=======
void konami_decode_gfx(device_gfx_interface &gfxdecode, int gfx_index, uint8_t *data, uint32_t total, const gfx_layout *layout, int bpp);
>>>>>>> upstream/master

/* helper function to sort three tile layers by priority order */
void konami_sortlayers3(int *layer, int *pri);
/* helper function to sort four tile layers by priority order */
void konami_sortlayers4(int *layer, int *pri);
/* helper function to sort five tile layers by priority order */
void konami_sortlayers5(int *layer, int *pri);

#endif
