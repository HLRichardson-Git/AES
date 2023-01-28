#pragma once

#include "helper.h"

class KeySchedule
{
public:

	unsigned char roundKey[4][4][11];

	void run();

	void rotWord(unsigned char temp[4], int round);
	void subWord(unsigned char temp[4], int round);
	void rcon(unsigned char temp[4], int round);

private:
	Help help;
	unsigned char key[4][4] = { {0x10, 0xd7, 0x74, 0xfb},
								{0xa5, 0x4b, 0xcf, 0x47},
								{0x88, 0xe5, 0x86, 0x38},
								{0x69, 0xa3, 0x7c, 0x59} };

	unsigned char RCon[10] = { 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1B, 0x36 };

};
