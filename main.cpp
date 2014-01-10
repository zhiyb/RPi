#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <inttypes.h>
#include <TFT/tft.h>
#include <TFT/conv.h>
#include <Graphic/cubeframe.h>

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

	new cubeFrame(0, point(), point(50, 0, 0), point(0, 50, 0), point(0, 0, 50), 0x00FFFF);
	new cubeFrame(0, point(), point(-50, 0, 0), point(0, -50, 0), point(0, 0, -50), 0xFFFF00);
	new cubeFrame(0, point(-10, -10, -10), point(-10, -40, -10), point(-40, -10, -10), point(-10, -10, -40), 0x7F7F00);
	new cubeFrame(0, point(-20, -20, -20), point(-20, -30, -20), point(-30, -20, -20), point(-20, -20, -30), 0x3F3F00);
	new cubeFrame(0, point(-10, 10, -10), point(-10, 40, -10), point(-40, 10, -10), point(-10, 10, -40), 0x007F7F);
	new cubeFrame(0, point(-20, 20, -20), point(-20, 30, -20), point(-30, 20, -20), point(-20, 20, -30), 0x003F3F);
	new cubeFrame(0, point(50, 0, 0), point(80, 0, 0), point(50, 0, -30), point(50, -30, 0), 0xFF00FF);
	new cubeFrame(0, point(), point(20, 10, -10), point(10, -20, -10), point(10, 10, -20), 0xFFFFFF);
	new line(0, point(), point(100, 100, 100), 0xFFFFFF);
	new line(0, point(), point(100, 100, -100), 0x7F0000);
	new line(0, point(), point(100, -100, 100), 0x007F00);
	new line(0, point(), point(-100, 100, 100), 0x00007F);
	new line(0, point(), point(100, -100, -100), 0x7F7F00);
	new line(0, point(), point(-100, 100, -100), 0x007F7F);
	new line(0, point(), point(-100, -100, 100), 0x7F7F00);
	new line(0, point(), point(-100, -100, -100), 0x7F7F7F);
	scrAxis->setP(point(160, 120, -200));
	scrAxis->setA(angle(0.3, 0, 0));
	scrAxis->showAxis(true);
	while (true) {
		scrAxis->show();
		tft.update();
		scrAxis->setA(angle(0.3, scrAxis->a().y() + 0.01, 0));
		//usleep(100);
	}
	gpio_close();
	return 0;
}
