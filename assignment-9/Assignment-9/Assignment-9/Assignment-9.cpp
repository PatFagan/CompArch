// main.cpp
#include <iostream>
#include <fstream>
using namespace std;

int encrypt(int &passedDigit)
{
	int newDigit = passedDigit;

	__asm {
		mov eax, newDigit
		sub eax, 2
		mov ebx, 1
		xor eax, ebx
		mov newDigit, eax
	}

	passedDigit = newDigit;

	return passedDigit;
}

int decrypt(int & passedDigit)
{
	int newDigit = passedDigit;

	__asm {
		mov eax, newDigit
		mov ebx, 1
		xor eax, ebx
		add eax, 2
		mov newDigit, eax
	}

	passedDigit = newDigit;

	return passedDigit;
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
		cout << code[i] << " ";
	}
	cout << endl;

	cout << "Encrypted Code" << endl;
	for (int i = 0; i < 4; i++)
	{
		cout << encrypt(code[i]) << " ";
	}
	cout << endl;

	cout << "Decrypted Code" << endl;
	for (int i = 0; i < 4; i++)
	{
		cout << decrypt(code[i]) << " ";
	}
	cout << endl;

	return 0;
}