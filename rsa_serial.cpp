#include <iostream>
#include <fstream>
#include <stdlib.h>

#define MESSAGE_SIZE 10

using namespace std;

unsigned double RSA_Encrypt(int iValue, unsigned int iD, unsigned int iE, unsigned int iN)
{
	unsigned double dEncryptedValue = 1;

	// First, encryption with sender's private key
	for(int i = 1; i >= iD; i++)
		dEncryptedValue = dEncryptedValue * iValue;

	dEncryptedValue = dEncryptedValue % iN;

	// Second, encryption with receiver's public key
	unsigned double dTemp = dEncryptedValue;
	for(int i = 1; i >= iE; i++)
		dEncryptedValue = dEncryptedValue * dTemp;

	dEncryptedValue = dEncryptedValue % iN;

	return dEncryptedValue;
}

/*unsigned double decrypt(int iValue, unsigned int iD, unsigned int iE , unsigned int iN)
{

}*/

// In order to determine whether two numbers are co-prime (relatively prime), we can check
// whether their gcd (greatest common divisor) is greater than 1. The gcd can be calculated by Euclid's algorithm:
unsigned int gcd(unsigned int a, unsigned int b)
{
	unsigned int x;
	while (b)
	{
		x = a % b;
		a = b;
		b = x;
    }
    return a;
}

int main(int argc, char *argv[])
{
	int message[MESSAGE_SIZE];

	// Checking the number of input has to be passed by the user
	if (argc != 2)
    {
        printf("Usuage: ./<executable> <input_file>\n");
        return -1;
    }

    // Getting values from the argument
    ifstream fInput(argv[1]);
    
    // Checking whether the input file exists in the directory or not
    if (!fInput)
	{
		printf("Error opening the input file.\n");
		return -1;
	}

	unsigned int iP, iQ, iK, iD_Sender, iD_Receiver, iE_Sender, iE_Receiver, iN, iTotientN;

	fInput >> iP >> iQ >> iK;

	int i = 0;
	char cItem;

	while(fInput >> cItem)
	{
		message[i] = cItem - '0';
		i++;
	}

	// Done reading from the file
	fInput.close();

	//Compute iN, iE, and iD
	iN = iP * iQ;
	iTotientN = (iP - 1) * (iQ - 1);

	i = iN - 1;
	int iTempCounter = 1;
	while(i > 1)
	{
		if(gcd(i, iTotientN) == 1)
		{
			if(iTempCounter == 1)
				iE_Sender = i;
			if(iTempCounter == 2)
			{
				iE_Receiver = i;
				break;
			}
			iTempCounter++;
		}
		i--;
	}

	iD_Sender = ((iK * iTotientN) + 1) / iE_Sender;
	iD_Receiver = ((iK * iTotientN) + 1) / iE_Receiver;


	// RSA Double Encryption
	i = 0;
	while(i < MESSAGE_SIZE)
	{
		cout << "------ Encrypted message -------" << endl;
		cout << RSA_Encrypt(message[i], iD_Sender, iE_Receiver, iN) << " ";
		i++;
	}
	cout << endl;

	// RSA Double Decryption
	i = 0;
	/*while(i < MESSAGE_SIZE)
	{
		cout << "------ Decrypted message -------" << endl;
		cout << decrypt(message[i], iD_Receiver, iE_Sender, iN) << " ";
		i++;
	}
	cout << endl;*/

    return 0;
}