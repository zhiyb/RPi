#ifndef __SCRBUFF_H
#define __SCRBUFF_H

#include <inttypes.h>
#include "basic.h"

#define SCRW	320
#define SCRH	240

struct scrBuffStruct {
	uint32_t colour, buff;
	float deep;
};

extern scrBuffStruct scrBuff[SCRW][SCRH];
extern volatile bool scrBuffLock;

namespace scr {
	static inline void drawPoint(const class point& p, const uint32_t c);
	static inline void drawLine(const class point& p1, const class point& p2, const uint32_t c);
	static inline void drawDotLine(const class point& p1, const class point& p2, const uint32_t c);
	static inline void drawSphere(const class point& center, const class point& r, const bool fill, const uint32_t c);
	void scrCapture(const char *path);
}

#include <math.h>
#include <stdlib.h>
#include "circle.h"

inline void scr::drawPoint(const class point& p, const uint32_t c)
{
	int x = p.x() + 0.5, y = p.y() + 0.5, z = p.z() + 0.5;
	if (x >= SCRW || y >= SCRH || x < 0 || y < 0)
		return;
	if (z > 0 || (scrBuff[x][y].deep <= 0 && scrBuff[x][y].deep > z))
		return;
	scrBuff[x][y].deep = z;
	scrBuff[x][y].colour = c;
}

inline void scr::drawLine(const class point& p1, const class point& p2, const uint32_t c)
{
#if 0
	float dz = p2.z() - p1.z();

	// Bresenham's line algorithm (http://en.wikipedia.org/wiki/Bresenham's_line_algorithm)
	int x0 = p1.x() + 0.5, x1 = p2.x() + 0.5, y0 = p1.y() + 0.5, y1 = p2.y() + 0.5;
	int dx = abs(x1 - x0), dy = abs(y1 - y0);
	int sx = x0 < x1 ? 1 : -1, sy = y0 < y1 ? 1 : -1, err = dx - dy;

	while (true) {
		drawPoint(point(x0, y0, p1.z() + dz * abs(x1 - x0) / dx), c);
		if (x0 == x1 && y0 == y1)
			break;
		int e2 = 2 * err;
		if (e2 > -dy) {
			err = err - dy;
			x0 = x0 + sx;
		}
		if (x0 == x1 && y0 == y1) {
			drawPoint(point(x0, y0, p1.z() + dz * abs(x1 - x0) / dx), c);
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
		drawPoint(point(p1.x() + dx * i / dmax, p1.y() + dy * i / dmax, p1.z() + dz * i / dmax), c);
	drawPoint(p2, c);
#endif
}

inline void scr::drawDotLine(const class point& p1, const class point& p2, const uint32_t c)
{
	float dx = p2.x() - p1.x(), dy = p2.y() - p1.y(), dz = p2.z() - p1.z();
	float dmax = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
	for (float i = 0; i < dmax; i += 4)
		drawPoint(point(p1.x() + dx * i / dmax, p1.y() + dy * i / dmax, p1.z() + dz * i / dmax), c);
	drawPoint(p2, c);
}

static inline void scr::drawSphere(const class point& center, const class point& r, const bool fill, const uint32_t c)
{
	float radius = r.x();
	if (radius < CIRCLE_STEP) {
		drawPoint(center + point(0, 0, r.z()), c);
		drawPoint(center - point(0, 0, r.z()), c);
		return;
	}
	if (fill)
		drawSphere(center, point(radius - CIRCLE_STEP, sqrt(r.z() * r.z() - (radius - CIRCLE_STEP) * (radius - CIRCLE_STEP)), r.z()), true, c);
	float x = radius, y = 0;
	while (y / x < tan(3.1415926535 / 4) + 0.2) {
		drawPoint(center + point(x, y, r.y()), c);
		drawPoint(center + point(x, -y, r.y()), c);
		drawPoint(center + point(-x, y, r.y()), c);
		drawPoint(center + point(-x, -y, r.y()), c);
		drawPoint(center + point(y, x, r.y()), c);
		drawPoint(center + point(y, -x, r.y()), c);
		drawPoint(center + point(-y, x, r.y()), c);
		drawPoint(center + point(-y, -x, r.y()), c);
		drawPoint(center + point(x, y, -r.y()), c);
		drawPoint(center + point(x, -y, -r.y()), c);
		drawPoint(center + point(-x, y, -r.y()), c);
		drawPoint(center + point(-x, -y, -r.y()), c);
		drawPoint(center + point(y, x, -r.y()), c);
		drawPoint(center + point(y, -x, -r.y()), c);
		drawPoint(center + point(-y, x, -r.y()), c);
		drawPoint(center + point(-y, -x, -r.y()), c);
		y += 1;
		x = sqrt(radius * radius - y * y);
	}
}

#endif
