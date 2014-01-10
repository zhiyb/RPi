#ifndef GPIO_H
#define GPIO_H

#include <stdio.h>
#include <stdlib.h>
#include <bcm2835.h>

#define RPI_V2_GPIO_P1_0	 RPI_V2_GPIO_P1_00
#define RPI_V2_GPIO_P1_1	 RPI_V2_GPIO_P1_01
#define RPI_V2_GPIO_P1_2	 RPI_V2_GPIO_P1_02
#define RPI_V2_GPIO_P1_3	 RPI_V2_GPIO_P1_03
#define RPI_V2_GPIO_P1_4	 RPI_V2_GPIO_P1_04
#define RPI_V2_GPIO_P1_5	 RPI_V2_GPIO_P1_05
#define RPI_V2_GPIO_P1_6	 RPI_V2_GPIO_P1_06
#define RPI_V2_GPIO_P1_7	 RPI_V2_GPIO_P1_07
#define RPI_V2_GPIO_P1_8	 RPI_V2_GPIO_P1_08
#define RPI_V2_GPIO_P1_9	 RPI_V2_GPIO_P1_09

#define PIN(pin)		RPI_V2_GPIO_P1_ ## pin

#define GPIO_PUD_UP(pin)	bcm2835_gpio_set_pud(pin, \
		BCM2835_GPIO_PUD_UP)
#define GPIO_PUD_DOWN(pin)	bcm2835_gpio_set_pud(pin, \
		BCM2835_GPIO_PUD_DOWN)
#define GPIO_PUD_OFF(pin)	bcm2835_gpio_set_pud(pin, \
		BCM2835_GPIO_PUD_OFF)

#define GPIO_INPUT(pin)		bcm2835_gpio_fsel(pin, \
		BCM2835_GPIO_FSEL_INPT)
#define GPIO_OUTPUT(pin)	bcm2835_gpio_fsel(pin, \
		BCM2835_GPIO_FSEL_OUTP)
#define GPIO_READ(pin)		bcm2835_gpio_lev(pin)
#define GPIO_SET(pin)		bcm2835_gpio_set(pin)
#define GPIO_CLR(pin)		bcm2835_gpio_clr(pin)
#define GPIO_WRITE(pin, e)	do \
	if (e) \
		GPIO_SET(pin); \
	else \
		GPIO_CLR(pin); \
while (0)

#define gpio_init() do \
	if (!bcm2835_init()) { \
		fputs("Initialise GPIO failed!", stderr); \
		exit(1); \
	} \
while (0)
#define gpio_close() bcm2835_close()

void gpio_reset(void);

#endif
