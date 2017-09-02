$input a_position, a_texcoord0
$output v_dir

/*
<<<<<<< HEAD
 * Copyright 2014 Dario Manesku. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#include "../common/common.sh"
=======
 * Copyright 2014-2016 Dario Manesku. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include "../common/common.sh"
#include "uniforms.sh"
>>>>>>> upstream/master

uniform mat4 u_mtx;

void main()
{
	gl_Position = mul(u_modelViewProj, vec4(a_position, 1.0) );

<<<<<<< HEAD
	vec2 tex = 2.0 * a_texcoord0 - 1.0;
	v_dir = mul(u_mtx, vec4(tex, 1.0, 0.0) ).xyz;
=======
	float fov = radians(45.0);
	float height = tan(fov*0.5);
	float aspect = height*(u_viewRect.z / u_viewRect.w);
	vec2 tex = (2.0*a_texcoord0-1.0) * vec2(aspect, height);

	mat4 mtx;
	mtx[0] = u_mtx0;
	mtx[1] = u_mtx1;
	mtx[2] = u_mtx2;
	mtx[3] = u_mtx3;
	v_dir = instMul(mtx, vec4(tex, 1.0, 0.0) ).xyz;
>>>>>>> upstream/master
}
