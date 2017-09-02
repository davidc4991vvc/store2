$input v_position

/*
 * Copyright 2013-2014 Dario Manesku. All rights reserved.
<<<<<<< HEAD
 * License: http://www.opensource.org/licenses/BSD-2-Clause
=======
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
>>>>>>> upstream/master
 */

#include "../common/common.sh"

<<<<<<< HEAD
void main()
{
	float depth = v_position.z/v_position.w * 0.5 + 0.5;
=======
uniform vec4 u_depthScaleOffset;  // for GL, map depth values into [0, 1] range
#define u_depthScale u_depthScaleOffset.x
#define u_depthOffset u_depthScaleOffset.y

void main()
{
	float depth = v_position.z/v_position.w * u_depthScale + u_depthOffset;
>>>>>>> upstream/master
	gl_FragColor = packFloatToRgba(depth);
}
