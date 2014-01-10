#ifndef __SPHEREFRAME_H
#define __SPHEREFRAME_H

#include "basic.h"
#include "object.h"

class sphereFrame: public object
{
public:
	inline sphereFrame(class axis *parent = 0, const class point p = point(), const float r = 0, const uint32_t c = 0);
	inline void set(const class point p = point(), const float r = 0, const uint32_t c = 0);
	inline void setColour(const uint32_t c) {set(center, radius, c);}

private:
	uint32_t colour;
	float radius;
	class point center;
	class circle *frame[16];
};

#include "circle.h"

inline sphereFrame::sphereFrame(class axis *parent, const class point p, const float r, const uint32_t c): object(parent)
{
	for (int i = 0; i < 16; i++)
		frame[i] = new circle(parent);
	set(p, r, c);
}

inline void sphereFrame::set(const class point p, const float r, const uint32_t c)
{
	frame[0]->set(p, angle(0, PI * 0 / 6, 0), r, c);
	frame[1]->set(p, angle(0, PI * 1 / 6, 0), r, c);
	frame[2]->set(p, angle(0, PI * 2 / 6, 0), r, c);
	frame[3]->set(p, angle(0, PI * 3 / 6, 0), r, c);
	frame[4]->set(p, angle(0, PI * 4 / 6, 0), r, c);
	frame[5]->set(p, angle(0, PI * 5 / 6, 0), r, c);
	frame[6]->set(p, angle(PI * 1 / 6, 0, 0), r, c);
	frame[7]->set(p, angle(PI * 2 / 6, 0, 0), r, c);
	frame[8]->set(p, angle(PI * 3 / 6, 0, 0), r, c);
	frame[9]->set(p, angle(PI * 4 / 6, 0, 0), r, c);
	frame[10]->set(p, angle(PI * 5 / 6, 0, 0), r, c);
	frame[11]->set(p, angle(PI / 2, PI * 1 / 6, 0), r, c);
	frame[12]->set(p, angle(PI / 2, PI * 2 / 6, 0), r, c);
	frame[13]->set(p, angle(PI / 2, PI * 3 / 6, 0), r, c);
	frame[14]->set(p, angle(PI / 2, PI * 4 / 6, 0), r, c);
	frame[15]->set(p, angle(PI / 2, PI * 5 / 6, 0), r, c);
	colour = c;
	radius = r;
	center = p;
}

#endif