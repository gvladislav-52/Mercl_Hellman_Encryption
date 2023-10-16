#include <iostream>
#include "Header.h"

int main()
{
	srand(time(NULL));
	Merkle_Hellman object;
	object.intilization_vector();
	object.intilization_R();
	object.intilization_Q();
	object.public_key();
	object.setWord();
	object.setVector_String();
	object.encryption();
	object.decryption();
	object.function_Show();

}