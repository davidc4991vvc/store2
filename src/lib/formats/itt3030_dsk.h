// license:BSD-3-Clause
// copyright-holders:Olivier Galibert
/*********************************************************************

    formats/itt3030_dsk.h

    ITT3030 disk image format

*********************************************************************/

#ifndef ITT3030_DSK_H_
#define ITT3030_DSK_H_

#include "wd177x_dsk.h"

class itt3030_format : public wd177x_format {
public:
	itt3030_format();

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


extern const floppy_format_type FLOPPY_ITT3030_FORMAT;

#endif
