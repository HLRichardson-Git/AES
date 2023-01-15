#pragma once

#include "KeySchedule.h"
#include "helper.h"

class Decryption
{
public:

	unsigned char plainText[4][4];

	void run();

private:

	KeySchedule key;
	Help help;
	bool debug = 1; // BOOL DEBUG ACTIVE
	unsigned char nist[4][4] = { {0x6d, 0x25, 0x1e, 0x69},
								 {0x44, 0xb0, 0x51, 0xe0},
								 {0x4e, 0xaa, 0x6f, 0xb4},
								 {0xdb, 0xf7, 0x84, 0x65} };

	void invSubByte();
	void invShiftRows();
	void invMixColumns();
	void invAddRoundKey(int round);

	void initializePlainText();

};
