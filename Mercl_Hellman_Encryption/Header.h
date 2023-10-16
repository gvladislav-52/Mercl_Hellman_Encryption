#pragma once
#ifndef HEADER_H_
#define HEADER_H_
#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
#include <ctype.h>
#include <time.h>

class Merkle_Hellman
{
private:
	std::vector<int> vector_first;
	std::vector<int> vector_second;
	int q;
	int r;
	int r_shtix;
	std::vector<std::string> vec_str;
	std::vector<int> vector_encryption;
	std::vector<std::string> dec_vec;
	std::string word;
	int gcdExtended(int a, int b, int& x, int& y);
	bool is_prime(int n);
	std::string to_binary(int decimal);
	int multiplicativeInverse(int a, int m);
	std::string getWord();
public:
	void setWord();
	void setVector_String();
	void intilization_vector();
	int intilization_Q();
	int intilization_R();
	void public_key();
	void encryption();
	void decryption();
	void Function_Debu();
};
#endif // !HEADER_H_
