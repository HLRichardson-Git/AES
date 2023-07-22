#include <iostream>
#include <iomanip>
#include "helper.h"

using namespace std;

void printResult(unsigned char array[4][4])
{

    for (int x = 0; x < 4; x++)
    {
        for (int y = 0; y < 4; y++)
        {
            cout << hex << setfill('0') << setw(2) << int(array[y][x]);
        }
    }

}

void print2dArray(unsigned char array[4][4])
{
    for (int x = 0; x < 4; x++)
    {
        for (int y = 0; y < 4; y++)
        {
            cout << " K:" << x << "," << y << " " << hex << setfill('0') << setw(2) << int(array[x][y]) << " |";
        }
        cout << endl;
    }
}

void print3dArray(unsigned char array[4][4][11])
{
    for (int z = 0; z < 11; z++)
    {
        cout << "\n------------------Round: " << z << "------------------" << endl;
        for (int x = 0; x < 4; x++)
        {
            for (int y = 0; y < 4; y++)
            {
                cout << " K:" << x << "," << y << " " << hex << setfill('0') << setw(2) << int(array[x][y][z]) << " |";
            }
            cout << endl;
        }
        cout << "--------------------------------------------" << endl;
    }
}

unsigned char multiplyBy2(unsigned char element)
{

	unsigned char constant = ((element & 0x80) == 0x80) ? 0x1b : 0x00;
	return (element << 1) ^ constant;

}
