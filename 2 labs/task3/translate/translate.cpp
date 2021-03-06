﻿#include <iostream>
#include <fstream>
#include "MiniDictionary.h"
#include <Windows.h>
#include <algorithm>

using namespace std;

bool ExtractDictionaryFromFile(const string dictionaryPath, Vocabulary &vocabulary)
{
	ifstream dictionaryFile(dictionaryPath);
	if (dictionaryFile.is_open())
	{
		istream& streamToDictionaryFile = dictionaryFile;
		if (!DownloadTranslationsFromDictionary(streamToDictionaryFile, vocabulary))
		{
			cout << "некорректно записан файл библиотеки" << endl;
			cout << "[england] russian" << endl;
			return false;
		}
	}

	return true;
}

bool RunAndChangeDictionary(Vocabulary& vocabulary)
{
	bool dictionaryChanged = false;
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
					AddWordToDictionary(inputWord, outputWord, vocabulary);
					cout << "Слово \"" << inputWord << "\" сохранено в словаре как \"" << outputWord << "\"" << endl;
				}
			}
			else
			{
				cout << outputWord << endl;
			}
		}
	} while (inputWord != "...");

	return dictionaryChanged;
}

bool ChangeDictionaryContent(Vocabulary &vocabulary, string dictionaryPath)
{
	cout << "В словарь были внесены изменения.";
	cout << "Введите Y или y для сохранения перед выходом." << endl;

	string inputWord;
	getline(cin, inputWord);
	if (inputWord == "Y" || inputWord == "y")
	{
		ofstream outputDictionaryFile(dictionaryPath);
		if (!outputDictionaryFile.is_open())
		{
			cout << "ошибка при открытии файла" << endl;
			return false;
		}
		ostream& streamToOutputDictionaryFile = outputDictionaryFile;
		SavingDictionaryToFile(streamToOutputDictionaryFile, vocabulary);

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

	Vocabulary vocabulary;
	if (!ExtractDictionaryFromFile(string(argv[1]), vocabulary))
	{
		return 1;
	}

	if (RunAndChangeDictionary(vocabulary))
	{
		if (!ChangeDictionaryContent(vocabulary, string(argv[1])))
		{
			return 1;
		}
	}

	return 0;
}