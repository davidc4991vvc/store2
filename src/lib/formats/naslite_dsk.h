// license:BSD-3-Clause
// copyright-holders:Curt Coder
/*********************************************************************

    formats/naslite_dsk.h

    NASLite 1.72MB with funky interleaving format

*********************************************************************/

#ifndef NASLITE_DSK_H_
#define NASLITE_DSK_H_

#include "upd765_dsk.h"

class naslite_format : public upd765_format {
public:
	naslite_format();

<<<<<<< HEAD
	virtual const char *name() const;
	virtual const char *description() const;
	virtual const char *extensions() const;
=======
	virtual const char *name() const override;
	virtual const char *description() const override;
	virtual const char *extensions() const override;
>>>>>>> upstream/master

protected:
	static const format formats[];

<<<<<<< HEAD
	virtual void build_sector_description(const format &d, UINT8 *sectdata, desc_s *sectors, int track, int head) const;
=======
	virtual void build_sector_description(const format &d, uint8_t *sectdata, desc_s *sectors, int track, int head) const override;
>>>>>>> upstream/master
};

extern const floppy_format_type FLOPPY_NASLITE_FORMAT;

#endif
