static const uint8_t fs_clear3_glsl[250] =
{
	0x46, 0x53, 0x48, 0x04, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x10, 0x62, 0x67, 0x66, 0x78, 0x5f, // FSH........bgfx_
	0x63, 0x6c, 0x65, 0x61, 0x72, 0x5f, 0x63, 0x6f, 0x6c, 0x6f, 0x72, 0x02, 0x08, 0x00, 0x00, 0x08, // clear_color.....
	0x00, 0xd4, 0x00, 0x00, 0x00, 0x75, 0x6e, 0x69, 0x66, 0x6f, 0x72, 0x6d, 0x20, 0x76, 0x65, 0x63, // .....uniform vec
	0x34, 0x20, 0x62, 0x67, 0x66, 0x78, 0x5f, 0x63, 0x6c, 0x65, 0x61, 0x72, 0x5f, 0x63, 0x6f, 0x6c, // 4 bgfx_clear_col
	0x6f, 0x72, 0x5b, 0x38, 0x5d, 0x3b, 0x0a, 0x76, 0x6f, 0x69, 0x64, 0x20, 0x6d, 0x61, 0x69, 0x6e, // or[8];.void main
	0x20, 0x28, 0x29, 0x0a, 0x7b, 0x0a, 0x20, 0x20, 0x67, 0x6c, 0x5f, 0x46, 0x72, 0x61, 0x67, 0x44, //  ().{.  gl_FragD
	0x61, 0x74, 0x61, 0x5b, 0x30, 0x5d, 0x20, 0x3d, 0x20, 0x62, 0x67, 0x66, 0x78, 0x5f, 0x63, 0x6c, // ata[0] = bgfx_cl
	0x65, 0x61, 0x72, 0x5f, 0x63, 0x6f, 0x6c, 0x6f, 0x72, 0x5b, 0x30, 0x5d, 0x3b, 0x0a, 0x20, 0x20, // ear_color[0];.  
	0x67, 0x6c, 0x5f, 0x46, 0x72, 0x61, 0x67, 0x44, 0x61, 0x74, 0x61, 0x5b, 0x31, 0x5d, 0x20, 0x3d, // gl_FragData[1] =
	0x20, 0x62, 0x67, 0x66, 0x78, 0x5f, 0x63, 0x6c, 0x65, 0x61, 0x72, 0x5f, 0x63, 0x6f, 0x6c, 0x6f, //  bgfx_clear_colo
	0x72, 0x5b, 0x31, 0x5d, 0x3b, 0x0a, 0x20, 0x20, 0x67, 0x6c, 0x5f, 0x46, 0x72, 0x61, 0x67, 0x44, // r[1];.  gl_FragD
	0x61, 0x74, 0x61, 0x5b, 0x32, 0x5d, 0x20, 0x3d, 0x20, 0x62, 0x67, 0x66, 0x78, 0x5f, 0x63, 0x6c, // ata[2] = bgfx_cl
	0x65, 0x61, 0x72, 0x5f, 0x63, 0x6f, 0x6c, 0x6f, 0x72, 0x5b, 0x32, 0x5d, 0x3b, 0x0a, 0x20, 0x20, // ear_color[2];.  
	0x67, 0x6c, 0x5f, 0x46, 0x72, 0x61, 0x67, 0x44, 0x61, 0x74, 0x61, 0x5b, 0x33, 0x5d, 0x20, 0x3d, // gl_FragData[3] =
	0x20, 0x62, 0x67, 0x66, 0x78, 0x5f, 0x63, 0x6c, 0x65, 0x61, 0x72, 0x5f, 0x63, 0x6f, 0x6c, 0x6f, //  bgfx_clear_colo
	0x72, 0x5b, 0x33, 0x5d, 0x3b, 0x0a, 0x7d, 0x0a, 0x0a, 0x00,                                     // r[3];.}...
};
<<<<<<< HEAD
static const uint8_t fs_clear3_dx9[240] =
{
	0x46, 0x53, 0x48, 0x04, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x10, 0x62, 0x67, 0x66, 0x78, 0x5f, // FSH........bgfx_
	0x63, 0x6c, 0x65, 0x61, 0x72, 0x5f, 0x63, 0x6f, 0x6c, 0x6f, 0x72, 0x12, 0x08, 0x00, 0x00, 0x04, // clear_color.....
	0x00, 0xcc, 0x00, 0x00, 0x03, 0xff, 0xff, 0xfe, 0xff, 0x24, 0x00, 0x43, 0x54, 0x41, 0x42, 0x1c, // .........$.CTAB.
=======
static const uint8_t fs_clear3_dx9[244] =
{
	0x46, 0x53, 0x48, 0x04, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x10, 0x62, 0x67, 0x66, 0x78, 0x5f, // FSH........bgfx_
	0x63, 0x6c, 0x65, 0x61, 0x72, 0x5f, 0x63, 0x6f, 0x6c, 0x6f, 0x72, 0x12, 0x08, 0x00, 0x00, 0x04, // clear_color.....
	0x00, 0xd0, 0x00, 0x00, 0x03, 0xff, 0xff, 0xfe, 0xff, 0x25, 0x00, 0x43, 0x54, 0x41, 0x42, 0x1c, // .........%.CTAB.
>>>>>>> upstream/master
	0x00, 0x00, 0x00, 0x5b, 0x00, 0x00, 0x00, 0x00, 0x03, 0xff, 0xff, 0x01, 0x00, 0x00, 0x00, 0x1c, // ...[............
	0x00, 0x00, 0x00, 0x00, 0x91, 0x00, 0x00, 0x54, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x02, // .......T...0....
	0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x44, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x62, // .......D.......b
	0x67, 0x66, 0x78, 0x5f, 0x63, 0x6c, 0x65, 0x61, 0x72, 0x5f, 0x63, 0x6f, 0x6c, 0x6f, 0x72, 0x00, // gfx_clear_color.
	0xab, 0xab, 0xab, 0x01, 0x00, 0x03, 0x00, 0x01, 0x00, 0x04, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, // ................
	0x00, 0x00, 0x00, 0x70, 0x73, 0x5f, 0x33, 0x5f, 0x30, 0x00, 0x4d, 0x69, 0x63, 0x72, 0x6f, 0x73, // ...ps_3_0.Micros
	0x6f, 0x66, 0x74, 0x20, 0x28, 0x52, 0x29, 0x20, 0x48, 0x4c, 0x53, 0x4c, 0x20, 0x53, 0x68, 0x61, // oft (R) HLSL Sha
<<<<<<< HEAD
	0x64, 0x65, 0x72, 0x20, 0x43, 0x6f, 0x6d, 0x70, 0x69, 0x6c, 0x65, 0x72, 0x20, 0x39, 0x2e, 0x32, // der Compiler 9.2
	0x39, 0x2e, 0x39, 0x35, 0x32, 0x2e, 0x33, 0x31, 0x31, 0x31, 0x00, 0x01, 0x00, 0x00, 0x02, 0x00, // 9.952.3111......
	0x08, 0x0f, 0x80, 0x00, 0x00, 0xe4, 0xa0, 0x01, 0x00, 0x00, 0x02, 0x01, 0x08, 0x0f, 0x80, 0x01, // ................
	0x00, 0xe4, 0xa0, 0x01, 0x00, 0x00, 0x02, 0x02, 0x08, 0x0f, 0x80, 0x02, 0x00, 0xe4, 0xa0, 0x01, // ................
	0x00, 0x00, 0x02, 0x03, 0x08, 0x0f, 0x80, 0x03, 0x00, 0xe4, 0xa0, 0xff, 0xff, 0x00, 0x00, 0x00, // ................
};
static const uint8_t fs_clear3_dx11[439] =
{
	0x46, 0x53, 0x48, 0x04, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x10, 0x62, 0x67, 0x66, 0x78, 0x5f, // FSH........bgfx_
	0x63, 0x6c, 0x65, 0x61, 0x72, 0x5f, 0x63, 0x6f, 0x6c, 0x6f, 0x72, 0x12, 0x08, 0x00, 0x00, 0x08, // clear_color.....
	0x00, 0x90, 0x01, 0x44, 0x58, 0x42, 0x43, 0x12, 0x80, 0x92, 0xa3, 0x15, 0xef, 0x86, 0x85, 0x80, // ...DXBC.........
	0xb7, 0x87, 0xf9, 0x1f, 0xb5, 0xa2, 0x4a, 0x01, 0x00, 0x00, 0x00, 0x90, 0x01, 0x00, 0x00, 0x03, // ......J.........
	0x00, 0x00, 0x00, 0x2c, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00, 0xdc, 0x00, 0x00, 0x00, 0x49, // ...,...`.......I
	0x53, 0x47, 0x4e, 0x2c, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x20, // SGN,........... 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, // ................
	0x00, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00, 0x53, 0x56, 0x5f, 0x50, 0x4f, 0x53, 0x49, 0x54, 0x49, // .......SV_POSITI
	0x4f, 0x4e, 0x00, 0x4f, 0x53, 0x47, 0x4e, 0x74, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x08, // ON.OSGNt........
	0x00, 0x00, 0x00, 0x68, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, // ...h............
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00, 0x68, 0x00, 0x00, 0x00, 0x01, // ...........h....
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x0f, // ................
	0x00, 0x00, 0x00, 0x68, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, // ...h............
	0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00, 0x68, 0x00, 0x00, 0x00, 0x03, // ...........h....
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x0f, // ................
	0x00, 0x00, 0x00, 0x53, 0x56, 0x5f, 0x54, 0x41, 0x52, 0x47, 0x45, 0x54, 0x00, 0xab, 0xab, 0x53, // ...SV_TARGET...S
	0x48, 0x44, 0x52, 0xac, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x2b, 0x00, 0x00, 0x00, 0x59, // HDR....@...+...Y
	0x00, 0x00, 0x04, 0x46, 0x8e, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x65, // ...F. .........e
	0x00, 0x00, 0x03, 0xf2, 0x20, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x65, 0x00, 0x00, 0x03, 0xf2, // .... ......e....
	0x20, 0x10, 0x00, 0x01, 0x00, 0x00, 0x00, 0x65, 0x00, 0x00, 0x03, 0xf2, 0x20, 0x10, 0x00, 0x02, //  ......e.... ...
	0x00, 0x00, 0x00, 0x65, 0x00, 0x00, 0x03, 0xf2, 0x20, 0x10, 0x00, 0x03, 0x00, 0x00, 0x00, 0x36, // ...e.... ......6
	0x00, 0x00, 0x06, 0xf2, 0x20, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46, 0x8e, 0x20, 0x00, 0x00, // .... ......F. ..
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x36, 0x00, 0x00, 0x06, 0xf2, 0x20, 0x10, 0x00, 0x01, // .......6.... ...
	0x00, 0x00, 0x00, 0x46, 0x8e, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x36, // ...F. .........6
	0x00, 0x00, 0x06, 0xf2, 0x20, 0x10, 0x00, 0x02, 0x00, 0x00, 0x00, 0x46, 0x8e, 0x20, 0x00, 0x00, // .... ......F. ..
	0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x36, 0x00, 0x00, 0x06, 0xf2, 0x20, 0x10, 0x00, 0x03, // .......6.... ...
	0x00, 0x00, 0x00, 0x46, 0x8e, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x3e, // ...F. .........>
	0x00, 0x00, 0x01, 0x00, 0x00, 0x80, 0x00,                                                       // .......
};
static const uint8_t fs_clear3_mtl[735] =
{
	0x46, 0x53, 0x48, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xd0, 0x02, 0x00, 0x00, 0x75, 0x73, // FSH...........us
=======
	0x64, 0x65, 0x72, 0x20, 0x43, 0x6f, 0x6d, 0x70, 0x69, 0x6c, 0x65, 0x72, 0x20, 0x31, 0x30, 0x2e, // der Compiler 10.
	0x30, 0x2e, 0x31, 0x30, 0x30, 0x31, 0x31, 0x2e, 0x31, 0x36, 0x33, 0x38, 0x34, 0x00, 0xab, 0x01, // 0.10011.16384...
	0x00, 0x00, 0x02, 0x00, 0x08, 0x0f, 0x80, 0x00, 0x00, 0xe4, 0xa0, 0x01, 0x00, 0x00, 0x02, 0x01, // ................
	0x08, 0x0f, 0x80, 0x01, 0x00, 0xe4, 0xa0, 0x01, 0x00, 0x00, 0x02, 0x02, 0x08, 0x0f, 0x80, 0x02, // ................
	0x00, 0xe4, 0xa0, 0x01, 0x00, 0x00, 0x02, 0x03, 0x08, 0x0f, 0x80, 0x03, 0x00, 0xe4, 0xa0, 0xff, // ................
	0xff, 0x00, 0x00, 0x00,                                                                         // ....
};
static const uint8_t fs_clear3_dx11[555] =
{
	0x46, 0x53, 0x48, 0x04, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x10, 0x62, 0x67, 0x66, 0x78, 0x5f, // FSH........bgfx_
	0x63, 0x6c, 0x65, 0x61, 0x72, 0x5f, 0x63, 0x6f, 0x6c, 0x6f, 0x72, 0x12, 0x08, 0x00, 0x00, 0x08, // clear_color.....
	0x00, 0x04, 0x02, 0x44, 0x58, 0x42, 0x43, 0xd5, 0x4f, 0xed, 0x6d, 0x3f, 0x90, 0xd6, 0xbb, 0x53, // ...DXBC.O.m?...S
	0x7b, 0xdc, 0x55, 0x0b, 0xda, 0x6f, 0x86, 0x01, 0x00, 0x00, 0x00, 0x04, 0x02, 0x00, 0x00, 0x04, // {.U..o..........
	0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0xa0, 0x00, 0x00, 0x00, 0x54, 0x01, 0x00, 0x00, 0x88, // ...0.......T....
	0x01, 0x00, 0x00, 0x41, 0x6f, 0x6e, 0x39, 0x68, 0x00, 0x00, 0x00, 0x68, 0x00, 0x00, 0x00, 0x00, // ...Aon9h...h....
	0x02, 0xff, 0xff, 0x38, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x01, 0x00, 0x24, 0x00, 0x00, // ...8...0.....$..
	0x00, 0x30, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x24, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, // .0...0...$...0..
	0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0xff, 0xff, 0x01, // ................
	0x00, 0x00, 0x02, 0x00, 0x08, 0x0f, 0x80, 0x00, 0x00, 0xe4, 0xa0, 0x01, 0x00, 0x00, 0x02, 0x01, // ................
	0x08, 0x0f, 0x80, 0x01, 0x00, 0xe4, 0xa0, 0x01, 0x00, 0x00, 0x02, 0x02, 0x08, 0x0f, 0x80, 0x02, // ................
	0x00, 0xe4, 0xa0, 0x01, 0x00, 0x00, 0x02, 0x03, 0x08, 0x0f, 0x80, 0x03, 0x00, 0xe4, 0xa0, 0xff, // ................
	0xff, 0x00, 0x00, 0x53, 0x48, 0x44, 0x52, 0xac, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x2b, // ...SHDR....@...+
	0x00, 0x00, 0x00, 0x59, 0x00, 0x00, 0x04, 0x46, 0x8e, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, // ...Y...F. ......
	0x00, 0x00, 0x00, 0x65, 0x00, 0x00, 0x03, 0xf2, 0x20, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x65, // ...e.... ......e
	0x00, 0x00, 0x03, 0xf2, 0x20, 0x10, 0x00, 0x01, 0x00, 0x00, 0x00, 0x65, 0x00, 0x00, 0x03, 0xf2, // .... ......e....
	0x20, 0x10, 0x00, 0x02, 0x00, 0x00, 0x00, 0x65, 0x00, 0x00, 0x03, 0xf2, 0x20, 0x10, 0x00, 0x03, //  ......e.... ...
	0x00, 0x00, 0x00, 0x36, 0x00, 0x00, 0x06, 0xf2, 0x20, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46, // ...6.... ......F
	0x8e, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x36, 0x00, 0x00, 0x06, 0xf2, // . .........6....
	0x20, 0x10, 0x00, 0x01, 0x00, 0x00, 0x00, 0x46, 0x8e, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, //  ......F. ......
	0x00, 0x00, 0x00, 0x36, 0x00, 0x00, 0x06, 0xf2, 0x20, 0x10, 0x00, 0x02, 0x00, 0x00, 0x00, 0x46, // ...6.... ......F
	0x8e, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x36, 0x00, 0x00, 0x06, 0xf2, // . .........6....
	0x20, 0x10, 0x00, 0x03, 0x00, 0x00, 0x00, 0x46, 0x8e, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, //  ......F. ......
	0x00, 0x00, 0x00, 0x3e, 0x00, 0x00, 0x01, 0x49, 0x53, 0x47, 0x4e, 0x2c, 0x00, 0x00, 0x00, 0x01, // ...>...ISGN,....
	0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, // ....... ........
	0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00, 0x53, // ...............S
	0x56, 0x5f, 0x50, 0x4f, 0x53, 0x49, 0x54, 0x49, 0x4f, 0x4e, 0x00, 0x4f, 0x53, 0x47, 0x4e, 0x74, // V_POSITION.OSGNt
	0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x68, 0x00, 0x00, 0x00, 0x00, // ...........h....
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, // ................
	0x00, 0x00, 0x00, 0x68, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, // ...h............
	0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00, 0x68, 0x00, 0x00, 0x00, 0x02, // ...........h....
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x0f, // ................
	0x00, 0x00, 0x00, 0x68, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, // ...h............
	0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00, 0x53, 0x56, 0x5f, 0x54, 0x41, // ...........SV_TA
	0x52, 0x47, 0x45, 0x54, 0x00, 0xab, 0xab, 0x00, 0x00, 0x80, 0x00,                               // RGET.......
};
static const uint8_t fs_clear3_mtl[711] =
{
	0x46, 0x53, 0x48, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xb8, 0x02, 0x00, 0x00, 0x75, 0x73, // FSH...........us
>>>>>>> upstream/master
	0x69, 0x6e, 0x67, 0x20, 0x6e, 0x61, 0x6d, 0x65, 0x73, 0x70, 0x61, 0x63, 0x65, 0x20, 0x6d, 0x65, // ing namespace me
	0x74, 0x61, 0x6c, 0x3b, 0x0a, 0x73, 0x74, 0x72, 0x75, 0x63, 0x74, 0x20, 0x78, 0x6c, 0x61, 0x74, // tal;.struct xlat
	0x4d, 0x74, 0x6c, 0x53, 0x68, 0x61, 0x64, 0x65, 0x72, 0x49, 0x6e, 0x70, 0x75, 0x74, 0x20, 0x7b, // MtlShaderInput {
	0x0a, 0x7d, 0x3b, 0x0a, 0x73, 0x74, 0x72, 0x75, 0x63, 0x74, 0x20, 0x78, 0x6c, 0x61, 0x74, 0x4d, // .};.struct xlatM
	0x74, 0x6c, 0x53, 0x68, 0x61, 0x64, 0x65, 0x72, 0x4f, 0x75, 0x74, 0x70, 0x75, 0x74, 0x20, 0x7b, // tlShaderOutput {
<<<<<<< HEAD
	0x0a, 0x20, 0x20, 0x68, 0x61, 0x6c, 0x66, 0x34, 0x20, 0x67, 0x6c, 0x5f, 0x46, 0x72, 0x61, 0x67, // .  half4 gl_Frag
	0x44, 0x61, 0x74, 0x61, 0x5f, 0x30, 0x20, 0x5b, 0x5b, 0x63, 0x6f, 0x6c, 0x6f, 0x72, 0x28, 0x30, // Data_0 [[color(0
	0x29, 0x5d, 0x5d, 0x3b, 0x0a, 0x20, 0x20, 0x68, 0x61, 0x6c, 0x66, 0x34, 0x20, 0x67, 0x6c, 0x5f, // )]];.  half4 gl_
	0x46, 0x72, 0x61, 0x67, 0x44, 0x61, 0x74, 0x61, 0x5f, 0x31, 0x20, 0x5b, 0x5b, 0x63, 0x6f, 0x6c, // FragData_1 [[col
	0x6f, 0x72, 0x28, 0x31, 0x29, 0x5d, 0x5d, 0x3b, 0x0a, 0x20, 0x20, 0x68, 0x61, 0x6c, 0x66, 0x34, // or(1)]];.  half4
	0x20, 0x67, 0x6c, 0x5f, 0x46, 0x72, 0x61, 0x67, 0x44, 0x61, 0x74, 0x61, 0x5f, 0x32, 0x20, 0x5b, //  gl_FragData_2 [
	0x5b, 0x63, 0x6f, 0x6c, 0x6f, 0x72, 0x28, 0x32, 0x29, 0x5d, 0x5d, 0x3b, 0x0a, 0x20, 0x20, 0x68, // [color(2)]];.  h
	0x61, 0x6c, 0x66, 0x34, 0x20, 0x67, 0x6c, 0x5f, 0x46, 0x72, 0x61, 0x67, 0x44, 0x61, 0x74, 0x61, // alf4 gl_FragData
	0x5f, 0x33, 0x20, 0x5b, 0x5b, 0x63, 0x6f, 0x6c, 0x6f, 0x72, 0x28, 0x33, 0x29, 0x5d, 0x5d, 0x3b, // _3 [[color(3)]];
	0x0a, 0x7d, 0x3b, 0x0a, 0x73, 0x74, 0x72, 0x75, 0x63, 0x74, 0x20, 0x78, 0x6c, 0x61, 0x74, 0x4d, // .};.struct xlatM
	0x74, 0x6c, 0x53, 0x68, 0x61, 0x64, 0x65, 0x72, 0x55, 0x6e, 0x69, 0x66, 0x6f, 0x72, 0x6d, 0x20, // tlShaderUniform
	0x7b, 0x0a, 0x20, 0x20, 0x66, 0x6c, 0x6f, 0x61, 0x74, 0x34, 0x20, 0x62, 0x67, 0x66, 0x78, 0x5f, // {.  float4 bgfx_
	0x63, 0x6c, 0x65, 0x61, 0x72, 0x5f, 0x63, 0x6f, 0x6c, 0x6f, 0x72, 0x5b, 0x38, 0x5d, 0x3b, 0x0a, // clear_color[8];.
	0x7d, 0x3b, 0x0a, 0x66, 0x72, 0x61, 0x67, 0x6d, 0x65, 0x6e, 0x74, 0x20, 0x78, 0x6c, 0x61, 0x74, // };.fragment xlat
	0x4d, 0x74, 0x6c, 0x53, 0x68, 0x61, 0x64, 0x65, 0x72, 0x4f, 0x75, 0x74, 0x70, 0x75, 0x74, 0x20, // MtlShaderOutput
	0x78, 0x6c, 0x61, 0x74, 0x4d, 0x74, 0x6c, 0x4d, 0x61, 0x69, 0x6e, 0x20, 0x28, 0x78, 0x6c, 0x61, // xlatMtlMain (xla
	0x74, 0x4d, 0x74, 0x6c, 0x53, 0x68, 0x61, 0x64, 0x65, 0x72, 0x49, 0x6e, 0x70, 0x75, 0x74, 0x20, // tMtlShaderInput
	0x5f, 0x6d, 0x74, 0x6c, 0x5f, 0x69, 0x20, 0x5b, 0x5b, 0x73, 0x74, 0x61, 0x67, 0x65, 0x5f, 0x69, // _mtl_i [[stage_i
	0x6e, 0x5d, 0x5d, 0x2c, 0x20, 0x63, 0x6f, 0x6e, 0x73, 0x74, 0x61, 0x6e, 0x74, 0x20, 0x78, 0x6c, // n]], constant xl
	0x61, 0x74, 0x4d, 0x74, 0x6c, 0x53, 0x68, 0x61, 0x64, 0x65, 0x72, 0x55, 0x6e, 0x69, 0x66, 0x6f, // atMtlShaderUnifo
	0x72, 0x6d, 0x26, 0x20, 0x5f, 0x6d, 0x74, 0x6c, 0x5f, 0x75, 0x20, 0x5b, 0x5b, 0x62, 0x75, 0x66, // rm& _mtl_u [[buf
	0x66, 0x65, 0x72, 0x28, 0x30, 0x29, 0x5d, 0x5d, 0x29, 0x0a, 0x7b, 0x0a, 0x20, 0x20, 0x78, 0x6c, // fer(0)]]).{.  xl
	0x61, 0x74, 0x4d, 0x74, 0x6c, 0x53, 0x68, 0x61, 0x64, 0x65, 0x72, 0x4f, 0x75, 0x74, 0x70, 0x75, // atMtlShaderOutpu
	0x74, 0x20, 0x5f, 0x6d, 0x74, 0x6c, 0x5f, 0x6f, 0x3b, 0x0a, 0x20, 0x20, 0x5f, 0x6d, 0x74, 0x6c, // t _mtl_o;.  _mtl
	0x5f, 0x6f, 0x2e, 0x67, 0x6c, 0x5f, 0x46, 0x72, 0x61, 0x67, 0x44, 0x61, 0x74, 0x61, 0x5f, 0x30, // _o.gl_FragData_0
	0x20, 0x3d, 0x20, 0x68, 0x61, 0x6c, 0x66, 0x34, 0x28, 0x5f, 0x6d, 0x74, 0x6c, 0x5f, 0x75, 0x2e, //  = half4(_mtl_u.
	0x62, 0x67, 0x66, 0x78, 0x5f, 0x63, 0x6c, 0x65, 0x61, 0x72, 0x5f, 0x63, 0x6f, 0x6c, 0x6f, 0x72, // bgfx_clear_color
	0x5b, 0x30, 0x5d, 0x29, 0x3b, 0x0a, 0x20, 0x20, 0x5f, 0x6d, 0x74, 0x6c, 0x5f, 0x6f, 0x2e, 0x67, // [0]);.  _mtl_o.g
	0x6c, 0x5f, 0x46, 0x72, 0x61, 0x67, 0x44, 0x61, 0x74, 0x61, 0x5f, 0x31, 0x20, 0x3d, 0x20, 0x68, // l_FragData_1 = h
	0x61, 0x6c, 0x66, 0x34, 0x28, 0x5f, 0x6d, 0x74, 0x6c, 0x5f, 0x75, 0x2e, 0x62, 0x67, 0x66, 0x78, // alf4(_mtl_u.bgfx
	0x5f, 0x63, 0x6c, 0x65, 0x61, 0x72, 0x5f, 0x63, 0x6f, 0x6c, 0x6f, 0x72, 0x5b, 0x31, 0x5d, 0x29, // _clear_color[1])
	0x3b, 0x0a, 0x20, 0x20, 0x5f, 0x6d, 0x74, 0x6c, 0x5f, 0x6f, 0x2e, 0x67, 0x6c, 0x5f, 0x46, 0x72, // ;.  _mtl_o.gl_Fr
	0x61, 0x67, 0x44, 0x61, 0x74, 0x61, 0x5f, 0x32, 0x20, 0x3d, 0x20, 0x68, 0x61, 0x6c, 0x66, 0x34, // agData_2 = half4
	0x28, 0x5f, 0x6d, 0x74, 0x6c, 0x5f, 0x75, 0x2e, 0x62, 0x67, 0x66, 0x78, 0x5f, 0x63, 0x6c, 0x65, // (_mtl_u.bgfx_cle
	0x61, 0x72, 0x5f, 0x63, 0x6f, 0x6c, 0x6f, 0x72, 0x5b, 0x32, 0x5d, 0x29, 0x3b, 0x0a, 0x20, 0x20, // ar_color[2]);.
	0x5f, 0x6d, 0x74, 0x6c, 0x5f, 0x6f, 0x2e, 0x67, 0x6c, 0x5f, 0x46, 0x72, 0x61, 0x67, 0x44, 0x61, // _mtl_o.gl_FragDa
	0x74, 0x61, 0x5f, 0x33, 0x20, 0x3d, 0x20, 0x68, 0x61, 0x6c, 0x66, 0x34, 0x28, 0x5f, 0x6d, 0x74, // ta_3 = half4(_mt
	0x6c, 0x5f, 0x75, 0x2e, 0x62, 0x67, 0x66, 0x78, 0x5f, 0x63, 0x6c, 0x65, 0x61, 0x72, 0x5f, 0x63, // l_u.bgfx_clear_c
	0x6f, 0x6c, 0x6f, 0x72, 0x5b, 0x33, 0x5d, 0x29, 0x3b, 0x0a, 0x20, 0x20, 0x72, 0x65, 0x74, 0x75, // olor[3]);.  retu
	0x72, 0x6e, 0x20, 0x5f, 0x6d, 0x74, 0x6c, 0x5f, 0x6f, 0x3b, 0x0a, 0x7d, 0x0a, 0x0a, 0x00,       // rn _mtl_o;.}...
};
=======
	0x0a, 0x20, 0x20, 0x66, 0x6c, 0x6f, 0x61, 0x74, 0x34, 0x20, 0x67, 0x6c, 0x5f, 0x46, 0x72, 0x61, // .  float4 gl_Fra
	0x67, 0x44, 0x61, 0x74, 0x61, 0x5f, 0x30, 0x20, 0x5b, 0x5b, 0x63, 0x6f, 0x6c, 0x6f, 0x72, 0x28, // gData_0 [[color(
	0x30, 0x29, 0x5d, 0x5d, 0x3b, 0x0a, 0x20, 0x20, 0x66, 0x6c, 0x6f, 0x61, 0x74, 0x34, 0x20, 0x67, // 0)]];.  float4 g
	0x6c, 0x5f, 0x46, 0x72, 0x61, 0x67, 0x44, 0x61, 0x74, 0x61, 0x5f, 0x31, 0x20, 0x5b, 0x5b, 0x63, // l_FragData_1 [[c
	0x6f, 0x6c, 0x6f, 0x72, 0x28, 0x31, 0x29, 0x5d, 0x5d, 0x3b, 0x0a, 0x20, 0x20, 0x66, 0x6c, 0x6f, // olor(1)]];.  flo
	0x61, 0x74, 0x34, 0x20, 0x67, 0x6c, 0x5f, 0x46, 0x72, 0x61, 0x67, 0x44, 0x61, 0x74, 0x61, 0x5f, // at4 gl_FragData_
	0x32, 0x20, 0x5b, 0x5b, 0x63, 0x6f, 0x6c, 0x6f, 0x72, 0x28, 0x32, 0x29, 0x5d, 0x5d, 0x3b, 0x0a, // 2 [[color(2)]];.
	0x20, 0x20, 0x66, 0x6c, 0x6f, 0x61, 0x74, 0x34, 0x20, 0x67, 0x6c, 0x5f, 0x46, 0x72, 0x61, 0x67, //   float4 gl_Frag
	0x44, 0x61, 0x74, 0x61, 0x5f, 0x33, 0x20, 0x5b, 0x5b, 0x63, 0x6f, 0x6c, 0x6f, 0x72, 0x28, 0x33, // Data_3 [[color(3
	0x29, 0x5d, 0x5d, 0x3b, 0x0a, 0x7d, 0x3b, 0x0a, 0x73, 0x74, 0x72, 0x75, 0x63, 0x74, 0x20, 0x78, // )]];.};.struct x
	0x6c, 0x61, 0x74, 0x4d, 0x74, 0x6c, 0x53, 0x68, 0x61, 0x64, 0x65, 0x72, 0x55, 0x6e, 0x69, 0x66, // latMtlShaderUnif
	0x6f, 0x72, 0x6d, 0x20, 0x7b, 0x0a, 0x20, 0x20, 0x66, 0x6c, 0x6f, 0x61, 0x74, 0x34, 0x20, 0x62, // orm {.  float4 b
	0x67, 0x66, 0x78, 0x5f, 0x63, 0x6c, 0x65, 0x61, 0x72, 0x5f, 0x63, 0x6f, 0x6c, 0x6f, 0x72, 0x5b, // gfx_clear_color[
	0x38, 0x5d, 0x3b, 0x0a, 0x7d, 0x3b, 0x0a, 0x66, 0x72, 0x61, 0x67, 0x6d, 0x65, 0x6e, 0x74, 0x20, // 8];.};.fragment 
	0x78, 0x6c, 0x61, 0x74, 0x4d, 0x74, 0x6c, 0x53, 0x68, 0x61, 0x64, 0x65, 0x72, 0x4f, 0x75, 0x74, // xlatMtlShaderOut
	0x70, 0x75, 0x74, 0x20, 0x78, 0x6c, 0x61, 0x74, 0x4d, 0x74, 0x6c, 0x4d, 0x61, 0x69, 0x6e, 0x20, // put xlatMtlMain 
	0x28, 0x78, 0x6c, 0x61, 0x74, 0x4d, 0x74, 0x6c, 0x53, 0x68, 0x61, 0x64, 0x65, 0x72, 0x49, 0x6e, // (xlatMtlShaderIn
	0x70, 0x75, 0x74, 0x20, 0x5f, 0x6d, 0x74, 0x6c, 0x5f, 0x69, 0x20, 0x5b, 0x5b, 0x73, 0x74, 0x61, // put _mtl_i [[sta
	0x67, 0x65, 0x5f, 0x69, 0x6e, 0x5d, 0x5d, 0x2c, 0x20, 0x63, 0x6f, 0x6e, 0x73, 0x74, 0x61, 0x6e, // ge_in]], constan
	0x74, 0x20, 0x78, 0x6c, 0x61, 0x74, 0x4d, 0x74, 0x6c, 0x53, 0x68, 0x61, 0x64, 0x65, 0x72, 0x55, // t xlatMtlShaderU
	0x6e, 0x69, 0x66, 0x6f, 0x72, 0x6d, 0x26, 0x20, 0x5f, 0x6d, 0x74, 0x6c, 0x5f, 0x75, 0x20, 0x5b, // niform& _mtl_u [
	0x5b, 0x62, 0x75, 0x66, 0x66, 0x65, 0x72, 0x28, 0x30, 0x29, 0x5d, 0x5d, 0x29, 0x0a, 0x7b, 0x0a, // [buffer(0)]]).{.
	0x20, 0x20, 0x78, 0x6c, 0x61, 0x74, 0x4d, 0x74, 0x6c, 0x53, 0x68, 0x61, 0x64, 0x65, 0x72, 0x4f, //   xlatMtlShaderO
	0x75, 0x74, 0x70, 0x75, 0x74, 0x20, 0x5f, 0x6d, 0x74, 0x6c, 0x5f, 0x6f, 0x3b, 0x0a, 0x20, 0x20, // utput _mtl_o;.  
	0x5f, 0x6d, 0x74, 0x6c, 0x5f, 0x6f, 0x2e, 0x67, 0x6c, 0x5f, 0x46, 0x72, 0x61, 0x67, 0x44, 0x61, // _mtl_o.gl_FragDa
	0x74, 0x61, 0x5f, 0x30, 0x20, 0x3d, 0x20, 0x5f, 0x6d, 0x74, 0x6c, 0x5f, 0x75, 0x2e, 0x62, 0x67, // ta_0 = _mtl_u.bg
	0x66, 0x78, 0x5f, 0x63, 0x6c, 0x65, 0x61, 0x72, 0x5f, 0x63, 0x6f, 0x6c, 0x6f, 0x72, 0x5b, 0x30, // fx_clear_color[0
	0x5d, 0x3b, 0x0a, 0x20, 0x20, 0x5f, 0x6d, 0x74, 0x6c, 0x5f, 0x6f, 0x2e, 0x67, 0x6c, 0x5f, 0x46, // ];.  _mtl_o.gl_F
	0x72, 0x61, 0x67, 0x44, 0x61, 0x74, 0x61, 0x5f, 0x31, 0x20, 0x3d, 0x20, 0x5f, 0x6d, 0x74, 0x6c, // ragData_1 = _mtl
	0x5f, 0x75, 0x2e, 0x62, 0x67, 0x66, 0x78, 0x5f, 0x63, 0x6c, 0x65, 0x61, 0x72, 0x5f, 0x63, 0x6f, // _u.bgfx_clear_co
	0x6c, 0x6f, 0x72, 0x5b, 0x31, 0x5d, 0x3b, 0x0a, 0x20, 0x20, 0x5f, 0x6d, 0x74, 0x6c, 0x5f, 0x6f, // lor[1];.  _mtl_o
	0x2e, 0x67, 0x6c, 0x5f, 0x46, 0x72, 0x61, 0x67, 0x44, 0x61, 0x74, 0x61, 0x5f, 0x32, 0x20, 0x3d, // .gl_FragData_2 =
	0x20, 0x5f, 0x6d, 0x74, 0x6c, 0x5f, 0x75, 0x2e, 0x62, 0x67, 0x66, 0x78, 0x5f, 0x63, 0x6c, 0x65, //  _mtl_u.bgfx_cle
	0x61, 0x72, 0x5f, 0x63, 0x6f, 0x6c, 0x6f, 0x72, 0x5b, 0x32, 0x5d, 0x3b, 0x0a, 0x20, 0x20, 0x5f, // ar_color[2];.  _
	0x6d, 0x74, 0x6c, 0x5f, 0x6f, 0x2e, 0x67, 0x6c, 0x5f, 0x46, 0x72, 0x61, 0x67, 0x44, 0x61, 0x74, // mtl_o.gl_FragDat
	0x61, 0x5f, 0x33, 0x20, 0x3d, 0x20, 0x5f, 0x6d, 0x74, 0x6c, 0x5f, 0x75, 0x2e, 0x62, 0x67, 0x66, // a_3 = _mtl_u.bgf
	0x78, 0x5f, 0x63, 0x6c, 0x65, 0x61, 0x72, 0x5f, 0x63, 0x6f, 0x6c, 0x6f, 0x72, 0x5b, 0x33, 0x5d, // x_clear_color[3]
	0x3b, 0x0a, 0x20, 0x20, 0x72, 0x65, 0x74, 0x75, 0x72, 0x6e, 0x20, 0x5f, 0x6d, 0x74, 0x6c, 0x5f, // ;.  return _mtl_
	0x6f, 0x3b, 0x0a, 0x7d, 0x0a, 0x0a, 0x00,                                                       // o;.}...
};
extern const uint8_t* fs_clear3_pssl;
extern const uint32_t fs_clear3_pssl_size;
>>>>>>> upstream/master
