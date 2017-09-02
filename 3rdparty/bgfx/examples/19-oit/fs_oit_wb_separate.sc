$input v_pos

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

uniform vec4 u_color;

void main()
{
	vec4 color = u_color;

	float depth = v_pos.z/v_pos.w;

	float weight = color.w * clamp(0.03 / (1e-5 + pow(depth / 200.0, 5.0) ), 0.01, 3000.0);
	gl_FragData[0] = color * weight;
	gl_FragData[1] = vec4_splat(weight);
}
