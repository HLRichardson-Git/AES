
#include <iostream>
#include <iomanip>

#include "helper.h"
#include "KeySchedule.h"
#include "Encryption.h"
#include "Decryption.h"

using namespace std;

int main()
{

    Encryption encrypt;
    Decryption decrypt;
    KeySchedule key;

    encrypt.run();
    decrypt.run();

    printResult(encrypt.cipherText);
    cout << endl;
    printResult(decrypt.plainText);
    
}


