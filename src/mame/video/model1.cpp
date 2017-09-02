// license:BSD-3-Clause
// copyright-holders:Olivier Galibert
<<<<<<< HEAD
#include "emu.h"
#include "video/segaic24.h"
=======

#include <glm/glm/geometric.hpp>

#include "emu.h"
>>>>>>> upstream/master
#include "cpu/mb86233/mb86233.h"
#include "includes/model1.h"

#define LOG_TGP_VIDEO 0

#define LOG_TGP(x)  do { if (LOG_TGP_VIDEO) logerror x; } while (0)
#define LOG_TGP_DEV(d,x)  do { if (LOG_TGP_VIDEO) d->logerror x; } while (0)


// Model 1 geometrizer TGP and rasterizer simulation
enum { FRAC_SHIFT = 16 };
enum { MOIRE = 0x01000000 };

<<<<<<< HEAD


struct vector_t {
	float x, y, z;
};

struct lightparam {
	float a;
	float d;
	float s;
	int p;
};

struct view {
	int xc, yc, x1, y1, x2, y2;
	float zoomx, zoomy, transx, transy;
	float a_bottom, a_top, a_left, a_right;
	float vxx, vyy, vzz, ayy, ayyc, ayys;
	float trans_mat[12];
	struct vector_t light;
	struct lightparam lightparams[32];
};

struct m1_spoint {
	INT32 x, y;
};

struct m1_point {
	float x, y, z;
	float xx, yy;
	struct m1_spoint s;
};


struct quad_m1 {
	struct m1_point *p[4];
	float z;
	int col;
};



static UINT32 readi(const UINT16 *adr)
{
	return adr[0]|(adr[1] << 16);
}

static INT16 readi16(const UINT16 *adr)
{
	return adr[0];
}

static float readf(const UINT16 *adr)
=======
uint32_t model1_state::readi(int adr) const
{
	return m_display_list_current[(adr + 0)&0x7fff] | (m_display_list_current[(adr + 1)&0x7fff] << 16);
}

int16_t model1_state::readi16(int adr) const
{
	return m_display_list_current[(adr + 0)&0x7fff];
}

float model1_state::readf(int adr) const
>>>>>>> upstream/master
{
	return u2f(readi(adr));
}

<<<<<<< HEAD
static void _transform_point(struct view *view, struct m1_point *p)
{
	struct m1_point q = *p;
	float *trans = view->trans_mat;
	float xx, zz;
	xx = trans[0]*q.x+trans[3]*q.y+trans[6]*q.z+trans[9]+view->vxx;
	p->y = trans[1]*q.x+trans[4]*q.y+trans[7]*q.z+trans[10]+view->vyy;
	zz = trans[2]*q.x+trans[5]*q.y+trans[8]*q.z+trans[11]+view->vzz;
	p->x = view->ayyc*xx-view->ayys*zz;
	p->z = view->ayys*xx+view->ayyc*zz;
}

static void transform_vector(struct view *view, struct vector_t *p)
{
	struct vector_t q = *p;
	float *trans = view->trans_mat;
	p->x = trans[0]*q.x+trans[3]*q.y+trans[6]*q.z;
	p->y = trans[1]*q.x+trans[4]*q.y+trans[7]*q.z;
	p->z = trans[2]*q.x+trans[5]*q.y+trans[8]*q.z;
}

static void normalize_vector(struct vector_t *p)
{
	float norm = sqrt(p->x*p->x+p->y*p->y+p->z*p->z);
	if(norm) {
		p->x /= norm;
		p->y /= norm;
		p->z /= norm;
	}
}

static float mult_vector(const struct vector_t *p, const struct vector_t *q)
{
	return p->x*q->x+p->y*q->y+p->z*q->z;
}

static float view_determinant(const struct m1_point *p1, const struct m1_point *p2, const struct m1_point *p3)
=======
void model1_state::view_t::transform_point(point_t *p) const
{
	point_t q = *p;
	float xx = translation[0] * q.x + translation[3] * q.y + translation[6] * q.z + translation[ 9] + vxx;
		p->y = translation[1] * q.x + translation[4] * q.y + translation[7] * q.z + translation[10] + vyy;
	float zz = translation[2] * q.x + translation[5] * q.y + translation[8] * q.z + translation[11] + vzz;
	p->x = ayyc * xx - ayys * zz;
	p->z = ayys * xx + ayyc * zz;
}

void model1_state::view_t::transform_vector(glm::vec3& p) const
{
	glm::vec3 q(p);
	glm::vec3 row1(translation[0], translation[3], translation[6]);
	glm::vec3 row2(translation[1], translation[4], translation[7]);
	glm::vec3 row3(translation[2], translation[5], translation[8]);
	p = glm::vec3(glm::dot(q, row1), glm::dot(q, row2), glm::dot(q, row3));
	//p->set_x(translation[0] * q.x() + translation[3] * q.y() + translation[6] * q.z());
	//p->set_y(translation[1] * q.x() + translation[4] * q.y() + translation[7] * q.z());
	//p->set_z(translation[2] * q.x() + translation[5] * q.y() + translation[8] * q.z());
}

void model1_state::cross_product(point_t* o, const point_t* p, const point_t* q) const
{
	o->x = p->y * q->z - q->y * p->z;
	o->y = p->z * q->x - q->z * p->x;
	o->z = p->x * q->y - q->x * p->y;
}

float model1_state::view_determinant(const point_t *p1, const point_t *p2, const point_t *p3) const
>>>>>>> upstream/master
{
	float x1 = p2->x - p1->x;
	float y1 = p2->y - p1->y;
	float z1 = p2->z - p1->z;
	float x2 = p3->x - p1->x;
	float y2 = p3->y - p1->y;
	float z2 = p3->z - p1->z;

<<<<<<< HEAD
	return p1->x*(y1*z2-y2*z1) + p1->y*(z1*x2-z2*x1) + p1->z*(x1*y2-x2*y1);
}


static void project_point(struct view *view, struct m1_point *p)
{
	p->xx = p->x / p->z;
	p->yy = p->y / p->z;
	p->s.x = view->xc+(p->xx*view->zoomx+view->transx);
	p->s.y = view->yc-(p->yy*view->zoomy+view->transy);
}

static void project_point_direct(struct view *view, struct m1_point *p)
{
	p->xx = p->x /*/ p->z*/;
	p->yy = p->y /*/ p->z*/;
	p->s.x = view->xc+(p->xx);
	p->s.y = view->yc-(p->yy);
}


