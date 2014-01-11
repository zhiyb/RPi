#ifndef __SPHEREFRAME_H
#define __SPHEREFRAME_H

#include "basic.h"
#include "object.h"

class sphereFrame: public object
{
public:
	inline sphereFrame(class object *parent = 0, const class point p = point(), const float r = 0, const uint32_t c = 0);
	inline void set(const class point p = point(), const float r = 0, const uint32_t c = 0);
	inline void setColour(const uint32_t c = 0);

private:
	float radius;
	class circle *frame[16];
};

#include "circle.h"

inline sphereFrame::sphereFrame(class object *parent, const class point p, const float r, const uint32_t c): object(parent)
{
	for (int i = 0; i < 16; i++)
		frame[i] = new circle(this);
	set(p, r, c);
}

inline void sphereFrame::set(const class point p, const float r, const uint32_t c)
{
	radius = r;
	colour = c;
	setTPoint(p);
	frame[0]->set(point(), angle(0, PI * 0 / 6, 0), r, false, c);
	frame[1]->set(point(), angle(0, PI * 1 / 6, 0), r, false, c);
	frame[2]->set(point(), angle(0, PI * 2 / 6, 0), r, false, c);
	frame[3]->set(point(), angle(0, PI * 3 / 6, 0), r, false, c);
	frame[4]->set(point(), angle(0, PI * 4 / 6, 0), r, false, c);
	frame[5]->set(point(), angle(0, PI * 5 / 6, 0), r, false, c);
	frame[6]->set(point(), angle(PI * 1 / 6, 0, 0), r, false, c);
	frame[7]->set(point(), angle(PI * 2 / 6, 0, 0), r, false, c);
	frame[8]->set(point(), angle(PI * 3 / 6, 0, 0), r, false, c);
	frame[9]->set(point(), angle(PI * 4 / 6, 0, 0), r, false, c);
	frame[10]->set(point(), angle(PI * 5 / 6, 0, 0), r, false, c);
	frame[11]->set(point(), angle(PI / 2, PI * 1 / 6, 0), false, r, c);
	frame[12]->set(point(), angle(PI / 2, PI * 2 / 6, 0), false, r, c);
	frame[13]->set(point(), angle(PI / 2, PI * 3 / 6, 0), false, r, c);
	frame[14]->set(point(), angle(PI / 2, PI * 4 / 6, 0), false, r, c);
	frame[15]->set(point(), angle(PI / 2, PI * 5 / 6, 0), false, r, c);
}

inline void sphereFrame::setColour(const uint32_t c)
{
	for (int i = 0; i < 16; i++)
		frame[i]->setColour(c);
}

#endif
