// license:BSD-3-Clause
// copyright-holders:Olivier Galibert
/*********************************************************************

    formats/nanos_dsk.h

    nanos format

*********************************************************************/

#ifndef NANOS_DSK_H_
#define NANOS_DSK_H_

#include "upd765_dsk.h"

class nanos_format : public upd765_format {
public:
	nanos_format();

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

extern const floppy_format_type FLOPPY_NANOS_FORMAT;

#endif
