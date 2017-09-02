// license:GPL-2.0+
// copyright-holders:Juergen Buchmueller
/*
    ataridev.h

*/

<<<<<<< HEAD
#ifndef _ATARIFDC_H
#define _ATARIFDC_H
=======
#ifndef MAME_MACHINE_ATARIFDC_H
#define MAME_MACHINE_ATARIFDC_H
>>>>>>> upstream/master

#include "imagedev/flopdrv.h"

class atari_fdc_device : public device_t
{
public:
<<<<<<< HEAD
	atari_fdc_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
=======
	atari_fdc_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
>>>>>>> upstream/master

	DECLARE_READ8_MEMBER( serin_r );
	DECLARE_WRITE8_MEMBER( serout_w );
	DECLARE_WRITE_LINE_MEMBER( pia_cb2_w );
<<<<<<< HEAD
	void atari_load_proc(device_image_interface &image);

protected:
	// device-level overrides
	virtual void device_start();
	virtual machine_config_constructor device_mconfig_additions() const;
=======
	void atari_load_proc(device_image_interface &image, bool is_created);

protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_add_mconfig(machine_config &config) override;
>>>>>>> upstream/master

private:
	void clr_serout(int expect_data);
	void add_serout(int expect_data);
	void clr_serin(int ser_delay);
<<<<<<< HEAD
	void add_serin(UINT8 data, int with_checksum);
=======
	void add_serin(uint8_t data, int with_checksum);
>>>>>>> upstream/master
	void a800_serial_command();
	void a800_serial_write();
	legacy_floppy_image_device *atari_floppy_get_device_child(int drive);

	struct atari_drive
	{
<<<<<<< HEAD
		UINT8 *image;       /* alloc'd image */
=======
		std::unique_ptr<uint8_t[]> image;       /* alloc'd image */
>>>>>>> upstream/master
		int type;           /* type of image (XFD, ATR, DSK) */
		int mode;           /* 0 read only, != 0 read/write */
		int density;        /* 0 SD, 1 MD, 2 DD */
		int header_skip;    /* number of bytes in format header */
		int tracks;         /* number of tracks (35,40,77,80) */
		int heads;          /* number of heads (1,2) */
		int spt;            /* sectors per track (18,26) */
		int seclen;         /* sector length (128,256) */
		int bseclen;        /* boot sector length (sectors 1..3) */
		int sectors;        /* total sectors, ie. tracks x heads x spt */
	};

	int  m_serout_count;
	int  m_serout_offs;
<<<<<<< HEAD
	UINT8 m_serout_buff[512];
	UINT8 m_serout_chksum;
=======
	uint8_t m_serout_buff[512];
	uint8_t m_serout_chksum;
>>>>>>> upstream/master
//  int  m_serout_delay;

	int  m_serin_count;
	int  m_serin_offs;
<<<<<<< HEAD
	UINT8 m_serin_buff[512];
	UINT8 m_serin_chksum;
=======
	uint8_t m_serin_buff[512];
	uint8_t m_serin_chksum;
>>>>>>> upstream/master
	int  m_serin_delay;

	atari_drive m_drv[4];
};

<<<<<<< HEAD
extern const device_type ATARI_FDC;

#endif /* _ATARIFDC_H */
=======
DECLARE_DEVICE_TYPE(ATARI_FDC, atari_fdc_device)

#endif // MAME_MACHINE_ATARIFDC_H
>>>>>>> upstream/master
