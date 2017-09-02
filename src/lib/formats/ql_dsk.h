// license:BSD-3-Clause
// copyright-holders:Curt Coder
/*********************************************************************

    formats/ql_dsk.h

    Sinclair QL disk image formats

*********************************************************************/

#ifndef QL_DSK_H_
#define QL_DSK_H_

#include "wd177x_dsk.h"

class ql_format : public wd177x_format {
public:
	ql_format();

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

extern const floppy_format_type FLOPPY_QL_FORMAT;

#endif
