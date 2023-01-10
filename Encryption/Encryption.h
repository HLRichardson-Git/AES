#pragma once

#include "KeySchedule.h"
#include "helper.h"

class Encryption
{
public:

	unsigned char cipherText[4][4];

	void run();

private:

	KeySchedule key;
	Help help;
	bool debug = 1; // BOOL DEBUG ACTIVE

	void subByte();
	void shiftRows();
	void mixColumns();
	void addRoundKey(int round);

	void initializeCipherText();

};
