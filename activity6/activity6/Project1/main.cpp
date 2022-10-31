// main.cpp
#include <iostream>
using namespace std;

extern "C" int _asmMain();

extern "C" double _getDouble() 
{
	double d;
	cin >> d;
	return d;
}

extern "C" void _printString(char* s)
{
	cout << s;
	return;
}

extern "C" void _printDouble(double d)
{
	cout << d << endl;
}

// main stub driver
int main() 
{
	_asmMain();
	return 0;
}