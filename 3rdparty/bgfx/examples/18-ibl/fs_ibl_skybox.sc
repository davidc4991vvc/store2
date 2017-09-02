$input v_dir

/*
<<<<<<< HEAD
 * Copyright 2014 Dario Manesku. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#include "../common/common.sh"

SAMPLERCUBE(s_texCube, 0);

uniform vec4 u_params;
#define u_exposure  u_params.y
=======
 * Copyright 2014-2016 Dario Manesku. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include "../common/common.sh"
#include "uniforms.sh"

SAMPLERCUBE(s_texCube, 0);
SAMPLERCUBE(s_texCubeIrr, 1);
>>>>>>> upstream/master

void main()
{
	vec3 dir = normalize(v_dir);

<<<<<<< HEAD
	vec4 color = textureCubeLod(s_texCube, dir, 0.0);
=======
	vec4 color;
	if (u_bgType == 7.0)
	{
		color = toLinear(textureCube(s_texCubeIrr, dir));
	}
	else
	{
		float lod = u_bgType;
		dir = fixCubeLookup(dir, lod, 256.0);
		color = toLinear(textureCubeLod(s_texCube, dir, lod));
	}
>>>>>>> upstream/master
	color *= exp2(u_exposure);

	gl_FragColor = toFilmic(color);
}
