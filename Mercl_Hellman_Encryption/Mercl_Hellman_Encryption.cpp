#include <iostream>
#include <vector>
#include <ctype.h>
#include <time.h>
#include <string>
#include <algorithm>

using namespace std;

string to_binary(int decimal) 
{
	string binary = "";
	while (decimal > 0) 
	{
		binary = to_string(decimal % 2) + binary;
		decimal /= 2;
	}
	//while (binary.length() < 7)
	//	binary = "0" + binary;
	return binary;
}
bool is_prime(int n) 
{
	if (n <= 1) 
		return false;
	for (int i = 2; i * i <= n; i++)
		if (n % i == 0)
			return false;
	return true;
}
void intilization_vector(vector<int> &temp_key)
{
	for (int i = 0; i < 8; i++) 
		temp_key.push_back(pow(2,i));
}
int intilization_Q(const vector<int>&temp_key)
{
	int q = rand() % 100 + temp_key.back();
	return q;
}
int intilization_R()
{
	int num = rand() % 100 + 1; 
	while (!is_prime(num))
		num = rand() % 100 + 1; 
	return num;
}
void public_key(const vector<int>& old_key,vector<int>& new_key,int &r,int &q)
{	
	for (auto c : old_key)
		new_key.push_back(c*r%q);
}

void encryption(vector<int> &vector_encryption, vector<string>&vector_str, const vector<int> &vector_second,string &word)
{
	for (const auto& str : vector_str)
	{
		int sum = 0;
		for (int i = 0; i < str.length(); i++)
		{
			if (str[i] == '1')
			{
				sum += vector_second[i];
			}
		}
		vector_encryption.push_back(sum);
	}
}

void decryption(vector<int>&vector_first,vector<int>& vector_encryption,int &q,int &r_shtix)
{
	sort(rbegin(vector_first), rend(vector_first));

	vector<int>temp;
	for(auto i: vector_encryption)
		temp.push_back(i * r_shtix % q);
	cout << "Mode: ";
	for (auto c : temp)
		cout << c << " ";
	cout << "\nBin string: ";
	vector<string> dec_vec;
	for (int i = 0; i < temp.size(); i++)
	{
		string index = "";
		while (temp[i] != 0)
		{
			for(int c = 0; c < vector_first.size(); c++)
			{
				if (c == 0)
					continue;
				//if (temp[i] == 0)
				//	break;
				//else
					if (temp[i] < vector_first[c])
					{
						index += "0";
						continue;
					}
					else
					{
						index += "1";
						temp[i] -= vector_first[c];
					}
			}
		}
		reverse(index.begin(), index.end());
		dec_vec.push_back(index);
	}
	for (auto c : dec_vec)
		cout << c << " ";
}

int gcdExtended(int a, int b, int& x, int& y) {
	if (a == 0) {
		x = 0;
		y = 1;
		return b;
	}
	int x1, y1;
	int gcd = gcdExtended(b % a, a, x1, y1);
	x = y1 - (b / a) * x1;
	y = x1;
	return gcd;
}

int multiplicativeInverse(int a, int m) {
	int x, y;
	int gcd = gcdExtended(a, m, x, y);
	if (gcd != 1) {
		return -1; // обратного элемента не существует
	}
	else {
		return (x % m + m) % m; // мультипликативное обратное равно x (mod m)
	}
}

int main()
{
	srand(time(NULL));
	vector<int> vector_first;
	vector<int> vector_second;
	intilization_vector(vector_first);
	int q = intilization_Q(vector_first);
	int r = intilization_R();
	int r_shtix = multiplicativeInverse(r, q);
	public_key(vector_first, vector_second,r,q);
	string word;
	getline(cin, word);

	vector<string> vec_str;
	for (int i = 0; i < word.length(); i++)
		vec_str.push_back(to_binary(word[i]));
	vector<int> vector_encryption;
	encryption(vector_encryption, vec_str, vector_second, word);
	cout << "Q:\t" << q << endl;
	cout << "R:\t" << r << endl;
	cout << "R':\t" << r_shtix << endl;
	cout << "Vector_first:\t";
	for (auto c : vector_first)
	cout << c << " ";
	cout << "\nVector_second:\t";
	for (auto c : vector_second)
		cout << c << " ";
	cout << endl;
	cout << "Word:\t\t";
	for (auto c : vec_str)
		cout << c << " ";
	cout << endl;
	cout << "Encryption:\t";
	for (auto c : vector_encryption)
		cout << c << " ";
	cout << endl;
	decryption(vector_first, vector_encryption,q, r_shtix);
}