#ifndef __CIRCLE_H
#define __CIRCLE_H

#include "object.h"
#include "basic.h"
#include <list>
#define PI		(3.141592653589793)
#define CIRCLE_STEP	0.25

class circle: public object
{
public:
	inline circle(class object *parent = 0, const class point p = point(), const class angle a = angle(), const float r = 0, const bool f = false, const uint32_t c = 0);
	inline void set(const class point p = point(), const class angle a = angle(), const float r = 0, const bool f = false, const uint32_t c = 0);
	inline void setColour(const uint32_t c = 0);

protected:
	inline void paint(void);

private:
	float radius;
	std::list<class circle *> circles;
};

#include <math.h>

inline circle::circle(class object *parent, const class point p, const class angle a, const float r, const bool f, const uint32_t c): object(parent)
{
	set(p, a, r, f, c);
}

inline void circle::set(const class point p, const class angle a, const float r, const bool f, const uint32_t c)
{
	radius = r;
	setColour(c);
	setTPoint(p);
	setTAngle(a);
	while (!circles.empty())
		circles.pop_back();
	if (f)
		for (float r = radius; r > CIRCLE_STEP; r -= CIRCLE_STEP)
			circles.push_back(new circle(this, point(), angle(), r, false, c));
}

inline void circle::setColour(const uint32_t c)
{
	colour = c;
	for (std::list<class circle *>::iterator it = circles.begin(); it != circles.end(); it++)
		(*it)->setColour(c);
}

inline void circle::paint(void)
{
	using namespace scr;
	float x = radius, y = 0;
	while (y / x < tan(3.1415926535 / 4)) {
		drawPoint(transform(point(x, y, 0)), c());
		drawPoint(transform(point(x, -y, 0)), c());
		drawPoint(transform(point(-x, y, 0)), c());
		drawPoint(transform(point(-x, -y, 0)), c());
		drawPoint(transform(point(y, x, 0)), c());
		drawPoint(transform(point(y, -x, 0)), c());
		drawPoint(transform(point(-y, x, 0)), c());
		drawPoint(transform(point(-y, -x, 0)), c());
		y += 1;
		x = sqrt(radius * radius - y * y);
	}
}

#endif
