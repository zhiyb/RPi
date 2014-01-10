#include "scrbuff.h"
#include <iostream>
#include <fstream>

struct scrBuffStruct scrBuff[SCRW][SCRH];

const char *header = "\x42\x4D\x36\x84\x03\x00\x00\x00\x00\x00\x36\x00\x00\x00\x28\x00\x00\x00\x40\x01\x00\x00\xF0\x00\x00\x00\x01\x00\x18\x00\x00\x00\x00\x00\x00\x84\x03\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00";

using namespace std;

void scrCapture(const char *path)
{
	ofstream file(path, ios::out | ios::binary);
	if (!file.is_open()) {
		std::cerr << "Error openning file " << path << std::endl;
		return;
	}
	file.write(header, 54);
	for (int y = 0; y < SCRH; y++)
		for (int x = 0; x < SCRW; x++) {
			file.put((scrBuff[x][y].colour >> 0) & 0xFF);
			file.put((scrBuff[x][y].colour >> 8) & 0xFF);
			file.put((scrBuff[x][y].colour >> 16) & 0xFF);
		}
	file.close();
}
