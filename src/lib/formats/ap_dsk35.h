// license:BSD-3-Clause
// copyright-holders:Nathan Woods, R. Belmont
/*********************************************************************

    ap_dsk35.h

    Apple 3.5" disk images

*********************************************************************/

#ifndef AP_DSK35_H
#define AP_DSK35_H

#include "flopimg.h"

<<<<<<< HEAD
void sony_filltrack(UINT8 *buffer, size_t buffer_len, size_t *pos, UINT8 data);
UINT8 sony_fetchtrack(const UINT8 *buffer, size_t buffer_len, size_t *pos);
=======
void sony_filltrack(uint8_t *buffer, size_t buffer_len, size_t *pos, uint8_t data);
uint8_t sony_fetchtrack(const uint8_t *buffer, size_t buffer_len, size_t *pos);
>>>>>>> upstream/master

int apple35_sectors_per_track(floppy_image_legacy *image, int track);

/**************************************************************************/

LEGACY_FLOPPY_OPTIONS_EXTERN(apple35_mac);
LEGACY_FLOPPY_OPTIONS_EXTERN(apple35_iigs);

class dc42_format : public floppy_image_format_t
{
public:
	dc42_format();

<<<<<<< HEAD
	virtual int identify(io_generic *io, UINT32 form_factor);
	virtual bool load(io_generic *io, UINT32 form_factor, floppy_image *image);
	virtual bool save(io_generic *io, floppy_image *image);

	virtual const char *name() const;
	virtual const char *description() const;
	virtual const char *extensions() const;
	virtual bool supports_save() const;
=======
	virtual int identify(io_generic *io, uint32_t form_factor) override;
	virtual bool load(io_generic *io, uint32_t form_factor, floppy_image *image) override;
	virtual bool save(io_generic *io, floppy_image *image) override;

	virtual const char *name() const override;
	virtual const char *description() const override;
	virtual const char *extensions() const override;
	virtual bool supports_save() const override;
>>>>>>> upstream/master

private:
	static const desc_e mac_gcr[];

<<<<<<< HEAD
	UINT8 gb(const UINT8 *buf, int ts, int &pos, int &wrap);
	void update_chk(const UINT8 *data, int size, UINT32 &chk);
=======
	uint8_t gb(const uint8_t *buf, int ts, int &pos, int &wrap);
	void update_chk(const uint8_t *data, int size, uint32_t &chk);
>>>>>>> upstream/master
};

extern const floppy_format_type FLOPPY_DC42_FORMAT;

#endif /* AP_DSK35_H */
