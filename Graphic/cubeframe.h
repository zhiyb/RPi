#ifndef __CUBE_H
#define __CUBE_H

#include "basic.h"
#include "object.h"

class cubeFrame: public object
{
public:
	// Cuboid
	inline cubeFrame(class object *parent = 0, \
			const class point p1 = point(), \
			const class point p2 = point(), \
			const uint32_t c = 0);
	// Parallelepiped
	inline cubeFrame(class object *parent = 0, \
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
	inline void setColour(const uint32_t c = 0);

private:
	class point dir[3];
	class line *edge[12];
};

#include "line.h"

inline cubeFrame::cubeFrame(class object *parent, const class point p1, \
		const class point p2, const uint32_t c): object(parent)
{
	for (int i = 0; i < 12; i++)
		edge[i] = new class line(this);
	set(p1, point(0, 0, p2.z()), point(0, p2.y(), 0), point(p2.x(), 0, 0), c);
}

inline cubeFrame::cubeFrame(class object *parent, const class point p1, \
		const class point p2, const class point p3, \
		const class point p4, const uint32_t c): object(parent)
{
	for (int i = 0; i < 12; i++)
		edge[i] = new class line(this);
	set(p1, p2, p3, p4, c);
}

inline void cubeFrame::set(const class point p1, const class point p2, \
		const class point p3, const class point p4, \
		const uint32_t c)
{
	colour = c;
	setTPoint(p1);
	dir[0] = p2;
	dir[1] = p3;
	dir[2] = p4;
	edge[0]->set(0, p2, c);
	edge[4]->set(p3, p2, c);
	edge[8]->set(p4, p2, c);
	edge[10]->set(p4 + p3, p2, c);
	edge[1]->set(0, p3, c);
	edge[3]->set(p2, p3, c);
	edge[6]->set(p4, p3, c);
	edge[11]->set(p4 + p2, p3, c);
	edge[2]->set(0, p4, c);
	edge[7]->set(p2, p4, c);
	edge[5]->set(p3, p4, c);
	edge[9]->set(p2 + p3, p4, c);
}

inline void cubeFrame::setColour(const uint32_t c)
{
	for (int i = 0; i < 12; i++)
		edge[i]->setColour(c);
}

#endif
