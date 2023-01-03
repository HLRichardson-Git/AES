
#include <iostream>
#include <iomanip>

#include "Encryption.h"

using namespace std;

void Encryption::run()
{

	initializeCipherText();
	key.run();
	print3dArray(key.roundKey);
	int round = 0;

	print2dArray(cipherText);
	for (int x = 0; x < 4; x++)
	{
		for (int y = 0; y < 4; y++)
		{
			cipherText[x][y] = cipherText[x][y] ^ key.roundKey[x][y][0];
		}
	}
	round++;
	print2dArray(cipherText);
	while (round < 10)
	{

		cout << "=== ENCRYPTION ROUND: " << round << " ===" << endl;
		cout << "SubByte" << endl;
		subByte();
		print2dArray(cipherText);

		cout << "ShiftRows" << endl;
		shiftRows();
		print2dArray(cipherText);

		cout << "MixColumns" << endl;
		mixColumns();
		print2dArray(cipherText);

		cout << "AddRoundKey" << endl;
		addRoundKey(round);
		print2dArray(cipherText);
		round++;

	}

	cout << "=== ENCRYPTION ROUND: " << round << " ===" << endl;
	cout << "SubByte" << endl;
	subByte();
	print2dArray(cipherText);

	cout << "ShiftRows" << endl;
	shiftRows();
	print2dArray(cipherText);

	cout << "AddRoundKey" << endl;
	addRoundKey(round);
	print2dArray(cipherText);

}

void Encryption::subByte()
{

	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			cipherText[x][y] = help.sBox[cipherText[x][y]];
		}
	}

}

void Encryption::shiftRows()
{

	int shift = 1;

	for (int x = 1; x < 4; x++)
	{
		int index = 1;

		while (index <= shift)
		{
			unsigned char first = cipherText[x][0];

			for (int y = 0; y < 3; y++)
				cipherText[x][y] = cipherText[x][y + 1];

			index++;
			cipherText[x][3] = first;
		}

		shift++;

	}

}

void Encryption::mixColumns()
{

	unsigned char temp[4] = { 0x00,0x00,0x00,0x00 };

	unsigned char newState[4][4] = { {0,0,0,0},
									 {0,0,0,0},
									 {0,0,0,0},
									 {0,0,0,0} };

	int rijndaelMatric[4][4] = { {2,3,1,1},
								 {1,2,3,1},
								 {1,1,2,3},
								 {3,1,1,2} };

	for (int y = 0; y < 4; y++)
	{
		int z = 0;
		for (int i = 0; i < 4; i++)
		{
			temp[i] = 0x00;
		}
		for (int x = 0; x < 4; x++)
		{
			for (int j = 0; j < 4; j++)
			{
				unsigned char constant = 0x00;
				unsigned char element = 0x00;
				switch (rijndaelMatric[z][j])
				{
				case 1:
					temp[j] = cipherText[j][y];
					break;
				case 2:
					element = cipherText[j][y];
					temp[j] = multiplyBy2(element);
					break;
				case 3:
					element = cipherText[j][y];
					temp[j] = multiplyBy2(element) ^ element;
					break;
				}

			}
			newState[x][y] = int(temp[0]) ^ int(temp[1]) ^ int(temp[2]) ^ int(temp[3]);
			z++;
		}

	}

	for (int x = 0; x < 4; x++)
	{
		for (int y = 0; y < 4; y++)
		{
			cipherText[x][y] = newState[x][y];
		}
	}

}

void Encryption::addRoundKey(int round)
{

	for (int x = 0; x < 4; x++)
	{
		for (int y = 0; y < 4; y++)
		{
			cipherText[x][y] = cipherText[x][y] ^ key.roundKey[x][y][round];
		}
	}

}

void Encryption::initializeCipherText()
{
	switch (debug)
	{
	case 0:

		break;
	case 1:
		for (int x = 0; x < 4; x++)
		{
			for (int y = 0; y < 4; y++)
			{
				cipherText[x][y] = 0x00;
			}
		}
		break;
	}
}