static void draw_hline(bitmap_rgb32 &bitmap, int x1, int x2, int y, int color)
{
	UINT32 *base = &bitmap.pix32(y);
	while(x1 <= x2) {
=======
	return p1->x * (y1 * z2 - y2 * z1) + p1->y * (z1 * x2 - z2 * x1) + p1->z * (x1 * y2 - x2 * y1);
}

void model1_state::view_t::project_point(point_t *p) const
{
	p->xx = p->x / p->z;
	p->yy = p->y / p->z;
	p->s.x = xc + (p->xx * zoomx + viewx);
	p->s.y = yc - (p->yy * zoomy + viewy);
}

void model1_state::view_t::project_point_direct(point_t *p) const
{
	p->xx = p->x /*/ p->z*/;
	p->yy = p->y /*/ p->z*/;
	p->s.x = xc + p->xx;
	p->s.y = yc - p->yy;
}

void model1_state::draw_hline(bitmap_rgb32 &bitmap, int x1, int x2, int y, int color)
{
	uint32_t *base = &bitmap.pix32(y);
	while(x1 <= x2)
	{
>>>>>>> upstream/master
		base[x1] = color;
		x1++;
	}
}

<<<<<<< HEAD
static void draw_hline_moired(bitmap_rgb32 &bitmap, int x1, int x2, int y, int color)
{
	UINT32 *base = &bitmap.pix32(y);
	while(x1 <= x2) {
		if((x1^y)&1)
			base[x1] = color;
=======
void model1_state::draw_hline_moired(bitmap_rgb32 &bitmap, int x1, int x2, int y, int color)
{
	uint32_t *base = &bitmap.pix32(y);
	while(x1 <= x2)
	{
		if((x1^y) & 1)
		{
			base[x1] = color;
		}
>>>>>>> upstream/master
		x1++;
	}
}

<<<<<<< HEAD
static void fill_slope(bitmap_rgb32 &bitmap, struct view *view, int color, INT32 x1, INT32 x2, INT32 sl1, INT32 sl2, INT32 y1, INT32 y2, INT32 *nx1, INT32 *nx2)
{
	if(y1 > view->y2)
		return;

	if(y2 <= view->y1) {
		int delta = y2-y1;
		*nx1 = x1+delta*sl1;
		*nx2 = x2+delta*sl2;
		return;
	}

	if(y2 > view->y2)
		y2 = view->y2+1;

	if(y1 < view->y1) {
		int delta = view->y1 - y1;
		x1 += delta*sl1;
		x2 += delta*sl2;
		y1 = view->y1;
	}

	if(x1 > x2 || (x1==x2 && sl1 > sl2)) {
		INT32 t, *tp;
		t = x1;
		x1 = x2;
		x2 = t;
		t = sl1;
		sl1 = sl2;
		sl2 = t;
		tp = nx1;
=======
void model1_state::fill_slope(bitmap_rgb32 &bitmap, view_t *view, int color, int32_t x1, int32_t x2, int32_t sl1, int32_t sl2, int32_t y1, int32_t y2, int32_t *nx1, int32_t *nx2)
{
	if(y1 > view->y2)
	{
		return;
	}

	if (y2 <= view->y1)
	{
		int delta = y2 - y1;
		*nx1 = x1 + delta * sl1;
		*nx2 = x2 + delta * sl2;
		return;
	}

	if (y2 > view->y2)
	{
		y2 = view->y2 + 1;
	}

	if (y1 < view->y1)
	{
		int delta = view->y1 - y1;
		x1 += delta * sl1;
		x2 += delta * sl2;
		y1 = view->y1;
	}

	if (x1 > x2 || (x1 == x2 && sl1 > sl2))
	{
		int32_t t = x1;
		x1 = x2;
		x2 = t;

		t = sl1;
		sl1 = sl2;
		sl2 = t;

		int32_t *tp = nx1;
>>>>>>> upstream/master
		nx1 = nx2;
		nx2 = tp;
	}

<<<<<<< HEAD
	while(y1 < y2) {
		if(y1 >= view->y1) {
			int xx1 = x1>>FRAC_SHIFT;
			int xx2 = x2>>FRAC_SHIFT;
			if(xx1 <= view->x2 || xx2 >= view->x1) {
				if(xx1 < view->x1)
					xx1 = view->x1;
				if(xx2 > view->x2)
					xx2 = view->x2;

				if(color & MOIRE)
					draw_hline_moired(bitmap, xx1, xx2, y1, color);
				else
					draw_hline(bitmap, xx1, xx2, y1, color);
=======
	while(y1 < y2)
	{
		if(y1 >= view->y1)
		{
			int xx1 = x1>>FRAC_SHIFT;
			int xx2 = x2>>FRAC_SHIFT;
			if(xx1 <= view->x2 || xx2 >= view->x1)
			{
				if(xx1 < view->x1)
				{
					xx1 = view->x1;
				}
				if(xx2 > view->x2)
				{
					xx2 = view->x2;
				}

				if(color & MOIRE)
				{
					draw_hline_moired(bitmap, xx1, xx2, y1, color);
				}
				else
				{
					draw_hline(bitmap, xx1, xx2, y1, color);
				}
>>>>>>> upstream/master
			}
		}

		x1 += sl1;
		x2 += sl2;
		y1++;
	}
	*nx1 = x1;
	*nx2 = x2;
}

<<<<<<< HEAD
static void fill_line(bitmap_rgb32 &bitmap, struct view *view, int color, INT32 y, INT32 x1, INT32 x2)
=======
void model1_state::fill_line(bitmap_rgb32 &bitmap, view_t *view, int color, int32_t y, int32_t x1, int32_t x2)
>>>>>>> upstream/master
{
	int xx1 = x1>>FRAC_SHIFT;
	int xx2 = x2>>FRAC_SHIFT;

	if(y > view->y2 || y < view->y1)
		return;

	if(xx1 <= view->x2 || xx2 >= view->x1) {
		if(xx1 < view->x1)
			xx1 = view->x1;
		if(xx2 > view->x2)
			xx2 = view->x2;

		if(color & MOIRE)
			draw_hline_moired(bitmap, xx1, xx2, y, color);
		else
			draw_hline(bitmap, xx1, xx2, y, color);
	}
}

<<<<<<< HEAD
static void fill_quad(device_t *device,bitmap_rgb32 &bitmap, struct view *view, const struct quad_m1 *q)
{
	INT32 sl1, sl2, cury, limy, x1, x2;
	int pmin, pmax, i, ps1, ps2;
	struct m1_spoint p[8];
	int color = q->col;

	if(color < 0) {
		color = -1-color;
		LOG_TGP_DEV(device,("VIDEOD: Q (%d, %d)-(%d, %d)-(%d, %d)-(%d, %d)\n",
					q->p[0]->s.x, q->p[0]->s.y,
					q->p[1]->s.x, q->p[1]->s.y,
					q->p[2]->s.x, q->p[2]->s.y,
					q->p[3]->s.x, q->p[3]->s.y));
	}

	for(i=0; i<4; i++) {
		p[i].x = p[i+4].x = q->p[i]->s.x << FRAC_SHIFT;
		p[i].y = p[i+4].y = q->p[i]->s.y;
	}

	pmin = pmax = 0;
	for(i=1; i<4; i++) {
		if(p[i].y < p[pmin].y)
			pmin = i;
		if(p[i].y > p[pmax].y)
			pmax = i;
	}

	cury = p[pmin].y;
	limy = p[pmax].y;

	if(cury == limy) {
		x1 = x2 = p[0].x;
		for(i=1; i<4; i++) {
			if(p[i].x < x1)
				x1 = p[i].x;
			if(p[i].x > x2)
				x2 = p[i].x;
=======
void model1_state::fill_quad(bitmap_rgb32 &bitmap, view_t *view, const quad_t& q) const
{
	spoint_t p[8];
	int color = q.col;

	if (color < 0)
	{
		color = -1 - color;
		LOG_TGP_DEV(this,("VIDEOD: Q (%d, %d)-(%d, %d)-(%d, %d)-(%d, %d)\n",
					q.p[0]->s.x, q.p[0]->s.y,
					q.p[1]->s.x, q.p[1]->s.y,
					q.p[2]->s.x, q.p[2]->s.y,
					q.p[3]->s.x, q.p[3]->s.y));
	}

	for (int i = 0; i < 4; i++)
	{
		p[i].x = p[i+4].x = q.p[i]->s.x << FRAC_SHIFT;
		p[i].y = p[i+4].y = q.p[i]->s.y;
	}

	int pmin = 0;
	int pmax = 0;
	for (int i = 1; i < 4; i++)
	{
		if(p[i].y < p[pmin].y)
		{
			pmin = i;
		}
		if(p[i].y > p[pmax].y)
		{
			pmax = i;
		}
	}

	int32_t cury = p[pmin].y;
	int32_t limy = p[pmax].y;

	int32_t x1, x2;
	if (cury == limy)
	{
		x1 = p[0].x;
		x2 = p[0].x;
		for (int i = 1; i < 4; i++)
		{
			if (p[i].x < x1)
			{
				x1 = p[i].x;
			}
			if (p[i].x > x2)
			{
				x2 = p[i].x;
			}
>>>>>>> upstream/master
		}
		fill_line(bitmap, view, color, cury, x1, x2);
		return;
	}

	if(cury > view->y2)
<<<<<<< HEAD
		return;
	if(limy <= view->y1)
		return;

	if(limy > view->y2)
		limy = view->y2;

	ps1 = pmin+4;
	ps2 = pmin;

	goto startup;

	for(;;) {
		if(p[ps1-1].y == p[ps2+1].y) {
			fill_slope(bitmap, view, color, x1, x2, sl1, sl2, cury, p[ps1-1].y, &x1, &x2);
			cury = p[ps1-1].y;
			if(cury >= limy)
				break;
=======
	{
		return;
	}
	if(limy <= view->y1)
	{
		return;
	}

	if(limy > view->y2)
	{
		limy = view->y2;
	}

	int ps1 = pmin+4;
	int ps2 = pmin;

	goto startup;

	int32_t sl1, sl2;
	for(;;)
	{
		if (p[ps1 - 1].y == p[ps2 + 1].y)
		{
			fill_slope(bitmap, view, color, x1, x2, sl1, sl2, cury, p[ps1 - 1].y, &x1, &x2);
			cury = p[ps1 - 1].y;
			if(cury >= limy)
			{
				break;
			}
>>>>>>> upstream/master
			ps1--;
			ps2++;

		startup:
			while(p[ps1-1].y == cury)
<<<<<<< HEAD
				ps1--;
			while(p[ps2+1].y == cury)
				ps2++;
			x1 = p[ps1].x;
			x2 = p[ps2].x;
			sl1 = (x1-p[ps1-1].x)/(cury-p[ps1-1].y);
			sl2 = (x2-p[ps2+1].x)/(cury-p[ps2+1].y);
		} else if(p[ps1-1].y < p[ps2+1].y) {
			fill_slope(bitmap, view, color, x1, x2, sl1, sl2, cury, p[ps1-1].y, &x1, &x2);
			cury = p[ps1-1].y;
			if(cury >= limy)
				break;
			ps1--;
			while(p[ps1-1].y == cury)
				ps1--;
			x1 = p[ps1].x;
			sl1 = (x1-p[ps1-1].x)/(cury-p[ps1-1].y);
		} else {
			fill_slope(bitmap, view, color, x1, x2, sl1, sl2, cury, p[ps2+1].y, &x1, &x2);
			cury = p[ps2+1].y;
			if(cury >= limy)
				break;
			ps2++;
			while(p[ps2+1].y == cury)
				ps2++;
			x2 = p[ps2].x;
			sl2 = (x2-p[ps2+1].x)/(cury-p[ps2+1].y);
		}
	}
	if(cury == limy)
		fill_line(bitmap, view, color, cury, x1, x2);
}
#if 0
static void draw_line(bitmap_rgb32 &bitmap, struct view *view, int color, int x1, int y1, int x2, int y2)
{
	int s1x, s1y, s2x, s2y;
	int d1, d2;
	int cur;
	int x, y;

	if((x1 < view->x1 && x2 < view->x1) ||
=======
			{
				ps1--;
			}
			while(p[ps2+1].y == cury)
			{
				ps2++;
			}
			x1 = p[ps1].x;
			x2 = p[ps2].x;
			sl1 = (x1 - p[ps1 - 1].x) / (cury - p[ps1 - 1].y);
			sl2 = (x2 - p[ps2 + 1].x) / (cury - p[ps2 + 1].y);
		}
		else if (p[ps1 - 1].y < p[ps2 + 1].y)
		{
			fill_slope(bitmap, view, color, x1, x2, sl1, sl2, cury, p[ps1 - 1].y, &x1, &x2);
			cury = p[ps1 - 1].y;
			if(cury >= limy)
			{
				break;
			}
			ps1--;
			while(p[ps1 - 1].y == cury)
			{
				ps1--;
			}
			x1 = p[ps1].x;
			sl1 = (x1 - p[ps1 - 1].x) / (cury - p[ps1 - 1].y);
		}
		else
		{
			fill_slope(bitmap, view, color, x1, x2, sl1, sl2, cury, p[ps2 + 1].y, &x1, &x2);
			cury = p[ps2 + 1].y;
			if(cury >= limy)
			{
				break;
			}
			ps2++;
			while(p[ps2 + 1].y == cury)
			{
				ps2++;
			}
			x2 = p[ps2].x;
			sl2 = (x2 - p[ps2 + 1].x) / (cury - p[ps2 + 1].y);
		}
	}
	if(cury == limy)
	{
		fill_line(bitmap, view, color, cury, x1, x2);
	}
}

#if 0
void model1_state::draw_line(bitmap_rgb32 &bitmap, model1_state::view_t *view, int color, int x1, int y1, int x2, int y2) const
{
	if ((x1 < view->x1 && x2 < view->x1) ||
>>>>>>> upstream/master
		(x1 > view->x2 && x2 > view->x2) ||
		(y1 < view->y1 && y2 < view->y1) ||
		(y1 > view->y2 && y2 > view->y2))
		return;

<<<<<<< HEAD
	x = x1;
	y = y1;
	s1x = 1;
	s1y = 0;
	s2x = 0;
	s2y = 1;

	d1 = x2-x1;
	d2 = y2-y1;
	if(d1<0) {
		s1x = -s1x;
		d1 = -d1;
	}
	if(d2<0) {
		s2y = -s2y;
		d2 = -d2;
	}
	if(d1 < d2) {
		int t;
		t = s1x;
=======
	int x = x1;
	int y = y1;
	int s1x = 1;
	int s1y = 0;
	int s2x = 0;
	int s2y = 1;

	int d1 = x2-x1;
	int d2 = y2-y1;
	if (d1 < 0)
	{
		s1x = -s1x;
		d1 = -d1;
	}
	if (d2 < 0)
	{
		s2y = -s2y;
		d2 = -d2;
	}
	if (d1 < d2)
	{
		int t = s1x;
>>>>>>> upstream/master
		s1x = s2x;
		s2x = t;
		t = s1y;
		s1y = s2y;
		s2y = t;
		t = d1;
		d1 = d2;
		d2 = t;
	}

	if(d1 > 600)
<<<<<<< HEAD
		return;

	cur = 0;
	while(x != x2 || y != y2) {
		if(x>=view->x1 && x<=view->x2 && y>=view->y1 && y<=view->y2)
			bitmap.pix32(y, x) = color;
		x += s1x;
		y += s1y;
		cur += d2;
		if(cur >= d1) {
=======
	{
		return;
	}

	int cur = 0;
	while (x != x2 || y != y2)
	{
		if (x >= view->x1 && x <= view->x2 && y >= view->y1 && y <= view->y2)
		{
			bitmap.pix32(y, x) = color;
		}
		x += s1x;
		y += s1y;
		cur += d2;
		if (cur >= d1)
		{
>>>>>>> upstream/master
			cur -= d1;
			x += s2x;
			y += s2y;
		}
	}
<<<<<<< HEAD
	if(x>=view->x1 && x<=view->x2 && y>=view->y1 && y<=view->y2)
		bitmap.pix16(y, x) = color;
}
#endif
static int comp_quads(const void *q1, const void *q2)
{
	float z1 = (*(const struct quad_m1 **)q1)->z;
	float z2 = (*(const struct quad_m1 **)q2)->z;

	if(z1<z2)
		return +1;
	if(z1>z2)
		return -1;

	if (*(const struct quad_m1 **)q1 - *(const struct quad_m1 **)q2 < 0)
=======
	if (x >= view->x1 && x <= view->x2 && y >= view->y1 && y <= view->y2)
	{
		bitmap.pix16(y, x) = color;
	}
}
#endif

static int comp_quads(const void *q1, const void *q2)
{
	model1_state::quad_t* const* c1 = static_cast<model1_state::quad_t* const*>(q1);
	model1_state::quad_t* const* c2 = static_cast<model1_state::quad_t* const*>(q2);

	return (*c1)->compare(*c2);
}

int model1_state::quad_t::compare(const model1_state::quad_t* other) const
{
	float z2 = other->z;

	if (z < z2)
		return +1;
	if (z > z2)
		return -1;

	if (this - other < 0)
>>>>>>> upstream/master
		return -1;

	return +1;
}

<<<<<<< HEAD
void model1_state::sort_quads()
{
	int count = m_quadpt - m_quaddb;
	int i;
	for(i=0; i<count; i++)
		m_quadind[i] = m_quaddb+i;
	qsort(m_quadind, count, sizeof(struct quad_m1 *), comp_quads);
}

void model1_state::unsort_quads()
{
	int count = m_quadpt - m_quaddb;
	int i;
	for(i=0; i<count; i++)
		m_quadind[i] = m_quaddb+i;
=======
void model1_state::sort_quads() const
{
	const int count = m_quadpt - m_quaddb;
	for (int i = 0; i < count; i++)
	{
		m_quadind[i] = m_quaddb + i;
	}
	qsort(m_quadind, count, sizeof(model1_state::quad_t*), comp_quads);
}

void model1_state::unsort_quads() const
{
	const int count = m_quadpt - m_quaddb;
	for (int i = 0; i < count; i++)
	{
		m_quadind[i] = m_quaddb + i;
	}
>>>>>>> upstream/master
}


void model1_state::draw_quads(bitmap_rgb32 &bitmap, const rectangle &cliprect)
{
<<<<<<< HEAD
	struct view *view = m_view;
	int count = m_quadpt - m_quaddb;
	int i;
=======
	view_t *view = m_view;
	int count = m_quadpt - m_quaddb;
>>>>>>> upstream/master

	/* clip to the cliprect */
	int save_x1 = view->x1;
	int save_x2 = view->x2;
	int save_y1 = view->y1;
	int save_y2 = view->y2;
<<<<<<< HEAD
	view->x1 = MAX(view->x1, cliprect.min_x);
	view->x2 = MIN(view->x2, cliprect.max_x);
	view->y1 = MAX(view->y1, cliprect.min_y);
	view->y2 = MIN(view->y2, cliprect.max_y);

	for(i=0; i<count; i++) {
		struct quad_m1 *q = m_quadind[i];

		fill_quad(this, bitmap, view, q);
#if 0
		draw_line(bitmap, m_palette->black_pen(), q->p[0]->s.x, q->p[0]->s.y, q->p[1]->s.x, q->p[1]->s.y);
		draw_line(bitmap, m_palette->black_pen(), q->p[1]->s.x, q->p[1]->s.y, q->p[2]->s.x, q->p[2]->s.y);
		draw_line(bitmap, m_palette->black_pen(), q->p[2]->s.x, q->p[2]->s.y, q->p[3]->s.x, q->p[3]->s.y);
		draw_line(bitmap, m_palette->black_pen(), q->p[3]->s.x, q->p[3]->s.y, q->p[0]->s.x, q->p[0]->s.y);
=======
	view->x1 = std::max(view->x1, cliprect.min_x);
	view->x2 = std::min(view->x2, cliprect.max_x);
	view->y1 = std::max(view->y1, cliprect.min_y);
	view->y2 = std::min(view->y2, cliprect.max_y);

	for (int i = 0; i < count; i++)
	{
		fill_quad(bitmap, view, *m_quadind[i]);
#if 0
		quad_t *q = m_quadind[i];
		draw_line(bitmap, m_palette->black_pen(), q.p[0]->s.x, q.p[0]->s.y, q.p[1]->s.x, q.p[1]->s.y);
		draw_line(bitmap, m_palette->black_pen(), q.p[1]->s.x, q.p[1]->s.y, q.p[2]->s.x, q.p[2]->s.y);
		draw_line(bitmap, m_palette->black_pen(), q.p[2]->s.x, q.p[2]->s.y, q.p[3]->s.x, q.p[3]->s.y);
		draw_line(bitmap, m_palette->black_pen(), q.p[3]->s.x, q.p[3]->s.y, q.p[0]->s.x, q.p[0]->s.y);
>>>>>>> upstream/master
#endif
	}

	view->x1 = save_x1;
	view->x2 = save_x2;
	view->y1 = save_y1;
	view->y2 = save_y2;
}
#if 0
<<<<<<< HEAD
static UINT16 scale_color(UINT16 color, float level)
{
	int r, g, b;
	r = ((color >> 10) & 31)*level;
	g = ((color >> 5) & 31)*level;
	b = (color & 31)*level;
	return (r<<10)|(g<<5)|b;
=======
uint16_t model1_state::scale_color(uint16_t color, float level) const
{
	int r = ((color >> 10) & 31) * level;
	int g = ((color >>  5) & 31) * level;
	int b =         (color & 31) * level;
	return (r << 10) | (g << 5) | b;
>>>>>>> upstream/master
}
#endif
// xe = xc + (x/z * zm + tx)
// xe < x1 => xc + (x/z * zm + tx) < x1
//         => x/z < (x1-xc-tx)/zm
//         => x < z*(x1-xc-tx)/zm

// ye = yc - (y/z * zm + ty)
// ye < y1 => yc - (y/z * zm + ty) < y1
//         => -y/z < (y1-yc+ty)/zm
//         => y > -z*(y1-yc+ty)/zm

// xf = zf*a
// xx = x1*t+x2(1-t); zz = z1*t+z2(1-t)
// => x1*t+x2(1-t) = z1*t*a+z2*(1-t)*a
// => t*(x1-x2+a*(z2-z1) = -x2+a*z2
// => t = (z2*a-x2)/((z2-z1)*a-(x2-x1))

<<<<<<< HEAD
static void recompute_frustrum(struct view *view)
{
	view->a_left   = ( view->x1-view->xc-view->transx)/view->zoomx;
	view->a_right  = ( view->x2-view->xc-view->transx)/view->zoomx;
	view->a_bottom = (-view->y1+view->yc-view->transy)/view->zoomy;
	view->a_top    = (-view->y2+view->yc-view->transy)/view->zoomy;
}

static int fclip_isc_bottom(struct view *view, struct m1_point *p)
{
	return p->y > p->z*view->a_bottom;
}

static void fclip_clip_bottom(struct view *view, struct m1_point *pt, struct m1_point *p1, struct m1_point *p2)
{
	float t = (p2->z*view->a_bottom-p2->y)/((p2->z-p1->z)*view->a_bottom-(p2->y-p1->y));
	pt->x = p1->x*t + p2->x*(1-t);
	pt->y = p1->y*t + p2->y*(1-t);
	pt->z = p1->z*t + p2->z*(1-t);
	project_point(view, pt);
}

static int fclip_isc_top(struct view *view, struct m1_point *p)
{
	return p->y < p->z*view->a_top;
}

static void fclip_clip_top(struct view *view, struct m1_point *pt, struct m1_point *p1, struct m1_point *p2)
{
	float t = (p2->z*view->a_top-p2->y)/((p2->z-p1->z)*view->a_top-(p2->y-p1->y));
	pt->x = p1->x*t + p2->x*(1-t);
	pt->y = p1->y*t + p2->y*(1-t);
	pt->z = p1->z*t + p2->z*(1-t);
	project_point(view, pt);
}

static int fclip_isc_left(struct view *view, struct m1_point *p)
{
	return p->x < p->z*view->a_left;
}

static void fclip_clip_left(struct view *view, struct m1_point *pt, struct m1_point *p1, struct m1_point *p2)
{
	float t = (p2->z*view->a_left-p2->x)/((p2->z-p1->z)*view->a_left-(p2->x-p1->x));
	pt->x = p1->x*t + p2->x*(1-t);
	pt->y = p1->y*t + p2->y*(1-t);
	pt->z = p1->z*t + p2->z*(1-t);
	project_point(view, pt);
}

static int fclip_isc_right(struct view *view, struct m1_point *p)
{
	return p->x > p->z*view->a_right;
}

static void fclip_clip_right(struct view *view, struct m1_point *pt, struct m1_point *p1, struct m1_point *p2)
{
	float t = (p2->z*view->a_right-p2->x)/((p2->z-p1->z)*view->a_right-(p2->x-p1->x));
	pt->x = p1->x*t + p2->x*(1-t);
	pt->y = p1->y*t + p2->y*(1-t);
	pt->z = p1->z*t + p2->z*(1-t);
	project_point(view, pt);
}

static const struct {
	int (*isclipped)(struct view *view, struct m1_point *p);
	void (*clip)(struct view *view, struct m1_point *pt, struct m1_point *p1, struct m1_point *p2);
} clipfn[4] = {
	{ fclip_isc_bottom, fclip_clip_bottom },
	{ fclip_isc_top,    fclip_clip_top },
	{ fclip_isc_left,   fclip_clip_left },
	{ fclip_isc_right,  fclip_clip_right },
};

void model1_state::fclip_push_quad_next(int level, struct quad_m1 *q,
									struct m1_point *p1, struct m1_point *p2, struct m1_point *p3, struct m1_point *p4)
{
	struct quad_m1 q2;
	q2.col = q->col;
	q2.z = q->z;
	q2.p[0] = p1;
	q2.p[1] = p2;
	q2.p[2] = p3;
	q2.p[3] = p4;

	fclip_push_quad(level+1, &q2);
}

void model1_state::fclip_push_quad(int level, struct quad_m1 *q)
{
	struct view *view = m_view;
	int i, j;
	struct m1_point *pt[4], *pi1, *pi2;
	int is_out[4], is_out2[4];
	void (*fclip_point)(struct view *view, struct m1_point *pt, struct m1_point *p1, struct m1_point *p2);

	if(level == 4) {
		LOG_TGP(("VIDEOCQ %d", level));
		for(i=0; i<4; i++)
			LOG_TGP((" (%f, %f, %f)", q->p[i]->x, q->p[i]->y, q->p[i]->z));
		LOG_TGP(("\n"));
		*m_quadpt = *q;
=======
void model1_state::view_t::recompute_frustum()
{
	a_left   = ( x1 - xc - viewx) / zoomx;
	a_right  = ( x2 - xc - viewx) / zoomx;
	a_bottom = (-y1 + yc - viewy) / zoomy;
	a_top    = (-y2 + yc - viewy) / zoomy;
}

bool model1_state::fclip_isc_bottom(view_t *view, point_t *p)
{
	return p->y > (p->z * view->a_bottom);
}

void model1_state::fclip_clip_bottom(view_t *view, point_t *pt, point_t *p1, point_t *p2)
{
	float t = (p2->z * view->a_bottom-p2->y) / ((p2->z - p1->z) * view->a_bottom - (p2->y - p1->y));
	pt->x = p1->x * t + p2->x * (1 - t);
	pt->y = p1->y * t + p2->y * (1 - t);
	pt->z = p1->z * t + p2->z * (1 - t);
	view->project_point(pt);
}

bool model1_state::fclip_isc_top(view_t *view, point_t *p)
{
	return p->y < (p->z * view->a_top);
}

void model1_state::fclip_clip_top(view_t *view, point_t *pt, point_t *p1, point_t *p2)
{
	float t = (p2->z * view->a_top - p2->y) / ((p2->z - p1->z) * view->a_top - (p2->y - p1->y));
	pt->x = p1->x * t + p2->x * (1 - t);
	pt->y = p1->y * t + p2->y * (1 - t);
	pt->z = p1->z * t + p2->z * (1 - t);
	view->project_point(pt);
}

bool model1_state::fclip_isc_left(view_t *view, point_t *p)
{
	return p->x < (p->z * view->a_left);
}

void model1_state::fclip_clip_left(view_t *view, point_t *pt, point_t *p1, point_t *p2)
{
	float t = (p2->z * view->a_left - p2->x) / ((p2->z - p1->z) * view->a_left - (p2->x - p1->x));
	pt->x = p1->x * t + p2->x * (1 - t);
	pt->y = p1->y * t + p2->y * (1 - t);
	pt->z = p1->z * t + p2->z * (1 - t);
	view->project_point(pt);
}

bool model1_state::fclip_isc_right(view_t *view, point_t *p)
{
	return p->x > (p->z * view->a_right);
}

void model1_state::fclip_clip_right(view_t *view, point_t *pt, point_t *p1, point_t *p2)
{
	float t = (p2->z * view->a_right - p2->x) / ((p2->z - p1->z) * view->a_right - (p2->x - p1->x));
	pt->x = p1->x * t + p2->x * (1 - t);
	pt->y = p1->y * t + p2->y * (1 - t);
	pt->z = p1->z * t + p2->z * (1 - t);
	view->project_point(pt);
}

void model1_state::fclip_push_quad_next(int level, quad_t& q, point_t *p1, point_t *p2, point_t *p3, point_t *p4)
{
	quad_t cquad(q.col, q.z, p1, p2, p3, p4);
	fclip_push_quad(level+1, cquad);
}

void model1_state::fclip_push_quad(int level, quad_t& q)
{
	view_t *view = m_view;

	if (level == 4)
	{
		LOG_TGP(("VIDEOCQ %d", level));
		for (int i = 0; i < 4; i++)
			LOG_TGP((" (%f, %f, %f)", q.p[i]->x, q.p[i]->y, q.p[i]->z));
		LOG_TGP(("\n"));
		*m_quadpt = q;
>>>>>>> upstream/master
		m_quadpt++;
		return;
	}

<<<<<<< HEAD
	for(i=0; i<4; i++)
		is_out[i] = clipfn[level].isclipped(view, q->p[i]);

	LOG_TGP(("VIDEOCQ %d", level));
	for(i=0; i<4; i++)
		LOG_TGP((" (%f, %f, %f, %d)", q->p[i]->x, q->p[i]->y, q->p[i]->z, is_out[i]));
	LOG_TGP(("\n"));

	// No clipping
	if(!is_out[0] && !is_out[1] && !is_out[2] && !is_out[3]) {
=======
	bool is_out[4];
	for (int i = 0; i < 4; i++)
	{
		is_out[i] = m_clipfn[level].m_isclipped(view, q.p[i]);
	}

	LOG_TGP(("VIDEOCQ %d", level));
	for (int i = 0; i < 4; i++)
		LOG_TGP((" (%f, %f, %f, %d)", q.p[i]->x, q.p[i]->y, q.p[i]->z, is_out[i]));
	LOG_TGP(("\n"));

	// No clipping
	if(!is_out[0] && !is_out[1] && !is_out[2] && !is_out[3])
	{
>>>>>>> upstream/master
		fclip_push_quad(level+1, q);
		return;
	}

<<<<<<< HEAD
	fclip_point = clipfn[level].clip;

=======
>>>>>>> upstream/master
	// Full clipping
	if(is_out[0] && is_out[1] && is_out[2] && is_out[3])
		return;

	// Find n so that point n is clipped and n-1 isn't
<<<<<<< HEAD
	for(i=0; i<4; i++)
		if(is_out[i] && !is_out[(i-1)&3])
			break;

	for(j=0; j<4; j++) {
		pt[j] = q->p[(i+j)&3];
		is_out2[j] = is_out[(i+j)&3];
	}

	// At this point, pt[0] is clipped out and pt[3] isn't.  Test for the 4 possible cases
	if(is_out2[1])
		if(is_out2[2]) {
			// pt 0,1,2 clipped out, one triangle left
			fclip_point(view, m_pointpt, pt[2], pt[3]);
			pi1 = m_pointpt++;
			fclip_point(view, m_pointpt, pt[3], pt[0]);
			pi2 = m_pointpt++;
			fclip_push_quad_next(level, q, pi1, pt[3], pi2, pi2);
		} else {
			// pt 0,1 clipped out, one quad left
			fclip_point(view, m_pointpt, pt[1], pt[2]);
			pi1 = m_pointpt++;
			fclip_point(view, m_pointpt, pt[3], pt[0]);
			pi2 = m_pointpt++;
			fclip_push_quad_next(level, q, pi1, pt[2], pt[3], pi2);
		}
	else
		if(is_out2[2]) {
			// pt 0,2 clipped out, shouldn't happen, two triangles
			fclip_point(view, m_pointpt, pt[0], pt[1]);
			pi1 = m_pointpt++;
			fclip_point(view, m_pointpt, pt[1], pt[2]);
			pi2 = m_pointpt++;
			fclip_push_quad_next(level, q, pi1, pt[1], pi2, pi2);
			fclip_point(view, m_pointpt, pt[2], pt[3]);
			pi1 = m_pointpt++;
			fclip_point(view, m_pointpt, pt[3], pt[0]);
			pi2 = m_pointpt++;
			fclip_push_quad_next(level, q, pi1, pt[3], pi2, pi2);
		} else {
			// pt 0 clipped out, one decagon left, split in quad+tri
			fclip_point(view, m_pointpt, pt[0], pt[1]);
			pi1 = m_pointpt++;
			fclip_point(view, m_pointpt, pt[3], pt[0]);
			pi2 = m_pointpt++;
			fclip_push_quad_next(level, q, pi1, pt[1], pt[2], pt[3]);
			fclip_push_quad_next(level, q, pt[3], pi2, pi1, pi1);
		}
}

static float min4f(float a, float b, float c, float d)
=======
	int i;
	for (i = 0; i < 4; i++)
		if(is_out[i] && !is_out[(i-1)&3])
			break;

	point_t* pt[4];
	bool is_out2[4];
	for (int j = 0; j < 4; j++)
	{
		pt[j] = q.p[(i + j) & 3];
		is_out2[j] = is_out[(i + j) & 3];
	}

	// At this point, pt[0] is clipped out and pt[3] isn't.  Test for the 4 possible cases
	if (is_out2[1])
	{
		if (is_out2[2])
		{
			// pt 0,1,2 clipped out, one triangle left
			m_clipfn[level].m_clip(view, m_pointpt, pt[2], pt[3]);
			point_t* pi1 = m_pointpt++;
			m_clipfn[level].m_clip(view, m_pointpt, pt[3], pt[0]);
			point_t* pi2 = m_pointpt++;
			fclip_push_quad_next(level, q, pi1, pt[3], pi2, pi2);
		}
		else
		{
			// pt 0,1 clipped out, one quad left
			m_clipfn[level].m_clip(view, m_pointpt, pt[1], pt[2]);
			point_t* pi1 = m_pointpt++;
			m_clipfn[level].m_clip(view, m_pointpt, pt[3], pt[0]);
			point_t* pi2 = m_pointpt++;
			fclip_push_quad_next(level, q, pi1, pt[2], pt[3], pi2);
		}
	}
	else
	{
		if (is_out2[2])
		{
			// pt 0,2 clipped out, shouldn't happen, two triangles
			m_clipfn[level].m_clip(view, m_pointpt, pt[0], pt[1]);
			point_t* pi1 = m_pointpt++;
			m_clipfn[level].m_clip(view, m_pointpt, pt[1], pt[2]);
			point_t* pi2 = m_pointpt++;
			fclip_push_quad_next(level, q, pi1, pt[1], pi2, pi2);
			m_clipfn[level].m_clip(view, m_pointpt, pt[2], pt[3]);
			pi1 = m_pointpt++;
			m_clipfn[level].m_clip(view, m_pointpt, pt[3], pt[0]);
			pi2 = m_pointpt++;
			fclip_push_quad_next(level, q, pi1, pt[3], pi2, pi2);
		}
		else
		{
			// pt 0 clipped out, one decagon left, split in quad+tri
			m_clipfn[level].m_clip(view, m_pointpt, pt[0], pt[1]);
			point_t* pi1 = m_pointpt++;
			m_clipfn[level].m_clip(view, m_pointpt, pt[3], pt[0]);
			point_t* pi2 = m_pointpt++;
			fclip_push_quad_next(level, q, pi1, pt[1], pt[2], pt[3]);
			fclip_push_quad_next(level, q, pt[3], pi2, pi1, pi1);
		}
	}
}

float model1_state::min4f(float a, float b, float c, float d)
>>>>>>> upstream/master
{
	float m = a;
	if(b<m)
		m = b;
	if(c<m)
		m = c;
	if(d<m)
		m = d;
	return m;
}

<<<<<<< HEAD
static float max4f(float a, float b, float c, float d)
{
	float m = a;
	if(b>m)
		m = b;
	if(c>m)
		m = c;
	if(d>m)
=======
float model1_state::max4f(float a, float b, float c, float d)
{
	float m = a;
	if (b > m)
		m = b;
	if (c > m)
		m = c;
	if (d > m)
>>>>>>> upstream/master
		m = d;
	return m;
}

#ifdef UNUSED_DEFINITION
<<<<<<< HEAD
static const UINT8 num_of_times[]={1,1,1,1,2,2,2,3};
#endif
static float compute_specular(struct vector_t *normal, struct vector_t *light,float diffuse,int lmode)
{
#if 0
	float s;
	int p=view->lightparams[lmode].p&7;
	int i;
	float sv=view->lightparams[lmode].s;

	//This is how it should be according to model2 geo program, but doesn't work fine
	s=2*(diffuse*normal->z-light->z);
	for(i=0;i<num_of_times[p];++i)
		s*=s;
	s*=sv;
	if(s<0.0)
		return 0.0;
	if(s>1.0)
		return 1.0;
	return s;

	return fabs(diffuse)*sv;

=======
static const uint8_t num_of_times[]={1,1,1,1,2,2,2,3};
#endif
float model1_state::compute_specular(glm::vec3& normal, glm::vec3& light, float diffuse, int lmode)
{
#if 0
	int p = m_view->lightparams[lmode].p & 7;
	float sv = m_view->lightparams[lmode].s;

	//This is how it should be according to model2 geo program, but doesn't work fine
	float s = 2 * (diffuse * normal.z - light.z);
	for (int i = 0; i < num_of_times[p]; i++)
	{
		s *= s;
	}
	s *= sv;
	if (s < 0.0f)
	{
		return 0.0f;
	}
	if (s > 1.0f)
	{
		return 1.0f;
	}
	return s;

	// ???
	//return fabs(diffuse)*sv;
>>>>>>> upstream/master
#endif

	return 0;
}

<<<<<<< HEAD
void model1_state::push_object(UINT32 tex_adr, UINT32 poly_adr, UINT32 size)
{
	struct view *view = m_view;
	int i;
	UINT32 flags;
	struct m1_point *old_p0, *old_p1, *p0, *p1;
	struct vector_t vn;
	int link, type;
#if 0
	int dump;
#endif
	int lightmode;
	float old_z;
	struct quad_m1 cquad;
	float *poly_data;

	if(poly_adr & 0x800000)
		poly_data=(float *) m_poly_ram;
	else
		poly_data=(float *) m_poly_rom;
=======
void model1_state::push_object(uint32_t tex_adr, uint32_t poly_adr, uint32_t size) {
#if 0
	int dump;
#endif

	float *poly_data;
	if (poly_adr & 0x800000)
		poly_data = (float *)m_poly_ram.get();
	else
		poly_data = (float *)m_poly_rom;
>>>>>>> upstream/master

	poly_adr &= 0x7fffff;
#if 0
	dump = poly_adr == 0x944ea;
	dump = 0;
#endif

#if 0
<<<<<<< HEAD
	if(poly_adr < 0x10000 || poly_adr >= 0x80000)
		return;

	if(poly_adr < 0x40000 || poly_adr >= 0x50000)
		return;

	if(poly_adr == 0x4c7db || poly_adr == 0x4cdaa || poly_adr == 0x4d3e7)
		return;

	if(poly_adr != 0x483e5)
		return;
#endif

	if(1) {
		LOG_TGP(("XVIDEO:   draw object (%x, %x, %x)\n", tex_adr, poly_adr, size));
	}

	if(!size)
		size = 0xffffffff;

	old_p0 = m_pointpt++;
	old_p1 = m_pointpt++;

	old_p0->x = poly_data[poly_adr+0];
	old_p0->y = poly_data[poly_adr+1];
	old_p0->z = poly_data[poly_adr+2];
	old_p1->x = poly_data[poly_adr+3];
	old_p1->y = poly_data[poly_adr+4];
	old_p1->z = poly_data[poly_adr+5];
	_transform_point(view, old_p0);
	_transform_point(view, old_p1);
	if(old_p0->z > 0)
		project_point(view, old_p0);
	else
		old_p0->s.x = old_p0->s.y = 0;
	if(old_p1->z > 0)
		project_point(view, old_p1);
	else
		old_p1->s.x = old_p1->s.y = 0;

	old_z = 0;

	poly_adr += 6;

	for(i=0; i<size; i++) {
#if 0
		LOG_TGP(("VIDEO:     %08x (%f, %f, %f) (%f, %f, %f) (%f, %f, %f)\n",
					*(UINT32 *)(poly_data+poly_adr) & ~(0x01800303),
					poly_data[poly_adr+1], poly_data[poly_adr+2], poly_data[poly_adr+3],
					poly_data[poly_adr+4], poly_data[poly_adr+5], poly_data[poly_adr+6],
					poly_data[poly_adr+7], poly_data[poly_adr+8], poly_data[poly_adr+9]));
#endif
		flags = *(UINT32 *)(poly_data+poly_adr);

		type = flags & 3;
		if(!type)
			break;

		if(flags & 0x00001000)
			tex_adr ++;
		lightmode=(flags>>17)&15;

		p0 = m_pointpt++;
		p1 = m_pointpt++;

		vn.x = poly_data[poly_adr+1];
		vn.y = poly_data[poly_adr+2];
		vn.z = poly_data[poly_adr+3];
		p0->x = poly_data[poly_adr+4];
		p0->y = poly_data[poly_adr+5];
		p0->z = poly_data[poly_adr+6];
		p1->x = poly_data[poly_adr+7];
		p1->y = poly_data[poly_adr+8];
		p1->z = poly_data[poly_adr+9];

		link = (flags >> 8) & 3;

		transform_vector(view, &vn);

		_transform_point(view, p0);
		_transform_point(view, p1);
		if(p0->z > 0)
			project_point(view, p0);
		else
			p0->s.x = p0->s.y = 0;
		if(p1->z > 0)
			project_point(view, p1);
		else
			p1->s.x = p1->s.y = 0;

#if 0
		if(dump)
			LOG_TGP(("VIDEO:     %08x (%f, %f, %f) (%f, %f, %f)\n",
						*(UINT32 *)(poly_data+poly_adr),
						p0->x, p0->y, p0->z,
						p1->x, p1->y, p1->z));
=======
	if (poly_adr < 0x10000 || poly_adr >= 0x80000)
		return;

	if (poly_adr < 0x40000 || poly_adr >= 0x50000)
		return;

	if (poly_adr == 0x4c7db || poly_adr == 0x4cdaa || poly_adr == 0x4d3e7)
		return;

	if (poly_adr != 0x483e5)
		return;
#endif

	if (true) {
		LOG_TGP(("XVIDEO:   draw object (%x, %x, %x)\n", tex_adr, poly_adr, size));
	}

	if (!size)
		size = 0xffffffff;

	point_t *old_p0 = m_pointpt++;
	point_t *old_p1 = m_pointpt++;

	old_p0->x = poly_data[poly_adr + 0];
	old_p0->y = poly_data[poly_adr + 1];
	old_p0->z = poly_data[poly_adr + 2];
	old_p1->x = poly_data[poly_adr + 3];
	old_p1->y = poly_data[poly_adr + 4];
	old_p1->z = poly_data[poly_adr + 5];
	m_view->transform_point(old_p0);
	m_view->transform_point(old_p1);

	if (old_p0->z > 0)
	{
		m_view->project_point(old_p0);
	}
	else
	{
		old_p0->s.x = old_p0->s.y = 0;
	}

	if (old_p1->z > 0)
	{
		m_view->project_point(old_p1);
	}
	else
	{
		old_p1->s.x = old_p1->s.y = 0;
	}

	float old_z = 0;

	poly_adr += 6;

	for (int i = 0; i < size; i++)
	{
#if 0
		LOG_TGP(("VIDEO:     %08x (%f, %f, %f) (%f, %f, %f) (%f, %f, %f)\n",
			*(uint32_t *)(poly_data + poly_adr) & ~(0x01800303),
			poly_data[poly_adr + 1], poly_data[poly_adr + 2], poly_data[poly_adr + 3],
			poly_data[poly_adr + 4], poly_data[poly_adr + 5], poly_data[poly_adr + 6],
			poly_data[poly_adr + 7], poly_data[poly_adr + 8], poly_data[poly_adr + 9]));
#endif
		uint32_t flags = *reinterpret_cast<uint32_t*>(poly_data + poly_adr);

		int type = flags & 3;
		if (!type)
			break;

		if (flags & 0x00001000)
			tex_adr++;
		int lightmode = (flags >> 17) & 15;

		point_t *p0 = m_pointpt++;
		point_t *p1 = m_pointpt++;

		glm::vec3 vn(poly_data[poly_adr + 1], poly_data[poly_adr + 2], poly_data[poly_adr + 3]);
		p0->x = poly_data[poly_adr + 4];
		p0->y = poly_data[poly_adr + 5];
		p0->z = poly_data[poly_adr + 6];
		p1->x = poly_data[poly_adr + 7];
		p1->y = poly_data[poly_adr + 8];
		p1->z = poly_data[poly_adr + 9];

		int link = (flags >> 8) & 3;

		m_view->transform_vector(vn);

		m_view->transform_point(p0);
		m_view->transform_point(p1);
		if (p0->z > 0)
		{
			m_view->project_point(p0);
		}
		else
		{
			p0->s.x = p0->s.y = 0;
		}

		if (p1->z > 0)
		{
			m_view->project_point(p1);
		}
		else
		{
			p1->s.x = p1->s.y = 0;
		}

#if 0
		if (dump)
			LOG_TGP(("VIDEO:     %08x (%f, %f, %f) (%f, %f, %f)\n",
				*(uint32_t *)(poly_data + poly_adr),
				p0->x, p0->y, p0->z,
				p1->x, p1->y, p1->z));
>>>>>>> upstream/master
#endif


#if 0
<<<<<<< HEAD
		if(1 || dump) {
			LOG_TGP(("VIDEO:     %08x (%d, %d) (%d, %d) (%d, %d) (%d, %d)\n",
						*(UINT32 *)(poly_data+poly_adr),
						old_p0->s.x, old_p0->s.y,
						old_p1->s.x, old_p1->s.y,
						p0->s.x, p0->s.y,
						p1->s.x, p1->s.y));
		}
#endif

		if(!link)
			goto next;

		if(!(flags & 0x00004000) && view_determinant(old_p1, old_p0, p0) > 0)
			goto next;

		normalize_vector(&vn);
=======
		if (true || dump) {
			LOG_TGP(("VIDEO:     %08x (%d, %d) (%d, %d) (%d, %d) (%d, %d)\n",
				*(uint32_t *)(poly_data + poly_adr),
				old_p0->s.x, old_p0->s.y,
				old_p1->s.x, old_p1->s.y,
				p0->s.x, p0->s.y,
				p1->s.x, p1->s.y));
		}
#endif

		quad_t cquad;

		if (!link)
			goto next;

		if (!(flags & 0x00004000) && view_determinant(old_p1, old_p0, p0) > 0)
			goto next;

		vn = glm::normalize(vn);
>>>>>>> upstream/master

		cquad.p[0] = old_p1;
		cquad.p[1] = old_p0;
		cquad.p[2] = p0;
		cquad.p[3] = p1;

<<<<<<< HEAD
		switch((flags >> 10) & 3) {
		case 0:
			cquad.z = old_z;
			break;
		case 1:
			cquad.z = old_z = min4f(old_p1->z, old_p0->z, p0->z, p1->z);
			break;
		case 2:
			cquad.z = old_z = max4f(old_p1->z, old_p0->z, p0->z, p1->z);
			break;
		case 3:
		default:
			cquad.z = 0.0;
			break;
=======
		switch ((flags >> 10) & 3)
		{
			case 0:
				cquad.z = old_z;
				break;
			case 1:
				cquad.z = old_z = min4f(old_p1->z, old_p0->z, p0->z, p1->z);
				break;
			case 2:
				cquad.z = old_z = max4f(old_p1->z, old_p0->z, p0->z, p1->z);
				break;
			case 3:
			default:
				cquad.z = 0.0;
				break;
>>>>>>> upstream/master
		}

		{
#if 0
<<<<<<< HEAD
			float dif=mult_vector(&vn, &view->light);
			float ln=view->lightparams[lightmode].a + view->lightparams[lightmode].d*MAX(0.0,dif);
			cquad.col = scale_color(machine().pens[0x1000|(m_tgp_ram[tex_adr-0x40000] & 0x3ff)], MIN(1.0,ln));
			cquad.col = scale_color(machine().pens[0x1000|(m_tgp_ram[tex_adr-0x40000] & 0x3ff)], MIN(1.0,ln));
#endif
			float dif=mult_vector(&vn, &view->light);
			float spec=compute_specular(&vn,&view->light,dif,lightmode);
			float ln=view->lightparams[lightmode].a + view->lightparams[lightmode].d*MAX(0.0f,dif) + spec;
			int lumval=255.0f*MIN(1.0f,ln);
			int color=m_paletteram16[0x1000|(m_tgp_ram[tex_adr-0x40000] & 0x3ff)];
			int r=(color>>0x0)&0x1f;
			int g=(color>>0x5)&0x1f;
			int b=(color>>0xA)&0x1f;
			lumval>>=2; //there must be a luma translation table somewhere
			if(lumval>0x3f) lumval=0x3f;
			else if(lumval<0) lumval=0;
			r=(m_color_xlat[(r<<8)|lumval|0x0]>>3)&0x1f;
			g=(m_color_xlat[(g<<8)|lumval|0x2000]>>3)&0x1f;
			b=(m_color_xlat[(b<<8)|lumval|0x4000]>>3)&0x1f;
			cquad.col=(pal5bit(r)<<16)|(pal5bit(g)<<8)|(pal5bit(b)<<0);
		}

		if(flags & 0x00002000)
			cquad.col |= MOIRE;

		fclip_push_quad(0, &cquad);

	next:
		poly_adr += 10;
		switch(link) {
		case 0:
		case 2:
			old_p0 = p0;
			old_p1 = p1;
			break;
		case 1:
			old_p1 = p0;
			break;
		case 3:
			old_p0 = p1;
			break;
=======
			float dif = mult_vector(&vn, &view->light);
			float ln = view->lightparams[lightmode].a + view->lightparams[lightmode].d*MAX(0.0, dif);
			cquad.col = scale_color(machine().pens[0x1000 | (m_tgp_ram[tex_adr - 0x40000] & 0x3ff)], MIN(1.0, ln));
			cquad.col = scale_color(machine().pens[0x1000 | (m_tgp_ram[tex_adr - 0x40000] & 0x3ff)], MIN(1.0, ln));
#endif

			float dif = glm::dot(vn, m_view->light);
			float spec = compute_specular(vn, m_view->light, dif, lightmode);
			float ln = m_view->lightparams[lightmode].a + m_view->lightparams[lightmode].d * std::max(0.0f, dif) + spec;
			int lumval = 255.0f * std::min(1.0f, ln);
			int color = m_paletteram16[0x1000 | (m_tgp_ram[tex_adr - 0x40000] & 0x3ff)];
			int r = (color >> 0x0) & 0x1f;
			int g = (color >> 0x5) & 0x1f;
			int b = (color >> 0xA) & 0x1f;

			lumval >>= 2; //there must be a luma translation table somewhere
			if (lumval > 0x3f)
				lumval = 0x3f;
			else if (lumval < 0)
				lumval = 0;

			r = (m_color_xlat[(r << 8) | lumval | 0x0] >> 3) & 0x1f;
			g = (m_color_xlat[(g << 8) | lumval | 0x2000] >> 3) & 0x1f;
			b = (m_color_xlat[(b << 8) | lumval | 0x4000] >> 3) & 0x1f;
			cquad.col = (pal5bit(r) << 16) | (pal5bit(g) << 8) | (pal5bit(b) << 0);
		}

		if (flags & 0x00002000)
			cquad.col |= MOIRE;

		fclip_push_quad(0, cquad);

	next:
		poly_adr += 10;
		switch (link) {
			case 0:
			case 2:
				old_p0 = p0;
				old_p1 = p1;
				break;
			case 1:
				old_p1 = p0;
				break;
			case 3:
				old_p0 = p1;
				break;
>>>>>>> upstream/master
		}
	}
}

<<<<<<< HEAD
UINT16 *model1_state::push_direct(UINT16 *list)
{
	struct view *view = m_view;
	UINT32 flags;
	UINT32 tex_adr, lum; //, v1, v2;
	struct m1_point *old_p0, *old_p1, *p0, *p1;
	int link, type;
	float z;
	struct quad_m1 cquad;

	tex_adr = readi(list);
//  v1      = readi(list+2);
//  v2      = readi(list+10);

	old_p0 = m_pointpt++;
	old_p1 = m_pointpt++;

	old_p0->x = readf(list+4);
	old_p0->y = readf(list+6);
	old_p0->z = readf(list+8);
	old_p1->x = readf(list+12);
	old_p1->y = readf(list+14);
	old_p1->z = readf(list+16);

	LOG_TGP(("VIDEOD start direct\n"));
	LOG_TGP(("VIDEOD (%f, %f, %f) (%f, %f, %f)\n",
				old_p0->x, old_p0->y, old_p0->z,
				old_p1->x, old_p1->y, old_p1->z));

	//_transform_point(view, old_p0);
	//_transform_point(view, old_p1);
	if(old_p0->z > 0)
		project_point_direct(view, old_p0);
	else
		old_p0->s.x = old_p0->s.y = 0;
	if(old_p1->z > 0)
		project_point_direct(view, old_p1);
	else
		old_p1->s.x = old_p1->s.y = 0;

	list += 18;

	for(;;) {
		flags = readi(list);

		type = flags & 3;
		if(!type)
			break;

		if(flags & 0x00001000)
			tex_adr ++;

		// list+2 is luminosity
		// list+4 is 0?
		// list+12 is z?

		p0 = m_pointpt++;
		p1 = m_pointpt++;

		lum   = readi(list+2);
//      v1    = readi(list+4);

		if(type == 2) {
			p0->x = readf(list+6);
			p0->y = readf(list+8);
			p0->z = readf(list+10);
			z = p0->z;
			LOG_TGP(("VIDEOD %08x %08x (%f, %f, %f)\n",
						flags, lum,
						p0->x, p0->y, p0->z));
			*p1 = *p0;
			list += 12;
		} else {
			p0->x = readf(list+6);
			p0->y = readf(list+8);
			p0->z = readf(list+10);
			p1->x = readf(list+14);
			p1->y = readf(list+16);
			p1->z = readf(list+18);
			z     = readf(list+12);
			LOG_TGP(("VIDEOD %08x %08x (%f, %f, %f) (%f, %f, %f)\n",
						flags, lum,
						p0->x, p0->y, p0->z,
						p1->x, p1->y, p1->z));
			list += 20;
		}

		link = (flags >> 8) & 3;

		//_transform_point(view, p0);
		//_transform_point(view, p1);
		if(p0->z > 0)
			project_point_direct(view, p0);
		if(p1->z > 0)
			project_point_direct(view, p1);

#if 1
		if(old_p0 && old_p1)
			LOG_TGP(("VIDEOD:     %08x (%d, %d) (%d, %d) (%d, %d) (%d, %d)\n",
						flags,
						old_p0->s.x, old_p0->s.y,
						old_p1->s.x, old_p1->s.y,
						p0->s.x, p0->s.y,
						p1->s.x, p1->s.y));
		else
			LOG_TGP(("VIDEOD:     %08x (%d, %d) (%d, %d)\n",
						flags,
						p0->s.x, p0->s.y,
						p1->s.x, p1->s.y));

#endif

		if(!link)
=======

int model1_state::push_direct(int list_offset) {
	uint32_t tex_adr = readi(list_offset + 2);
	//  v1      = readi(list_offset+2+2);
	//  v2      = readi(list_offset+2+10);

	point_t *old_p0 = m_pointpt++;
	point_t *old_p1 = m_pointpt++;

	old_p0->x = readf(list_offset + 2 + 4);
	old_p0->y = readf(list_offset + 2 + 6);
	old_p0->z = readf(list_offset + 2 + 8);
	old_p1->x = readf(list_offset + 2 + 12);
	old_p1->y = readf(list_offset + 2 + 14);
	old_p1->z = readf(list_offset + 2 + 16);

	LOG_TGP(("VIDEOD start direct\n"));
	LOG_TGP(("VIDEOD (%f, %f, %f) (%f, %f, %f)\n",
		old_p0->x, old_p0->y, old_p0->z,
		old_p1->x, old_p1->y, old_p1->z));

	//m_view-transform_point(old_p0);
	//m_view->transform_point(old_p1);
	if (old_p0->z > 0)
	{
		m_view->project_point_direct(old_p0);
	}
	else
	{
		old_p0->s.x = old_p0->s.y = 0;
	}

	if (old_p1->z > 0)
	{
		m_view->project_point_direct(old_p1);
	}
	else
	{
		old_p1->s.x = old_p1->s.y = 0;
	}

	list_offset += 18;

	for (;;) {
		uint32_t flags = readi(list_offset + 2);

		int type = flags & 3;
		if (!type)
			break;

		if (flags & 0x00001000)
			tex_adr++;

		// list+2+2 is luminosity
		// list+2+4 is 0?
		// list+2+12 is z?

		point_t *p0 = m_pointpt++;
		point_t *p1 = m_pointpt++;

		uint32_t lum = readi(list_offset + 2 + 2);
		//      v1    = readi(list_offset+2+4);

		float z = 0;
		if (type == 2)
		{
			p0->x = readf(list_offset + 2 + 6);
			p0->y = readf(list_offset + 2 + 8);
			p0->z = readf(list_offset + 2 + 10);
			z = p0->z;
			LOG_TGP(("VIDEOD %08x %08x (%f, %f, %f)\n",
				flags, lum,
				p0->x, p0->y, p0->z));
			*p1 = *p0;
			list_offset += 12;
		}
		else
		{
			p0->x = readf(list_offset + 2 + 6);
			p0->y = readf(list_offset + 2 + 8);
			p0->z = readf(list_offset + 2 + 10);
			p1->x = readf(list_offset + 2 + 14);
			p1->y = readf(list_offset + 2 + 16);
			p1->z = readf(list_offset + 2 + 18);
			z = readf(list_offset + 2 + 12);
			LOG_TGP(("VIDEOD %08x %08x (%f, %f, %f) (%f, %f, %f)\n",
				flags, lum,
				p0->x, p0->y, p0->z,
				p1->x, p1->y, p1->z));
			list_offset += 20;
		}

		int link = (flags >> 8) & 3;

		//m_view->transform_point(p0);
		//m_view->transform_point(p1);
		if (p0->z > 0)
		{
			m_view->project_point_direct(p0);
		}
		if (p1->z > 0)
		{
			m_view->project_point_direct(p1);
		}

#if 1
		if (old_p0 && old_p1)
			LOG_TGP(("VIDEOD:     %08x (%d, %d) (%d, %d) (%d, %d) (%d, %d)\n",
				flags,
				old_p0->s.x, old_p0->s.y,
				old_p1->s.x, old_p1->s.y,
				p0->s.x, p0->s.y,
				p1->s.x, p1->s.y));
		else
			LOG_TGP(("VIDEOD:     %08x (%d, %d) (%d, %d)\n",
				flags,
				p0->s.x, p0->s.y,
				p1->s.x, p1->s.y));

#endif

		quad_t cquad;
		if (!link)
>>>>>>> upstream/master
			goto next;

		cquad.p[0] = old_p1;
		cquad.p[1] = old_p0;
		cquad.p[2] = p0;
		cquad.p[3] = p1;
<<<<<<< HEAD
		cquad.z    = z;
		{
			int lumval=((float) (lum>>24)) * 2.0f;
			int color=m_paletteram16[0x1000|(m_tgp_ram[tex_adr-0x40000] & 0x3ff)];
			int r=(color>>0x0)&0x1f;
			int g=(color>>0x5)&0x1f;
			int b=(color>>0xA)&0x1f;
			lumval>>=2; //there must be a luma translation table somewhere
			if(lumval>0x3f) lumval=0x3f;
			else if(lumval<0) lumval=0;
			r=(m_color_xlat[(r<<8)|lumval|0x0]>>3)&0x1f;
			g=(m_color_xlat[(g<<8)|lumval|0x2000]>>3)&0x1f;
			b=(m_color_xlat[(b<<8)|lumval|0x4000]>>3)&0x1f;
			cquad.col=(pal5bit(r)<<16)|(pal5bit(g)<<8)|(pal5bit(b)<<0);
		}
		//cquad.col  = scale_color(machine().pens[0x1000|(m_tgp_ram[tex_adr-0x40000] & 0x3ff)],((float) (lum>>24)) / 128.0);
		if(flags & 0x00002000)
			cquad.col |= MOIRE;

		fclip_push_quad(0, &cquad);

	next:
		switch(link) {
=======
		cquad.z = z;
		{
			int lumval = ((float)(lum >> 24)) * 2.0f;
			int color = m_paletteram16[0x1000 | (m_tgp_ram[tex_adr - 0x40000] & 0x3ff)];
			int r = (color >> 0x0) & 0x1f;
			int g = (color >> 0x5) & 0x1f;
			int b = (color >> 0xA) & 0x1f;
			lumval >>= 2; //there must be a luma translation table somewhere
			if (lumval > 0x3f) lumval = 0x3f;
			else if (lumval < 0) lumval = 0;
			r = (m_color_xlat[(r << 8) | lumval | 0x0] >> 3) & 0x1f;
			g = (m_color_xlat[(g << 8) | lumval | 0x2000] >> 3) & 0x1f;
			b = (m_color_xlat[(b << 8) | lumval | 0x4000] >> 3) & 0x1f;
			cquad.col = (pal5bit(r) << 16) | (pal5bit(g) << 8) | (pal5bit(b) << 0);
		}
		//cquad.col  = scale_color(machine().pens[0x1000|(m_tgp_ram[tex_adr-0x40000] & 0x3ff)],((float) (lum>>24)) / 128.0);
		if (flags & 0x00002000)
			cquad.col |= MOIRE;

		fclip_push_quad(0, cquad);

	next:
		switch (link) {
>>>>>>> upstream/master
		case 0:
		case 2:
			old_p0 = p0;
			old_p1 = p1;
			break;
		case 1:
			old_p1 = p0;
			break;
		case 3:
			old_p0 = p1;
			break;
		}
	}
<<<<<<< HEAD
	return list+2;
}

static UINT16 *skip_direct(UINT16 *list)
{
	UINT32 flags;
	int type;

	list += 18;

	for(;;) {
		flags = readi(list);

		type = flags & 3;
		if(!type)
			break;

		if(type == 2)
			list += 12;
		else
			list += 20;
	}
	return list+2;
=======
	list_offset += 4;
	return list_offset;
}

int model1_state::skip_direct(int list_offset) const
{
	list_offset += 18;

	while (true) {
		uint32_t flags = readi(list_offset + 2);

		int type = flags & 3;
		if (!type)
			break;

		if (type == 2)
			list_offset += 12;
		else
			list_offset += 20;
	}
	list_offset += 4;
	return list_offset;
>>>>>>> upstream/master
}

void model1_state::draw_objects(bitmap_rgb32 &bitmap, const rectangle &cliprect)
{
<<<<<<< HEAD
	if(m_quadpt != m_quaddb) {
=======
	if (m_quadpt != m_quaddb)
	{
>>>>>>> upstream/master
		LOG_TGP(("VIDEO: sort&draw\n"));
		sort_quads();
		draw_quads(bitmap, cliprect);
	}

	m_quadpt = m_quaddb;
	m_pointpt = m_pointdb;
}

<<<<<<< HEAD
UINT16 *model1_state::draw_direct(bitmap_rgb32 &bitmap, const rectangle &cliprect, UINT16 *list)
{
	UINT16 *res;

	LOG_TGP(("VIDEO:   draw direct %x\n", readi(list)));

	draw_objects(bitmap, cliprect);
	res = push_direct(list);
=======

int model1_state::draw_direct(bitmap_rgb32 &bitmap, const rectangle &cliprect, int list_offset)
{
	LOG_TGP(("VIDEO:   draw direct %x\n", readi(list_offset + 2)));

	draw_objects(bitmap, cliprect);

	list_offset = push_direct(list_offset);

>>>>>>> upstream/master
	unsort_quads();
	draw_quads(bitmap, cliprect);

	m_quadpt = m_quaddb;
	m_pointpt = m_pointdb;
<<<<<<< HEAD
	return res;
}

UINT16 *model1_state::get_list()
{
	if(!(m_listctl[0] & 4))
		m_listctl[0] = (m_listctl[0] & ~0x40) | (m_listctl[0] & 8 ? 0x40 : 0);
	return m_listctl[0] & 0x40 ? m_display_list1 : m_display_list0;
=======

	return list_offset;
}


void model1_state::set_current_render_list()
{
	if(!(m_listctl[0] & 4))
		m_listctl[0] = (m_listctl[0] & ~0x40) | (m_listctl[0] & 8 ? 0x40 : 0);
	m_display_list_current = m_listctl[0] & 0x40 ? m_display_list1 : m_display_list0;
>>>>>>> upstream/master
}

int model1_state::get_list_number()
{
	if(!(m_listctl[0] & 4))
		m_listctl[0] = (m_listctl[0] & ~0x40) | (m_listctl[0] & 8 ? 0x40 : 0);
	return m_listctl[0] & 0x40 ? 0 : 1;
}

void model1_state::end_frame()
{
	if((m_listctl[0] & 4) && (m_screen->frame_number() & 1))
		m_listctl[0] ^= 0x40;
}

READ16_MEMBER(model1_state::model1_listctl_r)
{
	if(!offset)
		return m_listctl[0] | 0x30;
	else
		return m_listctl[1];
}

WRITE16_MEMBER(model1_state::model1_listctl_w)
{
<<<<<<< HEAD
	COMBINE_DATA(m_listctl+offset);
	LOG_TGP(("VIDEO: control=%08x\n", (m_listctl[1]<<16)|m_listctl[0]));
}

void model1_state::tgp_render(bitmap_rgb32 &bitmap, const rectangle &cliprect)
{
	struct view *view = m_view;
	m_render_done = 1;
	if((m_listctl[1] & 0x1f) == 0x1f) {
		UINT16 *list = get_list();
		int zz = 0;
		LOG_TGP(("VIDEO: render list %d\n", get_list_number()));

		memset(view->trans_mat, 0, sizeof(view->trans_mat));
		view->trans_mat[0] = 1.0;
		view->trans_mat[4] = 1.0;
		view->trans_mat[8] = 1.0;

		for(;;) {
			int type = (list[1]<<16)|list[0];
			m_glist=list;
			switch(type & 15) {
			case 0:
				list += 2;
				break;
			case 1:
=======
	COMBINE_DATA(m_listctl + offset);
	LOG_TGP(("VIDEO: control=%08x\n", (m_listctl[1] << 16) | m_listctl[0]));
}

void model1_state::view_t::init_translation_matrix()
{
	memset(translation, 0, sizeof(translation));
	translation[0] = 1.0;
	translation[4] = 1.0;
	translation[8] = 1.0;
}

void model1_state::view_t::set_viewport(float xcenter, float ycenter, float xl, float xr, float yb, float yt)
{
	xc = xcenter;
	yc = ycenter;
	x1 = xl;
	x2 = xr;
	y1 = yb;
	y2 = yt;

	recompute_frustum();
}

void model1_state::view_t::set_lightparam(int index, float diffuse, float ambient, float specular, int power)
{
	lightparams[index].d = diffuse;
	lightparams[index].a = ambient;
	lightparams[index].s = specular;
	lightparams[index].p = power;
}

void model1_state::view_t::set_zoom(float x, float y)
{
	zoomx = x;
	zoomy = y;

	recompute_frustum();
}

void model1_state::view_t::set_light_direction(float x, float y, float z)
{
	light = glm::normalize(glm::vec3(x, y, z));
}

void model1_state::view_t::set_translation_matrix(float* mat)
{
	for (int i = 0; i < 12; i++)
	{
		translation[i] = mat[i];
	}
}

void model1_state::view_t::set_view_translation(float x, float y)
{
	viewx = x;
	viewy = y;

	recompute_frustum();
}



void model1_state::tgp_render(bitmap_rgb32 &bitmap, const rectangle &cliprect)
{
	m_render_done = 1;
	if ((m_listctl[1] & 0x1f) == 0x1f)
	{
		set_current_render_list();
		int zz = 0;
		LOG_TGP(("VIDEO: render list %d\n", get_list_number()));

		m_view->init_translation_matrix();

		int list_offset = 0;
		for (;;) {
			int type = readi(list_offset + 0);

			switch (type)
			{
			case 0:
				list_offset += 2;
				break;
			case 1:
			case 0x41:
>>>>>>> upstream/master
				// 1 = plane 1
				// 2 = ??  draw object (413d3, 17c4c, e)
				// 3 = plane 2
				// 4 = ??  draw object (408a8, a479, 9)
				// 5 = decor
				// 6 = ??  draw object (57bd4, 387460, 2ad)

<<<<<<< HEAD
				if(1 || zz >= 666)
					push_object(readi(list+2), readi(list+4), readi(list+6));
				list += 8;
				break;
			case 2:
				list = draw_direct(bitmap, cliprect, list+2);
				break;
			case 3:
				LOG_TGP(("VIDEO:   viewport (%d, %d, %d, %d, %d, %d, %d)\n",
							readi(list+2),
							readi16(list+4), readi16(list+6), readi16(list+8),
							readi16(list+10), readi16(list+12), readi16(list+14)));

				draw_objects(bitmap, cliprect);

				view->xc = readi16(list+4);
				view->yc = 383-(readi16(list+6)-39);
				view->x1 = readi16(list+8);
				view->y2 = 383-(readi16(list+10)-39);
				view->x2 = readi16(list+12);
				view->y1 = 383-(readi16(list+14)-39);

				recompute_frustrum(view);

				list += 16;
				break;
			case 4: {
				int adr = readi(list+2);
				int len = readi(list+4)+1;
				int i;
				LOG_TGP(("ZVIDEO:   color write, adr=%x, len=%x\n", adr, len));
				for(i=0; i<len; i++)
					m_tgp_ram[adr-0x40000+i] = list[6+2*i];
				list += 6+len*2;
				break;
			}
			case 5:
				{
					int adr = readi(list+2);
					int len = readi(list+4);
					int i;
					for(i=0;i<len;++i)
					{
						m_poly_ram[adr-0x800000+i]=readi(list+2*i+6);
					}
					list+=6+len*2;
				}
				break;
			case 6: {
				int adr = readi(list+2);
				int len = readi(list+4);
				int i;
				LOG_TGP(("VIDEO:   upload data, adr=%x, len=%x\n", adr, len));
				for(i=0;i<len;++i)
				{
					int v=readi(list+6+i*2);
					view->lightparams[i+adr].d=((float) (v&0xff))/255.0f;
					view->lightparams[i+adr].a=((float) ((v>>8)&0xff))/255.0f;
					view->lightparams[i+adr].s=((float) ((v>>16)&0xff))/255.0f;
					view->lightparams[i+adr].p=(v>>24)&0xff;
				}
				list += 6+len*2;
				break;
			}
			case 7:
				LOG_TGP(("VIDEO:   code 7 (%d)\n", readi(list+2)));
				zz++;
				list += 4;
				break;
			case 8:
				LOG_TGP(("VIDEO:   select mode %08x\n", readi(list+2)));
				list += 4;
				break;
			case 9:
				LOG_TGP(("VIDEO:   zoom (%f, %f)\n", readf(list+2), readf(list+4)));
				view->zoomx = readf(list+2)*4;
				view->zoomy = readf(list+4)*4;

				recompute_frustrum(view);

				list += 6;
				break;
			case 0xa:
				LOG_TGP(("VIDEO:   light vector (%f, %f, %f)\n", readf(list+2), readf(list+4), readf(list+6)));
				view->light.x = readf(list+2);
				view->light.y = readf(list+4);
				view->light.z = readf(list+6);
				normalize_vector(&view->light);
				list += 8;
				break;
			case 0xb: {
				int i;
				LOG_TGP(("VIDEO:   matrix (%f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f)\n",
							readf(list+2), readf(list+4), readf(list+6),
							readf(list+8), readf(list+10), readf(list+12),
							readf(list+14), readf(list+16), readf(list+18),
							readf(list+20), readf(list+22), readf(list+24)));
				for(i=0; i<12; i++)
					view->trans_mat[i] = readf(list+2+2*i);
				list += 26;
				break;
			}
			case 0xc:
				LOG_TGP(("VIDEO:   trans (%f, %f)\n", readf(list+2), readf(list+4)));
				view->transx = readf(list+2);
				view->transy = readf(list+4);

				recompute_frustrum(view);

				list += 6;
				break;
			case 0xf:
			//case -1:
=======
				if (true || zz >= 666)
					push_object(readi(list_offset + 2), readi(list_offset + 4), readi(list_offset + 6));
				list_offset += 8;
				break;
			case 2:
			{
				list_offset = draw_direct(bitmap, cliprect, list_offset);
				break;
			}
			case 3:
			{
				LOG_TGP(("VIDEO:   viewport (%d, %d, %d, %d, %d, %d, %d)\n",
					readi(list_offset + 2),
					readi16(list_offset + 4), readi16(list_offset + 6), readi16(list_offset + 8),
					readi16(list_offset + 10), readi16(list_offset + 12), readi16(list_offset + 14)));

				draw_objects(bitmap, cliprect);

				float xc = readi16(list_offset + 4);
				float yc = 383 - (readi16(list_offset + 6) - 39);
				float x1 = readi16(list_offset + 8);
				float y2 = 383 - (readi16(list_offset + 10) - 39);
				float x2 = readi16(list_offset + 12);
				float y1 = 383 - (readi16(list_offset + 14) - 39);

				m_view->set_viewport(xc, yc, x1, x2, y1, y2);

				list_offset += 16;
				break;
			}
			case 4:
			{
				int adr = readi(list_offset + 2);
				int len = readi(list_offset + 4) + 1;
				LOG_TGP(("ZVIDEO:   color write, adr=%x, len=%x\n", adr, len));
				for (int i = 0; i < len; i++)
				{
					m_tgp_ram[adr - 0x40000 + i] = readi16(list_offset + 6 + 2 * i);
				}
				list_offset += 6 + len * 2;
				break;
			}
			case 5:
			{
				int adr = readi(list_offset + 2);
				int len = readi(list_offset + 4);
				for (int i = 0; i < len; i++)
				{
					m_poly_ram[adr - 0x800000 + i] = readi(list_offset + 2 * i + 6);
				}
				list_offset += 6 + len * 2;
				break;
			}
			case 6:
			{
				int adr = readi(list_offset + 2);
				int len = readi(list_offset + 4);
				LOG_TGP(("VIDEO:   upload data, adr=%x, len=%x\n", adr, len));
				for (int i = 0; i < len; i++)
				{
					int v = readi(list_offset + 6 + i * 2);
					float diffuse = (float(v & 0xff)) / 255.0f;
					float ambient = (float((v >> 8) & 0xff)) / 255.0f;
					float specular = (float((v >> 16) & 0xff)) / 255.0f;
					int power = (v >> 24) & 0xff;
					m_view->set_lightparam(i + adr, diffuse, ambient, specular, power);
				}
				list_offset += 6 + len * 2;
				break;
			}
			case 7:
				LOG_TGP(("VIDEO:   code 7 (%d)\n", readi(list_offset + 2)));
				zz++;
				list_offset += 4;
				break;
			case 8:
				LOG_TGP(("VIDEO:   select mode %08x\n", readi(list_offset + 2)));
				list_offset += 4;
				break;
			case 9:
				LOG_TGP(("VIDEO:   zoom (%f, %f)\n", readf(list_offset + 2), readf(list_offset + 4)));
				m_view->set_zoom(readf(list_offset + 2) * 4, readf(list_offset + 4) * 4);
				list_offset += 6;
				break;
			case 0xa:
				LOG_TGP(("VIDEO:   light vector (%f, %f, %f)\n", readf(list_offset + 2), readf(list_offset + 4), readf(list_offset + 6)));
				m_view->set_light_direction(readf(list_offset + 2), readf(list_offset + 4), readf(list_offset + 6));
				list_offset += 8;
				break;
			case 0xb:
			{
				LOG_TGP(("VIDEO:   matrix (%f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f)\n",
					readf(list_offset + 2), readf(list_offset + 4), readf(list_offset + 6),
					readf(list_offset + 8), readf(list_offset + 10), readf(list_offset + 12),
					readf(list_offset + 14), readf(list_offset + 16), readf(list_offset + 18),
					readf(list_offset + 20), readf(list_offset + 22), readf(list_offset + 24)));
				float mat[12];
				for (int i = 0; i < 12; i++)
				{
					mat[i] = readf(list_offset + 2 + 2 * i);
				}
				m_view->set_translation_matrix(mat);
				list_offset += 26;
				break;
			}
			case 0xc:
				LOG_TGP(("VIDEO:   trans (%f, %f)\n", readf(list_offset + 2), readf(list_offset + 4)));
				m_view->set_view_translation(readf(list_offset + 2), readf(list_offset + 4));
				list_offset += 6;
				break;
			case 0xf:
				//case -1:
>>>>>>> upstream/master
				goto end;
			default:
				LOG_TGP(("VIDEO:   unknown type %d\n", type));
				goto end;
			}
		}
	end:
		draw_objects(bitmap, cliprect);
	}
}

<<<<<<< HEAD
void model1_state::tgp_scan()
{
	struct view *view = m_view;
#if 0
	if (machine().input().code_pressed_once(KEYCODE_F))
		{
		FILE *fp;
		fp=fopen("tgp-ram.bin", "w+b");
		if (fp)
				{
			fwrite(m_tgp_ram, (0x100000-0x40000)*2, 1, fp);
			fclose(fp);
				}
		exit(0);
		}
#endif
	if(!m_render_done && (m_listctl[1] & 0x1f) == 0x1f) {
		UINT16 *list = get_list();
		// Skip everything but the data uploads
		LOG_TGP(("VIDEO: scan list %d\n", get_list_number()));
		for(;;) {
			int type = (list[1]<<16)|list[0];
			switch(type) {
			case 0:
				list += 2;
				break;
			case 1:
				list += 8;
				break;
			case 2:
				list = skip_direct(list+2);
				break;
			case 3:
				list += 16;
				break;
			case 4: {
				int adr = readi(list+2);
				int len = readi(list+4)+1;
				int i;
				LOG_TGP(("ZVIDEO:   scan color write, adr=%x, len=%x\n", adr, len));
				for(i=0; i<len; i++)
					m_tgp_ram[adr-0x40000+i] = list[6+2*i];
				list += 6+len*2;
				break;
			}
			case 5:
				{
					int adr = readi(list+2);
					int len = readi(list+4);
					int i;
					for(i=0;i<len;++i)
					{
						m_poly_ram[adr-0x800000+i]=readi(list+2*i+6);
					}
					list+=6+len*2;
				}
				break;
			case 6: {
				int adr = readi(list+2);
				int len = readi(list+4);
				int i;
				//LOG_TGP(("VIDEO:   upload data, adr=%x, len=%x\n", adr, len));
				for(i=0;i<len;++i)
				{
					int v=readi(list+6+i*2);
					view->lightparams[i+adr].d=((float) (v&0xff))/255.0f;
					view->lightparams[i+adr].a=((float) ((v>>8)&0xff))/255.0f;
					view->lightparams[i+adr].s=((float) ((v>>16)&0xff))/255.0f;
					view->lightparams[i+adr].p=(v>>24)&0xff;
					//LOG_TGP(("         %02X\n",v));
				}
				list += 6+len*2;
				break;
			}
			case 7:
				list += 4;
				break;
			case 8:
				list += 4;
				break;
			case 9:
				list += 6;
				break;
			case 0xa:
				list += 8;
				break;
			case 0xb:
				list += 26;
				break;
			case 0xc:
				list += 6;
				break;
			case 0xf:
			case -1:
				goto end;
			default:
				LOG_TGP(("VIDEO:   unknown type %d\n", type));
				goto end;
=======

void model1_state::tgp_scan()
{
#if 0
	if (machine().input().code_pressed_once(KEYCODE_F)) {
		FILE *fp;
		fp = fopen("tgp-ram.bin", "w+b");
		if (fp) {
			fwrite(m_tgp_ram, (0x100000 - 0x40000) * 2, 1, fp);
			fclose(fp);
		}
		exit(0);
	}
#endif
	if (!m_render_done && (m_listctl[1] & 0x1f) == 0x1f)
	{
		set_current_render_list();
		// Skip everything but the data uploads
		LOG_TGP(("VIDEO: scan list %d\n", get_list_number()));

		int list_offset = 0;
		for (;;)
		{
			int type = readi(list_offset + 0);
			switch (type) {
				case 0:
					list_offset += 2;
					break;
				case 1:
				case 0x41:
					list_offset += 8;
					break;
				case 2:
					list_offset = skip_direct(list_offset);

					break;
				case 3:
					list_offset += 16;
					break;
				case 4:
				{
					int adr = readi(list_offset + 2);
					int len = readi(list_offset + 4) + 1;
					LOG_TGP(("ZVIDEO:   scan color write, adr=%x, len=%x\n", adr, len));
					for (int i = 0; i<len; i++)
					{
						m_tgp_ram[adr - 0x40000 + i] = readi16(list_offset + 6 + 2 * i);
					}
					list_offset += 6 + len * 2;
					break;
				}
				case 5:
				{
					int adr = readi(list_offset + 2);
					int len = readi(list_offset + 4);
					for (int i = 0; i < len; i++)
					{
						m_poly_ram[adr - 0x800000 + i] = readi(list_offset + 2 * i + 6);
					}
					list_offset += 6 + len * 2;
					break;
				}
				case 6:
				{
					int adr = readi(list_offset + 2);
					int len = readi(list_offset + 4);
					//LOG_TGP(("VIDEO:   upload data, adr=%x, len=%x\n", adr, len));
					for (int i = 0; i<len; i++)
					{
						int v = readi(list_offset + 6 + i * 2);
						m_view->lightparams[i + adr].d = (float(v & 0xff)) / 255.0f;
						m_view->lightparams[i + adr].a = (float((v >> 8) & 0xff)) / 255.0f;
						m_view->lightparams[i + adr].s = (float((v >> 16) & 0xff)) / 255.0f;
						m_view->lightparams[i + adr].p = (v >> 24) & 0xff;
						//LOG_TGP(("         %02X\n",v));
					}
					list_offset += 6 + len * 2;
					break;
				}
				case 7:
					list_offset += 4;
					break;
				case 8:
					list_offset += 4;
					break;
				case 9:
					list_offset += 6;
					break;
				case 0xa:
					list_offset += 8;
					break;
				case 0xb:
					list_offset += 26;
					break;
				case 0xc:
					list_offset += 6;
					break;
				case 0xf:
				case -1:
					goto end;
				default:
					LOG_TGP(("VIDEO:   unknown type %d\n", type));
					goto end;
>>>>>>> upstream/master
			}
		}
	end:
		;
	}
	m_render_done = 0;
}

<<<<<<< HEAD
VIDEO_START_MEMBER(model1_state,model1)
{
	m_view = auto_alloc_clear(machine(), struct view);

	m_poly_rom = (UINT32 *)memregion("user1")->base();
	m_poly_ram = auto_alloc_array_clear(machine(), UINT32, 0x400000);
	m_tgp_ram = auto_alloc_array_clear(machine(), UINT16, 0x100000-0x40000);
	m_pointdb = auto_alloc_array_clear(machine(), struct m1_point, 1000000*2);
	m_quaddb  = auto_alloc_array_clear(machine(), struct quad_m1, 1000000);
	m_quadind = auto_alloc_array_clear(machine(), struct quad_m1 *, 1000000);
=======
VIDEO_START_MEMBER(model1_state, model1)
{
	m_view = auto_alloc_clear(machine(), <model1_state::view_t>());

	m_poly_rom = (uint32_t *)memregion("user1")->base();
	m_poly_ram = make_unique_clear<uint32_t[]>(0x400000);
	m_tgp_ram = make_unique_clear<uint16_t[]>(0x100000-0x40000);
	m_pointdb = auto_alloc_array_clear(machine(), model1_state::point_t, 1000000*2);
	m_quaddb  = auto_alloc_array_clear(machine(), model1_state::quad_t, 1000000);
	m_quadind = auto_alloc_array_clear(machine(), model1_state::quad_t *, 1000000);
>>>>>>> upstream/master

	m_pointpt = m_pointdb;
	m_quadpt = m_quaddb;
	m_listctl[0] = m_listctl[1] = 0;

<<<<<<< HEAD
	save_pointer(NAME(m_tgp_ram), 0x100000-0x40000);
	save_pointer(NAME(m_poly_ram), 0x40000);
	save_item(NAME(m_listctl));
}

UINT32 model1_state::screen_update_model1(screen_device &screen, bitmap_rgb32 &bitmap, const rectangle &cliprect)
{
	struct view *view = m_view;
#if 0
	{
		int mod = 0;
		double delta;
		delta = 1;

		if(machine().input().code_pressed(KEYCODE_F)) {
			mod = 1;
			view->vxx -= delta;
		}
		if(machine().input().code_pressed(KEYCODE_G)) {
			mod = 1;
			view->vxx += delta;
		}
		if(machine().input().code_pressed(KEYCODE_H)) {
			mod = 1;
			view->vyy -= delta;
		}
		if(machine().input().code_pressed(KEYCODE_J)) {
			mod = 1;
			view->vyy += delta;
		}
		if(machine().input().code_pressed(KEYCODE_K)) {
			mod = 1;
			view->vzz -= delta;
		}
		if(machine().input().code_pressed(KEYCODE_L)) {
			mod = 1;
			view->vzz += delta;
		}
		if(machine().input().code_pressed(KEYCODE_U)) {
			mod = 1;
			view->ayy -= 0.05;
		}
		if(machine().input().code_pressed(KEYCODE_I)) {
			mod = 1;
			view->ayy += 0.05;
		}
		if(mod)
			popmessage("%g,%g,%g:%g", view->vxx, view->vyy, view->vzz, view->ayy);
=======
	m_clipfn[0].m_isclipped = &model1_state::fclip_isc_bottom;
	m_clipfn[0].m_clip = &model1_state::fclip_clip_bottom;
	m_clipfn[1].m_isclipped = &model1_state::fclip_isc_top;
	m_clipfn[1].m_clip = &model1_state::fclip_clip_top;
	m_clipfn[2].m_isclipped = &model1_state::fclip_isc_left;
	m_clipfn[2].m_clip = &model1_state::fclip_clip_left;
	m_clipfn[3].m_isclipped = &model1_state::fclip_isc_right;
	m_clipfn[3].m_clip = &model1_state::fclip_clip_right;

	save_pointer(NAME(m_tgp_ram.get()), 0x100000-0x40000);
	save_pointer(NAME(m_poly_ram.get()), 0x40000);
	save_item(NAME(m_listctl));
}

uint32_t model1_state::screen_update_model1(screen_device &screen, bitmap_rgb32 &bitmap, const rectangle &cliprect)
{
	model1_state::view_t *view = m_view;
#if 0
	{
		bool mod = false;
		double delta = 1.0;

		if(machine().input().code_pressed(KEYCODE_F))
		{
			mod = true;
			view->vxx -= delta;
		}
		if(machine().input().code_pressed(KEYCODE_G))
		{
			mod = true;
			view->vxx += delta;
		}
		if(machine().input().code_pressed(KEYCODE_H))
		{
			mod = true;
			view->vyy -= delta;
		}
		if(machine().input().code_pressed(KEYCODE_J))
		{
			mod = true;
			view->vyy += delta;
		}
		if(machine().input().code_pressed(KEYCODE_K))
		{
			mod = true;
			view->vzz -= delta;
		}
		if(machine().input().code_pressed(KEYCODE_L))
		{
			mod = true;
			view->vzz += delta;
		}
		if(machine().input().code_pressed(KEYCODE_U))
		{
			mod = true;
			view->ayy -= 0.05;
		}
		if(machine().input().code_pressed(KEYCODE_I))
		{
			mod = true;
			view->ayy += 0.05;
		}
		if(mod)
		{
			popmessage("%g,%g,%g:%g", view->vxx, view->vyy, view->vzz, view->ayy);
		}
>>>>>>> upstream/master
	}
#endif

	view->ayyc = cos(view->ayy);
	view->ayys = sin(view->ayy);

	screen.priority().fill(0);
	bitmap.fill(m_palette->pen(0), cliprect);

<<<<<<< HEAD
	segas24_tile *tile = machine().device<segas24_tile>("tile");
	tile->draw(screen, bitmap, cliprect, 6, 0, 0);
	tile->draw(screen, bitmap, cliprect, 4, 0, 0);
	tile->draw(screen, bitmap, cliprect, 2, 0, 0);
	tile->draw(screen, bitmap, cliprect, 0, 0, 0);

	tgp_render(bitmap, cliprect);

	tile->draw(screen, bitmap, cliprect, 7, 0, 0);
	tile->draw(screen, bitmap, cliprect, 5, 0, 0);
	tile->draw(screen, bitmap, cliprect, 3, 0, 0);
	tile->draw(screen, bitmap, cliprect, 1, 0, 0);
=======
	m_tiles->draw(screen, bitmap, cliprect, 6, 0, 0);
	m_tiles->draw(screen, bitmap, cliprect, 4, 0, 0);
	m_tiles->draw(screen, bitmap, cliprect, 2, 0, 0);
	m_tiles->draw(screen, bitmap, cliprect, 0, 0, 0);

	tgp_render(bitmap, cliprect);

	m_tiles->draw(screen, bitmap, cliprect, 7, 0, 0);
	m_tiles->draw(screen, bitmap, cliprect, 5, 0, 0);
	m_tiles->draw(screen, bitmap, cliprect, 3, 0, 0);
	m_tiles->draw(screen, bitmap, cliprect, 1, 0, 0);
>>>>>>> upstream/master

	return 0;
}

<<<<<<< HEAD
void model1_state::screen_eof_model1(screen_device &screen, bool state)
=======
WRITE_LINE_MEMBER(model1_state::screen_vblank_model1)
>>>>>>> upstream/master
{
	// on rising edge
	if (state)
	{
		tgp_scan();
		end_frame();
		LOG_TGP(("TGP: vsync\n"));
	}
}
