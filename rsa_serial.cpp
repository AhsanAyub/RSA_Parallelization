#include <iostream>
#include <fstream>
#include <stdlib.h>

#define MESSAGE_SIZE 10

using namespace std;

unsigned int RSA(int iValue, unsigned int iKey, unsigned int iModulus)
{
	unsigned int iComputeddValue = 1;

	cout << " | " << iComputeddValue << " | " << iValue << " | " << iKey << " | " << endl;
	
	// Encryption with E or
	// Decryption with D
	for(int i = 1; i <= iKey; i++)
	{
		iComputeddValue = iComputeddValue * iValue;
		cout << iComputeddValue << endl;
	}

	cout << " | " << iComputeddValue << " | " << iValue << " | " << iKey << " | ";
	
	iComputeddValue = iComputeddValue % iModulus;

	return iComputeddValue;
}

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
	int encryptedMessage[MESSAGE_SIZE];

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

	unsigned int iP, iQ, iD, iE, iN, iTotientN;

	fInput >> iP >> iQ;

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

	iE = iN / 2;
	while(i < (iN - 1))
	{
		if(gcd(iE, iTotientN) == 1)
			break;
			
		iE++;
	}

	cout << pow(9,7)<< endl;

	// RSA Double Encryption
	i = 0;
	cout << "E: " << iE << endl;
	cout << "N: " << iN << endl;
	cout << "------ Encrypted message -------" << endl;
	while(i < 1)
	{
		encryptedMessage[i] = RSA(message[i], 7, iN);
		cout << encryptedMessage[i]  << ' ';
		i++;
	}
	cout << endl;

	// RSA Double Decryption
	i = 0;
	cout << "D: " << iD << endl;
	cout << "N: " << iN << endl;
	cout << "------ Decrypted message -------" << endl;
	while(i < 1)
	{
		cout << RSA(encryptedMessage[i], 11, iN) << " ";
		i++;
	}
	cout << endl;

    return 0;
}