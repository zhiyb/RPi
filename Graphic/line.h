#ifndef __LINE_H
#define __LINE_H

#include <inttypes.h>
#include "object.h"
#include "basic.h"

class line: public object
{
public:
	inline line(class object *parent = 0, \
			const class point p1 = point(), \
			const class point p2 = point(), \
			const uint32_t c = 0);
	inline void set(const class point p1, const class point p2, \
			const uint32_t c);

protected:
	inline void paint(void);

private:
	class point dir;
};

inline line::line(class object *parent, const class point p1, \
		const class point p2, const uint32_t c): object(parent)
{
	set(p1, p2, c);
}

inline void line::set(const class point p1, const class point p2, \
		const uint32_t c)
{
	setTPoint(p1);
	dir = p2;
	setColour(c);
}

inline void line::paint(void)
{
	scr::drawLine(transform(0), transform(dir), c());
}

#endif
