#include <iostream>
#include <fstream>

using namespace std;

char GetCharacterAfterLogicalOrWithKey(char symbol, int key)// XOR
{
	symbol = symbol ^ key;
	return symbol;
}

char GetByteWithMixedBits(uint8_t symbol, int movementIndex[])//Перестановка битов в байте 
{
	uint8_t variableForBitOffset = symbol;
	uint8_t mixedBitByte = 0;

	const int AMOUNT_OF_BITS_IN_A_BYTE = 8;
	uint8_t arrangementOfUnitsInBytes[AMOUNT_OF_BITS_IN_A_BYTE]
	{ 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80 };

	int offsetNumber = 0;

	for (int i = 0; i < AMOUNT_OF_BITS_IN_A_BYTE; i++)
	{
		variableForBitOffset = symbol;
		offsetNumber = i - movementIndex[i];
		if (offsetNumber < 0)
		{
			offsetNumber *= -1;
			variableForBitOffset = variableForBitOffset << offsetNumber;
		}
		else
		{
			variableForBitOffset = variableForBitOffset >> offsetNumber;
		}

		variableForBitOffset = variableForBitOffset &
			arrangementOfUnitsInBytes[movementIndex[i]];

		mixedBitByte = mixedBitByte ^ variableForBitOffset;
	}

	return mixedBitByte;
}

char GetEncryptedBit(char symbol, int key)
{
	symbol = GetCharacterAfterLogicalOrWithKey(symbol, key);
	int movementIndex[]{ 2, 3, 4, 6, 7, 0, 1, 5 };
	symbol = GetByteWithMixedBits(symbol, movementIndex);

	return symbol;
}

char GetDecryptedBit(char symbol, int key)
{
	int movementIndex[]{ 5, 6, 0, 1, 2, 7, 3, 4 };
	symbol = GetByteWithMixedBits(symbol, movementIndex);
	symbol = GetCharacterAfterLogicalOrWithKey(symbol, key);

	return symbol;
}

int main(int argc, char* argv[])
{
	if (argc != 5)
	{
		if (argc < 5)
			cout << "not enough arguments" << endl;
		else
			cout << "argument overflow" << endl;
		cout << "crypt.exe crypt <input file> <output file> <key>" << endl;
		cout << "OR" << endl;
		cout << "crypt.exe decrypt <input file> <output file> <key> " << endl;
		return 1;
	}

	ifstream inputFile;
	inputFile.open(argv[2], ios::binary);
	if (!inputFile.is_open())
	{
		cout << "Errore open file" << endl;
		return 1;
	}

	char symbol = '0';

	ofstream outputFile;
	outputFile.open(argv[3], ios::binary);
	if (!outputFile.is_open())
	{
		cout << "Errore open output file" << endl;
		return 1;
	}

	if (!atoi(argv[4]))
	{
		cout << "key consists of invalid characters" << endl;
		return 1;
	}

	int key = atoi(argv[4]);

	if (key < 0 || key > 255)
	{
		cout << "key is greater than the limit" << endl;
		return 1;
	}

	string valueFirstArgv = argv[1];

	if (valueFirstArgv == "crypt")
	{
		while (inputFile.get(symbol))// для шифровки 
		{
			symbol = GetEncryptedBit(symbol, key);
			outputFile.write(&symbol, sizeof(symbol));
		}
	}
	else
	{
		if (valueFirstArgv == "decrypt")
		{
			while (inputFile.get(symbol))// для шифровки 
			{
				symbol = GetDecryptedBit(symbol, key);
				outputFile.write(&symbol, sizeof(symbol));
			}
		}
		else
		{
			cout << "Erorre do not function crypt" << endl;
			return 1;
		}
	}

	inputFile.close();
	outputFile.close();
	return 0;
}