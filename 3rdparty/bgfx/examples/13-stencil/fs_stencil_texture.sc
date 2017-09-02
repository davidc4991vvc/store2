$input v_texcoord0

/*
 * Copyright 2013-2014 Dario Manesku. All rights reserved.
<<<<<<< HEAD
 * License: http://www.opensource.org/licenses/BSD-2-Clause
=======
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
>>>>>>> upstream/master
 */

#include "../common/common.sh"
SAMPLER2D(s_texColor, 0);

void main()
{
	gl_FragColor = texture2D(s_texColor, v_texcoord0);
}
