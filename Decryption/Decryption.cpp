
#include <iostream>
#include <iomanip>

#include "Decryption.h"

using namespace std;

void Decryption::run()
{

    int round = 10;

    initializePlainText();
    key.run();
    print2dArray(plainText);
    cout << "=== DECRYPTION ROUND: " << round << " ===" << endl;
    cout << "Inverse AddRoundKey" << endl;
    invAddRoundKey(round);
    print2dArray(plainText);

    cout << "Inverse ShiftRows" << endl;
    invShiftRows();
    print2dArray(plainText);

    cout << "Inverse SubByte" << endl;
    invSubByte();
    print2dArray(plainText);

    round--;

    while (round > 0)
    {
        cout << "=== DECRYPTION ROUND: " << round << " ===" << endl;
        cout << "Inverse AddRoundKey" << endl;
        invAddRoundKey(round);
        print2dArray(plainText);

        cout << "Inverse MixColumns" << endl;
        invMixColumns();
        print2dArray(plainText);

        cout << "Inverse ShiftRows" << endl;
        invShiftRows();
        print2dArray(plainText);

        cout << "Inverse SubByte" << endl;
        invSubByte();
        print2dArray(plainText);

        round--;

    }

    cout << "=== DECRYPTION ROUND: " << round << " ===" << endl;
    cout << "Inverse AddRoundKey" << endl;
    invAddRoundKey(round);
    print2dArray(plainText);


}

void Decryption::invSubByte()
{

    for (int y = 0; y < 4; y++)
    {
        for (int x = 0; x < 4; x++)
        {
            plainText[x][y] = help.InvsBox[plainText[x][y]];
        }
    }

}

void Decryption::invShiftRows()
{

    int shift = 1;

    for (int x = 1; x < 4; x++)
    {
        int index = 1;

        while (index <= shift)
        {
            unsigned char last = plainText[x][3];

            for (int y = 3; y > 0; y--)
                plainText[x][y] = plainText[x][y - 1];

            index++;
            plainText[x][0] = last;
        }

        shift++;

    }

}

void Decryption::invMixColumns()
{

    unsigned char temp[4] = { 0x00,0x00,0x00,0x00 };

    unsigned char newState[4][4] = { {0,0,0,0},
                                     {0,0,0,0},
                                     {0,0,0,0},
                                     {0,0,0,0} };

    int rijndaelMatric[4][4] = { {14,11,13,9},
                                 {9,14,11,13},
                                 {13,9,14,11},
                                 {11,13,9,14} };

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
                case 9:
                    element = plainText[j][y];
                    temp[j] = (multiplyBy2(multiplyBy2(multiplyBy2(element)))) ^ element;
                    break;
                case 11:
                    element = plainText[j][y];
                    temp[j] = (multiplyBy2(multiplyBy2(multiplyBy2(element)) ^ element)) ^ element;
                    break;
                case 13:
                    element = plainText[j][y];
                    temp[j] = multiplyBy2(multiplyBy2(multiplyBy2(element) ^ element)) ^ element;
                    break;
                case 14:
                    element = plainText[j][y];
                    temp[j] = multiplyBy2((multiplyBy2(multiplyBy2(element) ^ element)) ^ element);
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
            plainText[x][y] = newState[x][y];
        }
    }

}

void Decryption::invAddRoundKey(int round)
{

    for (int x = 0; x < 4; x++)
    {
        for (int y = 0; y < 4; y++)
        {
            plainText[x][y] = plainText[x][y] ^ key.roundKey[x][y][round];
        }
    }

}

void Decryption::initializePlainText()
{

	switch (debug)
	{
	case 0:

		break;
	case 1:
		for (int y = 0; y < 4; y++)
		{
			for (int x = 0; x < 4; x++)
			{
				plainText[x][y] = nist[y][x];
			}
		}
		break;
	}

}
