$input a_position, a_normal
$output v_view, v_normal

/*
<<<<<<< HEAD
 * Copyright 2014 Dario Manesku. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#include "../common/common.sh"

uniform vec4 u_camPos;
=======
 * Copyright 2014-2016 Dario Manesku. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include "../common/common.sh"
#include "uniforms.sh"
>>>>>>> upstream/master

void main()
{
	gl_Position = mul(u_modelViewProj, vec4(a_position, 1.0) );

<<<<<<< HEAD
	vec3 normal = a_normal * 2.0 - 1.0;
	v_normal = mul(u_model[0], vec4(normal, 0.0) ).xyz;
	v_view = normalize(u_camPos.xyz - mul(u_model[0], vec4(a_position, 1.0)).xyz);
=======
	v_view = u_camPos - mul(u_model[0], vec4(a_position, 1.0)).xyz;

	vec3 normal = a_normal * 2.0 - 1.0;
	v_normal = mul(u_model[0], vec4(normal, 0.0) ).xyz;
>>>>>>> upstream/master
}
