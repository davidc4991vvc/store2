// license:BSD-3-Clause
// copyright-holders:Curt Coder
/*********************************************************************

    formats/tiki100_dsk.h

    TIKI 100 disk image format

*********************************************************************/

#ifndef TIKI100_DSK_H_
#define TIKI100_DSK_H_

#include "wd177x_dsk.h"

class tiki100_format : public wd177x_format {
public:
	tiki100_format();

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

extern const floppy_format_type FLOPPY_TIKI100_FORMAT;

#endif
