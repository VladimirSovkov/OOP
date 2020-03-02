#include <iostream>
#include <fstream>
#include <string>

using namespace std;

//Искомая строка не может быть пустой.

string IsThereGivenLine(
	string lineElement, 
	const string SEARCH_ELEMENT, 
	const string INSERTABLE_ELEMENT)
{
	size_t sizeSearchElement = SEARCH_ELEMENT.length();
	size_t sizeInsertableElement = INSERTABLE_ELEMENT.length();
	size_t indexChar = lineElement.find(SEARCH_ELEMENT);
	for (indexChar; indexChar != string::npos; )
	{
		lineElement.erase(indexChar, sizeSearchElement); //Удаляет подстроку из строки
		lineElement.insert(indexChar, INSERTABLE_ELEMENT);// добавляет новою подстроку в строку
		indexChar = lineElement.find(SEARCH_ELEMENT, indexChar + sizeInsertableElement);
	}
	
	return lineElement;
}

int main(int argc, char *argv[])
{
	setlocale(0, "ru");
	if (argc != 5)
	{
		cout << "Empty search string" << endl;
		return 1;
	}

	string lineElement = "";
	ifstream inputFile;
	inputFile.open(argv[1]);
	ofstream outputFile;
	outputFile.open(argv[2]);


	if (!inputFile.is_open())//проверка на открытие файла для чтения
	{
		cout << "Errore is open input file!" << endl;
		return 1;
	}

	if (!outputFile.is_open())//проверка на открытие файла для записи
	{
		return 1;
	}

	string SearchElement = string(argv[3]);
	string InsertableElement = string(argv[4]);

	while (getline(inputFile, lineElement))
	{

		
		if (lineElement.length() >= SearchElement.length())
		{
			lineElement = IsThereGivenLine(lineElement, SearchElement, InsertableElement);
		}
		outputFile << lineElement << endl;
		lineElement = "";
	}
	inputFile.close();
	outputFile.close();

	return 0;
}