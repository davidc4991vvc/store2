// license:BSD-3-Clause
// copyright-holders:Olivier Galibert
/*********************************************************************

    formats/dmv_dsk.h

    NCR Decision Mate V format

*********************************************************************/

#ifndef DMV_DSK_H_
#define DMV_DSK_H_

#include "upd765_dsk.h"

class dmv_format : public upd765_format {
public:
	dmv_format();

<<<<<<< HEAD
	virtual const char *name() const;
	virtual const char *description() const;
	virtual const char *extensions() const;
=======
	virtual const char *name() const override;
	virtual const char *description() const override;
	virtual const char *extensions() const override;
>>>>>>> upstream/master

private:
	static const format formats[];
};

extern const floppy_format_type FLOPPY_DMV_FORMAT;

#endif /* DMV_DSK_H_ */
