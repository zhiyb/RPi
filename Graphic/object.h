#ifndef __OBJECT_H
#define __OBJECT_H

#include <inttypes.h>

class object
{
	friend class axis;

public:
	inline object(class axis *parent = 0);
	virtual inline void show(void);

protected:
	static inline void showPoint(const class point& p, const uint32_t c);
	static inline void showLine(const class point& p1, const class point& p2, const uint32_t c);
	static inline void showDotLine(const class point& p1, const class point& p2, const uint32_t c);
	static inline class point convPoint(const class point& p = point(), const class angle& a = angle());
	static inline class point convPoint(const class point& p = point(), const class axis *from = 0, const class axis *to = 0);

	class axis *parent;
};

#include <iostream>
#include <stdlib.h>
#include <math.h>
#include "axis.h"

inline object::object(class axis *parent)
{
	if (parent == 0)
		parent = scrAxis;
	this->parent = parent;
	parent->insert(this);
}

inline void object::show(void)
{
	//std::cout << "object->show()" << std::endl;
}

inline void object::showPoint(const class point& p, const uint32_t c)
{
	int x = p.x() + 0.5, y = p.y() + 0.5, z = p.z() + 0.5;
	if (x >= SCRW || y >= SCRH || x < 0 || y < 0)
		return;
	if (z > 0 || (scrBuff[x][y].deep <= 0 && scrBuff[x][y].deep > z))
		return;
	scrBuff[x][y].deep = z;
	scrBuff[x][y].colour = c;
}

inline void object::showLine(const class point& p1, const class point& p2, const uint32_t c)
{
#if 0
	float dz = p2.z() - p1.z();

	// Bresenham's line algorithm (http://en.wikipedia.org/wiki/Bresenham's_line_algorithm)
	int x0 = p1.x() + 0.5, x1 = p2.x() + 0.5, y0 = p1.y() + 0.5, y1 = p2.y() + 0.5;
	int dx = abs(x1 - x0), dy = abs(y1 - y0);
	int sx = x0 < x1 ? 1 : -1, sy = y0 < y1 ? 1 : -1, err = dx - dy;

	while (true) {
		showPoint(point(x0, y0, p1.z() + dz * abs(x1 - x0) / dx), c);
		if (x0 == x1 && y0 == y1)
			break;
		int e2 = 2 * err;
		if (e2 > -dy) {
			err = err - dy;
			x0 = x0 + sx;
		}
		if (x0 == x1 && y0 == y1) {
			showPoint(point(x0, y0, p1.z() + dz * abs(x1 - x0) / dx), c);
			break;
		}
		if (e2 < dx) {
			err = err + dx;
			y0 = y0 + sy;
		}
	}
#else
	float dx = p2.x() - p1.x(), dy = p2.y() - p1.y(), dz = p2.z() - p1.z();
	float dmax = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
	for (float i = 0; i < dmax; i += 0.75)
		showPoint(point(p1.x() + dx * i / dmax, p1.y() + dy * i / dmax, p1.z() + dz * i / dmax), c);
	showPoint(p2, c);
#endif
}

inline void object::showDotLine(const class point& p1, const class point& p2, const uint32_t c)
{
	float dx = p2.x() - p1.x(), dy = p2.y() - p1.y(), dz = p2.z() - p1.z();
	float dmax = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
	for (float i = 0; i < dmax; i += 4)
		showPoint(point(p1.x() + dx * i / dmax, p1.y() + dy * i / dmax, p1.z() + dz * i / dmax), c);
	showPoint(p2, c);
}

inline class point object::convPoint(const class point& p, const class angle& a)
{
	// Rotation matrix (http://en.wikipedia.org/wiki/Rotation_matrix)
	float cosrx = cos(a.x()), cosry = cos(a.y()), cosrz = cos(a.z()), sinrx = sin(a.x()), sinry = sin(a.y()), sinrz = sin(a.z());
	float x = (cosry * cosrz) * p.x() +				(-cosry * sinrz) * p.y() +				(sinry) * p.z();
	float y = (cosrz * sinrx * sinry + cosrx * sinrz) * p.x() +	(cosrx * cosrz - sinrx * sinry * sinrz) * p.y() +	(-cosry * sinrx) * p.z();
	float z = (-cosrx * cosrz * sinry + sinrx * sinrz) * p.x() +	(cosrz * sinrx + cosrx * sinry * sinrz) * p.y() +	(cosrx * cosry) * p.z();
	return point(x, y, z);
}

inline class point object::convPoint(const class point& p, const class axis *from, const class axis *to)
{
	if (from == 0)
		from = scrAxis;
	if (to == 0)
		to = gRoot;
	point res = convPoint(p, from->a()) + from->p();
	if (from->parent != gRoot)
		res = convPoint(res, from->parent);
	return res;
}

#endif
