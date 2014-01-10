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

	new cubeFrame(0, point(5, 5, 5), point(45, 45, 45), 0x7F7F7F);
	new cubeFrame(0, point(5, -5, 5), point(45, -45, 45), 0xFF0000);
	new cubeFrame(0, point(-5, 5, 5), point(-45, 45, 45), 0x00FF00);
	new cubeFrame(0, point(5, 5, -5), point(45, 45, -45), 0x0000FF);
	new cubeFrame(0, point(-5, -5, 5), point(-45, -45, 45), 0xFF00FF);
	new cubeFrame(0, point(5, -5, -5), point(45, -45, -45), 0x00FFFF);
	new cubeFrame(0, point(-5, 5, -5), point(-45, 45, -45), 0xFFFF00);
	new cubeFrame(0, point(-5, -5, -5), point(-45, -45, -45), 0xFFFFFF);
	scrAxis->setP(point(160, 120, -200));
	scrAxis->setA(angle(0.5, 0, 0));
	scrAxis->showAxis(true);
	while (true) {
		scrAxis->show();
		tft.update();
		scrAxis->setA(angle(0.5, scrAxis->a().y() + 0.1, 0));
		//usleep(100);
	}
	gpio_close();
	return 0;
}
