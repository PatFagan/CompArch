// main.cpp
#include <iostream>
#include <fstream>
using namespace std;

int encrypt(int &currentDigit)
{
	currentDigit *= 2;
	return currentDigit;
}

int decrypt(int &currentDigit)
{
	currentDigit /= 2;
	__asm {
		mov eax, currentDigit
		inc eax
		mov currentDigit, eax
	}
	return currentDigit;
}

// main stub driver
int main()
{
	int code[4];
	ifstream fin;
	fin.open("input.txt");

	int index = 0;
	while (!fin.eof())
	{
		fin >> code[index];
		index++;
	}

	cout << "Initial Code" << endl;
	for (int i = 0; i < 4; i++)
	{
		cout << code[i];
	}
	cout << endl;

	cout << "Encrypted Code" << endl;
	for (int i = 0; i < 4; i++)
	{
		encrypt(code[i]);
		cout << code[i];
	}
	cout << endl;

	cout << "Decrypted Code" << endl;
	for (int i = 0; i < 4; i++)
	{
		decrypt(code[i]);
		cout << code[i];
	}
	cout << endl;

	return 0;
}