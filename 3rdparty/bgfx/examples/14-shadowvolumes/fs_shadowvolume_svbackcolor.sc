/*
 * Copyright 2013-2014 Dario Manesku. All rights reserved.
<<<<<<< HEAD
 * License: http://www.opensource.org/licenses/BSD-2-Clause
=======
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
>>>>>>> upstream/master
 */

#include "../common/common.sh"
uniform vec4 u_color;

void main()
{
	gl_FragColor.xyz = u_color.xyz;
	gl_FragColor.w = 0.98;
}
