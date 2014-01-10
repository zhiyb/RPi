#ifndef __CUBE_H
#define __CUBE_H

#include "basic.h"
#include "object.h"

class cubeFrame: public object
{
public:
	inline cubeFrame(class axis *parent, \
			const class point p1 = point(), \
			const class point p2 = point(), \
			const class point p3 = point(), \
			const class point p4 = point(), \
			const uint32_t c = 0);
	inline void set(const class point p1 = point(), \
			const class point p2 = point(), \
			const class point p3 = point(), \
			const class point p4 = point(), \
			const uint32_t c = 0);

private:
	uint32_t colour;
	class point coord[12];
	class line *edge[12];
};

#include "line.h"

inline cubeFrame::cubeFrame(class axis *parent, const class point p1, \
		const class point p2, const class point p3, \
		const class point p4, const uint32_t c): object(parent)
{
	edge[0] = new class line(parent);
	edge[1] = new class line(parent);
	edge[2] = new class line(parent);
	edge[3] = new class line(parent);
	edge[4] = new class line(parent);
	edge[5] = new class line(parent);
	edge[6] = new class line(parent);
	edge[7] = new class line(parent);
	edge[8] = new class line(parent);
	edge[9] = new class line(parent);
	edge[10] = new class line(parent);
	edge[11] = new class line(parent);
	set(p1, p2, p3, p4, c);
}

inline void cubeFrame::set(const class point p1, const class point p2, \
		const class point p3, const class point p4, \
		const uint32_t c)
{
	colour = c;
	coord[0] = p1;
	coord[1] = p2;
	coord[2] = p3;
	coord[3] = p4;
	edge[0]->set(p1, p2, c);
	edge[1]->set(p1, p3, c);
	edge[2]->set(p1, p4, c);
	edge[3]->set(p2, p2 + p3 - p1, c);
	edge[4]->set(p3, p2 + p3 - p1, c);
	edge[5]->set(p3, p4 + p3 - p1, c);
	edge[6]->set(p4, p4 + p3 - p1, c);
	edge[7]->set(p2, p4 + p2 - p1, c);
	edge[8]->set(p4, p4 + p2 - p1, c);
	edge[9]->set(p2 + p3 - p1, p4 + p2 - p1 + p3 - p1, c);
	edge[10]->set(p4 + p3 - p1, p4 + p2 - p1 + p3 - p1, c);
	edge[11]->set(p4 + p2 - p1, p4 + p2 - p1 + p3 - p1, c);
}

#endif
