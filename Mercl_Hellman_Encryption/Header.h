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
	int gcd_Extended(int a, int b, int& x, int& y);
	bool is_prime(int n);
	std::string to_binary(int decimal);
	int multiplicative_Inverse(int a, int m);
	std::string getWord();
	std::vector<int> decimalValues;
public:
	void setWord();
	void setVector_String();
	void intilization_vector();
	int intilization_Q();
	int intilization_R();
	void public_key();
	void encryption();
	void decryption();
	void function_Show();
	void binaryToDecimal(const std::vector<std::string>& binaryValues);
};
#endif // !HEADER_H_
