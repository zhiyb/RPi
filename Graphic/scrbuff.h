#ifndef __SCRBUFF_H
#define __SCRBUFF_H

#include <inttypes.h>
#include "basic.h"

#define SCRW	320
#define SCRH	240

#define ZOOM_FACTOR	400
#define ZOOM_IGNORE	0

struct scrBuffStruct {
	uint32_t colour, buff;
	float deep;
};

extern scrBuffStruct scrBuff[SCRW][SCRH];
extern volatile bool scrBuffLock;

namespace scr {
	static inline void drawPoint(const class point& pOrig, const uint32_t c);
	static inline void drawLine(const class point& p1, const class point& p2, const uint32_t c);
	static inline void drawDotLine(const class point& p1, const class point& p2, const uint32_t c);
	static inline void drawSphereLine(const class point& l, const class point& r, const uint32_t c, const float radius, const class point& center);
	static inline void drawSphere(const class point& center, const float radius, const uint32_t c);
	void scrCapture(const char *path);
}

#include <math.h>
#include <stdlib.h>
#include "circle.h"

inline void scr::drawPoint(const class point& pOrig, const uint32_t c)
{
	int z = pOrig.z() + 0.5;
	if (z >= 0)
		return;
	float factor = ZOOM_FACTOR / (ZOOM_FACTOR - ZOOM_IGNORE - pOrig.z());
	factor = factor > 1 ? 1 : factor;
	//int x = gAxis->p().x() + (pOrig.x() - gAxis->p().x()) * factor + 0.5, y = gAxis->p().y() + (pOrig.y() - gAxis->p().y()) * factor + 0.5;
	int x = SCRW / 2 + (pOrig.x() - SCRW / 2) * factor + 0.5, y = SCRH / 2 + (pOrig.y() - SCRH / 2) * factor + 0.5;
	if (x >= SCRW || y >= SCRH || x < 0 || y < 0)
		return;
	if (scrBuff[x][y].deep <= 0 && scrBuff[x][y].deep > z)
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
	dmax = dmax > abs(dz) ? dmax : abs(dz);
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

inline void scr::drawSphereLine(const class point& l, const class point& r, const uint32_t c, const float radius, const class point& center)
{
	float dx = r.x() - l.x(), dy = r.y() - l.y();
	float dmax = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
	for (float i = 0; i < dmax + CIRCLE_STEP; i += CIRCLE_STEP) {
		class point coord(point(dx * i / dmax, dy * i / dmax) + l);
		float dz = radius * radius - coord.x() * coord.x() - coord.y() * coord.y();
		dz = dz < 0 ? 0 : sqrt(dz);
		drawPoint(center + coord + point(0, 0, dz), c);
		drawPoint(center + coord - point(0, 0, dz), c);
	}
}

static inline void scr::drawSphere(const class point& center, const float radius, const uint32_t c)
{
	float x = radius, y = 0;
	while (y / x < 1) {
		drawSphereLine(point(x, +y), point(-x, +y), c, radius, center);
		drawSphereLine(point(x, -y), point(-x, -y), c, radius, center);
		drawSphereLine(point(y, +x), point(-y, +x), c, radius, center);
		drawSphereLine(point(y, -x), point(-y, -x), c, radius, center);
		y += CIRCLE_STEP;
		x = sqrt(radius * radius - y * y);
	}
}

#endif
