$input v_texcoord0

/*
<<<<<<< HEAD
 * Copyright 2011-2015 Branimir Karadzic. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
=======
 * Copyright 2011-2017 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
>>>>>>> upstream/master
 */

#include "../common/common.sh"

SAMPLER2D(s_texColor, 0);

void main()
{
	gl_FragColor = texture2D(s_texColor, v_texcoord0.xy*0.5+0.5);
}
