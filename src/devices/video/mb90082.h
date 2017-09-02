// license:LGPL-2.1+
// copyright-holders:Angelo Salese
/***************************************************************************

 Fujitsu MB90082 OSD

***************************************************************************/

<<<<<<< HEAD
#pragma once

#ifndef __MB90082DEV_H__
#define __MB90082DEV_H__
=======
#ifndef MAME_VIDEO_MB90082DEV_H
#define MAME_VIDEO_MB90082DEV_H

#pragma once
>>>>>>> upstream/master



//**************************************************************************
//  INTERFACE CONFIGURATION MACROS
//**************************************************************************

#define MCFG_MB90082_ADD(_tag,_freq) \
	MCFG_DEVICE_ADD(_tag, MB90082, _freq)

//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

<<<<<<< HEAD
enum
{
	OSD_COMMAND = 0,
	OSD_DATA
};

=======
>>>>>>> upstream/master

// ======================> mb90082_device

class mb90082_device :  public device_t,
						public device_memory_interface
{
public:
	// construction/destruction
<<<<<<< HEAD
	mb90082_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
=======
	mb90082_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
>>>>>>> upstream/master

	// I/O operations
	DECLARE_WRITE8_MEMBER( write );
	DECLARE_WRITE_LINE_MEMBER( set_cs_line );

<<<<<<< HEAD
	UINT32 screen_update(screen_device &screen, bitmap_rgb32 &bitmap, const rectangle &cliprect);
	virtual const rom_entry *device_rom_region() const;

protected:
	// device-level overrides
	virtual void device_validity_check(validity_checker &valid) const;
	virtual void device_start();
	virtual void device_reset();
	virtual const address_space_config *memory_space_config(address_spacenum spacenum = AS_0) const;

private:
	UINT8 m_cmd_ff;
	UINT8 m_cmd,m_cmd_param;
	UINT8 m_reset_line;

	UINT16 m_osd_addr;
	UINT8 m_fil;
	UINT8 m_uc;
	UINT8 m_attr;

	inline UINT16 read_word(offs_t address);
	inline void write_word(offs_t address, UINT16 data);
=======
	uint32_t screen_update(screen_device &screen, bitmap_rgb32 &bitmap, const rectangle &cliprect);
	virtual const tiny_rom_entry *device_rom_region() const override;

protected:
	// device-level overrides
	virtual void device_validity_check(validity_checker &valid) const override;
	virtual void device_start() override;
	virtual void device_reset() override;
	virtual space_config_vector memory_space_config() const override;

private:
	enum
	{
		OSD_COMMAND = 0,
		OSD_DATA
	};

	uint8_t m_cmd_ff;
	uint8_t m_cmd,m_cmd_param;
	uint8_t m_reset_line;

	uint16_t m_osd_addr;
	uint8_t m_fil;
	uint8_t m_uc;
	uint8_t m_attr;

	inline uint16_t read_word(offs_t address);
	inline void write_word(offs_t address, uint16_t data);
>>>>>>> upstream/master

	const address_space_config      m_space_config;
};


// device type definition
<<<<<<< HEAD
extern const device_type MB90082;



//**************************************************************************
//  GLOBAL VARIABLES
//**************************************************************************



#endif
=======
DECLARE_DEVICE_TYPE(MB90082, mb90082_device)

#endif // MAME_VIDEO_MB90082DEV_H
>>>>>>> upstream/master
