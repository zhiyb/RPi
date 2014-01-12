#ifndef __CIRCLE_H
#define __CIRCLE_H

#include "object.h"
#include "basic.h"
#include <list>
#define PI		3.141592653589793
#define CIRCLE_STEP	0.8

class circle: public object
{
public:
	inline circle(class object *parent = 0, const class point p = point(), const class angle a = angle(), const float r = 0, const bool f = false, const uint32_t c = 0);
	inline void set(const class point p = point(), const class angle a = angle(), const float r = 0, const bool f = false, const uint32_t c = 0);

protected:
	inline void paint(void);

private:
	bool fill;
	float radius;
};

#include <math.h>

inline circle::circle(class object *parent, const class point p, const class angle a, const float r, const bool f, const uint32_t c): object(parent)
{
	set(p, a, r, f, c);
}

inline void circle::set(const class point p, const class angle a, const float r, const bool f, const uint32_t c)
{
	fill = f;
	radius = r;
	setColour(c);
	setTPoint(p);
	setTAngle(a);
}

inline void circle::paint(void)
{
	using namespace scr;
	float x = radius, y = 0;
	while (y / x < 1) {
		if (fill) {
			drawLine(transform(point(x, y)), transform(point(-x, y)), c());
			drawLine(transform(point(x, -y)), transform(point(-x, -y)), c());
			drawLine(transform(point(y, x)), transform(point(-y, x)), c());
			drawLine(transform(point(y, -x)), transform(point(-y, -x)), c());
			drawLine(transform(point(x, y)), transform(point(-x, -y)), c());
			drawLine(transform(point(x, -y)), transform(point(-x, y)), c());
			drawLine(transform(point(y, x)), transform(point(-y, -x)), c());
			drawLine(transform(point(y, -x)), transform(point(-y, x)), c());
		} else {
			drawPoint(transform(point(x, y)), c());
			drawPoint(transform(point(x, -y)), c());
			drawPoint(transform(point(-x, y)), c());
			drawPoint(transform(point(-x, -y)), c());
			drawPoint(transform(point(y, x)), c());
			drawPoint(transform(point(y, -x)), c());
			drawPoint(transform(point(-y, x)), c());
			drawPoint(transform(point(-y, -x)), c());
		}
		y += CIRCLE_STEP;
		x = sqrt(radius * radius - y * y);
	}
}

#endif
