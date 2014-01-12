#ifndef __OBJECT_H
#define __OBJECT_H

#include <inttypes.h>
#include <list>
#include "basic.h"

class object
{
public:
	inline object(class object *parent = 0, const class point& p = point(), const class angle& a = angle(), const float disp = 0);
	inline virtual ~object(void);
	inline void show(void);
	inline class object *showAxis(const float disp = 0) {display = disp; return this;}
	inline class object *insert(class object *o) {obj.push_back(o); return this;}
	inline class object *remove(class object *o) {obj.remove(o); return this;}
	virtual inline void setColour(const uint32_t c = 0) {colour = c;}
	virtual inline void setT(const class point& p = point(), const class angle& a = angle()) {tPoint = p; tAngle = a;}
	virtual inline void setTPoint(const class point& p = point()) {tPoint = p;}
	virtual inline void setTAngle(const class angle& a = angle()) {tAngle = a;}
	virtual inline void set(const class point& p = point(), const class angle& a = angle()) {setT(p, a);}
	virtual inline void setPoint(const class point& p = point()) {setTPoint(p);}
	virtual inline void setAngle(const class angle& a = angle()) {setTAngle(a);}
	virtual inline void setP(const class point& p = point()) {setTPoint(p);}
	virtual inline void setA(const class angle& a = angle()) {setTAngle(a);}
	virtual inline uint32_t c(void) const {return colour;}
	virtual inline class point p(void) const {return tPoint;}
	virtual inline class angle a(void) const {return tAngle;}

protected:
	virtual inline class point transform(const class point& p = point());
	static inline class point convPoint(const class point& p = point(), const class angle& a = angle());
	virtual inline void paint(void) {}

	uint32_t colour;
	float display;
	class object *parent;
	class point tPoint;
	class angle tAngle;

private:
	std::list<class object *> obj;
};

extern class object *gRoot;
extern class object *gAxis;

#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include "scrbuff.h"

inline object::object(class object *parent, const class point& p, const class angle& a, const float disp)
{
	if (parent == 0)
		parent = gAxis;
	if ((int)parent != -1)
		parent->insert(this);
	this->parent = parent;
	tPoint = p;
	tAngle = a;
	display = disp;
	colour = 0;
}

inline object::~object(void)
{
	while (!obj.empty())
		obj.pop_back();
	parent->remove(this);
}

inline class point object::transform(const class point& p)
{
	if ((int)parent == -1)
		return p;
	return parent->transform(tPoint + convPoint(p, tAngle));
}

inline class point object::convPoint(const class point& p, const class angle& a)
{
	// Rotation matrix (http://en.wikipedia.org/wiki/Rotation_matrix)
	float cosrx = cos(a.x()), cosry = cos(a.y()), cosrz = cos(a.z()), sinrx = sin(a.x()), sinry = sin(a.y()), sinrz = sin(a.z());
	float x = (cosry * cosrz) * p.x() +				(-cosry * sinrz) * p.y() +				(sinry) * p.z();
	float y = (cosrz * sinrx * sinry + cosrx * sinrz) * p.x() +	(cosrx * cosrz - sinrx * sinry * sinrz) * p.y() +	(-cosry * sinrx) * p.z();
	float z = (-cosrx * cosrz * sinry + sinrx * sinrz) * p.x() +	(cosrz * sinrx + cosrx * sinry * sinrz) * p.y() +	(cosrx * cosry) * p.z();
	return point(x, y, z);
}

inline void object::show(void)
{
	using namespace scr;
	if ((int)parent == -1) {
		while (scrBuffLock)
			usleep(1000);
		scrBuffLock = true;
		for (int x = 0; x < SCRW; x++)
			for (int y = 0; y < SCRH; y++) {
				scrBuff[x][y].deep = 1;
				scrBuff[x][y].buff = scrBuff[x][y].colour;
				scrBuff[x][y].colour = colour;
		}
		scrBuffLock = false;
	}
	if (display > 1) {
		drawDotLine(transform(), transform(point(display, 0, 0)), 0xFF0000);
		drawDotLine(transform(), transform(point(0, display, 0)), 0x00FF00);
		drawDotLine(transform(), transform(point(0, 0, display)), 0x0000FF);
	}
	for (std::list<class object *>::iterator it = obj.begin(); it != obj.end(); it++)
		(*it)->show();
	paint();
}

#endif
