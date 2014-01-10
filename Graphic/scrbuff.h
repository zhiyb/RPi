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

void scrCapture(const char *path);

#endif
