#ifndef __STRING_H
#define __STRING_H

#include <string>
#include "object.h"

class gString: public object
{
public:
	inline gString(class object *parent = 0, class point p = point(), class angle a = angle(), uint32_t c = 0, std::string s = 0, float z = 1);
	inline void set(class point p = point(), class angle a = angle(), uint32_t c = 0, std::string s = 0, float z = 1);
	inline void setString(const std::string& s) {str = s;}
	inline void paintChar(const char c, const int x);
	inline void paint(void);

private:
	float zoom;
	std::string str;
};

#include "ascii.h"

inline gString::gString(class object *parent, class point p, class angle a, uint32_t c, std::string s, float z): object(parent)
{
	set(p, a, c, s, z);
}

inline void gString::set(class point p, class angle a, uint32_t c, std::string s, float z)
{
	str = s;
	zoom = z;
	setColour(c);
	setTPoint(p);
	setTAngle(a);
}

inline void gString::paintChar(const char c, const int x)
{
	using namespace scr;
	for (int dy = 0; dy < FONT_H * zoom; dy++)
		for (int dx = 0; dx < FONT_W * zoom; dx++)
			if (ascii[c - ' '][FONT_H - 1 - (int)(dy / zoom)] & (0x80 >> (int)(dx / zoom)))
				showPoint(transform(point(x + dx, dy, 0)), colour);
}

inline void gString::paint(void)
{
	for (std::string::size_type i = 0; i != str.size(); i++)
		paintChar(str[i], i * FONT_W * zoom);
}

#endif
