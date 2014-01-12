#ifndef __SPHERE_H
#define __SPHERE_H

#include <list>
#include "basic.h"
#include "object.h"
#include "circle.h"

class sphere: public object
{
public:
	inline sphere(class object *parent = 0, const class point p = point(), const float r = 0, const uint32_t c = 0);
	inline void set(const class point p = point(), const float r = 0, const uint32_t c = 0);

protected:
	inline void paint(void);

private:
	float radius;
};

#include "scrbuff.h"

inline sphere::sphere(class object *parent, const class point p, const float r, const uint32_t c): object(parent)
{
	set(p, r, c);
}

inline void sphere::set(const class point p, const float r, const uint32_t c)
{
	radius = r;
	colour = c;
	setTPoint(p);
}

inline void sphere::paint(void)
{
	class point center = transform(), r = transform(point(radius, 0, 0));
	float radius = (center - r).length();
	scr::drawSphere(center, point(radius, 0, radius), true, c());
}

#endif
