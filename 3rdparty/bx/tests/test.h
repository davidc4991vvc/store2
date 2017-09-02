/*
<<<<<<< HEAD
 * Copyright 2010-2015 Branimir Karadzic. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
=======
 * Copyright 2010-2017 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bx#license-bsd-2-clause
>>>>>>> upstream/master
 */

#ifndef __TEST_H__
#define __TEST_H__

#include <bx/bx.h>
<<<<<<< HEAD
#include <UnitTest++.h>
#include "dbg.h"

#if !BX_COMPILER_MSVC
#	define _strdup strdup
#endif // !BX_COMPILER_MSVC
=======

BX_PRAGMA_DIAGNOSTIC_PUSH();
BX_PRAGMA_DIAGNOSTIC_IGNORED_MSVC(4312); // warning C4312 : 'reinterpret_cast' : conversion from 'int' to 'const char *' of greater size
#include <catch/catch.hpp>
BX_PRAGMA_DIAGNOSTIC_POP();

#define TEST(_x) TEST_CASE(#_x, "")
#define CHECK_EQUAL(_x, _y) REQUIRE(_x == _y)

#include "dbg.h"
>>>>>>> upstream/master

#endif // __TEST_H__
