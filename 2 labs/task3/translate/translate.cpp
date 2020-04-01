#include <iostream>
#include <fstream>
#include "MiniDictionary.h"
#include <Windows.h>
#include <algorithm>

using namespace std;

bool ExtractDictionaryFromFile(string nameFileDictionary, Vocabulary &vocabulary)
{
	ifstream dictionaryFile(nameFileDictionary);
	if (dictionaryFile.is_open())
	{
		if (!LoadingWordsInDictionary(dictionaryFile, vocabulary))
		{
			cout << "некорректно записан файл библиотеки" << endl;
			cout << "[england] russian" << endl;
			return false;
		}
	}

	dictionaryFile.close();

	return true;
}

void RunDictionary(Vocabulary &vocabulary, bool &dictionaryChanged)
{
	string inputWord;
	string outputWord;

	do
	{
		getline(cin, inputWord);
		transform(inputWord.begin(), inputWord.end(), inputWord.begin(), tolower);
		if (inputWord.empty())
		{
			continue;
		}

		if (inputWord != "...")
		{
			outputWord = Translate(inputWord, vocabulary);

			if (outputWord == "")
			{
				dictionaryChanged = true;
				cout << "Неизвестное слово \"" << inputWord << "\".";
				cout << "Введите перевод или пустую строку для отказа." << endl;


				getline(cin, outputWord);

				transform(outputWord.begin(), outputWord.end(), outputWord.begin(), tolower);

				if (outputWord.empty())
				{
					cout << "Слово \"" << inputWord << "\" проигнорировано." << endl;
				}
				else
				{
					AddWordToTheDictionary(inputWord, outputWord, vocabulary);
					cout << "Слово \"" << inputWord << "\" сохранено в словаре как \"" << outputWord << "\"" << endl;
				}
			}
			else
			{
				cout << outputWord << endl;
			}
		}

	} while (inputWord != "...");
}
bool ChangeDictionaryContent(Vocabulary &vocabulary, string nameFileDictionary)
{
	string inputWord;

	cout << "В словарь были внесены изменения.";
	cout << "Введите Y или y для сохранения перед выходом." << endl;

	getline(cin, inputWord);

	if (inputWord == "Y" || inputWord == "y")
	{

		if (!SavingTheDictionaryToFile(nameFileDictionary, vocabulary))
		{
			cout << "ошибка при записи файла" << endl;
			return false;
		}

		cout << "Изменения сохранены. Досвидания" << endl;
	}
	else
	{
		cout << "Изменения НЕ сохранены. Досвидания" << endl;
	}

	return true;
}

int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "Russian");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	if (argc != 2)
	{
		std::cout << "invalid number of arguments" << "\n";
		std::cout << "translator.exe <dictionary file>" << std::endl;
		return 1;
	}

	string nameFileDictionary = string(argv[1]);
	Vocabulary vocabulary;

	if (!ExtractDictionaryFromFile(string(argv[1]), vocabulary))
	{
		return 1;
	}

	bool dictionaryChanged = false;

	RunDictionary(vocabulary, dictionaryChanged);

	if (dictionaryChanged)
	{
		if (!ChangeDictionaryContent(vocabulary, string(argv[1])))
		{
			return 1;
		}
	}

	return 0;
}