#ifndef __CIRCLE_H
#define __CIRCLE_H

#include "object.h"
#include "basic.h"
#define PI (3.141592653589793)

class circle: public object
{
public:
	inline circle(class object *parent = 0, const class point p = point(), const class angle a = angle(), const float r = 0, const uint32_t c = 0);
	inline void set(const class point p = point(), const class angle a = angle(), const float r = 0, const uint32_t c = 0);
	inline void paint(void);

private:
	float radius;
};

#include <math.h>

inline circle::circle(class object *parent, const class point p, const class angle a, const float r, const uint32_t c): object(parent)
{
	set(p, a, r, c);
}

inline void circle::set(const class point p, const class angle a, const float r, const uint32_t c)
{
	radius = r;
	setColour(c);
	setTPoint(p);
	setTAngle(a);
}

inline void circle::paint(void)
{
	using namespace scr;
	float x = radius, y = 0;
	while (y / x < tan(3.1415926535 / 4)) {
		showPoint(transform(point(x, y, 0)), c());
		showPoint(transform(point(x, -y, 0)), c());
		showPoint(transform(point(-x, y, 0)), c());
		showPoint(transform(point(-x, -y, 0)), c());
		showPoint(transform(point(y, x, 0)), c());
		showPoint(transform(point(y, -x, 0)), c());
		showPoint(transform(point(-y, x, 0)), c());
		showPoint(transform(point(-y, -x, 0)), c());
		y += 1;
		x = sqrt(radius * radius - y * y);
	}
}

#endif
