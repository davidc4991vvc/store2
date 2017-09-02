$input v_view, v_normal

/*
<<<<<<< HEAD
 * Copyright 2014 Dario Manesku. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#include "../common/common.sh"

uniform vec4 u_params;
uniform mat4 u_mtx;
uniform vec4 u_flags;
uniform vec4 u_rgbDiff;
uniform vec4 u_rgbSpec;
=======
 * Copyright 2014-2016 Dario Manesku. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include "../common/common.sh"
#include "uniforms.sh"
>>>>>>> upstream/master

SAMPLERCUBE(s_texCube, 0);
SAMPLERCUBE(s_texCubeIrr, 1);

<<<<<<< HEAD
#define u_glossiness u_params.x
#define u_exposure   u_params.y
#define u_diffspec   u_params.z

#define u_doDiffuse     u_flags.x
#define u_doSpecular    u_flags.y
#define u_doDiffuseIbl  u_flags.z
#define u_doSpecularIbl u_flags.w

vec3 fresnel(vec3 _cspec, float _dot)
{
	return _cspec + (1.0 - _cspec) * pow(1.0 - _dot, 5);
}

void main()
{
	vec3 light  = vec3(0.0, 0.0, -1.0);
	vec3 clight = vec3(1.0, 1.0,  1.0);

	vec3 v = v_view;
	vec3 n = normalize(v_normal);
	vec3 l = normalize(light);
	vec3 h = normalize(v + l);

	float ndotl = clamp(dot(n, l), 0.0, 1.0); //diff
	float ndoth = clamp(dot(n, h), 0.0, 1.0); //spec
	float vdoth = clamp(dot(v, h), 0.0, 1.0); //spec fresnel
	float ndotv = clamp(dot(n, v), 0.0, 1.0); //env spec fresnel

	vec3 r = 2.0*ndotv*n - v; // reflect(v, n);

	vec3 cubeR = normalize(mul(u_mtx, vec4(r, 0.0)).xyz);
	vec3 cubeN = normalize(mul(u_mtx, vec4(n, 0.0)).xyz);

	float mipLevel = min((1.0 - u_glossiness)*11.0 + 1.0, 8.0);
	vec3 cenv = textureCubeLod(s_texCube, cubeR, mipLevel).xyz;

	vec3 kd = u_rgbDiff.xyz;
	vec3 ks = u_rgbSpec.xyz;

	vec3 cs = ks * u_diffspec;
	vec3 cd = kd * (1.0 - cs);

	vec3 diff = cd;
	float pwr = exp2(u_glossiness * 11.0 + 1.0);
	vec3 spec = cs * pow(ndoth, pwr) * ( (pwr + 8.0)/8.0) * fresnel(cs, vdoth);

	vec3 ambspec = fresnel(cs, ndotv) * cenv;
	vec3 ambdiff = cd * textureCube(s_texCubeIrr, cubeN).xyz;

	vec3 lc = (   diff * u_doDiffuse    +    spec * u_doSpecular   ) * ndotl * clight;
	vec3 ec = (ambdiff * u_doDiffuseIbl + ambspec * u_doSpecularIbl);

	vec3 color = lc + ec;
	color = color * exp2(u_exposure);

=======
vec3 calcFresnel(vec3 _cspec, float _dot, float _strength)
{
	return _cspec + (1.0 - _cspec)*pow(1.0 - _dot, 5.0) * _strength;
}

vec3 calcLambert(vec3 _cdiff, float _ndotl)
{
	return _cdiff*_ndotl;
}

vec3 calcBlinn(vec3 _cspec, float _ndoth, float _ndotl, float _specPwr)
{
	float norm = (_specPwr+8.0)*0.125;
	float brdf = pow(_ndoth, _specPwr)*_ndotl*norm;
	return _cspec*brdf;
}

float specPwr(float _gloss)
{
	return exp2(10.0*_gloss+2.0);
}

void main()
{
	// Light.
	vec3 ld     = normalize(u_lightDir);
	vec3 clight = u_lightCol;

	// Input.
	vec3 nn = normalize(v_normal);
	vec3 vv = normalize(v_view);
	vec3 hh = normalize(vv + ld);

	float ndotv = clamp(dot(nn, vv), 0.0, 1.0);
	float ndotl = clamp(dot(nn, ld), 0.0, 1.0);
	float ndoth = clamp(dot(nn, hh), 0.0, 1.0);
	float hdotv = clamp(dot(hh, vv), 0.0, 1.0);

	// Material params.
	vec3  inAlbedo       = u_rgbDiff.xyz;
	float inReflectivity = u_reflectivity;
	float inGloss        = u_glossiness;

	// Reflection.
	vec3 refl;
	if (0.0 == u_metalOrSpec) // Metalness workflow.
	{
		refl = mix(vec3_splat(0.04), inAlbedo, inReflectivity);
	}
	else // Specular workflow.
	{
		refl = u_rgbSpec.xyz * vec3_splat(inReflectivity);
	}
	vec3 albedo = inAlbedo * (1.0 - inReflectivity);
	vec3 dirFresnel = calcFresnel(refl, hdotv, inGloss);
	vec3 envFresnel = calcFresnel(refl, ndotv, inGloss);

	vec3 lambert = u_doDiffuse  * calcLambert(albedo * (1.0 - dirFresnel), ndotl);
	vec3 blinn   = u_doSpecular * calcBlinn(dirFresnel, ndoth, ndotl, specPwr(inGloss));
	vec3 direct  = (lambert + blinn)*clight;

	// Note: Environment textures are filtered with cmft: https://github.com/dariomanesku/cmft
	// Params used:
	// --excludeBase true //!< First level mip is not filtered.
	// --mipCount 7       //!< 7 mip levels are used in total, [256x256 .. 4x4]. Lower res mip maps should be avoided.
	// --glossScale 10    //!< Spec power scale. See: specPwr().
	// --glossBias 2      //!< Spec power bias. See: specPwr().
	// --edgeFixup warp   //!< This must be used on DirectX9. When fileted with 'warp', fixCubeLookup() should be used.
	float mip = 1.0 + 5.0*(1.0 - inGloss); // Use mip levels [1..6] for radiance.

	mat4 mtx;
	mtx[0] = u_mtx0;
	mtx[1] = u_mtx1;
	mtx[2] = u_mtx2;
	mtx[3] = u_mtx3;
	vec3 vr = 2.0*ndotv*nn - vv; // Same as: -reflect(vv, nn);
	vec3 cubeR = normalize(instMul(mtx, vec4(vr, 0.0)).xyz);
	vec3 cubeN = normalize(instMul(mtx, vec4(nn, 0.0)).xyz);
	cubeR = fixCubeLookup(cubeR, mip, 256.0);

	vec3 radiance    = toLinear(textureCubeLod(s_texCube, cubeR, mip).xyz);
	vec3 irradiance  = toLinear(textureCube(s_texCubeIrr, cubeN).xyz);
	vec3 envDiffuse  = albedo     * irradiance * u_doDiffuseIbl;
	vec3 envSpecular = envFresnel * radiance   * u_doSpecularIbl;
	vec3 indirect    = envDiffuse + envSpecular;

	// Color.
	vec3 color = direct + indirect;
	color = color * exp2(u_exposure);
>>>>>>> upstream/master
	gl_FragColor.xyz = toFilmic(color);
	gl_FragColor.w = 1.0;
}
