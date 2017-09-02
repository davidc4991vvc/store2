// license:BSD-3-Clause
// copyright-holders:Olivier Galibert, R. Belmont
/*********************************************************************

    formats/concept_dsk.h

    Formats for Corvus Concept

*********************************************************************/

#ifndef CONCEPT_DSK_H_
#define CONCEPT_DSK_H_

#include "flopimg.h"

class cc525dsdd_format : public floppy_image_format_t
{
public:
	cc525dsdd_format();

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

	static const desc_e cc_9_desc[];

private:
<<<<<<< HEAD
	void find_size(io_generic *io, UINT8 &track_count, UINT8 &head_count, UINT8 &sector_count);
=======
	void find_size(io_generic *io, uint8_t &track_count, uint8_t &head_count, uint8_t &sector_count);
>>>>>>> upstream/master
};

extern const floppy_format_type FLOPPY_CONCEPT_525DSDD_FORMAT;

#endif /* CONCEPT_DSK_H_ */
