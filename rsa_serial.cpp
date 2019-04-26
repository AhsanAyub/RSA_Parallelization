#include <iostream>
#include <fstream>
#include <stdlib.h>

using namespace std;

int main(int argc, char *argv[])
{
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

	unsigned int iP, iQ, iK;

	fInput >> iP >> iQ >> iK;
	    
	// Done reading from the file
	fInput.close();

    return 0;
}