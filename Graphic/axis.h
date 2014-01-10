#ifndef __AXIS_H
#define __AXIS_H

#include <vector>
#include "basic.h"

class axis
{
	friend class object;

public:
	inline axis(class axis *parent = 0, const class point p = point(), const class angle a = angle(), const float disp = 0);
	inline void insert(class object *o) {obj.push_back(o);}
	inline void insert(class axis *a) {ax.push_back(a);}
	inline class angle a(void) const {return scrA;}
	inline class point p(void) const {return scrP;}
	inline void setA(const class angle a) {scrA = a;}
	inline void setP(const class point p) {scrP = p;}
	inline void showAxis(const float disp) {display = disp;}
	inline virtual void show(void);

private:
	float display;
	class angle scrA;
	class point scrP;
	class axis *parent;
	std::vector<class object *> obj;
	std::vector<class axis *> ax;
};

extern class axis *scrAxis;
extern class axis *gRoot;

#include <iostream>
#include "scrbuff.h"
#include "object.h"

inline axis::axis(class axis *parent, const class point p, const class angle a, const float disp)
{
	if (parent == 0)
		parent = gRoot;
	if ((int)parent != -1)
		parent->insert(this);
	this->parent = parent;
	scrA = a;
	scrP = p;
	display = disp;
}

inline void axis::show(void)
{
	if ((int)parent == -1)
		scrBuffClean();
	if (display > 1) {
		object::showDotLine(object::convPoint(point(), this), object::convPoint(point(display, 0, 0), this), 0xFF0000);
		object::showDotLine(object::convPoint(point(), this), object::convPoint(point(0, display, 0), this), 0x00FF00);
		object::showDotLine(object::convPoint(point(), this), object::convPoint(point(0, 0, display), this), 0x0000FF);
	}
	for (std::vector<class object *>::size_type i = 0; i != obj.size(); i++)
		obj[i]->show();
	for (std::vector<class axis *>::size_type i = 0; i != ax.size(); i++)
		ax[i]->show();
}

#endif
