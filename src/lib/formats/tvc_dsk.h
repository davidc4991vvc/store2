// license:BSD-3-Clause
// copyright-holders:Olivier Galibert
/*********************************************************************

    formats/tvc_dsk.h

    Videoton TVC HBF format

*********************************************************************/

#ifndef TVC_DSK_H_
#define TVC_DSK_H_

#include "wd177x_dsk.h"

class tvc_format : public wd177x_format {
public:
	tvc_format();

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

extern const floppy_format_type FLOPPY_TVC_FORMAT;

#endif
