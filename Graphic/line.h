#ifndef __LINE_H
#define __LINE_H

#include <inttypes.h>
#include "object.h"
#include "basic.h"

class line: public object
{
public:
	inline line(class axis *parent = 0, \
			const class point p1 = point(), \
			const class point p2 = point(), \
			const uint32_t c = 0);
	inline void set(const class point p1, const class point p2, \
			const uint32_t c);
	inline void setColour(const uint32_t c = 0) {colour = c;}
	inline void show(void);

private:
	uint32_t colour;
	class point p1, p2;
};

#include <iostream>

inline line::line(class axis *parent, const class point p1, \
		const class point p2, const uint32_t c): object(parent)
{
	set(p1, p2, c);
}

inline void line::set(const class point p1, const class point p2, \
		const uint32_t c)
{
	this->p1 = p1;
	this->p2 = p2;
	colour = c;
}

inline void line::show(void)
{
	//std::cout << "line->show()" << std::endl;
	showLine(convPoint(p1, parent), convPoint(p2, parent), colour);
}

#endif
