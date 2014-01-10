#ifndef __SCRBUFF_H
#define __SCRBUFF_H

#include <inttypes.h>

#define SCRW	320
#define SCRH	240

struct scrBuffStruct {
	uint32_t colour;
	float deep;
};

extern scrBuffStruct scrBuff[SCRW][SCRH];

static inline void scrBuffClean(void)
{
	for (int x = 0; x < SCRW; x++)
		for (int y = 0; y < SCRH; y++) {
			scrBuff[x][y].deep = 1;
			scrBuff[x][y].colour = 0;
		}
}

#endif
