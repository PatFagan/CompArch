// main.cpp
#include <iostream>
#include <fstream>
using namespace std;

// encrypt data, pass current digit by reference
int encrypt(int &passedDigit)
{
	int newDigit = passedDigit; // move parameter data to a local var to avoid messy data

	__asm {
		mov eax, newDigit; move the current digit to eax
		sal eax, 1; encryption step 1: bit shift left
		neg eax; encryption step 2: negate eax
		sub eax, 2; encryption step 3: subtract eax by 2
		mov ebx, 0; set ebx to 0
		inc ebx; increment ebx by 1
		add eax, ebx; encryption step 4: add eax by the current ebx value
		mov ebx, 2; move two to ebx
		xor eax, ebx; encryption step 5: xor eax with ebx
		mov newDigit, eax
	}

	passedDigit = newDigit;

	return passedDigit;
}

// undo encryption, pass current digit by reference
int decrypt(int & passedDigit)
{
	int newDigit = passedDigit; // move parameter data to a local var to avoid messy data

	__asm {
		mov eax, newDigit; move the current digit into eax
		mov ebx, 2; move 2 into ebx
		xor eax, ebx; decryptionstep 1: xor eax with ebx
		add eax, 2; decryption step 2: add 2 to eax
		dec ebx; decrement ebx
		sub eax, ebx; decryption step 3: subtract eax by the new value of ebx
		neg eax; decryption step 4: negate eax
		sar eax, 1; decryption step 5: bit shift right
		mov newDigit, eax; move the new value from eax into newdigit
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