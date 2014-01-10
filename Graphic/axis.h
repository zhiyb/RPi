#ifndef __AXIS_H
#define __AXIS_H

#include <vector>
#include "basic.h"

class axis
{
public:
	inline axis(const class point p = point(), const class angle a = angle(), const bool e = false);
	inline void insert(class object *o);
	inline class angle a(void) const {return scrA;}
	inline class point p(void) const {return scrP;}
	inline void setA(const class angle a) {scrA = a;}
	inline void setP(const class point p) {scrP = p;}
	inline void showAxis(const bool e) {display = e;}
	inline virtual void show(void);

private:
	bool display;
	class angle scrA;
	class point scrP;
	std::vector<class object *> obj;
};

extern class axis *scrAxis;

#include <iostream>
#include "scrbuff.h"
#include "object.h"

inline axis::axis(const class point p, const class angle a, const bool e)
{
	scrA = a;
	scrP = p;
	display = e;
}

inline void axis::insert(class object *o)
{
	obj.push_back(o);
}

inline void axis::show(void)
{
	for (int x = 0; x < SCRW; x++)
		for (int y = 0; y < SCRH; y++) {
			scrBuff[x][y].deep = 1;
			scrBuff[x][y].colour = 0;
		}
	if (display) {
		object::showDotLine(object::convPoint(this, point()), object::convPoint(this, point(200, 0, 0)), 0xFF0000);
		object::showDotLine(object::convPoint(this, point()), object::convPoint(this, point(0, 200, 0)), 0x00FF00);
		object::showDotLine(object::convPoint(this, point()), object::convPoint(this, point(0, 0, 200)), 0x0000FF);
	}
	for (std::vector<class object *>::size_type i = 0; i != obj.size(); i++)
		obj[i]->show();
}

#endif
