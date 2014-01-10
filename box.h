#ifndef BOX_H
#define BOX_H

#include <inttypes.h>
#include <iostream>
#include "conv.h"

#define SCR_W	320
#define SCR_H	240

class box
{
public:
	box(void);
	void move(void);
	void setSize(int size) {s = size;}
	class box& operator++(int x);

//protected:
	void show(void) {show(fgc);}
	virtual void show(uint32_t clr);

	double dx, dy;
	double x, y, s;
	uint32_t fgc, bgc;
};

std::ostream& operator<<(std::ostream& out, const class box& b)
{
	out << "x: " << b.x << std::endl;
	out << "y: " << b.y << std::endl;
	out << "s: " << b.s << std::endl;
	return out;
}

class box& box::operator++(int x)
{
	move();
	return *this;
}

void box::show(uint32_t clr)
{
	tft.rectangle(x, y, s, s, conv::c32to16(clr));
}

box::box(void)
{
	s = 5;
	x = (SCR_W - s) / 2;
	y = (SCR_H - s) / 2;
	dx = 1;
	dy = 1;
	fgc = 0xFFFF00;
	bgc = 0x66CCFF;
	show();
}

#define RAND() ((double)((rand() % 200) / 100.0 + 0.001))
void box::move(void)
{
	show(bgc);
	if ((int)x + s >= SCR_W || (int)x <= 0) {
		bgc = rand() % 0xFFFFFF;
		dx = (int)x <= 0 ? 1 : -1;
		dx = (double)(dx > 0 ? 1 : -1) * RAND();
		dy = (double)(dy > 0 ? 1 : -1) * RAND();
	}
	x += dx;
	if ((int)y + s >= SCR_H || (int)y <= 0) {
		bgc = rand() % 0xFFFFFF;
		dy = (int)y <= 0 ? 1 : -1;
		dx = (double)(dx > 0 ? 1 : -1) * RAND();
		dy = (double)(dy > 0 ? 1 : -1) * RAND();
	}
	y += dy;
	show(fgc);
}

#endif
