#include "Header.h"

std::string Merkle_Hellman::to_binary(int decimal)
{
	std::string binary = "";
	while (decimal > 0)
	{
		binary = std::to_string(decimal % 2) + binary;
		decimal /= 2;
	}
	return binary;
}
bool Merkle_Hellman::is_prime(int n)
{
	if (n <= 1)
		return false;
	for (int i = 2; i * i <= n; i++)
		if (n % i == 0)
			return false;
	return true;
}
void Merkle_Hellman::intilization_vector()
{
	for (int i = 0; i < 8; i++)
		vector_first.push_back(pow(2, i));
}
int Merkle_Hellman::intilization_Q()
{
	 q = rand() % 100 + vector_first.back();
	 return q;
}
int Merkle_Hellman::intilization_R()
{
	r = rand() % 100 + 1;
	while (!is_prime(r))
		r = rand() % 100 + 1;
	return r;
}

void Merkle_Hellman::setWord()
{
	std::getline(std::cin, word);
}

std::string Merkle_Hellman::getWord()
{
	return word;
}

void Merkle_Hellman::setVector_String()
{
	for (int i = 0; i < getWord().length(); i++)
		vec_str.push_back(to_binary(word[i]));
}


void Merkle_Hellman::public_key ()
{
	for (auto c : vector_first)
		vector_second.push_back(c * r % q);
}

void Merkle_Hellman::encryption()
{
	for (const auto& str : vec_str)
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

void Merkle_Hellman::decryption()
{
	int r_shtix = multiplicative_Inverse(r, q); 
	std::sort(rbegin(vector_first), rend(vector_first));

	std::vector<int>temp;
	for (auto i : vector_encryption)
		temp.push_back(i * r_shtix % q);

	for (int i = 0; i < temp.size(); i++)
	{
		std::string index = "";
		while (temp[i] != 0)
		{
			for (int c = 0; c < vector_first.size(); c++)
			{
				if (c == 0)
					continue;
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
	binaryToDecimal(dec_vec);
}

int Merkle_Hellman::gcd_Extended(int a, int b, int& x, int& y) {
	if (a == 0) {
		x = 0;
		y = 1;
		return b;
	}
	int x1, y1;
	int gcd = gcd_Extended(b % a, a, x1, y1);
	x = y1 - (b / a) * x1;
	y = x1;
	return gcd;
}

int Merkle_Hellman::multiplicative_Inverse(int a, int m) {
	int x, y;
	int gcd = gcd_Extended(a, m, x, y);
	if (gcd != 1) {
		return -1; 
	}
	else {
		return (x % m + m) % m;
	}
}

void Merkle_Hellman::binaryToDecimal(const std::vector<std::string>& binaryValues)
{
	for (const auto& binary : binaryValues)
	{
		int decimal = 0;
		int base = 1;

		for (int i = binary.size() - 1; i >= 0; --i)
		{
			if (binary[i] == '1')
			{
				decimal += base;
			}
			base *= 2;
		}

		decimalValues.push_back(decimal);
	}

}

void Merkle_Hellman::function_Show()
{
	using std::cout;
	using std::endl;
	cout << "Q:\t" << q << endl;
	cout << "R:\t" << r << endl;
	cout << "R':\t" << r_shtix << endl;
	//cout << "Word:\t";
	//char k = word[0];
	//cout << (int)k << endl;
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
	cout << "\nBin string:\t";
	for (auto c : dec_vec)
		cout << c << " ";
	cout << "\nDecryption:\t";
	cout << decimalValues.size() << endl;
	for (auto c : decimalValues)
		std::cout << (char)c << " ";
}