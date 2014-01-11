#ifndef __SCRBUFF_H
#define __SCRBUFF_H

#include <inttypes.h>
#include "basic.h"

#define SCRW	320
#define SCRH	240

struct scrBuffStruct {
	uint32_t colour;
	float deep;
};

extern scrBuffStruct scrBuff[SCRW][SCRH];

namespace scr {
	static inline void showPoint(const class point& p, const uint32_t c);
	static inline void showLine(const class point& p1, const class point& p2, const uint32_t c);
	static inline void showDotLine(const class point& p1, const class point& p2, const uint32_t c);
	void scrCapture(const char *path);
}

#include <math.h>
#include <stdlib.h>

inline void scr::showPoint(const class point& p, const uint32_t c)
{
	int x = p.x() + 0.5, y = p.y() + 0.5, z = p.z() + 0.5;
	if (x >= SCRW || y >= SCRH || x < 0 || y < 0)
		return;
	if (z > 0 || (scrBuff[x][y].deep <= 0 && scrBuff[x][y].deep > z))
		return;
	scrBuff[x][y].deep = z;
	scrBuff[x][y].colour = c;
}

inline void scr::showLine(const class point& p1, const class point& p2, const uint32_t c)
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

inline void scr::showDotLine(const class point& p1, const class point& p2, const uint32_t c)
{
	float dx = p2.x() - p1.x(), dy = p2.y() - p1.y(), dz = p2.z() - p1.z();
	float dmax = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
	for (float i = 0; i < dmax; i += 4)
		showPoint(point(p1.x() + dx * i / dmax, p1.y() + dy * i / dmax, p1.z() + dz * i / dmax), c);
	showPoint(p2, c);
}

#endif
