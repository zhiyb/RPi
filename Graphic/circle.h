#ifndef __CIRCLE_H
#define __CIRCLE_H

#include "axis.h"
#include "basic.h"

class circle: public object
{
public:
	inline circle(class axis *parent = 0, const class point p = point(), const class angle a = angle(), const float r = 0, const uint32_t c = 0);
	inline void set(const class point p = point(), const class angle a = angle(), const float r = 0, const uint32_t c = 0);
	inline void setColour(const uint32_t c) {colour = c;}
	inline void show(void);

private:
	class point center;
	class angle rot;
	float radius;
	uint32_t colour;
};

#include <math.h>

inline circle::circle(class axis *parent, const class point p, const class angle a, const float r, const uint32_t c): object(parent)
{
	set(p, a, r, c);
}

inline void circle::set(const class point p, const class angle a, const float r, const uint32_t c)
{
	center = p;
	rot = a;
	radius = r;
	colour = c;
}

inline void circle::show(void)
{
	float x = radius, y = 0;
	while (y / x < tan(3.1415926535 / 4)) {
		showPoint(convPoint(center + convPoint(point(x, y, 0), rot), parent), colour);
		showPoint(convPoint(center + convPoint(point(x, -y, 0), rot), parent), colour);
		showPoint(convPoint(center + convPoint(point(-x, y, 0), rot), parent), colour);
		showPoint(convPoint(center + convPoint(point(-x, -y, 0), rot), parent), colour);
		showPoint(convPoint(center + convPoint(point(y, x, 0), rot), parent), colour);
		showPoint(convPoint(center + convPoint(point(y, -x, 0), rot), parent), colour);
		showPoint(convPoint(center + convPoint(point(-y, x, 0), rot), parent), colour);
		showPoint(convPoint(center + convPoint(point(-y, -x, 0), rot), parent), colour);
		y += 1;
		x = sqrt(radius * radius - y * y);
	}
}

#endif
