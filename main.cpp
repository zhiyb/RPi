#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <inttypes.h>
#include <TFT/tft.h>
#include <TFT/conv.h>
#include <Graphic/shapes.h>
#include <time.h>
#include <pthread.h>

//#define CAPTURE
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

	class object *subAxis = new object(0, point(0, -60, -60), angle());
	(new cubeFrame(subAxis, point(5, 5, 5), point(20, 20, 20), 0x7F7F7F));//->showAxis(100);
	(new cubeFrame(subAxis, point(5, -5, 5), point(20, -20, 20), 0xFF0000));//->showAxis(100);
	(new cubeFrame(subAxis, point(-5, 5, 5), point(-20, 20, 20), 0x00FF00));//->showAxis(100);
	(new cubeFrame(subAxis, point(5, 5, -5), point(20, 20, -20), 0x0000FF));//->showAxis(100);
	(new cubeFrame(subAxis, point(-5, -5, 5), point(-20, -20, 20), 0xFF00FF));//->showAxis(100);
	(new cubeFrame(subAxis, point(5, -5, -5), point(20, -20, -20), 0x00FFFF));//->showAxis(100);
	(new cubeFrame(subAxis, point(-5, 5, -5), point(-20, 20, -20), 0xFFFF00));//->showAxis(100);
	(new cubeFrame(subAxis, point(-5, -5, -5), point(-20, -20, -20), 0xFFFFFF));//->showAxis(100);
	(new cubeFrame(subAxis, point(30, 30, 30), point(-60, -60, -60), 0x3F3F3F));//->showAxis(100);
	(new gString(subAxis, point(0, 30, 0), angle(0, 0, 1.57079), 0x66CCFF, "Hello, world!"));//->showAxis(100);

	class gString *str = new gString(0, point(-94), angle(), 0x66CCFF, "Hello, world!", 4);
	class sphereFrame *sph = new sphereFrame(str, point(-20, 40, 0), 30, 0x66CCFF);
	//(new sphereFrame(str, point(-20, 40, 0), 20, 0xFF0000))->showAxis(150);
	//(new sphereFrame(str, point(-20, -8, 0), 20, 0x0000FF));
	//(new circle(str, point(210, -8, 0), angle(), 20, false, 0xFFFF00));
	new sphereFrame(new sphere(str, point(210, 40, 0), 30, 0x00FF00), point(), 20, 0xFF0000);
	class cubeFrame *cube;
	(new cubeFrame((new cubeFrame((cube = new cubeFrame((new cubeFrame((new cubeFrame((new cubeFrame(sph, \
			point(10, 10, 10), point(-10, -10, -10), 0xFF0000))/*->showAxis(50)*/, \
			point(10, 10, 10), point(-10, -10, -10), 0x00FF00))/*->showAxis(50)*/, \
			point(10, 10, 10), point(-10, -10, -10), 0x0000FF))/*->showAxis(50)*/, \
			point(10, 10, 10), point(-10, -10, -10), 0xFFFF00))/*->showAxis(50)*/, \
			point(10, 10, 10), point(-10, -10, -10), 0x00FFFF))/*->showAxis(50)*/, \
			point(10, 10, 10), point(-10, -10, -10), 0xFF00FF))/*->showAxis(50)*/;
	gAxis->set(point(160, 120, -100), angle(0.5));
	gAxis->showAxis(0);
	sph->showAxis(150);
	str->showAxis(150);
#ifdef CAPTURE
	int i = 0;
#endif
	time_t timep;
	time(&timep);
	std::string tstr(ctime(&timep) + 11);
	tstr.resize(8);
	str->setString(tstr);
	gRoot->show();
	pthread_t pid;
	pthread_create(&pid, NULL, tftUpdateThread, NULL);
	while (true) {
		gRoot->show();
#ifdef CAPTURE
		char path[std::char_traits<char>::length(PICS ".bmp") + 7];
		sprintf(path, PICS "%06d.bmp", i++);
		scr::scrCapture(path);
#endif
		time_t timep;
		time(&timep);
		tstr = ctime(&timep) + 11;
		tstr.resize(8);
		str->setString(tstr);
		gAxis->setA(angle(0.5, gAxis->a().y() + 0.05, 0));
		if (gAxis->a().y() > 2 * PI)
			gAxis->setA(0.5);
		subAxis->setA(angle(subAxis->a().x() + 0.1, subAxis->a().y() + 0.1, subAxis->a().z() + 0.1));
		if (subAxis->a().x() > 4 * PI)
			subAxis->setA();
		str->setA(angle(str->a().x() + 0.05, 0, 0));
		if (str->a().x() > 2 * PI)
			str->setA();
		if (cube != NULL) {
			cube->setA(angle(0, 0, cube->a().z() + 0.05));
			if (cube->a().z() > 4 * PI) {
				//cube->setA();
				delete cube;
				cube = NULL;
			}
		}
		//cube->setColour(rand() % 0x1000000);
		//str->setColour(rand() % 0x1000000);
		sph->setColour(rand() % 0x1000000);
		//gRoot->setColour(rand() % 0x1000000);
		usleep(1000);
	}
	pthread_detach(pid);
	gpio_close();
	return 0;
}
