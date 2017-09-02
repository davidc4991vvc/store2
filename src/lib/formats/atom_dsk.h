<<<<<<< HEAD
=======
// license:BSD-3-Clause
// copyright-holders:Carl
>>>>>>> upstream/master
#ifndef __ATOM_DSK_H__
#define __ATOM_DSK_H__

#include "flopimg.h"
#include "wd177x_dsk.h"

class atom_format : public wd177x_format
{
public:
	atom_format();

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

extern const floppy_format_type FLOPPY_ATOM_FORMAT;

#endif
