#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <inttypes.h>
#include <TFT/tft.h>
#include <TFT/conv.h>
#include <Graphic/object.h>
#include <Graphic/scrbuff.h>
#include <Graphic/cubeframe.h>
#include <Graphic/string.h>
#include <Graphic/sphereframe.h>
#include <time.h>

#define PICS	"/mnt/NFS/files/capture/"

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

	class object *subAxis = new object(0, point(-60, -60, -60), angle(), 150);
	(new cubeFrame(subAxis, point(5, 5, 5), point(20, 20, 20), 0x7F7F7F))->showAxis(100);
	(new cubeFrame(subAxis, point(5, -5, 5), point(20, -20, 20), 0xFF0000))->showAxis(100);
	(new cubeFrame(subAxis, point(-5, 5, 5), point(-20, 20, 20), 0x00FF00))->showAxis(100);
	(new cubeFrame(subAxis, point(5, 5, -5), point(20, 20, -20), 0x0000FF))->showAxis(100);
	(new cubeFrame(subAxis, point(-5, -5, 5), point(-20, -20, 20), 0xFF00FF))->showAxis(100);
	(new cubeFrame(subAxis, point(5, -5, -5), point(20, -20, -20), 0x00FFFF))->showAxis(100);
	(new cubeFrame(subAxis, point(-5, 5, -5), point(-20, 20, -20), 0xFFFF00))->showAxis(100);
	(new cubeFrame(subAxis, point(-5, -5, -5), point(-20, -20, -20), 0xFFFFFF))->showAxis(100);
	(new cubeFrame(subAxis, point(30, 30, 30), point(-60, -60, -60), 0x3F3F3F))->showAxis(100);
	(new gString(subAxis, point(0, 30, 0), angle(0, 0, 1.57079), 0x66CCFF, "Hello, world!"))->showAxis(100);

	class sphereFrame *sphere = new sphereFrame(0, point(0, 0, 0), 50, 0x66CCFF);
	class gString *str = new gString(0, point(-100, 80, 0), angle(0, 0, 0), 0x66CCFF, "Hello, world!", 4);
	(new sphereFrame(str, point(-10, 40, 0), 10, 0xFF0000))->showAxis(150);
	(new sphereFrame(str, point(-10, -8, 0), 10, 0x0000FF))->showAxis(150);
	class cubeFrame *cube;
	(new cubeFrame((new cubeFrame((new cubeFrame((cube = new cubeFrame((new cubeFrame((new cubeFrame(0, \
			point(10, 10, 10), point(-10, -10, -10), 0xFF0000))->showAxis(50), \
			point(10, 10, 10), point(-10, -10, -10), 0x00FF00))->showAxis(50), \
			point(10, 10, 10), point(-10, -10, -10), 0x0000FF))->showAxis(50), \
			point(10, 10, 10), point(-10, -10, -10), 0xFFFF00))->showAxis(50), \
			point(10, 10, 10), point(-10, -10, -10), 0x00FFFF))->showAxis(50), \
			point(10, 10, 10), point(-10, -10, -10), 0xFF00FF))->showAxis(50);
	gAxis->setTPoint(point(160, 120, -500));
	gAxis->showAxis(0);
	sphere->showAxis(150);
	str->showAxis(150);
	//int i = 0;
	while (true) {
		time_t timep;
		time(&timep);
		std::string time(ctime(&timep) + 11);
		time.resize(8);
		str->setString(time);
		gRoot->show();
		/*char path[std::char_traits<char>::length(PICS ".bmp") + 7];
		sprintf(path, PICS "%06d.bmp", i++);
		scr::scrCapture(path);*/
		tft.update();
		subAxis->setA(angle(subAxis->a().x() - 0.1, subAxis->a().y() - 0.1, subAxis->a().z() - 0.1));
		gAxis->setA(angle(0.5, gAxis->a().y() + 0.05, 0));
		str->setA(angle(str->a().x() + 0.05, 0, 0));
		cube->setA(angle(0, 0, cube->a().z() + 0.05));
		//cube->setColour(rand() % 0x1000000);
		//str->setColour(rand() % 0x1000000);
		sphere->setColour(rand() % 0x1000000);
		//gRoot->setColour(rand() % 0x1000000);
		//usleep(100);
	}
	gpio_close();
	return 0;
}
