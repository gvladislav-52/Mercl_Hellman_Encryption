#include <iostream>
#include <vector>
#include <ctype.h>
#include <time.h>
#include <string>

using namespace std;

string to_binary(int decimal) 
{
	string binary = "";
	while (decimal > 0) 
	{
		binary = to_string(decimal % 2) + binary;
		decimal /= 2;
	}
	while (binary.length() < 7)
		binary = "0" + binary;
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

void encryption(vector<int> &vector_encryption, string** matrix, const vector<int> &vector_second,string &word)
{
	int sum = 0;

	for (int i = 0; i < word.length(); i++)
	{
		for (int j = 0; j < 8; j++) {
			if (stoi(matrix[i][j]) == 1)
			{
				sum += vector_second[i];
			}
			vector_encryption.push_back(sum);
		}
	}
}

string** create_matrix(string row,int col)
{
	string** matrix = new string * [stoi(row)];
	for (int i = 0; i < stoi(row); i++)
		matrix[i] = new string[col];
	return matrix;
}

void fill_matrix(string** matrix, string row, int col)
{
	for (int i = 0; i < row.length(); i++)
	{
		for (int j = 0; j < 8; j++)
		{
			matrix[i][j] = to_binary(row[j]);
		}
	}
}

void deleteMatrix(string** matrix, string row) {
	for (int i = 0; i < row.length(); i++) {
		delete[] matrix[i];
	}
	delete[] matrix;
}

int main()
{
	srand(time(NULL));
	vector<int> vector_first;
	vector<int> vector_second;
	intilization_vector(vector_first);
	int q = intilization_Q(vector_first);
	int r = intilization_R();
	public_key(vector_first, vector_second,r,q);
	string word;
	getline(cin, word);

	string** matrix = create_matrix(word, 8);
	fill_matrix(matrix, word, 8);
	vector<int> vector_encryption;
	encryption(vector_encryption, matrix, vector_second, word);
	cout << "Q: " << q << endl;
	cout << "R: " << r << endl;
	cout << "Vector_first: ";
	for (auto c : vector_first)
	cout << c << " ";
	cout << "\nVector_second: ";
	for (auto c : vector_second)
		cout << c << " ";
	cout << endl;
	cout << "Word:\n";
	for (auto c : vector_encryption)
		cout << c << " ";
	cout << endl;
	deleteMatrix(matrix, word);
}