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
	static inline class point convPoint(const class axis *org = 0, const class point& p = point());

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
	for (float i = 0; i < dmax; i += 3)
		showPoint(point(p1.x() + dx * i / dmax, p1.y() + dy * i / dmax, p1.z() + dz * i / dmax), c);
	showPoint(p2, c);
}

inline class point object::convPoint(const class axis *org, const class point& p)
{
	if (org == 0)
		org = scrAxis;
#define X	(p.x())
#define Y	(p.y())
#define Z	(p.z())
#define RX	(org->a().x())
#define RY	(org->a().y())
#define RZ	(org->a().z())
	/*float x = org->p().x() + (cos(RY) * cos(RZ)) * X +					(-cos(RY) * sin(RZ)) * Y +				(sin(RY)) * Z;
	float y = org->p().y() + (cos(RZ) * sin(RX) * sin(RY) + cos(RX) * sin(RZ)) * X +	(cos(RX) * cos(RZ) - sin(RX) * sin(RY) * sin(RZ)) * Y +	(-cos(RY) * sin(RX)) * Z;
	float z = org->p().z() + (-cos(RX) * cos(RZ) * sin(RY) + sin(RX) * sin(RZ)) * X +	(cos(RZ) * sin(RX) + cos(RX) * sin(RY) * sin(RZ)) * Y +	(cos(RX) * cos(RY)) * Z;*/
	float cosrx = cos(RX), cosry = cos(RY), cosrz = cos(RZ), sinrx = sin(RX), sinry = sin(RY), sinrz = sin(RZ);
	float x = org->p().x() + (cosry * cosrz) * X +				(-cosry * sinrz) * Y +				(sinry) * Z;
	float y = org->p().y() + (cosrz * sinrx * sinry + cosrx * sinrz) * X +	(cosrx * cosrz - sinrx * sinry * sinrz) * Y +	(-cosry * sinrx) * Z;
	float z = org->p().z() + (-cosrx * cosrz * sinry + sinrx * sinrz) * X +	(cosrz * sinrx + cosrx * sinry * sinrz) * Y +	(cosrx * cosry) * Z;
#undef X
#undef Y
#undef Z
#undef RX
#undef RY
#undef RZ
	return point(x, y, z);
}

#endif
