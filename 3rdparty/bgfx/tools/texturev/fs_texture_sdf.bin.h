static const uint8_t fs_texture_sdf_glsl[647] =
{
	0x46, 0x53, 0x48, 0x04, 0x01, 0x83, 0xf2, 0xe1, 0x02, 0x00, 0x0a, 0x73, 0x5f, 0x74, 0x65, 0x78, // FSH........s_tex
	0x43, 0x6f, 0x6c, 0x6f, 0x72, 0x00, 0x01, 0x00, 0x00, 0x01, 0x00, 0x08, 0x75, 0x5f, 0x70, 0x61, // Color.......u_pa
	0x72, 0x61, 0x6d, 0x73, 0x02, 0x01, 0x00, 0x00, 0x01, 0x00, 0x58, 0x02, 0x00, 0x00, 0x76, 0x61, // rams......X...va
	0x72, 0x79, 0x69, 0x6e, 0x67, 0x20, 0x68, 0x69, 0x67, 0x68, 0x70, 0x20, 0x76, 0x65, 0x63, 0x32, // rying highp vec2
	0x20, 0x76, 0x5f, 0x74, 0x65, 0x78, 0x63, 0x6f, 0x6f, 0x72, 0x64, 0x30, 0x3b, 0x0a, 0x75, 0x6e, //  v_texcoord0;.un
	0x69, 0x66, 0x6f, 0x72, 0x6d, 0x20, 0x73, 0x61, 0x6d, 0x70, 0x6c, 0x65, 0x72, 0x32, 0x44, 0x20, // iform sampler2D 
	0x73, 0x5f, 0x74, 0x65, 0x78, 0x43, 0x6f, 0x6c, 0x6f, 0x72, 0x3b, 0x0a, 0x75, 0x6e, 0x69, 0x66, // s_texColor;.unif
	0x6f, 0x72, 0x6d, 0x20, 0x68, 0x69, 0x67, 0x68, 0x70, 0x20, 0x76, 0x65, 0x63, 0x34, 0x20, 0x75, // orm highp vec4 u
	0x5f, 0x70, 0x61, 0x72, 0x61, 0x6d, 0x73, 0x3b, 0x0a, 0x76, 0x6f, 0x69, 0x64, 0x20, 0x6d, 0x61, // _params;.void ma
	0x69, 0x6e, 0x20, 0x28, 0x29, 0x0a, 0x7b, 0x0a, 0x20, 0x20, 0x6c, 0x6f, 0x77, 0x70, 0x20, 0x76, // in ().{.  lowp v
	0x65, 0x63, 0x33, 0x20, 0x74, 0x6d, 0x70, 0x76, 0x61, 0x72, 0x5f, 0x31, 0x3b, 0x0a, 0x20, 0x20, // ec3 tmpvar_1;.  
	0x74, 0x6d, 0x70, 0x76, 0x61, 0x72, 0x5f, 0x31, 0x20, 0x3d, 0x20, 0x74, 0x65, 0x78, 0x74, 0x75, // tmpvar_1 = textu
	0x72, 0x65, 0x32, 0x44, 0x4c, 0x6f, 0x64, 0x20, 0x20, 0x20, 0x20, 0x28, 0x73, 0x5f, 0x74, 0x65, // re2DLod    (s_te
	0x78, 0x43, 0x6f, 0x6c, 0x6f, 0x72, 0x2c, 0x20, 0x76, 0x5f, 0x74, 0x65, 0x78, 0x63, 0x6f, 0x6f, // xColor, v_texcoo
	0x72, 0x64, 0x30, 0x2c, 0x20, 0x75, 0x5f, 0x70, 0x61, 0x72, 0x61, 0x6d, 0x73, 0x2e, 0x78, 0x29, // rd0, u_params.x)
	0x2e, 0x78, 0x79, 0x7a, 0x3b, 0x0a, 0x20, 0x20, 0x6c, 0x6f, 0x77, 0x70, 0x20, 0x66, 0x6c, 0x6f, // .xyz;.  lowp flo
	0x61, 0x74, 0x20, 0x74, 0x6d, 0x70, 0x76, 0x61, 0x72, 0x5f, 0x32, 0x3b, 0x0a, 0x20, 0x20, 0x74, // at tmpvar_2;.  t
	0x6d, 0x70, 0x76, 0x61, 0x72, 0x5f, 0x32, 0x20, 0x3d, 0x20, 0x28, 0x6d, 0x61, 0x78, 0x20, 0x28, // mpvar_2 = (max (
	0x6d, 0x69, 0x6e, 0x20, 0x28, 0x74, 0x6d, 0x70, 0x76, 0x61, 0x72, 0x5f, 0x31, 0x2e, 0x78, 0x2c, // min (tmpvar_1.x,
	0x20, 0x74, 0x6d, 0x70, 0x76, 0x61, 0x72, 0x5f, 0x31, 0x2e, 0x79, 0x29, 0x2c, 0x20, 0x6d, 0x69, //  tmpvar_1.y), mi
	0x6e, 0x20, 0x28, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x6d, 0x61, 0x78, 0x20, 0x28, 0x74, 0x6d, 0x70, // n (.    max (tmp
	0x76, 0x61, 0x72, 0x5f, 0x31, 0x2e, 0x78, 0x2c, 0x20, 0x74, 0x6d, 0x70, 0x76, 0x61, 0x72, 0x5f, // var_1.x, tmpvar_
	0x31, 0x2e, 0x79, 0x29, 0x0a, 0x20, 0x20, 0x2c, 0x20, 0x74, 0x6d, 0x70, 0x76, 0x61, 0x72, 0x5f, // 1.y).  , tmpvar_
	0x31, 0x2e, 0x7a, 0x29, 0x29, 0x20, 0x2d, 0x20, 0x30, 0x2e, 0x35, 0x29, 0x3b, 0x0a, 0x20, 0x20, // 1.z)) - 0.5);.  
	0x6c, 0x6f, 0x77, 0x70, 0x20, 0x66, 0x6c, 0x6f, 0x61, 0x74, 0x20, 0x74, 0x6d, 0x70, 0x76, 0x61, // lowp float tmpva
	0x72, 0x5f, 0x33, 0x3b, 0x0a, 0x20, 0x20, 0x74, 0x6d, 0x70, 0x76, 0x61, 0x72, 0x5f, 0x33, 0x20, // r_3;.  tmpvar_3 
	0x3d, 0x20, 0x63, 0x6c, 0x61, 0x6d, 0x70, 0x20, 0x28, 0x28, 0x28, 0x74, 0x6d, 0x70, 0x76, 0x61, // = clamp (((tmpva
	0x72, 0x5f, 0x32, 0x20, 0x2f, 0x20, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x28, 0x61, 0x62, 0x73, 0x28, // r_2 / .    (abs(
	0x64, 0x46, 0x64, 0x78, 0x28, 0x74, 0x6d, 0x70, 0x76, 0x61, 0x72, 0x5f, 0x32, 0x29, 0x29, 0x20, // dFdx(tmpvar_2)) 
	0x2b, 0x20, 0x61, 0x62, 0x73, 0x28, 0x64, 0x46, 0x64, 0x79, 0x28, 0x74, 0x6d, 0x70, 0x76, 0x61, // + abs(dFdy(tmpva
	0x72, 0x5f, 0x32, 0x29, 0x29, 0x29, 0x0a, 0x20, 0x20, 0x29, 0x20, 0x2b, 0x20, 0x30, 0x2e, 0x35, // r_2))).  ) + 0.5
	0x29, 0x2c, 0x20, 0x30, 0x2e, 0x30, 0x2c, 0x20, 0x31, 0x2e, 0x30, 0x29, 0x3b, 0x0a, 0x20, 0x20, // ), 0.0, 1.0);.  
	0x6d, 0x65, 0x64, 0x69, 0x75, 0x6d, 0x70, 0x20, 0x76, 0x65, 0x63, 0x34, 0x20, 0x74, 0x6d, 0x70, // mediump vec4 tmp
	0x76, 0x61, 0x72, 0x5f, 0x34, 0x3b, 0x0a, 0x20, 0x20, 0x74, 0x6d, 0x70, 0x76, 0x61, 0x72, 0x5f, // var_4;.  tmpvar_
	0x34, 0x20, 0x3d, 0x20, 0x6d, 0x69, 0x78, 0x20, 0x28, 0x76, 0x65, 0x63, 0x34, 0x28, 0x31, 0x2e, // 4 = mix (vec4(1.
	0x30, 0x2c, 0x20, 0x31, 0x2e, 0x30, 0x2c, 0x20, 0x31, 0x2e, 0x30, 0x2c, 0x20, 0x31, 0x2e, 0x30, // 0, 1.0, 1.0, 1.0
	0x29, 0x2c, 0x20, 0x76, 0x65, 0x63, 0x34, 0x28, 0x30, 0x2e, 0x30, 0x2c, 0x20, 0x30, 0x2e, 0x30, // ), vec4(0.0, 0.0
	0x2c, 0x20, 0x30, 0x2e, 0x30, 0x2c, 0x20, 0x31, 0x2e, 0x30, 0x29, 0x2c, 0x20, 0x74, 0x6d, 0x70, // , 0.0, 1.0), tmp
	0x76, 0x61, 0x72, 0x5f, 0x33, 0x29, 0x3b, 0x0a, 0x20, 0x20, 0x67, 0x6c, 0x5f, 0x46, 0x72, 0x61, // var_3);.  gl_Fra
	0x67, 0x43, 0x6f, 0x6c, 0x6f, 0x72, 0x20, 0x3d, 0x20, 0x74, 0x6d, 0x70, 0x76, 0x61, 0x72, 0x5f, // gColor = tmpvar_
	0x34, 0x3b, 0x0a, 0x7d, 0x0a, 0x0a, 0x00,                                                       // 4;.}...
};
static const uint8_t fs_texture_sdf_dx9[533] =
{
	0x46, 0x53, 0x48, 0x04, 0x01, 0x83, 0xf2, 0xe1, 0x02, 0x00, 0x0a, 0x73, 0x5f, 0x74, 0x65, 0x78, // FSH........s_tex
	0x43, 0x6f, 0x6c, 0x6f, 0x72, 0x30, 0x01, 0x00, 0x00, 0x01, 0x00, 0x08, 0x75, 0x5f, 0x70, 0x61, // Color0......u_pa
	0x72, 0x61, 0x6d, 0x73, 0x12, 0x01, 0x00, 0x00, 0x01, 0x00, 0xe8, 0x01, 0x00, 0x03, 0xff, 0xff, // rams............
	0xfe, 0xff, 0x2e, 0x00, 0x43, 0x54, 0x41, 0x42, 0x1c, 0x00, 0x00, 0x00, 0x83, 0x00, 0x00, 0x00, // ....CTAB........
	0x00, 0x03, 0xff, 0xff, 0x02, 0x00, 0x00, 0x00, 0x1c, 0x00, 0x00, 0x00, 0x00, 0x91, 0x00, 0x00, // ................
	0x7c, 0x00, 0x00, 0x00, 0x44, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x01, 0x00, 0x02, 0x00, // |...D...........
	0x50, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, // P.......`.......
	0x01, 0x00, 0x00, 0x00, 0x6c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x73, 0x5f, 0x74, 0x65, // ....l.......s_te
	0x78, 0x43, 0x6f, 0x6c, 0x6f, 0x72, 0x00, 0xab, 0x04, 0x00, 0x0c, 0x00, 0x01, 0x00, 0x01, 0x00, // xColor..........
	0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x75, 0x5f, 0x70, 0x61, 0x72, 0x61, 0x6d, 0x73, // ........u_params
	0x00, 0xab, 0xab, 0xab, 0x01, 0x00, 0x03, 0x00, 0x01, 0x00, 0x04, 0x00, 0x01, 0x00, 0x00, 0x00, // ................
	0x00, 0x00, 0x00, 0x00, 0x70, 0x73, 0x5f, 0x33, 0x5f, 0x30, 0x00, 0x4d, 0x69, 0x63, 0x72, 0x6f, // ....ps_3_0.Micro
	0x73, 0x6f, 0x66, 0x74, 0x20, 0x28, 0x52, 0x29, 0x20, 0x48, 0x4c, 0x53, 0x4c, 0x20, 0x53, 0x68, // soft (R) HLSL Sh
	0x61, 0x64, 0x65, 0x72, 0x20, 0x43, 0x6f, 0x6d, 0x70, 0x69, 0x6c, 0x65, 0x72, 0x20, 0x39, 0x2e, // ader Compiler 9.
	0x32, 0x39, 0x2e, 0x39, 0x35, 0x32, 0x2e, 0x33, 0x31, 0x31, 0x31, 0x00, 0x51, 0x00, 0x00, 0x05, // 29.952.3111.Q...
	0x01, 0x00, 0x0f, 0xa0, 0x00, 0x00, 0x80, 0x3f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xbf, // .......?........
	0x00, 0x00, 0x00, 0x3f, 0x51, 0x00, 0x00, 0x05, 0x02, 0x00, 0x0f, 0xa0, 0x00, 0x00, 0x80, 0xbf, // ...?Q...........
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x3f, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x00, 0x00, 0x02, // .......?........
	0x05, 0x00, 0x00, 0x80, 0x00, 0x00, 0x03, 0x90, 0x1f, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x90, // ................
	0x00, 0x08, 0x0f, 0xa0, 0x05, 0x00, 0x00, 0x03, 0x00, 0x00, 0x07, 0x80, 0x01, 0x00, 0xd0, 0xa0, // ................
	0x00, 0x00, 0xc4, 0x90, 0x01, 0x00, 0x00, 0x02, 0x00, 0x00, 0x08, 0x80, 0x00, 0x00, 0x00, 0xa0, // ................
	0x5f, 0x00, 0x00, 0x03, 0x00, 0x00, 0x0f, 0x80, 0x00, 0x00, 0xe4, 0x80, 0x00, 0x08, 0xe4, 0xa0, // _...............
	0x02, 0x00, 0x00, 0x03, 0x00, 0x00, 0x08, 0x80, 0x00, 0x00, 0x55, 0x81, 0x00, 0x00, 0x00, 0x80, // ..........U.....
	0x58, 0x00, 0x00, 0x04, 0x00, 0x00, 0x03, 0x80, 0x00, 0x00, 0xff, 0x80, 0x00, 0x00, 0xe1, 0x80, // X...............
	0x00, 0x00, 0xe4, 0x80, 0x0a, 0x00, 0x00, 0x03, 0x01, 0x00, 0x01, 0x80, 0x00, 0x00, 0xaa, 0x80, // ................
	0x00, 0x00, 0x55, 0x80, 0x0b, 0x00, 0x00, 0x03, 0x02, 0x00, 0x01, 0x80, 0x00, 0x00, 0x00, 0x80, // ..U.............
	0x01, 0x00, 0x00, 0x80, 0x02, 0x00, 0x00, 0x03, 0x00, 0x00, 0x01, 0x80, 0x02, 0x00, 0x00, 0x80, // ................
	0x01, 0x00, 0xaa, 0xa0, 0x5b, 0x00, 0x00, 0x02, 0x00, 0x00, 0x02, 0x80, 0x00, 0x00, 0x00, 0x80, // ....[...........
	0x5c, 0x00, 0x00, 0x02, 0x00, 0x00, 0x04, 0x80, 0x00, 0x00, 0x00, 0x80, 0x02, 0x00, 0x00, 0x03, // ................
	0x00, 0x00, 0x02, 0x80, 0x00, 0x00, 0xaa, 0x8b, 0x00, 0x00, 0x55, 0x8b, 0x06, 0x00, 0x00, 0x02, // ..........U.....
	0x00, 0x00, 0x02, 0x80, 0x00, 0x00, 0x55, 0x80, 0x04, 0x00, 0x00, 0x04, 0x00, 0x00, 0x11, 0x80, // ......U.........
	0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x55, 0x80, 0x01, 0x00, 0xff, 0xa0, 0x04, 0x00, 0x00, 0x04, // ......U.........
	0x00, 0x08, 0x0f, 0x80, 0x00, 0x00, 0x00, 0x80, 0x02, 0x00, 0x40, 0xa0, 0x02, 0x00, 0xaa, 0xa0, // ..........@.....
	0xff, 0xff, 0x00, 0x00, 0x00,                                                                   // .....
};
static const uint8_t fs_texture_sdf_dx11[708] =
{
	0x46, 0x53, 0x48, 0x04, 0x01, 0x83, 0xf2, 0xe1, 0x02, 0x00, 0x08, 0x75, 0x5f, 0x70, 0x61, 0x72, // FSH........u_par
	0x61, 0x6d, 0x73, 0x12, 0x00, 0x00, 0x00, 0x01, 0x00, 0x0a, 0x73, 0x5f, 0x74, 0x65, 0x78, 0x43, // ams.......s_texC
	0x6f, 0x6c, 0x6f, 0x72, 0x30, 0x01, 0x00, 0x00, 0x01, 0x00, 0x94, 0x02, 0x44, 0x58, 0x42, 0x43, // olor0.......DXBC
	0xfa, 0x89, 0x1e, 0xd3, 0xdd, 0xf3, 0x5c, 0xf1, 0xc3, 0xff, 0x7f, 0xa1, 0xd8, 0xa1, 0x03, 0x00, // ................
	0x01, 0x00, 0x00, 0x00, 0x94, 0x02, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x2c, 0x00, 0x00, 0x00, // ............,...
	0xa0, 0x00, 0x00, 0x00, 0xd4, 0x00, 0x00, 0x00, 0x49, 0x53, 0x47, 0x4e, 0x6c, 0x00, 0x00, 0x00, // ........ISGNl...
	0x03, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x50, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // ........P.......
	0x01, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00, // ................
	0x5c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, // ................
	0x01, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00, 0x62, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // ........b.......
	0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x03, 0x03, 0x00, 0x00, // ................
	0x53, 0x56, 0x5f, 0x50, 0x4f, 0x53, 0x49, 0x54, 0x49, 0x4f, 0x4e, 0x00, 0x43, 0x4f, 0x4c, 0x4f, // SV_POSITION.COLO
	0x52, 0x00, 0x54, 0x45, 0x58, 0x43, 0x4f, 0x4f, 0x52, 0x44, 0x00, 0xab, 0x4f, 0x53, 0x47, 0x4e, // R.TEXCOORD..OSGN
	0x2c, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, // ,........... ...
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // ................
	0x0f, 0x00, 0x00, 0x00, 0x53, 0x56, 0x5f, 0x54, 0x41, 0x52, 0x47, 0x45, 0x54, 0x00, 0xab, 0xab, // ....SV_TARGET...
	0x53, 0x48, 0x44, 0x52, 0xb8, 0x01, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x6e, 0x00, 0x00, 0x00, // SHDR....@...n...
	0x59, 0x00, 0x00, 0x04, 0x46, 0x8e, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, // Y...F. .........
	0x5a, 0x00, 0x00, 0x03, 0x00, 0x60, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x58, 0x18, 0x00, 0x04, // Z....`......X...
	0x00, 0x70, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x55, 0x55, 0x00, 0x00, 0x62, 0x10, 0x00, 0x03, // .p......UU..b...
	0x32, 0x10, 0x10, 0x00, 0x02, 0x00, 0x00, 0x00, 0x65, 0x00, 0x00, 0x03, 0xf2, 0x20, 0x10, 0x00, // 2.......e.... ..
	0x00, 0x00, 0x00, 0x00, 0x68, 0x00, 0x00, 0x02, 0x01, 0x00, 0x00, 0x00, 0x48, 0x00, 0x00, 0x0c, // ....h.......H...
	0xf2, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46, 0x10, 0x10, 0x00, 0x02, 0x00, 0x00, 0x00, // ........F.......
	0x46, 0x7e, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, // F~.......`......
	0x0a, 0x80, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x34, 0x00, 0x00, 0x07, // .. .........4...
	0x82, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1a, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, // ................
	0x0a, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x33, 0x00, 0x00, 0x07, 0x52, 0x00, 0x10, 0x00, // ........3...R...
	0x00, 0x00, 0x00, 0x00, 0x56, 0x06, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x03, 0x10, 0x00, // ....V...........
	0x00, 0x00, 0x00, 0x00, 0x34, 0x00, 0x00, 0x07, 0x12, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, // ....4...........
	0x2a, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0a, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, // *...............
	0x00, 0x00, 0x00, 0x07, 0x12, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0a, 0x00, 0x10, 0x00, // ................
	0x00, 0x00, 0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0xbf, 0x0b, 0x00, 0x00, 0x05, // .....@..........
	0x22, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0a, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, // "...............
	0x0c, 0x00, 0x00, 0x05, 0x42, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0a, 0x00, 0x10, 0x00, // ....B...........
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x09, 0x22, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, // ........".......
	0x2a, 0x00, 0x10, 0x80, 0x81, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1a, 0x00, 0x10, 0x80, // *...............
	0x81, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0e, 0x00, 0x00, 0x07, 0x12, 0x00, 0x10, 0x00, // ................
	0x00, 0x00, 0x00, 0x00, 0x0a, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1a, 0x00, 0x10, 0x00, // ................
	0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x07, 0x12, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, // ..... ..........
	0x0a, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, // .........@.....?
	0x32, 0x00, 0x00, 0x0f, 0xf2, 0x20, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x00, 0x10, 0x00, // 2.... ..........
	0x00, 0x00, 0x00, 0x00, 0x02, 0x40, 0x00, 0x00, 0x00, 0x00, 0x80, 0xbf, 0x00, 0x00, 0x80, 0xbf, // .....@..........
	0x00, 0x00, 0x80, 0xbf, 0x00, 0x00, 0x00, 0x00, 0x02, 0x40, 0x00, 0x00, 0x00, 0x00, 0x80, 0x3f, // .........@.....?
	0x00, 0x00, 0x80, 0x3f, 0x00, 0x00, 0x80, 0x3f, 0x00, 0x00, 0x80, 0x3f, 0x3e, 0x00, 0x00, 0x01, // ...?...?...?>...
	0x00, 0x00, 0x10, 0x00,                                                                         // ....
};
static const uint8_t fs_texture_sdf_mtl[955] =
{
	0x46, 0x53, 0x48, 0x04, 0x01, 0x83, 0xf2, 0xe1, 0x00, 0x00, 0xac, 0x03, 0x00, 0x00, 0x75, 0x73, // FSH...........us
	0x69, 0x6e, 0x67, 0x20, 0x6e, 0x61, 0x6d, 0x65, 0x73, 0x70, 0x61, 0x63, 0x65, 0x20, 0x6d, 0x65, // ing namespace me
	0x74, 0x61, 0x6c, 0x3b, 0x0a, 0x73, 0x74, 0x72, 0x75, 0x63, 0x74, 0x20, 0x78, 0x6c, 0x61, 0x74, // tal;.struct xlat
	0x4d, 0x74, 0x6c, 0x53, 0x68, 0x61, 0x64, 0x65, 0x72, 0x49, 0x6e, 0x70, 0x75, 0x74, 0x20, 0x7b, // MtlShaderInput {
	0x0a, 0x20, 0x20, 0x66, 0x6c, 0x6f, 0x61, 0x74, 0x32, 0x20, 0x76, 0x5f, 0x74, 0x65, 0x78, 0x63, // .  float2 v_texc
	0x6f, 0x6f, 0x72, 0x64, 0x30, 0x3b, 0x0a, 0x7d, 0x3b, 0x0a, 0x73, 0x74, 0x72, 0x75, 0x63, 0x74, // oord0;.};.struct
	0x20, 0x78, 0x6c, 0x61, 0x74, 0x4d, 0x74, 0x6c, 0x53, 0x68, 0x61, 0x64, 0x65, 0x72, 0x4f, 0x75, //  xlatMtlShaderOu
	0x74, 0x70, 0x75, 0x74, 0x20, 0x7b, 0x0a, 0x20, 0x20, 0x68, 0x61, 0x6c, 0x66, 0x34, 0x20, 0x67, // tput {.  half4 g
	0x6c, 0x5f, 0x46, 0x72, 0x61, 0x67, 0x43, 0x6f, 0x6c, 0x6f, 0x72, 0x3b, 0x0a, 0x7d, 0x3b, 0x0a, // l_FragColor;.};.
	0x73, 0x74, 0x72, 0x75, 0x63, 0x74, 0x20, 0x78, 0x6c, 0x61, 0x74, 0x4d, 0x74, 0x6c, 0x53, 0x68, // struct xlatMtlSh
	0x61, 0x64, 0x65, 0x72, 0x55, 0x6e, 0x69, 0x66, 0x6f, 0x72, 0x6d, 0x20, 0x7b, 0x0a, 0x20, 0x20, // aderUniform {.  
	0x66, 0x6c, 0x6f, 0x61, 0x74, 0x34, 0x20, 0x75, 0x5f, 0x70, 0x61, 0x72, 0x61, 0x6d, 0x73, 0x3b, // float4 u_params;
	0x0a, 0x7d, 0x3b, 0x0a, 0x66, 0x72, 0x61, 0x67, 0x6d, 0x65, 0x6e, 0x74, 0x20, 0x78, 0x6c, 0x61, // .};.fragment xla
	0x74, 0x4d, 0x74, 0x6c, 0x53, 0x68, 0x61, 0x64, 0x65, 0x72, 0x4f, 0x75, 0x74, 0x70, 0x75, 0x74, // tMtlShaderOutput
	0x20, 0x78, 0x6c, 0x61, 0x74, 0x4d, 0x74, 0x6c, 0x4d, 0x61, 0x69, 0x6e, 0x20, 0x28, 0x78, 0x6c, //  xlatMtlMain (xl
	0x61, 0x74, 0x4d, 0x74, 0x6c, 0x53, 0x68, 0x61, 0x64, 0x65, 0x72, 0x49, 0x6e, 0x70, 0x75, 0x74, // atMtlShaderInput
	0x20, 0x5f, 0x6d, 0x74, 0x6c, 0x5f, 0x69, 0x20, 0x5b, 0x5b, 0x73, 0x74, 0x61, 0x67, 0x65, 0x5f, //  _mtl_i [[stage_
	0x69, 0x6e, 0x5d, 0x5d, 0x2c, 0x20, 0x63, 0x6f, 0x6e, 0x73, 0x74, 0x61, 0x6e, 0x74, 0x20, 0x78, // in]], constant x
	0x6c, 0x61, 0x74, 0x4d, 0x74, 0x6c, 0x53, 0x68, 0x61, 0x64, 0x65, 0x72, 0x55, 0x6e, 0x69, 0x66, // latMtlShaderUnif
	0x6f, 0x72, 0x6d, 0x26, 0x20, 0x5f, 0x6d, 0x74, 0x6c, 0x5f, 0x75, 0x20, 0x5b, 0x5b, 0x62, 0x75, // orm& _mtl_u [[bu
	0x66, 0x66, 0x65, 0x72, 0x28, 0x30, 0x29, 0x5d, 0x5d, 0x0a, 0x20, 0x20, 0x2c, 0x20, 0x20, 0x20, // ffer(0)]].  ,   
	0x74, 0x65, 0x78, 0x74, 0x75, 0x72, 0x65, 0x32, 0x64, 0x3c, 0x66, 0x6c, 0x6f, 0x61, 0x74, 0x3e, // texture2d<float>
	0x20, 0x73, 0x5f, 0x74, 0x65, 0x78, 0x43, 0x6f, 0x6c, 0x6f, 0x72, 0x20, 0x5b, 0x5b, 0x74, 0x65, //  s_texColor [[te
	0x78, 0x74, 0x75, 0x72, 0x65, 0x28, 0x30, 0x29, 0x5d, 0x5d, 0x2c, 0x20, 0x73, 0x61, 0x6d, 0x70, // xture(0)]], samp
	0x6c, 0x65, 0x72, 0x20, 0x5f, 0x6d, 0x74, 0x6c, 0x73, 0x6d, 0x70, 0x5f, 0x73, 0x5f, 0x74, 0x65, // ler _mtlsmp_s_te
	0x78, 0x43, 0x6f, 0x6c, 0x6f, 0x72, 0x20, 0x5b, 0x5b, 0x73, 0x61, 0x6d, 0x70, 0x6c, 0x65, 0x72, // xColor [[sampler
	0x28, 0x30, 0x29, 0x5d, 0x5d, 0x29, 0x0a, 0x7b, 0x0a, 0x20, 0x20, 0x78, 0x6c, 0x61, 0x74, 0x4d, // (0)]]).{.  xlatM
	0x74, 0x6c, 0x53, 0x68, 0x61, 0x64, 0x65, 0x72, 0x4f, 0x75, 0x74, 0x70, 0x75, 0x74, 0x20, 0x5f, // tlShaderOutput _
	0x6d, 0x74, 0x6c, 0x5f, 0x6f, 0x3b, 0x0a, 0x20, 0x20, 0x68, 0x61, 0x6c, 0x66, 0x34, 0x20, 0x74, // mtl_o;.  half4 t
	0x6d, 0x70, 0x76, 0x61, 0x72, 0x5f, 0x31, 0x3b, 0x0a, 0x20, 0x20, 0x74, 0x6d, 0x70, 0x76, 0x61, // mpvar_1;.  tmpva
	0x72, 0x5f, 0x31, 0x20, 0x3d, 0x20, 0x68, 0x61, 0x6c, 0x66, 0x34, 0x28, 0x73, 0x5f, 0x74, 0x65, // r_1 = half4(s_te
	0x78, 0x43, 0x6f, 0x6c, 0x6f, 0x72, 0x2e, 0x73, 0x61, 0x6d, 0x70, 0x6c, 0x65, 0x28, 0x5f, 0x6d, // xColor.sample(_m
	0x74, 0x6c, 0x73, 0x6d, 0x70, 0x5f, 0x73, 0x5f, 0x74, 0x65, 0x78, 0x43, 0x6f, 0x6c, 0x6f, 0x72, // tlsmp_s_texColor
	0x2c, 0x20, 0x28, 0x66, 0x6c, 0x6f, 0x61, 0x74, 0x32, 0x29, 0x28, 0x5f, 0x6d, 0x74, 0x6c, 0x5f, // , (float2)(_mtl_
	0x69, 0x2e, 0x76, 0x5f, 0x74, 0x65, 0x78, 0x63, 0x6f, 0x6f, 0x72, 0x64, 0x30, 0x29, 0x2c, 0x20, // i.v_texcoord0), 
	0x6c, 0x65, 0x76, 0x65, 0x6c, 0x28, 0x5f, 0x6d, 0x74, 0x6c, 0x5f, 0x75, 0x2e, 0x75, 0x5f, 0x70, // level(_mtl_u.u_p
	0x61, 0x72, 0x61, 0x6d, 0x73, 0x2e, 0x78, 0x29, 0x29, 0x29, 0x3b, 0x0a, 0x20, 0x20, 0x68, 0x61, // arams.x)));.  ha
	0x6c, 0x66, 0x20, 0x74, 0x6d, 0x70, 0x76, 0x61, 0x72, 0x5f, 0x32, 0x3b, 0x0a, 0x20, 0x20, 0x74, // lf tmpvar_2;.  t
	0x6d, 0x70, 0x76, 0x61, 0x72, 0x5f, 0x32, 0x20, 0x3d, 0x20, 0x28, 0x6d, 0x61, 0x78, 0x20, 0x28, // mpvar_2 = (max (
	0x6d, 0x69, 0x6e, 0x20, 0x28, 0x74, 0x6d, 0x70, 0x76, 0x61, 0x72, 0x5f, 0x31, 0x2e, 0x78, 0x2c, // min (tmpvar_1.x,
	0x20, 0x74, 0x6d, 0x70, 0x76, 0x61, 0x72, 0x5f, 0x31, 0x2e, 0x79, 0x29, 0x2c, 0x20, 0x6d, 0x69, //  tmpvar_1.y), mi
	0x6e, 0x20, 0x28, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x6d, 0x61, 0x78, 0x20, 0x28, 0x74, 0x6d, 0x70, // n (.    max (tmp
	0x76, 0x61, 0x72, 0x5f, 0x31, 0x2e, 0x78, 0x2c, 0x20, 0x74, 0x6d, 0x70, 0x76, 0x61, 0x72, 0x5f, // var_1.x, tmpvar_
	0x31, 0x2e, 0x79, 0x29, 0x0a, 0x20, 0x20, 0x2c, 0x20, 0x74, 0x6d, 0x70, 0x76, 0x61, 0x72, 0x5f, // 1.y).  , tmpvar_
	0x31, 0x2e, 0x7a, 0x29, 0x29, 0x20, 0x2d, 0x20, 0x28, 0x68, 0x61, 0x6c, 0x66, 0x29, 0x30, 0x2e, // 1.z)) - (half)0.
	0x35, 0x29, 0x3b, 0x0a, 0x20, 0x20, 0x5f, 0x6d, 0x74, 0x6c, 0x5f, 0x6f, 0x2e, 0x67, 0x6c, 0x5f, // 5);.  _mtl_o.gl_
	0x46, 0x72, 0x61, 0x67, 0x43, 0x6f, 0x6c, 0x6f, 0x72, 0x20, 0x3d, 0x20, 0x6d, 0x69, 0x78, 0x20, // FragColor = mix 
	0x28, 0x28, 0x68, 0x61, 0x6c, 0x66, 0x34, 0x29, 0x66, 0x6c, 0x6f, 0x61, 0x74, 0x34, 0x28, 0x31, // ((half4)float4(1
	0x2e, 0x30, 0x2c, 0x20, 0x31, 0x2e, 0x30, 0x2c, 0x20, 0x31, 0x2e, 0x30, 0x2c, 0x20, 0x31, 0x2e, // .0, 1.0, 1.0, 1.
	0x30, 0x29, 0x2c, 0x20, 0x28, 0x68, 0x61, 0x6c, 0x66, 0x34, 0x29, 0x66, 0x6c, 0x6f, 0x61, 0x74, // 0), (half4)float
	0x34, 0x28, 0x30, 0x2e, 0x30, 0x2c, 0x20, 0x30, 0x2e, 0x30, 0x2c, 0x20, 0x30, 0x2e, 0x30, 0x2c, // 4(0.0, 0.0, 0.0,
	0x20, 0x31, 0x2e, 0x30, 0x29, 0x2c, 0x20, 0x63, 0x6c, 0x61, 0x6d, 0x70, 0x20, 0x28, 0x28, 0x0a, //  1.0), clamp ((.
	0x20, 0x20, 0x20, 0x20, 0x28, 0x74, 0x6d, 0x70, 0x76, 0x61, 0x72, 0x5f, 0x32, 0x20, 0x2f, 0x20, //     (tmpvar_2 / 
	0x28, 0x61, 0x62, 0x73, 0x28, 0x64, 0x66, 0x64, 0x78, 0x28, 0x74, 0x6d, 0x70, 0x76, 0x61, 0x72, // (abs(dfdx(tmpvar
	0x5f, 0x32, 0x29, 0x29, 0x20, 0x2b, 0x20, 0x61, 0x62, 0x73, 0x28, 0x64, 0x66, 0x64, 0x79, 0x28, // _2)) + abs(dfdy(
	0x74, 0x6d, 0x70, 0x76, 0x61, 0x72, 0x5f, 0x32, 0x29, 0x29, 0x29, 0x29, 0x0a, 0x20, 0x20, 0x20, // tmpvar_2)))).   
	0x2b, 0x20, 0x28, 0x68, 0x61, 0x6c, 0x66, 0x29, 0x30, 0x2e, 0x35, 0x29, 0x2c, 0x20, 0x28, 0x68, // + (half)0.5), (h
	0x61, 0x6c, 0x66, 0x29, 0x30, 0x2e, 0x30, 0x2c, 0x20, 0x28, 0x68, 0x61, 0x6c, 0x66, 0x29, 0x31, // alf)0.0, (half)1
	0x2e, 0x30, 0x29, 0x29, 0x3b, 0x0a, 0x20, 0x20, 0x72, 0x65, 0x74, 0x75, 0x72, 0x6e, 0x20, 0x5f, // .0));.  return _
	0x6d, 0x74, 0x6c, 0x5f, 0x6f, 0x3b, 0x0a, 0x7d, 0x0a, 0x0a, 0x00,                               // mtl_o;.}...
};
extern const uint8_t* fs_texture_sdf_pssl;
extern const uint32_t fs_texture_sdf_pssl_size;
