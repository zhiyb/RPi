#ifndef __STRING_H
#define __STRING_H

#include <string>
#include "object.h"

class gString: public object
{
public:
	inline gString(class axis *parent = 0, class point p = point(), uint32_t c = 0, std::string s = 0, float z = 1);
	inline void set(class point p = point(), uint32_t c = 0, std::string s = 0, float z = 1);
	inline void setColour(const uint32_t c = 0) {colour = c;}
	inline void show(void);
	inline void showChar(const char c, const int x);

private:
	float zoom;
	uint32_t colour;
	std::string str;
	class point p;
};

#include <iostream>
#include "ascii.h"

inline gString::gString(class axis *parent, class point p, uint32_t c, std::string s, float z): object(parent)
{
	set(p, c, s, z);
}

inline void gString::set(class point p, uint32_t c, std::string s, float z)
{
	str = s;
	colour = c;
	zoom = z;
	this->p = p;
}

inline void gString::showChar(const char c, const int x)
{
	for (int dy = 0; dy < FONT_H * zoom; dy++)
		for (int dx = 0; dx < FONT_W * zoom; dx++)
			if (ascii[c - ' '][(int)(dy / zoom)] & (0x80 >> (int)(dx / zoom)))
				showPoint(convPoint(point(x + dx, p.y() - dy, p.z()), parent), colour);
}

inline void gString::show(void)
{
	//std::cout << str << std::endl;
	for (std::string::size_type i = 0, x = p.x(); i != str.size(); i++, x += FONT_W * zoom)
		showChar(str[i], x);
}

#endif
