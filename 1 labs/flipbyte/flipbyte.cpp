#include <iostream>
#include <string>

using namespace std;

unsigned int Reverse(unsigned int number)// реверсирование битов
{
	uint8_t numberBit = number;
	numberBit = (numberBit & 0xF0) >> 4 | (numberBit & 0x0F) << 4;
	numberBit = (numberBit & 0xCC) >> 2 | (numberBit & 0x33) << 2;
	numberBit = (numberBit & 0xAA) >> 1 | (numberBit & 0x55) << 1;
	number = numberBit;
	return number;
}

int main(int argc, char* argv[])
{
	if (argc < 2)
	{
		cout << "no parameter" << endl;
		return 1;
	}
	else if (argc > 2)
	{
		cout << "error entering parameter" << endl;
		return 1;
	}

	string line;
	line = argv[1];
	int sizeLine = line.length();


	int number = 0;

	for (int i = 0; i < sizeLine; i++)
	{
		char Symbol = line.c_str()[i];
		if (Symbol < '0' || Symbol > '9')
		{
			cout << "Invalid line";
			return 1;
		}

		number = number * 10 + line[i] - 0x30;
		if (number > 255)
		{
			cout << "number is greater than the limit" <<endl;
			return 1;
		}
	}

	if (number < 0 || number > 255)
	{
		cout << "number is greater than the specified range"<< endl;
		return 1;
	}

	number = Reverse(number);
	cout << number << endl;


	return 0;
}