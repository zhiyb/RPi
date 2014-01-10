#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <inttypes.h>
#include <TFT/tft.h>
#include <TFT/conv.h>
#include <Graphic/cubeframe.h>
#include <Graphic/string.h>

void init(void)
{
	gpio_init();
	tft.init();
	tft /= tft.FlipLandscape;
	tft.setBackground(0x0000);
	tft.setForeground(0xFFFF);
	tft.clean();
	tft++;
}

int main(void)
{
	init();

	class axis *newAxis = new axis(scrAxis, point(55, 55, 55), angle(), 60);
	new cubeFrame(newAxis, point(5, 5, 5), point(25, 25, 25), 0x7F7F7F);
	new cubeFrame(newAxis, point(5, -5, 5), point(25, -25, 25), 0xFF0000);
	new cubeFrame(newAxis, point(-5, 5, 5), point(-25, 25, 25), 0x00FF00);
	new cubeFrame(newAxis, point(5, 5, -5), point(25, 25, -25), 0x0000FF);
	new cubeFrame(newAxis, point(-5, -5, 5), point(-25, -25, 25), 0xFF00FF);
	new cubeFrame(newAxis, point(5, -5, -5), point(25, -25, -25), 0x00FFFF);
	new cubeFrame(newAxis, point(-5, 5, -5), point(-25, 25, -25), 0xFFFF00);
	new cubeFrame(newAxis, point(-5, -5, -5), point(-25, -25, -25), 0xFFFFFF);
	new cubeFrame(newAxis, point(30, 30, 30), point(-30, -30, -30), 0x3F3F3F);
	new gString(newAxis, point(0, 30 + 8, 0), 0x66CCFF, "Hello, world!");

	class axis *subAxis = new axis(scrAxis, point(-55, -55, -55), angle(), 60);
	new cubeFrame(subAxis, point(5, 5, 5), point(25, 25, 25), 0x7F7F7F);
	new cubeFrame(subAxis, point(5, -5, 5), point(25, -25, 25), 0xFF0000);
	new cubeFrame(subAxis, point(-5, 5, 5), point(-25, 25, 25), 0x00FF00);
	new cubeFrame(subAxis, point(5, 5, -5), point(25, 25, -25), 0x0000FF);
	new cubeFrame(subAxis, point(-5, -5, 5), point(-25, -25, 25), 0xFF00FF);
	new cubeFrame(subAxis, point(5, -5, -5), point(25, -25, -25), 0x00FFFF);
	new cubeFrame(subAxis, point(-5, 5, -5), point(-25, 25, -25), 0xFFFF00);
	new cubeFrame(subAxis, point(-5, -5, -5), point(-25, -25, -25), 0xFFFFFF);
	new cubeFrame(subAxis, point(30, 30, 30), point(-30, -30, -30), 0x3F3F3F);
	new gString(subAxis, point(0, 30 + 8, 0), 0x66CCFF, "Hello, world!");

	new cubeFrame(0, point(5, 5, 5), point(45, 45, 45), 0x7F7F7F);
	new cubeFrame(0, point(5, -5, 5), point(45, -45, 45), 0xFF0000);
	new cubeFrame(0, point(-5, 5, 5), point(-45, 45, 45), 0x00FF00);
	new cubeFrame(0, point(5, 5, -5), point(45, 45, -45), 0x0000FF);
	new cubeFrame(0, point(-5, -5, 5), point(-45, -45, 45), 0xFF00FF);
	new cubeFrame(0, point(5, -5, -5), point(45, -45, -45), 0x00FFFF);
	new cubeFrame(0, point(-5, 5, -5), point(-45, 45, -45), 0xFFFF00);
	new cubeFrame(0, point(-5, -5, -5), point(-45, -45, -45), 0xFFFFFF);
	class cubeFrame *cube = new cubeFrame(0, point(55, 55, 55), point(-55, -55, -55), 0x3F3F3F);
	class gString *str = new gString(0, point(0, 55 + 16, 0), 0x66CCFF, "Hello, world!", 2);
	scrAxis->setP(point(160, 120, -500));
	scrAxis->setA(angle(0.5, 0, 0));
	scrAxis->showAxis(150);
	while (true) {
		gRoot->show();
		tft.update();
		newAxis->setA(angle(newAxis->a().x() + 0.1, newAxis->a().y() + 0.1, newAxis->a().z() + 0.1));
		subAxis->setA(angle(subAxis->a().x() - 0.1, subAxis->a().y() - 0.1, subAxis->a().z() - 0.1));
		scrAxis->setA(angle(0.5, scrAxis->a().y() + 0.05, 0));
		cube->setColour(rand() % 0x1000000);
		str->setColour(rand() % 0x1000000);
		//usleep(100);
	}
	gpio_close();
	return 0;
}
