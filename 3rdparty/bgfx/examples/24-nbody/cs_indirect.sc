/*
 * Copyright 2014 Stanlo Slasinski. All rights reserved.
<<<<<<< HEAD
 * License: http://www.opensource.org/licenses/BSD-2-Clause
=======
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
>>>>>>> upstream/master
 */

#include "bgfx_compute.sh"
#include "uniforms.sh"

BUFFER_WR(indirectBuffer, uvec4, 0);

NUM_THREADS(1, 1, 1)
void main()
{
	drawIndexedIndirect(indirectBuffer, 0, 6, u_dispatchSize * threadGroupUpdateSize, 0, 0, 0);
	dispatchIndirect(indirectBuffer, 1, u_dispatchSize, 1, 1);
}
