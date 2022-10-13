// main.cpp
#include <iostream>
using namespace std;

extern "C" int asmMain();

extern "C" int setFirstValue();
extern "C" int setSecondValue();

int main() 
{
	cout << asmMain();
	return 0;
}

extern "C" int getInput()
{
	cout << "Input number: ";
	int inputNumber;
	cin >> inputNumber;
	return inputNumber;
}

extern "C" void displayResult(int result)
{
	cout << "The sum is: " << result;
}