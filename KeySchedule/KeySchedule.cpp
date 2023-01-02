#include "KeySchedule.h"


void KeySchedule::run()
{

    int round = 0;

    while (round < 10)
    {
        if (round == 0)
        {
            for (int x = 0; x < 4; x++)
            {
                for (int y = 0; y < 4; y++)
                {
                    roundKey[x][y][0] = key[x][y];
                    //roundKey[x][y][0] = 0x00;
                }
            }
        }

        unsigned char temp[4] = { 0x00, 0x00, 0x00, 0x00 };

        if (round == 0)
        {
            temp[0] = roundKey[0][3][0];
            temp[1] = roundKey[1][3][0];
            temp[2] = roundKey[2][3][0];
            temp[3] = roundKey[3][3][0];
        }
        else
        {
            temp[0] = roundKey[0][3][round];
            temp[1] = roundKey[1][3][round];
            temp[2] = roundKey[2][3][round];
            temp[3] = roundKey[3][3][round];
        }

        rotWord(temp, round);
        subWord(temp, round);
        rcon(temp, round);

        round++;

        for (int x = 0; x < 4; x++)
        {
            roundKey[x][0][round] = temp[x] ^ roundKey[x][0][round - 1];
        }

        for (int y = 1; y < 4; y++)
        {
            for (int x = 0; x < 4; x++)
            {
                roundKey[x][y][round] = roundKey[x][y][round - 1] ^ roundKey[x][y - 1][round];
            }
        }
    }


}

void KeySchedule::rotWord(unsigned char temp[4], int round)
{

    unsigned char temp2 = temp[0];
    for (int x = 0; x < 4; x++)
    {
        temp[x] = temp[x + 1];
    }
    temp[3] = temp2;

}

void KeySchedule::subWord(unsigned char temp[4], int round)
{

    for (int x = 0; x < 4; x++)
    {
        temp[x] = help.sBox[temp[x]];
    }

}

void KeySchedule::rcon(unsigned char temp[4], int round)
{

    temp[0] = temp[0] ^ RCon[round];

}
